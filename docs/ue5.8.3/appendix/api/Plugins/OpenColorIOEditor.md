# Plugins / OpenColorIOEditor

- module root: `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor`
- headers: 13; symbols: 152
- symbol kinds: class=16, delegate=3, enum=1, enumerator=2, function=12, member=35, namespace=1, prototype=79, struct=2, typedef=1
- PrivateDependencyModuleNames: AssetDefinition, Core, CoreUObject, DesktopWidgets, EditorFramework, Engine, ImageCore, InputCore, LevelEditor, OpenColorIO, OpenColorIOWrapper, Projects, PropertyEditor, RHI, RenderCore, Renderer, Settings, Slate, SlateCore, ToolMenus, UnrealEd
- PrivateIncludePathModuleNames: 

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/AssetDefinition_OpenColorIOConfiguration.h` (Private)


#### class `UAssetDefinition_OpenColorIOConfiguration`  
`class UAssetDefinition_OpenColorIOConfiguration : public UAssetDefinitionDefault`  
_L10-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L16 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L17 _public function_ `virtual bool CanImport() const override`
- L19 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L20 _public prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L21 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L22 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/Factories/OpenColorIOConfigurationFactory.h` (Private)


#### class `UOpenColorIOConfigurationFactory`  
`class UOpenColorIOConfigurationFactory : public UFactory`  
_L14-24_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UOpenColorIOConfiguration objects.
- L21 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, const FString& Filename, const TCHAR* Params, FFeedbackContext* Warn, bool& bOutOperationCanceled) override;`
- L22 _public prototype_ `virtual bool FactoryCanImport(const FString& Filename) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/Factories/OpenColorIOConfigurationFactoryNew.h` (Private)


#### class `UOpenColorIOConfigurationFactoryNew`  
`class UOpenColorIOConfigurationFactoryNew : public UFactory`  
_L14-25_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UOpenColorIOConfiguration objects.
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual uint32 GetMenuCategories() const override;`
- L24 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/OpenColorIOColorSpaceConversionCustomization.h` (Private)


#### class `FOpenColorIOColorConversionSettingsCustomization`  
`class FOpenColorIOColorConversionSettingsCustomization : public IPropertyTypeCustomization`  
_L14-52_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FOpenColorIOColorConversionSettings
- L17 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L26 _public prototype_ `void OnSelectionChanged(const FOpenColorIOColorSpace& NewColorSpace, const FOpenColorIODisplayView& NewDisplayView, bool bIsDestination);`
- L30 _private prototype_ `void OnConfigurationReset();` — Callback to reset the configuration in the transform source/destination pickers.
- L33 _private prototype_ `struct FOpenColorIOColorConversionSettings* GetConversionSettings() const;` — Get the struct value of the color space settings member property.
- L36 _private member_ `TSharedPtr<IPropertyHandle> SourceColorSpaceProperty;` — Pointer to the struct SourceColorSpace property handle.
- L39 _private member_ `TSharedPtr<IPropertyHandle> DestinationColorSpaceProperty;` — Pointer to the struct DestinationColorSpace property handle.
- L42 _private member_ `TSharedPtr<IPropertyHandle> DestinationDisplayViewProperty;` — Pointer to the struct DestinationDisplayView property handle.
- L45 _private member_ `TSharedPtr<IPropertyHandle> DisplayViewDirectionProperty;` — Pointer to the struct DisplayViewDirection property handle.
- L48 _private member_ `TStaticArray<TSharedPtr<SOpenColorIOColorSpacePicker>, 2> TransformPicker;` — ColorSpace pickers reference to update them when config asset is changed
- L51 _private member_ `TSharedPtr<IPropertyHandle> ColorSpaceSettingsProperty;` — Property handle to the conversion settings struct.

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/OpenColorIOColorSpaceCustomization.h` (Private)


