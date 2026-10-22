# Plugins / CineAssemblyToolsEditor

- module root: `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor`
- headers: 46; symbols: 963
- symbol kinds: class=47, delegate=14, enum=6, enumerator=16, externvar=1, function=33, macro=4, member=212, namespace=10, prototype=607, struct=13
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, CineAssemblyTools, CinematicCamera, ClassViewer, ContentBrowser, ContentBrowserData, Core, CoreUObject, DesktopPlatform, DeveloperSettings, DirectoryPlaceholder, EditorSubsystem, EditorWidgets, Engine, InputCore, Json, JsonUtilities, LevelSequence, LevelSequenceEditor, MovieRenderPipelineCore, MovieScene, MovieSceneTools, MovieSceneTracks, NamingTokens, NamingTokensUI, Projects, PropertyEditor, Sequencer, SequencerCore, SharedSettingsWidgets, Slate, SlateCore, SourceControl, StructUtilsEditor, TakeRecorder, TakesCore, TimeManagement, ToolMenus, ToolWidgets, UniversalObjectLocator, UnrealEd, WorkspaceMenuStructure
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/AssetDefinition_CineAssembly.h` (Private)


#### class `UAssetDefinition_CineAssembly`  
`class UAssetDefinition_CineAssembly : public UAssetDefinition_LevelSequence`  
_L11-27_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_LevelSequence`
- desc: Asset definition for a UCineAssembly asset
- L17 _protected prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _protected prototype_ `virtual FText GetAssetDisplayName(const FAssetData& AssetData) const override;`
- L19 _protected prototype_ `virtual FText GetAssetDescription(const FAssetData& AssetData) const override;`
- L20 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L21 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L23 _protected prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L24 _protected prototype_ `virtual TArray<FAssetData> PrepareToActivateAssets(const FAssetActivateArgs& ActivateArgs) const override;`
- L25 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/AssetDefinition_CineAssemblySchema.h` (Private)


#### class `UAssetDefinition_CineAssemblySchema`  
`class UAssetDefinition_CineAssemblySchema : public UAssetDefinition`  
_L11-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition`
- desc: Asset definition for a UCineAssemblySchema asset
- L17 _protected prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L18 _protected prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _protected prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L20 _protected prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _protected prototype_ `virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;`
- L22 _protected prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L23 _protected prototype_ `virtual FAssetSupportResponse CanRename(const FAssetData& InAsset) const override;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblyAssetTags.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace CineAssemblyTools` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::CineAssemblyTools`)
- L13 _prototype_ `void LogMissingSchemaThumbnailTagOnce(FName SchemaPackageName);` (scope `UE::CineAssemblyTools::Private`) — Logs (once per schema asset) a diagnostic when the schema's thumbnail registry tag does not exist.
- L16 _prototype_ `FGuid GetSchemaID(const FAssetData& AssetData, FName TagName);` (scope `UE::CineAssemblyTools::Private`) — Reads a schema GUID from the named registry tag on the input asset data.
- L19 _prototype_ `FSoftObjectPath GetSchemaThumbnailPath(const FAssetData& SchemaAssetData);` (scope `UE::CineAssemblyTools::Private`) — Reads the thumbnail texture path from a schema's asset registry tags.
- L22 _prototype_ `FAssetData GetSchemaAssetData(const FAssetData& AssemblyAssetData);` (scope `UE::CineAssemblyTools::Private`) — Returns the Schema FAssetData referenced by the input Assembly asset

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblyCustomization.h` (Private)


#### class `FCineAssemblyCustomization`  
`class FCineAssemblyCustomization : public IDetailCustomization`  
_L21-101_
- inherits: `IDetailCustomization`
- desc: Detail customization for UCineAssembly
- L25 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L28 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this detail layout class for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); ~ Begin IDetailCustomization interface
- L33 _private prototype_ `void CustomizeDefaultCategory(IDetailLayoutBuilder& DetailBuilder);` — Utility functions to customize each of the categories
- L34 _private prototype_ `void CustomizeMetadataCategory(IDetailLayoutBuilder& DetailBuilder);`
- L35 _private prototype_ `void CustomizeManagedAssetsCategory(IDetailLayoutBuilder& DetailBuilder);`
- L38 _private prototype_ `TSharedRef<SWidget> MakeMetadataWidget(IDetailLayoutBuilder& DetailBuilder, const FAssemblyMetadataDesc& MetadataDesc);` — Creates the appropriate widget for a metadata field based on its type
- L44 _private prototype_ `TSharedRef<SWidget> MakeStringValueWidget(const FAssemblyMetadataDesc& MetadataDesc);` — Given a FAssemblyMetadataDesc, makes a STemplateStringEditableTextBox for a string value that has bEvaluateTokens set to true, and a SMultiLineEditableTextBox for a string value that has bEvaluateTokens set to false.
- L47 _private prototype_ `TSharedRef<SWidget> BuildProductionNameMenu();` — Builds the drop-down menu list of productions
- L50 _private prototype_ `bool ShouldFilterAssetBySchema(const FAssetData& InAssetData, FSoftObjectPath Schema);` — Determines whether the input asset should be filtered out of an object picker widget, based on whether it is of the input schema type
- L60 _private prototype_ `FText GetMetadataTokenStringValue(const FString& InMetadataKey) const;` — Returns the template text for a token string metadata property
- L63 _private prototype_ `void SetMetadataTokenStringValue(const FString& InMetadataKey, const FText& InValue, ETemplateStringType InTemplateStringType);` — Updates either the template text or resolved text for a token string metadata property
- L66 _private prototype_ `void AddAssetRowsRecursive(IDetailCategoryBuilder& Category, UCineAssembly* Assembly, int32 Depth);` — Recursively adds rows to the input category for the input Assembly's SubAssemblies and AssociatedAssets, using the recursion depth to indent properly
- L69 _private prototype_ `void AddSubAssemblyRow(IDetailCategoryBuilder& Category, UCineAssembly* SubAssembly, int32 Depth);` — Adds an asset row for a managed SubAssembly
- L72 _private prototype_ `void AddAssociatedAssetRow(IDetailCategoryBuilder& Category, UCineAssembly* OwnerAssembly, const FGuid& AssetID, int32 Depth);` — Adds an asset row for a managed Associated Asset
- L75 _private prototype_ `FReply OnSubAssemblyRowClicked(const FGeometry&, const FPointerEvent& MouseEvent, UCineAssembly* SubAssembly);` — Callback when a SubAssembly asset row is clicked. Right-click shows a menu to edit the SubAssembly's label and metadata
- L78 _private prototype_ `FReply OnAssociatedAssetRowClicked(const FGeometry&, const FPointerEvent& MouseEvent, UCineAssembly* OwnerAssembly, FGuid AssetID);` — Callback when an Associated Asset row is clicked. Right-click shows a menu to edit the descriptor's Label
- L82 _private member_ `UCineAssembly* CustomizedCineAssembly;` — The assembly being customized
- L85 _private member_ `TArray<TStrongObjectPtr<UCineAssemblyNamingTokensContext>> ManagedAssetRowTokenContexts;` — Naming Token Contexts for each asset row, referencing the correct SubAssembly for token resolution
- L88 _private member_ `TSharedPtr<FLeadingZeroNumericTypeInterface> LeadingZeroTypeInterface;` — Type interface for a numeric entry box that supports leading zeroes
- L91 _private member_ `TStrongObjectPtr<UCineAssemblyNamingTokensContext> NamingTokenContext;` — Context object allowing cine assembly tokens to evaluate
- L94 _private member_ `FNamingTokenFilterArgs FilterArgs;` — Filter allowing cine assembly tokens to evaluate without the namespace prefix
- L97 _private member_ `bool bIsMetadataReadOnly = true;` — True if the metadata properties are read-only, false if they are editable
- L100 _private member_ `bool bIsBeingConfigured = false;` — True if the assembly is being configured (transient), false if viewing an existing assembly

#### enum `FCineAssemblyCustomization::ETemplateStringType`  
`enum class ETemplateStringType`  
_L53-57_
- desc: Used to specify which member of an FTemplateString is desired
- L55 _public enumerator_ `Template`
- L56 _public enumerator_ `Resolved`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblyFactory.h` (Private)


#### enum `EDuplicateExternalAssetPreference`  
`enum class EDuplicateExternalAssetPreference : uint8`  
_L14-19_
- reflection: `UENUM(BlueprintType)`
- desc: Options for handling the duplication of assets (subsequences, sublevels, etc.) that live outside of the source assembly's content tree
- L16 _public enumerator_ `DuplicateIntoAssemblyFolder UMETA(ToolTip = "Duplicate external assets into the same folder as the duplicate assembly")`
- L17 _public enumerator_ `DuplicateIntoOriginalFolder UMETA(ToolTip = "Duplicate external assets into the same folder as the original asset")`
- L18 _public enumerator_ `DoNotDuplicate UMETA(ToolTip = "Do not duplicate external assets. Maintain the reference to the original asset.")`

#### class `UCineAssemblyFactory`  
`class UCineAssemblyFactory : public UFactory`  
_L26-76_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Factory class used to create new UCineAssembly objects Before creating a new Cine Assembly, the factory will spawn a new window to configure the properties of the asset that is being created.
- L36 _public prototype_ `static bool CreateConfiguredAssembly(UCineAssembly* ConfiguredAssembly, const FString& CreateAssetPath);` — Takes a pre-configured, transient assembly, creates a valid package for it, and initializes it. Returns true on success. Returns false if the assembly could not be persisted (e.g. resulting package path was too long). When called recursively for a SubAssembly, a false return is the caller's signal to remove the dangling section from the parent.
- L39 _public prototype_ `static void CreateConfiguredSubAssemblies(UCineAssembly* ConfiguredAssembly, const FString& CreateAssetPath);` — Create a valid package for each SubAssembly found in a SubSequence or Shot Track of the input Assembly's MovieScene
- L42 _public prototype_ `static void CreateSubFolders(UCineAssembly* Assembly);` — Create the content folders specified by the input Assembly's DefaultFolderNames.
- L48 _public prototype_ `static void DuplicateSubsequences(UCineAssembly* Assembly, EDuplicateExternalAssetPreference ExternalAssetPreference = EDuplicateExternalAssetPreference::DuplicateIntoAssemblyFolder);` — Recursively duplicate all subsequences of the input Assembly. This will skip over managed SubAssemblies which are handled by CreateConfiguredSubAssemblies. Note: The input assembly should have its SourceAssemblyPath set before calling this, so that relative paths can be computed correctly for the duplicated subsequences.
- L51 _public prototype_ `static void CreateAssociatedAssets(UCineAssembly* ConfiguredAssembly);` — Create new assets for each associated asset definition on the input Assembly
- L54 _public prototype_ `static void DuplicateAssociatedAsset(UCineAssembly* DuplicatedAssembly, FAssemblyAssociatedAssetDesc& AssetDesc, EDuplicateExternalAssetPreference ExternalAssetPreference = EDuplicateExternalAssetPreference::DuplicateIntoAssemblyFolder);` — Duplicate the input asset associated with the duplicated assembly
- L57 _public prototype_ `static void DuplicateAssociatedAssets(UCineAssembly* DuplicatedAssembly, EDuplicateExternalAssetPreference ExternalAssetPreference = EDuplicateExternalAssetPreference::DuplicateIntoAssemblyFolder);` — Duplicate the associated assets of a duplicated assembly, updating each definition's CreatedAsset to point to the duplicate
- L60 _public prototype_ `static void PopulateLinkedMetadataRecursive(UCineAssembly* Assembly);` — Populate metadata fields of the input assembly (and managed SubAssemblies) that are linked to associated assets
- L63 _public prototype_ `static FString MakeAssemblyPackageName(UCineAssembly* ConfiguredAssembly, const FString& CreateAssetPath);` — Takes a CineAssembly and a creation path and makes a formatted CineAssembly package name.
- L66 _public prototype_ `static bool MakeUniqueNameAndPath(UCineAssembly* ConfiguredAssembly, const FString& CreateAssetPath, FString& UniquePackageName, FString& UniqueAssetName);` — Recursively evaluates the default assembly name and path until a unique combination is found
- L69 _protected prototype_ `UCineAssemblyFactory();`
- L72 _protected prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L73 _protected prototype_ `virtual bool CanCreateNew() const override;`
- L74 _protected prototype_ `virtual bool ConfigureProperties() override;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblyMetadataCustomization.h` (Private)


#### class `FCineAssemblyMetadataCustomization`  
`class FCineAssemblyMetadataCustomization : public IPropertyTypeCustomization`  
_L12-56_
- inherits: `IPropertyTypeCustomization`
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L27 _private prototype_ `TSharedRef<SWidget> MakeStringDefaultValueWidget(FAssemblyMetadataDesc& MetadataDesc, TSharedRef<IPropertyHandle> PropertyHandle);` — Given a FAssemblyMetadataDesc, makes a SNamingTokensEditableTextBox for a string default value that has bEvaluateTokens set to true, and a SMultiLineEditableTextBox for a string default value that has bEvaluateTokens set to false.
- L30 _private prototype_ `void CustomizeKeyProperty(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, FAssemblyMetadataDesc& MetadataDesc);` — Customizes the metadata desc Key property
- L33 _private prototype_ `void RenameMetadataKey(TSharedRef<IPropertyHandle> KeyPropertyHandle, const FString& NewKeyName);` — Renames the metadata key via its PropertyHandle and migrates the TemplateSequence's MetadataLinks entry (if any) from the old key to the new one
- L36 _private prototype_ `bool ValidateKeyName(const FText& InText, FText& OutErrorMessage) const;` — Checks whether the proposed key name is valid (not empty, not a duplicate)
- L39 _private prototype_ `FString MakeUniqueKeyName();` — Returns a unique key name within the context of the schema
- L42 _private prototype_ `void ValidateMetadataLink();` — Validates the active metadata link against the current metadata field properties and removes the link if no longer valid
- L45 _private prototype_ `bool IsLinkedAssetCompatible(const FGuid& InLinkedAssetID, const FAssemblyMetadataDesc& InMetadataDesc) const;` — Whether the currently linked asset is compatible with the input metadata field properties
- L49 _private member_ `UCineAssemblySchema* Schema;` — The schema that owns the metadata desc struct being customized
- L52 _private member_ `int32 ArrayIndex;` — The array index of the metadata struct being customized
- L55 _private member_ `TSharedPtr<FLeadingZeroNumericTypeInterface> LeadingZeroTypeInterface;` — Type interface for a numeric entry box that supports leading zeroes

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblySchemaCustomization.h` (Private)


#### class `FCineAssemblySchemaCustomization`  
`class FCineAssemblySchemaCustomization : public IDetailCustomization`  
_L13-44_
- inherits: `IDetailCustomization`
- desc: Detail customization for UCineAssemblySchema
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this detail layout class for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); ~ Begin IDetailCustomization interface
- L25 _private prototype_ `FString MakeUniqueSchemaName() const;` — Generate a unique schema name
- L28 _private prototype_ `bool DoesSchemaExistWithName(const FString& SchemaName) const;` — Returns true if a schema already exists with the input name
- L31 _private prototype_ `bool ValidateSchemaName(const FText& InText, FText& OutErrorMessage) const;` — Validates the user input text for the associated properties
- L32 _private prototype_ `bool ValidateDefaultAssemblyName(const FText& InText, FText& OutErrorMessage) const;`
- L35 _private prototype_ `bool IsSchemaNameResetToDefaultVisible(TSharedPtr<IPropertyHandle> SchemaNamePropertyHandle) const;` — Implements "reset to default" behavior for the schema name property
- L36 _private prototype_ `void OnSchemaNameResetToDefault(TSharedPtr<IPropertyHandle> SchemaNamePropertyHandle);`
- L40 _private member_ `UCineAssemblySchema* CustomizedSchema;` — The assembly schema being customized
- L43 _private member_ `FString OriginalSchemaName;` — Original name of the schema being customized

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblySchemaFactory.h` (Private)


#### class `UCineAssemblySchemaFactory`  
`class UCineAssemblySchemaFactory : public UFactory`  
_L16-32_
- reflection: `UCLASS(hidecategories = Object)`
- inherits: `UFactory`
- desc: Factory class used to create new UCineAssemblySchema objects Before creating a new assembly schema, the factory will spawn a window to configure the properties of the asset that is being created
- L22 _public prototype_ `static void CreateConfiguredSchema(UCineAssemblySchema* ConfiguredSchema, const FString& CreateAssetPath);` — Takes a pre-configured, transient schema, creates a valid package for it, and initializes it
- L25 _protected prototype_ `UCineAssemblySchemaFactory();`
- L28 _protected prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L29 _protected prototype_ `virtual bool CanCreateNew() const override;`
- L30 _protected prototype_ `virtual bool ConfigureProperties() override;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblyToolsAnalytics.h` (Private)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CineAssemblyToolsAnalytics` (scope `UE`)
- L11 _prototype_ `void RecordEvent_CreateAssembly(const UCineAssembly* const Assembly);` (scope `UE::CineAssemblyToolsAnalytics`)
- L12 _prototype_ `void RecordEvent_CreateAssemblySchema();` (scope `UE::CineAssemblyToolsAnalytics`)
- L13 _prototype_ `void RecordEvent_CreateProduction();` (scope `UE::CineAssemblyToolsAnalytics`)
- L14 _prototype_ `void RecordEvent_ProductionAddAssetNaming();` (scope `UE::CineAssemblyToolsAnalytics`)
- L15 _prototype_ `void RecordEvent_ProductionCreateTemplateFolders();` (scope `UE::CineAssemblyToolsAnalytics`)
- L16 _prototype_ `void RecordEvent_RecordAssembly();` (scope `UE::CineAssemblyToolsAnalytics`)

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblyToolsEditorModule.h` (Private)


#### class `FCineAssemblyToolsEditorModule`  
`class FCineAssemblyToolsEditorModule : public ICineAssemblyToolsEditorModule`  
_L25-118_
- inherits: `ICineAssemblyToolsEditorModule`
- L30 _public prototype_ `virtual void StartupModule() override;`
- L31 _public prototype_ `virtual void ShutdownModule() override;`
- L35 _public prototype_ `void OpenSchemaForEdit(UCineAssemblySchema* Schema);` — Opens a window to edit the properties of the input assembly schema
- L38 _public function_ `inline const FProductionExtensions& GetProductionExtensions()` — Get the ProductionExtensions object.
- L41 _public prototype_ `virtual void RegisterProductionExtension(const UScriptStruct& DataScriptStruct) override;`
- L42 _public prototype_ `virtual void UnregisterProductionExtension(const UScriptStruct& DataScriptStruct) override;`
- L43 _public prototype_ `virtual void RegisterProductionWizardCustomization(const UScriptStruct& ForDataScriptStruct, FGetWidget MakeCustomWidget, TAttribute<FText> Label, TAttribute<FSlateIcon> Icon, bool bShowProductionSelection, bool bHideInWizard) override;`
- L45 _public prototype_ `virtual void UnregisterProductionWizardCustomization(const UScriptStruct& ForDataScriptStruct) override;`
- L46 _public prototype_ `virtual void RegisterProductionWizardUserSettings(const FName Name, FGetWidget MakeCustomWidget, TAttribute<FText> Label, TAttribute<FSlateIcon> Icon) override;`
- L47 _public prototype_ `virtual void UnregisterProductionWizardUserSettings(const FName Name) override;`
- L51 _private prototype_ `void OnPostEngineInit();`
- L54 _private prototype_ `TSharedRef<SDockTab> SpawnProductionWizard(const FSpawnTabArgs& SpawnTabArgs);` — Spawns a nomad tab for the Production Wizard tool
- L57 _private prototype_ `TSharedRef<SDockTab> SpawnAssemblyTab(const FSpawnTabArgs& SpawnTabArgs, UCineAssembly* Assembly);` — Spawns a nomad tab for an Assembly asset to edit its properties
- L58 _private prototype_ `TSharedRef<SDockTab> SpawnAssemblyTab(const FSpawnTabArgs& SpawnTabArgs, FGuid AssemblyGuid);`
- L59 _private prototype_ `TSharedRef<SDockTab> SpawnAssemblyTab(const FSpawnTabArgs& SpawnTabArgs, TSharedPtr<SCineAssemblyPropertyEditor> Widget);`
- L62 _private prototype_ `TSharedRef<SDockTab> SpawnSchemaTab(const FSpawnTabArgs& SpawnTabArgs, UCineAssemblySchema* Schema);` — Spawns a nomad tab for an Schema asset to edit its properties
- L63 _private prototype_ `TSharedRef<SDockTab> SpawnSchemaTab(const FSpawnTabArgs& SpawnTabArgs, FGuid SchemaGuid);`
- L64 _private prototype_ `TSharedRef<SDockTab> SpawnSchemaTab(const FSpawnTabArgs& SpawnTabArgs, TSharedPtr<SCineAssemblySchemaWindow> Widget);`
- L67 _private prototype_ `void RegisterMenus();` — Add context menu actions
- L70 _private prototype_ `void RegisterTokens();` — Register additional tokens with the cine assembly tokens
- L73 _private prototype_ `void OnSequenceSet(UMoviePipelineExecutorJob* Job, ULevelSequence* Sequence);` — Called whenever a job has its sequence set.
- L76 _private prototype_ `void OpenAssemblyForEdit(UCineAssembly* Assembly);` — Opens a window to edit the properties of the input assembly
- L79 _private prototype_ `bool TryGetNextTab(const TMap<FTabId, FGuid>& TabMap, FTabId& OutTabId);` — Returns the next available tab name in the map of managed tabs. If there are no available tabs, returns false
- L82 _private prototype_ `void OnAssetDeleted(UObject* Object);` — Callback when an asset is deleted which allows us to check if it was a Cine Assembly and then close the tab for that Assembly (if one was open)
- L85 _private prototype_ `FGuid FindTabAssetInConfig(FName TabName);` — Look up the tab name in the open tabs config section and return the asset ID associated with that tab (if there is one)
- L88 _private prototype_ `void SaveOpenTabs(const TMap<FTabId, FGuid>& TabMap);` — Write out all of the tabs in the input tab map that are currently open (i.e. have a valid asset ID)
- L91 _private prototype_ `void ExtendLevelEditorToolbar();` — Extend the level editor toolbar with our menu.
- L94 _private prototype_ `TSharedRef<SWidget> GenerateProductionLevelEditorToolbarMenu();` — Generates the toolbar button widget.
- L97 _private prototype_ `void OnSchemaPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);` — Subscribe to CineAssemblySchema property changes in order to refresh Style brushes for Schema thumbnails
- L101 _private member_ `TUniquePtr<FCineAssemblyTakeRecorderIntegration> TakeRecorderIntegration;` — Manages all integration of Cinematic Assembly Tools with Take Recorder.
- L104 _private member_ `FProductionExtensions ProductionExtensions;` — Extensions for the Production data and Production Wizard.
- L107 _private member_ `TMap<FTabId, FGuid> ManagedAssemblyTabs;` — Map of TabIds to Asset IDs to track which assets are open in which tabs
- L108 _private member_ `TMap<FTabId, FGuid> ManagedSchemaTabs;`
- L111 _private member_ `TArray<TSharedPtr<FCinematicProduction>> ProductionList;` — Available productions.
- L113 _private member_ `static const FString OpenTabSection;`
- L115 _private member_ `FDelegateHandle OnSequenceSetHandle;`
- L116 _private member_ `FDelegateHandle RegisterSubTrackEditorHandle;`
- L117 _private member_ `FDelegateHandle SchemaPropertyChangedHandle;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace CineAssemblyTools` (scope `UE`)
- L22 _externvar_ `extern FAssetCategoryPath CineAssemblyAssetCategory;` (scope `UE::CineAssemblyTools`)

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CineAssemblyToolsStyle.h` (Private)


