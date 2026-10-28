# Plugins / AvalancheEditor

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor`
- headers: 48; symbols: 689
- symbol kinds: class=47, delegate=1, enum=3, enumerator=15, function=17, member=171, prototype=428, struct=4, typedef=3
- PrivateDependencyModuleNames: ActorModifier, ActorModifierCore, ActorModifierCoreEditor, AdvancedPreviewScene, AdvancedRenamer, AppFramework, ApplicationCore, AssetRegistry, AssetTools, AvalancheAttributeEditor, AvalancheComponentVisualizers, AvalancheCore, AvalancheEditorCore, AvalancheEffectors, AvalancheInteractiveTools, AvalancheLevelViewport, AvalancheMedia, AvalancheMediaEditor, AvalancheModifiers, AvalancheOutliner, AvalanchePropertyAnimator, AvalancheRemoteControlEditor, AvalancheSceneRig, AvalancheSceneRigEditor, AvalancheSceneTree, AvalancheSequence, AvalancheSequencer, AvalancheShapes, AvalancheTag, AvalancheText, AvalancheTransition, AvalancheTransitionEditor, AvalancheViewport, BlueprintGraph, CinematicCamera, ClonerEffector, CommonMenuExtensions, ContentBrowser, CustomDetailsView, DeveloperSettings, DynamicMaterial, DynamicMaterialEditor, EditorFramework, EditorWidgets, Engine, GeometryAlgorithms, GeometryCore, GraphEditor, InputCore, InteractiveToolsFramework, Kismet, KismetCompiler, Landscape, LevelEditor, LevelSequence, LevelSequenceEditor, MaterialEditor, MediaCompositing, MediaPlate, ModelingEditorUI, MovieScene, OperatorStackEditor, PlacementMode, Projects, PropertyAnimatorCore, PropertyEditor, RHI, RawMesh, RemoteControl, RemoteControlComponents, RemoteControlUI, RenderCore, SVGImporter, SVGImporterEditor, SceneOutliner, Sequencer, Slate, SlateCore, StateTreeEditorModule, StateTreeModule, StatusBar, SubobjectDataInterface, SubobjectEditor, Text3D, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UElibPNG, UMG, UMGEditor, UnrealEd, XmlParser, zlib
- PublicDependencyModuleNames: Avalanche, Core, CoreUObject, Engine

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AdvancedRenamer/AvaAdvancedRenamerExtension.h` (Private)


#### class `FAvaAdvancedRenamerExtension`  
`class FAvaAdvancedRenamerExtension : public FAvaEditorExtension`  
_L11-32_
- inherits: `FAvaEditorExtension`
- L14 _public prototype_ `UE_AVA_INHERITS(FAvaAdvancedRenamerExtension, FAvaEditorExtension);`
- L17 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L21 _private prototype_ `bool CanOpenAdvancedRenamerTool_SelectedActors() const;`
- L23 _private prototype_ `void OpenAdvancedRenamerTool_SelectedActors() const;`
- L25 _private prototype_ `bool CanOpenAdvancedRenamerTool_ClassActors() const;`
- L27 _private prototype_ `void OpenAdvancedRenamerTool_SharedClassActors() const;`
- L29 _private prototype_ `TArray<AActor*> GetSelectedActors() const;`
- L31 _private prototype_ `void OpenAdvancedRenamerTool(const TArray<AActor*>& InActors) const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorActorUtils.h` (Private)


#### struct `FAvaEditorActorUtils`  
`struct FAvaEditorActorUtils`  
_L12-30_
- L14 _public prototype_ `static void GetActorsToEdit(TArray<AActor*>& InOutSelectedActors);`
- L17 _public prototype_ `static void GetAttachedComponents(const USceneComponent* InParent, TSet<USceneComponent*>& OutAttachedComponents);` — Fills the OutAttachedComponents array with all the components attached to the given component within the same actor.
- L20 _public prototype_ `static void GetDirectlyAttachedActors(const USceneComponent* InParent, TSet<AActor*>& OutAttachedActors);` — Returns the actors directly attached to this component.
- L23 _public prototype_ `static void GetAllAttachedActors(const USceneComponent* InParent, TSet<AActor*>& OutAttachedActors);` — Returns all the actors attached directly or indirectly to this component.
- L26 _public prototype_ `static void GetDirectlyAttachedActors(const TSet<USceneComponent*>& InComponentList, TSet<AActor*>& OutAttachedActors);` — Returns all actors attached directly to the given components.
- L29 _public prototype_ `static void GetAllAttachedActors(const TSet<USceneComponent*>& InComponentList, TSet<AActor*>& OutAttachedActors);` — Returns all actors attached to these components directly or indirectly.

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorCommands.h` (Private)


#### class `FAvaEditorCommands`  
`class FAvaEditorCommands : public TCommands<FAvaEditorCommands>`  
_L7-106_
- inherits: `TCommands<FAvaEditorCommands>`
- L10 _public prototype_ `FAvaEditorCommands();`
- L12 _public prototype_ `virtual void RegisterCommands() override;`
- L14 _public prototype_ `void RegisterViewportCommands();`
- L15 _public prototype_ `void RegisterPivotCommands();`
- L16 _public prototype_ `void RegisterToolsCommands();`
- L17 _public prototype_ `void RegisterAdvancedRenamerCommands();`
- L18 _public prototype_ `void RegisterClonerEffectorCommands();`
- L21 _public member_ `TSharedPtr<FUICommandInfo> SwitchViewports;` — Switches between Camera "2D" viewport and 3D viewport.
- L22 _public member_ `TSharedPtr<FUICommandInfo> SetMotionDesignViewportType;`
- L25 _public member_ `TSharedPtr<FUICommandInfo> GroupActors;` — Groups the Selected Actors via a Null Actor.
- L26 _public member_ `TSharedPtr<FUICommandInfo> UngroupActors;`
- L29 _public member_ `TSharedPtr<FUICommandInfo> PivotTopLeftActor;` — Pivot
- L30 _public member_ `TSharedPtr<FUICommandInfo> PivotTopMiddleActor;`
- L31 _public member_ `TSharedPtr<FUICommandInfo> PivotTopRightActor;`
- L32 _public member_ `TSharedPtr<FUICommandInfo> PivotMiddleLeftActor;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> PivotCenterActor;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> PivotMiddleRightActor;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomLeftActor;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomMiddleActor;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomRightActor;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthFrontActor;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthMiddleActor;`
- L40 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthBackActor;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> PivotTopLeftActorAndChildren;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> PivotTopMiddleActorAndChildren;`
- L44 _public member_ `TSharedPtr<FUICommandInfo> PivotTopRightActorAndChildren;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> PivotMiddleLeftActorAndChildren;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> PivotCenterActorAndChildren;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> PivotMiddleRightActorAndChildren;`
- L48 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomLeftActorAndChildren;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomMiddleActorAndChildren;`
- L50 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomRightActorAndChildren;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthFrontActorAndChildren;`
- L52 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthMiddleActorAndChildren;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthBackActorAndChildren;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> PivotTopLeftSelection;`
- L56 _public member_ `TSharedPtr<FUICommandInfo> PivotTopMiddleSelection;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> PivotTopRightSelection;`
- L58 _public member_ `TSharedPtr<FUICommandInfo> PivotMiddleLeftSelection;`
- L59 _public member_ `TSharedPtr<FUICommandInfo> PivotCenterSelection;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> PivotMiddleRightSelection;`
- L61 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomLeftSelection;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomMiddleSelection;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> PivotBottomRightSelection;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthFrontSelection;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthMiddleSelection;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> PivotDepthBackSelection;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> StaticMeshToolsCategory;` — Tools
- L70 _public member_ `TSharedPtr<FUICommandInfo> CameraToolsCategory;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> LightsToolsCategory;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> CubeTool;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> SphereTool;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> CylinderTool;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> ConeTool;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> PlaneTool;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> CycloramaTool;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> MediaPlateTool;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> CameraTool;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> CineCameraTool;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> CameraRigCraneTool;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> CameraRigRailTool;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> CameraShakeSourceTool;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> AvaPostProcessVolumeTool;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> TickerTool;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> PointLightTool;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> DirectionalLightTool;`
- L92 _public member_ `TSharedPtr<FUICommandInfo> SpotLightTool;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> RectLightTool;`
- L94 _public member_ `TSharedPtr<FUICommandInfo> SkyLightTool;`
- L97 _public member_ `TSharedPtr<FUICommandInfo> OpenAdvancedRenamerTool_SelectedActors;` — Advanced Renamer
- L98 _public member_ `TSharedPtr<FUICommandInfo> OpenAdvancedRenamerTool_SharedClassActors;`
- L101 _public member_ `TSharedPtr<FUICommandInfo> DisableCloners;` — ClonerEffector
- L102 _public member_ `TSharedPtr<FUICommandInfo> EnableCloners;`
- L103 _public member_ `TSharedPtr<FUICommandInfo> DisableEffectors;`
- L104 _public member_ `TSharedPtr<FUICommandInfo> EnableEffectors;`
- L105 _public member_ `TSharedPtr<FUICommandInfo> CreateCloner;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorIntegration.h` (Private)


#### struct `FAvaLevelEditorIntegration`  
`struct FAvaLevelEditorIntegration`  
_L9-12_
- L11 _public prototype_ `static TSharedRef<IAvaEditor> BuildEditor();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorModule.h` (Private)


