# Plugins / AnimationLocomotionLibraryRuntime

- module root: `Plugins/Animation/AnimationLocomotionLibrary/Source/Runtime`
- headers: 3; symbols: 12
- symbol kinds: class=3, macro=2, prototype=7
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationCore, Core, CoreUObject, Engine

### `Plugins/Animation/AnimationLocomotionLibrary/Source/Runtime/Public/AnimCharacterMovementLibrary.h` (Public)


#### class `UAnimCharacterMovementLibrary`  
`class UAnimCharacterMovementLibrary : public UBlueprintFunctionLibrary`  
_L17-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of common techniques for driving character locomotion animations.
- L31 _public prototype_ `static FVector PredictGroundMovementStopLocation(const FVector& Velocity, bool bUseSeparateBrakingFriction, float BrakingFriction, float GroundFriction, float BrakingFrictionFactor, float BrakingDecelerationWalking);` — `UFUNCTION(BlueprintPure, Category = "Animation Character Movement", meta = (BlueprintThreadSafe))` — Predict where the character will stop based on its current movement properties and parameters from the movement component. This uses prediction logic that is heavily tied to the UCharacterMovementComponent. Each parameter corresponds to a value from the UCharacterMovementComponent with the same name. Because this is a thread safe function, it's	recommended to populate these fields via the Property Access system. @return The predicted stop position in local space to the character. The size of this vector will be the distance to the stop location.
- L42 _public prototype_ `static FVector PredictGroundMovementPivotLocation(const FVector& Acceleration, const FVector& Velocity, float GroundFriction);` — `UFUNCTION(BlueprintPure, Category = "Animation Character Movement", meta = (BlueprintThreadSafe))` — Predict where the character will change direction during a pivot based on its current movement properties and parameters from the movement component. This uses prediction logic that is heavily tied to the UCharacterMovementComponent. Each parameter corresponds to a value from the UCharacterMovementComponent with the same name. Because this is a thread safe function, it's	recommended to populate these fields via the Property Access system. @return The predicted pivot position in local space to the character. The size of this vector will be the distance to the pivot.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ANIMATIONLOCOMOTIONLIBRARYRUNTIME_API`

### `Plugins/Animation/AnimationLocomotionLibrary/Source/Runtime/Public/AnimDistanceMatchingLibrary.h` (Public)


#### class `UAnimDistanceMatchingLibrary`  
`class UAnimDistanceMatchingLibrary : public UBlueprintFunctionLibrary`  
_L21-63_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Library of techniques for driving animations by distance metrics rather than by time. These techniques can be effective at compensating for differences between character movement and authored motion in the animations. Distance Matching effectively changes the play rate of the animation to keep the feet from sliding. It's common to clamp the resulting play rate to avoid animations playing too slow or too fast and to use techniques such as Stride Warping to make up the difference.
- L36 _public prototype_ `static FSequenceEvaluatorReference AdvanceTimeByDistanceMatching(const FAnimUpdateContext& UpdateContext, const FSequenceEvaluatorReference& SequenceEvaluator, float DistanceTraveled, FName DistanceCurveName, FVector2D PlayRateClamp = FVector2D(0.75f, 1.25f));` — `UFUNCTION(BlueprintCallable, Category = "Distance Matching", meta=(BlueprintThreadSafe))` — Advance the sequence evaluator forward by distance traveled rather than time. A distance curve is required on the animation that describes the distance traveled by the root bone in the animation. See UDistanceCurveModifier. @param UpdateContext - The update context provided in the anim node function. @param SequenceEvaluator - The sequence evaluator node to operate on. @param DistanceTraveled - The distance traveled by the character since the last animation update. @param DistanceCurveName - Name of the curve we want to match @param PlayRateClamp - A clamp on the effective play rate of the animation after distance matching. Set to (0,0) for no clamping.
- L48 _public prototype_ `static FSequenceEvaluatorReference DistanceMatchToTarget(const FSequenceEvaluatorReference& SequenceEvaluator, float DistanceToTarget, FName DistanceCurveName);` — `UFUNCTION(BlueprintCallable, Category = "Distance Matching", meta=(BlueprintThreadSafe))` — Set the time of the sequence evaluator to the point in the animation where the distance curve matches the DistanceToTarget input. A common use case is to achieve stops without foot sliding by, each frame, selecting the point in the animation that matches the distance the character has remaining until it stops. Note that because this technique sets the time of the animation by distance remaining, it doesn't respect phase of any previous animation (e.g. from a jog cycle). @param SequenceEvaluator - The sequence evaluator node to operate on. @param DistanceToTarget - The distance remaining to a target (e.g. a stop or pivot point). @param DistanceCurveName - Name of the curve we want to match
- L61 _public prototype_ `static FSequencePlayerReference SetPlayrateToMatchSpeed(const FSequencePlayerReference& SequencePlayer, float SpeedToMatch, FVector2D PlayRateClamp = FVector2D(0.75f, 1.25f));` — `UFUNCTION(BlueprintCallable, Category = "Distance Matching", meta=(BlueprintThreadSafe))` — Set the play rate of the sequence player so that the speed of the animation matches in-game movement speed. While distance matching is commonly used for transition animations, cycle animations (walk, jog, etc) typically just adjust their play rate to match the in-game movement speed. This function assumes that the animation has a constant speed. @param SequencePlayer - The sequence player node to operate on. @param SpeedToMatch - The in-game movement speed to match. This is usually the current speed of the movement component. @param PlayRateClamp - A clamp on how much the animation's play rate can change to match the in-game movement speed. Set to (0,0) for no clamping.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API ANIMATIONLOCOMOTIONLIBRARYRUNTIME_API`

### `Plugins/Animation/AnimationLocomotionLibrary/Source/Runtime/Public/AnimationLocomotionLibraryModule.h` (Public)


#### class `FAnimationLocomotionLibraryRuntimeModule`  
`class FAnimationLocomotionLibraryRuntimeModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
