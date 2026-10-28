# Plugins / MoverTests

- module root: `Plugins/Experimental/MoverTests/Source/MoverTests`
- headers: 2; symbols: 16
- symbol kinds: class=1, function=1, member=2, prototype=11, struct=1
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine, Mover, MoverExamples, NetCore, RuntimeTests, Slate, SlateCore

### `Plugins/Experimental/MoverTests/Source/MoverTests/Public/MoverTests.h` (Public)


#### class `FMoverTestsModule`  
`class FMoverTestsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/MoverTests/Source/MoverTests/Public/TestCustomLayeredMoves.h` (Public)


#### struct `FTestCustomLayeredMove`  
`struct FTestCustomLayeredMove : public FLayeredMoveBase`  
_L12-43_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FLayeredMoveBase`
- desc: Custom Layered move for testing purposes - acts the same as the Launch layered move
- L16 _public prototype_ `FTestCustomLayeredMove();`
- L17 _public function_ `virtual ~FTestCustomLayeredMove() override`
- L21 _public member_ `FVector LaunchVelocity = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover, meta=(ForceUnits="cm/s"))` — Velocity to apply to the actor. Could be additive or overriding depending on MixMode setting.
- L25 _public member_ `FName ForceMovementMode = NAME_None;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mover)` — Optional movement mode name to force the actor into before applying the impulse velocity.
- L27 _public prototype_ `virtual void OnStart(const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard) override;`
- L29 _public prototype_ `virtual void OnEnd(const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, double CurrentSimTimeMs) override;`
- L32 _public prototype_ `virtual bool GenerateMove(const FMoverTickStartData& StartState, const FMoverTimeStep& TimeStep, const UMoverComponent* MoverComp, UMoverBlackboard* SimBlackboard, FProposedMove& OutProposedMove) override;` — Generate a movement
- L34 _public prototype_ `virtual FLayeredMoveBase* Clone() const override;`
- L36 _public prototype_ `virtual void NetSerialize(FArchive& Ar) override;`
- L38 _public prototype_ `virtual UScriptStruct* GetScriptStruct() const override;`
- L40 _public prototype_ `virtual FString ToSimpleString() const override;`
- L42 _public prototype_ `virtual void AddReferencedObjects(class FReferenceCollector& Collector) override;`