#### class `FAvaEditorModule`  
`class FAvaEditorModule : public IModuleInterface`  
_L21-52_
- inherits: `IModuleInterface`
- desc: Main Motion Design Editor Module
- L25 _public prototype_ `virtual void StartupModule() override;`
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L29 _public prototype_ `static FSlateIcon GetOutlinerShapeActorIcon(TSharedPtr<const FAvaOutlinerItem> InItem);`
- L31 _public prototype_ `static const TSet<TSubclassOf<AActor>>& DefaultSceneRigActorClasses();`
- L35 _private member_ `TSharedPtr<IAvaEditor> AvaLevelEditor;` — Motion Design Level Editor
- L37 _private prototype_ `void CreateAvaLevelEditor();`
- L39 _private prototype_ `void PostEngineInit();`
- L40 _private prototype_ `void PreExit();`
- L42 _private prototype_ `void RegisterAssetTools();`
- L43 _private prototype_ `void RegisterPropertyEditorCategories();`
- L45 _private prototype_ `void RegisterCustomLayouts();`
- L46 _private prototype_ `void UnregisterCustomLayouts();`
- L48 _private prototype_ `void RegisterLevelTemplates();`
- L51 _private member_ `FDelegateHandle OnKnownGathersCompleteHandle;` — Delegate handle to when asset registry is done scanning assets

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(AvaLog, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(AvaLog, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorSettings.h` (Private)


#### class `UAvaEditorSettings`  
`class UAvaEditorSettings : public UDeveloperSettings`  
_L19-77_
- reflection: `UCLASS(Config=EditorPerProjectUserSettings, meta = (DisplayName = "Editor"))`
- inherits: `UDeveloperSettings`
- desc: Motion Design Editor Settings
- L24 _public prototype_ `UAvaEditorSettings();`
- L26 _public prototype_ `virtual ~UAvaEditorSettings() override = default;`
- L28 _public prototype_ `static UAvaEditorSettings* Get();`
- L32 _public member_ `bool bEnableLevelContextSwitching = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Behavior")` — Whether to allow the Motion Design Interface to show the current selected level rather than fixed at the persistent level
- L36 _public member_ `bool bAutoIncludeAttachedActorsInEditActions = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Behavior")` — Whether to Automatically Include the Attached Actors when performing Edit Actions such as Cut, Copy, Duplicate.
- L40 _public member_ `bool bKeepRelativeTransformWhenGrouping = false;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Behavior")` — When Grouping Actors with a Null Actor, whether to keep the relative transform of these Actors
- L47 _public member_ `float CameraDistance = 500.0f;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Behavior")` — Distance from the camera that new actors are created via the toolbox or drag and drop. Also sets the distance from the origin that new Camera Preview Viewport cameras are created.
- L53 _public member_ `bool bAutoActivateMotionDesignViewport = true;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Behavior")` — Whether to automatically switch to the Motion Design viewport when the mode is activated or a Motion Design level is opened.
- L57 _public member_ `FAvaViewportQualitySettings DefaultViewportQualitySettings = FAvaViewportQualitySettings(true);` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Quality")` — Default viewport quality settings for all newly created Motion Design blueprints.
- L61 _public member_ `TMap<FName, FAvaViewportQualitySettings> ViewportQualityPresets_DEPRECATED;` — `UPROPERTY(Meta = (DeprecatedProperty, DeprecationMessage = "This property type has changed. Use the updated ViewportQualityPresets instead."))` — Viewport quality settings user presets.
- L65 _public member_ `TArray<FAvaViewportQualitySettingsPreset> ViewportQualitySettingsPresets;` — `UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Quality")` — Viewport quality settings user presets.
- L68 _public prototype_ `virtual void PostLoad() override;`
- L71 _public prototype_ `void OpenEditorSettingsWindow() const;`
- L74 _private prototype_ `void EnsureDefaultViewportQualityPresets();`
- L76 _private prototype_ `void MaintainViewportQualityPresetsIntegrity();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorStyle.h` (Private)


#### class `FAvaEditorStyle`  
`class FAvaEditorStyle final : public FSlateStyleSet`  
_L7-18_
- inherits: `FSlateStyleSet`
- L10 _public function_ `static FAvaEditorStyle& Get()`
- L16 _public prototype_ `FAvaEditorStyle();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/AvaEditorViewportUtils.h` (Private)


#### struct `FAvaEditorViewportUtils`  
`struct FAvaEditorViewportUtils`  
_L10-15_
- L12 _public prototype_ `static bool MeshSizeToPixelSize(const TSharedRef<IAvaViewportClient>& InViewportClient, double InMeshSize, double& OutPixelSize);`
- L14 _public prototype_ `static bool PixelSizeToMeshSize(const TSharedRef<IAvaViewportClient>& InViewportClient, double InPixelSize, double& OutMeshSize);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/ClonerEffector/AvaClonerEffectorExtension.h` (Private)


#### class `FAvaClonerEffectorExtension`  
`class FAvaClonerEffectorExtension : public FAvaEditorExtension`  
_L12-31_
- inherits: `FAvaEditorExtension`
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaClonerEffectorExtension, FAvaEditorExtension);`
- L17 _public prototype_ `FAvaClonerEffectorExtension();`
- L20 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L24 _private prototype_ `TSet<AActor*> GetSelectedActors() const;`
- L26 _private prototype_ `void EnableEffectors(bool bInEnable) const;`
- L27 _private prototype_ `void EnableCloners(bool bInEnable) const;`
- L28 _private prototype_ `void CreateCloner() const;`
- L30 _private member_ `TSharedRef<FUICommandList> ClonerEffectorCommands;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/ComponentVisualizer/AvaComponentVisualizerExtension.h` (Private)


#### class `FAvaComponentVisualizerExtension`  
`class FAvaComponentVisualizerExtension : public FAvaEditorExtension`  
_L9-24_
- inherits: `FAvaEditorExtension`
- L12 _public prototype_ `UE_AVA_INHERITS(FAvaComponentVisualizerExtension, FAvaEditorExtension);`
- L17 _public prototype_ `virtual void Activate() override;`
- L18 _public prototype_ `virtual void Deactivate() override;`
- L19 _public prototype_ `virtual void NotifyOnSelectionChanged(const FAvaEditorSelection& InSelection) override;`
- L23 _protected prototype_ `void OnViewportSettingsChanged(const UAvaViewportSettings* InSettings, FName InSetting);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/AvaDetailsExtension.h` (Private)


#### class `FAvaDetailsExtension`  
`class FAvaDetailsExtension: public FAvaEditorExtension, public IAvaDetailsProvider, public IDetailKeyframeHandler`  
_L14-34_
- inherits: `FAvaEditorExtension,IAvaDetailsProvider,IDetailKeyframeHandler`
- L17 _public prototype_ `UE_AVA_INHERITS(FAvaDetailsExtension, FAvaEditorExtension, IAvaDetailsProvider, IDetailKeyframeHandler);`
- L20 _public prototype_ `virtual FEditorModeTools* GetDetailsModeTools() const override;`
- L21 _public prototype_ `virtual TSharedPtr<IDetailKeyframeHandler> GetDetailsKeyframeHandler() const override;`
- L25 _public prototype_ `virtual bool IsPropertyKeyingEnabled() const override;`
- L26 _public prototype_ `virtual bool IsPropertyKeyable(const UClass* InObjectClass, const IPropertyHandle& InPropertyHandle) const override;`
- L27 _public prototype_ `virtual void OnKeyPropertyClicked(const IPropertyHandle& InPropertyHandle) override;`
- L28 _public prototype_ `virtual bool IsPropertyAnimated(const IPropertyHandle& InPropertyHandle, UObject* InParentObject) const override;`
- L29 _public prototype_ `virtual EPropertyKeyedStatus GetPropertyKeyedStatus(const IPropertyHandle& PropertyHandle) const override;`
- L33 _private prototype_ `TSharedPtr<ISequencer> GetSequencer() const;`

#### Free symbols / members of external scopes

- L11 _prototype_ `UE_AVA_TYPE_EXTERNAL(IAvaDetailsProvider);`
- L12 _prototype_ `UE_AVA_TYPE_EXTERNAL(IDetailKeyframeHandler);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/Customizations/AvaCategoryHiderCustomization.h` (Private)


#### class `FAvaCategoryHiderCustomization`  
`class FAvaCategoryHiderCustomization : public IDetailCustomization`  
_L7-20_
- inherits: `IDetailCustomization`
- L10 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L15 _public prototype_ `virtual ~FAvaCategoryHiderCustomization() override = default;`
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L19 _public prototype_ `static void HideCategories(IDetailLayoutBuilder& DetailBuilder);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/Customizations/AvaMeshesDetailCustomization.h` (Private)


#### class `FAvaMeshesDetailCustomization`  
`class FAvaMeshesDetailCustomization : public IDetailCustomization`  
_L17-46_
- inherits: `IDetailCustomization`
- desc: Used to create the details materials meshes widget and export to StaticMesh
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L30 _protected member_ `static const FLazyName AutoUpdateTextureMetadata;`
- L33 _protected prototype_ `bool CanConvertToStaticMesh() const;` — Enable or disable the button when selected object is not compatible
- L36 _protected prototype_ `FReply OnConvertToStaticMeshClicked();` — Handler when the convert button is clicked
- L38 _protected prototype_ `bool CanSizeToTexture() const;`
- L39 _protected prototype_ `FReply OnSizeToTextureClicked();`
- L40 _protected prototype_ `ECheckBoxState OnIsAutoSizeToTextureChecked() const;`
- L41 _protected prototype_ `void OnTexturePropertyChanged();`
- L42 _protected prototype_ `void OnAutoSizeToTextureStateChanged(ECheckBoxState InState);`
- L43 _protected prototype_ `void ApplySizeToTexture(UAvaShapeDynamicMeshBase* InMeshGenerator);`
- L45 _protected member_ `TArray<TWeakObjectPtr<UAvaShapeDynamicMeshBase>> MeshGeneratorsWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/Customizations/AvaSceneSettingsCustomization.h` (Private)


#### class `FAvaSceneSettingsCustomization`  
`class FAvaSceneSettingsCustomization : public IDetailCustomization`  
_L11-26_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeDefaultInstance();`
- L16 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance(TWeakPtr<IAvaEditor> InEditorWeak);`
- L18 _public prototype_ `explicit FAvaSceneSettingsCustomization(const TWeakPtr<IAvaEditor>& InEditorWeak);`
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L25 _private member_ `TWeakPtr<IAvaEditor> EditorWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/Customizations/AvaVectorPropertyTypeCustomization.h` (Private)


#### class `FAvaVectorPropertyTypeIdentifier`  
`class FAvaVectorPropertyTypeIdentifier : public IPropertyTypeIdentifier`  
_L19-27_
- inherits: `IPropertyTypeIdentifier`
- desc: Used to detect if the type customization can be applied to a property
- L22 _public function_ `virtual bool IsPropertyTypeCustomized(const IPropertyHandle& InPropertyHandle) const override`

#### enum `ERatioMode`  
`enum class ERatioMode : uint8`  
_L30-40_
- reflection: `UENUM()`
- L32 _public enumerator_ `None = 0` — Free
- L33 _public enumerator_ `X = 1 << 0`
- L34 _public enumerator_ `Y = 1 << 1`
- L35 _public enumerator_ `Z = 1 << 2`
- L36 _public enumerator_ `PreserveXY = X | Y` — Lock XY
- L37 _public enumerator_ `PreserveYZ = Y | Z` — Lock YZ  (3D)
- L38 _public enumerator_ `PreserveXZ = X | Z` — Lock XZ  (3D)
- L39 _public enumerator_ `PreserveXYZ = X | Y | Z` — Lock XYZ (3D)

#### class `FAvaVectorPropertyTypeCustomization`  
`class FAvaVectorPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L44-139_
- inherits: `IPropertyTypeCustomization`
- L47 _public typedef_ `using SNumericVectorInputBox2D = SNumericVectorInputBox<double, UE::Math::TVector2<double>, 2>;`
- L48 _public typedef_ `using SNumericVectorInputBox3D = SNumericVectorInputBox<FVector::FReal, UE::Math::TVector<FVector::FReal>, 3>;`
- L50 _public member_ `static constexpr const TCHAR* PropertyMetadata = TEXT("All`
- L51 _public member_ `static constexpr uint8 MULTI_OBJECT_DEBOUNCE = 3;`
- L52 _public member_ `static constexpr uint8 SINGLE_OBJECT_DEBOUNCE = 2;`
- L53 _public member_ `static constexpr uint8 INVALID_COMPONENT_IDX = 5;`
- L55 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L60 _public function_ `explicit FAvaVectorPropertyTypeCustomization()`
- L65 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L68 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L74 _protected prototype_ `TOptional<double> GetVectorComponent(const uint8 InComponent) const;`
- L75 _protected prototype_ `void SetVectorComponent(double InNewValue, const uint8 InComponent);`
- L76 _protected prototype_ `void SetVectorComponent(double InNewValue, ETextCommit::Type InCommitType, const uint8 InComponent);`
- L78 _protected prototype_ `void OnBeginSliderMovement();`
- L79 _protected prototype_ `void OnEndSliderMovement(double InNewValue);`
- L81 _protected prototype_ `TSharedRef<SWidget> OnGenerateRatioWidget(FName InRatioMode);`
- L82 _protected prototype_ `void OnRatioSelectionChanged(FName InRatioMode, ESelectInfo::Type InSelectInfo) const;`
- L83 _protected prototype_ `FName GetRatioCurrentItem() const;`
- L84 _protected prototype_ `EVisibility GetRatioWidgetVisibility() const;`
- L86 _protected prototype_ `const FSlateBrush* GetRatioModeBrush(const ERatioMode InMode) const;`
- L87 _protected prototype_ `FText GetRatioModeDisplayText(const ERatioMode InMode) const;`
- L89 _protected prototype_ `const FSlateBrush* GetCurrentRatioModeBrush() const;`
- L90 _protected prototype_ `FText GetCurrentRatioModeDisplayText() const;`
- L92 _protected prototype_ `ERatioMode GetRatioModeMetadata() const;`
- L93 _protected prototype_ `void SetRatioModeMetadata(ERatioMode InMode) const;`
- L95 _protected prototype_ `bool CanEditValue() const;`
- L96 _protected prototype_ `void InitVectorValuesForRatio();`
- L97 _protected prototype_ `void ResetVectorValuesForRatio();`
- L99 _protected prototype_ `void SetComponentValue(const double InNewValue, const uint8 InComponent, const EPropertyValueSetFlags::Type InFlags);`
- L102 _protected prototype_ `double GetClampedRatioValueChange(const int32 InObjectIdx, const double InNewValue, const uint8 InComponent, const TArray<bool>& InPreserveRatios) const;` — get the correct clamped ratio if a component hit min/max value
- L105 _protected prototype_ `double GetClampedComponentValue(const int32 InObjectIdx, double InNewValue, const double InRatio, const uint8 InComponentIdx, const uint8 InOriginalComponent);` — get the new clamped value if a component original value is zero since ratio * 0 = 0
- L108 _protected prototype_ `double MeshSizeToPixelSize(double InMeshSize) const;` — special case for the pixel property only available in editor
- L110 _protected prototype_ `double PixelSizeToMeshSize(double InPixelSize) const;`
- L113 _private member_ `TWeakPtr<IAvaViewportClient> ViewportClient;`
- L115 _private member_ `TSharedPtr<IPropertyHandle> VectorPropertyHandle;`
- L116 _private member_ `TArray<TSharedPtr<IPropertyHandle>> VectorComponentPropertyHandles;`
- L119 _private member_ `TArray<TOptional<FVector>> Begin3DValues;` — optional begin values to compute ratios change
- L120 _private member_ `TArray<TOptional<FVector2D>> Begin2DValues;`
- L122 _private member_ `int32 SelectedObjectNum = 0;`
- L123 _private member_ `uint8 DebounceValueSet = 0;`
- L124 _private member_ `uint8 LastComponentValueSet = INDEX_NONE;`
- L125 _private member_ `bool bMovingSlider = false;`
- L126 _private member_ `bool bIsVector3d = false;`
- L129 _private member_ `bool bPixelSizeProperty = false;` — specific case to handle that needs conversion
- L132 _private member_ `TOptional<FVector> MinVectorClamp;` — optional clamp values
- L133 _private member_ `TOptional<FVector> MaxVectorClamp;`
- L134 _private member_ `TOptional<FVector2D> MinVector2DClamp;`
- L135 _private member_ `TOptional<FVector2D> MaxVector2DClamp;`
- L138 _private member_ `TArray<FName> RatioModes;` — Ratio modes available for the property dropdown

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/Customizations/AvaViewportQualitySettingsPropertyTypeCustomization.h` (Private)


#### class `FAvaViewportQualitySettingsPropertyTypeCustomization`  
`class FAvaViewportQualitySettingsPropertyTypeCustomization : public IPropertyTypeCustomization`  
_L12-42_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& DetailBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _protected prototype_ `void RefreshPresets();`
- L25 _protected prototype_ `FAvaViewportQualitySettings& GetStructRef() const;`
- L27 _protected prototype_ `FReply HandleDefaultsButtonClick();`
- L28 _protected prototype_ `FReply HandleEnableAllButtonClick();`
- L29 _protected prototype_ `FReply HandleDisableAllButtonClick();`
- L30 _protected prototype_ `FReply HandlePresetButtonClick(const FText InPresetName);`
- L32 _protected prototype_ `bool IsDefaultsButtonEnabled() const;`
- L33 _protected prototype_ `bool IsAllButtonEnabled() const;`
- L34 _protected prototype_ `bool IsNoneButtonEnabled() const;`
- L35 _protected prototype_ `bool IsPresetButtonEnabled(const FText InPresetName) const;`
- L37 _protected prototype_ `void OpenEditorSettings() const;`
- L39 _protected member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L41 _protected member_ `TSharedPtr<SWrapBox> PresetsWrapBox;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/IAvaDetailsProvider.h` (Private)


#### class `IAvaDetailsProvider`  
`class IAvaDetailsProvider`  
_L10-16_
- L13 _public prototype_ `virtual FEditorModeTools* GetDetailsModeTools() const = 0;`
- L15 _public prototype_ `virtual TSharedPtr<IDetailKeyframeHandler> GetDetailsKeyframeHandler() const = 0;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/DetailView/Widgets/SAvaDynamicMaterialWidget.h` (Private)


#### class `SAvaDynamicMaterialWidget`  
`class SAvaDynamicMaterialWidget : public SCompoundWidget`  
_L12-38_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SAvaDynamicMaterialWidget)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<IPropertyHandle> InPropertyHandle);`
- L21 _protected member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L23 _protected prototype_ `UObject* GetAsset() const;`
- L24 _protected prototype_ `void SetAsset(UObject* NewAsset);`
- L26 _protected prototype_ `UDynamicMaterialInstance* GetDynamicMaterialInstance() const;`
- L27 _protected prototype_ `void SetDynamicMaterialInstance(UDynamicMaterialInstance* NewInstance);`
- L29 _protected prototype_ `FReply OnButtonClicked();`
- L30 _protected prototype_ `FReply CreateDynamicMaterialInstance();`
- L31 _protected prototype_ `FReply ClearDynamicMaterialInstance();`
- L32 _protected prototype_ `FReply OpenDynamicMaterialInstanceTab();`
- L34 _protected prototype_ `EVisibility GetButtonVisibility() const;`
- L35 _protected prototype_ `EVisibility GetPickerVisibility() const;`
- L36 _protected prototype_ `FString GetAssetPath() const;`
- L37 _protected prototype_ `void OnAssetChanged(const FAssetData& AssetData);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/EditorProvider/AvaEditorProvider.h` (Private)


#### class `FAvaEditorProvider`  
`class FAvaEditorProvider : public IAvaEditorProvider`  
_L8-19_
- inherits: `IAvaEditorProvider`
- desc: Base Implementation for the Core Editor Provider
- L12 _public prototype_ `virtual UObject* GetSceneObject(UWorld* InWorld, EAvaEditorObjectQueryType InQueryType) override;`
- L13 _public prototype_ `virtual bool ShouldAutoActivateScene(UObject* InSceneObject) const override;`
- L14 _public prototype_ `virtual void SetAutoActivateScene(UObject* InSceneObject, bool bInAutoActivateScene) const override;`
- L15 _public prototype_ `virtual void GetActorsToEdit(TArray<AActor*>& InOutActorsToEdit) const override;`
- L16 _public prototype_ `virtual void OnSceneActivated() override;`
- L17 _public prototype_ `virtual void OnSceneDeactivated() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/InteractiveTools/AvaCameraActorTool.h` (Private)


#### class `UAvaCameraActorTool`  
`class UAvaCameraActorTool : public UAvaInteractiveToolsActorTool`  
_L9-20_
- reflection: `UCLASS(DisplayName = "Motion Design Camera Actor Tool")`
- inherits: `UAvaInteractiveToolsActorTool`
- L14 _public prototype_ `UAvaCameraActorTool();`
- L18 _protected prototype_ `virtual void DefaultAction() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/InteractiveTools/AvaInteractiveToolsExtension.h` (Private)


#### class `FAvaInteractiveToolsExtension`  
`class FAvaInteractiveToolsExtension : public FAvaEditorExtension`  
_L12-33_
- inherits: `FAvaEditorExtension`
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaInteractiveToolsExtension, FAvaEditorExtension);`
- L20 _public prototype_ `virtual void PostInvokeTabs() override;`
- L21 _public prototype_ `virtual void Activate() override;`
- L22 _public prototype_ `virtual void Deactivate() override;`
- L26 _protected prototype_ `void RegisterToolDelegates();`
- L28 _protected prototype_ `void UnregisterToolDelegates();`
- L30 _protected prototype_ `void RegisterCategories(IAvalancheInteractiveToolsModule* InModule);`
- L32 _protected prototype_ `void RegisterTools(IAvalancheInteractiveToolsModule* InModule);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/MaterialDesigner/AvaLevelMaterialDesignerExtension.h` (Private)


#### class `FAvaLevelMaterialDesignerExtension`  
`class FAvaLevelMaterialDesignerExtension : public FAvaMaterialDesignerExtension`  
_L15-35_
- inherits: `FAvaMaterialDesignerExtension`
- L18 _public prototype_ `UE_AVA_INHERITS(FAvaLevelMaterialDesignerExtension, FAvaMaterialDesignerExtension);`
- L21 _public prototype_ `virtual void Activate() override;`
- L22 _public prototype_ `virtual void Deactivate() override;`
- L26 _private member_ `bool bIsActive = false;`
- L28 _private prototype_ `static void InitContentBrowserExtension();`
- L30 _private prototype_ `static void DeinitContentBrowserExtension();`
- L32 _private prototype_ `static TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& InSelectedAssets);`
- L34 _private prototype_ `static void AddTextureToSene(FAssetData InAssetData);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/MaterialDesigner/AvaMaterialDesignerExtension.h` (Private)


#### class `FAvaMaterialDesignerExtension`  
`class FAvaMaterialDesignerExtension : public FAvaEditorExtension`  
_L11-29_
- inherits: `FAvaEditorExtension`
- L14 _public prototype_ `UE_AVA_INHERITS(FAvaMaterialDesignerExtension, FAvaEditorExtension);`
- L16 _public prototype_ `void OpenEditor();`
- L19 _public prototype_ `virtual void Activate() override;`
- L20 _public prototype_ `virtual void ExtendToolbarMenu(UToolMenu& InMenu) override;`
- L24 _private prototype_ `bool IsDynamicMaterialModelValid(UDynamicMaterialModelBase* InMaterialModel);`
- L26 _private prototype_ `bool SetDynamicMaterialValue(const FDMObjectMaterialProperty& InObjectMaterialProperty, UDynamicMaterialInstance* InMaterial);`
- L28 _private prototype_ `void InitWorldSubsystem();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/MaterialDesigner/AvaMaterialDesignerTextureAssetFactory.h` (Private)


#### class `UAvaMaterialDesignerTextureAssetFactory`  
`class UAvaMaterialDesignerTextureAssetFactory : public UActorFactory`  
_L9-32_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L16 _public prototype_ `UAvaMaterialDesignerTextureAssetFactory();`
- L18 _public prototype_ `void SetCameraRotation(const FRotator& InRotation);`
- L21 _public prototype_ `virtual bool CanCreateActorFrom(const FAssetData& InAssetData, FText& OutErrorMsg) override;`
- L25 _protected member_ `bool bFactoryEnabled;`
- L26 _protected member_ `FRotator CameraRotation;`
- L29 _protected prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L30 _protected prototype_ `virtual FString GetDefaultActorLabel(UObject* InAsset) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/OperatorStack/AvaOperatorStackExtension.h` (Private)


#### class `FAvaOperatorStackExtension`  
`class FAvaOperatorStackExtension : public FAvaEditorExtension`  
_L10-33_
- inherits: `FAvaEditorExtension`
- L13 _public prototype_ `UE_AVA_INHERITS(FAvaOperatorStackExtension, FAvaEditorExtension);`
- L15 _public prototype_ `FAvaOperatorStackExtension();`
- L17 _public prototype_ `TSharedPtr<SDockTab> FindOrOpenTab(bool bInOpen) const;`
- L20 _public prototype_ `virtual void Activate() override;`
- L21 _public prototype_ `virtual void Deactivate() override;`
- L22 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<IAvaEditor>& InEditor) const override;`
- L23 _public prototype_ `virtual void ExtendLevelEditorLayout(FLayoutExtender& InExtender) const override;`
- L24 _public prototype_ `virtual void ExtendToolbarMenu(UToolMenu& InMenu) override;`
- L25 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L29 _private prototype_ `void EnableAnimators(bool bInEnable) const;`
- L30 _private prototype_ `void OnOperatorStackSpawned(TSharedRef<SOperatorStackEditorWidget> InWidget);`
- L32 _private member_ `TSharedRef<FUICommandList> AnimatorCommands;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Outliner/AvaOutlinerExtension.h` (Private)