#### class `FCineAssemblyToolsStyle`  
`class FCineAssemblyToolsStyle : public FSlateStyleSet`  
_L13-35_
- inherits: `FSlateStyleSet`
- desc: Slate style set that defines all the styles for the Cinematic Assembly Tools
- L16 _public member_ `static FName StyleName;`
- L19 _public prototype_ `static FCineAssemblyToolsStyle& Get();` — Access the singleton instance for this style set
- L22 _public prototype_ `FName GetThumbnailBrushNameForSchema(const FGuid& SchemaGuid) const;` — Returns the name of the thumbnail brush associated with the schema identified by the input GUID
- L29 _public prototype_ `void SetThumbnailBrushTextureForSchema(const FGuid& SchemaGuid, UTexture2D* BrushTexture);` — Sets the texture resource used by the thumbnail brush associated with the schema identified by the input GUID. If the schema does not have a thumbnail brush associated with it yet, a new one will be created first. If the texture resource is null, the brush will fallback to using a predefined icon.
- L33 _private prototype_ `FCineAssemblyToolsStyle();`
- L34 _private prototype_ `~FCineAssemblyToolsStyle();`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/CinematicProductionCustomization.h` (Private)


#### class `FCinematicProductionCustomization`  
`class FCinematicProductionCustomization : public IPropertyTypeCustomization`  
_L10-19_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for FCinematicProduction
- L13 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L17 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/LeadingZeroNumericTypeInterface.h` (Private)


#### struct `FLeadingZeroNumericTypeInterface`  
`struct FLeadingZeroNumericTypeInterface : public TDefaultNumericTypeInterface<int32>`  
_L7-18_
- inherits: `TDefaultNumericTypeInterface<int32>`
- L9 _public prototype_ `FLeadingZeroNumericTypeInterface() = default;`
- L12 _public prototype_ `virtual FString ToString(const int32& Value) const override;`
- L13 _public prototype_ `virtual TOptional<int32> FromString(const FString& InString, const int32& InExistingValue) override;`
- L17 _private member_ `int32 MinimumIntegralDigits = 1;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/ProductionExtensions.h` (Private)


#### struct `FProductionWizardCustomizationParameters`  
`struct FProductionWizardCustomizationParameters`  
_L12-28_
- desc: Struct holding details on a Production Settings customization for the Production Wizard interface.
- L15 _public member_ `TAttribute<FText> Label;` — Label override to display on the tab in the Production Wizard.
- L18 _public member_ `TAttribute<FSlateIcon> Icon;` — Icon override to display on the tab in the Production Wizard.
- L21 _public member_ `FGetWidget MakeCustomWidget = nullptr;` — Callback to create the SWidget to display in the Production Wizard.
- L24 _public member_ `bool bShowProductionSelection = true;` — Whether the production selection combo box should be shown for this customization in the Production Wizard.
- L27 _public member_ `bool bHideInWizard = false;` — Hides the tab and widget completely from the Production Wizard.

#### struct `FProductionWizardUserSettingsExtensionParameters`  
`struct FProductionWizardUserSettingsExtensionParameters`  
_L31-41_
- desc: Struct holding details on a Users Settings extension for the Production Wizard interface.
- L34 _public member_ `FText Label;` — Label for the tab.
- L37 _public member_ `TAttribute<FSlateIcon> Icon;` — Optional icon to display on the tab.
- L40 _public member_ `FGetWidget MakeCustomWidget = nullptr;` — Callback to create the widget to display.

#### class `FProductionExtensions`  
`class FProductionExtensions`  
_L44-89_
- desc: Class that allows registering of extensions to Productions and the Production Wizard.
- L48 _public prototype_ `void RegisterProductionExtension(const UScriptStruct& DataScriptStruct);` — Register a new production extension struct type.
- L51 _public prototype_ `void UnregisterProductionExtension(const UScriptStruct& DataScriptStruct);` — Unregister a Production extension struct type.
- L57 _public prototype_ `void RegisterProductionWizardCustomization(const UScriptStruct& ForDataScriptStruct, FGetWidget MakeCustomWidget, TAttribute<FText> Label = TAttribute<FText>(), TAttribute<FSlateIcon> Icon = TAttribute<FSlateIcon>(), bool bShowProductionSelection = true, bool bHideInWizard = false);` — Register a customization for the Production Wizard for the given extended data struct type. The extended data struct type must already have been registered as a Production extension using RegisterProductionExtension.
- L62 _public prototype_ `void UnregisterProductionWizardCustomization(const UScriptStruct& ForDataScriptStruct);` — Unregister the registered customization for the given extended data struct type.
- L65 _public prototype_ `void RegisterProductionWizardUserSettings(const FName Name, FGetWidget MakeCustomWidget, TAttribute<FText> Label = TAttribute<FText>(), TAttribute<FSlateIcon> Icon = TAttribute<FSlateIcon>());` — Register a custom User Setting tab to show in the Production wizard by providing a callback to create the SWidget to show.
- L69 _public prototype_ `void UnregisterProductionWizardUserSettings(const FName Name);` — Unregister the custom User Settings tab from the Production Wizard with the given name.
- L72 _public function_ `inline const TSet<const UScriptStruct*>& GetProductionExtensions() const` — Gets all registered Production Extension types.
- L75 _public function_ `inline const TMap<const UScriptStruct*, FProductionWizardCustomizationParameters>& GetProductionWizardCustomizations() const` — Get registered production wizard customizations.
- L78 _public function_ `inline const TMap<FName, FProductionWizardUserSettingsExtensionParameters>& GetProductionWizardUserSettingsExtensions() const` — Get the map of all registered custom Production Wizard User Settings tabs.
- L82 _private member_ `TSet<const UScriptStruct*> ProductionExtensions;` — Set of all registered Production Extension types.
- L85 _private member_ `TMap<const UScriptStruct*, FProductionWizardCustomizationParameters> ProductionWizardCustomizations;` — Map of all registered Production Wizard Production Settings customizations.
- L88 _private member_ `TMap<FName, FProductionWizardUserSettingsExtensionParameters> ProductionWizardExtendedUserSettings;` — Map of all registered Production Wizard Users Settings extensions.

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/ProductionSettingsCustomization.h` (Private)


#### class `FProductionSettingsCustomization`  
`class FProductionSettingsCustomization : public IDetailCustomization`  
_L15-37_
- inherits: `IDetailCustomization`
- desc: Detail customization for UProductionSettings
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this detail layout class for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); ~ Begin IDetailCustomization interface
- L27 _private prototype_ `void SetActiveProduction(FGuid ProductionID);` — Set the active production of the production project settings
- L30 _private prototype_ `FText GetActiveProductionName() const;` — Get the name of the currently active production
- L33 _private prototype_ `TSharedRef<SWidget> BuildProductionNameMenu();` — Build the menu widget for the production name combo button
- L36 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;` — Property Utils, used to refresh the property settings details when changing the active production

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/Sequencer/CineAssemblySchemaSequencerCustomization.h` (Private)


#### class `FCineAssemblySchemaSequencerCustomization`  
`class FCineAssemblySchemaSequencerCustomization : public ISequencerCustomization`  
_L10-23_
- inherits: `ISequencerCustomization`
- desc: Sequencer customization applied when a UCineAssembly is the focused sequence in a Schema window
- L13 _public prototype_ `FCineAssemblySchemaSequencerCustomization();`
- L15 _public prototype_ `virtual void RegisterSequencerCustomization(FSequencerCustomizationBuilder& Builder) override;`
- L16 _public prototype_ `virtual void UnregisterSequencerCustomization() override;`
- L19 _private prototype_ `ESequencerPasteSupport OnPaste();`
- L22 _private member_ `TArray<TUniquePtr<ISequencerCustomization>> BaseCustomizations;` — Customizations inherited from ULevelSequence that should be applied alongside this customization.

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/Sequencer/CineAssemblySchemaSpawnRegister.h` (Private)


#### class `FCineAssemblySchemaSpawnRegister`  
`class FCineAssemblySchemaSpawnRegister : public FMovieSceneSpawnRegister`  
_L8-29_
- inherits: `FMovieSceneSpawnRegister`
- desc: Movie scene spawn register that handles spawning objects in a Cine Assembly Schema's template sequence
- L11 _public prototype_ `FCineAssemblySchemaSpawnRegister();`
- L12 _public prototype_ `~FCineAssemblySchemaSpawnRegister() = default;`
- L16 _protected prototype_ `virtual UObject* SpawnObject(const FGuid& BindingId, UMovieScene& MovieScene, FMovieSceneSequenceIDRef Template, TSharedRef<const FSharedPlaybackState> SharedPlaybackState, int32 BindingIndex) override;`
- L17 _protected prototype_ `virtual UObject* SpawnObject(FMovieSceneSpawnable& Spawnable, FMovieSceneSequenceIDRef TemplateID, TSharedRef<const FSharedPlaybackState> SharedPlaybackState) override;`
- L19 _protected prototype_ `virtual void DestroySpawnedObject(UObject& Object, UMovieSceneSpawnableBindingBase* CustomSpawnableBinding) override;`
- L22 _protected prototype_ `virtual bool CanSpawnObject(UClass* InClass) const override;`
- L23 _protected prototype_ `virtual void SetupDefaultsForSpawnable(UObject* SpawnedObject, const FGuid& Guid, const TOptional<FTransformData>& TransformData, TSharedRef<ISequencer> Sequencer, USequencerSettings* Settings) override;`
- L28 _private member_ `TArray<TSharedRef<IMovieSceneObjectSpawner>> MovieSceneObjectSpawners;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/Sequencer/CineAssemblySequencerUtilities.h` (Private)


#### struct `FCineAssemblySequencerUtilities`  
`struct FCineAssemblySequencerUtilities`  
_L12-30_
- desc: Utility functions for Sequencer and MovieScene operations used by the Cine Assembly Tools
- L16 _public prototype_ `static void CreateCamera(TSharedRef<ISequencer> Sequencer);` — Create a new spawnable camera binding without actually spawning a camera
- L22 _public prototype_ `static void ReplaceSubSequence(UMovieSceneSubSection* InSubSection, UMovieSceneSequence* InSequence);` — Replace the Sequence in the input SubSection with the input Sequence If needed, the SubSection will be first unlocked to ensure the assignment is succesful, and then its original lock status is restored.
- L29 _public prototype_ `static void DuplicateMovieSceneContents(UMovieSceneSequence* InSrcSequence, UMovieSceneSequence* InDstSequence);` — Copy every root track and binding from InSrcSequence's MovieScene into InDstSequence's MovieScene. Tracks are deep-duplicated and Bindings are recreated with fresh GUIDs. Any relevant binding references are reassigned to the new GUIDs in the InDstSequence.

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/Sequencer/MovieSceneSubAssemblySectionCustomization.h` (Private)


#### class `FSubAssemblySectionDetailCustomization`  
`class FSubAssemblySectionDetailCustomization : public IDetailCustomization`  
_L14-30_
- inherits: `IDetailCustomization`
- desc: Detail Customization for UMovieSceneSubAssemblySection
- L18 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this customization for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — Makes a new instance of this customization for a specific detail view requesting it static TSharedRef<IDetailCustomization> MakeInstance(); ~ Begin IDetailCustomization interface
- L26 _private prototype_ `bool OnShouldFilterAsset(const FAssetData& InAssetData, const UCineAssemblySchema* OwningSchema);` — Determines whether the input asset should be filtered out of the Assembly Template asset picker
- L29 _private prototype_ `void AddMetadataOverrideRow(IDetailCategoryBuilder& Category, UMovieSceneSubAssemblySection* Section, const FAssemblyMetadataDesc& MetadataDesc);` — Adds a row to the input category to display a metadata override for the input metadata descriptor

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/Sequencer/SubAssemblySection.h` (Private)


#### class `FSubAssemblySection`  
`class FSubAssemblySection : public TSubSectionMixin<>, public TSharedFromThis<FSubAssemblySection>`  
_L14-59_
- inherits: `TSubSectionMixin<>,TSharedFromThis<FSubAssemblySection>`
- desc: An ISequencerSection that handles the UI of a UMovieSceneSubAssemblySection
- L17 _public prototype_ `FSubAssemblySection(TSharedPtr<ISequencer> InSequencer, UMovieSceneSubAssemblySection* InSection);`
- L21 _public prototype_ `virtual UMovieSceneSection* GetSectionObject() override;`
- L22 _public prototype_ `virtual FText GetSectionTitle() const override;`
- L23 _public prototype_ `virtual float GetSectionHeight(const UE::Sequencer::FViewDensityInfo& ViewDensity) const override;`
- L24 _public prototype_ `virtual TSharedRef<SWidget> GenerateSectionWidget() override;`
- L25 _public prototype_ `virtual int32 OnPaintSection(FSequencerSectionPainter& InPainter) const override;`
- L26 _public prototype_ `virtual FReply OnSectionDoubleClicked(const FGeometry& SectionGeometry, const FPointerEvent& MouseEvent) override;`
- L27 _public prototype_ `virtual void BuildSectionContextMenu(FMenuBuilder& MenuBuilder, const FGuid& ObjectBinding) override;`
- L28 _public prototype_ `virtual void CustomizePropertiesDetailsView(TSharedRef<IDetailsView> DetailsView, const FSequencerSectionPropertyDetailsViewCustomizationParams& InParams) const override;`
- L33 _private prototype_ `FText GetSectionText() const;` — Get the name of the sequence to display in the Section Widget
- L36 _private prototype_ `void SetSectionText(const FText& InText, ETextCommit::Type InCommitType);` — Set the name of the sequence in a template section
- L39 _private prototype_ `bool ValidateSectionText(const FText& InText, FText& OutErrorMessage) const;` — Validate the tokenized Subassembly name
- L42 _private prototype_ `FText GetOriginText() const;` — If this is a template section, return the name of the template object. Otherwise, return text indicating that this is a reference section.
- L45 _private prototype_ `FText GetLabelText() const;` — Returns the section's label wrapped in square brackets for display, or empty text if no label is set
- L48 _private prototype_ `EVisibility GetLabelVisibility() const;` — Visibility for the label line (hidden when no label is set)
- L51 _private prototype_ `bool HasDuplicateName() const;` — Returns true if this template section could produce a SubAssembly with the same resolved name as another template section in the same MovieScene
- L55 _private member_ `UMovieSceneSubAssemblySection* MovieSceneSubAssemblySection;` — MovieSceneSubAssemblySection handled by this sequencer section
- L58 _private member_ `TSharedPtr<SNamingTokensEditableTextBox> EditableTextBlock;` — Editable textbox widget, used for renaming the sequence in template sections

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/Sequencer/SubAssemblyTrackEditor.h` (Private)


#### class `FSubAssemblyTrackEditor`  
`class FSubAssemblyTrackEditor : public FSubTrackEditor`  
_L19-83_
- inherits: `FSubTrackEditor`
- desc: Sequencer Track Editor for SubAssembly Tracks (extends the functionality of normal SubTracks for CineAssemblies)
- L22 _public prototype_ `FSubAssemblyTrackEditor(TSharedRef<ISequencer> InSequencer);`
- L23 _public prototype_ `virtual ~FSubAssemblyTrackEditor() = default;`
- L25 _public prototype_ `static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> OwningSequencer);`
- L28 _public prototype_ `virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;`
- L29 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;`
- L30 _public prototype_ `virtual TSharedPtr<SWidget> BuildOutlinerColumnWidget(const FBuildColumnWidgetParams& Params, const FName& ColumnName) override;`
- L31 _public prototype_ `virtual bool HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid) override;`
- L32 _public prototype_ `virtual FReply OnDrop(const FDragDropEvent& DragDropEvent, const FSequencerDragDropParams& DragDropParams) override;`
- L33 _public prototype_ `virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;`
- L34 _public prototype_ `virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;`
- L38 _public prototype_ `virtual TSubclassOf<UMovieSceneSubTrack> GetSubTrackClass() const override;`
- L43 _private prototype_ `UMovieSceneSubAssemblyTrack* AddSubAssemblyTrack(ESubAssemblyTrackType TrackType);` — Adds a new SubAssembly Track to the focused movie scene, and sets it Track Type appropriately
- L46 _private prototype_ `TSharedRef<SWidget> BuildAddSubSequenceComboButtonContent(UE::Sequencer::TWeakViewModelPtr<UE::Sequencer::FViewModel> WeakViewModel);` — Build the menu to display when clicking the "+" button on a SubAssembly Track
- L49 _private prototype_ `TSharedRef<SWidget> BuildAssetPicker(UMovieSceneSubAssemblyTrack* Track, TArray<FTopLevelAssetPath> ClassPaths, bool bUseAssetAsTemplate);` — Build an Asset Picker widget that will only display assets matching one of the input class paths
- L52 _private prototype_ `void AddNewSequenceSubMenu(FMenuBuilder& MenuBuilder, UMovieSceneSubAssemblyTrack* Track);` — Adds the "New Sequence" submenu to the SubAssembly track menu
- L55 _private prototype_ `void AddReferenceSubMenu(FMenuBuilder& MenuBuilder, UMovieSceneSubAssemblyTrack* Track);` — Adds the "Reference" Sequence submenu to the SubAssembly track menu
- L58 _private prototype_ `void OnAssetSelectedAsTemplate(const FAssetData& AssetData, UMovieSceneSubAssemblyTrack* Track);` — Callback when an asset is selected in the asset picker as a template for a new sequence to add to the track
- L61 _private prototype_ `void OnAssetEnterPressedAsTemplate(const TArray<FAssetData>& AssetData, UMovieSceneSubAssemblyTrack* Track);` — Callback when one or more assets are selected in the asset picker as a template for a new sequence to add to the track
- L64 _private prototype_ `void OnAssetSelectedAsReference(const FAssetData& AssetData, UMovieSceneSubAssemblyTrack* Track);` — Callback when an asset is selected in the asset picker as a reference to add to the track
- L67 _private prototype_ `void OnAssetEnterPressedAsReference(const TArray<FAssetData>& AssetData, UMovieSceneSubAssemblyTrack* Track);` — Callback when one or more assets are selected in the asset picker as a reference to add to the track
- L70 _private prototype_ `void AddNewSequenceToTrack(UMovieSceneSubAssemblyTrack* Track, UObject* TemplateObject);` — Creates and adds a new sequence to the input Track, then finds the newly created SubAssemblySection and assigns the input TemplateObject to it
- L73 _private prototype_ `bool AddDroppedAsset(UObject* Asset, UMovieSceneSubAssemblyTrack* Track, FFrameNumber FrameNumber);` — Adds the input Asset onto the input Track (or a new Track if that is null) at the input FrameNumber
- L76 _private prototype_ `void OnDroppedAsTemplate(UObject* Asset, UMovieSceneSubAssemblyTrack* Track, FFrameNumber FrameNumber);` — Callback when an asset is dropped and handled by this track editor to be added as a template for a new sequence
- L79 _private prototype_ `void OnDroppedAsReference(UMovieSceneSequence* Sequence, UMovieSceneSubAssemblyTrack* Track, FFrameNumber FrameNumber);` — Callback when an asset is dropped and handled by this track editor to be added as a reference
- L82 _private prototype_ `ESubAssemblyTrackType GetTrackTypeForAsset(UObject* Asset);` — Return the appropriate track type for the input asset

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/TakeRecorder/CineAssemblyTakeRecorderIntegration.h` (Private)


#### class `FCineAssemblyTakeRecorderIntegration`  
`class FCineAssemblyTakeRecorderIntegration : public FNoncopyable`  
_L13-44_
- inherits: `FNoncopyable`
- desc: Manages Cine Assembly Tools interactions with Take Recorder
- L16 _public prototype_ `FCineAssemblyTakeRecorderIntegration();`
- L17 _public prototype_ `~FCineAssemblyTakeRecorderIntegration();`
- L21 _private prototype_ `void OnRecordingInitialized(UTakeRecorder* TakeRecorder);` — Bind to TakeRecorder's OnTickRecording and OnRecordingStopped, and complete the pending assembly configuration.
- L24 _private prototype_ `void OnTickRecording(UTakeRecorder* TakeRecorder, const FQualifiedFrameTime& CurrentFrameTime);` — Expand full-range SubSections to the current recording frame.
- L27 _private prototype_ `void OnRecordingStopped(UTakeRecorder* TakeRecorder);` — Save the SubAssembly and Associated Assets when recording completes.
- L30 _private prototype_ `void OnAssemblySchemaSettingChanged();` — Apply the AssemblySchema to the pending take.
- L33 _private prototype_ `void OnTakePresetAllocated();` — Bind to the allocated TakePreset's OnLevelSequenceChanged event to apply the schema content to the pending take.
- L36 _private prototype_ `void OnPendingTakeLevelSequenceChanged();` — Apply the configured schema when the pending take's level sequence is recreated.
- L39 _private prototype_ `void OnPendingTakeCleared();` — Null the AssemblySchema setting so that the cleared pending take does not immediately repopulate the take with schema content.
- L43 _private member_ `FDelegateHandle PendingTakeLevelSequenceChangedHandle;` — Subscription handle on the pending take's per-instance OnLevelSequenceChanged event.

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/TakeRecorder/CineAssemblyTakeRecorderSettings.h` (Private)