#### class `IPropertyTypeCustomizationOpenColorIO`  
`class IPropertyTypeCustomizationOpenColorIO : public IPropertyTypeCustomization`  
_L17-37_
- inherits: `IPropertyTypeCustomization`
- desc: Implements a details view customization for the FOpenColorIOConfiguration
- L20 _public prototype_ `IPropertyTypeCustomizationOpenColorIO(TSharedPtr<IPropertyHandle> InConfigurationObjectProperty);`
- L23 _public function_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override` — IPropertyTypeCustomization interface
- L24 _public function_ `virtual void CustomizeChildren(TSharedRef<class IPropertyHandle> InPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override`
- L28 _protected prototype_ `static FOpenColorIOWrapperConfig* GetConfigWrapper(const TSharedPtr<IPropertyHandle>& InConfigurationObjectProperty);`
- L33 _protected member_ `TSharedPtr<IPropertyHandle> CachedProperty;` — Pointer to the property handle.
- L36 _protected member_ `TSharedPtr<IPropertyHandle> ConfigurationObjectProperty;` — Pointer to the configuration object property handle.

#### class `FOpenColorIOColorSpaceCustomization`  
`class FOpenColorIOColorSpaceCustomization : public IPropertyTypeCustomizationOpenColorIO`  
_L40-58_
- inherits: `IPropertyTypeCustomizationOpenColorIO`
- L45 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TSharedPtr<IPropertyHandle> InConfigurationObjectProperty)`
- L50 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L53 _private prototype_ `void ProcessColorSpaceForMenuGeneration(FMenuBuilder& InMenuBuilder, const int32 InMenuDepth, const FString& InPreviousFamilyHierarchy, const FOpenColorIOColorSpace& InColorSpace, TArray<FString>& InOutExistingMenuFilter);`
- L54 _private prototype_ `void PopulateSubMenu(FMenuBuilder& InMenuBuilder, const int32 InMenuDepth, FString InPreviousFamilyHierarchy);`
- L55 _private prototype_ `void AddMenuEntry(FMenuBuilder& InMenuBuilder, const FOpenColorIOColorSpace& InColorSpace);`
- L57 _private prototype_ `TSharedRef<SWidget> HandleSourceComboButtonMenuContent();`

#### class `FOpenColorIODisplayViewCustomization`  
`class FOpenColorIODisplayViewCustomization : public IPropertyTypeCustomizationOpenColorIO`  
_L61-78_
- inherits: `IPropertyTypeCustomizationOpenColorIO`
- L66 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TSharedPtr<IPropertyHandle> InConfigurationObjectProperty)`
- L71 _public prototype_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> InPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& PropertyTypeCustomizationUtils) override;`
- L74 _private prototype_ `void PopulateViewSubMenu(FMenuBuilder& InMenuBuilder, FOpenColorIODisplayView InDisplayView);`
- L75 _private prototype_ `void AddMenuEntry(FMenuBuilder& InMenuBuilder, const FOpenColorIODisplayView& InDisplayView);`
- L77 _private prototype_ `TSharedRef<SWidget> HandleSourceComboButtonMenuContent();`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/OpenColorIOConfigurationCustomization.h` (Private)


#### class `FOpenColorIOConfigurationCustomization`  
`class FOpenColorIOConfigurationCustomization : public IDetailCustomization`  
_L17-55_
- inherits: `IDetailCustomization`
- desc: Implements a details view customization for the UOpenColorIOConfiguration
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L25 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L30 _private prototype_ `void OnConfigTypeChanged(TSharedPtr<FString> InValue, ESelectInfo::Type InSelectInfo);` — Callback for when the config type changes.
- L33 _private prototype_ `void OnConfigurationFileChanged();` — Callback for when the configuration file path changes.
- L36 _private prototype_ `TSharedRef<SWidget> MakeConfigTypeWidget(TSharedPtr<FString> InOption);` — Create the config type widget.
- L39 _private prototype_ `FText GetCurrentConfigTypeLabel() const;` — Get the current config type label.
- L42 _private member_ `TMap<FString, FString> CachedConfigNamePairs;` — Cached OpenColorIO built-in name/UI-name pairs.
- L45 _private member_ `TArray<TSharedPtr<FString>> ConfigTypes;` — List of available config types
- L48 _private member_ `TSharedPtr<FString> CurrentConfigType;` — Currently selected type
- L51 _private member_ `TSharedPtr<IPropertyHandle> ConfigurationFilePropertyHandle;` — Handle to the ConfigurationFile property
- L54 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> TypeCombo;` — Cached combo box widget.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace ESelectInfo`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/OpenColorIOEditorModule.h` (Private)


