# Plugins / StormSyncTransportCore

- module root: `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore`
- headers: 10; symbols: 171
- symbol kinds: class=6, delegate=2, enum=1, enumerator=3, function=24, member=54, namespace=4, prototype=55, struct=20, variable=2
- PrivateDependencyModuleNames: DeveloperSettings, Engine, MessagingCommon, Networking, Sockets, StormSyncCore
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Internal/IStormSyncTransportCoreModule.h` (Internal)


#### class `IStormSyncTransportCoreModule`  
`class IStormSyncTransportCoreModule : public IModuleInterface`  
_L8-45_
- inherits: `IModuleInterface`
- L17 _public function_ `static IStormSyncTransportCoreModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L28 _public function_ `static bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L35 _public prototype_ `DECLARE_DELEGATE_RetVal(FString, FOnGetEndpointConfig);` — Definition of a delegate to query endpoint configuration.
- L38 _public prototype_ `virtual FOnGetEndpointConfig& OnGetCurrentTcpServerEndpointAddress() = 0;` — Delegate for querying the currently bound tcp server address.
- L41 _public prototype_ `virtual FOnGetEndpointConfig& OnGetServerEndpointMessageAddress() = 0;` — Delegate for querying the message bus server endpoint address.
- L44 _public prototype_ `virtual FOnGetEndpointConfig& OnGetClientEndpointMessageAddress() = 0;` — Delegate for querying the message bus client endpoint address.

#### Free symbols / members of external scopes

- L35 _delegate_ `DECLARE_DELEGATE_RetVal(FString, FOnGetEndpointConfig);` — Definition of a delegate to query endpoint configuration.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Private/StormSyncTransportCoreLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncTransportCore, Display, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogStormSyncTransportCore, Display, All);`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Private/StormSyncTransportCoreModule.h` (Private)


#### class `FStormSyncTransportCoreModule`  
`class FStormSyncTransportCoreModule : public IStormSyncTransportCoreModule`  
_L12-25_
- inherits: `IStormSyncTransportCoreModule`
- desc: Implements the StormSyncTransportCore module.
- L16 _public function_ `virtual FOnGetEndpointConfig& OnGetCurrentTcpServerEndpointAddress() override`
- L17 _public function_ `virtual FOnGetEndpointConfig& OnGetServerEndpointMessageAddress() override`
- L18 _public function_ `virtual FOnGetEndpointConfig& OnGetClientEndpointMessageAddress() override`
- L22 _private member_ `FOnGetEndpointConfig OnGetCurrentTcpServerAddressDelegate;`
- L23 _private member_ `FOnGetEndpointConfig OnGetServerEndpointMessageAddressDelegate;`
- L24 _private member_ `FOnGetEndpointConfig OnGetClientEndpointMessageAddressDelegate;`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/IStormSyncTransportLocalEndpoint.h` (Public)


#### class `IStormSyncTransportLocalEndpoint`  
`class IStormSyncTransportLocalEndpoint : public TSharedFromThis<IStormSyncTransportLocalEndpoint, ESPMode::ThreadSafe>`  
_L12-23_
- inherits: `TSharedFromThis<IStormSyncTransportLocalEndpoint,ESPMode::ThreadSafe>`
- desc: Interface representing a local endpoint you can send from for Storm Sync
- L16 _public prototype_ `virtual ~IStormSyncTransportLocalEndpoint() = default;` — Virtual destructor
- L19 _public prototype_ `virtual bool IsRunning() const = 0;` — Returns whether message endpoint is currently active
- L22 _public prototype_ `virtual TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> GetMessageEndpoint() const = 0;` — Returns underlying message endpoint implemented by the local endpoint provider

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/IStormSyncTransportMessageService.h` (Public)


#### class `IStormSyncTransportMessageService`  
`class IStormSyncTransportMessageService : public TSharedFromThis<IStormSyncTransportMessageService, ESPMode::ThreadSafe>`  
_L14-22_
- inherits: `TSharedFromThis<IStormSyncTransportMessageService,ESPMode::ThreadSafe>`
- desc: Interface for message services They are typically created within a IStormSyncTransportLocalEndpoint derived class, from local endpoints' InitializeMessaging() post constructor time.
- L18 _public prototype_ `virtual ~IStormSyncTransportMessageService() = default;` — Virtual destructor
- L21 _public prototype_ `virtual void InitializeMessageEndpoint(FMessageEndpointBuilder& InEndpointBuilder) = 0;` — This lets child classes the opportunity to add custom message handlers to the endpoint builder

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/StormSyncTransportMessages.h` (Public)