#### class `UCineAssemblyTakeRecorderSettings`  
`class UCineAssemblyTakeRecorderSettings : public UObject`  
_L13-36_
- reflection: `UCLASS(Config=EditorPerProjectUserSettings, DisplayName = "Take Recorder")`
- inherits: `UObject`
- L19 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L24 _public prototype_ `bool CanEditAssemblySchema() const;` — `UFUNCTION()` — Returns true if the Take Preset settings TargetRecordClass is set to CineAssembly
- L27 _public function_ `FOnAssemblySchemaChanged& OnAssemblySchemaChanged()` — Multicast delegate fired whenever the AssemblySchema property is edited
- L32 _public member_ `TSoftObjectPtr<UCineAssemblySchema> AssemblySchema;` — `UPROPERTY(Config, EditAnywhere, Category = "Cine Assembly", meta=(EditCondition = "CanEditAssemblySchema", EditConditionHides))` — The Cine Assembly Schema to use as the base for the recorded Assembly
- L35 _private member_ `FOnAssemblySchemaChanged OnAssemblySchemaChangedDelegate;`

#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnAssemblySchemaChanged);`
- L10 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnAssemblySchemaChanged);`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/CineAssembly/CineAssemblyMetadataWidgets.h` (Private)


#### struct `FCineAssemblyMetadataWidgets`  
`struct FCineAssemblyMetadataWidgets`  
_L12-22_
- L15 _public prototype_ `static TSharedRef<SWidget> MakeEditMenuForAssembly(UCineAssembly* InAssembly);` — Edit panel for a UCineAssembly to edit its label and metadata
- L18 _public prototype_ `static TSharedRef<SWidget> MakeEditMenuForSection(UMovieSceneSubAssemblySection* InSubAssemblySection);` — Edit panel for a SubAssembly Section to edit its label and metadata overrides
- L21 _public prototype_ `static TSharedRef<SWidget> MakeEditMenuForAssociatedAsset(UCineAssembly* InAssembly, const FGuid& AssetID);` — Edit panel for an Associated Asset descriptor identified by AssetID on the owning assembly

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/CineAssembly/SCineAssemblyAssetTreeView.h` (Private)


#### class `FCineAssemblyTreeDragDrop`  
`class FCineAssemblyTreeDragDrop : public FDragDropOperation`  
_L21-42_
- inherits: `FDragDropOperation`
- desc: Drag and Drop operation to handle dragging tree items in the CineAssembly AssetTreeView
- L25 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FCineAssemblyTreeDragDrop, FDragDropOperation) FCineAssemblyTreeDragDrop() = default;`
- L29 _public prototype_ `static TSharedRef<FCineAssemblyTreeDragDrop> New(const TSharedPtr<ICineAssemblyTreeItem>& InItem);`
- L32 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L33 _public prototype_ `virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;`
- L34 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L38 _public member_ `TSharedPtr<ICineAssemblyTreeItem> TreeItem;` — The tree item being dragged.
- L41 _public member_ `FSimpleDelegate OnDropNotHandled;` — Callback to handle the case where an item is dropped somewhere not on the tree view

#### class `SCineAssemblyAssetTreeView`  
`class SCineAssemblyAssetTreeView : public SCompoundWidget`  
_L47-196_
- inherits: `SCompoundWidget`
- desc: A tree view widget that displays the folder hierarchy and asset layout of a CineAssembly.
- L50 _public prototype_ `SCineAssemblyAssetTreeView() = default;`
- L52 _public function_ `SLATE_BEGIN_ARGS(SCineAssemblyAssetTreeView) : _SelectionMode(ESelectionMode::Type::Single) , _ShouldEvaluateTokens(false) , _IsReadOnly(false) , _DisplayHintText(false)`
- L60 _public prototype_ `SLATE_ARGUMENT(ESelectionMode::Type, SelectionMode) SLATE_ARGUMENT(bool, ShouldEvaluateTokens) SLATE_ARGUMENT(bool, IsReadOnly) SLATE_ARGUMENT(bool, DisplayHintText) SLATE_EVENT(FSimpleDelegate, OnItemRemoved) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UCineAssembly* InAssembly);` — Sets the selection mode for this tree view. Ignored when IsReadOnly is true (selection is forced off).
- L79 _public prototype_ `void AddFolder();` — Adds a new child folder under the currently selected folder (or the root if nothing is selected)
- L82 _public prototype_ `void Reinitialize();` — Rebuilds the content tree from the current assembly state and refreshes the tree view
- L86 _private prototype_ `void InitializeContentTree(UCineAssembly* Assembly, TSharedPtr<FCineAssemblyFolderItem>& ContentRoot, TSharedPtr<FSubAssemblyItem>& TopLevelAssembly);` — Build the content tree for the input Assembly, including its SubAssemblies and default folders
- L89 _private prototype_ `void AddSubAssemblySectionsToTree(UCineAssembly* Assembly, TSharedPtr<FCineAssemblyFolderItem>& ContentRoot);` — Add SubAssemblySection items to the tree from the Assembly's MovieScene
- L92 _private prototype_ `void AddSubAssembliesToTree(UCineAssembly* Assembly, TSharedPtr<FCineAssemblyFolderItem>& ContentRoot);` — Add SubAssembly items to the tree from the Assembly's SubAssembly list
- L95 _private prototype_ `void AddAssociatedAssetsToTree(UCineAssembly* Assembly, TSharedPtr<FCineAssemblyFolderItem>& ContentRoot);` — Add associated asset items to the tree from the Assembly's AssociatedAssets list
- L98 _private prototype_ `TSharedRef<ITableRow> OnGenerateTreeRow(TSharedPtr<ICineAssemblyTreeItem> TreeItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates the row widget for an entry in the tree view
- L101 _private prototype_ `void OnGetChildren(TSharedPtr<ICineAssemblyTreeItem> TreeItem, TArray<TSharedPtr<ICineAssemblyTreeItem>>& OutNodes);` — Gets the children of the input tree view item to build additional tree rows
- L104 _private prototype_ `void OnTreeItemsRebuilt();` — Callback when the content tree view rebuilds itself, used to make the textbox in the most recently added row editable
- L107 _private prototype_ `FText GetTreeItemDisplayName(TSharedPtr<ICineAssemblyTreeItem> TreeItem) const;` — Callback to get the display name of the input tree item
- L110 _private prototype_ `FText GetTreeItemLabelText(TSharedPtr<ICineAssemblyTreeItem> TreeItem) const;` — Callback to get the semantic label of the input tree item
- L113 _private prototype_ `FText GetTreeItemTooltipText(TSharedPtr<ICineAssemblyTreeItem> TreeItem) const;` — Callback to get the tooltip text of the input tree item
- L116 _private prototype_ `void OnTreeItemTextCommitted(const FText& InText, ETextCommit::Type InCommitType, TSharedPtr<ICineAssemblyTreeItem> TreeItem);` — Renames the tree item, and updates the paths of all of its children
- L119 _private prototype_ `bool OnValidateTreeItemName(const FText& InText, FText& OutErrorMessage, TSharedPtr<ICineAssemblyTreeItem> TreeItem);` — Validates a tree item's name, checking for empty names, invalid characters, and duplicate folder names
- L122 _private prototype_ `void OnTreeItemTextResolved(const FText& InText, TSharedPtr<ICineAssemblyTreeItem> TreeItem);` — Callback when naming tokens in a tree item's text are evaluated, used to update the assembly's resolved name
- L125 _private prototype_ `void OnTreeViewDoubleClick(TSharedPtr<ICineAssemblyTreeItem> TreeItem);` — Handles double clicks on the tree view to rename the item
- L128 _private prototype_ `FReply OnTreeViewKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — Handles key presses on the tree view
- L131 _private prototype_ `TSharedPtr<SWidget> MakeContentTreeContextMenu();` — Create the context menu when the content tree view is right-clicked
- L134 _private prototype_ `void DeleteTreeItem(TSharedPtr<ICineAssemblyTreeItem> TreeItem);` — Remove the input item and its children from the tree view
- L137 _private prototype_ `void DeleteFolderItem(const TSharedPtr<FCineAssemblyFolderItem>& FolderItem);` — Removes a folder and all of its children from the tree view
- L140 _private prototype_ `void UpdateFolderList();` — Update the list of folders to create from the current set in the tree view
- L143 _private prototype_ `void ExpandTreeRecursive(const TSharedPtr<FCineAssemblyFolderItem>& FolderItem) const;` — Recursively expands every folder in the tree view
- L146 _private prototype_ `TSharedRef<SWidget> MakeTemplateAssetPicker(TSharedPtr<FAssociatedAssetItem> AssetItem);` — Creates the inline template asset picker widget for an Associated Asset row. Returns SNullWidget if AssetItem is null or its AssetClass can't be resolved.
- L149 _private prototype_ `FString GetTemplateAssetObjectPath(TSharedPtr<FAssociatedAssetItem> AssetItem) const;` — Returns the current TemplateAsset path string for the row's descriptor (or empty if the descriptor is missing).
- L152 _private prototype_ `void OnTemplateAssetChanged(const FAssetData& AssetData, TSharedPtr<FAssociatedAssetItem> AssetItem);` — Updates the row's descriptor TemplateAsset to the picker's new selection.
- L155 _private prototype_ `TSharedRef<SWidget> MakeMetadataLinkButton(TSharedPtr<ICineAssemblyTreeItem> TreeItem);` — Creates the metadata link widget for associated asset and SubAssembly section items (returns SNullWidget read-only trees)
- L158 _private prototype_ `FReply OnTreeRowDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Begins a drag and drop event to drag an item out of the content tree view
- L161 _private prototype_ `FReply OnTreeRowAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<ICineAssemblyTreeItem> InItem);` — Callback when an item is dropped onto a folder in the content tree view to add it to the children of that row
- L165 _private member_ `TWeakObjectPtr<UCineAssembly> WeakAssembly;` — The assembly that this tree view was constructed with
- L168 _private member_ `TSharedPtr<STreeView<TSharedPtr<ICineAssemblyTreeItem>>> TreeView;` — The tree view of content folders and assets for the provided CineAssembly (and its SubAssemblies)
- L171 _private member_ `TArray<TSharedPtr<ICineAssemblyTreeItem>> TreeItems;` — Items source for the tree view
- L174 _private member_ `TSharedPtr<FCineAssemblyFolderItem> RootFolder;` — The root folder in the tree view
- L177 _private member_ `TSharedPtr<FSubAssemblyItem> TopLevelAssemblyItem;` — An item representing where the top-level assembly should be created
- L180 _private member_ `TSharedPtr<ICineAssemblyTreeItem> MostRecentlyAddedItem;` — The most recently added tree item, used to allow the user to immediately rename the item after the tree view updates to show it
- L183 _private member_ `FSimpleDelegate OnItemRemoved;` — Delegate broadcast when an item is removed from the tree
- L186 _private member_ `ESelectionMode::Type SelectionMode = ESelectionMode::Single;` — The selection mode for this tree view
- L189 _private member_ `bool bShouldEvaluateTokens = false;` — Whether this tree view should evaluate and display resolved token strings
- L192 _private member_ `bool bIsReadOnly = false;` — When true, all editing interactions are disabled
- L195 _private member_ `bool bDisplayHintText = false;` — When true, displays additional context text next to tree items

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/CineAssembly/SCineAssemblyConfigPanel.h` (Private)