#### class `FAvaOutlinerExtension`  
`class FAvaOutlinerExtension : public FAvaEditorExtension, public IAvaOutlinerProvider`  
_L14-73_
- inherits: `FAvaEditorExtension,IAvaOutlinerProvider`
- L17 _private member_ `static constexpr EAvaOutlinerIgnoreNotifyFlags NotifyFlags = EAvaOutlinerIgnoreNotifyFlags::Spawn | EAvaOutlinerIgnoreNotifyFlags::Duplication;` — Flags to use while processing Copy/Paste
- L20 _public prototype_ `UE_AVA_INHERITS(FAvaOutlinerExtension, FAvaEditorExtension, IAvaOutlinerProvider);`
- L22 _public prototype_ `static void StaticStartup();`
- L24 _public prototype_ `FAvaOutlinerExtension();`
- L26 _public function_ `TSharedPtr<IAvaOutliner> GetAvaOutliner() const`
- L29 _public prototype_ `virtual void Activate() override;`
- L30 _public prototype_ `virtual void PostInvokeTabs() override;`
- L31 _public prototype_ `virtual void Deactivate() override;`
- L32 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L33 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<IAvaEditor>& InEditor) const override;`
- L34 _public prototype_ `virtual void ExtendLevelEditorLayout(FLayoutExtender& InExtender) const override;`
- L35 _public prototype_ `virtual void Save() override;`
- L36 _public prototype_ `virtual void Load() override;`
- L37 _public prototype_ `virtual void NotifyOnSelectionChanged(const FAvaEditorSelection& InSelection) override;`
- L38 _public prototype_ `virtual void OnCopyActors(FString& OutCopyData, TConstArrayView<AActor*> InActorsToCopy) override;`
- L39 _public prototype_ `virtual void PrePasteActors() override;`
- L40 _public prototype_ `virtual void PostPasteActors(bool bInPasteSucceeded) override;`
- L41 _public prototype_ `virtual void OnPasteActors(FStringView InPastedData, TConstArrayView<FAvaEditorPastedActor> InPastedActors) override;`
- L45 _public function_ `virtual bool ShouldCreateWidget() const override`
- L46 _public prototype_ `virtual bool ShouldLockOutliner() const override;`
- L47 _public prototype_ `virtual bool CanOutlinerProcessActorSpawn(AActor* InActor) const override;`
- L48 _public prototype_ `virtual bool ShouldHideItem(const FAvaOutlinerItemPtr& InItem) const override;`
- L49 _public prototype_ `virtual void OutlinerDuplicateActors(const TArray<AActor*>& InTemplateActors) override;`
- L50 _public prototype_ `virtual void OutlinerDeleteActors(const TArray<AActor*>& InDeleteActors) override;`
- L51 _public prototype_ `virtual FEditorModeTools* GetOutlinerModeTools() const override;`
- L52 _public prototype_ `virtual FAvaSceneTree* GetSceneTree() const override;`
- L53 _public prototype_ `virtual UWorld* GetOutlinerWorld() const override;`
- L54 _public prototype_ `virtual FTransform GetOutlinerDefaultActorSpawnTransform() const override;`
- L55 _public prototype_ `virtual void ExtendOutlinerToolBar(UToolMenu* InToolBarMenu) override;`
- L56 _public prototype_ `virtual void ExtendOutlinerItemContextMenu(UToolMenu* InItemContextMenu) override;`
- L57 _public prototype_ `virtual void ExtendOutlinerItemFilters(TArray<TSharedPtr<class IAvaOutlinerItemFilter>>& OutItemFilters) override;`
- L58 _public prototype_ `virtual TOptional<EItemDropZone> OnOutlinerItemCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) const override;`
- L59 _public prototype_ `virtual FReply OnOutlinerItemAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FAvaOutlinerItemPtr InTargetItem) override;`
- L60 _public prototype_ `virtual void NotifyOutlinerItemRenamed(const FAvaOutlinerItemPtr& InItem) override;`
- L61 _public prototype_ `virtual void NotifyOutlinerItemLockChanged(const FAvaOutlinerItemPtr& InItem) override;`
- L62 _public prototype_ `virtual const FAttachmentTransformRules& GetTransformRule(bool bIsPrimaryTransformRule) const override;`
- L66 _private prototype_ `void GroupSelection();`
- L68 _private prototype_ `bool OnSceneRigFilterPass(FAvaOutlinerFilterType InItem) const;`
- L70 _private member_ `TSharedPtr<IAvaOutliner> AvaOutliner;`
- L72 _private member_ `TSharedRef<FUICommandList> OutlinerCommands;`

#### Free symbols / members of external scopes

- L12 _prototype_ `UE_AVA_TYPE_EXTERNAL(IAvaOutlinerProvider);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Outliner/AvaOutlinerMaterialDesigner.h` (Private)


#### class `FAvaOutlinerMaterialDesigner`  
`class FAvaOutlinerMaterialDesigner : public FAvaOutlinerMaterial`  
_L15-28_
- inherits: `FAvaOutlinerMaterial`
- desc: Item in Outliner representing a Material. Inherits from FAvaOutlinerObjectReference as multiple objects can have the same material
- L18 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerMaterialDesigner, FAvaOutlinerMaterial) FAvaOutlinerMaterialDesigner(IAvaOutliner& InOutliner , UMaterialInterface* InMaterial , const FAvaOutlinerItemPtr& InReferencingItem , int32 InMaterialIndex);`
- L26 _public prototype_ `virtual void Select(FAvaOutlinerScopedSelection& InSelection) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Outliner/AvaOutlinerMaterialDesignerProxy.h` (Private)


