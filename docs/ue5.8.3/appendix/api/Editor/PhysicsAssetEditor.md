# Editor / PhysicsAssetEditor

- module root: `Source/Editor/PhysicsAssetEditor`
- headers: 37; symbols: 1285
- symbol kinds: class=36, delegate=9, enum=4, enumerator=24, externvar=1, function=74, member=365, namespace=1, prototype=742, struct=11, typedef=18
- DynamicallyLoadedModuleNames: MainFrame, MeshUtilities, PropertyEditor
- PrivateDependencyModuleNames: AdvancedPreviewScene, AnimGraph, AnimGraphRuntime, ApplicationCore, Core, CoreUObject, DetailCustomizations, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, Engine, GraphEditor, InputCore, InteractiveToolsFramework, Kismet, LevelEditor, MeshUtilitiesCommon, Persona, PhysicsCore, PhysicsUtilities, PinnedCommandList, RenderCore, SkeletonEditor, Slate, SlateCore, ToolMenus, ToolWidgets, TypedElementRuntime, UnrealEd
- PublicIncludePathModuleNames: Persona, UnrealEd

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetDetailsCustomization.h` (Private)


#### class `FPhysicsAssetDetailsCustomization`  
`class FPhysicsAssetDetailsCustomization : public IDetailCustomization`  
_L17-116_
- inherits: `IDetailCustomization`
- L21 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<FPhysicsAssetEditor> InPhysicsAssetEditor);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public function_ `FPhysicsAssetDetailsCustomization(TWeakPtr<FPhysicsAssetEditor> InPhysicsAssetEditor) : PhysicsAssetEditorPtr(InPhysicsAssetEditor), bIsRenamePending(false)`
- L29 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L32 _private prototype_ `void BindCommands();`
- L34 _private prototype_ `TSharedRef<SWidget> FillPhysicalAnimationProfileOptions();`
- L36 _private prototype_ `TSharedRef<SWidget> FillConstraintProfilesOptions();`
- L38 _private prototype_ `TSharedRef<SWidget> MakePhysicalAnimationProfilesWidget();`
- L40 _private prototype_ `TSharedRef<SWidget> MakeConstraintProfilesWidget();`
- L42 _private prototype_ `TSharedRef<SWidget> CreateProfileButton(const FName& InIconName, TSharedPtr<FUICommandInfo> InCommand);`
- L44 _private prototype_ `void HandlePhysicalAnimationProfileNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L46 _private prototype_ `void HandleConstraintProfileNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L48 _private prototype_ `void ApplyPhysicalAnimationProfile(FName InName);`
- L50 _private prototype_ `void NewPhysicalAnimationProfile();`
- L52 _private prototype_ `bool CanCreateNewPhysicalAnimationProfile() const;`
- L54 _private prototype_ `void DuplicatePhysicalAnimationProfile();`
- L56 _private prototype_ `bool CanDuplicatePhysicalAnimationProfile() const;`
- L58 _private prototype_ `void DeleteCurrentPhysicalAnimationProfile();`
- L60 _private prototype_ `bool CanDeleteCurrentPhysicalAnimationProfile() const;`
- L62 _private prototype_ `void AddBodyToPhysicalAnimationProfile();`
- L64 _private prototype_ `bool CanAddBodyToPhysicalAnimationProfile() const;`
- L66 _private prototype_ `void RemoveBodyFromPhysicalAnimationProfile();`
- L68 _private prototype_ `bool CanRemoveBodyFromPhysicalAnimationProfile() const;`
- L70 _private prototype_ `void SelectAllBodiesInCurrentPhysicalAnimationProfile();`
- L72 _private prototype_ `bool CanSelectAllBodiesInCurrentPhysicalAnimationProfile() const;`
- L74 _private prototype_ `void ApplyConstraintProfile(FName InName);`
- L76 _private prototype_ `bool ConstraintProfileExistsForAny() const;`
- L78 _private prototype_ `void NewConstraintProfile();`
- L80 _private prototype_ `bool CanCreateNewConstraintProfile() const;`
- L82 _private prototype_ `void DuplicateConstraintProfile();`
- L84 _private prototype_ `bool CanDuplicateConstraintProfile() const;`
- L86 _private prototype_ `void DeleteCurrentConstraintProfile();`
- L88 _private prototype_ `bool CanDeleteCurrentConstraintProfile() const;`
- L90 _private prototype_ `void AddConstraintToCurrentConstraintProfile();`
- L92 _private prototype_ `bool CanAddConstraintToCurrentConstraintProfile() const;`
- L94 _private prototype_ `void RemoveConstraintFromCurrentConstraintProfile();`
- L96 _private prototype_ `bool CanRemoveConstraintFromCurrentConstraintProfile() const;`
- L98 _private prototype_ `void SelectAllBodiesInCurrentConstraintProfile();`
- L100 _private prototype_ `bool CanSelectAllBodiesInCurrentConstraintProfile() const;`
- L103 _private member_ `TWeakPtr<FPhysicsAssetEditor> PhysicsAssetEditorPtr;`
- L105 _private member_ `TSharedPtr<IPropertyHandle> PhysicalAnimationProfilesHandle;`
- L107 _private member_ `TSharedPtr<IPropertyHandle> ConstraintProfilesHandle;`
- L109 _private member_ `TSharedPtr<IPropertyHandle> AsyncScenePropertyHandle;`
- L111 _private member_ `TSharedPtr<SEditableTextBox> PhysicalAnimationProfileNameTextBox;`
- L113 _private member_ `TSharedPtr<SEditableTextBox> ConstraintProfileNameTextBox;`
- L115 _private member_ `bool bIsRenamePending;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditor.h` (Private)


#### enum `EPhysicsAssetEditorConstraintType`  
`enum EPhysicsAssetEditorConstraintType`  
_L51-57_
- L53 _public enumerator_ `EPCT_BSJoint`
- L54 _public enumerator_ `EPCT_Hinge`
- L55 _public enumerator_ `EPCT_SkelJoint`
- L56 _public enumerator_ `EPCT_Prismatic`

#### class `FPhysicsAssetEditor`  
`class FPhysicsAssetEditor : public IPhysicsAssetEditor, public FGCObject, public FEditorUndoClient, public FTickableEditorObject`  
_L63-471_
- inherits: `IPhysicsAssetEditor,FGCObject,FEditorUndoClient,FTickableEditorObject`
- L66 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L69 _public prototype_ `virtual ~FPhysicsAssetEditor();` — Destructor
- L72 _public prototype_ `void InitPhysicsAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, UPhysicsAsset* ObjectToEdit);` — Edits the specified PhysicsAsset object
- L75 _public prototype_ `TSharedPtr<FPhysicsAssetEditorSharedData> GetSharedData() const;` — Shared data accessor
- L78 _public prototype_ `void HandleViewportSelectionChanged(const TArray<FPhysicsAssetEditorSelectedElement>& InSelectedElements);` — Handles a group selection change... assigns the proper object to the properties widget and the hierarchy tree view
- L81 _public prototype_ `void RefreshHierarchyTree();` — Repopulates the hierarchy tree view
- L84 _public prototype_ `void RefreshPreviewViewport();` — Refreshes the preview viewport
- L87 _public prototype_ `void BuildMenuWidgetBody(FMenuBuilder& InMenuBuilder);` — Methods for building the various context menus
- L88 _public prototype_ `void BuildMenuWidgetPrimitives(FMenuBuilder& InMenuBuilder);`
- L89 _public prototype_ `void BuildMenuWidgetConstraint(FMenuBuilder& InMenuBuilder);`
- L90 _public prototype_ `void BuildMenuWidgetSelection(FMenuBuilder& InMenuBuilder);`
- L91 _public prototype_ `void BuildMenuWidgetNewConstraint(FMenuBuilder& InMenuBuilder);`
- L92 _public prototype_ `TSharedRef<ISkeletonTree> BuildMenuWidgetNewConstraintForBody(FMenuBuilder& InMenuBuilder, int32 InSourceBodyIndex, SGraphEditor::FActionMenuClosed InOnActionMenuClosed = SGraphEditor::FActionMenuClosed());`
- L93 _public prototype_ `void BuildMenuWidgetBone(FMenuBuilder& InMenuBuilder);`
- L94 _public prototype_ `TSharedRef<SWidget> BuildStaticMeshAssetPicker();`
- L95 _public prototype_ `void AddAdvancedMenuWidget(FMenuBuilder& InMenuBuilder);`
- L98 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L99 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L100 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L101 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L102 _public prototype_ `virtual void InitToolMenuContext(FToolMenuContext& MenuContext) override;`
- L105 _public function_ `virtual FString GetDocumentationLink() const override` — @return the documentation location for this editor
- L111 _public prototype_ `virtual TArray<int32> GetSelectedBodyIndices() const override;` — IPhysicsAssetEditor interface
- L112 _public prototype_ `virtual TArray<int32> GetSelectedConstraintIndices() const override;`
- L114 _public prototype_ `virtual void ModifySelection(EPhysicsAssetEditorSelection ElementType, const TArray<int32>& Indices, bool bAddToSelection) override;`
- L115 _public prototype_ `virtual void ClearSelection() override;`
- L118 _public function_ `virtual TSharedRef<IPersonaToolkit> GetPersonaToolkit() const override` — IHasPersonaToolkit interface
- L119 _public prototype_ `virtual void OnClose() override;`
- L122 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget, int32 ZOrder = INDEX_NONE) override;` — FAssetEditorToolkit interface
- L123 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget> InOverlaidWidget) override;`
- L126 _public prototype_ `void HandleViewportCreated(const TSharedRef<class IPersonaViewport>& InViewport);` — Store the viewport reference for overlay widget forwarding.
- L129 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L130 _public function_ `virtual FString GetReferencerName() const override`
- L136 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L137 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L138 _public prototype_ `virtual TStatId GetStatId() const override;`
- L141 _public prototype_ `void HandleDetailsCreated(const TSharedRef<class IDetailsView>& InDetailsView);`
- L143 _public prototype_ `void HandlePhysicsAssetGraphCreated(const TSharedRef<SPhysicsAssetGraph>& InPhysicsAssetGraph);`
- L145 _public prototype_ `void HandleGraphObjectsSelected(const TArrayView<UObject*>& InObjects);`
- L147 _public prototype_ `void HandleSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);`
- L149 _public prototype_ `void HandleCreateNewConstraint(int32 BodyIndex0, int32 BodyIndex1);`
- L151 _public function_ `TSharedPtr<ISkeletonTree> GetSkeletonTree() const`
- L153 _public prototype_ `void CreateBodiesAndConstraintsForSelectedBones(const EPhysAssetFitGeomType InGeomType, const bool bInShouldCreateConstraints);`
- L154 _public prototype_ `void CreateBodiesAndConstraintsForSelectedBones(const FPhysAssetCreateParams& InBodyData);`
- L157 _public prototype_ `void ResetBoneCollision();` — Reset bone collision for selected or regenerate all bodies if no bodies are selected
- L160 _public prototype_ `bool IsNotSimulation() const;` — Check whether we are out of simulation mode
- L163 _public function_ `TSharedPtr<FUICommandList_Pinnable> GetViewportCommandList() const` — Get the command list used for viewport commands
- L166 _public prototype_ `TSharedRef<SWidget> MakeConstraintScaleWidget();` — Make the constraint scale widget
- L169 _public prototype_ `TSharedRef<SWidget> MakeCoMMarkerScaleWidget();` — Make the Center of Mass marker scale widget
- L172 _public prototype_ `TSharedRef<SWidget> MakeCollisionOpacityWidget();` — Make the collision opacity widget
- L176 _public member_ `FSimpleMulticastDelegate OnPostUndo;` — Delegate fired on undo/redo
- L187 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L188 _private prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L192 _private prototype_ `void OnAssetReimport(UObject* Object);` — Called when an asset has just been imported
- L195 _private prototype_ `void ExtendMenu();` — Builds the menu for the PhysicsAsset editor
- L198 _private prototype_ `void ExtendToolbar();` — Builds the toolbar widget for the PhysicsAsset editor
- L201 _private prototype_ `void ExtendViewportMenus();` — Extends the viewport menus for the PhysicsAsset editor
- L204 _private prototype_ `void BindCommands();` — Binds our UI commands to delegates
- L206 _private prototype_ `void OnAssetSelectedFromStaticMeshAssetPicker(const FAssetData& AssetData);`
- L208 _private prototype_ `TSharedRef<SWidget> BuildPhysicalMaterialAssetPicker(bool bForAllBodies);`
- L210 _private prototype_ `void OnAssetSelectedFromPhysicalMaterialAssetPicker(const FAssetData& AssetData, bool bForAllBodies);`
- L213 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);` — Call back for when bone/body properties are changed
- L216 _private prototype_ `bool ShouldFilterAssetBasedOnSkeleton(const FAssetData& AssetData);` — Helper function for SContentReference which tells it whether a particular asset is valid for the current skeleton
- L219 _private prototype_ `void SnapConstraintToBone(const FPhysicsAssetEditorSharedData::FSelection* Constraint);` — Constraint editing helper methods
- L221 _private prototype_ `void CreateOrConvertConstraint(EPhysicsAssetEditorConstraintType ConstraintType);`
- L224 _private prototype_ `void AddNewPrimitive(EAggCollisionShape::Type PrimitiveType, bool bCopySelected = false);` — Collision editing helper methods
- L225 _private prototype_ `void SetBodiesBelowSelectedPhysicsType( EPhysicsType InPhysicsType, bool bMarkAsDirty);`
- L226 _private prototype_ `void SetBodiesBelowPhysicsType( EPhysicsType InPhysicsType, const TArray<int32> & Indices, bool bMarkAsDirty);`
- L229 _private prototype_ `bool HasSelectedBodyAndIsNotSimulation() const;` — Toolbar/menu command methods
- L230 _private prototype_ `bool HasOneSelectedBodyAndIsNotSimulation() const;`
- L231 _private prototype_ `bool HasMoreThanOneSelectedBodyAndIsNotSimulation() const;`
- L232 _private prototype_ `bool HasSelectedBodyOrConstraintAndIsNotSimulation() const;`
- L233 _private prototype_ `bool CanEditConstraintProperties() const;`
- L234 _private prototype_ `bool HasSelectedConstraintAndIsNotSimulation() const;`
- L235 _private prototype_ `void OnChangeDefaultMesh(USkeletalMesh* OldPreviewMesh, USkeletalMesh* NewPreviewMesh);`
- L236 _private prototype_ `void OnCopyBodies();`
- L237 _private prototype_ `bool IsCopyBodies() const;`
- L238 _private prototype_ `bool CanCopyBodies() const;`
- L239 _private prototype_ `void OnPasteBodies();`
- L240 _private prototype_ `bool CanPasteBodies() const;`
- L241 _private prototype_ `void OnCopyShapes();`
- L242 _private prototype_ `bool CanCopyShapes() const;`
- L243 _private prototype_ `void OnPasteShapes();`
- L244 _private prototype_ `bool CanPasteShapes() const;`
- L245 _private prototype_ `void OnCopyProperties();`
- L246 _private prototype_ `bool IsCopyProperties() const;`
- L247 _private prototype_ `bool CanCopyProperties() const;`
- L248 _private prototype_ `void OnPasteProperties();`
- L249 _private prototype_ `bool CanPasteProperties() const;`
- L250 _private prototype_ `void OnCopyBodyName();`
- L251 _private prototype_ `bool CanCopyBodyName() const;`
- L252 _private prototype_ `bool IsSelectedEditMode() const;`
- L253 _private prototype_ `void OnRepeatLastSimulation();`
- L254 _private prototype_ `void OnToggleSimulation(bool bInSelected);`
- L255 _private prototype_ `void OnToggleSimulationNoGravity();`
- L256 _private prototype_ `bool IsNoGravitySimulationEnabled() const;`
- L257 _private prototype_ `void OnToggleSimulationFloorCollision();`
- L258 _private prototype_ `bool IsSimulationFloorCollisionEnabled() const;`
- L259 _private prototype_ `void SetupSelectedSimulation();`
- L260 _private prototype_ `bool IsFullSimulation() const;`
- L261 _private prototype_ `bool IsSelectedSimulation() const;`
- L262 _private prototype_ `bool IsToggleSimulation() const;`
- L263 _private prototype_ `void OnMeshRenderingMode(EPhysicsAssetEditorMeshViewMode Mode, bool bSimulation);`
- L264 _private prototype_ `bool IsMeshRenderingMode(EPhysicsAssetEditorMeshViewMode Mode, bool bSimulation) const;`
- L265 _private prototype_ `void OnCenterOfMassRenderingMode(EPhysicsAssetEditorCenterOfMassViewMode Mode, bool bSimulation);`
- L266 _private prototype_ `bool IsCenterOfMassRenderingMode(EPhysicsAssetEditorCenterOfMassViewMode Mode, bool bSimulation) const;`
- L267 _private prototype_ `void OnCollisionRenderingMode(EPhysicsAssetEditorCollisionViewMode Mode, bool bSimulation);`
- L268 _private prototype_ `bool IsCollisionRenderingMode(EPhysicsAssetEditorCollisionViewMode Mode, bool bSimulation) const;`
- L269 _private prototype_ `void OnConstraintRenderingMode(EPhysicsAssetEditorConstraintViewMode Mode, bool bSimulation);`
- L270 _private prototype_ `bool IsConstraintRenderingMode(EPhysicsAssetEditorConstraintViewMode Mode, bool bSimulation) const;`
- L271 _private prototype_ `void ToggleDrawConstraintsAsPoints();`
- L272 _private prototype_ `bool IsDrawingConstraintsAsPoints() const;`
- L273 _private prototype_ `void ToggleDrawViolatedLimits();`
- L274 _private prototype_ `bool IsDrawingViolatedLimits() const;`
- L275 _private prototype_ `void ToggleHideCenterOfMassForKinematicBodies();`
- L276 _private prototype_ `bool IsHidingCenterOfMassForKinematicBodies() const;`
- L277 _private prototype_ `void ToggleRenderOnlySelectedConstraints();`
- L278 _private prototype_ `bool IsRenderingOnlySelectedConstraints() const;`
- L279 _private prototype_ `void ToggleRenderOnlySelectedSolid();`
- L280 _private prototype_ `void ToggleHideSimulatedBodies();`
- L281 _private prototype_ `void ToggleHideKinematicBodies();`
- L282 _private prototype_ `void ToggleHighlightOverlappingBodies();`
- L283 _private prototype_ `void ToggleHideBodyMass();`
- L284 _private prototype_ `bool IsRenderingOnlySelectedSolid() const;`
- L285 _private prototype_ `bool IsHidingSimulatedBodies() const;`
- L286 _private prototype_ `bool IsHidingKinematicBodies() const;`
- L287 _private prototype_ `bool IsHighlightOverlappingBodies() const;`
- L288 _private prototype_ `bool IsHidingBodyMass() const;`
- L289 _private prototype_ `bool IsDrawingBodyMass() const;`
- L290 _private prototype_ `void OnToggleMassProperties();`
- L291 _private prototype_ `bool IsToggleMassProperties() const;`
- L292 _private prototype_ `void OnSetCollision(bool bEnable);`
- L293 _private prototype_ `bool CanSetCollision(bool bEnable) const;`
- L294 _private prototype_ `void OnSetCollisionAll(bool bEnable);`
- L295 _private prototype_ `bool CanSetCollisionAll(bool bEnable) const;`
- L296 _private prototype_ `void OnSetPrimitiveCollision(ECollisionEnabled::Type CollisionEnabled);`
- L297 _private prototype_ `bool CanSetPrimitiveCollision(ECollisionEnabled::Type CollisionEnabled) const;`
- L298 _private prototype_ `bool IsPrimitiveCollisionChecked(ECollisionEnabled::Type CollisionEnabled) const;`
- L299 _private prototype_ `void OnSetPrimitiveContributeToMass();`
- L300 _private prototype_ `bool CanSetPrimitiveContributeToMass() const;`
- L301 _private prototype_ `bool GetPrimitiveContributeToMass() const;`
- L302 _private prototype_ `void OnWeldToBody();`
- L303 _private prototype_ `bool CanWeldToBody();`
- L304 _private prototype_ `void OnAddSphere();`
- L305 _private prototype_ `void OnAddSphyl();`
- L306 _private prototype_ `void OnAddBox();`
- L307 _private prototype_ `void OnAddTaperedCapsule();`
- L308 _private prototype_ `bool CanAddPrimitive(EAggCollisionShape::Type InPrimitiveType) const;`
- L309 _private prototype_ `void OnDeletePrimitive();`
- L310 _private prototype_ `void OnDuplicatePrimitive();`
- L311 _private prototype_ `bool CanDuplicatePrimitive() const;`
- L312 _private prototype_ `void OnResetConstraint();`
- L313 _private prototype_ `void OnConstrainChildBodiesToParentBody();`
- L314 _private prototype_ `void OnSnapConstraint(const EConstraintTransformComponentFlags ComponentFlags);`
- L315 _private prototype_ `void OnConvertToBallAndSocket();`
- L316 _private prototype_ `void OnConvertToHinge();`
- L317 _private prototype_ `void OnConvertToPrismatic();`
- L318 _private prototype_ `void OnConvertToSkeletal();`
- L319 _private prototype_ `void OnDeleteConstraint();`
- L320 _private prototype_ `void OnViewType(ELevelViewportType ViewType);`
- L321 _private prototype_ `void OnSetBodyPhysicsType( EPhysicsType InPhysicsType );`
- L322 _private prototype_ `bool IsBodyPhysicsType( EPhysicsType InPhysicsType );`
- L323 _private prototype_ `void OnDeleteBody();`
- L324 _private prototype_ `void OnDeleteAllBodiesBelow();`
- L325 _private prototype_ `void OnDeleteSelection();`
- L326 _private prototype_ `void OnCycleConstraintOrientation();`
- L327 _private prototype_ `void OnCycleConstraintActive();`
- L328 _private prototype_ `void OnToggleSwing1();`
- L329 _private prototype_ `void OnToggleSwing2();`
- L330 _private prototype_ `void OnToggleTwist();`
- L331 _private prototype_ `bool IsSwing1Locked() const;`
- L332 _private prototype_ `bool IsSwing2Locked() const;`
- L333 _private prototype_ `bool IsTwistLocked() const;`
- L335 _private prototype_ `void Mirror();`
- L338 _private prototype_ `void OnSelectAllBodies();` — menu commands
- L339 _private prototype_ `void OnSelectKinematicBodies();`
- L340 _private prototype_ `void OnSelectSimulatedBodies();`
- L341 _private prototype_ `void OnSelectBodies(EPhysicsType PhysicsType = EPhysicsType::PhysType_Simulated);`
- L342 _private prototype_ `void OnSelectShapes(const ECollisionEnabled::Type CollisionEnabled);`
- L343 _private prototype_ `void OnSelectAllConstraints();`
- L344 _private prototype_ `void OnToggleCreateConstraintsWhenCreatingBodies();`
- L345 _private prototype_ `void OnToggleSelectionType(bool bIgnoreUserConstraints);`
- L346 _private prototype_ `void OnToggleShowSelected();`
- L347 _private prototype_ `void OnShowSelected();`
- L348 _private prototype_ `void OnHideSelected();`
- L349 _private prototype_ `void OnToggleShowOnlyColliding();`
- L350 _private prototype_ `void OnToggleShowOnlyConstrained();`
- L351 _private prototype_ `void OnToggleShowOnlySelected();`
- L352 _private prototype_ `void OnShowAll();`
- L353 _private prototype_ `void OnHideAll();`
- L354 _private prototype_ `void OnDeselectAll();`
- L355 _private prototype_ `bool LoadMLLevelSetFromDataTable(UDataTable* DataTableMLLevelSetModelBoneBinningInfo, TArray<FString>& ErrorMessages);`
- L356 _private prototype_ `void ImportMLLevelSetFromDataTable();`
- L358 _private prototype_ `bool ShouldCreateConstraintsWhenCreatingBodies() const;`
- L360 _private prototype_ `void GenerateSkinnedTriangleMesh();`
- L362 _private prototype_ `FText GetRepeatLastSimulationToolTip() const;`
- L363 _private prototype_ `FSlateIcon GetRepeatLastSimulationIcon() const;`
- L366 _private prototype_ `void BuildMenuWidgetBone(FMenuBuilder& InMenuBuilder, const TArray<TSharedPtr<ISkeletonTreeItem>>& SelectedBones);` — Add skeleton tree context menu entries specific to the currently selected set of bones.
- L369 _private prototype_ `void HandlePreviewSceneCreated(const TSharedRef<IPersonaPreviewScene>& InPersonaPreviewScene);` — Handle initial preview scene setup
- L372 _private prototype_ `void HandleOnPreviewSceneSettingsCustomized(IDetailLayoutBuilder& DetailBuilder) const;` — Handle customization of Preview Scene Settings details
- L375 _private prototype_ `void HandleExtendContextMenu(FMenuBuilder& InMenuBuilder);` — Build context menu for tree items
- L378 _private prototype_ `void HandleExtendFilterMenu(FMenuBuilder& InMenuBuilder);` — Extend the filter menu
- L381 _private prototype_ `void HandleToggleShowBodies();` — Filter menu toggles
- L382 _private prototype_ `void HandleToggleShowSimulatedBodies();`
- L383 _private prototype_ `void HandleToggleShowKinematicBodies();`
- L384 _private prototype_ `void HandleToggleShowConstraints();`
- L385 _private prototype_ `void HandleToggleShowConstraintsOnParentBodies();`
- L386 _private prototype_ `void HandleToggleShowCrossConstraints();`
- L387 _private prototype_ `void HandleToggleShowParentChildConstraints();`
- L388 _private prototype_ `void HandleToggleShowPrimitives();`
- L389 _private prototype_ `ECheckBoxState GetShowBodiesChecked() const;`
- L390 _private prototype_ `ECheckBoxState GetShowSimulatedBodiesChecked() const;`
- L391 _private prototype_ `ECheckBoxState GetShowKinematicBodiesChecked() const;`
- L392 _private prototype_ `ECheckBoxState GetShowConstraintsChecked() const;`
- L393 _private prototype_ `ECheckBoxState GetShowConstraintsOnParentBodiesChecked() const;`
- L394 _private prototype_ `ECheckBoxState GetShowCrossConstraintsChecked() const;`
- L395 _private prototype_ `ECheckBoxState GetShowParentChildConstraintsChecked() const;`
- L396 _private prototype_ `ECheckBoxState GetShowPrimitivesChecked() const;`
- L397 _private prototype_ `bool IsShowBodiesChecked() const;`
- L398 _private prototype_ `bool IsShowConstraintsChecked() const;`
- L401 _private prototype_ `void HandleGetFilterLabel(TArray<FText>& InOutItems) const;` — Customize the filter label
- L404 _private prototype_ `void RefreshFilter();` — refresh filter after changing filter settings
- L407 _private prototype_ `void RecreatePhysicsState();` — Invalidate convex meshes and recreate the physics state. Performed on property changes (etc)
- L410 _private prototype_ `void ShowNotificationMessage(const FText& Message, const SNotificationItem::ECompletionState CompletionState);` — show a notification message
- L413 _private prototype_ `template<typename TValueAccessor> TSharedRef<SWidget> MakeScaleWidget(const float MinValue, const float MaxValue, TValueAccessor ValueAccessorFunction, const FName WidgetInteractionText);` — Helper function for creating Scale Widgets
- L417 _private member_ `TSharedPtr<class IDetailsView> PhysAssetProperties;` — Physics asset properties tab
- L420 _private member_ `TSharedPtr<FPhysicsAssetEditorSharedData> SharedData;` — Data and methods shared across multiple classes
- L423 _private member_ `TSharedPtr<FExtender> ToolbarExtender;` — Toolbar extender - used repeatedly as the body/constraints mode will remove/add this when changed
- L426 _private member_ `TSharedPtr<FExtender> MenuExtender;` — Menu extender - used for commands like Select All
- L429 _private member_ `bool bSelecting;` — True if in OnTreeSelectionChanged()... protects against infinite recursion
- L432 _private member_ `bool SelectedSimulation;` — True if we want to only simulate from selected body/constraint down
- L435 _private member_ `TArray<EPhysicsType> PhysicsTypeState;` — Used to keep track of the physics type before using Selected Simulation
- L438 _private member_ `TSharedPtr<ISkeletonTree> SkeletonTree;` — The skeleton tree widget
- L441 _private member_ `TSharedPtr<FPhysicsAssetEditorSkeletonTreeBuilder> SkeletonTreeBuilder;` — The skeleton tree builder
- L444 _private member_ `TSharedPtr<IPersonaToolkit> PersonaToolkit;` — The persona toolkit
- L447 _private member_ `TSharedPtr<class IPersonaViewport> Viewport;` — Viewport for overlay widget forwarding
- L450 _private member_ `TWeakPtr<SPhysicsAssetGraph> PhysicsAssetGraph;` — The current physics asset graph, if any
- L453 _private member_ `TSharedPtr<FUICommandList_Pinnable> SkeletonTreeCommandList;` — Command list for skeleton tree operations
- L456 _private member_ `TSharedPtr<FUICommandList_Pinnable> ViewportCommandList;` — Command list for viewport operations
- L459 _private member_ `FDelegateHandle OnAssetReimportDelegateHandle;` — To unregister reimport handler
- L461 _private prototype_ `void FixPhysicsState();`
- L462 _private prototype_ `void ImpToggleSimulation();`
- L465 _private prototype_ `void OnAddPhatRecord(const FString& Action, bool bRecordSimulate, bool bRecordMode);` — Records PhysicsAssetEditor related data - simulating or mode change
- L469 _public member_ `TArray<int32> HiddenBodies;`
- L470 _public member_ `TArray<int32> HiddenConstraints;`

