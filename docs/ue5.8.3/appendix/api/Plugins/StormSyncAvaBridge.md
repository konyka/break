# Plugins / StormSyncAvaBridge

- module root: `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridge`
- headers: 5; symbols: 44
- symbol kinds: class=3, delegate=1, member=3, namespace=3, prototype=31, variable=3
- PrivateDependencyModuleNames: AvalancheMedia, CoreUObject, Engine, Slate, SlateCore, StormSyncCore, StormSyncTransportClient, StormSyncTransportCore, StormSyncTransportServer
- PublicDependencyModuleNames: Core

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridge/Private/ModularFeature/StormSyncAvaSyncProvider.h` (Private)


#### class `FStormSyncAvaSyncProvider`  
`class FStormSyncAvaSyncProvider : public IAvaMediaSyncProvider`  
_L18-81_
- inherits: `IAvaMediaSyncProvider`
- desc: Motion Design synchronization provider feature implementation
- L21 _public prototype_ `FStormSyncAvaSyncProvider();`
- L25 _public prototype_ `virtual FName GetName() const override;`
- L26 _public prototype_ `virtual void SyncToAll(const TArray<FName>& InPackageNames) override;`
- L27 _public prototype_ `virtual void PushToRemote(const FString& InRemoteName, const TArray<FName>& InPackageNames, const FOnAvaMediaSyncResponse& DoneDelegate) override;`
- L28 _public prototype_ `virtual void PullFromRemote(const FString& InRemoteName, const TArray<FName>& InPackageNames, const FOnAvaMediaSyncResponse& DoneDelegate) override;`
- L29 _public prototype_ `virtual void CompareWithRemote(const FString& InRemoteName, const TArray<FName>& InPackageNames, const FOnAvaMediaSyncCompareResponse& DoneDelegate) override;`
- L30 _public prototype_ `virtual FOnAvaMediaSyncPackageModified& GetOnAvaSyncPackageModified() override;`
- L35 _protected prototype_ `virtual void CompareWith(const FMessageAddress& InRemoteAddress, const TArray<FName>& InPackageNames, const FOnAvaMediaSyncCompareResponse& DoneDelegate);` — Low lvl API using direct message address destination
- L41 _protected prototype_ `void OnPakAssetExtracted(const FName& InPackageName, const FString& InDestFilepath);` — Handler called when a file is extracted from an incoming storm sync pak and relay to the OnAvaSyncPackageModified event
- L44 _private member_ `FOnAvaMediaSyncPackageModified OnAvaSyncPackageModified;`
- L56 _private prototype_ `static bool GetAddressFromUserData(const FString& InRemoteName, const FString& InUserDataKey, FMessageAddress& OutAddress, FText* OutErrorMessage = nullptr);` — Helper to get either client or server user data depending on local playback client / server state eg. 1. If client, we get user data from server 2. If server, we get user data from client 3. In case we are neither a client of server, returns invalid address and false 4. If an instance is both a client and server, the client takes priority and server side is ignored
- L59 _private prototype_ `static bool GetAddressFromServerUserData(const FString& InServerName, const FString& InUserDataKey, FMessageAddress& OutAddress, FText* OutErrorMessage = nullptr);` — Helper to get server user data from playback client
- L62 _private prototype_ `static bool GetAddressFromClientUserData(const FString& InClientName, const FString& InUserDataKey, FMessageAddress& OutAddress, FText* OutErrorMessage = nullptr);` — Helper to get client user data from playback server
- L65 _private prototype_ `static bool IsPlaybackServer();` — Returns whether local editor instance has a playback server started
- L68 _private prototype_ `static bool IsPlaybackClient();` — Returns whether local editor instance has a playback client started
- L71 _private prototype_ `static TSharedPtr<FAvaMediaSyncCompareResponse> CreateErrorResponse(const FText& InText);` — Helper to create a new error response (used when calling back DoneDelegate to indicate an error)
- L74 _private prototype_ `static FAvaMediaSyncResponse ConvertSyncResponse(const TSharedPtr<FStormSyncTransportSyncResponse>& InResponse);` — Helper to convert a FStormSyncTransportSyncResponse struct to the modular feature equivalent
- L77 _private prototype_ `static FAvaMediaSyncConnectionInfo ConvertConnectionInfo(const FStormSyncConnectionInfo& InConnectionInfo);` — Helper to convert a FStormSyncConnectionInfo struct to the modular feature equivalent
- L80 _private prototype_ `static EAvaMediaSyncEngineType ConvertInstanceType(const EStormSyncEngineType InInstanceType);` — Helper to convert instance type enum specific to this implementation to the interface one (for connection info)

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridge/Private/StormSyncAvaBridge.h` (Private)


