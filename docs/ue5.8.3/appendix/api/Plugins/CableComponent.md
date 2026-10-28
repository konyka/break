# Plugins / CableComponent

- module root: `Plugins/Runtime/CableComponent/Source/CableComponent`
- headers: 3; symbols: 69
- symbol kinds: class=2, delegate=1, function=1, macro=1, member=37, prototype=26, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RHI, RenderCore

### `Plugins/Runtime/CableComponent/Source/CableComponent/Classes/CableActor.h` (Public)


#### class `ACableActor`  
`class ACableActor : public AActor`  
_L10-17_
- reflection: `UCLASS(MinimalAPI, hidecategories=(Input,Replication), showcategories=("Input|MouseInput", "Input|TouchInput"))`
- inherits: `AActor`
- desc: An actor that renders a simulated cable
- L16 _private member_ `TObjectPtr<class UCableComponent> CableComponent;` — `UPROPERTY(Category=Cable, VisibleAnywhere, BlueprintReadOnly)` — Cable component that performs simulation and rendering

### `Plugins/Runtime/CableComponent/Source/CableComponent/Classes/CableComponent.h` (Public)


#### struct `FCableParticle`  
`struct FCableParticle`  
_L13-27_
- desc: Struct containing information about a point along the cable
- L15 _public function_ `FCableParticle() : bFree(true) , Position(0,0,0) , OldPosition(0,0,0)`
- L22 _public member_ `bool bFree;` — If this point is free (simulating) or fixed to something
- L24 _public member_ `FVector Position;` — Current position of point
- L26 _public member_ `FVector OldPosition;` — Position of point on previous iteration

