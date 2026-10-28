# Plugins / UMGWidgetPreview

- module root: `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview`
- headers: 18; symbols: 341
- symbol kinds: class=17, delegate=2, enum=1, enumerator=6, externvar=1, function=10, macro=1, member=81, namespace=40, prototype=169, struct=8, typedef=4, variable=1
- PrivateDependencyModuleNames: AdvancedPreviewScene, AssetDefinition, BlueprintGraph, ContentBrowser, Core, CoreUObject, DataValidation, EditorSubsystem, Engine, FieldNotification, InputCore, MessageLog, Projects, PropertyEditor, Slate, SlateCore, ToolMenus, UMG, UMGEditor, UnrealEd

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/AssetDefinition_WidgetPreview.h` (Private)


#### class `UAssetDefinition_WidgetPreview`  
`class UAssetDefinition_WidgetPreview : public UAssetDefinitionDefault`  
_L10-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `UAssetDefinition_WidgetPreview();`
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L21 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L24 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L25 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/Customizations/PreviewableWidgetCustomization.h` (Private)


#### class `UE::UMGWidgetPreview::Private::FPreviewableWidgetCustomization`  
`class FPreviewableWidgetCustomization : public IPropertyTypeCustomization`  
_L24-58_
- inherits: `IPropertyTypeCustomization`
- L28 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L31 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L32 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L36 _private prototype_ `bool GetCallInEditorFunctions(TArray<UFunction*>& OutCallInEditorFunctions) const;`
- L37 _private prototype_ `void AddCallInEditorFunctions(IDetailChildrenBuilder& ChildBuilder, const TArrayView<UFunction*>& InCallInEditorFunctions);`
- L39 _private prototype_ `TArray<TWeakObjectPtr<UObject>> GetFunctionCallExecutionContext(TWeakObjectPtr<UFunction> InWeakFunction) const;`
- L42 _private prototype_ `FReply OnExecuteCallInEditorFunction(TWeakObjectPtr<UFunction> InWeakFunction);` — Executes the specified method on the widget instance
- L45 _private prototype_ `bool CanExecuteCallInEditorFunction(TWeakObjectPtr<UFunction> InWeakFunction) const;` — Checks if the function can be called - ie. that it has an object to call with.
- L47 _private prototype_ `FPreviewableWidgetVariant* GetPreviewableWidgetVariant() const;`
- L48 _private prototype_ `UUserWidget* GetWidgetInstance() const;`
- L50 _private prototype_ `void OnWidgetChanged(const EWidgetPreviewWidgetChangeType InChangeType);`
- L53 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L54 _private member_ `TWeakObjectPtr<UWidgetPreview> WeakOwningPreview;`
- L55 _private member_ `TSharedPtr<IPropertyHandle> PreviewVariantHandle;`
- L56 _private member_ `TSharedPtr<IPropertyHandle> ObjectPathHandle;`
- L57 _private member_ `TWeakObjectPtr<UUserWidget> WeakWidgetInstance;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/Customizations/WidgetPreviewCustomization.h` (Private)


#### class `UE::UMGWidgetPreview::Private::FWidgetPreviewCustomization`  
`class FWidgetPreviewCustomization : public IDetailCustomization`  
_L25-40_
- inherits: `IDetailCustomization`
- L29 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L32 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L36 _private member_ `static const FName WidgetTypePropertyName;`
- L37 _private member_ `static const FName SlotWidgetTypesPropertyName;`
- L38 _private member_ `static const FName WidgetInstancePropertyName;`
- L39 _private member_ `static const FName OverriddenSizePropertyName;`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L23 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/UMGWidgetPreviewModule.h` (Private)


#### class `UE::UMGWidgetPreview::Private::FUMGWidgetPreviewModule`  
`class FUMGWidgetPreviewModule : public IUMGWidgetPreviewModule`  
_L9-27_
- inherits: `IUMGWidgetPreviewModule`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _public prototype_ `virtual FOnRegisterTabs& OnRegisterTabsForEditor() override;`
- L23 _private prototype_ `void RegisterMenus();`
- L26 _private member_ `FOnRegisterTabs RegisterTabsForEditorDelegate;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/WidgetPreviewCommands.h` (Private)


#### class `UE::UMGWidgetPreview::Private::FWidgetPreviewCommands`  
`class FWidgetPreviewCommands : public TCommands<FWidgetPreviewCommands>`  
_L9-24_
- inherits: `TCommands<FWidgetPreviewCommands>`
- L13 _public prototype_ `FWidgetPreviewCommands();`
- L16 _public prototype_ `virtual void RegisterCommands() override;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> OpenEditor;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ResetPreview;` — Resets the state of the given preview.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/WidgetPreviewEditor.h` (Private)


