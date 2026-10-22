# Plugins / AvalancheMaskEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor`
- headers: 9; symbols: 91
- symbol kinds: class=8, delegate=1, function=5, macro=1, member=23, namespace=5, prototype=46, variable=2
- PrivateDependencyModuleNames: ActorModifierCore, Avalanche, AvalancheEditorCore, AvalancheMask, AvalancheModifiers, AvalancheShapes, CoreUObject, DynamicMaterialEditor, EditorFramework, EditorSubsystem, Engine, GeometryMask, GeometryMaskEditor, InputCore, LevelEditor, MediaPlateEditor, Projects, Slate, SlateCore, ToolMenus, TypedElementFramework, TypedElementRuntime, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/AvaMaskEditorCommands.h` (Private)


#### class `FAvaMaskEditorCommands`  
`class FAvaMaskEditorCommands : public TCommands<FAvaMaskEditorCommands>`  
_L10-30_
- inherits: `TCommands<FAvaMaskEditorCommands>`
- L13 _public function_ `FAvaMaskEditorCommands() : TCommands<FAvaMaskEditorCommands>( TEXT("AvaMaskEditor"), LOCTEXT("MotionDesignMaskEditor", "Motion Design Masking"), NAME_None, FAvaMaskEditorStyle::Get().GetStyleSetName())`
- L22 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> ShowVisualizeMasks;`
- L26 _public member_ `TSharedPtr<FUICommandInfo> ToggleMaskMode;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowAllMasks;`
- L28 _public member_ `TSharedPtr<FUICommandInfo> ToggleIsolateMask;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> ToggleEnableMask;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define LOCTEXT_NAMESPACE "AvaMaskEditorCommands"`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/AvaMaskEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMaskEditor, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaMaskEditor, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/AvaMaskEditorMode.h` (Private)


#### class `UAvaMaskEditorMode`  
`class UAvaMaskEditorMode : public UEdMode`  
_L17-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdMode`
- L22 _public member_ `static const FEditorModeID EM_MotionDesignMaskEditorModeId;`
- L24 _public prototype_ `UAvaMaskEditorMode();`
- L25 _public prototype_ `virtual ~UAvaMaskEditorMode() override = default;`
- L28 _public prototype_ `virtual void Enter() override;`
- L29 _public prototype_ `virtual void Exit() override;`
- L30 _public prototype_ `virtual bool UsesToolkits() const override;`
- L31 _public prototype_ `virtual void CreateToolkit() override;`
- L32 _public prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L34 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L37 _public function_ `virtual bool IsOperationSupportedForCurrentAsset(EAssetOperation InOperation) const` — Only accept saving on current asset
- L41 _private prototype_ `void OnSelectionChanged(const UTypedElementSelectionSet* InSelectionSet);`
- L42 _private prototype_ `UGeometryMaskCanvas* GetCanvasReferencedByActor(const AActor* InActor);`
- L43 _private prototype_ `void UpdatePreviewWidget();`
- L46 _private member_ `FDelegateHandle OnPreActorSpawnedHandle;`
- L47 _private member_ `FDelegateHandle OnActorSpawnedHandle;`
- L50 _private member_ `TWeakObjectPtr<AActor> WeakLastSelectedActor = nullptr;`
- L51 _private member_ `TWeakObjectPtr<UTypedElementSelectionSet> WeakActorSelectionSet;`
- L52 _private member_ `TArray<TWeakObjectPtr<AActor>> WeakMaskWriterActors;`
- L54 _private member_ `TSharedPtr<SWidget> ViewportOverlayWidget;`
- L55 _private member_ `TSharedPtr<SGeometryMaskCanvasPreview> CanvasPreviewWidget;`
- L57 _private member_ `TWeakObjectPtr<UAvaMask2DBaseModifier> SelectedMaskModifier;`
- L58 _private member_ `TWeakObjectPtr<UGeometryMaskCanvas> SelectedMaskCanvas;`
- L61 _private member_ `FGeometryMaskCanvasId PreviewCanvasId;` — @note: these can differ from the selection when interacting
- L63 _private prototype_ `AActor* GetActorToParentTo() const;`
- L65 _private prototype_ `void OnActorSpawned(AActor* InActor);`
- L67 _private prototype_ `bool AddMaskToSelected(const TArray<AActor*>& InMaskingActors);`
- L69 _private prototype_ `UAvaMask2DBaseModifier* FindOrAddMaskModifier(AActor* InActor, const TSubclassOf<UAvaMask2DBaseModifier>& InMaskModifierType);`
- L73 _private function_ `MaskModifierType* FindOrAddMaskModifier(AActor* InActor)`
- L79 _private prototype_ `bool CanMaskSelected(AActor* InSelectedActor = nullptr);` — Uses USelection if SelectedActor not specified.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/AvaMaskEditorModule.h` (Private)


#### class `FAvalancheMaskEditorModule`  
`class FAvalancheMaskEditorModule : public IModuleInterface`  
_L13-34_
- inherits: `IModuleInterface`
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`
- L22 _public prototype_ `TSharedPtr<FUICommandList> GetCommandList() const;`
- L25 _private prototype_ `void RegisterMenus();`
- L26 _private prototype_ `void ToggleEditorMode();`
- L28 _private prototype_ `TSharedRef<SWidget> GetStatusBarWidgetMenuContent();`
- L29 _private prototype_ `FReply OnToggleMaskModeClicked();`
- L30 _private prototype_ `void OnGetMediaPlateMaterialAssetPaths(TArray<FName>& OutAssetPaths);`
- L33 _private member_ `TSharedPtr<FUICommandList> CommandList;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/AvaMaskEditorSVE.h` (Private)


