# Plugins / InterchangeEditorPipelines

- module root: `Plugins/Interchange/Editor/Source/Pipelines`
- headers: 18; symbols: 339
- symbol kinds: class=30, delegate=5, enum=1, enumerator=3, function=47, macro=3, member=97, namespace=2, prototype=142, struct=5, typedef=4
- PrivateDependencyModuleNames: AssetDefinition, AssetTools, EngineAssetDefinitions, InputCore, InterchangeNodes, InterchangePipelines, MainFrame, Projects, PropertyEditor, Slate, SlateCore, ToolWidgets, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, InterchangeCore, InterchangeEngine

### `Plugins/Interchange/Editor/Source/Pipelines/Private/AssetDefinition/AssetDefinition_InterchangeBlueprintPipeline.h` (Private)


#### class `UAssetDefinition_InterchangeBlueprintPipeline`  
`class UAssetDefinition_InterchangeBlueprintPipeline : public UAssetDefinition_Blueprint`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L23 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/AssetDefinition/AssetDefinition_InterchangeEditorBlueprintPipeline.h` (Private)


#### class `UAssetDefinition_InterchangeEditorBlueprintPipeline`  
`class UAssetDefinition_InterchangeEditorBlueprintPipeline : public UAssetDefinition_Blueprint`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinition_Blueprint`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L23 _public prototype_ `virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/AssetDefinition/AssetDefinition_InterchangePipeline.h` (Private)


#### class `UAssetDefinition_InterchangePipeline`  
`class UAssetDefinition_InterchangePipeline : public UAssetDefinitionDefault`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/AssetDefinition/AssetDefinition_InterchangePythonPipeline.h` (Private)


#### class `UAssetDefinition_InterchangePythonPipeline`  
`class UAssetDefinition_InterchangePythonPipeline : public UAssetDefinitionDefault`  
_L9-25_
- reflection: `UCLASS()`
- inherits: `UAssetDefinitionDefault`
- L14 _public function_ `virtual FText GetAssetDisplayName() const override` — UAssetDefinition Begin
- L15 _public function_ `virtual FLinearColor GetAssetColor() const override`
- L16 _public function_ `virtual TSoftClassPtr<UObject> GetAssetClass() const override`
- L17 _public function_ `virtual TConstArrayView<FAssetCategoryPath> GetAssetCategories() const override`
- L23 _public prototype_ `virtual EAssetCommandResult OpenAssets(const FAssetOpenArgs& OpenArgs) const override;`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/InterchangeEditorPipelineDetails.h` (Private)


#### class `FInterchangePipelineBaseDetailsCustomization`  
`class FInterchangePipelineBaseDetailsCustomization : public IDetailCustomization`  
_L34-84_
- inherits: `IDetailCustomization`
- L39 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L42 _public prototype_ `static void SetConflictsInfo(TArray<FInterchangeConflictInfo>& ConflictInfos);` — Temporary: Used to pass data to the next instance created.
- L45 _public prototype_ `static void SetExtraInformation(const TMap<FString, FString>& InExtraInformation);` — Temporary: Used to pass ExtraInformation to the next instance created.
- L48 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L52 _public prototype_ `static void ReCollectConflictAndExtraInfo();`
- L53 _public member_ `static FOnGatherConflictAndExtraInfo OnGatherConflictAndExtraInfo;`
- L61 _private prototype_ `void RefreshCustomDetail();`
- L62 _private prototype_ `void LockPropertyHandleRow(const TSharedPtr<IPropertyHandle> PropertyHandle, IDetailPropertyRow& PropertyRow) const;`
- L63 _private prototype_ `void AddSubCategory(IDetailLayoutBuilder& DetailBuilder, TMap<FName, TMap<FName, TArray<FInternalPropertyData>>>& SubCategoriesPropertiesPerMainCategory);`
- L64 _private prototype_ `void InternalGetPipelineProperties(const UInterchangePipelineBase* Pipeline, const TArray<FName>& AllCategoryNames, TMap<FName, TArray<FName>>& PropertiesPerCategorys) const;`
- L65 _private prototype_ `void AddConflictSection();`
- L66 _private prototype_ `void AddExtraInformationSection();`
- L67 _private prototype_ `FReply ShowConflictDialog(FInterchangeConflictInfo ConflictInfo);`
- L69 _private prototype_ `void SetTextComboBoxWidget(IDetailPropertyRow& PropertyRow, const TSharedPtr<IPropertyHandle>& Handle, const TArray<FString>& PossibleValues);`
- L70 _private prototype_ `void OnTextComboBoxChanged(TSharedPtr<FString> NewValue, ESelectInfo::Type SelectInfo, TWeakPtr<IPropertyHandle> HandlePtr);`
- L77 _private member_ `TMap<TSharedPtr<IPropertyHandle>, FInternalComboBoxData> ComboBoxDataPerProperty;`
- L80 _private prototype_ `FInterchangePipelineBaseDetailsCustomization();` — Use MakeInstance to create an instance of this class
- L82 _private member_ `TWeakObjectPtr<UInterchangePipelineBase> InterchangePipeline;`
- L83 _private member_ `IDetailLayoutBuilder* CachedDetailBuilder;` — The detail builder for this customisation

#### struct `FInterchangePipelineBaseDetailsCustomization::FInternalPropertyData`  
`struct FInternalPropertyData`  
_L56-60_
- L58 _public member_ `TSharedPtr<IPropertyHandle> PropertyHandle;`
- L59 _public member_ `bool bReadOnly = false;`

#### struct `FInterchangePipelineBaseDetailsCustomization::FInternalComboBoxData`  
`struct FInternalComboBoxData`  
_L71-76_
- L73 _public member_ `TArray<TSharedPtr<FString>> StringSharedOptions;`
- L74 _public member_ `TArray<FString> StringOptions;`
- L75 _public member_ `TArray<FName> NameOptions;`

#### class `FInterchangeBaseNodeDetailsCustomization`  
`class FInterchangeBaseNodeDetailsCustomization : public IDetailCustomization`  
_L86-185_
- inherits: `IDetailCustomization`
- L89 _public prototype_ `~FInterchangeBaseNodeDetailsCustomization();`
- L92 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L95 _public prototype_ `virtual void CustomizeDetails( IDetailLayoutBuilder& DetailBuilder ) override;` — IDetailCustomization interface
- L99 _private prototype_ `void RefreshCustomDetail();`
- L100 _private prototype_ `void AddAttributeRow(UE::Interchange::FAttributeKey& AttributeKey, IDetailCategoryBuilder& AttributeCategory);`
- L107 _private prototype_ `void BuildBoolValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — Bool: Add a row to the category containing a check box (read/write)
- L111 _private prototype_ `template<typename NumericType> void BuildNumberValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — Number (float, double, signed/unsigned integer): Add one row to the category containing a numeric field (read/write)
- L115 _private prototype_ `template<typename StringType> void BuildStringValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — String (FString, FName): Add a row to the category containing text block (read only)
- L120 _private prototype_ `template<typename TransformnType, typename VectorType, typename QuatType, typename NumericType> void BuildTransformValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — FTransform: Add a group to the category that contain the Translation(FVector), Rotation(FQuat) and scale3D(FVector) Any numeric field are read/write
- L122 _private prototype_ `void BuildStringInterchangeMeshLODDataValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);`
- L123 _private prototype_ `void BuildStringInterchangeMeshLODDataArrayValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);`
- L127 _private prototype_ `void BuildColorValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — FColor: Add a row to the category that contain the RGBA value Any numeric field are read/write
- L131 _private prototype_ `void BuildLinearColorValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — FLinearColor: Add a row to the category that contain the RGBA value Any numeric field are read/write
- L134 _private prototype_ `template<typename AttributeType, typename NumericType> void InternalBuildColorValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey, NumericType DefaultTypeValue);`
- L139 _private prototype_ `template<typename BoxType, typename VectorType, typename NumericType> void BuildBoxValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — FBox: Add a group to the category that contain the Minimum corner position(FVector), and the maximum corner position(FVector) Any numeric field are read/write
- L144 _private prototype_ `template<typename VectorType, typename NumericType> void BuildVectorValueContent(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey);` — FVector: Add a row to the category that display a FVector. Any numeric field are read/write
- L153 _private prototype_ `void CreateInvalidHandleRow(IDetailCategoryBuilder& AttributeCategory, UE::Interchange::FAttributeKey& AttributeKey) const;` — Add a row to the specified category which let the user that a attribute handle is invalid
- L160 _private prototype_ `TSharedRef<SWidget> CreateNameWidget(UE::Interchange::FAttributeKey& AttributeKey) const;`
- L162 _private prototype_ `TSharedRef<SWidget> CreateSimpleNameWidget(const FString& SimpleName) const;`
- L166 _private prototype_ `template<typename VectorType, typename NumericWidgetType, typename FunctorGet, typename FunctorSet> TSharedRef<SWidget> CreateVectorWidget(FunctorGet GetValue, FunctorSet SetValue, UE::Interchange::FAttributeKey& AttributeKey);` — FVector Create a 3 digit widget (X, Y, Z)
- L170 _private prototype_ `template<typename QuatType, typename NumericWidgetType, typename FunctorGet, typename FunctorSet> TSharedRef<SWidget> CreateQuaternionWidget(FunctorGet GetValue, FunctorSet SetValue, UE::Interchange::FAttributeKey& AttributeKey);` — FQuat Create a 4 digit widget (X, Y, Z, W)
- L174 _private prototype_ `template<typename NumericType, typename FunctorGet, typename FunctorSet> TSharedRef<SWidget> MakeNumericWidget(int32 ComponentIndex, FunctorGet GetValue, FunctorSet SetValue, UE::Interchange::FAttributeKey& AttributeKey);` — Create one numeric widget, support (float, double, signed/unsigned integer)
- L181 _private prototype_ `FInterchangeBaseNodeDetailsCustomization();` — Use MakeInstance to create an instance of this class
- L183 _private member_ `UInterchangeBaseNode* InterchangeBaseNode;`
- L184 _private member_ `IDetailLayoutBuilder* CachedDetailBuilder;` — The detail builder for this customisation

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L24 _namespace_ `namespace Interchange` (scope `UE`)
- L30 _typedef_ `using FInterchangeConflictInfoArray = TArray<FInterchangeConflictInfo>;`
- L31 _typedef_ `using FInterchangeExtraInfoMap = TMap<FString, FString>;`
- L32 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGatherConflictAndExtraInfo, FInterchangeConflictInfoArray&, FInterchangeExtraInfoMap&);`
- L32 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnGatherConflictAndExtraInfo, FInterchangeConflictInfoArray&, FInterchangeExtraInfoMap&);`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/InterchangeEditorPipelineStyle.h` (Private)


#### class `FInterchangeEditorPipelineStyle`  
`class FInterchangeEditorPipelineStyle final : public FSlateStyleSet`  
_L15-81_
- inherits: `FSlateStyleSet`
- desc: Implements the visual style of the text asset editor UI.
- L20 _public function_ `FInterchangeEditorPipelineStyle() : FSlateStyleSet("InterchangeEditorPipelineStyle")` — Default constructor.
- L77 _public function_ `~FInterchangeEditorPipelineStyle()` — Destructor.

