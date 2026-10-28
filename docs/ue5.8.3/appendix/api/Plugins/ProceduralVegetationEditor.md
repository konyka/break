# Plugins / ProceduralVegetationEditor

- module root: `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor`
- headers: 39; symbols: 764
- symbol kinds: class=43, delegate=6, enum=5, enumerator=26, externvar=6, function=22, member=205, namespace=22, prototype=402, struct=14, typedef=4, variable=9
- PrivateDependencyModuleNames: AdvancedPreviewScene, AssetDefinition, AssetTools, Chaos, ContentBrowser, ContentBrowserData, Core, CoreUObject, CurveEditor, DataflowEditor, DynamicWind, DynamicWindEditor, EditorFramework, EditorWidgets, Engine, GeometryCore, GeometryFramework, GeometryScriptingCore, InputCore, InteractiveToolsFramework, Json, JsonUtilities, LevelEditor, MeshConversion, MeshConversionEngineTypes, ModelingComponents, PCG, PCGEditor, PackagesDialog, PlanarCut, ProceduralVegetation, Projects, PropertyEditor, RHI, RenderCore, SkeletalMeshDescription, Slate, SlateCore, StaticMeshDescription, ToolMenus, ToolWidgets, UnrealEd

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/AssetDefinition_ProceduralVegetation.h` (Private)


#### class `UAssetDefinition_ProceduralVegetation`  
`class UAssetDefinition_ProceduralVegetation : public UAssetDefinitionDefault`  
_L9-19_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public prototype_ `virtual FText GetAssetDisplayName() const override;`
- L15 _public prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L16 _public prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L17 _public prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L18 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/PVColliderParamsCustomization.h` (Private)


#### class `FPVColliderParamsCustomization`  
`class FPVColliderParamsCustomization : public IPropertyTypeCustomization`  
_L8-28_
- inherits: `IPropertyTypeCustomization`
- L11 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L13 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L19 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L27 _private prototype_ `void CustomizeColliderSelectorWidget(const TSharedPtr<IPropertyHandle>& InChildHandle, IDetailPropertyRow& InRowBuilder);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/PVFloatRampCustomization.h` (Private)


#### class `FPVFloatRampOwner`  
`class FPVFloatRampOwner : public FCurveOwnerInterface`  
_L14-59_
- inherits: `FCurveOwnerInterface`
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFloatRampChanged, FRichCurve* );`
- L20 _public prototype_ `FPVFloatRampOwner(FRichCurve* InCurve, const FName InCurveName = NAME_None);`
- L21 _public prototype_ `FPVFloatRampOwner(const FPVFloatRampOwner& Other);`
- L22 _public prototype_ `FPVFloatRampOwner& operator=(const FPVFloatRampOwner& Other);`
- L24 _public prototype_ `FPVFloatRampOwner(FPVFloatRampOwner&& Other) = delete;`
- L25 _public prototype_ `FPVFloatRampOwner& operator=(FPVFloatRampOwner&& Other) = delete;`
- L28 _public prototype_ `virtual TArray<FRichCurveEditInfoConst> GetCurves() const override;` — `UE_DEPRECATED(5.6, "Use version taking a TAdderReserverRef")`
- L29 _public prototype_ `virtual void GetCurves(TAdderReserverRef<FRichCurveEditInfoConst> Curves) const override;`
- L30 _public prototype_ `virtual TArray<FRichCurveEditInfo> GetCurves() override;`
- L32 _public prototype_ `const FName& GetCurveName() const;`
- L33 _public prototype_ `void SetCurveName(const FName InName);`
- L34 _public prototype_ `void SetCurve(FRichCurve* InCurve);`
- L35 _public prototype_ `FRichCurve& GetRichCurve();`
- L36 _public prototype_ `const FRichCurve& GetRichCurve() const;`
- L38 _public prototype_ `void SetOwner(UObject* InOwner);`
- L39 _public prototype_ `UObject* GetOwner();`
- L40 _public prototype_ `const UObject* GetOwner() const;`
- L41 _public prototype_ `virtual TArray<const UObject*> GetOwners() const override;`
- L42 _public prototype_ `virtual void ModifyOwner() override;`
- L43 _public prototype_ `virtual void MakeTransactional() override;`
- L45 _public prototype_ `virtual void OnCurveChanged(const TArray<FRichCurveEditInfo>& ChangedCurveEditInfos) override;`
- L46 _public prototype_ `virtual bool IsValidCurve(FRichCurveEditInfo CurveInfo) override;`
- L48 _public prototype_ `FOnFloatRampChanged& OnFloatRampChanged();`
- L51 _private member_ `FRichCurve* FloatCurve;`
- L53 _private member_ `TObjectPtr<UObject> CurveOwner;`
- L55 _private member_ `FRichCurveEditInfo FloatCurveEditInfo;`
- L56 _private member_ `FRichCurveEditInfoConst ConstFloatCurveEditInfo;`
- L58 _private member_ `FOnFloatRampChanged OnFloatRampChangedDelegate;`

#### class `FPVFloatRampCustomization`  
`class FPVFloatRampCustomization : public IPropertyTypeCustomization, FEditorUndoClient`  
_L61-116_
- inherits: `IPropertyTypeCustomization,FEditorUndoClient`
- L64 _public prototype_ `FPVFloatRampCustomization();`
- L67 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L69 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L75 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L82 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L83 _public prototype_ `virtual void PostRedo(bool bSuccess) override;`
- L86 _private prototype_ `SCurveEditor::FArguments GetCurveEditorArgs(const TSharedRef<IPropertyHandle>& InPropertyHandle);`
- L88 _private prototype_ `TSharedRef<SCurveEditor> CreateCurveEditor(const SCurveEditor::FArguments& Args) const;`
- L89 _private prototype_ `TSharedRef<SWidget> CreateRampValueWidget(const TSharedRef<SWidget>& ChildContent, bool bIsWindowWidget = false);`
- L90 _private prototype_ `TSharedRef<SWidget> CreateRampControlsWidget(bool bIsWindowWidget = false);`
- L92 _private prototype_ `void OnRampPresetSelected(const FString& Selection) const;`
- L94 _private prototype_ `FReply OnRampPreviewDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L95 _private prototype_ `void DestroyPopOutWindow();`
- L98 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L100 _private member_ `FPVFloatRamp* FloatRamp = nullptr;`
- L101 _private member_ `TUniquePtr<FPVFloatRampOwner> FloatRampOwner;`
- L103 _private member_ `bool bHasHorizontalRange = false;`
- L104 _private member_ `bool bHasVerticalRange = false;`
- L106 _private member_ `TSharedPtr<SCurveEditor> CurveEditor;`
- L108 _private member_ `TWeakPtr<SWindow> CurveEditorWindow;`
- L110 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L111 _private member_ `FCurveEditorCommands* CurveEditorCommands;`
- L113 _private member_ `TSharedPtr<SComboBox<TSharedPtr<FString>>> PresetsComboBox;`
- L115 _private member_ `static const FVector2D DEFAULT_WINDOW_SIZE;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnFloatRampChanged, FRichCurve* );`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/PVGrowerSettingsCustomization.h` (Private)


#### class `FPVGrowerSettingsCustomization`  
`class FPVGrowerSettingsCustomization : public IDetailCustomization`  
_L9-18_
- inherits: `IDetailCustomization`
- L12 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L13 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L17 _private member_ `static FString ActiveSection;` — Persists across panel instances; Slate visibility lambdas read it every tick.

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/PVImportStaticMeshParamsCustomization.h` (Private)


