# Developer / GDKPlatformEditor

- module root: `Source/Developer/Microsoft/GDKPlatformEditor`
- headers: 3; symbols: 135
- symbol kinds: class=4, enum=3, enumerator=8, function=5, macro=2, member=73, prototype=25, struct=14, typedef=1
- PrivateDependencyModuleNames: Core, CoreUObject, DeveloperToolSettings, Engine, InputCore, MainFrame, Projects, PropertyEditor, SharedSettingsWidgets, Slate, SlateCore, SourceControl, ToolWidgets, UnrealEd, XmlParser
- PrivateIncludePathModuleNames: Settings
- PublicIncludePathModuleNames: PropertyEditor

### `Source/Developer/Microsoft/GDKPlatformEditor/Public/GDKPlatformEditorModule.h` (Public)


#### class `IGDKPlatformEditorModule`  
`class IGDKPlatformEditorModule : public IModuleInterface`  
_L12-27_
- inherits: `IModuleInterface`
- L15 _public function_ `static inline IGDKPlatformEditorModule& Get()`
- L20 _public typedef_ `typedef TMap<FString,FString> FPartnerCenterProduct;`
- L22 _public prototype_ `virtual void PartnerCenterQueryProductsAsync( TFunction<void(bool)> OnComplete ) = 0;`
- L23 _public prototype_ `virtual const TArray<TSharedPtr<FPartnerCenterProduct>>* GetPartnerCenterProducts() = 0;`
- L25 _public prototype_ `virtual bool IsQueryingPartnerCenter() const = 0;`
- L26 _public prototype_ `virtual void CancelQueryPartnerCenter() = 0;`

### `Source/Developer/Microsoft/GDKPlatformEditor/Public/GDKTargetSettings.h` (Public)


#### enum `EGDKForegroundColor`  
`enum class EGDKForegroundColor : uint8`  
_L16-23_
- reflection: `UENUM()`
- L19 _public enumerator_ `Light` — Use light colored text to contrast against a dark background.
- L22 _public enumerator_ `Dark` — Use dark colored text to contrast against a light background.

#### struct `FGDKPackageStringResources`  
`struct FGDKPackageStringResources`  
_L27-42_
- reflection: `USTRUCT()`
- L35 _public member_ `FString ApplicationDisplayName;` — `UPROPERTY(EditAnywhere, Config, Category=Content)` — Friendly application display name. This value will be displayed on game tiles in the dashboard.
- L41 _public member_ `FString ApplicationDescription;` — `UPROPERTY(EditAnywhere, Config, Category=Content)` — Friendly application description. This value will be displayed on game tiles in the game collection.

#### struct `FGDKLocalizedPackageResources`  
`struct FGDKLocalizedPackageResources`  
_L45-60_
- reflection: `USTRUCT()`
- L53 _public member_ `FString StageId;` — `UPROPERTY(EditAnywhere, Config, Category=Content, Meta=(GetOptions="GetKnownCultureStageIds", DisplayName="Language"))` — Which CultureToStage entry these resources should apply to. See "Languages To Package" in Packaging settings
- L59 _public member_ `FGDKPackageStringResources CultureStringResources;` — `UPROPERTY(EditAnywhere, Config, Category=Content)` — The package localized strings.

#### enum `EGDKCustomChunkMappingType`  
`enum class EGDKCustomChunkMappingType : uint8`  
_L67-71_
- reflection: `UENUM()`
- L69 _public enumerator_ `Main`
- L70 _public enumerator_ `Optional`

#### struct `FGDKCustomChunkMapping`  
`struct FGDKCustomChunkMapping`  
_L74-88_
- reflection: `USTRUCT()`
- L79 _public member_ `int32 ChunkId = 0;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, Meta=(ClampMin=0))`
- L83 _public member_ `FString Pattern;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging)` — relative content path: e.g. shootergame/content/movies/\*  or  shootergame/content/movies/movie1.mp4
- L87 _public member_ `EGDKCustomChunkMappingType Type = EGDKCustomChunkMappingType::Main;` — `UPROPERTY()` — not currently wired up, so keeping at default