### `Plugins/Interchange/Editor/Source/Pipelines/Private/InterchangeGLTFPipelineCustomizations.h` (Private)


#### class `FInterchangeGLTFPipelineSettingsCustomization`  
`class FInterchangeGLTFPipelineSettingsCustomization : public IDetailCustomization`  
_L12-27_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this class
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L26 _private member_ `TWeakObjectPtr<UGLTFPipelineSettings> GLTFPipelineSettings;`

#### class `FInterchangeGLTFPipelineCustomization`  
`class FInterchangeGLTFPipelineCustomization : public IDetailCustomization`  
_L29-41_
- inherits: `IDetailCustomization`
- L36 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this class
- L39 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Interchange/Editor/Source/Pipelines/Private/InterchangeMaterialXPipelineCustomizations.h` (Private)


#### class `FInterchangeMaterialXPipelineSettingsCustomization`  
`class FInterchangeMaterialXPipelineSettingsCustomization : public IDetailCustomization`  
_L12-30_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this class
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L26 _protected prototype_ `static bool OnShouldFilterAssetEnum(const FAssetData&, uint8 EnumType, uint8 EnumValue);`
- L29 _private member_ `TWeakObjectPtr<UMaterialXPipelineSettings> MaterialXSettings;`

#### class `FInterchangeMaterialXPipelineCustomization`  
`class FInterchangeMaterialXPipelineCustomization : public IDetailCustomization`  
_L32-44_
- inherits: `IDetailCustomization`
- L39 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Creates an instance of this class
- L42 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Interchange/Editor/Source/Pipelines/Private/InterchangePipelineFactories.h` (Private)


#### class `FInterchangePipelineBaseFilterViewer`  
`class FInterchangePipelineBaseFilterViewer : public IClassViewerFilter`  
_L11-38_
- inherits: `IClassViewerFilter`
- L14 _public member_ `TSet<const UClass*> AllowedChildrenOfClasses;`
- L15 _public member_ `TSet<const UClass*> DisallowedChildrenOfClasses;`
- L16 _public member_ `EClassFlags DisallowedClassFlags = EClassFlags::CLASS_None;`
- L17 _public function_ `virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<class FClassViewerFilterFuncs> InFilterFuncs) override`
- L28 _public function_ `virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override`

#### class `UInterchangeBlueprintPipelineBaseFactory`  
`class UInterchangeBlueprintPipelineBaseFactory : public UFactory`  
_L41-60_
- reflection: `UCLASS(hidecategories = Object, collapsecategories)`
- inherits: `UFactory`
- L46 _public prototype_ `UInterchangeBlueprintPipelineBaseFactory();`
- L54 _public member_ `TSubclassOf<class UInterchangePipelineBase> ParentClass;` — `UPROPERTY(EditAnywhere, Category = InterchangeBlueprintPipelineBaseFactory)` — The parent class of the created blueprint
- L57 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L58 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UInterchangeEditorBlueprintPipelineBaseFactory`  
`class UInterchangeEditorBlueprintPipelineBaseFactory : public UFactory`  
_L63-82_
- reflection: `UCLASS(hidecategories = Object, collapsecategories)`
- inherits: `UFactory`
- L68 _public prototype_ `UInterchangeEditorBlueprintPipelineBaseFactory();`
- L76 _public member_ `TSubclassOf<class UInterchangeEditorPipelineBase> ParentClass;` — `UPROPERTY(EditAnywhere, Category = InterchangeEditorBlueprintPipelineBaseFactory)` — The parent class of the created blueprint
- L79 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;`
- L80 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;`

#### class `UInterchangePipelineBaseFactory`  
`class UInterchangePipelineBaseFactory : public UFactory`  
_L85-99_
- reflection: `UCLASS(hidecategories = Object, collapsecategories)`
- inherits: `UFactory`
- L90 _public prototype_ `UInterchangePipelineBaseFactory();`
- L93 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L94 _public prototype_ `virtual FText GetDisplayName() const override;`
- L95 _public prototype_ `virtual bool ConfigureProperties() override;`
- L98 _private member_ `UClass* PipelineClass = nullptr;`

#### class `UInterchangePythonPipelineAssetFactory`  
`class UInterchangePythonPipelineAssetFactory : public UFactory`  
_L102-116_
- reflection: `UCLASS(hidecategories = Object, collapsecategories)`
- inherits: `UFactory`
- L107 _public prototype_ `UInterchangePythonPipelineAssetFactory();`
- L110 _public prototype_ `virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;` — UFactory Interface
- L111 _public prototype_ `virtual FText GetDisplayName() const override;`
- L112 _public prototype_ `virtual bool ConfigureProperties() override;`
- L115 _private member_ `UClass* PythonClass = nullptr;`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/SInterchangeAssetCard.h` (Private)


