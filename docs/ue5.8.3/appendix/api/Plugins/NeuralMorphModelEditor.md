# Plugins / NeuralMorphModelEditor

- module root: `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor`
- headers: 8; symbols: 238
- symbol kinds: class=15, function=18, macro=7, member=49, namespace=20, prototype=129
- PrivateDependencyModuleNames: ApplicationCore, CoreUObject, DeveloperSettings, Engine, InputCore, Json, MLDeformerFramework, MLDeformerFrameworkEditor, NeuralMorphModel, PropertyEditor, Slate, SlateCore, ToolWidgets, UnrealEd
- PrivateIncludePathModuleNames: 
- PublicDependencyModuleNames: Core

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/NeuralMorphEditorModel.h` (Public)


#### class `UE::NeuralMorphModel::FNeuralMorphEditorModel`  
`class FNeuralMorphEditorModel : public FMLDeformerMorphModelEditorModel`  
_L25-174_
- inherits: `FMLDeformerMorphModelEditorModel`
- desc: The editor model related to the neural morph model's runtime class (UNeuralMorphModel).
- L30 _public prototype_ `static FMLDeformerEditorModel* MakeInstance();` — We need to implement this static MakeInstance method.
- L33 _public function_ `virtual FString GetReferencerName() const override` — FGCObject overrides.
- L37 _public prototype_ `virtual void Init(const InitSettings& Settings) override;` — FMLDeformerEditorModel overrides.
- L38 _public prototype_ `virtual ETrainingResult Train() override;`
- L39 _public prototype_ `virtual void InitInputInfo(UMLDeformerInputInfo* InputInfo) override;`
- L40 _public prototype_ `virtual FText GetOverlayText() const override;`
- L41 _public prototype_ `virtual void OnPropertyChanged(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _public prototype_ `virtual TSharedPtr<SMLDeformerInputWidget> CreateInputWidget() override;`
- L43 _public prototype_ `virtual void OnPostInputAssetChanged() override;`
- L44 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L45 _public function_ `virtual bool GetSupportsPerTrainingInputAnimVertexMask() const override`
- L46 _public prototype_ `virtual void UpdateTrainingDeviceList() override;`
- L47 _public prototype_ `virtual UMeshDeformer* GetActiveHeatMapDeformer() const override;`
- L48 _public prototype_ `virtual void UpdateIsReadyForTrainingState() override;`
- L49 _public prototype_ `virtual bool LoadTrainedNetwork() const override;`
- L53 _public prototype_ `virtual const TArrayView<const float> GetMaskForMorphTarget(int32 MorphTargetIndex) const override;` — FMLDeformerMorphModelEditorModel overrides.
- L54 _public function_ `virtual bool IsInputMaskingSupported() const override`
- L58 _public function_ `UNeuralMorphModel* GetNeuralMorphModel() const` — Get a pointer to the neural morph runtime model.
- L69 _public prototype_ `void BuildMaskBuffer(TArray<float>& OutMaskBuffer);` — Build a set of masks, all concatenated into one flat array. The number of masks is (NumBones + NumCurves + NumBoneGroups + NumCurveGroups). Each mask contains Model->GetNumBaseMeshVerts() number of floats. The masks for curves and curve groups are all set to 1.0. The masks for bones and bone groups contain all the vertices they influence during skinning, as well as the ones from the parent bone. This will modify the item mask buffer as returned by UMLDeformerMorphModel::GetInputItemMaskBuffer(). @param OutMaskBuffer The mask buffer to write to. This will automatically be resized.
- L72 _public prototype_ `void RebuildEditorMaskInfo();` — Rebuild the mask buffer.
- L78 _public prototype_ `FName GenerateUniqueBoneGroupName() const;` — Generate a unique name for a bone group. @return The unique name.
- L84 _public prototype_ `FName GenerateUniqueCurveGroupName() const;` — Generate a unique name for a curve group. @return The unique name.
- L89 _public prototype_ `void RemoveNonExistingMaskInfos();` — Remove mask infos for bones that do not exist in the bone include list.
- L92 _public prototype_ `void ResetBoneMaskInfos();` — Clear all bone mask infos.
- L95 _public prototype_ `void ResetBoneGroupMaskInfos();` — Clear all bone group mask infos.
- L107 _public prototype_ `void GenerateBoneMaskInfos(int32 HierarchyDepth);` — Generate bone mask infos for all bones in the bone input list. Use a specific hierarchy depth for this, which defines how deep up and down the hierarchy we should traverse for each specific bone. Imagine we generate the mask for a bone in a chain of bones. We look at all vertices skinned to this bone, and include those vertices in the mask. With a hierarchy depth of 1, include all vertices skinned to its parent bone as well as to its child bone. With a hierarchy depth of 2 we also include the parent of the parent and the child of the child if it exists. We always want the mask to be large enough, otherwise if say skin stretches a lot, we will not capture the vertex deltas for those vertices far away from the bone, which can cause issues. However we don't want the mask to be too large either, as that costs performance and memory usage. @param HierarchyDepth The hierarchy depth to use, which should be a value of 1 or above.
- L115 _public prototype_ `void GenerateBoneGroupMaskInfos(int32 HierarchyDepth);` — Generate the mask infos for all bone groups. Look at the GenerateBoneMaskInfos method for a detailed description of the HierarchyDepth. @param HierarchyDepth The hierarchy depth to use, which should be a value of 1 or above. @see GenerateBoneMaskInfos
- L124 _public prototype_ `void GenerateBoneMaskInfo(int32 InputInfoBoneIndex, int32 HierarchyDepth);` — Generate the mask info for a given bone. Look at the GenerateBoneMaskInfos method for a detailed description of the HierarchyDepth. @param InputInfoBoneIndex The bone index inside the input info object. @param HierarchyDepth The hierarchy depth to use, which should be a value of 1 or above. @see GenerateBoneMaskInfos
- L133 _public prototype_ `void GenerateBoneGroupMaskInfo(int32 InputInfoBoneGroupIndex, int32 HierarchyDepth);` — Generate the mask info for a given bone group. Look at the GenerateBoneMaskInfos method for a detailed description of the HierarchyDepth. @param InputInfoBoneIndex The bone index inside the input info object. @param HierarchyDepth The hierarchy depth to use, which should be a value of 1 or above. @see GenerateBoneMaskInfos
- L141 _public function_ `void SetMaskVisualizationItemIndex(int32 InMaskVizItemIndex)` — Set the mask visualization item index. This specifies which item (bone, curve, bone group, curve group) to visualize the mask for. The first index values are for all input bones. Indices that come after that are for curves, then for bone groups and finally followed by curve groups. So if there are 10 input bones and 4 bone groups, and the visualization index is 11, it means it's for the second bone group. @param InMaskVizItemIndex The mask visualization index.
- L149 _public function_ `int32 GetMaskVisualizationItemIndex() const` — Get the mask visualization item index. This specifies which item (bone, curve, bone group, curve group) to visualize the mask for. The first index values are for all input bones. Indices that come after that are for curves, then for bone groups and finally followed by curve groups. So if there are 10 input bones and 4 bone groups, and the visualization index is 11, it means it's for the second bone group. @return The item to visualize the mask for.
- L158 _public prototype_ `void DebugDrawItemMask(FPrimitiveDrawInterface* PDI, int32 MaskItemIndex, const FVector& DrawOffset);` — Draw the mask for a given item. An item can be a bone, curve or anything else that has a mask. @param PDI The debug draw interface. @param MaskItemIndex The item index. The valid range on default is [0..NumEditorInfoBones + NumEditorInfoCurves - 1]. The curves are attached after the bones. So if you have 10 bones, and 5 curves, and the MaskItemIndex is value 12, it will draw the mask for the third curve, because items [0..9] would be for the bones, and [10..14] for the curves. @param DrawOffset The offset in world space units to draw the mask at.
- L170 _private prototype_ `void AddTwistBones(const FReferenceSkeleton& RefSkel, TArray<int32>& SkelBoneIndices);` — Add child twist bones to the list of skeletal bone indices. This will iterate over all bones inside the SkelBoneIndices array and check if there are direct child nodes inside the ref skeleton that contain the substring "twist" inside their name. If so, that bone will be added to the SkelBoneIndices array as well. The "twist" string is case-insensitive. The "twist" string can be configured on a per project basis inside the UNeuralMorphModel::TwistBoneSubString property, which is exposed in the per project .ini file. On default this value is "twist". @param RefSkel The reference skeleton we use to find child nodes. @param SkelBoneIndices The input and output array of indices inside the reference skeleton. This method potentially adds new entries to this array.
- L173 _protected member_ `int32 MaskVizItemIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NEURALMORPHMODELEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace MLDeformer` (scope `UE`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace NeuralMorphModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/NeuralMorphEditorProjectSettings.h` (Public)


#### class `UNeuralMorphEditorProjectSettings`  
`class UNeuralMorphEditorProjectSettings : public UDeveloperSettings`  
_L13-40_
- reflection: `UCLASS(MinimalAPI, config = EditorPerProjectUserSettings)`
- inherits: `UDeveloperSettings`
- L19 _public prototype_ `static const UNeuralMorphEditorProjectSettings* Get();`
- L22 _public function_ `virtual FName GetContainerName() const` — UDeveloperSettings overrides
- L23 _public function_ `virtual FName GetCategoryName() const`
- L24 _public function_ `virtual FName GetSectionName() const`
- L26 _public prototype_ `virtual FText GetSectionText() const override;`
- L27 _public prototype_ `virtual FText GetSectionDescription() const override;`
- L39 _public member_ `FString TwistBoneFilter = TEXT("twi` — `UPROPERTY(config, EditAnywhere, Category = "Bone and Bone Group masking")` — The bone name filter that identifies twist bones. Any bone name with this string inside its name will be seen as a twist bone. This is only used during bone and bone group mask generation inside the Neural Morph Model. Twist bones that are a child of the bones included in the bone mask are automatically included inside the mask generation as well. We use this case-insensitive sub-string to identify twist bones. Set this to an empty string to disable automatically adding twist bones.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NEURALMORPHMODELEDITOR_API`

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/NeuralMorphModelDetails.h` (Public)


#### class `UE::NeuralMorphModel::FNeuralMorphModelDetails`  
`class FNeuralMorphModelDetails : public UE::MLDeformer::FMLDeformerMorphModelDetails`  
_L18-28_
- inherits: `UE::MLDeformer::FMLDeformerMorphModelDetails`
- desc: The detail customization for the neural morph model.
- L23 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it.
- L26 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — ILayoutDetails overrides.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API NEURALMORPHMODELEDITOR_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace NeuralMorphModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/NeuralMorphModelVizSettingsDetails.h` (Public)


#### class `UE::NeuralMorphModel::FNeuralMorphModelVizSettingsDetails`  
`class FNeuralMorphModelVizSettingsDetails : public UE::MLDeformer::FMLDeformerMorphModelVizSettingsDetails`  
_L16-24_
- inherits: `UE::MLDeformer::FMLDeformerMorphModelVizSettingsDetails`
- desc: The neural morph model visualization settings detail customization. This is inherited from the Morph Model detail customization. We do not have to do anything else. We still need this class in order to do our detail customization correctly. Just using the Morph Model directly would cause issues.
- L20 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace NeuralMorphModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/NeuralMorphTrainingModel.h` (Public)


#### class `UNeuralMorphTrainingModel`  
`class UNeuralMorphTrainingModel : public UMLDeformerGeomCacheTrainingModel`  
_L17-47_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UMLDeformerGeomCacheTrainingModel`
- desc: The training model for the neural morph model. This class is our link to the Python training.
- L23 _public prototype_ `virtual void Init(UE::MLDeformer::FMLDeformerEditorModel* InEditorModel) override;`
- L31 _public prototype_ `int32 Train() const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "Training Model")` — Main training function, with implementation in python. You need to implement this method. See the UMLDeformerTrainingModel documentation for more details. @see UMLDeformerTrainingModel
- L34 _public prototype_ `int32 GetNumBoneGroups() const;` — `UFUNCTION(BlueprintPure, Category = "Training Model")`
- L37 _public prototype_ `int32 GetNumCurveGroups() const;` — `UFUNCTION(BlueprintPure, Category = "Training Model")`
- L40 _public prototype_ `TArray<int32> GenerateBoneGroupIndices() const;` — `UFUNCTION(BlueprintPure, Category = "Training Model")`
- L43 _public prototype_ `TArray<int32> GenerateCurveGroupIndices() const;` — `UFUNCTION(BlueprintPure, Category = "Training Model")`
- L46 _public prototype_ `TArray<float> GetMorphTargetMasks() const;` — `UFUNCTION(BlueprintPure, Category = "Training Model")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API NEURALMORPHMODELEDITOR_API`

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/SNeuralMorphBoneGroupsWidget.h` (Public)


#### class `UE::NeuralMorphModel::FNeuralMorphBoneGroupsCommands`  
`class FNeuralMorphBoneGroupsCommands : public TCommands<FNeuralMorphBoneGroupsCommands>`  
_L25-39_
- inherits: `TCommands<FNeuralMorphBoneGroupsCommands>`
- L29 _public prototype_ `FNeuralMorphBoneGroupsCommands();`
- L30 _public prototype_ `virtual void RegisterCommands() override;`
- L33 _public member_ `TSharedPtr<FUICommandInfo> CreateGroup;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelectedItems;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> ClearGroups;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> AddBoneToGroup;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> CopyBoneGroups;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> PasteBoneGroups;`

#### class `UE::NeuralMorphModel::FNeuralMorphBoneGroupsTreeElement`  
`class FNeuralMorphBoneGroupsTreeElement : public TSharedFromThis<FNeuralMorphBoneGroupsTreeElement>`  
_L42-57_
- inherits: `TSharedFromThis<FNeuralMorphBoneGroupsTreeElement>`
- L46 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FNeuralMorphBoneGroupsTreeElement> InTreeElement, TSharedPtr<SNeuralMorphBoneGroupsWidget> InTreeWidget);`
- L48 _public function_ `bool IsGroup() const`
- L51 _public member_ `FName Name;`
- L52 _public member_ `TArray<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>> Children;`
- L53 _public member_ `TWeakPtr<FNeuralMorphBoneGroupsTreeElement> ParentGroup;`
- L54 _public member_ `FSlateColor TextColor;`
- L55 _public member_ `int32 GroupIndex = INDEX_NONE;`
- L56 _public member_ `int32 GroupBoneIndex = INDEX_NONE;`

#### class `UE::NeuralMorphModel::SNeuralMorphBoneGroupsTreeRowWidget`  
`class SNeuralMorphBoneGroupsTreeRowWidget : public STableRow<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>>`  
_L60-71_
- inherits: `STableRow<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>>`
- L64 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FNeuralMorphBoneGroupsTreeElement> InTreeElement, TSharedPtr<SNeuralMorphBoneGroupsWidget> InTreeView);`
- L67 _private member_ `TWeakPtr<FNeuralMorphBoneGroupsTreeElement> WeakTreeElement;`
- L68 _private prototype_ `FText GetName() const;`

#### class `UE::NeuralMorphModel::SNeuralMorphBoneGroupsWidget`  
`class SNeuralMorphBoneGroupsWidget : public STreeView<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>>`  
_L74-118_
- inherits: `STreeView<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>>`
- L78 _public function_ `SLATE_BEGIN_ARGS(SNeuralMorphBoneGroupsWidget)`
- L79 _public prototype_ `SLATE_ARGUMENT(FNeuralMorphEditorModel*, EditorModel) SLATE_ARGUMENT(TSharedPtr<UE::MLDeformer::SMLDeformerInputWidget>, InputWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L84 _public prototype_ `void BindCommands(TSharedPtr<FUICommandList> CommandList);`
- L85 _public prototype_ `void Refresh(bool bBroadcastPropertyChanged=false);`
- L87 _public prototype_ `FText GetSectionTitle() const;`
- L88 _public prototype_ `int32 GetNumSelectedGroups() const;`
- L89 _public prototype_ `TSharedPtr<UE::MLDeformer::SMLDeformerInputWidget> GetInputWidget() const;`
- L92 _private prototype_ `void AddElement(TSharedPtr<FNeuralMorphBoneGroupsTreeElement> Element, TSharedPtr<FNeuralMorphBoneGroupsTreeElement> ParentElement);`
- L93 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FNeuralMorphBoneGroupsTreeElement> InItem, TArray<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>>& OutChildren);`
- L94 _private prototype_ `void OnSelectionChanged(TSharedPtr<FNeuralMorphBoneGroupsTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L95 _private prototype_ `const TArray<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>>& GetRootElements() const;`
- L96 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L97 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FNeuralMorphBoneGroupsTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L98 _private prototype_ `TSharedPtr<SWidget> CreateContextMenuWidget() const;`
- L100 _private prototype_ `void UpdateTreeElements();`
- L101 _private prototype_ `void RefreshTree(bool bBroadcastPropertyChanged);`
- L102 _private prototype_ `bool BroadcastModelPropertyChanged(const FName PropertyName);`
- L103 _private prototype_ `TSharedPtr<SWidget> CreateContextWidget() const;`
- L105 _private prototype_ `void OnCopyBoneGroups() const;`
- L106 _private prototype_ `void OnPasteBoneGroups();`
- L108 _private prototype_ `void OnCreateBoneGroup();`
- L109 _private prototype_ `void OnDeleteSelectedItems();`
- L110 _private prototype_ `void OnClearBoneGroups();`
- L111 _private prototype_ `void OnAddBoneToGroup();`
- L114 _private member_ `TArray<TSharedPtr<FNeuralMorphBoneGroupsTreeElement>> RootElements;`
- L115 _private member_ `TSharedPtr<UE::MLDeformer::SMLDeformerInputWidget> InputWidget;`
- L116 _private member_ `FNeuralMorphEditorModel* EditorModel = nullptr;`
- L117 _private member_ `FText SectionTitle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NEURALMORPHMODELEDITOR_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace MLDeformer` (scope `UE`)
- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace NeuralMorphModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/SNeuralMorphCurveGroupsWidget.h` (Public)


#### class `UE::NeuralMorphModel::FNeuralMorphCurveGroupsCommands`  
`class FNeuralMorphCurveGroupsCommands : public TCommands<FNeuralMorphCurveGroupsCommands>`  
_L26-40_
- inherits: `TCommands<FNeuralMorphCurveGroupsCommands>`
- L30 _public prototype_ `FNeuralMorphCurveGroupsCommands();`
- L31 _public prototype_ `virtual void RegisterCommands() override;`
- L34 _public member_ `TSharedPtr<FUICommandInfo> CreateGroup;`
- L35 _public member_ `TSharedPtr<FUICommandInfo> DeleteSelectedItems;`
- L36 _public member_ `TSharedPtr<FUICommandInfo> ClearGroups;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> AddCurveToGroup;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> CopyCurveGroups;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> PasteCurveGroups;`

#### class `UE::NeuralMorphModel::FNeuralMorphCurveGroupsTreeElement`  
`class FNeuralMorphCurveGroupsTreeElement : public TSharedFromThis<FNeuralMorphCurveGroupsTreeElement>`  
_L43-58_
- inherits: `TSharedFromThis<FNeuralMorphCurveGroupsTreeElement>`
- L47 _public prototype_ `TSharedRef<ITableRow> MakeTreeRowWidget(const TSharedRef<STableViewBase>& InOwnerTable, TSharedRef<FNeuralMorphCurveGroupsTreeElement> InTreeElement, TSharedPtr<SNeuralMorphCurveGroupsWidget> InTreeWidget);`
- L49 _public function_ `bool IsGroup() const`
- L52 _public member_ `FName Name;`
- L53 _public member_ `TArray<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>> Children;`
- L54 _public member_ `TWeakPtr<FNeuralMorphCurveGroupsTreeElement> ParentGroup;`
- L55 _public member_ `FSlateColor TextColor;`
- L56 _public member_ `int32 GroupIndex = INDEX_NONE;`
- L57 _public member_ `int32 GroupCurveIndex = INDEX_NONE;`

#### class `UE::NeuralMorphModel::SNeuralMorphCurveGroupsTreeRowWidget`  
`class SNeuralMorphCurveGroupsTreeRowWidget : public STableRow<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>>`  
_L61-72_
- inherits: `STableRow<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>>`
- L65 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTable, TSharedRef<FNeuralMorphCurveGroupsTreeElement> InTreeElement, TSharedPtr<SNeuralMorphCurveGroupsWidget> InTreeView);`
- L68 _private member_ `TWeakPtr<FNeuralMorphCurveGroupsTreeElement> WeakTreeElement;`
- L69 _private prototype_ `FText GetName() const;`

#### class `UE::NeuralMorphModel::SNeuralMorphCurveGroupsWidget`  
`class SNeuralMorphCurveGroupsWidget : public STreeView<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>>`  
_L75-119_
- inherits: `STreeView<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>>`
- L79 _public function_ `SLATE_BEGIN_ARGS(SNeuralMorphCurveGroupsWidget)`
- L80 _public prototype_ `SLATE_ARGUMENT(FNeuralMorphEditorModel*, EditorModel) SLATE_ARGUMENT(TSharedPtr<UE::MLDeformer::SMLDeformerInputWidget>, InputWidget) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L85 _public prototype_ `void BindCommands(TSharedPtr<FUICommandList> CommandList);`
- L86 _public prototype_ `void Refresh(bool bBroadcastPropertyChanged=false);`
- L88 _public prototype_ `FText GetSectionTitle() const;`
- L89 _public prototype_ `int32 GetNumSelectedGroups() const;`
- L90 _public prototype_ `TSharedPtr<UE::MLDeformer::SMLDeformerInputWidget> GetInputWidget() const;`
- L93 _private prototype_ `void AddElement(TSharedPtr<FNeuralMorphCurveGroupsTreeElement> Element, TSharedPtr<FNeuralMorphCurveGroupsTreeElement> ParentElement);`
- L94 _private prototype_ `void HandleGetChildrenForTree(TSharedPtr<FNeuralMorphCurveGroupsTreeElement> InItem, TArray<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>>& OutChildren);`
- L95 _private prototype_ `void OnSelectionChanged(TSharedPtr<FNeuralMorphCurveGroupsTreeElement> Selection, ESelectInfo::Type SelectInfo);`
- L96 _private prototype_ `const TArray<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>>& GetRootElements() const;`
- L97 _private prototype_ `virtual FReply OnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;`
- L98 _private prototype_ `TSharedRef<ITableRow> MakeTableRowWidget(TSharedPtr<FNeuralMorphCurveGroupsTreeElement> InItem, const TSharedRef<STableViewBase>& OwnerTable);`
- L99 _private prototype_ `TSharedPtr<SWidget> CreateContextMenuWidget() const;`
- L101 _private prototype_ `void UpdateTreeElements();`
- L102 _private prototype_ `void RefreshTree(bool bBroadcastPropertyChanged);`
- L103 _private prototype_ `bool BroadcastModelPropertyChanged(const FName PropertyName);`
- L104 _private prototype_ `TSharedPtr<SWidget> CreateContextWidget() const;`
- L106 _private prototype_ `void OnCopyCurveGroups() const;`
- L107 _private prototype_ `void OnPasteCurveGroups();`
- L109 _private prototype_ `void OnCreateCurveGroup();`
- L110 _private prototype_ `void OnDeleteSelectedItems();`
- L111 _private prototype_ `void OnClearCurveGroups();`
- L112 _private prototype_ `void OnAddCurveToGroup();`
- L115 _private member_ `TArray<TSharedPtr<FNeuralMorphCurveGroupsTreeElement>> RootElements;`
- L116 _private member_ `TSharedPtr<UE::MLDeformer::SMLDeformerInputWidget> InputWidget;`
- L117 _private member_ `FNeuralMorphEditorModel* EditorModel = nullptr;`
- L118 _private member_ `FText SectionTitle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API NEURALMORPHMODELEDITOR_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace MLDeformer` (scope `UE`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace NeuralMorphModel` (scope `UE`)

### `Plugins/Animation/MLDeformer/NeuralMorphModel/Source/NeuralMorphModelEditor/Public/SNeuralMorphInputWidget.h` (Public)


#### class `UE::NeuralMorphModel::FNeuralMorphInputWidgetCommands`  
`class FNeuralMorphInputWidgetCommands : public TCommands<FNeuralMorphInputWidgetCommands>`  
_L29-47_
- inherits: `TCommands<FNeuralMorphInputWidgetCommands>`
- L33 _public prototype_ `FNeuralMorphInputWidgetCommands();`
- L34 _public prototype_ `virtual void RegisterCommands() override;`
- L37 _public member_ `TSharedPtr<FUICommandInfo> ResetAllBoneMasks;`
- L38 _public member_ `TSharedPtr<FUICommandInfo> ResetSelectedBoneMasks;`
- L39 _public member_ `TSharedPtr<FUICommandInfo> ExpandSelectedBoneMasks;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> ResetAllBoneGroupMasks;`
- L42 _public member_ `TSharedPtr<FUICommandInfo> ResetSelectedBoneGroupMasks;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> ExpandSelectedBoneGroupMasks;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> ConfigureBoneMask;`
- L46 _public member_ `TSharedPtr<FUICommandInfo> ConfigureBoneGroupMask;`

#### class `UE::NeuralMorphModel::SNeuralMorphInputWidget`  
`class SNeuralMorphInputWidget : public UE::MLDeformer::SMLDeformerInputWidget`  
_L50-113_
- inherits: `UE::MLDeformer::SMLDeformerInputWidget`
- L54 _public function_ `SLATE_BEGIN_ARGS(SNeuralMorphInputWidget)`
- L55 _public prototype_ `SLATE_ARGUMENT(UE::MLDeformer::FMLDeformerEditorModel*, EditorModel) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L61 _public prototype_ `virtual void Refresh() override;` — SMLDeformerInputWidget overrides.
- L62 _public prototype_ `virtual void AddInputBonesMenuItems(FMenuBuilder& MenuBuilder) override;`
- L63 _public prototype_ `virtual void AddInputBonesPlusIconMenuItems(FMenuBuilder& MenuBuilder) override;`
- L64 _public prototype_ `virtual void OnAddInputBones(const TArray<FName>& Names) override;`
- L65 _public prototype_ `virtual void OnAddInputCurves(const TArray<FName>& Names) override;`
- L66 _public prototype_ `virtual void OnAddAnimatedBones() override;`
- L67 _public prototype_ `virtual void OnClearInputBones() override;`
- L68 _public prototype_ `virtual void OnDeleteInputBones(const TArray<FName>& Names) override;`
- L69 _public prototype_ `virtual void OnDeleteInputCurves(const TArray<FName>& Names) override;`
- L70 _public prototype_ `virtual void OnSelectInputBone(FName BoneName) override;`
- L71 _public prototype_ `virtual void OnSelectInputCurve(FName BoneName) override;`
- L72 _public prototype_ `virtual void OnAddAnimatedCurves() override;`
- L73 _public prototype_ `virtual void ClearSelectionForAllWidgetsExceptThis(TSharedPtr<SWidget> ExceptThisWidget) override;`
- L74 _public prototype_ `virtual TSharedPtr<SWidget> GetExtraBonePickerWidget() override;`
- L77 _public prototype_ `void AddInputBoneGroupsMenuItems(FMenuBuilder& MenuBuilder);`
- L78 _public prototype_ `void AddInputBoneGroupsPlusIconMenuItems(FMenuBuilder& MenuBuilder);`
- L80 _public prototype_ `void OnSelectInputBoneGroup(TSharedPtr<FNeuralMorphBoneGroupsTreeElement> Element);`
- L81 _public prototype_ `void OnSelectInputCurveGroup(TSharedPtr<FNeuralMorphCurveGroupsTreeElement> Element);`
- L83 _public function_ `TSharedPtr<FUICommandList> GetBoneGroupsCommandList() const`
- L84 _public function_ `TSharedPtr<FUICommandList> GetCurveGroupsCommandList() const`
- L86 _public function_ `int32 GetHierarchyDepth() const`
- L89 _protected prototype_ `void CreateBoneGroupsSection();`
- L90 _protected prototype_ `void CreateCurveGroupsSection();`
- L92 _protected prototype_ `void ResetAllBoneMasks();`
- L93 _protected prototype_ `void ResetSelectedBoneMasks();`
- L94 _protected prototype_ `void ExpandBoneMasks();`
- L96 _protected prototype_ `void ResetAllBoneGroupMasks();`
- L97 _protected prototype_ `void ResetSelectedBoneGroupMasks();`
- L98 _protected prototype_ `void ExpandBoneGroupMasks();`
- L100 _protected prototype_ `void ConfigureBoneMask();`
- L101 _protected prototype_ `void ConfigureBoneGroupMask();`
- L103 _protected prototype_ `void BindCommands();`
- L104 _protected prototype_ `FReply ShowBoneGroupsManageContextMenu();`
- L105 _protected prototype_ `FReply ShowCurveGroupsManageContextMenu();`
- L108 _protected member_ `TSharedPtr<SNeuralMorphBoneGroupsWidget> BoneGroupsWidget;`
- L109 _protected member_ `TSharedPtr<SNeuralMorphCurveGroupsWidget> CurveGroupsWidget;`
- L110 _protected member_ `TSharedPtr<FUICommandList> BoneGroupsCommandList;`
- L111 _protected member_ `TSharedPtr<FUICommandList> CurveGroupsCommandList;`
- L112 _protected member_ `int32 HierarchyDepth = 2;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API NEURALMORPHMODELEDITOR_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace MLDeformer` (scope `UE`)
- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace NeuralMorphModel` (scope `UE`)
