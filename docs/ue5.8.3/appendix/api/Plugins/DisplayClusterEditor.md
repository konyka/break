# Plugins / DisplayClusterEditor

- module root: `Plugins/Runtime/nDisplay/Source/DisplayClusterEditor`
- headers: 5; symbols: 34
- symbol kinds: class=4, delegate=2, member=11, prototype=17
- PrivateDependencyModuleNames: Core, CoreUObject, DisplayCluster, DisplayClusterConfiguration, Engine, EngineSettings, EnhancedInput, UnrealEd

### `Plugins/Runtime/nDisplay/Source/DisplayClusterEditor/Private/DisplayClusterEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterEditor, Log, All);` — Plugin-wide log categories
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterEditor, Log, All);` — Plugin-wide log categories
- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterEditorEngine, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDisplayClusterEditorEngine, Log, All);`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterEditor/Private/DisplayClusterEditorModule.h` (Private)


#### class `FDisplayClusterEditorModule`  
`class FDisplayClusterEditorModule : public IDisplayClusterEditor`  
_L11-30_
- inherits: `IDisplayClusterEditor`
- desc: Display Cluster editor module
- L15 _public prototype_ `FDisplayClusterEditorModule();`
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _protected prototype_ `void RegisterSettings();`
- L24 _protected prototype_ `void UnregisterSettings();`
- L27 _private member_ `const FName Container;`
- L28 _private member_ `const FName Category;`
- L29 _private member_ `const FName Section;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterEditor/Private/Settings/DisplayClusterEditorSettings.h` (Private)


#### class `UDisplayClusterEditorSettings`  
`class UDisplayClusterEditorSettings : public UObject`  
_L14-30_
- reflection: `UCLASS(config = Engine, defaultconfig)`
- inherits: `UObject`
- desc: Implements nDisplay settings
- L19 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L25 _protected member_ `bool bEnabled;` — `UPROPERTY(config, EditAnywhere, Category = Main, meta = (ToolTip = "When enabled, automatically overrides some engine classes and settings", ConfigRestartRequired = true))` — Used to set or reset additional nDisplay settings
- L29 _protected member_ `bool bClusterReplicationEnabled;` — `UPROPERTY(config, EditAnywhere, Category = Main, meta = (ToolTip = "When enabled, replaces the original NetDriver to DisplayClusterNetDriver, original NetConnection to DisplayClusterNetDriver", ConfigRestartRequired = true))` — When enabled, replaces the original NetDriver to DisplayClusterNetDriver, original NetConnection to DisplayClusterNetDriver

### `Plugins/Runtime/nDisplay/Source/DisplayClusterEditor/Public/DisplayClusterEditorEngine.h` (Public)


#### class `UDisplayClusterEditorEngine`  
`class UDisplayClusterEditorEngine : public UUnrealEdEngine`  
_L17-48_
- reflection: `UCLASS()`
- inherits: `UUnrealEdEngine`
- desc: Extended editor engine
- L23 _public prototype_ `virtual void Init(IEngineLoop* InEngineLoop) override;`
- L24 _public prototype_ `virtual void PreExit() override;`
- L25 _public prototype_ `virtual void StartPlayInEditorSession(FRequestPlaySessionParams& InRequestParams) override;`
- L26 _public prototype_ `virtual bool LoadMap(FWorldContext& WorldContext, FURL URL, class UPendingNetGame* Pending, FString& Error) override;`
- L27 _public prototype_ `virtual void Tick(float DeltaSeconds, bool bIdleMode) override;`
- L30 _private prototype_ `ADisplayClusterRootActor* FindDisplayClusterRootActor(UWorld* InWorld);`
- L33 _private member_ `IPDisplayCluster* DisplayClusterModule = nullptr;`
- L37 _private member_ `FDelegateHandle BeginPIEDelegate;`
- L38 _private prototype_ `void OnBeginPIE(const bool bSimulate);`
- L41 _private member_ `FDelegateHandle EndPIEDelegate;`
- L42 _private prototype_ `void OnEndPIE(const bool bSimulate);`
- L44 _private member_ `bool bIsActivePIE = false;`
- L45 _private member_ `bool bIsNDisplayPIE = false;`
- L47 _private member_ `uint64 SessionFrameCounter = 0;`

### `Plugins/Runtime/nDisplay/Source/DisplayClusterEditor/Public/IDisplayClusterEditor.h` (Public)


#### class `IDisplayClusterEditor`  
`class IDisplayClusterEditor : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- desc: Display Cluster editor module interface
- L16 _public prototype_ `virtual ~IDisplayClusterEditor() = default;`
