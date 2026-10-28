# Plugins / DMXFixtures

- module root: `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures`
- headers: 9; symbols: 214
- symbol kinds: class=8, enum=1, enumerator=5, function=30, member=90, prototype=77, struct=3
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, DMXFixtureActorInterface, DMXProtocol, DMXRuntime, Engine, ProceduralMeshComponent, RHI, RenderCore

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixtureActor.h` (Public)


#### enum `EDMXFixtureQualityLevel`  
`enum EDMXFixtureQualityLevel : int`  
_L24-31_
- reflection: `UENUM()`
- L26 _public enumerator_ `LowQuality UMETA(DisplayName = "Low")`
- L27 _public enumerator_ `MediumQuality UMETA(DisplayName = "Medium")`
- L28 _public enumerator_ `HighQuality UMETA(DisplayName = "High")`
- L29 _public enumerator_ `UltraQuality UMETA(DisplayName = "Ultra")`
- L30 _public enumerator_ `Custom UMETA(DisplayName = "Custom")`

#### class `ADMXFixtureActor`  
`class ADMXFixtureActor : public ADMXFixtureActorBase , public IDMXMVRFixtureActorInterface`  
_L34-208_
- reflection: `UCLASS()`
- inherits: `ADMXFixtureActorBase,IDMXMVRFixtureActorInterface`
- L43 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L48 _public prototype_ `ADMXFixtureActor();`
- L51 _public prototype_ `virtual void OnMVRGetSupportedDMXAttributes_Implementation(TArray<FName>& OutAttributeNames, TArray<FName>& OutMatrixAttributeNames) const override;`
- L54 _public member_ `bool HasBeenInitialized;`
- L55 _public member_ `float LensRadius;`
- L56 _public prototype_ `void FeedFixtureData();`
- L62 _public member_ `TEnumAsByte<EDMXFixtureQualityLevel> QualityLevel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX Light Fixture", meta = (DisplayPriority = 0))` — Visual quality level that changes the number of samples in the volumetric beam
- L66 _public member_ `float BeamQuality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX Light Fixture", meta = (EditCondition = "QualityLevel == EDMXFixtureQualityLevel::Custom", EditConditionHides))` — Visual quality for the light beam - small value is visually better but cost more on GPU
- L70 _public member_ `float ZoomQuality;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX Light Fixture", meta = (EditCondition = "QualityLevel == EDMXFixtureQualityLevel::Custom", EditConditionHides))` — Visual quality for the light beam when zoom is wide - small value is visually better but cost more on GPU
- L74 _public member_ `TObjectPtr<USceneComponent> Base;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DMX Light Fixture")` — HIERARCHY---------------------------------
- L77 _public member_ `TObjectPtr<USceneComponent> Yoke;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DMX Light Fixture")`
- L80 _public member_ `TObjectPtr<USceneComponent> Head;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DMX Light Fixture")`
- L85 _public prototype_ `void InitializeFixture(UStaticMeshComponent* StaticMeshLens, UStaticMeshComponent* StaticMeshBeam);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")`
- L88 _public prototype_ `virtual void PushNormalizedValuesPerAttribute(const FDMXNormalizedAttributeValueMap& ValuePerAttributeMap) override;` — Pushes DMX Values to the Fixture. Expects normalized values in the range of 0.0f - 1.0f
- L97 _public prototype_ `void UpdateSpotLightIntensity();` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Updates the spotlight intensity. Considers light intensity max, the spotlight intensity scale and the cone angle to compute the intensity. Should be used instead of setting the intensity of the spotlight directly.
- L101 _public prototype_ `void SetLightIntensityMax(float NewLightIntensityMax);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Sets the a new max light intensity
- L105 _public prototype_ `void SetLightDistanceMax(float NewLightDistanceMax);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Sets a new max light distance
- L109 _public prototype_ `void SetLightColorTemp(float NewLightColorTemp);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Sets a new light color temperature
- L113 _public prototype_ `void SetSpotlightIntensityScale(float NewSpotlightIntensityScale);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Sets a new spotlight intensity scale
- L117 _public prototype_ `void SetPointlightIntensityScale(float NewPointlightIntensityScale);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Sets a new pointlight intensity scale
- L121 _public prototype_ `void SetLightCastShadow(bool bLightShouldCastShadow);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Sets if the light should cast shadows
- L127 _public member_ `float LightIntensityMax;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetLightIntensityMax, Category = "DMX Light Fixture")` — Light intensity at 1 steradian (32.77deg half angle)
- L131 _public member_ `float LightDistanceMax;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetLightDistanceMax, Category = "DMX Light Fixture")` — Sets Attenuation Radius on the spotlight and pointlight
- L135 _public member_ `float LightColorTemp;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetLightColorTemp, Category = "DMX Light Fixture")` — Light color temperature on the spotlight and pointlight
- L139 _public member_ `float SpotlightIntensityScale;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetSpotlightIntensityScale, Category = "DMX Light Fixture")` — Scales spotlight intensity
- L143 _public member_ `float PointlightIntensityScale;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetPointlightIntensityScale, Category = "DMX Light Fixture")` — Scales pointlight intensity
- L147 _public member_ `bool LightCastShadow;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetLightCastShadow, Category = "DMX Light Fixture")` — Enable/disable cast shadow on the spotlight and pointlight
- L151 _public member_ `bool UseDynamicOcclusion;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX Light Fixture")` — Simple solution useful for walls, 1 linetrace from the center
- L155 _public member_ `bool DisableLights;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DMX Light Fixture")` — Disable lights rendering in the fixture to save on GPU
- L160 _public member_ `TArray<TObjectPtr<UStaticMeshComponent>> StaticMeshComponents;` — `UPROPERTY(BlueprintReadOnly, Category = "DMX Light Fixture")`
- L163 _public member_ `TObjectPtr<class USpotLightComponent> SpotLight;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DMX Light Fixture")`
- L166 _public member_ `TObjectPtr<class UPointLightComponent> PointLight;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DMX Light Fixture")`
- L169 _public member_ `TObjectPtr<class UArrowComponent> OcclusionDirection;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DMX Light Fixture")`
- L175 _public member_ `TObjectPtr<UMaterialInstance> LensMaterialInstance;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "DMX Light Fixture")`
- L178 _public member_ `TObjectPtr<UMaterialInstance> BeamMaterialInstance;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "DMX Light Fixture")`
- L181 _public member_ `TObjectPtr<UMaterialInstance> SpotLightMaterialInstance;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "DMX Light Fixture")`
- L184 _public member_ `TObjectPtr<UMaterialInstance> PointLightMaterialInstance;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category = "DMX Light Fixture")`
- L187 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialLens;` — `UPROPERTY(BlueprintReadOnly, Category = "DMX Light Fixture")`
- L190 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialBeam;` — `UPROPERTY(BlueprintReadOnly, Category = "DMX Light Fixture")`
- L193 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialSpotLight;` — `UPROPERTY(BlueprintReadOnly, Category = "DMX Light Fixture")`
- L196 _public member_ `TObjectPtr<UMaterialInstanceDynamic> DynamicMaterialPointLight;` — `UPROPERTY(BlueprintReadOnly, Category = "DMX Light Fixture")`
- L203 _public member_ `float MinQuality_DEPRECATED;` — `UE_DEPRECATED(5.1, "Use BeamQuality instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use BeamQuality instead."))`
- L207 _public member_ `float MaxQuality_DEPRECATED;` — `UE_DEPRECATED(5.1, "Use ZoomQuality instead")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "Use ZoomQuality instead."))`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixtureActorBase.h` (Public)


