# Plugins / CaptureDataEditor

- module root: `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor`
- headers: 12; symbols: 85
- symbol kinds: class=14, delegate=1, function=3, macro=4, member=12, namespace=3, prototype=47, struct=1
- PrivateDependencyModuleNames: AssetDefinition, CaptureDataCore, Core, CoreUObject, EditorScriptingUtilities, Engine, InputCore, PropertyEditor, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: 

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Private/CaptureDataEditorModule.h` (Private)


#### class `FCaptureDataEditorModule`  
`class FCaptureDataEditorModule : public UE::CaptureManager::ICaptureDataEditorBridge`  
_L8-23_
- inherits: `UE::CaptureManager::ICaptureDataEditorBridge`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`
- L18 _public prototype_ `virtual void DeferMarkDirty(TWeakObjectPtr<UObject> InObject) override;`
- L22 _private member_ `FName CaptureMetadataName;`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Private/Customizations/CaptureMetadataCustomization.h` (Private)


#### class `FCaptureMetadataCustomization`  
`class FCaptureMetadataCustomization : public IDetailCustomization`  
_L9-18_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L16 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Private/DeferredObjectDirtier.h` (Private)


#### class `UE::CaptureManager::FDeferredObjectDirtier`  
`class FDeferredObjectDirtier : public FTickableEditorObject`  
_L12-25_
- inherits: `FTickableEditorObject`
- L15 _public prototype_ `static FDeferredObjectDirtier& Get();`
- L16 _public prototype_ `void Enqueue(TWeakObjectPtr<UObject> InObject);`
- L18 _public prototype_ `virtual void Tick(float InDeltaTime) override;`
- L19 _public prototype_ `virtual bool IsTickable() const override;`
- L20 _public prototype_ `virtual TStatId GetStatId() const override;`
- L23 _private prototype_ `FDeferredObjectDirtier() = default;`
- L24 _private member_ `TArray<TWeakObjectPtr<UObject>> ObjectsToMarkDirty;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace CaptureManager` (scope `UE`)

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/AssetDefinition_CameraCalibration.h` (Public)


#### class `UAssetDefinition_CameraCalibration`  
`class UAssetDefinition_CameraCalibration : public UAssetDefinitionDefault`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual bool CanImport() const override;`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/AssetDefinition_CaptureData.h` (Public)


#### class `UAssetDefinition_MeshCaptureData`  
`class UAssetDefinition_MeshCaptureData : public UAssetDefinitionDefault`  
_L13-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L20 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L21 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L22 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L23 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`

#### class `UAssetDefinition_FootageCaptureData`  
`class UAssetDefinition_FootageCaptureData : public UAssetDefinitionDefault`  
_L31-46_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L38 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L39 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L40 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L41 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L43 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/CameraCalibrationFactory.h` (Public)


#### class `UCameraCalibrationFactory`  
`class UCameraCalibrationFactory : public UFactory`  
_L13-23_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- desc: Implements a factory for UCameraCalibrationFactory objects from file
- L19 _public prototype_ `UCameraCalibrationFactory();`
- L22 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/CameraCalibrationMetadata.h` (Public)


#### class `UCameraCalibrationMetadata`  
`class UCameraCalibrationMetadata : public UBaseCaptureMetadata`  
_L15-44_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UBaseCaptureMetadata`
- L22 _public prototype_ `static void SetCameraCalibrationMetadata(UObject* InObject, const UCameraCalibrationMetadata* InCameraCalibrationMetadata);` — `UFUNCTION(BlueprintCallable, Category = "Camera Calibration Metadata")`
- L25 _public prototype_ `static UCameraCalibrationMetadata* GetCameraCalibrationMetadata(const UObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Camera Calibration Metadata")`
- L28 _public prototype_ `static void ClearCameraCalibrationMetadata(const UObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Camera Calibration Metadata")`
- L31 _public prototype_ `static bool ShowCameraCalibrationMetadataObjects(const FText& InTitle, const TArray<UObject*>& InObjects);` — `UFUNCTION(BlueprintCallable, Category = "Camera Calibration Metadata")`
- L34 _public member_ `double ReprojectionRMSError = 0.0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Camera Calibration Metadata")`
- L37 _public member_ `FTimecode GenerationTimecode;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Camera Calibration Metadata")`
- L40 _public member_ `FFrameRate GenerationFrameRate;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Camera Calibration Metadata")`
- L43 _public member_ `TArray<int32> SelectedFrames;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Camera Calibration Metadata")`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API CAPTUREDATAEDITOR_API`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/CaptureDataFactory.h` (Public)


#### class `UMeshCaptureDataFactory`  
`class UMeshCaptureDataFactory : public UFactory`  
_L14-24_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L21 _public prototype_ `UMeshCaptureDataFactory();`
- L23 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

#### class `UFootageCaptureDataFactory`  
`class UFootageCaptureDataFactory : public UFactory`  
_L30-40_
- reflection: `UCLASS(hideCategories=Object)`
- inherits: `UFactory`
- L37 _public prototype_ `UFootageCaptureDataFactory();`
- L39 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn) override;`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/CaptureMetadata.h` (Public)


