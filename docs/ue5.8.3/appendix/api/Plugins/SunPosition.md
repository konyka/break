# Plugins / SunPosition

- module root: `Plugins/Runtime/SunPosition/Source/SunPosition`
- headers: 4; symbols: 20
- symbol kinds: class=4, function=1, member=7, prototype=7, struct=1
- PrivateDependencyModuleNames: Core, CoreUObject, EditorFramework, Engine, PlacementMode, Projects, Slate, SlateCore, UnrealEd

### `Plugins/Runtime/SunPosition/Source/SunPosition/Private/SunPositionModule.h` (Private)


#### class `FSunPositionModule`  
`class FSunPositionModule : public IModuleInterface`  
_L6-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Runtime/SunPosition/Source/SunPosition/Public/SunPosition.h` (Public)


#### struct `FSunPositionData`  
`struct FSunPositionData`  
_L13-44_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public prototype_ `FSunPositionData();`
- L23 _public member_ `float Elevation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Sun Position")` — Sun Elevation
- L27 _public member_ `float CorrectedElevation;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Position")` — Sun Elevation, corrected for atmospheric diffraction
- L31 _public member_ `float Azimuth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Position")` — Sun azimuth
- L35 _public member_ `FTimespan SunriseTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Position")` — Sunrise time
- L39 _public member_ `FTimespan SunsetTime;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Position")` — Sunset time
- L43 _public member_ `FTimespan SolarNoon;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sun Position")` — Solar noon

#### class `USunPositionFunctionLibrary`  
`class USunPositionFunctionLibrary : public UBlueprintFunctionLibrary`  
_L47-55_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L54 _public prototype_ `static void GetSunPosition(float Latitude, float Longitude, float TimeZone, bool bIsDaylightSavingTime, int32 Year, int32 Month, int32 Day, int32 Hours, int32 Minutes, int32 Seconds, FSunPositionData& SunPositionData);` — `UFUNCTION(BlueprintCallable, Category = "Sun Position")` — Get the sun's position data based on position, date and time

### `Plugins/Runtime/SunPosition/Source/SunPosition/Public/SunPositionPlacement.h` (Public)


#### class `FSunPositionPlacement`  
`class FSunPositionPlacement`  
_L7-11_
- L10 _public prototype_ `static void RegisterPlacement();`

### `Plugins/Runtime/SunPosition/Source/SunPosition/Public/SunPositionStyle.h` (Public)


#### class `FSunPositionStyle`  
`class FSunPositionStyle`  
_L8-17_
- L11 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L13 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L16 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`