#### class `ADMXFixtureActorBase`  
`class ADMXFixtureActorBase : public AActor`  
_L14-31_
- reflection: `UCLASS()`
- inherits: `AActor`
- L20 _public prototype_ `ADMXFixtureActorBase();`
- L24 _public prototype_ `virtual void PushNormalizedValuesPerAttribute(const FDMXNormalizedAttributeValueMap& ValuePerAttributeMap);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")` — Pushes DMX Values to the Fixture. Expects normalized values in the range of 0.0f - 1.0f
- L27 _public prototype_ `void InterpolateDMXComponents(float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, Category = "DMX Fixture")`
- L30 _public member_ `TObjectPtr<UDMXComponent> DMX;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DMX Light Fixture")`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixtureActorMatrix.h` (Public)


#### class `ADMXFixtureActorMatrix`  
`class ADMXFixtureActorMatrix : public ADMXFixtureActor`  
_L15-90_
- reflection: `UCLASS()`
- inherits: `ADMXFixtureActor`
- L20 _public prototype_ `ADMXFixtureActorMatrix();`
- L25 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L30 _public prototype_ `virtual void OnMVRGetSupportedDMXAttributes_Implementation(TArray<FName>& OutAttributeNames, TArray<FName>& OutMatrixAttributeNames) const override;`
- L33 _public member_ `TArray<uint8> MatrixData;`
- L34 _public member_ `int MatrixDataSize;`
- L35 _public member_ `int NbrTextureRows;`
- L36 _public member_ `int QuadIndexCount;`
- L37 _public member_ `int XCells;`
- L38 _public member_ `int YCells;`
- L40 _public member_ `UTexture2D* MatrixDataTexture;`
- L41 _public member_ `FUpdateTextureRegion2D TextureRegion;`
- L44 _public member_ `TObjectPtr<UProceduralMeshComponent> MatrixHead;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DMX Matrix Fixture")`
- L47 _public member_ `float MatrixWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Matrix Fixture")`
- L50 _public member_ `float MatrixHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Matrix Fixture")`
- L53 _public member_ `float MatrixDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Matrix Fixture")`
- L57 _public member_ `bool bIgnorePixelMappingDistributionOfFixturePatch = false;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category = "DMX Matrix Fixture")` — If set to true, ignores the distribution set in the patch (hence the distribution becomes visible when not left to right, top to bottom)
- L59 _public prototype_ `void GenerateMatrixMesh();`
- L60 _public prototype_ `void GenerateMatrixCells();`
- L61 _public prototype_ `void GenerateMatrixBeam();`
- L62 _public prototype_ `void GenerateMatrixChassis(FVector TL, FVector BL, FVector BR, FVector TR);`
- L63 _public prototype_ `void AddQuad(FVector TL, FVector BL, FVector BR, FVector TR, FProcMeshTangent Tangent);`
- L64 _public prototype_ `void UpdateDynamicTexture();`
- L65 _public prototype_ `FLinearColor GetMatrixAverageColor();`
- L66 _public prototype_ `void UpdateMatrixData(int32 RowIndex, int32 CellIndex, int32 ChannelIndex, float Value);`
- L69 _public prototype_ `void PushFixtureMatrixCellData(TArray<FDMXCell> MatrixPixelData);` — `UFUNCTION(BlueprintCallable, Category = "DMX Matrix Fixture")`
- L72 _public prototype_ `void InitializeMatrixFixture();` — `UFUNCTION(BlueprintCallable, Category = "DMX Matrix Fixture")`
- L75 _public prototype_ `void GenerateEditorMatrixMesh();` — `UFUNCTION(BlueprintCallable, Category = "DMX Matrix Fixture")`
- L79 _protected prototype_ `void SetDefaultMatrixFixtureState();` — Sets the matrix fixture in a defaulted state using default values of its Fixture Components
- L82 _private member_ `TArray<FVector> Vertices;`
- L83 _private member_ `TArray<int32> Triangles;`
- L84 _private member_ `TArray<FVector> Normals;`
- L85 _private member_ `TArray<FProcMeshTangent> Tangents;`
- L86 _private member_ `TArray<FVector2D> UV0;`
- L87 _private member_ `TArray<FVector2D> UV1;`
- L88 _private member_ `TArray<FVector2D> UV2;`
- L89 _private member_ `TArray<FColor> Colors;`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixtureComponent.h` (Public)


#### struct `FDMXChannelData`  
`struct FDMXChannelData`  
_L19-34_
- reflection: `USTRUCT(BlueprintType)`
- L24 _public member_ `FDMXAttributeName Name;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Channel")`
- L27 _public member_ `float MinValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Channel")`
- L30 _public member_ `float MaxValue = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Channel")`
- L33 _public member_ `float DefaultValue = 0.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Channel")`