#### class `UWidgetPreviewEditor`  
`class UWidgetPreviewEditor : public UAssetEditor`  
_L17-49_
- reflection: `UCLASS(Transient)`
- inherits: `UAssetEditor`
- desc: Minimalistic container to spawn the toolkit.
- L23 _public prototype_ `void Initialize(const TObjectPtr<UWidgetPreview>& InWidgetPreview);`
- L26 _public prototype_ `virtual void GetObjectsToEdit(TArray<UObject*>& InObjectsToEdit) override;`
- L27 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;`
- L28 _public prototype_ `virtual void FocusWindow(UObject* ObjectToFocusOn) override;`
- L31 _public prototype_ `UWidgetPreview* GetObjectToEdit() const;`
- L34 _public prototype_ `static bool AreObjectsValidTargets(const TArray<UObject*>& InObjects);` — Checks that all of the objects are valid targets for a Widget Preview session.
- L42 _public prototype_ `static bool AreAssetsValidTargets(const TArray<FAssetData>& InAssets);` — Checks that all of the assets are valid targets for an editor session. This is preferable over AreObjectsValidTargets when we have FAssetData because it allows us to avoid forcing a load of the underlying UObjects (for instance to avoid triggering a load when right clicking an asset in the content browser).
- L45 _public prototype_ `static UWidgetPreview* CreatePreviewForWidget(const UUserWidget* InUserWidget);` — Creates a new, unsaved Widget Preview asset for the given UUserWidget.
- L48 _private member_ `TObjectPtr<UWidgetPreview> WidgetPreview = nullptr;`

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/WidgetPreviewFactory.h` (Private)