#### enum `FPhysicsAssetEditor::EPhatHierarchyFilterMode`  
`enum EPhatHierarchyFilterMode`  
_L180-184_
- L182 _public enumerator_ `PHFM_All`
- L183 _public enumerator_ `PHFM_Bodies`

#### Free symbols / members of external scopes

- L46 _namespace_ `namespace PhysicsAssetEditorModes`
- L48 _externvar_ `extern const FName PhysicsAssetEditorMode;` (scope `PhysicsAssetEditorModes`)

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorActions.h` (Private)


#### class `FPhysicsAssetEditorCommands`  
`class FPhysicsAssetEditorCommands : public TCommands<FPhysicsAssetEditorCommands>`  
_L18-185_
- inherits: `TCommands<FPhysicsAssetEditorCommands>`
- L22 _public function_ `FPhysicsAssetEditorCommands() : TCommands<FPhysicsAssetEditorCommands>("PhysicsAssetEditor", NSLOCTEXT("Contexts", "PhysicsAssetEditor", "PhysicsAssetEditor"), NAME_None, FAppStyle::GetAppStyleSetName())` — Constructor
- L29 _public member_ `TSharedPtr<FUICommandInfo> RegenerateBodies;`
- L30 _public member_ `TSharedPtr<FUICommandInfo> CreateBodies;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> CreateBodyWithSphere;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> CreateBodyWithSphyl;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> CreateBodyWithBox;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> CreateBodyWithSingleConvex;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> CreateBodyWithMultiConvex;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> CreateBodyWithTaperedCapsule;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> CreateBodyShouldCreateConstraints;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> CreateOrRegenerateBodies;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> ApplyPhysicalMaterial;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> Snap;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> CopyBodies;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> PasteBodies;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> CopyShapes;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> PasteShapes;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> CopyProperties;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> PasteProperties;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> CopyBodyName;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> RepeatLastSimulation;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> SimulationNoGravity;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> SimulationFloorCollision;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> SelectedSimulation;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> SimulationAll;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Solid;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Wireframe;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_None;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> CenterOfMassRenderingMode_All;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> CenterOfMassRenderingMode_Selected;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> CenterOfMassRenderingMode_None;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Solid;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Wireframe;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_SolidWireframe;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_None;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_None;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_AllPositions;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_AllLimits;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Simulation_Solid;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Simulation_Wireframe;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> MeshRenderingMode_Simulation_None;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> CenterOfMassRenderingMode_Simulation_All;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> CenterOfMassRenderingMode_Simulation_Selected;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> CenterOfMassRenderingMode_Simulation_None;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_Solid;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_Wireframe;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_SolidWireframe;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> CollisionRenderingMode_Simulation_None;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_Simulation_None;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_Simulation_AllPositions;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> ConstraintRenderingMode_Simulation_AllLimits;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> RenderOnlySelectedSolid;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> HideSimulatedBodies;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> HideKinematicBodies;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> HighlightOverlappingBodies;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> DrawBodyMass;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> DrawCenterOfMass;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> HideCenterOfMassForKinematicBodies;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> RenderOnlySelectedBodyCoMs;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> RenderOnlySelectedConstraints;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> DrawConstraintsAsPoints;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> DrawViolatedLimits;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> DisableCollision;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> DisableCollisionAll;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> EnableCollision;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> EnableCollisionAll;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> PrimitiveQueryAndPhysics;`
- L95 _public member_ `TSharedPtr<FUICommandInfo> PrimitiveQueryAndProbe;`
- L96 _public member_ `TSharedPtr<FUICommandInfo> PrimitiveQueryOnly;`
- L97 _public member_ `TSharedPtr<FUICommandInfo> PrimitivePhysicsOnly;`
- L98 _public member_ `TSharedPtr<FUICommandInfo> PrimitiveProbeOnly;`
- L99 _public member_ `TSharedPtr<FUICommandInfo> PrimitiveNoCollision;`
- L100 _public member_ `TSharedPtr<FUICommandInfo> PrimitiveContributeToMass;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> WeldToBody;`
- L102 _public member_ `TSharedPtr<FUICommandInfo> AddSphere;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> AddSphyl;`
- L104 _public member_ `TSharedPtr<FUICommandInfo> AddBox;`
- L105 _public member_ `TSharedPtr<FUICommandInfo> AddTaperedCapsule;`
- L106 _public member_ `TSharedPtr<FUICommandInfo> DeletePrimitive;`
- L107 _public member_ `TSharedPtr<FUICommandInfo> DuplicatePrimitive;`
- L108 _public member_ `TSharedPtr<FUICommandInfo> ConstrainChildBodiesToParentBody;`
- L109 _public member_ `TSharedPtr<FUICommandInfo> ResetConstraint;`
- L110 _public member_ `TSharedPtr<FUICommandInfo> SnapConstraint;`
- L111 _public member_ `TSharedPtr<FUICommandInfo> SnapConstraintChildPosition;`
- L112 _public member_ `TSharedPtr<FUICommandInfo> SnapConstraintChildOrientation;`
- L113 _public member_ `TSharedPtr<FUICommandInfo> SnapConstraintParentPosition;`
- L114 _public member_ `TSharedPtr<FUICommandInfo> SnapConstraintParentOrientation;`
- L115 _public member_ `TSharedPtr<FUICommandInfo> ConvertToBallAndSocket;`
- L116 _public member_ `TSharedPtr<FUICommandInfo> ConvertToHinge;`
- L117 _public member_ `TSharedPtr<FUICommandInfo> ConvertToPrismatic;`
- L118 _public member_ `TSharedPtr<FUICommandInfo> ConvertToSkeletal;`
- L119 _public member_ `TSharedPtr<FUICommandInfo> DeleteConstraint;`
- L120 _public member_ `TSharedPtr<FUICommandInfo> ShowSkeleton;`
- L121 _public member_ `TSharedPtr<FUICommandInfo> MakeBodyKinematic;`
- L122 _public member_ `TSharedPtr<FUICommandInfo> MakeBodySimulated;`
- L123 _public member_ `TSharedPtr<FUICommandInfo> MakeBodyDefault;`
- L124 _public member_ `TSharedPtr<FUICommandInfo> KinematicAllBodiesBelow;`
- L125 _public member_ `TSharedPtr<FUICommandInfo> SimulatedAllBodiesBelow;`
- L126 _public member_ `TSharedPtr<FUICommandInfo> MakeAllBodiesBelowDefault;`
- L127 _public member_ `TSharedPtr<FUICommandInfo> DeleteBody;`
- L128 _public member_ `TSharedPtr<FUICommandInfo> DeleteAllBodiesBelow;`
- L129 _public member_ `TSharedPtr<FUICommandInfo> SelectAllBodies;`
- L130 _public member_ `TSharedPtr<FUICommandInfo> SelectSimulatedBodies;`
- L131 _public member_ `TSharedPtr<FUICommandInfo> SelectKinematicBodies;`
- L132 _public member_ `TSharedPtr<FUICommandInfo> SelectShapesQueryOnly;`
- L133 _public member_ `TSharedPtr<FUICommandInfo> SelectShapesQueryAndPhysics;`
- L134 _public member_ `TSharedPtr<FUICommandInfo> SelectShapesPhysicsOnly;`
- L135 _public member_ `TSharedPtr<FUICommandInfo> SelectShapesQueryAndProbe;`
- L136 _public member_ `TSharedPtr<FUICommandInfo> SelectShapesProbeOnly;`
- L137 _public member_ `TSharedPtr<FUICommandInfo> ImportMLLevelSet;`
- L138 _public member_ `TSharedPtr<FUICommandInfo> GenerateSkinnedTriangleMesh;`
- L139 _public member_ `TSharedPtr<FUICommandInfo> SelectAllConstraints;`
- L140 _public member_ `TSharedPtr<FUICommandInfo> ToggleSelectionType;`
- L141 _public member_ `TSharedPtr<FUICommandInfo> ToggleSelectionTypeWithUserConstraints;`
- L142 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowSelected;`
- L143 _public member_ `TSharedPtr<FUICommandInfo> ShowSelected;`
- L144 _public member_ `TSharedPtr<FUICommandInfo> HideSelected;`
- L145 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowOnlyColliding;`
- L146 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowOnlyConstrained;`
- L147 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowOnlySelected;`
- L148 _public member_ `TSharedPtr<FUICommandInfo> ShowAll;`
- L149 _public member_ `TSharedPtr<FUICommandInfo> HideAll;`
- L150 _public member_ `TSharedPtr<FUICommandInfo> DeselectAll;`
- L151 _public member_ `TSharedPtr<FUICommandInfo> Mirror;`
- L152 _public member_ `TSharedPtr<FUICommandInfo> NewPhysicalAnimationProfile;`
- L153 _public member_ `TSharedPtr<FUICommandInfo> DuplicatePhysicalAnimationProfile;`
- L154 _public member_ `TSharedPtr<FUICommandInfo> DeleteCurrentPhysicalAnimationProfile;`
- L155 _public member_ `TSharedPtr<FUICommandInfo> AddBodyToPhysicalAnimationProfile;`
- L156 _public member_ `TSharedPtr<FUICommandInfo> RemoveBodyFromPhysicalAnimationProfile;`
- L157 _public member_ `TSharedPtr<FUICommandInfo> SelectAllBodiesInCurrentPhysicalAnimationProfile;`
- L158 _public member_ `TSharedPtr<FUICommandInfo> NewConstraintProfile;`
- L159 _public member_ `TSharedPtr<FUICommandInfo> DuplicateConstraintProfile;`
- L160 _public member_ `TSharedPtr<FUICommandInfo> DeleteCurrentConstraintProfile;`
- L161 _public member_ `TSharedPtr<FUICommandInfo> AddConstraintToCurrentConstraintProfile;`
- L162 _public member_ `TSharedPtr<FUICommandInfo> RemoveConstraintFromCurrentConstraintProfile;`
- L163 _public member_ `TSharedPtr<FUICommandInfo> SelectAllBodiesInCurrentConstraintProfile;`
- L164 _public member_ `TSharedPtr<FUICommandInfo> ShowBodies;`
- L165 _public member_ `TSharedPtr<FUICommandInfo> ShowSimulatedBodies;`
- L166 _public member_ `TSharedPtr<FUICommandInfo> ShowKinematicBodies;`
- L167 _public member_ `TSharedPtr<FUICommandInfo> ShowConstraints;`
- L168 _public member_ `TSharedPtr<FUICommandInfo> ShowConstraintsOnParentBodies;`
- L169 _public member_ `TSharedPtr<FUICommandInfo> ShowCrossConstraints;`
- L170 _public member_ `TSharedPtr<FUICommandInfo> ShowParentChildConstraints;`
- L171 _public member_ `TSharedPtr<FUICommandInfo> ShowPrimitives;`
- L174 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelected;` — Hotkey only commands
- L175 _public member_ `TSharedPtr<FUICommandInfo> CycleConstraintOrientation;`
- L176 _public member_ `TSharedPtr<FUICommandInfo> CycleConstraintActive;`
- L177 _public member_ `TSharedPtr<FUICommandInfo> ToggleSwing1;`
- L178 _public member_ `TSharedPtr<FUICommandInfo> ToggleSwing2;`
- L179 _public member_ `TSharedPtr<FUICommandInfo> ToggleTwist;`
- L180 _public member_ `TSharedPtr<FUICommandInfo> FocusOnSelection;`
- L184 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorAnimInstance.h` (Private)


#### class `UPhysicsAssetEditorAnimInstance`  
`class UPhysicsAssetEditorAnimInstance : public UAnimPreviewInstance`  
_L16-28_
- reflection: `UCLASS(transient, NotBlueprintable)`
- inherits: `UAnimPreviewInstance`
- L20 _private prototype_ `virtual void Grab(FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained);`
- L21 _private prototype_ `virtual void Ungrab();`
- L22 _private prototype_ `virtual void UpdateHandleTransform(const FTransform& NewTransform);`
- L23 _private prototype_ `virtual void UpdateDriveSettings(bool bLinearSoft, float LinearStiffness, float LinearDamping);`
- L24 _private prototype_ `virtual void CreateSimulationFloor(FBodyInstance* FloorBodyInstance, const FTransform& Transform);`
- L27 _protected prototype_ `virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorAnimInstanceProxy.h` (Private)


#### struct `FPhysicsAssetEditorAnimInstanceProxy`  
`struct FPhysicsAssetEditorAnimInstanceProxy : public FAnimPreviewInstanceProxy`  
_L18-57_
- reflection: `USTRUCT()`
- inherits: `FAnimPreviewInstanceProxy`
- desc: Proxy override for this UAnimInstance-derived class
- L23 _public prototype_ `FPhysicsAssetEditorAnimInstanceProxy();`
- L25 _public prototype_ `FPhysicsAssetEditorAnimInstanceProxy(UAnimInstance* InAnimInstance);`
- L27 _public prototype_ `virtual ~FPhysicsAssetEditorAnimInstanceProxy();`
- L29 _public prototype_ `virtual void Initialize(UAnimInstance* InAnimInstance) override;`
- L30 _public prototype_ `virtual FAnimNode_Base* GetCustomRootNode() override;`
- L31 _public prototype_ `virtual void GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes) override;`
- L33 _public prototype_ `virtual void UpdateAnimationNode(const FAnimationUpdateContext& InContext) override;`
- L34 _public prototype_ `virtual bool Evaluate_WithRoot(FPoseContext& Output, FAnimNode_Base* InRootNode) override;`
- L36 _public prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None) override;`
- L38 _public prototype_ `virtual void Grab(FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained);`
- L39 _public prototype_ `virtual void Ungrab();`
- L40 _public prototype_ `virtual void UpdateHandleTransform(const FTransform& NewTransform);`
- L41 _public prototype_ `virtual void UpdateDriveSettings(bool bLinearSoft, float LinearStiffness, float LinearDamping);`
- L42 _public prototype_ `virtual void CreateSimulationFloor(FBodyInstance* FloorBodyInstance, const FTransform& Transform);`
- L43 _public prototype_ `virtual void DestroySimulationFloor();`
- L46 _private prototype_ `void ConstructNodes();`
- L48 _private member_ `FAnimNode_RigidBody RagdollNode;`
- L49 _private member_ `FAnimNode_ConvertComponentToLocalSpace ComponentToLocalSpace;`
- L50 _private member_ `FPhysicsAssetSolverSettings SolverSettings;`
- L51 _private member_ `FSolverIterations SolverIterations;`
- L53 _private member_ `ImmediatePhysics::FActorHandle* TargetActor;`
- L54 _private member_ `ImmediatePhysics::FActorHandle* HandleActor;`
- L55 _private member_ `ImmediatePhysics::FJointHandle* HandleJoint;`
- L56 _private member_ `ImmediatePhysics::FActorHandle* FloorActor;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorBodySetupDetailsCustomization.h` (Private)


