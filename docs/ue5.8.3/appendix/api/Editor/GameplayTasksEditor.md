# Editor / GameplayTasksEditor

- module root: `Source/Editor/GameplayTasksEditor`
- headers: 2; symbols: 24
- symbol kinds: class=2, function=3, macro=1, member=2, prototype=16
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, GameplayTasks, KismetCompiler, UnrealEd

### `Source/Editor/GameplayTasksEditor/Classes/K2Node_LatentGameplayTaskCall.h` (Public)


#### class `UK2Node_LatentGameplayTaskCall`  
`class UK2Node_LatentGameplayTaskCall : public UK2Node_BaseAsyncTask`  
_L30-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UK2Node_BaseAsyncTask`
- L35 _public prototype_ `UK2Node_LatentGameplayTaskCall(const FObjectInitializer& ObjectInitializer);`
- L38 _public prototype_ `virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;` — UEdGraphNode interface
- L39 _public prototype_ `virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;`
- L42 _public prototype_ `virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;`
- L43 _public prototype_ `virtual void PinDefaultValueChanged(UEdGraphPin* Pin) override;`
- L44 _public prototype_ `bool ConnectSpawnProperties(UClass* ClassToSpawn, const UEdGraphSchema_K2* Schema, class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph, UEdGraphPin*& LastThenPin, UEdGraphPin* SpawnedActorReturnPin);` — Helper
- L45 _public prototype_ `virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;`
- L47 _public prototype_ `void CreatePinsForClass(UClass* InClass);`
- L48 _public prototype_ `UEdGraphPin* GetClassPin(const TArray<UEdGraphPin*>* InPinsToSearch = NULL) const;`
- L49 _public prototype_ `UClass* GetClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch = NULL) const;`
- L50 _public prototype_ `UEdGraphPin* GetResultPin() const;`
- L51 _public prototype_ `bool IsSpawnVarPin(UEdGraphPin* Pin);`
- L52 _public prototype_ `bool ValidateActorSpawning(class FKismetCompilerContext& CompilerContext, bool bGenerateErrors);`
- L53 _public prototype_ `bool ValidateActorArraySpawning(class FKismetCompilerContext& CompilerContext, bool bGenerateErrors);`
- L56 _public member_ `TArray<FName> SpawnParamPins;` — `UPROPERTY()`
- L58 _public prototype_ `static void RegisterSpecializedTaskNodeClass(TSubclassOf<UK2Node_LatentGameplayTaskCall> NodeClass);`
- L60 _protected prototype_ `static bool HasDedicatedNodeClass(TSubclassOf<UGameplayTask> TaskClass);`
- L62 _protected function_ `virtual bool IsHandling(TSubclassOf<UGameplayTask> TaskClass) const`
- L65 _private member_ `static TArray<TWeakObjectPtr<UClass> > NodeClasses;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API GAMEPLAYTASKSEDITOR_API`

### `Source/Editor/GameplayTasksEditor/Public/GameplayTasksEditorModule.h` (Public)


#### class `IGameplayTasksEditorModule`  
`class IGameplayTasksEditorModule : public IModuleInterface`  
_L12-37_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L23 _public function_ `static inline IGameplayTasksEditorModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L33 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
