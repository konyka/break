# Editor / LevelEditor

- module root: `Source/Editor/LevelEditor`
- headers: 52; symbols: 2163
- symbol kinds: class=61, delegate=29, enum=10, enumerator=38, externvar=1, function=160, macro=15, member=630, namespace=17, prototype=1163, struct=9, typedef=18, variable=12
- DynamicallyLoadedModuleNames: AssetTools, AutomationWindow, ClassViewer, DeviceManager, DeviceProfileEditor, HeadMountedDisplay, Layers, MainFrame, MergeActors, NewLevelDialog, Persona, PlacementMode, SessionFrontend, SettingsEditor, SlateReflector, VREditor, WorkspaceMenuStructure, WorldBrowser, WorldPartitionEditor
- PrivateDependencyModuleNames: ActionableMessage, ActorPickerMode, Analytics, AppFramework, ApplicationCore, CommonMenuExtensions, ContentBrowser, Core, CoreUObject, DataLayerEditor, DerivedDataEditor, DerivedDataWidgets, DesktopPlatform, DeveloperSettings, DeviceProfileServices, EditorFramework, EditorInteractiveToolsFramework, EditorSubsystem, EditorWidgets, Engine, EngineSettings, EnvironmentLightingViewer, Foliage, HierarchicalLODOutliner, HierarchicalLODUtilities, InputCore, InteractiveToolsFramework, Json, JsonUtilities, KismetWidgets, LauncherPlatform, LevelSequence, MaterialShaderQualitySettings, MessageLog, PixelInspectorModule, Projects, PropertyEditor, RHI, RenderCore, SceneOutliner, Slate, SlateCore, SourceControl, SourceControlWindows, StatsViewer, StatusBar, SubobjectDataInterface, SubobjectEditor, ToolMenus, ToolWidgets, TranslationEditor, TypedElementFramework, TypedElementRuntime, UncontrolledChangelists, UnrealEd, UnsavedAssetsTracker, ZenEditor
- PrivateIncludePathModuleNames: AssetTools, ClassViewer, Layers, LiveCoding, LocalizationDashboard, MainFrame, MergeActors, NewLevelDialog, PlacementMode, PortalServices, SlateReflector, TurnkeySupport, WorldBrowser
- PublicIncludePathModuleNames: CommonMenuExtensions, Settings, ToolWidgets, UnrealEd, VREditor

### `Source/Editor/LevelEditor/Private/ActorDetailsSCSEditorUICustomization.h` (Private)


#### class `FActorDetailsSCSEditorUICustomization`  
`class FActorDetailsSCSEditorUICustomization final : public ISCSEditorUICustomization`  
_L9-50_
- inherits: `ISCSEditorUICustomization`
- L14 _public prototype_ `static TSharedPtr<FActorDetailsSCSEditorUICustomization> NewInstance();`
- L16 _public prototype_ `explicit FActorDetailsSCSEditorUICustomization(FPrivateToken);`
- L17 _public function_ `virtual ~FActorDetailsSCSEditorUICustomization() override`
- L19 _public prototype_ `virtual bool HideComponentsTree(TArrayView<UObject*> Context) const override;`
- L21 _public prototype_ `virtual bool HideComponentsFilterBox(TArrayView<UObject*> Context) const override;`
- L23 _public prototype_ `virtual bool HideAddComponentButton(TArrayView<UObject*> Context) const override;`
- L25 _public prototype_ `virtual bool HideBlueprintButtons(TArrayView<UObject*> Context) const override;`
- L27 _public prototype_ `virtual const FSlateBrush* GetIconBrush(const FSubobjectData&) const override;`
- L28 _public prototype_ `virtual TSharedPtr<SWidget> GetControlsWidget(TSharedRef<SSubobjectEditor>&, const FSubobjectData&) const override;`
- L29 _public prototype_ `virtual bool OverrideDesiredVisibility(const UE::Editor::FSubobjectEditorContext& Context, EVisibility& VisibilityOut) const;`
- L31 _public prototype_ `virtual EChildActorComponentTreeViewVisualizationMode GetChildActorVisualizationMode() const override;`
- L33 _public prototype_ `virtual TSubclassOf<UActorComponent> GetComponentTypeFilter(TArrayView<UObject*> Context) const override;`
- L35 _public prototype_ `virtual bool FilterSubobjectData(TArray<FSubobjectDataHandle>& SubobjectData) const override;`
- L37 _public prototype_ `virtual void PrePotentialTargetChange(SSubobjectEditor& SubobjectEditor) override;`
- L38 _public prototype_ `virtual bool SelectDefaultSubobject(SSubobjectEditor& SubobjectEditor) override;`
- L40 _public prototype_ `virtual bool SupportsTreeViewOverlay(const SSubobjectEditor& Editor) const override;`
- L41 _public prototype_ `virtual TSharedRef<SWidget> ConstructTreeViewOverlay(TWeakPtr<SSubobjectEditor> Editor) const override;`
- L43 _public prototype_ `void AddCustomization(TSharedPtr<ISCSEditorUICustomization> Customization);`
- L44 _public prototype_ `void RemoveCustomization(TSharedPtr<ISCSEditorUICustomization> Customization);`
- L47 _private function_ `FActorDetailsSCSEditorUICustomization()`
- L49 _private member_ `TArray<TSharedPtr<ISCSEditorUICustomization>> Customizations;`

#### struct `FActorDetailsSCSEditorUICustomization::FPrivateToken`  
`struct FPrivateToken`  
_L12-12_
- L12 _public prototype_ `struct FPrivateToken`

### `Source/Editor/LevelEditor/Private/Elements/Actor/ActorElementLevelEditorCommonActionsCustomization.h` (Private)


#### class `FActorElementLevelEditorCommonActionsCustomization`  
`class FActorElementLevelEditorCommonActionsCustomization : public FTypedElementCommonActionsCustomization, public FTypedElementAssetEditorToolkitHostMixin`  
_L8-23_
- inherits: `FTypedElementCommonActionsCustomization,FTypedElementAssetEditorToolkitHostMixin`
- L10 _private typedef_ `using Super = FTypedElementCommonActionsCustomization;`
- L12 _public prototype_ `virtual bool IsCopyCapable() const override;`
- L13 _public prototype_ `virtual bool CanCopyElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles) override;`
- L14 _public prototype_ `virtual void CopyElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, FOutputDevice& Out) override;`
- L15 _public prototype_ `virtual void CutElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, UWorld* InWorld, UTypedElementSelectionSet* InSelectionSet, const FTypedElementDeletionOptions& InDeletionOptions, FOutputDevice& Out) override;`
- L18 _public prototype_ `virtual bool DeleteElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, UWorld* InWorld, UTypedElementSelectionSet* InSelectionSet, const FTypedElementDeletionOptions& InDeletionOptions) override;`
- L19 _public prototype_ `virtual void DuplicateElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, UWorld* InWorld, const FVector& InLocationOffset, TArray<FTypedElementHandle>& OutNewElements) override;`
- L20 _public prototype_ `virtual TSharedPtr<FWorldElementPasteImporter> GetPasteImporter(ITypedElementWorldInterface* InWorldInterface, const FTypedElementListConstPtr& InSelectedHandles, UWorld* InWorld) override;`

### `Source/Editor/LevelEditor/Private/Elements/Actor/ActorElementLevelEditorSelectionCustomization.h` (Private)


#### class `FActorElementLevelEditorSelectionCustomization`  
`class FActorElementLevelEditorSelectionCustomization : public FTypedElementSelectionCustomization, public FTypedElementAssetEditorToolkitHostMixin`  
_L10-31_
- inherits: `FTypedElementSelectionCustomization,FTypedElementAssetEditorToolkitHostMixin`
- L13 _public prototype_ `virtual bool CanSelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L14 _public prototype_ `virtual bool CanDeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L15 _public prototype_ `virtual bool SelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L16 _public prototype_ `virtual bool DeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L17 _public prototype_ `virtual bool AllowSelectionModifiers(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet) override;`
- L18 _public prototype_ `virtual FTypedElementHandle GetSelectionElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod) override;`
- L19 _public prototype_ `virtual void GetNormalizedElements(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet, const FTypedElementSelectionNormalizationOptions& InNormalizationOptions, FTypedElementListRef OutNormalizedElements) override;`
- L21 _public prototype_ `bool CanSelectActorElement(const TTypedElement<ITypedElementSelectionInterface>& InActorSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) const;`
- L22 _public prototype_ `bool CanDeselectActorElement(const TTypedElement<ITypedElementSelectionInterface>& InActorSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) const;`
- L24 _public prototype_ `bool SelectActorElement(const TTypedElement<ITypedElementSelectionInterface>& InActorSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);`
- L25 _public prototype_ `bool DeselectActorElement(const TTypedElement<ITypedElementSelectionInterface>& InActorSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);`
- L27 _public prototype_ `bool SelectActorGroup(AGroupActor* InGroupActor, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions, const bool bForce);`
- L28 _public prototype_ `bool DeselectActorGroup(AGroupActor* InGroupActor, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions, const bool bForce);`
- L30 _public prototype_ `static void AppendNormalizedActors(AActor* InActor, FTypedElementListConstRef InSelectionSet, const FTypedElementSelectionNormalizationOptions& InNormalizationOptions, FTypedElementListRef OutNormalizedElements);`

### `Source/Editor/LevelEditor/Private/Elements/ActorFolder/ActorFolderElementLevelEditorCommonActionsCustomization.h` (Private)


#### class `FActorFolderElementLevelEditorCommonActionsCustomization`  
`class FActorFolderElementLevelEditorCommonActionsCustomization : public FTypedElementCommonActionsCustomization, public FTypedElementAssetEditorToolkitHostMixin`  
_L8-13_
- inherits: `FTypedElementCommonActionsCustomization,FTypedElementAssetEditorToolkitHostMixin`
- L10 _private typedef_ `using Super = FTypedElementCommonActionsCustomization;`
- L12 _public prototype_ `virtual bool IsCopyCapable() const override;`

### `Source/Editor/LevelEditor/Private/Elements/CommonActions/LevelEditorCommonActions.h` (Private)


#### class `ULevelEditorCommonActions`  
`class ULevelEditorCommonActions : public UTypedElementCommonActions`  
_L13-28_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UTypedElementCommonActions`
- desc: Specific override of UTypedElementCommonActions for the Level Editor, mainly to handle interop with the new TEv1 support for folders and the legacy copy/paste for actors
- L17 _public prototype_ `virtual ~ULevelEditorCommonActions() override = default;`
- L18 _public prototype_ `virtual TArray<FTypedElementHandle> DuplicateNormalizedElements(const FTypedElementListConstPtr& ElementListPtr, UWorld* World, const FVector& LocationOffset) override;`
- L19 _public prototype_ `virtual TArray<FTypedElementHandle> PasteNormalizedElements(const FTypedElementListConstPtr& ElementListPtr, UWorld* World, const FTypedElementPasteOptions& PasteOptions, const FString* OptionalInputString = nullptr) override;`
- L24 _protected prototype_ `void FixupFolderDataPostDuplicate(const TArray<FTypedElementHandle>& DuplicatedElements) const;` — If a folder and an actor contained in it are both selected and duplicated (or pasted), the duplicated actor will end up in the original folder instead of the duplicated one. So we need some post duplicate/paste fixup to handle this case.
- L27 _protected member_ `TSet<FFolder> DuplicateFoldersCache;`

### `Source/Editor/LevelEditor/Private/Elements/Component/ComponentElementLevelEditorCommonActionsCustomization.h` (Private)


#### class `FComponentElementLevelEditorCommonActionsCustomization`  
`class FComponentElementLevelEditorCommonActionsCustomization : public FTypedElementCommonActionsCustomization, public FTypedElementAssetEditorToolkitHostMixin`  
_L8-20_
- inherits: `FTypedElementCommonActionsCustomization,FTypedElementAssetEditorToolkitHostMixin`
- L10 _private typedef_ `using Super = FTypedElementCommonActionsCustomization;`
- L12 _public prototype_ `virtual bool IsCopyCapable() const override;`
- L13 _public prototype_ `virtual bool CanCopyElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles) override;`
- L14 _public prototype_ `virtual void CopyElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, FOutputDevice& Out) override;`
- L15 _public prototype_ `virtual bool DeleteElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, UWorld* InWorld, UTypedElementSelectionSet* InSelectionSet, const FTypedElementDeletionOptions& InDeletionOptions) override;`
- L16 _public prototype_ `virtual void DuplicateElements(ITypedElementWorldInterface* InWorldInterface, TArrayView<const FTypedElementHandle> InElementHandles, UWorld* InWorld, const FVector& InLocationOffset, TArray<FTypedElementHandle>& OutNewElements) override;`
- L17 _public prototype_ `virtual TSharedPtr<FWorldElementPasteImporter> GetPasteImporter(ITypedElementWorldInterface* InWorldInterface, const FTypedElementListConstPtr& InSelectedHandles, UWorld* InWorld) override;`

### `Source/Editor/LevelEditor/Private/Elements/Component/ComponentElementLevelEditorSelectionCustomization.h` (Private)


#### class `FComponentElementLevelEditorSelectionCustomization`  
`class FComponentElementLevelEditorSelectionCustomization : public FTypedElementSelectionCustomization, public FTypedElementAssetEditorToolkitHostMixin`  
_L8-25_
- inherits: `FTypedElementSelectionCustomization,FTypedElementAssetEditorToolkitHostMixin`
- L11 _public prototype_ `virtual bool CanSelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L12 _public prototype_ `virtual bool CanDeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L13 _public prototype_ `virtual bool SelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L14 _public prototype_ `virtual bool DeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L15 _public prototype_ `virtual FTypedElementHandle GetSelectionElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod) override;`
- L16 _public prototype_ `virtual void GetNormalizedElements(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet, const FTypedElementSelectionNormalizationOptions& InNormalizationOptions, FTypedElementListRef OutNormalizedElements) override;`
- L18 _public prototype_ `bool CanSelectComponentElement(const TTypedElement<ITypedElementSelectionInterface>& InComponentSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) const;`
- L19 _public prototype_ `bool CanDeselectComponentElement(const TTypedElement<ITypedElementSelectionInterface>& InComponentSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) const;`
- L21 _public prototype_ `bool SelectComponentElement(const TTypedElement<ITypedElementSelectionInterface>& InComponentSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);`
- L22 _public prototype_ `bool DeselectComponentElement(const TTypedElement<ITypedElementSelectionInterface>& InComponentSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions);`
- L24 _public prototype_ `static FTypedElementHandle GetSelectionElementStatic(const FTypedElementHandle& InComponentHandle, FTypedElementListConstRef InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod);`

### `Source/Editor/LevelEditor/Private/Elements/SMInstance/SMInstanceElementLevelEditorSelectionCustomization.h` (Private)


#### class `FSMInstanceElementLevelEditorSelectionCustomization`  
`class FSMInstanceElementLevelEditorSelectionCustomization : public FTypedElementSelectionCustomization, public FTypedElementAssetEditorToolkitHostMixin`  
_L8-20_
- inherits: `FTypedElementSelectionCustomization,FTypedElementAssetEditorToolkitHostMixin`
- L11 _public prototype_ `virtual bool CanSelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L12 _public prototype_ `virtual bool CanDeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L13 _public prototype_ `virtual bool SelectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L14 _public prototype_ `virtual bool DeselectElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListRef InSelectionSet, const FTypedElementSelectionOptions& InSelectionOptions) override;`
- L15 _public prototype_ `virtual FTypedElementHandle GetSelectionElement(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InCurrentSelection, const ETypedElementSelectionMethod InSelectionMethod) override;`
- L16 _public prototype_ `virtual bool AllowSelectionModifiers(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet) override;`
- L18 _private prototype_ `static bool HasSMInstanceSelectionInSameComponent(const TTypedElement<ITypedElementSelectionInterface>& InElementSelectionHandle, FTypedElementListConstRef InSelectionSet);`
- L19 _private member_ `bool bCameFromSecondary = false;`

### `Source/Editor/LevelEditor/Private/HighresScreenshotUI.h` (Private)


#### class `SHighResScreenshotDialog`  
`class SHighResScreenshotDialog : public SCompoundWidget`  
_L22-217_
- inherits: `SCompoundWidget`
- L25 _public function_ `SLATE_BEGIN_ARGS( SHighResScreenshotDialog )`
- L26 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L30 _public prototype_ `SHighResScreenshotDialog();`
- L32 _public function_ `virtual ~SHighResScreenshotDialog()`
- L37 _public function_ `void SetWindow( TSharedPtr<SWindow> InWindow )`
- L42 _public function_ `void SetCaptureRegionWidget(TSharedPtr<class SCaptureRegionWidget> InCaptureRegionWidget)`
- L47 _public function_ `void SetCaptureRegion(const FIntRect& InCaptureRegion)`
- L57 _public function_ `FHighResScreenshotConfig& GetConfig()`
- L62 _public function_ `TSharedPtr<class SCaptureRegionWidget> GetCaptureRegionWidget()`
- L67 _public prototype_ `static TWeakPtr<class SWindow> OpenDialog(const TSharedPtr<FSceneViewport>& InViewport, TSharedPtr<SCaptureRegionWidget> InCaptureRegionWidget = TSharedPtr<class SCaptureRegionWidget>());`
- L70 _private prototype_ `EVisibility GetCaptureWarningVisibility() const;`
- L72 _private prototype_ `FReply OnOpenScreenshotFolder();`
- L73 _private prototype_ `FReply OnCaptureClicked();`
- L74 _private prototype_ `FReply OnSelectCaptureRegionClicked();`
- L75 _private prototype_ `FReply OnSelectCaptureCancelRegionClicked();`
- L76 _private prototype_ `FReply OnSelectCaptureAcceptRegionClicked();`
- L77 _private prototype_ `FReply OnSetFullViewportCaptureRegionClicked();`
- L78 _private prototype_ `FReply OnSetCameraSafeAreaCaptureRegionClicked();`
- L80 _private prototype_ `bool IsSetCameraSafeAreaCaptureRegionEnabled() const;`
- L82 _private function_ `void OnResolutionMultiplierSliderChanged( float NewValue )`
- L90 _private function_ `void OnMaskEnabledChanged( ECheckBoxState NewValue )`
- L101 _private function_ `void OnHDREnabledChanged(ECheckBoxState NewValue)`
- L111 _private function_ `void OnForce128BitRenderingChanged(ECheckBoxState NewValue)`
- L121 _private function_ `void OnDateTimeBasedNamingEnabledChanged(ECheckBoxState NewValue)`
- L127 _private function_ `void OnBufferVisualizationDumpEnabledChanged(ECheckBoxState NewValue)`
- L135 _private function_ `EVisibility GetSpecifyCaptureRegionVisibility() const`
- L140 _private function_ `EVisibility GetCaptureRegionControlsVisibility() const`
- L145 _private function_ `void SetCaptureRegionControlsVisibility(bool bVisible)`
- L150 _private function_ `float GetResolutionMultiplierSlider() const`
- L155 _private function_ `ECheckBoxState GetMaskEnabled() const`
- L160 _private function_ `ECheckBoxState GetHDRCheckboxUIState() const`
- L165 _private function_ `ECheckBoxState GetForce128BitRenderingCheckboxUIState() const`
- L170 _private function_ `ECheckBoxState GetBufferVisualizationDumpEnabled() const`
- L175 _private function_ `ECheckBoxState GetDateTimeBasedNamingEnabled() const`
- L180 _private function_ `bool IsCaptureRegionEditingAvailable() const`
- L185 _private function_ `void SetHDRUIEnableState(bool bEnable)`
- L191 _private function_ `void SetForce128BitRenderingState(bool bEnable)`
- L197 _private prototype_ `static void WindowClosedHandler(const TSharedRef<SWindow>& InWindow);`
- L199 _private prototype_ `static void ResetViewport();`
- L200 _private prototype_ `static void ResetFrameBuffer();`
- L202 _private member_ `TSharedPtr<SWindow> Window;`
- L203 _private member_ `TSharedPtr<class SCaptureRegionWidget> CaptureRegionWidget;`
- L204 _private member_ `TSharedPtr<SButton> CaptureRegionButton;`
- L205 _private member_ `TSharedPtr<SHorizontalBox> RegionCaptureActiveControlRoot;`
- L206 _private member_ `TSharedPtr<SCheckBox> HDRCheckBox;`
- L207 _private member_ `TSharedPtr<STextBlock> HDRLabel;`
- L208 _private member_ `TSharedPtr<SCheckBox> Force128BitRenderingCheckBox;`
- L209 _private member_ `TSharedPtr<STextBlock> Force128BitRenderingLabel;`
- L211 _private member_ `FHighResScreenshotConfig& Config;`
- L212 _private member_ `bool bCaptureRegionControlsVisible;`
- L214 _private member_ `static TWeakPtr<SWindow> CurrentWindow;`
- L215 _private member_ `static TWeakPtr<SHighResScreenshotDialog> CurrentDialog;`
- L216 _private member_ `static bool bMaskVisualizationWasEnabled;`

### `Source/Editor/LevelEditor/Private/LevelEditorCreateActorMenu.h` (Private)