#### class `FPhysicsAssetEditorBodySetupDetailsCustomization`  
`class FPhysicsAssetEditorBodySetupDetailsCustomization : public FBodySetupDetails`  
_L24-44_
- inherits: `FBodySetupDetails`
- desc: Class FPhysicsAssetEditorBodySetupDetailsCustomization Replaces the base BodySetupDetails customization, adding support for Center of Mass (CoM) offset editing tools to the details panel.
- L28 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L30 _public prototype_ `FPhysicsAssetEditorBodySetupDetailsCustomization();`
- L33 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface
- L35 _public prototype_ `virtual void CustomizeCoMNudge(IDetailLayoutBuilder& DetailBuilder, TSharedRef<IPropertyHandle> BodyInstanceHandler) override;`
- L36 _public prototype_ `FReply ToggleFixCOMInComponentSpace(const EAxis::Type Axis);`
- L37 _public prototype_ `bool IsCOMAxisFixedInComponentSpace(const EAxis::Type Axis) const;`
- L38 _public prototype_ `void SetCoMAxisFixedInComponentSpace(const EAxis::Type Axis, const bool bCoMFixed) const;`
- L42 _private member_ `FPhysicsAssetEditorSharedData* SharedData;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorEditMode.h` (Private)


#### class `FPhysicsAssetEditorEditMode`  
`class FPhysicsAssetEditorEditMode : public IPersonaEditMode`  
_L20-136_
- inherits: `IPersonaEditMode`
- L23 _public member_ `static FName ModeName;`
- L25 _public prototype_ `FPhysicsAssetEditorEditMode();`
- L28 _public function_ `void SetSharedData(const TSharedRef<FPhysicsAssetEditor>& InPhysicsAssetEditor, FPhysicsAssetEditorSharedData& InSharedData)` — Set shared data
- L31 _public prototype_ `virtual bool GetCameraTarget(FSphere& OutTarget) const override;` — IPersonaEditMode interface
- L32 _public prototype_ `virtual class IPersonaPreviewScene& GetAnimPreviewScene() const override;`
- L33 _public prototype_ `virtual void GetOnScreenDebugInfo(TArray<FText>& OutDebugInfo) const override;`
- L36 _public prototype_ `virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — FEdMode interface
- L37 _public prototype_ `virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;`
- L38 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L39 _public prototype_ `virtual bool InputAxis(FEditorViewportClient* InViewportClient, FViewport* Viewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime) override;`
- L40 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L41 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime) override;`
- L42 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L43 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L44 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L45 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L46 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L47 _public prototype_ `virtual bool UsesTransformWidget(UE::Widget::EWidgetMode CheckMode) const override;`
- L48 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L49 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L50 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L51 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;`
- L52 _public function_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override`
- L53 _public prototype_ `virtual bool ReceivedFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport);`
- L54 _public prototype_ `virtual bool LostFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport);`
- L55 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L56 _public prototype_ `virtual void Enter() override;`
- L57 _public prototype_ `virtual void Exit() override;`
- L60 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;` — Start IGizmoEdModeInterface overrides
- L61 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L65 _public function_ `FPhysicsAssetEditorSharedData* GetSharedData() const` — Accessor for shared data, used by UPhysicsAssetSimInteraction.
- L69 _private prototype_ `bool SimMousePress(FEditorViewportClient* InViewportClient, FKey Key);` — Simulation mouse forces
- L70 _private prototype_ `void SimMouseMove(FEditorViewportClient* InViewportClient, float DeltaX, float DeltaY);`
- L71 _private prototype_ `bool SimMouseRelease();`
- L72 _private prototype_ `bool SimMouseWheelUp(FEditorViewportClient* InViewportClient);`
- L73 _private prototype_ `bool SimMouseWheelDown(FEditorViewportClient* InViewportClient);`
- L76 _private prototype_ `void CycleSelectedConstraintOrientation();` — Changes the orientation of a constraint
- L79 _private prototype_ `void ModifyPrimitiveSize(int32 BodyIndex, EAggCollisionShape::Type PrimType, int32 PrimIndex, FVector DeltaSize);` — Scales a collision body
- L82 _private prototype_ `bool IsGroupSelectionActive() const;` — Returns true if input events should be considered part of a group selection operation.
- L85 _private prototype_ `void HitNothing(FEditorViewportClient* InViewportClient, const bool bGroupSelect = false);` — Called when no scene proxy is hit, deselects everything
- L87 _private prototype_ `void CycleTransformMode();`
- L89 _private prototype_ `void OpenBodyMenu(FEditorViewportClient* InViewportClient);`
- L91 _private prototype_ `void OpenConstraintMenu(FEditorViewportClient* InViewportClient);`
- L93 _private prototype_ `void OpenSelectionMenu(FEditorViewportClient* InViewportClient);`
- L96 _private prototype_ `EConstraintFrame::Type GetConstraintFrameForWidget() const;` — Returns the identifier for the constraint frame (child or parent) in which the manipulator widget should be drawn.
- L99 _private prototype_ `bool HandleBeginTransform();` — Manage the start and end of a transform action in the viewport.
- L100 _private prototype_ `bool HandleEndTransform(FEditorViewportClient* InViewportClient) const;`
- L104 _private member_ `FPhysicsAssetEditorSharedData* SharedData;` — Shared data
- L107 _private member_ `UFont* PhysicsAssetEditorFont;` — Font used for drawing debug text to the viewport
- L110 _private member_ `const float MinPrimSize;` — Misc consts
- L111 _private member_ `const float PhysicsAssetEditor_TranslateSpeed;`
- L112 _private member_ `const float PhysicsAssetEditor_RotateSpeed;`
- L113 _private member_ `const float PhysicsAssetEditor_LightRotSpeed;`
- L114 _private member_ `const float SimHoldDistanceChangeDelta;`
- L115 _private member_ `const float SimMinHoldDistance;`
- L116 _private member_ `const float SimGrabMoveSpeed;`
- L119 _private member_ `float SimGrabPush;` — Simulation mouse forces
- L120 _private member_ `float SimGrabMinPush;`
- L121 _private member_ `FVector SimGrabLocation;`
- L122 _private member_ `FVector SimGrabX;`
- L123 _private member_ `FVector SimGrabY;`
- L124 _private member_ `FVector SimGrabZ;`
- L127 _private member_ `TArray<FTransform> ManConTM;` — Members used for interacting with the asset while the simulation is running
- L128 _private member_ `TArray<FTransform> StartManRelConTM;`
- L129 _private member_ `TArray<FTransform> StartManParentConTM;`
- L130 _private member_ `TArray<FTransform> StartManChildConTM;`
- L132 _private member_ `float DragX;`
- L133 _private member_ `float DragY;`
- L135 _private member_ `TWeakPtr<FPhysicsAssetEditor> PhysicsAssetEditorPtr;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorHitProxies.h` (Private)


#### struct `HPhysicsAssetEditorEdBoneProxy`  
`struct HPhysicsAssetEditorEdBoneProxy : public HHitProxy`  
_L14-37_
- inherits: `HHitProxy`
- L16 _public prototype_ `DECLARE_HIT_PROXY();`
- L18 _public member_ `int32 BodyIndex;`
- L19 _public member_ `EAggCollisionShape::Type PrimType;`
- L20 _public member_ `int32 PrimIndex;`
- L22 _public function_ `HPhysicsAssetEditorEdBoneProxy(int32 InBodyIndex, EAggCollisionShape::Type InPrimType, int32 InPrimIndex) : HHitProxy(HPP_World) , BodyIndex(InBodyIndex) , PrimType(InPrimType) , PrimIndex(InPrimIndex)`
- L28 _public function_ `virtual EMouseCursor::Type GetMouseCursor()`
- L33 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

#### struct `HPhysicsAssetEditorEdCoMProxy`  
`struct HPhysicsAssetEditorEdCoMProxy : public HHitProxy`  
_L39-59_
- inherits: `HHitProxy`
- L41 _public prototype_ `DECLARE_HIT_PROXY();`
- L43 _public member_ `int32 BodyIndex;`
- L45 _public function_ `HPhysicsAssetEditorEdCoMProxy(const int32 InBodyIndex) : HHitProxy(HPP_World) , BodyIndex(InBodyIndex)`
- L50 _public function_ `virtual EMouseCursor::Type GetMouseCursor()`
- L55 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

#### struct `HPhysicsAssetEditorEdConstraintProxy`  
`struct HPhysicsAssetEditorEdConstraintProxy : public HHitProxy`  
_L61-80_
- inherits: `HHitProxy`
- L63 _public prototype_ `DECLARE_HIT_PROXY();`
- L65 _public member_ `int32 ConstraintIndex;`
- L67 _public function_ `HPhysicsAssetEditorEdConstraintProxy(int32 InConstraintIndex) : HHitProxy(HPP_Foreground) , ConstraintIndex(InConstraintIndex)`
- L71 _public function_ `virtual EMouseCursor::Type GetMouseCursor()`
- L76 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

#### struct `HPhysicsAssetEditorEdBoneNameProxy`  
`struct HPhysicsAssetEditorEdBoneNameProxy : public HHitProxy`  
_L82-96_
- inherits: `HHitProxy`
- L84 _public prototype_ `DECLARE_HIT_PROXY();`
- L86 _public member_ `int32 BoneIndex;`
- L88 _public function_ `HPhysicsAssetEditorEdBoneNameProxy(int32 InBoneIndex) : HHitProxy(HPP_Foreground) , BoneIndex(InBoneIndex)`
- L92 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorMode.h` (Private)


