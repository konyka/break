# Plugins / ActorLayerUtilities

- module root: `Plugins/Runtime/ActorLayerUtilities/Source/ActorLayerUtilities`
- headers: 1; symbols: 6
- symbol kinds: class=1, member=1, prototype=3, struct=1
- PrivateDependencyModuleNames: Engine
- PublicDependencyModuleNames: Core, CoreUObject

### `Plugins/Runtime/ActorLayerUtilities/Source/ActorLayerUtilities/Public/ActorLayerUtilities.h` (Public)


#### struct `FActorLayer`  
`struct FActorLayer`  
_L10-17_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `FName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Layer)` — The name of this layer

#### class `ULayersBlueprintLibrary`  
`class ULayersBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L24-49_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Function library containing methods for interacting with editor layers
- L34 _public prototype_ `static TArray<AActor*> GetActors(UObject* WorldContextObject, const FActorLayer& ActorLayer);` — `UFUNCTION(BlueprintCallable, Category=Layer, meta=(WorldContext=WorldContextObject))` — Get all the actors in this layer
- L40 _public prototype_ `static void AddActorToLayer(AActor* InActor, const FActorLayer& Layer);` — `UFUNCTION(BlueprintCallable, Category = Layer)` — Adds the actor to the specified layer
- L46 _public prototype_ `static void RemoveActorFromLayer(AActor* InActor, const FActorLayer& Layer);` — `UFUNCTION(BlueprintCallable, Category = Layer)` — Removes the actor from the specified layer