#### class `FAvaOutlinerMaterialDesignerProxy`  
`class FAvaOutlinerMaterialDesignerProxy : public FAvaOutlinerMaterialProxy`  
_L8-20_
- inherits: `FAvaOutlinerMaterialProxy`
- L11 _public prototype_ `UE_AVA_INHERITS_WITH_SUPER(FAvaOutlinerMaterialDesignerProxy, FAvaOutlinerMaterialProxy);`
- L13 _public prototype_ `FAvaOutlinerMaterialDesignerProxy(IAvaOutliner& InOutliner, const FAvaOutlinerItemPtr& InParentItem);`
- L15 _public prototype_ `virtual ~FAvaOutlinerMaterialDesignerProxy() override = default;`
- L18 _public prototype_ `virtual void GetProxiedItems(const TSharedRef<IAvaOutlinerItem>& InParent, TArray<FAvaOutlinerItemPtr>& OutChildren, bool bInRecursive) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Outliner/AvaOutlinerTabSpawner.h` (Private)


#### class `FAvaOutlinerTabSpawner`  
`class FAvaOutlinerTabSpawner : public FAvaTabSpawner`  
_L7-22_
- inherits: `FAvaTabSpawner`
- L10 _public member_ `static constexpr int32 MaxTabCount = 4;`
- L11 _public prototype_ `static FName GetTabID(int32 InOutlinerId = 0);`
- L13 _public prototype_ `explicit FAvaOutlinerTabSpawner(int32 InOutlinerId, const TSharedRef<IAvaEditor>& InEditor);`
- L16 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody() override;`
- L17 _public prototype_ `virtual FTabSpawnerEntry& RegisterTabSpawner(const TSharedRef<FTabManager>& InTabManager, const TSharedPtr<FWorkspaceItem>& InWorkspaceMenu) override;`
- L21 _private member_ `int32 OutlinerViewId = -1;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/RemoteControl/AvaRCExtension.h` (Private)


#### class `FAvaRCExtension`  
`class FAvaRCExtension: public FAvaEditorExtension`  
_L11-45_
- inherits: `FAvaEditorExtension`
- L14 _public prototype_ `UE_AVA_INHERITS(FAvaRCExtension, FAvaEditorExtension);`
- L16 _public prototype_ `virtual ~FAvaRCExtension() override = default;`
- L18 _public prototype_ `URemoteControlPreset* GetRemoteControlPreset() const;`
- L21 _public prototype_ `virtual void Activate() override;`
- L22 _public prototype_ `virtual void Deactivate() override;`
- L23 _public prototype_ `virtual void ExtendLevelEditorLayout(FLayoutExtender& InExtender) const override;`
- L24 _public prototype_ `virtual void ExtendToolbarMenu(UToolMenu& InMenu) override;`
- L25 _public prototype_ `virtual void OnSceneObjectChanged(UObject* InOldSceneObject, UObject* InNewSceneObject) override;`
- L29 _protected prototype_ `void OpenRemoteControlTab(bool bInCreateIfNotFound) const;`
- L30 _protected prototype_ `void CloseRemoteControlTab() const;`
- L32 _protected prototype_ `void RegisterSignatureCustomization();`
- L33 _protected prototype_ `void UnregisterSignatureCustomization();`
- L36 _protected prototype_ `bool CanDeleteRemoteControlPreset() const;` — Determines whether the scene's rc preset can be deleted
- L39 _protected prototype_ `void DeleteRemoteControlPreset();` — Deletes the scene's rc preset (if any)
- L42 _protected prototype_ `void GenerateRemoteControlOptions(UToolMenu* InMenu);` — Generates the sub-menu options for remote control
- L44 _protected member_ `TSharedPtr<IRCSignatureCustomization> SignatureCustomization;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/RemoteControl/AvaRCSignatureCustomization.h` (Private)


#### class `FAvaRCSignatureCustomization`  
`class FAvaRCSignatureCustomization : public IRCSignatureCustomization`  
_L7-13_
- inherits: `IRCSignatureCustomization`
- L10 _private prototype_ `virtual bool CanAcceptDrop(const FDragDropEvent& InDragDropEvent, IRCSignatureItem* InSignatureItem) const override;`
- L11 _private prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, IRCSignatureItem* InSignatureItem) const override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/SVGImporter/AvaOutlinerSVGActorContextMenu.h` (Private)