#### class `FOpenColorIOEditorModule`  
`class FOpenColorIOEditorModule : public IOpenColorIOEditorModule, public TSharedFromThis<FOpenColorIOEditorModule>`  
_L21-77_
- inherits: `IOpenColorIOEditorModule,TSharedFromThis<FOpenColorIOEditorModule>`
- desc: Implements the OpenColorIOEditor module.
- L25 _public prototype_ `virtual ~FOpenColorIOEditorModule() = default;`
- L28 _public prototype_ `virtual void StartupModule() override;`
- L29 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _public prototype_ `void SetActiveViewportConfiguration(const FOpenColorIODisplayConfiguration& InConfiguration);` — Set a color transform display configuration on the active editor viewport.
- L36 _protected prototype_ `void RegisterCustomizations();`
- L37 _protected prototype_ `void UnregisterCustomizations();`
- L38 _protected prototype_ `void RegisterSettings();`
- L39 _protected prototype_ `void UnregisterSettings();`
- L41 _protected prototype_ `void OnWorldInit(UWorld* InWorld, const UWorld::InitializationValues InInitializationValues);`
- L42 _protected prototype_ `void OnLevelEditorFeatureLevelChanged(ERHIFeatureLevel::Type InFeatureLevel);`
- L43 _protected prototype_ `void CleanFeatureLevelDelegate();`
- L44 _protected prototype_ `void RegisterStyle();`
- L45 _protected prototype_ `void UnregisterStyle();`
- L48 _protected prototype_ `void RegisterViewMenuExtension();` — Registers and configure display look configuration in the View menu
- L49 _protected prototype_ `void UnregisterViewMenuExtension();`
- L50 _protected prototype_ `void AddOpenColorIODisplaySubMenu(UToolMenu* Menu);`
- L53 _protected prototype_ `void OnDisplayConfigurationChanged(const FOpenColorIODisplayConfiguration& NewConfiguration);` — Callback when a configuration has changed to update the display manager of a new configuration
- L56 _protected prototype_ `void OnLevelViewportClientListChanged();` — Callback when Level viewport list changed to be able to remove a configured one
- L59 _protected prototype_ `void OnEngineLoopInitComplete();` — Callback when engine loop is done to be able to register ourselves to LevelViewport when editor is valid.
- L62 _protected prototype_ `void SetupViewportDisplaySettings(FLevelEditorViewportClient* Client);` — Verify in settings if a viewport's identifier is pre-configured and add it if yes
- L65 _protected prototype_ `void TrackNewViewportIfRequired(FViewport* Viewport);` — Creates a new ViewportData entry if none exist for the given one
- L69 _private member_ `TWeakObjectPtr<UWorld> EditorWorld;`
- L70 _private member_ `FDelegateHandle FeatureLevelChangedDelegateHandle;`
- L71 _private member_ `TUniquePtr<FSlateStyleSet> StyleInstance;`
- L72 _private member_ `TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;`
- L75 _private typedef_ `using FViewportPair = TPair<FLevelEditorViewportClient*, FName>;` — List of existing viewport we configured to have display look with associated identifier
- L76 _private member_ `TArray<FViewportPair> ConfiguredViewports;`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/OpenColorIOEditorSettings.h` (Private)


#### struct `FPerViewportDisplaySettingPair`  
`struct FPerViewportDisplaySettingPair`  
_L19-30_
- reflection: `USTRUCT()`
- L25 _public member_ `FName ViewportIdentifier;` — `UPROPERTY(config)` — Name associated with this viewport's layout to identify it.
- L29 _public member_ `FOpenColorIODisplayConfiguration DisplayConfiguration;` — `UPROPERTY(config)` — Display configuration for a given viewport

#### class `UOpenColorIOLevelViewportSettings`  
`class UOpenColorIOLevelViewportSettings : public UObject`  
_L36-55_
- reflection: `UCLASS(config = OpenColorIO)`
- inherits: `UObject`
- desc: List of settings associated to level viewport instances linked with an identifier
- L42 _public prototype_ `virtual void PostInitProperties() override;`
- L45 _public prototype_ `const FOpenColorIODisplayConfiguration* GetViewportSettings(FName ViewportIdentifier) const;` — Returns setting associated with a given viewport identifier
- L48 _public prototype_ `void SetViewportSettings(FName ViewportIdentifier, const FOpenColorIODisplayConfiguration& Configuration);` — Add or Update settings for a given viewport identifier
- L54 _protected member_ `TArray<FPerViewportDisplaySettingPair> ViewportsSettings;` — `UPROPERTY(config)` — Settings associated to each viewport that was configured

#### class `UOpenColorIODefaultViewportSettings`  
`class UOpenColorIODefaultViewportSettings : public UObject`  
_L58-69_
- reflection: `UCLASS(config = OpenColorIO)`
- inherits: `UObject`
- L64 _public prototype_ `virtual void PostInitProperties() override;`
- L68 _public member_ `FOpenColorIODisplayConfiguration DefaultDisplayConfiguration;` — `UPROPERTY(config, EditAnywhere, Category = OpenColorIO, DisplayName="Default Viewport Configuration")` — Default settings applied to level viewports when none was previously set, or if settings have been cleared.

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/Widgets/SOpenColorIOColorSpacePicker.h` (Private)


