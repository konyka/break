# Plugins / MetaHumanToolkit

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit`
- headers: 7; symbols: 277
- symbol kinds: class=8, delegate=11, enum=1, enumerator=2, function=29, macro=5, member=56, prototype=164, struct=1
- PrivateDependencyModuleNames: CaptureDataCore, Engine, InputCore, MediaAssets, MetaHumanCore, ProceduralMeshComponent, Projects, PropertyEditor, RenderCore, ToolMenus
- PublicDependencyModuleNames: AdvancedPreviewScene, Core, CoreUObject, ImgMedia, MetaHumanCaptureData, MetaHumanImageViewer, MetaHumanImageViewerEditor, MetaHumanSequencer, MovieScene, MovieSceneTracks, Sequencer, Slate, SlateCore, UnrealEd

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit/Public/MetaHumanABCommandList.h` (Public)


#### class `FMetaHumanABCommandList`  
`class FMetaHumanABCommandList final`  
_L15-64_
- desc: A helper class to manage the command lists in the AB view environments. It is basically a container for two distinct FUICommandList objects with helper functions to bind commands using a single function call. This can be passed around by value as the internals are just pointers
- L18 _public function_ `FMetaHumanABCommandList() : CommandListA`
- L31 _public function_ `template<typename UserClass, ESPMode Mode, typename ExecuteActionFunc, typename CanExecuteActionFunc, typename IsActionCheckedFunc, typename... VarTypes> void MapAction(TSharedPtr<FUICommandInfo> InCommand, TSharedRef<UserClass, Mode> InObject, ExecuteActionFunc InExecuteActionFunc, CanExecuteActionFunc InCanExecuteActionFunc, IsActionCheckedFunc InIsActionCheckedFunc, VarTypes... InVars)` — @brief Maps the given member functions to each command list so they are called with the appropriate EABImageViewMode enum @param InCommand The FUICommandInfo to map in the command lists @param InObject The object that will get called when the command is activated @param InExecuteActionFunc The member function of the given object that will get called with the command is triggered @param InIsActionCheckedFunc The member function of the give object called to determine if the action is checked or not
- L52 _public function_ `TSharedPtr<FUICommandList> GetCommandList(EABImageViewMode InViewMode)` — Gets the command list for a view mode
- L60 _private member_ `TSharedPtr<FUICommandList> CommandListA;` — Command list associated with view A
- L63 _private member_ `TSharedPtr<FUICommandList> CommandListB;` — Command list associated with view B

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit/Public/MetaHumanEditorViewportClient.h` (Public)


#### struct `FMetaHumanViewportClientDepthData`  
`struct FMetaHumanViewportClientDepthData`  
_L19-78_
- desc: Struct for storing information about near and far plane for depth data.
- L21 _public function_ `FMetaHumanViewportClientDepthData(float InNear, float InFar, float InNearMin, float InNearMax, float InNearFarDelta = 1.0f) : Near(InNear) , Far(InFar) , DepthRangeNear(TRange<float>::Inclusive(InNearMin, InNearMax)) , NearFarDelta(InNearFarDelta)`
- L32 _public function_ `void SetNear(float InValue)`
- L38 _public function_ `float GetNear() const`
- L43 _public function_ `void SetFar(float InValue)`
- L48 _public function_ `float GetFar() const`
- L53 _public function_ `TRange<float> GetRangeNear() const`
- L58 _public function_ `TRange<float> GetRangeFar() const`
- L68 _private member_ `float Near = 10.0f;` — Near plane value
- L71 _private member_ `float Far = 55.0f;` — Far plane value
- L74 _private member_ `TRange<float> DepthRangeNear;` — Valid range for near value
- L77 _private member_ `float NearFarDelta = 1.0f;` — Minimal allowed difference between far and near value

#### class `FMetaHumanEditorViewportClient`  
`class FMetaHumanEditorViewportClient : public FEditorViewportClient , public TSharedFromThis<FMetaHumanEditorViewportClient>`  
_L91-379_
- inherits: `FEditorViewportClient,TSharedFromThis<FMetaHumanEditorViewportClient>`
- desc: The base class for viewport clients used in the MetaHuman asset editor viewports that need to support the AB split functionality and user manipulation of tracker contour data. The viewport client is the point of contact between the toolkit and anything related to manipulating the viewport. As a general guideline on using this class, any interaction with viewport by external classes should be handled by the viewport client. If the viewport client needs any information from external classes it should request it through a delegate. This class is meant to work on its own but it relies on delegates to get which components should be hidden for views A and B, see GetHiddenComponentsForView. There is also functionality to manipulate components with UE's standard transform gizmo and delegates called when the camera moves and stops. The viewport client also controls the active navigation mode by means of locking and unlocking the navigation
- L96 _public prototype_ `FMetaHumanEditorViewportClient(FPreviewScene* InPreviewScene, class UMetaHumanViewportSettings* InViewportSettings = nullptr);`
- L97 _public prototype_ `virtual ~FMetaHumanEditorViewportClient();`
- L100 _public prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L101 _public prototype_ `virtual void ProcessClick(FSceneView& InView, HHitProxy* InHitProxy, FKey InKey, EInputEvent InEvent, uint32 InHitX, uint32 InHitY) override;`
- L102 _public prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L103 _public prototype_ `virtual void SetWidgetMode(UE::Widget::EWidgetMode InWidgetMode) override;`
- L104 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L105 _public prototype_ `virtual void TrackingStarted(const struct FInputEventState& InInputState, bool bInIsDraggingWidget, bool bInNudge) override;`
- L106 _public prototype_ `virtual void TrackingStopped() override;`
- L107 _public prototype_ `virtual bool InputWidgetDelta(FViewport* InViewport, EAxisList::Type InCurrentAxis, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L108 _public prototype_ `virtual void PerspectiveCameraMoved() override;`
- L109 _public prototype_ `virtual void EndCameraMovement() override;`
- L110 _public prototype_ `virtual void UpdateMouseDelta() override;`
- L111 _public prototype_ `virtual void SetCameraSpeedSettings(const FEditorViewportCameraSpeedSettings& InCameraSpeedSettings) override;`
- L115 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;` — The base class for viewport clients used in the MetaHuman asset editor viewports that need to support the AB split functionality and user manipulation of tracker contour data. The viewport client is the point of contact between the toolkit and anything related to manipulating the viewport. As a general guideline on using this class, any interaction with viewport by external classes should be handled by the viewport client. If the viewport client needs any information from external classes it should request it through a delegate. This class is meant to work on its own but it relies on delegates to get which components should be hidden for views A and B, see GetHiddenComponentsForView. There is also functionality to manipulate components with UE's standard transform gizmo and delegates called when the camera moves and stops. The viewport client also controls the active navigation mode by means of locking and unlocking the navigation class FMetaHumanEditorViewportClient : public FEditorViewportClient , public TSharedFromThis<FMetaHumanEditorViewportClient> { public: UE_API FMetaHumanEditorViewportClient(FPreviewScene* InPreviewScene, class UMetaHumanViewportSettings* InViewportSettings = nullptr); UE_API virtual ~FMetaHumanEditorViewportClient(); ~Begin FEditorViewportClient interface UE_API virtual void Tick(float InDeltaSeconds) override; UE_API virtual void ProcessClick(FSceneView& InView, HHitProxy* InHitProxy, FKey InKey, EInputEvent InEvent, uint32 InHitX, uint32 InHitY) o
- L116 _public prototype_ `virtual FString GetReferencerName() const override;`
- L122 _public prototype_ `DECLARE_DELEGATE_RetVal(TArray<class UPrimitiveComponent*>, FOnGetAllPrimitiveComponents) FOnGetAllPrimitiveComponents OnGetAllPrimitiveComponentsDelegate;` — A delegate used to query all primitive components that are in the preview scene
- L126 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(class UPrimitiveComponent*, FOnGetPrimitiveComponentInstance, class UPrimitiveComponent* InPrimitiveComponent) FOnGetPrimitiveComponentInstance OnGetPrimitiveComponentInstanceDelegate;` — A delegate used get the primitive component instance of a given primitive component. The instance is what is displayed
- L130 _public prototype_ `DECLARE_DELEGATE_RetVal(TArray<class UPrimitiveComponent*>, FOnGetSelectedPrimitiveComponents) FOnGetSelectedPrimitiveComponents OnGetSelectedPrimitivesComponentsDelegate;` — A delegate used to query which components are selected so they can be highlighted in the viewport
- L134 _public prototype_ `DECLARE_DELEGATE_RetVal(EIdentityPoseType, FOnGetSelectedPoseType) FOnGetSelectedPoseType OnGetSelectedPoseTypeDelegate;` — A delegate used to query which pose is currently selected in the tree view
- L138 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnPrimitiveComponentClicked, const class UPrimitiveComponent*) FOnPrimitiveComponentClicked OnPrimitiveComponentClickedDelegate;` — Delegated called when a click is detected in a component
- L147 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FOnShouldUnlockNavigation) FOnShouldUnlockNavigation OnShouldUnlockNavigationDelegate;` — A delegate called to query if the navigation should really be unlocked if there is no visible footage component in the current view mode. UpdateABVisibility will determine if the navigation should be locked or unlocked based on which components are present in the current view mode. If it determines that no footage component is visible it defaults to unlock the navigation, going back to 3D mode, however, this delegate can be used to keep the navigation locked if it returns false.
- L151 _public member_ `FSimpleMulticastDelegate OnCameraMovedDelegate;` — Called every time the camera moves
- L154 _public member_ `FSimpleMulticastDelegate OnCameraStoppedDelegate;` — Called when the camera stops moving
- L157 _public prototype_ `DECLARE_DELEGATE_TwoParams(FOnUpdateDepthData, float, float) FOnUpdateDepthData OnUpdateFootageDepthDataDelegate;` — Triggered when footage depth data is changed.
- L161 _public member_ `FOnUpdateDepthData OnUpdateMeshDepthDataDelegate;` — Triggered when mesh depth data is changed.
- L164 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnUpdateDepthMapVisibility, bool) FOnUpdateDepthMapVisibility OnUpdateDepthMapVisibilityDelegate;` — Triggered when the visibility of the depth map is changed
- L170 _public function_ `virtual TArray<class UPrimitiveComponent*> GetHiddenComponentsForView(EABImageViewMode InViewMode) const` — Can be overridden to determine which components are visible for a given view mode
- L173 _public prototype_ `virtual void FocusViewportOnSelection();` — Focus the viewport on the selected components. Uses OnGetSelectedPrimitivesComponentsDelegate to determine the bounding box to focus on
- L180 _public prototype_ `virtual void UpdateABVisibility(bool bInSetViewpoint = true);` — Function that should be called anytime the visibility state of a component in the viewport changes. This function will hide components depending on the active view mode and will manage the scene capture components responsible for capturing the views A and B while in AB Split or AB Wipe modes.
- L183 _public prototype_ `virtual bool CanChangeEV100(EABImageViewMode InViewMode) const;` — Return true if the EV100 value can be changed
- L186 _public prototype_ `virtual bool CanChangeViewMode(EABImageViewMode InViewMode) const;` — Returns true if the view mode can be changed
- L189 _public prototype_ `virtual class UMetaHumanFootageComponent* GetActiveFootageComponent(const TArray<UPrimitiveComponent*>& InAllComponents) const;` — Returns which of InAllComponents is the active, but not necessarily visible, footage component
- L192 _public prototype_ `virtual bool GetSetViewpoint() const;` — Returns true if the view point is defined by the capture data (true for cases where you have footage, and thus a camera, but false for mesh capture data)
- L195 _public prototype_ `void UpdateSceneCaptureComponents(bool bInClearHiddenComponents = false);` — Updates the scene capture components based on the active view mode with the option to clear the hidden components
- L198 _public prototype_ `void SetEditorViewportWidget(TSharedRef<class SMetaHumanEditorViewport> InEditorViewportWidget);` — Sets the viewport widget we are going to control and creates the scene capture components to handle views A and B.
- L201 _public prototype_ `bool IsViewModeIndexEnabled(EABImageViewMode InViewMode, EViewModeIndex InViewModeIndex, bool) const;` — Returns if the given EViewModeIndex is enable for a particular EABImageViewMode
- L204 _public prototype_ `void SetViewModeIndex(EABImageViewMode InViewMode, EViewModeIndex InViewModeIndex, bool bInNotify);` — Sets the view mode index for view A or view B
- L207 _public prototype_ `float GetEV100(EABImageViewMode InViewMode) const;` — Returns the EV100 value for view A or view B
- L210 _public prototype_ `void SetEV100(float InValue, EABImageViewMode InViewMode, bool bInNotify);` — Sets the exposure for view A or view B. The value comes first to allow binding directly to the spinbox Value function
- L213 _public prototype_ `static FPostProcessSettings GetDefaultPostProcessSettings();` — Returns the default post process settings to be used with this viewport
- L216 _public prototype_ `const FPostProcessSettings& GetPostProcessSettingsForCurrentView() const;` — Returns the post process settings for the current view if single of View A if wipe or dual
- L219 _public prototype_ `void SetDepthMeshComponent(class UMetaHumanDepthMeshComponent* InDepthMeshComponent);` — Sets the depth mesh component used to display depth data as a 3D mesh
- L222 _public prototype_ `void SetFootageDepthData(const FMetaHumanViewportClientDepthData& InDepthData);` — Updates footage depth data.
- L225 _public prototype_ `FMetaHumanViewportClientDepthData GetFootageDepthData() const;` — Returns footage depth data.
- L228 _public prototype_ `void SetMeshDepthData(const FMetaHumanViewportClientDepthData& InDepthData);` — Updates mesh depth data.
- L231 _public prototype_ `FMetaHumanViewportClientDepthData GetMeshDepthData() const;` — Returns mesh depth data.
- L234 _public prototype_ `EViewModeIndex GetViewModeIndexForABViewMode(EABImageViewMode InViewMode) const;` — Returns the view mode index for view A or view B
- L237 _public prototype_ `EABImageViewMode GetABViewMode() const;` — Returns the current active AB view mode
- L240 _public prototype_ `void SetNavigationLocked(bool bIsLocked);` — Lock the navigation by changing it to 2D navigation mode
- L243 _public prototype_ `bool IsNavigationLocked() const;` — Returns whether or not the navigation is locked for the active AB view mode
- L246 _public prototype_ `bool IsCameraMoving() const;` — Returns whether or not the camera is moving
- L249 _public prototype_ `void SetCurveDataController(const TSharedPtr<class FMetaHumanCurveDataController> InCurveDataController);` — Sets the shape annotation with tracking data to be drawn in the viewport as an overlay
- L252 _public prototype_ `void SetTrackerImageSize(const FIntPoint& InTrackerImageSize);` — Sets the size of the tracker image. This is used to place the contour data on screen
- L255 _public prototype_ `void SetEditCurvesAndPointsEnabled(bool bInCanEdit);` — Sets whether or not points and curves can be edited by means of user interaction
- L258 _public prototype_ `void RefreshTrackerImageViewer();` — Updates the tracker image viewer by resetting its state
- L261 _public prototype_ `void ResetABWipePostion();` — Calls a AB wipe reset on SABImage
- L264 _public prototype_ `void StoreCameraStateInViewportSettings();` — Store the camera state in the viewport settings so it can be serialized and restored later
- L267 _public prototype_ `void SetABViewMode(EABImageViewMode InViewMode);` — Sets the new active AB view mode
- L270 _public prototype_ `void NotifyViewportSettingsChanged() const;` — Trigger viewport settings changed delegate to broadcast
- L272 _public prototype_ `bool IsShowingSingleView() const;`
- L273 _public prototype_ `bool IsShowingDualView() const;`
- L274 _public prototype_ `bool IsShowingWipeView() const;`
- L276 _public prototype_ `bool IsShowingViewA() const;`
- L277 _public prototype_ `bool IsShowingViewB() const;`
- L279 _public prototype_ `void ToggleABViews();`
- L280 _public prototype_ `void ToggleShowCurves(EABImageViewMode InViewMode);`
- L281 _public prototype_ `void ToggleShowControlVertices(EABImageViewMode InViewMode);`
- L283 _public prototype_ `virtual bool CanToggleShowCurves(EABImageViewMode InViewMode) const;`
- L284 _public prototype_ `virtual bool CanToggleShowControlVertices(EABImageViewMode InViewMode) const;`
- L287 _public prototype_ `bool IsShowingCurves(EABImageViewMode InViewMode) const;` — Returns the state of the Curves toggle
- L290 _public prototype_ `bool IsShowingControlVertices(EABImageViewMode InViewMode) const;` — Returns the state of the Control Vertices toggle
- L293 _public prototype_ `virtual bool ShouldShowCurves(EABImageViewMode InViewMode) const;` — Returns whether the viewport allows the rendering of the curves
- L295 _public prototype_ `virtual bool ShouldShowControlVertices(EABImageViewMode InViewMode) const;` — Returns whether the viewport allows the rendering of the control points
- L297 _public prototype_ `virtual bool IsFootageVisible(EABImageViewMode InViewMode) const;`
- L299 _public prototype_ `bool IsRigVisible(EABImageViewMode InViewMode) const;`
- L300 _public prototype_ `bool IsDepthMeshVisible(EABImageViewMode InViewMode) const;`
- L301 _public prototype_ `bool IsShowingUndistorted(EABImageViewMode InViewMode) const;`
- L303 _public prototype_ `void ToggleRigVisibility(EABImageViewMode InViewMode);`
- L304 _public prototype_ `void ToggleFootageVisibility(EABImageViewMode InViewMode);`
- L305 _public prototype_ `void ToggleDepthMeshVisible(EABImageViewMode InViewMode);`
- L306 _public prototype_ `void ToggleDistortion(EABImageViewMode InViewMode);`
- L309 _public function_ `bool CanExecuteAction(EABImageViewMode InViewMode) const` — A default CanExecuteAction function used when mapping actions in with the FABCommandList
- L315 _public prototype_ `FVector2D GetWidgetSize() const;` — Returns the size of the STrackerImageViewer widget
- L318 _public prototype_ `FVector2D GetPointPositionOnImage(const FVector2D& InScreenPosition) const;` — Returns image coordinates for specified screen position
- L321 _public prototype_ `void SetOverlay(const FText& InOverlay) const;` — Set a text overlay in the STrackerImageViewer widget
- L326 _protected member_ `TMap<EABImageViewMode, TObjectPtr<class UMetaHumanSceneCaptureComponent2D>> ABSceneCaptureComponents;` — Map holding the state of each view
- L329 _protected member_ `TObjectPtr<class UPostProcessComponent> PostProcessComponent;` — A post process component used to control exactly how we display the scene in the viewport
- L332 _protected member_ `FMetaHumanViewportClientDepthData DepthDataFootage { 10.0f, 55.0f, 2.0f, 200.0f };` — Current depth data setup for footage.
- L335 _protected member_ `FMetaHumanViewportClientDepthData DepthDataMesh { 10.0f, 55.0f, 2.0f, 200.0f };` — Current depth data setup for mesh.
- L338 _protected member_ `TWeakObjectPtr<class UMetaHumanDepthMeshComponent> DepthMeshComponent;` — A reference to the depth mesh component
- L341 _protected member_ `TObjectPtr<class UMetaHumanViewportSettings> ViewportSettings;` — A reference to the viewport settings being used to store the state of this viewport
- L346 _private prototype_ `TSharedRef<class SMetaHumanEditorViewport> GetMetaHumanEditorViewport() const;` — Returns a reference to the SMetaHumanEditorViewport we are controlling
- L349 _private prototype_ `TSharedRef<SMetaHumanOverlayWidget<STrackerImageViewer>> GetTrackerImageViewer() const;` — Returns the STrackerImage widget we are controlling. The widget lives in SMetaHumanEditorViewport
- L352 _private prototype_ `TArray<class UPrimitiveComponent*> GetSelectedPrimitiveComponents() const;` — Uses OnGetSelectedPrimitivesComponentsDelegate to determine which components are selected
- L355 _private prototype_ `FBox GetComponentsBoundingBox(const TArray<class UPrimitiveComponent*>& InComponents) const;` — Calculates the bounding box of given list of primitive components
- L358 _private prototype_ `void GetAllComponentsAndComponentsHiddenForView(TArray<class UPrimitiveComponent*>& OutAllComponents, TMap<EABImageViewMode, TArray<class UPrimitiveComponent*>>& OutHiddenComponentsForView) const;` — Returns the list of all primitive components in the viewport and a map of which components are marked as hidden for view A and B
- L361 _private prototype_ `bool IsAnyFootageComponentVisible(const TArray<class UPrimitiveComponent*>& InAllComponents, const TMap<EABImageViewMode, TArray<class UPrimitiveComponent*>>& InHiddenComponentsForView) const;` — Determine if there is any footage components visible in the viewport
- L364 _private prototype_ `void UpdateCameraViewportFromFootage(const TArray<UPrimitiveComponent*>& InAllComponents, bool bInIsAnyFootageComponentVisible, bool bInSetViewpoint);` — Update the camera viewport size based on the available footage image size
- L369 _private member_ `UE::Widget::EWidgetMode WidgetMode;` — The current gizmo widget mode
- L372 _private member_ `FVector InitialPivotLocation;` — The initial pivot location when the user starts interacting with gizmos in the viewport
- L375 _private member_ `uint8 bIsManipulating : 1;` — True if we are manipulating a component through a gizmo
- L378 _private member_ `TUniquePtr<class FScopedTransaction> ScopedTransaction;` — The transaction used to record modifications done using the gizmos in the viewport

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANTOOLKIT_API`
- L122 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<class UPrimitiveComponent*>, FOnGetAllPrimitiveComponents) FOnGetAllPrimitiveComponents OnGetAllPrimitiveComponentsDelegate;` — A delegate used to query all primitive components that are in the preview scene
- L126 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(class UPrimitiveComponent*, FOnGetPrimitiveComponentInstance, class UPrimitiveComponent* InPrimitiveComponent) FOnGetPrimitiveComponentInstance OnGetPrimitiveComponentInstanceDelegate;` — A delegate used get the primitive component instance of a given primitive component. The instance is what is displayed
- L130 _delegate_ `DECLARE_DELEGATE_RetVal(TArray<class UPrimitiveComponent*>, FOnGetSelectedPrimitiveComponents) FOnGetSelectedPrimitiveComponents OnGetSelectedPrimitivesComponentsDelegate;` — A delegate used to query which components are selected so they can be highlighted in the viewport
- L134 _delegate_ `DECLARE_DELEGATE_RetVal(EIdentityPoseType, FOnGetSelectedPoseType) FOnGetSelectedPoseType OnGetSelectedPoseTypeDelegate;` — A delegate used to query which pose is currently selected in the tree view
- L138 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPrimitiveComponentClicked, const class UPrimitiveComponent*) FOnPrimitiveComponentClicked OnPrimitiveComponentClickedDelegate;` — Delegated called when a click is detected in a component
- L147 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FOnShouldUnlockNavigation) FOnShouldUnlockNavigation OnShouldUnlockNavigationDelegate;` — A delegate called to query if the navigation should really be unlocked if there is no visible footage component in the current view mode. UpdateABVisibility will determine if the navigation should be locked or unlocked based on which components are present in the current view mode. If it determines that no footage component is visible it defaults to unlock the navigation, going back to 3D mode, however, this delegate can be used to keep the navigation locked if it returns false.
- L157 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnUpdateDepthData, float, float) FOnUpdateDepthData OnUpdateFootageDepthDataDelegate;` — Triggered when footage depth data is changed.
- L164 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUpdateDepthMapVisibility, bool) FOnUpdateDepthMapVisibility OnUpdateDepthMapVisibilityDelegate;` — Triggered when the visibility of the depth map is changed

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit/Public/MetaHumanToolkitBase.h` (Public)


#### class `FMetaHumanToolkitBase`  
`class FMetaHumanToolkitBase : public FBaseAssetToolkit , public FGCObject , public FNotifyHook , public FSelfRegisteringEditorUndoClient`  
_L25-222_
- inherits: `FBaseAssetToolkit,FGCObject,FNotifyHook,FSelfRegisteringEditorUndoClient`
- desc: A base toolkit class with common functionality of the MetaHuman asset editors. FMetaHumanToolkitBase provides a toolkit with with a details panel, sequencer and viewport. The viewport has AB capabilities by default with a post process component already in the scene to control exactly how the viewport behaves. Derived classes have the option to provide an extra widget to be displayed in the bottom of the viewport as well as extra entries to the AB view menus to control the visibility of components displayed in the viewport.
- L32 _public prototype_ `FMetaHumanToolkitBase(UAssetEditor* InOwningAssetEditor);`
- L33 _public prototype_ `virtual ~FMetaHumanToolkitBase();`
- L38 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L39 _public prototype_ `virtual FString GetReferencerName() const override;`
- L43 _public prototype_ `virtual bool IsPrimaryEditor() const override;`
- L44 _public prototype_ `virtual void CreateWidgets() override;`
- L45 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L46 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager) override;`
- L47 _public prototype_ `virtual void PostInitAssetEditor() override;`
- L51 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FProperty* InPropertyThatChanged) override;`
- L55 _public prototype_ `virtual void PostUndo(bool bInSuccess) override;`
- L56 _public prototype_ `virtual void PostRedo(bool bInSuccess) override;`
- L62 _protected prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L63 _protected prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;`
- L69 _protected function_ `virtual void BindCommands()` — Override to bind commands that are specific to a MetaHuman toolkit
- L72 _protected prototype_ `virtual TSharedRef<SWidget> GetViewportExtraContentWidget();` — Override to return a extra widget to be displayed in the bottom of the viewport
- L75 _protected function_ `virtual void HandleGetViewABMenuContents(EABImageViewMode InViewMode, class FMenuBuilder& InMenuBuilder)` — Override to customize the menus to control the visibility of components in the views A and B
- L78 _protected function_ `virtual bool IsTimelineEnabled() const` — Override to control if timeline widget is enabled
- L83 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Sequencer(const FSpawnTabArgs& InArgs);` — Spawns the sequencer tab
- L85 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& InArgs);`
- L87 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& InArgs);`
- L89 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSettings(const FSpawnTabArgs& InArgs);`
- L92 _protected prototype_ `TRange<int32> GetSequencerPlaybackRange() const;` — Get the current sequencer playback range
- L95 _protected prototype_ `FFrameNumber GetCurrentFrameNumber() const;` — Returns the current frame number in sequencer
- L104 _protected prototype_ `void SetMediaTrack(EMediaTrackType InTrackType, TSubclassOf<class UMetaHumanMovieSceneMediaTrack> InTrackClass, class UImgMediaSource* InImageSequence, FTimecode InTimecode, FFrameNumber InStartFrameOffset = 0);` — Set or create a media track with the given image sequence
- L105 _protected prototype_ `void SetMediaTrack(TSubclassOf<class UMovieSceneAudioTrack> InTrackClass, class USoundBase* InAudio, FTimecode InTimecode, FFrameNumber InStartFrameOffset = 0);`
- L108 _protected prototype_ `void ClearMediaTracks();` — Removes all media tracks from sequencer
- L111 _protected prototype_ `bool ChannelContainsKey(class UMetaHumanMovieSceneMediaTrack* InMediaTrack, const FFrameNumber& InFrameTime) const;` — Returns true if the given media track has a key in the given frame time
- L114 _protected prototype_ `virtual void HandleSequencerGlobalTimeChanged();` — Called when the global time in sequencer changes
- L117 _protected function_ `virtual void HandleSequencerMovieSceneDataChanged(EMovieSceneDataChangeType InDataChangeType)` — Called when sequencer triggers a movie scene data changed event
- L120 _protected function_ `virtual void HandleSequencerKeyAdded(struct FMovieSceneChannel* InChannel, const TArray<struct FKeyAddOrDeleteEventItem>& InItems)` — Called when a key is added through the sequencer UI
- L123 _protected function_ `virtual void HandleSequencerKeyRemoved(struct FMovieSceneChannel* InChannel, const TArray<struct FKeyAddOrDeleteEventItem>& InItems)` — Called when a key is removed from the sequencer UI
- L126 _protected function_ `virtual void HandleFootageDepthDataChanged(float InNear, float InFar)` — Called when footage depth data changes.
- L129 _protected function_ `virtual void HandleMeshDepthDataChanged(float InNear, float InFar)` — Called when mesh depth data changes.
- L132 _protected prototype_ `virtual void HandleDepthMapVisibilityChanged(bool bInDepthMapVisibility);` — Called when mesh depth map visibility changes.
- L137 _protected function_ `virtual void HandleUndoOrRedoTransaction(const class FTransaction* InTransaction)` — Handles an Undo or Redo transaction. The base implementation does nothing by default
- L140 _protected prototype_ `void CreateDepthMeshComponent(class UCameraCalibration* InCameraCalibration);` — Creates the depth mesh visualization component using the information from the given camera calibration
- L143 _protected prototype_ `void SetDepthMeshTexture(class UTexture* InDepthTexture);` — Uses the given texture as input for the depth mesh component
- L146 _protected prototype_ `void DestroyDepthMeshComponent();` — Destroys the depth mesh component
- L149 _protected prototype_ `void HandleDepthMeshMaterialCompiled(UMaterialInterface* InMaterialInterface);` — Called when depth mesh material is compiled. Used to invalidate the scene capture components
- L152 _protected prototype_ `void HandleMapChanged(UWorld* InNewWorld, EMapChangeType InMapChangeType);` — Called when level is changed
- L157 _private prototype_ `void CreatePreviewScene();` — Creates the preview scene that will be displayed in the viewport
- L160 _private prototype_ `void CreateSequencerTimeline();` — Creates the sequencer objects
- L163 _private prototype_ `TSharedRef<class FMetaHumanEditorViewportClient> GetMetaHumanEditorViewportClient() const;` — Returns the viewport client as a FMetaHumanEditorViewportClient
- L168 _protected member_ `static const FName TimelineTabId;` — The name of the sequencer tab
- L171 _protected member_ `static const FName PreviewSettingsTabId;` — The name of the preview settings tab
- L176 _protected member_ `FMetaHumanABCommandList ABCommandList;` — The command list with actions to be performed by views A or B
- L179 _protected member_ `TSharedPtr<class FAdvancedPreviewScene> PreviewScene;` — A reference to the preview scene we are seeing in the viewport
- L182 _protected member_ `TObjectPtr<class AActor> PreviewActor;` — The PreviewScene manages the lifetime of this object
- L185 _protected member_ `TObjectPtr<class UMetaHumanDepthMeshComponent> DepthMeshComponent;` — The depth mesh component used to display depth data as a 3D mesh
- L188 _protected member_ `TSharedPtr<class ISequencer> TimelineSequencer;` — The object that represents Sequencer
- L191 _protected member_ `TSharedPtr<class FMetaHumanSequencerPlaybackContext> PlaybackContext;` — The playback context used for sequencer to play audio tracks
- L194 _protected member_ `TObjectPtr<class UMetaHumanSceneSequence> Sequence;` — The Sequence we are currently visualizing in the timeline
- L197 _protected member_ `TObjectPtr<class UMetaHumanMovieSceneMediaTrack> ColourMediaTrack;` — The main colour media track displayed in sequencer
- L200 _protected member_ `TObjectPtr<class UMetaHumanMovieSceneMediaTrack> DepthMediaTrack;` — The main depth media track displayed in sequencer
- L203 _protected member_ `TObjectPtr<class UMovieSceneAudioTrack> AudioMediaTrack;` — The main audio track displayed in sequencer
- L206 _protected member_ `TObjectPtr<class UMediaTexture> ColourMediaTexture;` — The media texture representing the colour track
- L209 _protected member_ `TObjectPtr<class UMediaTexture> DepthMediaTexture;` — The media texture representing the depth track
- L211 _protected member_ `const float InitialFloorOffset = 250.0f;`
- L215 _private prototype_ `void RatchetMovieSceneDisplayRate(FFrameRate InFrameRate);` — Increases the display rate of the movie scene if the supplied rate is higher
- L221 _private prototype_ `void ResetMovieSceneDisplayRate();` — Resets the display rate of the movie scene to a low value, so that the ratcheting function will increase the value as new tracks get added