#### class `FAvaOutlinerSVGActorContextMenu`  
`class FAvaOutlinerSVGActorContextMenu`  
_L10-19_
- L14 _public prototype_ `static void OnExtendOutlinerContextMenu(UToolMenu* InToolMenu);` — Extend outliner context menu
- L17 _private prototype_ `static void GetActorItems(const UToolMenu* InToolMenu, TSet<TWeakObjectPtr<AActor>>& InActors);`
- L18 _private prototype_ `static void AddSVGActorMenuEntries(UToolMenu* InToolMenu, const TSet<TWeakObjectPtr<AActor>>& InActors);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Scene/AvaSceneDefaults.h` (Private)


#### enum `EAvaSceneDefaultActorResponse`  
`enum class EAvaSceneDefaultActorResponse : uint8`  
_L16-22_
- L18 _public enumerator_ `SkipActor`
- L19 _public enumerator_ `CreateNewActor`
- L20 _public enumerator_ `ReplaceActor`
- L21 _public enumerator_ `UpdateActor`

#### struct `FAvaSceneDefaultActorResponse`  
`struct FAvaSceneDefaultActorResponse`  
_L24-31_
- L26 _public member_ `TWeakObjectPtr<UClass> ActorClassWeak;`
- L27 _public member_ `FText Description = FText::GetEmpty();`
- L28 _public member_ `TArray<TWeakObjectPtr<AActor>> AvailableActors = {};`
- L29 _public member_ `TWeakObjectPtr<AActor> SelectedActor = nullptr;`
- L30 _public member_ `EAvaSceneDefaultActorResponse Response = EAvaSceneDefaultActorResponse::CreateNewActor;`

