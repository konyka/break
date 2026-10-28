# Plugins / DatasmithContentEditor

- module root: `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor`
- headers: 7; symbols: 105
- symbol kinds: class=8, delegate=8, function=7, macro=3, member=13, prototype=65, struct=1
- PrivateDependencyModuleNames: DetailCustomizations, InputCore, PropertyEditor, Slate, SlateCore, ToolMenus
- PublicDependencyModuleNames: AssetDefinition, ContentBrowser, Core, CoreUObject, DatasmithContent, DesktopPlatform, EditorFramework, Engine, Projects, UnrealEd

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor/Private/AssetDefinition_DatasmithScene.h` (Private)


#### class `UAssetDefinition_DatasmithScene`  
`class UAssetDefinition_DatasmithScene : public UAssetDefinitionDefault`  
_L12-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L19 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L20 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L22 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _public function_ `virtual bool CanImport() const override`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor/Private/DatasmithAreaLightActorDetailsPanel.h` (Private)


#### class `FDatasmithAreaLightActorDetailsPanel`  
`class FDatasmithAreaLightActorDetailsPanel : public IDetailCustomization`  
_L11-22_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `FDatasmithAreaLightActorDetailsPanel();`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailLayout) override;` — IDetailCustomization interface

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor/Private/DatasmithImportInfoCustomization.h` (Private)


#### class `FDatasmithImportInfoCustomization`  
`class FDatasmithImportInfoCustomization : public IPropertyTypeCustomization`  
_L17-54_
- inherits: `IPropertyTypeCustomization`
- L20 _public prototype_ `FDatasmithImportInfoCustomization();`
- L23 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L26 _public function_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override` — IDetailCustomization interface
- L27 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _private prototype_ `FName GetCurrentScheme() const;`
- L33 _private prototype_ `FReply OnBrowseSourceClicked() const;`
- L35 _private prototype_ `bool SelectNewSource(FName SourceScheme) const;`
- L37 _private prototype_ `FDatasmithImportInfo* GetImportInfo() const;`
- L40 _private prototype_ `UObject* GetOuterClass() const;` — Access the outer class that contains this struct
- L43 _private prototype_ `FText GetUriText() const;` — Get text for the UI
- L45 _private prototype_ `void OnSchemeComboBoxChanged(FName InItem, ESelectInfo::Type InSeletionInfo);`
- L49 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — Property handle of the property we're editing
- L51 _private member_ `TSharedPtr<SComboBox<FName>> SchemeComboBox;`
- L53 _private member_ `TArray<FName> AvailableUriSchemes;`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor/Private/DatasmithSceneActorDetailsPanel.h` (Private)


#### class `FDatasmithSceneActorDetailsPanel`  
`class FDatasmithSceneActorDetailsPanel : public IDetailCustomization`  
_L12-30_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `FDatasmithSceneActorDetailsPanel();`
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailLayout ) override;` — IDetailCustomization interface
- L25 _protected prototype_ `FReply OnExecuteAction();`
- L28 _private member_ `TArray< TWeakObjectPtr< UObject > > SelectedObjectsList;`
- L29 _private member_ `bool bReimportDeletedActors;`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor/Private/DatasmithSceneDetails.h` (Private)