#### enum `EActorCreateMode::Type`  
`enum Type`  
_L16-24_
- L19 _public enumerator_ `Add` — Add the actor at the last click location
- L22 _public enumerator_ `Replace` — Replace the actor that was last clicked on

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace EActorCreateMode`
- L27 _namespace_ `namespace LevelEditorCreateActorMenu`
- L33 _prototype_ `void FillAddReplaceContextMenuSections(FToolMenuSection& Section, ULevelEditorContextMenuContext* LevelEditorMenuContext);` (scope `LevelEditorCreateActorMenu`) — Fill the context menu section(s) for adding or replacing an actor in the viewport @param	Section		The tool menu section to which entries are added
- L39 _prototype_ `void FillAddReplaceActorMenu(UToolMenu* Menu, EActorCreateMode::Type CreateMode);` (scope `LevelEditorCreateActorMenu`) — Fill the context menu for adding or replacing an actor. Used for in-viewport and level editor toolbar menus. @param	MenuBuilder		The menu builder used to generate the context menu

### `Source/Editor/LevelEditor/Private/LevelEditorGenericDetails.h` (Private)


#### class `FLevelEditorGenericDetails`  
`class FLevelEditorGenericDetails : public IDetailCustomization`  
_L14-38_
- inherits: `IDetailCustomization`
- desc: Creates details for the level editor details view that are not specific to any selected actor type
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails( class IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L27 _private prototype_ `void AddSurfaceDetails( class IDetailLayoutBuilder& DetailLayout );` — Adds a section for selected surface details
- L32 _private prototype_ `void GetSelectedSurfaceMaterials(IMaterialListBuilder& MaterialList) const;` — Populate the specified material list with the materials used on the currently selected BSP surfaces
- L37 _private prototype_ `void OnMaterialChanged( UMaterialInterface* NewMaterial, UMaterialInterface* PrevMaterial, int32 SlotIndex, bool bReplaceAll );` — Called when the material should be changed on all selected BSP surfaces

### `Source/Editor/LevelEditor/Private/LevelEditorInternalTools.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace InternalEditorLevelLibrary`
- L16 _prototype_ `TSharedPtr<SLevelViewport> GetLevelViewport(const FName& ViewportConfigKey);` (scope `InternalEditorLevelLibrary`)
- L17 _prototype_ `TSharedPtr<SLevelViewport> GetActiveLevelViewport();` (scope `InternalEditorLevelLibrary`)
- L18 _prototype_ `bool IsEditingLevelInstanceCurrentLevel(UWorld* InWorld);` (scope `InternalEditorLevelLibrary`)
- L19 _prototype_ `AActor* GetEditingLevelInstance(UWorld* InWorld);` (scope `InternalEditorLevelLibrary`)
- L20 _prototype_ `bool IsActorEditorContextVisible(UWorld* InWorld);` (scope `InternalEditorLevelLibrary`)
- L25 _prototype_ `bool DoesDetailSelectionContainNonActorsOrComponents(const UTypedElementSelectionSet* SelectionSet);` (scope `InternalEditorLevelLibrary`) — When converted to objects that would be given to the detail panel, does the selection contain anything that is not an actor or component?

### `Source/Editor/LevelEditor/Private/LevelEditorMenu.h` (Private)


#### class `FLevelEditorMenu`  
`class FLevelEditorMenu`  
_L14-30_
- desc: Level editor menu
- L19 _public prototype_ `static void RegisterLevelEditorMenus();`
- L26 _public prototype_ `static TSharedRef< SWidget > MakeLevelEditorMenu( const TSharedPtr<FUICommandList>& CommandList, TSharedPtr<class SLevelEditor> LevelEditor );` — Static: Creates a widget for the level editor's menu @return	New widget
- L28 _private prototype_ `static void RegisterBuildMenu();`
- L29 _private prototype_ `static void RegisterSelectMenu();`

### `Source/Editor/LevelEditor/Private/LevelEditorToolBar.h` (Private)


#### class `FLevelEditorToolBar`  
`class FLevelEditorToolBar`  
_L16-104_
- desc: Unreal level editor main toolbar
- L26 _public prototype_ `static TSharedRef< SWidget > MakeLevelEditorToolBar( const TSharedRef<FUICommandList>& InCommandList, const TSharedRef<SLevelEditor> InLevelEditor );` — Static: Creates a widget for the main tool bar @return	New widget
- L27 _public prototype_ `static void RegisterLevelEditorToolBar( const TSharedRef<FUICommandList>& InCommandList, const TSharedRef<SLevelEditor> InLevelEditor );`
- L34 _public prototype_ `static TSharedRef< SWidget > MakeLevelEditorSecondaryModeToolbar(TSharedRef<FUICommandList> InCommandList, TMap<FName, TSharedPtr<FLevelEditorModeUILayer>>& ModeUILayers );` — Static: Creates a widget for the secondary tool bar which is displayed below the main toolbar @return	New widget
- L35 _public prototype_ `static void RegisterLevelEditorSecondaryModeToolbar();`
- L36 _public prototype_ `static FName GetSecondaryModeToolbarName();`
- L45 _protected prototype_ `static TSharedRef< SWidget > GenerateBuildMenuContent(TSharedRef<FUICommandList> InCommandList, TWeakPtr<SLevelEditor> InLevelEditor);` — Generates menu content for the build combo button drop down menu @return	Menu content widget
- L52 _protected prototype_ `static TSharedRef< SWidget > GenerateQuickSettingsMenu(TSharedRef<FUICommandList> InCommandList, TWeakPtr<SLevelEditor> InLevelEditor);` — Generates menu content for the quick settings combo button drop down menu @return	Menu content widget
- L59 _protected prototype_ `static TSharedRef< SWidget > GenerateSourceControlMenu(TSharedRef<FUICommandList> InCommandList, TWeakPtr<SLevelEditor> InLevelEditor);` — Generates menu content for the source control combo button drop down menu @return	Menu content widget
- L66 _protected prototype_ `static TSharedRef< SWidget > GenerateOpenBlueprintMenuContent(TSharedRef<FUICommandList> InCommandList, TWeakPtr<SLevelEditor> InLevelEditor);` — Generates menu content for the compile combo button drop down menu @return	Menu content widget
- L73 _protected prototype_ `static TSharedRef< SWidget > GenerateCinematicsMenuContent(TSharedRef<FUICommandList> InCommandList, TWeakPtr<SLevelEditor> InLevelEditor);` — Generates menu content for the Cinematics combo button drop down menu @return	Menu content widget
- L75 _protected prototype_ `static TSharedRef< SWidget > GenerateAddMenuWidget(TSharedRef<FUICommandList> InCommandList, TWeakPtr<SLevelEditor> InLevelEditor);`
- L81 _protected prototype_ `static void OnCinematicsActorPicked( AActor* Actor );` — Delegate for actor selection within the Cinematics popup menu's SceneOutliner. Opens the editor for the selected actor and dismisses all popup menus.
- L88 _protected prototype_ `static void OnOpenSubLevelBlueprint( ULevel* InLevel );` — Callback to open a sub-level script Blueprint @param InLevel	The level to open the Blueprint of (creates if needed)
- L91 _private prototype_ `static void RegisterSourceControlMenu();`
- L92 _private prototype_ `static void RegisterCinematicsMenu();`
- L94 _private prototype_ `static void RegisterQuickSettingsMenu();`
- L95 _private prototype_ `static void RegisterOpenBlueprintMenu();`
- L96 _private prototype_ `static void RegisterAddMenu();`
- L98 _private prototype_ `static FText GetActiveModeName(TWeakPtr<SLevelEditor> LevelEditorPtr);`
- L99 _private prototype_ `static const FSlateBrush* GetActiveModeIcon(TWeakPtr<SLevelEditor> LevelEditorPtr);`
- L102 _private member_ `static FName SecondaryModeToolbarName;`

### `Source/Editor/LevelEditor/Private/LevelViewportLayout2x2.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FEditorViewportLayout2x2 FLevelViewportLayout2x2;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayout2x2 instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`

### `Source/Editor/LevelEditor/Private/LevelViewportLayoutFourPanes.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FEditorViewportLayoutFourPanesLeft FLevelViewportLayoutFourPanesLeft;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutFourPanesLeft instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`
- L11 _typedef_ `typedef FEditorViewportLayoutFourPanesRight FLevelViewportLayoutFourPanesRight;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutFourPanesRight instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`
- L14 _typedef_ `typedef FEditorViewportLayoutFourPanesTop FLevelViewportLayoutFourPanesTop;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutFourPanesTop instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`
- L17 _typedef_ `typedef FEditorViewportLayoutFourPanesBottom FLevelViewportLayoutFourPanesBottom;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutFourPanesBottom instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`

### `Source/Editor/LevelEditor/Private/LevelViewportLayoutOnePane.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FEditorViewportLayoutOnePane FLevelViewportLayoutOnePane;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutOnePane instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`

### `Source/Editor/LevelEditor/Private/LevelViewportLayoutThreePanes.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FEditorViewportLayoutThreePanesLeft FLevelViewportLayoutThreePanesLeft;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutThreePanesLeft instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`
- L12 _typedef_ `typedef FEditorViewportLayoutThreePanesRight FLevelViewportLayoutThreePanesRight;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutThreePanesRight instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`
- L16 _typedef_ `typedef FEditorViewportLayoutThreePanesTop FLevelViewportLayoutThreePanesTop;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutThreePanesTop instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`
- L20 _typedef_ `typedef FEditorViewportLayoutThreePanesBottom FLevelViewportLayoutThreePanesBottom;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutThreePanesBottom instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`

### `Source/Editor/LevelEditor/Private/LevelViewportLayoutTwoPanes.h` (Private)


#### Free symbols / members of external scopes

- L8 _typedef_ `typedef FEditorViewportLayoutTwoPanesVert FLevelViewportLayoutTwoPanesVert;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutTwoPanesVert instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`
- L11 _typedef_ `typedef FEditorViewportLayoutTwoPanesHoriz FLevelViewportLayoutTwoPanesHoriz;` — `UE_DEPRECATED(5.0, "Level Pane layouts are now owned by their level layouts. Use FEditorViewportLayoutTwoPanesHoriz instead, and add any custom types to FAssetEditorViewportLayout::FactoryPaneConfigurationFromTypeName.")`

### `Source/Editor/LevelEditor/Private/LightEditorSubsystem.h` (Private)


#### class `FLightEditingCommands`  
`class FLightEditingCommands : public TCommands<FLightEditingCommands>`  
_L22-38_
- inherits: `TCommands<FLightEditingCommands>`
- desc: Light manipulation actions
- L26 _public function_ `FLightEditingCommands() : TCommands<FLightEditingCommands> ( "LightActor",`
- L35 _public member_ `TSharedPtr< FUICommandInfo > SwapLightType;`
- L37 _public prototype_ `virtual void RegisterCommands() override;`

#### class `ULightEditorSubsystem`  
`class ULightEditorSubsystem : public UEditorSubsystem`  
_L41-53_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L45 _public function_ `ULightEditorSubsystem()`
- L46 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L48 _public prototype_ `virtual void Deinitialize() override;`
- L49 _public prototype_ `void ExtendQuickActionMenu();`
- L50 _public prototype_ `void SwapLightType(const FToolMenuContext& InContext, UClass* InClass) const;`
- L52 _public member_ `TSharedPtr<FUICommandList> LightEditingCommands;` — The list of commands with bound delegates for the level editor.

### `Source/Editor/LevelEditor/Private/SActorDetails.h` (Private)


#### class `SActorDetails`  
`class SActorDetails : public SCompoundWidget, public FEditorUndoClient, public FGCObject`  
_L39-165_
- inherits: `SCompoundWidget,FEditorUndoClient,FGCObject`
- desc: Wraps a details panel customized for the level editor
- L42 _public function_ `SLATE_BEGIN_ARGS(SActorDetails)`
- L43 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UTypedElementSelectionSet* InSelectionSet, const FName TabIdentifier, TSharedPtr<FUICommandList> InCommandList, TSharedPtr<FTabManager> InTabManager, TWeakPtr<FActorDetailsSCSEditorUICustomization> InLevelEditorSubobjectEditorCustomization);`
- L56 _public prototype_ `bool IsObservingSelectionSet(const UTypedElementSelectionSet* InSelectionSet) const;` — Return true if this details panel is observing the given selection set.
- L61 _public prototype_ `void RefreshSelection(const bool bForceRefresh = false);` — Update the view based on our observed selection set.
- L66 _public prototype_ `void OverrideSelection(const TArray<AActor*>& InActors, const bool bForceRefresh = false);` — Update the view based on the given set of actors.
- L69 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L70 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L73 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L74 _public prototype_ `virtual FString GetReferencerName() const override;`
- L81 _public prototype_ `void SetActorDetailsRootCustomization(TSharedPtr<FDetailsViewObjectFilter> InActorDetailsObjectFilter, TSharedPtr<class IDetailRootObjectCustomization> ActorDetailsRootCustomization);` — Sets the filter that should be used to filter incoming actors in or out of the details panel @param InFilter	The filter to use or nullptr to remove the active filter
- L85 _protected prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L95 _private prototype_ `void RefreshTopLevelElements(TArrayView<const TTypedElement<ITypedElementDetailsInterface>> InDetailsElements, const bool bForceRefresh, const bool bOverrideLock);`
- L96 _private prototype_ `void RefreshSubobjectTreeElements(TArrayView<const TSharedPtr<FSubobjectEditorTreeNode>> InSelectedNodes, const bool bForceRefresh, const bool bOverrideLock);`
- L97 _private prototype_ `void SetElementDetailsObjects(TArrayView<const TUniquePtr<ITypedElementDetailsObject>> InElementDetailsObjects, const bool bForceRefresh, const bool bOverrideLock, TArrayView<const TTypedElement<ITypedElementDetailsInterface>>* InDetailsElementsPtr = nullptr);`
- L99 _private prototype_ `AActor* GetActorContext() const;`
- L100 _private prototype_ `UObject* GetObjectContext() const;`
- L101 _private prototype_ `bool GetAllowComponentTreeEditing() const;`
- L106 _private prototype_ `EVisibility GetComponentEditorButtonsVisibility() const;` — Gets the Visibility of the top of the panel buttons in the details panel
- L108 _private prototype_ `void OnComponentsEditedInWorld();`
- L109 _private prototype_ `void OnSubobjectEditorTreeViewSelectionChanged(const TArray<TSharedPtr<FSubobjectEditorTreeNode> >& SelectedNodes);`
- L110 _private prototype_ `void OnSubobjectEditorTreeViewItemDoubleClicked(const TSharedPtr<FSubobjectEditorTreeNode> ClickedNode);`
- L111 _private prototype_ `void UpdateComponentTreeFromEditorSelection();`
- L113 _private prototype_ `bool IsPropertyReadOnly(const struct FPropertyAndParent& PropertyAndParent) const;`
- L114 _private prototype_ `bool IsPropertyEditingEnabled() const;`
- L115 _private prototype_ `EVisibility GetComponentEditorVisibility() const;`
- L116 _private prototype_ `EVisibility GetUCSComponentWarningVisibility() const;`
- L117 _private prototype_ `EVisibility GetInheritedBlueprintComponentWarningVisibility() const;`
- L118 _private prototype_ `EVisibility GetNativeComponentWarningVisibility() const;`
- L119 _private prototype_ `void OnBlueprintedComponentWarningHyperlinkClicked(const FSlateHyperlinkRun::FMetadata& Metadata);`
- L120 _private prototype_ `void OnNativeComponentWarningHyperlinkClicked(const FSlateHyperlinkRun::FMetadata& Metadata);`
- L122 _private prototype_ `void AddBPComponentCompileEventDelegate(UBlueprint* ComponentBlueprint);`
- L123 _private prototype_ `void RemoveBPComponentCompileEventDelegate();`
- L124 _private prototype_ `void OnBlueprintComponentCompiled(UBlueprint* ComponentBlueprint);`
- L125 _private prototype_ `void OnObjectsReinstanced(const TMap<UObject*, UObject*>& InReinstancedObjects);`
- L126 _private prototype_ `void OnObjectPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);`
- L128 _private member_ `TSharedPtr<SSplitter> DetailsSplitter;`
- L129 _private member_ `TSharedPtr<class IDetailsView> DetailsView;`
- L130 _private member_ `TSharedPtr<SBox> ComponentsBox;`
- L133 _private member_ `TSharedPtr<FActorDetailsSCSEditorUICustomization> LevelEditorSubobjectEditorCustomization;` — Subobject Editor customization that hosts other customizations. Scoped to the level editor
- L136 _private member_ `TSharedPtr<FInternalSubobjectCustomization> InternalSubobjectEditorCustomization;` — Subobject Editor customization that is maintained as last priority in the LevelEditorCustomization and is specific to the SActorDetails
- L138 _private member_ `TSharedPtr<SSubobjectEditor> SubobjectEditor;` — The subobject editor provides a tree widget that allows for editing of subobjects
- L140 _private member_ `TSharedPtr<UE::LevelEditor::Private::SElementSelectionDetailsButtons> ElementSelectionDetailsButtons;`
- L143 _private member_ `UTypedElementSelectionSet* SelectionSet = nullptr;` — The selection set this details panel is observing
- L146 _private member_ `bool bHasSelectionOverride = false;` — The selection override, if any
- L147 _private member_ `TArray<AActor*> SelectionOverrideActors;`
- L150 _private member_ `TArray<TUniquePtr<ITypedElementDetailsObject>> TopLevelElements;` — Array of top-level elements that are currently being edited
- L153 _private member_ `TArray<TUniquePtr<ITypedElementDetailsObject>> SubobjectTreeElements;` — Array of component elements that are being edited from the Subobject tree selection
- L156 _private member_ `TWeakObjectPtr<UBlueprint> SelectedBPComponentBlueprint;` — The current component blueprint selection
- L157 _private member_ `bool bSelectedComponentRecompiled = false;`
- L160 _private member_ `bool bSelectionGuard = false;` — Used to prevent reentrant changes
- L164 _private member_ `TSharedPtr<FDetailsDisplayManager> DisplayManager;` — A @code TSharedPtr @endcode to the @code FDetailsDisplayManager @endcode to manage various aspects of the details view

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace LevelEditor` (scope `UE`)
- L31 _namespace_ `namespace Private` (scope `UE::LevelEditor`)

### `Source/Editor/LevelEditor/Private/SActorPilotViewportToolbar.h` (Private)


#### class `SActorPilotViewportToolbar`  
`class SActorPilotViewportToolbar : public SViewportToolBar`  
_L8-25_
- inherits: `SViewportToolBar`
- L11 _public function_ `SLATE_BEGIN_ARGS(SActorPilotViewportToolbar)`
- L12 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SLevelViewport>, Viewport) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L17 _public prototype_ `FText GetActiveText() const;`
- L19 _public prototype_ `EVisibility GetLockedTextVisibility() const;`
- L24 _private member_ `TWeakPtr<SLevelViewport> Viewport;` — The viewport that we are in

### `Source/Editor/LevelEditor/Private/SCaptureRegionWidget.h` (Private)


#### class `SCaptureRegionWidget`  
`class SCaptureRegionWidget : public SCompoundWidget`  
_L19-88_
- inherits: `SCompoundWidget`
- L23 _public function_ `SLATE_BEGIN_ARGS( SCaptureRegionWidget ) : _Enabled()`
- L28 _public prototype_ `SLATE_ATTRIBUTE( bool, Enabled )` — Whether the control is enabled
- L39 _public prototype_ `void Activate(bool bCurrentCaptureRegionIsFullViewport);`
- L40 _public prototype_ `void Deactivate(bool bKeepChanges);`
- L41 _public prototype_ `void Reset();`
- L43 _public prototype_ `FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L44 _public prototype_ `FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L45 _public prototype_ `FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L72 _private member_ `EState CurrentState;`
- L73 _private member_ `FVector2D DragStartPosition;`
- L75 _private member_ `FIntRect OriginalCaptureRegion;` — FIntRect CurrentCaptureRegion;
- L76 _private member_ `EPotentialInteraction PotentialInteraction;`
- L77 _private member_ `bool bIgnoreExistingCaptureRegion;` — Don't allow manipulation of the current region. Will be true after first activation, if the original capture region is the size of the viewport
- L85 _private prototype_ `void BuildNewCaptureRegion(const FVector2D& InPointA, const FVector2D& InPointB);`
- L87 _private prototype_ `void SendUpdatedCaptureRegion();`

#### enum `SCaptureRegionWidget::EState`  
`enum EState`  
_L49-56_
- L51 _public enumerator_ `State_Inactive`
- L52 _public enumerator_ `State_Dragging`
- L53 _public enumerator_ `State_Moving`
- L54 _public enumerator_ `State_XAxisResize`
- L55 _public enumerator_ `State_YAxisResize`

#### enum `SCaptureRegionWidget::EPotentialInteraction`  
`enum EPotentialInteraction`  
_L58-70_
- L60 _public enumerator_ `PI_DrawNewCaptureRegion`
- L61 _public enumerator_ `PI_ResizeTL`
- L62 _public enumerator_ `PI_ResizeTR`
- L63 _public enumerator_ `PI_ResizeBL`
- L64 _public enumerator_ `PI_ResizeBR`
- L65 _public enumerator_ `PI_ResizeLeft`
- L66 _public enumerator_ `PI_ResizeRight`
- L67 _public enumerator_ `PI_ResizeTop`
- L68 _public enumerator_ `PI_ResizeBottom`
- L69 _public enumerator_ `PI_MoveExistingRegion`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCaptureRegionChanged, const FIntRect& ) DECLARE_DELEGATE_OneParam( FOnCaptureRegionCompleted, bool ) class SCaptureRegionWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS( SCaptureRegionWidget ) : _Enabled() {} SLATE_ATTRIBUTE( bool, Enabled )`
- L17 _delegate_ `DECLARE_DELEGATE_OneParam( FOnCaptureRegionCompleted, bool ) class SCaptureRegionWidget : public SCompoundWidget { public: SLATE_BEGIN_ARGS( SCaptureRegionWidget ) : _Enabled() {} SLATE_ATTRIBUTE( bool, Enabled )`

### `Source/Editor/LevelEditor/Private/SInViewportDetails.h` (Private)


#### class `SInViewportDetails`  
`class SInViewportDetails : public SCompoundWidget, public FEditorUndoClient`  
_L32-81_
- inherits: `SCompoundWidget,FEditorUndoClient`
- desc: Wraps a details panel customized for viewing actors
- L35 _public function_ `SLATE_BEGIN_ARGS(SInViewportDetails)`
- L36 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<class SEditorViewport>, InOwningViewport) SLATE_ARGUMENT(TSharedPtr<ILevelEditor>, InOwningLevelEditor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _public prototype_ `void GenerateWidget();`
- L44 _public prototype_ `EVisibility GetHeaderVisibility() const;`
- L45 _public prototype_ `TSharedRef<SWidget> MakeDetailsWidget();`
- L46 _public prototype_ `~SInViewportDetails();`
- L53 _public prototype_ `void SetObjects(const TArray<UObject*>& InObjects, bool bForceRefresh = false);` — Sets the objects to be viewed by the details panel @param InObjects	The objects to set
- L56 _public prototype_ `virtual void PostUndo(bool bSuccess) override;` — FEditorUndoClient Interface
- L57 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L59 _public prototype_ `FReply StartDraggingDetails(FVector2D InTabGrabScreenSpaceOffset, const FPointerEvent& MouseEvent);`
- L60 _public prototype_ `void FinishDraggingDetails(const FVector2D InLocation);`
- L61 _public function_ `FDetailColumnSizeData& GetColumnSizeData()`
- L62 _public prototype_ `AActor* GetSelectedActorInEditor() const;`
- L63 _public prototype_ `UToolMenu* GetGeneratedToolbarMenu() const;`
- L68 _private prototype_ `AActor* GetActorContext() const;`
- L69 _private prototype_ `TSharedRef<ITableRow> GenerateListRow(TSharedPtr<IDetailTreeNode> InItem, const TSharedRef<STableViewBase>& InOwningTable);`
- L70 _private prototype_ `void OnEditorSelectionChanged(UObject* Object);`
- L73 _private member_ `TSharedPtr<SSplitter> DetailsSplitter;`
- L74 _private member_ `TSharedPtr<SListView<TSharedPtr<class IDetailTreeNode>>> NodeList;`
- L75 _private member_ `TArray<TSharedPtr<class IDetailTreeNode>> Nodes;`
- L76 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;`
- L77 _private member_ `FDetailColumnSizeData ColumnSizeData;`
- L78 _private member_ `TWeakPtr<class SEditorViewport> OwningViewport;`
- L79 _private member_ `TWeakPtr<ILevelEditor> ParentLevelEditor;`
- L80 _private member_ `TWeakObjectPtr<UToolMenu> GeneratedToolbarMenu;`

#### class `SInViewportDetailsHeader`  
`class SInViewportDetailsHeader : public SCompoundWidget`  
_L83-105_
- inherits: `SCompoundWidget`
- L87 _public function_ `SLATE_BEGIN_ARGS(SInViewportDetailsHeader)`
- L88 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(TSharedPtr<SInViewportDetails>, Parent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L94 _public function_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L100 _public prototype_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L101 _public prototype_ `TSharedPtr<class FDragDropOperation> CreateDragDropOperation();`
- L104 _public member_ `TWeakPtr<SInViewportDetails> ParentPtr;` — The parent in-viewport details

#### class `SInViewportDetailsToolbar`  
`class SInViewportDetailsToolbar : public SCompoundWidget`  
_L107-117_
- inherits: `SCompoundWidget`
- L110 _public function_ `SLATE_BEGIN_ARGS(SInViewportDetailsToolbar)`
- L111 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<SInViewportDetails>, Parent) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L115 _public prototype_ `FName GetQuickActionMenuName(UClass* InClass);`

### `Source/Editor/LevelEditor/Private/SLevelEditor.h` (Private)


#### class `SLevelEditor`  
`class SLevelEditor : public ILevelEditor`  
_L36-390_
- inherits: `ILevelEditor`
- desc: Unreal editor level editor Slate widget
- L41 _public function_ `SLATE_BEGIN_ARGS( SLevelEditor )`
- L48 _public prototype_ `SLevelEditor();` — Constructor
- L50 _public prototype_ `~SLevelEditor();`
- L57 _public prototype_ `void Construct( const FArguments& InArgs );` — Constructs this widget @param InArgs    Declaration from which to construct the widget
- L63 _public prototype_ `void Initialize( const TSharedRef<SDockTab>& OwnerTab, const TSharedRef<SWindow>& OwnerWindow );` — Initialize the newly constructed level editor UI, needed because restoring the layout could trigger showing tabs that immediately try to get a reference to the current level editor.
- L71 _public prototype_ `TSharedPtr<class SLevelViewport> GetActiveViewport() const;` — Gets the currently active viewport in the level editor @todo Slate: Needs a better implementation @return The active viewport.  If multiple are active it returns the first one
- L74 _public prototype_ `virtual const UTypedElementSelectionSet* GetElementSelectionSet() const override;` — ILevelEditor interface
- L75 _public prototype_ `virtual UTypedElementSelectionSet* GetMutableElementSelectionSet() override;`
- L76 _public prototype_ `virtual void SummonLevelViewportContextMenu(const FTypedElementHandle& HitProxyElement = FTypedElementHandle()) override;`
- L77 _public prototype_ `virtual FText GetLevelViewportContextMenuTitle() const override;`
- L78 _public prototype_ `virtual void SummonLevelViewportViewOptionMenu(const ELevelViewportType ViewOption) override;`
- L79 _public prototype_ `virtual const TArray< TSharedPtr< class IToolkit > >& GetHostedToolkits() const override;`
- L80 _public prototype_ `virtual TArray< TSharedPtr< SLevelViewport > > GetViewports() const override;`
- L81 _public prototype_ `virtual TMap< int32, TArray< TSharedPtr< SLevelViewport > > > GetViewportsByTab() const override;`
- L82 _public prototype_ `virtual TSharedPtr<SLevelViewport> GetActiveViewportInterface() override;`
- L83 _public prototype_ `virtual void AppendCommands( const TSharedRef<FUICommandList>& InCommandsToAppend ) override;`
- L84 _public prototype_ `virtual void AddStandaloneLevelViewport( const TSharedRef<SLevelViewport>& LevelViewport ) override;`
- L90 _public prototype_ `TSharedPtr<SDockTab> TryInvokeTab( FName TabID );` — Given a tab ID, summons a new tab in the position saved in the current layout, or in a default position. @return the invoked tab
- L96 _public prototype_ `void SyncDetailsToSelection();` — Sync the details panel to the current selection Will spawn a new details window if required (and possible) due to other details windows being locked
- L101 _public prototype_ `bool HasActivePlayInEditorViewport() const;` — @return true if the level editor has a viewport currently being used for pie
- L104 _public prototype_ `FText GetTabTitle() const;` — @return	Returns the title to display in the level editor's tab label
- L107 _public prototype_ `FText GetTabSuffix() const;` — @return	Returns the suffix to display in the level editor's after tab label
- L115 _public prototype_ `virtual FReply OnKeyDownInViewport( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Processes level editor keybindings using events made in a viewport @param MyGeometry		Information about the size and position of the viewport widget @param InKeyEvent	The event which just occurred
- L118 _public function_ `virtual const TSharedPtr< FUICommandList >& GetLevelEditorActions() const override` — Returns the full action list for this level editor instance
- L124 _public prototype_ `virtual TSharedRef< class SWidget > GetParentWidget() override;` — IToolKitHost interface
- L125 _public prototype_ `virtual void BringToFront() override;`
- L126 _public prototype_ `virtual TSharedPtr<FTabManager> GetTabManager() const override;`
- L127 _public prototype_ `virtual void OnToolkitHostingStarted( const TSharedRef< class IToolkit >& Toolkit ) override;`
- L128 _public prototype_ `virtual void OnToolkitHostingFinished( const TSharedRef< class IToolkit >& Toolkit ) override;`
- L129 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L130 _public prototype_ `virtual TSharedRef<SWidget> CreateActorDetails( const FName TabIdentifier ) override;`
- L131 _public prototype_ `virtual void SetActorDetailsRootCustomization(TSharedPtr<FDetailsViewObjectFilter> InActorDetailsObjectFilter, TSharedPtr<IDetailRootObjectCustomization> InActorDetailsRootCustomization) override;`
- L132 _public prototype_ `virtual void AddActorDetailsSCSEditorUICustomization(TSharedPtr<ISCSEditorUICustomization> ActorDetailsSCSEditorUICustomization) override;`
- L133 _public prototype_ `virtual void RemoveActorDetailsSCSEditorUICustomization(TSharedPtr<ISCSEditorUICustomization> ActorDetailsSCSEditorUICustomization) override;`
- L134 _public prototype_ `virtual FEditorModeTools& GetEditorModeManager() const override;`
- L135 _public prototype_ `virtual UTypedElementCommonActions* GetCommonActions() const override;`
- L136 _public prototype_ `virtual FName GetStatusBarName() const override;`
- L137 _public function_ `virtual FOnActiveViewportChanged& OnActiveViewportChanged()`
- L138 _public prototype_ `virtual void AddViewportOverlayWidget(TSharedRef<SWidget>, int32 ZOrder = INDEX_NONE, TSharedPtr<IAssetViewport> InViewport = nullptr) override;`
- L139 _public prototype_ `virtual void RemoveViewportOverlayWidget(TSharedRef<SWidget>, TSharedPtr<IAssetViewport> InViewport = nullptr) override;`
- L142 _public prototype_ `virtual FVector2f GetActiveViewportWidgetSize() const override;`
- L144 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — Tick to check the ActiveViewport
- L147 _public function_ `virtual bool SupportsKeyboardFocus() const override` — SWidget overrides
- L153 _public prototype_ `TSharedPtr<SDockTab> AttachSequencer( TSharedPtr<SWidget> SequencerWidget, TSharedPtr<IAssetEditorInstance> NewSequencerAssetEditor );` — Attaches a sequencer asset editor used to animate objects in the level to this level editor
- L156 _public prototype_ `virtual void GetSceneOutlinerInitializationOptions(const FName TabIdentifier, FSceneOutlinerInitializationOptions& OutInitOptions) override;` — Gets the default FSceneOutlinerInitializationOptions for this Level Editor's Scene Outliners
- L159 _public prototype_ `virtual TArray<TWeakPtr<ISceneOutliner>> GetAllSceneOutliners() const override;` — Get an array containing weak pointers to all 4 Scene Outliners which could be potentially active
- L162 _public prototype_ `virtual void SetMostRecentlyUsedSceneOutliner(FName OutlinerIdentifier) override;` — Set the outliner with the given name as the most recently interacted with
- L165 _public prototype_ `virtual TSharedPtr<ISceneOutliner> GetMostRecentlyUsedSceneOutliner() override;` — Return the most recently interacted with Outliner
- L167 _public function_ `virtual TWeakPtr<UE::WorldHierarchy::IWorldHierarchy> GetWorldHierarchy() override`
- L169 _public function_ `TSharedRef<SWidget> GetTitleBarMessageWidget() const`
- L172 _private prototype_ `TSharedRef<SDockTab> SpawnLevelEditorTab(const FSpawnTabArgs& Args, FName TabIdentifier, FString InitializationPayload);`
- L173 _private prototype_ `bool CanSpawnLevelEditorTab(const FSpawnTabArgs& Args, FName TabIdentifier);`
- L175 _private prototype_ `TSharedRef<SDockTab> SummonDetailsPanel( FName Identifier );` — TSharedRef<SDockTab> SpawnLevelEditorModeTab(const FSpawnTabArgs& Args, FEdMode* EditorMode);
- L180 _private prototype_ `void BindCommands();` — Binds UI commands to actions for the level editor
- L183 _private prototype_ `void RegisterMenus();` — Registers menus associated with level editor
- L189 _private prototype_ `TSharedRef<SWidget> RestoreContentArea( const TSharedRef<SDockTab>& OwnerTab, const TSharedRef<SWindow>& OwnerWindow );` — Fills the level editor with content, using the layout string, or the default if no layout string is passed in
- L192 _private prototype_ `void HandleExperimentalSettingChanged(FName PropertyName);` — Called when a property is changed
- L195 _private prototype_ `void RefreshEditorModeCommands();` — Rebuilds the command list for spawning editor modes, this is done when new modes are registered.
- L198 _private prototype_ `void EditorModeCommandsChanged();` — Editor mode has been added or removed, clears cached command list so it will be rebuilt
- L201 _private prototype_ `static FName GetEditorModeTabId( FEditorModeID ModeID );` — Gets the tabId mapping to an editor mode
- L204 _private prototype_ `void ToggleEditorMode( FEditorModeID ModeID );` — Toggles the editor mode on and off, this is what the auto generated editor mode commands are mapped to.
- L207 _private prototype_ `bool IsModeActive(FEditorModeID ModeID);` — Checks if the editor mode is active for the auto-generated editor mode command.
- L210 _private prototype_ `bool ShouldShowModeInToolbar(FEditorModeID ModeID);` — Checks if the editor mode is visible for the auto-generated editor mode command.
- L218 _private prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — Processes keybindings on the level editor @param MyGeometry		Information about the size and position of the level editor widget @param InKeyEvent	The event which just occurred
- L221 _private prototype_ `void OnLayoutHasChanged();` — Callback for when the level editor layout has changed
- L224 _private prototype_ `void ConstructTitleBarMessages();` — Constructs the title bar message widget
- L227 _private prototype_ `TSharedRef<SDockTab> BuildViewportTab( const FText& Label, const FString LayoutId, const FString& InitializationPayload );` — Builds a viewport tab.
- L230 _private prototype_ `void OnViewportTabClosed(TSharedRef<SDockTab> ClosedTab);` — Called when a viewport tab is closed
- L233 _private prototype_ `void OnToolboxTabClosed(TSharedRef<SDockTab> ClosedTab);` — Called when the toolbox tab is closed
- L236 _private prototype_ `void SaveViewportTabInfo(TSharedRef<const class FLevelViewportTabContent> ViewportTabContent);` — Save the information about the given viewport in the transient viewport information
- L239 _private prototype_ `void RestoreViewportTabInfo(TSharedRef<FLevelViewportTabContent> ViewportTabContent) const;` — Restore the information about the given viewport from the transient viewport information
- L242 _private prototype_ `void ResetViewportTabInfo();` — Reset the transient viewport information
- L245 _private prototype_ `void HandleEditorMapChange( uint32 MapChangeFlags );` — Handles Editor map changes
- L248 _private prototype_ `void HandleAssetsDeleted(const TArray<UClass*>& DeletedClasses);` — Handles deletion of assets
- L251 _private prototype_ `void OnIsmInstanceRemoving(const FSMInstanceElementId& SMInstanceElementId, int32 InstanceIndex);` — Handles events where an instance of an Instanced Static Mesh is about to be removed.
- L254 _private prototype_ `void OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh = false);` — Called when element selection changes
- L257 _private prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh);` — Called when actor selection changes
- L260 _private prototype_ `void OnOverridePropertyEditorSelection(const TArray<AActor*>& NewSelection, bool bForceRefresh = false);` — Called to set property editors to show the given actors, even if those actors aren't in the current selection set
- L263 _private prototype_ `void OnLevelActorDeleted(AActor* InActor);` — Called when an actor is destroyed
- L266 _private prototype_ `void OnLevelActorOuterChanged(AActor* InActor = nullptr, UObject* InOldOuter = nullptr);` — Called when an actor changes outer
- L269 _private prototype_ `void RegisterStatusBarTools();` — Registers toolbar options for the level editor status bar
- L272 _private prototype_ `TArray<TSharedRef<SActorDetails>> GetAllActorDetails() const;` — @return All valid actor details panels
- L275 _private prototype_ `TSharedRef<ISceneOutliner> CreateSceneOutliner(FName TabIdentifier);` — Create a Scene Outliner for the Level Editor
- L278 _private prototype_ `void OnExtendSceneOutlinerTabContextMenu(FMenuBuilder& InMenuBuilder);` — Function to extend the context menu for the outliner tab
- L281 _private prototype_ `FText GetSceneOutlinerLabel(FName SceneOutlinerTabIdentifier);` — Helper function to get the display name for an outliner
- L284 _private prototype_ `void ResetMostRecentOutliner();` — Sets the first available outliner as the most recent outliner
- L286 _private prototype_ `void RegisterViewportInteractions(UViewportInteractionsBehaviorSource* Source) const;`
- L291 _private member_ `TArray< TWeakPtr<FLevelViewportTabContent> > ViewportTabs;` — Tracking the active viewports in this level editor.
- L294 _private member_ `TArray< TWeakPtr<SLevelViewport> > StandaloneViewports;` — A list of any standalone editor viewports that aren't in tabs
- L297 _private member_ `TWeakPtr<class SLevelViewport> CachedActiveViewport;` — The last known active viewport
- L300 _private member_ `TSharedPtr< SBorder > DocumentsAreaBorder;` — Border that hosts the document content for the level editor.
- L303 _private member_ `TSharedPtr<FUICommandList> LevelEditorCommands;` — The list of commands with bound delegates for the level editor.
- L306 _private member_ `TArray< TWeakPtr< class SLevelEditorToolBox > > ToolBoxTabs;` — Weak reference to all toolbox panels this level editor has spawned.  May contain invalid entries for tabs that were closed.
- L309 _private member_ `TArray< TSharedPtr< class IToolkit > > HostedToolkits;` — List of all of the toolkits we're currently hosting.
- L312 _private member_ `UWorld* World;` — The UWorld that this level editor is viewing and allowing the user to interact with through.
- L315 _private member_ `UTypedElementSelectionSet* SelectedElements = nullptr;` — The list of selected elements (also set on the global USelection for actors and components).
- L318 _private member_ `UTypedElementCommonActions* CommonActions = nullptr;` — The common actions implementation for the level editor
- L321 _private member_ `TSharedPtr<SHorizontalBox> TtileBarMessageBox;` — The box that holds the title bar messages.
- L324 _private member_ `TSharedPtr<IDetailsView> WorldSettingsView;` — Holds the world settings details view.
- L327 _private member_ `TMap<FString, FLevelViewportInfo> TransientEditorViews;` — Transient editor viewport states - one for each view type. Key is "LayoutId[ELevelViewportType]", eg) "Viewport 1[0]"
- L330 _private member_ `TArray< TWeakPtr<class SActorDetails> > AllActorDetailPanels;` — List of all actor details panels to update when selection changes
- L333 _private member_ `TWeakPtr<IAssetEditorInstance> SequencerAssetEditor;` — Attached sequencer asset editor
- L336 _private member_ `TWeakPtr<SWidget> SequencerWidgetPtr;` — Weak pointer to the level editor's Sequencer widget
- L339 _private member_ `TWeakPtr<ISceneOutliner> SceneOutlinerPtr;` — Weak pointer to the level editor's most recently created scene outliner
- L342 _private member_ `TWeakPtr<UE::WorldHierarchy::IWorldHierarchy> WorldHierarchy;` — The content displayed by the LevelEditorTabIds::WorldBrowserHierarchy tab.
- L345 _private member_ `TMap<FName, TWeakPtr<ISceneOutliner>> SceneOutliners;` — Map containing Weak pointers to all the Outliners in the level editor
- L348 _private member_ `TMap<FName, TWeakPtr<SDockTab>> SceneOutlinerTabs;` — Map containing Weak pointers to all the Scene Outliner Tabs in the level editor
- L351 _private member_ `TMap<FName, FText> SceneOutlinerDisplayNames;` — Map containing the display names of all the outliners
- L354 _private member_ `FDelegateHandle PreviewFeatureLevelChangedHandle;` — Handle to the registered OnPreviewFeatureLevelChanged delegate.
- L357 _private member_ `FDelegateHandle PreviewPlatformChangedHandle;` — Handle to the registered OnPreviewPlatformChanged delegate.
- L360 _private member_ `FDelegateHandle LevelActorDeletedHandle;` — Handle to the registered OnLevelActorDeleted delegate
- L363 _private member_ `FDelegateHandle LevelActorOuterChangedHandle;` — Handle to the registered OnLevelActorOuterChanged delegate
- L366 _private member_ `TSharedPtr<FDetailsViewObjectFilter> ActorDetailsObjectFilter;` — Actor details object filters
- L369 _private member_ `TSharedPtr<IDetailRootObjectCustomization> ActorDetailsRootCustomization;` — Actor details root customization
- L372 _private member_ `TSharedPtr<FActorDetailsSCSEditorUICustomization> ActorDetailsSCSEditorUICustomization;` — Actor details SCS editor customization
- L375 _private member_ `FOnActiveViewportChanged OnActiveViewportChangedDelegate;` — A delegate which is called any time the LevelEditor's active viewport changes.
- L378 _private member_ `UE::Editor::DataStorage::RowHandle LevelEditorScopeRow = UE::Editor::DataStorage::InvalidRowHandle;` — Context row for the Editor Scope Tree system
- L381 _private member_ `std::atomic<bool> bNeedsRefresh;` — If this flag is raised we will force refresh on next selection update.
- L383 _private member_ `TMap<FName, TSharedPtr<FLevelEditorModeUILayer>> ModeUILayers;`
- L386 _private member_ `TSharedPtr<SBorder> SecondaryModeToolbarWidget;` — Pointer to the widget that houses the level editor's mode toolbar
- L389 _private member_ `FText CachedViewportContextMenuTitle;` — Viewport context menu title, cached each time the element selection set changes

#### Free symbols / members of external scopes

- L31 _namespace_ `namespace UE`
- L31 _namespace_ `namespace WorldHierarchy` (scope `UE`)

### `Source/Editor/LevelEditor/Private/SLevelEditorBuildAndSubmit.h` (Private)


#### class `SLevelEditorBuildAndSubmit`  
`class SLevelEditorBuildAndSubmit : public SCompoundWidget`  
_L22-113_
- inherits: `SCompoundWidget`
- desc: Build and Submit tab for the level editor
- L34 _public function_ `SLATE_BEGIN_ARGS( SLevelEditorBuildAndSubmit )`
- L37 _public prototype_ `virtual ~SLevelEditorBuildAndSubmit();`
- L42 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef< class ILevelEditor >& OwningLevelEditor );` — Construct a SLevelEditorBuildAndSubmit widget based on initial parameters.
- L49 _public function_ `void SetDockableTab(TSharedRef<SDockTab> InParentDockTab)` — Sets the parent tab so that the widget can close its host tab. @param ParentDockTab		The parent/host dockable tab of this widget.
- L51 _public prototype_ `void OnEditorPackageModified(class UPackage* Package);`
- L55 _private prototype_ `void OnSourceControlStateChanged();` — Called by the package file cache callback to inform this widget of source control state changes
- L58 _private prototype_ `TSharedRef< ITableRow > OnGenerateWidgetForPackagesList( TSharedPtr<FPackageItem> InItem, const TSharedRef<STableViewBase>& OwnerTable );` — Called by the OnGenerateRow event of the additional package list - creates the widget representing each package in the list
- L61 _private prototype_ `void UpdatePackagesList();` — Called from various places internally, to rebuild the additional package list contents based on the states in the global package file cache
- L64 _private prototype_ `FReply OnBuildAndCloseClicked();` — Called when the Build and Clsoe button is clicked. Runs the automated build and submit process based in the options set in the widget THEN closes the widget's tab/window
- L67 _private prototype_ `FReply OnBuildClicked();` — Called when the Build button is clicked. Runs the automated build and submit process based in the options set in the widget.
- L74 _private prototype_ `void OnShowHideExtraPackagesSection(bool bIsExpanded);` — Called when the additional package list is shown/hidden by the user clicking the expander arrow around the list @param bIsExpanded	The expansion state of the package list area (true => visible)
- L82 _private prototype_ `void OnShowPackagesNotInSCBoxChanged(ECheckBoxState InNewState);` — Called when the check box to show/hide packages not in source control is clicked. Changes the packages shown in the additional package list. @param InNewState	The state of the check box
- L85 _private member_ `TWeakPtr<class ILevelEditor> LevelEditor;` — Level editor that we're associated with
- L88 _private member_ `TWeakPtr<SDockTab> ParentDockTab;` — SDockTab in the LevelEditor that we're associated with
- L91 _private member_ `TArray<TSharedPtr<FPackageItem>> PackagesList;` — The package list that acts as the items source for the additional packages list widget
- L94 _private member_ `TSharedPtr<SEditableTextBox> DescriptionBox;` — The editable text box containing the submission description
- L97 _private member_ `TSharedPtr<SCheckBox> NoSubmitOnMapErrorBox;` — Options check box - Stops the auto-build and submit process submitting files if any map errors occur
- L100 _private member_ `TSharedPtr<SCheckBox> NoSubmitOnSaveErrorBox;` — Options check box - Stops the auto-build and submit process submitting files if any save errors occur
- L103 _private member_ `TSharedPtr<SCheckBox> ShowPackagesNotInSCBox;` — Options check box - Controls whether packages not in source control are shown in the additional packages list
- L106 _private member_ `TSharedPtr<SCheckBox> AddFilesToSCBox;` — Options check box - Controls whether new map packages are auto-added to source control during the auto-build and submit process
- L109 _private member_ `bool bIsExtraPackagesSectionExpanded;` — Set by OnShowHideExtraPackagesSection() - keeps track of the visibility or the additional packages list
- L112 _private member_ `FDelegateHandle OnSourceControlStateChangedDelegateHandle;` — Handle to the registered OnSourceControlStateChanged delegate

#### class `SLevelEditorBuildAndSubmit::FPackageItem`  
`class FPackageItem`  
_L26-32_
- desc: A check box selectable item in the additional package list
- L29 _public member_ `FString Name;`
- L30 _public member_ `FSourceControlStatePtr SourceControlState;`
- L31 _public member_ `bool Selected;`

### `Source/Editor/LevelEditor/Private/SLevelEditorToolBox.h` (Private)


#### class `ULevelEditorUISubsystem`  
`class ULevelEditorUISubsystem : public UAssetEditorUISubsystem`  
_L27-35_
- reflection: `UCLASS()`
- inherits: `UAssetEditorUISubsystem`
- L32 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L33 _public prototype_ `virtual void Deinitialize() override;`
- L34 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`

#### class `FLevelEditorModeUILayer`  
`class FLevelEditorModeUILayer : public FAssetEditorModeUILayer`  
_L38-47_
- inherits: `FAssetEditorModeUILayer`
- L41 _public prototype_ `FLevelEditorModeUILayer(const IToolkitHost* InToolkitHost);`
- L42 _public function_ `FLevelEditorModeUILayer()`
- L43 _public prototype_ `virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;`
- L44 _public prototype_ `virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;`
- L46 _public prototype_ `virtual TSharedPtr<FWorkspaceItem> GetModeMenuCategory() const override;`

### `Source/Editor/LevelEditor/Private/SSurfaceProperties.h` (Private)


