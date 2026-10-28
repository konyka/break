# Plugins / RigLogicDeveloper

- module root: `Plugins/Animation/RigLogic/Source/RigLogicDeveloper`
- headers: 2; symbols: 12
- symbol kinds: class=2, delegate=1, macro=2, member=1, prototype=6
- DynamicallyLoadedModuleNames: RigLogicEditor
- PrivateDependencyModuleNames: AnimGraph, BlueprintGraph, Core, CoreUObject, Engine, MessageLog, RigLogicModule
- PrivateIncludePathModuleNames: RigLogicEditor
- PublicDependencyModuleNames: AnimationCore

### `Plugins/Animation/RigLogic/Source/RigLogicDeveloper/Public/AnimGraphNode_RigLogic.h` (Public)


#### class `UAnimGraphNode_RigLogic`  
`class UAnimGraphNode_RigLogic : public UAnimGraphNode_Base`  
_L12-25_
- reflection: `UCLASS(MinimalAPI, meta = (Keywords = "Rig Logic Animation Node"))`
- inherits: `UAnimGraphNode_Base`
- L17 _private member_ `FAnimNode_RigLogic Node;` — `UPROPERTY(EditAnywhere, Category = Settings)`
- L20 _public prototype_ `FText GetTooltipText() const;`
- L21 _public prototype_ `FText GetNodeTitle(ENodeTitleType::Type TitleType) const;`
- L24 _protected prototype_ `void ValidateAnimNodeDuringCompilation(USkeleton* ForSkeleton, FCompilerResultsLog& MessageLog);`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API RIGLOGICDEVELOPER_API`

### `Plugins/Animation/RigLogic/Source/RigLogicDeveloper/Public/RigLogicDeveloper.h` (Public)


#### class `FRigLogicDeveloperModule`  
`class FRigLogicDeveloperModule : public IModuleInterface`  
_L12-17_
- inherits: `IModuleInterface`
- L15 _public prototype_ `void StartupModule() override;`
- L16 _public prototype_ `void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API RIGLOGICDEVELOPER_API`
- L10 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicDeveloper, Log, All);`
- L10 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogRigLogicDeveloper, Log, All);`