#### class `FPVImportStaticMeshParamsCustomization`  
`class FPVImportStaticMeshParamsCustomization : public IPropertyTypeCustomization`  
_L9-25_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L20 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/PVLoopDebugStepperCustomization.h` (Private)


#### class `FPVLoopDebugStepperCustomization`  
`class FPVLoopDebugStepperCustomization : public IPropertyTypeCustomization`  
_L9-31_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L20 _public prototype_ `virtual void CustomizeChildren( TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils ) override;`
- L28 _private member_ `FLoopDebugStepper* LoopDebugStepper = nullptr;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> PropertyHandle = nullptr;`
- L30 _private member_ `UObject* ParentObject = nullptr;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/PVOutputSettingsCustomizations.h` (Private)


#### class `FPVOutputSettingsCustomizations`  
`class FPVOutputSettingsCustomizations : public IPropertyTypeCustomization`  
_L9-21_
- inherits: `IPropertyTypeCustomization`
- L12 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L14 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L15 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L16 _public prototype_ `FText GetWarningTextForAssemblies() const;`
- L19 _private prototype_ `void CustomizeNaniteAssembliesWidget(const TSharedPtr<IPropertyHandle>& ChildHandle, IDetailPropertyRow& RowBuilder);`
- L20 _private prototype_ `void CustomizeNaniteShapePreservationWidget(const TSharedPtr<IPropertyHandle>& ChildHandle, IDetailPropertyRow& RowBuilder);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/PVTrunkTextureSetupSettingsCustomization.h` (Private)


#### class `FPVTrunkTextureSetupSettingsCustomization`  
`class FPVTrunkTextureSetupSettingsCustomization : public IDetailCustomization`  
_L10-23_
- inherits: `IDetailCustomization`
- L13 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L18 _private prototype_ `bool BakeTexturesButtonEnabled() const;`
- L19 _private prototype_ `FReply OnBakeTexturesClicked();`
- L22 _private member_ `TArray<TWeakObjectPtr<UPVTrunkTextureSetupSettings>> SelectedSettings;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Customizations/RichTextColorDecorator.h` (Private)


#### class `FColorBlockTextRun`  
`class FColorBlockTextRun : public FSlateTextRun`  
_L10-42_
- inherits: `FSlateTextRun`
- L13 _public prototype_ `FColorBlockTextRun( const FRunInfo& InRunInfo, const TSharedRef<const FString>& InText, const FTextBlockStyle& InStyle, const FTextRange& InRange, const FLinearColor& InBg );`
- L21 _public prototype_ `static TSharedRef<FColorBlockTextRun> Create( const FRunInfo& InRunInfo, const TSharedRef<const FString>& InText, const FTextBlockStyle& InStyle, const FTextRange& InRange, const FLinearColor& InBg );`
- L29 _public prototype_ `virtual int32 OnPaint( const FPaintArgs& Args, const FTextArgs& TextArgs, const FGeometry& Allotted, const FSlateRect& Culling, FSlateWindowElementList& Out, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;`
- L41 _private member_ `FLinearColor BgColor;`

#### class `FColorBlockDecorator`  
`class FColorBlockDecorator : public ITextDecorator`  
_L44-58_
- inherits: `ITextDecorator`
- L47 _public prototype_ `static TSharedRef<FColorBlockDecorator> CreateDecorator();`
- L49 _public prototype_ `virtual bool Supports(const FTextRunParseResults& RunParseResults, const FString& Text) const override;`
- L51 _public prototype_ `virtual TSharedRef<ISlateRun> Create( const TSharedRef<FTextLayout>& TextLayout, const FTextRunParseResults& RunInfo, const FString& OriginalText, const TSharedRef<FString>& ModelText, const ISlateStyle* Style ) override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Exporter/PVExporter.h` (Private)


#### struct `FPVOutputEntryStats`  
`struct FPVOutputEntryStats`  
_L15-41_
- reflection: `USTRUCT()`
- L20 _public member_ `int32 NumPoints = -1;` — `UPROPERTY(VisibleAnywhere, Category="Stats", meta=(EditCondition="NumPoints != -1"))`
- L23 _public member_ `int32 NumBranches = -1;` — `UPROPERTY(VisibleAnywhere, Category="Stats", meta=(EditCondition="NumBranches != -1"))`
- L26 _public member_ `int32 NumVertices = -1;` — `UPROPERTY(VisibleAnywhere, Category="Stats", DisplayName="Num Vertices (Trunk)", meta=(EditCondition="NumVertices != -1"))`
- L29 _public member_ `int32 NumTris = -1;` — `UPROPERTY(VisibleAnywhere, Category="Stats", DisplayName="Num Triangles (Trunk)", meta=(EditCondition="NumTris != -1"))`
- L32 _public member_ `int32 NumBones = -1;` — `UPROPERTY(VisibleAnywhere, Category="Stats", meta=(EditCondition="NumBones != -1"))`
- L35 _public member_ `int32 NumFoliage = -1;` — `UPROPERTY(VisibleAnywhere, Category="Stats", meta=(EditCondition="NumFoliage != -1"))`
- L38 _public member_ `int32 NumFoliageInstances = -1;` — `UPROPERTY(VisibleAnywhere, Category="Stats", meta=(EditCondition="NumFoliageInstances != -1"))`
- L40 _public prototype_ `void SetupStats(const FManagedArrayCollection& InCollection);`

#### class `UPVExportEntry`  
`class UPVExportEntry : public UObject`  
_L44-75_
- reflection: `UCLASS()`
- inherits: `UObject`
- L50 _public member_ `bool bExport = true;` — `UPROPERTY(Transient)`
- L53 _public member_ `bool bIsNodeSelected = false;` — `UPROPERTY(Transient)`
- L56 _public member_ `TObjectPtr<UPCGNode> Node = nullptr;` — `UPROPERTY(Transient)`
- L59 _public member_ `bool bExportFoliage = true;` — `UPROPERTY(VisibleAnywhere, Category="Stats", DisplayName="Has Foliage")`
- L62 _public member_ `FPVOutputEntryStats Stats;` — `UPROPERTY(VisibleAnywhere, Category="Stats", meta=(ShowOnlyInnerProperties))`
- L65 _public member_ `TObjectPtr<UPVExportSettings> Settings = nullptr;` — `UPROPERTY(EditAnywhere, Category="Export Settings", meta=(ShowOnlyInnerProperties))`
- L67 _public member_ `TSharedPtr<FManagedArrayCollection> OutputCollection;`
- L69 _public prototype_ `void Initialize( const TSharedPtr<FManagedArrayCollection>& InCollection, const TObjectPtr<UPCGNode> InNode, bool InIsNodeSelected = false, bool InHasFoliage = true );`

#### class `FPVExporter`  
`class FPVExporter`  
_L77-108_
- L94 _public prototype_ `FPVExporter(TObjectPtr<UProceduralVegetation> InProceduralVegetation, const TArray<TObjectPtr<UPVExportEntry>>& InExportEntries);`
- L96 _public prototype_ `bool Export();`
- L99 _private prototype_ `bool ValidateExportEntries();`
- L100 _private prototype_ `bool ShouldOverwriteAssets();`
- L103 _private member_ `TObjectPtr<UProceduralVegetation> ProceduralVegetation = nullptr;`
- L105 _private member_ `TArray<TObjectPtr<UPVExportEntry>> ExportEntries;`
- L107 _private member_ `FScopedMessages Messages;`

#### struct `FPVExporter::FScopedMessages`  
`struct FScopedMessages`  
_L79-91_
- L81 _public prototype_ `TSharedRef<FTokenizedMessage> Error(const FText& ErrorMsg);`
- L82 _public prototype_ `TSharedRef<FTokenizedMessage> Warning(const FText& ErrorMsg);`
- L83 _public prototype_ `TSharedRef<FTokenizedMessage> Info(const FText& ErrorMsg);`
- L85 _public prototype_ `~FScopedMessages();`
- L88 _private prototype_ `bool ContainsErrors() const;`
- L90 _private member_ `TArray<TSharedRef<FTokenizedMessage>> Messages;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Helpers/PVExportHelper.h` (Private)


#### enum `PV::Export::EExportResult`  
`enum class EExportResult`  
_L33-39_
- L35 _public enumerator_ `Success`
- L36 _public enumerator_ `Fail`
- L37 _public enumerator_ `Cancelled`
- L38 _public enumerator_ `Skipped`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Geometry` (scope `UE`)
- L29 _namespace_ `namespace PV`
- L29 _namespace_ `namespace Export` (scope `PV`)
- L31 _typedef_ `typedef TFunction<bool(const FText& Stage, float Progress)> FStatusReportCallback;` (scope `PV::Export`)
- L41 _prototype_ `EExportResult ExportCollectionAsMesh( const TObjectPtr<UProceduralVegetation> InProceduralVegetation, const FManagedArrayCollection& Collection, const TObjectPtr<UPVExportEntry>& ExportEntry, TArray<FString>& OutCreatedAssets, const FStatusReportCallback& StatusReportCallback );` (scope `PV::Export`)
- L50 _namespace_ `namespace PV`
- L50 _namespace_ `namespace Export` (scope `PV`)
- L50 _namespace_ `namespace Internal` (scope `PV::Export`)
- L52 _typedef_ `typedef TFunction<void(const FString& MeshName, int32 InstanceID, int32 VertexStart, int32 VertexCount)> FMeshInstanceCombined;` (scope `PV::Export::Internal`)
- L54 _prototype_ `TObjectPtr<UDynamicMesh> CollectionToDynamicMesh(const FManagedArrayCollection& Collection);` (scope `PV::Export::Internal`)
- L56 _prototype_ `FGeometryScriptCopyMeshToAssetOptions GetCopyMeshToAssetOptions( const TArray<TObjectPtr<UMaterialInterface>>& InMaterials, const FMeshNaniteSettings& InNaniteSettings, const ENaniteShapePreservation InShapePreservation );` (scope `PV::Export::Internal`)
- L62 _prototype_ `bool CombineMeshInstancesToDynamicMesh( const FManagedArrayCollection& Collection, UDynamicMesh* DynamicMesh, TArray<TObjectPtr<UMaterialInterface>>& Materials, const FMeshInstanceCombined& OnMeshInstanceCombined, const TFunction<bool(float)>& OnProgressUpdated );` (scope `PV::Export::Internal`)
- L70 _prototype_ `void BuildNaniteAssemblyData( const FManagedArrayCollection& Collection, UStaticMesh* StaticMesh, TArray<UPackage*>& OutModifiedPackages );` (scope `PV::Export::Internal`)
- L76 _prototype_ `void AddNodeToBuilder( FNaniteAssemblyDataBuilder& AssemblyBuilder, const FManagedArrayCollection& Collection, const TMap<FString, int32>& InMeshNamePartMap, const TMap<FString, TArray<TObjectPtr<UMaterialInterface>>>& InMeshMaterialsMap );` (scope `PV::Export::Internal`)
- L83 _prototype_ `bool ExportCollectionToStaticMesh( TObjectPtr<UStaticMesh> ExportMesh, const FManagedArrayCollection& Collection, ENaniteShapePreservation InShapePreservation, bool bBuildNaniteAssemblies, bool bShouldExportFoliage, bool bCollision, TArray<UPackage*>& OutModifiedPackages, const FStatusReportCallback& StatusReportCallback );` (scope `PV::Export::Internal`)
- L94 _prototype_ `bool ExportCollectionToSkeletalMesh( TObjectPtr<USkeletalMesh> ExportMesh, const FManagedArrayCollection& Collection, ENaniteShapePreservation InShapePreservation, TObjectPtr<const UPVWindSettings> InWindSettings, TObjectPtr<UPhysicsAsset> InPhysicsAsset, bool bBuildNaniteAssemblies, bool bShouldExportFoliage, EPVCollisionGeneration CollisionGeneration, TArray<UPackage*>& OutModifiedPackages, const FStatusReportCallback& StatusReportCallback );` (scope `PV::Export::Internal`)
- L107 _prototype_ `void AttachProceduralVegetationLink(UObject* InExportedMesh, const TObjectPtr<UProceduralVegetation>& InProceduralVegetation);` (scope `PV::Export::Internal`)
- L109 _prototype_ `void AssignBoneIDsToFoliage(const TArray<Facades::FBoneNode>& Bones, FManagedArrayCollection& Collection);` (scope `PV::Export::Internal`)
- L111 _prototype_ `void RemoveUnwantedSkinWeights(TObjectPtr<UDynamicMesh> DynamicMesh, const FName ProfileName, const TArray<int32>& VertexBoneIDs, int32 FoliageVertexStart, const TArray<Facades::FBoneNode>& BoneNodes);` (scope `PV::Export::Internal`)
- L114 _prototype_ `void SetupPhysicAsset(const FManagedArrayCollection& Collection,const EPVCollisionGeneration& CollisionGeneration, UPhysicsAsset* PhysicsAsset, TArray<Facades::FBoneNode> InBones);` (scope `PV::Export::Internal`)
- L116 _prototype_ `bool ConvertToDefaultSkeletalMesh(USkeletalMesh* SkeletalMesh, FDynamicMesh3& Mesh, const TArray<TObjectPtr<UMaterialInterface>>& Materials );` (scope `PV::Export::Internal`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Helpers/PVGraphHelpers.h` (Private)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace PV`
- L13 _namespace_ `namespace Graph` (scope `PV`)
- L15 _prototype_ `UPVBaseSettings* GetNodeSettings(const UPCGNode* InNode);` (scope `PV::Graph`)
- L16 _prototype_ `IPVRenderSettings* GetRenderSettings(const UPCGNode* InNode);` (scope `PV::Graph`)
- L18 _prototype_ `UPCGPin* GetInPinFromNode(UPCGNode* InNode);` (scope `PV::Graph`)
- L19 _prototype_ `UPCGPin* GetOutPinFromNode(UPCGNode* InNode);` (scope `PV::Graph`)
- L20 _prototype_ `UPCGPin* GetUpstreamPin(UPCGPin* InPin);` (scope `PV::Graph`)
- L21 _prototype_ `UPCGPin* GetDownstreamPin(UPCGPin* InPin);` (scope `PV::Graph`)
- L23 _prototype_ `TArray<TObjectPtr<UPCGPin>> GetAllPVPinsFromNode(const UPCGNode* InNode);` (scope `PV::Graph`)
- L27 _function_ `template <typename PVDataType> requires std::is_base_of_v<FPCGDataTypeInfo, PVDataType> bool IsPinOfType(UPCGPin* InPin)` (scope `PV::Graph`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/PVEditor.h` (Private)


#### class `FPVEditor`  
`class FPVEditor : public FPCGEditor`  
_L16-128_
- inherits: `FPCGEditor`
- L19 _public prototype_ `FPVEditor();`
- L21 _public prototype_ `void Initialize( const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost, UProceduralVegetation* InProceduralVegetation );`
- L27 _public prototype_ `virtual TSubclassOf<UPCGEditorGraphSchema> GetSchemaClass() const override;`
- L29 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L32 _public prototype_ `virtual FText GetToolkitName() const override;`
- L33 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L34 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L35 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L37 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L38 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L40 _public prototype_ `virtual void OnClose() override;`
- L44 _public prototype_ `virtual IPCGBaseSubsystem* GetSubsystem() const override;`
- L49 _protected prototype_ `virtual void BindCommands() override;`
- L50 _protected prototype_ `virtual void OnSelectedNodesChanged(const TSet<UObject*>& InNewSelection) override;`
- L51 _protected prototype_ `virtual void OnGraphChanged(UPCGGraphInterface* InGraph, EPCGChangeType ChangeType) override;`
- L53 _protected prototype_ `virtual TAttribute<FGraphAppearanceInfo> GetAppearanceInfo() const override;`
- L54 _protected prototype_ `virtual TSharedRef<FTabManager::FLayout> GetDefaultLayout() const override;`
- L56 _protected prototype_ `virtual void RegisterExtraTabFactories(FWorkflowAllowedTabSet& TabSet) override;`
- L57 _protected prototype_ `virtual bool IsPanelAvailable(const FName PanelID) const override;`
- L58 _protected prototype_ `virtual void RegisterToolbarInternal(FToolBarBuilder& ToolbarBuilder) const override;`
- L60 _protected prototype_ `virtual bool CanToggleInspected() const override;`
- L62 _protected prototype_ `virtual TSharedRef<SPCGEditorViewport> CreateViewportWidget(int32 Index) override;`
- L64 _protected prototype_ `virtual void SetupModeTools(FAssetEditorModeManager* InModeTools) override;`
- L66 _protected prototype_ `virtual void OnNodeToolStarted(UPCGEditorGraphNodeBase* InteractiveNode) override;`
- L69 _protected prototype_ `static TSharedRef<SCollectionSpreadSheetWidget> CreateCollectionSpreadSheetWidget();`
- L72 _private prototype_ `FPCGStack GetStackFromPin(const UPCGPin* InPin) const;`
- L74 _private prototype_ `const UPVData* GetDataFromPin(const UPCGPin* InPin);`
- L76 _private prototype_ `void OnGraphExecuted(IPCGBaseSubsystem* InSubsystem, IPCGGraphExecutionSource* InExecutionSource, EPCGGenerationStatus InGenerationStatus);`
- L79 _private prototype_ `void ChangeNodeInspection(UPCGEditorGraphNodeBase* InNode);`
- L80 _private prototype_ `void OnLockNodeSelection();`
- L82 _private prototype_ `TObjectPtr<UPCGNode> GetFirstSelectedNode();`
- L83 _private prototype_ `TObjectPtr<UPCGEditorGraphNodeBase> GetFirstSelectedEdNode();`
- L84 _private prototype_ `bool IsNodeSelected(TObjectPtr<UPCGNode> InNode);`
- L86 _private prototype_ `TObjectPtr<UPCGNode> GetNodeBeingInspected();`
- L87 _private prototype_ `void SetNodeBeingInspected(TObjectPtr<UPCGEditorGraphNodeBase> InNode);`
- L90 _private prototype_ `bool IsInspectedNodeStale() const;` — Returns true if the currently inspected EdNode no longer exists in its owning graph (i.e. was deleted).
- L97 _private prototype_ `void ClearInspection();` — Fully releases inspection: clears base PCG inspection bookkeeping, tears down the drawn viewport scene, clears the "Previewing Output of Node" banner and the stats overlay, and resets all inspection state. Safe to call (no-op) when nothing is inspected.
- L99 _private prototype_ `void UpdateInspectedCollection();`
- L101 _private prototype_ `void UpdateCollectionSpreadSheet();`
- L103 _private prototype_ `void GatherStats(TArray<FText>& OverlayStats);`
- L104 _private prototype_ `void UpdateStats();`
- L106 _private prototype_ `void OnExport();`
- L109 _private member_ `static const FName CollectionSpreadSheetTabId;`
- L110 _private member_ `static const FName PreviewSceneSettingsTabId;`
- L112 _private member_ `TObjectPtr<UPCGDefaultExecutionSource> ExecutionSource;`
- L115 _private member_ `TWeakObjectPtr<UPCGGraph> LastGeneratedRootGraph;` — Root graph the execution source was last asked to generate, so refocusing the same graph does not regenerate it.
- L117 _private member_ `TObjectPtr<UProceduralVegetation> ProceduralVegetationBeingEdited = nullptr;`
- L119 _private member_ `TSharedPtr<SPVEditorViewport> EditorViewport = nullptr;`
- L121 _private member_ `TObjectPtr<UPCGEditorGraphNodeBase> NodeBeingInspected = nullptr;`
- L122 _private member_ `TArray<TObjectPtr<UPCGEditorGraphNodeBase>> SelectedNodes;`
- L124 _private member_ `TSharedPtr<SCollectionSpreadSheetWidget> CollectionSpreadSheetWidget;`
- L125 _private member_ `TSharedPtr<FManagedArrayCollection> CollectionBeingInspected = nullptr;`
- L127 _private member_ `FDateTime SessionStartTime;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/PVEditorCommands.h` (Private)


#### class `FPVEditorCommands`  
`class FPVEditorCommands : public TCommands<FPVEditorCommands>`  
_L7-25_
- inherits: `TCommands<FPVEditorCommands>`
- L10 _public prototype_ `FPVEditorCommands();`
- L13 _public prototype_ `virtual void RegisterCommands() override;`
- L17 _public member_ `TSharedPtr<FUICommandInfo> Export;` — Editor Commands
- L20 _public member_ `TSharedPtr<FUICommandInfo> ShowMannequin;` — Viewport Commands
- L21 _public member_ `TSharedPtr<FUICommandInfo> ShowScaleVisualization;`
- L22 _public member_ `TSharedPtr<FUICommandInfo> AutoFocusViewport;`
- L23 _public member_ `TSharedPtr<FUICommandInfo> ShowStats;`
- L24 _public member_ `TSharedPtr<FUICommandInfo> LockNodeInspection;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/PVEditorCommon.h` (Private)


#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace EditorCommon` (scope `PV`)
- L14 _variable_ `constexpr int32 EdgeCylinderNumSides = 6;` (scope `PV::EditorCommon`) — Tessellation for the tapered cylinder representing each skeleton edge.
- L17 _variable_ `constexpr int32 PointHighlightNumSides = 16;` (scope `PV::EditorCommon`) — Tessellation for the wireframe-sphere highlight drawn over points.
- L20 _variable_ `constexpr int32 InfluenceRadiusNumSides = 32;` (scope `PV::EditorCommon`) — Tessellation for the influence-radius circles drawn in SelectByEuclideanDistance mode.
- L23 _variable_ `constexpr float PointMinScale = 0.1f;` (scope `PV::EditorCommon`) — Minimum scale for the point sphere.
- L26 _variable_ `constexpr float HighlightPointScaleBias = 1.25f;` (scope `PV::EditorCommon`) — Scale biases applied to the mesh sphere, point highlight, and edge highlight.
- L27 _variable_ `constexpr float HighlightEdgeScaleBias = 1.1f;` (scope `PV::EditorCommon`)
- L30 _externvar_ `extern const FLinearColor HoverHighlightColor;` (scope `PV::EditorCommon`) — Hover/selection highlight visuals. Defined in PVEditorCommon.cpp.
- L31 _externvar_ `extern const FLinearColor SelectedHighlightColor;` (scope `PV::EditorCommon`)
- L32 _externvar_ `extern const FLinearColor InfluenceRadiusColor;` (scope `PV::EditorCommon`)
- L34 _variable_ `constexpr float HighlightLineThickness = 0.0f;` (scope `PV::EditorCommon`)
- L35 _variable_ `constexpr uint8 HighlightPointDepthPriority = SDPG_Foreground;` (scope `PV::EditorCommon`)
- L36 _variable_ `constexpr uint8 HighlightEdgeDepthPriority = SDPG_World;` (scope `PV::EditorCommon`)
- L40 _externvar_ `extern const PV::TDynamicMeshVertexAttributeDefinition<int32> BranchIndexAttribute;` (scope `PV::EditorCommon`) — Per-vertex int32 attribute names. Anchored on the dynamic mesh attribute set so the click ray cast can recover (BranchIndex, BranchPointIndex) for any hit triangle.
- L41 _externvar_ `extern const PV::TDynamicMeshVertexAttributeDefinition<int32> BranchPointIndexAttribute;` (scope `PV::EditorCommon`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/PVEditorSchema.h` (Private)


#### class `UPVEditorSchema`  
`class UPVEditorSchema : public UPCGEditorGraphSchema`  
_L9-24_
- reflection: `UCLASS()`
- inherits: `UPCGEditorGraphSchema`
- L15 _public prototype_ `virtual EPCGElementType GetElementTypeFiltering() const override;` — Return the element type filtering for the current editor. By default it is all.
- L17 _public prototype_ `virtual TSubclassOf<UPCGBaseSubgraphSettings> GetSubgraphSettingsClass() const override;`
- L20 _public prototype_ `virtual const FPCGGraphEditorCustomization& GetGraphEditorCustomization(const UEdGraph* InEdGraph) const override;` — Return the graph customization for this editor. By default it is the one provided by the graph.
- L23 _protected prototype_ `virtual void GetNativeElementActions(FGraphActionMenuBuilder& ActionMenuBuilder, const FPCGActionsFilter& ActionFilter) const override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/ProceduralVegetationFactory.h` (Private)


#### class `UProceduralVegetationFactory`  
`class UProceduralVegetationFactory : public UFactory`  
_L12-31_
- reflection: `UCLASS(hidecategories=Object)`
- inherits: `UFactory`
- L17 _public prototype_ `UProceduralVegetationFactory(const FObjectInitializer& ObjectInitializer);`
- L20 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* Warn) override;`
- L21 _public function_ `virtual bool ShouldShowInNewMenu() const override`
- L22 _public prototype_ `virtual bool ConfigureProperties() override;`
- L23 _public prototype_ `virtual FString GetDefaultNewAssetName() const override;`
- L27 _private member_ `TObjectPtr<UProceduralVegetation> SampleProceduralVegetation = nullptr;` — `UPROPERTY()`
- L30 _private member_ `TOptional<FString> SampleName;` — `UPROPERTY()`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/SPVEditorViewport.h` (Private)


#### enum `EPVVisualizationMode`  
`enum class EPVVisualizationMode : uint8`  
_L18-33_
- reflection: `UENUM()`
- L20 _public enumerator_ `Default UMETA(DisplayName = "Default")`
- L21 _public enumerator_ `PointData UMETA(DisplayName = "Point data")`
- L22 _public enumerator_ `Mesh UMETA(DisplayName = "Mesh")`
- L23 _public enumerator_ `FoliageGrid UMETA(DisplayName = "Foliage grid")`
- L24 _public enumerator_ `Bones UMETA(DisplayName = "Bones")`
- L25 _public enumerator_ `PointDataLeafProxy UMETA(DisplayName = "Point data + Leaf Proxy")`
- L26 _public enumerator_ `PointDataMesh UMETA(DisplayName = "Point data + Mesh")`
- L27 _public enumerator_ `PointDataFoliageAttachment UMETA(DisplayName = "Point data + Foliage attachments")`
- L28 _public enumerator_ `FoliageMesh UMETA(DisplayName = "Foliage + Mesh")`
- L29 _public enumerator_ `FoliageAttachmentMesh UMETA(DisplayName = "Foliage attachments + Mesh")`
- L30 _public enumerator_ `BonesMesh UMETA(DisplayName = "Bones + Mesh")`
- L31 _public enumerator_ `GraftsGrid UMETA(DisplayName = "Grafts grid")`
- L32 _public enumerator_ `BoundingBoxOnly UMETA(Hidden, DisplayName = "Bounding Box Only")`

#### struct `FLegendData`  
`struct FLegendData`  
_L35-39_
- L37 _public member_ `FLinearColor Color;`
- L38 _public member_ `FText Text;`

#### class `UPVMannequinWidgetContext`  
`class UPVMannequinWidgetContext : public UObject`  
_L50-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L55 _public member_ `TSharedPtr<SWidget> MannequinOffsetWidget = nullptr;`

#### class `UPVFoliageComponentsContext`  
`class UPVFoliageComponentsContext : public UObject`  
_L59-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L64 _public member_ `TSharedPtr<TArray<TObjectPtr<UMeshComponent>>> FoliageComponents = nullptr;`
- L65 _public member_ `TSharedPtr<TMap<FString, bool>> FoliageVisibility = nullptr;`

#### class `SPVEditorViewport`  
`class SPVEditorViewport : public SPCGEditorViewport`  
_L68-169_
- inherits: `SPCGEditorViewport`
- L71 _public function_ `SLATE_BEGIN_ARGS(SPVEditorViewport) : _ModeTools(nullptr)`
- L74 _public prototype_ `SLATE_ARGUMENT(FEditorModeTools*, ModeTools) SLATE_END_ARGS() SPVEditorViewport();`
- L79 _public prototype_ `void Construct(const FArguments& InArgs);`
- L80 _public prototype_ `FToolMenuEntry CreateSettingsToolbarMenu();`
- L81 _public prototype_ `FToolMenuEntry CreateVisualizationModeToolbarMenu();`
- L82 _public prototype_ `void CreatePointDataSettingsMenu(UToolMenu* InPointDataSubMenu);`
- L84 _public prototype_ `void OnNodeInspectionChanged(IPVRenderSettings* InSettings);`
- L85 _public prototype_ `void ClearNodeInspection();`
- L87 _public prototype_ `void SetOverlayText(const FText& CurrentlyLockedNodeName = FText::GetEmpty());`
- L88 _public prototype_ `void PopulateStatsOverlayText(const TArrayView<FText> TextItems);`
- L89 _public prototype_ `void PopulateLegendOverlayText(const TArrayView<TPair<FColor, FText>> LegendItems);`
- L91 _public prototype_ `void AddInstancedFoliageComponent(TObjectPtr<UMeshComponent> Component);`
- L92 _public prototype_ `void SetSkeletonVisualizerComponent(TObjectPtr<UPVSkeletonVisualizerComponent> InSkeletonVisualizerComponent);`
- L94 _public function_ `TSharedRef<FAdvancedPreviewScene> GetAdvancedPreviewSceneRef() const`
- L99 _public member_ `TOptional<ELevelViewportType> OverriddenViewportType;`
- L103 _protected prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L104 _protected prototype_ `virtual void BindCommands() override;`
- L107 _protected prototype_ `virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;`
- L108 _protected prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L112 _private prototype_ `void InitVisualizationScene();`
- L113 _private prototype_ `void ResetVisualizationScene();`
- L115 _private prototype_ `TSharedRef<SWidget> CreateMannequinOffsetWidget() const;`
- L117 _private prototype_ `void ToggleShowMannequin();`
- L118 _private prototype_ `bool IsShowMannequinChecked() const;`
- L119 _private prototype_ `void SetMannequinState(bool InEnable);`
- L121 _private prototype_ `void ToggleShowScaleVis();`
- L122 _private prototype_ `bool IsShowScaleVisChecked() const;`
- L123 _private prototype_ `void SetScaleVisState(bool InEnable);`
- L125 _private prototype_ `void ToggleShowStats();`
- L126 _private prototype_ `bool IsShowStatsChecked() const;`
- L128 _private prototype_ `void ToggleAutofocusViewport();`
- L129 _private prototype_ `bool IsAutoFocusViewportChecked() const;`
- L131 _private prototype_ `float GetMannequinOffset() const;`
- L132 _private prototype_ `void SetMannequinOffset(float NewValue, bool bSaveConfig = false) const;`
- L134 _private prototype_ `UPVMannequinWidgetContext* CreateMannequinWidgetContext();`
- L135 _private prototype_ `UPVFoliageComponentsContext* CreateFoliageComponentsContext();`
- L137 _private member_ `TArray<EPVRenderType> SupportedRenderTypes;`
- L138 _private member_ `EPVVisualizationMode CurrentVisualizationMode = EPVVisualizationMode::Default;`
- L139 _private member_ `IPVRenderSettings* InspectedNodeSettings = nullptr;`
- L141 _private prototype_ `void OnVisualizationModeChanged(EPVVisualizationMode InMode);`
- L143 _private member_ `bool bFocusOnNextUpdate = true;`
- L146 _protected prototype_ `virtual void OnSetupScene() override;`
- L147 _protected prototype_ `virtual void OnResetScene() override;`
- L150 _private member_ `TObjectPtr<UStaticMeshComponent> MannequinComponent = nullptr;`
- L151 _private member_ `TObjectPtr<UPVScaleVisualizationComponent> ScaleVisualizationComponent = nullptr;`
- L152 _private member_ `TObjectPtr<UPVSkeletonVisualizerComponent> SkeletonVisualizerComponent = nullptr;`
- L154 _private member_ `TSharedPtr<SWidget> MannequinOffsetWidget;`
- L155 _private member_ `TStrongObjectPtr<UPVMannequinWidgetContext> MannequinWidgetContext;`
- L156 _private member_ `TStrongObjectPtr<UPVFoliageComponentsContext> FoliageComponentsContext;`
- L158 _private member_ `TSharedPtr<TArray<TObjectPtr<UMeshComponent>>> FoliageComponents;`
- L159 _private member_ `TSharedPtr<TMap<FString, bool>> FoliageVisibility;`
- L161 _private member_ `bool bIsPreviewingLockedNode = false;`
- L162 _private member_ `TSharedPtr<SRichTextBlock> OverlayText;`
- L163 _private member_ `TSharedPtr<SRichTextBlock> StatsOverlayText;`
- L164 _private member_ `TArray<TSharedPtr<FText>> LegendData;`
- L165 _private member_ `ESkeletonVisualizationModes DebugVisualizationMode = ESkeletonVisualizationModes::None;`
- L167 _private member_ `TSharedPtr<FSlateBrush> PreviewNodeBackgroundBrush;`
- L168 _private member_ `TSharedPtr<SListView<TSharedPtr<FText>>> LegendListView;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Tools/Contexts/PVToolContext.h` (Private)


#### class `UPVToolContextObject`  
`class UPVToolContextObject : public UObject`  
_L16-23_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: PVE-specific context object stored alongside UPCGNodeToolContext in the context store. Carries vegetation data that PCG's generic context does not hold.
- L22 _public member_ `FPCGStack InspectionStack;` — `UPROPERTY()`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Tools/Helpers/PVManualEditToolHelpers.h` (Private)


#### enum `PV::Tools::ESkeletonHoverType`  
`enum class ESkeletonHoverType : uint8`  
_L24-29_
- L26 _public enumerator_ `None`
- L27 _public enumerator_ `Point`
- L28 _public enumerator_ `Edge`

#### struct `PV::Tools::FManualEditAttributes`  
`struct FManualEditAttributes`  
_L31-45_
- L33 _public member_ `FPointPositionAttributeConstView PointPosition;`
- L34 _public member_ `FPointScaleAttributeConstView PointScale;`
- L35 _public member_ `FPointLengthFromRootAttributeConstView PointLengthFromRoot;`
- L36 _public member_ `FPointBudNumberAttributeConstView PointBudNumber;`
- L37 _public member_ `FBranchPointsAttributeConstView BranchPoints;`
- L38 _public member_ `FBranchNumberAttributeConstView BranchNumber;`
- L39 _public member_ `FBranchChildrenAttributeConstView BranchChildren;`
- L40 _public member_ `FBranchParentNumberAttributeConstView BranchParents;`
- L42 _public prototype_ `bool InitializeFromCollection(const FManagedArrayCollection& InCollection);`
- L44 _public prototype_ `bool IsValid() const;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace PV`
- L16 _namespace_ `namespace Facades` (scope `PV`)
- L22 _namespace_ `namespace PV`
- L22 _namespace_ `namespace Tools` (scope `PV`)
- L48 _prototype_ `bool IsPointRemoved( const FPointBudNumberAttributeConstView& PointBudNumberAttribute, const TArray<bool>& RemovedPoints, int32 PointIndex );` (scope `PV::Tools`) — Returns true if PointIndex's BudNumber maps to a "removed" entry in RemovedPoints.
- L54 _prototype_ `TArray<int32> GetBranchImmediateChildren(const FManualEditAttributes& Attributes, const int32 BranchIndex);` (scope `PV::Tools`)
- L58 _prototype_ `bool GetPointWorldPositionAndScale( const FManualEditAttributes& Attributes, const TArray<FVector3f>& Offsets, const int32 BranchIndex, const int32 BranchPointIndex, FVector& OutPosition, float& OutScale );` (scope `PV::Tools`) — Compute world-space position and per-point scale for a (BranchIndex, BranchPointIndex). Returns false on any invalid input (collection invalid, branch out of range, point index out of range, etc.).
- L68 _prototype_ `void DrawPointHighlight( FPrimitiveDrawInterface* PDI, const FVector& Position, float Scale, const FLinearColor& Color );` (scope `PV::Tools`) — Wireframe sphere drawn slightly larger than the mesh sphere so it visually wraps it.
- L77 _prototype_ `void DrawEdgeHighlight( FPrimitiveDrawInterface* PDI, const FVector& PosA, const FVector& PosB, float RadiusA, float RadiusB, const FLinearColor& Color );` (scope `PV::Tools`) — Six PDI lines along the longitudinal ridges of the tapered cylinder built by AppendTaperedCylinder, plus two end-cap circles. Tessellation matches PV::EditorCommon::EdgeCylinderNumSides.
- L84 _prototype_ `int32 GetPointIndexFromHitProxy(HHitProxy* InProxy);` (scope `PV::Tools`)
- L86 _prototype_ `UPVSkeletonVisualizerComponent* GetVisualizerComponentFromHitProxy(HHitProxy* InProxy);` (scope `PV::Tools`)
- L88 _prototype_ `bool FindBranchSelectionFromRay( const UPVSkeletonVisualizerComponent* VisualizerComponent, const FRay& WorldRay, int32& OutBranchIndex, int32& OutBranchPointIndex );` (scope `PV::Tools`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Tools/Helpers/PVSkeletonPointsSelection.h` (Private)


#### struct `FSkeletonPointsSelection`  
`struct FSkeletonPointsSelection`  
_L21-95_
- desc: Selection state for the skeleton edit tool: a primary "anchor" point plus an extended set reachable from the anchor via one of three modes (neighbour count, tree distance, or Euclidean distance). Owned exclusively by UPVManualEditTool.
- L37 _public prototype_ `explicit FSkeletonPointsSelection(const FManagedArrayCollection* const InCollection);`
- L39 _public prototype_ `void SelectPoint(int32 InBranchIndex, int32 InBranchPointIndex);`
- L41 _public prototype_ `void ExtendSelection( ESkeletonSelectionMode SelectionMode, float ExtensionLimit, const TArray<FVector3f>& Offsets, EPointSelectionSmoothnessMethod SmoothnessMethod = EPointSelectionSmoothnessMethod::Linear );`
- L48 _public prototype_ `void ApplySelectionWeights( ESkeletonSelectionMode SelectionMode, float ExtensionLimit, EPointSelectionSmoothnessMethod SmoothnessMethod );`
- L54 _public prototype_ `void ClearSelection();`
- L56 _public prototype_ `bool HasSelection() const;`
- L58 _public function_ `int32 GetSelectedBranchIndex() const`
- L59 _public function_ `int32 GetSelectedBranchPointIndex() const`
- L61 _public function_ `const FSelectedPoint& GetPrimarySelected() const`
- L62 _public function_ `bool HasPrimarySelected() const`
- L64 _public function_ `const TArray<FSelectedPoint>& GetSelectedPoints() const`
- L65 _public function_ `int32 NumSelectedPoints() const`
- L69 _private prototype_ `void ExtendSelectionByNeighbours( const PV::Facades::FPointFacade& PointFacade, const PV::Facades::FBranchFacade& BranchFacade, float ExtensionLimit);` — Mode-specific extension helpers, dispatched from ExtendSelection.
- L74 _private prototype_ `void ExtendSelectionByTreeDistance( const PV::Facades::FPointFacade& PointFacade, const PV::Facades::FBranchFacade& BranchFacade, const TArray<FVector3f>& Offsets, float ExtensionLimit);`
- L80 _private prototype_ `void ExtendSelectionByEuclideanDistance( const PV::Facades::FPointFacade& PointFacade, const PV::Facades::FBranchFacade& BranchFacade, const TArray<FVector3f>& Offsets, float ExtensionLimit);`
- L86 _private prototype_ `float GetWeightBySelectedSmoothness( float Weight, EPointSelectionSmoothnessMethod SmoothnessMethod = EPointSelectionSmoothnessMethod::Linear ) const;`
- L91 _private member_ `const FManagedArrayCollection* const Collection = nullptr;`
- L93 _private member_ `FSelectedPoint PrimarySelectedPoint;`
- L94 _private member_ `TArray<FSelectedPoint> SelectedPoints;`

#### struct `FSkeletonPointsSelection::FSelectedPoint`  
`struct FSelectedPoint`  
_L23-35_
- L25 _public member_ `int32 BranchIndex = INDEX_NONE;`
- L26 _public member_ `int32 BranchPointIndex = INDEX_NONE;`
- L27 _public member_ `float Weight = 0.0f;`
- L29 _public member_ `int32 NeighbourIndex = INDEX_NONE;`
- L31 _public function_ `bool operator==(const FSelectedPoint& Other) const`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace PV`
- L11 _namespace_ `namespace Facades` (scope `PV`)
- L97 _prototype_ `uint32 GetTypeHash(const FSkeletonPointsSelection::FSelectedPoint& InPoint);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Tools/NodeTools/PVColliderTransformTool.h` (Private)


#### class `UPVColliderTransformTool`  
`class UPVColliderTransformTool : public UPVBaseInteractiveTool, public IClickBehaviorTarget`  
_L19-57_
- reflection: `UCLASS()`
- inherits: `UPVBaseInteractiveTool,IClickBehaviorTarget`
- L28 _public prototype_ `UPVColliderTransformTool();`
- L30 _public prototype_ `virtual void Setup() override;`
- L31 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L33 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L34 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L37 _protected prototype_ `virtual void OnNodeSettingsChanged(UPCGSettings* InNodeSettings, EPCGChangeType InChangeType) override;`
- L39 _protected prototype_ `void SetupColliderPreviews();`
- L40 _protected prototype_ `void ClearColliderPreviews();`
- L42 _protected prototype_ `void OnGizmoTransformBegin(UTransformProxy* Proxy);`
- L43 _protected prototype_ `void OnGizmoTransformChanged(UTransformProxy* Proxy, FTransform NewTransform);`
- L44 _protected prototype_ `void OnGizmoTransformEnd(UTransformProxy* Proxy);`
- L48 _private member_ `TArray<TObjectPtr<UStaticMeshComponent>> MeshComponents;` — `UPROPERTY(Transient)`
- L50 _private member_ `int32 SelectedComponentIndex = INDEX_NONE;`
- L53 _private member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY(Transient)`
- L56 _private member_ `TObjectPtr<UCombinedTransformGizmo> CombinedGizmo = nullptr;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Tools/NodeTools/PVExtractFromImageTool.h` (Private)


#### class `UPVExtractFromImageTool`  
`class UPVExtractFromImageTool : public UPVBaseInteractiveTool, public IClickDragBehaviorTarget`  
_L15-44_
- reflection: `UCLASS()`
- inherits: `UPVBaseInteractiveTool,IClickDragBehaviorTarget`
- L22 _public prototype_ `UPVExtractFromImageTool();`
- L25 _public prototype_ `virtual void Setup() override;`
- L26 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L27 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L31 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L32 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L33 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L34 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L35 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L39 _private prototype_ `void EndClickDragBehavior();`
- L42 _private member_ `int32 DraggedPlantIndex = INDEX_NONE;`
- L43 _private member_ `bool bDraggingRotation = false;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Tools/NodeTools/PVManualEditTool.h` (Private)


#### class `UPVManualEditTool`  
`class UPVManualEditTool : public UPVBaseInteractiveTool, public IClickBehaviorTarget, public IHoverBehaviorTarget, public FSelfRegisteringEditorUndoClient`  
_L27-133_
- reflection: `UCLASS()`
- inherits: `UPVBaseInteractiveTool,IClickBehaviorTarget,IHoverBehaviorTarget,FSelfRegisteringEditorUndoClient`
- L40 _public prototype_ `UPVManualEditTool();`
- L43 _public prototype_ `virtual void Setup() override;`
- L44 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L45 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L46 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L50 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos) override;`
- L51 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos) override;`
- L55 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L56 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L57 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L58 _public prototype_ `virtual void OnEndHover() override;`
- L62 _public prototype_ `virtual bool MatchesContext( const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts ) const override;`
- L66 _public prototype_ `virtual void PostUndo(bool bSuccess) override;`
- L71 _protected prototype_ `virtual void OnNodeSettingsChanged(UPCGSettings* InNodeSettings, EPCGChangeType InChangeType) override;`
- L75 _protected prototype_ `virtual void OnNodeExecuted() override;`
- L79 _private prototype_ `void InitializeTool();`
- L80 _private prototype_ `bool IsToolInitialized() const;`
- L82 _private prototype_ `void OnGizmoTransformBegin(UTransformProxy* TransformProxy);`
- L83 _private prototype_ `void OnGizmoTransformChanged(UTransformProxy* TransformProxy, FTransform Transform);`
- L84 _private prototype_ `void OnGizmoTransformEnd(UTransformProxy* TransformProxy);`
- L87 _private prototype_ `void RenderSelectionHighlights( FPrimitiveDrawInterface* PDI, const UPVManualEditSettings* ManualEditSettings, int32 SelectedBranchIndex, int32 SelectedBranchPointIndex );` — --- Render passes ---
- L93 _private prototype_ `void RenderHoverHighlight(FPrimitiveDrawInterface* PDI);`
- L94 _private prototype_ `void RenderInfluenceRadius(FPrimitiveDrawInterface* PDI, const float Radius);`
- L97 _private prototype_ `void ApplySelectionAtClick(int32 HitBranchIndex, int32 HitBranchPointIndex);` — --- OnClicked mode dispatch ---
- L98 _private prototype_ `void ApplyBranchRemovalAtClick(int32 HitBranchIndex, int32 HitBranchPointIndex);`
- L101 _private prototype_ `bool GetPointWorldPositionAndScale( int32 BranchIndex, int32 BranchPointIndex, FVector& OutPosition, float& OutScale );` — Compute the world-space position and per-point scale for (BranchIndex, BranchPointIndex). Mirrors RebuildPreviewMesh's lookup.
- L110 _protected member_ `TObjectPtr<UTransformProxy> TransformProxy = nullptr;` — `UPROPERTY(Transient)`
- L113 _protected member_ `TObjectPtr<UCombinedTransformGizmo> CombinedGizmo = nullptr;` — `UPROPERTY(Transient)`
- L116 _protected member_ `TObjectPtr<UPVSkeletonVisualizerComponent> PreviewComponent = nullptr;` — `UPROPERTY(Transient)`
- L118 _protected member_ `TUniquePtr<FSkeletonPointsSelection> Selection;`
- L120 _protected member_ `PV::Tools::FManualEditAttributes Attributes;`
- L123 _private member_ `FQuat4f PreviousRotation = FQuat4f::Identity;`
- L126 _private member_ `int32 HoveredBranchIndex = INDEX_NONE;` — Last hovered (BranchIndex, BranchPointIndex) and whether the hit was a sphere or a cylinder triangle.
- L127 _private member_ `int32 HoveredBranchPointIndex = INDEX_NONE;`
- L128 _private member_ `PV::Tools::ESkeletonHoverType HoveredType = PV::Tools::ESkeletonHoverType::None;`
- L130 _private member_ `bool bHoveringRotationGizmo = false;`
- L132 _private member_ `bool bIsTransforming = false;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Tools/PVBaseInteractiveTool.h` (Private)


#### class `UPVBaseInteractiveTool`  
`class UPVBaseInteractiveTool : public UPCGAssetEditorInteractiveTool`  
_L20-65_
- reflection: `UCLASS(Abstract)`
- inherits: `UPCGAssetEditorInteractiveTool`
- L25 _public prototype_ `virtual void Setup() override;`
- L26 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L28 _public prototype_ `virtual void RequestShutdown(EToolShutdownType ShutdownType);`
- L30 _public prototype_ `TObjectPtr<UWorld> GetTargetWorld();`
- L32 _public prototype_ `bool HasCollection() const;`
- L33 _public prototype_ `const TSharedPtr<FManagedArrayCollection>& GetCollection() const;`
- L36 _public function_ `template <typename T = UPVBaseSettings> TObjectPtr<T> GetNodeSettings()`
- L39 _public function_ `template <typename T = UPVBaseSettings> TObjectPtr<const T> GetNodeSettings() const`
- L42 _protected function_ `virtual void OnNodeExecuted()`
- L45 _private prototype_ `void OnGraphExecuted(IPCGBaseSubsystem* InSubsystem, IPCGGraphExecutionSource* InExecutionSource, EPCGGenerationStatus InGenerationStatus);`
- L47 _private prototype_ `bool CacheData(const TArray<FPCGTaggedData>& InTaggedData);`
- L51 _protected member_ `TObjectPtr<UWorld> TargetWorld = nullptr;` — `UPROPERTY(Transient)`
- L54 _protected member_ `TObjectPtr<AActor> PreviewActor = nullptr;` — `UPROPERTY(Transient)`
- L57 _protected member_ `TObjectPtr<UPVBaseSettings> NodeSettings = nullptr;` — `UPROPERTY(Transient)`
- L60 _protected member_ `TObjectPtr<UEditorInteractiveToolsContext> InteractiveToolsContext;` — `UPROPERTY(Transient)`
- L64 _private member_ `TObjectPtr<const UPVData> InputData = nullptr;` — `UPROPERTY(Transient)`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/DebugVisualization/PVDebugVisualizationBase.h` (Private)


#### class `FPVDebugVisualizationBase`  
`class FPVDebugVisualizationBase`  
_L18-59_
- L21 _public prototype_ `virtual ~FPVDebugVisualizationBase() = default;`
- L22 _public function_ `FPVDebugVisualizationBase()`
- L23 _public prototype_ `virtual void Draw(FVisualizerDrawContext& InContext);`
- L25 _protected prototype_ `void DrawPivotPoints(const FVisualizerDrawContext& InContext);`
- L26 _protected prototype_ `void DrawAttributes(FVisualizerDrawContext& InContext);`
- L27 _protected prototype_ `void AddDrawAsPoint(const FVector& InPos, float PointScale, const FLinearColor& InColor = FLinearColor::White);`
- L28 _protected prototype_ `virtual TArray<FVector3f> GetPivotPositions(const FManagedArrayCollection& InCollection) = 0;`
- L29 _protected prototype_ `virtual void GetPivot(const FManagedArrayCollection& InCollection, const int InIndex, FVector3f& OutPos, float& OutScale) = 0;`
- L45 _protected prototype_ `static void DrawAsText(FPCGSceneSetupParams& InOutParams, const FText& InTextToDraw, const FVector3f& InPos, float InScale, float TextSize, const FLinearColor& InColor = FLinearColor::White, const FVector3f TextOffset = FVector3f::Zero());`
- L46 _protected prototype_ `static void DrawAsLine(UPVLineBatchComponent* LineBatchComponent, const FVector& InStartPos, const FVector& InEndPos, const FLinearColor& InColor, ESceneDepthPriorityGroup InDepthPriorityGroup);`
- L47 _protected prototype_ `static void DrawAsSphere(UPVLineBatchComponent* LineBatchComponent, const FVector& InPos, float Radius, const FLinearColor& InColor, ESceneDepthPriorityGroup InDepthPriorityGroup);`
- L48 _protected prototype_ `static void DrawAsPoints(UPVLineBatchComponent* LineBatchComponent, const TArray<FPoint>& InPoints, ESceneDepthPriorityGroup InDepthPriorityGroup);`
- L49 _protected prototype_ `static void DrawAsMeshPoints(UInstancedStaticMeshComponent* InstancedStaticMeshComponent, const TArray<FPoint>& InPoints);`
- L50 _protected prototype_ `static void DrawAsMeshSpheres(UInstancedStaticMeshComponent* SphereComponent, const TArray<FSphere>& InSpheres);`
- L52 _protected prototype_ `static UPVLineBatchComponent* GetOrCreateLineComponent(FPCGSceneSetupParams& InOutParams);`
- L53 _protected prototype_ `static UInstancedStaticMeshComponent* GetOrCreateSphereComponent(FPCGSceneSetupParams& InOutParams);`
- L55 _protected prototype_ `static void AddToScene(FPCGSceneSetupParams& InOutParams, UPrimitiveComponent* InComponent);`
- L58 _private member_ `TArray<FPoint> PointsToDraw;`

#### struct `FPVDebugVisualizationBase::FPoint`  
`struct FPoint`  
_L31-36_
- L33 _public member_ `FVector Position;`
- L34 _public member_ `float Scale;`
- L35 _public member_ `FLinearColor Color;`

#### struct `FPVDebugVisualizationBase::FSphere`  
`struct FSphere`  
_L38-43_
- L40 _public member_ `FVector Position;`
- L41 _public member_ `float Radius;`
- L42 _public member_ `FLinearColor Color;`

#### Free symbols / members of external scopes

- L60 _typedef_ `typedef TSharedPtr<FPVDebugVisualizationBase> FPVDebugVisualizationPtr;`
- L62 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogPVDebugVisualization, Log, All);`
- L62 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogPVDebugVisualization, Log, All);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/DebugVisualization/PVDebugVisualizations.h` (Private)


#### class `FPVPointDebugVisualization`  
`class FPVPointDebugVisualization final : public FPVDebugVisualizationBase`  
_L12-19_
- inherits: `FPVDebugVisualizationBase`
- L15 _public function_ `FPVPointDebugVisualization()`
- L17 _protected prototype_ `virtual TArray<FVector3f> GetPivotPositions(const FManagedArrayCollection& InCollection) override;`
- L18 _protected prototype_ `virtual void GetPivot(const FManagedArrayCollection& InCollection, const int InIndex, FVector3f& OutPos, float& OutScale) override;`

#### class `FPVFoliageDebugVisualization`  
`class FPVFoliageDebugVisualization final : public FPVDebugVisualizationBase`  
_L21-28_
- inherits: `FPVDebugVisualizationBase`
- L24 _public function_ `FPVFoliageDebugVisualization()`
- L26 _protected prototype_ `virtual TArray<FVector3f> GetPivotPositions(const FManagedArrayCollection& InCollection) override;`
- L27 _protected prototype_ `virtual void GetPivot(const FManagedArrayCollection& InCollection, const int InIndex, FVector3f& OutPos, float& OutScale) override;`

#### class `FPVBranchDebugVisualization`  
`class FPVBranchDebugVisualization final : public FPVDebugVisualizationBase`  
_L30-37_
- inherits: `FPVDebugVisualizationBase`
- L33 _public function_ `FPVBranchDebugVisualization()`
- L35 _protected prototype_ `virtual TArray<FVector3f> GetPivotPositions(const FManagedArrayCollection& InCollection) override;`
- L36 _protected prototype_ `virtual void GetPivot(const FManagedArrayCollection& InCollection, const int InIndex, FVector3f& OutPos, float& OutScale) override;`

#### class `FPVCustomDebugVisualization`  
`class FPVCustomDebugVisualization final : public FPVDebugVisualizationBase`  
_L39-57_
- inherits: `FPVDebugVisualizationBase`
- L42 _private member_ `FName PivotPositionAttributeName = NAME_None;`
- L43 _private member_ `FName PivotScaleAttributeName = NAME_None;`
- L44 _private member_ `FName PivotGroupName = NAME_None;`
- L47 _public function_ `FPVCustomDebugVisualization(FName InPivotPositionAttributeName, FName InPivotScaleAttributeName, FName InPivotGroupName) : PivotPositionAttributeName(InPivotPositionAttributeName) , PivotScaleAttributeName(InPivotScaleAttributeName) , PivotGroupName(InPivotGroupName)`
- L55 _protected prototype_ `virtual TArray<FVector3f> GetPivotPositions(const FManagedArrayCollection& InCollection) override;`
- L56 _protected prototype_ `virtual void GetPivot(const FManagedArrayCollection& InCollection, const int InIndex, FVector3f& OutPos, float& OutScale) override;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/DebugVisualization/PVDebugVisualizer.h` (Private)


#### struct `FVisualizerDrawContext`  
`struct FVisualizerDrawContext`  
_L15-21_
- L17 _public prototype_ `FVisualizerDrawContext(const FManagedArrayCollection& InCollection, const FPVVisualizationSettings& InSettings, FPCGSceneSetupParams& InSceneParams);`
- L18 _public member_ `const FManagedArrayCollection& Collection;`
- L19 _public member_ `const FPVVisualizationSettings& VisualizationSettings;`
- L20 _public member_ `FPCGSceneSetupParams& SceneSetupParams;`

#### class `FPVDebugVisualizer`  
`class FPVDebugVisualizer`  
_L23-39_
- L26 _public prototype_ `static void DrawDebugVisualizations(const TArray<FPVVisualizationSettings>& VisualizationSettings, const FManagedArrayCollection& Collection, FPCGSceneSetupParams& InOutParams);`
- L27 _public prototype_ `static void DrawDebugParams(const TArray<FPVParamDebuggerSettings>& ParamDebugVisualizationSettings, bool bAutoFocusLoopDebug, FPCGSceneSetupParams& InOutParams);`
- L30 _private prototype_ `static void VisualizeDebuggerParam( FPCGSceneSetupParams& InOutParams, const FPVParamDebuggerSettings& Settings, UPVLineBatchComponent* LineBatcher, FLinearColor Color, FBox& BoundingBox );`
- L38 _private prototype_ `static FPVDebugVisualizationPtr CreateVisualizer(const FPVVisualizationSettings& InSettings);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/Helpers/PVSkeletonVisualizerHelpers.h` (Private)


#### struct `PV::Visualizations::FPVAppendMeshResult`  
`struct FPVAppendMeshResult`  
_L21-25_
- desc: @brief Holder struct for PVMeshGenerators Vertices and Indices IDs. Returned from MeshGenerators AddToMesh method
- L23 _public member_ `TArray<int32, TInlineAllocator<16>> VertexIDs;`
- L24 _public member_ `TArray<int32, TInlineAllocator<32>> TriangleIDs;`

#### struct `PV::Visualizations::FPVEdgeMeshGenerator`  
`struct FPVEdgeMeshGenerator`  
_L27-53_
- L29 _public prototype_ `FPVEdgeMeshGenerator(UE::Geometry::FDynamicMesh3* InMesh);`
- L30 _public prototype_ `~FPVEdgeMeshGenerator() = default;`
- L40 _public prototype_ `FPVAppendMeshResult AddToMesh( const FTransform& InBottomTransform, const FTransform& InTopTransform, FLinearColor InBottomColor = FLinearColor::White, FLinearColor InTopColor = FLinearColor::White );` — @param InBottomTransform Transform of the bottom of the edge mesh in the dynamic mesh @param InTopTransform Transform of the top of the edge mesh in the dynamic mesh @param InBottomColor Vertex Color to add to the bottom edge vertices, given the mesh has color overlay enabled @param InTopColor Vertex Color to add to the top edge vertices, given the mesh has color overlay enabled @returns FPVAppendMeshResult with all the added vertices and indices added to the InMesh
- L48 _private member_ `UE::Geometry::FDynamicMesh3* Mesh = nullptr;`
- L50 _private member_ `UE::Geometry::FDynamicMeshColorOverlay* ColorOverlay = nullptr;`
- L52 _private member_ `TArray<FVector> CircleVertices;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Geometry` (scope `UE`)
- L15 _namespace_ `namespace PV`
- L15 _namespace_ `namespace Visualizations` (scope `PV`)

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/PVBoneComponent.h` (Private)


#### class `FPVBoneSceneProxy`  
`class FPVBoneSceneProxy final : public FPrimitiveSceneProxy`  
_L15-34_
- inherits: `FPrimitiveSceneProxy`
- L18 _public prototype_ `FPVBoneSceneProxy(const UPVBoneComponent* InComponent);`
- L20 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L21 _public prototype_ `virtual void GetDynamicMeshElements( const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector ) const override;`
- L28 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L29 _public prototype_ `virtual uint32 GetMemoryFootprint(void) const override;`
- L31 _public prototype_ `virtual bool CanBeOccluded() const override;`
- L33 _private member_ `const TObjectPtr<const UPVBoneComponent> BoneComponent;`

#### struct `FPVBoneInfo`  
`struct FPVBoneInfo`  
_L37-44_
- reflection: `USTRUCT()`
- L41 _public member_ `FVector StartPos;`
- L42 _public member_ `FVector EndPos;`
- L43 _public member_ `FLinearColor Color;`

#### class `UPVBoneComponent`  
`class UPVBoneComponent : public UPrimitiveComponent`  
_L47-69_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UPrimitiveComponent`
- L52 _public prototype_ `UPVBoneComponent();`
- L54 _public prototype_ `void InitBounds();`
- L55 _public prototype_ `void AddBone(const FVector& InStartPos, const FVector& InEndPos, const FLinearColor& InColor = FLinearColor::White);`
- L57 _public prototype_ `void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) const;`
- L59 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L60 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L62 _public prototype_ `void SetCollection(const FManagedArrayCollection* const InSkeletonCollection);`
- L63 _public prototype_ `int GetBoneCount();`
- L66 _protected member_ `FBox BBox;`
- L67 _protected member_ `TArray<FPVBoneInfo> Bones;`
- L68 _protected member_ `const FManagedArrayCollection* SkeletonCollection;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/PVDataVisualization.h` (Private)


#### class `FPVDataVisualization`  
`class FPVDataVisualization : public IPCGSpatialDataVisualization`  
_L17-44_
- inherits: `IPCGSpatialDataVisualization`
- L20 _public prototype_ `FPVDataVisualization();`
- L23 _public prototype_ `virtual void ExecuteDebugDisplay(FPCGContext* Context, const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data, AActor* TargetActor) const override;`
- L24 _public prototype_ `virtual FPCGSetupSceneFunc GetViewportSetupFunc(const UPCGSettingsInterface* SettingsInterface, const UPCGData* Data) const override;`
- L28 _protected member_ `TMap<EPVRenderType, FPVRenderCallback> RenderMap;`
- L30 _protected prototype_ `void RegisterVisualizations();`
- L32 _protected prototype_ `void MeshRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L33 _protected prototype_ `void SkeletonRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L34 _protected prototype_ `void FoliageRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L35 _protected prototype_ `void BonesRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L36 _protected prototype_ `void FoliageGridRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L37 _protected prototype_ `void FoliageAttachmentPointsRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L38 _protected prototype_ `void SeedRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L39 _protected prototype_ `void TexturesRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L40 _protected prototype_ `void GrowerLeavesRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L41 _protected prototype_ `void GrafterPaletteGridRenderer(const UPVData* InData, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L42 _protected prototype_ `void PlantProfileRenderer(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`
- L43 _protected prototype_ `void SetupBoundingBoxOnly(const UPVData* Data, const FManagedArrayCollection& InCollection, FPCGSceneSetupParams& InOutParams, FBoxSphereBounds& OutBounds, const UPCGSettingsInterface* Settings);`

#### Free symbols / members of external scopes

- L15 _delegate_ `DECLARE_DELEGATE_FiveParams(FPVRenderCallback, const UPVData*, const FManagedArrayCollection&, FPCGSceneSetupParams&, FBoxSphereBounds&, const UPCGSettingsInterface*);`
- L15 _prototype_ `DECLARE_DELEGATE_FiveParams(FPVRenderCallback, const UPVData*, const FManagedArrayCollection&, FPCGSceneSetupParams&, FBoxSphereBounds&, const UPCGSettingsInterface*);`
- L46 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogProceduralVegetationDataVisualization, Log, All);`
- L46 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogProceduralVegetationDataVisualization, Log, All);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/PVLineBatchComponent.h` (Private)


#### enum `EPointDrawSettings`  
`enum class EPointDrawSettings : uint8`  
_L15-21_
- L17 _public enumerator_ `None`
- L18 _public enumerator_ `Start`
- L19 _public enumerator_ `End`
- L20 _public enumerator_ `Both`

#### struct `FPVLineInfo`  
`struct FPVLineInfo`  
_L23-30_
- L25 _public member_ `FVector StartPos;`
- L26 _public member_ `FVector EndPos;`
- L27 _public member_ `FLinearColor Color;`
- L28 _public member_ `ESceneDepthPriorityGroup DepthPriorityGroup = SDPG_World;`
- L29 _public member_ `EPointDrawSettings PointDrawSettings = EPointDrawSettings::None;`

#### struct `FPVPointInfo`  
`struct FPVPointInfo`  
_L32-38_
- L34 _public member_ `FVector PointLocation;`
- L35 _public member_ `float PointSize;`
- L36 _public member_ `FLinearColor Color;`
- L37 _public member_ `ESceneDepthPriorityGroup DepthPriorityGroup = SDPG_World;`

#### class `FPVLineSceneProxy`  
`class FPVLineSceneProxy final : public FPrimitiveSceneProxy`  
_L40-61_
- inherits: `FPrimitiveSceneProxy`
- L43 _private member_ `TArray<FPVLineInfo> Lines;`
- L44 _private member_ `TArray<FPVPointInfo> Points;`
- L45 _private member_ `float PointSize;`
- L48 _public prototype_ `FPVLineSceneProxy(const UPVLineBatchComponent* InComponent);`
- L50 _public prototype_ `virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;`
- L51 _public prototype_ `virtual void GetDynamicMeshElements( const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector ) const override;`
- L58 _public prototype_ `virtual SIZE_T GetTypeHash() const override;`
- L59 _public prototype_ `virtual uint32 GetMemoryFootprint(void) const override;`
- L60 _public prototype_ `virtual bool CanBeOccluded() const override;`

#### class `UPVLineBatchComponent`  
`class UPVLineBatchComponent : public UPrimitiveComponent`  
_L64-96_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UPrimitiveComponent`
- L72 _public prototype_ `UPVLineBatchComponent();`
- L74 _public prototype_ `void InitBounds();`
- L76 _public prototype_ `void AddLine(const FVector& InStartPos, const FVector& InEndPos, const FLinearColor& InColor, const ESceneDepthPriorityGroup InDepthPriorityGroup, const EPointDrawSettings InPointDrawSettings = EPointDrawSettings::None);`
- L78 _public prototype_ `void AddSphere(const FVector& InPos, float Radius, const FLinearColor& InColor, const ESceneDepthPriorityGroup InDepthPriorityGroup);`
- L80 _public prototype_ `void AddPoint(const FVector& PointLocation, float PointSize, const FLinearColor& InColor, const ESceneDepthPriorityGroup InDepthPriorityGroup);`
- L82 _public prototype_ `void AddPoints(const TArray<FPVPointInfo>& InPoints);`
- L84 _public prototype_ `void Flush();`
- L86 _public prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L87 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`
- L90 _protected member_ `FBox BBox;`
- L91 _protected member_ `TArray<FPVLineInfo> Lines;`
- L92 _protected member_ `TArray<FPVPointInfo> Points;`
- L95 _private member_ `const float PointSize = 5.0f;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/PVScaleVisualizationComponent.h` (Private)


#### class `UPVScaleVisualizationComponent`  
`class UPVScaleVisualizationComponent : public UPVLineBatchComponent`  
_L15-37_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UPVLineBatchComponent`
- L20 _public prototype_ `UPVScaleVisualizationComponent();`
- L22 _public prototype_ `FBoxSphereBounds& GetScaleBounds();`
- L23 _public prototype_ `const FBoxSphereBounds& GetScaleBounds() const;`
- L24 _public prototype_ `void SetScaleBounds(const FBoxSphereBounds& InBounds);`
- L26 _public prototype_ `TObjectPtr<UTextRenderComponent> GetTextRenderComponent(int32 Index) const;`
- L27 _public prototype_ `const TStaticArray<TObjectPtr<UTextRenderComponent>, 3>& GetTextRenderComponents() const;`
- L29 _public prototype_ `virtual void OnRegister() override;`
- L31 _public prototype_ `void UpdateScaleVisualizations();`
- L34 _private member_ `FBoxSphereBounds Bounds;`
- L36 _private member_ `TStaticArray<TObjectPtr<UTextRenderComponent>, 3> TextRenderComponents = {nullptr, nullptr, nullptr};`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Visualizations/PVSkeletonVisualizerComponent.h` (Private)


#### class `UPVSkeletonVisualizerComponent`  
`class UPVSkeletonVisualizerComponent : public UPVLineBatchComponent`  
_L23-74_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta=(BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UPVLineBatchComponent`
- L28 _public prototype_ `UPVSkeletonVisualizerComponent();`
- L30 _public prototype_ `const FManagedArrayCollection* GetCollection() const;`
- L31 _public prototype_ `void SetCollection(const FManagedArrayCollection* const InSkeletonCollection);`
- L33 _public prototype_ `void RebuildSkeleton();`
- L35 _public prototype_ `TObjectPtr<UDynamicMeshComponent> GetDynamicMeshComponent() const;`
- L36 _public prototype_ `const UE::Geometry::FDynamicMeshAABBTree3& GetDynamicMeshOctree() const;`
- L38 _public prototype_ `TObjectPtr<UInstancedStaticMeshComponent> GetPointMeshInstancerComponent() const;`
- L40 _public prototype_ `bool GetPointDataFromInstanceIndex(const int32 InstanceIndex, int32& BranchIndex, int32& BranchPointIndex);`
- L42 _public prototype_ `ESkeletonVisualizationModes GetVisualizationMode() const;`
- L43 _public prototype_ `void SetVisualizationMode(ESkeletonVisualizationModes InMode);`
- L45 _public prototype_ `void SetUseMeshPreview(bool bInUseMeshPreview);`
- L46 _public prototype_ `bool IsUsingMeshPreview() const;`
- L48 _public prototype_ `bool HasOctree() const;`
- L49 _public prototype_ `void SetBuildOctree(bool bInBuildOctree);`
- L51 _public prototype_ `TArray<FLinearColor> GetVisualizationColors() const;`
- L53 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnDrawPoint, const int32, FVector&);`
- L54 _public member_ `FOnDrawPoint OnDrawPoint;`
- L58 _protected member_ `TObjectPtr<UDynamicMeshComponent> PreviewMeshComponent;` — `UPROPERTY()`
- L61 _protected member_ `TObjectPtr<UInstancedStaticMeshComponent> PointMeshInstancer;` — `UPROPERTY()`
- L63 _protected member_ `UE::Geometry::FDynamicMeshAABBTree3 EdgeMeshOctree;`
- L65 _protected member_ `TUniquePtr<PV::Visualizations::FPVEdgeMeshGenerator> EdgeMeshGenerator;`
- L68 _private member_ `const FManagedArrayCollection* SkeletonCollection = nullptr;`
- L70 _private member_ `TArray<TPair<int32, int32>> InstanceToPointData;`
- L71 _private member_ `ESkeletonVisualizationModes CurrentVisualizationMode = ESkeletonVisualizationModes::None;`
- L72 _private member_ `bool bUseMeshPreview = false;`
- L73 _private member_ `bool bBuildOctree = false;`

#### Free symbols / members of external scopes

- L53 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FOnDrawPoint, const int32, FVector&);`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Widgets/SPVCreateDialog.h` (Private)


#### class `SPVCreateDialog`  
`class SPVCreateDialog : public SCompoundWidget`  
_L11-37_
- inherits: `SCompoundWidget`
- L14 _public function_ `SLATE_BEGIN_ARGS(SPVCreateDialog)`
- L20 _private prototype_ `bool GetCreateButtonEnabled() const;`
- L22 _private prototype_ `FReply OnProceduralVegetationCreate();`
- L23 _private prototype_ `FReply OnProceduralVegetationCreateNew();`
- L24 _private prototype_ `FReply OnProceduralVegetationCancelled();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L29 _public prototype_ `static bool OpenCreateModal(const FText& TitleText, TObjectPtr<UProceduralVegetation>& SampleProceduralVegetation);`
- L31 _private member_ `TWeakPtr<SWindow> WeakParentWindow;`
- L33 _private member_ `bool bPressedOk = false;`
- L34 _private member_ `bool bCreateNew = false;`
- L36 _private member_ `FAssetData SelectedProceduralVegetation;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Widgets/SPVExportSelectionDialog.h` (Private)


#### enum `EPVExportType`  
`enum class EPVExportType : int32`  
_L29-33_
- reflection: `UENUM()`
- L31 _public enumerator_ `Batch`
- L32 _public enumerator_ `Selected`

#### class `SPVExportSelectionDialog`  
`class SPVExportSelectionDialog : public SWindow`  
_L35-83_
- inherits: `SWindow`
- L37 _private function_ `SLATE_BEGIN_ARGS(SPVExportSelectionDialog)`
- L45 _public prototype_ `void Construct(const FArguments& InArgs);`
- L48 _public prototype_ `EAppReturnType::Type ShowModal();` — Displays the dialog in a blocking fashion
- L51 _private prototype_ `FReply OnButtonClick(EAppReturnType::Type ButtonID);`
- L53 _private prototype_ `TSharedRef<ITableRow> OnGenerateExportItem(TObjectPtr<UPVExportEntry> InExportEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L54 _private prototype_ `TSharedRef<ITableRow> OnGenerateStatItem(TSharedPtr<FStatType> InStatEntry, const TSharedRef<STableViewBase>& OwnerTable);`
- L56 _private prototype_ `void OnExportEntrySelected(TObjectPtr<UPVExportEntry> InExportEntry, ESelectInfo::Type SelectInfo = ESelectInfo::Direct);`
- L57 _private prototype_ `void SetupCurrentExportEntryStats();`
- L59 _private prototype_ `EPVExportType GetExportType() const;`
- L60 _private prototype_ `void OnExportTypeChanged(const EPVExportType InNewValue);`
- L61 _private prototype_ `void SetExportType();`
- L63 _private prototype_ `void UpdateExportButtonState();`
- L66 _private member_ `TSharedPtr<SScrollBox> ScrollBox;`
- L68 _private member_ `TSharedPtr<SPrimaryButton> ExportButton;`
- L69 _private member_ `TSharedPtr<SListView<TSharedPtr<FStatType>>> StatTableView;`
- L70 _private member_ `TSharedPtr<SListView<TObjectPtr<UPVExportEntry>>> ExportEntriesTableView;`
- L72 _private member_ `TArray<TObjectPtr<UPVExportEntry>> ExportEntries;`
- L74 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L76 _private member_ `TObjectPtr<UPVExportEntry> CurrentlySelectedEntry = nullptr;`
- L78 _private member_ `TArray<TSharedPtr<FStatType>> CurrentExportEntryStats;`
- L80 _private member_ `EPVExportType ExportType = EPVExportType::Selected;`
- L82 _private member_ `EAppReturnType::Type UserResponse = EAppReturnType::Type::Cancel;`

#### Free symbols / members of external scopes

- L26 _typedef_ `using FStatType = TPair<FText, int32>;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Private/Widgets/SPVGradientBox.h` (Private)


#### class `SPVGradientBox`  
`class SPVGradientBox : public SCompoundWidget`  
_L6-24_
- inherits: `SCompoundWidget`
- L8 _private function_ `SLATE_BEGIN_ARGS(SPVGradientBox)`
- L13 _public prototype_ `void Construct(const FArguments& InArgs);`
- L15 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L18 _public prototype_ `virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;`
- L21 _private member_ `float BoxSize = 0.0f;`
- L23 _private member_ `TArray<FSlateGradientStop> GradientStops;`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Public/PVEditorSettings.h` (Public)


#### class `UPVEditorSettings`  
`class UPVEditorSettings : public UObject`  
_L10-50_
- reflection: `UCLASS(MinimalAPI, config=EditorPerProjectUserSettings, meta = (DisplayName = "Procedural Vegetation Editor Settings"))`
- inherits: `UObject`
- L17 _public member_ `FLinearColor GrowthDataPinColor = FColor(239, 239, 239);` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type GrowthData
- L21 _public member_ `FLinearColor MeshDataPinColor = FColor(3, 234, 234);` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type MeshData
- L25 _public member_ `FLinearColor FoliageMeshDataPinColor = FColor(0, 255, 0);` — `UPROPERTY(EditAnywhere, config, Category = Node, meta = (HideAlphaChannel))` — Color used for data pins of type FoliageMeshData
- L28 _public member_ `bool bShowMannequin = false;` — `UPROPERTY(EditAnywhere, config, Category = Viewport)`
- L31 _public member_ `float MannequinOffset = 0.0f;` — `UPROPERTY(EditAnywhere, config, Category = Viewport)`
- L34 _public member_ `bool bShowScaleVisualization = false;` — `UPROPERTY(EditAnywhere, config, Category = Viewport)`
- L37 _public member_ `bool bShowStats = true;` — `UPROPERTY(EditAnywhere, config, Category = Export)`
- L40 _public member_ `bool bAutoFocusViewport = false;` — `UPROPERTY(EditAnywhere, config, Category = Export)`
- L43 _public member_ `bool bUseMeshSkeletonPreview = false;` — `UPROPERTY(EditAnywhere, config, Category = Viewport)`
- L46 _public member_ `float PointScaleBias = 1.2f;` — `UPROPERTY(EditAnywhere, config, Category = Viewport, meta = (UIMin=0.0f, ClampMin=0.0f))`
- L49 _public member_ `FLinearColor SkeletonDefaultColor = FLinearColor::White;` — `UPROPERTY(EditAnywhere, config, Category = Viewport)`

### `Plugins/Experimental/ProceduralVegetationEditor/Source/ProceduralVegetationEditor/Public/ProceduralVegetationEditorModule.h` (Public)


#### class `FProceduralVegetationEditorModule`  
`class FProceduralVegetationEditorModule : public IModuleInterface`  
_L19-44_
- inherits: `IModuleInterface`
- L23 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L24 _public prototype_ `virtual void ShutdownModule() override;`
- L28 _private member_ `TSharedPtr<class IFabWorkflowFactory> MegaSeedImportWorkflowFactory;`
- L29 _private member_ `FDelegateHandle LevelEditorExtenderDelegateHandle;`
- L31 _private prototype_ `void RegisterMenus();`
- L32 _private prototype_ `void ExecuteOpenInPVEditor(const FToolMenuContext& InContext);`
- L33 _private prototype_ `bool CanExecuteOpenInPVEditor(const FToolMenuContext& InContext);`
- L35 _private prototype_ `void RegisterLevelEditorMenuExtension();`
- L36 _private prototype_ `void UnregisterLevelEditorMenuExtension();`
- L37 _private prototype_ `void RegisterPinColorAndIcons();`
- L38 _private prototype_ `void UnregisterPinColorAndIcons();`
- L40 _private prototype_ `static TSharedRef<FExtender> OnExtendLevelEditorActorSelectionMenu(const TSharedRef<FUICommandList> InCommandList, TArray<AActor*> InSelectedActors);`
- L41 _private prototype_ `static void ExecuteOpenInPVEditorOnSelectedActors();`
- L42 _private prototype_ `static UProceduralVegetation* GetProceduralVegetationFromAsset(UObject* InObject);`
- L43 _private prototype_ `static UProceduralVegetation* GetProceduralVegetationFromActor(AActor* InActor);`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace PVEditor`
- L14 _externvar_ `extern const FName MessageLogName;` (scope `PVEditor`)
- L17 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogProceduralVegetationEditor, Log, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogProceduralVegetationEditor, Log, All);`