#### class `SSurfaceProperties`  
`class SSurfaceProperties : public SCompoundWidget, public FNotifyHook, public FGCObject`  
_L27-303_
- inherits: `SCompoundWidget,FNotifyHook,FGCObject`
- desc: Surface Properties This class creates a widget which allows the user to edit any BSP surfaces selected. Functionality includes allowing Panning, Rotating and scaling of the texture coordinates. As well as editing the lighting settings of the surface.
- L30 _public function_ `SLATE_BEGIN_ARGS( SSurfaceProperties )`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct( const FArguments& InArgs );`
- L36 _public function_ `UWorld* GetWorld() const` — Fallback to GWorld
- L53 _private prototype_ `virtual void NotifyPostChange( const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged ) override;` — FNotifyHook Interface
- L56 _private prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject Interface
- L57 _private prototype_ `virtual FString GetReferencerName() const override;`
- L63 _private prototype_ `TSharedRef<SWidget> ConstructTexturePan();` — Creates Pan texture controls @returns Shared Reference to a widget containing constructed UI elements
- L69 _private prototype_ `TSharedRef<SWidget> ConstructTextureRotate();` — Creates Rotate texture controls @returns Shared Reference to a widget containing constructed UI elements
- L75 _private prototype_ `TSharedRef<SWidget> ConstructTextureFlip();` — Creates Flip texture controls @returns Shared Reference to a widget containing constructed UI elements
- L81 _private prototype_ `TSharedRef<SWidget> ConstructTextureScale();` — Creates Scale texture controls @returns Shared Reference to a widget containing constructed UI elements
- L87 _private prototype_ `TSharedRef<SWidget> ConstructLighting();` — Creates Lighting controls @returns Shared Reference to a widget containing constructed UI elements
- L96 _private prototype_ `FReply OnPanTexture(int32 PanAmount, TextureCoordChannel Channel);` — Pans the texture on the selected surfaces @param PanAmount			- The amount to pan the texture coordinates. @param Channel			- The Texture coordinate channel to perform the operation on. @return Always returns FReply::Handled()
- L105 _private prototype_ `FReply OnRotateTexture(int32 RotationAmount, RotationAction Action);` — Rotates the texture on the selected surfaces @param RotationAmount	- The amount in Degrees to rotate the texture. @param Action			- Dictates whether to Rotate by the passed in amount or Flip the texture @return Always returns FReply::Handled()
- L113 _private prototype_ `FReply OnFlipTexture(TextureCoordChannel Channel);` — Flips the texture on the selected surfaces @param Channel			- which texture coordinate Channel to flip the texture around. @return Always returns FReply::Handled()
- L121 _private prototype_ `void OnScaleTexture( float InScaleU, float InScaleV, bool InRelative );` — Scales the texture on the selected surfaces @param InScaleU			- Value to scale the U texture coordinate by. @param InScaleV			- Value to scale the V texture coordinate by. @param InRelative		- Whether to scale the coordinates relatively or absolutely.
- L127 _private prototype_ `void SetLightmassSettingsForSelectedSurfaces(FLightmassPrimitiveSettings& InSettings);` — Updates the selected surfaces light mass settings. @param InSettings		- Updated settings to be applied to surfaces
- L133 _private prototype_ `TOptional<float> GetLightmapResolutionValue() const;` — Called by the lightmap resolution control to access what value to display. @return Value to display
- L139 _private prototype_ `void OnLightmapResolutionCommitted(float NewValue, ETextCommit::Type CommitInfo);` — Called when the lightmap resolution field has been updated @param NewValue			- New Lightmap resolution value
- L147 _private prototype_ `void OnScaleSelectionChanged( TSharedPtr<FString> ProposedSelection, ESelectInfo::Type SelectInfo, TextureCoordChannel Channel );` — Called when a new value is chosen from the scale Combobuttons drop down menu. @param ProposedSelection	- Value chosen from the menu, to be applied as the new scale value @param Channel			- Texture coordinate channel to operate on @param SelectInfo		- Provides context on how the selection changed
- L154 _private prototype_ `void OnScaleValueCommitted(float Value, ETextCommit::Type CommitInfo, TextureCoordChannel Channel);` — Called when a new Scale value is typed into the editable text field on a scale Combobutton. @param Channel			- Texture coordinate channel to operate on @param Value				- New value to be set as the scaling factor
- L161 _private prototype_ `TOptional<float> OnGetScalingValue(TextureCoordChannel Channel) const;` — Called by the scaling combobuttons to access what value to display. @param Channel			- Texture coordinate channel to operate on @returns Value to display (CachedScalingValueU or CachedScalingValueV)
- L167 _private prototype_ `FReply OnApplyScaling();` — Called by the Apply button in the scaling field, results in executing a scaling operation using the values from the scaling factors.
- L173 _private prototype_ `const FSlateBrush* GetPreserveScaleRatioImage() const;` — Called by the Preserve Scaling Ratio control to access which image to display @returns A FSlateBursh pointer to the correct image to display
- L179 _private prototype_ `void OnPreserveScaleRatioToggled( ECheckBoxState NewState );` — Called by the Preserve Scaling Ratio control when clicked @param NewState			- The new state which the control has entered into
- L185 _private prototype_ `ECheckBoxState IsPreserveScaleRatioChecked() const;` — called by the Preserve scaling ratio control to determine whether or not the control is toggled @returns The appropriate Checked state for whether the control is toggled
- L194 _private prototype_ `TSharedRef< ITableRow > OnGenerateScaleTableRow( TSharedPtr<FString> Item, const TSharedRef< STableViewBase >& OwnerTable );` — Constructs the internal Table rows of the Scale combobuttons menu. @param Item				- Table entry to generate row for @param OwnerTable		- Table entry parent table @return Shared reference to a newly generated TableRow
- L200 _private prototype_ `void OnScaleLabelClicked( );` — Toggles Scale mode from Relative to Absolute, called when Scale label clicked @param Payload			- Required by delegate format, ignored in this case.
- L205 _private prototype_ `FText GetScalingLabel() const;` — Returns the text for the scaling label, determined by the value of bUseRelativeScaling
- L212 _private prototype_ `void OnCustomPanValueCommitted( int32 NewValue, ETextCommit::Type CommitInfo, TextureCoordChannel Channel );` — Called with a value has been committed by one of the custom pan combobuttons @param NewValue			- The amount to pan texture coordinate by. @param Channel			- Texture coordinate channel to apply the panning on.
- L218 _private prototype_ `void OnCustomRotateValueCommitted(int32 NewValue, ETextCommit::Type CommitInfo );` — Called when a custom rotate value has been set via the rotations combobutton. @param NewValue			- Rotation value to be applied.
- L224 _private prototype_ `const FSlateBrush* GetTogglePanDirectionImage( TextureCoordChannel Channel ) const;` — Returns the image to display on the Toggle Pan Direction control, for the specified texture channel @param Channel			- Texture Coordinate Channel this control operates on.
- L230 _private prototype_ `ECheckBoxState IsUsingNegativePanning( TextureCoordChannel Channel ) const;` — Returns the correct checkbox state for the specified texture channels panning state. @param Channel			- Texture Coordinate Channel this control operates on.
- L237 _private prototype_ `void OnTogglePanningDirection( ECheckBoxState NewState, TextureCoordChannel Channel );` — Toggles the specified texture channels panning state. @param NewState			- State of the toggled control. @param Channel			- Texture Coordinate Channel this control operates on.
- L242 _private prototype_ `const FSlateBrush* GetToggleRotationDirectionImage() const;` — Returns the image to display on the Toggle Rotation Direction control.
- L247 _private prototype_ `ECheckBoxState IsUsingNegativeRotation() const;` — Returns the correct checkbox state for the current rotation directions state.
- L253 _private prototype_ `void OnToggleRotationDirection( ECheckBoxState NewState );` — Toggles the Rotation directions state. @param NewValue			- Rotation value to be applied.
- L256 _private typedef_ `typedef TArray<TObjectPtr<ULightmassPrimitiveSettingsObject>> TLightmassSettingsObjectArray;` — typedef to make it easier to handle the lightmass objects
- L259 _private member_ `TArray<TLightmassSettingsObjectArray> LevelLightmassSettingsObjects;` — Stores the lightmass settings objects, regardless of their selection status. Must be serialized.
- L262 _private member_ `TArray<TObjectPtr<UObject>> SelectedLightmassSettingsObjects;` — Stores the selected lightmass settings objects, must be serialized. Used to create property tree.
- L265 _private member_ `TSharedPtr<class IDetailsView> PropertyView;` — Holds reference to the lightmass property tree view
- L268 _private member_ `TArray<TSharedPtr<FString>> ScalingFactors;` — Stores a list of all of the scaling factor options for the scaling menu values
- L271 _private member_ `TArray<TWeakPtr<SComboButton>> ScalingComboButton;` — Stores a reference to the two scaling buttons
- L274 _private member_ `TArray<TWeakPtr<SListView<TSharedPtr<FString>>>> ScalingListViews;` — Stores a reference to the two scaling buttons List views
- L277 _private member_ `TWeakPtr<SComboButton> CustomRotationButton;` — Stores a pointer to the combobutton of the custom rotation control
- L280 _private member_ `TArray<TWeakPtr<SComboButton>> CustomPanButtoms;` — Stores pointers to the combobuttons of the custom panning controls
- L283 _private member_ `float CachedScalingValueU;` — Cached scaling values
- L284 _private member_ `float CachedScalingValueV;`
- L287 _private member_ `bool bPreserveScaleRatio;` — If TRUE then any change to one scaling value will be reflected in the other
- L290 _private member_ `bool bUseRelativeScaling;` — If TRUE Scaling will be done relative rather than absolute.
- L293 _private member_ `bool bUseNegativePanningU;` — If TRUE the panning operation the U texture coordinate will be inverted
- L296 _private member_ `bool bUseNegativePanningV;` — If TRUE the panning operation the V texture coordinate will be inverted
- L299 _private member_ `bool bUseNegativeRotation;` — If TRUE the Rotation operation will be inverted
- L302 _private member_ `bool bShiftIsDown;` — Cached value of Shifts current state, this should be updated before any buttons OnClicked is called

#### enum `SSurfaceProperties::TextureCoordChannel`  
`enum TextureCoordChannel`  
_L39-43_
- desc: Texture Coordinate channels to perform operations on
- L41 _public enumerator_ `UChannel = 0`
- L42 _public enumerator_ `VChannel = 1`

#### enum `SSurfaceProperties::RotationAction`  
`enum RotationAction`  
_L46-50_
- desc: Actions available to rotation controls
- L48 _public enumerator_ `Rotate`
- L49 _public enumerator_ `RotateCustom`

### `Source/Editor/LevelEditor/Private/TedsOutliner/SceneOutlinerWidgetFactory.h` (Private)


#### class `USceneOutlinerWidgetFactory`  
`class USceneOutlinerWidgetFactory : public UEditorDataStorageFactory`  
_L19-30_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- L24 _public prototype_ `~USceneOutlinerWidgetFactory() override = default;`
- L26 _public prototype_ `void RegisterWidgetPurposes(UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`
- L28 _public prototype_ `void RegisterWidgetConstructors(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::IUiProvider& DataStorageUi) const override;`

#### struct `FSceneOutlinerWidgetConstructor`  
`struct FSceneOutlinerWidgetConstructor : public FSimpleWidgetConstructor`  
_L33-47_
- reflection: `USTRUCT()`
- inherits: `FSimpleWidgetConstructor`
- L38 _public prototype_ `FSceneOutlinerWidgetConstructor();`
- L39 _public prototype_ `~FSceneOutlinerWidgetConstructor() override = default;`
- L41 _public prototype_ `virtual TSharedPtr<SWidget> CreateWidget( UE::Editor::DataStorage::ICoreProvider* DataStorage, UE::Editor::DataStorage::IUiProvider* DataStorageUi, UE::Editor::DataStorage::RowHandle TargetRow, UE::Editor::DataStorage::RowHandle WidgetRow, const UE::Editor::DataStorage::FMetaDataView& Arguments) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API TEDSOUTLINER_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace DataStorage` (scope `UE::Editor`)

### `Source/Editor/LevelEditor/Private/ViewportInteractions/LevelViewportClickSelection.h` (Private)


#### class `ULevelViewportClickSelection`  
`class ULevelViewportClickSelection : public UViewportClickInteraction, public IHoverBehaviorTarget`  
_L16-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportClickInteraction,IHoverBehaviorTarget`
- desc: Left-mouse click in level editor viewport, for elements selection
- L21 _public prototype_ `ULevelViewportClickSelection();`
- L23 _public prototype_ `virtual void OnClickDown(const FInputDeviceRay& InClickPos) override;`
- L25 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L26 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L27 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L28 _public prototype_ `virtual void OnEndHover() override;`
- L31 _protected prototype_ `virtual void BuildBehaviors() override;`
- L32 _protected prototype_ `virtual void ProcessClick_Internal(const FViewportClick& InViewportClick, HHitProxy* InHitProxy, FSceneView& View) override;`
- L35 _private member_ `TOptional<FVector2d> LastPosition;`
- L36 _private member_ `TOptional<bool> LastResult;`
- L37 _private member_ `TRefCountPtr<HHitProxy> LastProxy;`

#### class `ULevelViewportClickContextMenu`  
`class ULevelViewportClickContextMenu : public ULevelViewportClickSelection`  
_L44-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULevelViewportClickSelection`
- desc: Right-mouse click in level editor viewport, for selecting + summoning context menu
- L49 _public prototype_ `ULevelViewportClickContextMenu();`
- L52 _protected prototype_ `virtual void BuildBehaviors() override;`

#### class `ULevelViewportSetPivot`  
`class ULevelViewportSetPivot : public ULevelViewportClickSelection`  
_L59-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULevelViewportClickSelection`
- desc: Set the pivot based on click, for various meta-interactions
- L64 _public prototype_ `ULevelViewportSetPivot();`
- L67 _protected prototype_ `virtual void BuildBehaviors() override;`
- L69 _protected prototype_ `virtual void ProcessClick_Internal(const FViewportClick& InViewportClick, HHitProxy* InHitProxy, FSceneView& View) override;`

#### class `ULevelViewportDoubleClickBehavior`  
`class ULevelViewportDoubleClickBehavior : public UViewportClickBehavior`  
_L73-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportClickBehavior`
- L78 _protected prototype_ `virtual TOptional<FInputCapturePriority> GetCapturePriority(UE::Editor::ViewportInteractions::EInputStage Stage, const FInputDeviceState& InputState) const;`

#### class `ULevelViewportDoubleClick`  
`class ULevelViewportDoubleClick : public ULevelViewportClickSelection`  
_L85-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULevelViewportClickSelection`
- desc: Left-mouse double click
- L90 _public prototype_ `ULevelViewportDoubleClick();`
- L93 _protected prototype_ `virtual void BuildBehaviors() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Private/ViewportToolbar/LevelEditorSubmenus.h` (Private)


#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace LevelEditor` (scope `UE`)
- L17 _prototype_ `void CreateCameraSpawnMenu(UToolMenu* InMenu);` (scope `UE::LevelEditor`)
- L18 _prototype_ `void CreateBookmarksMenu(UToolMenu* InMenu);` (scope `UE::LevelEditor`)
- L19 _prototype_ `void AddCameraActorSelectSection(UToolMenu* InMenu);` (scope `UE::LevelEditor`)
- L21 _prototype_ `FToolMenuEntry CreateFOVMenu(TWeakPtr<SLevelViewport> InLevelViewportWeak);` (scope `UE::LevelEditor`)
- L22 _prototype_ `FToolMenuEntry CreateFarViewPlaneMenu(TWeakPtr<SLevelViewport> InLevelViewportWeak);` (scope `UE::LevelEditor`)
- L23 _prototype_ `FToolMenuEntry CreateCameraSpeedSlider(TWeakPtr<SLevelViewport> InLevelViewportWeak);` (scope `UE::LevelEditor`)
- L24 _prototype_ `FToolMenuEntry CreateCameraSpeedScalarSlider(TWeakPtr<SLevelViewport> InLevelViewportWeak);` (scope `UE::LevelEditor`)
- L25 _prototype_ `FToolMenuEntry CreateToolbarCameraSubmenu();` (scope `UE::LevelEditor`)
- L27 _prototype_ `TSharedPtr<FExtender> GetViewModesLegacyExtenders();` (scope `UE::LevelEditor`)
- L28 _prototype_ `void PopulateViewModesMenu(UToolMenu* InMenu);` (scope `UE::LevelEditor`)
- L29 _prototype_ `void ExtendViewModesSubmenu(FName InViewModesSubmenuName);` (scope `UE::LevelEditor`)
- L30 _prototype_ `FToolMenuEntry CreatePIEViewModesSubmenu();` (scope `UE::LevelEditor`)
- L32 _prototype_ `FToolMenuEntry CreateShowFoliageSubmenu();` (scope `UE::LevelEditor`)
- L33 _prototype_ `FToolMenuEntry CreateShowHLODsSubmenu();` (scope `UE::LevelEditor`)
- L34 _prototype_ `FToolMenuEntry CreateShowLayersSubmenu();` (scope `UE::LevelEditor`)
- L35 _prototype_ `FToolMenuEntry CreateShowSpritesSubmenu();` (scope `UE::LevelEditor`)
- L37 _prototype_ `FToolMenuEntry CreateShowStatsSubmenu( bool bInAddToggleStatsCheckbox = false, TAttribute<FText> InLabelOverride = TAttribute<FText>() );` (scope `UE::LevelEditor`)
- L41 _prototype_ `FToolMenuEntry CreateDynamicChannelsSubmenu();` (scope `UE::LevelEditor`)
- L42 _prototype_ `FToolMenuEntry CreateShowVolumesSubmenu();` (scope `UE::LevelEditor`)
- L43 _prototype_ `FToolMenuEntry CreateShowSubmenu();` (scope `UE::LevelEditor`)
- L44 _prototype_ `FToolMenuEntry CreatePIEShowSubmenu();` (scope `UE::LevelEditor`)
- L46 _prototype_ `FToolMenuEntry CreateFeatureLevelPreviewSubmenu();` (scope `UE::LevelEditor`)
- L47 _prototype_ `FToolMenuEntry CreateMaterialQualityLevelSubmenu();` (scope `UE::LevelEditor`)
- L48 _prototype_ `FToolMenuEntry CreatePerformanceAndScalabilitySubmenu();` (scope `UE::LevelEditor`)
- L49 _prototype_ `FToolMenuEntry CreatePIEPerformanceAndScalabilitySubmenu();` (scope `UE::LevelEditor`)
- L51 _prototype_ `void GenerateViewportLayoutsMenu(UToolMenu* InMenu);` (scope `UE::LevelEditor`)
- L52 _prototype_ `TSharedRef<SWidget> BuildVolumeControlCustomWidget();` (scope `UE::LevelEditor`)
- L53 _prototype_ `TSharedRef<SWidget> BuildPIEVolumeControlCustomWidget(const TWeakPtr<SLevelViewport>& Viewport);` (scope `UE::LevelEditor`)
- L54 _prototype_ `FToolMenuEntry CreateSettingsSubmenu();` (scope `UE::LevelEditor`)
- L55 _prototype_ `FToolMenuEntry CreatePIESettingsSubmenu();` (scope `UE::LevelEditor`)
- L57 _prototype_ `FToolMenuEntry CreateViewportSizingSubmenu();` (scope `UE::LevelEditor`)
- L59 _prototype_ `void ExtendCameraSubmenu(FName InCameraOptionsSubmenuName);` (scope `UE::LevelEditor`)
- L60 _prototype_ `void ExtendTransformSubmenu(FName InTransformSubmenuName);` (scope `UE::LevelEditor`)
- L61 _prototype_ `void ExtendSnappingSubmenu(FName InSnappingSubmenuName);` (scope `UE::LevelEditor`)

### `Source/Editor/LevelEditor/Private/ViewportToolbar/LevelViewportContext.h` (Private)


#### class `ULegacyLevelViewportToolbarContext`  
`class ULegacyLevelViewportToolbarContext : public ULevelViewportToolBarContext`  
_L18-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULevelViewportToolBarContext`
- desc: Customizes ULevelViewportToolBarContext for backwards compatability TODO: Remove this once the old toolbars are deprecated.
- L23 _public member_ `TWeakPtr<SLevelViewport> LevelViewport;`
- L25 _public prototype_ `virtual FLevelEditorViewportClient* GetLevelViewportClient() const override;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/DlgDeltaTransform.h` (Public)


#### class `FDlgDeltaTransform`  
`class FDlgDeltaTransform`  
_L20-55_
- desc: FDlgDeltaTransform Wrapper class for SDlgDeltaTransform. This class creates and launches the dialog then awaits the Result to return to the user.
- L32 _public prototype_ `FDlgDeltaTransform();` — Constructs A move Asset Dialog @param bInLegacyOrMapPackage		-	Used to handle moving into or out of map packages, or legacy packages. @param InPackage					-	Package information of the current asset @param InGroup					-	Group information of the current asset @param InName					-	Name information of the current asset
- L46 _public prototype_ `EResult ShowModal();` — Displays the dialog in a blocking fashion returns User response in EResult form.
- L51 _private member_ `TSharedPtr<SWindow> DeltaTransformWindow;` — Cached pointer to the modal window
- L54 _private member_ `TSharedPtr<class SDlgDeltaTransform> DeltaTransformWidget;` — Cached pointer to the message box held within the window

#### enum `FDlgDeltaTransform::EResult`  
`enum EResult`  
_L35-39_
- desc: Custom result types
- L37 _public enumerator_ `Cancel = 0`
- L38 _public enumerator_ `OK`

### `Source/Editor/LevelEditor/Public/Elements/Actor/ActorElementLevelEditorViewportInteractionCustomization.h` (Public)


#### class `FActorElementLevelEditorViewportInteractionCustomization`  
`class FActorElementLevelEditorViewportInteractionCustomization : public FActorElementEditorViewportInteractionCustomization, public FTypedElementAssetEditorLevelEditorViewportClientMixin`  
_L10-20_
- inherits: `FActorElementEditorViewportInteractionCustomization,FTypedElementAssetEditorLevelEditorViewportClientMixin`
- L13 _public prototype_ `virtual void GizmoManipulationStarted(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode) override;`
- L14 _public prototype_ `virtual void GizmoManipulationDeltaUpdate(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode, const EAxisList::Type InDragAxis, const FInputDeviceState& InInputState, const FTransform& InDeltaTransform, const FVector& InPivotLocation) override;`
- L15 _public prototype_ `virtual void GizmoManipulationStopped(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode, const ETypedElementViewportInteractionGizmoManipulationType InManipulationType) override;`
- L16 _public prototype_ `virtual void PostGizmoManipulationStopped(TArrayView<const FTypedElementHandle> InElementHandles, const UE::Widget::EWidgetMode InWidgetMode) override;`
- L19 _private prototype_ `void ModifyScale(AActor* InActor, const EAxisList::Type InDragAxis, FVector& ScaleDelta, bool bCheckSmallExtent);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/Elements/Component/ComponentElementLevelEditorViewportInteractionCustomization.h` (Public)


#### class `FComponentElementLevelEditorViewportInteractionCustomization`  
`class FComponentElementLevelEditorViewportInteractionCustomization : public FComponentElementEditorViewportInteractionCustomization, public FTypedElementAssetEditorLevelEditorViewportClientMixin`  
_L12-24_
- inherits: `FComponentElementEditorViewportInteractionCustomization,FTypedElementAssetEditorLevelEditorViewportClientMixin`
- L15 _public prototype_ `virtual void GizmoManipulationStarted(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode) override;`
- L16 _public prototype_ `virtual void GizmoManipulationDeltaUpdate(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode, const EAxisList::Type InDragAxis, const FInputDeviceState& InInputState, const FTransform& InDeltaTransform, const FVector& InPivotLocation) override;`
- L17 _public prototype_ `virtual void GizmoManipulationStopped(const TTypedElement<ITypedElementWorldInterface>& InElementWorldHandle, const UE::Widget::EWidgetMode InWidgetMode, const ETypedElementViewportInteractionGizmoManipulationType InManipulationType) override;`
- L19 _public prototype_ `static void ValidateScale(const FVector& InOriginalPreDragScale, const EAxisList::Type InDragAxis, const FVector& InCurrentScale, const FVector& InBoxExtent, FVector& InOutScaleDelta, bool bInCheckSmallExtent);`
- L20 _public prototype_ `static FProperty* GetEditTransformProperty(const UE::Widget::EWidgetMode InWidgetMode);`
- L23 _private prototype_ `void ModifyScale(USceneComponent* InComponent, const EAxisList::Type InDragAxis, FVector& ScaleDelta);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/Elements/Framework/TypedElementAssetEditorLevelEditorViewportClientMixin.h` (Public)


#### class `FTypedElementAssetEditorLevelEditorViewportClientMixin`  
`class FTypedElementAssetEditorLevelEditorViewportClientMixin`  
_L12-42_
- desc: Mixin for asset editor customizations that provides access to the owner level editor viewport client.
- L18 _public function_ `const FLevelEditorViewportClient* GetLevelEditorViewportClient() const` — Get the owner level editor viewport client.
- L26 _public function_ `FLevelEditorViewportClient* GetMutableLevelEditorViewportClient()` — Get the owner level editor viewport client.
- L34 _public function_ `void SetLevelEditorViewportClient(FLevelEditorViewportClient* InLevelEditorViewportClient)` — Set the owner level editor viewport client.
- L41 _private member_ `FLevelEditorViewportClient* LevelEditorViewportClient = nullptr;` — The owner level editor viewport client.

### `Source/Editor/LevelEditor/Public/ILevelEditor.h` (Public)


#### class `ILevelEditor`  
`class ILevelEditor : public SCompoundWidget, public IToolkitHost`  
_L29-104_
- inherits: `SCompoundWidget,IToolkitHost`
- desc: Public interface to SLevelEditor
- L35 _public prototype_ `virtual const UTypedElementSelectionSet* GetElementSelectionSet() const = 0;` — Get the element selection set used by this level editor
- L36 _public prototype_ `virtual UTypedElementSelectionSet* GetMutableElementSelectionSet() = 0;`
- L39 _public prototype_ `virtual void SummonLevelViewportContextMenu(const FTypedElementHandle& HitProxyElement = FTypedElementHandle()) = 0;` — Summons a context menu for this level editor at the mouse cursor's location
- L42 _public prototype_ `virtual FText GetLevelViewportContextMenuTitle() const = 0;` — Gets the title for the context menu for this level editor
- L45 _public prototype_ `virtual void SummonLevelViewportViewOptionMenu(ELevelViewportType ViewOption) = 0;` — Summons a context menu for view options
- L48 _public prototype_ `virtual const TArray< TSharedPtr< IToolkit > >& GetHostedToolkits() const = 0;` — Returns a list of all of the toolkits that are currently hosted by this toolkit host
- L51 _public prototype_ `virtual TArray< TSharedPtr< SLevelViewport > > GetViewports() const = 0;` — Gets an array of all viewports in this level editor
- L57 _public prototype_ `virtual TMap< int32, TArray< TSharedPtr< SLevelViewport > > > GetViewportsByTab() const = 0;` — Gets a list of all the viewport tabs in this level editor mapped to arrays of all viewports in that tab. There are 4 viewport tabs, mapped to 0 to 3. Standalone viewports are mapped to index 4.
- L60 _public prototype_ `virtual TSharedPtr<SLevelViewport> GetActiveViewportInterface() = 0;` — Gets the active level viewport for this level editor
- L63 _public prototype_ `virtual const TSharedPtr< FUICommandList >& GetLevelEditorActions() const = 0;` — Access the level editor's action command list
- L66 _public prototype_ `virtual FReply OnKeyDownInViewport( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) = 0;` — Called to process a key down event in a viewport when in immersive mode
- L69 _public prototype_ `virtual void AppendCommands( const TSharedRef<FUICommandList>& InCommandsToAppend ) = 0;` — Append commands to the command list for the level editor
- L73 _public prototype_ `virtual void AddStandaloneLevelViewport( const TSharedRef<SLevelViewport>& LevelViewport ) = 0;` — After spawning a new level viewport outside of the editor's tab system, this function must be called so that the editor can keep track of that viewport
- L76 _public prototype_ `virtual TSharedRef<SWidget> CreateActorDetails( const FName TabIdentifier ) = 0;` — Spawns an Actor Details widget
- L79 _public prototype_ `virtual void SetActorDetailsRootCustomization(TSharedPtr<FDetailsViewObjectFilter> ActorDetailsObjectFilter, TSharedPtr<IDetailRootObjectCustomization> ActorDetailsRootCustomization) = 0;` — Set the filter that should be used to determine the set of objects that should be shown in a details panel when an actor in the level editor is selected
- L82 _public prototype_ `virtual void AddActorDetailsSCSEditorUICustomization(TSharedPtr<class ISCSEditorUICustomization> ActorDetailsSCSEditorUICustomization) = 0;` — Adds the UI customization of the SCSEditor inside the level editor details panel.
- L85 _public prototype_ `virtual void RemoveActorDetailsSCSEditorUICustomization(TSharedPtr<class ISCSEditorUICustomization> ActorDetailsSCSEditorUICustomization) = 0;` — Remove the UI customization of the SCSEditor inside the level editor details panel.
- L88 _public function_ `virtual void SetActorDetailsSCSEditorUICustomization(TSharedPtr<class ISCSEditorUICustomization> ActorDetailsSCSEditorUICustomization)` — `UE_DEPRECATED(5.5, "Use AddActorDetailsSCSEditorUICustomization/RemoveActorDetailsSCSEditorUICustomization instead.")`
- L91 _public prototype_ `virtual void GetSceneOutlinerInitializationOptions(const FName TabIdentifier, FSceneOutlinerInitializationOptions& OutInitOptions) = 0;` — Gets the default FSceneOutlinerInitializationOptions for this Level Editor's Scene Outliners
- L94 _public prototype_ `virtual TArray<TWeakPtr<ISceneOutliner>> GetAllSceneOutliners() const = 0;` — Get an array containing weak pointers to all 4 Scene Outliners which could be potentially active
- L97 _public prototype_ `virtual void SetMostRecentlyUsedSceneOutliner(FName OutlinerIdentifier) = 0;` — Set the outliner with the given name as the most recently interacted with
- L100 _public prototype_ `virtual TSharedPtr<ISceneOutliner> GetMostRecentlyUsedSceneOutliner() = 0;` — Return the most recently interacted with Outliner
- L103 _public prototype_ `virtual TWeakPtr<UE::WorldHierarchy::IWorldHierarchy> GetWorldHierarchy() = 0;` — @return The widget displayed in the Levels tab, if the tab is summoned.

#### Free symbols / members of external scopes

- L24 _namespace_ `namespace UE`
- L24 _namespace_ `namespace WorldHierarchy` (scope `UE`)

### `Source/Editor/LevelEditor/Public/LevelEditor.h` (Public)


#### class `LevelEditorTabIds`  
`class LevelEditorTabIds`  
_L33-65_
- L36 _public member_ `static const FName LevelEditorViewport;`
- L37 _public member_ `static const FName LevelEditorViewport_Clone1;`
- L38 _public member_ `static const FName LevelEditorViewport_Clone2;`
- L39 _public member_ `static const FName LevelEditorViewport_Clone3;`
- L40 _public member_ `static const FName LevelEditorViewport_Clone4;`
- L41 _public member_ `static const FName LevelEditorToolBox;`
- L42 _public member_ `static const FName LevelEditorSelectionDetails;`
- L43 _public member_ `static const FName LevelEditorSelectionDetails2;`
- L44 _public member_ `static const FName LevelEditorSelectionDetails3;`
- L45 _public member_ `static const FName LevelEditorSelectionDetails4;`
- L46 _public member_ `static const FName PlacementBrowser;`
- L47 _public member_ `static const FName LevelEditorBuildAndSubmit;`
- L48 _public member_ `static const FName LevelEditorSceneOutliner;`
- L49 _public member_ `static const FName LevelEditorSceneOutliner2;`
- L50 _public member_ `static const FName LevelEditorSceneOutliner3;`
- L51 _public member_ `static const FName LevelEditorSceneOutliner4;`
- L52 _public member_ `static const FName LevelEditorStatsViewer;`
- L53 _public member_ `static const FName LevelEditorLayerBrowser;`
- L54 _public member_ `static const FName LevelEditorDataLayerBrowser;`
- L55 _public member_ `static const FName Sequencer;`
- L56 _public member_ `static const FName SequencerGraphEditor;`
- L57 _public member_ `static const FName WorldSettings;`
- L58 _public member_ `static const FName WorldBrowserComposition;`
- L59 _public member_ `static const FName WorldBrowserPartitionEditor;`
- L60 _public member_ `static const FName WorldBrowserHierarchy;`
- L61 _public member_ `static const FName WorldBrowserDetails;`
- L62 _public member_ `static const FName LevelEditorHierarchicalLODOutliner;`
- L63 _public member_ `static const FName OutputLog;`
- L64 _public member_ `static const FName LevelEditorEnvironmentLightingViewer;`

#### class `FLevelEditorModule`  
`class FLevelEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility`  
_L70-550_
- inherits: `IModuleInterface,IHasMenuExtensibility,IHasToolBarExtensibility`
- desc: Level editor module
- L75 _public prototype_ `FLevelEditorModule();` — Constructor, set up console commands and variables
- L80 _public prototype_ `virtual void StartupModule() override;` — Called right after the module DLL has been loaded and the module object has been created
- L85 _public prototype_ `virtual void ShutdownModule() override;` — Called before the module is unloaded, right before the module object is destroyed.
- L92 _public function_ `virtual bool SupportsDynamicReloading() override` — Override this to set whether your module is allowed to be unloaded on the fly @return Whether the module supports shutdown separate from the rest of the engine.
- L102 _public prototype_ `virtual void SummonSelectionDetails();` — Spawns a new property viewer @todo This only works with the first level editor. Fix it.
- L108 _public prototype_ `virtual void SummonBuildAndSubmit();` — Spawns a new build and submit widget @todo This only works with the first level editor. Fix it.
- L110 _public prototype_ `virtual void SummonWorldBrowserHierarchy();`
- L111 _public prototype_ `virtual void SummonWorldBrowserDetails();`
- L112 _public prototype_ `virtual void SummonWorldBrowserComposition();`
- L119 _public prototype_ `virtual TSharedPtr<SDockTab> AttachSequencer(TSharedPtr<SWidget> SequencerWidget, TSharedPtr<class IAssetEditorInstance> SequencerAssetEditor );` — Spawns a new sequencer tab if one doesn't exist already @todo This only works with the first level editor. Fix it.
- L124 _public prototype_ `virtual void StartPlayInEditorSession();` — Starts a play in editor session using the active viewport
- L129 _public prototype_ `virtual void GoImmersiveWithActiveLevelViewport( const bool bForceGameView );` — Takes the first active viewport and switches it to immersive mode.  Designed to be called at editor startup.  Optionally forces the viewport into game view mode too.
- L134 _public prototype_ `virtual void ToggleImmersiveOnActiveLevelViewport();` — Toggles immersive mode on the currently active level viewport
- L137 _public prototype_ `virtual TSharedPtr< class ILevelEditor > GetFirstLevelEditor() const;` — @return Returns the first Level Editor that we currently know about
- L140 _public prototype_ `virtual TSharedPtr<SDockTab> GetLevelEditorTab() const;` — @return the dock tab in which the level editor currently resides.
- L147 _public prototype_ `virtual TSharedPtr<class IAssetViewport> GetFirstActiveViewport();` — Gets the first active viewport of all the viewports. @todo This only works with the first level editor. Fix it.
- L154 _public prototype_ `virtual TSharedPtr<class SLevelViewport> GetFirstActiveLevelViewport();` — Gets the first active viewport of all the viewports. @todo This only works with the first level editor. Fix it.
- L159 _public prototype_ `virtual void FocusPIEViewport();` — Called to focus the level editor that has a play in editor viewport
- L164 _public prototype_ `virtual void FocusViewport();` — Called to focus the level editor viewport
- L169 _public function_ `virtual const TSharedRef<FUICommandList> GetGlobalLevelEditorActions() const` — @return The list of bound level editor commands that are common to all level editors
- L174 _public prototype_ `virtual const class FLevelEditorCommands& GetLevelEditorCommands() const;` — Method for getting level editor commands outside of this module
- L179 _public prototype_ `virtual const class FLevelEditorModesCommands& GetLevelEditorModesCommands() const;` — Method for getting level editor modes commands outside of this module
- L184 _public prototype_ `virtual const class FLevelViewportCommands& GetLevelViewportCommands() const;` — Method for getting level viewport commands outside of this module
- L187 _public prototype_ `virtual TWeakPtr<class ILevelEditor> GetLevelEditorInstance() const;` — @return The pointer to the current level Editor instance
- L190 _public prototype_ `virtual TWeakPtr<class SDockTab> GetLevelEditorInstanceTab() const;` — @return The pointer to the level editor tab
- L193 _public prototype_ `virtual TSharedPtr<FTabManager> GetLevelEditorTabManager() const;` — @return The pointer to the level editor tab manager
- L196 _public prototype_ `virtual void SetLevelEditorInstance( TWeakPtr<class SLevelEditor> LevelEditor );` — Set the pointer to the current level Editor instance
- L199 _public prototype_ `virtual void SetLevelEditorInstanceTab( TWeakPtr<class SDockTab> LevelEditorTab );` — Set the pointer to the level editor tab
- L202 _public prototype_ `virtual void SetLevelEditorTabManager( const TSharedPtr<SDockTab>& OwnerTab );` — Create a tab manager for the level editor based on the given tab (or clears the tab manager if OwnerTab is null)
- L205 _public prototype_ `DECLARE_EVENT(FLevelEditorModule, FTabManagerChangedEvent);` — Called when the tab manager is changed
- L206 _public function_ `virtual FTabManagerChangedEvent& OnTabManagerChanged()`
- L209 _public prototype_ `DECLARE_EVENT(FLevelEditorModule, FTabContentChangedEvent);` — Called when the tab content is changed
- L210 _public function_ `virtual FTabContentChangedEvent& OnTabContentChanged()`
- L213 _public prototype_ `DECLARE_EVENT_OneParam(FLevelEditorModule, FOnLevelEditorCreated, TSharedPtr<ILevelEditor>);` — Called when a level editor widget has been created
- L214 _public function_ `virtual FOnLevelEditorCreated& OnLevelEditorCreated()`
- L221 _public prototype_ `virtual void BroadcastActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh=false);` — Called when actor selection changes @param NewSelection	List of objects that are now selected
- L228 _public prototype_ `virtual void BroadcastElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh=false);` — Called when element selection changes @param SelectionSet	Set of selected elements
- L235 _public prototype_ `virtual void BroadcastOverridePropertyEditorSelection(const TArray<AActor*>& NewSelection, bool bForceRefresh=false);` — Called to set property editors to show the given actors, even if those actors aren't in the current selection set @param NewSelection	List of actors to edit the properties of
- L242 _public prototype_ `virtual void BroadcastRedrawViewports( bool bInvalidateHitProxies );` — Called by the engine when level editing viewports need to be redrawn @param bInvalidateHitProxies	true to invalidate hit proxies
- L248 _public prototype_ `virtual void BroadcastTakeHighResScreenShots( );` — Called by the engine when level editing viewports need to take a high res screenshot
- L255 _public prototype_ `virtual void BroadcastMapChanged( UWorld* World, EMapChangeType MapChangeType );` — Called by the engine when a new map is loaded @param World	The new world
- L258 _public prototype_ `virtual void BroadcastComponentsEdited();` — Called when an edit command is executed on one or more components in the world
- L261 _public prototype_ `DECLARE_EVENT_TwoParams(FLevelEditorModule, FActorSelectionChangedEvent, const TArray<UObject*>&, bool);` — Called when actor selection changes
- L262 _public function_ `virtual FActorSelectionChangedEvent& OnActorSelectionChanged()`
- L265 _public prototype_ `DECLARE_EVENT_TwoParams(FLevelEditorModule, FElementSelectionChangedEvent, const UTypedElementSelectionSet*, bool);` — Called when element selection changes
- L266 _public function_ `virtual FElementSelectionChangedEvent& OnElementSelectionChanged()`
- L269 _public prototype_ `DECLARE_EVENT_TwoParams(FLevelEditorModule, FOverridePropertyEditorSelectionEvent, const TArray<AActor*>&, bool);` — Called to set property editors to show the given actors, even if those actors aren't in the current selection set
- L270 _public function_ `virtual FOverridePropertyEditorSelectionEvent& OnOverridePropertyEditorSelection()`
- L273 _public prototype_ `DECLARE_EVENT_OneParam( FLevelEditorModule, FRedrawLevelEditingViewportsEvent, bool );` — Called when level editor viewports should be redrawn
- L274 _public function_ `virtual FRedrawLevelEditingViewportsEvent& OnRedrawLevelEditingViewports()`
- L277 _public prototype_ `DECLARE_EVENT_TwoParams( FLevelEditorModule, FMapChangedEvent, UWorld*, EMapChangeType );` — Called when a new map is loaded
- L278 _public function_ `virtual FMapChangedEvent& OnMapChanged()`
- L281 _public prototype_ `DECLARE_EVENT(FLevelEditorModule, FComponentsEditedEvent);` — Called when an edit command is executed on components in the world
- L282 _public function_ `virtual FComponentsEditedEvent& OnComponentsEdited()`
- L285 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FLevelEditorMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the level viewport menus
- L286 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<FExtender>, FLevelViewportMenuExtender_SelectedObjects, const TSharedRef<FUICommandList>, const TArray<UObject*>);`
- L287 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<FExtender>, FLevelViewportMenuExtender_SelectedActors, const TSharedRef<FUICommandList>, const TArray<AActor*>);`
- L288 _public function_ `virtual TArray<FLevelViewportMenuExtender_SelectedObjects>& GetAllLevelViewportDragDropContextMenuExtenders()`
- L289 _public function_ `virtual TArray<FLevelViewportMenuExtender_SelectedActors>& GetAllLevelViewportContextMenuExtenders()`
- L290 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelViewportOptionsMenuExtenders()`
- L291 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelViewportShowMenuExtenders()`
- L292 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelEditorToolbarViewMenuExtenders()`
- L293 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelEditorToolbarBuildMenuExtenders()`
- L294 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelEditorToolbarCompileMenuExtenders()`
- L295 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelEditorToolbarSourceControlMenuExtenders()`
- L296 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelEditorToolbarCreateMenuExtenders()`
- L297 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelEditorToolbarPlayMenuExtenders()`
- L298 _public function_ `virtual TArray<TSharedPtr<FExtender>>& GetAllLevelEditorToolbarBlueprintsMenuExtenders()`
- L299 _public function_ `virtual TArray<TSharedPtr<FExtender>>& GetAllLevelEditorToolbarCinematicsMenuExtenders()`
- L300 _public function_ `virtual TArray<FLevelEditorMenuExtender>& GetAllLevelEditorLevelMenuExtenders()`
- L303 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override` — Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars
- L304 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override`
- L305 _public function_ `virtual TSharedPtr<FExtensibilityManager> GetModeBarExtensibilityManager()`
- L307 _public prototype_ `virtual TSharedPtr<FExtender> AssembleExtenders(TSharedRef<FUICommandList>& InCommandList, TArray<FLevelEditorMenuExtender>& MenuExtenderDelegates) const;`
- L309 _public prototype_ `DECLARE_EVENT_OneParam(ILevelEditor, FOnRegisterTabs, TSharedPtr<FTabManager>);`
- L310 _public function_ `FOnRegisterTabs& OnRegisterTabs()`
- L312 _public prototype_ `DECLARE_EVENT_OneParam(ILevelEditor, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L313 _public function_ `FOnRegisterLayoutExtensions& OnRegisterLayoutExtensions()`
- L325 _public function_ `const TMap<FName, FTitleBarItem>& GetTitleBarItems() const`
- L326 _public prototype_ `virtual void AddTitleBarItem(FName InTitleBarIdentifier, const FTitleBarItem& InTitleBarITem);`
- L327 _public prototype_ `virtual void RemoveTitleBarItem(FName InTitleBarIdentifier);`
- L330 _public prototype_ `DECLARE_EVENT( FLevelEditorModule, FTitleBarMessagesChanged );` — Called when a new map is loaded
- L331 _public function_ `virtual FTitleBarMessagesChanged& OnTitleBarMessagesChanged()`
- L333 _public function_ `virtual void BroadcastTitleBarMessagesChanged()`
- L336 _public prototype_ `DECLARE_EVENT( FLevelEditorModule, FTakeHighResScreenShotsEvent );` — Called when a high res screenshot is requested.
- L337 _public function_ `virtual FTakeHighResScreenShotsEvent& OnTakeHighResScreenShots()`
- L340 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(UAnimSequence*, FCaptureSingleFrameAnimSequence, USkeletalMeshComponent* );` — Delegate used to capture skeletal meshes to single-frame animations when 'keeping simulation changes'
- L341 _public function_ `virtual FCaptureSingleFrameAnimSequence& OnCaptureSingleFrameAnimSequence()`
- L344 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FGetVisualizeCheckerboardEnabled);` — Delegate used to determine if users should be able to enable the alpha-blended checkerboard for the level viewport
- L345 _public function_ `virtual FGetVisualizeCheckerboardEnabled& OnGetVisualizeCheckerboardEnabled()`
- L353 _public prototype_ `virtual void AddCustomFilterToOutliner(TSharedRef<FFilterBase<const ISceneOutlinerTreeItem&>> InCustomFilter);` — `UE_DEPRECATED(5.2, "Use the AddCustomFilterToOutliner override that takes in a delegate instead so each Outliner can have a unique instance of the filter")` — Add a custom filter to the outliner filter bar. These are all AND'd together @see FLevelEditorOutlinerSettings @see FGenericFilter on how to create generic filters NOTE: Currently does not support adding filters dynamically, they must be added before the Level Editor is init
- L360 _public prototype_ `virtual void AddCustomFilterToOutliner(FLevelEditorOutlinerSettings::FOutlinerFilterFactory InCreateCustomFilter);` — Add a custom filter to the outliner filter bar. These are all AND'd together This function takes in a delegate that will be called to create an instance of the custom filter for each Outliner that the level editor creates. @see FGenericFilter on how to create generic filters
- L367 _public prototype_ `virtual void AddCustomClassFilterToOutliner(TSharedRef<FCustomClassFilterData> InCustomClassFilterData);` — Add a custom class filter to the outliner filter bar. These represent asset/actor type filters and are OR'd @see FLevelEditorOutlinerSettings Can be created using IAssetTypeActions or UClass (@see constructor) NOTE: Currently does not support adding filters dynamically, they must be added before the Level Editor is init
- L372 _public prototype_ `virtual TSharedPtr<FFilterCategory> GetOutlinerFilterCategory(const FName& CategoryName) const;` — Get the FFilterCategory attached to the given category name. Use this to add filters to the built in categories @see FLevelEditorOutlinerBuiltInCategories
- L377 _public function_ `void AddEditableObjectPredicate(const FAreObjectsEditable& InPredicate)` — Add a delegate that will get called to check whether the specified objects should be editable on the details panel or not
- L384 _public function_ `void RemoveEditableObjectPredicate(FDelegateHandle InPredicateHandle)` — Remove a delegate that was added via AddEditableObjectPredicate
- L390 _public function_ `bool AreObjectsEditable(const TArray<TWeakObjectPtr<UObject>>& InObjects) const` — Check whether the specified objects are editable
- L403 _public prototype_ `virtual TSharedPtr<FLevelEditorOutlinerSettings> GetLevelEditorOutlinerSettings() const;` — Return the settings (containing the outliner filters) used to create the level editor's outliners
- L406 _public prototype_ `virtual void RefreshLevelEditorOutliners() const;` — Refresh all of the level editor's outliners (close and recreate them)
- L411 _public function_ `void RegisterViewportType(FName InLayoutName, const FViewportTypeDefinition& InDefinition)` — Register a viewport type for the level editor
- L417 _public function_ `void UnregisterViewportType(FName InLayoutName)` — Unregister a previously registered viewport type
- L423 _public function_ `void IterateViewportTypes(TFunctionRef<void(FName, const FViewportTypeDefinition&)> Iter)` — Iterate all registered viewport types
- L433 _public prototype_ `TSharedRef<ILevelViewportLayoutEntity> FactoryViewport(FName InTypeName, const FAssetEditorViewportConstructionArgs& ConstructionArgs) const;` — `UE_DEPRECATED(4.26, "Use FactoryViewport from inside of a FLevelViewportTabContent.")` — Create an instance of a custom viewport from the specified viewport type name
- L439 _private prototype_ `void BindGlobalLevelEditorCommands();` — Binds all global level editor commands to delegates
- L442 _private function_ `void HandleTabManagerPersistLayout( const TSharedRef<FTabManager::FLayout>& LayoutToSave )` — Callback for persisting the Level Editor's layout.
- L448 _private prototype_ `TSharedRef<SDockTab> SpawnLevelEditor( const FSpawnTabArgs& InArgs );` — Spawn the main level editor tab
- L451 _private prototype_ `void OnExtendTabContextMenu(FMenuBuilder& InMenuBuilder);` — Extend the dock tab context menu
- L454 _private prototype_ `bool OnCanBrowseLevelInContentBrowser();` — Is the active level an asset that can be browsed to
- L457 _private prototype_ `void OnBrowseLevelInContentBrowser();` — Browse to active level in content browser
- L460 _private member_ `TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;`
- L461 _private member_ `TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;`
- L462 _private member_ `TSharedPtr<FExtensibilityManager> ModeBarExtensibilityManager;`
- L463 _private member_ `TSharedPtr<FExtensibilityManager> NotificationBarExtensibilityManager;`
- L465 _private member_ `TMap<FName, FTitleBarItem> TitleBarItems;`
- L466 _private member_ `FTitleBarMessagesChanged TitleBarMessagesChangedEvent;`
- L472 _private member_ `TSharedPtr<FUICommandList> GlobalLevelEditorActions;` — A command list that can be passed around and isn't bound to an instance of a level editor. Only commands that arent bound to an instance of SLevelEditor should be used here (like level context menu commands)
- L474 _private member_ `FAutoConsoleCommand ToggleImmersiveConsoleCommand;`
- L477 _private member_ `FTabManagerChangedEvent TabManagerChangedEvent;` — Multicast delegate executed when the tab manager is changed
- L480 _private member_ `FTabContentChangedEvent TabContentChangedEvent;` — Multicast delegate executed when the tab content is changed
- L483 _private member_ `FOnLevelEditorCreated LevelEditorCreatedEvent;` — Multicast delegate executed when a level editor has been created
- L486 _private member_ `FActorSelectionChangedEvent ActorSelectionChangedEvent;` — Multicast delegate executed when actor selection changes
- L489 _private member_ `FElementSelectionChangedEvent ElementSelectionChangedEvent;` — Multicast delegate executed when element selection changes
- L492 _private member_ `FOverridePropertyEditorSelectionEvent OverridePropertyEditorSelectionEvent;` — Multicast delegate executed to set property editors to show the given actors, even if those actors aren't in the current selection set
- L495 _private member_ `FRedrawLevelEditingViewportsEvent RedrawLevelEditingViewportsEvent;` — Multicast delegate executed when viewports should be redrawn
- L498 _private member_ `FComponentsEditedEvent ComponentsEditedEvent;` — Multicast delegate executed after components are edited in the world
- L501 _private member_ `FTakeHighResScreenShotsEvent TakeHighResScreenShotsEvent;` — Multicast delegate executed when viewports should be redrawn
- L504 _private member_ `FMapChangedEvent MapChangedEvent;` — Multicast delegate executed when a map is changed (loaded,saved,new map, etc)
- L507 _private member_ `FCaptureSingleFrameAnimSequence CaptureSingleFrameAnimSequenceDelegate;` — Delegate used to capture skeletal meshes to single-frame animations when 'keeping simulation changes'
- L510 _private member_ `FGetVisualizeCheckerboardEnabled GetVisualizeCheckerboardEnabled;` — Delegate used to determine if 'Visualize Alpha with Checkerboard' checkbox is enabled in the level viewports
- L513 _private member_ `TArray<FLevelViewportMenuExtender_SelectedObjects> LevelViewportDragDropContextMenuExtenders;` — All extender delegates for the level viewport menus
- L514 _private member_ `TArray<FLevelViewportMenuExtender_SelectedActors> LevelViewportContextMenuExtenders;`
- L515 _private member_ `TArray<FLevelEditorMenuExtender> LevelViewportOptionsMenuExtenders;`
- L516 _private member_ `TArray<FLevelEditorMenuExtender> LevelViewportShowMenuExtenders;`
- L517 _private member_ `TArray<FLevelEditorMenuExtender> LevelEditorToolbarViewMenuExtenders;`
- L518 _private member_ `TArray<FLevelEditorMenuExtender> LevelEditorToolbarBuildMenuExtenders;`
- L519 _private member_ `TArray<FLevelEditorMenuExtender> LevelEditorToolbarCompileMenuExtenders;`
- L520 _private member_ `TArray<FLevelEditorMenuExtender> LevelEditorToolbarSourceControlMenuExtenders;`
- L521 _private member_ `TArray<FLevelEditorMenuExtender> LevelEditorToolbarCreateMenuExtenders;`
- L522 _private member_ `TArray<FLevelEditorMenuExtender> LevelEditorToolbarPlayMenuExtenders;`
- L523 _private member_ `TArray<TSharedPtr<FExtender>> LevelEditorToolbarCinematicsMenuExtenders;`
- L524 _private member_ `TArray<TSharedPtr<FExtender>> LevelEditorToolbarBlueprintsMenuExtenders;`
- L525 _private member_ `TArray<FLevelEditorMenuExtender> LevelEditorLevelMenuExtenders;`
- L528 _private member_ `TWeakPtr<class SLevelEditor> LevelEditorInstancePtr;` — Pointer to the current level Editor instance
- L531 _private member_ `TWeakPtr<class SDockTab> LevelEditorInstanceTabPtr;` — Pointer to the level editor tab
- L534 _private member_ `TSharedPtr<FTabManager> LevelEditorTabManager;` — Holds the Editor's tab manager
- L537 _private member_ `TMap<FName, FViewportTypeDefinition> CustomViewports;` — Map of named viewport types to factory functions
- L540 _private member_ `FOnRegisterLayoutExtensions RegisterLayoutExtensions;` — Register layout extensions event
- L543 _private member_ `FOnRegisterTabs RegisterTabs;` — Register external tabs event
- L546 _private member_ `TArray<FAreObjectsEditable> AreObjectsEditableDelegates;` — Array of delegates that are used to check if the specified objects should be editable on the details panel
- L549 _private member_ `TSharedPtr<FLevelEditorOutlinerSettings> OutlinerSettings;` — The settings used to create any Outliners in the Level Editor

#### struct `FLevelEditorModule::FTitleBarItem`  
`struct FTitleBarItem`  
_L316-324_
- desc: Add / Remove title bar item
- L319 _public member_ `TAttribute<EVisibility> Visibility;` — Visiblility of the title bar item.
- L321 _public member_ `TAttribute<FText> Label;` — Label of the title bar item.
- L323 _public member_ `TAttribute<FText> Value;` — Value of the title bar item.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API LEVELEDITOR_API`
- L29 _externvar_ `extern const FName LevelEditorApp;`
- L31 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAreObjectsEditable, const TArray<TWeakObjectPtr<UObject>>&);`
- L31 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FAreObjectsEditable, const TArray<TWeakObjectPtr<UObject>>&);`
- L205 _delegate_ `DECLARE_EVENT(FLevelEditorModule, FTabManagerChangedEvent);` — Called when the tab manager is changed
- L209 _delegate_ `DECLARE_EVENT(FLevelEditorModule, FTabContentChangedEvent);` — Called when the tab content is changed
- L213 _delegate_ `DECLARE_EVENT_OneParam(FLevelEditorModule, FOnLevelEditorCreated, TSharedPtr<ILevelEditor>);` — Called when a level editor widget has been created
- L261 _delegate_ `DECLARE_EVENT_TwoParams(FLevelEditorModule, FActorSelectionChangedEvent, const TArray<UObject*>&, bool);` — Called when actor selection changes
- L265 _delegate_ `DECLARE_EVENT_TwoParams(FLevelEditorModule, FElementSelectionChangedEvent, const UTypedElementSelectionSet*, bool);` — Called when element selection changes
- L269 _delegate_ `DECLARE_EVENT_TwoParams(FLevelEditorModule, FOverridePropertyEditorSelectionEvent, const TArray<AActor*>&, bool);` — Called to set property editors to show the given actors, even if those actors aren't in the current selection set
- L273 _delegate_ `DECLARE_EVENT_OneParam( FLevelEditorModule, FRedrawLevelEditingViewportsEvent, bool );` — Called when level editor viewports should be redrawn
- L277 _delegate_ `DECLARE_EVENT_TwoParams( FLevelEditorModule, FMapChangedEvent, UWorld*, EMapChangeType );` — Called when a new map is loaded
- L281 _delegate_ `DECLARE_EVENT(FLevelEditorModule, FComponentsEditedEvent);` — Called when an edit command is executed on components in the world
- L285 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam( TSharedRef<FExtender>, FLevelEditorMenuExtender, const TSharedRef<FUICommandList>);` — Delegates to be called to extend the level viewport menus
- L286 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<FExtender>, FLevelViewportMenuExtender_SelectedObjects, const TSharedRef<FUICommandList>, const TArray<UObject*>);`
- L287 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams( TSharedRef<FExtender>, FLevelViewportMenuExtender_SelectedActors, const TSharedRef<FUICommandList>, const TArray<AActor*>);`
- L309 _delegate_ `DECLARE_EVENT_OneParam(ILevelEditor, FOnRegisterTabs, TSharedPtr<FTabManager>);`
- L312 _delegate_ `DECLARE_EVENT_OneParam(ILevelEditor, FOnRegisterLayoutExtensions, FLayoutExtender&);`
- L330 _delegate_ `DECLARE_EVENT( FLevelEditorModule, FTitleBarMessagesChanged );` — Called when a new map is loaded
- L336 _delegate_ `DECLARE_EVENT( FLevelEditorModule, FTakeHighResScreenShotsEvent );` — Called when a high res screenshot is requested.
- L340 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(UAnimSequence*, FCaptureSingleFrameAnimSequence, USkeletalMeshComponent* );` — Delegate used to capture skeletal meshes to single-frame animations when 'keeping simulation changes'
- L344 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FGetVisualizeCheckerboardEnabled);` — Delegate used to determine if users should be able to enable the alpha-blended checkerboard for the level viewport
- L386 _function_ `AreObjectsEditableDelegates.RemoveAll([=](const FAreObjectsEditable& P){ return P.GetHandle() == InPredicateHandle; });` (scope `FLevelEditorModule::RemoveEditableObjectPredicate`)

