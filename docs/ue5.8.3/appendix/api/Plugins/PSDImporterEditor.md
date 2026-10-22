# Plugins / PSDImporterEditor

- module root: `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor`
- headers: 14; symbols: 132
- symbol kinds: class=11, delegate=1, function=2, member=24, namespace=7, prototype=85, struct=1, variable=1
- PrivateDependencyModuleNames: AssetDefinition, DeveloperSettings, EditorFramework, EditorSubsystem, Engine, ImageCore, InputCore, MaterialEditor, PSDImporter, Projects, PsdSDK, SequencerCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, PSDImporterCore

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/AssetDefinition_PSDDocument.h` (Private)


#### class `UAssetDefinition_PSDDocument`  
`class UAssetDefinition_PSDDocument : public UAssetDefinitionDefault`  
_L10-23_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L17 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L18 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L19 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L21 _public prototype_ `virtual bool CanImport() const override;`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Customizations/PSDActorCustomization.h` (Private)


#### class `UE::PSDImporterEditor::FPSDActorCustomization`  
`class FPSDActorCustomization : public IDetailCustomization`  
_L11-20_
- inherits: `IDetailCustomization`
- desc: Sorts the PSD category to the top.
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L18 _protected prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace PSDImporterEditor` (scope `UE`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Customizations/PSDLayerCustomization.h` (Private)


