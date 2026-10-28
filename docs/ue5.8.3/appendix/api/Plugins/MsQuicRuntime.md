# Plugins / MsQuicRuntime

- module root: `Plugins/Runtime/MsQuic/Source`
- headers: 2; symbols: 11
- symbol kinds: class=1, delegate=1, macro=1, member=3, prototype=5
- PublicDependencyModuleNames: Core, MsQuic

### `Plugins/Runtime/MsQuic/Source/Private/MsQuicRuntimePrivate.h` (Private)


#### Free symbols / members of external scopes

- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMsQuicRuntime, Display, All);` — Declares a log category for this module.
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMsQuicRuntime, Display, All);` — Declares a log category for this module.

### `Plugins/Runtime/MsQuic/Source/Public/MsQuicRuntimeModule.h` (Public)


#### class `FMsQuicRuntimeModule`  
`class FMsQuicRuntimeModule : public IModuleInterface`  
_L11-52_
- inherits: `IModuleInterface`
- L20 _public prototype_ `static bool InitRuntime();` — Initializes the runtime by loading the MsQuic DLL if it's not loaded already.
- L26 _public prototype_ `virtual void ShutdownModule() override;`
- L33 _private prototype_ `static bool LoadMsQuicDll();` — Load the appropriate MsQuic DLL/So for this platform.
- L38 _private prototype_ `static void FreeMsQuicDll();` — Frees the DLL handle.
- L43 _private member_ `static inline void* MsQuicLibraryHandle = nullptr;` — Holds the MsQuic library dll handle.
- L46 _private member_ `static inline const FString MSQUIC_VERSION = "v2` — Defines the MsQuic version to be used.
- L49 _private member_ `static inline const FString MSQUIC_BINARIES_PATH = "Binaries/ThirdParty` — Defines the MsQuic binaries path.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API MSQUICRUNTIME_API`