### `Source/Editor/LevelEditor/Public/LevelEditorActions.h` (Public)


#### class `FLevelEditorCommands`  
`class FLevelEditorCommands : public TCommands<FLevelEditorCommands>`  
_L31-703_
- inherits: `TCommands<FLevelEditorCommands>`
- desc: Unreal level editor actions
- L35 _public prototype_ `FLevelEditorCommands();`
- L40 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L42 _public prototype_ `FORCENOINLINE static const FLevelEditorCommands& Get();`
- L46 _public member_ `TSharedPtr< FUICommandInfo > BrowseDocumentation;`
- L47 _public member_ `TSharedPtr< FUICommandInfo > BrowseViewportControls;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> NewLevel;` — Level file commands
- L52 _public member_ `TSharedPtr<FUICommandInfo> OpenLevel;` — `UE_DEPRECATED(5.5, "This command has been moved to FGlobalEditorCommonCommands and is no longer registered.")`
- L53 _public member_ `TSharedPtr<FUICommandInfo> Save;`
- L54 _public member_ `TSharedPtr<FUICommandInfo> SaveAs;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> SaveAllLevels;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> BrowseLevel;`
- L58 _public member_ `static const int32 MaxRecentFiles = 10;`
- L59 _public member_ `TArray< TSharedPtr< FUICommandInfo > > OpenRecentFileCommands;`
- L60 _public member_ `static const int32 MaxFavoriteFiles = 20;`
- L61 _public member_ `TArray< TSharedPtr< FUICommandInfo > > OpenFavoriteFileCommands;`
- L63 _public member_ `TSharedPtr< FUICommandInfo > ClearRecentFiles;`
- L65 _public member_ `TSharedPtr< FUICommandInfo > ToggleFavorite;`
- L68 _public member_ `TSharedPtr< FUICommandInfo > ImportScene;` — Import Scene
- L71 _public member_ `TSharedPtr< FUICommandInfo > ExportAll;` — Export All
- L74 _public member_ `TSharedPtr< FUICommandInfo > ExportSelected;` — Export Selected
- L78 _public member_ `static constexpr int32 MaxExternalBuildTypes = 10;` — Build commands
- L79 _public member_ `TArray<TSharedPtr< FUICommandInfo >> ExternalBuildTypeCommands;`
- L81 _public member_ `TSharedPtr< FUICommandInfo > Build;`
- L82 _public member_ `TSharedPtr< FUICommandInfo > BuildAndSubmitToSourceControl;`
- L83 _public member_ `TSharedPtr< FUICommandInfo > BuildLightingOnly;`
- L84 _public member_ `TSharedPtr< FUICommandInfo > BuildReflectionCapturesOnly;`
- L85 _public member_ `TSharedPtr< FUICommandInfo > BuildLightingOnly_VisibilityOnly;`
- L86 _public member_ `TSharedPtr< FUICommandInfo > LightingBuildOptions_UseErrorColoring;`
- L87 _public member_ `TSharedPtr< FUICommandInfo > LightingBuildOptions_ShowLightingStats;`
- L88 _public member_ `TSharedPtr< FUICommandInfo > BuildGeometryOnly;`
- L89 _public member_ `TSharedPtr< FUICommandInfo > BuildGeometryOnly_OnlyCurrentLevel;`
- L90 _public member_ `TSharedPtr< FUICommandInfo > BuildPathsOnly;`
- L91 _public member_ `TSharedPtr< FUICommandInfo > BuildHLODs;`
- L92 _public member_ `TSharedPtr< FUICommandInfo > BuildHLODs_SelectedActors;`
- L93 _public member_ `TSharedPtr< FUICommandInfo > BuildMinimap;`
- L94 _public member_ `TSharedPtr< FUICommandInfo > BuildLandscapeSplineMeshes;`
- L95 _public member_ `TSharedPtr< FUICommandInfo > BuildTextureStreamingOnly;`
- L96 _public member_ `TSharedPtr< FUICommandInfo > BuildVirtualTextureOnly;`
- L97 _public member_ `TSharedPtr< FUICommandInfo > BuildAllLandscape;`
- L98 _public member_ `TSharedPtr< FUICommandInfo > LightingQuality_Production;`
- L99 _public member_ `TSharedPtr< FUICommandInfo > LightingQuality_High;`
- L100 _public member_ `TSharedPtr< FUICommandInfo > LightingQuality_Medium;`
- L101 _public member_ `TSharedPtr< FUICommandInfo > LightingQuality_Preview;`
- L102 _public member_ `TSharedPtr< FUICommandInfo > LightingDensity_RenderGrayscale;`
- L103 _public member_ `TSharedPtr< FUICommandInfo > LightingResolution_CurrentLevel;`
- L104 _public member_ `TSharedPtr< FUICommandInfo > LightingResolution_SelectedLevels;`
- L105 _public member_ `TSharedPtr< FUICommandInfo > LightingResolution_AllLoadedLevels;`
- L106 _public member_ `TSharedPtr< FUICommandInfo > LightingResolution_SelectedObjectsOnly;`
- L107 _public member_ `TSharedPtr< FUICommandInfo > LightingStaticMeshInfo;`
- L108 _public member_ `TSharedPtr< FUICommandInfo > SceneStats;`
- L109 _public member_ `TSharedPtr< FUICommandInfo > TextureStats;`
- L110 _public member_ `TSharedPtr< FUICommandInfo > MapCheck;`
- L113 _public member_ `TSharedPtr< FUICommandInfo > RecompileLevelEditor;` — Recompile
- L114 _public member_ `TSharedPtr< FUICommandInfo > ReloadLevelEditor;`
- L115 _public member_ `TSharedPtr< FUICommandInfo > RecompileGameCode;`
- L118 _public member_ `TSharedPtr< FUICommandInfo > LiveCoding_Enable;`
- L119 _public member_ `TSharedPtr< FUICommandInfo > LiveCoding_StartSession;`
- L120 _public member_ `TSharedPtr< FUICommandInfo > LiveCoding_ShowConsole;`
- L121 _public member_ `TSharedPtr< FUICommandInfo > LiveCoding_Settings;`
- L131 _public member_ `TSharedPtr< FUICommandInfo > EditAsset;` — Edits associated asset(s), prompting for confirmation if there is more than one selected
- L134 _public member_ `TSharedPtr< FUICommandInfo > EditAssetNoConfirmMultiple;` — Edits associated asset(s)
- L137 _public member_ `TSharedPtr< FUICommandInfo > OpenSelectionInPropertyMatrix;` — Opens the associated asset(s) in the property matrix
- L140 _public member_ `TSharedPtr< FUICommandInfo > GoHere;` — Moves the camera to the current mouse position
- L143 _public member_ `TSharedPtr< FUICommandInfo > PlayFromHere;` — Plays from the current position (selected actor or clicked)
- L146 _public member_ `TSharedPtr< FUICommandInfo > SnapCameraToObject;` — Snaps the camera to the selected object.
- L149 _public member_ `TSharedPtr< FUICommandInfo > SnapObjectToCamera;` — Snaps the selected actor to the camera.
- L152 _public member_ `TSharedPtr< FUICommandInfo > CopyActorFilePathtoClipboard;` — Copy the file path where the actor is saved.
- L155 _public member_ `TSharedPtr< FUICommandInfo > OpenActorInReferenceViewer;` — Opens the reference viewer for the selected actor.
- L158 _public member_ `TSharedPtr< FUICommandInfo > SaveActor;` — Save the selected actor.
- L161 _public member_ `TSharedPtr< FUICommandInfo > OpenSourceControl;` — Opens the source control panel.
- L164 _public member_ `TSharedPtr< FUICommandInfo > ShowActorHistory;` — Shows the history of the file containing the actor.
- L167 _public member_ `TSharedPtr< FUICommandInfo > GoToCodeForActor;` — Goes to the source code for the selected actor's class.
- L170 _public member_ `TSharedPtr< FUICommandInfo > GoToDocsForActor;` — Goes to the documentation for the selected actor's class.
- L173 _public member_ `TSharedPtr< FUICommandInfo > AddScriptBehavior;` — Customize the script behavior of an instance.
- L176 _public member_ `TSharedPtr< FUICommandInfo > PasteHere;` — Paste actor at click location
- L183 _public member_ `TSharedPtr< FUICommandInfo > SnapOriginToGrid;` — Snaps the actor to the grid at its pivot
- L186 _public member_ `TSharedPtr< FUICommandInfo > SnapOriginToGridPerActor;` — Snaps each selected actor separately to the grid at its pivot
- L189 _public member_ `TSharedPtr< FUICommandInfo > AlignOriginToGrid;` — Aligns the actor to the grid at its pivot
- L192 _public member_ `TSharedPtr< FUICommandInfo > SnapTo2DLayer;` — Snaps the actor to the 2D layer
- L195 _public member_ `TSharedPtr< FUICommandInfo > MoveSelectionUpIn2DLayers;` — Moves the selected actors up one 2D layer (changing the active layer at the same time)
- L198 _public member_ `TSharedPtr< FUICommandInfo > MoveSelectionDownIn2DLayers;` — Moves the selected actors down one 2D layer (changing the active layer at the same time)
- L201 _public member_ `TSharedPtr< FUICommandInfo > MoveSelectionToTop2DLayer;` — Moves the selected actors to the top 2D layer (changing the active layer at the same time)
- L204 _public member_ `TSharedPtr< FUICommandInfo > MoveSelectionToBottom2DLayer;` — Moves the selected actors to the bottom 2D layer (changing the active layer at the same time)
- L207 _public member_ `TSharedPtr< FUICommandInfo > Select2DLayerAbove;` — Changes the active 2D layer to one above the current one
- L210 _public member_ `TSharedPtr< FUICommandInfo > Select2DLayerBelow;` — Changes the active 2D layer to one below the current one
- L213 _public member_ `TSharedPtr< FUICommandInfo > SnapToFloor;` — Snaps the actor to the floor
- L216 _public member_ `TSharedPtr< FUICommandInfo > AlignToFloor;` — Aligns the actor with the floor
- L219 _public member_ `TSharedPtr< FUICommandInfo > SnapPivotToFloor;` — Snaps the actor to the floor at its pivot
- L222 _public member_ `TSharedPtr< FUICommandInfo > AlignPivotToFloor;` — Aligns the actor to the floor at its pivot
- L225 _public member_ `TSharedPtr< FUICommandInfo > SnapBottomCenterBoundsToFloor;` — Snaps the actor to the floor at its bottom center bounds position
- L228 _public member_ `TSharedPtr< FUICommandInfo > AlignBottomCenterBoundsToFloor;` — Aligns the actor to the floor at its bottom center bounds position
- L231 _public member_ `TSharedPtr< FUICommandInfo > SnapOriginToActor;` — Snaps the actor to another actor at its pivot
- L234 _public member_ `TSharedPtr< FUICommandInfo > AlignOriginToActor;` — Aligns the actor to another actor at its pivot
- L237 _public member_ `TSharedPtr< FUICommandInfo > SnapToActor;` — Snaps the actor to another actor
- L240 _public member_ `TSharedPtr< FUICommandInfo > AlignToActor;` — Aligns the actor with another actor
- L243 _public member_ `TSharedPtr< FUICommandInfo > SnapPivotToActor;` — Snaps the actor to another actor at its pivot
- L246 _public member_ `TSharedPtr< FUICommandInfo > AlignPivotToActor;` — Aligns the actor to another actor at its pivot
- L249 _public member_ `TSharedPtr< FUICommandInfo > SnapBottomCenterBoundsToActor;` — Snaps the actor to the Actor at its bottom center bounds position
- L252 _public member_ `TSharedPtr< FUICommandInfo > AlignBottomCenterBoundsToActor;` — Aligns the actor to the Actor at its bottom center bounds position
- L255 _public member_ `TSharedPtr< FUICommandInfo > DeltaTransformToActors;` — Apply delta transform to selected actors
- L258 _public member_ `TSharedPtr< FUICommandInfo > MirrorActorX;` — Mirros the actor along the x axis
- L261 _public member_ `TSharedPtr< FUICommandInfo > MirrorActorY;` — Mirros the actor along the y axis
- L264 _public member_ `TSharedPtr< FUICommandInfo > MirrorActorZ;` — Mirros the actor along the z axis
- L267 _public member_ `TSharedPtr< FUICommandInfo > LockActorMovement;` — Locks the actor so it cannot be moved
- L270 _public member_ `TSharedPtr< FUICommandInfo > SavePivotToPrePivot;` — Saves the pivot to the pre-pivot
- L273 _public member_ `TSharedPtr< FUICommandInfo > ResetPrePivot;` — Resets the pre-pivot
- L276 _public member_ `TSharedPtr< FUICommandInfo > ResetPivot;` — Resets the pivot
- L279 _public member_ `TSharedPtr< FUICommandInfo > MovePivotHere;` — Moves the pivot to the click location
- L282 _public member_ `TSharedPtr< FUICommandInfo > MovePivotHereSnapped;` — Moves the pivot to the click location and snap it to the grid
- L285 _public member_ `TSharedPtr< FUICommandInfo > MovePivotToCenter;` — Moves the pivot to the center of the selection
- L288 _public member_ `TSharedPtr< FUICommandInfo > DetachFromParent;` — Detach selected actor(s) from any parent
- L290 _public member_ `TSharedPtr< FUICommandInfo > AttachSelectedActors;`
- L292 _public member_ `TSharedPtr< FUICommandInfo > AttachActorIteractive;`
- L294 _public member_ `TSharedPtr< FUICommandInfo > CreateNewOutlinerFolder;`
- L296 _public member_ `TSharedPtr< FUICommandInfo > HoldToEnableVertexSnapping;`
- L297 _public member_ `TSharedPtr< FUICommandInfo > HoldToEnablePivotVertexSnapping;`
- L304 _public member_ `TSharedPtr< FUICommandInfo > OrderFirst;` — Put the selected brushes first in the draw order
- L307 _public member_ `TSharedPtr< FUICommandInfo > OrderLast;` — Put the selected brushes last in the draw order
- L310 _public member_ `TSharedPtr< FUICommandInfo > ConvertToAdditive;` — Converts the brush to an additive brush
- L313 _public member_ `TSharedPtr< FUICommandInfo > ConvertToSubtractive;` — Converts the brush to a subtractive brush
- L316 _public member_ `TSharedPtr< FUICommandInfo > MakeSolid;` — Make the brush solid
- L319 _public member_ `TSharedPtr< FUICommandInfo > MakeSemiSolid;` — Make the brush semi-solid
- L322 _public member_ `TSharedPtr< FUICommandInfo > MakeNonSolid;` — Make the brush non-solid
- L325 _public member_ `TSharedPtr< FUICommandInfo > MergePolys;` — Merge bsp polys into as few faces as possible
- L328 _public member_ `TSharedPtr< FUICommandInfo > SeparatePolys;` — Reverse a merge
- L331 _public member_ `TSharedPtr<FUICommandInfo> AlignBrushVerticesToGrid;` — Align brush vertices to the grid
- L338 _public member_ `TSharedPtr< FUICommandInfo > RegroupActors;` — Group or regroup the selected actors depending on context
- L340 _public member_ `TSharedPtr< FUICommandInfo > GroupActors;` — Groups selected actors
- L342 _public member_ `TSharedPtr< FUICommandInfo > UngroupActors;` — Ungroups selected actors
- L344 _public member_ `TSharedPtr< FUICommandInfo > AddActorsToGroup;` — Adds the selected actors to the selected group
- L346 _public member_ `TSharedPtr< FUICommandInfo > RemoveActorsFromGroup;` — Removes selected actors from the group
- L348 _public member_ `TSharedPtr< FUICommandInfo > LockGroup;` — Locks the selected group
- L350 _public member_ `TSharedPtr< FUICommandInfo > UnlockGroup;` — Unlocks the selected group
- L356 _public member_ `TSharedPtr< FUICommandInfo > ShowAll;` — Shows all actors
- L359 _public member_ `TSharedPtr< FUICommandInfo > ShowSelectedOnly;` — Shows only selected actors
- L362 _public member_ `TSharedPtr< FUICommandInfo > ShowSelected;` — Unhides selected actors
- L365 _public member_ `TSharedPtr< FUICommandInfo > HideSelected;` — Hides selected actors
- L368 _public member_ `TSharedPtr< FUICommandInfo > ToggleSelectedVisibility;` — Hides or shows selected actors
- L371 _public member_ `TSharedPtr< FUICommandInfo > ShowSelectedHierarchy;` — Unhides selected actors and their children
- L374 _public member_ `TSharedPtr< FUICommandInfo > HideSelectedHierarchy;` — Hides selected actors and their children
- L377 _public member_ `TSharedPtr< FUICommandInfo > ToggleSelectedHierarchyVisibility;` — Hides or shows selected actors and their children
- L380 _public member_ `TSharedPtr< FUICommandInfo > ShowAllStartup;` — Shows all actors at startup
- L383 _public member_ `TSharedPtr< FUICommandInfo > ShowSelectedStartup;` — Shows selected actors at startup
- L386 _public member_ `TSharedPtr< FUICommandInfo > HideSelectedStartup;` — Hides selected actors at startup
- L389 _public member_ `TSharedPtr< FUICommandInfo > ShowSelectedHierarchyStartup;` — Shows selected actors and their current children at startup
- L392 _public member_ `TSharedPtr< FUICommandInfo > HideSelectedHierarchyStartup;` — Hides selected actors and their current children at startup
- L395 _public member_ `TSharedPtr< FUICommandInfo > CycleNavigationDataDrawn;` — Cycles through all navigation data to show one at a time
- L402 _public member_ `TSharedPtr< FUICommandInfo > SelectNone;` — Select nothing
- L405 _public member_ `TSharedPtr< FUICommandInfo > InvertSelection;` — Invert the current selection
- L408 _public member_ `TSharedPtr< FUICommandInfo > SelectImmediateChildren;` — Selects all direct children of the current selection
- L411 _public member_ `TSharedPtr< FUICommandInfo > SelectAllDescendants;` — Selects all descendants of the current selection
- L414 _public member_ `TSharedPtr< FUICommandInfo > SelectAllActorsOfSameClass;` — Selects all actors of the same class as the current selection
- L417 _public member_ `TSharedPtr< FUICommandInfo > SelectAllActorsOfSameClassWithArchetype;` — Selects all actors of the same class and archetype as the current selection
- L420 _public member_ `TSharedPtr< FUICommandInfo > SelectComponentOwnerActor;` — Selects the actor that owns the currently selected component(s)
- L423 _public member_ `TSharedPtr< FUICommandInfo > SelectRelevantLights;` — Selects all lights relevant to the current selection
- L426 _public member_ `TSharedPtr< FUICommandInfo > SelectStaticMeshesOfSameClass;` — Selects all actors using the same static mesh(es) as the current selection
- L429 _public member_ `TSharedPtr< FUICommandInfo > SelectStaticMeshesAllClasses;` — Selects all actors using the same static mesh(es) and same actor class as the current selection
- L432 _public member_ `TSharedPtr< FUICommandInfo > SelectOwningHierarchicalLODCluster;` — Selects the HLOD cluster (ALODActor), if available, that has this actor as one of its SubActors
- L435 _public member_ `TSharedPtr< FUICommandInfo > SelectSkeletalMeshesOfSameClass;` — Selects all actors using the same skeletal mesh(es) as the current selection
- L438 _public member_ `TSharedPtr< FUICommandInfo > SelectSkeletalMeshesAllClasses;` — Selects all actors using the same skeletal mesh(es) and same actor class as the current selection
- L441 _public member_ `TSharedPtr< FUICommandInfo > SelectAllWithSameMaterial;` — Selects all actors using the same material(s) as the current selection
- L444 _public member_ `TSharedPtr< FUICommandInfo > SelectMatchingEmitter;` — Selects all emitters using the same particle system as the current selection
- L447 _public member_ `TSharedPtr< FUICommandInfo > SelectAllLights;` — Selects all lights
- L450 _public member_ `TSharedPtr< FUICommandInfo > SelectStationaryLightsExceedingOverlap;` — Selects all lights exceeding the overlap limit
- L453 _public member_ `TSharedPtr< FUICommandInfo > SelectAllAddditiveBrushes;` — Selects all additive brushes
- L456 _public member_ `TSharedPtr< FUICommandInfo > SelectAllSubtractiveBrushes;` — Selects all subtractive brushes
- L461 _public member_ `TSharedPtr< FUICommandInfo > SelectAllSurfaces;` — Surface commands
- L464 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAllMatchingBrush;` — Select all surfaces in the same brush as the current surface selection
- L467 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAllMatchingTexture;` — Select all surfaces using the same material as current surface selection
- L470 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAllAdjacents;` — Select all surfaces adjacent to current surface selection
- L473 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAllAdjacentCoplanars;` — Select all surfaces adjacent and coplanar to current surface selection
- L476 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAllAdjacentWalls;` — Select all surfaces adjacent to to current surface selection that are walls
- L479 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAllAdjacentFloors;` — Select all surfaces adjacent to to current surface selection that are floors(normals pointing up)
- L482 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAllAdjacentSlants;` — Select all surfaces adjacent to to current surface selection that are slants
- L485 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectReverse;` — Invert current surface selection
- L488 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectMemorize;` — Memorize current surface selection
- L491 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectRecall;` — Recall previously memorized selection
- L494 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectOr;` — Replace the current selection with only the surfaces which are both currently selected and contained within the saved selection in memory
- L497 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectAnd;` — Add the selection of surfaces saved in memory to the current selection
- L500 _public member_ `TSharedPtr< FUICommandInfo > SurfSelectXor;` — Replace the current selection with only the surfaces that are not in both the current selection and the selection saved in memory
- L503 _public member_ `TSharedPtr< FUICommandInfo > SurfUnalign;` — Unalign surface texture
- L506 _public member_ `TSharedPtr< FUICommandInfo > SurfAlignPlanarAuto;` — Auto align surface texture
- L509 _public member_ `TSharedPtr< FUICommandInfo > SurfAlignPlanarWall;` — Align surface texture like its a wall
- L512 _public member_ `TSharedPtr< FUICommandInfo > SurfAlignPlanarFloor;` — Align surface texture like its a floor
- L515 _public member_ `TSharedPtr< FUICommandInfo > SurfAlignBox;` — Align surface texture using box
- L518 _public member_ `TSharedPtr< FUICommandInfo > SurfAlignFit;` — Best fit surface texture alignment
- L521 _public member_ `TSharedPtr< FUICommandInfo > ApplyMaterialToSurface;` — Apply the currently selected material to the currently selected surfaces
- L528 _public member_ `TSharedPtr< FUICommandInfo > CreateBoundingBoxVolume;` — Create a blocking volume from the meshes bounding box
- L531 _public member_ `TSharedPtr< FUICommandInfo > CreateHeavyConvexVolume;` — Create a blocking volume from the meshes using a heavy convex shape
- L534 _public member_ `TSharedPtr< FUICommandInfo > CreateNormalConvexVolume;` — Create a blocking volume from the meshes using a normal convex shape
- L537 _public member_ `TSharedPtr< FUICommandInfo > CreateLightConvexVolume;` — Create a blocking volume from the meshes using a light convex shape
- L540 _public member_ `TSharedPtr< FUICommandInfo > CreateRoughConvexVolume;` — Create a blocking volume from the meshes using a rough convex shape
- L543 _public member_ `TSharedPtr< FUICommandInfo > SetCollisionBlockAll;` — Set the actors collision to block all
- L546 _public member_ `TSharedPtr< FUICommandInfo > SetCollisionBlockWeapons;` — Set the actors collision to block only weapons
- L549 _public member_ `TSharedPtr< FUICommandInfo > SetCollisionBlockNone;` — Set the actors collision to block nothing
- L556 _public member_ `TSharedPtr< FUICommandInfo > KeepSimulationChanges;` — Pushes properties of the selected actor back to its EditorWorld counterpart
- L564 _public member_ `TSharedPtr< FUICommandInfo > MakeActorLevelCurrent;` — Makes the actor level the current level
- L567 _public member_ `TSharedPtr< FUICommandInfo > MoveSelectedToCurrentLevel;` — Move all the selected actors to the current level
- L570 _public member_ `TSharedPtr< FUICommandInfo > FindActorLevelInContentBrowser;` — Finds the level of the selected actors in the content browser
- L573 _public member_ `TSharedPtr< FUICommandInfo > FindLevelsInLevelBrowser;` — Finds the levels of the selected actors in the level browser
- L576 _public member_ `TSharedPtr< FUICommandInfo > AddLevelsToSelection;` — Add levels of the selected actors to the level browser selection
- L579 _public member_ `TSharedPtr< FUICommandInfo > RemoveLevelsFromSelection;` — Remove levels of the selected actors from the level browser selection
- L584 _public member_ `TSharedPtr< FUICommandInfo > FindActorInLevelScript;` — Level Script Commands
- L590 _public member_ `TSharedPtr< FUICommandInfo > WorldProperties;`
- L591 _public member_ `TSharedPtr< FUICommandInfo > OpenPlaceActors;`
- L592 _public member_ `TSharedPtr< FUICommandInfo > OpenContentBrowser;`
- L593 _public member_ `TSharedPtr< FUICommandInfo > ToggleVR;`
- L594 _public member_ `TSharedPtr< FUICommandInfo > ImportContent;`
- L599 _public member_ `TSharedPtr< FUICommandInfo > OpenLevelBlueprint;` — Blueprints commands
- L600 _public member_ `TSharedPtr< FUICommandInfo > CheckOutProjectSettingsConfig;`
- L601 _public member_ `TSharedPtr< FUICommandInfo > CreateBlankBlueprintClass;`
- L602 _public member_ `TSharedPtr< FUICommandInfo > ConvertSelectionToBlueprint;`
- L605 _public member_ `TArray< TSharedPtr< FUICommandInfo > > EditorModeCommands;` — Editor mode commands
- L610 _public member_ `TSharedPtr< FUICommandInfo > ShowTransformWidget;` — View commands
- L611 _public member_ `TSharedPtr< FUICommandInfo > AllowTranslucentSelection;`
- L612 _public member_ `TSharedPtr< FUICommandInfo > AllowGroupSelection;`
- L613 _public member_ `TSharedPtr< FUICommandInfo > ShowSelectionSubcomponents;`
- L615 _public member_ `TSharedPtr< FUICommandInfo > StrictBoxSelect;`
- L616 _public member_ `TSharedPtr< FUICommandInfo > TransparentBoxSelect;`
- L617 _public member_ `TSharedPtr< FUICommandInfo > DrawBrushMarkerPolys;`
- L618 _public member_ `TSharedPtr< FUICommandInfo > OnlyLoadVisibleInPIE;`
- L620 _public member_ `TSharedPtr< FUICommandInfo > ToggleSocketSnapping;`
- L621 _public member_ `TSharedPtr< FUICommandInfo > ToggleParticleSystemLOD;`
- L622 _public member_ `TSharedPtr< FUICommandInfo > ToggleParticleSystemHelpers;`
- L623 _public member_ `TSharedPtr< FUICommandInfo > ToggleFreezeParticleSimulation;`
- L624 _public member_ `TSharedPtr< FUICommandInfo > ToggleLODViewLocking;`
- L625 _public member_ `TSharedPtr< FUICommandInfo > LevelStreamingVolumePrevis;`
- L627 _public member_ `TSharedPtr< FUICommandInfo > EnableActorSnap;`
- L628 _public member_ `TSharedPtr< FUICommandInfo > EnableVertexSnap;`
- L630 _public member_ `TSharedPtr< FUICommandInfo > ToggleHideViewportUI;`
- L632 _public member_ `TSharedPtr< FUICommandInfo > MaterialQualityLevel_Low;`
- L633 _public member_ `TSharedPtr< FUICommandInfo > MaterialQualityLevel_Medium;`
- L634 _public member_ `TSharedPtr< FUICommandInfo > MaterialQualityLevel_High;`
- L635 _public member_ `TSharedPtr< FUICommandInfo > MaterialQualityLevel_Epic;`
- L637 _public member_ `TSharedPtr< FUICommandInfo > TogglePreviewPlatform;`
- L639 _public member_ `TArray<TSharedPtr<FUICommandInfo>> PreviewPlatformOverrides;`
- L656 _public member_ `TSharedPtr< FUICommandInfo > DisablePlatformPreview;`
- L657 _public member_ `TMap<FName, TArray<PreviewPlatformCommand>> PlatformToPreviewPlatformOverrides;`
- L658 _public member_ `TMap<FName, TArray<PreviewPlatformCommand>> PlatformToPreviewJsonPlatformOverrides;`
- L663 _public member_ `TSharedPtr<FUICommandInfo> OrbitCameraAroundSelection;` — Camera Preferences
- L664 _public member_ `TSharedPtr<FUICommandInfo> LinkOrthographicViewports;`
- L665 _public member_ `TSharedPtr<FUICommandInfo> OrthoZoomToCursor;`
- L678 _public member_ `TSharedPtr< FUICommandInfo > ShowSelectedDetails;` — Misc Commands
- L679 _public member_ `TSharedPtr< FUICommandInfo > RecompileShaders;`
- L680 _public member_ `TSharedPtr< FUICommandInfo > ProfileGPU;`
- L681 _public member_ `TSharedPtr< FUICommandInfo > DumpGPU;`
- L683 _public member_ `TSharedPtr< FUICommandInfo > ResetAllParticleSystems;`
- L684 _public member_ `TSharedPtr< FUICommandInfo > ResetSelectedParticleSystem;`
- L685 _public member_ `TSharedPtr< FUICommandInfo > SelectActorsInLayers;`
- L688 _public member_ `TSharedPtr< FUICommandInfo > OpenMergeActor;` — Open merge actor command
- L690 _public member_ `TSharedPtr< FUICommandInfo > FixupGroupActor;`
- L692 _public member_ `TSharedPtr<FUICommandInfo> AllowArcballRotation;`
- L693 _public member_ `TSharedPtr<FUICommandInfo> AllowScreenspaceRotation;`
- L694 _public member_ `TSharedPtr<FUICommandInfo> EnableViewportHoverFeedback;`
- L700 _public member_ `TSharedPtr<FUICommandInfo> InvertMiddleMousePan;` — Mouse Controls
- L701 _public member_ `TSharedPtr<FUICommandInfo> InvertOrbitYAxis;`
- L702 _public member_ `TSharedPtr<FUICommandInfo> InvertRightMouseDollyYAxis;`