#### class `FPhysicsAssetEditorMode`  
`class FPhysicsAssetEditorMode : public FApplicationMode`  
_L11-25_
- inherits: `FApplicationMode`
- L14 _public prototype_ `FPhysicsAssetEditorMode(TSharedRef<class FWorkflowCentricApplication> InHostingApp, TSharedRef<class ISkeletonTree> InSkeletonTree, TSharedRef<class IPersonaPreviewScene> InPreviewScene);`
- L17 _public prototype_ `virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;` — FApplicationMode interface
- L21 _protected member_ `TWeakPtr<FPhysicsAssetEditor> PhysicsAssetEditorPtr;` — The hosting app
- L24 _protected member_ `FWorkflowAllowedTabSet TabFactories;` — The tab factories we support

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorPhysicsHandleComponent.h` (Private)


#### class `UPhysicsAssetEditorPhysicsHandleComponent`  
`class UPhysicsAssetEditorPhysicsHandleComponent : public UPhysicsHandleComponent`  
_L13-28_
- reflection: `UCLASS()`
- inherits: `UPhysicsHandleComponent`
- desc: Extend the Physics Handle for PhAt. This adds support for manipulating the physics if it is running in a RigidBody AnimNode (which is always is with Chaos at the moment).
- L17 _private member_ `bool bAnimInstanceMode;`
- L20 _public prototype_ `void SetAnimInstanceMode(bool bInAnimInstanceMode);`
- L22 _public prototype_ `virtual void ReleaseComponent() override;`
- L25 _protected prototype_ `virtual void UpdateHandleTransform(const FTransform& NewTransform) override;`
- L26 _protected prototype_ `virtual void UpdateDriveSettings() override;`
- L27 _protected prototype_ `virtual void GrabComponentImp(class UPrimitiveComponent* Component, FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained) override;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorProfilesSummoner.h` (Private)


#### struct `FPhysicsAssetEditorProfilesSummoner`  
`struct FPhysicsAssetEditorProfilesSummoner : public FWorkflowTabFactory`  
_L9-20_
- inherits: `FWorkflowTabFactory`
- L12 _public prototype_ `FPhysicsAssetEditorProfilesSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp, UPhysicsAsset* InPhysicsAsset);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L16 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L19 _public member_ `TWeakObjectPtr<UPhysicsAsset> PhysicsAssetPtr;` — Reference to our Physics Asset

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorSelection.h` (Private)


#### struct `FPhysicsAssetEditorSelectedElement`  
`struct FPhysicsAssetEditorSelectedElement`  
_L17-54_
- reflection: `USTRUCT()`
- L21 _public typedef_ `using Type = std::underlying_type_t<EPhysicsAssetEditorSelection>;`
- L24 _public member_ `static constexpr Type None = UnderlyingType(EPhysicsAssetEditorSelection::None);` — Backward-compatability aliases — existing code uses FPhysicsAssetEditorSelectedElement::Body etc.
- L25 _public member_ `static constexpr Type Body = UnderlyingType(EPhysicsAssetEditorSelection::Body);`
- L26 _public member_ `static constexpr Type CenterOfMass = UnderlyingType(EPhysicsAssetEditorSelection::CenterOfMass);`
- L27 _public member_ `static constexpr Type Constraint = UnderlyingType(EPhysicsAssetEditorSelection::Constraint);`
- L28 _public member_ `static constexpr Type Primitive = UnderlyingType(EPhysicsAssetEditorSelection::Primitive);`
- L29 _public member_ `static constexpr Type All = UnderlyingType(EPhysicsAssetEditorSelection::All);`
- L31 _public prototype_ `FPhysicsAssetEditorSelectedElement() = default;`
- L32 _public prototype_ `FPhysicsAssetEditorSelectedElement(const Type InSelectedElementType, const int32 InBodyIndex, const EAggCollisionShape::Type InPrimitiveType, const int32 InPrimitiveIndex);`
- L33 _public prototype_ `FPhysicsAssetEditorSelectedElement(const Type InSelectedElementType, const int32 InBodyIndex);`
- L35 _public prototype_ `int32 GetIndex() const;`
- L36 _public prototype_ `EAggCollisionShape::Type GetPrimitiveType() const;`
- L37 _public prototype_ `int32 GetPrimitiveIndex() const;`
- L38 _public prototype_ `Type GetElementType() const;`
- L40 _public prototype_ `bool HasType(const uint32 InElementTypeFlags) const;`
- L43 _public member_ `int32 Index = INDEX_NONE;` — `UPROPERTY()`
- L46 _public member_ `TEnumAsByte<EAggCollisionShape::Type> PrimitiveType = EAggCollisionShape::Unknown;` — `UPROPERTY()`
- L49 _public member_ `int32 PrimitiveIndex = INDEX_NONE;` — `UPROPERTY()`
- L52 _public member_ `int32 SelectedElementType = None;` — `UPROPERTY()`

#### class `FPhysicsAssetEditorSelectionIterator`  
`class FPhysicsAssetEditorSelectionIterator`  
_L75-112_
- L79 _public typedef_ `using Element = FPhysicsAssetEditorSelectedElement;`
- L81 _public prototype_ `FPhysicsAssetEditorSelectionIterator();`
- L82 _public prototype_ `FPhysicsAssetEditorSelectionIterator(const UPhysicsAssetEditorSelection* const InParentSelection);`
- L83 _public prototype_ `FPhysicsAssetEditorSelectionIterator(const UPhysicsAssetEditorSelection* const InParentSelection, const uint32 InElementTypeFlags);`
- L84 _public prototype_ `FPhysicsAssetEditorSelectionIterator(const UPhysicsAssetEditorSelection* const InParentSelection, const uint32 InElementTypeFlags, const uint32 InElementIndex);`
- L85 _public prototype_ `FPhysicsAssetEditorSelectionIterator(const FPhysicsAssetEditorSelectionIterator& Other);`
- L87 _public prototype_ `bool IsValid() const;`
- L88 _public prototype_ `operator bool() const;`
- L90 _public prototype_ `const Element& operator*();`
- L91 _public prototype_ `const Element* operator->();`
- L93 _public prototype_ `void operator++();`
- L94 _public prototype_ `void operator--();`
- L95 _public prototype_ `bool operator==(const FPhysicsAssetEditorSelectionIterator& Other) const;`
- L97 _public prototype_ `uint32 GetElementTypeFlags() const;`
- L98 _public prototype_ `uint32 GetIndexIntoFilteredSelection() const;`
- L99 _public prototype_ `uint32 GetIndexIntoParentSelection() const;`
- L100 _public prototype_ `const UPhysicsAssetEditorSelection* const GetParentSelection() const;`
- L103 _private prototype_ `void StepIndex(const bool bReverseDirection);`
- L105 _private prototype_ `const Element& GetElement();`
- L107 _private member_ `const UPhysicsAssetEditorSelection* const ParentSelection;`
- L108 _private member_ `const uint32 ElementTypeFlags;`
- L110 _private member_ `uint32 FilteredElementIndex;`
- L111 _private member_ `uint32 ParentElementIndex;`

#### class `TPhysicsAssetEditorUniqueIterator`  
`template< typename IteratorType > class TPhysicsAssetEditorUniqueIterator`  
_L114-136_
- L118 _public typedef_ `using ThisType = TPhysicsAssetEditorUniqueIterator< IteratorType >;`
- L119 _public typedef_ `using Iterator = IteratorType;`
- L120 _public typedef_ `using Element = typename Iterator::Element;`
- L122 _public prototype_ `TPhysicsAssetEditorUniqueIterator(Iterator InIterator);`
- L124 _public prototype_ `bool IsValid() const;`
- L125 _public prototype_ `operator bool() const;`
- L126 _public prototype_ `const Element& operator*();`
- L127 _public prototype_ `const Element* operator->();`
- L129 _public prototype_ `void operator++();`
- L130 _public prototype_ `void operator--();`
- L131 _public prototype_ `bool operator==(const ThisType& Other) const;`
- L134 _private member_ `TArray<int32> EncounteredIndexIntoParentSelection;`
- L135 _private member_ `IteratorType ManagedIterator;`
- L213 _function_ `template< typename IteratorType > TPhysicsAssetEditorUniqueIterator< IteratorType >::TPhysicsAssetEditorUniqueIterator(Iterator InIterator) : ManagedIterator(InIterator)`
- L217 _function_ `template< typename IteratorType > bool TPhysicsAssetEditorUniqueIterator< IteratorType >::IsValid() const`
- L222 _function_ `template< typename IteratorType > TPhysicsAssetEditorUniqueIterator< IteratorType >::operator bool() const`
- L227 _function_ `template< typename IteratorType > const typename TPhysicsAssetEditorUniqueIterator< IteratorType >::Element& TPhysicsAssetEditorUniqueIterator< IteratorType >::operator*()`
- L232 _function_ `template< typename IteratorType > const typename TPhysicsAssetEditorUniqueIterator< IteratorType >::Element* TPhysicsAssetEditorUniqueIterator< IteratorType >::operator->()`
- L237 _function_ `template< typename IteratorType > void TPhysicsAssetEditorUniqueIterator< IteratorType >::operator++()`
- L247 _function_ `template< typename IteratorType > void TPhysicsAssetEditorUniqueIterator< IteratorType >::operator--()`
- L261 _function_ `template< typename IteratorType > bool TPhysicsAssetEditorUniqueIterator< IteratorType >::operator==(const ThisType& Other) const`

#### class `TPhysicsAssetEditorSelectionRange`  
`template< typename IteratorType > class TPhysicsAssetEditorSelectionRange`  
_L138-162_
- L141 _public typedef_ `using Iterator = IteratorType;`
- L142 _public typedef_ `using Element = Iterator::Element;`
- L143 _public typedef_ `using TConstIterator = Iterator;`
- L145 _public prototype_ `TPhysicsAssetEditorSelectionRange(Iterator InBegin, Iterator InEnd);`
- L147 _public prototype_ `Iterator CreateConstIterator();`
- L149 _public prototype_ `Iterator begin() const;`
- L150 _public prototype_ `Iterator end() const;`
- L152 _public prototype_ `bool IsValid() const;`
- L153 _public prototype_ `operator bool() const;`
- L154 _public prototype_ `bool IsEmpty() const;`
- L155 _public prototype_ `int32 Num() const;`
- L156 _public prototype_ `TArray<Element> ToArray();`
- L157 _public prototype_ `const Element& At(const int32 InIndex) const;`
- L160 _private member_ `Iterator IteratorBegin;`
- L161 _private member_ `Iterator IteratorEnd;`
- L270 _function_ `template< typename IteratorType > TPhysicsAssetEditorSelectionRange< IteratorType >::TPhysicsAssetEditorSelectionRange(Iterator InBegin, Iterator InEnd) : IteratorBegin(InBegin) , IteratorEnd(InEnd)`
- L275 _function_ `template< typename IteratorType > TPhysicsAssetEditorSelectionRange< IteratorType >::Iterator TPhysicsAssetEditorSelectionRange< IteratorType >::CreateConstIterator()`
- L280 _function_ `template< typename IteratorType > TPhysicsAssetEditorSelectionRange< IteratorType >::Iterator TPhysicsAssetEditorSelectionRange< IteratorType >::begin() const`
- L285 _function_ `template< typename IteratorType > TPhysicsAssetEditorSelectionRange< IteratorType >::Iterator TPhysicsAssetEditorSelectionRange< IteratorType >::end() const`
- L290 _function_ `template< typename IteratorType > bool TPhysicsAssetEditorSelectionRange< IteratorType >::IsValid() const`
- L295 _function_ `template< typename IteratorType > TPhysicsAssetEditorSelectionRange< IteratorType >::operator bool() const`
- L300 _function_ `template< typename IteratorType > bool TPhysicsAssetEditorSelectionRange< IteratorType >::IsEmpty() const`
- L305 _function_ `template< typename IteratorType > int32 TPhysicsAssetEditorSelectionRange< IteratorType >::Num() const`
- L312 _function_ `template< typename IteratorType > TArray< typename TPhysicsAssetEditorSelectionRange< IteratorType >::Element > TPhysicsAssetEditorSelectionRange< IteratorType >::ToArray()`
- L319 _function_ `template< typename IteratorType > const typename TPhysicsAssetEditorSelectionRange< IteratorType >::Element& TPhysicsAssetEditorSelectionRange< IteratorType >::At(const int32 InIndex) const`

#### class `UPhysicsAssetEditorSelection`  
`class UPhysicsAssetEditorSelection : public UObject`  
_L165-209_
- reflection: `UCLASS()`
- inherits: `UObject`
- L170 _public typedef_ `using Element = FPhysicsAssetEditorSelectedElement;`
- L171 _public typedef_ `using Selection = TArray< Element >;`
- L172 _public typedef_ `using Iterator = FPhysicsAssetEditorSelectionIterator;`
- L174 _public typedef_ `using FilterIterator = FPhysicsAssetEditorSelectionIterator;`
- L175 _public typedef_ `using UniqueIterator = TPhysicsAssetEditorUniqueIterator< FilterIterator >;`
- L177 _public typedef_ `using FilterRange = TPhysicsAssetEditorSelectionRange< FilterIterator >;`
- L178 _public typedef_ `using UniqueRange = TPhysicsAssetEditorSelectionRange< UniqueIterator >;`
- L180 _public prototype_ `const Selection& SelectedElements() const;`
- L181 _public prototype_ `const Element& GetSelectedAt(const int32 InElementIndex) const;`
- L182 _public prototype_ `const Element* GetSelectedAtValidIndex(const int32 InElementIndex) const;`
- L183 _public prototype_ `bool IsValidIndex(const int32 InElementIndex) const;`
- L184 _public prototype_ `bool ContainsType(const uint32 InElementTypeFlags) const;`
- L185 _public function_ `int32 Num() const`
- L186 _public prototype_ `int32 NumOfType(const uint32 InElementTypeFlags) const;`
- L188 _public prototype_ `void ClearSelection();`
- L189 _public prototype_ `void ClearSelection(const uint32 InElementTypeFlags);`
- L190 _public prototype_ `void ClearSelectionWithoutTransaction(const uint32 InElementTypeFlags);` — This can be used to clear selected elements of type when inside an existing transaction.
- L192 _public function_ `Iterator SelectedElementsOfTypeIterator(const uint32 InElementTypeFlags) const`
- L193 _public prototype_ `FilterRange SelectedElementsOfType(const uint32 InElementTypeFlags) const;`
- L194 _public prototype_ `UniqueRange UniqueSelectedElementsOfType(const uint32 InElementTypeFlags) const;`
- L196 _public prototype_ `bool ModifySelected(const TArray<Element>& InSelectedElements, const bool bSelected);`
- L197 _public prototype_ `bool SetSelected(const TArray<Element>& InSelectedElements);`
- L199 _public prototype_ `const Element* GetNextSelectedOfType(const int32 InElementIndex, const uint32 InElementTypeFlags) const;`
- L200 _public prototype_ `const Element* GetLastSelectedOfType(const uint32 InElementTypeFlags) const;`
- L204 _private prototype_ `void ClearSelectionInternal();`
- L205 _private prototype_ `void ClearSelectionInternal(const uint32 InElementTypeFlags, const bool bShouldCreateTransaction);`
- L208 _private member_ `TArray< FPhysicsAssetEditorSelectedElement > SelectedElementCollection;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L56 _prototype_ `bool operator==(const FPhysicsAssetEditorSelectedElement& Lhs, const FPhysicsAssetEditorSelectedElement& Rhs);`
- L58 _prototype_ `bool IsReferencingPrimitive(const FPhysicsAssetEditorSelectedElement& InSelection, const int32 InBodyIndex, const EAggCollisionShape::Type InPrimitiveType, const int32 InPrimitiveIndex);`
- L60 _prototype_ `FPhysicsAssetEditorSelectedElement MakeBodySelection(TObjectPtr<UPhysicsAsset> InPhysicsAsset, const int32 InBodyIndex);`
- L61 _prototype_ `TArray<FPhysicsAssetEditorSelectedElement> MakeBodySelection(TObjectPtr<UPhysicsAsset> InPhysicsAsset, const TArray<int32> InBodyIndexCollection);`
- L63 _prototype_ `FPhysicsAssetEditorSelectedElement MakeCoMSelection(const int32 InCoMIndex);`
- L65 _prototype_ `FPhysicsAssetEditorSelectedElement MakeConstraintSelection(const int32 InConstraintIndex);`
- L66 _prototype_ `TArray<FPhysicsAssetEditorSelectedElement> MakeConstraintSelection(const TArray<int32>& Indices);`
- L68 _prototype_ `FPhysicsAssetEditorSelectedElement MakePrimitiveSelection(const int32 InBodyIndex, const EAggCollisionShape::Type InPrimitiveType, const int32 InPrimitiveIndex);`
- L70 _prototype_ `FPhysicsAssetEditorSelectedElement MakeSelectionAnyPrimitiveInBody(TObjectPtr<UPhysicsAsset> InPhysicsAsset, const int32 InBodyIndex);` — Selected the 'first' primitive in the supplied body
- L71 _prototype_ `TArray<FPhysicsAssetEditorSelectedElement> MakeSelectionAllPrimitivesInBody(TObjectPtr<UPhysicsAsset> InPhysicsAsset, const int32 InBodyIndex);`
- L72 _prototype_ `TArray<FPhysicsAssetEditorSelectedElement> MakeSelectionAllPrimitivesInBody(TObjectPtr<UPhysicsAsset> InPhysicsAsset, const TArray<int32> InBodyIndexCollection);`
- L241 _function_ `while (IsValid() && EncounteredIndexIntoParentSelection.ContainsByPredicate([this](const int32& Element) { return ManagedIterator.GetParentSelection()->GetSelectedAt(Element).Index == ManagedIterator->Index; }))` (scope `TPhysicsAssetEditorUniqueIterator::operator ++`)

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorSharedData.h` (Private)


#### struct `FScopedBulkSelection`  
`struct FScopedBulkSelection`  
_L29-35_
- desc: Scoped object that blocks selection broadcasts until it leaves scope
- L31 _public prototype_ `FScopedBulkSelection(TSharedPtr<FPhysicsAssetEditorSharedData> InSharedData);`
- L32 _public prototype_ `~FScopedBulkSelection();`
- L34 _public member_ `TSharedPtr<FPhysicsAssetEditorSharedData> SharedData;`

#### class `UPhysicsAssetCollisionPair`  
`class UPhysicsAssetCollisionPair : public UObject`  
_L43-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: class UPhysicsAssetCollisionPair Used to simplify Copy + Paste of collision relationships between physics bodies.
- L48 _public function_ `void Set(const FName InBoneNameA, const FName InBoneNameB)`
- L55 _public member_ `FName BoneNameA;` — `UPROPERTY()`
- L58 _public member_ `FName BoneNameB;` — `UPROPERTY()`

#### class `FPhysicsAssetEditorSharedData`  
`class FPhysicsAssetEditorSharedData`  
_L65-506_
- L69 _public typedef_ `using SelectionFilterRange = UPhysicsAssetEditorSelection::FilterRange;`
- L70 _public typedef_ `using SelectionUniqueRange = UPhysicsAssetEditorSelection::UniqueRange;`
- L73 _public prototype_ `FPhysicsAssetEditorSharedData();` — Constructor/Destructor
- L74 _public prototype_ `virtual ~FPhysicsAssetEditorSharedData();`
- L84 _public typedef_ `using FSelection = FPhysicsAssetEditorSelectedElement;` — Encapsulates a selected set of bodies or constraints
- L87 _public prototype_ `void Initialize(const TSharedRef<IPersonaPreviewScene>& InPreviewScene);` — Initializes members
- L90 _public prototype_ `void CachePreviewMesh();` — Caches a preview mesh. Sets us to a default mesh if none is set yet (or if an older one got deleted)
- L93 _public prototype_ `EPhysicsAssetEditorMeshViewMode GetCurrentMeshViewMode(bool bSimulation);` — Accessor for mesh view mode, allows access for simulation and non-simulation modes
- L96 _public prototype_ `EPhysicsAssetEditorCenterOfMassViewMode GetCurrentCenterOfMassViewMode(const bool bSimulation) const;` — Accessor for Center of Mass view mode, allows access for simulation and non-simulation modes
- L99 _public prototype_ `EPhysicsAssetEditorCollisionViewMode GetCurrentCollisionViewMode(bool bSimulation);` — Accessor for collision view mode, allows access for simulation and non-simulation modes
- L102 _public prototype_ `EPhysicsAssetEditorConstraintViewMode GetCurrentConstraintViewMode(bool bSimulation);` — Accessor for constraint view mode, allows access for simulation and non-simulation modes
- L105 _public prototype_ `void ClearSelectedConstraints();` — Clear all of the selected constraints
- L108 _public prototype_ `void ModifySelectedConstraints(const int32 ConstraintIndex, const bool bSelected);` — Add or remove a constraint from the current selection
- L111 _public prototype_ `void ModifySelectedConstraints(const TArray<int32>& ConstraintsIndices, const bool bSelected);` — Add or remove a collection of constraints from the current selection
- L114 _public prototype_ `void SetSelectedConstraints(const TArray<int32>& ConstraintsIndices);` — Set the current selection
- L117 _public prototype_ `bool IsConstraintSelected(int32 ConstraintIndex) const;` — Check whether the constraint at the specified index is selected
- L120 _public prototype_ `FTransform GetConstraintWorldTM(const FSelection* Constraint, EConstraintFrame::Type Frame) const;` — Get the world transform of the specified selected constraint
- L123 _public prototype_ `FTransform GetConstraintWorldTM(const UPhysicsConstraintTemplate* const ConstraintSetup, const EConstraintFrame::Type Frame, const float Scale = 1.0f) const;` — Get the world transform of the specified constraint
- L126 _public prototype_ `FTransform GetConstraintMatrix(int32 ConstraintIndex, EConstraintFrame::Type Frame, float Scale) const;` — Get the world transform of the specified constraint
- L129 _public prototype_ `FTransform GetConstraintBodyTM(const UPhysicsConstraintTemplate* ConstraintSetup, EConstraintFrame::Type Frame) const;` — Get the body transform of the specified constraint
- L132 _public prototype_ `void SetConstraintRelTM(const FSelection* Constraint, const FTransform& RelTM);` — Set the constraint relative transform
- L135 _public function_ `inline void SetSelectedConstraintRelTM(const FTransform& RelTM)` — Set the constraint relative transform for a single selected constraint
- L141 _public prototype_ `void SnapConstraintToBone(const int32 ConstraintIndex, const EConstraintTransformComponentFlags ComponentFlags = EConstraintTransformComponentFlags::All);` — Snaps a constraint at the specified index to it's bone
- L144 _public prototype_ `void SnapConstraintToBone(FConstraintInstance& ConstraintInstance, const EConstraintTransformComponentFlags ComponentFlags = EConstraintTransformComponentFlags::All);` — Snaps the specified constraint to it's bone
- L147 _public prototype_ `void PasteConstraintProperties();` — Paste the currently-copied constraint properties onto the single selected constraint
- L151 _public prototype_ `void CycleCurrentConstraintOrientation();` — Cycles the rows of the transform matrix for the selected constraint. Assumes the selected constraint is valid and that we are in constraint editing mode
- L154 _public prototype_ `void CycleCurrentConstraintActive();` — Cycles the active constraint
- L157 _public prototype_ `void ToggleConstraint(EPhysicsAssetEditorConstraintType Constraint);` — Cycles the active constraint between locked and limited
- L160 _public prototype_ `bool IsAngularConstraintLocked(EPhysicsAssetEditorConstraintType Constraint) const;` — Gets whether the active constraint is locked
- L162 _public prototype_ `void DeleteBody(int32 DelBodyIndex, bool bRefreshComponent = true);`
- L165 _public prototype_ `void DeleteCurrentSelection();` — Deletes all currently selected objects
- L168 _public prototype_ `void DeleteCurrentBody();` — Deletes the currently selected bodies and all their primitives
- L171 _public prototype_ `void DeleteCurrentPrim();` — Deletes the currently selected primitives
- L174 _public prototype_ `void DeleteCurrentConstraint();` — Deletes the currently selected constraints
- L177 _public prototype_ `void SetGroupSelectionActive(const bool bIsActive);`
- L178 _public prototype_ `bool IsGroupSelectionActive() const;`
- L180 _public prototype_ `void ModifySelected(const TArray<FSelection>& InSelectedElements, const bool bSelected);`
- L181 _public prototype_ `void SetSelected(const TArray<FSelection>& InSelectedElements);`
- L182 _public prototype_ `bool IsSelected(const FSelection& InSelection) const;`
- L185 _public prototype_ `void ClearSelectedCoMs();` — Center of Mass Selection
- L186 _public prototype_ `void ModifySelectedCoMs(const FSelection& InSelectedCoM, const bool bSelected);`
- L187 _public prototype_ `void ModifySelectedCoMs(const TArray<FSelection>& InSelectedElements, const bool bSelected);`
- L188 _public prototype_ `void SetSelectedCoMs(const FSelection& InSelectedElement);`
- L189 _public prototype_ `void SetSelectedCoMs(const TArray<FSelection>& InSelectedElements);`
- L190 _public prototype_ `bool IsCoMSelected(const int32 BodyIndex) const;`
- L193 _public prototype_ `void ClearSelectedBody();` — Body Selection
- L194 _public prototype_ `void ModifySelectedBodies(const FSelection& Body, bool bSelected);`
- L195 _public prototype_ `void ModifySelectedBodies(const TArray<FSelection>& Bodies, bool bSelected);`
- L196 _public prototype_ `void SetSelectedBodies(const FSelection& InSelectedElement);`
- L197 _public prototype_ `void SetSelectedBodies(const TArray<FSelection>& Bodies);`
- L198 _public prototype_ `bool IsBodySelected(const FSelection& Body) const;`
- L199 _public prototype_ `bool IsBodySelected(const int32 BodyIndex) const;`
- L201 _public prototype_ `void ModifySelectedBodies(const int32 BodyIndex, const bool bSelected);`
- L202 _public prototype_ `void ModifySelectedBodies(const TArray<int32>& BodiesIndices, const bool bSelected);`
- L203 _public prototype_ `void SetSelectedBodies(const int32 BodyIndex);`
- L204 _public prototype_ `void SetSelectedBodies(const TArray<int32>& BodiesIndices);`
- L206 _public prototype_ `void SetSelectedBodiesAllPrimitive(const TArray<int32>& BodiesIndices, bool bSelected);`
- L207 _public prototype_ `void SetSelectedBodiesPrimitivesWithCollisionType(const TArray<int32>& BodiesIndices, const ECollisionEnabled::Type CollisionType, bool bSelected);`
- L208 _public prototype_ `void SetSelectedBodiesPrimitives(const TArray<int32>& BodiesIndices, bool bSelected, const TFunction<bool(const TArray<FSelection>&, const int32 BodyIndex, const FKShapeElem&)>& Predicate);`
- L211 _public prototype_ `void ClearSelectedPrimitives();` — Primitives Selection
- L212 _public prototype_ `void ModifySelectedPrimitives(const FSelection& InSelectedPrimitive, const bool bSelected);`
- L213 _public prototype_ `void ModifySelectedPrimitives(const TArray<FSelection>& InSelectedElements, const bool bSelected);`
- L214 _public prototype_ `void SetSelectedPrimitives(const FSelection& InSelectedElement);`
- L215 _public prototype_ `void SetSelectedPrimitives(const TArray<FSelection>& InSelectedElements);`
- L217 _public prototype_ `void ToggleSelectionType(bool bIgnoreUserConstraints = true);`
- L218 _public prototype_ `void ToggleShowSelected();`
- L219 _public prototype_ `bool IsBodyHidden(const int32 BodyIndex) const;`
- L220 _public prototype_ `bool IsConstraintHidden(const int32 ConstraintIndex) const;`
- L221 _public prototype_ `void HideBody(const int32 BodyIndex);`
- L222 _public prototype_ `void ShowBody(const int32 BodyIndex);`
- L223 _public prototype_ `void HideConstraint(const int32 ConstraintIndex);`
- L224 _public prototype_ `void ShowConstraint(const int32 ConstraintIndex);`
- L225 _public prototype_ `void ShowAll();`
- L226 _public prototype_ `void HideAll();`
- L227 _public prototype_ `void HideAllBodies();`
- L228 _public prototype_ `void HideAllConstraints();`
- L229 _public prototype_ `void ToggleShowOnlyColliding();`
- L230 _public prototype_ `void ToggleShowOnlyConstrained();`
- L231 _public prototype_ `void ToggleShowOnlySelected();`
- L232 _public prototype_ `void ShowSelected();`
- L233 _public prototype_ `void HideSelected();`
- L234 _public prototype_ `void RefreshPhysicsAssetChange(const UPhysicsAsset* InPhysAsset, bool bFullClothRefresh = true);`
- L237 _public prototype_ `void MakeNewBody( int32 NewBoneIndex, bool bAutoSelect = true, TConstArrayView<int32> BoneIndicesInCreation = TConstArrayView<int32>());` — The optional BoneIndicesInCreation can contain a list of bone indices that will be created - for when bones are checked to see if they are (or will be) physical.
- L240 _public prototype_ `void MakeNewBody( const FPhysAssetCreateParams& NewBodyData, const int32 NewBoneIndex, const bool bAutoSelect = true, TConstArrayView<int32> BoneIndicesInCreation = TConstArrayView<int32>());`
- L243 _public prototype_ `void RecreateBody(const int32 BoneIndex, const bool bAutoSelect = true);` — Create a new physics body to replace an existing one.
- L244 _public prototype_ `void RecreateBody(const FPhysAssetCreateParams& BodyData, const int32 BoneIndex, const bool bAutoSelect = true);` — Create a new physics body to replace an existing one.
- L245 _public prototype_ `void MakeOrRecreateBody(const int32 NewBoneIndex, const bool bAutoSelect = true);` — Create a new physics body, replacing an existing one at the same index if it exists.
- L246 _public prototype_ `void MakeNewConstraints(int32 ParentBodyIndex, const TArray<int32>& ChildBodyIndices);`
- L247 _public prototype_ `void MakeNewConstraint(int32 ParentBodyIndex, int32 ChildBodyIndex);`
- L248 _public prototype_ `void CopySelectedBodiesAndConstraintsToClipboard(int32& OutNumCopiedBodies, int32& OutNumCopiedConstraints, int32& OutNumCopiedDisabledCollisionPairs);`
- L249 _public prototype_ `bool CanPasteBodiesAndConstraintsFromClipboard() const;`
- L250 _public prototype_ `void PasteBodiesAndConstraintsFromClipboard(int32& OutNumPastedBodies, int32& OutNumPastedConstraints, int32& OutNumPastedDisabledCollisionPairs);`
- L251 _public prototype_ `void CopySelectedShapesToClipboard(int32& OutNumCopiedShapes, int32& OutNumBodiesCopiedFrom);`
- L252 _public prototype_ `bool CanPasteShapesFromClipboard() const;`
- L253 _public prototype_ `void PasteShapesFromClipboard(int32& OutNumPastedShapes, int32& OutNumBodiesPastedInto);`
- L254 _public prototype_ `void CopyBodyProperties();`
- L255 _public prototype_ `void CopyConstraintProperties();`
- L256 _public prototype_ `void PasteBodyProperties();`
- L257 _public prototype_ `void CopyBodyName();`
- L258 _public prototype_ `bool WeldSelectedBodies(bool bWeld = true);`
- L259 _public prototype_ `void Mirror();`
- L262 _public prototype_ `void AutoNamePrimitive(int32 BodyIndex, EAggCollisionShape::Type PrimitiveType, int32 PrimitiveIndex = INDEX_NONE);` — auto name a primitive, if PrimitiveIndex is INDEX_NONE, then the last primitive of specified typed is renamed
- L263 _public prototype_ `void AutoNameAllPrimitives(int32 BodyIndex, EAggCollisionShape::Type PrimitiveType);`
- L264 _public prototype_ `void AutoNameAllPrimitives(int32 BodyIndex, EPhysAssetFitGeomType PrimitiveType);`
- L267 _public prototype_ `void ToggleSimulation();` — Toggle simulation on and off
- L270 _public prototype_ `void OpenNewBodyDlg();` — Open a new body dialog
- L273 _public prototype_ `static void OpenNewBodyDlg(EAppReturnType::Type* NewBodyResponse);` — Open a new body dialog, filling in NewBodyResponse when the dialog is closed
- L276 _public prototype_ `static TSharedRef<SWidget> CreateGenerateBodiesWidget(const FSimpleDelegate& InOnCreate, const FSimpleDelegate& InOnCancel = FSimpleDelegate(), const TAttribute<bool>& InIsEnabled = TAttribute<bool>(), const TAttribute<FText>& InCreateButtonText = TAttribute<FText>(), bool bForNewAsset = false);` — Helper function for creating the details panel widget and other controls that form the New body dialog (used by OpenNewBodyDlg and the tools tab)
- L279 _public prototype_ `void HitBone(int32 BodyIndex, EAggCollisionShape::Type PrimType, int32 PrimIndex, bool bGroupSelect);` — Handle clicking on a body
- L282 _public prototype_ `void HitCoM(const int32 BodyIndex, const bool bGroupSelect);` — Handle clicking on a Center of Mass marker
- L285 _public prototype_ `void HitConstraint(int32 ConstraintIndex, bool bGroupSelect);` — Handle clikcing on a constraint
- L288 _public prototype_ `void PostUndo();` — Undo/Redo
- L289 _public prototype_ `void Redo();`
- L292 _public prototype_ `void SetCollisionBetweenSelected(bool bEnableCollision);` — Helpers to enable/disable collision on selected bodies
- L293 _public prototype_ `bool CanSetCollisionBetweenSelected(bool bEnableCollision) const;`
- L294 _public prototype_ `void SetCollisionBetweenSelectedAndAll(bool bEnableCollision);`
- L295 _public prototype_ `bool CanSetCollisionBetweenSelectedAndAll(bool bEnableCollision) const;`
- L298 _public prototype_ `void SetPrimitiveCollision(ECollisionEnabled::Type CollisionEnabled);` — Helpers to set primitive-level collision filtering on selected bodies
- L299 _public prototype_ `bool CanSetPrimitiveCollision(ECollisionEnabled::Type CollisionEnabled) const;`
- L300 _public prototype_ `bool GetIsPrimitiveCollisionEnabled(ECollisionEnabled::Type CollisionEnabled) const;`
- L301 _public prototype_ `void SetPrimitiveContributeToMass(bool bContributeToMass);`
- L302 _public prototype_ `bool CanSetPrimitiveContributeToMass() const;`
- L303 _public prototype_ `bool GetPrimitiveContributeToMass() const;`
- L306 _public prototype_ `void AddReferencedObjects(FReferenceCollector& Collector);` — Prevents GC from collecting our objects
- L309 _public prototype_ `void EnableSimulation(bool bEnableSimulation);` — Enables and disables simulation. Used by ToggleSimulation
- L312 _public prototype_ `void ForceDisableSimulation();` — Force simulation off for all bodies, regardless of physics type
- L315 _public prototype_ `void UpdateClothPhysics();` — Update the clothing simulation's (if any) collision
- L318 _public prototype_ `void BroadcastSelectionChanged();` — broadcast a selection change ( if bSuspendSelectionBroadcast is false )
- L321 _public prototype_ `void BroadcastHierarchyChanged();` — broadcast a change in the hierarchy
- L324 _public prototype_ `void BroadcastPreviewChanged();` — broadcast a change in the preview
- L327 _public prototype_ `static bool ClipboardHasCompatibleData();` — Returns true if the clipboard contains data this class can process
- L330 _public prototype_ `void ToggleShowCom();` — Control whether we draw a CoM marker in the viewport
- L331 _public prototype_ `void SetShowCom(bool InValue);`
- L332 _public prototype_ `bool GetShowCom() const;`
- L335 _public prototype_ `FVector GetCOMRenderPosition(const int32 BodyIndex) const;` — Returns the correct location to draw a CoM marker in the viewport
- L337 _public prototype_ `bool IsCoMAxisFixedInComponentSpace(const int32 BodyIndex, const EAxis::Type InAxis) const;`
- L338 _public prototype_ `void SetCoMAxisFixedInComponentSpace(const int32 BodyIndex, const EAxis::Type InAxis, const bool bValue);`
- L341 _public prototype_ `FVector CalculateCoMNudgeForWorldSpacePosition(const int32 BodyIndex, const FVector& CoMPositionWorldSpace) const;` — Calculate a Center of Mass nudge (offset) for a given body that will locate that body's CoM at the supplied position in world space.
- L344 _public prototype_ `void RecordSelectedCoM();` — Make a copy of the current component space CoM position from each selected physics body - called before a change in physics body transform
- L346 _public function_ `const FVector* FindManipulatedBodyCoMPosition(const int32 BodyIndex) const`
- L351 _public function_ `FVector* FindManipulatedBodyCoMPosition(const int32 BodyIndex)`
- L356 _public prototype_ `void PostManipulationUpdateCoM();`
- L357 _public prototype_ `void UpdateCoM();`
- L359 _public prototype_ `const UPhysicsAssetEditorSelection* GetSelectedObjects() const;`
- L361 _public prototype_ `SelectionFilterRange SelectedBodies() const;`
- L362 _public prototype_ `SelectionFilterRange SelectedCoMs() const;`
- L363 _public prototype_ `SelectionFilterRange SelectedConstraints() const;`
- L364 _public prototype_ `SelectionFilterRange SelectedPrimitives() const;`
- L365 _public prototype_ `SelectionFilterRange SelectedBodiesAndPrimitives() const;`
- L366 _public prototype_ `SelectionUniqueRange UniqueSelectionReferencingBodies() const;`
- L369 _public prototype_ `const FSelection* GetSelectedBodyOrPrimitive() const;` — Returns the most recently selected body or primitive - this is useful as selecting a primitive often acts in the same way as selecting its owning body.
- L370 _public prototype_ `const FSelection* GetSelectedBody() const;`
- L371 _public prototype_ `const FSelection* GetSelectedCoM() const;`
- L372 _public prototype_ `const FSelection* GetSelectedConstraint() const;`
- L373 _public prototype_ `const FSelection* GetSelectedPrimitive() const;`
- L375 _public prototype_ `FVector GetSelectedCoMPosition();`
- L378 _public prototype_ `void ClearSelected();` — Clears all the selected objects
- L382 _private prototype_ `bool ModifySelectionInternal(TFunctionRef<bool(void)> SelectionOperation);`
- L385 _private prototype_ `void InitConstraintSetup(UPhysicsConstraintTemplate* ConstraintSetup, int32 ChildBodyIndex, int32 ParentBodyIndex);` — Initializes a constraint setup
- L388 _private prototype_ `void SetCollisionBetween(int32 Body1Index, int32 Body2Index, bool bEnableCollision);` — Collision editing helper methods
- L391 _private prototype_ `void UpdateNoCollisionBodies();` — Update the cached array of bodies that do not collide with the current body selection
- L394 _private prototype_ `void CopyConstraintProperties(const UPhysicsConstraintTemplate * FromConstraintSetup, UPhysicsConstraintTemplate * ToConstraintSetup, bool bKeepOldRotation = false);` — Copy the properties of the one and only selected constraint
- L397 _private prototype_ `void CopyToClipboard(const FString& ObjectType, UObject* Object);` — Copies a reference to a given element to the clipboard
- L400 _private prototype_ `bool PasteFromClipboard(const FString& InObjectType, UPhysicsAsset*& OutAsset, UObject*& OutObject);` — Pastes data from the clipboard on a given type
- L403 _private prototype_ `void ConditionalClearClipboard(const FString& ObjectType, UObject* Object);` — Clears data in clipboard if it was pointing to the given type/data
- L406 _private prototype_ `static bool ParseClipboard(UPhysicsAsset*& OutAsset, FString& OutObjectType, UObject*& OutObject);` — Checks and parses clipboard data
- L409 _private prototype_ `FString MakeUniqueNewConstraintName();` — Generate a new unique name for a constraint
- L413 _public prototype_ `DECLARE_EVENT_OneParam(FPhysicsAssetEditorSharedData, FSelectionChanged, const TArray<FSelection>&);` — Callback for handling selection changes
- L414 _public member_ `FSelectionChanged SelectionChangedEvent;`
- L417 _public prototype_ `DECLARE_EVENT(FPhysicsAssetEditorSharedData, FHierarchyChanged);` — Callback for handling changes to the bone/body/constraint hierarchy
- L418 _public member_ `FHierarchyChanged HierarchyChangedEvent;`
- L421 _public prototype_ `DECLARE_EVENT(FPhysicsAssetEditorSharedData, FHierarchySelectionChangedEvent);` — Callback for handling changes to the current selection in the tree
- L422 _public member_ `FHierarchySelectionChangedEvent HierarchySelectionChangedEvent;`
- L425 _public prototype_ `DECLARE_EVENT(FPhysicsAssetEditorSharedData, FPreviewChanged);` — Callback for triggering a refresh of the preview viewport
- L426 _public member_ `FPreviewChanged PreviewChangedEvent;`
- L429 _public member_ `TObjectPtr<UPhysicsAsset> PhysicsAsset;` — The PhysicsAsset asset being inspected
- L432 _public member_ `TObjectPtr<UPhysicsAssetEditorSkeletalMeshComponent> EditorSkelComp;` — PhysicsAssetEditor specific skeletal mesh component
- L435 _public member_ `TObjectPtr<class UPhysicalAnimationComponent> PhysicalAnimationComponent;` — PhysicsAssetEditor specific physical animation component
- L438 _public member_ `TWeakPtr<IPersonaPreviewScene> PreviewScene;` — Preview scene
- L441 _public member_ `TObjectPtr<UPhysicsAssetEditorOptions> EditorOptions;` — Editor options
- L444 _public member_ `EAppReturnType::Type NewBodyResponse;` — Results from the new body dialog
- L447 _public member_ `TObjectPtr<UPhysicsAssetEditorPhysicsHandleComponent> MouseHandle;` — Helps define how the asset behaves given user interaction in simulation mode
- L450 _public member_ `const FColor COMRenderColor;` — Draw color for center of mass debug strings
- L453 _public member_ `TArray<int32> NoCollisionBodies;` — List of bodies that don't collide with the currently selected collision body
- L456 _public member_ `TArray<FBoneVertInfo> DominantWeightBoneInfos;` — Bone info
- L457 _public member_ `TArray<FBoneVertInfo> AnyWeightBoneInfos;`
- L459 _public member_ `TObjectPtr<UPhysicsAssetEditorSelection> SelectedObjects;`
- L461 _public prototype_ `void BeginManipulation();`
- L462 _public prototype_ `void EndManipulation();`
- L463 _public function_ `bool IsManipulating() const`
- L465 _public member_ `TMap<int32, FVector> ManipulatedBodyCoMPositionMap;`
- L467 _public prototype_ `struct FPhysicsAssetRenderSettings* GetRenderSettings() const;`
- L470 _public prototype_ `void FindOverlappingBodyPairs(const int32 InBodyIndex, TArray<TPair<int32, int32>>& OutCollidingBodyPairs);` — Physics Body Overlap Detection
- L471 _public prototype_ `void RemoveOverlappingBodyPairs(const int32 InBodyIndex, TArray<TPair<int32, int32>>& OutCollidingBodyPairs);`
- L472 _public prototype_ `void InitializeOverlappingBodyPairs();`
- L473 _public prototype_ `void UpdateOverlappingBodyPairs(const int32 InBodyIndex);`
- L474 _public prototype_ `bool IsBodyOverlapping(const int32 InBodyIndex) const;`
- L475 _public prototype_ `bool ShouldShowBodyOverlappingHighlight(const int32 InBodyIndex) const;`
- L477 _public prototype_ `void ToggleHighlightOverlapingBodies();`
- L478 _public prototype_ `bool IsHighlightingOverlapingBodies() const;`
- L480 _public member_ `TArray<TPair<int32, int32>> OverlappingCollidingBodyPairs;` — A record of all the pairs of physics bodies that are overlapping and not flagged as non-colliding in the physics asset.
- L483 _public member_ `bool bRunningSimulation;` — Misc toggles
- L484 _public member_ `bool bNoGravitySimulation;`
- L487 _public member_ `bool bManipulating;` — Manipulation (rotate, translate, scale)
- L489 _public member_ `bool bIsGroupSelectionActive = false;`
- L490 _public member_ `bool bShouldUpdatedSelectedCoMs = false;`
- L493 _public member_ `bool bSuspendSelectionBroadcast;` — when true, we dont broadcast every selection change - allows for bulk changes without so much overhead
- L496 _public member_ `int32 InsideSelChange;` — Used to prevent recursion with tree hierarchy ... needs to be rewritten!
- L498 _public member_ `FTransform ResetTM;`
- L500 _public member_ `FIntPoint LastClickPos;`
- L501 _public member_ `FVector LastClickOrigin;`
- L502 _public member_ `FVector LastClickDirection;`
- L503 _public member_ `FVector LastClickHitPos;`
- L504 _public member_ `FVector LastClickHitNormal;`
- L505 _public member_ `bool bLastClickHit;`

#### enum `FPhysicsAssetEditorSharedData::EPhysicsAssetEditorConstraintType`  
`enum EPhysicsAssetEditorConstraintType`  
_L76-81_
- L78 _public enumerator_ `PCT_Swing1`
- L79 _public enumerator_ `PCT_Swing2`
- L80 _public enumerator_ `PCT_Twist`

#### Free symbols / members of external scopes

- L413 _delegate_ `DECLARE_EVENT_OneParam(FPhysicsAssetEditorSharedData, FSelectionChanged, const TArray<FSelection>&);` — Callback for handling selection changes
- L417 _delegate_ `DECLARE_EVENT(FPhysicsAssetEditorSharedData, FHierarchyChanged);` — Callback for handling changes to the bone/body/constraint hierarchy
- L421 _delegate_ `DECLARE_EVENT(FPhysicsAssetEditorSharedData, FHierarchySelectionChangedEvent);` — Callback for handling changes to the current selection in the tree
- L425 _delegate_ `DECLARE_EVENT(FPhysicsAssetEditorSharedData, FPreviewChanged);` — Callback for triggering a refresh of the preview viewport
- L508 _prototype_ `EAggCollisionShape::Type ConvertPhysicsAssetGeomTypeToAggCollisionShapeType(EPhysAssetFitGeomType PhysicsAssetGeomType);`
- L509 _prototype_ `EPhysAssetFitGeomType ConvertAggCollisionShapeTypeToPhysicsAssetGeomType(const EAggCollisionShape::Type AggCollisionShapeType);`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorSkeletalMeshComponent.h` (Private)


