# Runtime / PortalProxies

- module root: `Source/Runtime/Portal/Proxies`
- headers: 4; symbols: 12
- symbol kinds: class=4, function=3, member=1, prototype=4
- DynamicallyLoadedModuleNames: Messaging, MessagingRpc
- PrivateDependencyModuleNames: CoreUObject, PortalMessages
- PrivateIncludePathModuleNames: MessagingRpc, PortalServices
- PublicDependencyModuleNames: Core

### `Source/Runtime/Portal/Proxies/Private/Account/PortalUserLoginProxy.h` (Private)


#### class `FPortalUserLoginProxyFactory`  
`class FPortalUserLoginProxyFactory`  
_L8-12_
- L11 _public prototype_ `static TSharedRef<IPortalService> Create(const TSharedRef<IMessageRpcClient>& RpcClient);`

### `Source/Runtime/Portal/Proxies/Private/Account/PortalUserProxy.h` (Private)


#### class `FPortalUserProxyFactory`  
`class FPortalUserProxyFactory`  
_L8-12_
- L11 _public prototype_ `static TSharedRef<IPortalService> Create(const TSharedRef<IMessageRpcClient>& RpcClient);`

### `Source/Runtime/Portal/Proxies/Private/Application/PortalApplicationWindowProxy.h` (Private)


#### class `FPortalApplicationWindowProxyFactory`  
`class FPortalApplicationWindowProxyFactory`  
_L8-12_
- L11 _public prototype_ `static TSharedRef<IPortalService> Create(const TSharedRef<IMessageRpcClient>& RpcClient);`

### `Source/Runtime/Portal/Proxies/Private/Package/PortalPackageInstallerProxy.h` (Private)


#### class `FPortalPackageInstallerProxy`  
`class FPortalPackageInstallerProxy : public IPortalPackageInstaller`  
_L10-36_
- inherits: `IPortalPackageInstaller`
- L15 _public function_ `FPortalPackageInstallerProxy(const TSharedRef<IMessageRpcClient>& InRpc) : RpcClient(InRpc)`
- L19 _public prototype_ `virtual ~FPortalPackageInstallerProxy() = default;`
- L23 _public function_ `virtual TAsyncResult<bool> Install(const FString& Path, const FString& AppName, const FString& BuildLabel) override`
- L28 _public function_ `virtual TAsyncResult<bool> Uninstall(const FString& Path, const FString& AppName, const FString& BuildLabel, bool RemoveUserFiles) override`
- L35 _private member_ `TSharedRef<IMessageRpcClient> RpcClient;`