#### struct `FStormSyncTransportHeartbeatMessage`  
`struct FStormSyncTransportHeartbeatMessage`  
_L12-22_
- reflection: `USTRUCT()`
- desc: Empty message indicating an Heartbeat event
- L18 _public member_ `bool bIsServerRunning = false;` — `UPROPERTY(EditAnywhere, Category="Storm Sync Message")` — Whether local server endpoint is currently running and able to receive incoming connections
- L21 _public prototype_ `FStormSyncTransportHeartbeatMessage() = default;` — Default constructor

#### struct `FStormSyncConnectionInfo`  
`struct FStormSyncConnectionInfo`  
_L26-74_
- reflection: `USTRUCT()`
- desc: Holds data about local project (such as Message Address Ids, Project Name, Hostname, InstanceId, etc.)
- L32 _public member_ `int32 EngineVersion = 0;` — `UPROPERTY(EditAnywhere, Category="Storm Sync Message")` — Holds the engine version checksum
- L36 _public member_ `FGuid InstanceId;` — `UPROPERTY(EditAnywhere, Category="Storm Sync Message")` — Holds the instance identifier
- L40 _public member_ `EStormSyncEngineType InstanceType = EStormSyncEngineType::Unknown;` — `UPROPERTY(EditAnywhere, Category="Storm Sync Message")` — Holds the type of the engine instance
- L44 _public member_ `FGuid SessionId;` — `UPROPERTY(EditAnywhere, Category="Storm Sync Message")` — Holds the identifier of the session that the application belongs to
- L48 _public member_ `FString StormSyncServerAddressId;` — `UPROPERTY(EditAnywhere, Category="Storm Sync Message")` — Holds the message bus address identifier for Storm Sync Server endpoint
- L52 _public member_ `FString StormSyncClientAddressId;` — `UPROPERTY(EditAnywhere, Category="Storm Sync Message")` — Holds the message bus address identifier for Storm Sync Client endpoint
- L56 _public member_ `FString HostName;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The hostname this message was generated from
- L60 _public member_ `FString ProjectName;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The unreal project name this message was generated from
- L64 _public member_ `FString ProjectDir;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The unreal project directory this message was generated from
- L67 _public prototype_ `FStormSyncConnectionInfo();` — Default constructor
- L70 _public prototype_ `FString ToString() const;` — Returns debug string for this message
- L73 _public prototype_ `static FString GetBasename(const FString& InPath);` — Internal helper to return the last portion of a path, similar to the Unix basename command. Trailing directory separators are ignored

#### struct `FStormSyncTransportConnectMessage`  
`struct FStormSyncTransportConnectMessage : public FStormSyncConnectionInfo`  
_L78-81_
- reflection: `USTRUCT()`
- inherits: `FStormSyncConnectionInfo`
- desc: Connection message indicating a Connect event with data about local project / application

#### struct `FStormSyncTransportWakeupRequest`  
`struct FStormSyncTransportWakeupRequest`  
_L85-88_
- reflection: `USTRUCT()`
- desc: Request sent by the discovery service to wake up the other endpoints in case they become inactive.

#### struct `FStormSyncTransportSyncRequest`  
`struct FStormSyncTransportSyncRequest`  
_L102-134_
- reflection: `USTRUCT()`
- desc: FStormSyncTransportSyncRequest. A sync request represents the ava package and files we want to synchronize. Contains info such as: - The top level list of package names we want to synchronize - The package descriptor metadata (name, description, etc.) along the list of inner dependencies and their state (file size, timestamp, file hash, etc.)
- L108 _public member_ `FGuid MessageId;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The message ID of this sync request / response transaction (used to identify the correct response from the target)
- L112 _public member_ `TArray<FName> PackageNames;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The top level list of package names (from which we gather the list of inner file dependencies / references)
- L116 _public member_ `FStormSyncPackageDescriptor PackageDescriptor;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The package descriptor describing the state of the ava package we want to synchronize
- L119 _public prototype_ `FStormSyncTransportSyncRequest() = default;` — Default constructor.
- L121 _public function_ `explicit FStormSyncTransportSyncRequest(const FGuid& InMessageId) : MessageId(InMessageId)`
- L126 _public function_ `FStormSyncTransportSyncRequest(const TArray<FName>& InPackageNames, const FStormSyncPackageDescriptor& InPackageDescriptor) : MessageId(FGuid::NewGuid()) , PackageNames( InPackageNames) , PackageDescriptor(InPackageDescriptor)`
- L133 _public prototype_ `FString ToString() const;`

