# Programs / UninstallHelper

- module root: `Source/Programs/UninstallHelper`
- headers: 1; symbols: 12
- symbol kinds: delegate=1, enum=1, enumerator=8, namespace=1, prototype=1

### `Source/Programs/UninstallHelper/Private/UninstallHelper.h` (Private)


#### enum `UninstallHelper::EReturnCode`  
`enum class EReturnCode : int32`  
_L11-22_
- L13 _public enumerator_ `Success = 0`
- L14 _public enumerator_ `UnknownError`
- L15 _public enumerator_ `ArgumentError`
- L16 _public enumerator_ `UnknownAppName`
- L17 _public enumerator_ `InvalidInstallDir`
- L18 _public enumerator_ `ExecActionFailed`
- L19 _public enumerator_ `DiskOperationFailed`
- L21 _public enumerator_ `Crash = 255`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogUninstallHelper, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUninstallHelper, Log, All);`
- L9 _namespace_ `namespace UninstallHelper`
