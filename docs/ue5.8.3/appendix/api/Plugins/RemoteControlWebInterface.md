# Plugins / RemoteControlWebInterface

- module root: `Plugins/VirtualProduction/RemoteControlWebInterface/Source/RemoteControlWebInterface`
- headers: 5; symbols: 61
- symbol kinds: class=5, delegate=1, enum=1, enumerator=4, function=1, member=14, prototype=35
- PrivateDependencyModuleNames: DeveloperSettings, EditorStyle, EditorWidgets, PropertyEditor, RemoteControl, RemoteControlCommon, RemoteControlLogic, RemoteControlUI, Serialization, Settings, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Projects, RemoteControl, Slate, SlateCore, Sockets, WebRemoteControl, WebSocketNetworking

### `Plugins/VirtualProduction/RemoteControlWebInterface/Source/RemoteControlWebInterface/Private/RCWebInterfaceCustomizations.h` (Private)


#### class `FRCWebInterfaceCustomizations`  
`class FRCWebInterfaceCustomizations`  
_L23-78_
- desc: Handles registering customizations acting on the remote control panel.
- L26 _public prototype_ `FRCWebInterfaceCustomizations(TSharedPtr<FRemoteControlWebInterfaceProcess> Process);`
- L27 _public prototype_ `~FRCWebInterfaceCustomizations();`
- L31 _private prototype_ `void RegisterPanelExtension();`
- L32 _private prototype_ `void UnregisterPanelExtension();`
- L35 _private prototype_ `void GeneratePanelExtensions(TArray<TSharedRef<SWidget>>& OutExtensions);` — Handles adding the widget extension to the remote control panel.
- L38 _private prototype_ `class FReply OpenWebApp() const;` — Handles launching the web app through a web browser.
- L41 _private prototype_ `void RegisterExposedEntityCallback() const;`
- L42 _private prototype_ `void UnregisterExposedEntityCallback() const;`
- L45 _private prototype_ `void RegisterPanelMetadataCustomization();`
- L46 _private prototype_ `void UnregisterPanelMetadataCustomization();`
- L49 _private prototype_ `void CustomizeWidgetTypeMetadata(URemoteControlPreset* Preset, const FGuid& DisplayedEntityId, IDetailLayoutBuilder& LayoutBuilder, IDetailCategoryBuilder& CategoryBuilder);` — Handles customizing the widget type metadata entry.
- L52 _private prototype_ `void CustomizeWidgetDescriptionMetadata(URemoteControlPreset* Preset, const FGuid& DisplayedEntityId, IDetailLayoutBuilder& LayoutBuilder, IDetailCategoryBuilder& CategoryBuilder);` — Handles customizing the widget description metadata entry.
- L55 _private prototype_ `void OnWidgetSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type) const;` — Handles selecting a different widget representation for an entity.
- L58 _private prototype_ `void OnWidgetDescriptionChanged(const FText& InDescription, ETextCommit::Type) const;` — Handles widget description change.
- L61 _private prototype_ `FString OnInitializeWidgetMetadata(URemoteControlPreset* Preset, const FGuid& EntityId) const;` — Handles initializing the widget metadata for entities.
- L65 _private member_ `TSharedPtr<class FRemoteControlWebInterfaceProcess> WebApp;` — The actual process that runs the middleman server.
- L68 _private member_ `TArray<TSharedPtr<FString>> WidgetTypes;` — List of widgets displayed in the metadata widget combo box.
- L71 _private member_ `TWeakPtr<FRemoteControlEntity> EntityBeingDisplayed;` — Holds the entity currently being displayed in the RC Panel.
- L74 _private member_ `TSharedPtr<SSearchableComboBox> SearchableBox;` — Holds the searchable box used for picking a widget for a given entity.
- L77 _private member_ `TSharedPtr<SEditableTextBox> DescriptionBox;` — Holds the textbox used for specifying the description for a given entity.