#### class `UWidgetPreviewFactory`  
`class UWidgetPreviewFactory : public UFactory`  
_L10-20_
- reflection: `UCLASS(HideCategories = Object, CollapseCategories, MinimalAPI)`
- inherits: `UFactory`
- L15 _public prototype_ `UWidgetPreviewFactory();`
- L18 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/WidgetPreviewLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)
- L9 _variable_ `static const FLazyName MessageLogName = "Wi` (scope `UE::UMGWidgetPreview::Private`)
- L12 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWidgetPreview, VeryVerbose, All);`
- L12 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWidgetPreview, VeryVerbose, All);`

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/WidgetPreviewStyle.h` (Private)


#### class `UE::UMGWidgetPreview::Private::FWidgetPreviewStyle`  
`class FWidgetPreviewStyle : public FSlateStyleSet`  
_L10-21_
- inherits: `FSlateStyleSet`
- L14 _public member_ `static FName StyleName;`
- L16 _public prototype_ `static FWidgetPreviewStyle& Get();`
- L19 _private prototype_ `FWidgetPreviewStyle();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/WidgetPreviewToolkit.h` (Private)


#### struct `UE::UMGWidgetPreview::Private::FWidgetPreviewabilityFixer`  
`struct FWidgetPreviewabilityFixer : DataValidation::IFixer`  
_L23-31_
- inherits: `DataValidation::IFixer`
- L25 _public prototype_ `virtual EFixApplicability GetApplicability(int32 FixIndex) const override;`
- L26 _public prototype_ `virtual FFixResult ApplyFix(int32 FixIndex) override;`
- L28 _public member_ `TWeakObjectPtr<const UUserWidget> WeakUserWidget;`
- L30 _public prototype_ `static TSharedRef<FWidgetPreviewabilityFixer> Create(const UUserWidget* InUserWidget);`

#### class `UE::UMGWidgetPreview::Private::FWidgetPreviewScene`  
`class FWidgetPreviewScene : public FTickableEditorObject`  
_L36-57_
- inherits: `FTickableEditorObject`
- desc: Encapsulates the state needed to run the preview world.
- L40 _public prototype_ `explicit FWidgetPreviewScene(const TSharedRef<FWidgetPreviewToolkit>& InPreviewToolkit);`
- L41 _public prototype_ `virtual ~FWidgetPreviewScene() override = default;`
- L44 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L45 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L46 _public prototype_ `virtual TStatId GetStatId() const override;`
- L50 _public prototype_ `UWorld* GetWorld() const;`
- L52 _public prototype_ `TSharedRef<FAdvancedPreviewScene> GetPreviewScene() const;`
- L55 _private member_ `TWeakPtr<FWidgetPreviewToolkit> WeakToolkit;`
- L56 _private member_ `TSharedPtr<FAdvancedPreviewScene> PreviewScene;`

#### struct `UE::UMGWidgetPreview::Private::FWidgetPreviewToolkitStateBase`  
`struct FWidgetPreviewToolkitStateBase`  
_L59-78_
- L61 _public prototype_ `explicit FWidgetPreviewToolkitStateBase(const FName& Id);`
- L63 _public prototype_ `virtual ~FWidgetPreviewToolkitStateBase() = default;`
- L65 _public prototype_ `FName GetId() const;`
- L66 _public prototype_ `const TSharedPtr<FTokenizedMessage>& GetStatusMessage() const;`
- L67 _public prototype_ `bool CanTick() const;`
- L68 _public prototype_ `bool ShouldOverlayStatusMessage() const;`
- L70 _public prototype_ `virtual void OnEnter(const FWidgetPreviewToolkitStateBase* InFromState);`
- L71 _public prototype_ `virtual void OnExit(const FWidgetPreviewToolkitStateBase* InToState);`
- L74 _protected member_ `FName Id;`
- L75 _protected member_ `TSharedPtr<FTokenizedMessage> StatusMessage;`
- L76 _protected member_ `bool bCanTick = false;`
- L77 _protected member_ `bool bShouldOverlayMessage = false;`

#### struct `UE::UMGWidgetPreview::Private::FWidgetPreviewToolkitPausedState`  
`struct FWidgetPreviewToolkitPausedState : FWidgetPreviewToolkitStateBase`  
_L80-83_
- inherits: `FWidgetPreviewToolkitStateBase`
- L82 _public prototype_ `FWidgetPreviewToolkitPausedState();`

#### struct `UE::UMGWidgetPreview::Private::FWidgetPreviewToolkitBackgroundState`  
`struct FWidgetPreviewToolkitBackgroundState : FWidgetPreviewToolkitPausedState`  
_L85-88_
- inherits: `FWidgetPreviewToolkitPausedState`
- L87 _public prototype_ `FWidgetPreviewToolkitBackgroundState();`

#### struct `UE::UMGWidgetPreview::Private::FWidgetPreviewToolkitUnsupportedWidgetState`  
`struct FWidgetPreviewToolkitUnsupportedWidgetState : FWidgetPreviewToolkitPausedState`  
_L90-101_
- inherits: `FWidgetPreviewToolkitPausedState`
- L92 _public prototype_ `FWidgetPreviewToolkitUnsupportedWidgetState();`
- L94 _public prototype_ `void SetUnsupportedWidgets(const TArray<const UUserWidget*>& InWidgets);`
- L97 _private prototype_ `void ResetStatusMessage();`
- L100 _private member_ `TArray<TWeakObjectPtr<const UUserWidget>> UnsupportedWidgets;`

#### struct `UE::UMGWidgetPreview::Private::FWidgetPreviewToolkitRunningState`  
`struct FWidgetPreviewToolkitRunningState : FWidgetPreviewToolkitStateBase`  
_L103-106_
- inherits: `FWidgetPreviewToolkitStateBase`
- L105 _public prototype_ `FWidgetPreviewToolkitRunningState();`

#### class `UE::UMGWidgetPreview::Private::FWidgetPreviewToolkit`  
`class FWidgetPreviewToolkit : public FBaseAssetToolkit , public FGCObject , public IWidgetPreviewToolkit`  
_L108-219_
- inherits: `FBaseAssetToolkit,FGCObject,IWidgetPreviewToolkit`
- L114 _public prototype_ `explicit FWidgetPreviewToolkit(UWidgetPreviewEditor* InOwningEditor);`
- L118 _public prototype_ `virtual void CreateWidgets() override;`
- L119 _public prototype_ `virtual void RegisterToolbar() override;`
- L123 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L124 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;`
- L125 _public prototype_ `virtual void PostInitAssetEditor() override;`
- L126 _public prototype_ `virtual bool CanSaveAsset() const override;`
- L127 _public prototype_ `virtual void SaveAsset_Execute() override;`
- L128 _public prototype_ `virtual bool IsSaveAssetAsVisible() const override;`
- L129 _public prototype_ `virtual void SaveAssetAs_Execute() override;`
- L130 _public prototype_ `virtual void GetSaveableObjects(TArray<UObject*>& OutObjects) const override;`
- L134 _public prototype_ `virtual FText GetToolkitName() const override;`
- L135 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L136 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L137 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L138 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L142 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L143 _public prototype_ `virtual FString GetReferencerName() const override;`
- L147 _public prototype_ `virtual TSharedPtr<FLayoutExtender> GetLayoutExtender() const override;`
- L148 _public prototype_ `virtual FOnSelectedObjectsChanged& OnSelectedObjectsChanged() override;`
- L149 _public prototype_ `virtual TConstArrayView<TWeakObjectPtr<UObject>> GetSelectedObjects() const override;`
- L150 _public prototype_ `virtual void SetSelectedObjects(const TArray<TWeakObjectPtr<UObject>>& InObjects) override;`
- L151 _public prototype_ `virtual UWidgetPreview* GetPreview() const override;`
- L152 _public prototype_ `virtual UWorld* GetPreviewWorld() override;`
- L155 _public prototype_ `FWidgetPreviewToolkitStateBase* GetState() const;`
- L157 _public typedef_ `using FOnStateChanged = TMulticastDelegate<void(FWidgetPreviewToolkitStateBase* InOldState, FWidgetPreviewToolkitStateBase* InNewState)>;`
- L158 _public prototype_ `FOnStateChanged& OnStateChanged();`
- L159 _public prototype_ `FSimpleMulticastDelegate& OnMessageChanged();`
- L161 _public prototype_ `TSharedPtr<FWidgetPreviewScene> GetPreviewScene();`
- L164 _public member_ `static const FLazyName PreviewSceneSettingsTabID;`
- L165 _public member_ `static const FLazyName MessageLogTabID;`
- L168 _protected prototype_ `bool ShouldUpdate() const;`
- L170 _protected prototype_ `void OnBlueprintPrecompile(UBlueprint* InBlueprint);`
- L172 _protected prototype_ `void OnWidgetChanged(const EWidgetPreviewWidgetChangeType InChangeType);`
- L174 _protected prototype_ `void OnFocusChanging( const FFocusEvent& InFocusEvent, const FWeakWidgetPath& InOldWidgetPath, const TSharedPtr<SWidget>& InOldWidget, const FWidgetPath& InNewWidgetPath, const TSharedPtr<SWidget>& InNewWidget);`
- L180 _protected prototype_ `bool SetState(FWidgetPreviewToolkitStateBase* InNewState);` — If the given state is different to the current state, this will handle transitions and events. Returns true if the state changed.
- L183 _protected prototype_ `void ResolveState();` — Resolve and set the current state based on various conditions.
- L186 _protected prototype_ `void ResetPreview();` — Resets to the default state.
- L188 _protected prototype_ `virtual TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args) override;`
- L189 _protected prototype_ `virtual TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args) override;`
- L190 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewSceneSettings(const FSpawnTabArgs& Args);`
- L191 _protected prototype_ `TSharedRef<SDockTab> SpawnTab_MessageLog(const FSpawnTabArgs& Args);`
- L194 _private member_ `TObjectPtr<UWidgetPreview> Preview;`
- L196 _private member_ `FOnSelectedObjectsChanged SelectedObjectsChangedDelegate;`
- L197 _private member_ `TArray<TWeakObjectPtr<UObject>> SelectedObjects;`
- L199 _private member_ `TSharedPtr<FWidgetPreviewScene> PreviewScene;`
- L200 _private member_ `FAdvancedPreviewSceneModule::FOnPreviewSceneChanged OnPreviewSceneChangedDelegate;`
- L201 _private member_ `TSharedPtr<SWidget> PreviewSettingsWidget;`
- L203 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;`
- L204 _private member_ `TSharedPtr<SWidget> MessageLogWidget;`
- L206 _private member_ `bool bIsFocused = false;`
- L208 _private member_ `FDelegateHandle OnBlueprintPrecompileHandle;`
- L209 _private member_ `FDelegateHandle OnWidgetChangedHandle;`
- L210 _private member_ `FDelegateHandle OnFocusChangingHandle;`
- L211 _private member_ `FOnStateChanged OnStateChangedDelegate;`
- L212 _private member_ `FSimpleMulticastDelegate OnMessageChangedDelegate;` — Called when state doesn't change, but the message still needs to update.
- L214 _private member_ `FWidgetPreviewToolkitStateBase* CurrentState = nullptr;`
- L215 _private member_ `FWidgetPreviewToolkitPausedState PausedState;`
- L216 _private member_ `FWidgetPreviewToolkitBackgroundState BackgroundState;`
- L217 _private member_ `FWidgetPreviewToolkitUnsupportedWidgetState UnsupportedWidgetState;`
- L218 _private member_ `FWidgetPreviewToolkitRunningState RunningState;`