#### class `UDMXFixtureComponent`  
`class UDMXFixtureComponent : public UActorComponent`  
_L38-121_
- reflection: `UCLASS(Abstract, Meta=(IsBlueprintBase=false))`
- inherits: `UActorComponent`
- L44 _protected prototype_ `void InitCells(int NumCells);` — Initializes the cells for the fixture
- L47 _public prototype_ `UDMXFixtureComponent();`
- L51 _public prototype_ `virtual void Initialize();` — `UFUNCTION()` — Initializes the component
- L54 _public prototype_ `virtual void SetCurrentCell(int Index);` — Sets the cell that is currently active
- L57 _public prototype_ `virtual void PushNormalizedValuesPerAttribute(const FDMXNormalizedAttributeValueMap& ValuePerAttribute) PURE_VIRTUAL(UDMXFixtureComponent::PushNormalizedValuesPerAttribute, return; );` — Pushes DMX Values to the Fixture Component. Expects normalized values in the range of 0.0f to 1.0f
- L61 _public member_ `bool bIsEnabled = true;` — `UPROPERTY(EditAnywhere, Category = "DMX Parameters", meta = (DisplayPriority = 0))` — If used within a DMX Fixture Actor or Fixture Matrix Actor, the component only receives data when set to true. Else needs be implemented in blueprints.
- L65 _public member_ `float SkipThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "DMX Parameters")` — Value changes smaller than this threshold are ignored
- L69 _public member_ `bool bUseInterpolation = false;` — `UPROPERTY(EditAnywhere, Category = "DMX Parameters")` — If used within a DMX Fixture Actor or Fixture Matrix Actor, the plugin interpolates towards the last set value.
- L73 _public member_ `float InterpolationScale = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "DMX Parameters")` — The scale of the interpolation speed. Faster when > 1, slower when < 1
- L77 _public member_ `bool bUsingMatrixData = false;` — `UPROPERTY()` — True if the component is attached to a matrix fixture
- L81 _public prototype_ `class ADMXFixtureActor* GetParentFixtureActor();` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — If attached to a DMX Fixture Actor, returns the parent fixture actor.
- L88 _public prototype_ `TArray<FLinearColor> GetTextureCenterColors(UTexture2D* TextureAtlas, int numTextures, bool bUpdateTextureResource = true);` — `UFUNCTION(BlueprintCallable, Category = "DMX")` — Reads pixel color in the middle of each "Texture" and output linear colors. Note, this function locks the GPU to read the color and is slow to call, even if Update TextureResource is not enabled.
- L92 _public prototype_ `void InterpolateComponent(float DeltaSeconds);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "DMX")` — Called each tick when interpolation is enabled, to calculate the next value
- L96 _public prototype_ `void InitializeComponent();` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "DMX")` — Called to initialize the component in blueprints
- L100 _public prototype_ `void GetSupportedDMXAttributes(TArray<FName>& OutAttributeNames);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DMX")` — Should be implemented to let other objects (e.g. datasmith) know which attributes the component can handle
- L101 _public function_ `virtual void GetSupportedDMXAttributes_Implementation(TArray<FName>& OutAttributeNames)`
- L104 _public prototype_ `void ApplySpeedScale();` — Applies the speed scale property
- L109 _public member_ `TArray<FCell> Cells;` — A cell represent one "lens" in a light fixture i.e.: Single light fixture contains one cell but Matrix fixtures contain multiple cells Also, a cell can have multiple channels (single, double)
- L112 _public member_ `FCell* CurrentCell;` — The currently handled cell
- L117 _public function_ `virtual void SetBitResolution(TMap<FDMXAttributeName, EDMXFixtureSignalFormat> AttributeNameToSignalFormatMap)` — `UE_DEPRECATED(4.27, "Removed, was unused 4.26 and has no clear use.")`
- L120 _public function_ `virtual void SetRangeValue()` — `UE_DEPRECATED(4.27, "Only call initialize instead.")`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixtureComponentColor.h` (Public)


#### class `UDMXFixtureComponentColor`  
`class UDMXFixtureComponentColor : public UDMXFixtureComponent`  
_L14-66_
- reflection: `UCLASS(ClassGroup = DMXFixtureComponent, meta = (IsBlueprintBase = true))`
- inherits: `UDMXFixtureComponent`
- desc: Specific class to handle color mixing using 4 channels (rgb, cmy, rgbw). Note, the color values are never interpolated.
- L19 _public prototype_ `UDMXFixtureComponentColor();`
- L22 _public prototype_ `virtual void PushNormalizedValuesPerAttribute(const FDMXNormalizedAttributeValueMap& ValuePerAttribute) override;`
- L23 _public prototype_ `virtual void GetSupportedDMXAttributes_Implementation(TArray<FName>& OutAttributeNames) override;`
- L27 _public member_ `FDMXAttributeName DMXChannel1;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX Channel")`
- L30 _public member_ `FDMXAttributeName DMXChannel2;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX Channel")`
- L33 _public member_ `FDMXAttributeName DMXChannel3;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX Channel")`
- L36 _public member_ `FDMXAttributeName DMXChannel4;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DMX Channel")`
- L39 _public prototype_ `virtual void Initialize() override;` — Initializes the interpolation range of the channels
- L42 _public prototype_ `virtual void SetCurrentCell(int Index) override;` — Sets the current cell
- L45 _public prototype_ `bool IsColorValid(const FLinearColor& NewColor) const;` — True if the color is valid for the component
- L48 _public prototype_ `void SetTargetColor(const FLinearColor& NewColor);` — Sets the target color for the current cell
- L52 _public prototype_ `void SetColorNoInterp(const FLinearColor& NewColor);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "DMX")` — Sets the color of the component. Note DMX Fixture Component Color does not support interpolation
- L55 _public member_ `TArray<FLinearColor> TargetColorArray;` — The target color, when interpolating. Otherwise just the final color
- L58 _public member_ `FLinearColor* CurrentTargetColorRef;` — Pointer to the current target color, corresponding to the current cell
- L65 _public function_ `void SetComponent(FLinearColor NewColor)` — `UE_DEPRECATED(4.27, "Replaced with SetColorNoInterp")`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixtureComponentDouble.h` (Public)


#### class `UDMXFixtureComponentDouble`  
`class UDMXFixtureComponentDouble : public UDMXFixtureComponent`  
_L11-95_
- reflection: `UCLASS(ClassGroup = FixtureComponent, meta=(IsBlueprintBase = true))`
- inherits: `UDMXFixtureComponent`
- desc: Component that uses 2 DMX channels
- L16 _public prototype_ `UDMXFixtureComponentDouble();`
- L19 _public prototype_ `virtual void PushNormalizedValuesPerAttribute(const FDMXNormalizedAttributeValueMap& ValuePerAttribute) override;`
- L20 _public prototype_ `virtual void GetSupportedDMXAttributes_Implementation(TArray<FName>& OutAttributeNames) override;`
- L25 _public member_ `FDMXChannelData DMXChannel1;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Channels")` — The first dmx attribute the component handles
- L29 _public member_ `FDMXChannelData DMXChannel2;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Channels")` — The second dmx attribute the component handles
- L32 _public prototype_ `virtual void Initialize() override;` — Initializes the interpolation range of the channels
- L36 _public prototype_ `float GetDMXInterpolatedStep(int32 ChannelIndex) const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Gets the interpolation delta value (step) for this frame
- L40 _public prototype_ `float GetDMXInterpolatedValue(int32 ChannelIndex) const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Gets the current interpolated value
- L44 _public prototype_ `float GetDMXTargetValue(int32 ChannelIndex) const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Gets the target value towards which the component interpolates
- L48 _public prototype_ `bool IsDMXInterpolationDone(int32 ChannelIndex) const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — True if the target value is reached and no interpolation is required
- L51 _public prototype_ `float NormalizedToAbsoluteValue(int32 ChannelIndex, float Alpha) const;` — Maps the normalized value to the compoenent's value range
- L54 _public prototype_ `bool IsTargetValid(int32 ChannelIndex, float Target);` — Returns true, if the target value is valid
- L57 _public prototype_ `void SetTargetValue(int32 ChannelIndex, float Value);` — Sets the target value for specified channel index. Interpolates to the value if bUseInterpolation is true.
- L61 _public prototype_ `void SetChannel1ValueNoInterp(float Channel1Value);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "DMX")` — Sets first value of the second channel. When interpolation is enabled this function should be called until the value is reached, else just once
- L65 _public prototype_ `void SetChannel2ValueNoInterp(float Channel2Value);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "DMX")` — Sets second value of the second channel. When interpolation is enabled this function should be called until the value is reached, else just once
- L73 _public function_ `void Push(int32 ChannelIndex, float Target)` — `UE_DEPRECATED(4.27, "Replaced with SetTargetValue (handling both Push and SetTarget).")`
- L76 _public function_ `void SetTarget(int32 ChannelIndex, float Target)` — `UE_DEPRECATED(4.27, "Replaced with SetTargetValue (handling both Push and SetTarget).")`
- L79 _public function_ `float DMXInterpolatedStep(int32 ChannelIndex)` — `UE_DEPRECATED(4.27, "Replaced with GetDMXInterpolatedStep")`
- L82 _public function_ `float DMXInterpolatedValue(int32 ChannelIndex)` — `UE_DEPRECATED(4.27, "Replaced with GetDMXInterpolatedValue")`
- L85 _public function_ `float DMXTargetValue(int32 ChannelIndex)` — `UE_DEPRECATED(4.27, "Replaced with GetDMXTargetValue")`
- L88 _public function_ `float RemapValue(int32 ChannelIndex, float Alpha)` — `UE_DEPRECATED(4.27, "Replaced with NormalizedToAbsoluteValue")`
- L91 _public function_ `void SetComponentChannel1(float NewValue)` — `UE_DEPRECATED(4.27, "Replaced with SetChannel1ValueNoInterp")`
- L94 _public function_ `void SetComponentChannel2(float NewValue)` — `UE_DEPRECATED(4.27, "Replaced with SetChannel1ValueNoInterp")`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixtureComponentSingle.h` (Public)


#### class `UDMXFixtureComponentSingle`  
`class UDMXFixtureComponentSingle : public UDMXFixtureComponent`  
_L11-83_
- reflection: `UCLASS(ClassGroup = FixtureComponent, meta=(IsBlueprintBase = true))`
- inherits: `UDMXFixtureComponent`
- desc: Component that uses 1 DMX channel
- L16 _public prototype_ `UDMXFixtureComponentSingle();`
- L19 _public prototype_ `virtual void PushNormalizedValuesPerAttribute(const FDMXNormalizedAttributeValueMap& ValuePerAttribute) override;`
- L20 _public prototype_ `virtual void GetSupportedDMXAttributes_Implementation(TArray<FName>& OutAttributeNames) override;`
- L24 _public member_ `FDMXChannelData DMXChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DMX Channels")`
- L27 _public prototype_ `virtual void Initialize() override;` — Initializes the interpolation range of the channels
- L31 _public prototype_ `float GetDMXInterpolatedStep() const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Gets the interpolation delta value (step) for this frame
- L35 _public prototype_ `float GetDMXInterpolatedValue() const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Gets the current interpolated value
- L39 _public prototype_ `float GetDMXTargetValue() const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — Gets the target value towards which the component interpolates
- L43 _public prototype_ `bool IsDMXInterpolationDone() const;` — `UFUNCTION(BlueprintPure, Category = "DMX")` — True if the target value is reached and no interpolation is required
- L46 _public prototype_ `float NormalizedToAbsoluteValue(float Alpha) const;` — Maps the normalized value to the compoenent's value range
- L49 _public prototype_ `bool IsTargetValid(float Target);` — Retuns true if the target differs from the previous target, and when interpolating, from the current value
- L52 _public prototype_ `void SetTargetValue(float AbsoluteValue);` — Sets the target value. Interpolates to the value if bUseInterpolation is true. Expects the value to be in value range of the component
- L56 _public prototype_ `void SetValueNoInterp(float NewValue);` — `UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "DMX Component")` — Called to set the value. When interpolation is enabled this function is called by the plugin until the target value is reached, else just once.
- L64 _public function_ `void Push(float Target)` — `UE_DEPRECATED(4.27, "Replaced with SetTargetValue (handling both Push and SetTarget).")`
- L67 _public function_ `void SetTarget(float Target)` — `UE_DEPRECATED(4.27, "Replaced with SetTargetValue (handling both Push and SetTarget).")`
- L70 _public function_ `float DMXInterpolatedStep()` — `UE_DEPRECATED(4.27, "Replaced with GetDMXInterpolatedStep")`
- L73 _public function_ `float DMXInterpolatedValue()` — `UE_DEPRECATED(4.27, "Replaced with GetDMXInterpolatedValue")`
- L76 _public function_ `float DMXTargetValue()` — `UE_DEPRECATED(4.27, "Replaced with GetDMXTargetValue")`
- L79 _public function_ `float RemapValue(float Alpha)` — `UE_DEPRECATED(4.27, "Replaced with NormalizedToAbsoluteValue")`
- L82 _public function_ `void SetComponent(float NewValue)` — `UE_DEPRECATED(4.27, "Replaced with SetValueNoInterp")`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXFixturesModule.h` (Public)