#### class `SCineAssemblyConfigPanel`  
`class SCineAssemblyConfigPanel : public SCompoundWidget`  
_L19-78_
- inherits: `SCompoundWidget`
- desc: A widget that wraps details and config steps for setting up a cine assembly asset
- L22 _public prototype_ `SCineAssemblyConfigPanel() = default;`
- L24 _public function_ `SLATE_BEGIN_ARGS(SCineAssemblyConfigPanel) : _HideSubAssemblies(false)`
- L29 _public prototype_ `SLATE_ARGUMENT(bool, HideSubAssemblies) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UCineAssembly* InAssembly);` — If set to true, the SubAssemblies section in the details view will be hidden
- L36 _public prototype_ `void Refresh();` — Refreshes the details view and hierarchy tree view
- L40 _private prototype_ `TSharedRef<SWidget> MakeDetailsWidget();` — Creates the widget to display for the Overview tab
- L43 _private prototype_ `TSharedRef<SWidget> MakeHierarchyWidget();` — Creates the widget to display for the Hierarchy tab
- L46 _private prototype_ `TSharedRef<SWidget> MakeNotesWidget();` — Creates the widget to display for the Notes tab
- L49 _private prototype_ `bool ValidateAssemblyName(const FText& InText, FText& OutErrorMessage) const;` — Validates the user input text for the assembly name
- L52 _private prototype_ `bool IsCustomRowVisible(FName RowName, FName ParentName);` — Filter used by the Details View to determine which custom rows to show
- L55 _private prototype_ `const FSlateBrush* GetSchemaThumbnail() const;` — Get the thumbnail brush for the selected schema
- L59 _private member_ `UCineAssembly* CineAssemblyToConfigure = nullptr;` — Transient object used only by this UI to configure the properties of the new asset that will get created by the Factory
- L62 _private member_ `TSharedPtr<SWidgetSwitcher> TabSwitcher;` — Switcher that controls which tab widget is currently visible
- L65 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — Details View displaying the reflected properties of the Cine Assembly being configured
- L68 _private member_ `TSharedPtr<SCineAssemblyAssetTreeView> TreeView;` — A TreeView to display the list of other assets and folders that this Assembly will create
- L71 _private member_ `TStrongObjectPtr<UCineAssemblyNamingTokensContext> NamingTokenContext;` — Naming Token Context object, with a pointer to the assembly being configured
- L74 _private member_ `FNamingTokenFilterArgs FilterArgs;` — Naming Token filter properties
- L77 _private member_ `TSharedPtr<SNamingTokensEditableTextBox> AssemblyNameTextBox;` — TextBox displaying the name of the assembly being configured

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/CineAssembly/SCineAssemblyConfigWindow.h` (Private)


#### class `SCineAssemblyConfigWindow`  
`class SCineAssemblyConfigWindow : public SWindow`  
_L15-62_
- inherits: `SWindow`
- desc: A window for configuring the properties of a UCineAssembly asset
- L18 _public prototype_ `SCineAssemblyConfigWindow() = default;`
- L19 _public prototype_ `~SCineAssemblyConfigWindow();`
- L21 _public function_ `SLATE_BEGIN_ARGS(SCineAssemblyConfigWindow)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FString& InCreateAssetPath);`
- L28 _private prototype_ `TSharedRef<SWidget> MakeSchemaPanel();` — Creates the panel that displays the available Cine Assembly Schemas
- L31 _private prototype_ `TSharedRef<SWidget> MakeButtonsPanel();` — Creates the buttons on the bottom of the window
- L34 _private prototype_ `FText GetCreateButtonText() const;` — Returns the text to display on the Create Asset button, based on the selected schema
- L37 _private prototype_ `FReply OnCreateAssetClicked();` — Closes the window and indicates that a new asset should be created by the asset factory
- L40 _private prototype_ `FReply OnCancelClicked();` — Closes the window and indicates that no assets should be created by the asset factory
- L43 _private prototype_ `void OnSchemaSelected(const FAssetData& AssetData);` — Updates the UI and CineAssembly properties based on the selected schema
- L46 _private prototype_ `bool ValidateAssetName(FText& OutErrorMessage) const;` — Validate the asset name is acceptable.
- L47 _private prototype_ `bool ValidateAssetName() const;`
- L51 _private member_ `TStrongObjectPtr<UCineAssembly> CineAssemblyToConfigure = nullptr;` — Transient object used only by this UI to configure the properties of the new asset that will get created by the Factory
- L54 _private member_ `TSharedPtr<SCineAssemblyConfigPanel> ConfigPanel;` — The widget that display all of the configuration properties for the Cine Assembly asset
- L57 _private member_ `FString CreateAssetPath;` — The root path where the configured assembly will be created
- L60 _private member_ `bool bShowEngineContentCached = false;` — Cached content browser settings, used to restore defaults when closing the window
- L61 _private member_ `bool bShowPluginContentCached = false;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/CineAssembly/SCineAssemblyPropertyEditor.h` (Private)


#### class `SCineAssemblyPropertyEditor`  
`class SCineAssemblyPropertyEditor : public SCompoundWidget`  
_L15-62_
- inherits: `SCompoundWidget`
- desc: A panel that displays the editable properties of a Cine Assembly asset
- L18 _public prototype_ `SCineAssemblyPropertyEditor() = default;`
- L19 _public prototype_ `~SCineAssemblyPropertyEditor();`
- L21 _public function_ `SLATE_BEGIN_ARGS(SCineAssemblyPropertyEditor)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UCineAssembly* InAssembly);`
- L32 _public prototype_ `void Construct(const FArguments& InArgs, FGuid InAssemblyGuid);` — Widget construction, initialized with the GUID of the assembly to be edited The widget will search the asset registry to find the assembly asset with the matching GUID, and then update the widget contents accordingly.
- L35 _public prototype_ `FString GetAssemblyName();` — Returns the name of the assembly asset being edited
- L38 _public prototype_ `void FindAssembly(FGuid AssemblyID);` — Searches the asset registry for a Cine Assembly matching the input ID and updates the UI
- L41 _public prototype_ `bool HasRenderedThumbnail();` — Returns true if the Assembly asset has a rendered thumbnail (such as from the Sequencer preview)
- L45 _private prototype_ `TSharedRef<SWidget> BuildUI();` — Constructs the main UI for the widget
- L48 _private prototype_ `TSharedRef<SWidget> MakeOverviewWidget();` — Creates the widget to display for the Overview tab
- L51 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent);` — Filter used by the Details View to determine which properties to show
- L54 _private prototype_ `bool IsCustomRowVisible(FName RowName, FName ParentName);` — Filter used by the Details View to determine which custom rows to show
- L58 _private member_ `UCineAssembly* CineAssembly = nullptr;` — The assembly asset whose properties are displayed by this widget
- L61 _private member_ `TSharedPtr<SWidgetSwitcher> TabSwitcher;` — Switcher that controls which tab widget is currently visible

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/CineAssembly/SCineAssemblySchemaWindow.h` (Private)


#### enum `ESchemaConfigMode`  
`enum class ESchemaConfigMode : uint8`  
_L15-19_
- desc: Mode that configures the UI based on the intended user interactions with the Cine Assembly Schema asset
- L17 _public enumerator_ `CreateNew`
- L18 _public enumerator_ `Edit`

#### class `SCineAssemblySchemaWindow`  
`class SCineAssemblySchemaWindow : public SCompoundWidget`  
_L24-183_
- inherits: `SCompoundWidget`
- desc: A window for configuring the properties of a UCineAssemblySchema
- L27 _public prototype_ `SCineAssemblySchemaWindow() = default;`
- L28 _public prototype_ `~SCineAssemblySchemaWindow();`
- L30 _public function_ `SLATE_BEGIN_ARGS(SCineAssemblySchemaWindow)`
- L31 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FString& InCreateAssetPath);`
- L37 _public prototype_ `void Construct(const FArguments& InArgs, UCineAssemblySchema* InSchema);` — Widget construction, initialized with the schema asset being edited
- L44 _public prototype_ `void Construct(const FArguments& InArgs, FGuid InSchemaGuid);` — Widget construction, initialized with the GUID of the schema to be edited The widget will search the asset registry to find the schema asset with the matching GUID, and then update the widget contents accordingly.
- L47 _public prototype_ `FString GetSchemaName();` — Returns the name of the schema asset being edited
- L50 _public prototype_ `void FindSchema(FGuid SchemaID);` — Searches the asset registry for a Cine Assembly Schema matching the input ID and updates the UI
- L53 _public prototype_ `void OnWindowClosed(const TSharedRef<SWindow>& InWindow);` — Callback to cleanup this widget when the containing window is closed
- L57 _private prototype_ `TSharedRef<SWidget> BuildUI();` — Constructs the main UI for the widget
- L60 _private prototype_ `TSharedRef<SWidget> MakeMenuPanel();` — Creates the panel that displays the tab menu
- L63 _private prototype_ `TSharedRef<SWidget> MakeContentPanel();` — Creates the panel that displays the content for each tab
- L66 _private prototype_ `TSharedRef<SWidget> MakeButtonsPanel();` — Creates the buttons on the bottom of the window
- L69 _private prototype_ `TSharedRef<SWidget> MakeDetailsTabContent();` — Creates the content for the Details tab
- L72 _private prototype_ `TSharedRef<SWidget> MakeMetadataTabContent();` — Creates the content for the Metadata tab
- L75 _private prototype_ `TSharedRef<SWidget> MakeHierarchyTabContent();` — Creates the content for the Hierarchy tab
- L78 _private prototype_ `TSharedRef<SWidget> MakeDetailsWidget(bool bShowMetadata);` — Creates the content for the Details and Data tabs (metadata properties are only shown in the Data tab)
- L81 _private prototype_ `void InitializeSequencer();` — Creates the Sequencer for editing the TemplateSequence
- L84 _private prototype_ `bool DoesSchemaExistWithName(const FString& SchemaName) const;` — Returns true if a schema already exists with the input name
- L87 _private prototype_ `bool ValidateSchemaName(const FText& InText, FText& OutErrorMessage) const;` — Validates the user input text for the schema name
- L90 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent& PropertyAndParent, bool bShowMetadata);` — Filter used by the Details Views to determine which schema properties to display
- L93 _private prototype_ `FReply OnCreateAssetClicked();` — Closes the window and indicates that a new asset should be created by the asset factory
- L96 _private prototype_ `FReply OnCancelClicked();` — Closes the window and indicates that no assets should be created by the asset factory
- L99 _private prototype_ `void OnAssetsPreDelete(const TArray<UObject*>& AssetsToDelete);` — Callback used to tear-down the Sequencer and other object references in this window before the Schema asset it is editing is deleted
- L102 _private prototype_ `TSharedRef<SWidget> OnGetAddAssetMenuContent();` — Returns the menu content for the Add Asset button
- L105 _private prototype_ `void AddAssetMenuRow(FMenuBuilder& MenuBuilder, const UClass* AssetClass, FExecuteAction OnClickAction = FExecuteAction());` — Adds a menu entry to the Add Asset menu for the input asset class
- L108 _private prototype_ `TSharedRef<SWidget> MakeAssetMenuRowWidget(const UClass* AssetClass);` — Builds the icon-and-label row widget used by Add Asset entries (and shared with the Level sub-menu's top-level entry)
- L111 _private prototype_ `void PopulateAddLevelSubMenu(FMenuBuilder& MenuBuilder);` — Populates the Add Asset > Level sub-menu: quick-pick template entries (Basic, Open World) above a UWorld asset picker
- L114 _private prototype_ `TSharedRef<SWidget> BuildLevelTemplateAssetPicker();` — Builds the embedded UWorld asset picker shown inside the Add Asset > Level sub-menu
- L117 _private prototype_ `void AddAssociatedAsset(const UClass* AssetClass, TSoftObjectPtr<UObject> InTemplateAsset = nullptr);` — Adds a new associated asset definition to the template sequence, with an optional template asset
- L120 _private prototype_ `FReply OnAddFolderClicked();` — Adds a new folder item to the content tree view
- L123 _private prototype_ `void OnSchemaPropertiesChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — Callback when one of the properties of the schema being configured changes
- L126 _private prototype_ `void OnActorAddedToSequencer(AActor* InActor, const FGuid InBinding);` — Callback when an actor is added to the template sequence, used to remove the actor(s) from the binding
- L129 _private prototype_ `void OnMovieSceneDataChanged(EMovieSceneDataChangeType InChangeType);` — Callback whenever MovieScene data in the template sequence is changed
- L132 _private prototype_ `void ValidateSubAssemblyLinks();` — Validates all CineAssembly metadata links
- L135 _private prototype_ `void AddSequencerToolbarExtension(FToolBarBuilder& Builder);` — Extends the sequencer widget's toolbar
- L138 _private prototype_ `void OnImportSequenceClicked();` — Opens an asset picker to import a LevelSequence or CineAssembly to initialize the TemplateSequence
- L141 _private prototype_ `void ImportSequence(ULevelSequence* SourceSequence);` — Initializes the TemplateSequence with the input Sequence
- L144 _private prototype_ `void ValidateTemplateSequence();` — Validates the schema's TemplateSequence and fixes / removes incorrect bindings and tracks
- L147 _private prototype_ `void ExtendSequencerToolbarBaseCommands(FToolBarBuilder& Builder);` — Extends the Sequencer Toolbar with custom entries for this specific Sequencer
- L150 _private prototype_ `EVisibility GetDisplayRateWarningVisibility() const;` — Returns the visibility of the display rate warning toolbar widget
- L153 _private prototype_ `void MuteTracks();` — Mutes all tracks in the template sequence that we do not want to evaluate locally in this Sequencer widget
- L156 _private member_ `bool bShowEngineContentCached = false;` — Cached content browser settings, used to restore defaults when closing the window
- L157 _private member_ `bool bShowPluginContentCached = false;`
- L161 _private member_ `TSharedPtr<SWidgetSwitcher> MenuTabSwitcher;` — Switcher that controls which menu tab is currently visible
- L164 _private member_ `TStrongObjectPtr<UCineAssemblySchema> NewSchemaObject;` — Strong reference to a new, transient Schema object, held so that it cannot be GC'd while the user is still configuring it. Not used when editing existing schemas.
- L167 _private member_ `UCineAssemblySchema* SchemaToConfigure = nullptr;` — Schema object being configured by this window.
- L170 _private member_ `ESchemaConfigMode Mode = ESchemaConfigMode::CreateNew;` — Mode that configures the UI based on the intended user interactions with the Cine Assembly schema asset
- L173 _private member_ `FString CreateAssetPath;` — The root path where the configured schema will be created
- L176 _private member_ `TSharedPtr<ISequencer> Sequencer;` — The sequencer used to display / edit the template sequence
- L179 _private member_ `TSharedPtr<SCineAssemblyAssetTreeView> TreeView;` — A TreeView to display the list of other assets and folders that Assembly's made from this Schema will create
- L182 _private member_ `FDelegateHandle OnAssetsPreDeleteHandle;` — Handle for OnAssetsPreDelete

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/CineAssembly/SDuplicateAssemblyWindow.h` (Private)


#### enum `ECineAssemblyDuplicationMode`  
`enum class ECineAssemblyDuplicationMode : uint8`  
_L17-22_
- desc: List of available duplication modes for a subsequence
- L19 _public enumerator_ `DuplicateOriginal` — Duplicates the original assembly's subsequence track/section AND duplicates the original subsequence, updating the reference
- L20 _public enumerator_ `MaintainReference` — Duplicates the original assembly's subsequence track/section BUT maintains the reference to the original subsequence
- L21 _public enumerator_ `Remove` — Does not duplicate the original assembly's subsequence track/section

#### struct `FSubsequenceDuplicationData`  
`struct FSubsequenceDuplicationData`  
_L25-35_
- desc: The data required to duplicate a specific subsequence
- L28 _public member_ `ECineAssemblyDuplicationMode DuplicationMode = ECineAssemblyDuplicationMode::DuplicateOriginal;` — The duplication mode to use
- L31 _public member_ `FString RelativePath;` — The folder path relative to the parent sequence
- L34 _public member_ `FString DuplicateName;` — The name to use for the duplicated subsequence (if the mode is DuplicateOriginal)

#### struct `FSequenceTreeItem`  
`struct FSequenceTreeItem`  
_L38-70_
- desc: An item in the subsequence tree view, associating a subsequence with its duplication data and child subsequences
- L45 _public member_ `TWeakObjectPtr<UCineAssembly> OwningAssembly;` — The assembly that owns this tree item. This could be null if this item is not managed by a CineAssembly For SubAssembly items, this is the assembly that manages this item in its SubAssemblies list. For Associated Asset items, this is the assembly that manages this item in its AssociatedAssets list.
- L48 _public member_ `UMovieSceneSubSection* SubSection = nullptr;` — The SubSection in the MovieScene of the Duplicate Assembly (or one of its SubAssemblies)
- L51 _public member_ `TWeakObjectPtr<UMovieSceneSequence> OriginalSequence;` — The original sequence referenced by this SubSection before any duplication occured
- L54 _public member_ `FSubsequenceDuplicationData DuplicationData;` — The duplication data associated with this subsequence
- L57 _public member_ `FGuid AssociatedAssetID;` — The ID of the associated asset in the owning assembly's AssociatedAssets array. Invalid for SubSequence item types.
- L60 _public member_ `TArray<TSharedPtr<FSequenceTreeItem>> Children;` — Child subsequence tree items
- L63 _public member_ `TWeakPtr<FSequenceTreeItem> Parent;` — Parent sequence tree item
- L66 _public member_ `bool bIsManagedSubAssembly = false;` — Indicates whether this tree item represents a SubAssembly in the managed SubAssemblies list of an Assembly being duplicated
- L69 _public prototype_ `UCineAssembly* GetDuplicateSubAssembly() const;` — If this tree item is a managed SubAssembly, returns the duplicate SubAssembly in the SubSection. Otherwise, returns nullptr

#### class `SSubsequenceDuplicationRow`  
`class SSubsequenceDuplicationRow : public SMultiColumnTableRow<TSharedPtr<FSequenceTreeItem>>`  
_L73-127_
- inherits: `SMultiColumnTableRow<TSharedPtr<FSequenceTreeItem>>`
- desc: Widget row for an item in the subsequence tree view
- L77 _public function_ `SLATE_BEGIN_ARGS(SSubsequenceDuplicationRow)`
- L78 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedPtr<FSequenceTreeItem>& InTreeItem, UCineAssembly* DuplicateAssembly);`
- L83 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Creates the widget for this row for the specified column
- L87 _private prototype_ `TSharedRef<SWidget> MakeOriginalNameWidget();` — Make the widget for each column
- L88 _private prototype_ `TSharedRef<SWidget> MakeDuplicationModeWidget();`
- L89 _private prototype_ `TSharedRef<SWidget> MakeDuplicateNameWidget();`
- L92 _private prototype_ `const FSlateBrush* GetOriginalNameIcon() const;` — Returns the icon brush for the original name column
- L95 _private prototype_ `FText GetOriginalDisplayName() const;` — Returns the display name for the original name column
- L98 _private prototype_ `FText GetDuplicateDisplayName() const;` — Returns the display name for the duplicate name column (varies by duplication mode)
- L101 _private prototype_ `void SetDuplicationModeRecursive(TSharedPtr<FSequenceTreeItem> InItem, ECineAssemblyDuplicationMode Mode);` — Updates the duplication mode for the input tree item, and potentially its children
- L104 _private prototype_ `void OnSubsequenceNameCommitted(const FText& InText, ETextCommit::Type InCommitType);` — Updates the subsequence template name associated with this tree row
- L107 _private prototype_ `void OnSubsequenceTokenTextEvaluated(const FText& InText);` — Updates the subsequence resolved name after the token text was evaluated
- L110 _private prototype_ `bool ValidateSubsequenceName(const FText& InText, FText& OutErrorMessage) const;` — Validates the user input text for the subsequence name
- L113 _private prototype_ `FText GetDuplicationModeDisplayName(ECineAssemblyDuplicationMode DuplicationMode) const;` — Get the display name of the input duplication mode
- L117 _private member_ `TSharedPtr<FSequenceTreeItem> TreeItem;` — The tree view item displayed by this row widget
- L120 _private member_ `TStrongObjectPtr<UCineAssemblyNamingTokensContext> NamingTokenContext;` — Naming Token Context object, with a pointer to the duplicate assembly
- L123 _private member_ `FNamingTokenFilterArgs FilterArgs;` — Naming Token filter properties
- L126 _private member_ `UClass* ItemClass = nullptr;` — Cached item class

