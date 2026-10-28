# Programs / DatasmithMax2027

- module root: `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter`
- headers: 28; symbols: 1170
- symbol kinds: class=74, delegate=1, enum=11, enumerator=145, function=80, macro=175, member=227, namespace=12, prototype=421, struct=20, typedef=4

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/DatasmithMaxAttributes.h` (Private)


#### enum `EStaticMeshExportMode`  
`enum EStaticMeshExportMode : uint8`  
_L9-15_
- L12 _public enumerator_ `Default` — Export the static mesh (Default)
- L14 _public enumerator_ `BoundingBox` — Export a simplified geometry for the mesh

#### class `FDatasmithMaxStaticMeshAttributes`  
`class FDatasmithMaxStaticMeshAttributes`  
_L20-47_
- desc: Attributes extracted from the datasmith attributes modifier for a static mesh
- L24 _public prototype_ `static TOptional<FDatasmithMaxStaticMeshAttributes> ExtractStaticMeshAttributes(INode* Node);`
- L26 _public prototype_ `FDatasmithMaxStaticMeshAttributes(int32 LightmapUVChannel, INode* CustomCollisionNode, EStaticMeshExportMode ExportMode);`
- L28 _public function_ `int32 GetLightmapUVChannel() const`
- L33 _public function_ `INode* GetCustomCollisonNode() const`
- L38 _public function_ `EStaticMeshExportMode GetExportMode() const`
- L44 _private member_ `const int32 LightmapUVChannel;`
- L45 _private member_ `INode* CustomCollisionNode;`
- L46 _private member_ `const EStaticMeshExportMode ExportMode;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/DatasmithMaxSceneHelper.h` (Private)


#### enum `EMaxExporterInstanceMode`  
`enum class EMaxExporterInstanceMode`  
_L26-32_
- desc: This tell the exporter how to manage the instancing of a Geometry
- L28 _public enumerator_ `NotInstanced`
- L29 _public enumerator_ `InstanceMaster`
- L30 _public enumerator_ `InstanceCopy`
- L31 _public enumerator_ `UnrealHISM`

#### enum `EMaxTriMode`  
`enum class EMaxTriMode`  
_L34-39_
- L36 _public enumerator_ `TriNotChecked`
- L37 _public enumerator_ `TriEnabled`
- L38 _public enumerator_ `TriDisabled`

#### enum `EMaxEntityType`  
`enum class EMaxEntityType`  
_L41-47_
- L43 _public enumerator_ `Geometry`
- L44 _public enumerator_ `Light`
- L45 _public enumerator_ `Camera`
- L46 _public enumerator_ `Dummy`

#### enum `EMaxLightClass`  
`enum class EMaxLightClass`  
_L49-68_
- L51 _public enumerator_ `Unknown`
- L52 _public enumerator_ `TheaLightOmni`
- L53 _public enumerator_ `TheaLightSpot`
- L54 _public enumerator_ `TheaLightIES`
- L55 _public enumerator_ `TheaLightPlane`
- L56 _public enumerator_ `SpotLight`
- L57 _public enumerator_ `DirectLight`
- L58 _public enumerator_ `OmniLight`
- L59 _public enumerator_ `PhotometricLight`
- L60 _public enumerator_ `PhotoplaneLight`
- L61 _public enumerator_ `VRayLightIES`
- L62 _public enumerator_ `VRayLight`
- L63 _public enumerator_ `CoronaLight`
- L64 _public enumerator_ `ArnoldLight`
- L65 _public enumerator_ `SunEquivalent`
- L66 _public enumerator_ `SkyEquivalent`
- L67 _public enumerator_ `SkyPortal`

#### class `FDatasmithMaxSceneHelper`  
`class FDatasmithMaxSceneHelper`  
_L70-78_
- L73 _public prototype_ `static EMaxLightClass GetLightClass(INode* InNode);`
- L74 _public prototype_ `static bool CanBeTriMesh(Object* Obj);`
- L75 _public member_ `static const TArray< FString, TInlineAllocator< 4 > > CollisionNodesPrefixes;` — List of supported mesh prefixes for Unreal collision
- L77 _public prototype_ `static bool HasCollisionName(INode* Node);`

#### Free symbols / members of external scopes

- L23 _prototype_ `DWORD WINAPI DummyFunction(LPVOID Arg);` — Dummy function for calls to ProgressStart in the Max API

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/DatasmithMaxTexmapParser.h` (Private)


#### struct `DatasmithMaxTexmapParser::FMapParameter`  
`struct FMapParameter`  
_L15-32_
- L17 _public function_ `FMapParameter() : Map( nullptr ) , bEnabled( true ) , Weight( 1.f )`
- L24 _public function_ `bool IsMapPresentAndEnabled()`
- L29 _public member_ `Texmap* Map;`
- L30 _public member_ `bool bEnabled;`
- L31 _public member_ `float Weight;`

#### struct `DatasmithMaxTexmapParser::FWeightedColorParameter`  
`struct FWeightedColorParameter`  
_L34-44_
- L36 _public function_ `FWeightedColorParameter() : Value( FLinearColor::White ) , Weight( 1.f )`
- L42 _public member_ `FLinearColor Value;`
- L43 _public member_ `float Weight;`

#### struct `DatasmithMaxTexmapParser::FCompositeTexmapParameters`  
`struct FCompositeTexmapParameters`  
_L46-62_
- L61 _public member_ `TArray< FLayer > Layers;`

#### struct `DatasmithMaxTexmapParser::FCompositeTexmapParameters::FLayer`  
`struct FLayer`  
_L48-59_
- L50 _public function_ `FLayer() : CompositeMode( EDatasmithCompositeCompMode::Alpha )`
- L55 _public member_ `EDatasmithCompositeCompMode CompositeMode;`
- L57 _public member_ `FMapParameter Map;`
- L58 _public member_ `FMapParameter Mask;`

#### struct `DatasmithMaxTexmapParser::FNormalMapParameters`  
`struct FNormalMapParameters`  
_L66-74_
- L68 _public member_ `FMapParameter NormalMap;`
- L69 _public member_ `FMapParameter BumpMap;`
- L71 _public member_ `bool bFlipGreen = false;`
- L72 _public member_ `bool bFlipRed = false;`
- L73 _public member_ `bool bSwapRedAndGreen = false;`

#### struct `DatasmithMaxTexmapParser::FAutodeskBitmapParameters`  
`struct FAutodeskBitmapParameters`  
_L78-92_
- L80 _public member_ `PBBitmap* SourceFile = nullptr;`
- L81 _public member_ `float Brightness = 1;`
- L82 _public member_ `bool bInvertImage = false;`
- L83 _public member_ `FVector2D Position = FVector2D(0,0);`
- L84 _public member_ `float Rotation = 0;`
- L85 _public member_ `FVector2D Scale = FVector2D(1, 1);`
- L86 _public member_ `bool bRepeatHorizontal = true;`
- L87 _public member_ `bool bRepeatVertical = true;`
- L88 _public member_ `float BlurValue = 0;`
- L89 _public member_ `float BlurOffset = 0;`
- L90 _public member_ `float FilteringValue = 0;`
- L91 _public member_ `int MapChannel = 1;`

#### struct `DatasmithMaxTexmapParser::FCoronaBitmapParameters`  
`struct FCoronaBitmapParameters`  
_L96-108_
- L98 _public member_ `FString Path;`
- L99 _public member_ `float TileU = 1.0f;`
- L100 _public member_ `float TileV = 1.0f;`
- L101 _public member_ `float OffsetU = 1.0f;`
- L102 _public member_ `float OffsetV = 1.0f;`
- L103 _public member_ `float RotW = 0.f;`
- L104 _public member_ `int UVCoordinate = 0;`
- L105 _public member_ `int MirrorU = 0;`
- L106 _public member_ `int MirrorV = 0;`
- L107 _public member_ `float Gamma = 1.0f;`

#### struct `DatasmithMaxTexmapParser::FCoronaColorParameters`  
`struct FCoronaColorParameters`  
_L112-121_
- L114 _public member_ `FLinearColor RgbColor = FLinearColor::Black;`
- L115 _public member_ `FVector ColorHdr = FVector::ZeroVector;`
- L116 _public member_ `float Multiplier = 1.f;`
- L117 _public member_ `float Temperature = 6500.f;`
- L118 _public member_ `int Method = 0;`
- L119 _public member_ `FString HexColor;`
- L120 _public member_ `bool bInputIsLinear = false;`

#### struct `DatasmithMaxTexmapParser::FColorCorrectionParameters`  
`struct FColorCorrectionParameters`  
_L125-147_
- L127 _public member_ `Texmap* TextureSlot1 = nullptr;`
- L128 _public member_ `FLinearColor Color1;`
- L129 _public member_ `FLinearColor Tint;`
- L131 _public member_ `float HueShift = 0.f;`
- L132 _public member_ `float Saturation = 0.f;`
- L133 _public member_ `float LiftRGB = 0.f;`
- L134 _public member_ `float Brightness = 0.f;`
- L135 _public member_ `float GammaRGB = 0.f;`
- L136 _public member_ `float Contrast = 0.f;`
- L137 _public member_ `float TintStrength = 0.f;`
- L139 _public member_ `int RewireR = 0;`
- L140 _public member_ `int RewireG = 0;`
- L141 _public member_ `int RewireB = 0;`
- L142 _public member_ `bool bAdvancedLightnessMode = false;`
- L144 _public member_ `bool bEnableR = false;`
- L145 _public member_ `bool bEnableG = false;`
- L146 _public member_ `bool bEnableB = false;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace DatasmithMaxTexmapParser`
- L64 _prototype_ `FCompositeTexmapParameters ParseCompositeTexmap( Texmap* InTexmap );` (scope `DatasmithMaxTexmapParser`)
- L76 _prototype_ `FNormalMapParameters ParseNormalMap( Texmap* InTexmap );` (scope `DatasmithMaxTexmapParser`)
- L94 _prototype_ `FAutodeskBitmapParameters ParseAutodeskBitmap(Texmap* InTexmap);` (scope `DatasmithMaxTexmapParser`)
- L110 _prototype_ `FCoronaBitmapParameters ParseCoronaBitmap(Texmap* InTexmap);` (scope `DatasmithMaxTexmapParser`)
- L123 _prototype_ `FCoronaColorParameters ParseCoronaColor(Texmap* InTexmap);` (scope `DatasmithMaxTexmapParser`)
- L149 _prototype_ `FColorCorrectionParameters ParseColorCorrection(Texmap* InTexmap);` (scope `DatasmithMaxTexmapParser`)

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxCoronaMaterialsToUEPbr.h` (Private)


#### class `FDatasmithMaxCoronaMaterialsToUEPbr`  
`class FDatasmithMaxCoronaMaterialsToUEPbr : public FDatasmithMaxMaterialsToUEPbrExpressions`  
_L7-14_
- inherits: `FDatasmithMaxMaterialsToUEPbrExpressions`
- L10 _public prototype_ `FDatasmithMaxCoronaMaterialsToUEPbr();`
- L12 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L13 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxCoronaBlendMaterialToUEPbr`  
`class FDatasmithMaxCoronaBlendMaterialToUEPbr : public FDatasmithMaxCoronaMaterialsToUEPbr`  
_L16-21_
- inherits: `FDatasmithMaxCoronaMaterialsToUEPbr`
- L19 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L20 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxCoronaLightMaterialToUEPbr`  
`class FDatasmithMaxCoronaLightMaterialToUEPbr : public FDatasmithMaxCoronaMaterialsToUEPbr`  
_L23-28_
- inherits: `FDatasmithMaxCoronaMaterialsToUEPbr`
- L26 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L27 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxCoronaPhysicalMaterialToUEPbr`  
`class FDatasmithMaxCoronaPhysicalMaterialToUEPbr : public FDatasmithMaxCoronaMaterialsToUEPbr`  
_L30-35_
- inherits: `FDatasmithMaxCoronaMaterialsToUEPbr`
- L33 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L34 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxCoronaTexmapToUEPbr.h` (Private)


#### class `FDatasmithMaxCoronaAOToUEPbr`  
`class FDatasmithMaxCoronaAOToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L8-13_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L11 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L12 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxCoronaColorToUEPbr`  
`class FDatasmithMaxCoronaColorToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L15-20_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L18 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L19 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxCoronalNormalToUEPbr`  
`class FDatasmithMaxCoronalNormalToUEPbr : public FDatasmithMaxNormalToUEPbr`  
_L22-30_
- inherits: `FDatasmithMaxNormalToUEPbr`
- L24 _private typedef_ `using Super = FDatasmithMaxNormalToUEPbr;`
- L27 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L28 _public prototype_ `DatasmithMaxTexmapParser::FNormalMapParameters ParseMap( Texmap* InTexmap ) override;`
- L29 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxCoronalBitmapToUEPbr`  
`class FDatasmithMaxCoronalBitmapToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L32-37_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L35 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L36 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxMaterialsToUEPbr.h` (Private)


#### struct `DatasmithMaxDirectLink::FMaterialConversionContext`  
`struct FMaterialConversionContext`  
_L32-37_
- L35 _public member_ `TSet<Texmap*>& TexmapsConverted;` — Records texmaps that were asked for conversion while material conversion is performed
- L36 _public member_ `FMaterialsCollectionTracker& MaterialsCollectionTracker;`

#### class `FDatasmithMaxMaterialsToUEPbrManager`  
`class FDatasmithMaxMaterialsToUEPbrManager`  
_L43-50_
- L46 _public prototype_ `static FDatasmithMaxMaterialsToUEPbr* GetMaterialConverter( Mtl* Material );`
- L47 _public prototype_ `static void AddDatasmithMaterial(TSharedRef<IDatasmithScene> DatasmithScene, Mtl* Material, TSharedPtr<IDatasmithBaseMaterialElement> DatasmithMaterial);`
- L48 _public prototype_ `static const TCHAR* GetDatasmithMaterialName(Mtl* Material);`
- L49 _public member_ `static DatasmithMaxDirectLink::FMaterialConversionContext* Context;`