#### class `SInterchangeAssetCard`  
`class SInterchangeAssetCard : public SCompoundWidget`  
_L19-63_
- inherits: `SCompoundWidget`
- L22 _public prototype_ `~SInterchangeAssetCard();`
- L24 _public function_ `SLATE_BEGIN_ARGS(SInterchangeAssetCard) : _PreviewNodeContainer(nullptr) , _AssetClass(nullptr) , _CardDisabled(false) , _ShouldImportAssetType() , _OnImportAssetTypeChanged()`
- L40 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget
- L42 _public prototype_ `void RefreshCard(UInterchangeBaseNodeContainer* InPreviewNodeContainer);`
- L44 _public prototype_ `bool RefreshHasConflicts(const TArray<FInterchangeConflictInfo>& InConflictInfos);`
- L48 _protected member_ `int32 CardAssetCount = 0;`
- L49 _protected member_ `int32 CardAssetToImportCount = 0;`
- L50 _protected member_ `int32 CardAssetDisabledCount = 0;`
- L51 _protected member_ `FString CardTooltip;`
- L52 _protected member_ `bool bHasConflictWarnings = false;`
- L53 _protected member_ `bool bCardDisabled = false;`
- L56 _protected member_ `UClass* AssetClass = nullptr;` — The factory asset class so we can know which kind of Unreal asset this card is for.
- L59 _protected member_ `FInterchangeCard_ShouldImportAssetType ShouldImportAssetType;` — Delegate to invoke when we update the should import asset type UI.
- L62 _protected member_ `FInterchangeCard_OnImportAssetTypeChanged OnImportAssetTypeChanged;` — Delegate to invoke when should import asset type value change.

#### class `SInterchangeAssetCardList`  
`class SInterchangeAssetCardList : public SCompoundWidget`  
_L65-88_
- inherits: `SCompoundWidget`
- L69 _public function_ `SLATE_BEGIN_ARGS(SInterchangeAssetCardList) : _AssetCards()`
- L77 _public prototype_ `void Construct(const FArguments& InArgs);` — Construct this widget
- L79 _public prototype_ `void RefreshList(UInterchangeBaseNodeContainer* InPreviewNodeContainer);`
- L83 _private member_ `TArray<TSharedPtr<SInterchangeAssetCard>>* AssetCards;`
- L85 _private prototype_ `TSharedRef<ITableRow> MakeAssetCardListRowWidget(TSharedPtr<SInterchangeAssetCard> InElement, const TSharedRef<STableViewBase>& OwnerTable);`
- L87 _private member_ `TSharedPtr <SListView<TSharedPtr<SInterchangeAssetCard>>> AssetCardList;`

#### Free symbols / members of external scopes