#### Free symbols / members of external scopes

- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L21 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/WidgetPreviewTypesPrivate.h` (Private)


#### struct `UE::UMGWidgetPreview::Private::FWidgetTypeTuple`  
`struct FWidgetTypeTuple`  
_L11-44_
- L13 _public prototype_ `FWidgetTypeTuple() = default;`
- L15 _public function_ `explicit FWidgetTypeTuple(const UUserWidget* InUserWidgetCDO) : bIsValid(true)`
- L22 _public function_ `void Set(const UUserWidget* InUserWidgetCDO)` — Attempt to resolve the tuple from the given UserWidget CDO.
- L31 _public member_ `const UUserWidget* ClassDefaultObject = nullptr;`
- L32 _public member_ `UWidgetBlueprint* Blueprint = nullptr;`
- L33 _public member_ `UWidgetBlueprintGeneratedClass* BlueprintGeneratedClass = nullptr;`
- L36 _public function_ `inline bool IsValid() const` — Returns true if at least one of the tuple values is valid.
- L43 _private member_ `bool bIsValid = false;` — True only when value resolution has been attempted.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/Widgets/SWidgetPreview.h` (Private)


#### class `UE::UMGWidgetPreview::Private::SWidgetPreview`  
`class SWidgetPreview : public SCompoundWidget`  
_L23-68_
- inherits: `SCompoundWidget`
- L27 _public typedef_ `using FSlotWidgetMap = TMap<FName, TObjectPtr<UWidget>>;`
- L29 _public function_ `SLATE_BEGIN_ARGS(SWidgetPreview)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<FWidgetPreviewToolkit>& InToolkit);`
- L36 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L39 _private prototype_ `void OnStateChanged(FWidgetPreviewToolkitStateBase* InOldState, FWidgetPreviewToolkitStateBase* InNewState);`
- L40 _private prototype_ `void OnWidgetChanged(const EWidgetPreviewWidgetChangeType InChangeType);`
- L43 _private prototype_ `UWorld* GetWorld() const;` — Convenience method to get world from the associated viewport.
- L45 _private prototype_ `TSharedRef<SWidget> GetCreatedSlateWidget() const;`
- L47 _private prototype_ `void RebuildContainer();`
- L48 _private prototype_ `FText GetPreviewSizeText() const;`
- L51 _private member_ `TWeakPtr<FWidgetPreviewToolkit> WeakToolkit;`
- L53 _private member_ `TSharedPtr<SRetainerWidget> RetainerWidget;`
- L54 _private member_ `TSharedPtr<SBorder> ContainerWidget;`
- L55 _private member_ `TSharedPtr<SBox> SizeBoxWidget;`
- L56 _private member_ `TWeakPtr<SWidget> CreatedSlateWidget;`
- L57 _private member_ `SOverlay::FOverlaySlot* OverlaySlot;`
- L59 _private member_ `bool bClearWidgetOnNextPaint = false;`
- L60 _private member_ `bool bIsRetainedRender = false;`
- L61 _private member_ `bool bSizeOverridden = false;`
- L63 _private member_ `FDelegateHandle OnStateChangedHandle;`
- L64 _private member_ `FDelegateHandle OnWidgetChangedHandle;`
- L66 _private member_ `EDesignPreviewSizeMode CreatedWidgetPreviewSizeMode;`
- L67 _private member_ `FVector2D CreatedWidgetPreviewCustomSize;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L18 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/Widgets/SWidgetPreviewDetails.h` (Private)