#### class `SDuplicateAssemblyWindow`  
`class SDuplicateAssemblyWindow : public SWindow`  
_L130-227_
- inherits: `SWindow`
- desc: A window to configure how a Cine Assembly asset should be duplicated
- L133 _public prototype_ `SDuplicateAssemblyWindow() = default;`
- L135 _public function_ `SLATE_BEGIN_ARGS(SDuplicateAssemblyWindow)`
- L136 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UCineAssembly* InAssembly);`
- L141 _public member_ `static const FName OriginalNameColumn;`
- L142 _public member_ `static const FName DuplicationModeColumn;`
- L143 _public member_ `static const FName DuplicateNameColumn;`
- L147 _private prototype_ `TSharedRef<SWidget> MakeSubsequencesPanel();` — Creates the subsequences panel
- L150 _private prototype_ `TSharedRef<SWidget> MakeButtonsPanel();` — Creates the buttons on the bottom of the window
- L153 _private prototype_ `FReply OnDuplicateClicked();` — Called when the Duplicate button is pressed, which will execute the duplication steps as defined by the duplication data for each subsequence
- L156 _private prototype_ `FReply OnCancelClicked();` — Called when the Cancel button is pressed, which will close the window without duplicating anything
- L159 _private prototype_ `TSharedRef<ITableRow> OnGenerateTreeRow(TSharedPtr<FSequenceTreeItem> InTreeItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates the row widget in the subsequence tree view for the input tree item
- L162 _private prototype_ `void OnGetChildren(TSharedPtr<FSequenceTreeItem> InTreeItem, TArray<TSharedPtr<FSequenceTreeItem>>& OutNodes);` — Adds the children of the input tree item to the OutNodes array
- L168 _private prototype_ `void PopulateSubsequenceTreeRecursive(UMovieSceneSequence* InSequence, TSharedPtr<FSequenceTreeItem> InTreeItem, const FString& SourceBasePath);` — Builds the list of tree items in the subsequence tree by recursively walking the input sequence and finding all subsequences that may need to be duplicated. SourceBasePath is the asset folder used to compute non-SubAssembly relative paths.
- L171 _private prototype_ `void DuplicateSubsequencesRecursive(UMovieSceneSequence* InSequence);` — Recursively duplicates any of the subsequences of the input sequence that are set to the DuplicateOriginal duplication mode
- L174 _private prototype_ `void RestoreOriginalSubAssembliesRecursive(const TSharedPtr<FSequenceTreeItem>& InItem);` — Recursively restores the original subsequences of the input item that are not set to DuplicateOriginal duplication mode
- L177 _private prototype_ `void RemoveSubsequencesRecursive(UMovieSceneSequence* InSequence);` — Recursively removes any of the subsequences of the input sequence that are set to the Remove duplication mode
- L180 _private prototype_ `void RemoveTracksFromFoldersRecursive(TArrayView<UMovieSceneFolder* const> Folders, const TArray<UMovieSceneTrack*>& TracksToRemove);` — Recursively removes the set of tracks from the input folders (or child folders)
- L183 _private prototype_ `void ProcessAssociatedAssets(const TSharedPtr<FSequenceTreeItem>& InItem);` — Recursively handles duplication, maintaining, or clearing of the associated assets based on the duplication mode
- L186 _private prototype_ `void BuildDuplicationMapRecursive(const TSharedPtr<FSequenceTreeItem> InTreeItem);` — Converts the subsequence tree into a map of subsequences to their associated duplication data
- L189 _private prototype_ `void ExpandTreeItem(TSharedPtr<FSequenceTreeItem> InTreeItem) const;` — Expands the input item in the subsequence tree view
- L192 _private prototype_ `void SaveDuplicationPreferences() const;` — Save the duplication mode settings for each subassembly to a config file to re-use the next time an assembly with the same schema is duplicated
- L195 _private prototype_ `void SaveDuplicationPreferencesRecursive(const TSharedPtr<FSequenceTreeItem>& InItem, const FString& SectionName) const;` — Recursively saves the duplication mode preference for the input tree item and its children
- L198 _private prototype_ `ECineAssemblyDuplicationMode GetDuplicationPreference(const FString& SubAssemblyName) const;` — Reads the saved config and returns the most recent duplication mode for the input subassembly
- L202 _private member_ `UCineAssembly* OriginalAssembly;` — The original assembly being duplicated
- L205 _private member_ `TStrongObjectPtr<UCineAssembly> DuplicateAssembly;` — The duplicated assembly that is being configured
- L208 _private member_ `TArray<TSharedPtr<FSequenceTreeItem>> TreeItems;` — List of subsequence tree items for the tree view
- L211 _private member_ `TSharedPtr<STreeView<TSharedPtr<FSequenceTreeItem>>> TreeView;` — Tree view of subsequences, allowing the user to configure the duplication data
- L214 _private member_ `TMap<UMovieSceneSequence*, FSubsequenceDuplicationData> SubsequenceDuplicationData;` — Subset of the duplication data derived from the tree view for non-managed subsequences
- L217 _private member_ `FString DuplicationPath;` — The path where the duplicate assembly asset should be created
- L220 _private member_ `FString OriginalAssemblyPath;` — The path of the original assembly asset
- L223 _private member_ `FString OriginalAssemblyRootFolder;` — The root folder of the original assembly (i.e. the asset path with the default assembly path from the schema removed)
- L226 _private member_ `static const FString DuplicationPreferenceSection;` — Config section name for duplication preferences

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SActiveProductionCombo.h` (Private)


#### class `SActiveProductionCombo`  
`class SActiveProductionCombo : public SCompoundWidget`  
_L12-19_
- inherits: `SCompoundWidget`
- desc: Combo button widget for choosing an available production to be the Active production
- L15 _public function_ `SLATE_BEGIN_ARGS(SActiveProductionCombo)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SActiveProductionExtendedDataDetailsView.h` (Private)


#### class `SActiveProductionExtendedDataDetailsView`  
`class SActiveProductionExtendedDataDetailsView : public SCompoundWidget`  
_L22-87_
- inherits: `SCompoundWidget`
- desc: Widget that shows Extended Data in a details view for the active production. This widget displays a view of the Extended Data in the context of the UProductionSettings objects. This means all change events propogate back to the UProductionSettings object.
- L26 _public prototype_ `SActiveProductionExtendedDataDetailsView() = default;` — Default constructor.
- L29 _public prototype_ `~SActiveProductionExtendedDataDetailsView();` — Destructor unhooks from UProductionSettings events.
- L31 _public function_ `SLATE_BEGIN_ARGS(SActiveProductionExtendedDataDetailsView) : _TargetScriptStruct(nullptr), _InnerWidget(nullptr), _bShowProductionSelection(true)`
- L38 _public prototype_ `SLATE_ARGUMENT(const UScriptStruct*, TargetScriptStruct) SLATE_ARGUMENT(TSharedPtr<SWidget>, InnerWidget) SLATE_ARGUMENT(bool, bShowProductionSelection) SLATE_END_ARGS()` — The target script structure of Extended Data to show.
- L53 _private prototype_ `void HandleActiveProductionChanged();` — Handles when the active production changes in UProductionSettings.
- L56 _private prototype_ `void HandleProductionListChanged();` — Handles when the production list changes in UProductionSettings.
- L59 _private prototype_ `void UpdateActiveData();` — Updates the active and displayed data.
- L62 _private prototype_ `TSharedRef<SWidget> MakeContents(TSharedPtr<SWidget> InnerWidget);` — Make the contents of the widget taking a custom inner widget and parameters into account.
- L65 _private prototype_ `TSharedRef<SWidget> MakeDetailsWidget();` — Makes the details widget and sets up customizations for the view.
- L68 _private member_ `TSharedPtr<IDetailsView> DetailsView;` — The details view in use.
- L71 _private member_ `TSharedPtr<SWidgetSwitcher> DetailsWidgetSwitcher;` — Switcher widget used to display a message when no active production is selected.
- L74 _private member_ `TWeakPtr<UE::ActiveProductionData::Private::FProductionSettingsSingleExtendedDataDetails> WeakDetailsCustomization;` — Forward declared customization object used to customize this instance of the details view.
- L77 _private member_ `const UScriptStruct* TargetScriptStruct = nullptr;` — The Extended Data script structure to display.
- L80 _private member_ `bool bShowProductionSelection = true;` — Whether the Productions selection combo box should be shown.
- L83 _private member_ `FDelegateHandle ActiveProductionChangedHandle;` — Delegate bound to the Production Setting's OnActiveProductionChanged event
- L86 _private member_ `FDelegateHandle ProductionListChangedHandle;` — Delegate bound to the Production Setting's OnProductionListChanged event

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ActiveProductionData` (scope `UE`)
- L11 _namespace_ `namespace Private` (scope `UE::ActiveProductionData`)

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SAssemblyMetadataLink.h` (Private)


#### class `SAssemblyMetadataLink`  
`class SAssemblyMetadataLink : public SCompoundWidget`  
_L26-142_
- inherits: `SCompoundWidget`
- desc: A composite widget that handles the linking between a CineAssembly's associated assets and metadata fields. Operates in one of two modes: Asset Mode:    Handles the logic to link an associated asset to one or more metadata fields Metadata Mode: Handles the logic to link a metadata field to an associated asset In Metadata Mode, this widget wraps a value widget to display when the field is not linked, and handles switching to a read-only textbox displaying the name of the linked asset when it is linked.
- L29 _public function_ `SLATE_BEGIN_ARGS(SAssemblyMetadataLink) : _EvaluateTokens(false)`
- L34 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, UnlinkedValueWidget) SLATE_ARGUMENT(bool, EvaluateTokens) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UCineAssembly* InAssembly, FGuid InAssetID);` — Optional value widget to show when unlinked. Only applicable to Metadata Mode
- L48 _public prototype_ `void Construct(const FArguments& InArgs, UCineAssembly* InAssembly, const TAttribute<FString>& InMetadataKey);` — Metadata Mode. InMetadataKey is a TAttribute to prevent the widget from caching a FString Key that could be renamed.
- L52 _private prototype_ `void ConstructInternal(const FArguments& InArgs);` — Shared widget construction for Asset and Metadata modes
- L55 _private prototype_ `TSharedRef<SWidget> BuildMenuContent();` — Builds the dropdown menu content showing the link options
- L58 _private prototype_ `void BuildAssetModeMenu(FMenuBuilder& MenuBuilder);` — Builds the asset mode dropdown menu options with metadata fields this asset can link to
- L61 _private prototype_ `void BuildMetadataModeMenu(FMenuBuilder& MenuBuilder);` — Builds the metadata mode dropdown menu options with associated assets and SubAssemblies this field can link to
- L64 _private prototype_ `void AddMenuEntryForAsset(FMenuBuilder& MenuBuilder, FGuid AssetID, const FText& DisplayName);` — Adds a menu entry to the dropdown menu content for the input Asset
- L67 _private prototype_ `void ToggleMetadataLink(FString InMetadataKey, FGuid InAssetID);` — Toggles a link between a metadata key and an asset GUID
- L70 _private prototype_ `bool IsAssetLinked(FString InMetadataKey, FGuid InAssetID) const;` — Whether the input metadata key and associated asset are currently linked
- L76 _private prototype_ `bool HasAnyLink() const;` — AssetMode: Whether the tracked AssociatedAssetID is linked to any metadata field MetadataMode: Whether the tracked MetadataKey is linked to any associated asset
- L83 _private prototype_ `void UnlinkAll();` — Clears every metadata link relevant to this widget's mode in a single transaction. AssetMode: removes every MetadataLinks entry that points at the tracked AssociatedAssetID. MetadataMode: removes the MetadataLinks entry for the tracked MetadataKey.
- L86 _private prototype_ `EVisibility GetLinkButtonVisibility() const;` — Determines the visibility of the link button
- L89 _private prototype_ `FSlateColor GetLinkButtonColor() const;` — Returns the link button icon color based on link status
- L95 _private prototype_ `FText GetLinkedAssetTemplateText() const;` — Returns the linked target's (unresolved) template text. Token evaluation is handled by the SNamingTokensEditableTextBox when EvaluateTokens is true, using NamingTokensContext as its evaluation context.
- L98 _private prototype_ `void UpdateNamingTokensContext();` — Updates NamingTokensContext->Assembly to match the current link target so token evaluation resolves correctly.
- L101 _private prototype_ `const FSlateBrush* GetLinkedAssetIcon() const;` — Returns the class icon for the linked target, or nullptr if the target can't be resolved.
- L104 _private prototype_ `EVisibility GetLinkedAssetIconVisibility() const;` — Collapses the linked asset icon slot when no icon can be resolved.
- L107 _private prototype_ `const UCineAssemblySchema* GetSchema() const;` — Returns the schema that defines the assembly's metadata fields
- L110 _private prototype_ `bool IsAssetClassCompatible(const UClass* InAssetClass, const UClass* InFilterClass) const;` — Whether the AssetClass is compatible with the FilterClass. Always returns true if FilterClass is nullptr.
- L113 _private prototype_ `bool IsSchemaCompatible(FGuid InSubAssemblyID, const FSoftObjectPath& InSchemaType) const;` — Whether the input SubAssembly has a schema that is compatible with the input SchemaType filter. Always return true if SchemaType is not specified.
- L116 _private prototype_ `bool IsMetadataDescCompatible(const FAssemblyMetadataDesc& InMetadataDesc) const;` — Whether the input metadata desc is compatible for linking with this asset
- L119 _private prototype_ `bool IsSubAssemblyCompatible(FGuid InSubAssemblyID, const FAssemblyMetadataDesc& InMetadataDesc) const;` — Whether the input SubAssembly is compatible for linking with the input metadata desc
- L122 _private prototype_ `void ForEachSubAssembly(TFunctionRef<bool(FGuid ID, const FText& DisplayName, const UCineAssemblySchema* Schema)> Visitor) const;` — Iterates all SubAssemblies of the tracked Assembly and calls the visitor for each
- L126 _private member_ `TWeakObjectPtr<UCineAssembly> WeakAssembly;` — The assembly whose associated assets and schema metadata are being linked
- L129 _private member_ `FGuid AssociatedAssetID;` — Asset Mode: the associated asset being linked
- L132 _private member_ `TAttribute<FString> MetadataKey;` — Metadata Mode: the metadata field key. Stored as a TAttribute so renames made while the widget is alive are reflected on the next read.
- L135 _private member_ `bool bIsAssetMode = false;` — Whether this widget is in Asset Mode (true) or Metadata Mode (false)
- L138 _private member_ `bool bEvaluateTokens = false;` — Whether to evaluate naming tokens when displaying the linked asset name
- L141 _private member_ `TStrongObjectPtr<UCineAssemblyNamingTokensContext> NamingTokensContext;` — Context for naming token evaluation

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SAssetNamingPanel.h` (Private)


#### struct `FAssetNamingRowData`  
`struct FAssetNamingRowData`  
_L12-19_
- desc: Data to display in a row in the asset naming list view
- L15 _public member_ `const UClass* Class;` — The asset class being given a new default asset name (chosen using a class picker widget)
- L18 _public member_ `FString DefaultName;` — The new default asset name to register for the asset type

#### class `SAssetNamingRow`  
`class SAssetNamingRow : public SMultiColumnTableRow<TSharedPtr<FAssetNamingRowData>>`  
_L24-68_
- inherits: `SMultiColumnTableRow<TSharedPtr<FAssetNamingRowData>>`
- desc: Row widget for the asset naming list view
- L28 _public function_ `SLATE_BEGIN_ARGS(SAssetNamingRow) : _OnDeleteRow()`
- L33 _public prototype_ `SLATE_EVENT(FOnDeleteRow, OnDeleteRow) SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView, const TSharedPtr<FAssetNamingRowData>& InRowData);` — Called when a row is deleted from the list
- L40 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Creates the widget for this row for the specified column
- L44 _public member_ `TSharedPtr<SNamingTokensEditableTextBox> EditableTextBlock;` — The text box where the user can type the default asset name
- L48 _private prototype_ `void SetAssetClass(const UClass* SelectedClass);` — Set the asset class for this row widget
- L51 _private prototype_ `void SetDefaultAssetName(const FText& InText, ETextCommit::Type InCommitType);` — Set the default name for this row widget
- L54 _private prototype_ `bool ValidateDefaultAssetName(const FText& InText, FText& OutErrorMessage);` — Validate the text entered by the user to ensure it will be a valid asset name
- L57 _private prototype_ `FReply DeleteRow();` — Removes this row's default naming from the active production settings, and removes it from the list view
- L60 _private prototype_ `FReply SummonEditMenu(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Summons a right-click context menu for the current row
- L64 _private member_ `TSharedPtr<FAssetNamingRowData> AssetNaming;` — The underlying asset naming data, used to properly display the class picker and default naming for that class
- L67 _private member_ `FOnDeleteRow OnDeleteRow;` — Delegate to execute when a row is deleted from the list

#### class `SAssetNamingPanel`  
`class SAssetNamingPanel : public SCompoundWidget`  
_L73-103_
- inherits: `SCompoundWidget`
- desc: UI for the Asset Naming panel in the Production Wizard
- L76 _public prototype_ `SAssetNamingPanel() = default;`
- L77 _public prototype_ `~SAssetNamingPanel();`
- L79 _public function_ `SLATE_BEGIN_ARGS(SAssetNamingPanel)`
- L80 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L86 _private prototype_ `TSharedRef<ITableRow> OnGenerateAssetNamingRow(TSharedPtr<FAssetNamingRowData> InAssetNaming, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row displaying asset naming data
- L89 _private prototype_ `void OnListViewDoubleClick(TSharedPtr<FAssetNamingRowData> InAssetNaming);` — Handle double clicks on rows in the list view
- L92 _private prototype_ `void UpdateAssetNamingList();` — Update the list view with the asset naming properties of the current active production
- L96 _private member_ `TArray<TSharedPtr<FAssetNamingRowData>> AssetNamingListItems;` — Source of default asset names for the active production
- L99 _private member_ `TSharedPtr<SListView<TSharedPtr<FAssetNamingRowData>>> AssetNamingListView;` — List view displaying the default asset names for the active production
- L102 _private member_ `FDelegateHandle ActiveProductionChangedHandle;` — Delegate bound to the Production Setting's OnActiveProductionChanged event

#### Free symbols / members of external scopes

- L21 _delegate_ `DECLARE_DELEGATE(FOnDeleteRow);`
- L21 _prototype_ `DECLARE_DELEGATE(FOnDeleteRow);`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SFolderHierarchyPanel.h` (Private)


#### enum `ETemplateFolderStatus`  
`enum class ETemplateFolderStatus : uint8`  
_L13-26_
- desc: States in which a template folder can exist
- L16 _public enumerator_ `None` — The status has not yet been determined
- L19 _public enumerator_ `Exists` — Template folder path exists in the Project Content folder
- L22 _public enumerator_ `MissingCreate` — Template folder path does not exist in the Project Content folder, but should be created OnApply
- L25 _public enumerator_ `MissingDoNotCreate` — Template folder path does not exist in the Project Content folder, but should not be created OnApply

#### struct `FTemplateFolderTreeItem`  
`struct FTemplateFolderTreeItem`  
_L29-51_
- desc: An entry in the template folder tree view with knowledge of its path, children, and parent
- L32 _public member_ `FContentBrowserItemPath Path;` — The path of this template folder
- L35 _public member_ `FString FriendlyName;` — Friendly name that should appear in the tree view. If empty, the path leaf will be displayed
- L38 _public member_ `TSharedPtr<FTemplateFolderTreeItem> Parent;` — The parent of this item in the tree
- L41 _public member_ `TArray<TSharedPtr<FTemplateFolderTreeItem>> Children;` — The children of this item in the tree
- L44 _public member_ `ETemplateFolderStatus Status = ETemplateFolderStatus::None;` — The status of this template folder, indicating whether it needs to be created OnApply
- L47 _public member_ `TSharedPtr<SNamingTokensEditableTextBox> NameWidget;` — The text widget that display this item's name and supports renaming
- L50 _public member_ `bool bIsReadOnly = false;` — If true, this item cannot be renamed or deleted

#### class `FTemplateFolderDragDrop`  
`class FTemplateFolderDragDrop : public FDragDropOperation`  
_L54-80_
- inherits: `FDragDropOperation`
- desc: Drag and Drop operation to handle dragging template folders
- L58 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FTemplateFolderDragDrop, FDragDropOperation) DECLARE_DELEGATE(FOnDropNotHandled);`
- L62 _public prototype_ `FTemplateFolderDragDrop() = default;`
- L64 _public prototype_ `static TSharedRef<FTemplateFolderDragDrop> New(const FString& Name);`
- L67 _public prototype_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override;`
- L68 _public prototype_ `virtual void OnDragged(const class FDragDropEvent& DragDropEvent) override;`
- L69 _public prototype_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override;`
- L73 _public member_ `TSharedPtr<FTemplateFolderTreeItem> SourceTreeItem;` — The source item being dragged. This could be null if the thing being dragged is from the Asset List (not the tree)
- L76 _public member_ `FString ItemName;` — The name of the item being displayed, used by the decorator and to name the new tree item that will get made when dropped
- L79 _public member_ `FOnDropNotHandled OnDropNotHandled;` — Callback to handle the case where an item is dropped somewhere not on the tree view

#### class `SFolderHierarchyPanel`  
`class SFolderHierarchyPanel : public SCompoundWidget`  
_L85-208_
- inherits: `SCompoundWidget`
- desc: UI for the Folder Hierarchy panel in the Production Wizard
- L88 _public function_ `SLATE_BEGIN_ARGS(SFolderHierarchyPanel)`
- L91 _public prototype_ `SFolderHierarchyPanel() = default;`
- L92 _public prototype_ `~SFolderHierarchyPanel();`
- L94 _public prototype_ `void Construct(const FArguments& InArgs);`
- L98 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FTemplateFolderTreeItem> TreeItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates the row widget for an entry in the tree view
- L101 _private prototype_ `void OnGetChildren(TSharedPtr<FTemplateFolderTreeItem> TreeItem, TArray<TSharedPtr<FTemplateFolderTreeItem>>& OutNodes);` — Gets the children of the input tree view item to build additional tree rows
- L104 _private prototype_ `void OnItemsRebuilt();` — Callback when the tree view rebuilds itself, used here to allow the user to immediately rename the item after the tree view updates to show it
- L107 _private prototype_ `void SetExpansionRecursive(TSharedPtr<FTemplateFolderTreeItem> TreeItem, bool bInExpand) const;` — Set the expansion state of the input treem item and all of its children (recursively)
- L110 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();` — Spawns a context menu when the user right-clicks on an entry in the tree view
- L113 _private prototype_ `FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — Handles key presses on the tree view
- L116 _private prototype_ `void OnTreeViewDoubleClick(TSharedPtr<FTemplateFolderTreeItem> TreeItem);` — Handles double clicks on the tree view to rename the item
- L119 _private prototype_ `FReply OnTreeRowDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);` — Begins a drag and drop event to drag an item out of the content tree view
- L122 _private prototype_ `FReply OnTreeRowAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<FTemplateFolderTreeItem> InItem);` — Callback when an item is dropped onto a folder in the content tree view to add it to the children of that row
- L125 _private prototype_ `void BuildTreeFromProductionTemplate();` — Builds the template folder list items (displayed in the tree view) using the current active production's folder template
- L128 _private prototype_ `FReply OnAddFolderToTemplate();` — Adds a new folder to the template under the currently selected tree item
- L131 _private prototype_ `FReply OnCreateTemplateFolders();` — Creates any template folders whose status is MissingCreate in the Content Browser
- L134 _private prototype_ `FReply OnResetTemplateChanges();` — Resets the active production's template to the previously cached state and updates the tree view
- L137 _private prototype_ `bool IsValidFolderName(const FText& InText, FText& OutErrorMessage, TSharedPtr<FTemplateFolderTreeItem> TreeItem);` — Returns true if the input text is a valid folder name, otherwise false and fills the output error message accordingly
- L143 _private prototype_ `void SetTemplateFolderName(const FText& InText, ETextCommit::Type InCommitType, TSharedPtr<FTemplateFolderTreeItem> TreeItem);` — Sets the name of the input template folder. If the folder exists in the Content Browser, and is empty, the user is prompted with the option to also rename the Content Browser folder
- L149 _private prototype_ `void DeleteTemplateFolder(TSharedPtr<FTemplateFolderTreeItem> SelectedTreeItem);` — Deletes the input template folder from the template. If the folder exists in the Content Browser, and is empty, the user is prompted with the option to also delete the Content Browser folder
- L152 _private prototype_ `TSharedPtr<FTemplateFolderTreeItem> FindItemAtPath(const FString& Path);` — Returns the template folder tree item whose path matches the input path
- L153 _private prototype_ `TSharedPtr<FTemplateFolderTreeItem> FindItemAtPathRecursive(TSharedPtr<FTemplateFolderTreeItem> TreeItem, const FString& Path);`
- L156 _private prototype_ `void CreateFolderFromTemplateRecursive(TSharedPtr<FTemplateFolderTreeItem> TreeItem);` — Walks the template folder tree and creates all folders marked as MissingCreate
- L159 _private prototype_ `void RemoveFolderFromTemplateRecursive(TSharedPtr<FTemplateFolderTreeItem> TreeItem);` — Removes the input tree item and all of its children (recursively) from the template
- L162 _private prototype_ `void SetChildrenPathRecursive(TSharedPtr<FTemplateFolderTreeItem> TreeItem, const FString& NewPath);` — Modifies the path of the input tree item and all of its children (recursively) with the input new path
- L165 _private prototype_ `void SetTemplateFolderStatusRecursive(TSharedPtr<FTemplateFolderTreeItem> TreeItem, ETemplateFolderStatus NewStatus);` — Sets the folder status of the input tree item and all of its children (recursively)
- L168 _private prototype_ `FString CreateUniqueFolderName(FContentBrowserItemPath InPath);` — Returns a valid folder name that is unique at the input path in both the Content Browser and the Folder Template
- L171 _private prototype_ `bool IsFolderEmpty(TSharedPtr<FTemplateFolderTreeItem> TreeItem) const;` — Returns true if the input tree item exists in the Content Browser and contains any assets (other than placeholders)
- L174 _private prototype_ `const FSlateBrush* GetFolderIconBadge(TSharedPtr<FTemplateFolderTreeItem> TreeItem) const;` — Returns the badge icon to overlay on top of the folder icon for the input tree item
- L177 _private prototype_ `FText GetFolderStatusText(TSharedPtr<FTemplateFolderTreeItem> TreeItem) const;` — Returns the status text to display next to the input tree item in its row in the tree view
- L180 _private prototype_ `bool DoesPathExist(const FString& Path) const;` — Returns true if the path already exists in the asset registry
- L183 _private prototype_ `FString ResolveTemplatePath(const FString& TemplatePath) const;` — Resolves any naming tokens in the input template path against the active production context. Returns the resolved path string.
- L187 _private member_ `TArray<TSharedPtr<FTemplateFolderTreeItem>> FolderItemsSource;` — The source template folder items for the tree view
- L190 _private member_ `TSharedPtr<STreeView<TSharedPtr<FTemplateFolderTreeItem>>> TreeView;` — The tree view of template folders for the current active production
- L193 _private member_ `TSharedPtr<FTemplateFolderTreeItem> ContentRootItem;` — Convenient alias for the Project Content root item in the tree view
- L196 _private member_ `TSharedPtr<FTemplateFolderTreeItem> PluginRootItem;` — Convenient alias for the Project Plugin root item in the tree view
- L199 _private member_ `TArray<FFolderTemplate> CachedInitialState;` — The cached state of the template, used to reset user changes
- L202 _private member_ `TSharedPtr<FTemplateFolderTreeItem> MostRecentlyAddedItem;` — The mostly recently added tree item, used to allow the user to immediately rename the item after the tree view updates to show it
- L205 _private member_ `bool bIsSettingTemplateFolderName = false;` — Guards against re-entrant SetTemplateFolderName when FMessageDialog::Open's nested message pump dispatches a second OnTextCommitted.
- L207 _private member_ `FDelegateHandle ActiveProductionChangedHandle;`

#### Free symbols / members of external scopes

- L60 _delegate_ `DECLARE_DELEGATE(FOnDropNotHandled);`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SNamingTokensPanel.h` (Private)