#### struct `FOpenColorIOPickerSelection`  
`struct FOpenColorIOPickerSelection`  
_L22-26_
- desc: Pair of OpenColorIO transform selection objects.
- L24 _public member_ `FOpenColorIOColorSpace ColorSpace;`
- L25 _public member_ `FOpenColorIODisplayView DisplayView;`

#### enum `EOpenColorIOTransformDomain`  
`enum EOpenColorIOTransformDomain : uint32`  
_L29-33_
- desc: OpenColorIO transformation source or destination.
- L31 _public enumerator_ `OCIO_Src = 0`
- L32 _public enumerator_ `OCIO_Dst = 1`

#### class `SOpenColorIOColorSpacePicker`  
`class SOpenColorIOColorSpacePicker : public SCompoundWidget`  
_L35-74_
- inherits: `SCompoundWidget`
- L38 _public function_ `SLATE_BEGIN_ARGS(SOpenColorIOColorSpacePicker)`
- L47 _public prototype_ `void Construct(const FArguments& InArgs);`
- L50 _public prototype_ `void SetConfiguration(TWeakObjectPtr<UOpenColorIOConfiguration> NewConfiguration);` — Update current configuration asset for this picker
- L55 _protected prototype_ `void SetCurrentColorSpace(const FOpenColorIOColorSpace& NewColorSpace);` — Called when a selection has been made
- L56 _protected prototype_ `void SetCurrentDisplayView(const FOpenColorIODisplayView& NewDisplayView);`
- L59 _protected prototype_ `TSharedRef<SWidget> HandleColorSpaceComboButtonMenuContent();` — Handles color space list menu creation
- L62 _protected prototype_ `FReply OnResetToDefault();` — Reset to default triggered in UI
- L65 _protected prototype_ `EVisibility ShouldShowResetToDefaultButton() const;` — Whether or not ResetToDefault button should be shown
- L68 _protected member_ `TSharedPtr<SComboButton> SelectionButton;`
- L69 _protected member_ `TWeakObjectPtr<UOpenColorIOConfiguration> Configuration;`
- L70 _protected member_ `TAttribute<FText> Selection;`
- L71 _protected member_ `TAttribute<FString> SelectionRestriction;`
- L72 _protected member_ `FOnColorSpaceChanged OnColorSpaceChanged;`
- L73 _protected member_ `bool bIsDestination = false;`

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnColorSpaceChanged, const FOpenColorIOColorSpace& , const FOpenColorIODisplayView& , bool );`
- L19 _prototype_ `DECLARE_DELEGATE_ThreeParams(FOnColorSpaceChanged, const FOpenColorIOColorSpace& , const FOpenColorIODisplayView& , bool );`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Private/Widgets/SOpenColorIODisplay.h` (Private)


