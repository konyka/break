# Runtime / UnixCommonStartup

- module root: `Source/Runtime/Unix/UnixCommonStartup`
- headers: 1; symbols: 1
- symbol kinds: prototype=1
- PrivateDependencyModuleNames: ApplicationCore, Core, Projects, Slate, SourceControl
- PublicDependencyModuleNames: Engine

### `Source/Runtime/Unix/UnixCommonStartup/Public/UnixCommonStartup.h` (Public)


#### Free symbols / members of external scopes

- L16 _prototype_ `int CommonUnixMain(int argc, char *argv[], int (*RealMain)(const TCHAR * CommandLine), void (*AppExitCallback)() = nullptr);` — @brief CommonUnixMain - executes common startup code for Unix programs/engine @param argc - number of arguments in argv[] @param argv - array of arguments @param RealMain - the next main routine to call in chain @param AppExitCallback - workaround for Launch module that needs to call FEngineLoop::AppExit() at certain point @return error code to return to the OS