#### class `SNamingTokenRow`  
`class SNamingTokenRow : public SMultiColumnTableRow<TSharedPtr<FNamingTokenData>>`  
_L13-27_
- inherits: `SMultiColumnTableRow<TSharedPtr<FNamingTokenData>>`
- desc: Row widget for the global tokens list view
- L16 _public function_ `SLATE_BEGIN_ARGS(SNamingTokenRow)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& Args, const TSharedRef<STableViewBase>& OwnerTableView, TSharedPtr<FNamingTokenData>& InRowData);`
- L22 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;` — Creates the widget for this row for the specified column
- L26 _private member_ `TSharedPtr<FNamingTokenData> TokenData;` — The underlying token data, used to propertly display its token key and display name

#### class `SNamingTokensPanel`  
`class SNamingTokensPanel : public SCompoundWidget`  
_L32-76_
- inherits: `SCompoundWidget`
- desc: UI for the Naming Tokens panel in the Production Wizard
- L35 _public function_ `SLATE_BEGIN_ARGS(SNamingTokensPanel)`
- L36 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L42 _private prototype_ `TSharedRef<ITableRow> OnGenerateNamingTokenRow(TSharedPtr<FNamingTokenData> InTokenData, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row displaying token data
- L45 _private prototype_ `TSharedRef<ITableRow> OnGenerateNamingTokenNamespaceRow(TSharedPtr<FString> InNamespace, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row displaying a namespace, and a checkbox to add/remove it from the active production settings DenyList
- L48 _private prototype_ `void OnNamespaceSelectionChanged(TSharedPtr<FString> SelectedNamespace, ESelectInfo::Type SelectInfo);` — Callback when the selection in the namespace list view changes, which updates the custom token list view to display the tokens in the selected namespace
- L51 _private prototype_ `void OnNamespaceChecked(ECheckBoxState CheckBoxState, TSharedPtr<FString> Namespace);` — Adds / Removes the associated namespace from the active production settings DenyList
- L54 _private prototype_ `ECheckBoxState GetNamespaceCheckBoxState(TSharedPtr<FString> Namespace) const;` — Indicates whether the associated namespace is in the active production settings DenyList
- L57 _private prototype_ `void HandleGlobalTokenListSort(EColumnSortPriority::Type, const FName& ColumnId, EColumnSortMode::Type SortMode);` — Handles sorting of the items in each list view  in this panel
- L58 _private prototype_ `void HandleNamespaceListSort(EColumnSortPriority::Type, const FName& ColumnId, EColumnSortMode::Type SortMode);`
- L59 _private prototype_ `void HandleCustomTokenListSort(EColumnSortPriority::Type, const FName& ColumnId, EColumnSortMode::Type SortMode);`
- L63 _private member_ `TArray<TSharedPtr<FNamingTokenData>> GlobalTokenListItems;` — Sources for the list views in this panel
- L64 _private member_ `TArray<TSharedPtr<FString>> NamingTokenNamespaceListItems;`
- L65 _private member_ `TArray<TSharedPtr<FNamingTokenData>> CustomTokenListItems;`
- L68 _private member_ `TSharedPtr<SListView<TSharedPtr<FNamingTokenData>>> GlobalTokenListView;` — List view widgets in this panel
- L69 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> NamingTokenNamespaceListView;`
- L70 _private member_ `TSharedPtr<SListView<TSharedPtr<FNamingTokenData>>> CustomTokenListView;`
- L73 _private member_ `EColumnSortMode::Type GlobalTokenListSortMode = EColumnSortMode::Ascending;` — Sort mode for each of the sortable lists in this panel
- L74 _private member_ `EColumnSortMode::Type NamespaceListSortMode = EColumnSortMode::Ascending;`
- L75 _private member_ `EColumnSortMode::Type CustomTokenListSortMode = EColumnSortMode::Ascending;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SProductionListPanel.h` (Private)


#### class `SProductionListButton`  
`class SProductionListButton : public SButton`  
_L17-50_
- inherits: `SButton`
- desc: Button used in the Productions panel, containing functionality for a single FCinematicProduction. This button supports right-click (for renaming) and will show an editable text box for the user to rename a button.
- L20 _public prototype_ `SProductionListButton();`
- L22 _public function_ `SLATE_BEGIN_ARGS(SProductionListButton) : _ProductionID()`
- L27 _public prototype_ `SLATE_ATTRIBUTE(FGuid, ProductionID) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — ID of the production that this button controls
- L34 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;` — OnMouseButtonDown is overridden because the base class SButton ignores right-clicks
- L35 _public prototype_ `virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L36 _public prototype_ `virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;`
- L39 _public prototype_ `void EnterEditMode();` — Put the editable text block into edit mode
- L43 _private member_ `TSlateAttribute<FGuid, EInvalidateWidgetReason::Paint> ProductionID;` — ID of the production that this button controls
- L46 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditableTextBlock;` — User-editable text widget for renaming the production
- L49 _private member_ `bool bIsHovered = false;` — Hover state, used to determine color/opacity of the button icon

#### class `SProductionListPanel`  
`class SProductionListPanel : public SCompoundWidget`  
_L55-97_
- inherits: `SCompoundWidget`
- desc: UI for the Productions panel of the Production Wizard
- L58 _public prototype_ `SProductionListPanel() = default;`
- L59 _public prototype_ `~SProductionListPanel();`
- L61 _public function_ `SLATE_BEGIN_ARGS(SProductionListPanel)`
- L62 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L68 _private prototype_ `void UpdateProductionList();` — Creates the list of productions used by the production list view widget
- L71 _private prototype_ `TSharedRef<ITableRow> OnGenerateProductionRow(TSharedPtr<FCinematicProduction> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row in the production list view
- L74 _private prototype_ `void OnProductionListItemsRebuilt();` — Callback when the production list view is finished regenerating its rows
- L77 _private prototype_ `FReply ExportProduction(TSharedPtr<FCinematicProduction> InItem);` — Exports the input production to a .json file on disk containing all of its production settings
- L80 _private prototype_ `FReply ImportProduction();` — Imports a production setting .json file from disk and adds it to the Production Project Settings list of productions
- L84 _private member_ `TArray<TSharedPtr<FCinematicProduction>> ProductionList;` — List items sources for the production list view
- L87 _private member_ `TSharedPtr<SListView<TSharedPtr<FCinematicProduction>>> ProductionListView;` — Production list views, which allows the user to interact with one of the available productions in the Productions menu
- L90 _private member_ `TSharedPtr<SProductionListButton> ProductionListButtonToRename;` — Button belonging to one of the production list view rows that needs to be put into edit mode for the user to rename its production
- L93 _private member_ `FGuid MostRecentProductionID;` — Valid immediately after a new production is added, used to determine which production list item should be put into edit mode
- L96 _private member_ `FDelegateHandle ProductionListChangedHandle;` — Handle to the delegate which responds to changes in UProductionSettings list of productions

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SProductionWizard.h` (Private)


#### struct `FProductionWizardMenuEntry`  
`struct FProductionWizardMenuEntry`  
_L13-23_
- desc: Structure for the list view of menu entires
- L16 _public member_ `FText Label;` — Displayed menu entry text
- L19 _public member_ `FSlateIcon Icon;` — Displayed menu entry icon
- L22 _public member_ `TSharedPtr<SWidget> Panel;` — Widget to attach to the content panel slot when this menu entry is selected

#### class `SProductionWizard`  
`class SProductionWizard : public SCompoundWidget`  
_L28-75_
- inherits: `SCompoundWidget`
- desc: Main UI widget for the Production Wizard Tool
- L31 _public prototype_ `SProductionWizard() = default;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SProductionWizard)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L40 _private prototype_ `TSharedRef<SWidget> MakeMenuPanel();` — Creates the menu on the left side of the production wizard
- L43 _private prototype_ `TSharedRef<SWidget> MakeButtonsPanel();` — Creates the buttons on the bottom of the production wizard
- L46 _private prototype_ `TSharedRef<ITableRow> OnGenerateMenuRow(TSharedPtr<FProductionWizardMenuEntry> MenuEntry, const TSharedRef<STableViewBase>& OwnerTable);` — Generates a row in the menu list views
- L49 _private prototype_ `void OnUserMenuSelectionChanged(TSharedPtr<FProductionWizardMenuEntry> SelectedEntry, ESelectInfo::Type SelectInfo);` — Callback when one of the user menu entries is selected, which will cause its panel to be displayed on the right side of the production wizard
- L52 _private prototype_ `void OnProductionMenuSelectionChanged(TSharedPtr<FProductionWizardMenuEntry> SelectedEntry, ESelectInfo::Type SelectInfo);` — Callback when one of the production menu entries is selected, which will cause its panel to be displayed on the right side of the production wizard
- L55 _private prototype_ `FReply OnBackClicked();` — Cycles backwards through the available panels
- L58 _private prototype_ `FReply OnNextClicked();` — Cycles forwards through the available panels
- L61 _private prototype_ `void MakeMenuExtensions();` — Adds User Settings and Production Settings extensions to the Menu Panel.
- L65 _private member_ `SSplitter::FSlot* MenuPanelSlot = nullptr;` — Slots for the menu and menu entry content panels
- L66 _private member_ `SSplitter::FSlot* ContentPanelSlot = nullptr;`
- L69 _private member_ `TArray<TSharedPtr<FProductionWizardMenuEntry>> UserMenuEntries;` — List items sources for the menu list views
- L70 _private member_ `TArray<TSharedPtr<FProductionWizardMenuEntry>> ProductionMenuEntries;`
- L73 _private member_ `TSharedPtr<SListView<TSharedPtr<FProductionWizardMenuEntry>>> UserMenuListView;` — Menu list views, which allow the user to select a step in the production wizard
- L74 _private member_ `TSharedPtr<SListView<TSharedPtr<FProductionWizardMenuEntry>>> ProductionMenuListView;`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SRevisionControlPanel.h` (Private)


#### class `SRevisionControlPanel`  
`class SRevisionControlPanel : public SCompoundWidget`  
_L12-24_
- inherits: `SCompoundWidget`
- desc: UI for the Revision Control panel in the Production Wizard
- L15 _public function_ `SLATE_BEGIN_ARGS(SRevisionControlPanel)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L23 _private prototype_ `static const FSlateBrush* GetSourceControlIconBadge();` — Returns the icon badge to indicate connection status

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Private/UI/SSequencerSettingsPanel.h` (Private)


#### class `SSequencerSettingsPanel`  
`class SSequencerSettingsPanel : public SCompoundWidget`  
_L12-19_
- inherits: `SCompoundWidget`
- desc: UI for the Sequencer Settings panel in the Production Wizard
- L15 _public function_ `SLATE_BEGIN_ARGS(SSequencerSettingsPanel)`
- L16 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Public/CineAssemblyEditorFunctionLibrary.h` (Public)


#### struct `FCineAssemblyLevelSaveOptions`  
`struct FCineAssemblyLevelSaveOptions`  
_L27-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: When opening a level, these options tell us how to handle unsaved changes in the currently open level
- L33 _public member_ `bool bSaveCurrentLevel = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Cine Assembly Tools")` — Whether the currently open level should be saved before opening a different level
- L37 _public member_ `bool bPromptForUnsavedChanges = true;` — `UPROPERTY(BlueprintReadWrite, Category = "Cine Assembly Tools", meta = (EditCondition = bSaveCurrentLevel))` — Whether the user should be prompted before saving the current level

#### class `UCineAssemblyEditorFunctionLibrary`  
`class UCineAssemblyEditorFunctionLibrary : public UBlueprintFunctionLibrary`  
_L44-344_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of functions that expose CineAssembly functionality to editor scripting
- L51 _public prototype_ `static void OpenAssembly(UCineAssembly* CineAssembly, bool bOpenAssociatedLevel = true, FCineAssemblyLevelSaveOptions SaveOptions = FCineAssemblyLevelSaveOptions());` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AdvancedDisplay = "SaveOptions"))` — Opens a CineAssembly in Sequencer, and optionally opens its associated Level
- L58 _public prototype_ `static bool OpenAssociatedLevel(UCineAssembly* CineAssembly, FCineAssemblyLevelSaveOptions SaveOptions = FCineAssemblyLevelSaveOptions());` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AdvancedDisplay = "SaveOptions"))` — Opens the Level associated with the input CineAssembly (if it has one). Returns false only if the input assembly was invalid, or if its associated level was valid but could not be opened.
- L74 _public prototype_ `static UCineAssembly* CreateAssembly(UCineAssemblySchema* Schema, TSoftObjectPtr<UWorld> Level, TSoftObjectPtr<UCineAssembly> ParentAssembly, const TMap<FString, FString>& Metadata, const FString& Path, const FString& NameOverride = FString());` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AutoCreateRefTerm = "Metadata"))` — Create a new CineAssembly asset using the input Schema, Level, and Metadata. It is important that any metadata required for resolving asset naming tokens is provided to this function so that the Assembly and SubAssemblies are all named correctly. @param Schema             The schema to initialize the new assembly from @param Level              Optional Level to associate with the new assembly @param ParentAssembly     Optional parent assembly reference @param Metadata           Optional metadata overrides to apply to the assembly (key/value string pairs) @param Path               The content browser path where the assembly should be created @param NameOverride       Optional name for the assembly. If empty, the default name defined by the schema is used. @return The newly created assembly, or nullptr if creation failed
- L90 _public prototype_ `static UCineAssembly* CreateAssemblyToConfigure(UCineAssemblySchema* Schema, TSoftObjectPtr<UWorld> Level, TSoftObjectPtr<UCineAssembly> ParentAssembly, const TMap<FString, FString>& Metadata);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AutoCreateRefTerm = "Metadata"))` — Creates an in-memory (transient) CineAssembly object, with defaults configured from the input Schema, ready for further configuration. SubAssembly objects (as specified by the Schema) are also created in-memory and can be obtained by calling GetSubAssemblies(). Once configuration is complete, call FinalizeConfiguredAssembly() to persist the Assembly (and SubAssemblies) as a real asset. Other persist APIs (duplicate/rename/save) on the transient CineAssembly are not supported. @param Schema             The schema to initialize the new assembly from @param Level              Optional Level to associate with the new assembly @param ParentAssembly     Optional parent assembly reference @param Metadata           Optional metadata overrides to apply to the assembly (key/value string pairs) @return The transient assembly, or nullptr if creation failed
- L102 _public prototype_ `static UCineAssembly* FinalizeConfiguredAssembly(UCineAssembly* ConfiguredAssembly, const FString& Path, const FString& NameOverride = FString());` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Persists an in-memory, pre-configured CineAssembly object (typically returned by CreateAssemblyToConfigure()) to the specified path. @param ConfiguredAssembly     The transient CineAssembly object to persist @param Path                   The content browser path where the assembly should be created @param NameOverride           Optional name for the assembly. If empty, the configured name (tokens resolved) is used. @return The persisted CineAssembly asset, or nullptr if the operation failed.
- L118 _public prototype_ `static UCineAssembly* DuplicateAssembly(UCineAssembly* SourceAssembly, const FString& DuplicatePath, const TMap<FString, FString>& Metadata, bool bDuplicateSubsequences = true, bool bDuplicateAssociatedAssets = true, const FString& NameOverride = FString(), EDuplicateExternalAssetPreference ExternalAssetPreference = EDuplicateExternalAssetPreference::DuplicateIntoAssemblyFolder);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AutoCreateRefTerm = "Metadata", AdvancedDisplay = "ExternalAssetPreference"))` — Duplicates a CineAssembly asset at the specified path. @param SourceAssembly                   The assembly to duplicate @param DuplicatePath                    The content browser path where the duplicate should be created @param Metadata                         Optional metadata overrides to apply to the assembly (key/value string pairs) @param bDuplicateSubsequences           If true, recursively duplicate all descendant subsequences. If false, subsequences will reference the same sequences as the source Assembly. @param bDuplicateAssociatedAssets       If true, the schema-defined associated assets are duplicated from the source assembly and its managed SubAssemblies. @param NameOverride                     Optional name for the duplicate. If empty, the source assembly's name is used. @param ExternalAssetPreference          Preference for handling assets (subsequences, sublevels, etc.) that live outside the source assembly's content tree @return The duplicated assembly, or nullptr if duplication failed
- L134 _public prototype_ `static UCineAssembly* DuplicateAssemblyToConfigure(UCineAssembly* SourceAssembly, const TMap<FString, FString>& Metadata, bool bDuplicateSubsequences = true);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AutoCreateRefTerm = "Metadata"))` — Creates an in-memory (transient) duplicate of the source CineAssembly, ready for further configuration. If bDuplicateSubsequences is true, duplicate SubAssembly objects are also created in-memory and can be obtained by calling GetSubAssemblies(). Once configuration is complete, call FinalizeDuplicateAssembly() to persist the duplicate Assembly (and SubAssemblies) as a real asset. Other persist APIs (duplicate/rename/save) on the transient CineAssembly are not supported. @param SourceAssembly            The assembly to duplicate @param Metadata                  Optional metadata overrides to apply to the assembly (key/value string pairs) @param bDuplicateSubsequences    If true, each managed SubAssembly (as specified by the Schema) is also duplicated in-memory. Additional subsequences can be duplicated during FinalizeDuplicateAssembly(). If false, the duplicate assembly will maintain a reference to source assembly's original SubAssemblies. @return The transient duplicate, or nullptr if duplication failed
- L150 _public prototype_ `static UCineAssembly* FinalizeDuplicateAssembly(UCineAssembly* ConfiguredDuplicateAssembly, const FString& DuplicatePath, const FString& NameOverride = FString(), bool bDuplicateSubsequences = true, bool bDuplicateAssociatedAssets = true, EDuplicateExternalAssetPreference ExternalAssetPreference = EDuplicateExternalAssetPreference::DuplicateIntoAssemblyFolder);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AdvancedDisplay = "ExternalAssetPreference"))` — Persists an in-memory, pre-configured CineAssembly duplicate (typically returned by DuplicateAssemblyToConfigure()) to the specified path, and optionally duplicates the source assembly's unmanaged subsequences and associated assets. @param ConfiguredDuplicateAssembly    The transient assembly to persist @param DuplicatePath                  The content browser path where the duplicate should be created @param NameOverride                   Optional name for the assembly. If empty, the configured name (tokens resolved) is used. @param bDuplicateSubsequences         If true, unmanaged subsequences are duplicated using ExternalAssetPreference. @param bDuplicateAssociatedAssets     If true, the schema-defined associated assets are duplicated from the source assembly and its managed SubAssemblies. @param ExternalAssetPreference        Preference for handling assets (subsequences, sublevels, etc.) that live outside the source assembly's content tree @return The now-persisted assembly, or nullptr if the input was not a transient assembly or the path was invalid
- L168 _public prototype_ `static UCineAssemblySchema* CreateSchema( const FString& SchemaName, const FString& AssetPath, const FString& DefaultAssemblyName = FString(), const FString& RelativeAssemblyPath = FString(), const FString& Description = FString(), UCineAssemblySchema* ParentSchema = nullptr, UTexture2D* ThumbnailImage = nullptr, bool bIsDataOnly = false, bool bIsHidden = false );` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AdvancedDisplay = "Description, ParentSchema, ThumbnailImage, bIsDataOnly, bIsHidden"))` — Creates a new CineAssemblySchema asset at the specified path. @param SchemaName              The name of the schema, used as the "assembly type" for assemblies made from it @param AssetPath               The content browser path where the schema should be created @param DefaultAssemblyName     The default name pattern for assemblies created from this schema @param RelativeAssemblyPath    The default path (relative to the content root) where assemblies created from this schema should be placed @param Description             A user-facing text description of the schema @param ParentSchema            Restricts assemblies made from this schema to only allow setting the Parent Assembly to an Assembly with this Parent Schema @param ThumbnailImage          The thumbnail image to use for this schema and assemblies built from it @param bIsDataOnly             Mark this schema as data-only @param bIsHidden               Hide this schema from the UI when creating new assemblies @return The new schema, or nullptr if creation failed
- L194 _public prototype_ `static UMovieSceneSubAssemblySection* AddSubAssemblyTemplate( UCineAssemblySchema* Schema, ESubAssemblyTrackType TrackType = ESubAssemblyTrackType::SubsequenceTrack, const FString& SubAssemblyName = FString(), FName Label = NAME_None, const FString& RelativePath = FString(), UPARAM(meta = (AllowedClasses = "/Script/LevelSequence.LevelSequence, /Script/CineAssemblyTools.CineAssembly, /Script/CineAssemblyTools.CineAssemblySchema")) UObject* TemplateObject = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Adds a new template SubAssembly track and section to a Schema's template sequence. When an Assembly is created from this Schema, a new sequence will be initialized from the provided template object. @param Schema             The schema whose template sequence will be modified @param TrackType          Whether this SubAssembly represents a Shot track or Subsequence track @param SubAssemblyName    The name for the new SubAssembly sequence @param Label              The semantic label for the new section. If None (default), a unique default label is auto-assigned. @param RelativePath       The path (relative to the assembly root) where the new SubAssembly should be created @param TemplateObject     The template object (UCineAssemblySchema, UCineAssembly, or ULevelSequence) to use when initializing the SubAssembly @return The new SubAssemblySection, or null if creation failed
- L214 _public prototype_ `static UMovieSceneSubAssemblySection* AddSubAssemblyReference( UCineAssemblySchema* Schema, ESubAssemblyTrackType TrackType = ESubAssemblyTrackType::SubsequenceTrack, UMovieSceneSequence* Sequence = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Adds a new reference SubAssembly track and section to a Schema's template sequence. When an Assembly is created from this Schema, the section will reference the provided sequence directly. @param Schema             The schema whose template sequence will be modified @param TrackType          Whether this SubAssembly represents a Shot track or Subsequence track @param Sequence           The existing sequence (UCineAssembly or ULevelSequence) to reference @return The new SubAssemblySection, or null if creation failed
- L238 _public prototype_ `static FGuid AddAssociatedAsset( UCineAssemblySchema* Schema, TSubclassOf<UObject> AssetClass, const FString& AssetName = FString(), FName Label = NAME_None, const FString& RelativePath = FString(), UObject* TemplateAsset = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (ScriptMethod))` — Adds a new Associated Asset descriptor to a Schema's template sequence. When an Assembly is created from this Schema, the CineAssembly factory will create an asset of the specified class at the specified relative path, and include it in the Assembly's asset tree. EXPERIMENTAL: The CinematicAssemblyTools plugin officially supports UWorld for associated assets through the CineAssemblySchema UI. Associating assets of other class types may work, but some are untested. Note: Only asset classes are supported. Non-asset classes, such as AActor or UActorComponent, will be rejected at runtime. Note: If AssetClass is UCineAssembly, the call is routed to AddSubAssemblyTemplate and the returned AssetID will be invalid. Consider calling AddSubAssemblyTemplate instead. @param Schema          The schema whose template sequence will be modified @param AssetClass      The class of asset to create alongside each assembly. Only asset classes are supported. Non-asset classes, such as AActor or UActorComponent, will be rejected at runtime. @param AssetName       Optional template name for the asset. If empty, the factory's default asset name is used. @param Label           Optional semantic label. If empty, a unique label is auto-assigned from the asset's display name. @param RelativePath    Optional path, relative to the assembly root, where the asset should be created @param TemplateAsset   Optional template asset to duplicate when the factory creates this descriptor's asset. Must match AssetCl
- L248 _public prototype_ `static void RemoveAssociatedAsset(UCineAssemblySchema* Schema, FGuid AssetID);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (ScriptMethod))` — Removes an Associated Asset descriptor from a Schema's template sequence by AssetID.
- L252 _public prototype_ `static FAssemblyAssociatedAssetDesc GetSchemaAssociatedAssetDesc(UCineAssemblySchema* Schema, FGuid AssetID);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Get Associated Asset Desc", meta = (ScriptMethod = "GetAssociatedAssetDesc"))` — Returns a copy of the Associated Asset descriptor with the given AssetID on the Schema's template sequence. To mutate, call one of the appropriate setter functions with the descriptor's AssetID.
- L256 _public prototype_ `static FAssemblyAssociatedAssetDesc GetAssemblyAssociatedAssetDesc(UCineAssembly* Assembly, FGuid AssetID);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Get Associated Asset Desc", meta = (ScriptMethod = "GetAssociatedAssetDesc"))` — Returns a copy of the Associated Asset descriptor with the given AssetID on the Assembly. To mutate, call one of the appropriate setter functions with the descriptor's AssetID.
- L260 _public prototype_ `static TArray<FAssemblyAssociatedAssetDesc> GetSchemaAssociatedAssetDescs(UCineAssemblySchema* Schema);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Get Associated Asset Descs", meta = (ScriptMethod = "GetAssociatedAssetDescs"))` — Returns copies of all Associated Asset descriptors on the Schema's template sequence. To mutate one, call one of the appropriate setter functions with the descriptor's AssetID.
- L264 _public prototype_ `static TArray<FAssemblyAssociatedAssetDesc> GetAssemblyAssociatedAssetDescs(UCineAssembly* Assembly);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Get Associated Asset Descs", meta = (ScriptMethod = "GetAssociatedAssetDescs"))` — Returns copies of all Associated Asset descriptors on the Assembly. To mutate one, call one of the appropriate setter functions with the descriptor's AssetID.
- L268 _public prototype_ `static void SetAssociatedAssetClass(UCineAssemblySchema* Schema, FGuid AssetID, TSubclassOf<UObject> NewAssetClass);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (ScriptMethod))` — Sets the AssetClass of the Associated Asset descriptor matching the AssetID in the Schema's template sequence. Schema-only because AssetClass is a structural property shared across all assemblies.
- L272 _public prototype_ `static void SetAssociatedAssetRelativePath(UCineAssemblySchema* Schema, FGuid AssetID, const FString& NewRelativePath);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (ScriptMethod))` — Sets the RelativePath of the Associated Asset descriptor matching the AssetID in the Schema's template sequence. Schema-only because RelativePath is a structural property shared across all assemblies.
- L279 _public prototype_ `static void SetAssociatedAssetTemplate(UCineAssemblySchema* Schema, FGuid AssetID, UObject* NewTemplateAsset);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (ScriptMethod))` — Sets the TemplateAsset of the Associated Asset descriptor matching the AssetID in the Schema's template sequence. Schema-only because TemplateAsset is a structural property shared across all assemblies. Note: Operation will fail if the input TemplateAsset does not match the existing AssetClass filter of the Associated Asset descriptor.
- L283 _public prototype_ `static void SetSchemaAssociatedAssetName(UCineAssemblySchema* Schema, FGuid AssetID, const FString& NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Set Associated Asset Name", meta = (ScriptMethod = "SetAssociatedAssetName"))` — Sets the AssetName of the Associated Asset descriptor matching the AssetID in the Schema's template sequence.
- L287 _public prototype_ `static void SetSchemaAssociatedAssetLabel(UCineAssemblySchema* Schema, FGuid AssetID, FName NewLabel);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Set Associated Asset Label", meta = (ScriptMethod = "SetAssociatedAssetLabel"))` — Sets the Label of the Associated Asset descriptor matching the AssetID in the Schema's template sequence.
- L294 _public prototype_ `static void SetAssemblyAssociatedAssetName(UCineAssembly* Assembly, FGuid AssetID, const FString& NewAssetName);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Set Associated Asset Name", meta = (ScriptMethod = "SetAssociatedAssetName"))` — Sets the AssetName of the Associated Asset descriptor matching the AssetID in the Assembly. Note: Operation will fail if descriptor's asset has already been created.
- L298 _public prototype_ `static void SetAssemblyAssociatedAssetLabel(UCineAssembly* Assembly, FGuid AssetID, FName NewLabel);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Set Associated Asset Label", meta = (ScriptMethod = "SetAssociatedAssetLabel"))` — Sets the Label of the Associated Asset descriptor matching the AssetID in the Assembly.
- L305 _public prototype_ `static void SetAssemblyAssociatedAssetShouldCreate(UCineAssembly* Assembly, FGuid AssetID, bool bShouldCreate);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", DisplayName = "Set Associated Asset Should Create", meta = (ScriptMethod = "SetAssociatedAssetShouldCreate"))` — Sets the bShouldCreate flag of the Associated Asset descriptor matching the AssetID in the Assembly. Note: This operation has no effect if the descriptor's asset has already been created.
- L308 _public prototype_ `static FString GetDefaultAssetNameForClass(const UClass* AssetClass);` — Get the default asset name for a new Associated Asset of the given class
- L311 _public prototype_ `static FName MakeDefaultAssociatedAssetLabel(const UCineAssemblySchema* Schema, const UClass* AssetClass);` — Get the default unique Label for a new Associated Asset of the given class on the given Schema
- L322 _public prototype_ `static FNamingTokenResultData EvaluateTokenString(const FString& TokenString, UCineAssembly* Assembly);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Evaluates a tokenized string using the input Assembly for context. Always considers tokens in the "cat" namespace. @param TokenString    The template string containing tokens to resolve @param Assembly       The assembly context used to evaluate tokens @return The full FNamingTokenResultData results, including the evaluated text and per-token information
- L332 _public prototype_ `static UObject* BuildTokenContext(UCineAssembly* Assembly);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Constructs a CineAssembly Naming Token context object for the input Assembly. @param Assembly    The assembly context used to evaluate tokens @return The new context object which can be passed to the NamingTokensEngineSubsystem's EvaluateTokenString function.
- L343 _public prototype_ `static TArray<FAssetData> FindAssembliesBySchema(const UCineAssemblySchema* Schema);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Returns asset data for every CineAssembly asset created from the input Schema. If the input is null, this function returns all CineAssembly assets that have no schema set. @param Schema    The schema to search for, or null to find assemblies with no schema @return Asset data for every assembly whose schema matches the input

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API CINEASSEMBLYTOOLSEDITOR_API`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Public/CineAssemblyEditorSubsystem.h` (Public)


#### class `UCineAssemblyEditorSubsystem`  
`class UCineAssemblyEditorSubsystem : public UEditorSubsystem`  
_L30-64_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Editor Subsystem for CineAssemblyTools
- L36 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L37 _public prototype_ `virtual void Deinitialize() override;`
- L45 _public member_ `FOnCineAssemblyCreatedDynamic OnAssemblyCreated;` — `UPROPERTY(BlueprintAssignable, Category = "Cine Assembly Tools")` — Broadcast when a CineAssembly asset has been created Note: This event may broadcast multiple times if the CineAssembly creates any SubAssembly assets
- L49 _public member_ `FOnCineAssemblySchemaCreatedDynamic OnSchemaCreated;` — `UPROPERTY(BlueprintAssignable, Category = "Cine Assembly Tools")` — Broadcast when a CineAssemblySchema asset has been created
- L56 _public member_ `FOnCineAssemblyDuplicatedDynamic OnAssemblyDuplicated;` — `UPROPERTY(BlueprintAssignable, Category = "Cine Assembly Tools")` — Broadcast when a CineAssembly asset has been duplicated. Note: OnAssemblyCreated will also be broadcast.
- L60 _public member_ `FOnCineAssemblyMetadataChangedDynamic OnAssemblyMetadataChanged;` — `UPROPERTY(BlueprintAssignable, Category = "Cine Assembly Tools")` — Broadcast when adding or editing a metadata value on a CineAssembly asset
- L63 _private member_ `FDelegateHandle OnAssemblyMetadataChangedHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CINEASSEMBLYTOOLSEDITOR_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCineAssemblyCreatedDynamic, UCineAssembly*, NewAssembly);` — Broadcast when a CineAssembly asset has been created
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCineAssemblyCreatedDynamic, UCineAssembly*, NewAssembly);` — Broadcast when a CineAssembly asset has been created
- L18 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCineAssemblySchemaCreatedDynamic, UCineAssemblySchema*, NewSchema);` — Broadcast when a CineAssemblySchema asset has been created
- L18 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCineAssemblySchemaCreatedDynamic, UCineAssemblySchema*, NewSchema);` — Broadcast when a CineAssemblySchema asset has been created
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCineAssemblyDuplicatedDynamic, UCineAssembly*, Duplicate, UCineAssembly*, Source);` — Broadcast when a CineAssembly asset has been duplicated.
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCineAssemblyDuplicatedDynamic, UCineAssembly*, Duplicate, UCineAssembly*, Source);` — Broadcast when a CineAssembly asset has been duplicated.
- L24 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCineAssemblyMetadataChangedDynamic, UCineAssembly*, Assembly, const FString&, Key);` — Broadcast when adding or editing a metadata value on a CineAssembly asset
- L24 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCineAssemblyMetadataChangedDynamic, UCineAssembly*, Assembly, const FString&, Key);` — Broadcast when adding or editing a metadata value on a CineAssembly asset

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Public/ICineAssemblyToolsEditorModule.h` (Public)


#### class `ICineAssemblyToolsEditorModule`  
`class ICineAssemblyToolsEditorModule : public IModuleInterface`  
_L19-93_
- inherits: `IModuleInterface`
- desc: Interface for CineAssemblyToolsEditor module
- L23 _public function_ `static ICineAssemblyToolsEditorModule& Get()` — Get the implementation instance for the module.
- L29 _public function_ `static bool IsAvailable()` — Gets if this module is loaded.
- L35 _public prototype_ `virtual ~ICineAssemblyToolsEditorModule() = default;` — Virtual destructor.
- L62 _public prototype_ `virtual void RegisterProductionExtension(const UScriptStruct& DataScriptStruct) = 0;` — Register a new production extension struct type. An ExtendedData production extension type is a USTRUCT type that is registered as additional data to each Production object. The struct must be a standard USTRUCT and registered to the productions using: ``` USTRUCT() struct FMyStruct { GENERATED_BODY() UPROPERTY(EditAnywhere, Category=Default) int MyIntMember; } { ICineAssemblyToolsEditorModule& CatEdModule = ICineAssemblyToolsEditorModule::Get(); CatEdModule.RegisterProductionExtension(*FMyStruct::StaticStruct()); } ``` Once registered, each production will have its own instance of the extended data struct type. See FCinematicProduction for more on how to access and modify the data.
- L65 _public prototype_ `virtual void UnregisterProductionExtension(const UScriptStruct& DataScriptStruct) = 0;` — Unregister a Production extension struct type.
- L77 _public prototype_ `virtual void RegisterProductionWizardCustomization(const UScriptStruct& ForDataScriptStruct, FGetWidget MakeCustomWidget, TAttribute<FText> Label, TAttribute<FSlateIcon> Icon, bool bShowProductionSelection, bool bHideInWizard) = 0;` — Register a customization for the Production Wizard for the given extended data struct type. A callback can be provided to construct a custom widget, or leave unbound if the default details view is desired. You can then override the label, icon and if the Production Selection combo box is shown in the wizard for the data tab. If bHideInWizard is given as true, then the tab is hidden from the Production Wizard completely for the given struct type. The extended data struct type should already have been registered as a Production extension using RegisterProductionExtension.
- L81 _public prototype_ `virtual void UnregisterProductionWizardCustomization(const UScriptStruct& ForDataScriptStruct) = 0;` — Unregister the registered customization for the given extended data struct type.
- L88 _public prototype_ `virtual void RegisterProductionWizardUserSettings(const FName Name, FGetWidget MakeCustomWidget, TAttribute<FText> Label, TAttribute<FSlateIcon> Icon) = 0;` — Register a custom User Setting tab to show in the Production wizard by providing a callback to create the SWidget to show, as well as customizations to label and icon to display. If no label is provided, Name will be used as the display label on the Production Wizard interface.
- L92 _public prototype_ `virtual void UnregisterProductionWizardUserSettings(const FName Name) = 0;` — Unregister the custom User Settings tab from the Production Wizard with the given name.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGetWidget);` — Callback for constructing a new SWidget.
- L14 _prototype_ `DECLARE_DELEGATE_RetVal(TSharedRef<SWidget>, FGetWidget);` — Callback for constructing a new SWidget.

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Public/ProductionFunctionLibrary.h` (Public)


#### class `UProductionFunctionLibrary`  
`class UProductionFunctionLibrary : public UBlueprintFunctionLibrary`  
_L19-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of Blueprint/Python accessible functions to interface with the Cinematic Production Settings
- L27 _public prototype_ `static UProductionSettings* GetProductionSettings();` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Returns the Production Settings object
- L31 _public prototype_ `static TArray<FCinematicProduction> GetAllProductions();` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Returns an array of all available Cinematic Productions
- L35 _public prototype_ `static bool GetProduction(FGuid ProductionID, FCinematicProduction& Production);` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools", meta=(ReturnDisplayName="IsValid"))` — Get the Cinematic Production matching the input ProductionID (if it exists)
- L39 _public prototype_ `static bool GetActiveProduction(FCinematicProduction& Production);` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools", meta=(ReturnDisplayName = "IsValid"))` — Get the active Cinematic Production (if it exists)
- L46 _public prototype_ `static void SetActiveProduction(FCinematicProduction Production = FCinematicProduction());` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Sets the input Production as the current Active Production If no input is provided, the Active Production will be set to None
- L50 _public prototype_ `static void SetActiveProductionByID(FGuid ProductionID);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Sets the Production matching the input ProductionID as the current Active Production
- L54 _public prototype_ `static void ClearActiveProduction();` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Sets the active Cinematic Production to None
- L58 _public prototype_ `static bool IsActiveProduction(FGuid ProductionID);` — `UFUNCTION(BlueprintPure, Category = "Cine Assembly Tools")` — Returns true if input ProductionID matches the ID of the current Active Production
- L62 _public prototype_ `static void AddProduction(FCinematicProduction Production);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Add the input Cinematic Production to the Production Settings' list of productions
- L66 _public prototype_ `static void DeleteProduction(FGuid ProductionID);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Removes the Cinematic Production matching the input ProductionID from the Production Settings' list of productions
- L70 _public prototype_ `static void RenameProduction(FGuid ProductionID, FString NewName);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Renames the Cinematic Production matching the input ProductionID
- L74 _public prototype_ `static bool GetProductionExtendedData(FGuid ProductionID, const UScriptStruct* DataStruct, FInstancedStruct& OutData);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Given a ProductionID and an Extended Data Struct type, returns the Extended Data object for that production if found.
- L78 _public prototype_ `static bool SetProductionExtendedData(FGuid ProductionID, const FInstancedStruct& Data);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools")` — Given a ProductionID and an Extended Data Struct, sets the struct data on the production.
- L88 _public prototype_ `static UCineAssembly* CreateAssembly(UCineAssemblySchema* Schema, TSoftObjectPtr<UWorld> Level, TSoftObjectPtr<UCineAssembly> ParentAssembly, const TMap<FString, FString>& Metadata, const FString& Path, const FString& Name, bool bUseDefaultNameFromSchema = true);` — `UFUNCTION(BlueprintCallable, Category = "Cine Assembly Tools", meta = (AutoCreateRefTerm = "Metadata"))` — Note: Prefer the CineAssembly Editor Function Library version of CreateAssembly. The Production Function Library version is kept for backwards compatibility. Create a new CineAssembly asset using the input Schema, Level, and Metadata. If bUseDefaultNameFromSchema is true, the default assembly name from the specified schema will be used as the new asset name. It is important that any metadata required for resolving asset naming tokens is provided to this function so that the Assembly and SubAssemblies are all named correctly.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CINEASSEMBLYTOOLSEDITOR_API`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Public/ProductionSettings.h` (Public)