#### struct `FPhysicsAssetEditorDrawState`  
`struct FPhysicsAssetEditorDrawState`  
_L22-34_
- reflection: `USTRUCT()`
- desc: FDrawState Keeps track of render material and line color for an object or state displayed in the view port.
- L25 _public prototype_ `FPhysicsAssetEditorDrawState() = default;`
- L26 _public prototype_ `FPhysicsAssetEditorDrawState(TObjectPtr<UMaterialInstanceDynamic> InMaterial, const FColor& InColor);`
- L27 _public prototype_ `FPhysicsAssetEditorDrawState(const TCHAR* MaterialName, const FColor& InColor);`
- L30 _public member_ `TObjectPtr<UMaterialInstanceDynamic> Material;` — `UPROPERTY(transient)`
- L33 _public member_ `FColor Color = FColor::Black;` — `UPROPERTY(transient)`

#### class `UPhysicsAssetEditorSkeletalMeshComponent`  
`class UPhysicsAssetEditorSkeletalMeshComponent : public UDebugSkelMeshComponent`  
_L38-128_
- reflection: `UCLASS()`
- inherits: `UDebugSkelMeshComponent`
- L43 _private member_ `class FPhysicsAssetEditorSharedData* SharedData;` — Data and methods shared across multiple classes
- L49 _private member_ `FPhysicsAssetEditorDrawState ElemSelectedPrimitiveDrawState;` — `UPROPERTY(transient)` — Primitives that are directly selected.
- L53 _private member_ `FPhysicsAssetEditorDrawState ElemPrimitiveInSelectedBodyDrawState;` — `UPROPERTY(transient)` — Primitives that are part of a selected body but not directly selected.
- L57 _private member_ `FPhysicsAssetEditorDrawState ElemUnselectedDrawState;` — `UPROPERTY(transient)` — Bodies that are currently not selected.
- L61 _private member_ `FPhysicsAssetEditorDrawState ElemSelectedOverlappingDrawState;` — `UPROPERTY(transient)` — Bodies that are currently selected and would collide with other bodies in the current pose during simulation.
- L65 _private member_ `FPhysicsAssetEditorDrawState ElemUnselectedOverlappingDrawState;` — `UPROPERTY(transient)` — Bodies that are currently not selected and would collide with other bodies in the current pose during simulation.
- L69 _private member_ `FPhysicsAssetEditorDrawState ElemCollidingWithSelectedDrawState;` — `UPROPERTY(transient)` — Bodies that are able to collide with one or more of the selected bodies.
- L72 _private member_ `FPhysicsAssetEditorDrawState BoneUnselectedDrawState;` — `UPROPERTY(transient)`
- L75 _private member_ `FPhysicsAssetEditorDrawState BoneNoCollisionDrawState;` — `UPROPERTY(transient)`
- L77 _private member_ `FColor ConstraintBone1Color;`
- L78 _private member_ `FColor ConstraintBone2Color;`
- L79 _private member_ `FColor HierarchyDrawColor;`
- L80 _private member_ `FColor AnimSkelDrawColor;`
- L81 _private member_ `float COMRenderSize;`
- L82 _private member_ `float InfluenceLineLength;`
- L83 _private member_ `FColor InfluenceLineColor;`
- L86 _private member_ `TObjectPtr<UMaterialInterface> BoneMaterialHit;` — `UPROPERTY(transient)`
- L89 _private member_ `TArray<FTransform> AnimationSpaceBases;` — Mesh-space matrices showing state of just animation (ie before physics) - useful for debugging!
- L92 _private prototype_ `virtual TObjectPtr<UAnimPreviewInstance> CreatePreviewInstance() override;` — UDebugSkelMeshComponent interface
- L95 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;` — UPrimitiveComponent interface
- L96 _private prototype_ `virtual void AddImpulseAtLocation(FVector Impulse, FVector Location, FName BoneName = NAME_None) override;`
- L97 _private prototype_ `virtual bool ShouldCreatePhysicsState() const override;`
- L100 _private prototype_ `virtual void RefreshBoneTransforms(FActorComponentTickFunction* TickFunction = nullptr) override;` — USkinnedMeshComponent interface
- L103 _private prototype_ `void DebugDraw(const FSceneView* View, FPrimitiveDrawInterface* PDI);` — Debug drawing
- L106 _private prototype_ `FTransform GetPrimitiveTransform(const FTransform& BoneTM, const int32 BodyIndex, const EAggCollisionShape::Type PrimType, const int32 PrimIndex, const float Scale) const;` — Accessors/helper methods
- L107 _private prototype_ `FColor GetPrimitiveColor(const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex) const;`
- L108 _private prototype_ `UMaterialInterface* GetPrimitiveMaterial(const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex) const;`
- L111 _private prototype_ `virtual void Grab(FName InBoneName, const FVector& Location, const FRotator& Rotation, bool bRotationConstrained);` — Manipulator methods
- L112 _private prototype_ `virtual void Ungrab();`
- L113 _private prototype_ `virtual void UpdateHandleTransform(const FTransform& NewTransform);`
- L114 _private prototype_ `virtual void UpdateDriveSettings(bool bLinearSoft, float LinearStiffness, float LinearDamping);`
- L117 _private prototype_ `virtual void CreateSimulationFloor(FBodyInstance* FloorBodyInstance, const FTransform& Transform);` — Sim setup
- L120 _public function_ `virtual bool CanOverrideCollisionProfile() const override`
- L123 _private prototype_ `const FPhysicsAssetEditorDrawState& GetPrimitiveDrawState(const int32 BodyIndex, const EAggCollisionShape::Type PrimitiveType, const int32 PrimitiveIndex) const;`
- L125 _private prototype_ `void UpdateSkinnedLevelSets();`
- L126 _private prototype_ `void UpdateMLLevelSets();`
- L127 _private prototype_ `void UpdateSkinnedTriangleMeshes();`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorSkeletonTreeBuilder.h` (Private)


