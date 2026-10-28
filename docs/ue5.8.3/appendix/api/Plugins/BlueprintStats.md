# Plugins / BlueprintStats

- module root: `Plugins/Experimental/BlueprintStats/Source/BlueprintStats`
- headers: 2; symbols: 24
- symbol kinds: class=2, function=3, member=16, prototype=3
- PublicDependencyModuleNames: BlueprintGraph, Core, CoreUObject, EditorFramework, Engine, GraphEditor, MessageLog, UnrealEd

### `Plugins/Experimental/BlueprintStats/Source/BlueprintStats/Private/BlueprintStats.h` (Private)


#### class `FBlueprintStatRecord`  
`class FBlueprintStatRecord`  
_L11-59_
- L15 _public member_ `UBlueprint* SourceBlueprint;` — Can be NULL, if it's a meta-record
- L17 _public member_ `TMap<UClass*, int32> NodeCount;`
- L18 _public member_ `TMap<UFunction*, int32> FunctionCount;`
- L19 _public member_ `TMap<UClass*, int32> FunctionOwnerCount;`
- L20 _public member_ `TMap<UEdGraph*, int32> RemoteMacroCount;`
- L22 _public member_ `int32 ImpureNodesWithInputs;`
- L23 _public member_ `int32 ImpureNodesWithOutputs;`
- L24 _public member_ `int32 ImpureNodesWithInputsAndOutputs;`
- L25 _public member_ `int32 ImpureFunctionNodes;`
- L26 _public member_ `int32 PureFunctionNodes;`
- L27 _public member_ `int32 NumUserFunctions;` — pure or impure
- L28 _public member_ `int32 NumUserPureFunctions;`
- L29 _public member_ `int32 NumUserMacros;`
- L30 _public member_ `int32 NumBlueprints;`
- L31 _public member_ `int32 NumDataOnlyBlueprints;`
- L32 _public member_ `int32 NumNodes;`
- L34 _public function_ `FBlueprintStatRecord(UBlueprint* InBlueprint = NULL) : SourceBlueprint(InBlueprint) , ImpureNodesWithInputs(0) , ImpureNodesWithOutputs(0) , ImpureNodesWithInputsAndOutputs(0) , ImpureFunctionNodes(0) , PureFunctionNodes(0) , NumUserFunctions(0) , NumUserPureFunctions(0) , NumUserMacros(0) , NumBlueprints(0) , NumDataOnlyBlueprints(0) , NumNodes(0)`
- L54 _public prototype_ `void MergeAnotherRecordIn(const FBlueprintStatRecord& OtherRecord);`
- L56 _public prototype_ `FString ToString(bool bHeader = false) const;`
- L58 _protected prototype_ `void ReadStatsFromBlueprint();`

### `Plugins/Experimental/BlueprintStats/Source/BlueprintStats/Public/IBlueprintStatsModule.h` (Public)


#### class `IBlueprintStatsModule`  
`class IBlueprintStatsModule : public IModuleInterface`  
_L12-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IBlueprintStatsModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
