# Programs / TestPAL

- module root: `Source/Programs/TestPAL`
- headers: 3; symbols: 11
- symbol kinds: class=1, delegate=1, macro=1, member=3, prototype=5
- PrivateDependencyModuleNames: ApplicationCore, Core, DirectoryWatcher, Projects, SDL3
- PublicIncludePathModuleNames: Launch

### `Source/Programs/TestPAL/Private/Parent.h` (Private)


#### class `FParent`  
`class FParent`  
_L8-28_
- L11 _private member_ `TArray< FProcHandle > Children;` — Children to be controlled
- L14 _private member_ `int NumTotalChildren;` — Total children to spawn
- L17 _private member_ `int MaxChildrenAtOnce;` — Max children at once
- L20 _private prototype_ `FProcHandle Launch(bool bDetached = false);` — Launches the child, returns the launched process handle.
- L25 _public prototype_ `void Run();` — Spawns the children one by one
- L27 _public prototype_ `FParent(int InNumTotalChildren, int InMaxChildrenAtOnce);`

### `Source/Programs/TestPAL/Private/TestDirectoryWatcher.h` (Private)


#### Free symbols / members of external scopes

- L7 _macro_ `#define USE_DIRECTORY_WATCHER (PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX)`
- L9 _prototype_ `int32 DirectoryWatcherTest(const TCHAR* CommandLine);`

### `Source/Programs/TestPAL/Private/TestPALLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogTestPAL, Verbose, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogTestPAL, Verbose, All);`
