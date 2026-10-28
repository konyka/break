# Editor / GameplayDebuggerEditor

- module root: `Source/Editor/GameplayDebugger`
- headers: 6; symbols: 67
- symbol kinds: class=6, function=11, member=20, prototype=30
- PrivateDependencyModuleNames: DeveloperSettings, DrawPrimitiveDebugger, EditorFramework, GameplayDebugger, InputCore, LevelEditor, PropertyEditor, RenderCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Editor/GameplayDebugger/Public/GameplayDebuggerCategoryConfigCustomization.h` (Public)


#### class `FGameplayDebuggerCategoryConfigCustomization`  
`class FGameplayDebuggerCategoryConfigCustomization : public IPropertyTypeCustomization`  
_L11-32_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _protected member_ `TSharedPtr<IPropertyHandle> CategoryNameProp;`
- L24 _protected member_ `TSharedPtr<IPropertyHandle> SlotIdxProp;`
- L25 _protected member_ `TSharedPtr<IPropertyHandle> ActiveInGameProp;`
- L26 _protected member_ `TSharedPtr<IPropertyHandle> ActiveInSimulateProp;`
- L28 _protected member_ `FText CachedHeader;`
- L29 _protected function_ `FText GetHeaderDesc() const`
- L31 _protected prototype_ `void OnChildValueChanged();`

### `Source/Editor/GameplayDebugger/Public/GameplayDebuggerEdMode.h` (Public)


#### class `FGameplayDebuggerEdMode`  
`class FGameplayDebuggerEdMode : public FEdMode`  
_L12-38_
- inherits: `FEdMode`
- L15 _public function_ `FGameplayDebuggerEdMode() : FocusedViewport(nullptr)`
- L18 _public function_ `virtual bool UsesToolkits() const override` — FEdMode interface
- L19 _public prototype_ `virtual void Enter() override;`
- L20 _public prototype_ `virtual void Exit() override;`
- L21 _public prototype_ `virtual bool ReceivedFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L22 _public prototype_ `virtual bool LostFocus(FEditorViewportClient* ViewportClient, FViewport* Viewport) override;`
- L23 _public prototype_ `virtual bool InputKey(FEditorViewportClient* InViewportClient, FViewport* InViewport, FKey InKey, EInputEvent InEvent) override;`
- L24 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient, float DeltaTime);`
- L25 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L28 _public prototype_ `static void SafeOpenMode();`
- L29 _public prototype_ `static void SafeCloseMode();`
- L31 _public member_ `static const FName EM_GameplayDebugger;`
- L34 _private member_ `FEditorViewportClient* FocusedViewport;`
- L35 _private member_ `bool bPrevGAreScreenMessagesEnabled;`
- L37 _private prototype_ `void EnableViewportClientFlags(FEditorViewportClient* ViewportClient, bool bEnable);`

### `Source/Editor/GameplayDebugger/Public/GameplayDebuggerEditorModule.h` (Public)


#### class `FGameplayDebuggerEditorModule`  
`class FGameplayDebuggerEditorModule : public IModuleInterface`  
_L10-21_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L16 _public prototype_ `void OnWorldInitialized(UWorld* World, const UWorld::InitializationValues IVS);`
- L18 _public prototype_ `void OnLocalControllerInitialized();`
- L19 _public prototype_ `void OnLocalControllerUninitialized();`
- L20 _public prototype_ `void OnDebuggerEdModeActivation();`

### `Source/Editor/GameplayDebugger/Public/GameplayDebuggerExtensionConfigCustomization.h` (Public)


#### class `FGameplayDebuggerExtensionConfigCustomization`  
`class FGameplayDebuggerExtensionConfigCustomization : public IPropertyTypeCustomization`  
_L11-30_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _protected member_ `TSharedPtr<IPropertyHandle> ExtensionNameProp;`
- L24 _protected member_ `TSharedPtr<IPropertyHandle> UseExtensionProp;`
- L26 _protected member_ `FText CachedHeader;`
- L27 _protected function_ `FText GetHeaderDesc() const`
- L29 _protected prototype_ `void OnChildValueChanged();`

### `Source/Editor/GameplayDebugger/Public/GameplayDebuggerInputConfigCustomization.h` (Public)


#### class `FGameplayDebuggerInputConfigCustomization`  
`class FGameplayDebuggerInputConfigCustomization : public IPropertyTypeCustomization`  
_L11-34_
- inherits: `IPropertyTypeCustomization`
- L14 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L23 _protected member_ `TSharedPtr<IPropertyHandle> ConfigNameProp;`
- L24 _protected member_ `TSharedPtr<IPropertyHandle> KeyProp;`
- L25 _protected member_ `TSharedPtr<IPropertyHandle> ModShiftProp;`
- L26 _protected member_ `TSharedPtr<IPropertyHandle> ModCtrlProp;`
- L27 _protected member_ `TSharedPtr<IPropertyHandle> ModAltProp;`
- L28 _protected member_ `TSharedPtr<IPropertyHandle> ModCmdProp;`
- L30 _protected member_ `FText CachedHeader;`
- L31 _protected function_ `FText GetHeaderDesc() const`
- L33 _protected prototype_ `void OnChildValueChanged();`

### `Source/Editor/GameplayDebugger/Public/GameplayDebuggerToolkit.h` (Public)


#### class `FGameplayDebuggerToolkit`  
`class FGameplayDebuggerToolkit : public FModeToolkit`  
_L13-35_
- inherits: `FModeToolkit`
- L16 _public prototype_ `FGameplayDebuggerToolkit(class FEdMode* InOwningMode);`
- L19 _public prototype_ `virtual FText GetBaseToolkitName() const override;` — IToolkit interface
- L20 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L21 _public function_ `virtual class FEdMode* GetEditorMode() const override`
- L22 _public function_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override`
- L26 _public prototype_ `virtual void Init(const TSharedPtr<class IToolkitHost>& InitToolkitHost) override;` — FModeToolkit interface
- L30 _private member_ `class FEdMode* DebuggerEdMode;`
- L31 _private member_ `TSharedPtr<class SWidget> MyWidget;`
- L33 _private prototype_ `EVisibility GetScreenMessageWarningVisibility() const;`
- L34 _private prototype_ `FReply OnClickedDisableTool();`
