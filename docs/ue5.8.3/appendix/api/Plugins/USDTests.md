# Plugins / USDTests

- module root: `Plugins/Importers/USDImporter/Source/USDTests`
- headers: 2; symbols: 9
- symbol kinds: class=2, macro=1, prototype=6
- PrivateDependencyModuleNames: BlueprintGraph, Core, CoreUObject, Engine, USDClasses, USDSchemas, USDStage, USDUtilities, UnrealEd, UnrealUSDWrapper

### `Plugins/Importers/USDImporter/Source/USDTests/Public/USDTestsBlueprintLibrary.h` (Public)


#### class `USDTestsBlueprintLibrary`  
`class UE_DEPRECATED(all, "These functions were meant for internal testing only and will be removed in a future release") USDTestsBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L13-42_
- reflection: `UCLASS(MinimalAPI, meta = (ScriptName = "USDTestingLibrary"))`
- inherits: `UBlueprintFunctionLibrary`
- L21 _public prototype_ `static bool RecompileBlueprintStageActor(AUsdStageActor* BlueprintDerivedStageActor);` — `UE_DEPRECATED(all, "These functions were meant for internal testing only and will be removed in a future release.")` — `UFUNCTION()`
- L25 _public prototype_ `static void DirtyStageActorBlueprint(AUsdStageActor* BlueprintDerivedStageActor);` — `UE_DEPRECATED(all, "These functions were meant for internal testing only and will be removed in a future release.")` — `UFUNCTION()`
- L29 _public prototype_ `static int64 GetSubtreeVertexCount(AUsdStageActor* StageActor, const FString& PrimPath);` — `UE_DEPRECATED(all, "These functions were meant for internal testing only and will be removed in a future release.")` — `UFUNCTION()`
- L33 _public prototype_ `static int64 GetSubtreeMaterialSlotCount(AUsdStageActor* StageActor, const FString& PrimPath);` — `UE_DEPRECATED(all, "These functions were meant for internal testing only and will be removed in a future release.")` — `UFUNCTION()`
- L37 _public prototype_ `static void SetUsdStageCpp(AUsdStageActor* StageActor, const FString& NewStageRootLayer);` — `UE_DEPRECATED(all, "These functions were meant for internal testing only and will be removed in a future release.")` — `UFUNCTION()`
- L41 _public prototype_ `static void ClearTransactionHistory();` — `UE_DEPRECATED(all, "These functions were meant for internal testing only and will be removed in a future release.")` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API USDTESTS_API`

### `Plugins/Importers/USDImporter/Source/USDTests/Public/USDTestsModule.h` (Public)


#### class `IUsdTestsModule`  
`class IUsdTestsModule : public IModuleInterface`  
_L7-9_
- inherits: `IModuleInterface`