#### class `FAvaSceneDefaults`  
`class FAvaSceneDefaults`  
_L33-37_
- L36 _public prototype_ `static void CreateDefaultScene(TSharedRef<IAvaEditor> InEditor, UWorld* InWorld);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Scene/AvaSceneExtension.h` (Private)


#### class `FAvaSceneExtension`  
`class FAvaSceneExtension : public FAvaEditorExtension`  
_L7-20_
- inherits: `FAvaEditorExtension`
- L10 _public prototype_ `UE_AVA_INHERITS(FAvaSceneExtension, FAvaEditorExtension);`
- L13 _public prototype_ `virtual void ExtendToolbarMenu(UToolMenu& InMenu) override;`
- L14 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<IAvaEditor>& InEditor) const override;`
- L15 _public prototype_ `virtual void ExtendLevelEditorLayout(FLayoutExtender& InExtender) const override;`
- L19 _private prototype_ `void SpawnDefaultScene();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Scene/AvaSceneRigExtension.h` (Private)


#### class `FAvaSceneRigExtension`  
`class FAvaSceneRigExtension : public FAvaEditorExtension`  
_L16-49_
- inherits: `FAvaEditorExtension`
- L19 _public prototype_ `UE_AVA_INHERITS(FAvaSceneRigExtension, FAvaEditorExtension);`
- L21 _public prototype_ `void PromptToSaveSceneRigFromOutlinerItems();`
- L22 _public prototype_ `bool CanSaveSceneRigFromOutlinerItems() const;`
- L24 _public prototype_ `void AddOutlinerItemsToSceneRig();`
- L25 _public prototype_ `bool CanAddOutlinerItemsToSceneRig() const;`
- L27 _public prototype_ `void RemoveOutlinerItemsFromSceneRig();`
- L28 _public prototype_ `bool CanRemoveOutlinerItemsFromSceneRig() const;`
- L31 _public prototype_ `virtual void Activate() override;`
- L32 _public prototype_ `virtual void Deactivate() override;`
- L33 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L37 _protected prototype_ `static TArray<AActor*> OutlinerItemsToActors(const TConstArrayView<FAvaOutlinerItemWeakPtr>& InOutlinerItems , const bool bInIncludeLocked = false);`
- L40 _protected prototype_ `void ExtendOutlinerItemContextMenu(UToolMenu* const InToolMenu);`
- L42 _protected prototype_ `void CreateSubMenu(UToolMenu* const InToolMenu);`
- L44 _protected member_ `FDelegateHandle OutlinerItemContextMenuDelegate;`
- L46 _protected member_ `TWeakPtr<FUICommandList> CommandListWeak;`
- L48 _protected member_ `TWeakObjectPtr<UAvaOutlinerItemsContext> ItemsContextWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Scene/AvaSceneSettingsTabSpawner.h` (Private)


#### class `FAvaSceneSettingsTabSpawner`  
`class FAvaSceneSettingsTabSpawner : public FAvaTabSpawner`  
_L7-17_
- inherits: `FAvaTabSpawner`
- L10 _public prototype_ `static FName GetTabID();`
- L12 _public prototype_ `explicit FAvaSceneSettingsTabSpawner(const TSharedRef<IAvaEditor>& InEditor);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody() override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Scene/SAvaSceneDefaultActorResponseRow.h` (Private)


#### class `SAvaSceneDefaultActorResponseRow`  
`class SAvaSceneDefaultActorResponseRow : public SMultiColumnTableRow<TSharedRef<FAvaSceneDefaultActorResponse>>`  
_L19-78_
- inherits: `SMultiColumnTableRow<TSharedRef<FAvaSceneDefaultActorResponse>>`
- L21 _private function_ `SLATE_BEGIN_ARGS(SAvaSceneDefaultActorResponseRow)`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, const TSharedRef<SAvaSceneDefaultActorResponses>& InActorResponses, const TSharedRef<FAvaSceneDefaultActorResponse>& InActorResponse);`
- L29 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName & InColumnName) override;`
- L32 _public prototype_ `static bool IsSelectableActor(TWeakObjectPtr<AActor> InActor);`
- L35 _protected member_ `TWeakPtr<SAvaSceneDefaultActorResponses> ActorResponsesWeak;`
- L36 _protected member_ `TSharedPtr<FAvaSceneDefaultActorResponse> ActorResponse;`
- L38 _protected member_ `TSharedPtr<SComboBox<TWeakObjectPtr<AActor>>> ActorSelect;`
- L39 _protected member_ `TSharedPtr<SCheckBox> CreateNewCheckBox;`
- L40 _protected member_ `TSharedPtr<SCheckBox> ReplaceCheckBox;`
- L41 _protected member_ `TSharedPtr<SCheckBox> UpdateCheckBox;`
- L42 _protected member_ `TSharedPtr<SCheckBox> EnabledCheckBox;`
- L44 _protected member_ `mutable TOptional<FText> SelectedActorLabel;`
- L45 _protected member_ `mutable TOptional<FSlateColor> SelectedActorColor;`
- L47 _protected prototype_ `TSharedRef<SWidget> GenerateRow_Description();`
- L48 _protected prototype_ `TSharedRef<SWidget> GenerateRow_Actor();`
- L49 _protected prototype_ `TSharedRef<SWidget> GenerateRow_CreateNew();`
- L50 _protected prototype_ `TSharedRef<SWidget> GenerateRow_Replace();`
- L51 _protected prototype_ `TSharedRef<SWidget> GenerateRow_Update();`
- L52 _protected prototype_ `TSharedRef<SWidget> GenerateRow_Enabled();`
- L54 _protected prototype_ `FSlateColor GetDescriptionColor() const;`
- L56 _protected prototype_ `ECheckBoxState GetCreateNewCheckBoxState() const;`
- L57 _protected prototype_ `EVisibility GetCreateNewCheckBoxVisibility() const;`
- L58 _protected prototype_ `void OnCreateNewCheckBoxChanged(ECheckBoxState InState);`
- L60 _protected prototype_ `ECheckBoxState GetReplaceCheckBoxState() const;`
- L61 _protected prototype_ `EVisibility GetReplaceCheckBoxVisibility() const;`
- L62 _protected prototype_ `void OnReplaceCheckBoxChanged(ECheckBoxState InState);`
- L64 _protected prototype_ `ECheckBoxState GetUpdateCheckBoxState() const;`
- L65 _protected prototype_ `EVisibility GetUpdateCheckBoxVisibility() const;`
- L66 _protected prototype_ `void OnUpdateCheckBoxChanged(ECheckBoxState InState);`
- L68 _protected prototype_ `ECheckBoxState GetEnabledCheckBoxState() const;`
- L69 _protected prototype_ `void OnEnabledCheckBoxChanged(ECheckBoxState InState);`
- L71 _protected prototype_ `EVisibility GetActorSelectVisibility() const;`
- L72 _protected prototype_ `void OnActorPickerSelected(AActor* InActor);`
- L74 _protected prototype_ `FSlateColor GetActorSelectRowColor() const;`
- L75 _protected prototype_ `FText GetActorSelectRowLabel() const;`
- L77 _protected prototype_ `bool HasSelectedActor() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Scene/SAvaSceneDefaultActorResponses.h` (Private)


#### class `SAvaSceneDefaultActorResponses`  
`class SAvaSceneDefaultActorResponses : public SCompoundWidget`  
_L17-62_
- inherits: `SCompoundWidget`
- L19 _private function_ `SLATE_BEGIN_ARGS(SAvaSceneDefaultActorResponses)`
- L23 _public member_ `static const FName DescriptionRowName;`
- L24 _public member_ `static const FName CreateNewRowName;`
- L25 _public member_ `static const FName ReplaceRowName;`
- L26 _public member_ `static const FName UpdateRowName;`
- L27 _public member_ `static const FName EnabledRowName;`
- L28 _public member_ `static const FName TargetActorRowName;`
- L30 _public prototype_ `void Construct(const FArguments& InArgs, UWorld* InWorld, const TArray<TSharedRef<FAvaSceneDefaultActorResponse>>& InResponses);`
- L32 _public function_ `UWorld* GetWorld() const`
- L34 _public function_ `const TArray<TSharedRef<FAvaSceneDefaultActorResponse>>& GetResponses() const`
- L36 _public function_ `bool WasAccepted() const`
- L39 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L43 _protected member_ `TWeakObjectPtr<UWorld> World;`
- L44 _protected member_ `TArray<TSharedRef<FAvaSceneDefaultActorResponse>> Responses;`
- L45 _protected member_ `bool bAccepted;`
- L47 _protected member_ `TSharedPtr<SListView<TSharedRef<FAvaSceneDefaultActorResponse>>> ListView;`
- L49 _protected prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedRef<FAvaSceneDefaultActorResponse> InListItem, const TSharedRef<STableViewBase>& InListView);`
- L51 _protected prototype_ `bool IsOkayEnabled() const;`
- L53 _protected prototype_ `FReply OnOkayClick();`
- L55 _protected prototype_ `FReply OnCancelClick();`
- L57 _protected prototype_ `void CloseWindow();`
- L59 _protected prototype_ `ECheckBoxState GetEnableAllCheckState() const;`
- L61 _protected prototype_ `void OnEnableAllChecked(ECheckBoxState InState);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Selection/AvaPivotSetOperation.h` (Private)