#### class `FDMXFixturesModule`  
`class FDMXFixturesModule : public IModuleInterface`  
_L10-26_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L17 _public function_ `static FDMXFixturesModule& Get()`
- L22 _public function_ `static bool IsAvailable()`

### `Plugins/VirtualProduction/DMX/DMXFixtures/Source/DMXFixtures/Public/DMXInterpolation.h` (Public)


#### struct `FInterpolationData`  
`struct FInterpolationData`  
_L8-166_
- desc: Interpolation that provides a damping effect and support direction changes
- L10 _public member_ `bool IsUpdating;`
- L11 _public member_ `float InterpolationScale;`
- L13 _public member_ `float CurrentValue;`
- L14 _public member_ `float TargetValue;`
- L15 _public member_ `float ToTravel;`
- L16 _public member_ `float RangeValue;`
- L17 _public member_ `float Direction;`
- L18 _public member_ `float TotalTravel;`
- L19 _public member_ `float PreviousT;`
- L20 _public member_ `float PreviousStep;`
- L22 _public member_ `float CurrentSpeed;`
- L23 _public member_ `float AccelerationThreshold;`
- L24 _public member_ `float SpeedIncMin;`
- L25 _public member_ `float SpeedIncMid;`
- L26 _public member_ `float SpeedIncMax;`
- L27 _public member_ `float SpeedMinimum;`
- L29 _public member_ `bool bFirstValueWasSet;`
- L31 _public function_ `FInterpolationData()`
- L53 _public function_ `bool IsTargetValid(float Value, float SkipThreshold) const`
- L58 _public function_ `void SetValueNoInterp(float NewValue)`
- L64 _public function_ `bool IsInterpolationDone() const`
- L69 _public function_ `void EndInterpolation()`
- L81 _public function_ `void StartTravel(float NewTarget)`
- L92 _public function_ `void UpdateTravel(float NewTarget)`
- L120 _public function_ `void Travel(float DeltaSeconds)` — TODO: instead of using the derivative of the SmoothStep, use a sine wave
- L154 _public function_ `void Push(float NewTarget)`

#### struct `FCell`  
`struct FCell`  
_L168-171_
- L170 _public member_ `TArray<FInterpolationData> ChannelInterpolation;`
