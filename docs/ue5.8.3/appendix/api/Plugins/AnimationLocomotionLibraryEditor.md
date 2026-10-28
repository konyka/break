# Plugins / AnimationLocomotionLibraryEditor

- module root: `Plugins/Animation/AnimationLocomotionLibrary/Source/Editor`
- headers: 2; symbols: 19
- symbol kinds: class=2, enum=1, enumerator=7, member=5, prototype=4
- PrivateDependencyModuleNames: 
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: AnimGraphRuntime, AnimationBlueprintLibrary, AnimationModifiers, Core, CoreUObject, Engine

### `Plugins/Animation/AnimationLocomotionLibrary/Source/Editor/Public/AnimationLocomotionLibraryEditor.h` (Public)


#### class `IAnimationLocomotionLibraryEditorModule`  
`class IAnimationLocomotionLibraryEditorModule : public IModuleInterface`  
_L8-10_
- inherits: `IModuleInterface`

### `Plugins/Animation/AnimationLocomotionLibrary/Source/Editor/Public/DistanceCurveModifier.h` (Public)


#### enum `EDistanceCurve_Axis`  
`enum class EDistanceCurve_Axis : uint8`  
_L12-21_
- reflection: `UENUM(BlueprintType)`
- desc: Axes to calculate the distance value from
- L14 _public enumerator_ `X`
- L15 _public enumerator_ `Y`
- L16 _public enumerator_ `Z`
- L17 _public enumerator_ `XY`
- L18 _public enumerator_ `XZ`
- L19 _public enumerator_ `YZ`
- L20 _public enumerator_ `XYZ`

#### class `UDistanceCurveModifier`  
`class UDistanceCurveModifier : public UAnimationModifier`  
_L28-62_
- reflection: `UCLASS()`
- inherits: `UAnimationModifier`
- desc: Extracts traveling distance information from root motion and bakes it to a curve. A negative value indicates distance remaining to a stop or pivot point. A positive value indicates distance traveled from a start point or from the beginning of the clip.
- L36 _public member_ `int32 SampleRate = 30;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ClampMin = "1"))` — Rate used to sample the animation.
- L40 _public member_ `FName CurveName = "Di` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Name for the generated curve.
- L44 _public member_ `float StopSpeedThreshold = 5.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta=(EditCondition="!bStopAtEnd"))` — Root motion speed must be below this threshold to be considered stopped.
- L48 _public member_ `EDistanceCurve_Axis Axis = EDistanceCurve_Axis::XY;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Axes to calculate the distance value from.
- L52 _public member_ `bool bStopAtEnd = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings)` — Root motion is considered to be stopped at the clip's end
- L54 _public prototype_ `virtual void OnApply_Implementation(UAnimSequence* Animation) override;`
- L55 _public prototype_ `virtual void OnRevert_Implementation(UAnimSequence* Animation) override;`
- L60 _private prototype_ `static float CalculateMagnitude(const FVector& Vector, EDistanceCurve_Axis Axis);` — Helper functions to calculate the magnitude of a vector only considering a specific axis or axes
- L61 _private prototype_ `static float CalculateMagnitudeSq(const FVector& Vector, EDistanceCurve_Axis Axis);`