#### class `FDatasmithSceneDetails`  
`class FDatasmithSceneDetails : public IDetailCustomization`  
_L14-26_
- inherits: `IDetailCustomization`
- desc: Customization of the details of the Datasmith Scene for the data prep editor.
- L17 _public function_ `static TSharedRef< IDetailCustomization > MakeDetails()`
- L20 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — Called when details should be customized
- L22 _public prototype_ `virtual void CustomizeDetails( const TSharedPtr<IDetailLayoutBuilder>& DetailBuilder ) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATASMITHCONTENTEDITOR_API`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor/Public/DatasmithContentEditorModule.h` (Public)


#### class `IDataprepImporterInterface`  
`class IDataprepImporterInterface`  
_L20-35_
- desc: DATAPREP_TODO: Temporary interface to emulate future workflow. Interface to trigger build world and 'finalize' from data prep editor
- L23 _public prototype_ `virtual ~IDataprepImporterInterface() = default;`
- L30 _public prototype_ `virtual bool Initialize(const FString& Namespace, UWorld* ImportWorld, UDatasmithScene* DatasmithScene) = 0;` — @param Namespace			The namespace in which to generate asset's unique ids. @param ImportWorld		The destination world that we will spawn the actors in. @param DatasmithScene	The DatasmithScene that we will apply the data prep pipeline on.
- L31 _public prototype_ `virtual bool BuildWorld(TArray<TWeakObjectPtr<UObject>>& OutAssets) = 0;`
- L32 _public prototype_ `virtual bool SetFinalWorld(UWorld* FinalWorld) = 0;`
- L33 _public prototype_ `virtual bool FinalizeAssets(const TArray<TWeakObjectPtr<UObject>>& Assets) = 0;`
- L34 _public prototype_ `virtual TSubclassOf<class UDatasmithSceneImportData> GetAssetImportDataClass() const = 0;`

#### struct `FImporterDescription`  
`struct FImporterDescription`  
_L47-56_
- L49 _public member_ `FText Label;`
- L50 _public member_ `FText Description;`
- L51 _public member_ `FName StyleName;`
- L52 _public member_ `FString IconPath;`
- L53 _public member_ `TArray<FString> Formats;`
- L54 _public member_ `FString FilterString;`
- L55 _public member_ `FOnCreateDatasmithImportHandler Handler;`

#### class `IDatasmithContentEditorModule`  
`class IDatasmithContentEditorModule : public IModuleInterface`  
_L62-136_
- inherits: `IModuleInterface`
- desc: The public interface of the DatasmithContent module
- L72 _public function_ `static inline IDatasmithContentEditorModule& Get()` — Singleton-like access to IDatasmithContentEditorModule @return Returns DatasmithContent singleton instance, loading the module on demand if needed
- L82 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L90 _public prototype_ `virtual void RegisterSpawnDatasmithSceneActorsHandler( FOnSpawnDatasmithSceneActors SpawnActorsDelegate ) = 0;` — Delegate to spawn the actors related to a Datasmith scene. Called when the user triggers the action in the UI.
- L91 _public prototype_ `virtual void UnregisterSpawnDatasmithSceneActorsHandler( FOnSpawnDatasmithSceneActors SpawnActorsDelegate ) = 0;`
- L92 _public prototype_ `virtual FOnSpawnDatasmithSceneActors GetSpawnDatasmithSceneActorsHandler() const = 0;`
- L97 _public prototype_ `virtual void RegisterDatasmithSceneEditorHandler(FOnCreateDatasmithSceneEditor InCreateDatasmithSceneEditor) = 0;` — Delegate to creation of the datasmith scene editor. The action is in this module while the datasmith scene editor is in its own plugin
- L98 _public prototype_ `virtual void UnregisterDatasmithSceneEditorHandler(FOnCreateDatasmithSceneEditor InCreateDatasmithSceneEditor) = 0;`
- L99 _public prototype_ `virtual FOnCreateDatasmithSceneEditor GetDatasmithSceneEditorHandler() const = 0;`
- L104 _public prototype_ `virtual void RegisterDatasmithImporter(const void* Registrar, const FImporterDescription& ImporterDescription) = 0;` — Delegate to creation of the datasmith scene editor. The action is in this module while the datasmith scene editor is in its own plugin
- L105 _public prototype_ `virtual void UnregisterDatasmithImporter(const void* Registrar) = 0;`
- L106 _public prototype_ `virtual TArray<FImporterDescription> GetDatasmithImporters() = 0;`
- L111 _public prototype_ `virtual void RegisterSetAssetAutoReimportHandler(FOnSetAssetAutoReimport&& SetAssetAutoReimportDelegate) = 0;` — Delegate to enable or disable AutoReimport of an asset.
- L112 _public prototype_ `virtual void UnregisterSetAssetAutoReimportHandler(FDelegateHandle InHandle) = 0;`
- L113 _public prototype_ `virtual TOptional<bool> SetAssetAutoReimport(UObject* Asset, bool bEnabled) const = 0;`
- L118 _public prototype_ `virtual void RegisterIsAssetAutoReimportAvailableHandler(FOnIsAssetAutoReimportAvailable&& IsAssetAutoReimportAvailableDelegate) = 0;` — Delegate returning if the AutoReimport feature is available for a given asset.
- L119 _public prototype_ `virtual void UnregisterIsAssetAutoReimportAvailableHandler(FDelegateHandle InHandle) = 0;`
- L120 _public prototype_ `virtual TOptional<bool> IsAssetAutoReimportAvailable(UObject* Asset) const = 0;`
- L125 _public prototype_ `virtual void RegisterIsAssetAutoReimportEnabledHandler(FOnIsAssetAutoReimportEnabled&& IsAssetAutoReimportEnabledDelegate) = 0;` — Delegate returning if the AutoReimport is currently active for a given asset.
- L126 _public prototype_ `virtual void UnregisterIsAssetAutoReimportEnabledHandler(FDelegateHandle InHandle) = 0;`
- L127 _public prototype_ `virtual TOptional<bool> IsAssetAutoReimportEnabled(UObject* Asset) const = 0;`
- L129 _public prototype_ `virtual void RegisterBrowseExternalSourceUriHandler(FOnBrowseExternalSourceUri&& BrowseExternalSourceUriDelegate) = 0;`
- L130 _public prototype_ `virtual void UnregisterBrowseExternalSourceUriHandler(FDelegateHandle InHandle) = 0;`
- L131 _public prototype_ `virtual bool BrowseExternalSourceUri(FName UriScheme, const FString& DefaultUri, FString& OutSourceUri, FString& OutFallbackFilepath) const = 0;`
- L133 _public prototype_ `virtual void RegisterGetSupportedUriSchemeHandler(FOnGetSupportedUriSchemes&& GetSupportedUriSchemeDelegate) = 0;`
- L134 _public prototype_ `virtual void UnregisterGetSupportedUriSchemeHandler(FDelegateHandle InHandle) = 0;`
- L135 _public prototype_ `virtual TOptional<TArray<FName>> GetSupportedUriScheme() const = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define DATASMITHCONTENTEDITOR_MODULE_NAME TEXT("DatasmithContentEditor")`
- L37 _delegate_ `DECLARE_DELEGATE_TwoParams( FOnSpawnDatasmithSceneActors, class ADatasmithSceneActor*, bool );`
- L37 _prototype_ `DECLARE_DELEGATE_TwoParams( FOnSpawnDatasmithSceneActors, class ADatasmithSceneActor*, bool );`
- L38 _delegate_ `DECLARE_DELEGATE_ThreeParams( FOnCreateDatasmithSceneEditor, const EToolkitMode::Type, const TSharedPtr< class IToolkitHost >&, class UDatasmithScene*);`
- L38 _prototype_ `DECLARE_DELEGATE_ThreeParams( FOnCreateDatasmithSceneEditor, const EToolkitMode::Type, const TSharedPtr< class IToolkitHost >&, class UDatasmithScene*);`
- L39 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IDataprepImporterInterface>, FOnCreateDatasmithImportHandler );`
- L39 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<IDataprepImporterInterface>, FOnCreateDatasmithImportHandler );`
- L41 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnSetAssetAutoReimport, UObject* , bool );`
- L41 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnSetAssetAutoReimport, UObject* , bool );`
- L42 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsAssetAutoReimportAvailable, UObject* );`
- L42 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsAssetAutoReimportAvailable, UObject* );`
- L43 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsAssetAutoReimportEnabled, UObject* );`
- L43 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnIsAssetAutoReimportEnabled, UObject* );`
- L44 _delegate_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnBrowseExternalSourceUri, FName , const FString& , FString& , FString& );`
- L44 _prototype_ `DECLARE_DELEGATE_RetVal_FourParams(bool, FOnBrowseExternalSourceUri, FName , const FString& , FString& , FString& );`
- L45 _delegate_ `DECLARE_DELEGATE_RetVal(const TArray<FName>&, FOnGetSupportedUriSchemes);`
- L45 _prototype_ `DECLARE_DELEGATE_RetVal(const TArray<FName>&, FOnGetSupportedUriSchemes);`

### `Plugins/Enterprise/DatasmithContent/Source/DatasmithContentEditor/Public/DatasmithContentEditorStyle.h` (Public)


#### class `FDatasmithContentEditorStyle`  
`class FDatasmithContentEditorStyle`  
_L11-25_
- desc: Contains a collection of named properties (StyleSet) that guide the appearance of Datasmith related UI.
- L14 _public prototype_ `static void Initialize();`
- L15 _public prototype_ `static void Shutdown();`
- L16 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L18 _public prototype_ `static FName GetStyleSetName();`
- L21 _private prototype_ `static FString InContent(const FString& RelativePath, const TCHAR* Extension);`
- L24 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATASMITHCONTENTEDITOR_API`
