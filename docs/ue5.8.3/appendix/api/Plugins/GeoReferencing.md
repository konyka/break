# Plugins / GeoReferencing

- module root: `Plugins/Runtime/GeoReferencing/Source/GeoReferencing`
- headers: 7; symbols: 164
- symbol kinds: class=6, enum=1, enumerator=2, function=23, member=48, prototype=82, struct=2
- PrivateDependencyModuleNames: CoreUObject, Engine, InputCore, PROJ, Projects, RHI, SQLiteCore, Slate
- PublicDependencyModuleNames: Core, Engine

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencing/Public/Ellipsoid.h` (Public)


#### struct `FEllipsoid`  
`struct FEllipsoid`  
_L11-30_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public prototype_ `FEllipsoid();`
- L17 _public prototype_ `FEllipsoid(double RadiusX, double RadiusY, double RadiusZ);`
- L18 _public prototype_ `FEllipsoid(const FVector& InRadii);`
- L20 _public member_ `FVector Radii;`
- L21 _public member_ `FVector RadiiSquared;`
- L22 _public member_ `FVector OneOverRadii;`
- L23 _public member_ `FVector OneOverRadiiSquared;`
- L25 _public prototype_ `double GetMaximumRadius();`
- L26 _public prototype_ `double GetMinimumRadius();`
- L28 _public prototype_ `FVector GeodeticSurfaceNormal(const FVector& ECEFLocation) const;`
- L29 _public prototype_ `FVector GeodeticSurfaceNormal(const FGeographicCoordinates& GeographicCoordinates) const;`

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencing/Public/GeoReferencingBFL.h` (Public)