#### struct `FStormSyncTransportPushRequest`  
`struct FStormSyncTransportPushRequest : public FStormSyncTransportSyncRequest`  
_L145-156_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportSyncRequest`
- desc: Push Request message (which is effectively a SyncRequest without extra info) This is a separate struct to differentiate this message from sync request, that is used to broadcast a synchronization request to all receivers active on the network. This one is meant to be used to send a synchronization request to a specific remote.
- L150 _public prototype_ `FStormSyncTransportPushRequest() = default;` — Default constructor.
- L152 _public function_ `FStormSyncTransportPushRequest(const TArray<FName>& InPackageNames, const FStormSyncPackageDescriptor& InPackageDescriptor) : FStormSyncTransportSyncRequest(InPackageNames, InPackageDescriptor)`

#### struct `FStormSyncTransportPullRequest`  
`struct FStormSyncTransportPullRequest : public FStormSyncTransportSyncRequest`  
_L165-192_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportSyncRequest`
- desc: Pull Request message (which is effectively a SyncRequest with extra info about local server and network config) We are sending network / server info so that remote can initiate a sync response with correct address the tcp client will attempt to send buffer to.
- L171 _public member_ `FString HostName;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The hostname this message was generated from
- L175 _public member_ `FString HostAddress;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The host endpoint address local tcp server is currently listening on this message was generated from (can be 0.0.0.0)
- L183 _public member_ `TArray<FString> HostAdapterAddresses;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The host local addresses associated with the adapters on the local computer. Clients should try to connect to each when server is listening on 0.0.0.0
- L186 _public prototype_ `FStormSyncTransportPullRequest() = default;` — Default constructor.
- L188 _public function_ `FStormSyncTransportPullRequest(const TArray<FName>& InPackageNames, const FStormSyncPackageDescriptor& InPackageDescriptor) : FStormSyncTransportSyncRequest(InPackageNames, InPackageDescriptor)`

#### enum `EStormSyncResponseResult`  
`enum class EStormSyncResponseResult : uint8`  
_L195-205_
- reflection: `UENUM()`
- L198 _public enumerator_ `Error` — Indicates an Error happened
- L201 _public enumerator_ `Success` — Indicates successful completion
- L204 _public enumerator_ `Unknown` — Should not happen

#### struct `FStormSyncTransportSyncResponse`  
`struct FStormSyncTransportSyncResponse : public FStormSyncTransportSyncRequest`  
_L219-271_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportSyncRequest`
- desc: FStormSyncTransportSyncResponse. Effectively a sync request with: - An additional list of sync modifiers, representing the diffing results and files we want to synchronize. - Additional information about server network settings such as Hostname and Address. @see FStormSyncFileModifierInfo
- L225 _public member_ `EStormSyncResponseResult Status = EStormSyncResponseResult::Unknown;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — Status of the response, error or success
- L235 _public member_ `FText StatusText;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — Localized text that can be filled with further information about response. In case of error, a localized text describing what went wrong. In case of success, either empty or filled with useful info for the remote to know.
- L240 _public member_ `FStormSyncConnectionInfo ConnectionInfo;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — Holds data about local project and send to remote for it to display as result status
- L244 _public member_ `TArray<FStormSyncFileModifierInfo> Modifiers;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — List of sync modifiers, either an Addition, Missing or Overwrite operation
- L248 _public member_ `FString HostName;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The hostname this message was generated from
- L252 _public member_ `FString HostAddress;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The host endpoint address local tcp server is currently listening on this message was generated from (can be 0.0.0.0)
- L260 _public member_ `TArray<FString> HostAdapterAddresses;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The host local addresses associated with the adapters on the local computer. Clients should try to connect to each when server is listening on 0.0.0.0
- L263 _public prototype_ `FStormSyncTransportSyncResponse() = default;` — Default constructor
- L265 _public function_ `explicit FStormSyncTransportSyncResponse(const FGuid& InMessageId) : FStormSyncTransportSyncRequest(InMessageId)`
- L270 _public prototype_ `FString ToString() const;`

#### struct `FStormSyncTransportPushResponse`  
`struct FStormSyncTransportPushResponse : public FStormSyncTransportSyncResponse`  
_L277-288_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportSyncResponse`
- desc: FStormSyncTransportPushResponse, a FStormSyncTransportSyncResponse child struct.
- L282 _public prototype_ `FStormSyncTransportPushResponse() = default;` — Default constructor.
- L284 _public function_ `explicit FStormSyncTransportPushResponse(const FGuid& InMessageId) : FStormSyncTransportSyncResponse(InMessageId)`

