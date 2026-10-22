# Plugins / GPUReshape

- module root: `Plugins/Developer/GPUReshape/Source/GPUReshape`
- headers: 3; symbols: 28
- symbol kinds: class=3, delegate=1, function=3, member=8, prototype=13
- DynamicallyLoadedModuleNames: LevelEditor

### `Plugins/Developer/GPUReshape/Source/GPUReshape/Private/GPUReshapeCommands.h` (Private)


#### class `FGPUReshapeCommands`  
`class FGPUReshapeCommands : public TCommands<FGPUReshapeCommands>`  
_L12-24_
- inherits: `TCommands<FGPUReshapeCommands>`
- L15 _public function_ `FGPUReshapeCommands() : TCommands(TEXT("GPUReshape"), NSLOCTEXT("Contexts", "GPUReshape", "GPUReshape Plugin"), NAME_None, FGPUReshapeStyle::Get()->GetStyleSetName())`
- L21 _public prototype_ `virtual void RegisterCommands() override;` — TCommands overrides
- L23 _public member_ `TSharedPtr<class FUICommandInfo> OpenApp;`

### `Plugins/Developer/GPUReshape/Source/GPUReshape/Private/GPUReshapeModule.h` (Private)


#### class `FGPUReshapeModule`  
`class FGPUReshapeModule : public IModuleInterface`  
_L11-71_
- inherits: `IModuleInterface`
- L15 _public prototype_ `void OpenOrSwitchToApp();` — Open, or switch to if present, the app
- L18 _public prototype_ `void SwitchToApp();` — Switch to the already open app
- L21 _public function_ `uint32 GetAppGetProcessID() const` — Get the current process id
- L27 _public function_ `bool IsInitialized() const` — Is GPU Reshape initialized correctly?
- L33 _protected prototype_ `virtual void StartupModule() override;` — protected:   IModuleInterface
- L34 _protected prototype_ `virtual void ShutdownModule() override;`
- L38 _private prototype_ `bool FindAndInstallLoader();` — Find the appropriate loader and install it
- L41 _private prototype_ `bool InstallLoader(void* Handle);` — Install the loader onto the current process
- L44 _private prototype_ `void CacheLoaderReservedToken(void* Handle);` — Cache the reserved token for attaching
- L47 _private prototype_ `void OnPostEngineInit();` — Invoked for editor extensions
- L51 _private member_ `TUniquePtr<class FAutoConsoleCommand> OpenAppCommand;` — Commands
- L54 _private member_ `FString GPUReshapePath;` — Bin path for tooling
- L57 _private member_ `FString ReservedToken;` — Cached token for attaching
- L60 _private member_ `FProcHandle AppProcHandle;` — Current process handle
- L63 _private member_ `uint32 AppProcessID = 0;` — Current process id
- L66 _private member_ `bool bBackendInitialized = false;` — Everything set up right?
- L69 _private member_ `TSharedPtr<class FGPUReshapeEditorExtension> EditorExtension;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGPUReshape, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGPUReshape, Log, All);`

### `Plugins/Developer/GPUReshape/Source/GPUReshape/Private/GPUReshapeStyle.h` (Private)


#### class `FGPUReshapeStyle`  
`class FGPUReshapeStyle`  
_L9-18_
- L13 _public prototype_ `static void Initialize();` — Setup
- L14 _public prototype_ `static void Shutdown();`
- L17 _public prototype_ `static TSharedPtr<ISlateStyle> Get();` — Get the shared style
