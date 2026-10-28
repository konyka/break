# Plugins / LiveLinkHubEditor

- module root: `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubEditor`
- headers: 5; symbols: 54
- symbol kinds: class=4, enum=1, enumerator=3, function=2, member=19, namespace=2, prototype=22, struct=1
- PrivateDependencyModuleNames: Engine, Json, LauncherPlatform, LiveLink, LiveLinkEditor, LiveLinkHub, LiveLinkHubMessaging, LiveLinkInterface, Serialization, Slate, SlateCore, ToolMenus, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubEditor/Private/LiveLinkHubClientIdCustomization.h` (Private)


#### class `FLiveLinkHubClientIdCustomization`  
`class FLiveLinkHubClientIdCustomization : public IPropertyTypeCustomization`  
_L13-25_
- inherits: `IPropertyTypeCustomization`
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L19 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _public function_ `virtual bool ShouldInlineKey() const override`
- L24 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;` — Cached property handle

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubEditor/Private/LiveLinkHubEditorModule.h` (Private)


#### class `FLiveLinkHubEditorModule`  
`class FLiveLinkHubEditorModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: Editor module responsible for creating the hub's status bar.
- L17 _public prototype_ `virtual void StartupModule();`
- L19 _public prototype_ `virtual void ShutdownModule();`
- L24 _private prototype_ `void OnPostEngineInit();` — Callback used to register the livelink hub status bar.
- L27 _private prototype_ `void RegisterLiveLinkHubStatusBar();` — Extend the editor's bottom status bar to add the livelink hub widget.
- L30 _private prototype_ `void UnregisterLiveLinkHubStatusBar();` — Unregister our tool menu customization.
- L33 _private prototype_ `TSharedRef<class SWidget> CreateLiveLinkHubWidget();` — Instantiate the livelink hub status bar widget.
- L36 _private member_ `FString LiveLinkHubExecutablePath;` — Path to livelink hub.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubEditor/Private/LiveLinkHubEditorSettings.h` (Private)


#### class `ULiveLinkHubEditorSettings`  
`class ULiveLinkHubEditorSettings : public UObject`  
_L13-33_
- reflection: `UCLASS(MinimalAPI, config = Editor, defaultconfig)`
- inherits: `UObject`
- desc: Settings for LiveLinkHub in editor.
- L20 _public member_ `bool bDetectLiveLinkHubExecutable = false;` — `UPROPERTY(config)` — Whether to find the livelinkhub executable by looking up a registry key.
- L24 _public member_ `FString LiveLinkHubStorePage;` — `UPROPERTY(config)` — Relative URI to the LiveLinkHub page in the epic games launcher.
- L28 _public member_ `FString LiveLinkHubAppName;` — `UPROPERTY(config)` — App name of LiveLinkHub, used to automatically detect if it's installed.
- L32 _public member_ `FString LiveLinkHubTargetVersion;` — `UPROPERTY(config)` — The version of LiveLinkHub that should be used. If empty, any version will be allowed.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubEditor/Private/SLiveLinkHubEditorStatusBar.h` (Private)


#### enum `EHubConnectionState`  
`enum EHubConnectionState`  
_L15-20_
- L17 _public enumerator_ `Invalid`
- L18 _public enumerator_ `Valid`
- L19 _public enumerator_ `Timeout`

#### class `SLiveLinkHubEditorStatusBar`  
`class SLiveLinkHubEditorStatusBar : public SCompoundWidget`  
_L23-79_
- inherits: `SCompoundWidget`
- desc: Widget responsible for showing the current connection status with the hub. Will only appear if a connection has been established with a hub instance.
- L25 _private function_ `SLATE_BEGIN_ARGS(SLiveLinkHubEditorStatusBar)`
- L28 _private prototype_ `~SLiveLinkHubEditorStatusBar() override;`
- L30 _private prototype_ `void Construct(const FArguments& InArgs);`
- L34 _private prototype_ `FText GetStatusText() const;` — Get the status text for the widget.
- L36 _private prototype_ `FText GetToolTipText() const;` — Get the tooltip text for the widget.
- L38 _private prototype_ `FSlateColor GetIconColor() const;` — Get the icon color for the widget according to the current status.
- L41 _private prototype_ `void OnSourceRemoved(FGuid SourceId);` — Handler used to update the current connection state.
- L44 _private prototype_ `void OnSubjectRemoved(FLiveLinkSubjectKey SubjectKey);` — Handler used to update the subject list displayed by the status bar.
- L47 _private prototype_ `void OnHubConnectionEstablished(FGuid SourceId);` — Handler used to update the connection state and source id when a connection with a hub instance is established.
- L50 _private prototype_ `void CheckHubConnection();` — Check whether the hub connection is still active.
- L53 _private prototype_ `EVisibility GetVisibility() const;` — Returns the visibility of the widget (Depends on whether we've established connection).
- L56 _private prototype_ `void RefreshSubjects();` — Method called when the subjects or sources have been modified, used to refresh the subject list UI.
- L60 _private member_ `class ILiveLinkClient* LiveLinkClient = nullptr;` — LiveLink client used to retrieve the status of the hub connection.
- L63 _private member_ `bool bHasConnectedOnce = false;` — Whether the editor was able to connect to a hub, will always show the status bar icon after this.
- L66 _private member_ `TSet<FGuid> SourceIds;` — Ids of the livelinkhub sources connected to this editor.
- L69 _private member_ `EHubConnectionState ConnectionState = Invalid;` — Current connection state to the hub.
- L72 _private member_ `FTimerHandle TimerHandle;` — Handle to the timer responsible for triggering CheckHubConnection.
- L75 _private member_ `static constexpr float CheckConnectionIntervalSeconds = 1.0f;` — Interval of the timer to check for connection validity.
- L78 _private member_ `TSharedPtr<class FLiveLinkSubjectsView> SubjectsView;` — Object responsible for creating and handling the subject list widget.

### `Plugins/Animation/LiveLinkHub/Source/LiveLinkHubEditor/Public/LiveLinkHubLauncherUtils.h` (Public)


#### struct `UE::LiveLinkHubLauncherUtils::FInstalledApp`  
`struct FInstalledApp`  
_L9-28_
- L12 _public member_ `FString InstallLocation;` — Location of the installed app.
- L15 _public member_ `FString NamespaceId;` — Namespace of the app.
- L18 _public member_ `FString ItemId;` — Id of the app.
- L21 _public member_ `FString ArtifactId;` — Unique ID for the app on the EGS.
- L24 _public member_ `FString AppVersion;` — Version of the app. For LiveLinkHub this will correspond to a CL number.
- L27 _public member_ `FString AppName;` — The apps' internal name. Usually matches the ArtifactId except if the app was using a legacy publishing workflow.

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace LiveLinkHubLauncherUtils` (scope `UE`)
- L31 _prototype_ `bool FindLiveLinkHubInstallation(FInstalledApp& OutLiveLinkHubInfo);` (scope `UE::LiveLinkHubLauncherUtils`) — Gather all the installed apps from the Epic Games Launcher.
- L34 _prototype_ `void OpenLiveLinkHub();` (scope `UE::LiveLinkHubLauncherUtils`) — Launch the livelinkhub executable.
