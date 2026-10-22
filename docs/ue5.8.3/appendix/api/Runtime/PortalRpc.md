# Runtime / PortalRpc

- module root: `Source/Runtime/Portal/Rpc`
- headers: 9; symbols: 36
- symbol kinds: class=7, delegate=1, function=4, macro=2, member=5, prototype=15, struct=2
- DynamicallyLoadedModuleNames: 
- PrivateIncludePathModuleNames: Messaging, MessagingCommon
- PublicDependencyModuleNames: Core, CoreUObject, MessagingRpc

### `Source/Runtime/Portal/Rpc/Private/PortalRpcDefines.h` (Private)


#### Free symbols / members of external scopes

- L10 _macro_ `#define PORTAL_RPC_LOCATE_INTERVAL 5.0` — Defines interval at which the Portal RPC server is being located (in seconds).
- L13 _macro_ `#define PORTAL_RPC_LOCATE_TIMEOUT 15.0` — Defines the time after which Portal RPC servers time out (in seconds).

### `Source/Runtime/Portal/Rpc/Private/PortalRpcLocator.h` (Private)


#### class `FPortalRpcLocatorFactory`  
`class FPortalRpcLocatorFactory`  
_L8-12_
- L11 _public prototype_ `static TSharedRef<IPortalRpcLocator> Create();`

### `Source/Runtime/Portal/Rpc/Private/PortalRpcMessages.h` (Private)


#### struct `FPortalRpcLocateServer`  
`struct FPortalRpcLocateServer`  
_L12-42_
- reflection: `USTRUCT()`
- L18 _public member_ `FGuid ProductId;` — `UPROPERTY(EditAnywhere, Category="Message")` — The product's unique identifier.
- L22 _public member_ `FString ProductVersion;` — `UPROPERTY(EditAnywhere, Category="Message")` — The product's version string.
- L26 _public member_ `FString HostMacAddress;` — `UPROPERTY(EditAnywhere, Category = "Message")` — The mac address of the host.
- L30 _public member_ `FString HostUserId;` — `UPROPERTY(EditAnywhere, Category = "Message")` — The user identification for the host.
- L33 _public function_ `FPortalRpcLocateServer()` — Default constructor.
- L36 _public function_ `FPortalRpcLocateServer(const FGuid& InProductId, const FString& InProductVersion, const FString& InHostMacAddress, const FString& InHostUserId) : ProductId(InProductId) , ProductVersion(InProductVersion) , HostMacAddress(InHostMacAddress) , HostUserId(InHostUserId)` — Create and initialize a new instance.

#### struct `FPortalRpcServer`  
`struct FPortalRpcServer`  
_L46-61_
- reflection: `USTRUCT()`
- L52 _public member_ `FString ServerAddress;` — `UPROPERTY(EditAnywhere, Category="Message")` — The RPC server's message address as a string.
- L55 _public function_ `FPortalRpcServer()` — Default constructor.
- L58 _public function_ `FPortalRpcServer(const FString& InServerAddress) : ServerAddress(InServerAddress)` — Create and initialize a new instance.

### `Source/Runtime/Portal/Rpc/Private/PortalRpcResponder.h` (Private)


#### class `FPortalRpcResponderFactory`  
`class FPortalRpcResponderFactory`  
_L8-12_
- L11 _public prototype_ `static TSharedRef<IPortalRpcResponder> Create();`

### `Source/Runtime/Portal/Rpc/Private/PortalRpcServer.h` (Private)


#### class `FPortalRpcServerFactory`  
`class FPortalRpcServerFactory`  
_L8-12_
- L11 _public prototype_ `static TSharedRef<IPortalRpcServer> Create();`

### `Source/Runtime/Portal/Rpc/Public/IPortalRpcLocator.h` (Public)


#### class `IPortalRpcLocator`  
`class IPortalRpcLocator`  
_L12-46_
- desc: Interface for Portal RPC server locators.
- L22 _public prototype_ `virtual const FMessageAddress& GetServerAddress() const = 0;` — Get the address of the located Portal RPC server. @return The RPC server's message address, or invalid if no server found. @see OnServerLocated, OnServerLost
- L32 _public prototype_ `virtual FSimpleDelegate& OnServerLocated() = 0;` — Get a delegate that is executed when an RPC server has been located. @return The delegate. @see GetServerAddress, OnServerLost
- L40 _public prototype_ `virtual FSimpleDelegate& OnServerLost() = 0;` — Get a delegate that is executed when an RPC server has been located. @return The delegate. @see GetServerAddress, OnServerLocated
- L45 _public prototype_ `virtual ~IPortalRpcLocator() = default;` — Virtual destructor.

### `Source/Runtime/Portal/Rpc/Public/IPortalRpcModule.h` (Public)


#### class `IPortalRpcModule`  
`class IPortalRpcModule : public IModuleInterface`  
_L14-22_
- inherits: `IModuleInterface`
- desc: Interface for the PortalRpc module.
- L19 _public prototype_ `virtual TSharedRef<IPortalRpcLocator> CreateLocator() = 0;`
- L20 _public prototype_ `virtual TSharedRef<IPortalRpcResponder> CreateResponder() = 0;`
- L21 _public prototype_ `virtual TSharedRef<IPortalRpcServer> CreateServer() = 0;`

### `Source/Runtime/Portal/Rpc/Public/IPortalRpcResponder.h` (Public)


#### class `IPortalRpcResponder`  
`class IPortalRpcResponder`  
_L14-25_
- desc: Interface for Portal RPC responders.
- L19 _public prototype_ `virtual FOnPortalRpcLookup& OnLookup() = 0;` — Get a delegate that is executed when a look-up for an RPC server occurs.
- L24 _public prototype_ `virtual ~IPortalRpcResponder() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IPortalRpcServer>, FOnPortalRpcLookup, const FString& ) class IPortalRpcResponder { public: virtual FOnPortalRpcLookup& OnLookup() = 0; public: virtual ~IPortalRpcResponder() = default; };`

### `Source/Runtime/Portal/Rpc/Public/IPortalRpcServer.h` (Public)


#### class `IPortalRpcServer`  
`class IPortalRpcServer`  
_L12-28_
- desc: Interface for Portal RPC server
- L20 _public prototype_ `virtual void ConnectTo(const FMessageAddress& Address) const = 0;` — Sends a FPortalRpcServer response to the specified address, effectively allowing the two services to now communicate with each other directly.
- L22 _public prototype_ `virtual IMessageRpcServer* GetMessageServer() = 0;`
- L27 _public prototype_ `virtual ~IPortalRpcServer() = default;` — Virtual destructor.
