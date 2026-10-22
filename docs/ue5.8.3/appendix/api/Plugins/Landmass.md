# Plugins / Landmass

- module root: `Plugins/Experimental/Landmass/Source/Runtime`
- headers: 4; symbols: 64
- symbol kinds: class=1, enum=2, enumerator=6, function=5, member=39, prototype=2, struct=9
- PrivateDependencyModuleNames: 
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Experimental/Landmass/Source/Runtime/Public/BrushEffectsList.h` (Public)


#### struct `FBrushEffectBlurring`  
`struct FBrushEffectBlurring`  
_L11-25_
- reflection: `USTRUCT(BlueprintType)`
- L15 _public function_ `FBrushEffectBlurring() : bBlurShape(true) , Radius(2)`
- L21 _public member_ `bool bBlurShape;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L24 _public member_ `int32 Radius;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`

#### struct `FBrushEffectCurlNoise`  
`struct FBrushEffectCurlNoise`  
_L29-51_
- reflection: `USTRUCT(BlueprintType)`
- L33 _public function_ `FBrushEffectCurlNoise() : Curl1Amount(0) , Curl2Amount(0) , Curl1Tiling(16.0) , Curl2Tiling(3.0)`
- L41 _public member_ `float Curl1Amount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L44 _public member_ `float Curl2Amount;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L47 _public member_ `float Curl1Tiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L50 _public member_ `float Curl2Tiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`

#### struct `FBrushEffectCurves`  
`struct FBrushEffectCurves`  
_L54-80_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public function_ `FBrushEffectCurves() : bUseCurveChannel(true) , ElevationCurveAsset(nullptr) , ChannelEdgeOffset(0.0f) , ChannelDepth(0.0f) , CurveRampWidth(512.0f)`
- L67 _public member_ `bool bUseCurveChannel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L70 _public member_ `TObjectPtr<UCurveFloat> ElevationCurveAsset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L73 _public member_ `float ChannelEdgeOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L76 _public member_ `float ChannelDepth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L79 _public member_ `float CurveRampWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`

#### struct `FBrushEffectDisplacement`  
`struct FBrushEffectDisplacement`  
_L84-114_
- reflection: `USTRUCT(BlueprintType)`
- L88 _public function_ `FBrushEffectDisplacement() : DisplacementHeight(0) , DisplacementTiling(0) , Texture(nullptr) , Midpoint(-128.0f) , Channel(0,0,0,1) , WeightmapInfluence(0.0f)`
- L98 _public member_ `float DisplacementHeight;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L101 _public member_ `float DisplacementTiling;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L104 _public member_ `TObjectPtr<UTexture2D> Texture;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L107 _public member_ `float Midpoint;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L110 _public member_ `FLinearColor Channel;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L113 _public member_ `float WeightmapInfluence;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`

#### struct `FBrushEffectSmoothBlending`  
`struct FBrushEffectSmoothBlending`  
_L118-127_
- reflection: `USTRUCT(BlueprintType)`
- L123 _public member_ `float InnerSmoothDistance = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L126 _public member_ `float OuterSmoothDistance = 0.01f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`

#### struct `FBrushEffectTerracing`  
`struct FBrushEffectTerracing`  
_L130-156_
- reflection: `USTRUCT(BlueprintType)`
- L134 _public function_ `FBrushEffectTerracing() : TerraceAlpha(0.0f) , TerraceSpacing(256.0f) , TerraceSmoothness(0.0f) , MaskLength(0.0f) , MaskStartOffset(0.0f)`
- L143 _public member_ `float TerraceAlpha;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L146 _public member_ `float TerraceSpacing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L149 _public member_ `float TerraceSmoothness;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L152 _public member_ `float MaskLength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L155 _public member_ `float MaskStartOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`

#### struct `FLandmassBrushEffectsList`  
`struct FLandmassBrushEffectsList`  
_L160-178_
- reflection: `USTRUCT(BlueprintType)`
- L165 _public member_ `FBrushEffectBlurring Blurring;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BrushEffects)`
- L168 _public member_ `FBrushEffectCurlNoise CurlNoise;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`
- L171 _public member_ `FBrushEffectDisplacement Displacement;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`
- L174 _public member_ `FBrushEffectSmoothBlending SmoothBlending;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`
- L177 _public member_ `FBrushEffectTerracing Terracing;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`

### `Plugins/Experimental/Landmass/Source/Runtime/Public/FalloffSettings.h` (Public)


#### enum `EBrushFalloffMode`  
`enum class EBrushFalloffMode : uint8`  
_L8-12_
- reflection: `UENUM(BlueprintType)`
- L10 _public enumerator_ `Angle`
- L11 _public enumerator_ `Width`

#### struct `FLandmassFalloffSettings`  
`struct FLandmassFalloffSettings`  
_L15-34_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public prototype_ `FLandmassFalloffSettings();`
- L21 _public member_ `EBrushFalloffMode FalloffMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`
- L24 _public member_ `float FalloffAngle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`
- L27 _public member_ `float FalloffWidth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`
- L30 _public member_ `float EdgeOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`
- L33 _public member_ `float ZOffset;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = FalloffSettings)`

### `Plugins/Experimental/Landmass/Source/Runtime/Public/LandmassModule.h` (Public)


#### class `ILandmassModuleInterface`  
`class ILandmassModuleInterface : public IModuleInterface`  
_L8-10_
- inherits: `IModuleInterface`

### `Plugins/Experimental/Landmass/Source/Runtime/Public/TerrainCarvingSettings.h` (Public)


#### enum `EBrushBlendType`  
`enum class EBrushBlendType : uint8`  
_L12-22_
- reflection: `UENUM(BlueprintType)`
- desc: The blend mode changes how the brush material is applied to the terrain.
- L15 _public enumerator_ `AlphaBlend` — Alpha Blend will affect the heightmap both upwards and downwards.
- L17 _public enumerator_ `Min` — Limits the brush to only lowering the terrain.
- L19 _public enumerator_ `Max` — Limits the brush to only raising the terrain.
- L21 _public enumerator_ `Additive` — Performs an additive blend, using a flat Z=0 terrain as the input. Useful when you want to preserve underlying detail or ramps.

#### struct `FLandmassTerrainCarvingSettings`  
`struct FLandmassTerrainCarvingSettings`  
_L25-45_
- reflection: `USTRUCT(BlueprintType)`
- L29 _public prototype_ `FLandmassTerrainCarvingSettings();`
- L32 _public member_ `EBrushBlendType BlendMode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=TerrainCarvingSettings)`
- L35 _public member_ `bool bInvertShape;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TerrainCarvingSettings)`
- L38 _public member_ `FLandmassFalloffSettings FalloffSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TerrainCarvingSettings)`
- L41 _public member_ `FLandmassBrushEffectsList Effects;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TerrainCarvingSettings)`
- L44 _public member_ `int32 Priority;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TerrainCarvingSettings)`
