# Plugins / ChaosModularVehicleEditor

- module root: `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEditor`
- headers: 2; symbols: 11
- symbol kinds: class=2, function=3, member=1, prototype=5
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, BlueprintGraph, Chaos, ChaosModularVehicleEngine, Core, CoreUObject, EditorFramework, Engine, NetCore, PropertyEditor, ToolMenus, UnrealEd

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEditor/Public/ChaosModularVehicle/AnimGraphNode_ModularVehicleController.h` (Public)


#### class `UAnimGraphNode_ModularVehicleController`  
`class UAnimGraphNode_ModularVehicleController : public UAnimGraphNode_SkeletalControlBase`  
_L14-35_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Modify Modular Vehicle"))`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L19 _private member_ `FAnimNode_ModularVehicleController Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual void ValidateAnimNodePostCompile(class FCompilerResultsLog& MessageLog, class UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex) override;` — validate if this is within VehicleAnimInstance
- L27 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L32 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L33 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Plugins/Experimental/ChaosModularVehicle/Source/ChaosModularVehicleEditor/Public/ChaosModularVehicle/ChaosModularVehicleEditorPlugin.h` (Public)


#### class `IChaosModularVehicleEditorPlugin`  
`class IChaosModularVehicleEditorPlugin : public IModuleInterface`  
_L13-40_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IChaosModularVehicleEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L34 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
