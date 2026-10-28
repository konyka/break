# Plugins / ChaosVehiclesEditor

- module root: `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor`
- headers: 7; symbols: 42
- symbol kinds: class=6, function=11, member=7, prototype=18
- PublicDependencyModuleNames: AnimGraph, AnimGraphRuntime, BlueprintGraph, ChaosVehicles, ChaosVehiclesCore, ChaosVehiclesEngine, Core, CoreUObject, EditorFramework, Engine, PhysicsCore, PropertyEditor, Slate, SlateCore, ToolMenus, UnrealEd

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor/Private/ChaosVehiclesEditorStyle.h` (Private)


#### class `FChaosVehiclesEditorStyle`  
`class FChaosVehiclesEditorStyle final : public FSlateStyleSet`  
_L8-49_
- inherits: `FSlateStyleSet`
- L11 _public function_ `FChaosVehiclesEditorStyle() : FSlateStyleSet("ChaosVehiclesEditorStyle")`
- L26 _public function_ `~FChaosVehiclesEditorStyle()`
- L33 _public function_ `static FChaosVehiclesEditorStyle& Get()`
- L42 _public function_ `static void Destroy()`
- L48 _private member_ `static TOptional<FChaosVehiclesEditorStyle> Singleton;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor/Public/AnimGraphNode_StageCoachWheelController.h` (Public)


#### class `UAnimGraphNode_StageCoachWheelController`  
`class UAnimGraphNode_StageCoachWheelController : public UAnimGraphNode_SkeletalControlBase`  
_L14-35_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Modify Wheel Vehicle"))`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L19 _private member_ `FAnimNode_StageCoachWheelController Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual void ValidateAnimNodePostCompile(class FCompilerResultsLog& MessageLog, class UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex) override;` — validate if this is within VehicleAnimInstance
- L27 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L32 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L33 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor/Public/AnimGraphNode_WheelController.h` (Public)


#### class `UAnimGraphNode_WheelController`  
`class UAnimGraphNode_WheelController : public UAnimGraphNode_SkeletalControlBase`  
_L14-35_
- reflection: `UCLASS(MinimalAPI, meta=(Keywords = "Modify Wheel Vehicle"))`
- inherits: `UAnimGraphNode_SkeletalControlBase`
- L19 _private member_ `FAnimNode_WheelController Node;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L23 _public prototype_ `virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;` — UEdGraphNode interface
- L24 _public prototype_ `virtual FText GetTooltipText() const override;`
- L26 _public prototype_ `virtual void ValidateAnimNodePostCompile(class FCompilerResultsLog& MessageLog, class UAnimBlueprintGeneratedClass* CompiledClass, int32 CompiledNodeIndex) override;` — validate if this is within VehicleAnimInstance
- L27 _public prototype_ `virtual bool IsCompatibleWithGraph(const UEdGraph* TargetGraph) const override;`
- L32 _protected prototype_ `virtual FText GetControllerDescription() const override;` — UAnimGraphNode_SkeletalControlBase interface
- L33 _protected function_ `virtual const FAnimNode_SkeletalControlBase* GetNode() const override`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor/Public/AssetTypeActions_ChaosVehicles.h` (Public)


#### class `FAssetTypeActions_ChaosVehicles`  
`class FAssetTypeActions_ChaosVehicles : public FAssetTypeActions_Base`  
_L9-20_
- inherits: `FAssetTypeActions_Base`
- L13 _public function_ `virtual FText GetName() const override` — IAssetTypeActions Implementation
- L14 _public prototype_ `virtual void GetActions(const TArray<UObject*>& InObjects, struct FToolMenuSection& Section) override;`
- L15 _public function_ `virtual FColor GetTypeColor() const override`
- L16 _public prototype_ `virtual UClass* GetSupportedClass() const override;`
- L17 _public prototype_ `virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;`
- L18 _public function_ `virtual uint32 GetCategories() override`
- L19 _public prototype_ `virtual UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor/Public/ChaosVehiclesEditorCommands.h` (Public)


#### class `FChaosVehiclesCommands`  
`class FChaosVehiclesCommands`  
_L12-14_
- desc: The public interface to this module

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor/Public/ChaosVehiclesEditorPlugin.h` (Public)


#### class `IChaosVehiclesEditorPlugin`  
`class IChaosVehiclesEditorPlugin : public IModuleInterface`  
_L14-56_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L16 _private member_ `TArray<IConsoleObject*> EditorCommands;`
- L19 _public prototype_ `virtual void StartupModule();`
- L20 _public prototype_ `virtual void ShutdownModule();`
- L29 _public function_ `static inline IChaosVehiclesEditorPlugin& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L39 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L46 _private prototype_ `void PhysSceneInit(FPhysScene* PhysScene);`
- L47 _private prototype_ `void PhysSceneTerm(FPhysScene* PhysScene);`
- L49 _private member_ `class FAssetTypeActions_ChaosVehicles* AssetTypeActions_ChaosVehicles;`
- L52 _private member_ `FDelegateHandle OnPhysSceneInitHandle;` — FDelegateHandle OnUpdatePhysXMaterialHandle; FDelegateHandle OnPhysicsAssetChangedHandle;
- L53 _private member_ `FDelegateHandle OnPhysSceneTermHandle;`

### `Plugins/Experimental/ChaosVehiclesPlugin/Source/ChaosVehiclesEditor/Public/ChaosVehiclesFactory.h` (Public)
_(no declarations extracted)_