#### struct `FStormSyncTransportPullResponse`  
`struct FStormSyncTransportPullResponse : public FStormSyncTransportSyncResponse`  
_L294-307_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportSyncResponse`
- desc: FStormSyncTransportPullResponse, a FStormSyncTransportSyncResponse child struct.
- L299 _public prototype_ `FStormSyncTransportPullResponse() = default;` — Default constructor.
- L301 _public function_ `explicit FStormSyncTransportPullResponse(const FGuid& InMessageId) : FStormSyncTransportSyncResponse(InMessageId)`
- L306 _public prototype_ `FString ToString() const;`

#### struct `FStormSyncTransportStatusRequest`  
`struct FStormSyncTransportStatusRequest`  
_L310-339_
- reflection: `USTRUCT()`
- L316 _public member_ `FGuid MessageId;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The request ID of this status (used to identify the correct response from the target)
- L320 _public member_ `TArray<FName> PackageNames;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The top level list of package names (from which we gather the list of inner file dependencies / references)
- L324 _public member_ `TArray<FStormSyncFileDependency> Dependencies;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The inner list of file assets dependencies for this ava package
- L326 _public prototype_ `FStormSyncTransportStatusRequest() = default;`
- L328 _public function_ `FStormSyncTransportStatusRequest(const TArray<FName>& InPackageNames, const TArray<FStormSyncFileDependency>& InFileDependencies) : MessageId(FGuid::NewGuid()) , PackageNames(InPackageNames) , Dependencies(InFileDependencies)`
- L335 _public function_ `FString ToString() const`

#### struct `FStormSyncTransportStatusResponse`  
`struct FStormSyncTransportStatusResponse`  
_L342-373_
- reflection: `USTRUCT()`
- L348 _public member_ `FGuid StatusRequestId;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The request ID of this status (used to identify the correct response from the target)
- L352 _public member_ `FStormSyncConnectionInfo ConnectionInfo;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — Holds data about local project and send to remote for it to display as result status
- L356 _public member_ `bool bNeedsSynchronization = false;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — Whether the two remotes have differing state (eg. Modifiers array is not empty)
- L360 _public member_ `TArray<FStormSyncFileModifierInfo> Modifiers;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — List of sync modifiers, either an Addition, Missing or Overwrite operation
- L362 _public prototype_ `FStormSyncTransportStatusResponse() = default;`
- L364 _public function_ `explicit FStormSyncTransportStatusResponse(const FGuid& InId) : StatusRequestId(InId)`
- L369 _public function_ `FString ToString() const`

#### struct `FStormSyncTransportStatusPing`  
`struct FStormSyncTransportStatusPing`  
_L376-379_
- reflection: `USTRUCT()`

#### struct `FStormSyncTransportStatusPong`  
`struct FStormSyncTransportStatusPong`  
_L382-385_
- reflection: `USTRUCT()`

#### struct `FStormSyncTransportPingMessage`  
`struct FStormSyncTransportPingMessage`  
_L389-421_
- reflection: `USTRUCT()`
- desc: Basic Ping message
- L395 _public member_ `FString Hostname;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The hostname this message was generated from (defaults to platform computer name)
- L399 _public member_ `FString Username;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The platform username for the host this message was generated from
- L403 _public member_ `FString ProjectName;` — `UPROPERTY(VisibleAnywhere, Category = "Storm Sync Message")` — The local project name this message was generated from
- L406 _public function_ `FStormSyncTransportPingMessage() : Hostname(FPlatformProcess::ComputerName()), Username(FPlatformProcess::UserName()), ProjectName(FApp::GetProjectName())` — Default constructor.
- L413 _public function_ `FStormSyncTransportPingMessage(const FString& Hostname, const FString& Username) : Hostname(Hostname), Username(Username), ProjectName(FApp::GetProjectName())`
- L420 _public prototype_ `FString ToString() const;`

