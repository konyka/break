# Plugins / ScriptEditorPlugin

- module root: `Plugins/ScriptPlugin/Source/ScriptEditorPlugin`
- headers: 6; symbols: 44
- symbol kinds: class=5, delegate=1, function=3, member=6, prototype=28, typedef=1
- PublicDependencyModuleNames: AssetTools, BlueprintGraph, ClassViewer, Core, CoreUObject, EditorFramework, Engine, InputCore, Kismet, KismetCompiler, ScriptPlugin, UnrealEd

### `Plugins/ScriptPlugin/Source/ScriptEditorPlugin/Classes/ReimportScriptFactory.h` (Public)


#### class `UReimportScriptFactory`  
`class UReimportScriptFactory : public UScriptFactory, public FReimportHandler`  
_L18-33_
- reflection: `UCLASS(MinimalApi, collapsecategories, EarlyAccessPreview)`
- inherits: `UScriptFactory,FReimportHandler`
- desc: Script Blueprint re-import factory
- L23 _private member_ `TObjectPtr<class UScriptBlueprint> OriginalScript;` — `UPROPERTY()`
- L25 _private prototype_ `virtual bool ConfigureProperties() override;`
- L28 _private prototype_ `virtual bool CanReimport(UObject* Obj, TArray<FString>& OutFilenames) override;`
- L29 _private prototype_ `virtual void SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths) override;`
- L30 _private prototype_ `virtual EReimportResult::Type Reimport(UObject* Obj) override;`
- L31 _private prototype_ `virtual int32 GetPriority() const override;`

### `Plugins/ScriptPlugin/Source/ScriptEditorPlugin/Classes/ScriptFactory.h` (Public)


#### class `UScriptFactory`  
`class UScriptFactory : public UFactory`  
_L14-28_
- reflection: `UCLASS(collapsecategories, hidecategories = Object, EarlyAccessPreview)`
- inherits: `UFactory`
- desc: Script Blueprint factory
- L21 _public member_ `TSubclassOf<class UObject> ParentClass;` — `UPROPERTY(EditAnywhere, Category = ScriptFactory, meta = (AllowAbstract = "", BlueprintBaseOnly = ""))`
- L24 _public prototype_ `virtual bool ConfigureProperties() override;`
- L25 _public prototype_ `virtual bool DoesSupportClass(UClass* Class) override;`
- L26 _public prototype_ `virtual UObject* FactoryCreateText(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const TCHAR*& Buffer, const TCHAR* BufferEnd, FFeedbackContext* Warn);`

### `Plugins/ScriptPlugin/Source/ScriptEditorPlugin/Private/ScriptBlueprintCompiler.h` (Private)


#### class `FScriptBlueprintCompiler`  
`class FScriptBlueprintCompiler : public FKismetCompilerContext`  
_L14-61_
- inherits: `FKismetCompilerContext`
- desc: Script Blueprint Compiler
- L18 _protected typedef_ `typedef FKismetCompilerContext Super;`
- L21 _public prototype_ `FScriptBlueprintCompiler(UScriptBlueprint* SourceSketch, FCompilerResultsLog& InMessageLog, const FKismetCompilerOptions& InCompilerOptions);`
- L22 _public prototype_ `virtual ~FScriptBlueprintCompiler();`
- L25 _protected function_ `UScriptBlueprint* ScriptBlueprint() const`
- L28 _protected prototype_ `virtual void PreCompile() override;` — FKismetCompilerContext
- L29 _protected prototype_ `virtual void SpawnNewClass(const FString& NewClassName) override;`
- L30 _protected prototype_ `virtual void OnNewClassSet(UBlueprintGeneratedClass* ClassToUse) override;`
- L31 _protected prototype_ `virtual void CleanAndSanitizeClass(UBlueprintGeneratedClass* ClassToClean, UObject*& InOldCDO) override;`
- L32 _protected prototype_ `virtual void EnsureProperGeneratedClass(UClass*& TargetClass) override;`
- L33 _protected prototype_ `virtual void CreateClassVariablesFromBlueprint() override;`
- L34 _protected prototype_ `virtual void CreateFunctionList() override;`
- L35 _protected prototype_ `virtual void FinishCompilingClass(UClass* Class) override;`
- L36 _protected prototype_ `virtual bool ValidateGeneratedClass(UBlueprintGeneratedClass* Class) override;`
- L44 _protected prototype_ `void CreateScriptContextProperty();` — Creates a script context property for this class (if needed)
- L51 _protected prototype_ `void CreateScriptDefinedFunction(FScriptField& Field);` — Creates a Blueprint Graph function definition for script defined function @param Field Function exported by script
- L54 _protected member_ `UScriptBlueprintGeneratedClass* NewScriptBlueprintClass;` — New script class
- L56 _protected member_ `TUniquePtr<FScriptContextBase> ScriptContext;` — Script context
- L58 _protected member_ `TArray<FScriptField> ScriptDefinedFields;` — Script-defined properties and functions
- L60 _protected member_ `FObjectProperty* ContextProperty;` — Script context property generated for the compiled class

### `Plugins/ScriptPlugin/Source/ScriptEditorPlugin/Private/ScriptBlueprintEditor.h` (Private)


#### class `FScriptBlueprintEditor`  
`class FScriptBlueprintEditor : public FBlueprintEditor`  
_L11-27_
- inherits: `FBlueprintEditor`
- desc: Script blueprint editor (extends Blueprint editor)
- L14 _public prototype_ `FScriptBlueprintEditor();`
- L15 _public prototype_ `virtual ~FScriptBlueprintEditor();`
- L18 _public prototype_ `void InitScriptBlueprintEditor(const EToolkitMode::Type Mode, const TSharedPtr< IToolkitHost >& InitToolkitHost, const TArray<UBlueprint*>& InBlueprints, bool bShouldOpenInDefaultsMode);` — Initializes script editor
- L21 _public prototype_ `virtual void AddApplicationMode(FName ModeName, TSharedRef<FApplicationMode> Mode) override;` — Work around for the fact there's no other way to prevent Components Mode and Graph Mode from being entered/created
- L24 _public prototype_ `class UScriptBlueprint* GetScriptBlueprintObj() const;` — @return The Script blueprint currently being edited in this editor
- L26 _public prototype_ `virtual UBlueprint* GetBlueprintObj() const override;`

### `Plugins/ScriptPlugin/Source/ScriptEditorPlugin/Private/ScriptEditorPluginLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogScriptEditorPlugin, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogScriptEditorPlugin, Log, All);`

### `Plugins/ScriptPlugin/Source/ScriptEditorPlugin/Public/IScriptEditorPlugin.h` (Public)


#### class `IScriptEditorPlugin`  
`class IScriptEditorPlugin : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L23 _public function_ `static inline IScriptEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