- L16 _delegate_ `DECLARE_DELEGATE_OneParam(FInterchangeCard_OnImportAssetTypeChanged, bool) DECLARE_DELEGATE_RetVal(bool, FInterchangeCard_ShouldImportAssetType) class SInterchangeAssetCard : public SCompoundWidget { public: ~SInterchangeAssetCard(); SLATE_BEGIN_ARGS(SInterchangeAssetCard) : _PreviewNodeContainer(nullptr) , _AssetClass(nullptr) , _CardDisabled(false) , _ShouldImportAssetType() , _OnImportAssetTypeChanged() {} SLATE_ARGUMENT(UInterchangeBaseNodeContainer*, PreviewNodeContainer) SLATE_ARGUMENT(UClass*, AssetClass) SLATE_ARGUMENT(bool, CardDisabled) SLATE_EVENT(FInterchangeCard_ShouldImportAssetType, ShouldImportAssetType) SLATE_EVENT(FInterchangeCard_OnImportAssetTypeChanged, OnImportAssetTypeChanged) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); void RefreshCard(UInterchangeBaseNodeContainer* InPreviewNodeContainer); bool RefreshHasConflicts(const TArray<FInterchangeConflictInfo>& InConflictInfos); protected: int32 CardAssetCount = 0; int32 CardAssetToImportCount = 0; int32 CardAssetDisabledCount = 0; FString CardTooltip; bool bHasConflictWarnings = false; bool bCardDisabled = false;`
- L17 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FInterchangeCard_ShouldImportAssetType) class SInterchangeAssetCard : public SCompoundWidget { public: ~SInterchangeAssetCard(); SLATE_BEGIN_ARGS(SInterchangeAssetCard) : _PreviewNodeContainer(nullptr) , _AssetClass(nullptr) , _CardDisabled(false) , _ShouldImportAssetType() , _OnImportAssetTypeChanged() {} SLATE_ARGUMENT(UInterchangeBaseNodeContainer*, PreviewNodeContainer) SLATE_ARGUMENT(UClass*, AssetClass) SLATE_ARGUMENT(bool, CardDisabled) SLATE_EVENT(FInterchangeCard_ShouldImportAssetType, ShouldImportAssetType) SLATE_EVENT(FInterchangeCard_OnImportAssetTypeChanged, OnImportAssetTypeChanged) SLATE_END_ARGS() public: void Construct(const FArguments& InArgs); void RefreshCard(UInterchangeBaseNodeContainer* InPreviewNodeContainer); bool RefreshHasConflicts(const TArray<FInterchangeConflictInfo>& InConflictInfos); protected: int32 CardAssetCount = 0; int32 CardAssetToImportCount = 0; int32 CardAssetDisabledCount = 0; FString CardTooltip; bool bHasConflictWarnings = false; bool bCardDisabled = false; UClass* AssetClass = nullptr;`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/SInterchangeGraphInspectorWindow.h` (Private)


#### class `SInterchangeGraphInspectorTreeView`  
`class SInterchangeGraphInspectorTreeView : public STreeView<UInterchangeBaseNode*>`  
_L16-55_
- inherits: `STreeView<UInterchangeBaseNode*>`
- L19 _public prototype_ `~SInterchangeGraphInspectorTreeView();`
- L21 _public function_ `SLATE_BEGIN_ARGS(SInterchangeGraphInspectorTreeView) : _InterchangeBaseNodeContainer(nullptr) , _bPreview(false) , _OnSelectionChangedDelegate()`
- L26 _public prototype_ `SLATE_ARGUMENT(UInterchangeBaseNodeContainer*, InterchangeBaseNodeContainer) SLATE_ARGUMENT(bool, bPreview) SLATE_EVENT(FOnGraphInspectorSelectionChanged, OnSelectionChangedDelegate) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L33 _public prototype_ `TSharedRef< ITableRow > OnGenerateRowGraphInspectorTreeView(UInterchangeBaseNode* Item, const TSharedRef< STableViewBase >& OwnerTable);`
- L34 _public prototype_ `void OnGetChildrenGraphInspectorTreeView(UInterchangeBaseNode* InParent, TArray< UInterchangeBaseNode* >& OutChildren);`
- L36 _public prototype_ `void OnToggleSelectAll(ECheckBoxState CheckType);`
- L37 _public prototype_ `FReply OnExpandAll();`
- L38 _public prototype_ `FReply OnCollapseAll();`
- L40 _protected member_ `UInterchangeBaseNodeContainer* InterchangeBaseNodeContainer = nullptr;`
- L41 _protected member_ `bool bPreview = false;`
- L43 _protected member_ `FOnGraphInspectorSelectionChanged OnSelectionChangedDelegate;` — Delegate to invoke when selection changes.
- L45 _protected member_ `TArray<UInterchangeBaseNode*> RootNodeArray;` — the elements we show in the tree view
- L48 _protected prototype_ `TSharedPtr<SWidget> OnOpenContextMenu();` — Open a context menu for the current selection
- L49 _protected prototype_ `void RecursiveSetImport(UInterchangeBaseNode* Node, bool bState);`
- L50 _protected prototype_ `void RecursiveSetExpand(UInterchangeBaseNode* Node, bool ExpandState);`
- L51 _protected prototype_ `void AddSelectionToImport();`
- L52 _protected prototype_ `void RemoveSelectionFromImport();`
- L53 _protected prototype_ `void SetSelectionImportState(bool MarkForImport);`
- L54 _protected prototype_ `void OnTreeViewSelectionChanged(UInterchangeBaseNode* Item, ESelectInfo::Type SelectionType);`

#### class `SInterchangeGraphInspectorWindow`  
`class SInterchangeGraphInspectorWindow : public SCompoundWidget`  
_L57-113_
- inherits: `SCompoundWidget`
- L60 _public function_ `SLATE_BEGIN_ARGS(SInterchangeGraphInspectorWindow) : _InterchangeBaseNodeContainer(nullptr) , _bPreview(false) , _OwnerWindow()`
- L73 _public prototype_ `SInterchangeGraphInspectorWindow();`
- L74 _public prototype_ `~SInterchangeGraphInspectorWindow();`
- L76 _public prototype_ `void Construct(const FArguments& InArgs);`
- L77 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L79 _public prototype_ `void CloseGraphInspector();`
- L81 _public function_ `FReply OnCloseDialog()`
- L87 _public function_ `virtual FReply OnKeyDown( const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent ) override`
- L98 _private member_ `TWeakPtr< SWindow > OwnerWindow;`
- L100 _private prototype_ `TSharedRef<SBox> SpawnGraphInspector();`
- L101 _private prototype_ `void OnSelectionChanged(UInterchangeBaseNode* Item, ESelectInfo::Type SelectionType);`
- L105 _private member_ `UInterchangeBaseNodeContainer* InterchangeBaseNodeContainer;`
- L106 _private member_ `bool bPreview = false;`
- L111 _private member_ `TSharedPtr<SInterchangeGraphInspectorTreeView> GraphInspectorTreeview;`
- L112 _private member_ `TSharedPtr<IDetailsView> GraphInspectorDetailsView;`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnGraphInspectorSelectionChanged, UInterchangeBaseNode*, ESelectInfo::Type) class SInterchangeGraphInspectorTreeView : public STreeView<UInterchangeBaseNode*> { public: ~SInterchangeGraphInspectorTreeView(); SLATE_BEGIN_ARGS(SInterchangeGraphInspectorTreeView) : _InterchangeBaseNodeContainer(nullptr) , _bPreview(false) , _OnSelectionChangedDelegate() {} SLATE_ARGUMENT(UInterchangeBaseNodeContainer*, InterchangeBaseNodeContainer) SLATE_ARGUMENT(bool, bPreview) SLATE_EVENT(FOnGraphInspectorSelectionChanged, OnSelectionChangedDelegate) SLATE_END_ARGS() void Construct(const FArguments& InArgs); TSharedRef< ITableRow > OnGenerateRowGraphInspectorTreeView(UInterchangeBaseNode* Item, const TSharedRef< STableViewBase >& OwnerTable); void OnGetChildrenGraphInspectorTreeView(UInterchangeBaseNode* InParent, TArray< UInterchangeBaseNode* >& OutChildren); void OnToggleSelectAll(ECheckBoxState CheckType); FReply OnExpandAll(); FReply OnCollapseAll(); protected: UInterchangeBaseNodeContainer* InterchangeBaseNodeContainer = nullptr; bool bPreview = false; FOnGraphInspectorSelectionChanged OnSelectionChangedDelegate; TArray<UInterchangeBaseNode*> RootNodeArray; TSharedPtr<SWidget> OnOpenContextMenu(); void RecursiveSetImport(UInterchangeBaseNode* Node, bool bState); void RecursiveSetExpand(UInterchangeBaseNode* Node, bool ExpandState); void AddSelectionToImport(); void RemoveSelectionFromImport(); void SetSelectionImportState(bool MarkForImport);`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/SInterchangePipelineConfigurationDialog.h` (Private)


#### class `SInterchangePipelineStackPresetItem`  
`class SInterchangePipelineStackPresetItem : public SHorizontalBox`  
_L28-43_
- inherits: `SHorizontalBox`
- desc: Pipeline Stack Presets
- L31 _public function_ `SLATE_BEGIN_ARGS(SInterchangePipelineStackPresetItem) : _PresetItem(nullptr)`
- L34 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FString>, PresetItem) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L39 _public prototype_ `static const FSlateBrush* GetItemIconBrush();`
- L42 _private member_ `TSharedPtr<FString> PresetItem = nullptr;`

#### struct `FInterchangePipelineItemType`  
`struct FInterchangePipelineItemType`  
_L48-58_
- desc: Pipeline List View
- L51 _public member_ `FString DisplayName;`
- L52 _public member_ `UInterchangePipelineBase* Pipeline;`
- L53 _public member_ `UObject* ReimportObject = nullptr;`
- L54 _public member_ `UInterchangeBaseNodeContainer* Container = nullptr;`
- L55 _public member_ `UInterchangeSourceData* SourceData = nullptr;`
- L56 _public member_ `bool bShowEssentials = false;`
- L57 _public member_ `TArray<FInterchangeConflictInfo> ConflictInfos;`

#### class `SInterchangePipelineItem`  
`class SInterchangePipelineItem : public STableRow<TSharedPtr<FInterchangePipelineItemType>>`  
_L60-72_
- inherits: `STableRow<TSharedPtr<FInterchangePipelineItemType>>`
- L63 _public prototype_ `void Construct( const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedPtr<FInterchangePipelineItemType> InPipelineElement);`
- L68 _private prototype_ `const FSlateBrush* GetImageItemIcon() const;`
- L69 _private prototype_ `FSlateColor GetTextColor() const;`
- L71 _private member_ `TSharedPtr<FInterchangePipelineItemType> PipelineElement = nullptr;`

#### enum `ECloseEventType`  
`enum class ECloseEventType : uint8`  
_L76-81_
- L78 _public enumerator_ `Cancel`
- L79 _public enumerator_ `PrimaryButton`
- L80 _public enumerator_ `WindowClosing`

#### class `SInterchangePipelineConfigurationDialog`  
`class SInterchangePipelineConfigurationDialog : public SCompoundWidget`  
_L83-249_
- inherits: `SCompoundWidget`
- L86 _public function_ `SLATE_BEGIN_ARGS(SInterchangePipelineConfigurationDialog) : _OwnerWindow()`
- L106 _public prototype_ `SInterchangePipelineConfigurationDialog();`
- L107 _public prototype_ `virtual ~SInterchangePipelineConfigurationDialog();`
- L109 _public prototype_ `void Construct(const FArguments& InArgs);`
- L110 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L112 _public prototype_ `void ClosePipelineConfiguration(const ECloseEventType CloseEventType);`
- L114 _public function_ `FReply OnCloseDialog(const ECloseEventType CloseEventType)`
- L120 _public function_ `void OnWindowClosed(const TSharedRef<SWindow>& ClosedWindow)`
- L125 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L127 _public function_ `bool IsCanceled() const`
- L128 _public function_ `bool IsImportAll() const`
- L131 _private prototype_ `TSharedRef<SBox> SpawnPipelineConfiguration();`
- L132 _private prototype_ `TSharedRef<SBox> SpawnCardsConfiguration();`
- L134 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent&) const;`
- L135 _private prototype_ `FText GetSourceDescription() const;`
- L136 _private prototype_ `FReply OnResetToDefault();`
- L138 _private prototype_ `bool ValidateAllPipelineSettings(TOptional<FText>& OutInvalidReason) const;`
- L139 _private prototype_ `bool IsImportButtonEnabled() const;`
- L140 _private prototype_ `FText GetImportButtonTooltip() const;`
- L142 _private prototype_ `void SaveAllPipelineSettings() const;`
- L145 _private prototype_ `static FString GetPipelineDisplayName(const UInterchangePipelineBase* Pipeline);` — Internal utility function to properly display pipeline's name
- L147 _private prototype_ `void SetEditPipeline(FInterchangePipelineItemType* PipelineItemToEdit);`
- L148 _private prototype_ `FReply OnEditTranslatorSettings();`
- L150 _private prototype_ `void GatherConflictAndExtraInfo(TArray<FInterchangeConflictInfo>& ConflictInfo, TMap<FString, FString>& ExtraInfo);`
- L153 _private prototype_ `void OnExtendPipelineDetailsViewSettingsMenu(FMenuBuilder& MenuBuilder);` — Details View Menu Extension
- L154 _private prototype_ `void Execute_ToggleShowEssentials();`
- L155 _private prototype_ `void Execute_ToggleFilterOnContent();`
- L158 _private member_ `TWeakPtr< SWindow > OwnerWindow;`
- L159 _private member_ `double OriginalMinWindowSize = 0.0;`
- L160 _private member_ `double DeltaClientWindowSize = 0.0;`
- L161 _private member_ `TWeakObjectPtr<UInterchangeSourceData> SourceData;`
- L162 _private member_ `TWeakObjectPtr<UInterchangeBaseNodeContainer> BaseNodeContainer;`
- L163 _private member_ `mutable TWeakObjectPtr<UInterchangeBaseNodeContainer> PreviewNodeContainer;`
- L164 _private member_ `TWeakObjectPtr<UObject> ReimportObject;`
- L165 _private member_ `TWeakObjectPtr<UInterchangeTranslatorBase> Translator;`
- L166 _private member_ `TObjectPtr<UInterchangeTranslatorSettings> TranslatorSettings = nullptr;`
- L167 _private member_ `TArray<FInterchangeStackInfo> PipelineStacks;`
- L168 _private member_ `TArray<UInterchangePipelineBase*>* OutPipelines;`
- L171 _private member_ `TArray<TSharedPtr<FString>> AvailableStacks;` — The available stacks
- L173 _private prototype_ `TSharedRef<SWidget> MakePipelinePresetComboBoxEntryWidget(TSharedPtr<FString> InElement);`
- L174 _private prototype_ `FText GetSelectedPipelineStackPresetLabelText() const;`
- L176 _private prototype_ `void OnStackSelectionChanged(TSharedPtr<FString> String, ESelectInfo::Type);`
- L177 _private prototype_ `void UpdateStack(const FName& NewStackName);`
- L182 _private member_ `TSharedPtr<SPipelineListViewType> PipelinesListView;`
- L183 _private member_ `TArray< TSharedPtr< FInterchangePipelineItemType > > PipelineListViewItems;`
- L186 _private prototype_ `TSharedRef<ITableRow> MakePipelineListRowWidget(TSharedPtr<FInterchangePipelineItemType> InElement, const TSharedRef<STableViewBase>& OwnerTable);` — list view generate row callback
- L188 _private prototype_ `void OnPipelineSelectionChanged(TSharedPtr<FInterchangePipelineItemType> InItem, ESelectInfo::Type SelectInfo);`
- L197 _private member_ `TArray<TObjectPtr<UClass>> PipelineSupportAssetClasses;`
- L204 _private member_ `TMap<UClass*, FPerSupportedAssetClassData> PipelineSupportedAssetData;`
- L206 _private member_ `TSharedPtr<SScrollBar> CardViewScrollbar;`
- L207 _private member_ `TMap<UClass*, FFactoryNodeEnabledData> EnableDataPerFactoryNodeClass;`
- L208 _private member_ `TSharedPtr<SInterchangeAssetCardList> CardViewList = nullptr;`
- L209 _private member_ `TArray<TSharedPtr<SInterchangeAssetCard>> AssetCards;`
- L210 _private prototype_ `void UpdatePipelineSupportedAssetClasses();`
- L211 _private prototype_ `void UpdateEnableDataPerFactoryNodeClass();`
- L212 _private prototype_ `void FillAssetCardsList();`
- L213 _private prototype_ `void CreateCardsViewList();`
- L214 _private prototype_ `void RefreshCardsViewList();`
- L215 _private prototype_ `UInterchangeCardsPipeline* GenerateTransientCardsPipeline() const;`
- L218 _private member_ `double SplitAdvancedRatio = 0.6;` — Splitter management
- L219 _private member_ `TSharedPtr<SSplitter> CardsAndAdvancedSplitter = nullptr;`
- L221 _private prototype_ `const FSlateBrush* GetImportButtonIcon() const;`
- L223 _private prototype_ `void UpdatePreviewContainer(bool bUpdateCards) const;`
- L225 _private prototype_ `FReply OnPreviewImport() const;`
- L227 _private member_ `TSharedPtr<IDetailsView> PipelineConfigurationDetailsView;`
- L228 _private member_ `TSharedPtr<SCheckBox> UseSameSettingsForAllCheckBox;`
- L230 _private member_ `bool bSceneImport = false;`
- L231 _private member_ `bool bReimport = false;`
- L232 _private member_ `bool bCanceled = false;`
- L233 _private member_ `bool bImportAll = false;`
- L235 _private member_ `bool bPendingDetailsViewSectionReset = false;`
- L238 _private member_ `bool bTestConfigDialog = false;` — This is used to denote that the import dialog is opened from the Interchange Test Plan asset to configure the chosen Pipelines.
- L240 _private member_ `bool bFilterOptions = false;`
- L241 _private member_ `bool bShowEssentials = false;`
- L242 _private member_ `bool bShowSettings = false;`
- L243 _private member_ `bool bShowCards = true;`
- L245 _private member_ `FName CurrentStackName = NAME_None;`
- L246 _private member_ `TWeakPtr<FString> CurrentSelectedStackPresetItem = nullptr;`
- L247 _private member_ `TObjectPtr<UInterchangePipelineBase> CurrentSelectedPipeline = nullptr;`
- L248 _private member_ `TWeakPtr<FInterchangePipelineItemType> CurrentSelectedPipelineItem = nullptr;`

#### struct `SInterchangePipelineConfigurationDialog::FFactoryNodeEnabledData`  
`struct FFactoryNodeEnabledData`  
_L192-196_
- L194 _public member_ `bool bEnable = true;`
- L195 _public member_ `TObjectPtr<UClass> ObjectClass = nullptr;`

#### struct `SInterchangePipelineConfigurationDialog::FPerSupportedAssetClassData`  
`struct FPerSupportedAssetClassData`  
_L199-202_
- L201 _public member_ `TSet<UClass*> FactoryNodeClasses;`

#### Free symbols / members of external scopes

- L45 _typedef_ `typedef SComboBox< TSharedPtr<FString> > SPipelinePresetComboBox;`
- L74 _typedef_ `typedef SListView< TSharedPtr<FInterchangePipelineItemType> > SPipelineListViewType;`

### `Plugins/Interchange/Editor/Source/Pipelines/Private/SInterchangeTranslatorSettingsDialog.h` (Private)


#### class `SInterchangeTranslatorSettingsDialog`  
`class SInterchangeTranslatorSettingsDialog : public SWindow`  
_L15-53_
- inherits: `SWindow`
- L19 _public function_ `SLATE_BEGIN_ARGS(SInterchangeTranslatorSettingsDialog)`
- L26 _public prototype_ `SLATE_EVENT(FSimpleDelegate, OnClosed) SLATE_ARGUMENT(SWindow::FArguments, WindowArguments) SLATE_ARGUMENT(TWeakObjectPtr<UInterchangeTranslatorSettings>, TranslatorSettings) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Event triggered when the dialog is closed, either because one of the buttons is pressed, or the windows is closed.
- L39 _public prototype_ `bool ShowModal();` — Show a modal dialog. Will block until an input is received.
- L41 _public function_ `FOnTranslatorSettingsDialogClosed& GetTranslatorSettingsDialogClosed()`
- L44 _private member_ `FOnTranslatorSettingsDialogClosed OnTranslatorSettingsDialogClosed;`
- L46 _private member_ `TWeakObjectPtr<UInterchangeTranslatorSettings> TranslatorSettings;`
- L47 _private member_ `UInterchangeTranslatorSettings* OriginalTranslatorSettings = nullptr;`
- L48 _private member_ `UInterchangeTranslatorSettings* TranslatorSettingsCDO = nullptr;`
- L50 _private member_ `bool bTranslatorSettingsChanged = false;`
- L51 _private member_ `bool bUserResponse = false;`

#### Free symbols / members of external scopes

- L13 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnTranslatorSettingsDialogClosed, bool, bool);`
- L13 _prototype_ `DECLARE_DELEGATE_TwoParams(FOnTranslatorSettingsDialogClosed, bool, bool);`

### `Plugins/Interchange/Editor/Source/Pipelines/Public/InterchangeCardsPipeline.h` (Public)


#### class `UInterchangeCardsPipeline`  
`class UInterchangeCardsPipeline : public UInterchangePipelineBase`  
_L24-59_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInterchangePipelineBase`
- desc: This pipeline is use by the interchange default UI to enable and disable factory node. @note This is an import only pipeline that is execute only when importing from the interchange default dialog.
- L39 _public function_ `virtual bool SupportReimport() const override` — This pipeline must never be saved into any asset import data.
- L44 _public prototype_ `void SetDisabledFactoryNodes(TArray<UClass*> FactoryNodeClasses);` — Set all factory node class to disabled.
- L48 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L50 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`
- L58 _private member_ `TArray<TObjectPtr<UClass>> FactoryNodeClassesToDisabled;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API INTERCHANGEEDITORPIPELINES_API`

### `Plugins/Interchange/Editor/Source/Pipelines/Public/InterchangeEditorBlueprintPipelineBase.h` (Public)


#### class `UInterchangeEditorPipelineBase`  
`class UInterchangeEditorPipelineBase : public UInterchangePipelineBase`  
_L15-28_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangePipelineBase`
- L21 _public function_ `virtual bool IsEditorOnly() const override` — UObject Interface
- L26 _public prototype_ `virtual UWorld* GetWorld() const override;`

#### class `UInterchangeEditorBlueprintPipelineBase`  
`class UInterchangeEditorBlueprintPipelineBase : public UInterchangeBlueprintPipelineBase`  
_L34-64_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UInterchangeBlueprintPipelineBase`
- desc: This class allow users to create editor only Interchange blueprint pipeline.
- L39 _public function_ `UInterchangeEditorBlueprintPipelineBase()`
- L47 _public function_ `virtual bool IsEditorOnly() const override` — UObject Interface
- L54 _public function_ `virtual bool SupportedByDefaultBlueprintFactory() const override` — UBlueprint interface
- L59 _public function_ `virtual bool AlwaysCompileOnLoad() const override`

### `Plugins/Interchange/Editor/Source/Pipelines/Public/InterchangeEditorPipelinesModule.h` (Public)


#### class `IInterchangeEditorPipelinesModule`  
`class IInterchangeEditorPipelinesModule : public IModuleInterface`  
_L10-35_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L21 _public function_ `static inline IInterchangeEditorPipelinesModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L31 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Interchange/Editor/Source/Pipelines/Public/InterchangeGraphInspectorPipeline.h` (Public)


#### class `UInterchangeGraphInspectorPipeline`  
`class UInterchangeGraphInspectorPipeline : public UInterchangePipelineBase`  
_L21-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UInterchangePipelineBase`
- desc: This pipeline is the generic pipeline option for all types of meshes. It should be called before specialized mesh pipelines like the generic static mesh or skeletal mesh pipelines. All import options that are shared between mesh types should be added here. UPROPERTY possible meta values: @meta ImportOnly - Boolean. The property is used only for import, not for reimport. Cannot be mixed with ReimportOnly. @meta ReimportOnly - Boolean. The property is used only for reimport, not for import. Cannot be mixed with ImportOnly. @meta MeshType - String. The property is for static mesh or skeletal mesh or both. If not specified, it will apply to all mesh types.
- L36 _public function_ `virtual bool SupportReimport() const override` — This pipeline must never be saved into any asset import data.
- L40 _protected prototype_ `virtual void ExecutePipeline(UInterchangeBaseNodeContainer* BaseNodeContainer, const TArray<UInterchangeSourceData*>& SourceDatas, const FString& ContentBasePath) override;`
- L44 _protected function_ `virtual bool CanExecuteOnAnyThread(EInterchangePipelineTask PipelineTask) override`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEEDITORPIPELINES_API`

### `Plugins/Interchange/Editor/Source/Pipelines/Public/InterchangePipelineConfigurationGeneric.h` (Public)


#### class `UInterchangePipelineConfigurationGeneric`  
`class UInterchangePipelineConfigurationGeneric : public UInterchangePipelineConfigurationBase`  
_L18-27_
- reflection: `UCLASS(MinimalAPI, BlueprintType, editinlinenew)`
- inherits: `UInterchangePipelineConfigurationBase`
- L25 _protected prototype_ `virtual EInterchangePipelineConfigurationDialogResult ShowPipelineDialog_Internal(FPipelineConfigurationDialogParams& InParams) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API INTERCHANGEEDITORPIPELINES_API`
