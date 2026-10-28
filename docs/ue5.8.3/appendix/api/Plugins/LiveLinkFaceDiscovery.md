# Plugins / LiveLinkFaceDiscovery

- module root: `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceDiscovery`
- headers: 2; symbols: 30
- symbol kinds: class=2, delegate=1, function=3, member=11, prototype=12, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: CaptureProtocolStack, CaptureUtils, Core

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceDiscovery/Private/LiveLinkFaceDiscoveryModule.h` (Private)


#### class `FLiveLinkFaceDiscoveryModule`  
`class FLiveLinkFaceDiscoveryModule : public IModuleInterface`  
_L7-17_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MetaHuman/MetaHumanLiveLink/Source/LiveLinkFaceDiscovery/Public/LiveLinkFaceDiscovery.h` (Public)


#### class `FLiveLinkFaceDiscovery`  
`class FLiveLinkFaceDiscovery : public TSharedFromThis<FLiveLinkFaceDiscovery>`  
_L20-99_
- inherits: `TSharedFromThis<FLiveLinkFaceDiscovery>`
- desc: Periodically sends out multicast discovery requests and listens for any responses from devices running the Live Link Face application. In addition, if a device sends a discovery notification the internal list of discovered servers will be updated. Each time the internal server list is updated the delegate will be triggered on the game thread with a set of discovered servers.
- L57 _public function_ `friend uint32 GetTypeHash(const FServer& Server)`
- L68 _public prototype_ `FLiveLinkFaceDiscovery(const double InRefreshDelay = 3.0f, const double InServerExpiry = 6.0f);` — @param InRefreshDelay The period of time in seconds to wait before sending discovery requests. @param InServerExpiry The period of time after which we consider a device stale and remove it from the set. Note that this will only be evaluated every InRefreshDelay seconds and should be larger than the refresh delay.
- L69 _public prototype_ `~FLiveLinkFaceDiscovery();`
- L74 _public prototype_ `void Start();` — Start discovery. Bind to the OnServersUpdated delegate before starting to receive every update.
- L76 _public prototype_ `void Stop();`
- L78 _public prototype_ `DECLARE_DELEGATE_OneParam(FOnServersUpdated, const TSet<FServer>& Servers);`
- L83 _public member_ `FOnServersUpdated OnServersUpdated;` — Bind to this delegate before starting discovery in order to receive every update
- L86 _private member_ `const float RefreshDelay;`
- L87 _private member_ `const float ServerExpiry;`
- L89 _private member_ `TUniquePtr<UE::CaptureManager::FDiscoveryMessenger> DiscoveryMessenger;`
- L90 _private member_ `FTSTicker::FDelegateHandle RefreshTickerHandle;`
- L91 _private member_ `TSet<FServer> Servers;`
- L93 _private prototype_ `static uint32 Pack(const uint8 InA, const uint8 InB, const uint8 InC, const uint8 InD);`
- L95 _private prototype_ `FServer CreateServer(const FString& InServerAddress, const TStaticArray<uint8, 16>& InServerId, const FString& InServerName, const uint16 InControlPort);`
- L96 _private prototype_ `bool Refresh(float InDeltaTime);`
- L97 _private prototype_ `void SendRequestBurst() const;`
- L98 _private prototype_ `void UpdateDelegate();`

#### struct `FLiveLinkFaceDiscovery::FServer`  
`struct FServer`  
_L26-61_
- desc: A representation of a discovered device running the Live Link Face application
- L29 _public member_ `const FGuid Id;` — A unique identifier for the device
- L32 _public member_ `const FString Name;` — The user defined device name
- L35 _public member_ `const FString Address;` — The IPV4 address of the discovered device
- L38 _public member_ `const uint16 ControlPort;` — The port to use when establishing a CPS control TCP connection
- L41 _public member_ `const double LastSeen;` — The PlatformTime when the device last provided a discovery response or notification
- L43 _public function_ `FServer(const FGuid InId, FString InName, FString InAddress, const uint16 InControlPort, const double InLastSeen) : Id(InId) , Name(MoveTemp(InName)) , Address(MoveTemp(InAddress)) , ControlPort(InControlPort) , LastSeen(InLastSeen)`
- L52 _public function_ `bool operator==(const FServer& InOther) const`

#### Free symbols / members of external scopes

- L78 _delegate_ `DECLARE_DELEGATE_OneParam(FOnServersUpdated, const TSet<FServer>& Servers);`
