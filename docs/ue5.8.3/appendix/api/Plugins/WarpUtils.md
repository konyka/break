# Plugins / WarpUtils

- module root: `Plugins/Runtime/WarpUtils/Source/WarpUtils`
- headers: 3; symbols: 10
- symbol kinds: class=2, delegate=1, prototype=7
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: Core

### `Plugins/Runtime/WarpUtils/Source/WarpUtils/Private/WarpUtilsLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogWarpUtilsBlueprint, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogWarpUtilsBlueprint, Log, All);`

### `Plugins/Runtime/WarpUtils/Source/WarpUtils/Public/Blueprints/WarpUtilsBlueprintLibrary.h` (Public)


#### class `UWarpUtilsBlueprintLibrary`  
`class UWarpUtilsBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L11-42_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L18 _public prototype_ `static bool SavePFM(const FString& File, const int TexWidth, const int TexHeight, const TArray<FVector>& Vertices);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save PFM"), Category = "Miscellaneous|Warp")` — Save data to a PFM file
- L22 _public prototype_ `static bool SavePFMEx(const FString& File, const int TexWidth, const int TexHeight, const TArray<FVector>& Vertices, const TArray<bool>& TilesValidityFlags);` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save PFM Extended"), Category = "Miscellaneous|Warp")` — Save data to a PFM file. Since the float NaN value is not available in blueprints, we provide a flags array (false == NaN)
- L26 _public prototype_ `static bool GeneratePFM( const FString& File, const FVector& StartLocation, const FRotator& StartRotation, const AActor* PFMOrigin, const int TilesHorizontal, const int TilesVertical, const float ColumnAngle, const float TileSizeHorizontal, const float TileSizeVertical, const int TilePixelsHorizontal, const int TilePixelsVertical, const bool AddMargin );` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Generate PFM"), Category = "Miscellaneous|Warp")` — Generate and save data to a PFM file
- L35 _public prototype_ `static bool GeneratePFMEx( const FString& File, const FVector& StartLocation, const FRotator& StartRotation, const AActor* PFMOrigin, const int TilesHorizontal, const int TilesVertical, const float ColumnAngle, const float TileSizeHorizontal, const float TileSizeVertical, const int TilePixelsHorizontal, const int TilePixelsVertical, const bool AddMargin, const TArray<bool>& TilesValidityFlags );` — `UFUNCTION(BlueprintCallable, meta = (DisplayName = "Generate PFM Extended"), Category = "Miscellaneous|Warp")` — Generate and save data to a PFM file. Additionally, we have an array of tiles validiy flags (false == all pixels of a tile are NaN)

### `Plugins/Runtime/WarpUtils/Source/WarpUtils/Public/WarpUtils.h` (Public)


#### class `FWarpUtilsModule`  
`class FWarpUtilsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`