#### class `FDatasmithMaxMaterialsToUEPbr`  
`class FDatasmithMaxMaterialsToUEPbr`  
_L52-119_
- L55 _public prototype_ `FDatasmithMaxMaterialsToUEPbr();`
- L56 _public prototype_ `virtual ~FDatasmithMaxMaterialsToUEPbr() = default;`
- L58 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) = 0;`
- L60 _public prototype_ `virtual bool IsSupported( Mtl* Material ) = 0;` — Called by FDatasmithMaxMaterialsToUEPbrManager to see if instantiated converter can actually convert a material instance
- L61 _public prototype_ `virtual bool IsTexmapSupported( Texmap* InTexmap ) const;`
- L66 _public prototype_ `IDatasmithMaterialExpression* ConvertTexmap( const DatasmithMaxTexmapParser::FMapParameter& MapParameter );` — Returns a LinearInterpolate expression if the map weight is smaller than 1.f, input 0 is not connected in that case
- L69 _public function_ `void AddTexmap(Texmap* Texmap, const FString& DesiredTextureElementName, const TSharedPtr<DatasmithMaxDirectLink::ITexmapToTextureElementConverter>& Converter)` — Texmap which needs to have a datasmith texture element created for
- L89 _public member_ `} ConvertState;`
- L91 _public prototype_ `void AddConvertedMap(const DatasmithMaxTexmapParser::FMapParameter& MapParameter);`
- L93 _public function_ `const TCHAR* GetMaterialName(Mtl* Material) const`
- L98 _public member_ `DatasmithMaxDirectLink::FMaterialConversionContext* Context = nullptr;`
- L101 _protected member_ `TIndirectArray< IDatasmithMaxTexmapToUEPbr > TexmapConverters;`

#### struct `FDatasmithMaxMaterialsToUEPbr::FConvertState`  
`struct FConvertState`  
_L77-89_
- L79 _public member_ `TSharedPtr< IDatasmithScene > DatasmithScene;`
- L80 _public member_ `TSharedPtr< IDatasmithUEPbrMaterialElement > MaterialElement;`
- L81 _public member_ `FString AssetsPath;`
- L83 _public member_ `bool bCanBake = true;`
- L84 _public member_ `bool bIsMonoChannel = false;` — true if we are parsing a mono channel (ie: opacity)
- L85 _public member_ `bool bTreatNormalMapsAsLinear = false;` — Corona has an option that treats all normal map inputs as linear
- L87 _public member_ `EDatasmithTextureMode DefaultTextureMode = EDatasmithTextureMode::Diffuse;`

#### struct `FDatasmithMaxMaterialsToUEPbr::FScopedConvertState`  
`struct FScopedConvertState`  
_L104-118_
- desc: Structure used to have recursive import state.
- L106 _public function_ `FScopedConvertState(FConvertState& InCurrentConvertState) : CurrentConvertStateRef(InCurrentConvertState), PreviousConvertState(InCurrentConvertState)`
- L111 _public function_ `~FScopedConvertState()`
- L116 _private member_ `FConvertState& CurrentConvertStateRef;`
- L117 _private member_ `const FConvertState PreviousConvertState;`

#### class `IDatasmithMaxTexmapToUEPbr`  
`class IDatasmithMaxTexmapToUEPbr`  
_L121-128_
- L124 _public prototype_ `virtual ~IDatasmithMaxTexmapToUEPbr() = default;`
- L126 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const = 0;`
- L127 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) = 0;`

#### class `FDatasmithMaxMaterialsToUEPbrExpressions`  
`class FDatasmithMaxMaterialsToUEPbrExpressions: public FDatasmithMaxMaterialsToUEPbr`  
_L137-191_
- inherits: `FDatasmithMaxMaterialsToUEPbr`
- L140 _public prototype_ `TSharedPtr<IDatasmithUEPbrMaterialElement> GetMaterialElement();`
- L143 _public prototype_ `IDatasmithMaterialExpression& Scalar(float Value, const TCHAR* ParameterName=nullptr);` — Specify ParameterName to have constant exposed as material parameter
- L144 _public prototype_ `IDatasmithMaterialExpression& Color(const FLinearColor& Value, const TCHAR* ParameterName=nullptr);`
- L146 _public prototype_ `IDatasmithMaterialExpression* WeightTextureOrScalar(const DatasmithMaxTexmapParser::FMapParameter& TextureWeight, float Weight);`
- L148 _public prototype_ `IDatasmithMaterialExpression& Add(IDatasmithMaterialExpression& A, IDatasmithMaterialExpression& B);`
- L149 _public prototype_ `IDatasmithMaterialExpression& Add(IDatasmithMaterialExpression& A, float B);`
- L151 _public prototype_ `IDatasmithMaterialExpression& Subtract(IDatasmithMaterialExpression& A, IDatasmithMaterialExpression& B);`
- L152 _public prototype_ `IDatasmithMaterialExpression& Subtract(IDatasmithMaterialExpression& A, float B);`
- L154 _public prototype_ `IDatasmithMaterialExpression& Multiply(IDatasmithMaterialExpression& A, IDatasmithMaterialExpression& B);`
- L155 _public prototype_ `IDatasmithMaterialExpression& Multiply(IDatasmithMaterialExpression& A, float B);`
- L157 _public prototype_ `IDatasmithMaterialExpression& Divide(IDatasmithMaterialExpression& A, IDatasmithMaterialExpression& B);`
- L159 _public prototype_ `IDatasmithMaterialExpression& Desaturate(IDatasmithMaterialExpression& A);`
- L161 _public prototype_ `IDatasmithMaterialExpression& Power(IDatasmithMaterialExpression& A, IDatasmithMaterialExpression& B);`
- L162 _public prototype_ `IDatasmithMaterialExpression& Power(IDatasmithMaterialExpression& A, float Exp);`
- L164 _public prototype_ `IDatasmithMaterialExpression& Lerp(IDatasmithMaterialExpression& A, IDatasmithMaterialExpression& B, IDatasmithMaterialExpression& Alpha);`
- L166 _public prototype_ `IDatasmithMaterialExpression& Fresnel(IDatasmithMaterialExpression* Exponent=nullptr, IDatasmithMaterialExpression* BaseReflectFraction=nullptr);` — Any input can be null
- L168 _public prototype_ `IDatasmithMaterialExpression& PathTracingQualitySwitch(IDatasmithMaterialExpression& Normal, IDatasmithMaterialExpression& PathTraced);`
- L170 _public prototype_ `IDatasmithMaterialExpression* BlendTexmapWithColor(const DatasmithMaxTexmapParser::FMapParameter& Texmap, const FLinearColor& InColor, const TCHAR* ColorName = nullptr, const TCHAR* WeightName = nullptr);`
- L171 _public prototype_ `IDatasmithMaterialExpression* BlendTexmapWithScalar(const DatasmithMaxTexmapParser::FMapParameter& Texmap, float InScalar, const TCHAR* ScalarName = nullptr, const TCHAR* WeightName = nullptr);`
- L174 _public function_ `FLinearColor ScaleRGB(const FLinearColor& C, const float X)` — Multiply RGB without multiplying A
- L176 _public prototype_ `IDatasmithMaterialExpression* ApplyWeightExpression(IDatasmithMaterialExpression* ValueExpression, IDatasmithMaterialExpression* WeightExpression);`
- L178 _public prototype_ `IDatasmithMaterialExpression& CalcIORComplex(double IORn, double IORk, IDatasmithMaterialExpression& ToBeConnected90, IDatasmithMaterialExpression& ToBeConnected0);`
- L179 _public prototype_ `IDatasmithMaterialExpression& CalcIORComplex(IDatasmithMaterialExpression& IORn, IDatasmithMaterialExpression& IORk, IDatasmithMaterialExpression& ToBeConnected90, IDatasmithMaterialExpression& ToBeConnected0);`
- L181 _public prototype_ `void Connect(IDatasmithExpressionInput& Input, IDatasmithMaterialExpression& ValueExpression);`
- L182 _public prototype_ `bool Connect(IDatasmithExpressionInput& Input, IDatasmithMaterialExpression* ValueExpression);` — Connect if not null
- L184 _public prototype_ `IDatasmithMaterialExpression* TextureOrColor(const TCHAR* Name, const DatasmithMaxTexmapParser::FMapParameter& Map, FLinearColor Color);`
- L187 _public prototype_ `IDatasmithMaterialExpression* TextureOrScalar(const TCHAR* Name, const DatasmithMaxTexmapParser::FMapParameter& Map, float Value);`
- L190 _public prototype_ `IDatasmithMaterialExpression& OneMinus(IDatasmithMaterialExpression& Expression);`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace DatasmithMaxTexmapParser`
- L28 _namespace_ `namespace DatasmithMaxDirectLink`
- L205 _macro_ `#define COMPOSE_OR_DEFAULT1(Default, Func, Param0) ([this](IDatasmithMaterialExpression* P0, IDatasmithMaterialExpression* D) {return P0 ? &Func(*P0) : D; } (Param0, Default))` — Create expression from expression parameters when they are all non-null or return default value E.g. instead of: IDatasmithMaterialExpression* SomeExpression = MakeExpressionCanReturnNull(...) IDatasmithMaterialExpression* ResultExpression = SomeExpression ? Desaturate(SomeExpression) : nullptr; Can do this: IDatasmithMaterialExpression* ResultExpression = COMPOSE_OR_NULL(Desaturate, MakeExpressionCanReturnNull(...)); Which allows chaining expressions: COMPOSE_OR_DEFAULT2(&Scalar(1), Multiply, COMPOSE_OR_NULL(Desaturate, MakeExpressionCanReturnNull(...)), AnotherExpression) Implementation details: Pass params by value in order to prevent statement creating expression to be evaluated twice e.g. COMPOSE_OR_DEFAULT1(nullptr, Multiply, &Scalar(1.0), SomeExpression) won't create two expressions of each Scalar Func should be a method of this of free function - so it can be just substituted
- L206 _macro_ `#define COMPOSE_OR_DEFAULT2(Default, Func, Param0, Param1) ([this](IDatasmithMaterialExpression* P0, IDatasmithMaterialExpression* P1, IDatasmithMaterialExpression* D) { return (P0 && P1) ? &Func(*P0, *P1) : D;} (Param0, Param1, Default))`
- L208 _macro_ `#define COMPOSE_OR_NULL(Func, Param0) ([this](IDatasmithMaterialExpression* P0) {return P0 ? &Func(*P0) : nullptr; } (Param0 ))` — Calls Func when param is not NULL, returns NULL otherwise
- L209 _macro_ `#define COMPOSE_OR_NULL2(Func, Param0, Param1) ([this](IDatasmithMaterialExpression* P0, IDatasmithMaterialExpression* P1) { return (P0 && P1) ? &Func(*P0, *P1) : nullptr;} (Param0, Param1))`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxMentalMaterialToUEPbr.h` (Private)


#### class `FDatasmithMaxMentalMaterialToUEPbr`  
`class FDatasmithMaxMentalMaterialToUEPbr : public FDatasmithMaxMaterialsToUEPbrExpressions`  
_L7-12_
- inherits: `FDatasmithMaxMaterialsToUEPbrExpressions`
- L10 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L11 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxPhysicalMaterialToUEPbr.h` (Private)


#### class `FDatasmithMaxPhysicalMaterialToUEPbr`  
`class FDatasmithMaxPhysicalMaterialToUEPbr : public FDatasmithMaxMaterialsToUEPbrExpressions`  
_L7-12_
- inherits: `FDatasmithMaxMaterialsToUEPbrExpressions`
- L10 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L11 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxScanlineMaterialsToUEPbr.h` (Private)


#### class `FDatasmithMaxScanlineMaterialsToUEPbr`  
`class FDatasmithMaxScanlineMaterialsToUEPbr : public FDatasmithMaxMaterialsToUEPbr`  
_L7-12_
- inherits: `FDatasmithMaxMaterialsToUEPbr`
- L10 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L11 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxBlendMaterialsToUEPbr`  
`class FDatasmithMaxBlendMaterialsToUEPbr : public FDatasmithMaxMaterialsToUEPbr`  
_L14-19_
- inherits: `FDatasmithMaxMaterialsToUEPbr`
- L17 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L18 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxTexmapToUEPbr.h` (Private)


#### class `FDatasmithMaxTexmapToUEPbrUtils`  
`class FDatasmithMaxTexmapToUEPbrUtils`  
_L11-19_
- L14 _public prototype_ `static IDatasmithMaterialExpression* ConvertTextureOutput( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, IDatasmithMaterialExpression* InputExpression, class TextureOutput* InTextureOutput );`
- L15 _public prototype_ `static void SetupTextureCoordinates( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, IDatasmithExpressionInput& UVCoordinatesInput, Texmap* InTexmap );`
- L16 _public prototype_ `static IDatasmithMaterialExpression* MapOrValue( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, const DatasmithMaxTexmapParser::FMapParameter& MapParameter, const TCHAR* ParameterName, TOptional< FLinearColor > Color, TOptional< float > Scalar );`
- L18 _public prototype_ `static IDatasmithMaterialExpression* ConvertBitMap(FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap, FString& ActualBitmapName, bool bUseAlphaAsMono, bool bIsSRGB);`

#### class `FDatasmithMaxBitmapToUEPbr`  
`class FDatasmithMaxBitmapToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L21-26_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L24 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L25 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxAutodeskBitmapToUEPbr`  
`class FDatasmithMaxAutodeskBitmapToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L28-33_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L31 _public prototype_ `virtual bool IsSupported(const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap) const override;`
- L32 _public prototype_ `virtual IDatasmithMaterialExpression* Convert(FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap) override;`

#### class `FDatasmithMaxNormalToUEPbr`  
`class FDatasmithMaxNormalToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L35-41_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L38 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L39 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`
- L40 _public prototype_ `virtual DatasmithMaxTexmapParser::FNormalMapParameters ParseMap( Texmap* InTexmap );`

#### class `FDatasmithMaxRGBMultiplyToUEPbr`  
`class FDatasmithMaxRGBMultiplyToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L43-48_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L46 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L47 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxRGBTintToUEPbr`  
`class FDatasmithMaxRGBTintToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L50-55_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L53 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L54 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxMixToUEPbr`  
`class FDatasmithMaxMixToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L57-62_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L60 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L61 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxFalloffToUEPbr`  
`class FDatasmithMaxFalloffToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L64-69_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L67 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L68 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxNoiseToUEPbr`  
`class FDatasmithMaxNoiseToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L71-76_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L74 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L75 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxCompositeToUEPbr`  
`class FDatasmithMaxCompositeToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L78-83_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L81 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L82 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxTextureOutputToUEPbr`  
`class FDatasmithMaxTextureOutputToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L85-90_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L88 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L89 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxColorCorrectionToUEPbr`  
`class FDatasmithMaxColorCorrectionToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L95-99_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- desc: Color Correction is baked when possible but we convert some parameters when we can't bake it
- L97 _private prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L98 _private prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxBakeableToUEPbr`  
`class FDatasmithMaxBakeableToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L104-109_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- desc: Maps for which the result is baked into a texture
- L107 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L108 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxPassthroughToUEPbr`  
`class FDatasmithMaxPassthroughToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L114-123_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- desc: Maps for which we only export the first texmap or color
- L117 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L119 _public prototype_ `virtual const TCHAR* GetColorParameterName(Texmap* InTexmap) const;`
- L121 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`
- L122 _public prototype_ `FLinearColor GetColorParameter( Texmap* InTexmap, const TCHAR* ParameterName );`

#### class `FDatasmithMaxCellularToUEPbr`  
`class FDatasmithMaxCellularToUEPbr : public FDatasmithMaxPassthroughToUEPbr`  
_L125-129_
- inherits: `FDatasmithMaxPassthroughToUEPbr`
- L127 _private prototype_ `virtual const TCHAR* GetColorParameterName(Texmap* InTexmap) const override;`
- L128 _private prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`

#### class `FDatasmithMaxThirdPartyMultiTexmapToUEPbr`  
`class FDatasmithMaxThirdPartyMultiTexmapToUEPbr : public FDatasmithMaxPassthroughToUEPbr`  
_L131-135_
- inherits: `FDatasmithMaxPassthroughToUEPbr`
- L133 _private prototype_ `virtual const TCHAR* GetColorParameterName(Texmap* InTexmap) const override;`
- L134 _private prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxVRayTexmapToUEPbr.h` (Private)


#### class `FDatasmithMaxVRayColorTexmapToUEPbr`  
`class FDatasmithMaxVRayColorTexmapToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L7-12_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L10 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L11 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxVRayHDRITexmapToUEPbr`  
`class FDatasmithMaxVRayHDRITexmapToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L14-19_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L17 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L18 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

#### class `FDatasmithMaxVRayDirtTexmapToUEPbr`  
`class FDatasmithMaxVRayDirtTexmapToUEPbr : public IDatasmithMaxTexmapToUEPbr`  
_L21-26_
- inherits: `IDatasmithMaxTexmapToUEPbr`
- L24 _public prototype_ `virtual bool IsSupported( const FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) const override;`
- L25 _public prototype_ `virtual IDatasmithMaterialExpression* Convert( FDatasmithMaxMaterialsToUEPbr* MaxMaterialToUEPbr, Texmap* InTexmap ) override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/MaxMaterialsToUEPbr/DatasmithMaxVrayMaterialsToUEPbr.h` (Private)


#### class `FDatasmithMaxVRayMaterialsToUEPbr`  
`class FDatasmithMaxVRayMaterialsToUEPbr : public FDatasmithMaxMaterialsToUEPbr`  
_L7-14_
- inherits: `FDatasmithMaxMaterialsToUEPbr`
- L10 _public prototype_ `FDatasmithMaxVRayMaterialsToUEPbr();`
- L12 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L13 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxVRay2SidedMaterialsToUEPbr`  
`class FDatasmithMaxVRay2SidedMaterialsToUEPbr : public FDatasmithMaxMaterialsToUEPbr`  
_L16-21_
- inherits: `FDatasmithMaxMaterialsToUEPbr`
- L19 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L20 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxVRayWrapperMaterialsToUEPbr`  
`class FDatasmithMaxVRayWrapperMaterialsToUEPbr : public FDatasmithMaxMaterialsToUEPbr`  
_L23-28_
- inherits: `FDatasmithMaxMaterialsToUEPbr`
- L26 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L27 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxVRayBlendMaterialToUEPbr`  
`class FDatasmithMaxVRayBlendMaterialToUEPbr : public FDatasmithMaxVRayMaterialsToUEPbr`  
_L30-35_
- inherits: `FDatasmithMaxVRayMaterialsToUEPbr`
- L33 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L34 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

#### class `FDatasmithMaxVRayLightMaterialToUEPbr`  
`class FDatasmithMaxVRayLightMaterialToUEPbr : public FDatasmithMaxMaterialsToUEPbrExpressions`  
_L37-42_
- inherits: `FDatasmithMaxMaterialsToUEPbrExpressions`
- L40 _public prototype_ `virtual bool IsSupported( Mtl* Material ) override;`
- L41 _public prototype_ `virtual void Convert( TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithBaseMaterialElement >& MaterialElement, Mtl* Material, const TCHAR* AssetsPath ) override;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/UI/IDatasmith3dsMaxUI.h` (Private)


#### class `DatasmithMaxDirectLink::Ui::IMessagesWindow`  
`class IMessagesWindow`  
_L10-23_
- L14 _public prototype_ `virtual void OpenWindow() = 0;`
- L16 _public prototype_ `virtual void AddError(const FString& Message) = 0;`
- L17 _public prototype_ `virtual void AddWarning(const FString& Message) = 0;`
- L18 _public prototype_ `virtual void AddInfo(const FString& Message) = 0;`
- L19 _public prototype_ `virtual void AddCompletion(const FString& Message) = 0;`
- L20 _public prototype_ `virtual void ClearMessages() = 0;`
- L22 _public prototype_ `virtual ~IMessagesWindow() = default;`

#### Free symbols / members of external scopes

- L5 _namespace_ `namespace DatasmithMaxDirectLink`
- L7 _namespace_ `namespace Ui` (scope `DatasmithMaxDirectLink`)
- L25 _prototype_ `IMessagesWindow* CreateMessagesWindow();` (scope `DatasmithMaxDirectLink::Ui`)

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Private/VRayLights.h` (Private)


#### enum `EVRayIESLightShapes`  
`enum class EVRayIESLightShapes`  
_L5-12_
- L7 _public enumerator_ `Point`
- L8 _public enumerator_ `Rectangle`
- L9 _public enumerator_ `Circle`
- L10 _public enumerator_ `Sphere`
- L11 _public enumerator_ `VerticalCylinder`

#### enum `EVRayLightParamBlocks`  
`enum class EVRayLightParamBlocks : short`  
_L14-17_
- L16 _public enumerator_ `Params`

#### enum `EVrayLightsParams`  
`enum class EVrayLightsParams : short`  
_L20-77_
- desc: Based on VRay SDK pb2enum.h
- L22 _public enumerator_ `LightOn`
- L23 _public enumerator_ `Type`
- L24 _public enumerator_ `Size0`
- L25 _public enumerator_ `Size1`
- L26 _public enumerator_ `Size2`
- L27 _public enumerator_ `MinSamples`
- L28 _public enumerator_ `Samples`
- L29 _public enumerator_ `Color`
- L30 _public enumerator_ `Multiplier`
- L31 _public enumerator_ `DoubleSided`
- L32 _public enumerator_ `Transparent`
- L33 _public enumerator_ `IgnoreNormals`
- L34 _public enumerator_ `NormalizeColor`
- L35 _public enumerator_ `NoDecay`
- L36 _public enumerator_ `StoreWithIrradMap`
- L37 _public enumerator_ `DegradeDepth`
- L38 _public enumerator_ `LightPortal`
- L39 _public enumerator_ `SmoothShadows`
- L40 _public enumerator_ `Texmap`
- L41 _public enumerator_ `TexmapOn`
- L42 _public enumerator_ `TexmapResolution`
- L43 _public enumerator_ `DomeEmitRadius`
- L44 _public enumerator_ `DomeTargetRadius`
- L45 _public enumerator_ `ShadowBias`
- L46 _public enumerator_ `DomeVisibleOriginal`
- L47 _public enumerator_ `AffectDiffuse`
- L48 _public enumerator_ `AffectSpecular`
- L49 _public enumerator_ `DomeSpherical`
- L50 _public enumerator_ `CutoffThresh`
- L51 _public enumerator_ `UseToneOpNotUsed`
- L52 _public enumerator_ `AffectReflections`
- L53 _public enumerator_ `SimplePortal`
- L54 _public enumerator_ `CastShadows`
- L55 _public enumerator_ `TexmapAdaptiveness`
- L56 _public enumerator_ `MeshSource`
- L57 _public enumerator_ `MeshFlip`
- L58 _public enumerator_ `LightDistribution`
- L59 _public enumerator_ `MeshMoveLight`
- L60 _public enumerator_ `Temperature`
- L61 _public enumerator_ `ColorMode`
- L62 _public enumerator_ `DomeRayDistance`
- L63 _public enumerator_ `DomeRayDistanceMode`
- L64 _public enumerator_ `UseLightscape`
- L65 _public enumerator_ `Targeted`
- L66 _public enumerator_ `TargetDistance`
- L67 _public enumerator_ `RectPreview`
- L68 _public enumerator_ `UseMis`
- L69 _public enumerator_ `WireColor`
- L70 _public enumerator_ `WireColorOn`
- L71 _public enumerator_ `TexmapLocktodome`
- L72 _public enumerator_ `DomeAffectAlpha`
- L73 _public enumerator_ `TexmapPreview`
- L74 _public enumerator_ `TextOn`
- L75 _public enumerator_ `AffectDiffuseAmount`
- L76 _public enumerator_ `AffectSpecularAmount`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxCameraExporter.h` (Public)


