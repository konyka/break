# Plugins / ConcertInsightsServer

- module root: `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsServer/Source/ConcertInsightsServer`
- headers: 3; symbols: 29
- symbol kinds: class=3, function=3, member=5, namespace=6, prototype=11, struct=1
- PrivateDependencyModuleNames: ConcertInsightsCore, ConcertSyncServer, CoreUObject, Slate, SlateCore, ToolMenus
- PublicDependencyModuleNames: Core

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsServer/Source/ConcertInsightsServer/Private/ConcertInsightsServer.h` (Private)


#### class `UE::ConcertInsightsServer::FConcertInsightsServerModule`  
`class FConcertInsightsServerModule : public IConcertInsightsServerModule`  
_L11-26_
- inherits: `IConcertInsightsServerModule`
- L16 _public prototype_ `virtual void StartupModule() override;`
- L17 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public function_ `FServerTraceControls& GetTraceControls()`
- L25 _private member_ `TUniquePtr<FServerTraceControls> TraceControls;` — The local state of synchronized tracing.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace ConcertInsightsServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsServer/Source/ConcertInsightsServer/Private/ServerTraceControls.h` (Private)


#### class `UE::ConcertInsightsServer::FServerTraceControls`  
`class FServerTraceControls : public ConcertInsightsCore::FTraceControls`  
_L22-66_
- inherits: `ConcertInsightsCore::FTraceControls`
- desc: Server controls for the editor. This class also keeps track of the client that instigated the synchronized trace. If the instigating client disconnects, all other endpoints are told to stop tracing.
- L32 _protected prototype_ `virtual void OnSynchronizedTraceAccepted(const FConcertSessionContext& Context, const FConcertTrace_StartSyncTrace_Request& Request, const TSharedRef<IConcertSession>& Session) override;`
- L33 _protected prototype_ `virtual bool CanSendRequestsToEndpoint(const FGuid& EndpointId, const IConcertSession& Session) const override;`
- L34 _protected prototype_ `virtual ConcertInsightsCore::FInitArgs GetInitEventArgs() const override;`
- L52 _private member_ `TWeakPtr<IConcertSyncServer> ServerInstance;` — Keeps track of the created server. Usually has 0 or 1 entries.
- L55 _private member_ `TOptional<FSynchronizedSessionServerData> InProgressSynchronizedServerTrace;` — Additional data for the server about the synchronized trace.
- L57 _private prototype_ `FServerTraceControls();`
- L59 _private prototype_ `void OnServerCreated(TWeakPtr<IConcertSyncServer> Server);`
- L60 _private prototype_ `void RegisterHandlersForSessions(IConcertServer& Server);`
- L62 _private prototype_ `void OnSessionStartup(TWeakPtr<IConcertServerSession> Session);`
- L63 _private prototype_ `void OnSynchronizedTraceClientChanged(IConcertServerSession& ConcertServerSession, EConcertClientStatus ConcertClientStatus, const FConcertSessionClientInfo& ConcertSessionClientInfo);`
- L65 _private prototype_ `void CleanUpClientsChangedDelegate();`

#### struct `UE::ConcertInsightsServer::FServerTraceControls::FSynchronizedSessionServerData`  
`struct FSynchronizedSessionServerData`  
_L39-49_
- L45 _public member_ `FGuid SynchronizedTraceInstigator;` — Endpoints of the endpoint that instigated the synchronized trace. If this endpoint disconnects, the server tells all other clients to terminate the synchronized trace.
- L48 _public member_ `TWeakPtr<IConcertServerSession> InitiatingSession;` — The server session on which this trace was started.

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ConcertInsightsServer` (scope `UE`)

### `Plugins/Developer/Concert/ConcertInsights/ConcertInsightsServer/Source/ConcertInsightsServer/Public/IConcertInsightsServerModule.h` (Public)


#### class `UE::ConcertInsightsServer::IConcertInsightsServerModule`  
`class IConcertInsightsServerModule : public IModuleInterface`  
_L12-38_
- inherits: `IModuleInterface`
- desc: On the server, this module listens for requests to start synchronized session tracing.
- L22 _public function_ `static inline IConcertInsightsServerModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() during shutdown if IsAvailable() returns true. @return True if the module is loaded and ready to use

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ConcertInsightsServer` (scope `UE`)
