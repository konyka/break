# Plugins / LightMixer

- module root: `Plugins/Editor/ObjectMixer/LightMixer/Source/LightMixer`
- headers: 4; symbols: 35
- symbol kinds: class=4, function=10, macro=1, member=2, prototype=18
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, ContentBrowser, CoreUObject, EditorStyle, EditorWidgets, Engine, InputCore, Kismet, Projects, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, ObjectMixerEditor, OutputLog, PropertyEditor

### `Plugins/Editor/ObjectMixer/LightMixer/Source/LightMixer/Private/LightMixerStyle.h` (Private)


#### class `FLightMixerStyle`  
`class FLightMixerStyle : FSlateStyleSet`  
_L9-38_
- inherits: `FSlateStyleSet`
- L13 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static void ReloadTextures();`
- L19 _public prototype_ `static const ISlateStyle& Get();`
- L21 _public prototype_ `virtual const FName& GetStyleSetName() const override;`
- L23 _public prototype_ `virtual const FSlateBrush* GetBrush(const FName PropertyName, const ANSICHAR* Specifier = nullptr, const ISlateStyle* RequestingStyle = nullptr) const override;`
- L26 _public function_ `template< typename WidgetStyleType > static const WidgetStyleType& GetWidgetStyle(FName PropertyName, const ANSICHAR* Specifier = nullptr)`
- L33 _private prototype_ `static FString GetExternalPluginContent(const FString& PluginName, const FString& RelativePath, const ANSICHAR* Extension);`
- L35 _private prototype_ `static TSharedRef<FSlateStyleSet> Create();`
- L37 _private member_ `static TSharedPtr<FSlateStyleSet> StyleInstance;`

### `Plugins/Editor/ObjectMixer/LightMixer/Source/LightMixer/Public/LightMixerEditorSettings.h` (Public)


#### class `ULightMixerEditorSettings`  
`class ULightMixerEditorSettings : public UObject`  
_L8-22_
- reflection: `UCLASS(MinimalAPI, config = ObjectMixer)`
- inherits: `UObject`
- L13 _public function_ `ULightMixerEditorSettings(const FObjectInitializer& ObjectInitializer)`
- L21 _public member_ `bool bHideObjectMixerMenuItem = false;` — `UPROPERTY(Config, EditAnywhere, Category="Light Mixer", meta = (ConfigRestartRequired = true))` — If true, the Object Mixer menu item will be disabled and removed. This is useful if you only want to use Light Mixer and to avoid cluttering the menus.

### `Plugins/Editor/ObjectMixer/LightMixer/Source/LightMixer/Public/LightMixerModule.h` (Public)


#### class `FLightMixerModule`  
`class FLightMixerModule : public FObjectMixerEditorModule`  
_L9-30_
- inherits: `FObjectMixerEditorModule`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `static FLightMixerModule& Get();`
- L20 _public prototype_ `static void OpenProjectSettings();`
- L23 _public prototype_ `virtual void Initialize() override;`
- L24 _public prototype_ `virtual FName GetModuleName() const override;`
- L25 _public prototype_ `virtual void SetupMenuItemVariables() override;`
- L26 _public prototype_ `virtual FName GetTabSpawnerId() override;`
- L27 _public prototype_ `virtual void RegisterSettings() const override;`
- L28 _public prototype_ `virtual void UnregisterSettings() const override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API LIGHTMIXER_API`

### `Plugins/Editor/ObjectMixer/LightMixer/Source/LightMixer/Public/LightMixerObjectFilter.h` (Public)


#### class `ULightMixerObjectFilter`  
`class ULightMixerObjectFilter : public UObjectMixerObjectFilter`  
_L13-66_
- reflection: `UCLASS(MinimalAPI, BlueprintType, EditInlineNew)`
- inherits: `UObjectMixerObjectFilter`
- L18 _public function_ `virtual TSet<UClass*> GetObjectClassesToFilter() const override`
- L26 _public function_ `virtual TSet<TSubclassOf<AActor>> GetObjectClassesToPlace() const override`
- L34 _public function_ `virtual bool GetShowTransientObjects() const override`
- L39 _public function_ `virtual TSet<FName> GetColumnsToShowByDefault() const override`
- L47 _public function_ `virtual TSet<FName> GetForceAddedColumns() const override`
- L52 _public function_ `virtual bool ShouldIncludeUnsupportedProperties() const override`
- L57 _public function_ `virtual EObjectMixerInheritanceInclusionOptions GetObjectMixerPropertyInheritanceInclusionOptions() const override`
- L62 _public function_ `virtual EObjectMixerInheritanceInclusionOptions GetObjectMixerPlacementClassInclusionOptions() const override`
