# Programs / UnrealFrontend

- module root: `Source/Programs/UnrealFrontend`
- headers: 5; symbols: 18
- symbol kinds: class=4, delegate=1, function=1, member=1, prototype=11
- DynamicallyLoadedModuleNames: SlateReflector
- PrivateDependencyModuleNames: ApplicationCore, AutomationController, Core, CoreUObject, DeviceManager, DirectoryWatcher, LauncherServices, LegacyProjectLauncher, Messaging, Networking, OutputLog, Profiler, ProfilerClient, Projects, SessionFrontend, SessionServices, Slate, SlateCore, Sockets, SourceCodeAccess, StandaloneRenderer, TargetDeviceServices, TargetPlatform, TcpMessaging, UdpMessaging, UnixCommonStartup, VisualStudioSourceCodeAccess, XCodeSourceCodeAccess
- PrivateIncludePathModuleNames: Messaging, SlateReflector
- PublicIncludePathModuleNames: Launch

### `Source/Programs/UnrealFrontend/Private/Commands/ExecuteConsoleCommand.h` (Private)


#### class `FExecuteConsoleCommand`  
`class FExecuteConsoleCommand`  
_L11-20_
- L19 _public prototype_ `void Run(const FString& Params);` — Executes the command. Use '-Command=' command line argument to specify the console command. Use '-InstanceId=' command line argument to specify the target instance id.

### `Source/Programs/UnrealFrontend/Private/Commands/LaunchFromProfileCommand.h` (Private)


#### class `FLaunchFromProfileCommand`  
`class FLaunchFromProfileCommand`  
_L7-29_
- L15 _public prototype_ `void Run(const FString& Params);` — Executes the command. Use '-PROFILENAME=' command line argument to specify the name of a profile to use for this command.
- L22 _protected prototype_ `static void MessageReceived(const FString& InMessage);` — Logs out the messages from the launcher worker.  Used in a delegate.
- L24 _protected prototype_ `void LaunchCompleted(bool Outcome, double ExecutionTime, int32 ReturnCode);`
- L25 _protected prototype_ `void LaunchCanceled(double ExecutionTime);`
- L28 _private member_ `bool bTestRunning;`

### `Source/Programs/UnrealFrontend/Private/Commands/StatsConvertCommand.h` (Private)


#### class `FStatsConvertCommand`  
`class FStatsConvertCommand`  
_L11-26_
- L16 _public function_ `static void Run()` — Executes the command.
- L24 _protected prototype_ `void InternalRun();`

### `Source/Programs/UnrealFrontend/Private/Commands/UserInterfaceCommand.h` (Private)


#### class `FUserInterfaceCommand`  
`class FUserInterfaceCommand`  
_L7-29_
- L12 _public prototype_ `static void Run( );` — Executes the command.
- L21 _protected prototype_ `static void InitializeSlateApplication( const FString& LayoutIni );` — Initializes the Slate application. @param LayoutInit The path to the layout configuration file.
- L28 _protected prototype_ `static void ShutdownSlateApplication( const FString& LayoutIni );` — Shuts down the Slate application. @param LayoutInit The path to the layout configuration file.

### `Source/Programs/UnrealFrontend/Private/UnrealFrontendMain.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUFECommands, All, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUFECommands, All, All);`
- L15 _prototype_ `int32 UnrealFrontendMain( const TCHAR* CommandLine );` — The application's main function. @param CommandLine The application command line. @return Application's exit value.