#### class `UGeoReferencingBFL`  
`class UGeoReferencingBFL : public UBlueprintFunctionLibrary`  
_L13-35_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint function library to convert geospatial coordinates to text
- L21 _private prototype_ `static FText ToFullText(UPARAM(ref) FVector& CartesianCoordinates, int32 IntegralDigits = 3);` — `UFUNCTION(BlueprintPure, Category = "GeoReferencing", meta = (DisplayName = "ToFullText", AdvancedDisplay = "1", BlueprintAutocast))` — Converts a LargeCoordinates value to localized formatted text, in the form 'X= Y= Z='
- L27 _private prototype_ `static FText ToCompactText(UPARAM(ref) FVector& CartesianCoordinates, int32 IntegralDigits = 3);` — `UFUNCTION(BlueprintPure, Category = "GeoReferencing", meta = (DisplayName = "ToCompactText", AdvancedDisplay = "1", BlueprintAutocast))` — Converts a LargeCoordinates value to formatted text, in the form '(X, Y, Z)'
- L33 _private prototype_ `static void ToSeparateTexts(UPARAM(ref) FVector& CartesianCoordinates, FText& OutX, FText& OutY, FText& OutZ, int32 IntegralDigits = 3);` — `UFUNCTION(BlueprintPure, Category = "GeoReferencing", meta = (DisplayName = "ToSeparateTexts", AdvancedDisplay = "4", BlueprintAutocast))` — Converts a LargeCoordinates value to 3 separate text values

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencing/Public/GeoReferencingModule.h` (Public)


#### class `FGeoReferencingModule`  
`class FGeoReferencingModule : public IModuleInterface`  
_L13-19_
- inherits: `IModuleInterface`
- desc: FGeoReferencingModule
- L16 _public prototype_ `FGeoReferencingModule() = default;`
- L18 _public prototype_ `virtual void StartupModule() override;`

#### Free symbols / members of external scopes

- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGeoReferencing, Log, All);`

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencing/Public/GeoReferencingSystem.h` (Public)


#### enum `EPlanetShape`  
`enum class EPlanetShape : uint8`  
_L19-32_
- reflection: `UENUM(BlueprintType)`
- L24 _public enumerator_ `FlatPlanet UMETA(DisplayName = "Flat Planet")` — The world geometry coordinates are expressed in a projected space such as a Mercator projection. In this mode, Planet curvature is not considered and you might face errors related to projection on large environments
- L31 _public enumerator_ `RoundPlanet UMETA(DisplayName = "Round Planet")` — The world geometry coordinates are expressed in a planet wide Cartesian frame, placed on a specific location or at earth, or at the planet center. You might need dynamic rebasing to avoid precision issues at large scales.

#### class `AGeoReferencingSystem`  
`class AGeoReferencingSystem : public AInfo`  
_L39-434_
- reflection: `UCLASS(hidecategories = (Transform, Replication, Actor, Cooking))`
- inherits: `AInfo`
- desc: This AInfos enable you to define a correspondance between the UE origin and an actual geographic location on a planet Once done it offers different functions to convert coordinates between UE and Geographic coordinates
- L44 _public prototype_ `AGeoReferencingSystem(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L46 _public prototype_ `virtual void PostLoad() override;`
- L47 _public prototype_ `virtual void PostActorCreated() override;`
- L48 _public prototype_ `virtual void BeginDestroy() override;`
- L51 _public prototype_ `static AGeoReferencingSystem* GetGeoReferencingSystem(UObject* WorldContextObject);` — `UFUNCTION(BlueprintPure, Category = "GeoReferencing", meta = (WorldContext = "WorldContextObject"))`
- L63 _public function_ `void K2_EngineToProjected(const FVector& EngineCoordinates, FVector& ProjectedCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "Engine To Projected"))` — Convert a Vector expressed in ENGINE space to the PROJECTED CRS
- L69 _public function_ `void K2_ProjectedToEngine(const FVector& ProjectedCoordinates, FVector& EngineCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "Projected To Engine"))` — Convert a Vector expressed in PROJECTED CRS to ENGINE space
- L77 _public function_ `void K2_EngineToECEF(const FVector& EngineCoordinates, FVector& ECEFCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "Engine To ECEF"))` — Convert a Vector expressed in ENGINE space to the ECEF CRS
- L83 _public function_ `void K2_ECEFToEngine(const FVector& ECEFCoordinates, FVector& EngineCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "ECEF To Engine"))` — Convert a Vector expressed in ECEF CRS to ENGINE space
- L91 _public function_ `void K2_ProjectedToGeographic(const FVector& ProjectedCoordinates, FGeographicCoordinates& GeographicCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "Projected To Geographic"))` — Convert a Coordinate expressed in PROJECTED CRS to GEOGRAPHIC CRS
- L97 _public function_ `void K2_GeographicToProjected(const FGeographicCoordinates& GeographicCoordinates, FVector& ProjectedCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "Geographic To Projected"))` — Convert a Coordinate expressed in GEOGRAPHIC CRS to PROJECTED CRS
- L105 _public function_ `void K2_ProjectedToECEF(const FVector& ProjectedCoordinates, FVector& ECEFCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "Projected To ECEF"))` — Convert a Coordinate expressed in PROJECTED CRS to ECEF CRS
- L111 _public function_ `void K2_ECEFToProjected(const FVector& ECEFCoordinates, FVector& ProjectedCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "ECEF To Projected"))` — Convert a Coordinate expressed in ECEF CRS to PROJECTED CRS
- L119 _public function_ `void K2_GeographicToECEF(const FGeographicCoordinates& GeographicCoordinates, FVector& ECEFCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "Geographic To ECEF"))` — Convert a Coordinate expressed in GEOGRAPHIC CRS to ECEF CRS
- L125 _public function_ `void K2_ECEFToGeographic(const FVector& ECEFCoordinates, FGeographicCoordinates& GeographicCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations", meta = (DisplayName = "ECEF To Geographic"))` — Convert a Coordinate expressed in ECEF CRS to GEOGRAPHIC CRS
- L133 _public function_ `void K2_GetENUVectorsAtProjectedLocation(const FVector& ProjectedCoordinates, FVector& East, FVector& North, FVector& Up)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|ENU", meta = (DisplayName = "Get ENU Vectors At Projected Location"))` — Get the East North Up vectors at a specific location
- L139 _public function_ `void K2_GetENUVectorsAtECEFLocation(const FVector& ECEFCoordinates, FVector& East, FVector& North, FVector& Up)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|ENU", meta = (DisplayName = "Get ENU Vectors At ECEF Location"))` — Get the East North Up vectors at a specific location
- L145 _public function_ `void K2_GetECEFENUVectorsAtECEFLocation(const FVector& ECEFCoordinates, FVector& ECEFEast, FVector& ECEFNorth, FVector& ECEFUp)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|ENU", meta = (DisplayName = "Get ECEF ENU Vectors At ECEF Location"))` — Get the East North Up vectors at a specific location - Not in engine frame, but in pure ECEF Frame !
- L151 _public function_ `FTransform K2_GetTangentTransformAtProjectedLocation(const FVector& ProjectedCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|TangentTransforms", meta = (DisplayName = "Get Tangent Transform At Projected Location"))` — Get the the transform to locate an object tangent to Ellipsoid at a specific location
- L157 _public function_ `FTransform K2_GetTangentTransformAtECEFLocation(const FVector& ECEFCoordinates)` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|TangentTransforms", meta = (DisplayName = "Get Tangent Transform At ECEFLocation"))` — Get the the transform to locate an object tangent to Ellipsoid at a specific location
- L168 _public prototype_ `void EngineToProjected(const FVector& EngineCoordinates, FVector& ProjectedCoordinates);` — Convert a Vector expressed in ENGINE space to the PROJECTED CRS
- L173 _public prototype_ `void ProjectedToEngine(const FVector& ProjectedCoordinates, FVector& EngineCoordinates);` — Convert a Vector expressed in PROJECTED CRS to ENGINE space
- L180 _public prototype_ `void EngineToECEF(const FVector& EngineCoordinates, FVector& ECEFCoordinates);` — Convert a Vector expressed in ENGINE space to the ECEF CRS
- L185 _public prototype_ `void ECEFToEngine(const FVector& ECEFCoordinates, FVector& EngineCoordinates);` — Convert a Vector expressed in ECEF CRS to ENGINE space
- L193 _public prototype_ `void EngineToGeographic(const FVector& EngineCoordinates, FGeographicCoordinates& GeographicCoordinates);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations")` — Convert a Vector expressed in ENGINE space to the GEOGRAPHIC CRS
- L199 _public prototype_ `void GeographicToEngine(const FGeographicCoordinates& GeographicCoordinates, FVector& EngineCoordinates);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Transformations")` — Convert a Vector expressed in GEOGRAPHIC CRS to ENGINE space
- L207 _public prototype_ `void ProjectedToGeographic(const FVector& ProjectedCoordinates, FGeographicCoordinates& GeographicCoordinates);` — Convert a Coordinate expressed in PROJECTED CRS to GEOGRAPHIC CRS
- L212 _public prototype_ `void GeographicToProjected(const FGeographicCoordinates& GeographicCoordinates, FVector& ProjectedCoordinates);` — Convert a Coordinate expressed in GEOGRAPHIC CRS to PROJECTED CRS
- L219 _public prototype_ `void ProjectedToECEF(const FVector& ProjectedCoordinates, FVector& ECEFCoordinates);` — Convert a Coordinate expressed in PROJECTED CRS to ECEF CRS
- L224 _public prototype_ `void ECEFToProjected(const FVector& ECEFCoordinates, FVector& ProjectedCoordinates);` — Convert a Coordinate expressed in ECEF CRS to PROJECTED CRS
- L231 _public prototype_ `void GeographicToECEF(const FGeographicCoordinates& GeographicCoordinates, FVector& ECEFCoordinates);` — Convert a Coordinate expressed in GEOGRAPHIC CRS to ECEF CRS
- L236 _public prototype_ `void ECEFToGeographic(const FVector& ECEFCoordinates, FGeographicCoordinates& GeographicCoordinates);` — Convert a Coordinate expressed in ECEF CRS to GEOGRAPHIC CRS
- L244 _public prototype_ `void GetENUVectorsAtEngineLocation(const FVector& EngineCoordinates, FVector& East, FVector& North, FVector& Up);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|ENU")` — Get the East North Up vectors at a specific location
- L249 _public prototype_ `void GetENUVectorsAtProjectedLocation(const FVector& ProjectedCoordinates, FVector& East, FVector& North, FVector& Up);` — Get the East North Up vectors at a specific location
- L255 _public prototype_ `void GetENUVectorsAtGeographicLocation(const FGeographicCoordinates& GeographicCoordinates, FVector& East, FVector& North, FVector& Up);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|ENU")` — Get the East North Up vectors at a specific location
- L260 _public prototype_ `void GetENUVectorsAtECEFLocation(const FVector& ECEFCoordinates, FVector& East, FVector& North, FVector& Up);` — Get the East North Up vectors at a specific location
- L265 _public prototype_ `void GetECEFENUVectorsAtECEFLocation(const FVector& ECEFCoordinates, FVector& ECEFEast, FVector& ECEFNorth, FVector& ECEFUp);` — Get the East North Up vectors at a specific location - Not in engine frame, but in pure ECEF Frame !
- L271 _public prototype_ `FTransform GetTangentTransformAtEngineLocation(const FVector& EngineCoordinates);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|TangentTransforms")` — Get the the transform to locate an object tangent to Ellipsoid at a specific location
- L276 _public prototype_ `FTransform GetTangentTransformAtProjectedLocation(const FVector& ProjectedCoordinates);` — Get the the transform to locate an object tangent to Ellipsoid at a specific location
- L282 _public prototype_ `FTransform GetTangentTransformAtGeographicLocation(const FGeographicCoordinates& GeographicCoordinates);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|TangentTransforms")` — Get the the transform to locate an object tangent to Ellipsoid at a specific location
- L287 _public prototype_ `FTransform GetTangentTransformAtECEFLocation(const FVector& ECEFCoordinates);` — Get the the transform to locate an object tangent to Ellipsoid at a specific location
- L293 _public prototype_ `FTransform GetPlanetCenterTransform();` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Misc")` — Set this transform to an Ellipsoid to have it positioned tangent to the origin.
- L301 _public prototype_ `bool IsCRSStringValid(FString CRSString, FString& Error);` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Misc")` — Check if the string corresponds to a valid CRS descriptor
- L310 _public prototype_ `double GetGeographicEllipsoidMaxRadius();` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Ellipsoid")` — Find the underlying Geographic CRS Ellipsoid and return its maximum radius
- L315 _public prototype_ `double GetGeographicEllipsoidMinRadius();` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Ellipsoid")` — Find the underlying Geographic CRS Ellipsoid and return its minimum radius
- L321 _public prototype_ `double GetProjectedEllipsoidMaxRadius();` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Ellipsoid")` — Find the underlying Projected CRS Ellipsoid and return its maximum radius
- L326 _public prototype_ `double GetProjectedEllipsoidMinRadius();` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Ellipsoid")` — Find the underlying Projected CRS Ellipsoid and return its minimum radius
- L336 _public prototype_ `void ApplySettings();` — `UFUNCTION(BlueprintCallable, Category = "GeoReferencing|Misc", meta = (DisplayName = "Apply Runtime Changes"))` — In case you want to change the Origin or CRS definition properties during application execution, you need to call this function to update the internal transformation cache. Note this is not a recommended practice, because it will not move the level actors accordingly. Can be useful though if you rebase your actors yourself, or if you want to change one CRS used for displaying coordinates.
- L349 _public member_ `EPlanetShape PlanetShape = EPlanetShape::FlatPlanet;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing")` — This mode has to be set consistently with the way you authored your ground geometry. - For small environments, a projection is often applied and the world is considered as Flat - For planet scale environments, projections is not suitable and the geometry is Rounded.
- L356 _public member_ `FString ProjectedCRS = FString(TEXT("EPSG` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "GeoReferencing")` — String that describes the PROJECTED CRS of choice. CRS can be identified by their code (EPSG:4326), a well-known text(WKT) string, or PROJ strings...
- L363 _public member_ `FString GeographicCRS = FString(TEXT("EPSG` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "GeoReferencing")` — String that describes the GEOGRAPHIC CRS of choice. CRS can be identified by their code (EPSG:4326), a well-known text(WKT) string, or PROJ strings...
- L374 _public member_ `bool bOriginAtPlanetCenter = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "PlanetShape==EPlanetShape::RoundPlanet"))` — if true, the UE origin is located at the Planet Center, otherwise, the UE origin is assuming to be defined at one specific point of the planet surface, defined by the properties below.
- L385 _public member_ `bool bOriginLocationInProjectedCRS = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "bOriginAtPlanetCenter==false"))` — if true, the UE origin georeference is expressed in the PROJECTED CRS. (NOT in ECEF ! - Projected worlds are the most frequent use case...) if false, the origin is located using geographic coordinates. WARNING : the location has to be expressed as Integer values because of accuracy. Be very careful about that when authoring your data in external tools !
- L391 _public member_ `double OriginLatitude = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "!bOriginLocationInProjectedCRS && !bOriginAtPlanetCenter", ClampMin = "-90", ClampMax = "90"))` — Latitude of UE Origin on planet
- L397 _public member_ `double OriginLongitude = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "!bOriginLocationInProjectedCRS && !bOriginAtPlanetCenter", ClampMin = "-180", ClampMax = "180"))` — Longitude of UE Origin on planet
- L403 _public member_ `double OriginAltitude = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "!bOriginLocationInProjectedCRS && !bOriginAtPlanetCenter"))` — Altitude of UE Origin on planet
- L409 _public member_ `double OriginProjectedCoordinatesEasting = 500000.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "bOriginLocationInProjectedCRS && !bOriginAtPlanetCenter"))` — Easting position of UE Origin on planet, express in the Projected CRS Frame
- L415 _public member_ `double OriginProjectedCoordinatesNorthing = 5000000.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "bOriginLocationInProjectedCRS && !bOriginAtPlanetCenter"))` — Northing position of UE Origin on planet, express in the Projected CRS Frame
- L421 _public member_ `double OriginProjectedCoordinatesUp = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeoReferencing|Origin Location", meta = (EditConditionHides, EditCondition = "bOriginLocationInProjectedCRS && !bOriginAtPlanetCenter"))` — Up position of UE Origin on planet, express in the Projected CRS Frame
- L425 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L429 _private prototype_ `void Initialize();`
- L433 _private member_ `TPimplPtr<FGeoReferencingSystemInternals> Impl;`

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencing/Public/GeographicCoordinates.h` (Public)


#### struct `FGeographicCoordinates`  
`struct FGeographicCoordinates`  
_L12-35_
- reflection: `USTRUCT(BlueprintType)`
- L18 _public prototype_ `FGeographicCoordinates();`
- L19 _public prototype_ `FGeographicCoordinates(double InLongitude, double InLatitude, double InAltitude);`
- L20 _public prototype_ `FGeographicCoordinates(const FVector& LatLongAltVector);` — FVector where X = Latitude, Y = Longitude, Z = Altitude
- L23 _public member_ `double Longitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "GeoReferencing")`
- L25 _public member_ `double Latitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "GeoReferencing")`
- L27 _public member_ `double Altitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Config, Category = "GeoReferencing")`
- L29 _public prototype_ `FText ToFullText(int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool bAsDMS = false);`
- L30 _public prototype_ `FText ToCompactText(int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool bAsDMS = false);`
- L31 _public prototype_ `void ToSeparateTexts(FText& OutLatitude, FText& OutLongitude, FText& OutAltitude, int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool bAsDMS = false);`
- L34 _private prototype_ `static FText AsAngle(double Val, const FNumberFormattingOptions* const Options = NULL, bool bAsDMS = false);`

#### class `UGeographicCoordinatesFunctionLibrary`  
`class UGeographicCoordinatesFunctionLibrary : public UBlueprintFunctionLibrary`  
_L38-90_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L46 _private function_ `static inline FText ToFullText(UPARAM(ref) FGeographicCoordinates& GeographicCoordinates, int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool bAsDMS = false)` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToFullText", AdvancedDisplay = "1", BlueprintAutocast), Category = "GeoReferencing")` — Converts a GeographicCoordinates value to localized formatted text, in the form 'X= Y= Z='
- L55 _private function_ `static inline FText ToCompactText(UPARAM(ref) FGeographicCoordinates& GeographicCoordinates, int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool bAsDMS = false)` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToCompactText", AdvancedDisplay = "1", BlueprintAutocast), Category = "GeoReferencing")` — Converts a GeographicCoordinates value to formatted text, in the form '(X, Y, Z)'
- L64 _private function_ `static void ToSeparateTexts(UPARAM(ref) FGeographicCoordinates& GeographicCoordinates, FText& OutLatitude, FText& OutLongitude, FText& OutAltitude, int32 IntegralDigitsLatLon = 8, int32 IntegralDigitsAlti = 2, bool bAsDMS = false)` — `UFUNCTION(BlueprintPure, meta = (DisplayName = "ToSeparateTexts", AdvancedDisplay = "4", BlueprintAutocast), Category = "GeoReferencing")` — Converts a GeographicCoordinates value to 3 separate text values
- L75 _private function_ `static FGeographicCoordinates MakeGeographicCoordinates(const FVector& LatLongAltVector)` — `UFUNCTION(BlueprintPure, Category = "GeoReferencing|Coordinates")` — Make Geographic Coordinates from a FVector where X=Latitude, Y=Longitude, Z=Altitude
- L84 _private function_ `static void ToLatLongAltVector(UPARAM(ref) FGeographicCoordinates& GeographicCoordinates, FVector& OutLatLongAltVector)` — `UFUNCTION(BlueprintPure, Category = "GeoReferencing", meta = (DeprecatedFunction, DeprecationMessage = "BP now support doubles, Function useless and can lead to precision issues"))` — Express the Geographic coordinates as a FVector where  where X=Latitude, Y=Longitude, Z=Altitude

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencing/Public/RoundPlanetPawn.h` (Public)


#### class `ARoundPlanetPawn`  
`class ARoundPlanetPawn : public ADefaultPawn`  
_L22-269_
- reflection: `UCLASS()`
- inherits: `ADefaultPawn`
- desc: This pawn can be used to easily move around the globe while maintaining a sensible orientation. As the pawn moves across the horizon, it automatically changes its own up direction such that the world always looks right-side up.
- L25 _private prototype_ `ARoundPlanetPawn();`
- L37 _public member_ `TObjectPtr<UCurveFloat> AltitudeProfileCurve;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation")` — This curve dictates what percentage of the max altitude the pawn should take at a given time on the curve. Depending on the total distance to Fly, a constant maximum altitude is computed from FlyToLocationMaximumAltitudeCurve Then during the fly, the actual pawn altitude is computed from this profile and the reference maximum altitude. This allows to have nice movements whenever you FlyTo near or far from your actual location. This curve must be kept in the 0 to 1 range on both axes.
- L46 _public member_ `TObjectPtr<UCurveFloat> MaximumAltitudeCurve;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation")` — This curve is used to pick up a reference the maximum altitude when flying to a location. This maximum altitude will be moderated by the FlyToLocationAltitudeProfileCurve X Axis is the distance of the flight (meters) Y Axis is the maximum altitude to be used for this flight (meters)
- L53 _public member_ `float MaximumAltitudeValue = 300;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation")` — In case MaximumAltitudeCurve is not defined, the AltitudeProfileCurve will use this Maximum altitude value for the flight, whatever the travel distance. In meters
- L63 _public member_ `TObjectPtr<UCurveFloat> ProgressCurve;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation")` — This curve is used to ease in an out the Fly to Location speed. It must be kept in the 0 to 1 range on both axes. X axis is the normalized time of travel Y axis is the progress on the flight motion. A linear curve will give a constant progress speed whereas a easein//easeout one will slow down the speed at beginning/end of motion.
- L69 _public member_ `float FlyDuration = 5.0;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation", meta = (ClampMin = 0.0))` — Fly to Location duration (in seconds)
- L77 _public member_ `float GranularityDegrees = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation", meta = (ClampMin = 0.0))` — The granularity in degrees with which keypoints should be generated for the Fly to Location interpolation. Lower values means smoother motion. ROM : 1 degree latitude ~110km on earth. => 0.1 ~10km
- L85 _public member_ `int32 MinimumStepCount = 10;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation", meta = (ClampMin = 0.0))` — The minimum linear steps for the FlyTolocation motion. GranularityDegrees is not sufficient in case of short travels. Eg if 0.1, any jump shorter than 10km will have only one step. Make sure we have at least this number of steps in the trajectory.
- L91 _public member_ `int32 MaximumStepCount = 300;` — `UPROPERTY(EditAnywhere, Category = "FlyToLocation", meta = (ClampMin = 0.0))` — Make sure we don't get crazy in case of large flights with small granularity
- L99 _public member_ `bool OrbitalMotion = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")` — if True, the motion Forward/Right motion of the pawn are relative to Planet tangent, meaning the altitude will approximately be kept, whatever the pawn camera orientation
- L106 _public member_ `float BaseSpeedKmh = 100.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")` — The Reference maximum speed for the pawn, before being altered by any Scalar modifier or by altitude curve ActualMaxSpeed = BaseSpeedKmh * SpeedScalar * AltitudeSpeedModifierCurve(Altitude)
- L113 _public member_ `float SpeedScalar = 1.0f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")` — Scalar modifier for the base speed ActualMaxSpeed = BaseSpeedKmh * SpeedScalar * AltitudeSpeedModifierCurve(Altitude)
- L119 _public member_ `float SpeedScalarIncrement = 1.5f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")` — Multiplier/Divider for increasing/decreasing the speed scalar
- L127 _public member_ `TObjectPtr<UCurveFloat> SpeedByHATModifierCurve;` — `UPROPERTY(EditAnywhere, Category = "Movement")` — When being very high and moving around the planet, we have to dynamically increase the speed based on Height above terrain to accelerate movement This curve adds a multiplying factor to the maximum speed depending on HAT. ActualMaxSpeed = BaseSpeedKmh * SpeedScalar * AltitudeSpeedModifierCurve(Altitude)
- L133 _public member_ `float HAT = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")` — Height Above Terrain. The distance between the ground and the pawn
- L139 _public member_ `float Altitude = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")` — The distance between the geographic ellipsoid surface and the pawn
- L147 _public prototype_ `void FlyToLocationECEF(const FVector& ECEFDestination, double YawAtDestination, double PitchAtDestination, bool CanInterruptByMoving);` — `UFUNCTION(BlueprintCallable, Category = "FlyToLocation")` — Begin a smooth camera flight to the given ECEF destination such that the camera ends at the specified yaw and pitch. The flight can be enforced or canceled if the user moves the pawn
- L154 _public prototype_ `void FlyToLocationGeographic(const FGeographicCoordinates& GeographicDestination, double YawAtDestination, double PitchAtDestination, bool CanInterruptByMoving);` — `UFUNCTION(BlueprintCallable, Category = "FlyToLocation")` — Begin a smooth camera flight to the given Latitude/Longitude destination such that the camera ends at the specified yaw and pitch. The flight can be enforced or canceled if the user moves the pawn
- L161 _public prototype_ `void FlyToLocationLatitudeLongitudeAltitude(const double& InLatitude, const double& InLongitude, const double& InAltitude, double YawAtDestination, double PitchAtDestination, bool CanInterruptByMoving);` — `UFUNCTION(BlueprintCallable, Category = "FlyToLocation")` — Begin a smooth camera flight to the given Latitude/Longitude destination such that the camera ends at the specified yaw and pitch. The flight can be enforced or canceled if the user moves the pawn
- L167 _public prototype_ `void InterruptFlyToLocation();` — `UFUNCTION(BlueprintCallable, Category = "FlyToLocation")` — Stop the current Fly To Location motion
- L173 _public function_ `void ResetSpeedScalar()` — `UFUNCTION(BlueprintCallable, Category = "Movement")` — Reset the Speed Scalar to its default value - Middle-mouse button click equivalent
- L179 _public function_ `void IncreaseSpeedScalar()` — `UFUNCTION(BlueprintCallable, Category = "Movement")` — Increase the Speed Scalar - MouseWheel Up equivalent
- L185 _public function_ `void DecreaseSpeedScalar()` — `UFUNCTION(BlueprintCallable, Category = "Movement")` — Decrease the Speed Scalar - MouseWheel Down equivalent
- L189 _public prototype_ `void OnConstruction(const FTransform& Transform) override;`
- L191 _public prototype_ `void BeginPlay() override;`
- L193 _public prototype_ `void Tick(float DeltaSeconds) override;`
- L200 _public prototype_ `virtual void MoveForward(float Val) override;` — Input callback to move forward in local space (or backward if Val is negative). @param Val Amount of movement in the forward direction (or backward if negative). @see APawn::AddMovementInput()
- L207 _public prototype_ `virtual void MoveRight(float Val) override;` — Input callback to strafe right in local space (or left if Val is negative). @param Val Amount of movement in the right direction (or left if negative). @see APawn::AddMovementInput()
- L214 _public prototype_ `virtual void MoveUp_World(float Val) override;` — Input callback to move up in world space (or down if Val is negative). @param Val Amount of movement in the world up direction (or down if negative). @see APawn::AddMovementInput()
- L220 _public prototype_ `virtual FRotator GetViewRotation() const override;` — Don't return the controller rotation but a transformed rotation to consider planet roundness.
- L225 _public prototype_ `virtual FRotator GetBaseAimRotation() const override;` — Don't return the controller rotation but a transformed rotation to consider planet roundness.
- L230 _public prototype_ `void SetupPlayerInputComponent(UInputComponent* InInputComponent) override;` — Adds to the default pawn the Mouse Wheel inputs to tune the speed scalar
- L234 _protected member_ `TObjectPtr<AGeoReferencingSystem> GeoReferencingSystem;` — `UPROPERTY()`
- L242 _private prototype_ `void UpdateMotionObjectsCache(bool ForceUpdate = false);` — In order to limit computations, we keep a cache for some values : TangentTransform, ENU, Altitude, HAT They are updated each time the pawn travels more than CacheUpdateThresholdSq (In UE Units). if not HAT is found, we retry each tick.
- L246 _private prototype_ `void HandleMotionSpeed();` — Updates the Movement Component Speed and Inertia based on the speed scalar changes.
- L250 _private prototype_ `void ProcessFlyToLocation(float DeltaSeconds);` — When flying to a specific location, this function computes at each tick the Planet-relative trajectory.
- L254 _private member_ `bool bIsFlyingToLocation = false;` — Variables for FlyToLocation
- L255 _private member_ `bool bCanInterruptFlight = false;`
- L256 _private member_ `float CurrentFlyTime = 0.0;`
- L257 _private member_ `FRotator FlyToLocationOriginRotation;`
- L258 _private member_ `FRotator FlyToLocationDestinationRotation;`
- L259 _private member_ `TArray<FVector> FlyToLocationKeypoints;`
- L262 _private member_ `FVector LastCacheLocation;` — Variables for Motion Object caches
- L263 _private member_ `float CacheUpdateThresholdSq = 200.0 * 200.0;` — 2m
- L264 _private member_ `FVector East;`
- L265 _private member_ `FVector North;`
- L266 _private member_ `FVector Up;`
- L267 _private member_ `FTransform TangentTransform;`
- L268 _private member_ `bool bIsHATInvalid = true;`

