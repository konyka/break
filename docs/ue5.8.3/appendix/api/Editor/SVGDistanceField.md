# Editor / SVGDistanceField

- module root: `Source/Editor/SVGDistanceField`
- headers: 4; symbols: 44
- symbol kinds: class=1, enum=4, enumerator=14, macro=1, member=20, prototype=2, struct=2
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Source/Editor/SVGDistanceField/Public/DistanceFieldImage.h` (Public)


#### struct `FDistanceFieldImage`  
`struct FDistanceFieldImage`  
_L9-20_
- L11 _public member_ `TArray64<uint8> RawPixelData;`
- L12 _public member_ `static constexpr ETextureSourceCompressionFormat RawPixelDataCompressionFormat = TSCF_None;`
- L13 _public member_ `EPixelFormat PixelFormat = PF_Unknown;`
- L14 _public member_ `ETextureSourceFormat Format = TSF_Invalid;`
- L15 _public member_ `TextureCompressionSettings CompressionSettings = TC_Default;`
- L16 _public member_ `int32 SizeX = 0;`
- L17 _public member_ `int32 SizeY = 0;`
- L18 _public member_ `static constexpr bool bSRGB = false;`
- L19 _public member_ `static constexpr TextureMipGenSettings MipGenSettings = TMGS_NoMipmaps;`

### `Source/Editor/SVGDistanceField/Public/SvgDistanceFieldConfiguration.h` (Public)


#### enum `ESvgDistanceFieldType`  
`enum class ESvgDistanceFieldType : uint8`  
_L11-19_
- reflection: `UENUM(BlueprintType)`
- desc: The possible types of distance fields that can be generated
- L14 _public enumerator_ `Simple` — Simple single-channel Euclidean signed distance field
- L16 _public enumerator_ `Perpendicular` — Single-channel perpendicular-distance field - distance from corners is represented so that extrusions are not rounded.
- L18 _public enumerator_ `MultiChannelAndSimple` — Multi-channel signed distance field with simple Euclidean distance field in the alpha channel

#### enum `ESvgDistanceFieldUnits`  
`enum class ESvgDistanceFieldUnits : uint8`  
_L23-31_
- reflection: `UENUM(BlueprintType)`
- desc: The units in which certain values are expressed
- L26 _public enumerator_ `SvgUnits` — The "user units" sometimes also referred to as pixels in the input SVG file
- L28 _public enumerator_ `OutputPixels` — Pixels of the output image
- L30 _public enumerator_ `ProportionalToMaxDimension` — Proportion of the larger dimension of the output image

#### enum `ESvgDistanceFieldScaleMode`  
`enum class ESvgDistanceFieldScaleMode : uint8`  
_L35-45_
- reflection: `UENUM(BlueprintType)`
- desc: The strategy of scaling the SVG coordinate system units to output pixels
- L38 _public enumerator_ `ExplicitScale` — The SVG coordinates are to be multiplied by the Scale value.
- L40 _public enumerator_ `FitCanvas` — Scale is selected so that the entire SVG canvas tightly fits the output image.
- L42 _public enumerator_ `FitPaddedCanvas` — Scale is selected so that the SVG canvas padded by the outer distance spread on each side tightly fits the output image.
- L44 _public enumerator_ `FitBoundingBox` — Scale is selected so that all areas with a signed distance above the minimum representable value tightly fit the output image.

#### enum `ESvgDistanceFieldPlacementMode`  
`enum class ESvgDistanceFieldPlacementMode : uint8`  
_L49-59_
- reflection: `UENUM(BlueprintType)`
- desc: The strategy for positioning the SVG geometry within the output image
- L52 _public enumerator_ `DoNotTranslate` — Makes sure not to shift the coordinate system at all.
- L54 _public enumerator_ `PadWithOuterSpread` — Shifts the coordinate system predictably (by outer distance spread in both dimensions) to account for the outer distance gradient around the geometry.
- L56 _public enumerator_ `CenterCanvas` — Pins the center of the SVG canvas to the center of the output image.
- L58 _public enumerator_ `CenterBoundingBox` — Centers the actual geometry in such a way that left/right and top/bottom margins are the same.

#### struct `FSvgDistanceFieldConfiguration`  
`struct FSvgDistanceFieldConfiguration`  
_L62-110_
- reflection: `USTRUCT(BlueprintType)`
- L68 _public member_ `ESvgDistanceFieldType DistanceFieldType = ESvgDistanceFieldType::Simple;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField)` — Sets which type of signed distance field should be generated.
- L72 _public member_ `float BaseDistanceSpread = 4.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField)` — The base portion of the representable distance spread that will be divided equally between the inside and outside.
- L76 _public member_ `float ExtraOuterDistanceSpread = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField)` — The additional asymmetrical outer portion of the representable distance spread.
- L80 _public member_ `float ExtraInnerDistanceSpread = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField)` — The additional asymmetrical inner portion of the representable distance spread.
- L84 _public member_ `ESvgDistanceFieldUnits DistanceSpreadUnits = ESvgDistanceFieldUnits::OutputPixels;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField)` — Specifies the units in which all distance spread values are expressed.
- L88 _public member_ `int32 OutputWidth = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField, meta=(ClampMin=1))` — The width of the output image in pixels
- L92 _public member_ `int32 OutputHeight = 256;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField, meta=(ClampMin=1))` — The height of the output image in pixels
- L96 _public member_ `ESvgDistanceFieldScaleMode ScaleMode = ESvgDistanceFieldScaleMode::ExplicitScale;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField)` — Specifies how the SVG coordinates are scaled when converting to output pixel coordinates.
- L100 _public member_ `float Scale = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField, meta=(ClampMin=0, EditCondition="ScaleMode == ESvgDistanceFieldScaleMode::ExplicitScale"))` — The scaling factor from SVG coordinates to pixel coordinates if ScaleMode is set to ExplicitScale, otherwise ignored
- L104 _public member_ `ESvgDistanceFieldPlacementMode PlacementMode = ESvgDistanceFieldPlacementMode::DoNotTranslate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField)` — Specifies how the SVG coordinates are translated when converting to output pixel coordinates.
- L108 _public member_ `float MiterLimit = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=SvgDistanceField, meta=(ClampMin=0, EditCondition="DistanceFieldType != ESvgDistanceFieldType::Simple"))` — If DistanceFieldType is set to Perpendicular or MultiChannelAndSimple, specifies the miter limit when computing the bounding box.

### `Source/Editor/SVGDistanceField/Public/SvgDistanceFieldGenerate.h` (Public)


#### Free symbols / members of external scopes

- L9 _prototype_ `bool SvgDistanceFieldGenerate(TArrayView64<const char> InSvgData, const FSvgDistanceFieldConfiguration& InConfiguration, FDistanceFieldImage& OutDistanceFieldImage);`

### `Source/Editor/SVGDistanceField/Public/SvgDistanceFieldGenerator.h` (Public)


#### class `USvgDistanceFieldGenerator`  
`class USvgDistanceFieldGenerator : public UBlueprintFunctionLibrary`  
_L15-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L23 _public prototype_ `static UTexture2D* GenerateTextureFromSvgFile(const FString& SvgFilePath, const FSvgDistanceFieldConfiguration& Configuration);` — `UFUNCTION(BlueprintCallable, Category=SvgDistanceField)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SVGDISTANCEFIELD_API`
