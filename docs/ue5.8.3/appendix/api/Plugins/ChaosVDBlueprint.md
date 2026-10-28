# Plugins / ChaosVDBlueprint

- module root: `Plugins/ChaosVD/Source/ChaosVDBlueprint`
- headers: 1; symbols: 6
- symbol kinds: class=1, prototype=5
- PublicDependencyModuleNames: Chaos, Core, CoreUObject, Engine

### `Plugins/ChaosVD/Source/ChaosVDBlueprint/Public/ChaosVDRuntimeBlueprintLibrary.h` (Public)


#### class `UChaosVDRuntimeBlueprintLibrary`  
`class UChaosVDRuntimeBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L12-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library function to record debug draw shapes that will be played back when a CVD recording is loaded
- L17 _private prototype_ `static void RecordDebugDrawBox(const UObject* WorldContext, const FBox& InBox, FName Tag = NAME_None, FLinearColor Color = FLinearColor::Blue);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Visual Debugger", DisplayName="CVD Record Debug Draw Box", meta = (WorldContext = "WorldContext"))`
- L20 _private prototype_ `static void RecordDebugDrawLine(const UObject* WorldContext, const FVector& InStartLocation, const FVector& InEndLocation, FName Tag = NAME_None, FLinearColor Color = FLinearColor::Blue);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Visual Debugger", DisplayName="CVD Record Debug Draw Line", meta = (WorldContext = "WorldContext"))`
- L23 _private prototype_ `static void RecordDebugDrawVector(const UObject* WorldContext, const FVector& InStartLocation, const FVector& InVector, FName Tag = NAME_None, FLinearColor Color = FLinearColor::Blue);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Visual Debugger", DisplayName="CVD Record Debug Draw Vector", meta = (WorldContext = "WorldContext"))`
- L26 _private prototype_ `static void RecordDebugDrawSphere(const UObject* WorldContext, const FVector& InCenter, float Radius, FName Tag = NAME_None, FLinearColor Color = FLinearColor::Blue);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Visual Debugger", DisplayName="CVD Record Debug Draw Sphere", meta = (WorldContext = "WorldContext"))`
- L29 _private prototype_ `static void SetTraceRelevancyVolume(const UObject* WorldContext, const FBox& RelevancyVolume);` — `UFUNCTION(BlueprintCallable, Category = "Chaos Visual Debugger", DisplayName="CVD Set Trace Relevancy Volume", meta = (WorldContext = "WorldContext"))`