#### enum `FMetaHumanToolkitBase::EMediaTrackType`  
`enum class EMediaTrackType : uint8`  
_L97-101_
- L99 _public enumerator_ `Colour`
- L100 _public enumerator_ `Depth`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API METAHUMANTOOLKIT_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit/Public/MetaHumanToolkitCommands.h` (Public)


#### class `FMetaHumanToolkitCommands`  
`class FMetaHumanToolkitCommands : public TCommands<FMetaHumanToolkitCommands>`  
_L10-33_
- inherits: `TCommands<FMetaHumanToolkitCommands>`
- desc: Commands used by the base MetaHuman tookit
- L14 _public prototype_ `FMetaHumanToolkitCommands();`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L21 _public member_ `TSharedPtr<FUICommandInfo> ViewMixToSingle;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> ViewMixToWipe;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ViewMixToDual;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ToggleSingleViewToA;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleSingleViewToB;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ToggleRGBChannel;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ToggleCurves;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> ToggleControlVertices;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ToggleDepthMesh;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> ToggleUndistortion;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit/Public/MetaHumanToolkitStyle.h` (Public)


#### class `FMetaHumanToolkitStyle`  
`class FMetaHumanToolkitStyle : public FSlateStyleSet`  
_L9-20_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `static FMetaHumanToolkitStyle& Get();`
- L15 _public prototype_ `static void Register();`
- L16 _public prototype_ `static void Unregister();`
- L19 _private prototype_ `FMetaHumanToolkitStyle();`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API METAHUMANTOOLKIT_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit/Public/SMetaHumanEditorViewport.h` (Public)