### `Plugins/Runtime/GeoReferencing/Source/GeoReferencing/Public/UFSProjSupport.h` (Public)


#### class `FUFSProj`  
`class FUFSProj`  
_L7-23_
- L13 _private prototype_ `static PROJ_FILE_HANDLE* Open(PJ_CONTEXT* ctx, const char* filename, PROJ_OPEN_ACCESS access, void* user_data);`
- L14 _private prototype_ `static size_t Read(PJ_CONTEXT* ctx, PROJ_FILE_HANDLE* handle, void* buffer, size_t sizeBytes, void* user_data);`
- L15 _private prototype_ `static size_t Write(PJ_CONTEXT* ctx, PROJ_FILE_HANDLE* handle, const void* buffer, size_t sizeBytes, void* user_data);`
- L16 _private prototype_ `static int Seek(PJ_CONTEXT* ctx, PROJ_FILE_HANDLE* handle, long long offset, int whence, void* user_data);`
- L17 _private prototype_ `static unsigned long long Tell(PJ_CONTEXT* ctx, PROJ_FILE_HANDLE* handle, void* user_data);`
- L18 _private prototype_ `static void Close(PJ_CONTEXT* ctx, PROJ_FILE_HANDLE* handle, void* user_data);`
- L19 _private prototype_ `static int Exists(PJ_CONTEXT* ctx, const char* filename, void* user_data);`
- L20 _private prototype_ `static int MkDir(PJ_CONTEXT* ctx, const char* filename, void* user_data);`
- L21 _private prototype_ `static int Unlink(PJ_CONTEXT* ctx, const char* filename, void* user_data);`
- L22 _private prototype_ `static int Rename(PJ_CONTEXT * ctx, const char* oldPath, const char* newPath, void* user_data);`