#### class `UE::PSDImporterEditor::FPSDLayerCustomization`  
`class FPSDLayerCustomization : public IPropertyTypeCustomization , public FGCObject`  
_L19-85_
- inherits: `IPropertyTypeCustomization,FGCObject`
- L24 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L26 _public prototype_ `FPSDLayerCustomization();`
- L29 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`
- L31 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override`
- L36 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& InCollector) override;`
- L37 _public prototype_ `virtual FString GetReferencerName() const override;`
- L41 _private prototype_ `void OnThumbnailChanged();`
- L42 _private prototype_ `void OnLayerTextureChanged();`
- L43 _private prototype_ `void OnMaskTextureChanged();`
- L45 _private prototype_ `FPSDFileLayer* GetLayer() const;`
- L47 _private prototype_ `const FSlateBrush* GetVisibilityBrush() const;`
- L48 _private prototype_ `const FSlateBrush* GetLayerThumbnailBrush() const;`
- L49 _private prototype_ `EVisibility GetToolTipLayerThumbnailVisibility() const;`
- L50 _private prototype_ `const FSlateBrush* GetToolTipLayerThumbnailBrush() const;`
- L51 _private prototype_ `const FSlateBrush* GetMaskThumbnailBrush() const;`
- L52 _private prototype_ `EVisibility GetToolTipMaskThumbnailVisibility() const;`
- L53 _private prototype_ `const FSlateBrush* GetToolTipMaskThumbnailBrush() const;`
- L55 _private prototype_ `void UpdateLayerThumbnail(UTexture2D* InTexture);`
- L56 _private prototype_ `void UpdateLayerToolTipThumbnail(UTexture2D* InTexture);`
- L57 _private prototype_ `void UpdateMaskThumbnail(UTexture2D* InTexture);`
- L58 _private prototype_ `void UpdateMaskToolTipThumbnail(UTexture2D* InTexture);`
- L59 _private prototype_ `void UpdateThumbnailInternal(UTexture2D* InTexture, UMaterialInstanceDynamic* InMID, const TSharedPtr<FSlateBrush>& InBrush, TOptional<int32> InMaxSize = {});`
- L61 _private prototype_ `bool IsLoading() const;`
- L64 _private member_ `const FSlateBrush* VisibleBrush;`
- L65 _private member_ `const FSlateBrush* NotVisibleBrush;`
- L67 _private member_ `FSoftObjectPath ThumbnailMaterialPath;`
- L69 _private member_ `TObjectPtr<UMaterialInstanceDynamic> LayerThumbnailMID;`
- L70 _private member_ `TSharedPtr<FSlateBrush> LayerThumbnailBrush;`
- L72 _private member_ `TObjectPtr<UMaterialInstanceDynamic> LayerToolTipThumbnailMID;`
- L73 _private member_ `TSharedPtr<FSlateBrush> LayerToolTipThumbnailBrush;`
- L75 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MaskThumbnailMID;`
- L76 _private member_ `TSharedPtr<FSlateBrush> MaskThumbnailBrush;`
- L78 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MaskToolTipThumbnailMID;`
- L79 _private member_ `TSharedPtr<FSlateBrush> MaskToolTipThumbnailBrush;`
- L81 _private member_ `TSharedPtr<IPropertyHandle> LayerHandle;`
- L82 _private member_ `TSharedPtr<IPropertyHandle> ThumbnailHandle;`
- L83 _private member_ `TSharedPtr<IPropertyHandle> LayerTextureHandle;`
- L84 _private member_ `TSharedPtr<IPropertyHandle> MaskTextureHandle;`

#### Free symbols / members of external scopes

- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace PSDImporterEditor` (scope `UE`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Factories/ActorFactoryPSDDocument.h` (Private)


#### class `UActorFactoryPSDDocument`  
`class UActorFactoryPSDDocument : public UActorFactory`  
_L12-26_
- reflection: `UCLASS()`
- inherits: `UActorFactory`
- L17 _public prototype_ `UActorFactoryPSDDocument();`
- L20 _public prototype_ `virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;`
- L21 _public prototype_ `virtual UClass* GetDefaultActorClass(const FAssetData& AssetData) override;`
- L22 _public prototype_ `virtual void PostSpawnActor(UObject* Asset, AActor* NewActor) override;`
- L23 _public prototype_ `virtual UObject* GetAssetFromActorInstance(AActor* ActorInstance) override;`
- L24 _public prototype_ `virtual FQuat AlignObjectToSurfaceNormal(const FVector& InSurfaceNormal, const FQuat& ActorRotation) const override;`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Factories/PSDDocumentImportFactory.h` (Private)


#### class `UPSDDocumentImportFactory`  
`class UPSDDocumentImportFactory : public UFactory , public FReimportHandler`  
_L13-35_
- reflection: `UCLASS()`
- inherits: `UFactory,FReimportHandler`
- L20 _public prototype_ `UPSDDocumentImportFactory();`
- L23 _public prototype_ `virtual UObject* FactoryCreateFile(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, const FString& InFilename, const TCHAR* InParams, FFeedbackContext* InWarn, bool& bInOutOperationCanceled) override;`
- L28 _public prototype_ `virtual bool CanReimport(UObject* InObj, TArray<FString>& OutFilenames) override;`
- L29 _public prototype_ `virtual void SetReimportPaths(UObject* InObj, const TArray<FString>& InNewReimportPaths) override;`
- L30 _public prototype_ `virtual EReimportResult::Type Reimport(UObject* InObj) override;`
- L34 _private prototype_ `bool Import(const FString& InFilePath, UPSDDocument* InDocument);`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Factories/PSDDocumentImportFactory_Visitors.h` (Private)


#### struct `FPSDDocumentImportFactory_Visitors`  
`struct FPSDDocumentImportFactory_Visitors : UE::PSDImporter::FPSDFileImportVisitors`  
_L14-39_
- inherits: `UE::PSDImporter::FPSDFileImportVisitors`
- L16 _public prototype_ `explicit FPSDDocumentImportFactory_Visitors(const FString& InFilePath, UPSDDocument* InDocument);`
- L18 _public prototype_ `virtual void OnImportComplete() override;`
- L20 _public prototype_ `virtual void OnImportHeader(const FHeaderInputType& InHeader) override;`
- L22 _public prototype_ `virtual void OnImportLayers(const FLayersInputType& InLayers) override;`
- L24 _public prototype_ `virtual void OnImportLayer(const FLayerInputType& InLayer, const FLayerInputType* InParentLayer, TFunction<TFuture<FImage>()> InReadLayerData, TFunction<TFuture<FImage>()> InReadMaskData) override;`
- L28 _private prototype_ `UObject* MakeAsset(UClass* InClass, const FString& InDocumentName, const FString& InAssetName, const FString& InAssetPrefix);`
- L30 _private prototype_ `void MakeAssetPath(const FString& InDocumentName, const FString& InAssetName, const FString& InAssetPrefix, FString& OutPath, FString& OutName) const;`
- L33 _private member_ `FString FilePath;`
- L34 _private member_ `TStrongObjectPtr<UPSDDocument> Document;`
- L35 _private member_ `FPSDFileDocument& FileDocument;`
- L36 _private member_ `TSet<FPSDFileLayer> OldLayers;`
- L37 _private member_ `TSet<FPSDFileLayer> NewLayers;`
- L38 _private member_ `TSet<FString> ImportedAssets;`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Factories/PSDImporterLayeredMaterialFactory.h` (Private)


#### class `UPSDImporterLayeredMaterialFactory`  
`class UPSDImporterLayeredMaterialFactory : public UObject`  
_L20-44_
- reflection: `UCLASS()`
- inherits: `UObject`
- L25 _public prototype_ `virtual ~UPSDImporterLayeredMaterialFactory() override = default;`
- L27 _public prototype_ `bool CanCreateMaterial(const UPSDDocument* InDocument) const;`
- L29 _public prototype_ `UMaterial* CreateMaterial(const UPSDDocument* InDocument) const;`
- L32 _protected prototype_ `UMaterial* CreateMaterialAsset(const UPSDDocument& InDocument) const;`
- L34 _protected prototype_ `UMaterialExpression* CreateLayers(UMaterial& InMaterial, const UPSDDocument& InDocument) const;`
- L36 _protected prototype_ `UMaterialExpressionMaterialFunctionCall* CreateLayer(UMaterial& InMaterial, const UPSDDocument& InDocument, const FPSDFileLayer& InLayer) const;`
- L37 _protected prototype_ `UMaterialExpressionTextureSample* CreateLayer_Base(UMaterial& InMaterial, const FPSDFileLayer& InLayer) const;`
- L38 _protected prototype_ `UMaterialExpressionMaterialFunctionCall* CreateLayer_NoCrop(UMaterial& InMaterial, const FPSDFileLayer& InLayer) const;`
- L39 _protected prototype_ `UMaterialExpressionMaterialFunctionCall* CreateLayer_Crop(UMaterial& InMaterial, const FPSDFileLayer& InLayer, const FIntPoint& InSize, const FIntRect& InBounds) const;`
- L41 _protected prototype_ `UMaterialExpressionMaterialFunctionCall* CreateLayer_NoCrop_Mask(UMaterial& InMaterial, const FPSDFileLayer& InLayer) const;`
- L42 _protected prototype_ `UMaterialExpressionMaterialFunctionCall* CreateLayer_Crop_Mask(UMaterial& InMaterial, const FPSDFileLayer& InLayer, const FIntPoint& InLayerSize, const FIntRect& InLayerBounds, const FIntRect& InMaskBounds) const;`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Factories/PSDQuadsFactory.h` (Private)


#### class `UPSDQuadsFactory`  
`class UPSDQuadsFactory : public UObject`  
_L15-28_
- reflection: `UCLASS()`
- inherits: `UObject`
- L20 _public prototype_ `virtual ~UPSDQuadsFactory() override = default;`
- L22 _public prototype_ `APSDQuadActor* CreateQuadActor(UWorld& InWorld, UPSDDocument& InDocument) const;`
- L24 _public prototype_ `void CreateQuads(APSDQuadActor& InQuadActor) const;`
- L27 _protected prototype_ `APSDQuadMeshActor* CreateQuad(APSDQuadActor& InQuadActor, int32 InLayerIndex) const;`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/PSDImporterContentBrowserIntegration.h` (Private)


#### class `FPSDImporterContentBrowserIntegration`  
`class FPSDImporterContentBrowserIntegration`  
_L13-32_
- L16 _public prototype_ `static FPSDImporterContentBrowserIntegration& Get();`
- L18 _public prototype_ `void Integrate();`
- L20 _public prototype_ `void Disintegrate();`
- L23 _protected prototype_ `TSharedRef<FExtender> OnExtendContentBrowserAssetSelectionMenu(const TArray<FAssetData>& InSelectedAssets);`
- L25 _protected prototype_ `void CreateMenuEntries(FMenuBuilder& InMenuBuilder, TArray<FAssetData> InSelectedAssets);`
- L27 _protected prototype_ `void CreatePSDMaterial(TArray<FAssetData> InSelectedAssets);`
- L29 _protected prototype_ `void CreatePSDQuads(TArray<FAssetData> InSelectedAssets);`
- L31 _protected member_ `FDelegateHandle ContentBrowserHandle;`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/PSDImporterEditorLog.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPSDImporterEditor, All, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPSDImporterEditor, All, All);`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/PSDImporterEditorSettings.h` (Private)