#### class `FRCWebInterfaceCustomizations`  
`class FRCWebInterfaceCustomizations`  
_L82-84_
- L26 _public prototype_ `FRCWebInterfaceCustomizations(TSharedPtr<FRemoteControlWebInterfaceProcess> Process);`
- L27 _public prototype_ `~FRCWebInterfaceCustomizations();`
- L31 _private prototype_ `void RegisterPanelExtension();`
- L32 _private prototype_ `void UnregisterPanelExtension();`
- L35 _private prototype_ `void GeneratePanelExtensions(TArray<TSharedRef<SWidget>>& OutExtensions);` — Handles adding the widget extension to the remote control panel.
- L38 _private prototype_ `class FReply OpenWebApp() const;` — Handles launching the web app through a web browser.
- L41 _private prototype_ `void RegisterExposedEntityCallback() const;`
- L42 _private prototype_ `void UnregisterExposedEntityCallback() const;`
- L45 _private prototype_ `void RegisterPanelMetadataCustomization();`
- L46 _private prototype_ `void UnregisterPanelMetadataCustomization();`
- L49 _private prototype_ `void CustomizeWidgetTypeMetadata(URemoteControlPreset* Preset, const FGuid& DisplayedEntityId, IDetailLayoutBuilder& LayoutBuilder, IDetailCategoryBuilder& CategoryBuilder);` — Handles customizing the widget type metadata entry.
- L52 _private prototype_ `void CustomizeWidgetDescriptionMetadata(URemoteControlPreset* Preset, const FGuid& DisplayedEntityId, IDetailLayoutBuilder& LayoutBuilder, IDetailCategoryBuilder& CategoryBuilder);` — Handles customizing the widget description metadata entry.
- L55 _private prototype_ `void OnWidgetSelectionChanged(TSharedPtr<FString> InItem, ESelectInfo::Type) const;` — Handles selecting a different widget representation for an entity.
- L58 _private prototype_ `void OnWidgetDescriptionChanged(const FText& InDescription, ETextCommit::Type) const;` — Handles widget description change.
- L61 _private prototype_ `FString OnInitializeWidgetMetadata(URemoteControlPreset* Preset, const FGuid& EntityId) const;` — Handles initializing the widget metadata for entities.
- L65 _private member_ `TSharedPtr<class FRemoteControlWebInterfaceProcess> WebApp;` — The actual process that runs the middleman server.
- L68 _private member_ `TArray<TSharedPtr<FString>> WidgetTypes;` — List of widgets displayed in the metadata widget combo box.
- L71 _private member_ `TWeakPtr<FRemoteControlEntity> EntityBeingDisplayed;` — Holds the entity currently being displayed in the RC Panel.
- L74 _private member_ `TSharedPtr<SSearchableComboBox> SearchableBox;` — Holds the searchable box used for picking a widget for a given entity.
- L77 _private member_ `TSharedPtr<SEditableTextBox> DescriptionBox;` — Holds the textbox used for specifying the description for a given entity.

### `Plugins/VirtualProduction/RemoteControlWebInterface/Source/RemoteControlWebInterface/Private/RCWebInterfaceLibrary.h` (Private)


#### class `URCWebInterfaceBlueprintLibrary`  
`class URCWebInterfaceBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L9-56_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L19 _public prototype_ `static TMap<FString, AActor*> FindMatchingActorsToRebind(const FString& PresetId, const TArray<FString>& PropertyIds);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlWebInterface")` — Get a list of compatible actors to rebind the remote control preset properties returned value is a map, key is the actor label
- L26 _public prototype_ `static FString GetOwnerActorLabel(const FString& PresetId, const TArray<FString>& PropertyIds);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlWebInterface")` — Get the label of the owner actor of the remote control preset properties If the properties has different owners, an empty string will be returned
- L32 _public prototype_ `static void RebindProperties(const FString& PresetId, const TArray<FString>& PropertyIds, AActor* NewOwner);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlWebInterface")` — Rebind the remote control preset properties to a new owner
- L38 _public prototype_ `static TMap<AActor*, FString> FindAllActorsOfClass(UClass* Class);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlWebInterface")` — Shortcut function to find all actors of a class
- L44 _public prototype_ `static AActor* SpawnActor(UClass* Class);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlWebInterface")` — Shortcut function to spawn an actor of a class
- L50 _public prototype_ `static TMap<AActor*, FString> GetValuesOfActorsByClass(UClass* Class);` — `UFUNCTION(BlueprintCallable, Category = "RemoteControlWebInterface")` — Gets all properties values (as a json) of all actors of type Class
- L53 _private prototype_ `static class URemoteControlPreset* GetPreset(const FString& PresetId);`
- L55 _private prototype_ `static FString GetActorNameOrLabel(const AActor* Actor);`