#### struct `FLevelEditorCommands::PreviewPlatformCommand`  
`struct PreviewPlatformCommand`  
_L641-654_
- L643 _public function_ `PreviewPlatformCommand() : bIsGeneratingJsonCommand(false) , SectionName(NAME_None)`
- L649 _public member_ `bool bIsGeneratingJsonCommand;`
- L650 _public member_ `FName SectionName;`
- L651 _public member_ `TSharedPtr<FUICommandInfo> CommandInfo;`
- L652 _public member_ `FString FilePath;`
- L653 _public member_ `TSet<FName> PreviewShaderPlatformNames;`

#### class `FLevelEditorActionCallbacks`  
`class FLevelEditorActionCallbacks`  
_L708-1622_
- desc: Implementation of various level editor action callback functions
- L716 _public prototype_ `static bool DefaultCanExecuteAction();` — The default can execute action for all commands unless they override it By default commands cannot be executed if the application is in K2 debug mode.
- L719 _public prototype_ `static void BrowseDocumentation();` — Opens the global documentation homepage
- L722 _public prototype_ `static void BrowseViewportControls();` — Opens the viewport controls page
- L725 _public prototype_ `static void NewLevel();` — Creates a new level
- L726 _public prototype_ `static void NewLevel(bool& bOutLevelCreated);`
- L727 _public prototype_ `DECLARE_DELEGATE_OneParam(FNewLevelOverride, bool& );`
- L728 _public member_ `static FNewLevelOverride NewLevelOverride;`
- L729 _public prototype_ `static bool NewLevel_CanExecute();`
- L732 _public prototype_ `static void OpenLevel();` — Opens an existing level
- L733 _public prototype_ `static bool OpenLevel_CanExecute();`
- L736 _public prototype_ `static void ToggleVR();` — Toggles VR mode
- L737 _public prototype_ `static bool ToggleVR_CanExecute();`
- L738 _public prototype_ `static bool ToggleVR_IsButtonActive();`
- L739 _public prototype_ `static bool ToggleVR_IsChecked();`
- L742 _public prototype_ `static void DeltaTransform();` — Opens delta transform
- L749 _public prototype_ `static void OpenRecentFile( int32 RecentFileIndex );` — Opens a recent file @param	RecentFileIndex		Index into our MRU list of recent files that can be opened
- L752 _public prototype_ `static void ClearRecentFiles();` — Clear the list of recent files.
- L759 _public prototype_ `static void OpenFavoriteFile( int32 FavoriteFileIndex );` — Opens a favorite file @param	FavoriteFileIndex		Index into our list of favorite files that can be opened
- L761 _public prototype_ `static void ToggleFavorite();`
- L768 _public prototype_ `static void RemoveFavorite( int32 FavoriteFileIndex );` — Remove a favorite file from the favorites list @param	FavoriteFileIndex		Index into our list of favorite files to be removed
- L770 _public prototype_ `static bool ToggleFavorite_CanExecute();`
- L771 _public prototype_ `static bool ToggleFavorite_IsChecked();`
- L774 _public prototype_ `static bool CanSaveWorld();` — Determine whether the level can be saved at this moment
- L775 _public prototype_ `static bool CanSaveUnpartitionedWorld();`
- L778 _public prototype_ `static bool CanSaveCurrentAs();` — Save the current level as...
- L779 _public prototype_ `static void SaveCurrentAs();`
- L782 _public prototype_ `static void Save();` — Saves the current map
- L785 _public prototype_ `static void SaveAllLevels();` — Saves all unsaved maps (but not packages)
- L788 _public prototype_ `static void Browse();` — Browses to the current map
- L789 _public prototype_ `static bool CanBrowse();`
- L795 _public prototype_ `static void ImportScene_Clicked();` — Called when import scene is selected
- L800 _public prototype_ `static void PreviewJson_Clicked(FName PlatformName, FString JsonFile);` — Called When Preview Json is selected in the Platforms Preview Sub Menu
- L805 _public prototype_ `static bool IsPreviewJsonVisible(FName PlatformName);` — Is Preview Json visible in the Platforms Preview Sub Menu
- L810 _public prototype_ `static void GeneratePreviewJson_Clicked(FString PlatformName);` — Called When Generate Preview Json is selected in the Platforms Preview Sub Menu
- L815 _public prototype_ `static bool IsGeneratePreviewJsonVisible(FName PlatformName);` — Is Generate Preview Json visible in the Platforms Preview Sub Menu
- L820 _public prototype_ `static void ExportAll_Clicked();` — Called when export all is selected
- L826 _public prototype_ `static void ExportSelected_Clicked();` — Called when export selected is clicked
- L832 _public prototype_ `static bool ExportSelected_CanExecute();` — @return	True if the export selected option is available to execute
- L835 _public prototype_ `static void ConfigureLightingBuildOptions( const FLightingBuildOptions& Options );`
- L837 _public prototype_ `static bool CanBuildLighting();`
- L838 _public prototype_ `static bool CanBuildReflectionCaptures();`
- L843 _public prototype_ `static void Build_Execute();` — Build callbacks
- L844 _public prototype_ `static bool Build_CanExecute();`
- L845 _public prototype_ `static void BuildAndSubmitToSourceControl_Execute();`
- L846 _public prototype_ `static void BuildLightingOnly_Execute();`
- L847 _public prototype_ `static bool BuildLighting_CanExecute();`
- L848 _public prototype_ `static void BuildReflectionCapturesOnly_Execute();`
- L849 _public prototype_ `static bool BuildReflectionCapturesOnly_CanExecute();`
- L850 _public prototype_ `static void BuildLightingOnly_VisibilityOnly_Execute();`
- L851 _public prototype_ `static bool LightingBuildOptions_UseErrorColoring_IsChecked();`
- L852 _public prototype_ `static void LightingBuildOptions_UseErrorColoring_Toggled();`
- L853 _public prototype_ `static bool LightingBuildOptions_ShowLightingStats_IsChecked();`
- L854 _public prototype_ `static void LightingBuildOptions_ShowLightingStats_Toggled();`
- L855 _public prototype_ `static void BuildGeometryOnly_Execute();`
- L856 _public prototype_ `static void BuildGeometryOnly_OnlyCurrentLevel_Execute();`
- L857 _public prototype_ `static void BuildPathsOnly_Execute();`
- L858 _public prototype_ `static bool IsWorldPartitionEnabled();`
- L859 _public prototype_ `static bool IsWorldPartitionStreamingEnabled();`
- L860 _public prototype_ `static void BuildHLODs_Execute();`
- L861 _public prototype_ `static void BuildHLODs_SelectedActors_Execute();`
- L862 _public prototype_ `static void BuildMinimap_Execute();`
- L863 _public prototype_ `static void BuildLandscapeSplineMeshes_Execute();`
- L864 _public prototype_ `static void BuildTextureStreamingOnly_Execute();`
- L865 _public prototype_ `static void BuildVirtualTextureOnly_Execute();`
- L866 _public prototype_ `static void BuildAllLandscape_Execute();`
- L867 _public prototype_ `static bool BuildExternalType_CanExecute( int32 Index );`
- L868 _public prototype_ `static void BuildExternalType_Execute( int32 Index );`
- L869 _public prototype_ `static void SetLightingQuality( ELightingBuildQuality NewQuality );`
- L870 _public prototype_ `static bool IsLightingQualityChecked( ELightingBuildQuality TestQuality );`
- L871 _public prototype_ `static float GetLightingDensityIdeal();`
- L872 _public prototype_ `static void SetLightingDensityIdeal( float Value );`
- L873 _public prototype_ `static float GetLightingDensityMaximum();`
- L874 _public prototype_ `static void SetLightingDensityMaximum( float Value );`
- L875 _public prototype_ `static float GetLightingDensityColorScale();`
- L876 _public prototype_ `static void SetLightingDensityColorScale( float Value );`
- L877 _public prototype_ `static float GetLightingDensityGrayscaleScale();`
- L878 _public prototype_ `static void SetLightingDensityGrayscaleScale( float Value );`
- L879 _public prototype_ `static void SetLightingDensityRenderGrayscale();`
- L880 _public prototype_ `static bool IsLightingDensityRenderGrayscaleChecked();`
- L881 _public prototype_ `static void SetLightingResolutionStaticMeshes( ECheckBoxState NewCheckedState );`
- L882 _public prototype_ `static ECheckBoxState IsLightingResolutionStaticMeshesChecked();`
- L883 _public prototype_ `static void SetLightingResolutionBSPSurfaces( ECheckBoxState NewCheckedState );`
- L884 _public prototype_ `static ECheckBoxState IsLightingResolutionBSPSurfacesChecked();`
- L885 _public prototype_ `static void SetLightingResolutionLevel( FLightmapResRatioAdjustSettings::AdjustLevels NewLevel );`
- L886 _public prototype_ `static bool IsLightingResolutionLevelChecked( FLightmapResRatioAdjustSettings::AdjustLevels TestLevel );`
- L887 _public prototype_ `static void SetLightingResolutionSelectedObjectsOnly();`
- L888 _public prototype_ `static bool IsLightingResolutionSelectedObjectsOnlyChecked();`
- L889 _public prototype_ `static float GetLightingResolutionMinSMs();`
- L890 _public prototype_ `static void SetLightingResolutionMinSMs( float Value );`
- L891 _public prototype_ `static float GetLightingResolutionMaxSMs();`
- L892 _public prototype_ `static void SetLightingResolutionMaxSMs( float Value );`
- L893 _public prototype_ `static float GetLightingResolutionMinBSPs();`
- L894 _public prototype_ `static void SetLightingResolutionMinBSPs( float Value );`
- L895 _public prototype_ `static float GetLightingResolutionMaxBSPs();`
- L896 _public prototype_ `static void SetLightingResolutionMaxBSPs( float Value );`
- L897 _public prototype_ `static int32 GetLightingResolutionRatio();`
- L898 _public prototype_ `static void SetLightingResolutionRatio( int32 Value );`
- L899 _public prototype_ `static void SetLightingResolutionRatioCommit( int32 Value, ETextCommit::Type CommitInfo);`
- L900 _public prototype_ `static void ShowLightingStaticMeshInfo();`
- L901 _public prototype_ `static void AttachToActor(AActor* ParentActorPtr );`
- L902 _public prototype_ `static void AttachToSocketSelection(FName SocketName, AActor* ParentActorPtr);`
- L903 _public prototype_ `static void SetMaterialQualityLevel( EMaterialQualityLevel::Type NewQualityLevel );`
- L904 _public prototype_ `static bool IsMaterialQualityLevelChecked( EMaterialQualityLevel::Type TestQualityLevel );`
- L905 _public prototype_ `static void TogglePreviewPlatform();`
- L906 _public prototype_ `static bool IsPreviewPlatformEnabled();`
- L907 _public prototype_ `static bool IsPreviewPlatformActive();`
- L908 _public prototype_ `static bool IsPreviewModeButtonVisible();`
- L911 _public function_ `static void ToggleFeatureLevelPreview()` — `UE_DEPRECATED(5.8, "Use TogglePreviewPlatform instead")`
- L913 _public function_ `static bool IsFeatureLevelPreviewEnabled()` — `UE_DEPRECATED(5.8, "Use IsPreviewPlatformEnabled instead")`
- L915 _public function_ `static bool IsFeatureLevelPreviewActive()` — `UE_DEPRECATED(5.8, "Use IsPreviewPlatformActive instead")`
- L916 _public prototype_ `static void SetPreviewPlatform(FPreviewPlatformInfo NewPreviewPlatform);`
- L917 _public prototype_ `static bool CanExecutePreviewPlatform(FPreviewPlatformInfo NewPreviewPlatform);`
- L918 _public prototype_ `static bool IsPreviewPlatformChecked(FPreviewPlatformInfo NewPreviewPlatform);`
- L919 _public prototype_ `static void GeometryCollection_SelectAllGeometry();`
- L920 _public prototype_ `static void GeometryCollection_SelectNone();`
- L921 _public prototype_ `static void GeometryCollection_SelectInverseGeometry();`
- L922 _public prototype_ `static bool GeometryCollection_IsChecked();`
- L924 _public prototype_ `static void ToggleAllowArcballRotation();`
- L925 _public prototype_ `static bool IsAllowArcballRotationChecked();`
- L927 _public prototype_ `static void ToggleAllowScreenspaceRotation();`
- L928 _public prototype_ `static bool IsAllowScreenspaceRotationChecked();`
- L930 _public prototype_ `static void ToggleEnableViewportHoverFeedback();`
- L931 _public prototype_ `static bool IsEnableViewportHoverFeedbackChecked();`
- L933 _public prototype_ `static void TogglePreviewSelectedCameras(const TWeakPtr<SLevelViewport>& InLevelViewportWeak = {});`
- L934 _public prototype_ `static bool IsPreviewSelectedCamerasChecked();`
- L936 _public prototype_ `static void ToggleOrbitCameraAroundSelection();`
- L937 _public prototype_ `static bool IsOrbitCameraAroundSelectionChecked();`
- L939 _public prototype_ `static void ToggleLinkOrthographicViewports();`
- L940 _public prototype_ `static bool IsLinkOrthographicViewportsChecked();`
- L942 _public prototype_ `static void ToggleOrthoZoomToCursor();`
- L943 _public prototype_ `static bool IsOrthoZoomToCursorChecked();`
- L945 _public prototype_ `static void ToggleInvertMiddleMousePan();`
- L946 _public prototype_ `static bool IsInvertMiddleMousePanChecked();`
- L948 _public prototype_ `static void ToggleInvertOrbitYAxis();`
- L949 _public prototype_ `static bool IsInvertOrbitYAxisChecked();`
- L951 _public prototype_ `static void ToggleInvertRightMouseDollyYAxis();`
- L952 _public prototype_ `static bool IsInvertRightMouseDollyYAxisChecked();`
- L957 _public prototype_ `static void ShowSceneStats();` — Called when the Scene Stats button is clicked.  Invokes the Primitive Stats dialog.
- L962 _public prototype_ `static void ShowTextureStats();` — Called when the Texture Stats button is clicked.  Invokes the Texture Stats dialog.
- L967 _public prototype_ `static void MapCheck_Execute();` — Called when the Map Check button is clicked.  Invokes the Map Check dialog.
- L970 _public prototype_ `static bool CanShowSourceCodeActions();` — @return True if actions that should only be visible when source code is thought to be available
- L975 _public prototype_ `static void RecompileGameCode_Clicked();` — Called when the recompile buttons are clicked.
- L976 _public prototype_ `static bool Recompile_CanExecute();`
- L982 _public prototype_ `static void LiveCoding_ToggleEnabled();` — Enables live coding mode
- L987 _public prototype_ `static bool LiveCoding_IsEnabled();` — Determines if live coding is enabled
- L992 _public prototype_ `static void LiveCoding_StartSession_Clicked();` — Starts live coding (in manual mode)
- L997 _public prototype_ `static bool LiveCoding_CanStartSession();` — Determines whether we can manually start live coding for the current session
- L1002 _public prototype_ `static void LiveCoding_ShowConsole_Clicked();` — Shows the console
- L1007 _public prototype_ `static bool LiveCoding_CanShowConsole();` — Determines whether the console can be shown
- L1012 _public prototype_ `static void LiveCoding_Settings_Clicked();` — Shows the settings panel
- L1018 _public prototype_ `static void ConnectToSourceControl_Clicked();` — Called when requesting connection to source control
- L1023 _public prototype_ `static void CheckOutModifiedFiles_Clicked();` — Called when Check Out Modified Files is clicked
- L1024 _public prototype_ `static bool CheckOutModifiedFiles_CanExecute();`
- L1029 _public prototype_ `static void SubmitToSourceControl_Clicked();` — Called when Submit to Source Control is clicked
- L1030 _public prototype_ `static bool SubmitToSourceControl_CanExecute();`
- L1035 _public prototype_ `static void FindInContentBrowser_Clicked();` — Called when the FindInContentBrowser command is executed
- L1036 _public prototype_ `static bool FindInContentBrowser_CanExecute();`
- L1039 _public prototype_ `static void EditAsset_Clicked( const EToolkitMode::Type ToolkitMode, TWeakPtr< class SLevelEditor > LevelEditor, bool bAskMultiple );` — Called to when "Edit Asset" is clicked
- L1040 _public prototype_ `static bool EditAsset_CanExecute();`
- L1043 _public prototype_ `static void OpenSelectionInPropertyMatrix_Clicked();` — Called to when "Open Selection in Property Matrix" is clicked
- L1044 _public prototype_ `static bool OpenSelectionInPropertyMatrix_IsVisible();`
- L1048 _public prototype_ `static void DetachActor_Clicked();` — Called when 'detach' is clicked
- L1049 _public prototype_ `static bool DetachActor_CanExecute();`
- L1052 _public prototype_ `static void AttachSelectedActors();` — Called when attach selected actors is pressed
- L1055 _public prototype_ `static void AttachActorIteractive();` — Called when the actor picker needs to be used to select a new parent actor
- L1058 _public prototype_ `static bool IsAttachableActor( const AActor* const ParentActor );` — @return true if the selected actor can be attached to the given parent actor
- L1061 _public prototype_ `static void CreateNewOutlinerFolder_Clicked();` — Called when create new outliner folder is clicked
- L1067 _public prototype_ `static void GoHere_Clicked( const FVector* Point );` — Called when the go here command is clicked @param Point	- Specified point to go to.  If null, a point will be calculated from current mouse position
- L1070 _public prototype_ `static void PlayFromHere_Clicked(bool bFloatingWindow);` — Called when selected actor can be used to start a play session
- L1071 _public prototype_ `static bool PlayFromHere_IsVisible();`
- L1074 _public prototype_ `static void PlayFromHere();` — If an actor is selected, plays from its position (AActor::bCanPlayFromHere must be true) otherwise it will play from last clicked position
- L1077 _public prototype_ `static void GoToCodeForActor_Clicked();` — Called when 'Go to Code for Actor' is clicked
- L1078 _public prototype_ `static bool GoToCodeForActor_CanExecute();`
- L1079 _public prototype_ `static bool GoToCodeForActor_IsVisible();`
- L1082 _public prototype_ `static void GoToDocsForActor_Clicked();` — Called when 'Go to Documentation for Actor' is clicked
- L1087 _public prototype_ `static void LockActorMovement_Clicked();` — Called when the LockActorMovement command is executed
- L1093 _public prototype_ `static bool LockActorMovement_IsChecked();` — @return true if the lock actor menu option should appear checked
- L1102 _public prototype_ `static void AddActor_Clicked( UActorFactory* ActorFactory, FAssetData AssetData);` — Called when the AddActor command is executed @param ActorFactory		The actor factory to use when adding the actor @param bUsePlacement		Whether to use the placement editor. If not, the actor will be placed at the last click. @param ActorLocation		[opt] If NULL, positions the actor at the mouse location, otherwise the location specified. Default is true.
- L1103 _public prototype_ `static AActor* AddActor( UActorFactory* ActorFactory, const FAssetData& AssetData, const FTransform* ActorLocation );`
- L1110 _public prototype_ `static void AddActorFromClass_Clicked( UClass* ActorClass );` — Called when the AddActor command is executed and a class is selected in the actor browser @param ActorClass		The class of the actor to add
- L1111 _public prototype_ `static AActor* AddActorFromClass( UClass* ActorClass );`
- L1118 _public prototype_ `static void ReplaceActors_Clicked( UActorFactory* ActorFactory, FAssetData AssetData );` — Replaces currently selected actors with an actor from the given actor factory @param ActorFactory	The actor factory to use in replacement
- L1119 _public prototype_ `static AActor* ReplaceActors( UActorFactory* ActorFactory, const FAssetData& AssetData, bool bCopySourceProperties = true );`
- L1126 _public prototype_ `static void ReplaceActorsFromClass_Clicked( UClass* ActorClass );` — Called when the ReplaceActor command is executed and a class is selected in the actor browser @param ActorClass	The class of the actor to replace
- L1133 _public prototype_ `static bool Duplicate_CanExecute();` — Called to check to see if the Edit commands can be executed @return true, if the operation can be performed
- L1134 _public prototype_ `static bool Delete_CanExecute();`
- L1135 _public prototype_ `static void Rename_Execute();`
- L1136 _public prototype_ `static bool Rename_CanExecute();`
- L1137 _public prototype_ `static bool Cut_CanExecute();`
- L1138 _public prototype_ `static bool Copy_CanExecute();`
- L1139 _public prototype_ `static bool Paste_CanExecute();`
- L1140 _public prototype_ `static bool PasteHere_CanExecute();`
- L1147 _public prototype_ `static void ExecuteExecCommand( FString Command );` — Called when many of the menu items in the level editor context menu are clicked @param Command	The command to execute
- L1154 _public prototype_ `static void OnSelectAllActorsOfClass( bool bArchetype );` — Called when selecting all actors of the same class that is selected @param bArchetype	true to also check that the archetype is the same
- L1157 _public prototype_ `static bool CanSelectAllActorsOfClass();` — Called to see if all selected actors are the same class
- L1160 _public prototype_ `static void OnSelectComponentOwnerActor();` — Called when selecting the actor that owns the currently selected component(s)
- L1163 _public prototype_ `static bool CanSelectComponentOwnerActor();` — Called to see if any components are selected
- L1166 _public prototype_ `static bool CanHideSelectedActors();` — Called to see if selected actors can be hidden
- L1169 _public prototype_ `static bool CanShowSelectedActors();` — Called to see if selected actors can be hidden
- L1172 _public prototype_ `static bool CanToggleSelectedActorsVisibility();` — Called to see if the visibility of seleced actors can be toggled
- L1177 _public prototype_ `static void OnSelectAllLights();` — Called to select all lights
- L1180 _public prototype_ `static void OnSelectStationaryLightsExceedingOverlap();` — Selects stationary lights that are exceeding the overlap limit.
- L1185 _public prototype_ `static void OnSelectOwningHLODCluster();` — Called when selecting an Actor's (if available) owning HLOD cluster
- L1192 _public prototype_ `static void OnSurfaceAlignment( ETexAlign AligmentMode );` — Called to change bsp surface alignment @param AlignmentMode	The new alignment mode
- L1197 _public prototype_ `static void OnApplyMaterialToSurface();` — Called to apply a material to selected surfaces
- L1203 _public prototype_ `static bool GroupActors_CanExecute();` — Checks to see if the selected actors can be grouped @return true if it can execute.
- L1208 _public prototype_ `static void RegroupActor_Clicked();` — Called when the RegroupActor command is executed
- L1213 _public prototype_ `static void UngroupActor_Clicked();` — Called when the UngroupActor command is executed
- L1218 _public prototype_ `static void LockGroup_Clicked();` — Called when the LockGroup command is executed
- L1223 _public prototype_ `static void UnlockGroup_Clicked();` — Called when the UnlockGroup command is executed
- L1228 _public prototype_ `static void AddActorsToGroup_Clicked();` — Called when the AddActorsToGroup command is executed
- L1233 _public prototype_ `static void RemoveActorsFromGroup_Clicked();` — Called when the RemoveActorsFromGroup command is executed
- L1238 _public prototype_ `static void LocationGridSnap_Clicked();` — Called when the location grid snap is toggled off and on
- L1243 _public prototype_ `static bool LocationGridSnap_IsChecked();` — @return Returns whether or not location grid snap is enabled
- L1248 _public prototype_ `static void RotationGridSnap_Clicked();` — Called when the rotation grid snap is toggled off and on
- L1253 _public prototype_ `static bool RotationGridSnap_IsChecked();` — @return Returns whether or not rotation grid snap is enabled
- L1258 _public prototype_ `static void ScaleGridSnap_Clicked();` — Called when the scale grid snap is toggled off and on
- L1263 _public prototype_ `static bool ScaleGridSnap_IsChecked();` — @return Returns whether or not scale grid snap is enabled
- L1267 _public prototype_ `static void OnKeepSimulationChanges();` — Called when "Keep Simulation Changes" is clicked in the viewport right click menu
- L1270 _public prototype_ `static bool CanExecuteKeepSimulationChanges();` — @return Returns true if 'Keep Simulation Changes' can be used right now
- L1277 _public prototype_ `static void OnMakeSelectedActorLevelCurrent();` — Makes the currently selected actors level the current level If multiple actors are selected they must all be in the same level
- L1282 _public prototype_ `static void OnMoveSelectedToCurrentLevel();` — Moves the currently selected actors to the current level
- L1285 _public prototype_ `static void OnFindActorLevelInContentBrowser();` — Finds the currently selected actor(s) level in the content browser
- L1288 _public prototype_ `static bool CanExecuteFindActorLevelInContentBrowser();` — @return Returns true if all selected actors are from the same level and hence can browse to it in the content browser
- L1294 _public prototype_ `static void OnFindLevelsInLevelBrowser();` — Selects the currently selected actor(s) levels in the level browser Deselecting everything else first
- L1299 _public prototype_ `static void OnSelectLevelInLevelBrowser();` — Selects the currently selected actor(s) levels in the level browser
- L1304 _public prototype_ `static void OnDeselectLevelInLevelBrowser();` — Deselects the currently selected actor(s) levels in the level browser
- L1309 _public prototype_ `static void OnFindActorInLevelScript();` — Finds references to the currently selected actor(s) in level scripts
- L1312 _public prototype_ `static void OnShowWorldProperties( TWeakPtr< SLevelEditor > LevelEditor );` — Select the world info actor and show the properties
- L1315 _public prototype_ `static void OnFocusOutlinerToSelection(TWeakPtr<SLevelEditor> LevelEditor);` — Focuses the outliner on the selected actors
- L1318 _public prototype_ `static void OnFocusOutlinerToContextFolder(TWeakPtr<SLevelEditor> LevelEditor);` — Focuses the outliner on the context folder if it's currently set
- L1321 _public prototype_ `static void OpenPlaceActors();` — Open the Place Actors Panel
- L1324 _public prototype_ `static void OpenContentBrowser();` — Open the Content Browser
- L1327 _public prototype_ `static void ImportContent();` — Import content into a chosen location
- L1330 _public prototype_ `static void CheckOutProjectSettingsConfig();` — Checks out the Project Settings config
- L1333 _public prototype_ `static void OpenLevelBlueprint( TWeakPtr< SLevelEditor > LevelEditor );` — Open the level's blueprint in Kismet2
- L1336 _public prototype_ `static bool CanSelectGameModeBlueprint();` — Returns TRUE if the user can edit the game mode Blueprint, this requires the DefaultEngine config file to be writable
- L1339 _public prototype_ `static void CreateBlankBlueprintClass();` — Helps the user create a Blueprint class
- L1342 _public prototype_ `static bool CanConvertSelectedActorsIntoBlueprintClass();` — Can the selected actors be converted to a blueprint class in any of the supported ways?
- L1345 _public prototype_ `static void ConvertSelectedActorsIntoBlueprintClass();` — Bring up the convert actors to blueprint UI
- L1348 _public prototype_ `static void OnShowOnlySelectedActors();` — Shows only selected actors, hiding any unselected actors and unhiding any selected hidden actors.
- L1353 _public prototype_ `static void OnToggleTransformWidgetVisibility();` — View callbacks
- L1354 _public prototype_ `static bool OnGetTransformWidgetVisibility();`
- L1355 _public prototype_ `static void OnToggleShowSelectionSubcomponents();`
- L1356 _public prototype_ `static bool OnGetShowSelectionSubcomponents();`
- L1357 _public prototype_ `static void OnAllowTranslucentSelection();`
- L1358 _public prototype_ `static bool OnIsAllowTranslucentSelectionEnabled();`
- L1359 _public prototype_ `static void OnAllowGroupSelection();`
- L1360 _public prototype_ `static bool OnIsAllowGroupSelectionEnabled();`
- L1361 _public prototype_ `static void OnToggleStrictBoxSelect();`
- L1362 _public prototype_ `static bool OnIsStrictBoxSelectEnabled();`
- L1363 _public prototype_ `static void OnToggleTransparentBoxSelect();`
- L1364 _public prototype_ `static bool OnIsTransparentBoxSelectEnabled();`
- L1365 _public prototype_ `static void OnDrawBrushMarkerPolys();`
- L1366 _public prototype_ `static bool OnIsDrawBrushMarkerPolysEnabled();`
- L1367 _public prototype_ `static void OnToggleOnlyLoadVisibleInPIE();`
- L1368 _public prototype_ `static bool OnIsOnlyLoadVisibleInPIEEnabled();`
- L1369 _public prototype_ `static void OnToggleSocketSnapping();`
- L1370 _public prototype_ `static bool OnIsSocketSnappingEnabled();`
- L1371 _public prototype_ `static void OnToggleParticleSystemLOD();`
- L1372 _public prototype_ `static bool OnIsParticleSystemLODEnabled();`
- L1373 _public prototype_ `static void OnToggleFreezeParticleSimulation();`
- L1374 _public prototype_ `static bool OnIsParticleSimulationFrozen();`
- L1375 _public prototype_ `static void OnToggleParticleSystemHelpers();`
- L1376 _public prototype_ `static bool OnIsParticleSystemHelpersEnabled();`
- L1377 _public prototype_ `static void OnToggleLODViewLocking();`
- L1378 _public prototype_ `static bool OnIsLODViewLockingEnabled();`
- L1379 _public prototype_ `static void OnToggleLevelStreamingVolumePrevis();`
- L1380 _public prototype_ `static bool OnIsLevelStreamingVolumePrevisEnabled();`
- L1382 _public prototype_ `static FText GetAudioVolumeToolTip();`
- L1383 _public prototype_ `static float GetAudioVolume();`
- L1384 _public prototype_ `static void OnAudioVolumeChanged(float Volume);`
- L1385 _public prototype_ `static bool GetAudioMuted();`
- L1386 _public prototype_ `static void OnAudioMutedChanged(bool bMuted);`
- L1388 _public prototype_ `static void OnEnableActorSnap();`
- L1389 _public prototype_ `static bool OnIsActorSnapEnabled();`
- L1390 _public prototype_ `static FText GetActorSnapTooltip();`
- L1391 _public prototype_ `static float GetActorSnapSetting();`
- L1392 _public prototype_ `static void SetActorSnapSetting(float Distance);`
- L1393 _public prototype_ `static void OnEnableVertexSnap();`
- L1394 _public prototype_ `static bool OnIsVertexSnapEnabled();`
- L1396 _public prototype_ `static void OnToggleShowViewportToolbar();`
- L1397 _public prototype_ `static bool IsViewportToolbarVisible();`
- L1399 _public prototype_ `static void OnToggleShowViewportUI();`
- L1400 _public prototype_ `static bool IsViewportUIVisible();`
- L1402 _public prototype_ `static bool IsEditorModeActive( FEditorModeID EditorMode );`
- L1404 _public prototype_ `static void MakeBuilderBrush( UClass* BrushBuilderClass );`
- L1406 _public prototype_ `static void OnAddVolume( UClass* VolumeClass );`
- L1408 _public prototype_ `static void SelectActorsInLayers();`
- L1410 _public prototype_ `static void SetWidgetMode( UE::Widget::EWidgetMode WidgetMode );`
- L1411 _public prototype_ `static bool IsWidgetModeActive( UE::Widget::EWidgetMode WidgetMode );`
- L1412 _public prototype_ `static bool CanSetWidgetMode( UE::Widget::EWidgetMode WidgetMode );`
- L1413 _public prototype_ `static bool IsTranslateRotateModeVisible();`
- L1414 _public prototype_ `static void SetCoordinateSystem( ECoordSystem CoordSystem );`
- L1415 _public prototype_ `static bool IsCoordinateSystemActive( ECoordSystem CoordSystem );`
- L1420 _public prototype_ `static class UWorld* GetWorld();` — Return a world
- L1425 _public prototype_ `static void MoveElementsToGrid_Clicked( bool InAlign, bool InPerElement );` — Moves the selected elements to the grid.
- L1430 _public prototype_ `static void SnapObjectToView_Clicked();` — Snaps a selected actor to the camera view.
- L1435 _public prototype_ `static void CopyActorFilePathtoClipboard_Clicked();` — Copy the file path where the actor is saved.
- L1440 _public prototype_ `static void ViewActorReferences_Clicked();` — Opens the reference viewer for the selected actor.
- L1446 _public prototype_ `static bool ViewActorReferences_CanExecute();` — Checks whether OpenActorInReferenceViewer can be executed on the selected actor. @return 	True if OpenActorInReferenceViewer can be executed on the selected actor.
- L1451 _public prototype_ `static void SaveActor_Clicked();` — Save the actor.
- L1457 _public prototype_ `static bool SaveActor_CanExecute();` — Checks whether SaveActor can be executed on the selected actors. @return 	True if SaveActor can be executed on the selected actors.
- L1462 _public prototype_ `static void ShowActorHistory_Clicked();` — Shows the history of the file containing the actor.
- L1468 _public prototype_ `static bool ShowActorHistory_CanExecute();` — Checks whether ShowActorHistory can be executed on the selected actors. @return 	True if ShowActorHistory can be executed on the selected actors.
- L1473 _public prototype_ `static void MoveElementsToElement_Clicked( bool InAlign );` — Moves the selected elements to the last selected element.
- L1478 _public prototype_ `static void SnapTo2DLayer_Clicked();` — Snaps an actor to the currently selected 2D snap layer
- L1484 _public prototype_ `static bool CanSnapTo2DLayer();` — Checks to see if at least a single actor is selected and the 2D editor mode is enabled @return true if it can execute.
- L1489 _public prototype_ `static void MoveSelectionToDifferent2DLayer_Clicked(bool bGoingUp, bool bForceToTopOrBottom);` — Snaps an actor to the currently selected 2D snap layer
- L1495 _public prototype_ `static bool CanMoveSelectionToDifferent2DLayer(bool bGoingUp);` — Checks to see if at least a single actor is selected and the 2D editor mode is enabled and there is a layer above/below the current setting @return true if it can execute.
- L1500 _public prototype_ `static void Select2DLayerDeltaAway_Clicked(int32 Delta);` — Changes the active 2D snap layer to one a delta above or below the current layer
- L1509 _public prototype_ `static void SnapToFloor_Clicked( bool InAlign, bool InUseLineTrace, bool InUseBounds, bool InUsePivot );` — Snaps the selected elements to the floor.  Optionally will align with the trace normal. @param InAlign			Whether or not to rotate the actor to align with the trace normal. @param InUseLineTrace	Whether or not to only trace with a line through the world. @param InUseBounds		Whether or not to base the line trace off of the bounds. @param InUsePivot		Whether or not to use the pivot position.
- L1518 _public prototype_ `static void SnapElementsToElement_Clicked( bool InAlign, bool InUseLineTrace, bool InUseBounds, bool InUsePivot );` — Snaps the selected elements to another element.  Optionally will align with the trace normal. @param InAlign			Whether or not to rotate the actor to align with the trace normal. @param InUseLineTrace	Whether or not to only trace with a line through the world. @param InUseBounds		Whether or not to base the line trace off of the bounds. @param InUsePivot		Whether or not to use the pivot position.
- L1523 _public prototype_ `static void AlignBrushVerticesToGrid_Execute();` — Aligns brush vertices to the nearest grid point.
- L1529 _public prototype_ `static bool ActorSelected_CanExecute();` — Checks to see if at least one actor is selected @return true if it can execute.
- L1546 _public prototype_ `static bool ActorTypesSelected_CanExecute(EActorTypeFlags TypeFlags, bool bSingleOnly);` — Checks to see if at least one actor (of the given types) is selected @param TypeFlags		actor types to look for - one or more of EActorTypeFlags or'ed together @param bSingleOnly	if true, then requires selection to be exactly one actor @return				true if it can execute.
- L1552 _public prototype_ `static bool ActorsSelected_CanExecute();` — Checks to see if multiple actors are selected @return true if it can execute.
- L1559 _public prototype_ `static bool ElementSelected_CanExecute();` — `UE_DEPRECATED(5.4, "Use ElementSelected_CanExecuteMove. If you only needed to verify if there is at least one item in the selection set, use the selection set directly from the level editor.")` — Checks to see if at least one element is selected @return true if it can execute.
- L1566 _public prototype_ `static bool ElementsSelected_CanExecute();` — `UE_DEPRECATED(5.4, "Use ElementsSelected_CanExecuteMove. If you only needed to verify if there is more than one item in the selection set, use the selection set directly from the level editor.")` — Checks to see if multiple elements are selected @return true if it can execute.
- L1572 _public prototype_ `static bool ElementSelected_CanExecuteMove();` — Checks to see if at least one element is selected that can be translated @return true if it can execute.
- L1578 _public prototype_ `static bool ElementsSelected_CanExecuteMove();` — Checks to see if multiple elements are selected that can be translated @return true if it can execute.
- L1584 _public prototype_ `static bool ElementSelected_CanExecuteScale();` — Checks to see if at least one element is selected that can be scaled @return true if it can execute.
- L1590 _public prototype_ `static bool ElementsSelected_CanExecuteScale();` — Checks to see if multiple elements are selected that can be scaled @return true if it can execute.
- L1593 _public prototype_ `static void OpenMergeActor_Clicked();` — Called when 'Open Merge Actor' is clicked
- L1600 _private prototype_ `static void MoveTo_Clicked( const UTypedElementSelectionSet* InSelectionSet, const bool InAlign, bool InPerElement, const TTypedElement<ITypedElementWorldInterface>& InDestination = TTypedElement<ITypedElementWorldInterface>() );` — Moves the selected elements. @param InDestination		The destination element we want to move this element to, or invalid to move to the grid
- L1610 _private prototype_ `static void SnapTo_Clicked(const UTypedElementSelectionSet* InSelectionSet, const bool InAlign, const bool InUseLineTrace, const bool InUseBounds, const bool InUsePivot, const TTypedElement<ITypedElementWorldInterface>& InDestination = TTypedElement<ITypedElementWorldInterface>() );` — Snaps the selected elements. Optionally will align with the trace normal. @param InAlign			Whether or not to rotate the actor to align with the trace normal. @param InUseLineTrace	Whether or not to only trace with a line through the world. @param InUseBounds		Whether or not to base the line trace off of the bounds. @param InUsePivot		Whether or not to use the pivot position. @param InDestination		The destination element we want to move this actor to, or invalid to go towards the floor
- L1618 _private prototype_ `static bool SaveAnimationFromSkeletalMeshComponent(AActor * EditorActor, AActor * SimActor, TArray<class USkeletalMeshComponent*> & OutEditorComponents);` — Create and apply animation to the SkeletalMeshComponent if Simulating @param EditorActor	Editor Counterpart Actor @param SimActor		Simulating Actor in PIE or SIE
- L1621 _public prototype_ `static void FixupGroupActor_Clicked();`