#### class `UCableComponent`  
`class UCableComponent : public UMeshComponent`  
_L31-230_
- reflection: `UCLASS(MinimalAPI, hidecategories=(Object, Physics, Activation, "Components|Activation"), editinlinenew, meta=(BlueprintSpawnableComponent), ClassGroup=Rendering)`
- inherits: `UMeshComponent`
- desc: Component that allows you to specify custom triangle mesh geometry
- L38 _public prototype_ `virtual void OnRegister() override;`
- L39 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L40 _public prototype_ `virtual void SendRenderDynamicData_Concurrent() override;`
- L41 _public prototype_ `virtual void CreateRenderState_Concurrent(FRegisterComponentContext* Context) override;`
- L42 _public prototype_ `virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;`
- L46 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L47 _public prototype_ `virtual void QuerySupportedSockets(TArray<FComponentSocketDescription>& OutSockets) const override;`
- L48 _public prototype_ `virtual bool HasAnySockets() const override;`
- L49 _public prototype_ `virtual bool DoesSocketExist(FName InSocketName) const override;`
- L50 _public prototype_ `virtual FTransform GetSocketTransform(FName InSocketName, ERelativeTransformSpace TransformSpace = RTS_World) const override;`
- L51 _public prototype_ `virtual void OnVisibilityChanged() override;`
- L55 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L56 _public prototype_ `virtual void PostLoad() override;`
- L57 _public prototype_ `virtual void CollectPSOPrecacheData(const FPSOPrecacheParams& BasePrecachePSOParams, FMaterialInterfacePSOPrecacheParamsList& OutParams) override;`
- L61 _public prototype_ `virtual int32 GetNumMaterials() const override;`
- L70 _public member_ `bool bAttachStart;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cable")` — Should we fix the start to something, or leave it free. If false, component transform is just used for initial location of start of cable
- L77 _public member_ `bool bAttachEnd;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cable")` — Should we fix the end to something (using AttachEndTo and EndLocation), or leave it free. If false, AttachEndTo and EndLocation are just used for initial location of end of cable
- L81 _public member_ `FComponentReference AttachEndTo;` — `UPROPERTY(EditAnywhere, Category="Cable")` — Actor or Component that the defines the end position of the cable
- L85 _public member_ `FName AttachEndToSocketName;` — `UPROPERTY(EditAnywhere, Category = "Cable")` — Socket name on the AttachEndTo component to attach to
- L89 _public member_ `FVector EndLocation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cable", meta=(MakeEditWidget=true))` — End location of cable, relative to AttachEndTo (or AttachEndToSocketName) if specified, otherwise relative to cable component.
- L93 _public prototype_ `void SetAttachEndToComponent(USceneComponent* Component, FName SocketName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Cable")` — Attaches the end of the cable to a specific Component
- L97 _public prototype_ `void SetAttachEndTo(AActor* Actor, FName ComponentProperty, FName SocketName = NAME_None);` — `UFUNCTION(BlueprintCallable, Category = "Cable")` — Attaches the end of the cable to a specific Component within an Actor
- L101 _public prototype_ `AActor* GetAttachedActor() const;` — `UFUNCTION(BlueprintCallable, Category = "Cable")` — Gets the Actor that the cable is attached to
- L105 _public prototype_ `USceneComponent* GetAttachedComponent() const;` — `UFUNCTION(BlueprintCallable, Category = "Cable")` — Gets the specific USceneComponent that the cable is attached to
- L109 _public prototype_ `void GetCableParticleLocations(TArray<FVector>& Locations) const;` — `UFUNCTION(BlueprintCallable, Category = "Cable")` — Get array of locations of particles (in world space) making up the cable simulation.
- L113 _public member_ `float CableLength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cable", meta=(ClampMin = "0.0", UIMin = "0.0", UIMax = "1000.0"))` — Rest length of the cable
- L117 _public member_ `int32 NumSegments;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cable", meta=(ClampMin = "1", UIMin = "1", UIMax = "20"))` — How many segments the cable has
- L121 _public member_ `float SubstepTime;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, BlueprintReadOnly, Category="Cable", meta=(ClampMin = "0.005", UIMin = "0.005", UIMax = "0.1"))` — Controls the simulation substep time for the cable
- L125 _public member_ `int32 SolverIterations;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cable", meta=(ClampMin = "1", ClampMax = "16"))` — The number of solver iterations controls how 'stiff' the cable is
- L129 _public member_ `bool bEnableStiffness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Cable")` — Add stiffness constraints to cable.
- L133 _public member_ `bool bUseSubstepping = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Cable")` — When false, will still wait for SubstepTime to elapse before updating, but will only run the cable simulation once using all of accumulated simulation time
- L136 _public member_ `bool bSkipCableUpdateWhenNotVisible = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Cable")`
- L139 _public member_ `bool bSkipCableUpdateWhenNotOwnerRecentlyRendered = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Cable")`
- L147 _public member_ `bool bEnableCollision;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Cable")` — EXPERIMENTAL. Perform sweeps for each cable particle, each substep, to avoid collisions with the world. Uses the Collision Preset on the component to determine what is collided with. This greatly increases the cost of the cable simulation.
- L151 _public member_ `float CollisionFriction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "Cable", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bEnableCollision"))` — If collision is enabled, control how much sliding friction is applied when cable is in contact.
- L155 _public member_ `FVector CableForce;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cable Forces")` — Force vector (world space) applied to all particles in cable.
- L159 _public member_ `float CableGravityScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cable Forces")` — Scaling applied to world gravity affecting this cable.
- L163 _public member_ `float CableWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cable Rendering", meta=(ClampMin = "0.01", UIMin = "0.01", UIMax = "50.0"))` — How wide the cable geometry is
- L167 _public member_ `int32 NumSides;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Cable Rendering", meta=(ClampMin = "1", ClampMax = "16"))` — Number of sides of the cable geometry
- L171 _public member_ `float TileMaterial;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cable Rendering", meta=(UIMin = "0.1", UIMax = "8"))` — How many times to repeat the material along the length of the cable
- L177 _public member_ `bool bResetAfterTeleport = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")` — Always reset cable particle positions and velocities on a teleport.
- L184 _public member_ `float TeleportDistanceThreshold = 500;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Teleport", meta=(UIMin = "0"))` — Conduct teleportation if the movement of either fixed end point of the cable is greater than this threshold in 1 frame. Zero or negative values will skip the check.
- L192 _public member_ `float TeleportRotationThreshold = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Teleport", meta = (UIMin = "0"))` — Rotation threshold in degrees. Conduct teleportation if the cable's rotation is greater than this threshold in 1 frame. Zero or negative values will skip the check.
- L198 _public member_ `bool bTeleportAfterReattach = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleport")` — Teleport the cable particles on reattaching any end of the cable.
- L203 _private prototype_ `void SolveConstraints();` — Solve the cable spring constraints
- L205 _private prototype_ `void VerletIntegrate(float InSubstepTime, const FVector& Gravity);` — Integrate cable point positions
- L207 _private prototype_ `void PerformCableCollision();` — Perform collision traces for particles
- L209 _private prototype_ `void PerformSubstep(float InSubstepTime, const FVector& Gravity);` — Perform a simulation substep
- L211 _private prototype_ `void GetEndPositions(FVector& OutStartPosition, FVector& OutEndPosition);` — Get start and end position for the cable
- L213 _private member_ `float TimeRemainder;` — Amount of time 'left over' from last tick
- L215 _private member_ `TArray<FCableParticle> Particles;` — Array of cable particles
- L218 _private member_ `FTransform LastTransform;` — Previous cable state for teleport corrections
- L219 _private member_ `FTransform LastEndPointTransform;`
- L220 _private member_ `FVector LastEndPoint;`
- L221 _private member_ `FVector LastEndLocation;`
- L222 _private member_ `FVector LastStartPoint;`
- L223 _private member_ `bool bLastStartAttached;`
- L224 _private member_ `bool bLastEndAttached;`
- L227 _private prototype_ `void DoTeleportCorrections(const FVector& StartPosition, const FVector& EndPosition);` — Perform checks and corrections on particle positions for teleports

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CABLECOMPONENT_API`

### `Plugins/Runtime/CableComponent/Source/CableComponent/Private/CableComponentStats.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_STATS_GROUP(TEXT("Cable"), STATGROUP_CableComponent, STATCAT_Advan`