#### class `FAvaMaskSceneViewExtension`  
`class FAvaMaskSceneViewExtension : public FWorldSceneViewExtension , public FGCObject`  
_L9-30_
- inherits: `FWorldSceneViewExtension,FGCObject`
- L14 _public prototype_ `FAvaMaskSceneViewExtension(const FAutoRegister& AutoRegister, UWorld* InWorld);`
- L17 _public prototype_ `virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override;`
- L18 _public prototype_ `virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;`
- L19 _public prototype_ `virtual bool IsActiveThisFrame_Internal(const FSceneViewExtensionContext& Context) const override;`
- L23 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L24 _public prototype_ `virtual FString GetReferencerName() const override;`
- L28 _private member_ `TSoftObjectPtr<UMaterialInterface> PostProcessMaterial;`
- L29 _private member_ `TObjectPtr<UMaterialInstanceDynamic> PostProcessMaterialMID;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/AvaMaskEditorStyle.h` (Private)


#### class `FAvaMaskEditorStyle`  
`class FAvaMaskEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaMaskEditorStyle& Get()`
- L16 _public prototype_ `FAvaMaskEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/AvaMaskEditorSubsystem.h` (Private)


#### class `UAvaMaskEditorWorldSubsystem`  
`class UAvaMaskEditorWorldSubsystem : public UWorldSubsystem`  
_L18-30_
- reflection: `UCLASS()`
- inherits: `UWorldSubsystem`
- L25 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L29 _private member_ `TSharedPtr<FAvaMaskSceneViewExtension> SceneViewExtension;`

#### class `UAvaMaskEditorSubsystem`  
`class UAvaMaskEditorSubsystem : public UEditorSubsystem`  
_L33-68_
- reflection: `UCLASS()`
- inherits: `UEditorSubsystem`
- L40 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L41 _public prototype_ `virtual void Deinitialize() override;`
- L45 _private prototype_ `void ShowVisualizeMasks();`
- L47 _private prototype_ `void ToggleEditorMode();`
- L48 _private prototype_ `bool IsEditorModeActive();`
- L50 _private prototype_ `void ToggleShowAllMasks();`
- L51 _private prototype_ `bool IsShowingAllMasks();`
- L53 _private prototype_ `void ToggleIsolateSelectedMask();`
- L54 _private prototype_ `bool IsIsolatingSelectedMask();`
- L56 _private prototype_ `void ToggleEnableSelectedMask();`
- L57 _private prototype_ `bool IsSelectedMaskEnabled();`
- L61 _private member_ `bool bIsShowingAllMasks = true;` — `UPROPERTY(Transient)`
- L64 _private member_ `bool bIsIsolatingSelectedMask = true;` — `UPROPERTY(Transient)`
- L67 _private member_ `bool bIsSelectedMaskEnabled = true;` — `UPROPERTY(Transient)`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace AvaMaskEditor` (scope `UE`)
- L12 _namespace_ `namespace Internal` (scope `UE::AvaMaskEditor`)
- L14 _variable_ `static FName ToolkitOverlayMenuName = TEXT("Ava` (scope `UE::AvaMaskEditor::Internal`)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Private/Details/AvaMask2DModifierDetails.h` (Private)


#### class `FAvaMask2DModifierDetails`  
`class FAvaMask2DModifierDetails : public IDetailCustomization`  
_L8-18_
- inherits: `IDetailCustomization`
- L12 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheMaskEditor/Public/IAvaMaskEditor.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace AvaMaskEditor` (scope `UE`)
- L9 _variable_ `const static FName MotionDesignMaskEditorModeName("Edi` (scope `UE::AvaMaskEditor`)
