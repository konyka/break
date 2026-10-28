# Plugins / StallLogSubsystem

- module root: `Plugins/Experimental/EditorPerformance/Source/StallLogSubsystem`
- headers: 1; symbols: 11
- symbol kinds: class=1, macro=1, member=3, prototype=6
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, EditorSubsystem, Engine, InputCore, MessageLog, Slate, SlateCore, ToolMenus, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/EditorPerformance/Source/StallLogSubsystem/Public/StallLogSubsystem.h` (Public)


#### class `UStallLogSubsystem`  
`class UStallLogSubsystem : public UEditorSubsystem`  
_L26-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Subsystem that provides feedback on stall detection
- L31 _public prototype_ `virtual bool ShouldCreateSubsystem(UObject* Outer) const override;`
- L32 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L33 _public prototype_ `virtual void Deinitialize() override;`
- L35 _public prototype_ `TSharedRef<SWidget> CreateStallLogPanel();`
- L38 _private prototype_ `void RegisterStallDetectedDelegates();`
- L39 _private prototype_ `void UnregisterStallDetectedDelegates();`
- L43 _private member_ `FDelegateHandle OnStallDetectedDelegate;`
- L44 _private member_ `FDelegateHandle OnStallCompletedDelegate;`
- L45 _private member_ `TSharedPtr<FStallLogHistory, ESPMode::ThreadSafe> StallLogHistory;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API STALLLOGSUBSYSTEM_API`