#### struct `FStormSyncTransportPongMessage`  
`struct FStormSyncTransportPongMessage : public FStormSyncTransportPingMessage`  
_L425-436_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportPingMessage`
- desc: Basic Pong message (which is effectively a Ping without extra info)
- L430 _public prototype_ `FStormSyncTransportPongMessage() = default;` — Default constructor.
- L432 _public function_ `FStormSyncTransportPongMessage(const FString& Hostname, const FString& Username) : FStormSyncTransportPingMessage(Hostname, Username)`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/StormSyncTransportNetworkUtils.h` (Public)


#### class `FStormSyncTransportNetworkUtils`  
`class FStormSyncTransportNetworkUtils`  
_L15-41_
- desc: Network related helpers Main purpose of this class is to return correct information about network settings from UStormSyncTransportSettings and Socket Subsystem.
- L19 _public prototype_ `static FString GetServerName();` — Returns either the configured Server Name in settings, or falls back to platform computer name
- L22 _public prototype_ `static FString GetTcpEndpointAddress();` — Parses and return configured server endpoint in settings, or an empty string if setting is invalid
- L28 _public prototype_ `static TArray<FString> GetLocalAdapterAddresses();` — Returns the list of local adapter addresses as returned by the socket subsystem, with current port from server endpoint appended to the address list.
- L34 _public prototype_ `static FString GetCurrentTcpServerEndpointAddress();` — Returns the current tcp server endpoint address (ip:port). @remark This is potentially different from the configured endpoint address in case of port collisions, it may be on a different one.
- L37 _public prototype_ `static FString GetServerEndpointMessageAddress();` — Returns the current message bus server endpoint address.
- L40 _public prototype_ `static FString GetClientEndpointMessageAddress();` — Returns the current message bus client endpoint address.

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/StormSyncTransportSettings.h` (Public)


#### class `UStormSyncTransportSettings`  
`class UStormSyncTransportSettings : public UDeveloperSettings`  
_L16-196_
- reflection: `UCLASS(Config=Game, DefaultConfig, DisplayName="Transport & Network")`
- inherits: `UDeveloperSettings`
- desc: Settings for the StormSyncTransport plugins. Handles config for transport / network related features.
- L24 _public prototype_ `UStormSyncTransportSettings();`
- L26 _public prototype_ `static const UStormSyncTransportSettings& Get();`
- L30 _public prototype_ `void OpenEditorSettingsWindow() const;` — Helper to bring focus on transport settings in editor
- L40 _public prototype_ `FString GetServerEndpoint() const;` — Gets the listen endpoint endpoint to listen to when starting off the tcp socket server listener. The format is IP_ADDRESS:PORT_NUMBER. 0.0.0.0 will bind to the default network adapter on Windows, and all available network adapters on other operating systems.
- L43 _public prototype_ `FString GetTcpServerAddress() const;` — Returns the hostname tcp server is configured to run on
- L46 _public prototype_ `uint16 GetTcpServerPort() const;` — Returns the port tcp server is configured to run on
- L51 _public function_ `uint16 GetTcpServerPortMaxOffset() const` — Returns th port offset range when trying to acquire an available socket for the Tcp server.
- L54 _public prototype_ `uint32 GetInactiveTimeoutSeconds() const;` — Returns inactive timeout period. The amount of time in seconds to consider a client to be inactive
- L57 _public prototype_ `bool IsTcpDryRun() const;` — Returns true if we are in debug mode dry mode and shouldn't extract incoming buffer to local project
- L60 _public prototype_ `uint32 GetConnectionRetryDelay() const;` — Returns connection delay
- L63 _public prototype_ `bool HasConnectionRetryDelay() const;` — Returns connection delay
- L66 _public prototype_ `FString GetServerName() const;` — Returns user friendly name to describe this server on the network (defaults to hostname if left to empty)
- L69 _public prototype_ `bool IsAutoStartServer() const;` — Whether we should start the server endpoint on startup
- L72 _public prototype_ `float GetMessageBusHeartbeatPeriod() const;` — Returns message bus heartbeat frequency in seconds
- L75 _public prototype_ `float GetDiscoveryManagerTickInterval() const;` — Returns message bus heartbeat frequency in seconds, tick interval for the discovery manager to check for heartbeats timeouts
- L78 _public prototype_ `double GetMessageBusHeartbeatTimeout() const;` — Returns message bus heartbeat timeout in seconds, to determine when a connected device becomes unresponsive
- L81 _public prototype_ `double GetMessageBusTimeBeforeRemovingInactiveSource() const;` — Returns message bus inactive timeout in seconds, to determine when a connected device is considered disconnected
- L84 _public prototype_ `bool IsDiscoveryPeriodicPublishEnabled() const;` — Returns whether discovery manager should send a connect message at a regular interval (broadcast / publish)
- L87 _public prototype_ `bool ShouldShowImportWizard() const;` — Returns true if we are in debug mode dry mode and shouldn't extract incoming buffer to local project
- L97 _private member_ `bool bOverrideServerAddress = false;` — `UPROPERTY(config, EditAnywhere, Category = "Server")` — Whether to use a custom listen hostname address for the TCP server. By Default, Storm Sync will use the same value as defined in UDPMessagingSettings > Unicast Endpoint (or `-UDPMESSAGING_TRANSPORT_UNICAST=` command line flag)
- L109 _private member_ `FString TcpServerAddress;` — `UPROPERTY(config, EditAnywhere, Category = "Server", meta=(EditCondition = "bOverrideServerAddress", EditConditionHides))` — The IP endpoint to listen to when starting off the tcp socket server listener. 0.0.0.0 will bind to the default network adapter on Windows, and all available network adapters on other operating systems. Note: Only used if bOverrideServerAddress is false Can be specified on the command line with `-StormSyncServerEndpoint=`
- L117 _private member_ `uint16 TcpServerPort = 40990;` — `UPROPERTY(config, EditAnywhere, Category = "Server")` — The port to listen on when starting off the tcp socket server listener. Can be specified on the command line with `-StormSyncServerEndpoint=`
- L124 _private member_ `uint16 TcpServerPortMaxOffset = 10;` — `UPROPERTY(config, EditAnywhere, Category = "Server")` — Specifies the port offset range when trying to acquire an available socket for the Tcp server. The range of ports will be [TcpServerPort, TcpServerPort + TcpServerPortMaxOffset - 1].
- L130 _private member_ `FString ServerName;` — `UPROPERTY(config, EditAnywhere, Category = "Server")` — User friendly name to describe this server on the network (defaults to hostname if left to empty)
- L136 _private member_ `bool bAutoStartServer = true;` — `UPROPERTY(config, EditAnywhere, Category = "Server")` — Should this editor instance starts on startup a Storm Sync server endpoint (messaging and tcp)
- L144 _private member_ `uint32 InactiveTimeoutSeconds = 5;` — `UPROPERTY(config, EditAnywhere, Category = "Server")` — The amount of time in seconds to consider a client to be inactive, if it has not sent data in this interval. Server listener will close the tcp connection for any inactive clients passed that delay.
- L152 _private member_ `bool bTcpDryRun = false;` — `UPROPERTY(config, EditAnywhere, Category = "Server")` — Debug Development config. When set to true, an ava pak buffer received over tcp connection will only be displayed in console and not extracted / installed to local project
- L162 _private member_ `uint32 ConnectionRetryDelay = 0;` — `UPROPERTY(config, EditAnywhere, Category = "Client")` — Delay time between attempts to re-establish outgoing connections that become disconnected or fail to connect 0 disables reconnection Note that editor must be restarted for changes to this config to be taken into account.
- L166 _private member_ `float MessageBusHeartbeatPeriod = 1.f;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service Discovery", meta=(ClampMin = "0.1", ConfigRestartRequired=true, ForceUnits=s))` — The refresh frequency of the heartbeat event
- L170 _private member_ `float DiscoveryManagerTickInterval = 1.f;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service Discovery", meta=(ClampMin = "0.1", ConfigRestartRequired=true, ForceUnits=s))` — How long we should wait before checking for message bus sources activity
- L174 _private member_ `double MessageBusHeartbeatTimeout = 2.0;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service Discovery", meta=(ClampMin = "0.1", ConfigRestartRequired=true, ForceUnits=s))` — How long we should wait before a connected device becomes unresponsive
- L178 _private member_ `double MessageBusTimeBeforeRemovingInactiveSource = 15.0;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service Discovery", meta=(ClampMin = "0.1", ConfigRestartRequired=true, ForceUnits=s))` — Subjects will be removed when their source has been unresponsive for this long
- L188 _private member_ `bool bEnableDiscoveryPeriodicPublish = true;` — `UPROPERTY(config, EditAnywhere, AdvancedDisplay, Category = "Service Discovery", meta=(ConfigRestartRequired=true))` — Whether to allow Discovery Manager to broadcast a connect message at periodic interval (period time being the value of MessageBusTimeBeforeRemovingInactiveSource). This is a fail-safe mechanism to ensure editor instances can still discover each other in case both ends were inactive for an extended period of time.
- L192 _private member_ `bool bShowImportWizard = false;` — `UPROPERTY(config, EditAnywhere, Category = "UI")` — When set to true, an import wizard will be prompted to the user upon receiving a buffer request from network
- L195 _private prototype_ `bool GetUdpMessagingUnicastEndpoint(FString& OutUnicastHostname, FString& OutUnicastPort) const;` — Internal helper to return the value of UdpMessagingSettings UnicastEndpoint

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/StormSyncTransportTcpPackets.h` (Public)


#### struct `FStormSyncTransportTcpPacket`  
`struct FStormSyncTransportTcpPacket`  
_L8-28_
- reflection: `USTRUCT()`
- L18 _public member_ `FString Command;` — `UPROPERTY()` — An arbitrary "command" used when parsing JSON string to differentiate the incoming packets. Set in child structs.
- L22 _public member_ `FString HostName;` — `UPROPERTY()` — Host name the packet was generated from
- L24 _public function_ `FStormSyncTransportTcpPacket() : HostName(FPlatformProcess::ComputerName())`

#### struct `FStormSyncTransportTcpStatePacket`  
`struct FStormSyncTransportTcpStatePacket : public FStormSyncTransportTcpPacket`  
_L32-41_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportTcpPacket`
- desc: This is an initial snapshot, sent upon connecting
- L36 _public function_ `FStormSyncTransportTcpStatePacket() : FStormSyncTransportTcpPacket()`