#### enum `ESubsequencePriority`  
`enum class ESubsequencePriority : uint8`  
_L23-27_
- reflection: `UENUM()`
- desc: Options for determining the hierarchical bias of subsequences
- L25 _public enumerator_ `TopDown`
- L26 _public enumerator_ `BottomUp`

#### struct `FFolderTemplate`  
`struct FFolderTemplate`  
_L33-42_
- reflection: `USTRUCT()`
- desc: Properties of a folder in the production's template folder hierarchy
- L38 _public member_ `FString InternalPath;` — `UPROPERTY(config, EditAnywhere, Category = "Default")`
- L41 _public member_ `bool bCreateIfMissing = true;` — `UPROPERTY(config, EditAnywhere, Category = "Default")`

#### struct `FCinematicProduction`  
`struct FCinematicProduction`  
_L48-193_
- reflection: `USTRUCT(BlueprintType)`
- desc: Collection of production settings to override the project/editor behavior
- L55 _public prototype_ `FCinematicProduction();`
- L59 _public member_ `FGuid ProductionID;` — `UPROPERTY(BlueprintReadOnly, Category = "Default", meta = (IgnoreForMemberInitializationTest))` — Unique ID of the production
- L63 _public member_ `FString ProductionName;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Default")` — Production Name
- L67 _public member_ `FFrameRate DefaultDisplayRate;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Default")` — The default frame rate to set for new Level Sequences
- L71 _public member_ `int32 DefaultStartFrame;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Default")` — The default frame number (using the default frame rate) that new Level Sequences should start at
- L75 _public member_ `ESubsequencePriority SubsequencePriority = ESubsequencePriority::BottomUp;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Default")` — Controls whether subsequences override parent sequences, or vice versa
- L79 _public member_ `TSet<FString> NamingTokenNamespaceDenyList;` — `UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Default")` — List of Naming Token namespaces that should not be evaluated
- L83 _public member_ `TMap<TObjectPtr<const UClass>, FString> DefaultAssetNames;` — `UPROPERTY(config, VisibleAnywhere, BlueprintReadOnly, Category = "Default")` — List of default names for specific asset types
- L87 _public member_ `TArray<FFolderTemplate> TemplateFolders;` — `UPROPERTY(config, EditAnywhere, Category = "Default")` — List of folder paths that represent a template folder hierarchy to be used for this production
- L100 _public prototype_ `FInstancedStruct* LoadExtendedData(const UScriptStruct& ForStruct);` — Attempts to load Extended Data of the given type, and update the data in the production. This function always loads the data from ExtendedDataConfig if found, regardless of it has already been loaded or not. The given Struct type must have been registered with ICineAssemblyToolsEditorModule as a ProductionExtension. Returns a pointer to the loaded struct or nullptr if the type is not registered with ICineAssemblyToolsEditorModule. The returned pointer is only valid until the next allocation of ExtendedData.
- L128 _public prototype_ `FInstancedStruct* FindOrLoadExtendedData(const UScriptStruct& ForStruct);` — Attempts to find Extended Data of the given type, loading it if required and updating the data in the production. If the data is already loaded, then the existing data is returned and not loaded. The given Struct type must have been registered with ICineAssemblyToolsEditorModule as a ProductionExtension. To modify the returned FInstancedStruct and ensure that it is correctly re-exported back into the production after modification so that it is correctly saved into the config, use FScopedModifyProductionExtendedData. e.g. ``` if (FInstancedStruct* Data = Production.FindOrLoadExtendedData(*FMyStruct::StaticStruct())) { FScopedModifyProductionExtendedData ModifyGuard(Production, FMyStruct::StaticStruct()); FMyStruct& MyStructRef = Data->GetMutable(); ... // Modify MyStructRef ... } ``` Returns a pointer to the loaded struct or nullptr if the type is not registered with ICineAssemblyToolsEditorModule. The returned pointer is only valid until the next allocation of ExtendedData.
- L136 _public prototype_ `const FInstancedStruct* FindExtendedData(const UScriptStruct& ForStruct) const;` — Attempts to find existing Extended Data of the given type. If the data does not exist or has not been loaded, returns a nullptr. Use FindOrLoadExtendedData if you are unsure if the data has already been loaded, or ensure LoadExtendedData has already been called for this struct type. The returned pointer is null if the extended data was not found, and if found, is only valid until the next allocation of ExtendedData.
- L142 _public prototype_ `void ExportExtendedData(const UScriptStruct& ForData);` — Export the extended data ready to save to Config by exporting the given struct type into ExtendedDataConfig. The ExtendedDataConfig map is not emptied as part of this process.
- L145 _public function_ `FOnProductionExtendedDataExported& OnExtendedDataExported()` — Delegate called when the one or more ExtendedData structs are exported to ExtendedDataConfig.
- L148 _public prototype_ `static const FName GetExtendedDataMemberName();` — Helper function to get the compile time checked member name of the ExtendedData property.
- L156 _protected member_ `TMap<FSoftObjectPath, FInstancedStruct> ExtendedData;` — `UPROPERTY(Transient, SkipSerialization, EditAnywhere, Category = "Default", NoClear, EditFixedSize, meta = (DisplayThumbnail = "false"))` — Instance specific ExtendedData. This is saved to the config by exporting to text. Ensure modifications are guarded by a FScopedModifyProductionExtendedData instance or a call to ExportExtendedData.
- L163 _private prototype_ `void LoadAllExtendedData();` — Loads all registered ExtendedData from config loaded data and adds any additionally registered extended data types. Exports the data back into the ExtendedDataConfig struct once loading is complete.
- L166 _private prototype_ `TOptional<FInstancedStruct*> ImportExtendedData(const FString& ImportText);` — Import the text as ExtendedData. Returns the the newly created instance if import was successful.
- L169 _private prototype_ `void ExportExtendedData(const FInstancedStruct& InData);` — Export the InstancedStruct into ExtendedDataConfig.
- L172 _private prototype_ `FInstancedStruct& AddUniqueExtendedData(const UScriptStruct& ScriptStruct);` — Uniquely add an instance of the given struct type, returning a reference to either the existing data or the newly created data.
- L175 _private prototype_ `void NotifyExtendedDataExported(const UScriptStruct* ExportedStruct);` — Broadcast the ExtendedDataExported if bBlockNotifyExtendedDataExported is false with the given exported struct type.
- L178 _private member_ `FOnProductionExtendedDataExported ExtendedDataExported;` — Delegate called when the one or more ExtendedData structs are exported to ExtendedDataConfig.
- L181 _private member_ `bool bBlockNotifyExtendedDataExported = false;` — Whether the ExtendedDataExported delegate should be blocked or triggered when the ExtendedData is exported.
- L192 _private member_ `TMap<FSoftObjectPath, FString> ExtendedDataConfig;` — `UPROPERTY(config)` — Property used to serialize the extended data to configuration without requiring the types are present. The text representation is stored independently of the live ExtendedData to handle ExtendedData types that may not be able to be loaded due to coming from unloaded or missing modules. The map is keyed with a FSoftObjectPath which represents the PathName of the data UScriptStruct.