#### class `FPhysicsAssetEditorSkeletonTreeBuilder`  
`class FPhysicsAssetEditorSkeletonTreeBuilder : public FSkeletonTreeBuilder`  
_L10-36_
- inherits: `FSkeletonTreeBuilder`
- L13 _public prototype_ `FPhysicsAssetEditorSkeletonTreeBuilder(UPhysicsAsset* InPhysicsAsset, const FSkeletonTreeBuilderArgs& InSkeletonTreeBuilderArgs = FSkeletonTreeBuilderArgs(true, false, true, false));`
- L16 _public prototype_ `virtual void Build(FSkeletonTreeBuilderOutput& Output) override;` — ISkeletonTreeBuilder interface
- L17 _public prototype_ `virtual ESkeletonTreeFilterResult FilterItem(const FSkeletonTreeFilterArgs& InArgs, const TSharedPtr<class ISkeletonTreeItem>& InItem) override;`
- L20 _public member_ `bool bShowBodies;` — Flags used for filtering
- L21 _public member_ `bool bShowKinematicBodies;`
- L22 _public member_ `bool bShowSimulatedBodies;`
- L23 _public member_ `bool bShowConstraints;`
- L24 _public member_ `bool bShowConstraintsOnParentBodies;`
- L25 _public member_ `bool bShowCrossConstraints;`
- L26 _public member_ `bool bShowParentChildConstraints;`
- L27 _public member_ `bool bShowPrimitives;`
- L31 _private prototype_ `void AddBodies(FSkeletonTreeBuilderOutput& Output);` — Add bodies & their shapes to the tree
- L35 _private member_ `UPhysicsAsset* PhysicsAsset;` — The physics asset we use to populate the tree

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorToolMenuContext.h` (Private)


#### class `UPhysicsAssetEditorToolMenuContext`  
`class UPhysicsAssetEditorToolMenuContext : public UObject`  
_L11-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<FPhysicsAssetEditor> PhysicsAssetEditor;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetEditorToolsSummoner.h` (Private)