#### struct `FStormSyncTransportTcpSizePacket`  
`struct FStormSyncTransportTcpSizePacket : public FStormSyncTransportTcpPacket`  
_L45-61_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportTcpPacket`
- desc: This is a socket "message" sent from receiver to notify sender of the amount of bytes received so far
- L51 _public member_ `uint32 ReceivedBytes = 0;` — `UPROPERTY()` — Number of bytes received so far
- L53 _public prototype_ `FStormSyncTransportTcpSizePacket() = default;`
- L55 _public function_ `explicit FStormSyncTransportTcpSizePacket(const uint32 InReceivedBytes) : FStormSyncTransportTcpPacket() , ReceivedBytes(InReceivedBytes)`

#### struct `FStormSyncTransportTcpTransferCompletePacket`  
`struct FStormSyncTransportTcpTransferCompletePacket : public FStormSyncTransportTcpPacket`  
_L65-74_
- reflection: `USTRUCT()`
- inherits: `FStormSyncTransportTcpPacket`
- desc: This is a socket "message" sent from receiver to notify sender of the amount of bytes received so far
- L69 _public function_ `FStormSyncTransportTcpTransferCompletePacket() : FStormSyncTransportTcpPacket()`

### `Plugins/VirtualProduction/StormSync/Source/StormSyncTransportCore/Public/Utils/StormSyncTransportCommandUtils.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace StormSync` (scope `UE`)
- L8 _namespace_ `namespace Transport` (scope `UE::StormSync`)
- L8 _namespace_ `namespace Private` (scope `UE::StormSync::Transport`)
- L10 _variable_ `static const TCHAR* ServerEndpointFlag = TEXT("Sto` (scope `UE::StormSync::Transport::Private`)
- L11 _variable_ `static const TCHAR* NoServerAutoStartFlag = TEXT("NoS` (scope `UE::StormSync::Transport::Private`)
- L21 _prototype_ `bool GetServerEndpointParam(FString& OutEndpointValue, const FString& InDefaultHostName = FString());` (scope `UE::StormSync::Transport::Private`) — Returns value of command line -StormSyncServerEndpoint=hostname:1234 flag. Port value must be a valid digit. If "hostname" is omitted then the value of UStormSyncTransportSettings::TcpServerAddress is used from project settings with whatever Port value was given via command line (eg. 0.0.0.0:1234) OutEndpointValue will be updated only if the parsing was successful.
- L24 _prototype_ `bool IsServerAutoStartDisabled();` (scope `UE::StormSync::Transport::Private`) — Returns whether command line has either -StormSyncServerAutoStart or a valid -StormSyncServerEndpoint=<Port>