#### struct `FCaptureMetadataWindowOptions`  
`struct FCaptureMetadataWindowOptions`  
_L13-19_
- reflection: `USTRUCT(MinimalAPI, BlueprintType, Blueprintable)`
- L18 _public member_ `bool bAllowEdit = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture Metadata | Options")`

#### class `UCaptureMetadata`  
`class UCaptureMetadata : public UBaseCaptureMetadata`  
_L22-50_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UBaseCaptureMetadata`
- L30 _public prototype_ `static void SetCaptureMetadata(UObject* InObject, const UCaptureMetadata* InCaptureMetadata);` — `UFUNCTION(BlueprintCallable, Category = "Capture Metadata")`
- L33 _public prototype_ `static UCaptureMetadata* GetCaptureMetadata(const UObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Capture Metadata")`
- L36 _public prototype_ `static void ClearCaptureMetadata(const UObject* InObject);` — `UFUNCTION(BlueprintCallable, Category = "Capture Metadata")`
- L39 _public prototype_ `static bool ShowCaptureMetadataObjects(const FText& InTitle, const TArray<UObject*>& InObjects, const FCaptureMetadataWindowOptions& InOptions);` — `UFUNCTION(BlueprintCallable, Category = "Capture Metadata")`
- L42 _public member_ `FString CameraId;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Capture Metadata")`
- L44 _public prototype_ `bool IsEditable() const;`
- L45 _public prototype_ `FString GetOwnerName() const;`
- L49 _private member_ `bool bIsEditable = true;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API CAPTUREDATAEDITOR_API`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/Customizations/CaptureDataCustomizations.h` (Public)


#### class `FFootageCaptureDataCustomization`  
`class FFootageCaptureDataCustomization : public IDetailCustomization`  
_L11-20_
- inherits: `IDetailCustomization`
- L15 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API CAPTUREDATAEDITOR_API`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/FrameRangeArrayBuilder.h` (Public)


#### class `FFrameRangeArrayBuilder`  
`class FFrameRangeArrayBuilder : public FDetailArrayBuilder`  
_L10-24_
- inherits: `FDetailArrayBuilder`
- L14 _public prototype_ `DECLARE_DELEGATE_RetVal(FFrameNumber, FOnGetCurrentFrame);`
- L16 _public prototype_ `FFrameRangeArrayBuilder(TSharedRef<IPropertyHandle> InBaseProperty, TArray<FFrameRange>& InOutFrameRange, FOnGetCurrentFrame* InOnGetCurrentFrameDelegate = nullptr);`
- L18 _public prototype_ `virtual void GenerateChildContent(IDetailChildrenBuilder& InOutChildrenBuilder) override;`
- L22 _private member_ `TArray<FFrameRange>& FrameRange;`
- L23 _private member_ `FOnGetCurrentFrame* OnGetCurrentFrameDelegate = nullptr;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API CAPTUREDATAEDITOR_API`
- L14 _delegate_ `DECLARE_DELEGATE_RetVal(FFrameNumber, FOnGetCurrentFrame);`

### `Plugins/VirtualProduction/CaptureData/Source/CaptureDataEditor/Public/Metadata/MetadataHandler.h` (Public)


#### class `UBaseCaptureMetadata`  
`class UBaseCaptureMetadata : public UObject`  
_L13-21_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UObject`
- L20 _public member_ `FName OwnerName;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Base Capture Metadata")`

#### Free symbols / members of external scopes

- L23 _namespace_ `namespace UE`
- L28 _function_ `template<typename T> requires UE::CDerivedFrom<T, UBaseCaptureMetadata> void SetMetadataObject(UObject* InObject, T* InMetadata)` (scope `UE`)
- L84 _function_ `template<typename T> requires UE::CDerivedFrom<T, UBaseCaptureMetadata> T* GetMetadataObject(const UObject* InObject)` (scope `UE`)
- L127 _function_ `template<typename T> requires UE::CDerivedFrom<T, UBaseCaptureMetadata> void ClearMetadataObject(const UObject* InObject)` (scope `UE`)
- L168 _prototype_ `bool ShowMetadataObjects(const FText& InTitle, const TArray<UObject*>& InObjects);` (scope `UE`)
