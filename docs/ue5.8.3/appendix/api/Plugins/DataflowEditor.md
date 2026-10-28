# Plugins / DataflowEditor

- module root: `Plugins/Dataflow/Source/DataflowEditor`
- headers: 121; symbols: 3505
- symbol kinds: class=184, delegate=20, enum=25, enumerator=85, externvar=1, function=329, macro=41, member=929, namespace=154, prototype=1648, struct=54, typedef=32, variable=3
- PrivateDependencyModuleNames: ContentBrowser, SkeletalMeshModelingTools, TedsOutliner
- PublicDependencyModuleNames: AdvancedPreviewScene, AnimGraph, AppFramework, ApplicationCore, AssetDefinition, AssetRegistry, AssetTools, BaseCharacterFXEditor, BlueprintGraph, Chaos, ChaosCaching, Core, CoreUObject, DataflowCore, DataflowEngine, DataflowEnginePlugin, DataflowNodes, DataflowSimulation, DetailCustomizations, DeveloperSettings, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorStyle, EditorSubsystem, EditorWidgets, Engine, GeometryCache, GeometryCacheEd, GeometryCollectionEngine, GeometryCore, GeometryFramework, GraphEditor, ImageCore, InputCore, InteractiveToolsFramework, KismetWidgets, LevelEditor, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsEditorOnly, MeshModelingToolsEditorOnlyExp, MeshModelingToolsExp, MessageLog, ModelingComponents, ModelingComponentsEditorOnly, ModelingToolsEditorMode, PlanarCut, Projects, PropertyEditor, RHI, RenderCore, SceneOutliner, SequencerWidgets, SharedSettingsWidgets, SkeletalMeshDescription, SkeletonEditor, Slate, SlateCore, StaticMeshDescription, StructUtilsEditor, TedsOutliner, TimeManagement, ToolMenus, ToolWidgets, TypedElementFramework, TypedElementRuntime, UnrealEd, WidgetRegistration, WorkspaceMenuStructure, XmlParser
- PublicIncludePathModuleNames: SkeletonEditor

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/AssetDefinition_DataflowContext.h` (Private)


#### class `UAssetDefinition_DataflowContext`  
`class UAssetDefinition_DataflowContext : public UAssetDefinitionDefault`  
_L12-24_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L18 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L19 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L20 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L21 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L22 _private prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L23 _private prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const override;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowAdvancedPreviewDetailsTab.h` (Private)


#### class `SDataflowAdvancedPreviewDetailsTab`  
`class SDataflowAdvancedPreviewDetailsTab : public SCompoundWidget`  
_L21-89_
- inherits: `SCompoundWidget`
- L24 _public function_ `SLATE_BEGIN_ARGS(SDataflowAdvancedPreviewDetailsTab) : _ProfileIndexStorage(nullptr), _AdditionalSettings(nullptr)`
- L47 _public prototype_ `SDataflowAdvancedPreviewDetailsTab();`
- L48 _public prototype_ `~SDataflowAdvancedPreviewDetailsTab();`
- L51 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);` — SWidget functions
- L53 _public prototype_ `void Refresh();`
- L56 _protected prototype_ `void CreateSettingsView();`
- L57 _protected prototype_ `void ComboBoxSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type );`
- L58 _protected prototype_ `void UpdateSettingsView();`
- L59 _protected prototype_ `void UpdateProfileNames();`
- L60 _protected prototype_ `FReply AddProfileButtonClick();`
- L61 _protected prototype_ `FReply RemoveOrResetProfileButtonClick();`
- L63 _protected prototype_ `void OnAssetViewerSettingsRefresh(const FName& InPropertyName);`
- L64 _protected prototype_ `void OnAssetViewerSettingsPostUndo();`
- L67 _protected member_ `TSharedPtr<IDetailsView> SettingsView;` — Property viewing widget
- L68 _protected member_ `TSharedPtr<STextComboBox> ProfileComboBox;`
- L69 _protected member_ `TWeakPtr<FAdvancedPreviewScene> PreviewScenePtr;`
- L70 _protected member_ `UAssetViewerSettings* DefaultSettings;`
- L71 _protected member_ `UObject* AdditionalSettings;`
- L73 _protected member_ `TArray<TSharedPtr<FString>> ProfileNames;`
- L74 _protected member_ `int32 ProfileIndex;`
- L76 _protected prototype_ `void OnPreviewSceneChanged(TSharedRef<FAdvancedPreviewScene> PreviewScene);`
- L78 _protected member_ `FDelegateHandle RefreshDelegate;`
- L79 _protected member_ `FDelegateHandle AddRemoveProfileDelegate;`
- L80 _protected member_ `FDelegateHandle PostUndoDelegate;`
- L82 _protected member_ `TSharedPtr<FDataflowPreviewProfileController::IProfileIndexStorage> ProfileIndexStorage;`
- L84 _protected member_ `TArray<FAdvancedPreviewSceneModule::FDetailCustomizationInfo> DetailCustomizations;`
- L86 _protected member_ `TArray<FAdvancedPreviewSceneModule::FPropertyTypeCustomizationInfo> PropertyTypeCustomizations;`
- L88 _protected member_ `TArray<FAdvancedPreviewSceneModule::FDetailDelegates> Delegates;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowAnyTypeCustomization.h` (Private)


#### class `UE::Dataflow::FAnyTypeCustomizationBase`  
`class FAnyTypeCustomizationBase : public IPropertyTypeCustomization`  
_L17-24_
- inherits: `IPropertyTypeCustomization`
- L21 _private function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override`

#### class `UE::Dataflow::FNumericAnyTypeCustomization`  
`class FNumericAnyTypeCustomization : public FAnyTypeCustomizationBase`  
_L28-38_
- inherits: `FAnyTypeCustomizationBase`
- L32 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L36 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::Dataflow::FBoolAnyTypeCustomization`  
`class FBoolAnyTypeCustomization : public FAnyTypeCustomizationBase`  
_L42-52_
- inherits: `FAnyTypeCustomizationBase`
- L46 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L50 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::Dataflow::FStringAnyTypeCustomization`  
`class FStringAnyTypeCustomization : public FAnyTypeCustomizationBase`  
_L56-66_
- inherits: `FAnyTypeCustomizationBase`
- L60 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L64 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::Dataflow::FStringConvertibleAnyTypeCustomization`  
`class FStringConvertibleAnyTypeCustomization : public FAnyTypeCustomizationBase`  
_L70-80_
- inherits: `FAnyTypeCustomizationBase`
- L74 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L78 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::Dataflow::FVectorAnyTypeCustomization`  
`class FVectorAnyTypeCustomization : public FAnyTypeCustomizationBase`  
_L84-94_
- inherits: `FAnyTypeCustomizationBase`
- L88 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L92 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### class `UE::Dataflow::FTransformAnyTypeCustomization`  
`class FTransformAnyTypeCustomization : public FAnyTypeCustomizationBase`  
_L98-108_
- inherits: `FAnyTypeCustomizationBase`
- L102 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L106 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Dataflow` (scope `UE`)
- L112 _prototype_ `void RegisterAnyTypeCustomizations(FPropertyEditorModule& PropertyModule);` (scope `UE::Dataflow`)
- L113 _prototype_ `void UnregisterAnyTypeCustomizations(FPropertyEditorModule& PropertyModule);` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowAssetViewerSettingsCustomization.h` (Private)


#### class `FDataflowAssetViewerSettingsCustomization`  
`class FDataflowAssetViewerSettingsCustomization : public IDetailCustomization`  
_L24-61_
- inherits: `IDetailCustomization`
- L28 _public prototype_ `FDataflowAssetViewerSettingsCustomization(TSharedPtr<FDataflowPreviewProfileController::IProfileIndexStorage> ProfileIndexStorage);`
- L31 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L37 _protected prototype_ `FText OnGetProfileName() const;` — Callbacks for customized SEditableTextBox
- L38 _protected prototype_ `void OnProfileNameChanged(const FText& InNewText);`
- L39 _protected prototype_ `void OnProfileNameCommitted(const FText& InNewText, ETextCommit::Type InTextCommit);`
- L42 _protected prototype_ `const bool IsProfileNameValid(const FString& NewName);` — Check whether or not the given profile name is valid by cross-referencing it with existing names
- L43 _protected prototype_ `bool CanSetSharedProfile() const;`
- L44 _protected prototype_ `EVisibility ShowFileWatcherWidget() const;`
- L45 _protected prototype_ `FString SharedProfileConfigFilePath() const;`
- L50 _private member_ `TSharedPtr<SEditableTextBox> NameEditTextBox;` — Customized name edit text box used for the profile name
- L52 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;` — Cached data
- L54 _private member_ `TSharedPtr<SSettingsEditorCheckoutNotice> FileWatcherWidget;` — Watcher widget for the default config file (checks file status / SCC state).
- L56 _private member_ `int32 ProfileIndex;`
- L57 _private member_ `UAssetViewerSettings* ViewerSettings;`
- L58 _private member_ `bool bValidProfileName;`
- L60 _private member_ `TSharedPtr<FDataflowPreviewProfileController::IProfileIndexStorage> ProfileIndexStorage;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowCollectionSpreadSheet.h` (Private)


#### class `FDataflowCollectionSpreadSheet`  
`class FDataflowCollectionSpreadSheet : public FDataflowNodeView`  
_L17-36_
- inherits: `FDataflowNodeView`
- desc: Class to handle the SelectionView widget
- L21 _public prototype_ `FDataflowCollectionSpreadSheet(TObjectPtr<UDataflowBaseContent> InContent = nullptr);`
- L22 _public prototype_ `~FDataflowCollectionSpreadSheet();`
- L24 _public prototype_ `virtual void SetSupportedOutputTypes() override;`
- L25 _public prototype_ `virtual void UpdateViewData() override;`
- L26 _public function_ `virtual void ConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override`
- L27 _public function_ `virtual void SimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override`
- L29 _public prototype_ `void SetCollectionSpreadSheet(TSharedPtr<SCollectionSpreadSheetWidget>& InCollectionSpreadSheet);`
- L32 _private member_ `TSharedPtr<SCollectionSpreadSheetWidget> CollectionSpreadSheet;`
- L34 _private member_ `FDelegateHandle OnPinnedDownChangedDelegateHandle;`
- L35 _private member_ `FDelegateHandle OnRefreshLockedChangedDelegateHandle;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowCollectionSpreadSheetHelpers.h` (Private)


#### struct `UE::Dataflow::CollectionSpreadSheetHelpers::FAttrInfo`  
`struct FAttrInfo`  
_L14-18_
- L16 _public member_ `FName Name;`
- L17 _public member_ `FString Type;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)
- L12 _namespace_ `namespace CollectionSpreadSheetHelpers` (scope `UE::Dataflow`)
- L20 _variable_ `static TMap<FString, int32> AttrTypeWidthMap = { { TEXT("Transform"), 600 }, { TEXT("Transform3f"), 600 }, { TEXT("String"), 200 }, { TEXT("Name"), 200 }, { TEXT("LinearColor"), 80 }, { TEXT("int32"), 100 }, { TEXT("IntArray"), 200 }, { TEXT("Vector"), 250 }, { TEXT("Vector2D"), 160 }, { TEXT("Float"), 150 }, { TEXT("Double"), 150 }, { TEXT("IntVector"), 220 }, { TEXT("Bool"), 75 }, { TEXT("Box"), 550 }, { TEXT("MeshSection"), 100 }, { TEXT("UInt8"), 100 }, { TEXT("Guid"), 350 }, };` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L41 _prototype_ `FString AttributeValueToString(float Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L43 _prototype_ `FString AttributeValueToString(double Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L45 _prototype_ `FString AttributeValueToString(uint8 Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L47 _prototype_ `FString AttributeValueToString(int32 Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L49 _prototype_ `FString AttributeValueToString(const FString& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L51 _prototype_ `FString AttributeValueToString(const FName& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L53 _prototype_ `FString AttributeValueToString(const FLinearColor& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L55 _prototype_ `FString AttributeValueToString(const FVector& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L57 _prototype_ `FString AttributeValueToString(bool Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L59 _prototype_ `FString AttributeValueToString(const FConstBitReference& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L61 _prototype_ `FString AttributeValueToString(const TSet<int32>& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L63 _prototype_ `FString AttributeValueToString(const FTransform3f& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L65 _prototype_ `FString AttributeValueToString(const FTransform& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L67 _prototype_ `FString AttributeValueToString(const FBox& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L69 _prototype_ `FString AttributeValueToString(const FVector4f& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L71 _prototype_ `FString AttributeValueToString(const FVector3f& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L73 _prototype_ `FString AttributeValueToString(const FVector2f& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L75 _prototype_ `FString AttributeValueToString(const FIntVector& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L77 _prototype_ `FString AttributeValueToString(const FIntVector2& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L79 _prototype_ `FString AttributeValueToString(const FIntVector4& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L81 _prototype_ `FString AttributeValueToString(const FGuid& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L83 _prototype_ `FString AttributeValueToString(const FSoftObjectPath& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L85 _prototype_ `FString AttributeValueToString(const TObjectPtr<UObject>& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L87 _prototype_ `FString AttributeValueToString(const Chaos::FConvexPtr& Value);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L89 _prototype_ `FString AttributeValueToString(const FManagedArrayCollection& InCollection, const FName& InAttributeName, const FName& InGroupName, int32 InIdxColumn);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L91 _function_ `inline FName GetArrayTypeString(FManagedArrayCollection::EArrayType ArrayType)` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L95 _macro_ `#define MANAGED_ARRAY_TYPE(a,A) case EManagedArrayType::F##A##Type:\`
- L103 _prototype_ `FColor GetColorPerDepth(uint32 Depth);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L105 _prototype_ `FSlateColor UpdateItemColorFromCollection(const TSharedPtr<const FManagedArrayCollection> InCollection, const FName InGroup, const int32 InItemIndex);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)
- L107 _prototype_ `TSharedRef<SWidget> MakeColumnWidget(const TSharedPtr<const FManagedArrayCollection> InCollection, const FName InGroup, const FName InAttr, const int32 InItemIndex, const FSlateColor InItemColor);` (scope `UE::Dataflow::CollectionSpreadSheetHelpers`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowComponentToolTarget.h` (Private)


#### class `UDataflowComponentReadOnlyToolTarget`  
`class UDataflowComponentReadOnlyToolTarget : public UPrimitiveComponentToolTarget, public IMeshDescriptionProvider, public IDynamicMeshProvider, public IMaterialProvider`  
_L23-56_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UPrimitiveComponentToolTarget,IMeshDescriptionProvider,IDynamicMeshProvider,IMaterialProvider`
- desc: A tool target backed by a read-only dataflow component that can provide and take a mesh description.
- L34 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget implementation
- L37 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L38 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L41 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L42 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L43 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;`
- L44 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override;`
- L47 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider
- L55 _protected member_ `TUniquePtr<FMeshDescription> DataflowMeshDescription;` — Until UDataflow stores its internal representation as FMeshDescription, we need to retain the storage here to cover the lifetime of the pointer returned by GetMeshDescription().

#### class `UDataflowComponentToolTarget`  
`class UDataflowComponentToolTarget : public UDataflowComponentReadOnlyToolTarget, public IMeshDescriptionCommitter, public IDynamicMeshCommitter`  
_L63-82_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDataflowComponentReadOnlyToolTarget,IMeshDescriptionCommitter,IDynamicMeshCommitter`
- desc: A tool target backed by a dataflow component that can provide and take a mesh description.
- L72 _public prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitParams = FCommitMeshParameters()) override;` — IMeshDescriptionCommitter implementation
- L76 _public prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo& CommitInfo) override;` — IDynamicMeshCommitter

#### class `UDataflowComponentReadOnlyToolTargetFactory`  
`class UDataflowComponentReadOnlyToolTargetFactory : public UToolTargetFactory`  
_L87-96_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UDataflowComponentReadOnlyToolTarget to be used by the target manager.
- L94 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;` — UToolTargetFactory implementation
- L95 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### class `UDataflowComponentToolTargetFactory`  
`class UDataflowComponentToolTargetFactory : public UToolTargetFactory`  
_L101-110_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UDataflowComponentToolTarget to be used by the target manager.
- L108 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;` — UToolTargetFactory implementation
- L109 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowConstructionViewport.h` (Private)


#### class `SDataflowConstructionViewport`  
`class SDataflowConstructionViewport : public SBaseCharacterFXEditorViewport, public ICommonEditorViewportToolbarInfoProvider`  
_L18-63_
- inherits: `SBaseCharacterFXEditorViewport,ICommonEditorViewportToolbarInfoProvider`
- L21 _public function_ `SLATE_BEGIN_ARGS(SDataflowConstructionViewport)`
- L22 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FDataflowConstructionViewportClient>, ViewportClient) SLATE_END_ARGS() SDataflowConstructionViewport();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportConstructionArgs);`
- L30 _public prototype_ `virtual void BindCommands() override;` — SEditorViewport
- L31 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L32 _public prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L33 _public prototype_ `virtual bool IsVisible() const override;`
- L34 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L37 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider
- L38 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L39 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L40 _public prototype_ `virtual void PopulateViewportOverlays(TSharedRef<SOverlay> Overlay) override;`
- L42 _public prototype_ `FText GetOverlayText() const;`
- L43 _public prototype_ `bool HasEditorModeMessage() const;`
- L44 _public prototype_ `FText GetEditorModeMessage() const;`
- L45 _public prototype_ `EVisibility GetEditorModeMessageVisibility() const;`
- L46 _public prototype_ `void FocusViewportToSelection(bool bInstant);`
- L48 _public function_ `TSharedPtr<FDataflowConstructionViewportClient> GetDataflowClient() const`
- L51 _private prototype_ `static void BuildVisualizationMenu(FToolMenuSection& MenuSection);`
- L52 _private prototype_ `static void BuildViewMenu(FToolMenuSection& MenuSection);`
- L54 _private prototype_ `TWeakPtr<FDataflowConstructionScene> GetConstructionScene() const;`
- L56 _private member_ `TSharedPtr<FDataflowConstructionViewportClient> DataflowClient;`
- L59 _private member_ `TSharedPtr<SRichTextBlock> OverlayText;` — Pointer to the box into which the overlay text items are added
- L60 _private member_ `TSharedPtr<SErrorText> MessageWidget;`
- L62 _private prototype_ `UDataflowEditorMode* GetEdMode() const;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorBlueprintLibrary.h` (Private)


#### class `UDataflowEditorBlueprintLibrary`  
`class UDataflowEditorBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L11-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L20 _public prototype_ `static FName AddDataflowNode(UDataflow* Dataflow, FName NodeTypeName, FName BaseName, FVector2D Location);` — `UFUNCTION(BlueprintCallable, Category = "DataflowEditor", meta = (Keywords = "Dataflow Editor Graph Node"))` — Add a specific node , return the node name
- L26 _public prototype_ `static bool ConnectDataflowNodes(UDataflow* Dataflow, FName FromNodeName, FName OutputName, FName ToNodeName, FName InputName);` — `UFUNCTION(BlueprintCallable, Category = "DataflowEditor", meta = (Keywords = "Dataflow Editor Graph Node"))` — Connect the output oif a node to the input of another
- L29 _public prototype_ `static bool AddDataflowFromClipboardContent(UDataflow* Dataflow, const FString& ClipboardContent, FVector2D Location);` — `UFUNCTION(BlueprintCallable, Category = "DataflowEditor", meta = (Keywords = "Dataflow Editor Graph Node"))`
- L32 _public prototype_ `static bool SetDataflowNodeProperty(UDataflow* Dataflow, FName NodeName, FName PropertyName, FString Propertyvalue);` — `UFUNCTION(BlueprintCallable, Category = "DataflowEditor", meta = (Keywords = "Dataflow Editor Graph Node"))`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorCollectionComponent.h` (Private)


#### class `UDataflowEditorCollectionComponent`  
`class UDataflowEditorCollectionComponent : public UDynamicMeshComponent`  
_L16-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDynamicMeshComponent`
- desc: FleshComponent
- L22 _public member_ `int32 MeshIndex = INDEX_NONE;` — `UPROPERTY()`
- L25 _public member_ `TObjectPtr<const UDataflowEdNode> Node = nullptr;` — `UPROPERTY()`
- L28 _public member_ `TObjectPtr<UMeshWireframeComponent> WireframeComponent = nullptr;` — `UPROPERTY()`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorMode.h` (Private)


#### class `UDataflowEditorMode`  
`class UDataflowEditorMode final : public UBaseCharacterFXEditorMode`  
_L46-287_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UBaseCharacterFXEditorMode`
- desc: The dataflow editor mode is the mode used in the cloth asset editor. It holds most of the inter-tool state. We put things in a mode instead of directly into the asset editor in case we want to someday use the mode in multiple asset editors.
- L52 _public member_ `const static FEditorModeID EM_DataflowEditorModeId;`
- L54 _public prototype_ `UDataflowEditorMode();`
- L56 _public prototype_ `void SetDataflowEditor(UDataflowEditor* InDataflowEditor);`
- L57 _public function_ `TWeakPtr<FDataflowConstructionViewportClient, ESPMode::ThreadSafe> GetConstructionViewportClient()`
- L62 _public prototype_ `virtual FBox SceneBoundingBox() const override;` — Gets the scene bounding box
- L65 _public prototype_ `FBox SelectionBoundingBox() const;` — Bounding box for selected rest space mesh components
- L70 _public prototype_ `static const FToolTargetTypeRequirements& GetToolTargetRequirements();` — Gets the tool target requirements for the mode.
- L75 _public prototype_ `void SetConstructionViewMode(const FName& NewViewModeName);` — Construction View Mode
- L76 _public prototype_ `void SetConstructionViewModeForNode(const UDataflowEdNode* Node);`
- L78 _public prototype_ `const UE::Dataflow::IDataflowConstructionViewMode* GetConstructionViewMode() const;`
- L79 _public prototype_ `bool CanChangeConstructionViewModeTo(const FName& NewViewModeName) const;`
- L81 _public prototype_ `void ToggleConstructionViewWireframe();`
- L82 _public prototype_ `bool CanSetConstructionViewWireframeActive() const;`
- L83 _public function_ `bool IsConstructionViewWireframeActive() const`
- L89 _public prototype_ `void SetDataflowConstructionScene(TWeakPtr<FDataflowConstructionScene> InConstructionScene);` — Set the construction scene to store the dynamic meshes generated by the tools
- L90 _public function_ `const TWeakPtr<FDataflowConstructionScene>& GetDataflowConstructionScene()`
- L91 _public function_ `TWeakPtr<const FDataflowConstructionScene> GetDataflowConstructionScene() const`
- L94 _public function_ `void SetDataflowSimlationScene(TWeakPtr<FDataflowSimulationScene> InSimulationScene)` — Set the simulation scene to store the simulation components
- L95 _public function_ `const TWeakPtr<FDataflowSimulationScene>& GetDataflowSimulationScene()`
- L96 _public function_ `TWeakPtr<const FDataflowSimulationScene> GetDataflowSimulationScene() const`
- L99 _public prototype_ `void SetDataflowGraphEditor(TSharedPtr<SDataflowGraphEditor> DataflowGraphEditor);` — Set the data flow graph editor to create nodes once the tools have ended
- L101 _public function_ `TObjectPtr<UEditorInteractiveToolsContext> GetActiveToolsContext()`
- L106 _public prototype_ `void StartToolForSelectedNode(const UObject* SelectedNode);`
- L107 _public prototype_ `void ShutdownActiveToolIfNeeded(EToolShutdownType ShutdownType);`
- L109 _public prototype_ `void SetInputFocusOnConstructionViewport();`
- L115 _public prototype_ `const FName* FindRecentlyUsedViewMode(const TArray<FName>& AvailableViewModes) const;` — Each node has a set of view modes it can use. For each distinct set of available view modes, we store the last mode that the user has chosen. Use this function to find the most recently used view mode for nodes having the same set of available modes. Returns nullptr if there is nothing stored for the input set of modes
- L117 _public prototype_ `bool IsAnyNodeSelected() const;`
- L118 _public prototype_ `TObjectPtr<UDataflowEdNode> GetSelectedNode() const;`
- L119 _public prototype_ `FName GetSelectedNodeTypeName() const;`
- L121 _public function_ `FText GetUserMessage() const`
- L122 _public function_ `bool HasUserMessage() const`
- L129 _private prototype_ `virtual void Enter() final;` — UEdMode
- L130 _private prototype_ `virtual void Exit() override;`
- L131 _private prototype_ `virtual void ModeTick(float DeltaTime) override;`
- L132 _private prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;`
- L133 _private prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L134 _private prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L135 _private prototype_ `virtual void CreateToolkit() override;`
- L136 _private prototype_ `virtual void BindCommands() override;`
- L140 _private prototype_ `virtual void AddToolTargetFactories() override;` — UBaseCharacterFXEditorMode
- L141 _private prototype_ `virtual void RegisterTools() override;`
- L142 _private prototype_ `virtual void CreateToolTargets(const TArray<TObjectPtr<UObject>>& AssetsIn) override;`
- L143 _private prototype_ `virtual void InitializeTargets(const TArray<TObjectPtr<UObject>>& AssetsIn) override;`
- L146 _private prototype_ `void RegisterDataflowTool(TSharedPtr<FUICommandInfo> UICommand, FString ToolIdentifier, UInteractiveToolBuilder* Builder, UEditorInteractiveToolsContext* const ToolsContext, EToolsContextScope ToolScope = EToolsContextScope::Default);` — Use this function to register tools rather than UEdMode::RegisterTool() because we need to specify the ToolsContext
- L153 _private prototype_ `void AddNode(FName NewNodeType);` — Functions for quickly adding a node to the graph, e.g. when triggered by a toolbar button
- L154 _private prototype_ `bool CanAddNode(FName NewNodeType) const;`
- L156 _private prototype_ `void SetSimulationViewportClient(TWeakPtr<FDataflowSimulationViewportClient, ESPMode::ThreadSafe>);`
- L157 _private prototype_ `void RefocusSimulationViewportClient();`
- L158 _private prototype_ `void FirstTimeFocusSimulationViewport();`
- L160 _private prototype_ `void SetConstructionViewportClient(TWeakPtr<FDataflowConstructionViewportClient, ESPMode::ThreadSafe>);`
- L161 _private prototype_ `void RefocusConstructionViewportClient();`
- L162 _private prototype_ `void FirstTimeFocusConstructionViewport();`
- L163 _private prototype_ `bool IsComponentSelected(const UPrimitiveComponent* InComponent);`
- L164 _private prototype_ `void OnDataflowNodeDeleted(const TSet<UObject*>& DeletedNodes);`
- L170 _private prototype_ `UEdGraphNode* GetSingleSelectedNodeWithOutputType(const FName& SelectedNodeOutputTypeName) const;` — Return the single selected node in the Dataflow Graph Editor only if it has an output of the specified type If there is not a single node selected, or if it does not have the specified output, return null
- L175 _private prototype_ `UEdGraphNode* CreateNewNode(const FName& NewNodeTypeName);` — Create a node with the specified type in the graph
- L195 _private prototype_ `UEdGraphNode* CreateAndConnectNewNode(const FName& NewNodeTypeName, UEdGraphNode& UpstreamNode, const FName& ConnectionTypeName, const FName& NewNodeConnectionName);` — Create a node with the specified type, then connect it to the output of the specified UpstreamNode. If the specified output of the upstream node is already connected to another node downstream, we first break that connecttion, then insert the new node along the previous connection. We want to turn this: [UpstreamNode] ----> [DownstreamNode(s)] to this: [UpstreamNode] ----> [NewNode] ----> [DownstreamNode(s)] @param NewNodeTypeName The type of node to create, by name @param UpstreamNode Node to connect the new node to @param ConnectionTypeName The type of output of the upstream node to connect our new node to @param NewNodeConnectionName The name of the input/output connection on our new node that will be connected @return The newly-created node
- L198 _private prototype_ `void SetWireframeRenderToggleEnabled(bool bEnable);` — On all nodes in the graph, set whether the wireframe rendering toggle button is enabled
- L200 _private prototype_ `void InitializeContextObject();`
- L201 _private prototype_ `void DeleteContextObject();`
- L203 _private function_ `void SetPendingNodeSelectionChanged(bool bIsPending)`
- L209 _private prototype_ `const TArray<FName>& GetToolCategories();` — Get the tool categories from the construction scene
- L211 _private prototype_ `bool CanUseTools() const;`
- L212 _private prototype_ `bool CanSelectedNodeLaunchTool() const;`
- L213 _private prototype_ `bool IsSelectedNodeUpToDate(UE::Dataflow::FContext& Context) const;`
- L214 _private prototype_ `TSharedPtr<const FUICommandInfo> GetSelectedNodeToolCommand() const;`
- L215 _private prototype_ `bool IsDataflowEditable() const;`
- L217 _private prototype_ `TObjectPtr<UDataflowBaseContent> GetDataflowEditorContent() const;`
- L220 _private member_ `TWeakPtr<FDataflowConstructionScene> ConstructionScene;` — Dataflow construction scene from the toolkit
- L223 _private member_ `TWeakPtr<FDataflowSimulationScene> SimulationScene;` — Dataflow simulation scene from the toolkit
- L226 _private member_ `TMap<FName, TSharedPtr<const FUICommandInfo>> NodeTypeToAddNodeCommandMap;` — Correspondence between node types and commands to add the node to the graph
- L229 _private member_ `TMap<FName, TSharedPtr<const FUICommandInfo>> NodeTypeToToolCommandMap;` — Correspondence between node types and commands to launch tools
- L232 _private member_ `TWeakPtr<SDataflowGraphEditor> DataflowGraphEditor;` — Graph editor is required to add nodes once some tools are complete
- L235 _private member_ `const UE::Dataflow::IDataflowConstructionViewMode* ConstructionViewMode = nullptr;` — Points to a view mode owned by FRenderingViewModeFactory
- L238 _private member_ `bool bShouldRestoreSavedConstructionViewMode = false;` — Whether we should restore the previous view mode when a tool ends
- L241 _private member_ `FName SavedConstructionViewMode;` — The Construction view mode that was active before starting the current tool. When the tool ends, restore this view mode if bShouldRestoreSavedConstructionViewMode is true.
- L243 _private member_ `bool bConstructionViewWireframe = false;`
- L244 _private member_ `bool bShouldRestoreConstructionViewWireframe = false;`
- L247 _private member_ `TObjectPtr<UEditorInteractiveToolsContext> ActiveToolsContext = nullptr;` — `UPROPERTY()`
- L249 _private member_ `TWeakPtr<FDataflowConstructionViewportClient, ESPMode::ThreadSafe> ConstructionViewportClient;`
- L250 _private member_ `TWeakPtr<FDataflowSimulationViewportClient, ESPMode::ThreadSafe> SimulationViewportClient;`
- L252 _private prototype_ `void OnConstructionSceneUpdated();`
- L255 _private member_ `TSet<FName> FirstTimeRefocusedViews;` — The first time we get a valid mesh, refocus the camera on it
- L258 _private member_ `bool bShouldFocusConstructionView = true;` — Whether the rest space viewport should focus on the rest space mesh on the next tick
- L259 _private member_ `bool bShouldFocusSimulationView = true;`
- L261 _private prototype_ `void ViewportResized(FViewport* Viewport, uint32 Unused);`
- L264 _private member_ `FName NodeTypeForPendingToolStart;` — Dataflow node type whose corresponding tool should be started on the next Tick
- L267 _private member_ `bool bShouldRestartToolNextTick = false;` — If we should start the tool for the selected node on the next ModeTick call. Used when switching ViewModes to allow the scene to be rebuilt before restarting the tool.
- L271 _private member_ `bool bHadSingleSelectionBeforeToolShutdown = false;` — Whether we have a single mesh selected in the Construction Scene prior to shutting down a running tool. The Scene will likely be rebuilt when the tool ends, resulting in losing selection information, so we save this before shutting the tool down.
- L274 _private member_ `bool bPendingNodeSelectionChanged = false;` — Whether we are waiting for a node selection change to finish before starting a tool
- L276 _private member_ `UDataflowEditor* DataflowEditor = nullptr;`
- L279 _private member_ `FDateTime LastModeStartTimestamp;` — Timestamp for telemetry
- L282 _private member_ `FText UserMessage;` — Message to display to the user in the viewport
- L286 _private member_ `TMap<TArray<FName>, FName> NodeViewModeHistory;` — Each node has a set of view modes it can use. For each distinct set of available view modes, we store the last mode that the user has chosen. This will enable switching between different kinds of nodes and not have the view mode reset to a default every time.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Dataflow` (scope `UE`)
- L30 _typedef_ `using FToolBuilderModeMap = TMap<TWeakObjectPtr<const UInteractiveToolManager>, TWeakObjectPtr<UDataflowEditorMode>>;` (scope `UE::Dataflow`) — Process-wide singleton tool builders (held by FDataflowToolRegistry) can be shared across multiple simultaneously-open Dataflow editors. Storing a single Mode pointer on such a builder would alias to whichever editor opened last, causing silent wrong-editor focus and dangling-pointer crashes when one editor closes while another's tool is still active. These helpers maintain a per-tool-manager binding so each editor's tool sees its own mode.
- L33 _prototype_ `void RegisterModeForToolManager(FToolBuilderModeMap& InOutMap, UDataflowEditorMode* InMode);` (scope `UE::Dataflow`) — Insert InMode keyed by its tool manager, pruning any entries whose mode or tool manager have been GC'd.
- L36 _prototype_ `UDataflowEditorMode* FindModeForToolManager(const FToolBuilderModeMap& InMap, const UInteractiveToolManager* ToolManager);` (scope `UE::Dataflow`) — Look up the mode bound to ToolManager, or nullptr if absent / stale.

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorModeToolkit.h` (Private)


#### struct `FDataflowEditorModeToolPalette`  
`struct FDataflowEditorModeToolPalette`  
_L16-29_
- desc: Tool pallete data for the dataflow mode toolkit
- L19 _public member_ `TSharedPtr<STextBlock> ModeWarningArea;` — Mode area to display the warning messages
- L22 _public member_ `TSharedPtr<STextBlock> ModeHeaderArea;` — Mode header for the tools names
- L25 _public member_ `TSharedPtr<STextBlock> ToolWarningArea;` — Too warning area
- L28 _public member_ `FDelegateHandle ActivePaletteChangedHandle;` — Handle when the active palette is changed

#### class `FDataflowEditorModeToolkit`  
`class FDataflowEditorModeToolkit : public FBaseCharacterFXEditorModeToolkit`  
_L38-103_
- inherits: `FBaseCharacterFXEditorModeToolkit`
- L41 _public prototype_ `void Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode);`
- L44 _public prototype_ `virtual const FSlateBrush* GetActiveToolIcon(const FString& Identifier) const override;`
- L48 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L49 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L50 _public prototype_ `virtual void CustomizeModeDetailsViewArgs(FDetailsViewArgs& ArgsInOut) override;`
- L54 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L55 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L58 _public prototype_ `void SetConstructionViewportWidget(TWeakPtr<SDataflowConstructionViewport>);`
- L59 _public prototype_ `void SetSimulationViewportWidget(TWeakPtr<SDataflowSimulationViewport>);`
- L61 _public prototype_ `void OnRenderSettingsUpdated(const TArray<UDataflowRenderableTypeSettings*>& RenderSettings);`
- L66 _private prototype_ `void RegisterPalettes();` — Register the toolkit builder palettes
- L69 _private prototype_ `void MakeToolAcceptCancelWidget();` — Make the accept/cancel overlay widget
- L72 _private prototype_ `void UpdateActiveToolProperties(UInteractiveTool* Tool);` — Update the active tool properties
- L74 _private prototype_ `void UpdateModeDetailsView();`
- L77 _private prototype_ `void InvalidateCachedDetailPanelState(UObject* ChangedObject);` — Invalidate the cache state
- L80 _private prototype_ `void BindCommands();` — Bind all the tools commands
- L84 _private prototype_ `SBaseCharacterFXEditorViewport* GetViewportWidgetForManager(UInteractiveToolManager* Manager);` — Get the viewport widget associated with the given manager TODO: This should not be necessary any more as we do not run tools in the Simulation Viewport (JIRA UE-201248)
- L87 _private prototype_ `UEditorInteractiveToolsContext* GetCurrentToolsContext();` — Current tool context used to create nodes
- L89 _private prototype_ `void OnSettingsPropertiesChanged(const FPropertyChangedEvent& PropertyChangedEvent);`
- L91 _private prototype_ `void RefreshConstructionScene();`
- L94 _private member_ `TWeakPtr<SDataflowConstructionViewport> ConstructionViewportWidget;` — Construction viewport
- L97 _private member_ `TWeakPtr<SDataflowSimulationViewport> SimulationViewportWidget;` — Simulation viewport
- L100 _private member_ `FDataflowEditorModeToolPalette ModeToolPallete;` — Dataflow toolkit mode tool palette data
- L102 _private member_ `TArray<UDataflowRenderableTypeSettings*> RenderSettings;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorOptions.h` (Private)


#### enum `EDataflowConstructionViewportMousePanButton`  
`enum class EDataflowConstructionViewportMousePanButton : uint8`  
_L11-21_
- reflection: `UENUM(BlueprintType)`
- L14 _public enumerator_ `Right = 0` — Right Mouse Button
- L17 _public enumerator_ `Middle = 1` — Middle Mouse Button
- L20 _public enumerator_ `RightOrMiddle = 2` — Either Right or Middle Mouse Button

#### enum `EDataflowEditorEvaluationMode`  
`enum class EDataflowEditorEvaluationMode : uint8`  
_L24-31_
- reflection: `UENUM(BlueprintType)`
- L27 _public enumerator_ `Automatic = 0` — Dataflow graph will evaluate automatically when values are changed
- L30 _public enumerator_ `Manual = 1` — Dataflow graph will not eveluate until the user presses the evaluate button in the editor

#### class `UDataflowEditorOptions`  
`class UDataflowEditorOptions : public UDeveloperSettings`  
_L35-84_
- reflection: `UCLASS(HideCategories = Object, Config = EditorPerProjectUserSettings, Meta = (DisplayName = "Dataflow Editor"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: A settings class used to store and retreive user settings related to the Dataflow Editor
- L41 _private member_ `float ConstructionViewFOV;` — `UPROPERTY(config)` — FOV for the Construction viewport camera
- L45 _private member_ `float SimulationViewFOV;` — `UPROPERTY(config)` — FOV for the Simulation viewport camera
- L49 _private member_ `bool bConstructionViewFixedExposure;` — `UPROPERTY(config)` — Whether the Construction viewport has Auto or Fixed exposure
- L53 _private member_ `bool bSimulationViewFixedExposure;` — `UPROPERTY(config)` — Whether the Simulation viewport has Auto or Fixed exposure
- L57 _private member_ `FString ConstructionProfileName;` — `UPROPERTY(config)` — Preview Scene Profile for the Construction viewport
- L61 _private member_ `FString SimulationProfileName;` — `UPROPERTY(config)` — Preview Scene Profile for the Simulation viewport
- L65 _private member_ `FEditorViewportCameraSpeedSettings ConstructionCameraSpeedSettings;` — `UPROPERTY(config)` — The default camera speed settings for the viewport
- L68 _private member_ `FEditorViewportCameraSpeedSettings SimulationCameraSpeedSettings;` — `UPROPERTY(config)`
- L72 _private member_ `EDataflowConstructionViewportMousePanButton ConstructionViewportMousePanButton;` — `UPROPERTY(Config, EditAnywhere, Category = UI)` — Which mouse button controls camera panning in the Construction Viewport in 2D view mode
- L75 _private member_ `EDataflowEditorEvaluationMode EditorEvaluationMode = EDataflowEditorEvaluationMode::Automatic;` — `UPROPERTY(Config, EditAnywhere, Category = UI)`
- L78 _private prototype_ `virtual FName GetCategoryName() const override;` — UDeveloperSettings overrides
- L81 _private prototype_ `virtual FText GetSectionText() const override;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorStyle.h` (Private)


#### class `FDataflowEditorStyle`  
`class FDataflowEditorStyle final : public FSlateStyleSet`  
_L13-83_
- inherits: `FSlateStyleSet`
- L16 _public function_ `FDataflowEditorStyle() : FSlateStyleSet("DataflowEditorStyle")`
- L63 _public function_ `~FDataflowEditorStyle()`
- L70 _public member_ `UMaterial* DefaultMaterial = nullptr;` — Default Rendering Material for Mesh surfaces
- L71 _public member_ `UMaterial* VertexMaterial = nullptr;`
- L72 _public member_ `UMaterial* DefaultTwoSidedMaterial = nullptr;`
- L77 _public function_ `static FDataflowEditorStyle& Get()`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorSubGraphTabSummoner.h` (Private)


#### struct `FDataflowEditorSubGraphTabSummoner`  
`struct FDataflowEditorSubGraphTabSummoner : public FDocumentTabFactoryForObjects<UDataflowSubGraph>`  
_L14-48_
- inherits: `FDocumentTabFactoryForObjects<UDataflowSubGraph>`
- desc: Summoner class for Dataflow SubGraph tabs
- L17 _public prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UDataflowSubGraph*);`
- L20 _public prototype_ `FDataflowEditorSubGraphTabSummoner(TSharedPtr<FDataflowEditorToolkit> InEditorToolkitPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback);`
- L22 _public prototype_ `virtual void OnTabActivated(TSharedPtr<SDockTab> Tab) const override;`
- L24 _public prototype_ `virtual void OnTabForegrounded(TSharedPtr<SDockTab> Tab) const override;`
- L26 _public prototype_ `virtual void OnTabBackgrounded(TSharedPtr<SDockTab> Tab) const override;`
- L28 _public prototype_ `virtual void OnTabRefreshed(TSharedPtr<SDockTab> Tab) const override;`
- L30 _public prototype_ `virtual void SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const override;`
- L33 _protected prototype_ `static FText GetGraphDisplayName(const UEdGraph* Graph);`
- L35 _protected prototype_ `virtual TAttribute<FText> ConstructTabNameForObject(UDataflowSubGraph* DocumentID) const override;`
- L37 _protected prototype_ `virtual TSharedRef<SWidget> CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UDataflowSubGraph* DocumentID) const override;`
- L39 _protected prototype_ `virtual const FSlateBrush* GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UDataflowSubGraph* DocumentID) const override;`
- L41 _protected prototype_ `virtual TSharedRef<FGenericTabHistory> CreateTabHistoryNode(TSharedPtr<FTabPayload> Payload) override;`
- L43 _protected prototype_ `TSharedPtr<SDataflowGraphEditor> GetDataflowEditorFromTab(TSharedPtr<SDockTab> Tab) const;`
- L46 _protected member_ `TWeakPtr<FDataflowEditorToolkit> EditorToolkitWeakPtr;`
- L47 _protected member_ `FOnCreateGraphEditorWidget OnCreateGraphEditorWidget;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(TSharedRef<SGraphEditor>, FOnCreateGraphEditorWidget, TSharedRef<FTabInfo>, UDataflowSubGraph*);`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEditorUtil.h` (Private)


#### struct `UE::Dataflow::FScopedProgressNotification`  
`struct FScopedProgressNotification`  
_L67-84_
- L70 _public prototype_ `FScopedProgressNotification(const FText& Title, int32 InMaxProgress = 1.0f, float DelayInSeconds = 0.1f);`
- L71 _public prototype_ `~FScopedProgressNotification();`
- L73 _public prototype_ `void SetUpdateSteps(float InUpdateSteps);`
- L75 _public prototype_ `void SetProgress(float InProgress, const FText& Message = FText::GetEmpty());`
- L76 _public prototype_ `void AddProgress(float InDeltaProgress, const FText& Message = FText::GetEmpty());`
- L79 _private member_ `TUniquePtr<FSlowTask> SlowTask;`
- L80 _private member_ `float CurrentProgress = 0.0f;`
- L81 _private member_ `float LastUpdateProgress = 0.0f;`
- L82 _private member_ `float UpdateSteps = 0.0f;`
- L83 _private member_ `float MaxProgress = 1.0f;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Dataflow` (scope `UE`)
- L23 _namespace_ `namespace GeometryCollection`
- L23 _namespace_ `namespace Facades` (scope `GeometryCollection`)
- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Dataflow` (scope `UE`)
- L28 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L30 _prototype_ `bool HasSkeletalMesh(UObject* InObject);` (scope `UE::Dataflow::Private`)
- L32 _prototype_ `bool HasDataflowAsset(UObject* InObject);` (scope `UE::Dataflow::Private`)
- L34 _prototype_ `UDataflow* GetDataflowAssetFrom(UObject* InObject);` (scope `UE::Dataflow::Private`)
- L36 _prototype_ `USkeletalMesh* GetSkeletalMeshFrom(UObject* InObject);` (scope `UE::Dataflow::Private`)
- L38 _prototype_ `USkeleton* GetSkeletonFrom(UObject* InObject);` (scope `UE::Dataflow::Private`)
- L40 _prototype_ `UAnimationAsset* GetAnimationAssetFrom(UObject* InObject);` (scope `UE::Dataflow::Private`)
- L42 _prototype_ `FString GetDataflowTerminalFrom(UObject* InObject);` (scope `UE::Dataflow::Private`)
- L45 _namespace_ `namespace UE`
- L47 _namespace_ `namespace Material` (scope `UE`)
- L49 _prototype_ `UMaterial* LoadMaterialFromPath( const FName& Path, UObject* Outer);` (scope `UE::Material`)
- L53 _namespace_ `namespace UE`
- L53 _namespace_ `namespace Dataflow` (scope `UE`)
- L55 _prototype_ `TSharedPtr<UE::Dataflow::FEngineContext> GetContext(TObjectPtr<UDataflowBaseContent> Content);` (scope `UE::Dataflow`)
- L57 _prototype_ `bool IsViewModeSupported(const UDataflowEdNode& EdNode, const UDataflowBaseContent& EditorContent, const IDataflowConstructionViewMode& ViewMode, bool bCheckDebugDraw = true);` (scope `UE::Dataflow`)
- L59 _prototype_ `bool CanRenderNodeOutput(const UDataflowEdNode& EdNode, const UDataflowBaseContent& EditorContent, const UE::Dataflow::IDataflowConstructionViewMode& ViewMode, bool bCheckDebugDraw = true);` (scope `UE::Dataflow`)
- L63 _prototype_ `bool RenderNodeOutput(GeometryCollection::Facades::FRenderingFacade& RenderingFacade, const UDataflowEdNode& Node, const UDataflowBaseContent& EditorContent, const bool bEvaluateOutputs);` (scope `UE::Dataflow`) — This function fills the managed array collection linked to the rendering facade from the callbacks. Returns true if the resulting collection should be directly rendered of false if the collection will be used to generate a primitive component
- L64 _prototype_ `void GetViewModesForNode(const UDataflowEdNode& EdNode, const UDataflowBaseContent& EditorContent, TArray<FName>& OutValidViewModeNames);` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowEngineRendering.h` (Private)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Dataflow` (scope `UE`)
- L13 _prototype_ `void RenderingCallbacks();` (scope `UE::Dataflow`) — Rendering callbacks for the Dataflow Rendering Factory

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowFreezeActionsCustomization.h` (Private)


#### class `UE::Dataflow::FFreezeActionsCustomization`  
`class FFreezeActionsCustomization final : public IPropertyTypeCustomization`  
_L12-22_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for the Dataflow node UI.
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& customizationutils) override;`
- L20 _private function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> , IDetailChildrenBuilder& , IPropertyTypeCustomizationUtils& ) override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowFunctionPropertyCustomization.h` (Private)


#### class `UE::Dataflow::FFunctionPropertyCustomization`  
`class FFunctionPropertyCustomization : public IPropertyTypeCustomization`  
_L14-26_
- inherits: `IPropertyTypeCustomization`
- desc: Customization for buttons in the UStruct UI of dataflow nodes.
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L20 _protected prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L21 _protected function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> , IDetailChildrenBuilder& , IPropertyTypeCustomizationUtils& ) override`
- L24 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L25 _private member_ `TWeakPtr<const SDataflowGraphEditor> DataflowGraphEditor;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowMembersWidget.h` (Private)


#### class `SDataflowMembersWidget`  
`class SDataflowMembersWidget: public SCompoundWidget`  
_L35-168_
- inherits: `SCompoundWidget`
- desc: Widget to interact with Variables, subgraphs in Dataflow editors
- L38 _public function_ `SLATE_BEGIN_ARGS(SDataflowMembersWidget)`
- L39 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FDataflowEditorToolkit> InEditorToolkit);`
- L42 _public prototype_ `~SDataflowMembersWidget();`
- L79 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);` — SWidget interface
- L81 _private prototype_ `void OnObjectPropertyChanged(UObject* InObject, FPropertyChangedEvent& InPropertyChangedEvent);`
- L82 _private prototype_ `void OnVariablesOverrideStateChanged(const UDataflow* DataflowAsset, FName VariableName, bool bNewOverrideState);`
- L83 _private prototype_ `void OnSubGraphsChanged(const UDataflow* InDataflowAsset, const FGuid& InSubGraphGuid, UE::Dataflow::ESubGraphChangedReason InReason);`
- L85 _private prototype_ `void InvalidateVariableNode(const UDataflow& InDataflowAsset, FName VariableName);`
- L87 _private prototype_ `void OnFilterTextChanged(const FText& InFilterText);`
- L88 _private prototype_ `FText GetFilterText() const;`
- L89 _private prototype_ `TSharedRef<SWidget> OnCreateWidgetForAction(FCreateWidgetForActionData* const InCreateData);`
- L90 _private prototype_ `void CollectAllActions(FGraphActionListBuilderBase& OutAllActions);`
- L91 _private prototype_ `void CollectStaticSections(TArray<int32>& StaticSectionIDs);`
- L92 _private prototype_ `FReply OnActionDragged(const TArray<TSharedPtr<FEdGraphSchemaAction>>& InActions, const FPointerEvent& MouseEvent);`
- L93 _private prototype_ `void OnActionDoubleClicked(const TArray< TSharedPtr<FEdGraphSchemaAction> >& InActions);`
- L94 _private prototype_ `TSharedPtr<SWidget> OnContextMenuOpening();`
- L95 _private prototype_ `bool CanRequestRenameOnActionNode(TWeakPtr<FGraphActionNode> InSelectedNode) const;`
- L96 _private prototype_ `FText OnGetSectionTitle(int32 InSectionID);`
- L97 _private prototype_ `TSharedRef<SWidget> OnGetSectionWidget(TSharedRef<SWidget> RowWidget, int32 InSectionID);`
- L98 _private prototype_ `bool HandleActionMatchesName(FEdGraphSchemaAction* InAction, const FName& InName) const;`
- L100 _private prototype_ `TSharedRef<SWidget> CreateAddToSectionButton(int32 InSectionID, TWeakPtr<SWidget> WeakRowWidget);`
- L101 _private prototype_ `FReply OnAddButtonClickedOnSection(int32 InSectionID);`
- L102 _private prototype_ `bool CanAddNewElementToSection(int32 InSectionID) const;`
- L104 _private prototype_ `void SelectItemByName(const FName& ItemName, ESelectInfo::Type SelectInfo = ESelectInfo::Direct, int32 SectionId = INDEX_NONE, bool bIsCategory = false);`
- L105 _private prototype_ `bool IsAnyActionSelected() const;`
- L106 _private prototype_ `bool IsOnlySubgraphActionsSelected() const;`
- L107 _private prototype_ `TSharedPtr<FEdGraphSchemaAction> GetFirstSelectedAction() const;`
- L109 _private prototype_ `const TSharedPtr<ISection> GetSectionById(int32 SectionId) const;`
- L111 _private prototype_ `void CacheAssets();`
- L112 _private prototype_ `UDataflow* GetDataflowAsset() const;`
- L113 _private prototype_ `IDataflowInstanceInterface* GetDataflowInstanceInterface() const;`
- L116 _private prototype_ `void OnRequestRename();` — command functions
- L117 _private prototype_ `bool CanRequestRename() const;`
- L118 _private prototype_ `void OnCopy();`
- L119 _private prototype_ `bool CanCopy() const;`
- L120 _private prototype_ `void OnCut();`
- L121 _private prototype_ `bool CanCut() const;`
- L122 _private prototype_ `void OnPaste();`
- L123 _private prototype_ `bool CanPaste() const;`
- L124 _private prototype_ `void OnDuplicate();`
- L125 _private prototype_ `bool CanDuplicate() const;`
- L126 _private prototype_ `void OnDelete();`
- L127 _private prototype_ `bool CanDelete() const;`
- L128 _private prototype_ `bool IsSelectionForEachSubGraph() const;`
- L129 _private prototype_ `void SetForEachSubGraphOnSelection(bool bValue);`
- L131 _private prototype_ `bool IsDataflowAssetEditable() const;`
- L134 _private prototype_ `void Refresh();` — UI refresh
- L136 _private prototype_ `void InitializeCommands();`
- L137 _private prototype_ `void InitializeSections();`
- L138 _private prototype_ `void CreateVariableOverrideDetailView();`
- L139 _private prototype_ `void RefreshVariableOverrideDetailView();`
- L140 _private prototype_ `void OverridesDetailsViewFinishedChangingProperties(const FPropertyChangedEvent& InPropertyChangedEvent);`
- L142 _private prototype_ `const TSharedPtr<SDataflowGraphEditor> GetGraphEditor() const;`
- L145 _private member_ `TWeakPtr<FDataflowEditorToolkit> EditorToolkitWeakPtr;`
- L151 _private member_ `TWeakObjectPtr<UObject> EditedAssetWeakPtr;` — asset being edited by the graph - maybe a geometry collection with a dataflow asset bound to it Can be null if the dataflow asset graph is edited directly outside of the context of a specific asset
- L154 _private member_ `TWeakObjectPtr<UDataflow> DataflowAssetWeakPtr;` — Dataflow asset
- L157 _private member_ `TSharedPtr<FUICommandList> CommandList;` — List of UI Commands for this scope
- L160 _private member_ `TSharedPtr<SSearchBox> FilterBox;` — The filter box that handles filtering for graph action menu.
- L163 _private member_ `TSharedPtr<SGraphActionMenu> GraphActionMenu;` — Graph Action Menu for displaying all our variables and sub-graphs
- L165 _private member_ `TMap<int32, TSharedPtr<ISection>> SectionMap;`
- L167 _private member_ `TSharedPtr<IStructureDetailsView> OverridesDetailsView;`

#### struct `SDataflowMembersWidget::FButton`  
`struct FButton`  
_L45-50_
- L47 _public member_ `FText Tooltip;`
- L48 _public member_ `FName MetadataTag;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> Command;`

#### struct `SDataflowMembersWidget::ISection`  
`struct ISection`  
_L52-75_
- L54 _public prototype_ `virtual ~ISection() = default;`
- L56 _public prototype_ `virtual const FText& GetTitle() const = 0;`
- L57 _public prototype_ `virtual const FButton* GetAddButton() const = 0;`
- L59 _public prototype_ `virtual bool CanRequestRename() const = 0;`
- L61 _public prototype_ `virtual bool CanCopy() const = 0;`
- L62 _public prototype_ `virtual bool CanPaste() const = 0;`
- L63 _public prototype_ `virtual bool CanDuplicate() const = 0;`
- L64 _public prototype_ `virtual bool CanDelete() const = 0;`
- L66 _public prototype_ `virtual void OnCopy(FEdGraphSchemaAction&) const = 0;`
- L67 _public prototype_ `virtual void OnPaste(FEdGraphSchemaAction&) const = 0;`
- L68 _public prototype_ `virtual void OnDuplicate(FEdGraphSchemaAction&) const = 0;`
- L69 _public prototype_ `virtual void OnDelete(FEdGraphSchemaAction&) const = 0;`
- L71 _public prototype_ `virtual void OnDoubleClicked(FEdGraphSchemaAction&, FDataflowEditorToolkit&) const = 0;`
- L73 _public prototype_ `virtual void CollectActions(UDataflow* DataflowAsset, TArray<TSharedPtr<FEdGraphSchemaAction>>& OutActions) const = 0;`
- L74 _public prototype_ `virtual TSharedRef<SWidget> CreateWidgetForAction(FCreateWidgetForActionData* const InCreateData, TSharedPtr<SDataflowGraphEditor> Editor) const = 0;`

#### Free symbols / members of external scopes

- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowOutlinerFactory.h` (Private)


#### class `UDataflowObjectFactory`  
`class UDataflowObjectFactory : public UEditorDataStorageFactory`  
_L10-31_
- reflection: `UCLASS()`
- inherits: `UEditorDataStorageFactory`
- desc: Dataflow outliner factory used to register TEDs queries
- L15 _public prototype_ `virtual ~UDataflowObjectFactory() override = default;`
- L18 _public prototype_ `virtual void RegisterTables(UE::Editor::DataStorage::ICoreProvider& DataStorage, UE::Editor::DataStorage::ICompatibilityProvider&) override;`
- L19 _public prototype_ `virtual void RegisterQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage) override;`
- L24 _protected prototype_ `void RegisterVisibilityQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);` — Register all the visibility queries
- L27 _protected prototype_ `void RegisterLabelQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);` — Register all the label queries
- L30 _protected prototype_ `void RegisterHierarchyQueries(UE::Editor::DataStorage::ICoreProvider& DataStorage);` — Register all the hierarchy queries

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowOutlinerMode.h` (Private)


#### class `FDataflowOutlinerMode`  
`class FDataflowOutlinerMode : public UE::Editor::Outliner::FTedsOutlinerMode`  
_L13-39_
- inherits: `UE::Editor::Outliner::FTedsOutlinerMode`
- desc: Dataflow outliner mode used to represent the dataflow scenes (construction/simulation) It has a more limited view compared to the normal outliner, hiding features we don't support,
- L17 _public prototype_ `FDataflowOutlinerMode(const UE::Editor::Outliner::FTedsOutlinerParams& InModeParams, TWeakPtr<FDataflowConstructionScene> InConstructionScene, TWeakPtr<FDataflowSimulationScene> InSimulationScene);`
- L23 _public prototype_ `virtual void OnItemSelectionChanged(FSceneOutlinerTreeItemPtr Item, ESelectInfo::Type SelectionType, const FSceneOutlinerItemSelection& Selection) override;`
- L24 _public prototype_ `virtual void OnItemDoubleClick(FSceneOutlinerTreeItemPtr Item) override;`
- L25 _public prototype_ `virtual void OnItemAdded(FSceneOutlinerTreeItemPtr Item) override;`
- L26 _public function_ `virtual bool CanInteract(const ISceneOutlinerTreeItem& Item) const override`
- L27 _public function_ `virtual bool CanPopulate() const override`
- L28 _public function_ `virtual bool CanSupportDragAndDrop() const override`
- L29 _public function_ `virtual ESelectionMode::Type GetSelectionMode() const override`
- L30 _public prototype_ `virtual FReply OnKeyDown(const FKeyEvent& InKeyEvent) override;`
- L35 _private member_ `TWeakPtr<FDataflowConstructionScene> ConstructionScene;` — Construction dataflow scene
- L38 _private member_ `TWeakPtr<FDataflowSimulationScene> SimulationScene;` — Simulation dataflow scene

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowOutlinerView.h` (Private)


#### class `FDataflowOutlinerView`  
`class FDataflowOutlinerView : public FDataflowNodeView`  
_L13-49_
- inherits: `FDataflowNodeView`
- desc: Class to handle the dataflow outliner widget
- L16 _public prototype_ `FDataflowOutlinerView(TWeakPtr<FDataflowConstructionScene> InConstructionScene, TWeakPtr<FDataflowSimulationScene> InSimulationScene, TObjectPtr<UDataflowBaseContent> InContent = nullptr);`
- L17 _public prototype_ `~FDataflowOutlinerView();`
- L20 _public prototype_ `TSharedPtr<ISceneOutliner> CreateWidget();` — Create the outliner widget
- L23 _public prototype_ `virtual void SetSupportedOutputTypes() override;` — Set the supported output types
- L26 _public prototype_ `virtual void UpdateViewData() override;` — Update the view if necessary
- L29 _public prototype_ `virtual void RefreshView() override;` — Refresh the view if necessary
- L32 _public prototype_ `virtual void ConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override;` — Update the view based on changes in the construction view
- L35 _public prototype_ `virtual void SimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override;` — Update the view based on changes in the construction view
- L38 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Add GC managed objects
- L42 _private member_ `TSharedPtr<SSceneOutliner> OutlinerWidget;` — Outliner widget stored on the view
- L45 _private member_ `TWeakPtr<FDataflowConstructionScene> ConstructionScene;` — Construction scene the outliner could refer to
- L48 _private member_ `TWeakPtr<FDataflowSimulationScene> SimulationScene;` — Simulation scene the outliner could refer to

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowOutputLog.h` (Private)


#### class `FDataflowOutputLog`  
`class FDataflowOutputLog final : public FDataflowNodeView`  
_L20-54_
- inherits: `FDataflowNodeView`
- desc: Class to handle the OutputLog widget
- L23 _public prototype_ `explicit FDataflowOutputLog(TObjectPtr<UDataflowBaseContent> InContent = nullptr);`
- L24 _public prototype_ `virtual ~FDataflowOutputLog();`
- L26 _public function_ `TSharedPtr<SWidget> GetOutputLogWidget()`
- L28 _public prototype_ `TSharedRef<IMessageLogListing> GetMessageLog() const;`
- L29 _public prototype_ `void ClearMessageLog();`
- L32 _public prototype_ `void AddMessage(const EMessageSeverity::Type InSeverity, const FString& InMessage, const FDataflowPath& InPath);` — `UE_DEPRECATED(5.8, "AddMessage with a FString parameter is now deprecated, use the FText version")`
- L34 _public prototype_ `void AddMessage(const EMessageSeverity::Type InSeverity, const FText& InMessage, const FDataflowPath& InPath);`
- L36 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputLogMessageTokenClicked, const FString);`
- L37 _public function_ `FOnOutputLogMessageTokenClicked& GetOnOutputLogMessageTokenClickedDelegate()`
- L40 _private function_ `virtual void SetSupportedOutputTypes() override`
- L41 _private function_ `virtual void UpdateViewData() override`
- L42 _private function_ `virtual void ConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override`
- L43 _private function_ `virtual void SimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override`
- L45 _private prototype_ `void OnMessageTokenClicked(const TSharedRef<IMessageToken>& InMessageToken);`
- L47 _private prototype_ `void CreateMessageLog();`
- L48 _private prototype_ `void CreateMessageLogWidget();`
- L50 _private member_ `TSharedPtr<SWidget> OutputLogWidget;`
- L51 _private member_ `TSharedPtr<IMessageLogListing> MessageLogListing;`
- L53 _private member_ `FOnOutputLogMessageTokenClicked OnOutputLogMessageTokenClickedDelegate;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Dataflow` (scope `UE`)
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnOutputLogMessageTokenClicked, const FString);`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowPreviewProfileController.h` (Private)


#### class `FDataflowPreviewProfileController`  
`class FDataflowPreviewProfileController : public IPreviewProfileController`  
_L14-71_
- inherits: `IPreviewProfileController`
- desc: Preview Profile Controller that interfaces with a user-supplied index storage object
- L28 _public prototype_ `FDataflowPreviewProfileController(TSharedPtr<IProfileIndexStorage> ProfileIndexStorage);`
- L29 _public prototype_ `virtual ~FDataflowPreviewProfileController();`
- L32 _public prototype_ `virtual TArray<FString> GetPreviewProfiles(int32& OutCurrentProfileIndex) const override;` — Returns the list of available preview profiles names.
- L35 _public prototype_ `virtual bool SetActiveProfile(const FString& ProfileName) override;` — Set the specified preview profiles as the active one.
- L38 _public prototype_ `virtual FString GetActiveProfile() const override;` — Returns the preview profiles currently active.
- L41 _public prototype_ `virtual bool HasAnyUserProfiles() const override;` — Returns true if user has added one or more of their own profiles
- L44 _public function_ `virtual FOnPreviewProfileListChanged& OnPreviewProfileListChanged() override` — Invoked after the list of available profiles has changed.
- L47 _public function_ `virtual FOnPreviewProfileChanged& OnPreviewProfileChanged() override` — Invoked after the active preview profile changed.
- L50 _private prototype_ `void UpdateAssetViewerProfiles();`
- L51 _private prototype_ `void EnsureProfilesStateCoherence() const;`
- L55 _private member_ `TSharedPtr<IProfileIndexStorage> ProfileIndexStorage;`
- L58 _private member_ `UAssetViewerSettings* AssetViewerSettings = nullptr;` — Provides the list of available preview profiles along with the profile change delegates (to update the profile combo box selection)
- L61 _private member_ `TArray<FString> AssetViewerProfileNames;` — The list of available profiles.
- L64 _private member_ `int32 CurrentProfileIndex = 0;` — Holds the current profile index in the list. This is kept consistent with the cache list of names.
- L66 _private member_ `FOnPreviewProfileListChanged OnPreviewProfileListChangedDelegate;`
- L67 _private member_ `FOnPreviewProfileChanged OnPreviewSettingChangedDelegate;`
- L69 _private member_ `FDelegateHandle AssetViewerSettingsProfileAddRemoveHandle;`
- L70 _private member_ `FDelegateHandle AssetViewerSettingsChangedHandle;`

#### class `FDataflowPreviewProfileController::IProfileIndexStorage`  
`class IProfileIndexStorage`  
_L18-26_
- L21 _public prototype_ `virtual void StoreProfileIndex(int32) = 0;`
- L22 _public prototype_ `virtual int32 RetrieveProfileIndex() = 0;`
- L25 _protected prototype_ `virtual ~IProfileIndexStorage() = default;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSCommentNode.h` (Private)


#### class `SDataflowEdNodeComment`  
`class SDataflowEdNodeComment : public SGraphNodeComment`  
_L17-26_
- inherits: `SGraphNodeComment`
- L19 _private typedef_ `typedef SGraphNodeComment Super;`
- L22 _public function_ `SLATE_BEGIN_ARGS(SDataflowEdNodeComment)`
- L23 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphNode_Comment* InNode)`

#### struct `FAssetSchemaAction_Dataflow_CreateCommentNode_DataflowEdNode`  
`struct FAssetSchemaAction_Dataflow_CreateCommentNode_DataflowEdNode : public FEdGraphSchemaAction`  
_L32-50_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L37 _public function_ `FAssetSchemaAction_Dataflow_CreateCommentNode_DataflowEdNode(const TSharedPtr<SGraphEditor>& InGraphEditor) : FEdGraphSchemaAction() , GraphEditor(InGraphEditor)`
- L41 _public function_ `FAssetSchemaAction_Dataflow_CreateCommentNode_DataflowEdNode()`
- L43 _public prototype_ `static TSharedPtr<FAssetSchemaAction_Dataflow_CreateCommentNode_DataflowEdNode> CreateAction(UEdGraph* ParentGraph, const TSharedPtr<SGraphEditor>& GraphEditor);`
- L46 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L49 _public member_ `TSharedPtr<SGraphEditor> GraphEditor;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSPin.h` (Private)


#### class `SDataflowPin`  
`class SDataflowPin : public SGraphPin`  
_L13-54_
- inherits: `SGraphPin`
- desc: class used to for all dataflow node pins
- L16 _public function_ `SLATE_BEGIN_ARGS(SDataflowPin) : _IsPinInvalid(false) , _PinColorOverride(FLinearColor::White) , _bIsPinColorOverriden(false)`
- L21 _public prototype_ `SLATE_ATTRIBUTE(bool, IsPinInvalid) SLATE_ATTRIBUTE(FLinearColor, PinColorOverride) SLATE_ATTRIBUTE(bool, bIsPinColorOverriden) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UEdGraphPin* InPin);`
- L28 _public prototype_ `virtual FSlateColor GetPinColor() const override;`
- L29 _public prototype_ `virtual TSharedRef<SWidget> GetDefaultValueWidget() override;`
- L32 _private prototype_ `TSharedPtr<FDataflowNode> GetDataflowNode() const;`
- L34 _private prototype_ `ECheckBoxState GetBoolValue() const;`
- L35 _private prototype_ `void SetBoolValue(ECheckBoxState InIsChecked);`
- L36 _private prototype_ `TSharedRef<SWidget> MakeBoolWidget(const UEdGraphPin& Pin);`
- L38 _private prototype_ `TSharedRef<SWidget> MakeIntWidget(const UEdGraphPin& Pin);`
- L39 _private prototype_ `TOptional<int32> GetIntValue() const;`
- L40 _private prototype_ `void SetIntValue(int32 InValue, ETextCommit::Type CommitType);`
- L42 _private prototype_ `TSharedRef<SWidget> MakeFloatWidget(const UEdGraphPin& Pin);`
- L43 _private prototype_ `TOptional<float> GetFloatValue() const;`
- L44 _private prototype_ `void SetFloatValue(float InValue, ETextCommit::Type CommitType);`
- L46 _private prototype_ `TSharedRef<SWidget> MakeStringWidget(const UEdGraphPin& Pin);`
- L47 _private prototype_ `FText GetStringValue() const;`
- L48 _private prototype_ `void SetStringValue(const FText& NewTypeInValue, ETextCommit::Type );`
- L51 _private member_ `TAttribute<bool> bIsPinInvalid;`
- L52 _private member_ `TAttribute<FLinearColor> PinColorOverride;`
- L53 _private member_ `TAttribute<bool> bIsPinColorOverriden;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSceneProfileIndexStorage.h` (Private)


#### class `FDataflowConstructionSceneProfileIndexStorage`  
`class FDataflowConstructionSceneProfileIndexStorage : public FDataflowPreviewProfileController::IProfileIndexStorage`  
_L10-23_
- inherits: `FDataflowPreviewProfileController::IProfileIndexStorage`
- L14 _public prototype_ `explicit FDataflowConstructionSceneProfileIndexStorage(TWeakPtr<FDataflowConstructionScene> InConstructionScene);`
- L15 _public prototype_ `virtual ~FDataflowConstructionSceneProfileIndexStorage() override = default;`
- L17 _public prototype_ `virtual void StoreProfileIndex(int32 Index) override;`
- L18 _public prototype_ `virtual int32 RetrieveProfileIndex() override;`
- L22 _private member_ `TWeakPtr<FDataflowConstructionScene> ConstructionScene;`

#### class `FDataflowSimulationSceneProfileIndexStorage`  
`class FDataflowSimulationSceneProfileIndexStorage : public FDataflowPreviewProfileController::IProfileIndexStorage`  
_L25-38_
- inherits: `FDataflowPreviewProfileController::IProfileIndexStorage`
- L29 _public prototype_ `explicit FDataflowSimulationSceneProfileIndexStorage(TWeakPtr<FDataflowSimulationScene> InSimulationScene);`
- L30 _public prototype_ `virtual ~FDataflowSimulationSceneProfileIndexStorage() override = default;`
- L32 _public prototype_ `virtual void StoreProfileIndex(int32 Index) override;`
- L33 _public prototype_ `virtual int32 RetrieveProfileIndex() override;`
- L37 _private member_ `TWeakPtr<FDataflowSimulationScene> SimulationScene;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSelectionView.h` (Private)


#### class `FDataflowSelectionView`  
`class FDataflowSelectionView : public FDataflowNodeView`  
_L17-35_
- inherits: `FDataflowNodeView`
- desc: Class to handle the SelectionView widget
- L20 _public prototype_ `FDataflowSelectionView(TObjectPtr<UDataflowBaseContent> InContent = nullptr);`
- L21 _public prototype_ `~FDataflowSelectionView();`
- L23 _public prototype_ `virtual void SetSupportedOutputTypes() override;`
- L24 _public prototype_ `virtual void UpdateViewData() override;`
- L25 _public function_ `virtual void ConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override`
- L26 _public function_ `virtual void SimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override`
- L28 _public prototype_ `void SetSelectionView(TSharedPtr<SSelectionViewWidget>& InSelectionView);`
- L31 _private member_ `TSharedPtr<SSelectionViewWidget> SelectionView;`
- L33 _private member_ `FDelegateHandle OnPinnedDownChangedDelegateHandle;`
- L34 _private member_ `FDelegateHandle OnRefreshLockedChangedDelegateHandle;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSimulationControls.h` (Private)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Dataflow` (scope `UE`)
- L17 _prototype_ `bool ShouldResetWorld(const TObjectPtr<UDataflow>& SimulationGraph, const TObjectPtr<UWorld>& SimulationWorld, UE::Dataflow::FTimestamp& LastTimeStamp);` (scope `UE::Dataflow`) — Check if the simulation cache nodes have changed to trigger a reset
- L21 _prototype_ `TObjectPtr<AActor> SpawnSimulatedActor(const TSubclassOf<AActor>& ActorClass, const TObjectPtr<AChaosCacheManager>& CacheManager, const TObjectPtr<UChaosCacheCollection>& CacheCollection, const bool bIsRecording, const TObjectPtr<UDataflowBaseContent>& DataflowContent, const FTransform& ActorTransform, const FInstancedPropertyBag& BlueprintVariables);` (scope `UE::Dataflow`) — Spawn an actor given a class type and attach it to the cache manager
- L35 _prototype_ `bool SetupSkeletonAnimation(const TObjectPtr<AActor>& PreviewActor, const bool bSkeletalMeshVisibility = true);` (scope `UE::Dataflow`) — Setup the skelmesh animations to be used in the scene/generator return true if the animatiuon was properly set
- L38 _prototype_ `void UpdateSkeletonAnimation(const TObjectPtr<AActor>& PreviewActor, const float SimulationTime);` (scope `UE::Dataflow`) — Update the skelmesh animation at some point in time (GT)
- L41 _prototype_ `void ComputeSkeletonAnimation(const TObjectPtr<AActor>& PreviewActor, const float SimulationTime);` (scope `UE::Dataflow`) — Compute the skelmesh animation at some point in time (PT)
- L44 _prototype_ `void StartSkeletonAnimation(const TObjectPtr<AActor>& PreviewActor);` (scope `UE::Dataflow`) — Start the skelmesh animation
- L47 _prototype_ `void PauseSkeletonAnimation(const TObjectPtr<AActor>& PreviewActor);` (scope `UE::Dataflow`) — Pause the skelmesh animation
- L50 _prototype_ `void StepSkeletonAnimation(const TObjectPtr<AActor>& PreviewActor);` (scope `UE::Dataflow`) — Step the skelmesh animation

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSimulationPanel.h` (Private)


#### class `SDataflowSimulationPanel`  
`class SDataflowSimulationPanel : public SCompoundWidget`  
_L15-88_
- inherits: `SCompoundWidget`
- desc: Dataflow simulation panel to control an animation/simulation
- L28 _private function_ `SLATE_BEGIN_ARGS(SDataflowSimulationPanel)` — View min/max to run the simulation
- L29 _private prototype_ `SLATE_ATTRIBUTE( float, ViewInputMin ) SLATE_ATTRIBUTE( float, ViewInputMax ) SLATE_END_ARGS() void Construct( const FArguments& InArgs, TWeakPtr<FDataflowSimulationScene> InPreviewScene );`
- L37 _private prototype_ `TSharedRef<SWidget> OnCreatePreviewPlaybackModeWidget();` — Delegate when the playback mode is changed
- L40 _private prototype_ `FReply OnClick_Forward_Step();` — Delegate when the simulation controls are pressed
- L41 _private prototype_ `FReply OnClick_Forward_End();`
- L42 _private prototype_ `FReply OnClick_Backward_Step();`
- L43 _private prototype_ `FReply OnClick_Backward_End();`
- L44 _private prototype_ `FReply OnClick_Forward();`
- L45 _private prototype_ `FReply OnClick_Backward();`
- L46 _private prototype_ `FReply OnClick_PreviewPlaybackMode();`
- L47 _private prototype_ `FReply OnClick_Record();`
- L50 _private prototype_ `void OnTickPlayback(double InCurrentTime, float InDeltaTime);` — Main simulation delegates
- L51 _private prototype_ `void UpdateSimulationTimeFromScrubValue(float ScrubValue, const bool bRoundedFrame = true);`
- L52 _private prototype_ `void OnValueChanged(float NewValue);`
- L53 _private prototype_ `void SetFrameIndex(const FText& InNewText, ETextCommit::Type InCommitType);`
- L54 _private prototype_ `void OnBeginSliderMovement();`
- L57 _private prototype_ `EPlaybackMode::Type GetPlaybackMode() const;` — Get the playback mode used in the widget
- L60 _private prototype_ `float GetScrubValue() const;` — Get ethe current scrub value
- L63 _private prototype_ `uint32 GetNumberOfKeys() const;` — Get the number of keys
- L66 _private prototype_ `float GetSequenceLength() const;` — Get the sequence length
- L69 _private prototype_ `bool GetDisplayDrag() const;` — Get the display drag
- L72 _private member_ `TWeakPtr<FDataflowSimulationScene> SimulationScene;` — Simulation scene to be used for the widget
- L75 _private member_ `TSharedPtr<SScrubControlPanel> ScrubControlPanel;` — Scrub widget defined for the timeline
- L78 _private member_ `TSharedPtr<SButton> PreviewPlaybackModeButton;` — Playback mode button
- L81 _private member_ `TSharedPtr<SEditableTextBox> FrameIndexWidget;` — Widget showing editable frame index
- L84 _private member_ `EDataflowPlaybackMode PreviewPlaybackMode = EDataflowPlaybackMode::Looping;` — Preview playback mode (looping...)
- L87 _private member_ `EPlaybackMode::Type PlaybackMode = EPlaybackMode::Stopped;` — playback mode

#### enum `SDataflowSimulationPanel::EDataflowPlaybackMode`  
`enum class EDataflowPlaybackMode : int32`  
_L20-25_
- desc: Data flow playback mode
- L22 _public enumerator_ `Default`
- L23 _public enumerator_ `Looping`
- L24 _public enumerator_ `PingPong`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSimulationViewport.h` (Private)


#### class `SDataflowSimulationViewport`  
`class SDataflowSimulationViewport : public SBaseCharacterFXEditorViewport, public ICommonEditorViewportToolbarInfoProvider, public IPreviewLODController`  
_L17-60_
- inherits: `SBaseCharacterFXEditorViewport,ICommonEditorViewportToolbarInfoProvider,IPreviewLODController`
- L20 _public function_ `SLATE_BEGIN_ARGS(SDataflowSimulationViewport)`
- L21 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FEditorViewportClient>, ViewportClient) SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_END_ARGS() SDataflowSimulationViewport();`
- L27 _public prototype_ `void Construct(const FArguments& InArgs, const FAssetEditorViewportConstructionArgs& InViewportConstructionArgs);`
- L30 _public prototype_ `virtual void BindCommands() override;` — SEditorViewport
- L31 _public prototype_ `virtual bool IsVisible() const override;`
- L32 _public prototype_ `virtual TSharedPtr<SWidget> BuildViewportToolbar() override;`
- L33 _public prototype_ `virtual TSharedPtr<IPreviewProfileController> CreatePreviewProfileController() override;`
- L34 _public prototype_ `virtual void OnFocusViewportToSelection() override;`
- L37 _public prototype_ `virtual TSharedRef<class SEditorViewport> GetViewportWidget() override;` — ICommonEditorViewportToolbarInfoProvider
- L38 _public prototype_ `virtual TSharedPtr<FExtender> GetExtenders() const override;`
- L39 _public prototype_ `virtual void OnFloatingButtonClicked() override;`
- L42 _public prototype_ `virtual int32 GetCurrentLOD() const override;` — IPreviewLODController
- L43 _public prototype_ `virtual int32 GetLODCount() const override;`
- L44 _public prototype_ `virtual bool IsLODSelected(int32 LODIndex) const override;`
- L45 _public prototype_ `virtual void SetLODLevel(int32 LODIndex) override;`
- L48 _public prototype_ `const TSharedPtr<class FDataflowSimulationScene>& GetSimulationScene() const;` — Get the simulation scene
- L51 _public prototype_ `static void BuildVisualizationMenu(FToolMenuSection& MenuSection);` — Build visualisation menu
- L54 _private prototype_ `float GetViewMinInput() const;`
- L55 _private prototype_ `float GetViewMaxInput() const;`
- L57 _private prototype_ `FText GetDisplayString() const;`
- L59 _private prototype_ `UDataflowEditorMode* GetEdMode() const;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSkeletonView.h` (Private)


#### class `FDataflowSkeletonView`  
`class FDataflowSkeletonView : public FDataflowNodeView`  
_L20-66_
- inherits: `FDataflowNodeView`
- desc: Class to handle the SelectionView widget
- L23 _public prototype_ `FDataflowSkeletonView(TObjectPtr<UDataflowBaseContent> InContent = nullptr);`
- L24 _public prototype_ `~FDataflowSkeletonView();`
- L27 _public prototype_ `TSharedPtr<ISkeletonTree> CreateEditor(FSkeletonTreeArgs& InSkeletonTreeArgs);` — Create the Skeleton Tree Editor
- L30 _public prototype_ `virtual void SetSupportedOutputTypes() override;` — Set selection types
- L33 _public prototype_ `USkeleton* GetSkeleton();` — Skeleton Access
- L36 _public prototype_ `void UpdateSkeleton();` — Update Data
- L39 _public prototype_ `virtual void UpdateViewData() override;` — Update the view
- L42 _public prototype_ `virtual void ConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override;` — Update the view based on changes in the construction view
- L45 _public function_ `virtual void SimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override` — Update the view based on changes in the simulation view
- L48 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Add GC managed objects
- L51 _public prototype_ `void SkeletonViewSelectionChanged(const TArrayView<TSharedPtr<ISkeletonTreeItem>>& InSelectedItems, ESelectInfo::Type InSelectInfo);` — Selection View Callbacks
- L53 _public member_ `static const FName SkeletonName;`
- L56 _private member_ `TSharedPtr<ISkeletonTree> SkeletonEditor;`
- L59 _private member_ `TObjectPtr<USkeletalMesh> SkeletalMesh;` — Skeletal Mesh in the SkeletalViewer
- L62 _private member_ `TObjectPtr<USkeleton> Skeleton;` — Visualized Skeleton
- L65 _private member_ `TArray<int32> CollectionIndexRemap;` — Rempping from the selected node to the SkeletalMesh

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowSubGraphPaletteItem.h` (Private)


#### class `SDataflowSubGraphPaletteItem`  
`class SDataflowSubGraphPaletteItem : public SGraphPaletteItem`  
_L13-35_
- inherits: `SGraphPaletteItem`
- desc: Widget for displaying a subgraph entry in SDataflowMembersWidget
- L16 _public function_ `SLATE_BEGIN_ARGS(SDataflowSubGraphPaletteItem)`
- L17 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData, TSharedPtr<SDataflowGraphEditor> InEditor);`
- L23 _private prototype_ `virtual TSharedRef<SWidget> CreateTextSlotWidget(FCreateWidgetForActionData* const InCreateData, TAttribute<bool> bIsReadOnly) override;` — SGraphPaletteItem Interface
- L24 _private prototype_ `virtual bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage) override;`
- L25 _private prototype_ `virtual void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit) override;`
- L28 _private prototype_ `const FSlateBrush* GetSubGraphIcon() const;`
- L31 _private member_ `TSharedPtr<FEdGraphSchemaAction_DataflowSubGraph> SubGraphAction;`
- L34 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineRenameWidget;` — held for OnRequestRename calls

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowToolTarget.h` (Private)


#### class `UDataflowReadOnlyToolTarget`  
`class UDataflowReadOnlyToolTarget : public UToolTarget, public IMeshDescriptionProvider, public IDynamicMeshProvider, public IMaterialProvider`  
_L25-69_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTarget,IMeshDescriptionProvider,IDynamicMeshProvider,IMaterialProvider`
- desc: A tool target backed by a read-only dataflow asset that can provide and take a mesh description.
- L36 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget implementation
- L39 _public prototype_ `virtual const FMeshDescription* GetMeshDescription(const FGetMeshParameters& GetMeshParams = FGetMeshParameters()) override;` — IMeshDescriptionProvider implementation
- L40 _public prototype_ `virtual FMeshDescription GetEmptyMeshDescription() override;`
- L43 _public prototype_ `virtual int32 GetNumMaterials() const override;` — IMaterialProvider implementation
- L44 _public prototype_ `virtual UMaterialInterface* GetMaterial(int32 MaterialIndex) const override;`
- L45 _public prototype_ `virtual void GetMaterialSet(FComponentMaterialSet& MaterialSetOut, bool bPreferAssetMaterials) const override;`
- L46 _public prototype_ `virtual bool CommitMaterialSetUpdate(const FComponentMaterialSet& MaterialSet, bool bApplyToAsset) override;`
- L49 _public prototype_ `virtual UE::Geometry::FDynamicMesh3 GetDynamicMesh() override;` — IDynamicMeshProvider
- L57 _protected member_ `TUniquePtr<FMeshDescription> DataflowMeshDescription;` — Until UDataflow stores its internal representation as FMeshDescription, we need to retain the storage here to cover the lifetime of the pointer returned by GetMeshDescription().
- L61 _protected member_ `TObjectPtr<UDataflow> Dataflow = nullptr;` — `UPROPERTY()` — Internal dataflow pointer
- L65 _protected member_ `TObjectPtr<UObject> Asset = nullptr;` — `UPROPERTY()` — Internal asset pointer
- L68 _protected member_ `TSharedPtr<UE::Dataflow::FEngineContext> Context = nullptr;` — Engine context to be used for dataflow evaluation

#### class `UDataflowToolTarget`  
`class UDataflowToolTarget : public UDataflowReadOnlyToolTarget, public IMeshDescriptionCommitter, public IDynamicMeshCommitter`  
_L76-95_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDataflowReadOnlyToolTarget,IMeshDescriptionCommitter,IDynamicMeshCommitter`
- desc: A tool target backed by a dataflow asset that can provide and take a mesh description.
- L85 _public prototype_ `virtual void CommitMeshDescription(const FCommitter& Committer, const FCommitMeshParameters& CommitParams = FCommitMeshParameters()) override;` — IMeshDescriptionCommitter implementation
- L89 _public prototype_ `virtual void CommitDynamicMesh(const UE::Geometry::FDynamicMesh3& Mesh, const FDynamicMeshCommitInfo& CommitInfo) override;` — IDynamicMeshCommitter

#### class `UDataflowReadOnlyToolTargetFactory`  
`class UDataflowReadOnlyToolTargetFactory : public UToolTargetFactory`  
_L100-109_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UDataflowReadOnlyToolTarget to be used by the target manager.
- L107 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;` — UToolTargetFactory implementation
- L108 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### class `UDataflowToolTargetFactory`  
`class UDataflowToolTargetFactory : public UToolTargetFactory`  
_L114-123_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UToolTargetFactory`
- desc: Factory for UDataflowToolTarget to be used by the target manager.
- L121 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;` — UToolTargetFactory implementation
- L122 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowVariablePaletteItem.h` (Private)


#### class `SDataflowVariablePaletteItem`  
`class SDataflowVariablePaletteItem : public SGraphPaletteItem`  
_L14-36_
- inherits: `SGraphPaletteItem`
- desc: Widget for displaying a single variable item in SDataflowMembersWidget
- L17 _public function_ `SLATE_BEGIN_ARGS(SDataflowVariablePaletteItem)`
- L18 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, FCreateWidgetForActionData* const InCreateData, TSharedPtr<SDataflowGraphEditor> InEditor);`
- L24 _private prototype_ `virtual TSharedRef<SWidget> CreateTextSlotWidget(FCreateWidgetForActionData* const InCreateData, TAttribute<bool> bIsReadOnly) override;` — SGraphPaletteItem Interface
- L25 _private prototype_ `virtual bool OnNameTextVerifyChanged(const FText& InNewText, FText& OutErrorMessage) override;`
- L26 _private prototype_ `virtual void OnNameTextCommitted(const FText& NewText, ETextCommit::Type InTextCommit) override;`
- L29 _private prototype_ `void OnPinTypeChanged(const FEdGraphPinType& PinType);`
- L32 _private member_ `TSharedPtr<FEdGraphSchemaAction_DataflowVariable> VariableAction;`
- L35 _private member_ `TSharedPtr<SInlineEditableTextBlock> InlineRenameWidget;` — held for OnRequestRename calls

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DataflowView.h` (Private)


#### class `IDataflowViewListener`  
`class IDataflowViewListener`  
_L20-28_
- desc: Base listener class to interface between the DataflowToolkit and Dataflow views
- L23 _public prototype_ `virtual void OnConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) = 0;`
- L24 _public prototype_ `virtual void OnSimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) = 0;`
- L25 _public prototype_ `virtual void OnSelectedNodeChanged(UDataflowEdNode* InNode) = 0;` — nullptr is valid
- L26 _public prototype_ `virtual void OnNodeInvalidated(FDataflowNode* InvalidatedNode) = 0;`
- L27 _public prototype_ `virtual void RefreshView() = 0;`

#### class `FDataflowNodeView`  
`class FDataflowNodeView : public FGCObject, public IDataflowViewListener`  
_L36-95_
- inherits: `FGCObject,IDataflowViewListener`
- desc: FDataflowNodeView class implements common functions for single node based Dataflow views
- L39 _public prototype_ `FDataflowNodeView(TObjectPtr<UDataflowBaseContent> InContent = nullptr);`
- L41 _public function_ `UDataflowEdNode* GetSelectedNode() const`
- L42 _public prototype_ `bool SelectedNodeHaveSupportedOutputTypes(UDataflowEdNode* InNode);`
- L44 _public function_ `TArray<FString>& GetSupportedOutputTypes()`
- L46 _public prototype_ `TObjectPtr<UDataflowBaseContent> GetEditorContent();`
- L51 _public prototype_ `virtual void UpdateViewData() = 0;` — Virtual functions to overwrite in view widget classes
- L52 _public prototype_ `virtual void SetSupportedOutputTypes() = 0;`
- L53 _public prototype_ `virtual void ConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) = 0;`
- L54 _public prototype_ `virtual void SimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) = 0;`
- L58 _public function_ `void OnPinnedDownChanged(const bool State)` — Callback for PinnedDown change
- L63 _public function_ `void OnRefreshLockedChanged(const bool State)` — Callback for RefreshLock change
- L68 _public prototype_ `virtual void OnConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override;` — Virtual function overrides from IDataflowViewListener base class
- L69 _public prototype_ `virtual void OnSimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements) override;`
- L70 _public prototype_ `virtual void OnSelectedNodeChanged(UDataflowEdNode* InNode) override;` — nullptr is valid
- L71 _public function_ `virtual void OnNodeInvalidated(FDataflowNode* InvalidatedNode) override`
- L72 _public prototype_ `virtual void RefreshView() override;`
- L75 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L76 _public function_ `virtual FString GetReferencerName() const override`
- L79 _public prototype_ `UE::Dataflow::FTimestamp GetNodeLastModifiedTimeStamp(UDataflowEdNode* InNode) const;`
- L80 _public prototype_ `UE::Dataflow::FTimestamp GetNodeLastModifiedTimeStamp(FDataflowNode* InNode) const;`
- L83 _private member_ `TObjectPtr<UDataflowBaseContent> EditorContent = nullptr;`
- L85 _private member_ `TObjectPtr<UDataflowEdNode> SelectedNode = nullptr;`
- L86 _private member_ `UE::Dataflow::FTimestamp LastRefreshTimestamp = UE::Dataflow::FTimestamp::Invalid;`
- L88 _private member_ `bool bIsPinnedDown = false;`
- L90 _private member_ `bool bIsRefreshLocked = false;`
- L92 _private member_ `TArray<FString> SupportedOutputTypes;`
- L94 _private member_ `FDelegateHandle OnNodeInvalidatedDelegateHandle;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/DebugDrawText3dVisualization.h` (Private)


#### class `UE::Dataflow::FDebugDrawText3dVisualization`  
`class FDebugDrawText3dVisualization final : public IDataflowConstructionVisualization`  
_L9-20_
- inherits: `IDataflowConstructionVisualization`
- desc: Display Text3d from FDataflowDebugDraw on the editor's Canvas
- L12 _public member_ `static FName Name;`
- L15 _private function_ `virtual FName GetName() const override`
- L19 _private prototype_ `virtual void DrawCanvas(const FDataflowConstructionScene* ConstructionScene, FCanvas* Canvas, const FSceneView* SceneView) override;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/MeshStatsConstructionVisualization.h` (Private)


#### class `UE::Dataflow::FMeshStatsConstructionVisualization`  
`class FMeshStatsConstructionVisualization final : public IDataflowConstructionVisualization`  
_L9-23_
- inherits: `IDataflowConstructionVisualization`
- desc: A simple visualization that displays the number of triangles in the Construction View Scene
- L12 _public member_ `static FName Name;`
- L15 _private function_ `virtual FName GetName() const override`
- L19 _private prototype_ `virtual void ExtendViewportShowMenu(const TSharedPtr<FDataflowConstructionViewportClient>& ViewportClient, FMenuBuilder& MenuBuilder) override;`
- L20 _private prototype_ `virtual void DrawCanvas(const FDataflowConstructionScene* ConstructionScene, FCanvas* Canvas, const FSceneView* SceneView) override;`
- L22 _private member_ `bool bMeshStatsVisualizationEnabled = false;`

#### Free symbols / members of external scopes

- L6 _namespace_ `namespace UE`
- L6 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/SDataflowGraphActionWidget.h` (Private)


#### class `SDataflowGraphActionWidget`  
`class SDataflowGraphActionWidget : public SCompoundWidget`  
_L12-72_
- inherits: `SCompoundWidget`
- L14 _private function_ `SLATE_BEGIN_ARGS(SDataflowGraphActionWidget)`
- L15 _private function_ `SLATE_ARGUMENT(TSharedPtr<SWidget>, NameWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const FCreateWidgetForActionData* const InCreateData)`
- L58 _private function_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override`
- L69 _private member_ `TWeakPtr<FEdGraphSchemaAction> ActionPtr;` — The action that we want to display with this widget
- L71 _private member_ `FCreateWidgetMouseButtonDown MouseButtonDownDelegate;` — Delegate executed when mouse button goes down

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/SDataflowTemplatePicker.h` (Private)


#### enum `EDataflowPickerResult`  
`enum class EDataflowPickerResult : uint8`  
_L14-24_
- desc: Discriminator for FDataflowPickerResult::Type.
- L17 _public enumerator_ `Template` — User selected a template tile. TemplateIndex and TemplateId are valid.
- L19 _public enumerator_ `ExistingAsset` — User picked an existing asset from the content browser. SelectedAsset is valid.
- L21 _public enumerator_ `None` — User clicked "No Dataflow".
- L23 _public enumerator_ `Cancelled` — User cancelled or closed the window.

#### struct `FDataflowPickerResult`  
`struct FDataflowPickerResult`  
_L28-34_
- L30 _public member_ `EDataflowPickerResult Type = EDataflowPickerResult::Cancelled;`
- L31 _public member_ `int32 TemplateIndex = INDEX_NONE;`
- L32 _public member_ `FName TemplateId;`
- L33 _public member_ `FAssetData SelectedAsset;`

#### class `SDataflowTemplatePicker`  
`class SDataflowTemplatePicker : public SCompoundWidget`  
_L47-99_
- inherits: `SCompoundWidget`
- desc: Modal dialog that lets the user: • choose one of several Dataflow templates (name + icon tiles), • pick an existing Dataflow asset from the content browser, or • opt out ("No Dataflow"). Typical usage: FDataflowPickerResult Result = SDataflowTemplatePicker::ShowModal(Templates, ParentWindow);
- L50 _public function_ `SLATE_BEGIN_ARGS(SDataflowTemplatePicker) : _ParentWindow()`
- L53 _public prototype_ `SLATE_ARGUMENT(TArray<FDataflowTemplateOption>, Templates) SLATE_ARGUMENT(TWeakPtr<SWindow>, ParentWindow) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L63 _public prototype_ `static FDataflowPickerResult ShowModal( const TArray<FDataflowTemplateOption>& Templates, TSharedPtr<SWindow> ParentWindow = nullptr);` — Creates a modal window, blocks until dismissed, then returns the result. Pass a valid ParentWindow to centre the dialog; nullptr uses the main window.
- L67 _public function_ `const FDataflowPickerResult& GetResult() const`
- L71 _private prototype_ `TSharedRef<SWidget> BuildTemplateGrid();` — Build helpers
- L72 _private prototype_ `TSharedRef<SWidget> MakeTemplateTile(const FDataflowTemplateOption& Option, int32 Index);`
- L73 _private prototype_ `TSharedRef<SWidget> BuildAssetPickerSection();`
- L74 _private prototype_ `TSharedRef<SWidget> MakeAssetPickerMenu();`
- L75 _private prototype_ `TSharedRef<SWidget> BuildBottomBar();`
- L78 _private prototype_ `void OnTemplateTileChecked(ECheckBoxState NewState, int32 Index);` — Interaction
- L79 _private prototype_ `void OnAssetSelected(const FAssetData& AssetData);`
- L80 _private prototype_ `void OnAssetDoubleClicked(const FAssetData& AssetData);`
- L81 _private prototype_ `void OnClearAssetSelection();`
- L82 _private prototype_ `FReply OnNoDataflowClicked();`
- L83 _private prototype_ `FReply OnOKClicked();`
- L84 _private prototype_ `FReply OnCancelClicked();`
- L85 _private prototype_ `void CloseOwnerWindow();`
- L88 _private prototype_ `ECheckBoxState GetTileCheckState(int32 Index) const;` — Attribute getters (used by Slate attribute bindings)
- L89 _private prototype_ `bool IsOKEnabled() const;`
- L90 _private prototype_ `FText GetSelectedAssetLabel() const;`
- L91 _private prototype_ `bool HasAssetSelected() const;`
- L94 _private member_ `TArray<FDataflowTemplateOption> Templates;` — State
- L95 _private member_ `TWeakPtr<SWindow> OwnerWindow;`
- L96 _private member_ `TWeakPtr<SComboButton> AssetComboButton;`
- L97 _private member_ `FDataflowPickerResult CandidateResult;`
- L98 _private member_ `FDataflowPickerResult Result;`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/ScalarVertexPropertyGroupCustomization.h` (Private)


#### class `UE::Dataflow::FScalarVertexPropertyGroupCustomization`  
`class FScalarVertexPropertyGroupCustomization : public FPropertyGroupCustomization`  
_L12-22_
- inherits: `FPropertyGroupCustomization`
- desc: Customization for scalara vertex node group names input.
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L19 _private prototype_ `virtual TArray<FName> GetTargetGroupNames(const FManagedArrayCollection& Collection) const override;`
- L20 _private prototype_ `virtual FName GetCollectionPropertyName() const override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Dataflow/SelectionViewWidget.h` (Private)


#### struct `SSelectionInfo`  
`struct SSelectionInfo`  
_L16-20_
- desc: Struct to hold OutputType/Selection data for the outputs Data is stored in a map using the OutputName as key: TMap<FString, SSelectionInfo>
- L18 _public member_ `FString OutputType;`
- L19 _public member_ `const TBitArray<> SelectionArray;`

#### struct `FSelectionViewHeader`  
`struct FSelectionViewHeader`  
_L28-36_
- desc: Header 1st column possible values: Transform Index/Face Index/Vertex Index based on the OutputType 2nd column is SelectionStatus
- L30 _public member_ `static const FName IndexColumnNameTransform;`
- L31 _public member_ `static const FName IndexColumnNameFace;`
- L32 _public member_ `static const FName IndexColumnNameVertex;`
- L33 _public member_ `static const FName SelectionStatusColumnName;`
- L35 _public member_ `TArray<FName> ColumnNames;`

#### struct `FSelectionViewItem`  
`struct FSelectionViewItem`  
_L43-49_
- desc: Representing a row in the table Index/SelectionStatus
- L45 _public member_ `static const FName SelectedName;`
- L46 _public member_ `static const FName NotSelectedName;`
- L48 _public member_ `TArray<FString> Values;`

#### class `SSelectionViewRow`  
`class SSelectionViewRow : public SMultiColumnTableRow<TSharedPtr<const FSelectionViewItem>>`  
_L55-71_
- inherits: `SMultiColumnTableRow<TSharedPtr<constFSelectionViewItem>>`
- L58 _public function_ `SLATE_BEGIN_ARGS(SSelectionViewRow)`
- L60 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<const FSelectionViewHeader>, Header) SLATE_ARGUMENT(TSharedPtr<const FSelectionViewItem>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, const TSharedPtr<const FSelectionViewHeader>& InHeader, const TSharedPtr<const FSelectionViewItem>& InItem);`
- L66 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L69 _private member_ `TSharedPtr<const FSelectionViewHeader> Header;`
- L70 _private member_ `TSharedPtr<const FSelectionViewItem> Item;`

#### class `SSelectionView`  
`class SSelectionView : public SCompoundWidget`  
_L76-108_
- inherits: `SCompoundWidget`
- desc: 2xn grid to display Index/SelectionStatus data
- L79 _public function_ `SLATE_BEGIN_ARGS(SSelectionView)`
- L80 _public prototype_ `SLATE_ARGUMENT(FName, SelectedOutput) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L85 _public function_ `TMap<FString, SSelectionInfo>& GetSelectionInfoMap()`
- L87 _public prototype_ `const FName& GetSelectedOutput() const;`
- L88 _public prototype_ `void SetSelectedOutput(const FName& InSelectedOutput);`
- L90 _public function_ `int32 GetNumItems() const`
- L91 _public function_ `int32 GetNumSelectedItems() const`
- L93 _public prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<const FSelectionViewItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L96 _private member_ `FName SelectedOutput = FName(TEXT(""));`
- L97 _private member_ `TMap<FString, SSelectionInfo> SelectionInfoMap;`
- L99 _private member_ `TSharedPtr<SListView<TSharedPtr<const FSelectionViewItem>>> ListView;`
- L100 _private member_ `TArray<TSharedPtr<const FSelectionViewItem>> ListItems;`
- L102 _private member_ `TSharedPtr<FSelectionViewHeader> Header;`
- L103 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L105 _private member_ `int32 NumItems = 0, NumSelectedItems = 0;`
- L105 _private member_ `int32 NumItems = 0, NumSelectedItems = 0;`
- L106 _private prototype_ `void RegenerateHeader();`
- L107 _private prototype_ `void RepopulateListView();`

#### class `SSelectionViewWidget`  
`class SSelectionViewWidget : public SCompoundWidget`  
_L113-164_
- inherits: `SCompoundWidget`
- desc: Widget for the SelectionView panel
- L116 _public function_ `SLATE_BEGIN_ARGS(SSelectionViewWidget)`
- L118 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L128 _public prototype_ `void SetData(const FString& InNodeName);`
- L129 _public prototype_ `void RefreshWidget();`
- L130 _public function_ `TSharedPtr<SSelectionView> GetSelectionTable()`
- L131 _public prototype_ `void SetStatusText();`
- L134 _public prototype_ `void NodeOutputsComboBoxSelectionChanged(FName InSelectedOutput, ESelectInfo::Type InSelectInfo);` — UI callbacks
- L135 _public prototype_ `FText GetNoOutputText();`
- L138 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinnedDownChanged, const bool);` — Gets a multicast delegate which is called whenever the PinnedDown button clicked
- L139 _public function_ `FOnPinnedDownChanged& GetOnPinnedDownChangedDelegate()`
- L142 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRefreshLockedChanged, const bool);` — Gets a multicast delegate which is called whenever the LockRefresh button clicked
- L143 _public function_ `FOnRefreshLockedChanged& GetOnRefreshLockedChangedDelegate()`
- L145 _public prototype_ `const FSlateBrush* GetPinButtonImage() const;`
- L146 _public prototype_ `const FSlateBrush* GetLockButtonImage() const;`
- L149 _private member_ `TSharedPtr<STextBlock> NodeNameTextBlock;`
- L150 _private member_ `TSharedPtr<SComboBox<FName>> NodeOutputsComboBox;`
- L151 _private member_ `TSharedPtr<STextBlock> NodeOutputsComboBoxLabel;`
- L152 _private member_ `TSharedPtr<SSelectionView> SelectionTable;`
- L153 _private member_ `TSharedPtr<STextBlock> StatusTextBlock;`
- L155 _private member_ `FString NodeName;`
- L156 _private member_ `TArray<FName> NodeOutputs;`
- L157 _private member_ `bool bIsPinnedDown = false;`
- L158 _private member_ `bool bIsRefreshLocked = false;`
- L161 _protected member_ `FOnPinnedDownChanged OnPinnedDownChangedDelegate;`
- L162 _protected member_ `FOnRefreshLockedChanged OnRefreshLockedChangedDelegate;`

#### Free symbols / members of external scopes

- L138 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinnedDownChanged, const bool);` — Gets a multicast delegate which is called whenever the PinnedDown button clicked
- L142 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRefreshLockedChanged, const bool);` — Gets a multicast delegate which is called whenever the LockRefresh button clicked

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowDynamicMeshMapping.h` (Private)


#### struct `UE::Dataflow::FDynamicMeshMapping`  
`struct FDynamicMeshMapping`  
_L18-55_
- desc: Represent data to map from the dynamic mesh to the source mesh in some case the dynamic mesh may have more vertices created during its construction than the source
- L27 _public prototype_ `void Init(const UE::Geometry::FDynamicMesh3& Mesh);`
- L28 _public prototype_ `void Reset();`
- L30 _public function_ `const TArray<int32>& GetMappedSourceVertices() const`
- L32 _public prototype_ `void RemapVertices(const TSet<int32>& InVertices, TSet<int32>& OutVertices, ERemapDirection Direction) const;`
- L36 _private member_ `bool bHasNonManifoldMapping = false;` — true if the source mesh was non manifold and the dynamic mesh stores a mapping
- L42 _private member_ `TArray<int32> DynamicMeshToSource;` — mapping from the dynamic mesh vertices to the source mesh vertices (1 to 1 vertices) empty if bHasNonManifoldMapping = false
- L48 _private member_ `int32 SourceVertexIDOffset = 0;` — source vertex ID that correspond to the first entry of SourceToDynamicMesh this is used to save memory when only a subset of the orignal mesh is respresented by the dynamic mesh
- L54 _private member_ `TArray<TArray<int32>> SourceToDynamicMesh;` — mapping from the source mesh vertices to the dynamic mesh ones (1 to N relationship) empty if bHasNonManifoldMapping = false

#### enum `UE::Dataflow::FDynamicMeshMapping::ERemapDirection`  
`enum class ERemapDirection : uint8`  
_L21-25_
- L23 _public enumerator_ `SourceToDynamicMesh`
- L24 _public enumerator_ `DynamicMeshToSource`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Geometry` (scope `UE`)
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowEditorBoneManipulator.h` (Private)


#### class `UDataflowBoneManipulator`  
`class UDataflowBoneManipulator : public UObject`  
_L19-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L24 _public prototype_ `void Setup(UInteractiveToolManager* ToolManager, const FReferenceSkeleton& RefSkeleton);`
- L25 _public prototype_ `void Shutdown(UInteractiveToolManager* ToolManager);`
- L27 _public prototype_ `void SetSelectedBoneByName(FName BoneName);`
- L28 _public prototype_ `void SetSelectedBoneByIndex(int32 BoneIndex);`
- L30 _public function_ `URefSkeletonPoser* GetRefSkeletonPoser() const`
- L32 _public prototype_ `void SetEnabled(bool bEnabled);`
- L34 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReferenceSkeletonUpdated, UDataflowBoneManipulator&);`
- L35 _public member_ `FOnReferenceSkeletonUpdated OnReferenceSkeletonUpdated;`
- L38 _private prototype_ `void OnStartTransformEdit(UTransformProxy*);`
- L39 _private prototype_ `void OnTransformUpdated(UTransformProxy*, FTransform NewTransform);`
- L40 _private prototype_ `void OnEndTransformEdit(UTransformProxy*);`
- L44 _private member_ `TObjectPtr<UTransformProxy> TransformProxy;` — `UPROPERTY(Transient)` — Source mesh transform gizmo support
- L47 _private member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo;` — `UPROPERTY(Transient)`
- L50 _private member_ `TObjectPtr<URefSkeletonPoser> RefSkeletonPoser;` — `UPROPERTY(Transient)`
- L53 _private member_ `int32 BoneIndex = INDEX_NONE;` — `UPROPERTY(Transient)`
- L55 _private member_ `FTransform StartTransform;`
- L57 _private member_ `bool bEnabled = true;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnReferenceSkeletonUpdated, UDataflowBoneManipulator&);`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowEditorCorrectSkinWeightsNode.h` (Private)


#### enum `ESkinWeightsCorrectionType`  
`enum class ESkinWeightsCorrectionType : uint8`  
_L17-24_
- reflection: `UENUM()`
- desc: Skin weights correction type
- L19 _public enumerator_ `Relax`
- L20 _public enumerator_ `Prune`
- L21 _public enumerator_ `Hammer`
- L22 _public enumerator_ `Clamp`
- L23 _public enumerator_ `Normalize`

#### struct `FDataflowCorrectSkinWeightsNode`  
`struct FDataflowCorrectSkinWeightsNode : public FDataflowNode`  
_L28-117_
- reflection: `USTRUCT(Meta = (Experimental, DataflowCollection))`
- inherits: `FDataflowNode`
- desc: Correct skin weights vertex properties.
- L36 _public member_ `static const FName HammerSkinWeightsSelectionName;`
- L37 _public member_ `static const FName RelaxSkinWeightsSelectionName;`
- L38 _public member_ `static const FName ClampSkinWeightsSelectionName;`
- L39 _public member_ `static const FName NormalizeSkinWeightsSelectionName;`
- L41 _public prototype_ `FDataflowCorrectSkinWeightsNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L44 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L48 _public member_ `FString BoneIndicesName;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Bone Indices"))` — The name to be set for the bone indices.
- L52 _public member_ `FString BoneWeightsName;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Bone Weights"))` — The name to be set for the bone weights.
- L56 _public member_ `FString SelectionMapName;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Selection Map"))` — Map name to be used to select vertices to correct
- L60 _public member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Vertex Group"))` — Target group in which the attributes are stored
- L64 _public member_ `FCollectionAttributeKey BoneIndicesKey;` — `UPROPERTY(meta = (DisplayName = "Bone Indices", DataflowInput, DataflowOutput, DataflowPassthrough = "BoneIndicesKey"))` — Bone indices key to be used in other nodes if necessary
- L68 _public member_ `FCollectionAttributeKey BoneWeightsKey;` — `UPROPERTY(meta = (DisplayName = "Bone Weights", DataflowInput, DataflowOutput, DataflowPassthrough = "BoneWeightsKey"))` — Bone weights key to be used in other nodes if necessary
- L72 _public member_ `FCollectionAttributeKey SelectionMapKey;` — `UPROPERTY(meta = (DisplayName = "Selection Map", DataflowInput))` — Selection map key to be used in other nodes if necessary
- L76 _public member_ `ESkinWeightsCorrectionType CorrectionType = ESkinWeightsCorrectionType::Relax;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Correction Type"))` — Selection map key to be used in other nodes if necessary
- L80 _public member_ `int32 SmoothingIterations = 5;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Smoothing Iterations", DataflowInput, EditCondition = "CorrectionType == ESkinWeightsCorrectionType::Relax", EditConditionHides))` — Number of iteration required for the smoothing
- L84 _public member_ `float SmoothingFactor = 0.5;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Smooting Factor", DataflowInput, EditCondition = "CorrectionType == ESkinWeightsCorrectionType::Relax", EditConditionHides))` — Lerp value in between the current and the average weight values
- L88 _public member_ `bool bUseSelectionAsPerVertexFactor = false;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DataflowInput, EditCondition = "CorrectionType == ESkinWeightsCorrectionType::Relax", EditConditionHides))` — When true, use the decimal values of the selection as a per vertex factor for the selected operation - Currently available for Relax operation only - false by default
- L92 _public member_ `float PruningThreshold = 0.01f;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Pruning Threshold", DataflowInput, EditCondition = "CorrectionType == ESkinWeightsCorrectionType::Prune", EditConditionHides))` — All weights below this threshold will be pruned
- L96 _public member_ `int32 ClampingNumber = 8;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Clamping Number", DataflowInput, EditCondition = "CorrectionType == ESkinWeightsCorrectionType::Clamp", EditConditionHides))` — Max number of bones to consider for the skin weights
- L100 _public member_ `float SelectionThreshold = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Selection Threshold", DataflowInput, EditCondition = "CorrectionType == ESkinWeightsCorrectionType::Hammer", EditConditionHides, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Selection threshold to consider a neighbor skin weight
- L103 _public prototype_ `FCollectionAttributeKey GetBoneIndicesKey(UE::Dataflow::FContext& Context) const;` — Get the weights attribute key to retrieve/set the bone indices values
- L106 _public prototype_ `FCollectionAttributeKey GetBoneWeightsKey(UE::Dataflow::FContext& Context) const;` — Get the weights attribute key to retrieve/set the bone weights values
- L109 _public prototype_ `FCollectionAttributeKey GetSelectionMapKey(UE::Dataflow::FContext& Context) const;` — Get the selection map key to get the vertex selection on which the correction will be applied
- L114 _private prototype_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParametersImpl() const override;`
- L115 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowSetSkinningSelectionNode`  
`struct FDataflowSetSkinningSelectionNode : public FDataflowNode`  
_L121-158_
- reflection: `USTRUCT(Meta = (Experimental, DataflowCollection))`
- inherits: `FDataflowNode`
- desc: Set skin weights selection attributes.
- L128 _public prototype_ `FDataflowSetSkinningSelectionNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L131 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L135 _public member_ `FString SelectionMapName;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Selection Map"))` — Map name to be used to select vertices to correct
- L139 _public member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Vertex Group"))` — Target group in which the attributes are stored
- L143 _public member_ `FCollectionAttributeKey SelectionMapKey;` — `UPROPERTY(meta = (DisplayName = "Selection Map", DataflowInput))` — Selection map key to be used in other nodes if necessary
- L147 _public member_ `ESkinWeightsCorrectionType CorrectionType = ESkinWeightsCorrectionType::Relax;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Correction Type"))` — Selection map key to be used in other nodes if necessary
- L150 _public prototype_ `FCollectionAttributeKey GetSelectionMapKey(UE::Dataflow::FContext& Context) const;` — Get the selection map key to get the vertex selection on which the correction will be applied
- L155 _private prototype_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParametersImpl() const override;`
- L156 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### struct `FDataflowGetSkinningSelectionNode`  
`struct FDataflowGetSkinningSelectionNode : public FDataflowNode`  
_L164-194_
- reflection: `USTRUCT(Meta = (Experimental, DataflowCollection))`
- inherits: `FDataflowNode`
- desc: Get skin weights selection attributes.
- L171 _public prototype_ `FDataflowGetSkinningSelectionNode(const UE::Dataflow::FNodeParameters& InParam, FGuid InGuid = FGuid::NewGuid());`
- L174 _public member_ `FManagedArrayCollection Collection;` — `UPROPERTY(Meta = (DataflowInput, DataflowOutput, DataflowPassthrough = "Collection"))`
- L178 _public member_ `FScalarVertexPropertyGroup VertexGroup;` — `UPROPERTY(EditAnywhere, Category = "Vertex Attributes", meta = (DisplayName = "Vertex Group"))` — Target group in which the attributes are stored
- L182 _public member_ `FCollectionAttributeKey SelectionMapKey;` — `UPROPERTY(meta = (DisplayName = "Selection Map", DataflowOutput))` — Selection map key to be used in other nodes if necessary
- L186 _public member_ `ESkinWeightsCorrectionType CorrectionType = ESkinWeightsCorrectionType::Relax;` — `UPROPERTY(EditAnywhere, Category = "Skin Weights", meta = (DisplayName = "Correction Type"))` — Selection map key to be used in other nodes if necessary
- L191 _private prototype_ `virtual TArray<UE::Dataflow::FRenderingParameter> GetRenderParametersImpl() const override;`
- L192 _private prototype_ `virtual void Evaluate(UE::Dataflow::FContext& Context, const FDataflowOutput* Out) const override;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowEditorEditSkeletonBonesTool.h` (Private)


#### class `UDataflowEditorEditSkeletonBonesToolBuilder`  
`class UDataflowEditorEditSkeletonBonesToolBuilder : public USkeletonEditingToolBuilder, public IDataflowEditorToolBuilder`  
_L23-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkeletonEditingToolBuilder,IDataflowEditorToolBuilder`
- desc: Dataflow edit skeleton tool builder
- L29 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;`
- L30 _private function_ `virtual bool CanSetConstructionViewWireframeActive() const override`
- L34 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L35 _private prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L39 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UDataflowEditorEditSkeletonBonesTool`  
`class UDataflowEditorEditSkeletonBonesTool : public USkeletonEditingTool`  
_L46-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkeletonEditingTool`
- desc: Dataflow edit skeleton tool
- L51 _private prototype_ `virtual void Setup() override;`
- L52 _private prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L53 _private prototype_ `virtual TScriptInterface<ITransformGizmoSource> BuildTransformSource() override;`
- L61 _private function_ `void SetDataflowEditorContextObject(TObjectPtr<UDataflowContextObject> InDataflowEditorContextObject)` — Set the dataflow context object
- L67 _private member_ `struct FDataflowCollectionEditSkeletonBonesNode* EditSkeletonBonesNode = nullptr;` — Edit Skeleton node associated with that tool
- L70 _private member_ `TObjectPtr<UDataflowContextObject> DataflowEditorContextObject;` — Dataflow context object to be used to retrieve the node context data

#### class `FDataflowSkeletalMeshEditorNotifier`  
`class FDataflowSkeletalMeshEditorNotifier : public ISkeletalMeshNotifier`  
_L74-84_
- inherits: `ISkeletalMeshNotifier`
- desc: Notifier when skeleton selection is changing
- L77 _public prototype_ `FDataflowSkeletalMeshEditorNotifier();`
- L80 _public prototype_ `virtual void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) override;`

#### class `FDataflowSkeletalMeshEditorBinding`  
`class FDataflowSkeletalMeshEditorBinding : public ISkeletalMeshEditorBinding`  
_L87-104_
- inherits: `ISkeletalMeshEditorBinding`
- desc: Binding used to retrieve the bone names (morph targets not used)
- L90 _public prototype_ `FDataflowSkeletalMeshEditorBinding();`
- L93 _public prototype_ `virtual TSharedPtr<ISkeletalMeshNotifier> GetNotifier() override;`
- L94 _public prototype_ `virtual NameFunction GetNameFunction() override;`
- L95 _public prototype_ `virtual TArray<FName> GetSelectedBones() const override;`
- L98 _public member_ `TArray<FName> BoneSelection;`
- L103 _private member_ `TSharedPtr<FDataflowSkeletalMeshEditorNotifier> DataflowNotifier;` — Notifier used when the tool selection is changing

#### class `UDataflowTransformGizmoSource`  
`class UDataflowTransformGizmoSource : public UEditorTransformGizmoSource`  
_L111-135_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorTransformGizmoSource`
- desc: UDataflowTransformGizmoSource is an ITransformGizmoSource implementation that provides current state information used to configure the Editor transform gizmo.
- L117 _public prototype_ `virtual EGizmoTransformMode GetGizmoMode() const override;`
- L118 _public function_ `virtual EToolContextCoordinateSystem GetGizmoCoordSystemSpace() const override`
- L119 _public function_ `virtual float GetGizmoScale() const override`
- L120 _public prototype_ `virtual bool GetVisible(const EViewportContext InViewportContext = EViewportContext::Focused) const override;`
- L121 _public prototype_ `virtual bool CanInteract(const EViewportContext InViewportContext = EViewportContext::Focused) const override;`
- L122 _public function_ `virtual EGizmoTransformScaleType GetScaleType() const override`
- L123 _public prototype_ `virtual const FRotationContext& GetRotationContext() const override;`
- L127 _public prototype_ `static UDataflowTransformGizmoSource* CreateNew( UObject* Outer = (UObject*)GetTransientPackage(), const class UEditorTransformGizmoContextObject* ContextObject = nullptr);` — Transform source creation
- L134 _private member_ `EGizmoTransformMode GizmoMode = EGizmoTransformMode::Translate;` — Default transform mode to be used when moving bones

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowEditorSkinWeightsPaintTool.h` (Private)


#### class `UDataflowEditorSkinWeightsPaintToolBuilder`  
`class UDataflowEditorSkinWeightsPaintToolBuilder : public USkinWeightsPaintToolBuilder, public IDataflowEditorToolBuilder`  
_L26-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkinWeightsPaintToolBuilder,IDataflowEditorToolBuilder`
- desc: Dataflow skin weights tool builder
- L32 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;`
- L33 _private function_ `virtual bool CanSetConstructionViewWireframeActive() const override`
- L37 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L38 _private prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L42 _protected prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UDataflowEditorSkinWeightsPaintTool`  
`class UDataflowEditorSkinWeightsPaintTool : public USkinWeightsPaintTool`  
_L49-91_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkinWeightsPaintTool`
- desc: Dataflow skin weights painting tool
- L54 _public prototype_ `void SetSkinWeightNode(FDataflowCollectionEditSkinWeightsNode* Node);`
- L57 _public prototype_ `void SetDataflowEditorContextObject(TObjectPtr<UDataflowContextObject> InDataflowEditorContextObject);` — Set the dataflow context object
- L61 _private function_ `virtual FEditorViewportClient* GetViewportClient() const override`
- L62 _private prototype_ `virtual void Setup() override;`
- L63 _private prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L64 _private function_ `virtual bool CanAccept() const override`
- L65 _private prototype_ `virtual void ToggleBoneManipulation(bool bEnable);`
- L66 _private prototype_ `virtual const TArray<FTransform>& GetComponentSpaceBoneTransforms();`
- L69 _private prototype_ `void HandleOnBoneSelectionChanged(const TArray<FName>& BoneNames);`
- L70 _private prototype_ `void HandleOnUpdateRefSkeletonToDraw(FReferenceSkeleton& InOutRefSkeletonToUpdate);`
- L73 _private prototype_ `bool ExtractSkinWeights(TArray<TArray<int32>>& OutCurrentIndices, TArray<TArray<float>>& OutCurrentWeights, TArray<TArray<int32>>& OutSetupIndices, TArray<TArray<float>>& OutSetupWeights);` — extract the initial weights and indices values as well as the delta values
- L75 _private prototype_ `void PoseMesh(URefSkeletonPoser* Poser);`
- L78 _private prototype_ `int32 GetVertexOffset() const;` — Get the skeletal mesh vertex offset in the node collection
- L81 _private member_ `FDataflowCollectionEditSkinWeightsNode* SkinWeightNode = nullptr;` — Skin weight node associated with that tool
- L84 _private member_ `TObjectPtr<UDataflowContextObject> DataflowEditorContextObject;` — Dataflow context object to be used to retrieve the node context data
- L86 _private member_ `TObjectPtr<UDataflowBoneManipulator> BoneManipulator = nullptr;`
- L88 _private member_ `FDelegateHandle OnBoneSelectionChangedDelegateHandle;`
- L90 _private member_ `bool bWeightsHaveChanged = false;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowEditorToolEnums.h` (Private)


#### enum `EDataflowEditorToolEditMode`  
`enum class EDataflowEditorToolEditMode : uint8`  
_L8-12_
- reflection: `UENUM()`
- L10 _public enumerator_ `Brush`
- L11 _public enumerator_ `Mesh`

#### enum `EDataflowEditorToolBrushAreaType`  
`enum class EDataflowEditorToolBrushAreaType : uint8`  
_L15-19_
- reflection: `UENUM()`
- L17 _public enumerator_ `Connected`
- L18 _public enumerator_ `Volumetric`

#### enum `EDataflowEditorToolEditOperation`  
`enum class EDataflowEditorToolEditOperation : uint8`  
_L22-29_
- reflection: `UENUM()`
- L24 _public enumerator_ `Add`
- L25 _public enumerator_ `Replace`
- L26 _public enumerator_ `Multiply`
- L27 _public enumerator_ `Invert`
- L28 _public enumerator_ `Relax`

#### enum `EDataflowEditorToolColorMode`  
`enum class EDataflowEditorToolColorMode : uint8`  
_L32-37_
- reflection: `UENUM()`
- L34 _public enumerator_ `Greyscale`
- L35 _public enumerator_ `Ramp`
- L36 _public enumerator_ `FullMaterial`

#### enum `EDataflowEditorToolVisibilityType`  
`enum class EDataflowEditorToolVisibilityType : uint8`  
_L40-44_
- reflection: `UENUM()`
- L42 _public enumerator_ `None`
- L43 _public enumerator_ `Unoccluded`

#### enum `EDataflowEditorToolMirrorDirection`  
`enum class EDataflowEditorToolMirrorDirection : uint8`  
_L48-52_
- reflection: `UENUM()`
- desc: mirror direction mode
- L50 _public enumerator_ `PositiveToNegative`
- L51 _public enumerator_ `NegativeToPositive`

#### enum `EDataflowEditorToolValueQueryType`  
`enum class EDataflowEditorToolValueQueryType : uint8`  
_L56-66_
- reflection: `UENUM()`
- desc: Value Query mode
- L59 _public enumerator_ `Interpolated UMETA(DisplayName = "Interpolated")` — Value is interpolated from triangle vertices
- L62 _public enumerator_ `NearestVertexFast UMETA(DisplayName = "Nearest Vertex (Fast)")` — Return the value at the closest vertex of the triangle under the mouse cursor
- L65 _public enumerator_ `NearestVertexAccurate UMETA(DisplayName = "Nearest Vertex (Accurate)")` — Return the value of the nearest vertex inside the brush radius, even if the vertex is not on the triangle under the mouse cursor

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowEditorWeightMapPaintBrushOps.h` (Private)


#### class `FDataflowMeshVertexWeightMapEditBrushOp`  
`class FDataflowMeshVertexWeightMapEditBrushOp : public FMeshSculptBrushOp`  
_L12-39_
- inherits: `FMeshSculptBrushOp`
- L17 _public typedef_ `using FalloffFunction = TFunction<float(const FVector&)>;` — falloff as a function of position
- L20 _public function_ `virtual void ApplyStamp( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<FVector3d>& NewColorsOut) override` — not supported for this kind of brush op
- L30 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) = 0;`
- L37 _public member_ `bool bApplyRadiusLimit = true;` — If bApplyRadiusLimit is enabled, only vertices within the stamp radius are considered

#### class `UDataflowWeightMapEraseBrushOpProps`  
`class UDataflowWeightMapEraseBrushOpProps : public UMeshSculptBrushOpProps`  
_L48-60_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L55 _public member_ `double AttributeValue = 0;` — `UPROPERTY(EditAnywhere, Category = EraseBrush, meta = (DisplayName = "Erase Attribute", UIMin = 0))` — Attribute to set as Erased value
- L57 _public function_ `virtual double GetAttribute()`
- L59 _public function_ `virtual float GetFalloff() override`

#### class `FDataflowWeightMapEraseBrushOp`  
`class FDataflowWeightMapEraseBrushOp : public FDataflowMeshVertexWeightMapEditBrushOp`  
_L64-74_
- inherits: `FDataflowMeshVertexWeightMapEditBrushOp`
- L68 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) override;`

#### class `UDataflowWeightMapPaintBrushOpProps`  
`class UDataflowWeightMapPaintBrushOpProps : public UMeshSculptBrushOpProps`  
_L82-106_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L90 _public member_ `double AttributeValue = 1;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Value", UIMin = 0))` — The Attribute that will be assigned to triangles within the brush region
- L94 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10."))` — Strength of the Brush
- L97 _public member_ `float Falloff = 0;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (UIMin = "0.0", UIMax = "1.", ClampMin = "0.0", ClampMax = "1."))`
- L99 _public function_ `virtual double GetAttribute()`
- L101 _public function_ `virtual float GetStrength() override`
- L102 _public function_ `virtual void SetStrength(float NewStrength) override`
- L104 _public function_ `virtual void SetFalloff(float NewFalloff)`
- L105 _public function_ `virtual float GetFalloff() override`

#### class `FDataflowWeightMapPaintBrushOp`  
`class FDataflowWeightMapPaintBrushOp : public FDataflowMeshVertexWeightMapEditBrushOp`  
_L109-124_
- inherits: `FDataflowMeshVertexWeightMapEditBrushOp`
- L113 _public function_ `virtual bool IgnoreZeroMovements() const override`
- L118 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) override;`

#### class `UDataflowWeightMapSmoothBrushOpProps`  
`class UDataflowWeightMapSmoothBrushOpProps : public UMeshSculptBrushOpProps`  
_L132-145_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- L139 _public member_ `float Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10."))`
- L141 _public function_ `virtual float GetStrength() override`
- L142 _public function_ `virtual void SetStrength(float NewStrength) override`
- L144 _public function_ `virtual float GetFalloff() override`

#### class `FDataflowWeightMapSmoothBrushOp`  
`class FDataflowWeightMapSmoothBrushOp : public FDataflowMeshVertexWeightMapEditBrushOp`  
_L148-180_
- inherits: `FDataflowMeshVertexWeightMapEditBrushOp`
- L152 _public function_ `virtual bool IgnoreZeroMovements() const override`
- L157 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) override;`
- L163 _public prototype_ `static void ApplyStampByVerticesStatic( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut, bool bApplyRadiusLimit, TSharedPtr<FMeshSculptFallofFunc> FalloffFunc = {});`
- L171 _public prototype_ `static void ApplyToVerticesStatic( const FDynamicMesh3* Mesh, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut, const double SmoothingFactor, bool bApplyRadiusLimit, const FVector Center, const float Radius, FalloffFunction FalloffFunc = {});`

#### class `UDataflowVertexAttributePaintBrushOpProps`  
`class UDataflowVertexAttributePaintBrushOpProps : public UMeshSculptBrushOpProps`  
_L186-209_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptBrushOpProps`
- desc: this brush leverage EDataflowEditorToolEditOperation to decide how to paint the vertex attribute
- L193 _public member_ `double AttributeValue = 1;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Value", UIMin = 0))` — The Attribute that will be assigned to triangles within the brush region
- L196 _public member_ `float Strength = 1.0;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (DisplayName = "Strength", UIMin = "0.0", UIMax = "10.", ClampMin = "0.0", ClampMax = "10."))`
- L199 _public member_ `float Falloff = 0;` — `UPROPERTY(EditAnywhere, Category = PaintBrush, meta = (UIMin = "0.0", UIMax = "1.", ClampMin = "0.0", ClampMax = "1."))`
- L201 _public function_ `virtual double GetAttribute()`
- L202 _public function_ `virtual float GetStrength() override`
- L203 _public function_ `virtual void SetStrength(float NewStrength) override`
- L205 _public function_ `virtual void SetFalloff(float NewFalloff)`
- L206 _public function_ `virtual float GetFalloff() override`
- L208 _public member_ `EDataflowEditorToolEditOperation EditOperation = EDataflowEditorToolEditOperation::Add;`

#### class `FDataflowVertexAttributePaintBrushOp`  
`class FDataflowVertexAttributePaintBrushOp : public FDataflowMeshVertexWeightMapEditBrushOp`  
_L211-245_
- inherits: `FDataflowMeshVertexWeightMapEditBrushOp`
- L214 _public function_ `virtual bool IgnoreZeroMovements() const override`
- L219 _public prototype_ `virtual void ApplyStampByVertices( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut) override;`
- L225 _public prototype_ `static void ApplyStampByVerticesStatic( const FDynamicMesh3* Mesh, const FSculptBrushStamp& Stamp, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut, EDataflowEditorToolEditOperation EditOperation, const double ToolValue, bool bApplyRadiusLimit, TSharedPtr<FMeshSculptFallofFunc> FalloffFunc = {});`
- L235 _public prototype_ `static void ApplyToVerticesStatic( const FDynamicMesh3* Mesh, const TArray<int32>& Vertices, TArray<double>& NewAttributesOut, EDataflowEditorToolEditOperation EditOperation, const double ToolValue, bool bApplyRadiusLimit, const FVector Center, const float Radius, FalloffFunction FalloffFunc = {});`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowEditorWeightMapPaintTool.h` (Private)


#### class `UDataflowEditorWeightMapPaintToolBuilder`  
`class UDataflowEditorWeightMapPaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder, public IDataflowEditorToolBuilder`  
_L63-78_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder,IDataflowEditorToolBuilder`
- desc: Tool Builder
- L67 _public prototype_ `void SetEditorMode(UDataflowEditorMode* InMode);`
- L70 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;`
- L71 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L72 _private prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L73 _private function_ `virtual bool CanSetConstructionViewWireframeActive() const`
- L77 _private member_ `TMap<TWeakObjectPtr<const UInteractiveToolManager>, TWeakObjectPtr<UDataflowEditorMode>> ModeForToolManager;` — Per-editor mode lookup keyed by the editor's tool manager. This builder is held by the process-wide FDataflowToolRegistry singleton, so a single Mode pointer would alias across simultaneously-open Dataflow editors; the map keeps each editor's mode separate.

#### enum `EDataflowEditorWeightMapPaintInteractionType`  
`enum class EDataflowEditorWeightMapPaintInteractionType : uint8`  
_L85-93_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L87 _public enumerator_ `Brush`
- L88 _public enumerator_ `Fill`
- L89 _public enumerator_ `PolyLasso`
- L90 _public enumerator_ `Gradient`
- L92 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EDataflowEditorWeightMapPaintBrushType`  
`enum class EDataflowEditorWeightMapPaintBrushType : uint8`  
_L97-109_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L100 _public enumerator_ `Paint UMETA(DisplayName = "Paint")` — Paint weights
- L103 _public enumerator_ `Smooth UMETA(DisplayName = "Smooth")` — Smooth existing weights
- L106 _public enumerator_ `Erase UMETA(Hidden, DisplayName = "Erase")` — Erase weights
- L108 _public enumerator_ `LastValue UMETA(Hidden)`

#### enum `EDataflowEditorWeightMapPaintBrushAreaType`  
`enum class EDataflowEditorWeightMapPaintBrushAreaType : uint8`  
_L114-118_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Area Types
- L116 _public enumerator_ `Connected`
- L117 _public enumerator_ `Volumetric`

#### enum `EDataflowEditorWeightMapPaintVisibilityType`  
`enum class EDataflowEditorWeightMapPaintVisibilityType : uint8`  
_L122-126_
- reflection: `UENUM()`
- desc: Mesh Sculpting Brush Types
- L124 _public enumerator_ `None`
- L125 _public enumerator_ `Unoccluded`

#### class `UDataflowEditorWeightMapPaintBrushFilterProperties`  
`class UDataflowEditorWeightMapPaintBrushFilterProperties : public UInteractiveToolPropertySet`  
_L131-203_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L138 _public member_ `EDataflowEditorWeightMapPaintInteractionType SubToolType = EDataflowEditorWeightMapPaintInteractionType::Brush;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Action"))`
- L142 _public member_ `EDataflowEditorWeightMapPaintBrushType PrimaryBrushType = EDataflowEditorWeightMapPaintBrushType::Paint;` — `UPROPERTY(EditAnywhere, Category = ActionType, meta = (DisplayName = "Brush Mode", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush"))`
- L147 _public member_ `float BrushSize = 0.25f;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (DisplayName = "Brush Size", UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "10.0", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush"))` — Relative size of brush
- L153 _public member_ `double AttributeValue = 1;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "(SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush && PrimaryBrushType == EDataflowEditorWeightMapPaintBrushType::Paint) || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill || SubToolType == EDataflowEditorWeightMapPaintInteractionType::PolyLasso"))` — The new value to paint on the mesh
- L159 _public member_ `double Strength = 0.5;` — `UPROPERTY(EditAnywhere, Category = Brush, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill"))` — How quickly each brush stroke will drive mesh values towards the desired value
- L164 _public member_ `double GradientHighValue = 1.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Gradient"))` — The Gradient upper limit value
- L169 _public member_ `double GradientLowValue = 0.0;` — `UPROPERTY(EditAnywhere, Category = Gradient, meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Gradient"))` — The Gradient lower limit value
- L175 _public member_ `EMeshVertexPaintBrushAreaType BrushAreaMode = EMeshVertexPaintBrushAreaType::Connected;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (DisplayName = "Brush Area Mode", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill"))` — Area Mode specifies the shape of the brush and which triangles will be included relative to the cursor
- L181 _public member_ `float AngleThreshold = 180.0f;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0", HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill"))` — The Region affected by the current operation will be bounded by edge angles larger than this threshold
- L186 _public member_ `bool bUVSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill"))` — The Region affected by the current operation will be bounded by UV borders/seams
- L191 _public member_ `bool bNormalSeams = false;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill"))` — The Region affected by the current operation will be bounded by Hard Normal edges/seams
- L196 _public member_ `EDataflowEditorWeightMapPaintVisibilityType VisibilityFilter = EDataflowEditorWeightMapPaintVisibilityType::None;` — `UPROPERTY(EditAnywhere, Category = Filters, meta = (HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill || SubToolType == EDataflowEditorWeightMapPaintInteractionType::PolyLasso"))` — Control which triangles can be affected by the current operation based on visibility. Applied after all other filters.
- L201 _public member_ `double ValueAtBrush = 0;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Query, meta = (NoResetToDefault, HideEditConditionToggle, EditConditionHides, EditCondition = "SubToolType == EDataflowEditorWeightMapPaintInteractionType::Brush || SubToolType == EDataflowEditorWeightMapPaintInteractionType::Fill"))` — The weight value at the brush indicator

#### enum `EDataflowEditorWeightMapPaintToolActions`  
`enum class EDataflowEditorWeightMapPaintToolActions`  
_L206-213_
- reflection: `UENUM()`
- L208 _public enumerator_ `NoAction`
- L209 _public enumerator_ `FloodFillCurrent`
- L210 _public enumerator_ `ClearAll`
- L211 _public enumerator_ `InvertCurrent`
- L212 _public enumerator_ `InvertCurrentSurface`

#### class `UDataflowEditorMeshWeightMapPaintToolActions`  
`class UDataflowEditorMeshWeightMapPaintToolActions : public UInteractiveToolPropertySet`  
_L216-253_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L222 _public member_ `TWeakObjectPtr<UDataflowEditorWeightMapPaintTool> ParentTool;`
- L224 _public function_ `void Initialize(UDataflowEditorWeightMapPaintTool* ParentToolIn)`
- L226 _public prototype_ `void PostAction(EDataflowEditorWeightMapPaintToolActions Action);`
- L229 _public function_ `void ClearAll()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 10))`
- L235 _public function_ `void FloodFillCurrent()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 12))`
- L242 _public function_ `void InvertCurrent()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 13))` — Invert the values in range [0, 1] for the current selected geometry, including interior vertices
- L249 _public function_ `void InvertCurrentSurface()` — `UFUNCTION(CallInEditor, Category = Operations, meta = (DisplayPriority = 13))` — Invert the values in range [0, 1] for the current selected surface

#### class `UDataflowEditorUpdateWeightMapProperties`  
`class UDataflowEditorUpdateWeightMapProperties : public UInteractiveToolPropertySet`  
_L256-268_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L263 _public member_ `FString Name;` — `UPROPERTY()`
- L267 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`

#### class `UDataflowEditorWeightMapPaintTool`  
`class UDataflowEditorWeightMapPaintTool : public UMeshSculptToolBase`  
_L274-517_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSculptToolBase`
- desc: Mesh Element Paint Tool Class
- L279 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L281 _public prototype_ `virtual void Setup() override;`
- L282 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L283 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L284 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L285 _public prototype_ `virtual void UpdateMaterialMode(EMeshEditingMaterialModes MaterialMode) override;`
- L286 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L288 _public function_ `virtual bool HasCancel() const override`
- L289 _public function_ `virtual bool HasAccept() const override`
- L290 _public prototype_ `virtual bool CanAccept() const override;`
- L292 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L294 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L296 _public prototype_ `bool IsInBrushSubMode() const;`
- L298 _public prototype_ `virtual void CommitResult(UBaseDynamicMeshComponent* Component, bool bModifiedTopology) override;`
- L300 _public prototype_ `void SetDataflowEditorContextObject(TObjectPtr<UDataflowContextObject> InDataflowEditorContextObject);`
- L301 _public function_ `void SetEditorMode(UDataflowEditorMode* InMode)`
- L303 _public prototype_ `virtual void SetupBrushEditBehaviorSetup(ULocalTwoAxisPropertyEditInputBehavior& OutBehavior) override;`
- L307 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L314 _public member_ `TObjectPtr<UDataflowEditorWeightMapPaintBrushFilterProperties> FilterProperties;` — `UPROPERTY()` — Filters on paint brush
- L319 _private member_ `TObjectPtr<UDataflowWeightMapPaintBrushOpProps> PaintBrushOpProperties;` — `UPROPERTY()`
- L322 _private member_ `TObjectPtr<UDataflowWeightMapSmoothBrushOpProps> SmoothBrushOpProperties;` — `UPROPERTY()`
- L325 _private member_ `TObjectPtr<UDataflowWeightMapEraseBrushOpProps> EraseBrushOpProperties;` — `UPROPERTY()`
- L328 _public prototype_ `void FloodFillCurrentWeightAction();`
- L329 _public prototype_ `void ClearAllWeightsAction();`
- L330 _public prototype_ `void InvertCurrentWeightAction(bool bInvertSurfaceOnly = true);`
- L332 _public prototype_ `void SetVerticesToWeightMap(const TSet<int32>& Vertices, double WeightValue, bool bIsErase);`
- L334 _public prototype_ `bool HaveVisibilityFilter() const;`
- L335 _public prototype_ `void ApplyVisibilityFilter(const TArray<int32>& Vertices, TArray<int32>& VisibleVertices);`
- L336 _public prototype_ `void ApplyVisibilityFilter(TSet<int32>& Triangles, TArray<int32>& ROIBuffer, TArray<int32>& OutputBuffer);`
- L339 _public prototype_ `virtual void IncreaseBrushRadiusAction();` — we override these so we can update the separate BrushSize property added for this tool
- L340 _public prototype_ `virtual void DecreaseBrushRadiusAction();`
- L341 _public prototype_ `virtual void IncreaseBrushRadiusSmallStepAction();`
- L342 _public prototype_ `virtual void DecreaseBrushRadiusSmallStepAction();`
- L346 _protected function_ `virtual UBaseDynamicMeshComponent* GetSculptMeshComponent()` — UMeshSculptToolBase API
- L347 _protected function_ `virtual FDynamicMesh3* GetBaseMesh()`
- L348 _protected function_ `virtual const FDynamicMesh3* GetBaseMesh() const`
- L350 _protected prototype_ `virtual int32 FindHitSculptMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L351 _protected prototype_ `virtual int32 FindHitTargetMeshTriangleConst(const FRay3d& LocalRay) const override;`
- L352 _protected prototype_ `virtual void UpdateHitSculptMeshTriangle(int32 TriangleID, const FRay3d& LocalRay) override;`
- L354 _protected prototype_ `virtual void OnBeginStroke(const FRay& WorldRay) override;`
- L355 _protected prototype_ `virtual void OnEndStroke() override;`
- L357 _protected prototype_ `virtual TUniquePtr<FMeshSculptBrushOp>& GetActiveBrushOp();`
- L359 _protected function_ `virtual bool SharesBrushPropertiesChanges() const override`
- L369 _public prototype_ `virtual void RequestAction(EDataflowEditorWeightMapPaintToolActions ActionType);`
- L372 _public member_ `TObjectPtr<UDataflowEditorMeshWeightMapPaintToolActions> ActionsProps;` — `UPROPERTY()`
- L375 _public member_ `TObjectPtr<UDataflowEditorUpdateWeightMapProperties> UpdateWeightMapProperties;` — `UPROPERTY()`
- L378 _protected member_ `bool bHavePendingAction = false;`
- L379 _protected member_ `EDataflowEditorWeightMapPaintToolActions PendingAction;`
- L380 _protected prototype_ `virtual void ApplyAction(EDataflowEditorWeightMapPaintToolActions ActionType);`
- L389 _public member_ `TObjectPtr<UPolyLassoMarqueeMechanic> PolyLassoMechanic;` — `UPROPERTY()`
- L392 _protected prototype_ `void OnPolyLassoFinished(const FCameraPolyLasso& Lasso, bool bCanceled);`
- L399 _protected member_ `TObjectPtr<UPolygonSelectionMechanic> PolygonSelectionMechanic;` — `UPROPERTY()` — Gradient Support
- L401 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMeshAABBTree3> MeshSpatial = nullptr;`
- L403 _protected member_ `TUniquePtr<UE::Geometry::FTriangleGroupTopology> GradientSelectionTopology = nullptr;`
- L405 _protected member_ `FToolDataVisualizer GradientSelectionRenderer;`
- L407 _protected member_ `UE::Geometry::FGroupTopologySelection LowValueGradientVertexSelection;`
- L408 _protected member_ `UE::Geometry::FGroupTopologySelection HighValueGradientVertexSelection;`
- L410 _protected prototype_ `void ComputeGradient();`
- L411 _protected prototype_ `void OnSelectionModified();`
- L420 _protected member_ `TObjectPtr<AInternalToolFrameworkActor> PreviewMeshActor = nullptr;` — `UPROPERTY()`
- L423 _protected member_ `TObjectPtr<UDynamicMeshComponent> DynamicMeshComponent = nullptr;` — `UPROPERTY()`
- L426 _protected member_ `TObjectPtr<UMeshElementsVisualizer> MeshElementsDisplay = nullptr;` — `UPROPERTY()`
- L429 _protected member_ `TObjectPtr<UDataflowContextObject> DataflowEditorContextObject = nullptr;` — `UPROPERTY()`
- L432 _protected prototype_ `void OnDynamicMeshComponentChanged(UDynamicMeshComponent* Component, const FMeshVertexChange* Change, bool bRevert);` — realtime visualization
- L433 _protected member_ `FDelegateHandle OnDynamicMeshComponentChangedHandle;`
- L435 _protected member_ `UE::Geometry::FDynamicMeshWeightAttribute* ActiveWeightMap;`
- L436 _protected prototype_ `double GetCurrentWeightValue(int32 VertexId) const;`
- L437 _protected prototype_ `double GetCurrentWeightValueUnderBrush() const;`
- L438 _protected member_ `FVector3d CurrentBaryCentricCoords;`
- L439 _protected prototype_ `int32 GetBrushNearestVertex() const;`
- L441 _protected prototype_ `void GetCurrentWeightMap(TArray<float>& OutWeights) const;`
- L443 _protected prototype_ `void UpdateSubToolType(EDataflowEditorWeightMapPaintInteractionType NewType);`
- L445 _protected prototype_ `void UpdateBrushType(EDataflowEditorWeightMapPaintBrushType BrushType);`
- L447 _protected member_ `TSet<int32> AccumulatedTriangleROI;`
- L448 _protected member_ `bool bUndoUpdatePending = false;`
- L449 _protected member_ `TArray<int> NormalsBuffer;`
- L450 _protected prototype_ `void WaitForPendingUndoRedoUpdate();`
- L452 _protected member_ `TArray<int> TempROIBuffer;`
- L453 _protected member_ `TArray<int> VertexROI;`
- L454 _protected member_ `TArray<bool> VisibilityFilterBuffer;`
- L455 _protected member_ `TSet<int> VertexSetBuffer;`
- L456 _protected member_ `TSet<int> TriangleROI;`
- L457 _protected prototype_ `void UpdateROI(const FSculptBrushStamp& CurrentStamp);`
- L459 _protected member_ `EDataflowEditorWeightMapPaintBrushType PendingStampType = EDataflowEditorWeightMapPaintBrushType::Paint;`
- L461 _protected prototype_ `bool UpdateStampPosition(const FRay& WorldRay);`
- L462 _protected prototype_ `bool ApplyStamp();`
- L464 _protected member_ `UE::Geometry::FDynamicMeshOctree3 Octree;`
- L466 _protected prototype_ `bool UpdateBrushPosition(const FRay& WorldRay);`
- L468 _protected function_ `bool GetInEraseStroke()`
- L475 _protected member_ `bool bPendingPickWeight = false;`
- L477 _protected member_ `TArray<int32> ROITriangleBuffer;`
- L478 _protected member_ `TArray<double> ROIWeightValueBuffer;`
- L479 _protected prototype_ `bool SyncMeshWithWeightBuffer(FDynamicMesh3* Mesh);`
- L480 _protected prototype_ `bool SyncWeightBufferWithMesh(const FDynamicMesh3* Mesh);`
- L482 _protected member_ `TUniquePtr<UE::Geometry::FDynamicMeshChangeTracker> ActiveWeightEditChangeTracker;`
- L483 _protected prototype_ `void BeginChange();`
- L484 _protected prototype_ `void EndChange();`
- L486 _protected prototype_ `FColor GetColorForWeightValue(double WeightValue);`
- L488 _protected member_ `TArray<FVector3d> TriNormals;`
- L489 _protected member_ `TArray<int32> UVSeamEdges;`
- L490 _protected member_ `TArray<int32> NormalSeamEdges;`
- L491 _protected prototype_ `void PrecomputeFilterData();`
- L494 _protected member_ `bool bHaveDynamicMeshToWeightConversion = false;` — DynamicMesh might be unwelded mesh, but weights are on the welded mesh.
- L495 _protected member_ `TArray<int32> DynamicMeshToWeight;`
- L496 _protected member_ `TArray<TArray<int32>> WeightToDynamicMesh;`
- L499 _protected member_ `TArray<float> SetupWeights;` — Setup weights used to store the initial values
- L502 _protected function_ `virtual bool ShowWorkPlane() const override`
- L506 _protected member_ `bool bAnyChangeMade = false;`
- L510 _protected member_ `FDataflowCollectionAddScalarVertexPropertyNode* WeightMapNodeToUpdate = nullptr;`
- L512 _protected prototype_ `void UpdateSelectedNode();`
- L514 _protected prototype_ `void UpdateVertexColorOverlay(const TSet<int>* TrianglesToUpdate = nullptr);`
- L516 _protected member_ `UDataflowEditorMode* Mode = nullptr;`

#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L42 _delegate_ `DECLARE_STATS_GROUP(TEXT("WeightMapPaintTool"), STATGROUP_WeightMapPaintTool,`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowGizmoModeSource.h` (Private)


#### class `UDataflowGizmoModeSource`  
`class UDataflowGizmoModeSource : public UObject, public ITransformGizmoSource`  
_L16-63_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject,ITransformGizmoSource`
- desc: Per-instance ITransformGizmoSource that locks the new editor TRS gizmo to a single EGizmoTransformMode. Used when a Dataflow property opts into a Translate/Rotate/Scale-only gizmo and must not follow the editor mode toolbar.
- L21 _public member_ `EGizmoTransformMode FixedMode = EGizmoTransformMode::Translate;`
- L23 _public function_ `virtual EGizmoTransformMode GetGizmoMode() const override`
- L28 _public function_ `virtual EAxisList::Type GetGizmoAxisToDraw(EGizmoTransformMode InGizmoMode) const override`
- L33 _public function_ `virtual EToolContextCoordinateSystem GetGizmoCoordSystemSpace() const override`
- L38 _public function_ `virtual float GetGizmoScale() const override`
- L43 _public function_ `virtual bool GetVisible(const EViewportContext InViewportContext = EViewportContext::Focused) const override`
- L48 _public function_ `virtual bool CanInteract(const EViewportContext InViewportContext = EViewportContext::Focused) const override`
- L53 _public function_ `virtual EGizmoTransformScaleType GetScaleType() const override`
- L58 _public function_ `virtual const FRotationContext& GetRotationContext() const override`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowMeshSelectionTool.h` (Private)


#### class `UDataflowMeshSelectionToolDataProviderInterface`  
`class UDataflowMeshSelectionToolDataProviderInterface : public UInterface`  
_L26-29_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IDataflowMeshSelectionToolDataProviderInterface`  
`class IDataflowMeshSelectionToolDataProviderInterface`  
_L31-42_
- L36 _public prototype_ `virtual void Init(const UE::Geometry::FDynamicMesh3& Mesh) = 0;`
- L37 _public prototype_ `virtual void Shutdown() = 0;`
- L40 _public prototype_ `virtual void GetVertexSelection(TSet<int32>& OutSelection) const = 0;` — Face and edge selection are infered from the vertex selection
- L41 _public prototype_ `virtual void SetVertexSelection(const TSet<int32>& InSelection) = 0;`

#### class `UDataflowSelectionToolNodeDataProvider`  
`class UDataflowSelectionToolNodeDataProvider : public UObject , public IDataflowMeshSelectionToolDataProviderInterface`  
_L47-67_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IDataflowMeshSelectionToolDataProviderInterface`
- L54 _public prototype_ `void BindToNode(FDataflowSelectionToolNode& InNode, UE::Dataflow::FContext& Context);`
- L57 _public prototype_ `virtual void Init(const UE::Geometry::FDynamicMesh3& Mesh) override;`
- L58 _public prototype_ `virtual void Shutdown() override;`
- L59 _public prototype_ `virtual void GetVertexSelection(TSet<int32>& OutSelection) const override;`
- L60 _public prototype_ `virtual void SetVertexSelection(const TSet<int32>& InSelection) override;`
- L64 _private member_ `TWeakPtr<FDataflowSelectionToolNode> WeakNode;`
- L65 _private member_ `UE::Dataflow::FDynamicMeshMapping MeshMapping;`
- L66 _private member_ `FDataflowSelectionToolNodeData NodeData;`

#### class `UDataflowToolNodeSnapshotProvider`  
`class UDataflowToolNodeSnapshotProvider : public UObject`  
_L72-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L77 _public prototype_ `void BindToNode(FDataflowToolNode& InNode);`
- L79 _public prototype_ `TConstArrayView<FDataflowToolNodeSnapshot> GetSnapshots() const;`
- L80 _public prototype_ `void RemoveSnapshot();`
- L81 _public prototype_ `void MoveSnapshot(int32 FromPosition, int32 ToPosition);`
- L84 _private member_ `TWeakPtr<FDataflowToolNode> WeakNode;`

#### class `UDataflowMeshSelectionToolBuilder`  
`class UDataflowMeshSelectionToolBuilder : public UInteractiveToolWithToolTargetsBuilder, public IDataflowEditorToolBuilder`  
_L97-111_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolWithToolTargetsBuilder,IDataflowEditorToolBuilder`
- L103 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;` — IDataflowEditorToolBuilder
- L104 _private prototype_ `virtual bool CanSceneStateChange(const UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) const override;`
- L105 _private prototype_ `virtual void SceneStateChanged(UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) override;`
- L108 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;` — UInteractiveToolWithToolTargetsBuilder
- L109 _private prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L110 _private prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const override;`

#### class `UDataflowMeshSelectionTool`  
`class UDataflowMeshSelectionTool : public USingleSelectionMeshEditingTool`  
_L114-164_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleSelectionMeshEditingTool`
- L123 _private prototype_ `virtual void Setup() override;`
- L124 _private prototype_ `virtual void OnShutdown(EToolShutdownType ShutdownType) override;`
- L126 _private prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L127 _private prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L128 _private prototype_ `virtual void OnTick(float DeltaTime) override;`
- L130 _private function_ `virtual bool HasCancel() const override`
- L131 _private function_ `virtual bool HasAccept() const override`
- L132 _private prototype_ `virtual bool CanAccept() const override;`
- L136 _private prototype_ `virtual FBox GetWorldSpaceFocusBox() override;`
- L139 _private prototype_ `void OnSelectionModified();`
- L142 _public prototype_ `void NotifyTargetChanged();`
- L145 _public member_ `TObjectPtr<UPreviewMesh> PreviewMesh = nullptr;` — `UPROPERTY()`
- L148 _public member_ `TObjectPtr<UToolMeshSelector> MeshSelector = nullptr;` — `UPROPERTY()`
- L151 _public member_ `TScriptInterface<IDataflowMeshSelectionToolDataProviderInterface> DataProvider = nullptr;` — `UPROPERTY(Transient)`
- L154 _private prototype_ `void InitializeSculptMeshFromTarget();`
- L155 _private prototype_ `void InitializeMeshSelector();`
- L157 _private prototype_ `void LoadFromDataProvider();`
- L158 _private prototype_ `void SaveToDataProvider();`
- L160 _private prototype_ `void ConvertFaceToVertexSelection();`
- L161 _private prototype_ `void ConvertVertexToFaceSelection();`
- L163 _private member_ `bool bAnyChangeMade = false;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Dataflow` (scope `UE`)
- L91 _namespace_ `namespace UE`
- L91 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowEditorTools/DataflowPropertyGizmoManager.h` (Private)


#### class `UDataflowPropertyGizmoManager`  
`class UDataflowPropertyGizmoManager : public UObject`  
_L39-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Manages viewport gizmos for UPROPERTY-annotated properties on a selected dataflow node. Node authors opt in by adding meta=(GizmoType="Translate"|"Rotate"|"Scale"|"Transform") to a UPROPERTY. When a node is selected in the graph, Setup() creates one gizmo per annotated property. Gizmo manipulations write back to the node property and invalidate the node for re-evaluation. Example usage in a node struct: UPROPERTY(EditAnywhere, Category="Transform", meta=(GizmoType="Translate")) FVector Origin = FVector::ZeroVector; UPROPERTY(EditAnywhere, Category="Transform", meta=(GizmoType="Rotate")) FQuat Orientation = FQuat::Identity;
- L55 _public prototype_ `void Setup(UInteractiveToolManager* ToolManager, UDataflowEdNode* EdNode);` — Create gizmos for all GizmoType-annotated properties on the given node. Call when a node is selected.
- L58 _public prototype_ `void Teardown(UInteractiveToolManager* ToolManager);` — Destroy all active gizmos. Call when the node is deselected or the editor closes.
- L62 _public prototype_ `void SyncGizmosFromNodeProperties();` — Sync gizmo world transforms to match the current node property values. Call after an external property edit (e.g. via the details panel).
- L64 _public function_ `bool HasActiveGizmos() const`
- L67 _public prototype_ `void DrawPropertyLabels(FCanvas* Canvas, const FSceneView* SceneView) const;` — Draw the property name as a text overlay at each gizmo's world-space origin. Call from viewport DrawCanvas.
- L80 _private prototype_ `FTransform ReadPropertyAsTransform(const FPropertyGizmoEntry& Entry, const void* NodeMemory) const;`
- L81 _private prototype_ `FTransform ReadPropertyAsTransform(const FProperty* Property, const EGizmoType GizmoType, const void* NodeMemory) const;`
- L82 _private prototype_ `void WriteTransformToProperty(const FPropertyGizmoEntry& Entry, void* NodeMemory, const FTransform& NewTransform) const;`
- L84 _private prototype_ `void RefreshGizmo(const FPropertyGizmoEntry& Entry, const TSharedPtr<const FDataflowNode>& Node);`
- L86 _private prototype_ `static EGizmoType GizmoTypeFromString(const FString& GizmoTypeStr);`
- L87 _private prototype_ `static ETransformGizmoSubElements GizmoTypeToSubElements(const EGizmoType GizmoTypeStr);`
- L88 _private prototype_ `static EGizmoTransformMode GizmoTypeToTransformMode(const EGizmoType GizmoType);`
- L89 _private prototype_ `static bool IsPropertyEditable(const FDataflowNode& DataflowNode, const FProperty& Property);`
- L91 _private prototype_ `void OnEndTransformEdit(UTransformProxy* Proxy);`
- L93 _private member_ `TArray<FPropertyGizmoEntry> PropertyEntries;`
- L96 _private member_ `TArray<TObjectPtr<UTransformProxy>> TransformProxies;` — `UPROPERTY(Transient)`
- L99 _private member_ `TArray<TObjectPtr<UCombinedTransformGizmo>> TransformGizmos;` — `UPROPERTY(Transient)`
- L102 _private member_ `TArray<TObjectPtr<UTransformGizmo>> TRSGizmos;` — `UPROPERTY(Transient)`
- L105 _private member_ `TArray<TObjectPtr<UDataflowGizmoModeSource>> GizmoModeSources;` — `UPROPERTY(Transient)`
- L107 _private member_ `TWeakObjectPtr<UDataflowEdNode> TrackedEdNode;`

#### enum `UDataflowPropertyGizmoManager::EGizmoType`  
`enum class EGizmoType`  
_L43-50_
- L45 _public enumerator_ `None`
- L46 _public enumerator_ `Translate`
- L47 _public enumerator_ `Rotate`
- L48 _public enumerator_ `Scale`
- L49 _public enumerator_ `Transform`

#### struct `UDataflowPropertyGizmoManager::FPropertyGizmoEntry`  
`struct FPropertyGizmoEntry`  
_L72-78_
- desc: Parallel-array entry tying a reflected property to its gizmo/proxy indices.
- L74 _public member_ `EGizmoType GizmoType = EGizmoType::None;`
- L75 _public member_ `FProperty* Property = nullptr;`
- L76 _public member_ `FProperty* PositionProperty = nullptr;`
- L77 _public member_ `int32 ArrayIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowBoxRenderableType.h` (Private)


#### class `UDataflowBoxRenderSettings`  
`class UDataflowBoxRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _public member_ `FDataflowSimpleColorCommonRenderSettings ColorSettings;` — `UPROPERTY(EditAnywhere, Category = "Surface", meta = (ShowOnlyInnerProperties))`

#### class `UDataflowBoxArrayRenderSettings`  
`class UDataflowBoxArrayRenderSettings : public UDataflowRenderableTypeSettings`  
_L21-28_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "Surface|ConstantColor, Surface|RandomColor, Surface|ColorBySize")`
- inherits: `UDataflowRenderableTypeSettings`
- L27 _public member_ `FDataflowColorCommonRenderSettings ColorSettings;` — `UPROPERTY(EditAnywhere, Category = "Surface", meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Dataflow` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L32 _prototype_ `void RegisterBoxRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowDebugMeshRenderableType.h` (Private)


#### struct `FDataflowDebugMeshRenderElementSettings`  
`struct FDataflowDebugMeshRenderElementSettings`  
_L14-41_
- reflection: `USTRUCT()`
- L20 _public member_ `bool bShowIDs = false;` — `UPROPERTY(EditAnywhere, Category = "IDs", meta = (InlineEditConditionToggle))` — Show Ids
- L24 _public member_ `FColor IDsColor = FColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "IDs", meta = (EditCondition = bShowIDs))` — Color of the IDs text
- L28 _public member_ `bool bShowNormals = false;` — `UPROPERTY(EditAnywhere, Category = "Normals")` — Show normals
- L32 _public member_ `float NormalsLength = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Normals", meta = (EditCondition = bShowNormals, Units = cm))` — Length of the normals
- L36 _public member_ `float NormalsThickness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Normals", meta = (EditCondition = bShowNormals))` — Thickness of the normals
- L40 _public member_ `FColor NormalsColor = FColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Normals", meta = (EditCondition = bShowNormals))` — Color of the Normals

#### struct `FDataflowDebugMeshUVSettings`  
`struct FDataflowDebugMeshUVSettings`  
_L44-75_
- reflection: `USTRUCT()`
- L50 _public member_ `bool bShowUVs = false;` — `UPROPERTY(EditAnywhere, Category = "UVs")` — Show UVs
- L54 _public member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (UIMin = 0, UIClampMin = 0, UIMax = 7, UIClampMax = 7, EditCondition = bShowUVs))` — UV channel index
- L58 _public member_ `FColor UVColor = FColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (EditCondition = bShowUVs))` — Color of the UVs text
- L62 _public member_ `bool bUseUVMaterial = false;` — `UPROPERTY(EditAnywhere, Category = "Material")` — Assign UV material
- L66 _public member_ `TObjectPtr<UMaterialInterface> UVMaterial = nullptr;` — `UPROPERTY(VisibleAnywhere, Category = "Material")` — Material for meshes to display UVs
- L70 _public member_ `bool bColorUVIslands = false;` — `UPROPERTY(EditAnywhere, Category = "UV Islands")` — Color UV islands
- L74 _public member_ `int32 ColorRandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "UV Islands")` — Color UV islands

#### class `UDataflowDebugMeshRenderSettings`  
`class UDataflowDebugMeshRenderSettings : public UDataflowRenderableTypeSettings`  
_L78-93_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "MeshDebug")`
- inherits: `UDataflowRenderableTypeSettings`
- L82 _private prototype_ `UDataflowDebugMeshRenderSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L86 _public member_ `FDataflowDebugMeshRenderElementSettings VertexSettings;` — `UPROPERTY(EditAnywhere, Category = "MeshDebug")`
- L89 _public member_ `FDataflowDebugMeshRenderElementSettings FaceSettings;` — `UPROPERTY(EditAnywhere, Category = "MeshDebug")`
- L92 _public member_ `FDataflowDebugMeshUVSettings UVSettings;` — `UPROPERTY(EditAnywhere, Category = "MeshDebug", DisplayName="UV Settings")`

#### Free symbols / members of external scopes

- L95 _namespace_ `namespace UE`
- L95 _namespace_ `namespace Dataflow` (scope `UE`)
- L99 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L101 _prototype_ `void AddDebugComponents(FRenderableComponents& OutComponents, const UDataflowDebugMeshRenderSettings& Settings);` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowDynamicMeshRenderableType.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L7 _prototype_ `void RegisterDynamicMeshRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowGeometryCollectionProximityRenderableType.h` (Private)


#### class `UDataflowGeometryCollectionProximityRenderSettings`  
`class UDataflowGeometryCollectionProximityRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-32_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories="Proximity|Centers, Proximity|Connections")`
- inherits: `UDataflowRenderableTypeSettings`
- L16 _public member_ `bool bShowCenters = true;` — `UPROPERTY(EditAnywhere, Category = "Proximity|Centers")`
- L19 _public member_ `float PointSize = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Proximity|Centers")`
- L22 _public member_ `FColor PointColor = FColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Proximity|Centers")`
- L25 _public member_ `bool bShowConnections = true;` — `UPROPERTY(EditAnywhere, Category = "Proximity|Connections")`
- L28 _public member_ `float LineThickness = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Proximity|Connections")`
- L31 _public member_ `FColor LineColor = FColor::Yellow;` — `UPROPERTY(EditAnywhere, Category = "Proximity|Connections")`

#### Free symbols / members of external scopes

- L34 _namespace_ `namespace UE`
- L34 _namespace_ `namespace Dataflow` (scope `UE`)
- L34 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L36 _prototype_ `void RegisterGeometryCollectionProximityRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowGeometryCollectionRenderableType.h` (Private)


#### class `UDataflowGeometryCollectionSurfaceRenderSettings`  
`class UDataflowGeometryCollectionSurfaceRenderSettings : public UDataflowRenderableTypeSettings`  
_L16-57_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "Surface|Selection, Surface|Attribute, Surface|Curves")`
- inherits: `UDataflowRenderableTypeSettings`
- L20 _private prototype_ `UDataflowGeometryCollectionSurfaceRenderSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _public member_ `bool bShowSelection = true;` — `UPROPERTY(EditAnywhere, Category = "Surface|Selection")` — Show selected transforms when relevant to the selected node
- L29 _public member_ `TObjectPtr<UMaterialInterface> SelectionMaterial = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Surface|Selection", meta = (EditCondition = bShowSelection))` — Material used to display the transform selection
- L33 _public member_ `bool bShowVertexAttributeAsVertexColor = true;` — `UPROPERTY(EditAnywhere, Category = "Surface|Attribute")` — Show vertex attribute if available from the node or the override below
- L37 _public member_ `bool bUseVertexAttributeOverride = false;` — `UPROPERTY(EditAnywhere, Category = "Surface|Attribute", meta = (InlineEditConditionToggle, EditCondition = bShowVertexAttributeAsVertexColor))` — control whether the attribute override shoudl be used or not
- L41 _public member_ `FString VertexAttributeOverride;` — `UPROPERTY(EditAnywhere, Category = "Surface|Attribute", meta = (EditCondition = bUseVertexAttributeOverride))` — Vertex attribute to display - if not empty this will override any attribute displayed for the node
- L45 _public member_ `bool bUseColorRamp = false;` — `UPROPERTY(EditAnywhere, Category = "Surface|Attribute", meta = (EditCondition = bShowVertexAttributeAsVertexColor))` — If true use the color ramp to color vertices from the attribute
- L49 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Surface|Attribute", meta = (EditCondition = "bShowVertexAttributeAsVertexColor && bUseColorRamp"))` — Color ramp to use to display an single value attribute - ignored for vector based attributes
- L53 _public member_ `int32 MaxCurveVertices = 50000;` — `UPROPERTY(EditAnywhere, Category = "Surface|Curves")` — Maxmimum number of vertixes to render for curves (used for groom) , negative number to not cull any curves
- L56 _public prototype_ `const int32 GetHashFromProperties() const ;`

#### class `UDataflowExplodedViewRenderSettings`  
`class UDataflowExplodedViewRenderSettings : public UDataflowRenderableTypeSettings`  
_L60-81_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "ExplodedView")`
- inherits: `UDataflowRenderableTypeSettings`
- L67 _public member_ `bool bExplodedView = false;` — `UPROPERTY(EditAnywhere, Category = "ExplodedView")` — Apply exploded view to pieces
- L71 _public member_ `float Amount = 1.f;` — `UPROPERTY(EditAnywhere, Category = "ExplodedView", meta = (EditCondition = bExplodedView))` — Amount for the exploded view
- L75 _public member_ `FVector CenterOffset = FVector::ZeroVector;` — `UPROPERTY(EditAnywhere, Category = "ExplodedView", meta = (EditCondition = bExplodedView))` — Offset to the center of the exploded view
- L77 _public prototype_ `FVector ComputeExplodedVector(const FVector& Point, const FVector& Center) const;`
- L78 _public prototype_ `void ComputePerTransformExplodedVectors(const FManagedArrayCollection& Collection, TArray<FVector>& OutExplodedVectors) const;`
- L79 _public prototype_ `void ComputePerTransformExplodedVectors(const GeometryCollection::Facades::FBoundsFacade& BoundsFacade, TArray<FVector>& OutExplodedVectors) const;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace GeometryCollection`
- L13 _namespace_ `namespace Facades` (scope `GeometryCollection`)
- L83 _namespace_ `namespace UE`
- L83 _namespace_ `namespace Dataflow` (scope `UE`)
- L83 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L85 _prototype_ `void RegisterGeometryCollectionRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowMaterialRenderableType.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L7 _prototype_ `void RegisterMaterialRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowPhysicsAssetRenderableType.h` (Private)


#### class `UDataflowPhysicsAssetRenderSettings`  
`class UDataflowPhysicsAssetRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowRenderableTypeSettings`
- L15 _private prototype_ `UDataflowPhysicsAssetRenderSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L19 _public member_ `FDataflowSimpleColorCommonRenderSettings ColorSettings;` — `UPROPERTY(EditAnywhere, Category = "Surface", meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Dataflow` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L24 _prototype_ `void RegisterPhysicsAssetRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowPlaneRenderableType.h` (Private)


#### class `UDataflowPlaneRenderSettings`  
`class UDataflowPlaneRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-26_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _public member_ `FDataflowSimpleColorCommonRenderSettings ColorSettings;` — `UPROPERTY(EditAnywhere, Category = "Surface", meta = (ShowOnlyInnerProperties))`
- L21 _public member_ `float NormalScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Plane", meta = (UIMin = "1.0", UIMax = "10.0", ClampMin = "1.0", ClampMax = "10.0"))` — Length scalar for the normal
- L25 _public member_ `float PlaneScale = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Plane", meta = (UIMin = "1.0", UIMax = "10.0", ClampMin = "1.0", ClampMax = "10.0"))` — Plane size scalar

#### Free symbols / members of external scopes

- L28 _namespace_ `namespace UE`
- L28 _namespace_ `namespace Dataflow` (scope `UE`)
- L28 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L30 _prototype_ `void RegisterPlaneRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowPointArrayRenderableType.h` (Private)


#### class `UDataflowPointArrayRenderSettings`  
`class UDataflowPointArrayRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-20_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "")`
- inherits: `UDataflowRenderableTypeSettings`
- L16 _public member_ `float Size = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Point")`
- L19 _public member_ `FColor Color = FColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "Point")`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Dataflow` (scope `UE`)
- L22 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L24 _prototype_ `void RegisterPointArrayRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowPointRenderableType.h` (Private)


#### class `UDataflowPointRenderSettings`  
`class UDataflowPointRenderSettings : public UDataflowRenderableTypeSettings`  
_L13-85_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "")`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _private prototype_ `UDataflowPointRenderSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L22 _public member_ `bool bRenderPoints = true;` — `UPROPERTY(EditAnywhere, Category = "Point")` — Disable rendring the points
- L26 _public member_ `float Size = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Point", meta = (UIMin = 0.01f, ClampMin = 0.01f))` — Size of displayed points
- L30 _public member_ `FColor Color = FLinearColor(0.16f, 0.184f, 0.48f, 1.0f).ToFColor(true);` — `UPROPERTY(EditAnywhere, Category = "Point")` — Color of displayed points
- L34 _public member_ `bool bShowPointIDs = false;` — `UPROPERTY(EditAnywhere, Category = "Point", meta = (InlineEditConditionToggle))` — SHow the points IDs
- L38 _public member_ `FColor IDsColor = FColor::Cyan;` — `UPROPERTY(EditAnywhere, Category = "Point", meta = (EditCondition = bShowPointIDs))` — Color of the IDs text
- L42 _public member_ `bool bShowPositions = false;` — `UPROPERTY(EditAnywhere, Category = "Point", meta = (InlineEditConditionToggle))` — SHow the points positions
- L46 _public member_ `FColor PositionsColor = FColor::White;` — `UPROPERTY(EditAnywhere, Category = "Point", meta = (EditCondition = bShowPositions))` — Color of the poaition text
- L50 _public member_ `FString Attribute = FString("Dum` — `UPROPERTY(EditAnywhere, Category = "Point")` — Attribute on points to color the displayed points (Supported types: float, bool, int32, Vector3f
- L54 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Point")` — Attribute minimum value for coloring (This value represents the minimum color on the color ramp
- L58 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Point")` — Attribute maximum value for coloring (This value represents the maximum color on the color ramp
- L62 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Point")` — Color ramp to use to display a single value attribute - ignored for vector attributes
- L66 _public member_ `bool bRenderAsRGB = false;` — `UPROPERTY(EditAnywhere, Category = "Vector")` — Render vector data as RGB colors
- L69 _public member_ `float LineThickness = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (UIMin = 0.01f, ClampMin = 0.01f, EditCondition = "!bRenderAsRGB"))`
- L72 _public member_ `float LengthScalar = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (UIMin = 0.01f, ClampMin = 0.01f, EditCondition = "!bRenderAsRGB"))`
- L76 _public member_ `float LengthMin = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (UIMin = 0.01f, ClampMin = 0.01f, EditCondition = "!bRenderAsRGB"))` — Attribute minimum value for coloring (This value represents the minimum color on the color ramp
- L80 _public member_ `float LengthMax = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (EditCondition = "!bRenderAsRGB"))` — Attribute maximum value for coloring (This value represents the maximum color on the color ramp
- L84 _public member_ `FLinearColorRamp LengthColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Vector", meta = (EditCondition = "!bRenderAsRGB"))` — Color ramp to use to display a vector value attribute length - ignored for scalar attributes

#### Free symbols / members of external scopes

- L87 _namespace_ `namespace UE`
- L87 _namespace_ `namespace Dataflow` (scope `UE`)
- L87 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L89 _prototype_ `void RegisterPointRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowSamplerRenderableType.h` (Private)


#### enum `EDataflowSlicePlane`  
`enum class EDataflowSlicePlane : uint8`  
_L13-18_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `XYPlane UMETA(DisplayName = "XY Plane")`
- L16 _public enumerator_ `YZPlane UMETA(DisplayName = "YZ Plane")`
- L17 _public enumerator_ `ZXPlane UMETA(DisplayName = "ZX Plane")`

#### class `UDataflowFloatSamplerRenderSettings`  
`class UDataflowFloatSamplerRenderSettings : public UDataflowRenderableTypeSettings`  
_L21-67_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "")`
- inherits: `UDataflowRenderableTypeSettings`
- L25 _private prototype_ `UDataflowFloatSamplerRenderSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L30 _public member_ `bool bOverrideBounds = false;` — `UPROPERTY(EditAnywhere, Category = "Render Bounds")` — Override the sampler's specified render bounds and use the Center end Extent instead
- L34 _public member_ `FVector Center = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Render Bounds", meta = (EditCondition = bOverrideBounds))` — Center of the render bounds
- L38 _public member_ `FVector Extent = FVector(50.0f);` — `UPROPERTY(EditAnywhere, Category = "Render Bounds", meta = (UIMin = 0.01f, ClampMin = 0.01f, EditCondition = bOverrideBounds))` — Extent of the render bounds
- L42 _public member_ `EDataflowSlicePlane Plane = EDataflowSlicePlane::XYPlane;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings")` — Plane orientation for the visualization
- L46 _public member_ `float PointSeparation = 2.f;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings", meta = (UIMin = 0.01f, ClampMin = 0.01f))` — Distance between the displayed points on the plane
- L50 _public member_ `float Offset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings", meta = (ClampMin = "-1", ClampMax = "1"))` — Relative offset of the plane inside the render bounds. The offset is beetween -1 and 1
- L54 _public member_ `float Size = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Points", meta = (UIMin = 0.01f, ClampMin = 0.01f))` — Size of the displayed points
- L58 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Attribute minimum value for coloring. This value represents the minimum color on the color ramp
- L62 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Attribute maximum value for coloring. This value represents the maximum color on the color ramp
- L66 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Color ramp specifiyng the color for displayed points using a single value attribute

#### class `UDataflowVectorSamplerRenderSettings`  
`class UDataflowVectorSamplerRenderSettings : public UDataflowRenderableTypeSettings`  
_L71-125_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "")`
- inherits: `UDataflowRenderableTypeSettings`
- L75 _private prototype_ `UDataflowVectorSamplerRenderSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L80 _public member_ `bool bOverrideBounds = false;` — `UPROPERTY(EditAnywhere, Category = "Render Bounds")` — Override the sampler's specified render bounds and use the Center end Extent instead
- L84 _public member_ `FVector Center = FVector(0.f);` — `UPROPERTY(EditAnywhere, Category = "Render Bounds", meta = (EditCondition = bOverrideBounds))` — Center of the render bounds
- L88 _public member_ `FVector Extent = FVector(50.0f);` — `UPROPERTY(EditAnywhere, Category = "Render Bounds", meta = (UIMin = 0.01f, ClampMin = 0.01f, EditCondition = bOverrideBounds))` — Extent of the render bounds
- L92 _public member_ `EDataflowSlicePlane Plane = EDataflowSlicePlane::XYPlane;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings")` — Plane orientation for the visualization
- L96 _public member_ `float Delta = 5.f;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings", meta = (UIMin = 0.01f, ClampMin = 0.01f))` — Distance between the displayed points on the plane
- L100 _public member_ `float Offset = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Slice Settings", meta = (ClampMin = "-1", ClampMax = "1"))` — Relative offset of the plane inside the render bounds. The offset is beetween -1 and 1
- L104 _public member_ `float Size = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Points", meta = (UIMin = 0.01f, ClampMin = 0.01f))` — Size of displayed points
- L108 _public member_ `float LengthScalar = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Vectors")` — Scalar applied to the vectors
- L112 _public member_ `float LineThickness = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Vectors")` — Line thickness of the displayed vectors
- L116 _public member_ `float Min = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Attribute minimum value for coloring. This value represents the minimum color on the color ramp
- L120 _public member_ `float Max = 1.f;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Attribute maximum value for coloring. This value represents the maximum color on the color ramp
- L124 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Color ramp specifiyng the color for displayed points and vectors using a the length of the vector attribute

#### Free symbols / members of external scopes

- L129 _namespace_ `namespace UE`
- L129 _namespace_ `namespace Dataflow` (scope `UE`)
- L129 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L131 _prototype_ `void RegisterSamplerRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowSkeletalMeshRenderableType.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L7 _prototype_ `void RegisterSkeletalMeshRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowSphereRenderableType.h` (Private)


#### class `UDataflowSphereRenderSettings`  
`class UDataflowSphereRenderSettings : public UDataflowRenderableTypeSettings`  
_L11-18_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowRenderableTypeSettings`
- L17 _public member_ `FDataflowSimpleColorCommonRenderSettings ColorSettings;` — `UPROPERTY(EditAnywhere, Category = "Surface", meta = (ShowOnlyInnerProperties))`

#### class `UDataflowSphereArrayRenderSettings`  
`class UDataflowSphereArrayRenderSettings : public UDataflowRenderableTypeSettings`  
_L21-28_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "Surface|ConstantColor, Surface|RandomColor, Surface|ColorBySize")`
- inherits: `UDataflowRenderableTypeSettings`
- L27 _public member_ `FDataflowColorCommonRenderSettings ColorSettings;` — `UPROPERTY(EditAnywhere, Category = "Surface", meta = (ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Dataflow` (scope `UE`)
- L30 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L32 _prototype_ `void RegisterSphereRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowStaticMeshRenderableType.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L7 _prototype_ `void RegisterStaticMeshRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/DataflowRendering/DataflowTextureRenderableType.h` (Private)


#### Free symbols / members of external scopes

- L5 _namespace_ `namespace UE`
- L5 _namespace_ `namespace Dataflow` (scope `UE`)
- L5 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L7 _prototype_ `void RegisterTextureRenderableTypes();` (scope `UE::Dataflow::Private`)

### `Plugins/Dataflow/Source/DataflowEditor/Private/Widgets/DataflowSimulationBinding.h` (Private)


#### class `FDataflowSimulationBinding`  
`class FDataflowSimulationBinding : public TSharedFromThis<FDataflowSimulationBinding>`  
_L13-94_
- inherits: `TSharedFromThis<FDataflowSimulationBinding>`
- desc: Dataflow binding to centralize the bridge in between the timeline widget and the dataflow simulation scene
- L16 _public prototype_ `FDataflowSimulationBinding(const TWeakPtr<FDataflowSimulationScene>& InSimulationScene);`
- L17 _public prototype_ `~FDataflowSimulationBinding();`
- L20 _public function_ `TWeakPtr<FDataflowSimulationScene> GetSimulationScene() const` — Get the simulation scene from the binding
- L23 _public prototype_ `FFrameRate GetFrameRate() const;` — Get the framerate specified by the anim sequence
- L26 _public prototype_ `int32 GetTickResolution() const;` — Get the tick resolution we are displaying at
- L29 _public prototype_ `FAnimatedRange GetViewRange() const;` — Get the current view range
- L32 _public prototype_ `void SetViewRange(TRange<double> InRange);` — Set the current view range
- L35 _public prototype_ `FAnimatedRange GetWorkingRange() const;` — Get the working range of the model's data
- L38 _public prototype_ `TRange<FFrameNumber> GetPlaybackRange() const;` — Get the playback range of the model's data
- L41 _public prototype_ `void SetPlaybackRange(const TRange<FFrameNumber>& NewRange);` — Set the playback range
- L44 _public prototype_ `FFrameNumber GetScrubPosition() const;` — Get the current scrub position
- L47 _public prototype_ `float GetScrubTime() const;` — Get the current scrub time
- L50 _public prototype_ `void SetScrubTime(const float NewScrubTime);` — Set the current scrub time
- L53 _public prototype_ `float GetDeltaTime() const;` — Get the simulation delta time
- L56 _public prototype_ `float GetSequenceLength() const;` — Get the simulation sequence length
- L59 _public prototype_ `void SetScrubPosition(FFrameTime NewScrubPostion) const;` — Set the current scrub position
- L62 _public prototype_ `void HandleViewRangeChanged(TRange<double> InRange, EViewRangeInterpolation InInterpolation);` — Handle the view range being changed
- L65 _public prototype_ `void HandleWorkingRangeChanged(TRange<double> InRange);` — Handle the working range being changed
- L68 _public prototype_ `void RecordSimulationCache();` — Handle the recording of the simulation cache
- L71 _public prototype_ `void ResetSimulationScene();` — Handle the reset of the simulation scene
- L74 _public prototype_ `bool IsSimulationLocked() const;` — Get the locked simulation flag
- L77 _public prototype_ `void SetSimulationLocked(const bool bIsSimulaitonLocked);` — Set the locked simulation flag
- L80 _public prototype_ `void FillCacheNames(TArray<FString>& CacheNames) const;` — Retrieve all the cache names
- L84 _private prototype_ `void OnSceneTimeRangeUpdated(const FDataflowSimulationScene& Scene);`
- L87 _private member_ `TWeakPtr<FDataflowSimulationScene> SimulationScene;` — Simulation scene to be used for the widget
- L90 _private member_ `FAnimatedRange ViewRange;` — View simulation range
- L93 _private member_ `FAnimatedRange WorkingRange;` — Working simulation range

### `Plugins/Dataflow/Source/DataflowEditor/Private/Widgets/DataflowTimeSliderController.h` (Private)


#### class `FDataflowTimeSliderController`  
`class FDataflowTimeSliderController : public ITimeSliderController, public TSharedFromThis<FDataflowTimeSliderController>`  
_L15-188_
- inherits: `ITimeSliderController,TSharedFromThis<FDataflowTimeSliderController>`
- L21 _public prototype_ `FDataflowTimeSliderController(const FTimeSliderArgs& InArgs, TWeakPtr<SDataflowSimulationTimeline> DataflowSimulationTimeline);`
- L22 _public prototype_ `~FDataflowTimeSliderController();`
- L25 _public prototype_ `virtual int32 OnPaintTimeSlider(bool bMirrorLabels, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L26 _public prototype_ `virtual int32 OnPaintViewArea(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, bool bEnabled, const FPaintViewAreaArgs& Args) const override;`
- L27 _public prototype_ `virtual FReply OnMouseButtonDown(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L28 _public prototype_ `virtual FReply OnMouseButtonUp(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L29 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(SWidget& OwnerWidget, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L30 _public prototype_ `virtual FReply OnMouseMove(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L31 _public prototype_ `virtual FReply OnMouseWheel(SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L32 _public prototype_ `virtual FCursorReply OnCursorQuery(const SWidget& WidgetOwner, const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;`
- L33 _public prototype_ `virtual void SetViewRange(double NewRangeMin, double NewRangeMax, EViewRangeInterpolation Interpolation) override;`
- L34 _public prototype_ `virtual void SetClampRange(double NewRangeMin, double NewRangeMax) override;`
- L35 _public prototype_ `virtual void SetPlayRange(FFrameNumber RangeStart, int32 RangeDuration) override;`
- L36 _public function_ `virtual FFrameRate GetDisplayRate() const override`
- L37 _public function_ `virtual FFrameRate GetTickResolution() const override`
- L38 _public function_ `virtual FAnimatedRange GetViewRange() const override`
- L39 _public function_ `virtual FAnimatedRange GetClampRange() const override`
- L40 _public function_ `virtual TRange<FFrameNumber> GetPlayRange() const override`
- L41 _public function_ `virtual FFrameTime GetScrubPosition() const`
- L42 _public function_ `virtual void SetScrubPosition(FFrameTime InTime, bool bEvaluate)`
- L51 _public prototype_ `void ClampViewRange(double& NewRangeMin, double& NewRangeMax);` — Clamp the given range to the clamp range @param NewRangeMin		The new lower bound of the range @param NewRangeMax		The new upper bound of the range
- L59 _public prototype_ `bool ZoomByDelta(float InDelta, float MousePositionFraction = 0.5f);` — Zoom the range by a given delta. @param InDelta					The total amount to zoom by (+ve = zoom out, -ve = zoom in) @param MousePositionFraction		Bias to apply to lower/upper extents of the range. (0 = lower, 0.5 = equal, 1 = upper)
- L66 _public prototype_ `void PanByDelta(float InDelta);` — Pan the range by a given delta @param InDelta		The total amount to pan by (+ve = pan forwards in time, -ve = pan backwards in time)
- L69 _public prototype_ `FFrameTime GetFrameTimeFromMouse(const FGeometry& Geometry, FVector2D ScreenSpacePosition) const;` — Determine frame time from a mouse position
- L78 _private prototype_ `void CommitScrubPosition(FFrameTime NewValue, bool bIsScrubbing);` — Call this method when the user's interaction has changed the scrub position @param NewValue				Value resulting from the user's interaction @param bIsScrubbing			True if done via scrubbing, false if just releasing scrubbing
- L88 _private prototype_ `void DrawTicks(FSlateWindowElementList& OutDrawElements, const TRange<double>& ViewRange, const FScrubRangeToScreen& RangeToScreen, FDrawTickArgs& InArgs) const;` — Draw time tick marks @param OutDrawElements	List to add draw elements to @param ViewRange			The currently visible time range in seconds @param RangeToScreen		Time range to screen space converter @param InArgs			Parameters for drawing the tick lines
- L95 _private prototype_ `int32 DrawSelectionRange(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen, const FPaintPlaybackRangeArgs& Args) const;` — Draw the selection range. @return The new layer ID.
- L102 _private prototype_ `int32 DrawPlaybackRange(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FScrubRangeToScreen& RangeToScreen, const FPaintPlaybackRangeArgs& Args) const;` — Draw the playback range. @return the new layer ID
- L105 _private prototype_ `bool HitTestRangeStart(const FScrubRangeToScreen& RangeToScreen, const TRange<double>& Range, float HitPixel) const;` — Hit test the lower bound of a range
- L108 _private prototype_ `bool HitTestRangeEnd(const FScrubRangeToScreen& RangeToScreen, const TRange<double>& Range, float HitPixel) const;` — Hit test the upper bound of a range
- L111 _private prototype_ `void SetPlaybackRangeStart(FFrameNumber NewStart);` — Set the playback range start
- L114 _private prototype_ `void SetPlaybackRangeEnd(FFrameNumber NewEnd);` — Set the playback range end
- L117 _private prototype_ `void SetSelectionRangeStart(FFrameNumber NewStart);` — Set the selection range start
- L120 _private prototype_ `void SetSelectionRangeEnd(FFrameNumber NewEnd);` — Set the selection range end
- L122 _private prototype_ `FFrameTime ComputeFrameTimeFromMouse(const FGeometry& Geometry, FVector2D ScreenSpacePosition, FScrubRangeToScreen RangeToScreen, bool CheckSnapping = true) const;`
- L132 _private prototype_ `FScrubPixelRange GetHitTestScrubberPixelRange(FFrameTime ScrubTime, const FScrubRangeToScreen& RangeToScreen) const;`
- L133 _private prototype_ `FScrubPixelRange GetScrubberPixelRange(FFrameTime ScrubTime, const FScrubRangeToScreen& RangeToScreen) const;`
- L134 _private prototype_ `FScrubPixelRange GetScrubberPixelRange(FFrameTime ScrubTime, FFrameRate Resolution, FFrameRate PlayRate, const FScrubRangeToScreen& RangeToScreen, float DilationPixels = 0.f) const;`
- L137 _private member_ `FTimeSliderArgs TimeSliderArgs;` — Time Slider args
- L140 _private member_ `TWeakPtr<SDataflowSimulationTimeline> SimulationTimeline;` — Pointer back to the timeline
- L143 _private member_ `const FSlateBrush* ScrubFillBrush;` — Brush for drawing the fill area on the scrubber
- L146 _private member_ `const FSlateBrush* ScrubHandleUpBrush;` — Brush for drawing an upwards facing scrub handles
- L149 _private member_ `const FSlateBrush* ScrubHandleDownBrush;` — Brush for drawing a downwards facing scrub handle
- L152 _private member_ `const FSlateBrush* EditableTimeBrush;` — Brush for drawing an editable time
- L156 _private member_ `float DistanceDragged;` — Total mouse delta during dragging
- L171 _private member_ `DragType MouseDragType;`
- L174 _private member_ `bool bPanning;` — If we are currently panning the panel
- L177 _private member_ `int32 DraggedTimeIndex;` — Index of the current dragged time
- L180 _private member_ `FVector2D MouseDownPosition[2];` — Mouse down position range
- L183 _private member_ `FGeometry MouseDownGeometry;` — Geometry on mouse down
- L186 _private member_ `TArray<TRange<double>> ViewRangeStack;` — Range stack

#### struct `FDataflowTimeSliderController::FScrubPixelRange`  
`struct FScrubPixelRange`  
_L125-130_
- L127 _public member_ `TRange<float> Range;`
- L128 _public member_ `TRange<float> HandleRange;`
- L129 _public member_ `bool bClamped;`

#### enum `FDataflowTimeSliderController::DragType`  
`enum DragType`  
_L159-169_
- desc: If we are dragging a scrubber or dragging to set the time range
- L161 _public enumerator_ `DRAG_SCRUBBING_TIME`
- L162 _public enumerator_ `DRAG_SETTING_RANGE`
- L163 _public enumerator_ `DRAG_PLAYBACK_START`
- L164 _public enumerator_ `DRAG_PLAYBACK_END`
- L165 _public enumerator_ `DRAG_SELECTION_START`
- L166 _public enumerator_ `DRAG_SELECTION_END`
- L167 _public enumerator_ `DRAG_TIME`
- L168 _public enumerator_ `DRAG_NONE`

### `Plugins/Dataflow/Source/DataflowEditor/Private/Widgets/SDataflowSimulationTimeline.h` (Private)


#### class `SDataflowSimulationTimeline`  
`class SDataflowSimulationTimeline : public SCompoundWidget`  
_L17-77_
- inherits: `SCompoundWidget`
- desc: Main dataflow simulation timeline widget to be used in the dataflow toolkit
- L20 _public function_ `SLATE_BEGIN_ARGS(SDataflowSimulationTimeline)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDataflowSimulationBinding>& InSimulationBinbding);`
- L26 _public function_ `TSharedRef<INumericTypeInterface<double>> GetNumericTypeInterface() const` — Get numeric Type interface for converting between frame numbers and display formats.
- L29 _public prototype_ `bool GetGridMetrics(float PhysicalWidth, double& OutMajorInterval, int32& OutMinorDivisions) const;` — Compute a major grid interval and number of minor divisions to display
- L33 _private prototype_ `void HandleScrubPositionChanged(FFrameTime NewScrubPosition, bool bIsScrubbing, bool bEvaluate) const;` — Handle any changes to the scrub position
- L35 _private prototype_ `void HandlePlaybackRangeChanged(TRange<FFrameNumber> NewRange);`
- L38 _private prototype_ `void InitTrackNames();` — Init track names from the simulation binding
- L41 _private function_ `float GetColumnFillCoefficient(int32 ColumnIndex) const` — Get the column coefficient
- L46 _private prototype_ `void OnColumnFillCoefficientChanged(float FillCoefficient, int32 ColumnIndex);` — callback when the column coefficient is changing
- L49 _private prototype_ `TSharedRef<ITableRow> HandleTimelineListViewGenerateRow(TSharedPtr<FString> Text, const TSharedRef<STableViewBase>& OwnerTable);` — Add a track row in the list viiew
- L52 _private member_ `float ColumnFillCoefficients[2];` — The fill coefficients of each column in the grid.
- L55 _private member_ `TWeakPtr<FDataflowSimulationBinding> SimulationBinding;` — Simulation binding to get the timing information from dataflow
- L58 _private member_ `TSharedPtr<INumericTypeInterface<double>> NumericTypeInterface;` — Interface to display the frame number
- L61 _private member_ `TSharedPtr<FDataflowTimeSliderController> TimeSliderController;` — Time slider controller used in the timeline
- L64 _private member_ `TSharedPtr<ITimeSlider> TimeSlider;` — Time Slider used in the time line
- L67 _private member_ `TArray<TSharedPtr<FString>> TrackNames;` — List of track names holding the caches
- L70 _private member_ `TArray<TSharedPtr<FString>> FilteredTracks;` — List of filtered tracks holding the caches
- L73 _private member_ `TSharedPtr<SListView<TSharedPtr<FString>>> TracksListView;` — Track list view in betwwen the timeline and the transport controls
- L76 _private member_ `TAttribute<FAnimatedRange> ViewRange;` — Animation view range

### `Plugins/Dataflow/Source/DataflowEditor/Private/Widgets/SDataflowSplitterOverlay.h` (Private)


#### class `SDataflowSplitterOverlay`  
`class SDataflowSplitterOverlay : public SOverlay`  
_L20-46_
- inherits: `SOverlay`
- desc: Splitter used on the dataflow timeline as an overlay. Input is disabled on all areas except the draggable positions
- L23 _public typedef_ `typedef SSplitter::FArguments FArguments;`
- L25 _public prototype_ `void Construct( const FArguments& InArgs );`
- L28 _public prototype_ `virtual void OnArrangeChildren( const FGeometry& AllottedGeometry, FArrangedChildren& ArrangedChildren ) const override;`
- L29 _public prototype_ `virtual FCursorReply OnCursorQuery( const FGeometry& MyGeometry, const FPointerEvent& CursorEvent ) const override;`
- L30 _public prototype_ `virtual FReply OnMouseButtonDown( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L31 _public prototype_ `virtual void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent) override;`
- L32 _public prototype_ `virtual FReply OnMouseButtonUp( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L33 _public prototype_ `virtual FReply OnMouseMove( const FGeometry& MyGeometry, const FPointerEvent& MouseEvent ) override;`
- L34 _public prototype_ `virtual void OnMouseLeave( const FPointerEvent& MouseEvent ) override;`
- L39 _private prototype_ `FMargin GetSplitterHandlePadding(int32 Index) const;` — Get the padding in between several tracks
- L42 _private member_ `TSharedPtr<SSplitter> SplitterWidget;` — Splitter widget to be used in between the tracks
- L45 _private member_ `mutable TArray<FMargin> SlotPadding;` — Slot padding

### `Plugins/Dataflow/Source/DataflowEditor/Private/Widgets/SDataflowTimelineOverlay.h` (Private)


#### class `SDataflowTimelineOverlay`  
`class SDataflowTimelineOverlay : public SCompoundWidget`  
_L20-57_
- inherits: `SCompoundWidget`
- desc: An overlay that displays global information in the track area.
- L23 _public function_ `SLATE_BEGIN_ARGS(SDataflowTimelineOverlay) : _DisplayTickLines(true) , _DisplayScrubPosition(false)`
- L28 _public function_ `SLATE_ATTRIBUTE(bool, DisplayTickLines) SLATE_ATTRIBUTE(bool, DisplayScrubPosition) SLATE_ATTRIBUTE(FPaintPlaybackRangeArgs, PaintPlaybackRangeArgs) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<FDataflowTimeSliderController> InTimeSliderController)`
- L44 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;` — SWidget Interface
- L47 _private member_ `TSharedPtr<FDataflowTimeSliderController> TimeSliderController;` — Controller for manipulating time
- L50 _private member_ `TAttribute<bool> bDisplayScrubPosition;` — Whether or not to display the scrub position
- L53 _private member_ `TAttribute<bool> bDisplayTickLines;` — Whether or not to display tick lines
- L56 _private member_ `TAttribute<FPaintPlaybackRangeArgs> PaintPlaybackRangeArgs;` — User-supplied options for drawing playback range

### `Plugins/Dataflow/Source/DataflowEditor/Private/Widgets/SDataflowTransportControl.h` (Private)


#### class `SDataflowTransportControl`  
`class SDataflowTransportControl : public SCompoundWidget`  
_L17-79_
- inherits: `SCompoundWidget`
- desc: Dataflow simulation widget to control an animation/simulation
- L20 _public function_ `SLATE_BEGIN_ARGS(SDataflowTransportControl)`
- L21 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<FDataflowSimulationBinding>& InSimulationBinding);`
- L37 _private prototype_ `FReply OnForwardPlay();` — Delegate when the simulation controls are pressed
- L38 _private prototype_ `FReply OnBackwardPlay();`
- L39 _private prototype_ `FReply OnForwardStep();`
- L40 _private prototype_ `FReply OnBackwardStep();`
- L41 _private prototype_ `FReply OnForwardEnd();`
- L42 _private prototype_ `FReply OnBackwardEnd();`
- L43 _private prototype_ `FReply OnPlaybackMode();`
- L44 _private prototype_ `FReply OnRecord();`
- L45 _private prototype_ `void OnTickPlayback(double InCurrentTime, float InDeltaTime);`
- L48 _private prototype_ `TSharedRef<SWidget> OnCreateModeButton();` — Create preview mode widget
- L51 _private prototype_ `TSharedRef<SWidget> OnCreateLockButton();` — Create lock widget
- L54 _private prototype_ `TSharedRef<SWidget> OnCreateResetButton();` — Create reset widget
- L57 _private prototype_ `const FSlateBrush* GetLockButtonImage() const;` — Get the lock button image
- L60 _private function_ `EPlaybackMode::Type GetPlaybackMode() const` — Get the playback mode
- L63 _private member_ `TWeakPtr<FDataflowSimulationBinding> SimulationBinding;` — Simulation binding to extract dataflow information
- L66 _private member_ `EPreviewMode PreviewMode = EPreviewMode::Looping;` — Preview mode (looping...)
- L69 _private member_ `EPlaybackMode::Type PlaybackMode = EPlaybackMode::Stopped;` — Playback mode
- L72 _private member_ `TSharedPtr<SButton> PreviewModeButton;` — Playback mode button
- L75 _private member_ `TSharedPtr<SCheckBox> LockSimulationBox;` — Widget showing if a simulation is locked or not
- L78 _private member_ `TSharedPtr<SButton> ResetSimulationButton;` — Widget to reset a simulation

#### enum `SDataflowTransportControl::EPreviewMode`  
`enum class EPreviewMode : uint8`  
_L29-34_
- desc: Data flow preview mode
- L31 _public enumerator_ `Default`
- L32 _public enumerator_ `Looping`
- L33 _public enumerator_ `PingPong`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/AssetDefinition_DataflowAsset.h` (Public)


#### struct `FDataflowNodeData`  
`struct FDataflowNodeData`  
_L70-85_
- reflection: `USTRUCT()`
- desc: Copy/Paste structs
- L75 _public member_ `FString Type;` — `UPROPERTY()`
- L78 _public member_ `FString Name;` — `UPROPERTY()`
- L81 _public member_ `FString Properties;` — `UPROPERTY()`
- L84 _public member_ `FVector2D Position = FVector2D::ZeroVector;` — `UPROPERTY()`

#### struct `FDataflowCommentNodeData`  
`struct FDataflowCommentNodeData`  
_L88-106_
- reflection: `USTRUCT()`
- L93 _public member_ `FString Name;` — `UPROPERTY()`
- L96 _public member_ `FVector2D Size = FVector2D::ZeroVector;` — `UPROPERTY()`
- L99 _public member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY()`
- L102 _public member_ `FVector2D Position = FVector2D::ZeroVector;` — `UPROPERTY()`
- L105 _public member_ `int32 FontSize = 18;` — `UPROPERTY()`

#### struct `FDataflowConnectionData`  
`struct FDataflowConnectionData`  
_L109-124_
- reflection: `USTRUCT()`
- L114 _public member_ `FString Out;` — `UPROPERTY()`
- L117 _public member_ `FString In;` — `UPROPERTY()`
- L119 _public prototype_ `void Set(const FDataflowOutput& Output, const FDataflowInput& Input);`
- L121 _public prototype_ `static FString GetNode(const FString InConnection);`
- L122 _public prototype_ `static FString GetProperty(const FString InConnection);`
- L123 _public prototype_ `static void GetNodePropertyAndType(const FString InConnection, FString& OutNode, FString& OutProperty, FString& OutType);`

#### struct `FDataflowSubGraphData`  
`struct FDataflowSubGraphData`  
_L127-148_
- reflection: `USTRUCT()`
- L132 _public member_ `FGuid SubGraphGuid;` — `UPROPERTY()`
- L135 _public member_ `FString Name;` — `UPROPERTY()`
- L138 _public member_ `bool bIsForEach = false;` — `UPROPERTY()`
- L141 _public member_ `TArray<FDataflowNodeData> NodeData;` — `UPROPERTY()`
- L144 _public member_ `TArray<FDataflowCommentNodeData> CommentNodeData;` — `UPROPERTY()`
- L147 _public member_ `TArray<FDataflowConnectionData> ConnectionData;` — `UPROPERTY()`

#### struct `FDataflowCopyPasteContent`  
`struct FDataflowCopyPasteContent`  
_L151-166_
- reflection: `USTRUCT()`
- L156 _public member_ `TArray<FDataflowNodeData> NodeData;` — `UPROPERTY()`
- L159 _public member_ `TArray<FDataflowCommentNodeData> CommentNodeData;` — `UPROPERTY()`
- L162 _public member_ `TArray<FDataflowConnectionData> ConnectionData;` — `UPROPERTY()`
- L165 _public member_ `TArray<FDataflowSubGraphData> SubGraphData;` — `UPROPERTY()`

#### class `UAssetDefinition_DataflowAsset`  
`class UAssetDefinition_DataflowAsset : public UAssetDefinitionDefault`  
_L170-184_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L176 _private prototype_ `virtual FText GetAssetDisplayName() const override;`
- L177 _private prototype_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override;`
- L178 _private prototype_ `virtual FLinearColor GetAssetColor() const override;`
- L179 _private prototype_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override;`
- L180 _private prototype_ `virtual UThumbnailInfo* LoadThumbnailInfo(const FAssetData& InAssetData) const override;`
- L182 _private prototype_ `virtual FAssetOpenSupport GetAssetOpenSupport(const FAssetOpenSupportArgs& OpenSupportArgs) const;`
- L183 _private prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace DataflowAssetDefinitionHelpers` (scope `UE`)
- L18 _prototype_ `bool CreateNewDataflowAsset(const UObject* BoundAsset, UObject*& OutDataflowAsset);` (scope `UE::DataflowAssetDefinitionHelpers`) — Create a brand new empty dataflow asset @return true is the asset is successfully created ( in that case OutDataflowAsset will containt the pointer to this asset )
- L23 _prototype_ `bool MakeShareableDataflowAsset(UObject* BoundAsset, UDataflow*& OutDataflowAsset);` (scope `UE::DataflowAssetDefinitionHelpers`) — Take an embedded dataflow asset from BoundAsset and make it shareable by being its own separate asset If the Dataflow asset was already shareable , do nothing @return true if the operation was a success ( in that case OutDataflowAsset will containt the pointer to the shareable Dataflow asset )
- L28 _prototype_ `bool EmbedDataflowAsset(UObject* BoundAsset, UDataflow*& OutDataflowAsset);` (scope `UE::DataflowAssetDefinitionHelpers`) — Take an shared dataflow asset from BoundAsset and embded it in BoundAsset If the Dataflow asset was already embedded, do nothing @return true if the operation was a success ( in that case OutDataflowAsset will containt the pointer to the Embdedded Dataflow asset )
- L31 _prototype_ `bool OpenDataflowAsset(const UObject* Asset, UObject*& OutDataflowAsset);` (scope `UE::DataflowAssetDefinitionHelpers`) — Return true if we should proceed, false if we should re-open the dialog
- L34 _prototype_ `bool NewOrOpenDialog(const UObject* Asset, UObject*& OutDataflowAsset);` (scope `UE::DataflowAssetDefinitionHelpers`) — Return true if we should proceed, false if we should re-open the dialog
- L37 _prototype_ `UObject* NewOrOpenDataflowAsset(const UObject* Asset);` (scope `UE::DataflowAssetDefinitionHelpers`) — Create a new UDataflow if one doesn't already exist for the Cloth Asset
- L40 _prototype_ `bool SetDataflowFromTemplatePicker(UObject* Asset, bool bShowDefaultBlankOption = true);` (scope `UE::DataflowAssetDefinitionHelpers`) — Set dataflow from a template picked by the user
- L43 _prototype_ `bool CanOpenDataflowAssetInEditor(const UObject* DataflowAsset);` (scope `UE::DataflowAssetDefinitionHelpers`) — Determine whether or not a UDataflow can be opened directly in the Dataflow Editor
- L46 _prototype_ `FDelegateHandle RegisterDataflowAssetMenus(UClass* AssetClass);` (scope `UE::DataflowAssetDefinitionHelpers`) — Register Dataflow related menus
- L48 _prototype_ `void UnregisterDataflowAssetMenus(FDelegateHandle Handle);` (scope `UE::DataflowAssetDefinitionHelpers`)
- L53 _prototype_ `UObject* FactoryCreateNew( UClass* AssetClass, UObject* Parent, FName Name, EObjectFlags Flags, const FString* DataflowTemplatePath, bool bEmbedDataflow, const TCHAR* AssetPrefix);` (scope `UE::DataflowAssetDefinitionHelpers`) — Create a new Dataflow based asset using the specified Dataflow template, an asset with an empty Dataflow if an empty path is provided, or an unbound asset if the path is nullptr. @note The Dataflow template is always duplicated to use with the new asset, even when not embedded. @return A new asset of type AssetClass that references a new Dataflow asset of the specified template.

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowAssetEditUtils.h` (Public)


#### struct `UE::Dataflow::FEditAssetUtils`  
`struct FEditAssetUtils`  
_L32-188_
- L37 _public prototype_ `UE_INTERNAL static bool IsUniqueDataflowSubObjectName(UDataflow* DataflowAsset, FName Name);` — Test if a dataflow sub-object ( Node, subgraph ... ) name is unique
- L39 _public prototype_ `UE_INTERNAL static TSharedPtr<IAssetReferenceFilter> MakeAssetReferenceFilter(const UEdGraph* Graph);`
- L55 _public prototype_ `UE_INTERNAL static UDataflowEdNode* AddNewNode(UEdGraph* EdGraph, const FVector2D& Location, const FName NodeName, const FName NodeTypeName, UEdGraphPin* FromPin);` — Add a new node to the graph @param EdGraph	Main Graph or Subgraph to add the node to @param Location	Location on the graph where to place the node @param NodeName	Name to give to the node ( if the name is not unique a unique name will be created out of the parameter one) @param TypeName	Name of the type of the node to add @param FromPin	Pin to connect automatically to the node @return the newly created EdGraphNode
- L64 _public prototype_ `UE_INTERNAL static UEdGraphNode* AddNewComment(UEdGraph* EdGraph, const FVector2D& Location, const FVector2D& Size);` — Add a new comment node to the graph @param EdGraph	Main Graph or Subgraph to add the node to @param Location	Location on the graph where to place the comment @param Location	Size of the comment box @return the newly created EdGraphNode
- L71 _public prototype_ `UE_INTERNAL static void DeleteNodes(UEdGraph* EdGraph, const TArray<UEdGraphNode*>& NodesToDelete);` — Delete some nodes from a graph @param EdGraph			Main Graph or Subgraph to duplicate the node in @param NodesToDelete		List of node to delete
- L81 _public prototype_ `UE_INTERNAL static void DuplicateNodes(UEdGraph* EdGraph, const TArray<UEdGraphNode*>& NodesToDuplicate, const FVector2D& Location, TArray<UEdGraphNode*>& OutDuplicatedNodes);` — Duplicate nodes within the same graph @param EdGraph			Main Graph or Subgraph to duplicate the node in @param NodeToDuplicate	List of nodes to duplicate @param Location			Location on the graph where to place the node @param OutDuplicatedNodes	List of newly created nodes @return the newly created EdGraphNode
- L93 _public prototype_ `UE_INTERNAL static void DuplicateNodes(UEdGraph* SourceEdGraph, const TArray<UEdGraphNode*>& NodesToDuplicate, UEdGraph* TargetEdGraph, const FVector2D& Location, TArray<UEdGraphNode*>& OutDuplicatedNodes, TMap<FGuid, FGuid>& OutNodeGuidMap);` — Duplicate nodes from one graph to another ( assuming same dataflow asset ) @param SourceEdGraph		Main Graph or Subgraph to duplicate the node from @param NodeToDuplicate	List of nodes to duplicate @param TargetEdGraph		Main Graph or Subgraph to duplicate the node to @param Location			Location on the graph where to place the node @param OutDuplicatedNodes	List of newly created nodes @param OutNodeGuidMap		Mapping of dup[licated -> new node guids @return the newly created EdGraphNode
- L98 _public prototype_ `UE_INTERNAL static void CopyNodesToClipboard(const TArray<const UEdGraphNode*>& NodesToCopy, int32& OutNumCopiedNodes);` — Copy a list of nodes and their connection to the clipboard
- L103 _public prototype_ `UE_INTERNAL static void PasteNodesFromClipboard(UEdGraph* EdGraph, const FVector2D& Location, TArray<UEdGraphNode*>& OutPastedNodes);` — Attempt to paste nodes from the clipboard
- L115 _public prototype_ `UE_INTERNAL static FName AddNewVariable(UDataflow* DataflowAsset, FName BaseName = DefaultNewVariableBaseName);` — Add a new Dataflow asset variable If BaseName already exists, use it to generate a unique name by adding an increment to it in the form of BaseName_##
- L121 _public prototype_ `UE_INTERNAL static FName AddNewVariable(UDataflow* DataflowAsset, FName BaseName, const FPropertyBagPropertyDesc& TemplateDesc);` — Add a new Dataflow asset variable from a property bag description template If BaseName already exists, use it to generate a unique name by adding an increment to it in the form of BaseName_##
- L126 _public prototype_ `UE_INTERNAL static void DeleteVariable(UDataflow* DataflowAsset, FName VariableName);` — Remove a Dataflow asset variable
- L131 _public prototype_ `UE_INTERNAL static void RenameVariable(UDataflow* DataflowAsset, FName OldVariableName, FName NewVariableName);` — Rename a Dataflow asset variable
- L137 _public prototype_ `UE_INTERNAL static FName DuplicateVariable(UDataflow* DataflowAsset, FName VariableName);` — Duplicate a Dataflow asset variable the new variable name will be generate uniquely based on the name of the original variable
- L142 _public prototype_ `UE_INTERNAL static void SetVariableType(UDataflow* DataflowAsset, FName VariableName, const FEdGraphPinType& PinType);` — Set the type of a Dataflow asset variable
- L148 _public prototype_ `UE_INTERNAL static void SetVariableValue(UDataflow* DataflowAsset, FName VariableName, const FInstancedPropertyBag& SourceBag);` — Set value of a Dataflow asset variable from an property in a propertybag Name and type must match for the operation to be successful
- L153 _public prototype_ `UE_INTERNAL static void CopyVariableToClipboard(UDataflow* DataflowAsset, FName VariableName);` — Copy a variable to clipboard
- L158 _public prototype_ `UE_INTERNAL static FName PasteVariableFromClipboard(UDataflow* DataflowAsset);` — Paste a variable from clipboard and return its name
- L169 _public prototype_ `UE_INTERNAL static FName AddNewSubGraph(UDataflow* DataflowAsset, FName BaseName = DefaultNewSubGraphBaseName);` — Add a new SubGraph to the Dataflow Asset and return its name
- L174 _public prototype_ `UE_INTERNAL static void RenameSubGraph(UDataflow* DataflowAsset, FName OldSubGraphName, FName NewSubGraphName);` — Rename a Dataflow SubGraph
- L179 _public prototype_ `UE_INTERNAL static void DeleteSubGraph(UDataflow* DataflowAsset, FGuid SubGraphGuid);` — Delete a Dataflow SubGraph
- L187 _private prototype_ `static UDataflowSubGraph* CreateSubGraphWithGuid(UDataflow& DataflowAsset, FName UniqueName, const FGuid& Guid, bool bIsForEach);` — Create a UDataflowSubGraph that preserves a specific GUID and ForEach state. Restricted to FEditAssetUtils via UDataflowSubGraph friend access so only the paste-from-clipboard path can recreate a subgraph with a non-fresh GUID.

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Dataflow` (scope `UE`)
- L29 _variable_ `static const FName DefaultNewVariableBaseName = "Ne` (scope `UE::Dataflow`)
- L30 _variable_ `static const FName DefaultNewSubGraphBaseName = "Ne` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowAssetFactory.h` (Public)


#### class `UDataflowAssetFactory`  
`class UDataflowAssetFactory : public UFactory`  
_L10-32_
- reflection: `UCLASS()`
- inherits: `UFactory`
- L15 _public prototype_ `UDataflowAssetFactory();`
- L18 _public prototype_ `bool CanCreateNew() const override;` — UFactory Interface
- L19 _public prototype_ `bool FactoryCanImport(const FString& Filename) override;`
- L20 _public prototype_ `UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`
- L27 _public prototype_ `bool ShouldShowInNewMenu() const override;`
- L28 _public prototype_ `bool ConfigureProperties() override;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowCollectionSpreadSheetWidget.h` (Public)


#### struct `SCollectionInfo`  
`struct SCollectionInfo`  
_L21-25_
- desc: Struct to hold OutputType/Selection data for the outputs Data is stored in a map using the OutputName as key: TMap<FString, SCollectionInfo>
- L24 _public member_ `TSharedPtr<const FManagedArrayCollection> Collection;` — FString OutputType;

#### struct `FCollectionSpreadSheetHeader`  
`struct FCollectionSpreadSheetHeader`  
_L33-39_
- desc: Header 1st column possible values: Transform Index/Face Index/Vertex Index based on the OutputType 2nd column is SelectionStatus
- L35 _public member_ `static const FName IndexColumnName;`
- L36 _public member_ `static const FName NoColumnName;`
- L38 _public member_ `TArray<FName> ColumnNames;`

#### struct `FCollectionSpreadSheetItem`  
`struct FCollectionSpreadSheetItem`  
_L46-49_
- desc: Representing a row in the table Index/SelectionStatus
- L48 _public member_ `TArray<FString> Values;`

#### class `SCollectionSpreadSheetRow`  
`class SCollectionSpreadSheetRow : public SMultiColumnTableRow<TSharedPtr<const FCollectionSpreadSheetItem>>`  
_L55-71_
- inherits: `SMultiColumnTableRow<TSharedPtr<constFCollectionSpreadSheetItem>>`
- L58 _public function_ `SLATE_BEGIN_ARGS(SCollectionSpreadSheetRow)`
- L60 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<const FCollectionSpreadSheetHeader>, Header) SLATE_ARGUMENT(TSharedPtr<const FCollectionSpreadSheetItem>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, const TSharedPtr<const FCollectionSpreadSheetHeader>& InHeader, const TSharedPtr<const FCollectionSpreadSheetItem>& InItem);`
- L66 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L69 _private member_ `TSharedPtr<const FCollectionSpreadSheetHeader> Header;`
- L70 _private member_ `TSharedPtr<const FCollectionSpreadSheetItem> Item;`

#### class `SCollectionSpreadSheet`  
`class SCollectionSpreadSheet : public SCompoundWidget`  
_L76-114_
- inherits: `SCompoundWidget`
- desc: 2xn grid to display Collection data
- L79 _public function_ `SLATE_BEGIN_ARGS(SCollectionSpreadSheet)`
- L80 _public prototype_ `SLATE_ARGUMENT(FName, SelectedOutput) SLATE_ARGUMENT(TSharedPtr<SScrollBar>, ExternalVerticalScrollBar) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L86 _public function_ `TMap<FString, SCollectionInfo>& GetCollectionInfoMap()`
- L88 _public prototype_ `const FName& GetSelectedOutput() const;`
- L89 _public prototype_ `const FString GetSelectedOutputStr() const;`
- L90 _public prototype_ `void SetSelectedOutput(const FName& InSelectedOutput);`
- L92 _public prototype_ `const FName& GetSelectedGroup() const;`
- L93 _public prototype_ `void SetSelectedGroup(const FName& InSelectedGroup);`
- L95 _public function_ `int32 GetNumItems() const`
- L96 _public function_ `void SetNumItems(int32 InNumItems)`
- L98 _public prototype_ `TSharedRef<ITableRow> GenerateRow(TSharedPtr<const FCollectionSpreadSheetItem> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L101 _private member_ `FName SelectedOutput = FName(TEXT(""));`
- L102 _private member_ `FName SelectedGroup = FName(TEXT(""));`
- L103 _private member_ `TMap<FString, SCollectionInfo> CollectionInfoMap;` — Map<Name of Output, FManagedArrayCollection>
- L105 _private member_ `TSharedPtr<SListView<TSharedPtr<const FCollectionSpreadSheetItem>>> ListView;`
- L106 _private member_ `TArray<TSharedPtr<const FCollectionSpreadSheetItem>> ListItems;`
- L108 _private member_ `TSharedPtr<FCollectionSpreadSheetHeader> Header;`
- L109 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L111 _private member_ `int32 NumItems = 0;`
- L112 _private prototype_ `void RegenerateHeader();`
- L113 _private prototype_ `void RepopulateListView();`

#### class `SCollectionSpreadSheetWidget`  
`class SCollectionSpreadSheetWidget : public SCompoundWidget`  
_L123-225_
- inherits: `SCompoundWidget`
- desc: Widget for the CollectionSpreadSheet panel
- L126 _public function_ `SLATE_BEGIN_ARGS(SCollectionSpreadSheetWidget)`
- L127 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L137 _public prototype_ `void SetData(const FString& InNodeName);`
- L138 _public prototype_ `void RefreshWidget();`
- L139 _public function_ `TSharedPtr<SCollectionSpreadSheet> GetCollectionTable()`
- L140 _public prototype_ `void SetStatusText();`
- L142 _public prototype_ `void UpdateCollectionGroups(const FName& InOutputName);`
- L144 _public prototype_ `const FSlateBrush* GetPinButtonImage() const;`
- L145 _public prototype_ `const FSlateBrush* GetLockButtonImage() const;`
- L148 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinnedDownChanged, const bool);` — Gets a multicast delegate which is called whenever the PinnedDown button clicked
- L149 _public function_ `FOnPinnedDownChanged& GetOnPinnedDownChangedDelegate()`
- L152 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRefreshLockedChanged, const bool);` — Gets a multicast delegate which is called whenever the LockRefresh button clicked
- L153 _public function_ `FOnRefreshLockedChanged& GetOnRefreshLockedChangedDelegate()`
- L155 _public member_ `TSet<FName> NonListViewGroups = { FName(TEXT("Transform")), FName(TEXT("Vertices")), F`
- L157 _public function_ `EVisibility GetCollectionSpreadSheetVisibility() const`
- L162 _public function_ `EVisibility GetTransformOutlinerVisibility() const`
- L167 _public function_ `EVisibility GetVerticesOutlinerVisibility() const`
- L172 _public function_ `EVisibility GetFacesOutlinerVisibility() const`
- L178 _public prototype_ `void NodeOutputsComboBoxSelectionChanged(FName InSelectedOutput, ESelectInfo::Type InSelectInfo);` — UI callbacks
- L179 _public prototype_ `void CollectionGroupsComboBoxSelectionChanged(FName InSelectedOutput, ESelectInfo::Type InSelectInfo);`
- L180 _public prototype_ `FText GetNoOutputText();`
- L181 _public prototype_ `FText GetNoGroupText();`
- L184 _private prototype_ `void UpdateTransformOutliner();`
- L185 _private prototype_ `void UpdateVertexOutliner();`
- L186 _private prototype_ `void UpdateFaceOutliner();`
- L188 _private member_ `TSharedPtr<STextBlock> NodeNameTextBlock;`
- L189 _private member_ `TSharedPtr<SComboBox<FName>> NodeOutputsComboBox;`
- L190 _private member_ `TSharedPtr<STextBlock> NodeOutputsComboBoxLabel;`
- L191 _private member_ `TSharedPtr<SComboBox<FName>> CollectionGroupsComboBox;`
- L192 _private member_ `TSharedPtr<STextBlock> CollectionGroupsComboBoxLabel;`
- L193 _private member_ `TSharedPtr<SCollectionSpreadSheet> CollectionTable;`
- L196 _private member_ `TSharedPtr<STransformOutliner> TransformOutliner;` — Widget to display Transform hierarchy
- L199 _private member_ `TSharedPtr<SVerticesOutliner> VerticesOutliner;` — Widget to display Vertices hierarchy
- L202 _private member_ `TSharedPtr<SFacesOutliner> FacesOutliner;` — Widget to display Faces hierarchy
- L204 _private member_ `TSharedPtr<STextBlock> StatusTextBlock;`
- L206 _private member_ `FString NodeName;`
- L207 _private member_ `TArray<FName> NodeOutputs;`
- L208 _private member_ `TArray<FName> CollectionGroups;`
- L209 _private member_ `bool bIsPinnedDown = false;`
- L210 _private member_ `bool bIsRefreshLocked = false;`
- L212 _private member_ `TSharedPtr<SScrollBar> SpreadSheetHorizontalScrollBar;` — ScrollBar to scroll ListView/TreeView view area
- L214 _private member_ `TSharedPtr<SScrollBar> CollectionSpreadSheetExternalVerticalScrollBar;` — External scrollbar to scroll CollectionSpreadSheet vertically, only visible when CollectionSpreadSheet is visible
- L216 _private member_ `TSharedPtr<SScrollBar> TransformOutlinerExternalVerticalScrollBar;` — External scrollbar to scroll TransformOutliner vertically, only visible when TransformOutliner is visible
- L218 _private member_ `TSharedPtr<SScrollBar> VerticesOutlinerExternalVerticalScrollBar;` — External scrollbar to scroll VerticesOutliner vertically, only visible when VerticesOutliner is visible
- L220 _private member_ `TSharedPtr<SScrollBar> FacesOutlinerExternalVerticalScrollBar;` — External scrollbar to scroll FacesOutliner vertically, only visible when FacesOutliner is visible
- L223 _protected member_ `FOnPinnedDownChanged OnPinnedDownChangedDelegate;`
- L224 _protected member_ `FOnRefreshLockedChanged OnRefreshLockedChangedDelegate;`

#### Free symbols / members of external scopes

- L148 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinnedDownChanged, const bool);` — Gets a multicast delegate which is called whenever the PinnedDown button clicked
- L152 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRefreshLockedChanged, const bool);` — Gets a multicast delegate which is called whenever the LockRefresh button clicked

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowColorRampCustomization.h` (Public)


#### class `UE::Dataflow::FDataflowColorRampCustomization`  
`class FDataflowColorRampCustomization : public IPropertyTypeCustomization`  
_L9-20_
- inherits: `IPropertyTypeCustomization`
- L14 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L18 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> , IDetailChildrenBuilder& , IPropertyTypeCustomizationUtils& ) override`

#### class `UE::Dataflow::FDataflowLinearColorRampCustomization`  
`class FDataflowLinearColorRampCustomization : public IPropertyTypeCustomization`  
_L22-33_
- inherits: `IPropertyTypeCustomization`
- L27 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L30 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L31 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> , IDetailChildrenBuilder& , IPropertyTypeCustomizationUtils& ) override`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowConstructionScene.h` (Public)


#### class `FDataflowConstructionScene`  
`class FDataflowConstructionScene : public FDataflowPreviewSceneBase`  
_L38-152_
- inherits: `FDataflowPreviewSceneBase`
- desc: Dataflow construction scene holding all the dynamic meshes used/displayed in the dataflow graph
- L41 _private typedef_ `typedef TPair<TObjectPtr<const UDataflowEdNode>, int32> FDataflowRenderKey;` — (const void* ObjectPointer, const int32 ObjectIndex)
- L45 _public member_ `inline static FName DebugMeshComponentTag = TEXT("Mes`
- L47 _public prototype_ `FDataflowConstructionScene(FPreviewScene::ConstructionValues ConstructionValues, UDataflowEditor* Editor);`
- L48 _public prototype_ `virtual ~FDataflowConstructionScene();`
- L51 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L54 _public prototype_ `virtual void TickDataflowScene(const float DeltaSeconds) override;` — Tick data flow scene
- L57 _public function_ `virtual bool CanRunSimulation() const override` — Check if the preview scene can run simulation
- L60 _public prototype_ `bool HasRenderableGeometry();` — Is there ANYTHING to render
- L63 _public prototype_ `void ResetConstructionScene();` — Close the construction scene
- L66 _public prototype_ `void UpdateConstructionScene();` — Update the construction scene
- L69 _public prototype_ `void SetVisibility(bool bVisible, UActorComponent* Component = nullptr);` — Hide all or a single component
- L72 _public prototype_ `TArray<TObjectPtr<UDynamicMeshComponent>> GetDynamicMeshComponents() const;` — Array of all DynamicMeshComponents in the scene
- L75 _public prototype_ `TArray<TObjectPtr<UDebugDrawComponent>> GetDebugDrawComponents() const;` — Get all Debug draw components
- L78 _public prototype_ `TArray<UObject*> GetRenderSettings() const;` — Get the render settings for the selected nodes
- L81 _public prototype_ `void SelectNodeComponents(const UDataflowEdNode* EdNode);` — select only the components that are relates to a specific node
- L84 _public prototype_ `TArray<UDataflowRenderableTypeSettings*> GetRenderableTypeSettings() const;` — Get the render settings for matching the selected nodes
- L86 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnConstructionSceneUpdated) FOnConstructionSceneUpdated OnConstructionSceneUpdated;`
- L92 _private prototype_ `void ResetWireframeMeshElementsVisualizer();` — Reset the scene mesh visualizer
- L95 _private prototype_ `void UpdateWireframeMeshElementsVisualizer();` — Update the scene mesh visualizer
- L98 _private prototype_ `void AddWireframeMeshElementsVisualizer();` — Add a mesh visualizer to the scene
- L101 _private prototype_ `void ResetSceneComponents();` — Reset all the scene components (dynamic mesh / primitive)
- L104 _private prototype_ `void UpdateDynamicMeshComponents();` — Build the dynamic mesh components from the dataflow graph render targets
- L107 _private prototype_ `void UpdatePrimitiveComponents();` — Build the primitive components from the dataflow graph selected node
- L110 _private prototype_ `TArray<UMaterialInterface*> GetMaterialsFromRenderingFacade(const GeometryCollection::Facades::FRenderingFacade& RenderingFacade, int32 MeshIndex);` — Get the materials stored in the rendering facade for a speicfic mesh
- L113 _private prototype_ `void UpdateComponentsFromNode(const UDataflowEdNode* Node, bool bWireframe);` — Build the primitive components from the dataflow graph selected node
- L116 _private prototype_ `TObjectPtr<UDynamicMeshComponent>& AddDynamicMeshComponent( FDataflowRenderKey InKey, const FString& MeshName, UE::Geometry::FDynamicMesh3&& DynamicMesh, const TArray<UMaterialInterface*>& MaterialSet, const FTransform& InMeshTransform = FTransform::Identity);` — Add a dynamic mesh component to the scene
- L120 _private prototype_ `void RemoveSceneComponent(USelection* SelectedComponents, UPrimitiveComponent* PrimitiveComponent);` — Remove the scene component from selection and destroy it
- L123 _private prototype_ `void UpdateFloorVisibility();` — update floor visibility based on the view type
- L126 _private typedef_ `typedef TPair<FDataflowRenderKey, TObjectPtr<UDynamicMeshComponent>> FRenderElement;` — Dynamic mesh components generated by the tools for edit/manipulation
- L127 _private member_ `TMap<FDataflowRenderKey, TObjectPtr<UDynamicMeshComponent>> DynamicMeshComponents;`
- L130 _private typedef_ `typedef TPair<TObjectPtr<UDynamicMeshComponent>, TObjectPtr<UMeshElementsVisualizer>> FRenderWireElement;` — Rest space wireframe. They have to get ticked to be able to respond to setting changes. [ticked]
- L131 _private member_ `TMap<TObjectPtr<UDynamicMeshComponent>,TObjectPtr<UMeshElementsVisualizer> > WireframeElements;`
- L134 _private member_ `TArray<UDynamicMeshComponent*> MeshComponentsForWireframeRendering;` — Source meshes for Wireframe rendering
- L137 _private member_ `TArray<TObjectPtr<UInteractiveToolPropertySet>> PropertyObjectsToTick;` — Property objects (visible or not) that get ticked. [ticked]
- L140 _private member_ `UE::Dataflow::FTimestamp LastRenderedTimestamp = UE::Dataflow::FTimestamp::Invalid;` — Last Rendered Timestamp
- L143 _private member_ `bool bConstructionViewWireframe = true;` — Show the wireframe on render
- L146 _private member_ `TArray<TObjectPtr<UPrimitiveComponent>> PrimitiveComponents;` — Primitive components generated by the nodes and to be used by the tools
- L149 _private member_ `TArray<UE::Dataflow::FRenderableTypeInstance> RenderableTypeInstances;` — list of renderable type instance, there's one per node/output that can be rendered
- L151 _private member_ `TObjectPtr<UDataflowDebugMeshRenderSettings> DebugMeshRenderSettings = nullptr;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Geometry` (scope `UE`)
- L29 _namespace_ `namespace Dataflow` (scope `UE`)
- L86 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnConstructionSceneUpdated) FOnConstructionSceneUpdated OnConstructionSceneUpdated;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowConstructionViewportClient.h` (Public)


#### class `FDataflowConstructionViewportClient`  
`class FDataflowConstructionViewportClient : public FDataflowEditorViewportClientBase`  
_L21-109_
- inherits: `FDataflowEditorViewportClientBase`
- L24 _public typedef_ `using Super = FDataflowEditorViewportClientBase;`
- L26 _public prototype_ `FDataflowConstructionViewportClient(FEditorModeTools* InModeTools, TWeakPtr<FDataflowConstructionScene> InConstructionScenePtr, const bool bCouldTickScene, const TWeakPtr<SEditorViewport> InEditorViewportWidget = nullptr);`
- L29 _public prototype_ `virtual ~FDataflowConstructionViewportClient();`
- L31 _public prototype_ `void SetConstructionViewMode(const UE::Dataflow::IDataflowConstructionViewMode* InViewMode);`
- L33 _public prototype_ `USelection* GetSelectedComponents() const;`
- L36 _public prototype_ `void SetDataflowEditorToolkit(TWeakPtr<FDataflowEditorToolkit> DataflowToolkit);` — Set the data flow toolkit used to create the client
- L39 _public function_ `const TWeakPtr<FDataflowEditorToolkit>& GetDataflowEditorToolkit() const` — Get the data flow toolkit
- L42 _public prototype_ `void SetToolCommandList(TWeakPtr<FUICommandList> ToolCommandList);` — Set the tool command list
- L45 _public function_ `virtual FString GetReferencerName() const override` — FGCObject Interface
- L47 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedMulticast, const TArray<UPrimitiveComponent*>&, const TArray<FDataflowBaseElement*>&) FOnSelectionChangedMulticast OnSelectionChangedMulticast;`
- L50 _public prototype_ `FString GetOverlayString() const;`
- L53 _public function_ `UE::Widget::EWidgetMode GetToolWidgetMode() const` — Return the widget mode only used for tooling
- L55 _public prototype_ `void ShowMeshEdges(bool bShow);`
- L57 _public prototype_ `void FocusViewportOnBoundingBox(const FBox& BoundingBox, bool bInstant);`
- L62 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L67 _private prototype_ `virtual void OnViewportClicked(HHitProxy* HitProxy) override;` — FDataflowEditorViewportClientBase
- L70 _private prototype_ `virtual void Tick(float DeltaSeconds) override;` — FEditorViewportClient interface
- L71 _private prototype_ `virtual bool InputKey(const FInputKeyEventArgs& EventArgs) override;`
- L72 _private prototype_ `virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L73 _private prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L74 _private prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L75 _private prototype_ `virtual float GetMinimumOrthoZoom() const override;`
- L76 _private prototype_ `virtual bool CanSetWidgetMode(UE::Widget::EWidgetMode NewMode) const override;`
- L77 _private prototype_ `virtual UE::Widget::EWidgetMode GetWidgetMode() const override;`
- L78 _private prototype_ `virtual void SetWidgetMode(UE::Widget::EWidgetMode NewMode) override;`
- L79 _private prototype_ `virtual bool ShouldOrbitCamera() const override;`
- L81 _private prototype_ `void UpdateFromSettings();`
- L83 _private member_ `TUniquePtr<IClickDragBehaviorTarget> OrthoScrollBehaviorTarget;`
- L84 _private member_ `TUniquePtr<FEditor2DMouseWheelZoomBehaviorTarget> ZoomBehaviorTarget;`
- L85 _private member_ `TArray<TObjectPtr<UInputBehavior>> BehaviorsFor2DMode;`
- L88 _private member_ `TWeakPtr<FDataflowEditorToolkit> DataflowEditorToolkitPtr = nullptr;` — Toolkit used to create the viewport client
- L91 _private member_ `TWeakPtr<FDataflowConstructionScene> ConstructionScene;` — Dataflow preview scene from the toolkit
- L94 _private member_ `TWeakPtr<FUICommandList> ToolCommandList;` — @todo(brice) : Is this needed?
- L97 _private member_ `const UE::Dataflow::IDataflowConstructionViewMode* ConstructionViewMode = nullptr;` — Construction view mode
- L100 _private member_ `bool bEnableSceneTicking = false;` — Flag to enable scene ticking from the client
- L103 _private member_ `TMap<FName, FViewportCameraTransform> SavedInactiveViewTransforms;` — Saved view transforms for the currently inactive view modes (e.g. store the 3D camera here while in 2D mode and vice-versa)
- L106 _private member_ `UE::Widget::EWidgetMode WidgetMode = UE::Widget::WM_Translate;` — Currently active transform widget type.
- L108 _private member_ `FDelegateHandle OnSettingsChangeHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Dataflow` (scope `UE`)
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedMulticast, const TArray<UPrimitiveComponent*>&, const TArray<FDataflowBaseElement*>&) FOnSelectionChangedMulticast OnSelectionChangedMulticast;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowConstructionVisualization.h` (Public)


#### class `UE::Dataflow::IDataflowConstructionVisualization`  
`class IDataflowConstructionVisualization`  
_L18-27_
- L21 _public prototype_ `virtual ~IDataflowConstructionVisualization() = default;`
- L23 _public prototype_ `virtual FName GetName() const = 0;`
- L24 _public function_ `virtual void ExtendViewportShowMenu(const TSharedPtr<FDataflowConstructionViewportClient>& ViewportClient, FMenuBuilder& MenuBuilder)`
- L25 _public function_ `virtual void Draw(const FDataflowConstructionScene* ConstructionScene, FPrimitiveDrawInterface* PDI, const FSceneView* View = nullptr)`
- L26 _public function_ `virtual void DrawCanvas(const FDataflowConstructionScene* ConstructionScene, FCanvas* Canvas, const FSceneView* SceneView)`

#### class `UE::Dataflow::FDataflowConstructionVisualizationRegistry`  
`class FDataflowConstructionVisualizationRegistry`  
_L29-46_
- L34 _public prototype_ `static FDataflowConstructionVisualizationRegistry& GetInstance();` — FLazySingleton
- L35 _public prototype_ `static void TearDown();`
- L37 _public prototype_ `void RegisterVisualization(TUniquePtr<IDataflowConstructionVisualization>&& Visualization);`
- L38 _public prototype_ `void DeregisterVisualization(const FName& VisualizationName);`
- L40 _public prototype_ `const TMap<FName, TUniquePtr<IDataflowConstructionVisualization>>& GetVisualizations() const;`
- L41 _public prototype_ `const IDataflowConstructionVisualization* GetVisualization(const FName& VisualizationOption) const;`
- L45 _private member_ `TMap<FName, TUniquePtr<IDataflowConstructionVisualization>> VisualizationMap;`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditor.h` (Public)


#### class `UDataflowEditorSettings`  
`class UDataflowEditorSettings : public UObject`  
_L31-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`

#### class `UDataflowEditorUserSettings`  
`class UDataflowEditorUserSettings : public UObject`  
_L37-49_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UObject`
- L44 _public member_ `bool bUseAsyncEvaluation = false;` — `UPROPERTY(config, EditAnywhere, Category = "Dataflow")` — When true use the task graph based evaluation system
- L48 _public member_ `bool bShowPerformanceData = false;` — `UPROPERTY(config, EditAnywhere, Category = "Dataflow")` — Whether to show the performance data on top of the nodes

#### class `UDataflowEditor`  
`class UDataflowEditor : public UBaseCharacterFXEditor`  
_L65-144_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBaseCharacterFXEditor`
- L70 _public prototype_ `UDataflowEditor();`
- L73 _public prototype_ `virtual TSharedPtr<FBaseAssetToolkit> CreateToolkit() override;` — UBaseCharacterFXEditor interface
- L76 _public prototype_ `virtual void Initialize(const TArray<TObjectPtr<UObject>>& InObjects, const TSubclassOf<AActor>& InPreviewClass = {}) override;` — Initialize editor contents given a list of objects
- L79 _public prototype_ `void UpdateTerminalContents(const UE::Dataflow::FTimestamp TimeStamp);` — Update the terminal contents
- L82 _public prototype_ `void UpdateEditorContent();` — Update the editor content
- L85 _public function_ `TObjectPtr<UDataflowBaseContent>& GetEditorContent()` — Dataflow editor content accessors
- L86 _public function_ `const TObjectPtr<UDataflowBaseContent>& GetEditorContent() const`
- L89 _public function_ `TArray<TObjectPtr<UDataflowBaseContent>>& GetTerminalContents()` — Dataflow terminal contents accessors
- L90 _public function_ `const TArray<TObjectPtr<UDataflowBaseContent>>& GetTerminalContents() const`
- L93 _public function_ `const TArray<FName>& GetToolCategories() const` — Get the registered tool categories
- L97 _public function_ `template<typename T> inline const T* FindEditorSettings() const` — Get the editor settings
- L110 _public function_ `void RegisterToolCategories(const TArray<FName>& InToolCategrories)` — Registere tool categories available for that construction scene
- L113 _public prototype_ `void AddEditorSettings(const UDataflowEditorSettings* Settings);` — set the settings for this editor - this needs to be called before initialize for it to be applied
- L119 _private typedef_ `using ValidTerminalsType = TMap<TSharedPtr<FDataflowNode>,TObjectPtr<UDataflowBaseContent>>;`
- L122 _private prototype_ `void RemoveTerminalContents(const TSharedPtr<UE::Dataflow::FGraph>& DataflowGraph, ValidTerminalsType& ValidTerminals);` — Remove invalid terminal contents from the container
- L125 _private prototype_ `void AddTerminalContents(const TSharedPtr<UE::Dataflow::FGraph>& DataflowGraph, ValidTerminalsType& ValidTerminals);` — Add valid terminal nodes to the container
- L132 _private member_ `TObjectPtr<UDataflowBaseContent> EditorContent;` — `UPROPERTY()` — Dataflow editor is the owner of the object list to edit/process and the dataflow mode is the one holding the dynamic mesh components to be rendered in the viewport It is why the data flow asset/owner/skelmesh have been added here. Could be added in the subsystem if necessary
- L136 _private member_ `TArray<TObjectPtr<UDataflowBaseContent>> TerminalContents;` — `UPROPERTY()` — List of dataflow contents available in the graph and coming from all the terminal nodes
- L140 _private member_ `TArray<TObjectPtr<const UDataflowEditorSettings>> EditorSettings;` — `UPROPERTY()` — array of settings for this instance
- L143 _private member_ `TArray<FName> ToolCategories;` — List of tool categories registered for that editor

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L146 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowEditor, Log, All);`
- L146 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowEditor, Log, All);`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditorCommands.h` (Public)


#### class `FDataflowEditorCommandsImpl`  
`class FDataflowEditorCommandsImpl : public TBaseCharacterFXEditorCommands<FDataflowEditorCommandsImpl>`  
_L31-103_
- inherits: `TBaseCharacterFXEditorCommands<FDataflowEditorCommandsImpl>`
- desc: FDataflowEditorCommandsImpl
- L35 _public prototype_ `FDataflowEditorCommandsImpl();`
- L40 _public prototype_ `~FDataflowEditorCommandsImpl() = default;` — Note: We need to explicitly disable warnings on these constructors/operators for clang to be happy with deprecated variables (See Confluence page "How to Deprecate Code in UE > How to deprecate variables inside a UStruct")
- L41 _public prototype_ `FDataflowEditorCommandsImpl(const FDataflowEditorCommandsImpl&) = default;`
- L42 _public prototype_ `FDataflowEditorCommandsImpl(FDataflowEditorCommandsImpl&&) = default;`
- L43 _public prototype_ `FDataflowEditorCommandsImpl& operator=(const FDataflowEditorCommandsImpl&) = default;`
- L44 _public prototype_ `FDataflowEditorCommandsImpl& operator=(FDataflowEditorCommandsImpl&&) = default;`
- L48 _public prototype_ `virtual void RegisterCommands() override;` — TBaseCharacterFXEditorCommands<> interface
- L52 _public function_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override` — TInteractiveToolCommands<> Each tool will have its own TInteractiveToolCommands<> object stored in the DataflowToolRegistry, so this should not return anything
- L59 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);` — Add or remove commands relevant to Tool to the given UICommandList. Call this when the active tool changes (eg on ToolManager.OnToolStarted / OnToolEnded) @param bUnbind if true, commands are removed, otherwise added
- L61 _public member_ `TSharedPtr<FUICommandInfo> EvaluateNode;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> EvaluateGraph;`
- L63 _public member_ `TSharedPtr<FUICommandInfo> ToggleSimulation;`
- L64 _public member_ `TSharedPtr<FUICommandInfo> StartSimulation;`
- L65 _public member_ `TSharedPtr<FUICommandInfo> PauseSimulation;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> StepSimulation;`
- L67 _public member_ `TSharedPtr<FUICommandInfo> ResetSimulation;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> StopSimulation;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> EvaluateGraphAutomatic;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> EvaluateGraphManual;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> ClearGraphCache;`
- L72 _public member_ `TSharedPtr<FUICommandInfo> TogglePerfData;`
- L73 _public member_ `TSharedPtr<FUICommandInfo> FreezeNodes;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> UnfreezeNodes;`
- L75 _public member_ `TSharedPtr<FUICommandInfo> CreateComment;`
- L76 _public member_ `TSharedPtr<FUICommandInfo> ToggleEnabledState;`
- L77 _public member_ `TSharedPtr<FUICommandInfo> ToggleObjectSelection;`
- L78 _public member_ `TSharedPtr<FUICommandInfo> ToggleFaceSelection;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> ToggleVertexSelection;`
- L80 _public member_ `TSharedPtr<FUICommandInfo> AddOptionPin;`
- L81 _public member_ `TSharedPtr<FUICommandInfo> RemoveOptionPin;`
- L82 _public member_ `TSharedPtr<FUICommandInfo> ZoomToFitGraph;`
- L83 _public member_ `TSharedPtr<FUICommandInfo> AddNewVariable;`
- L84 _public member_ `TSharedPtr<FUICommandInfo> AddNewSubGraph;`
- L85 _public member_ `TSharedPtr<FUICommandInfo> ConvertToBasicSubGraph;`
- L86 _public member_ `TSharedPtr<FUICommandInfo> ConvertToForEachSubGraph;`
- L87 _public member_ `TSharedPtr<FUICommandInfo> ToggleAsyncEvaluation;`
- L88 _public member_ `TSharedPtr<FUICommandInfo> CollapseToSubGraph;`
- L89 _public member_ `TSharedPtr<FUICommandInfo> ConvertToEmbeddedDataflow;`
- L90 _public member_ `TSharedPtr<FUICommandInfo> ConvertToExternalDataflow;`
- L91 _public member_ `TSharedPtr<FUICommandInfo> ToggleDataflowEditingLock;`
- L93 _public member_ `TMap<FName, TSharedPtr<FUICommandInfo>> SetConstructionViewModeCommands;`
- L94 _public member_ `TMap<FName, TSharedPtr<FUICommandInfo>> ToolPaletteCommands;`
- L97 _public member_ `const static FString BeginWeightMapPaintToolIdentifier;` — `UE_DEPRECATED(5.5, "Dataflow Tool commands are now stored in FDataflowToolRegistry")`
- L99 _public member_ `TSharedPtr<FUICommandInfo> BeginWeightMapPaintTool;` — `UE_DEPRECATED(5.5, "Dataflow Tool commands are now stored in FDataflowToolRegistry")`
- L101 _public member_ `const static FString AddWeightMapNodeIdentifier;`
- L102 _public member_ `TSharedPtr<FUICommandInfo> AddWeightMapNode;`

#### class `FDataflowEditorCommands`  
`class FDataflowEditorCommands`  
_L106-205_
- desc: @todo(brice) Merge this into the above class
- L110 _public typedef_ `typedef TFunction<void(const FDataflowNode*, const FDataflowOutput*)> FGraphEvaluationCallback;` — `UE_DEPRECATED(5.8, "Use SDataflowGraphEditor::FGraphEvaluationCallback instead ")`
- L113 _public typedef_ `typedef TFunction<void(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)> FOnDragDropEventCallback;` — `UE_DEPRECATED(5.8, "Use SDataflowGraphEditor::FOnDragDropEventCallback instead ")`
- L115 _public prototype_ `static void Register();`
- L116 _public prototype_ `static void Unregister();`
- L117 _public prototype_ `static bool IsRegistered();`
- L119 _public prototype_ `static const FDataflowEditorCommandsImpl& Get();`
- L133 _public prototype_ `static const FDataflowNode* EvaluateNode(UE::Dataflow::FContext& Context, UE::Dataflow::FTimestamp& InOutLastNodeTimestamp, const UDataflow* Dataflow, const FDataflowNode* Node, const FDataflowOutput* Output = nullptr, const FString& NodeName = FString(), UObject* Asset = nullptr);` — Node evaluation utility function. @param Context  The evaluation context. @param InOutLastNodeTimestamp  The last evaluation time used to trigger the evaluation when the node's timestamp is more recent than this value. If the node is evaluated, the value also gets updated with the evaluated node's current timestamp. @param Dataflow  The dataflow asset used to search for the NodeName when Node is nullptr. @param Node  The node to evaluate. When null, a node with the given NodeName will be evaluated instead if it exists. @param Output  The node's output to evaluate. When no output are specified, all outputs will be evaluated. @param NodeName  When no node is specified, then the node will be searched instead within the Dataflow's graph using NodeName, otherwise NodeName is ignored. @param Asset  When Asset is non null, if the node is a terminal node, and if the node timestamp is more recent than InOutLastNodeTimestamp. then the node SetAssetValue method will be called on this asset. @return  The node that has been evaluated if any.
- L137 _public prototype_ `static void EvaluateNode(UE::Dataflow::FContext& Context, const FDataflowNode& Node, const FDataflowOutput* Output, UObject* Asset, UE::Dataflow::FTimestamp& InOutLastNodeTimestamp, UE::Dataflow::FOnPostEvaluationFunction OnEvaluationCompleted);`
- L142 _public prototype_ `static void DeleteNodes(UEdGraph* EdGraph, const FGraphPanelSelectionSet& SelectedNodes);` — DeleteNodes
- L147 _public prototype_ `static void FreezeNodes(UE::Dataflow::FContext& Context, const FGraphPanelSelectionSet& SelectedNodes);` — FreezeNodes
- L152 _public prototype_ `static void UnfreezeNodes(UE::Dataflow::FContext& Context, const FGraphPanelSelectionSet& SelectedNodes);` — UnfreezeNodes
- L157 _public prototype_ `static bool OnNodeVerifyTitleCommit(const FText& NewText, UEdGraphNode* GraphNode, FText& OutErrorMessage);` — OnNodeVerifyTitleCommit
- L162 _public prototype_ `static void OnNodeTitleCommitted(const FText& InNewText, ETextCommit::Type InCommitType, UEdGraphNode* GraphNode);` — OnNodeTitleCommitted
- L167 _public prototype_ `static void OnNotifyPropertyPreChange(TSharedPtr<IStructureDetailsView> PropertiesEditor, UDataflow* Graph, class FEditPropertyChain* PropertyAboutToChange);` — OnNotifyPropertyPreChange
- L172 _public prototype_ `static void OnPropertyValueChanged(UDataflow* Graph, TSharedPtr<UE::Dataflow::FEngineContext>& Context, UE::Dataflow::FTimestamp& OutLastNodeTimestamp, const FPropertyChangedEvent& PropertyChangedEvent, const TSet<TObjectPtr<UDataflowEdNode>>& NewSelection = {});` — OnPropertyValueChanged
- L173 _public prototype_ `static void OnCommentPropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent, const TSet<TObjectPtr<UEdGraphNode_Comment>>& CommentSelection = {});`
- L174 _public prototype_ `static void OnAssetPropertyValueChanged(TObjectPtr<UDataflowBaseContent> Content, const FPropertyChangedEvent& PropertyChangedEvent);`
- L179 _public prototype_ `static void OnSelectedNodesChanged(TSharedPtr<IStructureDetailsView> PropertiesEditor, UObject* Asset, UDataflow* Graph, const TSet<TObjectPtr<UObject>>& NewSelection);` — OnSelectedNodesChanged
- L184 _public prototype_ `static void ToggleEnabledState(UDataflow* Graph);` — ToggleEnabledState
- L189 _public prototype_ `static void DuplicateNodes(UEdGraph* EdGraph, const TSharedPtr<SDataflowGraphEditor>& DataflowGraphEditor, const FGraphPanelSelectionSet& SelectedNodes);` — DuplicateNodes
- L194 _public prototype_ `static void CopyNodes(UEdGraph* EdGraph, const TSharedPtr<SDataflowGraphEditor>& DataflowGraphEditor, const FGraphPanelSelectionSet& SelectedNodes);` — CopyNodes
- L199 _public prototype_ `static void PasteNodes(UEdGraph* EdGraph, const TSharedPtr<SDataflowGraphEditor>& DataflowGraphEditor);` — PasteSelectedNodes
- L204 _public prototype_ `static void RenameNode(const TSharedPtr<SDataflowGraphEditor>& DataflowGraphEditor, UEdGraphNode* EdNode);` — RenameNode

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L25 _typedef_ `typedef TSet<class UObject*> FGraphPanelSelectionSet;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditorModeUILayer.h` (Public)


#### class `UDataflowEditorUISubsystem`  
`class UDataflowEditorUISubsystem : public UAssetEditorUISubsystem`  
_L12-24_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAssetEditorUISubsystem`
- desc: Interchange layer to manage built in tab locations within the editor's layout.
- L17 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L18 _public prototype_ `virtual void Deinitialize() override;`
- L19 _public prototype_ `virtual void RegisterLayoutExtensions(FLayoutExtender& Extender) override;`
- L22 _public member_ `static const FName EditorSidePanelAreaName;` — Identifier for the Layout extension in DataflowEditorToolkit's StandaloneDefaultLayout

#### class `FDataflowEditorModeUILayer`  
`class FDataflowEditorModeUILayer : public FBaseCharacterFXEditorModeUILayer`  
_L27-31_
- inherits: `FBaseCharacterFXEditorModeUILayer`
- desc: Handles the hosting of additional toolkits, such as the mode toolkit, within the DataflowEditor's toolkit.
- L30 _public function_ `FDataflowEditorModeUILayer(const IToolkitHost* InToolkitHost) : FBaseCharacterFXEditorModeUILayer(InToolkitHost)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditorModule.h` (Public)


#### class `FDataflowEditorModule`  
`class FDataflowEditorModule : public FBaseCharacterFXEditorModule`  
_L16-32_
- inherits: `FBaseCharacterFXEditorModule`
- desc: The public interface to this module
- L20 _public member_ `static const FColor SurfaceColor;`
- L23 _public prototype_ `virtual void StartupModule();` — IModuleInterface implementation
- L24 _public prototype_ `virtual void ShutdownModule();`
- L28 _private member_ `TSharedPtr<FDataflowSNodeFactory> DataflowSNodeFactory;`
- L29 _private member_ `FDelegateHandle AssetViewExtraStateGeneratorHandle;`
- L30 _private member_ `FDelegateHandle SkeletalMeshDataflowMenusHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditorPreviewSceneBase.h` (Public)


#### struct `FDataflowConstructionObjectTag`  
`struct FDataflowConstructionObjectTag final : public FEditorDataStorageTag`  
_L24-27_
- reflection: `USTRUCT(meta = (DisplayName = "Dataflow construction object"))`
- inherits: `FEditorDataStorageTag`
- desc: TEDS tag added to any object that belongs to dataflow construction scene

#### struct `FDataflowSimulationObjectTag`  
`struct FDataflowSimulationObjectTag final : public FEditorDataStorageTag`  
_L33-36_
- reflection: `USTRUCT(meta = (DisplayName = "Dataflow simulation object"))`
- inherits: `FEditorDataStorageTag`
- desc: TEDS tag added to any object that belongs to dataflow simulation scene

#### struct `FDataflowSceneObjectTag`  
`struct FDataflowSceneObjectTag final : public FEditorDataStorageTag`  
_L42-45_
- reflection: `USTRUCT(meta = (DisplayName = "Dataflow scene object", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`
- desc: TEDS tag added to any object that belongs to dataflow scene

#### struct `FDataflowSceneStructTag`  
`struct FDataflowSceneStructTag final : public FEditorDataStorageTag`  
_L51-54_
- reflection: `USTRUCT(meta = (DisplayName = "Dataflow scene struct", EditorDataStorage_DynamicColumnTemplate))`
- inherits: `FEditorDataStorageTag`
- desc: TEDS tag added to any struct that belongs to dataflow scene

#### struct `FDataflowSceneTypeColumn`  
`struct FDataflowSceneTypeColumn final : public FEditorDataStorageColumn`  
_L60-67_
- reflection: `USTRUCT(meta = (DisplayName = "Dataflow scene type"))`
- inherits: `FEditorDataStorageColumn`
- desc: TEDS column added to any struct/scene to display the type (construction/simulation/evaluation)
- L66 _public member_ `int32 SceneType = 0;`

#### class `FDataflowPreviewSceneBase`  
`class FDataflowPreviewSceneBase : public FAdvancedPreviewScene`  
_L78-192_
- inherits: `FAdvancedPreviewScene`
- desc: Dataflow preview scene base @brief the scene is holding all the objects that will be visible and potentially editable within the viewport
- L82 _public prototype_ `FDataflowPreviewSceneBase(FPreviewScene::ConstructionValues ConstructionValues, UDataflowEditor* Editor, const FName& InActorName);`
- L83 _public prototype_ `virtual ~FDataflowPreviewSceneBase();`
- L86 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L89 _public prototype_ `TObjectPtr<UDataflowBaseContent>& GetEditorContent();` — Dataflow editor content accessors
- L90 _public prototype_ `const TObjectPtr<UDataflowBaseContent>& GetEditorContent() const;`
- L93 _public prototype_ `TArray<TObjectPtr<UDataflowBaseContent>>& GetTerminalContents();` — Dataflow terminal contents accessors
- L94 _public prototype_ `const TArray<TObjectPtr<UDataflowBaseContent>>& GetTerminalContents() const;`
- L97 _public function_ `TObjectPtr<AActor> GetRootActor()` — Root scene actor accessors
- L98 _public function_ `const TObjectPtr<AActor> GetRootActor() const`
- L101 _public function_ `TSharedPtr<FAssetEditorModeManager>& GetDataflowModeManager()` — Dataflow mode manager accessors
- L102 _public function_ `const TSharedPtr<FAssetEditorModeManager>& GetDataflowModeManager() const`
- L105 _public prototype_ `virtual FBox GetBoundingBox() const;` — Build the scene bounding box
- L108 _public function_ `const IDataflowDebugDrawInterface::FDataflowElementsType& GetSceneElements() const` — Get const scene elements
- L111 _public function_ `IDataflowDebugDrawInterface::FDataflowElementsType& ModifySceneElements()` — Get non const scene elements
- L114 _public function_ `const TObjectPtr<class UDataflowDebugDrawComponent>& GetDebugDrawComponent() const` — Get const debug draw component
- L117 _public function_ `TObjectPtr<class UDataflowDebugDrawComponent>& ModifyDebugDrawComponent()` — Get non const debug draw component
- L120 _public function_ `virtual void TickDataflowScene(const float DeltaSeconds)` — Tick data flow scene
- L123 _public prototype_ `bool IsComponentSelected(const UPrimitiveComponent* InComponent) const;` — Check if a primitive component is selected
- L126 _public function_ `virtual bool CanRunSimulation() const` — Check if the preview scene can run simulation
- L129 _public prototype_ `void SetCurrentProfileIndex(int32 NewProfileIndex);` — Update the currently selected scene profile
- L132 _public function_ `bool IsSceneDirty() const` — Return true if the preview scene is dirty
- L135 _public function_ `void SetDirtyFlag()` — Set the dirty flag
- L138 _public function_ `void ResetDirtyFlag()` — Reset the dirty flag
- L141 _public function_ `FDataflowFocusRequestDelegate& OnFocusRequest()` — Event triggered when an object is focused in the scene (double-click in the scene outliner)
- L144 _public prototype_ `void RegisterSceneElements(const bool bIsConstruction);` — Register all the scene elements to TEDs
- L147 _public prototype_ `void UnregisterSceneElements();` — Unregister all the scene elements to TEDs
- L150 _public prototype_ `USelection* GetSelectedComponents() const;` — Return the scene selected components
- L153 _public function_ `const UDataflowEditor* GetDataflowEditor() const` — Get the dataflow editor
- L158 _protected prototype_ `void AddSceneObject(UObject* SceneObject, const bool bIsConstruction) const;` — Store Scene object into the TEDS database
- L161 _protected prototype_ `void AddSceneStruct(void* SceneStruct, const TWeakObjectPtr<const UScriptStruct> TypeInfo, const bool bIsConstruction) const;` — Store Scene struct into the TEDS database
- L164 _protected prototype_ `void RemoveSceneObject(UObject* SceneObject) const;` — Remove Scene object from the TEDS database
- L167 _protected prototype_ `void RemoveSceneStruct(void* SceneStruct) const;` — Remove Scene struct from the TEDS database
- L170 _protected prototype_ `void OnAssetViewerSettingsRefresh(const FName& InPropertyName);` — Respond to changes in the scene profile settings
- L173 _protected member_ `TObjectPtr<AActor> RootSceneActor = nullptr;` — Root scene actor
- L176 _protected member_ `UDataflowEditor* DataflowEditor = nullptr;` — Dataflow editor linked to that preview scene
- L179 _protected member_ `TSharedPtr<FAssetEditorModeManager> DataflowModeManager;` — Mode Manager for selection
- L182 _protected member_ `bool bPreviewSceneDirty = false;` — Boolean to check if the preview scene is dirty or not
- L185 _protected member_ `FDataflowFocusRequestDelegate FocusRequestDelegate;` — Delegate to focus the viewport
- L188 _protected member_ `IDataflowDebugDrawInterface::FDataflowElementsType SceneElements;` — List of scene elements that could be used in the editor (outliner/viewport...)
- L191 _protected member_ `TObjectPtr<class UDataflowDebugDrawComponent> DebugDrawComponent;` — Persistent component used for debug drawing

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L71 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FDataflowFocusRequestDelegate, const FBox&) class FDataflowPreviewSceneBase : public FAdvancedPreviewScene { public: FDataflowPreviewSceneBase(FPreviewScene::ConstructionValues ConstructionValues, UDataflowEditor* Editor, const FName& InActorName); virtual ~FDataflowPreviewSceneBase();` — Dataflow focus request delegate

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditorToolkit.h` (Public)


#### struct `UE::Dataflow::Private::FLogMessageStorage`  
`struct FLogMessageStorage`  
_L54-73_
- desc: stores the log message per node and
- L57 _public prototype_ `void Add(const UE::Dataflow::FContext::FLogMessage& Message);`
- L58 _public prototype_ `void RemoveForNode(const FDataflowNode& Node, const FTimestamp& Timestamp = FTimestamp::Invalid);`
- L59 _public prototype_ `void GetMessageForNode(const FDataflowNode& Node, TArray<UE::Dataflow::FContext::FLogMessage>& OutMessages) const;`
- L60 _public prototype_ `EMessageSeverity::Type GetMaxSeverityForNode(const FDataflowNode& Node) const;`
- L61 _public function_ `int32 Num() const`
- L62 _public prototype_ `void GetMessage(int32 Index, UE::Dataflow::FContext::FLogMessage& OutMessage) const;`
- L63 _public prototype_ `EMessageSeverity::Type GetMaxSeverity();`
- L72 _private member_ `TArray<FEntry> Entries;`

#### struct `UE::Dataflow::Private::FLogMessageStorage::FEntry`  
`struct FEntry`  
_L66-70_
- L68 _public member_ `UE::Dataflow::FTimestamp Timestamp;`
- L69 _public member_ `UE::Dataflow::FContext::FLogMessage Message;`

#### class `UDataflowEvaluationSettings`  
`class UDataflowEvaluationSettings : public UDataflowEditorSettings`  
_L80-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowEditorSettings`
- L86 _public member_ `bool bAllowEvaluationInPIE = false;` — `UPROPERTY()`

#### class `FDataflowEditorToolkit`  
`class FDataflowEditorToolkit final : public FBaseCharacterFXEditorToolkit, public FTickableEditorObject, public FNotifyHook, public FGCObject`  
_L89-479_
- inherits: `FBaseCharacterFXEditorToolkit,FTickableEditorObject,FNotifyHook,FGCObject`
- L95 _public prototype_ `explicit FDataflowEditorToolkit(UAssetEditor* InOwningAssetEditor);`
- L96 _public prototype_ `~FDataflowEditorToolkit();`
- L98 _public prototype_ `static bool CanOpenDataflowEditor(UObject* ObjectToEdit);`
- L99 _public prototype_ `static bool HasDataflowAsset(UObject* ObjectToEdit);`
- L100 _public prototype_ `static UDataflow* GetDataflowAsset(UObject* ObjectToEdit);`
- L101 _public prototype_ `static const UDataflow* GetDataflowAsset(const UObject* ObjectToEdit);`
- L102 _public prototype_ `bool IsSimulationDataflowAsset() const;`
- L103 _public prototype_ `FName GetGraphLogName() const;`
- L104 _public prototype_ `void LogMessage(const EMessageSeverity::Type Severity, const FDataflowNode* Node, const FDataflowOutput* Output, const FString& Message) const;`
- L105 _public prototype_ `void LogMessage(const EMessageSeverity::Type Severity, const FDataflowNode* Node, const FDataflowOutput* Output, const FText& Message) const;`
- L108 _public prototype_ `const TObjectPtr<UDataflowBaseContent>& GetEditorContent() const;` — Editor dataflow content accessors
- L109 _public prototype_ `TObjectPtr<UDataflowBaseContent>& GetEditorContent();`
- L112 _public prototype_ `const TArray<TObjectPtr<UDataflowBaseContent>>& GetTerminalContents() const;` — Terminal dataflow contents accessors
- L113 _public prototype_ `TArray<TObjectPtr<UDataflowBaseContent>>& GetTerminalContents();`
- L116 _public function_ `const TSharedPtr<SDataflowGraphEditor> GetDataflowGraphEditor() const` — Dataflow graph editor accessor
- L119 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L120 _public prototype_ `virtual FText GetToolkitName() const override;`
- L121 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L122 _public prototype_ `virtual FText GetToolkitToolTipText() const override;`
- L123 _public prototype_ `virtual FString GetWorldCentricTabPrefix() const override;`
- L124 _public prototype_ `virtual FLinearColor GetWorldCentricTabColorScale() const override;`
- L125 _public prototype_ `virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;`
- L126 _public prototype_ `virtual void UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) override;`
- L129 _public function_ `const TSharedPtr<FDataflowSimulationScene>& GetSimulationScene() const` — Dataflow preview scenes accessor
- L130 _public function_ `const TSharedPtr<FDataflowConstructionScene>& GetConstructionScene() const`
- L131 _public function_ `const TSharedPtr<FDataflowSimulationSceneProfileIndexStorage>& GetSimulationSceneProfileIndexStorage() const`
- L134 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FSerializableObject interface
- L135 _public function_ `virtual FString GetReferencerName() const override`
- L141 _public prototype_ `void OpenSubGraphTab(FName SubGraphName);`
- L142 _public prototype_ `void OpenSubGraphTab(const UDataflowSubGraph* SubGraph);`
- L143 _public prototype_ `void CloseSubGraphTab(const UDataflowSubGraph* SubGraph);`
- L144 _public prototype_ `void ReOpenSubGraphTab(const UDataflowSubGraph* SubGraph);`
- L145 _public prototype_ `void SetSubGraphTabActiveState(TSharedPtr<SDataflowGraphEditor> SubGraphEditor, bool bActive);`
- L146 _public prototype_ `UDataflowSubGraph* GetSubGraph(const FGuid& SubGraphGuid) const;`
- L147 _public prototype_ `UDataflowSubGraph* GetSubGraph(FName SubGraphName) const;`
- L149 _public prototype_ `FGuid FocusOnNextVariableNode(FName VariableName, const FGuid& LastTimeNodeGuid);`
- L150 _public prototype_ `void FindAllVariableNodeInGraph(UEdGraph* EdGraph, FName VariableName, TArray<UDataflowEdNode*>& OutEdNodes);`
- L152 _public prototype_ `const FString& GetDebugDrawOverlayString() const;`
- L155 _public prototype_ `void DrawPropertyGizmoLabels(FCanvas* Canvas, const FSceneView* SceneView) const;` — Draw property name labels at gizmo origins for the currently selected node. Call from viewport DrawCanvas.
- L157 _public prototype_ `void OnConstructionViewModeChanged(const UE::Dataflow::IDataflowConstructionViewMode* NewConstructionViewMode);`
- L159 _public prototype_ `void OnDataflowAssetChanged();`
- L162 _public function_ `const EDataflowEditorEvaluationMode& GetEvaluationMode() const` — Get the toolkit evaluation mode
- L165 _public prototype_ `void ResetDataflowSimulation() const;` — Reset dataflow simulation
- L168 _public prototype_ `void ToggleDataflowSimulation() const;` — Toggle dataflow simulation
- L171 _public prototype_ `void StartDataflowSimulation() const;` — Start dataflow simulation
- L174 _public prototype_ `void StopDataflowSimulation() const;` — Stop dataflow simulation
- L177 _public prototype_ `void StepDataflowSimulation() const;` — Step dataflow simulation
- L180 _public prototype_ `void PauseDataflowSimulation() const;` — Pause dataflow simulation
- L183 _public prototype_ `bool HasSimulationManager() const;` — Check if the simulation can be toggled or not
- L186 _public prototype_ `bool IsSimulationEnabled() const;` — Check if the simulation is enabled or not
- L189 _public prototype_ `bool IsSimulationDisabled() const;` — Check if the simulation is disabled or not
- L193 _protected member_ `UDataflowEditor* DataflowEditor = nullptr;`
- L196 _protected prototype_ `void OnPropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);` — List of dataflow actions callbacks
- L197 _protected prototype_ `bool OnNodeVerifyTitleCommit(const FText& NewText, UEdGraphNode* GraphNode, FText& OutErrorMessage);`
- L198 _protected prototype_ `void OnNodeTitleCommitted(const FText& InNewText, ETextCommit::Type InCommitType, UEdGraphNode* GraphNode);`
- L199 _protected prototype_ `void OnNodeDoubleClicked(UEdGraphNode* ClickedNode);`
- L200 _protected prototype_ `void OnNodeSelectionChanged(const TSet<UObject*>& NewSelection);`
- L201 _protected prototype_ `void OnNodeInvalidated(UDataflow& DataflowAsset, FDataflowNode& Node);`
- L202 _protected prototype_ `void OnNodeDeleted(const TSet<UObject*>& NewSelection);`
- L203 _protected prototype_ `void OnAssetPropertyValueChanged(const FPropertyChangedEvent& PropertyChangedEvent);`
- L204 _protected prototype_ `void OnConstructionViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements);`
- L205 _protected prototype_ `void OnSimulationViewSelectionChanged(const TArray<UPrimitiveComponent*>& SelectedComponents, const TArray<FDataflowBaseElement*>& SelectedElements);`
- L207 _protected prototype_ `void OnTabClosed(TSharedRef<SDockTab> Tab);` — Callback to remove the closed one from the listener views
- L210 _protected prototype_ `void EvaluateTerminalNode(const FDataflowTerminalNode& TerminalNode);` — Node evaluation
- L211 _protected prototype_ `void EvaluateNode(const FDataflowNode* Node, const FDataflowOutput* Output, UE::Dataflow::FTimestamp& InOutTimestamp);`
- L212 _protected prototype_ `void EvaluateGraph();`
- L213 _protected prototype_ `void RefreshViewsIfNeeded(bool bForce = false);`
- L214 _protected prototype_ `void OnNodeBeginEvaluate(const FDataflowNode* Node, const FDataflowOutput* Output);`
- L215 _protected prototype_ `void OnNodeFinishEvaluate(const FDataflowNode* Node, const FDataflowOutput* Output);`
- L216 _protected prototype_ `void OnOutputLogMessageTokenClicked(const FString TokenString);`
- L217 _protected prototype_ `void OnContextLog(const UE::Dataflow::FContext::FLogMessage& InLogMessage);`
- L218 _protected prototype_ `void RefreshLogMessageView();`
- L223 _private prototype_ `TSharedRef<SDockTab> SpawnTab_GraphCanvas(const FSpawnTabArgs& Args);` — Spawning of all the additional tabs (viewport,details ones are coming from the base asset toolkit)
- L224 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SubGraphTab(const FSpawnTabArgs& Args);`
- L225 _private prototype_ `TSharedRef<SDockTab> SpawnTab_NodeDetails(const FSpawnTabArgs& Args);`
- L226 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SkeletonView(const FSpawnTabArgs& Args);`
- L227 _private prototype_ `TSharedRef<SDockTab> SpawnTab_OutlinerView(const FSpawnTabArgs& Args);`
- L228 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SelectionView(const FSpawnTabArgs& Args);`
- L229 _private prototype_ `TSharedRef<SDockTab> SpawnTab_CollectionSpreadSheet(const FSpawnTabArgs& Args);`
- L230 _private prototype_ `TSharedRef<SDockTab> SpawnTab_AssetDetails(const FSpawnTabArgs& Args);`
- L231 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SimulationViewport(const FSpawnTabArgs& Args);`
- L232 _private prototype_ `TSharedRef<SDockTab> SpawnTab_PreviewScene(const FSpawnTabArgs& Args);`
- L233 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SimulationVisualization(const FSpawnTabArgs& Args);`
- L234 _private prototype_ `TSharedRef<SDockTab> SpawnTab_MembersWidget(const FSpawnTabArgs& Args);`
- L235 _private prototype_ `TSharedRef<SDockTab> SpawnTab_OutputLog(const FSpawnTabArgs& Args);`
- L236 _private prototype_ `TSharedRef<SDockTab> SpawnTab_SimulationTimeline(const FSpawnTabArgs& Args);`
- L239 _private prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableEditorObject interface
- L240 _private function_ `virtual bool IsTickable() const override`
- L241 _private prototype_ `virtual TStatId GetStatId() const override;`
- L244 _private prototype_ `virtual FEditorModeID GetEditorModeId() const override;` — FBaseCharacterFXEditorToolkit interface
- L245 _private prototype_ `virtual void InitializeEdMode(UBaseCharacterFXEditorMode* EdMode) override;`
- L246 _private prototype_ `virtual void CreateEditorModeUILayer() override;`
- L249 _private prototype_ `virtual bool OnRequestClose(EAssetEditorCloseReason InCloseReason) override;` — FAssetEditorToolkit interface
- L250 _private prototype_ `virtual void OnClose() override;`
- L251 _private prototype_ `virtual void PostInitAssetEditor() override;`
- L252 _private prototype_ `virtual void GetSaveableObjects(TArray<UObject*>& OutObjects) const override;`
- L253 _private prototype_ `virtual void OnAssetsSavedAs(const TArray<UObject*>& SavedObjects) override;`
- L254 _private prototype_ `virtual bool ShouldReopenEditorForSavedAsset(const UObject* Asset) const override;`
- L257 _private prototype_ `virtual void CreateWidgets() override;` — FBaseAssetToolkit interface
- L258 _private prototype_ `virtual AssetEditorViewportFactoryFunction GetViewportDelegate() override;`
- L259 _private prototype_ `virtual TSharedPtr<FEditorViewportClient> CreateEditorViewportClient() const override;`
- L260 _private prototype_ `virtual void CreateEditorModeManager() override;`
- L262 _private prototype_ `void UpdateGizmos();`
- L265 _private prototype_ `virtual void NotifyPreChange(class FEditPropertyChain* PropertyAboutToChange) override;` — FNotifyHook
- L268 _private member_ `static const FName GraphCanvasTabId;` — List of all the tab names ids that will be used to identify the editor widgets
- L269 _private member_ `static const FName SubGraphCanvasTabId;`
- L270 _private member_ `static const FName NodeDetailsTabId;`
- L271 _private member_ `static const FName SkeletonViewTabId;`
- L272 _private member_ `static const FName OutlinerViewTabId;`
- L273 _private member_ `static const FName SelectionViewTabId_1;`
- L274 _private member_ `static const FName SelectionViewTabId_2;`
- L275 _private member_ `static const FName SelectionViewTabId_3;`
- L276 _private member_ `static const FName SelectionViewTabId_4;`
- L277 _private member_ `static const FName CollectionSpreadSheetTabId_1;`
- L278 _private member_ `static const FName CollectionSpreadSheetTabId_2;`
- L279 _private member_ `static const FName CollectionSpreadSheetTabId_3;`
- L280 _private member_ `static const FName CollectionSpreadSheetTabId_4;`
- L281 _private member_ `static const FName SimulationViewportTabId;`
- L282 _private member_ `static const FName PreviewSceneTabId;`
- L283 _private member_ `static const FName SimulationVisualizationTabId;`
- L284 _private member_ `static const FName SimulationTimelineTabId;`
- L285 _private member_ `static const FName MembersWidgetTabId;`
- L286 _private member_ `static const FName OutputLogTabId;`
- L289 _private member_ `TSharedPtr<SDataflowConstructionViewport> DataflowConstructionViewport;` — List of all the widgets shared ptr that will be built in the editor
- L290 _private member_ `TSharedPtr<SDataflowSimulationViewport> DataflowSimulationViewport;`
- L291 _private member_ `TSharedPtr<SDataflowGraphEditor> GraphEditor;`
- L292 _private member_ `TSharedPtr<SDockTab> GraphEditorTab;`
- L293 _private member_ `TSharedPtr<IStructureDetailsView> NodeDetailsEditor;`
- L294 _private member_ `TSharedPtr<SDataflowMembersWidget> MembersWidget;`
- L295 _private member_ `TSharedPtr<UE::Dataflow::FDataflowNodeDetailExtensionHandler> NodeDetailsExtensionHandler;`
- L296 _private member_ `TSharedPtr<FDataflowSkeletonView> SkeletonEditorView;`
- L297 _private member_ `TSharedPtr<FDataflowOutlinerView> DataflowOutlinerView;`
- L298 _private member_ `TSharedPtr<IDetailsView> AssetDetailsEditor;`
- L299 _private member_ `TSharedPtr<FDataflowSelectionView> DataflowSelectionView_1;`
- L300 _private member_ `TSharedPtr<FDataflowSelectionView> DataflowSelectionView_2;`
- L301 _private member_ `TSharedPtr<FDataflowSelectionView> DataflowSelectionView_3;`
- L302 _private member_ `TSharedPtr<FDataflowSelectionView> DataflowSelectionView_4;`
- L303 _private member_ `TSharedPtr<FDataflowCollectionSpreadSheet> DataflowCollectionSpreadSheet_1;`
- L304 _private member_ `TSharedPtr<FDataflowCollectionSpreadSheet> DataflowCollectionSpreadSheet_2;`
- L305 _private member_ `TSharedPtr<FDataflowCollectionSpreadSheet> DataflowCollectionSpreadSheet_3;`
- L306 _private member_ `TSharedPtr<FDataflowCollectionSpreadSheet> DataflowCollectionSpreadSheet_4;`
- L307 _private member_ `TSharedPtr<SWidget> AdvancedPreviewSettingsWidget;`
- L308 _private member_ `TSharedPtr<SWidget> SimulationVisualizationWidget;`
- L309 _private member_ `TSharedPtr<SDataflowSimulationTimeline> SimulationTimelineWidget;`
- L310 _private member_ `TSharedPtr<FDataflowOutputLog> DataflowOutputLog;`
- L313 _private prototype_ `TSharedRef<class IDetailCustomization> CustomizePreviewSceneDescription() const;` — Customize preview scene with editor/terminal contents
- L315 _private prototype_ `TSharedRef<class IDetailCustomization> CustomizeAssetViewer() const;`
- L318 _private prototype_ `TSharedRef<SDataflowGraphEditor> CreateGraphEditorWidget(UEdGraph* GraphToEdit, TSharedPtr<IStructureDetailsView> PropertiesEditor);` — Utility factory functions to build the widgets
- L319 _private prototype_ `TSharedPtr<IDetailsView> CreateAssetDetailsEditorWidget(const TArray<UObject*>& ObjectsToEdit);`
- L320 _private prototype_ `TSharedPtr<SWidget> CreateSimulationVisualizationWidget();`
- L321 _private prototype_ `TSharedPtr<IStructureDetailsView> CreateNodeDetailsEditorWidget(UObject* ObjectToEdit);`
- L322 _private prototype_ `TSharedPtr<SDataflowMembersWidget> CreateDataflowMembersWidget();`
- L323 _private prototype_ `TSharedRef<SGraphEditor> CreateSubGraphEditorWidget(TSharedRef<FTabInfo> InTabInfo, UDataflowSubGraph* InGraph);`
- L325 _private prototype_ `void AddEvaluationWidget(FToolMenuSection& Section);`
- L326 _private prototype_ `TSharedRef<SWidget> GenerateEvaluationOptionsMenu();`
- L327 _private prototype_ `FSlateIcon GetEvaluationStatusImage() const;`
- L328 _private prototype_ `bool IsGraphDirty() const;`
- L329 _private prototype_ `bool IsEvaluateButtonEnabled() const;`
- L331 _private prototype_ `void SetEvaluateGraphMode(EDataflowEditorEvaluationMode Mode);`
- L332 _private prototype_ `void ClearGraphCache();`
- L333 _private prototype_ `bool CanClearGraphCache() const;`
- L334 _private prototype_ `void TogglePerfData();`
- L335 _private prototype_ `bool IsPerfDataEnabled() const;`
- L336 _private prototype_ `void ToggleAsyncEvaluation();`
- L337 _private prototype_ `bool IsAsyncEvaluationEnabled() const;`
- L340 _private prototype_ `void CreateSimulationViewportClient();` — Create the simulation viewport client
- L342 _private prototype_ `void SetDataflowPathFromNodeAndOutput(const FDataflowNode* Node, const FDataflowOutput* Output, FDataflowPath& OutPath) const;`
- L344 _private prototype_ `void RegisterContextHandlers();`
- L345 _private prototype_ `void UnregisterContextHandlers();`
- L348 _private prototype_ `void UpdateDebugDraw();` — Update the debug draw based on a change of currently selected or pinned nodes
- L351 _private prototype_ `void ResetEditor();` — reset the editor. Used when the dataflow graph as changed
- L354 _private prototype_ `void AddDataflowActionWidget(FToolMenuSection& Section);` — This adds the widget to switch from embdedded or external dataflow as well as read - only lock when applicable
- L357 _private prototype_ `bool IsEmbeddedDataflow() const;` — return true if the Dataflow is not an asset and is an object embedded into the owner asset
- L360 _private prototype_ `bool IsExternalDataflow() const;` — return true if the Dataflow is a separate asset or no dataflow is assigned to the owner asset
- L363 _private prototype_ `bool IsReferenceAssetNullOrSameAsBoundAsset() const;` — return true if the bound asset is the reference asset or if the reference asset is null
- L366 _private prototype_ `UObject* GetReferenceAsset() const;` — Get Reference asset from the dataflow graph
- L369 _private prototype_ `bool AllowExternalDataflowEditing() const;` — return true the current dataflow can be edited - condition are must be External and match reference asset (if reference asset is defined)
- L372 _private prototype_ `bool IsEditingLockButtonVisible() const;` — whether the Lock/Unlock editing button is visible or not
- L374 _private prototype_ `bool IsEditable() const;`
- L377 _private prototype_ `void ConvertToEmbeddedDataflow();` — Duplicate the current external dataflow and embed it into the owner asset
- L383 _private prototype_ `void ConvertToExternalDataflow();` — Duplicate the embedded dataflow object and store it into a separate asset this methid is interactive and will prompt a dialog for the user to choose a path to save the duplicated Dataflow to
- L385 _private prototype_ `void ToggleDataflowEditingLock();`
- L387 _private prototype_ `void UpdateViewsFromNode(UDataflowEdNode* Node = nullptr);`
- L388 _private prototype_ `static TSet<TObjectPtr<UDataflowEdNode>> FilterDataflowEdNodesFromSet(const TSet<UObject*>& Set);`
- L389 _private prototype_ `static const TObjectPtr<UDataflowEdNode> GetOnlyFromSet(const TSet<TObjectPtr<UDataflowEdNode>>& Set);`
- L392 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — List of editor commands used  for the dataflow asset
- L395 _private member_ `TArray<IDataflowViewListener*> ViewListeners;` — List of selection view / collection spreadsheet widgets that are listening to any changed in the graph
- L398 _private member_ `FDelegateHandle OnSelectionChangedMulticastDelegateHandle;` — Graph delegates used to update the UI
- L399 _private member_ `FDelegateHandle OnNodeDeletedMulticastDelegateHandle;`
- L400 _private member_ `FDelegateHandle OnEvaluateSelectedNodesDelegateHandle;`
- L401 _private member_ `FDelegateHandle OnFinishedChangingPropertiesDelegateHandle;`
- L402 _private member_ `FDelegateHandle OnFinishedChangingAssetPropertiesDelegateHandle;`
- L403 _private member_ `FDelegateHandle OnConstructionSelectionChangedDelegateHandle;`
- L404 _private member_ `FDelegateHandle OnSimulationSelectionChangedDelegateHandle;`
- L405 _private member_ `FDelegateHandle OnSimulationSceneChangedDelegateHandle;`
- L408 _private member_ `FDelegateHandle OnNodeBeginEvaluateMulticastDelegateHandle;` — Delegates to communicate with Context
- L409 _private member_ `FDelegateHandle OnNodeFinishEvaluateMulticastDelegateHandle;`
- L410 _private member_ `FDelegateHandle OnOutputLogMessageTokenClickedDelegateHandle;`
- L412 _private member_ `FDelegateHandle OnContextLogDelegateHandle;`
- L415 _private member_ `TSet<TObjectPtr<UDataflowEdNode>> SelectedDataflowNodes;` — The currently selected set of dataflow nodes.
- L416 _private member_ `TSet<TObjectPtr<UEdGraphNode_Comment>> SelectedComments;`
- L419 _private member_ `TObjectPtr<UDataflowPropertyGizmoManager> PropertyGizmoManager;` — Manages viewport gizmos for GizmoType-annotated properties on the currently selected node.
- L422 _private member_ `TSharedPtr<FDataflowConstructionScene> ConstructionScene;` — Pointer to the construction viewport scene. Note this is an alias of ObjectScene in FBaseCharacterFXEditorToolkit but with the specific type
- L425 _private member_ `TSharedPtr<FDataflowSimulationScene> SimulationScene;` — PreviewScene showing the objects being simulated
- L427 _private member_ `TSharedPtr<FDataflowSimulationSceneProfileIndexStorage> SimulationSceneProfileIndexStorage;`
- L430 _private member_ `TSharedPtr<FEditorModeTools> SimulationModeManager;` — The editor mode manager used by the simulation preview scene
- L433 _private member_ `TSharedPtr<class FEditorViewportTabContent> SimulationTabContent;` — Simulation tab content
- L436 _private member_ `AssetEditorViewportFactoryFunction SimulationViewportDelegate;` — Simulation viewport delegate
- L439 _private member_ `TSharedPtr<FDataflowSimulationViewportClient> SimulationViewportClient;` — Simulation Viewport client
- L442 _private member_ `TSharedPtr<FTabManager::FLayout> SimulationDefaultLayout;` — Simulation default layout
- L445 _private member_ `TSharedPtr<FTabManager::FLayout> ConstructionDefaultLayout;` — Simulation default layout
- L448 _private member_ `bool bDataflowEnableGraphEval;` — Cached value of the p.Dataflow.EnableGraphEval cvar, to avoid calling FindConsoleVariable too often
- L451 _private member_ `bool bAllowExternalDataflowEditing = false;` — Allow editing of external dataflow
- L454 _private member_ `bool bAllowEvaluationInPIE = false;` — Cached value from the editor evaluation settings
- L456 _private member_ `EDataflowEditorEvaluationMode EvaluationMode;`
- L459 _private member_ `FDelegateHandle GraphEvalCVarChangedDelegateHandle;` — Delegate for updating the cached value of p.Dataflow.EnableGraphEval
- L461 _private member_ `TWeakPtr<SDataflowGraphEditor> ActiveSubGraphEditorWeakPtr;`
- L464 _private member_ `TSharedPtr<FDocumentTracker> DocumentManager;` — Document tracker for dynamic tabs ( like subgraphs )
- L466 _private member_ `TWeakPtr<SDockTab> WeakOutputLogDockTab;`
- L468 _private member_ `TSet<FGuid> NodesToEvaluateOnTick;`
- L471 _private member_ `TSharedRef<UE::Dataflow::Private::FLogMessageStorage> LogMessages;` — relevant message to display
- L473 _private member_ `bool bViewsNeedRefresh = false;`
- L475 _private member_ `FString DebugDrawOverlayString;`
- L478 _private member_ `TSharedPtr<FDataflowSimulationBinding> SimulationBinding;` — Simulation Binding to control the simulation scene from the timeline

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L48 _namespace_ `namespace UE`
- L48 _namespace_ `namespace Dataflow` (scope `UE`)
- L51 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L76 _namespace_ `namespace EMessageSeverity`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowEditorViewportClientBase.h` (Public)


#### class `FDataflowEditorViewportClientBase`  
`class FDataflowEditorViewportClientBase : public FEditorViewportClient, public IInputBehaviorSource`  
_L15-65_
- inherits: `FEditorViewportClient,IInputBehaviorSource`
- L18 _public typedef_ `using Super = FEditorViewportClient;`
- L20 _public prototype_ `FDataflowEditorViewportClientBase(FEditorModeTools* InModeTools, TWeakPtr<FDataflowPreviewSceneBase> InPreviewScene, const bool bCouldTickScene, const TWeakPtr<SEditorViewport> InEditorViewportWidget = nullptr);`
- L22 _public prototype_ `virtual ~FDataflowEditorViewportClientBase();`
- L26 _protected prototype_ `virtual void OnViewportClicked(HHitProxy* HitProxy) = 0;`
- L29 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject
- L32 _protected prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L36 _protected member_ `TWeakPtr<FDataflowPreviewSceneBase> DataflowPreviewScene;` — Dataflow preview scene from the toolkit
- L39 _protected member_ `TArray<TObjectPtr<UInputBehavior>> BaseBehaviors;` — Behaviors defined by this base class
- L42 _protected member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet;` — All behaviors available to the current viewport (subclasses can add to this set)
- L47 _protected prototype_ `void GetSelectedElements(HHitProxy* HitProxy, TArray<FDataflowBaseElement*>& SelectedElements) const;` — Get all the scene selected elements
- L51 _private prototype_ `void HandleFocusRequest(const FBox& BoundingBox);` — Handle the focus request onto the bounding box
- L54 _private prototype_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override;` — IInputBehaviorSource
- L57 _private prototype_ `void RegisterDelegates();` — Called from constructor/destructor to manage callbacks when settings change
- L58 _private prototype_ `void DeregisterDelegates();`
- L61 _private member_ `FDelegateHandle OnAssetViewerSettingsChangedDelegateHandle;` — Handle for callback when preview scene profile settings change
- L64 _private member_ `FDelegateHandle OnFocusRequestDelegateHandle;` — Handle for callback when preview scene focus request is triggered

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowFacesOutlinerWidget.h` (Public)


#### class `FGeometryCollectionFacesTreeItem`  
`class FGeometryCollectionFacesTreeItem : public TSharedFromThis<FGeometryCollectionFacesTreeItem>`  
_L23-33_
- inherits: `TSharedFromThis<FGeometryCollectionFacesTreeItem>`
- L26 _public prototype_ `virtual ~FGeometryCollectionFacesTreeItem() = default;`
- L27 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false) = 0;`
- L28 _public prototype_ `virtual void GetChildren(FGeometryCollectionFacesTreeItemList& OutChildren) = 0;`
- L30 _public function_ `virtual int32 GetFaceIndex() const`
- L32 _public prototype_ `void GenerateContextMenu(UToolMenu* Menu, SFacesOutliner& Outliner);`

#### class `FGeometryCollectionFacesTreeItemGeometry`  
`class FGeometryCollectionFacesTreeItemGeometry : public FGeometryCollectionFacesTreeItem`  
_L35-86_
- inherits: `FGeometryCollectionFacesTreeItem`
- L38 _public function_ `FGeometryCollectionFacesTreeItemGeometry(TSharedPtr<const FManagedArrayCollection> InCollection, int32 InGeoemtryIdx, TSharedPtr<STreeView<FGeometryCollectionFacesTreeItemPtr>> InTreeView) : Collection(InCollection) , GeometryIdx(InGeoemtryIdx) , TreeView(InTreeView)`
- L46 _public prototype_ `virtual ~FGeometryCollectionFacesTreeItemGeometry() = default;`
- L49 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FGeometryCollectionFacesTreeItem interface
- L50 _public prototype_ `virtual void GetChildren(FGeometryCollectionFacesTreeItemList& OutChildren) override;`
- L52 _public prototype_ `FGeometryCollectionFacesTreeItemPtr GetItemFromFaceIndex(int32 InFaceIndex) const;`
- L54 _public prototype_ `void GetChildrenForFace(FGeometryCollectionFacesTreeItemFace& FaceItem, FGeometryCollectionFacesTreeItemList& OutChildren) const;`
- L55 _public prototype_ `bool HasChildrenForFace(const FGeometryCollectionFacesTreeItemFace& FaceItem) const;`
- L57 _public prototype_ `void ExpandAll();`
- L58 _public prototype_ `void RegenerateChildren();`
- L59 _public prototype_ `void RequestTreeRefresh();`
- L61 _public function_ `TSharedPtr<const FManagedArrayCollection> GetCollection()`
- L63 _public prototype_ `bool IsValid() const;`
- L66 _public function_ `void Invalidate()` — Mark item as unused/invalid; helpful because slate defers destroying tree items and can still run callbacks on them until tick
- L72 _private prototype_ `bool FilterBoneIndex(int32 BoneIndex) const;`
- L74 _private member_ `TSharedPtr<const FManagedArrayCollection> Collection;`
- L75 _private member_ `int32 GeometryIdx;`
- L77 _private member_ `TSharedPtr<STreeView<FGeometryCollectionFacesTreeItemPtr>> TreeView;`
- L80 _private member_ `TArray<FGeometryCollectionFacesTreeItemPtr> ChildItems;` — The direct children under this component
- L81 _private member_ `TMap<int32, FGeometryCollectionFacesTreeItemPtr> ItemsByFaceIndex;`
- L82 _private member_ `int32 RootIndex;`
- L85 _private member_ `bool bInvalidated = false;` — track whether the item has been explicitly invalidated

#### class `FGeometryCollectionFacesTreeItemFace`  
`class FGeometryCollectionFacesTreeItemFace : public FGeometryCollectionFacesTreeItem`  
_L88-117_
- inherits: `FGeometryCollectionFacesTreeItem`
- L91 _public function_ `FGeometryCollectionFacesTreeItemFace(const int32 InFaceIndex, FGeometryCollectionFacesTreeItemGeometry* InParentCollectionItem) : FaceIndex(InFaceIndex) , ParentCollectionItem(InParentCollectionItem) , ItemColor(FSlateColor::UseForeground())`
- L98 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FGeometryCollectionFacesTreeItem interface
- L99 _public prototype_ `TSharedRef<SWidget> MakeIndexColumnWidget() const;`
- L100 _public prototype_ `TSharedRef<SWidget> MakeEmptyColumnWidget() const;`
- L102 _public prototype_ `virtual void GetChildren(FGeometryCollectionFacesTreeItemList& OutChildren) override;`
- L103 _public prototype_ `bool IsValidFace() const;`
- L104 _public function_ `virtual int32 GetFaceIndex() const override`
- L105 _public function_ `FSlateColor GetItemColor() const`
- L106 _public prototype_ `bool HasChildren() const;`
- L107 _public prototype_ `TSharedPtr<const FManagedArrayCollection> GetCollection() const;`
- L112 _private prototype_ `void UpdateItemColorFromCollection();`
- L114 _private member_ `const int32 FaceIndex;`
- L115 _private member_ `FGeometryCollectionFacesTreeItemGeometry* ParentCollectionItem;`
- L116 _private member_ `FSlateColor ItemColor;`

#### class `SFacesOutlinerRow`  
`class SFacesOutlinerRow : public SMultiColumnTableRow<FGeometryCollectionFacesTreeItemFacePtr>`  
_L119-138_
- inherits: `SMultiColumnTableRow<FGeometryCollectionFacesTreeItemFacePtr>`
- L122 _protected member_ `FGeometryCollectionFacesTreeItemFacePtr Item;`
- L125 _public function_ `SLATE_BEGIN_ARGS(SFacesOutlinerRow)`
- L126 _public prototype_ `SLATE_END_ARGS() virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L130 _public function_ `void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, FGeometryCollectionFacesTreeItemFacePtr InItemToEdit)`

#### class `SFacesOutliner`  
`class SFacesOutliner : public SCompoundWidget`  
_L140-172_
- inherits: `SCompoundWidget`
- L142 _private function_ `SLATE_BEGIN_ARGS(SFacesOutliner)`
- L147 _public prototype_ `void Construct(const FArguments& InArgs);`
- L149 _public prototype_ `void RegenerateItems();`
- L150 _public prototype_ `void RegenerateHeader();`
- L152 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(FGeometryCollectionFacesTreeItemPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L153 _public prototype_ `TSharedRef<ITableRow> OnGeneratePinnedRowWidget(FGeometryCollectionFacesTreeItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable, bool bPinned);`
- L154 _public prototype_ `void OnGetChildren(TSharedPtr<FGeometryCollectionFacesTreeItem> InInfo, TArray< TSharedPtr<FGeometryCollectionFacesTreeItem> >& OutChildren);`
- L155 _public prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();`
- L157 _public prototype_ `void UpdateGeometryCollection();`
- L158 _public prototype_ `void SetCollection(const TSharedPtr<const FManagedArrayCollection>& InCollection);`
- L159 _public prototype_ `int32 GetBoneSelectionCount() const;`
- L161 _public prototype_ `void ExpandAll();`
- L162 _public prototype_ `void ExpandRecursive(TSharedPtr<FGeometryCollectionFacesTreeItem> TreeItem, bool bInExpansionState) const;`
- L165 _private prototype_ `void OnSelectionChanged(FGeometryCollectionFacesTreeItemPtr Item, ESelectInfo::Type SelectInfo);`
- L167 _private member_ `TSharedPtr<STreeView<FGeometryCollectionFacesTreeItemPtr>> TreeView;`
- L168 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L169 _private member_ `TArray<TSharedPtr<FGeometryCollectionFacesTreeItemGeometry>> RootNodes;`
- L170 _private member_ `bool bPerformingSelection;`
- L171 _private member_ `TSharedPtr<const FManagedArrayCollection> Collection;`

#### Free symbols / members of external scopes

- L19 _typedef_ `typedef TArray<TSharedPtr<FGeometryCollectionFacesTreeItem>> FGeometryCollectionFacesTreeItemList;`
- L20 _typedef_ `typedef TSharedPtr<FGeometryCollectionFacesTreeItem> FGeometryCollectionFacesTreeItemPtr;`
- L21 _typedef_ `typedef TSharedPtr<class FGeometryCollectionFacesTreeItemFace> FGeometryCollectionFacesTreeItemFacePtr;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowGraphEditor.h` (Public)


#### class `SDataflowGraphEditor`  
`class SDataflowGraphEditor : public SGraphEditor, public FGCObject, public FDataflowSEditorInterface`  
_L45-271_
- inherits: `SGraphEditor,FGCObject,FDataflowSEditorInterface`
- desc: The SDataflowGraphEditpr class is a specialization of SGraphEditor to display and manipulate the actions of a Dataflow asset see(SDataprepGraphEditor for reference)
- L49 _public typedef_ `using FGraphEvaluationCallback = TFunction<void(const FDataflowNode*, const FDataflowOutput*)>;`
- L50 _public typedef_ `using FOnDragDropEventCallback = TFunction<void(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)>;`
- L51 _public typedef_ `using FIsEditableCallback = TFunction<bool()>;`
- L53 _public function_ `SLATE_BEGIN_ARGS(SDataflowGraphEditor) : _AdditionalCommands(static_cast<FUICommandList*>(nullptr)) , _GraphToEdit(nullptr)`
- L58 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, AdditionalCommands) SLATE_ATTRIBUTE(FGraphAppearanceInfo, Appearance) SLATE_ARGUMENT_DEFAULT(UEdGraph*, GraphToEdit) = nullptr;`
- L61 _public prototype_ `SLATE_ARGUMENT(FGraphEditorEvents, GraphEvents) SLATE_ARGUMENT(TSharedPtr<IStructureDetailsView>, DetailsView) SLATE_ARGUMENT(FGraphEvaluationCallback, EvaluateGraph) SLATE_ARGUMENT(FOnDragDropEventCallback, OnDragDropEvent) SLATE_ARGUMENT(FIsEditableCallback, IsEditable) SLATE_ARGUMENT_DEFAULT(UDataflowEditor*, DataflowEditor) = nullptr;`
- L71 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChangedMulticast, const FGraphPanelSelectionSet&) FOnSelectionChangedMulticast OnSelectionChangedMulticast;` — This delegate exists in SGraphEditor but it is not multicast, and we are going to bind it to OnSelectedNodesChanged(). This new multicast delegate will be broadcast from the OnSelectedNodesChanged handler in case another class wants to be notified.
- L74 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodeDeletedMulticast, const FGraphPanelSelectionSet&) FOnNodeDeletedMulticast OnNodeDeletedMulticast;`
- L77 _public prototype_ `virtual ~SDataflowGraphEditor();`
- L80 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;` — SWidget overrides
- L81 _public prototype_ `virtual FReply OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L82 _public prototype_ `virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L83 _public prototype_ `virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent) override;`
- L84 _public prototype_ `bool IsControlDown() const;`
- L85 _public prototype_ `bool IsAltDown() const;`
- L91 _public prototype_ `void Construct(const FArguments& InArgs, UObject* AssetOwner);`
- L94 _public prototype_ `bool IsEditable() const;` — return whether or not the graph is editable
- L97 _public prototype_ `void EvaluateNode();`
- L100 _public prototype_ `void FreezeNodes();`
- L103 _public prototype_ `void UnfreezeNodes();`
- L106 _public prototype_ `void DeleteNode();`
- L109 _public prototype_ `void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);`
- L112 _public prototype_ `void CreateComment();`
- L115 _public prototype_ `void AlignTop();`
- L118 _public prototype_ `void AlignMiddle();`
- L121 _public prototype_ `void AlignBottom();`
- L124 _public prototype_ `void AlignLeft();`
- L127 _public prototype_ `void AlignCenter();`
- L130 _public prototype_ `void AlignRight();`
- L133 _public prototype_ `void StraightenConnections();`
- L136 _public prototype_ `void DistributeHorizontally();`
- L139 _public prototype_ `void DistributeVertically();`
- L142 _public prototype_ `void ToggleEnabledState();`
- L145 _public prototype_ `void DuplicateSelectedNodes();`
- L148 _public prototype_ `void ZoomToFitGraph();`
- L151 _public prototype_ `void CopySelectedNodes();`
- L154 _public prototype_ `void CutSelectedNodes();`
- L157 _public prototype_ `void PasteSelectedNodes();`
- L160 _public prototype_ `void RenameNode();`
- L161 _public prototype_ `bool CanRenameNode() const;`
- L164 _public prototype_ `void AddNewVariable() const;` — Add a new variable for this dataflow graph
- L167 _public prototype_ `void AddNewSubGraph() const;` — Add a new SubGraph for this dataflow graph
- L169 _public function_ `SGraphEditor* GetGraphEditor()`
- L172 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L173 _public function_ `virtual FString GetReferencerName() const override`
- L176 _public prototype_ `virtual TSharedPtr<UE::Dataflow::FContext> GetDataflowContext() const override;`
- L177 _public prototype_ `virtual void OnRenderToggleChanged(UDataflowEdNode* UpdatedEdNode) const override;`
- L178 _public prototype_ `virtual FText GetMessageText(const UDataflowEdNode& Node) const override;`
- L179 _public prototype_ `virtual EMessageSeverity::Type GetMessageMaxSeverity(const UDataflowEdNode& Node) const override;`
- L182 _public function_ `const TSharedPtr<FUICommandList> GetCommands() const`
- L185 _public function_ `static const TWeakPtr<SDataflowGraphEditor>& GetSelectedGraphEditor()` — Return the currently selected editor. Only valid for the duration of the OnSelectedNodesChanged callback where the property editor is updated.
- L187 _public function_ `static const TWeakPtr<SDataflowGraphEditor>& GetLastActionMenuGraphEditor()`
- L189 _public function_ `bool GetFilterActionMenyByAssetType() const`
- L191 _public prototype_ `void SetLogMessageStorage(TSharedPtr<UE::Dataflow::Private::FLogMessageStorage> InLogMessages);`
- L195 _private prototype_ `void OnAddOptionPin();` — Add an additional option pin to all selected Dataflow nodes for those that overrides the AddPin function.
- L197 _private prototype_ `bool CanAddOptionPin() const;` — Return whether all currently selected Dataflow nodes can execute the AddPin function.
- L200 _private prototype_ `void OnRemoveOptionPin();` — Remove an option pin from all selected Dataflow nodes for those that overrides the RemovePin function.
- L202 _private prototype_ `bool CanRemoveOptionPin() const;` — Return whether all currently selected Dataflow nodes can execute the RemovePin function.
- L204 _private prototype_ `void OnStartWatchingPin();`
- L205 _private prototype_ `bool CanStartWatchingPin() const;`
- L206 _private prototype_ `void OnStopWatchingPin();`
- L207 _private prototype_ `bool CanStopWatchingPin() const;`
- L208 _private prototype_ `void OnPromoteToVariable();`
- L209 _private prototype_ `bool CanPromoteToVariable() const;`
- L211 _private prototype_ `bool GetPinVisibility(SGraphEditor::EPinVisibility InVisibility) const;`
- L214 _private prototype_ `void InitGraphEditorMessageBar();` — Create a widget to display an overlaid message in the graph editor panel
- L217 _private prototype_ `void InitEvaluationProgressBar();` — Create a widget to display the progress of the evaluation of the graph
- L220 _private prototype_ `FText GetGraphEditorOverlayText() const;` — Text for overlay message in graph editor panel
- L223 _private prototype_ `UDataflow* GetDataflowAsset() const;` — get the dataflow asset from the edGraph being edited
- L225 _private member_ `FOnDragDropEventCallback OnDragDropEventCallback;`
- L226 _private member_ `FGraphEvaluationCallback EvaluateGraphCallback;`
- L227 _private member_ `FIsEditableCallback IsEditableCallback;`
- L229 _private prototype_ `FActionMenuContent OnCreateActionMenu(UEdGraph* Graph, const FVector2f& Position, const TArray<UEdGraphPin*>& DraggedPins, bool bAutoExpandActionMenu, SGraphEditor::FActionMenuClosed OnClosed);`
- L230 _private prototype_ `void OnActionMenuFilterByAssetTypeChanged(ECheckBoxState NewState, const TWeakPtr<SGraphEditorActionMenu> WeakActionMenu);`
- L231 _private prototype_ `ECheckBoxState IsActionMenuFilterByAssetTypeChecked() const;`
- L234 _private member_ `TWeakObjectPtr<UObject> AssetOwner;` — The asset that ownes this dataflow graph
- L237 _private member_ `TWeakObjectPtr<UEdGraph> EdGraphWeakPtr;` — The dataflow asset associated with this graph
- L240 _private member_ `TSharedPtr<FUICommandList> GraphEditorCommands;` — Command list associated with this graph editor
- L243 _private member_ `TSharedPtr<IStructureDetailsView> DetailsView;` — The details view that responds to this widget.
- L246 _private member_ `static TSharedPtr<FDataflowGraphEditorNodeFactory> NodeFactory;` — Factory to create the associated SGraphNode classes for Dataprep graph's UEdGraph classes
- L249 _private member_ `static TWeakPtr<SDataflowGraphEditor> SelectedGraphEditor;` — The current graph editor when the selection callback is invoked.
- L252 _private member_ `static TWeakPtr<SDataflowGraphEditor> LastActionMenuGraphEditor;` — The last graph editor used when a action context  menu was brough up in the graph.
- L255 _private member_ `UDataflowEditor* DataflowEditor = nullptr;` — Editor for the content
- L257 _private member_ `bool VKeyDown = false;`
- L258 _private member_ `bool LeftControlKeyDown = false;`
- L259 _private member_ `bool RightControlKeyDown = false;`
- L260 _private member_ `bool LeftAltKeyDown = false;`
- L261 _private member_ `bool RightAltKeyDown = false;`
- L263 _private member_ `bool bFilterActionMenyByAssetType = true;`
- L265 _private member_ `FDelegateHandle CVarChangedDelegateHandle;`
- L266 _private member_ `TSharedPtr<SWidget> MessageBar;`
- L267 _private member_ `TSharedPtr<SWidget> EvaluationProgressBar;`
- L268 _private member_ `FText MessageBarText;`
- L270 _private member_ `TSharedPtr<UE::Dataflow::Private::FLogMessageStorage> LogMessages;`

#### Free symbols / members of external scopes

- L22 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Dataflow` (scope `UE`)
- L34 _namespace_ `namespace Private` (scope `UE::Dataflow`)
- L71 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionChangedMulticast, const FGraphPanelSelectionSet&) FOnSelectionChangedMulticast OnSelectionChangedMulticast;` — This delegate exists in SGraphEditor but it is not multicast, and we are going to bind it to OnSelectedNodesChanged(). This new multicast delegate will be broadcast from the OnSelectedNodesChanged handler in case another class wants to be notified.
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnNodeDeletedMulticast, const FGraphPanelSelectionSet&) FOnNodeDeletedMulticast OnNodeDeletedMulticast;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowGraphSchemaAction.h` (Public)


#### enum `UE::Dataflow::ESchemaActionSectionID`  
`enum class ESchemaActionSectionID: int32`  
_L24-29_
- desc: Enums to use when grouping action in widgets see SDataflowMembersWidget
- L26 _public enumerator_ `NONE = 0`
- L27 _public enumerator_ `SUBGRAPHS`
- L28 _public enumerator_ `VARIABLES`

#### struct `FAssetSchemaAction_Dataflow_CreateNode_DataflowEdNode`  
`struct FAssetSchemaAction_Dataflow_CreateNode_DataflowEdNode : public FEdGraphSchemaAction`  
_L38-58_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action to add a node to the graph
- L43 _public function_ `FAssetSchemaAction_Dataflow_CreateNode_DataflowEdNode() : FEdGraphSchemaAction()`
- L45 _public prototype_ `FAssetSchemaAction_Dataflow_CreateNode_DataflowEdNode(const FName& InName, const FName& InType, FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords, FName InIconName);`
- L46 _public prototype_ `FAssetSchemaAction_Dataflow_CreateNode_DataflowEdNode(const FName& InName, const FName& InType, FText InNodeCategory, FText InMenuDesc, FText InToolTip, FText InKeywords, const FSlateIcon& InIcon);`
- L48 _public prototype_ `static TSharedPtr<FAssetSchemaAction_Dataflow_CreateNode_DataflowEdNode> CreateAction(const UEdGraph* ParentGraph, const FName& NodeTypeName, const FName& InOverrideNodeName = NAME_None);`
- L51 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L53 _public prototype_ `virtual FSlateBrush const* GetPaletteIcon() const override;`
- L55 _public member_ `FName NodeName;`
- L56 _public member_ `FName NodeTypeName;`
- L57 _public member_ `FSlateIcon Icon;`

#### struct `FEdGraphSchemaAction_DataflowVariable`  
`struct FEdGraphSchemaAction_DataflowVariable : public FEdGraphSchemaAction`  
_L65-136_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action that refers to a dataflow variable It is used to display the variables in the SDataflowMembersWidget
- L70 _public prototype_ `FEdGraphSchemaAction_DataflowVariable();`
- L72 _public prototype_ `FEdGraphSchemaAction_DataflowVariable(UDataflow* InDataflowAsset, const FPropertyBagPropertyDesc& PropertyDesc);`
- L75 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L76 _public function_ `virtual FName GetTypeId() const override`
- L78 _public function_ `const FString& GetVariableName() const`
- L83 _public function_ `FName GetFullVariableName() const`
- L88 _public function_ `const FEdGraphPinType& GetVariableType() const`
- L94 _public function_ `virtual bool IsAVariable() const` — FEdGraphSchemaAction interface
- L95 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L98 _public prototype_ `bool CanRenameItem(FText NewName) const;`
- L99 _public prototype_ `void RenameItem(FText NewName);`
- L100 _public prototype_ `void SetVariableType(const FEdGraphPinType& PinType);`
- L102 _public prototype_ `void CopyItemToClipboard();`
- L103 _public prototype_ `void PasteItemFromClipboard();`
- L104 _public prototype_ `void DeleteItem();`
- L105 _public prototype_ `void DuplicateItem();`
- L108 _private prototype_ `static FString CategoryFromFullName(FName FullName);`
- L109 _private prototype_ `static FString NameFromFullName(FName FullName);`
- L117 _private member_ `FName FullVariableName;` — Name of the variable the name can contain a category is using a separating | example : Category.VariableName
- L122 _private member_ `FString VariableName;` — Variable short name ( extracted from FullName )
- L127 _private member_ `FString VariableCategory;` — Variable category name ( extracted from FullName )
- L132 _private member_ `FEdGraphPinType VariableType;` — type of the variable (as a Pin type)
- L135 _private member_ `TWeakObjectPtr<UDataflow> DataflowAssetWeakPtr;` — Dataflow asset associated with this action

#### struct `FGraphSchemaActionDragDropAction_DataflowVariable`  
`struct FGraphSchemaActionDragDropAction_DataflowVariable : public FGraphSchemaActionDragDropAction`  
_L144-155_
- inherits: `FGraphSchemaActionDragDropAction`
- desc: Dataflow variable drag and drop action see FEdGraphSchemaAction_DataflowVariable
- L147 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FGraphSchemaActionDragDropAction_DataflowVariable, FGraphSchemaActionDragDropAction) static TSharedRef<FGraphSchemaActionDragDropAction_DataflowVariable> New(TSharedPtr<FEdGraphSchemaAction_DataflowVariable>& InAction);`
- L152 _private prototype_ `FGraphSchemaActionDragDropAction_DataflowVariable();`
- L154 _private member_ `TSharedPtr<FEdGraphSchemaAction_DataflowVariable> VariableAction;`

#### struct `FEdGraphSchemaAction_DataflowSubGraph`  
`struct FEdGraphSchemaAction_DataflowSubGraph : public FEdGraphSchemaAction`  
_L165-201_
- reflection: `USTRUCT()`
- inherits: `FEdGraphSchemaAction`
- desc: Action that refers to a dataflow subgraph It is used to display the variables in the SDataflowMembersWidget
- L170 _public prototype_ `FEdGraphSchemaAction_DataflowSubGraph();`
- L172 _public prototype_ `FEdGraphSchemaAction_DataflowSubGraph(UDataflow* InDataflowAsset, const FGuid& InSubGraphGuid);`
- L175 _public function_ `static FName StaticGetTypeId()` — Simple type info
- L176 _public function_ `virtual FName GetTypeId() const override`
- L178 _public prototype_ `const FName GetSubGraphName() const;`
- L179 _public prototype_ `bool IsForEachSubGraph() const;`
- L180 _public prototype_ `void SetForEachSubGraph(bool bValue);`
- L183 _public function_ `virtual bool IsAVariable() const` — FEdGraphSchemaAction interface
- L184 _public prototype_ `virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2f& Location, bool bSelectNewNode = true) override;`
- L187 _public prototype_ `bool CanRenameItem(FText NewName) const;`
- L188 _public prototype_ `void RenameItem(FText NewName);`
- L190 _public prototype_ `void CopyItemToClipboard();`
- L191 _public prototype_ `void PasteItemFromClipboard();`
- L192 _public prototype_ `void DeleteItem();`
- L193 _public prototype_ `void DuplicateItem();`
- L197 _private member_ `FGuid SubGraphGuid;` — Guid of the subgraph
- L200 _private member_ `TWeakObjectPtr<UDataflow> DataflowAssetWeakPtr;` — Dataflow asset associated with this action

#### struct `FGraphSchemaActionDragDropAction_DataflowSubGraph`  
`struct FGraphSchemaActionDragDropAction_DataflowSubGraph : public FGraphSchemaActionDragDropAction`  
_L209-220_
- inherits: `FGraphSchemaActionDragDropAction`
- desc: Dataflow variable drag and drop action see FEdGraphSchemaAction_DataflowSubGraph
- L212 _public prototype_ `DRAG_DROP_OPERATOR_TYPE(FGraphSchemaActionDragDropAction_DataflowSubGraph, FGraphSchemaActionDragDropAction) static TSharedRef<FGraphSchemaActionDragDropAction_DataflowSubGraph> New(TSharedPtr<FEdGraphSchemaAction_DataflowSubGraph>& InAction);`
- L217 _private prototype_ `FGraphSchemaActionDragDropAction_DataflowSubGraph();`
- L219 _private member_ `TSharedPtr<FEdGraphSchemaAction_DataflowSubGraph> SubGraphAction;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowInstanceDetails.h` (Public)


#### class `FDataflowVariableOverridesDetails`  
`class FDataflowVariableOverridesDetails : public IPropertyTypeCustomization`  
_L16-25_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FDataflowVariableOverrides.
- L20 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L23 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L24 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& InChildrenBuilder, IPropertyTypeCustomizationUtils& InCustomizationUtils) override;`

#### class `FDataflowInstanceDetailCustomization`  
`class FDataflowInstanceDetailCustomization : public IDetailCustomization`  
_L27-38_
- inherits: `IDetailCustomization`
- L31 _public prototype_ `FDataflowInstanceDetailCustomization(bool bOnlyShowVariableOverrides);` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L34 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L37 _private member_ `bool bOnlyShowVariableOverrides = false;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowNodeDetailExtension.h` (Public)


#### class `UE::Dataflow::IDataflowNodeDetailExtension`  
`class IDataflowNodeDetailExtension : public IDetailPropertyExtensionHandler`  
_L14-20_
- inherits: `IDetailPropertyExtensionHandler`
- desc: IDetailPropertyExtensionHandler that can be registered with FDataflowNodeDetailExtensionRegistry to be aggregated and applied to the Dataflow Node Details panel.
- L17 _public prototype_ `virtual ~IDataflowNodeDetailExtension() = default;`
- L19 _public prototype_ `virtual FName GetName() const = 0;`

#### class `UE::Dataflow::FDataflowNodeDetailExtensionRegistry`  
`class FDataflowNodeDetailExtensionRegistry`  
_L26-44_
- desc: Registry for IDataflowNodeDetailExtension. Register/Deregister extensions to extend the Dataflow Node Details rows via IDetailPropertyExtensionHandler. The only reason why this isn't an IDetailPropertyExtensionHandler is because DetailsViews want a SharedPtr of an IDetailPropertyExtensionHandler, but this is a singleton registry.
- L31 _public prototype_ `static FDataflowNodeDetailExtensionRegistry& GetInstance();` — FLazySingleton
- L32 _public prototype_ `static void TearDown();`
- L34 _public prototype_ `void RegisterExtension(TUniquePtr<IDataflowNodeDetailExtension>&& Extension);`
- L35 _public prototype_ `void DeregisterExtension(const FName& ExtensionName);`
- L38 _public prototype_ `bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const;` — These methods aggregate calls on the registered extensions.
- L39 _public prototype_ `void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle);`
- L43 _private member_ `TMap<FName, TUniquePtr<IDataflowNodeDetailExtension>> ExtensionMap;`

#### class `UE::Dataflow::FDataflowNodeDetailExtensionHandler`  
`class FDataflowNodeDetailExtensionHandler : public IDetailPropertyExtensionHandler`  
_L50-56_
- inherits: `IDetailPropertyExtensionHandler`
- desc: This is the IDetailPropertyExtensionHandler that the DataflowToolkit actually uses.It simply calls the equivalent methods on the FDataflowNodeDetailExtensionRegistry singleton.
- L54 _public prototype_ `virtual bool IsPropertyExtendable(const UClass* InObjectClass, const IPropertyHandle& PropertyHandle) const override;` — IDetailPropertyExtensionHandler
- L55 _public prototype_ `virtual void ExtendWidgetRow(FDetailWidgetRow& InWidgetRow, const IDetailLayoutBuilder& InDetailBuilder, const UClass* InObjectClass, TSharedPtr<IPropertyHandle> PropertyHandle) override;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowRenderingFactory.h` (Public)


#### struct `UE::Dataflow::FGraphRenderingState`  
`struct FGraphRenderingState`  
_L22-74_
- L24 _public function_ `FGraphRenderingState(const FGuid InGuid, const FDataflowNode* InNode, const FRenderingParameter& InParameters, UE::Dataflow::FContext& InContext, const UE::Dataflow::IDataflowConstructionViewMode& ViewMode, const bool bInEvaluateOutputs = true) : NodeGuid(InGuid) , Node(InNode) , RenderName(InParameters.Name) , RenderType(InParameters.Type) , RenderOutputs(InParameters.Outputs) , Context(InContext) , ViewMode(ViewMode) , bEvaluateOutputs(bInEvaluateOutputs)`
- L36 _public function_ `const FGuid& GetGuid() const`
- L37 _public function_ `FName GetNodeName() const`
- L38 _public function_ `FRenderKey GetRenderKey() const`
- L39 _public function_ `const TArray<FName>& GetRenderOutputs() const`
- L42 _public function_ `template<class T> const T& GetValue(FName OutputName, const T& Default) const`
- L58 _public function_ `const UE::Dataflow::IDataflowConstructionViewMode& GetViewMode() const`
- L61 _private member_ `const FGuid NodeGuid;`
- L62 _private member_ `const FDataflowNode* Node = nullptr;`
- L64 _private member_ `FString RenderName;`
- L65 _private member_ `FName RenderType;`
- L66 _private member_ `TArray<FName> RenderOutputs;`
- L68 _private member_ `UE::Dataflow::FContext& Context;`
- L70 _private member_ `const UE::Dataflow::IDataflowConstructionViewMode& ViewMode;`
- L73 _private member_ `bool bEvaluateOutputs = true;` — Boolean to check if we need to reevaluate the outputs or read the cached value

#### class `UE::Dataflow::FRenderingFactory`  
`class FRenderingFactory`  
_L77-109_
- L91 _public function_ `~FRenderingFactory()`
- L93 _public prototype_ `static FRenderingFactory* GetInstance();`
- L95 _public prototype_ `void RegisterCallbacks(TUniquePtr<ICallbackInterface> InCallbacks);`
- L96 _public prototype_ `void DeregisterCallbacks(const FRenderKey& Key);`
- L98 _public function_ `bool Contains(const FRenderKey& InKey) const`
- L99 _public prototype_ `void RenderNodeOutput(GeometryCollection::Facades::FRenderingFacade& RenderingFacade, const FGraphRenderingState& State);`
- L100 _public prototype_ `bool CanRenderNodeOutput(const FGraphRenderingState& State) const;`
- L104 _private function_ `FRenderingFactory()`
- L106 _private member_ `static FRenderingFactory* Instance;`
- L108 _private member_ `TMap<FRenderKey, TUniquePtr<ICallbackInterface>> CallbackMap;`

#### class `UE::Dataflow::FRenderingFactory::ICallbackInterface`  
`class ICallbackInterface`  
_L81-89_
- L84 _public prototype_ `virtual ~ICallbackInterface() = default;`
- L85 _public prototype_ `virtual FRenderKey GetRenderKey() const = 0;`
- L86 _public prototype_ `virtual bool CanRender(const UE::Dataflow::IDataflowConstructionViewMode& ViewMode) const = 0;`
- L87 _public function_ `virtual bool CanRenderFromState(const FGraphRenderingState& State) const`
- L88 _public prototype_ `virtual void Render(GeometryCollection::Facades::FRenderingFacade& RenderingFacade, const FGraphRenderingState& State) = 0;`

#### Free symbols / members of external scopes

- L13 _namespace_ `namespace GeometryCollection`
- L13 _namespace_ `namespace Facades` (scope `GeometryCollection`)
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Dataflow` (scope `UE`)
- L20 _typedef_ `typedef TPair<FString, FName> FRenderKey;` (scope `UE::Dataflow`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowRenderingViewMode.h` (Public)


#### class `UE::Dataflow::IDataflowConstructionViewMode`  
`class IDataflowConstructionViewMode`  
_L29-42_
- L32 _public prototype_ `virtual ~IDataflowConstructionViewMode() = default;`
- L34 _public prototype_ `virtual FName GetName() const = 0;`
- L35 _public prototype_ `virtual FText GetButtonText() const = 0;`
- L36 _public prototype_ `virtual FText GetTooltipText() const = 0;`
- L37 _public prototype_ `virtual ELevelViewportType GetViewportType() const = 0;`
- L38 _public function_ `virtual FRotator GetViewportOrientation() const`
- L39 _public function_ `virtual bool CanDisplayGizmo() const`
- L41 _public prototype_ `bool IsPerspective() const;`

#### class `UE::Dataflow::FDataflowConstruction2DViewModeBase`  
`class FDataflowConstruction2DViewModeBase : public IDataflowConstructionViewMode`  
_L46-50_
- inherits: `IDataflowConstructionViewMode`
- L49 _public prototype_ `virtual ELevelViewportType GetViewportType() const override;`

#### class `UE::Dataflow::FDataflowConstruction3DViewModeBase`  
`class FDataflowConstruction3DViewModeBase : public IDataflowConstructionViewMode`  
_L52-56_
- inherits: `IDataflowConstructionViewMode`
- L55 _public prototype_ `virtual ELevelViewportType GetViewportType() const override;`

#### class `UE::Dataflow::FDataflowConstruction2DViewMode`  
`class FDataflowConstruction2DViewMode : public FDataflowConstruction2DViewModeBase`  
_L60-70_
- inherits: `FDataflowConstruction2DViewModeBase`
- L63 _public member_ `static FName Name;`
- L64 _public prototype_ `virtual ~FDataflowConstruction2DViewMode() = default;`
- L66 _private prototype_ `virtual FName GetName() const override;`
- L67 _private prototype_ `virtual FText GetButtonText() const override;`
- L68 _private prototype_ `virtual FText GetTooltipText() const override;`
- L69 _private prototype_ `virtual FRotator GetViewportOrientation() const override;`

#### class `UE::Dataflow::FDataflowConstruction3DViewMode`  
`class FDataflowConstruction3DViewMode : public FDataflowConstruction3DViewModeBase`  
_L72-83_
- inherits: `FDataflowConstruction3DViewModeBase`
- L75 _public member_ `static FName Name;`
- L76 _public prototype_ `virtual ~FDataflowConstruction3DViewMode() = default;`
- L78 _private prototype_ `virtual FName GetName() const override;`
- L79 _private prototype_ `virtual FText GetButtonText() const override;`
- L80 _private prototype_ `virtual FText GetTooltipText() const override;`
- L81 _private prototype_ `virtual FRotator GetViewportOrientation() const override;`
- L82 _private function_ `virtual bool CanDisplayGizmo() const`

#### class `UE::Dataflow::FDataflowConstructionUVViewMode`  
`class FDataflowConstructionUVViewMode : public FDataflowConstruction2DViewModeBase`  
_L86-96_
- inherits: `FDataflowConstruction2DViewModeBase`
- desc: UV view mode (same as 2D but with a different name and button text)
- L89 _public member_ `static FName Name;`
- L90 _public prototype_ `virtual ~FDataflowConstructionUVViewMode() = default;`
- L92 _private prototype_ `virtual FName GetName() const override;`
- L93 _private prototype_ `virtual FText GetButtonText() const override;`
- L94 _private prototype_ `virtual FText GetTooltipText() const override;`
- L95 _private prototype_ `virtual FRotator GetViewportOrientation() const override;`

#### class `UE::Dataflow::FDataflowConstructionMaterialViewMode`  
`class FDataflowConstructionMaterialViewMode : public FDataflowConstruction3DViewModeBase`  
_L98-107_
- inherits: `FDataflowConstruction3DViewModeBase`
- L101 _public member_ `static FName Name;`
- L102 _public prototype_ `virtual ~FDataflowConstructionMaterialViewMode() = default;`
- L104 _private prototype_ `virtual FName GetName() const override;`
- L105 _private prototype_ `virtual FText GetButtonText() const override;`
- L106 _private prototype_ `virtual FText GetTooltipText() const override;`

#### class `UE::Dataflow::FRenderingViewModeFactory`  
`class FRenderingViewModeFactory`  
_L113-133_
- L117 _public prototype_ `FRenderingViewModeFactory();`
- L120 _public prototype_ `static FRenderingViewModeFactory& GetInstance();` — FLazySingleton
- L121 _public prototype_ `static void TearDown();`
- L123 _public prototype_ `void RegisterViewMode(TUniquePtr<IDataflowConstructionViewMode>&& ViewMode);`
- L124 _public prototype_ `void DeregisterViewMode(const FName& ViewModeName);`
- L126 _public prototype_ `const IDataflowConstructionViewMode* GetViewMode(const FName& ViewModeName) const;`
- L128 _public prototype_ `const TMap<FName, TUniquePtr<IDataflowConstructionViewMode>>& GetViewModes() const;`
- L132 _private member_ `TMap<FName, TUniquePtr<IDataflowConstructionViewMode>> ViewModeMap;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSEditorInterface.h` (Public)


#### class `FDataflowSEditorInterface`  
`class FDataflowSEditorInterface`  
_L19-51_
- desc: FDataflowSEditorInterface
- L23 _public prototype_ `virtual TSharedPtr<UE::Dataflow::FContext> GetDataflowContext() const = 0;` — Dataflow editor content accessors
- L25 _public function_ `virtual bool NodesHaveToggleWidget() const`
- L30 _public function_ `virtual bool NodesHaveFreezeWidget() const`
- L35 _public function_ `virtual void OnRenderToggleChanged(UDataflowEdNode* UpdatedEdNode) const`
- L39 _public function_ `virtual FText GetMessageText(const UDataflowEdNode& Node) const`
- L44 _public function_ `virtual EMessageSeverity::Type GetMessageMaxSeverity(const UDataflowEdNode& Node) const`
- L50 _protected prototype_ `FDataflowSEditorInterface() = default;`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSNode.h` (Public)


#### class `SDataflowEdNode`  
`class SDataflowEdNode : public SGraphNode , public FGCObject`  
_L22-89_
- inherits: `SGraphNode,FGCObject`
- L24 _private typedef_ `typedef SGraphNode Super;`
- L27 _public typedef_ `typedef TFunction<void(UEdGraphNode* InNode, bool InEnabled)> FToggleRenderCallback;`
- L29 _public function_ `SLATE_BEGIN_ARGS(SDataflowEdNode) : _GraphNodeObj(nullptr)`
- L32 _public prototype_ `SLATE_ARGUMENT(UDataflowEdNode*, GraphNodeObj) SLATE_ARGUMENT(FDataflowSEditorInterface*, DataflowInterface) SLATE_END_ARGS() void Construct(const FArguments& InArgs, UDataflowEdNode* InNode);`
- L39 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;` — SGraphNode interface
- L40 _public prototype_ `virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2f& WidgetSize) const override;`
- L41 _public prototype_ `virtual FText GetNodeTooltip() const override;`
- L42 _public prototype_ `virtual void UpdateErrorInfo() override;`
- L43 _public function_ `virtual void RequestRenameOnSpawn() override`
- L45 _public prototype_ `static void CopyDataflowNodeSettings(TSharedPtr<FDataflowNode> SourceDataflowNode, TSharedPtr<FDataflowNode> TargetDataflowNode);`
- L48 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;`
- L49 _public function_ `virtual FString GetReferencerName() const override`
- L59 _private prototype_ `virtual void CreateInputSideAddButton(TSharedPtr<SVerticalBox> InputBox) override;` — Override this to create a button to add pins on the input side of the node
- L61 _private prototype_ `virtual void CreateOutputSideAddButton(TSharedPtr<SVerticalBox> OutputBox) override;` — Override this to create a button to add pins on the output side of the node
- L63 _private prototype_ `virtual FReply OnAddPin() override;` — Callback function executed when Add pin button is clicked
- L65 _private prototype_ `virtual EVisibility IsAddPinButtonVisible() const;` — Checks whether Add pin button should currently be visible
- L68 _private prototype_ `FReply OnShowHideInputs();` — when clicking on the show/hide input pins button
- L70 _private prototype_ `const FSlateBrush* GetPinButtonImage() const;`
- L72 _private prototype_ `virtual TSharedPtr<SGraphPin> CreatePinWidget(UEdGraphPin* Pin) const override;`
- L73 _private prototype_ `virtual TSharedRef<SWidget> CreateTitleWidget(TSharedPtr<SNodeTitle> NodeTitle);`
- L74 _private prototype_ `virtual TSharedRef<SWidget> CreateTitleRightWidget() override;`
- L76 _private member_ `TObjectPtr<UDataflowEdNode> DataflowGraphNode = nullptr;`
- L78 _private member_ `FCheckBoxStyle CheckBoxStyle;`
- L79 _private member_ `TSharedPtr<SCheckBox> RenderCheckBoxWidget;`
- L80 _private member_ `TSharedPtr<SImage> FreezeImageWidget;`
- L81 _private member_ `TSharedPtr<STextBlock> PerfWidget;`
- L82 _private member_ `TSharedPtr<STextBlock> WatchWidget;`
- L87 _private member_ `FDataflowSEditorInterface* DataflowInterface;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWEDITOR_API`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSNodeFactories.h` (Public)


#### class `FDataflowGraphNodeFactory`  
`class FDataflowGraphNodeFactory : public FGraphNodeFactory, public TSharedFromThis<FDataflowGraphNodeFactory>`  
_L13-27_
- inherits: `FGraphNodeFactory,TSharedFromThis<FDataflowGraphNodeFactory>`
- L16 _public prototype_ `virtual ~FDataflowGraphNodeFactory() = default;`
- L18 _public function_ `FDataflowGraphNodeFactory(FDataflowSEditorInterface* InDataflowInterface) : DataflowInterface(InDataflowInterface)`
- L23 _public prototype_ `virtual TSharedPtr<SGraphNode> CreateNodeWidget(UEdGraphNode* InNode) override;` — Create a widget for the supplied node
- L26 _private member_ `FDataflowSEditorInterface* DataflowInterface;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSchema.h` (Public)


#### class `UDataflowSchema`  
`class UDataflowSchema : public UEdGraphSchema`  
_L21-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEdGraphSchema`
- L25 _public prototype_ `UDataflowSchema();`
- L28 _public prototype_ `virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const override;`
- L29 _public prototype_ `virtual void GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;`
- L30 _public prototype_ `virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;`
- L32 _public prototype_ `virtual FLinearColor GetPinTypeColor(const FEdGraphPinType& PinType) const override;`
- L33 _public prototype_ `virtual FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;`
- L34 _public prototype_ `virtual void OnPinConnectionDoubleCicked(UEdGraphPin* PinA, UEdGraphPin* PinB, const FVector2f& GraphPosition) const override;`
- L35 _public prototype_ `virtual void BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const override;`
- L36 _public prototype_ `virtual bool TryCreateConnection(UEdGraphPin* PinA, UEdGraphPin* PinB) const override;`
- L37 _public prototype_ `virtual bool CreateAutomaticConversionNodeAndConnections(UEdGraphPin* InSourcePin, UEdGraphPin* InTargetPin) const override;`
- L39 _public prototype_ `virtual void GetAssetsGraphHoverMessage(const TArray<FAssetData>& Assets, const UEdGraph* HoverGraph, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L40 _public prototype_ `virtual void DroppedAssetsOnGraph(const TArray<FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraph* Graph) const override;`
- L42 _public prototype_ `virtual void GetAssetsNodeHoverMessage(const TArray<struct FAssetData>& Assets, const UEdGraphNode* HoverNode, FString& OutTooltipText, bool& OutOkIcon) const override;`
- L43 _public prototype_ `virtual void DroppedAssetsOnNode(const TArray<struct FAssetData>& Assets, const FVector2f& GraphPosition, UEdGraphNode* Node) const override;`
- L45 _public function_ `virtual void SetPinBeingDroppedOnNode(UEdGraphPin* InSourcePin) const override`
- L46 _public prototype_ `virtual bool SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection, FText& OutMessage) const override;`
- L47 _public prototype_ `virtual UEdGraphPin* DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName, const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const override;`
- L50 _public prototype_ `static FLinearColor GetTypeColor(const FName& Type);`
- L51 _public prototype_ `float GetPinTypeWireThickness(const FName& Type) const;`
- L52 _public prototype_ `TOptional<FLinearColor> GetPinColorOverride(TSharedPtr<FDataflowNode> DataflowNode, UEdGraphPin* Pin) const;`
- L56 _private prototype_ `static bool CanPinBeConnectedToNode(const UEdGraphPin* Pin, const UE::Dataflow::FFactoryParameters& NodeParameters);`
- L57 _private prototype_ `static bool CanConnectPins(const UEdGraphPin& OutputPin, const UEdGraphPin& InputPin);`
- L58 _private prototype_ `static bool CanConvertPins(const UEdGraphPin& OutputPin, const UEdGraphPin& InputPin);`
- L59 _private prototype_ `static bool IsCategorySupported(FName NodeCategory, FName AssetType);`
- L60 _private prototype_ `static FName GetEditedAssetType();`
- L61 _private prototype_ `static UE::Dataflow::FPin::EDirection GetDirectionFromPinDirection(EEdGraphPinDirection InPinDirection);`
- L63 _private prototype_ `static TSharedPtr<UE::Dataflow::FGraph> GetDataflowGraphFromPin(const UEdGraphPin& Pin);`
- L64 _private prototype_ `static TSharedPtr<const FDataflowNode> GetDataflowNodeFromPin(const UEdGraphPin& Pin);`
- L65 _private prototype_ `static const FDataflowInput* GetDataflowInputFromPin(const UEdGraphPin& Pin);`
- L66 _private prototype_ `static const FDataflowOutput* GetDataflowOutputFromPin(const UEdGraphPin& Pin);`
- L69 _private member_ `mutable UEdGraphPin* PinBeingDropped = nullptr;` — used by SupportsDropPinOnNode to know which original connection is being dropped
- L71 _private prototype_ `virtual bool IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const override;`
- L72 _private prototype_ `virtual int32 GetCurrentVisualizationCacheID() const override;`
- L73 _private prototype_ `virtual void ForceVisualizationCacheClear() const override;`
- L74 _private member_ `static int32 CurrentCacheRefreshID;`

#### class `FDataflowConnectionDrawingPolicy`  
`class FDataflowConnectionDrawingPolicy : public FConnectionDrawingPolicy, public FGCObject`  
_L77-91_
- inherits: `FConnectionDrawingPolicy,FGCObject`
- L80 _public prototype_ `FDataflowConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InGraph);`
- L81 _public prototype_ `virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;`
- L83 _public function_ `const UDataflowSchema* GetSchema()`
- L86 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L87 _public function_ `virtual FString GetReferencerName() const override`
- L90 _private member_ `TObjectPtr<UDataflowSchema> Schema = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSimulationGenerator.h` (Public)


#### class `UE::Dataflow::FDataflowSimulationTask`  
`class FDataflowSimulationTask : public FNonAbandonableTask`  
_L22-62_
- inherits: `FNonAbandonableTask`
- desc: Simulation Task to be run on the async thread
- L25 _public function_ `FDataflowSimulationTask()`
- L29 _public prototype_ `void DoWork();` — Run the simulation
- L32 _public function_ `bool CanAbandon()` — Can abandon check
- L37 _public function_ `TStatId GetStatId() const`
- L43 _public member_ `TSharedPtr<struct FDataflowTaskManager> TaskManager = nullptr;` — Task Manager
- L46 _public member_ `float DeltaTime = 0.0f;` — Simulation delta time
- L49 _public member_ `float MinTime = TNumericLimits<float>::Max();` — Simulation min time
- L52 _public member_ `float MaxTime = TNumericLimits<float>::Lowest();` — Simulation max time
- L55 _public member_ `UWorld* SimulationWorld = nullptr;` — Simulation world
- L58 _public member_ `bool bAsyncCaching = true;` — Boolean to check if we are running the task in the background
- L61 _public member_ `bool bRestartSimulation = false;` — Boolean to check if we should restart the simulation in the range

#### struct `UE::Dataflow::FDataflowSimulationResource`  
`struct FDataflowSimulationResource`  
_L65-94_
- desc: Async simulation resource that will be used while simulating
- L68 _public member_ `std::atomic<int32>* NumSimulatedFrames = nullptr;` — Number of simulated frames
- L71 _public member_ `std::atomic<int64>* RecentDateTimeTicks = nullptr;` — Simulation time of current frames
- L74 _public member_ `std::atomic<bool>* bCancelled = nullptr;` — Async cancel boolean
- L77 _public function_ `bool IsCancelled() const` — Check if the simulation is canceled or not
- L83 _public function_ `void FinishFrame()` — Finish simulating the current frame

#### struct `UE::Dataflow::FDataflowTaskManager`  
`struct FDataflowTaskManager`  
_L97-152_
- desc: Simulation Task manager
- L100 _public member_ `TSharedPtr<FDataflowSimulationResource> SimulationResource;` — Simulation resource
- L103 _public member_ `TUniquePtr<FAsyncTask<FDataflowSimulationTask>> SimulationTask;` — Simulation task
- L106 _public member_ `TUniquePtr<FAsyncTaskNotification> AsyncNotification;` — Async notification
- L109 _public member_ `int32 NumFrames;` — Number of frames to simulate
- L112 _public member_ `FDateTime StartTime;` — Start time of the simulation
- L115 _public member_ `FDateTime LastUpdateTime;` — Last updated time
- L118 _public prototype_ `bool AllocateSimulationResource(const FVector2f& TimeRange, const int32 FrameRate, const TObjectPtr<UChaosCacheCollection>& CacheAsset, const TSubclassOf<AActor>& ActorClass, const TObjectPtr<UDataflowBaseContent>& DataflowContent, const FTransform& BlueprintTransform, const FInstancedPropertyBag& BlueprintVariables, const bool bSkeletalMeshVisibility, float DeltaTime);` — Allocate the simulation resource from the properties
- L130 _public prototype_ `void FreeSimulationResource();` — Free the simulation resource
- L133 _public prototype_ `void CancelSimulationGeneration();` — Cancel the simulation generation
- L136 _public member_ `std::atomic<int32> NumSimulatedFrames = 0;` — Number of simulated frames
- L139 _public member_ `std::atomic<int64> RecentDateTimeTicks = 0;` — Simulation time of current frames
- L142 _public member_ `std::atomic<bool> bCancelled = false;` — Boolean to check if the simulation has been cancelled
- L145 _public member_ `UWorld* SimulationWorld = nullptr;` — Temporary world created to run the simulation
- L148 _public member_ `TObjectPtr<AChaosCacheManager> CacheManager = nullptr;` — Temporary cache manager created to run the simulation
- L151 _public member_ `TObjectPtr<AActor> PreviewActor = nullptr;` — Temporary cache manager created to run the simulation

#### enum `UE::Dataflow::EDataflowGeneratorActions`  
`enum class EDataflowGeneratorActions`  
_L155-160_
- desc: Enum for all the generator actions
- L157 _public enumerator_ `NoAction`
- L158 _public enumerator_ `StartGenerate`
- L159 _public enumerator_ `TickGenerate`

#### class `UE::Dataflow::FDataflowSimulationGenerator`  
`class FDataflowSimulationGenerator : public FTickableEditorObject`  
_L163-245_
- inherits: `FTickableEditorObject`
- desc: Dataflow simulation generator
- L166 _public prototype_ `FDataflowSimulationGenerator();`
- L167 _public prototype_ `virtual ~FDataflowSimulationGenerator();`
- L170 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L171 _public prototype_ `virtual TStatId GetStatId() const override;`
- L172 _public function_ `virtual ETickableTickType GetTickableTickType() const override`
- L176 _public prototype_ `void SetBlueprintClass(const TSubclassOf<AActor>& InBlueprintClass);` — Set the blueprint class for cache recording
- L179 _public prototype_ `void SetBlueprintTransform(const FTransform& InBlueprintTransform);` — Set the blueprint transform for cache recording
- L182 _public prototype_ `void SetBlueprintVariables(const FInstancedPropertyBag& InBlueprintVariables);` — Set the blueprint variables' values used to customize the blueprint
- L185 _public prototype_ `void SetCacheParams(const FDataflowPreviewCacheParams& InCacheParams);` — Set the cache params for cache recording
- L188 _public prototype_ `void SetCacheAsset(const TObjectPtr<UChaosCacheCollection>& InCacheAsset);` — Set the cache asset for cache recording
- L191 _public prototype_ `void SetDataflowContent(const TObjectPtr<UDataflowBaseContent>& InDataflowContent);` — Set the dataflow content
- L194 _public prototype_ `void SetSkeletalMeshVisibility(const bool bInSkeletalMeshVisibility);` — Set the skeletal mesh visibility
- L197 _public function_ `void SetDeltaTime(float InDeltaTime)` — Set delta time
- L200 _public prototype_ `void RequestGeneratorAction(EDataflowGeneratorActions Action);` — Enqueue a generator action to be processed on the async thread
- L203 _public function_ `bool IsSimulating()` — If the generator is running simulation
- L208 _private prototype_ `void StartGenerateSimulation();` — Start generating the simulation
- L211 _private prototype_ `void TickGenerateSimulation();` — Tick the generated simulation
- L214 _private prototype_ `void FreeTaskResource(bool bCancelled);` — Free the task resource used while generating the simulation
- L217 _private member_ `TObjectPtr<UChaosCacheCollection> CacheAsset = nullptr;` — Cache asset to store the caches
- L220 _private member_ `FDataflowPreviewCacheParams CacheParams;` — Cache params used to record simulation
- L223 _private member_ `TSubclassOf<AActor> BlueprintClass;` — Blueprint class used to spawn the actor
- L226 _private member_ `FTransform BlueprintTransform = FTransform::Identity;` — Blueprint transform used to spawn the actor
- L229 _private member_ `FInstancedPropertyBag BlueprintVariables;` — Blueprint variables' values used to customize the blueprint
- L232 _private member_ `TObjectPtr<UDataflowBaseContent> DataflowContent;` — Dataflow content
- L235 _private member_ `bool bSkeletalMeshVisibility = true;` — Skeletal mesh visibility
- L238 _private member_ `float GeneratorDeltaTime = 0.f;` — Delta time for a frame
- L241 _private member_ `EDataflowGeneratorActions PendingAction = EDataflowGeneratorActions::NoAction;` — Pending action to be send to the async thread
- L244 _private member_ `TSharedPtr<FDataflowTaskManager> TaskManager = nullptr;` — Task manager to run the async tasks

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowSimulationGenerator, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowSimulationGenerator, Log, All);`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSimulationGeometryCache.h` (Public)


#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowSimulationGeometryCache, Log, All);`
- L13 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogDataflowSimulationGeometryCache, Log, All);`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace DataflowSimulationGeometryCache` (scope `UE`)
- L18 _prototype_ `void SaveGeometryCache(UGeometryCache& GeometryCache, float FrameRate, const USkinnedAsset& Asset, TConstArrayView<uint32> ImportedVertexNumbers, TArrayView<TArray<FVector3f>> PositionsToMoveFrom);` (scope `UE::DataflowSimulationGeometryCache`) — Saves skinned asset positions into the geometry cache
- L21 _prototype_ `void SaveGeometryCache(UGeometryCache& GeometryCache, float FrameRate, const UStaticMesh& StaticMesh, TArrayView<TArray<FVector3f>> PositionsToMoveFrom);` (scope `UE::DataflowSimulationGeometryCache`) — Saves static mesh positions into the geometry cache
- L24 _prototype_ `void SavePackage(UObject& Object);` (scope `UE::DataflowSimulationGeometryCache`) — Saves the geometry cache

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSimulationScene.h` (Public)


#### class `UDataflowSimulationSettings`  
`class UDataflowSimulationSettings : public UDataflowEditorSettings`  
_L28-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataflowEditorSettings`
- L34 _public member_ `bool bIsSimulationPlayingByDefault = false;` — `UPROPERTY()`
- L37 _public member_ `bool bIsAsyncCachingSupported = false;` — `UPROPERTY()`
- L40 _public member_ `bool bIsAsyncCachingEnabledByDefault = false;` — `UPROPERTY()`
- L43 _public member_ `bool bIsGeometryCacheOutputSupported = false;` — `UPROPERTY()`

#### class `UDataflowSimulationSceneDescription`  
`class UDataflowSimulationSceneDescription : public UObject`  
_L47-139_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L52 _public member_ `FDataflowSimulationSceneDescriptionChanged DataflowSimulationSceneDescriptionChanged;`
- L54 _public function_ `UDataflowSimulationSceneDescription()`
- L60 _public prototype_ `void SetSimulationScene(class FDataflowSimulationScene* SimulationScene);` — Set the simulation scene
- L63 _public prototype_ `void SetBlueprintClass(TSubclassOf<AActor> InBlueprintClass);` — Set the Blueprint.
- L66 _public prototype_ `const TSubclassOf<AActor>& GetBlueprintClass() const;` — Return the Blueprint.
- L71 _public member_ `TSubclassOf<AActor> BlueprintClass;` — `UE_DEPRECATED(5.8, "Use the SetBlueprintClass setter/getter instead as to get correct operations.")` — `UPROPERTY(EditAnywhere, Setter = SetBlueprintClass, Getter = GetBlueprintClass, Category = "Scene")` — Caching blueprint actor class to spawn
- L74 _public member_ `FInstancedPropertyBag BlueprintVariables;` — `UPROPERTY(EditAnywhere, Category = "Scene|BlueprintVariables", Meta = (FixedLayout, ShowOnlyInnerProperties))`
- L78 _public member_ `FTransform BlueprintTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, Category = "Scene")` — Blueprint actor transform
- L81 _public member_ `bool bPauseSimulationViewportWhenPlayingInEditor = true;` — `UPROPERTY(EditAnywhere, Category = "Viewport")`
- L84 _public member_ `bool bPauseSimulationViewportWhenNotFocused = true;` — `UPROPERTY(EditAnywhere, Category = "Viewport")`
- L88 _public member_ `TObjectPtr<UChaosCacheCollection> CacheAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category="Caching", DisplayName="Cache Collection")` — Caching asset to be used to record the simulation
- L92 _public member_ `FDataflowPreviewCacheParams CacheParams;` — `UPROPERTY(EditAnywhere, Category="Caching")` — Caching params used to record the simulation
- L95 _public member_ `bool bIsGeometryCacheOutputSupported = false;` — `UPROPERTY()`
- L99 _public member_ `TObjectPtr<UGeometryCache> GeometryCacheAsset = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Geometry Cache", DisplayName="Geometry Cache", meta=(EditCondition = "bIsGeometryCacheOutputSupported && CacheAsset != nullptr", EditConditionHides))` — Geometry cache asset used to extract skeletal mesh results from simulation
- L103 _public member_ `TObjectPtr<USkeletalMesh> EmbeddedSkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Geometry Cache", meta = (EditCondition = "bIsGeometryCacheOutputSupported && CacheAsset != nullptr && EmbeddedStaticMesh == nullptr", EditConditionHides))` — Skeletal mesh interpolated from simulation. This should match the SkeletalMesh used in GenerateSurfaceBindings node
- L107 _public member_ `TObjectPtr<UStaticMesh> EmbeddedStaticMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Geometry Cache", meta = (EditCondition = "bIsGeometryCacheOutputSupported && CacheAsset != nullptr && EmbeddedSkeletalMesh == nullptr", EditConditionHides))` — Static mesh interpolated from simulation. This should match the Static mesh used in GenerateSurfaceBindings node
- L111 _public prototype_ `void GenerateGeometryCache();` — `UFUNCTION(CallInEditor, Category = "Geometry Cache")` — Interpolates and saves geometry cache from Chaos cache
- L115 _public prototype_ `void NewGeometryCache();` — `UFUNCTION(CallInEditor, Category = "Geometry Cache")` — Creates a new geometry cache file
- L119 _public member_ `bool bSkeletalMeshVisibility = true;` — `UPROPERTY(EditAnywhere, Category = "Skeletal Mesh")` — Visibility of the skeletal mesh
- L123 _private prototype_ `virtual void PreEditChange(class FProperty* PropertyAboutToChange) override;`
- L124 _private prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L125 _private prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L126 _private prototype_ `virtual void BeginDestroy() override;`
- L128 _private prototype_ `void OnBlueprintClassPreChanged();`
- L129 _private prototype_ `void OnBlueprintClassPostChanged();`
- L130 _private prototype_ `void UpdateBlueprintVariables(class UBlueprint* Blueprint);`
- L131 _private prototype_ `void RegisterOnBlueprintCompiledDelegate();`
- L132 _private prototype_ `void UnregisterOnBlueprintCompiledDelegate();`
- L135 _private member_ `class FDataflowSimulationScene* SimulationScene;` — Simulation scene linked to that descriptor
- L138 _private member_ `TArray<TArray<FVector3f>> RenderPositions;` — Render geometry positions from interpolation

#### class `FDataflowSimulationScene`  
`class FDataflowSimulationScene : public FDataflowPreviewSceneBase`  
_L144-312_
- inherits: `FDataflowPreviewSceneBase`
- desc: Dataflow simulation scene holding all the dataflow content components
- L148 _public prototype_ `FDataflowSimulationScene(FPreviewScene::ConstructionValues ConstructionValues, UDataflowEditor* Editor);`
- L151 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L153 _public prototype_ `virtual ~FDataflowSimulationScene();`
- L156 _public prototype_ `void OnObjectsReinstanced(const TMap<UObject*, UObject*>& ObjectsMap);` — Functions that will be triggered when objects will be reinstanced (BP compilation)
- L159 _public prototype_ `virtual void TickDataflowScene(const float DeltaSeconds) override;` — Tick data flow scene
- L162 _public function_ `virtual bool CanRunSimulation() const` — Check if the preview scene can run simulation
- L165 _public prototype_ `virtual FBox GetBoundingBox() const override;` — Get the bounding box for the selected components or the entire sim scene
- L168 _public function_ `UDataflowSimulationSceneDescription* GetPreviewSceneDescription() const` — Get the scene description used in the preview scene widget
- L171 _public prototype_ `void CreateSimulationScene();` — Create all the simulation world components and instances
- L174 _public prototype_ `void ResetSimulationScene();` — Reset all the simulation world components and instances
- L177 _public prototype_ `void PauseSimulationScene() const;` — Pause the simulation
- L180 _public prototype_ `void StartSimulationScene() const;` — Start the simulation
- L183 _public prototype_ `void StepSimulationScene() const;` — Step the simulation
- L186 _public prototype_ `bool IsSimulationEnabled() const;` — Gets whether the simulation is running
- L189 _public prototype_ `void SetSimulationEnabled(bool bEnable) const;` — Sets whether the simulation should be enabled or not
- L192 _public prototype_ `bool HasCachingEnabled() const;` — Check if caching is enabled or not
- L195 _public prototype_ `void RebuildSimulationScene();` — Rebuild the simulation scene
- L198 _public function_ `bool HasRenderableGeometry()` — Check if there is something to render
- L201 _public prototype_ `void SceneDescriptionPropertyChanged(const FName& PropertyName);` — Update Scene in response to the SceneDescription changing
- L204 _public prototype_ `void RecordSimulationCache();` — Record the simulation cache
- L207 _public prototype_ `void UpdateSimulationCache();` — Update the simulation cache
- L210 _public function_ `const FVector2f& GetTimeRange() const` — Get the simulation time range
- L213 _public prototype_ `void SetTimeRange(const FVector2f& NewTimeRange);` — Set the simulation time range
- L216 _public function_ `const int32& GetNumFrames() const` — Get the number of frames
- L219 _public function_ `const int32 GetFrameRate() const` — Get the frame rate
- L222 _public function_ `const int32 GetSubframeRate() const` — Get the subframe rate
- L225 _public function_ `float GetDeltaTime() const` — Get delta time
- L228 _public member_ `float SimulationTime = 0.0f;` — Simulation time used to drive the cache loading
- L231 _public member_ `float PreviousTime = 0.0f;` — Previous simulation time
- L234 _public function_ `TObjectPtr<AActor> GetPreviewActor()` — Preview actor accessors
- L235 _public function_ `const TObjectPtr<AActor> GetPreviewActor() const`
- L238 _public prototype_ `void SetPreviewLOD(int32 InLOD);` — LOD for preview actor components
- L239 _public prototype_ `int32 GetPreviewLOD() const;`
- L242 _public function_ `bool IsSimulationLocked() const` — Check if the simulation is locked or not
- L245 _public prototype_ `void SetSimulationLocked(const bool bSimulationLocked, const bool bIsPlaying);` — Set the locked simulation flag
- L247 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeRangeUpdated, const FDataflowSimulationScene&);`
- L248 _public member_ `FOnTimeRangeUpdated OnTimeRangeUpdated;`
- L254 _private prototype_ `void BindSceneSelection();` — Bind the scene selection to the components
- L257 _private prototype_ `void UnbindSceneSelection();` — Unbind the scene selection from the components
- L260 _private prototype_ `void ReadPreviewPropertiesFromDataflowOwner();` — Sync the blueprint preview properties with the edited asset.
- L263 _private prototype_ `void WritePreviewPropertiesToDataflowOwner() const;` — Sync the blueprint preview properties with the edited asset.
- L265 _private prototype_ `void UpdateTimelinedataFromAnimations();`
- L268 _private prototype_ `void BroadcastTimeRangeUpdated();` — Recompute NumFrames from TimeRange and broadcast OnTimeRangeUpdated.
- L272 _private prototype_ `void OnEditorContentPropertyChanged(UObject* Object, struct FPropertyChangedEvent& Event);` — Called when any UObject property changes - filters for animation changes on our editor content
- L276 _private member_ `TObjectPtr<UDataflowSimulationSceneDescription> SceneDescription;` — Simulation scene description
- L279 _private member_ `TSharedPtr<UE::Dataflow::FDataflowSimulationGenerator> SimulationGenerator;` — Simulation generator to record the simulation result
- L282 _private member_ `FVector2f TimeRange;` — Cache time range in seconds
- L285 _private member_ `int32 NumFrames;` — Number of cache frames
- L288 _private member_ `float DeltaTime;` — Delta time (1/fps)
- L291 _private member_ `UE::Dataflow::FTimestamp LastTimeStamp = UE::Dataflow::FTimestamp::Invalid;` — Last context time stamp for which we regenerated the world
- L294 _private member_ `TObjectPtr<AActor> PreviewActor;` — Preview actor that will will be used to visualize the result of the simulation graph
- L297 _private member_ `FDelegateHandle OnObjectsReinstancedHandle;` — Handle for the delegate
- L301 _private member_ `FDelegateHandle OnObjectPropertyChangedHandle;` — Handle for the object property changed delegate to detect animation changes
- L305 _private member_ `int32 CurrentPreviewLOD = INDEX_NONE;` — Preview LOD used in the simulation viewport
- L308 _private member_ `bool bIsRecordingCache = false;` — Boolean to check if we are recording the cache or not
- L311 _private member_ `bool bIsSimulationLocked = false;` — Boolean to check if the simulation is locked onto the timeline

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L25 _delegate_ `DECLARE_EVENT(UDataflowSimulationSceneDescription, FDataflowSimulationSceneDescriptionChanged) UCLASS(MinimalAPI) class UDataflowSimulationSettings : public UDataflowEditorSettings { public: GENERATED_BODY() UPROPERTY() bool bIsSimulationPlayingByDefault = false; UPROPERTY() bool bIsAsyncCachingSupported = false; UPROPERTY() bool bIsAsyncCachingEnabledByDefault = false; UPROPERTY() bool bIsGeometryCacheOutputSupported = false; };`
- L247 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimeRangeUpdated, const FDataflowSimulationScene&);`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSimulationViewportClient.h` (Public)


#### class `FDataflowSimulationViewportClient`  
`class FDataflowSimulationViewportClient : public FDataflowEditorViewportClientBase`  
_L16-65_
- inherits: `FDataflowEditorViewportClientBase`
- L20 _public typedef_ `using Super = FDataflowEditorViewportClientBase;`
- L22 _public prototype_ `FDataflowSimulationViewportClient(FEditorModeTools* InModeTools, TWeakPtr<FDataflowSimulationScene> InSimulationScene, const bool bCouldTickScene, const TWeakPtr<SEditorViewport> InEditorViewportWidget = nullptr);`
- L25 _public prototype_ `virtual ~FDataflowSimulationViewportClient();`
- L28 _public prototype_ `void SetDataflowEditorToolkit(TWeakPtr<FDataflowEditorToolkit> DataflowToolkit);` — Set the data flow toolkit used to create the client
- L31 _public function_ `const TWeakPtr<FDataflowEditorToolkit>& GetDataflowEditorToolkit() const` — Get the data flow toolkit
- L34 _public prototype_ `void SetToolCommandList(TWeakPtr<FUICommandList> ToolCommandList);` — Set the tool command list
- L37 _public function_ `virtual FString GetReferencerName() const override` — FGCObject Interface
- L39 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedMulticast, const TArray<UPrimitiveComponent*>&, const TArray<FDataflowBaseElement*>&) FOnSelectionChangedMulticast OnSelectionChangedMulticast;`
- L43 _private prototype_ `bool IsDataflowEditorTabActive() const;`
- L46 _private prototype_ `virtual void OnViewportClicked(HHitProxy* HitProxy) override;` — FDataflowEditorViewportClientBase
- L49 _private prototype_ `virtual void Tick(float DeltaSeconds) override;` — FEditorViewportClient interface
- L50 _private prototype_ `virtual void ProcessClick(FSceneView& View, HHitProxy* HitProxy, FKey Key, EInputEvent Event, uint32 HitX, uint32 HitY) override;`
- L51 _private prototype_ `virtual void Draw(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L52 _private prototype_ `virtual void DrawCanvas(FViewport& InViewport, FSceneView& View, FCanvas& Canvas) override;`
- L55 _private member_ `TWeakPtr<FDataflowEditorToolkit> DataflowEditorToolkitPtr = nullptr;` — Toolkit used to create the viewport client
- L58 _private member_ `TWeakPtr<FDataflowSimulationScene> DataflowSimulationScenePtr;` — strongly typed simulation scene
- L61 _private member_ `TWeakPtr<FUICommandList> ToolCommandList;` — @todo(brice) : Is this needed?
- L64 _private member_ `bool bEnableSceneTicking = false;` — Flag to enable scene ticking from the client

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L39 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChangedMulticast, const TArray<UPrimitiveComponent*>&, const TArray<FDataflowBaseElement*>&) FOnSelectionChangedMulticast OnSelectionChangedMulticast;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowSimulationVisualization.h` (Public)


#### class `UE::Dataflow::IDataflowSimulationVisualization`  
`class IDataflowSimulationVisualization`  
_L19-30_
- L22 _public prototype_ `virtual ~IDataflowSimulationVisualization() = default;`
- L24 _public prototype_ `virtual FName GetName() const = 0;`
- L25 _public function_ `virtual void ExtendSimulationVisualizationMenu(const TSharedPtr<FDataflowSimulationViewportClient>& ViewportClient, FMenuBuilder& MenuBuilder)`
- L26 _public function_ `virtual void Draw(const FDataflowSimulationScene* SimulationScene, FPrimitiveDrawInterface* PDI)`
- L27 _public function_ `virtual void DrawCanvas(const FDataflowSimulationScene* SimulationScene, FCanvas* Canvas, const FSceneView* SceneView)`
- L28 _public function_ `virtual FText GetDisplayString(const FDataflowSimulationScene* SimulationScene) const`
- L29 _public function_ `virtual void SimulationSceneUpdated(const FDataflowSimulationScene* SimulationScene)`

#### class `UE::Dataflow::FDataflowSimulationVisualizationRegistry`  
`class FDataflowSimulationVisualizationRegistry`  
_L32-49_
- L37 _public prototype_ `static FDataflowSimulationVisualizationRegistry& GetInstance();` — FLazySingleton
- L38 _public prototype_ `static void TearDown();`
- L40 _public prototype_ `void RegisterVisualization(TUniquePtr<IDataflowSimulationVisualization>&& Visualization);`
- L41 _public prototype_ `void DeregisterVisualization(const FName& VisualizationName);`
- L43 _public prototype_ `const TMap<FName, TUniquePtr<IDataflowSimulationVisualization>>& GetVisualizations() const;`
- L44 _public prototype_ `const IDataflowSimulationVisualization* GetVisualization(const FName& VisualizationOption) const;`
- L48 _private member_ `TMap<FName, TUniquePtr<IDataflowSimulationVisualization>> VisualizationMap;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowTemplateRegistry.h` (Public)


#### struct `FDataflowTemplateOption`  
`struct FDataflowTemplateOption`  
_L10-18_
- desc: One template entry
- L12 _public member_ `FText DisplayName;`
- L13 _public member_ `FText Tooltip;`
- L15 _public member_ `const FSlateBrush* Icon = nullptr;` — Icon shown in the tile. Pass nullptr to fall back to a generic dataflow icon.
- L17 _public member_ `FName TemplateId;` — Opaque identifier returned to the caller in the result.

#### struct `FDataflowTemplateAssetRegistration`  
`struct FDataflowTemplateAssetRegistration`  
_L30-46_
- desc: Describes a single UDataflow asset to expose as a named template for a specific asset class. Passed to FDataflowTemplateRegistry::RegisterTemplateAsset at module startup. Example: FDataflowTemplateRegistry::Get().RegisterTemplateAsset( UGroomAsset::StaticClass(), { FSoftObjectPath(TEXT("/GroomEditor/Dataflow/Templates/DF_BasicHair")), LOCTEXT("BasicHair", "Basic Hair"), {}, FSlateIcon("GroomEditorStyle", "ClassThumbnail.GroomAsset") });
- L33 _public member_ `FSoftObjectPath AssetPath;` — Soft path to the specific UDataflow asset.
- L36 _public member_ `FText DisplayName;` — Tile label. If empty, derived from the asset name (strips "DF_", replaces underscores with spaces).
- L39 _public member_ `FText Tooltip;` — Tooltip shown on hover. If empty, defaults to the asset object path.
- L45 _public member_ `FSlateIcon Icon;` — Tile icon. Falls back to the generic Dataflow icon if not set. e.g. FSlateIcon("GroomEditorStyle", "ClassThumbnail.GroomAsset").

#### struct `FDataflowTemplateFolderRegistration`  
`struct FDataflowTemplateFolderRegistration`  
_L52-64_
- desc: Describes a content folder containing UDataflow template assets for a specific asset class. Passed to FDataflowTemplateRegistry::RegisterTemplateFolder at module startup.
- L55 _public member_ `FString ContentFolder;` — Content path to scan recursively, e.g. "/Game/Dataflow/Templates/Cloth".
- L63 _public member_ `FSlateIcon Icon;` — Icon for every template found in this folder. Using FSlateIcon allows referencing brushes from any style set, not just FAppStyle — required for class icons that live in plugin style sets (e.g. FSlateIcon("GroomEditorStyle", "ClassIcon.GroomAsset")). A default Dataflow icon is used when the icon is not set.

#### class `FDataflowTemplateRegistry`  
`class FDataflowTemplateRegistry`  
_L80-111_
- desc: Registry mapping asset classes to content folders containing UDataflow template assets. Modules register their template folders in StartupModule. When the Dataflow picker dialog opens for an asset, it queries this registry to populate the template tile list. Registrations for parent classes are automatically included (class hierarchy walk, most-derived first). Example (in a plugin's editor module StartupModule): FDataflowTemplateRegistry::Get().RegisterTemplateFolder( UChaosClothAsset::StaticClass(), { TEXT("/ChaosClothEditor/Dataflow/Templates"), FSlateIcon("ChaosClothEditorStyle", "ClassIcon.ChaosClothAsset") });
- L83 _public prototype_ `static FDataflowTemplateRegistry& Get();`
- L90 _public prototype_ `void RegisterTemplateAsset(const UClass* AssetClass, FDataflowTemplateAssetRegistration Registration);` — Register a single UDataflow asset as a template for the given asset class. Registrations are visible for subclasses of AssetClass. Safe to call from any module's StartupModule (game thread only).
- L97 _public prototype_ `void RegisterTemplateFolder(const UClass* AssetClass, FDataflowTemplateFolderRegistration Registration);` — Register a content folder to scan for UDataflow template assets for a given asset class. Registrations are also visible when the picker is opened for any subclass of AssetClass. Safe to call from any module's StartupModule (game thread only).
- L105 _public prototype_ `TArray<FDataflowTemplateOption> GetTemplateOptions(const UClass* AssetClass, bool bAddDefaultBlankOption = true) const;` — Build template options for the given asset class by scanning all registered folders (including those registered for parent classes, most-derived first). A "Blank" option is always prepended. Queries the asset registry synchronously — call from the game thread only.
- L109 _private member_ `TMap<FTopLevelAssetPath, TArray<FDataflowTemplateAssetRegistration>> AssetRegistrations;` — Keyed by class path so we don't hold raw UClass* pointers across module reloads.
- L110 _private member_ `TMap<FTopLevelAssetPath, TArray<FDataflowTemplateFolderRegistration>> Registrations;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowToolRegistry.h` (Public)


#### class `UE::Dataflow::FDataflowToolRegistry`  
`class FDataflowToolRegistry`  
_L19-102_
- L33 _public prototype_ `static FDataflowToolRegistry& Get();`
- L34 _public prototype_ `static void TearDown();`
- L36 _public prototype_ `void AddNodeToToolMapping(const FName& NodeName, TObjectPtr<UInteractiveToolBuilder> ToolBuilder, const TSharedRef<const IDataflowToolActionCommands>& ToolActionCommands, const FSlateIcon& AddNodeButtonIcon, const FText& AddNodeButtonText, const FName& ToolCategory = FName("General"), const FName& AddNodeConnectionType = FName("FManagedArrayCollection"), const FName& AddNodeConnectionName = FName("Collection") );`
- L47 _public function_ `void AddNodeToToolMapping(const FName& NodeName, TObjectPtr<UInteractiveToolBuilder> ToolBuilder, const TSharedRef<const IDataflowToolActionCommands>& ToolActionCommands)` — `UE_DEPRECATED(5.6, "Please use the version of AddNodeToToolMapping taking AddNodeButtonIcon and AddNodeButtonText")`
- L54 _public prototype_ `void RemoveNodeToToolMapping(const FName& NodeName);`
- L56 _public prototype_ `TArray<FName> GetNodeNames() const;`
- L58 _public function_ `bool HasToolInfoForNodeType(const FName& NodeType) const`
- L63 _public prototype_ `TSharedPtr<FUICommandInfo>& GetAddNodeCommandForNode(const FName& NodeType);`
- L64 _public prototype_ `const FSlateIcon& GetAddNodeButtonIcon(const FName& NodeType) const;`
- L65 _public prototype_ `const FText& GetAddNodeButtonText(const FName& NodeType) const;`
- L66 _public prototype_ `const FName& GetAddNodeConnectionType(const FName& NodeType) const;`
- L67 _public prototype_ `const FName& GetAddNodeConnectionName(const FName& NodeType) const;`
- L69 _public prototype_ `TSharedPtr<FUICommandInfo>& GetToolCommandForNode(const FName& NodeName);`
- L72 _public prototype_ `const FName& GetToolCategoryForNode(const FName& NodeName) const;` — Return the category the tool has been registered in
- L74 _public prototype_ `UInteractiveToolBuilder* GetToolBuilderForNode(const FName& NodeName);`
- L75 _public prototype_ `const UInteractiveToolBuilder* GetToolBuilderForNode(const FName& NodeName) const;`
- L77 _public prototype_ `void UnbindActiveCommands(const TSharedPtr<FUICommandList>& UICommandList) const;`
- L78 _public prototype_ `void BindCommandsForCurrentTool(const TSharedPtr<FUICommandList>& UICommandList, UInteractiveTool* Tool) const;`
- L100 _private member_ `TMap<FName, FToolInfo> NodeTypeToToolMap;`

#### class `UE::Dataflow::FDataflowToolRegistry::IDataflowToolActionCommands`  
`class IDataflowToolActionCommands`  
_L25-31_
- desc: Interface for binding/unbinding tool actions. When a tool begins or ends we switch out the currently available FUICommandList. This allows multiple tools to have individual hotkey actions with the same key chords, for example.
- L28 _public prototype_ `virtual ~IDataflowToolActionCommands() = default;`
- L29 _public prototype_ `virtual void UnbindActiveCommands(const TSharedPtr<FUICommandList>& UICommandList) const = 0;`
- L30 _public prototype_ `virtual void BindCommandsForCurrentTool(const TSharedPtr<FUICommandList>& UICommandList, UInteractiveTool* Tool) const = 0;`

#### struct `UE::Dataflow::FDataflowToolRegistry::FToolInfo`  
`struct FToolInfo`  
_L82-98_
- L85 _public member_ `TObjectPtr<UInteractiveToolBuilder> ToolBuilder;` — Specified when registering the tool
- L86 _public member_ `TSharedRef<const IDataflowToolActionCommands> ToolActionCommands;`
- L87 _public member_ `FSlateIcon AddNodeButtonIcon;`
- L88 _public member_ `FText AddNodeButtonText;`
- L89 _public member_ `FName AddNodeConnectionType;`
- L90 _public member_ `FName AddNodeConnectionName;`
- L93 _public member_ `TSharedPtr<FUICommandInfo> AddNodeCommand;` — Constructed automatically in FDataflowEditorCommandsImpl::RegisterCommands
- L94 _public member_ `TSharedPtr<FUICommandInfo> ToolCommand;`
- L97 _public member_ `FName ToolCategory;` — Tool category for filtering

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowTransformOutlinerWidget.h` (Public)


#### class `FDataflowOutlinerTreeItem`  
`class FDataflowOutlinerTreeItem : public TSharedFromThis<FDataflowOutlinerTreeItem>`  
_L30-40_
- inherits: `TSharedFromThis<FDataflowOutlinerTreeItem>`
- L33 _public prototype_ `virtual ~FDataflowOutlinerTreeItem() = default;`
- L34 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false) = 0;`
- L35 _public prototype_ `virtual void GetChildren(FDataflowOutlinerTreeItemList& OutChildren) = 0;`
- L37 _public function_ `virtual int32 GetBoneIndex() const`
- L39 _public prototype_ `void GenerateContextMenu(UToolMenu* Menu, STransformOutliner& Outliner);`

#### class `FDataflowOutlinerTreeItemCollection`  
`class FDataflowOutlinerTreeItemCollection : public FDataflowOutlinerTreeItem`  
_L42-94_
- inherits: `FDataflowOutlinerTreeItem`
- L45 _public function_ `FDataflowOutlinerTreeItemCollection(TSharedPtr<const FManagedArrayCollection> InCollection, FName InOutputName, TSharedPtr<STreeView<FDataflowOutlinerTreeItemPtr>> InTreeView) : Collection(InCollection) , OutputName(InOutputName) , TreeView(InTreeView)`
- L53 _public prototype_ `virtual ~FDataflowOutlinerTreeItemCollection() = default;`
- L56 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FDataflowOutlinerTreeItem interface
- L57 _public prototype_ `virtual void GetChildren(FDataflowOutlinerTreeItemList& OutChildren) override;`
- L59 _public prototype_ `FDataflowOutlinerTreeItemPtr GetItemFromBoneIndex(int32 BoneIndex) const;`
- L61 _public prototype_ `void GetChildrenForBone(FDataflowOutlinerTreeItemBone& BoneItem, FDataflowOutlinerTreeItemList& OutChildren) const;`
- L62 _public prototype_ `bool HasChildrenForBone(const FDataflowOutlinerTreeItemBone& BoneItem) const;`
- L64 _public prototype_ `void ExpandAll();`
- L65 _public prototype_ `void RegenerateChildren();`
- L66 _public prototype_ `void RequestTreeRefresh();`
- L67 _public prototype_ `void ExpandByLevel(const int32 InLevel);`
- L69 _public function_ `TSharedPtr<const FManagedArrayCollection> GetCollection()`
- L71 _public prototype_ `bool IsValid() const;`
- L74 _public function_ `void Invalidate()` — Mark item as unused/invalid; helpful because slate defers destroying tree items and can still run callbacks on them until tick
- L80 _private prototype_ `bool FilterBoneIndex(int32 BoneIndex) const;`
- L82 _private member_ `TSharedPtr<const FManagedArrayCollection> Collection;`
- L83 _private member_ `FName OutputName;`
- L85 _private member_ `TSharedPtr<STreeView<FDataflowOutlinerTreeItemPtr>> TreeView;`
- L88 _private member_ `TArray<FDataflowOutlinerTreeItemPtr> ChildItems;` — The direct children under this component
- L89 _private member_ `TMap<int32, FDataflowOutlinerTreeItemPtr> ItemsByBoneIndex;`
- L90 _private member_ `int32 RootIndex;`
- L93 _private member_ `bool bInvalidated = false;` — track whether the item has been explicitly invalidated

#### class `FDataflowOutlinerTreeItemBone`  
`class FDataflowOutlinerTreeItemBone : public FDataflowOutlinerTreeItem`  
_L96-126_
- inherits: `FDataflowOutlinerTreeItem`
- L99 _public function_ `FDataflowOutlinerTreeItemBone(const int32 InBoneIndex, FDataflowOutlinerTreeItemCollection* InParentCollectionItem) : BoneIndex(InBoneIndex) , ParentCollectionItem(InParentCollectionItem) , ItemColor(FSlateColor::UseForeground())`
- L106 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FDataflowOutlinerTreeItem interface
- L107 _public prototype_ `TSharedRef<SWidget> MakeIndexColumnWidget() const;`
- L109 _public prototype_ `TSharedRef<SWidget> MakeEmptyColumnWidget() const;` — TSharedRef<SWidget> MakeSimulationTypeColumnWidget() const;
- L111 _public prototype_ `virtual void GetChildren(FDataflowOutlinerTreeItemList& OutChildren) override;`
- L112 _public prototype_ `bool IsValidBone() const;`
- L113 _public function_ `virtual int32 GetBoneIndex() const override`
- L114 _public function_ `FSlateColor GetItemColor() const`
- L115 _public prototype_ `bool HasChildren() const;`
- L116 _public prototype_ `TSharedPtr<const FManagedArrayCollection> GetCollection() const;`
- L121 _private prototype_ `void UpdateItemColorFromCollection();`
- L123 _private member_ `const int32 BoneIndex;`
- L124 _private member_ `FDataflowOutlinerTreeItemCollection* ParentCollectionItem;`
- L125 _private member_ `FSlateColor ItemColor;`

#### class `STransformOutlinerRow`  
`class STransformOutlinerRow : public SMultiColumnTableRow<FDataflowOutlinerTreeItemBonePtr>`  
_L128-147_
- inherits: `SMultiColumnTableRow<FDataflowOutlinerTreeItemBonePtr>`
- L131 _protected member_ `FDataflowOutlinerTreeItemBonePtr Item;`
- L134 _public function_ `SLATE_BEGIN_ARGS(STransformOutlinerRow)`
- L135 _public prototype_ `SLATE_END_ARGS() virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L139 _public function_ `void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, FDataflowOutlinerTreeItemBonePtr InItemToEdit)`

#### class `STransformOutliner`  
`class STransformOutliner : public SCompoundWidget`  
_L149-188_
- inherits: `SCompoundWidget`
- L151 _private function_ `SLATE_BEGIN_ARGS(STransformOutliner)`
- L156 _public prototype_ `void Construct(const FArguments& InArgs);`
- L158 _public prototype_ `void RegenerateItems();`
- L159 _public prototype_ `void RegenerateHeader();`
- L161 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(FDataflowOutlinerTreeItemPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L162 _public prototype_ `TSharedRef<ITableRow> OnGeneratePinnedRowWidget(FDataflowOutlinerTreeItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable, bool bPinned);`
- L163 _public prototype_ `void OnGetChildren(TSharedPtr<FDataflowOutlinerTreeItem> InInfo, TArray< TSharedPtr<FDataflowOutlinerTreeItem> >& OutChildren);`
- L164 _public prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();`
- L166 _public prototype_ `void UpdateGeometryCollection();`
- L167 _public prototype_ `void SetCollection(const TSharedPtr<const FManagedArrayCollection>& InCollection, const FName InOutputName);`
- L168 _public prototype_ `int32 GetBoneSelectionCount() const;`
- L170 _public prototype_ `void ExpandAll();`
- L171 _public prototype_ `void ExpandRecursive(TSharedPtr<FDataflowOutlinerTreeItem> TreeItem, bool bInExpansionState) const;`
- L172 _public prototype_ `void ExpandByLevel(const int32 InLevel);`
- L174 _public member_ `int32 DisplayLevel = -1;`
- L176 _public prototype_ `void ContextMenuExpandAll();`
- L177 _public prototype_ `void ContextMenuPreviousLevel();`
- L178 _public prototype_ `void ContextMenuNextLevel();`
- L181 _private prototype_ `void OnSelectionChanged(FDataflowOutlinerTreeItemPtr Item, ESelectInfo::Type SelectInfo);`
- L183 _private member_ `TSharedPtr<STreeView<FDataflowOutlinerTreeItemPtr>> TreeView;`
- L184 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L185 _private member_ `TArray<TSharedPtr<FDataflowOutlinerTreeItemCollection>> RootNodes;`
- L186 _private member_ `bool bPerformingSelection;`
- L187 _private member_ `TSharedPtr<const FManagedArrayCollection> Collection;`

#### Free symbols / members of external scopes

- L26 _typedef_ `typedef TArray<TSharedPtr<FDataflowOutlinerTreeItem>> FDataflowOutlinerTreeItemList;`
- L27 _typedef_ `typedef TSharedPtr<FDataflowOutlinerTreeItem> FDataflowOutlinerTreeItemPtr;`
- L28 _typedef_ `typedef TSharedPtr<class FDataflowOutlinerTreeItemBone> FDataflowOutlinerTreeItemBonePtr;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/DataflowVerticesOutlinerWidget.h` (Public)


#### class `FGeometryCollectionVerticesTreeItem`  
`class FGeometryCollectionVerticesTreeItem : public TSharedFromThis<FGeometryCollectionVerticesTreeItem>`  
_L26-36_
- inherits: `TSharedFromThis<FGeometryCollectionVerticesTreeItem>`
- L29 _public prototype_ `virtual ~FGeometryCollectionVerticesTreeItem() = default;`
- L30 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false) = 0;`
- L31 _public prototype_ `virtual void GetChildren(FGeometryCollectionVerticesTreeItemList& OutChildren) = 0;`
- L33 _public function_ `virtual int32 GetVertexIndex() const`
- L35 _public prototype_ `void GenerateContextMenu(UToolMenu* Menu, SVerticesOutliner& Outliner);`

#### class `FGeometryCollectionVerticesTreeItemGeometry`  
`class FGeometryCollectionVerticesTreeItemGeometry : public FGeometryCollectionVerticesTreeItem`  
_L38-89_
- inherits: `FGeometryCollectionVerticesTreeItem`
- L41 _public function_ `FGeometryCollectionVerticesTreeItemGeometry(TSharedPtr<const FManagedArrayCollection> InCollection, int32 InGeoemtryIdx, TSharedPtr<STreeView<FGeometryCollectionVerticesTreeItemPtr>> InTreeView) : Collection(InCollection) , GeometryIdx(InGeoemtryIdx) , TreeView(InTreeView)`
- L49 _public prototype_ `virtual ~FGeometryCollectionVerticesTreeItemGeometry() = default;`
- L52 _public prototype_ `virtual TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FGeometryCollectionVerticesTreeItem interface
- L53 _public prototype_ `virtual void GetChildren(FGeometryCollectionVerticesTreeItemList& OutChildren) override;`
- L55 _public prototype_ `FGeometryCollectionVerticesTreeItemPtr GetItemFromVertexIndex(int32 InVertexIndex) const;`
- L57 _public prototype_ `void GetChildrenForVertex(FGeometryCollectionVerticesTreeItemVertex& VertexItem, FGeometryCollectionVerticesTreeItemList& OutChildren) const;`
- L58 _public prototype_ `bool HasChildrenForVertex(const FGeometryCollectionVerticesTreeItemVertex& VertexItem) const;`
- L60 _public prototype_ `void ExpandAll();`
- L61 _public prototype_ `void RegenerateChildren();`
- L62 _public prototype_ `void RequestTreeRefresh();`
- L64 _public function_ `TSharedPtr<const FManagedArrayCollection> GetCollection()`
- L66 _public prototype_ `bool IsValid() const;`
- L69 _public function_ `void Invalidate()` — Mark item as unused/invalid; helpful because slate defers destroying tree items and can still run callbacks on them until tick
- L75 _private prototype_ `bool FilterBoneIndex(int32 BoneIndex) const;`
- L77 _private member_ `TSharedPtr<const FManagedArrayCollection> Collection;`
- L78 _private member_ `int32 GeometryIdx;`
- L80 _private member_ `TSharedPtr<STreeView<FGeometryCollectionVerticesTreeItemPtr>> TreeView;`
- L83 _private member_ `TArray<FGeometryCollectionVerticesTreeItemPtr> ChildItems;` — The direct children under this component
- L84 _private member_ `TMap<int32, FGeometryCollectionVerticesTreeItemPtr> ItemsByVertexIndex;`
- L85 _private member_ `int32 RootIndex;`
- L88 _private member_ `bool bInvalidated = false;` — track whether the item has been explicitly invalidated

#### class `FGeometryCollectionVerticesTreeItemVertex`  
`class FGeometryCollectionVerticesTreeItemVertex : public FGeometryCollectionVerticesTreeItem`  
_L91-120_
- inherits: `FGeometryCollectionVerticesTreeItem`
- L94 _public function_ `FGeometryCollectionVerticesTreeItemVertex(const int32 InVertexIndex, FGeometryCollectionVerticesTreeItemGeometry* InParentCollectionItem) : VertexIndex(InVertexIndex) , ParentCollectionItem(InParentCollectionItem) , ItemColor(FSlateColor::UseForeground())`
- L101 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, bool bIsPinned = false);` — FGeometryCollectionVerticesTreeItem interface
- L102 _public prototype_ `TSharedRef<SWidget> MakeIndexColumnWidget() const;`
- L103 _public prototype_ `TSharedRef<SWidget> MakeEmptyColumnWidget() const;`
- L105 _public prototype_ `virtual void GetChildren(FGeometryCollectionVerticesTreeItemList& OutChildren) override;`
- L106 _public prototype_ `bool IsValidVertex() const;`
- L107 _public function_ `virtual int32 GetVertexIndex() const override`
- L108 _public function_ `FSlateColor GetItemColor() const`
- L109 _public prototype_ `bool HasChildren() const;`
- L110 _public prototype_ `TSharedPtr<const FManagedArrayCollection> GetCollection() const;`
- L115 _private prototype_ `void UpdateItemColorFromCollection();`
- L117 _private member_ `const int32 VertexIndex;`
- L118 _private member_ `FGeometryCollectionVerticesTreeItemGeometry* ParentCollectionItem;`
- L119 _private member_ `FSlateColor ItemColor;`

#### class `SVerticesOutlinerRow`  
`class SVerticesOutlinerRow : public SMultiColumnTableRow<FGeometryCollectionVerticesTreeItemVertexPtr>`  
_L122-141_
- inherits: `SMultiColumnTableRow<FGeometryCollectionVerticesTreeItemVertexPtr>`
- L125 _protected member_ `FGeometryCollectionVerticesTreeItemVertexPtr Item;`
- L128 _public function_ `SLATE_BEGIN_ARGS(SVerticesOutlinerRow)`
- L129 _public prototype_ `SLATE_END_ARGS() virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L133 _public function_ `void Construct(const FArguments& InArgs, TSharedRef<STableViewBase> OwnerTableView, FGeometryCollectionVerticesTreeItemVertexPtr InItemToEdit)`

#### class `SVerticesOutliner`  
`class SVerticesOutliner : public SCompoundWidget`  
_L143-175_
- inherits: `SCompoundWidget`
- L145 _private function_ `SLATE_BEGIN_ARGS(SVerticesOutliner)`
- L150 _public prototype_ `void Construct(const FArguments& InArgs);`
- L152 _public prototype_ `void RegenerateItems();`
- L153 _public prototype_ `void RegenerateHeader();`
- L155 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(FGeometryCollectionVerticesTreeItemPtr InInfo, const TSharedRef<STableViewBase>& OwnerTable);`
- L156 _public prototype_ `TSharedRef<ITableRow> OnGeneratePinnedRowWidget(FGeometryCollectionVerticesTreeItemPtr InItem, const TSharedRef<STableViewBase>& InOwnerTable, bool bPinned);`
- L157 _public prototype_ `void OnGetChildren(TSharedPtr<FGeometryCollectionVerticesTreeItem> InInfo, TArray< TSharedPtr<FGeometryCollectionVerticesTreeItem> >& OutChildren);`
- L158 _public prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();`
- L160 _public prototype_ `void UpdateGeometryCollection();`
- L161 _public prototype_ `void SetCollection(const TSharedPtr<const FManagedArrayCollection>& InCollection);`
- L162 _public prototype_ `int32 GetBoneSelectionCount() const;`
- L164 _public prototype_ `void ExpandAll();`
- L165 _public prototype_ `void ExpandRecursive(TSharedPtr<FGeometryCollectionVerticesTreeItem> TreeItem, bool bInExpansionState) const;`
- L168 _private prototype_ `void OnSelectionChanged(FGeometryCollectionVerticesTreeItemPtr Item, ESelectInfo::Type SelectInfo);`
- L170 _private member_ `TSharedPtr<STreeView<FGeometryCollectionVerticesTreeItemPtr>> TreeView;`
- L171 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L172 _private member_ `TArray<TSharedPtr<FGeometryCollectionVerticesTreeItemGeometry>> RootNodes;`
- L173 _private member_ `bool bPerformingSelection;`
- L174 _private member_ `TSharedPtr<const FManagedArrayCollection> Collection;`

#### Free symbols / members of external scopes

- L22 _typedef_ `typedef TArray<TSharedPtr<FGeometryCollectionVerticesTreeItem>> FGeometryCollectionVerticesTreeItemList;`
- L23 _typedef_ `typedef TSharedPtr<FGeometryCollectionVerticesTreeItem> FGeometryCollectionVerticesTreeItemPtr;`
- L24 _typedef_ `typedef TSharedPtr<class FGeometryCollectionVerticesTreeItemVertex> FGeometryCollectionVerticesTreeItemVertexPtr;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/PropertyGroupCustomization.h` (Public)


#### class `UE::Dataflow::FPropertyGroupCustomization`  
`class FPropertyGroupCustomization : public FPropertyListCustomization`  
_L16-45_
- inherits: `FPropertyListCustomization`
- desc: Property group customization to allow selecting of a group from a list of the groups currently held by the node's collection.
- L19 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();`
- L21 _public function_ `FPropertyGroupCustomization() : FPropertyListCustomization(FPropertyListCustomization::FOnGetListNames::CreateRaw(this, &FPropertyGroupCustomization::GetListNames))`
- L35 _private prototype_ `static bool MakeGroupName(FString& InOutString);` — Turn a string into a valid collection group or attribute name. The resulting name won't contains spaces and any other special characters as listed in INVALID_OBJECTNAME_CHARACTERS (currently "',/.:|&!~\n\r\t@#(){}[]=;^%$`). It will also have all leading underscore removed, as these names are reserved for internal use. @param InOutString The string to turn into a valid collection name. @return Whether the InOutString was already a valid collection name.
- L38 _private function_ `virtual TArray<FName> GetTargetGroupNames(const FManagedArrayCollection& Collection) const` — List of valid group names for the drop down list. Override this method to filter to a specific set of group names.
- L43 _private prototype_ `virtual bool MakeValidListName(FString& InOutString, FText& OutErrorMessage) const override;`
- L44 _private prototype_ `TArray<FName> GetListNames(const FManagedArrayCollection& Collection) const;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/Dataflow/PropertyListCustomization.h` (Public)


#### class `UE::Dataflow::FPropertyListCustomization`  
`class FPropertyListCustomization : public IPropertyTypeCustomization`  
_L23-84_
- inherits: `IPropertyTypeCustomization`
- desc: Property list customization to allow selecting of a name from a list derived from the node's collection.
- L28 _public prototype_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<FName>, FOnGetListNames, const FManagedArrayCollection&);` — Delegate to return the list of valid names for the drop down list.
- L30 _public prototype_ `FPropertyListCustomization() = default;`
- L32 _public function_ `explicit FPropertyListCustomization(FOnGetListNames&& InOnGetListNames) : IPropertyTypeCustomization() , OnGetListNames(MoveTemp(InOnGetListNames))`
- L40 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;`
- L41 _private function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> , IDetailChildrenBuilder& , IPropertyTypeCustomizationUtils& ) override`
- L51 _private prototype_ `static const FManagedArrayCollection& GetPropertyCollection( const TSharedPtr<UE::Dataflow::FContext>& Context, const TSharedPtr<IPropertyHandle>& ChildPropertyHandle, const FName CollectionPropertyName);` — Return the FManagedArrayCollection with the specified name from the property held by the top level struct owner of ChildPropertyHandle. @param Context The current editor Dataflow context. @param ChildPropertyHandle The handle of a customized property from which to find the owner struct. @param CollectionPropertyName @return The collection.
- L57 _private function_ `virtual bool MakeValidListName(FString& InOutString, FText& OutErrorMessage) const` — Override to make a list name valid and generate an error message if name is not valid.
- L64 _private function_ `virtual FName GetCollectionPropertyName() const` — Name of the collection property. Override this method to specify your own collection property name.
- L69 _private prototype_ `FText GetText() const;`
- L70 _private prototype_ `void OnTextCommitted(const FText& NewText, ETextCommit::Type CommitInfo);`
- L71 _private prototype_ `void OnSelectionChanged(TSharedPtr<FText> ItemSelected, ESelectInfo::Type SelectInfo);`
- L72 _private prototype_ `bool OnVerifyTextChanged(const FText& Text, FText& OutErrorMessage);`
- L73 _private prototype_ `TSharedRef<ITableRow> MakeCategoryViewWidget(TSharedPtr<FText> Item, const TSharedRef<STableViewBase>& OwnerTable);`
- L74 _private prototype_ `TSharedRef<SWidget> OnGetMenuContent();`
- L76 _private member_ `static inline const FName DefaultCollectionPropertyName = TEXT("Col`
- L78 _private member_ `TWeakPtr<const SDataflowGraphEditor> DataflowGraphEditor;`
- L79 _private member_ `TSharedPtr<IPropertyHandle> ChildPropertyHandle;`
- L80 _private member_ `TWeakPtr<SComboButton> ComboButton;`
- L81 _private member_ `TArray<TSharedPtr<FText>> ListNames;`
- L83 _private member_ `FOnGetListNames OnGetListNames;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Dataflow` (scope `UE`)
- L28 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TArray<FName>, FOnGetListNames, const FManagedArrayCollection&);` — Delegate to return the list of valid names for the drop down list.

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowEditorTools/DataflowEditorToolBuilder.h` (Public)


#### class `UDataflowEditorToolBuilder`  
`class UDataflowEditorToolBuilder : public UInterface`  
_L18-21_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IDataflowEditorToolBuilder`  
`class IDataflowEditorToolBuilder`  
_L24-44_
- L31 _public prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const = 0;` — Returns all Construction View modes that this tool can operate in. The first element should be the preferred mode to switch to if necessary.
- L34 _public function_ `virtual bool CanSetConstructionViewWireframeActive() const` — Returns whether or not view can be set to wireframe when this tool is active..
- L37 _public function_ `virtual bool CanSceneStateChange(const UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState) const` — Returns true if the tool can keep running when the SceneState changes
- L40 _public function_ `virtual void SceneStateChanged(UInteractiveTool* ActiveTool, const FToolBuilderState& SceneState)` — Respond to SceneState changing

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowEditorTools/DataflowEditorVertexAttributePaintTool.h` (Public)


#### class `UDataflowEditorVertexAttributePaintToolBuilder`  
`class UDataflowEditorVertexAttributePaintToolBuilder : public UMeshSurfacePointMeshEditingToolBuilder, public IDataflowEditorToolBuilder`  
_L46-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshSurfacePointMeshEditingToolBuilder,IDataflowEditorToolBuilder`
- desc: Tool Builder
- L50 _public function_ `void SetFallbackToolBuilder(UMeshSurfacePointMeshEditingToolBuilder* InFallbackToolBuilder)`
- L51 _public prototype_ `void SetEditorMode(UDataflowEditorMode* InMode);`
- L54 _private prototype_ `virtual void GetSupportedConstructionViewModes(const UDataflowContextObject& ContextObject, TArray<const UE::Dataflow::IDataflowConstructionViewMode*>& Modes) const override;`
- L55 _private prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L56 _private prototype_ `virtual UMeshSurfacePointTool* CreateNewTool(const FToolBuilderState& SceneState) const override;`
- L57 _private function_ `virtual bool CanSetConstructionViewWireframeActive() const`
- L61 _private member_ `TMap<TWeakObjectPtr<const UInteractiveToolManager>, TWeakObjectPtr<UDataflowEditorMode>> ModeForToolManager;` — Per-editor mode lookup keyed by the editor's tool manager. This builder is held by the process-wide FDataflowToolRegistry singleton, so a single Mode pointer would alias across simultaneously-open Dataflow editors; the map keeps each editor's mode separate.
- L64 _private member_ `TObjectPtr<UMeshSurfacePointMeshEditingToolBuilder> FallbackToolBuilder = nullptr;` — `UPROPERTY()`

#### struct `FDataflowEditorVertexAttributePaintToolDataAdapter`  
`struct FDataflowEditorVertexAttributePaintToolDataAdapter`  
_L69-95_
- L72 _public prototype_ `void Setup( const FDynamicMesh3& InMesh, UE::Geometry::FDynamicMeshWeightAttribute* InActiveWeightMap, FDataflowVertexAttributeEditableNode* InNodeToUpdate, TObjectPtr<UDataflowContextObject> InDataflowEditorContextObject );`
- L79 _public prototype_ `void CommitToNode(TObjectPtr<UDataflowContextObject> InDataflowEditorContextObject, IToolsContextTransactionsAPI* TransactionAPI);`
- L81 _public function_ `bool HaveDynamicMeshToWeightConversion() const`
- L82 _public function_ `const TArray<int32>& GetDynamicMeshToWeight() const`
- L83 _public function_ `const TArray<TArray<int32>>& GetWeightToDynamicMesh() const`
- L87 _private member_ `bool bHaveDynamicMeshToWeightConversion = false;` — DynamicMesh might be unwelded mesh, but weights are on the welded mesh.
- L88 _private member_ `TArray<int32> DynamicMeshToWeight;`
- L89 _private member_ `TArray<TArray<int32>> WeightToDynamicMesh;`
- L92 _private member_ `FDataflowVertexAttributeEditableNode* NodeToUpdate = nullptr;` — Corresponding node to read from and write back to
- L94 _private member_ `UE::Geometry::FDynamicMeshWeightAttribute* ActiveWeightMap = nullptr;`

#### class `UDataflowEditorVertexAttributePaintTool`  
`class UDataflowEditorVertexAttributePaintTool : public UMeshVertexAttributePaintToolBase`  
_L103-140_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshVertexAttributePaintToolBase`
- desc: Dataflow Editor tool to paint a vertex attribute as vertex colors
- L108 _public prototype_ `virtual bool SetupToolMesh(FDynamicMesh3& InOutToolMesh, int32& OutInitialAttributeIndex) override;`
- L109 _public prototype_ `virtual void CommitToolMesh(FDynamicMesh3& InToolMesh) override;`
- L113 _public prototype_ `virtual void Setup() override;`
- L115 _public prototype_ `void SetDataflowEditorContextObject(TObjectPtr<UDataflowContextObject> InDataflowEditorContextObject);`
- L116 _public function_ `void SetEditorMode(UDataflowEditorMode* InMode)`
- L119 _public prototype_ `static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);`
- L122 _public prototype_ `virtual void SetFocusInViewport() const override;`
- L131 _protected member_ `TObjectPtr<UDataflowContextObject> DataflowEditorContextObject = nullptr;` — `UPROPERTY()`
- L133 _protected member_ `FDataflowEditorVertexAttributePaintToolDataAdapter DataAdapter;`
- L138 _protected member_ `UDataflowEditorMode* Mode = nullptr;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L35 _namespace_ `namespace UE`
- L35 _namespace_ `namespace DataflowEditorVertexAttributePaintTool` (scope `UE`)
- L35 _namespace_ `namespace CVars` (scope `UE::DataflowEditorVertexAttributePaintTool`)
- L37 _externvar_ `extern bool DataflowEditorUseNewWeightMapTool;` (scope `UE::DataflowEditorVertexAttributePaintTool::CVars`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowRendering/DataflowDebugMeshComponent.h` (Public)


#### class `UDataflowDebugMeshComponent`  
`class UDataflowDebugMeshComponent : public UDebugDrawComponent`  
_L13-27_
- reflection: `UCLASS(MinimalAPI, Hidden)`
- inherits: `UDebugDrawComponent`
- L18 _public typedef_ `using FText3d = FDebugRenderSceneProxy::FText3d;`
- L19 _public typedef_ `using FLine = FDebugRenderSceneProxy::FDebugLine;`
- L21 _public member_ `TArray<FText3d> IDs;`
- L22 _public member_ `TArray<FLine> Normals;`
- L25 _private prototype_ `virtual FDebugRenderSceneProxy* CreateDebugSceneProxy() override;`
- L26 _private prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override;`

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowRendering/DataflowRenderableComponents.h` (Public)


#### struct `UE::Dataflow::FRenderableComponents`  
`struct FRenderableComponents`  
_L17-60_
- desc: List of renderable components for a sepcific root actor this class is used by IRenderableType to collect the components to render
- L20 _public function_ `FRenderableComponents(AActor* InRootActor) : RootActor(InRootActor)`
- L30 _public function_ `template<typename T UE_REQUIRES(TIsDerivedFrom<T, UPrimitiveComponent>::Value)> T* AddNewComponent(FName ComponentName = NAME_None, UObject* ComponentParent = nullptr)` — Create a new component of a specific type ( needs to inherit from UPrimitiveComponent ) and add it to the list returns  the newly added component so that it can be configured by the caller
- L50 _public function_ `template<typename T UE_REQUIRES(TIsDerivedFrom<T, UObject>::Value)> T* MakeNewObject(FName ObjectName = NAME_None)`
- L55 _public function_ `const TArray<UPrimitiveComponent*>& GetComponents() const`
- L58 _private member_ `AActor* RootActor = nullptr;`
- L59 _private member_ `TArray<UPrimitiveComponent*> Components;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowRendering/DataflowRenderableType.h` (Public)


#### struct `UE::Dataflow::IRenderableType`  
`struct IRenderableType`  
_L17-37_
- desc: this interface defines a way to render a specific data type in Dataflow rendering is achieve by provided a number of components that will be added to the rednering scene
- L21 _public prototype_ `virtual FName GetOutputType() const = 0;` — Returns the renderable primary type (ie: TObjectPtr<UDynamicMesh>)
- L24 _public function_ `virtual FName GetRenderGroup() const` — Returns the supported render group, useful when rendering a specific type in a particular way (ie : "Surface" may render the geometry related groups )
- L27 _public function_ `virtual void GetSettingsClasses(TArray<const UClass*>& OutArray) const` — returns the class of the settings object if any
- L30 _public prototype_ `virtual bool IsViewModeSupported(const IDataflowConstructionViewMode& ViewMode) const = 0;` — return true if the ViewMode is supported for rendering this
- L33 _public function_ `virtual bool CanRender(const FRenderableTypeInstance& Instance) const` — Whether this type can be rendered in this context
- L36 _public prototype_ `virtual void GetPrimitiveComponents(const FRenderableTypeInstance& Instance, FRenderableComponents& OutComponents) const = 0;` — Get the primitive components for the specific render context

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Dataflow` (scope `UE`)
- L42 _macro_ `#define UE_DATAFLOW_IRENDERABLE_PRIMARY_TYPE(Type, Name) \`
- L49 _macro_ `#define UE_DATAFLOW_IRENDERABLE_RENDER_GROUP(Name) \`
- L54 _macro_ `#define UE_DATAFLOW_IRENDERABLE_VIEW_MODE(ViewModeClass) \`
- L58 _macro_ `#define UE_DATAFLOW_IRENDERABLE_SETTINGS(RenderSettingsClass) \`

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowRendering/DataflowRenderableTypeInstance.h` (Public)


#### struct `UE::Dataflow::FRenderableTypeInstance`  
`struct FRenderableTypeInstance final`  
_L28-175_
- desc: This describe a renderable type instance which match to a specific node + output(s) And to be rendered in the context a specific Actor and Dataflow context
- L32 _public prototype_ `static void GetRenderableInstancesForNode(FContext& Context, const IDataflowConstructionViewMode& ViewMode, const FDataflowNode& Node, bool bEvaluateOutputs, TArray<FRenderableTypeInstance>& OutRenderableInstances);` — find all renderable instances for a specific node and a specific view mode
- L35 _public prototype_ `bool CanRender() const;` — Whether this instance can render
- L38 _public prototype_ `FString GetDisplayName() const;` — Returns the display name of this instance
- L41 _public prototype_ `FName GetComponentName(const FName& InComponentName) const;` — Returns the display name of this instance
- L44 _public prototype_ `void GetPrimitiveComponents(FRenderableComponents& OutComponents) const;` — Get the corresponding
- L51 _public function_ `template <typename T> const T& GetOutputValue(const T& Default = T()) const` — Get value for the primary output to render Returns the default value if not found of this fails internally
- L56 _public function_ `bool HasUptoDateCachedValue(FName CacheName = NAME_None) const`
- L68 _public function_ `template<typename T> const T& GetCachedValue(FName CacheName = NAME_None) const`
- L77 _public function_ `template<typename T> void CacheValue(T&& InValue, FName CacheName = NAME_None) const`
- L87 _public prototype_ `const FDataflowNode::FAttributeKey GetVertexAttributeToVisualize() const;`
- L89 _public prototype_ `const void GetSelectionToVisualize(FDataflowSelection& OutSelection) const;`
- L91 _public prototype_ `TArray<UDataflowRenderableTypeSettings*> GetAllRenderSettings() const;`
- L92 _public prototype_ `UDataflowRenderableTypeSettings* GetRenderSettings(const UClass* SettingsClass) const;`
- L95 _public function_ `template <typename T UE_REQUIRES(std::is_base_of_v<UDataflowRenderableTypeSettings, T>)> const T* GetTypedRenderSettings() const`
- L101 _public function_ `template <typename T> const T& GetOutputValue(FName Name, const T& Default = T()) const`
- L118 _public function_ `template <typename T UE_REQUIRES(!std::is_base_of_v<FDataflowAnyType, T>)> const T& GetOutputValueByType(const T& Default, FName Metadata = NAME_None) const` — Find the first output of a specific match type and optionally containing a specific metadata string and return its value - non-anytype version
- L138 _public function_ `template <typename T UE_REQUIRES(std::is_base_of_v<FDataflowAnyType, T>)> const typename T::FStorageType& GetOutputValueByType(const typename T::FStorageType& Default, FName Metadata = NAME_None) const` — Find the first output of a specific match type and return its value - anytype version
- L157 _private prototype_ `FContextCacheKey ComputeCacheKey() const;`
- L159 _private prototype_ `static bool HasMetadata(const FDataflowOutput& Output, FName Metadata);`
- L161 _private function_ `FRenderableTypeInstance(FContext& InContext, const TSharedPtr<const FDataflowNode>& InNode, const FName InOutputName, const IRenderableType* InRenderableType, bool bEvaluateOutputsIn) : EvaluationContext(InContext) , Node(InNode) , OutputName(InOutputName) , RenderableType(InRenderableType) , bEvaluateOutputs(bEvaluateOutputsIn)`
- L170 _private member_ `FContext& EvaluationContext;`
- L171 _private member_ `TSharedPtr<const FDataflowNode> Node;`
- L172 _private member_ `const FName OutputName;`
- L173 _private member_ `const IRenderableType* RenderableType;`
- L174 _private member_ `bool bEvaluateOutputs;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Dataflow` (scope `UE`)

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowRendering/DataflowRenderableTypeRegistry.h` (Public)


#### struct `UE::Dataflow::FRenderableTypeRegistry`  
`struct FRenderableTypeRegistry`  
_L16-36_
- desc: this registry contains all Dataflow renderable types instances
- L19 _public typedef_ `using FRenderableTypes = TArray<const IRenderableType*>;`
- L22 _public prototype_ `void Register(const IRenderableType* RenderableType);` — register a renderable type instance - use UE_DATAFLOW_REGISTER_RENDERABLE_TYPE instead of calling this directly for ease of use
- L25 _public prototype_ `const FRenderableTypes& GetRenderableTypes(FName PrimaryType) const;` — Get all the available renderable types for a specific primary type
- L28 _public prototype_ `static FRenderableTypeRegistry& GetInstance();` — get the one and only instance of this registry
- L31 _private prototype_ `FRenderableTypeRegistry() = default;`
- L34 _private member_ `TMap<FName, FRenderableTypes> RenderableTypesByPrimaryType;`
- L35 _private member_ `TSet<FName> RegisteredAnyTypes;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Dataflow` (scope `UE`)
- L43 _macro_ `#define UE_DATAFLOW_REGISTER_RENDERABLE_TYPE(Type) \`

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowRendering/DataflowRenderableTypeSettings.h` (Public)


#### class `UDataflowRenderableTypeSettings`  
`class UDataflowRenderableTypeSettings : public UObject`  
_L10-15_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L14 _public prototype_ `static void RegisterSection(UClass* Class, FName Name, const FText& DisplayName, TConstArrayView<FName> Categories);`

#### class `UDataflowUVsRenderSettings`  
`class UDataflowUVsRenderSettings : public UDataflowRenderableTypeSettings`  
_L20-38_
- reflection: `UCLASS(MinimalAPI, AutoExpandCategories = "UVs")`
- inherits: `UDataflowRenderableTypeSettings`
- L26 _public function_ `int32 GetUVChannel(int32 DefaultChannel) const` — return the overriden channel if enabled or the default passed to this method
- L33 _private member_ `bool bOverrideUVchannel = false;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (InlineEditConditionToggle))`
- L37 _private member_ `int32 UVChannel = 0;` — `UPROPERTY(EditAnywhere, Category = "UVs", meta = (UIMIn = 0, UIMax = 7, ClampMin = 0, ClampMax = 7, EditCondition = bOverrideUVchannel))` — UV channel to display if oiverride is enabled

### `Plugins/Dataflow/Source/DataflowEditor/Public/DataflowRendering/DataflowRenderableTypeUtils.h` (Public)


#### enum `EDataflowColorMethodType`  
`enum class EDataflowColorMethodType : uint8`  
_L26-32_
- reflection: `UENUM(BlueprintType)`
- L28 _public enumerator_ `Constant UMETA(DisplayName = "Constant")`
- L29 _public enumerator_ `Random UMETA(DisplayName = "Random")`
- L30 _public enumerator_ `BySize UMETA(DisplayName = "By Size")`
- L31 _public enumerator_ `BoundingBox UMETA(DisplayName = "BoundinBox")`

#### struct `FDataflowSimpleColorCommonRenderSettings`  
`struct FDataflowSimpleColorCommonRenderSettings`  
_L35-51_
- reflection: `USTRUCT()`
- L42 _public member_ `bool bWireframe = false;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Display surface as wireframe
- L46 _public member_ `float Transparency = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — Transparency
- L50 _public member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = "ConstantColor")` — Constant color

#### struct `FDataflowColorCommonRenderSettings`  
`struct FDataflowColorCommonRenderSettings`  
_L54-98_
- reflection: `USTRUCT()`
- L59 _public prototype_ `FDataflowColorCommonRenderSettings();`
- L63 _public member_ `bool bWireframe = false;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Display surface as wireframe
- L67 _public member_ `float Transparency = 0.f;` — `UPROPERTY(EditAnywhere, Category = "Color", meta = (UIMin = 0, ClampMin = 0, UIMax = 1, ClampMax = 1))` — Transparency
- L71 _public member_ `EDataflowColorMethodType ColorMethod = EDataflowColorMethodType::Constant;` — `UPROPERTY(EditAnywhere, Category = "Color")` — Method for coloring the boxes
- L75 _public member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = "ConstantColor", meta = (EditCondition = "ColorMethod == EDataflowColorMethodType::Constant"))` — Constant color
- L79 _public member_ `int32 RandomSeed = 0;` — `UPROPERTY(EditAnywhere, Category = "RandomColor", meta = (UIMin = 0, EditCondition = "ColorMethod == EDataflowColorMethodType::Random"))` — Seed for the random color
- L83 _public member_ `float SizeMin = 1.f;` — `UPROPERTY(EditAnywhere, Category = "ColorBySize", meta = (UIMin = 0, ClampMin = 0, EditCondition = "ColorMethod == EDataflowColorMethodType::BySize"))` — Minimum size
- L87 _public member_ `float SizeMax = 100.f;` — `UPROPERTY(EditAnywhere, Category = "ColorBySize", meta = (UIMin = 0, ClampMin = 0, EditCondition = "ColorMethod == EDataflowColorMethodType::BySize"))` — Maximum size
- L91 _public member_ `FLinearColorRamp ColorRamp;` — `UPROPERTY(EditAnywhere, Category = "ColorBySize", meta = (EditCondition = "ColorMethod == EDataflowColorMethodType::BySize"))` — Color ramp for colorin by scale
- L97 _public member_ `int32 PermutationIndex = 0;` — `UPROPERTY(EditAnywhere, Category = "ColorByBoundingBox", meta = (UIMin = 0, UIMax = 23, EditCondition = "ColorMethod == EDataflowColorMethodType::BoundingBox"))` — The normalized position of the center of the object in the component bounding box is computed. Then the X or 1-X, Y or 1-Y, Z or 1-Z of the normalized position is set to the (R,G,B) values. There are 32 different permutation. The index specifies which one gets used.

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API DATAFLOWEDITOR_API`
- L100 _namespace_ `namespace UE`
- L100 _namespace_ `namespace Dataflow` (scope `UE`)
- L105 _namespace_ `namespace Rendering` (scope `UE::Dataflow`)
- L108 _prototype_ `UMaterial* GetVertexMaterial();` (scope `UE::Dataflow::Rendering`) — Get the default vertex material for dynamic meshes
- L111 _prototype_ `TSharedPtr<UE::Geometry::FDynamicMesh3> GenerateUvMesh(const FMeshDescription& MeshDescription, int32 UvChannel);` (scope `UE::Dataflow::Rendering`) — Generate a dynamic mesh from a mesh description UV data
- L114 _prototype_ `TSharedPtr<UE::Geometry::FDynamicMesh3> GenerateUvMesh(const UStaticMesh& StaticMesh, int32 UvChannel);` (scope `UE::Dataflow::Rendering`) — Generate a dynamic mesh from a static mesh UV data
- L117 _prototype_ `TSharedPtr<UE::Geometry::FDynamicMesh3> GenerateUvMesh(const USkeletalMesh& SkeletalMesh, int32 UvChannel);` (scope `UE::Dataflow::Rendering`) — Generate a dynamic mesh from a skeletal mesh UV data
- L120 _prototype_ `TSharedPtr<UE::Geometry::FDynamicMesh3> GenerateUvMesh(const UE::Geometry::FDynamicMesh3& DynamicMesh, int32 UvChannel);` (scope `UE::Dataflow::Rendering`) — Generate a dynamic mesh from a dynamic mesh UV data
- L123 _prototype_ `TSharedPtr<UE::Geometry::FDynamicMesh3> GenerateUvMesh(const FManagedArrayCollection& Collection, int32 UvChannel);` (scope `UE::Dataflow::Rendering`) — Generate a dynamic mesh from a managed array collection UV data
- L126 _prototype_ `UDynamicMeshComponent* AddDynamicMeshComponent(UE::Geometry::FDynamicMesh3&& DynamicMesh, FRenderableComponents& OutComponents);` (scope `UE::Dataflow::Rendering`) — Make a dynamic mesh component and add it to the OutComponents
- L129 _prototype_ `void SetUvMaterial(UDynamicMeshComponent& Component, int32 MaterialIndex);` (scope `UE::Dataflow::Rendering`) — set UV material on a primitive component
- L133 _function_ `template<typename T> void AddUvDynamicMeshComponent(const T& Source, int32 UvIndex, FRenderableComponents& OutComponents)` (scope `UE::Dataflow::Rendering`) — Generate a Uv mesh from a templated source and make a dynamic mesh component out of it and add it to the OutComponents
- L144 _prototype_ `int32 GetUVChannelFromInstance(const FRenderableTypeInstance& Instance, int32 DefaultValue = 0);` (scope `UE::Dataflow::Rendering`)
- L146 _prototype_ `FLinearColor GetColor(const int32 InIdx, const FBox& InComponentBoundingBox, const FVector& InCenter, float InSize, const FDataflowColorCommonRenderSettings& InSettings);` (scope `UE::Dataflow::Rendering`)
- L150 _namespace_ `namespace RenderGeometry` (scope `UE::Dataflow`)
- L153 _prototype_ `UE::Geometry::FDynamicMesh3 BuildCapsuleMesh(float Radius, float Length);` (scope `UE::Dataflow::RenderGeometry`) — Build a uniform capsule mesh centered at origin, aligned along +Z. Total height = Length + 2 * Radius.
- L156 _prototype_ `UE::Geometry::FDynamicMesh3 BuildTaperedCapsuleMesh(float Radius0, float Radius1, float Length, int32 ArcSteps = 6, int32 CircleSteps = 12);` (scope `UE::Dataflow::RenderGeometry`) — Build a tapered capsule mesh centered at origin, aligned along +Z.
- L159 _prototype_ `UE::Geometry::FDynamicMesh3 BuildConvexMesh(const FKConvexElem& Elem);` (scope `UE::Dataflow::RenderGeometry`) — Build a triangle mesh from a convex element's pre-computed vertex/index data. Returns an empty mesh if data is missing.
- L167 _prototype_ `void AddAggGeomComponents( const FKAggregateGeom& AggGeom, const FTransform& BoneTransform, FName BoneName, FRenderableComponents& OutComponents, UObject* ComponentParent, UMaterialInstanceDynamic* MaterialInstance, int32& InOutShapeCounter);` (scope `UE::Dataflow::RenderGeometry`) — Add UPrimitiveComponent instances for all shape elements in AggGeom to OutComponents. BoneTransform: component-space transform of the owning bone (pass Identity for standalone geometry). BoneName: used only for component naming (pass NAME_None for standalone geometry). InOutShapeCounter: incremented once per shape added; share a single counter across calls for unique names.
