# Plugins / ComputeFrameworkEditor

- module root: `Plugins/Runtime/ComputeFramework/Source/ComputeFrameworkEditor`
- headers: 3; symbols: 9
- symbol kinds: class=3, function=2, member=1, prototype=3
- PrivateDependencyModuleNames: ComputeFramework, Core, Engine, UnrealEd

### `Plugins/Runtime/ComputeFramework/Source/ComputeFrameworkEditor/Private/ComputeFramework/ComputeFrameworkCompilationTick.h` (Private)


#### class `FComputeFrameworkCompilationTick`  
`class FComputeFrameworkCompilationTick : public FTickableEditorObject`  
_L8-22_
- inherits: `FTickableEditorObject`
- desc: Editor tickable object used to tick the shader compilation process.
- L11 _public function_ `ETickableTickType GetTickableTickType() const override`
- L16 _public function_ `TStatId GetStatId() const override`
- L21 _public prototype_ `void Tick(float DeltaSeconds) override;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFrameworkEditor/Private/ComputeFramework/ComputeFrameworkEditorModule.h` (Private)


#### class `FComputeFrameworkEditorModule`  
`class FComputeFrameworkEditorModule : public IComputeFrameworkEditorModule`  
_L7-16_
- inherits: `IComputeFrameworkEditorModule`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`
- L15 _private member_ `TUniquePtr<class FComputeFrameworkCompilationTick> TickObject;`

### `Plugins/Runtime/ComputeFramework/Source/ComputeFrameworkEditor/Public/ComputeFramework/IComputeFrameworkEditorModule.h` (Public)


#### class `IComputeFrameworkEditorModule`  
`class IComputeFrameworkEditorModule : public IModuleInterface`  
_L8-11_
- inherits: `IModuleInterface`