#### class `FDatasmithMaxCameraExporter`  
`class FDatasmithMaxCameraExporter`  
_L26-38_
- desc: Export both the cameras and the tone operator as they share a lot of parameters.
- L29 _public prototype_ `static bool ExportCamera( TimeValue CurrentTime, INode& Node, TSharedRef< IDatasmithCameraActorElement > CameraElement );`
- L30 _public prototype_ `static bool ExportToneOperator( ToneOperator& ToneOp, TSharedRef< IDatasmithPostProcessVolumeElement > PostProcessVolumeElement );`
- L33 _private prototype_ `static bool ExportPhysicalCamera( CameraObject& Camera, TSharedRef< IDatasmithCameraActorElement > CameraElement );`
- L34 _private prototype_ `static bool ExportVRayPhysicalCamera( CameraObject& Camera, TSharedRef< IDatasmithCameraActorElement > CameraElement );`
- L36 _private prototype_ `static bool ExportPhysicalExposureControl( ToneOperator& ToneOp, TSharedRef< IDatasmithPostProcessVolumeElement > PostProcessVolumeElement );`
- L37 _private prototype_ `static bool ExportVRayExposureControl( ToneOperator& ToneOp, TSharedRef< IDatasmithPostProcessVolumeElement > PostProcessVolumeElement );`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxClassIDs.h` (Public)


#### Free symbols / members of external scopes

- L5 _macro_ `#define DATASMITHUNREALEXPORTER_CLASS_ID Class_ID(0x49ad677c, 0x3c9edc59)`
- L8 _macro_ `#define DATASMITHUNREALATTRIBUTEMODIFIER_CLASS_ID Class_ID(0x60178e47, 0x2feafe95)` — MAXSCRIPT MODIFIER
- L12 _macro_ `#define RBITMAPCLASS Class_ID(0x240, 0x0)` — MAPS CLASS IDS
- L13 _macro_ `#define AUTODESKBITMAPCLASS Class_ID(0x7ed417e4, 0x273deef8)`
- L14 _macro_ `#define RGBMULTIPLYCLASS Class_ID(0x290, 0x0)`
- L15 _macro_ `#define RGBTINTCLASS Class_ID(0x224, 0x0)`
- L16 _macro_ `#define OUTPUTMAPCLASS Class_ID(0x2b0, 0x0)`
- L17 _macro_ `#define THEABITMAPCLASS Class_ID(0x30260307, 0x35535b85)`
- L18 _macro_ `#define REGULARNORMALCLASS Class_ID(0x243e22C6, 0x63f6a014)`
- L19 _macro_ `#define CORONANORMALCLASS Class_ID(0x2870ceaa, 0xcc18437c)`
- L20 _macro_ `#define COLORCORRECTCLASS Class_ID(0x2d0, 0x0)`
- L21 _macro_ `#define FALLOFFCLASS Class_ID(0x6ec3730c, 0x0)`
- L22 _macro_ `#define MIXCLASS Class_ID(0x230, 0x0)`
- L23 _macro_ `#define NOISECLASS Class_ID(0x234, 0x0)`
- L24 _macro_ `#define GRADIENTCLASS Class_ID(0x270, 0x0)`
- L25 _macro_ `#define GRADIENTRAMPCLASS Class_ID(0x1dec5b86, 0x43383a51)`
- L26 _macro_ `#define CHECKERCLASS Class_ID(0x00000200, 0x00000000)`
- L27 _macro_ `#define CELLULARCLASS Class_ID(0xc90017a5, 0x111940bb)`
- L28 _macro_ `#define COMPOSITETEXCLASS Class_ID(0x280, 0x0)`
- L29 _macro_ `#define CORONABITMAPCLASS Class_ID(0xabba5784, 0x65484244)`
- L30 _macro_ `#define CORONACOLORCLASS Class_ID(0x68426dca, 0x372362d4)`
- L31 _macro_ `#define CORONAMIXCLASS Class_ID(0x6847286f, 0x3fffaab4)`
- L32 _macro_ `#define CORONAMULTITEXCLASS Class_ID(0xbaba3487, 0x30782624)`
- L33 _macro_ `#define CORONAAOCLASS Class_ID(0x26ea4249, 0x404b4b59)`
- L34 _macro_ `#define CORONAPHYSICALSKYCLASS Class_ID(0x59577962, 0x4cab7ac1)`
- L35 _macro_ `#define MRPHYSICALSKYCLASS Class_ID(0x628e269e, 0x72386abf)`
- L36 _macro_ `#define MRPHYSICALSKYBCLASS Class_ID(0x223349b4, 0x562a7d8b)`
- L37 _macro_ `#define THIRDPARTYMULTITEXCLASS Class_ID(0x55c6d763, 0xc637bb2e)`
- L38 _macro_ `#define TILESMAPCLASS Class_ID(0x64035fb9, 0x69664cdc)`
- L39 _macro_ `#define COLORMAPCLASS Class_ID(0x139f22c6, 0x13f6a914)`
- L42 _macro_ `#define VRAYNORMALCLASS Class_ID(0x71fa6e51, 0x72057c2f)`
- L43 _macro_ `#define VRAYCOLORCLASS Class_ID(0x58f82b74, 0x73b75d7f)`
- L44 _macro_ `#define VRAYDIRTCLASS Class_ID(0x2f567899, 0x90d5ea4)`
- L45 _macro_ `#define VRAYPHYSICALSKYCLASS Class_ID(0x48480b4e, 0x62ff5a90)`
- L46 _macro_ `#define VRAYCOLOR2BUMP Class_ID(0x31e15d1d, 0x7d7e2810)`
- L47 _macro_ `#define VRAYHDRICLASS Class_ID(0x6769144b, 0x2c1017d)`
- L49 _macro_ `#define FORESTCOLORCLASS Class_ID(0x602f7917, 0x06354410)`
- L52 _macro_ `#define MULTIMAT_CLASS_ID Class_ID(0x200, 0x0)` — MATERIAL CLASS IDS
- L53 _macro_ `#define THEAMATERIALCLASS Class_ID(0x11dcacdd, 0x446400f0)`
- L54 _macro_ `#define THEAMATOLDCLASS Class_ID(0x372e9654, 0x1bdffef0)`
- L55 _macro_ `#define THEARANDOMCLASS Class_ID(0x544ff1de, 0x21ab5ea6)`
- L56 _macro_ `#define THEABASICCLASS Class_ID(0x587ff1de, 0x21ec5ea6)`
- L57 _macro_ `#define THEAGLOSSYCLASS Class_ID(0x39c95ac3, 0x1db33879)`
- L58 _macro_ `#define THEASSSCLASS Class_ID(0x65572bd9, 0x7137c4b)`
- L59 _macro_ `#define THEAFILMCLASS Class_ID(0x51a048bf, 0x3420ada8)`
- L60 _macro_ `#define THEACOATINGCLASS Class_ID(0x2ca1f05e, 0x224ea918)`
- L61 _macro_ `#define STANDARDMATCLASS Class_ID(0x2,0x0)`
- L62 _macro_ `#define SHELLCLASS Class_ID(0x255,0x0)`
- L63 _macro_ `#define BLENDMATCLASS Class_ID(0x250, 0x0)`
- L64 _macro_ `#define XREFMATCLASS Class_ID(0x272c0d4b,0x432a414b)`
- L65 _macro_ `#define ARCHDESIGNMATCLASS Class_ID(0x70b05735, 0x4a163654)`
- L66 _macro_ `#define CORONAMATCLASS Class_ID(0x70be6506,0x448931dd)`
- L67 _macro_ `#define CORONALAYERMATCLASS Class_ID(0x65486584,0x8425554e)`
- L68 _macro_ `#define CORONALIGHTMATCLASS Class_ID(0x53b7717a,0x500d5093)`
- L69 _macro_ `#define CORONAPHYSICALMTLCLASS Class_ID(0x6912ab89,0x87151720)`
- L70 _macro_ `#define PHYSICALMATCLASS Class_ID(0x3d6b1cec,0xdeadc001)`
- L74 _macro_ `#define VRAYMATCLASS Class_ID(0x37bf3f2f, 0x7034695c)`
- L75 _macro_ `#define VRAYBLENDMATCLASS Class_ID(0x3da0041b, 0xf436e31)`
- L76 _macro_ `#define VRAYLIGHTMATCLASS Class_ID(0x7ccf263e, 0x3f5b39b9)`
- L77 _macro_ `#define VRAYFASTSSSCLASS Class_ID(0x3f2c5faa, 0x750008bc)`
- L78 _macro_ `#define VRAY2SIDEDMATCLASS Class_ID(0x6066686a, 0x11731b4b)`
- L79 _macro_ `#define VRAYWRAPPERMATCLASS Class_ID(0x409517df, 0x3a5f44b6)`
- L80 _macro_ `#define VRAYOVERRIDEMATCLASS Class_ID(0x15d20e6b, 0x54e217eb)`
- L83 _macro_ `#define THEAOMNICLASS Class_ID(0x1a486759, 0x69269430)` — LIGHTS
- L84 _macro_ `#define THEASPOTCLASS Class_ID(0x6fe6bc2a, 0x4c04b705)`
- L85 _macro_ `#define THEAIESCLASS Class_ID(0x29b64382, 0x31882eb0)`
- L86 _macro_ `#define THEAPLANECLASS Class_ID(0x7c40f14e, 0x172d9b94)`
- L87 _macro_ `#define REGULARSPOTACLASS Class_ID(0x1012, 0x0)`
- L88 _macro_ `#define REGULARSPOTBCLASS Class_ID(0x1014, 0x0)`
- L89 _macro_ `#define REGULARDIRECTACLASS Class_ID(0x1013, 0x0)`
- L90 _macro_ `#define REGULARDIRECTBCLASS Class_ID(0x1015, 0x0)`
- L91 _macro_ `#define REGULAROMNICLASS Class_ID(0x1011, 0x0)`
- L92 _macro_ `#define PHOTOPLANEACLASS Class_ID(0x36507d92, 0x105a1a47)`
- L93 _macro_ `#define PHOTOPLANEBCLASS Class_ID(0x71794f9d, 0x70ae52f2)`
- L94 _macro_ `#define VRAYLIGHTIESCLASS Class_ID(0x2EAF2F07, 0x7EC44F31)`
- L95 _macro_ `#define VRAYLIGHTCLASS Class_ID(0x3C5575A1, 0x5FD602DF)`
- L96 _macro_ `#define VRAYSUNCLASS Class_ID(0x732c0383, 0x7d993776)`
- L97 _macro_ `#define SUNLIGHTACLASS Class_ID(0x23fe7f4f, 0x6cf2fe9)`
- L98 _macro_ `#define SUNLIGHTBCLASS Class_ID(0x71503bbb, 0x25e21124)`
- L99 _macro_ `#define SUNPOSITIONERCLASS Class_ID(0x27fe329c, 0x716f5b25)`
- L102 _macro_ `#define CORONASUNCLASS Class_ID(0x7c3a3c80, 0x294c5879)`
- L103 _macro_ `#define CORONASUNCLASSB Class_ID(0x7c3a3c80, 0x9cf576f)`
- L104 _macro_ `#define CORONALIGHTCLASS Class_ID(0x423045e5, 0x294c5879)`
- L105 _macro_ `#define ARNOLDLIGHTCLASS Class_ID(0x6705f00d, 0xca131d05)`
- L106 _macro_ `#define MRPORTALLIGHTCLASS Class_ID(0x335c655c, 0x382151b1)`
- L108 _macro_ `#define DAYLIGHTASSEMBLYCLASS Class_ID(0x4a1e6deb, 0x31c77d57)`
- L109 _macro_ `#define SKYLIGHTCLASS Class_ID(0x7bf61478, 0x522e4705)`
- L110 _macro_ `#define IESSKYLIGHTCLASS Class_ID(0x4b241b11, 0x64e8527d)`
- L111 _macro_ `#define MRSKYLIGHTCLASS Class_ID(0x26ee3350, 0x799b5b56)`
- L115 _macro_ `#define VRAYPROXY_CLASS_ID Class_ID(0x6CF53873, 0x1FF85498)` — SPECIAL CASE GEOMETRIES
- L116 _macro_ `#define VRAYPLANE_CLASS_ID Class_ID(0x628140F6, 0x3BDB0E0C)`
- L117 _macro_ `#define VRAYFUR_CLASS_ID Class_ID(0x527763C6, 0x26B35193)`
- L118 _macro_ `#define VRAYSPHERE_CLASS_ID Class_ID(0xF7B1CAC, 0x1DF87067)`
- L119 _macro_ `#define MENTALPROXY_CLASS_ID Class_ID(0x2E013BD5, 0x13C00AFB)`
- L120 _macro_ `#define ITOOFOREST_CLASS_ID Class_ID(0x79fE41C2, 0x1D7B4FB1)`
- L121 _macro_ `#define RAILCLONE_CLASS_ID Class_ID(0x39712DEF, 0x10A72959)`
- L122 _macro_ `#define PFLOWEVENT_CLASS_ID Class_ID(0X74F93B02, 0x1EB34300)`
- L123 _macro_ `#define PFLOWVIEW_CLASS_ID Class_ID(0X74F93B07, 0x1EB34300)`
- L124 _macro_ `#define THEAPROXY_CLASS_ID Class_ID(0x600846F6, 0x1D8C7F97)`
- L125 _macro_ `#define POPULATE_CLASS_ID Class_ID(0x418219c7, 0x180f6d1e)`
- L126 _macro_ `#define BODYOBJECT_CLASS_ID Class_ID(0x25292BC6, 0x17f40588)`
- L130 _macro_ `#define PHYSICAL_CRTL_CLASSID Class_ID(0x27964a9b, 0x2ea5376a)` — EXPOSURE CONTROLS
- L131 _macro_ `#define VRAY_CRTL_CLASSID Class_ID(0x565a20b6, 0x10480513)`
- L132 _macro_ `#define MR_CRTL_CLASSID Class_ID(0x73317331, 0x49154663)`
- L135 _macro_ `#define PHYSICALCAMERA_CLASS Class_ID(0x46697218, 0x28e8008d) // MaxSDK::IPhysicalCamera::GetClassID() isn't supported in Max 2016` — CAMERAS
- L136 _macro_ `#define VRAY_PHYSICALCAMERA_CLASS Class_ID(0x405e3fee, 0x4f6513be)`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxConverters.h` (Public)


#### class `DatasmithMaxDirectLink::FNodeConverted`  
`class FNodeConverted: FNoncopyable`  
_L26-31_
- inherits: `FNoncopyable`
- desc: Identifies data for Max node converted to Datasmith
- L29 _public member_ `TSharedPtr<IDatasmithActorElement> DatasmithActorElement;`
- L30 _public member_ `TSharedPtr<IDatasmithMeshActorElement> DatasmithMeshActor;`

#### class `DatasmithMaxDirectLink::FMeshConverted`  
`class FMeshConverted`  
_L33-52_
- L36 _public member_ `TSharedPtr<IDatasmithMeshElement> DatasmithMeshElement;`
- L38 _public function_ `[[nodiscard]] TSharedPtr<IDatasmithMeshElement> GetDatasmithMeshElement() const`
- L43 _public member_ `TSet<uint16> SupportedChannels;`
- L44 _public member_ `TMap<int32, int32> UVChannelsMap;`
- L46 _public function_ `void ReleaseMeshConverted()`

#### class `DatasmithMaxDirectLink::FNodeConverter`  
`class FNodeConverter: FNoncopyable`  
_L54-78_
- inherits: `FNoncopyable`
- L67 _public function_ `FNodeConverter(EType InConverterType=EType::Unknown): ConverterType(InConverterType)`
- L71 _public function_ `virtual ~FNodeConverter()`
- L73 _public prototype_ `virtual void Parse(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) = 0;`
- L74 _public prototype_ `virtual void ConvertToDatasmith(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) = 0;`
- L75 _public prototype_ `virtual void RemoveFromTracked(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) = 0;`
- L77 _public member_ `const EType ConverterType;`

#### enum `DatasmithMaxDirectLink::FNodeConverter::EType`  
`enum EType`  
_L57-65_
- L59 _public enumerator_ `Unknown`
- L60 _public enumerator_ `MeshNode`
- L61 _public enumerator_ `HismNode`
- L62 _public enumerator_ `LightNode`
- L63 _public enumerator_ `CameraNode`
- L64 _public enumerator_ `HelperNode`

#### class `DatasmithMaxDirectLink::FMeshNodeConverter`  
`class FMeshNodeConverter: public FNodeConverter`  
_L80-92_
- inherits: `FNodeConverter`
- L83 _public function_ `FMeshNodeConverter(): FNodeConverter(EType::MeshNode)`
- L86 _public prototype_ `virtual void Parse(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L87 _public prototype_ `virtual void ConvertToDatasmith(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L88 _public prototype_ `virtual void RemoveFromTracked(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L90 _public member_ `AnimHandle InstanceHandle = 0;` — todo: rename - this is handle for object this node is instance of
- L91 _public member_ `bool bMaterialsAssignedToStaticMesh;` — This node will used materials assigned to static mesh, otherwise actor's override

#### class `DatasmithMaxDirectLink::FHismNodeConverter`  
`class FHismNodeConverter: public FNodeConverter`  
_L94-103_
- inherits: `FNodeConverter`
- L97 _public function_ `FHismNodeConverter(): FNodeConverter(EType::HismNode)`
- L100 _public prototype_ `virtual void RemoveFromTracked(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L102 _public member_ `TArray<FMeshConverted> Meshes;`

#### class `DatasmithMaxDirectLink::FRailCloneNodeConverter`  
`class FRailCloneNodeConverter: public FHismNodeConverter`  
_L105-110_
- inherits: `FHismNodeConverter`
- L108 _public prototype_ `virtual void Parse(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L109 _public prototype_ `virtual void ConvertToDatasmith(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`

#### class `DatasmithMaxDirectLink::FForestNodeConverter`  
`class FForestNodeConverter: public FHismNodeConverter`  
_L112-117_
- inherits: `FHismNodeConverter`
- L115 _public prototype_ `virtual void Parse(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L116 _public prototype_ `virtual void ConvertToDatasmith(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`

#### class `DatasmithMaxDirectLink::FHelperNodeConverter`  
`class FHelperNodeConverter: public FNodeConverter`  
_L119-129_
- inherits: `FNodeConverter`
- L122 _public function_ `FHelperNodeConverter(): FNodeConverter(EType::HelperNode)`
- L126 _public prototype_ `virtual void Parse(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L127 _public prototype_ `virtual void ConvertToDatasmith(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L128 _public prototype_ `virtual void RemoveFromTracked(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`

#### class `DatasmithMaxDirectLink::FLightNodeConverter`  
`class FLightNodeConverter: public FNodeConverter`  
_L131-149_
- inherits: `FNodeConverter`
- L134 _public function_ `FLightNodeConverter(): FNodeConverter(EType::LightNode)`
- L138 _public prototype_ `virtual void Parse(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L139 _public prototype_ `virtual void ConvertToDatasmith(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L140 _public prototype_ `virtual void RemoveFromTracked(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L142 _public prototype_ `void ApplyIesProfile(const TCHAR* InIesFilePath);`
- L143 _public prototype_ `const TCHAR* GetIesProfile();`
- L144 _public prototype_ `bool IsIesProfileValid();`
- L147 _private member_ `FString IesFilePath;`

#### class `DatasmithMaxDirectLink::FCameraNodeConverter`  
`class FCameraNodeConverter: public FNodeConverter`  
_L151-160_
- inherits: `FNodeConverter`
- L154 _public function_ `FCameraNodeConverter(): FNodeConverter(EType::CameraNode)`
- L157 _public prototype_ `virtual void Parse(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L158 _public prototype_ `virtual void ConvertToDatasmith(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`
- L159 _public prototype_ `virtual void RemoveFromTracked(ISceneTracker& SceneTracker, FNodeTracker& NodeTracker) override;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace DatasmithMaxDirectLink`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxDirectLink.h` (Public)


#### class `DatasmithMaxDirectLink::IPersistentExportOptions`  
`class IPersistentExportOptions`  
_L50-68_
- desc: Global export options, stored in preferences
- L55 _public prototype_ `virtual void SetAnimatedTransforms(bool) = 0;` — Whether to export animation or not
- L56 _public prototype_ `virtual bool GetAnimatedTransforms() = 0;`
- L59 _public prototype_ `virtual void SetStatSync(bool) = 0;` — Whether to output export statistics to listener/log
- L60 _public prototype_ `virtual bool GetStatSync() = 0;`
- L62 _public prototype_ `virtual void SetTextureResolution(int32 Bool) = 0;`
- L63 _public prototype_ `virtual int32 GetTextureResolution() = 0;`
- L65 _public prototype_ `virtual void SetXRefScenes(bool) = 0;`
- L66 _public prototype_ `virtual bool GetXRefScenes() = 0;`

#### class `DatasmithMaxDirectLink::IExporter`  
`class IExporter`  
_L71-102_
- desc: Main class for export/change tracking
- L74 _public function_ `virtual ~IExporter()`
- L76 _public prototype_ `virtual void Shutdown() = 0;`
- L78 _public prototype_ `virtual void SetOutputPath(const TCHAR* Path) = 0;`
- L79 _public prototype_ `virtual void SetName(const TCHAR* Name) = 0;`
- L81 _public prototype_ `virtual ISceneTracker& GetSceneTracker() = 0;`
- L83 _public prototype_ `virtual void InitializeScene() = 0;`
- L86 _public prototype_ `virtual bool UpdateScene(bool bQuiet) = 0;` — Scene update
- L88 _public prototype_ `virtual void ResetSceneTracking() = 0;`
- L91 _public prototype_ `virtual void StartSceneChangeTracking() = 0;` — ChangeTracking
- L94 _public prototype_ `virtual void InitializeDirectLinkForScene() = 0;` — DirectLink
- L95 _public prototype_ `virtual void UpdateDirectLinkScene() = 0;`
- L96 _public prototype_ `virtual bool ToggleAutoSync() = 0;`
- L97 _public prototype_ `virtual bool IsAutoSyncEnabled() = 0;`
- L98 _public prototype_ `virtual void SetAutoSyncDelay(float Seconds) = 0;`
- L99 _public prototype_ `virtual void SetAutoSyncIdleDelay(float Seconds) = 0;`
- L101 _public prototype_ `virtual void PerformSync(bool bQuiet) = 0;`

#### struct `DatasmithMaxDirectLink::FXRefScene`  
`struct FXRefScene`  
_L119-125_
- L121 _public member_ `INode* Tree = nullptr;`
- L122 _public member_ `int32 XRefFileIndex = -1;`
- L124 _public function_ `operator bool()`

#### struct `DatasmithMaxDirectLink::FSyncPoint`  
`struct FSyncPoint`  
_L128-131_
- desc: Incapsulating time slider value to distinguish usage of TimeValue specifically for point on timeslider where we syncing
- L130 _public member_ `TimeValue Time;`

#### struct `DatasmithMaxDirectLink::FValidity`  
`struct FValidity`  
_L134-197_
- desc: Incapsulating time interval value to distinguish usage of Interval specifically for validity of synced entity
- L136 _public function_ `explicit FValidity()`
- L141 _public function_ `bool IsInvalidated() const`
- L146 _public function_ `void SetValid()`
- L151 _public function_ `void Invalidate()`
- L157 _public function_ `bool IsValidForSyncPoint(const FSyncPoint& State) const`
- L163 _public function_ `void ResetValidityInterval()` — Maximize validity interval before updating invalidated
- L170 _public function_ `void NarrowValidityToInterval(const Interval& InValidityInterval)` — Intersect current validity interval with the param
- L175 _public function_ `void NarrowValidityToInterval(const FValidity& Validity)`
- L185 _public function_ `bool Overlaps(const FValidity& Validity) const` — This Validity contains another validity interval fully. Used to determine if this validity doesn't need to be updated @return True is this validity doesn't need to be updated
- L191 _private member_ `Interval ValidityInterval;`
- L196 _private member_ `bool bIsInvalidated;` — todo: this flag indicates that ValidityInterval is determined to be recalculated this is done in order to distinguish from Empty Interval that might happen somehow when updated Until ValidityInterval is recalculated bIsInvalidated stays - this supports cancelling Update at any point. So on the next Update nodes with bIsInvalidated are updated(again, if their update wasn't finished)

#### class `DatasmithMaxDirectLink::FNodeTracker`  
`class FNodeTracker: FNoncopyable`  
_L206-308_
- inherits: `FNoncopyable`
- desc: Identifies Max node to track its changes, including tracked dependencies
- L209 _public function_ `explicit FNodeTracker(FNodeKey InNodeKey, INode* InNode) : NodeKey(InNodeKey), Node(InNode)`
- L211 _public function_ `void SetXRefIndex(FXRefScene InXRefScene)`
- L216 _public function_ `INode* GetXRefParent()`
- L222 _public function_ `FNodeConverted& CreateConverted()`
- L229 _public function_ `FNodeConverted& GetConverted()`
- L235 _public function_ `bool HasConverted()`
- L240 _public function_ `void ReleaseConverted()`
- L246 _public function_ `template<typename ConverterType> ConverterType& CreateConverter()`
- L254 _public function_ `FNodeConverter& GetConverter()`
- L260 _public function_ `bool HasConverter()`
- L265 _public function_ `FNodeConverter::EType GetConverterType()`
- L274 _public function_ `void ReleaseConverter()`
- L280 _public member_ `FNodeKey NodeKey;` — Node entity identification data
- L281 _public member_ `INode* const Node;`
- L288 _public member_ `FXRefScene XRefScene;` — Keep root node and xref index when this node is a direct child of an XRef scene This is needed to retrieve parent node(e.g. when updated) Keeping parent node itself doesn't work - it can change and the only way to get it when it's changed is to call INode::GetXRefParent
- L289 _public member_ `FString Name;`
- L292 _public member_ `bool bParsed = false;` — Node validity
- L293 _public member_ `bool bDeleted = false;`
- L294 _public member_ `FValidity Validity;`
- L295 _public member_ `FValidity SubtreeValidity;`
- L298 _public member_ `FNodeTracker* Collision = nullptr;` — Other related tracked entities
- L299 _public member_ `FLayerTracker* Layer = nullptr;`
- L300 _public member_ `TSet<class FMaterialTracker*> MaterialTrackers;`
- L305 _public member_ `TUniquePtr<FNodeConverted> Converted = nullptr;` — Datasmith element that this Node is converted to
- L307 _public member_ `TUniquePtr<FNodeConverter> Converter = nullptr;` — Converter for specific Max object type

#### class `DatasmithMaxDirectLink::FMeshConverterSource`  
`class FMeshConverterSource`  
_L310-340_
- L317 _public member_ `INode* Node;` — Node this mesh instantiates. When this is a 'regular' node it's  just instantiates mesh for Params but it's possible that this Node wants mesh to be bounding-box(when DatasmithAttributes spicifies it)
- L320 _public member_ `FString MeshName;` — Suggested Mesh name
- L323 _public member_ `GeomUtils::FRenderMeshForConversion RenderMesh;` — Extracted render mesh
- L326 _public member_ `bool bConsolidateMaterialIds;` — Whether to join all materials id into single material slot for render mesh (used when a geometry doesn't have a multimaterial assigned)
- L328 _public member_ `GeomUtils::FRenderMeshForConversion CollisionMesh;`
- L330 _public function_ `Interval GetValidityInterval()`
- L336 _public function_ `bool IsValid()` — Whether this will make a mesh

#### struct `DatasmithMaxDirectLink::FSceneUpdateStats`  
`struct FSceneUpdateStats`  
_L344-387_
- L346 _public function_ `void Reset()`
- L352 _public member_ `int32 ParseSceneXRefFileEncountered = 0;` — Explicitly initialize every stat
- L353 _public member_ `int32 ParseSceneXRefFileDisabled = 0;`
- L354 _public member_ `int32 ParseSceneXRefFileMissing = 0;`
- L355 _public member_ `int32 ParseSceneXRefFileToParse = 0;`
- L356 _public member_ `int32 ParseNodeNodesEncountered = 0;`
- L357 _public member_ `int32 RemoveDeletedNodesNodes = 0;`
- L358 _public member_ `int32 RefreshCollisionsChangedNodes = 0;`
- L359 _public member_ `int32 UpdateNodeNodesUpdated = 0;`
- L360 _public member_ `int32 UpdateNodeSkippedAsCollisionNode = 0;`
- L361 _public member_ `int32 UpdateNodeSkippedAsHiddenNode = 0;`
- L362 _public member_ `int32 UpdateNodeSkippedAsUnselected = 0;`
- L363 _public member_ `int32 UpdateNodeGeomObjEncontered = 0;`
- L364 _public member_ `int32 UpdateNodeHelpersEncontered = 0;`
- L365 _public member_ `int32 UpdateNodeCamerasEncontered = 0;`
- L366 _public member_ `int32 UpdateNodeLightsEncontered = 0;`
- L367 _public member_ `int32 UpdateNodeLightsSkippedAsUnknown = 0;`
- L368 _public member_ `int32 UpdateNodeGeomObjSkippedAsNonRenderable = 0;`
- L369 _public member_ `int32 UpdateNodeGeomObjConverted = 0;`
- L370 _public member_ `int32 ReparentActorsSkippedWithoutDatasmithActor = 0;`
- L371 _public member_ `int32 ReparentActorsAttached = 0;`
- L372 _public member_ `int32 ReparentActorsAttachedToRoot = 0;`
- L373 _public member_ `int32 ProcessInvalidatedMaterialsInvalidated = 0;`
- L374 _public member_ `int32 ProcessInvalidatedMaterialsActualToUpdate = 0;`
- L375 _public member_ `int32 UpdateMaterialsTotal = 0;`
- L376 _public member_ `int32 UpdateMaterialsSkippedAsAlreadyConverted =0;`
- L377 _public member_ `int32 UpdateMaterialsConverted = 0;`
- L378 _public member_ `int32 UpdateTexturesTotal = 0;`
- L379 _public member_ `int32 CheckTimeSliderTotalChecks = 0;`
- L380 _public member_ `int32 CheckTimeSliderSkippedAsAlreadyInvalidated = 0;`
- L381 _public member_ `int32 CheckTimeSliderSkippedAsSubtreeValid = 0;`
- L382 _public member_ `int32 CheckTimeSliderInvalidated = 0;`
- L383 _public member_ `int32 ConvertNodesConverted = 0;`
- L384 _public member_ `int32 UpdateInstancesGeometryUpdated = 0;`
- L385 _public member_ `int32 UpdateTexturesBaked = 0;`
- L386 _public member_ `int64 UpdateTexturesBakedPixels = 0;`

#### class `DatasmithMaxDirectLink::ISceneTracker`  
`class ISceneTracker`  
_L398-451_
- desc: Modifies Datasmith scene in responce to change notification calls Subscription to various Max notification systems is done separately, see  FNotifications
- L401 _public function_ `virtual ~ISceneTracker()`
- L404 _public prototype_ `virtual void NodeAdded(INode* Node) = 0;` — Change notifications
- L405 _public prototype_ `virtual void NodeDeleted(INode* Node) = 0;`
- L406 _public prototype_ `virtual void NodeGeometryChanged(INode* Node) = 0;`
- L407 _public prototype_ `virtual void NodeHideChanged(INode* Node) = 0;`
- L408 _public prototype_ `virtual void NodeNameChanged(FNodeKey NodeKey) = 0;`
- L409 _public prototype_ `virtual void NodePropertiesChanged(INode* Node) = 0;`
- L410 _public prototype_ `virtual void NodeLinkChanged(FNodeKey NodeKey) = 0;`
- L411 _public prototype_ `virtual void NodeTransformChanged(INode* Node) = 0;`
- L412 _public prototype_ `virtual void NodeMaterialAssignmentChanged(FNodeKey NodeKey) = 0;`
- L413 _public prototype_ `virtual void NodeMaterialAssignmentChanged(INode* Node) = 0;`
- L414 _public prototype_ `virtual void NodeMaterialGraphModified(FNodeKey NodeKey) = 0;`
- L415 _public prototype_ `virtual void NodeMaterialGraphModified(INode* NodeKey) = 0;`
- L417 _public prototype_ `virtual void MaterialGraphModified(Mtl* Material) = 0;`
- L419 _public prototype_ `virtual void HideByCategoryChanged() = 0;`
- L421 _public prototype_ `virtual bool IsUpdateInProgress() = 0;`
- L424 _public prototype_ `virtual void AddMeshElement(TSharedPtr<IDatasmithMeshElement>& Mesh, FDatasmithMesh& DatasmithMesh, FDatasmithMesh* CollisionMesh) = 0;` — Scene modification
- L425 _public prototype_ `virtual void ReleaseMeshElement(FMeshConverted& Converted) = 0;`
- L426 _public prototype_ `virtual void SetupActor(FNodeTracker& NodeTracker) = 0;`
- L427 _public prototype_ `virtual void SetupDatasmithHISMForNode(FNodeTracker& NodeTracker, FMeshConverterSource& MeshSource, Mtl* Material, int32 MeshIndex, const TArray<Matrix3>& Transforms) = 0;`
- L428 _public prototype_ `virtual void RemoveMaterial(const TSharedPtr<IDatasmithBaseMaterialElement>& DatasmithMaterial) = 0;`
- L429 _public prototype_ `virtual void RemoveTexture(const TSharedPtr<IDatasmithTextureElement>&) = 0;`
- L430 _public prototype_ `virtual void NodeXRefMerged(INode* Node) = 0;`
- L431 _public prototype_ `virtual void RemapConvertedMaterialUVChannels(Mtl* ActualMaterial, const TSharedPtr<IDatasmithBaseMaterialElement>& DatasmithMaterial) = 0;`
- L434 _public member_ `FSyncPoint CurrentSyncPoint;` — Sync/Update
- L436 _public prototype_ `virtual void AddGeometryNodeInstance(FNodeTracker& NodeTracker, FMeshNodeConverter& MeshConverter, Object* Obj) = 0;`
- L437 _public prototype_ `virtual void RemoveGeometryNodeInstance(FNodeTracker& NodeTracker) = 0;`
- L438 _public prototype_ `virtual void ConvertGeometryNodeToDatasmith(FNodeTracker& NodeTracker, FMeshNodeConverter& MeshConverter) = 0;`
- L440 _public prototype_ `virtual void UnregisterNodeForMaterial(FNodeTracker& NodeTracker) = 0;`
- L442 _public prototype_ `virtual const TCHAR* AcquireIesTexture(const FString& IesFilePath) = 0;`
- L443 _public prototype_ `virtual void ReleaseIesTexture(const FString& IesFilePath) = 0;`
- L445 _public prototype_ `virtual TSharedRef<IDatasmithScene> GetDatasmithSceneRef() = 0;`
- L446 _public prototype_ `virtual const TCHAR* GetAssetsOutputPath() = 0;`
- L449 _public prototype_ `virtual FNodeTracker* GetNodeTrackerByNodeName(const TCHAR* Name) = 0;` — Utility
- L450 _public prototype_ `virtual FSceneUpdateStats& GetStats() = 0;`

#### struct `DatasmithMaxDirectLink::MeshConversionParams`  
`struct MeshConversionParams`  
_L454-464_
- desc: Input data for mesh conversion
- L457 _public member_ `INode* Node;` — Node, this geom object created from
- L460 _public member_ `const GeomUtils::FRenderMeshForConversion& RenderMesh;` — Extracted render mesh
- L463 _public member_ `bool bConsolidateMaterialIds;` — Whether to join all materials id into single material slot (used when a geometry doesn't have a multimaterial assigned)

#### class `DatasmithMaxDirectLink::FDatasmithMeshConverter`  
`class FDatasmithMeshConverter`  
_L467-481_
- desc: Holds all the data to export mesh to DatasmithMeshElement
- L470 _public prototype_ `FMD5Hash ComputeHash();`
- L472 _public member_ `FDatasmithMesh RenderMesh;`
- L473 _public member_ `TSet<uint16> SupportedChannels;`
- L474 _public member_ `TMap<int32, int32> UVChannelsMap;`
- L475 _public member_ `int32 SelectedLightmapUVChannel = -1;`
- L477 _public member_ `FDatasmithMesh CollisionMesh;`
- L478 _public member_ `bool bHasCollision = false;`
- L480 _public member_ `FMeshConverted Converted;`

#### class `DatasmithMaxDirectLink::FNotifications`  
`class FNotifications`  
_L495-523_
- L499 _public prototype_ `FNotifications(IExporter& InExporter);`
- L500 _public prototype_ `~FNotifications();`
- L502 _public prototype_ `void RegisterForSystemNotifications();`
- L504 _public prototype_ `void StartSceneChangeTracking();`
- L505 _public prototype_ `void StopSceneChangeTracking();`
- L507 _public prototype_ `void AddNode(INode*);`
- L508 _public prototype_ `void AddMaterial(Mtl*);`
- L510 _public prototype_ `FString ConvertNotificationCodeToString(int code);`
- L511 _public prototype_ `void PrepareForUpdate();`
- L513 _public prototype_ `static void On3dsMaxNotification(void* param, NotifyInfo* info);`
- L515 _public member_ `bool bSceneChangeTracking = false;`
- L517 _public member_ `IExporter& Exporter;`
- L518 _public member_ `TMap<int, FString> NotificationCodetoString;` — todo: remove, just for debug to output strings for notification codes
- L519 _public member_ `TArray<int> NotificationCodesRegistered;`
- L520 _public member_ `TUniquePtr<FNodeEventCallback> NodeEventCallback;`
- L521 _public member_ `TUniquePtr<FNodeObserver> NodeObserver;`
- L522 _public member_ `TUniquePtr<FMaterialObserver> MaterialObserver;`

#### class `DatasmithMaxDirectLink::FDatasmithConverter`  
`class FDatasmithConverter`  
_L526-570_
- L529 _public member_ `const float UnitToCentimeter;`
- L531 _public prototype_ `FDatasmithConverter();`
- L533 _public function_ `FVector toDatasmithVector(Point3 Point) const`
- L540 _public function_ `FVector toDatasmithNormal(Point3 Point) const`
- L545 _public function_ `FColor toDatasmithColor(Point3& Point)`
- L551 _public function_ `void MaxToUnrealCoordinates(Matrix3 Matrix, FVector& Translation, FQuat& Rotation, FVector& Scale)`

#### class `DatasmithMaxDirectLink::FMaterialTracker`  
`class FMaterialTracker`  
_L573-612_
- desc: Material change tracking
- L576 _public function_ `explicit FMaterialTracker(Mtl* InMaterial) : Material(InMaterial)`
- L579 _public member_ `Mtl* Material;`
- L582 _public member_ `TArray<Mtl*> Materials;` — Actual materials used for this assigned material
- L583 _public member_ `TArray<Texmap*> Textures;`
- L585 _public member_ `bool bInvalidated = true;`
- L587 _public function_ `TArray<Mtl*>& GetActualMaterials()`
- L592 _public function_ `TArray<Texmap*>& GetActualTexmaps()`
- L597 _public function_ `void ResetActualMaterialAndTextures()`
- L603 _public function_ `void AddActualMaterial(Mtl* ActualMaterial)`
- L608 _public function_ `void AddActualTexture(Texmap* Texture)`

#### class `DatasmithMaxDirectLink::FMaterialTrackerHandle`  
`class FMaterialTrackerHandle`  
_L614-632_
- L618 _public function_ `explicit FMaterialTrackerHandle(Mtl* InMaterial) : Impl(MakeShared<FMaterialTracker>(InMaterial))`
- L620 _public function_ `FMaterialTracker* GetMaterialTracker()`
- L626 _private member_ `TSharedPtr<FMaterialTracker> Impl;` — todo: reuse material tracker objects(e.g. make a pool)
- L628 _private function_ `FMaterialTracker& GetImpl()`

#### class `DatasmithMaxDirectLink::ITexmapToTextureElementConverter`  
`class ITexmapToTextureElementConverter`  
_L639-646_
- desc: Converts texmap to texture element This is different from IDatasmithMaxTexmapToUEPbr which performs texmap conversion to full MaterialExpression which is used in material graph IDatasmithMaxTexmapToUEPbr uses ToTextureElementConverter when it needs a texture element
- L642 _public function_ `virtual ~ITexmapToTextureElementConverter()`
- L643 _public prototype_ `virtual TSharedPtr<IDatasmithTextureElement> Convert(FMaterialsCollectionTracker& MaterialsTracker, const FString& ActualBitmapName) = 0;`
- L645 _public member_ `FString TextureElementName;`

#### class `DatasmithMaxDirectLink::FMaterialsCollectionTracker`  
`class FMaterialsCollectionTracker`  
_L648-762_
- L652 _public function_ `FMaterialsCollectionTracker(ISceneTracker& InSceneTracker) : SceneTracker(InSceneTracker), Stats(InSceneTracker.GetStats())`
- L654 _public prototype_ `void Reset();`
- L657 _public prototype_ `FMaterialTracker* AddMaterial(Mtl* Material);` — Add material to track its changes
- L659 _public prototype_ `void ReleaseMaterial(FMaterialTracker& MaterialTracker);` — When Material is not used in scene anymore - stop tracking it
- L661 _public prototype_ `void InvalidateMaterial(Mtl* Material);` — Mark changed
- L663 _public prototype_ `void UpdateMaterial(FMaterialTracker* MaterialTracker);` — Reparse source material
- L665 _public prototype_ `void ConvertMaterial(Mtl* Material, TSharedRef<IDatasmithScene> DatasmithScene, const TCHAR* AssetsPath, TSet<Texmap*>& TexmapsConverted);` — Convert to Datasmith
- L668 _public prototype_ `void RemoveConvertedMaterial(FMaterialTracker& MaterialTracker);` — Clean all converted data, remove from datasmith scene(e.g. before rebuilding material)
- L671 _public prototype_ `void AddActualMaterial(FMaterialTracker& MaterialTracker, Mtl* Material);` — Add material used in a specific tracked material's graph
- L673 _public prototype_ `void ReleaseActualMaterial(FMaterialTracker& MaterialTracker, Mtl* Material);` — Reverse of AddActualMaterial
- L676 _public prototype_ `const TCHAR* GetMaterialName(Mtl* SubMaterial);` — Get name used for Datasmith material. Datasmith material names must be unique(used to identify elements)
- L679 _public prototype_ `bool IsMaterialUsed(Mtl* Material);` — If material is used on a mesh/actor to create a datamsith element
- L681 _public prototype_ `void SetMaterialsForMeshElement(FMeshConverted& MeshConverted, Mtl* Material);` — Set datasmith materials to Datasmith static mesh according to assigned max material
- L682 _public prototype_ `void SetMaterialsForMeshElement(const TSharedPtr<IDatasmithMeshElement>& MeshElement, Mtl* Material, const TSet<uint16>& SupportedChannels);`
- L683 _public prototype_ `void SetMaterialForMeshElement(const TSharedPtr<IDatasmithMeshElement>& MeshElement, Mtl* MaterialAssignedToNode, Mtl* ActualMaterial, uint16 SlotId);`
- L684 _public prototype_ `void UnSetMaterialsForMeshElement(const TSharedPtr<IDatasmithMeshElement>& MeshElement);`
- L686 _public prototype_ `void SetMaterialsForMeshActor(const TSharedPtr<IDatasmithMeshActorElement>& MeshActor, Mtl* Material, TSet<uint16>& SupportedChannels, const FVector3f& RandomSeed);` — Set datasmith materials for mesh actor for assigned max material
- L687 _public prototype_ `void SetMaterialForMeshActorElement(const TSharedPtr<IDatasmithMeshActorElement>& MeshActor, Mtl* MaterialAssignedToNode, Mtl* Material, int32 SlotId);`
- L688 _public prototype_ `void UnSetMaterialsForMeshActor(const TSharedPtr<IDatasmithMeshActorElement>&);`
- L691 _public prototype_ `void AddDatasmithMaterialForUsedMaterial(TSharedRef<IDatasmithScene> DatasmithScene, Mtl* Material, TSharedPtr<IDatasmithBaseMaterialElement> DatasmithMaterial);` — Record which Datasmith material was created for a Max material, not only for tracked(assigned) materials
- L692 _public prototype_ `void RemoveDatasmithMaterialForUsedMaterial(Mtl* Material);`
- L694 _public function_ `void ResetInvalidatedMaterials()`
- L699 _public function_ `TSet<FMaterialTracker*> GetInvalidatedMaterials()`
- L704 _public prototype_ `void UpdateTexmap(Texmap* Texmap);`
- L707 _public prototype_ `void AddTexmapForConversion(Texmap* Texmap, const FString& DesiredTextureElementName, const TSharedPtr<ITexmapToTextureElementConverter>& Converter);` — Adds a texmap that need to be converted to texture element
- L709 _public prototype_ `void AddTextureElement(const TSharedPtr<IDatasmithTextureElement>& );`
- L710 _public prototype_ `void RemoveTextureElement(const TSharedPtr<IDatasmithTextureElement>& TextureElement);`
- L712 _public member_ `ISceneTracker& SceneTracker;`
- L715 _public member_ `TMap<FMaterialKey, FMaterialTrackerHandle> MaterialTrackers;` — Tracks all assigned materials
- L717 _public member_ `TSet<FMaterialTracker*> InvalidatedMaterialTrackers;` — Materials needing update
- L729 _public member_ `TMap<Mtl*, TSet<FMaterialTracker*>> ActualMaterialToMaterialTracker;` — Tracked material for every Actual material (i.e. set of material which use an Mtl as a submaterial )
- L731 _public member_ `TMap<Mtl*, TSharedPtr<IDatasmithBaseMaterialElement>> UsedMaterialToDatasmithMaterial;` — All materials that have a corresponding Datasmith material created
- L734 _public member_ `TMap<Mtl*, FString> UsedMaterialToDatasmithMaterialName;` — Cached unique name for each used material for Datasmith Element
- L737 _public member_ `TMap<Mtl*, TMap<IDatasmithMeshElement*, TSet<int32>>> UsedMaterialToMeshElementSlot;` — Track materials used for static meshes
- L738 _public member_ `TMap<IDatasmithMeshElement*, TMap<Mtl*, TSet<int32>>> MeshElementToUsedMaterialSlot;`
- L741 _public member_ `TMap<Mtl*, TMap<IDatasmithMeshActorElement*, TSet<int32>>> UsedMaterialToMeshActorSlot;` — Track materials used for overrides on mesh actors
- L742 _public member_ `TMap<IDatasmithMeshActorElement*, TMap<Mtl*, TSet<int32>>> MeshActorToUsedMaterialSlot;`
- L746 _public member_ `TMap<Texmap*, TSet<FMaterialTracker*>> UsedTextureToMaterialTracker;` — Materials uses by nodes keep set of assigned textures they are used for
- L748 _public member_ `TMap<Texmap*, TSet<TSharedPtr<IDatasmithTextureElement>>> UsedTextureToDatasmithElement;` — Keep track of Datasmith Element created for texmap to simplify update/removal(no need to search DatasmithScene)
- L750 _public member_ `TMap<TSharedPtr<IDatasmithTextureElement>, TSet<Texmap*>> TextureElementToTexmap;` — Back reference - which texture elements correspond to which texmaps(different texmaps can make same element)
- L752 _public member_ `TMap<Texmap*, TSharedPtr<ITexmapToTextureElementConverter>> TexmapConverters;`
- L755 _public member_ `TMap<FString, TSharedPtr<IDatasmithTextureElement>> BitmapTextureElements;` — Bitmap textures using the same file become same texture element
- L757 _public member_ `TSet<TSharedPtr<IDatasmithTextureElement>> TextureElementsAddedToScene;`
- L759 _public member_ `FSceneUpdateStats& Stats;`
- L761 _public member_ `FDatasmithUniqueNameProvider MaterialNameProvider;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithMaxExporter, Log, All);`
- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDatasmithMaxExporter, Log, All);`
- L37 _prototype_ `void AssignMeshMaterials(TSharedPtr<IDatasmithMeshElement>&MeshElement, Mtl * Material, const TSet<uint16>&SupportedChannels);`
- L41 _namespace_ `namespace DatasmithMaxDirectLink`
- L105 _prototype_ `bool CreateExporter(bool bEnableUI, const TCHAR* EnginePath);` (scope `DatasmithMaxDirectLink`) — Create exporter with ability for DirectLink change tracking
- L106 _prototype_ `IExporter* GetExporter();` (scope `DatasmithMaxDirectLink`)
- L107 _prototype_ `void ShutdownExporter();` (scope `DatasmithMaxDirectLink`)
- L108 _prototype_ `bool Export(const TCHAR* Name, const TCHAR* OutputPath, bool bQuiet, bool bSelected);` (scope `DatasmithMaxDirectLink`)
- L109 _prototype_ `void ShutdownScripts();` (scope `DatasmithMaxDirectLink`)
- L112 _prototype_ `IPersistentExportOptions& GetPersistentExportOptions();` (scope `DatasmithMaxDirectLink`)
- L115 _typedef_ `typedef NodeEventNamespace::NodeKey FNodeKey;` (scope `DatasmithMaxDirectLink`) — Max nodes are matched by these keys
- L116 _typedef_ `typedef MtlBase* FMaterialKey;` (scope `DatasmithMaxDirectLink`)
- L389 _macro_ `#define SCENE_UPDATE_STAT_INC(Category, Name) {Stats.Category##Name++;}`
- L390 _macro_ `#define SCENE_UPDATE_STAT_SET(Category, Name, Value) Stats.Category##Name = Value`
- L391 _macro_ `#define SCENE_UPDATE_STAT_GET(Category, Name) Stats.Category##Name`
- L484 _prototype_ `bool ConvertMaxMeshToDatasmith(TimeValue CurrentTime, FMeshConverterSource& MeshSource, FDatasmithMeshConverter& MeshConverter);` (scope `DatasmithMaxDirectLink`) — Creates Mesh element and converts max mesh into it
- L486 _prototype_ `bool OpenDirectLinkUI();` (scope `DatasmithMaxDirectLink`)
- L487 _prototype_ `const TCHAR* GetDirectlinkCacheDirectory();` (scope `DatasmithMaxDirectLink`)
- L766 _prototype_ `void LogFlush();` (scope `DatasmithMaxDirectLink`)
- L768 _prototype_ `void LogError(const TCHAR* Msg);` (scope `DatasmithMaxDirectLink`)
- L769 _prototype_ `void LogWarning(const TCHAR* Msg);` (scope `DatasmithMaxDirectLink`)
- L770 _prototype_ `void LogCompletion(const TCHAR* Msg);` (scope `DatasmithMaxDirectLink`)
- L771 _prototype_ `void LogInfo(const TCHAR* Msg);` (scope `DatasmithMaxDirectLink`)
- L773 _prototype_ `void LogError(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L774 _prototype_ `void LogWarning(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L775 _prototype_ `void LogCompletion(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L776 _prototype_ `void LogInfo(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L778 _prototype_ `void LogErrorDialog(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L779 _prototype_ `void LogWarningDialog(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L780 _prototype_ `void LogCompletionDialog(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L781 _prototype_ `void LogInfoDialog(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L784 _prototype_ `void LogDebugImpl(const FString& Msg);` (scope `DatasmithMaxDirectLink`) — Debug logging
- L785 _prototype_ `void LogDebugDialog(const FString& Msg);` (scope `DatasmithMaxDirectLink`)
- L788 _macro_ `#define LOG_DEBUG_HEAVY(message) LogDebug(message)`
- L790 _macro_ `#define LOG_DEBUG_HEAVY(message)`
- L793 _prototype_ `void LogDebugNode(const FString& Name, class INode* Node);` (scope `DatasmithMaxDirectLink`)
- L794 _prototype_ `void LogNodeEvent(const MCHAR* Name, INodeEventCallback::NodeKeyTab& Nodes);` (scope `DatasmithMaxDirectLink`)
- L796 _macro_ `#define LogDebug(Msg) LogDebugImpl(Msg)`
- L798 _macro_ `#define LogDebug(Msg)`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxExporterDefines.h` (Public)


#### Free symbols / members of external scopes

- L6 _macro_ `#define IGNORE_CLANG_WARNINGS`
- L16 _macro_ `#define MAX_INCLUDES_START \`
- L30 _macro_ `#define MAX_INCLUDES_END \`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxExporterUtils.h` (Public)


#### Free symbols / members of external scopes

- L17 _namespace_ `namespace DatasmithMaxExporterUtils`
- L19 _prototype_ `void ExportMaxTagsForDatasmithActor(const TSharedPtr<IDatasmithActorElement>& ActorElement, INode* Node, INode* ParentNode, TMap<TPair<uint32, TPair<uint32, uint32>>, MAXClass*>& KnownMaxClass, TMap<uint32, MAXSuperClass*>& KnownMaxSuperClass);` (scope `DatasmithMaxExporterUtils`)

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxGeomUtils.h` (Public)


#### class `DatasmithMaxDirectLink::GeomUtils::FRenderMeshForConversion`  
`class FRenderMeshForConversion: FNoncopyable`  
_L26-125_
- inherits: `FNoncopyable`
- L29 _public function_ `explicit FRenderMeshForConversion() : Node(nullptr) , MaxMesh(nullptr) , bNeedsDelete(false) , ObjectToDelete(nullptr) , Pivot(FTransform::Identity)`
- L39 _public function_ `explicit FRenderMeshForConversion(INode* InNode, Mesh* InMaxMesh, bool bInNeedsDelete, TriObject* InObjectToDelete=nullptr) : Node(InNode) , MaxMesh(InMaxMesh) , bNeedsDelete(bInNeedsDelete) , ObjectToDelete(InObjectToDelete) , Pivot(FTransform::Identity)`
- L49 _public function_ `FRenderMeshForConversion(FRenderMeshForConversion&& Other)`
- L71 _public function_ `~FRenderMeshForConversion()`
- L83 _public function_ `bool IsValid() const`
- L88 _public function_ `INode* GetNode() const`
- L93 _public function_ `Mesh* GetMesh() const`
- L98 _public function_ `const FTransform& GetPivot() const`
- L103 _public function_ `void SetPivot(const FTransform& InPivot)`
- L108 _public function_ `void SetValidityInterval(const Interval& Interval)`
- L113 _public function_ `Interval GetValidityInterval()`
- L118 _private member_ `INode* Node;` — Scene node mesh is taken from
- L119 _private member_ `Mesh* MaxMesh;` — the 3ds Max Mesh which holds the geometry
- L120 _private member_ `bool bNeedsDelete;` — Whether Mesh lifetime is in our hands
- L121 _private member_ `TriObject* ObjectToDelete;` — When the Mesh is retrieved from some temporary TriObject this TriObject needs to be deleted(after Mesh is used)
- L123 _private member_ `FTransform Pivot;`
- L124 _private member_ `Interval ValidityInterval;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace DatasmithMaxDirectLink`
- L23 _namespace_ `namespace GeomUtils` (scope `DatasmithMaxDirectLink`)
- L127 _prototype_ `bool ConvertRailClone(DatasmithMaxDirectLink::ISceneTracker& SceneTracker, DatasmithMaxDirectLink::FNodeTracker& NodeTracker);` (scope `DatasmithMaxDirectLink::GeomUtils`)
- L128 _prototype_ `bool ConvertForest(DatasmithMaxDirectLink::ISceneTracker& Scene, DatasmithMaxDirectLink::FNodeTracker& NodeTracker);` (scope `DatasmithMaxDirectLink::GeomUtils`)
- L130 _prototype_ `FRenderMeshForConversion GetMeshForGeomObject(TimeValue CurrentTime, INode* Node, const FTransform& Pivot = FTransform::Identity);` (scope `DatasmithMaxDirectLink::GeomUtils`) — Extract mesh using already evaluated object
- L132 _prototype_ `FRenderMeshForConversion GetMeshForCollision(TimeValue CurrentTime, DatasmithMaxDirectLink::ISceneTracker& SceneTracker, INode* Node, bool bBakePivot);` (scope `DatasmithMaxDirectLink::GeomUtils`)
- L133 _prototype_ `INode* GetCollisionNode(DatasmithMaxDirectLink::ISceneTracker& SceneTracker, INode* OriginalNode, const FDatasmithMaxStaticMeshAttributes* DatasmithAttributes, bool& bOutFromDatasmithAttribute);` (scope `DatasmithMaxDirectLink::GeomUtils`)
- L135 _prototype_ `void FillDatasmithMeshFromMaxMesh(TimeValue CurrentTime, FDatasmithMesh& DatasmithMesh, Mesh& MaxMesh, INode* ExportedNode, bool bForceSingleMat, TSet<uint16>& SupportedChannels, TMap<int32, int32>& UVChannelsMap, FTransform Pivot);` (scope `DatasmithMaxDirectLink::GeomUtils`)

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxHelper.h` (Public)


#### struct `FScopedBitMapPtr`  
`struct FScopedBitMapPtr`  
_L21-32_
- desc: Helper structure to help manage loading and deleting bitmaps when we only have its BitmapInfo
- L24 _public member_ `BitmapInfo MapInfo;`
- L25 _public member_ `Bitmap* Map = nullptr;`
- L27 _public prototype_ `FScopedBitMapPtr(const BitmapInfo& InMapInfo, Bitmap* InMap);`
- L28 _public prototype_ `~FScopedBitMapPtr();`
- L31 _private member_ `bool bNeedsDelete = false;`

#### Free symbols / members of external scopes

- L17 _function_ `inline double GetSystemUnitScale(int type)`
- L35 _namespace_ `namespace DatasmithMaxHelper`
- L37 _prototype_ `void FilterInvertedScaleTransforms(const TArray<FTransform>& Transforms, TArray<FTransform>& OutNormal, TArray<FTransform>& OutInverted);` (scope `DatasmithMaxHelper`)

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxLogger.h` (Public)


#### class `DatasmithMaxLogger`  
`class DatasmithMaxLogger :public FDatasmithLogger, public TSharedFromThis<DatasmithMaxLogger>`  
_L18-58_
- inherits: `FDatasmithLogger,TSharedFromThis<DatasmithMaxLogger>`
- L21 _public prototype_ `static DatasmithMaxLogger& Get();`
- L23 _public prototype_ `void Purge();`
- L25 _public prototype_ `void AddPartialSupportedMat(Mtl* Mat);`
- L26 _public prototype_ `void AddUnsupportedMat(Mtl* Mat);`
- L27 _public prototype_ `void AddPartialSupportedMap(Texmap* Map);`
- L28 _public prototype_ `void AddUnsupportedMap(Texmap* Map);`
- L29 _public prototype_ `void AddOtherMapWarning(FString Warning);`
- L30 _public prototype_ `void AddUnsupportedLight(INode* Light);`
- L31 _public prototype_ `void AddUnsupportedUV(INode* Node);`
- L33 _public prototype_ `void AddInvalidObj(INode* Node);`
- L34 _public prototype_ `TArray<INode*>GetInvalidObjects() const;`
- L36 _public prototype_ `void AddInvalidTransform(INode* Node);`
- L38 _public prototype_ `bool HasWarnings();`
- L39 _public prototype_ `void Show(HWND hDlg);`
- L40 _public prototype_ `bool CopyToClipBoard();`
- L42 _public prototype_ `FString GetLightDescription(INode* LightNode);`
- L45 _private prototype_ `void AddItem(const TCHAR* Msg, HWND Handle, FString& FullMsg);`
- L46 _private prototype_ `void AddObjectList(TArray< INode* > ObjectList, HWND Handle, const TCHAR* Header, const TCHAR* Description = nullptr);`
- L48 _private member_ `TArray<Mtl*> PartialSupportedMats;`
- L49 _private member_ `TArray<Mtl*> UnsupportedMats;`
- L50 _private member_ `TArray<Texmap*> PartialSupportedMaps;`
- L51 _private member_ `TArray<Texmap*> UnsupportedMaps;`
- L52 _private member_ `TArray<INode*> UnsupportedLight;`
- L53 _private member_ `TArray<INode*> FailUVs;`
- L54 _private member_ `TArray<INode*> FailObjs;`
- L55 _private member_ `TArray<INode*> InvalidTransforms;`
- L57 _private member_ `FString ShowMessage;`

#### Free symbols / members of external scopes

- L60 _prototype_ `INT_PTR CALLBACK MsgListDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxMeshExporter.h` (Public)


#### struct `FMaxExportMeshArgs`  
`struct FMaxExportMeshArgs`  
_L18-34_
- L20 _public member_ `bool bForceSingleMat = false;`
- L21 _public member_ `INode* Node = nullptr;`
- L24 _public member_ `Mesh* MaxMesh = nullptr;` — Pass along a mesh if the mesh can't be simply extracted from the node
- L26 _public member_ `const FDatasmithMaxStaticMeshAttributes* DatasmithAttributes;`
- L28 _public member_ `const TCHAR* ExportPath = nullptr;`
- L29 _public member_ `const TCHAR* ExportName = nullptr;`
- L31 _public member_ `float UnitMultiplier = 1.f;`
- L32 _public member_ `FTransform Pivot = FTransform::Identity;`
- L33 _public member_ `bool bBakePivot = true;`

#### class `FDatasmithMaxMeshExporter`  
`class FDatasmithMaxMeshExporter`  
_L36-104_
- L39 _public prototype_ `FDatasmithMaxMeshExporter();`
- L40 _public prototype_ `~FDatasmithMaxMeshExporter();`
- L42 _public prototype_ `bool CalcSupportedChannelsOnly(INode* Node, TSet<uint16>& SupportedChannels, bool bForceSingleMat) const;`
- L45 _public prototype_ `TSharedPtr< IDatasmithMeshElement > ExportMesh(FMaxExportMeshArgs& ExportMeshArgs, TSet<uint16>& SupportedChannels, FString& Error);` — export unreal mesh from actual node
- L48 _public prototype_ `TSharedPtr< IDatasmithMeshElement > ExportDummyMesh( const TCHAR* ExportPath, const TCHAR* ExportName );` — export dummy unreal mesh it could be used for helpers etc, currently a void mesh is exported
- L50 _public typedef_ `typedef TMap<int32, int32> FUVChannelsMap;`
- L51 _public prototype_ `const FUVChannelsMap& GetUVChannelsMapForMesh(const TCHAR* MeshName) const;`
- L53 _public prototype_ `static INode* GetCollisionNode(INode* OriginalNode, const FDatasmithMaxStaticMeshAttributes* DatasmithAttributes, bool& bOutFromDatasmithAttribute);`
- L66 _private prototype_ `bool CreateDatasmithMesh(FDatasmithMesh& DSMesh, FMaxExportMeshArgs& ExportMeshArgs, TSet<uint16>& SupportedChannels);` — Export a scene node to a datasmith mesh @param DSMesh	        Destination mesh @param bForceSingleMat   Ignore Material from source mesh @param ExportNode        Source scene node @param SupportedChannels @param MeshName          UVChannel name @param Pivot             Transformation to bake into the mesh
- L78 _private prototype_ `void FillDatasmithMeshFromMaxMesh(FDatasmithMesh& DatasmithMesh, Mesh& MaxMesh, INode* ExportedNode, bool bForceSingleMat, TSet<uint16>& SupportedChannels, const TCHAR* MeshName, FTransform Pivot);` — Actual data extraction from Max mesh @param DatasmithMesh      Destination mesh @param MaxMesh            Source mesh @param bForceSingleMat    Ignore Material from source mesh @param SupportedChannels @param MeshName           UVChannel name @param Pivot              Transformation to bake into the mesh
- L89 _private prototype_ `bool FillDatasmithMeshFromBoundingBox(FDatasmithMesh& DatasmithMesh, INode* ExportNode, FTransform Pivot) const;` — Fill the mesh with a bounding box @param DatasmithMesh		Destination mesh @param ExportNode		The node from which the bounding box will be made @param Pivot				Transformation to bake into the mesh @return True if the mesh was filled with a bounding box
- L92 _private prototype_ `FVector Point3ToFVector(Point3 p3) const;` — Convert Max to UE axis
- L95 _private prototype_ `FVector Unit3ToFVector(Point3 p3) const;` — Convert Max to UE axis, and handle scene unit scaling
- L97 _private prototype_ `MeshNormalSpec* GetSpecifiedNormalsFromMesh(Mesh* MaxMesh) const;`
- L98 _private prototype_ `INode* GetTemporalNode() const;`
- L99 _private prototype_ `bool DeleteTemporalNode() const;`
- L101 _private member_ `TMap<FString, FUVChannelsMap> MeshNamesToUVChannels;`
- L103 _private member_ `float UnitMultiplier;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxProgressManager.h` (Public)


#### class `FDatasmithMaxProgressManager`  
`class FDatasmithMaxProgressManager : public IDatasmithProgressManager`  
_L6-31_
- inherits: `IDatasmithProgressManager`
- L9 _public prototype_ `FDatasmithMaxProgressManager();`
- L13 _public prototype_ `virtual void ProgressEvent(float InProgressRatio, const TCHAR* InProgressString) override;`
- L15 _public prototype_ `void SetMainMessage(const TCHAR* InProgressMessage);`
- L17 _public function_ `void SetProgressStart(float InProgressStart)`
- L22 _public function_ `void SetProgressEnd(float InProgressEnd)`
- L28 _private member_ `float ProgressStart;`
- L29 _private member_ `float ProgressEnd;`
- L30 _private member_ `int32 ProgressBarCounter;`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxSceneExporter.h` (Public)


#### struct `FMaxLightCoordinateConversionParams`  
`struct FMaxLightCoordinateConversionParams`  
_L47-56_
- desc: Lights may have multiple default orientation depending on their shape and type. This is a structure used when converting actor's coordinate in MaxToUnrealCoordinates to make sure to apply right correction to the light objects.
- L50 _public member_ `bool bIsLight = false;`
- L51 _public member_ `bool bIsCoronaLight = false;`
- L52 _public member_ `EDatasmithLightShape LightShape = EDatasmithLightShape::None;`
- L54 _public function_ `FMaxLightCoordinateConversionParams()`
- L55 _public prototype_ `FMaxLightCoordinateConversionParams(INode* LightNode, EDatasmithLightShape Shape = EDatasmithLightShape::None);`

#### class `FDatasmithMaxSceneExporter`  
`class FDatasmithMaxSceneExporter`  
_L58-106_
- L61 _public prototype_ `static bool ExportActor(TSharedRef< IDatasmithScene > DatasmithScene, INode* Node, const TCHAR* Name, float UnitMultiplier);`
- L62 _public prototype_ `static void ExportMeshActor(TSharedRef< IDatasmithScene > DatasmithScene, TSet<uint16>& SupportedChannels, INode* Node, const TCHAR* MeshName, float UnitMultiplier, bool bPivotIsBakedInGeometry, Mtl* StaticMeshMtl, const EStaticMeshExportMode& ExportMode);`
- L64 _public prototype_ `static bool ExportCameraActor(TSharedRef< IDatasmithScene > DatasmithScene, INode* Parent, INodeTab Instances, int InstanceIndex, const TCHAR* Name, float UnitMultiplier);`
- L65 _public prototype_ `static void WriteEnvironment(TSharedRef< IDatasmithScene > DatasmithScene, bool bOnlySelection);`
- L66 _public prototype_ `static void ExportToneOperator(TSharedRef< IDatasmithScene > DatasmithScene);`
- L67 _public prototype_ `static void ExportAnimation(TSharedRef< IDatasmithLevelSequenceElement > LevelSequence, INode* ParentNode, INode* Node, const TCHAR* ActorName, float UnitMultiplier, const FMaxLightCoordinateConversionParams& LightParams = FMaxLightCoordinateConversionParams());`
- L69 _public prototype_ `static FString GetActualPath(const TCHAR* OriginalPath);`
- L71 _public prototype_ `static Mtl* GetRandomSubMaterial(Mtl* Material, FVector3f RandomSeed);`
- L81 _public prototype_ `static FTransform GetPivotTransform(INode* Node, float UnitMultiplier);` — Extract the Node to Object transform in UE coordinates @note aka. Object-Offset Transform Matrix in Autodesk language @see https://help.autodesk.com/view/3DSMAX/2018/ENU/?guid=__files_GUID_3B001F21_8FE9_4663_A972_E648682A0ACD_htm @param Node           node to extract Pivot from @param UnitMultiplier scene master scale
- L82 _public prototype_ `static void MaxToUnrealCoordinates(Matrix3 Matrix, FVector& Translation, FQuat& Rotation, FVector& Scale, float UnitMultiplier, const FMaxLightCoordinateConversionParams& LightParams = FMaxLightCoordinateConversionParams());`
- L84 _public prototype_ `static TSharedPtr< IDatasmithLightActorElement > CreateLightElementForNode(INode* Node, const TCHAR* Name);`
- L85 _public prototype_ `static bool ParseLight(DatasmithMaxDirectLink::FLightNodeConverter&, INode* Node, TSharedRef< IDatasmithLightActorElement > LightElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L87 _public prototype_ `static TSharedPtr<IDatasmithMetaDataElement> ParseUserProperties(INode* Node, TSharedRef< IDatasmithActorElement > ActorElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L91 _private prototype_ `static float GetLightPhysicalScale();` — Return the physical scale for the unitless light
- L93 _private prototype_ `static int GetSeedFromMaterial(Mtl* Material);`
- L95 _private prototype_ `static bool ParseActor(INode* Node, TSharedRef< IDatasmithActorElement > ActorElement, float UnitMultiplier, TSharedRef< IDatasmithScene > DatasmithScene);`
- L96 _private prototype_ `static bool ParseLightObject(LightObject& Light, TSharedRef< IDatasmithLightActorElement > LightElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L97 _private prototype_ `static bool ParseCoronaLight(DatasmithMaxDirectLink::FLightNodeConverter&, LightObject& Light, TSharedRef< IDatasmithAreaLightElement > AreaLightElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L98 _private prototype_ `static bool ParsePhotometricLight(DatasmithMaxDirectLink::FLightNodeConverter& Converter, LightObject& Light, TSharedRef< IDatasmithPointLightElement > PointLightElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L99 _private prototype_ `static bool ParseVRayLight(LightObject& Light, TSharedRef< IDatasmithAreaLightElement > AreaLightElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L100 _private prototype_ `static bool ParseVRayLightPortal(LightObject& Light, TSharedRef< IDatasmithLightmassPortalElement > LightPortalElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L101 _private prototype_ `static bool ParseVRayLightIES(DatasmithMaxDirectLink::FLightNodeConverter&, LightObject& Light, TSharedRef< IDatasmithPointLightElement > PointLightElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L102 _private prototype_ `static bool ParseLightParameters(DatasmithMaxDirectLink::FLightNodeConverter&, EMaxLightClass LightClass, LightObject& Light, TSharedRef< IDatasmithLightActorElement > LightElement, TSharedRef< IDatasmithScene > DatasmithScene);`
- L103 _private prototype_ `static bool ProcessLightTexture(TSharedRef< IDatasmithLightActorElement > LightElement, Texmap* LightTexture, TSharedRef< IDatasmithScene > DatasmithScene);`
- L104 _private prototype_ `static bool ParseTransformAnimation(INode* ParentNode, INode* Node, TSharedRef< IDatasmithTransformAnimationElement > AnimationElement, float UnitMultiplier, const FMaxLightCoordinateConversionParams& LightParams);`
- L105 _private prototype_ `static void ParseSun(INode* Node, TSharedRef<IDatasmithLightActorElement> LightElement);`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace DatasmithMaxDirectLink`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Public/DatasmithMaxWriter.h` (Public)


#### enum `EDSBitmapType`  
`enum class EDSBitmapType`  
_L21-48_
- L23 _public enumerator_ `NotSupported`
- L24 _public enumerator_ `RegularBitmap`
- L25 _public enumerator_ `AutodeskBitmap`
- L26 _public enumerator_ `TheaBitmap`
- L27 _public enumerator_ `CoronaBitmap`
- L28 _public enumerator_ `VRayHRDI`
- L29 _public enumerator_ `NormalMap`
- L30 _public enumerator_ `ColorCorrector`
- L31 _public enumerator_ `FallOff`
- L32 _public enumerator_ `Mix`
- L33 _public enumerator_ `Gradient`
- L34 _public enumerator_ `GradientRamp`
- L35 _public enumerator_ `Checker`
- L36 _public enumerator_ `Noise`
- L37 _public enumerator_ `Cellular`
- L38 _public enumerator_ `VRayDirt`
- L39 _public enumerator_ `VRayColor`
- L40 _public enumerator_ `CoronaColor`
- L41 _public enumerator_ `CoronaMix`
- L42 _public enumerator_ `CoronaMultiTex`
- L43 _public enumerator_ `CoronaAO`
- L44 _public enumerator_ `CompositeTex`
- L45 _public enumerator_ `PhysicalSky`
- L46 _public enumerator_ `ThirdPartyMultiTex`
- L47 _public enumerator_ `BakeableMap`

#### enum `EDSMaterialType`  
`enum class EDSMaterialType`  
_L50-75_
- L52 _public enumerator_ `NotSupported`
- L53 _public enumerator_ `TheaMaterial`
- L54 _public enumerator_ `TheaMaterialDeprecated`
- L55 _public enumerator_ `TheaBasic`
- L56 _public enumerator_ `TheaGlossy`
- L57 _public enumerator_ `TheaSSS`
- L58 _public enumerator_ `TheaFilm`
- L59 _public enumerator_ `TheaCoating`
- L60 _public enumerator_ `TheaRandom`
- L61 _public enumerator_ `MultiMat`
- L62 _public enumerator_ `StandardMat`
- L63 _public enumerator_ `BlendMat`
- L64 _public enumerator_ `XRefMat`
- L65 _public enumerator_ `ArchDesignMat`
- L66 _public enumerator_ `ShellMat`
- L67 _public enumerator_ `VRayMat`
- L68 _public enumerator_ `VRayLightMat`
- L69 _public enumerator_ `VRayBlendMat`
- L70 _public enumerator_ `VRayFastSSSMat`
- L71 _public enumerator_ `CoronaMat`
- L72 _public enumerator_ `CoronaLightMat`
- L73 _public enumerator_ `CoronaLayerMat`
- L74 _public enumerator_ `PhysicalMat`

#### class `FDatasmithMaxMatHelper`  
`class FDatasmithMaxMatHelper`  
_L77-99_
- L81 _public prototype_ `static EDSBitmapType GetTextureClass(Texmap* mTexMap);` — CLASS RELATED FUNCTIONS
- L82 _public prototype_ `static EDSMaterialType GetMaterialClass(Mtl* Material);`
- L88 _public prototype_ `static Mtl* GetRenderedXRefMaterial(Mtl* XRefMaterial);` — Gets a XRefMaterial and returns the rendered material which is either the SubMaterial or SourceMaterial depending on if the source material is overridden. @param XRefMaterial	The XRefMaterial we want the rendered material of. @return              The rendered material, can be nullptr.
- L90 _public prototype_ `static bool HasNonBakeableSubmap(Texmap* InTexmap);`
- L92 _public prototype_ `static FLinearColor MaxColorToFLinearColor(BMM_Color_fl Color, float Multiplier = 1.0f);` — todo: rename, although result type is FLinearColor this function does pow(rgb, 1/gamma), i.e. converting to gamma-space
- L93 _public prototype_ `static FLinearColor MaxLinearColorToFLinearColor(BMM_Color_fl Color, float Multiplier = 1.0f);`
- L94 _public prototype_ `static float GetBitmapGamma(BitmapTex* InBitmapTex);`
- L95 _public prototype_ `static float GetBitmapGamma(BitmapInfo* InBitmapInfo);`
- L96 _public prototype_ `static float GetVrayHdriGamma(BitmapTex* InBitmapTex);`
- L97 _public prototype_ `static bool IsSRGB(Bitmap& InBitmap);`
- L98 _public prototype_ `static bool IsSRGB(BitmapTex& InBitmapTex);`

#### class `FDatasmithMaxMatExport`  
`class FDatasmithMaxMatExport`  
_L102-114_
- desc: EXPORT FUNCTIONS THAT NEEDS TO BE CALLED FROM OTHER PARTS OF CODE
- L106 _public prototype_ `static void GetXMLTexture(TSharedRef< IDatasmithScene > DatasmithScene, Texmap* InTexmap, const TCHAR* AssetsPath, TArray<TSharedPtr< IDatasmithTextureElement >>* OutTextureElements=nullptr);` — stores the textures without allowing dupe in uniqueTextures
- L109 _public prototype_ `static TSharedPtr< IDatasmithBaseMaterialElement > ExportUniqueMaterial(TSharedRef< IDatasmithScene > DatasmithScene, Mtl* Material, const TCHAR* AssetsPath);` — Exports the given material if it hasn't been exported yet and returns the created IDatasmithBaseMaterialElement, else returns an invalid TSharedPtr.
- L110 _public prototype_ `static void WriteXMLMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement > MaterialElement, Mtl* Material);`
- L113 _private prototype_ `static bool UseFirstSubMapOnly(EDSMaterialType MaterialType, Mtl* Material);`

#### class `FDatasmithMaxMatWriter`  
`class FDatasmithMaxMatWriter`  
_L117-196_
- desc: ACTUAL EXPORT FUNCTIONS
- L121 _public member_ `static FString TextureSuffix;` — String suffix to be added to the textures identifier
- L123 _public member_ `static FString TextureBakeFormat;` — File suffix for texture bakes including its dot
- L125 _public prototype_ `static FString DumpTexture(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, const TCHAR* ColorPrefix, bool bForceInvert, bool bIsGrayscale);` — selects from any kind of texture
- L127 _public prototype_ `static FString DumpNormalTexture(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, const TCHAR* ColorPrefix, bool bForceInvert, bool bIsGrayscale);` — selects from any kind of texture
- L129 _public prototype_ `static void DumpWeightedTexture(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, BMM_Color_fl Color, float Weight, const TCHAR* Prefix, const TCHAR* ColorPrefix, bool bForceInvert, bool bIsGrayscale);` — selects from any kind of texture the texture is mixed with the given color using Weight
- L131 _public prototype_ `static void DumpWeightedColor(TSharedPtr<IDatasmithCompositeTexture>& CompTex, BMM_Color_fl ColorA, BMM_Color_fl ColorB, float Weight, const TCHAR* Prefix);` — selects from any kind of texture the ColorA is mixed with the Color B using Weight
- L133 _public prototype_ `static FString DumpColorOfTexmap(TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* ColorPrefix, const TCHAR* property);` — if we want to export sub-texture but it is void
- L138 _public prototype_ `static FString GetActualBitmapPath(BitmapTex* InBitmapTex);`
- L139 _public prototype_ `static FString GetActualBitmapPath(BitmapInfo* InBitmapInfo);`
- L140 _public prototype_ `static FString GetActualBitmapName(BitmapTex* InBitmapTex);`
- L141 _public prototype_ `static FString GetActualBitmapName(BitmapInfo* InBitmapInfo);`
- L142 _public prototype_ `static FString CropBitmap(BitmapTex* InBitmapTex);`
- L143 _public prototype_ `static FString DumpBitmap(TSharedPtr<IDatasmithCompositeTexture>& CompTex, BitmapTex* InBitmapTex, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L144 _public prototype_ `static FString DumpAutodeskBitmap(TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L145 _public prototype_ `static void ExportStandardMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L146 _public prototype_ `static void ExportBlendMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L147 _public prototype_ `static FString DumpColorCorrect(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L148 _public prototype_ `static FString DumpMix(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L149 _public prototype_ `static FString DumpCompositetex(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L150 _public prototype_ `static FString DumpFalloff(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L151 _public prototype_ `static FString DumpBakeable(TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L156 _public prototype_ `static FString DumpBitmapThea(TSharedPtr<IDatasmithCompositeTexture>& CompTex, BitmapTex* InBitmapTex, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L157 _public prototype_ `static void GetTheaTexmap(TSharedRef< IDatasmithScene > DatasmithScene, BitmapTex* InBitmapTex, TArray<TSharedPtr< IDatasmithTextureElement >>* OutTextureElements);`
- L158 _public prototype_ `static void ExportTheaSubmaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithShaderElement >& MaterialShader, Mtl* Material, EDSMaterialType MaterialType);`
- L159 _public prototype_ `static void ExportTheaMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L164 _public prototype_ `static FString DumpVrayColor(TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert);`
- L165 _public prototype_ `static FString DumpVrayHdri(TSharedPtr<IDatasmithCompositeTexture>& CompTex, BitmapTex* InBitmapTex, const TCHAR* Prefix, bool bForceInvert);`
- L166 _public prototype_ `static void ExportVRayMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L167 _public prototype_ `static void ExportVRayLightMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L168 _public prototype_ `static void ExportVrayBlendMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L169 _public prototype_ `static FString GetActualVRayBitmapName(BitmapTex* InBitmapTex);`
- L174 _public prototype_ `static void ExportArchDesignMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L179 _public prototype_ `static FString DumpBitmapCorona(TSharedPtr<IDatasmithCompositeTexture>& CompTex, BitmapTex* InBitmapTex, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L180 _public prototype_ `static FString DumpCoronaColor(TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert);`
- L181 _public prototype_ `static void GetCoronaTexmap(TSharedRef< IDatasmithScene > DatasmithScene, BitmapTex* InBitmapTex, TArray<TSharedPtr< IDatasmithTextureElement >>* OutTextureElements);`
- L182 _public prototype_ `static void ExportCoronaMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L183 _public prototype_ `static void ExportCoronaLightMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L184 _public prototype_ `static void ExportCoronaBlendMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L185 _public prototype_ `static FString DumpCoronaMix(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, bool bForceInvert, bool bIsGrayscale);`
- L186 _public prototype_ `static FString DumpCoronaMultitex(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr<IDatasmithCompositeTexture>& CompTex, Texmap* InTexmap, const TCHAR* Prefix, const TCHAR* ColorPrefix, bool bForceInvert, bool bIsGrayscale);`
- L187 _public prototype_ `static bool GetCoronaFixNormal(Texmap* InTexmap);`
- L192 _public prototype_ `static void ExportPhysicalMaterial(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L193 _public prototype_ `static void ExportPhysicalMaterialCoat(TSharedRef< IDatasmithScene > DatasmithScene, TSharedPtr< IDatasmithMaterialElement >& MaterialElement, Mtl* Material);`
- L194 _public prototype_ `static void ExportPhysicalMaterialProperty(TSharedRef< IDatasmithScene > DatasmithScene, Texmap* Texture, bool bTextureEnabled, Texmap* TextureWeight, bool bTextureWeightEnabled, BMM_Color_fl Color, float Weight, TSharedPtr<IDatasmithCompositeTexture>& CompTex, FString TextureAliasName, FString ColorAliasName, bool bForceInvert, bool bIsGrayscale);`

### `Source/Programs/Enterprise/Datasmith/DatasmithMaxExporter/Resources/Windows/resource.h` (Other)


#### Free symbols / members of external scopes

- L7 _macro_ `#define IDS_DXFEXP 1` — {{NO_DEPENDENCIES}} Microsoft Visual C++ generated include file. Used by Resource.rc
- L8 _macro_ `#define IDCOPY 4`
- L9 _macro_ `#define IDSELECTINVALID 5`
- L10 _macro_ `#define IDD_EXPORTOPTIONS 101`
- L11 _macro_ `#define IDB_BITMAP1 105`
- L12 _macro_ `#define IDI_ICON1 107`
- L13 _macro_ `#define IDI_ICONUE 107`
- L14 _macro_ `#define IDR_ACCELERATOR1 108`
- L15 _macro_ `#define IDS_SYNC_NAME 109`
- L16 _macro_ `#define IDS_SYNC_DESC 110`
- L17 _macro_ `#define IDS_CONNECTIONS_NAME 111`
- L18 _macro_ `#define IDS_CONNECTIONS_DESC 112`
- L19 _macro_ `#define IDS_AUTOSYNC_NAME 113`
- L20 _macro_ `#define IDS_AUTOSYNC_DESC 114`
- L21 _macro_ `#define IDS_EXPORT_NAME 115`
- L22 _macro_ `#define IDS_EXPORT_DESC 116`
- L23 _macro_ `#define IDS_SHOWLOG_NAME 117`
- L24 _macro_ `#define IDS_SHOWLOG_DESC 118`
- L25 _macro_ `#define IDS_DATASMITH_CATEGORY 119`
- L26 _macro_ `#define IDS_EXPORT_SELECTED_NAME 120`
- L27 _macro_ `#define IDS_EXPORT_SELECTED_DESC 121`
- L28 _macro_ `#define IDD_ERROR_MSGS 181`
- L29 _macro_ `#define IDC_BYOBJECT 1016`
- L30 _macro_ `#define IDC_BYMATERIAL 1017`
- L31 _macro_ `#define IDC_1LAYER 1018`
- L32 _macro_ `#define IDC_ACTORS 1019`
- L33 _macro_ `#define IDC_EDITPATH 1020`
- L34 _macro_ `#define IDC_CBTextures 1020`
- L35 _macro_ `#define IDC_MATERIALS 1021`
- L36 _macro_ `#define IDC_LIGHTS 1022`
- L37 _macro_ `#define IDC_GEOMETRY 1023`
- L38 _macro_ `#define IDC_LBTextures 1024`
- L39 _macro_ `#define IDC_CBColorGamma 1025`
- L40 _macro_ `#define IDC_LBColorGamma 1026`
- L41 _macro_ `#define IDC_CBLightmap 1027`
- L42 _macro_ `#define IDC_LBLightmap 1028`
- L43 _macro_ `#define IDC_CBMaxSize 1029`
- L44 _macro_ `#define IDC_LBMaxSize 1030`
- L45 _macro_ `#define IDC_CBPath 1031`
- L46 _macro_ `#define IDC_CBInclude 1031`
- L47 _macro_ `#define IDC_LBPath 1032`
- L48 _macro_ `#define IDC_LBInclude 1032`
- L49 _macro_ `#define IDC_STATIC_LOGO 1033`
- L50 _macro_ `#define IDC_LBMaxSize2 1034`
- L51 _macro_ `#define IDC_LBVersion 1034`
- L52 _macro_ `#define IDC_CHECK1 1035`
- L53 _macro_ `#define IDC_CHECKNEWVRAY 1035`
- L54 _macro_ `#define IDC_CBAnimated 1035`
- L55 _macro_ `#define IDC_LBAnimated 1036`
- L56 _macro_ `#define IDC_ERROR_MSG_LIST 1168`
- L57 _macro_ `#define IDC_STATIC -1`
- L63 _macro_ `#define _APS_NEXT_RESOURCE_VALUE 120`
- L64 _macro_ `#define _APS_NEXT_COMMAND_VALUE 40002`
- L65 _macro_ `#define _APS_NEXT_CONTROL_VALUE 1036`
- L66 _macro_ `#define _APS_NEXT_SYMED_VALUE 101`
