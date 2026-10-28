# Plugins / LiveCodingToolset

- module root: `Plugins/Experimental/Toolsets/LiveCodingToolset/Source/LiveCodingToolset`
- headers: 3; symbols: 10
- symbol kinds: class=3, member=1, prototype=6
- PrivateDependencyModuleNames: Core, CoreUObject, EditorSubsystem, Engine, LiveCoding, UnrealEd
- PublicDependencyModuleNames: ToolsetRegistry

### `Plugins/Experimental/Toolsets/LiveCodingToolset/Source/LiveCodingToolset/Public/LiveCodingToolset.h` (Public)


#### class `ULiveCodingToolset`  
`class ULiveCodingToolset : public UToolsetDefinition`  
_L17-28_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UToolsetDefinition`
- desc: Live Coding compile toolset. Exposes an MCP tool that triggers a Live Coding compile from the running editor and waits for the result, returning the compile status together with any captured LogLiveCoding output and UBT compiler diagnostics.
- L27 _public prototype_ `static FString CompileLiveCoding();` — `UFUNCTION(meta = (AICallable), Category = "LiveCodingToolset")` — Triggers a Live Coding compile and waits for the result. Live Coding must be enabled in Editor Preferences. @return The compile result status followed by any compiler output (errors, warnings, etc).

### `Plugins/Experimental/Toolsets/LiveCodingToolset/Source/LiveCodingToolset/Public/LiveCodingToolsetModule.h` (Public)


#### class `FLiveCodingToolsetModule`  
`class FLiveCodingToolsetModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;`
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/Toolsets/LiveCodingToolset/Source/LiveCodingToolset/Public/LiveCodingToolsetSubsystem.h` (Public)


#### class `ULiveCodingToolsetSubsystem`  
`class ULiveCodingToolsetSubsystem : public UEditorSubsystem`  
_L16-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: Registers the LiveCodingToolset with UToolsetRegistry for the lifetime of the editor. Registration can be toggled at runtime via the LiveCodingToolset.Enable CVar.
- L22 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L24 _public prototype_ `virtual void Deinitialize() override;`
- L27 _public prototype_ `void SetToolsetEnabled(bool bEnabled);` — Register or unregister the toolset with UToolsetRegistry at runtime.
- L31 _private member_ `bool bToolsetRegistered = false;`