#### enum `EAvaPivotBoundsType`  
`enum class EAvaPivotBoundsType : uint8`  
_L20-25_
- L22 _public enumerator_ `Actor`
- L23 _public enumerator_ `ActorAndChildren`
- L24 _public enumerator_ `Selection`

#### class `FAvaPivotSetOperation`  
`class FAvaPivotSetOperation`  
_L27-68_
- L30 _public typedef_ `using PivotSetCallbackType = TFunction<void(const FBox, FVector&)>;`
- L32 _public prototype_ `FAvaPivotSetOperation(UWorld* InWorld, EAvaPivotBoundsType InBoundsType, PivotSetCallbackType InPivotSetPredicate);`
- L34 _public prototype_ `void SetPivot();`
- L37 _protected member_ `UWorld* World;`
- L39 _protected member_ `EAvaPivotBoundsType BoundsType;`
- L41 _protected member_ `PivotSetCallbackType PivotSetCallback;`
- L43 _protected member_ `UAvaSelectionProviderSubsystem* SelectionProvider;`
- L45 _protected member_ `UAvaBoundsProviderSubsystem* BoundsProvider;`
- L47 _protected member_ `TConstArrayView<TWeakObjectPtr<AActor>> SelectedActors;`
- L49 _protected member_ `TSet<AActor*> SelectedActorSet;`
- L51 _protected member_ `TArray<AActor*> ValidActors;`
- L53 _protected member_ `TSet<AActor*> ValidActorsSet;`
- L55 _protected member_ `TSet<AActor*> InvalidActors;`
- L57 _protected member_ `FBox AxisAlignedBounds;`
- L59 _protected member_ `FTransform AxisAlignedTransform;`
- L61 _protected prototype_ `void GenerateValidActors();`
- L63 _protected prototype_ `void SetPivotCommonParent(AActor* InCommonParent);`
- L65 _protected prototype_ `void SetPivotIndividual();`
- L67 _protected prototype_ `AAvaNullActor* SpawnPivot(ULevel* InLevel);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Selection/AvaSelectionProviderExtension.h` (Private)


#### class `FAvaSelectionProviderExtension`  
`class FAvaSelectionProviderExtension : public FAvaEditorExtension`  
_L11-33_
- inherits: `FAvaEditorExtension`
- L14 _public prototype_ `UE_AVA_INHERITS(FAvaSelectionProviderExtension, FAvaEditorExtension);`
- L19 _public prototype_ `virtual void Activate() override;`
- L20 _public prototype_ `virtual void Deactivate() override;`
- L21 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L22 _public prototype_ `virtual void NotifyOnSelectionChanged(const FAvaEditorSelection& InSelection) override;`
- L26 _public prototype_ `void SetPlanePivot(FVector2D InPivotUV, EAvaPivotBoundsType InBoundsType);` — InPivotUV should be a UV-style value between -1 and 1 based on the bounds of the selection.
- L29 _public prototype_ `void SetDepthPivot(double InPivotUV, EAvaPivotBoundsType InBoundsType);` — InPivotUV should be a UV-style value between -1 and 1 based on the bounds of the selection.
- L32 _protected prototype_ `void OnLevelAttachmentChange(AActor* InAttachedActor, const AActor* InAttachedToActor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Sequencer/AvaLevelSequencerExtension.h` (Private)


#### class `FAvaLevelSequencerExtension`  
`class FAvaLevelSequencerExtension : public FAvaSequencerExtension`  
_L17-68_
- inherits: `FAvaSequencerExtension`
- L20 _public prototype_ `UE_AVA_INHERITS(FAvaLevelSequencerExtension, FAvaSequencerExtension);`
- L22 _public prototype_ `FAvaLevelSequencerExtension();`
- L27 _public prototype_ `virtual FAvaSequencerArgs MakeSequencerArgs() const override;`
- L31 _public prototype_ `virtual void Construct(const TSharedRef<IAvaEditor>& InEditor) override;`
- L32 _public prototype_ `virtual void ExtendLevelEditorLayout(FLayoutExtender& InExtender) const override;`
- L33 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<IAvaEditor>& InEditor) const override;`
- L34 _public prototype_ `virtual void Activate() override;`
- L35 _public prototype_ `virtual void Deactivate() override;`
- L36 _public prototype_ `virtual void PostInvokeTabs() override;`
- L40 _public prototype_ `virtual TSharedPtr<ISequencer> GetExternalSequencer() const override;`
- L41 _public prototype_ `virtual void OnViewedSequenceChanged(UAvaSequence* InOldSequence, UAvaSequence* InNewSequence) override;`
- L45 _private prototype_ `ULevelSequence* GetViewedSequence() const;`
- L47 _private prototype_ `ILevelSequenceEditorToolkit* OpenSequencerWithViewedSequence() const;`
- L49 _private prototype_ `void OnAssetEditorOpened(UObject* InObject);`
- L51 _private prototype_ `void ApplyTabContent();`
- L53 _private prototype_ `void RestoreTabContent();`
- L55 _private prototype_ `void AddCinematicsToolbarExtension();`
- L57 _private prototype_ `void RemoveCinematicsToolbarExtension();`
- L59 _private prototype_ `void AddSequenceEntries(FToolMenuSection& InSection, IAvaSequenceProvider* InSequenceProvider);`
- L61 _private member_ `TSharedRef<IAvaSequencerController> SequencerController;`
- L63 _private member_ `TWeakPtr<SWidget> SequencerTabContentWeak;`
- L65 _private member_ `TWeakPtr<SDockTab> SequencerTabWeak;`
- L67 _private member_ `FDelegateHandle OnAssetEditorOpenedHandle;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Sequencer/AvaSequencerExtension.h` (Private)


#### class `FAvaSequencerExtension`  
`class FAvaSequencerExtension: public FAvaEditorExtension, public IAvaSequencerProvider`  
_L18-91_
- inherits: `FAvaEditorExtension,IAvaSequencerProvider`
- L21 _public prototype_ `UE_AVA_INHERITS(FAvaSequencerExtension, FAvaEditorExtension, IAvaSequencerProvider);`
- L23 _public prototype_ `FAvaSequencerExtension();`
- L25 _public prototype_ `explicit FAvaSequencerExtension(FName InSequencerTabId, bool bInSupportsDrawerWidget);`
- L27 _public prototype_ `TSharedPtr<ISequencer> GetSequencer() const;`
- L29 _public prototype_ `void OnObjectRenamed(UObject* InRenamedObject, const FText& InDisplayNameText);`
- L31 _public function_ `FName GetSequencerTabId() const`
- L33 _public prototype_ `virtual FAvaSequencerArgs MakeSequencerArgs() const;`
- L36 _public function_ `virtual TSharedPtr<IAvaSequencer> GetAvaSequencer() const override`
- L37 _public prototype_ `virtual void Activate() override;`
- L38 _public prototype_ `virtual void Deactivate() override;`
- L39 _public prototype_ `virtual void Cleanup() override;`
- L40 _public prototype_ `virtual void OnSceneObjectCreated(UObject* InSceneObject) override;`
- L41 _public prototype_ `virtual void OnSceneObjectChanged(UObject* InOldSceneObject, UObject* InNewSceneObject) override;`
- L42 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<IAvaEditor>& InEditor) const override;`
- L43 _public prototype_ `virtual void ExtendLevelEditorLayout(FLayoutExtender& InExtender) const override;`
- L44 _public prototype_ `virtual void NotifyOnSelectionChanged(const FAvaEditorSelection& InSelection) override;`
- L45 _public prototype_ `virtual void OnCopyActors(FString& OutExtensionData, TConstArrayView<AActor*> InActorsToCopy) override;`
- L46 _public prototype_ `virtual void OnPasteActors(FStringView InPastedData, TConstArrayView<FAvaEditorPastedActor> InPastedActors) override;`
- L50 _public prototype_ `virtual IAvaSequenceProvider* GetSequenceProvider() const override;`
- L51 _public prototype_ `virtual FEditorModeTools* GetSequencerModeTools() const override;`
- L52 _public prototype_ `virtual IAvaSequencePlaybackObject* GetPlaybackObject() const override;`
- L53 _public prototype_ `virtual TSharedPtr<IToolkitHost> GetSequencerToolkitHost() const override;`
- L54 _public prototype_ `virtual UObject* GetPlaybackContext() const override;`
- L55 _public prototype_ `virtual bool CanEditOrPlaySequences() const override;`
- L56 _public prototype_ `virtual void ExportSequences(TConstArrayView<UAvaSequence*> InSequencesToExport) override;`
- L60 _protected member_ `TSharedPtr<IAvaSequencer> AvaSequencer;`
- L63 _private prototype_ `void BindDelegates();`
- L65 _private prototype_ `void UnbindDelegates();`
- L67 _private prototype_ `TSharedRef<SWidget> GetSequenceDrawerWidget();`
- L69 _private prototype_ `void RegisterSequenceDrawerWidget();`
- L71 _private prototype_ `void UnregisterSequenceDrawerWidget();`
- L74 _private prototype_ `void ConditionallyCreateDefaultSequences();` — Creates the default sequences gotten from the default preset group to use
- L77 _private prototype_ `void ValidateDirectorBlueprints();` — Temporary fix ensuring that any Director Blueprint that got renamed to the incorrect outer gets fixed to the correct outer
- L80 _private member_ `TSharedPtr<SWidget> SequencerDrawerWidget;` — The Drawer Widget for the Animations
- L82 _private member_ `const FName SequencerTabId;`
- L84 _private member_ `const bool bSupportsDrawerWidget;`
- L90 _private member_ `bool bCreateDefaultSequences = false;` — Flag to indicate whether to create the default sequences when activating Set to true when the scene object is first created, but before the editor itself is activated.

