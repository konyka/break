# Plugins / MetaHumanDepthGenerator

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanDepthGenerator`
- headers: 6; symbols: 44
- symbol kinds: class=4, function=1, member=17, namespace=5, prototype=16, struct=1
- PrivateDependencyModuleNames: CameraCalibrationCore, CaptureDataEditor, CaptureDataUtils, ContentBrowser, ContentBrowserData, ImgMedia, MeshTrackerInterface, MetaHumanCaptureData, MetaHumanCaptureSource, MetaHumanCore, MetaHumanPipeline, MetaHumanPipelineCore, Slate, SlateCore, ToolMenus, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: CaptureDataCore, Core, CoreUObject

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanDepthGenerator/Private/MetaHumanDepthGenerator.h` (Private)


#### class `UMetaHumanDepthGenerator`  
`class UMetaHumanDepthGenerator : public UObject`  
_L15-25_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `UObject`
- L21 _public prototype_ `bool Process(UFootageCaptureData* InFootageCaptureData);`
- L24 _public prototype_ `bool Process(UFootageCaptureData* InFootageCaptureData, UMetaHumanGenerateDepthWindowOptions* InOptions);` — `UFUNCTION(BlueprintCallable, Category = "MetaHuman | DepthGenerator")`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanDepthGenerator/Private/MetaHumanDepthGeneratorAutoReimport.h` (Private)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace MetaHuman` (scope `UE`)
- L11 _prototype_ `TArray<FAutoReimportDirectoryConfig> DepthGeneratorUpdateAutoReimportExclusion( const FString& InSourceDirectory, const FString& InWildcard, const TArray<FAutoReimportDirectoryConfig>& InDirectoryConfigs );` (scope `UE::MetaHuman`) — Note: This function is duplicated in the MetaHumanCaptureSource module. The intention is to consolidate these functions in future.
- L19 _prototype_ `bool DepthGeneratorDirectoryConfigsAreDifferent( const TArray<FAutoReimportDirectoryConfig>& Lhs, const TArray<FAutoReimportDirectoryConfig>& Rhs );` (scope `UE::MetaHuman`) — Note: This function is duplicated in the MetaHumanCaptureSource module. The intention is to consolidate these functions in future.

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanDepthGenerator/Private/MetaHumanDepthGeneratorModule.h` (Private)


#### class `FMetaHumanDepthGeneratorModule`  
`class FMetaHumanDepthGeneratorModule : public IModuleInterface`  
_L7-19_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _private prototype_ `void PostEngineInit();`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanDepthGenerator/Private/Utils/FrameOffsetCalculator.h` (Private)


#### struct `UE::MetaHuman::DepthGenerator::FCameraTimecodeInfo`  
`struct FCameraTimecodeInfo`  
_L12-16_
- L14 _public member_ `FTimecode Timecode;`
- L15 _public member_ `FFrameRate FrameRate;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace MetaHuman` (scope `UE`)
- L9 _namespace_ `namespace DepthGenerator` (scope `UE::MetaHuman`)
- L18 _prototype_ `TArray<int32> CalculateFrameOffset(const TArray<FCameraTimecodeInfo>& InCameraTimecodeInfos);` (scope `UE::MetaHuman::DepthGenerator`)

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanDepthGenerator/Private/Widgets/MetaHumanGenerateDepthWindowOptions.h` (Private)


#### class `UMetaHumanGenerateDepthWindowOptions`  
`class UMetaHumanGenerateDepthWindowOptions : public UObject`  
_L13-76_
- reflection: `UCLASS(BlueprintType)`
- inherits: `UObject`
- L18 _public member_ `static const FString ImageSequenceDirectoryName;`
- L23 _public member_ `FString AssetName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L26 _public member_ `FDirectoryPath PackagePath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options", meta = (ContentDir))`
- L29 _public member_ `FDirectoryPath ImageSequenceRootPath;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L32 _public member_ `bool bAutoSaveAssets = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L35 _public member_ `bool bShouldExcludeDepthFilesFromImport = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L38 _public member_ `bool bShouldCompressDepthFiles = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L41 _public member_ `TObjectPtr<UCameraCalibration> ReferenceCameraCalibration = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Options")`
- L51 _public member_ `float MinDistance = 10.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Depth Options", meta = (Units="Centimeters", ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0"))` — The minimum cm from the camera expected for valid depth information. Depth information closer than this will be ignored to help filter out noise.
- L61 _public member_ `float MaxDistance = 25.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Depth Options", meta = (Units="Centimeters", ClampMin = "0.0", ClampMax = "200.0", UIMin = "0.0", UIMax = "200.0"))` — The maximum cm from the camera expected for valid depth information. Depth information beyond this will be ignored to help filter out noise.
- L65 _public member_ `EMetaHumanCaptureDepthPrecisionType DepthPrecision = EMetaHumanCaptureDepthPrecisionType::Eightieth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Depth Options")` — Precision of the calculated depth data. Full precision is more accurate, but requires more disk space to store.
- L69 _public member_ `EMetaHumanCaptureDepthResolutionType DepthResolution = EMetaHumanCaptureDepthResolutionType::Full;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Depth Options")` — Resolution scaling applied to the calculated depth data. Full resolution is more accurate, but requires more disk space to store.
- L74 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanDepthGenerator/Private/Widgets/SMetaHumanGenerateDepthWindow.h` (Private)


#### class `SMetaHumanGenerateDepthWindow`  
`class SMetaHumanGenerateDepthWindow : public SWindow`  
_L12-42_
- inherits: `SWindow`
- L16 _public function_ `SLATE_BEGIN_ARGS(SMetaHumanGenerateDepthWindow) : _CaptureData(nullptr)`
- L21 _public prototype_ `SLATE_ARGUMENT(UFootageCaptureData*, CaptureData) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _public prototype_ `TOptional<TStrongObjectPtr<UMetaHumanGenerateDepthWindowOptions>> ShowModal();`
- L31 _private prototype_ `FString GetDefaultPackagePath();`
- L32 _private prototype_ `FDirectoryPath GetDefaultStoragePath();`
- L33 _private prototype_ `FString GetDirectoryName();`
- L34 _private prototype_ `TObjectPtr<UCameraCalibration> GetDefaultCameraCalibration();`
- L36 _private prototype_ `TSharedRef<SWidget> GenerateWarningMessageIfNeeded() const;`
- L38 _private member_ `bool UserResponse = false;`
- L40 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L41 _private member_ `UFootageCaptureData* CaptureData;`