#### struct `FPhysicsAssetEditorToolsSummoner`  
`struct FPhysicsAssetEditorToolsSummoner : public FWorkflowTabFactory`  
_L7-15_
- inherits: `FWorkflowTabFactory`
- L10 _public prototype_ `FPhysicsAssetEditorToolsSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp);`
- L13 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L14 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetConnectionDrawingPolicy.h` (Private)


#### class `FPhysicsAssetConnectionDrawingPolicy`  
`class FPhysicsAssetConnectionDrawingPolicy : public FConnectionDrawingPolicy`  
_L7-23_
- inherits: `FConnectionDrawingPolicy`
- L10 _public function_ `FPhysicsAssetConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements) : FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements)`
- L18 _public function_ `virtual FVector2f ComputeSplineTangent(const FVector2f& Start, const FVector2f& End) const override`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetGraph.h` (Private)


#### class `UPhysicsAssetGraph`  
`class UPhysicsAssetGraph : public UEdGraph`  
_L19-74_
- reflection: `UCLASS()`
- inherits: `UEdGraph`
- L24 _public prototype_ `void Initialize(const TSharedRef<FPhysicsAssetEditor>& InPhysicsAssetEditor, UPhysicsAsset* InPhysicsAsset, const TSharedRef<IEditableSkeleton>& InEditableSkeleton);`
- L27 _public prototype_ `void RebuildGraph();` — Rebuilds graph from selection
- L30 _public prototype_ `void SelectObjects(const TArray<USkeletalBodySetup*>& InBodies, const TArray<UPhysicsConstraintTemplate*>& InConstraints);` — Set the selected bones/constraints
- L33 _public function_ `const TArray<UPhysicsAssetGraphNode_Bone*>& GetRootNodes() const` — Get the root nodes we are displaying
- L36 _public function_ `TSharedRef<FPhysicsAssetEditor> GetPhysicsAssetEditor() const` — Get the physics asset editor we are embedded in
- L39 _public function_ `void RequestRefreshLayout(bool bInRefreshLayout)` — Requests a layout refresh
- L42 _public function_ `bool NeedsRefreshLayout() const` — Get whether a layout refresh was requested
- L45 _public function_ `UPhysicsAsset* GetPhysicsAsset() const` — Get the physics asset we are editing
- L48 _public prototype_ `const UPhysicsAssetGraphSchema* GetPhysicsAssetGraphSchema();` — Get the skeleton graph schema
- L51 _private prototype_ `void ConstructNodes();`
- L54 _private prototype_ `void RemoveAllNodes();` — Removes all nodes from the graph
- L57 _private member_ `TArray<USkeletalBodySetup*> SelectedBodies;`
- L59 _private member_ `TArray<USkeletalBodySetup*> InitiallySelectedBodies;`
- L61 _private member_ `TArray<UPhysicsConstraintTemplate*> SelectedConstraints;`
- L63 _private member_ `TArray<int32> SelectedBodyIndices;`
- L65 _private member_ `TArray<UPhysicsAssetGraphNode_Bone*> RootNodes;`
- L67 _private member_ `TWeakPtr<FPhysicsAssetEditor> WeakPhysicsAssetEditor;`
- L69 _private member_ `TWeakObjectPtr<UPhysicsAsset> WeakPhysicsAsset;`
- L71 _private member_ `TWeakPtr<IEditableSkeleton> WeakEditableSkeleton;`
- L73 _private member_ `bool bRefreshLayout;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetGraphNode.h` (Private)


#### class `UPhysicsAssetGraphNode`  
`class UPhysicsAssetGraphNode : public UEdGraphNode`  
_L16-49_
- reflection: `UCLASS()`
- inherits: `UEdGraphNode`
- L20 _private prototype_ `virtual void SetupPhysicsAssetNode();`
- L21 _private prototype_ `virtual UObject* GetDetailsObject();`
- L23 _private prototype_ `class UPhysicsAssetGraph* GetPhysicsAssetGraph() const;`
- L26 _private prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode implementation
- L27 _private prototype_ `virtual void AllocateDefaultPins() override;`
- L29 _private prototype_ `UEdGraphPin& GetInputPin() const;`
- L31 _private prototype_ `UEdGraphPin& GetOutputPin() const;`
- L33 _private function_ `void SetDimensions(const FVector2D& InDimensions)`
- L34 _private function_ `const FVector2D& GetDimensions() const`
- L39 _protected member_ `FText NodeTitle;` — Cached title for the node
- L42 _protected member_ `UEdGraphPin* InputPin;` — Our one input pin
- L45 _protected member_ `UEdGraphPin* OutputPin;` — Our one output pin
- L48 _protected member_ `FVector2D Dimensions;` — Cached dimensions of this node (used for layout)

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetGraphNode_Bone.h` (Private)


#### class `UPhysicsAssetGraphNode_Bone`  
`class UPhysicsAssetGraphNode_Bone : public UPhysicsAssetGraphNode`  
_L15-44_
- reflection: `UCLASS()`
- inherits: `UPhysicsAssetGraphNode`
- L21 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode implementation
- L24 _public prototype_ `void SetupBoneNode(USkeletalBodySetup* InBodySetup, int32 InBodyIndex, UPhysicsAsset* InPhysicsAsset);` — Setup a node from a bone
- L27 _public prototype_ `void SetParentNode(UPhysicsAssetGraphNode_Bone* ParentNode);` — Setup hierarchy
- L31 _public member_ `int32 BodyIndex;` — Index into body setups in the physics asset
- L34 _public member_ `USkeletalBodySetup* BodySetup;` — The body setup in the physics asset
- L37 _public member_ `UPhysicsAsset* PhysicsAsset;` — The physics asset we are contained in
- L40 _public member_ `UPhysicsAssetGraphNode_Bone* ParentNode;` — Parent node
- L43 _public member_ `TArray<UPhysicsAssetGraphNode_Bone*> Children;` — Child nodes

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetGraphNode_Constraint.h` (Private)


#### class `UPhysicsAssetGraphNode_Constraint`  
`class UPhysicsAssetGraphNode_Constraint : public UPhysicsAssetGraphNode`  
_L12-36_
- reflection: `UCLASS()`
- inherits: `UPhysicsAssetGraphNode`
- L18 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;` — UEdGraphNode implementation
- L21 _public prototype_ `void SetupConstraintNode(UPhysicsConstraintTemplate* InConstraint, int32 InConstraintIndex, UPhysicsAsset* InPhysicsAsset);` — Setup a node from a body
- L23 _public prototype_ `FName GetBoneName1() const;`
- L25 _public prototype_ `FName GetBoneName2() const;`
- L29 _public member_ `int32 ConstraintIndex;` — Index into constraint templates in the physics asset
- L32 _public member_ `UPhysicsConstraintTemplate* Constraint;` — The index of the constraint in the physics asset
- L35 _public member_ `UPhysicsAsset* PhysicsAsset;` — The physics asset we are contained in

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetGraphPanelNodeFactory.h` (Private)


#### class `FPhysicsAssetGraphPanelNodeFactory`  
`class FPhysicsAssetGraphPanelNodeFactory : public FGraphPanelNodeFactory`  
_L10-13_
- inherits: `FGraphPanelNodeFactory`
- L12 _private prototype_ `virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetGraphSchema.h` (Private)


#### class `UPhysicsAssetGraphSchema`  
`class UPhysicsAssetGraphSchema : public UEdGraphSchema`  
_L18-42_
- reflection: `UCLASS()`
- inherits: `UEdGraphSchema`
- L24 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;` — UEdGraphSchema interface
- L25 _public function_ `virtual FName GetParentContextMenuName() const override`
- L26 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L27 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L28 _public prototype_ `virtual void BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const override;`
- L29 _public prototype_ `virtual FPinConnectionResponse MovePinLinks(UEdGraphPin& MoveFromPin, UEdGraphPin& MoveToPin, bool bIsIntermediateMove = false, bool bNotifyLinkedNodes = false) const override;`
- L30 _public prototype_ `virtual FPinConnectionResponse CopyPinLinks(UEdGraphPin& CopyFromPin, UEdGraphPin& CopyToPin, bool bIsIntermediateCopy = false) const override;`
- L31 _public prototype_ `virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L32 _public function_ `virtual bool ShouldAlwaysPurgeOnModification() const override`
- L33 _public prototype_ `virtual FPinConnectionResponse CanCreateNewNodes(UEdGraphPin* InSourcePin) const override;`
- L34 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;`
- L35 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const override;`
- L38 _public prototype_ `virtual UPhysicsAssetGraphNode_Bone* CreateGraphNodesForBone(UPhysicsAssetGraph* InGraph, USkeletalBodySetup* InBodySetup, int32 InBodyIndex, UPhysicsAsset* InPhysicsAsset) const;`
- L39 _public prototype_ `virtual UPhysicsAssetGraphNode_Constraint* CreateGraphNodesForConstraint(UPhysicsAssetGraph* InGraph, UPhysicsConstraintTemplate* InConstraint, int32 InConstraintIndex, UPhysicsAsset* InPhysicsAsset) const;`
- L41 _public prototype_ `virtual void LayoutNodes(UPhysicsAssetGraph* InGraph, UPhysicsAsset* InPhysicsAsset) const;`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/PhysicsAssetGraphSummoner.h` (Private)


#### struct `FPhysicsAssetGraphSummoner`  
`struct FPhysicsAssetGraphSummoner : public FWorkflowTabFactory`  
_L12-32_
- inherits: `FWorkflowTabFactory`
- L15 _public prototype_ `FPhysicsAssetGraphSummoner(TSharedPtr<FAssetEditorToolkit> InHostingApp, UPhysicsAsset* InPhysicsAsset, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, FOnPhysicsAssetGraphCreated InOnPhysicsAssetGraphCreated, FOnGraphObjectsSelected InOnGraphObjectsSelected);`
- L18 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;` — FWorkflowTabFactory interface
- L19 _public prototype_ `virtual TSharedPtr<SToolTip> CreateTabToolTipWidget(const FWorkflowTabSpawnInfo& Info) const override;`
- L22 _public member_ `TWeakObjectPtr<UPhysicsAsset> PhysicsAssetPtr;` — Reference to our Physics Asset
- L25 _public member_ `TWeakPtr<IEditableSkeleton> EditableSkeletonPtr;` — Reference to our editable skeleton
- L28 _public member_ `FOnPhysicsAssetGraphCreated OnPhysicsAssetGraphCreated;` — Graph created delegate
- L31 _public member_ `FOnGraphObjectsSelected OnGraphObjectsSelected;` — Object selected delegate

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/SBoneNode.h` (Private)


#### class `SBoneNode`  
`class SBoneNode : public SPhysicsAssetGraphNode`  
_L7-16_
- inherits: `SPhysicsAssetGraphNode`
- L10 _public function_ `SLATE_BEGIN_ARGS(SBoneNode)`
- L12 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UPhysicsAssetGraphNode_Bone* InNode);`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/SConstraintNode.h` (Private)


#### class `SConstraintNode`  
`class SConstraintNode : public SPhysicsAssetGraphNode`  
_L8-17_
- inherits: `SPhysicsAssetGraphNode`
- L11 _public function_ `SLATE_BEGIN_ARGS(SConstraintNode)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UPhysicsAssetGraphNode_Constraint* InNode);`

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/SPhysicsAssetGraph.h` (Private)


