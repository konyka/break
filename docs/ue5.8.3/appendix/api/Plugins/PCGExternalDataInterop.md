# Plugins / PCGExternalDataInterop

- module root: `Plugins/PCGInterops/PCGExternalDataInterop/Source/PCGExternalDataInterop`
- headers: 1; symbols: 21
- symbol kinds: class=2, enum=1, enumerator=2, function=1, member=5, prototype=10
- PrivateDependencyModuleNames: AlembicLib, AlembicLibrary, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, PCG, Projects

### `Plugins/PCGInterops/PCGExternalDataInterop/Source/PCGExternalDataInterop/Public/Elements/PCGLoadAlembicElement.h` (Public)


#### enum `EPCGLoadAlembicStandardSetup`  
`enum class EPCGLoadAlembicStandardSetup : uint8`  
_L12-16_
- reflection: `UENUM()`
- L14 _public enumerator_ `None = 0`
- L15 _public enumerator_ `CitySample UMETA(Tooltip="Uses the same setup as in the City Sample demo: right handed Y-up and the orient and scale mapping to the rotation and scale, respectively")`

#### class `UPCGLoadAlembicSettings`  
`class UPCGLoadAlembicSettings : public UPCGExternalDataSettings`  
_L19-67_
- reflection: `UCLASS(MinimalAPI, BlueprintType, ClassGroup = (Procedural))`
- inherits: `UPCGExternalDataSettings`
- L26 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public function_ `virtual FName GetDefaultNodeName() const override`
- L33 _public prototype_ `virtual FText GetDefaultNodeTitle() const override;`
- L34 _public prototype_ `virtual FText GetNodeTooltipText() const override;`
- L38 _protected prototype_ `virtual FPCGElementPtr CreateElement() const override;`
- L43 _public member_ `FFilePath AlembicFilePath;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Alembic", meta = (FilePathFilter = "Alembic files (*.abc)|*.abc", PCG_Overridable))`
- L48 _public member_ `FVector ConversionScale = FVector(1.0f, -1.0f, 1.0f);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Alembic", meta = (PCG_Overridable))` — Scale to apply during import. Note that for both Max/Maya presets the value flips the Y axis.
- L52 _public member_ `FVector ConversionRotation = FVector::ZeroVector;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Alembic", meta = (PCG_Overridable))` — Rotation in Euler angles applied during import. For Max, use (90, 0, 0).
- L56 _public member_ `bool bConversionFlipHandedness = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Alembic", meta = (PCG_Overridable, Tooltip="Flips rotation direction (W), useful together with swizzling"))` — When changing handedness, it is sometimes needed to flip the rotation direction
- L59 _public prototype_ `void SetupFromStandard(EPCGLoadAlembicStandardSetup InSetup);` — `UFUNCTION(BlueprintCallable, Category = "PCG|AlembicImport")`
- L61 _public prototype_ `static void SetupFromStandard(EPCGLoadAlembicStandardSetup InSetup, FVector& InConversionScale, FVector& InConversionRotation, bool& bInConversionFlipHandedness, TMap<FString, FPCGAttributePropertyInputSelector>& InAttributeMapping);`
- L65 _public member_ `EPCGLoadAlembicStandardSetup Setup = EPCGLoadAlembicStandardSetup::None;` — `UPROPERTY(EditAnywhere, Category = "Alembic", meta = (DisplayName="Setup from standard"))`

#### class `FPCGLoadAlembicElement`  
`class FPCGLoadAlembicElement : public FPCGExternalDataElement`  
_L69-77_
- inherits: `FPCGExternalDataElement`
- L72 _public prototype_ `virtual void GetDependenciesCrc(const FPCGGetDependenciesCrcParams& InParams, FPCGCrc& OutCrc) const override;`
- L74 _protected prototype_ `virtual FPCGContext* CreateContext() override;`
- L75 _protected prototype_ `virtual bool PrepareLoad(FPCGExternalDataContext* Context) const override;`
- L76 _protected prototype_ `virtual bool ExecuteLoad(FPCGExternalDataContext* Context) const override;`