#### class `UE::UMGWidgetPreview::Private::SWidgetPreviewDetails`  
`class SWidgetPreviewDetails : public SCompoundWidget , public FNotifyHook`  
_L17-38_
- inherits: `SCompoundWidget,FNotifyHook`
- L21 _private function_ `SLATE_BEGIN_ARGS(SWidgetPreviewDetails)`
- L22 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<FWidgetPreviewToolkit>& InToolkit);`
- L28 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged) override;`
- L31 _private prototype_ `void OnSelectedObjectChanged(const TConstArrayView<TWeakObjectPtr<UObject>> InSelectedObjects) const;`
- L34 _private member_ `TWeakPtr<FWidgetPreviewToolkit> WeakToolkit;`
- L35 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L37 _private member_ `FDelegateHandle OnSelectedObjectsChangedHandle;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L13 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/Widgets/SWidgetPreviewStatus.h` (Private)


#### class `UE::UMGWidgetPreview::Private::SWidgetPreviewStatus`  
`class SWidgetPreviewStatus : public SCompoundWidget`  
_L17-46_
- inherits: `SCompoundWidget`
- L20 _private function_ `SLATE_BEGIN_ARGS(SWidgetPreviewStatus)`
- L21 _private prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<FWidgetPreviewToolkit>& InToolkit);`
- L28 _private prototype_ `void OnStateChanged(FWidgetPreviewToolkitStateBase* InOldState, FWidgetPreviewToolkitStateBase* InNewState);`
- L29 _private prototype_ `void OnMessageChanged();`
- L31 _private prototype_ `TSharedRef<SWidget> MakeMessageWidget();`
- L33 _private prototype_ `TSharedPtr<FTokenizedMessage> GetStatusMessage() const;`
- L35 _private prototype_ `EVisibility GetStatusVisibility() const;`
- L36 _private prototype_ `const FSlateBrush* GetSeverityIconBrush() const;`
- L37 _private prototype_ `EMessageSeverity::Type GetSeverity() const;`
- L38 _private prototype_ `FText GetMessage() const;`
- L41 _private member_ `TWeakPtr<FWidgetPreviewToolkit> WeakToolkit;`
- L42 _private member_ `TSharedPtr<SBox> MessageContainerWidget;`
- L44 _private member_ `FDelegateHandle OnStateChangedHandle;`
- L45 _private member_ `FDelegateHandle OnMessageChangedHandle;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L15 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Private/Widgets/SWidgetPreviewViewport.h` (Private)


#### class `UE::UMGWidgetPreview::Private::SWidgetPreviewViewport`  
`class SWidgetPreviewViewport : public SEditorViewport`  
_L11-26_
- inherits: `SEditorViewport`
- L15 _public function_ `SLATE_BEGIN_ARGS(SWidgetPreviewViewport)`
- L16 _public prototype_ `SLATE_ATTRIBUTE(FVector2D, ViewportSize);`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FWidgetPreviewToolkit>& InToolkit);`
- L22 _private prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L25 _private member_ `TWeakPtr<FWidgetPreviewToolkit> WeakToolkit;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L7 _namespace_ `namespace Private` (scope `UE::UMGWidgetPreview`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Public/IUMGWidgetPreviewModule.h` (Public)


