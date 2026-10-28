# Programs / UnrealInsights

- module root: `Source/Programs/UnrealInsights`
- headers: 2; symbols: 5
- symbol kinds: class=1, prototype=4
- DynamicallyLoadedModuleNames: SlateReflector
- PrivateDependencyModuleNames: AppFramework, ApplicationCore, Core, CoreUObject, LiveCoding, NetworkFile, OutputLog, Projects, SessionFrontend, Slate, SlateCore, SourceCodeAccess, StandaloneRenderer, StreamingFile, TargetDeviceServices, TargetPlatform, TcpMessaging, TraceInsights, TraceInsightsCore, TraceInsightsFrontend, UdpMessaging, UnixCommonStartup, VisualStudioSourceCodeAccess, XCodeSourceCodeAccess
- PrivateIncludePathModuleNames: SlateReflector
- PublicIncludePathModuleNames: Launch

### `Source/Programs/UnrealInsights/Private/UnrealInsightsMain.h` (Private)


#### Free symbols / members of external scopes

- L13 _prototype_ `int32 UnrealInsightsMain(const TCHAR* CommandLine);` — The application's main function. @param CommandLine The application command line. @return Application's exit value.

### `Source/Programs/UnrealInsights/Private/UserInterfaceCommand.h` (Private)


#### class `FUserInterfaceCommand`  
`class FUserInterfaceCommand`  
_L7-23_
- L11 _public prototype_ `static void Run(bool bFrontendMode, const FString& TraceFileToOpen);` — Executes the command.
- L17 _protected prototype_ `static void InitializeSlateApplication(bool bFrontendMode, const FString& TraceFileToOpen);` — Initializes the Slate application.
- L22 _protected prototype_ `static void ShutdownSlateApplication();` — Shuts down the Slate application.
