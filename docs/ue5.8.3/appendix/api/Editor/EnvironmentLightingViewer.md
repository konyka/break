# Editor / EnvironmentLightingViewer

- module root: `Source/Editor/EnvironmentLightingViewer`
- headers: 2; symbols: 31
- symbol kinds: class=2, function=1, macro=1, member=11, prototype=16
- DynamicallyLoadedModuleNames: AssetRegistry, AssetTools, EditorWidgets
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, InputCore, Settings, Slate, SlateCore, UnrealEd
- PrivateIncludePathModuleNames: WorkspaceMenuStructure

### `Source/Editor/EnvironmentLightingViewer/Private/SEnvironmentLightingViewer.h` (Private)


#### class `SEnvironmentLightingViewer`  
`class SEnvironmentLightingViewer : public SCompoundWidget`  
_L32-83_
- inherits: `SCompoundWidget`
- L35 _public function_ `SLATE_BEGIN_ARGS(SEnvironmentLightingViewer)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `virtual TSharedRef<SWidget> GetContent();` — Gets the widget contents of the app
- L50 _public prototype_ `virtual ~SEnvironmentLightingViewer();`
- L53 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;` — SWidget interface
- L57 _private member_ `TSharedPtr<class IDetailsView> DetailsViews[ENVLIGHT_MAX_DETAILSVIEWS];`
- L58 _private member_ `FLinearColor DefaultForegroundColor;`
- L60 _private member_ `TSharedPtr<class SCheckBox> CheckBoxAtmosphericLightsOnly;`
- L62 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBoxDetailFilter;`
- L63 _private member_ `TArray<TSharedPtr<FString>> ComboBoxDetailFilterOptions;`
- L64 _private member_ `int32 SelectedComboBoxDetailFilterOptions;`
- L66 _private member_ `TSharedPtr<class SButton> ButtonCreateSkyLight;`
- L67 _private member_ `TSharedPtr<class SButton> ButtonCreateAtmosphericLight0;`
- L68 _private member_ `TSharedPtr<class SButton> ButtonCreateSkyAtmosphere;`
- L69 _private member_ `TSharedPtr<class SButton> ButtonCreateVolumetricCloud;`
- L70 _private member_ `TSharedPtr<class SButton> ButtonCreateHeightFog;`
- L72 _private prototype_ `FReply OnButtonCreateSkyLight();`
- L73 _private prototype_ `FReply OnButtonCreateDirectionalLight(uint32 Index);`
- L74 _private prototype_ `FReply OnButtonCreateSkyAtmosphere();`
- L75 _private prototype_ `FReply OnButtonCreateVolumetricCloud();`
- L76 _private prototype_ `FReply OnButtonCreateHeightFog();`
- L78 _private prototype_ `TSharedRef<SWidget> ComboBoxDetailFilterWidget(TSharedPtr<FString> InItem);`
- L79 _private prototype_ `void ComboBoxDetailFilterWidgetSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);`
- L80 _private prototype_ `FText GetSelectedComboBoxDetailFilterTextLabel() const;`
- L82 _private prototype_ `bool GetIsPropertyVisible(const FPropertyAndParent& PropertyAndParent) const;`

#### Free symbols / members of external scopes

- L30 _macro_ `#define ENVLIGHT_MAX_DETAILSVIEWS 5`

### `Source/Editor/EnvironmentLightingViewer/Public/EnvironmentLightingModule.h` (Public)


#### class `FEnvironmentLightingViewerModule`  
`class FEnvironmentLightingViewerModule : public IModuleInterface`  
_L12-26_
- inherits: `IModuleInterface`
- desc: Struct Viewer module
- L18 _public prototype_ `virtual void StartupModule();` — Called right after the module DLL has been loaded and the module object has been created
- L23 _public prototype_ `virtual void ShutdownModule();` — Called before the module is unloaded, right before the module object is destroyed.
- L25 _public prototype_ `virtual TSharedRef<class SWidget> CreateEnvironmentLightingViewer();`