#### class `SMetaHumanEditorViewport`  
`class SMetaHumanEditorViewport : public SAssetEditorViewport`  
_L17-71_
- inherits: `SAssetEditorViewport`
- desc: A viewport to manage AB views with the ability to display editable tracker contours as an overlay. This viewport can also display an extra widget at the bottom represented by the Content default slot.
- L22 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanEditorViewport)`
- L25 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<class FMetaHumanEditorViewportClient>, ViewportClient) SLATE_ARGUMENT(FMetaHumanABCommandList, ABCommandList) SLATE_EVENT(FOnGetABMenuContents, OnGetABViewMenuContents) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportConstructionArgs);` — Extra content to display in the bottom of the viewport
- L41 _public prototype_ `TSharedRef<SMetaHumanOverlayWidget<STrackerImageViewer>> GetTrackerImageViewer() const;` — Returns a reference to the STrackerImageViewer we are controlling
- L44 _public prototype_ `virtual void Tick(const FGeometry& InAllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L45 _public prototype_ `virtual void BindCommands() override;`
- L46 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> InOverlay) override;`
- L47 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L48 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InMyGeometry, const FKeyEvent& InKeyEvent) override;`
- L53 _private prototype_ `bool IsShowingCurvesForCurrentView() const;`
- L54 _private prototype_ `bool IsShowingPointsForCurrentView() const;`
- L56 _private prototype_ `TSharedRef<class FMetaHumanEditorViewportClient> GetMetaHumanViewportClient() const;`
- L61 _private member_ `TSharedPtr<SMetaHumanOverlayWidget<STrackerImageViewer>> TrackerImageViewer;` — A reference to the tracker image viewer overlay
- L64 _private member_ `FGeometry CurrentViewportGeometry;` — Holds the current geometry of the widget. Used to trigger the ViewportSizeChangedDelegate if the size changes
- L67 _private member_ `FOnGetABMenuContents OnGetABViewMenuContentsDelegate;` — Triggered to request the context menu for view A and B
- L70 _private member_ `FMetaHumanABCommandList ABCommandList;` — The AB command list used when showing the view menus A and B

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API METAHUMANTOOLKIT_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanToolkit/Public/SMetaHumanEditorViewportToolBar.h` (Public)