#### class `SPhysicsAssetGraph`  
`class SPhysicsAssetGraph : public SCompoundWidget, public FEditorUndoClient`  
_L26-79_
- inherits: `SCompoundWidget,FEditorUndoClient`
- L29 _public function_ `SLATE_BEGIN_ARGS(SPhysicsAssetGraph)`
- L33 _public prototype_ `~SPhysicsAssetGraph();`
- L36 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L39 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient interface
- L40 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L43 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FPhysicsAssetEditor>& InPhysicsAssetEditor, UPhysicsAsset* InPhysicsAsset, const TSharedRef<IEditableSkeleton>& InEditableSkeleton, FOnGraphObjectsSelected InOnGraphObjectSelected);` — Constructs this widget with InArgs
- L46 _public prototype_ `void SelectObjects(const TArray<USkeletalBodySetup*>& InBodies, const TArray<UPhysicsConstraintTemplate*>& InConstraints);` — Set the selected bodies/constraints
- L51 _private prototype_ `FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2f& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);` — Called to create context menu when right-clicking on graph
- L54 _private prototype_ `void OnSearchBarTextChanged(const FText& NewText);` — Called when the path is being edited
- L57 _private prototype_ `void OnSearchBarTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);` — Sets the new path for the viewer
- L59 _private prototype_ `void RegisterActions();`
- L61 _private prototype_ `void HandleSelectionChanged(const FGraphPanelSelectionSet& SelectionSet);`
- L63 _private prototype_ `void HandleNodeDoubleClicked(UEdGraphNode* InNode);`
- L67 _private member_ `TSharedPtr<SGraphEditor> GraphEditor;`
- L69 _private member_ `UPhysicsAssetGraph* GraphObj;`
- L71 _private member_ `FOnGraphObjectsSelected OnGraphObjectsSelected;`
- L73 _private member_ `bool bZoomToFit;`
- L75 _private member_ `bool bSelecting;`
- L78 _private member_ `int32 BlockSelectionBroadcastCounter;` — As selection broadcasting is deferred in the graph, we need to block re-broadcasting a for a few frames on refresh

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPhysicsAssetGraphCreated, const TSharedRef<SPhysicsAssetGraph>& );` — Delegate used to inform clients of a graph's creation
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPhysicsAssetGraphCreated, const TSharedRef<SPhysicsAssetGraph>& );` — Delegate used to inform clients of a graph's creation
- L24 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGraphObjectsSelected, const TArrayView<UObject*>& );` — Delegate used to communicate graph selection
- L24 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGraphObjectsSelected, const TArrayView<UObject*>& );` — Delegate used to communicate graph selection

### `Source/Editor/PhysicsAssetEditor/Private/PhysicsAssetGraph/SPhysicsAssetGraphNode.h` (Private)


#### class `SPhysicsAssetGraphNode`  
`class SPhysicsAssetGraphNode : public SGraphNode`  
_L16-44_
- inherits: `SGraphNode`
- L19 _public function_ `SLATE_BEGIN_ARGS(SPhysicsAssetGraphNode)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, class UPhysicsAssetGraphNode* InNode);`
- L26 _public prototype_ `void AddSubWidget(const TSharedRef<SWidget>& InWidget);`
- L30 _protected prototype_ `virtual void CreatePinWidgets() override;` — SGraphNode interface
- L31 _protected prototype_ `virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;`
- L32 _protected prototype_ `virtual void UpdateGraphNode() override;`
- L33 _protected prototype_ `virtual const FSlateBrush* GetShadowBrush(bool bSelected) const override;`
- L35 _protected prototype_ `FSlateColor GetNodeColor() const;`
- L36 _protected prototype_ `FText GetNodeTitle() const;`
- L40 _protected member_ `TSharedPtr<SWidget> ContentWidget;` — The content widget for this node - derived classes can insert what they want
- L43 _protected member_ `TSharedPtr<SVerticalBox> SubNodeContent;` — Any sub-nodes are inserted here

### `Source/Editor/PhysicsAssetEditor/Private/SkeletonTreePhysicsBodyItem.h` (Private)


#### class `FSkeletonTreePhysicsBodyItem`  
`class FSkeletonTreePhysicsBodyItem : public FSkeletonTreePhysicsItem`  
_L9-46_
- inherits: `FSkeletonTreePhysicsItem`
- L12 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreePhysicsBodyItem, FSkeletonTreePhysicsItem) FSkeletonTreePhysicsBodyItem(class USkeletalBodySetup* InBodySetup, int32 InBodySetupIndex, const FName& InBoneName, bool bInHasBodySetup, bool bInHasShapes, class UPhysicsAsset* const InPhysicsAsset, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L16 _public prototype_ `virtual UObject* GetObject() const override;`
- L19 _public function_ `int32 GetBodySetupIndex() const` — Get the index of the body setup in the physics asset
- L22 _public prototype_ `virtual void OnToggleItemDisplayed(ECheckBoxState InCheckboxState) override;` — UI Callbacks
- L23 _public prototype_ `virtual ECheckBoxState IsItemDisplayed() const override;`
- L27 _private prototype_ `virtual const FSlateBrush* GetBrush() const override;` — Gets the icon to display for this body
- L30 _private prototype_ `virtual FSlateColor GetTextColor() const override;` — Gets the color to display the item's text
- L33 _private prototype_ `virtual FText GetNameColumnToolTip() const override;` — Gets the tool tip to display on hovering over the item's name
- L36 _private member_ `USkeletalBodySetup* BodySetup;` — The body setup we are representing
- L39 _private member_ `int32 BodySetupIndex;` — The index of the body setup in the physics asset
- L42 _private member_ `bool bHasBodySetup;` — Whether there is a body set up for this bone
- L45 _private member_ `bool bHasShapes;` — Whether this body has shapes

### `Source/Editor/PhysicsAssetEditor/Private/SkeletonTreePhysicsConstraintItem.h` (Private)


#### class `FSkeletonTreePhysicsConstraintItem`  
`class FSkeletonTreePhysicsConstraintItem : public FSkeletonTreePhysicsItem`  
_L11-56_
- inherits: `FSkeletonTreePhysicsItem`
- L14 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreePhysicsConstraintItem, FSkeletonTreePhysicsItem) FSkeletonTreePhysicsConstraintItem(UPhysicsConstraintTemplate* const InConstraint, const int32 InConstraintIndex, const FName& InBoneName, const bool bInIsConstraintOnParentBody, const bool bInIsCrossConstraint, class UPhysicsAsset* const InPhysicsAsset, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L17 _public prototype_ `FSkeletonTreePhysicsConstraintItem(UPhysicsConstraintTemplate* InConstraint, int32 InConstraintIndex, const FName& InBoneName, bool bInIsConstraintOnParentBody, class UPhysicsAsset* const InPhysicsAsset, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L20 _public prototype_ `virtual UObject* GetObject() const override;` — ISkeletonTreeItem interface
- L23 _public function_ `int32 GetConstraintIndex() const` — Get the index of the constraint in the physics asset
- L26 _public function_ `bool IsConstraintOnParentBody() const` — since constraint are showing on both parent and child, gets  if this tree item is the one on the parent body
- L29 _public function_ `bool IsCrossConstraint() const` — True if the bones affected by this constraint are not adjacent (parent/child) in the owning skeleton. Constraints between non-adjacent bones are referred to as 'cross-constraints' and have different icons in the editor.
- L32 _public prototype_ `virtual void OnToggleItemDisplayed(ECheckBoxState InCheckboxState) override;` — UI Callbacks
- L33 _public prototype_ `virtual ECheckBoxState IsItemDisplayed() const override;`
- L37 _private prototype_ `virtual const FSlateBrush* GetBrush() const override;` — Gets the icon to display for this body
- L40 _private prototype_ `virtual FSlateColor GetTextColor() const override;` — Gets the color to display the item's text
- L43 _private prototype_ `virtual FText GetNameColumnToolTip() const override;` — Gets the tool tip to display on hovering over the item's name
- L46 _private member_ `UPhysicsConstraintTemplate* Constraint;` — The constraint we are representing
- L49 _private member_ `int32 ConstraintIndex;` — The index of the body setup in the physics asset
- L52 _private member_ `bool bIsConstraintOnParentBody;` — since constraint are showing on both parent and child, indicates if this tree item is the one on the parent body
- L55 _private member_ `bool bIsCrossConstraint;` — True if the bones affected by this constraint are not adjacent (parent/child) in the owning skeleton. Constraints between non-adjacent bones are referred to as 'cross-constraints' and have different icons in the editor.

### `Source/Editor/PhysicsAssetEditor/Private/SkeletonTreePhysicsItem.h` (Private)


#### class `FSkeletonTreePhysicsItem`  
`class FSkeletonTreePhysicsItem : public FSkeletonTreeItem`  
_L13-48_
- inherits: `FSkeletonTreeItem`
- L16 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreePhysicsItem, FSkeletonTreeItem) FSkeletonTreePhysicsItem(class UPhysicsAsset* const InPhysicsAsset, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L21 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — ISkeletonTreeItem interface
- L22 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected) override;`
- L23 _public function_ `virtual FName GetRowItemName() const override`
- L26 _public prototype_ `virtual void OnToggleItemDisplayed(ECheckBoxState InCheckboxState) = 0;` — UI Callbacks
- L27 _public prototype_ `virtual ECheckBoxState IsItemDisplayed() const = 0;`
- L31 _private prototype_ `virtual const FSlateBrush* GetBrush() const = 0;` — Gets the icon to display for this body
- L34 _private prototype_ `virtual FSlateColor GetTextColor() const = 0;` — Gets the color to display the item's text
- L37 _private prototype_ `virtual FText GetNameColumnToolTip() const = 0;` — Gets the tool tip to display on hovering over the item's name
- L41 _protected prototype_ `struct FPhysicsAssetRenderSettings* GetRenderSettings() const;` — Gets the physics asset render settings for this physics item
- L44 _protected member_ `uint32 PhysicsAssetPathNameHash;` — Unique ID of the physics asset for this physics item
- L47 _protected member_ `FName DisplayName;` — The name of the item in the tree

### `Source/Editor/PhysicsAssetEditor/Private/SkeletonTreePhysicsShapeItem.h` (Private)


#### class `FSkeletonTreePhysicsShapeItem`  
`class FSkeletonTreePhysicsShapeItem : public FSkeletonTreeItem`  
_L16-73_
- inherits: `FSkeletonTreeItem`
- L19 _public prototype_ `SKELETON_TREE_ITEM_TYPE(FSkeletonTreePhysicsShapeItem, FSkeletonTreeItem) FSkeletonTreePhysicsShapeItem(USkeletalBodySetup* InBodySetup, const FName& InBoneName, int32 InBodySetupIndex, EAggCollisionShape::Type InShapeType, int32 InShapeIndex, const TSharedRef<class ISkeletonTree>& InSkeletonTree);`
- L24 _public prototype_ `virtual void GenerateWidgetForNameColumn(TSharedPtr< SHorizontalBox > Box, const TAttribute<FText>& FilterText, FIsSelected InIsSelected) override;` — ISkeletonTreeItem interface
- L25 _public prototype_ `virtual TSharedRef< SWidget > GenerateWidgetForDataColumn(const FName& DataColumnName, FIsSelected InIsSelected ) override;`
- L26 _public prototype_ `virtual FName GetRowItemName() const override;`
- L27 _public prototype_ `virtual UObject* GetObject() const override;`
- L28 _public prototype_ `virtual bool CanRenameItem() const override;`
- L29 _public prototype_ `virtual void RequestRename() override;`
- L30 _public prototype_ `virtual void OnItemDoubleClicked() override;`
- L33 _public function_ `int32 GetBodySetupIndex() const` — Get the index of the body setup in the physics asset
- L36 _public function_ `EAggCollisionShape::Type GetShapeType() const` — Get the shape type of this item
- L39 _public function_ `int32 GetShapeIndex() const` — Get the index of the shape in the physics assets aggregate geom
- L43 _private prototype_ `FText GetNameAsText() const;` — Get the text to display for this item
- L46 _private prototype_ `FString GetNameAsString() const;` — Get the text to display for this item
- L49 _private prototype_ `void HandleTextCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Handle the shape being renamed
- L53 _private prototype_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename
- L54 _private member_ `FOnRenameRequested OnRenameRequested;`
- L57 _private member_ `USkeletalBodySetup* BodySetup;` — The body setup we are representing part of
- L60 _private member_ `FName DefaultLabel;` — The label we display in the tree
- L63 _private member_ `int32 BodySetupIndex;` — The index of the body setup in the physics asset
- L66 _private member_ `EAggCollisionShape::Type ShapeType;` — The kind of shape we represent
- L69 _private member_ `int32 ShapeIndex;` — The index into the relevant body setup array for this shape
- L72 _private member_ `const FSlateBrush* ShapeBrush;` — The brush to use for this shape

#### Free symbols / members of external scopes

- L53 _delegate_ `DECLARE_DELEGATE(FOnRenameRequested);` — Delegate for when the context menu requests a rename

### `Source/Editor/PhysicsAssetEditor/Private/ViewportInteractions/PhysicsAssetSimInteraction.h` (Private)


#### class `UPhysicsAssetSimInteraction`  
`class UPhysicsAssetSimInteraction : public UViewportDragInteraction , public IMouseWheelBehaviorTarget`  
_L18-67_
- reflection: `UCLASS(Transient)`
- inherits: `UViewportDragInteraction,IMouseWheelBehaviorTarget`
- desc: Viewport interaction for the Physics Asset Editor simulation mode. Handles Ctrl+RMB grab (drag body with physics handle), Ctrl+LMB poke (apply impulse), and Ctrl+scroll wheel (adjust grab distance).
- L25 _public prototype_ `UPhysicsAssetSimInteraction();`
- L27 _public prototype_ `virtual bool CanBeActivated() const override;`
- L28 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L29 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`
- L30 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L31 _public prototype_ `virtual void OnStateUpdated(const FInputDeviceState& InInputDeviceState) override;`
- L34 _public prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& CurrentPos) override;`
- L35 _public prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& CurrentPos) override;`
- L36 _public prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& CurrentPos) override;`
- L40 _public prototype_ `void SetEditMode(FPhysicsAssetEditorEditMode* InEditMode);` — Set by the edit mode during registration.
- L43 _private prototype_ `FPhysicsAssetEditorSharedData* GetSharedData() const;`
- L46 _private member_ `FPhysicsAssetEditorEditMode* EditMode = nullptr;`
- L49 _private member_ `bool bIsRightMouseDown = false;` — Whether RMB is currently held, determines drag vs pulse.
- L52 _private member_ `float SimGrabPush = 0.0f;` — Simulation grab state
- L53 _private member_ `float SimGrabMinPush = 0.0f;`
- L54 _private member_ `FVector SimGrabLocation = FVector::ZeroVector;`
- L55 _private member_ `FVector SimGrabX = FVector::ZeroVector;`
- L56 _private member_ `FVector SimGrabY = FVector::ZeroVector;`
- L57 _private member_ `FVector SimGrabZ = FVector::ZeroVector;`
- L59 _private member_ `float DragX = 0.0f;`
- L60 _private member_ `float DragY = 0.0f;`
- L63 _private member_ `bool bIsGrabbing = false;` — Whether the current drag is a grab (RMB) vs poke (LMB).
- L65 _private member_ `static constexpr float SimHoldDistanceChangeDelta = 20.0f;`
- L66 _private member_ `static constexpr float SimMinHoldDistance = 10.0f;`

### `Source/Editor/PhysicsAssetEditor/Public/IPhysicsAssetEditor.h` (Public)


#### class `IPhysicsAssetEditor`  
`class IPhysicsAssetEditor : public FPersonaAssetEditorToolkit, public IHasPersonaToolkit`  
_L18-37_
- inherits: `FPersonaAssetEditorToolkit,IHasPersonaToolkit`
- L22 _public prototype_ `virtual TArray<int32> GetSelectedBodyIndices() const = 0;` — Get the body indices of the currently selected bodies.
- L25 _public prototype_ `virtual TArray<int32> GetSelectedConstraintIndices() const = 0;` — Get the constraint indices currently selected.
- L33 _public prototype_ `virtual void ModifySelection(EPhysicsAssetEditorSelection ElementType, const TArray<int32>& Indices, bool bAddToSelection) = 0;` — Add or remove elements from the selection. For Body/CenterOfMass: Indices are body indices. For Bone: Indices are skeleton bone indices. For Constraint: Indices are constraint indices. For primitive types (PrimitiveCapsule, Primitive, etc.): Indices are body indices; the specific enum value determines which shape types are selected within those bodies.
- L36 _public prototype_ `virtual void ClearSelection() = 0;` — Clear all selection (bodies, constraints, primitives, center of mass, bones).

#### class `IPhysicsAssetEditorOverride`  
`class IPhysicsAssetEditorOverride : public IModularFeature`  
_L39-45_
- inherits: `IModularFeature`
- L42 _public member_ `static const inline FName ModularFeatureName = "Ph`
- L44 _public prototype_ `virtual bool OpenAsset(UPhysicsAsset*) = 0;`

### `Source/Editor/PhysicsAssetEditor/Public/PhysicsAssetEditorModule.h` (Public)


#### class `IPhysicsAssetEditorModule`  
`class IPhysicsAssetEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L21-33_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- L26 _public prototype_ `virtual TSharedRef<IPhysicsAssetEditor> CreatePhysicsAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, UPhysicsAsset* PhysicsAsset) = 0;` — Creates a new PhysicsAssetEditor instance
- L29 _public prototype_ `virtual FOnPhysicsAssetEditorCreated& OnPhysicsAssetEditorCreated() = 0;` — Delegate called when a physics asset editor is created
- L32 _public prototype_ `virtual void OpenNewBodyDlg(EAppReturnType::Type* NewBodyResponse) = 0;` — Opens a "New Asset/Body" modal dialog window

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsAssetEditor, Log, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPhysicsAssetEditor, Log, All);`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhysicsAssetEditorCreated, const TSharedRef<IPhysicsAssetEditor>& );` — Delegate called when a physics asset editor is created
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhysicsAssetEditorCreated, const TSharedRef<IPhysicsAssetEditor>& );` — Delegate called when a physics asset editor is created

### `Source/Editor/PhysicsAssetEditor/Public/PhysicsAssetEditorSelectionType.h` (Public)


#### enum `EPhysicsAssetEditorSelection`  
`enum class EPhysicsAssetEditorSelection : int32`  
_L11-34_
- desc: Element types in the Physics Asset Editor selection system. Individual primitive types allow shape-specific selection via ModifySelection.
- L13 _public enumerator_ `None = 0`
- L14 _public enumerator_ `Body = 1 << 0`
- L15 _public enumerator_ `CenterOfMass = 1 << 1`
- L16 _public enumerator_ `Constraint = 1 << 2`
- L17 _public enumerator_ `Primitive = 1 << 3`
- L18 _public enumerator_ `Bone = 1 << 4`
- L21 _public enumerator_ `PrimitiveSphere = 1 << 5` — Individual primitive types (for shape-specific selection)
- L22 _public enumerator_ `PrimitiveBox = 1 << 6`
- L23 _public enumerator_ `PrimitiveCapsule = 1 << 7` — Maps to EAggCollisionShape::Sphyl
- L24 _public enumerator_ `PrimitiveConvex = 1 << 8`
- L25 _public enumerator_ `PrimitiveTaperedCapsule = 1 << 9`
- L26 _public enumerator_ `PrimitiveLevelSet = 1 << 10`
- L27 _public enumerator_ `PrimitiveSkinnedLevelSet = 1 << 11`
- L30 _public enumerator_ `AllPrimitive = PrimitiveSphere | PrimitiveBox | PrimitiveCapsule | PrimitiveConvex | PrimitiveTaperedCapsule | PrimitiveLevelSet | PrimitiveSkinnedLevelSet` — Combined: all primitive types
- L33 _public enumerator_ `All = ~None`

#### Free symbols / members of external scopes

- L36 _function_ `static constexpr std::underlying_type_t<EPhysicsAssetEditorSelection> UnderlyingType(const EPhysicsAssetEditorSelection SelectionType)`