#### class `UPSDImporterEditorSettings`  
`class UPSDImporterEditorSettings : public UDeveloperSettings`  
_L13-28_
- reflection: `UCLASS(Config = EditorPerProjectUserSettings, meta = (DisplayName = "PSD Importer"))`
- inherits: `UDeveloperSettings`
- desc: DM Texture Set Settings
- L18 _public prototype_ `UPSDImporterEditorSettings();`
- L19 _public prototype_ `virtual ~UPSDImporterEditorSettings() override = default;`
- L21 _public prototype_ `static UPSDImporterEditorSettings* Get();`
- L24 _public member_ `bool bResizeLayersToDocument;` — `UPROPERTY(Config, EditAnywhere, Category = "PSD Importer|Importer Defaults")`
- L27 _public member_ `bool bImportInvisibleLayers;` — `UPROPERTY(Config, EditAnywhere, Category = "PSD Importer|Importer Defaults")`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/PSDImporterEditorUtilities.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace PSDImporterEditor` (scope `UE`)
- L10 _namespace_ `namespace Private` (scope `UE::PSDImporterEditor`)
- L13 _variable_ `constexpr double InitialScale = 0.52;` (scope `UE::PSDImporterEditor::Private`) — Makes a document at 1080p fit the viewport on initial import.
- L17 _prototype_ `FIntPoint FitMinClampMaxXY(const FIntPoint& InSource, const int32 InMinSize, const int32 InMaxSize);` (scope `UE::PSDImporterEditor::Private`) — Calculate an X and Y scale such that no one axis is smaller than MinSize, and then none larger than MaxSize. The output can be therefore be smaller than MinSize, but not larger than MaxSize.
- L19 _prototype_ `FVector2D FitMinClampMaxXY(const FVector2D& InSource, const int32 InMinSize, const int32 InMaxSize);` (scope `UE::PSDImporterEditor::Private`)
- L21 _prototype_ `void SelectLayerTextureAsset(const FPSDFileLayer& InLayer);` (scope `UE::PSDImporterEditor::Private`)
- L23 _prototype_ `void SelectMaskTextureAsset(const FPSDFileLayer& InLayer);` (scope `UE::PSDImporterEditor::Private`)
- L29 _prototype_ `bool AddOpacityParameterNodes(UMaterial& InMaterial);` (scope `UE::PSDImporterEditor::Private`) — Adds the global opacity parameter and, if it can, the geometry mask apply node. Returns true if the material attribute input was changed.
- L31 _prototype_ `EPSDImporterLayerMaterialType GetLayerMaterialType(const TArray<FPSDFileLayer>& InLayers, int32 InLayerIndex);` (scope `UE::PSDImporterEditor::Private`)

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Utils/PSDImporterMaterialLibrary.h` (Private)


#### class `FPSDImporterMaterialLibrary`  
`class FPSDImporterMaterialLibrary`  
_L13-27_
- L16 _public prototype_ `static UMaterialFunctionInterface* GetMaterialFunction(const TCHAR* InFunctionPath);`
- L18 _public prototype_ `static UMaterialExpression* CreateExpression(UMaterial& InMaterial, UClass& InExpressionClass);`
- L21 _public function_ `template<typename InExpressionType> static InExpressionType* CreateExpression(UMaterial& InMaterial)`
- L26 _public prototype_ `static void ResetTexture(APSDQuadMeshActor& InQuadMeshActor);`

### `Plugins/Experimental/PSDImporter/Source/PSDImporterEditor/Private/Utils/PSDImporterMaterialNodeArranger.h` (Private)


#### class `FPSDImporterMaterialNodeArranger`  
`class FPSDImporterMaterialNodeArranger`  
_L10-17_
- L13 _public prototype_ `static void ArrangeNodes(const FExpressionInput& InMaterialChannelInput);`
- L16 _private prototype_ `static void ArrangeNodes(UMaterialExpression& InExpression, FIntPoint InPosition);`
