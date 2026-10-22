# Plugins / RemoteControlUI

- module root: `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI`
- headers: 117; symbols: 2720
- symbol kinds: class=129, delegate=43, enum=17, enumerator=67, function=386, macro=2, member=660, namespace=38, prototype=1311, struct=32, typedef=23, variable=12
- PrivateDependencyModuleNames: ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BlueprintGraph, ClassViewer, ContentBrowser, Core, CoreUObject, DesktopWidgets, DeveloperSettings, EditorStyle, EditorWidgets, Engine, GraphEditor, HotReload, InputCore, LevelEditor, MainFrame, MessageLog, Projects, PropertyEditor, RemoteControl, RemoteControlCommon, RemoteControlLogic, RemoteControlProtocol, RemoteControlProtocolWidgets, SceneOutliner, Serialization, Slate, SlateCore, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UnrealEd, WidgetRegistration, WorkspaceMenuStructure

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/AssetDefinition/AssetDefinition_RemoteControlPreset.h` (Private)


#### class `UAssetDefinition_RemoteControlPreset`  
`class UAssetDefinition_RemoteControlPreset : public UAssetDefinitionDefault`  
_L9-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L15 _public prototype_ `virtual FText GetAssetDisplayName() const override;` — UAssetDefinition Begin
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L18 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L19 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`
- L20 _public prototype_ `virtual FAssetSupportResponse CanLocalize(const FAssetData& InAsset) const override;`
- L21 _public prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/AssetEditor/RemoteControlPresetEditorToolkit.h` (Private)


#### class `FRemoteControlPresetEditorToolkit`  
`class FRemoteControlPresetEditorToolkit : public FAssetEditorToolkit`  
_L14-56_
- inherits: `FAssetEditorToolkit`
- desc: Viewer/editor for a Remote Control Preset
- L20 _public prototype_ `static TSharedRef<FRemoteControlPresetEditorToolkit> CreateEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class URemoteControlPreset* InPreset);` — Create an editor for a remote control preset asset.
- L25 _public prototype_ `void InitRemoteControlPresetEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class URemoteControlPreset* InPreset);` — Initialize a remote control preset editor module.
- L26 _public prototype_ `~FRemoteControlPresetEditorToolkit();`
- L29 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L30 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L31 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L32 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L33 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L34 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L35 _public prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;`
- L40 _public prototype_ `virtual void FocusWindow(UObject* ObjectToFocusOn = nullptr) override;` — Begin IAssetEditorInstance interface
- L45 _private prototype_ `TSharedRef<SDockTab> HandleTabManagerSpawnPanelTab(const FSpawnTabArgs& Args);`
- L48 _private prototype_ `void InvokePanelTab();` — Handle invoking the remote control tab.
- L51 _private member_ `static const FName RemoteControlPanelAppIdentifier;` — Holds the remote control panel app identifier.
- L53 _private member_ `URemoteControlPreset* Preset = nullptr;` — Holds the preset being edited.
- L55 _private member_ `TSharedPtr<SRemoteControlPanel> PanelTab;` — Holds the panel widget

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/Commands/RemoteControlCommands.h` (Private)


#### class `FRemoteControlCommands`  
`class FRemoteControlCommands : public TCommands<FRemoteControlCommands>`  
_L12-103_
- inherits: `TCommands<FRemoteControlCommands>`
- desc: Defines commands for the Remote Control API which enables most functionality of the Remote Control Panel.
- L16 _public prototype_ `FRemoteControlCommands();`
- L20 _public prototype_ `virtual void RegisterCommands() override;`
- L27 _public member_ `TSharedPtr<FUICommandInfo> SavePreset;` — Holds the information about UI Command that saves the actively edited preset.
- L32 _public member_ `TSharedPtr<FUICommandInfo> ActivateProtocolsMode;` — Holds the information about UI Command that brings up a panel which holds the active protocol mappings.
- L37 _public member_ `TSharedPtr<FUICommandInfo> ActivateDetailsMode;` — Holds the information about UI Command that brings up the Entity Details UI panel.
- L42 _public member_ `TSharedPtr<FUICommandInfo> ActivateLogicMode;` — Holds the information about UI Command that brings up a panel which enables the RC Logical Behaviour.
- L47 _public member_ `TSharedPtr<FUICommandInfo> ActivateSignatureMode;` — Holds the information about UI Command that brings up the RC Signature UI panel.
- L52 _public member_ `TSharedPtr<FUICommandInfo> ActivateOutputLogMode;` — Holds the information about UI Command that brings up the Output panel.
- L57 _public member_ `TSharedPtr<FUICommandInfo> DeleteEntity;` — Holds the information about UI Command that deletes currently selected group/exposed entity.
- L62 _public member_ `TSharedPtr<FUICommandInfo> RenameEntity;` — Holds the information about UI Command that renames selected group/exposed entity.
- L67 _public member_ `TSharedPtr<FUICommandInfo> ChangePropId;` — Holds the information about UI Command that change the selected property Ids.
- L72 _public member_ `TSharedPtr<FUICommandInfo> CopyItem;` — UI Command for copying a UI item in the Remote Control preset. Currently used for Logic panel
- L77 _public member_ `TSharedPtr<FUICommandInfo> PasteItem;` — UI Command for pasting a UI item in the Remote Control preset. Currently used for Logic panel
- L82 _public member_ `TSharedPtr<FUICommandInfo> DuplicateItem;` — UI Command for duplicating a UI item in the Remote Control preset. Currently used for Logic panel
- L87 _public member_ `TSharedPtr<FUICommandInfo> UpdateValue;` — UI Command for updating the action in the action list with the value in the field list. Currently used for Logic panel
- L92 _public member_ `TSharedPtr<FUICommandInfo> SelectSource;` — UI Command for selecting the source of a property in an action. Currently used for Logic panel
- L97 _public member_ `TSharedPtr<FUICommandInfo> ProtocolsGeneratePropertyChangeEvents;` — UI Command to Toggle if protocols generate property changed events
- L102 _public member_ `TSharedPtr<FUICommandInfo> ProtocolsGenerateTransactions;` — UI Command to Toggle if protocols generate transactions

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/Factories/RemoteControlPresetActorFactory.h` (Private)


#### class `URemoteControlPresetActorFactory`  
`class URemoteControlPresetActorFactory : public UActorFactory`  
_L15-30_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L20 _public prototype_ `URemoteControlPresetActorFactory();`
- L23 _public prototype_ `virtual AActor* SpawnActor(UObject* InAsset, ULevel* InLevel, const FTransform& InTransform, const FActorSpawnParameters& InSpawnParams) override;`
- L24 _public prototype_ `virtual bool CanCreateActorFrom( const FAssetData& AssetData, FText& OutErrorMsg ) override;`
- L25 _public prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L29 _private member_ `TWeakPtr<SNotificationItem> ActiveNotification;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/Factories/RemoteControlPresetFactory.h` (Private)


#### class `URemoteControlPresetFactory`  
`class URemoteControlPresetFactory : public UFactory`  
_L14-26_
- reflection: `UCLASS(BlueprintType, hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for URemoteControlPreset objects.
- L19 _public prototype_ `URemoteControlPresetFactory();`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L23 _public prototype_ `virtual bool ShouldShowInNewMenu() const override;`
- L24 _public prototype_ `virtual uint32 GetMenuCategories() const override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/RemoteControlUIModule.h` (Private)


#### class `FRemoteControlUIModule`  
`class FRemoteControlUIModule : public IRemoteControlUIModule`  
_L24-333_
- inherits: `IRemoteControlUIModule`
- desc: A Remote Control module that allows exposing objects and properties from the editor.
- L28 _public function_ `FRemoteControlUIModule() : RemoteControlAssetCategoryBit(EAssetTypeCategories::Misc)`
- L39 _public function_ `static FRemoteControlUIModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L46 _public prototype_ `virtual void StartupModule() override;`
- L47 _public prototype_ `virtual void ShutdownModule() override;`
- L51 _public function_ `virtual FOnGenerateExtensions& GetExtensionGenerators() override`
- L52 _public function_ `virtual FOnRemoteControlPresetOpened& OnRemoteControlPresetOpened() override`
- L53 _public function_ `virtual FOnGenerateControllerExtensionsWidgets& OnGenerateControllerExtensionsWidgets() override`
- L54 _public function_ `virtual FOnAddControllerExtensionColumn& OnAddControllerExtensionColumn() override`
- L55 _public prototype_ `virtual FDelegateHandle AddPropertyFilter(FOnDisplayExposeIcon OnDisplayExposeIcon) override;`
- L56 _public prototype_ `virtual void RemovePropertyFilter(const FDelegateHandle& FilterDelegateHandle) override;`
- L57 _public prototype_ `virtual void RegisterMetadataCustomization(FName MetadataKey, FOnCustomizeMetadataEntry OnCustomizeCallback) override;`
- L58 _public prototype_ `virtual void UnregisterMetadataCustomization(FName MetadataKey) override;`
- L59 _public prototype_ `virtual URemoteControlPreset* GetActivePreset() const override;`
- L60 _public prototype_ `virtual uint32 GetRemoteControlAssetCategory() const override;`
- L61 _public prototype_ `virtual void RegisterSignatureCustomization(const TSharedPtr<IRCSignatureCustomization>& InCustomization) override;`
- L62 _public prototype_ `virtual void UnregisterSignatureCustomization(const TSharedPtr<IRCSignatureCustomization>& InCustomization) override;`
- L63 _public prototype_ `virtual void RegisterExposedEntitiesListSettingsForProtocol(const TSharedRef<IRCPanelExposedEntitiesListSettingsForProtocol>& InSettings) override;`
- L64 _public prototype_ `virtual void UnregisterExposedEntitiesListSettingsForProtocol(const TSharedRef<IRCPanelExposedEntitiesListSettingsForProtocol>& InSettings) override;`
- L65 _public prototype_ `virtual void RegisterExposedEntitiesPanelExtender(const TSharedRef<IRCExposedEntitiesPanelExtender>& InExtender) override;`
- L66 _public prototype_ `virtual void UnregisterExposedEntitiesPanelExtender(const TSharedRef<IRCExposedEntitiesPanelExtender>& InExtender) override;`
- L67 _public prototype_ `virtual void RegisterExposedEntitiesGroupWidgetFactory(const TSharedRef<IRCPanelExposedEntitiesGroupWidgetFactory>& InFactory) override;`
- L68 _public prototype_ `virtual void UnregisterExposedEntitiesGroupWidgetFactory(const TSharedRef<IRCPanelExposedEntitiesGroupWidgetFactory>& InFactory) override;`
- L69 _public prototype_ `virtual void RegisterExposedEntityWidgetFactory(const TSharedRef<IRCPanelExposedEntityWidgetFactory>& InFactory) override;`
- L70 _public prototype_ `virtual void UnregisterExposedEntityWidgetFactory(const TSharedRef<IRCPanelExposedEntityWidgetFactory>& InFactory) override;`
- L71 _public prototype_ `virtual void RegisterWidgetFactoryForType(UScriptStruct* RemoteControlEntityType, const FOnGenerateRCWidget& OnGenerateRCWidgetDelegate) override;`
- L72 _public prototype_ `virtual void UnregisterWidgetFactoryForType(UScriptStruct* RemoteControlEntityType) override;`
- L73 _public prototype_ `virtual void HighlightPropertyInDetailsPanel(const FPropertyPath& Path) const override;`
- L74 _public prototype_ `virtual void SelectObjects(const TArray<UObject*>& Objects) const override;`
- L75 _public prototype_ `virtual TSharedPtr<SWidget> CreateCustomControllerWidget(URCVirtualPropertyBase* InController, TSharedPtr<IPropertyHandle> InOriginalPropertyHandle) const override;`
- L76 _public prototype_ `virtual void RegisterPropertyResolver(FName InResolverId, const FRCPropertyResolver& InResolver) override;`
- L77 _public prototype_ `virtual void UnregisterPropertyResolver(FName InResolverId) override;`
- L80 _public prototype_ `void SelectSource(TSharedPtr<FRemoteControlEntity> InEntity);`
- L87 _public prototype_ `TSharedRef<SRemoteControlPanel> CreateRemoteControlPanel(URemoteControlPreset* Preset, const TSharedPtr<IToolkitHost>& ToolkitHost = TSharedPtr<IToolkitHost>());` — Create a remote control panel to display a given preset. @param The preset to display. @return The remote control widget.
- L89 _public prototype_ `void UnregisterRemoteControlPanel(SRemoteControlPanel* Panel);`
- L94 _public function_ `const TMap<FName, FOnCustomizeMetadataEntry>& GetEntityMetadataCustomizations() const` — Get the map of entity metadata entry customizations.
- L99 _public function_ `TConstArrayView<TSharedRef<IRCSignatureCustomization>> GetSignatureCustomizations() const`
- L104 _public function_ `TConstArrayView<TSharedRef<IRCExposedEntitiesPanelExtender>> GetExposedEntitiesPanelExtenders() const`
- L110 _public prototype_ `const TSharedRef<IRCPanelExposedEntitiesListSettingsForProtocol>* GetExposedEntitiesListSettingsForProtocol(const FName& ProtocolName) const;` — Returns the exposed entity list settings for a protocol, or nullptr if no entities list settings could be found
- L113 _public prototype_ `const TSharedRef<IRCPanelExposedEntitiesGroupWidgetFactory>* GetExposedEntitiesGroupWidgetFactory(const FName& ForColumnName, const FName& InActiveProtocol) const;` — Returns the exposed entities group widget factory, or nullptr if no widget factory is registered for the specified protocol and column name.
- L116 _public prototype_ `const TSharedRef<IRCPanelExposedEntityWidgetFactory>* GetExposedEntityWidgetFactory(const FName& ForColumnName, const FName& InActiveProtocol) const;` — Returns the exposed entity widget factory, or nullptr if no widget factory is registered for the specified protocol and column name.
- L119 _public member_ `static const FName RemoteControlPanelTabName;`
- L121 _public prototype_ `TSharedPtr<SRCPanelTreeNode> GenerateEntityWidget(const FGenerateWidgetArgs& Args);`
- L136 _private prototype_ `void BindRemoteControlCommands();`
- L137 _private prototype_ `void UnbindRemoteControlCommands();`
- L140 _private prototype_ `void RegisterContextMenuExtender();`
- L141 _private prototype_ `void UnregisterContextMenuExtender();`
- L144 _private prototype_ `void RegisterDetailRowExtension();`
- L145 _private prototype_ `void UnregisterDetailRowExtension();`
- L148 _private prototype_ `void RegisterEvents();`
- L149 _private prototype_ `void UnregisterEvents();`
- L152 _private prototype_ `TSharedPtr<IDetailsView> GetDetailsView(bool bInResolveIfInvalid=true, TConstArrayView<FName> InDetailsTabIdentifierOverrides = {}) const;` — Retrieves the saved details view. If invalid, optionally resolve by finding a new details panel to store in DetailsPanelWeak and return that
- L155 _private prototype_ `void ExtendPropertyRowContextMenu() const;` — Extend context row menu
- L158 _private prototype_ `void FillRemoteControlRowContextSection(UToolMenu* InToolMenu) const;` — Fills the RemoteControl details view row context menu
- L161 _private prototype_ `void GetSubPropertySubMenu(UToolMenu* InToolMenu, FRCExposesPropertyArgs InExposesPropertyArgs) const;` — Create the SubProperty expose/unexpose sub menu for the details view row context menu
- L164 _private prototype_ `void HandleCreatePropertyRowExtension(const FOnGenerateGlobalRowExtensionArgs& InArgs, TArray<FPropertyRowExtensionButton>& OutExtensions);` — Handle creating the row extensions.
- L170 _private prototype_ `TSharedPtr<SRemoteControlPanel> GetPanelForObject(const UObject* Object) const;` — Returns the Panel widget associated with an property by, in the case of embedded presets, examining the world that the property's owning object belongs to. In the case of assets, just returns the Panel ref in this module.
- L171 _private prototype_ `TSharedPtr<SRemoteControlPanel> GetPanelForProperty(const FRCExposesPropertyArgs& InPropertyArgs) const;`
- L172 _private prototype_ `TSharedPtr<SRemoteControlPanel> GetPanelForPropertyChangeEvent(const FPropertyChangedEvent& InPropertyChangeEvent) const;`
- L175 _private prototype_ `FSlateIcon OnGetPropertyActionIcon(const FRCExposesPropertyArgs InArgs) const;` — Handle getting the icon displayed in the row extension.
- L178 _private prototype_ `bool CanExecutePropertyAction(const FRCExposesPropertyArgs InArgs) const;` — Handle getting the expose button visibility.
- L181 _private prototype_ `ECheckBoxState GetPropertyExposedCheckState(const FRCExposesPropertyArgs InArgs) const;` — Is the property currently exposed?
- L184 _private prototype_ `void ExecutePropertyAction(const FRCExposesPropertyArgs InArgs) const;` — Handle clicking the expose button.
- L187 _private prototype_ `void OnToggleExposeSubProperty(const FRCExposesPropertyArgs InArgs, const FString InDesiredName = TEXT("")) const;` — Handle clicking the expose SubProperty button.
- L189 _private prototype_ `void OnToggleExposePropertyWithChild(const FRCExposesPropertyArgs InArgs);`
- L201 _private prototype_ `void OnExposeAll(const TArray<FRCExposesAllPropertiesArgs> InExposeAllArgs) const;` — Handle clicking the expose all in the SubProperty menu
- L204 _private prototype_ `void OnUnexposeAll(const TArray<FRCExposesAllPropertiesArgs> InExposeAllArgs) const;` — Handle clicking the expose all in the SubProperty menu
- L207 _private prototype_ `EPropertyExposeStatus GetPropertyExposeStatus(const FRCExposesPropertyArgs& InArgs) const;` — Returns whether a property is exposed, unexposed or unexposable.
- L210 _private prototype_ `FSlateIcon OnGetOverrideMaterialsIcon(const FRCExposesPropertyArgs InArgs) const;` — Handle getting the icon displayed in the row extension.
- L213 _private prototype_ `bool IsStaticOrSkeletalMaterialProperty(const FRCExposesPropertyArgs InArgs) const;` — Handle getting the override materials button visibility.
- L216 _private prototype_ `void AddGetPathOption(class FMenuBuilder& MenuBuilder, AActor* SelectedActor);` — Handle adding an option to get the object path in the actors' context menu.
- L219 _private prototype_ `TSharedRef<FExtender> ExtendLevelViewportContextMenuForRemoteControl(const TSharedRef<FUICommandList> CommandList, TArray<AActor*> SelectedActors);` — Handle adding the menu extender for the actors.
- L222 _private prototype_ `bool ShouldDisplayExposeIcon(const FRCExposesPropertyArgs& InArgs) const;` — Returns whether a given extension args should have an exposed icon.
- L225 _private prototype_ `bool ShouldSkipOwnPanelProperty(const FRCExposesPropertyArgs& InArgs) const;` — Return true if the extension args from remote control panel
- L227 _private prototype_ `bool IsAllowedOwnerObjects(TArray<UObject*> InOuterObjects) const;`
- L230 _private prototype_ `void RegisterStructCustomizations();`
- L231 _private prototype_ `void UnregisterStructCustomizations();`
- L234 _private prototype_ `void RegisterSettings();`
- L235 _private prototype_ `void UnregisterSettings();`
- L236 _private prototype_ `void OnSettingsModified(UObject*, struct FPropertyChangedEvent&);`
- L238 _private prototype_ `void RegisterWidgetFactories();`
- L241 _private prototype_ `FText GetPropertyActionTooltip(const FRCExposesPropertyArgs InArgs) const;` — Returns expose button tooltip based on exposed state
- L244 _private prototype_ `FText GetPropertyActionText(const FRCExposesPropertyArgs InArgs) const;` — Returns expose button text based on exposed state
- L247 _private prototype_ `void TryOverridingMaterials(const FRCExposesPropertyArgs InArgs);` — Attempts to replace the static or skeletal materials with their corressponding overrides.
- L250 _private prototype_ `UMeshComponent* GetSelectedMeshComponentToBeModified(UObject* InOwnerObject, UMaterialInterface* InOriginalMaterial);` — Return Selected Mesh Component by given OwnerObject and MaterialInterface
- L253 _private prototype_ `void RefreshPanels();` — Attempts to refresh the details panel.
- L256 _private prototype_ `bool ShouldCreateSubMenuForChildProperties(const TSharedPtr<SRemoteControlPanel>& InPanel, const FRCExposesPropertyArgs InPropertyArgs) const;` — Check if a sub menu should be created when ctrl+click on the eyeball icon in the details view
- L259 _private prototype_ `bool HasChildProperties(const FProperty* InProperty) const;` — Check if the property has child properties that can be exposed
- L262 _private prototype_ `void CreateSubMenuForChildProperties(const FRCExposesPropertyArgs InPropertyArgs) const;` — Create a sub menu for each sub property
- L265 _private prototype_ `bool HasChildPropertiesExposed(const FRCExposesPropertyArgs& InPropertyArgs) const;` — Check if any sub-property is exposed
- L267 _private prototype_ `void GetAllExposableSubPropertyFromStruct(const FRCExposesPropertyArgs InPropertyArgs, TArray<FRCExposesAllPropertiesArgs>& OutAllProperty) const;`
- L269 _private prototype_ `void RegisterDefaultPropertyResolvers();`
- L271 _private prototype_ `static bool ResolveDisplayClusterConfigurationDataProperty(const TSharedRef<FRemoteControlProperty>& InProperty, TArray<UObject*>& InOutBoundObjects, TSharedPtr<FPropertyPath>& OutPropertyPath);`
- L273 _private prototype_ `TSharedPtr<FPropertyPath> ResolveProperty(const TSharedRef<FRemoteControlProperty>& InProperty, TArray<UObject*>& InOutBoundObjects);`
- L277 _private member_ `FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors LevelViewportContextMenuRemoteControlExtender;` — Holds the context menu extender.
- L280 _private member_ `FDelegateHandle MenuExtenderDelegateHandle;` — Holds the menu extender delegate handle.
- L283 _private member_ `TWeakPtr<SRemoteControlPanel> WeakActivePanel;` — Holds a weak ptr to the active control panel.
- L286 _private member_ `TWeakPtr<IDetailTreeNode> WeakDetailsTreeNode;` — Holds a weak ptr to the owner tree node of the active details panel.
- L289 _private member_ `mutable TWeakPtr<IDetailsView> DetailsPanelWeak;` — Holds a weak ptr to the global details panel.
- L292 _private member_ `FOnGenerateExtensions ExtensionsGenerator;` — Delegate called to gather extensions added externally to the panel.
- L295 _private member_ `FOnRemoteControlPresetOpened RemoteControlPresetOpenedDelegate;` — Delegate called when a Remote Control Preset panel is created for the specified Remote Control Preset
- L298 _private member_ `FOnAddControllerExtensionColumn OnAddControllerExtensionColumnDelegate;` — Called when setting up/resetting the Controller panel list. Register to add custom column.
- L301 _private member_ `FOnGenerateControllerExtensionsWidgets GenerateControllerExtensionsWidgetsDelegate;` — Delegate called when a Remote Control Preset panel is created/opened for the specified Remote Control Preset
- L304 _private member_ `TMap<FDelegateHandle, FOnDisplayExposeIcon> ExternalFilterDelegates;` — Filters added by other plugins queried to determine if a property should display an expose icon.
- L307 _private member_ `TMap<FName, FOnCustomizeMetadataEntry> ExternalEntityMetadataCustomizations;` — Map of metadata key to customization handler.
- L310 _private member_ `TArray<TSharedRef<IRCSignatureCustomization>> SignatureCustomizations;` — Registered Signature Customizations
- L313 _private member_ `TArray<TSharedRef<IRCPanelExposedEntitiesListSettingsForProtocol>> ExposedEntitiesListSettingsForProtocols;` — Registered Exposed Entities List Settings for Protocols
- L316 _private member_ `TArray<TSharedRef<IRCExposedEntitiesPanelExtender>> ExposedEntitiesPanelExtenders;` — Registered Exposed Entities Panel Extenders
- L319 _private member_ `TArray<TSharedRef<IRCPanelExposedEntitiesGroupWidgetFactory>> ExposedEntitiesGroupWidgetFactories;` — Registered Exposed Entities Group Widget Factories
- L322 _private member_ `TArray<TSharedRef<IRCPanelExposedEntityWidgetFactory>> ExposedEntityWidgetFactories;` — Registered Exposed Entity Widget Factories
- L324 _private member_ `TMap<TWeakObjectPtr<UScriptStruct>, FOnGenerateRCWidget> GenerateWidgetDelegates;`
- L327 _private member_ `EAssetTypeCategories::Type RemoteControlAssetCategoryBit;` — Holds the advanced asset type category bit registered by Remote Control.
- L329 _private member_ `TArray<TWeakPtr<SRemoteControlPanel>> RegisteredRemoteControlPanels;`
- L332 _private member_ `TMap<FName, FRCPropertyResolver> PropertyResolvers;` — List of property sources resolvers.

#### enum `FRemoteControlUIModule::EPropertyExposeStatus`  
`enum class EPropertyExposeStatus : uint8`  
_L127-132_
- desc: The status of a property.
- L129 _public enumerator_ `Exposed`
- L130 _public enumerator_ `Unexposed`
- L131 _public enumerator_ `Unexposable`

#### struct `FRemoteControlUIModule::FRCExposesAllPropertiesArgs`  
`struct FRCExposesAllPropertiesArgs`  
_L192-199_
- desc: Store the information to expose/unexpose all properties from the parent one
- L194 _public member_ `FRCExposesPropertyArgs PropertyArgs;`
- L195 _public member_ `FText PropName;`
- L196 _public member_ `FString DesiredName;`
- L197 _public member_ `FText ExposedPropertyLabel;`
- L198 _public member_ `TAttribute<FText> ToolTip;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/Styling/RemoteControlStyles.h` (Private)


#### struct `FRCPanelStyle`  
`struct FRCPanelStyle : public FSlateWidgetStyle`  
_L19-120_
- reflection: `USTRUCT()`
- inherits: `FSlateWidgetStyle`
- desc: Represents the appearance of an RC Panel.
- L23 _public prototype_ `FRCPanelStyle();`
- L25 _public function_ `virtual ~FRCPanelStyle()`
- L28 _public prototype_ `virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;`
- L30 _public member_ `static const FName TypeName;`
- L31 _public function_ `virtual const FName GetTypeName() const override`
- L33 _public prototype_ `static const FRCPanelStyle& GetDefault();`
- L38 _public member_ `FSlateBrush ContentAreaBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Brush used by the RC Panels to draw the content associated with this panel.
- L39 _public function_ `FRCPanelStyle& SetContentAreaBrush(const FSlateBrush& InContentAreaBrush)`
- L43 _public member_ `FSlateBrush ContentAreaBrushDark;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Brush used by the RC Panels to draw the content associated with this panel (Dark).
- L44 _public function_ `FRCPanelStyle& SetContentAreaBrushDark(const FSlateBrush& InContentAreaBrushDark)`
- L48 _public member_ `FSlateBrush ContentAreaBrushLight;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Brush used by the RC Panels to draw the content associated with this panel (Light).
- L49 _public function_ `FRCPanelStyle& SetContentAreaBrushLight(const FSlateBrush& InContentAreaBrushLight)`
- L53 _public member_ `FButtonStyle FlatButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Style used for the flat button
- L54 _public function_ `FRCPanelStyle& SetFlatButtonStyle(const FButtonStyle& InFlatButtonStyle)`
- L58 _public member_ `FMargin HeaderRowPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Panel Header Row Style
- L59 _public function_ `FRCPanelStyle& SetHeaderRowPadding(const FMargin& InHeaderRowPadding)`
- L63 _public member_ `FHeaderRowStyle HeaderRowStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Panel Header Row Style
- L64 _public function_ `FRCPanelStyle& SetHeaderRowStyle(const FHeaderRowStyle& InHeaderRowStyle)`
- L68 _public member_ `FTextBlockStyle HeaderTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Panel Header Text Style
- L69 _public function_ `FRCPanelStyle& SetHeaderTextStyle(const FTextBlockStyle& InHeaderTextStyle)`
- L73 _public member_ `FVector2D IconSize;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Padding used around this panel
- L74 _public function_ `FRCPanelStyle& SetIconSize(const FVector2D& InIconSize)`
- L78 _public member_ `FMargin PanelPadding;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Padding used around this panel
- L79 _public function_ `FRCPanelStyle& SetPanelPadding(const FMargin& InPanelPadding)`
- L83 _public member_ `FTextBlockStyle PanelTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Panel Text Style
- L84 _public function_ `FRCPanelStyle& SetPanelTextStyle(const FTextBlockStyle& InPanelTextStyle)`
- L88 _public member_ `FTextBlockStyle SectionHeaderTextStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Panel Section Header Text Style
- L89 _public function_ `FRCPanelStyle& SetSectionHeaderTextStyle(const FTextBlockStyle& InSectionHeaderTextStyle)`
- L93 _public member_ `FSlateBrush SectionHeaderBrush;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Brush used by the RC Panels to draw the section header associated with this panel.
- L94 _public function_ `FRCPanelStyle& SetSectionHeaderBrush(const FSlateBrush& InSectionHeaderBrush)`
- L98 _public member_ `FTableRowStyle TableRowStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Panel Table Row Style
- L99 _public function_ `FRCPanelStyle& SetTableRowStyle(const FTableRowStyle& InTableRowStyle)`
- L103 _public member_ `FTableViewStyle TableViewStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Panel Table View Style
- L104 _public function_ `FRCPanelStyle& SetTableViewStyle(const FTableViewStyle& InTableViewStyle)`
- L108 _public member_ `FCheckBoxStyle SwitchButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Style used for the switch button
- L109 _public function_ `FRCPanelStyle& SetSwitchButtonStyle(const FCheckBoxStyle& InSwitchButtonStyle)`
- L113 _public member_ `FCheckBoxStyle ToggleButtonStyle;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Style used for the toggle button
- L114 _public function_ `FRCPanelStyle& SetToggleButtonStyle(const FCheckBoxStyle& InToggleButtonStyle)`
- L118 _public member_ `float SplitterHandleSize;` — `UPROPERTY(EditAnywhere, Category = Appearance)` — Splitter handle size
- L119 _public function_ `FRCPanelStyle& SetSplitterHandleSize(const float InSplitterHandleSize)`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/Bind/RCActionBindModel.h` (Private)


#### class `FRCActionBindModel`  
`class FRCActionBindModel : public FRCActionModel`  
_L17-33_
- inherits: `FRCActionModel`
- desc: ~ FRCActionBindModel ~ UI model for representing an Action of the Bind Behaviour.
- L20 _public function_ `FRCActionBindModel(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionModel(InAction, InBehaviourItem, InRemoteControlPanel)`
- L26 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FRCActionBindModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — OnGenerateRow delegate for the Actions List View
- L29 _public prototype_ `static TSharedPtr<SHeaderRow> GetHeaderRow();` — Get the Header Row appropriate for this particular Action model
- L32 _public prototype_ `static TSharedPtr<FRCActionBindModel> GetModelByActionType(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);` — Chooses the appropriate Action model for the current class and field type

#### class `FRCPropertyActionBindModel`  
`class FRCPropertyActionBindModel : public FRCActionBindModel`  
_L40-50_
- inherits: `FRCActionBindModel`
- desc: ~ FRCPropertyActionBindModel ~ UI model for Property based Bind Actions
- L43 _public function_ `FRCPropertyActionBindModel(URCPropertyBindAction* InPropertyAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionBindModel(InPropertyAction, InBehaviourItem, InRemoteControlPanel)`
- L49 _public prototype_ `virtual FLinearColor GetActionTypeColor() const override;` — Color code for this Action

#### class `FRCPropertyIdActionBindModel`  
`class FRCPropertyIdActionBindModel : public FRCActionBindModel, public FRCPropertyIdActionType`  
_L57-80_
- inherits: `FRCActionBindModel,FRCPropertyIdActionType`
- desc: FRCPropertyIdActionBindModel UI model for PropertyId based Bind Actions
- L60 _public function_ `FRCPropertyIdActionBindModel(URCPropertyIdAction* InPropertyIdAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionBindModel(InPropertyIdAction, InBehaviourItem, InRemoteControlPanel) , FRCPropertyIdActionType(InPropertyIdAction)`
- L66 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action
- L71 _public function_ `virtual TSharedRef<SWidget> GetNameWidget() const override` — Widget representing Action Name field
- L76 _public function_ `virtual TSharedRef<SWidget> GetWidget() const override` — Widget representing the Value field

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/Conditional/RCActionConditionalModel.h` (Private)


#### class `FRCActionConditionalModel`  
`class FRCActionConditionalModel : public FRCActionModel`  
_L27-64_
- inherits: `FRCActionModel`
- desc: ~ FRCActionConditionalModel ~ UI model for representing an Action of the Conditional Behaviour. Contains a Condition widget for representing the comparand/comparator and target property/value widgets <Actions Table>       <Condition>                <Description>         <Value> Color coding | Comparator+Comparand | Target Property | Value To Set
- L30 _public prototype_ `FRCActionConditionalModel(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L35 _public prototype_ `TSharedRef<SWidget> GetConditionWidget();` — Widget representing the Condition (Comparator|Comparand) used to trigger the corresponding action
- L38 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FRCActionConditionalModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — OnGenerateRow delegate for the Actions List View
- L41 _public prototype_ `static TSharedPtr<SHeaderRow> GetHeaderRow();` — Get the Header Row appropriate for this particular Action model
- L44 _public prototype_ `static TSharedPtr<FRCActionConditionalModel> GetModelByActionType(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);` — Chooses the appropriate Action model for the current class and field type
- L48 _private prototype_ `FText CreateConditionComparandText(const URCBehaviourConditional* InBehaviour, const FRCBehaviourCondition* InCondition);` — Create the text to be assigned to the ConditionWidget
- L51 _private prototype_ `void UpdateConditionWidget(const FText& InNewText) const;` — Update the condition widget text with the new text given
- L54 _private prototype_ `TSharedRef<SWidget> OnGenerateConditionWidget(class URCVirtualPropertySelfContainer* InComparand);` — Called when constructing the widget or after editing the condition value
- L57 _private prototype_ `void OnExitingEditingMode();` — Called when exiting edit mode to update other selected actions
- L60 _private prototype_ `void UpdateSelectedConditionalActionModel(const FRCBehaviourCondition* InConditionToCopy, const FText& InNewConditionText) const;` — Called when updating the condition to update every other actions currently selected with the new condition
- L63 _private member_ `TSharedPtr<STextBlock> ConditionWidget;` — Holding the widget that display the condition as text

#### class `FRCPropertyActionConditionalModel`  
`class FRCPropertyActionConditionalModel : public FRCActionConditionalModel, public FRCPropertyActionType`  
_L71-88_
- inherits: `FRCActionConditionalModel,FRCPropertyActionType`
- desc: ~ FRCPropertyActionConditionalModel ~ UI model for Property based Conditional Actions
- L74 _public function_ `FRCPropertyActionConditionalModel(URCPropertyAction* InPropertyAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionConditionalModel(InPropertyAction, InBehaviourItem, InRemoteControlPanel), FRCPropertyActionType(InPropertyAction)`
- L78 _public function_ `virtual TSharedRef<SWidget> GetWidget() const override`
- L84 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action

#### class `FRCFunctionActionConditionalModel`  
`class FRCFunctionActionConditionalModel : public FRCActionConditionalModel, public FRCFunctionActionType`  
_L95-107_
- inherits: `FRCActionConditionalModel,FRCFunctionActionType`
- desc: ~ FRCFunctionActionConditionalModel ~ UI model for Function based Conditional Actions
- L98 _public function_ `FRCFunctionActionConditionalModel(URCFunctionAction* InFunctionAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionConditionalModel(InFunctionAction, InBehaviourItem, InRemoteControlPanel) , FRCFunctionActionType(InFunctionAction)`
- L103 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action

#### class `FRCPropertyIdActionConditionalModel`  
`class FRCPropertyIdActionConditionalModel : public FRCActionConditionalModel, public FRCPropertyIdActionType`  
_L114-139_
- inherits: `FRCActionConditionalModel,FRCPropertyIdActionType`
- desc: FRCPropertyIdActionConditionalModel UI model for PropertyId based Conditional Actions
- L117 _public function_ `FRCPropertyIdActionConditionalModel(URCPropertyIdAction* InPropertyIdAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionConditionalModel(InPropertyIdAction, InBehaviourItem, InRemoteControlPanel) , FRCPropertyIdActionType(InPropertyIdAction)`
- L123 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action
- L129 _public function_ `virtual TSharedRef<SWidget> GetNameWidget() const override` — Widget representing Action Name field
- L135 _public function_ `virtual TSharedRef<SWidget> GetWidget() const override` — Widget representing the Value field

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/Path/RCActionSetAssetByPathModelNew.h` (Private)


#### class `FRCActionSetAssetByPathModelNew`  
`class FRCActionSetAssetByPathModelNew : public FRCActionModel`  
_L18-34_
- inherits: `FRCActionModel`
- desc: ~ FRCActionSetAssetByPathModelNew ~ UI model for representing an Action of the Set Asset (new)
- L21 _public function_ `FRCActionSetAssetByPathModelNew(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionModel(InAction, InBehaviourItem, InRemoteControlPanel)`
- L27 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FRCActionSetAssetByPathModelNew> InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — OnGenerateRow delegate for the Actions List View
- L30 _public prototype_ `static TSharedPtr<SHeaderRow> GetHeaderRow();` — Get the Header Row appropriate for this particular Action model
- L33 _public prototype_ `static TSharedPtr<FRCActionSetAssetByPathModelNew> GetModelByActionType(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);` — Chooses the appropriate Action model for the current class and field type

#### class `FRCPropertyActionSetAssetByPathModelNew`  
`class FRCPropertyActionSetAssetByPathModelNew : public FRCActionSetAssetByPathModelNew`  
_L41-51_
- inherits: `FRCActionSetAssetByPathModelNew`
- desc: ~ FRCPropertyActionSetAssetByPathModelNew ~ UI model for representing a Property Action of the Set Asset (new)
- L44 _public function_ `FRCPropertyActionSetAssetByPathModelNew(URCSetAssetByPathActionNew* InPropertyAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionSetAssetByPathModelNew(InPropertyAction, InBehaviourItem, InRemoteControlPanel)`
- L50 _public prototype_ `virtual FLinearColor GetActionTypeColor() const override;` — Color code for this Action

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/RCActionModel.h` (Private)


#### class `FRCActionModel`  
`class FRCActionModel : public FRCLogicModeBase`  
_L34-97_
- inherits: `FRCLogicModeBase`
- desc: ~ FRCActionModel ~ UI model for representing an Action. Contains a row widget with Action related metadata and a generic value widget
- L37 _public member_ `static const FLazyName ActionModelName;`
- L39 _public prototype_ `FRCActionModel(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L41 _public function_ `virtual FName GetModelType() const override`
- L47 _public prototype_ `URCAction* GetAction() const;` — Fetch the Action (data model) associated with us
- L50 _public prototype_ `virtual TSharedRef<SWidget> GetNameWidget() const;` — Widget representing Action Name field
- L53 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() const override;` — Widget representing the Value field
- L55 _public prototype_ `virtual int32 RemoveModel() override;`
- L58 _public prototype_ `virtual TSharedRef<SWidget> GetTypeColorTagWidget() const;` — Widget representing Color Coding for the Action Type
- L61 _public prototype_ `virtual FLinearColor GetActionTypeColor() const = 0;` — Color code for this Action. Customized per action type
- L64 _public prototype_ `virtual void AddSpecialContextMenuOptions(FMenuBuilder& MenuBuilder);` — Allows Logic panels to add special functionality to the Context Menu based on context
- L67 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FRCActionModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — OnGenerateRow delegate for the Actions List View
- L70 _public prototype_ `static TSharedPtr<SHeaderRow> GetHeaderRow();` — Get the Header Row appropriate for this particular Action model
- L73 _public prototype_ `static TSharedPtr<FRCActionModel> GetModelByActionType(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);` — Chooses the appropriate Action model for the current class and field type
- L76 _public prototype_ `virtual void OnSelectionExit();` — Invoked when this Action item no longer has focus
- L79 _public function_ `TSharedPtr<FRCBehaviourModel> GetParentBehaviour()` — Returns the Behaviour Item associated with us
- L86 _protected member_ `TWeakObjectPtr<URCAction> ActionWeakPtr;` — The Action (data model) associated with us
- L89 _protected member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L92 _protected member_ `TWeakPtr<FRCBehaviourModel> BehaviourItemWeakPtr;` — The Behaviour (UI model) associated with us
- L96 _protected member_ `TSharedPtr<SRCVirtualPropertyWidget> EditableVirtualPropertyWidget;` — Optional: An editable virtual property widget associated with this row Child action models can assign this variable and receive the Edit context menu option automatically

#### class `FRCPropertyActionType`  
`class FRCPropertyActionType`  
_L104-136_
- desc: ~ FRCPropertyActionType ~ Reusable class containing Property action related data and functions
- L107 _public prototype_ `FRCPropertyActionType(URCPropertyAction* InPropertyAction);`
- L109 _public prototype_ `~FRCPropertyActionType();`
- L112 _public prototype_ `const FName& GetPropertyName() const;` — Property Name associated with this Action
- L117 _public prototype_ `TSharedRef<SWidget> GetPropertyWidget() const;` — The widget to be rendered for this Property Represents the input field which the user will use to set a value for this Action
- L119 _public prototype_ `FLinearColor GetPropertyTypeColor() const;`
- L123 _protected prototype_ `void OnActionValueChange() const;` — Callback for when the ChangeProperty type is ValueSet
- L126 _protected prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangeEvent) const;` — Callback when the action value change
- L129 _protected member_ `TWeakObjectPtr<URCPropertyAction> PropertyActionWeakPtr;` — The Property Action (data model) associated with us
- L132 _protected member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The row generator used to represent this widget as a row, when used with SListView
- L135 _protected member_ `TWeakPtr<IDetailTreeNode> DetailTreeNodeWeakPtr;` — Used to create a generic Value Widget for the property row widget

#### class `FRCFunctionActionType`  
`class FRCFunctionActionType`  
_L143-158_
- desc: ~ FRCFunctionActionType ~ Reusable class containing Function action related data and functions
- L146 _public function_ `FRCFunctionActionType(URCFunctionAction* InFunctionAction) : FunctionActionWeakPtr(InFunctionAction)`
- L149 _public function_ `FLinearColor GetFunctionTypeColor() const` — Color code for function actions in the Actions table
- L157 _protected member_ `TWeakObjectPtr<URCFunctionAction> FunctionActionWeakPtr;` — The Function Action (data model) associated with us

#### class `FRCPropertyIdActionType`  
`class FRCPropertyIdActionType`  
_L165-217_
- desc: FRCPropertyIdActionType Reusable class containing PropertyID action related data and functions
- L168 _public prototype_ `FRCPropertyIdActionType(URCPropertyIdAction* InPropertyIdAction);`
- L170 _public prototype_ `~FRCPropertyIdActionType();`
- L173 _public prototype_ `FLinearColor GetPropertyIdTypeColor() const;` — Color code for function actions in the Actions table
- L176 _public prototype_ `TSharedRef<SWidget> GetPropertyIdNameWidget() const;` — Widget representing Action Name field
- L181 _public prototype_ `TSharedRef<SWidget> GetPropertyIdValueWidget() const;` — The widget to be rendered for this PropertyId Represents the input field which the user will use to set a value for this Action
- L185 _private prototype_ `void OnActionValueChange() const;` — Callback for when the ChangeProperty type is ValueSet
- L188 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangeEvent) const;` — Callback when the action value change
- L191 _private prototype_ `void RefreshNameWidget();` — Recreates the name section of this row widget.
- L194 _private prototype_ `void RefreshValueWidget();` — Recreates the value section of this row widget.
- L198 _protected member_ `TWeakObjectPtr<URCPropertyIdAction> PropertyIdActionWeakPtr;` — The PropertyId Action (data model) associated with this.
- L201 _protected member_ `TSharedPtr<IPropertyRowGenerator> PropertyIdNameRowGenerator;` — The row generator used to represent name of this widget as a row, when used with SListView
- L204 _protected member_ `TMap<FPropertyIdContainerKey, TSharedPtr<IPropertyRowGenerator>> PropertyIdValueRowGenerator;` — The cache of the row generator used to not recreate it
- L207 _protected member_ `TMap<FPropertyIdContainerKey, TSharedPtr<IPropertyRowGenerator>> CachedPropertyIdValueRowGenerator;` — The row generator used to represent value of this widget as a row, when used with SListView
- L210 _protected member_ `TWeakPtr<IDetailTreeNode> FieldIdTreeNodeWeakPtr;` — Used to create a generic Field Id Widget for the property row widget
- L213 _protected member_ `TMap<FPropertyIdContainerKey, TWeakPtr<IDetailTreeNode>> ValueTreeNodeWeakPtr;` — Used to create a generic Value Widget for the property row widget
- L216 _protected member_ `TMap<FPropertyIdContainerKey, TWeakPtr<IDetailTreeNode>> CachedValueTreeNodeWeakPtr;` — Used to cache a generic Value Widget for the property row widget to not recreate it

#### class `FRCPropertyActionModel`  
`class FRCPropertyActionModel : public FRCActionModel, public FRCPropertyActionType`  
_L224-241_
- inherits: `FRCActionModel,FRCPropertyActionType`
- desc: ~ FRCPropertyActionModel ~ UI model for Property based Actions
- L227 _public function_ `FRCPropertyActionModel(URCPropertyAction* InPropertyAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionModel(InPropertyAction, InBehaviourItem, InRemoteControlPanel), FRCPropertyActionType(InPropertyAction)`
- L231 _public function_ `virtual TSharedRef<SWidget> GetWidget() const override`
- L237 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action

#### class `FRCFunctionActionModel`  
`class FRCFunctionActionModel : public FRCActionModel, public FRCFunctionActionType`  
_L248-260_
- inherits: `FRCActionModel,FRCFunctionActionType`
- desc: ~ FRCFunctionActionModel ~ UI model for Function based Actions
- L251 _public function_ `FRCFunctionActionModel(URCFunctionAction* InFunctionAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionModel(InFunctionAction, InBehaviourItem, InRemoteControlPanel) , FRCFunctionActionType(InFunctionAction)`
- L256 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action

#### class `FRCPropertyIdActionModel`  
`class FRCPropertyIdActionModel : public FRCActionModel, public FRCPropertyIdActionType`  
_L267-292_
- inherits: `FRCActionModel,FRCPropertyIdActionType`
- desc: FRCPropertyIdActionModel UI model for PropertyId based Actions
- L270 _public function_ `FRCPropertyIdActionModel(URCPropertyIdAction* InPropertyIdAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionModel(InPropertyIdAction, InBehaviourItem, InRemoteControlPanel) , FRCPropertyIdActionType(InPropertyIdAction)`
- L276 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action
- L282 _public function_ `virtual TSharedRef<SWidget> GetNameWidget() const override` — Widget representing Action Name field
- L288 _public function_ `virtual TSharedRef<SWidget> GetWidget() const override` — Widget representing the Value field

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/RangeMap/RCActionRangeMapModel.h` (Private)


#### class `FRCActionRangeMapModel`  
`class FRCActionRangeMapModel : public FRCActionModel`  
_L20-54_
- inherits: `FRCActionModel`
- desc: ~ FRCActionRangeMapModel ~ UI Model for representing Actions as Input for the RangeMap Behaviour. Contains and represents, other than name and value, a step value being a value between 0 to 1. <Input Value> <Name> <Value>
- L23 _public prototype_ `FRCActionRangeMapModel(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L28 _public prototype_ `virtual TSharedRef<SWidget> GetInputWidget();` — Simple Widget representing the Normalized Value or Input Value for the Range and this particular Value.
- L31 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FRCActionRangeMapModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — OnGenerateRow delegate for the Actions List View
- L34 _public prototype_ `static TSharedPtr<SHeaderRow> GetHeaderRow();` — Get the Header Row appropriate for this particular Action model
- L37 _public prototype_ `static TSharedPtr<FRCActionRangeMapModel> GetModelByActionType(URCAction* InAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);` — Chooses the appropriate Action model for the current class and field type
- L41 _private prototype_ `void UpdateConditionWidget(const FText& InNewText) const;` — Update the condition widget text with the new text given
- L44 _private prototype_ `void UpdateSelectedRangeMapActionModel(double InNewValue, const FText& InNewConditionText) const;` — Called when updating the condition to update every other actions currently selected with the new condition
- L47 _private prototype_ `TSharedRef<SWidget> OnGenerateInputWidget(class URCVirtualPropertySelfContainer* InComparand) const;` — Called when constructing the widget or after editing the condition value
- L50 _private prototype_ `void OnExitingEditingMode() const;` — Called when exiting edit mode to update other selected actions
- L53 _private member_ `TSharedPtr<STextBlock> ConditionWidget;` — Holding the widget that display the condition as text

#### class `FRCPropertyActionRangeMapModel`  
`class FRCPropertyActionRangeMapModel : public FRCActionRangeMapModel, public FRCPropertyActionType`  
_L61-78_
- inherits: `FRCActionRangeMapModel,FRCPropertyActionType`
- desc: ~ FRCPropertyActionRangeMapModel ~ UI model for Property based RangeMap Actions
- L64 _public function_ `FRCPropertyActionRangeMapModel(URCPropertyAction* InPropertyAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionRangeMapModel(InPropertyAction, InBehaviourItem, InRemoteControlPanel), FRCPropertyActionType(InPropertyAction)`
- L68 _public function_ `virtual TSharedRef<SWidget> GetWidget() const override`
- L74 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action

#### class `FRCFunctionActionRangeMapModel`  
`class FRCFunctionActionRangeMapModel : public FRCActionRangeMapModel, public FRCFunctionActionType`  
_L85-97_
- inherits: `FRCActionRangeMapModel,FRCFunctionActionType`
- desc: ~ FRCFunctionActionRangeMapModel ~ UI model for Function based RangeMap Actions
- L88 _public function_ `FRCFunctionActionRangeMapModel (URCFunctionAction* InFunctionAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionRangeMapModel(InFunctionAction, InBehaviourItem, InRemoteControlPanel) , FRCFunctionActionType(InFunctionAction)`
- L93 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action

#### class `FRCPropertyIdActionRangeMapModel`  
`class FRCPropertyIdActionRangeMapModel : public FRCActionRangeMapModel, public FRCPropertyIdActionType`  
_L104-126_
- inherits: `FRCActionRangeMapModel,FRCPropertyIdActionType`
- desc: FRCPropertyIdActionRangeMapModel UI model for PropertyId based RangeMap Actions
- L107 _public function_ `FRCPropertyIdActionRangeMapModel(URCPropertyIdAction* InPropertyIdAction, const TSharedPtr<class FRCBehaviourModel> InBehaviourItem, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel) : FRCActionRangeMapModel(InPropertyIdAction, InBehaviourItem, InRemoteControlPanel) , FRCPropertyIdActionType(InPropertyIdAction)`
- L112 _public function_ `virtual FLinearColor GetActionTypeColor() const override` — Color code for this Action
- L117 _public function_ `virtual TSharedRef<SWidget> GetNameWidget() const override` — Widget representing Action Name field
- L122 _public function_ `virtual TSharedRef<SWidget> GetWidget() const override` — Widget representing the Value field

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/SRCActionPanel.h` (Private)


#### class `SRCActionPanel`  
`class SRCActionPanel : public SRCLogicPanelBase`  
_L31-199_
- inherits: `SRCLogicPanelBase`
- desc: ~ SRCActionPanel ~ UI Widget for Action Panel. Contains a header, footer, list of actions and a behaviour specific panel
- L34 _public function_ `SLATE_BEGIN_ARGS(SRCActionPanel)`
- L38 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRemoteControlPanel>& InPanel);`
- L44 _public prototype_ `bool IsListFocused() const;` — Whether the Actions list widget currently has focus.
- L47 _public prototype_ `virtual void DeleteSelectedPanelItems() override;` — Delete Items UI command implementation for this panel
- L50 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() const override;` — Returns the UI items currently selected by the user (if any). To be implemented per child panel
- L53 _public prototype_ `virtual void DuplicateSelectedPanelItems() override;` — "Duplicate Items" UI command implementation for Action panel
- L56 _public prototype_ `virtual void CopySelectedPanelItems() override;` — "Copy Items" UI command implementation for Action panel
- L59 _public prototype_ `virtual void PasteItemsFromClipboard() override;` — "Paste Items" UI command implementation for Action panel
- L62 _public prototype_ `virtual bool CanPasteClipboardItems(const TArrayView<const TObjectPtr<UObject>> InLogicClipboardItems) const override;` — Whether clipboard items can be successfully pasted into this panel
- L65 _public prototype_ `virtual void UpdateValue() override;` — "Update Value" UI command implementation for panels
- L68 _public prototype_ `virtual bool CanUpdateValue() const override;` — Whether this panel can call the UpdateValue command
- L71 _public prototype_ `virtual FText GetPasteItemMenuEntrySuffix() override;` — Provides an item suffix for the Paste context menu to provide users with useful context on the nature of the item being pasted
- L74 _public prototype_ `URCAction* AddAction();` — Adds an PropertyId Action for the currently active Behaviour and broadcasts to parent panels
- L77 _public prototype_ `URCAction* AddAction(FName InFieldId);` — Adds an PropertyId Action for the currently active Behaviour and broadcasts to parent panels
- L80 _public prototype_ `URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField);` — Adds an Action for the currently active Behaviour and broadcasts to parent panels
- L83 _public prototype_ `bool CanHaveActionForField(const FGuid& InRemoteControlFieldId);` — Whether this Actions panel can create an action for the given remote control field
- L86 _public prototype_ `void SetIsBehaviourEnabled(const bool bIsEnabled);` — Set the Enabled state of our parent Behaviour
- L89 _public function_ `TSharedPtr<FRCBehaviourModel> GetSelectedBehaviourItem()` — Fetches the currently selected behaviour item
- L95 _public prototype_ `void RefreshIsBehaviourEnabled(const bool bIsEnabled);` — Refreshes the UI widgets enabled state depending on whether the parent behaviour is currently enabled
- L99 _protected prototype_ `virtual FReply RequestDeleteSelectedItem() override;` — Warns user before deleting a selected panel item.
- L102 _protected prototype_ `virtual FReply RequestDeleteAllItems() override;` — Warns user before deleting all items in a panel.
- L106 _private prototype_ `EVisibility HandleAddAllButtonVisibility() const;` — Determines the visibility Add All Button.
- L109 _private prototype_ `EVisibility HandleSelectSourceVisibility() const;` — Determines the visibility Select Source Button.
- L115 _private prototype_ `void OnBehaviourSelectionChanged(TSharedPtr<FRCBehaviourModel> InBehaviourItem);` — Behaviour selection change listener. Updates the list of actions from newly selected Behaviour
- L118 _private prototype_ `void UpdateWrappedWidget(TSharedPtr<FRCBehaviourModel> InBehaviourItem = nullptr);` — Rebuilds the Action Panel for a newly selected Behaviour
- L121 _private prototype_ `FReply OnClickOverrideBlueprintButton();` — Handles click event for Open Behaviour Blueprint button
- L127 _private prototype_ `TSharedRef<SWidget> GetActionMenuContentWidget();` — Builds a menu containing the list of all possible Actions These are derived from the list of Exposed entities of the Remote Control Preset associated with us.
- L130 _private prototype_ `void CreateActionPanelWidgets();` — Check the validity of the panel widgets and if not valid will create them
- L133 _private prototype_ `bool AreActionPanelWidgetsValid() const;` — Return whether or not all panel widgets are valid
- L136 _private prototype_ `void OnAddActionClicked(TSharedPtr<FRemoteControlField> InRemoteControlField);` — Handles click event for Add Action button
- L139 _private prototype_ `void OnAddActionClicked();` — Handles click event for Add Action (PropertyId) button
- L142 _private prototype_ `void OnAddActionClicked(FName InFieldId);` — Handles click event for Add specific PropertyId Action buttons
- L145 _private prototype_ `FReply OnClickEmptyButton();` — Handles click event for Empty button; clear all Actions from the panel
- L148 _private prototype_ `FReply OnAddAllFields();` — Handles click event for Add All button; Adds all possible actions for the active Remote Control Preset
- L151 _private prototype_ `FReply OnAddAllSelectedFields();` — Handles click event for Add All Selected button; Adds all selected actions for the active Remote Control Preset
- L154 _private prototype_ `FReply OnSelectSource();` — Handles click event for Select Source button; Selects the actor/component in the scene whose properties are bound in this action
- L158 _private prototype_ `static TSharedRef<SBox> GetNoneSelectedWidget();` — Helper widget for behavior details.
- L160 _private prototype_ `void DuplicateAction(URCAction* InAction);`
- L162 _private prototype_ `void AddNewActionToList(URCAction* NewAction);`
- L165 _private member_ `TWeakPtr<FRCBehaviourModel> SelectedBehaviourItemWeakPtr;` — The parent Behaviour that this Action panel is associated with
- L168 _private member_ `TSharedPtr<SBox> WrappedBoxWidget;` — Parent Box for the entire widget
- L171 _private member_ `TSharedPtr<SRCLogicPanelListBase> ActionPanelList;` — Widget representing List of Actions
- L174 _private member_ `TSharedPtr<SRCBehaviourDetails> BehaviourDetailsWidget;` — Behaviour specific details widget
- L177 _private member_ `const FRCPanelStyle* RCPanelStyle = nullptr;` — Panel Style reference.
- L180 _private member_ `TSharedPtr<SRCMinorPanel> ActionDockPanel;` — Action Minor Panel
- L183 _private member_ `TSharedPtr<SComboButton> AddNewActionButton;` — ComboButton to add new action
- L186 _private member_ `TSharedPtr<SWidget> AddAllActionsButton;` — Add all actions button
- L189 _private member_ `TSharedPtr<SWidget> AddAllSelectedActionsButton;` — Add all selected actions button
- L192 _private member_ `TSharedPtr<SWidget> SelectSourceButton;` — Select source for action button
- L195 _private member_ `TSharedPtr<SRCMajorPanel> ActionsPanel;` — Action Major Panel
- L198 _private member_ `TSharedPtr<SRCMinorPanel> BehaviorDetailsPanel;` — Behavior Details Minor Panel

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/SRCActionPanelList.h` (Private)


#### class `SRCActionPanelList`  
`class SRCActionPanelList : public SRCLogicPanelListBase`  
_L50-619_
- inherits: `SRCLogicPanelListBase`
- L53 _public function_ `SLATE_BEGIN_ARGS(SRCActionPanelList<ActionType>)`
- L57 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRCActionPanel> InActionPanel, TSharedPtr<FRCBehaviourModel> InBehaviourItem)`
- L120 _public function_ `virtual ~SRCActionPanelList()`
- L131 _public function_ `void OnActionsListModified()`
- L137 _public function_ `virtual bool IsEmpty() const override` — Returns true if the underlying list is valid and empty.
- L143 _public function_ `virtual int32 Num() const override` — Returns number of items in the list.
- L149 _public function_ `virtual int32 NumSelectedLogicItems() const override` — The number of Controllers currently selected
- L155 _public function_ `virtual bool IsListFocused() const override` — Whether the Actions List View currently has focus.
- L161 _public function_ `virtual void DeleteSelectedPanelItems() override` — Deletes currently selected items from the list view
- L171 _public function_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() override` — Returns the UI items currently selected by the user (if any).
- L191 _public function_ `TSharedPtr<FRCActionModel> GetSelectedActionItem()` — The currently selected Action item
- L197 _public function_ `TSharedPtr<SRCActionPanel> GetActionPanel()` — Fetches the parent Action panel
- L203 _public function_ `TSharedPtr<FRCBehaviourModel> GetBehaviourItem()` — Fetches the Behaviour (UI model) associated with us
- L209 _public function_ `URCAction* AddAction(const FGuid& InRemoteControlFieldId)` — Adds an Action by Remote Control Field Guid
- L226 _public function_ `URCAction* AddAction(const FName InPropertyId)` — Adds a PropertyId action with the given PropertyId
- L235 _public function_ `virtual void AddNewLogicItem(UObject* InLogicItem) override`
- L242 _public function_ `void AddRowToList(URCAction* InAction)`
- L267 _public function_ `void RequestRefresh()`
- L273 _public function_ `virtual void AddSpecialContextMenuOptions(FMenuBuilder& MenuBuilder) override` — Allows Logic panels to add special functionality to the Context Menu based on context
- L281 _public function_ `void SelectSource_Execute() override`
- L308 _private function_ `TSharedRef<ITableRow> OnGenerateWidgetForList( TSharedPtr<ActionType> InItem, const TSharedRef<STableViewBase>& OwnerTable )` — OnGenerateRow delegate for the Actions List View
- L322 _private function_ `void OnActionAdded(URCAction* InAction)` — Responds to the selection of a newly created action. Resets UI state
- L330 _private function_ `void OnEmptyActions()` — Responds to the removal of all actions. Rests UI state
- L336 _private function_ `virtual void Reset() override` — Refreshes the list from the latest state of the data model
- L357 _private function_ `void Refresh()` — Refreshes the list
- L363 _private function_ `virtual void BroadcastOnItemRemoved() override` — Handles broadcasting of a successful remove item operation.
- L366 _private function_ `virtual URemoteControlPreset* GetPreset() override` — Fetches the Remote Control preset associated with the parent panel
- L377 _private function_ `FReply OnExposedFieldDrop(TSharedPtr<FDragDropOperation> DragDropOperation)` — Drag and drop event for creating an Action from an exposed field
- L483 _private function_ `bool OnAllowDrop(TSharedPtr<FDragDropOperation> DragDropOperation)` — Whether drag and drop is possible from the current exposed property to the Actions table
- L590 _private function_ `void OnSelectionChanged(TSharedPtr<ActionType> InItem, ESelectInfo::Type)` — OnSelectionChanged delegate for Actions List View
- L603 _private member_ `TSharedPtr<FRCActionModel> SelectedActionItem;` — The currently selected Action item
- L606 _private member_ `TWeakPtr<SRCActionPanel> ActionPanelWeakPtr;` — The parent Action Panel widget
- L609 _private member_ `TWeakPtr<FRCBehaviourModel> BehaviourItemWeakPtr;` — The Behaviour (UI model) associated with us
- L612 _private member_ `TArray<TSharedPtr<ActionType>> ActionItems;` — List of Actions (UI model) active in this widget
- L615 _private member_ `TSharedPtr<SListView<TSharedPtr<ActionType>>> ListView;` — List View widget for representing our Actions List
- L618 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.

#### Free symbols / members of external scopes

- L38 _macro_ `#define LOCTEXT_NAMESPACE "SRCActionPanelList"`
- L92 _function_ `.OnDropped_Lambda([this](const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent) { return SRCActionPanelList::OnExposedFieldDrop(InDragDropEvent.GetOperation()); }) .OnAllowDrop(this, &SRCActionPanelList::OnAllowDrop) .OnIsRecognized(this, &SRCActionPanelList::OnAllowDrop) [ ListView.ToSharedRef() ] ];` (scope `SRCActionPanelList::SLATE_END_ARGS`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/SRCBehaviourDetails.h` (Private)


#### class `SRCBehaviourDetails`  
`class SRCBehaviourDetails : public SCompoundWidget`  
_L16-61_
- inherits: `SCompoundWidget`
- desc: A custom widget dedicated to show the details of the selected behaviour.
- L19 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviourDetails)`
- L23 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<SRCActionPanel> InActionPanel, TSharedPtr<FRCBehaviourModel> InBehaviourItem);`
- L29 _public prototype_ `void SetIsBehaviourEnabled(const bool bIsEnabled) const;` — Set the Enabled state of our parent Behaviour
- L32 _public prototype_ `void SetNewBehavior(const TSharedPtr<FRCBehaviourModel>& InBehaviourItem);` — Set a new behavior for this Details widget
- L35 _public prototype_ `TSharedPtr<FRCBehaviourModel> GetCurrentBehavior() const;` — Get the current Behavior used for this details
- L39 _private prototype_ `void RefreshIsBehaviourEnabled(const bool bIsEnabled) const;` — Refreshes the UI widgets enabled state depending on whether the parent behaviour is currently enabled
- L42 _private prototype_ `void Refresh();` — Refresh the behaviour widgets
- L45 _private member_ `TWeakPtr<SRCActionPanel> ActionPanelWeakPtr;` — The parent Action panel UI widget holding this Header
- L48 _private member_ `TWeakPtr<FRCBehaviourModel> BehaviourItemWeakPtr;` — The active Behaviour (UI Model) associated with the Actions being shown
- L51 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L54 _private member_ `TSharedPtr<SBox> BehaviourDetailsBox;` — Behaviour Box containing the details widget
- L57 _private member_ `TSharedPtr<SWidget> BehaviourDetailsWidget;` — Behaviour specific details panel
- L60 _private member_ `TSharedPtr<STextBlock> BehaviourTitleWidget;` — Behaviour Title text widget

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Action/SRCVirtualPropertyWidget.h` (Private)


#### class `SRCVirtualPropertyWidget`  
`class SRCVirtualPropertyWidget : public SCompoundWidget`  
_L28-85_
- inherits: `SCompoundWidget`
- desc: ~ SRCVirtualPropertyWidget ~ Multi purpose widget for Virtual Properties covering both read-only and Edit usage scenarios 1) In Read-Only mode, the OnGenerateWidget delegate is used to build a view widget as required by the caller. 2) In Edit mode, a generic field widget is generated from the Virtual property Supported edit actions: 1) Double-click 2) Right-click -> Contet menu -> Edit Context menu support is automatically provided when this widget is set to the EditableVirtualPropertyWidget member of FRCActionModel.
- L31 _public typedef_ `using FOnGenerateWidget = typename TSlateDelegates<URCVirtualPropertySelfContainer*>::FOnGenerateWidget;`
- L33 _public function_ `SLATE_BEGIN_ARGS(SRCVirtualPropertyWidget) : _OnGenerateWidget()`
- L38 _public prototype_ `SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnExitingEditMode, OnExitingEditMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs, URCVirtualPropertySelfContainer* InVirtualProperty);`
- L48 _public prototype_ `void EnterEditMode();` — Activates Edit Mode, generates a generic field widget for the virtual property to facilitate user entry
- L51 _public prototype_ `void ExitEditMode();` — Exits Edit Mode, restores the original read-only widget view as defined by the caller (via OnGenerateWidget)
- L54 _public prototype_ `void AddEditContextMenuOption(FMenuBuilder& MenuBuilder);` — Automatically provides Right-click Edit support (invoked from FRCActionModel's GetContextMenuWidget function
- L58 _protected member_ `FOnGenerateWidget OnGenerateWidget;` — Delegate to be invoked when the list needs to generate a new widget from a data item.
- L62 _private prototype_ `FReply OnMouseDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);` — Double-click event for the border wrapping the Virtual Property widget. Provides Edit mode entry
- L66 _private prototype_ `void OnPropertyValueChanged();` — Property value change listener for the generic field widget. Used to exit edit mode. This is used in lieu of regular commit events as we don't have access to the generic field widget's internals
- L69 _private member_ `TWeakObjectPtr<URCVirtualPropertySelfContainer> VirtualPropertyWeakPtr;` — The Virtual Property which this widget represents
- L72 _private member_ `TSharedPtr<SBox> VirtualPropertyWidgetBox;` — Parent box encompassing read-only and edit modes.
- L75 _private member_ `bool bIsEditMode = false;` — Whether the virtual property is currently in edit mode
- L78 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The property generator used to build a generic value widget
- L81 _private member_ `TWeakPtr<IDetailTreeNode> DetailTreeNodeWeakPtr;` — Detail tree node used to create a generic value widget
- L84 _private member_ `FOnExitingEditMode OnExitingEditModeDelegate;` — Delegate executed when exiting edit mode if bound

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE(FOnExitingEditMode) class SRCVirtualPropertyWidget : public SCompoundWidget { public: using FOnGenerateWidget = typename TSlateDelegates<URCVirtualPropertySelfContainer*>::FOnGenerateWidget; SLATE_BEGIN_ARGS(SRCVirtualPropertyWidget) : _OnGenerateWidget() { } SLATE_EVENT(FOnGenerateWidget, OnGenerateWidget) SLATE_EVENT(FOnExitingEditMode, OnExitingEditMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs, URCVirtualPropertySelfContainer* InVirtualProperty); void EnterEditMode(); void ExitEditMode(); void AddEditContextMenuOption(FMenuBuilder& MenuBuilder);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/BaseLogicUI/RCLogicHelpers.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RCLogicHelpers` (scope `UE`)
- L16 _prototype_ `UBlueprint* CreateBlueprintWithDialog(UClass* InBlueprintParentClass, const UPackage* InSourcePackage, TSubclassOf<UBlueprint> InBlueprintClassType, TSubclassOf<UBlueprintGeneratedClass> InBlueprintGeneratedCClassType);` (scope `UE::RCLogicHelpers`) — Launches the Create Blueprint dialog for creating custom Behaviour blueprints
- L19 _prototype_ `bool OpenBlueprintEditor(UBlueprint* InBlueprint);` (scope `UE::RCLogicHelpers`) — Opens the Blueprint Editor for a given custom Behaviour blueprint

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/BaseLogicUI/RCLogicModeBase.h` (Private)


#### class `FRCLogicModeBase`  
`class FRCLogicModeBase : public TSharedFromThis<FRCLogicModeBase>`  
_L18-46_
- inherits: `TSharedFromThis<FRCLogicModeBase>`
- desc: ~ FRCLogicModeBase ~ Base UI model for representing a Logic item (Controllers / Behaviours / Actions) Provides a row widget that can be used in list views.
- L21 _public function_ `FRCLogicModeBase()`
- L22 _public prototype_ `FRCLogicModeBase(const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L24 _public prototype_ `virtual ~FRCLogicModeBase() = default;`
- L27 _public prototype_ `virtual FName GetModelType() const = 0;` — Returns a name to identify the type of logic model
- L32 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() const;` — Represents the widget to be rendered for associated UI Model. Implemented by child classes to supply the row widget for various panel lists
- L35 _public prototype_ `URemoteControlPreset* GetPreset() const;` — Returns the Remote Control Preset object associated with us
- L38 _public prototype_ `TSharedPtr<SRemoteControlPanel> GetRemoteControlPanel() const;` — Returns the Remote Control Preset object associated with us
- L41 _public prototype_ `virtual int32 RemoveModel() = 0;` — Removes this model from the owning UI panel. Returns the number of items removed.
- L45 _protected member_ `TWeakPtr<SRemoteControlPanel> PanelWeakPtr;` — The parent Remote Control Panel widget

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/BaseLogicUI/SRCLogicPanelBase.h` (Private)


#### class `SRCLogicPanelBase`  
`class SRCLogicPanelBase : public SCompoundWidget`  
_L20-84_
- inherits: `SCompoundWidget`
- desc: ~ SRCLogicPanelBase ~ Base UI Widget for Logic Panels (Controllers / Behaviours / Actions). Provides access to parent Remote Control Preset object and common Delete Panel Item functionality
- L23 _public function_ `SLATE_BEGIN_ARGS(SRCLogicPanelBase)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRemoteControlPanel>& InPanel);`
- L33 _public prototype_ `virtual URemoteControlPreset* GetPreset() const;` — Returns the Remote Control Preset object associated with us
- L37 _public prototype_ `virtual TSharedPtr<SRemoteControlPanel> GetRemoteControlPanel() const;` — Returns the parent Remote Control Panel widget, This is the main container holding all the Remote Control panels including Logic and Exposed Properties
- L40 _public prototype_ `virtual void DeleteSelectedPanelItems() = 0;` — "Delete Items" UI command implementation for panels
- L43 _public function_ `virtual bool CanDuplicateItems() const` — Whether this panel can Duplicate Items
- L46 _public function_ `virtual void DuplicateSelectedPanelItems()` — "Duplicate Items" UI command implementation for action panels
- L49 _public function_ `virtual bool CanCopyItems() const` — Whether this panel can Copy Items
- L52 _public function_ `virtual void CopySelectedPanelItems()` — "Copy Items" UI command implementation for panels
- L55 _public function_ `virtual void PasteItemsFromClipboard()` — "Paste Items" UI command implementation for panels
- L58 _public function_ `virtual bool CanPasteClipboardItems(const TArrayView<const TObjectPtr<UObject>> InLogicClipboardItems) const` — Whether a given clipboard items can be successfully pasted into this panel
- L61 _public function_ `virtual void UpdateValue()` — "Update Value" UI command implementation for panels
- L64 _public function_ `virtual bool CanUpdateValue() const` — Whether this panel can call the UpdateValue command
- L67 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() const = 0;` — Returns the UI items currently selected by the user (if any). To be implemented per child panel
- L70 _public function_ `virtual FText GetPasteItemMenuEntrySuffix()` — Provides an item suffix for the Paste context menu to provide users with useful context on the nature of the item being pasted
- L73 _public prototype_ `virtual FReply RequestDeleteSelectedItem() = 0;` — Warns user before deleting a selected panel item.
- L76 _public prototype_ `virtual FReply RequestDeleteAllItems() = 0;` — Warns user before deleting all items in a panel.
- L80 _protected member_ `TSharedPtr<class SRCLogicPanelListBase> PanelList;` — Widget representing List of Controllers/Behaviours/Actions
- L83 _protected member_ `TWeakPtr<SRemoteControlPanel> PanelWeakPtr;` — The parent Remote Control Panel widget

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/BaseLogicUI/SRCLogicPanelListBase.h` (Private)


#### class `SRCLogicPanelListBase`  
`class SRCLogicPanelListBase : public SCompoundWidget`  
_L25-146_
- inherits: `SCompoundWidget`
- desc: ~ SRCLogicPanelListBase ~ Base UI Widget for Lists in Logic Panels. Can represent Controllers / Behaviours / Actions, etc.
- L28 _public function_ `SLATE_BEGIN_ARGS(SRCLogicPanelListBase)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRCLogicPanelBase>& InLogicParentPanel, const TSharedRef<SRemoteControlPanel>& InPanel);`
- L38 _public prototype_ `virtual bool IsEmpty() const = 0;` — Returns true if the underlying list is valid and empty.
- L41 _public prototype_ `virtual int32 Num() const = 0;` — Returns number of items in the list.
- L44 _public prototype_ `virtual int32 NumSelectedLogicItems() const = 0;` — The number of items currently selected in a Logic list panel
- L47 _public prototype_ `virtual bool IsListFocused() const = 0;` — Whether the List View currently has focus.
- L50 _public prototype_ `virtual void DeleteSelectedPanelItems() = 0;` — Deletes currently selected items from the list view
- L53 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() = 0;` — Returns the UI items currently selected by the user (if any). To be implemented per child panel
- L56 _public function_ `virtual void AddNewLogicItem(UObject* InLogicItem)` — Provides a common entry point for adding Logic related data objects (UObjects) to their respective panels
- L59 _public prototype_ `TSharedPtr<SWidget> GetContextMenuWidget();` — Builds the right-click context menu populated with generic actions (based on UI Commands)
- L62 _public function_ `virtual void AddSpecialContextMenuOptions(FMenuBuilder& MenuBuilder)` — Allows Logic panels to add special functionality to the Context Menu based on context
- L64 _public function_ `TSharedPtr<SRemoteControlPanel> GetRemoteControlPanel()`
- L69 _public function_ `virtual void SelectSource_Execute()`
- L74 _private prototype_ `virtual void Reset() = 0;` — Refreshes the list from the latest state of the model
- L78 _private prototype_ `virtual void BroadcastOnItemRemoved() = 0;` — Handles broadcasting of a successful remove item operation. This is handled uniquely by each type of child list widget
- L81 _private prototype_ `virtual URemoteControlPreset* GetPreset() = 0;` — Fetches the Remote Control preset associated with the parent panel
- L84 _private prototype_ `virtual int32 RemoveModel(const TSharedPtr<FRCLogicModeBase> InModel);` — Removes the given UI model item from the list of UI models for this panel list
- L87 _private prototype_ `bool CanDeleteAllItems() const;` — Returns true when we can delete all items.
- L90 _private prototype_ `void RequestDeleteAllItems();` — Requests the parent logic panel to delete all items in this list
- L93 _protected member_ `TWeakPtr<SWidget> ContextMenuWidgetCached;`
- L101 _protected function_ `template<class T> bool DeleteItemsFromLogicPanel(TArray<TSharedPtr<T>>& ItemsSource, const TArray<TSharedPtr<T>>& SelectedItems)` — Helper function for handling common Delete Item functionality across all child panels (Actions/Behaviours/Controllers) Currently invoked from each Panel List child class with appropriate template class @return true if any items were deleted
- L137 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — Command list to build context menus for
- L140 _protected member_ `TWeakPtr<SRemoteControlPanel> RemoteControlPanelWeakPtr;` — The parent Remote Control Panel widget
- L143 _protected member_ `TWeakPtr<SRCLogicPanelBase> LogicPanelWeakPtr;` — The parent Logic Panel
- L145 _protected prototype_ `virtual void UpdateEntityUsage();`

#### Free symbols / members of external scopes

- L116 _function_ `` (scope `SRCLogicPanelListBase::DeleteItemsFromLogicPanel`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Bind/RCBehaviourBindModel.h` (Private)


#### class `FRCBehaviourBindModel`  
`class FRCBehaviourBindModel : public FRCBehaviourModel`  
_L18-41_
- inherits: `FRCBehaviourModel`
- desc: ~ FRCBehaviourBindModel ~ UI model for Bind Behaviour
- L21 _public prototype_ `FRCBehaviourBindModel(URCBehaviourBind* BindBehaviour, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L24 _public prototype_ `virtual bool HasBehaviourDetailsWidget() override;` — Returns true if this behaviour have a details widget or false if not
- L27 _public prototype_ `virtual TSharedRef<SWidget> GetBehaviourDetailsWidget() override;` — Builds a Behaviour specific details widget for Bind Behaviour
- L30 _public prototype_ `virtual TSharedPtr<SRCLogicPanelListBase> GetActionsListWidget(TSharedRef<SRCActionPanel> InActionPanel);` — The Actions List widget to be used for Bind Behaviour
- L33 _public prototype_ `URCBehaviourBind* GetBindBehaviour() const;` — Fetches the Bind Behaviour UObject model
- L37 _private member_ `TWeakObjectPtr<URCBehaviourBind> BindBehaviourWeakPtr;` — The Bind Behaviour (Data model) associated with us
- L40 _private member_ `TSharedPtr<SRCBehaviourBind> BehaviourDetailsWidget;` — Behaviour Details Widget for Bind Behaviour

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Bind/SRCBehaviourBind.h` (Private)


#### class `SRCBehaviourBind`  
`class SRCBehaviourBind : public SCompoundWidget`  
_L20-42_
- inherits: `SCompoundWidget`
- desc: ~ SRCBehaviourConditional ~ Behaviour specific details panel for Bind Behaviour Contains a checkbox which specifies whether string to numeric (and vice versa) conversions are desired
- L23 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviourBind)`
- L27 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FRCBehaviourBindModel> InBehaviourItem);`
- L35 _private prototype_ `void OnAllowNumericCheckboxChanged(ECheckBoxState NewState);` — Called when the checkbox state changes for "Allow Numeric Input As Strings"
- L38 _private member_ `TWeakPtr<FRCBehaviourBindModel> BindBehaviourItemWeakPtr;` — The Behaviour (UI model) associated with us
- L41 _private member_ `TSharedPtr<SCheckBox> CheckboxAllowNumericInput;` — Checkbox for "Allow Numeric Input as Strings"

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Conditional/RCBehaviourConditionalModel.h` (Private)


#### class `FRCBehaviourConditionalModel`  
`class FRCBehaviourConditionalModel : public FRCBehaviourModel`  
_L22-71_
- inherits: `FRCBehaviourModel`
- desc: ~ FRCBehaviourConditionalModel ~ UI model for Conditional Behaviour
- L25 _public prototype_ `FRCBehaviourConditionalModel(URCBehaviourConditional* IsEqualBehaviour);`
- L28 _public prototype_ `URCBehaviourConditional* GetConditionalBehaviour();` — Fetches the Conditional Behaviour UObject
- L31 _public prototype_ `virtual URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField);` — Add a Logic Action using a remote control field as input
- L34 _public prototype_ `virtual bool HasBehaviourDetailsWidget() override;` — Returns true if this behaviour have a details widget or false if not
- L37 _public prototype_ `virtual TSharedRef<SWidget> GetBehaviourDetailsWidget() override;` — Builds a Behaviour specific details widget enabling the user to define Conditions
- L40 _public prototype_ `TSharedRef<SWidget> GetComparandFieldWidget() const;` — Builds the Comparand input field's widget which enables the user to enter values to compare with
- L43 _public prototype_ `void SetSelectedConditionType(const ERCBehaviourConditionType InCondition);` — Updates the condition type selected by the user for Conditional Behaviour
- L46 _public prototype_ `virtual TSharedPtr<SRCLogicPanelListBase> GetActionsListWidget(TSharedRef<SRCActionPanel> InActionPanel);` — The Actions List widget to be used for Conditional Behaviour
- L49 _public member_ `ERCBehaviourConditionType Condition;` — The condition type currently selected by the user
- L53 _protected prototype_ `virtual void OnActionAdded(URCAction* Action) override;` — Invoked by parent class after an action has been added from UI
- L58 _private prototype_ `void CreateComparandInputField();` — Builds a generic value widget of the Controller's type This is used to store the Comparand's value as entered by the user
- L61 _private member_ `TWeakObjectPtr<URCBehaviourConditional> ConditionalBehaviourWeakPtr;` — The Conditional Behaviour (Data model) associated with us
- L64 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The row generator used to build a generic Value Widget
- L67 _private member_ `TWeakPtr<IDetailTreeNode> DetailTreeNodeWeakPtr;` — Used to create a generic value widget for comparison based on the active Controller's type
- L70 _private member_ `TSharedPtr<SRCBehaviourConditional> BehaviourDetailsWidget;` — Behaviour Details Widget (Conditions Widget in the case of this Behaviour)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Conditional/SRCBehaviourConditional.h` (Private)


#### class `SRCBehaviourConditional`  
`class SRCBehaviourConditional : public SCompoundWidget`  
_L25-63_
- inherits: `SCompoundWidget`
- desc: ~ SRCBehaviourConditional ~ Behaviour specific details panel for Conditional Behaviour Provides users with the ability to definite Conditions on a per action basis Contains a Conditions list (for choosing a Condition) and a Comparand input field (for specifying the value with which to compare, per condition)
- L28 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviourConditional)`
- L32 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FRCBehaviourConditionalModel> InBehaviourItem);`
- L40 _public prototype_ `void RefreshPropertyWidget();` — Refreshes the Comparand input field. This needs to be performed each time the user creates a new Action, because the previous Comparand field has been consumed and so we create a new virtual property Comparand with whose memory the UI widget needs to be rebound.
- L44 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForConditionsList(TSharedPtr<ERCBehaviourConditionType> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — OnGenerateRow delegate for the Conditions List
- L47 _private prototype_ `void OnConditionsListSelectionChanged(TSharedPtr<ERCBehaviourConditionType> InItem, ESelectInfo::Type);` — OnSelectionChanged delegate for the Conditions List
- L50 _private member_ `TArray<TSharedPtr<ERCBehaviourConditionType>> Conditions;` — List of possible Condition Types
- L53 _private member_ `TWeakPtr<FRCBehaviourConditionalModel> ConditionalBehaviourItemWeakPtr;` — The Behaviour (UI model) associated with us
- L56 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L59 _private member_ `TSharedPtr <SListView<TSharedPtr<ERCBehaviourConditionType>>> ListViewConditions;` — Conditions List View widget - Enables the user to pick a Condition Type per Condition
- L62 _private member_ `TSharedPtr<SBox> ComparandFieldBoxWidget;` — Parent Box for the Comparand input field (which enables us to refresh it whenever required)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Path/RCBehaviorSetAssetByPathModelNew.h` (Private)


#### class `FRCSetAssetByPathBehaviorModelNew`  
`class FRCSetAssetByPathBehaviorModelNew : public FRCBehaviourModel, public FNotifyHook`  
_L30-106_
- inherits: `FRCBehaviourModel,FNotifyHook`
- desc: ~ FRCSetAssetByPathBehaviorModelNew ~ Child Behaviour class representing the "Set Asset By Path" Behavior's UI model. Generates several Widgets where users can build a Root Path using strings or controller values. This is assigned as a loaded asset to exposed properties defined by actions actions.
- L33 _public prototype_ `explicit FRCSetAssetByPathBehaviorModelNew(URCSetAssetByPathBehaviorNew* InSetAssetByPathBehavior, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L35 _public prototype_ `void Initialize();`
- L38 _public prototype_ `virtual bool HasBehaviourDetailsWidget() override;` — Returns true if this behavior have a details widget or false if not
- L41 _public prototype_ `virtual TSharedRef<SWidget> GetBehaviourDetailsWidget() override;` — Builds a Behavior specific widget as required for the Set Asset By Path Behavior
- L48 _public prototype_ `TSharedRef<SWidget> GetPropertyWidget();` — Builds the Property Details Widget, including a generic expendable Array Widget and further two Text Widgets representing elements needed for the Path Behavior. All of them store the user input and use them to perform the SetAssetByPath Behavior.
- L51 _public prototype_ `virtual void NotifyControllerValueChanged(TSharedPtr<FRCControllerModel> InControllerModel) override;` — Called when a controller value changed
- L53 _public prototype_ `virtual TSharedPtr<SRCLogicPanelListBase> GetActionsListWidget(TSharedRef<SRCActionPanel> InActionPanel) override;`
- L56 _public prototype_ `void RefreshPreview() const;` — Refresh the PreviewPath
- L59 _public prototype_ `void RefreshValidity();` — Refresh the validity state of the path elements.
- L61 _public prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, class FEditPropertyChain* InPropertyThatChanged) override;`
- L63 _public prototype_ `void ReorderElementItems(int32 InDroppedOnIndex, EItemDropZone InDropZone, int32 InDroppedIndex);`
- L67 _private prototype_ `void OnAssetPathFinishedChangingProperties(const FPropertyChangedEvent& InEvent);` — Callback called when the AssetPath properties change to either refresh or reconstruct it updating the path values
- L70 _private prototype_ `void RegenerateWeakPtrInternal();` — Reconstruct the PropertyRow Generator
- L73 _private prototype_ `void RefreshPathAndPreview();` — Regenerates and creates a new PathArray Widget if changed
- L76 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FRCPathBehaviorElementRow> InItem, const TSharedRef<STableViewBase>& InOwnerTable);` — Creates a row for the elements view.
- L78 _private prototype_ `void RefreshValidity_Internal(TConstArrayView<FRCSetAssetByPathBehaviorNewPathElement> InPathStack);`
- L80 _private prototype_ `void RefreshValidity_External(TConstArrayView<FRCSetAssetByPathBehaviorNewPathElement> InPathStack);`
- L84 _private member_ `TWeakObjectPtr<URCSetAssetByPathBehaviorNew> SetAssetByPathBehaviorWeakPtr;` — The SetAssetByPath Behaviour associated with this Model
- L87 _private member_ `TSharedPtr<SBox> PathArrayWidget;` — Pointer to the Widget holding the PathArray created for this behavior
- L90 _private member_ `TSharedPtr<SListView<TSharedPtr<FRCPathBehaviorElementRow>>> ElementsView;` — List view containing the path elements.
- L93 _private member_ `TArray<TSharedPtr<FRCPathBehaviorElementRow>> ElementItems;` — Data for each row in the list view.
- L96 _private member_ `TSharedPtr<SHorizontalBox> PreviewPathWidget;` — Pointer to the Preview Text Widget for the Path
- L99 _private member_ `TSharedPtr<SImage> ValidationImage;` — Image showing whether the path is valid or not.
- L102 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGeneratorArray;` — The row generator used to build the generic array value widget for the Path Array
- L105 _private member_ `TArray<TSharedPtr<IDetailTreeNode>> DetailTreeNodeWeakPtrArray;` — Used to create a generic Value Widget based on the Paths Available

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Path/RCBehaviourSetAssetByPathModel.h` (Private)


#### class `FRCSetAssetByPathBehaviourModel`  
`class FRCSetAssetByPathBehaviourModel : public FRCBehaviourModel`  
_L24-91_
- inherits: `FRCBehaviourModel`
- desc: ~ FRCSetAssetByPathModel ~ Child Behaviour class representing the "Set Asset By Path" Behaviour's UI model. Generates several Widgets where users can enter the RootPath, Target Property, and Default Property as FStrings. The values are then put together, getting a path towards a possible object.
- L27 _public prototype_ `FRCSetAssetByPathBehaviourModel(URCSetAssetByPathBehaviour* SetAssetByPathBehaviour, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L30 _public prototype_ `virtual bool HasBehaviourDetailsWidget() override;` — Returns true if this behaviour have a details widget or false if not
- L33 _public prototype_ `virtual TSharedRef<SWidget> GetBehaviourDetailsWidget() override;` — Builds a Behaviour specific widget as required for the Set Asset By Path Behaviour
- L40 _public prototype_ `TSharedRef<SWidget> GetPropertyWidget();` — Builds the Property Details Widget, including a generic expendable Array Widget and further two Text Widgets representing elements needed for the Path Behaviour. All of them store the user input and use them to perform the SetAssetByPath Behaviour.
- L43 _public prototype_ `TSharedRef<SWidget> GetSelectorWidget(TWeakPtr<const FRemoteControlEntity> InInitialSelected);` — Builds the Combobox which the Behaviour will use to select and and apply it's Asset Setting on.
- L46 _public prototype_ `virtual void NotifyControllerValueChanged(TSharedPtr<FRCControllerModel> InControllerModel) override;` — Called when a controller value changed
- L49 _public prototype_ `void RefreshPreview() const;` — Refresh the PreviewPath
- L53 _protected prototype_ `FText GetSelectedEntityText() const;` — Gets the currently selected Entities Name, or a failure Text in case it fails.
- L57 _private prototype_ `void OnAssetPathFinishedChangingProperties(const FPropertyChangedEvent& InEvent);` — Callback called when the AssetPath properties change to either refresh or reconstruct it updating the path values
- L60 _private prototype_ `void RegenerateWeakPtrInternal();` — Reconstruct the PropertyRow Generator
- L63 _private prototype_ `void RefreshPathAndPreview();` — Regenerates and creates a new PathArray Widget if changed
- L66 _private member_ `TWeakObjectPtr<URCSetAssetByPathBehaviour> SetAssetByPathBehaviourWeakPtr;` — The SetAssetByPath Behaviour associated with this Model
- L69 _private member_ `TSharedPtr<SBox> PathArrayWidget;` — Pointer to the Widget holding the PathArray created for this behaviour
- L72 _private member_ `TSharedPtr<STextBlock> PreviewPathWidget;` — Pointer to the Preview Text Widget for the Path
- L75 _private member_ `TSharedPtr<SWidget> SelectorBox;` — POinter to the ComboBox Widget
- L78 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The row generator used to build the generic value widgets
- L81 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGeneratorArray;` — The row generator used to build the generic array value widget for the Path Array
- L84 _private member_ `TArray<TSharedPtr<IDetailTreeNode>> DetailTreeNodeWeakPtr;` — Used to create a generic Value Widget based on the active Controller's type
- L87 _private member_ `TArray<TSharedPtr<IDetailTreeNode>> DetailTreeNodeWeakPtrArray;` — Used to create a generic Value Widget based on the Paths Available
- L90 _private member_ `TArray<TWeakPtr<const FRemoteControlEntity>> ExposedEntities;` — Array of Exposed Entities from the Preset to help create a Widget to choose the Target

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace SetAssetByPathModelHelper`
- L13 _variable_ `const FString InputToken = FString(TEXT("*INP` (scope `SetAssetByPathModelHelper`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Path/SRCBehaviorSetAssetByPathNew.h` (Private)


#### class `SRCBehaviorSetAssetByPathNew`  
`class SRCBehaviorSetAssetByPathNew : public SCompoundWidget`  
_L15-38_
- inherits: `SCompoundWidget`
- L18 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviorSetAssetByPathNew)`
- L20 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FRCSetAssetByPathBehaviorModelNew> InBehaviourItem);`
- L27 _private prototype_ `ECheckBoxState GetInternalExternalSwitchState(bool bInIsInternal) const;` — Determines the state of the internal/external buttons.
- L30 _private prototype_ `void OnInternalExternalSwitchStateChanged(ECheckBoxState InState, bool bInIsInternal);` — Called when the Internal/External button are pressed
- L34 _private member_ `TWeakPtr<FRCSetAssetByPathBehaviorModelNew> SetAssetByPathWeakPtr;` — The Behaviour (UI model) associated with us
- L37 _private member_ `TWeakObjectPtr<URCSetAssetByPathBehaviorNew> PathBehaviour;` — The PathBehaviour associated with us

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Path/SRCBehaviorSetAssetByPathNewElementRow.h` (Private)


#### enum `ERCPathBehaviorElementValidty`  
`enum ERCPathBehaviorElementValidty`  
_L16-26_
- L18 _public enumerator_ `ValidPath`
- L19 _public enumerator_ `ValidAsset`
- L20 _public enumerator_ `InvalidPath`
- L21 _public enumerator_ `InvalidAsset`
- L22 _public enumerator_ `InvalidController`
- L23 _public enumerator_ `EmptyControllerValue`
- L24 _public enumerator_ `Unknown`
- L25 _public enumerator_ `Unchecked`

#### struct `FRCPathBehaviorElementRow`  
`struct FRCPathBehaviorElementRow`  
_L28-33_
- L30 _public member_ `int32 Index;`
- L31 _public member_ `TSharedRef<SWidget> Widget;`
- L32 _public member_ `ERCPathBehaviorElementValidty Validity = ERCPathBehaviorElementValidty::Unchecked;`

#### class `SRCBehaviorSetAssetByPathNewElementRow`  
`class SRCBehaviorSetAssetByPathNewElementRow : public STableRow<RCBehaviorSetAssetByPathNewElementListItem>`  
_L35-64_
- inherits: `STableRow<RCBehaviorSetAssetByPathNewElementListItem>`
- L37 _private typedef_ `using FSuperRowType = STableRow<RCBehaviorSetAssetByPathNewElementListItem>;`
- L40 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviorSetAssetByPathNewElementRow)`
- L42 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<FRCSetAssetByPathBehaviorModelNew> InSetAssetByPathBehaviorModelNew, RCBehaviorSetAssetByPathNewElementListItem InElementItem);`
- L47 _public prototype_ `int32 GetElementIndex() const;`
- L51 _private prototype_ `TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, RCBehaviorSetAssetByPathNewElementListItem InItem);` — Called to validate whether a drag drop event is accepted for a behavior item row
- L54 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, RCBehaviorSetAssetByPathNewElementListItem InItem);` — Called when a drop happens on this behavior item row
- L56 _private prototype_ `FReply OnRowDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L58 _private prototype_ `const FSlateBrush* GetValidityImage() const;`
- L60 _private prototype_ `FText GetValidityToolTip() const;`
- L62 _private member_ `TWeakPtr<FRCSetAssetByPathBehaviorModelNew> SetAssetByPathBehaviorModelNewWeak;`
- L63 _private member_ `RCBehaviorSetAssetByPathNewElementListItem ElementItem;`

#### Free symbols / members of external scopes

- L14 _typedef_ `using RCBehaviorSetAssetByPathNewElementListItem = TSharedPtr<FRCPathBehaviorElementRow>;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/Path/SRCBehaviourSetAssetByPath.h` (Private)


#### class `SRCBehaviourSetAssetByPath`  
`class SRCBehaviourSetAssetByPath : public SCompoundWidget`  
_L14-51_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviourSetAssetByPath)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FRCSetAssetByPathBehaviourModel> InBehaviourItem);`
- L28 _private prototype_ `void OnInternalExternalSwitchWidgetPressed(bool bInIsInternal) const;` — Called when the Internal/External button are pressed
- L31 _private prototype_ `FSlateColor GetExternalWidgetColor() const;` — Return the color of the External widget
- L34 _private prototype_ `FSlateColor GetInternalWidgetColor() const;` — Return the color of the Internal widget
- L37 _private prototype_ `EVisibility GetInternalExternalVisibility() const;` — Return the visibility of the InternalExternal widget
- L40 _private prototype_ `FSlateColor GetSelectedClassWidgetColor(UClass* InClass) const;` — Return the color of the SelectedClass widget
- L43 _private prototype_ `void OnSelectedClassWidgetPressed(UClass* InClass) const;` — Called when the SelectedClass buttons are pressed
- L47 _private member_ `TWeakPtr<const FRCSetAssetByPathBehaviourModel> SetAssetByPathWeakPtr;` — The Behaviour (UI model) associated with us
- L50 _private member_ `TWeakObjectPtr<URCSetAssetByPathBehaviour> PathBehaviour;` — The PathBehaviour associated with us

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/RangeMap/RCBehaviourRangeMapModel.h` (Private)


#### class `FRCRangeMapBehaviourModel`  
`class FRCRangeMapBehaviourModel : public FRCBehaviourModel`  
_L19-57_
- inherits: `FRCBehaviourModel`
- desc: ~ FRCRangeMapBehaviourModel ~ Child Behaviour class representing the "Range Mapping" Behaviour's UI model Generates a Property Widget where users can enter the Max, Min, Threshhold, and Step Values. The values of them are used for the interaction implementation of the properties it affects..
- L22 _public prototype_ `FRCRangeMapBehaviourModel(URCRangeMapBehaviour* RangeMapBehaviour);`
- L25 _public prototype_ `virtual bool HasBehaviourDetailsWidget() override;` — Returns true if this behaviour have a details widget or false if not
- L28 _public prototype_ `virtual TSharedRef<SWidget> GetBehaviourDetailsWidget() override;` — Builds a Behaviour specific widget as required for Range Mapping behaviour
- L32 _public prototype_ `TSharedRef<SWidget> GetPropertyWidget() const;` — Builds a generic Value Widget of the Controller's type Use to store user input for performing the Range Mapping Behaviour Interactions
- L35 _public prototype_ `virtual URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField) override;` — Add a Logic Action using a remote control field as input
- L38 _public prototype_ `virtual TSharedPtr<SRCLogicPanelListBase> GetActionsListWidget(TSharedRef<SRCActionPanel> InActionPanel) override;` — The Actions List Widget used in the RangeMap Behaviour
- L42 _protected prototype_ `virtual void OnActionAdded(URCAction* Action) override;` — Invoked by parent class after an action has been added from UI
- L46 _private member_ `TWeakObjectPtr<URCRangeMapBehaviour> RangeMapBehaviourWeakPtr;` — The Range Mapping Behaviour (Data model) associated with us
- L49 _private member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The row generator used to build a generic Value Widget
- L52 _private member_ `TArray<TWeakPtr<IDetailTreeNode>> DetailTreeNodeWeakPtrArray;` — Used to create generic Value Widgets for lerping control of values
- L56 _private prototype_ `TSharedRef<SWidget> CreateMinMaxWidget(TSharedPtr<IDetailTreeNode> MinInputDetailTree, TSharedPtr<IDetailTreeNode> MaxInputDetailTree) const;` — Creates the horizontal box containing box the Minimum and Maximum Range Widgets

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/Builtin/RangeMap/SRCBehaviourRangeMap.h` (Private)


#### class `SRCBehaviourRangeMap`  
`class SRCBehaviourRangeMap : public SCompoundWidget`  
_L17-30_
- inherits: `SCompoundWidget`
- desc: ~ SRCBehaviourRangeMap Behaviour specific details panel for Range Mapping Behaviour. Contains Input Panels which will be used to calculate and work with in the Behaviour itself.
- L20 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviourRangeMap)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<const FRCRangeMapBehaviourModel> InBehaviourItem);`
- L29 _private member_ `TWeakPtr<const FRCRangeMapBehaviourModel> RangeMapBehaviourItemWeakPtr;` — The Behaviour (UI Model) associated with this.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/RCBehaviourModel.h` (Private)


#### class `FRCBehaviourModel`  
`class FRCBehaviourModel : public FRCLogicModeBase`  
_L22-98_
- inherits: `FRCLogicModeBase`
- desc: ~ FRCBehaviourModel ~ UI model for representing a Behaviour Generates a row widget with Behaviour related metadata
- L25 _public member_ `static const FLazyName BehaviorModelName;`
- L27 _public prototype_ `FRCBehaviourModel(URCBehaviour* InBehaviour, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel = nullptr);`
- L29 _public function_ `virtual FName GetModelType() const override`
- L34 _public prototype_ `virtual int32 RemoveModel() override;`
- L37 _public prototype_ `virtual URCAction* AddAction();` — Add a Logic Action using as an identity action.
- L40 _public prototype_ `virtual URCAction* AddAction(FName InFieldId);` — Add a Logic Action using as an identity action.
- L43 _public prototype_ `virtual URCAction* AddAction(const TSharedRef<const FRemoteControlField> InRemoteControlField);` — Add a Logic Action using a remote control field as input.
- L48 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() const override;` — The widget to be rendered for this Property in the Behaviour panel Currently displays Behaviour Name metadata in the Behaviours Panel List
- L51 _public prototype_ `virtual bool HasBehaviourDetailsWidget();` — Returns true if this behaviour have a details widget or false if not.
- L54 _public prototype_ `virtual TSharedRef<SWidget> GetBehaviourDetailsWidget();` — Builds a Behaviour specific widget that child Behaviour classes can implement as required.
- L57 _public prototype_ `URCBehaviour* GetBehaviour() const;` — Returns the Behaviour (Data model) associated with us.
- L60 _public prototype_ `void OnOverrideBlueprint() const;` — Handling for user action to override this behaviour via new Blueprint class.
- L63 _public prototype_ `bool IsBehaviourEnabled() const;` — Whether the underlying Behaviour is currently enabled.
- L66 _public prototype_ `void SetIsBehaviourEnabled(const bool bIsEnabled);` — Set the Enabled state of our underlying Behaviour.
- L69 _public prototype_ `void RefreshIsBehaviourEnabled(const bool bIsEnabled);` — Refreshes the UI widgets enabled state depending on whether the parent behaviour is currently enabled.
- L74 _public prototype_ `virtual TSharedPtr<SRCLogicPanelListBase> GetActionsListWidget(TSharedRef<SRCActionPanel> InActionPanel);` — The Actions List widget to be used for this Behaviour. The default actions table is used if a behaviour doesn't specify it.
- L77 _public prototype_ `bool SupportPropertyId() const;` — Whether or not the behaviour support PropertyId action.
- L80 _public function_ `virtual void NotifyControllerValueChanged(TSharedPtr<class FRCControllerModel> InControllerModel)` — Called when a controller value changed
- L84 _protected function_ `virtual void OnActionAdded(URCAction* Action)` — Invoked after an action has been added for this Behaviour in the actions panel.
- L88 _private member_ `TWeakObjectPtr<URCBehaviour> BehaviourWeakPtr;` — The Behaviour (Data model) associated with us.
- L91 _private member_ `TSharedPtr<STextBlock> BehaviourTitleText;` — Text block widget for representing the Behaviour's title.
- L94 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L97 _private member_ `bool bDetailsEditableBehavior = false;` — Determines if the behavior is an object editable in details view

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/SRCBehaviorPanelRow.h` (Private)


#### class `SRCBehaviorPanelRow`  
`class SRCBehaviorPanelRow : public STableRow<FRCBehaviorPanelListItem>`  
_L15-47_
- inherits: `STableRow<FRCBehaviorPanelListItem>`
- L17 _private typedef_ `using FSuperRowType = STableRow<FRCBehaviorPanelListItem>;`
- L20 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviorPanelRow)`
- L22 _public prototype_ `SLATE_STYLE_ARGUMENT(FTableRowStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<SRCBehaviourPanelList> InBehaviorPanelList, FRCBehaviorPanelListItem InBehaviorItem);`
- L28 _public prototype_ `FRCBehaviorPanelListItem GetBehavior() const;`
- L32 _private prototype_ `TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FRCBehaviorPanelListItem InItem);` — Called to validate whether a drag drop event is accepted for a behavior item row
- L35 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FRCBehaviorPanelListItem InItem);` — Called when a drop happens on this behavior item row
- L37 _private prototype_ `FReply OnRowDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L40 _private prototype_ `ECheckBoxState IsBehaviourChecked() const;` — Return whether or not the given behaviour is checked
- L43 _private prototype_ `void OnToggleEnableBehaviour(ECheckBoxState State);` — Executed when toggling the behaviour state
- L45 _private member_ `TWeakPtr<SRCBehaviourPanelList> BehaviorPanelListWeak;`
- L46 _private member_ `FRCBehaviorPanelListItem BehaviorItem;`

#### Free symbols / members of external scopes

- L13 _typedef_ `using FRCBehaviorPanelListItem = TSharedPtr<FRCBehaviourModel>;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/SRCBehaviourPanel.h` (Private)


#### class `SRCBehaviourPanel`  
`class SRCBehaviourPanel : public SRCLogicPanelBase`  
_L23-125_
- inherits: `SRCLogicPanelBase`
- desc: ~ SRCBehaviourPanel ~ UI Widget for Behaviour Panel. Contains a header (Add/Remove/Empty) and List of Behaviours
- L26 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviourPanel)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRemoteControlPanel>& InPanel);`
- L36 _public prototype_ `bool IsListFocused() const;` — Whether the Behaviour list widget currently has focus. Used for Delete Item UI command
- L39 _public prototype_ `virtual void DeleteSelectedPanelItems() override;` — Delete Items UI command implementation for this panel
- L42 _public prototype_ `virtual void DuplicateSelectedPanelItems() override;` — "Duplicate Items" UI command implementation for Behaviour panel
- L45 _public prototype_ `virtual void CopySelectedPanelItems() override;` — "Copy Items" UI command implementation for Behaviour panel
- L48 _public prototype_ `virtual void PasteItemsFromClipboard() override;` — "Paste Items" UI command implementation for Behaviour panel
- L51 _public prototype_ `virtual bool CanPasteClipboardItems(const TArrayView<const TObjectPtr<UObject>> InLogicClipboardItems) const override;` — Whether a given clipboard items can be successfully pasted into this panel
- L54 _public prototype_ `virtual FText GetPasteItemMenuEntrySuffix() override;` — Provides an item suffix for the Paste context menu to provide users with useful context on the nature of the item being pasted
- L57 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() const override;` — Returns the UI items currently selected by the user (if any). To be implemented per child panel
- L60 _public prototype_ `URCController* GetParentController() const;` — Returns the parent Controller associated with this behaviour
- L65 _protected prototype_ `virtual FReply RequestDeleteSelectedItem() override;` — Warns user before deleting a selected panel item.
- L68 _protected prototype_ `virtual FReply RequestDeleteAllItems() override;` — Warns user before deleting all items in a panel.
- L72 _private prototype_ `static TSharedRef<SBox> GetNoneSelectedWidget();` — Get a Helper widget for behavior details.
- L75 _private prototype_ `void DuplicateBehaviour(URCBehaviour* InBehaviour);` — Duplicates a given Behaviour object
- L81 _private prototype_ `void OnControllerSelectionChanged(TSharedPtr<FRCControllerModel> InControllerItem, ESelectInfo::Type InSelectInfo);` — Controller list selection change listener. Updates the list of behaviours from newly selected Controller
- L84 _private prototype_ `void OnControllerValueChanged(TSharedPtr<FRCControllerModel> InController);` — Called when a controller value is changed
- L87 _private prototype_ `void UpdateWrappedWidget(const TSharedPtr<FRCControllerModel>& InControllerItem = nullptr);` — Rebuilds the Behaviour Panel for a newly selected Controller
- L90 _private prototype_ `TSharedRef<SWidget> GetBehaviourMenuContentWidget();` — Builds a menu containing the list of all possible Behaviours
- L93 _private prototype_ `void OnAddBehaviourClicked(UClass* InClass);` — Handles click event for Add Behaviour button
- L96 _private prototype_ `bool CanExecuteAddBehaviour(UClass* InClass, URCController* InController) const;` — Check if the controller can add the behaviour requested
- L99 _private prototype_ `FReply OnClickEmptyButton();` — Handles click event for "Empty" button; clears all Behaviours from the panel
- L102 _private prototype_ `void CreateBehaviorPanelWidgets();` — Check the validity of the panel widgets and if not valid will create them
- L105 _private prototype_ `bool AreBehaviorPanelWidgetsValid() const;` — Return whether or not all panel widgets are valid
- L109 _private member_ `TWeakPtr<FRCControllerModel> SelectedControllerItemWeakPtr = nullptr;` — The parent Controller that this Behaviour panel is associated with
- L112 _private member_ `TSharedPtr<SBox> WrappedBoxWidget;` — Parent Box for the entire widget
- L115 _private member_ `TSharedPtr<class SRCBehaviourPanelList> BehaviourPanelList;` — Widget representing List of Behaviours
- L118 _private member_ `TSharedPtr<SComboButton> AddNewBehaviorComboButton;` — ComboButton to add new behavior
- L121 _private member_ `TSharedPtr<SRCMinorPanel> BehaviourDockPanel;` — Behavior Minor Panel
- L124 _private member_ `const FRCPanelStyle* RCPanelStyle = nullptr;` — Panel Style reference.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Behaviour/SRCBehaviourPanelList.h` (Private)


#### class `SRCBehaviourPanelList`  
`class SRCBehaviourPanelList : public SRCLogicPanelListBase`  
_L27-146_
- inherits: `SRCLogicPanelListBase`
- desc: ~ SRCBehaviourPanelList ~ UI Widget for Behaviours List Used as part of the RC Logic Behaviour Panel.
- L30 _public function_ `SLATE_BEGIN_ARGS(SRCBehaviourPanelList)`
- L34 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRCBehaviourPanel> InBehaviourPanel, TSharedPtr<FRCControllerModel> InControllerItem, const TSharedRef<SRemoteControlPanel> InRemoteControlPanel);`
- L40 _public prototype_ `virtual bool IsEmpty() const override;` — Returns true if the underlying list is valid and empty.
- L43 _public prototype_ `virtual int32 Num() const override;` — Returns number of items in the list.
- L46 _public prototype_ `virtual int32 NumSelectedLogicItems() const override;` — The number of Controllers currently selected
- L49 _public prototype_ `virtual bool IsListFocused() const override;` — Whether the Behaviours List View currently has focus.
- L52 _public prototype_ `virtual void DeleteSelectedPanelItems() override;` — Deletes currently selected items from the list view
- L55 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() override;` — Returns the UI items currently selected by the user (if any).
- L58 _public function_ `TSharedPtr<FRCBehaviourModel> GetSelectedBehaviourItem()` — Return the behavior currently selected and displaying its ActionPanel
- L64 _public prototype_ `TArray<TSharedPtr<FRCBehaviourModel>> GetSelectedBehaviourItems() const;` — Return the list of all behavior currently selected
- L66 _public prototype_ `void RequestRefresh();`
- L68 _public prototype_ `virtual void AddNewLogicItem(UObject* InLogicItem) override;`
- L71 _public prototype_ `virtual void AddSpecialContextMenuOptions(FMenuBuilder& MenuBuilder) override;` — Allows Logic panels to add special functionality to the Context Menu based on context
- L74 _public prototype_ `void SelectFirstItem();` — Will set the selection to the first item
- L77 _public prototype_ `void SetSelection(TArray<TSharedPtr<FRCBehaviourModel>> InBehaviorToSelect);` — Set the current selection to the given InBehaviorToSelect list
- L80 _public prototype_ `void NotifyControllerValueChanged(TSharedPtr<FRCControllerModel> InController);` — Called when a controller value changed
- L83 _public prototype_ `TSharedPtr<FRCControllerModel> GetControllerItem() const;` — Return the controller item for this behavior
- L86 _public prototype_ `void SetControllerItem(const TSharedPtr<FRCControllerModel>& InNewControllerItem);` — Set a new controller item to update the behavior view based on the new controller
- L89 _public prototype_ `void SetAreSelectedBehaviorsEnabled(const bool bIsEnabled);` — Enables or Disables the currently selected behaviour
- L92 _public prototype_ `void SetIsBehaviourEnabled(TSharedRef<FRCBehaviourModel> InBehaviorModel, const bool bIsEnabled);` — Enables or Disables the given behaviour
- L95 _public prototype_ `void ReorderBehaviorItems(TSharedRef<FRCBehaviourModel> InDroppedOnModel, EItemDropZone InDropZone, TArray<TSharedPtr<FRCBehaviourModel>> InDroppedModels);` — Rearranges the behaviors based on the dropped behaviours.
- L100 _private prototype_ `void SetIsBehaviourEnabled(const TSharedPtr<FRCBehaviourModel>& InBehaviourModel, const bool bIsEnabled);` — Enables or Disables the passed behaviour
- L102 _private prototype_ `void AddBehaviourToList(URCBehaviour* InBehaviour);`
- L105 _private prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForList(TSharedPtr<FRCBehaviourModel> InItem, const TSharedRef<STableViewBase>& OwnerTable);` — OnGenerateRow delegate for the Behaviours List View
- L108 _private prototype_ `void OnTreeSelectionChanged(TSharedPtr<FRCBehaviourModel> InItem , ESelectInfo::Type);` — OnSelectionChanged delegate for Behaviours List View
- L111 _private prototype_ `void OnBehaviourAdded(const URCBehaviour* InBehaviour);` — Responds to the selection of a newly created Behaviour. Resets UI state
- L114 _private prototype_ `void OnEmptyBehaviours();` — Responds to the removal of all Behaviours. Rests UI state
- L117 _private prototype_ `virtual void Reset() override;` — Refreshes the list from the latest state of the model
- L120 _private prototype_ `virtual void BroadcastOnItemRemoved() override;` — Handles broadcasting of a successful remove item operation.
- L123 _private prototype_ `virtual URemoteControlPreset* GetPreset() override;` — Fetches the Remote Control preset associated with the parent panel
- L125 _private prototype_ `void OnBehaviourListModified();`
- L130 _private member_ `TWeakPtr<SRCBehaviourPanel> BehaviourPanelWeakPtr;` — The parent Behaviour Panel widget
- L133 _private member_ `TWeakPtr<FRCControllerModel> ControllerItemWeakPtr;` — The Controller (UI model) associated with us
- L136 _private member_ `TWeakPtr<FRCBehaviourModel> SelectedBehaviourItemWeakPtr;` — The currently selected Behaviour item (UI model)
- L139 _private member_ `TArray<TSharedPtr<FRCBehaviourModel>> BehaviourItems;` — List of Behaviours (UI models) active in this widget
- L142 _private member_ `TSharedPtr<SListView<TSharedPtr<FRCBehaviourModel>>> ListView;` — List View widget for representing our Behaviours List
- L145 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/CustomControllers/SCustomStatelessEventControllerWidget.h` (Private)


#### class `SCustomStatelessEventControllerWidget`  
`class SCustomStatelessEventControllerWidget : public SCompoundWidget`  
_L12-30_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SCustomStatelessEventControllerWidget)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, URCController* InController, const TSharedPtr<IPropertyHandle>& InOriginalPropertyHandle);`
- L27 _private member_ `TWeakObjectPtr<URCController> ControllerWeak;` — The controller associated with this widget.
- L29 _private prototype_ `FReply OnButtonClicked();`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/CustomControllers/SCustomStringListControllerListEditorWidget.h` (Private)


#### class `SCustomStringListControllerListEditorWidget`  
`class SCustomStringListControllerListEditorWidget : public SCompoundWidget`  
_L14-55_
- inherits: `SCompoundWidget`
- L17 _public function_ `SLATE_BEGIN_ARGS(SCustomStringListControllerListEditorWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() static void OpenModalWindow(const TSharedRef<SCustomStringListControllerWidget>& InParentWidget, const TArray<FName>& InEntries);`
- L23 _public prototype_ `virtual ~SCustomStringListControllerListEditorWidget() override = default;`
- L25 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SCustomStringListControllerWidget>& InParentWidget, const TArray<FName>& InEntries);`
- L27 _public prototype_ `bool HasEntry(FName InDescription) const;`
- L29 _public prototype_ `void AddEntry(FName InEntry);`
- L31 _public prototype_ `void RemoveEntry(FName InEntry);`
- L33 _public prototype_ `void ReplaceEntry(FName InFrom, FName InTo);`
- L35 _public prototype_ `void OnValuesChanged();`
- L37 _public prototype_ `TConstArrayView<FName> GetEntries() const;`
- L39 _public prototype_ `void OnValidDrop(FName InDropTarget, FName InDropped, EItemDropZone InDropZone);`
- L42 _private member_ `TWeakPtr<SCustomStringListControllerWidget> ParentWidgetWeak;`
- L43 _private member_ `TSharedPtr<SListView<FName>> ListView;`
- L44 _private member_ `TArray<FName> Entries;`
- L46 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(FName InEntry, const TSharedRef<STableViewBase>& InOwnerTable);`
- L48 _private prototype_ `void UpdateStringList();`
- L50 _private prototype_ `void CloseWindow();`
- L52 _private prototype_ `FReply OnOkClicked();`
- L54 _private prototype_ `FReply OnCancelClicked();`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/CustomControllers/SCustomStringListControllerWidget.h` (Private)


#### class `SCustomStringListControllerWidget`  
`class SCustomStringListControllerWidget : public SCompoundWidget`  
_L18-50_
- inherits: `SCompoundWidget`
- L21 _public function_ `SLATE_BEGIN_ARGS(SCustomStringListControllerWidget)`
- L25 _public prototype_ `virtual ~SCustomStringListControllerWidget() override = default;`
- L31 _public prototype_ `void Construct(const FArguments& InArgs, URCVirtualPropertyBase* InController, const TSharedPtr<IPropertyHandle>& InOriginalPropertyHandle);` — Constructs this widget with InArgs @param InOriginalPropertyHandle Original PropertyHandle of this CustomWidget
- L33 _public prototype_ `void UpdateStringList(const TArray<FName>& InNewEntries);`
- L37 _private member_ `TWeakObjectPtr<URCVirtualPropertyBase> ControllerWeak;` — Original PropertyHandle, used to update correctly the Widget and the Controller
- L38 _private member_ `TSharedPtr<IPropertyHandle> OriginalPropertyHandle;`
- L39 _private member_ `TSharedPtr<SBox> PropertyWidgetContainer;`
- L40 _private member_ `TArray<FName> Entries;`
- L41 _private member_ `TSharedPtr<SComboBox<FName>> StringSelector;`
- L43 _private prototype_ `FReply OnEditStringListClicked();`
- L45 _private prototype_ `TSharedRef<SWidget> OnGenerateWidget(FName InEntry);`
- L47 _private prototype_ `void OnSelectionChanged(FName InEntry, ESelectInfo::Type InSelectionType);`
- L49 _private prototype_ `FText GetCurrentValueText() const;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/CustomControllers/SCustomTextureControllerWidget.h` (Private)


#### class `SCustomTextureControllerWidget`  
`class SCustomTextureControllerWidget : public SCompoundWidget`  
_L12-88_
- inherits: `SCompoundWidget`
- L15 _public function_ `SLATE_BEGIN_ARGS(SCustomTextureControllerWidget)`
- L19 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, URCController* InController, const TSharedPtr<IPropertyHandle>& InOriginalPropertyHandle);`
- L29 _private prototype_ `void OnControllerTypeChanged(TSharedPtr<FString, ESPMode::ThreadSafe> InString, ESelectInfo::Type InArg);` — Handle toggling Texture Controller type change: External vs. Internal
- L32 _private prototype_ `void OnAssetSelected(const FAssetData& AssetData);` — Called when a Texture is selected in Asset mode
- L35 _private prototype_ `void UpdateControllerValue();` — Sets the controller value starting from the current path set via this Widget
- L38 _private prototype_ `void HandleFilePathPickerPathPicked(const FString& String);` — Called to handle the file selection via OS window
- L41 _private prototype_ `void UpdateValueWidget();` — Refresh the value widget content. Useful when switching between External and Asset modes
- L44 _private prototype_ `void UpdateThumbnailWidget();` — Refresh the thumbnail widget content
- L47 _private prototype_ `void RefreshThumbnailImage();` — Loads the selected texture and updates the thumbnail Widget
- L50 _private prototype_ `FString GetFilePath() const;` — Returns the current external file path
- L53 _private prototype_ `FString GetAssetPath() const;` — Returns the current internal/asset file path
- L56 _private prototype_ `FString GetAssetPathName() const;` — Returns the path name for the currently stored texture
- L59 _private prototype_ `FString GetCurrentPath() const;` — Returns current texture path value. Can be External or Asset, depending on current mode
- L61 _private prototype_ `TSharedRef<SWidget> GetAssetThumbnailWidget();`
- L62 _private prototype_ `TSharedRef<SWidget> GetExternalTextureValueWidget();`
- L63 _private prototype_ `TSharedRef<SWidget> GetAssetTextureValueWidget();`
- L66 _private member_ `TObjectPtr<UTexture2D> Texture;` — The texture selected by the user via the asset or external file path
- L69 _private member_ `TSharedPtr<SBox> ValueWidgetBox;` — The widget containing the controller value
- L72 _private member_ `TSharedPtr<SBox> ThumbnailWidgetBox;` — The widget containing the thumbnail for the currently selected Texture
- L75 _private member_ `FString CurrentAssetPath;` — Current path for texture project asset
- L78 _private member_ `FString CurrentExternalPath;` — Current path pointing to external texture (e.g. png file)
- L81 _private member_ `bool bInternal = false;` — Is the Texture controller currently used to select a texture asset (internal) or an external texture?
- L84 _private member_ `TArray<TSharedPtr<FString>> ControllerTypes;` — List of available Texture Controller types, used by combo box selection. Supports Asset and External
- L87 _private member_ `TSharedPtr<IPropertyHandle> OriginalPropertyHandle;` — Original PropertyHandle, used to update correctly the Widget and the Controller

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/RCCategoryModel.h` (Private)


#### class `FRCCategoryModel`  
`class FRCCategoryModel : public FRCLogicModeBase`  
_L21-81_
- inherits: `FRCLogicModeBase`
- desc: ~ FRCCategoryModel ~ UI model for representing a Category Contains a row widget with Category Name
- L24 _public member_ `static const FLazyName CategoryModelName;`
- L26 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueChanged, TSharedPtr<FRCCategoryModel> );`
- L28 _public prototype_ `FRCCategoryModel(const FGuid& InCateogryId, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L30 _public function_ `virtual FName GetModelType() const override`
- L35 _public prototype_ `TOptional<FRCVirtualPropertyCategory> GetCategory() const;`
- L38 _public prototype_ `void Initialize();` — Called right after object construction to initialize the model (and allow using SharedThis, etc)
- L44 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() const override;` — The widget to be rendered for this Category Used to represent a single row when added to the Controllers Panel List
- L46 _public prototype_ `virtual int32 RemoveModel() override;`
- L49 _public prototype_ `TSharedRef<SWidget> GetNameWidget() const;` — The widget showing the Name of this Category
- L52 _public prototype_ `void EnterNameEditingMode();` — Allows users to enter text into the Category Name Box
- L55 _public prototype_ `FText GetCategoryDisplayName() const;` — User-friendly Name of the underlying Category
- L58 _public function_ `FGuid GetId() const` — Fetches the unique Id for this UI item
- L61 _public prototype_ `void SetDisplayIndex(int32 InDisplayIndex);` — Set the display index of the underlying category item
- L64 _public member_ `FOnValueChanged OnValueChanged;` — Triggered when the Value this controller changes
- L68 _private prototype_ `void OnCategoryNameCommitted(const FText& InNewCategoryName, ETextCommit::Type InCommitInfo);` — Text commit event for Category Name text box
- L71 _private prototype_ `void CheckCachedIndex() const;` — Checks cached index fro validity and sets it if not.
- L74 _private member_ `TSharedPtr<SInlineEditableTextBlock> CategoryNameTextBox;` — Category name - editable text box
- L77 _private member_ `FGuid Id;` — Unique Id for this UI item
- L80 _private member_ `mutable int32 CachedIndex;` — Cached index for the category for faster lookup.

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueChanged, TSharedPtr<FRCCategoryModel> );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/RCControllerModel.h` (Private)


#### class `FRCControllerModel`  
`class FRCControllerModel : public FRCLogicModeBase, public FSelfRegisteringEditorUndoClient`  
_L30-166_
- inherits: `FRCLogicModeBase,FSelfRegisteringEditorUndoClient`
- desc: ~ FRCControllerModel ~ UI model for representing a Controller Contains a row widget with Controller Name, Field Id and a Value Widget. If this is setup to be a MultiController, a Value Type selection Widget will be available as well.
- L33 _public member_ `static const FLazyName ControllerModelName;`
- L35 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValueTypeChanged, URCVirtualPropertyBase* , EPropertyBagPropertyType );`
- L36 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueChanged, TSharedPtr<FRCControllerModel> );`
- L38 _public prototype_ `FRCControllerModel(URCVirtualPropertyBase* InVirtualProperty, const TSharedRef<IDetailTreeNode>& InTreeNode, const TSharedPtr<SRemoteControlPanel> InRemoteControlPanel);`
- L40 _public function_ `virtual FName GetModelType() const override`
- L46 _public prototype_ `void Initialize();` — Called right after object construction to initialize the model (and allow using SharedThis, etc)
- L52 _public prototype_ `virtual TSharedRef<SWidget> GetWidget() const override;` — The widget to be rendered for this Controller Used to represent a single row when added to the Controllers Panel List
- L54 _public prototype_ `virtual int32 RemoveModel() override;`
- L57 _public prototype_ `TSharedRef<SWidget> GetNameWidget() const;` — The widget showing the Name of this Controller
- L60 _public prototype_ `TSharedRef<SWidget> GetDescriptionWidget() const;` — The widget showing the Description of this Controller
- L63 _public prototype_ `TSharedRef<SWidget> GetFieldIdWidget() const;` — The widget showing the Field Id of this Controller
- L66 _public prototype_ `TSharedRef<SWidget> GetTypeSelectionWidget();` — The widget showing the Value Type selection dropdown for this Controller (used for MultiControllers)
- L69 _public prototype_ `TSharedRef<SWidget> GetControllerExtensionWidget(const FName& InColumnName) const;` — The widget allowing controller columns customization
- L75 _public prototype_ `void SetMultiController(bool bInIsMultiController);` — Specify if this is a MultiController handling other hidden controllers. MultiControllers will setup and show a Type Selection Widget.
- L78 _public prototype_ `virtual URCVirtualPropertyBase* GetVirtualProperty() const;` — Returns the Controller (Data Model) associated with us
- L81 _public prototype_ `virtual const FName GetPropertyName() const;` — Returns the Controller Name (from Virtual Property) represented by us
- L84 _public prototype_ `TSharedPtr<FRCBehaviourModel> GetSelectedBehaviourModel() const;` — Returns the currently selected Behaviour (UI model)
- L87 _public prototype_ `void UpdateSelectedBehaviourModel(TSharedPtr<FRCBehaviourModel> InModel);` — Updates our internal record of the currently selected Behaviour (UI Model)
- L90 _public prototype_ `void EnterDescriptionEditingMode();` — Allows users to enter text into the Controller Name Box
- L93 _public prototype_ `FText GetControllerDisplayName() const;` — User-friendly Name of the underlying Controller
- L96 _public prototype_ `FText GetControllerDescription() const;` — Description of the underlying Controller
- L99 _public function_ `FGuid GetId() const` — Fetches the unique Id for this UI item
- L102 _public member_ `FOnValueTypeChanged OnValueTypeChanged;` — Triggered when the Value Type of this changes (for MultiControllers)
- L105 _public member_ `FOnValueChanged OnValueChanged;` — Triggered when the Value this controller changes
- L109 _private prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L110 _private function_ `virtual void PostRedo(bool bSuccess) override`
- L114 _private prototype_ `void OnControllerNameCommitted(const FText& InNewControllerName, ETextCommit::Type InCommitInfo);` — Text commit event for Controller Name text box
- L117 _private prototype_ `void OnControllerDescriptionCommitted(const FText& InNewControllerDescription, ETextCommit::Type InCommitInfo);` — Text commit event for Controller description text box
- L120 _private prototype_ `void OnControllerFieldIdCommitted(const FText& InNewControllerFieldId, ETextCommit::Type InCommitInfo);` — Text commit event for Controller FieldId text box
- L123 _private prototype_ `void OnTextControlValueTypeChanged(TSharedPtr<FString, ESPMode::ThreadSafe> InControlValueTypeString, ESelectInfo::Type Arg);` — Value Type change event, in case this is a MultiController
- L126 _private prototype_ `void OnPropertyValueChanged(const FPropertyChangedEvent& InPropertyChangedEvent);` — Value change event
- L129 _private prototype_ `EVisibility GetPlaceholderVisibility() const;` — Get the current visibility of the placeholder TextBlock widget
- L132 _private prototype_ `void InitControlledTypes();` — Initializes the list of controlled types. Used by MultiControllers
- L135 _private member_ `TWeakObjectPtr<URCVirtualPropertyBase> VirtualPropertyWeakPtr;` — Virtual Property (Data Model) represented by us
- L138 _private member_ `TWeakPtr<IDetailTreeNode> DetailTreeNodeWeakPtr;` — The row generator used to build a generic Value Widget
- L141 _private member_ `TWeakPtr<FRCBehaviourModel> SelectedBehaviourModelWeakPtr;` — The currently selected Behaviour (UI model)
- L144 _private member_ `TSharedPtr<SEditableTextBox> ControllerNameTextBox;` — Controller id - editable text box
- L147 _private member_ `TSharedPtr<SInlineEditableTextBlock> ControllerDescriptionTextBox;` — Controller description - editable text box
- L150 _private member_ `TSharedPtr<SInlineEditableTextBlock> ControllerFieldIdTextBox;` — Controller Field Id - editable text box
- L153 _private member_ `TArray<TSharedPtr<FString>> ControlledTypesAsStrings;` — Holds a list of controlled types, represented as strings. Used to show the Value Type selection dropdown
- L156 _private member_ `int32 CurrentControlValueTypeIndex = 0;` — Index representing the currently selected Value Type within the ControlledTypesAsStrings array
- L159 _private member_ `EPropertyBagPropertyType CurrentControlValueType;` — Current control value type
- L162 _private member_ `bool bIsMultiController = false;` — Is this a multi controller?
- L165 _private member_ `FGuid Id;` — Unique Id for this UI item

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnValueTypeChanged, URCVirtualPropertyBase* , EPropertyBagPropertyType );`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnValueChanged, TSharedPtr<FRCControllerModel> );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/RCControllerPanelListItem.h` (Private)


#### enum `ERCControllerPanelListItemType`  
`enum class ERCControllerPanelListItemType : uint8`  
_L9-14_
- L11 _public enumerator_ `None`
- L12 _public enumerator_ `Category`
- L13 _public enumerator_ `Controller`

#### struct `FRCControllerPanelListItem`  
`struct FRCControllerPanelListItem`  
_L16-50_
- L18 _public member_ `ERCControllerPanelListItemType Type;`
- L19 _public member_ `int32 Index;`
- L21 _public function_ `operator bool() const`
- L26 _public function_ `bool operator==(const FRCControllerPanelListItem& InOther) const`
- L32 _public function_ `bool operator<(const FRCControllerPanelListItem& InOther) const`

#### struct `TIsValidListItem`  
`template <> struct TIsValidListItem<FRCControllerPanelListItem>`  
_L61-67_

#### enum `TIsValidListItem::(anonymous)`  
``  
_L64-66_

#### struct `TListTypeTraits`  
`template <> struct TListTypeTraits<FRCControllerPanelListItem>`  
_L73-119_
- desc: Functionality (e.g. setting the value, testing invalid value) specialized for FGroupItem.
- L76 _public typedef_ `typedef FRCControllerPanelListItem NullableType;`
- L78 _public typedef_ `using MapKeyFuncs = TDefaultMapHashableKeyFuncs<FRCControllerPanelListItem, TSharedRef<ITableRow>, false>;`
- L79 _public typedef_ `using MapKeyFuncsSparse = TDefaultMapHashableKeyFuncs<FRCControllerPanelListItem, FSparseItemInfo, false>;`
- L80 _public typedef_ `using SetKeyFuncs = DefaultKeyFuncs<FRCControllerPanelListItem>;`
- L83 _public function_ `template<typename U> static void AddReferencedObjects(FReferenceCollector& Collector, TArray<FRCControllerPanelListItem>& ItemsWithGeneratedWidgets, TSet<FRCControllerPanelListItem>& SelectedItems, TMap<const U*, FRCControllerPanelListItem>& WidgetToItemMap)`
- L90 _public function_ `static bool IsPtrValid(const FRCControllerPanelListItem& InValue)`
- L95 _public function_ `static void ResetPtr(FRCControllerPanelListItem& InValue)`
- L101 _public function_ `static FRCControllerPanelListItem MakeNullPtr()`
- L106 _public function_ `static FRCControllerPanelListItem NullableItemTypeConvertToItemType(const FRCControllerPanelListItem& InValue)`
- L111 _public function_ `static FString DebugDump(FRCControllerPanelListItem InValue)`

#### class `TListTypeTraits::SerializerType`  
`class SerializerType`  
_L116-118_

#### Free symbols / members of external scopes

- L46 _function_ `friend uint32 GetTypeHash(const FRCControllerPanelListItem& InItem)`
- L52 _namespace_ `namespace UE`
- L52 _namespace_ `namespace RemoteControl` (scope `UE`)
- L52 _namespace_ `namespace UI` (scope `UE::RemoteControl`)
- L52 _namespace_ `namespace Private` (scope `UE::RemoteControl::UI`)
- L54 _namespace_ `namespace ControllerPanelListItem` (scope `UE::RemoteControl::UI::Private`)
- L56 _variable_ `const FRCControllerPanelListItem None = {ERCControllerPanelListItemType::None, INDEX_NONE};` (scope `UE::RemoteControl::UI::Private::ControllerPanelListItem`)
- L65 _enumerator_ `Value = true` (scope `TIsValidListItem::__anon9bb11f0e0103`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/RCMultiController.h` (Private)


#### struct `FRCMultiController`  
`struct FRCMultiController`  
_L15-45_
- desc: A MultiController keeps a reference to a Main Controller and to a set of Handled Controllers with the same Field Id. A MultiController can try to use its MainController value to update the value of its Handled Controllers. This is useful when Control Panel List is in MultiController Mode, and Controllers with duplicate Field Ids are hidden.
- L18 _public prototype_ `FRCMultiController(const TWeakObjectPtr<URCVirtualPropertyBase>& InController);`
- L21 _public prototype_ `void SetMainController(URCVirtualPropertyBase* InController);` — Sets the provided controller as the MainController, which will drive other Handled Controllers
- L24 _public prototype_ `void AddHandledController(URCVirtualPropertyBase* InController);` — Adds a controller to the list of Handled Controllers managed by the MainController of this MultiController setup
- L27 _public prototype_ `void UpdateHandledControllersValue();` — Goes through each Handled Controller, and tries to update its value based on the current value of the MainController
- L30 _public function_ `bool IsValid() const` — MultiController is considered valid when its MainController is valid
- L33 _public prototype_ `FName GetFieldId() const;` — Returns the Field Id this MultiController is associated with
- L36 _public prototype_ `FGuid GetMainControllerId() const;` — Return the Id of the MainController
- L39 _public function_ `EPropertyBagPropertyType GetValueType() const` — Returns the value type of the MainController
- L42 _private member_ `TWeakObjectPtr<URCVirtualPropertyBase> MainControllerWeak;`
- L43 _private member_ `EPropertyBagPropertyType ValueType;`
- L44 _private member_ `TArray<TObjectPtr<URCVirtualPropertyBase>> HandledControllers;`

#### struct `FRCMultiControllersState`  
`struct FRCMultiControllersState`  
_L51-79_
- desc: Holds and handles a Map of MultiControllers. Also keeps reference of currently selected Value Type per each Field Id.
- L53 _public prototype_ `bool TryToAddAsMultiController(URCVirtualPropertyBase* InController);`
- L55 _public prototype_ `EPropertyBagPropertyType GetCurrentType(const FName& InFieldId);`
- L56 _public prototype_ `FRCMultiController GetMultiController(const FName& InFieldId);`
- L62 _public prototype_ `void UpdateFieldIdValueType(const FName& InFieldId, EPropertyBagPropertyType InValueType);` — Calling this function will overwrite the currently selected type for the specified field id. FRCMultiControllersState will then be in an invalid state, so it will require the hosting ControllerPanelList to call Reset()
- L65 _public prototype_ `void ResetMultiControllers();` — Empties the internal map referencing the handled MultiControllers
- L68 _public prototype_ `void ResetSelectedValueTypes();` — Empties the internal map used to store the currently selected value type for each Field Id
- L71 _public prototype_ `void RemoveMultiController(const FName& InFieldId);` — Removes the MultiController associated with the specified Field Id
- L75 _private member_ `TMap<FName, FRCMultiController> MultiControllersMap;` — Map of MultiControllers, indexed by their Field Id
- L78 _private member_ `TMap<FName, EPropertyBagPropertyType> SelectedValueTypes;` — Used to store the currently chosen value type. This is stored outside of FRCMultiController, so that the info is kept between UI Refreshes

#### Free symbols / members of external scopes

- L81 _namespace_ `namespace UE`
- L81 _namespace_ `namespace MultiControllers` (scope `UE`)
- L81 _namespace_ `namespace Public` (scope `UE::MultiControllers`)
- L84 _prototype_ `EPropertyBagPropertyType GetOptimalValueTypeForFieldId(const URemoteControlPreset* InPreset, const FName& InFieldId);` (scope `UE::MultiControllers::Public`) — Returns the optimal value type for the specified Field Id
- L87 _prototype_ `TArray<EPropertyBagPropertyType> GetFieldIdValueTypes(const URemoteControlPreset* InPreset, const FName& InFieldId);` (scope `UE::MultiControllers::Public`) — Returns a list of all the Value Types currently associated to the specified Field Id

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/SRCControllerPanel.h` (Private)


#### struct `UE::RemoteControl::UI::Private::FRCControllerPropertyInfo`  
`struct FRCControllerPropertyInfo`  
_L26-43_
- desc: Helper struct used when generating Controllers. Wraps the TypeObject and the Bag Type. Additionally, some facultative MetaData can be added to create a Custom Controller extending the initial type e.g. External Texture custom controller is a specialized String controller See RCCustomControllerUtilities.h for helper functions related to custom controllers.
- L28 _public member_ `static const FLazyName CategoryName;`
- L29 _public member_ `static const FLazyName InitialDescriptionName;`
- L30 _public member_ `static const FString CategoryMeta;`
- L32 _public function_ `FRCControllerPropertyInfo()`
- L33 _public function_ `FRCControllerPropertyInfo(UObject* InValueTypeObject) : ValueTypeObject(InValueTypeObject)`
- L36 _public member_ `EPropertyBagPropertyType Type = EPropertyBagPropertyType::Name;` — The type of the controller which will be created starting from this FRCControllerPropertyInfo
- L39 _public member_ `UObject* ValueTypeObject = nullptr;` — Object defining an Enum, Struct, or Class
- L42 _public member_ `TMap<FName, FString> CustomMetaData;` — MetaData Map which can be used to pass additional settings or information to be used when customizing a Custom Controller

#### class `SRCControllerPanel`  
`class SRCControllerPanel : public SRCLogicPanelBase`  
_L53-160_
- inherits: `SRCLogicPanelBase`
- desc: ~ SRCControllerPanel ~ UI Widget for Controller Panel. Contains a header (Add/Remove/Empty) and List of Controllers
- L56 _public function_ `SLATE_BEGIN_ARGS(SRCControllerPanel)`
- L59 _public prototype_ `SLATE_ATTRIBUTE(bool, LiveMode) SLATE_END_ARGS() static UE::RemoteControl::UI::Private::FRCControllerPropertyInfo GetPropertyInfoForCustomType(const FName& InType);`
- L66 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<SRemoteControlPanel>& InPanel);` — Constructs this widget with InArgs
- L69 _public prototype_ `void Refresh();` — Called to refresh the controller list
- L72 _public prototype_ `bool IsListFocused() const;` — Whether the Controller list widget currently has focus. Used for Delete Item UI command
- L75 _public prototype_ `virtual void DeleteSelectedPanelItems() override;` — Delete Items UI command implementation for this panel
- L78 _public prototype_ `virtual bool CanDuplicateItems() const override;` — Checks to make sure selected items are duplicatable
- L81 _public prototype_ `virtual void DuplicateSelectedPanelItems() override;` — "Duplicate Items" UI command implementation for Controller panel
- L84 _public prototype_ `virtual bool CanCopyItems() const override;` — Checks to make sure selected items are copyable.
- L87 _public prototype_ `virtual void CopySelectedPanelItems() override;` — "Copy Items" UI command implementation for Controller panel
- L90 _public prototype_ `virtual void PasteItemsFromClipboard() override;` — "Paste Items" UI command implementation for Controller panel
- L93 _public prototype_ `virtual FText GetPasteItemMenuEntrySuffix() override;` — Provides an item suffix for the Paste context menu to provide users with useful context on the nature of the item being pasted
- L96 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() const override;` — Returns the UI items currently selected by the user (if any). To be implemented per child panel
- L99 _public prototype_ `TArray<TSharedPtr<FRCControllerModel>> GetSelectedControllers() const;` — Get the currently selected controller models.
- L102 _public prototype_ `int32 NumControllerItems() const;` — Retrieve the current number of Controllers
- L104 _public prototype_ `void EnterRenameMode();`
- L108 _protected prototype_ `virtual FReply RequestDeleteSelectedItem() override;` — Warns user before deleting a selected panel item.
- L111 _protected prototype_ `virtual FReply RequestDeleteAllItems() override;` — Warns user before deleting all items in a panel.
- L115 _private prototype_ `void DuplicateController(URCController* InController);` — Duplicates a given Controller object
- L118 _private prototype_ `TSharedRef<SWidget> GetControllerMenuContentWidget() const;` — Builds a menu containing the list of all possible Controllers
- L121 _private prototype_ `void GetControllerMenuStructContentWidget(FMenuBuilder& InMenuBuilder) const;` — Builds a menu containing the list of all possible structs on which to base a Controller.
- L124 _private prototype_ `void GetControllerMenuEnumContentWidget(FMenuBuilder& InMenuBuilder) const;` — Builds a menu containing the list of all possible enums on which to base a Controller.
- L126 _private prototype_ `TSharedRef<SWidget> GetMultiControllerSwitchWidget();`
- L129 _private prototype_ `void OnAddControllerClicked(const EPropertyBagPropertyType InValueType, const UE::RemoteControl::UI::Private::FRCControllerPropertyInfo InControllerPropertyInfo) const;` — Handles click event for Add Controller button
- L130 _private prototype_ `void OnAddControllerClicked(const EPropertyBagPropertyType InValueType, const UE::RemoteControl::UI::Private::FRCControllerPropertyInfo InControllerPropertyInfo, TSubclassOf<URCController> InControllerClass) const;`
- L133 _private prototype_ `void OnAddCategoryClicked() const;` — Handles adding a new category
- L136 _private prototype_ `void OnAddControllerSelected(TSharedPtr<UE::RemoteControl::UI::Private::FRCControllerPropertyInfo> InControllerPropertyInfo) const;` — Handles selection of controller type in submenus.
- L139 _private prototype_ `void OnToggleMultiControllersMode(ECheckBoxState CheckBoxState);` — Handles checkbox changes event for the MultiController mode selection widget
- L142 _private prototype_ `EVisibility GetMultiControllerSwitchVisibility() const;` — Whether to show the MultiController switch or not
- L145 _private prototype_ `FReply OnClickEmptyButton();` — Handles click event for Empty button; clears all controllers from the panel
- L150 _private member_ `TSharedPtr<class SRCControllerPanelList> ControllerPanelList;` — Widget representing List of Controllers
- L153 _private member_ `TAttribute<bool> bIsInLiveMode;` — Whether the panel is in live mode.
- L156 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L159 _private member_ `bool bIsMultiControllerMode = false;` — Is the Panel showing a list with MultiControllers handling (and hiding) controllers with duplicate Field Ids?

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace RemoteControl` (scope `UE`)
- L16 _namespace_ `namespace UI` (scope `UE::RemoteControl`)
- L16 _namespace_ `namespace Private` (scope `UE::RemoteControl::UI`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/SRCControllerPanelCategoryRow.h` (Private)


#### class `SRCControllerPanelCategoryRow`  
`class SRCControllerPanelCategoryRow : public STableRow<FRCControllerPanelListItem>`  
_L16-46_
- inherits: `STableRow<FRCControllerPanelListItem>`
- L18 _private typedef_ `using FSuperRowType = STableRow<FRCControllerPanelListItem>;`
- L21 _public function_ `SLATE_BEGIN_ARGS(SRCControllerPanelCategoryRow)`
- L22 _public prototype_ `SLATE_STYLE_ARGUMENT(FTableRowStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<SRCControllerPanelList> InControllerPanelList, FRCControllerPanelListItem InCategoryItem);`
- L28 _public prototype_ `TSharedPtr<FRCCategoryModel> GetCategory() const;`
- L32 _private prototype_ `TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FRCControllerPanelListItem InItem);` — Called to validate whether a drag drop event is accepted for a controller item row
- L35 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FRCControllerPanelListItem InItem);` — Called when a drop happens on this controller item row
- L37 _private prototype_ `void AddControllerFromEntities(const FExposedEntityDragDrop& InExposedEntityDragDrop, EItemDropZone InDropZone);`
- L40 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L41 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L44 _private member_ `TWeakPtr<SRCControllerPanelList> ControllerPanelListWeak;`
- L45 _private member_ `FRCControllerPanelListItem CategoryItem;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/SRCControllerPanelControllerRow.h` (Private)


#### struct `FRCControllerColumns`  
`struct FRCControllerColumns`  
_L14-23_
- L16 _public member_ `static const FLazyName Wires;`
- L17 _public member_ `static const FLazyName TypeColor;`
- L18 _public member_ `static const FLazyName ControllerId;`
- L19 _public member_ `static const FLazyName Description;`
- L20 _public member_ `static const FLazyName Value;`
- L21 _public member_ `static const FLazyName FieldId;`
- L22 _public member_ `static const FLazyName ValueTypeSelection;`

#### class `SRCControllerPanelControllerRow`  
`class SRCControllerPanelControllerRow : public SMultiColumnTableRow<FRCControllerPanelListItem>`  
_L25-69_
- inherits: `SMultiColumnTableRow<FRCControllerPanelListItem>`
- L28 _public function_ `SLATE_BEGIN_ARGS(SRCControllerPanelControllerRow)`
- L29 _public prototype_ `SLATE_STYLE_ARGUMENT(FTableRowStyle, Style) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<SRCControllerPanelList> InControllerPanelList, FRCControllerPanelListItem InControllerItem);`
- L35 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L37 _public prototype_ `TSharedPtr<FRCControllerModel> GetControllerModel() const;`
- L41 _private prototype_ `TOptional<EItemDropZone> CanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FRCControllerPanelListItem InItem);` — Called to validate whether a drag drop event is accepted for a controller item row
- L44 _private prototype_ `FReply OnAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, FRCControllerPanelListItem InItem);` — Called when a drop happens on this controller item row
- L55 _private prototype_ `void CreateBindBehaviorsFromEntities(const FExposedEntityDragDrop& InExposedEntityDragDrop, const FDragDropContext& InContext);` — Creates a bind behavior on the existing controller items for all the given entities found in the drag drop
- L58 _private prototype_ `void CreateControllersFromEntities(const FExposedEntityDragDrop& InExposedEntityDragDrop, const FDragDropContext& InContext);` — Creates new controllers next to this item row (above/below depending on drop zone) and creates a bind behavior for each new controller for all the given entities found in the drag drop
- L60 _private prototype_ `TSharedRef<SWidget> GetTypeColorWidget();`
- L63 _private prototype_ `virtual FReply OnDragDetected(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L64 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L67 _private member_ `TWeakPtr<SRCControllerPanelList> ControllerPanelListWeak;`
- L68 _private member_ `FRCControllerPanelListItem ControllerItem;`

#### struct `SRCControllerPanelControllerRow::FDragDropContext`  
`struct FDragDropContext`  
_L46-52_
- L48 _public member_ `URemoteControlPreset* Preset;`
- L49 _public member_ `const TSharedPtr<SRCControllerPanelList>& ControllerPanelList;`
- L50 _public member_ `const FRCControllerPanelListItem& Item;`
- L51 _public member_ `EItemDropZone DropZone;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/SRCControllerPanelList.h` (Private)


#### class `FRCControllerPanelDragDrop`  
`class FRCControllerPanelDragDrop final : public FDecoratedDragDropOp`  
_L38-56_
- inherits: `FDecoratedDragDropOp`
- desc: ~ FRCControllerPanelDragDrop ~ Facilitates drag-drop operation
- L41 _public function_ `DRAG_DROP_OPERATOR_TYPE(FRCControllerDragDropOp, FDecoratedDragDropOp) explicit FRCControllerPanelDragDrop(const TArray<FRCControllerPanelListItem>& InItems) : Items(InItems)`
- L49 _public function_ `TArray<FRCControllerPanelListItem> GetItems() const`
- L55 _private member_ `TArray<FRCControllerPanelListItem> Items;`

#### class `SRCControllerPanelList`  
`class SRCControllerPanelList : public SRCLogicPanelListBase, public FNotifyHook`  
_L64-282_
- inherits: `SRCLogicPanelListBase,FNotifyHook`
- desc: ~ SRCControllerPanelList ~ UI Widget for Controllers List Used as part of the RC Logic Actions Panel.
- L67 _public function_ `SLATE_BEGIN_ARGS(SRCControllerPanelList)`
- L71 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRCControllerPanel> InControllerPanel, const TSharedRef<SRemoteControlPanel> InRemoteControlPanel);`
- L77 _public prototype_ `virtual bool IsEmpty() const override;` — Returns true if the underlying list is valid and empty.
- L80 _public prototype_ `virtual int32 Num() const override;` — Returns number of items in the list.
- L83 _public prototype_ `virtual int32 NumSelectedLogicItems() const override;` — The number of Controllers currently selected
- L86 _public prototype_ `virtual bool IsListFocused() const override;` — Whether the Controllers List View currently has focus.
- L89 _public prototype_ `virtual void DeleteSelectedPanelItems() override;` — Deletes currently selected items from the list view
- L92 _public prototype_ `TArray<FRCControllerPanelListItem> GetSelectedItems() const;` — Returns the list items selected by the user (if any).
- L95 _public prototype_ `TArray<TSharedPtr<FRCControllerModel>> GetSelectedControllers() const;` — Returns the controllers selected by the user (if any).
- L98 _public prototype_ `TArray<TSharedPtr<FRCCategoryModel>> GetSelectedCategories() const;` — Returns the categories selected by the user (if any).
- L101 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() override;` — Returns the UI items currently selected by the user (if any).
- L104 _public prototype_ `virtual void NotifyPreChange(FEditPropertyChain* PropertyAboutToChange) override;` — FNotifyHook Interface Begin
- L107 _public prototype_ `void EnterRenameMode();`
- L109 _public function_ `int32 NumControllerItems() const`
- L115 _public prototype_ `TSharedPtr<FRCCategoryModel> FindCategoryItemByListItem(const FRCControllerPanelListItem& InItem) const;` — Finds a category by list item
- L118 _public prototype_ `TSharedPtr<FRCControllerModel> FindControllerItemByListItem(const FRCControllerPanelListItem& InItem) const;` — Finds a Controller UI model by list item
- L121 _public prototype_ `TSharedPtr<FRCControllerModel> FindControllerItemById(const FGuid& InId) const;` — Finds a Controller UI model by unique Id
- L124 _public prototype_ `TSharedPtr<FRCControllerModel> FindControllerItemByPropertyName(const FName& InPropertyName) const;` — Finds a Controller UI model by unique Id
- L127 _public prototype_ `TArray<TSharedPtr<FRCControllerModel>> FindControllerItemsById(TConstArrayView<FGuid> InIds);` — Finds the Controller UI models by unique Id
- L130 _public prototype_ `TArray<TSharedPtr<FRCControllerModel>> FindControllerItemsByObject(TConstArrayView<URCController*> InControllers);` — Finds the Controller UI models by their controllers
- L133 _public prototype_ `FRCControllerPanelListItem FindListItemByControllerItem(const TSharedRef<FRCControllerModel>& InModel) const;` — Finds the item by controller UI model
- L136 _public prototype_ `FRCControllerPanelListItem FindListItemByCategoryItem(const TSharedRef<FRCCategoryModel>& InModel) const;` — Finds the item by category id
- L142 _public prototype_ `bool ReorderItems(TConstArrayView<FRCControllerPanelListItem> InItemsToMove, FRCControllerPanelListItem InDroppedOnItem, EItemDropZone InDropZone);` — Called to moves the given controller items to the given target index, pushing all other rows below returns true if the operation was successful
- L145 _public function_ `void RequestRefresh()` — Requests the panel to refresh its contents from the latest list of Controllers
- L151 _public prototype_ `bool OnAllowDrop(TSharedPtr<FDragDropOperation> DragDropOperation);` — Drag-Drop validation delegate for the Controllers Panel List
- L154 _public prototype_ `FReply OnControllerTreeViewDragDrop(TSharedPtr<FDragDropOperation> InDragDropOperation);` — Drag-Drop action delegate for the Controllers Panel List
- L157 _public prototype_ `virtual URemoteControlPreset* GetPreset() override;` — Fetches the Remote Control preset associated with the parent panel
- L160 _public prototype_ `void CreateBindBehaviourAndAssignTo(URCController* Controller, TSharedRef<const FRemoteControlProperty> InRemoteControlProperty, const bool bExecuteBind);` — Creates a Bind Behaviour for the given Controller and binds the given remote control property to it
- L163 _public prototype_ `bool IsTreeViewHovered();` — Whether the user's cursor is directly hovered over the List View
- L166 _public prototype_ `void SetMultiControllerMode(bool bIsUniqueModeOn);` — Enable/disable MultiController Mode
- L169 _public function_ `TConstArrayView<FName> GetCustomColumns() const` — Return the current list of custom columns names, if any
- L177 _public member_ `bool bIsAnyControllerItemEligibleForDragDrop = false;` — Flag that facilitates usage of two mutually exclusive drag-drop zones within a single panel The first drag-drop zone is empty panel space for "Bind To New Controller" The second drag-drop zone is the Controller name widget for "Bind To Existing Controller" This flag is set if any Controller has active drag-drop focus, in which case we disable the first drag-drop zone. This is purely for visual clarity
- L180 _public prototype_ `TSharedRef<ITableRow> OnGenerateWidgetForTree(FRCControllerPanelListItem InItem, const TSharedRef<STableViewBase>& OwnerTable);` — OnGenerateRow delegate for the Actions List View
- L183 _public prototype_ `bool IsItemCategoryExpanded(FRCControllerPanelListItem InItem) const;` — Returns the row for a given item.
- L186 _public prototype_ `void OnGetChildren(FRCControllerPanelListItem InItem, TArray<FRCControllerPanelListItem>& OutChildren);` — Gets the children for categories.
- L189 _public prototype_ `void OnTreeSelectionChanged(FRCControllerPanelListItem InItem , ESelectInfo::Type);` — OnSelectionChanged delegate for Actions List View
- L192 _public prototype_ `void SelectController(URCController* InController);` — Selects the Controller UI item corresponding to a given Controller UObject
- L195 _public prototype_ `void OnControllerAdded(const FName& InNewPropertyName);` — Responds to the selection of a newly created Controller. Resets UI state
- L198 _public prototype_ `void OnEmptyControllers();` — Responds to the removal of all Controllers. Resets UI state
- L200 _public prototype_ `void OnControllerContainerModified();`
- L205 _public prototype_ `void OnNotifyPreChangeProperties(const FPropertyChangedEvent& PropertyChangedEvent);` — Pre Change listener for Controllers, propagated via FNotifyHook associated with PropertyRowGenerator Invoked while the user is scrubbing float or Vector sliders in the UI
- L210 _public prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);` — Change listener for Controllers. Bound to the PropertyRowGenerator's delegate This is propagated to the corresponding Controller model (Virtual Property) for evaluating all associated Behaviours.
- L213 _public prototype_ `void OnControllerValueTypeChanged(URCVirtualPropertyBase* InController, EPropertyBagPropertyType InValueType);` — Called when a MultiController Value Type changes.
- L219 _public prototype_ `void OnControllerValueChanged(TSharedPtr<FRCControllerModel> InControllerModel, bool bInIsMultiController);` — Called when a Controller Value changes. Currently used to update handled controllers, in case of MultiControllers.
- L222 _public prototype_ `bool CreateAutoBindForProperty(TSharedPtr<const FRemoteControlProperty> InRemoteControlProperty);` — Creates a new Controller for the given Remote Control Property and also binds to it. Returns true if operation succeeded, false if nothing happened
- L225 _public member_ `TSharedPtr<IPropertyRowGenerator> PropertyRowGenerator;` — The row generator used to represent each Controller as a row, when used with STreeView
- L228 _public member_ `TWeakPtr<FRCControllerModel> SelectedControllerItemWeakPtr = nullptr;` — The currently selected Controller item (UI model)
- L231 _public member_ `TWeakPtr<SRCControllerPanel> ControllerPanelWeakPtr;` — The parent Controller Panel widget
- L234 _public member_ `TArray<TSharedPtr<FRCCategoryModel>> CategoryItems;` — List of Category (UI model) active in this widget
- L237 _public member_ `TArray<TSharedPtr<FRCControllerModel>> ControllerItems;` — List of Controllers (UI model) active in this widget
- L240 _public member_ `TArray<FRCControllerPanelListItem> RootItems;` — List of Controllers (UI model) that are in the root category
- L243 _public member_ `TSharedPtr<STreeView<FRCControllerPanelListItem>> TreeView;` — Tree View widget for representing our Controllers List
- L246 _public prototype_ `virtual void Reset() override;` — Refreshes the list from the latest state of the model
- L249 _public prototype_ `void UpdateRootItems();` — Updates the root item set from ControllerItems
- L252 _public prototype_ `void OnItemRemoved(const FRCControllerPanelListItem& InRemovedItem);` — Called to update metadata when things are removed.
- L255 _public prototype_ `virtual void BroadcastOnItemRemoved() override;` — Handles broadcasting of a successful remove item operation.
- L258 _public prototype_ `void ShowValueTypeHeaderColumn(bool bInShowColumn);` — Set the visibility of the Tree header the Value Type Column used for MultiControllers
- L261 _public prototype_ `void ShowFieldIdHeaderColumn(bool bInShowColumn);` — Set the visibility of the Tree header the Field Id Column
- L264 _public prototype_ `void AddColumn(const FName& InColumnName);` — Add a custom column
- L267 _public prototype_ `bool IsEntitySupported(FGuid ExposedEntityId);` — Checks whether the provided Entity can be used to create a Controller
- L270 _public member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L273 _public member_ `FRCMultiControllersState MultiControllers;` — Keeps track of current MultiControllers
- L275 _public member_ `bool bIsInMultiControllerMode = false;`
- L278 _public member_ `TSharedPtr<SHeaderRow> ControllersHeaderRow;` — Storing the header so we can add/remove columns
- L281 _public member_ `TArray<FName> CustomColumns;` — List of custom columns names

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeSelector/RCControllerTypeBase.h` (Private)


#### class `UE::RemoteControl::UI::Private::FRCControllerTypeBase`  
`class FRCControllerTypeBase`  
_L14-20_
- L17 _public typedef_ `using ItemType = TSharedPtr<FRCControllerPropertyInfo>;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RemoteControl` (scope `UE`)
- L9 _namespace_ `namespace UI` (scope `UE::RemoteControl`)
- L9 _namespace_ `namespace Private` (scope `UE::RemoteControl::UI`)
- L19 _delegate_ `DECLARE_DELEGATE_OneParam(FOnTypeSelected, ItemType) };`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeSelector/SRCControllerTypeList.h` (Private)


#### class `UE::RemoteControl::UI::Private::SRCControllerTypeList`  
`class SRCControllerTypeList : public SListView<TSharedPtr<FRCControllerPropertyInfo>>, public FRCControllerTypeBase`  
_L18-44_
- inherits: `SListView<TSharedPtr<FRCControllerPropertyInfo>>,FRCControllerTypeBase`
- L20 _private typedef_ `using Super = SListView<ItemType>;`
- L23 _public function_ `SLATE_BEGIN_ARGS(SRCControllerTypeList)`
- L25 _public prototype_ `SLATE_ARGUMENT(FOnTypeSelected, OnTypeSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<ItemType>& InTypes);`
- L30 _public prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L33 _private member_ `TArray<ItemType> Types;`
- L34 _private member_ `TArray<ItemType> FilteredTypes;`
- L35 _private member_ `FString Filter;`
- L36 _private member_ `FOnTypeSelected OnTypeSelectedDelegate;`
- L38 _private prototype_ `TSharedRef<ITableRow> GenerateRow(ItemType InItem, const TSharedRef<STableViewBase>& InOwnerTable);`
- L41 _private prototype_ `void UpdateItemsBasedOnFilter(const FString& InFilter, bool bInReFilter);` — Setting bReFilter to true will filter the already filtered list.
- L43 _private prototype_ `void OnTypeSelected(ItemType InItem, ESelectInfo::Type InSelectInfo);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace RemoteControl` (scope `UE`)
- L13 _namespace_ `namespace UI` (scope `UE::RemoteControl`)
- L13 _namespace_ `namespace Private` (scope `UE::RemoteControl::UI`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeSelector/SRCControllerTypeListEntry.h` (Private)


#### class `UE::RemoteControl::UI::Private::SRCControllerTypeListEntry`  
`class SRCControllerTypeListEntry : public STableRow<TSharedPtr<FRCControllerPropertyInfo>>, public FRCControllerTypeBase`  
_L14-25_
- inherits: `STableRow<TSharedPtr<FRCControllerPropertyInfo>>,FRCControllerTypeBase`
- L16 _private typedef_ `using Super = STableRow<ItemType>;`
- L19 _public function_ `SLATE_BEGIN_ARGS(SRCControllerTypeListEntry)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, ItemType InItem);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RemoteControl` (scope `UE`)
- L9 _namespace_ `namespace UI` (scope `UE::RemoteControl`)
- L9 _namespace_ `namespace Private` (scope `UE::RemoteControl::UI`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeSelector/SRCControllerTypeSelector.h` (Private)


#### class `UE::RemoteControl::UI::Private::SRCControllerTypeSelector`  
`class SRCControllerTypeSelector : public SCompoundWidget, public FRCControllerTypeBase`  
_L15-29_
- inherits: `SCompoundWidget,FRCControllerTypeBase`
- L18 _public function_ `SLATE_BEGIN_ARGS(SRCControllerTypeSelector)`
- L20 _public prototype_ `SLATE_ARGUMENT(FOnTypeSelected, OnTypeSelected) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TArray<ItemType>& InTypes);`
- L26 _private member_ `TSharedPtr<SRCControllerTypeList> TypeList;`
- L28 _private prototype_ `void OnFilterTextCommitted(const FText& InNewText, ETextCommit::Type InCommitInfo);`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace RemoteControl` (scope `UE`)
- L10 _namespace_ `namespace UI` (scope `UE::RemoteControl`)
- L10 _namespace_ `namespace Private` (scope `UE::RemoteControl::UI`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeTranslator/RCBoolHandler.h` (Private)


#### class `FRCBoolHandler`  
`class FRCBoolHandler : public FRCTypeHandler`  
_L7-23_
- inherits: `FRCTypeHandler`
- L10 _public prototype_ `virtual void Apply(const bool& InValue, URCVirtualPropertyBase* InController) override;`
- L11 _public prototype_ `virtual void Apply(const uint8& InValue, URCVirtualPropertyBase* InController) override;`
- L12 _public prototype_ `virtual void Apply(const double& InValue, URCVirtualPropertyBase* InController) override;`
- L13 _public prototype_ `virtual void Apply(const float& InValue, URCVirtualPropertyBase* InController) override;`
- L14 _public prototype_ `virtual void Apply(const int32& InValue, URCVirtualPropertyBase* InController) override;`
- L15 _public prototype_ `virtual void Apply(const int64& InValue, URCVirtualPropertyBase* InController) override;`
- L16 _public prototype_ `virtual void Apply(const FName& InValue, URCVirtualPropertyBase* InController) override;`
- L17 _public prototype_ `virtual void Apply(const FString& InValue, URCVirtualPropertyBase* InController) override;`
- L18 _public prototype_ `virtual void Apply(const FText& InValue, URCVirtualPropertyBase* InController) override;`
- L21 _protected prototype_ `static void UpdateValue(URCVirtualPropertyBase* InVirtualProperty, const bool InValue);`
- L22 _protected prototype_ `~FRCBoolHandler() = default;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeTranslator/RCFloatHandler.h` (Private)


#### class `FRCFloatHandler`  
`class FRCFloatHandler : public FRCTypeHandler`  
_L7-23_
- inherits: `FRCTypeHandler`
- L10 _public prototype_ `virtual void Apply(const bool& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L11 _public prototype_ `virtual void Apply(const uint8& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L12 _public prototype_ `virtual void Apply(const double& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L13 _public prototype_ `virtual void Apply(const float& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L14 _public prototype_ `virtual void Apply(const int32& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L15 _public prototype_ `virtual void Apply(const int64& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L16 _public prototype_ `virtual void Apply(const FName& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L17 _public prototype_ `virtual void Apply(const FString& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L18 _public prototype_ `virtual void Apply(const FText& InValue, URCVirtualPropertyBase* InVirtualProperty) override;`
- L21 _protected prototype_ `static void UpdateValue(URCVirtualPropertyBase* InVirtualProperty, const float InValue);`
- L22 _protected prototype_ `~FRCFloatHandler() = default;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeTranslator/RCStringHandler.h` (Private)


#### class `FRCStringHandler`  
`class FRCStringHandler : public FRCTypeHandler`  
_L7-23_
- inherits: `FRCTypeHandler`
- L10 _public prototype_ `virtual void Apply(const bool& InValue, URCVirtualPropertyBase* InController) override;`
- L11 _public prototype_ `virtual void Apply(const uint8& InValue, URCVirtualPropertyBase* InController) override;`
- L12 _public prototype_ `virtual void Apply(const double& InValue, URCVirtualPropertyBase* InController) override;`
- L13 _public prototype_ `virtual void Apply(const float& InValue, URCVirtualPropertyBase* InController) override;`
- L14 _public prototype_ `virtual void Apply(const int32& InValue, URCVirtualPropertyBase* InController) override;`
- L15 _public prototype_ `virtual void Apply(const int64& InValue, URCVirtualPropertyBase* InController) override;`
- L16 _public prototype_ `virtual void Apply(const FName& InValue, URCVirtualPropertyBase* InController) override;`
- L17 _public prototype_ `virtual void Apply(const FString& InValue, URCVirtualPropertyBase* InController) override;`
- L18 _public prototype_ `virtual void Apply(const FText& InValue, URCVirtualPropertyBase* InController) override;`
- L21 _protected prototype_ `static void UpdateValue(URCVirtualPropertyBase* InVirtualProperty, const FString& InValue);`
- L22 _protected prototype_ `~FRCStringHandler() = default;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeTranslator/RCTypeHandler.h` (Private)


#### class `FRCTypeHandler`  
`class FRCTypeHandler`  
_L7-24_
- L10 _public prototype_ `static void OnControllerPropertyModified(URCVirtualPropertyBase* InVirtualProperty);`
- L12 _public prototype_ `virtual void Apply(const bool& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L13 _public prototype_ `virtual void Apply(const uint8& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L14 _public prototype_ `virtual void Apply(const double& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L15 _public prototype_ `virtual void Apply(const float& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L16 _public prototype_ `virtual void Apply(const int32& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L17 _public prototype_ `virtual void Apply(const int64& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L18 _public prototype_ `virtual void Apply(const FName& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L19 _public prototype_ `virtual void Apply(const FString& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L20 _public prototype_ `virtual void Apply(const FText& InValue, URCVirtualPropertyBase* InVirtualProperty) = 0;`
- L23 _protected prototype_ `~FRCTypeHandler() = default;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Controller/TypeTranslator/RCTypeTranslator.h` (Private)


#### class `FRCTypeTranslator`  
`class FRCTypeTranslator`  
_L9-53_
- L12 _public prototype_ `static FRCTypeTranslator* Get();`
- L21 _public prototype_ `static void Translate(const URCVirtualPropertyBase* InSourceVirtualProperty, const TArray<URCVirtualPropertyBase*>& InTargetVirtualProperties);` — Conversion function: tries to use the Source Virtual Property current value to update the specified Target Virtual Properties values. Particularly useful for MultiControllers. @param InSourceVirtualProperty the virtual property providing the source value @param InTargetVirtualProperties the properties which will be updated using the source value
- L24 _public prototype_ `static EPropertyBagPropertyType GetOptimalValueType(const TArray<EPropertyBagPropertyType>& ValueTypes);` — Returns the "optimal" value type among the specified list
- L28 _private function_ `template<typename InValueType> static void Apply(const InValueType& Value, const TArray<URCVirtualPropertyBase*>& InTargetVirtualProperties)`
- L47 _private prototype_ `static FRCTypeHandler* CreateTypeHandler(EPropertyBagPropertyType InValueType);`
- L49 _private prototype_ `FRCTypeTranslator();`
- L51 _private member_ `inline static FRCTypeTranslator* TypeTranslatorSingleton = nullptr;`
- L52 _private member_ `inline static TMap<EPropertyBagPropertyType, FRCTypeHandler*> TypeHandlers;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Customizations/FPassphraseCustomization.h` (Private)


#### class `FPassphraseCustomization`  
`class FPassphraseCustomization : public IPropertyTypeCustomization`  
_L7-20_
- inherits: `IPropertyTypeCustomization`
- L10 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L15 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L17 _public function_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils ) override`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Customizations/NetworkAddressCustomization.h` (Private)


#### class `FNetworkAddressCustomization`  
`class FNetworkAddressCustomization : public IPropertyTypeCustomization`  
_L13-31_
- inherits: `IPropertyTypeCustomization`
- L22 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — It is just a convenient helpers which will be used to register our customization. When the propertyEditor module find our FRCNetworkAddress property, it will use this static method to instanciate our customization object.
- L26 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L28 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Customizations/RCAssetPathElementCustomization.h` (Private)


#### class `FRCAssetPathElementCustomization`  
`class FRCAssetPathElementCustomization : public IPropertyTypeCustomization`  
_L14-72_
- inherits: `IPropertyTypeCustomization`
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance(TSharedPtr<FRCSetAssetByPathBehaviorModelNew> InPathBehaviorModelNew);`
- L22 _public prototype_ `FRCAssetPathElementCustomization(TSharedPtr<FRCSetAssetByPathBehaviorModelNew> InPathBehaviorModelNew);`
- L25 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L26 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L31 _private prototype_ `void OnPathChanged();` — Called when the path change
- L34 _private prototype_ `ECheckBoxState IsChecked() const;` — Returns if the CheckBox is checked or not
- L37 _private prototype_ `void OnCheckStateChanged(ECheckBoxState InNewState);` — Callback called when you click on the CheckBox to enable/disable it
- L40 _private prototype_ `FReply OnGetAssetFromSelectionClicked();` — Callback called when you click on the arrow button next to the entries to retrieve the path of the selected Asset
- L43 _private prototype_ `bool IsCreateControllerButtonEnabled() const;` — Only lets you click the button if the path is empty.
- L46 _private prototype_ `FReply OnCreateControllerButtonClicked();` — Callback called when you click on the plus button next to the entries to create a controller associated with the current RC Input entry
- L49 _private prototype_ `int32 OnGetWidgetSwitcherIndex() const;` — Retrieve the current widget switcher index
- L51 _private prototype_ `FString GetSelectedAssetPath() const;`
- L53 _private prototype_ `FString GetSelectedAssetPath_ContentBrowser() const;`
- L55 _private prototype_ `FString GetSelectedAssetPath_EntityList() const;`
- L57 _private prototype_ `TSharedRef<SWidget> GetPathSelectorMenuContent();`
- L59 _private prototype_ `void SetAssetPathFromContentBrowser();`
- L61 _private prototype_ `void SetAssetPathFromEntityList();`
- L63 _private prototype_ `void SetAssetFromPath(FString InPath);`
- L66 _private member_ `TWeakPtr<FRCSetAssetByPathBehaviorModelNew> PathBehaviorModelNewWeak;`
- L67 _private member_ `TSharedPtr<SWidget> PathWidget;`
- L68 _private member_ `TSharedPtr<IPropertyUtilities> PropertyUtilities;`
- L69 _private member_ `TSharedPtr<IPropertyHandle> ArrayEntryHandle;`
- L70 _private member_ `TSharedPtr<IPropertyHandle> IsInputHandle;`
- L71 _private member_ `TSharedPtr<IPropertyHandle> PathHandle;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Customizations/RemoteControlEntityCustomization.h` (Private)


#### class `FRemoteControlEntityCustomization`  
`class FRemoteControlEntityCustomization : public IDetailCustomization`  
_L17-56_
- inherits: `IDetailCustomization`
- desc: Implements a details panel customization for remote control entities.
- L20 _public prototype_ `FRemoteControlEntityCustomization();`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L26 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L30 _private prototype_ `void CreateRangeWidget(URemoteControlPreset* Preset, const FGuid& DisplayedEntityId, IDetailLayoutBuilder& LayoutBuilder, IDetailCategoryBuilder& CategoryBuilder);` — Create a widget that handles modifying the min and max properties.
- L33 _private prototype_ `void CreateBindingWidget(const FRemoteControlEntity* RCEntity, IDetailLayoutBuilder& LayoutBuilder, IDetailCategoryBuilder& CategoryBuilder) const;` — Create a widget that displays what's the entity currently bound to.
- L36 _private prototype_ `void OnMetadataKeyCommitted(const FText& Text, ETextCommit::Type Type, FName MetadataKey);` — Handler called upon modifying the metadata of an exposed entity.
- L39 _private prototype_ `FRemoteControlEntity* GetEntityPtr();` — Get a pointer to the entity currently being displayed in the details view.
- L42 _private prototype_ `const FRemoteControlEntity* GetEntityPtr() const;` — Get a const pointer to the entity currently being displayed in the details view.
- L45 _private prototype_ `FText GetMetadataValue(FName Key) const;` — Get a value from the metadata map of the entity.
- L48 _private prototype_ `void GeneratePropertyRows(IDetailLayoutBuilder& DetailBuilder, IDetailCategoryBuilder& CategoryBuilder);` — Generate property row widgets
- L52 _private member_ `TSharedPtr<FStructOnScope> DisplayedEntity;` — Entity currently being displayed.
- L55 _private member_ `TMap<FName, FOnCustomizeMetadataEntry> MetadataCustomizations;` — Map of metadata key to initializer delegate.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Filters/SRCFilterBar.h` (Private)


#### class `URCFilterBarContext`  
`class URCFilterBarContext : public UObject`  
_L32-39_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: ToolMenuContext that is used to create the Add Filter Menu
- L37 _public member_ `TSharedPtr<FFilterCategory> MenuExpansion;`
- L38 _public member_ `FOnPopulateAddRCFilterMenu PopulateFilterMenu;`

#### class `SRCFilterBar`  
`template<typename FilterType> class SRCFilterBar : public SBasicFilterBar<FilterType>`  
_L45-787_
- inherits: `SBasicFilterBar<FilterType>`
- desc: A custom filter bar to handle Remote Control Filtering System.
- L49 _public typedef_ `using FOnFilterChanged = typename SBasicFilterBar<FilterType>::FOnFilterChanged;`
- L51 _public function_ `SLATE_BEGIN_ARGS(SRCFilterBar) : _UseDefaultEntityFilters(true)`
- L56 _public function_ `SLATE_EVENT(SRCFilterBar<FilterType>::FOnFilterChanged, OnFilterChanged) SLATE_EVENT(FOnExtendAddFilterMenu, OnExtendAddFilterMenu) SLATE_ARGUMENT(TArray<TSharedRef<FFilterBase<FilterType>>>, CustomFilters) SLATE_ARGUMENT(TArray<TSharedRef<FCustomTypeFilterData>>, CustomTypeFilters) SLATE_ARGUMENT(bool, UseDefaultEntityFilters) SLATE_END_ARGS() void Construct(const FArguments& InArgs)` — Delegate for when filters have changed
- L183 _public function_ `FRCFilter GetCombinedBackendFilter() const` — Use this function to get an FRCFilter that represents all the Asset & Entity Type filters that are currently active.
- L202 _public function_ `virtual void RemoveAllFilters() override` — Remove all filters from the filter bar, while disabling any active ones
- L214 _protected function_ `TSharedRef<FEntityFilter> AddEntityFilter(const TSharedPtr<FCustomTypeFilterData>& CustomTypeFilter)` — Add an RC Filter to the list of filters, making it "Active" but not enabled
- L225 _protected function_ `bool HasAnyFilters() const` — Returns true if any filters are applied
- L231 _protected function_ `void RemoveEntityFilter(const TSharedPtr<FCustomTypeFilterData>& CustomTypeFilter, bool ExecuteOnFilterChanged = true)` — Attempts to remove the given filter from list.
- L258 _protected function_ `void OnResetFilters()` — Called when reset filters option is pressed
- L264 _protected function_ `void CreateEntityTypeFilters()` — Create the default set of EClassCastFlags Filters provided with the widget if requested
- L388 _protected function_ `void UpdateEntityTypeCategories()` — Normalizes the CustomTypeFilters to their respective categories.
- L416 _protected function_ `void CreateFiltersMenuCategory(FToolMenuSection& Section, const TArray<TSharedPtr<FCustomTypeFilterData>> CustomTypeFilterDatas) const` — Handler for when the add filter menu is populated by a category
- L439 _protected function_ `void CreateFiltersMenuCategory(UToolMenu* InMenu, const TArray<TSharedPtr<FCustomTypeFilterData>> CustomTypeFilterDatas) const` — Handler for when the add filter menu is populated by a category
- L445 _protected function_ `virtual TSharedRef<SWidget> MakeAddFilterMenu() override` — Handler for when the add filter button was clicked
- L479 _protected function_ `virtual void PopulateAddFilterMenu(UToolMenu* Menu, TSharedPtr<FFilterCategory> MenuExpansion, FOnFilterEntityType OnFilterEntityType)` — Handler to Populate the Add Filter Menu. Use OnFilterEntityType in Subclasses to add classes to the exclusion list
- L647 _protected function_ `void FilterByTypeClicked(TSharedPtr<FCustomTypeFilterData> CustomTypeFilterData)` — Handler for when filter by type is selected
- L664 _protected function_ `bool IsEntityTypeInUse(TSharedPtr<FCustomTypeFilterData> EntityType) const` — Handler to determine the "checked" state of class filter in the filter dropdown
- L678 _protected function_ `void FilterByTypeCategoryClicked(TSharedPtr<FFilterCategory> TypeCategory, TArray<TSharedPtr<FCustomTypeFilterData>> EntityTypes)` — Handler for when filter by type category is selected
- L705 _protected function_ `ECheckBoxState IsEntityTypeCategoryChecked(TSharedPtr<FFilterCategory> TypeCategory, TArray<TSharedPtr<FCustomTypeFilterData>> EntityTypes) const` — Handler to determine the "checked" state of an type category in the filter dropdown
- L739 _protected function_ `bool IsEntityTypeCategoryInUse(TSharedPtr<FFilterCategory> TypeCategory, TArray<TSharedPtr<FCustomTypeFilterData>> EntityTypes) const` — Function to check if a given type category is in use
- L755 _private function_ `void PopulateFilterData(EEntityTypeCategories::Type InEntityTypeCategory, FFieldClass* InEntityType, FText InFilterDisplayName, const FName& InCustomTypeName = NAME_None)` — Populates CustomTypeFilters from Entity Type and its Category.
- L762 _private function_ `void PopulateFilterData(TWeakPtr<IAssetTypeActions> InAssetTypeAction)` — Populates CustomTypeFilters from Asset Type Action.
- L771 _protected member_ `TArray<TSharedRef<FEntityFilter>> EntityFilters;` — A copy of all active Entity Filters in this->EntityFilters for convenient access.
- L774 _protected member_ `TArray<TSharedRef<FCustomTypeFilterData>> CustomTypeFilters;` — List of all custom entity filters.
- L777 _protected member_ `TMap<EEntityTypeCategories::Type, TSharedPtr<FFilterCategory>> TypeFilterCategories;` — A map of property type with its corresponding filter category.
- L780 _protected member_ `TMap<EAssetTypeCategories::Type, TSharedPtr<FFilterCategory>> AssetFilterCategories;` — A map of asset type with its corresponding filter category.
- L783 _protected member_ `TSet<FString> AssetTypesToIgnore = { "C++` — A list of Asset Types to ignore.
- L786 _protected member_ `bool bUseDefaultEntityFilters;` — Whether the filter bar provides the default RC Filters

#### class `SRCFilterBar::FEntityFilter`  
`class FEntityFilter`  
_L93-178_
- desc: A custom data model to represent each type of filters we have.
- L97 _public function_ `FEntityFilter(TSharedRef<FCustomTypeFilterData> InCustomTypeFilter, FOnFilterChanged InOnFilterChanged) : bEnabled(false) , CustomTypeFilter(InCustomTypeFilter) , OnFilterChanged(InOnFilterChanged)`
- L105 _public function_ `void GetBackendFilter(FRCFilter& OutFilter) const` — Returns contribution of this filter to the combined filter
- L121 _public function_ `const TSharedPtr<FCustomTypeFilterData>& GetCustomTypeFilterData() const` — Gets the asset type actions associated with this filter
- L127 _public function_ `FText GetFilterDisplayName() const` — Returns the display name for this filter
- L138 _public function_ `FString GetFilterName() const` — Returns the actual name of this filter.
- L149 _public function_ `bool IsEnabled() const` — Returns true if this filter contributes to the combined filter
- L155 _public function_ `void SetEnabled(bool InEnabled, bool InExecuteOnFilterChanged = true)` — Sets whether or not this filter is applied to the combined filter
- L171 _protected member_ `bool bEnabled;` — Whether this filter is active or not.
- L174 _protected member_ `TSharedPtr<FCustomTypeFilterData> CustomTypeFilter;` — View model for this filter describing the nature of this filter.
- L177 _protected member_ `FOnFilterChanged OnFilterChanged;` — Invoked when the filter toggled

#### struct `SRCFilterBar::CreateEntityTypeFilters::FCompareIAssetTypeActions`  
`struct FCompareIAssetTypeActions`  
_L350-356_
- desc: Sort the list
- L352 _public function_ `FORCEINLINE bool operator()(const TWeakPtr<IAssetTypeActions>& A, const TWeakPtr<IAssetTypeActions>& B) const`

#### struct `SRCFilterBar::PopulateAddFilterMenu::FCategoryMenu`  
`struct FCategoryMenu`  
_L482-495_
- desc: A local struct to describe a category in the filter menu
- L485 _public member_ `TArray<TSharedPtr<FCustomTypeFilterData>> EntityTypes;` — The Property Type that belong to this category
- L488 _public member_ `FName SectionExtensionHook;` — Menu section
- L489 _public member_ `FText SectionHeading;`
- L491 _public function_ `FCategoryMenu(const FName& InSectionExtensionHook, const FText& InSectionHeading) : SectionExtensionHook(InSectionExtensionHook) , SectionHeading(InSectionHeading)`

#### Free symbols / members of external scopes

- L20 _macro_ `#define LOCTEXT_NAMESPACE "RCFilterBar"`
- L25 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterEntityType, FFieldClass* );` — Delegate that subclasses can use to specify classes to not include in this filter Returning false for a class will prevent it from showing up in the add filter dropdown
- L25 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnFilterEntityType, FFieldClass* );` — Delegate that subclasses can use to specify classes to not include in this filter Returning false for a class will prevent it from showing up in the add filter dropdown
- L28 _delegate_ `DECLARE_DELEGATE_ThreeParams(FOnPopulateAddRCFilterMenu, UToolMenu*, TSharedPtr<FFilterCategory>, FOnFilterEntityType) UCLASS() class URCFilterBarContext : public UObject { GENERATED_BODY() public: TSharedPtr<FFilterCategory> MenuExpansion; FOnPopulateAddRCFilterMenu PopulateFilterMenu; };` — Delegate used by SRCFilterBar to populate the add filter menu
- L303 _function_ `` (scope `SRCFilterBar::CreateEntityTypeFilters`)
- L455 _function_ `` (scope `SRCFilterBar::MakeAddFilterMenu`)
- L569 _function_ `FExecuteAction::CreateSP(this, &SRCFilterBar<FilterType>::OnResetFilters), FCanExecuteAction::CreateLambda([this]() { return HasAnyFilters(); })) );` (scope `SRCFilterBar::PopulateAddFilterMenu`)
- L619 _function_ `CategoryToMenuMap.KeySort([](const TSharedPtr<FFilterCategory>& A, const TSharedPtr<FFilterCategory>& B) { return A->Title.CompareTo(B->Title) < 0; });` (scope `SRCFilterBar::PopulateAddFilterMenu`) — Sort by category name so that we add the submenus in alphabetical order

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Filters/SRCPanelFilter.h` (Private)


#### class `SRCPanelFilter`  
`class SRCPanelFilter : public SRCFilterBar<FEntityFilterType>`  
_L16-43_
- inherits: `SRCFilterBar<FEntityFilterType>`
- desc: A custom list of filters currently applied to an Remote Control Panel.
- L20 _public typedef_ `using FOnFilterChanged = typename SRCFilterBar<FEntityFilterType>::FOnFilterChanged;`
- L22 _public function_ `SLATE_BEGIN_ARGS(SRCPanelFilter)`
- L26 _public prototype_ `SLATE_EVENT(FOnFilterChanged, OnFilterChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Delegate for when filters have changed
- L34 _public prototype_ `void SaveSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString) const;` — Saves any settings to config that should be persistent between editor sessions
- L37 _public prototype_ `void LoadSettings(const FString& IniFilename, const FString& IniSection, const FString& SettingsString);` — Loads any settings to config that should be persistent between editor sessions
- L42 _private member_ `FOnFilterChanged OnFilterChanged;` — Delegate for when filters have changed

#### Free symbols / members of external scopes

- L11 _typedef_ `using FEntityFilterType = TSharedRef<const SRCPanelTreeNode>;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/MenuContext/RemoteControlPanelMenuContext.h` (Private)


#### class `URemoteControlPanelMenuContext`  
`class URemoteControlPanelMenuContext : public UObject`  
_L10-17_
- reflection: `UCLASS()`
- inherits: `UObject`
- L16 _public member_ `TWeakPtr<SRemoteControlPanel> RemoteControlPanel;` — RemoteControlPanel of this context

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Panels/SRCDockPanel.h` (Private)


#### enum `EToolbar`  
`enum EToolbar`  
_L13-23_
- L16 _public enumerator_ `Left` — Left toolbar.
- L19 _public enumerator_ `Right` — Right toolbar.
- L22 _public enumerator_ `Center` — Center toolbar.

#### class `SRCDockPanel`  
`class SRCDockPanel : public SBorder`  
_L28-58_
- inherits: `SBorder`
- desc: A custom slate widget representing a dockable panel on RC Panel.
- L34 _public function_ `SLATE_BEGIN_ARGS(SRCDockPanel) : _Content()`
- L38 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L48 _protected member_ `TAttribute<bool> bIsFooterEnabled;` — Holds whether the footer panel is enabled or not.
- L51 _protected member_ `TAttribute<bool> bIsHeaderEnabled;` — Holds whether the header panel is enabled or not.
- L54 _protected member_ `TSharedPtr<SSplitter> ContentPanel;` — Holds the entire content panel.
- L57 _protected member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.

#### class `SRCMajorPanel`  
`class SRCMajorPanel : public SRCDockPanel`  
_L63-137_
- inherits: `SRCDockPanel`
- desc: A custom slate widget representing a major panel on RC Panel.
- L69 _public function_ `SLATE_BEGIN_ARGS(SRCMajorPanel) : _EnableFooter(false) , _EnableHeader(true) , _HeaderLabel(FText::GetEmpty()) , _Orientation(Orient_Vertical) , _ChildOrientation(Orient_Horizontal)`
- L77 _public prototype_ `SLATE_ARGUMENT(bool, EnableFooter) SLATE_ARGUMENT(bool, EnableHeader) SLATE_ATTRIBUTE(FText, HeaderLabel) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_ARGUMENT(EOrientation, ChildOrientation) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L100 _public prototype_ `virtual int32 AddPanel(TSharedRef<SWidget> InPanel, const TAttribute<float> InDesiredSize, const bool bResizable = true);` — Adds the given panel to the children. @param InPanel The panel widget. @param InDesiredSize The desired size for the Panel widget @param bResizable Can the slot be resize by the user @return the index of the newly added slot. Slot can be accessed using this index by calling SRCMajorPanel::GetSplitterSlotAt(Index)
- L107 _public prototype_ `const TSharedRef<SWidget>& GetContent() const;` — Gets the content of this panel @return The widget used as content for the panel
- L110 _public prototype_ `void ClearContent();` — Clears out the content for the panel
- L113 _public prototype_ `void AddFooterToolItem(EToolbar InToolbar, TSharedRef<SWidget> InWidget);` — Adds widgets to the specified footer toolbar (Left or Right).
- L116 _public function_ `FSimpleDelegate& OnSplitterFinishedResizing()` — Delegate called whenever the splitter is finished resizing
- L119 _public prototype_ `SSplitter::FSlot& GetSplitterSlotAt(const int32 InIndex) const;` — Returns the slot at the specified index
- L124 _private member_ `TSharedPtr<SHorizontalBox> LeftToolbar;` — Actual toolbar widget located left to the footer.
- L127 _private member_ `TSharedPtr<SHorizontalBox> RightToolbar;` — Actual toolbar widget located right to the footer.
- L130 _private member_ `TSharedPtr<SHorizontalBox> CenterToolbar;` — Actual toolbar widget located Center to the footer.
- L133 _private member_ `TSharedPtr<SSplitter> Children;` — Holds the entire child panels.
- L136 _private member_ `FSimpleDelegate OnSplitterFinishedResizingDelegate;` — Delegate called whenever the splitter is finished resizing

#### class `SRCMinorPanel`  
`class SRCMinorPanel : public SRCDockPanel`  
_L142-215_
- inherits: `SRCDockPanel`
- desc: A custom slate widget representing a minor panel on RC Panel.
- L148 _public function_ `SLATE_BEGIN_ARGS(SRCMinorPanel) : _Content() , _EnableFooter(false) , _EnableHeader(true) , _HeaderLabel(FText::GetEmpty()) , _Orientation(Orient_Vertical)`
- L155 _public prototype_ `SLATE_DEFAULT_SLOT(FArguments, Content) SLATE_ARGUMENT(bool, EnableFooter) SLATE_ARGUMENT(bool, EnableHeader) SLATE_ATTRIBUTE(FText, HeaderLabel) SLATE_ARGUMENT(EOrientation, Orientation) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L175 _public prototype_ `virtual void SetContent(TSharedRef<SWidget> InContent );` — Sets the content for this panel @param	InContent	The widget to use as content for the panel
- L182 _public prototype_ `const TSharedRef<SWidget>& GetContent() const;` — Gets the content for this panel @return The widget used as content for the panel
- L185 _public prototype_ `void ClearContent();` — Clears out the content for the panel
- L188 _public prototype_ `void AddFooterToolbarItem(EToolbar InToolbar, TSharedRef<SWidget> InWidget);` — Adds widgets to the specified footer toolbar (Left or Right).
- L191 _public prototype_ `void AddHeaderToolbarItem(EToolbar InToolbar, TSharedRef<SWidget> InWidget);` — Adds widgets to the specified header toolbar (Left or Right).
- L194 _public prototype_ `void ClearHeaderToolbarItems() const;` — Clear toolbar items
- L199 _private member_ `TSharedPtr<SHorizontalBox> LeftFooterToolbar;` — Actual toolbar widget located left to the footer.
- L202 _private member_ `TSharedPtr<SHorizontalBox> RightFooterToolbar;` — Actual toolbar widget located right to the footer.
- L205 _private member_ `TSharedPtr<SHorizontalBox> LeftHeaderToolbar;` — Actual toolbar widget located left to the header.
- L208 _private member_ `TSharedPtr<SHorizontalBox> RightHeaderToolbar;` — Actual toolbar widget located right to the header.
- L211 _private member_ `TSharedPtr<SHorizontalBox> CenterHeaderToolbar;` — Actual toolbar widget located Center to the header.
- L214 _private member_ `int32 ContentIndex = 0;` — Index of the Content slot

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/RCPanelWidgetRegistry.h` (Private)


#### enum `ERCFindNodeMethod`  
`enum class ERCFindNodeMethod`  
_L14-18_
- L16 _public enumerator_ `Name` — Find a node by providing its property name.
- L17 _public enumerator_ `Path` — Find a node by providing a property path.

#### struct `FRCTreeNodeFinderHandler`  
`struct FRCTreeNodeFinderHandler`  
_L25-29_
- L27 _public member_ `FRCTreeNodeFinderIsException IsExceptionFunc;`
- L28 _public member_ `FRCTreeNodeFinderFunction FinderFunction;`

#### class `FRCPanelWidgetRegistry`  
`class FRCPanelWidgetRegistry : public TSharedFromThis<FRCPanelWidgetRegistry>`  
_L31-104_
- inherits: `TSharedFromThis<FRCPanelWidgetRegistry>`
- L34 _public prototype_ `FRCPanelWidgetRegistry();`
- L35 _public prototype_ `~FRCPanelWidgetRegistry();`
- L43 _public prototype_ `TSharedPtr<IDetailTreeNode> GetObjectTreeNode(UObject* InObject, const FString& InField, ERCFindNodeMethod InFindMethod);` — Get a detail tree node for a given object and property. @param InObject the object used to generate the detail row. @param InField a string specifying which field to generate a row for. @param InFindMethod whether the field parameter is a path or a field name.
- L51 _public prototype_ `TSharedPtr<IDetailTreeNode> GetStructTreeNode(const TSharedPtr<FStructOnScope>& InStruct, const FString& InField, ERCFindNodeMethod InFindMethod);` — Get a detail tree node for a given struct and field. @param InStruct the struct used to generate the detail row. @param InField a string specifying which field to generate a row for. @param InFindMethod whether the field parameter is a path or a field name.
- L56 _public prototype_ `void Refresh(UObject* InObject, bool bForceRefresh = false);` — Update the generator for a given object.
- L61 _public prototype_ `void Refresh(const TSharedPtr<FStructOnScope>& InStruct);` — Update the generator for a given struct.
- L66 _public prototype_ `void UpdateGeneratorAndTreeCache(UObject* InOldObject, UObject* InNewObject, FString InPath);` — Update the InOldOObject generator and the tree cache with the InNewObject.
- L71 _public prototype_ `void Clear();` — Clear the registry and its cache.
- L76 _public function_ `FOnObjectsRefreshed& OnObjectRefreshed()` — Get the on object refresh delegate.
- L84 _private prototype_ `bool IsNDisplayObject(UObject* InObject, const FString& InField = FString(), ERCFindNodeMethod InFindMethod = ERCFindNodeMethod::Path);` — Special handlers for ndisplay root actor and its details customizations
- L85 _private prototype_ `TSharedPtr<IDetailTreeNode> FindNDisplayTreeNode(UObject* InObject, const FString& InField, ERCFindNodeMethod InFindMethod);`
- L86 _private prototype_ `void OnRowsRefreshed(TSharedPtr<IPropertyRowGenerator> Generator);`
- L88 _private prototype_ `TSharedPtr<IPropertyRowGenerator> CreateGenerator(UObject* InObject);` — Create a property row generator
- L90 _private prototype_ `void ReplaceGeneratorObject(UObject* InOldObject, UObject* InNewObject);` — Replace old object if found with new object
- L92 _private prototype_ `void ReplaceTreeCacheObject(UObject* InOldObject, UObject* InNewObject, FString InPath);` — Update Cached tree, main use when switching between different world needs to be called after ReplaceGeneratorObject
- L95 _private member_ `TMap<TWeakObjectPtr<UObject>, TSharedPtr<IPropertyRowGenerator>> ObjectToRowGenerator;` — Map of objects to row generator, used to have one row generator per object.
- L97 _private member_ `TMap<TSharedPtr<FStructOnScope>, TSharedPtr<IPropertyRowGenerator>> StructToRowGenerator;` — Map of struct on scope to row generator, used to have one row generator per struct ptr.
- L99 _private member_ `TMap<TPair<TWeakObjectPtr<UObject>, FString>, TWeakPtr<IDetailTreeNode>> TreeNodeCache;` — Cache of Object&Field to tree nodes.
- L101 _private member_ `TArray<FRCTreeNodeFinderHandler> SpecialTreeNodeHandlers;` — List of tree node finder handlers for certain type
- L103 _private member_ `FOnObjectsRefreshed OnObjectRefreshedDelegate;` — Called when a generator gets refreshed. (ie. forcefully refreshed by a customization)

#### Free symbols / members of external scopes

- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectsRefreshed, const TArray<UObject*>&);`
- L20 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectsRefreshed, const TArray<UObject*>&);`
- L23 _typedef_ `using FRCTreeNodeFinderIsException = TFunction< bool(UObject* , const FString& , ERCFindNodeMethod ) >;` — Local special case handlers to generate widgets to be displayed
- L24 _typedef_ `using FRCTreeNodeFinderFunction = TFunction< TSharedPtr<IDetailTreeNode>(UObject* , const FString& , ERCFindNodeMethod ) >;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/RCUIHelpers.h` (Private)


#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace RCUIHelpers` (scope `UE`)
- L25 _prototype_ `FLinearColor GetFieldClassTypeColor(const FProperty* InProperty);` (scope `UE::RCUIHelpers`) — GetFieldClassTypeColor Fetches the editor color associated with a given Unreal Type (FProperty) Used to provide color coding in the Remote Control Logic Actions panel
- L30 _prototype_ `FName GetFieldClassDisplayName(const FProperty* InProperty);` (scope `UE::RCUIHelpers`) — GetFieldClassDisplayName Fetches the display name associated with a given Unreal Type (FProperty)
- L38 _prototype_ `TSharedPtr<IDetailTreeNode> GetDetailTreeNodeForVirtualProperty(TObjectPtr<URCVirtualPropertySelfContainer> InVirtualPropertySelfContainer, TSharedPtr<IPropertyRowGenerator>& OutPropertyRowGenerator);` (scope `UE::RCUIHelpers`) — GetDetailTreeNodeForVirtualProperty Given a Virtual Property this function generates the corresponding Detail Tree Node. The Property Row Generator used to create this is also set as an output parameter.
- L46 _prototype_ `TSharedRef<SWidget> GetGenericFieldWidget(const TSharedPtr<IDetailTreeNode> DetailTreeNode, TSharedPtr<IPropertyHandle>* OutPropertyHandle = nullptr, bool bFocusInputWidget = false);` (scope `UE::RCUIHelpers`) — GetGenericFieldWidget Constructs a widget representing a generic property using an input detail tree node Optionally returns the corresponding property handle as an output parameter.
- L56 _prototype_ `bool FindFocusableWidgetAndSetKeyboardFocus(const TSharedRef< SWidget> InWidget);` (scope `UE::RCUIHelpers`) — FindFocusableWidgetAndSetKeyboardFocus Searches the entire widget hierarchy of a given widget for a focusable child item and sets the focus on it If the input widget is itself focusable, then we simply set the focus on it and return
- L64 _prototype_ `TSharedRef<SWidget> GetTypeColorWidget(const FProperty* InProperty);` (scope `UE::RCUIHelpers`) — GetTypeColorWidget Generates a Type Color widget which provides a color coding guide for the user given a desired color Used to provide a consistent look for the type color widget across various Remote Control Logic panels
- L73 _prototype_ `TSharedRef<SWidget> GetTypeColorWidget(const FLinearColor& InTypeColor, const FText& InTypeDescription);` (scope `UE::RCUIHelpers`) — GetTypeColorWidget Generates a Type Color widget which provides a color coding guide for the user given a desired color Used to provide a consistent look for the type color widget across various Remote Control Logic panels This is the direct version which takes a color and description, instead of extracting them from a property.
- L76 _prototype_ `UObject* GetEntityOwner(const TSharedPtr<const FRemoteControlEntity>& InEntity);` (scope `UE::RCUIHelpers`) — Retrieves the entity owner for a given entity. If the entity is bound to an actor's subobject, the actor will be returned.
- L79 _prototype_ `FText GenerateControllerDescriptionFromEntity(const TSharedPtr<const FRemoteControlEntity>& InEntity);` (scope `UE::RCUIHelpers`) — Generates the description to use for a new or existing controller, from the given property
- L82 _prototype_ `URCController* CreateControllerFromEntity(URemoteControlPreset* InPreset, const TSharedPtr<const FRemoteControlProperty>& InRemoteControlProperty);` (scope `UE::RCUIHelpers`) — Automatically creates a controller for a given remote control property

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/RemoteControlExposeMenuStyle.h` (Private)


#### class `FRemoteControlExposeMenuStyle`  
`class FRemoteControlExposeMenuStyle`  
_L11-40_
- L17 _public prototype_ `static void Initialize();` — Initialize the style set.
- L22 _public prototype_ `static void Shutdown();` — Shutdown the style set.
- L27 _public prototype_ `static TSharedPtr<ISlateStyle> Get();` — Static getter for the style set.
- L32 _public prototype_ `static FName GetStyleSetName();` — Static getter for the style set name.
- L35 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);` — Get a path to the module's resources folder.
- L39 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;` — Holds the style set.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/RemoteControlPanelStyle.h` (Private)


#### class `FRemoteControlPanelStyle`  
`class FRemoteControlPanelStyle`  
_L9-40_
- L15 _public prototype_ `static void Initialize();` — Initialize the style set.
- L20 _public prototype_ `static void Shutdown();` — Shutdown the style set.
- L25 _public prototype_ `static TSharedPtr<ISlateStyle> Get();` — Static getter for the style set.
- L30 _public prototype_ `static FName GetStyleSetName();` — Static getter for the style set name.
- L33 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);` — Get a path to the module's resources folder.
- L35 _private prototype_ `static void SetupPanelStyles(TSharedRef<FSlateStyleSet> InStyle);`
- L39 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;` — Holds the style set.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCHeaderRow.h` (Private)


#### class `SRCHeaderRow`  
`class SRCHeaderRow : public SHeaderRow`  
_L14-167_
- inherits: `SHeaderRow`
- desc: A custom Header Row to hide entry in the SubMenu to Hide/Show the Header.
- L96 _public function_ `static FColumn::FArguments Column(const FName& InColumnId)`
- L103 _public function_ `SLATE_BEGIN_ARGS(SRCHeaderRow) : _CanSelectGeneratedColumn(false) , _HiddenColumnsList({})`
- L108 _public prototype_ `SLATE_STYLE_ARGUMENT(FHeaderRowStyle, Style) SLATE_SUPPORTS_SLOT_WITH_ARGS(FColumn) SLATE_ARGUMENT(bool, CanSelectGeneratedColumn) SLATE_ARGUMENT(TArray<FName>, HiddenColumnsList) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L123 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L131 _private prototype_ `SHeaderRow::FColumn* CreateHeaderRowColumn(const FColumn InColumn);` — Creates and returns a customized column object.
- L136 _private prototype_ `void RegenerateOverriddenWidgets();` — Overridden method that is used to regenerate the custom column(s).
- L141 _private prototype_ `void OnOverrideGenerateSelectColumnsSubMenu(FMenuBuilder& InSubMenuBuilder);` — Overridden method that is called when the user perform right click on custom column(s).
- L146 _private prototype_ `void ToggleOverriddenGeneratedColumn(FName ColumnId);` — Toggles the visibility of the overridden custom column(s).
- L151 _private prototype_ `ECheckBoxState GetOverriddenGeneratedColumnCheckedState(FName ColumnId) const;` — Rretrieves the check box state of the overridden custom column(s).
- L154 _private prototype_ `void StoreHiddenColumnsSettings();` — Save the current settings for shown/hidden columns to Remote Control Config
- L161 _private member_ `TIndirectArray<FColumn> Columns;` — Holds the array of overridden custom column(s).
- L166 _private member_ `bool bOverrideCanSelectGeneratedColumn;` — Determines whether the column can be shown in the context menu or not.

#### class `SRCHeaderRow::FColumn`  
`class FColumn`  
_L18-94_
- L22 _public function_ `SLATE_BEGIN_ARGS(FColumn) : _ColumnId() , _DefaultLabel() , _FillWidth(1.f) , _FixedWidth() , _HAlignHeader(HAlign_Fill) , _VAlignHeader(VAlign_Fill) , _HeaderContentPadding() , _HAlignCell(HAlign_Fill) , _VAlignCell(VAlign_Fill)`
- L34 _public function_ `SLATE_ARGUMENT(FName, ColumnId) SLATE_ATTRIBUTE(FText, DefaultLabel) SLATE_ATTRIBUTE(float, FillWidth) SLATE_ARGUMENT(TOptional<float>, FixedWidth) SLATE_ARGUMENT(EHorizontalAlignment, HAlignHeader) SLATE_ARGUMENT(EVerticalAlignment, VAlignHeader) SLATE_ARGUMENT(TOptional<FMargin>, HeaderContentPadding) SLATE_ARGUMENT(EHorizontalAlignment, HAlignCell) SLATE_ARGUMENT(EVerticalAlignment, VAlignCell) SLATE_ATTRIBUTE(bool, ShouldGenerateWidget) SLATE_ATTRIBUTE(bool, ShouldGenerateSubMenuEntry) SLATE_END_ARGS() FColumn(const FArguments& InArgs) : ColumnId(InArgs._ColumnId) , DefaultText(InArgs._DefaultLabel) , Width(1.0f) , DefaultWidth(1.0f) , SizeRule(EColumnSizeMode::Fill) , HeaderHAlignment(InArgs._HAlignHeader) , HeaderVAlignment(InArgs._VAlignHeader) , HeaderContentPadding(InArgs._HeaderContentPadding) , CellHAlignment(InArgs._HAlignCell) , CellVAlignment(InArgs._VAlignCell) , ShouldGenerateWidget(InArgs._ShouldGenerateWidget) , ShouldGenerateSubMenuEntry(InArgs._ShouldGenerateSubMenuEntry) , bIsVisible(true)`
- L81 _public member_ `FName ColumnId;`
- L82 _public member_ `TAttribute<FText> DefaultText;`
- L83 _public member_ `TAttribute<float> Width;`
- L84 _public member_ `float DefaultWidth;`
- L85 _public member_ `EColumnSizeMode::Type SizeRule;`
- L86 _public member_ `EHorizontalAlignment HeaderHAlignment;`
- L87 _public member_ `EVerticalAlignment HeaderVAlignment;`
- L88 _public member_ `TOptional<FMargin> HeaderContentPadding;`
- L89 _public member_ `EHorizontalAlignment CellHAlignment;`
- L90 _public member_ `EVerticalAlignment CellVAlignment;`
- L91 _public member_ `TAttribute<bool> ShouldGenerateWidget;`
- L92 _public member_ `TAttribute<bool> ShouldGenerateSubMenuEntry;`
- L93 _public member_ `bool bIsVisible;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCLogger.h` (Private)


#### class `SRCLogger`  
`class SRCLogger : public SCompoundWidget`  
_L15-29_
- inherits: `SCompoundWidget`
- desc: Lists RemoteControlLogging entries
- L18 _public function_ `SLATE_BEGIN_ARGS(SRCLogger)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L28 _private member_ `TSharedPtr<SWidget> LogListingWidget;` — Pointer to log widget

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCModeSwitcher.h` (Private)


#### enum `EModeWidgetSizing::Rule`  
`enum Rule`  
_L14-24_
- L17 _public enumerator_ `Fill = 0` — Mode widget stretches to a fraction of the mode switcher.
- L20 _public enumerator_ `Fixed = 1` — Mode widget is fixed width and cannot be resized.
- L23 _public enumerator_ `Auto = 2` — Mode widget will be sized to fit the content.

#### class `SRCModeSwitcher`  
`class SRCModeSwitcher : public SBorder`  
_L30-253_
- inherits: `SBorder`
- desc: A custom mode switcher for Remote Control Panel.
- L170 _public function_ `static FRCMode::FArguments Mode(const FName& InModeId)` — Create a mode with the specified ModeId
- L178 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnModeSwitched, const FRCMode& );` — Delegate to be invoked when the active mode is switched/changed.
- L179 _public function_ `FOnModeSwitched& OnModeSwitched()`
- L182 _public prototype_ `DECLARE_EVENT_OneParam(SRCModeSwitcher, FModesChanged, const TSharedRef<SRCModeSwitcher>& );` — Delegate to be invoked when the number of modes changed.
- L183 _public function_ `FModesChanged* OnModesChanged()`
- L185 _public function_ `SLATE_BEGIN_ARGS(SRCModeSwitcher)`
- L190 _public prototype_ `SLATE_ARGUMENT(FName, DefaultMode) SLATE_EVENT(FOnModeSwitched, OnModeSwitched) SLATE_EVENT(FModesChanged::FDelegate, OnModesChanged) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L201 _public prototype_ `const TArray<FRCMode>& GetModes() const;` — @return the Modes driven by the mode switcher.
- L204 _public prototype_ `void AddMode(const FRCMode::FArguments& NewModeArgs);` — Adds a mode to the mode switcher.
- L205 _public prototype_ `void AddMode(FRCMode& NewMode);`
- L208 _public prototype_ `void InsertMode(const FRCMode::FArguments& NewModeArgs, int32 InsertIdx);` — Inserts a mode at the specified index in the mode switcher.
- L209 _public prototype_ `void InsertMode(FRCMode& NewMode, int32 InsertIdx);`
- L212 _public prototype_ `void RemoveMode(const FName& InModeId);` — Removes a mode from the mode switcher.
- L215 _public prototype_ `void RefreshModes();` — Force refreshing of the mode widgets
- L218 _public prototype_ `void ClearModes();` — Removes all modes from the mode switcher.
- L223 _private prototype_ `ECheckBoxState IsModeEnabled(FRCMode* InMode) const;` — Retrieves whether the given mode is enabled or not.
- L226 _private prototype_ `void RegenerateWidgets();` — Regenerates all widgets in the mode switcher.
- L229 _private prototype_ `void SetModeEnabled(ECheckBoxState NewState, FRCMode* NewMode);` — Sets the given mode as active.
- L237 _private prototype_ `void SetModeEnabled_Internal(ECheckBoxState NewState, FRCMode* NewMode, bool bInForceModeEnabled = false);` — Sets the given mode as active. Also allows to force the operation. Useful e.g. when Widget is being created and the current mode already matches the required one.
- L240 _private member_ `FName ActiveMode;` — Holdes the active mode.
- L243 _private member_ `TArray<FRCMode> RCModes;` — Information about the various RC modes.
- L246 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L249 _private member_ `FModesChanged ModesChanged;` — Holds the delegate to be invoked when the number of modes changed.
- L252 _private member_ `FOnModeSwitched ModeSwitched;` — Holds the delegate to be invoked when the active mode is switched/changed.

#### class `SRCModeSwitcher::FRCMode`  
`class FRCMode`  
_L34-167_
- desc: Describes a single mode switch.
- L38 _public function_ `SLATE_BEGIN_ARGS(FRCMode) : _ModeId() , _DefaultLabel() , _DefaultTooltip() , _ToolTip() , _FillWidth(1.0f) , _FixedWidth() , _HAlignCell(HAlign_Fill) , _VAlignCell(VAlign_Fill) , _IsDefault(false)`
- L50 _public function_ `SLATE_ARGUMENT(FName, ModeId) SLATE_ATTRIBUTE(FText, DefaultLabel) SLATE_ATTRIBUTE(FText, DefaultTooltip) SLATE_ATTRIBUTE(TSharedPtr< IToolTip >, ToolTip) SLATE_ATTRIBUTE(float, FillWidth) SLATE_ARGUMENT(TOptional<float>, FixedWidth) SLATE_ARGUMENT(EHorizontalAlignment, HAlignCell) SLATE_ARGUMENT(EVerticalAlignment, VAlignCell) SLATE_ATTRIBUTE(FSlateIcon, OptionalIcon) SLATE_ARGUMENT(bool, IsDefault) SLATE_ATTRIBUTE(bool, ShouldGenerateWidget) SLATE_END_ARGS() FRCMode(const FArguments& InArgs) : bIsDefault(InArgs._IsDefault) , bIsVisible(true) , bShowIcon(false) , CellHAlignment(InArgs._HAlignCell) , CellVAlignment(InArgs._VAlignCell) , DefaultText(InArgs._DefaultLabel) , DefaultTooltip(InArgs._DefaultTooltip) , ModeId(InArgs._ModeId) , OptionalIcon(InArgs._OptionalIcon) , ToolTip(InArgs._ToolTip) , ShouldGenerateWidget(InArgs._ShouldGenerateWidget) , SizeRule(EModeWidgetSizing::Fill) , Width(1.f)`
- L107 _public function_ `bool operator==(const FRCMode& OtherMode)`
- L112 _public function_ `bool operator==(const FRCMode& OtherMode) const`
- L119 _public function_ `void SetWidth(float NewWidth)`
- L124 _public function_ `float GetWidth() const`
- L130 _public member_ `bool bIsDefault;` — Whether this mode is default or not.
- L133 _public member_ `bool bIsVisible;` — Determines the visibility of the mode widget for this mode.
- L136 _public member_ `bool bShowIcon;` — Determines whether we need to generate icon widget for this mode or not.
- L139 _public member_ `EHorizontalAlignment CellHAlignment;` — Holds the mode widget alignment by horizontal.
- L142 _public member_ `EVerticalAlignment CellVAlignment;` — Holds the mode widget alignment by vertical.
- L145 _public member_ `TAttribute<FText> DefaultText;` — Default text to use if no widget is passed in.
- L148 _public member_ `TAttribute<FText> DefaultTooltip;` — Default tooltip to use if no widget is passed in
- L151 _public member_ `FName ModeId;` — A unique ID for this mode, so that it can be saved and restored.
- L154 _public member_ `TAttribute<FSlateIcon> OptionalIcon;` — Optional icon to be used.
- L157 _public member_ `TAttribute<TSharedPtr<IToolTip>> ToolTip;` — Custom tooltip to use
- L160 _public member_ `TAttribute<bool> ShouldGenerateWidget;` — Determines whether we need to generate mode widget for this mode or not.
- L163 _public member_ `EModeWidgetSizing::Rule SizeRule;` — Determines the sizing of the mode widget for this mode.
- L166 _public member_ `TAttribute<float> Width;` — Width of the mode widget in Slate Units

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace EModeWidgetSizing`
- L178 _delegate_ `DECLARE_DELEGATE_OneParam(FOnModeSwitched, const FRCMode& );` — Delegate to be invoked when the active mode is switched/changed.
- L182 _delegate_ `DECLARE_EVENT_OneParam(SRCModeSwitcher, FModesChanged, const TSharedRef<SRCModeSwitcher>& );` — Delegate to be invoked when the number of modes changed.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelDragHandle.h` (Private)


#### class `SRCPanelDragHandle`  
`template <typename DragDropType> class SRCPanelDragHandle : public SCompoundWidget`  
_L17-86_
- inherits: `SCompoundWidget`
- L20 _public typedef_ `using DragDropWidgetType = typename DragDropType::WidgetType;`
- L21 _public function_ `SLATE_BEGIN_ARGS(SRCPanelDragHandle)`
- L23 _public function_ `SLATE_ARGUMENT(TSharedPtr<DragDropWidgetType>, Widget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, FGuid InId)`
- L51 _public function_ `FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L56 _public function_ `FReply OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L70 _public function_ `TSharedPtr<FDragDropOperation> CreateDragDropOperation()`
- L83 _private member_ `TWeakPtr<DragDropWidgetType> Widget;` — Holds the widget to display when dragging.
- L85 _private member_ `FGuid Id;` — Holds the ID of the item being dragged.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelExposedActor.h` (Private)


#### struct `SRCPanelExposedActor`  
`struct SRCPanelExposedActor : public SRCPanelExposedEntity`  
_L20-56_
- inherits: `SRCPanelExposedEntity`
- desc: Represents an actor exposed to remote control.
- L24 _public function_ `SLATE_BEGIN_ARGS(SRCPanelExposedActor) : _LiveMode(false)`
- L27 _public prototype_ `SLATE_ATTRIBUTE(bool, LiveMode) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() static TSharedPtr<SRCPanelTreeNode> MakeInstance(const FGenerateWidgetArgs& Args);`
- L33 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FRemoteControlActor> InWeakActor, URemoteControlPreset* InPreset, FRCColumnSizeData InColumnSizeData);`
- L36 _public prototype_ `virtual ENodeType GetRCType() const override;`
- L37 _public prototype_ `virtual void Refresh() override;`
- L42 _private prototype_ `TSharedRef<SWidget> RecreateWidget(const FString& Path);` — Regenerate this row's content.
- L44 _private prototype_ `void OnChangeActor(const FAssetData& AssetData);` — Handle the user selecting a different actor to expose.
- L46 _private prototype_ `void OnChangeActor(AActor* Actor);` — Handle direct actor value event instead of by asset.
- L48 _private prototype_ `TSharedRef<SWidget> CreateEmbeddedPresetActorPicker();` — Creates an actor picker for hosted presets because the engine default one cannot use custom worlds.
- L51 _private member_ `TWeakObjectPtr<URemoteControlPreset> WeakPreset;` — Weak reference to the preset that exposes the actor.
- L53 _private member_ `TWeakPtr<FRemoteControlActor> WeakActor;` — Weak ptr to the remote control actor structure.
- L55 _private member_ `TAttribute<bool> bLiveMode;` — Holds this row's panel live mode.

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_OneParam(FOnUnexposeActor, const FGuid& );`
- L17 _prototype_ `DECLARE_DELEGATE_OneParam(FOnUnexposeActor, const FGuid& );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelExposedEntitiesGroup.h` (Private)


#### class `SRCPanelExposedEntitiesGroup`  
`class SRCPanelExposedEntitiesGroup : public SRCPanelTreeNode`  
_L16-92_
- inherits: `SRCPanelTreeNode`
- desc: Widget that is used as a parent for field widget
- L19 _public function_ `SLATE_BEGIN_ARGS(SRCPanelExposedEntitiesGroup)`
- L22 _public function_ `SLATE_EVENT(FOnGroupPropertyIdChanged, OnGroupPropertyIdChanged) SLATE_ARGUMENT(FName, FieldKey) SLATE_END_ARGS()`
- L34 _public prototype_ `void Construct(const FArguments& InArgs, ERCFieldGroupType InFieldGroupType, URemoteControlPreset* Preset);`
- L37 _public prototype_ `virtual TSharedRef<SWidget> GetWidget(const FName ForColumnName, const FName InActiveProtocol) override;`
- L44 _public prototype_ `void AssignChildren(const TArray<TSharedPtr<SRCPanelTreeNode>>& InFieldEntities);` — Take the current fields in RC and assign them to its child widgets based on the group key @param InFieldEntities Current fields exposed in RC
- L47 _public prototype_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRCPanelTreeNode>>& OutChildren) const override;` — Get this tree node's children.
- L50 _public function_ `virtual bool HasChildren() const override` — Returns true if this tree node has children.
- L53 _public function_ `ERCFieldGroupType GetGroupType() const` — Get the group type of this group
- L56 _public function_ `FName GetFieldKey() const` — Get the field key of this group
- L60 _private prototype_ `FMakeNodeWidgetArgs CreateNodeWidgetArgs();` — Create the node Args for this class that will be used to create the widget
- L67 _private prototype_ `void OnPropertyIdTextCommitted(const FText& InText, ETextCommit::Type InTextCommitType);` — Called when the text label is renamed @param InText New Text @param InTextCommitType Type of commit, look at ETextCommit for more information
- L70 _private prototype_ `TArray<TSharedRef<FRemoteControlProperty>> GetChildProperties() const;` — Returns the properties that are children of this group
- L73 _private member_ `TArray<TSharedPtr<SRCPanelTreeNode>> ChildWidgets;` — Child widgets of this group
- L76 _private member_ `FName FieldKey;` — Field key value of this group
- L79 _private member_ `FText OwnerDisplayName;` — Shared owner of the entity group
- L82 _private member_ `FName PropertyIdName;` — Shared property id of the entity group
- L85 _private member_ `ERCFieldGroupType GroupType = ERCFieldGroupType::None;` — Field group type of this group
- L88 _private member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeak;` — Weak ptr to the preset where this group reside
- L91 _private member_ `FOnGroupPropertyIdChanged OnGroupPropertyIdChangedDelegate;` — Delegate called when the group type is PropertyId and the value change

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE(FOnGroupPropertyIdChanged) class SRCPanelExposedEntitiesGroup : public SRCPanelTreeNode { public: SLATE_BEGIN_ARGS(SRCPanelExposedEntitiesGroup) {} SLATE_EVENT(FOnGroupPropertyIdChanged, OnGroupPropertyIdChanged) SLATE_ARGUMENT(FName, FieldKey) SLATE_END_ARGS()` — Delegate called when the PropertyId of a group change

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelExposedEntitiesList.h` (Private)


#### enum `EEntitiesListMode`  
`enum class EEntitiesListMode : uint8`  
_L44-48_
- L46 _public enumerator_ `Default`
- L47 _public enumerator_ `Protocols`

#### struct `FGroupDragEvent`  
`struct FGroupDragEvent`  
_L51-65_
- desc: Holds information about a group drag and drop event
- L53 _public function_ `FGroupDragEvent(TSharedPtr<SRCPanelGroup> InDragOriginGroup, TSharedPtr<SRCPanelGroup> InDragTargetGroup) : DragOriginGroup(MoveTemp(InDragOriginGroup)) , DragTargetGroup(MoveTemp(InDragTargetGroup))`
- L59 _public prototype_ `bool IsDraggedFromSameGroup() const;`
- L62 _public member_ `TSharedPtr<SRCPanelGroup> DragOriginGroup;` — Group the drag originated in.
- L64 _public member_ `TSharedPtr<SRCPanelGroup> DragTargetGroup;` — Group where the element was dropped.

#### class `SRCPanelExposedEntitiesList`  
`class SRCPanelExposedEntitiesList : public SCompoundWidget`  
_L69-374_
- inherits: `SCompoundWidget`
- L72 _public function_ `SLATE_BEGIN_ARGS(SRCPanelExposedEntitiesList) : _LiveMode(false) , _ProtocolsMode(false)`
- L76 _public prototype_ `SLATE_ATTRIBUTE(bool, LiveMode) SLATE_ATTRIBUTE(bool, ProtocolsMode) SLATE_ATTRIBUTE(TSharedPtr<SWidget>, ExposeFunctionsComboButton) SLATE_ATTRIBUTE(TSharedPtr<SWidget>, ExposeActorsComboButton) SLATE_EVENT(FSimpleDelegate, OnEntityListUpdated) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() void Construct(const FArguments& InArgs, URemoteControlPreset* InPreset, TWeakPtr<FRCPanelWidgetRegistry> InWidgetRegistry);`
- L86 _public prototype_ `~SRCPanelExposedEntitiesList();`
- L89 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L92 _public function_ `URemoteControlPreset* GetPreset() const`
- L98 _public prototype_ `TSharedPtr<SRCPanelTreeNode> GetSelectedGroup() const;` — Get the currently selected group.
- L101 _public prototype_ `TSharedPtr<SRCPanelTreeNode> GetSelectedEntity() const;` — Get the currently selected exposed entity.
- L104 _public prototype_ `TArray<TSharedPtr<SRCPanelTreeNode>> GetSelectedEntities() const;` — Get the currently selected exposed entities.
- L107 _public prototype_ `int32 GetSelectedEntitiesNum() const;` — Get the currently selected exposed entities.
- L110 _public prototype_ `bool IsEntitySelected(const TSharedPtr<SRCPanelTreeNode>& InNode) const;` — Return true if the given node is currently selected.
- L113 _public prototype_ `void SetSelection(const TSharedPtr<SRCPanelTreeNode>& Node, const bool bForceMouseClick = false);` — Set the currently selected group or exposed entity.
- L116 _public prototype_ `void SetBackendFilter(const FRCFilter& InBackendFilter);` — Notifies the entities list view that the filter-list filter has changed
- L119 _public prototype_ `void RebuildListWithColumns(EEntitiesListMode InListMode);` — Recreate the list with dynamic columns.
- L122 _public prototype_ `void Refresh();` — Recreate everything in the panel.
- L125 _public prototype_ `void TryRefreshingSearch(const FText& InSearchText, bool bApplyFilter = true);` — Tries to refresh the list according to the provided search text.
- L128 _public function_ `void ResetSearch()` — Notifies us that the search has ended.
- L131 _public function_ `FOnSelectionChange& OnSelectionChange()` — Returns delegate called on selection change.
- L134 _public function_ `FSimpleDelegate OnEntityListUpdated()` — Returns delegate triggered upon a modification to an exposed entity.
- L137 _public function_ `TSharedPtr<SRCPanelFilter> GetFilterPtr() const` — Return the FilterPtr of this RCPanelEntitiesList
- L140 _public prototype_ `void UpdateSearch();` — Update the Search
- L143 _public prototype_ `void UpdateEntityUsage();` — Update the In Use flag on entities.
- L147 _private prototype_ `FText HandleEntityListHeaderLabel() const;` — Handles label to be shown in the entity list header.
- L149 _private prototype_ `void OnObjectPropertyChange(UObject* InObject, FPropertyChangedEvent& InChangeEvent);` — Handles object property changes, used to update arrays correctly.
- L151 _private prototype_ `void OnActorLabelChanged(AActor* InActor);` — Called when the label of an actor has changed
- L153 _private prototype_ `void GenerateListWidgets();` — Create exposed entity widgets.
- L155 _private prototype_ `void GenerateListWidgets(const FRemoteControlPresetGroup& FromGroup);` — Create exposed entity widgets.
- L157 _private prototype_ `void RefreshGroups();` — Generate the groups using the preset's layout data.
- L159 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<SRCPanelTreeNode> Node, const TSharedRef<STableViewBase>& OwnerTable);` — Generate row widgets for groups and exposed entities.
- L161 _private prototype_ `void OnGetNodeChildren(TSharedPtr<SRCPanelTreeNode> Node, TArray<TSharedPtr<SRCPanelTreeNode>>& OutNodes);` — Handle getting a node's children.
- L163 _private prototype_ `void OnSelectionChanged(TSharedPtr<SRCPanelTreeNode> Node, ESelectInfo::Type SelectInfo);` — Handle selection changes.
- L165 _private prototype_ `FReply OnDropOnGroup(const TSharedPtr<FDragDropOperation>& DragDropOperation, const TSharedPtr<SRCPanelTreeNode>& TargetEntity, const TSharedPtr<SRCPanelTreeNode>& DragTargetGroup);` — Handlers for drag/drop events.
- L167 _private prototype_ `void OnFilterChanged();` — Handler for when a filter in the filter list has changed
- L169 _private prototype_ `FGuid GetGroupId(const FGuid& EntityId);` — Get the id of the group that holds a particular widget.
- L171 _private prototype_ `FReply OnCreateGroup();` — Handles creating a new group.
- L173 _private prototype_ `void OnDeleteGroup(const FGuid& GroupId);` — Handles group deletion.
- L175 _private prototype_ `void OnEntityRebind(const FGuid& InEntityGuid);` — Called when an Entity is rebound
- L177 _private prototype_ `void SelectActorsInlevel(const TArray<UObject*>& Objects);` — Select actors in the current level.
- L179 _private prototype_ `void RegisterEvents();`
- L180 _private prototype_ `void UnregisterEvents();`
- L183 _private function_ `float OnGetLeftColumnWidth() const`
- L184 _private function_ `float OnGetRightColumnWidth() const`
- L185 _private function_ `void OnSetColumnWidth(float InWidth)`
- L188 _private prototype_ `void OnSearchTextChanged(const FText& InFilterText);` — Exposed Entities filtering. (Filters the Exposed Entities view)
- L189 _private prototype_ `void OnSearchTextCommitted(const FText& InFilterText, ETextCommit::Type InCommitType);`
- L190 _private prototype_ `void PopulateSearchStrings(const SRCPanelTreeNode& Item, TArray<FString>& OutSearchStrings) const;`
- L193 _private prototype_ `TSharedPtr<SRCPanelGroup> FindGroupById(const FGuid& Id);` — Find a group using its id.
- L196 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening(SRCPanelTreeNode::ENodeType InType);` — Handle context menu opening on a row.
- L198 _private prototype_ `TSharedRef<SWidget> GetGroupMenuContentWidget();`
- L204 _private prototype_ `void OnCreateFieldGroup(ERCFieldGroupType InFieldGroupType);` — Called when the group type changed, if the new group type is the same as the current one it will be set to none @param InFieldGroupType New grouping type
- L207 _private prototype_ `void CreateFieldGroup();` — Group fields based on the current group type (PropertyId/Owner)
- L213 _private prototype_ `void OnGroupOrderChanged(ERCFieldGroupOrder InGroupOrder);` — Called when the order type changed, if the new order type is the same as the current one it will be set to none @param InGroupOrder New group order
- L216 _private prototype_ `void OrderGroups();` — Order the groups based on the current order assigned (Ascending/Descending)
- L219 _private prototype_ `void RefreshGroupsAndRestoreExpansions();` — Refresh the fields groups and restore the expansion
- L222 _private prototype_ `void CreateGroupsAndSort();` — Calls both the CreateFieldGroup and the OrderGroups
- L225 _private prototype_ `void RegisterPresetDelegates();`
- L226 _private prototype_ `void UnregisterPresetDelegates();`
- L227 _private prototype_ `void OnEntityAdded(const FGuid& EntityId);`
- L228 _private prototype_ `void OnEntityRemoved(const FGuid& InGroupId, const FGuid& EntityId);`
- L229 _private prototype_ `void OnGroupAdded(const FRemoteControlPresetGroup& Group);`
- L230 _private prototype_ `void OnGroupDeleted(FRemoteControlPresetGroup DeletedGroup);`
- L231 _private prototype_ `void OnGroupOrderChanged(const TArray<FGuid>& GroupIds);`
- L232 _private prototype_ `void OnGroupRenamed(const FGuid& GroupId, FName NewName);`
- L233 _private prototype_ `void OnFieldAdded(const FGuid& GroupId, const FGuid& FieldId, int32 FieldPosition);`
- L234 _private prototype_ `void OnFieldDeleted(const FGuid& GroupId, const FGuid& FieldId, int32 FieldPosition);`
- L235 _private prototype_ `void OnFieldOrderChanged(const FGuid& GroupId, const TArray<FGuid>& Fields);`
- L236 _private prototype_ `void OnEntitiesUpdated(URemoteControlPreset*, const TSet<FGuid>& UpdatedEntities);`
- L239 _private prototype_ `void ApplyFilters();` — Requests that the entities view refreshes all it's items.
- L242 _private prototype_ `void RequestSearchOrFilter();` — Notifies us that we need to do a search or filter in the next tick.
- L245 _private prototype_ `FReply RequestDeleteAllEntities();` — Delete all operation for entities list.
- L247 _private prototype_ `FReply RequestDeleteAllGroups();` — Delete all operation for groups list.
- L249 _private prototype_ `SHeaderRow::FColumn::FArguments CreateColumn(const FName ForColumnName);`
- L250 _private prototype_ `int32 GetColumnIndex(const FName& ForColumn) const;`
- L251 _private prototype_ `int32 GetColumnIndex_Internal(const FName& ForColumn, const FName& ExistingColumnName, ERCColumn::Position InPosition) const;`
- L252 _private prototype_ `FText GetColumnLabel(const FName& ForColumn) const;`
- L253 _private prototype_ `float GetColumnSize(const FName ForColumn) const;`
- L254 _private prototype_ `void InsertColumn(const FName& InColumnName);`
- L255 _private prototype_ `void RemoveColumn(const FName& InColumnName);`
- L257 _private prototype_ `void OnProtocolBindingAddedOrRemoved(ERCProtocolBinding::Op BindingOperation);`
- L260 _private prototype_ `void OnWidgetRegistryRefreshed(const TArray<UObject*>& Objects);` — Called when the widget registry is refreshed by an underlying property generator.
- L262 _private prototype_ `void ProcessRefresh();`
- L267 _private prototype_ `void ExposedEntitiesNodesRefresh();` — If necessary, will perform a refresh of the exposed entities nodes widgets.
- L270 _private prototype_ `void OnPropertyIdRenamed(const FName InNewId, TSharedPtr<SRCPanelTreeNode> InNode);` — Executed when a property Id is changed, will set all selected node(s) property id to the new one
- L273 _private prototype_ `void OnLabelModified(const FName InOldName, const FName InNewName);` — Executed when a property Name is changed, will set all selected node(s) property Name to the new one
- L276 _private prototype_ `FReply OnNodeDragDetected(const FGeometry& InGeometry, const FPointerEvent& InPointerEvent, TSharedPtr<SRCPanelTreeNode> InNode);` — Executed when a drag is detected, will create the Drag and Drop widget of the node(s)
- L279 _private prototype_ `void StoreListSettings();` — Stores the list settings
- L282 _private prototype_ `void RecallListSettings();` — Recalls the list settings
- L285 _private prototype_ `void SelectSource_Execute();` — Selects the source of the currently selected entity.
- L287 _private prototype_ `void UpdateEntityUsage_Execute();`
- L291 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list to use if specified
- L293 _private member_ `TSharedPtr<SListView<TSharedPtr<SRCPanelTreeNode>>> GroupsListView;` — Holds the Groups list view.
- L295 _private member_ `TSharedPtr<STreeView<TSharedPtr<SRCPanelTreeNode>>> FieldsListView;` — Holds the Fields list view.
- L297 _private member_ `TArray<TSharedPtr<SRCPanelGroup>> FieldGroups;` — Holds all the field groups.
- L299 _private member_ `TArray<TSharedPtr<SRCPanelTreeNode>> FieldEntities;` — Holds all the field entities.
- L301 _private member_ `TSet<FObjectKey> CachedEntityOwners;` — Cached list of entity owners used to track whether owner changes should refresh the list
- L303 _private member_ `TArray<TSharedPtr<SRCPanelTreeNode>> CachedFieldEntities;` — Cached field entities used to store the original Entities when switching groups.
- L305 _private member_ `TArray<TSharedPtr<SRCPanelExposedEntitiesGroup>> ExposedEntitiesGroups;` — Holds all the exposed entities groups.
- L307 _private member_ `ERCFieldGroupType CurrentGroupType = ERCFieldGroupType::None;` — Holds the current group type
- L309 _private member_ `ERCFieldGroupOrder CurrentGroupSortType = ERCFieldGroupOrder::None;` — Holds the current sorting type
- L311 _private member_ `TArray<TSharedPtr<SRCPanelExposedEntitiesGroup>> FieldEntitiesGroups;` — Holds all the entities groups currently in the list
- L313 _private member_ `TMap<FGuid, TSharedPtr<SRCPanelTreeNode>> FieldWidgetMap;` — Map of field ids to field widgets.
- L315 _private member_ `TAttribute<bool> bIsInLiveMode;` — Whether the panel is in live mode.
- L317 _private member_ `TAttribute<bool> bIsInProtocolsMode;` — Whether the panel is in protocols mode.
- L319 _private member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeak;` — Holds a weak reference to the preset asset.
- L321 _private member_ `FDelegateHandle OnPropertyChangedHandle;` — Handle to the delegate called when an object property change is detected.
- L323 _private member_ `FDelegateHandle OnProtocolBindingAddedOrRemovedHandle;` — Handle to the delegate called when a binding is added or removed.
- L325 _private member_ `FDelegateHandle OnActorLabelChangedHandle;` — Handle to the delegate called when an actor's label is renamed
- L327 _private member_ `FOnSelectionChange OnSelectionChangeDelegate;` — Delegate called on selected group change.
- L329 _private member_ `FRCColumnSizeData ColumnSizeData;` — The column data shared between all tree nodes in order to share a splitter amongst all rows.
- L331 _private member_ `float ColumnWidth = 0.49f;` — The actual width of the right column.  The left column is 1-ColumnWidth
- L333 _private member_ `FSimpleDelegate OnEntityListUpdatedDelegate;` — Event triggered when the entity list is updated.
- L335 _private member_ `TWeakPtr<FRCPanelWidgetRegistry> WidgetRegistry;` — Holds the cache of widgets to be used by this list's entities.
- L337 _private member_ `FRCFilter BackendFilter;` — Holds the cache of filters to be used by this list's entities.
- L339 _private member_ `bool bFilterApplicationRequested;` — If true, the entity items will be refreshed next frame.
- L341 _private member_ `bool bSearchRequested;` — If true, the entity items will be refreshed next frame.
- L343 _private member_ `bool bUpdateEntityUsage;` — If true, the entity list will have its in use flag updated next frame.
- L345 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L347 _private member_ `TSharedPtr<SRCHeaderRow> FieldsHeaderRow;` — Holds the header row of entities list.
- L349 _private member_ `TSharedPtr<SRCPanelFilter> FilterPtr;` — The filter list
- L351 _private member_ `TSharedPtr<SSearchBox> SearchBoxPtr;` — The text box used to search for tags.
- L353 _private member_ `TSharedPtr<SComboButton> ComboButtonGroupButton;` — Button giving you the possibilities for grouping.
- L355 _private member_ `TSharedPtr<TTextFilter<const SRCPanelTreeNode&>> SearchTextFilter;` — Text filter for the search text.
- L357 _private member_ `TSharedPtr<FText> SearchedText;` — Actively searched term.
- L359 _private member_ `EEntitiesListMode ActiveListMode;` — Holds the active list mode.
- L361 _private member_ `FName ActiveProtocol;` — Holds the active protocol enabled by the mode switcher.
- L363 _private member_ `static TSet<FName> DefaultProtocolColumns;` — Columns to be present by default in protocols mode.
- L365 _private member_ `FGuid CurrentlySelectedGroup;` — Holds identifier of the selected group.
- L367 _private member_ `FRCPanelExposedEntitiesListSettingsData DefaultSettings;` — Default settings for this entities list
- L369 _private member_ `bool bRefreshRequested = false;`
- L370 _private member_ `bool bRefreshEntitiesGroups = false;`
- L373 _private member_ `bool bNodesRefreshRequested = false;` — When true, widgets of the Exposed Entities List will be refreshed on Tick

#### Free symbols / members of external scopes

- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChange, const TSharedPtr<SRCPanelTreeNode>& );`
- L67 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChange, const TSharedPtr<SRCPanelTreeNode>& );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelExposedEntity.h` (Private)


#### struct `SRCPanelExposedEntity`  
`struct SRCPanelExposedEntity : public SRCPanelTreeNode`  
_L22-134_
- inherits: `SRCPanelTreeNode`
- desc: @Note if you inherit from this struct, you must call SRCPanelExposedEntity::Initialize.
- L25 _public prototype_ `TSharedPtr<FRemoteControlEntity> GetEntity() const;`
- L26 _public prototype_ `virtual TSharedPtr<SWidget> GetContextMenu() override;`
- L27 _public function_ `virtual FGuid GetRCId() const override final`
- L29 _public prototype_ `virtual void EnterRenameMode() override;` — Make the group name's text box editable.
- L31 _public prototype_ `virtual FName GetPropertyId() override;` — Get the PropertyId of this Node.
- L33 _public function_ `virtual void SetPropertyId(FName InNewPropertyId) override` — Set the PropertyId of this Node.
- L35 _public function_ `virtual void SetName(FName InNewName) override` — Set the Name of this Node.
- L37 _public function_ `virtual void SetHighlightText(const FText& InHightlightText = FText::GetEmpty()) override` — Updates the highlight text to active search term.
- L39 _public prototype_ `virtual void Refresh() override;`
- L49 _protected prototype_ `void Initialize(const FInitParams& InParams);`
- L52 _protected prototype_ `TSharedRef<SWidget> CreateInvalidWidget(const FText& InErrorText = FText::GetEmpty());` — Create a widget that displays the rebind button.
- L55 _protected prototype_ `EVisibility GetVisibilityAccordingToLiveMode(EVisibility NonEditModeVisibility) const;` — Get the widget's visibility according to the panel's mode.
- L58 _protected prototype_ `TSharedRef<SWidget> CreateEntityWidget(TSharedPtr<SWidget> ValueWidget, TSharedPtr<SWidget> ResetWidget = SNullWidget::NullWidget, const FText& OptionalWarningMessage = FText::GetEmpty(), TSharedRef<SWidget> EditConditionWidget = SNullWidget::NullWidget);` — Create an exposed entity widget with a drag handle and unexpose button.
- L61 _protected prototype_ `virtual FMakeNodeWidgetArgs CreateEntityWidgetInternal(TSharedPtr<SWidget> ValueWidget, TSharedPtr<SWidget> ResetWidget = SNullWidget::NullWidget, const FText& OptionalWarningMessage = FText::GetEmpty(), TSharedRef<SWidget> EditConditionWidget = SNullWidget::NullWidget);` — Returns populated args to display this widget.
- L65 _protected member_ `FGuid EntityId;` — Id of the entity.
- L67 _protected member_ `TWeakObjectPtr<URemoteControlPreset> Preset;` — The underlying preset.
- L69 _protected member_ `TAttribute<bool> bLiveMode;` — Whether the panel is in live mode or not.
- L71 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — Command list to use for the context menu
- L73 _protected member_ `FText CachedOwnerDisplayName;` — Display name of the entity's owner (What actor it's bound to).
- L75 _protected member_ `FName CachedOwnerPathName;` — Name of the entity's owner (What actor it's bound to).
- L77 _protected member_ `FName CachedSubobjectPath;` — Path from the entity owner to the object holding the exposed property.
- L79 _protected member_ `FName CachedBindingPath;` — Path of the entity's binding.
- L81 _protected member_ `bool bValidBinding = false;` — Whether the binding is valid at the moment.
- L83 _protected member_ `FName CachedLabel;` — Display name of the entity.
- L85 _protected member_ `FName PropertyIdLabel;` — Display PropertyId of the entity.
- L87 _protected member_ `FString CachedFieldPath;` — Cached entity field path.
- L89 _protected member_ `TAttribute<FText> HighlightText;` — Text to be highlighted while searching.
- L91 _protected member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L93 _protected member_ `static const FText SelectInOutliner;` — Extra information to add to the tooltips.
- L96 _private prototype_ `void OnActorSelected(AActor* InActor) const;` — Handles changing the object this entity is bound to upon selecting an actor in the rebinding dropdown.
- L99 _private prototype_ `const FSlateBrush* GetBorderImage() const;` — Get the widget's border.
- L101 _private prototype_ `TSharedRef<SWidget> CreateRebindMenuContent();` — Create the content of the rebind button.
- L104 _private prototype_ `void CreateRebindComponentMenuContent(FMenuBuilder& SubMenuBuilder);` — Create the content of the rebind component button.
- L107 _private prototype_ `void CreateRebindSubObjectMenuContent(FMenuBuilder& SubMenuBuilder);` — Create the content of the rebind subobject button.
- L110 _private prototype_ `TSharedRef<SWidget> CreateRebindAllPropertiesForActorMenuContent();` — Create the content for the menu used to rebind all properties for the actor that owns this entity.
- L113 _private prototype_ `void OnActorSelectedForRebindAllProperties(AActor* InActor) const;` — Handle selecting an actor for a rebind for all properties under an actor.
- L116 _private prototype_ `bool OnVerifyItemLabelChanged(const FText& InLabel, FText& OutErrorMessage);` — Verifies that the entity's label doesn't already exist.
- L118 _private prototype_ `void OnLabelCommitted(const FText& InLabel, ETextCommit::Type InCommitInfo);` — Handles committing a entity label.
- L120 _private prototype_ `bool IsActorSelectable(const AActor* Parent) const;` — Returns whether or not the actor is selectable for a binding replacement.
- L122 _private prototype_ `void HandleUnexposeEntity();` — Handle clicking on the unexpose button.
- L124 _private prototype_ `void SelectActor(AActor* InActor) const;`
- L127 _private prototype_ `TSharedRef<SWidget> CreateUseContextCheckbox();`
- L128 _private prototype_ `void OnUseContextChanged(ECheckBoxState State);`
- L129 _private prototype_ `ECheckBoxState IsUseContextEnabled() const;`
- L130 _private prototype_ `bool ShouldUseRebindingContext() const;`
- L133 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameTextBox;` — The textbox for the row's name.

#### struct `SRCPanelExposedEntity::FInitParams`  
`struct FInitParams`  
_L42-48_
- L44 _public member_ `FGuid EntityId;`
- L45 _public member_ `URemoteControlPreset* Preset;`
- L46 _public member_ `TAttribute<bool> bLiveMode;`
- L47 _public member_ `TSharedPtr<FUICommandList> CommandList;`

#### class `FExposedEntityDragDrop`  
`class FExposedEntityDragDrop final : public FDecoratedDragDropOp`  
_L136-205_
- inherits: `FDecoratedDragDropOp`
- L141 _public typedef_ `using WidgetType = SWidget;`
- L143 _public function_ `FExposedEntityDragDrop(const TSharedPtr<SWidget>& InWidget, const FGuid& InNodeId, const TArray<TSharedPtr<SRCPanelTreeNode>>& InSelectedEntities) : NodeId(InNodeId) , SelectedEntities(InSelectedEntities)`
- L169 _public function_ `FGuid GetNodeId() const` — Get the ID of the represented entity or group.
- L175 _public function_ `const TArray<TSharedPtr<SRCPanelTreeNode>>& GetSelectedEntities() const` — Get the IDs that were selected at the time the drag started.
- L181 _public function_ `const TArray<FGuid>& GetSelectedFieldsId() const` — Get the IDs that were selected at the time the drag started.
- L186 _public function_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override`
- L191 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L198 _private member_ `FGuid NodeId;` — ID of the represented entity or group.
- L200 _private member_ `TArray<FGuid> SelectedFieldsIds;` — Field IDs that were selected at the time the drag started.
- L202 _private member_ `TArray<TSharedPtr<SRCPanelTreeNode>> SelectedEntities;` — Entities that were selected at the time the drag started.
- L204 _private member_ `TSharedPtr<SWidget> DecoratorWidget;` — Decorator Drag and Drop widget.

#### Free symbols / members of external scopes

- L151 _function_ `` (scope `FExposedEntityDragDrop::FExposedEntityDragDrop`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelExposedField.h` (Private)


#### struct `SRCPanelExposedField`  
`struct SRCPanelExposedField : public SRCPanelExposedEntity`  
_L29-134_
- inherits: `SRCPanelExposedEntity`
- desc: Widget that displays an exposed field.
- L31 _public function_ `SLATE_BEGIN_ARGS(SRCPanelExposedField) : _LiveMode(false) , _HighlightText() , _Preset(nullptr)`
- L36 _public prototype_ `SLATE_ATTRIBUTE(bool, LiveMode) SLATE_ATTRIBUTE(FText, HighlightText) SLATE_ATTRIBUTE(URemoteControlPreset*, Preset) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() static TSharedPtr<SRCPanelTreeNode> MakeInstance(const FGenerateWidgetArgs& Args);`
- L44 _public prototype_ `void Construct(const FArguments& InArgs, TWeakPtr<FRemoteControlField> Field, FRCColumnSizeData ColumnSizeData, TWeakPtr<FRCPanelWidgetRegistry> InWidgetRegistry);`
- L47 _public prototype_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRCPanelTreeNode>>& OutChildren) const override;`
- L48 _public prototype_ `virtual ENodeType GetRCType() const override;`
- L49 _public prototype_ `virtual void FocusPropertyIdWidget() const override;`
- L50 _public prototype_ `virtual bool HasChildren() const override;`
- L51 _public prototype_ `virtual void Refresh() override;`
- L52 _public prototype_ `virtual TSharedRef<SWidget> GetWidget(const FName ForColumnName, const FName InActiveProtocol) override;`
- L56 _public prototype_ `virtual void SetIsHovered(bool bIsBeingHovered) override;`
- L60 _public prototype_ `virtual TSharedRef<SWidget> GetProtocolWidget(const FName ForColumnName, const FName InProtocolName = NAME_None) override;`
- L61 _public prototype_ `virtual const bool HasProtocolExtension() const override;`
- L62 _public prototype_ `virtual const bool GetProtocolBindingsNum() const override;`
- L63 _public prototype_ `virtual const bool SupportsProtocol(const FName& InProtocolName) const override;`
- L67 _public function_ `TWeakPtr<FRemoteControlField> GetRemoteControlField() const` — Get a weak pointer to the underlying remote control field.
- L70 _public prototype_ `FName GetFieldLabel() const;` — Get this field's label.
- L73 _public prototype_ `EExposedFieldType GetFieldType() const;` — Get this field's type.
- L76 _public prototype_ `void GetBoundObjects(TSet<UObject*>& OutBoundObjects) const;` — Returns this widget's underlying objects.
- L79 _public prototype_ `FText GetOwnerDisplayName() const;` — Get the owner display name of this field
- L82 _public prototype_ `FName GetOwnerPathName() const;` — Get the owner path name of this field
- L86 _protected prototype_ `virtual FMakeNodeWidgetArgs CreateEntityWidgetInternal(TSharedPtr<SWidget> ValueWidget, TSharedPtr<SWidget> ResetWidget = SNullWidget::NullWidget, const FText& OptionalWarningMessage = FText::GetEmpty(), TSharedRef<SWidget> EditConditionWidget = SNullWidget::NullWidget) override;` — Returns populated args to display this widget.
- L90 _private prototype_ `TSharedRef<SWidget> ConstructWidget();` — Construct a property widget.
- L92 _private prototype_ `TSharedRef<SWidget> MakeFieldWidget(const TSharedRef<SWidget>& InWidget, const TSharedRef<SWidget>& EditConditionWidget = SNullWidget::NullWidget);` — Create the wrapper around the field value widget.
- L94 _private prototype_ `void ConstructPropertyWidget();` — Construct this field widget as a property widget.
- L96 _private prototype_ `void ConstructFunctionWidget();` — Construct this field widget as a function widget.
- L98 _private prototype_ `TSharedRef<SWidget> ConstructResetToDefaultWidget(UObject* InObject, TSharedPtr<IPropertyHandle> InPropertyHandle);` — Construct the ResetToDefault Widget that can have CustomReset for certain Property (Right now only Light Intensity)
- L104 _private prototype_ `TSharedRef<SWidget> ConstructCallFunctionButton(bool bIsEnabled = true);` — Construct a call function button @param bIsEnabled Whether the button should be clickable or not. @return The constructed widget.
- L106 _private prototype_ `FReply OnClickFunctionButton();` — Handles calling an exposed function.
- L109 _private prototype_ `FText GetPropertyIdText();` — Return the text to be displayed in the PropertyId column
- L111 _private prototype_ `void OnPropertyIdTextCommitted(const FText& InText, ETextCommit::Type InCommitInfo);` — Handles committing a property id label.
- L114 _private prototype_ `TSharedRef<SWidget> CreateInUseWidget();` — Creates a widget which says whether this field is bound to a controller.
- L117 _private prototype_ `int32 GetBoundCount() const;` — Returns the number of behaviors bound to this field.
- L121 _private member_ `TWeakPtr<FRemoteControlField> WeakField;` — Weak pointer to the underlying RC Field.
- L123 _private member_ `bool bIsHovered = false;` — Whether the widget is currently hovered by a drag and drop operation.
- L125 _private member_ `TArray<TSharedPtr<SRCPanelFieldChildNode>> ChildWidgets;` — This exposed field's child widgets (ie. An array's rows)
- L127 _private member_ `TWeakPtr<FRCPanelWidgetRegistry> WidgetRegistry;` — Holds the panel's cached widgets.
- L129 _private member_ `TUniquePtr<uint8[]> DefaultValue;` — Holds the zeroed Default Value of the ExposedField
- L131 _private member_ `TSharedPtr<SWidget> ResetButtonWidget;` — Holds the shared reference of reset button for this field.
- L133 _private member_ `TSharedPtr<SWidget> PropertyIdWidget;` — Holds the SharedPtr of the PropertyId widget of this field.

#### struct `SRCPanelFieldChildNode`  
`struct SRCPanelFieldChildNode : public SRCPanelTreeNode`  
_L138-150_
- inherits: `SRCPanelTreeNode`
- desc: Represents a child of an exposed field widget.
- L140 _public function_ `SLATE_BEGIN_ARGS(SRCPanelFieldChildNode)`
- L142 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IDetailTreeNode>& InNode, FRCColumnSizeData InColumnSizeData);`
- L145 _public function_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRCPanelTreeNode>>& OutChildren) const override`
- L146 _public function_ `virtual FGuid GetRCId() const override`
- L147 _public function_ `virtual ENodeType GetRCType() const override`
- L149 _public member_ `TArray<TSharedPtr<SRCPanelFieldChildNode>> ChildrenNodes;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelFieldGroup.h` (Private)


#### class `SRCPanelGroup`  
`class SRCPanelGroup : public SRCPanelTreeNode`  
_L24-114_
- inherits: `SRCPanelTreeNode`
- desc: Widget representing a group.
- L31 _public prototype_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnFieldDropEvent, const TSharedPtr<FDragDropOperation>& , const TSharedPtr<SRCPanelTreeNode>& , const TSharedPtr<SRCPanelTreeNode>& );`
- L32 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FGuid, FOnGetGroupId, const FGuid& );`
- L33 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnDeleteGroup, const FGuid& );`
- L35 _public function_ `SLATE_BEGIN_ARGS(SRCPanelGroup) : _LiveMode(false)`
- L38 _public prototype_ `SLATE_ARGUMENT(FGuid, Id) SLATE_ARGUMENT(FName, Name) SLATE_ARGUMENT(TArray<TSharedPtr<SRCPanelTreeNode>>, Children) SLATE_EVENT(FOnFieldDropEvent, OnFieldDropEvent) SLATE_EVENT(FOnGetGroupId, OnGetGroupId) SLATE_EVENT(FOnDeleteGroup, OnDeleteGroup) SLATE_ATTRIBUTE(bool, LiveMode) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() void Tick(const FGeometry&, const double, const float);`
- L49 _public prototype_ `void Construct(const FArguments& InArgs, URemoteControlPreset* InPreset, FRCColumnSizeData IInColumnSizeData);`
- L52 _public prototype_ `FName GetGroupName() const;` — Get this group's name.
- L55 _public prototype_ `void SetName(FName InName);` — Set this widget's name.
- L58 _public function_ `TArray<TSharedPtr<SRCPanelTreeNode>>& GetNodes()` — Get raw access to this group's child nodes.
- L61 _public prototype_ `virtual void EnterRenameMode() override;` — Make the group name's text box editable.
- L64 _public prototype_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRCPanelTreeNode>>& OutChildren) const override;`
- L65 _public prototype_ `virtual TSharedPtr<SWidget> GetContextMenu() override;`
- L66 _public prototype_ `virtual FGuid GetRCId() const override;`
- L67 _public prototype_ `virtual ENodeType GetRCType() const override;`
- L68 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;`
- L72 _private prototype_ `FReply OnFieldDropGroup(const FDragDropEvent& Event, TSharedPtr<SRCPanelTreeNode> TargetField);`
- L73 _private prototype_ `FReply OnFieldDropGroup(TSharedPtr<FDragDropOperation> DragDropOperation, TSharedPtr<SRCPanelTreeNode> TargetField);`
- L74 _private prototype_ `bool OnAllowDropFromOtherGroup(TSharedPtr<FDragDropOperation> DragDropOperation);`
- L77 _private prototype_ `FReply HandleDeleteGroup();` — Handles group deletion
- L79 _private prototype_ `FSlateColor GetGroupNameTextColor() const;` — Returns group name's text color according to the current selection.
- L81 _private prototype_ `const FSlateBrush* GetBorderImage() const;` — Get the border image according to the current selection.
- L83 _private prototype_ `EVisibility GetVisibilityAccordingToLiveMode(EVisibility DefaultHiddenVisibility) const;` — Get the visibility according to the panel's current mode.
- L85 _private prototype_ `bool OnVerifyItemLabelChanged(const FText& InLabel, FText& OutErrorMessage);`
- L87 _private prototype_ `void OnLabelCommitted(const FText& InLabel, ETextCommit::Type InCommitInfo);`
- L89 _private prototype_ `FSlateColor GetGroupColor() const;`
- L93 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list to use for context menu actions
- L95 _private member_ `FOnFieldDropEvent OnFieldDropEvent;` — Event called when something is dropped on this group.
- L97 _private member_ `FOnGetGroupId OnGetGroupId;` — Getter for this group's name.
- L99 _private member_ `FOnDeleteGroup OnDeleteGroup;` — Event called then the user deletes the group.
- L101 _private member_ `TSharedPtr<SInlineEditableTextBlock> NameTextBox;` — Holds the text box for the group name.
- L103 _private member_ `TAttribute<bool> bLiveMode;` — Whether the panel is currently in live mode.
- L105 _private member_ `bool bNeedsRename = false;` — Whether the group needs to be renamed. (As requested by a click on the rename button)
- L107 _private member_ `TWeakObjectPtr<URemoteControlPreset> Preset;` — Weak ptr to the preset that contains the field group.
- L109 _private member_ `FName Name;` — Name of the group.
- L111 _private member_ `FGuid Id;` — Id for this group. (Matches the one in the preset layout data.
- L113 _private member_ `TArray<TSharedPtr<SRCPanelTreeNode>> Nodes;` — This group's child nodes

#### class `FFieldGroupDragDropOp`  
`class FFieldGroupDragDropOp final : public FDecoratedDragDropOp`  
_L117-158_
- inherits: `FDecoratedDragDropOp`
- L122 _public typedef_ `using WidgetType = SRCPanelGroup;`
- L124 _public function_ `FFieldGroupDragDropOp(TSharedPtr<SRCPanelGroup> InWidget, FGuid InId) : Id(MoveTemp(InId))`
- L138 _public function_ `FGuid GetGroupId() const`
- L143 _public function_ `virtual void OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent) override`
- L148 _public function_ `virtual TSharedPtr<SWidget> GetDefaultDecorator() const override`
- L155 _private member_ `FGuid Id;` — Id of the held group.
- L157 _private member_ `TSharedPtr<SWidget> DecoratorWidget;` — Holds the displayed widget.

#### Free symbols / members of external scopes

- L31 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(FReply, FOnFieldDropEvent, const TSharedPtr<FDragDropOperation>& , const TSharedPtr<SRCPanelTreeNode>& , const TSharedPtr<SRCPanelTreeNode>& );`
- L32 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FGuid, FOnGetGroupId, const FGuid& );`
- L33 _delegate_ `DECLARE_DELEGATE_OneParam(FOnDeleteGroup, const FGuid& );`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelFunctionPicker.h` (Private)


#### class `SRCPanelFunctionPicker`  
`class SRCPanelFunctionPicker : public SCompoundWidget`  
_L15-62_
- inherits: `SCompoundWidget`
- desc: Widget that displays a picker for blueprint functions.
- L18 _public function_ `SLATE_BEGIN_ARGS(SRCPanelFunctionPicker) : _AllowDefaultObjects(false)`
- L21 _public prototype_ `SLATE_EVENT(FOnSelectFunction, OnSelectFunction) SLATE_ARGUMENT(TSharedPtr<SRemoteControlPanel>, RemoteControlPanel) SLATE_ARGUMENT(UClass*, ObjectClass) SLATE_ARGUMENT(FText, Label) SLATE_ARGUMENT(bool, AllowDefaultObjects) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L31 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L34 _public prototype_ `virtual FReply OnFocusReceived(const FGeometry& MyGeometry, const FFocusEvent& InFocusEvent) override;`
- L35 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L41 _public prototype_ `void Refresh();` — Regenerate the list of functions.
- L45 _private member_ `FOnSelectFunction OnSelectFunction;` — Delegate that handles selecting a function in the picker.
- L47 _private member_ `TArray<TSharedPtr<FRCFunctionPickerTreeNode>> ObjectNodes;` — Holds the object nodes.
- L49 _private member_ `TSharedPtr<SSearchableTreeView<TSharedPtr<FRCFunctionPickerTreeNode>>> ObjectsTreeView;` — Holds the object picker tree view.
- L51 _private member_ `TWeakObjectPtr<UClass> ObjectClass;` — The class used to filter objects available in the dropdown.
- L53 _private member_ `FText Label;` — The label that is displayed on the button.
- L55 _private member_ `bool bAllowDefaultObjects = false;` — Allow default objects when refreshing.
- L57 _private member_ `double LastTimeSinceTick = 0.0;` — Keep track of the last time this widget tick in order to focus it if it's been more than a frame.
- L59 _private member_ `TWeakPtr<SRemoteControlPanel> RemoteControlPanel;` — Keep a weak reference to the RCPanel for access to toolkit host.
- L61 _private prototype_ `UWorld* GetWorld(bool bIgnorePIE = false) const;` — Checks the remote control panel to get a reference to the preset world.

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnSelectFunction, UObject*, UFunction*);`
- L7 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnSelectFunction, UObject*, UFunction*);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelPerPresetProtocolSettings.h` (Private)


#### class `SRCPanelPerPresetProtocolSettings`  
`class SRCPanelPerPresetProtocolSettings : public SCompoundWidget`  
_L12-47_
- inherits: `SCompoundWidget`
- desc: Widget that displays a picker for blueprint functions.
- L15 _public function_ `SLATE_BEGIN_ARGS(SRCPanelPerPresetProtocolSettings)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TWeakObjectPtr<URemoteControlPreset> InPreset);`
- L25 _private prototype_ `void SetupCommandList();` — Creates the command list to use for this widget
- L28 _private prototype_ `TSharedRef<SWidget> CreateSettingsMenu() const;` — Creates the settings menu
- L31 _private prototype_ `void ToggleProtocolsGeneratePropertyChangeEvents();` — Called when the Protocols Generate Property Changed Events setting changed
- L34 _private prototype_ `bool AreProtocolsGeneratingPropertyChangedEvents();` — Returns true if protocols are generating Property Changed Events
- L37 _private prototype_ `void ToggleProtocolsGenerateTransactions();` — Called when the Protocols Generate Transactions setting changed
- L40 _private prototype_ `bool AreProtocolsGeneratingTransactions();` — Returns true if protocols are generating transactions
- L43 _private member_ `TSharedPtr<FUICommandList> CommandList;` — The command list for this widget
- L46 _private member_ `TWeakObjectPtr<URemoteControlPreset> WeakPreset;` — The preset for which the settings are made

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRCPanelTreeNode.h` (Private)


#### enum `ERCColumn::Position`  
`enum Position`  
_L32-39_
- L35 _public enumerator_ `ERC_After` — Places the given column after a specific column.
- L38 _public enumerator_ `ERC_Before` — Places the given column before a specific column.

#### struct `SRCPanelTreeNode`  
`struct SRCPanelTreeNode : public SCompoundWidget, public IHasProtocolExtensibility`  
_L46-187_
- inherits: `SCompoundWidget,IHasProtocolExtensibility`
- desc: A node in the panel tree view.
- L59 _public function_ `virtual ~SRCPanelTreeNode()`
- L62 _public prototype_ `virtual TSharedRef<SWidget> GetProtocolWidget(const FName ForColumnName, const FName InProtocolName = NAME_None) override;`
- L63 _public prototype_ `virtual const bool HasProtocolExtension() const override;`
- L64 _public prototype_ `virtual const bool GetProtocolBindingsNum() const override;`
- L65 _public prototype_ `virtual void OnProtocolTextChanged(const FText& InText, const FName InProtocolName);`
- L66 _public prototype_ `virtual const bool SupportsProtocol(const FName& InProtocolName) const override;`
- L70 _public function_ `virtual void GetNodeChildren(TArray<TSharedPtr<SRCPanelTreeNode>>& OutChildren) const` — Get this tree node's childen.
- L73 _public function_ `virtual FGuid GetRCId() const` — Get this node's ID if any.
- L76 _public function_ `virtual ENodeType GetRCType() const` — Get get this node's type.
- L79 _public function_ `virtual bool HasChildren() const` — Returns true if this tree node has childen.
- L82 _public function_ `virtual void Refresh()` — Refresh the node.
- L85 _public function_ `virtual TSharedPtr<SWidget> GetContextMenu()` — Get the context menu for this node.
- L88 _public function_ `virtual void SetIsHovered(bool bIsBeingHovered)` — Set whether this widget is currently hovered when drag and dropping.
- L91 _public function_ `virtual void EnterRenameMode()` — Make the node name's text box editable.
- L94 _public function_ `virtual FName GetPropertyId()` — Get the PropertyId of this Node.
- L97 _public function_ `virtual void SetPropertyId(FName InNewPropertyId)` — Set the PropertyId of this Node.
- L100 _public function_ `virtual void FocusPropertyIdWidget() const` — Focus the PropertyId widget.
- L103 _public function_ `virtual void SetName(FName InNewName)` — Set the Name of this Node.
- L106 _public function_ `virtual void SetHighlightText(const FText& InHightlightText = FText::GetEmpty())` — Updates the highlight text to active search term.
- L109 _public prototype_ `virtual TSharedRef<SWidget> GetWidget(const FName ForColumnName, const FName InActiveProtocol);` — Retrieves the referenced widget corresponding to the given column name.
- L112 _public prototype_ `TSharedRef<SWidget> GetDragAndDropWidget(int32 InSelectedEntitiesNum = 1);` — Retrieves the DragAndDropWidget if possible otherwise returns a NullWidget.
- L115 _public function_ `FOnLabelModified& OnLabelModified()` — Executed when the Name of the node is changed.
- L118 _public function_ `FOnPropertyIdRenamed& OnPropertyIdRenamed()` — Executed when the PropertyId of the node is changed.
- L132 _protected prototype_ `TSharedRef<SWidget> MakeSplitRow(TSharedRef<SWidget> LeftColumn, TSharedRef<SWidget> RightColumn);` — Create a widget that represents a row with a splitter.
- L135 _protected prototype_ `TSharedRef<SWidget> MakeNodeWidget(const FMakeNodeWidgetArgs& Args);` — Create a widget that represents a node in the panel tree hierarchy.
- L138 _protected prototype_ `void MakeNodeWidgets(const FMakeNodeWidgetArgs& Args);` — Creates cached copies of underlying widgets.
- L142 _private prototype_ `void OnLeftColumnResized(float) const;` — Stub handler for column resize callback to prevent the splitter from handling it internally.
- L145 _private prototype_ `float GetLeftColumnWidth() const;`
- L146 _private prototype_ `float GetRightColumnWidth() const;`
- L147 _private prototype_ `void SetColumnWidth(float InWidth);`
- L152 _public member_ `static TSet<FName> DefaultColumns;` — Columns to be present by default in protocols mode.
- L156 _protected member_ `FRCColumnSizeData ColumnSizeData;` — Holds the row's columns' width.
- L161 _private member_ `TSharedPtr<SWidget> PropertyIdWidget;` — Cached widget of PropertyId identifier.
- L164 _private member_ `TSharedPtr<SWidget> NodeOwnerNameWidget;` — Cached widget of node owner name.
- L167 _private member_ `TSharedPtr<SWidget> SubobjectPathWidget;` — Cached widget of subobject path.
- L170 _private member_ `TSharedPtr<SWidget> NodeNameWidget;` — Cached widget of node name.
- L173 _private member_ `TSharedPtr<SWidget> NodeValueWidget;` — Cached widget of node value.
- L176 _private member_ `TSharedPtr<SWidget> ResetValueWidget;` — Cached widget of reset arrow.
- L180 _private member_ `static constexpr float SplitterOffset = 0.008f;` — The splitter offset to align the group splitter with the other row's splitters.
- L183 _private member_ `FOnLabelModified OnLabelModifiedDelegate;` — Delegate called when the Node Name is renamed.
- L186 _private member_ `FOnPropertyIdRenamed OnPropertyIdRenamedDelegate;` — Delegate called when the Node Property Id change.

#### enum `SRCPanelTreeNode::ENodeType`  
`enum ENodeType`  
_L48-57_
- L50 _public enumerator_ `Invalid`
- L51 _public enumerator_ `Group`
- L52 _public enumerator_ `Field`
- L53 _public enumerator_ `FieldChild`
- L54 _public enumerator_ `Actor`
- L55 _public enumerator_ `Material`
- L56 _public enumerator_ `FieldGroup`

#### struct `SRCPanelTreeNode::FMakeNodeWidgetArgs`  
`struct FMakeNodeWidgetArgs`  
_L121-129_
- L123 _public member_ `TSharedPtr<SWidget> PropertyIdWidget;`
- L124 _public member_ `TSharedPtr<SWidget> OwnerNameWidget;`
- L125 _public member_ `TSharedPtr<SWidget> SubObjectPathWidget;`
- L126 _public member_ `TSharedPtr<SWidget> NameWidget;`
- L127 _public member_ `TSharedPtr<SWidget> ValueWidget;`
- L128 _public member_ `TSharedPtr<SWidget> ResetButton;`

#### Free symbols / members of external scopes

- L18 _namespace_ `namespace RemoteControlPresetColumns`
- L20 _variable_ `static FName PropertyIdentifier = TEXT("Pro` (scope `RemoteControlPresetColumns`)
- L21 _variable_ `static FName OwnerName = TEXT("Own` (scope `RemoteControlPresetColumns`)
- L22 _variable_ `static FName SubobjectPath = TEXT("Sub` (scope `RemoteControlPresetColumns`)
- L23 _variable_ `static FName Description = TEXT("Des` (scope `RemoteControlPresetColumns`)
- L24 _variable_ `static FName Value = TEXT("Val` (scope `RemoteControlPresetColumns`)
- L25 _variable_ `static FName BindingStatus = TEXT("Bin` (scope `RemoteControlPresetColumns`)
- L26 _variable_ `static FName Status = TEXT("Sta` (scope `RemoteControlPresetColumns`)
- L27 _variable_ `static FName Reset = TEXT("Res` (scope `RemoteControlPresetColumns`)
- L30 _namespace_ `namespace ERCColumn`
- L42 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLabelModified, FName , FName ) DECLARE_DELEGATE_OneParam(FOnPropertyIdRenamed, FName ) struct SRCPanelTreeNode : public SCompoundWidget, public IHasProtocolExtensibility { enum ENodeType { Invalid, Group, Field, FieldChild, Actor, Material, FieldGroup }; virtual ~SRCPanelTreeNode() {}`
- L43 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPropertyIdRenamed, FName ) struct SRCPanelTreeNode : public SCompoundWidget, public IHasProtocolExtensibility { enum ENodeType { Invalid, Group, Field, FieldChild, Actor, Material, FieldGroup }; virtual ~SRCPanelTreeNode() {}`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SRemoteControlPanel.h` (Private)


#### enum `ERCPanelMode`  
`enum class ERCPanelMode : uint8`  
_L17-30_
- desc: The variety of panels we have in the RC Panel.
- L19 _public enumerator_ `Controller`
- L21 _public enumerator_ `EntityDetails`
- L23 _public enumerator_ `Protocols`
- L25 _public enumerator_ `OutputLog`
- L27 _public enumerator_ `Live`
- L29 _public enumerator_ `Signature`

#### class `SRemoteControlPanel`  
`class SRemoteControlPanel : public SCompoundWidget, public FGCObject`  
_L75-509_
- inherits: `SCompoundWidget,FGCObject`
- desc: UI representation of a remote control preset. Allows a user to expose/unexpose properties and functions from actors and blueprint libraries.
- L77 _private function_ `SLATE_BEGIN_ARGS(SRemoteControlPanel)`
- L84 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControllerAdded, const FName& );` — Remote Control Logic Delegates
- L85 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerSelectionChanged, TSharedPtr<FRCControllerModel> , ESelectInfo::Type );`
- L86 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControllerValueChanged, TSharedPtr<FRCControllerModel> );`
- L87 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBehaviourAdded, const URCBehaviour* );`
- L88 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBehaviourSelectionChanged, TSharedPtr<FRCBehaviourModel> );`
- L89 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActionAdded, URCAction* );`
- L91 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEmptyControllers);`
- L92 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEmptyBehaviours);`
- L93 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEmptyActions);`
- L95 _public prototype_ `void Construct(const FArguments& InArgs, URemoteControlPreset* InPreset, TSharedPtr<IToolkitHost> InToolkitHost);`
- L96 _public prototype_ `~SRemoteControlPanel();`
- L99 _public prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);`
- L100 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L106 _public function_ `URemoteControlPreset* GetPreset()` — @return The preset represented by the panel.
- L114 _public function_ `const URemoteControlPreset* GetPreset() const` — @return The preset represented by the panel.
- L123 _public prototype_ `bool IsExposed(const FRCExposesPropertyArgs& InArgs);` — @param InArgs extension arguments @return Whether a property is exposed or not.
- L131 _public prototype_ `bool IsAllObjectsExposed(TArray<UObject*> InOuterObjects, const FString& InPropertyPath, bool bUsingDuplicatesInPath);` — @param InOuterObjects outer objects to check @param InPropertyPath full property path @param bUsingDuplicatesInPath whether duplications like property.property[1] should be exists or just property[1] @return Whether objects is exposed or not.
- L138 _public prototype_ `void ExecutePropertyAction(const FRCExposesPropertyArgs& InArgs, const FString& InDesiredName = TEXT(""));` — Exposes or unexposes a property. @param InArgs The extension arguments of the property to toggle. @param InDesiredName Desired Name for this property if leaved empty RC will deduce it itself
- L143 _public prototype_ `FGuid GetSelectedGroup() const;` — Get the selected group.
- L145 _public prototype_ `bool CanActivateMode(ERCPanelMode InPanelMode) const;`
- L146 _public prototype_ `bool IsModeActive(ERCPanelMode InPanelMode) const;`
- L147 _public prototype_ `void SetActiveMode(ERCPanelMode InPanelMode);`
- L152 _public function_ `TSharedPtr<SRCPanelExposedEntitiesList> GetEntityList()` — Get the exposed entity list.
- L155 _public prototype_ `void Refresh();` — Re-create the sections of the panel.
- L158 _public prototype_ `void AddToolbarWidget(TSharedRef<SWidget> Widget);` — Adds or removes widgets from the default toolbar in this asset editor
- L159 _public prototype_ `void RemoveAllToolbarWidgets();`
- L162 _public prototype_ `void DeleteEntity();` — Public Workaround Delete for Key Handling Issues when Docked
- L163 _public prototype_ `void RenameEntity();`
- L166 _public function_ `TSharedPtr<SRCActionPanel> GetLogicActionPanel()` — Retrieves the Logic Action panel.
- L171 _public function_ `TSharedPtr<FUICommandList> GetCommandList() const`
- L177 _public prototype_ `int32 NumControllerItems() const;` — Retrieves the number of controllers.
- L180 _public prototype_ `void SetLogicClipboardItems(const TArray<UObject*>& InItems, const TSharedPtr<SRCLogicPanelBase>& SourcePanel);` — For Copy UI command - Sets the logic clipboard item and source
- L183 _public function_ `TArray<UObject*> GetLogicClipboardItems()` — Fetches the last UI item copied to Logic clipboard by the user
- L189 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L193 _private prototype_ `void ApplyProtocolBindings();` — Applies all the protocol bindings within this widget's owning preset to their respective protocols
- L196 _private prototype_ `void UnapplyProtocolBindings();` — Unapplies all the protocol bindings within this widget's owning preset to their respective protocols
- L199 _private prototype_ `static TSharedRef<SBox> CreateNoneSelectedWidget();` — Returns a Helper widget for entity details view and protocol details view.
- L201 _private prototype_ `TSharedRef<SWidget> BuildLogicModeContent(const TSharedRef<SWidget>& InLogicPanel);`
- L202 _private prototype_ `TSharedRef<SWidget> BuildEntityDetailsModeContent(const TAttribute<float>& InRatioTop, const TAttribute<float>& InRatioBottom);`
- L203 _private prototype_ `TSharedRef<SWidget> BuildProtocolsModeContent(const TAttribute<float>& InRatioTop, const TAttribute<float>& InRatioBottom);`
- L204 _private prototype_ `TSharedRef<SWidget> BuildLiveModeContent(const TSharedRef<SWidget>& InLogicPanel);`
- L205 _private prototype_ `TSharedRef<SWidget> BuildSignaturesModeContent();`
- L208 _private prototype_ `void BindRemoteControlCommands();`
- L211 _private prototype_ `void OnObjectReplaced(const TMap<UObject*, UObject*>& InObjectReplaced);` — Called when object are replaced, blueprint for example
- L214 _private prototype_ `void PostPIEStarted(const bool bInIsSimulating);` — Called when PIE begins
- L217 _private prototype_ `void PostLoadMapWithWorld(UWorld* InWorld);` — Called at the end of LoadMap to keep the remote control preset panel up-to-date with current PIE world
- L220 _private prototype_ `void OnEndPIE(const bool bInIsSimulating);` — Called when PIE ends
- L223 _private prototype_ `void RegisterEvents();` — Register editor events needed to handle reloading objects and blueprint libraries.
- L225 _private prototype_ `void UnregisterEvents();` — Unregister editor events
- L228 _private prototype_ `void Unexpose(const FRCExposesPropertyArgs& InArgs);` — Unexpose a field from the preset.
- L231 _private prototype_ `void OnBlueprintReinstanced();` — Handler called when a blueprint is reinstanced.
- L234 _private prototype_ `void ExposeProperty(UObject* Object, FRCFieldPathInfo FieldPath, FString InDesiredName = TEXT(""));` — Expose a property using its handle.
- L237 _private prototype_ `void ExposeFunction(UObject* Object, UFunction* Function);` — Exposes a function.
- L240 _private prototype_ `void OnExposeActor(const FAssetData& AssetData);` — Handles exposing an actor from asset data.
- L243 _private prototype_ `void ExposeActor(AActor* Actor);` — Handle exposing an actor.
- L246 _private prototype_ `FReply OnClickDisableUseLessCPU() const;` — Handles disabling CPU throttling.
- L249 _private prototype_ `FReply OnClickIgnoreWarnings() const;` — Handles ignoring Warnings.
- L252 _private prototype_ `TSharedRef<SWidget> CreateCPUThrottleWarning() const;` — Creates a widget that warns the user when CPU throttling is enabled.
- L255 _private prototype_ `TSharedRef<SWidget> CreateProtectedIgnoredWarning() const;` — Creates a widget that warns the user when the settings are currently ignoring the Protected flag is enabled.
- L258 _private prototype_ `TSharedRef<SWidget> CreateGetterSetterIgnoredWarning() const;` — Creates a widget that warns the user when the settings are currently ignoring the Getter/Setter is enabled.
- L261 _private prototype_ `TSharedRef<SWidget> CreateExposeFunctionsButton();` — Create expose button, allowing to expose blueprints and actor functions.
- L264 _private prototype_ `TSharedRef<SWidget> CreateExposeActorsButton();` — Create expose button, allowing to expose actors.
- L267 _private prototype_ `TSharedRef<SWidget> CreateExposeByClassWidget();` — Create expose by class menu content
- L270 _private prototype_ `void CacheLevelClasses();` — Cache the classes (and parent classes) of all actors in the level.
- L273 _private prototype_ `void OnActorAddedToLevel(AActor* Actor);`
- L274 _private prototype_ `void OnLevelActorsRemoved(AActor* Actor);`
- L275 _private prototype_ `void OnLevelActorListChanged();`
- L278 _private prototype_ `void CacheActorClass(AActor* Actor);` — Handles caching an actor's class and parent classes.
- L281 _private prototype_ `void OnMapChange(uint32);` — Handles refreshing the class picker when the map is changed.
- L284 _private prototype_ `TSharedRef<SWidget> CreateEntityDetailsView();` — Create the details view for the entity currently selected.
- L287 _private prototype_ `void UpdateEntityDetailsView(const TSharedPtr<SRCPanelTreeNode>& SelectedNode);` — Update the details view following entity selection change.
- L290 _private prototype_ `void UpdateRebindButtonVisibility();` — Returns whether the preset has any unbound property or function.
- L293 _private prototype_ `FReply OnClickRebindAllButton();` — Handle user clicking on the rebind all button.
- L296 _private prototype_ `void OnEntityExposed(URemoteControlPreset* InPreset, const FGuid& InEntityId);`
- L297 _private prototype_ `void OnEntityUnexposed(URemoteControlPreset* InPreset, const FGuid& InEntityId);`
- L300 _private prototype_ `void OnLogCheckboxToggle(ECheckBoxState InState);` — Toggles the logging part of UI
- L303 _private prototype_ `void UpdateActorFunctionPicker();` — Triggers a next frame update of the actor function picker to ensure that added actors are valid.
- L306 _private prototype_ `FReply OnClickSettingsButton();` — Handle clicking on the setting button.
- L309 _private prototype_ `void OnMaterialCompiled(class UMaterialInterface* MaterialInterface);` — Handle triggers each time when any material has been recompiled
- L312 _private prototype_ `void TriggerMaterialCompiledRefresh();` — Refreshed called at max once per frame when a material is compiled.
- L315 _private prototype_ `static void RegisterDefaultToolBar();` — Registers default tool bar
- L318 _private prototype_ `void GenerateToolbar();` — Makes a default asset editing toolbar
- L321 _private prototype_ `static void RegisterAuxiliaryToolBar();` — Registers Auxiliary tool bar
- L324 _private prototype_ `void GenerateAuxiliaryToolbar();` — Makes a Auxiliary asset editing toolbar
- L326 _private prototype_ `FText HandlePresetName() const;`
- L329 _private prototype_ `bool CanSaveAsset() const;` — Called to test if "Save" should be enabled for this asset
- L332 _private prototype_ `void SaveAsset() const;` — Called when "Save" is clicked for this asset
- L335 _private prototype_ `bool CanFindInContentBrowser() const;` — Called to test if "Find in Content Browser" should be enabled for this asset
- L338 _private prototype_ `void FindInContentBrowser() const;` — Called when "Find in Content Browser" is clicked for this asset
- L340 _private prototype_ `static bool ShouldForceSmallIcons();`
- L343 _private prototype_ `void DeleteEntity_Execute();` — Called when user attempts to delete a group/exposed entity.
- L346 _private prototype_ `bool CanDeleteEntity() const;` — Called to test if user is able to delete a group/exposed entity.
- L349 _private prototype_ `void RenameEntity_Execute() const;` — Called when user attempts to rename a group/exposed entity.
- L352 _private prototype_ `bool CanRenameEntity() const;` — Called to test if user is able to rename a group/exposed entity.
- L355 _private prototype_ `void ChangePropertyId_Execute() const;` — Called when user attempts to change property Ids.
- L358 _private prototype_ `bool CanChangePropertyId() const;` — Called to test if user is able to change property Ids.
- L361 _private prototype_ `void CopyItem_Execute();` — Called when user attempts to Copy a logic UI item.
- L364 _private prototype_ `bool CanCopyItem() const;` — Called to test if user is able to Copy a logic UI item.
- L367 _private prototype_ `void PasteItem_Execute();` — Called when user attempts to Paste a logic UI item.
- L370 _private prototype_ `bool CanPasteItem() const;` — Called to test if user is able to Paste a logic UI item.
- L373 _private prototype_ `void DuplicateItem_Execute();` — Called when user attempts to Duplicate a logic UI item.
- L376 _private prototype_ `bool CanDuplicateItem() const;` — Called to test if user is able to Duplicate a logic UI item.
- L379 _private prototype_ `void UpdateValue_Execute();` — Called when user attempts to Update a logic UI item.
- L382 _private prototype_ `bool CanUpdateValue() const;` — Called to test if user is able to Update a logic UI item.
- L385 _private prototype_ `void LoadSettings(const FGuid& InInstanceId) const;` — Loads settings from config based on the preset identifier.
- L388 _private prototype_ `void SaveSettings();` — Saves settings from config based on the preset identifier.
- L391 _private prototype_ `TSharedPtr<SRCLogicPanelBase> GetActiveLogicPanel() const;` — Retrieves active logic panel.
- L394 _private prototype_ `TSharedRef<SWidget> OnGetSelectedWorldButtonContent();` — Get the menu content for the SelectedWorld button
- L397 _private prototype_ `void UpdatePanelForWorld(const UWorld* InWorld);` — Update the panel for the new World
- L400 _private prototype_ `void OpenPanelForEmbeddedPreset(const UWorld* World);` — Handle the TargetWorld change for embedded presets
- L403 _private prototype_ `static void CreateTargetWorldButtonDynamicEntries(UToolMenu* InMenu);` — Handle the TargetWorld ComboButton entries creation
- L406 _private member_ `static const FName DefaultRemoteControlPanelToolBarName;`
- L407 _private member_ `static const FName AuxiliaryRemoteControlPanelToolBarName;`
- L408 _private member_ `static const FName TargetWorldRemoteControlPanelMenuName;`
- L410 _private member_ `TWeakObjectPtr<URemoteControlPreset> PresetWeak;` — Holds a weak reference to the preset asset.
- L412 _private member_ `TSharedPtr<FUICommandList> CommandList;` — Command list of this panel
- L414 _private member_ `FOnLiveModeChange OnLiveModeChange;` — Delegate called when the live mode changes.
- L416 _private member_ `TSharedPtr<SRCPanelFunctionPicker> BlueprintPicker;` — Holds the blueprint library picker
- L418 _private member_ `TSharedPtr<SRCPanelFunctionPicker> ActorFunctionPicker;` — Holds the actor function picker
- L420 _private member_ `TSharedPtr<SRCPanelFunctionPicker> SubsystemFunctionPicker;` — Holds the subsystem function picker.
- L422 _private member_ `TSharedPtr<SRCPanelExposedEntitiesList> EntityList;` — Holds the exposed entity list view.
- L424 _private member_ `TSharedPtr<SComboButton> ExposeFunctionsComboButton;` — Holds the combo button that allows exposing functions.
- L426 _private member_ `TSharedPtr<SComboButton> ExposeActorsComboButton;` — Holds the combo button that allows exposing actors.
- L428 _private member_ `TSet<TWeakObjectPtr<const UClass>> CachedClassesInLevel;` — Caches all the classes of actors in the current level.
- L430 _private member_ `TSharedPtr<SClassViewer> ClassPicker;` — Holds the class picker used to expose all actors of class.
- L432 _private member_ `TSharedPtr<class IStructureDetailsView> EntityDetailsView;` — Holds the field's details.
- L434 _private member_ `TSharedPtr<SBorder> WrappedEntityDetailsView;` — Wrapper widget for entity details view.
- L436 _private member_ `TSharedPtr<SBox> EntityProtocolDetails;` — Holds the field's protocol details.
- L438 _private member_ `bool bShowRebindButton = false;` — Whether to show the rebind all button.
- L440 _private member_ `TSet<FRCExposesPropertyArgs> CachedExposedPropertyArgs;` — Cache of exposed property arguments.
- L442 _private member_ `TSharedPtr<FRCPanelWidgetRegistry> WidgetRegistry;` — Holds a cache of widgets.
- L444 _private member_ `FTimerHandle NextTickTimerHandle;` — Holds the handle to a timer set for next tick. Used to not schedule more than once event per frame
- L446 _private member_ `TWeakPtr<IToolkitHost> ToolkitHost;` — The toolkit that hosts this panel.
- L448 _private member_ `TSharedPtr<SWidget> Toolbar;` — Asset Editor Default Toolbar
- L450 _private member_ `TSharedPtr<SWidget> AuxiliaryToolbar;` — Asset Editor Auxiliary Toolbar
- L452 _private member_ `TSharedPtr<SBorder> ToolbarWidgetContent;` — The widget that will house the default Toolbar widget
- L454 _private member_ `TSharedPtr<SBorder> AuxiliaryToolbarWidgetContent;` — The widget that will house the Auxiliary Toolbar widget
- L456 _private member_ `TArray<TSharedRef<SWidget>> ToolbarWidgets;` — Additional widgets to be added to the toolbar
- L458 _private member_ `TSharedPtr<SRCPanelTreeNode> LastSelectedEntity;` — Holds a shared pointer reference to the last entity that was selected.
- L460 _private member_ `TSharedPtr<SRCPanelDrawer> PanelDrawer;` — Panel Drawer widget holds all docked panels.
- L462 _private member_ `TMap<ERCPanelMode, TSharedRef<FRCPanelDrawerArgs>> RegisteredDrawers;` — Map of Opened Drawers.
- L464 _private member_ `const FRCPanelStyle* RCPanelStyle;` — Panel Style reference.
- L466 _private member_ `ERCPanelMode ActiveMode = ERCPanelMode::Controller;` — Stores the active panel that is drawn.
- L468 _private member_ `FString SelectedWorldName;` — Currently selected world name
- L472 _private member_ `TSharedPtr<SRCControllerPanel> ControllerPanel;` — Controller panel UI widget for Remote Control Logic
- L474 _private member_ `TSharedPtr<SRCBehaviourPanel> BehaviorPanel;` — Behaviour panel UI widget for Remote Control Logic
- L476 _private member_ `TSharedPtr<SRCActionPanel> ActionPanel;` — Action panel UI widget for Remote Control Logic
- L478 _private member_ `TSharedPtr<SRCSignaturePanel> SignaturePanel;` — Signature panel UI widget
- L485 _private member_ `TArray<TObjectPtr<UObject>> LogicClipboardItems;` — LogicClipboardItems - Holds the items copied from a Logic panel Note: We track UObjects (Data Model) here rather than the UI Models as the latter are swept away the moment the user navigates to a different Controller. For example if the user copies an action from a behaviour in a given Controller but then navigates to another Controller, we can no longer rely on the previous UI objects as they would have been discarded in favor of a new data set for the actively selected Controller
- L488 _private function_ `virtual FString GetReferencerName() const override` — FGCObject interface
- L491 _private member_ `bool bMaterialsCompiledThisFrame = false;` — Keeps track of whether materials were compiled from the current frame. Used to limit the number of UI refresh to once per frame.
- L495 _public member_ `static const float MinimumPanelWidth;`
- L497 _public member_ `FOnControllerAdded OnControllerAdded;` — Global Delegates for Remote Control Logic
- L498 _public member_ `FOnBehaviourAdded OnBehaviourAdded;`
- L499 _public member_ `FOnActionAdded OnActionAdded;`
- L500 _public member_ `FOnControllerSelectionChanged OnControllerSelectionChanged;`
- L501 _public member_ `FOnControllerValueChanged OnControllerValueChangedDelegate;`
- L502 _public member_ `FOnBehaviourSelectionChanged OnBehaviourSelectionChanged;`
- L503 _public member_ `FOnEmptyControllers OnEmptyControllers;`
- L504 _public member_ `FOnEmptyBehaviours OnEmptyBehaviours;`
- L505 _public member_ `FOnEmptyActions OnEmptyActions;`
- L508 _public member_ `TSharedPtr<SRCLogicPanelBase> LogicClipboardItemSource;` — The panel from which the latest Logic UI item was copied

#### Free symbols / members of external scopes

- L69 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnLiveModeChange, TSharedPtr<SRemoteControlPanel> , bool );`
- L69 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnLiveModeChange, TSharedPtr<SRemoteControlPanel> , bool );`
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControllerAdded, const FName& );` — Remote Control Logic Delegates
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnControllerSelectionChanged, TSharedPtr<FRCControllerModel> , ESelectInfo::Type );`
- L86 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnControllerValueChanged, TSharedPtr<FRCControllerModel> );`
- L87 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBehaviourAdded, const URCBehaviour* );`
- L88 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBehaviourSelectionChanged, TSharedPtr<FRCBehaviourModel> );`
- L89 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActionAdded, URCAction* );`
- L91 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEmptyControllers);`
- L92 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEmptyBehaviours);`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEmptyActions);`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SSearchableItemList.h` (Private)


#### class `SSearchableItemList`  
`template <typename ItemType> class SSearchableItemList : public SCompoundWidget`  
_L20-212_
- inherits: `SCompoundWidget`
- desc: Widget that displays a searchable dropdown list.
- L23 _public function_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, ItemType ) DECLARE_DELEGATE_RetVal_OneParam(FString, FOnGetDisplayName, ItemType ) SLATE_BEGIN_ARGS(SSearchableItemList)`
- L27 _public function_ `SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_ARGUMENT(TArray<ItemType>, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L68 _public function_ `virtual void Tick(const FGeometry&, const double, const float DeltaTime) override`
- L85 _private function_ `void Refresh()` — Triggers a refresh on the next tick.
- L91 _private function_ `void Populate()` — Create the initial list of items to be displayed.
- L103 _private function_ `TSharedRef<ITableRow> OnGenerateRow(ItemType InObject, const TSharedRef<STableViewBase>& OwnerTable)` — Generates the rows.
- L128 _private function_ `void OnFilterTextChanged(const FText& Text)` — Filter text changed handler.
- L135 _private function_ `void ConstructRow(ItemType Object)` — Add a row if it's not filtered.
- L144 _private function_ `void OnSelectionChanged(ItemType SelectedObject, ESelectInfo::Type SelectInfo)` — Handle selection item selection changed.
- L154 _private function_ `void TransformElementToString(ItemType InObject, TArray<FString>& OutStrings)` — Create the row's display name using the delegate.
- L160 _private function_ `FText GetFilterHighlightText() const` — Handler for getting the rows highlight text.
- L166 _private function_ `FReply OnKeyDown(const FGeometry&, const FKeyEvent& KeyEvent)` — Handler for key down events.
- L187 _private member_ `FOnItemSelected OnItemSelected;` — Item selected delegate.
- L190 _private member_ `FOnGetDisplayName OnGetDisplayName;` — Display name generator delegate.
- L193 _private member_ `TSharedPtr<TTextFilter<ItemType>> SearchBoxFilter;` — Holds the search box filter.
- L196 _private member_ `TSharedPtr<SListView<ItemType>> ListView;` — Holds the list view widget.
- L199 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Holds the search box widget.
- L202 _private member_ `TArray<ItemType> Items;` — Holds the unfiltered item list.
- L205 _private member_ `TArray<ItemType> FilteredItems;` — Holds the filtered item list.
- L208 _private member_ `bool bNeedsRefresh;` — Whether the list should be refreshed on the next tick.
- L211 _private member_ `bool bNeedsFocus;` — Whether the searchbox needs to be focused on the next frame.

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_OneParam(FOnItemSelected, ItemType ) DECLARE_DELEGATE_RetVal_OneParam(FString, FOnGetDisplayName, ItemType ) SLATE_BEGIN_ARGS(SSearchableItemList) {} SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_ARGUMENT(TArray<ItemType>, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { bNeedsRefresh = true; bNeedsFocus = true; Items = InArgs._Items; OnItemSelected = InArgs._OnItemSelected; OnGetDisplayName = InArgs._OnGetDisplayName; ListView = SNew(SListView<ItemType>) .ItemHeight(24) .ListItemsSource(&FilteredItems) .OnGenerateRow(this, &SSearchableItemList::OnGenerateRow) .OnSelectionChanged(this, &SSearchableItemList::OnSelectionChanged) .SelectionMode(ESelectionMode::Single); SearchBoxFilter = MakeShared<TTextFilter<ItemType>>(TTextFilter<ItemType>::FItemToStringArray::CreateSP(this, &SSearchableItemList::TransformElementToString)); ChildSlot [ SNew(SVerticalBox) + SVerticalBox::Slot() .Padding(7.0f, 6.0f) .AutoHeight() [ SAssignNew(SearchBox, SSearchBox) .OnTextChanged(this, &SSearchableItemList::OnFilterTextChanged) .OnKeyDownHandler(this, &SSearchableItemList::OnKeyDown) ] + SVerticalBox::Slot() [`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FString, FOnGetDisplayName, ItemType ) SLATE_BEGIN_ARGS(SSearchableItemList) {} SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_ARGUMENT(TArray<ItemType>, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { bNeedsRefresh = true; bNeedsFocus = true; Items = InArgs._Items; OnItemSelected = InArgs._OnItemSelected; OnGetDisplayName = InArgs._OnGetDisplayName; ListView = SNew(SListView<ItemType>) .ItemHeight(24) .ListItemsSource(&FilteredItems) .OnGenerateRow(this, &SSearchableItemList::OnGenerateRow) .OnSelectionChanged(this, &SSearchableItemList::OnSelectionChanged) .SelectionMode(ESelectionMode::Single); SearchBoxFilter = MakeShared<TTextFilter<ItemType>>(TTextFilter<ItemType>::FItemToStringArray::CreateSP(this, &SSearchableItemList::TransformElementToString)); ChildSlot [ SNew(SVerticalBox) + SVerticalBox::Slot() .Padding(7.0f, 6.0f) .AutoHeight() [ SAssignNew(SearchBox, SSearchBox) .OnTextChanged(this, &SSearchableItemList::OnFilterTextChanged) .OnKeyDownHandler(this, &SSearchableItemList::OnKeyDown) ] + SVerticalBox::Slot() [ ListView.ToSharedRef()`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/SSearchableTreeView.h` (Private)


#### class `SSearchableTreeView`  
`template <typename ItemType> class SSearchableTreeView : public SCompoundWidget`  
_L20-327_
- inherits: `SCompoundWidget`
- desc: Widget that displays a searchable tree view.
- L23 _public function_ `DECLARE_DELEGATE_TwoParams(FOnItemSelected, ItemType , ItemType ) DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetDisplayName, ItemType ) DECLARE_DELEGATE_TwoParams(FOnGetChildren, ItemType , TArray<ItemType>& ) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsSelectable, ItemType ) SLATE_BEGIN_ARGS(SSearchableTreeView)`
- L29 _public function_ `SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetChildren, OnGetChildren) SLATE_EVENT(FIsSelectable, IsSelectable) SLATE_ARGUMENT(TArray<ItemType>*, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs)`
- L78 _public function_ `virtual void Tick(const FGeometry&, const double, const float DeltaTime) override`
- L94 _public function_ `void Refresh()` — Triggers a refresh on the next tick.
- L100 _public function_ `void Focus()` — Focuses the search text box.
- L106 _public function_ `void ClearSearchBox()` — Clears this TreeView's search box.
- L114 _private function_ `void Populate()` — Create the initial list of items to be displayed.
- L128 _private function_ `TSharedRef<ITableRow> OnGenerateRow(ItemType InObject, const TSharedRef<STableViewBase>& OwnerTable)` — Generates the rows.
- L152 _private function_ `void OnGetChildren(ItemType Item, TArray<ItemType>& OutChildren) const`
- L168 _private function_ `void OnFilterTextChanged(const FText& Text)` — Filter text changed handler.
- L175 _private function_ `void ConstructRow(ItemType Object)` — Add a row if it's not filtered.
- L204 _private function_ `void OnSelectionChanged(ItemType SelectedObject, ESelectInfo::Type SelectInfo)` — Handle selection item selection changed.
- L221 _private function_ `void OnMouseClick(ItemType SelectedObject)` — Handle an item being clicked
- L236 _private function_ `void TransformElementToString(ItemType InObject, TArray<FString>& OutStrings)` — Create the row's display name using the delegate.
- L242 _private function_ `FText GetFilterHighlightText() const` — Handler for getting the rows highlight text.
- L248 _private function_ `virtual FReply OnKeyDown(const FGeometry&, const FKeyEvent& KeyEvent) override` — Handler for key down events.
- L272 _private function_ `ItemType GetParent(const ItemType& InItem)`
- L296 _private member_ `FOnItemSelected OnItemSelected;` — Item selected delegate.
- L299 _private member_ `FIsSelectable IsSelectable;` — Checks if an item is selectable.
- L302 _private member_ `FOnGetDisplayName OnGetDisplayName;` — Display name generator delegate.
- L305 _private member_ `FOnGetChildren OnGetChildrenDelegate;` — Get an item's children delegate.
- L308 _private member_ `TSharedPtr<TTextFilter<ItemType>> SearchBoxFilter;` — Holds the search box filter.
- L311 _private member_ `TSharedPtr<STreeView<ItemType>> TreeView;` — Holds the list view widget.
- L314 _private member_ `TSharedPtr<SSearchBox> SearchBox;` — Holds the search box widget.
- L317 _private member_ `TArray<ItemType>* Items;` — Holds the unfiltered item list.
- L320 _private member_ `TArray<ItemType> FilteredItems;` — Holds the filtered item list.
- L323 _private member_ `bool bNeedsRefresh;` — Whether the list should be refreshed on the next tick.
- L326 _private member_ `bool bNeedsFocus;` — Whether the searchbox needs to be focused on the next frame.

#### Free symbols / members of external scopes

- L23 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnItemSelected, ItemType , ItemType ) DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetDisplayName, ItemType ) DECLARE_DELEGATE_TwoParams(FOnGetChildren, ItemType , TArray<ItemType>& ) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsSelectable, ItemType ) SLATE_BEGIN_ARGS(SSearchableTreeView) {} SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetChildren, OnGetChildren) SLATE_EVENT(FIsSelectable, IsSelectable) SLATE_ARGUMENT(TArray<ItemType>*, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { bNeedsRefresh = true; bNeedsFocus = true; Items = InArgs._Items; checkSlow(Items); OnItemSelected = InArgs._OnItemSelected; OnGetDisplayName = InArgs._OnGetDisplayName; OnGetChildrenDelegate = InArgs._OnGetChildren; IsSelectable = InArgs._IsSelectable; TreeView = SNew(STreeView<ItemType>) .TreeItemsSource(&FilteredItems) .OnGenerateRow(this, &SSearchableTreeView::OnGenerateRow) .OnGetChildren(this, &SSearchableTreeView::OnGetChildren) .OnSelectionChanged(this, &SSearchableTreeView::OnSelectionChanged) .OnMouseButtonClick(this, &SSearchableTreeView::OnMouseClick); SearchBoxFilter = MakeShared<TTextFilter<ItemType>>(TTextFilter<ItemType>::FItemToStringArray::CreateSP(this, &SSearchableTreeView::TransformElementToString)); ChildSlot [ SNew(SVerticalBox) + SVerticalBox::Slot() .Padding(7.0f, 6.0f)`
- L24 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FText, FOnGetDisplayName, ItemType ) DECLARE_DELEGATE_TwoParams(FOnGetChildren, ItemType , TArray<ItemType>& ) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsSelectable, ItemType ) SLATE_BEGIN_ARGS(SSearchableTreeView) {} SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetChildren, OnGetChildren) SLATE_EVENT(FIsSelectable, IsSelectable) SLATE_ARGUMENT(TArray<ItemType>*, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { bNeedsRefresh = true; bNeedsFocus = true; Items = InArgs._Items; checkSlow(Items); OnItemSelected = InArgs._OnItemSelected; OnGetDisplayName = InArgs._OnGetDisplayName; OnGetChildrenDelegate = InArgs._OnGetChildren; IsSelectable = InArgs._IsSelectable; TreeView = SNew(STreeView<ItemType>) .TreeItemsSource(&FilteredItems) .OnGenerateRow(this, &SSearchableTreeView::OnGenerateRow) .OnGetChildren(this, &SSearchableTreeView::OnGetChildren) .OnSelectionChanged(this, &SSearchableTreeView::OnSelectionChanged) .OnMouseButtonClick(this, &SSearchableTreeView::OnMouseClick); SearchBoxFilter = MakeShared<TTextFilter<ItemType>>(TTextFilter<ItemType>::FItemToStringArray::CreateSP(this, &SSearchableTreeView::TransformElementToString)); ChildSlot [ SNew(SVerticalBox) + SVerticalBox::Slot() .Padding(7.0f, 6.0f) .AutoHeight()`
- L25 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGetChildren, ItemType , TArray<ItemType>& ) DECLARE_DELEGATE_RetVal_OneParam(bool, FIsSelectable, ItemType ) SLATE_BEGIN_ARGS(SSearchableTreeView) {} SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetChildren, OnGetChildren) SLATE_EVENT(FIsSelectable, IsSelectable) SLATE_ARGUMENT(TArray<ItemType>*, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { bNeedsRefresh = true; bNeedsFocus = true; Items = InArgs._Items; checkSlow(Items); OnItemSelected = InArgs._OnItemSelected; OnGetDisplayName = InArgs._OnGetDisplayName; OnGetChildrenDelegate = InArgs._OnGetChildren; IsSelectable = InArgs._IsSelectable; TreeView = SNew(STreeView<ItemType>) .TreeItemsSource(&FilteredItems) .OnGenerateRow(this, &SSearchableTreeView::OnGenerateRow) .OnGetChildren(this, &SSearchableTreeView::OnGetChildren) .OnSelectionChanged(this, &SSearchableTreeView::OnSelectionChanged) .OnMouseButtonClick(this, &SSearchableTreeView::OnMouseClick); SearchBoxFilter = MakeShared<TTextFilter<ItemType>>(TTextFilter<ItemType>::FItemToStringArray::CreateSP(this, &SSearchableTreeView::TransformElementToString)); ChildSlot [ SNew(SVerticalBox) + SVerticalBox::Slot() .Padding(7.0f, 6.0f) .AutoHeight() [`
- L26 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FIsSelectable, ItemType ) SLATE_BEGIN_ARGS(SSearchableTreeView) {} SLATE_EVENT(FOnGetDisplayName, OnGetDisplayName) SLATE_EVENT(FOnItemSelected, OnItemSelected) SLATE_EVENT(FOnGetChildren, OnGetChildren) SLATE_EVENT(FIsSelectable, IsSelectable) SLATE_ARGUMENT(TArray<ItemType>*, Items) SLATE_END_ARGS() void Construct(const FArguments& InArgs) { bNeedsRefresh = true; bNeedsFocus = true; Items = InArgs._Items; checkSlow(Items); OnItemSelected = InArgs._OnItemSelected; OnGetDisplayName = InArgs._OnGetDisplayName; OnGetChildrenDelegate = InArgs._OnGetChildren; IsSelectable = InArgs._IsSelectable; TreeView = SNew(STreeView<ItemType>) .TreeItemsSource(&FilteredItems) .OnGenerateRow(this, &SSearchableTreeView::OnGenerateRow) .OnGetChildren(this, &SSearchableTreeView::OnGetChildren) .OnSelectionChanged(this, &SSearchableTreeView::OnSelectionChanged) .OnMouseButtonClick(this, &SSearchableTreeView::OnMouseClick); SearchBoxFilter = MakeShared<TTextFilter<ItemType>>(TTextFilter<ItemType>::FItemToStringArray::CreateSP(this, &SSearchableTreeView::TransformElementToString)); ChildSlot [ SNew(SVerticalBox) + SVerticalBox::Slot() .Padding(7.0f, 6.0f) .AutoHeight() [ SAssignNew(SearchBox, SSearchBox)`
- L163 _function_ `OutChildren.Append(FilteredChildren.FilterByPredicate([this](const ItemType& ChildItem){ return SearchBoxFilter->PassesFilter(ChildItem); }));` (scope `SSearchableTreeView::OnGetChildren`)
- L185 _function_ `` (scope `SSearchableTreeView::ConstructRow`)

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Actions/RCSignatureActionColumn.h` (Private)


#### class `FRCSignatureActionColumn`  
`class FRCSignatureActionColumn : public IRCSignatureColumn`  
_L10-28_
- inherits: `IRCSignatureColumn`
- L13 _public prototype_ `explicit FRCSignatureActionColumn(const TAttribute<bool>& InLiveMode);`
- L17 _private prototype_ `virtual FName GetColumnId() const override;`
- L18 _private prototype_ `virtual bool ShouldShowColumnByDefault() const override;`
- L19 _private prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L20 _private prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(TSharedPtr<FRCSignatureTreeItemBase> InItem, const TSharedRef<SRCSignatureTree>& InList, const TSharedRef<SRCSignatureRow>& InRow) override;`
- L23 _private prototype_ `void RefreshActionTypes(const TSharedRef<FRCSignatureTreeFieldItem>& InFieldItem);`
- L25 _private member_ `TArray<TSharedPtr<FRCSignatureActionType>> ActionTypes;`
- L27 _private member_ `TAttribute<bool> LiveMode;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Actions/RCSignatureActionType.h` (Private)


#### struct `FRCSignatureActionType`  
`struct FRCSignatureActionType`  
_L12-22_
- desc: Struct to describe an Item in the Action Type combo box
- L15 _public member_ `const UScriptStruct* Type = nullptr;` — Struct type of the Action to create if selected
- L18 _public member_ `FText Title;` — Display Name Text in the combo box entry
- L21 _public member_ `FRCSignatureActionIcon Icon;` — Icon and color in the combo box entry

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Actions/SRCSignatureAction.h` (Private)


#### class `SRCSignatureAction`  
`class SRCSignatureAction : public SCompoundWidget`  
_L11-39_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureAction)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FRCSignatureTreeActionItem>& InActionItem);`
- L21 _protected prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L22 _protected prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L23 _protected prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& InCaptureLostEvent) override;`
- L27 _private prototype_ `bool IsPressed() const;`
- L28 _private prototype_ `void SetPressed(bool bInPressed);`
- L30 _private prototype_ `const FSlateBrush* GetBackgroundBrush() const;`
- L32 _private member_ `TWeakPtr<FRCSignatureTreeActionItem> ActionItemWeak;`
- L34 _private member_ `TSharedPtr<SRCSignatureActionIcon> ActionImage;`
- L36 _private member_ `const FCheckBoxStyle* CheckBoxStyle = nullptr;`
- L38 _private member_ `bool bIsPressed = false;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Actions/SRCSignatureActionBox.h` (Private)


#### class `SRCSignatureActionBox`  
`class SRCSignatureActionBox : public SCompoundWidget`  
_L15-52_
- inherits: `SCompoundWidget`
- L18 _public typedef_ `using FOnRefreshActionTypes = TDelegate<void(const TSharedRef<FRCSignatureTreeFieldItem>&)>;`
- L20 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureActionBox)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(bool, LiveMode) SLATE_ITEMS_SOURCE_ARGUMENT(TSharedPtr<FRCSignatureActionType>, ActionTypesSource) SLATE_EVENT(FOnRefreshActionTypes, OnRefreshActionTypes) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FRCSignatureTreeItemBase>& InItem, const TSharedRef<SRCSignatureRow>& InRow);`
- L29 _private prototype_ `void Refresh();`
- L31 _private prototype_ `void OnComboBoxOpening();`
- L33 _private prototype_ `bool CanAddAction() const;`
- L35 _private prototype_ `EVisibility GetAddActionVisibility() const;`
- L37 _private prototype_ `TSharedRef<SWidget> GenerateActionTypeWidget(TSharedPtr<FRCSignatureActionType> InActionType);`
- L39 _private prototype_ `void OnActionTypeSelected(TSharedPtr<FRCSignatureActionType> InActionType, ESelectInfo::Type InSelectType);`
- L41 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FRCSignatureActionType>>> ActionTypesComboBox;`
- L43 _private member_ `TWeakPtr<FRCSignatureTreeItemBase> ItemWeak;`
- L45 _private member_ `TSharedPtr<SScrollBox> ActionListBox;`
- L47 _private member_ `FOnRefreshActionTypes OnRefreshActionTypes;`
- L49 _private member_ `TAttribute<bool> IsHovered;`
- L50 _private member_ `TAttribute<bool> IsSelected;`
- L51 _private member_ `TAttribute<bool> LiveMode;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Actions/SRCSignatureActionIcon.h` (Private)


#### class `SRCSignatureActionIcon`  
`class SRCSignatureActionIcon : public SCompoundWidget`  
_L10-25_
- inherits: `SCompoundWidget`
- L13 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureActionIcon)`
- L14 _public prototype_ `SLATE_ARGUMENT(FRCSignatureActionIcon, ActionIcon) SLATE_END_ARGS() static constexpr float IconSize = 16.f;`
- L19 _public prototype_ `void Construct(const FArguments& InArgs);`
- L21 _public prototype_ `void SetActionIcon(const FRCSignatureActionIcon& InActionIcon);`
- L24 _private member_ `TSharedPtr<SLayeredImage> LayeredImage;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Description/RCSignatureDescriptionColumn.h` (Private)


#### class `FRCSignatureDescriptionColumn`  
`class FRCSignatureDescriptionColumn : public IRCSignatureColumn`  
_L7-15_
- inherits: `IRCSignatureColumn`
- L10 _private prototype_ `virtual FName GetColumnId() const override;`
- L11 _private prototype_ `virtual bool ShouldShowColumnByDefault() const override;`
- L12 _private prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L13 _private prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(TSharedPtr<FRCSignatureTreeItemBase> InItem, const TSharedRef<SRCSignatureTree>& InList, const TSharedRef<SRCSignatureRow>& InRow) override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Description/SRCSignatureDescription.h` (Private)


#### class `SRCSignatureDescription`  
`class SRCSignatureDescription : public SCompoundWidget`  
_L9-23_
- inherits: `SCompoundWidget`
- L12 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureDescription)`
- L13 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FRCSignatureTreeItemBase>& InItem);`
- L18 _private prototype_ `FText GetDescription() const;`
- L20 _private member_ `TWeakPtr<FRCSignatureTreeItemBase> ItemWeak;`
- L22 _private member_ `mutable TOptional<FText> CachedDescription;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Details/SRCSignatureDetails.h` (Private)


#### class `SRCSignatureDetails`  
`class SRCSignatureDetails : public SCompoundWidget, public FNotifyHook`  
_L18-50_
- inherits: `SCompoundWidget,FNotifyHook`
- L21 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureDetails)`
- L22 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, URCSignatureRegistry* InSignatureRegistry, const TSharedRef<FRCSignatureTreeItemSelection>& InSelection);`
- L28 _public prototype_ `void Refresh();`
- L31 _private prototype_ `void GatherStructOnScopes(TArray<TSharedPtr<FStructOnScope>>& OutStructOnScopes, TArray<TWeakPtr<FRCSignatureTreeItemBase>>& OutItems) const;`
- L33 _private prototype_ `void OnFinishedChangingProperties(const FPropertyChangedEvent& InChangeEvent);`
- L36 _private prototype_ `virtual void NotifyPreChange(FEditPropertyChain* InPropertyAboutToChange) override;`
- L37 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged) override;`
- L40 _private member_ `TSharedPtr<IStructureDetailsView> StructDetailsView;`
- L42 _private member_ `TSharedPtr<FScopedTransaction> CurrentTransaction;`
- L44 _private member_ `TWeakObjectPtr<URCSignatureRegistry> SignatureRegistryWeak;`
- L46 _private member_ `TWeakPtr<FRCSignatureTreeItemSelection> SelectionWeak;`
- L49 _private member_ `TArray<TWeakPtr<FRCSignatureTreeItemBase>> ViewedItems;` — Currently viewed items in the Details Panel

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/IRCSignatureColumn.h` (Private)


#### class `IRCSignatureColumn`  
`class IRCSignatureColumn : public TSharedFromThis<IRCSignatureColumn>`  
_L12-33_
- inherits: `TSharedFromThis<IRCSignatureColumn>`
- L15 _public prototype_ `virtual ~IRCSignatureColumn() = default;`
- L17 _public prototype_ `virtual FName GetColumnId() const = 0;`
- L23 _public function_ `virtual bool ShouldShowColumnByDefault() const` — Determines whether the Column should be Showing by Default while still be able to toggle it on/off. Used when calling SHeaderRow::SetShowGeneratedColumn (requires ShouldGenerateWidget to not be set).
- L28 _public prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() = 0;`
- L30 _public prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(TSharedPtr<FRCSignatureTreeItemBase> InItem , const TSharedRef<SRCSignatureTree>& InList , const TSharedRef<SRCSignatureRow>& InRow) = 0;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Items/RCSignatureTreeActionItem.h` (Private)


#### class `FRCSignatureTreeActionItem`  
`class FRCSignatureTreeActionItem : public FRCSignatureTreeItemBase`  
_L14-45_
- inherits: `FRCSignatureTreeItemBase`
- desc: Item class representing a Field owned by a Signature
- L17 _public member_ `static constexpr ERCSignatureTreeItemType StaticItemType = ERCSignatureTreeItemType::Action;`
- L19 _public prototype_ `explicit FRCSignatureTreeActionItem(int32 InActionIndex, const TSharedPtr<SRCSignatureTree>& InSignatureTree);`
- L21 _public prototype_ `const FRCSignatureActionInstance* FindActionInstance() const;`
- L23 _public prototype_ `FRCSignatureActionInstance* FindActionInstanceMutable();`
- L25 _public prototype_ `FRCSignatureActionIcon GetIcon() const;`
- L29 _protected prototype_ `virtual void BuildPathSegment(FStringBuilderBase& InStringBuilder) const override;`
- L30 _protected prototype_ `virtual TOptional<bool> IsEnabled() const override;`
- L31 _protected prototype_ `virtual int32 RemoveFromRegistry() override;`
- L32 _protected prototype_ `virtual FText GetDisplayNameText() const override;`
- L33 _protected prototype_ `virtual FText GetDescription() const override;`
- L34 _protected prototype_ `virtual TSharedPtr<FStructOnScope> MakeSelectionStruct() override;`
- L35 _protected prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged) override;`
- L36 _protected function_ `virtual ERCSignatureTreeItemType GetItemType() const override`
- L40 _private prototype_ `TSharedPtr<FRCSignatureTreeFieldItem> GetParentFieldItem() const;`
- L42 _private prototype_ `FRCSignatureField* FindParentFieldMutable(URCSignatureRegistry** OutRegistry = nullptr);`
- L44 _private member_ `int32 ActionIndex;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Items/RCSignatureTreeFieldItem.h` (Private)


#### class `FRCSignatureTreeFieldItem`  
`class FRCSignatureTreeFieldItem : public FRCSignatureTreeItemBase`  
_L13-47_
- inherits: `FRCSignatureTreeItemBase`
- desc: Item class representing a Field owned by a Signature
- L16 _public member_ `static constexpr ERCSignatureTreeItemType StaticItemType = ERCSignatureTreeItemType::Field;`
- L18 _public prototype_ `explicit FRCSignatureTreeFieldItem(int32 InFieldIndex, const TSharedPtr<SRCSignatureTree>& InSignatureTree);`
- L20 _public prototype_ `const FRCSignatureField* FindField() const;`
- L22 _public prototype_ `FRCSignatureField* FindFieldMutable(URCSignatureRegistry** OutRegistry);`
- L24 _public prototype_ `void AddAction(const UScriptStruct* InActionType);`
- L28 _protected prototype_ `virtual void BuildPathSegment(FStringBuilderBase& InStringBuilder) const override;`
- L29 _protected prototype_ `virtual TOptional<bool> IsEnabled() const override;`
- L30 _protected prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L31 _protected prototype_ `virtual FText GetDisplayNameText() const override;`
- L32 _protected prototype_ `virtual FText GetDescription() const override;`
- L33 _protected prototype_ `virtual int32 RemoveFromRegistry() override;`
- L34 _protected function_ `virtual ERCSignatureTreeItemType GetItemType() const override`
- L35 _protected prototype_ `virtual void GenerateChildren(TArray<TSharedPtr<FRCSignatureTreeItemBase>>& OutChildren) const override;`
- L39 _private prototype_ `TSharedPtr<FRCSignatureTreeSignatureItem> GetParentSignatureItem() const;`
- L41 _private prototype_ `FRCSignature* FindParentSignature(URCSignatureRegistry** OutRegistry);`
- L44 _private prototype_ `void ForEachSiblingFieldItem(TFunctionRef<void(const TSharedPtr<FRCSignatureTreeFieldItem>&)> InCallable);` — Iterates each field item sibling
- L46 _private member_ `int32 FieldIndex;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Items/RCSignatureTreeItemBase.h` (Private)


#### enum `ERCSignatureTreeItemViewFlags`  
`enum class ERCSignatureTreeItemViewFlags : uint8`  
_L13-18_
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Expanded = 1 << 0`
- L17 _public enumerator_ `Hidden = 1 << 1`

#### enum `ERCSignatureTreeItemType`  
`enum class ERCSignatureTreeItemType : uint8`  
_L21-28_
- L23 _public enumerator_ `Undefined`
- L24 _public enumerator_ `Root`
- L25 _public enumerator_ `Signature`
- L26 _public enumerator_ `Field`
- L27 _public enumerator_ `Action`

#### class `FRCSignatureTreeItemBase`  
`class FRCSignatureTreeItemBase : public FRCLogicModeBase`  
_L31-214_
- inherits: `FRCLogicModeBase`
- desc: Base class for any Item represented in the Signature Tree
- L36 _public member_ `static const FLazyName SignatureTreeItemName;`
- L43 _public function_ `template<typename T, typename... ArgTypes UE_REQUIRES(std::is_base_of_v<FRCSignatureTreeItemBase, T>)> static TSharedRef<T> Create(const TSharedPtr<FRCSignatureTreeItemBase>& InParent, ArgTypes&&... InArgs)` — Creates an Item and Initializes it with the given Parent NOTE: this does not build/make child items. RebuildChildren would need to be called separately if necessary.
- L50 _public prototype_ `explicit FRCSignatureTreeItemBase(const TSharedPtr<SRCSignatureTree>& InSignatureTree);`
- L52 _public function_ `virtual FName GetModelType() const override`
- L57 _public prototype_ `virtual int32 RemoveModel() override;`
- L59 _public function_ `virtual TOptional<bool> IsEnabled() const`
- L64 _public function_ `virtual void SetEnabled(bool bInEnabled)`
- L68 _public function_ `FName GetPathId() const`
- L73 _public function_ `ERCSignatureTreeItemViewFlags GetTreeViewFlags() const`
- L78 _public prototype_ `void AddTreeViewFlags(ERCSignatureTreeItemViewFlags InFlags);`
- L80 _public prototype_ `void RemoveTreeViewFlags(ERCSignatureTreeItemViewFlags InFlags);`
- L82 _public prototype_ `bool HasAnyTreeViewFlags(ERCSignatureTreeItemViewFlags InFlags) const;`
- L84 _public function_ `virtual FText GetDisplayNameText() const`
- L89 _public function_ `virtual void SetRenaming(bool bInRenaming)`
- L97 _public function_ `virtual TMulticastDelegateRegistration<void(bool)>* GetOnRenameStateChanged() const` — Gets the Rename Delegate @return the delegate to when renaming state changes, or nullptr if item does not support renaming
- L102 _public function_ `virtual void SetDisplayNameText(const FText& InText)`
- L106 _public function_ `virtual FText GetDescription() const`
- L111 _public function_ `virtual int32 RemoveFromRegistry()`
- L116 _public prototype_ `void SetSelected(bool bInSelected, bool bInIsMultiSelection);`
- L118 _public prototype_ `bool IsSelected() const;`
- L121 _public function_ `virtual TSharedPtr<FStructOnScope> MakeSelectionStruct()` — Optional: makes a struct on scope for selection visualization in Details Panel
- L127 _public function_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged)` — Called when the Selection Struct created for this Item is changed via the Details Panel
- L131 _public function_ `virtual ERCSignatureTreeItemType GetItemType() const`
- L137 _public function_ `template<typename InItemType> TSharedPtr<InItemType> MutableCast()`
- L147 _public function_ `template<typename InItemType> TSharedPtr<const InItemType> Cast() const`
- L156 _public function_ `TConstArrayView<TSharedPtr<FRCSignatureTreeItemBase>> GetChildren() const`
- L161 _public function_ `TSharedPtr<FRCSignatureTreeItemBase> GetParent() const`
- L166 _public function_ `TSharedPtr<SRCSignatureTree> GetSignatureTree() const`
- L171 _public prototype_ `void RebuildChildren();`
- L173 _public prototype_ `void VisitChildren(TFunctionRef<bool(const TSharedPtr<FRCSignatureTreeItemBase>&)> InCallable, bool bInRecursive);`
- L177 _protected prototype_ `void RebuildPath();` — Called when needing to recalculate a new path to the item
- L179 _protected function_ `virtual void BuildPathSegment(FStringBuilderBase& InBuilder) const`
- L183 _protected function_ `virtual void GenerateChildren(TArray<TSharedPtr<FRCSignatureTreeItemBase>>& OutChildren) const`
- L187 _protected function_ `virtual void PostChildrenRebuild()`
- L192 _private prototype_ `void Initialize(const TSharedPtr<FRCSignatureTreeItemBase>& InParent);`
- L194 _private prototype_ `void RestoreFrom(const TSharedPtr<FRCSignatureTreeItemBase>& InOldItem);`
- L196 _private prototype_ `TSharedPtr<FRCSignatureTreeItemSelection> GetRootSelection() const;`
- L199 _private prototype_ `FName BuildPath() const;` — Builds the path from the root to the item. Each item will be its own segment delimited by a dot
- L202 _private member_ `FName Path;` — Unique path from the root to the item. Used to identify items in the Signature Tree
- L204 _private member_ `TArray<TSharedPtr<FRCSignatureTreeItemBase>> Children;`
- L206 _private member_ `TWeakPtr<FRCSignatureTreeItemBase> ParentWeak;`
- L208 _private member_ `TWeakPtr<SRCSignatureTree> SignatureTreeWeak;`
- L210 _private member_ `ERCSignatureTreeItemViewFlags TreeViewFlags = ERCSignatureTreeItemViewFlags::Expanded;`
- L213 _private member_ `mutable TWeakPtr<FRCSignatureTreeItemSelection> SelectionWeak;` — Cached weak pointer to the selection object to avoid having to go up the hierarchy to find it

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Items/RCSignatureTreeRootItem.h` (Private)


#### class `FRCSignatureTreeRootItem`  
`class FRCSignatureTreeRootItem : public FRCSignatureTreeItemBase`  
_L13-39_
- inherits: `FRCSignatureTreeItemBase`
- desc: Item class for the Root of all items This is primarily so that the Top level items can have the same set of functionalities as the rest of the items in the tree
- L16 _public member_ `static constexpr ERCSignatureTreeItemType StaticItemType = ERCSignatureTreeItemType::Root;`
- L18 _public prototype_ `explicit FRCSignatureTreeRootItem(const TSharedPtr<SRCSignatureTree>& InSignatureTree);`
- L20 _public function_ `TArray<TSharedPtr<FRCSignatureTreeItemBase>>& GetChildrenMutable()`
- L25 _public function_ `const TSharedRef<FRCSignatureTreeItemSelection>& GetSelection() const`
- L32 _protected function_ `virtual void BuildPathSegment(FStringBuilderBase& InBuilder) const override`
- L33 _protected function_ `virtual ERCSignatureTreeItemType GetItemType() const`
- L34 _protected prototype_ `virtual void GenerateChildren(TArray<TSharedPtr<FRCSignatureTreeItemBase>>& OutChildren) const override;`
- L35 _protected prototype_ `virtual void PostChildrenRebuild() override;`
- L38 _protected member_ `TSharedRef<FRCSignatureTreeItemSelection> Selection;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Items/RCSignatureTreeSignatureItem.h` (Private)


#### class `FRCSignatureTreeSignatureItem`  
`class FRCSignatureTreeSignatureItem : public FRCSignatureTreeItemBase, public IRCSignatureItem`  
_L16-62_
- inherits: `FRCSignatureTreeItemBase,IRCSignatureItem`
- desc: Item class representing an RC Signature
- L19 _public member_ `static constexpr ERCSignatureTreeItemType StaticItemType = ERCSignatureTreeItemType::Signature;`
- L21 _public prototype_ `explicit FRCSignatureTreeSignatureItem(const FRCSignature& InSignature, const TSharedPtr<SRCSignatureTree>& InSignatureTree);`
- L23 _public prototype_ `const FGuid& GetSignatureId() const;`
- L25 _public prototype_ `URCSignatureRegistry* GetRegistry() const;`
- L27 _public prototype_ `const FRCSignature* FindSignature() const;`
- L29 _public prototype_ `FRCSignature* FindSignatureMutable(URCSignatureRegistry* InRegistry);`
- L31 _public prototype_ `bool AddField(URCSignatureRegistry* InRegistry, const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L34 _public prototype_ `virtual void ApplySignature(TConstArrayView<TWeakObjectPtr<UObject>> InObjects) override;`
- L39 _protected prototype_ `virtual void BuildPathSegment(FStringBuilderBase& InBuilder) const override;`
- L40 _protected prototype_ `virtual TOptional<bool> IsEnabled() const override;`
- L41 _protected prototype_ `virtual void SetEnabled(bool bInEnabled) override;`
- L42 _protected prototype_ `virtual FText GetDisplayNameText() const override;`
- L43 _protected prototype_ `virtual void SetRenaming(bool bInRenaming) override;`
- L44 _protected prototype_ `virtual TMulticastDelegateRegistration<void(bool)>* GetOnRenameStateChanged() const override;`
- L45 _protected prototype_ `virtual void SetDisplayNameText(const FText& InText) override;`
- L46 _protected prototype_ `virtual FText GetDescription() const override;`
- L47 _protected prototype_ `virtual int32 RemoveFromRegistry() override;`
- L48 _protected function_ `virtual ERCSignatureTreeItemType GetItemType() const override`
- L49 _protected prototype_ `virtual void GenerateChildren(TArray<TSharedPtr<FRCSignatureTreeItemBase>>& OutChildren) const override;`
- L53 _private member_ `TWeakObjectPtr<URCSignatureRegistry> RegistryWeak;`
- L55 _private member_ `FGuid SignatureId;`
- L58 _private member_ `mutable TMulticastDelegate<void(bool)> OnRenameStateChangedDelegate;` — delegate to call when entering/exiting rename mode
- L61 _private member_ `bool bRenaming = false;` — true if currently in rename mode

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Label/RCSignatureLabelColumn.h` (Private)


#### class `FRCSignatureLabelColumn`  
`class FRCSignatureLabelColumn : public IRCSignatureColumn`  
_L7-14_
- inherits: `IRCSignatureColumn`
- L10 _private prototype_ `virtual FName GetColumnId() const override;`
- L11 _private prototype_ `virtual SHeaderRow::FColumn::FArguments ConstructHeaderRowColumn() override;`
- L12 _private prototype_ `virtual TSharedRef<SWidget> ConstructRowWidget(TSharedPtr<FRCSignatureTreeItemBase> InItem, const TSharedRef<SRCSignatureTree>& InList, const TSharedRef<SRCSignatureRow>& InRow) override;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/Label/SRCSignatureLabel.h` (Private)


#### class `SRCSignatureLabel`  
`class SRCSignatureLabel : public SCompoundWidget`  
_L13-54_
- inherits: `SCompoundWidget`
- L16 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureLabel)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedRef<FRCSignatureTreeItemBase>& InItem , const TSharedRef<SRCSignatureRow>& InRow);`
- L26 _private prototype_ `TSharedRef<SWidget> CreateTextBlock(const TSharedRef<FRCSignatureTreeItemBase>& InItem, const TSharedRef<SRCSignatureRow>& InRow);`
- L29 _private prototype_ `void OnItemRenameStateChanged(bool bInRenaming);` — Called when the Item rename state changes
- L31 _private prototype_ `void SetEditMode(bool bInEditMode);`
- L33 _private prototype_ `ECheckBoxState GetItemEnabledState() const;`
- L35 _private prototype_ `void SetItemEnabledState(ECheckBoxState InState);`
- L37 _private prototype_ `FText GetSignatureDisplayName() const;`
- L39 _private prototype_ `void OnSignatureDisplayNameCommitted(const FText& InText, ETextCommit::Type InCommitType);`
- L41 _private member_ `TWeakPtr<FRCSignatureTreeItemBase> ItemWeak;`
- L43 _private member_ `TWeakPtr<SRCSignatureTree> SignatureTreeWeak;`
- L45 _private member_ `TSharedPtr<SInlineEditableTextBlock> EditableTextBlock;`
- L47 _private member_ `mutable TOptional<ECheckBoxState> CachedCheckBoxState;`
- L49 _private member_ `mutable TOptional<FText> CachedDisplayName;`
- L51 _private member_ `FDelegateHandle OnRenameStateChangedHandle;`
- L53 _private member_ `bool bEditMode = false;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/RCSignatureTreeItemSelection.h` (Private)


#### class `FRCSignatureTreeItemSelection`  
`class FRCSignatureTreeItemSelection : public TSharedFromThis<FRCSignatureTreeItemSelection>`  
_L11-61_
- inherits: `TSharedFromThis<FRCSignatureTreeItemSelection>`
- L25 _public prototype_ `FSelectionScope CreateSelectionScope();`
- L27 _public function_ `TMulticastDelegateRegistration<void()>& OnSelectionChanged() const`
- L32 _public prototype_ `void SetSelected(const TSharedRef<FRCSignatureTreeItemBase>& InItem, bool bInSelected, bool bInMultiSelection);`
- L34 _public prototype_ `bool IsSelected(const TSharedPtr<const FRCSignatureTreeItemBase>& InItem) const;`
- L36 _public prototype_ `void ClearSelection();`
- L38 _public prototype_ `void NotifySelectionChanged();`
- L40 _public function_ `TConstArrayView<TWeakPtr<FRCSignatureTreeItemBase>> GetSelectedItemsView() const`
- L45 _public prototype_ `TArray<TSharedPtr<FRCSignatureTreeItemBase>> GetSelectedItems() const;`
- L51 _public prototype_ `void RecacheSelectedItems(const TSharedRef<FRCSignatureTreeItemBase>& InRoot);` — Clears the current selection items (not paths!) and rebuilds a new selection list of all the items that match one of the selected paths. @param InRoot the root item to iterate
- L54 _private member_ `TSet<FName> SelectedPaths;`
- L56 _private member_ `TArray<TWeakPtr<FRCSignatureTreeItemBase>> CachedSelectedItems;`
- L58 _private member_ `mutable TMulticastDelegate<void()> OnSelectionChangedDelegate;`
- L60 _private member_ `bool bAllowNotifications = true;`

#### struct `FRCSignatureTreeItemSelection::FSelectionScope`  
`struct FSelectionScope`  
_L15-23_
- desc: Scope class to ensure Notify Selection Changed gets called at most once for the duration of the scope
- L17 _public prototype_ `explicit FSelectionScope(FRCSignatureTreeItemSelection* InSelection);`
- L18 _public prototype_ `~FSelectionScope();`
- L21 _private member_ `FRCSignatureTreeItemSelection* Selection;`
- L22 _private member_ `bool OldValue = false;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/SRCSignaturePanel.h` (Private)


#### class `SRCSignaturePanel`  
`class SRCSignaturePanel : public SRCLogicPanelBase, public FSelfRegisteringEditorUndoClient`  
_L12-56_
- inherits: `SRCLogicPanelBase,FSelfRegisteringEditorUndoClient`
- L15 _public function_ `SLATE_BEGIN_ARGS(SRCSignaturePanel)`
- L16 _public prototype_ `SLATE_ATTRIBUTE(bool, LiveMode) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRemoteControlPanel>& InPanel);`
- L22 _public prototype_ `URCSignatureRegistry* GetSignatureRegistry() const;` — Gets the Signature Registry from the RC Preset
- L24 _public prototype_ `void AddToSignature(const FRCExposesPropertyArgs& InPropertyArgs);`
- L27 _public prototype_ `bool IsListFocused() const;` — Whether this widget currently has focus
- L29 _public prototype_ `void EnterRenameMode();`
- L32 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() const override;`
- L33 _public prototype_ `virtual FReply RequestDeleteSelectedItem() override;`
- L34 _public prototype_ `virtual FReply RequestDeleteAllItems() override;`
- L35 _public prototype_ `virtual bool CanCopyItems() const override;`
- L36 _public prototype_ `virtual bool CanDuplicateItems() const override;`
- L37 _public prototype_ `virtual void DeleteSelectedPanelItems() override;`
- L42 _protected prototype_ `virtual void PostUndo(bool bInSuccess) override;`
- L43 _protected prototype_ `virtual void PostRedo(bool bInSuccess) override;`
- L47 _private prototype_ `void Refresh();`
- L49 _private prototype_ `FReply OnAddButtonClicked();`
- L51 _private prototype_ `FReply DeleteAllItems();`
- L53 _private member_ `TSharedPtr<SRCSignatureTree> SignatureTreeView;`
- L55 _private member_ `TSharedPtr<SRCSignatureDetails> SignatureDetails;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/SRCSignatureRow.h` (Private)


#### class `SRCSignatureRow`  
`class SRCSignatureRow : public SMultiColumnTableRow<TSharedPtr<FRCSignatureTreeItemBase>>`  
_L14-41_
- inherits: `SMultiColumnTableRow<TSharedPtr<FRCSignatureTreeItemBase>>`
- L17 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureRow)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs , const TSharedPtr<FRCSignatureTreeItemBase>& InItem , const TSharedRef<SRCSignatureTree>& InSignatureTree , const TSharedRef<STableViewBase>& InTableView);`
- L26 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;`
- L30 _private prototype_ `TOptional<EItemDropZone> OnRowCanAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<FRCSignatureTreeItemBase> InItem);`
- L32 _private prototype_ `FReply OnRowAcceptDrop(const FDragDropEvent& InDragDropEvent, EItemDropZone InDropZone, TSharedPtr<FRCSignatureTreeItemBase> InItem);`
- L34 _private prototype_ `void HandleActorDragDrop(IRCSignatureItem* InSignatureItem, const FActorDragDropOp& InActorDragDropOp);`
- L36 _private prototype_ `void HandleFolderDragDrop(IRCSignatureItem* InSignatureItem, const FFolderDragDropOp& InFolderDragDropOp);`
- L38 _private member_ `TWeakPtr<FRCSignatureTreeItemBase> ItemWeak;`
- L40 _private member_ `TWeakPtr<SRCSignatureTree> SignatureTreeWeak;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Private/UI/Signature/SRCSignatureTree.h` (Private)


#### class `SRCSignatureTree`  
`class SRCSignatureTree : public SRCLogicPanelListBase`  
_L15-80_
- inherits: `SRCLogicPanelListBase`
- L18 _public function_ `SLATE_BEGIN_ARGS(SRCSignatureTree)`
- L19 _public prototype_ `SLATE_ARGUMENT(TArray<TSharedRef<IRCSignatureColumn>>, Columns) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<SRCSignaturePanel>& InSignaturePanel, const TSharedRef<SRemoteControlPanel>& InRCPanel);`
- L24 _public prototype_ `TSharedRef<FRCSignatureTreeRootItem> GetRootItem() const;`
- L26 _public prototype_ `URCSignatureRegistry* GetSignatureRegistry() const;`
- L28 _public prototype_ `TSharedPtr<IRCSignatureColumn> FindColumn(FName InColumnName) const;`
- L30 _public prototype_ `void Refresh();`
- L32 _public prototype_ `void EnterRenameMode();`
- L34 _public prototype_ `void ProcessRenameQueue();`
- L36 _public prototype_ `TArray<TSharedPtr<FRCSignatureTreeItemBase>> GetSelectedItems() const;`
- L39 _public prototype_ `virtual URemoteControlPreset* GetPreset() override;`
- L40 _public prototype_ `virtual TArray<TSharedPtr<FRCLogicModeBase>> GetSelectedLogicItems() override;`
- L41 _public prototype_ `virtual bool IsEmpty() const override;`
- L42 _public prototype_ `virtual bool IsListFocused() const override;`
- L43 _public prototype_ `virtual int32 Num() const override;`
- L44 _public prototype_ `virtual int32 NumSelectedLogicItems() const override;`
- L45 _public prototype_ `virtual void DeleteSelectedPanelItems() override;`
- L46 _public function_ `virtual void BroadcastOnItemRemoved() override`
- L47 _public prototype_ `virtual void Reset() override;`
- L51 _private prototype_ `void ConstructColumns(TConstArrayView<TSharedRef<IRCSignatureColumn>> InColumns);`
- L53 _private prototype_ `TSharedRef<ITableRow> OnGenerateRow(TSharedPtr<FRCSignatureTreeItemBase> InItem, const TSharedRef<STableViewBase>& InTableView);`
- L55 _private prototype_ `void OnGetChildren(TSharedPtr<FRCSignatureTreeItemBase> InItem, TArray<TSharedPtr<FRCSignatureTreeItemBase>>& OutChildren) const;`
- L57 _private prototype_ `void OnItemExpansionChanged(TSharedPtr<FRCSignatureTreeItemBase> InItem, bool bInIsExpanded);`
- L59 _private prototype_ `void UpdateTreeViewSelection();`
- L61 _private prototype_ `void OnItemSelectionChanged(TSharedPtr<FRCSignatureTreeItemBase> InItem, ESelectInfo::Type InSelectionType);`
- L63 _private member_ `TSharedPtr<FRCSignatureTreeRootItem> RootItem;`
- L65 _private member_ `TMap<FName, TSharedRef<IRCSignatureColumn>> Columns;`
- L67 _private member_ `TSharedPtr<STreeView<TSharedPtr<FRCSignatureTreeItemBase>>> SignatureTreeView;`
- L69 _private member_ `TSharedPtr<SHeaderRow> HeaderRow;`
- L71 _private member_ `TWeakPtr<SRCSignaturePanel> SignaturePanelWeak;`
- L74 _private member_ `TArray<TWeakPtr<FRCSignatureTreeItemBase>> RenameQueue;` — Items that are pending to be renamed
- L77 _private member_ `TWeakPtr<FRCSignatureTreeItemBase> CurrentItemRenamingWeak;` — Current item being renamed
- L79 _private member_ `bool bSyncingSelection = false;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/IHasProtocolExtensibility.h` (Public)


#### class `IHasProtocolExtensibility`  
`class IHasProtocolExtensibility`  
_L12-40_
- desc: A simple interface provides protocol specific utilities.
- L19 _public prototype_ `virtual TSharedRef<SWidget> GetProtocolWidget(const FName ForColumnName, const FName InProtocolName = NAME_None) = 0;` — Retrieves the protocol specific widget if protocol is specified, column specific widget otherwise.
- L24 _public prototype_ `virtual const bool HasProtocolExtension() const = 0;` — Ensures the derived classes supports protocols.
- L29 _public prototype_ `virtual const bool GetProtocolBindingsNum() const = 0;` — Returns true when the derived classes has two or more protocol bindings.
- L34 _public prototype_ `virtual void OnProtocolTextChanged(const FText& InText, const FName InProtocolName) = 0;` — Callback for the editable text's OnTextChanged event.
- L39 _public prototype_ `virtual const bool SupportsProtocol(const FName& InProtocolName) const = 0;` — Determines whether the derived class supports the given protocol.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/IRemoteControlUIModule.h` (Public)


#### struct `FRCColumnSizeData`  
`struct FRCColumnSizeData`  
_L32-39_
- L34 _public member_ `TAttribute<float> LeftColumnWidth;`
- L35 _public member_ `TAttribute<float> RightColumnWidth;`
- L36 _public member_ `SSplitter::FOnSlotResized OnWidthChanged;`
- L38 _public function_ `void SetColumnWidth(float InWidth)`

#### struct `FGenerateWidgetArgs`  
`struct FGenerateWidgetArgs`  
_L41-50_
- L43 _public member_ `URemoteControlPreset* Preset = nullptr;`
- L44 _public member_ `FRCColumnSizeData ColumnSizeData;`
- L45 _public member_ `TSharedPtr<FRemoteControlEntity> Entity;`
- L46 _public member_ `TAttribute<bool> bIsInLiveMode;`
- L47 _public member_ `TWeakPtr<FRCPanelWidgetRegistry> WidgetRegistry;`
- L48 _public member_ `TSharedPtr<FUICommandList> CommandList;`
- L49 _public member_ `FText HighlightText;`

#### struct `FRCExposesPropertyArgs`  
`struct FRCExposesPropertyArgs`  
_L56-119_
- desc: Exposed property arguments The struct is wrapper struct to generate Remote Control Entity from IPropertyHandle or OwnerObject with Property Path and Property instance
- L68 _public prototype_ `FRCExposesPropertyArgs();`
- L69 _public prototype_ `FRCExposesPropertyArgs(const FOnGenerateGlobalRowExtensionArgs& InExtensionArgs);`
- L70 _public prototype_ `FRCExposesPropertyArgs(FOnGenerateGlobalRowExtensionArgs&& InExtensionArgs);`
- L71 _public prototype_ `FRCExposesPropertyArgs(TSharedPtr<IPropertyHandle>& InPropertyHandle);`
- L72 _public prototype_ `FRCExposesPropertyArgs(const TSharedPtr<IPropertyHandle>& InPropertyHandle);`
- L73 _public prototype_ `FRCExposesPropertyArgs(UObject* InOwnerObject, const FString& InPropertyPath, FProperty* InProperty);`
- L77 _public prototype_ `bool IsValid() const;` — whether extensions arguments valid
- L80 _public prototype_ `EType GetType() const;` — Get Type of the Extension Arguments
- L83 _public prototype_ `FProperty* GetProperty() const;` — Get property on the exposed arguments type
- L86 _public prototype_ `FProperty* GetPropertyChecked() const;` — Checked version of Get Property
- L105 _public member_ `TSharedPtr<IPropertyHandle> PropertyHandle;` — The detail row's property handle.
- L108 _public member_ `TWeakObjectPtr<UObject> OwnerObject;` — Owner object for the property extension
- L111 _public member_ `FString PropertyPath;` — Path of the exposed property
- L114 _public member_ `TWeakFieldPtr<FProperty> Property;` — Exposed property
- L118 _private member_ `FGuid Id;` — Unique generated ID of the struct

#### enum `FRCExposesPropertyArgs::EType`  
`enum class EType : uint8`  
_L61-66_
- desc: Type of the Extension arguments
- L63 _public enumerator_ `E_Handle`
- L64 _public enumerator_ `E_OwnerObject`
- L65 _public enumerator_ `E_None`

#### struct `FRCControllerExtensionWidgetsInfo`  
`struct FRCControllerExtensionWidgetsInfo`  
_L136-161_
- desc: A struct used for controllers list items columns customization
- L138 _public function_ `FRCControllerExtensionWidgetsInfo(URCVirtualPropertyBase* InController) : Controller(InController)`
- L144 _public function_ `bool AddColumnWidget(const FName& InColumnName, const TSharedRef<SWidget>& InWidget)` — Add a new widget, and associate it to the specified custom column
- L157 _public member_ `URCVirtualPropertyBase* Controller;` — The controller being customized
- L160 _public member_ `TMap<FName, TSharedRef<SWidget>> CustomWidgetsMap;` — A map associating each column with a widget

#### class `IRemoteControlUIModule`  
`class IRemoteControlUIModule : public IModuleInterface`  
_L183-348_
- inherits: `IModuleInterface`
- desc: A Remote Control module that allows exposing objects and properties from the editor.
- L192 _public function_ `static IRemoteControlUIModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L199 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoteControlPresetOpened, URemoteControlPreset* );` — Delegate called when a Remote Control Preset panel is created/opened for the specified Remote Control Preset
- L200 _public prototype_ `virtual FOnRemoteControlPresetOpened& OnRemoteControlPresetOpened() = 0;`
- L203 _public prototype_ `virtual FOnGenerateControllerExtensionsWidgets& OnGenerateControllerExtensionsWidgets() = 0;` — Delegate called when a Remote Control Preset panel is created/opened for the specified Remote Control Preset
- L206 _public prototype_ `virtual FOnAddControllerExtensionColumn& OnAddControllerExtensionColumn() = 0;` — Delegate called when a Remote Control Preset panel is created/opened for the specified Remote Control Preset
- L212 _public prototype_ `virtual FOnGenerateExtensions& GetExtensionGenerators() = 0;` — Get the toolbar extension generators. Usage: Bind a handler that adds a widget to the out array parameter.
- L221 _public prototype_ `virtual FDelegateHandle AddPropertyFilter(FOnDisplayExposeIcon OnDisplayExposeIcon) = 0;` — Add a property filter that indicates if the property handle should be displayed or not. When queried, returning true will allow the expose icon to be displayed in the details panel, false will hide it. @Note This filter will be queried after the RemoteControlModule's own filters. @param OnDisplayExposeIcon The delegate called to determine whether to display the icon or not. @return A handle to the delegate, used to unregister the delegate with the module.
- L226 _public prototype_ `virtual void RemovePropertyFilter(const FDelegateHandle& FilterDelegateHandle) = 0;` — Remove a property filter using its id.
- L233 _public prototype_ `virtual void RegisterMetadataCustomization(FName MetadataKey, FOnCustomizeMetadataEntry OnCustomizeCallback) = 0;` — Register a delegate to customize how an entry is displayed in the entity details panel. @param MetadataKey The metadata map entry to customize. @param OnCustomizeCallback The handler called to handle customization for the entry's details panel row.
- L239 _public prototype_ `virtual void UnregisterMetadataCustomization(FName MetadataKey) = 0;` — Unregister the delegate used to customize how an entry is displayed in the entity details panel. @param MetadataKey The metadata map entry to unregister the customization for.
- L244 _public prototype_ `virtual URemoteControlPreset* GetActivePreset() const = 0;` — Get the preset currently being edited in the editor.
- L249 _public prototype_ `virtual uint32 GetRemoteControlAssetCategory() const = 0;` — Retrieves the advanced asset category type registered by Remote Control Module.
- L255 _public prototype_ `virtual void RegisterSignatureCustomization(const TSharedPtr<IRCSignatureCustomization>& InCustomization) = 0;` — Register the given signature customization to extend the Signature Panel capabilities like Drag/Drop handling @param InCustomization	The signature customization instance to register
- L261 _public prototype_ `virtual void UnregisterSignatureCustomization(const TSharedPtr<IRCSignatureCustomization>& InCustomization) = 0;` — Unregisters the given signature customization @param InCustomization	The signature customization instance to unregister
- L267 _public prototype_ `virtual void RegisterExposedEntitiesListSettingsForProtocol(const TSharedRef<IRCPanelExposedEntitiesListSettingsForProtocol>& InSettings) = 0;` — Registers the given settings for an exposed entities list. @param InSettings		The exposed entities list settings instance to register.
- L273 _public prototype_ `virtual void UnregisterExposedEntitiesListSettingsForProtocol(const TSharedRef<IRCPanelExposedEntitiesListSettingsForProtocol>& InSettings) = 0;` — Unregisters the given settings for an exposed entities list. @param InSettings		The exposed entities list settings instance to unregister.
- L279 _public prototype_ `virtual void RegisterExposedEntitiesPanelExtender(const TSharedRef<IRCExposedEntitiesPanelExtender>& InExtender) = 0;` — Registers the given customization for an exposed entities panel. @param InExtender		The exposed entities panel extender instance to register.
- L285 _public prototype_ `virtual void UnregisterExposedEntitiesPanelExtender(const TSharedRef<IRCExposedEntitiesPanelExtender>& InExtender) = 0;` — Unregisters the given exposed entities panel customization. @param InExtender		The exposed entities panel extender instance to unregister.
- L291 _public prototype_ `virtual void RegisterExposedEntitiesGroupWidgetFactory(const TSharedRef<IRCPanelExposedEntitiesGroupWidgetFactory>& InFactory) = 0;` — Registers a widget factory a column in an exposed entities group row. @param InFactory			The widget factory to register.
- L297 _public prototype_ `virtual void UnregisterExposedEntitiesGroupWidgetFactory(const TSharedRef<IRCPanelExposedEntitiesGroupWidgetFactory>& InFactory) = 0;` — Unregisters the given widget factory. @param InFactory			The factory to unregister.
- L303 _public prototype_ `virtual void RegisterExposedEntityWidgetFactory(const TSharedRef<IRCPanelExposedEntityWidgetFactory>& InFactory) = 0;` — Registers a widget factory a column in an exposed entity row. @param InFactory			The widget factory to register.
- L309 _public prototype_ `virtual void UnregisterExposedEntityWidgetFactory(const TSharedRef<IRCPanelExposedEntityWidgetFactory>& InFactory) = 0;` — Unregisters the given customization for a exposed entity. @param InFactory			The factory to unregister.
- L314 _public prototype_ `virtual void RegisterWidgetFactoryForType(UScriptStruct* RemoteControlEntityType, const FOnGenerateRCWidget& OnGenerateRCWidgetDelegate) = 0;` — Register a widget factory to handle creating a widget in the control panel.
- L319 _public prototype_ `virtual void UnregisterWidgetFactoryForType(UScriptStruct* RemoteControlEntityType) = 0;` — Unregister a previously registered widget factory.
- L324 _public prototype_ `virtual void RegisterPropertyResolver(FName InResolverId, const FRCPropertyResolver& InResolver) = 0;` — Registers a property source resolution callback.
- L329 _public prototype_ `virtual void UnregisterPropertyResolver(FName InResolverId) = 0;` — Unregisters a property source resolution callback.
- L332 _public member_ `static const FString SettingsIniSection;` — The section of EditorPerProjectUserSettings in which to save filter settings
- L337 _public prototype_ `virtual void HighlightPropertyInDetailsPanel(const FPropertyPath& Path) const = 0;` — If a details panel is open, highlight a property specified by the path in it.
- L342 _public prototype_ `virtual void SelectObjects(const TArray<UObject*>& Objects) const = 0;` — Set the list of selected objects.
- L347 _public prototype_ `virtual TSharedPtr<SWidget> CreateCustomControllerWidget(URCVirtualPropertyBase* InController, TSharedPtr<IPropertyHandle> InOriginalPropertyHandle) const = 0;` — Tries to retrieve a Custom Controller Widget for the specified Controller

#### Free symbols / members of external scopes

- L88 _function_ `friend inline bool operator==(const FRCExposesPropertyArgs& LHS, const FRCExposesPropertyArgs& RHS)`
- L93 _function_ `friend inline bool operator!=(const FRCExposesPropertyArgs& LHS, const FRCExposesPropertyArgs& RHS)`
- L98 _function_ `friend inline uint32 GetTypeHash(const FRCExposesPropertyArgs& InArgs)`
- L121 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SRCPanelTreeNode>, FOnGenerateRCWidget, const FGenerateWidgetArgs& );`
- L121 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<SRCPanelTreeNode>, FOnGenerateRCWidget, const FGenerateWidgetArgs& );`
- L123 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateExtensions, TArray<TSharedRef<class SWidget>>& );`
- L123 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateExtensions, TArray<TSharedRef<class SWidget>>& );`
- L128 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDisplayExposeIcon, const FRCExposesPropertyArgs& );` — Filter queried in order to determine if a property should be displayed.
- L128 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FOnDisplayExposeIcon, const FRCExposesPropertyArgs& );` — Filter queried in order to determine if a property should be displayed.
- L133 _delegate_ `DECLARE_DELEGATE_FourParams(FOnCustomizeMetadataEntry, URemoteControlPreset* , const FGuid& , IDetailLayoutBuilder& , IDetailCategoryBuilder& );` — Callback called to customize the display of a metadata entry for entities.
- L133 _prototype_ `DECLARE_DELEGATE_FourParams(FOnCustomizeMetadataEntry, URemoteControlPreset* , const FGuid& , IDetailLayoutBuilder& , IDetailCategoryBuilder& );` — Callback called to customize the display of a metadata entry for entities.
- L166 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateControllerExtensionsWidgets, FRCControllerExtensionWidgetsInfo& );` — Callback called to customize the extensible widget for controllers in controllers list
- L166 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenerateControllerExtensionsWidgets, FRCControllerExtensionWidgetsInfo& );` — Callback called to customize the extensible widget for controllers in controllers list
- L171 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddControllerExtensionColumn, TArray<FName>& );` — Called when setting up / resetting the Controller panel list. Register to add custom column.
- L171 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAddControllerExtensionColumn, TArray<FName>& );` — Called when setting up / resetting the Controller panel list. Register to add custom column.
- L178 _delegate_ `DECLARE_DELEGATE_RetVal_ThreeParams(bool, FRCPropertyResolver, const TSharedRef<FRemoteControlProperty>& , TArray<UObject*>& , TSharedPtr<FPropertyPath>& ) class IRemoteControlUIModule : public IModuleInterface { public: static IRemoteControlUIModule& Get() { static const FName ModuleName = "RemoteControlUI"; return FModuleManager::LoadModuleChecked<IRemoteControlUIModule>(ModuleName); } DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoteControlPresetOpened, URemoteControlPreset* ); virtual FOnRemoteControlPresetOpened& OnRemoteControlPresetOpened() = 0; virtual FOnGenerateControllerExtensionsWidgets& OnGenerateControllerExtensionsWidgets() = 0; virtual FOnAddControllerExtensionColumn& OnAddControllerExtensionColumn() = 0; virtual FOnGenerateExtensions& GetExtensionGenerators() = 0; /** * Add a property filter that indicates if the property handle should be displayed or not. * When queried, returning true will allow the expose icon to be displayed in the details panel, false will hide it. * @Note This filter will be queried after the RemoteControlModule's own filters.` — Callback for custom resolution of exposed property sources. Returns true if the property is resolved / dealt with. When successfully resolving, bound objects can be replaced.
- L199 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoteControlPresetOpened, URemoteControlPreset* );` — Delegate called when a Remote Control Preset panel is created/opened for the specified Remote Control Preset

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/Filters/CustomRCFilterData.h` (Public)


#### class `FCustomTypeFilterData`  
`class FCustomTypeFilterData`  
_L18-152_
- desc: A custom view model to represent each type of filters we have.
- L22 _public function_ `FCustomTypeFilterData(EEntityTypeCategories::Type InEntityTypeCategory, FFieldClass* InEntityType, FText InFilterDisplayName, const FName& InCustomTypeName = NAME_None) : Class(nullptr) , EntityType(InEntityType) , EntityTypeCategory(InEntityTypeCategory) , FilterDisplayName(InFilterDisplayName) , Color(FLinearColor::White) , CustomTypeName(InCustomTypeName) , AssetTypeActions(nullptr)`
- L33 _public function_ `FCustomTypeFilterData(EEntityTypeCategories::Type InEntityTypeCategory, FFieldClass* InEntityType, FText InEntityTypeDisplayName, TSharedPtr<FFilterCategory> InCategory, const FName& InCustomTypeName = NAME_None) : Class(nullptr) , EntityType(InEntityType) , EntityTypeCategory(InEntityTypeCategory) , FilterDisplayName(InEntityTypeDisplayName) , Color(FLinearColor::White) , CustomTypeName(InCustomTypeName) , AssetTypeActions(nullptr)`
- L46 _public function_ `FCustomTypeFilterData(TWeakPtr<IAssetTypeActions> InAssetTypeAction) : Class(nullptr) , EntityType(FObjectProperty::StaticClass()) , EntityTypeCategory(EEntityTypeCategories::Assets) , Color(FLinearColor::White) , CustomTypeName(NAME_None) , AssetTypeActions(InAssetTypeAction)` — You can provide an IAssetTypeActions for your type to get all the information from that
- L57 _public function_ `FCustomTypeFilterData(UClass* InClass, TSharedPtr<FFilterCategory> InCategory, FLinearColor InColor) : Class(InClass) , EntityType(FObjectProperty::StaticClass()) , EntityTypeCategory(EEntityTypeCategories::Assets) , Color(InColor) , CustomTypeName(NAME_None) , AssetTypeActions(nullptr)` — Or you can provide a UClass, a Category and a Color to identify the filter
- L69 _public prototype_ `void AddCategory(TSharedPtr<FFilterCategory> InCategory);` — Unlike normal filters, Type Filters are allowed to belong to multiple categories
- L72 _public prototype_ `void BuildBackendFilter(FRCFilter& OutFilter);` — Add this filter to the input Backend Filter
- L75 _public prototype_ `TSharedPtr<IAssetTypeActions> GetAssetTypeActions() const;` — Get the AssetTypeActions associated with this filter if they exist
- L78 _public prototype_ `TArray<TSharedPtr<FFilterCategory>> GetCategories() const;` — Get the Catgories this filter belongs to
- L81 _public prototype_ `UClass* GetClass() const;` — Get the UClass associated with this filter
- L84 _public prototype_ `FFieldClass* GetEntityType() const;` — Get the Property Type associated with this filter
- L87 _public prototype_ `EEntityTypeCategories::Type GetEntityTypeCategory() const;` — Get the Entity Type Catgories this filter belongs to
- L90 _public prototype_ `FLinearColor GetColor() const;` — Get the color of this filter
- L93 _public prototype_ `FText GetName() const;` — Get the logical name of this filter class
- L96 _public prototype_ `FString GetFilterName() const;` — Get the display name of this filter class
- L99 _public prototype_ `FSlateIcon GetSlateIcon() const;` — Retrieves the appropriate icon for the filter.
- L102 _public prototype_ `void ResetBackendFilter(FRCFilter& OutFilter);` — Remove this filter from the input Backend Filter
- L107 _protected prototype_ `FText GetProperEntityDisplayName() const;` — Returns proper name of the entity type to be displayed.
- L110 _protected prototype_ `FSlateIcon GetProperEntityIcon() const;` — Returns proper icon of the entity type to be displayed.
- L115 _private member_ `UClass* Class;` — The Class the filter is associated with (if it does not have an AssetTypeAction)
- L118 _private member_ `FFieldClass* EntityType;` — The Entity Type the filter is associated with.
- L121 _private member_ `EEntityTypeCategories::Type EntityTypeCategory;` — The Entity Type the filter is associated with.
- L124 _private member_ `FText FilterDisplayName;` — The entity type display name
- L127 _private member_ `TArray<TSharedPtr<FFilterCategory>> Categories;` — The Categories the filter will show up under
- L130 _private member_ `FLinearColor Color;` — The Color of the filter.
- L133 _private member_ `FName CustomTypeName;` — If property name could not be deducted from entity type then this will be used instead.
- L136 _private member_ `TWeakPtr<IAssetTypeActions> AssetTypeActions;` — An optional AssetTypeAction to get information about the filter class
- L139 _private member_ `static FSlateIcon EmptyIcon;` — Empty Slate Icon.
- L142 _private member_ `static FSlateIcon EntityIcon;` — Entity Slate Icon.
- L145 _private member_ `static FSlateIcon ArrayIcon;` — Array Slate Icon.
- L148 _private member_ `static FSlateIcon MapIcon;` — Map Slate Icon.
- L151 _private member_ `static FSlateIcon SetIcon;` — Set Slate Icon.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/Filters/RCFilter.h` (Public)


#### enum `EEntityTypeCategories::Type`  
`enum Type`  
_L24-45_
- L26 _public enumerator_ `None = 0`
- L28 _public enumerator_ `Core = 1 << 0`
- L30 _public enumerator_ `Strings = 1 << 1`
- L32 _public enumerator_ `Structs = 1 << 2`
- L34 _public enumerator_ `Containers = 1 << 3`
- L36 _public enumerator_ `Objects = 1 << 4`
- L38 _public enumerator_ `References = 1 << 5`
- L40 _public enumerator_ `UserDefined = 1 << 6`
- L42 _public enumerator_ `Assets = 1 << 7`
- L44 _public enumerator_ `Primary = 1 << 8`

#### class `FRCFilter`  
`class FRCFilter`  
_L51-89_
- desc: A data model to represent combined backend filter.
- L56 _public prototype_ `void AddTypeFilter(FFieldClass* InEntityTypeFilter);` — Adds an entity type to the filters list.
- L59 _public prototype_ `void AddTypeFilter(const FName InCustomTypeFilter);` — Adds a custom type to the filters list.
- L62 _public prototype_ `void AddTypeFilter(UClass* InAssetTypeFilter);` — Adds an asset type to the filters list.
- L65 _public prototype_ `bool DoesPassFilters(FEntityFilterType InEntityItem);` — Returns true if the given item passes atleast one filter.
- L68 _public prototype_ `bool HasAnyActiveFilters();` — Returns true if atleast one of the type filters are populated.
- L71 _public prototype_ `void RemoveTypeFilter(FFieldClass* InEntityTypeFilter);` — Removes an entity type from the filters list.
- L74 _public prototype_ `void RemoveTypeFilter(const FName& InCustomTypeFilter);` — Removes a custom type from the filters list.
- L77 _public prototype_ `void RemoveTypeFilter(UClass* InAssetTypeFilter);` — Removes an asset type from the filters list.
- L82 _private member_ `TSet<FFieldClass*> EntityTypeFilters;` — The list of active entity types.
- L85 _private member_ `TSet<UClass*> AssetTypeFilters;` — The list of active asset types.
- L88 _private member_ `TSet<FName> CustomTypeFilters;` — The list of active custom types.

#### Free symbols / members of external scopes

- L10 _typedef_ `using FEntityFilterType = TSharedRef<const SRCPanelTreeNode>;`
- L12 _namespace_ `namespace RemoteControlTypes`
- L14 _variable_ `static const FName NAME_RCActors = "Ex` (scope `RemoteControlTypes`)
- L16 _variable_ `static const FName NAME_RCFunctions = "Ex` (scope `RemoteControlTypes`)
- L22 _namespace_ `namespace EEntityTypeCategories`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/IRCExposedEntitiesPanelExtender.h` (Public)


#### class `IRCExposedEntitiesPanelExtender`  
`class IRCExposedEntitiesPanelExtender`  
_L13-23_
- desc: An externder for the exposed entities panel. Draws a widget above the exposed entities list.
- L22 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(URemoteControlPreset* Preset, const FArgs& Args) = 0;` — Creates a widget above the exposed entities list.

#### struct `IRCExposedEntitiesPanelExtender::FArgs`  
`struct FArgs`  
_L16-19_
- L18 _public member_ `TAttribute<FName> ActiveProtocolAttribute;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/IRCPanelExposedEntitiesGroupWidgetFactory.h` (Public)


#### struct `FRCPanelExposedEntitiesGroupWidgetFactoryArgs`  
`struct FRCPanelExposedEntitiesGroupWidgetFactoryArgs`  
_L15-29_
- desc: Arguments provided by the exposed entities group widget factory
- L17 _public function_ `FRCPanelExposedEntitiesGroupWidgetFactoryArgs( const TWeakObjectPtr<URemoteControlPreset> InWeakPreset, const TArray<TSharedRef<FRemoteControlProperty>> InChildProperties) : WeakPreset(InWeakPreset) , ChildProperties(InChildProperties)`
- L25 _public member_ `TWeakObjectPtr<URemoteControlPreset> WeakPreset;` — The preset for which this exposed entities group widget is painted
- L28 _public member_ `TArray<TSharedRef<FRemoteControlProperty>> ChildProperties;` — The child properties that reside in this exposed entities group.

#### class `IRCPanelExposedEntitiesGroupWidgetFactory`  
`class IRCPanelExposedEntitiesGroupWidgetFactory`  
_L32-43_
- desc: Factory for a widget in a column in an exposed entities group row
- L36 _public prototype_ `virtual TSharedRef<SWidget> MakeWidget(const FRCPanelExposedEntitiesGroupWidgetFactoryArgs& Args) = 0;` — Creates a widget in a column in an exposed entities group row.
- L39 _public prototype_ `virtual FName GetColumnName() const = 0;` — Returns the column in which the widget should be painted
- L42 _public function_ `virtual FName GetProtocolName() const` — Returns the protocol name, or name none if the widget factory is not protocol specific.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/IRCPanelExposedEntitiesListSettingsForProtocol.h` (Public)


#### class `IRCPanelExposedEntitiesListSettingsForProtocol`  
`class IRCPanelExposedEntitiesListSettingsForProtocol`  
_L11-27_
- desc: Interface to store and recall settings for an entity list for a specific protocol
- L15 _public prototype_ `virtual FName GetProtocolName() const = 0;` — Returns the protocol name
- L18 _public prototype_ `virtual FRCPanelExposedEntitiesListSettingsData GetListSettings(URemoteControlPreset* Preset) const = 0;` — Returns the list settings that should be applied to the exposed entities list
- L26 _public prototype_ `virtual void OnSettingsChanged(URemoteControlPreset* Preset, const FRCPanelExposedEntitiesListSettingsData& ListSettings) = 0;` — Called when the corresponding entity list changed. Useful to store the current settings. @param Preset				The preset for which the list is painted. @param ListSettings			The current list settings.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/IRCPanelExposedEntityWidgetFactory.h` (Public)


#### struct `FRCPanelExposedPropertyWidgetArgs`  
`struct FRCPanelExposedPropertyWidgetArgs`  
_L15-29_
- desc: Arguments to construct an exposed property widget
- L17 _public function_ `FRCPanelExposedPropertyWidgetArgs( const TWeakObjectPtr<URemoteControlPreset> InWeakPreset, const TSharedRef<FRemoteControlProperty> InProperty) : WeakPreset(InWeakPreset) , Property(InProperty)`
- L25 _public member_ `const TWeakObjectPtr<URemoteControlPreset> WeakPreset;` — The preset for which this exposed entities group widget is painted
- L28 _public member_ `const TSharedRef<FRemoteControlProperty> Property;` — The property of shown in this widget.

#### class `IRCPanelExposedEntityWidgetFactory`  
`class IRCPanelExposedEntityWidgetFactory`  
_L32-43_
- desc: Factory for a widget in a column of an exposed entity row
- L36 _public prototype_ `virtual TSharedRef<SWidget> MakePropertyWidget(const FRCPanelExposedPropertyWidgetArgs& Args) = 0;` — Creates a widget for a property in a column of an exposed entity row
- L39 _public prototype_ `virtual FName GetColumnName() const = 0;` — Returns the column in which the widget should be drawn
- L42 _public function_ `virtual FName GetProtocolName() const` — Returns the protocol name, or name none if the widget factory is not protocol specific.

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/RCFieldGroupOrder.h` (Public)


#### enum `ERCFieldGroupOrder`  
`enum class ERCFieldGroupOrder : uint8`  
_L9-14_
- reflection: `UENUM()`
- desc: Order of remote control field groups
- L11 _public enumerator_ `None`
- L12 _public enumerator_ `Ascending`
- L13 _public enumerator_ `Descending`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/RCFieldGroupType.h` (Public)


#### enum `ERCFieldGroupType`  
`enum class ERCFieldGroupType : uint8`  
_L9-19_
- reflection: `UENUM()`
- desc: Types of remote control field groups
- L12 _public enumerator_ `None` — No Grouping. Will be shown as a flat list
- L15 _public enumerator_ `PropertyId` — Fields with same property id are grouped together
- L18 _public enumerator_ `Owner` — Fields with same owner are grouped together

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/RCPanelExposedEntitiesListSettingsData.h` (Public)


#### struct `FRCPanelExposedEntitiesListSettingsData`  
`struct FRCPanelExposedEntitiesListSettingsData`  
_L12-23_
- reflection: `USTRUCT()`
- desc: Data for exposed entities list settings
- L18 _public member_ `ERCFieldGroupType FieldGroupType = ERCFieldGroupType::None;` — `UPROPERTY()` — The field group type for the entity list.
- L22 _public member_ `ERCFieldGroupOrder FieldGroupOrder = ERCFieldGroupOrder::Ascending;` — `UPROPERTY()` — Whether the field groups are expanded

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/Signature/IRCSignatureCustomization.h` (Public)


#### class `IRCSignatureCustomization`  
`class IRCSignatureCustomization`  
_L10-16_
- desc: Customization Interface to extend the capabilities of RC Signature UI
- L13 _public prototype_ `virtual bool CanAcceptDrop(const FDragDropEvent& InDragDropEvent, IRCSignatureItem* InSignatureItem) const = 0;`
- L15 _public prototype_ `virtual FReply AcceptDrop(const FDragDropEvent& InDragDropEvent, IRCSignatureItem* InSignatureItem) const = 0;`

### `Plugins/VirtualProduction/RemoteControl/Source/RemoteControlUI/Public/UI/Signature/IRCSignatureItem.h` (Public)


#### class `IRCSignatureItem`  
`class IRCSignatureItem`  
_L11-15_
- desc: Interface for external implementations to interact with the Signature View Model
- L14 _public prototype_ `virtual void ApplySignature(TConstArrayView<TWeakObjectPtr<UObject>> InObjects) = 0;`