#### class `IUMGWidgetPreviewModule`  
`class IUMGWidgetPreviewModule : public IModuleInterface`  
_L19-25_
- inherits: `IModuleInterface`
- desc: The public interface of the UMG widget preview (editor) module.
- L23 _public prototype_ `DECLARE_EVENT_TwoParams(IUMGWidgetPreviewModule, FOnRegisterTabs, const TSharedPtr<UE::UMGWidgetPreview::IWidgetPreviewToolkit>&, const TSharedRef<FTabManager>&);`
- L24 _public prototype_ `virtual FOnRegisterTabs& OnRegisterTabsForEditor() = 0;`

#### Free symbols / members of external scopes

- L11 _externvar_ `extern const FLazyName UMGWidgetPreviewAppIdentifier;`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)
- L23 _delegate_ `DECLARE_EVENT_TwoParams(IUMGWidgetPreviewModule, FOnRegisterTabs, const TSharedPtr<UE::UMGWidgetPreview::IWidgetPreviewToolkit>&, const TSharedRef<FTabManager>&);`

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Public/IWidgetPreviewToolkit.h` (Public)


#### class `UE::UMGWidgetPreview::IWidgetPreviewToolkit`  
`class IWidgetPreviewToolkit`  
_L14-34_
- L17 _public prototype_ `virtual ~IWidgetPreviewToolkit() = default;`
- L19 _public prototype_ `virtual TSharedPtr<FLayoutExtender> GetLayoutExtender() const = 0;`
- L21 _public typedef_ `using FOnSelectedObjectsChanged = TMulticastDelegate<void(const TConstArrayView<TWeakObjectPtr<UObject>>)>;`
- L22 _public prototype_ `virtual FOnSelectedObjectsChanged& OnSelectedObjectsChanged() = 0;`
- L25 _public prototype_ `virtual TConstArrayView<TWeakObjectPtr<UObject>> GetSelectedObjects() const = 0;` — Gets the "selected" objects, primarily used to display details for a given object/s other than the preview asset itself.
- L28 _public prototype_ `virtual void SetSelectedObjects(const TArray<TWeakObjectPtr<UObject>>& InObjects) = 0;` — Sets the selected objects. When empty, this will reset to the Preview asset.
- L30 _public prototype_ `virtual UWidgetPreview* GetPreview() const = 0;`
- L33 _public prototype_ `virtual UWorld* GetPreviewWorld() = 0;` — Returns the Preview World.

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace UMGWidgetPreview` (scope `UE`)