### `Plugins/VirtualProduction/RemoteControlWebInterface/Source/RemoteControlWebInterface/Private/RCWebInterfacePrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteControlWebInterface, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRemoteControlWebInterface, Log, All);`

### `Plugins/VirtualProduction/RemoteControlWebInterface/Source/RemoteControlWebInterface/Public/RCWebInterface.h` (Public)


#### class `FRemoteControlWebInterfaceModule`  
`class FRemoteControlWebInterfaceModule : public IModuleInterface , public FSelfRegisteringExec`  
_L13-54_
- inherits: `IModuleInterface,FSelfRegisteringExec`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _public prototype_ `virtual bool Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;`
- L32 _public function_ `static FRemoteControlWebInterfaceModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L40 _private prototype_ `void OnSettingsModified(UObject* Settings, struct FPropertyChangedEvent& PropertyChangedEvent);` — Handle Web Interface settings modifications.
- L44 _private member_ `TSharedPtr<FRemoteControlWebInterfaceProcess> WebApp;` — The actual process that runs the middleman server.
- L47 _private member_ `FDelegateHandle WebSocketServerStartedDelegate;` — WebSocketServer Start Delegate
- L50 _private member_ `TPimplPtr<FRCWebInterfaceCustomizations> Customizations;` — Customizations/Additions to add to the RC Panel.
- L53 _private member_ `bool bRCWebInterfaceDisable;` — Prevents the WebApp from starting. Can be set from command line with -RCWebInterfaceDisable

### `Plugins/VirtualProduction/RemoteControlWebInterface/Source/RemoteControlWebInterface/Public/RCWebInterfaceProcess.h` (Public)


#### class `FRemoteControlWebInterfaceProcess`  
`class FRemoteControlWebInterfaceProcess : private FRunnable`  
_L12-58_
- inherits: `FRunnable`
- L24 _public prototype_ `FRemoteControlWebInterfaceProcess();`
- L26 _public prototype_ `virtual ~FRemoteControlWebInterfaceProcess();`
- L29 _public prototype_ `void Start();` — Starts the webapp external process, first launch will take some time as it needs to compile the webapp
- L32 _public prototype_ `void Shutdown();` — Shutdown the webapp external process
- L35 _public prototype_ `EStatus GetStatus() const;` — Get the webapp's status.
- L38 _public prototype_ `void SetExternalLoggerEnabled(bool bEnableExternalLog);` — Enable / disable external logger
- L41 _protected prototype_ `virtual uint32 Run() override;`
- L45 _private member_ `FString Root;` — Plugin root folder
- L48 _private member_ `FProcHandle Process;` — WebApp Node.js process handle
- L51 _private member_ `FRunnableThread* Thread = nullptr;` — Thread for WebApp node.js process (read stdout and forward to log)
- L54 _private member_ `TUniquePtr<FAsyncTaskNotification> TaskNotification;` — Progress notification
- L57 _private member_ `std::atomic<EStatus> Status;` — The current status of the web app.

#### enum `FRemoteControlWebInterfaceProcess::EStatus`  
`enum class EStatus : uint8`  
_L15-21_
- L17 _public enumerator_ `Stopped`
- L18 _public enumerator_ `Launching`
- L19 _public enumerator_ `Running`
- L20 _public enumerator_ `Error`