#### struct `FGDKIntelligentDeliveryChunk`  
`struct FGDKIntelligentDeliveryChunk`  
_L94-118_
- reflection: `USTRUCT()`
- L100 _public member_ `int32 ChunkId = 0;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, Meta=(ClampMin=0))` — Unreal chunk identifier
- L104 _public member_ `FString Tags;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging)` — List of tags, separated by semicolons, (using # to define groups if Features are also used). Does not apply when 'required for launch' is set. See the GDK documentation for details
- L108 _public member_ `TArray<FString> StageIds;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, Meta=(GetOptions="GetKnownCultureStageIds", DisplayName="Languages"))` — List of languages from CultureToStage. See "Languages To Package" in Packaging settings
- L112 _public member_ `TArray<FString> Devices;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging, Meta=(GetOptions="GetKnownDeviceTypes"))` — List of devices that this chunk is available for.
- L116 _public member_ `bool bRequiredForLaunch = false;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging)` — Whether this chunk must be installed before the game can be launched.

#### struct `FGDKLocalizedIntelligentDeliveryFeatureResource`  
`struct FGDKLocalizedIntelligentDeliveryFeatureResource`  
_L121-132_
- reflection: `USTRUCT()`
- L127 _public member_ `FString StageId;` — `UPROPERTY(EditAnywhere, Config, Category=Content, Meta=(GetOptions="GetKnownCultureStageIds", DisplayName="Language"))` — Locale from CultureToStage. See "Languages To Package" in Packaging settings
- L131 _public member_ `FString DisplayName;` — `UPROPERTY(EditAnywhere, Config, Category=Content, AdvancedDisplay)` — Friendly install feature display name. This value will be displayed to the user in the shell

#### struct `FGDKIntelligentDeliveryFeature`  
`struct FGDKIntelligentDeliveryFeature`  
_L136-158_
- reflection: `USTRUCT()`
- L141 _public member_ `FString Id;` — `UPROPERTY(EditAnywhere, Config, Category=Feature)`
- L145 _public member_ `FString Tags;` — `UPROPERTY(EditAnywhere, Config, Category=Feature)` — Semicolon-separated list of chunk tags. See the GDK documentation for details
- L149 _public member_ `bool bHidden = true;` — `UPROPERTY(EditAnywhere, Config, Category=Feature)` — Whether this feature is hidden from the user. See the GDK documentation for details.
- L153 _public member_ `FString DefaultDisplayName;` — `UPROPERTY(EditAnywhere, Config, Category=Content, Meta=(EditCondition="!bHidden"))` — Friendly install feature display name. This value will be displayed to the user in the shell.
- L157 _public member_ `TArray<FGDKLocalizedIntelligentDeliveryFeatureResource> PerCultureResources;` — `UPROPERTY(EditAnywhere, Config, Category=Content, DisplayName="Per-Language Resources", Meta=(EditCondition="!bHidden", TitleProperty="StageId"))` — Optional per-language resources that will be used for this feature

#### struct `FGDKIntelligentDeliveryRecipe`  
`struct FGDKIntelligentDeliveryRecipe`  
_L162-180_
- reflection: `USTRUCT()`
- L167 _public member_ `FString Id;` — `UPROPERTY(EditAnywhere, Config, Category=Recipe)`
- L171 _public member_ `TArray<FString> IncludedFeatures;` — `UPROPERTY(EditAnywhere, Config, Category=Recipe, Meta=(GetOptions="GetKnownIntelligentDeliveryFeatures"))` — List of features to include, separated by semicolons. See the GDK documentation for details
- L175 _public member_ `TArray<FString> Devices;` — `UPROPERTY(EditAnywhere, Config, Category=Recipe, Meta=(GetOptions="GetKnownDeviceTypes"))` — List of devices that this recipe is available for.
- L179 _public member_ `TArray<FString> StoreIds;` — `UPROPERTY(EditAnywhere, Config, Category=Recipe)` — Premium product recipe. Only installed if the user owns one of these products. See the GDK documentation for details

#### struct `FGDKDLCPackageStringResources`  
`struct FGDKDLCPackageStringResources`  
_L183-194_
- reflection: `USTRUCT()`
- L189 _public member_ `FString StageId;` — `UPROPERTY(EditAnywhere, Config, Category=Content, Meta=(GetOptions="GetKnownCultureStageIds", DisplayName="Language"))` — Locale from CultureToStage. See "Languages To Package" in Packaging settings
- L193 _public member_ `FGDKPackageStringResources CultureStringResources;` — `UPROPERTY(EditAnywhere, Config, Category=Content)` — The localized strings

#### struct `FGDKDLCPackage`  
`struct FGDKDLCPackage`  
_L198-230_
- reflection: `USTRUCT()`
- L204 _public member_ `FString DLCName;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, DisplayName="DLC Name")` — Name of this DLC. Used by the various DLC support APIs
- L208 _public member_ `FString StoreId;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter)` — Store Id. Must match Partner Center configuration.
- L212 _public member_ `FString DefaultDisplayName;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Product Name")` — Name of the product in Partner Center. Must match Partner Center configuration
- L216 _public member_ `FString PackageName;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Package/Identity/Name")` — Package/Identity/Name. Must match Partner Center configuration
- L220 _public member_ `FString PackageVersion;` — `UPROPERTY(EditAnywhere, Config, Category=Packaging)` — Package version in the form 0.0.0.0. Leave blank to inherit the main package version
- L225 _public member_ `FGDKPackageStringResources DefaultStringResources;` — `UPROPERTY(EditAnywhere, Config, Category=Content)` — The package default strings.
- L229 _public member_ `TArray<FGDKDLCPackageStringResources> PerCultureResources;` — `UPROPERTY(EditAnywhere, Config, Category=Content, DisplayName="Per-Language Resources", Meta=(TitleProperty="StageId"))` — The per culture images, icons, and strings describing a package.

#### struct `FGDKDLCChunk`  
`struct FGDKDLCChunk`  
_L233-244_
- reflection: `USTRUCT()`
- L239 _public member_ `FString DLCName;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, DisplayName="DLC Name", Meta=(GetOptions="GetKnownDLCNames"))` — Name of the DLC to associate with this chunk
- L243 _public member_ `int32 ChunkId = 1;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, Meta=(ClampMin=1))` — Unreal chunk identifier that will be moved into this DLC

#### struct `FGDKDLCPlugins`  
`struct FGDKDLCPlugins`  
_L247-258_
- reflection: `USTRUCT()`
- L253 _public member_ `FString DLCName;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, DisplayName="DLC Name", Meta=(GetOptions="GetKnownDLCNames"))` — Name of the DLC to associate with this plugin
- L257 _public member_ `FString Plugin;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, Meta=(GetOptions="GetKnownDLCPlugins", DisplayName="Plugin"))` — Name of the explicity-loaded content plugin this DLC applies to

#### struct `FGDKUriActivationProtocol`  
`struct FGDKUriActivationProtocol`  
_L262-280_
- reflection: `USTRUCT()`
- L271 _public member_ `FString RegisteredProtocol;` — `UPROPERTY(EditAnywhere, Config, Category=ActivationProtocol, Meta=(DisplayName="OS-Registered Protocol", MaxLength=39))` — e.g. MyGameUGC Protocol that is registered with the OS. This will be what is launched by the user via MyGameUGC://<payload> note that this will be system-wide, so should be clearly unique for your title.
- L279 _public member_ `FString InGameUriPrefix;` — `UPROPERTY(EditAnywhere, Config, Category=ActivationProtocol)` — e.g. ugc:// Prefix for how this protocol's payload will be represented in FCoreDelegates::OnActivatedByProtocol as ugc://<payload> note that this is only visible to your game, so can be a generic name. this can be combined with other <platform>.*UriPrefix CVars to craft platform-agnostic OnActivatedByProtocol handler code.

#### enum `EGDKCustomInstallActionType`  
`enum class EGDKCustomInstallActionType : uint8`  
_L283-289_
- reflection: `UENUM()`
- L285 _public enumerator_ `Invalid UMETA(Hidden, DisplayName="...")`
- L286 _public enumerator_ `Install`
- L287 _public enumerator_ `Repair`
- L288 _public enumerator_ `Uninstall UMETA(ToolTip="Note: there is a bug in Windows 10 that prevents the uninstall action from being run. It is fixed in Windows 11")`

#### struct `FGDKCustomInstallCommand`  
`struct FGDKCustomInstallCommand`  
_L292-303_
- reflection: `USTRUCT()`
- L298 _public member_ `FFilePath Command;` — `UPROPERTY(EditAnywhere, Config, Category=Action, Meta=(FilePathFilter="Commands (*.exe;*.msi)|*.exe;*.msi|All Files (*.*)|*.*"))` — .exe or .msi file to run
- L302 _public member_ `FString Arguments;` — `UPROPERTY(EditAnywhere, Config, Category=Action)` — command line arguments to pass to the given command. For .msi files this can be blank

#### struct `FGDKCustomInstallAction`  
`struct FGDKCustomInstallAction`  
_L306-325_
- reflection: `USTRUCT()`
- L312 _public member_ `FString Name;` — `UPROPERTY(EditAnywhere, Config, Category=Action)` — name of the item to be installed/repaired/uninstalled. SourceFolder will be staged into a subfolder with this name
- L316 _public member_ `FDirectoryPath SourceFolder;` — `UPROPERTY(EditAnywhere, Config, Category=Actions, Meta=(RelativePath))` — Source folder for all the custom install commands. The contents of this directory will be staged automatically
- L320 _public member_ `FString TargetFolder;` — `UPROPERTY(EditAnywhere, Config, Category=Action)` — Relative destination folder when staging, relative to Custom Install Staging Root. Leave blank to stage the custom install action into a subfolder
- L324 _public member_ `TMap<EGDKCustomInstallActionType,FGDKCustomInstallCommand> Commands;` — `UPROPERTY(EditAnywhere, Config, Category=Action)` — The commands to run for each step of the installation

#### class `UGDKTargetSettings`  
`class UGDKTargetSettings : public UObject`  
_L334-483_
- reflection: `UCLASS(MinimalAPI, config = Engine, defaultconfig, Abstract)`
- inherits: `UObject`
- desc: Implements the settings for the GDK target platform. Note: Properties must use Config not GlobalConfig because the properties need to be serialized into the specialization's own ini file.
- L341 _public prototype_ `virtual const TCHAR* GetPlatformName() const PURE_VIRTUAL(GetPlatformName, return nullptr;);`
- L345 _public member_ `EGDKForegroundColor ApplicationForegroundColor;` — `UPROPERTY(EditAnywhere, Config, Category=Content, Meta=(DisplayName="Application Foreground Text"))` — Inform the OS of what color scheme best contrasts with your application's tile images.
- L349 _public member_ `FColor ApplicationBackgroundColor;` — `UPROPERTY(EditAnywhere, Config, Category=Content)` — Inform the OS what background color to use for your application tiles.
- L353 _public member_ `FGDKPackageStringResources CultureStringResources;` — `UPROPERTY(EditAnywhere, Config, Category=Content)` — The package default strings.
- L357 _public member_ `TArray<FGDKLocalizedPackageResources> PerCultureResources;` — `UPROPERTY(EditAnywhere, Config, Category=Content, DisplayName="Per-Language Resources", meta = (TitleProperty="StageId"))` — The per culture images, icons, and strings describing a package.
- L361 _public member_ `TMap<FString,FString> StageIdOverrides;` — `UPROPERTY(EditAnywhere, Config, Category=Content, AdvancedDisplay, Meta=(GetKeyOptions="GetKnownCultureStageIds", DisplayName="Language/Locale Overrides"))` — Mapping from "Languages To Package" in Packaging settings, to "Console-supported languages" in the GDK documentation. Leave empty to keep 1:1 mapping
- L366 _public member_ `bool bUseSimplifiedUserModel = false;` — `UPROPERTY(EditAnywhere, Config, Category=Features)` — Whether to use the Simplified User Model where the OS will maintain a primary user for the title and the title will be terminated if this user signs out. Other secondary users are free to sign in and out. See the GDK documention for details.
- L370 _public member_ `TArray<FGDKUriActivationProtocol> UriActivationProtocols;` — `UPROPERTY(EditAnywhere, Config, Category=Features, Meta=(TitleProperty="RegisteredProtocol", ForMSGameStore))` — List of custom protocol schemes to register (March 2023 GDK onwards)
- L376 _public member_ `FString DefaultDisplayName;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter)` — Name of the product in Partner Center. Must match Partner Center configuration
- L380 _public member_ `FString PackageName;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Package/Identity/Name")` — Package/Identity/Name. Must match Partner Center configuration
- L384 _public member_ `FString PublisherName;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Package/Identity/Publisher")` — Package/Identity/Publisher. Must match Partner Center configuration
- L388 _public member_ `FString PublisherDisplayName;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Package/Properties/PublisherDisplayName")` — Package/Properties/PublisherDisplayName. Must match Partner Center configuration
- L392 _public member_ `FString StoreId;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Store ID")` — Store Id. Must match Partner Center configuration.
- L396 _public member_ `FString TitleId;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Xbox Title ID")` — Xbox Live Title Id. Get this value from your Partner Center configuration. This value is required for title submission.
- L400 _public member_ `FString PrimaryServiceConfigId;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Xbox Services Configuration ID (SCID)")` — Xbox Live Service Config Id (SCID). Get this value from your Partner Center configuration. This value is required for title submission.
- L404 _public member_ `FString MSAAppId;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="MSA app Id")` — MSA App Id. Get this value from your Partner Center configuration. This value is required for title submission.
- L408 _public member_ `FString ProductId;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, DisplayName="Legacy Product ID", Meta=(EditCondition="CanEditProductId()"))` — Legacy Product GUID. Must match Partner Center configuration. Ignored if StoreId is specified
- L411 _public prototype_ `bool CanEditProductId() const;` — `UFUNCTION()`
- L417 _public member_ `FString PackageVersion;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter)` — Package version in the form 0.0.0.0
- L421 _public member_ `bool bIncludeEngineVersionInPackageVersion;` — `UPROPERTY(EditAnywhere, Config, Category=PartnerCenter, AdvancedDisplay)` — Use Include the current engine changelist in the package version number.
- L428 _public member_ `TArray<FGDKCustomChunkMapping> CustomChunkMapping;` — `UPROPERTY(EditAnywhere, Config, Category="Chunk Install", AdvancedDisplay, Meta = (TitleProperty="Pattern"))` — Define custom chunk mapping
- L432 _public member_ `bool bUseFeaturesAndRecipes;` — `UPROPERTY(EditAnywhere, Config, Category="Chunk Install")` — Whether to use simple On-Demand intelligent install chunks, or new Features and Recipes for defining chunks and installations
- L436 _public member_ `TArray<FGDKIntelligentDeliveryChunk> IntelligentDeliveryChunks;` — `UPROPERTY(EditAnywhere, Config, Category="Chunk Install", Meta = (TitleProperty="ChunkId"))` — List of chunks. See the GDK documentation for details
- L440 _public member_ `TArray<FGDKIntelligentDeliveryFeature> IntelligentDeliveryFeatures;` — `UPROPERTY(EditAnywhere, Config, Category="Chunk Install", Meta = (EditCondition="bUseFeaturesAndRecipes", TitleProperty="Id"))` — List of features. See the GDK documentation for details
- L444 _public member_ `TArray<FGDKIntelligentDeliveryRecipe> IntelligentDeliveryRecipes;` — `UPROPERTY(EditAnywhere, Config, Category="Chunk Install", Meta = (EditCondition="bUseFeaturesAndRecipes", TitleProperty="Id"))` — List of recipes. See the GDK documentation for details
- L449 _public prototype_ `virtual TArray<FString> GetKnownDeviceTypes();` — `UFUNCTION()` — UI helper functions to get the list of known devices, used by FGDKIntelligentDeliveryRecipe & FGDKIntelligentDeliveryChunk
- L453 _public prototype_ `TArray<FString> GetKnownIntelligentDeliveryFeatures();` — `UFUNCTION()` — UI helper function to get the list of known features, used by FGDKIntelligentDeliveryRecipe
- L457 _public prototype_ `TArray<FString> GetKnownCultureStageIds();` — `UFUNCTION()` — UI helper function to get the list of known culture StageIDs, used by FGDKIntelligentDeliveryChunk
- L461 _public prototype_ `TArray<FString> GetKnownDLCNames();` — `UFUNCTION()` — UI helper function to get the list of DLC packages
- L465 _public prototype_ `TArray<FString> GetKnownDLCPlugins();` — `UFUNCTION()` — UI helper function to get the list of known DLC plugins
- L470 _public member_ `TArray<FGDKDLCPackage> DLCPackages;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, Meta=(TitleProperty="DLCName", DisplayName="DLC Packages (EXPERIMENTAL)"))` — Configuration for DLC packages.
- L474 _public member_ `bool bAutoCreateDLCPackages = false;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, Meta=(DisplayName="Automatically Create DLC Packages (EXPERIMENTAL)"))` — When enabled, the DLC packages listed above will be generated automatically using `DLC Chunks` during normal packaging. This is not compatible with the "DLC Plugins" mechanism or packaging a single plugin in UAT via -dlcname=
- L478 _public member_ `TArray<FGDKDLCChunk> DLCChunks;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, Meta=(TitleProperty="ChunkId", DisplayName="DLC Chunks (EXPERIMENTAL)", EditCondition="bAutoCreateDLCPackages", EditConditionHides="true"))` — Chunks to pull out of the main package to include in DLC instead
- L482 _public member_ `TArray<FGDKDLCPlugins> DLCPlugins;` — `UPROPERTY(EditAnywhere, Config, Category=DLC, Meta=(TitleProperty="DLCName", DisplayName="DLC Plugins (EXPERIMENTAL)", EditCondition="!bAutoCreateDLCPackages", EditConditionHides="true"))` — Configuration for DLC plugins

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GDKPLATFORMEDITOR_API`

### `Source/Developer/Microsoft/GDKPlatformEditor/Public/GDKTargetSettingsDetails.h` (Public)


#### class `FGDKTargetSettingsDetails`  
`class FGDKTargetSettingsDetails : public IDetailCustomization`  
_L16-41_
- inherits: `IDetailCustomization`
- desc: Detail customization for GDK target settings panel
- L19 _public prototype_ `FGDKTargetSettingsDetails(const TCHAR* InPlatformName);`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L25 _protected prototype_ `void NotifyPropertyChanged(FProperty* Property, UObject* OwnerObject, const TSharedRef<class IPropertyUtilities> PropertyUtilities) const;`
- L26 _protected prototype_ `void NotifyPropertyChanged(FName PropertyName, UObject* OwnerObject, const TSharedRef<class IPropertyUtilities> PropertyUtilities) const;`
- L28 _protected function_ `virtual void AddAdditionalPlatformItems( TSharedPtr<class SHorizontalBox> PartnerCenterBox, TWeakObjectPtr<class UGDKTargetSettings> GDKTargetSettings )`
- L29 _protected function_ `virtual void AddAdditionalGettingStartedItems( TSharedPtr<class SHorizontalBox> GettingStartedBox, TWeakObjectPtr<class UGDKTargetSettings> GDKTargetSettings, const TSharedRef<class IPropertyUtilities> PropertyUtilities )`
- L31 _protected prototype_ `bool IsGDKConfigured(class UGDKTargetSettings* GDKTargetSettings) const;`
- L33 _protected member_ `FString PlatformName;`
- L36 _private prototype_ `void AddGettingStartedItems(TWeakObjectPtr<class UGDKTargetSettings> GDKTargetSettings, TSharedPtr<class SHorizontalBox> PartnerCenterBox, const TSharedRef<class IPropertyUtilities> PropertyUtilities);`
- L37 _private prototype_ `void OnClickUpdateFromPartnerCenter( UGDKTargetSettings* GDKTargetSettings, const TSharedRef<class IPropertyUtilities> PropertyUtilities );`
- L38 _private prototype_ `void UpdatePartnerCenterData( class UGDKTargetSettings* GDKTargetSettings, const IGDKPlatformEditorModule::FPartnerCenterProduct& Product, const TSharedRef<class IPropertyUtilities> PropertyUtilities );`
- L40 _private member_ `TSharedPtr<SWindow> PartnerCenterProductWindow;`

#### class `FGDKCultureResourceDetails`  
`class FGDKCultureResourceDetails : public IPropertyTypeCustomization`  
_L43-71_
- inherits: `IPropertyTypeCustomization`
- L46 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L52 _public function_ `virtual void CustomizeHeader(TSharedRef<class IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override` — Overridden to do nothing
- L55 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — Overridden display image customization options for packaging
- L59 _protected prototype_ `void OnClickConfigureImages(TSharedRef<IPropertyHandle> InStructPropertyHandle);` — Displays a dialog to set up the images for the given culture
- L62 _protected prototype_ `void AddImagePickerRow(TSharedPtr<class SScrollBox> ImagesBox, const FText& ImageDescription, const FString& DefaultImagePath, const FString& TargetImagePath, int32 ImageWidth, int32 ImageHeight);` — Creates a packaging image picker
- L65 _private prototype_ `TSharedPtr<IPropertyHandle> GetDLCNameProperty( TSharedPtr<IPropertyHandle> InStructPropertyHandle ) const;`
- L67 _private prototype_ `FString GetPickerPath();` — Delegate handler to get the path to start picking from
- L70 _private prototype_ `bool HandlePostExternalIconCopy(const FString& InChosenImage);` — Delegate handler to set the path to start picking from

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GDKPLATFORMEDITOR_API`