#### class `SMetaHumanEditorViewportToolBar`  
`class SMetaHumanEditorViewportToolBar : public SViewportToolBar`  
_L23-98_
- inherits: `SViewportToolBar`
- L27 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanEditorViewportToolBar)`
- L29 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class FUICommandList>, ViewportCommandList) SLATE_ARGUMENT(FMetaHumanABCommandList, ABCommandList) SLATE_ARGUMENT(TSharedPtr<class FMetaHumanEditorViewportClient>, ViewportClient) SLATE_EVENT(FOnGetABMenuContents, OnGetABMenuContents) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L41 _public prototype_ `EVisibility GetShowAVisibility() const;`
- L42 _public prototype_ `EVisibility GetShowBVisibility() const;`
- L45 _private prototype_ `TSharedRef<SWidget> CreateViewMenuWidget(EABImageViewMode InViewMode);`
- L46 _private prototype_ `TSharedRef<SWidget> CreateViewMixToggleWidget();`
- L47 _private prototype_ `TSharedRef<SWidget> CreateABToggleWidget();`
- L48 _private prototype_ `TSharedRef<SWidget> CreateCameraOptionsToolbarButtonWidget();`
- L49 _private prototype_ `TSharedRef<SWidget> FillDisplayOptionsForViewMenu(EABImageViewMode InViewMode);`
- L52 _private function_ `void EnterSingleScreenView()` — View Mix
- L53 _private function_ `void EnterMultiScreenView()`
- L54 _private function_ `void EnterSplitScreenView()`
- L56 _private function_ `bool MultiScreenViewIsChecked() const`
- L57 _private function_ `bool SplitScreenViewIsChecked() const`
- L58 _private function_ `bool SingleViewIsChecked() const`
- L61 _private prototype_ `bool CanChangeFOV() const;` — Field of View options
- L62 _private prototype_ `TOptional<float> GetFOVValue() const;`
- L63 _private prototype_ `void HandleFOVValueChanged(float InNewValue);`
- L66 _private prototype_ `bool CanChangeFootageDepthData() const;` — Depth data
- L67 _private prototype_ `TOptional<float> GetFootageDepthDataNear() const;`
- L68 _private prototype_ `void HandleFootageDepthDataNearChanged(float InNewValue);`
- L69 _private prototype_ `TOptional<float> GetFootageDepthDataFar() const;`
- L70 _private prototype_ `void HandleFootageDepthDataFarChanged(float InNewValue);`
- L74 _private member_ `static const FMargin ToolbarSlotPadding;`
- L76 _private member_ `TSharedPtr<class SHorizontalBox> ToolbarMenuHorizontalBox;`
- L77 _private member_ `TSharedPtr<class FUICommandList> ViewportCommandList;`
- L78 _private member_ `FMetaHumanABCommandList ABCommandList;`
- L79 _private member_ `TSharedPtr<class FMetaHumanEditorViewportClient> ViewportClient;`
- L81 _private member_ `FOnGetABMenuContents OnGetABMenuContentsDelegate;`
- L84 _private prototype_ `FText GetCameraSpeedLabel() const;` — Camera speed Label callback
- L87 _private prototype_ `TSharedRef<SWidget> CreateCameraOptionsDropDownMenuWidget();` — Creates the widget to display the camera controls
- L90 _private member_ `TSharedPtr<class SSlider> CamSpeedSlider;` — Reference to the camera slider used to display current camera speed
- L93 _private member_ `mutable TSharedPtr<SSpinBox<float>> CamSpeedScalarBox;` — Reference to the camera spinbox used to display current camera speed scalar
- L95 _private prototype_ `FText GetABToggleButtonATooltip() const;`
- L96 _private prototype_ `FText GetABToggleButtonBTooltip() const;`
- L97 _private prototype_ `FText GetABToggleButtonTooltip(FText InDefaultTooltipText) const;`

#### class `UMetaHumanEditorViewportViewMenuContext`  
`class UMetaHumanEditorViewportViewMenuContext : public UEditorViewportViewMenuContext`  
_L101-109_
- reflection: `UCLASS()`
- inherits: `UEditorViewportViewMenuContext`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API METAHUMANTOOLKIT_API`
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCamSpeedChanged, int32);` — A delegate that is executed when adding menu content.
- L19 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCamSpeedChanged, int32);` — A delegate that is executed when adding menu content.
- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnCamSpeedScalarChanged, float);`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnCamSpeedScalarChanged, float);`
- L21 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetABMenuContents, EABImageViewMode InABViewMode, FMenuBuilder& InMenuBuilder) class SMetaHumanEditorViewportToolBar : public SViewportToolBar { public: SLATE_BEGIN_ARGS(SMetaHumanEditorViewportToolBar) {} SLATE_ARGUMENT(TSharedPtr<class FUICommandList>, ViewportCommandList) SLATE_ARGUMENT(FMetaHumanABCommandList, ABCommandList) SLATE_ARGUMENT(TSharedPtr<class FMetaHumanEditorViewportClient>, ViewportClient) SLATE_EVENT(FOnGetABMenuContents, OnGetABMenuContents) SLATE_END_ARGS() void Construct(const FArguments& InArgs); EVisibility GetShowAVisibility() const; EVisibility GetShowBVisibility() const; private: TSharedRef<SWidget> CreateViewMenuWidget(EABImageViewMode InViewMode); TSharedRef<SWidget> CreateViewMixToggleWidget(); TSharedRef<SWidget> CreateABToggleWidget(); TSharedRef<SWidget> CreateCameraOptionsToolbarButtonWidget(); TSharedRef<SWidget> FillDisplayOptionsForViewMenu(EABImageViewMode InViewMode); void EnterSingleScreenView() {} void EnterMultiScreenView() {} void EnterSplitScreenView() {} bool MultiScreenViewIsChecked() const { return false; } bool SplitScreenViewIsChecked() const { return false; } bool SingleViewIsChecked() const { return false; }`
