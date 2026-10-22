# Plugins / PCGExternalDataInteropEditor

- module root: `Plugins/PCGInterops/PCGExternalDataInterop/Source/PCGExternalDataInteropEditor`
- headers: 1; symbols: 15
- symbol kinds: class=2, member=5, prototype=7, struct=1
- PrivateDependencyModuleNames: AlembicLib, AlembicLibrary, PCGEditor, PCGExternalDataInterop, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, PCG, Projects

### `Plugins/PCGInterops/PCGExternalDataInterop/Source/PCGExternalDataInteropEditor/Public/PCGLoadAlembic.h` (Public)


#### struct `FPCGLoadAlembicBPData`  
`struct FPCGLoadAlembicBPData`  
_L14-30_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `FFilePath AlembicFilePath;` — `UPROPERTY(EditAnywhere, Category = "Alembic", meta = (FilePathFilter = "Alembic files (*.abc)|*.abc", PCG_Overridable))`
- L23 _public member_ `FAbcConversionSettings ConversionSettings;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")` — Conversion settings that will be applied on the transform only
- L26 _public member_ `bool bConversionFlipHandedness = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (Tooltip = "Flips rotation direction (W), useful together with swizzling"))`
- L29 _public member_ `TMap<FString, FPCGAttributePropertyInputSelector> AttributeMapping;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")`

#### class `UPCGAlembicToPCGAssetExporter`  
`class UPCGAlembicToPCGAssetExporter : public UPCGAssetExporter`  
_L33-48_
- reflection: `UCLASS()`
- inherits: `UPCGAssetExporter`
- L39 _public prototype_ `virtual bool ExportAsset(const FString& PackageName, UPCGDataAsset* Asset);`
- L40 _public prototype_ `virtual UPackage* UpdateAsset(const FAssetData& PCGAsset) override;`
- L43 _protected prototype_ `virtual void SerializeMetadata(FArchive& Ar) override;`
- L47 _public member_ `FPCGLoadAlembicBPData LoadSettings;`

#### class `UPCGLoadAlembicFunctionLibrary`  
`class UPCGLoadAlembicFunctionLibrary : public UBlueprintFunctionLibrary`  
_L51-67_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- L57 _public prototype_ `static void ExportAlembicFileToPCG(const FPCGLoadAlembicBPData& Settings, FPCGAssetExporterParameters Parameters = FPCGAssetExporterParameters());` — `UFUNCTION(BlueprintCallable, Category = "PCG|IO")`
- L60 _public prototype_ `static void LoadAlembicFileToPCG(const FPCGLoadAlembicBPData& Settings, FPCGDataCollection& Data, UObject* TargetOuter);` — `UFUNCTION(BlueprintCallable, Category = "PCG|IO", meta = (DeprecatedFunction, DeprecationMessage="The LoadAlembicFileToPCG function has been replaced by ExportAlembicFileToPCG"))`
- L63 _public prototype_ `static void SetupFromStandard(UPARAM(ref) FPCGLoadAlembicBPData& Data, EPCGLoadAlembicStandardSetup InSetup);` — `UFUNCTION(BlueprintCallable, Category = "PCG|IO", meta = (ScriptMethod))`
- L66 _protected prototype_ `static void LoadAlembicFileToPCGInternal(const FPCGLoadAlembicBPData& Settings, FPCGDataCollection& Data, UObject* TargetOuter);`
