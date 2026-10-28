# Plugins / ArchVisCharacter

- module root: `Plugins/Runtime/ArchVisCharacter/Source/ArchVisCharacter`
- headers: 2; symbols: 36
- symbol kinds: class=2, macro=2, member=18, prototype=14
- PublicDependencyModuleNames: Core, CoreUObject, Engine, RHI, RenderCore

### `Plugins/Runtime/ArchVisCharacter/Source/ArchVisCharacter/Public/ArchVisCharMovementComponent.h` (Public)


#### class `UArchVisCharMovementComponent`  
`class UArchVisCharMovementComponent : public UCharacterMovementComponent`  
_L13-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCharacterMovementComponent`
- L19 _public prototype_ `UArchVisCharMovementComponent(const FObjectInitializer& ObjectInitializer);` — Ctor
- L23 _public member_ `FRotator RotationalAcceleration;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Controls how fast the character's turn rate accelerates when rotating and looking up/down
- L27 _public member_ `FRotator RotationalDeceleration;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Controls how fast the character's turn rate decelerates to 0 when user stops turning
- L31 _public member_ `FRotator MaxRotationalVelocity;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Fastest possible turn rate
- L35 _public member_ `float MinPitch;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Controls how far down you can look
- L39 _public member_ `float MaxPitch;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Controls how far up you can look
- L43 _public member_ `float WalkingFriction;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Controls walking deceleration.
- L47 _public member_ `float WalkingSpeed;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — How fast the character can walk.
- L51 _public member_ `float WalkingAcceleration;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — How fast the character accelerates.
- L55 _public prototype_ `void AddRotInput(float Pitch, float Yaw, float Roll);` — Adds rotational input.
- L59 _protected member_ `FRotator CurrentRotationalVelocity;`
- L61 _protected member_ `FRotator CurrentRotInput;`
- L63 _protected prototype_ `virtual void PhysWalking(float DeltaTime, int32 Iterations) override;`
- L64 _protected prototype_ `virtual void OnRegister() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ARCHVISCHARACTER_API`

### `Plugins/Runtime/ArchVisCharacter/Source/ArchVisCharacter/Public/ArchVisCharacter.h` (Public)


#### class `AArchVisCharacter`  
`class AArchVisCharacter : public ACharacter`  
_L15-71_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `ACharacter`
- L21 _public prototype_ `AArchVisCharacter(const FObjectInitializer& ObjectInitializer);` — Ctor
- L25 _public member_ `FString LookUpAxisName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Axis name for direct look up/down inputs (e.g. mouse). This should match an Axis Binding in your input settings
- L29 _public member_ `FString LookUpAtRateAxisName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Axis name for rate-based look up/down inputs (e.g. joystick). This should match an Axis Binding in your input settings
- L33 _public member_ `FString TurnAxisName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Axis name for direct turn left/right inputs (e.g. mouse). This should match an Axis Binding in your input settings
- L37 _public member_ `FString TurnAtRateAxisName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Axis name for rate-based turn left/right inputs (e.g. joystick). This should match an Axis Binding in your input settings
- L41 _public member_ `FString MoveForwardAxisName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Axis name for "move forward/back" control. This should match an Axis Binding in your input settings
- L45 _public member_ `FString MoveRightAxisName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Axis name for "move left/right" control. This should match an Axis Binding in your input settings
- L49 _public member_ `float MouseSensitivityScale_Pitch;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Controls how aggressively mouse motion translates to character rotation in the pitch axis.
- L53 _public member_ `float MouseSensitivityScale_Yaw;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ArchVis Controls")` — Controls how aggressively mouse motion translates to character rotation in the yaw axis.
- L58 _protected prototype_ `class UArchVisCharMovementComponent* GetArchVisCharMoveComponent() const;` — helper
- L60 _protected prototype_ `virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;`
- L61 _protected prototype_ `virtual FRotator GetViewRotation() const override;`
- L64 _protected prototype_ `virtual void Turn(float Val);` — input handlers
- L65 _protected prototype_ `virtual void TurnAtRate(float Val);`
- L66 _protected prototype_ `virtual void LookUp(float Val);`
- L67 _protected prototype_ `virtual void LookUpAtRate(float Val);`
- L68 _protected prototype_ `virtual void MoveRight(float Val);`
- L69 _protected prototype_ `virtual void MoveForward(float Val);`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ARCHVISCHARACTER_API`