#### enum `FLevelEditorActionCallbacks::EActorTypeFlags`  
`enum EActorTypeFlags : uint8`  
_L1531-1537_
- L1533 _public enumerator_ `IncludePawns = 1 << 0`
- L1534 _public enumerator_ `IncludeStaticMeshes = 1 << 1`
- L1535 _public enumerator_ `IncludeSkeletalMeshes = 1 << 2`
- L1536 _public enumerator_ `IncludeEmitters = 1 << 3`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API LEVELEDITOR_API`
- L727 _delegate_ `DECLARE_DELEGATE_OneParam(FNewLevelOverride, bool& );`

### `Source/Editor/LevelEditor/Public/LevelEditorCameraEditorState.h` (Public)


#### class `ULevelEditorCameraEditorState`  
`class ULevelEditorCameraEditorState : public UWorldDependantEditorState`  
_L12-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldDependantEditorState`
- L18 _public prototype_ `virtual FText GetCategoryText() const override;`
- L20 _public prototype_ `const FVector& GetCameraLocation() const;`
- L21 _public prototype_ `const FRotator& GetCameraRotation() const;`
- L22 _public prototype_ `const float GetCameraFOVAngle() const;`
- L25 _private prototype_ `virtual FOperationResult CaptureState() override;`
- L26 _private prototype_ `virtual FOperationResult RestoreState() const override;`
- L29 _private prototype_ `void RestoreCameraState(TSharedPtr<ILevelEditor> LevelEditor) const;`
- L34 _private member_ `FVector CameraLocation;` — `UPROPERTY(EditAnywhere, Category = Camera)` — Camera position
- L38 _private member_ `FRotator CameraRotation;` — `UPROPERTY(EditAnywhere, Category = Camera)` — Camera rotation
- L42 _private member_ `float CameraFOVAngle;` — `UPROPERTY(EditAnywhere, Category = Camera)` — Camera FOV Angle
- L44 _private member_ `mutable FDelegateHandle OnLevelEditorCreatedDelegateHandle;`

### `Source/Editor/LevelEditor/Public/LevelEditorContextMenu.h` (Public)


#### class `FLevelEditorContextMenu`  
`class FLevelEditorContextMenu`  
_L23-101_
- desc: Context menu construction class
- L34 _public prototype_ `static void SummonMenu( const TSharedRef< class SLevelEditor >& LevelEditor, ELevelEditorMenuContext ContextType, const FTypedElementHandle& HitProxyElement = FTypedElementHandle());` — Summons the level viewport context menu @param	LevelEditor		The level editor using this menu. @param	ContextType		The context we should use to specialize this menu @param	HitProxyActor	The hitproxy actor in the case the ContextType is Viewport
- L40 _public prototype_ `static void SummonViewOptionMenu( const TSharedRef< class SLevelEditor >& LevelEditor, const ELevelViewportType ViewOption );` — Summons the viewport view option menu @param LevelEditor		The level editor using this menu.
- L51 _public prototype_ `static TSharedRef< SWidget > BuildMenuWidget(TWeakPtr< ILevelEditor > LevelEditor, ELevelEditorMenuContext ContextType, TSharedPtr<FExtender> Extender = TSharedPtr<FExtender>(), const FTypedElementHandle& HitProxyElement = FTypedElementHandle());` — Creates a widget for the context menu that can be inserted into a pop-up window @param	LevelEditor		The level editor using this menu. @param	ContextType		The context we should use to specialize this menu @param	Extender		Allows extension of this menu based on context. @param	HitProxyActor	The hitproxy actor in the case the ContextType is Viewport @return	Widget for this context menu
- L62 _public prototype_ `static UToolMenu* GenerateMenu(TWeakPtr< ILevelEditor > LevelEditor, ELevelEditorMenuContext ContextType, TSharedPtr<FExtender> Extender = TSharedPtr<FExtender>(), const FTypedElementHandle& HitProxyElement = FTypedElementHandle());` — Populates the specified menu builder for the context menu that can be inserted into a pop-up window @param	Menu			The menu to fill @param	LevelEditor		The level editor using this menu. @param	ContextType		The context we should use to specialize this menu @param	Extender		Allows extension of this menu based on context. @param	HitProxyActor	The hitproxy actor in the case the ContextType is Viewport
- L65 _public prototype_ `static FName InitMenuContext(FToolMenuContext& Context, TWeakPtr<ILevelEditor> LevelEditor, ELevelEditorMenuContext ContextType, const FTypedElementHandle& HitProxyElement = FTypedElementHandle());` — Adds required information to Context for build menu based on current selection
- L68 _public prototype_ `static FName GetContextMenuName(ELevelEditorMenuContext ContextType, const UTypedElementSelectionSet* InSelectionSet);` — Returns name of menu to display based on current selection
- L71 _public prototype_ `static FText GetContextMenuTitle(ELevelEditorMenuContext ContextType, const UTypedElementSelectionSet* InSelectionSet);` — Returns a user-readable title for the menu to display; the title can be displayed in UI like the menu bar
- L74 _public prototype_ `static FText GetContextMenuToolTip(ELevelEditorMenuContext ContextType, const UTypedElementSelectionSet* InSelectionSet);` — Returns a user-readable tooltip describing the menu to display
- L76 _public prototype_ `static void RegisterComponentContextMenu();`
- L77 _public prototype_ `static void RegisterActorContextMenu();`
- L78 _public prototype_ `static void RegisterElementContextMenu();`
- L79 _public prototype_ `static void RegisterSceneOutlinerContextMenu();`
- L80 _public prototype_ `static void RegisterMenuBarEmptyContextMenu();`
- L81 _public prototype_ `static void RegisterEmptySelectionContextMenu();`
- L92 _public prototype_ `static void AddPlayFromHereSubMenu(FToolMenuSection& Section);`
- L100 _public prototype_ `static void BuildGroupMenu(FToolMenuSection& Section, const struct FSelectedActorInfo& SelectedActorInfo);` — Builds the actor group menu @param Menu		The menu to add items to. @param SelectedActorInfo	Information about the selected actors.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/LevelEditorMenuContext.h` (Public)


#### class `ULevelEditorMenuContext`  
`class ULevelEditorMenuContext : public UObject`  
_L36-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L40 _public prototype_ `TWeakPtr<ILevelEditor> GetLevelEditor() const;`
- L42 _public member_ `TWeakPtr<SLevelEditor> LevelEditor;`

#### enum `ELevelEditorMenuContext`  
`enum class ELevelEditorMenuContext : uint8`  
_L48-56_
- reflection: `UENUM()`
- desc: Enum to describe what a level editor context menu should be built for
- L51 _public enumerator_ `Viewport` — This context menu is applicable to a viewport (limited subset of entries)
- L53 _public enumerator_ `SceneOutliner` — This context menu is applicable to the Scene Outliner (disables click-position-based menu items)
- L55 _public enumerator_ `MainMenu` — This is the replica of the context menu that appears in the main menu bar (lists all entries)

#### class `ULevelEditorContextMenuContext`  
`class ULevelEditorContextMenuContext : public UObject`  
_L59-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L63 _public member_ `TWeakPtr<ILevelEditor> LevelEditor;`
- L66 _public member_ `ELevelEditorMenuContext ContextType;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelEditor|Menu")`
- L69 _public member_ `TObjectPtr<const UTypedElementSelectionSet> CurrentSelection;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelEditor|Menu")`
- L72 _public member_ `FTypedElementHandle HitProxyElement;` — If the ContextType is Viewport this property can be set to the HitProxy element that triggered the ContextMenu.
- L75 _public member_ `FVector CursorWorldLocation;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelEditor|Menu")`
- L78 _public member_ `TArray<TObjectPtr<UActorComponent>> SelectedComponents;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelEditor|Menu")`
- L82 _public member_ `TWeakObjectPtr<AActor> HitProxyActor = nullptr;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelEditor|Menu")` — If the ContextType is Viewport this property can be set to the HitProxy actor that triggered the ContextMenu.
- L85 _public prototype_ `FScriptTypedElementHandle GetScriptHitProxyElement();` — `UFUNCTION(BlueprintCallable, Category = "LevelEditor | Menu", DisplayName="Get Hit Proxy Element", meta=(ScriptName="GetHitProxyElement"))`

#### class `ULevelViewportContext`  
`class ULevelViewportContext : public UObject`  
_L89-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L94 _public prototype_ `static TSharedPtr<SLevelViewport> GetLevelViewport(const UToolMenu* Menu);`
- L95 _public prototype_ `static TSharedPtr<SLevelViewport> GetLevelViewport(const FToolMenuSection& Section);`
- L96 _public prototype_ `static TSharedPtr<SLevelViewport> GetLevelViewport(const FToolMenuContext& Context);`
- L98 _public member_ `TWeakPtr<SLevelViewport> LevelViewport;`
- L100 _public prototype_ `FLevelEditorViewportClient* GetLevelViewportClient() const;`

#### class `ULevelViewportToolBarContext`  
`class UE_DEPRECATED(5.7, "Use ULevelViewportContext instead") ULevelViewportToolBarContext : public UObject`  
_L105-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L110 _public member_ `TWeakPtr<SLevelViewportToolBar> LevelViewportToolBarWidget;`
- L113 _public function_ `virtual FLevelEditorViewportClient* GetLevelViewportClient() const`