#### Free symbols / members of external scopes

- L16 _prototype_ `UE_AVA_TYPE_EXTERNAL(IAvaSequencerProvider);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Sequencer/AvaSequencerTabSpawner.h` (Private)


#### class `FAvaSequencerTabSpawner`  
`class FAvaSequencerTabSpawner : public FAvaTabSpawner`  
_L7-22_
- inherits: `FAvaTabSpawner`
- L10 _public prototype_ `static FName GetTabID();`
- L12 _public prototype_ `explicit FAvaSequencerTabSpawner(const TSharedRef<IAvaEditor>& InEditor, FName InTabId, bool bInIsDrawerTab = false);`
- L15 _public prototype_ `virtual TSharedRef<SWidget> CreateTabBody() override;`
- L18 _public prototype_ `TSharedRef<SWidget> CreateDrawerDockButton(TSharedRef<IAvaEditor> InEditor) const;`
- L21 _private member_ `bool bIsDrawerTab;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Ticker/AvaTickerActorTool.h` (Private)


#### class `UAvaTickerActorTool`  
`class UAvaTickerActorTool : public UAvaInteractiveToolsActorPointToolBase`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAvaInteractiveToolsActorPointToolBase`
- L14 _public prototype_ `UAvaTickerActorTool();`
- L17 _public prototype_ `virtual void OnRegisterTool(IAvalancheInteractiveToolsModule* InAITModule) override;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Transition/AvaTransitionExtension.h` (Private)


#### class `FAvaTransitionExtension`  
`class FAvaTransitionExtension : public FAvaEditorExtension`  
_L12-45_
- inherits: `FAvaEditorExtension`
- L15 _public prototype_ `UE_AVA_INHERITS(FAvaTransitionExtension, FAvaEditorExtension);`
- L17 _public prototype_ `static void StaticStartup();`
- L18 _public prototype_ `static void StaticShutdown();`
- L21 _public prototype_ `virtual void Construct(const TSharedRef<IAvaEditor>& InEditor) override;`
- L22 _public prototype_ `virtual void Activate() override;`
- L23 _public prototype_ `virtual void Deactivate() override;`
- L24 _public prototype_ `virtual FName GetCategoryName() const override;`
- L25 _public prototype_ `virtual void ExtendSettingsCategory(IDetailCategoryBuilder& InCategoryBuilder) override;`
- L26 _public prototype_ `virtual void OnSceneObjectCreated(UObject* InSceneObject) override;`
- L27 _public prototype_ `virtual void ExtendToolbarMenu(UToolMenu& InMenu) override;`
- L28 _public prototype_ `virtual void ExtendCreateSceneOptions(UToolMenu* InMenu) override;`
- L32 _private prototype_ `IAvaTransitionBehavior* GetTransitionBehavior() const;`
- L34 _private prototype_ `void BuildDefaultTransitionTree(UAvaTransitionTreeEditorData& InTreeEditorData);`
- L36 _private prototype_ `void OpenTransitionEditor();`
- L38 _private prototype_ `void CloseTransitionEditor();`
- L40 _private prototype_ `void GenerateTransitionLogicOptions(UToolMenu* InMenu);`
- L42 _private member_ `static FDelegateHandle PropertyFilterHandle;`
- L44 _private member_ `static FAvaTransitionRundownExtension RundownExtension;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Transition/AvaTransitionRundownExtension.h` (Private)


#### class `FAvaTransitionRundownExtension`  
`class FAvaTransitionRundownExtension`  
_L12-33_
- L15 _public prototype_ `FAvaTransitionRundownExtension();`
- L17 _public prototype_ `~FAvaTransitionRundownExtension();`
- L19 _public prototype_ `void Startup();`
- L21 _public prototype_ `void Shutdown();`
- L24 _private prototype_ `void ExtendPageContextMenu(UToolMenu* InMenu);`
- L26 _private prototype_ `void OpenTransitionTree(TWeakPtr<FAvaRundownEditor> InPlaylistEditorWeak);`
- L28 _private prototype_ `void OpenTransitionTree(const FSoftObjectPath& InPageAssetPath, const TCHAR* InPlaylistName, int32 InPageId);`
- L30 _private member_ `TWeakObjectPtr<UToolMenu> PageContextMenuWeak;`
- L32 _private member_ `const FName ExtensionSectionName;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Viewport/AvaLevelViewportExtension.h` (Private)


#### class `FAvaLevelViewportExtension`  
`class FAvaLevelViewportExtension : public FAvaViewportExtension`  
_L18-72_
- inherits: `FAvaViewportExtension`
- L21 _public prototype_ `UE_AVA_INHERITS(FAvaLevelViewportExtension, FAvaViewportExtension);`
- L23 _public prototype_ `static TArray<TSharedPtr<IAvaViewportClient>> GetLevelEditorViewportClients();`
- L25 _public prototype_ `void SetDefaultViewportType();`
- L26 _public prototype_ `void SetMotionDesignViewportType();`
- L27 _public prototype_ `void SetViewportType(const TSharedRef<FUICommandInfo>& InViewportCommand, bool bInSetActiveCamera);`
- L31 _public prototype_ `bool IsCameraCutEnabled() const;`
- L34 _public prototype_ `virtual void BindCommands(const TSharedRef<FUICommandList>& InCommandList) override;`
- L35 _public prototype_ `virtual void Activate() override;`
- L36 _public prototype_ `virtual void Deactivate() override;`
- L40 _public prototype_ `virtual void Construct(const TSharedRef<IAvaEditor>& InEditor) override;`
- L41 _public prototype_ `virtual TArray<TSharedPtr<IAvaViewportClient>> GetViewportClients() const override;`
- L42 _public prototype_ `virtual void NotifyOnSelectionChanged(const FAvaEditorSelection& InSelection) override;`
- L46 _public prototype_ `virtual bool IsDroppingPreviewActor() const override;`
- L50 _private member_ `FDelegateHandle OnMapChangedHandle;`
- L52 _private prototype_ `FViewportTypeDefinition MakeViewportTypeDefinition();`
- L54 _private member_ `TWeakObjectPtr<AActor> LastCameraCutActorWeak;`
- L56 _private prototype_ `void OnSwitchViewports();`
- L58 _private prototype_ `void OnMapChanged(UWorld* InWorld, EMapChangeType InChangeType);`
- L60 _private prototype_ `void CheckValidViewportType();`
- L62 _private prototype_ `void BindCameraCutDelegate();`
- L63 _private prototype_ `void UnbindCameraCutDelegate();`
- L65 _private prototype_ `void OnCameraCut(UObject* InCameraObject, bool bInJumpCut);`
- L67 _private prototype_ `void SetActiveCamera(AActor* InActiveCameraActor, bool bInJumpCut);`
- L69 _private prototype_ `void ExecuteResetLocation();`
- L70 _private prototype_ `void ExecuteResetRotation();`
- L71 _private prototype_ `void ExecuteResetScale();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheEditor/Private/Viewport/AvaViewportExtension.h` (Private)


#### class `IAvaViewportProvider`  
`class IAvaViewportProvider`  
_L11-20_
- L14 _public prototype_ `UE_AVA_TYPE(IAvaViewportProvider);`
- L16 _public prototype_ `virtual ~IAvaViewportProvider() = default;`
- L19 _public prototype_ `virtual bool IsDroppingPreviewActor() const = 0;` — Returns if the User is currently dropping an Actor that is Preview (e.g. Dragging an Actor to Spawn but not dropping it yet)

#### class `FAvaViewportExtension`  
`class FAvaViewportExtension : public FAvaEditorExtension, public IAvaViewportProvider`  
_L22-28_
- inherits: `FAvaEditorExtension,IAvaViewportProvider`
- L25 _public prototype_ `UE_AVA_INHERITS(FAvaViewportExtension, FAvaEditorExtension, IAvaViewportProvider);`
- L27 _public function_ `virtual TArray<TSharedPtr<IAvaViewportClient>> GetViewportClients() const`
