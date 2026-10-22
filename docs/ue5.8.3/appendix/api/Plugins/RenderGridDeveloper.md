# Plugins / RenderGridDeveloper

- module root: `Plugins/Experimental/RenderGrid/Source/RenderGridDeveloper`
- headers: 6; symbols: 54
- symbol kinds: class=6, delegate=2, function=13, member=1, namespace=7, prototype=25
- PrivateDependencyModuleNames: BlueprintGraph, Engine, GraphEditor, RenderGrid, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Blutility, Core, CoreUObject, Engine, KismetCompiler

### `Plugins/Experimental/RenderGrid/Source/RenderGridDeveloper/Private/RenderGridDeveloperModule.h` (Private)


#### class `UE::RenderGrid::Private::FRenderGridDeveloperModule`  
`class FRenderGridDeveloperModule : public IRenderGridDeveloperModule`  
_L14-21_
- inherits: `IRenderGridDeveloperModule`
- desc: The implementation of the IRenderGridDeveloperModule interface.
- L18 _public prototype_ `virtual void StartupModule() override;`
- L19 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)
- L9 _namespace_ `namespace Private` (scope `UE::RenderGrid`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridDeveloper/Public/Blueprints/RenderGridBlueprint.h` (Public)


#### class `URenderGridBlueprint`  
`class URenderGridBlueprint : public UEditorUtilityBlueprint`  
_L17-75_
- reflection: `UCLASS(BlueprintType, Meta=(IgnoreClassThumbnail, DontUseGenericSpawnObject="true"))`
- inherits: `UEditorUtilityBlueprint`
- desc: A UBlueprint child class for the RenderGrid modules. Required in order for a RenderGrid to be able to have a blueprint graph.
- L22 _public prototype_ `URenderGridBlueprint();`
- L25 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override`
- L26 _public function_ `virtual bool AlwaysCompileOnLoad() const override`
- L27 _public function_ `virtual bool IsValidForBytecodeOnlyRecompile() const override`
- L28 _public function_ `virtual bool SupportsGlobalVariables() const override`
- L29 _public function_ `virtual bool SupportsLocalVariables() const override`
- L30 _public function_ `virtual bool SupportsFunctions() const override`
- L31 _public function_ `virtual bool SupportsMacros() const override`
- L32 _public function_ `virtual bool SupportsDelegates() const override`
- L33 _public function_ `virtual bool SupportsEventGraphs() const override`
- L34 _public function_ `virtual bool SupportsAnimLayers() const override`
- L35 _public function_ `virtual bool ShouldBeMarkedDirtyUponTransaction() const override`
- L36 _public prototype_ `virtual UClass* GetBlueprintClass() const override;`
- L37 _public prototype_ `virtual void PostLoad() override;`
- L41 _private prototype_ `DECLARE_DELEGATE_OneParam(FRenderGridBlueprintRunOnInstancesCallback, URenderGrid* );`
- L42 _private prototype_ `void RunOnInstances(const FRenderGridBlueprintRunOnInstancesCallback& Callback);`
- L45 _public prototype_ `void Load();`
- L46 _public prototype_ `void Save();`
- L48 _public prototype_ `void PropagateJobsToInstances();`
- L49 _public prototype_ `void PropagateAllPropertiesExceptJobsToInstances();`
- L50 _public prototype_ `void PropagateAllPropertiesToInstances();`
- L52 _public prototype_ `void PropagateJobsToAsset(URenderGrid* Instance);`
- L53 _public prototype_ `void PropagateAllPropertiesExceptJobsToAsset(URenderGrid* Instance);`
- L54 _public prototype_ `void PropagateAllPropertiesToAsset(URenderGrid* Instance);`
- L59 _public function_ `URenderGrid* GetRenderGrid() const` — `UFUNCTION(BlueprintPure, Category="Render Grid")` — Returns the RenderGrid reference that this RenderGrid asset contains. This is simply the data representation of the render grid, meaning that it won't contain a blueprint graph or any user code.
- L63 _public prototype_ `URenderGrid* GetRenderGridWithBlueprintGraph() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")` — Returns the RenderGrid reference that this RenderGrid asset contains. This will be the subclass of the blueprint class, meaning it will contain a blueprint graph.
- L67 _public prototype_ `URenderGrid* GetRenderGridClassDefaultObject() const;` — `UFUNCTION(BlueprintPure, Category="Render Grid")` — Returns the RenderGrid reference that this RenderGrid asset contains. This will be the default object of the subclass of the blueprint class, meaning it will contain a blueprint graph.
- L70 _private prototype_ `virtual void OnPostVariablesChange(UBlueprint* InBlueprint);`
- L74 _private member_ `TObjectPtr<URenderGrid> RenderGrid;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L41 _delegate_ `DECLARE_DELEGATE_OneParam(FRenderGridBlueprintRunOnInstancesCallback, URenderGrid* );`

### `Plugins/Experimental/RenderGrid/Source/RenderGridDeveloper/Public/Blueprints/RenderGridBlueprintCompiler.h` (Public)


#### class `UE::RenderGrid::FRenderGridBlueprintCompiler`  
`class FRenderGridBlueprintCompiler : public IBlueprintCompiler`  
_L16-23_
- inherits: `IBlueprintCompiler`
- desc: A IBlueprintCompiler child class for the RenderGrid modules. Required in order for a RenderGrid to be able to have a blueprint graph.
- L20 _public prototype_ `virtual bool CanCompile(const UBlueprint* Blueprint) override;`
- L21 _public prototype_ `virtual void Compile(UBlueprint* Blueprint, const FKismetCompilerOptions& CompileOptions, FCompilerResultsLog& Results) override;`

#### class `UE::RenderGrid::FRenderGridBlueprintCompilerContext`  
`class FRenderGridBlueprintCompilerContext : public FKismetCompilerContext`  
_L26-32_
- inherits: `FKismetCompilerContext`
- L29 _public function_ `FRenderGridBlueprintCompilerContext(UBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions) : FKismetCompilerContext(SourceSketch, InMessageLog, InCompilerOptions)`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridDeveloper/Public/IRenderGridDeveloperModule.h` (Public)


#### class `UE::RenderGrid::IRenderGridDeveloperModule`  
`class IRenderGridDeveloperModule : public IModuleInterface`  
_L14-15_
- inherits: `IModuleInterface`
- desc: RenderGridDeveloper module interface.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace RenderGrid` (scope `UE`)

### `Plugins/Experimental/RenderGrid/Source/RenderGridDeveloper/Public/RenderGridDeveloperLibrary.h` (Public)


#### class `URenderGridDeveloperLibrary`  
`class URenderGridDeveloperLibrary : public UBlueprintFunctionLibrary`  
_L15-54_
- reflection: `UCLASS(meta=(ScriptName="RenderGridDeveloperLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L26 _public prototype_ `static TArray<URenderGridBlueprint*> GetAllRenderGridBlueprintAssets();` — Returns all render grid assets that currently exist in the project (on disk and in memory). Will load the render grid assets in that are currently unloaded. This is a slow operation, so avoid doing this every tick.
- L35 _public prototype_ `static TArray<URenderGrid*> GetAllRenderGridAssets();` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Returns all render grid assets that currently exist in the project (on disk and in memory). Will load the render grid assets in that are currently unloaded. This is a slow operation, so avoid doing this every tick.
- L44 _public prototype_ `static URenderGridBlueprint* GetRenderGridBlueprintAsset(const FString& ObjectPath);` — Returns the given render grid asset that exists at the given object path (whether it's on disk or in memory). Will load the render grid asset if it's currently unloaded. This is a potentially slow operation, so avoid doing this every tick.
- L53 _public prototype_ `static URenderGrid* GetRenderGridAsset(const FString& ObjectPath);` — `UFUNCTION(BlueprintCallable, Category="Render Grid")` — Returns the given render grid asset that exists at the given object path (whether it's on disk or in memory). Will load the render grid asset if it's currently unloaded. This is a potentially slow operation, so avoid doing this every tick.

### `Plugins/Experimental/RenderGrid/Source/RenderGridDeveloper/Public/RenderGridDeveloperLog.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_CLASS(LogRenderGridDeveloper, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_CLASS(LogRenderGridDeveloper, Log, All);`
