# Programs / UnrealLaunchDaemon

- module root: `Source/Programs/IOS/UnrealLaunchDaemon`
- headers: 4; symbols: 11
- symbol kinds: class=1, delegate=1, member=2, prototype=7
- PrivateDependencyModuleNames: ApplicationCore, Core, LaunchDaemonMessages, Messaging, NetworkFile, Projects, Slate, SlateCore, StandaloneRenderer, StreamingFile, UdpMessaging
- PrivateIncludePathModuleNames: Messaging
- PublicIncludePathModuleNames: Launch

### `Source/Programs/IOS/UnrealLaunchDaemon/Private/IOS/IOSLaunchDaemonView.h` (Private)
_(no declarations extracted)_

### `Source/Programs/IOS/UnrealLaunchDaemon/Private/LaunchDaemonMessageHandler.h` (Private)


#### class `FLaunchDaemonMessageHandler`  
`class FLaunchDaemonMessageHandler`  
_L14-29_
- L18 _public prototype_ `void Init();`
- L19 _public prototype_ `void Shutdown();`
- L20 _public prototype_ `void Launch(const FString& LaunchURL);`
- L24 _private prototype_ `void HandlePingMessage(const FIOSLaunchDaemonPing& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L25 _private prototype_ `void HandleLaunchRequest(const FIOSLaunchDaemonLaunchApp& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);`
- L27 _private member_ `TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> MessageEndpoint;`
- L28 _private member_ `FString AppId;`

### `Source/Programs/IOS/UnrealLaunchDaemon/Private/UnrealLaunchDaemon.h` (Private)
_(no declarations extracted)_

### `Source/Programs/IOS/UnrealLaunchDaemon/Private/UnrealLaunchDaemonApp.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLaunchDaemon, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLaunchDaemon, Log, All);`
- L13 _prototype_ `void RunUnrealLaunchDaemon(const TCHAR* Commandline);` — Run the UnrealLaunchDaemon