#### class `UQuickActionMenuContext`  
`class UQuickActionMenuContext : public UObject`  
_L118-124_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L123 _public member_ `TObjectPtr<const UTypedElementSelectionSet> CurrentSelection;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="LevelEditor|Menu")`

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/LevelEditorModesActions.h` (Public)


#### class `FLevelEditorModesCommands`  
`class FLevelEditorModesCommands : public TCommands<FLevelEditorModesCommands>`  
_L12-35_
- inherits: `TCommands<FLevelEditorModesCommands>`
- desc: Unreal level editor actions
- L16 _public function_ `FLevelEditorModesCommands() : TCommands<FLevelEditorModesCommands> ( "LevelEditorModes",`
- L29 _public prototype_ `virtual void RegisterCommands() override;` — Initialize commands
- L34 _public member_ `TArray< TSharedPtr< FUICommandInfo > > EditorModeCommands;` — Editor mode commands

### `Source/Editor/LevelEditor/Public/LevelEditorOutlinerSettings.h` (Public)


#### struct `FLevelEditorOutlinerBuiltInCategories`  
`struct FLevelEditorOutlinerBuiltInCategories`  
_L21-34_
- desc: Structure of built-in filter categories. Defined as functions to enable external use without linkage
- L23 _public function_ `static FName Common()`
- L24 _public function_ `static FName Basic()`
- L25 _public function_ `static FName Animation()`
- L26 _public function_ `static FName Audio()`
- L27 _public function_ `static FName Geometry()`
- L28 _public function_ `static FName Lights()`
- L29 _public function_ `static FName Environment()`
- L30 _public function_ `static FName Visual()`
- L31 _public function_ `static FName Volumes()`
- L32 _public function_ `static FName VirtualProduction()`
- L33 _public function_ `static FName SourceControl()`

#### class `FLevelEditorOutlinerSettings`  
`class FLevelEditorOutlinerSettings : public TSharedFromThis<class FLevelEditorOutlinerSettings>`  
_L40-132_
- inherits: `TSharedFromThis<classFLevelEditorOutlinerSettings>`
- desc: Helper class to manage initalization options specific to the Level Editor Outliners Use AddCustomFilter/AddCustomClass Filter to register new filters in the Outliner. Make sure that the filters you attach have a category, otherwise they will not show up
- L43 _public function_ `FLevelEditorOutlinerSettings()`
- L44 _public prototype_ `~FLevelEditorOutlinerSettings();`
- L46 _public prototype_ `void Initialize();`
- L49 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<FFilterBase<const ISceneOutlinerTreeItem&>>, FOutlinerFilterFactory);` — Delegate to create a Filter for the Outliner
- L58 _public prototype_ `void AddCustomFilter(TSharedRef<FFilterBase<const ISceneOutlinerTreeItem&>> InCustomFilter);` — `UE_DEPRECATED(5.2, "Use the AddCustomFilter override that takes in a factory instead so each Outliner can have a unique instance of the filter")`
- L65 _public prototype_ `void AddCustomFilter(FOutlinerFilterFactory InCreateCustomFilter);` — Add a custom filter to the outliner filter bar. These are all AND'd together This function takes in a delegate that will be called to create an instance of the custom filter for each Outliner that the level editor creates. @see FGenericFilter on how to create generic filters
- L70 _public prototype_ `void AddCustomClassFilter(TSharedRef<FCustomClassFilterData> InCustomClassFilterData);` — Add a custom class filter to the outliner filter bar. These represent asset/actor type filters and are OR'd Can be created using IAssetTypeActions or UClass (@see constructor)
- L73 _public prototype_ `void CreateDefaultFilters();` — Creates the default filters that the level editor outliner has
- L76 _public prototype_ `void SetupBuiltInCategories();` — Setup the built in filter categories
- L79 _public prototype_ `void GetOutlinerFilters(FSceneOutlinerFilterBarOptions& OutFilterBarOptions);` — Append the init options stored in this class to the given Outliner init options
- L82 _public prototype_ `TSharedPtr<FFilterCategory> GetFilterCategory(const FName& CategoryName);` — Get the FFilterCategory attached to the given category name. Use this to add filters to the built in categories
- L86 _private prototype_ `void CreateSCCFilters();`
- L88 _private prototype_ `bool DoesActorPassUnsavedFilter(const ISceneOutlinerTreeItem& InItem);`
- L89 _private prototype_ `bool DoesActorPassUncontrolledFilter(const ISceneOutlinerTreeItem& InItem);`
- L91 _private prototype_ `void OnUnsavedAssetAdded(const FString& InAsset);`
- L92 _private prototype_ `void OnUnsavedAssetRemoved(const FString& InAsset);`
- L94 _private prototype_ `void OnUncontrolledChangelistModuleChanged();`
- L97 _private prototype_ `void RefreshOutlinersWithActiveFilter(bool bFullRefresh, const FString& InFilterName);` — Refresh any Outliners that have the given filter active
- L103 _private member_ `TArray<TSharedRef<FFilterBase<const ISceneOutlinerTreeItem&>>> CustomFilters;` — These are the custom filters that the Scene Outliner will have. All active filters will be AND'd together to test against.
- L106 _private member_ `TArray<FOutlinerFilterFactory> CustomFilterDelegates;` — These are delegates that will be used to create custom filters for each outliner that calls GetOutlinerFilters
- L111 _private member_ `TArray<TSharedRef<FCustomClassFilterData>> CustomClassFilters;` — These are the asset type filters that the Scene Outliner will have. All active filters will be OR'd together to test against.
- L114 _private member_ `TArray<TSharedRef<FFilterBase<const ISceneOutlinerTreeItem&>>> BuiltInCustomFilters;` — The built in custom filters created by this instance
- L117 _private member_ `TMap<FName, TSharedPtr<FFilterCategory>> FilterBarCategories;` — A map of the categories the Outliner filter bar will have
- L120 _private member_ `TMap<FName, FName> PlacementToFilterCategoryMap;` — A map to convert placement mode built in categories to filter bar categories
- L125 _private member_ `TSet<FName> UnsavedPackages;` — List of currently unsaved packages. Using a set here because it can grow a lot and impact performances when looking up in the list.
- L128 _private member_ `TSet<FName> UncontrolledPackages;` — List of currently uncontrolled packages. Using a set here because it can grow a lot and impact performances when looking up in the list.
- L130 _private member_ `static const FString UnsavedAssetsFilterName;`
- L131 _private member_ `static const FString UncontrolledAssetsFilterName;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LEVELEDITOR_API`
- L11 _namespace_ `namespace SceneOutliner`
- L14 _typedef_ `typedef const ISceneOutlinerTreeItem& FilterBarType;` (scope `SceneOutliner`) — The type of item that the Outliner's Filter Bar operates on
- L49 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<FFilterBase<const ISceneOutlinerTreeItem&>>, FOutlinerFilterFactory);` — Delegate to create a Filter for the Outliner

### `Source/Editor/LevelEditor/Public/LevelEditorSubsystem.h` (Public)


#### class `ULevelEditorSubsystem`  
`class ULevelEditorSubsystem : public UEditorSubsystem, public IActorEditorContextClient`  
_L38-282_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem,IActorEditorContextClient`
- desc: ULevelEditorSubsystem Subsystem for exposing Level Editor related functionality to scripts
- L43 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L45 _public prototype_ `virtual void Deinitialize() override;`
- L46 _public prototype_ `void ExtendQuickActionMenu();`
- L49 _public prototype_ `void PilotLevelActor(AActor* ActorToPilot, FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta=(DevelopmentOnly))`
- L50 _public prototype_ `void PilotLevelActor(const FToolMenuContext& InContext);`
- L52 _public prototype_ `void EjectPilotLevelActor(FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L55 _public prototype_ `AActor* GetPilotLevelActor(FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta=(DevelopmentOnly))`
- L58 _public prototype_ `bool GetExactCameraView(FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L60 _public prototype_ `void SetExactCameraView(bool bExactCameraView, FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L63 _public prototype_ `void EditorPlaySimulate();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L66 _public prototype_ `void EditorInvalidateViewports();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L69 _public prototype_ `void EditorSetViewportRealtime(bool bInRealtime, FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L72 _public prototype_ `void EditorSetGameView(bool bGameView, FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L75 _public prototype_ `bool EditorGetGameView(FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L78 _public prototype_ `void EditorRequestBeginPlay();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L81 _public prototype_ `void EditorRequestEndPlay();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L84 _public prototype_ `bool IsInPlayInEditor() const;` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L87 _public prototype_ `TArray<FName> GetViewportConfigKeys();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L90 _public prototype_ `FName GetActiveViewportConfigKey();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L93 _public prototype_ `void SetAllowsCinematicControl(bool bAllow, FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L96 _public prototype_ `bool GetAllowsCinematicControl(FName ViewportConfigKey = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))`
- L107 _public prototype_ `bool GetLevelViewportCameraInfo(FVector& CameraLocation, FRotator& CameraRotation, FName ViewportConfigKey);` — `UFUNCTION(BlueprintPure, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))` — Gets information about the camera position for the given level editor viewport. @param	CameraLocation	(out) Current location of the level editing viewport camera, or zero if none found @param	CameraRotation	(out) Current rotation of the level editing viewport camera, or zero if none found @param	ViewportConfigKey the viewport you wish to get from @return	Whether we were able to get the camera position for a level editing viewport
- L118 _public prototype_ `void SetLevelViewportCameraInfo(FVector CameraLocation, FRotator CameraRotation, FName ViewportConfigKey);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta = (DevelopmentOnly))` — Sets information about the camera position for the given level editor viewport. @param	CameraLocation	Location the camera will be moved to @param	CameraRotation	Rotation the camera will be set to @param	ViewportConfigKey	the viewport you wish to target
- L128 _public prototype_ `bool GetLevelViewportFOV(float& FOV, FName ViewportConfigKey);` — `UFUNCTION(BlueprintPure, Category = "Editor Scripting | Level Utility", meta=(DisplayName="Get Level Viewport Field Of View", DevelopmentOnly))` — Gets the horizontal field of view for the given level editor viewport. @param	FOV				Field of View of the Level editing viewport camera @param	ViewportConfigKey	the viewport you wish to get from @return	Whether we were able to get the FOV for a level editing viewport
- L137 _public prototype_ `void SetLevelViewportFOV(float FOV, FName ViewportConfigKey);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility", meta=(DisplayName="Set Level Viewport Field Of View", DevelopmentOnly))` — Sets the horizontal field of view for the given level editor viewport. @param	FOV					Field of View to set the camera to. Value will be clamped between 5 and 170 deg @param	ViewportConfigKey	the viewport you wish to target
- L147 _public prototype_ `bool NewLevel(const FString& AssetPath, bool bIsPartitionedWorld = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Close the current Persistent Level (without saving it). Create a new blank Level and save it. Load the new created level. @param	AssetPath		Asset Path of where the level will be saved. ie. /Game/MyFolder/MyAsset @param   bIsPartitionedWorld	If true, new map is partitioned. @return	True if the operation succeeds.
- L158 _public prototype_ `bool NewLevelFromTemplate(const FString& AssetPath, const FString& TemplateAssetPath);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Close the current Persistent Level (without saving it). Create a new Level base on another level and save it. Load the new created level. @param	AssetPath				Asset Path of where the level will be saved. ie. /Game/MyFolder/MyAsset @param	TemplateAssetPath		Level to be used as Template. ie. /Game/MyFolder/MyAsset @return	True if the operation succeeds.
- L167 _public prototype_ `bool LoadLevel(const FString& AssetPath);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Close the current Persistent Level (without saving it). Loads the specified level. @param	AssetPath				Asset Path of the level to be loaded. ie. /Game/MyFolder/MyAsset @return	True if the operation succeeds.
- L174 _public prototype_ `bool SaveCurrentLevel();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Saves the specified Level. Must already be saved at lease once to have a valid path. @return	True if the operation succeeds.
- L181 _public prototype_ `bool SaveAllDirtyLevels();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Saves all Level currently loaded by the World Editor. @return	True if the operation succeeds.
- L190 _public prototype_ `bool SetCurrentLevelByName(FName LevelName);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Set the current level used by the world editor. If more than one level shares the same name, the first one encounter of that level name will be used. @param	LevelName	The name of the Level the actor belongs to (same name as in the ContentBrowser). @return	True if the operation succeeds.
- L197 _public prototype_ `ULevel* GetCurrentLevel();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Get the current level used by the world editor. @return	The current level
- L206 _public prototype_ `bool DeleteActorFolder(FName FolderPath);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Deletes a folder from the World Outliner. Does not move or delete actors; only removes the folder entry itself. @param	FolderPath	The path of the folder to delete (e.g. 'Lighting/Spotlights'). @return	True if the folder existed and was deleted.
- L213 _public prototype_ `UTypedElementSelectionSet* GetSelectionSet();` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Get the selection set for the current world, you can use this to track and create changes to the level editor's selection
- L222 _public prototype_ `bool BuildLightMaps(ELightingBuildQuality Quality = ELightingBuildQuality::Quality_Production, bool bWithReflectionCaptures = false);` — `UFUNCTION(BlueprintCallable, Category = "Editor Scripting | Level Utility")` — Build Light Maps and optionally the reflection captures. @param	Quality	One of the enum LightingBuildQuality value. Default is Quality_Production. @param	bWithReflectionCaptures	Build the related reflection captures after building the light maps. @return	True if build was successful.
- L228 _public prototype_ `FEditorModeTools* GetLevelEditorModeManager();` — Gets the global level editor mode manager, if we have one. The mode manager is not created in commandlet environments, because modes inherently imply user interactions.
- L231 _public function_ `virtual void OnExecuteActorEditorContextAction(UWorld* InWorld, const EActorEditorContextAction& InType, class AActor* InActor = nullptr) override`
- L232 _public function_ `virtual void CaptureActorEditorContextState(UWorld* InWorld, UActorEditorContextStateCollection* InStateCollection) const override`
- L233 _public function_ `virtual void RestoreActorEditorContextState(UWorld* InWorld, const UActorEditorContextStateCollection* InStateCollection) override`
- L234 _public prototype_ `virtual bool GetActorEditorContextDisplayInfo(UWorld* InWorld, FActorEditorContextClientDisplayInfo& OutDiplayInfo) const override;`
- L235 _public function_ `virtual bool CanResetContext(UWorld* InWorld) const override`
- L236 _public prototype_ `virtual TSharedRef<SWidget> GetActorEditorContextWidget(UWorld* InWorld) const override;`
- L237 _public function_ `virtual FOnActorEditorContextClientChanged& GetOnActorEditorContextClientChanged() override`
- L242 _public member_ `FOnLevelEditorPreSaveWorld OnPreSaveWorld;` — `UPROPERTY(BlueprintAssignable, Category = "Editor Scripting | Level Utility")` — Expose PreSaveWorld to blueprints
- L245 _public member_ `FOnLevelEditorPostSaveWorld OnPostSaveWorld;` — `UPROPERTY(BlueprintAssignable, Category = "Editor Scripting | Level Utility")` — Expose PostSaveWorld to blueprints
- L249 _public member_ `FOnLevelEditorEditorCameraMoved OnEditorCameraMoved;` — `UPROPERTY(BlueprintAssignable, Category = "Editor Scripting | Level Utility")` — Expose EditorCameraMoved to blueprints
- L253 _public member_ `FOnLevelEditorMapChanged OnMapChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Editor Scripting | Level Utility")` — Expose MapChanged to blueprints. Note: This executes too early for some editor scripting, consider using OnMapOpened if this doesn't work for you.
- L257 _public member_ `FOnLevelEditorMapOpened OnMapOpened;` — `UPROPERTY(BlueprintAssignable, Category = "Editor Scripting | Level Utility")` — Expose MapOpened to blueprints
- L262 _private prototype_ `void OnLevelAddedOrRemoved(ULevel* InLevel, UWorld* InWorld);` — Called when a Level is added to a world or remove from a world
- L265 _private prototype_ `void OnCurrentLevelChanged(ULevel* InNewLevel, ULevel* InOldLevel, UWorld* InWorld);` — Called when the current level changes on a world
- L268 _private member_ `FOnActorEditorContextClientChanged ActorEditorContextClientChanged;` — Delegate used to notify changes to ActorEditorContextSubsystem
- L271 _private prototype_ `void HandleOnPreSaveWorldWithContext(class UWorld* World, FObjectPreSaveContext ObjectSaveContext);` — Called Pre SaveWorld
- L273 _private prototype_ `void HandleOnPostSaveWorldWithContext(class UWorld* World, FObjectPostSaveContext ObjectSaveContext);` — Called Post SaveWorld
- L276 _private prototype_ `void HandleOnEditorCameraMoved(const FVector& Location, const FRotator& Rotation, ELevelViewportType ViewportType, int32 ViewIndex);` — Called on Camera Movement
- L279 _private prototype_ `void HandleOnMapChanged(uint32 MapChangeFlags);` — Called on Map Change
- L281 _private prototype_ `void HandleOnMapOpened(const FString& Filename, bool bAsTemplate);` — Called on Map Open

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEVELEDITOR_API`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelEditorPreSaveWorld, int32, SaveFlags, class UWorld*, World);` — Delegate type for pre save world events ( uint32 SaveFlags, UWorld* World )
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelEditorPreSaveWorld, int32, SaveFlags, class UWorld*, World);` — Delegate type for pre save world events ( uint32 SaveFlags, UWorld* World )
- L23 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLevelEditorPostSaveWorld, int32, SaveFlags, class UWorld*, World, bool, bSuccess);` — Delegate type for post save world events ( uint32 SaveFlags, UWorld* World, bool bSuccess )
- L23 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnLevelEditorPostSaveWorld, int32, SaveFlags, class UWorld*, World, bool, bSuccess);` — Delegate type for post save world events ( uint32 SaveFlags, UWorld* World, bool bSuccess )
- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLevelEditorEditorCameraMoved, const FVector&, Location, const FRotator&, Rotation, ELevelViewportType, ViewportType, int32, ViewIndex);` — Delegate type for editor camera movement
- L26 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnLevelEditorEditorCameraMoved, const FVector&, Location, const FRotator&, Rotation, ELevelViewportType, ViewportType, int32, ViewIndex);` — Delegate type for editor camera movement
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelEditorMapChanged, int32, MapChangeEventFlags);` — Delegate type for map change events ( Params: uint32 MapChangeFlags (MapChangeEventFlags) )
- L29 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelEditorMapChanged, int32, MapChangeEventFlags);` — Delegate type for map change events ( Params: uint32 MapChangeFlags (MapChangeEventFlags) )
- L31 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelEditorMapOpened, const FString&, Filename, bool, bAsTemplate);` — Delegate type for triggering when a map is opened
- L31 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelEditorMapOpened, const FString&, Filename, bool, bAsTemplate);` — Delegate type for triggering when a map is opened

### `Source/Editor/LevelEditor/Public/LevelViewportActions.h` (Public)


#### class `FLevelViewportCommands`  
`class FLevelViewportCommands : public TCommands<FLevelViewportCommands>`  
_L43-244_
- inherits: `TCommands<FLevelViewportCommands>`
- desc: Class containing commands for level viewport actions
- L48 _public function_ `FLevelViewportCommands() : TCommands<FLevelViewportCommands> ( TEXT("LevelViewport"),`
- L60 _public prototype_ `FLevelViewportCommands(const FLevelViewportCommands&) = default;`
- L61 _public prototype_ `FLevelViewportCommands(FLevelViewportCommands&&) = default;`
- L62 _public prototype_ `FLevelViewportCommands& operator=(const FLevelViewportCommands&) = default;`
- L63 _public prototype_ `FLevelViewportCommands& operator=(FLevelViewportCommands&&) = default;`
- L66 _public prototype_ `virtual ~FLevelViewportCommands();`
- L86 _public member_ `TSharedPtr< FUICommandInfo > AdvancedSettings;` — Opens the advanced viewport settings
- L89 _public member_ `TSharedPtr< FUICommandInfo > PlaySettings;` — Opens the play settings for PIE
- L92 _public member_ `TSharedPtr< FUICommandInfo > ToggleGameView;` — Toggles game preview in the viewport
- L95 _public member_ `TSharedPtr< FUICommandInfo > ToggleImmersive;` — Toggles immersive mode in the viewport
- L98 _public member_ `TSharedPtr< FUICommandInfo > ToggleSidebarAllTabs;` — Toggles moving all tabs except the viewport to a sidebar or removing them from a sidebar
- L101 _public member_ `TSharedPtr< FUICommandInfo > ToggleMaximize;` — Toggles maximize mode in the viewport
- L104 _public member_ `TArray< TSharedPtr< FUICommandInfo > > CreateCameras;` — Creates a subclass of ACameraActor at current perspective viewport position
- L107 _public member_ `TSharedPtr< FUICommandInfo > HighResScreenshot;` — Opens the control panel for high resolution screenshots
- L110 _public member_ `TSharedPtr< FUICommandInfo > UseDefaultShowFlags;` — Reset all show flags to default
- L113 _public member_ `TSharedPtr< FUICommandInfo > ToggleCinematicPreview;` — Allows this viewport to be used for previewing cinematic animations
- L116 _public member_ `TSharedPtr< FUICommandInfo > ToggleAllowConstrainedAspectRatioInPreview;` — Allows this viewport to have a Constrained Aspect Ratio in Preview
- L119 _public member_ `TSharedPtr< FUICommandInfo > ToggleFlipConstrainedAspectRatioInPreview;` — Allows this viewport to flip the Constrained Aspect Ratio in Preview
- L122 _public member_ `TSharedPtr< FUICommandInfo > FindInLevelScriptBlueprint;` — Finds instances of selected object in level script.
- L125 _public member_ `TSharedPtr< FUICommandInfo > ShowAllVolumes;` — Shows all volume classes
- L128 _public member_ `TSharedPtr< FUICommandInfo > HideAllVolumes;` — Hides all volume classes
- L131 _public member_ `TArray< FShowMenuCommand > ShowVolumeCommands;` — List of commands for showing volume classes and their localized names.  One for each command
- L134 _public member_ `TSharedPtr< FUICommandInfo > ShowAllLayers;` — Shows all layers
- L137 _public member_ `TSharedPtr< FUICommandInfo > HideAllLayers;` — Hides all layers
- L140 _public member_ `TSharedPtr< FUICommandInfo > ShowAllDataLayers;` — Shows all DataLayers
- L143 _public member_ `TSharedPtr< FUICommandInfo > HideAllDataLayers;` — Hides all DataLayers
- L146 _public member_ `TSharedPtr< FUICommandInfo > ShowAllSprites;` — Shows all sprite categories
- L149 _public member_ `TSharedPtr< FUICommandInfo > HideAllSprites;` — Hides all sprite categories
- L152 _public member_ `TArray< FShowMenuCommand > ShowSpriteCommands;` — List of commands for showing sprite categories and their localized names.  One for each command
- L155 _public member_ `TSharedPtr< FUICommandInfo > HideAllStats;` — Hides all Stats categories
- L158 _public member_ `TMap< FString, TArray< FShowMenuCommand > > ShowStatCatCommands;` — A map of stat categories and the commands that belong in them
- L161 _public member_ `TSharedPtr< FUICommandInfo > ApplyMaterialToActor;` — Applys a material to an actor
- L163 _public member_ `TSharedPtr< FUICommandInfo > FocusViewportToSelectedActors;`
- L166 _public member_ `TSharedPtr< FUICommandInfo > EnableEditorShortcutsInPIE;` — Enable editor shortcuts when PIE is active
- L171 _public member_ `TArray< TSharedPtr< FUICommandInfo > > JumpToBookmarkCommands;` — Bookmarks
- L172 _public member_ `TArray< TSharedPtr< FUICommandInfo > > SetBookmarkCommands;`
- L173 _public member_ `TArray< TSharedPtr< FUICommandInfo > > ClearBookmarkCommands;`
- L174 _public member_ `TSharedPtr< FUICommandInfo > CompactBookmarks;`
- L177 _public member_ `TSharedPtr< FUICommandInfo > ClearAllBookMarks;` — `UE_DEPRECATED(4.21, "Please use the version of the member with corrected spelling (ClearAllBookmarks).")`
- L179 _public member_ `TSharedPtr< FUICommandInfo > ClearAllBookmarks;`
- L182 _public member_ `TSharedPtr< FUICommandInfo > SelectPilotedActor;` — Actor pilot commands
- L183 _public member_ `TSharedPtr< FUICommandInfo > EjectActorPilot;`
- L184 _public member_ `TSharedPtr< FUICommandInfo > PilotSelectedActor;`
- L187 _public member_ `TSharedPtr< FUICommandInfo > ToggleActorPilotCameraView;` — Toggles showing the exact camera view when locking a viewport to a camera
- L190 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_OnePane;` — Viewport pane configurations
- L191 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_TwoPanesH;`
- L192 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_TwoPanesV;`
- L193 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_ThreePanesLeft;`
- L194 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_ThreePanesRight;`
- L195 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_ThreePanesTop;`
- L196 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_ThreePanesBottom;`
- L197 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_FourPanesLeft;`
- L198 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_FourPanesRight;`
- L199 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_FourPanesTop;`
- L200 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_FourPanesBottom;`
- L201 _public member_ `TSharedPtr< FUICommandInfo > ViewportConfig_FourPanes2x2;`
- L203 _public member_ `TSharedPtr< FUICommandInfo > SetDefaultViewportType;`
- L205 _public member_ `TSharedPtr< FUICommandInfo > ToggleViewportToolbar;`
- L207 _public member_ `TSharedPtr< FUICommandInfo > EnablePreviewMesh;`
- L208 _public member_ `TSharedPtr< FUICommandInfo > CyclePreviewMesh;`
- L211 _public prototype_ `DECLARE_EVENT_TwoParams(FLevelViewportCommands, FOnNewStatCommandAdded, const TSharedPtr<FUICommandInfo>, const FString&);` — Delegate we fire every time a new stat has been had a command added
- L212 _public member_ `static FOnNewStatCommandAdded NewStatCommandDelegate;`
- L216 _public prototype_ `virtual void RegisterCommands() override;` — Registers our commands with the binding system
- L219 _public prototype_ `void RegisterShowVolumeCommands();` — Registers our commands with the binding system for showing volumes.
- L222 _public prototype_ `void RegisterShowSpriteCommands();` — Registers our commands with the binding system for showing sprites.
- L227 _private prototype_ `void HandleNewStatGroup(const TArray<FStatNameAndInfo>& NameAndInfos);` — Registers additional commands as they are loaded
- L228 _private prototype_ `void HandleNewStat(const FName& InStatName, const FName& InStatCategory, const FText& InStatDescription);`
- L229 _private prototype_ `int32 FindStatIndex(const TArray< FShowMenuCommand >* ShowStatCommands, const FString& InCommandName) const;`
- L235 _private function_ `void Dummy()` — Dummy function that's never used. Used to hide deprecation warnings due to auto generated methods.

#### struct `FLevelViewportCommands::FShowMenuCommand`  
`struct FShowMenuCommand`  
_L68-83_
- L70 _public member_ `TSharedPtr<FUICommandInfo> ShowMenuItem;`
- L71 _public member_ `FText LabelOverride;`
- L73 _public function_ `FShowMenuCommand( TSharedPtr<FUICommandInfo> InShowMenuItem, const FText& InLabelOverride ) : ShowMenuItem( InShowMenuItem ) , LabelOverride( InLabelOverride )`
- L79 _public function_ `FShowMenuCommand( TSharedPtr<FUICommandInfo> InShowMenuItem ) : ShowMenuItem( InShowMenuItem )`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace LevelViewportConfigurationNames`
- L24 _variable_ `static FName TwoPanesHoriz("Two` (scope `LevelViewportConfigurationNames`)
- L25 _variable_ `static FName TwoPanesVert("Two` (scope `LevelViewportConfigurationNames`)
- L26 _variable_ `static FName ThreePanesLeft("Thr` (scope `LevelViewportConfigurationNames`)
- L27 _variable_ `static FName ThreePanesRight("Thr` (scope `LevelViewportConfigurationNames`)
- L28 _variable_ `static FName ThreePanesTop("Thr` (scope `LevelViewportConfigurationNames`)
- L29 _variable_ `static FName ThreePanesBottom("Thr` (scope `LevelViewportConfigurationNames`)
- L30 _variable_ `static FName FourPanesLeft("Fou` (scope `LevelViewportConfigurationNames`)
- L31 _variable_ `static FName FourPanesRight("Fou` (scope `LevelViewportConfigurationNames`)
- L32 _variable_ `static FName FourPanesTop("Fou` (scope `LevelViewportConfigurationNames`)
- L33 _variable_ `static FName FourPanesBottom("Fou` (scope `LevelViewportConfigurationNames`)
- L34 _variable_ `static FName FourPanes2x2("Fou` (scope `LevelViewportConfigurationNames`)
- L35 _variable_ `static FName OnePane("One` (scope `LevelViewportConfigurationNames`)
- L211 _delegate_ `DECLARE_EVENT_TwoParams(FLevelViewportCommands, FOnNewStatCommandAdded, const TSharedPtr<FUICommandInfo>, const FString&);` — Delegate we fire every time a new stat has been had a command added

### `Source/Editor/LevelEditor/Public/LevelViewportLayout.h` (Public)


#### class `ILevelViewportLayoutEntity`  
`class ILevelViewportLayoutEntity : public IEditorViewportLayoutEntity`  
_L28-45_
- inherits: `IEditorViewportLayoutEntity`
- desc: Interface that defines an entity within a viewport layout
- L32 _public prototype_ `virtual ~ILevelViewportLayoutEntity() = default;` — Virtual destruction
- L35 _public function_ `virtual TSharedPtr<SLevelViewport> AsLevelViewport() const` — Optionally return this entity as an SLevelViewport. Legacy function for interop with code that used to deal directly with SLevelViewports
- L38 _public prototype_ `virtual FLevelEditorViewportClient& GetLevelViewportClient() const = 0;` — Get this viewport's level editor viewport client
- L41 _public prototype_ `virtual bool IsPlayInEditorViewportActive() const = 0;` — Check if this entity has an active play in editor viewport
- L44 _public prototype_ `virtual void RegisterGameViewportIfPIE() = 0;` — Register this viewport layout entity as a game viewport, if it's currently PIE-ing

#### class `FLevelViewportLayout`  
`class FLevelViewportLayout : public FAssetEditorViewportLayout`  
_L51-276_
- inherits: `FAssetEditorViewportLayout`
- desc: Base class for level viewport layout configurations Handles maximizing and restoring well as visibility of specific viewports.
- L57 _public prototype_ `FLevelViewportLayout();` — Constructor
- L62 _public prototype_ `virtual ~FLevelViewportLayout();` — Destructor
- L72 _public prototype_ `virtual TSharedRef<SWidget> BuildViewportLayout(TSharedPtr<SDockTab> InParentDockTab, TSharedPtr<FEditorViewportTabContent> InParentTab, const FString& LayoutString) override;` — Builds a viewport layout and returns the widget containing the layout @param InParentDockTab		The parent dock tab widget of this viewport configuration @param InParentTab			The parent tab object @param LayoutString			The layout string loaded from file to custom build the layout with @param InParentLevelEditor	Optional level editor parent to use for new viewports
- L74 _public prototype_ `virtual TSharedRef<SWidget> FactoryViewport(FName InTypeName, const FAssetEditorViewportConstructionArgs& ConstructionArgs) override;`
- L84 _public prototype_ `void RequestMaximizeViewport( FName ViewportToMaximize, const bool bWantMaximize, const bool bWantImmersive, const bool bAllowAnimation = true );` — Makes a request to maximize a specific viewport and hide the others in this layout @param	ViewportToMaximize	The viewport that should be maximized @param	bWantMaximize		True to maximize or false to "restore" @param	bWantImmersive		True to perform an "immersive" maximize, which transitions the viewport to fill the entire application window @param	bAllowAnimation		True if an animated transition should be used
- L89 _public prototype_ `virtual bool IsVisible() const override;` — @return true if this layout is visible.  It is not visible if its parent tab is not active
- L98 _public prototype_ `bool IsLevelViewportVisible( FName InViewport ) const;` — Checks to see the specified level viewport is visible in this layout A viewport is visible in a layout if the layout is visible and the viewport is the maximized viewport or there is no maximized viewport @param InViewport	The viewport within this layout that should be checked @return true if the viewport is visible.
- L105 _public function_ `bool IsMaximizeSupported() const` — Checks to see if the specified level viewport supports maximizing one pane @return true if the viewport supports maximizing
- L110 _public function_ `bool IsMaximized() const` — @return true if any viewport is maximized.
- L118 _public prototype_ `bool IsViewportMaximized( FName InViewport ) const;` — Checks to see if the specified level viewport is maximized @param InViewport	The viewport to check @return true if the viewport is maximized, false otherwise
- L126 _public prototype_ `bool IsViewportImmersive( FName InViewport ) const;` — Checks to see if the specified level viewport is in immersive mode @param InViewport	The viewport to check @return true if the viewport is immersive, false otherwise
- L132 _public prototype_ `virtual void Tick( float DeltaTime ) override;` — FTickableEditorObject interface
- L133 _public prototype_ `virtual bool IsTickable() const override;`
- L134 _public function_ `virtual TStatId GetStatId() const override`
- L138 _public function_ `void SetIsReplacement(bool bInIsReplacement)` — Tells this layout whether it was the intial layout or replaced an existing one when the user switched layouts
- L141 _public function_ `bool IsTransitioning() const` — Returns whether a viewport animation is currently taking place
- L143 _public prototype_ `virtual void LoadConfig(const FString& LayoutString) override;`
- L144 _public prototype_ `virtual void SaveConfig(const FString& LayoutString) const override;`
- L156 _protected prototype_ `void MaximizeViewport( FName ViewportToMaximize, const bool bWantMaximize, const bool bWantImmersive, const bool bAllowAnimation );` — Maximizes a specific viewport and hides the others in this layout @param	ViewportToMaximize	The viewport that should be maximized @param	bWantMaximize		True to maximize or false to "restore" @param	bWantImmersive		True to perform an "immersive" maximize, which transitions the viewport to fill the entire application window @param	bAllowAnimation		True if an animated transition should be used
- L164 _protected prototype_ `virtual EVisibility OnGetNonMaximizedVisibility() const override;` — Delegate called to get the visibility of the non-maximized viewports The non-maximized viewports are not visible if there is a maximized viewport on top of them @param EVisibility::Visible when visible, EVisibility::Collapsed otherwise
- L171 _protected prototype_ `FVector2D GetMaximizedViewportPositionOnCanvas() const;` — Returns the widget position for viewport transition animations @return	Viewport position on canvas
- L178 _protected prototype_ `FVector2D GetMaximizedViewportSizeOnCanvas() const;` — Returns the widget size for viewport transition animations @return	Viewport size on canvas
- L181 _protected prototype_ `void FinishMaximizeTransition();` — If a viewport animation is in progress, finishes that transition immediately
- L186 _protected prototype_ `void BeginThrottleForAnimatedResize();` — Begins a draw throttle for responsiveness when animating a viewports size
- L191 _protected prototype_ `void EndThrottleForAnimatedResize();` — Ends a draw throttle for responsiveness when animating a viewports size
- L195 _protected prototype_ `void InitCommonLayoutFromString(const FString& LayoutString, const FName PerspectiveViewportKey);` — Called in after factory of a new layout functions for derived types of layout to init values common to all types
- L198 _protected prototype_ `void SaveCommonLayoutString(const FString& SpecificLayoutString) const;` — Called in SaveConfig() functions for derived types of layout to save values common to all types
- L201 _protected member_ `bool bIsTransitioning;` — True if we've started an animation and are waiting for it to finish
- L204 _protected member_ `FCurveSequence MaximizeAnimation;` — Curve for animating from a "restored" state to a maximized state
- L207 _protected member_ `TWeakPtr< ILevelEditor > ParentLevelEditor;` — The optional parent level editor for this layout
- L210 _protected prototype_ `void TakeHighResScreenShot();` — Method for taking high res screen shots of viewports
- L213 _protected member_ `FName MaximizedViewport;` — The current maximized viewport if any
- L216 _protected member_ `bool bIsReplacement;` — True if the user selected this layout, false if it's the initial layout loaded
- L219 _protected member_ `bool bIsQueryingLayoutMetrics;` — Temporarily set to true while we are querying layout metrics and want all widgets to be visible
- L222 _protected member_ `bool bIsMaximizeSupported;` — True if the layout supports maximizing one viewport, false if the feature is disabled
- L225 _protected member_ `bool bIsMaximized;` — True if we're currently maximized
- L228 _protected member_ `bool bIsImmersive;` — True if we're currently in immersive mode
- L231 _protected member_ `bool bWasMaximized;` — True when transitioning from a maximized state
- L234 _protected member_ `bool bWasImmersive;` — True when transitioning from an immersive state
- L237 _protected member_ `FVector2D MaximizedViewportStartPosition;` — Window-space start position of the viewport that's currently being maximized
- L240 _protected member_ `FVector2D MaximizedViewportStartSize;` — Window-space start size of the viewport that's currently being maximized
- L243 _protected member_ `TSharedPtr< SWidget > ViewportsOverlayWidget;` — When maximizing viewports (or making them immersive), this stores the widget we create to wrap the viewport
- L246 _protected member_ `TSharedPtr< SWidget > ViewportReplacementWidget;` — Dummy widget that we'll inline-replace viewport widgets with while a view is maximized (or made immersive)
- L249 _protected member_ `TWeakPtr< SWindow > CachedOwnerWindow;` — Caches the window that our widgets are contained within
- L252 _protected member_ `FThrottleRequest ViewportResizeThrottleRequest;` — Viewport resize draw throttle request
- L275 _protected member_ `TArray<FMaximizeViewportCommand> DeferredMaximizeCommands;`

#### struct `FLevelViewportLayout::FMaximizeViewportCommand`  
`struct FMaximizeViewportCommand`  
_L259-274_
- desc: Maximize/immersive commands can be queued up at startup to be executed on the first tick. This is necessary, because these commands can't be executed until the viewport has a parent window, which might not be there upon viewport initialization
- L261 _public function_ `FMaximizeViewportCommand(FName InViewport, bool bInMaximize, bool bInImmersive, bool bInToggle=true, bool bInAllowAnimation=true) : Viewport(InViewport) , bMaximize(bInMaximize) , bImmersive(bInImmersive) , bToggle(bInToggle) , bAllowAnimation(bInAllowAnimation)`
- L269 _public member_ `FName Viewport;`
- L270 _public member_ `bool bMaximize;`
- L271 _public member_ `bool bImmersive;`
- L272 _public member_ `bool bToggle;`
- L273 _public member_ `bool bAllowAnimation;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/LevelViewportLayoutEntity.h` (Public)


#### class `FLevelViewportLayoutEntity`  
`class FLevelViewportLayoutEntity : public ILevelViewportLayoutEntity`  
_L14-35_
- inherits: `ILevelViewportLayoutEntity`
- L18 _public prototype_ `FLevelViewportLayoutEntity(TSharedPtr<SAssetEditorViewport> InLevelViewport);`
- L19 _public prototype_ `virtual TSharedRef<SWidget> AsWidget() const override;`
- L20 _public prototype_ `virtual TSharedPtr<SLevelViewport> AsLevelViewport() const override;`
- L22 _public prototype_ `bool IsPlayInEditorViewportActive() const;`
- L23 _public prototype_ `void RegisterGameViewportIfPIE();`
- L24 _public prototype_ `void SetKeyboardFocus();`
- L25 _public prototype_ `void OnLayoutDestroyed();`
- L26 _public prototype_ `void SaveConfig(const FString& ConfigSection);`
- L27 _public prototype_ `FLevelEditorViewportClient& GetLevelViewportClient() const;`
- L28 _public prototype_ `FName GetType() const;`
- L29 _public prototype_ `void TakeHighResScreenShot() const;`
- L34 _protected member_ `TSharedRef<SLevelViewport> LevelViewport;` — This entity's level viewport

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/LevelViewportTabContent.h` (Public)


#### class `FLevelViewportTabContent`  
`class FLevelViewportTabContent : public FEditorViewportTabContent`  
_L18-42_
- inherits: `FEditorViewportTabContent`
- desc: Represents the content in a viewport tab in the level editor. Each SDockTab holding viewports in the level editor contains and owns one of these.
- L21 _public prototype_ `~FLevelViewportTabContent();`
- L24 _public prototype_ `virtual void Initialize(AssetEditorViewportFactoryFunction Func, TSharedPtr<SDockTab> InParentTab, const FString& InLayoutString) override;` — Starts the tab content object and creates the initial layout based on the layout string
- L26 _public prototype_ `virtual void BindViewportLayoutCommands(FUICommandList& InOutCommandList, FName ViewportConfigKey) override;`
- L29 _protected prototype_ `virtual TSharedPtr<FEditorViewportLayout> FactoryViewportLayout(bool bIsSwitchingLayouts) override;`
- L30 _protected prototype_ `virtual FName GetLayoutTypeNameFromLayoutString() const override;`
- L32 _protected prototype_ `void OnLayoutStartChange(bool bSwitchingLayouts);`
- L33 _protected prototype_ `void OnLayoutChanged();`
- L36 _private prototype_ `void OnUIActionSetViewportConfiguration(FName InConfigurationName);`
- L37 _private prototype_ `FName GetViewportTypeWithinLayout(FName InConfigKey) const;`
- L38 _private prototype_ `void OnUIActionSetViewportTypeWithinLayout(FName InConfigKey, FName InLayoutType);`
- L39 _private prototype_ `bool IsViewportTypeWithinLayoutEqual(FName InConfigName, FName InLayoutType) const;`
- L40 _private prototype_ `bool IsViewportConfigurationChecked(FName InLayoutType) const;`
- L41 _private prototype_ `bool IsLayoutMaximized() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/LightmapResRatioAdjust.h` (Public)


#### class `FLightmapResRatioAdjustSettings`  
`class FLightmapResRatioAdjustSettings`  
_L16-94_
- desc: LightmapResRatioAdjust settings
- L33 _public function_ `static FLightmapResRatioAdjustSettings& Get()` — Static: Returns global lightmap resolution ratio adjust settings
- L38 _public prototype_ `bool ApplyRatioAdjustment();`
- L47 _public prototype_ `void AddRequiredLevels( AdjustLevels InLevelOptions, UWorld* World , TArray<ULevel*>& OutLevels );` — Add levels in a world to an array based on the LevelOptions setting @param InLevelOptions	Level options used to decided whether to add levels to the array @param InWorld		The world in which to get the levels from @param OutLevels		The array to add any levels to (The array is NOT reset by this function)
- L52 _protected member_ `static FLightmapResRatioAdjustSettings LightmapResRatioAdjustSettings;` — Static: Global lightmap resolution ratio adjust settings
- L57 _public function_ `FLightmapResRatioAdjustSettings() : Ratio(1.0f) , Min_StaticMeshes(32) , Max_StaticMeshes(256) , Min_BSPSurfaces(1) , Max_BSPSurfaces(512) , bStaticMeshes(false) , bBSPSurfaces(false) , LevelOptions(AdjustLevels::Current) , bSelectedObjectsOnly(false)` — Constructor
- L71 _public member_ `float Ratio;` — Ratio to apply
- L75 _public member_ `int32 Min_StaticMeshes;` — Static meshes
- L76 _public member_ `int32 Max_StaticMeshes;`
- L78 _public member_ `int32 Min_BSPSurfaces;` — BSP Surfaces
- L79 _public member_ `int32 Max_BSPSurfaces;`
- L82 _public member_ `bool bStaticMeshes;` — If true, apply to static meshes
- L84 _public member_ `bool bBSPSurfaces;` — If true, apply to BSP surfaces
- L87 _public member_ `uint8 PrimitiveFlags;` — The primitives to apply the adjustment to
- L90 _public member_ `AdjustLevels LevelOptions;` — The level(s) to check
- L93 _public member_ `bool bSelectedObjectsOnly;` — If true, then only do selected primitives in the level(s)

#### enum `FLightmapResRatioAdjustSettings::AdjustLevels`  
`enum AdjustLevels`  
_L22-30_
- desc: LightmapResRatioAdjust level options
- L25 _public enumerator_ `Current` — Current level only
- L27 _public enumerator_ `Selected` — Selected levels only
- L29 _public enumerator_ `AllLoaded` — All loaded levels

### `Source/Editor/LevelEditor/Public/SLevelViewport.h` (Public)


#### class `SLevelViewportToolBar`  
`class UE_DEPRECATED(5.7, "Use the UToolMenu \"LevelEditor.ViewportToolbar\" menu instead.") SLevelViewportToolBar : public SViewportToolBar`  
_L42-48_
- inherits: `SViewportToolBar`
- desc: This implementation is only present so that ULevelViewportToolBarContext & UViewportToolbarContext continues to have a valid public pointer.
- L44 _private function_ `SLATE_BEGIN_ARGS(SLevelViewportToolBar)`
- L45 _private function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs)`

#### class `SLevelViewport`  
`class SLevelViewport : public SAssetEditorViewport, public IAssetViewport`  
_L53-1109_
- inherits: `SAssetEditorViewport,IAssetViewport`
- desc: Encapsulates an SViewport and an SLevelViewportToolBar
- L56 _public function_ `SLATE_BEGIN_ARGS( SLevelViewport )`
- L59 _public prototype_ `SLATE_ARGUMENT( TWeakPtr<ILevelEditor>, ParentLevelEditor ) SLATE_ARGUMENT( TSharedPtr<FLevelEditorViewportClient>, LevelEditorViewportClient ) SLATE_END_ARGS() SLevelViewport();`
- L64 _public prototype_ `~SLevelViewport();`
- L70 _public prototype_ `void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InConstructionArgs);` — Constructs the viewport widget
- L75 _public prototype_ `void ConstructViewportOverlayContent();` — Constructs the widgets for the viewport overlay
- L80 _public prototype_ `void ConstructLevelEditorViewportClient(FLevelEditorViewportInstanceSettings& ViewportInstanceSettings);` — Constructs the level editor viewport client
- L85 _public prototype_ `virtual bool IsVisible() const override;` — @return true if the viewport is visible. false otherwise
- L88 _public prototype_ `bool IsInForegroundTab() const;` — @return true if this viewport is in a foregrounded tab
- L93 _public function_ `const FLevelEditorViewportClient& GetLevelViewportClient() const` — @return The editor client for this viewport
- L98 _public function_ `FLevelEditorViewportClient& GetLevelViewportClient()`
- L103 _public function_ `virtual FEditorViewportClient& GetAssetViewportClient() override`
- L111 _public prototype_ `void SetKeyboardFocusToThisViewport();` — Sets Slate keyboard focus to this viewport
- L116 _public function_ `const TSharedPtr<FUICommandList>& GetCommandList() const` — @return The list of commands on the viewport that are bound to delegates
- L119 _public prototype_ `void SaveConfig(const FString& ConfigName) const;` — Saves this viewport's config to ULevelEditorViewportSettings
- L122 _public prototype_ `virtual void StartPlayInEditorSession( UGameViewportClient* PlayClient, const bool bInSimulateInEditor ) override;` — IAssetViewport Interface
- L123 _public prototype_ `virtual void EndPlayInEditorSession() override;`
- L124 _public prototype_ `virtual void SwapViewportsForSimulateInEditor() override;`
- L125 _public prototype_ `virtual void SwapViewportsForPlayInEditor() override;`
- L126 _public prototype_ `virtual void OnSimulateSessionStarted() override;`
- L127 _public prototype_ `virtual void OnSimulateSessionFinished() override;`
- L128 _public prototype_ `virtual void RegisterGameViewportIfPIE() override;`
- L129 _public prototype_ `virtual bool HasPlayInEditorViewport() const override;`
- L130 _public prototype_ `virtual FViewport* GetActiveViewport() override;`
- L131 _public function_ `TSharedPtr<FSceneViewport> GetSharedActiveViewport() const override`
- L132 _public function_ `virtual TSharedRef< const SWidget> AsWidget() const override`
- L133 _public function_ `virtual TSharedRef< SWidget> AsWidget() override`
- L134 _public function_ `virtual TWeakPtr< SViewport > GetViewportWidget() override`
- L135 _public prototype_ `virtual void AddOverlayWidget( TSharedRef<SWidget> OverlaidWidget, int32 ZOrder=INDEX_NONE ) override;`
- L136 _public prototype_ `virtual void RemoveOverlayWidget( TSharedRef<SWidget> OverlaidWidget ) override;`
- L141 _public prototype_ `virtual void OnFocusViewportToSelection() override;` — SEditorViewport Interface
- L142 _public prototype_ `virtual EVisibility GetTransformToolbarVisibility() const override;`
- L143 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L144 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L145 _public prototype_ `virtual void ToggleInViewportContextMenu() override;`
- L147 _public prototype_ `virtual void HideInViewportContextMenu() override;`
- L148 _public prototype_ `virtual bool CanToggleInViewportContextMenu() override;`
- L150 _public prototype_ `static void EnableInViewportMenu();`
- L151 _public prototype_ `FMargin GetContextMenuPadding() const;`
- L156 _public prototype_ `FReply OnToggleMaximize();` — `UE_DEPRECATED(5.7, "Use OnTogleMaximizeMode() instead.")` — Called when the maximize command is executed
- L161 _public prototype_ `bool IsMaximized() const;` — @return true if this viewport is maximized, false otherwise
- L166 _public prototype_ `bool CanMaximize() const;` — @return true if this viewport can be maximized, false otherwise
- L173 _public prototype_ `void MakeMaximized(bool bWantMaximized, bool bAllowAnimation = true);` — Attempt to switch this viewport into a maximized or normal mode @param bWantMaximized Whether to witch to maximized or normal @param bAllowAnimation True to allow animation when transitioning, otherwise false
- L181 _public prototype_ `void MakeImmersive( const bool bWantImmersive, const bool bAllowAnimation ) override;` — Attempts to switch this viewport into immersive mode @param	bWantImmersive Whether to switch to immersive mode, or switch back to normal mode @param	bAllowAnimation	True to allow animation when transitioning, otherwise false
- L186 _public prototype_ `bool IsImmersive () const override;` — @return true if this viewport is in immersive mode, false otherwise
- L192 _public prototype_ `EVisibility GetCloseImmersiveButtonVisibility() const;` — Called to get the visibility of the viewport's 'Restore from Immersive' button. Returns EVisibility::Collapsed when not in immersive mode
- L198 _public prototype_ `EVisibility GetMaximizeToggleVisibility() const;` — Called to get the visibility of the viewport's maximize/minimize toggle button. Returns EVisibility::Collapsed when in immersive mode
- L203 _public prototype_ `bool IsPlayInEditorViewportActive() const;` — @return true if the active viewport is currently being used for play in editor
- L208 _public prototype_ `UGameViewportClient* GetPlayClient() const;` — @return The active play client, if any
- L215 _public prototype_ `void OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh=false);` — Called on all viewports, when actor selection changes. @param NewSelection	List of objects that are now selected
- L223 _public prototype_ `void OnElementSelectionChanged(const UTypedElementSelectionSet* SelectionSet, bool bForceRefresh);` — Called on all viewports, when element selection changes. @param SelectionSet  New selection @param bForceRefresh Force refresh
- L228 _public prototype_ `void ToggleGameView() override;` — Called when game view should be toggled
- L233 _public prototype_ `bool CanToggleGameView() const;` — @return true if we can toggle game view
- L238 _public prototype_ `bool IsInGameView() const override;` — @return true if we are in game view
- L245 _public prototype_ `void ToggleShowLayer( FName LayerName );` — Toggles layer visibility in this viewport @param LayerID					Index of the layer
- L252 _public prototype_ `bool IsLayerVisible( FName LayerName ) const;` — Checks if a layer is visible in this viewport @param LayerID					Index of the layer
- L259 _public prototype_ `void ToggleShowFoliageType(TWeakObjectPtr<class UFoliageType> FoliageType);` — Toggles foliage type visibility in this viewport @param FoliageType	Target foliage type
- L266 _public prototype_ `void ToggleAllFoliageTypes(bool bVisible);` — Toggles all foliage types visibility @param Visible	true if foliage types should be visible, false otherwise
- L273 _public prototype_ `bool IsFoliageTypeVisible(TWeakObjectPtr<class UFoliageType> FoliageType) const;` — Checks if a foliage type is visible in this viewport @param FoliageType	Target foliage type
- L277 _public prototype_ `void OnActorLockToggleFromMenu(AActor* Actor);` — Called to lock/unlock the actor from the viewport's context menu
- L280 _public prototype_ `void OnActorLockToggleFromMenu();` — Called to unlock the actor from the viewport's context menu
- L285 _public prototype_ `bool IsActorLocked(const TWeakObjectPtr<AActor> Actor) const;` — @return true if the actor is locked to the viewport
- L290 _public prototype_ `bool IsAnyActorLocked() const;` — @return true if an actor is locked to the viewport
- L295 _public prototype_ `bool IsSelectedActorLocked() const;` — @return true if the viewport is locked to selected actor
- L300 _public prototype_ `void ToggleActorPilotCameraView();` — Toggles enabling the exact camera view when locking a viewport to a camera
- L305 _public prototype_ `bool IsLockedCameraViewEnabled() const;` — Check whether locked camera view is enabled
- L312 _public prototype_ `void SetAllowsCinematicControl(bool bAllow);` — Sets whether the viewport should allow cinematic control @param Whether the viewport should allow cinematic control.
- L317 _public prototype_ `bool GetAllowsCinematicControl() const;` — @return Whether the viewport allows cinematic control.
- L322 _public prototype_ `static float GetActorLockSceneOutlinerColumnWidth();` — @return the fixed width that a column returned by CreateActorLockSceneOutlinerColumn expects to be
- L327 _public prototype_ `TSharedRef< class ISceneOutlinerColumn > CreateActorLockSceneOutlinerColumn( class ISceneOutliner& SceneOutliner ) const;` — @return a new custom column for a scene outliner that indicates whether each actor is locked to this viewport
- L330 _public prototype_ `void OnPreviewSelectedCamerasChange();` — Called when Preview Selected Cameras preference is changed.
- L338 _public function_ `void SetDeviceProfileString( const FString& ProfileName )` — `UE_DEPRECATED(5.7, "Device profiles & preview platforms are handled in the new ToolMenus toolbar.")` — Set the device profile name @param ProfileName The profile name to set
- L344 _public function_ `bool IsDeviceProfileStringSet( FString ProfileName ) const` — `UE_DEPRECATED(5.7, "Device profiles & preview platforms are handled in the new ToolMenus toolbar.")` — @return true if the in profile name matches the set profile name
- L350 _public function_ `FString GetDeviceProfileString( ) const` — `UE_DEPRECATED(5.7, "Device profiles & preview platforms are handled in the new ToolMenus toolbar.")` — @return the name of the selected device profile
- L353 _public function_ `TWeakPtr<ILevelEditor> GetParentLevelEditor() const` — Get the parent level editor for this viewport
- L356 _public prototype_ `virtual bool IsActorEditorContextVisible() const;` — @return whether the the actor editor context should be displayed for this viewport
- L359 _public prototype_ `FText GetCurrentScreenPercentageText() const;` — Called to get the screen percentage preview text
- L362 _public function_ `virtual EVisibility GetCurrentLevelTextVisibility() const` — `UE_DEPRECATED(5.1, "GetCurrentLevelTextVisibility not used anymore.")`
- L364 _public function_ `virtual EVisibility GetCurrentLevelButtonVisibility() const` — `UE_DEPRECATED(5.1, "GetCurrentLevelButtonVisibility not used anymore.")`
- L367 _public prototype_ `virtual EVisibility GetSelectedActorsCurrentLevelTextVisibility() const;` — @return The visibility of the current level text display
- L370 _public prototype_ `FText GetSelectedActorsCurrentLevelText(bool bDrawOnlyLabel) const;` — Called to get the text for the level the currently selected actor or actors are in.
- L373 _public prototype_ `EVisibility GetCurrentScreenPercentageVisibility() const;` — @return The visibility of the current screen percentage text display
- L377 _public function_ `virtual EVisibility GetViewportControlsVisibility() const` — @return The visibility of the viewport controls popup
- L382 _public prototype_ `virtual EVisibility GetToolBarVisibility() const;` — Called to get the visibility of the level viewport toolbar
- L390 _public prototype_ `void OnSetViewportConfiguration(FName ConfigurationName);` — `UE_DEPRECATED(5.1, "Moved to internal handling by FViewportTabContent. See FViewportTabContent::BindCommonViewportCommands")` — Sets the current layout on the parent tab that this viewport belongs to. @param ConfigurationName		The name of the layout (for the names in namespace LevelViewportConfigurationNames)
- L399 _public prototype_ `bool IsViewportConfigurationSet(FName ConfigurationName) const;` — `UE_DEPRECATED(5.1, "Moved to internal handling by FViewportTabContent. See FViewportTabContent::BindCommonViewportCommands")` — Returns whether the named layout is currently selected on the parent tab that this viewport belongs to. @param ConfigurationName		The name of the layout (for the names in namespace LevelViewportConfigurationNames) @return						True, if the named layout is currently active
- L403 _public prototype_ `FName GetViewportTypeWithinLayout() const;` — `UE_DEPRECATED(5.1, "Moved to internal handling by FViewportTabContent. See FViewportTabContent::BindCommonViewportCommands")` — Get this level viewport widget's type within its parent layout
- L407 _public prototype_ `void SetViewportTypeWithinLayout(FName InLayoutType);` — `UE_DEPRECATED(5.1, "Moved to internal handling by FViewportTabContent. See FViewportTabContent::BindCommonViewportCommands")` — Set this level viewport widget's type within its parent layout
- L411 _public prototype_ `void ToggleViewportTypeActivationWithinLayout(FName InLayoutType);` — `UE_DEPRECATED(5.1, "Moved to internal handling by FViewportTabContent. See FViewportTabContent::BindCommonViewportCommands")` — Activates the specified viewport type in the layout, if it's not already, or reverts to default if it is.
- L415 _public prototype_ `bool IsViewportTypeWithinLayoutEqual(FName InLayoutType);` — `UE_DEPRECATED(5.1, "Moved to internal handling by FViewportTabContent. See FViewportTabContent::BindCommonViewportCommands")` — Checks if the specified layout type matches our current viewport type.
- L418 _public prototype_ `bool IsActorAlwaysPreview(TWeakObjectPtr<AActor> Actor) const;` — For the specified actor, See if we're forcing a preview
- L421 _public prototype_ `void SetActorAlwaysPreview(TWeakObjectPtr<AActor> PreviewActor, bool bAlwaysPreview = true);` — For the specified actor, toggle Pinned/Unpinned of it's ActorPreview
- L424 _public prototype_ `void ToggleActorPreviewIsPinned(TWeakObjectPtr<AActor> PreviewActor);` — For the specified actor, toggle Pinned/Unpinned of it's ActorPreview
- L427 _public prototype_ `void ToggleActorPreviewIsPanelDetached(TWeakObjectPtr<AActor> PreviewActor);` — For the specified actor, toggle whether the panel is detached from it
- L430 _public prototype_ `bool IsActorPreviewPinned(TWeakObjectPtr<AActor> PreviewActor);` — See if the specified actor's ActorPreview is pinned or not
- L433 _public prototype_ `bool IsActorPreviewDetached(TWeakObjectPtr<AActor> PreviewActor);` — See if the specified actor's ActorPreview is detached from actor
- L436 _public prototype_ `void OnFloatingButtonClicked();` — Actions to perform whenever the viewports floating buttons are pressed
- L439 _public function_ `EVisibility GetToolbarVisibility() const` — `UE_DEPRECATED(5.6, "Call GetOptionsMenuVisibility() instead.")`
- L443 _public function_ `EVisibility GetOptionsMenuVisibility() const` — Get the visibility for viewport toolbar's options menu.
- L447 _public function_ `EVisibility GetFullToolbarVisibility() const` — Get the visibility for items considered to be part of the 'full' viewport toolbar
- L450 _public prototype_ `void RemoveAllPreviews(const bool bRemoveFromDesktopViewport = true);` — Unpin and close all actor preview windows
- L457 _public prototype_ `void OnSetBookmark( int32 BookmarkIndex );` — Called to set a bookmark @param BookmarkIndex	The index of the bookmark to set
- L464 _public prototype_ `bool OnHasBookmarkSet(int32 BookmarkIndex);` — Called to check if a bookmark is set @param BookmarkIndex	The index of the bookmark to check
- L471 _public prototype_ `void OnJumpToBookmark( int32 BookmarkIndex );` — Called to jump to a bookmark @param BookmarkIndex	The index of the bookmark to jump to
- L478 _public prototype_ `void OnClearBookmark( int32 BookmarkIndex );` — Called to clear a bookmark @param BookmarkIndex The index of the bookmark to clear
- L483 _public prototype_ `void OnClearAllBookmarks();` — Called to clear all bookmarks
- L488 _public prototype_ `void OnCompactBookmarks();` — Called to Compact Bookmarks.
- L495 _public function_ `FName GetConfigKey() const` — Returns the config key associated with this viewport. This is what is used when loading/saving per viewport settings. If a plugin extends a LevelViewport menu, they'll be able to identify it and match their settings accordingly
- L500 _public prototype_ `void ToggleViewportToolbarVisibility();` — Toggles the current viewport toolbar visibility.
- L505 _public prototype_ `bool IsViewportToolbarVisible() const;` — Whether the viewport toolbar is currently visible.
- L511 _protected prototype_ `virtual FName RegisterViewportToolbar() const;` — Registers the viewport toolbar UToolMenu and returns its name.
- L514 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;` — SEditorViewport interface
- L515 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L516 _protected prototype_ `TSharedRef<SWidget> BuildPIEViewportToolbar();`
- L518 _protected prototype_ `virtual void OnIncrementPositionGridSize() override;`
- L519 _protected prototype_ `virtual void OnDecrementPositionGridSize() override;`
- L520 _protected prototype_ `virtual void OnIncrementRotationGridSize() override;`
- L521 _protected prototype_ `virtual void OnDecrementRotationGridSize() override;`
- L522 _protected prototype_ `virtual const FSlateBrush* OnGetViewportBorderBrush() const override;`
- L523 _protected prototype_ `virtual FSlateColor OnGetViewportBorderColorAndOpacity() const override;`
- L524 _protected prototype_ `virtual EVisibility OnGetViewportContentVisibility() const override;`
- L525 _protected prototype_ `virtual EVisibility OnGetFocusedViewportIndicatorVisibility() const override;`
- L526 _protected prototype_ `virtual void BindCommands() override;`
- L529 _protected prototype_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override;` — SWidget Interface
- L530 _protected prototype_ `virtual void OnDragEnter( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L531 _protected prototype_ `virtual void OnDragLeave( const FDragDropEvent& DragDropEvent ) override;`
- L532 _protected prototype_ `virtual FReply OnDragOver( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L533 _protected prototype_ `virtual FReply OnDrop( const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent ) override;`
- L534 _protected prototype_ `virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override;`
- L539 _private member_ `bool bNeedToUpdatePreviews;` — Flag to know if we need to update the previews which is handled in the tick.
- L542 _private prototype_ `FLevelEditorViewportInstanceSettings LoadLegacyConfigFromIni(const FString& ConfigKey, const FLevelEditorViewportInstanceSettings& InDefaultSettings);` — Loads this viewport's config from the ini file
- L545 _private prototype_ `void HandleViewportSettingChanged(FName PropertyName);` — Called when a property is changed
- L550 _private prototype_ `int32 GetViewportToolbarIndex() const;` — Handles which viewport toolbar is active.
- L555 _private prototype_ `void OnAdvancedSettings();` — Called when the advanced settings should be opened.
- L560 _private prototype_ `void OnPlaySettings();` — Called when the play settings should be opened.
- L565 _private prototype_ `void OnToggleImmersive();` — Called when immersive mode is toggled by the user
- L568 _private prototype_ `void OnToggleSidebarTabs();` — Called when moving tabs in and out of a sidebar is activated by the user
- L573 _private prototype_ `bool CanToggleMaximizeMode() const;` — Called to determine whether the maximize mode of current viewport can be toggled
- L578 _private prototype_ `void OnToggleMaximizeMode();` — Called to toggle maximize mode of current viewport
- L581 _private prototype_ `void PreviewSelectedCameraActors(const bool bPreviewInDesktopViewport = true);` — Starts previewing any selected camera actors using live "PIP" sub-views
- L586 _private prototype_ `void OnCreateCameraActor(UClass *InClass);` — Called to create a cameraActor in the currently selected perspective viewport
- L591 _private prototype_ `void OnTakeHighResScreenshot();` — Called to bring up the screenshot UI
- L596 _private prototype_ `bool IsActiveLevelViewport() const;` — Returns whether this level viewport is the active level viewport
- L601 _private prototype_ `bool IsPerspectiveViewport() const;` — Called to check currently selected editor viewport is a perspective one
- L608 _private prototype_ `void OnToggleAllVolumeActors( bool bVisible );` — Toggles all volume classes visibility @param Visible					true if volumes should be visible, false otherwise
- L615 _private prototype_ `void ToggleShowVolumeClass( int32 VolumeID );` — Toggles volume classes visibility @param VolumeID					Index of the volume class
- L622 _private prototype_ `bool IsVolumeVisible( int32 VolumeID ) const;` — Checks if volume class is visible in this viewport @param VolumeID					Index of the volume class
- L629 _private prototype_ `void OnToggleAllLayers( bool bVisible );` — Toggles all layers visibility @param Visible					true if layers should be visible, false otherwise
- L636 _private prototype_ `void OnToggleAllSpriteCategories( bool bVisible );` — Toggles all sprite categories visibility @param Visible					true if sprites should be visible, false otherwise
- L643 _private prototype_ `void ToggleSpriteCategory( int32 CategoryID );` — Toggles sprite category visibility in this viewport @param CategoryID				Index of the category
- L650 _private prototype_ `bool IsSpriteCategoryVisible( int32 CategoryID ) const;` — Checks if sprite category is visible in this viewport @param CategoryID				Index of the category
- L657 _private prototype_ `void OnToggleAllStatCommands(bool bVisible);` — Toggles all Stat commands visibility @param Visible					true if Stats should be visible, false otherwise
- L662 _private prototype_ `void OnUseDefaultShowFlags(bool bUseSavedDefaults = false);` — Called when show flags for this viewport should be reset to default, or the saved settings
- L667 _private prototype_ `void OnToggleAllowCinematicPreview();` — Called to toggle allowing sequencer to use this viewport to preview in
- L672 _private prototype_ `bool AllowsCinematicPreview() const;` — @return true if this viewport allows cinematics to be previewed in it
- L675 _private prototype_ `void FindSelectedInLevelScript();` — Find currently selected actor in the level script.
- L678 _private prototype_ `bool CanFindSelectedInLevelScript() const;` — Can we find the currently selected actor in the level script.
- L681 _private prototype_ `void OnSelectLockedActor();` — Called to select the currently locked actor
- L686 _private prototype_ `bool CanExecuteSelectLockedActor() const;` — @return true if the currently locked actor is selectable
- L689 _private prototype_ `void OnActorUnlock();` — Called to clear the current actor lock
- L694 _private prototype_ `bool CanExecuteActorUnlock() const;` — @return true if clearing the current actor lock is a valid input
- L697 _private prototype_ `void OnActorLockSelected();` — Called to lock the viewport to the currently selected actor
- L702 _private prototype_ `bool CanExecuteActorLockSelected() const;` — @return true if clearing the setting the actor lock to the selected actor is a valid input
- L709 _private prototype_ `void RedrawViewport( bool bInvalidateHitProxies );` — Called when the viewport should be redrawn @param bInvalidateHitProxies	Whether or not to invalidate hit proxies
- L712 _private prototype_ `bool HandleDragObjects(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent);` — An internal handler for dagging dropable objects into the viewport.
- L718 _private prototype_ `bool HandlePlaceDraggedObjects(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent, bool bCreateDropPreview);` — An internal handler for dropping objects into the viewport. @param DragDropEvent		The drag event. @param bCreateDropPreview	If true, a drop preview actor will be spawned instead of a normal actor.
- L726 _private prototype_ `void GetAssetsFromDrag(const FDragDropEvent& DragDropEvent, TArray<FAssetData>& AssetDataArray);` — Tries to get assets from a drag and drop event. @param DragDropEvent		Event to get assets from. @param AssetDataArray	Asets will be added here.
- L732 _private prototype_ `void OnApplyMaterialToViewportTarget();` — Bound event Triggered via FLevelViewportCommands::ApplyMaterialToActor, attempts to apply a material selected in the content browser to an actor being hovered over in the Editor viewport.
- L739 _private prototype_ `void BindOptionCommands( FUICommandList& CommandList );` — Binds commands for our toolbar options menu @param CommandList	The list to bind commands to
- L746 _private prototype_ `void BindViewCommands( FUICommandList& CommandList );` — Binds commands for our toolbar view menu @param CommandList	The list to bind commands to
- L753 _private prototype_ `void BindShowCommands( FUICommandList& CommandList ) override;` — Binds commands for our toolbar show menu @param CommandList	The list to bind commands to
- L760 _private prototype_ `void BindDropCommands( FUICommandList& CommandList );` — Binds commands for our drag-drop context menu @param CommandList	The list to bind commands to
- L768 _private prototype_ `void BindStatCommand(const TSharedPtr<FUICommandInfo> InMenuItem, const FString& InCommandName);` — Binds commands for our stat menu, also used as a delegate listener @param InMenuItem		The menu item we need to bind @param InCommandName	The command used by the functions
- L774 _private prototype_ `void BindPIECommands( FUICommandList& OutCommandList );` — Binds commands for PIE-specific behavior @param OutCommandList	The list to bind commands to
- L779 _private prototype_ `void ResetPIEShowFlags();` — Resets the PIE show flags to default.
- L784 _private prototype_ `void TogglePIEShowFlag(FEngineShowFlags::EShowFlag Flag);` — Toggles a PIE show flag on or off.
- L789 _private prototype_ `bool IsPIEShowFlagEnabled(FEngineShowFlags::EShowFlag Flag) const;` — Returns whether a show flag is on in PIE.
- L794 _private prototype_ `void SetPIEViewMode(EViewModeIndex ViewMode);` — Sets the view mode on the PIE viewport.
- L799 _private prototype_ `bool IsPIEViewModeEnabled(EViewModeIndex ViewMode) const;` — Gets whether the view mode is enabled in the PIE Viewport
- L804 _private prototype_ `void RefreshPIEViewport();` — Refreshes the PIE viewport.
- L809 _private prototype_ `bool OnPIEViewportInputOverride(FInputKeyEventArgs& Input);` — A handler for processing input events before gameplay does.
- L814 _private prototype_ `TSharedRef< SWidget > BuildViewportDragDropContextMenu();` — Called to build the viewport context menu when the user is Drag Dropping from the Content Browser
- L819 _private prototype_ `void OnMapChanged( UWorld* World, EMapChangeType MapChangeType );` — Called when a map is changed (loaded,saved,new map, etc)
- L822 _private prototype_ `void OnLevelActorsRemoved(AActor* InActor);` — Called in response to an actor being deleted in the level
- L824 _private prototype_ `void OnEditorClose();`
- L827 _private prototype_ `FText GetLockedIconToolTip() const;` — Gets the locked icon tooltip text showing the meaning of the icon and the name of the locked actor
- L834 _private prototype_ `void PreviewActors( const TArray< AActor* >& ActorsToPreview, const bool bPreviewInDesktopViewport = true);` — Starts previewing the specified actors.  If the supplied list of actors is empty, turns off the preview. @param	ActorsToPreview		List of actors to draw previews for
- L837 _private prototype_ `void UpdateActorPreviewViewports();` — Called every frame to update any actor preview viewports we may have
- L844 _private prototype_ `void RemoveActorPreview( int32 PreviewIndex, AActor* Actor = nullptr, const bool bRemoveFromDesktopViewport = true);` — Removes a specified actor preview from the list @param PreviewIndex Array index of the preview to remove.
- L847 _private prototype_ `bool CanProduceActionForCommand(const TSharedRef<const FUICommandInfo>& Command) const;` — Returns true if this viewport is the active viewport and can process UI commands
- L850 _private prototype_ `void OnUndo();` — Called when undo is executed
- L853 _private prototype_ `void OnRedo();` — Called when undo is executed
- L856 _private prototype_ `bool CanExecuteUndo() const;` — @return Whether or not undo can be executed
- L859 _private prototype_ `bool CanExecuteRedo() const;` — @return Whether or not redo can be executed
- L862 _private prototype_ `EVisibility GetMouseCaptureLabelVisibility() const;` — @return Whether the mouse capture label is visible
- L865 _private prototype_ `FLinearColor GetMouseCaptureLabelColorAndOpacity() const;` — @return The current color & opacity for the mouse capture label
- L868 _private prototype_ `FText GetMouseCaptureLabelText() const;` — @return The current text for the mouse capture label
- L871 _private prototype_ `void ShowMouseCaptureLabel(ELabelAnchorMode AnchorMode);` — Show the mouse capture label with the specified vertical and horizontal alignment
- L874 _private prototype_ `TSharedRef<SWidget> BuildMouseCaptureWidget();` — Build the mouse capture label widget
- L877 _private prototype_ `void HideMouseCaptureLabel();` — Hide the mouse capture label
- L880 _private prototype_ `void ResetNewLevelViewFlags();` — Resets view flags when a new level is created or opened
- L883 _private prototype_ `FSceneViewport* GetGameSceneViewport() const;` — Gets the active scene viewport for the game
- L886 _private prototype_ `void TransitionToPIE(bool bIsSimulating);` — Handle any level viewport changes on entering PIE or simulate
- L889 _private prototype_ `void TransitionFromPIE(bool bIsSimulating);` — Handle any level viewport changes on leaving PIE or simulate
- L892 _private prototype_ `EStretch::Type OnGetScaleBoxStretch() const;` — Get the stretch type of the viewport
- L895 _private prototype_ `FVector2D GetSViewportSize() const;` — Get the SViewport size
- L898 _private prototype_ `void OnPerformanceSettingsChanged(UObject* Obj, struct FPropertyChangedEvent& ChangeEvent);` — Updates the real-time overrride applied to the viewport
- L901 _private prototype_ `void OnToggleEditorShortcutsInPIE();` — Called when the user wants to enable or disable editor shortcuts when PIE is active.
- L904 _private prototype_ `bool IsEditorShortcutsEnabledInPIE();` — Called to determine when editor shortcuts in PIE is active.
- L908 _private member_ `TWeakPtr<class FLevelViewportLayout> ParentLayout;` — Tab which this viewport is located in
- L911 _private member_ `TWeakPtr<ILevelEditor> ParentLevelEditor;` — Pointer to the parent level editor for this viewport
- L914 _private member_ `TSharedPtr<SHorizontalBox> ActorPreviewHorizontalBox;` — Viewport horizontal box used internally for drawing actor previews on top of the level viewport
- L917 _private member_ `TSharedPtr<class FSceneViewport> ActiveViewport;` — Active Slate viewport for rendering and I/O (Could be a pie viewport)
- L923 _private member_ `TSharedPtr<class FSceneViewport> InactiveViewport;` — Inactive Slate viewport for rendering and I/O If this is valid there is a pie viewport and this is the previous level viewport scene viewport
- L926 _private member_ `TSharedPtr<SDebugCanvas> EditorDebugCanvas;` — Debug canvas overlay for editor (non-PIE) mode; swapped out for SGameLayerManager during PIE
- L932 _private member_ `TSharedPtr<SWidget> InactiveViewportWidgetEditorContent;` — When in PIE this will contain the editor content for the viewport widget (toolbar). It was swapped out for GameUI content
- L937 _private member_ `FDelegateHandle PIEPreviewFeatureLevelChangedHandle;` — When PIE is active, the handle for the change feature level delegate
- L940 _private member_ `TSharedPtr<SLevelViewportToolBar> LevelViewportToolBar;`
- L944 _private member_ `TSharedPtr<FLevelEditorViewportClient> LevelViewportClient;` — Level viewport client
- L947 _private member_ `TWeakObjectPtr<UGameViewportClient> PlayClient;` — The GameViewportClient
- L950 _private member_ `TSharedPtr<FUICommandList> PIECommands;` — Commands specifically for PIE
- L953 _private member_ `const FSlateBrush* DebuggingBorder;` — The brush to use if this viewport is in debug mode
- L955 _private member_ `const FSlateBrush* BlackBackground;` — The brush to use for a black background
- L957 _private member_ `const FSlateBrush* StartingPlayInEditorBorder;` — The brush to use when transitioning into Play in Editor mode
- L959 _private member_ `const FSlateBrush* StartingSimulateBorder;` — The brush to use when transitioning into Simulate mode
- L961 _private member_ `const FSlateBrush* ReturningToEditorBorder;` — The brush to use when returning back to the editor from PIE or SIE mode
- L963 _private member_ `const FSlateBrush* NonMaximizedBorder;` — The brush to use when the viewport is not maximized
- L965 _private member_ `TArray<UObject*> DroppedObjects;` — Array of objects dropped during the OnDrop event
- L968 _private member_ `FIntPoint CachedOnDropLocalMousePos;` — Caching off of the DragDropEvent Local Mouse Position grabbed from OnDrop
- L971 _private member_ `TWeakPtr<class SWindow> HighResScreenshotDialog;` — Weak pointer to the highres screenshot dialog if it's open. Will become invalid if UI is closed whilst the viewport is open
- L974 _private member_ `TSharedPtr<class SCaptureRegionWidget> CaptureRegionWidget;` — Pointer to the capture region widget in the viewport overlay. Enabled by the high res screenshot UI when capture region selection is required
- L999 _private member_ `EViewTransition::Type ViewTransitionType;` — Type of transition we're currently playing
- L1002 _private member_ `FCurveSequence ViewTransitionAnim;` — Animation progress within current view transition
- L1005 _private member_ `bool bViewTransitionAnimPending;` — True if we want to kick off a transition animation but are waiting for the next tick to do so
- L1008 _private member_ `FName ConfigKey;` — The current viewport config key
- L1053 _private member_ `TArray< FViewportActorPreview > ActorPreviews;` — List of actor preview objects
- L1056 _private member_ `TSet<TWeakObjectPtr<AActor>> AlwaysPreviewActors;` — Storage for actors we always want to preview.  This comes from MU transactions .
- L1059 _private member_ `TSharedPtr<class SBorder> PIEOverlayBorder;` — The border in the SOverlay for the PIE mouse control label
- L1062 _private member_ `FCurveSequence PIEOverlayAnim;` — Separate curve to control fading out the PIE mouse control label
- L1065 _private member_ `bool bPIEHasFocus;` — Whether the PIE view has focus so we can track when to reshow the mouse control label
- L1068 _private member_ `bool bPIEContainsFocus;` — Whether the PIE view contains focus (even if not captured), if so we disable throttling.
- L1071 _private member_ `int32 UserAllowThrottlingValue;` — The users value for allowing throttling, we restore this value when we lose focus.
- L1074 _private member_ `bool bShowEditorToolbar = true;` — Whether to show the editor toolbar
- L1077 _private member_ `bool bShowPIEToolbar = true;` — Whether to show the in-PIE toolbar
- L1080 _private member_ `bool bShowImmersivePIEToolbar = false;` — Whether to show the in-PIE toolbar in immersive mode
- L1082 _private member_ `TSharedPtr<class SWidget> InViewportMenuWrapper;`
- L1083 _private member_ `bool bIsInViewportMenuShowing;`
- L1084 _private member_ `bool bIsInViewportMenuInitialized;`
- L1085 _private member_ `TSharedPtr<class SInViewportDetails> InViewportMenu;`
- L1086 _private member_ `static bool bInViewportMenuEnabled;`
- L1088 _private member_ `TSharedPtr<SWorldPartitionViewportWidget> WorldPartitionViewportWidget;`
- L1091 _private member_ `TSharedPtr<SActionableMessageViewportWidget> ActionableMessageViewportWidget;` — Viewport widget for warning messages
- L1097 _private member_ `FViewportCameraTransform CachedPerspectiveCameraTransform;` — Used to store last perspective camera transform before piloting (Actor Lock) Once piloting ends, this transform is re-applied to the camera.
- L1100 _protected prototype_ `void LockActorInternal(AActor* NewActorToLock);`
- L1103 _protected function_ `virtual void ExtendToolbarContext(FToolMenuContext& InToolMenuContext)` — Can be overriden by derived classes to add new context objects to the new toolbar
- L1106 _public prototype_ `static bool GetCameraInformationFromActor(AActor* Actor, FMinimalViewInfo& out_CameraInfo);`
- L1108 _public prototype_ `static bool CanGetCameraInformationFromActor(AActor* Actor);`

#### struct `SLevelViewport::EViewTransition`  
`struct EViewTransition`  
_L977-996_
- desc: Types of transition effects we support

#### enum `SLevelViewport::EViewTransition::Type`  
`enum Type`  
_L979-995_
- L982 _public enumerator_ `None = 0` — No transition
- L985 _public enumerator_ `FadingIn` — Fade in from black
- L988 _public enumerator_ `StartingPlayInEditor` — Entering PIE
- L991 _public enumerator_ `StartingSimulate` — Entering SIE
- L994 _public enumerator_ `ReturningToEditor` — Leaving either PIE or SIE

#### class `SLevelViewport::FViewportActorPreview`  
`class FViewportActorPreview`  
_L1013-1050_
- desc: Contains information about an actor being previewed within this viewport
- L1018 _public function_ `FViewportActorPreview() : bIsPinned(false) , bIsPanelDetached(false)`
- L1023 _public function_ `void ToggleIsPinned()`
- L1028 _public function_ `void ToggleIsPanelDetached()`
- L1034 _public member_ `TWeakObjectPtr< AActor > Actor;` — The Actor that is the center of attention.
- L1037 _public member_ `TSharedPtr< FLevelEditorViewportClient > LevelViewportClient;` — Level viewport client for our preview viewport
- L1040 _public member_ `TSharedPtr< FSceneViewport > SceneViewport;` — The scene viewport
- L1043 _public member_ `TSharedPtr< SActorPreview > PreviewWidget;` — Slate widget that represents this preview in the viewport
- L1046 _public member_ `bool bIsPinned;` — Whether or not this actor preview will remain on screen if the actor is deselected
- L1049 _public member_ `bool bIsPanelDetached;` — Whether this actor preview is displayed in a detached panel

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API LEVELEDITOR_API`

### `Source/Editor/LevelEditor/Public/ViewportTypeDefinition.h` (Public)


#### struct `FViewportTypeDefinition`  
`struct FViewportTypeDefinition`  
_L13-35_
- desc: Definition of a custom viewport
- L15 _public typedef_ `typedef TFunction<TSharedRef<ILevelViewportLayoutEntity>(const FAssetEditorViewportConstructionArgs&, TSharedPtr<ILevelEditor>)> FFactoryFunctionType;`
- L18 _public function_ `template<typename T> static FViewportTypeDefinition FromType(const TSharedPtr<FUICommandInfo>& ActivationCommand)`
- L25 _public function_ `FViewportTypeDefinition(const FFactoryFunctionType& InFactoryFunction, const TSharedPtr<FUICommandInfo>& InActivationCommand) : ActivationCommand(InActivationCommand) , FactoryFunction(InFactoryFunction)`
- L31 _public member_ `TSharedPtr<FUICommandInfo> ActivationCommand;` — A UI command for toggling activation this viewport
- L34 _public member_ `FFactoryFunctionType FactoryFunction;` — Function used to create a new instance of the viewport

#### Free symbols / members of external scopes

- L20 _function_ `return FViewportTypeDefinition([](const FAssetEditorViewportConstructionArgs& Args, TSharedPtr<ILevelEditor> InLevelEditor) -> TSharedRef<ILevelViewportLayoutEntity> { return MakeShareable(new T(Args, InLevelEditor)); }, ActivationCommand);` (scope `FViewportTypeDefinition::FromType`)
