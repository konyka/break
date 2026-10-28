# Plugins / ProceduralVegetation

- module root: `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation`
- headers: 142; symbols: 4123
- symbol kinds: class=179, delegate=2, enum=53, enumerator=233, externvar=5, function=456, macro=46, member=1296, namespace=93, prototype=1217, struct=219, typedef=62, variable=262
- PrivateDependencyModuleNames: Chaos, ChaosCore, Core, CoreUObject, Engine, GeometryCore, GeometryFramework, ImageCore, Json, JsonUtilities, MeshConversionEngineTypes, MeshDescription, ModelingComponents, PCG, Projects, RHI, RenderCore, StaticMeshDescription
- PublicDependencyModuleNames: DynamicWind

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataAssets/ProceduralVegetationGrowerPreset.h` (Private)


#### class `UProceduralVegetationGrowerPreset`  
`class UProceduralVegetationGrowerPreset : public UDataAsset`  
_L10-18_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataAsset`
- L14 _public prototype_ `virtual void PostLoad() override;`
- L17 _public member_ `FPVGrowerParams GrowthParams;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=( ShowOnlyInnerProperties))`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataAssets/ProceduralVegetationGrowthDataAsset.h` (Private)


#### struct `FPVGrowthVariationInfo`  
`struct FPVGrowthVariationInfo`  
_L10-16_
- reflection: `USTRUCT()`
- L15 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = "Variations", meta=(Tooltip="Name of the variation. Matches the output pin label."))`

#### class `UProceduralVegetationGrowthDataAsset`  
`class UProceduralVegetationGrowthDataAsset : public UDataAsset`  
_L19-36_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataAsset`
- L25 _public member_ `TMap<FString, FManagedArrayCollection> Variants;` — `UPROPERTY()`
- L28 _public member_ `TArray<FPVGrowthVariationInfo> GrowthVariations;` — `UPROPERTY(VisibleAnywhere, Category = "Growth Data")`
- L32 _private member_ `FDirectoryPath JsonDirectoryPath;` — `UPROPERTY(EditAnywhere, Category="Internal", meta = (DevelopmentOnly))`
- L35 _private prototype_ `void UpdateDataAsset();` — `UFUNCTION(CallInEditor, Category="Internal", meta = (DevelopmentOnly))`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataAssets/ProceduralVegetationPlantProfileDataAsset.h` (Private)


#### struct `FPVPlantProfile`  
`struct FPVPlantProfile`  
_L9-17_
- reflection: `USTRUCT(BlueprintType)`
- L14 _public member_ `FString Name;` — `UPROPERTY(VisibleAnywhere, Category="PlantProfile")`
- L16 _public member_ `TArray<float> Points;` — `UPROPERTY(VisibleAnywhere, Category="PlantProfile")`

#### class `UProceduralVegetationPlantProfileDataAsset`  
`class UProceduralVegetationPlantProfileDataAsset : public UDataAsset`  
_L21-33_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UDataAsset`
- L26 _public member_ `TArray<FPVPlantProfile> Profiles;` — `UPROPERTY(VisibleAnywhere, Category="PlantProfiles")`
- L29 _public member_ `FFilePath ProfileFilePath;` — `UPROPERTY(EditAnywhere, Category="Internal", meta = (DevelopmentOnly))`
- L32 _public prototype_ `void Load();` — `UFUNCTION(CallInEditor, Category="Internal", meta = (DevelopmentOnly))`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataTypes/PVDistributionParams.h` (Private)


#### enum `EPVDistributionCondition`  
`enum class EPVDistributionCondition : uint8`  
_L13-24_
- reflection: `UENUM()`
- L15 _public enumerator_ `Light`
- L16 _public enumerator_ `Scale`
- L17 _public enumerator_ `UpAlignment`
- L18 _public enumerator_ `Tip`
- L19 _public enumerator_ `Health`
- L20 _public enumerator_ `Height`
- L21 _public enumerator_ `Generation`
- L22 _public enumerator_ `Count UMETA(Hidden)`
- L23 _public enumerator_ `None UMETA(Hidden)`

#### struct `FPVDistributionConditionInfluence`  
`struct FPVDistributionConditionInfluence`  
_L29-43_
- reflection: `USTRUCT()`
- L34 _public member_ `float Weight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (ClampMin = 0.0f, ClampMax = 1.0f, UIMin = 0.0f, UIMax = 1.0f, Tooltip = "How heavily this condition counts in the combined score.\n\nMultiplied with this condition's measured value. Use to weight one condition more than others."))`
- L37 _public member_ `float Offset = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (ClampMin = -1.0f, ClampMax = 1.0f, UIMin = -1.0f, UIMax = 1.0f, Tooltip = "Constant added to this condition's score.\n\nShifts the condition's contribution up or down. Useful to favor or penalize a condition."))`
- L39 _public function_ `FString ToString() const`

#### struct `FPVDistributionConditionParams`  
`struct FPVDistributionConditionParams`  
_L46-107_
- reflection: `USTRUCT()`
- L51 _public member_ `float CutoffThreshold = 0.3f;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (ClampMin = 0.0f, ClampMax = 1.0f, UIMin = 0.0f, UIMax = 1.0f, Tooltip = "Minimum combined condition score required for placement.\n\nEach active condition contributes a 0-1 score; scores are combined (weighted) and compared to this threshold. Instances below the threshold are skipped. Higher = stricter filtering; lower = more permissive."))`
- L54 _public member_ `int32 MinimumCandidates = 1;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (ClampMin = 1, ClampMax = 10, UIMin = 0, UIMax = 10, Tooltip = "Minimum instances to place per branch regardless of conditions.\n\nSafety net: even if conditions reject everything, this many instances are considered viable candidates on each branch. Prevents bare branches when filtering is too aggressive."))`
- L57 _public member_ `bool bActivateLight = false;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (PinHiddenByDefault, InlineEditConditionToggle, Tooltip = "Enable Light as a placement filter.\n\nWhen on, exposes the Light influence with 'Weight' and 'Offset' fields."))`
- L60 _public member_ `FPVDistributionConditionInfluence Light;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (EditCondition = "bActivateLight", Tooltip = "Light influence configuration: Weight + Offset."))`
- L63 _public member_ `bool bActivateScale = false;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (PinHiddenByDefault, InlineEditConditionToggle, Tooltip = "Enable Scale as a placement filter.\n\nWhen on, exposes the Scale influence with 'Weight' and 'Offset' fields."))`
- L66 _public member_ `FPVDistributionConditionInfluence Scale;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (EditCondition = "bActivateScale", Tooltip = "Scale influence configuration: Weight + Offset."))`
- L69 _public member_ `bool bActivateUpAlignment = false;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (PinHiddenByDefault, InlineEditConditionToggle, Tooltip = "Enable UpAlignment as a placement filter.\n\nWhen on, exposes the UpAlignment influence with 'Weight' and 'Offset' fields."))`
- L72 _public member_ `FPVDistributionConditionInfluence UpAlignment;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (EditCondition = "bActivateUpAlignment", Tooltip = "UpAlignment influence configuration: Weight + Offset."))`
- L75 _public member_ `bool bActivateTip = false;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (PinHiddenByDefault, InlineEditConditionToggle, Tooltip = "Enable Tip as a placement filter.\n\nWhen on, exposes the Tip influence with 'Weight' and 'Offset' fields."))`
- L78 _public member_ `FPVDistributionConditionInfluence Tip;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (EditCondition = "bActivateTip", Tooltip = "Tip influence configuration: Weight + Offset."))`
- L81 _public member_ `bool bActivateHealth = false;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (PinHiddenByDefault, InlineEditConditionToggle, Tooltip = "Enable Health as a placement filter.\n\nWhen on, exposes the Health influence with 'Weight' and 'Offset' fields."))`
- L84 _public member_ `FPVDistributionConditionInfluence Health;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (EditCondition = "bActivateHealth", Tooltip = "Health influence configuration: Weight + Offset."))`
- L87 _public member_ `bool bActivateHeight = false;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (PinHiddenByDefault, InlineEditConditionToggle, Tooltip = "Enable Height as a placement filter.\n\nWhen on, exposes the Height influence with 'Weight' and 'Offset' fields."))`
- L90 _public member_ `FPVDistributionConditionInfluence Height;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (EditCondition = "bActivateHeight", Tooltip = "Height influence configuration: Weight + Offset."))`
- L93 _public member_ `bool bActivateGeneration = false;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (PinHiddenByDefault, InlineEditConditionToggle, Tooltip = "Enable Generation as a placement filter.\n\nWhen on, exposes the Generation influence with 'Weight' and 'Offset' fields."))`
- L96 _public member_ `FPVDistributionConditionInfluence Generation;` — `UPROPERTY(EditAnywhere, Category = "ConditionSettings", meta = (EditCondition = "bActivateGeneration", Tooltip = "Generation influence configuration: Weight + Offset."))`
- L98 _public prototype_ `bool HasActiveCondition() const;`
- L100 _public prototype_ `bool IsActiveCondition(const EPVDistributionCondition InCondition) const;`
- L102 _public prototype_ `void SetConditionState(const EPVDistributionCondition InCondition, const bool InNewState);`
- L104 _public prototype_ `FPVDistributionConditionInfluence* GetInfluence(const EPVDistributionCondition InCondition);`
- L106 _public prototype_ `bool GetInfluence(const EPVDistributionCondition InCondition, FPVDistributionConditionInfluence& OutSettings) const;`

#### enum `EPVAimVectorBlendAttribute`  
`enum class EPVAimVectorBlendAttribute : uint8`  
_L110-117_
- reflection: `UENUM()`
- L112 _public enumerator_ `PlantGradient`
- L113 _public enumerator_ `PlantGradientNormalized`
- L114 _public enumerator_ `BranchGradient`
- L115 _public enumerator_ `BranchGradientNormalized`
- L116 _public enumerator_ `WorldUpDot`

#### enum `EPVAimVectorType`  
`enum class EPVAimVectorType : uint8`  
_L120-127_
- reflection: `UENUM()`
- L122 _public enumerator_ `BranchUpFlatten`
- L123 _public enumerator_ `AxisFlatten`
- L124 _public enumerator_ `AxisAim`
- L125 _public enumerator_ `LightOptimal`
- L126 _public enumerator_ `LightAvoid`

#### struct `FPVAimVectorSettings`  
`struct FPVAimVectorSettings`  
_L130-168_
- reflection: `USTRUCT()`
- L134 _public function_ `FPVAimVectorSettings()`
- L140 _public member_ `bool bAffectTip = false;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(Tooltip="Apply this aim vector to the branch tip too."))`
- L143 _public member_ `EPVAimVectorBlendAttribute BlendAttribute = EPVAimVectorBlendAttribute::PlantGradient;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(Tooltip="What attribute drives the blend ramp.\n\nPicks gradient that drives the ramp's X axis (plant gradient, branch gradient, world-up dot, etc.)."))`
- L146 _public member_ `bool bDualVectors = false;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(Tooltip="Blend between two aim vectors using the ramp.\n\nWhen enabled, exposes Vector1/Vector2 configuration. When disabled, only Vector2 is used and the previous entry output represents Vector1."))`
- L149 _public member_ `EPVAimVectorType Vector1 = EPVAimVectorType::BranchUpFlatten;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(EditCondition="bDualVectors", EditConditionHides, Tooltip="Aim vector type for the blend's start.\n\nChoose from BranchUpFlatten, AxisFlatten, AxisAim, LightOptimal, LightAvoid."))`
- L152 _public member_ `FVector3f Vector1Axis = FVector3f::UpVector;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(DisplayName="Vector 1 Axis", EditCondition="bDualVectors && (Vector1 == EPVAimVectorType::AxisFlatten || Vector1 == EPVAimVectorType::AxisAim)", EditConditionHides, Tooltip="Custom axis vector for AxisFlatten / AxisAim modes."))`
- L155 _public member_ `float Vector1Strength = 1.0f;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(DisplayName="Vector 1 Strength", ClampMin=0.0f, ClampMax=1.0f, EditCondition="bDualVectors", EditConditionHides, Tooltip="How strongly this vector contributes to the final aim.\n\n0 = ignored. 1 = full influence. Combine with the ramp to vary strength along the plant."))`
- L158 _public member_ `EPVAimVectorType Vector2 = EPVAimVectorType::BranchUpFlatten;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(Tooltip="Aim vector type for the blend's end.\n\nChoose from BranchUpFlatten, AxisFlatten, AxisAim, LightOptimal, LightAvoid."))`
- L161 _public member_ `FVector3f Vector2Axis = FVector3f::UpVector;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(DisplayName="Vector 2 Axis", EditCondition="Vector2 == EPVAimVectorType::AxisFlatten || Vector2 == EPVAimVectorType::AxisAim", EditConditionHides, Tooltip="Custom axis vector for AxisFlatten / AxisAim modes."))`
- L164 _public member_ `float Vector2Strength = 1.0f;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(DisplayName="Vector 2 Strength", ClampMin=0.0f, ClampMax=1.0f, Tooltip="How strongly this vector contributes to the final aim.\n\n0 = ignored. 1 = full influence. Combine with the ramp to vary strength along the plant."))`
- L167 _public member_ `FPVFloatRamp VectorRamp;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve that blends from Vector1 (at ramp 0) to Vector2 (at ramp 1)."))`

#### enum `EPVFaceVectorType`  
`enum class EPVFaceVectorType : uint8`  
_L171-179_
- reflection: `UENUM()`
- L173 _public enumerator_ `Apical`
- L174 _public enumerator_ `Branch`
- L175 _public enumerator_ `AxisFlatten`
- L176 _public enumerator_ `AxisAim`
- L177 _public enumerator_ `LightOptimal`
- L178 _public enumerator_ `LightAvoid`

#### struct `FPVFaceVectorSettings`  
`struct FPVFaceVectorSettings`  
_L182-220_
- reflection: `USTRUCT()`
- L186 _public function_ `FPVFaceVectorSettings()`
- L192 _public member_ `bool bAffectTip = false;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(Tooltip="Apply this face vector to the branch tip too."))`
- L195 _public member_ `EPVAimVectorBlendAttribute BlendAttribute = EPVAimVectorBlendAttribute::PlantGradient;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(Tooltip="What attribute drives the blend ramp.\n\nPicks gradient that drives the ramp's X axis (plant gradient, branch gradient, world-up dot, etc.)."))`
- L198 _public member_ `bool bDualVectors = false;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(Tooltip="Blend between two face vectors using the ramp.\n\nWhen enabled, exposes Vector1/Vector2 configuration. When disabled, only Vector2 is used and the previous entry output represents Vector1."))`
- L201 _public member_ `EPVFaceVectorType Vector1 = EPVFaceVectorType::Apical;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(EditCondition="bDualVectors", EditConditionHides, Tooltip="Face vector type for the blend's start.\n\nChoose from Apical, Branch, AxisFlatten, AxisAim, LightOptimal, LightAvoid."))`
- L204 _public member_ `FVector3f Vector1Axis = FVector3f::UpVector;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(DisplayName="Vector 1 Axis", EditCondition="bDualVectors && (Vector1 == EPVFaceVectorType::AxisFlatten || Vector1 == EPVFaceVectorType::AxisAim)", EditConditionHides, Tooltip="Custom axis vector for AxisFlatten / AxisAim modes."))`
- L207 _public member_ `float Vector1Strength = 1.0f;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(DisplayName="Vector 1 Strength", ClampMin=0.0f, ClampMax=1.0f, EditCondition="bDualVectors", EditConditionHides, Tooltip="How strongly this vector contributes to the final face direction.\n\n0 = ignored. 1 = full influence. Combine with the ramp to vary strength along the plant."))`
- L210 _public member_ `EPVFaceVectorType Vector2 = EPVFaceVectorType::Branch;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(Tooltip="Face vector type for the blend's end.\n\nChoose from Apical, Branch, AxisFlatten, AxisAim, LightOptimal, LightAvoid."))`
- L213 _public member_ `FVector3f Vector2Axis = FVector3f::UpVector;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(DisplayName="Vector 2 Axis", EditCondition="Vector2 == EPVFaceVectorType::AxisFlatten || Vector2 == EPVFaceVectorType::AxisAim", EditConditionHides, Tooltip="Custom axis vector for AxisFlatten / AxisAim modes."))`
- L216 _public member_ `float Vector2Strength = 1.0f;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(ClampMin=0.0f, ClampMax=1.0f, DisplayName="Vector 2 Strength", Tooltip="How strongly this vector contributes to the final face direction.\n\n0 = ignored. 1 = full influence. Combine with the ramp to vary strength along the plant."))`
- L219 _public member_ `FPVFloatRamp VectorRamp;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve that blends from Vector1 (at ramp 0) to Vector2 (at ramp 1)."))`

#### struct `FPVDistributionAimVectorSettings`  
`struct FPVDistributionAimVectorSettings`  
_L223-232_
- reflection: `USTRUCT()`
- L228 _public member_ `bool bAutoAlignEnd = true;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(Tooltip="Automatically align the foliage to the branch end direction on tips.\n\nWhen enabled, foliage placed on the tip aligns with the branch tip's direction. Avoids unintended tip orientations."))`
- L231 _public member_ `TArray<FPVAimVectorSettings> AimVectors;` — `UPROPERTY(EditAnywhere, Category="AimVectorSettings", meta=(Tooltip="List of aim-vector strategies for orienting foliage.\n\nAim vector is the direction the leaf should be pointing, root to tip. Each entry blends one or two aim vectors based on a ramp. Most cases need only one entry. Use multiple to layer different orientations (e.g. tip-aiming for the lower half, light-seeking for the upper half). By default with a single entry it blends against the basic phyllotaxy."))`

#### struct `FPVDistributionFaceVectorSettings`  
`struct FPVDistributionFaceVectorSettings`  
_L235-244_
- reflection: `USTRUCT()`
- L240 _public member_ `bool bAutoAlignEnd = true;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(Tooltip="Automatically align the foliage face to the branch end direction on tips.\n\nWhen enabled, foliage placed on the tip aligns with the branch tip's direction. Avoids unintended tip orientations."))`
- L243 _public member_ `TArray<FPVFaceVectorSettings> FaceVectors;` — `UPROPERTY(EditAnywhere, Category="FaceVectorSettings", meta=(Tooltip="List of face-vector strategies for orienting foliage.\n\nFace vector governs the direction the foliage should be facing (orthogonal to the aim vector). Each entry blends one or two face vectors based on a ramp. Most cases need only one entry. Use multiple to layer different orientations."))`

#### enum `EPVRollPitchYawMode`  
`enum class EPVRollPitchYawMode : uint8`  
_L247-252_
- reflection: `UENUM()`
- L249 _public enumerator_ `Roll UMETA(DisplayName="Roll")`
- L250 _public enumerator_ `Pitch UMETA(DisplayName="Pitch")`
- L251 _public enumerator_ `Yaw UMETA(DisplayName="Yaw")`

#### struct `FPVRollPitchYawSettings`  
`struct FPVRollPitchYawSettings`  
_L255-270_
- reflection: `USTRUCT()`
- L260 _public member_ `EPVRollPitchYawMode Mode = EPVRollPitchYawMode::Roll;` — `UPROPERTY(EditAnywhere, Category="RollPitchYawSettings", meta=(Tooltip="Which axis to randomize: Roll, Pitch, or Yaw."))`
- L263 _public member_ `float MinStrength = 0.0f;` — `UPROPERTY(EditAnywhere, Category="RollPitchYawSettings", meta=(ClampMin=-1.0f, ClampMax=1.0f, Tooltip="Minimum random range mapped to a rotation angle.\n\n0 to 1 maps to 0° to 360°. Use small ranges for subtle jitter; ±1 for full random rotation."))`
- L266 _public member_ `float MaxStrength = 0.0f;` — `UPROPERTY(EditAnywhere, Category="RollPitchYawSettings", meta=(ClampMin=-1.0f, ClampMax=1.0f, Tooltip="Maximum random range mapped to a rotation angle.\n\n0 to 1 maps to 0° to 360°. Use small ranges for subtle jitter; ±1 for full random rotation."))`
- L269 _public member_ `int32 RandomSeed = 123456;` — `UPROPERTY(EditAnywhere, Category="RollPitchYawSettings", meta=(Tooltip="Seed for this random rotation.\n\nChange to vary the random pattern without changing strength."))`

#### struct `FPVDistributionRollPitchYawSettings`  
`struct FPVDistributionRollPitchYawSettings`  
_L273-279_
- reflection: `USTRUCT()`
- L278 _public member_ `TArray<FPVRollPitchYawSettings> RollPitchYaw;` — `UPROPERTY(EditAnywhere, Category="RollPitchYawSettings", meta=(Tooltip="List of random rotation operations applied after aim/face.\n\nEach entry adds a random Roll, Pitch, or Yaw rotation. Use multiple for layered jitter (e.g. roll for spin, then pitch for tilt)."))`

#### struct `FPVDistributionVectorParams`  
`struct FPVDistributionVectorParams`  
_L282-294_
- reflection: `USTRUCT()`
- L287 _public member_ `FPVDistributionAimVectorSettings AimVectorSettings;` — `UPROPERTY(EditAnywhere, Category="Vector Settings")`
- L290 _public member_ `FPVDistributionFaceVectorSettings FaceVectorSettings;` — `UPROPERTY(EditAnywhere, Category="Vector Settings")`
- L293 _public member_ `FPVDistributionRollPitchYawSettings RollPitchYawSettings;` — `UPROPERTY(EditAnywhere, Category="Vector Settings")`

#### enum `EPVDistributionSettingsMode`  
`enum class EPVDistributionSettingsMode : uint8`  
_L297-301_
- reflection: `UENUM()`
- L299 _public enumerator_ `ParametricSettings UMETA(DisplayName="Use Parametric Settings")`
- L300 _public enumerator_ `HormoneBasedSettings UMETA(DisplayName="Use Hormone Based Settings")`

#### struct `FPVHormoneDistributionSettings`  
`struct FPVHormoneDistributionSettings`  
_L304-327_
- reflection: `USTRUCT()`
- L308 _public function_ `FPVHormoneDistributionSettings()`
- L314 _public member_ `float EthyleneThreshold = 0.85f;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Branch points above this ethylene level keep their foliage.\n\nHigher Threshold → more buds/branches retained, making the plant foliage travel further down the trunk. Lower Threshold → fewer retained, concentrates foliage more at tips. Drives the natural look of where foliage is and isn't."))`
- L317 _public member_ `float InstanceSpacing = 0.3f;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Minimum distance between placed foliage instances.\n\nHigher spacing yields a more open distribution; lower spacing allows denser placement. Combine with InstanceSpacingRamp to vary along the plant."))`
- L320 _public member_ `FPVFloatRamp InstanceSpacingRamp;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings", meta=(PCG_Overridable, XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve that varies instance spacing along plant height.\n\nX = normalized gradient along the plant, 0 at root and 1 at tips. Y = spacing multiplier. Use to reduce or increase density."))`
- L323 _public member_ `float InstanceSpacingRampEffect = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Blend strength between base spacing and the ramp curve.\n\nLower values favor the base spacing (subtle ramp effect). Higher values apply the ramp more strongly. Use to subtly tune the ramp's influence."))`
- L326 _public member_ `int32 MaxPerBranch = -1;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings", meta=(PCG_Overridable, ClampMin=-1, ClampMax=1000, Tooltip="Cap on foliage instances per branch (-1 = no cap).\n\nUseful to prevent overcrowding on very long branches. -1 disables the cap."))`

#### struct `FPVHormoneScaleSettings`  
`struct FPVHormoneScaleSettings`  
_L330-359_
- reflection: `USTRUCT()`
- L334 _public function_ `FPVHormoneScaleSettings()`
- L340 _public member_ `float BaseScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, UIMin=0.0f, UIMax=5.0f, Tooltip="Base uniform scale for placed foliage.\n\nSets the base uniform scale applied to each instance before randomness and ramps. Increase to enlarge all instances proportionally."))`
- L343 _public member_ `float BranchScaleImpact = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="How much branch size affects foliage size.\n\n0 = scale independent of branch. 1 = larger branches receive larger foliage. Useful for natural species variation."))`
- L346 _public member_ `float MinScale = 0.5f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, UIMin=0.0f, UIMax=5.0f, Tooltip="Lower clamp for final foliage scale.\n\nClamps the final computed scale so it never goes below this value. Use to prevent tiny, hard-to-see instances."))`
- L349 _public member_ `float MaxScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, UIMin=0.0f, UIMax=5.0f, Tooltip="Upper clamp for final foliage scale.\n\nClamps the final computed scale so it never exceeds this value. Use to cap unusually large instances for visual consistency."))`
- L352 _public member_ `float RandomScaleMin = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, UIMin=0.0f, UIMax=5.0f, Tooltip="Lower bound for per-instance size variation."))`
- L355 _public member_ `float RandomScaleMax = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=1.0f, UIMin=1.0f, UIMax=5.0f, Tooltip="Upper bound for per-instance size variation."))`
- L358 _public member_ `FPVFloatRamp ScaleRamp;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve that varies foliage scale along plant height."))`

#### struct `FPVHormoneAngleSettings`  
`struct FPVHormoneAngleSettings`  
_L362-385_
- reflection: `USTRUCT()`
- L366 _public function_ `FPVHormoneAngleSettings()`
- L372 _public member_ `bool OverrideAxilAngle = true;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, Tooltip="Use a custom axil angle instead of the species default.\n\nWhen enabled, uses AxilAngle and the AxilAngleRamp settings to tilt foliage. When off, foliage uses the orientation inherited from the Grower's phyllotaxy."))`
- L375 _public member_ `float AxilAngle = 35.0f;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, EditCondition="OverrideAxilAngle", ClampMin = -90.0f, ClampMax=90.0f, UIMin=-90.0f, UIMax=90.0f, Tooltip="Base tilt from the parent axis.\n\nSets the base axil angle in degrees — the tilt of the instance relative to the parent branch's direction. Acts as the bound when used with a ramp."))`
- L378 _public member_ `FPVFloatRamp AxilAngleRamp;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(EditCondition="OverrideAxilAngle", XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=-1.0f, YAxisMax=1.0f, Tooltip="Curve that varies the axil angle along plant height."))`
- L381 _public member_ `float AxilAngleRampUpperValue = 45.0f;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, EditCondition="OverrideAxilAngle", ClampMin=0.0f, ClampMax=90.0f, UIMin=0.0f, UIMax=90.0f, Tooltip="Maximum angle reached when the ramp evaluates to 1."))`
- L384 _public member_ `float AxilAngleRampEffect = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, EditCondition="OverrideAxilAngle", ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Blend strength of the axil angle ramp."))`

#### struct `FPVHormonePhyllotaxySettings`  
`struct FPVHormonePhyllotaxySettings`  
_L388-415_
- reflection: `USTRUCT()`
- L393 _public member_ `bool ResetPhyllotaxy = false;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, Tooltip="Restart the phyllotaxy pattern at each branch.\n\nWhen enabled, each branch's foliage starts the phyllotaxy pattern from rotation 0 in relation to the branch up direction. When disabled the rotation is inherited from the parent and carried over to the branches."))`
- L396 _public member_ `EPhyllotaxyType PhyllotaxyType = EPhyllotaxyType::Alternate;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, Tooltip="Foliage arrangement pattern around the stem.\n\nAlternate (180° flip), Opposite (paired), Whorled (3+ at same node), Spiral (continuous rotation)."))`
- L399 _public member_ `EPhyllotaxyFormation PhyllotaxyFormation = EPhyllotaxyFormation::Octastichous;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, EditCondition="PhyllotaxyType == EPhyllotaxyType::Spiral", EditConditionHides, Tooltip="Spiral sub-formation angle.\n\nThis is the number of branches that occur in a full 360° revolve. E.g. Distichous is two and by extension; Distichous (180°), Tristichous (120°), Pentastichous (144°), Octastichous (135°), Parastichous (0°)."))`
- L402 _public member_ `int32 MinimumNodeBuds = 2;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, EditCondition="PhyllotaxyType == EPhyllotaxyType::Whorled", EditConditionHides, ClampMin=1, ClampMax=10, UIMin=1, UIMax=10, Tooltip="Minimum buds per node for Whorled phyllotaxy.\n\nSets the lower bound on instances at each node. Guarantees at least this many. Should be ≤ MaximumNodeBuds."))`
- L405 _public member_ `int32 MaximumNodeBuds = 3;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, EditCondition="PhyllotaxyType == EPhyllotaxyType::Whorled", EditConditionHides, ClampMin=1, ClampMax=10, UIMin=1, UIMax=10, Tooltip="Maximum buds per node for Whorled phyllotaxy.\n\nCaps the number of instances spawned at each node. Use in unison with MinimumNodeBuds to set upper and lower bounds."))`
- L408 _public member_ `bool bSingleBudTip = true;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, Tooltip="Place a single foliage instance at each branch tip.\n\nWhen enabled, the branch tip gets exactly one foliage instance. When disabled, the tip gets the same Min/Max bud count as other nodes."))`
- L411 _public member_ `float PhyllotaxyAdditionalAngle = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=360.0f, UIMin=0.0f, UIMax=360.0f, Tooltip="Extra rotation added to each node's phyllotaxy angle.\n\nAdds to the base angle picked by 'PhyllotaxyType'/'PhyllotaxyFormation'. Use to break perfect regularity, or for Parastichous patterns where base = 0°."))`
- L414 _public member_ `float PhyllotaxyOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=360.0f, UIMin=0.0f, UIMax=360.0f, Tooltip="Initial rotation of the phyllotaxy pattern.\n\nPhase-shifts the entire pattern. Useful when the default rotation doesn't align with how your scene's other plants look."))`

#### struct `FPVDistributionHormoneBasedParams`  
`struct FPVDistributionHormoneBasedParams`  
_L418-433_
- reflection: `USTRUCT()`
- L423 _public member_ `FPVHormoneDistributionSettings DistributionSettings;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings", meta=(ShowOnlyInnerProperties))`
- L426 _public member_ `FPVHormoneScaleSettings ScaleSettings;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(ShowOnlyInnerProperties))`
- L429 _public member_ `FPVHormoneAngleSettings AngleSettings;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(ShowOnlyInnerProperties))`
- L432 _public member_ `FPVHormonePhyllotaxySettings PhyllotaxySettings;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(ShowOnlyInnerProperties))`

#### enum `EPVDistributionBasis`  
`enum class EPVDistributionBasis : uint8`  
_L437-441_
- reflection: `UENUM()`
- L439 _public enumerator_ `Plant UMETA(DisplayName="Plant")`
- L440 _public enumerator_ `Branch UMETA(DisplayName="Branch")`

#### struct `FPVParametricSpacingSettings`  
`struct FPVParametricSpacingSettings`  
_L444-482_
- reflection: `USTRUCT()`
- L448 _public function_ `FPVParametricSpacingSettings()`
- L454 _public member_ `int32 BranchDensity = 45;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, UIMin=0, UIMax=100, ClampMin=0, ClampMax=10000, Tooltip="Number of foliage instances per asset.\n\nTotal instances scattered throughout the entire tree. Higher = denser foliage. Combine with 'RelativeStart' and 'RelativeEnd' to limit the range, and with 'SpacingRamp' to vary density along the branch or plant."))`
- L457 _public member_ `float RelativeStart = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Fraction along the branch where placement begins.\n\n0 = start from the branch base. 0.5 = start at the midpoint. Useful for plants that have bare lower stems or for separating the distribution into multiple distributors in a chain."))`
- L460 _public member_ `float RelativeEnd = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Fraction along the branch where placement ends.\n\n1 = continues to the branch tip. Lower values stop placement before the tip — useful when you want clean tips without foliage."))`
- L463 _public member_ `bool LimitStartGeneration = false;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, Tooltip="Restrict placement to branches above a starting generation.\n\nWhen on, only branches at or beyond 'StartGeneration' receive foliage. Use to keep the trunk bare while putting foliage on side branches."))`
- L467 _public member_ `int32 StartGeneration = 0;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, ClampMin=0, ClampMax=10, EditCondition="LimitStartGeneration", EditConditionHides, Tooltip="First generation to receive foliage.\n\n1 = trunk. 2 = first side branches. Higher numbers exclude lower-order branches from foliage placement."))`
- L470 _public member_ `bool LimitEndGeneration = false;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, Tooltip="Restrict placement to branches below an ending generation.\n\nWhen on, foliage stops at 'EndGeneration'. Use to keep the finest twigs free of foliage."))`
- L474 _public member_ `int32 EndGeneration = 0;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, ClampMin=0, ClampMax=10, EditCondition="LimitEndGeneration", EditConditionHides, Tooltip="Last generation to receive foliage.\n\nHigher numbers include more generations. 10 = effectively unlimited."))`
- L477 _public member_ `EPVDistributionBasis SpacingBasis = EPVDistributionBasis::Plant;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, Tooltip="Whether the spacing ramp is normalized to the plant or to each branch.\n\nPlant: ramp covers the whole plant from 0 at the root and 1 at each tip. Branch: ramp covers each branch's length individually."))`
- L481 _public member_ `FPVFloatRamp SpacingRamp;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(PCG_Overridable, XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve that varies instance spacing along the plant or branch.\n\nX = position along the spacing basis. Y = relative output position. Typical use case is leaving start and end as default and add a keypoint in between to concentrate the density of foliage either around the start and end."))`

#### struct `FPVParametricPhyllotaxySettings`  
`struct FPVParametricPhyllotaxySettings`  
_L485-519_
- reflection: `USTRUCT()`
- L491 _public member_ `bool ResetPhyllotaxy = false;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, Tooltip="Restart the phyllotaxy pattern at each branch.\n\nWhen enabled, each branch's foliage starts the phyllotaxy pattern from rotation 0 in relation to the branch up direction. When disabled the rotation is inherited from the parent and carried over to the branches."))`
- L495 _public member_ `EPhyllotaxyType PhyllotaxyType = EPhyllotaxyType::Spiral;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, Tooltip="Foliage arrangement pattern around the stem.\n\nAlternate (180° flip), Opposite (paired), Whorled (3+ at same node), Spiral (continuous rotation)."))`
- L499 _public member_ `EPhyllotaxyFormation PhyllotaxyFormation = EPhyllotaxyFormation::Octastichous;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, EditCondition="PhyllotaxyType == EPhyllotaxyType::Spiral", EditConditionHides, Tooltip="Spiral sub-formation angle.\n\nThis is the number of branches that occur in a full 360° revolve. E.g. Distichous is two and by extension; Distichous (180°), Tristichous (120°), Pentastichous (144°), Octastichous (135°), Parastichous (0°)."))`
- L503 _public member_ `int32 MinimumNodeBuds = 2;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, EditCondition="PhyllotaxyType == EPhyllotaxyType::Whorled", EditConditionHides, ClampMin=1, ClampMax=10, UIMin=1, UIMax=10, Tooltip="Minimum buds per node for Whorled phyllotaxy.\n\nSets the lower bound on instances at each node. Guarantees at least this many. Should be ≤ MaximumNodeBuds."))`
- L507 _public member_ `int32 MaximumNodeBuds = 3;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, EditCondition="PhyllotaxyType == EPhyllotaxyType::Whorled", EditConditionHides, ClampMin=1, ClampMax=10, UIMin=1, UIMax=10, Tooltip="Maximum buds per node for Whorled phyllotaxy.\n\nCaps the number of instances spawned at each node. Use in unison with MinimumNodeBuds to set upper and lower bounds."))`
- L510 _public member_ `bool bSingleBudTip = true;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, Tooltip="Place a single foliage instance at each branch tip.\n\nWhen enabled, the branch tip gets exactly one foliage instance. When disabled, the tip gets the same Min/Max bud count as other nodes."))`
- L514 _public member_ `float PhyllotaxyAdditionalAngle = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=360.0f, UIMin=0.0f, UIMax=360.0f, Tooltip="Extra rotation added to each node's phyllotaxy angle.\n\nAdds to the base angle picked by 'PhyllotaxyType'/'PhyllotaxyFormation'. Use to break perfect regularity, or for Parastichous patterns where base = 0°."))`
- L518 _public member_ `float PhyllotaxyOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=360.0f, UIMin=0.0f, UIMax=360.0f, Tooltip="Initial rotation of the phyllotaxy pattern.\n\nPhase-shifts the entire pattern. Useful when the default rotation doesn't align with how your scene's other plants look."))`

#### struct `FPVParametricAngleSettings`  
`struct FPVParametricAngleSettings`  
_L522-549_
- reflection: `USTRUCT()`
- L526 _public function_ `FPVParametricAngleSettings()`
- L532 _public member_ `float Rotation = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=360.0f, Tooltip="Base rotation around the branch axis.\n\nSpins each foliage instance around its parent branch's axis. Use to orient leaves in a specific direction relative to the branch."))`
- L535 _public member_ `float AxilAngle = 35.0f;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, ClampMin=-90.0f, ClampMax=90.0f, UIMin = -90.0f, UIMax = 90.0f, Tooltip="Base tilt of foliage relative to the branch direction.\n\n0° = foliage points along the branch (parallel). 90° = foliage sticks straight out (perpendicular). Combine with 'AxilAngleRamp' for per-position variation."))`
- L538 _public member_ `float RandomizeAxilAngleMinimum = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, ClampMin=-45.0f, ClampMax=0.0f, Tooltip="Minimum random tilt added to each instance.\n\nLower bound of random variation in axil angle per instance. Use to break uniformity."))`
- L541 _public member_ `float RandomizeAxilAngleMaximum = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=45.0f, Tooltip="Maximum random tilt added to each instance.\n\nUpper bound of random variation. Combine with the Minimum for symmetric jitter (e.g. -5 to +5)."))`
- L544 _public member_ `EPVDistributionBasis AxilAngleRampBasis = EPVDistributionBasis::Plant;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, Tooltip="Whether the axil angle ramp is normalized to plant or branch.\n\nPlant: ramp spans the full plant where it's 0 at root and one at all tips. Branch: ramp spans each branch individually."))`
- L548 _public member_ `FPVFloatRamp AxilAngleRamp;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(PCG_Overridable, XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=-1.0f, YAxisMax=1.0f, Tooltip="Curve that varies axil angle along the plant or branch.\n\nX = position. Y = -1 to 1, mapped into the angle range. Use to make foliage have a steeper angle at branch tips, or to droop near the base."))`

#### struct `FPVParametricScaleSettings`  
`struct FPVParametricScaleSettings`  
_L552-579_
- reflection: `USTRUCT()`
- L556 _public function_ `FPVParametricScaleSettings()`
- L562 _public member_ `EPVDistributionBasis ScaleRampBasis = EPVDistributionBasis::Plant;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, Tooltip="Whether the scale ramp is normalized to plant or branch."))`
- L565 _public member_ `float BaseScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=10.0f, Tooltip="Base uniform scale multiplier for all foliage.\n\nMultiplier applied to every instance before randomness and ramps. 1 = use the mesh's authored size; 0.5 = half-size; 2 = double-size."))`
- L568 _public member_ `float BranchScaleImpact = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, EditCondition="ScaleRampBasis == EPVDistributionBasis::Branch", EditConditionHides, Tooltip="How much relative branch size affects foliage size.\n\n0 = foliage size independent of relative branch size. 1 = large branches get large foliage, shorter branches get small foliage. Useful for realistic species where bigger branches support bigger leaves."))`
- L571 _public member_ `float RandomizeScaleMinimum = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Minimum random scale multiplier per instance."))`
- L574 _public member_ `float RandomizeScaleMaximum = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, ClampMin=1.0f, ClampMax=2.0f, Tooltip="Maximum random scale multiplier per instance."))`
- L578 _public member_ `FPVFloatRamp ScaleRamp;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(PCG_Overridable, XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve that varies foliage scale along the plant or branch.\n\nX = position. Y = scale multiplier. Use to make foliage smaller near branch tips or larger near the trunk."))`

#### struct `FPVDistributionParametricParams`  
`struct FPVDistributionParametricParams`  
_L582-597_
- reflection: `USTRUCT()`
- L587 _public member_ `FPVParametricSpacingSettings SpacingSettings;` — `UPROPERTY(EditAnywhere, Category="Spacing Settings", meta=(ShowOnlyInnerProperties))`
- L590 _public member_ `FPVParametricPhyllotaxySettings PhyllotaxySettings;` — `UPROPERTY(EditAnywhere, Category="Phyllotaxy Settings", meta=(ShowOnlyInnerProperties))`
- L593 _public member_ `FPVParametricAngleSettings AngleSettings;` — `UPROPERTY(EditAnywhere, Category="Angle Settings", meta=(ShowOnlyInnerProperties))`
- L596 _public member_ `FPVParametricScaleSettings ScaleSettings;` — `UPROPERTY(EditAnywhere, Category="Scale Settings", meta=(ShowOnlyInnerProperties))`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataTypes/PVDistributionSettingsData.h` (Private)


#### struct `FPVDataTypeInfoDistributionParametricSettings`  
`struct FPVDataTypeInfoDistributionParametricSettings : public FPCGDataTypeInfo`  
_L28-37_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L32 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L35 _public function_ `virtual bool Hidden() const override`

#### class `UPVDistributionParametricSettingsData`  
`class UPVDistributionParametricSettingsData : public UPCGData`  
_L40-51_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L45 _public member_ `FPVDistributionParametricParams Params;`
- L49 _public prototype_ `PV_DISTRIBUTION_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoDistributionHormoneBasedSettings`  
`struct FPVDataTypeInfoDistributionHormoneBasedSettings : public FPCGDataTypeInfo`  
_L54-63_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L58 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L61 _public function_ `virtual bool Hidden() const override`

#### class `UPVDistributionHormoneBasedSettingsData`  
`class UPVDistributionHormoneBasedSettingsData : public UPCGData`  
_L66-77_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L71 _public member_ `FPVDistributionHormoneBasedParams Params;`
- L75 _public prototype_ `PV_DISTRIBUTION_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoDistributionVectorSettings`  
`struct FPVDataTypeInfoDistributionVectorSettings : public FPCGDataTypeInfo`  
_L80-89_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L84 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L87 _public function_ `virtual bool Hidden() const override`

#### class `UPVDistributionVectorSettingsData`  
`class UPVDistributionVectorSettingsData : public UPCGData`  
_L92-103_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L97 _public member_ `FPVDistributionVectorParams Params;`
- L101 _public prototype_ `PV_DISTRIBUTION_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoDistributionConditionSettings`  
`struct FPVDataTypeInfoDistributionConditionSettings : public FPCGDataTypeInfo`  
_L106-115_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L110 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L113 _public function_ `virtual bool Hidden() const override`

#### class `UPVDistributionConditionSettingsData`  
`class UPVDistributionConditionSettingsData : public UPCGData`  
_L118-129_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L123 _public member_ `FPVDistributionConditionParams Params;`
- L127 _public prototype_ `PV_DISTRIBUTION_SETTINGS_OVERRIDE_CRC(Params);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define PV_DISTRIBUTION_SETTINGS_OVERRIDE_CRC(Params)\`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataTypes/PVGrowerParams.h` (Private)


#### struct `FPVAuxinParams`  
`struct FPVAuxinParams`  
_L12-27_
- reflection: `USTRUCT()`
- L17 _public member_ `float AuxinFalloff = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Advanced Auxin Controls", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How quickly auxin concentration drops with distance from the tip.\n\n0 = uniform auxin throughout the branch (very strong suppression everywhere). Higher = auxin only suppresses buds near the tip, with lateral buds further down free to activate. Controls the spatial pattern of apical dominance."))`
- L20 _public member_ `float ApicalDominance = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Advanced Auxin Controls", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Strength of tip-driven lateral bud suppression.\n\nHigh = single dominant leader (pines, firs). Low = freely-branching, bushy structure (shrubs). Bud activation requires 'ApicalHormone < (1 - ApicalDominance)'."))`
- L23 _public member_ `float RadicalAuxin = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Advanced Auxin Controls", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Base level of root-zone auxin.\n\nWhen > 0.05, suppresses axillary sprouting near the base of the plant (mimics the natural suppression of below-ground side shoots). Useful for preventing low branches on tree trunks."))`
- L26 _public member_ `float MinGravitationalDot = 0.0f;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FPVGrowerGravityParams::MinGravitationalDot instead."))`

#### enum `EPVHitGroundBehaviour`  
`enum class EPVHitGroundBehaviour : uint8`  
_L30-35_
- reflection: `UENUM()`
- L32 _public enumerator_ `Kill`
- L33 _public enumerator_ `Deflect`
- L34 _public enumerator_ `Ignore`

#### struct `FPVGrowerGravityParams`  
`struct FPVGrowerGravityParams`  
_L38-74_
- reflection: `USTRUCT()`
- L43 _public member_ `float GravitationalForce = 9.8f;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta=(UIMin=0.0f, UIMax=10.0f, Tooltip="Strength of gravity (m/s²).\n\nDefault 9.8 matches Earth gravity. Higher values exaggerate sag; lower values produce stiffer-looking plants regardless of mass. Useful for stylized art direction."))`
- L46 _public member_ `float CellWeight = 0.05f;` — `UPROPERTY(EditAnywhere , Category = "Basic" , meta=(UIMin=0.0f, UIMax=2.0f, ClampMin=0.0f, Tooltip="Weight per unit of wood volume.\n\nHigher = heavier branches that sag more under their own weight. Pair with 'CellDensity' for realistic species — dense hardwoods are both heavier and stiffer; balsa is light and flexible."))`
- L49 _public member_ `float FoliageWeight = 0.05f;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, Tooltip="Weight added per leaf instance.\n\nLeaves often dominate gravity stress on young branches. Higher values make leaf-heavy branches droop more (catalpa, banana plant)."))`
- L52 _public member_ `float BranchWeightBreakThreshold = 0.33f;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta=(DisplayName = "Branch Break Tension Threshold", UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How much bend a branch tolerates before snapping.\n\n0 = any bend breaks the branch (extreme). 1 = branches tolerate 180° bends without breaking. 0.3-0.4 produces realistic snap-off behavior for over-stressed limbs."))`
- L55 _public member_ `EPVHitGroundBehaviour HitGroundBehaviour = EPVHitGroundBehaviour::Kill;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta=(Tooltip="What happens when a drooping branch touches the ground.\n\nKill = remove the branch. Deflect = redirect along the ground. Ignore = let it pass through. Use Kill for clean pruning, Deflect for creeping vines, Ignore for purely artistic ground-following."))`
- L58 _public member_ `float MinGravitationalDot = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Determines how much a branch needs to face upwards upon birth to be spawned."))`
- L61 _public member_ `float TrunkReinforcement = 0.5f;` — `UPROPERTY(EditAnywhere , Category = "Reinforcement", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Extra stiffness applied to the main trunk.\n\nOverride for the physics: higher values keep the trunk vertical regardless of mass calculations. Useful when the simulated bend is unrealistic — e.g. for stout, mature trees that physics would otherwise show as bending excessively."))`
- L64 _public member_ `float InputReinforcement = 0.5f;` — `UPROPERTY(EditAnywhere , Category = "Reinforcement", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Extra stiffness applied to inherited input skeletons.\n\nWhen chaining Growers (output of one feeds another), this stiffens the input skeleton so the chained growth doesn't deform what came before. Set near 1 to keep the input skeleton rigid; near 0 to let it deform naturally."))`
- L67 _public member_ `bool bCustom = true;` — `UPROPERTY()`
- L70 _public member_ `FFloatRange CellDensity = FFloatRange(7000, 10000);` — `UPROPERTY(EditAnywhere , Category = "Cell Density", meta=(Tooltip="Wood stiffness range, young (min) to mature (max).\n\nValues are Young's modulus in MPa. The simulation lerps from min (flexible young wood, default 7000 MPa) to max (stiff mature wood, default 10000 MPa) over 'CellDevelopmentTime' cycles. Real wood E-modulus values: balsa ~3000, pine ~9000, oak ~11000, ironwood ~16000."))`
- L73 _public member_ `float CellDevelopmentTime = 5.0f;` — `UPROPERTY(EditAnywhere , Category = "Cell Density", meta=(UIMin=1.0f, UIMax=100.0f, ClampMin=1.0f, Tooltip="Cycles until wood reaches mature stiffness.\n\nHow many growth cycles a branch needs to age from young (CellDensity.Min) to mature (CellDensity.Max). Default 5 means a branch born this cycle is fully mature 5 cycles later. Higher values keep branches flexible longer, increasing gravity-driven bending."))`

#### struct `FPVFoliageParams`  
`struct FPVFoliageParams`  
_L77-104_
- reflection: `USTRUCT()`
- L82 _public member_ `float StartScale = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "Basic Settings" , meta=(UIMin=0.001f, UIMax=5.0f, ClampMin=0.001f, Tooltip="Initial leaf scale when a leaf spawns.\n\nScale multiplier for a newly-spawned leaf, before ethylene-driven growth. Smaller = young leaves grow visibly over time. Combine with 'EndScale' and 'DevelopmentTime' for the growth curve."))`
- L85 _public member_ `float EndScale = 0.8f;` — `UPROPERTY(EditAnywhere, Category = "Basic Settings" , meta=(UIMin=0.001f, UIMax=5.0f, ClampMin=0.001f, Tooltip="Final leaf scale once fully grown.\n\nScale a leaf reaches once it has accumulated enough ethylene to be fully mature. Functions as the upper bounds for how large leaf can get during its life span."))`
- L88 _public member_ `float DevelopmentTime = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Basic Settings", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Fraction of total cycles for a leaf to reach full scale.\n\n0 = leaves spawn at 'EndScale' immediately. 1 = leaves take all 'GrowthCycles' to reach 'EndScale'. Useful when modeling young saplings (low value) or simulating short summer-only growth (high value)."))`
- L91 _public member_ `int Density = 3;` — `UPROPERTY(EditAnywhere, Category = "Basic Settings" , meta=(UIMin=0, UIMax=5, ClampMin=0, ClampMax=10, Tooltip="Leaf density multiplier.\n\nHigher = more leaves per branch point. Affects gravity load (heavier canopy = more sag) and light occlusion (denser canopy = more shade on lower branches)."))`
- L94 _public member_ `float EthyleneBuildup = 0.15f;` — `UPROPERTY(EditAnywhere, Category = "Hormone Control", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How fast ethylene accumulates on each leaf per cycle.\n\nHigher = leaves drop sooner. Lower = leaves persist longer."))`
- L97 _public member_ `float EthyleneThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Hormone Control" , meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Ethylene level at which leaves drop.\n\nWhen per-leaf ethylene exceeds this value, the leaf is shed. Combine with 'EthyleneBuildup' for the leaf-life cycle: high threshold + low buildup = long-lived leaves; vice versa for short-lived."))`
- L100 _public member_ `float AbscisicAcid = 0;` — `UPROPERTY(EditAnywhere, Category = "Hormone Control" , meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Stress-driven random leaf shedding.\n\nIndependent of ethylene. Each cycle, this fraction of leaves is randomly removed regardless of phyllotaxy. Use to simulate stressed plants (drought, salt) or to artistically thin the canopy."))`
- L103 _public member_ `float AuxinRetention = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Hormone Control" , meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="High amounts of auxin counteracts the effect of ethylene-driven shedding.\n\nHigher = leaves cling longer despite ethylene buildup. Useful for plants where leaves persist through stress."))`

#### enum `EPVGrowthPhyllotaxyType`  
`enum class EPVGrowthPhyllotaxyType : uint8`  
_L109-116_
- reflection: `UENUM()`
- L111 _public enumerator_ `Alternate`
- L112 _public enumerator_ `Opposite`
- L113 _public enumerator_ `Decussate`
- L114 _public enumerator_ `Whorled`
- L115 _public enumerator_ `Spiral`

#### enum `EPVGrowthPhyllotaxyFormation`  
`enum class EPVGrowthPhyllotaxyFormation : uint8`  
_L119-126_
- reflection: `UENUM()`
- L121 _public enumerator_ `Disticious = 180`
- L122 _public enumerator_ `Tristicious = 120`
- L123 _public enumerator_ `Pentasticious = 144`
- L124 _public enumerator_ `Octasticious = 135`
- L125 _public enumerator_ `Parasticious = 0`

#### struct `FPVGrowerSettingsTargetInfo`  
`struct FPVGrowerSettingsTargetInfo`  
_L129-172_
- reflection: `USTRUCT()`
- L134 _public member_ `bool bTrunk = true;` — `UPROPERTY(EditAnywhere , Category = "Target")`
- L137 _public member_ `bool bBranch = true;` — `UPROPERTY(EditAnywhere , Category = "Target")`
- L139 _public function_ `FString ToString() const`

#### struct `FPVGrowerPhyllotaxyTargetInfo`  
`struct FPVGrowerPhyllotaxyTargetInfo : public FPVGrowerSettingsTargetInfo`  
_L175-198_
- reflection: `USTRUCT()`
- inherits: `FPVGrowerSettingsTargetInfo`
- L180 _public member_ `bool bFoliage = false;` — `UPROPERTY(EditAnywhere, Category = "Target", meta = (DisplayAfter = "bBranch"))`
- L182 _public function_ `FString ToString() const`

#### struct `FPVGrowerPhyllotaxyParams`  
`struct FPVGrowerPhyllotaxyParams`  
_L201-240_
- reflection: `USTRUCT()`
- L206 _public member_ `float AxilAngle = 35.0f;` — `UPROPERTY(EditAnywhere , Category = "Axial Angle", meta=(UIMin=0.0f, UIMax=90.0f, ClampMin=-90.0f, ClampMax=90.0f, Tooltip="Angle in degrees between child branches and the parent direction.\n\n0° = child branch points along the parent axis (rare). 90° = child sticks straight out (perpendicular). Negative values up to -90° (typed manually) make the child point backward. Larger angles widen the canopy; smaller angles produce columnar shapes."))`
- L209 _public member_ `EPVGrowthPhyllotaxyType Type = EPVGrowthPhyllotaxyType::Spiral;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta=(Tooltip="Pattern for arranging buds around the stem.\n\nAlternate (180° flip per node), Opposite (paired buds), Decussate (paired buds rotating 90°), Whorled (2+ buds per node), or Spiral (continuous rotation using the Formation sub-type)."))`
- L212 _public member_ `EPVGrowthPhyllotaxyFormation Formation = EPVGrowthPhyllotaxyFormation::Octasticious;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta = (EditCondition = "Type == EPVGrowthPhyllotaxyType::Spiral", EditConditionHides, Tooltip="Sub-angle for spiral phyllotaxy.\n\nRepresents the number of branches that occurs in a 360 degree rotation. Distichous (180°), Tristichous (120°), Pentastichous (144°), Octastichous (135°, the default — closest to Fibonacci), or Parastichous (0° — free-form, requires manual Additional Angle / Offset)."))`
- L215 _public member_ `uint32 Min = 3;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy" , meta = (EditCondition = "Type == EPVGrowthPhyllotaxyType::Whorled", EditConditionHides, Tooltip="Minimum number of buds per node for Whorled phyllotaxy.\n\nEach whorl spawns between 'Min' and 'Max' branches, picked at random. Set 'Min == Max' for predictable counts. Typical values: 3-5 for a open whorl, 6-8 for an tight one."))`
- L218 _public member_ `uint32 Max = 6;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta = (EditCondition = "Type == EPVGrowthPhyllotaxyType::Whorled", EditConditionHides, Tooltip="Maximum number of buds per node for Whorled phyllotaxy.\n\nUpper bound on whorl branch count. See 'Min' above."))`
- L221 _public member_ `float AdditionalAngle = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta=(UIMin=0.0f, UIMax=360.0f, Tooltip="Extra rotation added to each node's phyllotaxy angle.\n\nAdds to the base angle picked by 'Type'/'Formation'. E.g., Octastichous base = 135°; with AdditionalAngle = 10°, effective per-node rotation = 145°. Used to break perfect regularity or to author Parastichous patterns (where base = 0°, so this drives the entire rotation)."))`
- L224 _public member_ `float Offset = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta=(UIMin=0.0f, UIMax=360.0f, Tooltip="Initial rotation of the phyllotaxy pattern.\n\nPhase-shifts the whole spiral. Doesn't change per-node spacing, just where the first bud starts. Useful for an overall offset without other changes to the phyllotaxy."))`
- L227 _public member_ `float Flatten = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Behavior", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Flatten the 3D phyllotaxy onto a 2D plane.\n\nAt 0, the phyllotaxy spirals fully in 3D. At 1, branches flattens out relative to the branches up direction. Useful for plants that have a spiral phyllotaxy but appears to flatten out."))`
- L230 _public member_ `int32 ShowStagger = 1;` — `UPROPERTY()`
- L233 _public member_ `float Stagger = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Behavior", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, EditCondition="ShowStagger > 0", EditConditionHides, Tooltip="Jitter the apical bud opposite to activating axillary buds.\n\nAdds asymmetry to the growth direction when a side branch activates — the apical tip slightly bends away from the new side branch. Higher values create more wandering, irregular branch paths."))`
- L236 _public member_ `int32 ShowReset = 1;` — `UPROPERTY()`
- L239 _public member_ `bool bReset = false;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta=(EditCondition="ShowReset > 0", EditConditionHides, Tooltip="Reset phyllotaxy at each branch boundary.\n\nWhen enabled, each new branch starts its phyllotaxy fresh relative to the branch up direction. When disabled, the rotation is successively inherited from its previous generation and resumes its rotation from that point."))`

#### struct `FPVGrowerBifurcationParams`  
`struct FPVGrowerBifurcationParams`  
_L243-270_
- reflection: `USTRUCT()`
- L248 _public member_ `bool bEnableBifurcation = false;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta=(Tooltip="Enable tip splitting (bifurcation).\n\nWhen enabled, branch tips can split into multiple branches when cytokinin builds up. Common in birch, spruce and most common fruit trees. When disabled, growth is purely apical-axillary."))`
- L251 _public member_ `float SplitAngle = 60.0f;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta = (EditCondition = "bEnableBifurcation == true", UIMin=0.0f, UIMax=90.0f, ClampMin=-90.0f, ClampMax=90.0f, Tooltip="Angle between bifurcated branches in degrees.\n\nWhen a tip splits, new branches are spaced this many degrees apart. 60° = wide V-split; 180° = horizontal split; 30° = narrow split. Combine with 'SplitBias' to asymmetrize."))`
- L254 _public member_ `float SplitBias = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta = (EditCondition = "bEnableBifurcation == true", UIMin=-0.5f, UIMax=0.5f, ClampMin=-0.5f, ClampMax=0.5f, Tooltip="Asymmetry between bifurcated branches.\n\n0 = even split (both branches get same angle). 1 = one branch keeps the original axis, the other gets the full 'SplitAngle'. Values 0.3-0.7 produce natural-looking unequal splits."))`
- L257 _public member_ `uint32 SplitMin = 2;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta = (EditCondition = "bEnableBifurcation == true", UIMin=2, UIMax=10, ClampMin=2, Tooltip="Minimum number of new branches at each split.\n\nMost species split into 2 (dichotomous); set Min=Max=3 for trichotomous splits common in some palms. Random pick between Min and Max per split event."))`
- L260 _public member_ `uint32 SplitMax = 2;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta = (EditCondition = "bEnableBifurcation == true", UIMin=2, UIMax=10, ClampMin=2, Tooltip="Maximum number of new branches at each split.\n\nMost species split into 2 (dichotomous); set Min=Max=3 for trichotomous splits common in some palms. Random pick between Min and Max per split event."))`
- L263 _public member_ `float SplitThreshold = 0.33f;` — `UPROPERTY(EditAnywhere , Category = "Hormone Controls", meta = (EditCondition = "bEnableBifurcation == true", UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Cytokinin level required to trigger a split.\n\nWhen a plant is unable so support its own weight it starts producing cytokinin. When a bud's cytokinin exceeds this threshold, it's eligible to bifurcate. 1.0 = saturation required (rare splits). 0.5 = splits happen more often. Combine with 'CytokininBuildup' to tune frequency."))`
- L266 _public member_ `float CytokininBuildup = 0.33f;` — `UPROPERTY(EditAnywhere , Category = "Hormone Controls", meta = (EditCondition = "bEnableBifurcation == true", UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How fast cytokinin accumulates per cycle.\n\nHigher = splits happen sooner. Combine with 'SplitThreshold' to control overall split frequency."))`
- L269 _public member_ `float CytokininRandomness = 0.33f;` — `UPROPERTY(EditAnywhere , Category = "Hormone Controls", meta = (EditCondition = "bEnableBifurcation == true", UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Random variation added to cytokinin buildup each cycle.\n\nHigher = less predictable split timing across branches. 0 = perfectly synchronized splits."))`

#### struct `FPVPhototropismParams`  
`struct FPVPhototropismParams`  
_L273-291_
- reflection: `USTRUCT()`
- L278 _public member_ `float Apical = 0.25;` — `UPROPERTY(EditAnywhere , Category = "Phototropic Settings", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How strongly growing tips bend toward light.\n\n0 = no light-seeking (tips grow straight). 1 = tips fully follow optimal light direction. Values 0-0.5 are typical for natural plants — higher overrides phyllotaxy and can produce unnatural results."))`
- L281 _public member_ `float ApicalBias = 0.1f;` — `UPROPERTY(EditAnywhere , Category = "Phototropic Settings", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Bias between light-seeking and shadow-avoidance for tips.\n\n0 = bend toward the brightest direction. 1 = bend away from the darkest direction. The two are subtly different — shadow-avoidance tends to spread branches away from neighbors (canopy filling), while light-seeking tends to bend toward the sun."))`
- L284 _public member_ `float Axillary = 0.1f;` — `UPROPERTY(EditAnywhere , Category = "Phototropic Settings", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How strongly new side branches choose a light-seeking direction at birth.\n\nOnly affects the first segment of a new side branch. Useful when you want branches to immediately tilt toward light at activation. Higher values can override phyllotaxy aggressively."))`
- L287 _public member_ `float AxillaryBias = 0.75f;` — `UPROPERTY(EditAnywhere , Category = "Phototropic Settings", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Bias between light-seeking and shadow-avoidance for new side branches.\n\nSame idea as 'ApicalBias' but for axillary phototropism."))`
- L290 _public member_ `float LightRequirement = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Photosynthetic Impact", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Minimum light required for a bud to activate.\n\n0 = buds can activate regardless of light. 1 = full light required (extreme — most buds will fail). Combine with foliage occlusion to create realistic shade-sensitive plants. Distinct from light senescence: this gates initial sprouting, senescence gates branch survival."))`

#### struct `FPVDirectionalParams`  
`struct FPVDirectionalParams`  
_L294-306_
- reflection: `USTRUCT()`
- L299 _public member_ `float ApicalRandomAngle = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Random", meta=(UIMin=0.0f, UIMax=45.0f, Tooltip="Random angle added to each apical growth step.\n\nPer-step random tilt of the growing tip in degrees. 0 = perfectly straight. 5-15 = natural wobble. Higher values produce wandering, irregular branch paths."))`
- L302 _public member_ `float AxillaryRandomAngle = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Random", meta=(UIMin=0.0f, UIMax=45.0f, Tooltip="Random angle added to each new side branch's first segment.\n\nPer-branch initial direction jitter. Useful to break the regularity of phyllotaxy without changing the pattern itself."))`
- L305 _public member_ `float CodominentRandomAngle = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Random", meta=(UIMin=0.0f, UIMax=45.0f, Tooltip="Random angle added to bifurcated branches.\n\nOnly effective when bifurcation is enabled. Adds variation to the split angles for natural-looking splits."))`

#### enum `EPVRampBasis`  
`enum class EPVRampBasis : uint8`  
_L309-309_
- reflection: `UENUM()`
- L309 _public enumerator_ `enum class EPVRampBasis : uint8 { PlantTargetLength, BranchTargetLength }; USTRUCT() struct FPVTrunkGrowthParams { GENERATED_BODY() UPROPERTY(EditAnywhere , Category = "Basic Global", meta=(UIMin=1, ClampMin=1, Tooltip="Maximum branching depth.\n\n1 = trunk only. 5 = trunk + 4 levels of side branches. Higher values allow finer detail but increase generation time. Most trees look complete with 8-15."))`
- L309 _public enumerator_ `enum class EPVRampBasis : uint8 { PlantTargetLength, BranchTargetLength }; USTRUCT() struct FPVTrunkGrowthParams { GENERATED_BODY() UPROPERTY(EditAnywhere , Category = "Basic Global", meta=(UIMin=1, ClampMin=1, Tooltip="Maximum branching depth.\n\n1 = trunk only. 5 = trunk + 4 levels of side branches. Higher values allow finer detail but increase generation time. Most trees look complete with 8-15."))`

#### struct `FPVTrunkGrowthParams`  
`struct FPVTrunkGrowthParams`  
_L312-410_
- reflection: `USTRUCT()`
- L317 _public member_ `uint8 MaxGeneration = 25;` — `UPROPERTY(EditAnywhere , Category = "Basic Global", meta=(UIMin=1, ClampMin=1, Tooltip="Maximum branching depth.\n\n1 = trunk only. 5 = trunk + 4 levels of side branches. Higher values allow finer detail but increase generation time. Most trees look complete with 8-15."))`
- L320 _public member_ `float IncrementalRadius = 0.0033f;` — `UPROPERTY(EditAnywhere , Category = "Basic Global", meta=(UIMin=0.0005f, UIMax=0.01f, ClampMin=0.0001f, Tooltip="How much each branch thickens per cycle (in meters).\n\nSimulates secondary wood growth (girth increase). Default 0.0033 m/cycle = 3.3 mm/year. Thicker branches are stiffer (resist gravity better) and immune to senescence above 'RetentionRadius'."))`
- L323 _public member_ `float PlantTargetLength = 5.0f;` — `UPROPERTY(EditAnywhere , Category = "Basic Global", meta=(UIMin=0.2f, UIMax=15.0f, ClampMin=0.001f, Tooltip="Target height for the main trunk in meters.\n\nThe trunk's priority gradient is normalized to this distance. After reaching this height, the apical priority typically drops to near-zero (determinate growth) or stays positive (indeterminate growth) depending on the gradient curve."))`
- L326 _public member_ `float BranchTargetLength = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Basic Global", meta=(Tooltip="Target length for side branches; 0 = unlimited.\n\nSame as 'PlantTargetLength' but applied to branches. 0 = branches grow until resources run out. Set a finite value to create uniform side-branch lengths."))`
- L329 _public member_ `float SegmentLength = 0.25;` — `UPROPERTY(EditAnywhere , Category = "Internode Length" , meta=(UIMin=0.0f, UIMax=1.0f, Tooltip="Length of each internode in meters.\n\nDistance between consecutive growth points along a branch. Smaller = denser, compact plants. Larger = open, airy structure. This is the core control for plant scale relative to 'GrowthCycles'. Default 0.25 m = 25 cm per growth step."))`
- L332 _public member_ `float BranchScale = 1.0f;` — `UPROPERTY(EditAnywhere , Category = "Internode Length" , meta=(UIMin=0.1f, UIMax=2.0f, ClampMin=0.001f, Tooltip="Multiplier on SegmentLength for side branches.\n\nBelow 1 = side branches grow shorter steps than the trunk (tree-like tapering). Above 1 = side branches outgrow the trunk (spreading, bush-like). 1.0 = uniform across trunk and branches."))`
- L335 _public member_ `float LengthLightImpact = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Internode Length", meta=(UIMin=-1.0f, UIMax=1.0f, ClampMin=-1.0f, ClampMax=1.0f, Tooltip="How light level affects internode length.\n\nPositive: branches in bright spots grow longer segments (sun-loving species). Negative: shaded branches stretch longer toward light (etiolation — climbing vines, shade-stressed saplings)."))`
- L338 _public member_ `float LightRandomness = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Internode Length", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Random variation in light-driven length response.\n\nHigher values produce less uniform light response, making the plant look more natural and less computed."))`
- L341 _public member_ `float LengthBias = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Internode Length", meta=(UIMin=0.0f, UIMax=1.0f, Tooltip="Minimum guaranteed fraction of SegmentLength per step.\n\nEven when other factors (light, hormones, randomness) would shorten a step, this bias ensures at least this fraction is added. Prevents branches from stopping entirely. Higher = more consistent growth despite stress."))`
- L344 _public member_ `float AuxinImpact = 0.0f;` — `UPROPERTY(/*meta=(UIMin=0.0f, UIMax=1.0f)*/)`
- L347 _public member_ `float LengthSeedScaleImpact = 1.0f;` — `UPROPERTY()`
- L350 _public member_ `float AxillaryParentGrowth = 1.0f;` — `UPROPERTY(EditAnywhere , Category = "Axillary Resources", meta=(UIMin=0.0f, UIMax=2.0f, ClampMin=0.0f, Tooltip="Axillary priority multiplier for the trunk (Generation 1).\n\nScales the axillary priority gradient's output for the trunk. Higher = more side branches on the trunk. Lower = sparser trunk branching."))`
- L353 _public member_ `float AxillaryChildGrowth = 1.0f;` — `UPROPERTY(EditAnywhere , Category = "Axillary Resources", meta=(UIMin=0.0f, UIMax=2.0f, ClampMin=0.0f, Tooltip="Axillary priority multiplier for side branches (Generation 2+).\n\nSame as 'AxillaryParentGrowth' but applied to side branches. Use to control how dense the inner foliage is independent of trunk branch density."))`
- L356 _public member_ `bool bAxillaryRetry = true;` — `UPROPERTY(EditAnywhere , Category = "Axillary Resources", meta=(Tooltip="Allow failed axillary buds to retry in later cycles.\n\nWhen on, buds that failed to activate this cycle (due to light, randomness, or apical dominance) are still eligible to activate next cycle. When disabled, a failed bud is permanently dormant. Enabled creates more deterministic plants; on is more natural."))`
- L359 _public member_ `bool bAxillaryUseChildGradient = false;` — `UPROPERTY(EditAnywhere , Category = "Axillary Resources", meta=(Tooltip="Use a separate axillary priority ramp for side branches.\n\nWhen enabled, side branches use 'AxillaryPriorityChildGradient' instead of inheriting the trunk's 'AxillaryPriorityGradient'. Useful for plants where branching density differs along trunk vs. side branches."))`
- L362 _public member_ `EPVRampBasis AxillaryRampBasis = EPVRampBasis::PlantTargetLength;` — `UPROPERTY(EditAnywhere , Category = "Axillary Resources" , DisplayName = "Ramp Basis", meta=(Tooltip="Length used to normalize the axillary priority ramp.\n\n'PlantTargetLength': ramp spans the whole plant terminal length. 'BranchTargetLength': ramp spans each branch's individual length. Choose based on whether side-branch density should depend on plant-wide height or per-branch distance."))`
- L365 _public member_ `FPVFloatRamp AxillaryPriorityGradient;` — `UPROPERTY(EditAnywhere, Category= "Axillary Resources", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve controlling axillary bud activation likelihood vs. position.\n\nX axis = normalized position along trunk (or branch, per ramp basis). Y axis = priority threshold. Buds whose random roll falls below this curve activate. Set Y to 0 at the bottom to prevent branches in the lower trunk; set Y high at the top for denser canopy branching."))`
- L368 _public member_ `EPVRampBasis AxillaryChildRampBasis = EPVRampBasis::PlantTargetLength;` — `UPROPERTY(EditAnywhere , Category = "Axillary Resources" , DisplayName = "Child Ramp Basis", meta=(EditCondition = "bAxillaryUseChildGradient == true", EditConditionHides))`
- L371 _public member_ `FPVFloatRamp AxillaryPriorityChildGradient;` — `UPROPERTY(EditAnywhere, Category= "Axillary Resources", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, EditCondition = "bAxillaryUseChildGradient == true", EditConditionHides, Tooltip="Separate axillary priority ramp for side branches.\n\nUse independently from 'AxillaryPriorityGradient' to give side branches different density behavior."))`
- L374 _public member_ `float ApicalParentGrowth = 1.0f;` — `UPROPERTY(EditAnywhere , Category = "Apical Resources", meta=(UIMin=0.0f, UIMax=2.0f, ClampMin=0.0f, Tooltip="Apical priority multiplier for the trunk.\n\nHigher = the trunk's apical tip extends more reliably each cycle. Lower = the trunk slows or stops earlier (more determinate growth)."))`
- L377 _public member_ `float ApicalChildGrowth = 1.0f;` — `UPROPERTY(EditAnywhere , Category = "Apical Resources", meta=(UIMin=0.0f, UIMax=2.0f, ClampMin=0.0f, Tooltip="Apical priority multiplier for side branches.\n\nHigher = side branches keep extending longer. Lower = side branches stop after fewer cycles, producing short stubs."))`
- L380 _public member_ `EPVRampBasis ApicalRampBasis = EPVRampBasis::PlantTargetLength;` — `UPROPERTY(EditAnywhere , Category = "Apical Resources" , DisplayName = "Ramp Basis", meta=(Tooltip="Length used to normalize the apical priority ramp.\n\nSame idea as 'AxillaryRampBasis'. Default is 'BranchTargetLength' — branches use their own target. Switch to 'PlantTargetLength' for plant-wide apical scaling."))`
- L383 _public member_ `FPVFloatRamp ApicalPriorityGradient;` — `UPROPERTY(EditAnywhere, Category= "Apical Resources", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip="Curve controlling apical tip extension likelihood vs. position.\n\nX axis = normalized position. Y axis = priority threshold. Apical activation requires a random roll below Y. Set Y at the high end to 0 for determinate plants (trunk stops at PlantTargetLength). Keep Y > 0 throughout for indeterminate (continuously growing) plants."))`
- L386 _public member_ `bool bApicalUseChildGradient = false;` — `UPROPERTY(EditAnywhere , Category = "Apical Resources", meta=(Tooltip="Use a separate apical priority ramp for side branches.\n\nWhen on, side branches use 'ApicalPriorityChildGradient' instead of 'ApicalPriorityGradient'. Useful for letting side branches keep growing past the trunk's stop point."))`
- L389 _public member_ `EPVRampBasis ApicalChildRampBasis = EPVRampBasis::PlantTargetLength;` — `UPROPERTY(EditAnywhere , Category = "Apical Resources" , DisplayName = "Child Ramp Basis", meta=(EditCondition = "bApicalUseChildGradient == true", EditConditionHides))`
- L392 _public member_ `FPVFloatRamp ApicalPriorityChildGradient;` — `UPROPERTY(EditAnywhere, Category= "Apical Resources", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, EditCondition = "bApicalUseChildGradient == true", EditConditionHides, Tooltip="Separate apical priority ramp for side branches."))`
- L395 _public member_ `float SeedScaleEffect = 1.0f;` — `UPROPERTY(EditAnywhere , Category = "Advanced Globals", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How much seed-point scale influences final plant size.\n\nAt 1.0, the seed point's scale attribute directly multiplies the plant's size. At 0.0, seed scale is ignored. Useful when scattering seed points of varying sizes from PCG and you want either uniform plants (0) or size-variable plants (1)."))`
- L398 _public member_ `float WhorledRadiusImpact = 0.5f;` — `UPROPERTY(EditAnywhere , Category = "Advanced Globals", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="How much each branch in a Whorled phyllotaxy reduces the parent's effective radius.\n\nOnly relevant when Whorled phyllotaxy spawns multiple side branches at one node. Higher = more radius reduction per branch (mimics the natural taper of a heavily-branched node). 0 = no reduction."))`
- L401 _public member_ `float Corymb = 0.0f;` — `UPROPERTY(EditAnywhere , Category = "Advanced Globals", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Flattens the crown by letting lower branches grow longer.\n\nHigher values allow lower lateral branches to elongate beyond their parents' length, producing a corymb (flat-topped) crown shape — common in hawthorn or broccoli."))`
- L403 _public function_ `FPVTrunkGrowthParams()`

#### struct `FPVGuideParams`  
`struct FPVGuideParams`  
_L413-428_
- reflection: `USTRUCT()`
- L418 _public member_ `float GuidFollowStrength = 0.0;` — `UPROPERTY(EditAnywhere , Category = "GuideSettings")`
- L421 _public member_ `float GuideSearchDistance = 0.0;` — `UPROPERTY(EditAnywhere , Category = "GuideSettings")`
- L424 _public member_ `float GuideGravityOverride = 0.0;` — `UPROPERTY(EditAnywhere , Category = "GuideSettings")`
- L427 _public member_ `bool bUse = false;` — `UPROPERTY(EditAnywhere , Category = "GuideSettings")`

#### enum `EPVAbscissionMode`  
`enum class EPVAbscissionMode : uint8`  
_L431-435_
- reflection: `UENUM()`
- L433 _public enumerator_ `Kill`
- L434 _public enumerator_ `Degrade`

#### struct `FPVAgeSenescenceParams`  
`struct FPVAgeSenescenceParams`  
_L438-462_
- reflection: `USTRUCT()`
- L443 _public member_ `bool bResetOnResumeGrowth = true;` — `UPROPERTY(EditAnywhere , Category = "Gravity Senescence/Abscision" , meta=(Tooltip = "Reset branch age when resuming growth from an input skeleton.\n\nWhen chaining Growers, this controls whether inherited branches start aging fresh (true) or continue from where they left off (false). Use false for true 'resumed growth'; use true when chaining for stylistic effect without aging continuity."))`
- L446 _public member_ `EPVAbscissionMode Mode = EPVAbscissionMode::Degrade;` — `UPROPERTY(EditAnywhere , Category = "Gravity Senescence/Abscision", meta=(Tooltip="How aged branches are removed: Degrade (gradual) or Kill (instant).\n\nDegrade = the branch's brittleness increases each cycle until a gravity break occurs (natural-looking). Kill = the branch is fully removed after the senescence delay (clean and predictable)."))`
- L449 _public member_ `int SenescenceAge = 20;` — `UPROPERTY(EditAnywhere , Category = "Gravity Senescence/Abscision" , meta=(UIMin=1, UIMax=50, Tooltip="Cycle age after which branches become vulnerable to age-abscission.\n\nBranches younger than this are immune. After this age, they enter the senescent state and are subject to 'DegradationAmount' (Degrade mode) or 'SenescenceMin/Max' countdown (Kill mode)."))`
- L452 _public member_ `float DegradationAmount = 0;` — `UPROPERTY(EditAnywhere , Category = "Gravity Senescence/Abscision" , meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, EditCondition = "Mode == EPVAbscissionMode::Degrade", Tooltip="How much a senescent branch weakens each cycle.\n\nEach cycle past 'SenescenceAge', the branch's brittleness increases by this amount. Eventually the branch becomes more susceptible to break under gravity. Higher = faster weakening. 0 = no degradation (branch lingers indefinitely)."))`
- L455 _public member_ `int SenescenceMin = 1;` — `UPROPERTY(EditAnywhere , Category = "Gravity Senescence/Abscision" , meta=(UIMin=0, EditCondition = "Mode == EPVAbscissionMode::Kill", Tooltip="Minimum random range of cycles a senescent branch survives before removal.\n\nAfter 'SenescenceAge', a random duration between Min and Max is rolled per branch. The branch survives that many additional cycles, then is removed."))`
- L458 _public member_ `int SenescenceMax = 5;` — `UPROPERTY(EditAnywhere , Category = "Gravity Senescence/Abscision" , meta=(UIMin=0, EditCondition = "Mode == EPVAbscissionMode::Kill", Tooltip="Maximum random range of cycles a senescent branch survives before removal.\n\nAfter 'SenescenceAge', a random duration between Min and Max is rolled per branch. The branch survives that many additional cycles, then is removed."))`
- L461 _public member_ `float RetentionRadius = 0;` — `UPROPERTY(EditAnywhere , Category = "Gravity Senescence/Abscision" , meta=(UIMin=0.0f, UIMax=1.0f, Tooltip="Fraction of expected radius that immunizes a branch from age-death.\n\nSame concept as Light Senescence's RetentionRadius. Branches thicker than this fraction × expected radius survive past their senescence age."))`

#### struct `FPVLightSenescenceParams`  
`struct FPVLightSenescenceParams`  
_L465-480_
- reflection: `USTRUCT()`
- L470 _public member_ `float SenescenceThreshold = 0.33f;` — `UPROPERTY(EditAnywhere , Category = "Light Senescence/Abscission", meta=(UIMin=0.0f, UIMax=1.0f, ClampMin=0.0f, ClampMax=1.0f, Tooltip="Light level below which branches enter shade-death.\n\nWhen a branch's measured light drops below this value for enough cycles, it begins dying back. 0 = never (all branches survive any shade). 1 = full sun required (extreme — most branches will die). 0.3-0.5 produces realistic shade pruning."))`
- L473 _public member_ `int SenescenceMin = 1;` — `UPROPERTY(EditAnywhere , Category = "Light Senescence/Abscission" , meta=(UIMin=0, Tooltip="Minimum random range of cycles a shaded branch survives before dying.\n\nOnce a branch's light drops below 'SenescenceThreshold', a random duration between Min and Max is rolled. The branch survives that many cycles in shade, then is removed (in Kill mode) or has fully degraded (in Degrade mode)."))`
- L476 _public member_ `int SenescenceMax = 5;` — `UPROPERTY(EditAnywhere , Category = "Light Senescence/Abscission" , meta=(UIMin=0, Tooltip="Maximum random range of cycles a shaded branch survives before dying.\n\nOnce a branch's light drops below 'SenescenceThreshold', a random duration between Min and Max is rolled. The branch survives that many cycles in shade, then is removed (in Kill mode) or has fully degraded (in Degrade mode)."))`
- L479 _public member_ `float RetentionRadius = 0;` — `UPROPERTY(EditAnywhere , Category = "Light Senescence/Abscission" , meta=(UIMin=0.0f, UIMax=1.0f, Tooltip="Fraction of expected radius that immunizes a branch from shade-death.\n\nBranches thicker than this fraction × the expected radius for their age survive even when light senescence would kill them. Allows old, thick branches to persist in deep shade. 0 = no immunity; 0.5 = branches at half expected radius survive; 1.0 = only fully-mature branches survive."))`

#### struct `FPVGrowerAuxinWithTargets`  
`struct FPVGrowerAuxinWithTargets`  
_L483-492_
- reflection: `USTRUCT()`
- L488 _public member_ `FPVGrowerSettingsTargetInfo Targets;` — `UPROPERTY(EditAnywhere , Category = "Targets", meta = (ShowOnlyInnerProperties, PCG_NotOverridable))`
- L491 _public member_ `FPVAuxinParams Params;` — `UPROPERTY(EditAnywhere , Category = "Branching", meta = (ShowOnlyInnerProperties))`

#### struct `FPVGrowerPhototropismWithTargets`  
`struct FPVGrowerPhototropismWithTargets`  
_L495-504_
- reflection: `USTRUCT()`
- L500 _public member_ `FPVGrowerSettingsTargetInfo Targets;` — `UPROPERTY(EditAnywhere , Category = "Targets", meta = (ShowOnlyInnerProperties, PCG_NotOverridable))`
- L503 _public member_ `FPVPhototropismParams Params;` — `UPROPERTY(EditAnywhere , Category = "Phototropism", meta = (ShowOnlyInnerProperties))`

#### struct `FPVGrowerDirectionalWithTargets`  
`struct FPVGrowerDirectionalWithTargets`  
_L507-516_
- reflection: `USTRUCT()`
- L512 _public member_ `FPVGrowerSettingsTargetInfo Targets;` — `UPROPERTY(EditAnywhere , Category = "Targets", meta = (ShowOnlyInnerProperties, PCG_NotOverridable))`
- L515 _public member_ `FPVDirectionalParams Params;` — `UPROPERTY(EditAnywhere , Category = "RandomAngle", meta = (ShowOnlyInnerProperties))`

#### struct `FPVGrowerPhyllotaxyWithTargets`  
`struct FPVGrowerPhyllotaxyWithTargets`  
_L519-528_
- reflection: `USTRUCT()`
- L524 _public member_ `FPVGrowerPhyllotaxyTargetInfo Targets;` — `UPROPERTY(EditAnywhere , Category = "Targets", meta = (ShowOnlyInnerProperties, PCG_NotOverridable))`
- L527 _public member_ `FPVGrowerPhyllotaxyParams Params;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta = (ShowOnlyInnerProperties))`

#### struct `FPVGrowerBifurcationWithTargets`  
`struct FPVGrowerBifurcationWithTargets`  
_L531-540_
- reflection: `USTRUCT()`
- L536 _public member_ `FPVGrowerSettingsTargetInfo Targets;` — `UPROPERTY(EditAnywhere , Category = "Targets", meta = (ShowOnlyInnerProperties, PCG_NotOverridable))`
- L539 _public member_ `FPVGrowerBifurcationParams Params;` — `UPROPERTY(EditAnywhere , Category = "Bifurcation", meta = (ShowOnlyInnerProperties))`

#### enum `EPVPresetTarget`  
`enum class EPVPresetTarget : uint8`  
_L543-547_
- reflection: `UENUM()`
- L545 _public enumerator_ `Trunk`
- L546 _public enumerator_ `Branch`

#### struct `FPVLeafMeshGeometry`  
`struct FPVLeafMeshGeometry`  
_L554-563_
- desc: Pre-calculated geometry for a single leaf mesh. Built once when LeafMesh is selected in the editor; vertices/indices are reused every growth cycle without re-extracting from the render data.
- L556 _public member_ `TArray<FVector3f> Vertices;` — object-space vertex positions (cm)
- L557 _public member_ `TArray<uint32> Indices;` — triangle index buffer
- L558 _public member_ `FVector3f ObjMin = FVector3f(0.f);` — object-space AABB min
- L559 _public member_ `FVector3f ObjMax = FVector3f(0.f);` — object-space AABB max
- L561 _public function_ `bool IsValid() const`
- L562 _public function_ `void Reset()`

#### struct `FPVLeafTransform`  
`struct FPVLeafTransform`  
_L566-570_
- desc: A single leaf placement: world-space transform and the branch it belongs to.
- L568 _public member_ `FTransform Transform;`
- L569 _public member_ `int32 BranchNumber = 0;`

#### struct `FPVGrowerParams`  
`struct FPVGrowerParams`  
_L573-683_
- reflection: `USTRUCT()`
- L577 _public function_ `FPVGrowerParams()`
- L585 _public member_ `uint32 GrowthCycles = 1;` — `UPROPERTY(EditAnywhere , Category = "Basic" , meta=(UIMin=1.0f, UIMax=45.0f, PCG_Overridable, Tooltip="How many growing iterations to simulate.\n\nEach cycle can be considered one growing season, but certain plants can have multiple cycles each season. Higher counts produce larger, more complex plants with more visible aging effects. Start with 5-10 for typical trees; use 20-45 for very mature plants. Note that simulation cost grows roughly linearly with cycle count."))`
- L588 _public member_ `uint32 RandomSeed = 7023;` — `UPROPERTY(EditAnywhere , Category = "Basic", meta =(PCG_NotOverridable, Tooltip="Random seed for all stochastic choices.\n\nControls every random decision in the simulation: which buds activate, axillary angle jitter, bifurcation timing, etc. Same seed + same settings = identical plant. Change to explore natural variations of the same configuration."))`
- L591 _public member_ `FPVGrowerPhyllotaxyParams Phyllotaxy;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy | Trunk", meta =(PCG_NotOverridable))`
- L594 _public member_ `bool bBranchPhyllotaxySameAsTrunk = true;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta =(PCG_NotOverridable, Tooltip="Use the trunk's phyllotaxy for side branches.\n\nWhen on, side branches inherit the trunk's phyllotaxy settings. Turn off to configure side-branch phyllotaxy independently — useful for species like spruce (whorled trunk, opposite branches)."))`
- L597 _public member_ `FPVGrowerPhyllotaxyParams BranchPhyllotaxy;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy | Branch" , meta = (EditCondition = "bBranchPhyllotaxySameAsTrunk == false" , EditConditionHides, PCG_NotOverridable))`
- L600 _public member_ `bool bLeafPhyllotaxySameAsBranch = true;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy", meta =(PCG_NotOverridable, Tooltip="Use the branch phyllotaxy for leaf placement.\n\nWhen on, leaves use the same arrangement pattern as side branches. Turn off to give leaves their own phyllotaxy — useful when you want branches in a whorled pattern but leaves in a spiral, for example."))`
- L603 _public member_ `FPVGrowerPhyllotaxyParams LeafPhyllotaxy;` — `UPROPERTY(EditAnywhere , Category = "Phyllotaxy | Leaf" , meta = (EditCondition = "bLeafPhyllotaxySameAsBranch == false" , EditConditionHides, PCG_NotOverridable))`
- L606 _public member_ `FPVTrunkGrowthParams TrunkGrowth;` — `UPROPERTY(EditAnywhere , Category = "Growth", meta =(PCG_NotOverridable))`
- L609 _public member_ `FPVPhototropismParams Phototropism;` — `UPROPERTY(EditAnywhere , Category = "Phototropism | Trunk", meta =(PCG_NotOverridable))`
- L612 _public member_ `bool bBranchPhototropismSameAsTrunk = true;` — `UPROPERTY(EditAnywhere , Category = "Phototropism", meta =(PCG_NotOverridable, Tooltip="Use the trunk's phototropism for side branches.\n\nTurn off to configure side-branch phototropism independently."))`
- L615 _public member_ `FPVPhototropismParams BranchPhototropism;` — `UPROPERTY(EditAnywhere , Category = "Phototropism | Branch" , meta = (EditCondition = "bBranchPhototropismSameAsTrunk == false" , EditConditionHides, PCG_NotOverridable))`
- L618 _public member_ `FPVLightSenescenceParams LightSenescence;` — `UPROPERTY(EditAnywhere , Category = "Phototropism", meta =(PCG_NotOverridable, EditCondition = bSenescence))`
- L621 _public member_ `FPVGrowerGravityParams GravityParams;` — `UPROPERTY(EditAnywhere , Category = "Gravity", meta =(PCG_NotOverridable))`
- L624 _public member_ `bool bSenescence = true;` — `UPROPERTY(EditAnywhere, Category = "Gravity", meta =(PCG_NotOverridable, Tooltip="Master toggle for age and light senescence.\n\nWhen on, branches can die from old age ('FPVAgeSenescenceParams') or sustained shade ('FPVLightSenescenceParams'). When off, both senescence panels are inactive and branches never die naturally. Turn off only for short-cycle test plants or stylized art direction."))`
- L627 _public member_ `FPVAgeSenescenceParams AgeSenescence;` — `UPROPERTY(EditAnywhere , Category = "Gravity", meta =(PCG_NotOverridable, EditCondition = bSenescence))`
- L630 _public member_ `FPVGrowerBifurcationParams Bifurcation;` — `UPROPERTY(EditAnywhere , Category = "Bifurcation | Trunk", meta =(PCG_NotOverridable))`
- L633 _public member_ `FPVGrowerBifurcationParams BranchBifurcation;` — `UPROPERTY(EditAnywhere , Category = "Bifurcation | Branch" , meta = (PCG_NotOverridable))`
- L636 _public member_ `FPVDirectionalParams Directional;` — `UPROPERTY(EditAnywhere , Category = "Directional | Trunk", meta =(PCG_NotOverridable))`
- L639 _public member_ `bool bBranchDirectionalSameAsTrunk = true;` — `UPROPERTY(EditAnywhere , Category = "Directional", meta =(PCG_NotOverridable, Tooltip="Use the trunk's directional jitter for side branches."))`
- L642 _public member_ `FPVDirectionalParams BranchDirectional;` — `UPROPERTY(EditAnywhere , Category = "Directional | Branch", meta = (EditCondition = "bBranchDirectionalSameAsTrunk == false" , EditConditionHides, PCG_NotOverridable))`
- L645 _public member_ `FPVAuxinParams Auxin;` — `UPROPERTY(EditAnywhere , Category = "Auxin | Trunk", meta =(PCG_NotOverridable))`
- L648 _public member_ `bool bBranchAuxinConditionSameAsTrunk = true;` — `UPROPERTY(EditAnywhere , Category = "Auxin", meta =(PCG_NotOverridable, Tooltip="Use the trunk's auxin for side branches."))`
- L651 _public member_ `FPVAuxinParams BranchAuxin;` — `UPROPERTY(EditAnywhere , Category = "Auxin | Branch" , meta = (EditCondition = "bBranchAuxinConditionSameAsTrunk == false" , EditConditionHides, PCG_NotOverridable))`
- L654 _public member_ `FPVFoliageParams Foliage;` — `UPROPERTY(EditAnywhere, Category = "Foliage", meta =(PCG_NotOverridable))`
- L657 _public member_ `FPVGuideParams GuideSettings;` — `UPROPERTY()`
- L660 _public member_ `TArray<FPVColliderParams> ColliderSettings;` — `UPROPERTY(EditAnywhere , Category = "Object Interaction", meta =(PCG_NotOverridable, Tooltip="List of colliders that interact with growth (avoid, trim inside, trim outside).\n\nEach entry defines a collider shape (box, sphere, capsule) and a CollisionType. Growth either avoids the collider, is trimmed where it enters the collider, or is trimmed where it leaves the collider."))`
- L666 _public member_ `TObjectPtr<UStaticMesh> FoliageMesh;` — `UPROPERTY(EditAnywhere, Category = "Foliage", meta=(PCG_NotOverridable, Tooltip="Mesh used as the per-leaf light occluder.\n\nA simple static mesh representing one leaf, used to ray-trace light occlusion in 'DetectLight'. The default lightweight the default mesh is recommended unless you need accurate shadowing from custom leaf shapes (which costs more per cycle)."))` — Leaf mesh used as a light occluder during each growth cycle. Geometry is pre-calculated when this is set; only per-leaf instance transforms are computed at runtime.
- L670 _public member_ `FPVLeafMeshGeometry CachedLeafMeshGeometry;` — Pre-calculated vertex/index data for LeafMesh. Populated by PostEditChangeProperty or lazily on first growth cycle.
- L672 _public prototype_ `void GetPhyllotaxy(FPVGrowerPhyllotaxyParams& OutPhyllotaxy, int Generation) const;`
- L674 _public prototype_ `float GetPhyllotaxyAngle(const FPVGrowerPhyllotaxyParams& InPhyllotaxy) const;`
- L676 _public prototype_ `void GetAuxin(FPVAuxinParams& OutAuxin, int Generation) const;`
- L678 _public prototype_ `void GetPhototropism(FPVPhototropismParams& OutPhototropism, int Generation) const;`
- L680 _public prototype_ `void GetDirectionalParams(FPVDirectionalParams& OutDirectional, int Generation) const;`
- L682 _public prototype_ `void GetBifurcation(FPVGrowerBifurcationParams& OutBifurcation, int Generation) const;`

#### Free symbols / members of external scopes

- L106 _variable_ `static int PhyllotaxyTypeAngles[] = {180,0,90,90,0};`
- L142 _function_ `` (scope `FPVGrowerSettingsTargetInfo::ToString`)
- L185 _function_ `` (scope `FPVGrowerPhyllotaxyTargetInfo::ToString`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataTypes/PVGrowerParamsData.h` (Private)


#### struct `FPVDataTypeInfoGrowerParams`  
`struct FPVDataTypeInfoGrowerParams : public FPCGDataTypeInfo`  
_L13-18_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L17 _public prototype_ `PCG_DECLARE_TYPE_INFO();`

#### class `UPVGrowerParamsData`  
`class UPVGrowerParamsData : public UPVData`  
_L21-32_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVData`
- L26 _public member_ `FPVGrowerParams Params;`
- L29 _public prototype_ `PCG_ASSIGN_DEFAULT_TYPE_INFO(FPVDataTypeInfoGrowerParams) virtual void AddToCrc(FArchiveCrc32& Ar, bool bFullDataCrc) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataTypes/PVGrowerSettingsData.h` (Private)


#### struct `FPVDataTypeInfoGrowerPhyllotaxy`  
`struct FPVDataTypeInfoGrowerPhyllotaxy : public FPCGDataTypeInfo`  
_L28-38_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L32 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L36 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerPhyllotaxyData`  
`class UPVGrowerPhyllotaxyData : public UPCGData`  
_L41-52_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L46 _public member_ `FPVGrowerPhyllotaxyWithTargets ParamsWithTargets;`
- L50 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(ParamsWithTargets);`

#### struct `FPVDataTypeInfoGrowerAgeSenescence`  
`struct FPVDataTypeInfoGrowerAgeSenescence : public FPCGDataTypeInfo`  
_L55-65_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L59 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L63 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerAgeSenescenceData`  
`class UPVGrowerAgeSenescenceData : public UPCGData`  
_L68-79_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L73 _public member_ `FPVAgeSenescenceParams Params;`
- L77 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoGrowerLightSenescence`  
`struct FPVDataTypeInfoGrowerLightSenescence : public FPCGDataTypeInfo`  
_L82-92_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L86 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L90 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerLightSenescenceData`  
`class UPVGrowerLightSenescenceData : public UPCGData`  
_L95-106_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L100 _public member_ `FPVLightSenescenceParams Params;`
- L104 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoGrowerDirectional`  
`struct FPVDataTypeInfoGrowerDirectional : public FPCGDataTypeInfo`  
_L109-119_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L113 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L117 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerDirectionalData`  
`class UPVGrowerDirectionalData : public UPCGData`  
_L122-133_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L127 _public member_ `FPVGrowerDirectionalWithTargets ParamsWithTargets;`
- L131 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(ParamsWithTargets);`

#### struct `FPVDataTypeInfoGrowerAuxin`  
`struct FPVDataTypeInfoGrowerAuxin : public FPCGDataTypeInfo`  
_L136-146_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L140 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L144 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerAuxinData`  
`class UPVGrowerAuxinData : public UPCGData`  
_L149-160_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L154 _public member_ `FPVGrowerAuxinWithTargets ParamsWithTargets;`
- L158 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(ParamsWithTargets);`

#### struct `FPVDataTypeInfoGrowerGravity`  
`struct FPVDataTypeInfoGrowerGravity : public FPCGDataTypeInfo`  
_L163-173_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L167 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L171 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerGravityData`  
`class UPVGrowerGravityData : public UPCGData`  
_L176-187_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L181 _public member_ `FPVGrowerGravityParams Params;`
- L185 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoGrowerBifurcation`  
`struct FPVDataTypeInfoGrowerBifurcation : public FPCGDataTypeInfo`  
_L190-200_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L194 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L198 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerBifurcationData`  
`class UPVGrowerBifurcationData : public UPCGData`  
_L203-214_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L208 _public member_ `FPVGrowerBifurcationWithTargets ParamsWithTargets;`
- L212 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(ParamsWithTargets);`

#### struct `FPVDataTypeInfoGrowerFoliage`  
`struct FPVDataTypeInfoGrowerFoliage : public FPCGDataTypeInfo`  
_L217-227_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L221 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L225 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerFoliageData`  
`class UPVGrowerFoliageData : public UPCGData`  
_L230-241_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L235 _public member_ `FPVFoliageParams Params;`
- L239 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoGrowerPhototropism`  
`struct FPVDataTypeInfoGrowerPhototropism : public FPCGDataTypeInfo`  
_L244-254_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L248 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L252 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerPhototropismData`  
`class UPVGrowerPhototropismData : public UPCGData`  
_L257-268_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L262 _public member_ `FPVGrowerPhototropismWithTargets ParamsWithTargets;`
- L266 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(ParamsWithTargets);`

#### struct `FPVDataTypeInfoGrowerTrunkGrowth`  
`struct FPVDataTypeInfoGrowerTrunkGrowth : public FPCGDataTypeInfo`  
_L271-281_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L275 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L279 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowerTrunkGrowthData`  
`class UPVGrowerTrunkGrowthData : public UPCGData`  
_L284-295_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L289 _public member_ `FPVTrunkGrowthParams Params;`
- L293 _public prototype_ `PV_GROWER_SETTINGS_OVERRIDE_CRC(Params);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define PV_GROWER_SETTINGS_OVERRIDE_CRC(Params)\`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataTypes/PVMeshBuilderParams.h` (Private)


#### struct `FPVSkeletonShapingEntry`  
`struct FPVSkeletonShapingEntry`  
_L18-51_
- reflection: `USTRUCT()`
- desc: A single per-generation noise layer used by FPVMeshBuilderSkeletonShapingParams.
- L25 _public member_ `int32 Generation = 1;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", DisplayName="Generation", meta=(ClampMin=1, UIMin=1, Tooltip= "The branch-hierarchy generation this entry targets.\n\nGeneration 1 is the trunk. Generation 2 is the first tier of lateral branches, and so on. When Impact Remaining Generations is disabled the noise is applied only to branches whose hierarchy number equals this value."))`
- L30 _public member_ `bool bImpactRemainingGenerations = true;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", DisplayName="Impact Remaining Generations", meta=(Tooltip= "When enabled, this entry also governs all higher-numbered generations that have no entry of their own.\n\nA more specific entry (exact generation match, or a higher-generation fallback entry) always takes precedence over this one. Disable to restrict the effect to the exact generation number above."))`
- L35 _public member_ `float NoiseStrength = 5.0f;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", DisplayName="Noise Strength", meta=(ClampMin=0.0f, ClampMax=200.0f, UIMin=0.0f, UIMax=50.0f, Tooltip= "Amplitude of noise displacement in cm.\n\nHow far branches can bend at their peak displacement. 0 = straight branches. 5 cm = subtle bending. 20+ = dramatic curvature."))`
- L40 _public member_ `float NoiseFrequency = 0.05f;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", DisplayName="Noise Frequency", meta=(ClampMin=0.0001f, ClampMax=1.0f, UIMin=0.001f, UIMax=0.2f, Tooltip= "Spatial frequency of the noise field for this generation.\n\nHigher values produce tighter, more frequent bends; lower values produce broad, sweeping curves."))`
- L45 _public member_ `int32 NoiseSeed = 0;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", DisplayName="Noise Seed", meta=(Tooltip= "Offsets the Perlin noise sampling position for this generation. Each unique value produces a distinct deformation pattern."))`
- L50 _public member_ `float Smoothness = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", DisplayName="Smoothness", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Controls the smoothness of the branch curve. Higher values produce a smoother arc by applying more Laplacian smoothing passes to the branch point positions. Works independently of noise amplitude."))`

#### struct `FPVGenerationRamp`  
`struct FPVGenerationRamp`  
_L55-66_
- reflection: `USTRUCT()`
- desc: Per-generation ramp entry for FPVMeshBuilderBranchRadiusParams::BranchGenerationRamps.
- L60 _public member_ `FPVFloatRamp Ramp;` — `UPROPERTY(EditAnywhere, Category = "Branch Radius", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f))`
- L62 _public function_ `FPVGenerationRamp()`

#### struct `FPVGenerationScale`  
`struct FPVGenerationScale`  
_L70-76_
- reflection: `USTRUCT()`
- desc: Per-generation scale entry for FPVMeshBuilderBranchRadiusParams::BranchGenerationScales.
- L75 _public member_ `float Scale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Branch Radius", meta=(ClampMin=0.0f, UIMin=0.0f, Tooltip="Uniform scale multiplier applied to branch radius for this generation."))`

#### struct `FPVMeshBuilderMeshDetailParams`  
`struct FPVMeshBuilderMeshDetailParams`  
_L88-207_
- reflection: `USTRUCT()`
- L96 _public member_ `int32 SkeletonResolution = 10;` — `UPROPERTY(EditAnywhere, Category="Mesh Details", DisplayName="Skeletal Resolution", meta=(ClampMin=1, ClampMax=100, UIMin=1, UIMax=100, Tooltip= "Number of segments the longest branch is divided into for skeleton interpolation.\n\nHigher values add more interpolated points for smoother branch curvature at the cost of vertex count." ))`
- L102 _public member_ `float PointRemoval = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details", DisplayName="Point Removal", meta=(ClampMin=0.0f, ClampMax=0.1f, UIMin=0.0f, UIMax=0.1f, Tooltip= "Removes small points to simplify the mesh.\n\nReduces the points considered for mesh generation. Depends on Hull, Main Trunk, Ground, and Scale Retention settings. Higher = more aggressive simplification." ))`
- L108 _public member_ `float SegmentReduction = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details", DisplayName="Segment Reduction", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "How aggressively segments are reduced.\n\nSimplifies the branch polyline while preserving overall shape. Higher = fewer edges, lighter mesh. Combine with Retention settings to preserve important regions." ))`
- L114 _public member_ `int32 MinDivisions = 6;` — `UPROPERTY(EditAnywhere, Category="Mesh Details", DisplayName="Min Divisions", meta=(ClampMin=3, ClampMax=1024, UIMin=3, UIMax=36, Tooltip= "Minimum radial polygon count around branch cross-sections.\n\nLower bound on cross-section detail. 3 = triangular cross-sections (very angular); higher values for smooth round branches." ))`
- L120 _public member_ `int32 MaxDivisions = 12;` — `UPROPERTY(EditAnywhere, Category="Mesh Details", DisplayName="Max Divisions", meta=(ClampMin=3, ClampMax=1024, UIMin=3, UIMax=36, Tooltip= "Maximum radial divisions.\n\nUpper limit for cross-section detail on trunks/branches. Balance with Min Divisions to control density across sizes." ))`
- L126 _public member_ `bool AddEndCaps = true;` — `UPROPERTY(EditAnywhere, Category="Mesh Details", DisplayName="Add End Caps", meta=(Tooltip= "Add spherical end caps to branch tips.\n\nWhen on, each branch tip gets a hemispherical cap. Avoids open-ended cylinders. Turn off if your tip foliage will hide the open end anyway." ))`
- L132 _public member_ `int32 Accuracy = 5;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Reduction Accuracy", meta=(ClampMin=1, ClampMax=15, UIMin=1, UIMax=15, Tooltip= "Iterations of the simplification algorithm.\n\nMore iterations = more accurate reduction at the cost of processing power." ))`
- L138 _public member_ `float LongestSegmentLength = 10.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Longest Segment Allowed (meters)", meta=(ClampMin=0.0f, ClampMax=50.0f, UIMin=0.0f, UIMax=10.0f, Tooltip= "Maximum allowed segment length.\n\nCaps segment length after simplification to maintain even geometry and prevent stretched polygons." ))`
- L144 _public member_ `float ShortestSegmentLength = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Shortest Segment Allowed (meters)", meta=(ClampMin=0.0f, ClampMax=50.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Minimum allowed segment length.\n\nSegments shorter than this are merged or removed to avoid unnecessary fine detail that inflates polycount." ))`
- L150 _public member_ `float SegmentRetentionImpact = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Segment Retention Impact", meta=(ClampMin=0.0f, ClampMax=5.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "How strongly retention rules can reintroduce reduced points.\n\nRetention rules (Hull, Main Trunk, Ground, Scale) can reintroduce points the simplifier removed. This multiplier governs how strongly they push back. 0 = retention has no effect; 1 = full impact." ))`
- L156 _public member_ `float HullRetention = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Hull Retention", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Strength of preserving the outer hull.\n\nAdjusts retention of the mesh silhouette during reduction. Higher values protect external shape; lower values allow more simplification." ))`
- L162 _public member_ `float MainTrunkRetention = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Main Trunk Retention", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Preserves detail in the main trunk.\n\nControls how much trunk geometry is retained during simplification. High values keep trunk smooth and detailed; low values reduce complexity." ))`
- L168 _public member_ `float GroundRetention = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Ground Retention", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Preserves detail near ground regions.\n\nAdjusts retention for areas close to the base of the plant. Use higher values to keep root/ground transitions detailed." ))`
- L174 _public member_ `FPVFloatRamp HullRetentionGradient;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Hull Retention Gradient", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip= "Gradient for preserving outer hull detail.\n\nA ramp that varies outer-hull retention across the model. Use to keep silhouettes crisp where needed while simplifying elsewhere." ))`
- L180 _public member_ `FPVFloatRamp MainTrunkRetentionGradient;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Main Trunk Retention Gradient", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip= "Gradient controlling trunk detail retention.\n\nVaries trunk retention via a ramp. Useful to preserve key trunk regions while simplifying others." ))`
- L186 _public member_ `FPVFloatRamp GroundRetentionGradient;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Ground Retention Gradient", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip= "Gradient for preserving ground-region detail.\n\nA ramp that modulates retention around base regions. Tune to keep roots/basal features while allowing simplification above." ))`
- L192 _public member_ `float ScaleRetention = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Scale Retention", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Preserves detail relative to branch size.\n\nRetains more detail on larger/thicker structures and simplifies smaller ones to prioritize visually important geometry." ))`
- L198 _public member_ `FPVFloatRamp ScaleRetentionGradient;` — `UPROPERTY(EditAnywhere, Category="Mesh Details|Advanced", DisplayName="Scale Retention Gradient", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip= "Gradient controlling size-based retention.\n\nUses a ramp to vary how size-dependent retention is applied across the model. Keep large structures crisp while simplifying finer parts." ))`
- L200 _public function_ `FPVMeshBuilderMeshDetailParams()`

#### struct `FPVMeshBuilderProfileDetailParams`  
`struct FPVMeshBuilderProfileDetailParams`  
_L212-233_
- reflection: `USTRUCT()`
- L220 _public member_ `FPVFloatRamp FallOff;` — `UPROPERTY(EditAnywhere, Category="Profile Details", DisplayName="Falloff", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=0.0f, YAxisMax=1.0f, Tooltip = "How the profile shape is applied along trunk/branch length.\n\nX = position from base to tip. Y = profile intensity. Can create root flare (wider profile at base tapering to round at top)." ))`
- L224 _public member_ `float Scale = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Profile Details", DisplayName="Scale", meta=(ClampMin=0.0f, ClampMax=10.0f, UIMin=0.0f, UIMax=10.0f, Tooltip="Scale of the profile applied\n\nCan be used to create a wider base in conjection with Profile Falloff"))`
- L227 _public member_ `bool bApplyToBranches = false;` — `UPROPERTY(EditAnywhere, Category="Profile Details", meta=(Tooltip = "Apply the profile to side branches, not just the trunk.\n\nTurn on for species with consistent cross-section throughout (e.g. cacti)."))`
- L229 _public function_ `FPVMeshBuilderProfileDetailParams()`

#### struct `FPVMeshBuilderBranchRadiusParams`  
`struct FPVMeshBuilderBranchRadiusParams`  
_L238-265_
- reflection: `USTRUCT()`
- L246 _public member_ `float DaVinciRuleStrength = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Branch Radius", DisplayName="DaVinci Rule Strength", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Blend toward physically-plausible branch tapering (Da Vinci's rule).\n\n0 = use existing radius distribution unchanged. 1 = fully apply the cross-sectional area conservation law (parent cross-section = sum of child cross-sections). Higher values produce more realistic branch tapering." ))`
- L252 _public member_ `TArray<FPVGenerationRamp> GenerationRamps;` — `UPROPERTY(EditAnywhere, Category="Branch Radius", DisplayName="Branch Generation Ramps", meta=(Tooltip= "Per-generation ramp curves that remap branch radii within each generation.\n\nArray index 0 targets generation 1 (trunk), index 1 targets generation 2 (first lateral branches), etc. X axis: normalized radius within the generation (0 = thinnest, 1 = thickest). Y axis: output radius as a fraction of the generation maximum. The last entry also governs all higher generations with no dedicated entry. Applied after the DaVinci Rule, before Min Radius." ))`
- L258 _public member_ `TArray<FPVGenerationScale> GenerationScales;` — `UPROPERTY(EditAnywhere, Category="Branch Radius", DisplayName="Branch Generation Scales", meta=(Tooltip= "Per-generation uniform scale multipliers applied to branch radius.\n\nArray index 0 targets generation 1 (trunk), index 1 targets generation 2 (first lateral branches), etc. The last entry also governs all higher generations with no dedicated entry." ))`
- L264 _public member_ `float MinRadius = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Branch Radius", DisplayName="Min Radius", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip= "Minimum radius as a fraction of the max.\n\nRaises the thinnest branches to this floor while leaving the thickest unchanged. 0 = no floor (natural tapering). Higher = thicker twigs (better for older mature plants)." ))`

#### struct `FPVMeshBuilderDisplacementParams`  
`struct FPVMeshBuilderDisplacementParams`  
_L270-300_
- reflection: `USTRUCT()`
- L278 _public member_ `TObjectPtr<UTexture2D> Texture = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Displacement", meta=(Tooltip= "Texture used to drive mesh displacement.\n\nAssigns the texture map that controls displacement. Bright and dark areas in the texture push or pull the mesh surface to create additional geometric detail such as bark roughness, grooves, or ridges.\n\nOnly power of 2 textures with source texture formats (TSF_RGBA32F, TSF_RGBA16F, TSF_BGRA8, TSF_R32F, TSF_R16F, TSF_G8) are supported.\n\nFor formats TSF_RGBA32F, TSF_RGBA16F and TSF_BGRA8 data from R channel is used." ))`
- L283 _public member_ `float Strength = 0.5f;` — `UPROPERTY(EditAnywhere, Category="Displacement", DisplayName="Scale", meta=(Tooltip= "Intensity of displacement effect.\n\nHigher = more exaggerated surface depth. Lower = subtler. Balance with mesh stability — extreme values can cause polygons to overlap."))`
- L288 _public member_ `float Bias = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Displacement", DisplayName="Bias", meta=(Tooltip = "Shifts the midpoint of displacement.\n\nOffsets the neutral level of the displacement map. Positive bias lifts the surface outward. Useful for correcting textures that displace unevenly or need centering."))`
- L294 _public member_ `FVector2f UVScale = FVector2f(1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category="Displacement", DisplayName="UV Scale", meta=(Tooltip= "Tiling of the displacement texture (U, V).\n\nHigher values increase tiling frequency (smaller repeats). Lower values stretch the texture. 1 = native tile size." ))`
- L299 _public member_ `int32 GenerationUpperLimit = 1;` — `UPROPERTY(EditAnywhere, Category="Displacement", DisplayName="Generation Upper Limit", meta=(ClampMin=1, ClampMax=10, UIMin=1, UIMax=10, Tooltip= "Apply displacement only up to this generation.\n\n1 = trunk only. 2 = trunk + first branches. Higher = more generations covered. Limits performance cost on fine twigs where displacement would be invisible."))`

#### struct `FPVMeshBuilderSkeletonShapingParams`  
`struct FPVMeshBuilderSkeletonShapingParams`  
_L305-313_
- reflection: `USTRUCT()`
- L312 _public member_ `TArray<FPVSkeletonShapingEntry> Entries;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", meta=(Tooltip= "Per-generation noise layers.\n\nEach entry targets a specific generation. Higher-generation entries override lower-generation fallbacks when bImpactRemainingGenerations is on."))`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/DataTypes/PVMeshBuilderSettingsData.h` (Private)


#### struct `FPVDataTypeInfoMeshBuilderMeshDetail`  
`struct FPVDataTypeInfoMeshBuilderMeshDetail : public FPCGDataTypeInfo`  
_L31-40_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L35 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L38 _public function_ `virtual bool Hidden() const override`

#### class `UPVMeshBuilderMeshDetailData`  
`class UPVMeshBuilderMeshDetailData : public UPCGData`  
_L43-54_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L48 _public member_ `FPVMeshBuilderMeshDetailParams Params;`
- L52 _public prototype_ `PV_MESH_BUILDER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoMeshBuilderProfileDetail`  
`struct FPVDataTypeInfoMeshBuilderProfileDetail : public FPCGDataTypeInfo`  
_L59-68_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L63 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L66 _public function_ `virtual bool Hidden() const override`

#### class `UPVMeshBuilderProfileDetailData`  
`class UPVMeshBuilderProfileDetailData : public UPCGData`  
_L71-82_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L76 _public member_ `FPVMeshBuilderProfileDetailParams Params;`
- L80 _public prototype_ `PV_MESH_BUILDER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoMeshBuilderBranchRadius`  
`struct FPVDataTypeInfoMeshBuilderBranchRadius : public FPCGDataTypeInfo`  
_L87-96_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L91 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L94 _public function_ `virtual bool Hidden() const override`

#### class `UPVMeshBuilderBranchRadiusData`  
`class UPVMeshBuilderBranchRadiusData : public UPCGData`  
_L99-110_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L104 _public member_ `FPVMeshBuilderBranchRadiusParams Params;`
- L108 _public prototype_ `PV_MESH_BUILDER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoMeshBuilderDisplacement`  
`struct FPVDataTypeInfoMeshBuilderDisplacement : public FPCGDataTypeInfo`  
_L115-124_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L119 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L122 _public function_ `virtual bool Hidden() const override`

#### class `UPVMeshBuilderDisplacementData`  
`class UPVMeshBuilderDisplacementData : public UPCGData`  
_L127-141_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L132 _public member_ `FPVMeshBuilderDisplacementParams Params;`
- L135 _public member_ `TArray<float> Values;` — Cached pixel values extracted from Params.Texture, computed once when this data is produced.
- L139 _public prototype_ `PV_MESH_BUILDER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoMeshBuilderSkeletonShaping`  
`struct FPVDataTypeInfoMeshBuilderSkeletonShaping : public FPCGDataTypeInfo`  
_L146-155_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L150 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L153 _public function_ `virtual bool Hidden() const override`

#### class `UPVMeshBuilderSkeletonShapingData`  
`class UPVMeshBuilderSkeletonShapingData : public UPCGData`  
_L158-169_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L163 _public member_ `FPVMeshBuilderSkeletonShapingParams Params;`
- L167 _public prototype_ `PV_MESH_BUILDER_SETTINGS_OVERRIDE_CRC(Params);`

#### struct `FPVDataTypeInfoMeshBuilderMaterialDetail`  
`struct FPVDataTypeInfoMeshBuilderMaterialDetail : public FPCGDataTypeInfo`  
_L174-183_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L178 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L181 _public function_ `virtual bool Hidden() const override`

#### class `UPVMeshBuilderMaterialDetailData`  
`class UPVMeshBuilderMaterialDetailData : public UPCGData`  
_L186-197_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGData`
- L191 _public member_ `FPVMaterialSettings Params;`
- L195 _public prototype_ `PV_MESH_BUILDER_SETTINGS_OVERRIDE_CRC(Params);`

#### Free symbols / members of external scopes

- L12 _macro_ `#define PV_MESH_BUILDER_SETTINGS_OVERRIDE_CRC(Params)\`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Facades/PVFacadeCommon.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PV`
- L7 _namespace_ `namespace Facades` (scope `PV`)
- L9 _macro_ `#define FILL_COLLECTION_ATTRIBUTE(Accessor, InputArray) \`
- L23 _macro_ `#define FILL_COLLECTION_ATTRIBUTE_FROM_INDEX(Accessor, InputArray, StartIndex) \`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Facades/PVFoliageAttributesNames.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PV`
- L6 _namespace_ `namespace GroupNames` (scope `PV`)
- L8 _variable_ `inline static const FName FoliageConditionGroup = FName(TEXT("Foli` (scope `PV::GroupNames`)
- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace FoliageAttributeNames` (scope `PV`)
- L15 _variable_ `inline static const FName FoliageNameID = FName(TEXT("Foli` (scope `PV::FoliageAttributeNames`) — Foliage Attributes
- L16 _variable_ `inline static const FName FoliageBranchID = FName(TEXT("Foli` (scope `PV::FoliageAttributeNames`)
- L17 _variable_ `inline static const FName FoliagePivotPoint = FName(TEXT("Foli` (scope `PV::FoliageAttributeNames`)
- L18 _variable_ `inline static const FName FoliageUPVector = FName(TEXT("Foli` (scope `PV::FoliageAttributeNames`)
- L19 _variable_ `inline static const FName FoliageNormalVector = FName(TEXT("Foli` (scope `PV::FoliageAttributeNames`)
- L20 _variable_ `inline static const FName FoliageScale = FName(TEXT("Foli` (scope `PV::FoliageAttributeNames`)
- L21 _variable_ `inline static const FName FoliageLengthFromRoot = FName(TEXT("Leng` (scope `PV::FoliageAttributeNames`)
- L22 _variable_ `inline static const FName FoliageConditionLight = FName(TEXT("Cond` (scope `PV::FoliageAttributeNames`)
- L23 _variable_ `inline static const FName FoliageConditionTip = FName(TEXT("Cond` (scope `PV::FoliageAttributeNames`)
- L24 _variable_ `inline static const FName FoliageConditionScale = FName(TEXT("Cond` (scope `PV::FoliageAttributeNames`)
- L25 _variable_ `inline static const FName FoliageConditionUpAlignment = FName(TEXT("Cond` (scope `PV::FoliageAttributeNames`)
- L26 _variable_ `inline static const FName FoliageConditionHealth = FName(TEXT("Cond` (scope `PV::FoliageAttributeNames`)
- L27 _variable_ `inline static const FName FoliageConditionHeight = FName(TEXT("Cond` (scope `PV::FoliageAttributeNames`)
- L28 _variable_ `inline static const FName FoliageConditionGeneration = FName(TEXT("Cond` (scope `PV::FoliageAttributeNames`)
- L29 _variable_ `inline static const FName FoliageParentBoneID = FName(TEXT("Foli` (scope `PV::FoliageAttributeNames`)
- L32 _variable_ `inline static const FName FoliageUseAsMask = FName(TEXT("UseA` (scope `PV::FoliageAttributeNames`) — FoliageInfo Attributes
- L33 _variable_ `inline static const FName FoliageName = FName(TEXT("Name` (scope `PV::FoliageAttributeNames`)
- L34 _variable_ `inline static const FName FoliageAttributeLight = FName(TEXT("Ligh` (scope `PV::FoliageAttributeNames`)
- L35 _variable_ `inline static const FName FoliageAttributeScale = FName(TEXT("Scal` (scope `PV::FoliageAttributeNames`)
- L36 _variable_ `inline static const FName FoliageAttributeTip = FName(TEXT("Tip"` (scope `PV::FoliageAttributeNames`)
- L37 _variable_ `inline static const FName FoliageAttributeUpAlignment = FName(TEXT("UpAl` (scope `PV::FoliageAttributeNames`)
- L38 _variable_ `inline static const FName FoliageAttributeHealth = FName(TEXT("Heal` (scope `PV::FoliageAttributeNames`)
- L39 _variable_ `inline static const FName FoliageAttributeHeight = FName(TEXT("Heig` (scope `PV::FoliageAttributeNames`)
- L40 _variable_ `inline static const FName FoliageAttributeGeneration = FName(TEXT("Gene` (scope `PV::FoliageAttributeNames`)
- L43 _variable_ `inline static const FName ConditionName = FName(TEXT("Name` (scope `PV::FoliageAttributeNames`) — Condition
- L44 _variable_ `inline static const FName ConditionWeight = FName(TEXT("Weig` (scope `PV::FoliageAttributeNames`)
- L45 _variable_ `inline static const FName ConditionOffset = FName(TEXT("Offs` (scope `PV::FoliageAttributeNames`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Facades/PVFoliageConditionFacade.h` (Private)


#### struct `PV::Facades::FFoliageConditonInfo`  
`struct FFoliageConditonInfo`  
_L12-34_
- L14 _public member_ `FString Name;`
- L15 _public member_ `float Weight;`
- L16 _public member_ `float Offset;`
- L18 _public function_ `EPVDistributionCondition GetType() const`
- L30 _public function_ `FString ToString() const`

#### class `PV::Facades::FFoliageConditionFacade`  
`class FFoliageConditionFacade`  
_L36-61_
- L39 _public prototype_ `FFoliageConditionFacade(FManagedArrayCollection& InCollection);`
- L40 _public prototype_ `FFoliageConditionFacade(const FManagedArrayCollection& InCollection);`
- L42 _public prototype_ `bool IsValid() const;`
- L44 _public function_ `int32 NumEntries() const`
- L46 _public prototype_ `int32 Add(const FFoliageConditonInfo& InputData);`
- L48 _public prototype_ `void Set(const int32 Index, const FFoliageConditonInfo& InputData);`
- L49 _public prototype_ `void SetData(const TArray<FFoliageConditonInfo>& Infos);`
- L51 _public prototype_ `FFoliageConditonInfo GetEntry(const int32 Index) const;`
- L53 _public prototype_ `TArray<FFoliageConditonInfo> GetData() const;`
- L56 _protected prototype_ `void DefineSchema(FManagedArrayCollection& InCollection);`
- L58 _protected member_ `TManagedArrayAccessor<FString> NameAttribute;`
- L59 _protected member_ `TManagedArrayAccessor<float> WeightAttribute;`
- L60 _protected member_ `TManagedArrayAccessor<float> OffsetAttribute;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PV`
- L10 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVAttributesHelper.h` (Private)


#### struct `PV::AttributesHelper::FComputeBudNumbersAttributes`  
`struct FComputeBudNumbersAttributes`  
_L56-81_
- L58 _public member_ `FPointBudNumberAttributeView PointBudNumber;`
- L59 _public member_ `FBranchSourceBudNumberAttributeView BranchSourceBudNumber;`
- L60 _public member_ `FBranchPointsAttributeConstView BranchPoints;`
- L62 _public function_ `FComputeBudNumbersAttributes( FPointBudNumberAttributeView InPointBudNumber, FBranchSourceBudNumberAttributeView InBranchSourceBudNumber, FBranchPointsAttributeConstView InBranchPoints) : PointBudNumber(InPointBudNumber) , BranchSourceBudNumber(InBranchSourceBudNumber) , BranchPoints(InBranchPoints)`
- L71 _public function_ `FComputeBudNumbersAttributes(FManagedArrayCollection& InCollection) : PointBudNumber(FPointBudNumberAttribute::FindAttribute(InCollection)) , BranchSourceBudNumber(FBranchSourceBudNumberAttribute::FindAttribute(InCollection)) , BranchPoints(FBranchPointsAttribute::FindAttribute(InCollection))`
- L77 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeNjordPixelIndexAttributes`  
`struct FComputeNjordPixelIndexAttributes`  
_L86-109_
- L88 _public member_ `PV::FPointNjordPixelIndexAttributeView PointNjordPixelIndex;`
- L89 _public member_ `FPointBudNumberAttributeView PointBudNumber;`
- L91 _public function_ `FComputeNjordPixelIndexAttributes( FPointBudNumberAttributeView InPointBudNumber, PV::FPointNjordPixelIndexAttributeView InPointNjordPixelIndex) : PointNjordPixelIndex(InPointNjordPixelIndex) , PointBudNumber(InPointBudNumber)`
- L99 _public function_ `FComputeNjordPixelIndexAttributes(FManagedArrayCollection& InCollection) : PointNjordPixelIndex(PV::FPointNjordPixelIndexAttribute::FindAttribute(InCollection)) , PointBudNumber(FPointBudNumberAttribute::FindAttribute(InCollection))`
- L105 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeLengthFromRootAttributes`  
`struct FComputeLengthFromRootAttributes`  
_L114-157_
- L116 _public member_ `PV::FPointLengthFromRootAttributeView PointLengthFromRoot;`
- L117 _public member_ `PV::FPointLengthFromSeedAttributeView PointLengthFromSeed;`
- L118 _public member_ `PV::FPointPositionAttributeConstView PointPosition;`
- L119 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L120 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L121 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L122 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L124 _public function_ `FComputeLengthFromRootAttributes( PV::FPointLengthFromRootAttributeView InPointLengthFromRoot, PV::FPointLengthFromSeedAttributeView InPointLengthFromSeed, PV::FPointPositionAttributeConstView InPointPosition, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchNumberAttributeConstView InBranchNumber, PV::FBranchChildrenAttributeConstView InBranchChildren) : PointLengthFromRoot(InPointLengthFromRoot) , PointLengthFromSeed(InPointLengthFromSeed) , PointPosition(InPointPosition) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchNumber(InBranchNumber) , BranchChildren(InBranchChildren)`
- L142 _public function_ `FComputeLengthFromRootAttributes(FManagedArrayCollection& Collection) : PointLengthFromRoot(PV::FPointLengthFromRootAttribute::FindAttribute(Collection)) , PointLengthFromSeed(PV::FPointLengthFromSeedAttribute::FindAttribute(Collection)) , PointPosition(PV::FPointPositionAttribute::FindAttribute(Collection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(Collection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(Collection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(Collection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(Collection))`
- L153 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeLengthFromTrunkAttributes`  
`struct FComputeLengthFromTrunkAttributes`  
_L162-206_
- L164 _public member_ `PV::FPointLengthFromRootAttributeConstView PointLengthFromRoot;`
- L165 _public member_ `PV::FBudDevelopmentAttributeConstView BudDevelopment;`
- L166 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L167 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L168 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L169 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L171 _public function_ `FComputeLengthFromTrunkAttributes( PV::FPointLengthFromRootAttributeConstView InPointLengthFromRoot, PV::FBudDevelopmentAttributeConstView InBudDevelopment, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchNumberAttributeConstView InBranchNumber, PV::FBranchChildrenAttributeConstView InBranchChildren) : PointLengthFromRoot(InPointLengthFromRoot) , BudDevelopment(InBudDevelopment) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchNumber(InBranchNumber) , BranchChildren(InBranchChildren)`
- L186 _public function_ `FComputeLengthFromTrunkAttributes(const FManagedArrayCollection& Collection) : PointLengthFromRoot(PV::FPointLengthFromRootAttribute::FindAttribute(Collection)) , BudDevelopment(PV::FBudDevelopmentAttribute::FindAttribute(Collection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(Collection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(Collection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(Collection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(Collection))`
- L195 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeBudDevelopmentAttributes`  
`struct FComputeBudDevelopmentAttributes`  
_L209-246_
- L211 _public member_ `PV::FBudDevelopmentAttributeView BudDevelopment;`
- L212 _public member_ `PV::FPointPlantGradientAttributeConstView PointPlantGradient;`
- L213 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L214 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L215 _public member_ `PV::FBranchParentsAttributeConstView BranchParents;`
- L216 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L218 _public function_ `FComputeBudDevelopmentAttributes( PV::FBudDevelopmentAttributeView InBudDevelopment, PV::FPointPlantGradientAttributeConstView InPointPlantGradient, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchParentsAttributeConstView InBranchParents, PV::FBranchNumberAttributeConstView InBranchNumber) : BudDevelopment(InBudDevelopment) , PointPlantGradient(InPointPlantGradient) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchParents(InBranchParents) , BranchNumber(InBranchNumber)`
- L233 _public function_ `FComputeBudDevelopmentAttributes(FManagedArrayCollection& InCollection) : BudDevelopment(PV::FBudDevelopmentAttribute::FindAttribute(InCollection)) , PointPlantGradient(PV::FPointPlantGradientAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchParents(PV::FBranchParentsAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection))`
- L242 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeBudDirectionsAttributes`  
`struct FComputeBudDirectionsAttributes`  
_L251-288_
- L253 _public member_ `PV::FBudDirectionAttributeView BudDirection;`
- L254 _public member_ `PV::FPointPositionAttributeConstView PointPosition;`
- L255 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L256 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L257 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L258 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L260 _public function_ `FComputeBudDirectionsAttributes( PV::FBudDirectionAttributeView InBudDirection, PV::FPointPositionAttributeConstView InPointPosition, PV::FBranchChildrenAttributeConstView InBranchChildren, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchNumberAttributeConstView InBranchNumber, PV::FBranchPointsAttributeConstView InBranchPoints) : BudDirection(InBudDirection) , PointPosition(InPointPosition) , BranchChildren(InBranchChildren) , BranchParentNumber(InBranchParentNumber) , BranchNumber(InBranchNumber) , BranchPoints(InBranchPoints)`
- L275 _public function_ `FComputeBudDirectionsAttributes(FManagedArrayCollection& InCollection) : BudDirection(PV::FBudDirectionAttribute::FindAttribute(InCollection)) , PointPosition(PV::FPointPositionAttribute::FindAttribute(InCollection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection))`
- L284 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeBudHormoneLevelsAttributes`  
`struct FComputeBudHormoneLevelsAttributes`  
_L293-302_
- L295 _public member_ `PV::FBudHormoneLevelsAttributeView BudHormoneLevels;`
- L296 _public member_ `PV::FPointPlantGradientAttributeConstView PointPlantGradient;`
- L298 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputePointGroundGradientAttributes`  
`struct FComputePointGroundGradientAttributes`  
_L307-327_
- L309 _public member_ `PV::FPointGroundGradientAttributeView PointGroundGradient;`
- L310 _public member_ `PV::FPointPositionAttributeConstView PointPosition;`
- L312 _public function_ `FComputePointGroundGradientAttributes( PV::FPointGroundGradientAttributeView InPointGroundGradient, PV::FPointPositionAttributeConstView InPointLengthFromRoot) : PointGroundGradient(InPointGroundGradient) , PointPosition(InPointLengthFromRoot)`
- L320 _public function_ `FComputePointGroundGradientAttributes(FManagedArrayCollection& InCollection) : PointGroundGradient(PV::FPointGroundGradientAttribute::FindAttribute(InCollection)) , PointPosition(PV::FPointPositionAttribute::FindAttribute(InCollection))`
- L326 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputePointScaleGradientAttributes`  
`struct FComputePointScaleGradientAttributes`  
_L331-351_
- L333 _public member_ `PV::FPointScaleGradientAttributeView PointScaleGradient;`
- L334 _public member_ `PV::FPointScaleAttributeConstView PointScale;`
- L336 _public function_ `FComputePointScaleGradientAttributes( PV::FPointScaleGradientAttributeView InPointScaleGradient, PV::FPointScaleAttributeConstView InPointScale) : PointScaleGradient(InPointScaleGradient) , PointScale(InPointScale)`
- L344 _public function_ `FComputePointScaleGradientAttributes(FManagedArrayCollection& InCollection) : PointScaleGradient(PV::FPointScaleGradientAttribute::FindAttribute(InCollection)) , PointScale(PV::FPointScaleAttribute::FindAttribute(InCollection))`
- L350 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputePointPlantGradientAttributes`  
`struct FComputePointPlantGradientAttributes`  
_L355-390_
- L357 _public member_ `PV::FPointPlantGradientAttributeView PointPlantGradient;`
- L358 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L359 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L360 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L361 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L363 _public function_ `FComputePointPlantGradientAttributes( PV::FPointPlantGradientAttributeView InPointPlantGradient, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchNumberAttributeConstView InBranchNumber, PV::FBranchChildrenAttributeConstView InBranchChildren) : PointPlantGradient(InPointPlantGradient) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchNumber(InBranchNumber) , BranchChildren(InBranchChildren)`
- L377 _public function_ `FComputePointPlantGradientAttributes(FManagedArrayCollection& InCollection) : PointPlantGradient(PV::FPointPlantGradientAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(InCollection))`
- L386 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputePointHullGradientAttributes`  
`struct FComputePointHullGradientAttributes`  
_L394-425_
- L396 _public member_ `PV::FPointHullGradientAttributeView PointHullGradient;`
- L397 _public member_ `PV::FPointPositionAttributeConstView PointPosition;`
- L398 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L399 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L401 _public function_ `FComputePointHullGradientAttributes( PV::FPointHullGradientAttributeView InPointHullGradient, PV::FPointPositionAttributeConstView InPointPosition, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber) : PointHullGradient(InPointHullGradient) , PointPosition(InPointPosition) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber)`
- L413 _public function_ `FComputePointHullGradientAttributes(FManagedArrayCollection& InCollection) : PointHullGradient(PV::FPointHullGradientAttribute::FindAttribute(InCollection)) , PointPosition(PV::FPointPositionAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection))`
- L421 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputePointMainTrunkGradientAttributes`  
`struct FComputePointMainTrunkGradientAttributes`  
_L429-468_
- L431 _public member_ `PV::FPointMainTrunkGradientAttributeView PointMainTrunkGradient;`
- L432 _public member_ `PV::FPointPositionAttributeConstView PointPosition;`
- L433 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L434 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L435 _public member_ `PV::FBranchPlantNumberAttributeConstView BranchPlantNumber;`
- L436 _public member_ `PV::FBudDevelopmentAttributeConstView BudDevelopment;`
- L438 _public function_ `FComputePointMainTrunkGradientAttributes( PV::FPointMainTrunkGradientAttributeView InPointMainTrunkGradient, PV::FPointPositionAttributeConstView InPointPosition, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchPlantNumberAttributeConstView InBranchPlantNumber, PV::FBudDevelopmentAttributeConstView InBudDevelopment) : PointMainTrunkGradient(InPointMainTrunkGradient) , PointPosition(InPointPosition) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchPlantNumber(InBranchPlantNumber) , BudDevelopment(InBudDevelopment)`
- L454 _public function_ `FComputePointMainTrunkGradientAttributes(FManagedArrayCollection& InCollection) : PointMainTrunkGradient(PV::FPointMainTrunkGradientAttribute::FindAttribute(InCollection)) , PointPosition(PV::FPointPositionAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchPlantNumber(PV::FBranchPlantNumberAttribute::FindAttribute(InCollection)) , BudDevelopment(PV::FBudDevelopmentAttribute::FindAttribute(InCollection))`
- L464 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeBudStatusAttributes`  
`struct FComputeBudStatusAttributes`  
_L472-506_
- L474 _public member_ `PV::FBudStatusAttributeView BudStatus;`
- L475 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L476 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L477 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L478 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L480 _public function_ `FComputeBudStatusAttributes(PV::FBudStatusAttributeView InBudStatus, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchNumberAttributeConstView InBranchNumber, PV::FBranchChildrenAttributeConstView InBranchChildren) : BudStatus(InBudStatus) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchNumber(InBranchNumber) , BranchChildren(InBranchChildren)`
- L493 _public function_ `FComputeBudStatusAttributes(FManagedArrayCollection& InCollection) : BudStatus(PV::FBudStatusAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(InCollection))`
- L502 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeBudLateralMeristemAttributes`  
`struct FComputeBudLateralMeristemAttributes`  
_L511-562_
- L513 _public member_ `PV::FBudLateralMeristemAttributeView BudLateralMeristem;`
- L514 _public member_ `PV::FPointPositionAttributeConstView PointPosition;`
- L515 _public member_ `PV::FPointScaleAttributeConstView PointScale;`
- L516 _public member_ `PV::FPointLengthFromRootAttributeConstView PointLengthFromRoot;`
- L517 _public member_ `PV::FBudDirectionAttributeConstView BudDirection;`
- L518 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L519 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L520 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L521 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L523 _public function_ `FComputeBudLateralMeristemAttributes(FManagedArrayCollection& InCollection) : BudLateralMeristem(PV::FBudLateralMeristemAttribute::FindAttribute(InCollection)) , PointPosition(PV::FPointPositionAttribute::FindAttribute(InCollection)) , PointScale(PV::FPointScaleAttribute::FindAttribute(InCollection)) , PointLengthFromRoot(PV::FPointLengthFromRootAttribute::FindAttribute(InCollection)) , BudDirection(PV::FBudDirectionAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection))`
- L536 _public function_ `FComputeBudLateralMeristemAttributes( PV::FBudLateralMeristemAttributeView InBudLateralMeristem, PV::FPointPositionAttributeConstView InPointPosition, PV::FPointScaleAttributeConstView InPointScale, PV::FPointLengthFromRootAttributeConstView InPointLengthFromRoot, PV::FBudDirectionAttributeConstView InBudDirection, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchChildrenAttributeConstView InBranchChildren, PV::FBranchNumberAttributeConstView InBranchNumber) : BudLateralMeristem(InBudLateralMeristem) , PointPosition(InPointPosition) , PointScale(InPointScale) , PointLengthFromRoot(InPointLengthFromRoot) , BudDirection(InBudDirection) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchChildren(InBranchChildren) , BranchNumber(InBranchNumber)`
- L558 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FEstimateBudLightDetectedAttributes`  
`struct FEstimateBudLightDetectedAttributes`  
_L567-623_
- L569 _public member_ `PV::FPointHullGradientAttributeConstView PointHullGradient;`
- L570 _public member_ `PV::FPointGroundGradientAttributeConstView PointGroundGradient;`
- L571 _public member_ `PV::FBudStatusAttributeConstView BudStatus;`
- L572 _public member_ `PV::FBudLightDetectedAttributeView BudLightDetected;`
- L573 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L574 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L575 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L576 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L578 _public function_ `FEstimateBudLightDetectedAttributes( PV::FPointHullGradientAttributeConstView InPointHullGradient, PV::FPointGroundGradientAttributeConstView InPointGroundGradient, PV::FBudStatusAttributeConstView InBudStatus, PV::FBudLightDetectedAttributeView InBudLightDetected, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchChildrenAttributeConstView InBranchChildren, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchNumberAttributeConstView InBranchNumber) : PointHullGradient(InPointHullGradient) , PointGroundGradient(InPointGroundGradient) , BudStatus(InBudStatus) , BudLightDetected(InBudLightDetected) , BranchPoints(InBranchPoints) , BranchChildren(InBranchChildren) , BranchParentNumber(InBranchParentNumber) , BranchNumber(InBranchNumber)`
- L598 _public function_ `FEstimateBudLightDetectedAttributes(FManagedArrayCollection& InCollection) : PointHullGradient(PV::FPointHullGradientAttribute::FindAttribute(InCollection)) , PointGroundGradient(PV::FPointGroundGradientAttribute::FindAttribute(InCollection)) , BudStatus(PV::FBudStatusAttribute::FindAttribute(InCollection)) , BudLightDetected(PV::FBudLightDetectedAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection))`
- L610 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FComputeBranchHierarchyNumberAttributes`  
`struct FComputeBranchHierarchyNumberAttributes`  
_L628-659_
- L630 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L631 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L632 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L633 _public member_ `PV::FBranchHierarchyNumberAttributeView BranchHierarchyNumber;`
- L635 _public function_ `FComputeBranchHierarchyNumberAttributes( PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchNumberAttributeConstView InBranchNumber, PV::FBranchChildrenAttributeConstView InBranchChildren, PV::FBranchHierarchyNumberAttributeView InBranchHierarchyNumber) : BranchParentNumber(InBranchParentNumber) , BranchNumber(InBranchNumber) , BranchChildren(InBranchChildren) , BranchHierarchyNumber(InBranchHierarchyNumber)`
- L647 _public function_ `FComputeBranchHierarchyNumberAttributes(FManagedArrayCollection& InCollection) : BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(InCollection)) , BranchHierarchyNumber(PV::FBranchHierarchyNumberAttribute::FindAttribute(InCollection))`
- L655 _public function_ `bool IsValid() const`

#### struct `PV::AttributesHelper::FRecomputeGrowthDataAttributes`  
`struct FRecomputeGrowthDataAttributes`  
_L664-744_
- L666 _public member_ `FPointPositionAttributeConstView PointPosition;`
- L667 _public member_ `FBranchPointsAttributeConstView BranchPoints;`
- L668 _public member_ `FBranchParentNumberAttributeConstView BranchParentNumber;`
- L669 _public member_ `FBranchParentsAttributeConstView BranchParents;`
- L670 _public member_ `FBranchNumberAttributeConstView BranchNumber;`
- L671 _public member_ `FBranchChildrenAttributeConstView BranchChildren;`
- L672 _public member_ `FBranchHierarchyNumberAttributeConstView BranchHierarchyNumber;`
- L673 _public member_ `FBranchPlantNumberAttributeConstView BranchPlantNumber;`
- L674 _public member_ `FPointScaleAttributeView PointScale;`
- L675 _public member_ `FPointBudNumberAttributeView PointBudNumber;`
- L676 _public member_ `FBranchSourceBudNumberAttributeView BranchSourceBudNumber;`
- L677 _public member_ `FPointLengthFromRootAttributeView PointLengthFromRoot;`
- L678 _public member_ `FPointLengthFromSeedAttributeView PointLengthFromSeed;`
- L679 _public member_ `FBudDirectionAttributeView BudDirection;`
- L680 _public member_ `FBudLightDetectedAttributeView BudLightDetected;`
- L681 _public member_ `FBudLateralMeristemAttributeView BudLateralMeristem;`
- L682 _public member_ `FPointGroundGradientAttributeView PointGroundGradient;`
- L683 _public member_ `FPointScaleGradientAttributeView PointScaleGradient;`
- L684 _public member_ `FPointPlantGradientAttributeView PointPlantGradient;`
- L685 _public member_ `FPointHullGradientAttributeView PointHullGradient;`
- L686 _public member_ `FPointMainTrunkGradientAttributeView PointMainTrunkGradient;`
- L687 _public member_ `FBudDevelopmentAttributeView BudDevelopment;`
- L688 _public member_ `FBudHormoneLevelsAttributeView BudHormoneLevels;`
- L689 _public member_ `FBudStatusAttributeView BudStatus;`
- L691 _public prototype_ `FRecomputeGrowthDataAttributes() = default;`
- L692 _public function_ `FRecomputeGrowthDataAttributes(FManagedArrayCollection& InCollection) : PointPosition(FPointPositionAttribute::FindAttribute(InCollection)) , BranchPoints(FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchParents(FBranchParentsAttribute::FindAttribute(InCollection)) , BranchNumber(FBranchNumberAttribute::FindAttribute(InCollection)) , BranchChildren(FBranchChildrenAttribute::FindAttribute(InCollection)) , BranchHierarchyNumber(FBranchHierarchyNumberAttribute::FindAttribute(InCollection)) , BranchPlantNumber(FBranchPlantNumberAttribute::FindAttribute(InCollection)) , PointScale(FPointScaleAttribute::FindAttribute(InCollection)) , PointBudNumber(FPointBudNumberAttribute::FindAttribute(InCollection)) , BranchSourceBudNumber(FBranchSourceBudNumberAttribute::FindAttribute(InCollection)) , PointLengthFromRoot(FPointLengthFromRootAttribute::FindAttribute(InCollection)) , PointLengthFromSeed(FPointLengthFromSeedAttribute::FindAttribute(InCollection)) , BudDirection(FBudDirectionAttribute::FindAttribute(InCollection)) , BudLightDetected(FBudLightDetectedAttribute::FindAttribute(InCollection)) , BudLateralMeristem(FBudLateralMeristemAttribute::FindAttribute(InCollection)) , PointGroundGradient(FPointGroundGradientAttribute::FindAttribute(InCollection)) , PointScaleGradient(FPointScaleGradientAttribute::FindAttribute(InCollection)) , PointPlantGradient(FPointPlantGradientAttribute::FindAttribute(I ...`
- L719 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PV`
- L6 _namespace_ `namespace AttributesHelper` (scope `PV`)
- L8 _prototype_ `float GetBranchPointBranchGradient( PV::FPointLengthFromRootAttributeConstView PointLengthFromRootAttribute, PV::FBranchPointsAttributeConstView BranchPointsAttribute, int32 BranchIndex, int32 BranchPointIndex );` (scope `PV::AttributesHelper`)
- L15 _prototype_ `float GetBranchPointScale( PV::FPointScaleAttributeConstView PointScaleAttribute, PV::FBranchPointsAttributeConstView BranchPointsAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, int32 BranchIndex, int32 BranchPointIndex );` (scope `PV::AttributesHelper`)
- L27 _prototype_ `TArray<FVector3f> GetBudDirection( PV::FBudDirectionAttributeConstView BudDirectionAttribute, PV::FBranchPointsAttributeConstView BranchPointsAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, PV::FPointPositionAttributeConstView PointPositionAttribute, const int32 BranchIndex, const int32 BranchPointIndex );` (scope `PV::AttributesHelper`) — Returns the bud directions for the given branch point. For non-trunk branches, the 0th branch ring is the fused point shared with the parent; the frame is recomputed by rotating the first child point's axillary and up vectors through the dihedral from apical_next to dir, so callers always receive the correct child-branch frame without extra fused-point handling.
- L39 _prototype_ `TArray<int32> GetBudDevelopment( PV::FBudDevelopmentAttributeConstView BudDevelopmentAttribute, PV::FBranchPointsAttributeConstView BranchPointsAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, int32 BranchIndex, int32 BranchPointIndex );` (scope `PV::AttributesHelper`) — Returns the BudDevelopment data for a branch point, correctly handling the fused root point. For non-trunk branches, BranchPointIndex 0 is shared with the parent and retains the parent's BudDevelopment. This helper redirects to BranchPoints[1] (the first owned child point) instead.
- L49 _prototype_ `int32 GetBranchGeneration( PV::FBudDevelopmentAttributeConstView BudDevelopmentAttribute, PV::FBranchPointsAttributeConstView BranchPointsAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, int32 BranchIndex );` (scope `PV::AttributesHelper`) — Returns the Generation of the given branch. Returns INDEX_NONE if the inputs are invalid or the branch has no points.
- L84 _prototype_ `void ComputeBudNumbers(const FComputeBudNumbersAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes the point bud numbers and writes them to the BudNumber and BranchSourceBudNumber attributes.
- L112 _prototype_ `void ComputeNjordPixelIndex(const FComputeNjordPixelIndexAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes all njord pixel indices and writes them to the NjordPixelIndexAttribute.
- L160 _prototype_ `void ComputeLengthFromRoot(const FComputeLengthFromRootAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes the length from root and length from seed for all points.
- L207 _prototype_ `void ComputeLengthFromTrunk(const FComputeLengthFromTrunkAttributes& InAttributes, TArrayView<float> OutLengthFromTunk);` (scope `PV::AttributesHelper`)
- L249 _prototype_ `void ComputeBudDevelopment(const FComputeBudDevelopmentAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes bud development for all points using the existing branch hierarchy and plant gradient.
- L291 _prototype_ `void ComputeBudDirections(const FComputeBudDirectionsAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes the bud directions for all points.
- L305 _prototype_ `void ComputeBudHormoneLevels(const FComputeBudHormoneLevelsAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes the bud hormone levels using the plant gradient for all points.
- L329 _prototype_ `void ComputePointGroundGradient(const FComputePointGroundGradientAttributes& InAttributes);` (scope `PV::AttributesHelper`)
- L353 _prototype_ `void ComputePointScaleGradient(const FComputePointScaleGradientAttributes& InAttributes);` (scope `PV::AttributesHelper`)
- L392 _prototype_ `void ComputePointPlantGradient(const FComputePointPlantGradientAttributes& InAttributes);` (scope `PV::AttributesHelper`)
- L427 _prototype_ `void ComputePointHullGradient(const FComputePointHullGradientAttributes& InAttributes);` (scope `PV::AttributesHelper`)
- L470 _prototype_ `void ComputePointMainTrunkGradient(const FComputePointMainTrunkGradientAttributes& InAttributes);` (scope `PV::AttributesHelper`)
- L509 _prototype_ `void ComputeBudStatus(const FComputeBudStatusAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes the bud status for all points.
- L565 _prototype_ `void ComputeBudLateralMeristem(const FComputeBudLateralMeristemAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes the bud lateral meristem for all points.
- L626 _prototype_ `void EstimateBudLightDetected(const FEstimateBudLightDetectedAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Estimate the bud light detected for all points.
- L662 _prototype_ `void ComputeBranchHierarchyNumbers(const FComputeBranchHierarchyNumberAttributes& InAttributes);` (scope `PV::AttributesHelper`) — Re-computes the BranchHierarchyNumber attribute given an already existing branch hierarchy.
- L746 _prototype_ `bool RecomputeAllGrowthDataAttributes(const FRecomputeGrowthDataAttributes& InAttributes);` (scope `PV::AttributesHelper`)
- L749 _prototype_ `int32 GetMaxBudAge(PV::FBudDevelopmentAttributeConstView BudDevelopment);` (scope `PV::AttributesHelper`) — Returns the highest BudAge value across all points, or -1 if the view is invalid or empty.

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVDiagnosticHelper.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PV`
- L8 _namespace_ `namespace Diagnostic` (scope `PV`)
- L16 _prototype_ `FString GetUpstreamNodeChain(const UPCGNode* InNode, const TCHAR* Separator = TEXT(" ->` (scope `PV::Diagnostic`) — Builds a single-line, human-readable summary of the nodes upstream of InNode in data-flow order (the most distant sources first, InNode last and marked ">>...<<"). Reroute and named-reroute plumbing nodes are traversed but omitted, and each node is rendered as "Title[SettingsClass]". Intended for diagnostic and crash logging. Returns an empty string when InNode is null.

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVDistributionHelper.h` (Private)


#### struct `PV::DistributionVectorUtils::FPointVectorData`  
`struct FPointVectorData`  
_L12-23_
- L14 _public member_ `FVector3f ApicalDirection = FVector3f::ZeroVector;` — TODO : Verify
- L15 _public member_ `FVector3f LightOptimal = FVector3f::ZeroVector;`
- L16 _public member_ `FVector3f LightSubOptimal = FVector3f::ZeroVector;`
- L17 _public member_ `FVector3f UpVector = FVector3f::ZeroVector;`
- L18 _public member_ `float PlantGradient = 0.f;`
- L19 _public member_ `float BranchGradient = 0.f;`
- L20 _public member_ `float PlantGradientNormalized = 0.f;`
- L21 _public member_ `float BranchGradientNormalized = 0.f;`
- L22 _public member_ `bool bIsTip = false;`

#### struct `PV::DistributionConditionUtils::FConditionAttributes`  
`struct FConditionAttributes`  
_L38-49_
- L40 _public member_ `TArray<float> UpAlignment;`
- L41 _public member_ `TArray<float> Light;`
- L42 _public member_ `TArray<float> Scale;`
- L43 _public member_ `TArray<float> Tip;`
- L44 _public member_ `TArray<float> Health;`
- L45 _public member_ `TArray<float> Height;`
- L46 _public member_ `TArray<float> Generation;`
- L48 _public prototype_ `float GetConditionValue(EPVDistributionCondition InCondition, const int Index) const;`

#### struct `PV::DistributionConditionUtils::FNormalizedPointCaches`  
`struct FNormalizedPointCaches`  
_L51-65_
- L53 _public member_ `TArray<float> PScales;`
- L54 _public member_ `TArray<float> Light;`
- L55 _public member_ `TArray<float> Health;`
- L56 _public member_ `TArray<float> Height;`
- L57 _public member_ `TArray<float> Generation;`
- L58 _public member_ `bool bHasPScales = false;`
- L59 _public member_ `bool bHasLight = false;`
- L60 _public member_ `bool bHasHealth = false;`
- L61 _public member_ `bool bHasHeight = false;`
- L62 _public member_ `bool bHasGeneration = false;`
- L64 _public prototype_ `void Reset(const int32 NumPoints);`

#### struct `PV::DistributionConditionUtils::FNormalizationInputs`  
`struct FNormalizationInputs`  
_L67-75_
- L69 _public member_ `bool bComputePScales = true;`
- L70 _public member_ `bool bComputeLight = true;`
- L71 _public member_ `bool bComputeHealth = true;`
- L72 _public member_ `bool bComputeHeight = true;`
- L73 _public member_ `bool bComputeGeneration = true;`
- L74 _public member_ `TArray<float> PScalesOverride;`

#### struct `PV::DistributionConditionUtils::ConditionPicker::FPointConditionSample`  
`struct FPointConditionSample`  
_L99-131_
- L101 _public member_ `float Light = 0.0f;`
- L102 _public member_ `float Scale = 0.0f;`
- L103 _public member_ `float UpAlignment = 0.0f;`
- L104 _public member_ `float Tip = 0.0f;`
- L105 _public member_ `float Health = 0.0f;`
- L106 _public member_ `float Height = 0.0f;`
- L107 _public member_ `float Generation = 0.0f;`
- L109 _public function_ `FORCEINLINE float Get(EPVDistributionCondition Condition) const`

#### struct `PV::DistributionHelper::FAttachmentPoint`  
`struct FAttachmentPoint`  
_L165-181_
- L167 _public member_ `int32 BranchIndex;`
- L168 _public member_ `int32 PointIndexA;`
- L169 _public member_ `int32 PointIndexB;`
- L170 _public member_ `float PointAlpha;`
- L171 _public member_ `FVector3f Position;`
- L172 _public member_ `FVector3f UpDirection;`
- L173 _public member_ `FVector3f NormalDirection;`
- L175 _public member_ `float Scale;`
- L176 _public member_ `float LengthFromRoot;`
- L177 _public member_ `bool bIsTipInstance;`
- L178 _public member_ `int32 TipPointIndex;`
- L180 _public member_ `DistributionConditionUtils::ConditionPicker::FPointConditionSample ConditionSample;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PV`
- L10 _namespace_ `namespace DistributionVectorUtils` (scope `PV`)
- L25 _prototype_ `FQuat4f FetchAimTarget(const EPVAimVectorType Type, const FVector3f& InputVector, const FPointVectorData& Point, const FVector3f VectorAxis, const float BlendAmount);` (scope `PV::DistributionVectorUtils`)
- L26 _prototype_ `FQuat4f FetchFaceTarget(const EPVFaceVectorType Type, const FVector3f& InputVector, const FPointVectorData& Point, const FVector3f VectorAxis, const float BlendAmount);` (scope `PV::DistributionVectorUtils`)
- L28 _prototype_ `float GetBlendPosition(const EPVAimVectorBlendAttribute BlendAttr, const FPointVectorData& Point, const FVector3f InputVector);` (scope `PV::DistributionVectorUtils`)
- L30 _prototype_ `void AdjustAimVectors(const FPVDistributionAimVectorSettings& InAimVectors, const FPointVectorData& InPointData, const FVector3f InputVector, FVector3f& OutUpVector, FVector3f& OutNormalVector);` (scope `PV::DistributionVectorUtils`)
- L31 _prototype_ `void AdjustFaceVectors(const FPVDistributionFaceVectorSettings& InFaceVectors, const FPointVectorData& InPointData, const FVector3f InputVector, FVector3f& OutNormalVector);` (scope `PV::DistributionVectorUtils`)
- L32 _prototype_ `void ApplyRollPitchYaw(const FPVDistributionRollPitchYawSettings& InSettings, const int32 InstanceIndex, FVector3f& InOutUpVector, FVector3f& InOutNormalVector);` (scope `PV::DistributionVectorUtils`)
- L33 _prototype_ `void ApplyVectorSettings(const FPVDistributionVectorParams& InVectorSettings, const FPointVectorData& InPointData, const int32 InstanceIndex, FVector3f& InOutUpVector, FVector3f& InOutNormalVector);` (scope `PV::DistributionVectorUtils`)
- L36 _namespace_ `namespace PV`
- L36 _namespace_ `namespace DistributionConditionUtils` (scope `PV`)
- L77 _function_ `FORCEINLINE float UpAlignmentNormalized(const FVector3f& ApicalDirection)` (scope `PV::DistributionConditionUtils`)
- L87 _function_ `FORCEINLINE float Tip(const bool bIsTip)` (scope `PV::DistributionConditionUtils`)
- L92 _prototype_ `void BuildNormalizedPointCaches( const FManagedArrayCollection& Collection, const FNormalizationInputs& Options, FNormalizedPointCaches& OutCaches);` (scope `PV::DistributionConditionUtils`)
- L97 _namespace_ `namespace ConditionPicker` (scope `PV::DistributionConditionUtils`)
- L133 _typedef_ `using FCandidateValueGetter = TFunctionRef<float(int32, EPVDistributionCondition)>;` (scope `PV::DistributionConditionUtils::ConditionPicker`)
- L135 _typedef_ `using FCandidateValidFn = TFunctionRef<bool(int32)>;` (scope `PV::DistributionConditionUtils::ConditionPicker`)
- L137 _prototype_ `int32 PickCandidateIndex( const int32 NumCandidates, const FPVDistributionConditionParams& DistributionConditions, const FPointConditionSample& PointSample, const FRandomStream& RandomStream, const FCandidateValueGetter& GetCandidateValue, const FCandidateValidFn& IsCandidateValid);` (scope `PV::DistributionConditionUtils::ConditionPicker`)
- L152 _prototype_ `bool GetActiveConditionSettings( const FPVDistributionConditionParams& DistributionConditions, const EPVDistributionCondition Condition, FPVDistributionConditionInfluence& OutSettings);` (scope `PV::DistributionConditionUtils::ConditionPicker`)
- L157 _prototype_ `float GetAttributeValue( const FPVDistributionConditions& FoliageAttributes, const EPVDistributionCondition InCondition);` (scope `PV::DistributionConditionUtils::ConditionPicker`)
- L163 _namespace_ `namespace PV`
- L163 _namespace_ `namespace DistributionHelper` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVDynamicMeshHelpers.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Geometry` (scope `UE`)
- L12 _typedef_ `template<class T> class TMeshAABBTree3;` (scope `UE::Geometry`)
- L15 _namespace_ `namespace PV`
- L15 _namespace_ `namespace DynamicMeshHelper` (scope `PV`)
- L17 _typedef_ `using FFindMeshElemsResult = TArray<int32, TInlineAllocator<4>>;` (scope `PV::DynamicMeshHelper`)
- L19 _prototype_ `FFindMeshElemsResult GetUniqueVertexIndices(const UE::Geometry::FDynamicMesh3& DynamicMesh, const TArray<int32>& TriangleIds);` (scope `PV::DynamicMeshHelper`)
- L21 _prototype_ `FFindMeshElemsResult GetVertexNeighbours(const UE::Geometry::FDynamicMesh3& DynamicMesh, int32 VertexID);` (scope `PV::DynamicMeshHelper`)
- L23 _prototype_ `FFindMeshElemsResult FindVerticesInRadius(const UE::Geometry::FDynamicMeshAABBTree3& DynamicMeshAABBTree, const FVector& Pos, float Radius);` (scope `PV::DynamicMeshHelper`)
- L25 _prototype_ `FFindMeshElemsResult FindTrianglesInRadius(const UE::Geometry::FDynamicMeshAABBTree3& DynamicMeshAABBTree, const FVector& Pos, float Radius);` (scope `PV::DynamicMeshHelper`)
- L27 _prototype_ `FFindMeshElemsResult FindTrianglesInRadius( const UE::Geometry::FDynamicMeshAABBTree3& DynamicMeshAABBTree, const FVector& Pos, float Radius, TFunctionRef<float(int32)> GetVertexScale);` (scope `PV::DynamicMeshHelper`)
- L33 _prototype_ `FFindMeshElemsResult FindTrianglesInRadius( const UE::Geometry::FDynamicMeshAABBTree3& DynamicMeshAABBTree, const FVector& Pos, float Radius, TFunctionRef<float(int32)> GetVertexScale, float GlobalMaxVertexScale);` (scope `PV::DynamicMeshHelper`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVFoliageJSONHelper.h` (Private)


#### struct `PV::FPVFoliageVariationData`  
`struct FPVFoliageVariationData`  
_L17-22_
- L19 _public member_ `FString VariationName;`
- L20 _public member_ `TArray<FPVFoliageInfo> FoliageInfos;`
- L21 _public member_ `FoliageConditionMap Conditions;`

#### struct `PV::PVFoliageJSONHelper`  
`struct PVFoliageJSONHelper`  
_L26-32_
- L28 _public prototype_ `static bool LoadJSON(const FString& InPath, TSharedPtr<FJsonObject>& OutData, FString& OutErrorMessage);`
- L29 _public prototype_ `static bool LoadFoliageData(const FString& InPath, const FString& InPackagePath, FoliageVariationsMap& OutFoliageVariationsMap, FString& OutErrorMessage);`
- L30 _public prototype_ `static bool LoadFoliageDataInCollection(FManagedArrayCollection& Collection, const FString& InPresetPath, const FPVFoliageVariationData& VariationData, FString& OutErrorMessage);`
- L31 _public prototype_ `static void SetFoliagePaths(FManagedArrayCollection& Collection, const FString& FilePath);`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PV`
- L15 _typedef_ `typedef TMap<EPVDistributionCondition, Facades::FFoliageConditonInfo> FoliageConditionMap;` (scope `PV`)
- L24 _typedef_ `typedef TMap<FString, FPVFoliageVariationData> FoliageVariationsMap;` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVHormoneDistributionHelper.h` (Private)


#### struct `PV::HormoneDistributionHelper::FHormoneSettings::FDistributionSettings`  
`struct FDistributionSettings`  
_L15-22_
- L17 _public member_ `const float EthyleneThreshold;`
- L18 _public member_ `const float InstanceSpacing;`
- L19 _public member_ `const FPVFloatRamp* InstanceSpacingRamp;`
- L20 _public member_ `const float InstanceSpacingRampEffect;`
- L21 _public member_ `const int32 MaxPerBranch;`

#### struct `PV::HormoneDistributionHelper::FHormoneSettings::FScaleSettings`  
`struct FScaleSettings`  
_L24-33_
- L26 _public member_ `const float BaseScale;`
- L27 _public member_ `const float BranchScaleImpact;`
- L28 _public member_ `const float MinScale;`
- L29 _public member_ `const float MaxScale;`
- L30 _public member_ `const float RandomScaleMin;`
- L31 _public member_ `const float RandomScaleMax;`
- L32 _public member_ `const FPVFloatRamp* ScaleRamp;`

#### struct `PV::HormoneDistributionHelper::FHormoneSettings::FAxilSettings`  
`struct FAxilSettings`  
_L35-42_
- L37 _public member_ `const bool OverrideAxilAngle;`
- L38 _public member_ `const float AxilAngle;`
- L39 _public member_ `const FPVFloatRamp* AxilAngleRamp;`
- L40 _public member_ `const float AxilAngleRampUpperValue;`
- L41 _public member_ `const float AxilAngleRampEffect;`

#### struct `PV::HormoneDistributionHelper::FHormoneSettings::FPhyllotaxySettings`  
`struct FPhyllotaxySettings`  
_L44-54_
- L46 _public member_ `const EPhyllotaxyType PhyllotaxyType;`
- L47 _public member_ `const EPhyllotaxyFormation PhyllotaxyFormation;`
- L48 _public member_ `const int32 MinimumNodeBuds;`
- L49 _public member_ `const int32 MaximumNodeBuds;`
- L50 _public member_ `const bool bSingleBudTip;`
- L51 _public member_ `const float PhyllotaxyAdditionalAngle;`
- L52 _public member_ `const bool ResetPhyllotaxy;`
- L53 _public member_ `const float PhyllotaxyOffset;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace HormoneDistributionHelper` (scope `PV`)
- L13 _namespace_ `namespace FHormoneSettings` (scope `PV::HormoneDistributionHelper`)
- L57 _prototype_ `TArray<float> RemapPlantGradientToEthyleneThreshold( PV::FPointPlantGradientAttributeConstView PointPlantGradient, PV::FBudHormoneLevelsAttributeConstView BudHormoneLevels, float EthyleneThreshold);` (scope `PV::HormoneDistributionHelper`)
- L62 _prototype_ `TArray<float> RemapPScalesToEthyleneThreshold( PV::FPointScaleAttributeConstView PointScaleAttribute, PV::FBudHormoneLevelsAttributeConstView BudHormoneLevels, float EthyleneThreshold);` (scope `PV::HormoneDistributionHelper`)
- L67 _prototype_ `TArray<TArray<float>> RemapBranchGradientToEthyleneThreshold( PV::FBranchPointsAttributeConstView BranchPoints, PV::FPointLengthFromRootAttributeConstView PointLengthFromRoot, PV::FBudHormoneLevelsAttributeConstView BudHormoneLevels, float EthyleneThreshold);` (scope `PV::HormoneDistributionHelper`)
- L73 _prototype_ `void ComputeHormoneBasedAttachmentPoints( FManagedArrayCollection& OutCollection, const DistributionConditionUtils::FNormalizedPointCaches& NormalizedPointCaches, const FHormoneSettings::FDistributionSettings& DistributionSettings, const FHormoneSettings::FScaleSettings& ScaleSettings, const FHormoneSettings::FAxilSettings& AxilSettings, const FHormoneSettings::FPhyllotaxySettings& PhyllotaxySettings, const FPVDistributionVectorParams& VectorSettings, FRandomStream& RandomStream, float TrunkOffset, TArray<DistributionHelper::FAttachmentPoint>& OutAttachmentPoints);` (scope `PV::HormoneDistributionHelper`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVImportHelpers.h` (Private)


#### struct `FPVBranchDescription`  
`struct FPVBranchDescription`  
_L16-22_
- L18 _public member_ `int32 ParentBranchIndex = INDEX_NONE;`
- L19 _public member_ `int32 BranchIndex = INDEX_NONE;`
- L20 _public member_ `TArray<int32> ChildBranchIndices;`
- L21 _public member_ `TArray<int32> PointIndices;`

#### struct `FPVBranchHierarchyDescription`  
`struct FPVBranchHierarchyDescription`  
_L24-48_
- L26 _public member_ `int32 RootBranchIndex = INDEX_NONE;`
- L27 _public member_ `TArray<FPVBranchDescription> Branches;`
- L28 _public member_ `TArray<FVector3f> Points;`
- L29 _public member_ `TArray<float> PointsRadii;`
- L31 _public function_ `int32 GetNumBranches() const`
- L32 _public function_ `int32 GetNumPoints() const`
- L47 _public prototype_ `EValidateHierarchyResult ValidateHierarchy() const;`

#### enum `FPVBranchHierarchyDescription::EValidateHierarchyResult`  
`enum class EValidateHierarchyResult`  
_L34-46_
- L36 _public enumerator_ `InvalidRootBranchIndex`
- L37 _public enumerator_ `InvalidRootBranchParentIndex`
- L38 _public enumerator_ `InvalidParentBranchIndex`
- L39 _public enumerator_ `InvalidBranchIndex`
- L40 _public enumerator_ `InvalidChildBranchIndex`
- L41 _public enumerator_ `InvalidPointIndex`
- L42 _public enumerator_ `BranchIndexMismatch`
- L43 _public enumerator_ `DisjointedHierarchy`
- L44 _public enumerator_ `CircularHierarchy`
- L45 _public enumerator_ `Success`

#### struct `PV::ImportHelper::FLabel`  
`struct FLabel`  
_L85-90_
- L87 _public member_ `FVector3f Position;`
- L88 _public member_ `FString Text;`
- L89 _public member_ `float Scale;`

#### struct `PV::ImportHelper::FMeshBranchHierarchy`  
`struct FMeshBranchHierarchy`  
_L93-102_
- L101 _public member_ `TArray<FBranch> Branches;`

#### struct `PV::ImportHelper::FMeshBranchHierarchy::FBranch`  
`struct FBranch`  
_L95-99_
- L97 _public member_ `TArray<int32> BranchPoints;`
- L98 _public member_ `int32 ParentBranch = INDEX_NONE;`

#### enum `PV::ImportHelper::EAppendGrowthDataResult`  
`enum class EAppendGrowthDataResult`  
_L123-128_
- L125 _public enumerator_ `Success`
- L126 _public enumerator_ `InvalidTarget`
- L127 _public enumerator_ `InvalidSource`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Geometry` (scope `UE`)
- L50 _namespace_ `namespace PV`
- L50 _namespace_ `namespace ImportHelper` (scope `PV`)
- L52 _typedef_ `using FBooleanVertexAttribute = TDynamicMeshVertexAttributeExt<bool>;` (scope `PV::ImportHelper`)
- L53 _typedef_ `using FIntVertexAttribute = TDynamicMeshVertexAttributeExt<int32>;` (scope `PV::ImportHelper`)
- L54 _typedef_ `using FFloatVertexAttribute = TDynamicMeshVertexAttributeExt<float>;` (scope `PV::ImportHelper`)
- L56 _externvar_ `extern const PV::TDynamicMeshVertexAttributeDefinition<float> VertexScaleAttributeDefinition;` (scope `PV::ImportHelper`)
- L57 _externvar_ `extern const PV::TDynamicMeshVertexAttributeDefinition<bool> EndPointAttributeDefinition;` (scope `PV::ImportHelper`)
- L58 _externvar_ `extern const PV::TDynamicMeshVertexAttributeDefinition<bool> RootPointAttributeDefinition;` (scope `PV::ImportHelper`)
- L59 _externvar_ `extern const PV::TDynamicMeshVertexAttributeDefinition<float> LengthFromRootAttributeDefinition;` (scope `PV::ImportHelper`)
- L60 _externvar_ `extern const PV::TDynamicMeshVertexAttributeDefinition<int32> NextBranchPointAttributeDefinition;` (scope `PV::ImportHelper`)
- L62 _prototype_ `void AddDynamicMeshToCollection( const UE::Geometry::FDynamicMesh3& DynamicMesh, FManagedArrayCollection& InOutCollection, const FTransform& Offset = FTransform::Identity );` (scope `PV::ImportHelper`)
- L68 _prototype_ `void AddDynamicMeshVerticesToCollection( const UE::Geometry::FDynamicMesh3& DynamicMesh, const FBooleanVertexAttribute& Filter, const FTransform& VertexOffset, FManagedArrayCollection& InOutCollection, const FName TargetGroupName, const FName TargetAttributeName );` (scope `PV::ImportHelper`)
- L77 _prototype_ `void AddBranchHierarchiesToCollection( const TArray<FPVBranchHierarchyDescription>& BranchHierarchyDescriptions, FManagedArrayCollection& InOutCollection, const FVector& Offset = FVector::ZeroVector, const FName TargetAttributeName = PVImportNames::BranchHierarchyAttribute, const FName TargetGroupName = PVImportNames::BranchHierarchyGroup );` (scope `PV::ImportHelper`)
- L91 _prototype_ `void AddLabelsToCollection(const TArray<FLabel>& Labels, FManagedArrayCollection& InOutCollection);` (scope `PV::ImportHelper`)
- L104 _prototype_ `void ComputeDynamicMeshBranchHierarchies( const UE::Geometry::FDynamicMesh3& DynamicMesh, const FBooleanVertexAttribute& RootPointsAttribute, const FBooleanVertexAttribute& EndPointsAttribute, const FFloatVertexAttribute& VertexScaleAttribute, FFloatVertexAttribute& LengthFromRootAttribute, FIntVertexAttribute& NextBranchPointAttribute, const TFunction<bool(int32)>& VertexFilterPredicate, TArray<FMeshBranchHierarchy>& OutDynamicMeshBranchHierarchies );` (scope `PV::ImportHelper`)
- L115 _prototype_ `void ConvertDynamicMeshBranchHierarchiesToBranchDescription( const UE::Geometry::FDynamicMesh3& DynamicMesh, const FFloatVertexAttribute& VertexScaleAttribute, const FBooleanVertexAttribute& EndPointAttribute, const TArray<FMeshBranchHierarchy>& InMeshBranchHierarchies, TArray<FPVBranchHierarchyDescription>& OutBranchHierarchyDescriptions );` (scope `PV::ImportHelper`)
- L129 _prototype_ `EAppendGrowthDataResult AppendGrowthData(FManagedArrayCollection& Target, const FManagedArrayCollection& Source);` (scope `PV::ImportHelper`)
- L132 _prototype_ `void CreateEmptyGrowthData(FManagedArrayCollection& OutCollection, int32 NumPoints, int32 NumBranches);` (scope `PV::ImportHelper`) — Creates a collection containing all attributes (of the supplied size) required for creating PV growth data.
- L134 _prototype_ `void FillAttributesFromBranchHierarchy( FManagedArrayCollection& OutCollection, TArrayView<const FPVBranchHierarchyDescription> InBranchHierarchies );` (scope `PV::ImportHelper`)
- L141 _prototype_ `void FillAttributesFromBranchHierarchy( PV::FPointPositionAttributeView PointPositionAttribute, PV::FPointScaleAttributeView PointScaleAttribute, PV::FBranchPointsAttributeView BranchPointsAttribute, PV::FBranchParentsAttributeView BranchParentsAttribute, PV::FBranchChildrenAttributeView BranchChildrenAttribute, PV::FBranchParentNumberAttributeView BranchParentNumberAttribute, PV::FBranchNumberAttributeView BranchNumberAttribute, PV::FBranchHierarchyNumberAttributeView BranchHierarchyNumberAttribute, PV::FBranchPlantNumberAttributeView BranchPlantNumberAttribute, TArrayView<const FPVBranchHierarchyDescription> InBranchHierarchies );` (scope `PV::ImportHelper`) — Copies the branch hierarchies from the input BranchHierarchies to the attributes. Assumes the attributes are large enough to receive the hierarchies.
- L154 _prototype_ `void ComputeLengthFromRoot( const UE::Geometry::FDynamicMesh3& DynamicMesh, const FBooleanVertexAttribute& RootPointsAttribute, const FBooleanVertexAttribute& EndPointsAttribute, FFloatVertexAttribute& LengthFromRootAttribute, const TFunction<bool(int32)>& VertexFilterPredicate );` (scope `PV::ImportHelper`)
- L162 _prototype_ `void TraceBranches( const UE::Geometry::FDynamicMesh3& DynamicMesh, const FFloatVertexAttribute& LengthFromRootAttribute, const FBooleanVertexAttribute& RootPointAttribute, const FBooleanVertexAttribute& EndPointAttribute, FIntVertexAttribute& NextBranchPointAttribute, const TFunction<bool(int32)>& VertexFilterPredicate );` (scope `PV::ImportHelper`)
- L171 _prototype_ `void ExtractBranchHierarchies( const UE::Geometry::FDynamicMesh3& DynamicMesh, const FBooleanVertexAttribute& RootPointAttribute, const FBooleanVertexAttribute& EndPointAttribute, const FIntVertexAttribute& NextBranchPointAttribute, const FFloatVertexAttribute& VertexScaleAttribute, const FFloatVertexAttribute& LengthFromRootAttribute, TArray<FMeshBranchHierarchy>& OutMeshBranchHierarchies );` (scope `PV::ImportHelper`)
- L181 _prototype_ `bool GenerateGrowthDataFromBranchHierarchies(FManagedArrayCollection& OutCollection, TArrayView<const FPVBranchHierarchyDescription> InBranchHierarchies);` (scope `PV::ImportHelper`)
- L183 _prototype_ `bool GenerateGrowthDataFromBranchHierarchy(FManagedArrayCollection& OutCollection, const FPVBranchHierarchyDescription& InBranchHierarchy);` (scope `PV::ImportHelper`)
- L185 _prototype_ `void DistToBranch(const FVector3f& Point, const TArray<FVector3f>& Points, const TArray<int32>& BranchPointIndices, FVector3f& OutClosestPoint, float& OutDistSquared, int32& OutPointIndex);` (scope `PV::ImportHelper`)
- L187 _prototype_ `float DistToBranch(const FVector3f& Point, const TArray<FVector3f>& Points, const TArray<int32>& BranchPointIndices);` (scope `PV::ImportHelper`)
- L190 _prototype_ `TArray<int32> EstimateBranchHierarchy(const TArray<FVector3f>& Points, const TArray<TArray<int32>>& Branches, int32 RootBranchIndex);` (scope `PV::ImportHelper`) — Returns array of parent branch index for each supplied branch. Root branch will have parent index INDEX_NONE.
- L192 _prototype_ `int32 FindRootBranch(const TArray<FVector3f>& InPoints, const TArray<TArray<int32>>& BranchIndices);` (scope `PV::ImportHelper`)
- L194 _prototype_ `FPVBranchHierarchyDescription CreateBranchHierarchyFromPoints(const TArray<FVector3f>& InPoints, const TArray<float>& InPointsRadii, const TArray<TArray<int32>>& InBranchPointIndices);` (scope `PV::ImportHelper`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVJSONHelper.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace JSON` (scope `PV`)
- L13 _prototype_ `void FillAttributes(FManagedArrayCollection& Collection, const FName Group, const TSharedPtr<FJsonObject>& AttributesObject);` (scope `PV::JSON`)
- L15 _prototype_ `void FillDetailsAttributes(FManagedArrayCollection& Collection, const FName Group, const TSharedPtr<FJsonObject>& AttributesObject);` (scope `PV::JSON`)
- L17 _prototype_ `void FillPlantProfilesData(FManagedArrayCollection& Collection, const FName Group, const TSharedPtr<FJsonObject>& AttributesObject);` (scope `PV::JSON`)
- L19 _prototype_ `void FillFoliageData(FManagedArrayCollection& Collection, const TSharedPtr<FJsonObject>& PrimitiveAttributesObject, const FString& InPath);` (scope `PV::JSON`)
- L21 _prototype_ `void SetFoliagePaths(FManagedArrayCollection& Collection,const FString& FilePath);` (scope `PV::JSON`)
- L23 _prototype_ `bool HasJsonFieldPath(const TSharedPtr<FJsonObject>& JsonObject, const FString& Path);` (scope `PV::JSON`)
- L25 _prototype_ `bool LoadMegaPlantsJsonToCollection(FManagedArrayCollection& Collection, const FString& FilePath, FString& OutErrorMessage);` (scope `PV::JSON`)
- L27 _prototype_ `bool LoadGrowthDataJsonToCollection(FManagedArrayCollection& Collection, const FString& FilePath, FString& OutErrorMessage);` (scope `PV::JSON`)
- L29 _prototype_ `TSharedPtr<FJsonObject> LoadMetaFileIntoJsonObject(const FString& FilePath, FString& OutErrorMessage);` (scope `PV::JSON`)
- L31 _prototype_ `bool LoadMetaJsonToCollection(FManagedArrayCollection& Collection, TSharedPtr<FJsonObject> LoadedData);` (scope `PV::JSON`)
- L33 _prototype_ `bool LoadProfileData(FString FilePath, TArray<FPVPlantProfile>& OutProfileData, FString& OutErrorMessage);` (scope `PV::JSON`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVParametricDistributionHelper.h` (Private)


#### enum `PV::ParametricDistributionHelper::FParametricSettings::EDistributionBasis`  
`enum class EDistributionBasis : uint8`  
_L17-21_
- L19 _public enumerator_ `Plant`
- L20 _public enumerator_ `Branch`

#### struct `PV::ParametricDistributionHelper::FParametricSettings::FSpacingSettings`  
`struct FSpacingSettings`  
_L23-34_
- L25 _public member_ `const int32 BranchDensity;`
- L26 _public member_ `const float RelativeStart;`
- L27 _public member_ `const float RelativeEnd;`
- L28 _public member_ `const bool LimitStartGeneration;`
- L29 _public member_ `const int32 StartGeneration;`
- L30 _public member_ `const bool LimitEndGeneration;`
- L31 _public member_ `const int32 EndGeneration;`
- L32 _public member_ `const EDistributionBasis SpacingBasis;`
- L33 _public member_ `const FPVFloatRamp* SpacingRamp;`

#### struct `PV::ParametricDistributionHelper::FParametricSettings::FPhyllotaxySettings`  
`struct FPhyllotaxySettings`  
_L36-46_
- L38 _public member_ `const EPhyllotaxyType PhyllotaxyType;`
- L39 _public member_ `const EPhyllotaxyFormation PhyllotaxyFormation;`
- L40 _public member_ `const int32 MinimumNodeBuds;`
- L41 _public member_ `const int32 MaximumNodeBuds;`
- L42 _public member_ `const bool bSingleBudTip = true;`
- L43 _public member_ `const float PhyllotaxyAdditionalAngle;`
- L44 _public member_ `const bool ResetPhyllotaxy;`
- L45 _public member_ `const float PhyllotaxyOffset;`

#### struct `PV::ParametricDistributionHelper::FParametricSettings::FAngleSettings`  
`struct FAngleSettings`  
_L48-56_
- L50 _public member_ `const float Rotation;`
- L51 _public member_ `const float AxilAngle;`
- L52 _public member_ `const float RandomizeAxilAngleMinimum;`
- L53 _public member_ `const float RandomizeAxilAngleMaximum;`
- L54 _public member_ `const EDistributionBasis AxilAngleRampBasis;`
- L55 _public member_ `const FPVFloatRamp* AxilAngleRamp;`

#### struct `PV::ParametricDistributionHelper::FParametricSettings::FScaleSettings`  
`struct FScaleSettings`  
_L58-66_
- L60 _public member_ `const EDistributionBasis ScaleRampBasis;`
- L61 _public member_ `const float BaseScale;`
- L62 _public member_ `const float RandomizeScaleMinimum;`
- L63 _public member_ `const float RandomizeScaleMaximum;`
- L64 _public member_ `const FPVFloatRamp* ScaleRamp;`
- L65 _public member_ `const float BranchScaleImpact;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PV`
- L13 _namespace_ `namespace ParametricDistributionHelper` (scope `PV`)
- L15 _namespace_ `namespace FParametricSettings` (scope `PV::ParametricDistributionHelper`)
- L69 _prototype_ `float IndexedRandom01(const int32 Seed);` (scope `PV::ParametricDistributionHelper`)
- L71 _prototype_ `float IndexedRandomRange(const int32 Seed, const float MinValue, const float MaxValue);` (scope `PV::ParametricDistributionHelper`)
- L73 _prototype_ `int32 IndexedRandomIntInclusive(const int32 Seed, const int32 MinValue, const int32 MaxValue);` (scope `PV::ParametricDistributionHelper`)
- L75 _prototype_ `static float ComputeAttachmentScale( const int32 BudIndex, const int32 RandomSeed, const float PlantGradient, const float BranchGradient, const float LengthRatio, const FParametricSettings::FScaleSettings& ScaleSettings, float RelativeStart, float RelativeEnd);` (scope `PV::ParametricDistributionHelper`)
- L85 _prototype_ `void ComputeAttachmentPoints( FManagedArrayCollection& OutCollection, const FNormalizedPointCaches& NormalizedPointCaches, const FParametricSettings::FSpacingSettings& SpacingSettings, const FParametricSettings::FPhyllotaxySettings& PhyllotaxySettings, const FParametricSettings::FAngleSettings& AngleSettings, const FParametricSettings::FScaleSettings& ScaleSettings, const FPVDistributionVectorParams& VectorSettings, const int32 RandomSeed, float TrunkOffset, TArray<DistributionHelper::FAttachmentPoint>& OutAttachmentPoints);` (scope `PV::ParametricDistributionHelper`)
- L97 _prototype_ `TArray<float> RemapPScalesToGradientRange( FBranchPointsAttributeConstView BranchPointsAttribute, FPointLengthFromRootAttributeConstView PointLengthFromRootAttribute, FPointScaleAttributeConstView PointScaleAttribute, float RelativeStart, float RelativeEnd);` (scope `PV::ParametricDistributionHelper`)
- L104 _prototype_ `TMap<int32, float> ComputeBranchLengths( FPointLengthFromRootAttributeConstView PointLengthFromRootAttribute, FBranchPointsAttributeConstView BranchPointsAttribute);` (scope `PV::ParametricDistributionHelper`)
- L108 _prototype_ `FVector3f SampleVectorByFloat( const float SampleValue, const TArray<int32>& BranchPoints, FPointPlantGradientAttributeConstView PointPlantGradientAttribute, FPointPositionAttributeConstView PointPositionAttribute);` (scope `PV::ParametricDistributionHelper`)
- L114 _prototype_ `float SampleFloatByFloat( const float SampleValue, const TArray<int32>& BranchPoints, FPointPlantGradientAttributeConstView PointPlantGradientAttribute, FPointLengthFromRootAttributeConstView PointLengthFromRootAttribute);` (scope `PV::ParametricDistributionHelper`)
- L120 _prototype_ `bool FindPointByNormalizedLengthFromRoot( float SampleValue, const TArray<int32>& BranchPoints, FPointLengthFromRootAttributeConstView PointLengthFromRootAttribute, const float LFRofRoot, const float LFRofTip, int32& PreviousBranchPointIndex, int32& NextBranchPointIndex, float& OutAlpha);` (scope `PV::ParametricDistributionHelper`)
- L130 _prototype_ `void ComputeRotationAnglesForAttachment( const FVector3f& ApicalDirection, const FVector3f& BudDirectionUp, const FVector3f& BaseAxillaryDirection, const float PlantGradient, const float CurveU, const int32 Iteration, const int32 SubIteration, const int32 NumSubIterations, const int32 BudIndex, const int32 RandomSeed, const FParametricSettings::FAngleSettings& AngleSettings, const FParametricSettings::FSpacingSettings& SpacingSettings, FVector3f& OutUpDirection, FVector3f& OutNormalDirection);` (scope `PV::ParametricDistributionHelper`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVPhyllotaxyHelper.h` (Private)


#### enum `EPhyllotaxyType`  
`enum class EPhyllotaxyType : uint8`  
_L8-15_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `Alternate UMETA(DisplayName = "Alternate")`
- L11 _public enumerator_ `Opposite UMETA(DisplayName = "Opposite")`
- L12 _public enumerator_ `Decussate UMETA(DisplayName = "Decussate")`
- L13 _public enumerator_ `Whorled UMETA(DisplayName = "Whorled")`
- L14 _public enumerator_ `Spiral UMETA(DisplayName = "Spiral")`

#### enum `EPhyllotaxyFormation`  
`enum class EPhyllotaxyFormation : uint8`  
_L18-25_
- reflection: `UENUM(BlueprintType)`
- L20 _public enumerator_ `Distichous UMETA(DisplayName = "Distichous")`
- L21 _public enumerator_ `Tristichous UMETA(DisplayName = "Tristichous")`
- L22 _public enumerator_ `Pentastichous UMETA(DisplayName = "Pentastichous")`
- L23 _public enumerator_ `Octastichous UMETA(DisplayName = "Octastichous")`
- L24 _public enumerator_ `Parastichous UMETA(DisplayName = "Parastichous")`

#### struct `PV::PhyllotaxySettingsHelper::FResolvedPhyllotaxy`  
`struct FResolvedPhyllotaxy`  
_L29-36_
- L31 _public member_ `float FormationDegrees = 180.0f;`
- L32 _public member_ `int32 MinBuds = 1;`
- L33 _public member_ `int32 MaxBuds = 1;`
- L34 _public member_ `bool bResetPhyllotaxy = false;`
- L35 _public member_ `float OffsetDegrees = 0.0f;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace PV`
- L27 _namespace_ `namespace PhyllotaxySettingsHelper` (scope `PV`)
- L39 _function_ `template <typename TPhyllotaxySettings> FResolvedPhyllotaxy ResolvePhyllotaxy(const TPhyllotaxySettings& Settings)` (scope `PV::PhyllotaxySettingsHelper`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVPlantTraversalHelper.h` (Private)


#### struct `PV::PlantTraversalHelper::FBranchNumberToIndexTable`  
`struct FBranchNumberToIndexTable`  
_L11-99_
- desc: Lookup table that maps branch numbers to their array indices. Internally uses an offset array for dense ranges or a TMap for sparse ranges, chosen at construction time based on the ratio of element count to value range.
- L19 _public typedef_ `using FMapTable = TMap<int32, int32>;`
- L21 _public member_ `TVariant<FEmptyVariantState, FArrayTable, FMapTable> Table;`
- L23 _public prototype_ `FBranchNumberToIndexTable() = default;`
- L24 _public function_ `FBranchNumberToIndexTable(PV::FBranchNumberAttributeView BranchNumberAttribute)`
- L25 _public function_ `FBranchNumberToIndexTable(PV::FBranchNumberAttributeConstView BranchNumberAttribute)`
- L27 _public function_ `void Init(PV::FBranchNumberAttributeConstView BranchNumberAttribute)`
- L74 _public function_ `int32 Find(int32 BranchNumber) const`
- L95 _public function_ `bool IsValid() const`

#### struct `PV::PlantTraversalHelper::FBranchNumberToIndexTable::FArrayTable`  
`struct FArrayTable`  
_L13-17_
- L15 _public member_ `int32 Offset;`
- L16 _public member_ `TArray<int32> Table;`

#### enum `PV::PlantTraversalHelper::EForEachResult`  
`enum class EForEachResult`  
_L201-205_
- L203 _public enumerator_ `Break = 0`
- L204 _public enumerator_ `Continue = 1`

#### struct `PV::PlantTraversalHelper::FRecursiveWalkBranchPointsParams`  
`struct FRecursiveWalkBranchPointsParams`  
_L377-385_
- L379 _public member_ `int32 BranchIndex;`
- L380 _public member_ `int32 BranchPointIndex;` — The index of the point in the branch points attribute
- L381 _public member_ `int32 PointIndex;` — The global point index of this point
- L382 _public member_ `int32 ParentPointIndex;` — The global point index of this points parent point (INDEX_NONE for the first point on the trunk)
- L383 _public member_ `const TArray<int32>& ChildBranchIndices;`
- L384 _public member_ `const TArray<int32>& ChildPointIndices;`

#### struct `PV::PlantTraversalHelper::RecursiveWalkBranchPoints::__anon1fe59b920402::FChildPoint`  
`struct FChildPoint`  
_L432-436_
- L434 _public member_ `int32 BranchIndex;`
- L435 _public member_ `int32 BranchPointIndex;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PV`
- L6 _namespace_ `namespace PlantTraversalHelper` (scope `PV`)
- L101 _function_ `inline int32 GetBranchParentIndex( FBranchParentNumberAttributeConstView BranchParentNumberAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, int32 BranchIndex )` (scope `PV::PlantTraversalHelper`)
- L122 _function_ `inline int32 GetBranchParentIndex( FBranchParentNumberAttributeConstView BranchParentNumberAttribute, FBranchNumberAttributeConstView BranchNumberAttribute, int32 BranchIndex )` (scope `PV::PlantTraversalHelper`) — Slow variant of GetBranchParentIndex. Prefer GetBranchParentIndex with a FBranchNumberToIndexTable when a FBranchNumberToIndexTable is already available. The difference is in how the parent branch index is resolved: GetBranchParentIndex        — takes a pre-built FBranchNumberToIndexTable and resolves the parent in O(1). GetBranchParentIndex (Slow) — takes the raw BranchNumberAttribute and resolves the parent via a linear Find(), making repeated calls O(N) per lookup. Use this variant only when constructing the lookup table upfront is not practical (e.g. one-off lookups in contexts where the table is not already available and building it would be wasteful).
- L133 _function_ `inline TArray<int32> GetPlantBranchIndices( PV::FBranchPlantNumberAttributeConstView BranchPlantNumberAttribute, int32 PlantNumber )` (scope `PV::PlantTraversalHelper`)
- L151 _function_ `inline bool IsTrunk(FBranchParentNumberAttributeConstView BranchParentNumberAttribute, int32 BranchIndex)` (scope `PV::PlantTraversalHelper`)
- L156 _function_ `inline TArray<int32> GetTrunkIndices(FBranchParentNumberAttributeConstView BranchParentNumberAttribute)` (scope `PV::PlantTraversalHelper`)
- L169 _function_ `inline FVector3f GetPlantRootPoint( FBranchPlantNumberAttributeConstView BranchPlantNumberAttribute, FBranchParentNumberAttributeConstView BranchParentNumberAttribute, FBranchPointsAttributeConstView BranchPointsAttribute, FPointPositionAttributeConstView PointPositionAttribute, int32 PlantNumber )` (scope `PV::PlantTraversalHelper`)
- L191 _function_ `inline TArray<int32> GetUniquePlantNumbers(PV::FBranchPlantNumberAttributeConstView BranchPlantNumberAttribute)` (scope `PV::PlantTraversalHelper`)
- L209 _function_ `template <typename StateType> void RecursiveWalkBranches( FBranchParentNumberAttributeConstView BranchParentNumberAttribute, FBranchChildrenAttributeConstView BranchChildrenAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, const StateType& RootBranchState, const TFunction<EForEachResult(int32, StateType&)>& Body )` (scope `PV::PlantTraversalHelper`) — Walks the branches in hierarchical order (e.g. start with the trunk and recursivly visit the child branches)
- L223 _function_ `` (scope `PV::PlantTraversalHelper::RecursiveWalkBranches`)
- L262 _function_ `inline void RecursiveWalkBranches( FBranchParentNumberAttributeConstView BranchParentNumberAttribute, FBranchChildrenAttributeConstView BranchChildrenAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, const TFunction<EForEachResult(int32 BranchIndex)>& Body )` (scope `PV::PlantTraversalHelper`)
- L286 _function_ `inline void RecursiveWalkBranches_Reversed( FBranchParentNumberAttributeConstView BranchParentNumberAttribute, FBranchChildrenAttributeConstView BranchChildrenAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, const TFunction<EForEachResult(int32 BranchIndex)>& Body )` (scope `PV::PlantTraversalHelper`) — Walks the branches in reversed hierarchical order (e.g. first visit all leaf nodes, then their parents, and so on, visiting the tunk last)
- L301 _function_ `` (scope `PV::PlantTraversalHelper::RecursiveWalkBranches_Reversed`)
- L316 _function_ `inline TArray<int32> GetBranchPointChildBranchIndices( PV::FBranchChildrenAttributeConstView BranchChildrenAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, PV::FBranchPointsAttributeConstView BranchPointsAttribute, int32 BranchIndex, int32 BranchPointIndex )` (scope `PV::PlantTraversalHelper`)
- L388 _function_ `template <typename StateType, bool bWalkAxillaryFirst = false> inline EForEachResult RecursiveWalkBranchPoints( PV::FBranchChildrenAttributeConstView BranchChildrenAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, PV::FBranchPointsAttributeConstView BranchPointsAttribute, int32 BranchIndex, const StateType& RootPointState, const TFunction<EForEachResult(const FRecursiveWalkBranchPointsParams& Params, StateType& PointState)>& Body )` (scope `PV::PlantTraversalHelper`)
- L404 _function_ `` (scope `PV::PlantTraversalHelper::RecursiveWalkBranchPoints`)
- L480 _function_ `template<bool bWalkAxillaryFirst = false> inline EForEachResult RecursiveWalkBranchPoints( PV::FBranchChildrenAttributeConstView BranchChildrenAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, PV::FBranchPointsAttributeConstView BranchPointsAttribute, int32 BranchIndex, const TFunction<EForEachResult(const FRecursiveWalkBranchPointsParams& Params)>& Body )` (scope `PV::PlantTraversalHelper`)
- L504 _function_ `template <typename StateType, bool bWalkAxillaryBranchesFirst = false> void RecursiveWalkPlantPoints( PV::FBranchChildrenAttributeConstView BranchChildrenAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, PV::FBranchPointsAttributeConstView BranchPointsAttribute, const StateType& RootPointState, const TFunction<EForEachResult(const FRecursiveWalkBranchPointsParams& Params, StateType& PointState)>& Body )` (scope `PV::PlantTraversalHelper`)
- L532 _function_ `template <bool bWalkAxillaryBranchesFirst = false> inline void RecursiveWalkPlantPoints( PV::FBranchChildrenAttributeConstView BranchChildrenAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, const FBranchNumberToIndexTable& BranchNumberToIndex, PV::FBranchPointsAttributeConstView BranchPointsAttribute, const TFunction<EForEachResult(const FRecursiveWalkBranchPointsParams& Params)>& Body )` (scope `PV::PlantTraversalHelper`)
- L547 _function_ `` (scope `PV::PlantTraversalHelper::RecursiveWalkPlantPoints`)
- L553 _function_ `inline void ForEachUniquePointOnBranches( PV::FBranchPointsAttributeConstView BranchPointsAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, const TFunction<EForEachResult(int32 BranchIndex, int32 BranchPointIndex, int32 PointIndex)>& Body )` (scope `PV::PlantTraversalHelper`)
- L580 _function_ `inline void ForEachPlant( PV::FBranchPlantNumberAttributeConstView BranchPlantNumberAttribute, const TFunction<EForEachResult(int32 PlantNumber)>& Body )` (scope `PV::PlantTraversalHelper`)
- L594 _function_ `inline void ForEachPlant( const FManagedArrayCollection& Collection, const TFunction<EForEachResult(int32 PlantNumber)>& Body )` (scope `PV::PlantTraversalHelper`)
- L605 _function_ `inline void ForEachPlantPoint( PV::FBranchPlantNumberAttributeConstView BranchPlantNumberAttribute, PV::FBranchPointsAttributeConstView BranchPointsAttribute, PV::FBranchParentNumberAttributeConstView BranchParentNumberAttribute, int32 PlantNumber, const TFunction<EForEachResult(int32 BranchIndex, int32 PointIndex)>& Body )` (scope `PV::PlantTraversalHelper`)
- L632 _function_ `inline void ForEachPlantPoint( const FManagedArrayCollection& Collection, int32 PlantNumber, const TFunction<EForEachResult(int32 BranchIndex, int32 PointIndex)>& Body )` (scope `PV::PlantTraversalHelper`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Helpers/PVTransformHelper.h` (Private)


#### struct `PV::Transform::FRotateBranchPointsAttributeCollection`  
`struct FRotateBranchPointsAttributeCollection`  
_L12-41_
- desc: Attributes required to traverse a tree and rotate the points around its parent point.
- L14 _public member_ `PV::FPointPositionAttributeView PointPosition;`
- L15 _public member_ `PV::FBudDirectionAttributeView BudDirection;`
- L16 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L17 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L18 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L19 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L21 _public prototype_ `FRotateBranchPointsAttributeCollection() = default;`
- L22 _public function_ `FRotateBranchPointsAttributeCollection(FManagedArrayCollection& Collection) : PointPosition(PV::FPointPositionAttribute::FindAttribute(Collection)) , BudDirection(PV::FBudDirectionAttribute::FindAttribute(Collection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(Collection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(Collection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(Collection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(Collection))`
- L32 _public function_ `bool IsValid() const`

#### struct `PV::Transform::FTransformPointAttributeCollection`  
`struct FTransformPointAttributeCollection`  
_L43-68_
- L45 _public member_ `PV::FPointPositionAttributeView PointPosition;`
- L46 _public member_ `PV::FBudDirectionAttributeView BudDirection;`
- L48 _public prototype_ `FTransformPointAttributeCollection() = default;`
- L49 _public function_ `FTransformPointAttributeCollection(FManagedArrayCollection& Collection) : PointPosition(PV::FPointPositionAttribute::FindAttribute(Collection)) , BudDirection(PV::FBudDirectionAttribute::FindAttribute(Collection))`
- L55 _public function_ `FTransformPointAttributeCollection(const FRotateBranchPointsAttributeCollection& Other) : PointPosition(Other.PointPosition) , BudDirection(Other.BudDirection)`
- L61 _public function_ `FTransformPointAttributeCollection( PV::FPointPositionAttributeView InPointPositionAttribute, PV::FBudDirectionAttributeView InBudDirectionAttribute) : PointPosition(InPointPositionAttribute) , BudDirection(InBudDirectionAttribute)`

#### struct `PV::Transform::FRotateBranchPointResult`  
`struct FRotateBranchPointResult`  
_L80-84_
- L82 _public member_ `FQuat4f Rotation;`
- L83 _public member_ `bool bAbsoluteRotation;` — If true, then the rotation of the parent point will be ignored when rotating this point.

#### struct `PV::Transform::RecursiveRotateBranchPoints::FPointState`  
`struct FPointState`  
_L127-133_
- L129 _public member_ `FVector3f ParentPivotPoint;`
- L130 _public member_ `FVector3f ParentIdentityPosition;`
- L131 _public member_ `FMatrix44f TransformMatrix;`
- L132 _public member_ `StateType UserState;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PV`
- L7 _namespace_ `namespace Transform` (scope `PV`)
- L70 _prototype_ `extern void TransformPoint( const FTransformPointAttributeCollection& Attributes, int32 BranchIndex, int32 PointIndex, const FVector3f& Translation, const FQuat4f& Rotation );` (scope `PV::Transform`)
- L78 _typedef_ `using FRotateBranchPointParams = PV::PlantTraversalHelper::FRecursiveWalkBranchPointsParams;` (scope `PV::Transform`)
- L112 _function_ `template<typename StateType> inline bool RecursiveRotateBranchPoints( const FRotateBranchPointsAttributeCollection& Attributes, int32 BranchIndex, const StateType& RootPointState, const TFunction<void(const FRotateBranchPointParams& Params, FRotateBranchPointResult& Result, StateType& State)>& RotatePointsBody, const FVector3f& TrunkPivot = FVector3f::ZeroVector )` (scope `PV::Transform`) — Recursively rotates all points in the branch hierarchy starting from the specified BranchIndex. Parent rotations are multiplied into child transforms ensuring that child points inherit all parent rotations (unless bAbsoluteRotation is set to true). The behavior mirrors bone transform accumulation in a skeletal hierarchy. This function performs a depth-first traversal of the branch hierarchy: 1. It walks all points in the current branch in order. 2. For each point, it invokes RotatePointsBody, allowing the caller to define a local rotation for that point. 3. The computed rotation is accumulated with the parent’s transform, ensuring that rotations propagate hierarchically (similar to skeletal animation). Each point is effectively rotated around its parent pivot (or TrunkPivot for the root). 4. After finishing all points in the current branch, the function recursively processes any axillary (child) branches originating from points in this branch. @param Attributes       The attributes requried to traverse the tree and update the point rotations. @param BranchIndex      Index of the branch to start traversal from. @param RotatePointsBody Callback invoked for each point to compute its rotation. @param TrunkPivot       Pivot used for the root branch. @return true if the traversal and rotation succeeded; false otherwise.
- L150 _function_ `` (scope `PV::Transform::RecursiveRotateBranchPoints`)
- L196 _function_ `inline bool RecursiveRotateBranchPoints( const FRotateBranchPointsAttributeCollection& Attributes, int32 BranchIndex, const TFunction<void(const FRotateBranchPointParams& Params, FRotateBranchPointResult& Result)>& RotatePointsBody, const FVector3f& TrunkPivot = FVector3f::ZeroVector )` (scope `PV::Transform`)
- L207 _function_ `Attributes, BranchIndex, 0, [&](const FRotateBranchPointParams& Params, FRotateBranchPointResult& Result, int32&)` (scope `PV::Transform::RecursiveRotateBranchPoints`)
- L213 _function_ `template<typename StateType> inline bool RecursiveRotatePlantPoints( const FRotateBranchPointsAttributeCollection& Attributes, const StateType& RootPointState, const TFunction<void(const FRotateBranchPointParams& Params, FRotateBranchPointResult& Result, StateType& State)>& RotatePointsBody, const FVector3f& TrunkPivot = FVector3f::ZeroVector )` (scope `PV::Transform`)
- L244 _function_ `inline bool RecursiveRotatePlantPoints( const FRotateBranchPointsAttributeCollection& Attributes, const TFunction<void(const FRotateBranchPointParams& Params, FRotateBranchPointResult& Result)>& RotatePointsBody, const FVector3f& TrunkPivot = FVector3f::ZeroVector )` (scope `PV::Transform`)
- L253 _function_ `Attributes, 0, [&](const FRotateBranchPointParams& Params, FRotateBranchPointResult& Result, int32&)` (scope `PV::Transform::RecursiveRotatePlantPoints`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVCarve.h` (Private)


#### enum `ECarveBasis`  
`enum class ECarveBasis : uint8`  
_L14-20_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `LengthFromRoot UMETA(DisplayName = "Length from root")`
- L17 _public enumerator_ `FromBottom UMETA(DisplayName = "From Bottom")`
- L18 _public enumerator_ `ZPosition UMETA(DisplayName = "Z Position")`
- L19 _public enumerator_ `Radius UMETA(DisplayName = "Radius")`

#### struct `FPVCarveParams`  
`struct FPVCarveParams`  
_L23-32_
- reflection: `USTRUCT()`
- L28 _public member_ `ECarveBasis CarveBasis = ECarveBasis::LengthFromRoot;` — `UPROPERTY(EditAnywhere, Category="Carve", meta=(Tooltip="Reference rule used to trim the plant.\n\nLengthFromRoot: distance measured from the plant's root/trunk base (along the branch graph). FromBottom: relative height starting from the plant's lowest point. ZPosition: absolute world-space Z. Radius: branch thickness."))`
- L31 _public member_ `float Carve = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Carve", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="How much of the structure to remove (0 = none, 1 = aggressive).\n\nControls how much of the structure is removed according to the chosen Carve Basis. Lower values keep more geometry; higher values trim more."))`

#### struct `FPVCarve`  
`struct FPVCarve`  
_L34-61_
- L40 _public prototype_ `static void ApplyCarve(FManagedArrayCollection& OutCollection, const FManagedArrayCollection& SourceCollection, const ECarveBasis CarveBasis, const float Carve, int32* OutFirstInvalidBranchIndex = nullptr);` — OutFirstInvalidBranchIndex, when provided, receives the first branch (if any) whose branchSourceBudNumber either matched none of its own points, or matched a point that is not the branch's first, so callers can log diagnostics on that rare path without this hot path paying for a scan otherwise. Left as INDEX_NONE when all branches are valid.
- L43 _public prototype_ `static void UpdatePointScales(PV::Facades::FPointFacade& PointFacadeOut, const PV::Facades::FPointFacade& PointFacadeSource, const TArray<int>& BranchPoints, const float LastPointScale, const int32 LastPointIndex, const float CarveRatio, const int32 EndIndex, const float FirstPointTargetPScale, const bool InSkipFirstPoint);`
- L47 _public prototype_ `static void RecomputeAttributes(FManagedArrayCollection& OutCollection, const FManagedArrayCollection& SourceCollection, const TMap<int32, int32>& BranchesNewIDsToOldIDs);`
- L50 _public prototype_ `static void CarveFromTop(FManagedArrayCollection& OutCollection, const FManagedArrayCollection& SourceCollection, const float Carve, const ECarveBasis CarveBasis, int32* OutFirstInvalidBranchIndex = nullptr);`
- L53 _public prototype_ `static void CarveFromBottom(FManagedArrayCollection& OutCollection, const FManagedArrayCollection& SourceCollection, const float Carve);`
- L55 _public prototype_ `static void ComputeMetadata(TMap<int32, int32>& OutBranchNumbersToBranchIDs, TMap<int32, float>& OutBranchNumbersToLengthFromRoots, const PV::Facades::FBranchFacade& BranchFacadeSource, const PV::Facades::FPointFacade& PointFacadeSource);`
- L58 _public prototype_ `static void RemoveEntriesAndRecomputeAttributes(FManagedArrayCollection& OutCollection, const FManagedArrayCollection& SourceCollection, TArray<bool>& PointsToRemove, TArray<bool>& BranchesToRemove, TArray<bool>& FoliageInstancesToRemove);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVFoliage.h` (Private)


#### struct `FPVFoliage`  
`struct FPVFoliage`  
_L15-44_
- L17 _public prototype_ `static void DistributeFoliageWithHormoneBasedSettings( FManagedArrayCollection& OutCollection, const FManagedArrayCollection& FoliageCollection, const FHormoneSettings::FDistributionSettings& DistributionSettings, const FHormoneSettings::FScaleSettings& ScaleSettings, const FHormoneSettings::FAxilSettings& AxilSettings, const FHormoneSettings::FPhyllotaxySettings& PhyllotaxySettings, const FPVDistributionVectorParams& VectorSettings, const FPVDistributionConditionParams& DistributionConditions, const int32 RandomSeed, float ChainMaskDistance, float TrunkOffset );`
- L31 _public prototype_ `static void DistributeFoliageWithParametricSettings( FManagedArrayCollection& OutCollection, const FManagedArrayCollection& FoliageCollection, const FParametricSettings::FSpacingSettings& SpacingSettings, const FParametricSettings::FPhyllotaxySettings& PhyllotaxySettings, const FParametricSettings::FAngleSettings& AngleSettings, const FParametricSettings::FScaleSettings& ScaleSettings, const FPVDistributionVectorParams& VectorSettings, const FPVDistributionConditionParams& DistributionConditions, const int32 RandomSeed, float ChainMaskDistance, float TrunkOffset );`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVGrafter.h` (Private)


#### struct `FPVGrafter`  
`struct FPVGrafter`  
_L17-71_
- L32 _public prototype_ `static FTransform GetPointTransform(const FVector3f AttachmentPoint, const FVector3f UpVector, const FVector3f NormalVector, const float Scale);`
- L35 _public prototype_ `static void RescaleBranchForGraftingOnTip(FManagedArrayCollection& OutCollection, const int32 BranchIndex, const int32 BranchTipPointIndex, const float GraftTrunkLength);`
- L39 _public prototype_ `template <typename Fn> static void ForEachGraftPointExcludingRoot(const int32 NumPoints, const int32 RootIndex, Fn&& Func);`
- L41 _public prototype_ `static void SetGraft(FManagedArrayCollection& OutCollection, const FManagedArrayCollection& SourceGraftCollection, const FPVGraftAttributes& InAttributes);`
- L44 _public prototype_ `static bool RemoveFoliageDataIfPresent(FManagedArrayCollection& OutCollection);`
- L46 _public prototype_ `static TArray<FManagedArrayCollection> ExtractIndividualPlants(const FManagedArrayCollection& InCollection);`
- L48 _public prototype_ `static void DistributeGraftWithHormoneBasedSettings( FManagedArrayCollection& OutCollection, TArray<FManagedArrayCollection>& SourceGraftCollections, const FHormoneSettings::FDistributionSettings& DistributionSettings, const FHormoneSettings::FPhyllotaxySettings& PhyllotaxySettings, const FHormoneSettings::FScaleSettings& ScaleSettings, const FHormoneSettings::FAxilSettings& AxilSettings, const FPVDistributionVectorParams& VectorSettings, const FPVDistributionConditionParams& DistributionConditions, const int32 RandomSeed, const bool bRecomputeLightDetected);`
- L60 _public prototype_ `static void DistributeGraftWithParametricSettings( FManagedArrayCollection& OutCollection, TArray<FManagedArrayCollection>& SourceGraftCollections, const FParametricSettings::FSpacingSettings& SpacingSettings, const FParametricSettings::FPhyllotaxySettings& PhyllotaxySettings, const FParametricSettings::FAngleSettings& AngleSettings, const FParametricSettings::FScaleSettings& ScaleSettings, const FPVDistributionVectorParams& VectorSettings, const FPVDistributionConditionParams& DistributionConditions, const int32 RandomSeed, const bool bRecomputeLightDetected);`

#### struct `FPVGrafter::FPVGraftAttributes`  
`struct FPVGraftAttributes`  
_L19-30_
- L21 _public member_ `int32 BranchIndex;`
- L22 _public member_ `int32 PointIndex;`
- L23 _public member_ `int32 CurrentBudNumber;`
- L24 _public member_ `FVector3f AttachmentPoint;`
- L25 _public member_ `FVector3f UpVector;`
- L26 _public member_ `FVector3f NormalVector;`
- L27 _public member_ `float Scale;`
- L28 _public member_ `float LengthFromRoot;`
- L29 _public member_ `bool bIsTipInstance;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVGravity.h` (Private)


#### enum `EGravityMode`  
`enum class EGravityMode : uint8`  
_L19-23_
- reflection: `UENUM()`
- L21 _public enumerator_ `Gravity`
- L22 _public enumerator_ `Phototropic`

#### struct `FPVGravityParams`  
`struct FPVGravityParams`  
_L26-45_
- reflection: `USTRUCT()`
- L31 _public member_ `EGravityMode Mode = EGravityMode::Gravity;` — `UPROPERTY(EditAnywhere, Category="Gravity", meta=(Tooltip="Gravity (downward pull) or Phototropic (growth toward light/up).\n\nGravity = branches bend in the 'Direction' vector (default downward). Phototropic = branches bend upward toward the sky."))`
- L34 _public member_ `float Gravity = 0;` — `UPROPERTY(EditAnywhere, Category="Gravity", meta=(ClampMin=0.0f, ClampMax=10.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Strength of the gravity / phototropic effect.\n\nHigher values yield more pronounced curvature. 0 = no effect."))`
- L37 _public member_ `FVector3f Direction = FVector3f::DownVector;` — `UPROPERTY(EditAnywhere, Category="Gravity", meta=(EditCondition = "Mode == EGravityMode::Gravity", Tooltip="Direction vector for the gravity pull.\n\nWorld-space gravity direction. Default is straight down. Use custom directions for stylized effects (e.g. sideways wind-blown look)."))`
- L40 _public member_ `float AngleCorrection = 0;` — `UPROPERTY(EditAnywhere, Category="Gravity", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Preserves the original branch angle during bending.\n\nBias that resists over-bending by maintaining the original branching angle. Higher = branches keep more of their original orientation. 0 = full bend; 1 = no bend at all (overrides Gravity)."))`
- L44 _public member_ `float PhototropicBias = 0;` — `UPROPERTY(EditAnywhere, Category="Gravity", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, EditCondition = "Mode == EGravityMode::Phototropic", Tooltip="Bias toward light-facing growth.\n\nBias between optimal light direction and shadow avoidance. 0 Being Light optimal, 1 being shadow avoidance"))` — `UPROPERTY()`

#### struct `FPVGravity`  
`struct FPVGravity`  
_L47-57_
- L49 _public prototype_ `static void ApplyGravity(const FPVGravityParams& InGravityParams, FManagedArrayCollection& OutCollection);`
- L53 _private prototype_ `static void GeneratePhototropicData(const FPVGravityParams& InGravityParams, const PV::Facades::FBranchFacade& InBranchFacade, const PV::Facades::FPointFacade& InPointFacade, TArray<FVector3f>& OutPhototropicDirections);`
- L55 _private prototype_ `static void ApplyGravity(const int32 BranchIndex, const FPVGravityParams& GravitySettings, const TArray<FVector3f>& PhototropicDirections, FManagedArrayCollection& OutCollection, FQuat4f TotalDownForce = FQuat4f::Identity, FVector3f PreviousPosition = FVector3f::ZeroVector);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PV`
- L12 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVGrower.h` (Private)


#### struct `FPVGrower`  
`struct FPVGrower`  
_L16-163_
- L18 _public prototype_ `static void Grow(const FPVSeedPoint& SeedPoint, const FPVGrowerParams& InGrowerParams, FManagedArrayCollection& InCollection, bool bUseSplitPoints = true);`
- L20 _public prototype_ `static void Grow(const FManagedArrayCollection& InCollection, const FPVGrowerParams& InGrowerParams, FManagedArrayCollection& Collection, bool bUseSplitPoints = true);`
- L22 _public prototype_ `static void FillCollection(FManagedArrayCollection& Collection, UPVGrowerData* Skeleton, const FPVGrowerParams& GrowerParams);`
- L24 _public prototype_ `static void FillFromCollection(const FManagedArrayCollection& Collection, UPVGrowerData* Skeleton, bool bAgeReset, bool bUseSplitPoints = true);`
- L26 _public prototype_ `static void FillPointsFromCollection(const FManagedArrayCollection& Collection, UPVGrowerData* Skeleton, bool bAgeReset);`
- L28 _public prototype_ `static void FillBranchesFromCollection(const FManagedArrayCollection& Collection, UPVGrowerData* Skeleton, bool bUseSplitPoints = true);`
- L30 _public prototype_ `static float RandomValue(uint32 Seed);`
- L32 _public prototype_ `static void InitializeGrowth(const FPVGrowerParams& InGrowerParams, const FPVSeedPoint& SeedPoint, UPVGrowerData* Skeleton);`
- L34 _public prototype_ `static void InitializeGrowth(const FManagedArrayCollection& InCollection, UPVGrowerData* Skeleton, bool bAgeReset, bool bUseSplitPoints = true);`
- L36 _public prototype_ `static void IterateGrowthCycles(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton);`
- L38 _public prototype_ `static void PrintPoints(UPVGrowerData* Skeleton);`
- L40 _public prototype_ `static void ConvertPointsToCentimeters(UPVGrowerData* Skeleton);`
- L42 _public prototype_ `static void SplitBranchSourcePoints(UPVGrowerData* Skeleton);`
- L44 _public prototype_ `static UPVGrowerPoint* InitializePointFromSeed(const FPVSeedPoint& SeedPoint, UPVGrowerData* Skeleton, const FPVGrowerParams& InGrowerParams);`
- L46 _public prototype_ `static UPVGrowerPrimitive* InitializePrimitiveFromSeed(const FPVSeedPoint& SeedPoint, UPVGrowerData* Skeleton);`
- L48 _public prototype_ `static void ExecuteGrowthCycle(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton, const int InCycle, const FPVColliderMeshData& ColliderMeshData);`
- L50 _public prototype_ `static void UpdateAge(UPVGrowerData* Skeleton);`
- L55 _public prototype_ `static void GenerateLeaves(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton, int32 Cycle, TArray<FPVLeafTransform>& OutLeafTransforms);` — Generates leaf spawn transforms for all branches in the current skeleton state. Translates the Houdini generateLeaves() logic using ethylene levels, phyllotaxy, and axil angle to produce one FTransform per leaf (position in cm, scale = pscale).
- L57 _public prototype_ `static void DetectLight(UPVGrowerData* Skeleton, const FPVColliderMeshData& StaticColliderData, const FPVLeafMeshGeometry& LeafGeometry, const TArray<FPVLeafTransform>& LeafTransforms, int32 InCycle);`
- L60 _public prototype_ `static void ProcessPointLightData(UPVGrowerData* Skeleton, const TArray<FPVPointLightVectorData>& PointLightData);`
- L62 _public prototype_ `static void CreateSprout(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton, const int InCycle);`
- L64 _public prototype_ `static TArray<UPVGrowerPoint*> FindSproutCandidates(UPVGrowerData* Skeleton);`
- L66 _public prototype_ `static TArray<UPVGrowerPoint*> FindSprouts(const FPVGrowerParams& InGrowerParams, TArray<UPVGrowerPoint*> SproutCandidates, const int Cycle);`
- L68 _public prototype_ `static void SetNumberOfTriggered(TArray<UPVGrowerPoint*> Sprouts, const FPVGrowerParams& InGrowerParams);`
- L70 _public prototype_ `static uint32 GetPhyllotaxyMin(const FPVGrowerPhyllotaxyParams& InPhyllotaxy);`
- L72 _public prototype_ `static uint32 GetPhyllotaxyMax(const FPVGrowerPhyllotaxyParams& InPhyllotaxy);`
- L74 _public prototype_ `static void SetAxialElongation(TArray<UPVGrowerPoint*> Sprouts, const FPVTrunkGrowthParams& InAxialParams, const int InRandomSeed);`
- L76 _public prototype_ `static void ApicalGrowthCycle(const FPVGrowerParams& InGrowerParams, TArray<UPVGrowerPoint*> Sprouts, UPVGrowerData* Skeleton);`
- L78 _public prototype_ `static FVector SampleDirectionCone(const FVector& Direction, float AngleInRedians, float RandomX, float RandomY);`
- L80 _public prototype_ `static void AxillaryGrowthCycle(const FPVGrowerParams& InGrowerParams, TArray<UPVGrowerPoint*> Sprouts, UPVGrowerData* Skeleton);`
- L82 _public prototype_ `static void CodominantGrowth(const FPVGrowerParams& InGrowerParams, UPVGrowerPoint* Sprout, UPVGrowerData* Skeleton);`
- L84 _public prototype_ `static void SetApicalDirectionForCodominantSprout(const FPVGrowerParams& InGrowerParams, UPVGrowerPoint* Sprout);`
- L86 _public prototype_ `static void CodominantSprouting(const FPVGrowerParams& InGrowerParams, UPVGrowerPoint* Sprout, UPVGrowerData* Skeleton);`
- L88 _public prototype_ `static void PostGrowth(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton);`
- L90 _public prototype_ `static void ApplyGravity(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton);`
- L92 _public prototype_ `static void ApplyDavinciWeight(UPVGrowerData* Skeleton, const FPVGrowerGravityParams& InGravityParams, const FPVTrunkGrowthParams& InLateralParams);`
- L94 _public prototype_ `static void ApplyGravityWeight(UPVGrowerData* Skeleton, const FPVGrowerGravityParams& InGravityParams, const FPVFoliageParams& InFoliage, const FPVTrunkGrowthParams& InAxialParams, const FPVAgeSenescenceParams& InAgeSenescence);`
- L96 _public prototype_ `static void AttributeAccumulation(UPVGrowerData* Skeleton, TArray<FPVPointGravityAttribute>& GravityAttributes, const FPVGrowerGravityParams& InGravityParams, const FPVTrunkGrowthParams& InAxialParams);`
- L98 _public prototype_ `static void RealignVectors(UPVGrowerData* Skeleton);`
- L100 _public prototype_ `static void GravityBreakRoot(UPVGrowerData* Skeleton, TArray<int32>& BrokenPrimitives, const FPVGrowerGravityParams& InGravityParams);`
- L102 _public prototype_ `static void RemoveBrokenBranches(UPVGrowerData* Skeleton,const TArray<int32>& BrokenPrimitives);`
- L104 _public prototype_ `static void BranchBreak(UPVGrowerData* Skeleton, const FPVAgeSenescenceParams& InAgeSenescence, const FPVGrowerGravityParams& InGravityParams);`
- L106 _public prototype_ `static void RemoveBuds(UPVGrowerData* Skeleton, UPVGrowerPrimitive* Primitive, TArray<int32> BrokenBuds, TArray<UPVGrowerPrimitive*>& PrimitivesToRemove);`
- L108 _public prototype_ `static void FindParentsToClean(UPVGrowerPrimitive* Primitive, TArray<int32>& CleanParents);`
- L110 _public prototype_ `static void GetBranchesToRemoveForBrokenBud(UPVGrowerData* Skeleton, UPVGrowerPoint* Point, TArray<UPVGrowerPrimitive*>& RemoveBranches);`
- L112 _public prototype_ `static void CleanParentsForBrokenBuds(UPVGrowerData* Skeleton, TArray<UPVGrowerPrimitive*>& RemoveBranches, TArray<int32>& CleanParents);`
- L114 _public prototype_ `static void SetBrokenTip(UPVGrowerData* Skeleton, TArray<int32> UnbrokenPoints);`
- L116 _public prototype_ `static TArray<int> ExtractBroken(const TArray<int32>& Points, const TArray<int32>& UnBrokenPoints);`
- L118 _public prototype_ `static TArray<int32> FindNonBrokenBuds(UPVGrowerData* Skeleton, TArray<int32> PrimPoints, const FPVAgeSenescenceParams& InAgeSenescence, const FPVGrowerGravityParams& InGravityParams);`
- L120 _public prototype_ `static void FindAdopters(UPVGrowerData* Skeleton, TArray<UPVGrowerPrimitive*>& Adopters);`
- L122 _public prototype_ `static void AdoptOrphans(UPVGrowerData* Skeleton, TArray<UPVGrowerPrimitive*>& Adopters);`
- L124 _public prototype_ `static void CleanHierarchyForAdoption(UPVGrowerData* Skeleton, UPVGrowerPrimitive* Adopter,const TArray<UPVGrowerPrimitive*>& OrphanBranches);`
- L126 _public prototype_ `static void AdoptOrphanPoints(UPVGrowerData* Skeleton, UPVGrowerPrimitive* Adopter, TArray<int32>& OrphanPoints);`
- L128 _public prototype_ `static void ExtractOrphans(UPVGrowerData* Skeleton, UPVGrowerPrimitive* Adopter,const TArray<UPVGrowerPrimitive*>& Adopters, TArray<UPVGrowerPrimitive*>& OrphanBranches, TArray<int32>& OrphanPoints);`
- L130 _public prototype_ `static void GroundHitBehaviour(UPVGrowerData* Skeleton, const FPVGrowerGravityParams& InGravityParams);`
- L132 _public prototype_ `static void RemovePrimitiveFromParent(UPVGrowerData* Skeleton, TObjectPtr<UPVGrowerPrimitive> Primitive);`
- L134 _public prototype_ `static void DeactivateBrokenBuds(UPVGrowerData* Skeleton, const FPVAgeSenescenceParams& InAgeSenescence);`
- L136 _public prototype_ `static TArray<UPVGrowerPrimitive*> GetGenerationalSortedPrimitives(UPVGrowerData* Skeleton);`
- L138 _public prototype_ `static bool GetActiveInteractions(UPVGrowerData* Skeleton, UPVGrowerPoint* Point);`
- L140 _public prototype_ `static void ComputeGravity(UPVGrowerData* Skeleton, TArray<FPVPointGravityAttribute>& GravityAttributes, const FPVGrowerGravityParams& InGravityParams);`
- L142 _public prototype_ `static FQuat CreateGravityMatrix(const FPVPointGravityAttribute& Attribute, const FPVGrowerGravityParams& InGravityParams);`
- L144 _public prototype_ `static void RotateChildPoints(UPVGrowerData* Skeleton, TArray<FPVPointGravityAttribute>& GravityAttributes, FPVPointGravityAttribute& Attribute,const FQuat& Quat);`
- L146 _public prototype_ `static void UpdatePositions(UPVGrowerData* Skeleton,const TArray<FPVPointGravityAttribute>& GravityAttributes);`
- L148 _public prototype_ `static void OnGrowthCycleEnd(UPVGrowerData* Skeleton);`
- L150 _public prototype_ `static float GetLengthFromTrunk(const UPVGrowerPoint* InPoint, float NextElongation);`
- L152 _public prototype_ `static void AbscissionSenescence(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton, int32 Cycle);`
- L154 _public prototype_ `static bool LightSenescence(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton, FPVBud& Bud, UPVGrowerPrimitive* Primitive);`
- L156 _public prototype_ `static void DeActivateSenescenceChildren(UPVGrowerData* Skeleton, UPVGrowerPrimitive* Primitive);`
- L158 _public prototype_ `static void SetDegradationAmount(const FPVGrowerParams& InGrowerParams, UPVGrowerData* Skeleton, UPVGrowerPrimitive* Primitive, int32 Cycle);`
- L160 _public prototype_ `static void SetSenescence(UPVGrowerData* Skeleton, UPVGrowerPoint* Point, bool bDeactivate);`
- L162 _public prototype_ `static bool ApplyAgeSenescence(const FPVGrowerParams& InGrowerParams, UPVGrowerPoint* Point);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVGrowerData.h` (Private)


#### struct `FPVBudDevelopment`  
`struct FPVBudDevelopment`  
_L11-35_
- reflection: `USTRUCT()`
- L15 _public member_ `int Generation = 0;`
- L17 _public member_ `int BudAge = 0;`
- L19 _public member_ `int BranchAge = 0;`
- L21 _public member_ `int AgeSenescense = 0;`
- L23 _public member_ `int LightSenescense = 0;`
- L25 _public member_ `int RelativeBudAge = 0;`
- L27 _public function_ `TArray<int> GetDataArray() const`
- L32 _public prototype_ `void SetData(const TArray<int>& InArray);`
- L34 _public prototype_ `void ResetAge();`

#### struct `FPVBudDirection`  
`struct FPVBudDirection`  
_L38-60_
- reflection: `USTRUCT()`
- L42 _public member_ `FVector Apical = FVector::Zero();`
- L44 _public member_ `FVector Axillary = FVector::Zero();`
- L46 _public member_ `FVector LightOptimal = FVector::Zero();`
- L48 _public member_ `FVector LightSubOptimal = FVector::Zero();`
- L50 _public member_ `FVector CurveGuide = FVector::Zero();`
- L52 _public member_ `FVector UpVector = FVector::UpVector;`
- L54 _public function_ `TArray<FVector3f> GetDataArray() const`
- L59 _public prototype_ `void SetData(const TArray<FVector3f>& InArray);`

#### struct `FPVBudHormoneLevels`  
`struct FPVBudHormoneLevels`  
_L63-85_
- reflection: `USTRUCT()`
- L67 _public member_ `float Apical = 0.0;`
- L69 _public member_ `float Axillary = 0.0;`
- L71 _public member_ `float AxillaryInhibition = 0.0;`
- L73 _public member_ `float Radical = 0.0;`
- L75 _public member_ `float Ethylene = 0.0;`
- L77 _public member_ `float Cytokinin = 0.0;`
- L79 _public function_ `TArray<float> GetDataArray() const`
- L84 _public prototype_ `void SetData(const TArray<float>& InArray);`

#### struct `FPVBudLateralMeristem`  
`struct FPVBudLateralMeristem`  
_L88-112_
- reflection: `USTRUCT()`
- L92 _public member_ `float LateralMeristem = 0.0;`
- L94 _public member_ `float Multiplier = 0.0;`
- L96 _public member_ `float Inactive = 0.0;`
- L98 _public member_ `float Davinci = 0.0;`
- L100 _public member_ `float ParentDot = 0.0;`
- L102 _public member_ `float RootDistance = 0.0;`
- L104 _public member_ `float Degredation = 0.0;`
- L106 _public function_ `TArray<float> GetDataArray() const`
- L111 _public prototype_ `void SetData(const TArray<float>& InArray);`

#### struct `FPVBudLightDetected`  
`struct FPVBudLightDetected`  
_L115-133_
- reflection: `USTRUCT()`
- L119 _public member_ `float Available = 0.0;`
- L121 _public member_ `float Resource = 0.0;`
- L123 _public member_ `float Branch = 0.0;`
- L125 _public member_ `float Collision = 0.0;`
- L127 _public function_ `TArray<float> GetDataArray() const`
- L132 _public prototype_ `void SetData(const TArray<float>& InArray);`

#### struct `FPVBudStatus`  
`struct FPVBudStatus`  
_L136-166_
- reflection: `USTRUCT()`
- L140 _public member_ `int ApicalMeristem = 0;`
- L142 _public member_ `int Codominant = 0;`
- L144 _public member_ `int Axillary = 0;`
- L146 _public member_ `int Seed = 0;`
- L148 _public member_ `int Dormant = 0;`
- L150 _public member_ `int Triggered = 0;`
- L152 _public member_ `int NumTriggered = 0;`
- L154 _public member_ `int Inactive = 0;`
- L156 _public member_ `int BrokenTip = 0;`
- L158 _public member_ `int Broken = 0;`
- L160 _public function_ `TArray<int> GetDataArray() const`
- L165 _public prototype_ `void SetData(const TArray<int>& InArray);`

#### struct `FPVBud`  
`struct FPVBud`  
_L169-186_
- reflection: `USTRUCT()`
- L173 _public member_ `int BudNumber = 0;`
- L175 _public member_ `FPVBudDevelopment Development;`
- L177 _public member_ `FPVBudDirection Direction;`
- L179 _public member_ `FPVBudHormoneLevels HormoneLevels;`
- L181 _public member_ `FPVBudLateralMeristem LateralMeristem;`
- L183 _public member_ `FPVBudLightDetected LightDetected;`
- L185 _public member_ `FPVBudStatus Status;`

#### struct `FPVSeedInfo`  
`struct FPVSeedInfo`  
_L189-210_
- reflection: `USTRUCT()`
- L193 _public member_ `float PScale = 0.0;`
- L195 _public member_ `float PScaleRatio = 0.0;`
- L197 _public member_ `uint32 Type = 0;`
- L199 _public member_ `uint32 Generation = 0;`
- L201 _public member_ `uint32 PlantNumber = 0;`
- L203 _public member_ `uint32 BrancNumber = 0;`
- L205 _public member_ `uint32 MaxBranchNumber = 0;`
- L207 _public member_ `uint32 BudNumber = 0;`
- L209 _public member_ `uint32 MaxBudNumber = 0;`

#### enum `EPVAbscissionType`  
`enum class EPVAbscissionType : uint8`  
_L213-217_
- reflection: `UENUM()`
- L215 _public enumerator_ `Age`
- L216 _public enumerator_ `Light`

#### struct `FPVPrimitiveSenescence`  
`struct FPVPrimitiveSenescence`  
_L220-238_
- reflection: `USTRUCT()`
- L225 _public member_ `bool bDegradation = false;` — `UPROPERTY()`
- L228 _public member_ `float DegradationAmount = 0.0;` — `UPROPERTY()`
- L231 _public member_ `bool bAbscission = false;` — `UPROPERTY()`
- L234 _public member_ `EPVAbscissionType AbscissionType = EPVAbscissionType::Age;` — `UPROPERTY()`
- L237 _public member_ `bool bInactive = false;` — `UPROPERTY()`

#### class `UPVGrowerPrimitive`  
`class UPVGrowerPrimitive : public UObject`  
_L241-270_
- reflection: `UCLASS()`
- inherits: `UObject`
- L245 _public member_ `int32 BranchNumber = 1;`
- L247 _public member_ `int32 BranchParentNumber = 0;`
- L249 _public member_ `int32 BranchSourceBudNumber = 1;`
- L251 _public member_ `int32 PlantNumber = 1;`
- L254 _public member_ `TArray<int32> BranchBuds;` — Stores the Bud Numbers of the Points
- L257 _public member_ `TArray<int32> Children;` — Stores the BranchNumbers of Children
- L260 _public member_ `TArray<int32> Parents;` — Stores the BranchNumbers of parents
- L262 _public member_ `bool bNewBranch = false;`
- L265 _public member_ `FPVPrimitiveSenescence Senescence;` — `UPROPERTY()`
- L267 _public prototype_ `void AddBranchBud(UPVGrowerPoint* Point);`
- L269 _public prototype_ `void InsertBranchBud(UPVGrowerPoint* Point, int32 Index);`

#### class `UPVGrowerPoint`  
`class UPVGrowerPoint : public UObject`  
_L273-338_
- reflection: `UCLASS()`
- inherits: `UObject`
- L279 _public member_ `FVector Position;` — `UPROPERTY()`
- L282 _public member_ `float PScale = 0.0;` — `UPROPERTY()`
- L285 _public member_ `FVector Up = FVector::UpVector;` — `UPROPERTY()`
- L288 _public member_ `int VisAgeSenescen = 0.0;` — `UPROPERTY()`
- L290 _public member_ `FVector VisAuxin = FVector::ZeroVector;`
- L292 _public member_ `FVector VisCytokinin = FVector::ZeroVector;`
- L294 _public member_ `FVector VisEthylene = FVector::ZeroVector;`
- L296 _public member_ `FVector VisGravity = FVector::ZeroVector;`
- L298 _public member_ `int VisLightSenescen = 0;`
- L301 _public member_ `int16 BranchNumber = 0;` — `UPROPERTY()`
- L303 _public member_ `FPVBud Bud;`
- L305 _public member_ `FPVSeedInfo SeedInfo;`
- L308 _public member_ `float LengthFromRoot = 0.0;` — `UPROPERTY()`
- L311 _public member_ `float LengthFromTrunk = 0.0;` — `UPROPERTY()`
- L313 _public member_ `TArray<float> NextAxialElongations;`
- L315 _public member_ `FVector NextApicalDirection = FVector::ZeroVector;`
- L317 _public member_ `FVector NextAxillaryDirection = FVector::ZeroVector;`
- L319 _public member_ `FVector NextUpVector = FVector::UpVector;`
- L321 _public member_ `bool bNewBud = false;`
- L323 _public member_ `bool bLateralAppend = false;`
- L325 _public member_ `float IgnoreGravityBreak = 0.0f;`
- L328 _public member_ `TObjectPtr<UPVGrowerPrimitive> Primitive;` — `UPROPERTY()`
- L331 _public member_ `TArray<TObjectPtr<UPVGrowerPoint>> Neighbors;` — `UPROPERTY()`
- L333 _public member_ `int32 RefCount = 0;`
- L335 _public member_ `bool bInput = false;`
- L337 _public function_ `int32 GetBudNumber() const`

#### class `UPVGrowerData`  
`class UPVGrowerData : public UObject`  
_L341-415_
- reflection: `UCLASS()`
- inherits: `UObject`
- L347 _public member_ `TArray<TObjectPtr<UPVGrowerPoint>> Points;` — `UPROPERTY()`
- L350 _public member_ `TArray<TObjectPtr<UPVGrowerPrimitive>> Primitives;` — `UPROPERTY()`
- L353 _public member_ `TMap<int32, int32> BudNumberIndexMap;` — `UPROPERTY()`
- L356 _public member_ `TMap<int32, int32> PrimitiveNumberIndexMap;` — `UPROPERTY()`
- L358 _public member_ `float MinLengthFromRoot = 0.0;`
- L360 _public member_ `int32 MaxBranchNumber = 25;`
- L362 _public member_ `int32 MaxBudNumber = 0;`
- L366 _public member_ `TArray<FPVLeafTransform> LastLeafTransforms;` — Leaf transforms produced by the last growth cycle; written to the output collection by FillCollection for viewport visualization.
- L372 _public member_ `int32 InputCycleOffset = 0;` — Cycle offset derived from the max bud age in the upstream grower's collection. Added to the current cycle when computing SaplingAge in GenerateLeaves so that a chained grower begins with the foliage maturity the upstream plant already reached. Zero for fresh (seed-initialised) skeletons.
- L379 _public prototype_ `void AddPoint(TObjectPtr<UPVGrowerPoint> Point, TObjectPtr<UPVGrowerPrimitive> Primitive, bool bAddToBranch = true);` — Add the point to Points list and associate to the branch Increments the BudNumber and add point to BudNumberIndexMap
- L384 _public prototype_ `void AddPoint(TObjectPtr<UPVGrowerPoint> Point, int32 BudNumber);` — Add the point to points list and also add it to BudNumberIndexMap
- L386 _public prototype_ `void RemovePoint(TObjectPtr<UPVGrowerPrimitive> Primitive, int32 BudNumber);`
- L388 _public prototype_ `void RemovePoint(TObjectPtr<UPVGrowerPoint> Point);`
- L390 _public prototype_ `int32 GetPointIndex(int32 BudNumber);`
- L392 _public prototype_ `TObjectPtr<UPVGrowerPoint> GetPoint(int32 BudNumber) const;`
- L394 _public prototype_ `TObjectPtr<UPVGrowerPoint> GetPointFromIndex(int32 PointIndex) const;`
- L396 _public prototype_ `int32 GetPrimitiveIndex(int32 BranchNumber) const;`
- L398 _public prototype_ `void AddPrimitive(TObjectPtr<UPVGrowerPrimitive> Primitive);`
- L400 _public prototype_ `void AddPrimitive(TObjectPtr<UPVGrowerPrimitive> Primitive, int32 BranchNumber);`
- L402 _public prototype_ `UPVGrowerPrimitive* GetPrimitive(int32 BranchNumber) const;`
- L404 _public prototype_ `void RemovePrimitive(UPVGrowerPrimitive* RemoveItem);`
- L406 _public prototype_ `void RemovePrimitive(int32 PrimitiveNumber, bool bRemoveChildren = true);`
- L408 _public prototype_ `void RemovePrimitiveReferences(TObjectPtr<UPVGrowerPrimitive> Primitive, bool bRemoveChildren);`
- L410 _public prototype_ `void RemovePrimitiveInternal(int32 PrimitiveNumber);`
- L412 _public prototype_ `TArray<UPVGrowerPrimitive*> GetPointPrimitives(UPVGrowerPoint* Point) const;`
- L414 _public prototype_ `TArray<UPVGrowerPrimitive*> GetSourceBudPrimitives(int32 SourceBudNumber) const;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVImporter_StaticMesh.h` (Private)


#### enum `PV::StaticMeshImport::EImportResult`  
`enum class EImportResult`  
_L13-22_
- L15 _public enumerator_ `Success`
- L16 _public enumerator_ `InvalidSourceMesh`
- L17 _public enumerator_ `InvalidOutputPath`
- L18 _public enumerator_ `InvalidMeshData`
- L19 _public enumerator_ `MeshNotReady`
- L20 _public enumerator_ `InvalidMaterialFilter`
- L21 _public enumerator_ `FailedToGenerateGrowthData`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace StaticMeshImport` (scope `PV`)
- L24 _prototype_ `EImportResult ImportGrowthDataFromStaticMesh(const FPVImportStaticMeshParams& InParams, const FPVImportStaticMeshDebugParams& InDebugParams, FPVImportStaticMeshOutput& Output);` (scope `PV::StaticMeshImport`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVImporter_Texture2D.h` (Private)


#### enum `PV::Texture2DImport::ETracePerimeterCurvesResult`  
`enum class ETracePerimeterCurvesResult`  
_L13-19_
- L15 _public enumerator_ `Success`
- L16 _public enumerator_ `InvalidSourceTexture`
- L17 _public enumerator_ `InvalidSampleSize`
- L18 _public enumerator_ `InvalidTextureSize`

#### enum `PV::Texture2DImport::EFindTipsResult`  
`enum class EFindTipsResult`  
_L33-37_
- L35 _public enumerator_ `Success`
- L36 _public enumerator_ `NoTipsFound`

#### enum `PV::Texture2DImport::EImportResult`  
`enum class EImportResult`  
_L46-52_
- L48 _public enumerator_ `Success`
- L49 _public enumerator_ `InvalidPerimeterCurves`
- L50 _public enumerator_ `InvalidTipsAttribute`
- L51 _public enumerator_ `FailedToGenerateGrowthData`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace Texture2DImport` (scope `PV`)
- L21 _prototype_ `ETracePerimeterCurvesResult TracePerimeterCurves( TObjectPtr<UTexture2D> Texture2DAsset, int32 SampleResolution, bool bInvertImage, float WhiteLevel, EPCGTextureColorChannel ColorChannel, float MinBoundsArea, int32 SmoothingIterations, float SimplificationAmount, TArray<UE::Geometry::FPolygon2f>& OutPerimeterCurves );` (scope `PV::Texture2DImport`)
- L39 _prototype_ `EFindTipsResult FindTips( const TArray<UE::Geometry::FPolygon2f>& PerimeterCurves, float TipAngleThresholdInDegrees, float MaxTipAngleSearchDist, TArray<TArray<bool>>& OutTips );` (scope `PV::Texture2DImport`)
- L54 _prototype_ `EImportResult ImportGrowthDataFromPerimeterCurves( const TArray<UE::Geometry::FPolygon2f>& PerimeterCurves, const TArray<TArray<bool>>& Tips, const TArray<FPVImportTexture2DPlantSettings>& PlantSettings, EPVImportTexture2DDebugState DebugState, FPVImportTexture2DOutput& Output );` (scope `PV::Texture2DImport`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVLightDetection.h` (Private)


#### enum `EPVLightDetectionCollisionType`  
`enum class EPVLightDetectionCollisionType : uint8`  
_L17-23_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `Cylinder`
- L20 _public enumerator_ `TaperedCylinder`
- L21 _public enumerator_ `Card`
- L22 _public enumerator_ `Mesh`

#### struct `FPVRaycastOrigin`  
`struct FPVRaycastOrigin`  
_L25-30_
- L27 _public member_ `int32 PointNumber;`
- L28 _public member_ `int32 BranchNumber;`
- L29 _public member_ `FVector3f Position;`

#### struct `FPVCollisionData`  
`struct FPVCollisionData`  
_L32-41_
- L34 _public member_ `int32 PointNumber;`
- L35 _public member_ `int32 BranchNumber;`
- L36 _public member_ `int32 ApicalRay;`
- L37 _public member_ `int32 Type;`
- L38 _public member_ `FVector3f Position;`
- L39 _public member_ `FVector3f Direction;`
- L40 _public member_ `FVector3f Extents;`

#### struct `FPVLightDetectionData`  
`struct FPVLightDetectionData`  
_L43-51_
- L45 _public member_ `int32 PointNumber;`
- L46 _public member_ `int32 RayNumber;`
- L47 _public member_ `FVector3f Direction;`
- L48 _public member_ `float LightValue;`
- L49 _public member_ `int32 Hits;`
- L50 _public member_ `int32 FaliureType;`

#### struct `FPVPointLightVectorData`  
`struct FPVPointLightVectorData`  
_L53-59_
- L55 _public member_ `int32 PointNumber;`
- L56 _public member_ `float LightAvailable;`
- L57 _public member_ `FVector3f LightOptimalDirection;`
- L58 _public member_ `FVector3f LightSubOptimalDirection;`

#### struct `FPVMeshGeometryRange`  
`struct FPVMeshGeometryRange`  
_L64-70_
- desc: GPU struct: geometry for one unique static mesh (object-space vertices/indices). Multiple instances can reference the same geometry via GeometryIndex. Layout must match PVMeshGeometryRange in PVLightDetectionCS.usf (16 bytes).
- L66 _public member_ `int32 StartVertex;`
- L67 _public member_ `int32 EndVertex;`
- L68 _public member_ `int32 StartIndex;`
- L69 _public member_ `int32 EndIndex;`

#### struct `FPVMeshInstanceData`  
`struct FPVMeshInstanceData`  
_L74-81_
- desc: GPU struct: one placed instance of a geometry (external colliders — no branch association). Layout must match PVMeshInstanceData in PVLightDetectionCS.usf (112 bytes).
- L76 _public member_ `FMatrix44f Transform;` — 64 bytes — object-to-world
- L77 _public member_ `FVector4f AABBMin;` — 16 bytes — world-space AABB (w unused)
- L78 _public member_ `FVector4f AABBMax;` — 16 bytes — world-space AABB (w unused)
- L79 _public member_ `int32 GeometryIndex;` — 4 bytes — index into Geometries array
- L80 _public member_ `int32 _Pad[3];` — 12 bytes — explicit padding to reach 112 bytes

#### struct `FPVLeafMeshInstanceData`  
`struct FPVLeafMeshInstanceData`  
_L87-95_
- desc: GPU struct: one placed leaf instance — like FPVMeshInstanceData but carries the branch it belongs to so the shader can skip leaves on the same branch as the ray-cast origin. Layout must match PVLeafMeshInstanceData in PVLightDetectionCS.usf (112 bytes).
- L89 _public member_ `FMatrix44f Transform;` — 64 bytes — object-to-world
- L90 _public member_ `FVector4f AABBMin;` — 16 bytes — world-space AABB (w unused)
- L91 _public member_ `FVector4f AABBMax;` — 16 bytes — world-space AABB (w unused)
- L92 _public member_ `int32 GeometryIndex;` — 4 bytes — index into Geometries array
- L93 _public member_ `int32 BranchNumber;` — 4 bytes — owning branch (for self-exclusion)
- L94 _public member_ `int32 _Pad[2];` — 8 bytes — explicit padding to reach 112 bytes

#### struct `FPVColliderMeshData`  
`struct FPVColliderMeshData`  
_L98-105_
- L100 _public member_ `TArray<FVector3f> Vertices;` — object-space, shared across all instances
- L101 _public member_ `TArray<uint32> Indices;` — shared across all instances
- L102 _public member_ `TArray<FPVMeshGeometryRange> Geometries;` — one entry per unique UStaticMesh
- L103 _public member_ `TArray<FPVMeshInstanceData> Instances;` — external collider instances (no branch exclusion)
- L104 _public member_ `TArray<FPVLeafMeshInstanceData> LeafInstances;` — leaf instances (self-branch exclusion applied in shader)

#### struct `FPVLightDetection`  
`struct FPVLightDetection`  
_L107-132_
- L109 _public prototype_ `static TArray<FVector3f> GetApicalRayArray();`
- L111 _public prototype_ `static TArray<FPVCollisionData> BuildPVCollisionDataSkeleton(const UPVGrowerData* Skeleton);`
- L113 _public prototype_ `static TArray<FPVRaycastOrigin> BuildPVRayOriginData(const UPVGrowerData* Skeleton);`
- L115 _public prototype_ `static void BuildPVCollisionData(const TArray<FPVColliderParams>& Colliders, FPVColliderMeshData& MeshColliderData);`
- L119 _public prototype_ `static void BuildLeafMeshGeometry(const UStaticMesh* Mesh, FPVLeafMeshGeometry& OutGeometry);` — Extract vertices, indices, and object-space AABB from a static mesh. Call once when the mesh is selected; reuse OutGeometry every growth cycle.
- L125 _public prototype_ `static void BuildPVLeafInstanceData(const FPVLeafMeshGeometry& LeafGeometry, const TArray<FPVLeafTransform>& LeafTransforms, FPVColliderMeshData& OutMeshColliderData);` — Append leaf geometry and per-instance data into OutMeshColliderData. Each leaf instance carries its BranchNumber so the shader can skip leaves on the same branch as the ray origin. No-op if LeafGeometry is invalid or LeafTransforms is empty.
- L127 _public prototype_ `static TArray<FPVPointLightVectorData> ExecuteLightDetection(TArray<FPVCollisionData> CollisionData, TArray<FPVRaycastOrigin> RaycastOrigins, const FPVColliderMeshData& MeshColliderData);`
- L129 _public prototype_ `static void PrintLightDetectionData(TArray<FPVLightDetectionData> LightDetectionData);`
- L131 _public prototype_ `static void PrintPointLightVectorData(TArray<FPVPointLightVectorData> PointLightVectorData);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVLightDetectionCS.h` (Private)


#### class `FPVLightDetectionCS`  
`class FPVLightDetectionCS : public FGlobalShader`  
_L9-31_
- inherits: `FGlobalShader`
- L11 _private prototype_ `DECLARE_GLOBAL_SHADER(FPVLightDetectionCS);`
- L12 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FPVLightDetectionCS, FGlobalShader);`

#### class `FPVLightVectorCalculationCS`  
`class FPVLightVectorCalculationCS : public FGlobalShader`  
_L33-46_
- inherits: `FGlobalShader`
- L35 _private prototype_ `DECLARE_GLOBAL_SHADER(FPVLightVectorCalculationCS);`
- L36 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FPVLightVectorCalculationCS, FGlobalShader);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVMaterialSettings.h` (Private)


#### enum `EGenerationOffsetMethod`  
`enum class EGenerationOffsetMethod : uint8`  
_L13-17_
- reflection: `UENUM()`
- L15 _public enumerator_ `Clamped`
- L16 _public enumerator_ `Refit`

#### enum `EMaterialDistributionMethod`  
`enum class EMaterialDistributionMethod : uint8`  
_L20-24_
- reflection: `UENUM()`
- L22 _public enumerator_ `Repeat`
- L23 _public enumerator_ `Fit`

#### enum `EYTextureMode`  
`enum class EYTextureMode : uint8`  
_L27-32_
- reflection: `UENUM()`
- L29 _public enumerator_ `Default`
- L30 _public enumerator_ `Fit0_1`

#### enum `EUVMaterialMode`  
`enum class EUVMaterialMode : uint8`  
_L35-40_
- reflection: `UENUM()`
- L37 _public enumerator_ `Generation`
- L38 _public enumerator_ `Age`
- L39 _public enumerator_ `Radius`

#### struct `FTrunkGenerationMaterialSetup`  
`struct FTrunkGenerationMaterialSetup`  
_L43-76_
- reflection: `USTRUCT()`
- L48 _public member_ `bool bDeriveFromTrunkTextureSetup = false;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(DisplayName="Use Trunk Texture Setup", Tooltip="When enabled, the Material and X Range for this generation are sourced automatically from the connected Trunk Texture Setup pin, matched by generation index."))`
- L51 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(EditCondition="!bDeriveFromTrunkTextureSetup", EditConditionHides, Tooltip="Material to apply to this generation."))`
- L54 _public member_ `EYTextureMode YTextureMode = EYTextureMode::Default;` — `UPROPERTY(EditAnywhere, Category="Materials" , meta=(DisplayName = "Y Texture Mode", Tooltip="How textures align vertically (Default uses native tiling; Fit0_1 stretches once)."))`
- L57 _public member_ `float YScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(DisplayName = "Y Scale", EditCondition = "YTextureMode == EYTextureMode::Default", Tooltip="Texture tiling scale along Y.\n\nAdjusts vertical texture scale. Higher values increase tiling frequency (finer detail); lower values broaden patterns."))`
- L60 _public member_ `float YOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(DisplayName = "Y Offset", EditCondition = "YTextureMode == EYTextureMode::Default", Tooltip="Shifts texture position along Y.\n\nMoves the material vertically without changing scale. Useful for aligning repeats or hiding seams."))`
- L63 _public member_ `float YOffsetRandom = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(DisplayName = "Y Offset Random", EditCondition = "YTextureMode == EYTextureMode::Default", Tooltip="Randomizes Y offset per instance.\n\nAdds per-instance variation to the vertical texture offset to avoid visible repetitions across branches."))`
- L66 _public member_ `float XOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(Tooltip="Shifts texture position along X.\n\nMoves the material horizontally across the mesh to fine-tune alignment or hide seams."))`
- L69 _public member_ `float XOffsetRandom = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Materials" , meta=(DisplayName = "X Offset Random", Tooltip="Randomizes X offset per instance.\n\nAdds per-instance variation to the horizontal texture offset to break pattern repetition."))`
- L74 _public member_ `FFloatRange URange = FFloatRange(0,1);` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(DisplayName = "X Range", EditCondition="!bDeriveFromTrunkTextureSetup", EditConditionHides, Tooltip="Limits horizontal coverage range.\n\nSets the portion of the mesh affected along the X axis, useful for restricting materials (e.g., moss/lichen) to a subsection."))`

#### struct `FPVMaterialSettings`  
`struct FPVMaterialSettings`  
_L82-124_
- reflection: `USTRUCT()`
- L87 _public member_ `int32 GenerationOffset = 0;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(ClampMin = "0", Tooltip="Shifts which branch generation the material targets.\n\nAdjusts the generation index used for material assignment. For example, an offset of 1 targets branches one level above the default (trunk → gen0, first branches → gen1, etc.)."))`
- L90 _public member_ `EMaterialDistributionMethod DistributionMethod = EMaterialDistributionMethod::Repeat;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(Tooltip="Repeat or Fit materials across generations.\n\nRepeat: cycle materials when generations exceed material count. Fit: stretch N materials across all generations."))`
- L93 _public member_ `TArray<FTrunkGenerationMaterialSetup> MaterialSetups;` — `UPROPERTY(EditAnywhere, Category="Materials" , DisplayName="Generation Materials", meta=(Tooltip="List of materials applied to the mesh.\n\nDefines the collection of materials that can be distributed by generation, age, or radius. Enables complex setups (e.g., bark, moss, twig materials by region)."))`
- L96 _public member_ `EUVMaterialMode MaterialMode = EUVMaterialMode::Generation;` — `UPROPERTY(EditAnywhere, Category="Materials", meta=(Tooltip="Driver for material selection: Generation, Age, or Radius.\n\nGeneration: by branch hierarchy. Age: by segment age. Radius: by branch thickness."))`
- L103 _public prototype_ `void ApplyMaterialSettings(FManagedArrayCollection& Collection) const;` — Function takes the Collection as input and sets the branchUVMaterial for Branch, calculates the V value of the UV according to the settings and write into Point Group calculates the U offset and write to the Point Group in collection
- L105 _public prototype_ `void SetMaterial(UMaterialInterface* Material, FVector2f UMinMax, int32 Index);`
- L107 _public prototype_ `void SetMaterial(FString TrunkMaterial, FVector2f UMinMax, int32 Index);`
- L111 _private prototype_ `void SetBranchUVMaterial(FManagedArrayCollection& Collection, TArray<int32>& UsedMaterials, TArray<FBranchUVData>& BranchUVData) const;`
- L113 _private prototype_ `float GetMaterialValue(float Value, float MinValue, float MaxValue, float MinGeneration, float MaxGeneration) const;`
- L115 _private prototype_ `void SetUVOffsetAndScale(FManagedArrayCollection& Collection, TArray<FBranchUVData>& BranchUVData) const;`
- L117 _private prototype_ `void SetBaseUVs(FManagedArrayCollection& Collection, TArray<FPointUVData>& PointUVData) const;`
- L119 _private prototype_ `TArray<float> MakeSegmentArray(const PV::Facades::FPointFacade& PointFacade,const TArray<int32>& Points, const float MaxPointScale, const int Mode) const;`
- L121 _private prototype_ `void FitUVs01(FManagedArrayCollection& Collection, TArray<FPointUVData>& PointUVData, const TArray<int32>& UsedMaterials, TArray<FBranchUVData>& BranchUVData) const;`
- L123 _private prototype_ `void SetOutputUVs(FManagedArrayCollection& Collection, TArray<FPointUVData>& PointUVData, TArray<FBranchUVData>& BranchUVData) const;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVMeshBuilder.h` (Private)


#### struct `FPVMeshBuilderParams`  
`struct FPVMeshBuilderParams`  
_L29-53_
- reflection: `USTRUCT()`
- L34 _public member_ `FPVMeshBuilderSkeletonShapingParams SkeletonShaping;` — `UPROPERTY(EditAnywhere, Category="Skeleton Shaping", meta=(ShowOnlyInnerProperties, PCG_NotOverridable))`
- L37 _public member_ `FPVMeshBuilderBranchRadiusParams BranchRadius;` — `UPROPERTY(EditAnywhere, Category="Branch Radius", meta=(ShowOnlyInnerProperties, PCG_NotOverridable))`
- L40 _public member_ `FPVMeshBuilderProfileDetailParams ProfileDetails;` — `UPROPERTY(EditAnywhere, Category="Profile Details", meta=(ShowOnlyInnerProperties, PCG_NotOverridable))`
- L43 _public member_ `FPVMeshBuilderMeshDetailParams MeshDetails;` — `UPROPERTY(EditAnywhere, Category="Mesh Details", meta=(ShowOnlyInnerProperties, PCG_NotOverridable))`
- L46 _public member_ `FPVMaterialSettings MaterialDetails;` — `UPROPERTY(EditAnywhere, Category="Material Details", meta=(PCG_NotOverridable))`
- L49 _public member_ `FPVMeshBuilderDisplacementParams Displacement;` — `UPROPERTY(EditAnywhere, Category="Displacement", meta=(ShowOnlyInnerProperties, PCG_NotOverridable))`
- L52 _public member_ `TArray<float> DisplacementValues;` — `UPROPERTY(Transient, NonTransactional)`

#### struct `FLocalDynamicMeshData`  
`struct FLocalDynamicMeshData`  
_L55-70_
- L67 _public member_ `TArray<FVertex> Vertices;`
- L68 _public member_ `TArray<FIntVector4> Triangles;`
- L69 _public member_ `int MaterialID = 0;`

#### struct `FLocalDynamicMeshData::FVertex`  
`struct FVertex`  
_L57-65_
- L59 _public member_ `FVector3f Position;`
- L60 _public member_ `FVector3f Normal;`
- L61 _public member_ `FVector2f UV;`
- L62 _public member_ `FVector2f UV1;`
- L63 _public member_ `FVector2f UV2;`
- L64 _public member_ `float PointIndex;`

#### struct `FDisplacementData`  
`struct FDisplacementData`  
_L72-84_
- L74 _public member_ `const TArrayView<const float> Values;`
- L75 _public member_ `const int32 TextureWidth;`
- L76 _public member_ `const int32 TextureHeight;`
- L78 _public function_ `FDisplacementData(const TArrayView<const float>& InValues, const int32 InWidth, const int32 InHeight) : Values(InValues) , TextureWidth(InWidth) , TextureHeight(InHeight)`

#### class `FPVMeshGenerator`  
`class FPVMeshGenerator : public UE::Geometry::FMeshShapeGenerator`  
_L86-133_
- inherits: `UE::Geometry::FMeshShapeGenerator`
- L88 _private member_ `int32 VerticesCount = 0;`
- L89 _private member_ `int32 TriangleCount = 0;`
- L91 _private member_ `TArray<FLocalDynamicMeshData>* MeshesDatas = nullptr;`
- L94 _public function_ `FPVMeshGenerator(const int32 InVerticesCount, const int32 InTriangleCount, TArray<FLocalDynamicMeshData>* InMeshesDatas) : VerticesCount(InVerticesCount) , TriangleCount(InTriangleCount) , MeshesDatas(InMeshesDatas)`
- L101 _public function_ `virtual FMeshShapeGenerator& Generate() override`

#### struct `FMeshPointUVData`  
`struct FMeshPointUVData`  
_L135-140_
- L137 _public member_ `float TextureCoordV;`
- L138 _public member_ `float TextureCoordUOffset;`
- L139 _public member_ `FVector2f URange;`

#### struct `FPVMeshBuilder`  
`struct FPVMeshBuilder`  
_L142-207_
- L144 _public prototype_ `static void GenerateGeometryCollection(const FManagedArrayCollection& InSkeletonCollection, const FManagedArrayCollection& InPlantProfileCollection, const FPVMeshBuilderParams& MeshBuilderParams, FGeometryCollection& OutGeometryCollection);`
- L147 _public prototype_ `static void AddPointsToSkeleton(FManagedArrayCollection& OutCollection, int32 SkeletonResolution);`
- L149 _public prototype_ `static void ApplyNoiseToSkeleton(FManagedArrayCollection& OutCollection, const FPVMeshBuilderParams& MeshBuilderParams);`
- L151 _public prototype_ `static void GenerateDynamicMesh(FManagedArrayCollection& Collection, const FManagedArrayCollection& InPlantProfileCollection, const FPVMeshBuilderParams& MeshBuilderParams, TObjectPtr<UDynamicMesh>& OutMesh);`
- L154 _public prototype_ `static bool ExtractDisplacementData(const TObjectPtr<UTexture2D>& Texture, TArray<float>& OutValues, FString& OutError);`
- L157 _private prototype_ `static TSet<int32> CollectHardPoints(const PV::Facades::FBranchFacade& BranchFacade, const PV::Facades::FPointFacade& PointFacade, const PV::Facades::FPlantFacade& PlantFacade, PV::FPointNjordPixelIndexAttributeConstView NjordPixelIndexAttribute);`
- L160 _private prototype_ `static TSet<int32> ComputePointGradients(PV::FPointHullGradientAttributeConstView HullGradientAttribute, PV::FPointMainTrunkGradientAttributeConstView MainTrunkGradientAttribute, PV::FPointGroundGradientAttributeConstView GroundGradientAttribute, PV::FPointScaleGradientAttributeConstView ScaleGradientAttribute, const FPVMeshBuilderParams& MeshBuilderParams, const TSet<int32>& HardPoints, const float MaxPointScale, TArray<float>& OutMeshDivisionsGradients, TArray<float>& OutDeltaModifiers);`
- L168 _private prototype_ `static float GetMaxDeltaBetweenHardPoints(const PV::Facades::FBranchFacade& BranchFacade, const PV::Facades::FPointFacade& PointFacade, const TSet<int32>& HardPoints);`
- L171 _private prototype_ `static void PerformPathSimplification(const PV::Facades::FBranchFacade& BranchFacade, const PV::Facades::FPointFacade& PointFacade, const FPVMeshBuilderParams& MeshBuilderParams, const float MaxPointScale, const TSet<int32>& HardPoints, const TArray<float>& DeltaModifiers, TSet<int32>& InOutPointsToRemove);`
- L176 _private prototype_ `static TArray<int32> ComputeMeshDivisions(const PV::Facades::FBranchFacade& BranchFacade, const FPVMeshBuilderParams& MeshBuilderParams, const TArray<float>& MeshDivisionsGradients, const int32 PointCount);`
- L179 _private prototype_ `static void TriangulateRings(const TArray<int32>& PreviousIndices, const TArray<int32>& CurrentIndices, int32& InOutPolyGroupIndex, FLocalDynamicMeshData& OutMeshData);`
- L182 _private prototype_ `static float GetProfileMultiplier(const TArray<float>& InProfilePoints, const float ProfileUV_U);`
- L184 _private prototype_ `static TMap<int32, TArray<int32>> GetPointsIndicesToFoliageIndicesMap(const FManagedArrayCollection& Collection);`
- L186 _private prototype_ `static FMeshPointUVData ComputePointUVData(int32 PointIndex, int32 BranchPointIndex, bool bPrimitiveIsTrunk, const TArray<int32>& PrimitivePoints, const PV::Facades::FPointFacade& PointFacade, const TManagedArray<FVector3f>& PointPositions, float PointScale);`
- L190 _private prototype_ `static void GenerateBranchMeshData(const bool bPrimitiveIsTrunk, const int32 GenerationNumber, int32 BranchIndex, const TArray<int32>& PrimitivePoints, const FDisplacementData& DisplacementData, const FPVMeshBuilderParams& MeshBuilderParams, const TArray<int32>& TargetMeshDivisions, const FManagedArrayCollection& Collection, const FManagedArrayCollection& InPlantProfileCollection, FLocalDynamicMeshData& OutLocalMeshData);`
- L195 _private prototype_ `static void UpdateFoliagePivotPoints(const TSet<int32>& PointsToRemove, FManagedArrayCollection& OutCollection);`
- L197 _private prototype_ `static void GetLocalDynamicMeshData(FManagedArrayCollection& Collection, const FManagedArrayCollection& InPlantProfileCollection, const FPVMeshBuilderParams& MeshBuilderParams, TArray<FLocalDynamicMeshData>& MeshesData);`
- L200 _private prototype_ `static void ApplyDaVinciRule(FManagedArrayCollection& OutCollection, const FPVMeshBuilderParams& MeshBuilderParams);`
- L202 _private prototype_ `static void ApplyBranchGenerationRamps(FManagedArrayCollection& OutCollection, const FPVMeshBuilderParams& MeshBuilderParams);`
- L204 _private prototype_ `static void ApplyBranchGenerationScales(FManagedArrayCollection& OutCollection, const FPVMeshBuilderParams& MeshBuilderParams);`
- L206 _private prototype_ `static void ApplyMinRadius(FManagedArrayCollection& OutCollection, const FPVMeshBuilderParams& MeshBuilderParams);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVObjectInteraction.h` (Private)


#### struct `FPVObjectInteraction`  
`struct FPVObjectInteraction`  
_L9-18_
- L11 _public prototype_ `static FVector GetTriangleNormal( FMeshDescriptionTriangleMeshAdapter& Mesh, const int32 TID, TOptional<FVector> BaryCoords = TOptional<FVector>() );`
- L17 _public prototype_ `static void ObjectInteraction(FManagedArrayCollection& OutCollection, FPVColliderParams Collider);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVRecomputePointScale.h` (Private)


#### struct `PV::FComputePointScales_SmoothTaperAttributes`  
`struct FComputePointScales_SmoothTaperAttributes`  
_L13-59_
- L15 _public member_ `PV::FPointScaleAttributeView PointScale;`
- L16 _public member_ `PV::FPointLengthFromRootAttributeConstView PointLengthFromRoot;`
- L17 _public member_ `PV::FBranchPointsAttributeConstView BranchPoints;`
- L18 _public member_ `PV::FBranchParentNumberAttributeConstView BranchParentNumber;`
- L19 _public member_ `PV::FBranchChildrenAttributeConstView BranchChildren;`
- L20 _public member_ `PV::FBranchNumberAttributeConstView BranchNumber;`
- L22 _public function_ `FComputePointScales_SmoothTaperAttributes( PV::FPointScaleAttributeView InPointScale, PV::FPointLengthFromRootAttributeConstView InPointLengthFromRoot, PV::FBranchPointsAttributeConstView InBranchPoints, PV::FBranchParentNumberAttributeConstView InBranchParentNumber, PV::FBranchChildrenAttributeConstView InBranchChildren, PV::FBranchNumberAttributeConstView InBranchNumber) : PointScale(InPointScale) , PointLengthFromRoot(InPointLengthFromRoot) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber) , BranchChildren(InBranchChildren) , BranchNumber(InBranchNumber)`
- L38 _public function_ `FComputePointScales_SmoothTaperAttributes(FManagedArrayCollection& InCollection) : PointScale(PV::FPointScaleAttribute::FindAttribute(InCollection)) , PointLengthFromRoot(PV::FPointLengthFromRootAttribute::FindAttribute(InCollection)) , BranchPoints(PV::FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(PV::FBranchParentNumberAttribute::FindAttribute(InCollection)) , BranchChildren(PV::FBranchChildrenAttribute::FindAttribute(InCollection)) , BranchNumber(PV::FBranchNumberAttribute::FindAttribute(InCollection))`
- L48 _public function_ `bool IsValid() const`

#### struct `PV::FComputePointScales_UserTrunkScaleAttributes`  
`struct FComputePointScales_UserTrunkScaleAttributes`  
_L69-93_
- L71 _public member_ `FPointScaleAttributeView PointScale;`
- L72 _public member_ `FPointPlantGradientAttributeConstView PlantGradient;`
- L74 _public function_ `FComputePointScales_UserTrunkScaleAttributes( FPointScaleAttributeView InPointScale, FPointPlantGradientAttributeConstView InPlantGradient) : PointScale(InPointScale) , PlantGradient(InPlantGradient)`
- L81 _public function_ `FComputePointScales_UserTrunkScaleAttributes(FManagedArrayCollection& InCollection) : PointScale(FPointScaleAttribute::FindAttribute(InCollection)) , PlantGradient(FPointPlantGradientAttribute::FindAttribute(InCollection))`
- L86 _public function_ `bool IsValid() const`

#### struct `PV::FComputePointScales_MaxScaleAsTrunkScale`  
`struct FComputePointScales_MaxScaleAsTrunkScale`  
_L103-144_
- L105 _public member_ `FPointScaleAttributeView PointScale;`
- L106 _public member_ `FPointPlantGradientAttributeConstView PlantGradient;`
- L107 _public member_ `FBranchPlantNumberAttributeConstView BranchPlantNumber;`
- L108 _public member_ `FBranchPointsAttributeConstView BranchPoints;`
- L109 _public member_ `FBranchParentNumberAttributeConstView BranchParentNumber;`
- L111 _public function_ `FComputePointScales_MaxScaleAsTrunkScale( FPointScaleAttributeView InPointScale, FPointPlantGradientAttributeConstView InPlantGradient, FBranchPlantNumberAttributeConstView InBranchPlantNumber, FBranchPointsAttributeConstView InBranchPoints, FBranchParentNumberAttributeConstView InBranchParentNumber) : PointScale(InPointScale) , PlantGradient(InPlantGradient) , BranchPlantNumber(InBranchPlantNumber) , BranchPoints(InBranchPoints) , BranchParentNumber(InBranchParentNumber)`
- L125 _public function_ `FComputePointScales_MaxScaleAsTrunkScale(FManagedArrayCollection& InCollection) : PointScale(FPointScaleAttribute::FindAttribute(InCollection)) , PlantGradient(FPointPlantGradientAttribute::FindAttribute(InCollection)) , BranchPlantNumber(FBranchPlantNumberAttribute::FindAttribute(InCollection)) , BranchPoints(FBranchPointsAttribute::FindAttribute(InCollection)) , BranchParentNumber(FBranchParentNumberAttribute::FindAttribute(InCollection))`
- L134 _public function_ `bool IsValid() const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L64 _prototype_ `void ComputePointScales_SmoothTaper( const FComputePointScales_SmoothTaperAttributes& InAttributes, float MaxTaperRateMultiplier = 3.0f );` (scope `PV`) — Smooths the existing point scales across the branch hierarchy and writes the results back to the PointScale attribute. Expects the PointScale attribute to already contain valid scale values prior to calling this function. MaxTaperRateMultiplier controls how aggressively anomalous values are rejected: lower = stricter smoothing.
- L97 _prototype_ `void ComputePointScales_UserTrunkScale( const FComputePointScales_UserTrunkScaleAttributes& InAttributes, float TrunkScale, const FRichCurve* TaperProfile );` (scope `PV`) — Sets each point's scale to TaperProfile(PlantGradient) * TrunkScale, where TaperProfile is evaluated at each point's PlantGradient to shape the taper. If TaperProfile is null, falls back to PlantGradient * TrunkScale.
- L148 _prototype_ `void ComputePointScales_MaxScaleAsTrunkScale( const FComputePointScales_MaxScaleAsTrunkScale& InAttributes, float ScaleMultiplier, const FRichCurve* TaperProfile );` (scope `PV`) — Sets each point's scale to TaperProfile(PlantGradient) * (MaxPointScale * ScaleMultiplier), where MaxPointScale is the largest existing scale on the same plant. If TaperProfile is null, falls back to PlantGradient * (MaxPointScale * ScaleMultiplier).

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVRemoveBranches.h` (Private)


#### enum `ERemoveBranchesBasis`  
`enum class ERemoveBranchesBasis : uint8`  
_L11-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `Length`
- L14 _public enumerator_ `Radius`
- L15 _public enumerator_ `Light`
- L16 _public enumerator_ `Age`
- L17 _public enumerator_ `Generation`

#### struct `FPVRemoveBranches`  
`struct FPVRemoveBranches`  
_L20-23_
- L22 _public prototype_ `static void ApplyRemoveBranches(const ERemoveBranchesBasis InBasis, const float InThreshold, FManagedArrayCollection& OutCollection);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVRotateBranches.h` (Private)


#### enum `EPVGradientBlendMode`  
`enum class EPVGradientBlendMode : uint8`  
_L11-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `Multiply`
- L14 _public enumerator_ `Add`
- L15 _public enumerator_ `Min`
- L16 _public enumerator_ `Max`
- L17 _public enumerator_ `Lerp`

#### struct `FPVRotateBranchesParams`  
`struct FPVRotateBranchesParams`  
_L21-60_
- reflection: `USTRUCT()`
- L26 _public member_ `float Rotation = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (Units = Degrees, ClampMin = -180.0f, ClampMax = 180.0f, UIMin = -180.0f, UIMax = 180.0f, Tooltip="Base rotation angle applied to each branch in degrees.\n\nPositive = counter-clockwise around the parent axis (right-hand rule). Negative = clockwise. The actual per-branch rotation may be modified by ramps and randomness."))`
- L29 _public member_ `int32 StartGeneration = 1;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = 1, UIMin = 1, UIMax = 20, Tooltip="First branch generation to receive the rotation.\n\n1 = trunk (no-op since the trunk has no parent). 2 = first lateral branches. Higher numbers skip lower-order branches entirely. Use to apply rotation only to twigs or only to main branches."))`
- L32 _public member_ `int32 NumGenerations = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = 0, UIMin = 0, UIMax = 20, Tooltip="How many generations from StartGeneration to affect (0 = unlimited).\n\n0 = all generations from StartGeneration onward. 1 = only the StartGeneration tier. Use to limit the rotation's depth — e.g. rotate only first-order side branches without touching their children."))`
- L35 _public member_ `FPVFloatRamp PlantGradientMultiplier;` — `UPROPERTY(EditAnywhere, Category="Settings", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=-1.0f, YAxisMax=1.0f, Tooltip="Scales rotation amount based on branch position along the whole plant.\n\nX = plant gradient (0 = root, 1 = tip). Y = rotation multiplier from -1 to 1. Use to reverse rotation direction in different plant zones, or to suppress rotation near the base."))`
- L38 _public member_ `FPVFloatRamp BranchGradientMultiplier;` — `UPROPERTY(EditAnywhere, Category="Settings", meta=(XAxisMin=0.0f, XAxisMax=1.0f, YAxisMin=-1.0f, YAxisMax=1.0f, Tooltip="Scales rotation amount based on branch position along its parent.\n\nX = branch gradient (0 = branch root, 1 = branch tip). Y = rotation multiplier. Use to fade rotation in or out along each branch."))`
- L41 _public member_ `EPVGradientBlendMode GradientBlendMode = EPVGradientBlendMode::Lerp;` — `UPROPERTY(EditAnywhere, Category="Settings", meta=(Tooltip="How the plant and branch gradient multipliers combine.\n\nMultiply / Add / Min / Max / Lerp. Lerp blends them by 'BranchGradientBias'."))`
- L44 _public member_ `float BranchGradientBias = 0.f;` — `UPROPERTY(EditAnywhere, Category="Settings", meta=(ClampMin=0, ClampMax=1, UIMin=0, UIMax=1, EditCondition="GradientBlendMode==EPVGradientBlendMode::Lerp", EditConditionHides, Tooltip="Lerp blend between plant gradient (0) and branch gradient (1).\n\n0 = use only the plant gradient. 1 = use only the branch gradient. 0.5 = equal mix."))`
- L47 _public member_ `bool bAlternatingRotations = true;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(Tooltip="Alternate rotation direction between successive axillary branches.\n\nWhen on, branches alternate +angle, -angle, +angle, -angle as you walk along the parent. Turn off for uniform same-direction twist."))`
- L50 _public member_ `float Randomness = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = 0, ClampMax = 1, UIMin = 0, UIMax = 1, Tooltip="Random variation added to each branch's rotation.\n\n0 = perfectly uniform rotation. 1 = full random offset. Use to break perfect symmetry and create natural-looking variation."))`
- L53 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "Settings", meta=(Tooltip="Seed for the random rotation offsets.\n\nChange to get a different random pattern without changing the strength."))`
- L55 _public function_ `FPVRotateBranchesParams()`

#### struct `FPVRotateBranches`  
`struct FPVRotateBranches`  
_L62-65_
- L64 _public prototype_ `static void ApplyRotateBranches(const FPVRotateBranchesParams& InRotateBranchesParams, FManagedArrayCollection& OutCollection);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVScale.h` (Private)


#### struct `FPVScale`  
`struct FPVScale`  
_L8-12_
- L11 _public prototype_ `static void ApplyScale(const float InManualScale, FManagedArrayCollection& OutCollection);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVSeedGenerator.h` (Private)


#### struct `FPVSeedPoint`  
`struct FPVSeedPoint`  
_L11-63_
- reflection: `USTRUCT()`
- L17 _public member_ `FVector Position = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L20 _public member_ `FVector ApicalDirection = FVector::UpVector;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L23 _public member_ `FVector AxillaryDirection = FVector::ForwardVector;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L26 _public member_ `uint32 BranchNumber = 1;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L29 _public member_ `float LengthFromRoot = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L32 _public member_ `uint32 PlantNumber = 1;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L35 _public member_ `uint32 SeedBranchParentNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L38 _public member_ `uint32 SeedBranchSourceBudNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L41 _public member_ `uint32 SeedGeneration = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L44 _public member_ `uint32 SeedMaxBranchNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L47 _public member_ `uint32 SeedMaxBudNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L50 _public member_ `uint32 SeedPlantNumber = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L53 _public member_ `float SeedPScale = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L56 _public member_ `float SeedPScaleRatio = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L59 _public member_ `uint32 SeedType = 0;` — `UPROPERTY(EditAnywhere, Category = "Seed")`
- L62 _public member_ `FVector UpVector = FVector::RightVector;` — `UPROPERTY(EditAnywhere, Category = "Seed")`

#### class `UPVSeedGenerator`  
`class UPVSeedGenerator : public UObject`  
_L66-76_
- reflection: `UCLASS()`
- inherits: `UObject`
- L71 _public function_ `const FPVSeedPoint& GetSeedPoint() const`
- L75 _private member_ `FPVSeedPoint SeedPoint;` — `UPROPERTY(EditAnywhere, Category = "Seed")`

#### struct `FPVConvertToSeedPointParams`  
`struct FPVConvertToSeedPointParams`  
_L79-97_
- reflection: `USTRUCT()`
- L84 _public member_ `float Avoidance = 0;` — `UPROPERTY(EditAnywhere, Category = AvoidanceSettings , meta = (UIMin = "0.0", UIMax = "1.0", Tooltip="Strength of the avoidance bend applied to each seed's initial growth direction.\n\n0 = seeds grow straight up regardless of position. Higher values bend each seed's initial direction away from a reference. Use AvoidanceBias to choose whether the reference is the cluster center or nearby seeds."))`
- L87 _public member_ `float AvoidanceBias = 0;` — `UPROPERTY(EditAnywhere, Category = AvoidanceSettings, meta = (UIMin = "0.0", UIMax = "1.0", Tooltip="Mix between avoiding the cluster center (0) and avoiding neighbors (1).\n\n0 = seeds bend away from the cluster center. 1 = seeds bend away from nearby seeds. 0.5 = equal mix."))`
- L90 _public member_ `float AvoidanceCenterReduction = 0;` — `UPROPERTY(EditAnywhere, Category = AvoidanceSettings, meta = (UIMin = "0.0", UIMax = "1.0", Tooltip="Taper the avoidance bend so central seeds bend less than outer seeds.\n\n0 = all seeds bend equally regardless of position. 1 = central seeds grow closer to straight up, outer seeds bend fully toward the avoidance direction. Tapers smoothly from 0 at the cluster center to 1 at the outermost seed."))`
- L93 _public member_ `float ApicalRandom = 0;` — `UPROPERTY(VisibleAnywhere, Category = AvoidanceSettings, meta = (UIMin = "0.0", UIMax = "360.0", Tooltip="Auto-computed random apical direction range applied to each seed (degrees)."))`
- L96 _public member_ `float AxillaryRandom = 0;` — `UPROPERTY(VisibleAnywhere, Category = AvoidanceSettings, meta = (UIMin = "0.0", UIMax = "360.0", Tooltip="Auto-computed random axillary direction range applied to each seed (degrees)."))`

#### struct `FPVConvertToSeedPointImplementation`  
`struct FPVConvertToSeedPointImplementation`  
_L99-106_
- L101 _public prototype_ `static TArray<FTransform> FindNeighbours(const FTransform& InTransform, const UPCGPointData* PointData, float MaxDist, int MaxPoints);`
- L103 _public prototype_ `static void SetBaseDirection(const UPCGPointData* PointData, const FPVConvertToSeedPointParams& Params, TArray<TArray<FVector3f>>& DirectionArray, int PrimaryAxis = 0);`
- L105 _public prototype_ `static void FillCollection(FManagedArrayCollection& Collection, const FPVConvertToSeedPointParams& Params, const UPCGPointData* SeedPoints);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVSimplifyPlantSkeleton.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PV`
- L10 _prototype_ `extern void SimplifyPlantSkeleton(FManagedArrayCollection& InOutCollection, float SimplificationAmount);` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVSlope.h` (Private)


#### enum `EPVSlopeTrunkPivotPoint`  
`enum class EPVSlopeTrunkPivotPoint`  
_L16-20_
- reflection: `UENUM()`
- L18 _public enumerator_ `Origin`
- L19 _public enumerator_ `Trunk`

#### struct `FPVSlopeParams`  
`struct FPVSlopeParams`  
_L23-38_
- reflection: `USTRUCT()`
- L28 _public member_ `float SlopeAngle = 0;` — `UPROPERTY(EditAnywhere, Category = "Slope", meta = (Units = Degrees, ClampMin = -90.0f, ClampMax = 90.0f, UIMin = -90.0f, UIMax = 90.0f, Tooltip="Slope angle in degrees (positive = uphill, negative = downhill).\n\nThe angle of the ground the plant is growing on. 0 = flat. Positive = sloping up in the slope direction. Negative = sloping down."))`
- L31 _public member_ `float SlopeDirection = 0;` — `UPROPERTY(EditAnywhere, Category = "Slope", meta = (Units = Degrees, ClampMin = -180.0f, ClampMax = 180.0f, UIMin = -180.0f, UIMax = 180.0f, Tooltip="Compass direction of the slope's downhill side.\n\nHeading angle of the slope's downhill direction in degrees. 0 = north, 90 = east, -90 = west, ±180 = south."))`
- L34 _public member_ `float BendStrength = 2.0;` — `UPROPERTY(EditAnywhere, Category = "Slope", meta = (ClampMin = 0.0f, ClampMax = 100.0f, UIMin = 0.0f, UIMax = 10.0f, Tooltip="How strongly the plant bends back toward vertical as it grows.\n\n0 = no bending (plant grows perpendicular to slope and stays angled). Higher values = aggressive uprighting."))`
- L37 _public member_ `EPVSlopeTrunkPivotPoint TrunkPivotPoint = EPVSlopeTrunkPivotPoint::Origin;` — `UPROPERTY(EditAnywhere, Category = "Slope", meta=(Tooltip="Rotate around world origin or plant base (useful with multi seed plants)\n\n'Origin' = Pivot the ground rotation around the world origin. 'Trunk' = Pivot the ground rotation around the plant base (does not move plant base)."))`

#### struct `FPVSlope`  
`struct FPVSlope`  
_L40-43_
- L42 _public prototype_ `static void ApplySlope(const FPVSlopeParams& InSlopeParams, FManagedArrayCollection& OutCollection);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PV`
- L9 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVTrunkTextureSetup.h` (Private)


#### struct `FPVTrunkTextureSetupImplementation`  
`struct FPVTrunkTextureSetupImplementation`  
_L16-38_
- L18 _public prototype_ `static TArray<FString> GetChannels(const TArray<FPVTextureGenerationParams>& Array);`
- L19 _public prototype_ `static UTexture* CreateTexture(int Width, int Height, bool bCanCreateUAV, FName Name);`
- L20 _public prototype_ `static TMap<FString, TObjectPtr<UTexture>> CreateTextures(int32 Resolution, const TArray<FString>& ChannelNames, const FString& AssetNamePrefix, bool bVirtualTextureStreaming);`
- L21 _public prototype_ `static FRHITexture* GetRHITexture(UTexture* Texture);`
- L22 _public prototype_ `static FRDGTextureSRVRef GetTextureSRVRef(FRDGBuilder& GraphBuilder, UTexture* InputTexture, const TCHAR* Name);`
- L23 _public prototype_ `static FRDGTextureUAVRef GetTextureUAVRef(FRDGBuilder& GraphBuilder, UTexture* Texture, const TCHAR* Name);`
- L25 _public prototype_ `static void DilationPass(FRDGBuilder& GraphBuilder, float DilationFactor, float TileX, float TileY, UTexture* InputTexture, UTexture* OutputTexture);`
- L26 _public prototype_ `static void ScaleAndCombineTexturePass(FRDGBuilder& GraphBuilder, UTexture* TargetTexture, UTexture* InputTexture, const float WidthRatio, const float OffsetX, const FPVTextureGenerationParams& Generation);`
- L28 _public prototype_ `static void AddChannelTextureToTextureSet(const float InOffsetX, const FPVTextureGenerationParams& Generation, const FPVTextureChannelParams& Channel, UTexture* Texture);`
- L29 _public prototype_ `static void AddGenerationIntoChannel(const FString& ChannelName, UTexture* Texture, const FPVTrunkTextureSetupParams& Params);`
- L30 _public prototype_ `static void AddGenerationIntoChannel(const TMap<FString, TObjectPtr<UTexture>>& Map, const FPVTrunkTextureSetupParams& Params);`
- L32 _public prototype_ `static FString NormalizeString(FString InString);`
- L33 _public prototype_ `static EPVTextureChannel GetTextureChannelFromString(const FString& InString);`
- L34 _public prototype_ `static TObjectPtr<UTexture> GetChannelTextureForMaterialParam(FPVTrunkTextureSetupInfo& TrunkTextureSetupInfo, FString MaterialParamName);`
- L35 _public prototype_ `static void SetupMaterial(TObjectPtr<UMaterialInterface> Material, FPVTrunkTextureSetupInfo& TrunkTextureSetupInfo);`
- L36 _public prototype_ `static void CreateTrimSheetTexture( FPVTrunkTextureSetupParams& Params, FPVTrunkTextureSetupInfo& TrunkTextureSetupInfo);`
- L37 _public prototype_ `static UTexture2D* ConvertRenderTargetToTexture2D(UTextureRenderTarget2D* InRenderTarget, const FString& Path, FString& OutError);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Implementations/PVTrunkTextureSetupCS.h` (Private)


#### class `FPVTrunkTextureSetupDilationCS`  
`class FPVTrunkTextureSetupDilationCS : public FGlobalShader`  
_L9-24_
- inherits: `FGlobalShader`
- L11 _private prototype_ `DECLARE_GLOBAL_SHADER(FPVTrunkTextureSetupDilationCS);`
- L12 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FPVTrunkTextureSetupDilationCS, FGlobalShader);`

#### class `FPVTrunkTextureSetupScaleCS`  
`class FPVTrunkTextureSetupScaleCS : public FGlobalShader`  
_L26-41_
- inherits: `FGlobalShader`
- L28 _private prototype_ `DECLARE_GLOBAL_SHADER(FPVTrunkTextureSetupScaleCS);`
- L29 _private prototype_ `SHADER_USE_PARAMETER_STRUCT(FPVTrunkTextureSetupScaleCS, FGlobalShader);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/Development/PVGrowthDataDiffSettings.h` (Private)


#### class `UPVGrowthDataDiffSettings`  
`class UPVGrowthDataDiffSettings : public UPVBaseSettings`  
_L11-33_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public prototype_ `UPVGrowthDataDiffSettings();`
- L19 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L25 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L30 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L31 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L32 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `FPVGrowthDataDiffElement`  
`class FPVGrowthDataDiffElement : public FPVBaseElement`  
_L35-39_
- inherits: `FPVBaseElement`
- L38 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/Development/PVGrowthDataJsonImporterSettings.h` (Private)


#### class `UPVGrowthDataJsonImporterSettings`  
`class UPVGrowthDataJsonImporterSettings : public UPVBaseSettings`  
_L11-36_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public prototype_ `UPVGrowthDataJsonImporterSettings();`
- L19 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L25 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L30 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L31 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L35 _public member_ `FFilePath GrowthDataFile;` — `UPROPERTY(EditAnywhere, Category = "Growth Data")`

#### class `FPVGrowthDataJsonImporterElement`  
`class FPVGrowthDataJsonImporterElement : public FPVBaseElement`  
_L38-42_
- inherits: `FPVBaseElement`
- L41 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/Development/PVMockTreeImporterSettings.h` (Private)


#### class `UPVMockTreeImporterSettings`  
`class UPVMockTreeImporterSettings : public UPVBaseSettings`  
_L11-32_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public prototype_ `UPVMockTreeImporterSettings();`
- L19 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L25 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L30 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L31 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `FPVMockTreeImporterElement`  
`class FPVMockTreeImporterElement : public FPVBaseElement`  
_L34-38_
- inherits: `FPVBaseElement`
- L37 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/Development/PVRecomputeGrowthDataAttributesSettings.h` (Private)


#### class `UPVRecomputeGrowthDataAttributesSettings`  
`class UPVRecomputeGrowthDataAttributesSettings : public UPVBaseSettings`  
_L11-32_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public prototype_ `UPVRecomputeGrowthDataAttributesSettings();`
- L19 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L25 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L30 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L31 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `FPVRecomputeGrowthDataAttributesElement`  
`class FPVRecomputeGrowthDataAttributesElement : public FPVBaseElement`  
_L34-38_
- inherits: `FPVBaseElement`
- L37 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/DistributionSettings/PVDistributionBaseSettings.h` (Private)


#### class `UPVDistributionBaseSettings`  
`class UPVDistributionBaseSettings : public UPVBaseSettings`  
_L9-19_
- reflection: `UCLASS(BlueprintType, Abstract, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L15 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L16 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L17 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/DistributionSettings/PVDistributionConditionSettings.h` (Private)


#### class `UPVDistributionConditionSettings`  
`class UPVDistributionConditionSettings : public UPVDistributionBaseSettings`  
_L10-28_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVDistributionBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L22 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L23 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L27 _public member_ `FPVDistributionConditionParams Params;` — `UPROPERTY(EditAnywhere, Category = "Condition Settings", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVDistributionConditionElement`  
`class FPVDistributionConditionElement : public FPVBaseElement`  
_L30-34_
- inherits: `FPVBaseElement`
- L33 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/DistributionSettings/PVDistributionHormoneBasedSettings.h` (Private)


#### class `UPVDistributionHormoneBasedSettings`  
`class UPVDistributionHormoneBasedSettings : public UPVDistributionBaseSettings`  
_L10-28_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVDistributionBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L22 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L23 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L27 _public member_ `FPVDistributionHormoneBasedParams Params;` — `UPROPERTY(EditAnywhere, Category = "Hormone Based Settings", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVDistributionHormoneBasedElement`  
`class FPVDistributionHormoneBasedElement : public FPVBaseElement`  
_L30-34_
- inherits: `FPVBaseElement`
- L33 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/DistributionSettings/PVDistributionParametricSettings.h` (Private)


#### class `UPVDistributionParametricSettings`  
`class UPVDistributionParametricSettings : public UPVDistributionBaseSettings`  
_L10-28_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVDistributionBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L22 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L23 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L27 _public member_ `FPVDistributionParametricParams Params;` — `UPROPERTY(EditAnywhere, Category = "Parametric Settings", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVDistributionParametricElement`  
`class FPVDistributionParametricElement : public FPVBaseElement`  
_L30-34_
- inherits: `FPVBaseElement`
- L33 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/DistributionSettings/PVDistributionVectorSettings.h` (Private)


#### class `UPVDistributionVectorSettings`  
`class UPVDistributionVectorSettings : public UPVDistributionBaseSettings`  
_L10-28_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVDistributionBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected function_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override`
- L22 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L23 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L27 _public member_ `FPVDistributionVectorParams Params;` — `UPROPERTY(EditAnywhere, Category = "Vector Settings", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVDistributionVectorElement`  
`class FPVDistributionVectorElement : public FPVBaseElement`  
_L30-34_
- inherits: `FPVBaseElement`
- L33 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerAgeSenescenceSettings.h` (Private)


#### class `UPVGrowerAgeSenescenceSettings`  
`class UPVGrowerAgeSenescenceSettings : public UPVGrowerBaseSettings`  
_L12-29_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L18 _public function_ `virtual FName GetDefaultNodeName() const override`
- L19 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L28 _public member_ `FPVAgeSenescenceParams Params;` — `UPROPERTY(EditAnywhere, Category="AgeSenescence", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVAgeSenescenceElement`  
`class FPVAgeSenescenceElement : public FPVBaseElement`  
_L31-35_
- inherits: `FPVBaseElement`
- L34 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerAuxinSettings.h` (Private)


#### class `UPVGrowerAuxinSettings`  
`class UPVGrowerAuxinSettings : public UPVGrowerBaseSettings`  
_L10-29_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L28 _public member_ `FPVGrowerAuxinWithTargets ParamsWithTargets;` — `UPROPERTY(EditAnywhere, Category="AuxinSettings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerAuxinElement`  
`class FPVGrowerAuxinElement : public FPVBaseElement`  
_L31-35_
- inherits: `FPVBaseElement`
- L34 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerBaseSettings.h` (Private)


#### class `UPVGrowerBaseSettings`  
`class UPVGrowerBaseSettings : public UPVBaseSettings`  
_L9-24_
- reflection: `UCLASS(BlueprintType, Abstract, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L15 _public function_ `virtual FName GetDefaultNodeName() const override`
- L16 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L17 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L18 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L19 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L23 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerBifurcationSettings.h` (Private)


#### class `UPVGrowerBifurcationSettings`  
`class UPVGrowerBifurcationSettings : public UPVGrowerBaseSettings`  
_L10-29_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L28 _public member_ `FPVGrowerBifurcationWithTargets ParamsWithTargets;` — `UPROPERTY(EditAnywhere, Category="BifurcationSettings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerBifurcationElement`  
`class FPVGrowerBifurcationElement : public FPVBaseElement`  
_L31-35_
- inherits: `FPVBaseElement`
- L34 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerDirectionalSettings.h` (Private)


#### class `UPVGrowerDirectionalSettings`  
`class UPVGrowerDirectionalSettings : public UPVGrowerBaseSettings`  
_L10-30_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L29 _public member_ `FPVGrowerDirectionalWithTargets ParamsWithTargets;` — `UPROPERTY(EditAnywhere, Category="DirectionalSettings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerDirectionalElement`  
`class FPVGrowerDirectionalElement : public FPVBaseElement`  
_L32-36_
- inherits: `FPVBaseElement`
- L35 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerFoliageSettings.h` (Private)


#### class `UPVGrowerFoliageSettings`  
`class UPVGrowerFoliageSettings : public UPVGrowerBaseSettings`  
_L12-34_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L18 _public function_ `virtual FName GetDefaultNodeName() const override`
- L19 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L26 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L27 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L28 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L33 _public member_ `FPVFoliageParams Params;` — `UPROPERTY(EditAnywhere, Category="Foliage Settings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerFoliageElement`  
`class FPVGrowerFoliageElement : public FPVBaseElement`  
_L36-40_
- inherits: `FPVBaseElement`
- L39 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerGravitySettings.h` (Private)


#### class `UPVGrowerGravitySettings`  
`class UPVGrowerGravitySettings : public UPVGrowerBaseSettings`  
_L11-28_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L17 _public function_ `virtual FName GetDefaultNodeName() const override`
- L18 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L22 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L23 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L27 _public member_ `FPVGrowerGravityParams Params;` — `UPROPERTY(EditAnywhere, Category="GravitySetttings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerGravityElement`  
`class FPVGrowerGravityElement : public FPVBaseElement`  
_L30-34_
- inherits: `FPVBaseElement`
- L33 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerLightSenescenceSettings.h` (Private)


#### class `UPVGrowerLightSenescenceSettings`  
`class UPVGrowerLightSenescenceSettings : public UPVGrowerBaseSettings`  
_L12-29_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L18 _public function_ `virtual FName GetDefaultNodeName() const override`
- L19 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L28 _public member_ `FPVLightSenescenceParams Params;` — `UPROPERTY(EditAnywhere, Category="LightSenescence", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVLightSenescenceElement`  
`class FPVLightSenescenceElement : public FPVBaseElement`  
_L31-35_
- inherits: `FPVBaseElement`
- L34 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerPhototropismSettings.h` (Private)


#### class `UPVGrowerPhototropismSettings`  
`class UPVGrowerPhototropismSettings : public UPVGrowerBaseSettings`  
_L10-30_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L29 _public member_ `FPVGrowerPhototropismWithTargets ParamsWithTargets;` — `UPROPERTY(EditAnywhere, Category="PhototropismSettings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerPhototropismElement`  
`class FPVGrowerPhototropismElement : public FPVBaseElement`  
_L32-36_
- inherits: `FPVBaseElement`
- L35 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerPhyllotaxySettings.h` (Private)


#### class `UPVGrowerPhyllotaxySettings`  
`class UPVGrowerPhyllotaxySettings : public UPVGrowerBaseSettings`  
_L10-29_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L28 _public member_ `FPVGrowerPhyllotaxyWithTargets ParamsWithTargets;` — `UPROPERTY(EditAnywhere, Category="PhyllotaxySettings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerPhyllotaxyElement`  
`class FPVGrowerPhyllotaxyElement : public FPVBaseElement`  
_L31-35_
- inherits: `FPVBaseElement`
- L34 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/GrowerSettings/PVGrowerTrunkGrowthSettings.h` (Private)


#### class `UPVGrowerTrunkGrowthSettings`  
`class UPVGrowerTrunkGrowthSettings : public UPVGrowerBaseSettings`  
_L10-28_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVGrowerBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L22 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L27 _public member_ `FPVTrunkGrowthParams Params;` — `UPROPERTY(EditAnywhere, Category="TrunkGrowthSettings", meta=(ShowOnlyInnerProperties, PCG_Overridable, InnerCategoryToggle))`

#### class `FPVGrowerTrunkGrowthElement`  
`class FPVGrowerTrunkGrowthElement : public FPVBaseElement`  
_L30-34_
- inherits: `FPVBaseElement`
- L33 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/MesherSettings/PVMeshBuilderBaseSettings.h` (Private)


#### class `UPVMeshBuilderBaseSettings`  
`class UPVMeshBuilderBaseSettings : public UPVBaseSettings`  
_L9-24_
- reflection: `UCLASS(BlueprintType, Abstract, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L15 _public function_ `virtual FName GetDefaultNodeName() const override`
- L16 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L17 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L18 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L19 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L23 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/MesherSettings/PVMeshBuilderBranchRadiusSettings.h` (Private)


#### class `UPVMeshBuilderBranchRadiusSettings`  
`class UPVMeshBuilderBranchRadiusSettings : public UPVMeshBuilderBaseSettings`  
_L10-27_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVMeshBuilderBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L22 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L26 _public member_ `FPVMeshBuilderBranchRadiusParams Params;` — `UPROPERTY(EditAnywhere, Category = "Branch Radius", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVMeshBuilderBranchRadiusSettingsElement`  
`class FPVMeshBuilderBranchRadiusSettingsElement : public FPVBaseElement`  
_L29-33_
- inherits: `FPVBaseElement`
- L32 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/MesherSettings/PVMeshBuilderDisplacementSettings.h` (Private)


#### class `UPVMeshBuilderDisplacementSettings`  
`class UPVMeshBuilderDisplacementSettings : public UPVMeshBuilderBaseSettings`  
_L10-36_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVMeshBuilderBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L18 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L19 _public prototype_ `virtual void PostLoad() override;`
- L23 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L24 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L28 _public member_ `FPVMeshBuilderDisplacementParams Params;` — `UPROPERTY(EditAnywhere, Category = "Displacement", meta = (ShowOnlyInnerProperties, PCG_Overridable))`
- L32 _public member_ `TArray<float> CachedValues;` — `UPROPERTY(Transient, NonTransactional)` — Cached pixel values extracted from Params.Texture; populated in PostEditChangeProperty / PostLoad.
- L35 _public member_ `FString DisplacementWarnings;` — `UPROPERTY()`

#### class `FPVMeshBuilderDisplacementSettingsElement`  
`class FPVMeshBuilderDisplacementSettingsElement : public FPVBaseElement`  
_L38-42_
- inherits: `FPVBaseElement`
- L41 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/MesherSettings/PVMeshBuilderMaterialDetailSettings.h` (Private)


#### class `UPVMeshBuilderMaterialDetailSettings`  
`class UPVMeshBuilderMaterialDetailSettings : public UPVMeshBuilderBaseSettings`  
_L10-27_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVMeshBuilderBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L22 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L26 _public member_ `FPVMaterialSettings Params;` — `UPROPERTY(EditAnywhere, Category = "Material Details", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVMeshBuilderMaterialDetailSettingsElement`  
`class FPVMeshBuilderMaterialDetailSettingsElement : public FPVBaseElement`  
_L29-33_
- inherits: `FPVBaseElement`
- L32 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/MesherSettings/PVMeshBuilderMeshDetailSettings.h` (Private)


#### class `UPVMeshBuilderMeshDetailSettings`  
`class UPVMeshBuilderMeshDetailSettings : public UPVMeshBuilderBaseSettings`  
_L10-27_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVMeshBuilderBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L22 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L26 _public member_ `FPVMeshBuilderMeshDetailParams Params;` — `UPROPERTY(EditAnywhere, Category = "Mesh Details", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVMeshBuilderMeshDetailSettingsElement`  
`class FPVMeshBuilderMeshDetailSettingsElement : public FPVBaseElement`  
_L29-33_
- inherits: `FPVBaseElement`
- L32 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/MesherSettings/PVMeshBuilderProfileDetailSettings.h` (Private)


#### class `UPVMeshBuilderProfileDetailSettings`  
`class UPVMeshBuilderProfileDetailSettings : public UPVMeshBuilderBaseSettings`  
_L10-27_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVMeshBuilderBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L22 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L26 _public member_ `FPVMeshBuilderProfileDetailParams Params;` — `UPROPERTY(EditAnywhere, Category = "Profile Details", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVMeshBuilderProfileDetailSettingsElement`  
`class FPVMeshBuilderProfileDetailSettingsElement : public FPVBaseElement`  
_L29-33_
- inherits: `FPVBaseElement`
- L32 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/MesherSettings/PVMeshBuilderSkeletonShapingSettings.h` (Private)


#### class `UPVMeshBuilderSkeletonShapingSettings`  
`class UPVMeshBuilderSkeletonShapingSettings : public UPVMeshBuilderBaseSettings`  
_L10-27_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVMeshBuilderBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L22 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L26 _public member_ `FPVMeshBuilderSkeletonShapingParams Params;` — `UPROPERTY(EditAnywhere, Category = "Skeleton Shaping", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVMeshBuilderSkeletonShapingSettingsElement`  
`class FPVMeshBuilderSkeletonShapingSettingsElement : public FPVBaseElement`  
_L29-33_
- inherits: `FPVBaseElement`
- L32 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVBoneReductionSettings.h` (Private)


#### class `UPVBoneReductionSettings`  
`class UPVBoneReductionSettings : public UPVBaseSettings`  
_L9-36_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L17 _public function_ `virtual FName GetDefaultNodeName() const override`
- L18 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L19 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L20 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L23 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L24 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L28 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L29 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L31 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L35 _private member_ `float Strength = 0;` — `UPROPERTY(EditAnywhere, Category = "Bone Reduction", meta = (PCG_Overridable, ShowOnlyInnerProperties, ClampMin ="0", ClampMax = "1", UIMin = "0", UIMax = "1", Tooltip="How aggressively bones are reduced.\n\n0 = no reduction (full bone count, max wind accuracy). 1 = maximum reduction (fewest bones, fastest, least accurate wind)."))`

#### class `FPVBoneReductionElement`  
`class FPVBoneReductionElement : public FPVBaseElement`  
_L38-42_
- inherits: `FPVBaseElement`
- L41 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVCarveSettings.h` (Private)


#### class `UPVCarveSettings`  
`class UPVCarveSettings : public UPVBaseSettings`  
_L11-37_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L19 _public function_ `virtual FName GetDefaultNodeName() const override`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L25 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L30 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L32 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L36 _public member_ `FPVCarveParams CarveSettings;` — `UPROPERTY(EditAnywhere, Category = "Carve", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVCarveElement`  
`class FPVCarveElement : public FPVBaseElement`  
_L39-43_
- inherits: `FPVBaseElement`
- L42 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVExtractFromImageSettings.h` (Private)


#### class `UPVExtractFromImageSettings`  
`class UPVExtractFromImageSettings : public UPVBaseSettings`  
_L13-51_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L19 _public prototype_ `UPVExtractFromImageSettings();`
- L22 _public function_ `virtual FName GetDefaultNodeName() const override`
- L23 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L24 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L25 _public function_ `virtual EPCGSettingsType GetType() const override`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L28 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L30 _public function_ `virtual bool IsCollectionRenderingEnabled() const override`
- L31 _public function_ `virtual ELevelViewportType GetPreferredViewportType() const`
- L35 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L36 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L37 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L38 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L42 _public member_ `FPVImportTexture2DParams Params;` — `UPROPERTY(EditAnywhere, Category="Importer Settings", meta = (ShowOnlyInnerProperties))`
- L45 _public member_ `FPVImportTexture2DDebugParams DebugParams;` — `UPROPERTY(EditAnywhere, Transient, Category = DebugSettings, meta = (EditCondition = "bDebug", EditConditionHides))`
- L49 _public member_ `TObjectPtr<UMaterialInterface> TextureVisualizationMaterial;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "bDebug", EditConditionHides))`

#### class `FPVExtractFromImageElement`  
`class FPVExtractFromImageElement : public FPVBaseElement`  
_L53-57_
- inherits: `FPVBaseElement`
- L56 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVExtractFromMeshSettings.h` (Private)


#### class `UPVExtractFromMeshSettings`  
`class UPVExtractFromMeshSettings : public UPVBaseSettings`  
_L11-39_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L18 _public function_ `virtual FName GetDefaultNodeName() const override`
- L19 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L21 _public function_ `virtual EPCGSettingsType GetType() const override`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L24 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L25 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L29 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L30 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L31 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L35 _public member_ `FPVImportStaticMeshParams Params;` — `UPROPERTY(EditAnywhere, Category="Settings", meta = (ShowOnlyInnerProperties))`
- L38 _public member_ `FPVImportStaticMeshDebugParams DebugParams;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "bDebug", EditConditionHides))`

#### class `FPVExtractFromMeshElement`  
`class FPVExtractFromMeshElement : public FPVBaseElement`  
_L41-45_
- inherits: `FPVBaseElement`
- L44 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVFoliageDistributorSettings.h` (Private)


#### class `UPVFoliageDistributorSettings`  
`class UPVFoliageDistributorSettings : public UPVBaseSettings`  
_L12-71_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L20 _public function_ `virtual FName GetDefaultNodeName() const override`
- L21 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L22 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L23 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L24 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L26 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L27 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L33 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L36 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L37 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L38 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L40 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L45 _private member_ `EPVDistributionSettingsMode Mode = EPVDistributionSettingsMode::HormoneBasedSettings;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings Mode", meta=(PCG_Overridable, Tooltip="Choose between hormone-based or parametric placement.\n\nHormone Based: leverages the Grower's growth data in order to produce more botanically correct and realistic foliage that mirrors the growth simulation. Parametric: gradient and ramp based control for more artistic control with less reliance on botanical properties."))`
- L49 _private member_ `FPVDistributionParametricParams ParametricSettings;` — `UPROPERTY(EditAnywhere, Category="Parametric Settings", meta=(PCG_NotOverridable, EditCondition="Mode == EPVDistributionSettingsMode::ParametricSettings", EditConditionHides, Tooltip="Parametric distribution rules using ramps and gradients."))`
- L53 _private member_ `FPVDistributionHormoneBasedParams HormoneBasedSettings;` — `UPROPERTY(EditAnywhere, Category="Hormone Based Settings", meta=(PCG_NotOverridable, EditCondition="Mode == EPVDistributionSettingsMode::HormoneBasedSettings", EditConditionHides, Tooltip="Hormone-driven distribution rules using the Grower's growth data."))`
- L57 _private member_ `FPVDistributionVectorParams VectorSettings;` — `UPROPERTY(EditAnywhere, Category="Vector Settings", meta=(PCG_NotOverridable, ShowOnlyInnerProperties, Tooltip="Orientation rules: aim direction, face direction, roll/pitch/yaw."))`
- L61 _private member_ `FPVDistributionConditionParams ConditionSettings;` — `UPROPERTY(EditAnywhere, Category="ConditionSettings", meta=(PCG_NotOverridable, ShowOnlyInnerProperties, Tooltip="Per-condition filters (Light, Scale, UpAlignment, Tip, Health, Height, Generation)."))`
- L64 _private member_ `int32 RandomSeed = 123456;` — `UPROPERTY(EditAnywhere, Category = "Misc Settings", meta = (PCG_Overridable, Tooltip="Random seed for the distributor.\n\nIndependent of the Grower's RandomSeed. Same seed = identical foliage layout."))`
- L67 _private member_ `float ChainMaskDistance = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Misc Settings", meta = (PCG_Overridable, ClampMin = 0, UIMin = 0, UIMax = 100, Tooltip="Distance from previous foliage to mask out new placement.\n\nWhen chaining multiple Foliage Distributors, this prevents the new one from placing too close to existing foliage. 0 = no masking. Higher values create larger clear zones."))`
- L70 _private member_ `float TrunkOffset = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Misc Settings", meta=(Tooltip="Offset spawned foliage along the trunk thickness", PCG_Overridable, UIMin=0.0f, UIMax=1.0f))`

#### class `FPVFoliageDistributorElement`  
`class FPVFoliageDistributorElement : public FPVBaseElement`  
_L73-77_
- inherits: `FPVBaseElement`
- L76 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVFoliagePaletteSettings.h` (Private)


#### struct `FPinConnectionInfo`  
`struct FPinConnectionInfo`  
_L9-15_
- L11 _public member_ `TWeakObjectPtr<UPCGNode> Node = nullptr;`
- L12 _public member_ `TWeakObjectPtr<UPCGNode> TargetNode = nullptr;`
- L13 _public member_ `FName FromPinLabel = NAME_None;`
- L14 _public member_ `FName ToPinLabel = NAME_None;`

#### class `UPVFoliagePaletteSettings`  
`class UPVFoliagePaletteSettings : public UPVBaseSettings`  
_L18-61_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L24 _public function_ `virtual FName GetDefaultNodeName() const override`
- L25 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L26 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L27 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L28 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L30 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L31 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L32 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L34 _public prototype_ `virtual void ApplyDeprecation(UPCGNode* InOutNode) override;`
- L35 _public prototype_ `virtual void ApplyDeprecationBeforeUpdatePins(UPCGNode* InOutNode, TArray<TObjectPtr<UPCGPin>>& InInputPins, TArray<TObjectPtr<UPCGPin>>& InOutputPins) override;`
- L39 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L40 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L41 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L44 _public prototype_ `virtual void PostLoad() override;`
- L48 _public member_ `bool bOverrideFoliage = true;` — `UE_DEPRECATED(5.8, "FoliageInfos can now be updated without Override foliage")` — `UPROPERTY(EditAnywhere, Category="Meshes", meta=(PinHiddenByDefault, InlineEditConditionToggle, DeprecatedProperty, DeprecationMessage = "FoliageInfos can now be updated without Override foliage", Tooltip="(Deprecated) Override flag for foliage assignments.\n\nDeprecated. FoliageInfos can now be updated without an override toggle. Will be removed in a future release."))`
- L52 _public member_ `TArray<TSoftObjectPtr<UObject>> FoliageMeshes;` — `UE_DEPRECATED(5.8, "Use FoliageInfos instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use FoliageInfos instead"))`
- L57 _public member_ `TArray<struct FPVFoliageInfo> FoliageInfos;` — `UPROPERTY(EditAnywhere, Category = "Meshes", Meta = (AllowedClasses = "/Script/Engine.StaticMesh,/Script/Engine.SkeletalMesh", ShowOnlyInnerProperties, FullyExpand="true", Tooltip= "List of foliage meshes used for this plant.\n\nEach entry references a Static Mesh or Skeletal Mesh and sets condition values that decide where it spawns. The Foliage Distributor compares these condition values against each spawning point's attributes (light, scale, height, etc.) and places the entry whose conditions best match."))`
- L60 _private member_ `TArray<FPinConnectionInfo> PinConnectionsToUpdate;`

#### class `FPVFoliageElement`  
`class FPVFoliageElement : public FPVBaseElement`  
_L63-70_
- inherits: `FPVBaseElement`
- L66 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L69 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVGraftDistributorSettings.h` (Private)


#### class `UPVGraftDistributorSettings`  
`class UPVGraftDistributorSettings : public UPVBaseSettings`  
_L17-72_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L25 _public function_ `virtual FName GetDefaultNodeName() const override`
- L26 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L27 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L32 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L38 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L41 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L42 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L43 _protected prototype_ `virtual FPCGDataTypeIdentifier GetSkeletonPinTypeIdentifier() const;`
- L44 _protected prototype_ `virtual FPCGDataTypeIdentifier GetGraftPinTypeIdentifier() const;`
- L45 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L49 _private member_ `EPVDistributionSettingsMode Mode = EPVDistributionSettingsMode::ParametricSettings;` — `UPROPERTY(EditAnywhere, Category="Distribution Settings Mode", meta=(PCG_Overridable, Tooltip="Choose parametric or hormone-based distribution.\n\nParametric: parametric distribution leveraging ramps and gradients to control distribution. HormoneBased: uses the Grower's growth data for natural-looking placement."))`
- L53 _private member_ `FPVDistributionParametricParams ParametricSettings;` — `UPROPERTY(EditAnywhere, Category="Parametric Settings", meta=(PCG_NotOverridable, EditCondition="Mode == EPVDistributionSettingsMode::ParametricSettings", EditConditionHides, Tooltip="Parametric distribution rules (density, spacing, axil angle)."))`
- L57 _private member_ `FPVDistributionHormoneBasedParams HormoneBasedSettings;` — `UPROPERTY(EditAnywhere, Category="Hormone Based Settings", meta=(PCG_NotOverridable, EditCondition="Mode == EPVDistributionSettingsMode::HormoneBasedSettings", EditConditionHides, Tooltip="Hormone-driven distribution rules (ethylene threshold, scale, angle)."))`
- L61 _private member_ `FPVDistributionVectorParams VectorSettings;` — `UPROPERTY(EditAnywhere, Category="Vector Settings", meta=(PCG_NotOverridable, ShowOnlyInnerProperties, Tooltip="Orientation rules: aim, face, roll/pitch/yaw."))`
- L65 _private member_ `FPVDistributionConditionParams ConditionSettings;` — `UPROPERTY(EditAnywhere, Category="ConditionSettings", meta=(PCG_NotOverridable, ShowOnlyInnerProperties, Tooltip="Filtering conditions (light, scale, tip, health, etc.)."))`
- L68 _private member_ `int32 RandomSeed = 123456;` — `UPROPERTY(EditAnywhere, Category = "Misc Settings", meta = (PCG_Overridable, Tooltip="Random seed for graft placement.\n\nIndependent of the Grower's RandomSeed. Same seed = identical graft layout."))`
- L71 _private member_ `bool bRecomputeLight = true;` — `UPROPERTY(EditAnywhere, Category = "Misc Settings", meta = (PCG_Overridable, Tooltip="Recompute per-bud light after grafts are placed.\n\nWhen enabled, grafts contribute to light occlusion calculations affecting downstream nodes. Useful if you have additional Foliage Distributors or Senescence-aware nodes after the Grafter. Off = grafts will retain their incoming light data and will not consider its context after distribution."))`

#### class `FPVGraftDistributorElement`  
`class FPVGraftDistributorElement : public FPVBaseElement`  
_L74-78_
- inherits: `FPVBaseElement`
- L77 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PVGraftDistributorInputPins`
- L12 _variable_ `static const FName Skeleton("Ske` (scope `PVGraftDistributorInputPins`)
- L13 _variable_ `static const FName Graft("Gra` (scope `PVGraftDistributorInputPins`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVGraftPaletteSettings.h` (Private)


#### class `UPVGraftPaletteSettings`  
`class UPVGraftPaletteSettings : public UPVBaseSettings`  
_L15-48_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L20 _public prototype_ `UPVGraftPaletteSettings();`
- L23 _public function_ `virtual FName GetDefaultNodeName() const override`
- L24 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L25 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L29 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L30 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L34 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L35 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L36 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L37 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L40 _public prototype_ `virtual void PostLoad() override;`
- L44 _public member_ `TArray<FPVDistributionConditions> GrafterInfos;` — `UE_DEPRECATED(5.8, "Use GraftInfos instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use GraftInfos instead"))`
- L47 _public member_ `TArray<FPVGraftInfo> GraftInfos;` — `UPROPERTY(EditAnywhere, Category = "Graft Skeletons", Meta = (ShowOnlyInnerProperties, FullyExpand="true", Tooltip="List of graft slots — one input pin per entry.\n\nEach entry creates an input pin on this node where a pre-grown plant skeleton (graft) can be connected. The entry's Attributes set the placement conditions the Graft Distributor uses to decide which graft goes onto which attachment point."))`

#### class `FPVGraftPaletteElement`  
`class FPVGraftPaletteElement : public FPVBaseElement`  
_L50-58_
- inherits: `FPVBaseElement`
- L53 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L54 _protected function_ `virtual bool ShouldComputeFullOutputDataCrc(FPCGContext* Context) const override`
- L57 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVGravitySettings.h` (Private)


#### class `UPVGravitySettings`  
`class UPVGravitySettings : public UPVBaseSettings`  
_L10-39_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L18 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L19 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L20 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L22 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L26 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L27 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L29 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L33 _public member_ `FPVGravityParams GravitySettings;` — `UPROPERTY(EditAnywhere, Category="Gravity", meta=(ShowOnlyInnerProperties, PCG_Overridable))`
- L37 _public member_ `FLoopDebugStepper LoopDebugStepper;` — `UPROPERTY(EditAnywhere, Category = "Loop Debug", meta=(EditCondition = "bDebug", EditConditionHides))`

#### class `FPVGravityElement`  
`class FPVGravityElement : public FPVBaseElement`  
_L41-45_
- inherits: `FPVBaseElement`
- L44 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVGrowerSettings.h` (Private)


#### class `UPVGrowerSettings`  
`class UPVGrowerSettings : public UPVBaseSettings`  
_L14-58_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L20 _public function_ `virtual FName GetDefaultNodeName() const override`
- L21 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L22 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L23 _public function_ `virtual EPCGSettingsType GetType() const override`
- L24 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L25 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L27 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L28 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L29 _public prototype_ `virtual TMap<UObject*, FTransform> GetViewportObjects() const override;`
- L32 _public function_ `virtual bool CanCullTaskIfUnwired() const override`
- L33 _public prototype_ `virtual void PostInitProperties() override;`
- L34 _public prototype_ `virtual void PostLoad() override;`
- L37 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L38 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L39 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L40 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L41 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L44 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L51 _public member_ `TObjectPtr<UProceduralVegetationGrowerPreset> Preset;` — `UPROPERTY(EditAnywhere, Category = Preset, meta=(Tooltip="Optional grower preset to populate the Settings below.\n\nAssigning a preset copies its grower parameters into Settings. Use this to start from a known-good configuration or share configurations across assets. Edits to Settings after applying are not written back to the source preset."))`
- L54 _public member_ `bool bUseSplitPoints = false;` — `UPROPERTY()`
- L57 _public member_ `FPVGrowerParams GrowerParams;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=( ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVGrowerElement`  
`class FPVGrowerElement : public FPVBaseElement`  
_L60-66_
- inherits: `FPVBaseElement`
- L63 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L65 _protected function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVGrowthDataLoader.h` (Private)


#### class `UPVGrowthDataLoaderSettings`  
`class UPVGrowthDataLoaderSettings : public UPVBaseSettings`  
_L11-45_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public prototype_ `virtual void PostLoad() override;`
- L19 _public function_ `virtual FName GetDefaultNodeName() const override`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public function_ `virtual EPCGSettingsType GetType() const override`
- L23 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L24 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L25 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L27 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L31 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L32 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L33 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L34 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L38 _public member_ `TObjectPtr<class UProceduralVegetationGrowthDataAsset> GrowthAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category=Settings, meta=(Tooltip="The Growth Data asset to load.\n\nA Procedural Vegetation Growth Data asset stores one or more named plant variations — each a complete grown skeleton with hormones, branches, foliage attachment points, and material references."))`
- L41 _public member_ `TArray<FPVGrowthVariationInfo> GrowthVariations;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta=(Tooltip="List of variations available within the loaded asset.\n\nAuto-populated when the Growth Asset is set. Each entry corresponds to one output pin emitted by this node."))`
- L44 _private prototype_ `void FillGrowthVariationsInfo();`

#### class `FPVGrowthDataLoaderElement`  
`class FPVGrowthDataLoaderElement : public FPVBaseElement`  
_L47-51_
- inherits: `FPVBaseElement`
- L50 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVImporterSettings.h` (Private)


#### class `UPVImporterSettings`  
`class UPVImporterSettings : public UPVBaseSettings`  
_L11-35_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural), meta=(DeprecatedNode, DeprecationMessage="PVImporterSettings is deprecated and produces no output. Remove this node from your graph."))`
- inherits: `UPVBaseSettings`
- L16 _public prototype_ `UPVImporterSettings();`
- L19 _public function_ `virtual FName GetDefaultNodeName() const override`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public function_ `virtual EPCGSettingsType GetType() const override`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L24 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L28 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L29 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L30 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L34 _public member_ `FFilePath SkeletonFile;` — `UPROPERTY(VisibleAnywhere, Category="Skeleton")`

#### class `FPVImporterElement`  
`class FPVImporterElement : public FPVBaseElement`  
_L37-41_
- inherits: `FPVBaseElement`
- L40 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVMeshBuilderSettings.h` (Private)


#### class `UPVMeshBuilderSettings`  
`class UPVMeshBuilderSettings : public UPVBaseSettings`  
_L13-48_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L19 _public function_ `virtual FName GetDefaultNodeName() const override`
- L20 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L21 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L24 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L25 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L27 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L28 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L29 _public prototype_ `virtual void PostLoad() override;`
- L33 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L34 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L35 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L36 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L39 _protected prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L44 _public member_ `FPVMeshBuilderParams MesherSettings;` — `UPROPERTY(EditAnywhere, Category = "Mesh", meta = (ShowOnlyInnerProperties, PCG_Overridable))`
- L47 _public member_ `FString DisplacementWarnings;` — `UPROPERTY()`

#### class `FPVMeshBuilderElement`  
`class FPVMeshBuilderElement : public FPVBaseElement`  
_L50-54_
- inherits: `FPVBaseElement`
- L53 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVPlantProfileLoaderSettings.h` (Private)


#### class `UPVPlantProfileLoaderSettings`  
`class UPVPlantProfileLoaderSettings : public UPVBaseSettings`  
_L11-41_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L18 _public function_ `virtual FName GetDefaultNodeName() const override`
- L19 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L21 _public function_ `virtual EPCGSettingsType GetType() const override`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L24 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L26 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L30 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L31 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L32 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L33 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L37 _public member_ `TObjectPtr<class UProceduralVegetationPlantProfileDataAsset> PlantProfileData = nullptr;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(Tooltip="The Plant Profile asset to load.\n\nA procedural vegetation profile data asset contains data for a shape of the trunk."))`
- L40 _public member_ `TArray<FPVPlantProfile> Profiles;` — `UPROPERTY(VisibleAnywhere, Category = Settings, meta=(Tooltip="List of variations available within the loaded profile.\n\nWhen the loaded asset contains multiple variations, this array exposes them. Each entry typically defines one variant."))`

#### class `FPVPlantProfileLoaderElement`  
`class FPVPlantProfileLoaderElement : public FPVBaseElement`  
_L43-47_
- inherits: `FPVBaseElement`
- L46 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVPresetLoaderSettings.h` (Private)


#### class `UPVPresetLoaderSettings`  
`class UPVPresetLoaderSettings : public UPVBaseSettings`  
_L10-33_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural), meta=(DeprecatedNode, DeprecationMessage="PVPresetLoaderSettings is deprecated and produces no output. Remove this node from your graph."))`
- inherits: `UPVBaseSettings`
- L15 _public prototype_ `UPVPresetLoaderSettings();`
- L17 _public function_ `virtual FName GetDefaultNodeName() const override`
- L18 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L19 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L20 _public function_ `virtual EPCGSettingsType GetType() const override`
- L21 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L22 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L26 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L27 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L28 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L32 _public member_ `TObjectPtr<class UProceduralVegetationPreset> Preset = nullptr;` — `UPROPERTY(VisibleAnywhere, Category="Preset")`

#### class `FPVPresetLoaderElement`  
`class FPVPresetLoaderElement : public FPVBaseElement`  
_L35-39_
- inherits: `FPVBaseElement`
- L38 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVRecomputePointScaleSettings.h` (Private)


#### enum `EPVRecomputePointScaleMode`  
`enum class EPVRecomputePointScaleMode`  
_L10-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `UserTrunkRadius` — Scale is derived from a user-supplied absolute trunk radius value (TrunkRadius).
- L15 _public enumerator_ `MaxScaleAsTrunkRadius` — The largest scale component across all points is treated as the trunk radius.
- L17 _public enumerator_ `SmoothTaper` — Scale tapers smoothly from the base to the tip

#### class `UPVRecomputePointScaleSettings`  
`class UPVRecomputePointScaleSettings : public UPVBaseSettings`  
_L21-65_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L26 _public prototype_ `UPVRecomputePointScaleSettings();`
- L29 _public function_ `virtual FName GetDefaultNodeName() const override`
- L30 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L31 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L32 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L33 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L35 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L39 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L40 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L42 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L47 _public member_ `EPVRecomputePointScaleMode Mode = EPVRecomputePointScaleMode::UserTrunkRadius;` — `UPROPERTY(EditAnywhere, Category = "RecomputePointScale", meta=(Tooltip="How to compute the new scales.\n\n'UserTrunkRadius': set the trunk radius; everything else scales proportionally. 'MaxScaleAsTrunkRadius': largest existing scale is treated as the trunk; others are rescaled. 'SmoothTaper': scales taper smoothly from base to tip using a ramp profile."))`
- L51 _public member_ `float TrunkRadius = 1.f;` — `UPROPERTY(EditAnywhere, Category = "RecomputePointScale", meta=(EditCondition="Mode == EPVRecomputePointScaleMode::UserTrunkRadius", EditConditionHides, Tooltip="Trunk radius in cm.\n\nThe absolute radius (in cm) the trunk's thickest point should have. Other points scale relative to this."))`
- L55 _public member_ `float TrunkRadiusScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "RecomputePointScale", meta = (EditCondition = "Mode == EPVRecomputePointScaleMode::MaxScaleAsTrunkRadius", EditConditionHides, Tooltip="Multiplier applied to the auto-detected trunk radius.\n\nScales the auto-detected trunk radius by this factor. Use to thicken or thin the whole plant relative to its original values."))`
- L59 _public member_ `float TaperTolerance = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "RecomputePointScale", meta = (EditCondition = "Mode == EPVRecomputePointScaleMode::SmoothTaper", EditConditionHides, ClampMin = "1.0", Tooltip="Smoothing tolerance for the taper algorithm.\n\nHigher = smoother taper curves at the cost of less faithful reproduction of the original skeleton's local variations. 1 = minimal smoothing."))`
- L64 _public member_ `FPVFloatRamp TaperProfile;` — `UPROPERTY(EditAnywhere, Category = "RecomputePointScale", meta = (XAxisMin = 0.0f, XAxisMax = 1.0f, YAxisMin = -1.0f, YAxisMax = 1.0f, EditCondition = "Mode != EPVRecomputePointScaleMode::SmoothTaper", EditConditionHides, Tooltip="Curve controlling the per-position taper modulation.\n\nLets you override the default linear taper with a custom curve. X = position from base to tip. Y = scale modifier. Note: visible in non-SmoothTaper modes — 'SmoothTaper' uses its own internal algorithm."))`

#### class `FPVRecomputePointScaleElement`  
`class FPVRecomputePointScaleElement : public FPVBaseElement`  
_L67-71_
- inherits: `FPVBaseElement`
- L70 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVRemoveBranchesSettings.h` (Private)


#### class `UPVRemoveBranchesSettings`  
`class UPVRemoveBranchesSettings : public UPVBaseSettings`  
_L10-37_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L18 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L19 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L20 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L22 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L26 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L27 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L29 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L33 _public member_ `ERemoveBranchesBasis BranchRemoveBasis = ERemoveBranchesBasis::Length;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(PCG_Overridable, Tooltip="Which attribute decides whether a branch is removed.\n\nLength: short branches are removed. Radius: thin branches are removed. Light: shaded branches are removed. Age: old branches are removed. Generation: deep-hierarchy branches are removed."))`
- L36 _public member_ `float Threshold = 0;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(PCG_Overridable, ClampMin = 0f, ClampMax = 1.0f, UIMin = 0f, UIMax = 1.0f, Tooltip="Cutoff threshold for the chosen basis.\n\nBranches exceeding (or falling below, depending on basis) this normalized threshold are removed. Use lower/higher values to prune sparsely or aggressively. 0.1-0.2 = light pruning; 0.5+ = heavy pruning."))`

#### class `FPVRemoveBranchesElement`  
`class FPVRemoveBranchesElement : public FPVBaseElement`  
_L39-43_
- inherits: `FPVBaseElement`
- L42 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVRotateBranchesSettings.h` (Private)


#### class `UPVRotateBranchesSettings`  
`class UPVRotateBranchesSettings : public UPVBaseSettings`  
_L10-34_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L18 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L19 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L20 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L22 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L26 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L27 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L29 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L33 _public member_ `FPVRotateBranchesParams RotateBranchesParams;` — `UPROPERTY(EditAnywhere, Category = "RotateBranches", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVRotateBranchesElement`  
`class FPVRotateBranchesElement : public FPVBaseElement`  
_L36-40_
- inherits: `FPVBaseElement`
- L39 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVSaveGrowerPresetSettings.h` (Private)


#### class `UPVSaveGrowerPresetSettings`  
`class UPVSaveGrowerPresetSettings : public UPVBaseSettings`  
_L10-33_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L18 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L19 _public function_ `virtual EPCGSettingsType GetType() const override`
- L20 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L21 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L24 _public function_ `virtual bool CanCullTaskIfUnwired() const override`
- L27 _public member_ `FPCGAssetExporterParameters ExportParams;` — `UPROPERTY(EditAnywhere, Category = Settings, meta = (ShowOnlyInnerProperties, PCG_Overridable, Tooltip="Asset export configuration: target folder, filename, overwrite policy.\n\nWhere to save, what to name it, and what to do if the asset already exists. The preset asset can then be referenced from any Grower node's 'Preset' field."))`
- L30 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L31 _protected function_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override`
- L32 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `FPVSaveGrowerPresetElement`  
`class FPVSaveGrowerPresetElement : public FPVBaseElement`  
_L35-42_
- inherits: `FPVBaseElement`
- L38 _public function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`
- L41 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVScaleSettings.h` (Private)


#### class `UPVScaleSettings`  
`class UPVScaleSettings : public UPVBaseSettings`  
_L9-34_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L15 _public function_ `virtual FName GetDefaultNodeName() const override`
- L16 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L17 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L18 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L19 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L21 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L25 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L26 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L28 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L32 _public member_ `float Scale = 1;` — `UPROPERTY(EditAnywhere, Category = Settings, meta=(PCG_Overridable, ClampMin = 0.01f, ClampMax = 100.0f, UIMin = 0.01f, UIMax = 10.0f, Tooltip="Uniform scale multiplier applied to the whole plant.\n\nMultiplies the plant's overall size. 1 = no change. 2 = double scale. 0.5 = half scale. Affects both geometry and the underlying skeleton scale attribute."))`

#### class `FPVScaleElement`  
`class FPVScaleElement : public FPVBaseElement`  
_L36-40_
- inherits: `FPVBaseElement`
- L39 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVSeedGeneratorSettings.h` (Private)


#### class `UPVSeedGeneratorSettings`  
`class UPVSeedGeneratorSettings : public UPVBaseSettings`  
_L12-40_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L17 _public function_ `virtual FName GetDefaultNodeName() const override`
- L18 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L19 _public function_ `virtual FText GetNodeTooltipText() const override`
- L26 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L27 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L28 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L32 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L33 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L35 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L39 _public member_ `FPVConvertToSeedPointParams Params;` — `UPROPERTY(EditAnywhere, Category = AvoidanceSettings, meta=(ShowOnlyInnerProperties))`

#### class `FPVSeedGeneratorElement`  
`class FPVSeedGeneratorElement : public FPVBaseElement`  
_L42-46_
- inherits: `FPVBaseElement`
- L45 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVSimplifySettings.h` (Private)


#### class `UPVSimplifySettings`  
`class UPVSimplifySettings : public UPVBaseSettings`  
_L9-33_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L15 _public function_ `virtual FName GetDefaultNodeName() const override`
- L16 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L17 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L18 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L19 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L21 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L25 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L26 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L28 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L32 _public member_ `float Amount = 0;` — `UPROPERTY(EditAnywhere, Category = "Simplify", meta = (ClampMin = 0, ClampMax = 1, UIMin = 0, UIMax = 1.0, Tooltip="How aggressively to simplify (0 = no change, 1 = maximum simplification).\n\n0 = no simplification (keep all points). 1 = maximum simplification (collapse to the fewest possible points that still represent the rough shape)."))`

#### class `FPVSimplifyElement`  
`class FPVSimplifyElement : public FPVBaseElement`  
_L35-39_
- inherits: `FPVBaseElement`
- L38 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Nodes/PVSlopeSettings.h` (Private)


#### class `UPVSlopeSettings`  
`class UPVSlopeSettings : public UPVBaseSettings`  
_L10-34_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L16 _public function_ `virtual FName GetDefaultNodeName() const override`
- L17 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L18 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L19 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L20 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L22 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L26 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L27 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L29 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L33 _public member_ `FPVSlopeParams SlopeParams;` — `UPROPERTY(EditAnywhere, Category = "Slope", meta = (ShowOnlyInnerProperties, PCG_Overridable))`

#### class `FPVSlopeElement`  
`class FPVSlopeElement : public FPVBaseElement`  
_L36-40_
- inherits: `FPVBaseElement`
- L39 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/PVCommon.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PV`
- L6 _namespace_ `namespace Pins` (scope `PV`)
- L8 _variable_ `const FName GrowerPhyllotaxyInputLabel = TEXT("Phy` (scope `PV::Pins`)
- L9 _variable_ `const FName GrowerPhototropismInputLabel = TEXT("Pho` (scope `PV::Pins`)
- L10 _variable_ `const FName GrowerBifurcationInputLabel = TEXT("Bif` (scope `PV::Pins`)
- L11 _variable_ `const FName GrowerAgeSenescenceInputLabel = TEXT("Age` (scope `PV::Pins`)
- L12 _variable_ `const FName GrowerLightSenescenceInputLabel = TEXT("Lig` (scope `PV::Pins`)
- L13 _variable_ `const FName GrowerGuideInputLabel = TEXT("Gui` (scope `PV::Pins`)
- L14 _variable_ `const FName GrowerGravityInputLabel = TEXT("Gra` (scope `PV::Pins`)
- L15 _variable_ `const FName GrowerFoliageInputLabel = TEXT("Fol` (scope `PV::Pins`)
- L16 _variable_ `const FName GrowerGrowthInputLabel = TEXT("Gro` (scope `PV::Pins`)
- L17 _variable_ `const FName GrowerAuxinInputLabel = TEXT("Aux` (scope `PV::Pins`)
- L18 _variable_ `const FName GrowerDirectionalInputLabel = TEXT("Dir` (scope `PV::Pins`)
- L19 _variable_ `const FName GrowerParamsOutputLabel = TEXT("Par` (scope `PV::Pins`)
- L21 _variable_ `const FName FoliageDistributorFoliageInputLabel = TEXT("Fol` (scope `PV::Pins`)
- L23 _variable_ `const FName DistributionParametricSettingsInputLabel = TEXT("Par` (scope `PV::Pins`)
- L24 _variable_ `const FName DistributionHormoneBasedSettingsInputLabel = TEXT("Hor` (scope `PV::Pins`)
- L25 _variable_ `const FName DistributionVectorSettingsInputLabel = TEXT("Vec` (scope `PV::Pins`)
- L26 _variable_ `const FName DistributionConditionSettingsInputLabel = TEXT("Con` (scope `PV::Pins`)
- L28 _variable_ `const FName MeshBuilderProfileInputLabel = TEXT("Pro` (scope `PV::Pins`)
- L30 _variable_ `const FName MeshBuilderSkeletonShapingInputLabel = TEXT("Ske` (scope `PV::Pins`)
- L31 _variable_ `const FName MeshBuilderBranchRadiusInputLabel = TEXT("Bra` (scope `PV::Pins`)
- L32 _variable_ `const FName MeshBuilderProfileDetailsInputLabel = TEXT("Pro` (scope `PV::Pins`)
- L33 _variable_ `const FName MeshBuilderMeshDetailsInputLabel = TEXT("Mes` (scope `PV::Pins`)
- L34 _variable_ `const FName MeshBuilderMaterialDetailsInputLabel = TEXT("Mat` (scope `PV::Pins`)
- L35 _variable_ `const FName MeshBuilderDisplacementInputLabel = TEXT("Dis` (scope `PV::Pins`)
- L38 _namespace_ `namespace PV`
- L38 _namespace_ `namespace NodeColors` (scope `PV`)
- L40 _variable_ `inline const FLinearColor Growth = FLinearColor(FColor::FromHex(TEXT("EFB09` (scope `PV::NodeColors`)
- L41 _variable_ `inline const FLinearColor InputOutput = FLinearColor(FColor::FromHex(TEXT("EFB44` (scope `PV::NodeColors`)
- L42 _variable_ `inline const FLinearColor Foliage = FLinearColor(FColor::FromHex(TEXT("7BF85` (scope `PV::NodeColors`)
- L43 _variable_ `inline const FLinearColor PostGrowthModifiers = FLinearColor(FColor::FromHex(TEXT("FCFD5` (scope `PV::NodeColors`)
- L44 _variable_ `inline const FLinearColor Mesh = FLinearColor(FColor::FromHex(TEXT("7DEDF` (scope `PV::NodeColors`)
- L45 _variable_ `inline const FLinearColor Seed = FLinearColor(FColor::FromHex(TEXT("EFB09` (scope `PV::NodeColors`)
- L46 _variable_ `inline const FLinearColor Subgraph = FLinearColor(FColor::FromHex(TEXT("E5534` (scope `PV::NodeColors`)
- L47 _variable_ `inline const FLinearColor BoneReduction = FLinearColor(FColor::FromHex(TEXT("E640C` (scope `PV::NodeColors`)
- L48 _variable_ `inline const FLinearColor Development = FLinearColor(FColor::Black);` (scope `PV::NodeColors`)
- L51 _namespace_ `namespace PV`
- L51 _namespace_ `namespace Categories` (scope `PV`)
- L53 _variable_ `inline const FText Growth = NSLOCTEXT("PVNodeCategories", "Categ` (scope `PV::Categories`)
- L54 _variable_ `inline const FText InputOutput = NSLOCTEXT("PVNodeCategories", "` (scope `PV::Categories`)
- L55 _variable_ `inline const FText Foliage = NSLOCTEXT("PVNodeCategories", "Cate` (scope `PV::Categories`)
- L56 _variable_ `inline const FText PostGrowthModifiers = NSLOCTEXT("PVNodeCatego` (scope `PV::Categories`)
- L57 _variable_ `inline const FText Mesh = NSLOCTEXT("PVNodeCategories", "Categor` (scope `PV::Categories`)
- L58 _variable_ `inline const FText Seed = NSLOCTEXT("PVNodeCategories", "Categor` (scope `PV::Categories`)
- L59 _variable_ `inline const FText DistributionSettings = NSLOCTEXT("PVNodeCateg` (scope `PV::Categories`)
- L60 _variable_ `inline const FText GrowthSettings = NSLOCTEXT("PVNodeCategories"` (scope `PV::Categories`)
- L61 _variable_ `inline const FText MeshBuilderSettings = NSLOCTEXT("PVNodeCatego` (scope `PV::Categories`)
- L62 _variable_ `inline const FText Development = NSLOCTEXT("PVNodeCategories", "` (scope `PV::Categories`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/PVImportCommon.h` (Private)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PVImportNames`
- L9 _variable_ `inline static const FName BranchHierarchyGroup = TEXT("Bra` (scope `PVImportNames`) — Common
- L10 _variable_ `inline static const FName BranchHierarchyAttribute = TEXT("Cur` (scope `PVImportNames`)
- L11 _variable_ `inline static const FName LabelsGroup = TEXT("Lab` (scope `PVImportNames`)
- L12 _variable_ `inline static const FName LabelPositionAttribute = TEXT("Pos` (scope `PVImportNames`)
- L13 _variable_ `inline static const FName LabelScaleAttribute = TEXT("Sca` (scope `PVImportNames`)
- L14 _variable_ `inline static const FName LabelTextAttribute = TEXT("Tex` (scope `PVImportNames`)
- L15 _variable_ `inline static const FName TipVisualizationGroup = TEXT("End` (scope `PVImportNames`)
- L16 _variable_ `inline static const FName TipVisualizationSizeAttribute = TEXT("Siz` (scope `PVImportNames`)
- L17 _variable_ `inline static const FName TipVisualizationPositionAttribute = TEXT("Ver` (scope `PVImportNames`)
- L20 _variable_ `inline static const FName PixelsDebugGroup = TEXT("Pix` (scope `PVImportNames`) — 2D specific
- L21 _variable_ `inline static const FName PixelPositionsAttribute = TEXT("Pos` (scope `PVImportNames`)
- L22 _variable_ `inline static const FName PixelValueAttribute = TEXT("Val` (scope `PVImportNames`)
- L23 _variable_ `inline static const FName PerimeterCurveGroup = TEXT("Per` (scope `PVImportNames`)
- L24 _variable_ `inline static const FName PerimeterCurveAttribute = TEXT("Per` (scope `PVImportNames`)
- L25 _variable_ `inline static const FName UserRootPositionsGroup = TEXT("Roo` (scope `PVImportNames`)
- L26 _variable_ `inline static const FName UserRootPositionsAttribute = TEXT("Ver` (scope `PVImportNames`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Params/PVImportStaticMeshParams.h` (Private)


#### enum `EPVImportStaticMeshDebugState`  
`enum class EPVImportStaticMeshDebugState : uint8`  
_L11-23_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `None`
- L14 _public enumerator_ `InitialMesh`
- L15 _public enumerator_ `ComputeNormals`
- L16 _public enumerator_ `ComputeVerticesCenterAndRadius`
- L17 _public enumerator_ `CollapseBranchesToLine`
- L18 _public enumerator_ `FindEndPoints`
- L19 _public enumerator_ `FindRootPoints`
- L20 _public enumerator_ `ConnectBranchesToParent`
- L21 _public enumerator_ `ComputeBranchHierarchies`
- L22 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FPVImportStaticMeshParams`  
`struct FPVImportStaticMeshParams`  
_L26-35_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `TObjectPtr<UStaticMesh> StaticMeshAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta=(Tooltip="The static mesh to trace.\n\nPick a Static Mesh asset from the content browser. The mesh's geometry is analysed to identify branch tips, roots, and the hierarchy connecting them."))`
- L34 _public member_ `TArray<FName> MaterialsToKeep;` — `UPROPERTY(EditAnywhere, Category = "Asset", meta=(Tooltip="Names of materials to include in the trace.\n\nOnly mesh sections using one of these material slot names contribute to the extracted skeleton. Use to ignore leaf or foliage materials and keep only the bark/structural geometry."))`

#### struct `FPVImportStaticMeshDebugParams`  
`struct FPVImportStaticMeshDebugParams`  
_L38-50_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public member_ `EPVImportStaticMeshDebugState DebugState = EPVImportStaticMeshDebugState::None;` — `UPROPERTY(EditAnywhere, Category = "DebugSettings")`
- L46 _public member_ `bool bShowFoundTips = true;` — `UPROPERTY(EditAnywhere, Category = "DebugSettings")`
- L49 _public member_ `bool bShowFoundBranchCurves = true;` — `UPROPERTY(EditAnywhere, Category = "DebugSettings")`

#### struct `FPVImportStaticMeshOutput`  
`struct FPVImportStaticMeshOutput`  
_L52-57_
- L54 _public member_ `TOptional<FManagedArrayCollection> DebugCollection;`
- L55 _public member_ `FManagedArrayCollection VisualizationCollection;`
- L56 _public member_ `FManagedArrayCollection GrowthDataCollection;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Params/PVImportTexture2DParams.h` (Private)


#### enum `EPVImportTexture2DDebugState`  
`enum class EPVImportTexture2DDebugState : uint8`  
_L43-50_
- reflection: `UENUM(BlueprintType)`
- L45 _public enumerator_ `None`
- L46 _public enumerator_ `TriangulateCurves`
- L47 _public enumerator_ `ComputeVertexScale`
- L48 _public enumerator_ `ComputeBranchHierarchies`
- L49 _public enumerator_ `MAX UMETA(Hidden)`

#### struct `FPVImportTexture2DPlantSettings`  
`struct FPVImportTexture2DPlantSettings`  
_L53-65_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public member_ `FVector2f RootPosition = FVector2f::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(Tooltip="2D position in the image where this plant's root sits.\n\nWhen the image contains multiple plants, this anchors each one's root in 2D image coordinates."))`
- L61 _public member_ `float Rotation = 0;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(Tooltip="Rotation applied to the extracted skeleton in degrees.\n\nUseful for rotating the plant after extraction so it faces the correct direction in 3D space."))`
- L64 _public member_ `float Scale = 100.f;` — `UPROPERTY(EditAnywhere, Category = "Plant Settings", meta=(Tooltip="Uniform scale applied to the extracted skeleton.\n\nDefault 100 = image units treated as cm. Adjust to match your scene scale."))`

#### struct `FPVImportTexture2DParams`  
`struct FPVImportTexture2DParams`  
_L68-116_
- reflection: `USTRUCT(BlueprintType)`
- L73 _public member_ `TObjectPtr<UTexture2D> Texture2DAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Texture", meta=(Tooltip="The texture asset to trace.\n\nPick a texture from the content browser."))`
- L77 _public member_ `bool bInvertImage = false;` — `UPROPERTY(EditAnywhere, Category = "Texture", meta = (EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Invert image colors (use for dark plant on light background).\n\nWhen on, the brightness is inverted before tracing. Use when your source image has dark plant shapes on a light background."))`
- L81 _public member_ `float WhiteLevel = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Texture", meta = (ClampMin = 0, ClampMax = 1, UIMin = 0, UIMax = 1, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Brightness threshold for 'plant' vs. 'background'.\n\nPixels above this brightness are considered plant; below are background. Default 0.01 = nearly any non-black pixel is plant. Raise to ignore noise; lower to include faint pixels."))`
- L85 _public member_ `EPCGTextureColorChannel ColorChannel = EPCGTextureColorChannel::Red;` — `UPROPERTY(EditAnywhere, Category = "Texture", meta = (ClampMin = 0, UIMin = 0, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Which color channel to read brightness from.\n\nWhich color channel to read brightness from Red / Green / Blue / Alpha."))`
- L89 _public member_ `int32 SampleResolution = 1024;` — `UPROPERTY(EditAnywhere, Category = "Image Trace", meta = (ClampMin = 0, UIMin = 0, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Texture sampling resolution.\n\nHow densely the image is sampled during tracing. Higher = more detail, slower."))`
- L95 _public member_ `float MinBoundsArea = 0.05f;` — `UPROPERTY(EditAnywhere, Category = "Image Trace", meta = (ClampMin = 0, UIMin = 0, UIMax = 0.2, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Minimum region area to count as a plant region (fraction of image).\n\nFilters out small specks. 0.05 = ignore regions smaller than 5% of the image area. Lower to detect tiny plants in a sparse image; raise to focus only on the main shape."))` — Any plants with a bounds area lower than this value will be ignored. Value is normalized meaning a value of 0.1 will filter out any plants whose bounds cover less than 10% of the image.
- L99 _public member_ `int32 SmoothingIterations = 2;` — `UPROPERTY(EditAnywhere, Category = "Image Trace", meta = (ClampMin = 0, ClampMax = 100, UIMin = 0, UIMax = 10, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="How many passes of smoothing applied to the traced outline.\n\nHigher = smoother branch curves with less jagged outline noise. 0 = raw trace. Excessive smoothing may round away plant features."))`
- L103 _public member_ `float SimplificationAmount = 1.0;` — `UPROPERTY(EditAnywhere, Category = "Image Trace", meta = (ClampMin = 0, ClampMax = 100, UIMin = 0, UIMax = 10.0, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="How much to simplify the traced skeleton.\n\nHigher = fewer skeleton points, simpler structure. 0 = full detail. 1.0 = light simplification (default). Higher = heavy simplification."))`
- L107 _public member_ `float TipAngleThresholdInDegrees = 100.0;` — `UPROPERTY(EditAnywhere, Category = "Tip detection", meta = (ClampMin = 0.001, ClampMax = 180, UIMin = 0.01, UIMax = 180, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Minimum corner angle to detect a branch tip.\n\nSharper corners (smaller angles) are detected as branch tips. Lower values = more detected tips (more sensitive). Higher values = only sharp endpoints qualify."))`
- L111 _public member_ `float MaxTipAngleSearchDist = 0.005f;` — `UPROPERTY(EditAnywhere, Category = "Tip detection", meta = (ClampMin = 0, ClampMax = 0.01, UIMin = 0, UIMax = 0.01, EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Search distance for confirming detected tips.\n\nHow far the algorithm looks from a candidate tip to confirm it. Larger values catch tips on smooth curves; smaller values are stricter."))`
- L115 _public member_ `TArray<FPVImportTexture2DPlantSettings> PlantSettings;` — `UPROPERTY(EditAnywhere, Category = "Plant Geneneration", meta = (EditCondition = "Texture2DAsset != nullptr", EditConditionHides, Tooltip="Per-plant placement settings (root position, rotation, scale)."))`

#### struct `FPVImportTexture2DDebugParams`  
`struct FPVImportTexture2DDebugParams`  
_L119-125_
- reflection: `USTRUCT(BlueprintType)`
- L124 _public member_ `EPVImportTexture2DDebugState DebugState = EPVImportTexture2DDebugState::None;` — `UPROPERTY(EditAnywhere, Category = "DebugSettings")`

#### struct `FPVImportTexture2DOutput`  
`struct FPVImportTexture2DOutput`  
_L127-131_
- L129 _public member_ `TOptional<FManagedArrayCollection> DebugCollection;`
- L130 _public member_ `TArray<FManagedArrayCollection> PlantCollections;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PVTexture2DImporterVisualization`
- L14 _variable_ `constexpr float Scale = 100.f;` (scope `PVTexture2DImporterVisualization`)
- L15 _variable_ `inline const FVector3f Offset = FVector3f(0, -Scale / 2.f, 25.f);` (scope `PVTexture2DImporterVisualization`)
- L17 _function_ `inline FMatrix44f GetUVToWorldMatrix()` (scope `PVTexture2DImporterVisualization`)
- L28 _function_ `inline FMatrix44f GetWorldToUVMatrix()` (scope `PVTexture2DImporterVisualization`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Utils/PVAttributes.h` (Private)


#### class `PV::TAttributeView`  
`class TAttributeView`  
_L50-152_
- L53 _public typedef_ `using ElementType = std::remove_const_t<InElementType>;`
- L55 _public typedef_ `using ManagedArrayType = std::conditional_t<std::is_const_v<InElementType>, const TManagedArray<ElementType>, TManagedArray<ElementType>>;`
- L60 _public typedef_ `using ElementViewType = std::conditional_t<std::is_const_v<InElementType>, InElementConstViewType, InElementViewType>;`
- L65 _public typedef_ `using MutableAttributeViewType = TAttributeView<ElementType, InElementViewType, InElementConstViewType, InAttributeNameStr, InGroupNameStr>;`
- L66 _public typedef_ `using ConstAttributeViewType = TAttributeView<const ElementType, InElementViewType, InElementConstViewType, InAttributeNameStr, InGroupNameStr>;`
- L68 _public typedef_ `using SizeType = TArray<ElementType>::SizeType;`
- L70 _public member_ `inline static const FName AttributeName = FName(InAttributeNameStr);`
- L71 _public member_ `inline static const FName GroupName = FName(InGroupNameStr);`
- L73 _public member_ `ManagedArrayType* ManagedArray;`
- L75 _public function_ `TAttributeView() : ManagedArray(nullptr)`
- L79 _public function_ `TAttributeView(ManagedArrayType* InManagedArray) : ManagedArray(InManagedArray)`
- L83 _public function_ `TAttributeView(const MutableAttributeViewType& Other) : ManagedArray(Other.ManagedArray)`
- L89 _public function_ `TAttributeView(const ConstAttributeViewType& Other) : ManagedArray(Other.ManagedArray)`
- L94 _public function_ `bool IsValid() const`
- L99 _public function_ `ElementViewType operator[](SizeType Index) const`
- L105 _public function_ `operator bool() const`
- L110 _public function_ `bool operator!() const`
- L120 _public function_ `bool IsValidIndex(SizeType Index) const` — return true if index is in array range. @param Index Index to check.
- L128 _public function_ `int32 Find(const ElementType& Item) const` — Find first index of the element
- L133 _public function_ `SizeType Num() const`
- L138 _public typedef_ `using RangedForIteratorType = ManagedArrayType::RangedForIteratorType;`
- L139 _public typedef_ `using RangedForConstIteratorType = ManagedArrayType::RangedForConstIteratorType;`
- L141 _public typedef_ `using AttributeRangedForIteratorType = std::conditional_t<std::is_const_v<InElementType>, RangedForConstIteratorType, RangedForIteratorType>;`
- L150 _public function_ `FORCEINLINE AttributeRangedForIteratorType begin() const` — DO NOT USE DIRECTLY STL-like iterators to enable range-based for loop support.
- L151 _public function_ `FORCEINLINE AttributeRangedForIteratorType end() const`

#### class `PV::TAttributeAccessor`  
`class TAttributeAccessor : public TManagedArrayAccessor<InElementType>`  
_L161-205_
- inherits: `TManagedArrayAccessor<InElementType>`
- L166 _public typedef_ `using ElementType = InElementType;`
- L167 _public typedef_ `using ManagedArrayType = TManagedArray<ElementType>;`
- L168 _public typedef_ `using AttributeView = TAttributeView<ElementType, InElementViewType, InElementConstViewType, InAttributeNameStr, InGroupNameStr>;`
- L169 _public typedef_ `using AttributeConstView = TAttributeView<const ElementType, InElementViewType, InElementConstViewType, InAttributeNameStr, InGroupNameStr>;`
- L170 _public typedef_ `using Super = TManagedArrayAccessor<ElementType>;`
- L172 _public member_ `inline static const FName AttributeName = FName(InAttributeNameStr);`
- L173 _public member_ `inline static const FName GroupName = FName(InGroupNameStr);`
- L175 _public prototype_ `TAttributeAccessor() = delete;`
- L177 _public function_ `TAttributeAccessor(FManagedArrayCollection& InCollection) : Super(InCollection, AttributeName, GroupName)`
- L181 _public function_ `TAttributeAccessor(const FManagedArrayCollection& InCollection) : Super(InCollection, AttributeName, GroupName)`
- L185 _public function_ `AttributeView GetView()`
- L190 _public function_ `AttributeConstView GetConstView() const`
- L195 _public function_ `InElementViewType ModifyAt(int32 Index)`
- L201 _public function_ `InElementConstViewType operator[](int32 Index) const`

#### class `PV::TAttributeDefinition`  
`class TAttributeDefinition`  
_L214-318_
- L219 _public typedef_ `using AttributeType = InAttributeType;`
- L220 _public typedef_ `using AttributeAccessor = TAttributeAccessor<AttributeType, InElementViewType, InElementConstViewType, InAttributeNameStr, InGroupNameStr>;`
- L221 _public typedef_ `using AttributeView = AttributeAccessor::AttributeView;`
- L222 _public typedef_ `using AttributeConstView = AttributeAccessor::AttributeConstView;`
- L224 _public member_ `inline static const FName AttributeName = FName(InAttributeNameStr);`
- L225 _public member_ `inline static const FName GroupName = FName(InGroupNameStr);`
- L226 _public member_ `inline static const FManagedArrayCollection::FManagedType ManagedType = FManagedArrayCollection::TManagedType<AttributeType>(AttributeName, GroupName);`
- L232 _public function_ `static AttributeConstView FindAttribute(const FManagedArrayCollection& InCollection)` — Tries to find the attribute in the supplied collection. Returns a null view if attribute is not in collection. @return A const view of the found attribute.
- L241 _public function_ `static AttributeView FindAttribute(FManagedArrayCollection& InCollection)` — Tries to find the attribute in the supplied collection. Returns a null view if attribute is not in collection. @return A mutable view of the found attribute.
- L250 _public function_ `static AttributeConstView GetAttribute(const FManagedArrayCollection& InCollection)` — Checked version of FindAttribute. Will assert if attribute is missing from collection. @return A const view of the found attribute.
- L261 _public function_ `static AttributeView GetAttribute(FManagedArrayCollection& InCollection)` — Checked version of FindAttribute. Will assert if attribute is missing from collection. @return A mutable view of the found attribute.
- L272 _public function_ `static AttributeView AddAttribute(FManagedArrayCollection& InCollection)` — Add the attribute to the collection and returns a view to the added collection. Returns existing attribute in the collection if already present. @return A mutable view of the found attribute.
- L282 _public function_ `static AttributeView AddAttribute(FManagedArrayCollection& InCollection, const AttributeType& DefaultValue)` — Add the attribute to the collection and returns a view to the added collection. Returns existing attribute in the collection if already present. @param DefaultValue - Initialize all elements in the added attribute with this value (only if the attribute is not already present) @return A mutable view of the found attribute.
- L301 _public function_ `static bool HasAttribute(const FManagedArrayCollection& InCollection)` — Check for the existence of the attribute in the collection.
- L309 _public function_ `static void CopyAttribute(const FManagedArrayCollection& SourceCollection, FManagedArrayCollection& DestCollection)` — Copy the attribute from one collection to another. Will perform an implicit group sync.

#### struct `PV::TFixedSizeArrayHelper`  
`template<typename InElementType> struct TFixedSizeArrayHelper`  
_L322-354_
- desc: Helper class to allow for initialization, and selecton of, a fixed size array based of off default input array.
- L324 _public typedef_ `using ElementType = std::remove_const_t<InElementType>;`
- L325 _public typedef_ `using MutableArrayType = TArray<ElementType>;`
- L326 _public typedef_ `using ConstArrayType = const TArray<ElementType>;`
- L327 _public typedef_ `using ArrayType = std::conditional_t<std::is_const_v<InElementType>, ConstArrayType, MutableArrayType>;`
- L329 _public prototype_ `TFixedSizeArrayHelper() = delete;`
- L331 _public function_ `static MutableArrayType& GetFixedArray(MutableArrayType& InMutableArray, const ConstArrayType& InDefaultData)`
- L346 _public function_ `static ConstArrayType& GetFixedArray(ConstArrayType& InConstArray, const ConstArrayType& InDefaultData)`

#### struct `PV::TBudLightDetectedView`  
`template<typename TFloatType> struct TBudLightDetectedView`  
_L436-457_
- L438 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TFloatType>::ArrayType;`
- L440 _public member_ `inline const static TArray<float> DefaultData = { 0, 0, 0, 0 };`
- L442 _public member_ `ArrayType& Array;`
- L443 _public member_ `TFloatType& Availible;`
- L444 _public member_ `TFloatType& Resource;`
- L445 _public member_ `TFloatType& Branch;`
- L446 _public member_ `TFloatType& Collision;`
- L448 _public prototype_ `TBudLightDetectedView() = delete;`
- L449 _public function_ `TBudLightDetectedView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TFloatType>::GetFixedArray(InData, DefaultData)) , Availible(Array[0]) , Resource(Array[1]) , Branch(Array[2]) , Collision(Array[3])`

#### struct `PV::TBudLateralMeristemView`  
`template<typename TFloatType> struct TBudLateralMeristemView`  
_L463-490_
- L465 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TFloatType>::ArrayType;`
- L467 _public member_ `inline const static TArray<float> DefaultData = { 0, 0, 0, 0, 0, 0, 0 };`
- L469 _public member_ `ArrayType& Array;`
- L470 _public member_ `TFloatType& LateralMeristem;`
- L471 _public member_ `TFloatType& Multiplier;`
- L472 _public member_ `TFloatType& Inactive;`
- L473 _public member_ `TFloatType& Davinci;`
- L474 _public member_ `TFloatType& ParentDot;`
- L475 _public member_ `TFloatType& RootDistance;`
- L476 _public member_ `TFloatType& Degredation;`
- L478 _public prototype_ `TBudLateralMeristemView() = delete;`
- L479 _public function_ `TBudLateralMeristemView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TFloatType>::GetFixedArray(InData, DefaultData)) , LateralMeristem(Array[0]) , Multiplier(Array[1]) , Inactive(Array[2]) , Davinci(Array[3]) , ParentDot(Array[4]) , RootDistance(Array[5]) , Degredation(Array[6])`

#### struct `PV::TBudHormoneLevelsView`  
`template<typename TFloatType> struct TBudHormoneLevelsView`  
_L496-521_
- L498 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TFloatType>::ArrayType;`
- L500 _public member_ `inline const static TArray<float> DefaultData = { 0, 0, 0, 0, 0, 0 };`
- L502 _public member_ `ArrayType& Array;`
- L503 _public member_ `TFloatType& Apical;`
- L504 _public member_ `TFloatType& Axillary;`
- L505 _public member_ `TFloatType& AxillaryInhibition;`
- L506 _public member_ `TFloatType& Radical;`
- L507 _public member_ `TFloatType& Ethylene;`
- L508 _public member_ `TFloatType& Cytokinin;`
- L510 _public prototype_ `TBudHormoneLevelsView() = delete;`
- L511 _public function_ `TBudHormoneLevelsView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TFloatType>::GetFixedArray(InData, DefaultData)) , Apical(Array[0]) , Axillary(Array[1]) , AxillaryInhibition(Array[2]) , Radical(Array[3]) , Ethylene(Array[4]) , Cytokinin(Array[5])`

#### struct `PV::TBudDirectionView`  
`template<typename TVec3Type> struct TBudDirectionView`  
_L527-552_
- L529 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TVec3Type>::ArrayType;`
- L531 _public member_ `inline const static TArray<FVector3f> DefaultData = { FVector3f::ZeroVector, FVector3f::ZeroVector, FVector3f::ZeroVector, FVector3f::ZeroVector, FVector3f::ZeroVector, FVector3f::ZeroVector };`
- L533 _public member_ `ArrayType& Array;`
- L534 _public member_ `TVec3Type& Apical;`
- L535 _public member_ `TVec3Type& Axillary;`
- L536 _public member_ `TVec3Type& LightOptimal;`
- L537 _public member_ `TVec3Type& LightSubOptimal;`
- L538 _public member_ `TVec3Type& GuideCurve;`
- L539 _public member_ `TVec3Type& UpVector;`
- L541 _public prototype_ `TBudDirectionView() = delete;`
- L542 _public function_ `TBudDirectionView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TVec3Type>::GetFixedArray(InData, DefaultData)) , Apical(Array[0]) , Axillary(Array[1]) , LightOptimal(Array[2]) , LightSubOptimal(Array[3]) , GuideCurve(Array[4]) , UpVector(Array[5])`

#### struct `PV::TBudStatusView`  
`template<typename TIntType> struct TBudStatusView`  
_L558-591_
- L560 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TIntType>::ArrayType;`
- L562 _public member_ `inline const static TArray<int32> DefaultData = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };`
- L564 _public member_ `ArrayType& Array;`
- L565 _public member_ `TIntType& ApicalMeristem;`
- L566 _public member_ `TIntType& Codominant;`
- L567 _public member_ `TIntType& Axillary;`
- L568 _public member_ `TIntType& Seed;`
- L569 _public member_ `TIntType& Dormant;`
- L570 _public member_ `TIntType& Triggered;`
- L571 _public member_ `TIntType& NumTriggered;`
- L572 _public member_ `TIntType& Inactive;`
- L573 _public member_ `TIntType& BrokenTip;`
- L574 _public member_ `TIntType& Broken;`
- L576 _public prototype_ `TBudStatusView() = delete;`
- L577 _public function_ `TBudStatusView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TIntType>::GetFixedArray(InData, DefaultData)) , ApicalMeristem(Array[0]) , Codominant(Array[1]) , Axillary(Array[2]) , Seed(Array[3]) , Dormant(Array[4]) , Triggered(Array[5]) , NumTriggered(Array[6]) , Inactive(Array[7]) , BrokenTip(Array[8]) , Broken(Array[9])`

#### struct `PV::TBudDevelopmentView`  
`template<typename TIntType> struct TBudDevelopmentView`  
_L597-622_
- L599 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TIntType>::ArrayType;`
- L601 _public member_ `inline const static TArray<int32> DefaultData = { 0, 0, 0, 0, 0, 0 };`
- L603 _public member_ `ArrayType& Array;`
- L604 _public member_ `TIntType& Generation;`
- L605 _public member_ `TIntType& BudAge;`
- L606 _public member_ `TIntType& BranchAge;`
- L607 _public member_ `TIntType& AgeSenescense;`
- L608 _public member_ `TIntType& LightSenescense;`
- L609 _public member_ `TIntType& RelativeBudAge;`
- L611 _public prototype_ `TBudDevelopmentView() = delete;`
- L612 _public function_ `TBudDevelopmentView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TIntType>::GetFixedArray(InData, DefaultData)) , Generation(Array[0]) , BudAge(Array[1]) , BranchAge(Array[2]) , AgeSenescense(Array[3]) , LightSenescense(Array[4]) , RelativeBudAge(Array[5])`

#### struct `PV::TDetailLeafGrowthView`  
`template<typename TFloatType> struct TDetailLeafGrowthView`  
_L646-673_
- L648 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TFloatType>::ArrayType;`
- L650 _public member_ `inline const static TArray<float> DefaultData = { 0, 0, 0, 0, 0, 0, 0 };`
- L652 _public member_ `ArrayType& Array;`
- L653 _public member_ `TFloatType& Ethylene;`
- L654 _public member_ `TFloatType& StartScale;`
- L655 _public member_ `TFloatType& EndScale;`
- L656 _public member_ `TFloatType& Density;`
- L657 _public member_ `TFloatType& AbscisicAcid;`
- L658 _public member_ `TFloatType& EthyleneThreshold;`
- L659 _public member_ `TFloatType& LeafAuxinRetention;`
- L661 _public prototype_ `TDetailLeafGrowthView() = delete;`
- L662 _public function_ `TDetailLeafGrowthView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TFloatType>::GetFixedArray(InData, DefaultData)) , Ethylene(Array[0]) , StartScale(Array[1]) , EndScale(Array[2]) , Density(Array[3]) , AbscisicAcid(Array[4]) , EthyleneThreshold(Array[5]) , LeafAuxinRetention(Array[6])`

#### struct `PV::TDetailAbscissionSenescenseView`  
`template<typename TFloatType> struct TDetailAbscissionSenescenseView`  
_L679-710_
- L681 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TFloatType>::ArrayType;`
- L683 _public member_ `inline const static TArray<float> DefaultData = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };`
- L685 _public member_ `ArrayType& Array;`
- L686 _public member_ `TFloatType& GravitationalAbscissionFactor;`
- L687 _public member_ `TFloatType& AgeAbscissionThreshold;`
- L688 _public member_ `TFloatType& AgeAbscissionMin;`
- L689 _public member_ `TFloatType& AgeAbscissionMax;`
- L690 _public member_ `TFloatType& AgeScaleRetention;`
- L691 _public member_ `TFloatType& LightAbscissionThreshold;`
- L692 _public member_ `TFloatType& LightAbscissionMin;`
- L693 _public member_ `TFloatType& LightAbscissionMax;`
- L694 _public member_ `TFloatType& LightScaleRetention;`
- L696 _public prototype_ `TDetailAbscissionSenescenseView() = delete;`
- L697 _public function_ `TDetailAbscissionSenescenseView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TFloatType>::GetFixedArray(InData, DefaultData)) , GravitationalAbscissionFactor(Array[0]) , AgeAbscissionThreshold(Array[1]) , AgeAbscissionMin(Array[2]) , AgeAbscissionMax(Array[3]) , AgeScaleRetention(Array[4]) , LightAbscissionThreshold(Array[5]) , LightAbscissionMin(Array[6]) , LightAbscissionMax(Array[7]) , LightScaleRetention(Array[8])`

#### struct `PV::TDetailLateralElongationView`  
`template<typename TFloatType> struct TDetailLateralElongationView`  
_L716-747_
- L718 _public typedef_ `using ArrayType = TFixedSizeArrayHelper<TFloatType>::ArrayType;`
- L720 _public member_ `inline const static TArray<float> DefaultData = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };`
- L722 _public member_ `ArrayType& Array;`
- L723 _public member_ `TFloatType& Elongation;`
- L724 _public member_ `TFloatType& SeedScaleEffect;`
- L725 _public member_ `TFloatType& WhorledImpact;`
- L726 _public member_ `TFloatType& CellDensityMin;`
- L727 _public member_ `TFloatType& CellDensityMax;`
- L728 _public member_ `TFloatType& CellDensityCore;`
- L729 _public member_ `TFloatType& CellDevelopmentTime;`
- L730 _public member_ `TFloatType& LeafWeight;`
- L731 _public member_ `TFloatType& CellDensityInput;`
- L733 _public prototype_ `TDetailLateralElongationView() = delete;`
- L734 _public function_ `TDetailLateralElongationView(ArrayType& InData) : Array(TFixedSizeArrayHelper<TFloatType>::GetFixedArray(InData, DefaultData)) , Elongation(Array[0]) , SeedScaleEffect(Array[1]) , WhorledImpact(Array[2]) , CellDensityMin(Array[3]) , CellDensityMax(Array[4]) , CellDensityCore(Array[5]) , CellDevelopmentTime(Array[6]) , LeafWeight(Array[7]) , CellDensityInput(Array[8])`

#### Free symbols / members of external scopes

- L41 _namespace_ `namespace PV`
- L358 _function_ `template<typename... TAttributeViews> inline bool ValidateAttributeCollection(TAttributeViews... Attributes)` (scope `PV`) — Returns true if all attributes are valid, non-empty, and attributes sharing a group name have the same element count.
- L365 _function_ `` (scope `PV::ValidateAttributeCollection`)
- L395 _macro_ `#define PV_DEFINE_STRUCTURED_ATTRIBUTE(Name, Type, ElementViewType, ElementConstViewType, AttributeNameStr, AttributeGroupStr) \`
- L401 _macro_ `#define PV_DEFINE_ATTRIBUTE(Name, Type, AttributeNameStr, AttributeGroupStr) \`
- L405 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchParents, TArray<int32>, AttributeNames::BranchParentsStr, GroupNames::BranchGroupStr);` (scope `PV`) — Branch Attributes
- L406 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchChildren, TArray<int32>, AttributeNames::BranchChildrenStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L407 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchPoints, TArray<int32>, AttributeNames::BranchPointsStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L408 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchNumber, int32, AttributeNames::BranchNumberStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L409 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchSourceBudNumber, int32, AttributeNames::BranchSourceBudNumberStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L410 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchFoliageIDs, TArray<int32>, AttributeNames::BranchFoliageIDsStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L411 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchUVMaterial, int32, AttributeNames::BranchUVMaterialStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L412 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchHierarchyNumber, int32, AttributeNames::BranchHierarchyNumberStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L413 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchSimulationGroupIndex, int32, AttributeNames::BranchSimulationGroupIndexStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L414 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchPlantNumber, int32, AttributeNames::PlantNumberStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L415 _prototype_ `PV_DEFINE_ATTRIBUTE(BranchParentNumber, int32, AttributeNames::BranchParentNumberStr, GroupNames::BranchGroupStr);` (scope `PV`)
- L418 _prototype_ `PV_DEFINE_ATTRIBUTE(PointPosition, FVector3f, AttributeNames::PointPositionStr, GroupNames::PointGroupStr);` (scope `PV`) — Point Attributes
- L419 _prototype_ `PV_DEFINE_ATTRIBUTE(PointLengthFromRoot, float, AttributeNames::LengthFromRootStr, GroupNames::PointGroupStr);` (scope `PV`)
- L420 _prototype_ `PV_DEFINE_ATTRIBUTE(PointLengthFromSeed, float, AttributeNames::LengthFromSeedStr, GroupNames::PointGroupStr);` (scope `PV`)
- L421 _prototype_ `PV_DEFINE_ATTRIBUTE(PointScale, float, AttributeNames::PointScaleStr, GroupNames::PointGroupStr);` (scope `PV`)
- L422 _prototype_ `PV_DEFINE_ATTRIBUTE(PointTextureCoordV, float, AttributeNames::TextureCoordVStr, GroupNames::PointGroupStr);` (scope `PV`)
- L423 _prototype_ `PV_DEFINE_ATTRIBUTE(PointTextureCoordUOffset, float, AttributeNames::TextureCoordUOffsetStr, GroupNames::PointGroupStr);` (scope `PV`)
- L424 _prototype_ `PV_DEFINE_ATTRIBUTE(PointURange, FVector2f, AttributeNames::URangeStr, GroupNames::PointGroupStr);` (scope `PV`)
- L425 _prototype_ `PV_DEFINE_ATTRIBUTE(PointHullGradient, float, AttributeNames::HullGradientStr, GroupNames::PointGroupStr);` (scope `PV`)
- L426 _prototype_ `PV_DEFINE_ATTRIBUTE(PointMainTrunkGradient, float, AttributeNames::MainTrunkGradientStr, GroupNames::PointGroupStr);` (scope `PV`)
- L427 _prototype_ `PV_DEFINE_ATTRIBUTE(PointGroundGradient, float, AttributeNames::GroundGradientStr, GroupNames::PointGroupStr);` (scope `PV`)
- L428 _prototype_ `PV_DEFINE_ATTRIBUTE(PointScaleGradient, float, AttributeNames::PointScaleGradientStr, GroupNames::PointGroupStr);` (scope `PV`)
- L429 _prototype_ `PV_DEFINE_ATTRIBUTE(PointPlantGradient, float, AttributeNames::PlantGradientStr, GroupNames::PointGroupStr);` (scope `PV`)
- L430 _prototype_ `PV_DEFINE_ATTRIBUTE(PointBudNumber, int32, AttributeNames::BudNumberStr, GroupNames::PointGroupStr);` (scope `PV`)
- L431 _prototype_ `PV_DEFINE_ATTRIBUTE(PointNjordPixelIndex, float, AttributeNames::NjordPixelIndexStr, GroupNames::PointGroupStr);` (scope `PV`)
- L432 _prototype_ `PV_DEFINE_ATTRIBUTE(PointSeedPScale, float, AttributeNames::SeedPScaleStr, GroupNames::PointGroupStr);` (scope `PV`)
- L433 _prototype_ `PV_DEFINE_ATTRIBUTE(PointSeedPScaleRatio, float, AttributeNames::SeedPScaleRatioStr, GroupNames::PointGroupStr);` (scope `PV`)
- L458 _typedef_ `using FBudLightDetectedView = TBudLightDetectedView<float>;` (scope `PV`)
- L459 _typedef_ `using FBudLightDetectedConstView = TBudLightDetectedView<const float>;` (scope `PV`)
- L460 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(BudLightDetected, TArray<float>, FBudLightDetectedView, FBudLightDetectedConstView, AttributeNames::BudLightDetectedStr, GroupNames::PointGroupStr);` (scope `PV`)
- L491 _typedef_ `using FBudLateralMeristemView = TBudLateralMeristemView<float>;` (scope `PV`)
- L492 _typedef_ `using FBudLateralMeristemConstView = TBudLateralMeristemView<const float>;` (scope `PV`)
- L493 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(BudLateralMeristem, TArray<float>, FBudLateralMeristemView, FBudLateralMeristemConstView, AttributeNames::BudLateralMeristemStr, GroupNames::PointGroupStr);` (scope `PV`)
- L522 _typedef_ `using FBudHormoneLevelsView = TBudHormoneLevelsView<float>;` (scope `PV`)
- L523 _typedef_ `using FBudHormoneLevelsConstView = TBudHormoneLevelsView<const float>;` (scope `PV`)
- L524 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(BudHormoneLevels, TArray<float>, FBudHormoneLevelsView, FBudHormoneLevelsConstView, AttributeNames::BudHormoneLevelsStr, GroupNames::PointGroupStr);` (scope `PV`)
- L553 _typedef_ `using FBudDirectionView = TBudDirectionView<FVector3f>;` (scope `PV`)
- L554 _typedef_ `using FBudDirectionConstView = TBudDirectionView<const FVector3f>;` (scope `PV`)
- L555 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(BudDirection, TArray<FVector3f>, FBudDirectionView, FBudDirectionConstView, AttributeNames::BudDirectionStr, GroupNames::PointGroupStr);` (scope `PV`)
- L592 _typedef_ `using FBudStatusView = TBudStatusView<int32>;` (scope `PV`)
- L593 _typedef_ `using FBudStatusConstView = TBudStatusView<const int32>;` (scope `PV`)
- L594 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(BudStatus, TArray<int32>, FBudStatusView, FBudStatusConstView, AttributeNames::BudStatusStr, GroupNames::PointGroupStr);` (scope `PV`)
- L623 _typedef_ `using FBudDevelopmentView = TBudDevelopmentView<int32>;` (scope `PV`)
- L624 _typedef_ `using FBudDevelopmentConstView = TBudDevelopmentView<const int32>;` (scope `PV`)
- L625 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(BudDevelopment, TArray<int32>, FBudDevelopmentView, FBudDevelopmentConstView, AttributeNames::BudDevelopmentStr, GroupNames::PointGroupStr);` (scope `PV`)
- L628 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageNameID, int32, AttributeNames::FoliageNameIDStr, GroupNames::FoliageGroupStr);` (scope `PV`) — Foliage Attributes
- L629 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageBranchID, int32, AttributeNames::FoliageBranchIDStr, GroupNames::FoliageGroupStr);` (scope `PV`)
- L630 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliagePivotPoint, FVector3f, AttributeNames::FoliagePivotPointStr, GroupNames::FoliageGroupStr);` (scope `PV`)
- L631 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageUpVector, FVector3f, AttributeNames::FoliageUPVectorStr, GroupNames::FoliageGroupStr);` (scope `PV`)
- L632 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageNormalVector, FVector3f, AttributeNames::FoliageNormalVectorStr, GroupNames::FoliageGroupStr);` (scope `PV`)
- L633 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageScale, float, AttributeNames::FoliageScaleStr, GroupNames::FoliageGroupStr);` (scope `PV`)
- L634 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageLengthFromRoot, float, AttributeNames::FoliageLengthFromRootStr, GroupNames::FoliageGroupStr);` (scope `PV`)
- L635 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageParentBoneID, int32, AttributeNames::FoliageParentBoneIDStr, GroupNames::FoliageGroupStr);` (scope `PV`)
- L638 _prototype_ `PV_DEFINE_ATTRIBUTE(FoliageName, FString, AttributeNames::FoliageNameStr, GroupNames::FoliageNamesGroupStr);` (scope `PV`) — FoliageNames Attributes
- L641 _prototype_ `PV_DEFINE_ATTRIBUTE(DetailLeafPhyllotaxy, TArray<float>, AttributeNames::LeafPhyllotaxyStr, GroupNames::DetailsGroupStr);` (scope `PV`) — Details Attributes
- L642 _prototype_ `PV_DEFINE_ATTRIBUTE(DetailFoliagePath, FString, AttributeNames::FoliagePathStr, GroupNames::DetailsGroupStr);` (scope `PV`)
- L643 _prototype_ `PV_DEFINE_ATTRIBUTE(DetailGuid, FGuid, AttributeNames::GuidStr, GroupNames::DetailsGroupStr);` (scope `PV`)
- L674 _typedef_ `using FDetailLeafGrowthView = TDetailLeafGrowthView<float>;` (scope `PV`)
- L675 _typedef_ `using FDetailLeafGrowthConstView = TDetailLeafGrowthView<const float>;` (scope `PV`)
- L676 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(DetailLeafGrowth, TArray<float>, FDetailLeafGrowthView, FDetailLeafGrowthConstView, AttributeNames::LeafGrowthStr, GroupNames::DetailsGroupStr);` (scope `PV`)
- L711 _typedef_ `using FDetailAbscissionSenescenseView = TDetailAbscissionSenescenseView<float>;` (scope `PV`)
- L712 _typedef_ `using FDetailAbscissionSenescenseConstView = TDetailAbscissionSenescenseView<const float>;` (scope `PV`)
- L713 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(DetailAbscissionSenescense, TArray<float>, FDetailAbscissionSenescenseView, FDetailAbscissionSenescenseConstView, AttributeNames::AbscissionSenescenseStr, GroupNames::DetailsGroupStr);` (scope `PV`)
- L748 _typedef_ `using FDetailLateralElongationView = TDetailLateralElongationView<float>;` (scope `PV`)
- L749 _typedef_ `using FDetailLateralElongationConstView = TDetailLateralElongationView<const float>;` (scope `PV`)
- L750 _prototype_ `PV_DEFINE_STRUCTURED_ATTRIBUTE(DetailLateralElongation, TArray<float>, FDetailLateralElongationView, FDetailLateralElongationConstView, AttributeNames::LateralElongationStr, GroupNames::DetailsGroupStr);` (scope `PV`)
- L751 _prototype_ `PV_DEFINE_ATTRIBUTE(DetailTrunkURange, TArray<FVector2f>, AttributeNames::TrunkURangeStr, GroupNames::DetailsGroupStr);` (scope `PV`)
- L752 _prototype_ `PV_DEFINE_ATTRIBUTE(DetailTrunkMaterialPath, FString, AttributeNames::TrunkMaterialPathStr, GroupNames::DetailsGroupStr);` (scope `PV`)
- L755 _prototype_ `PV_DEFINE_ATTRIBUTE(ProfilePoints, TArray<float>, AttributeNames::ProfilePointsStr, GroupNames::PlantProfilesGroupStr);` (scope `PV`) — PlantProfiles Attributes
- L758 _prototype_ `PV_DEFINE_ATTRIBUTE(BoneName, FString, AttributeNames::BoneNameStr, GroupNames::BonesGroupStr);` (scope `PV`) — Bone Attributes
- L759 _prototype_ `PV_DEFINE_ATTRIBUTE(BoneParentIndex, int32, AttributeNames::BoneParentIndexStr, GroupNames::BonesGroupStr);` (scope `PV`)
- L760 _prototype_ `PV_DEFINE_ATTRIBUTE(BonePose, FTransform, AttributeNames::BonePoseStr, GroupNames::BonesGroupStr);` (scope `PV`)
- L761 _prototype_ `PV_DEFINE_ATTRIBUTE(BonePointIndex, int32, AttributeNames::BonePointIndexStr, GroupNames::BonesGroupStr);` (scope `PV`)
- L762 _prototype_ `PV_DEFINE_ATTRIBUTE(BoneAbsolutePosition, FVector3f, AttributeNames::BoneAbsolutePositionStr, GroupNames::BonesGroupStr);` (scope `PV`)
- L763 _prototype_ `PV_DEFINE_ATTRIBUTE(BoneBranchIndex, int32, AttributeNames::BoneBranchIndexStr, GroupNames::BonesGroupStr);` (scope `PV`)
- L764 _prototype_ `PV_DEFINE_ATTRIBUTE(BoneId, int32, AttributeNames::BoneIdStr, GroupNames::BonesGroupStr);` (scope `PV`)
- L767 _prototype_ `PV_DEFINE_ATTRIBUTE(VerticesPointIds, int32, AttributeNames::VertexPointIdsStr, GroupNames::VerticesGroupStr);` (scope `PV`) — VerticesGroup
- L770 _prototype_ `PV_DEFINE_ATTRIBUTE(LeafMeshPath, FString, AttributeNames::LeafMeshPathStr, GroupNames::LeafProxyMetaGroupStr);` (scope `PV`) — Leaf Meta Attributes (one element per plant; carries the leaf static mesh soft-object path)
- L773 _prototype_ `PV_DEFINE_ATTRIBUTE(LeafPosition, FVector3f, AttributeNames::PointPositionStr, GroupNames::LeafProxyGroupStr);` (scope `PV`) — Leaves Attributes (one element per leaf instance; stores the final-cycle spawn transform)
- L774 _prototype_ `PV_DEFINE_ATTRIBUTE(LeafRotation, FVector4f, AttributeNames::LeafRotationStr, GroupNames::LeafProxyGroupStr);` (scope `PV`)
- L775 _prototype_ `PV_DEFINE_ATTRIBUTE(LeafScale, float, AttributeNames::PointScaleStr, GroupNames::LeafProxyGroupStr);` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Private/Utils/PVDynamicMeshVertexAttribute.h` (Private)


#### class `PV::TDynamicMeshVertexAttributeExt`  
`template<typename AttribValueType> class TDynamicMeshVertexAttributeExt : public UE::Geometry::TDynamicMeshVertexAttribute<AttribValueType, 1>`  
_L13-99_
- inherits: `UE::Geometry::TDynamicMeshVertexAttribute<AttribValueType,1>`
- L17 _public typedef_ `using Super = UE::Geometry::TDynamicMeshVertexAttribute<AttribValueType, 1>;`
- L19 _public function_ `TDynamicMeshVertexAttributeExt() : Super()`
- L20 _public function_ `TDynamicMeshVertexAttributeExt(UE::Geometry::FDynamicMesh3* ParentIn, bool bAutoInit = true) : Super(ParentIn, bAutoInit)`
- L22 _public function_ `inline AttribValueType GetValue(int32 VertexID) const`
- L29 _public function_ `inline void SetValue(int32 VertexID, const AttribValueType& NewValue)`
- L35 _public function_ `template <typename Predicate, typename Iteratable> TArray<int32> FindAllByPredicate(Predicate Pred, const Iteratable& InIteratable) const`
- L58 _public function_ `TArray<int32> FindAllNonZero() const`
- L71 _public function_ `TArray<int32> FindAllZero() const`
- L84 _public function_ `TArray<int32> FindAllNonZero(const TArray<int32>& InVertexIDsToSearch) const`
- L92 _public function_ `TArray<int32> FindAllZero(const TArray<int32>& InVertexIDsToSearch) const`

#### class `PV::TDynamicMeshVertexAttributeDefinition`  
`template<typename T> class TDynamicMeshVertexAttributeDefinition`  
_L102-202_
- L105 _public typedef_ `using FAttributeType = TDynamicMeshVertexAttributeExt<T>;`
- L107 _public member_ `const FName AttributeName;`
- L109 _public function_ `TDynamicMeshVertexAttributeDefinition(FName InAttributeName) : AttributeName(InAttributeName)`
- L114 _public function_ `const FAttributeType* GetAttribute(const UE::Geometry::FDynamicMesh3& DynamicMesh) const`
- L123 _public function_ `FAttributeType* GetAttribute(UE::Geometry::FDynamicMesh3& DynamicMesh) const`
- L132 _public function_ `const FAttributeType& GetAttributeChecked(const UE::Geometry::FDynamicMesh3& DynamicMesh) const`
- L139 _public function_ `FAttributeType& GetAttributeChecked(UE::Geometry::FDynamicMesh3& DynamicMesh) const`
- L146 _public function_ `FAttributeType& GetOrAttachAttribute(UE::Geometry::FDynamicMesh3& DynamicMesh) const`
- L157 _public function_ `void AttachAttribute(UE::Geometry::FDynamicMesh3& DynamicMesh) const`
- L172 _public function_ `void CopyAttributeToCollection(const UE::Geometry::FDynamicMesh3& DynamicMesh, FManagedArrayCollection& OutCollection) const`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PV`
- L66 _function_ `[](const auto& Value)` (scope `PV::TDynamicMeshVertexAttributeExt::FindAllNonZero`)
- L79 _function_ `[](const auto& Value)` (scope `PV::TDynamicMeshVertexAttributeExt::FindAllZero`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVData.h` (Public)


#### enum `EPVRenderType`  
`enum class EPVRenderType : uint16`  
_L18-36_
- reflection: `UENUM()`
- L20 _public enumerator_ `None = 0`
- L21 _public enumerator_ `PointData = 1 << 0`
- L22 _public enumerator_ `Mesh = 1 << 1`
- L23 _public enumerator_ `Foliage = 1 << 2`
- L24 _public enumerator_ `Bones = 1 << 3`
- L25 _public enumerator_ `FoliageGrid = 1 << 4`
- L26 _public enumerator_ `FoliageAttachments = 1 << 5`
- L27 _public enumerator_ `Seed = 1 << 6`
- L28 _public enumerator_ `Textures = 1 << 7`
- L29 _public enumerator_ `Leaf = 1 << 8`
- L30 _public enumerator_ `GrafterGrid = 1 << 9`
- L31 _public enumerator_ `PlantProfile = 1 << 10`
- L32 _public enumerator_ `BoundingBoxOnly = 1 << 11`
- L35 _public enumerator_ `Count` — Add new renter type above

#### enum `EPVDebugType`  
`enum class EPVDebugType`  
_L41-47_
- reflection: `UENUM()`
- L43 _public enumerator_ `Point`
- L44 _public enumerator_ `Branches`
- L45 _public enumerator_ `Foliage`
- L46 _public enumerator_ `Custom`

#### enum `EPVDebugValueVisualizationMode`  
`enum class EPVDebugValueVisualizationMode`  
_L50-59_
- reflection: `UENUM()`
- L52 _public enumerator_ `Text`
- L53 _public enumerator_ `Direction`
- L54 _public enumerator_ `Sphere`
- L55 _public enumerator_ `Vector`
- L56 _public enumerator_ `Point`
- L57 _public enumerator_ `Curve`
- L58 _public enumerator_ `ColorRamp`

#### struct `FPVVisualizationSettings`  
`struct FPVVisualizationSettings`  
_L62-139_
- reflection: `USTRUCT()`
- L67 _public member_ `EPVDebugType DebugType = EPVDebugType::Point;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L70 _public member_ `bool bShow = true;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L73 _public member_ `bool bShowAnchorPoints = true;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L76 _public member_ `bool bDrawPointAsMesh = true;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "VisualizationMode==EPVDebugValueVisualizationMode::Point || bShowAnchorPoints"))`
- L79 _public member_ `bool bDrawSphereAsMesh = false;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "VisualizationMode==EPVDebugValueVisualizationMode::Sphere"))`
- L83 _public member_ `bool bUsePivotAsPosition = false;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "DebugType==EPVDebugType::Custom && VisualizationMode==EPVDebugValueVisualizationMode::Point"))` — If true, then the AttributeToFilter will be used as point scale and the CustomPivotPositionAttributeName will be used for the point position. If false then AttributeToFilter is used for position and pivot attribute is ignored.
- L86 _public member_ `FName AttributeToFilter;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L89 _public member_ `FName CustomGroupToFilter = TEXT("Cus` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "DebugType==EPVDebugType::Custom"))`
- L92 _public member_ `FName CustomPivotPositionAttributeName = TEXT("Pos` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "DebugType==EPVDebugType::Custom && VisualizationMode != EPVDebugValueVisualizationMode::Curve && (VisualizationMode != EPVDebugValueVisualizationMode::Point || bUsePivotAsPosition)"))`
- L95 _public member_ `FName CustomPivotScaleAttributeName = TEXT("Sca` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "DebugType==EPVDebugType::Custom && VisualizationMode != EPVDebugValueVisualizationMode::Curve && (VisualizationMode != EPVDebugValueVisualizationMode::Point || bUsePivotAsPosition)"))`
- L98 _public member_ `EPVDebugValueVisualizationMode VisualizationMode = EPVDebugValueVisualizationMode::Text;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L101 _public member_ `bool bRandomizeColors = false;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L104 _public member_ `FColor Color = FColor::Black;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "!bRandomizeColors"))`
- L107 _public member_ `float AnchorPointsScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "bShowAnchorPoints"))`
- L110 _public member_ `float TextScale = 2.5f;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "VisualizationMode==EPVDebugValueVisualizationMode::Text"))`
- L113 _public member_ `FVector3f TextOffset = FVector3f::Zero();` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta = (EditCondition = "VisualizationMode==EPVDebugValueVisualizationMode::Text"))`
- L116 _public member_ `float GizmoScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L119 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriorityGroup = ESceneDepthPriorityGroup::SDPG_World;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L121 _public function_ `FName GetGroupToFilter() const`

#### struct `FPVParamDebugData`  
`struct FPVParamDebugData`  
_L142-154_
- reflection: `USTRUCT()`
- L147 _public member_ `FVector Pivot = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = DebugData)`
- L150 _public member_ `TOptional<FVector> Direction;` — `UPROPERTY(EditAnywhere, Category = DebugData)`
- L153 _public member_ `TOptional<FText> TextData;` — `UPROPERTY(EditAnywhere, Category = DebugData)`

#### struct `FPVParamDebuggerSettings`  
`struct FPVParamDebuggerSettings`  
_L157-169_
- reflection: `USTRUCT()`
- L162 _public member_ `EPVDebugValueVisualizationMode VisualizationMode = EPVDebugValueVisualizationMode::Text;` — `UPROPERTY(EditAnywhere, Category = LoopDebugSettings)`
- L165 _public member_ `FText ParamName;` — `UPROPERTY(EditAnywhere, Category = LoopDebugSettings)`
- L168 _public member_ `FPVParamDebugData Data;` — `UPROPERTY(EditAnywhere, Category = LoopDebugSettings)`

#### struct `FPVDebugSettings`  
`struct FPVDebugSettings`  
_L172-183_
- reflection: `USTRUCT()`
- L177 _public member_ `TArray<FPVVisualizationSettings> VisualizationSettings;` — `UPROPERTY(EditAnywhere, Category = DebugSettings)`
- L180 _public member_ `TArray<FPVParamDebuggerSettings> ParamDebugVisualizationSettings;` — `UPROPERTY()`
- L182 _public member_ `bool bAutoFocusLoopDebug = false;`

#### struct `FPVVisualizationCollection`  
`struct FPVVisualizationCollection`  
_L185-189_
- L187 _public member_ `FManagedArrayCollection Collection;`
- L188 _public member_ `TArray<FPVVisualizationSettings> VisualizationSettings;`

#### struct `FPVSettingsVisualization`  
`struct FPVSettingsVisualization`  
_L192-201_
- reflection: `USTRUCT()`
- L197 _public member_ `FPVDebugSettings DebugSettings;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta=(EditConditionHides))`
- L200 _public member_ `TArray<EPVRenderType> CurrentRenderType;` — `UPROPERTY()`

#### class `UPVData`  
`class UPVData : public UPCGSpatialData`  
_L204-277_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSpatialData`
- L209 _public prototype_ `UPVData(const FObjectInitializer& ObjectInitializer);`
- L211 _public prototype_ `void Initialize(FManagedArrayCollection&& InCollection);`
- L212 _public prototype_ `void Initialize(FGeometryCollection&&) = delete;`
- L213 _public prototype_ `void Initialize(FTransformCollection&&) = delete;`
- L216 _public function_ `virtual EPCGDataType GetDataType() const override`
- L217 _public prototype_ `virtual void AddToCrc(FArchiveCrc32& Ar, bool bFullDataCrc) const override;`
- L221 _public function_ `virtual int GetDimension() const override`
- L222 _public prototype_ `virtual FBox GetBounds() const override;`
- L223 _public prototype_ `virtual bool SamplePoint(const FTransform& Transform, const FBox& Bounds, FPCGPoint& OutPoint, UPCGMetadata* OutMetadata) const override;`
- L226 _public function_ `const FManagedArrayCollection& GetCollection() const`
- L227 _public function_ `FManagedArrayCollection& GetCollection()`
- L228 _public function_ `TSharedPtr<FManagedArrayCollection>& GetSharedCollection()`
- L229 _public function_ `const TSharedPtr<FManagedArrayCollection>& GetSharedCollection() const`
- L231 _public function_ `void AddManagedResource(const UObject* InResource)`
- L240 _public prototype_ `void AddVisualizationCollection(FManagedArrayCollection InCollection, TArray<FPVVisualizationSettings> InVisualizationSettings = {});`
- L241 _public prototype_ `void SetDebugSettings(const FPVDebugSettings& InSettings) const;`
- L242 _public prototype_ `void SetDebugSettings(FPVDebugSettings&& InSettings) const;`
- L243 _public prototype_ `FPVDebugSettings GetDebugSettings() const;`
- L244 _public function_ `const TArray<FPVVisualizationCollection>& GetVisualizationCollections() const`
- L250 _protected function_ `virtual bool SupportsFullDataCrc() const override`
- L254 _protected prototype_ `virtual UPCGSpatialData* CopyInternal(FPCGContext* Context) const override;`
- L256 _public prototype_ `virtual const UPCGPointData* ToPointData(FPCGContext* Context, const FBox& InBounds) const override;`
- L257 _public prototype_ `virtual const UPCGPointArrayData* ToPointArrayData(FPCGContext* Context, const FBox& InBounds) const override;`
- L262 _private prototype_ `const UPCGBasePointData* ToBasePointData(FPCGContext* Context, const FBox& InBounds, TSubclassOf<UPCGBasePointData> PointDataClass) const;`
- L266 _protected member_ `TSharedPtr<FManagedArrayCollection> Collection;`
- L269 _protected member_ `TArray<TObjectPtr<const UObject>> ManagedResources;` — `UPROPERTY(Transient)`
- L272 _protected member_ `mutable FCriticalSection DebugSettingsMutex;`
- L273 _protected member_ `mutable FPVDebugSettings DebugSettings;`
- L275 _protected member_ `TArray<FPVVisualizationCollection> VisualizationCollections;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVFoliageData.h` (Public)


#### struct `FPVDataTypeInfoFoliage`  
`struct FPVDataTypeInfoFoliage : public FPCGDataTypeInfo`  
_L9-19_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L13 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L17 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVFoliageData`  
`class UPVFoliageData : public UPVData`  
_L22-30_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVData`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVFoliageInfo.h` (Public)


#### struct `FPVDistributionConditions`  
`struct FPVDistributionConditions`  
_L12-50_
- reflection: `USTRUCT()`
- L17 _public member_ `float Light = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Preferred light exposure at the placement point. 0 = shaded, 1 = fully lit."))`
- L20 _public member_ `float Scale = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Preferred normalized branch scale at the placement point. 0 = thin/small, 1 = thick/large."))`
- L23 _public member_ `float UpAlignment = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Preferred alignment of the branch with world up. 0 = horizontal, 1 = vertical."))`
- L26 _public member_ `float Health = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Preferred branch health at the placement point. 0 = unhealthy, 1 = healthy."))`
- L29 _public member_ `bool Tip = false;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(Tooltip="When enabled, this entry is only placed on branch tips."))`
- L32 _public member_ `float Height = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Preferred normalized height along the plant. 0 = base, 1 = top."))`
- L35 _public member_ `float Generation = 0.0f;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ClampMin=0.0f, ClampMax=1.0f, UIMin=0.0f, UIMax=1.0f, Tooltip="Preferred branch generation (sub-branch depth) at the placement point. 0 = trunk, 1 = furthest sub-branches."))`
- L37 _public function_ `FString ToString() const`

#### struct `FPVFoliageInfo`  
`struct FPVFoliageInfo`  
_L53-72_
- reflection: `USTRUCT()`
- L58 _public member_ `bool bUseAsMask = false;` — `UPROPERTY(EditAnywhere, Category = "Info", meta=(Tooltip="When enabled, this entry acts as a placement mask only — no mesh is spawned. Use to reserve slots driven by distribution conditions."))`
- L61 _public member_ `TSoftObjectPtr<UObject> Mesh;` — `UPROPERTY(EditAnywhere, Category = "Info", meta = (EditCondition="!bUseAsMask", EditConditionHides, AllowedClasses = "/Script/Engine.StaticMesh,/Script/Engine.SkeletalMesh", Tooltip="Static Mesh or Skeletal Mesh placed at points matched by this entry's Attributes."))`
- L64 _public member_ `FPVDistributionConditions Attributes;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ShowInnerProperties, FullyExpand="true", Tooltip="Target values (0–1) used by the Foliage Distributor to pick this entry: the distributor selects the foliage whose Attributes are closest to each point's sampled values."))`
- L66 _public function_ `bool IsValid() const`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVGraftInfo.h` (Public)


#### struct `FPVGraftInfo`  
`struct FPVGraftInfo`  
_L11-20_
- reflection: `USTRUCT()`
- L16 _public member_ `bool bUseAsMask = false;` — `UPROPERTY(EditAnywhere, Category = "Info", meta=(Tooltip="When enabled, this entry acts as a placement mask only — no graft is spawned and its input pin is hidden. Use to block attachment points matching these conditions without spawning a graft"))`
- L19 _public member_ `FPVDistributionConditions Attributes;` — `UPROPERTY(EditAnywhere, Category="Info", meta=(ShowInnerProperties, FullyExpand="true", Tooltip="Target values (0–1) used by the Graft Distributor to pick this entry: the distributor selects the entry whose Attributes are closest to each attachment point's sampled values."))`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVGrafterPaletteData.h` (Public)


#### struct `FPVDataTypeInfoGrafterPalette`  
`struct FPVDataTypeInfoGrafterPalette : public FPCGDataTypeInfo`  
_L10-20_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L14 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L18 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrafterPaletteData`  
`class UPVGrafterPaletteData : public UPVData`  
_L23-54_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVData`
- L29 _public prototype_ `PCG_ASSIGN_DEFAULT_TYPE_INFO(FPVDataTypeInfoGrafterPalette)`
- L34 _public prototype_ `void Initialize(FManagedArrayCollection&&) = delete;` — Prevent callers from using the base initializer, which would leave GrowthDataElements unpopulated.
- L37 _public prototype_ `virtual void AddToCrc(FArchiveCrc32& Ar, bool bFullDataCrc) const override;`
- L40 _public function_ `const TArray<TObjectPtr<UPVGrowthData>>& GetGrowthDataElements() const`
- L41 _public function_ `TArray<TObjectPtr<UPVGrowthData>>& GetGrowthDataElements()`
- L45 _protected function_ `virtual bool SupportsFullDataCrc() const override`
- L49 _protected prototype_ `virtual UPCGSpatialData* CopyInternal(FPCGContext* Context) const override;`
- L53 _protected member_ `TArray<TObjectPtr<UPVGrowthData>> GrowthDataElements;` — `UPROPERTY()`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVGrowthData.h` (Public)


#### struct `FPVDataTypeInfoGrowth`  
`struct FPVDataTypeInfoGrowth : public FPCGDataTypeInfo`  
_L11-21_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L15 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L19 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVGrowthData`  
`class UPVGrowthData : public UPVData`  
_L24-32_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVData`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVMeshData.h` (Public)


#### struct `FPVDataTypeInfoMesh`  
`struct FPVDataTypeInfoMesh : public FPCGDataTypeInfo`  
_L10-20_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L14 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L18 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVMeshData`  
`class UPVMeshData : public UPVData`  
_L23-31_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVData`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVPlantProfileData.h` (Public)


#### struct `FPVDataTypeInfoPlantProfile`  
`struct FPVDataTypeInfoPlantProfile : public FPCGDataTypeInfo`  
_L9-19_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L13 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L17 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVPlantProfileData`  
`class UPVPlantProfileData : public UPVData`  
_L22-30_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVData`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/DataTypes/PVTrunkTextureSetupData.h` (Public)


#### enum `EPVTextureChannel`  
`enum class EPVTextureChannel : uint8`  
_L12-24_
- reflection: `UENUM()`
- L14 _public enumerator_ `BaseColor`
- L15 _public enumerator_ `AO`
- L16 _public enumerator_ `Normal`
- L17 _public enumerator_ `Displacement`
- L18 _public enumerator_ `Bump`
- L19 _public enumerator_ `Cavity`
- L20 _public enumerator_ `Gloss`
- L21 _public enumerator_ `Roughness`
- L22 _public enumerator_ `Specular`
- L23 _public enumerator_ `Custom`

#### struct `FPVGenerationUVRange`  
`struct FPVGenerationUVRange`  
_L27-41_
- reflection: `USTRUCT()`
- L32 _public member_ `float OffsetXStart = 0.0f;` — `UPROPERTY()`
- L35 _public member_ `float OffsetXEnd = 1.0f;` — `UPROPERTY()`
- L38 _public member_ `float DilationFactor = 0.0f;` — `UPROPERTY()`
- L40 _public function_ `inline float GetOverflowValue() const`

#### struct `FPVTrunkTextureSetupInfo`  
`struct FPVTrunkTextureSetupInfo`  
_L44-64_
- reflection: `USTRUCT()`
- L49 _public member_ `TMap<FString, TObjectPtr<UTexture>> Channels;` — `UPROPERTY()`
- L52 _public member_ `TArray<FPVGenerationUVRange> GenerationUVs;` — `UPROPERTY()`
- L55 _public member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY()`
- L58 _public member_ `int Resolution = 1024;` — `UPROPERTY()`
- L61 _public member_ `FString PreviewChannelName;` — `UPROPERTY()`
- L63 _public prototype_ `bool IsOverflowing() const;`

#### struct `FPVDataTypeInfoTrunkTextureSetup`  
`struct FPVDataTypeInfoTrunkTextureSetup : public FPCGDataTypeInfo`  
_L67-77_
- reflection: `USTRUCT()`
- inherits: `FPCGDataTypeInfo`
- L71 _public prototype_ `PCG_DECLARE_TYPE_INFO();`
- L75 _public function_ `virtual bool Hidden() const override` — If the type should be hidden to the user.

#### class `UPVTrunkTextureSetupData`  
`class UPVTrunkTextureSetupData : public UPVData`  
_L80-93_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVData`
- L86 _public member_ `FPVTrunkTextureSetupInfo TrunkTextureSetupInfo;` — `UPROPERTY()`
- L88 _public prototype_ `PCG_ASSIGN_DEFAULT_TYPE_INFO(FPVDataTypeInfoTrunkTextureSetup) virtual void AddToCrc(FArchiveCrc32& Ar, bool bFullDataCrc) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/IShrinkableFacade.h` (Public)


#### class `PV::Facades::IShrinkable`  
`class IShrinkable`  
_L13-63_
- desc: Any Facade can implement IShrinkable to provide capability of removing arbitrary elements from the underlying Collection/Group in an optimal way.
- L16 _public prototype_ `virtual ~IShrinkable() = default;`
- L18 _public prototype_ `virtual int32 GetElementCount() const = 0;`
- L20 _public prototype_ `virtual void CopyEntry(int32 FromIndex, int32 ToIndex) = 0;`
- L22 _public prototype_ `virtual void RemoveEntries(int32 NumEntries, int32 StartIndex) = 0;`
- L24 _public function_ `static TMap<int32, int32> RemoveEntries(IShrinkable& FacadeOut, TArray<bool>& EntriesToRemove)`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PV`
- L7 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVAttributesNames.h` (Public)


#### Free symbols / members of external scopes

- L6 _namespace_ `namespace PV`
- L6 _namespace_ `namespace GroupNames` (scope `PV`)
- L9 _variable_ `inline constexpr TCHAR BranchGroupStr[] = TEXT("Pri` (scope `PV::GroupNames`) — Group Names
- L10 _variable_ `inline constexpr TCHAR PointGroupStr[] = TEXT("Poi` (scope `PV::GroupNames`)
- L11 _variable_ `inline constexpr TCHAR FoliageGroupStr[] = TEXT("Fol` (scope `PV::GroupNames`)
- L12 _variable_ `inline constexpr TCHAR FoliageNamesGroupStr[] = TEXT("Fol` (scope `PV::GroupNames`)
- L13 _variable_ `inline constexpr TCHAR DetailsGroupStr[] = TEXT("Det` (scope `PV::GroupNames`)
- L14 _variable_ `inline constexpr TCHAR PlantProfilesGroupStr[] = TEXT("Pla` (scope `PV::GroupNames`)
- L15 _variable_ `inline constexpr TCHAR BonesGroupStr[] = TEXT("Bon` (scope `PV::GroupNames`)
- L16 _variable_ `inline constexpr TCHAR VerticesGroupStr[] = TEXT("Ver` (scope `PV::GroupNames`)
- L18 _variable_ `inline static const FName BranchGroup = FName(BranchGroupStr);` (scope `PV::GroupNames`)
- L19 _variable_ `inline static const FName PointGroup = FName(PointGroupStr);` (scope `PV::GroupNames`)
- L20 _variable_ `inline static const FName FoliageGroup = FName(FoliageGroupStr);` (scope `PV::GroupNames`)
- L21 _variable_ `inline static const FName FoliageNamesGroup = FName(FoliageNamesGroupStr);` (scope `PV::GroupNames`)
- L22 _variable_ `inline static const FName DetailsGroup = FName(DetailsGroupStr);` (scope `PV::GroupNames`)
- L23 _variable_ `inline static const FName PlantProfilesGroup = FName(PlantProfilesGroupStr);` (scope `PV::GroupNames`)
- L24 _variable_ `inline static const FName BonesGroup = FName(BonesGroupStr);` (scope `PV::GroupNames`)
- L25 _variable_ `inline static const FName VerticesGroup = FName(VerticesGroupStr);` (scope `PV::GroupNames`)
- L28 _variable_ `inline constexpr TCHAR LeafProxyMetaGroupStr[] = TEXT("Lea` (scope `PV::GroupNames`) — Leaf instance groups (final-cycle spawn data written by FPVGrower::FillCollection)
- L29 _variable_ `inline constexpr TCHAR LeafProxyGroupStr[] = TEXT("Lea` (scope `PV::GroupNames`)
- L30 _variable_ `inline static const FName LeafMetaGroup = FName(LeafProxyMetaGroupStr);` (scope `PV::GroupNames`)
- L31 _variable_ `inline static const FName LeavesGroup = FName(LeafProxyGroupStr);` (scope `PV::GroupNames`)
- L34 _namespace_ `namespace PV`
- L34 _namespace_ `namespace AttributeNames` (scope `PV`)
- L37 _variable_ `inline constexpr TCHAR BranchParentsStr[] = TEXT("par` (scope `PV::AttributeNames`) — Branch Attributes
- L38 _variable_ `inline constexpr TCHAR BranchChildrenStr[] = TEXT("chi` (scope `PV::AttributeNames`)
- L39 _variable_ `inline constexpr TCHAR BranchPointsStr[] = TEXT("Poi` (scope `PV::AttributeNames`)
- L40 _variable_ `inline constexpr TCHAR BranchNumberStr[] = TEXT("bra` (scope `PV::AttributeNames`)
- L41 _variable_ `inline constexpr TCHAR BranchSourceBudNumberStr[] = TEXT("bra` (scope `PV::AttributeNames`)
- L42 _variable_ `inline constexpr TCHAR BranchFoliageIDsStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L43 _variable_ `inline constexpr TCHAR BranchUVMaterialStr[] = TEXT("bra` (scope `PV::AttributeNames`)
- L44 _variable_ `inline constexpr TCHAR TrunkMaterialPathStr[] = TEXT("Tru` (scope `PV::AttributeNames`)
- L45 _variable_ `inline constexpr TCHAR TrunkURangeStr[] = TEXT("Tru` (scope `PV::AttributeNames`)
- L46 _variable_ `inline constexpr TCHAR BranchHierarchyNumberStr[] = TEXT("bra` (scope `PV::AttributeNames`)
- L47 _variable_ `inline constexpr TCHAR BranchSimulationGroupIndexStr[] = TEXT("bra` (scope `PV::AttributeNames`)
- L48 _variable_ `inline constexpr TCHAR PlantNumberStr[] = TEXT("pla` (scope `PV::AttributeNames`)
- L49 _variable_ `inline constexpr TCHAR BranchParentNumberStr[] = TEXT("bra` (scope `PV::AttributeNames`)
- L51 _variable_ `inline static const FName BranchParents = FName(BranchParentsStr);` (scope `PV::AttributeNames`)
- L52 _variable_ `inline static const FName BranchChildren = FName(BranchChildrenStr);` (scope `PV::AttributeNames`)
- L53 _variable_ `inline static const FName BranchPoints = FName(BranchPointsStr);` (scope `PV::AttributeNames`)
- L54 _variable_ `inline static const FName BranchNumber = FName(BranchNumberStr);` (scope `PV::AttributeNames`)
- L55 _variable_ `inline static const FName BranchSourceBudNumber = FName(BranchSourceBudNumberStr);` (scope `PV::AttributeNames`)
- L56 _variable_ `inline static const FName BranchFoliageIDs = FName(BranchFoliageIDsStr);` (scope `PV::AttributeNames`)
- L57 _variable_ `inline static const FName BranchUVMaterial = FName(BranchUVMaterialStr);` (scope `PV::AttributeNames`)
- L58 _variable_ `inline static const FName TrunkMaterialPath = FName(TrunkMaterialPathStr);` (scope `PV::AttributeNames`)
- L59 _variable_ `inline static const FName TrunkURange = FName(TrunkURangeStr);` (scope `PV::AttributeNames`)
- L60 _variable_ `inline static const FName BranchHierarchyNumber = FName(BranchHierarchyNumberStr);` (scope `PV::AttributeNames`)
- L61 _variable_ `inline static const FName BranchSimulationGroupIndex = FName(BranchSimulationGroupIndexStr);` (scope `PV::AttributeNames`)
- L62 _variable_ `inline static const FName PlantNumber = FName(PlantNumberStr);` (scope `PV::AttributeNames`)
- L63 _variable_ `inline static const FName BranchParentNumber = FName(BranchParentNumberStr);` (scope `PV::AttributeNames`)
- L66 _variable_ `inline constexpr TCHAR PointPositionStr[] = TEXT("Pos` (scope `PV::AttributeNames`) — Point Attributes
- L67 _variable_ `inline constexpr TCHAR LengthFromRootStr[] = TEXT("len` (scope `PV::AttributeNames`)
- L68 _variable_ `inline constexpr TCHAR PointScaleGradientStr[] = TEXT("LOD` (scope `PV::AttributeNames`)
- L69 _variable_ `inline constexpr TCHAR PointScaleStr[] = TEXT("Sca` (scope `PV::AttributeNames`)
- L70 _variable_ `inline constexpr TCHAR LengthFromSeedStr[] = TEXT("len` (scope `PV::AttributeNames`)
- L71 _variable_ `inline constexpr TCHAR SeedPScaleStr[] = TEXT("see` (scope `PV::AttributeNames`)
- L72 _variable_ `inline constexpr TCHAR SeedPScaleRatioStr[] = TEXT("see` (scope `PV::AttributeNames`)
- L73 _variable_ `inline constexpr TCHAR BudLightDetectedStr[] = TEXT("bud` (scope `PV::AttributeNames`)
- L74 _variable_ `inline constexpr TCHAR BudDevelopmentStr[] = TEXT("bud` (scope `PV::AttributeNames`)
- L75 _variable_ `inline constexpr TCHAR BudLateralMeristemStr[] = TEXT("bud` (scope `PV::AttributeNames`)
- L76 _variable_ `inline constexpr TCHAR TextureCoordVStr[] = TEXT("uv_` (scope `PV::AttributeNames`)
- L77 _variable_ `inline constexpr TCHAR TextureCoordUOffsetStr[] = TEXT("uv_` (scope `PV::AttributeNames`)
- L78 _variable_ `inline constexpr TCHAR URangeStr[] = TEXT("uv_` (scope `PV::AttributeNames`)
- L79 _variable_ `inline constexpr TCHAR HullGradientStr[] = TEXT("LOD` (scope `PV::AttributeNames`)
- L80 _variable_ `inline constexpr TCHAR MainTrunkGradientStr[] = TEXT("LOD` (scope `PV::AttributeNames`)
- L81 _variable_ `inline constexpr TCHAR GroundGradientStr[] = TEXT("LOD` (scope `PV::AttributeNames`)
- L82 _variable_ `inline constexpr TCHAR BudNumberStr[] = TEXT("bud` (scope `PV::AttributeNames`)
- L83 _variable_ `inline constexpr TCHAR BudHormoneLevelsStr[] = TEXT("bud` (scope `PV::AttributeNames`)
- L84 _variable_ `inline constexpr TCHAR BudDirectionStr[] = TEXT("bud` (scope `PV::AttributeNames`)
- L85 _variable_ `inline constexpr TCHAR BudStatusStr[] = TEXT("bud` (scope `PV::AttributeNames`)
- L86 _variable_ `inline constexpr TCHAR PlantGradientStr[] = TEXT("pla` (scope `PV::AttributeNames`)
- L87 _variable_ `inline constexpr TCHAR NjordPixelIndexStr[] = TEXT("njo` (scope `PV::AttributeNames`)
- L89 _variable_ `inline static const FName PointPosition = FName(PointPositionStr);` (scope `PV::AttributeNames`)
- L90 _variable_ `inline static const FName LengthFromRoot = FName(LengthFromRootStr);` (scope `PV::AttributeNames`)
- L91 _variable_ `inline static const FName PointScaleGradient = FName(PointScaleGradientStr);` (scope `PV::AttributeNames`)
- L92 _variable_ `inline static const FName PointScale = FName(PointScaleStr);` (scope `PV::AttributeNames`)
- L93 _variable_ `inline static const FName LengthFromSeed = FName(LengthFromSeedStr);` (scope `PV::AttributeNames`)
- L94 _variable_ `inline static const FName BudLightDetected = FName(BudLightDetectedStr);` (scope `PV::AttributeNames`)
- L95 _variable_ `inline static const FName BudDevelopment = FName(BudDevelopmentStr);` (scope `PV::AttributeNames`)
- L96 _variable_ `inline static const FName BudLateralMeristem = FName(BudLateralMeristemStr);` (scope `PV::AttributeNames`)
- L97 _variable_ `inline static const FName TextureCoordV = FName(TextureCoordVStr);` (scope `PV::AttributeNames`)
- L98 _variable_ `inline static const FName TextureCoordUOffset = FName(TextureCoordUOffsetStr);` (scope `PV::AttributeNames`)
- L99 _variable_ `inline static const FName URange = FName(URangeStr);` (scope `PV::AttributeNames`)
- L100 _variable_ `inline static const FName HullGradient = FName(HullGradientStr);` (scope `PV::AttributeNames`)
- L101 _variable_ `inline static const FName MainTrunkGradient = FName(MainTrunkGradientStr);` (scope `PV::AttributeNames`)
- L102 _variable_ `inline static const FName GroundGradient = FName(GroundGradientStr);` (scope `PV::AttributeNames`)
- L103 _variable_ `inline static const FName BudNumber = FName(BudNumberStr);` (scope `PV::AttributeNames`)
- L104 _variable_ `inline static const FName BudHormoneLevels = FName(BudHormoneLevelsStr);` (scope `PV::AttributeNames`)
- L105 _variable_ `inline static const FName BudDirection = FName(BudDirectionStr);` (scope `PV::AttributeNames`)
- L106 _variable_ `inline static const FName BudStatus = FName(BudStatusStr);` (scope `PV::AttributeNames`)
- L107 _variable_ `inline static const FName PlantGradient = FName(PlantGradientStr);` (scope `PV::AttributeNames`)
- L108 _variable_ `inline static const FName NjordPixelIndex = FName(NjordPixelIndexStr);` (scope `PV::AttributeNames`)
- L110 _variable_ `inline static const FName SeedPScale = FName(SeedPScaleStr);` (scope `PV::AttributeNames`)
- L111 _variable_ `inline static const FName SeedPScaleRatio = FName(SeedPScaleRatioStr);` (scope `PV::AttributeNames`)
- L115 _variable_ `inline constexpr TCHAR FoliageNameIDStr[] = TEXT("Fol` (scope `PV::AttributeNames`) — Foliage Attributes
- L116 _variable_ `inline constexpr TCHAR FoliageBranchIDStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L117 _variable_ `inline constexpr TCHAR FoliagePivotPointStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L118 _variable_ `inline constexpr TCHAR FoliageUPVectorStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L119 _variable_ `inline constexpr TCHAR FoliageNormalVectorStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L120 _variable_ `inline constexpr TCHAR FoliageScaleStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L121 _variable_ `inline constexpr TCHAR FoliageLengthFromRootStr[] = TEXT("Len` (scope `PV::AttributeNames`)
- L122 _variable_ `inline constexpr TCHAR FoliageParentBoneIDStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L124 _variable_ `inline static const FName FoliageNameID = FName(FoliageNameIDStr);` (scope `PV::AttributeNames`)
- L125 _variable_ `inline static const FName FoliageBranchID = FName(FoliageBranchIDStr);` (scope `PV::AttributeNames`)
- L126 _variable_ `inline static const FName FoliagePivotPoint = FName(FoliagePivotPointStr);` (scope `PV::AttributeNames`)
- L127 _variable_ `inline static const FName FoliageUPVector = FName(FoliageUPVectorStr);` (scope `PV::AttributeNames`)
- L128 _variable_ `inline static const FName FoliageNormalVector = FName(FoliageNormalVectorStr);` (scope `PV::AttributeNames`)
- L129 _variable_ `inline static const FName FoliageScale = FName(FoliageScaleStr);` (scope `PV::AttributeNames`)
- L130 _variable_ `inline static const FName FoliageLengthFromRoot = FName(FoliageLengthFromRootStr);` (scope `PV::AttributeNames`)
- L131 _variable_ `inline static const FName FoliageParentBoneID = FName(FoliageParentBoneIDStr);` (scope `PV::AttributeNames`)
- L134 _variable_ `inline constexpr TCHAR FoliageNameStr[] = TEXT("Nam` (scope `PV::AttributeNames`) — FoliageNames Attributes
- L136 _variable_ `inline static const FName FoliageName = FName(FoliageNameStr);` (scope `PV::AttributeNames`)
- L139 _variable_ `inline constexpr TCHAR LeafPhyllotaxyStr[] = TEXT("phy` (scope `PV::AttributeNames`) — Details Attributes
- L140 _variable_ `inline constexpr TCHAR FoliagePathStr[] = TEXT("Fol` (scope `PV::AttributeNames`)
- L141 _variable_ `inline constexpr TCHAR GuidStr[] = TEXT("Gui` (scope `PV::AttributeNames`)
- L142 _variable_ `inline constexpr TCHAR LeafGrowthStr[] = TEXT("lea` (scope `PV::AttributeNames`)
- L143 _variable_ `inline constexpr TCHAR AbscissionSenescenseStr[] = TEXT("abs` (scope `PV::AttributeNames`)
- L144 _variable_ `inline constexpr TCHAR LateralElongationStr[] = TEXT("lat` (scope `PV::AttributeNames`)
- L145 _variable_ `inline constexpr TCHAR GraftUseAsMaskStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L146 _variable_ `inline constexpr TCHAR GraftLightStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L147 _variable_ `inline constexpr TCHAR GraftScaleStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L148 _variable_ `inline constexpr TCHAR GraftTipStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L149 _variable_ `inline constexpr TCHAR GraftUpAlignmentStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L150 _variable_ `inline constexpr TCHAR GraftHealthStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L151 _variable_ `inline constexpr TCHAR GraftHeightStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L152 _variable_ `inline constexpr TCHAR GraftGenerationStr[] = TEXT("Gra` (scope `PV::AttributeNames`)
- L154 _variable_ `inline static const FName LeafPhyllotaxy = FName(LeafPhyllotaxyStr);` (scope `PV::AttributeNames`)
- L155 _variable_ `inline static const FName FoliagePath = FName(FoliagePathStr);` (scope `PV::AttributeNames`)
- L156 _variable_ `inline static const FName Guid = FName(GuidStr);` (scope `PV::AttributeNames`)
- L157 _variable_ `inline static const FName LeafGrowth = FName(LeafGrowthStr);` (scope `PV::AttributeNames`)
- L158 _variable_ `inline static const FName AbscissionSenescense = FName(AbscissionSenescenseStr);` (scope `PV::AttributeNames`)
- L159 _variable_ `inline static const FName LateralElongation = FName(LateralElongationStr);` (scope `PV::AttributeNames`)
- L160 _variable_ `inline static const FName GraftUseAsMask = FName(GraftUseAsMaskStr);` (scope `PV::AttributeNames`)
- L161 _variable_ `inline static const FName GraftLight = FName(GraftLightStr);` (scope `PV::AttributeNames`)
- L162 _variable_ `inline static const FName GraftScale = FName(GraftScaleStr);` (scope `PV::AttributeNames`)
- L163 _variable_ `inline static const FName GraftTip = FName(GraftTipStr);` (scope `PV::AttributeNames`)
- L164 _variable_ `inline static const FName GraftUpAlignment = FName(GraftUpAlignmentStr);` (scope `PV::AttributeNames`)
- L165 _variable_ `inline static const FName GraftHealth = FName(GraftHealthStr);` (scope `PV::AttributeNames`)
- L166 _variable_ `inline static const FName GraftHeight = FName(GraftHeightStr);` (scope `PV::AttributeNames`)
- L167 _variable_ `inline static const FName GraftGeneration = FName(GraftGenerationStr);` (scope `PV::AttributeNames`)
- L170 _variable_ `inline constexpr TCHAR ProfilePointsStr[] = TEXT("Pro` (scope `PV::AttributeNames`) — PlantProfiles Attributes
- L172 _variable_ `inline static const FName ProfilePoints = FName(ProfilePointsStr);` (scope `PV::AttributeNames`)
- L175 _variable_ `inline constexpr TCHAR BoneNameStr[] = TEXT("Bon` (scope `PV::AttributeNames`) — Bone Attributes
- L176 _variable_ `inline constexpr TCHAR BoneParentIndexStr[] = TEXT("Bon` (scope `PV::AttributeNames`)
- L177 _variable_ `inline constexpr TCHAR BonePoseStr[] = TEXT("Bon` (scope `PV::AttributeNames`)
- L178 _variable_ `inline constexpr TCHAR BonePointIndexStr[] = TEXT("Bon` (scope `PV::AttributeNames`)
- L179 _variable_ `inline constexpr TCHAR BoneAbsolutePositionStr[] = TEXT("Bon` (scope `PV::AttributeNames`)
- L180 _variable_ `inline constexpr TCHAR BoneBranchIndexStr[] = TEXT("Bon` (scope `PV::AttributeNames`)
- L181 _variable_ `inline constexpr TCHAR NjordPixelIdStr[] = TEXT("Njo` (scope `PV::AttributeNames`)
- L182 _variable_ `inline constexpr TCHAR VertexPointIdsStr[] = TEXT("Ver` (scope `PV::AttributeNames`)
- L183 _variable_ `inline constexpr TCHAR BoneIdStr[] = TEXT("Bon` (scope `PV::AttributeNames`)
- L185 _variable_ `inline static const FName BoneName = FName(BoneNameStr);` (scope `PV::AttributeNames`)
- L186 _variable_ `inline static const FName BoneParentIndex = FName(BoneParentIndexStr);` (scope `PV::AttributeNames`)
- L187 _variable_ `inline static const FName BonePose = FName(BonePoseStr);` (scope `PV::AttributeNames`)
- L188 _variable_ `inline static const FName BonePointIndex = FName(BonePointIndexStr);` (scope `PV::AttributeNames`)
- L189 _variable_ `inline static const FName BoneAbsolutePosition = FName(BoneAbsolutePositionStr);` (scope `PV::AttributeNames`)
- L190 _variable_ `inline static const FName BoneBranchIndex = FName(BoneBranchIndexStr);` (scope `PV::AttributeNames`)
- L191 _variable_ `inline static const FName NjordPixelId = FName(NjordPixelIdStr);` (scope `PV::AttributeNames`)
- L192 _variable_ `inline static const FName VertexPointIds = FName(VertexPointIdsStr);` (scope `PV::AttributeNames`)
- L193 _variable_ `inline static const FName BoneId = FName(BoneIdStr);` (scope `PV::AttributeNames`)
- L196 _variable_ `inline constexpr TCHAR LeafMeshPathStr[] = TEXT("Mes` (scope `PV::AttributeNames`) — Leaf Meta Attributes
- L197 _variable_ `inline static const FName LeafMeshPath = FName(LeafMeshPathStr);` (scope `PV::AttributeNames`)
- L200 _variable_ `inline constexpr TCHAR LeafRotationStr[] = TEXT("Rot` (scope `PV::AttributeNames`) — Leaves Attributes (per-leaf transform; Position reuses PointPositionStr, Scale reuses PointScaleStr)
- L201 _variable_ `inline static const FName LeafRotation = FName(LeafRotationStr);` (scope `PV::AttributeNames`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVBoneFacade.h` (Public)


#### struct `PV::Facades::FBoneNode`  
`struct FBoneNode`  
_L13-24_
- desc: FBoneNode contains the bone data and linked point and branch ids
- L15 _public member_ `FName BoneName = NAME_None;`
- L16 _public member_ `int32 BoneIndex = INDEX_NONE;`
- L17 _public member_ `int32 ParentBoneIndex = INDEX_NONE;`
- L18 _public member_ `int32 PointIndex = INDEX_NONE;`
- L19 _public member_ `int32 BranchIndex = INDEX_NONE;`
- L20 _public member_ `float NjordPixelID = 0.0;`
- L22 _public member_ `FTransform BoneTransform{};`
- L23 _public member_ `FVector AbsolutePosition = FVector::ZeroVector;`

#### class `PV::Facades::FBoneFacade`  
`class FBoneFacade`  
_L30-72_
- desc: FBoneFacade is used to access and manipulate the Bone data from Bones Group with in the ProceduralVegetation's FManagedArrayCollection. NjordPixel id here is stored in vertex Group and is used for bone assignment
- L33 _public prototype_ `FBoneFacade(FManagedArrayCollection& InCollection);`
- L35 _public prototype_ `FBoneFacade(const FManagedArrayCollection& InCollection);`
- L37 _public prototype_ `static void DefineSchema(FManagedArrayCollection& InCollection);`
- L39 _public prototype_ `bool IsValid() const;`
- L41 _public prototype_ `void GetPointIds(TArray<int32>& OutVertexPointIds) const;`
- L43 _public prototype_ `const TManagedArray<FString>& GetBoneNames() const;`
- L45 _public prototype_ `const TManagedArray<int32>& GetBoneParentIndices() const;`
- L47 _public prototype_ `const TManagedArray<FTransform>& GetBonePoses() const;`
- L49 _public prototype_ `const TManagedArray<int32>& GetVertexPointIds() const;`
- L51 _public prototype_ `TManagedArray<int32>& ModifyVertexPointIds();`
- L53 _public prototype_ `void SetWindSimulationData(FManagedArrayCollection& Collection);`
- L55 _public prototype_ `bool CreateBoneData(TArray<FBoneNode>& Bones,const float ReductionStrength,bool bSetWindData = true);`
- L57 _public prototype_ `static FBoneNode* FindClosestBone(const FManagedArrayCollection& Collection, TArray<FBoneNode>& Bones, const int32 PointID);`
- L59 _public prototype_ `TArray<FBoneNode> GetBoneDataFromCollection() const;`
- L61 _public prototype_ `void SetBoneDataToCollection(TArray<FBoneNode>& Bones);`
- L64 _private member_ `TManagedArrayAccessor<FString> BoneName;`
- L65 _private member_ `TManagedArrayAccessor<int32> BoneParentIndex;`
- L66 _private member_ `TManagedArrayAccessor<int32> BoneId;`
- L67 _private member_ `TManagedArrayAccessor<FTransform> BonePose;`
- L68 _private member_ `TManagedArrayAccessor<int32> BonePointIndex;`
- L69 _private member_ `TManagedArrayAccessor<FVector3f> BoneAbsolutePosition;`
- L70 _private member_ `TManagedArrayAccessor<int32> BoneBranchIndex;`
- L71 _private member_ `TManagedArrayAccessor<int32> VertexPointIds;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PV`
- L8 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVBranchFacade.h` (Public)


#### class `PV::Facades::FBranchFacade`  
`class FBranchFacade final : public IShrinkable`  
_L16-194_
- inherits: `IShrinkable`
- desc: FBranchFacade is used to access and manipulate the data from Branch Group with in the ProceduralVegetation's FManagedArrayCollection A branch is made up of multiple points. Each Branch will know about its parents and children, along with other attributes Only add the frequently used branch attributes and their access to this facade, for the specific access write a new facade
- L19 _public prototype_ `FBranchFacade(FManagedArrayCollection& InCollection);`
- L20 _public prototype_ `FBranchFacade(const FManagedArrayCollection& InCollection);`
- L22 _public function_ `bool IsConst() const`
- L24 _public prototype_ `bool IsValid() const;`
- L26 _public prototype_ `virtual int32 GetElementCount() const override;`
- L28 _public prototype_ `const TArray<int32>& GetPoints(int32 Index) const;`
- L30 _public prototype_ `int32 GetRootPoint(int32 Index) const;`
- L32 _public prototype_ `void SetPoints(int32 Index, TArray<int32> InPoints);`
- L34 _public prototype_ `const TArray<int32>& GetChildren(int32 Index) const;`
- L36 _public prototype_ `TArray<int32> GetImmediateChildren(int32 Index) const;`
- L38 _public prototype_ `void SetChildren(int32 Index, TArray<int32> InChildren);`
- L40 _public prototype_ `const TArray<int32>& GetParents(int32 Index) const;`
- L42 _public prototype_ `int32 GetParentIndex(int32 BranchIndex) const;`
- L44 _public prototype_ `int32 GetParentBranchNumber(int32 BranchIndex) const;`
- L46 _public prototype_ `void SetParentBranchNumber(int32 BranchIndex, int32 InParentBranchNumber);`
- L48 _public prototype_ `const TManagedArray<int32>& GetParentBranchNumbers() const;`
- L50 _public prototype_ `void SetParents(int32 Index, TArray<int32> InParents);`
- L52 _public prototype_ `int32 GetBranchNumber(int32 Index) const;`
- L54 _public prototype_ `void SetBranchNumber(int32 Index, int32 InBranchNumber);`
- L56 _public prototype_ `const TArray<int32>& GetBranchFoliageIDs(int32 Index) const;`
- L58 _public prototype_ `void SetBranchFoliageIDs(int32 Index, TArray<int32> InBranchFoliageIDs);`
- L60 _public prototype_ `int32 GetBranchPlantNumber(int32 Index) const;`
- L62 _public prototype_ `void SetBranchPlantNumber(int32 Index, int32 InPlantNumber);`
- L64 _public prototype_ `int32 GetBranchSourceBudNumber(int32 Index) const;`
- L66 _public prototype_ `void SetBranchSourceBudNumber(int32 Index, int32 InSourceBudNumber);`
- L68 _public prototype_ `TArray<int32> GetParentBranchIndices(int BranchIndex) const;`
- L70 _public prototype_ `int32 GetParentBranchIndex(int32 BranchIndex) const;`
- L72 _public prototype_ `int32 GetHierarchyGenerationNumber(int32 Index) const;`
- L74 _public prototype_ `const TManagedArray<int32>& GetBranchNumbers() const;`
- L76 _public prototype_ `int32 GetBranchUVMaterial(int32 Index) const;`
- L78 _public prototype_ `void SetBranchUVMaterial(int32 Index, int32 InMaterial);`
- L80 _public prototype_ `int32 GetBranchHierarchyNumber(int32 Index) const;`
- L82 _public prototype_ `const TManagedArray<int32>& GetBranchHierarchyNumbers() const;`
- L84 _public prototype_ `void SetBranchHierarchyNumber(int32 Index, int32 InBranchHierarchyNumber);`
- L86 _public prototype_ `int32 GetBranchSimulationGroupIndex(int32 Index) const;`
- L88 _public prototype_ `void SetBranchSimulationGroupIndex(int32 Index, int32 InLogicalDepth);`
- L90 _public prototype_ `void SetTrunkMaterialPath(const FString& InPath);`
- L92 _public prototype_ `FString GetTrunkMaterialPath() const;`
- L94 _public prototype_ `void SetTrunkURange(TArray<FVector2f> InURange);`
- L96 _public prototype_ `const TArray<FVector2f>& GetTrunkURange() const;`
- L98 _public prototype_ `virtual void CopyEntry(int32 FromIndex, int32 ToIndex) override;`
- L100 _public prototype_ `virtual void RemoveEntries(int32 NumEntries, int32 StartIndex) override;`
- L102 _public prototype_ `void GetSortedBranchIndicesByHierarchy(TArray<int32>& OutSortedIndices) const;`
- L104 _public prototype_ `int32 GetBranchIndexFromPointIndex(int32 PointIndex) const;`
- L106 _public prototype_ `int32 AddElements(int NumElements);`
- L108 _public prototype_ `void FillParents(const TArray<TArray<int32>>& InputArray);`
- L110 _public prototype_ `void RecomputeBranchChildren();`
- L112 _public prototype_ `static TArray<int32> ComputeDescendantsForBranchNumber( const int32 BranchNumber, const TMap<int32, TArray<int32>>& ImmediateChildren, TMap<int32, TArray<int32>>& Memo, TSet<int32>& VisitingSet);`
- L118 _public prototype_ `static TArray<int32> ComputeParentsForBranchNumber(const int32 BranchNumber, const TMap<int32, int32>& BranchNumbersToBranchParentNumbers, TMap<int32, TArray<int32>>& Memo, TSet<int32>& VisitedParents);`
- L121 _public prototype_ `void RecomputeBranchParents();`
- L123 _public prototype_ `void FillChildren(const TArray<TArray<int32>>& InputArray);`
- L125 _public prototype_ `void FillBranchPoints(const TArray<TArray<int32>>& InputArray);`
- L127 _public prototype_ `void FillBranchNumbers(const TArray<int32>& InputArray);`
- L129 _public prototype_ `void FillBranchSourceBudNumber(const TArray<int32>& InputArray);`
- L131 _public prototype_ `void FillBranchHierarchyNumber(const TArray<int32>& InputArray);`
- L133 _public prototype_ `void FillBranchParentNumbers(const TArray<int32>& InputArray);`
- L135 _public prototype_ `void FillPlantNumbers(const TArray<int32>& InputArray);`
- L137 _public prototype_ `void SetBranchNumbersFromIndex(const TArray<int32>& InputArray, const int32 StartIndex);`
- L139 _public prototype_ `void SetParentBranchNumbersFromIndex(const TArray<int32>& InputArray, const int32 StartIndex);`
- L141 _public prototype_ `void SetBranchHierarchyNumbersFromIndex(const TArray<int32>& InputArray, const int32 StartIndex);`
- L144 _public function_ `template<typename T> FORCEINLINE bool GetValueFromAccessor(TManagedArrayAccessor<T> Accessor, T& OutValue, int32 Index, const T DefaultValue) const`
- L156 _public prototype_ `bool IsTrunk(int32 Index) const;`
- L158 _public prototype_ `void GetParents(int32 Index, TArray<int32>& OutValue) const;`
- L160 _public prototype_ `void GetChildren(int32 Index, TArray<int32>& OutValue) const;`
- L162 _public prototype_ `void GetBranchPoints(int32 Index, TArray<int32>& OutValue) const;`
- L164 _public prototype_ `void GetBranchNumber(int32 Index, int32& OutValue) const;`
- L166 _public prototype_ `void GetBranchSourceBudNumber(int32 Index, int32& OutValue) const;`
- L168 _public prototype_ `const TManagedArray<int32>& GetBranchSourceBudNumbers() const;`
- L170 _public prototype_ `void SetBranchSourceBudNumbersFromIndex(const TArray<int32>& InputArray, const int32 StartIndex);`
- L172 _public prototype_ `void GetBranchHierarchyNumber(int32 Index, int32& OutValue) const;`
- L174 _public prototype_ `void GetBranchParentNumber(int32 Index, int32& OutValue) const;`
- L176 _public prototype_ `void GetPlantNumber(int32 Index, int32& OutValue) const;`
- L179 _private member_ `FManagedArrayCollection* Collection = nullptr;`
- L181 _private member_ `TManagedArrayAccessor<TArray<int32>> Parents;`
- L182 _private member_ `TManagedArrayAccessor<TArray<int32>> Children;`
- L183 _private member_ `TManagedArrayAccessor<TArray<int32>> BranchPoints;`
- L184 _private member_ `TManagedArrayAccessor<int32> BranchNumbers;`
- L185 _private member_ `TManagedArrayAccessor<int32> BranchSourceBudNumber;`
- L186 _private member_ `TManagedArrayAccessor<TArray<int32>> BranchFoliageIDs;`
- L187 _private member_ `TManagedArrayAccessor<int32> BranchUVMaterial;`
- L188 _private member_ `TManagedArrayAccessor<int32> BranchHierarchyNumber;`
- L189 _private member_ `TManagedArrayAccessor<int32> BranchSimulationGroupIndex;`
- L190 _private member_ `TManagedArrayAccessor<FString> TrunkMaterialPathAttribute;`
- L191 _private member_ `TManagedArrayAccessor<TArray<FVector2f>> TrunkURangeAttribute;`
- L192 _private member_ `TManagedArrayAccessor<int32> BranchParentNumbers;`
- L193 _private member_ `TManagedArrayAccessor<int32> PlantNumbers;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PV`
- L9 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVBudVectorsFacade.h` (Public)


#### class `PV::Facades::FBudVectorsFacade`  
`class FBudVectorsFacade`  
_L23-39_
- desc: FBudVectorsFacade is used to access and manipulate the BudVectors data from Point Group with in the ProceduralVegetation's FManagedArrayCollection BudVectors represent different growth related vectors in plant data and are associated with each point.
- L26 _public prototype_ `FBudVectorsFacade(FManagedArrayCollection& InCollection);`
- L27 _public prototype_ `FBudVectorsFacade(const FManagedArrayCollection& InCollection);`
- L29 _public prototype_ `bool IsValid() const;`
- L31 _public prototype_ `const TArray<FVector3f>& GetBudDirection(int32 Index) const;`
- L33 _public prototype_ `TManagedArray<TArray<FVector3f>>& ModifyBudDirections();`
- L35 _public prototype_ `const TManagedArray<TArray<FVector3f>>& GetBudDirections() const;`
- L38 _private member_ `TManagedArrayAccessor<TArray<FVector3f>> BudDirection;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PV`
- L8 _namespace_ `namespace Facades` (scope `PV`)
- L10 _variable_ `constexpr int BudDirectionsApical = 0;` (scope `PV::Facades`)
- L11 _variable_ `constexpr int BudDirectionsAxillary = 1;` (scope `PV::Facades`)
- L12 _variable_ `constexpr int BudDirectionsLightOptimalIndex = 2;` (scope `PV::Facades`)
- L13 _variable_ `constexpr int BudDirectionsLightSubOptimal = 3;` (scope `PV::Facades`)
- L14 _variable_ `constexpr int BudDirectionsGuideCurve = 4;` (scope `PV::Facades`)
- L15 _variable_ `constexpr int BudDirectionsUpVector = 5;` (scope `PV::Facades`)
- L17 _variable_ `constexpr int BudLightDetectedAvailableIndex = 0;` (scope `PV::Facades`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVFoliageFacade.h` (Public)


#### struct `PV::Facades::FFoliageEntryData`  
`struct FFoliageEntryData`  
_L12-29_
- L14 _public member_ `int32 NameId;`
- L15 _public member_ `int32 BranchId;`
- L16 _public member_ `FVector3f PivotPoint;`
- L17 _public member_ `FVector3f UpVector;`
- L18 _public member_ `FVector3f NormalVector;`
- L19 _public member_ `float Scale;`
- L20 _public member_ `float LengthFromRoot;`
- L21 _public member_ `float ConditionUpAlignment;`
- L22 _public member_ `float ConditionTip;`
- L23 _public member_ `float ConditionLight;`
- L24 _public member_ `float ConditionScale;`
- L25 _public member_ `float ConditionHealth;`
- L26 _public member_ `float ConditionHeight;`
- L27 _public member_ `float ConditionGeneration;`
- L28 _public member_ `int32 ParentBoneID = INDEX_NONE;`

#### class `PV::Facades::FFoliageFacade`  
`class FFoliageFacade final : public IShrinkable`  
_L37-188_
- inherits: `IShrinkable`
- desc: FFoliageFacade is used to access and manipulate Foliage related data for a ProceduralVegetation's FManagedArrayCollection It presents access to foliage Mesh names, their respective Branch ids, and instancing transform data (Pivot point, Up Vector, and Scale) It lays out data in two Groups: FoliageNames and Foliage where Foliage references FoliageNames and Branch/Primitives with Ids It also adds Foliage entry Ids to the Branch/Primitives group.
- L40 _public prototype_ `FFoliageFacade(FManagedArrayCollection& InCollection, int32 InitialSize = 0);`
- L41 _public prototype_ `FFoliageFacade(const FManagedArrayCollection& InCollection);`
- L43 _public function_ `bool IsConst() const`
- L45 _public prototype_ `bool IsValid() const;`
- L47 _public function_ `int32 NumFoliageEntries() const`
- L49 _public prototype_ `FFoliageEntryData GetFoliageEntry(const int32 Index) const;`
- L51 _public prototype_ `float GetLengthFromRoot(int32 Index) const;`
- L53 _public prototype_ `void SetLengthFromRoot(int32 Index, float Input);`
- L55 _public prototype_ `int32 GetParentBoneID(int32 Index) const;`
- L57 _public prototype_ `void SetParentBoneID(int32 Index, int32 Input);`
- L59 _public prototype_ `const TArray<int32>& GetFoliageEntryIdsForBranch(int32 Index) const;`
- L61 _public prototype_ `int32 AddFoliageEntry(const FFoliageEntryData& InputData);`
- L63 _public prototype_ `void SetFoliageEntry(int32 Index, const FFoliageEntryData& InputData);`
- L65 _public prototype_ `void SetFoliageIdsArray(int32 Index, TArray<int32> InputIds);`
- L67 _public prototype_ `int32 GetFoliageBranchId(int32 Index) const;`
- L69 _public function_ `int32 NumFoliageNames() const`
- L71 _public prototype_ `void SetFoliageBranchId(int32 Index, int32 InputId);`
- L73 _public prototype_ `bool IsMaskFoliageEntry(int32 Index) const;`
- L75 _public prototype_ `void SetMaskFoliageEntry(int32 Index, bool InUseAsMask);`
- L77 _public prototype_ `const FString GetFoliageName(int32 Index) const;`
- L79 _public prototype_ `TArray<FString> GetFoliageNames() const;`
- L81 _public prototype_ `void SetFoliageNamesFromIndex(const TArray<FString>& InputArray, const int32 StartIndex);`
- L83 _public function_ `int32 NumFoliageInfo() const`
- L85 _public prototype_ `FPVFoliageInfo GetFoliageInfo(const int32 Index) const;`
- L87 _public prototype_ `const FVector3f& GetPivotPoint(int32 Index) const;`
- L89 _public prototype_ `TArray<FPVFoliageInfo> GetFoliageInfos() const;`
- L91 _public prototype_ `const FVector3f& GetUpVector(int32 Index) const;`
- L93 _public prototype_ `const FVector3f& GetNormalVector(int32 Index) const;`
- L95 _public prototype_ `void SetPivotPoint(int32 Index, const FVector3f& Input);`
- L97 _public prototype_ `void SetUpVector(int32 Index, const FVector3f& Input);`
- L99 _public prototype_ `void SetNormalVector(int32 Index, const FVector3f& Input);`
- L101 _public prototype_ `void SetScale(int32 Index, float Input);`
- L103 _public prototype_ `void SetFoliageName(int32 Index, const FString& Input);`
- L105 _public prototype_ `void SetFoliageNames(const TArray<FString>& InputNames);`
- L107 _public prototype_ `void SetFoliageInfo(const int32 Index, const FString& Input);`
- L109 _public prototype_ `void SetFoliageInfos(const TArray<FPVFoliageInfo>& Infos);`
- L111 _public prototype_ `int32 AppendFoliageInfos(const TArray<FPVFoliageInfo>& Infos);`
- L113 _public prototype_ `void SetFoliagePath(FString InPath);`
- L115 _public prototype_ `FString GetFoliagePath() const;`
- L117 _public prototype_ `virtual int32 GetElementCount() const override;`
- L119 _public prototype_ `virtual void CopyEntry(int32 FromIndex, int32 ToIndex) override;`
- L121 _public prototype_ `virtual void RemoveEntries(int32 NumEntries, int32 StartIndex) override;`
- L123 _public prototype_ `FTransform GetFoliageTransform(int32 Id) const;`
- L125 _public prototype_ `const TManagedArray<FVector3f>& GetPivotPositions() const;`
- L127 _public prototype_ `void SetPivotPositionsFromIndex(const TArray<FVector3f>& InputArray, const int32 StartIndex);`
- L129 _public prototype_ `TManagedArray<FVector3f>& ModifyPivotPositions();`
- L131 _public prototype_ `const TManagedArray<int32>& GetFoliageNameIDs() const;`
- L133 _public prototype_ `void SetFoliageNameIDsFromIndex(const TArray<int32>& InputArray, const int32 StartIndex);`
- L135 _public prototype_ `const TManagedArray<int32>& GetFoliageBranchIDs() const;`
- L137 _public prototype_ `void SetFoliageBranchIDsFromIndex(const TArray<int32>& InputArray, const int32 StartIndex);`
- L139 _public prototype_ `const TManagedArray<FVector3f>& GetUpVectors() const;`
- L141 _public prototype_ `void SetUpVectorsFromIndex(const TArray<FVector3f>& InputArray, const int32 StartIndex);`
- L143 _public prototype_ `const TManagedArray<FVector3f>& GetNormalVectors() const;`
- L145 _public prototype_ `void SetNormalVectorsFromIndex(const TArray<FVector3f>& InputArray, const int32 StartIndex);`
- L147 _public prototype_ `const TManagedArray<float>& GetScales() const;`
- L149 _public prototype_ `void SetScalesFromIndex(const TArray<float>& InputArray, const int32 StartIndex);`
- L151 _public prototype_ `const TManagedArray<float>& GetLFRs() const;`
- L153 _public prototype_ `void SetLFRsFromIndex(const TArray<float>& InputArray, const int32 StartIndex);`
- L156 _protected prototype_ `void DefineSchema(int32 InitialSize = 0);`
- L158 _protected member_ `const FManagedArrayCollection& ConstCollection;`
- L159 _protected member_ `FManagedArrayCollection* Collection = nullptr;`
- L161 _protected member_ `TManagedArrayAccessor<bool> FoliageInfoUseAsMaskAttribute;`
- L162 _protected member_ `TManagedArrayAccessor<FString> FoliageInfoNamesAttribute;`
- L163 _protected member_ `TManagedArrayAccessor<float> FoliageInfoLightAttribute;`
- L164 _protected member_ `TManagedArrayAccessor<float> FoliageInfoScaleAttribute;`
- L165 _protected member_ `TManagedArrayAccessor<float> FoliageInfoTipAttribute;`
- L166 _protected member_ `TManagedArrayAccessor<float> FoliageInfoUpAlignmentAttribute;`
- L167 _protected member_ `TManagedArrayAccessor<float> FoliageInfoHealthAttribute;`
- L168 _protected member_ `TManagedArrayAccessor<float> FoliageInfoHeightAttribute;`
- L169 _protected member_ `TManagedArrayAccessor<float> FoliageInfoGenerationAttribute;`
- L171 _protected member_ `TManagedArrayAccessor<int32> NameIdsAttribute;`
- L172 _protected member_ `TManagedArrayAccessor<int32> BranchIdsAttribute;`
- L173 _protected member_ `TManagedArrayAccessor<FVector3f> PivotPointsAttribute;`
- L174 _protected member_ `TManagedArrayAccessor<FVector3f> UpVectorsAttribute;`
- L175 _protected member_ `TManagedArrayAccessor<FVector3f> NormalVectorsAttribute;`
- L176 _protected member_ `TManagedArrayAccessor<float> ScalesAttribute;`
- L177 _protected member_ `TManagedArrayAccessor<float> LengthFromRootAttribute;`
- L178 _protected member_ `TManagedArrayAccessor<float> ConditionLightAttribute;`
- L179 _protected member_ `TManagedArrayAccessor<float> ConditionScaleAttribute;`
- L180 _protected member_ `TManagedArrayAccessor<float> ConditionTipAttribute;`
- L181 _protected member_ `TManagedArrayAccessor<float> ConditionUpAlignmentAttribute;`
- L182 _protected member_ `TManagedArrayAccessor<float> ConditionHealthAttribute;`
- L183 _protected member_ `TManagedArrayAccessor<float> ConditionHeightAttribute;`
- L184 _protected member_ `TManagedArrayAccessor<float> ConditionGenerationAttribute;`
- L185 _protected member_ `TManagedArrayAccessor<int32> ParentBoneIdsAttribute;`
- L186 _protected member_ `TManagedArrayAccessor<TArray<int32>> FoliageIdsAttribute;`
- L187 _protected member_ `TManagedArrayAccessor<FString> FoliagePathAttribute;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PV`
- L10 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVMetaInfoFacade.h` (Public)


#### class `PV::Facades::FMetaInfoFacade`  
`class FMetaInfoFacade`  
_L12-56_
- L15 _public prototype_ `FMetaInfoFacade(FManagedArrayCollection& InCollection, const int32 InitialSize = 0);`
- L16 _public prototype_ `FMetaInfoFacade(const FManagedArrayCollection& InCollection);`
- L18 _public function_ `bool IsConst() const`
- L19 _public prototype_ `bool IsValid() const;`
- L21 _public prototype_ `void CreateGuid(const FString& InPath);`
- L22 _public prototype_ `FGuid GetGuid() const;`
- L24 _public prototype_ `void SetGraftAttributes(const FPVGraftInfo& InGraftData);`
- L25 _public prototype_ `FPVGraftInfo GetGraftAttributes() const;`
- L27 _public prototype_ `bool GraftEntryUseAsMask() const;`
- L28 _public prototype_ `void SetGraftUseAsMask(const bool InUseAsMask);`
- L30 _public prototype_ `void SetLeafGrowth(const TArray<float>& InLeafGrowth);`
- L31 _public prototype_ `void SetAbscissionSenescense(const TArray<float>& InAbscissionSenescense);`
- L32 _public prototype_ `void SetLateralElongation(const TArray<float>& InLateralElongation);`
- L34 _public prototype_ `const TArray<float>& GetLeafGrowth() const;`
- L35 _public prototype_ `const TArray<float>& GetAbscissionSenescense() const;`
- L36 _public prototype_ `const TArray<float>& GetLateralElongation() const;`
- L39 _protected prototype_ `void DefineSchema(const int32 InitialSize = 0);`
- L41 _protected member_ `const FManagedArrayCollection& ConstCollection;`
- L42 _protected member_ `FManagedArrayCollection* Collection = nullptr;`
- L44 _protected member_ `TManagedArrayAccessor<FGuid> GuidAttribute;`
- L45 _protected member_ `TManagedArrayAccessor<TArray<float>> LeafGrowthAttribute;`
- L46 _protected member_ `TManagedArrayAccessor<TArray<float>> AbscissionSenescenseAttribute;`
- L47 _protected member_ `TManagedArrayAccessor<TArray<float>> LateralElongationAttribute;`
- L48 _protected member_ `TManagedArrayAccessor<bool> GraftUseAsMask;`
- L49 _protected member_ `TManagedArrayAccessor<float> GraftLightAttribute;`
- L50 _protected member_ `TManagedArrayAccessor<float> GraftUpAlignmentAttribute;`
- L51 _protected member_ `TManagedArrayAccessor<float> GraftHealthAttribute;`
- L52 _protected member_ `TManagedArrayAccessor<float> GraftTipAttribute;`
- L53 _protected member_ `TManagedArrayAccessor<float> GraftHeightAttribute;`
- L54 _protected member_ `TManagedArrayAccessor<float> GraftGenerationAttribute;`
- L55 _protected member_ `TManagedArrayAccessor<float> GraftScaleAttribute;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace PV`
- L10 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVPlantFacade.h` (Public)


#### class `PV::Facades::FPlantFacade`  
`class FPlantFacade`  
_L16-51_
- desc: FPlantFacade is used to access and manipulate the data from Plants Group with in the ProceduralVegetation's FManagedArrayCollection A ProceduralVegetation asset can consist of multiple plants. Each entry in the group references that plant's associated branch numbers and indices.
- L19 _public prototype_ `FPlantFacade(FManagedArrayCollection& InCollection);`
- L20 _public prototype_ `FPlantFacade(const FManagedArrayCollection& InCollection);`
- L22 _public function_ `bool IsConst() const`
- L24 _public prototype_ `bool IsValid() const;`
- L26 _public prototype_ `int32 GetElementCount() const;`
- L28 _public prototype_ `TArray<int32> GetBranchNumbers(const int32 PlantNumber) const;`
- L30 _public prototype_ `TArray<int32> GetBranchIndices(const int32 PlantNumber) const;`
- L32 _public prototype_ `TArray<int32> GetBranchIndicesSortedByHierarchyNumber(const int32 PlantNumber) const;`
- L34 _public prototype_ `TArray<int32> GetPlantNumbers() const;`
- L36 _public prototype_ `TArray<int32> GetTrunkIndices() const;`
- L38 _public prototype_ `TMap<int32, int32> GetPlantNumbersToTrunkIndicesMap() const;`
- L40 _public prototype_ `int32 GetTrunkIndex(const int32 PlantNumber) const;`
- L42 _public prototype_ `bool IsTrunkIndex(const int32 BranchIndex) const;`
- L45 _private member_ `FManagedArrayCollection* Collection = nullptr;`
- L47 _private member_ `TManagedArrayAccessor<int32> PlantNumbers;`
- L48 _private member_ `TManagedArrayAccessor<int32> BranchNumbers;`
- L49 _private member_ `TManagedArrayAccessor<int32> BranchParentNumbers;`
- L50 _private member_ `TManagedArrayAccessor<int32> BranchHierarchyNumbers;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace PV`
- L9 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVPointFacade.h` (Public)


#### class `PV::Facades::FPointFacade`  
`class FPointFacade final : public IShrinkable`  
_L30-242_
- inherits: `IShrinkable`
- desc: FPointFacade is used to access and manipulate the Point Group data from the ProceduralVegetation's FManagedArrayCollection Only add the frequently used Point attributes and their access to this facade, for the specific access write a new facade
- L33 _public prototype_ `FPointFacade(FManagedArrayCollection& InCollection);`
- L34 _public prototype_ `FPointFacade(const FManagedArrayCollection& InCollection);`
- L36 _public function_ `bool IsConst() const`
- L38 _public prototype_ `bool IsValid() const;`
- L40 _public prototype_ `virtual int32 GetElementCount() const override;`
- L42 _public prototype_ `const FVector3f& GetPosition(int32 Index) const;`
- L44 _public prototype_ `void SetPosition(int32 Index, const FVector3f& InPosition);`
- L46 _public prototype_ `float GetLengthFromRoot(int32 Index) const;`
- L48 _public prototype_ `void SetLengthFromRoot(int32 Index, float InLength);`
- L50 _public prototype_ `float GetLengthFromSeed(int32 Index) const;`
- L52 _public prototype_ `void SetLengthFromSeed(int32 Index, float InLength);`
- L54 _public prototype_ `float GetPointScale(int32 Index) const;`
- L56 _public prototype_ `void SetPointScale(int32 Index, float InPointScale);`
- L58 _public prototype_ `void SetSeedPScale(int32 Index, float InSeedPScale);`
- L60 _public prototype_ `void SetSeedPScaleRatio(int32 Index, float InSeedPScaleRatio);`
- L62 _public prototype_ `int32 GetBudNumber(int32 Index) const;`
- L64 _public prototype_ `void SetBudNumber(int32 Index, int32 InBudNumber);`
- L66 _public prototype_ `const TArray<float>& GetBudLightDetected(int32 Index) const;`
- L68 _public prototype_ `void SetBudLightDetected(int32 Index, const TArray<float>& InBudLightDetected);`
- L70 _public prototype_ `const TArray<int>& GetBudDevelopment(int32 Index) const;`
- L72 _public prototype_ `void SetBudDevelopment(int32 Index, const TArray<int>& InBudDevelopment);`
- L74 _public prototype_ `int32 GetBudGeneratation(int32 Index) const;`
- L76 _public prototype_ `int32 GetBudAge(int32 Index) const;`
- L78 _public prototype_ `int32 GetMaxBudAge() const;`
- L80 _public prototype_ `void AddToBudAgeForAllPoints(const int32 Age);`
- L82 _public prototype_ `int32 GetBudBranchAge(int32 Index) const;`
- L84 _public prototype_ `const TArray<FVector3f>& GetBudDirection(int32 Index) const;`
- L86 _public prototype_ `void SetBudDirections(int32 Index, const TArray<FVector3f>& InBudDirections);`
- L88 _public prototype_ `const TArray<float>& GetBudHormoneLevels(int32 Index) const;`
- L90 _public prototype_ `void SetBudHormoneLevels(int32 Index, const TArray<float>& InBudHormoneLevels);`
- L92 _public prototype_ `const TArray<float>& GetBudLateralMeristem(int32 Index) const;`
- L94 _public prototype_ `void SetBudLateralMeristem(int32 Index, const TArray<float>& InBudLateralMeristem);`
- L96 _public prototype_ `float GetTextureCoordV(int32 Index) const;`
- L98 _public prototype_ `void SetTextureCoordV(int32 Index, float InTextureCoordV);`
- L100 _public prototype_ `float GetTextureCoordUOffset(int32 Index) const;`
- L102 _public prototype_ `void SetTextureCoordUOffset(int32 Index, float InTextureCoordUOffset);`
- L104 _public prototype_ `const FVector2f& GetURange(int32 Index) const;`
- L106 _public prototype_ `void SetURange(int32 Index, FVector2f InURange);`
- L108 _public prototype_ `bool IsFusedPoint(const int Generation, const int SourceBudNumber, const int PointIndex) const;`
- L110 _public prototype_ `TManagedArray<FVector3f>& ModifyPositions();`
- L112 _public prototype_ `TManagedArray<float>& ModifyPointScales();`
- L114 _public prototype_ `TManagedArray<float>& ModifyLengthFromRoots();`
- L116 _public prototype_ `TManagedArray<float>& ModifyLengthFromSeeds();`
- L118 _public prototype_ `const TManagedArray<FVector3f>& GetPositions() const;`
- L120 _public prototype_ `const TManagedArray<float>& GetPointScales() const;`
- L122 _public prototype_ `const TManagedArray<float>& GetLengthFromRootsArray() const;`
- L124 _public prototype_ `virtual void CopyEntry(int32 FromIndex, int32 ToIndex) override;`
- L126 _public prototype_ `virtual void RemoveEntries(int32 NumEntries, int32 StartIndex) override;`
- L128 _public prototype_ `int32 AddElements(int NumElements);`
- L130 _public prototype_ `void FillPositions(const TArray<FVector3f>& InputArray);`
- L132 _public prototype_ `void FillLFR(const TArray<float>& InputArray);`
- L134 _public prototype_ `void FillPointScales(const TArray<float>& InputArray);`
- L136 _public prototype_ `void FillBudDirections(const TArray<TArray<FVector3f>>& InputArray);`
- L138 _public prototype_ `void FillBudHormoneLevels(const TArray<TArray<float>>& InputArray);`
- L140 _public prototype_ `void FillLengthFromSeeds(const TArray<float>& InputArray);`
- L142 _public prototype_ `void FillBudNumbers(const TArray<int32>& InputArray);`
- L144 _public prototype_ `void FillBudLightDetected(const TArray<TArray<float>>& InputArray);`
- L146 _public prototype_ `void FillBudDevelopment(const TArray<TArray<int>>& InputArray);`
- L148 _public prototype_ `void SetPositionsFromIndex(const TArray<FVector3f>& InputArray, const int32 StartIndex);`
- L150 _public prototype_ `void SetPointScalesFromIndex(const TArray<float>& InputArray, const int32 StartIndex);`
- L152 _public prototype_ `void SetSeedPScalesFromIndex(const TArray<float>& InputArray, const int32 StartIndex);`
- L154 _public prototype_ `void SetSeedPScaleRatiosFromIndex(const TArray<float>& InputArray, const int32 StartIndex);`
- L156 _public prototype_ `void SetLFRsFromIndex(const TArray<float>& InputArray, const int32 StartIndex);`
- L158 _public prototype_ `const TManagedArray<float>& GetLengthFromSeedsArray() const;`
- L160 _public prototype_ `void SetLengthFromSeedsArrayFromIndex(const TArray<float>& InputArray, const int32 StartIndex);`
- L162 _public prototype_ `void FillBudStatus(const TArray<TArray<int>>& InputArray);`
- L164 _public prototype_ `void FillBudLateralMeristem(const TArray<TArray<float>>& InputArray);`
- L166 _public prototype_ `void FillSeedPScale(const TArray<float>& InputArray);`
- L168 _public prototype_ `void FillSeedPScaleRatio(const TArray<float>& InputArray);`
- L171 _public function_ `template<typename T> FORCEINLINE bool GetValueFromAccessor(TManagedArrayAccessor<T> Accessor, T& OutValue, int32 Index, const T DefaultValue) const`
- L183 _public prototype_ `void GetLFR(int32 Index, float& LFR) const;`
- L185 _public prototype_ `void GetPointScales(int32 Index, float& OutValue) const;`
- L187 _public prototype_ `void GetBudDirections(int32 Index, TArray<FVector3f>& OutValue) const;`
- L189 _public prototype_ `void GetBudHormoneLevels(int32 Index, TArray<float>& OutValue) const;`
- L191 _public prototype_ `void GetBudNumbers(int32 Index, int32& OutValue) const;`
- L193 _public prototype_ `const TManagedArray<int32>& GetBudNumbersAttribute() const;`
- L195 _public prototype_ `void SetBudNumbersFromIndex(const TArray<int32>& InputArray, const int32 StartIndex);`
- L197 _public prototype_ `void GetBudLightDetected(int32 Index, TArray<float>& OutValue) const;`
- L199 _public prototype_ `const TManagedArray<TArray<float>>& GetBudLightDetectedArrays() const;`
- L201 _public prototype_ `const TManagedArray<TArray<float>>& GetBudLateralMeristemArrays() const;`
- L203 _public prototype_ `void SetBudLightDetectedArraysFromIndex(const TArray<TArray<float>>& InputArray, const int32 StartIndex);`
- L205 _public prototype_ `void GetBudDevelopment(int32 Index, TArray<int>& OutValue) const;`
- L207 _public prototype_ `void GetBudStatus(int32 Index, TArray<int>& OutValue) const;`
- L209 _public prototype_ `void SetBudStatus(int32 Index, const TArray<int>& InValue);`
- L211 _public prototype_ `void GetBudLateralMeristem(int32 Index, TArray<float>& OutValue) const;`
- L213 _public prototype_ `void GetSeedPScale(int32 Index, float& OutValue) const;`
- L215 _public prototype_ `void GetSeedPScaleRatio(int32 Index, float& OutValue) const;`
- L218 _private member_ `FManagedArrayCollection* Collection = nullptr;`
- L219 _private member_ `TManagedArrayAccessor<TArray<int32>> BranchPoints;`
- L220 _private member_ `TManagedArrayAccessor<FVector3f> Positions;`
- L221 _private member_ `TManagedArrayAccessor<float> LengthFromRoot;`
- L222 _private member_ `TManagedArrayAccessor<float> PointScaleGradient;`
- L223 _private member_ `TManagedArrayAccessor<float> HullGradient;`
- L224 _private member_ `TManagedArrayAccessor<float> MainTrunkGradient;`
- L225 _private member_ `TManagedArrayAccessor<float> GroundGradient;`
- L226 _private member_ `TManagedArrayAccessor<float> PointScale;`
- L227 _private member_ `TManagedArrayAccessor<TArray<FVector3f>> BudDirections;`
- L228 _private member_ `TManagedArrayAccessor<TArray<int>> BudStatus;`
- L229 _private member_ `TManagedArrayAccessor<TArray<float>> BudLateralMeristem;`
- L230 _private member_ `TManagedArrayAccessor<TArray<float>> BudHormoneLevels;`
- L231 _private member_ `TManagedArrayAccessor<float> PlantGradients;`
- L232 _private member_ `TManagedArrayAccessor<float> LengthFromSeed;`
- L233 _private member_ `TManagedArrayAccessor<float> SeedPScale;`
- L234 _private member_ `TManagedArrayAccessor<float> SeedPScaleRatio;`
- L235 _private member_ `TManagedArrayAccessor<int32> BudNumber;`
- L236 _private member_ `TManagedArrayAccessor<float> NjordPixelIndex;`
- L237 _private member_ `TManagedArrayAccessor<TArray<float>> BudLightDetected;`
- L238 _private member_ `TManagedArrayAccessor<TArray<int>> BudDevelopment;`
- L239 _private member_ `TManagedArrayAccessor<float> TextureCoordV;`
- L240 _private member_ `TManagedArrayAccessor<float> TextureCoordUOffset;`
- L241 _private member_ `TManagedArrayAccessor<FVector2f> URange;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace Facades` (scope `PV`)
- L13 _macro_ `#define FILL_COLLECTION_ATTRIBUTE(Accessor, InputArray) \`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVProfileFacade.h` (Public)


#### class `PV::Facades::FPlantProfileFacade`  
`class FPlantProfileFacade`  
_L13-36_
- desc: FTrunkProfileFacade is used to access and manipulate Trunk profile data for a ProceduralVegetation's FManagedArrayCollection
- L16 _public prototype_ `FPlantProfileFacade(FManagedArrayCollection& InCollection);`
- L17 _public prototype_ `FPlantProfileFacade(const FManagedArrayCollection& InCollection);`
- L19 _public function_ `bool IsConst() const`
- L21 _public prototype_ `bool IsValid() const;`
- L23 _public function_ `int32 NumProfileEntries() const`
- L25 _public prototype_ `int32 AddProfileEntry(const TArray<float>& InProfilePoints);`
- L27 _public prototype_ `const TArray<float>& GetProfilePoints(const int32 Index) const;`
- L30 _protected prototype_ `void DefineSchema();`
- L32 _protected member_ `const FManagedArrayCollection& ConstCollection;`
- L33 _protected member_ `FManagedArrayCollection* Collection = nullptr;`
- L35 _protected member_ `TManagedArrayAccessor<TArray<float>> ProfilePointsAttribute;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace PV`
- L8 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVRenderingFacade.h` (Public)


#### class `PV::Facades::FPVRenderingFacade`  
`class FPVRenderingFacade : public GeometryCollection::Facades::FRenderingFacade`  
_L13-30_
- inherits: `GeometryCollection::Facades::FRenderingFacade`
- desc: FPVRenderingFacade is used to build a collection that contains the render data required to render Procedural Vegetation Add functions to access and modify render data for Procedural Vegetation
- L16 _public prototype_ `FPVRenderingFacade(FManagedArrayCollection& InSelf);`
- L17 _public prototype_ `FPVRenderingFacade(const FManagedArrayCollection& InSelf);`
- L19 _public prototype_ `void DefineSchema();`
- L21 _public prototype_ `const FFoliageFacade& GetFoliageFacade() const;`
- L23 _public prototype_ `void CopyFrom(const FManagedArrayCollection& Other);`
- L26 _protected member_ `const FManagedArrayCollection& ConstProceduralVegetationCollection;`
- L27 _protected member_ `FManagedArrayCollection* ProceduralVegetationCollection = nullptr;`
- L29 _protected member_ `FFoliageFacade FoliageFacade;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace PV`
- L7 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Facades/PVTreeFacade.h` (Public)


#### enum `ESkeletonVisualizationModes`  
`enum class ESkeletonVisualizationModes : uint8`  
_L14-32_
- reflection: `UENUM()`
- L16 _public enumerator_ `None UMETA(Category="")`
- L17 _public enumerator_ `GravitationalStress UMETA(Category="Gravity")`
- L18 _public enumerator_ `CellDensity UMETA(Category="Gravity")`
- L19 _public enumerator_ `CellWeight UMETA(Category="Gravity")`
- L20 _public enumerator_ `LightSenescence UMETA(Category="Light")`
- L21 _public enumerator_ `BranchLight UMETA(Category="Light")`
- L22 _public enumerator_ `LightAbscissionRetention UMETA(Category="Light")`
- L23 _public enumerator_ `AgeSenescence UMETA(Category="Age")`
- L24 _public enumerator_ `AgeAbscissionRetention UMETA(Category="Age")`
- L25 _public enumerator_ `Apical UMETA(Category="Auxin")`
- L26 _public enumerator_ `Auxin UMETA(Category="Auxin")`
- L27 _public enumerator_ `Radical UMETA(Category="Auxin")`
- L28 _public enumerator_ `Ethylene UMETA(Category="Ethlyene")`
- L29 _public enumerator_ `AuxinRetention UMETA(Category="Ethlyene")`
- L30 _public enumerator_ `Cytokinin UMETA(Category="Cytokinin")`
- L31 _public enumerator_ `BranchGeneration UMETA(Category="Debug")`

#### struct `PV::Facades::FRemoveEntriesResult`  
`struct FRemoveEntriesResult`  
_L36-41_
- L38 _public member_ `TMap<int32, int32> PointsOldIDsToNewIDs;`
- L39 _public member_ `TMap<int32, int32> BranchesOldIDsToNewIDs;`
- L40 _public member_ `TMap<int32, int32> FoliageInstancesOldIDsToNewIDs;`

#### class `PV::Facades::FTreeFacade`  
`class FTreeFacade`  
_L50-63_
- desc: FTreeFacade is used to remove branches, points, and foliage instances from a tree collection. It does not validate whether the input data is consistent i.e. the points actually belong to the same branches that are asking to be removed etc.
- L53 _public prototype_ `static FRemoveEntriesResult RemoveEntriesAndReIndexAttributes(FManagedArrayCollection& OutCollection, TArray<bool>& PointsToRemove, TArray<bool>& BranchesToRemove, TArray<bool>& FoliageInstancesToRemove);`
- L56 _public prototype_ `static void RemoveBranches(const FBranchFacade& InBranchFacade, TArray<int>& InBranchesToRemove, FManagedArrayCollection& OutCollection);`
- L58 _public prototype_ `static int32 GetBranchGenerationNumber(const FManagedArrayCollection& Collection, int32 BranchIndex);`
- L60 _public prototype_ `static TArray<float> GetVisualizationValues(const FManagedArrayCollection& Collection, ESkeletonVisualizationModes VisualizationMode);`
- L62 _private prototype_ `static void GatherChildBranches(const FBranchFacade& InBranchFacade, const int InParentIndex, TArray<int32>& OutBranchesToRemove);`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace PV`
- L34 _namespace_ `namespace Facades` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Helpers/PVAnalyticsHelper.h` (Public)


#### enum `PV::Analytics::EExportResult`  
`enum class EExportResult`  
_L23-28_
- L25 _public enumerator_ `Failed`
- L26 _public enumerator_ `Success`
- L27 _public enumerator_ `Skipped`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace Analytics` (scope `PV`)
- L13 _prototype_ `void SendSessionStartedEvent();` (scope `PV::Analytics`)
- L14 _prototype_ `void SendSessionEndedEvent(const double InTimeInSeconds);` (scope `PV::Analytics`)
- L15 _prototype_ `void SendNodeAddedEvent(const FString& InNodeType);` (scope `PV::Analytics`)
- L16 _prototype_ `void SendNodeTweakedEvent(const FString& InNodeType, const FProperty* InProperty);` (scope `PV::Analytics`)
- L17 _prototype_ `void SendMaterialChangeEvent(FString InMatPath);` (scope `PV::Analytics`)
- L18 _prototype_ `void SendFoliageMeshChangeEvent(FString InFoliageMeshPath);` (scope `PV::Analytics`)
- L19 _prototype_ `void SendWindSettingsChangeEvent(FString InPath);` (scope `PV::Analytics`)
- L20 _prototype_ `TArray<FAnalyticsEventAttribute> GatherExportCommonAttributes(const FManagedArrayCollection& InCollection, const FPVExportParams& InExportParam);` (scope `PV::Analytics`)
- L21 _prototype_ `void SendExportStartEvent(const TArray<FAnalyticsEventAttribute>& InCommonAttributes);` (scope `PV::Analytics`)
- L29 _prototype_ `void SendExportFinishedEvent(TArray<FAnalyticsEventAttribute> InCommonAttributes, float InTotalTimeInSeconds, EExportResult ExportResult);` (scope `PV::Analytics`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Helpers/PVUtilities.h` (Public)


#### struct `FLoopDebugStepper`  
`struct FLoopDebugStepper`  
_L43-65_
- reflection: `USTRUCT()`
- L48 _public member_ `bool bDebug = false;` — `UPROPERTY(EditAnywhere, Category="Loop Debug", meta=(InlineEditConditionToggle))`
- L51 _public member_ `mutable bool bDebugFocus = false;` — `UPROPERTY(EditAnywhere, Category="Loop Debug")`
- L54 _public member_ `uint32 MaxSteps = 1;` — `UPROPERTY(EditAnywhere, Category="Loop Debug", meta=(EditCondition="bDebug"))`
- L56 _public function_ `void IncrementStep()`
- L61 _public function_ `void DecrementStep()`

#### struct `FPVParamDebuggerState`  
`struct FPVParamDebuggerState`  
_L67-74_
- L69 _public member_ `UPVData* Data = nullptr;`
- L72 _public member_ `FPVDebugSettings DebugSettings;`

#### struct `FPVLoopDebuggerState`  
`struct FPVLoopDebuggerState`  
_L76-110_
- L78 _public member_ `uint32 NumSteps = 0;`
- L79 _public member_ `const FLoopDebugStepper* LoopDebugStepper = nullptr;`
- L80 _public member_ `UPVData* Data = nullptr;`
- L82 _public member_ `bool bComplete = false;`
- L84 _public function_ `bool IsLastLoopIteration() const`
- L90 _public function_ `bool IterationsCompleted() const`
- L97 _public function_ `FPVDebugSettings GetDebugSettings() const`
- L103 _public function_ `void SetDebugSettings(FPVDebugSettings&& InSettings) const`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace PV`
- L17 _namespace_ `namespace Utilities` (scope `PV`)
- L19 _prototype_ `bool DebugModeEnabled();` (scope `PV::Utilities`)
- L21 _delegate_ `DECLARE_DELEGATE_OneParam(FFoliageComponentCreatedCallback, UMeshComponent*);`
- L21 _prototype_ `DECLARE_DELEGATE_OneParam(FFoliageComponentCreatedCallback, UMeshComponent*);` (scope `PV::Utilities`)
- L23 _prototype_ `bool ValidateAssetPathAndName(const FString& MeshName, const FString& Path, UClass* InClass, FString& OutError);` (scope `PV::Utilities`)
- L25 _prototype_ `bool IsFileNameValid(FName FileName, FText& Reason);` (scope `PV::Utilities`)
- L26 _prototype_ `bool DoesConflictingPackageExist(const FString& PackageName, UClass* InClass);` (scope `PV::Utilities`)
- L27 _prototype_ `bool PackageExists(const FString& LongPackageName, UClass* AssetClass);` (scope `PV::Utilities`)
- L28 _prototype_ `int32 GetMeshTriangles(const FString InMeshPath);` (scope `PV::Utilities`)
- L29 _prototype_ `FLinearColor GetRandomHueColor(float Alpha);` (scope `PV::Utilities`)
- L31 _prototype_ `bool IsValidGrowthData(const FManagedArrayCollection& Collection);` (scope `PV::Utilities`)
- L34 _prototype_ `template <typename T> TArray<T> LerpArrayElements(const TArray<T>& InArray1, const TArray<T>& InArray2, const float Alpha);` (scope `PV::Utilities`)
- L36 _prototype_ `int32 AddInterpolatedPointToCollection(FManagedArrayCollection& OutCollection, int32 BranchIndex, const int32 CurrentPointIndex, const int32 NextPointIndex, const float Alpha, const int32 BudNumber, bool CalculatePixelIndex = false);` (scope `PV::Utilities`)
- L39 _prototype_ `bool DoesAssetExist(const FSoftObjectPath& InPath);` (scope `PV::Utilities`)
- L115 _variable_ `inline FCriticalSection GlobalPVDebuggerLock;`
- L116 _variable_ `inline TUniquePtr<FPVParamDebuggerState> GlobalPVDebuggerState;`
- L118 _macro_ `#define PVE_DEBUG_LOCK() \`
- L121 _macro_ `#define PVE_DEBUG_UNLOCK() \`
- L124 _macro_ `#define PVE_PARAM_DEBUG_INIT(InputSettings, PVData) \`
- L131 _macro_ `#define PVE_PARAM_DEBUG_POINT_PARAM(InParamName, InPivot) \`
- L139 _macro_ `#define PVE_PARAM_DEBUG_DIRECTION_PARAM(InParamName, InPivot, InDirection) \`
- L147 _macro_ `#define PVE_PARAM_DEBUG_VECTOR_PARAM(InParamName, InPivot, InVector) \`
- L155 _macro_ `#define PVE_PARAM_DEBUG_TEXT_PARAM(InParamName, InPivot, InText) \`
- L163 _macro_ `#define PVE_PARAM_DEBUG_END() \`
- L170 _variable_ `inline TUniquePtr<FPVLoopDebuggerState> GlobalPVLoopDebuggerState;`
- L172 _macro_ `#define PVE_LOOP_DEBUG_INIT(InputSettings, LoopDebugStepperName, PVData) \`
- L178 _macro_ `#define PVE_LOOP_DEBUG_PARAMS_START() \`
- L188 _macro_ `#define PVE_LOOP_DEBUG_POINT_PARAM(InParamName, InPivot) \`
- L195 _macro_ `#define PVE_LOOP_DEBUG_DIRECTION_PARAM(InParamName, InPivot, InDirection) \`
- L202 _macro_ `#define PVE_LOOP_DEBUG_VECTOR_PARAM(InParamName, InPivot, InVector) \`
- L209 _macro_ `#define PVE_LOOP_DEBUG_TEXT_PARAM(InParamName, InPivot, InText) \`
- L216 _macro_ `#define PVE_LOOP_DEBUG_PARAMS_END() \`
- L220 _macro_ `#define PVE_OUTER_LOOP_DEBUG_CHECK(ExitMethod) \`
- L229 _macro_ `#define PVE_LOOP_DEBUG_CHECK(ExitMethod) \`
- L240 _macro_ `#define PVE_LOOP_DEBUG_STEP(ExitMethod) \`
- L247 _macro_ `#define PVE_LOOP_DEBUG_END() \`
- L252 _macro_ `#define PVE_DEBUG_LOCK()`
- L253 _macro_ `#define PVE_DEBUG_UNLOCK()`
- L255 _macro_ `#define PVE_PARAM_DEBUG_INIT(InputSettings, PVData)`
- L257 _macro_ `#define PVE_PARAM_DEBUG_POINT_PARAM(InParamName, InPivot)`
- L258 _macro_ `#define PVE_PARAM_DEBUG_DIRECTION_PARAM(InParamName, InPivot, InDirection)`
- L259 _macro_ `#define PVE_PARAM_DEBUG_VECTOR_PARAM(InParamName, InPivot, InVector)`
- L260 _macro_ `#define PVE_PARAM_DEBUG_TEXT_PARAM(InParamName, InPivot, InText)`
- L262 _macro_ `#define PVE_PARAM_DEBUG_END()`
- L264 _macro_ `#define PVE_LOOP_DEBUG_INIT(InputSettings, LoopDebugStepperName, PVData)`
- L266 _macro_ `#define PVE_LOOP_DEBUG_PARAMS_START()`
- L267 _macro_ `#define PVE_LOOP_DEBUG_POINT_PARAM(InParamName, InPivot)`
- L268 _macro_ `#define PVE_LOOP_DEBUG_DIRECTION_PARAM(InParamName, InPivot, InDirection)`
- L269 _macro_ `#define PVE_LOOP_DEBUG_VECTOR_PARAM(InParamName, InPivot, InVector)`
- L270 _macro_ `#define PVE_LOOP_DEBUG_TEXT_PARAM(InParamName, InPivot, InText)`
- L271 _macro_ `#define PVE_LOOP_DEBUG_PARAMS_END()`
- L273 _macro_ `#define PVE_OUTER_LOOP_DEBUG_CHECK(ExitMethod)`
- L274 _macro_ `#define PVE_LOOP_DEBUG_CHECK(ExitMethod)`
- L275 _macro_ `#define PVE_LOOP_DEBUG_STEP(ExitMethod)`
- L277 _macro_ `#define PVE_LOOP_DEBUG_END()`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVBaseSettings.h` (Public)


#### class `UPVBaseSettings`  
`class UPVBaseSettings : public UPCGSettings, public IPVRenderSettings`  
_L12-73_
- reflection: `UCLASS(BlueprintType, Abstract, HideCategories=(Debug, AssetInfo), ClassGroup = (Procedural))`
- inherits: `UPCGSettings,IPVRenderSettings`
- L17 _public prototype_ `UPVBaseSettings();`
- L20 _public function_ `virtual EPCGSettingsType GetType() const override`
- L26 _public function_ `virtual FText GetCategoryOverride() const` — Free-form category override for the PV action menu. Return an empty FText to fall back to the EPCGSettingsType enum-derived name.
- L28 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L30 _public function_ `virtual TArray<EPVRenderType> GetCurrentRenderTypes() const override`
- L31 _public function_ `virtual TMap<UObject*, FTransform> GetViewportObjects() const override`
- L32 _public prototype_ `virtual void SetCurrentRenderType (TArray<EPVRenderType> InRenderTypes) override;`
- L34 _public function_ `virtual const FPVDebugSettings& GetDebugVisualizationSettings() const override`
- L35 _public function_ `virtual bool IsDebug() const override`
- L36 _public function_ `virtual bool IsCollectionRenderingEnabled() const override`
- L37 _public function_ `virtual bool IsVisualizationCollectionsRenderingEnabled() const override`
- L38 _public function_ `virtual ELevelViewportType GetPreferredViewportType() const`
- L40 _public function_ `virtual bool IsInspectionLocked() const override`
- L41 _public function_ `virtual void SetInspectionLocked(bool bInLocked) override`
- L43 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L45 _public function_ `virtual EPCGNodeToolStartBehavior GetNodeToolStartBehaviour() const override`
- L49 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L50 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L51 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L52 _protected function_ `virtual bool HasExecutionDependencyPin() const override`
- L54 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const;`
- L55 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const;`
- L60 _public member_ `bool bOnlyExposeInDebugMode = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AssetInfo, AssetRegistrySearchable, meta = (PCGNoHash))`
- L66 _protected member_ `FPVSettingsVisualization Visualization;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta=(EditCondition = "bDebug", EditConditionHides))`
- L71 _private member_ `bool bLockInspection = false;`

#### class `FPVBaseElement`  
`class FPVBaseElement : public IPCGElement`  
_L75-80_
- inherits: `IPCGElement`
- L78 _protected prototype_ `virtual void PostExecuteInternal(FPCGContext* InContext) const override;`
- L79 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* Context) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVExportSettings.h` (Public)


#### class `UPVExportSettings`  
`class UPVExportSettings : public UPVBaseSettings`  
_L10-42_
- reflection: `UCLASS(ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L15 _public prototype_ `UPVExportSettings();`
- L18 _public function_ `virtual FName GetDefaultNodeName() const override`
- L19 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L20 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L21 _public function_ `virtual EPCGSettingsType GetType() const override`
- L22 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L23 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L24 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L25 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L29 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L30 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L32 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L35 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L36 _protected prototype_ `virtual EPCGChangeType GetChangeTypeForProperty(FPropertyChangedEvent& PropertyChangedEvent) const override;`
- L41 _public member_ `FPVExportParams ExportSettings;` — `UPROPERTY(EditAnywhere, Category = ExportSettings, meta = (PCG_Overridable, ShowOnlyInnerProperties))`

#### class `FPVExportElement`  
`class FPVExportElement : public FPVBaseElement`  
_L44-49_
- inherits: `FPVBaseElement`
- L46 _private prototype_ `virtual bool ExecuteInternal(FPCGContext* Context) const override;`
- L48 _private function_ `virtual bool CanExecuteOnlyOnMainThread(FPCGContext* Context) const override`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVManualEditSettings.h` (Public)


#### enum `EPointSelectionSmoothnessMethod`  
`enum class EPointSelectionSmoothnessMethod: uint8`  
_L10-19_
- reflection: `UENUM()`
- L12 _public enumerator_ `Linear`
- L13 _public enumerator_ `Smooth`
- L14 _public enumerator_ `Sphere`
- L15 _public enumerator_ `Root`
- L16 _public enumerator_ `Sharp`
- L17 _public enumerator_ `Sine`
- L18 _public enumerator_ `Constant`

#### enum `ESkeletonSelectionMode`  
`enum class ESkeletonSelectionMode: uint8`  
_L22-27_
- reflection: `UENUM()`
- L24 _public enumerator_ `SelectByTreeDistance`
- L25 _public enumerator_ `SelectByNeighbours`
- L26 _public enumerator_ `SelectByEuclideanDistance`

#### enum `EBranchRemovalMode`  
`enum class EBranchRemovalMode: uint8`  
_L30-34_
- reflection: `UENUM()`
- L32 _public enumerator_ `RemoveBranch`
- L33 _public enumerator_ `TrimBranch`

#### enum `EManualEditMode`  
`enum class EManualEditMode: uint8`  
_L37-41_
- reflection: `UENUM()`
- L39 _public enumerator_ `TRS`
- L40 _public enumerator_ `BranchRemoval`

#### struct `FPVSkeletonSelectionParams`  
`struct FPVSkeletonSelectionParams`  
_L44-61_
- reflection: `USTRUCT()`
- L49 _public member_ `EPointSelectionSmoothnessMethod SelectionFalloff = EPointSelectionSmoothnessMethod::Smooth;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta=(Tooltip="How selection weight falls off from the picked point.\n\nDetermines how strongly nearby points are co-selected. Linear / Smooth / Sphere / Root / Sharp / Sine / Constant."))`
- L52 _public member_ `ESkeletonSelectionMode SkeletonSelectionMode = ESkeletonSelectionMode::SelectByNeighbours;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta=(Tooltip="How to measure distance for selection: tree-distance, neighbours, or 3D distance.\n\nSelectByTreeDistance: walks along branch graph from the picked point. SelectByNeighbours: N hops along skeleton connections. SelectByEuclideanDistance: standard radial selection."))`
- L56 _public member_ `int32 NumPointsSelection = 0;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (UIMin=0, ClampMin=0, EditCondition="SkeletonSelectionMode == ESkeletonSelectionMode::SelectByNeighbours", EditConditionHides, Tooltip="Number of neighbouring points to include in the selection.\n\nWalks this many connections from the picked point. 0 = only the picked point itself. Higher = larger soft-selection."))`
- L60 _public member_ `float SelectionDistance = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta = (UIMin=0, ClampMin=0, EditCondition="SkeletonSelectionMode != ESkeletonSelectionMode::SelectByNeighbours", EditConditionHides, Tooltip="Selection radius (in skeleton or world units).\n\nFor SelectByTreeDistance: distance along the skeleton graph. For SelectByEuclideanDistance: straight-line 3D distance in cm. Higher = more points caught."))`

#### struct `FPVBranchRemovalParams`  
`struct FPVBranchRemovalParams`  
_L64-70_
- reflection: `USTRUCT()`
- L69 _public member_ `EBranchRemovalMode BranchRemovalMode = EBranchRemovalMode::TrimBranch;` — `UPROPERTY(EditAnywhere, Category = "Branch Removal", meta=(Tooltip="Remove the entire branch or just trim at the click point.\n\nRemoveBranch: deletes the branch and all its children. TrimBranch: cuts at the picked point."))`

#### struct `FPVManualEditParams`  
`struct FPVManualEditParams`  
_L73-93_
- reflection: `USTRUCT()`
- L78 _public member_ `EManualEditMode ManualEditMode = EManualEditMode::TRS;` — `UPROPERTY(EditAnywhere, Transient, Category = "Tool", meta=(Tooltip="Active editing mode: TRS (transform) or Branch Removal.\n\nTRS: shows a translate/rotate gizmo on the selected points. BranchRemoval: click branches to remove or trim them."))`
- L82 _public member_ `FPVSkeletonSelectionParams SkeletonSelectionParams;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta=(ShowOnlyInnerProperties, EditCondition="ManualEditMode == EManualEditMode::TRS", EditConditionHides))`
- L86 _public member_ `FPVBranchRemovalParams BranchRemovalParams;` — `UPROPERTY(EditAnywhere, Category = "Selection", meta=(ShowOnlyInnerProperties, EditCondition="ManualEditMode == EManualEditMode::BranchRemoval", EditConditionHides))`
- L89 _public member_ `TArray<FVector3f> RelativeOffsets;` — `UPROPERTY()`
- L92 _public member_ `TArray<bool> RemovedPoints;` — `UPROPERTY()`

#### class `UPVManualEditSettings`  
`class UPVManualEditSettings : public UPVBaseSettings`  
_L96-127_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L102 _public prototype_ `virtual FName GetDefaultNodeName() const override;`
- L103 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L104 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L105 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L107 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L111 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L112 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L114 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L119 _public prototype_ `void ClearTranformations();` — `UFUNCTION(CallInEditor, Category = "Edits", DisplayName="Clear Transformations", meta=(Tooltip="Reset all manual transforms.\n\nRemoves every manual translate/rotate/scale edit, restoring the skeleton to its source state. Does not affect branch removals."))`
- L122 _public prototype_ `void ClearRemovals();` — `UFUNCTION(CallInEditor, Category = "Edits", DisplayName="Clear Removals", meta=(Tooltip="Restore all removed branches.\n\nUndoes every branch removal, restoring all branches to the source state. Does not affect transforms."))`
- L126 _public member_ `FPVManualEditParams ManualEditSettings;` — `UPROPERTY(EditAnywhere, Category = "Manual Edit", meta = (ShowOnlyInnerProperties))`

#### class `FPVManualEditElement`  
`class FPVManualEditElement : public FPVBaseElement`  
_L129-133_
- inherits: `FPVBaseElement`
- L132 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVObjectInteractionSettings.h` (Public)


#### enum `EPVCollisionType`  
`enum class EPVCollisionType`  
_L10-15_
- reflection: `UENUM()`
- L12 _public enumerator_ `AVOID UMETA(DisplayName = "Avoid")`
- L13 _public enumerator_ `TRIM_OUTSIDE UMETA(DisplayName = "Trim Outside")`
- L14 _public enumerator_ `TRIM_INSIDE UMETA(DisplayName = "Trim Inside")`

#### struct `FPVColliderParams`  
`struct FPVColliderParams`  
_L18-36_
- reflection: `USTRUCT()`
- L23 _public member_ `TSoftObjectPtr<UStaticMesh> Mesh;` — `UPROPERTY(EditAnywhere, Category = "Collider", meta=(Tooltip="The static mesh used as the collider shape.\n\nAny static mesh — typically simple primitives like boxes, spheres, or capsules. Complex meshes work but cost more per evaluation."))`
- L26 _public member_ `FTransform Transform;` — `UPROPERTY(EditAnywhere, Category = "Collider", meta=(Tooltip="World-space transform of the collider.\n\nPosition, rotation, and scale of the collider relative to the plant's origin."))`
- L29 _public member_ `EPVCollisionType CollisionType = EPVCollisionType::AVOID;` — `UPROPERTY(EditAnywhere, Category = "Collider", meta=(Tooltip="How growth responds to this collider.\n\nAvoid: branches bend around the volume. Trim Outside: keep only growth inside the volume. Trim Inside: remove growth inside the volume."))`
- L32 _public member_ `int32 SmoothnessAmount = 0;` — `UPROPERTY(EditAnywhere, Category = "Collider", meta=(EditCondition = "CollisionType == EPVCollisionType::AVOID", EditConditionHides, UIMin=0, ClampMin=0, Tooltip="Smoothing iterations applied to deflected branches.\n\nHigher values create smoother bends around the collider. 0 = sharp deflection at contact; higher values produce gradual curves over more points."))`
- L35 _public member_ `float SmoothnessFactor = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Collider", meta=(EditCondition = "CollisionType == EPVCollisionType::AVOID", EditConditionHides, UIMin=0, UIMax=1, ClampMin=0, ClampMax=1, Tooltip="Strength of the smoothing per iteration.\n\n1.0 = full smoothing per iteration. Lower values produce more subtle smoothing."))`

#### struct `FPVObjectInteractionParams`  
`struct FPVObjectInteractionParams`  
_L39-45_
- reflection: `USTRUCT()`
- L44 _public member_ `TArray<FPVColliderParams> Colliders;` — `UPROPERTY(EditAnywhere, Category = "Colliders", meta=(Tooltip="List of collider volumes that affect growth.\n\nEach entry defines one collider's mesh, transform, and interaction mode. The list is evaluated in order."))`

#### class `UPVObjectInteractionSettings`  
`class UPVObjectInteractionSettings : public UPVBaseSettings`  
_L48-91_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L54 _public function_ `virtual FName GetDefaultNodeName() const override`
- L59 _public function_ `virtual FText GetNodeTooltipText() const override`
- L67 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L69 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L71 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L78 _protected prototype_ `virtual FPCGDataTypeIdentifier GetInputPinTypeIdentifier() const override;`
- L79 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L81 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L85 _public member_ `FPVObjectInteractionParams ObjectInteractionSettings;` — `UPROPERTY(EditAnywhere, Category = "Object Interaction", meta = (ShowOnlyInnerProperties))`
- L89 _public member_ `FLoopDebugStepper LoopDebugStepper;` — `UPROPERTY(EditAnywhere, Category = "Loop Debug", meta=(EditCondition = "bDebug", EditConditionHides))`

#### class `FPVObjectInteractionElement`  
`class FPVObjectInteractionElement : public FPVBaseElement`  
_L93-97_
- inherits: `FPVBaseElement`
- L96 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVPointScatterSettings.h` (Public)


#### class `UPVPointScatterSettings`  
`class UPVPointScatterSettings : public UPCGSubgraphSettings`  
_L9-38_
- reflection: `UCLASS(BlueprintType, HideCategories=(Debug), ClassGroup = (Procedural))`
- inherits: `UPCGSubgraphSettings`
- L13 _public prototype_ `UPVPointScatterSettings(const FObjectInitializer& InObjectInitializer);`
- L15 _public function_ `virtual bool IsDynamicGraph() const override`
- L16 _public function_ `virtual FString GetAdditionalTitleInformation() const override`
- L19 _public function_ `virtual FName GetDefaultNodeName() const override`
- L20 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L21 _public function_ `virtual FText GetNodeTooltipText() const override`
- L28 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L29 _public function_ `virtual EPCGSettingsType GetType() const override`
- L30 _public function_ `virtual bool GetPinExtraIcon(const UPCGPin* InPin, FName& OutExtraIcon, FText& OutTooltip) const override`
- L36 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L37 _protected function_ `virtual bool HasExecutionDependencyPin() const override`

#### class `FPVPointScatterElement`  
`class FPVPointScatterElement : public FPCGSubgraphElement`  
_L40-44_
- inherits: `FPCGSubgraphElement`
- L43 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVRenderSettings.h` (Public)


#### class `UPVRenderSettings`  
`class UPVRenderSettings : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IPVRenderSettings`  
`class IPVRenderSettings`  
_L20-42_
- L27 _public prototype_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const = 0;`
- L28 _public prototype_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const = 0;`
- L29 _public prototype_ `virtual TArray<EPVRenderType> GetCurrentRenderTypes() const = 0;`
- L30 _public prototype_ `virtual TMap<UObject*, FTransform> GetViewportObjects() const = 0;`
- L31 _public prototype_ `virtual void SetCurrentRenderType(TArray<EPVRenderType> InRenderTypes) = 0;`
- L32 _public prototype_ `virtual const FPVDebugSettings& GetDebugVisualizationSettings() const = 0;`
- L33 _public prototype_ `virtual ELevelViewportType GetPreferredViewportType() const = 0;`
- L35 _public prototype_ `virtual bool IsDebug() const = 0;`
- L36 _public prototype_ `virtual bool IsCollectionRenderingEnabled() const = 0;`
- L37 _public prototype_ `virtual bool IsVisualizationCollectionsRenderingEnabled() const = 0;`
- L39 _public function_ `virtual bool IsInspectionLocked() const`
- L40 _public function_ `virtual void SetInspectionLocked(bool bInLocked)`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVSubgraphSettings.h` (Public)


#### class `UPVSubgraphSettings`  
`class UPVSubgraphSettings : public UPCGBaseSubgraphSettings, public IPVRenderSettings`  
_L15-94_
- reflection: `UCLASS(BlueprintType, HideCategories=(Debug, AssetInfo), ClassGroup = (Procedural))`
- inherits: `UPCGBaseSubgraphSettings,IPVRenderSettings`
- L20 _public prototype_ `UPVSubgraphSettings(const FObjectInitializer& InObjectInitializer);`
- L23 _public function_ `virtual FName GetDefaultNodeName() const override`
- L24 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L25 _public function_ `virtual FText GetNodeTooltipText() const override`
- L32 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L33 _public function_ `virtual EPCGSettingsType GetType() const override`
- L34 _public prototype_ `virtual UObject* GetJumpTargetForDoubleClick() const override;`
- L35 _public function_ `virtual bool GetPinExtraIcon(const UPCGPin* InPin, FName& OutExtraIcon, FText& OutTooltip) const override`
- L37 _public function_ `virtual TArray<EPVRenderType> GetSupportedRenderTypes() const override`
- L38 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L39 _public function_ `virtual TArray<EPVRenderType> GetCurrentRenderTypes() const override`
- L40 _public function_ `virtual TMap<UObject*, FTransform> GetViewportObjects() const override`
- L41 _public prototype_ `virtual void SetCurrentRenderType (TArray<EPVRenderType> InRenderTypes) override;`
- L43 _public function_ `virtual const FPVDebugSettings& GetDebugVisualizationSettings() const override`
- L44 _public function_ `virtual bool IsDebug() const override`
- L45 _public function_ `virtual bool IsCollectionRenderingEnabled() const override`
- L46 _public function_ `virtual bool IsVisualizationCollectionsRenderingEnabled() const override`
- L47 _public function_ `virtual ELevelViewportType GetPreferredViewportType() const`
- L49 _public function_ `virtual bool IsInspectionLocked() const override`
- L50 _public function_ `virtual void SetInspectionLocked(bool bInLocked) override`
- L54 _public prototype_ `virtual UPCGNode* CreateNode() const override;`
- L55 _public prototype_ `virtual FString GetAdditionalTitleInformation() const override;`
- L56 _public prototype_ `virtual FPCGDataTypeIdentifier GetCurrentPinTypesID(const UPCGPin* InPin) const override;`
- L59 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L60 _protected prototype_ `virtual void SetSubgraphInternal(UPCGGraphInterface* InGraph) override;`
- L61 _protected function_ `virtual bool HasExecutionDependencyPin() const override`
- L62 _protected prototype_ `virtual TArray<FPCGPinProperties> OutputPinProperties() const override;`
- L65 _protected prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L66 _protected prototype_ `virtual EPCGChangeType GetChangeTypeForProperty(const FName& InPropertyName) const override;`
- L71 _private member_ `TObjectPtr<UProceduralVegetationInstance> SubgraphInstance;` — `UPROPERTY(VisibleAnywhere, Category = Properties, Instanced, meta = (NoResetToDefault, Tooltip="The Procedural Vegetation graph instance to embed.\n\nPick a UProceduralVegetationInstance asset. The subgraph's nodes execute within this node's context. Edits to the source asset propagate to this instance."))`
- L75 _public prototype_ `virtual UPCGGraphInterface* GetSubgraphInterface() const override;`
- L77 _public function_ `virtual UPCGGraphInterface* GetOriginalSubgraphInterface() const override`
- L81 _public function_ `virtual bool IsDynamicGraph() const override`
- L86 _protected member_ `FPVSettingsVisualization Visualization;` — `UPROPERTY(EditAnywhere, Category = DebugSettings, meta=(EditCondition = "bDebug", EditConditionHides, Tooltip="Debug visualization overrides for the subgraph."))`
- L91 _private member_ `bool bLockInspection = false;`

#### class `FPVSubgraphElement`  
`class FPVSubgraphElement : public FPCGSubgraphElement`  
_L96-101_
- inherits: `FPCGSubgraphElement`
- L99 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`
- L100 _protected prototype_ `virtual void PostExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Nodes/PVTrunkTextureSetupSettings.h` (Public)


#### class `UPVTrunkTextureSetupSettings`  
`class UPVTrunkTextureSetupSettings : public UPVBaseSettings`  
_L10-59_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPVBaseSettings`
- L15 _public prototype_ `UPVTrunkTextureSetupSettings();`
- L18 _public function_ `virtual FName GetDefaultNodeName() const override`
- L19 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L20 _public function_ `virtual FText GetNodeTooltipText() const override`
- L27 _public prototype_ `virtual FLinearColor GetNodeTitleColor() const override;`
- L28 _public prototype_ `virtual FText GetCategoryOverride() const override;`
- L30 _public function_ `virtual TArray<EPVRenderType> GetDefaultRenderType() const override`
- L31 _public prototype_ `virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `virtual void PostLoad() override;`
- L33 _public prototype_ `virtual void PostEditUndo() override;`
- L36 _public function_ `bool GetTextureBaked() const`
- L39 _protected prototype_ `virtual TArray<FPCGPinProperties> InputPinProperties() const override;`
- L40 _protected prototype_ `virtual FPCGDataTypeIdentifier GetOutputPinTypeIdentifier() const override;`
- L41 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L45 _public prototype_ `void BakeTextures();` — `UFUNCTION(Category=NoCategory)`
- L48 _public member_ `FPVTrunkTextureSetupParams TrunkTextureSetupParams;` — `UPROPERTY(EditAnywhere, Category=TrunkTextureSetup, meta=(RelativeToGameDir, ShowOnlyInnerProperties))`
- L51 _public member_ `FPVTrunkTextureSetupInfo TrunkTextureSetupInfo;` — `UPROPERTY()`
- L54 _public member_ `FString BakingErrors;` — `UPROPERTY()`
- L58 _private member_ `bool bTexturesBaked = false;` — `UPROPERTY()`

#### class `FPVTrunkTextureSetupElement`  
`class FPVTrunkTextureSetupElement : public FPVBaseElement`  
_L61-65_
- inherits: `FPVBaseElement`
- L64 _protected prototype_ `virtual bool ExecuteInternal(FPCGContext* InContext) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/PVWindSettings.h` (Public)


#### class `UPVWindSettings`  
`class UPVWindSettings : public UDataAsset`  
_L10-20_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UDataAsset`
- L16 _public member_ `bool bOverwriteExisting = false;` — `UPROPERTY(EditAnywhere, Category="Wind Settings", meta=(Tooltip="Overwrite existing wind data on the target mesh.\n\nWhen on, replaces any wind data already attached to the exported skeletal mesh. Off = leave existing wind setup intact."))`
- L19 _public member_ `TArray<FDynamicWindSimulationGroupData> SimulationGroupData;` — `UPROPERTY(EditAnywhere, Category="Wind Settings", meta=(Tooltip="List of wind simulation groups (provided by the Dynamic Wind plugin).\n\nEach entry configures one wind simulation group's stiffness, damping, and influence parameters. See the Dynamic Wind plugin docs for per-field details."))`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Params/PVExportParams.h` (Public)


#### enum `EPVExportMeshType`  
`enum class EPVExportMeshType: uint8`  
_L11-15_
- reflection: `UENUM()`
- L13 _public enumerator_ `StaticMesh`
- L14 _public enumerator_ `SkeletalMesh`

#### enum `EPVAssetReplacePolicy`  
`enum class EPVAssetReplacePolicy : uint8`  
_L18-28_
- reflection: `UENUM()`
- L21 _public enumerator_ `Append` — Create new assets with numbered suffixes
- L24 _public enumerator_ `Replace` — Replaces existing asset with new asset
- L27 _public enumerator_ `Ignore` — Ignores the new asset and keeps the existing asset

#### enum `EPVCollisionGeneration`  
`enum class EPVCollisionGeneration : uint8`  
_L31-41_
- reflection: `UENUM()`
- L34 _public enumerator_ `None` — Do not create collision for mesh
- L37 _public enumerator_ `TrunkOnly` — Creates collision for trunk only
- L40 _public enumerator_ `AllGenerations` — Creates collision for all branch generations

#### struct `FPVExportParams`  
`struct FPVExportParams`  
_L44-124_
- reflection: `USTRUCT()`
- L49 _public member_ `FDirectoryPath ContentBrowserFolder;` — `UPROPERTY(EditAnywhere, Category = "Asset", Meta = (ContentDir, DisplayName = "Content Browser Folder", Tooltip="Folder under Content/ to save the exported asset(s).\n\nPath relative to the project's Content folder. The exported mesh and any sub-assets (textures, materials) are written here. Must exist or be a writable parent directory."))`
- L52 _public member_ `FName MeshName;` — `UPROPERTY(EditAnywhere, Category = "Asset", Meta = (DisplayName = "Mesh Name", Tooltip="Filename for the exported mesh asset.\n\nBase name for the output. Combines with 'ReplacePolicy' to decide behavior on name collision."))`
- L55 _public member_ `EPVAssetReplacePolicy ReplacePolicy = EPVAssetReplacePolicy::Replace;` — `UPROPERTY(EditAnywhere, Category = "Asset", Meta = (DisplayName = "Asset Replace Policy", Tooltip="What to do if the target asset already exists: Append, Replace, or Ignore.\n\nAppend: create a numbered version ('MyTree_01', 'MyTree_02'). Replace: overwrite. Ignore: skip the export."))`
- L58 _public member_ `EPVExportMeshType ExportMeshType = EPVExportMeshType::SkeletalMesh;` — `UPROPERTY(EditAnywhere, Category = "Mesh", Meta = (DisplayName = "Export Mesh Type", Tooltip="Export as Static Mesh or Skeletal Mesh.\n\nStaticMesh: no wind animation support. SkeletalMesh: includes bones for wind sway."))`
- L61 _public member_ `bool bCreateNaniteFoliage = true;` — `UPROPERTY(EditAnywhere, Category = "Mesh | Nanite", Meta = (DisplayName = "Create Nanite Foliage", Tooltip="Add Nanite foliage support for the exported mesh."))`
- L64 _public member_ `ENaniteShapePreservation NaniteShapePreservation = ENaniteShapePreservation::Voxelize;` — `UPROPERTY(EditAnywhere, Category = "Mesh | Nanite", Meta = (DisplayName = "Nanite Shape Preservation Method", Tooltip="How Nanite preserves shape during simplification.\n\nVoxelize (default) is the standard Nanite shape-preservation algorithm. See Unreal's Nanite documentation for advanced options."))`
- L67 _public member_ `bool bCollision = false;` — `UPROPERTY(EditAnywhere, Category = "Mesh | Collision", Meta = (EditCondition = "ExportMeshType == EPVExportMeshType::StaticMesh", EditConditionHides, Tooltip="Generate collision geometry for the static mesh.\n\nWhen on, builds a simplified collision shape. Useful for plants the player can collide with. Higher build time."))`
- L70 _public member_ `EPVCollisionGeneration CollisionGeneration = EPVCollisionGeneration::None;` — `UPROPERTY(EditAnywhere, Category = "Mesh | Collision", Meta = (EditCondition = "ExportMeshType == EPVExportMeshType::SkeletalMesh", EditConditionHides, Tooltip="Generate a physics asset and pick which branches get collision.\n\nNone: no physics asset. TrunkOnly: collide only with the trunk. AllGenerations: collide with every branch (highest cost)."))`
- L73 _public member_ `TObjectPtr<UPVWindSettings> WindSettings;` — `UPROPERTY(EditAnywhere, Category = "Mesh | Dynamic Wind", Meta = (EditCondition = "ExportMeshType == EPVExportMeshType::SkeletalMesh", EditConditionHides, Tooltip="Wind simulation preset to assign to the skeletal mesh.\n\nContains the Dynamic Wind plugin's simulation group data. Default presets are available for saplings and trees. Required for wind sway."))`
- L75 _public function_ `void Initialize(const FString& InAssetPath, const FString& InName, const FString& InDefaultWindSettingsPath)`
- L84 _public function_ `FString GetOutputObjectPath() const`
- L91 _public function_ `FString GetOutputMeshPackagePath() const`
- L96 _public function_ `FString GetOutputSkeletonName() const`
- L101 _public function_ `FString GetOutputSkeletonPackagePath() const`
- L106 _public function_ `FString GetOutputPhysicsAssetName() const`
- L111 _public function_ `FString GetOutputPhysicsAssetPackagePath() const`
- L116 _public function_ `bool IsCollisionEnable() const`
- L121 _public prototype_ `UClass* GetMeshClass() const;`
- L123 _public prototype_ `bool Validate(FString& OutError) const;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Params/PVTrunkTextureSetupParams.h` (Public)


#### enum `EPVTrunkTextureSetupMode`  
`enum class EPVTrunkTextureSetupMode : uint8`  
_L12-16_
- reflection: `UENUM()`
- L14 _public enumerator_ `TextureCreate UMETA(DisplayName="Texture Create")`
- L15 _public enumerator_ `TextureLoad UMETA(DisplayName="Texture Load")`

#### enum `EPVTextureResolution`  
`enum class EPVTextureResolution`  
_L19-27_
- reflection: `UENUM()`
- L21 _public enumerator_ `Resolution512 = 512 UMETA(DisplayName = "512 x 512")`
- L22 _public enumerator_ `Resolution1024 = 1024 UMETA(DisplayName = "1024 x 1024")`
- L23 _public enumerator_ `Resolution2048 = 2048 UMETA(DisplayName = "2048 x 2048")`
- L24 _public enumerator_ `Resolution4096 = 4096 UMETA(DisplayName = "4096 x 4096")`
- L25 _public enumerator_ `Resolution8192 = 8192 UMETA(DisplayName = "8192 x 8192")`
- L26 _public enumerator_ `Resolution16384 = 16384 UMETA(DisplayName = "16384 x 16384")`

#### struct `FPVTextureChannelParams`  
`struct FPVTextureChannelParams`  
_L30-53_
- reflection: `USTRUCT()`
- L35 _public member_ `EPVTextureChannel Channel = EPVTextureChannel::BaseColor;` — `UPROPERTY(EditAnywhere, Category=Channel, meta=(Tooltip="Channel type (BaseColor, Normal, Roughness, etc.).\n\nPicks which output channel of the bake this texture contributes to."))`
- L38 _public member_ `FString ChannelName;` — `UPROPERTY(EditAnywhere, Category=Channel, meta=(EditCondition="Channel == EPVTextureChannel::Custom", Tooltip="Custom name for the channel.\n\nRequired when 'Channel == Custom'. The string becomes the texture parameter name on the output material."))`
- L41 _public member_ `FFilePath TextureFilePath;` — `UPROPERTY(EditAnywhere, Category= Channel, meta = (AllowPrivateAccess = true, FilePathFilter = "Image Files (*.png;*.PNG;*.jpg;*.jpeg;*.exr;)|*.png;*.PNG;*.jpg;*.jpeg;*.exr;", Tooltip="Path to a source image file (PNG / JPG / EXR).\n\nExternal texture loaded from disk for this channel."))`
- L44 _public member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(VisibleAnywhere, Category=Channel, meta=(Tooltip="Loaded texture object (auto-populated).\n\nSet automatically after the source file path is loaded. Read-only display."))`
- L46 _public member_ `float WidthRatio = 1.0;`
- L48 _public prototype_ `void LoadTexture();`
- L50 _public prototype_ `void ResetTexture();`
- L52 _public prototype_ `FString GetChannelName() const;`

#### struct `FPVTextureGenerationParams`  
`struct FPVTextureGenerationParams`  
_L56-84_
- reflection: `USTRUCT()`
- L61 _public member_ `float Dilation = 0.1f;` — `UPROPERTY(EditAnywhere, Category= Generation, meta=(Tooltip="Pixel dilation around each generation's region.\n\nAdds padding around the generation's texture region to avoid seams from filtering. Higher = more padding (less risk of seams, less usable area)."))`
- L64 _public member_ `float XScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category= Generation, meta=(Tooltip="Horizontal scale of this generation's region.\n\nMultiplier on the region's width within the trim sheet."))`
- L67 _public member_ `float BaseTileX = 1.0f;` — `UPROPERTY(EditAnywhere, Category= Generation, meta=(Tooltip="Base tile count in X for this generation.\n\nNumber of times the source material tiles within this generation's region."))`
- L70 _public member_ `float BaseTileY = 1.0f;` — `UPROPERTY(EditAnywhere, Category= Generation, meta=(Tooltip="Base tile count in Y for this generation.\n\nNumber of times the source material tiles within this generation's region."))`
- L73 _public member_ `TArray<FPVTextureChannelParams> Channels;` — `UPROPERTY(EditAnywhere, Category= Generation, meta=(Tooltip="Source textures for each channel of this generation."))`
- L75 _public prototype_ `void LoadChannelTexture(int ChannelIndex);`
- L77 _public prototype_ `TArray<FString> GetChannelNames();`
- L79 _public prototype_ `const FPVTextureChannelParams* GetChannel(const FString& Name);`
- L81 _public prototype_ `float GetWidthRatio() const;`
- L83 _public prototype_ `bool IsWidthRatioSame() const;`

#### struct `FPVTrunkTextureSetupParams`  
`struct FPVTrunkTextureSetupParams`  
_L87-120_
- reflection: `USTRUCT()`
- L92 _public member_ `EPVTrunkTextureSetupMode Mode = EPVTrunkTextureSetupMode::TextureCreate;` — `UPROPERTY(EditAnywhere, Category=TrunkTextureSetup, meta=(Tooltip="Bake new textures or load previously-baked ones.\n\nTexture Create: Setup textures and bake to disk. Texture Load: Uses textures already in the bake folder. Use Create when iterating on inputs; switch to Load when iterating on downstream nodes."))`
- L95 _public member_ `FString AssetNamePrefix;` — `UPROPERTY(EditAnywhere, Category= "Baked Textures", meta=(Tooltip="Prefix added to baked texture asset names.\n\nAll baked textures get this prefix in their filename. Useful for distinguishing multiple Texture Setup nodes' outputs in the same folder."))`
- L98 _public member_ `FDirectoryPath BakeTextureFolder;` — `UPROPERTY(EditAnywhere, Category= "Baked Textures", meta=(ContentDir, RelativeToGameDir, Tooltip="Folder where baked textures are written / loaded.\n\nPath under Content/. In Texture Create mode, textures are written here. In Texture Load mode, they're read from here. Must exist before baking."))`
- L101 _public member_ `bool bVirtualTexture = false;` — `UPROPERTY(EditAnywhere, Category= "Baked Textures", meta=(EditCondition="Mode == EPVTrunkTextureSetupMode::TextureCreate", EditConditionHides, Tooltip="Enable virtual texture streaming for the baked textures.\n\nGenerates the textures as virtual textures (VTs)."))`
- L104 _public member_ `TObjectPtr<UMaterialInstance> Material;` — `UPROPERTY(EditAnywhere, Category= NoCategory, meta=(Tooltip="Material instance to populate with the baked textures.\n\nAfter baking, the texture parameters on this material instance are set to the baked outputs. The Mesh Builder can then use this material."))`
- L107 _public member_ `EPVTextureChannel PreviewChannel = EPVTextureChannel::BaseColor;` — `UPROPERTY(EditAnywhere, Category=TrunkTextureSetup, meta=(EditCondition="Mode == EPVTrunkTextureSetupMode::TextureCreate", EditConditionHides, Tooltip="Which texture channel to preview in the editor.\n\nBaseColor / AO / Normal / Displacement / Bump / Cavity / Gloss / Roughness / Specular / Custom."))`
- L110 _public member_ `EPVTextureResolution Resolution = EPVTextureResolution::Resolution1024;` — `UPROPERTY(EditAnywhere, Category=TrunkTextureSetup, meta=(EditCondition="Mode == EPVTrunkTextureSetupMode::TextureCreate", EditConditionHides, Tooltip="Resolution of the baked textures.\n\n512 to 16384. Higher = more detail, bigger memory cost."))`
- L113 _public member_ `TArray<FPVTextureGenerationParams> Generations;` — `UPROPERTY(EditAnywhere, Category=TrunkTextureSetup, meta=(EditCondition="Mode == EPVTrunkTextureSetupMode::TextureCreate", EditConditionHides, Tooltip="Per-generation trim sheet packing configuration.\n\nEach entry defines how one branch generation's textures are arranged within the trim sheet. Add one entry per generation that should have its own texture region."))`
- L115 _public prototype_ `void LoadGenerationChannelTexture(int GenerationIndex, int ChannelIndex);`
- L117 _public prototype_ `float GetWidthRatio(FPVTextureGenerationParams Generation) const;`
- L119 _public prototype_ `bool IsWidthRatioSame(FPVTextureGenerationParams Generation) const;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/ProceduralVegetation.h` (Public)


#### class `UProceduralVegetationGraph`  
`class UProceduralVegetationGraph : public UPCGGraph`  
_L9-45_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPCGGraph`
- L14 _public function_ `UProceduralVegetationGraph(const FObjectInitializer& ObjectInitializer) : UPCGGraph(ObjectInitializer)`
- L30 _public prototype_ `virtual void PostLoad() override;`
- L33 _public function_ `virtual bool ShouldDisplayDebuggingProperties() const override`
- L34 _public function_ `virtual bool CanToggleStandaloneGraph() const override`
- L35 _public function_ `virtual bool IsExportToLibraryEnabled() const override`
- L36 _public function_ `virtual bool ShowGraphCustomization() const override`
- L37 _public function_ `virtual bool IsTemplatePropertyEnabled() const override`
- L39 _public function_ `virtual TSubclassOf<UPCGGraph> GetEmbeddedSubgraphClass() const override`
- L42 _public function_ `virtual bool SupportsEmbeddedSubgraphs() const override`
- L43 _public function_ `UProceduralVegetationGraph* GetEmbeddedParentGraph() const`
- L44 _public function_ `bool IsEmbeddedSubgraph() const`

#### class `UProceduralVegetationInterface`  
`class UProceduralVegetationInterface : public UObject`  
_L48-55_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`

#### class `UProceduralVegetation`  
`class UProceduralVegetation : public UProceduralVegetationInterface`  
_L61-74_
- reflection: `UCLASS()`
- inherits: `UProceduralVegetationInterface`
- desc: Asset type for procedural plant generation
- L66 _private member_ `TObjectPtr<UProceduralVegetationGraph> Graph;` — `UPROPERTY()`
- L69 _public function_ `virtual UPCGGraphInterface* GetGraph() override`
- L70 _public function_ `virtual const UPCGGraphInterface* GetGraph() const override`
- L72 _public function_ `void SetGraph(UProceduralVegetationGraph* InGraph)`
- L73 _public prototype_ `void CreateGraph(const UProceduralVegetationGraph* InGraph = nullptr);`

#### class `UProceduralVegetationGraphInstance`  
`class UProceduralVegetationGraphInstance : public UPCGGraphInstance`  
_L77-89_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPCGGraphInstance`
- L82 _public member_ `TObjectPtr<UProceduralVegetationInterface> ProceduralVegetation;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Instance)`
- L85 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L86 _public function_ `virtual bool ShouldShowGraphProperty() const override`
- L87 _public function_ `virtual bool CanSaveAsAsset() const override`

#### class `UProceduralVegetationInstance`  
`class UProceduralVegetationInstance : public UProceduralVegetationInterface`  
_L92-110_
- reflection: `UCLASS()`
- inherits: `UProceduralVegetationInterface`
- L97 _public prototype_ `UProceduralVegetationInstance(const FObjectInitializer& InObjectInitializer);`
- L99 _public function_ `virtual UPCGGraphInterface* GetGraph() override`
- L100 _public function_ `virtual const UPCGGraphInterface* GetGraph() const override`
- L102 _public function_ `UProceduralVegetationInterface* GetProceduralVegetationAsset() const`
- L103 _public function_ `void SetProceduralVegetationAsset(UProceduralVegetationInterface* InAsset)`
- L106 _public member_ `TObjectPtr<UProceduralVegetationGraphInstance> GraphInstance;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Properties, Instanced, meta = (NoResetToDefault))`
- L109 _public prototype_ `virtual void PostLoad() override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/ProceduralVegetationLink.h` (Public)


#### class `UProceduralVegetationLink`  
`class UProceduralVegetationLink : public UAssetUserData`  
_L10-17_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetUserData`
- L16 _public member_ `TObjectPtr<UProceduralVegetation> Source;` — `UPROPERTY(VisibleAnywhere, Category = Settings)`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/ProceduralVegetationModule.h` (Public)


#### class `FProceduralVegetationModule`  
`class FProceduralVegetationModule : public IModuleInterface`  
_L9-16_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L15 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogProceduralVegetation, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogProceduralVegetation, Log, All);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/ProceduralVegetationPreset.h` (Public)


#### struct `FPVPresetVariationInfo`  
`struct FPVPresetVariationInfo`  
_L12-27_
- reflection: `USTRUCT()`
- L17 _public member_ `FName Name;` — `UPROPERTY(VisibleAnywhere, Category = "Variations")`
- L20 _public member_ `TArray<TSoftObjectPtr<UObject>> FoliageMeshes;` — `UPROPERTY(VisibleAnywhere, Category = "Variations")`
- L23 _public member_ `TArray<TSoftObjectPtr<UObject>> Materials;` — `UPROPERTY(VisibleAnywhere, Category = "Variations")`
- L26 _public member_ `TArray<FString> PlantProfiles;` — `UPROPERTY(VisibleAnywhere, Category = "Variations")`

#### class `UProceduralVegetationPreset`  
`class UProceduralVegetationPreset : public UDataAsset`  
_L30-61_
- reflection: `UCLASS(BlueprintType, meta=(DisplayName="[DEPRECATED] Procedural Vegetation Preset"))`
- inherits: `UDataAsset`
- L36 _public member_ `FDirectoryPath JsonDirectoryPath;` — `UPROPERTY(VisibleAnywhere, Category="Preset Data")`
- L39 _public member_ `bool bOverrideFolderPaths = false;` — `UPROPERTY(VisibleAnywhere, Category="Preset Data")`
- L42 _public member_ `FDirectoryPath FoliageFolder;` — `UPROPERTY(VisibleAnywhere, Category="Preset Data")`
- L45 _public member_ `FDirectoryPath MaterialsFolder;` — `UPROPERTY(VisibleAnywhere, Category="Preset Data")`
- L48 _public member_ `FString TrunkMaterialName;` — `UPROPERTY(VisibleAnywhere, Category="Preset Data")`
- L51 _public member_ `bool bCreateProfileDataAsset = false;` — `UPROPERTY(VisibleAnywhere, Category="Preset Data")`
- L54 _public member_ `FString PlantProfileName;` — `UPROPERTY(VisibleAnywhere, Category="Preset Data")`
- L57 _public member_ `TMap<FString, FManagedArrayCollection> Variants;` — `UPROPERTY()`
- L60 _public member_ `TArray<FPVPresetVariationInfo> PresetVariations;` — `UPROPERTY(VisibleAnywhere, Category = "Preset Data")`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetation/Public/Utils/PVFloatRamp.h` (Public)


#### struct `FPVFloatRamp`  
`struct FPVFloatRamp`  
_L10-34_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public member_ `FRichCurve EditorCurveData;` — `UPROPERTY()`
- L17 _public function_ `FRichCurve* GetRichCurve()`
- L21 _public function_ `const FRichCurve* GetRichCurveConst() const`
- L26 _public function_ `void InitializeLinearCurve(const FVector2f& Range = FVector2f(0.f, 1.f), const FVector2f& Value = FVector2f(0.f, 1.f))`