#### class `SOpenColorIODisplay`  
`class SOpenColorIODisplay : public SCompoundWidget`  
_L23-60_
- inherits: `SCompoundWidget`
- L26 _public function_ `SLATE_BEGIN_ARGS(SOpenColorIODisplay)`
- L33 _public prototype_ `void Construct(const FArguments& InArgs);`
- L37 _protected prototype_ `FText GetConfigurationText() const;`
- L38 _protected prototype_ `void SelectConfigSubMenu(UToolMenu* Menu);`
- L39 _protected prototype_ `void OnConfigSelected(const FAssetData& AssetData);`
- L40 _protected prototype_ `void ToggleEnableDisplay();`
- L41 _protected prototype_ `bool CanEnableDisplayConfiguration();`
- L42 _protected prototype_ `bool GetDisplayConfigurationState();`
- L43 _protected prototype_ `void OnSelectionChanged(const FOpenColorIOColorSpace& NewColorSpace, const FOpenColorIODisplayView& NewDisplayView, bool bIsDestination);`
- L47 _protected member_ `FViewport* Viewport;`
- L50 _protected member_ `TSharedPtr<SWidget> ClassPicker;` — Class picker widget to be able to close back the menu once selection has been made
- L53 _protected member_ `TStaticArray<TSharedPtr<SOpenColorIOColorSpacePicker>, 2> TransformPicker;` — ColorSpace pickers reference to update them when config asset is changed
- L56 _protected member_ `FOpenColorIODisplayConfiguration Configuration;` — Current configuration
- L59 _protected member_ `FOnDisplayConfigurationChanged OnDisplayConfigurationChanged;` — Callback triggered any time the configuration changed

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDisplayConfigurationChanged, const FOpenColorIODisplayConfiguration& );`
- L20 _prototype_ `DECLARE_DELEGATE_OneParam(FOnDisplayConfigurationChanged, const FOpenColorIODisplayConfiguration& );`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Public/IOpenColorIOEditorModule.h` (Public)


#### class `IOpenColorIOEditorModule`  
`class IOpenColorIOEditorModule : public IModuleInterface`  
_L15-18_
- inherits: `IModuleInterface`
- desc: Interface for the OpenColorIOEditor module.

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenColorIOEditor, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogOpenColorIOEditor, Log, All);`

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Public/OpenColorIOEditorBlueprintLibrary.h` (Public)


#### class `UOpenColorIOEditorBlueprintLibrary`  
`class UOpenColorIOEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L13-56_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L24 _public prototype_ `static void SetActiveViewportConfiguration(const FOpenColorIODisplayConfiguration& InConfiguration);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — Set the active editor viewport's display configuration color transform . @param InDisplayConfiguration Display configuration color transform
- L34 _public prototype_ `static bool ApplyColorSpaceTransformToColor(const FOpenColorIOColorConversionSettings& ConversionSettings, const FLinearColor& InColor, FLinearColor& OutColor);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — Apply a color space transform to a color value. @param ConversionSettings Color transformation settings. @param InOutColor Color value transform. @return true upon success.
- L44 _public prototype_ `static bool ApplyColorSpaceTransformToTexture(const FOpenColorIOColorConversionSettings& ConversionSettings, UTexture* InOutTexture);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — Apply a color space transform to a texture asset. @param ConversionSettings Color transformation settings. @param InOutTexture Texture object to transform. @return true upon success.
- L55 _public prototype_ `static bool ApplyColorSpaceTransformToTextureCompressed(const FOpenColorIOColorConversionSettings& ConversionSettings, TextureCompressionSettings TargetCompression, UTexture* InOutTexture);` — `UFUNCTION(BlueprintCallable, Category = "OpenColorIO")` — Apply a color space transform with a target compression setting to a texture asset. @param ConversionSettings Color transformation settings. @param TargetCompression Target texture compression setting. @param InOutTexture Texture object to transform. @return true upon success.

### `Plugins/Compositing/OpenColorIO/Source/OpenColorIOEditor/Public/OpenColorIOShaderProcessor.h` (Public)


#### class `FOpenColorIOShaderProcessorTickable`  
`class FOpenColorIOShaderProcessorTickable : FTickableEditorObject`  
_L12-29_
- inherits: `FTickableEditorObject`
- desc: Handles ticking the shader compilation manager and dispatch the results
- L14 _private function_ `virtual ETickableTickType GetTickableTickType() const override`
- L19 _private function_ `virtual void Tick(float DeltaSeconds) override`
- L25 _private function_ `virtual TStatId GetStatId() const`