### `Plugins/Editor/UMGWidgetPreview/Source/UMGWidgetPreview/Public/WidgetPreview.h` (Public)


#### enum `EWidgetPreviewWidgetChangeType`  
`enum class EWidgetPreviewWidgetChangeType : uint8`  
_L19-27_
- L21 _public enumerator_ `Assignment = 0`
- L22 _public enumerator_ `Reinstanced = 1`
- L23 _public enumerator_ `Structure = 2`
- L24 _public enumerator_ `ChildReference = 3`
- L25 _public enumerator_ `Destroyed = 4` — Just before the Slate widget is destroyed, etc.
- L26 _public enumerator_ `Resized = 5`

#### struct `FPreviewableWidgetVariant`  
`struct FPreviewableWidgetVariant`  
_L30-67_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public member_ `FSoftObjectPath ObjectPath;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Widget", DisplayName = "Widget Type", meta = (AllowedClasses = "/Script/UMGEditor.WidgetBlueprint, /Script/UMGWidgetPreview.WidgetPreview"))`
- L37 _public prototype_ `FPreviewableWidgetVariant() = default;`
- L38 _public prototype_ `explicit FPreviewableWidgetVariant(const TSubclassOf<UUserWidget>& InWidgetType);`
- L39 _public prototype_ `explicit FPreviewableWidgetVariant(const UWidgetPreview* InWidgetPreview);`
- L43 _public prototype_ `void UpdateCachedWidget();` — Flushes cached widgets and re-resolves from the ObjectPath.
- L46 _public prototype_ `const UUserWidget* AsUserWidgetCDO() const;` — Returns the referenced Object as a UUserWidget (CDO). Returns nullptr if not found, or we couldn't find a nested UUserWidget (ie. inside a UWidgetPreview).
- L49 _public prototype_ `const UWidgetPreview* AsWidgetPreview() const;` — Returns the referenced Object as a UWidgetPreview. Returns nullptr if not found, or not a UWidgetPreview.
- L63 _private member_ `TObjectPtr<const UUserWidget> CachedWidgetCDO;` — `UPROPERTY(Transient)`
- L66 _private member_ `TWeakObjectPtr<UWidgetPreview> CachedWidgetPreview;` — `UPROPERTY(Transient)`