#### class `FStormSyncAvaBridgeModule`  
`class FStormSyncAvaBridgeModule : public IModuleInterface`  
_L22-69_
- inherits: `IModuleInterface`
- desc: Module for Storm Sync Ava Bridge runtime module This class handles the update of User Data in Ava Media Playback Server when module is loaded, and Storm Sync server is started or stopped. This is then replicated and made available on remote clients so that a Playlist asset can associate a message bus address id (for storm sync push / sync) to a remote on a channel.
- L25 _private prototype_ `virtual void StartupModule() override;`
- L26 _private prototype_ `virtual void ShutdownModule() override;`
- L30 _private member_ `TArray<IConsoleObject*> ConsoleCommands;` — References of registered console commands via IConsoleManager
- L33 _private member_ `TUniquePtr<FStormSyncAvaSyncProvider> SyncProvider;` — Ava sync provider feature instance
- L36 _private prototype_ `void OnPostEngineInit();` — Updates playback user data when engine is fully loaded to setup storm sync message address ids
- L39 _private prototype_ `void RegisterConsoleCommands();` — Called from StartupModule and sets up console commands for the plugin via IConsoleManager
- L42 _private prototype_ `void UnregisterConsoleCommands();` — Called from ShutdownModule and clears out previously registered console commands
- L45 _private prototype_ `static void ExecuteGetUserData(const TArray<FString>& Args);` — Console command handler to return associated user data in ava playback server
- L48 _private prototype_ `void OnStormSyncServerStarted();` — Updates user data when storm sync server is started
- L51 _private prototype_ `void OnStormSyncServerStopped();` — Updates user data when storm sync server is stopped
- L58 _private prototype_ `static void RegisterUserDataForPlaybackServer();` — Actual helper to set the user data for a running playback server. Sets up Storm Sync Server / Client and Discovery Manager address ids
- L65 _private prototype_ `static void RegisterUserDataForPlaybackClient();` — Actual helper to set the user data for a running playback client. Sets up Storm Sync Server / Client and Discovery Manager address ids
- L68 _private prototype_ `static bool ValidateModulesAreAvailable();` — Helper ensuring all required modules are loaded available

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridge/Private/StormSyncAvaBridgeLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncAvaBridge, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncAvaBridge, Display, All);`

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridge/Public/StormSyncAvaBridgeCommon.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace StormSync` (scope `UE`)
- L7 _namespace_ `namespace AvaBridgeCommon` (scope `UE::StormSync`)
- L10 _variable_ `static constexpr const TCHAR* StormSyncServerAddressKey = TEXT("Sto` (scope `UE::StormSync::AvaBridgeCommon`) — The user data key to store storm sync server address id
- L13 _variable_ `static constexpr const TCHAR* StormSyncClientAddressKey = TEXT("Sto` (scope `UE::StormSync::AvaBridgeCommon`) — The user data key to store storm sync discovery manager address id
- L16 _variable_ `static constexpr const TCHAR* StormSyncDiscoveryAddressKey = TEXT("Sto` (scope `UE::StormSync::AvaBridgeCommon`) — The user data key to store storm sync discovery manager address id

### `Plugins/VirtualProduction/StormSyncAvalancheBridge/Source/StormSyncAvaBridge/Public/StormSyncAvaBridgeUtils.h` (Public)


#### class `FStormSyncAvaBridgeUtils`  
`class FStormSyncAvaBridgeUtils`  
_L8-13_
- L12 _public prototype_ `static TArray<FString> GetServerNamesForChannel(const FString& InChannelName);` — Returns the list of Ava Playback Server nmes for a given channel
