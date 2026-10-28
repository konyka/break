# Plugins / BlendSpaceMotionAnalysis

- module root: `Plugins/Animation/BlendSpaceMotionAnalysis/Source/BlendSpaceMotionAnalysis`
- headers: 3; symbols: 39
- symbol kinds: class=4, enum=2, enumerator=14, macro=1, member=10, prototype=8
- PrivateDependencyModuleNames: Core, CoreUObject, Engine, Persona

### `Plugins/Animation/BlendSpaceMotionAnalysis/Source/BlendSpaceMotionAnalysis/Public/BlendSpaceMotionAnalysis.h` (Public)


#### class `UCachedMotionAnalysisProperties`  
`class UCachedMotionAnalysisProperties : public UCachedAnalysisProperties`  
_L14-20_
- reflection: `UCLASS()`
- inherits: `UCachedAnalysisProperties`
- L18 _public member_ `EAnalysisRootMotionAxis RootMotionFunctionAxis = EAnalysisRootMotionAxis::Speed;`
- L19 _public member_ `EAnalysisLocomotionAxis LocomotionFunctionAxis = EAnalysisLocomotionAxis::Speed;`

#### class `FBlendSpaceMotionAnalysis`  
`class FBlendSpaceMotionAnalysis : public IModuleInterface`  
_L23-28_
- inherits: `IModuleInterface`
- L26 _public prototype_ `void StartupModule() override;`
- L27 _public prototype_ `void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API BLENDSPACEMOTIONANALYSIS_API`

### `Plugins/Animation/BlendSpaceMotionAnalysis/Source/BlendSpaceMotionAnalysis/Public/LocomotionAnalysis.h` (Public)


#### enum `EAnalysisLocomotionAxis`  
`enum class EAnalysisLocomotionAxis : uint8`  
_L10-19_
- reflection: `UENUM()`
- L12 _public enumerator_ `Speed`
- L13 _public enumerator_ `Direction`
- L14 _public enumerator_ `ForwardSpeed`
- L15 _public enumerator_ `RightwardSpeed`
- L16 _public enumerator_ `UpwardSpeed`
- L17 _public enumerator_ `ForwardSlope`
- L18 _public enumerator_ `RightwardSlope`

#### class `ULocomotionAnalysisProperties`  
`class ULocomotionAnalysisProperties : public UAnalysisProperties`  
_L23-49_
- reflection: `UCLASS()`
- inherits: `UAnalysisProperties`
- L27 _public prototype_ `void InitializeFromCache(TObjectPtr<UCachedAnalysisProperties> Cache) override;`
- L28 _public prototype_ `void MakeCache(TObjectPtr<UCachedAnalysisProperties>& Cache, UBlendSpace* BlendSpace) override;`
- L32 _public member_ `EAnalysisLocomotionAxis FunctionAxis = EAnalysisLocomotionAxis::Speed;` — `UPROPERTY(EditAnywhere, DisplayName = "Axis", Category = AnalysisProperties)` — Axis for the analysis function
- L36 _public member_ `FBoneSocketTarget PrimaryBoneSocket;` — `UPROPERTY(EditAnywhere, DisplayName = "Bone/Socket 1", Category = AnalysisProperties)` — The primary bone or socket used for analysis
- L40 _public member_ `FBoneSocketTarget SecondaryBoneSocket;` — `UPROPERTY(EditAnywhere, DisplayName = "Bone/Socket 2", Category = AnalysisProperties)` — The secondary bone or socket used for analysis
- L44 _public member_ `EAnalysisLinearAxis CharacterFacingAxis = EAnalysisLinearAxis::PlusY;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — World or bone/socket axis that specifies the character's facing direction
- L48 _public member_ `EAnalysisLinearAxis CharacterUpAxis = EAnalysisLinearAxis::PlusZ;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — World or bone/socket axis that specifies the character's up direction

#### Free symbols / members of external scopes

- L55 _prototype_ `bool CalculateLocomotion( float& Result, const UBlendSpace& BlendSpace, const ULocomotionAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` — Calculates the locomotion speed from the animation (which may be playrate scaled), according to the analysis properties.

### `Plugins/Animation/BlendSpaceMotionAnalysis/Source/BlendSpaceMotionAnalysis/Public/RootMotionAnalysis.h` (Public)


#### enum `EAnalysisRootMotionAxis`  
`enum class EAnalysisRootMotionAxis : uint8`  
_L10-19_
- reflection: `UENUM()`
- L12 _public enumerator_ `Speed`
- L13 _public enumerator_ `Direction`
- L14 _public enumerator_ `ForwardSpeed`
- L15 _public enumerator_ `RightwardSpeed`
- L16 _public enumerator_ `UpwardSpeed`
- L17 _public enumerator_ `ForwardSlope`
- L18 _public enumerator_ `RightwardSlope`

#### class `URootMotionAnalysisProperties`  
`class URootMotionAnalysisProperties : public ULinearAnalysisPropertiesBase`  
_L23-41_
- reflection: `UCLASS()`
- inherits: `ULinearAnalysisPropertiesBase`
- L27 _public prototype_ `void InitializeFromCache(TObjectPtr<UCachedAnalysisProperties> Cache) override;`
- L28 _public prototype_ `void MakeCache(TObjectPtr<UCachedAnalysisProperties>& Cache, UBlendSpace* BlendSpace) override;`
- L32 _public member_ `EAnalysisRootMotionAxis FunctionAxis = EAnalysisRootMotionAxis::Speed;` — `UPROPERTY(EditAnywhere, DisplayName = "Axis", Category = AnalysisProperties)` — Axis for the analysis function
- L36 _public member_ `EAnalysisLinearAxis CharacterFacingAxis = EAnalysisLinearAxis::PlusY;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — World or bone/socket axis that specifies the character's facing direction
- L40 _public member_ `EAnalysisLinearAxis CharacterUpAxis = EAnalysisLinearAxis::PlusZ;` — `UPROPERTY(EditAnywhere, Category = AnalysisProperties)` — World or bone/socket axis that specifies the character's up direction

#### Free symbols / members of external scopes

- L47 _prototype_ `bool CalculateRootMotion( float& Result, const UBlendSpace& BlendSpace, const URootMotionAnalysisProperties* AnalysisProperties, const UAnimSequence& Animation, const float RateScale);` — Calculates the root motion movement speed from the animation (which may be playrate scaled), according to the analysis properties.