#### class `UWidgetPreview`  
`class UWidgetPreview : public UObject`  
_L70-179_
- reflection: `UCLASS(MinimalAPI, BlueprintType, NotBlueprintable, AutoExpandCategories = "Widgets")`
- inherits: `UObject`
- L77 _public prototype_ `UWidgetPreview(const FObjectInitializer& ObjectInitializer);`
- L79 _public prototype_ `virtual void BeginDestroy() override;`
- L82 _public prototype_ `bool CanCallInitializedWithoutPlayerContext(const bool bInRecursive, TArray<const UUserWidget*>& OutFailedWidgets);` — Convenience function to check that all utilized widgets have bCanCallInitializedWithoutPlayerContext set to true, and reports any that don't.
- L86 _public prototype_ `static bool CanCallInitializedWithoutPlayerContextOnWidget(const UUserWidget* InUserWidget, const bool bInRecursive, TArray<const UUserWidget*>& OutFailedWidgets);` — Convenience function to check that the provided widget (and it's children) has bCanCallInitializedWithoutPlayerContext set to true, and reports any that don't.
- L89 _public typedef_ `using FOnWidgetChanged = TMulticastDelegate<void(const EWidgetPreviewWidgetChangeType)>;`
- L91 _public function_ `FOnWidgetChanged& OnWidgetChanged()`
- L94 _public prototype_ `const TArray<FName>& GetWidgetSlotNames() const;` — `UFUNCTION(BlueprintCallable, Category = "Layout")`
- L97 _public prototype_ `[[maybe_unused]] UUserWidget* GetOrCreateWidgetInstance(UWorld* InWorld, const bool bInForceRecreate = false);` — Returns or builds and returns an instance of the root widget for previewing. Can be used to trigger a rebuild.
- L100 _public prototype_ `UUserWidget* GetWidgetInstance() const;` — Returns the current widget instance, if any.
- L103 _public prototype_ `TSharedPtr<SWidget> GetSlateWidgetInstance() const;` — Returns the current underlying slate widget instance, if any.
- L106 _public prototype_ `void ClearWidgetInstance();` — Stores the current instance in PreviousWidgetInstance, and clears WidgetInstance.
- L108 _public prototype_ `const UUserWidget* GetWidgetCDO() const;`
- L109 _public prototype_ `const UUserWidget* GetWidgetCDOForSlot(const FName InSlotName) const;`
- L111 _public prototype_ `const FPreviewableWidgetVariant& GetWidgetType() const;`
- L112 _public prototype_ `void SetWidgetType(const FPreviewableWidgetVariant& InWidget);`
- L114 _public prototype_ `const TMap<FName, FPreviewableWidgetVariant>& GetSlotWidgetTypes() const;`
- L115 _public prototype_ `void SetSlotWidgetTypes(const TMap<FName, FPreviewableWidgetVariant>& InWidgets);`
- L117 _public prototype_ `const bool GetbShouldOverrideWidgetSize() const;`
- L118 _public prototype_ `void SetbShouldOverrideWidgetSize(bool InOverride);`
- L120 _public prototype_ `const FVector2D GetOverriddenWidgetSize() const;`
- L121 _public prototype_ `void SetOverriddenWidgetSize(FVector2D InWidgetSize);`
- L123 _public prototype_ `bool ShouldDefaultConstructViewmodels() const;`
- L124 _public prototype_ `void SetDefaultConstructViewmodels(bool bInDefaultConstruct);`
- L127 _protected prototype_ `virtual void PostLoad() override;`
- L129 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L131 _protected prototype_ `void OnWidgetBlueprintChanged(UBlueprint* InBlueprint);`
- L134 _protected prototype_ `void UpdateWidgets();` — Misc. functionality to perform after a widget assignment is changed.
- L137 _protected prototype_ `UUserWidget* CreateWidgetInstance(UWorld* InWorld);` — Creates a new WidgetInstance, replacing the current one if it exists.
- L139 _protected prototype_ `void CleanupReferences();`
- L143 _protected prototype_ `TArray<FName> GetAvailableWidgetSlotNames();` — `UFUNCTION(BlueprintCallable, Category = "Widget")` — Returns slot names not already occupied in SlotWidgets.
- L148 _private member_ `FPreviewableWidgetVariant WidgetType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Widget", DisplayName = "Widget", meta = (AllowPrivateAccess = "true", ShowOnlyInnerProperties))` — Widget to preview.
- L152 _private member_ `TMap<FName, FPreviewableWidgetVariant> SlotWidgetTypes;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Widget", DisplayName = "Slot Widgets", meta = (AllowPrivateAccess = "true", GetKeyOptions = "GetAvailableWidgetSlotNames", ShowOnlyInnerProperties))` — Widget per-slot, if WidgetType has any.
- L156 _private member_ `bool bShouldOverrideWidgetSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Widget", DisplayName = "Override Widget Size", meta = (AllowPrivateAccess = "true", InlineEditConditionToggle))` — Widget Custom Size Override
- L159 _private member_ `FVector2D OverriddenWidgetSize;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter, Setter, Category = "Widget", DisplayName = "Widget Size", meta = (AllowPrivateAccess = "true", EditCondition="bShouldOverrideWidgetSize"))`
- L163 _private member_ `bool bDefaultConstructViewmodels;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Getter = ShouldDefaultConstructViewmodels, Setter = SetDefaultConstructViewmodels, Category = "Widget", meta = (AllowPrivateAccess = "true"))` — When this preview is opened in the previewer, automatically construct any missing viewmodels.
- L166 _private member_ `TObjectPtr<UUserWidget> WidgetInstance;` — `UPROPERTY(DuplicateTransient)`
- L168 _private member_ `TSharedPtr<SWidget> SlateWidgetInstance;`
- L172 _private member_ `TArray<FName> SlotNameCache;` — `UPROPERTY(Transient)` — Slot names available in WidgetType (if any).
- L176 _private member_ `TArray<TWeakObjectPtr<const UUserWidget>> WidgetReferenceCache;` — `UPROPERTY(Transient)` — Widgets here should be checked for validity when a new one is assigned, to allow tear-down functionality.
- L178 _private member_ `FOnWidgetChanged OnWidgetChangedDelegate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UMGWIDGETPREVIEW_API`
- L51 _function_ `friend bool operator==(const FPreviewableWidgetVariant& Left, const FPreviewableWidgetVariant& Right)`
- L56 _function_ `friend bool operator!=(const FPreviewableWidgetVariant& Left, const FPreviewableWidgetVariant& Right)`
