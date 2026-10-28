# Runtime / CEF3Utils

- module root: `Source/Runtime/CEF3Utils`
- headers: 2; symbols: 8
- symbol kinds: delegate=1, namespace=1, prototype=6
- PrivateDependencyModuleNames: Core

### `Source/Runtime/CEF3Utils/Private/CEF3UtilsLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCEF3Utils, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCEF3Utils, Log, All);`

### `Source/Runtime/CEF3Utils/Public/CEF3Utils.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace CEF3Utils`
- L15 _prototype_ `bool LoadCEF3Modules(bool bIsMainApp);` (scope `CEF3Utils`) — Load the required modules for CEF3, returns false if we fail to load the cef library
- L20 _prototype_ `void UnloadCEF3Modules();` (scope `CEF3Utils`) — Unload the required modules for CEF3
- L26 _prototype_ `void* GetCEF3ModuleHandle();` (scope `CEF3Utils`) — Get the module (dll) handle to the loaded CEF3 module, will be null if not loaded
- L32 _prototype_ `FString GetCEF3ModulePath();` (scope `CEF3Utils`) — Get the module loaded path
- L38 _prototype_ `void BackupCEF3Logfile(const FString& LogFilePath);` (scope `CEF3Utils`) — Move the current cef3.log file to a backup file, so CEF makes a new log when it starts up. This backup file is then cleaned up by the logic in FMaintenance::DeleteOldLogs()
