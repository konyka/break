# Plugins / ConcertInsightsClient

- module root: `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient`
- headers: 7; symbols: 45
- symbol kinds: class=6, function=5, member=2, namespace=12, prototype=20
- PrivateDependencyModuleNames: ConcertInsightsCore, ConcertSharedSlate, ConcertSyncClient, CoreUObject, EditorTraceUtilities, Engine, Slate, SlateCore, ToolMenus
- PublicDependencyModuleNames: Core

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Private/ClientTraceControls.h` (Private)


#### class `UE::ConcertInsightsClient::FClientTraceControls`  
`class FClientTraceControls : public ConcertInsightsCore::FTraceControls`  
_L14-35_
- inherits: `ConcertInsightsCore::FTraceControls`
- desc: Client controls for the editor. Puts the client's session and display name into the init args.
- L24 _protected prototype_ `virtual ConcertInsightsCore::FStartTraceArgs GetDefaultSynchronizedTraceArgs() const override;`
- L25 _protected prototype_ `virtual bool CanSendRequestsToEndpoint(const FGuid& EndpointId, const IConcertSession& Session) const override;`
- L26 _protected prototype_ `virtual ConcertInsightsCore::FInitArgs GetInitEventArgs() const override;`
- L31 _private prototype_ `FClientTraceControls();`
- L33 _private prototype_ `void OnSessionStart(TSharedRef<IConcertClientSession> Session);`
- L34 _private prototype_ `void OnSessionStopped(TSharedRef<IConcertClientSession> Session);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertInsightsClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Private/ConcertInsightsClient.h` (Private)


#### class `UE::ConcertInsightsClient::FConcertInsightsClientModule`  
`class FConcertInsightsClientModule : public IConcertInsightsClientModule`  
_L11-26_
- inherits: `IConcertInsightsClientModule`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private member_ `TUniquePtr<FClientTraceControls> TraceControls;` — The local state of synchronized tracing.
- L25 _private prototype_ `void PostEngineInit();`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertInsightsClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Private/ConcertInsightsClientSettings.h` (Private)


#### class `UConcertInsightsClientSettings`  
`class UConcertInsightsClientSettings : public UObject`  
_L9-19_
- reflection: `UCLASS(config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L14 _public function_ `static UConcertInsightsClientSettings* Get()`
- L18 _public member_ `FString SynchronizedTraceDestinationIP = TEXT("loc` — `UPROPERTY(config)` — This is the IP address that is sent to all endpoints to trace to when starting a synchronized trace.

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Private/StatusBar/SEditTraceDestinationWidget.h` (Private)


#### class `UE::ConcertInsightsClient::SEditTraceDestinationWidget`  
`class SEditTraceDestinationWidget : public SCompoundWidget`  
_L10-18_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SEditTraceDestinationWidget)`
- L15 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertInsightsClient` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Private/StatusBar/SMultiUserStatusBar.h` (Private)


#### class `UE::ConcertInsightsClient::SMultiUserStatusBar`  
`class SMultiUserStatusBar : public SCompoundWidget`  
_L13-34_
- inherits: `SCompoundWidget`
- L18 _public prototype_ `static void RegisterMultiUserToolMenu();` — Register the UToolMenu for the combo button.
- L20 _public function_ `SLATE_BEGIN_ARGS(SMultiUserStatusBar)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L26 _private prototype_ `TSharedRef<SWidget> MakeComboButton();`
- L27 _private prototype_ `TSharedRef<SWidget> MakeSessionConnectionIndicator() const;`
- L29 _private prototype_ `TSharedRef<SWidget> MakeTraceMenu() const;`
- L31 _private prototype_ `static bool IsConnectedToSession();`
- L32 _private prototype_ `static FText GetConnectionTooltip();`
- L33 _private prototype_ `static FText GetCurrentSessionLabel();`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace ConcertInsightsClient` (scope `UE`)
- L11 _prototype_ `void ExtendEditorStatusBarWithMultiUserWidget();` (scope `UE::ConcertInsightsClient`) — Extends the editor status bar with the Multi-User widget.

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Private/StatusBar/StatusBarExtension.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsClient` (scope `UE`)
- L12 _prototype_ `void ExtendMultiUserStatusBarWithInsights(FClientTraceControls& Controls);` (scope `UE::ConcertInsightsClient`) — Adds a sub-menu to the Multi User status bar.

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsClient/Source/ConcertInsightsClient/Public/IConcertInsightsClientModule.h` (Public)


#### class `UE::ConcertInsightsClient::IConcertInsightsClientModule`  
`class IConcertInsightsClientModule : public IModuleInterface`  
_L14-40_
- inherits: `IModuleInterface`
- desc: On the editor, this module - adds a context menu option to the Unreal Insights editor menu (bottom-right) for starting synchronized session tracing across multiple machines - listens for requests to synchronized session tracing while the local editor is in a Concert session
- L24 _public function_ `static inline IConcertInsightsClientModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsClient` (scope `UE`)
