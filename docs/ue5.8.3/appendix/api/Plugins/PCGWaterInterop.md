# Plugins / PCGWaterInterop

- module root: `Plugins/Experimental/PCGInterops/PCGWaterInterop/Source/PCGWaterInterop`
- headers: 3; symbols: 24
- symbol kinds: class=4, delegate=1, function=3, member=5, prototype=10, struct=1
- PublicDependencyModuleNames: Core, CoreUObject, Engine, PCG, Water

### `Plugins/Experimental/PCGInterops/PCGWaterInterop/Source/PCGWaterInterop/Public/Data/PCGWaterSplineData.h` (Public)


#### struct `FPCGWaterSplineMetadataStruct`  
`struct FPCGWaterSplineMetadataStruct`  
_L13-32_
- reflection: `USTRUCT()`
- desc: Helper struct to hold a copy of the WaterSplineMetadata contents.
- L19 _public member_ `FInterpCurveFloat Depth;` — `UPROPERTY()` — The Depth of the water at this vertex.
- L23 _public member_ `FInterpCurveFloat WaterVelocityScalar;` — `UPROPERTY()` — The Current of the water at this vertex. Magnitude and direction.
- L27 _public member_ `FInterpCurveFloat RiverWidth;` — `UPROPERTY()` — Rivers Only: The width of the river (from center) in each direction.
- L31 _public member_ `FInterpCurveFloat AudioIntensity;` — `UPROPERTY()` — A scalar used to define intensity of the water audio along the spline.

#### class `UPCGWaterSplineData`  
`class UPCGWaterSplineData : public UPCGSplineData`  
_L35-55_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGSplineData`
- L40 _public prototype_ `void Initialize(const UWaterSplineComponent* InSpline);`
- L43 _public prototype_ `virtual bool SamplePoint(const FTransform& Transform, const FBox& Bounds, FPCGPoint& OutPoint, UPCGMetadata* OutMetadata) const override;`
- L45 _protected prototype_ `virtual UPCGSpatialData* CopyInternal(FPCGContext* Context) const override;`
- L49 _protected prototype_ `virtual FTransform GetTransformAtDistance(int SegmentIndex, FVector::FReal Distance, bool bWorldSpace = true, FBox* OutBounds = nullptr) const override;`
- L50 _protected prototype_ `virtual void WriteMetadataToPoint(float InputKey, FPCGPoint& OutPoint, UPCGMetadata* OutMetadata) const override;`
- L54 _protected member_ `FPCGWaterSplineMetadataStruct WaterSplineMetadataStruct;` — `UPROPERTY()`

### `Plugins/Experimental/PCGInterops/PCGWaterInterop/Source/PCGWaterInterop/Public/Elements/PCGGetWaterSpline.h` (Public)


#### class `UPCGGetWaterSplineSettings`  
`class UPCGGetWaterSplineSettings : public UPCGGetSplineSettings`  
_L13-30_
- reflection: `UCLASS(BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGGetSplineSettings`
- desc: Builds a collection of data from WaterSplineComponents on the selected actors.
- L18 _public prototype_ `UPCGGetWaterSplineSettings();`
- L22 _public function_ `virtual FName GetDefaultNodeName() const override`
- L23 _public function_ `virtual FText GetDefaultNodeTitle() const override`
- L24 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L28 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`

#### class `FPCGGetWaterSplineElement`  
`class FPCGGetWaterSplineElement : public FPCGDataFromActorElement`  
_L32-36_
- inherits: `FPCGDataFromActorElement`
- L35 _protected prototype_ `virtual void ProcessActor(FPCGContext* Context, const UPCGDataFromActorSettings* Settings, AActor* FoundActor) const override;`

### `Plugins/Experimental/PCGInterops/PCGWaterInterop/Source/PCGWaterInterop/Public/PCGWaterInteropModule.h` (Public)


#### class `FPCGWaterInteropModule`  
`class FPCGWaterInteropModule final : public IModuleInterface`  
_L10-16_
- inherits: `IModuleInterface`
- L14 _public function_ `virtual bool SupportsDynamicReloading() override`

#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGWaterInterop, Log, All);`
- L8 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPCGWaterInterop, Log, All);`