#### class `UProductionSettings`  
`class UProductionSettings : public UDeveloperSettings`  
_L203-514_
- reflection: `UCLASS(config=Engine, defaultconfig)`
- inherits: `UDeveloperSettings`
- desc: Cinematic Production Settings
- L208 _public prototype_ `UProductionSettings() = default;`
- L211 _public member_ `constexpr static int32 ProductionNameMaxLength = 256;` — Maximum number of characters allowed in a Production Name
- L214 _public prototype_ `virtual FName GetContainerName() const override;`
- L215 _public prototype_ `virtual FName GetCategoryName() const override;`
- L216 _public prototype_ `virtual FName GetSectionName() const override;`
- L220 _public prototype_ `virtual void PostInitProperties() override;`
- L221 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L222 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L223 _public prototype_ `virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;`
- L224 _public prototype_ `virtual void PostEditUndo() override;`
- L231 _public prototype_ `const TArray<FCinematicProduction> GetProductions() const;` — Returns a copy of the production list
- L234 _public prototype_ `TOptional<const FCinematicProduction> GetProduction(FGuid ProductionID) const;` — Returns a copy of the production matching the input production ID (if it exists)
- L237 _public prototype_ `void AddProduction();` — Adds a new empty production to the list
- L240 _public prototype_ `void AddProduction(const FCinematicProduction& ProductionToAdd);` — Adds the input production to the list
- L243 _public prototype_ `void DuplicateProduction(FGuid ProductionID);` — Adds a duplicate of the input production to the list
- L246 _public prototype_ `void DeleteProduction(FGuid ProductionID);` — Removes the production matching the input ID from the list
- L249 _public prototype_ `void RenameProduction(FGuid ProductionID, FString NewName);` — Renames the production matching the input ID
- L252 _public prototype_ `TOptional<const FCinematicProduction> GetActiveProduction() const;` — Returns a copy of the active production (if there is one)
- L255 _public prototype_ `FGuid GetActiveProductionID() const;` — Returns the unique ID of the active production
- L258 _public prototype_ `void SetActiveProduction(FGuid ProductionID);` — Sets the active production based on the input production ID
- L261 _public prototype_ `bool IsActiveProduction(FGuid ProductionID) const;` — Returns true if the input production ID matches the ID of the active production
- L264 _public prototype_ `FFrameRate GetActiveDisplayRate() const;` — Returns the DefaultDisplayRate of the active production, or the underlying level sequence setting if there is no active production
- L267 _public prototype_ `int32 GetActiveStartFrame() const;` — Returns the DefaultStartFrame of the active production, or the value based on the underlying movie scene tools setting if there is no active production
- L270 _public prototype_ `ESubsequencePriority GetActiveSubsequencePriority() const;` — Returns the SubsequencePriority of the active production, or the default config value if there is no active production
- L273 _public prototype_ `void SetDisplayRate(FGuid ProductionID, FFrameRate DisplayRate);` — Sets the DefaultDisplayRate of the production matching the input ID
- L276 _public prototype_ `void SetStartFrame(FGuid ProductionID, int32 StartFrame);` — Sets the DefaultStartFrame of the production matching the input ID
- L279 _public prototype_ `void SetSubsequencePriority(FGuid ProductionID, ESubsequencePriority Priority);` — Sets the SubsequencePriority of the production matching the input ID
- L282 _public prototype_ `void AddNamespaceToDenyList(FGuid ProductionID, const FString& Namespace);` — Adds a Naming Token namespace to the DenyList of the production matching the input ID
- L285 _public prototype_ `void RemoveNamespaceFromDenyList(FGuid ProductionID, const FString& Namespace);` — Removes a Naming Token namespace from the DenyList of the production matching the input ID
- L288 _public prototype_ `void AddAssetNaming(FGuid ProductionID, const UClass* AssetClass, const FString& DefaultName);` — Adds a new entry into the DefaultAssetNames map of the production matching the input ID
- L291 _public prototype_ `void RemoveAssetNaming(FGuid ProductionID, const UClass* AssetClass);` — Removes an entry from the DefaultAssetNames map of the production matching the input ID
- L294 _public prototype_ `void AddTemplateFolder(FGuid ProductionID, const FString& Path, bool bCreateIfMissing=true);` — Add a new path to the input production's list of template folders
- L297 _public prototype_ `void RemoveTemplateFolder(FGuid ProductionID, const FString& Path);` — Removes a path from the input production's list of template folders
- L300 _public prototype_ `void SetTemplateFolderHierarchy(FGuid ProductionID, const TArray<FFolderTemplate>& TemplateHierarchy);` — Sets the input production's template folder hierarchy to the input array of template folders
- L303 _public prototype_ `void SetActiveDisplayRate(FFrameRate DisplayRate);` — Sets the DefaultDisplayRate of the active production
- L306 _public prototype_ `void SetActiveStartFrame(int32 StartFrame);` — Sets the DefaultStartFrame of the active production
- L309 _public prototype_ `void SetActiveSubsequencePriority(ESubsequencePriority Priority);` — Sets the SubsequencePriority of the active production
- L312 _public prototype_ `FString GetUniqueProductionName() const;` — Returns a new unique production name
- L313 _public prototype_ `FString GetUniqueProductionName(const FString& BaseName) const;`
- L316 _public function_ `bool IsLevelEditorToolbarEnabled() const` — Checks if the level editor toolbar is enabled.
- L319 _public function_ `FOnProductionListChanged& OnProductionListChanged()` — Returns the delegate that broadcasts when a production is added/removed
- L322 _public function_ `FOnActiveProductionChanged& OnActiveProductionChanged()` — Returns the delegate that broadcasts when the active production changes
- L326 _public function_ `template <typename TStruct> TStructView<TStruct> GetMutableProductionExtendedData(FGuid ProductionID)` — Given a production ID and data struct, tries to get a mutable view on the productions extended data of the matching type.
- L336 _public prototype_ `FStructView GetMutableProductionExtendedData(FGuid ProductionID, const UScriptStruct& DataStruct);` — Given a production ID and data struct, tries to get a mutable view on the productions extended data of the matching type.
- L340 _public function_ `template <typename TStruct> TConstStructView<TStruct> GetProductionExtendedData(FGuid ProductionID) const` — Given a production ID and data struct, tries to get a view on the productions extended data of the matching type.
- L350 _public prototype_ `FConstStructView GetProductionExtendedData(FGuid ProductionID, const UScriptStruct& DataStruct) const;` — Given a production ID and data struct, tries to get a view on the productions extended data of the matching type.
- L353 _public prototype_ `bool SetProductionExtendedData(FGuid ProductionID, const FConstStructView& DataStructView);` — Given a production ID and struct view, tries to set the struct in the productions extended data of the matching type.
- L387 _public prototype_ `[[nodiscard]] FScopedModifyProductionExtendedData ModifyProductionExtendedData(FGuid ProductionID);` — Get a FScopedModifyProductionExtendedData instance for the production matching the given production ID. This will allow modifying multiple extended data of a configured Production, ensuring modifications are exported correctly, ready to be saved back to the config with the new updates. e.g. ``` const FGuid TargetProductionId; // Set from elsewhere or use GetActiveProductionId() UProductionSettings* ProductionSettings = GetMutableDefault<UProductionSettings>(); FScopedModifyProductionExtendedData ModifyGuard = ProductionSettings->ModifyProductionExtendedData(TargetProductionId); if (TStructView<MyStruct> DataView1 = ProductionSettings->GetMutableProductionExtendedData<MyStruct>(TargetProductionId); DataView1.IsValid()) { MyStruct& MyStructRef = DataView1.Get(); ... // Modify MyStructRef ... } if (TStructView<MyOtherStruct> DataView2 = ProductionSettings->GetMutableProductionExtendedData<MyOtherStruct>(TargetProductionId); DataView2.IsValid()) { MyOtherStruct& MyOtherStructRef = DataView2.Get(); ... // Modify MyOtherStructRef ... } ``` For blueprints, use nodes GetProductionExtendedData (ProductionFunctionLibrary) and SetProductionExtendedData (ProductionFunctionLibrary).
- L412 _public prototype_ `[[nodiscard]] FScopedModifyProductionExtendedData ModifyProductionExtendedData(FGuid ProductionID, const UScriptStruct& ExtendedDataStruct);` — Get a FScopedModifyProductionExtendedData instance for the production matching the given production ID and extended data struct type. This will allow modifying the targeted extended data of a configured Production, ensuring modifications are exported correctly, ready to be saved back to the config with the new updates. e.g. ``` const FGuid TargetProductionId; // Set from elsewhere or use GetActiveProductionId() UProductionSettings* ProductionSettings = GetMutableDefault<UProductionSettings>(); if (TStructView<MyStruct> DataView = ProductionSettings->GetMutableProductionExtendedData<MyStruct>(TargetProductionId); DataView.IsValid()) { FScopedModifyProductionExtendedData ModifyGuard = ProductionSettings->ModifyProductionExtendedData(TargetProductionId); MyStruct& MyStructRef = DataView.Get(); ... // Modify MyStructRef ... } ``` For blueprints, use nodes GetProductionExtendedData (ProductionFunctionLibrary) and SetProductionExtendedData (ProductionFunctionLibrary).
- L415 _public prototype_ `static FName GetProductionsPropertyMemberName();` — Get the checked member name for the Productions property.
- L420 _public member_ `FOnProductionCreated OnProductionCreatedDynamic;` — `UPROPERTY(BlueprintAssignable, Category = "Cinematic Production", meta = (DisplayName = "On Production Created"))` — Blueprint-assignable delegate that broadcasts when a new production is created
- L424 _public member_ `FOnProductionSettingsChanged OnProductionSettingsChangedDynamic;` — `UPROPERTY(BlueprintAssignable, Category = "Cinematic Production", meta = (DisplayName = "On Production Settings Changed"))` — Blueprint-assignable delegate that broadcasts when a production's settings are modified
- L428 _public member_ `FOnActiveProductionSet OnActiveProductionSetDynamic;` — `UPROPERTY(BlueprintAssignable, Category = "Cinematic Production", meta = (DisplayName = "On Active Production Set"))` — Blueprint-assignable delegate that broadcasts when the active production changes
- L432 _private prototype_ `bool IsValidProductionName(const FString& ProductionName) const;` — Returns true if the input string is a valid Production name
- L435 _private prototype_ `void ApplyProjectOverrides();` — Applies overrides to various project settings based on the active production settings
- L438 _private prototype_ `void OverrideDefaultDisplayRate();` — Overrides the DefaultDisplayRate in the level sequence project settings based on the active production setting
- L441 _private prototype_ `void OverrideDefaultStartTime();` — Overrides the DefaultStartTime in the movie scene tools project settings based on the active production settings
- L444 _private prototype_ `void OverrideSubsequenceHierarchicalBias();` — Writes out the Hierarchical bias value (based on the Subsequence Priority setting) to EditorPerProjectUserSettings.ini
- L447 _private prototype_ `void OverrideDefaultAssetNames();` — Overrides the DefaultAssetNames property of the asset tools project settings based on the active production setting
- L450 _private prototype_ `void FilterNamingTokenNamespaces(TSet<FString>& Namespaces);` — Apply the active production's namespace deny list to the input set of namespace names
- L453 _private prototype_ `void SetActiveProductionName();` — Set the active production name and write out the new value to EditorPerProjectUserSettings.ini
- L456 _private prototype_ `void CacheProjectDefaults();` — Cache the default project settings that are overridden by the active production, used to reset when there is no active production
- L459 _private prototype_ `void OnPostEngineInit();` — Perform any setup after the engine has finished initilization.
- L462 _private prototype_ `const FCinematicProduction* GetActiveProductionPtr() const;` — Returns a pointer to the active production (if it exists)
- L465 _private prototype_ `void UpdateConfig();` — Try to update the default config file (will attempt to make the file writable if needed)
- L468 _private prototype_ `void NotifySettingsChange(const FCinematicProduction& Production);` — Update the config and broadcast OnProductionSettingsChangedDynamic for the given production
- L471 _private prototype_ `void ReloadProductionsExtendedData();` — Reload all Production extended data into the current Productions.
- L474 _private prototype_ `void BindToProductions();` — Binds to events on all productions.
- L477 _private prototype_ `void HandleProductionExtendedDataUpdated(const FCinematicProduction& SenderProduction, const UScriptStruct* ForData);` — Handler for when a Productions ExtendedData is updated.
- L480 _private prototype_ `void HandleProductionsChangeChainProperty(const TDoubleLinkedList<FProperty*>::TDoubleLinkedListNode& ProductionsChainNode, FPropertyChangedChainEvent& WithinPropertyChangedEvent);` — Given a property changed chain event and a node representing the productions property, handle any property changes that have occured to the Productions property.
- L485 _private member_ `FString ActiveProductionName;` — `UPROPERTY(VisibleAnywhere, Category = "Default", meta = (DisplayName = "Active Production"))` — Name of the active production
- L489 _private member_ `TArray<FCinematicProduction> Productions;` — `UPROPERTY(config, EditAnywhere, Category = "Default")` — List of available productions in this project
- L493 _private member_ `bool bEnableProductionsLevelEditorToolbar = true;` — `UPROPERTY(config, EditAnywhere, Category = "Default", meta = (ConfigRestartRequired = true, DisplayName = "Enable Production Toolbar"))` — Enable the production level editor toolbar.
- L496 _private member_ `FGuid ActiveProductionID;` — ID of the active production (in the Productions array)
- L499 _private member_ `FString ProjectDefaultDisplayRate;` — Cached default project settings that are overridden by the active production, used to reset when there is no active production
- L500 _private member_ `float ProjectDefaultStartTime;`
- L503 _private member_ `TSet<const UClass*> RegisteredAssetNameClasses;` — Asset classes for which Production Settings has currently registered a default name override with AssetTools. Tracked so we can unregister if the active production changes.
- L506 _private member_ `FString OriginalDefaultDisplayRateTooltip;` — Original tooltip text for sequencer settings
- L507 _private member_ `FString OriginalDefaultStartTimeTooltip;`
- L510 _private member_ `FOnProductionListChanged ProductionListChangedDelegate;` — Delegate that broadcasts when a production is added/removed
- L513 _private member_ `FOnActiveProductionChanged ActiveProductionChangedDelegate;` — Delegate that broadcasts when the active production changes

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API CINEASSEMBLYTOOLSEDITOR_API`
- L15 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnProductionListChanged);`
- L15 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnProductionListChanged);`
- L16 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnActiveProductionChanged);`
- L16 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnActiveProductionChanged);`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProductionExtendedDataExported, const FCinematicProduction& , const UScriptStruct* );`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnProductionExtendedDataExported, const FCinematicProduction& , const UScriptStruct* );`
- L195 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProductionCreated, const FCinematicProduction&, Production);`
- L195 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProductionCreated, const FCinematicProduction&, Production);`
- L196 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProductionSettingsChanged, const FCinematicProduction&, Production);`
- L196 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProductionSettingsChanged, const FCinematicProduction&, Production);`
- L197 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveProductionSet, const FCinematicProduction&, ActiveProduction, bool, bIsValid);`
- L197 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActiveProductionSet, const FCinematicProduction&, ActiveProduction, bool, bIsValid);`

### `Plugins/VirtualProduction/CinematicAssemblyTools/Source/CineAssemblyToolsEditor/Public/ScopedModifyProductionExtendedData.h` (Public)


#### class `FScopedModifyProductionExtendedData`  
`class FScopedModifyProductionExtendedData`  
_L33-76_
- desc: Helper class for scoping modifications to a Productions extended data. On destruction of the instance, Finish is called which will call update on the TargetProduction if it has not been already. Finish can also be called at any time if desired, and will not then be called on destruction. Use of this class is to create a locally scoped instance before making any modifications, and allowing it to fall out of scope or manually calling Finish when you wish those updates to propogate. eg. ``` { if (FInstancedStruct* ExtendedData = Production.FindOrLoadExtendedData(*FMyStruct::StaticStruct())) { FScopedModifyProductionExtendedData ModifyGuard(Production); ... // Modify ExtendedData ... } } ``` You can specify a specific ExtendedData UScriptStruct type to call update only for that type. If this is not provided at construction time, then all ExtendedData is updated on Finish.
- L37 _public prototype_ `FScopedModifyProductionExtendedData() = default;` — Default constructor that constructs into an inactive state.
- L40 _public prototype_ `FScopedModifyProductionExtendedData(FCinematicProduction& InProduction);` — Given a reference to a production, create a scoped modify instance.
- L47 _public prototype_ `FScopedModifyProductionExtendedData(FCinematicProduction& InProduction, const UScriptStruct& InTargetStruct);` — Given a reference to a production and a specific data struct type, create a scoped modify instance. If InTargetStruct is not found as an ExtendedData type within the Production, the scoped modify instance is not considered active.
- L50 _public prototype_ `virtual ~FScopedModifyProductionExtendedData();` — Destructor that will call Finish.
- L56 _public prototype_ `bool IsActive() const;` — Returns if this instance is active. It is considered active if it has not yet finished and has a valid Production reference and target data struct if supplied.
- L59 _public prototype_ `void Finish();` — Finish this scoped modify and update the extended data on the target production.
- L63 _private member_ `bool bOriginalBlockValue = false;` — Original value of the block flag for the production.
- L66 _private prototype_ `void Start();` — Start the modification and blocking of exported signals.
- L69 _private member_ `TStructView<FCinematicProduction> TargetProduction;` — View onto the target production object that is being modified.
- L72 _private member_ `TOptional<const UScriptStruct*> TargetStruct;` — Optional target struct type that is being updated as part of this modification.
- L75 _private member_ `bool bHasFinished = false;` — Whether this instance has had Finish called on it or not.
