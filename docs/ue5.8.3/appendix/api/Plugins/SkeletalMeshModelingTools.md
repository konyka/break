# Plugins / SkeletalMeshModelingTools

- module root: `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools`
- headers: 30; symbols: 1055
- symbol kinds: class=57, delegate=6, enum=7, enumerator=17, function=47, macro=6, member=297, namespace=18, prototype=582, struct=15, typedef=3
- PrivateDependencyModuleNames: AnimationCore, AnimationWidgets, ApplicationCore, CommonMenuExtensions, ContentBrowser, Core, CoreUObject, DetailCustomizations, DeveloperSettings, DynamicMesh, EditorFramework, EditorInteractiveToolsFramework, EditorWidgets, Engine, GeometryCore, GeometryFramework, GeometryScriptingEditor, InputCore, InteractiveToolsFramework, InterchangeEngine, MeshConversion, MeshDescription, MeshModelingTools, MeshModelingToolsEditorOnly, MeshModelingToolsEditorOnlyExp, MeshModelingToolsExp, ModelingComponents, ModelingComponentsEditorOnly, ModelingToolsEditorMode, Persona, Projects, PropertyEditor, SkeletalMeshDescription, SkeletalMeshEditor, SkeletalMeshModifiers, SkeletalMeshUtilitiesCommon, Slate, SlateCore, StaticMeshDescription, StatusBar, ToolMenus, ToolWidgets, UnrealEd, WidgetRegistration

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/Components/SKMBackedDynaMeshComponent.h` (Private)


#### class `USkeletalMeshBackedDynamicMeshComponent`  
`class USkeletalMeshBackedDynamicMeshComponent : public UDynamicMeshComponent`  
_L29-253_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDynamicMeshComponent`
- L78 _public prototype_ `EMeshLODIdentifier Init(USkeletalMesh* InSkeletalMesh, EMeshLODIdentifier InLOD);`
- L79 _public prototype_ `EMeshLODIdentifier GetLOD() const;`
- L80 _public prototype_ `bool CommitToSkeletalMesh();`
- L82 _public prototype_ `void DiscardChanges();`
- L84 _public prototype_ `void MarkDirty();`
- L85 _public prototype_ `void MarkBaseGeometryDirty();`
- L86 _public prototype_ `void HandleSkeletonChange(USkeletonModifier* InModifier);`
- L87 _public prototype_ `void ForwardVisibilityChangeRequest(bool bInVisible);`
- L89 _public prototype_ `void HandleGeometryUpdate( const FName EditingMorphTargetName, const FDynamicMesh3& PosedMesh, const TArray<FMatrix>& BoneMatrices, const TMap<FName, float>& MorphTargetWeights, const UE::Geometry::FDynamicSubmesh3* InSubmesh = nullptr );`
- L97 _public prototype_ `FName AddMorphTarget(FName InName);`
- L98 _public prototype_ `TArray<FName> AddMorphTargetsIfMissing(const TArray<FName>& Names);`
- L99 _public prototype_ `FName RenameMorphTarget(FName InOldName, FName InNewName);`
- L100 _public prototype_ `void RemoveMorphTargets(const TArray<FName>& InNames);`
- L101 _public prototype_ `TArray<FName> DuplicateMorphTargets(const TArray<FName>& InNames);`
- L102 _public prototype_ `void MirrorMorphTargets(const TArray<FName>& InNames);`
- L103 _public prototype_ `void FlipMorphTargets(const TArray<FName>& InNames);`
- L104 _public prototype_ `FName MergeMorphTargets(const TArray<FName>& InNames);`
- L105 _public prototype_ `void ApplyWeightToMorphTarget(FName InName, float InWeight);`
- L106 _public prototype_ `void GenerateFlippedMorphTargets(const TArray<TPair<FName, FName>>& InPairs);`
- L108 _public prototype_ `void MarkMorphTargetEdited(FName InName);`
- L110 _public function_ `const FSkeletonChangeTracker& GetSkeletonChangeTracker() const`
- L111 _public function_ `const FMorphTargetChangeTracker& GetMorphTargetChangeTracker() const`
- L112 _public function_ `const FReferenceSkeleton& GetRefSkeleton() const`
- L113 _public function_ `const TArray<FTransform>& GetComponentSpaceBoneTransformsRefPose() const`
- L115 _public prototype_ `bool IsSkeletonDirty() const;`
- L116 _public prototype_ `bool IsDirty() const;`
- L117 _public prototype_ `int32 GetChangeCount() const;`
- L120 _public prototype_ `USkeletalMesh* GetSkeletalMesh() const;`
- L122 _public prototype_ `const UE::Geometry::FGroupTopology& GetGroupTopology();`
- L125 _public prototype_ `const UE::Geometry::FMeshPlanarSymmetry* GetBaseMeshSymmetry();` — Lazily rebuilds when base geometry changes; pointer is invalidated by such edits.
- L127 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestingVisibilityChange, bool);`
- L128 _public function_ `FOnRequestingVisibilityChange& GetOnRequestingVisibilityChange()`
- L133 _public function_ `bool IsExpectingAssetChange() const` — Set before expected asset changes (commit, undo/redo of commit). Checked for re-entrancy in CommitToSkeletalMesh. Checked and cleared by HandleSkeletalMeshChanged to distinguish our own changes from external ones.
- L134 _public function_ `void ClearExpectAssetChange()`
- L136 _public prototype_ `void FlushPendingEvents();`
- L137 _public function_ `FSimpleMulticastDelegate& OnChanged()`
- L138 _public function_ `FSimpleMulticastDelegate& OnSkeletonChanged()`
- L140 _public prototype_ `virtual void BeginDestroy() override;`
- L142 _protected prototype_ `void ResetTrackersDirect();`
- L143 _protected prototype_ `FName GetAvailableMorphTargetName(FName InNewName, FName InOldName = NAME_None) const;`
- L144 _protected prototype_ `EMeshLODIdentifier GetValidEditingLOD(EMeshLODIdentifier InLOD) const;`
- L149 _protected prototype_ `FName AddMorphTargetDirect(FDynamicMesh3& Mesh, FName InName);` — Direct mesh-mutation primitives. Caller is responsible for opening FChangeScope, running EditMesh once for the whole batch, and calling MarkDirtyDirect afterwards. Trackers are updated here so subsequent Direct calls in the same batch see the new state.
- L150 _protected prototype_ `FName RenameMorphTargetDirect(FDynamicMesh3& Mesh, FName InOldName, FName InNewName);`
- L151 _protected prototype_ `void RemoveMorphTargetsDirect(FDynamicMesh3& Mesh, const TArray<FName>& InNames);`
- L152 _protected prototype_ `TArray<FName> DuplicateMorphTargetsDirect(FDynamicMesh3& Mesh, const TArray<FName>& InNames);`
- L153 _protected prototype_ `void MirrorMorphTargetsDirect(FDynamicMesh3& Mesh, const TArray<FName>& InNames);`
- L154 _protected prototype_ `void FlipMorphTargetsDirect(FDynamicMesh3& Mesh, const TArray<FName>& InNames);`
- L155 _protected prototype_ `FName MergeMorphTargetsDirect(FDynamicMesh3& Mesh, const TArray<FName>& InNames);`
- L156 _protected prototype_ `void ApplyWeightToMorphTargetDirect(FDynamicMesh3& Mesh, FName InName, float InWeight);`
- L158 _protected prototype_ `TSharedPtr<FDynamicMesh3> GetMeshCopy();`
- L159 _protected prototype_ `void MarkDirtyDirect();`
- L160 _protected prototype_ `void MarkBaseGeometryDirtyDirect();`
- L176 _protected member_ `FTrackers Trackers;`
- L178 _protected member_ `TWeakObjectPtr<USkeletalMesh> WeakSkeletalMesh;`
- L179 _protected member_ `EMeshLODIdentifier LOD = EMeshLODIdentifier::LOD0;`
- L180 _protected member_ `int32 LODIndex = 0;`
- L182 _protected member_ `bool bExpectAssetChange = false;`
- L184 _protected member_ `bool bPendingChangeEvent = false;`
- L185 _protected member_ `FSimpleMulticastDelegate OnChangedEvent;`
- L186 _protected member_ `bool bPendingSkeletonChangeEvent = false;`
- L187 _protected member_ `FSimpleMulticastDelegate OnSkeletonChangedEvent;`
- L189 _protected member_ `FOnRequestingVisibilityChange OnRequestingVisibilityChangeDelegate;`
- L194 _protected prototype_ `void OnTransactionStateChanged(const FTransactionContext& Context, ETransactionStateEventType EventType);` — Fires pending change events when the containing transaction settles (forward commit, undo/redo replay, or cancel). Replaces the previous Tick-driven flush so observers see a coherent post-transaction state before subsequent code reads it.
- L195 _protected member_ `FDelegateHandle TransactionStateChangedHandle;`
- L245 _protected member_ `TPimplPtr<UE::Geometry::FMeshPlanarSymmetry> ReadOnlySymmetry;` — Query only symmetry, not allow to modify mesh
- L246 _protected member_ `int32 BaseGeometryVersionForCurrentSymmetry = -1;`
- L247 _protected prototype_ `void UpdateSymmetryIfNeeded();`
- L250 _protected member_ `TPimplPtr<UE::Geometry::FGroupTopology> CachedGroupTopology;` — Cached group topology, lazily built and invalidated when base geometry changes
- L251 _protected member_ `int32 BaseGeometryVersionForCurrentGroupTopology = -1;`
- L252 _protected prototype_ `void UpdateGroupTopologyIfNeeded();`

#### struct `USkeletalMeshBackedDynamicMeshComponent::FSkeletonChangeTracker`  
`struct FSkeletonChangeTracker`  
_L35-47_
- L37 _public prototype_ `void Init(int32 NumBones);`
- L38 _public prototype_ `void HandleSkeletonChanged(const TArray<int32> ToolBoneIndexTracker);`
- L39 _public prototype_ `int32 GetChangeCount() const;`
- L40 _public prototype_ `const TArray<int32>& GetBoneIndexTracker() const;`
- L44 _private member_ `TArray<int32> BoneIndexTracker;` — Used to update retarget settings
- L46 _private member_ `int32 ChangeCount = 0;`

#### struct `USkeletalMeshBackedDynamicMeshComponent::FMorphTargetChangeTracker`  
`struct FMorphTargetChangeTracker`  
_L49-75_
- L51 _public prototype_ `void Init(const TArray<FName> ExistingMorphTargets);`
- L52 _public prototype_ `void HandleRenameMorphTarget(FName CurrentName, FName NewName);`
- L53 _public prototype_ `void HandleRemoveMorphTarget(FName Name);`
- L54 _public prototype_ `void HandleAddMorphTarget(FName Name);`
- L55 _public prototype_ `void HandleEditMorphTarget(FName Name);`
- L56 _public prototype_ `FName GetCurrentMorphTargetName(FName OriginalName) const;`
- L57 _public prototype_ `FName GetOriginalMorphTargetName(FName CurrentName) const;`
- L58 _public prototype_ `const TSet<FName>& GetEditedMorphTargets() const;`
- L64 _public prototype_ `TArray<FNameInfo> GetCurvesToRename() const;`
- L65 _public prototype_ `TArray<FName> GetCurvesToRemove() const;`
- L66 _public prototype_ `TArray<FName> GetCurvesToAdd() const;`
- L68 _public prototype_ `TArray<FName> GetCurrentMorphTargetNames() const;`
- L71 _private member_ `TMap<FName, FName> OriginalNameToCurrentName;`
- L72 _private member_ `TMap<FName, FName> CurrentNameToOriginalName;`
- L73 _private member_ `TSet<FName> EditedMorphTargets;`

#### struct `USkeletalMeshBackedDynamicMeshComponent::FMorphTargetChangeTracker::FNameInfo`  
`struct FNameInfo`  
_L59-63_
- L61 _public member_ `FName OldName;`
- L62 _public member_ `FName NewName;`

#### struct `USkeletalMeshBackedDynamicMeshComponent::FTrackers`  
`struct FTrackers`  
_L162-174_
- L164 _public member_ `TSharedPtr<FDynamicMesh3> InitialAssetMesh;`
- L166 _public member_ `int32 ChangeCount = 0;`
- L168 _public member_ `int32 BaseGeometryChangeCount = 0;` — Base Geometry determines if symmetry tracking needs to be updated
- L170 _public member_ `FReferenceSkeleton RefSkeleton;`
- L171 _public member_ `TArray<FTransform> ComponentSpaceBoneTransformsRefPose;`
- L172 _public member_ `FSkeletonChangeTracker SkeletonChangeTracker;`
- L173 _public member_ `FMorphTargetChangeTracker MorphTargetChangeTracker;`

#### class `USkeletalMeshBackedDynamicMeshComponent::FTrackerChange`  
`class FTrackerChange : public FToolCommandChange`  
_L197-211_
- inherits: `FToolCommandChange`
- L200 _public member_ `FTrackers OldTrackers;`
- L201 _public member_ `FTrackers NewTrackers;`
- L202 _public member_ `bool bIsCommitChange = false;`
- L203 _public prototype_ `FTrackerChange(USkeletalMeshBackedDynamicMeshComponent* InComponent);`
- L204 _public prototype_ `virtual FString ToString() const override;`
- L205 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L206 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L207 _public prototype_ `void Close(USkeletalMeshBackedDynamicMeshComponent* InComponent);`
- L209 _public prototype_ `bool ShouldEnqueueMeshChangedEvent() const;`
- L210 _public prototype_ `bool ShouldEnqueueSkeletonChangedEvent() const;`

#### class `USkeletalMeshBackedDynamicMeshComponent::FChangeScope`  
`class FChangeScope`  
_L214-231_
- desc: Records into current Transaction if there is one
- L217 _public prototype_ `FChangeScope(USkeletalMeshBackedDynamicMeshComponent* InComponent, bool bInRecordMeshChange = true);`
- L218 _public prototype_ `~FChangeScope();`
- L220 _public prototype_ `void MarkAsCommitChange();`
- L223 _private member_ `TUniquePtr<FTrackerChange> TrackerChange;`
- L224 _private member_ `TSharedPtr<FDynamicMesh3> OldMesh;`
- L225 _private member_ `TSharedPtr<FDynamicMesh3> NewMesh;`
- L227 _private member_ `USkeletalMeshBackedDynamicMeshComponent* Component = nullptr;`
- L228 _private member_ `bool bRecordMeshChange = false;`

#### class `USkeletalMeshBackedDynamicMeshComponent::FTrackerChangeScope`  
`class FTrackerChangeScope : public FChangeScope`  
_L233-237_
- inherits: `FChangeScope`
- L236 _public function_ `FTrackerChangeScope(USkeletalMeshBackedDynamicMeshComponent* InComponent) : FChangeScope(InComponent, false)`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SKELETALMESHMODELINGTOOLS_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)
- L127 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRequestingVisibilityChange, bool);`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/DetailCustomization/SKMMTMirroringPropertiesAxisCustomization.h` (Private)


#### class `UE::SkeletalMeshModelingTools::FSKMMTMirroringPropertiesAxisCustomization`  
`class FSKMMTMirroringPropertiesAxisCustomization : public IPropertyTypeCustomization`  
_L10-22_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for EAxis in the Skeletal Mesh editor
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L19 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SkeletalMeshModelingTools` (scope `UE`)

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/DetailCustomization/SKMMTOrientPropertiesAxisCustomization.h` (Private)


#### class `UE::SkeletalMeshModelingTools::FSKMMTOrientPropertiesAxisCustomization`  
`class FSKMMTOrientPropertiesAxisCustomization : public IPropertyTypeCustomization`  
_L10-22_
- inherits: `IPropertyTypeCustomization`
- desc: Property type customization for EAxis in the Skeletal Mesh editor
- L15 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Creates an instance of this property type customization
- L19 _private prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L20 _private prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace SkeletalMeshModelingTools` (scope `UE`)

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/DetailCustomization/SkeletonEditingToolPropertyCustomizations.h` (Private)


#### class `FSkeletonEditingToolDetailCustomization`  
`class FSkeletonEditingToolDetailCustomization : public IDetailCustomization`  
_L16-26_
- inherits: `IDetailCustomization`
- L19 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L20 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L22 _private prototype_ `void CustomizeEditAction(IDetailCategoryBuilder& InActionCategory) const;`
- L23 _private prototype_ `void CustomizeComponentSelection(IDetailLayoutBuilder& DetailBuilder) const;`
- L25 _private member_ `TWeakObjectPtr<USkeletonEditingTool> Tool = nullptr;`

#### class `ISkeletonEditingPropertiesDetailCustomization`  
`class ISkeletonEditingPropertiesDetailCustomization : public IDetailCustomization`  
_L32-66_
- inherits: `IDetailCustomization`
- L36 _protected function_ `template< typename T > static TWeakObjectPtr<T> GetCustomizedObject(const IDetailLayoutBuilder& InDetailBuilder)`
- L48 _protected function_ `template<typename TProperty> TWeakObjectPtr<USkeletonEditingTool> GetParentTool(const TWeakObjectPtr<TProperty>& InProperties)`
- L54 _protected prototype_ `TAttribute<EVisibility> GetCreationVisibility() const;`
- L55 _protected prototype_ `TAttribute<EVisibility> GetEditionVisibility() const;`
- L56 _protected prototype_ `TAttribute<bool> IsEnabledBySelection() const;`
- L58 _protected prototype_ `void UpdateProperties( IDetailLayoutBuilder& InDetailBuilder, const TAttribute<EVisibility>& InVisibility, const TAttribute<bool>& InEnabled = TAttribute<bool>()) const;`
- L63 _protected prototype_ `virtual const TArray<FName>& GetProperties() const = 0;`
- L65 _protected member_ `TWeakObjectPtr<USkeletonEditingTool> Tool;`

#### class `FSkeletonEditingPropertiesDetailCustomization`  
`class FSkeletonEditingPropertiesDetailCustomization : public ISkeletonEditingPropertiesDetailCustomization`  
_L72-88_
- inherits: `ISkeletonEditingPropertiesDetailCustomization`
- L75 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L76 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L79 _protected prototype_ `virtual const TArray<FName>& GetProperties() const override;`
- L82 _private prototype_ `void CustomizeValueGet(SAdvancedTransformInputBox<FTransform>::FArguments& InOutArgs);`
- L83 _private prototype_ `void CustomizeValueSet(SAdvancedTransformInputBox<FTransform>::FArguments& InOutArgs);`
- L84 _private prototype_ `void CustomizeClipboard(SAdvancedTransformInputBox<FTransform>::FArguments& InOutArgs);`
- L86 _private member_ `TUniquePtr<SkeletonEditingTool::FRefSkeletonChange> ActiveChange;`
- L87 _private member_ `TBitArray<> RelativeArray;`

#### class `FMirroringPropertiesDetailCustomization`  
`class FMirroringPropertiesDetailCustomization : public ISkeletonEditingPropertiesDetailCustomization`  
_L94-102_
- inherits: `ISkeletonEditingPropertiesDetailCustomization`
- L97 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L98 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L101 _protected prototype_ `virtual const TArray<FName>& GetProperties() const override;`

#### class `FOrientingPropertiesDetailCustomization`  
`class FOrientingPropertiesDetailCustomization : public ISkeletonEditingPropertiesDetailCustomization`  
_L108-116_
- inherits: `ISkeletonEditingPropertiesDetailCustomization`
- L111 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L112 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L115 _protected prototype_ `virtual const TArray<FName>& GetProperties() const override;`

#### class `FProjectionPropertiesDetailCustomization`  
`class FProjectionPropertiesDetailCustomization : public ISkeletonEditingPropertiesDetailCustomization`  
_L122-130_
- inherits: `ISkeletonEditingPropertiesDetailCustomization`
- L125 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L126 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L129 _protected prototype_ `virtual const TArray<FName>& GetProperties() const override;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/DetailCustomization/SkinWeightDetailCustomization.h` (Private)


#### class `FSkinWeightDetailCustomization`  
`class FSkinWeightDetailCustomization : public IDetailCustomization`  
_L15-48_
- inherits: `IDetailCustomization`
- L21 _public function_ `static TSharedRef<IDetailCustomization> MakeInstance()`
- L27 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface
- L29 _public function_ `void OnSelectionChanged()`
- L36 _private prototype_ `void AddBrushUI(IDetailLayoutBuilder& DetailBuilder) const;`
- L37 _private prototype_ `void AddSelectionUI(IDetailLayoutBuilder& DetailBuilder) const;`
- L38 _private prototype_ `void AddTransferUI(IDetailLayoutBuilder& DetailBuilder) const;`
- L40 _private member_ `IDetailLayoutBuilder* CurrentDetailBuilder = nullptr;`
- L41 _private member_ `TWeakObjectPtr<USkinWeightsPaintToolProperties> ToolSettings;`
- L42 _private member_ `TWeakObjectPtr<USkinWeightsPaintTool> Tool;`
- L44 _private member_ `static float WeightSliderWidths;`
- L45 _private member_ `static float WeightEditingLabelsPercent;`
- L46 _private member_ `static float WeightEditVerticalPadding;`
- L47 _private member_ `static float WeightEditHorizontalPadding;`

#### struct `FWeightEditorElement`  
`struct FWeightEditorElement`  
_L50-55_
- L52 _public member_ `int32 BoneIndex;`
- L54 _public function_ `FWeightEditorElement(int32 InBoneIndex) : BoneIndex(InBoneIndex)`

#### class `SVertexWeightItem`  
`class SVertexWeightItem : public SMultiColumnTableRow<TSharedPtr<FWeightEditorElement>>`  
_L58-79_
- inherits: `SMultiColumnTableRow<TSharedPtr<FWeightEditorElement>>`
- L62 _public function_ `SLATE_BEGIN_ARGS(SVertexWeightItem)`
- L63 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FWeightEditorElement>, Element) SLATE_ARGUMENT(TSharedPtr<SVertexWeightEditor>, ParentTable) SLATE_END_ARGS() virtual ~SVertexWeightItem() override = default;`
- L69 _public prototype_ `void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& OwnerTableView);`
- L71 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName) override;`
- L74 _private member_ `TSharedPtr<FWeightEditorElement> Element;`
- L75 _private member_ `TSharedPtr<SVertexWeightEditor> ParentTable;`
- L76 _private member_ `bool bInTransaction = false;`
- L77 _private member_ `float ValueAtStartOfSlide;`
- L78 _private member_ `float ValueDuringSlide;`

#### class `SVertexWeightEditor`  
`class SVertexWeightEditor : public SCompoundWidget`  
_L83-105_
- inherits: `SCompoundWidget`
- L86 _public function_ `SLATE_BEGIN_ARGS(SVertexWeightEditor)`
- L87 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, USkinWeightsPaintTool* InSkinTool);`
- L93 _public prototype_ `void RefreshView();`
- L97 _private prototype_ `void OnSelectionChanged(TSharedPtr<FWeightEditorElement> Selection, ESelectInfo::Type SelectInfo);` — Called when the selection in this editor changed
- L100 _private member_ `TSharedPtr<SWeightEditorListViewType> ListView;` — the vertex weight list view
- L101 _private member_ `TArray< TSharedPtr<FWeightEditorElement> > ListViewItems;`
- L102 _private member_ `TWeakObjectPtr<USkinWeightsPaintTool> Tool;`

#### Free symbols / members of external scopes

- L81 _typedef_ `typedef SListView< TSharedPtr<FWeightEditorElement> > SWeightEditorListViewType;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/Interfaces/ISKMBackedDynaMeshComponentProvider.h` (Private)


#### class `USkeletalMeshBackedDynamicMeshComponentProvider`  
`class USkeletalMeshBackedDynamicMeshComponentProvider : public UInterface`  
_L12-16_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ISkeletalMeshBackedDynamicMeshComponentProvider`  
`class ISkeletalMeshBackedDynamicMeshComponentProvider`  
_L19-25_
- L24 _public prototype_ `virtual USkeletalMeshBackedDynamicMeshComponent* GetComponent(UObject* SourceObject) = 0;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/MorphTargetManagerDataSource.h` (Private)


#### class `UMorphTargetManagerDataSource`  
`class UMorphTargetManagerDataSource : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IMorphTargetManagerDataSource`  
`class IMorphTargetManagerDataSource`  
_L15-43_
- L20 _public prototype_ `virtual TArray<FName> GetMorphTargets() = 0;`
- L22 _public prototype_ `virtual float GetMorphTargetWeight(FName MorphTarget) = 0;`
- L23 _public prototype_ `virtual void SetMorphTargetWeight(FName MorphTarget, float Weight) = 0;`
- L25 _public prototype_ `virtual bool GetMorphTargetAutoFill(FName MorphTarget) = 0;`
- L26 _public prototype_ `virtual void SetMorphTargetAutoFill(FName MorphTarget, bool bAutoFill, float PreviousOverrideWeight) = 0;`
- L28 _public prototype_ `virtual FName GetEditingMorphTarget() const = 0;`
- L29 _public prototype_ `virtual void SetEditingMorphTarget(FName MorphTarget) = 0;`
- L31 _public prototype_ `virtual FName AddMorphTarget(FName InName) = 0;`
- L32 _public prototype_ `virtual TArray<FName> AddMorphTargetsIfMissing(const TArray<FName>& Names) = 0;`
- L33 _public prototype_ `virtual FName RenameMorphTarget(FName OldName, FName NewName) = 0;`
- L34 _public prototype_ `virtual void RemoveMorphTargets(const TArray<FName>& Names) = 0;`
- L35 _public prototype_ `virtual TArray<FName> DuplicateMorphTargets(const TArray<FName>& Names) = 0;`
- L36 _public prototype_ `virtual void MirrorMorphTargets(const TArray<FName>& Names) = 0;`
- L37 _public prototype_ `virtual void FlipMorphTargets(const TArray<FName>& Names) = 0;`
- L38 _public prototype_ `virtual FName MergeMorphTargets(const TArray<FName>& Names) = 0;`
- L39 _public prototype_ `virtual void ApplyCurrentWeightToMorphTarget(FName Name) = 0;`
- L40 _public prototype_ `virtual void GenerateFlippedMorphTargets(const TArray<TPair<FName, FName>>& InPairs) = 0;`
- L42 _public prototype_ `virtual FSimpleMulticastDelegate& OnMorphTargetDataChanged() = 0;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SMorphTargetManager.h` (Private)


#### class `UMorphTargetManagerAddMissingMorphsSetting`  
`class UMorphTargetManagerAddMissingMorphsSetting : public UObject`  
_L31-39_
- reflection: `UCLASS(Transient)`
- inherits: `UObject`
- desc: Transient settings displayed in the "Add Empty Morph Targets From Template" modal dialog.
- L38 _public member_ `TObjectPtr<USkeletalMesh> SourceSkeletalMesh = nullptr;` — `UPROPERTY(EditAnywhere, Category = "Template", meta = (DisplayName = "Template Skeletal Mesh"))` — Template Skeletal Mesh to read Morph Target names from. Only the names are read — no delta data is transferred.

#### class `SMorphTargetManager`  
`class SMorphTargetManager : public SCompoundWidget`  
_L43-147_
- inherits: `SCompoundWidget`
- L55 _public function_ `SLATE_BEGIN_ARGS( SMorphTargetManager )`
- L56 _public prototype_ `SLATE_ARGUMENT(TWeakInterfacePtr<IMorphTargetManagerDataSource>, DataSource) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L65 _public prototype_ `virtual ~SMorphTargetManager();` — Destructor - resets the morph targets
- L67 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L68 _public prototype_ `void BindCommands();`
- L69 _public prototype_ `void RefreshList();`
- L70 _public prototype_ `void SelectMorphTargets(const TArray<FName>& MorphTargets);`
- L72 _public prototype_ `TSharedRef<SWidget> CreateNewMenuWidget();`
- L73 _public prototype_ `TSharedRef<SWidget> CreateSortMenuWidget();`
- L74 _public prototype_ `void SetSortMode(ESortMode NewMode);`
- L75 _public function_ `bool IsSortMode(ESortMode Mode) const`
- L76 _public prototype_ `TSharedRef<SWidget> CreateFilterOptionsMenuWidget();`
- L77 _public prototype_ `void ToggleInvertFilter();`
- L78 _public function_ `bool IsInvertFilterEnabled() const`
- L79 _public prototype_ `void ToggleDisableFilter();`
- L80 _public function_ `bool IsDisableFilterEnabled() const`
- L81 _public prototype_ `void OnFilterTextChanged(const FText& Text);`
- L82 _public prototype_ `FText GetFilterText() const;`
- L83 _public prototype_ `FText GetHighlightText(FText InName) const;`
- L85 _public prototype_ `TSharedRef<class ITableRow> GenerateMorphTargetRow(FMorphTargetInfoPtr MorphTargetItem, const TSharedRef<STableViewBase>& TableViewBase);`
- L86 _public prototype_ `TSharedPtr<SWidget> OnGetContextMenuContent();`
- L87 _public prototype_ `void OnItemScrolledIntoView(FMorphTargetInfoPtr InItem, const TSharedPtr<ITableRow>& InTableRow);`
- L89 _public prototype_ `void SetMorphTargetWeight(FName MorphTarget, float Weight);`
- L90 _public prototype_ `float GetMorphTargetWeight(FName MorphTarget);`
- L91 _public prototype_ `void SetMorphTargetAutoFill(FName MorphTarget, bool bAutoFill, float PreviousOverrideWeight);`
- L92 _public prototype_ `bool GetMorphTargetAutoFill(FName MorphTarget);`
- L93 _public prototype_ `void SetEditingMorphTarget(FName MorphTarget);`
- L94 _public prototype_ `bool IsEditingMorphTarget(FName MorphTarget);`
- L96 _public prototype_ `void AddMorphTarget();`
- L97 _public prototype_ `void OpenAddMissingMorphTargetsDialog();`
- L98 _public prototype_ `void AddMissingMorphTargetsFromSkeletalMesh(USkeletalMesh* SourceMesh);`
- L99 _public prototype_ `FName RenameMorphTarget(FName InOldName, FName InNewName);`
- L100 _public prototype_ `void OnDoubleClickMorphTarget(FMorphTargetInfoPtr Item);`
- L102 _protected prototype_ `void RenameSelectedMorphTarget();`
- L103 _protected prototype_ `bool CanRename();`
- L104 _protected prototype_ `void RemoveSelectedMorphTargets();`
- L105 _protected prototype_ `bool CanRemove();`
- L106 _protected prototype_ `void DuplicateSelectedMorphTargets();`
- L107 _protected prototype_ `bool CanDuplicate();`
- L108 _protected prototype_ `void MirrorSelectedMorphTargets();`
- L109 _protected prototype_ `bool CanMirror();`
- L110 _protected prototype_ `void FlipSelectedMorphTargets();`
- L111 _protected prototype_ `bool CanFlip();`
- L112 _protected prototype_ `void MergeSelectedMorphTargets();`
- L113 _protected prototype_ `bool CanMerge();`
- L114 _protected prototype_ `void ApplyCurrentWeightToSelectedMorphTarget();`
- L115 _protected prototype_ `bool CanApplyCurrentWeight();`
- L116 _protected prototype_ `void ToggleSelectedMorphTargetsWeight();`
- L117 _protected prototype_ `bool CanToggleSelectedMorphTargetsWeight();`
- L118 _protected prototype_ `void OpenConfigureNamingConventionDialog();`
- L119 _protected prototype_ `void GenerateFlippedMorphTargetsForSelection();`
- L120 _protected prototype_ `bool CanGenerateFlippedMorphTargets();`
- L122 _protected member_ `TSharedPtr<SSearchBox> NameFilterBox;`
- L123 _protected member_ `TSharedPtr<SMorphTargetManagerListType> ListView;`
- L125 _protected member_ `TArray<FMorphTargetInfoPtr> List;`
- L126 _protected member_ `TArray<FMorphTargetInfoPtr> FullList;`
- L128 _protected member_ `TWeakObjectPtr<UMorphTargetModifier> Modifier;`
- L136 _protected member_ `FPendingRowActions Pending;`
- L138 _protected member_ `TWeakInterfacePtr<IMorphTargetManagerDataSource> WeakDataSource;`
- L139 _protected member_ `FDelegateHandle InvalidationHandle;`
- L141 _protected member_ `ESortMode SortMode = ESortMode::Alphabetical;`
- L142 _protected member_ `bool bInvertFilter = false;`
- L143 _protected member_ `bool bDisableFilter = false;`
- L146 _protected member_ `TSharedPtr<FUICommandList> CommandList;` — Commands

#### enum `SMorphTargetManager::ESortMode`  
`enum class ESortMode : uint8`  
_L47-53_
- desc: How rows in the morph target list are ordered.
- L50 _public enumerator_ `Custom` — Preserve the order returned by the data source.
- L52 _public enumerator_ `Alphabetical` — Sort by morph target name.

#### struct `SMorphTargetManager::FPendingRowActions`  
`struct FPendingRowActions`  
_L130-135_
- L132 _public member_ `TSet<FName> ToSelect;`
- L133 _public member_ `FName ToScrollTo = NAME_None;`
- L134 _public member_ `FName ToRename = NAME_None;`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace MorphTargetManagerLocal`
- L18 _typedef_ `typedef TSharedPtr<MorphTargetManagerLocal::FMorphTargetInfo> FMorphTargetInfoPtr;`
- L19 _typedef_ `typedef SListView< FMorphTargetInfoPtr > SMorphTargetManagerListType;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/Selection/SKMEditingCacheSelector.h` (Private)


#### class `FSkeletalMeshEditingCacheSelectionTransformer`  
`class FSkeletalMeshEditingCacheSelectionTransformer : public FBasicDynamicMeshSelectionTransformer`  
_L25-31_
- inherits: `FBasicDynamicMeshSelectionTransformer`
- desc: Custom transformers that remap selection from editing-mesh space to preview-mesh space before delegating to the base class. Only BeginTransform is overridden.
- L28 _public member_ `const UE::Geometry::FDynamicSubmesh3* IsolationSubmeshMapping = nullptr;`
- L29 _public member_ `const UE::Geometry::FGroupTopology* PreviewGroupTopology = nullptr;`
- L30 _public prototype_ `virtual void BeginTransform(const UE::Geometry::FGeometrySelection& Selection) override;`

#### class `FSkeletalMeshEditingCachePolygroupTransformer`  
`class FSkeletalMeshEditingCachePolygroupTransformer : public FDynamicMeshPolygroupTransformer`  
_L33-39_
- inherits: `FDynamicMeshPolygroupTransformer`
- L36 _public member_ `const UE::Geometry::FDynamicSubmesh3* IsolationSubmeshMapping = nullptr;`
- L37 _public member_ `const UE::Geometry::FGroupTopology* PreviewGroupTopology = nullptr;`
- L38 _public prototype_ `virtual void BeginTransform(const UE::Geometry::FGeometrySelection& Selection) override;`

#### class `FSkeletalMeshEditingCacheSelector`  
`class FSkeletalMeshEditingCacheSelector : public FBaseDynamicMeshSelector`  
_L56-196_
- inherits: `FBaseDynamicMeshSelector`
- desc: Dual-mesh selector for skeletal mesh editing. Base-class TargetMesh is the posed preview mesh (from UPreviewMesh's DynamicMeshComponent). Spatial queries, hit testing, transformers, and rendering all use the preview mesh naturally. Selection IDs are always stored in editing-mesh (full mesh) space. When geometry isolation is active, the preview mesh is a submesh with different IDs, so the selector remaps between the two spaces via FDynamicSubmesh3 mappings. When no isolation is active, IDs are identical and no remapping is needed. A separate EditingMesh reference provides access to the full unposed mesh for topology queries and selection ID construction.
- L59 _public prototype_ `virtual ~FSkeletalMeshEditingCacheSelector();`
- L62 _public prototype_ `void InitializeFromEditingCache( FGeometryIdentifier InSourceGeometryIdentifier, USkeletalMeshEditingCache* InEditingCache, TFunction<FName()> InGetEditingMorphTargetFunc);` — Initialize from an editing cache. TargetMesh = preview mesh, stores editing mesh separately.
- L68 _public prototype_ `void SetActiveSubmeshMapping(const UE::Geometry::FDynamicSubmesh3* InSubmeshMapping);` — Set the active submesh mapping for ID remapping. nullptr when isolation is not active.
- L72 _public prototype_ `virtual void Shutdown() override;`
- L76 _public prototype_ `virtual void InitializeSelectionFromPredicate( FGeometrySelection& SelectionInOut, TFunctionRef<bool(UE::Geometry::FGeoSelectionID)> SelectionIDPredicate, EInitializeSelectionMode InitializeMode = EInitializeSelectionMode::All, const FGeometrySelection* ReferenceSelection = nullptr) override;`
- L82 _public prototype_ `virtual void UpdateSelectionFromSelection( const FGeometrySelection& FromSelection, bool bAllowConversion, FGeometrySelectionEditor& SelectionEditor, const FGeometrySelectionUpdateConfig& UpdateConfig, UE::Geometry::FGeometrySelectionDelta* SelectionDelta = nullptr) override;`
- L89 _public prototype_ `virtual bool ConvertSelection( const FGeometrySelection& FromSelectionIn, FGeometrySelection& ToSelectionOut, const UE::Geometry::EEnumerateSelectionConversionParams ConversionParams) override;`
- L96 _public prototype_ `virtual void UpdateSoftSelection( FGeometrySelection& Selection, const FUpdateSoftSelectionConfig& InSoftSelectionConfig) override;`
- L103 _public prototype_ `virtual void AccumulateSelectionElements( const FGeometrySelection& Selection, FGeometrySelectionElements& Elements, bool bTransformToWorld, UE::Geometry::EEnumerateSelectionMapping Flags = UE::Geometry::EEnumerateSelectionMapping::Default) override;`
- L109 _public prototype_ `virtual void AccumulateSelectionBounds( const FGeometrySelection& Selection, FGeometrySelectionBounds& BoundsInOut, bool bTransformToWorld) override;`
- L114 _public prototype_ `virtual void GetSelectionFrame( const FGeometrySelection& Selection, UE::Geometry::FFrame3d& SelectionFrame, bool bTransformToWorld) override;`
- L121 _public prototype_ `virtual void UpdateSelectionViaRaycast( const FWorldRayQueryInfo& RayInfo, FGeometrySelectionEditor& SelectionEditor, const FGeometrySelectionUpdateConfig& UpdateConfig, FGeometrySelectionUpdateResult& ResultOut) override;`
- L127 _public prototype_ `virtual void GetSelectionPreviewForRaycast( const FWorldRayQueryInfo& RayInfo, FGeometrySelectionEditor& PreviewEditor) override;`
- L131 _public prototype_ `virtual void UpdateSelectionViaShape( const FWorldShapeQueryInfo& ShapeInfo, FGeometrySelectionEditor& SelectionEditor, const FGeometrySelectionUpdateConfig& UpdateConfig, FGeometrySelectionUpdateResult& ResultOut) override;`
- L139 _public prototype_ `virtual IGeometrySelectionTransformer* InitializeTransformation(const FGeometrySelection& Selection) override;`
- L140 _public prototype_ `virtual void ShutdownTransformation(IGeometrySelectionTransformer* Transformer) override;`
- L145 _protected prototype_ `virtual void UpdateSelectionViaRaycast_MeshTopology( const FWorldRayQueryInfo& RayInfo, FGeometrySelectionEditor& SelectionEditor, const FGeometrySelectionUpdateConfig& UpdateConfig, FGeometrySelectionUpdateResult& ResultOut) override;`
- L151 _protected prototype_ `virtual void UpdateSelectionViaRaycast_GroupEdges( const FWorldRayQueryInfo& RayInfo, FGeometrySelectionEditor& SelectionEditor, const FGeometrySelectionUpdateConfig& UpdateConfig, FGeometrySelectionUpdateResult& ResultOut) override;`
- L159 _protected member_ `TWeakObjectPtr<UDynamicMesh> EditingMesh;`
- L160 _protected member_ `FDelegateHandle EditingMesh_OnMeshChangedHandle;`
- L161 _protected member_ `FGeometryIdentifier EditingMeshIdentifier;`
- L162 _protected member_ `TPimplPtr<UE::Geometry::FGroupTopology> EditingGroupTopology;`
- L164 _protected prototype_ `const UE::Geometry::FGroupTopology* GetEditingMeshGroupTopology();`
- L165 _protected prototype_ `void InvalidateEditingMeshCaches();`
- L170 _protected member_ `const UE::Geometry::FDynamicSubmesh3* ActiveSubmeshMapping = nullptr;` — Non-owning pointer to the submesh mapping. nullptr when isolation is not active.
- L175 _protected prototype_ `int32 RemapVertexToEditingMesh(int32 PreviewVertexID) const;` — Remap from preview-mesh space to editing-mesh space. Identity when no submesh mapping active.
- L176 _protected prototype_ `int32 RemapTriangleToEditingMesh(int32 PreviewTriangleID) const;`
- L177 _protected prototype_ `int32 RemapEdgeToEditingMesh(int32 PreviewEdgeID) const;`
- L180 _protected prototype_ `int32 RemapVertexToPreviewMesh(int32 EditingVertexID) const;` — Remap from editing-mesh space to preview-mesh space. Returns InvalidID if not in submesh.
- L181 _protected prototype_ `int32 RemapTriangleToPreviewMesh(int32 EditingTriangleID) const;`
- L185 _protected member_ `FDelegateHandle OnIsolationChangedHandle;`
- L186 _protected prototype_ `void HandleIsolationChanged();`
- L190 _protected member_ `TWeakObjectPtr<USkeletalMeshEditingCache> WeakEditingCache;`
- L191 _protected member_ `TFunction<FName()> GetEditingMorphTargetFunc;`
- L192 _protected member_ `TSharedPtr<FBasicDynamicMeshSelectionTransformer> ActiveTransformer;`
- L193 _protected prototype_ `void CommitMeshTransform();`

#### class `FSkeletalMeshEditingCacheSelectorFactory`  
`class FSkeletalMeshEditingCacheSelectorFactory : public IGeometrySelectorFactory`  
_L202-212_
- inherits: `IGeometrySelectorFactory`
- desc: Factory that constructs FSkeletalMeshEditingCacheSelector instances.
- L205 _public prototype_ `void Init(USkeletalMeshModelingToolsEditorMode* InEditorMode);`
- L207 _public prototype_ `virtual bool CanBuildForTarget(FGeometryIdentifier TargetIdentifier) const override;`
- L208 _public prototype_ `virtual TUniquePtr<IGeometrySelector> BuildForTarget(FGeometryIdentifier TargetIdentifier) const override;`
- L211 _protected member_ `TWeakObjectPtr<USkeletalMeshModelingToolsEditorMode> WeakEditorMode;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API SKELETALMESHMODELINGTOOLS_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/Selection/SKMGeometrySelectionTransformTweaker.h` (Private)


#### class `USkeletalMeshGeometrySelectionTransformTweaker`  
`class USkeletalMeshGeometrySelectionTransformTweaker : public UObject`  
_L16-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public prototype_ `void Setup(UGeometrySelectionManager* InSelectionManager);`
- L22 _public prototype_ `void Shutdown();`
- L24 _public prototype_ `const FTransform& GetSelectionFrameTransform();`
- L26 _public prototype_ `void BeginTransformEdit();`
- L27 _public prototype_ `void EndTransformEdit();`
- L28 _public prototype_ `bool IsEditingTransform() const;`
- L29 _public prototype_ `void TweakTransform(FVector& InDrag, FRotator& InRot, FVector& InScale, bool bInIsWorldSpace);`
- L31 _public prototype_ `void SetLocalFrameMode(EModelingSelectionInteraction_LocalFrameMode InLocalFrameMode);`
- L32 _public prototype_ `EModelingSelectionInteraction_LocalFrameMode GetLocalFrameMode() const;`
- L34 _public prototype_ `void UpdateSelectionFrameTransform();`
- L37 _protected prototype_ `void OnSelectionManager_SelectionModified();`
- L39 _protected member_ `TWeakObjectPtr<UGeometrySelectionManager> SelectionManager;`
- L41 _protected member_ `FTransform CachedSelectionFrameTransform;`
- L43 _protected member_ `FTransform StartSelectionFrameTransform;`
- L45 _protected member_ `FVector Scale;`
- L47 _protected member_ `EModelingSelectionInteraction_LocalFrameMode LocalFrameMode = EModelingSelectionInteraction_LocalFrameMode::FromGeometry;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshEditingCache.h` (Private)


#### class `UMorphTargetNamingConventionSettings`  
`class UMorphTargetNamingConventionSettings : public UObject`  
_L39-51_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Transient session settings for the morph-target batch operations exposed by SMorphTargetManager. Values live on the CDO and reset when the editor closes — no disk persistence. NOTE: Co-located with USkeletalMeshEditingCache for now; a follow-up refactor will move it.
- L46 _public member_ `FString LeftPattern = TEXT("*_l` — `UPROPERTY(EditAnywhere, Category = "Naming Convention")` — Wildcard pattern that identifies left-side morph targets. Must contain exactly one '*'.
- L50 _public member_ `FString RightPattern = TEXT("*_r` — `UPROPERTY(EditAnywhere, Category = "Naming Convention")` — Wildcard pattern for the right-side counterpart. Must contain exactly one '*'. The '*' is replaced with the stem extracted from the matching left morph.

#### class `FSkeletalMeshEditingCacheNotifier`  
`class FSkeletalMeshEditingCacheNotifier: public ISkeletalMeshNotifier`  
_L55-62_
- inherits: `ISkeletalMeshNotifier`
- L58 _public prototype_ `FSkeletalMeshEditingCacheNotifier(USkeletalMeshEditingCache* InEditingCahe);`
- L59 _public prototype_ `virtual void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) override;`
- L61 _private member_ `TWeakObjectPtr<USkeletalMeshEditingCache> EditingCache;`

#### class `USkeletalMeshEditingCache`  
`class USkeletalMeshEditingCache: public UObject`  
_L66-292_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- L71 _public prototype_ `DECLARE_DELEGATE_OneParam(FToggleSkeletalMeshBoneManipulation, bool);`
- L72 _public prototype_ `DECLARE_DELEGATE_RetVal(bool, FIsSkeletalMeshBoneManipulationEnabled);`
- L73 _public prototype_ `DECLARE_DELEGATE_RetVal(TSharedPtr<ISkeletalMeshNotifier>, FOnGetSkeletalMeshSkeletonNotifier);`
- L85 _public prototype_ `void Spawn(UWorld* World, USkeletalMeshComponent* SkeletalMeshComponent, EMeshLODIdentifier LOD, const FDelegates& InDelegates, IToolsContextTransactionsAPI* InTransactionsAPI);`
- L86 _public prototype_ `EMeshLODIdentifier GetLOD() const;`
- L88 _public prototype_ `void Destroy();`
- L90 _public prototype_ `void ApplyChanges();`
- L92 _public prototype_ `void DiscardChanges();`
- L94 _public prototype_ `void HandleComponentChanged();`
- L95 _public prototype_ `void HandleSkeletonChanged();`
- L97 _public prototype_ `void Tick();`
- L98 _public prototype_ `bool HandleClick(HHitProxy *HitProxy);`
- L99 _public prototype_ `void Render(FPrimitiveDrawInterface* PDI, TFunction<void(FSkelDebugDrawConfig&)> OverrideBoneDrawConfigFunc);`
- L100 _public prototype_ `void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas);`
- L102 _public prototype_ `TSharedPtr<ISkeletalMeshNotifier> GetNotifier();`
- L103 _public prototype_ `void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType);`
- L105 _public prototype_ `void ToggleForceEnableDynamicMesh(bool bEnable);`
- L107 _public prototype_ `USkeletalMeshBackedDynamicMeshComponent* GetEditingMeshComponent() const;`
- L108 _public prototype_ `UPrimitiveComponent* GetPreviewMeshComponent() const;`
- L109 _public prototype_ `const TArray<FTransform>& GetComponentSpaceBoneTransforms() const;`
- L110 _public prototype_ `FTransform GetTransform();`
- L112 _public prototype_ `void ToggleBoneManipulation(bool bEnable);`
- L113 _public prototype_ `void SetSkeletonDrawMode(ESkeletonDrawMode InSkeletonDrawMode);`
- L115 _public prototype_ `bool IsDynamicMeshSkeletonEnabled() const;`
- L116 _public prototype_ `bool IsDynamicMeshBoneManipulationEnabled() const;`
- L117 _public prototype_ `int32 GetFirstSelectedBoneIndex() const;`
- L118 _public prototype_ `TArray<FName> GetSelectedBones() const;`
- L119 _public prototype_ `void ResetDynamicMeshBoneTransforms(bool bSelectedOnly);`
- L121 _public prototype_ `TArray<FName> GetMorphTargets() const;`
- L122 _public prototype_ `TMap<FName, float> GetMorphTargetWeights() const;`
- L123 _public prototype_ `float GetMorphTargetWeight(FName MorphTarget) const;`
- L125 _public prototype_ `void HandleSetMorphTargetWeight(FName MorphTarget, float Weight);`
- L126 _public prototype_ `bool GetMorphTargetAutoFill(FName MorphTarget);`
- L127 _public prototype_ `void HandleSetMorphTargetAutoFill(FName MorphTarget, bool bAutoFill, float PreviousOverrideWeight);`
- L128 _public prototype_ `void HandleMorphTargetEdited(FName MorphTarget);`
- L130 _public prototype_ `void OverrideMorphTargetWeight(FName MorphTarget, float Weight);`
- L131 _public prototype_ `void ClearMorphTargetOverride(FName MorphTarget);`
- L133 _public prototype_ `FName AddMorphTarget(FName InName);`
- L134 _public prototype_ `TArray<FName> AddMorphTargetsIfMissing(const TArray<FName>& Names);`
- L135 _public prototype_ `FName RenameMorphTarget(FName InOldName, FName InNewName);`
- L136 _public prototype_ `void RemoveMorphTargets(const TArray<FName>& InNames);`
- L137 _public prototype_ `TArray<FName> DuplicateMorphTargets(const TArray<FName>& InNames);`
- L138 _public prototype_ `void MirrorMorphTargets(const TArray<FName>& InNames);`
- L139 _public prototype_ `void FlipMorphTargets(const TArray<FName>& InNames);`
- L140 _public prototype_ `FName MergeMorphTargets(const TArray<FName>& InNames);`
- L141 _public prototype_ `void ApplyCurrentWeightToMorphTarget(FName InName);`
- L142 _public prototype_ `void GenerateFlippedMorphTargets(const TArray<TPair<FName, FName>>& InPairs);`
- L144 _public prototype_ `void HandleGeometryUpdate(const UE::Geometry::FDynamicMesh3& InMesh, FName MorphTargetName);`
- L146 _public prototype_ `const UE::Geometry::FMeshPlanarSymmetry* GetBaseMeshSymmetry();`
- L148 _public prototype_ `URefSkeletonPoser* GetSkeletonPoser() const;`
- L153 _public prototype_ `bool IsolateSelection(const UE::Geometry::FGeometrySelection& InSelection);` — Geometry isolation — high-level APIs that compute new isolation, mutate state, rebuild preview mesh Returns false if no-op.
- L154 _public prototype_ `bool HideSelection(const UE::Geometry::FGeometrySelection& InSelection);`
- L155 _public prototype_ `bool ShowFullMesh(bool bSaveIsolation = false);`
- L159 _public prototype_ `bool ConvertIsolationForTopologyMode(UE::Geometry::EGeometryTopologyType NewTopologyType);` — Converts isolation triangles when switching topology modes (e.g. expands to full polygroups). Returns false if no-op.
- L161 _public prototype_ `bool HasIsolation() const;`
- L162 _public prototype_ `const TArray<int32>& GetIsolatedTriangles() const;`
- L163 _public prototype_ `const UE::Geometry::FDynamicSubmesh3* GetIsolationSubmesh() const;`
- L165 _public function_ `FSimpleMulticastDelegate& GetOnIsolationChanged()`
- L168 _public prototype_ `bool HasSavedIsolation() const;` — Saved isolation — allows temporarily showing full mesh and restoring later (e.g. during tool use)
- L169 _public prototype_ `const TArray<int32>& GetSavedIsolationTriangles() const;`
- L170 _public prototype_ `void RestoreSavedIsolation();`
- L171 _public prototype_ `void DiscardSavedIsolation();`
- L175 _public prototype_ `void SetTriangleIsolation(TArray<int32> InFullMeshTriangles);` — Sets isolation state and rebuilds the preview mesh. Records undo via TransactionsAPI.
- L177 _public prototype_ `void RequestDeformPreviewMesh();`
- L180 _protected member_ `TObjectPtr<AActor> HostActor;` — `UPROPERTY()`
- L183 _protected member_ `TObjectPtr<USkeletalMeshBackedDynamicMeshComponent> EditingMeshComponent;` — `UPROPERTY()`
- L186 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L189 _protected member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY()`
- L191 _protected member_ `FDelegates Delegates;`
- L192 _protected member_ `IToolsContextTransactionsAPI* TransactionsAPI = nullptr;`
- L194 _protected member_ `bool bShouldDeformPreviewMesh = false;`
- L197 _protected member_ `bool bCacheVisibility = true;` — Flags that drives both dyna mesh and skeletal mesh
- L198 _protected member_ `ESkeletonDrawMode CacheSkeletonDrawMode = ESkeletonDrawMode::Default;`
- L199 _protected member_ `bool bCacheBoneManipulation = true;`
- L201 _protected member_ `bool bForceEnableDynamicMesh = false;`
- L203 _protected prototype_ `bool IsDynamicMeshEnabled() const;`
- L206 _protected member_ `TValueWatcher<bool> SkeletonChangeCountWatcher;` — Rebinds the skeletal-mesh notifier scope when IsDynamicMeshSkeletonEnabled() transitions.
- L215 _protected member_ `TValueWatcher<FMeshVisibilityFactors> MeshVisibilityUpdater;`
- L225 _protected member_ `TValueWatcher<FSkeletonVisibilityFactors> SkeletonVisibilityUpdater;`
- L235 _protected member_ `TValueWatcher<FBoneManipulationFactors> BoneManipulationUpdater;`
- L237 _protected member_ `TValueWatcher<bool> PreviewMeshVisibilityWatcher;`
- L239 _protected prototype_ `void HandleVisibilityChangeRequest(bool bVisible);`
- L242 _protected member_ `TObjectPtr<URefSkeletonPoser> RefSkeletonPoser;` — `UPROPERTY()`
- L245 _protected member_ `TMap<FName, float> MorphTargetOverrides;` — `UPROPERTY()`
- L247 _protected member_ `SkeletalMeshToolsHelper::FPoseChangeDetector PoseChangeDetector;`
- L249 _protected prototype_ `void HandlePoseChangeDetectorEvent(SkeletalMeshToolsHelper::FPoseChangeDetector::FPayload Payload);`
- L251 _protected prototype_ `const TArray<FTransform>& GetComponentSpaceBoneTransformsRefPose() const;`
- L253 _protected prototype_ `const TMap<FName, float>& GetSkeletalMeshComponentMorphTargetWeights() const;`
- L255 _protected prototype_ `void DeformPreviewMesh(const TArray<FTransform>& ComponentSpaceTransforms, const TMap<FName, float>& MorphTargetWeights);`
- L257 _protected member_ `TSharedPtr<FSkeletalMeshEditingCacheNotifier> Notifier;`
- L258 _protected member_ `TUniquePtr<FSkeletalMeshNotifierBindScope> SkeletalMeshSkeletonNotifierBindScope;`
- L260 _protected member_ `TArray<FName> SelectedBoneNames;`
- L261 _protected member_ `TArray<int32> SelectedBoneIndices;`
- L262 _protected prototype_ `void UpdateSelectedBoneIndices();`
- L264 _protected prototype_ `void SetSkeletalMeshSkeletonDrawMode(ESkeletonDrawMode DrawMode) const;`
- L265 _protected prototype_ `ESkeletonDrawMode GetCurrentSkeletonDrawMode() const;`
- L267 _protected prototype_ `FLinearColor GetDefaultBoneColor(int32 BoneIndex) const;`
- L269 _protected prototype_ `UDebugSkelMeshComponent* GetDebugSkelMeshComponent() const;`
- L272 _protected member_ `TArray<int32> IsolatedTrianglesFromFullMesh;` — Geometry isolation state
- L273 _protected member_ `TOptional<UE::Geometry::FDynamicSubmesh3> IsolationSubmesh;`
- L274 _protected member_ `TOptional<TArray<int32>> SavedIsolationTriangles;`
- L275 _protected member_ `FSimpleMulticastDelegate OnIsolationChanged;`
- L277 _protected prototype_ `void RebuildPreviewMesh();`
- L287 _protected prototype_ `bool ComputeIsolatedTriangles( EIsolationOperation Operation, const UE::Geometry::FGeometrySelection& Selection, TArray<int32>& OutFullMeshTriangles) const;`

#### struct `USkeletalMeshEditingCache::FDelegates`  
`struct FDelegates`  
_L74-83_
- L76 _public member_ `FToggleSkeletalMeshBoneManipulation ToggleSkeletalMeshBoneManipulationDelegate;`
- L77 _public member_ `FIsSkeletalMeshBoneManipulationEnabled IsSkeletalMeshBoneManipulationEnabledDelegate;`
- L78 _public member_ `FOnGetSkeletalMeshSkeletonNotifier OnGetSkeletalMeshSkeletonNotifierDelegate;`
- L80 _public member_ `FSimpleMulticastDelegate OnComponentChangedEvent;`
- L81 _public member_ `FSimpleMulticastDelegate OnSkeletonChangedEvent;`
- L82 _public member_ `FSimpleMulticastDelegate OnPreviewMeshDeformedEvent;`

#### struct `USkeletalMeshEditingCache::FMeshVisibilityFactors`  
`struct FMeshVisibilityFactors`  
_L208-213_
- L210 _public member_ `bool bIsDynamicMeshEnabled= false;`
- L211 _public member_ `bool bCacheVisibility = true;`

#### struct `USkeletalMeshEditingCache::FSkeletonVisibilityFactors`  
`struct FSkeletonVisibilityFactors`  
_L218-223_
- L220 _public member_ `bool bIsDynamicMeshSkeletonEnabled = false;`
- L221 _public member_ `ESkeletonDrawMode CacheSkeletonDrawMode = ESkeletonDrawMode::Default;`

#### struct `USkeletalMeshEditingCache::FBoneManipulationFactors`  
`struct FBoneManipulationFactors`  
_L228-233_
- L230 _public member_ `bool bIsDynamicMeshSkeletonEnabled = false;`
- L231 _public member_ `bool bCacheBoneManipulation = true;`

#### enum `USkeletalMeshEditingCache::EIsolationOperation`  
`enum class EIsolationOperation`  
_L281-285_
- desc: Pure computation: given an operation and current selection, computes the new isolation triangle set (in full mesh space)
- L283 _public enumerator_ `Isolate`
- L284 _public enumerator_ `Hide`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API SKELETALMESHMODELINGTOOLS_API`
- L71 _delegate_ `DECLARE_DELEGATE_OneParam(FToggleSkeletalMeshBoneManipulation, bool);`
- L72 _delegate_ `DECLARE_DELEGATE_RetVal(bool, FIsSkeletalMeshBoneManipulationEnabled);`
- L73 _delegate_ `DECLARE_DELEGATE_RetVal(TSharedPtr<ISkeletalMeshNotifier>, FOnGetSkeletalMeshSkeletonNotifier);`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshEditorUtils.h` (Private)


#### class `USkeletalMeshEditorContextObject`  
`class USkeletalMeshEditorContextObject : public USkeletalMeshEditorContextObjectBase`  
_L40-90_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkeletalMeshEditorContextObjectBase`
- L45 _public prototype_ `void Register(UInteractiveToolManager* InToolManager);`
- L46 _public prototype_ `void Unregister(UInteractiveToolManager* InToolManager);`
- L48 _public prototype_ `void Init(USkeletalMeshModelingToolsEditorMode* InEditorMode);`
- L50 _public prototype_ `virtual EMeshLODIdentifier GetEditingLOD() override;`
- L52 _public prototype_ `virtual void HideSkeleton() override;`
- L53 _public prototype_ `virtual void ShowSkeleton() override;`
- L54 _public prototype_ `virtual void ToggleBoneManipulation(bool bEnable) override;`
- L55 _public prototype_ `virtual const TArray<FTransform>& GetComponentSpaceBoneTransforms(UToolTarget* InToolTarget) override;`
- L57 _public prototype_ `virtual FName GetEditingMorphTarget() override;`
- L58 _public prototype_ `virtual TMap<FName, float> GetMorphTargetWeights() override;`
- L59 _public prototype_ `virtual void NotifyMorphTargetEdited() override;`
- L60 _public prototype_ `virtual const UE::Geometry::FMeshPlanarSymmetry* GetBaseMeshSymmetry() override;`
- L61 _public prototype_ `virtual const TArray<int32>& GetIsolatedTriangles() const override;`
- L64 _public prototype_ `virtual void BindTo(ISkeletalMeshEditingInterface* InEditingInterface) override;`
- L65 _public prototype_ `virtual void UnbindFrom(ISkeletalMeshEditingInterface* InEditingInterface) override;`
- L68 _private member_ `TWeakObjectPtr<USkeletalMeshModelingToolsEditorMode> EditorMode = nullptr;`
- L70 _private prototype_ `TSharedPtr<ISkeletalMeshEditorBinding> GetBinding() const;`
- L76 _private member_ `TMap< ISkeletalMeshEditingInterface*, FBindData > EditorBindings;`
- L78 _private prototype_ `static FBindData BindInterfaceTo( ISkeletalMeshEditingInterface* InInterface, TSharedPtr<ISkeletalMeshNotifier> InOtherNotifier);`
- L82 _private prototype_ `static void UnbindInterfaceFrom( FBindData& InOutBindData);`
- L85 _private prototype_ `void BindEditor(ISkeletalMeshEditingInterface* InEditingInterface);`
- L86 _private prototype_ `void UnbindEditor(ISkeletalMeshEditingInterface* InEditingInterface);`
- L89 _private member_ `bool bRegistered = false;`

#### struct `USkeletalMeshEditorContextObject::FBindData`  
`struct FBindData`  
_L72-75_
- L74 _public member_ `TUniquePtr<FSkeletalMeshNotifierBindScope> BindScope;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API SKELETALMESHMODELINGTOOLS_API`
- L21 _namespace_ `namespace UE`
- L24 _namespace_ `namespace SkeletalMeshEditorUtils` (scope `UE`)
- L26 _prototype_ `bool RegisterEditorContextObject(UInteractiveToolsContext* InToolsContext);` (scope `UE::SkeletalMeshEditorUtils`)
- L27 _prototype_ `bool UnregisterEditorContextObject(UInteractiveToolsContext* InToolsContext);` (scope `UE::SkeletalMeshEditorUtils`)
- L29 _prototype_ `USkeletalMeshEditorContextObject* GetEditorContextObject(UInteractiveToolsContext* InToolsContext);` (scope `UE::SkeletalMeshEditorUtils`)

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshGizmoUtils.h` (Private)


#### class `USkeletalMeshGizmoWrapper`  
`class USkeletalMeshGizmoWrapper : public USkeletalMeshGizmoWrapperBase`  
_L57-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkeletalMeshGizmoWrapperBase`
- L61 _public prototype_ `virtual void Initialize(const FTransform& InTransform = FTransform::Identity, const EToolContextCoordinateSystem& InTransformMode = EToolContextCoordinateSystem::Local) override;`
- L62 _public prototype_ `virtual void HandleBoneTransform(FGetTransform GetTransformFunc, FSetTransform SetTransformFunc) override;`
- L63 _public prototype_ `virtual void Clear() override;`
- L65 _public prototype_ `virtual bool CanInteract() const override;`
- L66 _public prototype_ `virtual bool IsGizmoHit(const FInputDeviceRay& PressPos) const override;`
- L69 _public member_ `TObjectPtr<UTransformGizmo> TransformGizmo;` — `UPROPERTY()`
- L71 _public member_ `TObjectPtr<USkeletonTransformProxy> TransformProxy;` — `UPROPERTY()`

#### class `USkeletalMeshGizmoContextObject`  
`class USkeletalMeshGizmoContextObject : public USkeletalMeshGizmoContextObjectBase`  
_L80-99_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USkeletalMeshGizmoContextObjectBase`
- L87 _public prototype_ `static const FString& TransformBuilderIdentifier();` — builder identifiers for transform gizmo
- L89 _public prototype_ `void RegisterGizmosWithManager(UInteractiveToolManager* InToolManager);`
- L90 _public prototype_ `void UnregisterGizmosWithManager(UInteractiveToolManager* InToolManager);`
- L92 _public prototype_ `virtual USkeletalMeshGizmoWrapperBase* GetNewWrapper(UInteractiveToolManager* InToolManager, UObject* Outer = nullptr, IGizmoStateTarget* InStateTarget = nullptr, const TScriptInterface<ITransformGizmoSource>& GizmoSource = nullptr) override;`
- L96 _private prototype_ `static const FGizmoCustomization& GetGizmoCustomization();`
- L98 _private member_ `bool bGizmosRegistered = false;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API SKELETALMESHMODELINGTOOLS_API`
- L20 _namespace_ `namespace UE`
- L23 _namespace_ `namespace SkeletalMeshGizmoUtils` (scope `UE`)
- L35 _prototype_ `bool RegisterTransformGizmoContextObject(UInteractiveToolsContext* InToolsContext);` (scope `UE::SkeletalMeshGizmoUtils`) — If one does not already exist, create a new instance of USkeletalMeshGizmoContextObject and add it to the ToolsContext's ContextObjectStore @return true if the ContextObjectStore now has a USkeletalMeshGizmoContextObject (whether it already existed, or was created)
- L41 _prototype_ `bool UnregisterTransformGizmoContextObject(UInteractiveToolsContext* InToolsContext);` (scope `UE::SkeletalMeshGizmoUtils`) — Remove any existing USkeletalMeshGizmoContextObject from the ToolsContext's ContextObjectStore @return true if the ContextObjectStore no longer has a USkeletalMeshGizmoContextObject (whether it was removed, or did not exist)
- L46 _prototype_ `UTransformGizmo* CreateTransformGizmo(UInteractiveToolManager* ToolManager, void* Owner = nullptr);` (scope `UE::SkeletalMeshGizmoUtils`) — Spawn an editor like Transform Gizmo. ToolManager's ToolsContext must have a USkeletalMeshGizmoContextObject registered

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsCommands.h` (Private)


#### class `FSkeletalMeshModelingToolsCommands`  
`class FSkeletalMeshModelingToolsCommands : public TCommands<FSkeletalMeshModelingToolsCommands>`  
_L12-80_
- inherits: `TCommands<FSkeletalMeshModelingToolsCommands>`
- L15 _public function_ `FSkeletalMeshModelingToolsCommands() : TCommands<FSkeletalMeshModelingToolsCommands>( TEXT("SkeletalMeshModelingTools"), NSLOCTEXT("Contexts", "SkeletalMeshModelingToolsCommands", "Skeletal Mesh Modeling Tools"), NAME_None, FSkeletalMeshModelingToolsStyle::Get().GetStyleSetName())`
- L24 _public prototype_ `virtual void RegisterCommands() override;`
- L25 _public prototype_ `static const FSkeletalMeshModelingToolsCommands& Get();`
- L28 _public member_ `TSharedPtr<FUICommandInfo> BeginSkeletalMeshRunMeshProcessorBlueprintTool;` — Tool launch commands
- L31 _public member_ `TSharedPtr<FUICommandInfo> LoadMiscTools;` — Toolkit palette command — labels the "Misc" tool group.
- L34 _public member_ `TSharedPtr<FUICommandInfo> ToggleEditingToolsMode;` — Editing tools commands
- L37 _public member_ `TSharedPtr<FUICommandInfo> NewMorphTarget;` — Morph Target Editing commands
- L39 _public member_ `TSharedPtr<FUICommandInfo> AddMissingMorphTargetsFromSkeletalMesh;`
- L41 _public member_ `TSharedPtr<FUICommandInfo> MirrorSelectedMorphTarget;`
- L43 _public member_ `TSharedPtr<FUICommandInfo> MirrorEditingMorphTarget;`
- L45 _public member_ `TSharedPtr<FUICommandInfo> FlipSelectedMorphTarget;`
- L47 _public member_ `TSharedPtr<FUICommandInfo> FlipEditingMorphTarget;`
- L49 _public member_ `TSharedPtr<FUICommandInfo> MergeSelectedMorphTargets;`
- L51 _public member_ `TSharedPtr<FUICommandInfo> ApplyCurrentWeightToMorphTarget;`
- L53 _public member_ `TSharedPtr<FUICommandInfo> ToggleSelectedMorphTargetWeight;`
- L55 _public member_ `TSharedPtr<FUICommandInfo> ConfigureMorphTargetNamingConvention;`
- L57 _public member_ `TSharedPtr<FUICommandInfo> GenerateFlippedMorphTargets;`
- L60 _public member_ `TSharedPtr<FUICommandInfo> IsolateSelection;` — Geometry Isolation commands
- L61 _public member_ `TSharedPtr<FUICommandInfo> HideSelection;`
- L62 _public member_ `TSharedPtr<FUICommandInfo> ShowFullMesh;`
- L66 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_SelectAll;` — Mirror the entries in FModelingToolsManagerCommands so chords are remappable independently from the Modeling Mode shortcuts.
- L67 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Invert;`
- L68 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_ExpandToConnected;`
- L69 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_InvertConnected;`
- L70 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Expand;`
- L71 _public member_ `TSharedPtr<FUICommandInfo> BeginSelectionAction_Contract;`
- L74 _public member_ `TSharedPtr<FUICommandInfo> ShowQuickAccessMenu;` — Opens a context-menu-style popup at the cursor with selection-mode toggles and the last-used tool.
- L76 _public member_ `TSharedPtr<FUICommandInfo> ToggleHotkeyHints;`
- L79 _public member_ `TSharedPtr<FUICommandInfo> ToggleShowAllLocalRotationAxes;` — Command to toggle show all local rotation axes

#### class `FSkeletalMeshModelingToolsActionCommands`  
`class FSkeletalMeshModelingToolsActionCommands : public TInteractiveToolCommands<FSkeletalMeshModelingToolsActionCommands>`  
_L82-93_
- inherits: `TInteractiveToolCommands<FSkeletalMeshModelingToolsActionCommands>`
- L85 _public prototype_ `FSkeletalMeshModelingToolsActionCommands();`
- L88 _public prototype_ `virtual void GetToolDefaultObjectList(TArray<UInteractiveTool*>& ToolCDOs) override;` — TInteractiveToolCommands
- L90 _public prototype_ `static void RegisterAllToolActions();`
- L91 _public prototype_ `static void UnregisterAllToolActions();`
- L92 _public prototype_ `static void UpdateToolCommandBinding(UInteractiveTool* Tool, TSharedPtr<FUICommandList> UICommandList, bool bUnbind = false);`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsEditorMode.h` (Private)


#### class `FSkeletalMeshModelingToolsEditorModeNotifier`  
`class FSkeletalMeshModelingToolsEditorModeNotifier: public ISkeletalMeshNotifier`  
_L55-62_
- inherits: `ISkeletalMeshNotifier`
- desc: Mode Notifier simply serves as middle man between tools and editing cache to help record bone selection during tool <-> cache transitions, it does not start notifications instead it simply forwards the notification
- L58 _public prototype_ `FSkeletalMeshModelingToolsEditorModeNotifier(USkeletalMeshModelingToolsEditorMode* InEditorMode);`
- L59 _public prototype_ `virtual void HandleNotification(const TArray<FName>& BoneNames, const ESkeletalMeshNotifyType InNotifyType) override;`
- L61 _private member_ `TWeakObjectPtr<USkeletalMeshModelingToolsEditorMode> EditorMode;`

#### class `FSkeletalMeshModelingToolsEditorModeBinding`  
`class FSkeletalMeshModelingToolsEditorModeBinding: public ISkeletalMeshEditorBinding`  
_L64-77_
- inherits: `ISkeletalMeshEditorBinding`
- L67 _public prototype_ `FSkeletalMeshModelingToolsEditorModeBinding(USkeletalMeshModelingToolsEditorMode* InEditorMode);`
- L69 _public prototype_ `virtual TSharedPtr<ISkeletalMeshNotifier> GetNotifier() override;`
- L70 _public prototype_ `virtual NameFunction GetNameFunction() override;`
- L71 _public prototype_ `virtual TArray<FName> GetSelectedBones() const override;`
- L75 _private member_ `TWeakObjectPtr<USkeletalMeshModelingToolsEditorMode> EditorMode;`
- L76 _private member_ `TSharedPtr<FSkeletalMeshModelingToolsEditorModeNotifier> Notifier;`

#### class `USkeletalMeshModelingToolsEditorMode`  
`class USkeletalMeshModelingToolsEditorMode : public UBaseLegacyWidgetEdMode, public ISkeletalMeshBackedDynamicMeshComponentProvider, public IGizmoEdModeInterface, public IMorphTargetManagerDataSource, public IHotkeyHintProvider`  
_L82-382_
- reflection: `UCLASS()`
- inherits: `UBaseLegacyWidgetEdMode,ISkeletalMeshBackedDynamicMeshComponentProvider,IGizmoEdModeInterface,IMorphTargetManagerDataSource,IHotkeyHintProvider`
- L91 _public member_ `const static FEditorModeID Id;`
- L93 _public prototype_ `USkeletalMeshModelingToolsEditorMode();`
- L94 _public prototype_ `explicit USkeletalMeshModelingToolsEditorMode(FVTableHelper& Helper);`
- L98 _public prototype_ `virtual void Initialize() override;` — UEdMode overrides
- L99 _public prototype_ `virtual void Enter() override;`
- L100 _public prototype_ `virtual void Exit() override;`
- L101 _public prototype_ `virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;`
- L102 _public prototype_ `virtual void CreateToolkit() override;`
- L103 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L104 _public function_ `virtual bool UsesPropertyWidgets() const override`
- L106 _public prototype_ `virtual void Tick(FEditorViewportClient* InViewportClient, float InDeltaTime) override;`
- L107 _public prototype_ `virtual bool ComputeBoundingBoxForViewportFocus(AActor* Actor, UPrimitiveComponent* PrimitiveComponent, FBox& InOutBox) const override;`
- L108 _public function_ `virtual bool UsesToolkits() const override`
- L109 _public prototype_ `virtual bool ShouldToolStartBeAllowed(const FString& ToolIdentifier) const override;`
- L110 _public prototype_ `virtual void RegisterTool(TSharedPtr<FUICommandInfo> UICommand, FString ToolIdentifier, UInteractiveToolBuilder* Builder, EToolsContextScope ToolScope = EToolsContextScope::Default) override;`
- L113 _public prototype_ `TSharedPtr<FUICommandInfo> FindCommandForTool(const FString& ToolIdentifier) const;` — Returns the FUICommandInfo that registered the given tool identifier (palette button command), or nullptr if not registered through RegisterTool.
- L115 _public prototype_ `virtual bool MouseEnter(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 X, int32 Y) override;`
- L118 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;` — virtual bool StartTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override; virtual bool EndTracking(FEditorViewportClient* InViewportClient, FViewport* InViewport) override;
- L119 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L120 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient, FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L121 _public prototype_ `virtual bool AllowWidgetMove() override;`
- L122 _public prototype_ `virtual bool ShouldDrawWidget() const override;`
- L123 _public prototype_ `virtual bool UsesTransformWidget() const override;`
- L124 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L125 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L126 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(FMatrix& InMatrix, void* InData) override;`
- L127 _public prototype_ `virtual bool HandleClick(FEditorViewportClient* InViewportClient, HHitProxy *HitProxy, const FViewportClick &Click) override;`
- L128 _public function_ `virtual bool RequiresLegacyViewportInteractions() const override`
- L130 _public prototype_ `virtual void PostUndo() override;`
- L131 _public prototype_ `virtual bool OnRequestClose() override;`
- L134 _public prototype_ `virtual USkeletalMeshBackedDynamicMeshComponent* GetComponent(UObject* SourceObject) override;` — ISkeletalMeshBackedDynamicMeshComponentProvider
- L138 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) override;` — IGizmoEdModeInterface
- L139 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) override;`
- L142 _public prototype_ `TSharedPtr<ISkeletalMeshEditorBinding> GetModeBinding();` — binding
- L144 _public prototype_ `void SetEditorBinding(const TWeakPtr<ISkeletalMeshEditor>& InSkeletalMeshEditor);`
- L145 _public prototype_ `TSharedPtr<ISkeletalMeshEditorBinding> GetEditorBinding();`
- L146 _public prototype_ `TSharedPtr<ISkeletalMeshEditor> GetEditor() const;`
- L148 _public prototype_ `USkeletalMesh* GetSkeletalMesh() const;`
- L149 _public prototype_ `void HandleSkeletalMeshPreChange();`
- L150 _public prototype_ `void HandleSkeletalMeshChanged();`
- L152 _public prototype_ `bool CanSetEditingLOD();`
- L153 _public prototype_ `void SetEditingLOD(EMeshLODIdentifier EditingLOD);`
- L154 _public prototype_ `EMeshLODIdentifier GetEditingLOD();`
- L156 _public prototype_ `USkeletalMeshEditingCache* GetCurrentEditingCache() const;`
- L157 _public prototype_ `bool HasUnappliedChanges() const;`
- L158 _public prototype_ `void ApplyChanges();`
- L159 _public prototype_ `void DiscardChanges();`
- L167 _public prototype_ `EToolAcceptAction GetToolAcceptAction() const;`
- L168 _public prototype_ `void SetToolAcceptAction(EToolAcceptAction InAction);`
- L170 _public prototype_ `void RequestApplyChangesToAssetOnToolEnd();`
- L172 _public prototype_ `void HideSkeletonForTool();`
- L173 _public prototype_ `void ShowSkeletonForTool();`
- L174 _public prototype_ `void ToggleBoneManipulation(bool bEnable);`
- L175 _public prototype_ `USkeletonModifier* GetSkeletonReader();`
- L176 _public prototype_ `void SetSelectedBones(const TArray<FName>& InSelectedBones);`
- L177 _public prototype_ `TArray<FName> GetSelectedBones() const;`
- L180 _public prototype_ `virtual TArray<FName> GetMorphTargets() override;` — IMorphTargetManagerDataSource
- L181 _public prototype_ `virtual float GetMorphTargetWeight(FName MorphTarget) override;`
- L182 _public prototype_ `virtual void SetMorphTargetWeight(FName MorphTarget, float Weight) override;`
- L183 _public prototype_ `virtual bool GetMorphTargetAutoFill(FName MorphTarget) override;`
- L184 _public prototype_ `virtual void SetMorphTargetAutoFill(FName MorphTarget, bool bAutoFill, float PreviousOverrideWeight) override;`
- L185 _public prototype_ `virtual FName GetEditingMorphTarget() const override;`
- L186 _public prototype_ `virtual void SetEditingMorphTarget(FName MorphTarget) override;`
- L187 _public prototype_ `virtual FName AddMorphTarget(FName InName) override;`
- L188 _public prototype_ `virtual TArray<FName> AddMorphTargetsIfMissing(const TArray<FName>& Names) override;`
- L189 _public prototype_ `virtual FName RenameMorphTarget(FName OldName, FName NewName) override;`
- L190 _public prototype_ `virtual void RemoveMorphTargets(const TArray<FName>& Names) override;`
- L191 _public prototype_ `virtual TArray<FName> DuplicateMorphTargets(const TArray<FName>& Names) override;`
- L192 _public prototype_ `virtual void MirrorMorphTargets(const TArray<FName>& Names) override;`
- L193 _public prototype_ `virtual void FlipMorphTargets(const TArray<FName>& Names) override;`
- L194 _public prototype_ `virtual FName MergeMorphTargets(const TArray<FName>& Names) override;`
- L195 _public prototype_ `virtual void ApplyCurrentWeightToMorphTarget(FName Name) override;`
- L196 _public prototype_ `virtual void GenerateFlippedMorphTargets(const TArray<TPair<FName, FName>>& InPairs) override;`
- L197 _public function_ `virtual FSimpleMulticastDelegate& OnMorphTargetDataChanged() override`
- L199 _public prototype_ `TSharedPtr<FTabManager> GetAssociatedTabManager();`
- L201 _public prototype_ `void BindToolSkeletonTree(ISkeletalMeshEditingInterface* InEditingInterface);`
- L202 _public prototype_ `void UnbindToolSkeletonTree();`
- L204 _public function_ `FSimpleMulticastDelegate& OnInitialized()`
- L206 _public prototype_ `UGeometrySelectionManager* GetSelectionManager() const;`
- L209 _protected prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L210 _protected prototype_ `void OnToolPostBuild(UInteractiveToolManager* InToolManager, EToolSide InSide, UInteractiveTool* InBuiltTool, UInteractiveToolBuilder* InToolBuilder, const FToolBuilderState& ToolState);`
- L211 _protected prototype_ `void OnToolEndedWithStatus(UInteractiveToolManager* Manager, UInteractiveTool* Tool, EToolShutdownType ShutdownType);`
- L213 _protected prototype_ `void OnToolContextRender(IToolsContextRenderAPI* ToolsContextRenderAPI);`
- L214 _protected prototype_ `void OnToolContextDrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* ToolsContextRenderAPI);`
- L216 _protected prototype_ `void HandlePreSaveAsset();`
- L218 _private member_ `EToolAcceptAction ToolAcceptAction = EToolAcceptAction::ApplyToAsset;`
- L219 _private member_ `bool bApplyChangesToAssetOnToolEnd = false;`
- L221 _private member_ `TSharedPtr<FSkeletalMeshModelingToolsEditorModeBinding> ModeBinding;`
- L223 _private member_ `TWeakPtr<ISkeletalMeshEditor> Editor;`
- L224 _private member_ `TWeakPtr<ISkeletalMeshEditorBinding> EditorBinding;`
- L225 _private member_ `TWeakObjectPtr<USkeletalMesh> SkeletalMesh;`
- L228 _private member_ `TObjectPtr<USkeletalMeshEditingCache> CurrentEditingCache = nullptr;` — `UPROPERTY(NonTransactional)`
- L230 _private member_ `bool bExternalChangeDetected = false;`
- L231 _private prototype_ `void RecreateEditingCache(EMeshLODIdentifier InLOD);`
- L233 _private member_ `TUniquePtr<FSkeletalMeshNotifierBindScope> EditingCacheNotifierBindScope;`
- L237 _private member_ `TArray<FName> SelectedBones;` — Represents the collection of bones currently selected in the viewport for whichever skeleton that is currently active Helps maintain consistent bone selection state as different skeleton tree widget activates
- L240 _private member_ `FName EditingMorphTarget = NAME_None;` — `UPROPERTY()`
- L246 _private member_ `EToolManagerToolSwitchMode ToolSwitchModeToRestoreOnExit;` — we restore previous switch tool behavior when exiting this mode
- L248 _private prototype_ `static ISkeletalMeshEditingInterface* GetSkeletonInterface(UInteractiveTool* InTool);`
- L250 _private prototype_ `UDebugSkelMeshComponent* GetSkelMeshComponent() const;`
- L251 _private prototype_ `void ToggleSkeletalMeshBoneManipulation(bool bEnable);`
- L252 _private prototype_ `bool IsSkeletalMeshBoneManipulationEnabled();`
- L261 _private member_ `FDesiredSkeletonState DesiredSkeletonState;`
- L265 _private member_ `TObjectPtr<USkeletonModifier> SkeletonReader = nullptr;` — `UPROPERTY(NonTransactional)` — A dummy read-only modifier to host the current edited skeleton for RefSkeletonTree UI
- L276 _private member_ `TValueWatcher<FSkeletonTreeHostStateFactors> SkeletonTreeHostStateUpdater;` — Decides which skeleton tree widget to show to the user
- L278 _private member_ `bool bIsUsingToolSkeletonWidget = false;`
- L279 _private member_ `bool bActiveToolModifiesSkeleton = false;`
- L281 _private member_ `TWeakPtr<FSkeletalMeshModelingToolsEditorModeToolkit> TypedToolkit = nullptr;`
- L283 _private member_ `bool bDeactivateOnPIEStartStateToRestore;`
- L284 _private member_ `bool bDeactivateOnSaveWorldStateToRestore;`
- L286 _private prototype_ `void RegisterExtensions();`
- L288 _private member_ `TMap<FString, FExtensionToolDescription> ExtensionToolToInfo;` — Support extension tools having their own hotkey classes
- L291 _private prototype_ `bool TryGetExtensionToolCommandGetter(UInteractiveToolManager* InManager, const UInteractiveTool* InTool, TFunction<const UE::IInteractiveToolCommandsInterface&()>& OutGetter) const;` — Note: this will only work when the given tool is active, because we get the tool identifier out of the manager using GetActiveToolName
- L294 _private member_ `TFunction<const UE::IInteractiveToolCommandsInterface& ()> ExtensionToolCommandsGetter;` — Used to unbind extension tool commands
- L299 _private member_ `TSharedPtr<FUICommandList> ActiveToolCommandList;` — Separate from the toolkit list so chord dispatch isn't short-circuited by a disabled mode command sharing the chord (FUICommandList::ConditionalProcessCommandBindings short-circuits on the first chord match regardless of CanExecute).
- L300 _private member_ `TSharedPtr<FUICommandList> ActiveGeometrySelectionCommandList;`
- L302 _private member_ `bool bShowHotkeyHints = true;`
- L304 _private prototype_ `void DrawActiveToolHotkeyHints(FViewport* Viewport, FCanvas* Canvas) const;`
- L305 _private prototype_ `virtual void GetHotkeyHints(TArray<FHotkeyHint>& OutHints) const override;`
- L307 _private member_ `FSimpleMulticastDelegate OnInitializedDelegate;`
- L308 _private member_ `FSimpleMulticastDelegate OnMorphTargetDataChangedDelegate;`
- L313 _private member_ `TObjectPtr<UGeometrySelectionManager> SelectionManager;` — `UPROPERTY(NonTransactional)`
- L316 _private member_ `TObjectPtr<USkeletalMeshGeometrySelectionTransformTweaker> SelectionTransformTweaker;` — `UPROPERTY(NonTransactional)`
- L319 _private prototype_ `void HandleEditingCacheComponentChanged();` — Handlers for USkeletalMeshEditingCache events. Wired up in RecreateEditingCache.
- L320 _private prototype_ `void HandleEditingCacheSkeletonChanged();`
- L321 _private prototype_ `void HandleEditingCachePreviewMeshDeformed();`
- L327 _private prototype_ `void UpdateGeometrySelectionDerivedState();` — GeometrySelectionStateWatcher writes DesiredSkeletonState.bManipulation, which SkeletonStateUpdater reads — run them in order so the cascade settles in one pass. Also bound to SelectionManager->OnSelectionModified so any manager-driven state change (including undo/redo of selection mode) re-settles the derived state.
- L329 _private prototype_ `void SetSuspendGeometrySelection(bool bSuspend);`
- L330 _private prototype_ `void SetIsUsingToolSkeletonWidget(bool bUsing);`
- L331 _private prototype_ `void SetActiveToolModifiesSkeleton(bool bModifies);`
- L333 _private member_ `bool bSuspendGeometrySelection = false;`
- L335 _private prototype_ `void InitializeGeometrySelectionSystems();`
- L337 _private prototype_ `void OnBuildViewportInteractions(UViewportInteractionsBehaviorSource* Source);`
- L338 _private prototype_ `void PostBuildViewportInteractions(const UViewportInteractionsBehaviorSource* Source);`
- L342 _private member_ `TArray<TObjectPtr<UInteractiveCommand>> ModelingModeCommands;` — `UPROPERTY(NonTransactional)` — Used to keep the command objects alive
- L344 _private member_ `TValueWatcher<bool> GeometrySelectionStateWatcher;`
- L346 _private prototype_ `bool IsGeometrySelectionActive() const;`
- L347 _private prototype_ `bool HasActiveGeometrySelection() const;`
- L348 _private prototype_ `void ToggleGeometrySelectionViewportInteractions(bool bEnable);`
- L351 _private prototype_ `bool IsolateSelection();` — Geometry isolation (return false if no-op)
- L352 _private prototype_ `bool HideSelection();`
- L353 _private prototype_ `bool ShowFullMesh();`
- L355 _private member_ `FString LastActivatedToolName;`
- L357 _private member_ `TMap<FString, TSharedPtr<FUICommandInfo>> ToolIdentifierToCommand;`
- L359 _private prototype_ `void ShowQuickAccessMenu();`
- L368 _private prototype_ `FSkeletonStateFactors GetSkeletonStateFactors();`
- L370 _private member_ `TValueWatcher<FSkeletonStateFactors> SkeletonStateUpdater;`
- L372 _private member_ `int32 ToolReactivateScopeDepth = 0;`

#### enum `USkeletalMeshModelingToolsEditorMode::EToolAcceptAction`  
`enum class EToolAcceptAction: uint8`  
_L161-165_
- L163 _public enumerator_ `ApplyToAsset`
- L164 _public enumerator_ `ExitTool`

#### struct `USkeletalMeshModelingToolsEditorMode::FDesiredSkeletonState`  
`struct FDesiredSkeletonState`  
_L254-259_
- L256 _public member_ `bool bVisible = true;`
- L257 _public member_ `bool bManipulation = true;`

#### struct `USkeletalMeshModelingToolsEditorMode::FSkeletonTreeHostStateFactors`  
`struct FSkeletonTreeHostStateFactors`  
_L267-273_
- L269 _public member_ `bool bEnableDynamicMeshSkeleton = false;`
- L270 _public member_ `bool bIsUsingToolSkeletonWidget = false;`
- L271 _public member_ `bool bActiveToolModifiesSkeleton = false;`

#### struct `USkeletalMeshModelingToolsEditorMode::FSkeletonStateFactors`  
`struct FSkeletonStateFactors`  
_L362-367_
- L364 _public member_ `bool bIsGeometrySelectionActive = false;`
- L365 _public member_ `FDesiredSkeletonState DesiredSkeletonState;`

#### struct `USkeletalMeshModelingToolsEditorMode::FToolReactivateScope`  
`struct FToolReactivateScope`  
_L374-381_
- L376 _public prototype_ `FToolReactivateScope(USkeletalMeshModelingToolsEditorMode* InMode);`
- L377 _public prototype_ `~FToolReactivateScope();`
- L379 _private member_ `USkeletalMeshModelingToolsEditorMode* Mode = nullptr;`
- L380 _private member_ `bool bNeedsReactivate = false;`

#### Free symbols / members of external scopes

- L45 _namespace_ `namespace UE`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsEditorModeToolkit.h` (Private)


#### class `FSkeletalMeshModelingToolsEditorModeToolkit`  
`class FSkeletalMeshModelingToolsEditorModeToolkit : public FModeToolkit`  
_L19-132_
- inherits: `FModeToolkit`
- L27 _public prototype_ `virtual void Init(const TSharedPtr<IToolkitHost>& InToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode) override;` — IToolkit overrides
- L28 _public prototype_ `virtual FName GetToolkitFName() const override;`
- L29 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L30 _public function_ `virtual TSharedPtr<SWidget> GetInlineContent() const override`
- L33 _public prototype_ `virtual void OnToolStarted(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;` — FModeToolkit overrides
- L34 _public prototype_ `virtual void OnToolEnded(UInteractiveToolManager* Manager, UInteractiveTool* Tool) override;`
- L35 _public prototype_ `virtual FText GetActiveToolDisplayName() const override;`
- L36 _public prototype_ `virtual FText GetActiveToolMessage() const override;`
- L37 _public prototype_ `virtual void InvokeUI() override;`
- L38 _public prototype_ `virtual void ShutdownUI() override;`
- L40 _public prototype_ `TArray<FName> GetSelectedBonesForDynamicMeshSkeleton();`
- L41 _public prototype_ `void ResetDynamicMeshBoneTransforms(bool bSelectedOnly);`
- L42 _public prototype_ `void ShowDynamicMeshSkeletonTree();`
- L43 _public prototype_ `void ShowSkeletalMeshSkeletonTree();`
- L44 _public prototype_ `void ShowToolSkeletonTree();`
- L46 _public prototype_ `void EnableDynamicMeshSkeletonCommands();`
- L47 _public prototype_ `void EnableSkeletalMeshSkeletonCommands();`
- L49 _public prototype_ `void DisableEditingCacheSkeletonCommands();` — When tool has its own skeleton, the editing cache skeleton is hidden and shouldn't receive commands like reset bone transforms
- L51 _public prototype_ `bool BindToolSkeletonTree(ISkeletalMeshEditingInterface* InTool);`
- L52 _public prototype_ `void UnbindToolSkeletonTree();`
- L54 _public prototype_ `void RefreshDynamicMeshSkeletonTreeIfNeeded();`
- L56 _private prototype_ `void SetupCommands();`
- L58 _private prototype_ `void PostNotification(const FText& Message);`
- L59 _private prototype_ `void ClearNotification();`
- L61 _private prototype_ `void PostWarning(const FText& Message);`
- L62 _private prototype_ `void ClearWarning();`
- L65 _private prototype_ `void OnEditorModeInitialized();`
- L66 _private prototype_ `void UpdateSelectionColors(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent) const;`
- L68 _private prototype_ `TSharedPtr<SWidget> MakeFooterWidget();`
- L69 _private prototype_ `bool IsApplyButtonEnabled() const;`
- L70 _private prototype_ `FReply OnApplyButtonPressed();`
- L71 _private prototype_ `FText GetApplyButtonText() const;`
- L72 _private prototype_ `bool IsDiscardButtonEnabled() const;`
- L73 _private prototype_ `FReply OnDiscardButtonPressed();`
- L74 _private prototype_ `bool CanChangeAssetEditingSettings() const;`
- L76 _private prototype_ `void UpdateActiveToolProperties(UInteractiveTool* Tool);`
- L78 _private prototype_ `void RegisterPalettes();`
- L79 _private prototype_ `void RegisterExtensionsPalettes() const;`
- L80 _private member_ `FDelegateHandle ActivePaletteChangedHandle;`
- L82 _private prototype_ `void MakeToolAcceptCancelWidget();`
- L84 _private member_ `FText ActiveToolName;`
- L85 _private member_ `FText ActiveToolMessage;`
- L86 _private member_ `FStatusBarMessageHandle ActiveToolMessageHandle;`
- L88 _private member_ `TSharedPtr<SWidget> ToolkitWidget;`
- L89 _private member_ `TSharedPtr<IDetailsView> DetailsView;`
- L91 _private member_ `TSharedPtr<SWidget> ViewportOverlayWidget;`
- L92 _private member_ `const FSlateBrush* ActiveToolIcon = nullptr;`
- L94 _private member_ `TSharedPtr<STextBlock> ModeWarningArea;`
- L95 _private member_ `TSharedPtr<STextBlock> ModeHeaderArea;`
- L96 _private member_ `TSharedPtr<STextBlock> ToolWarningArea;`
- L98 _private member_ `TSharedPtr<SExpandableArea> AssetConfigPanel;`
- L100 _private member_ `TArray<EMeshLODIdentifier> AssetAvailableLODs;`
- L101 _private member_ `TArray<TSharedPtr<FString>> AssetLODModes;`
- L102 _private member_ `TSharedPtr<STextBlock> AssetLODModeLabel;`
- L103 _private member_ `TSharedPtr<STextComboBox> AssetLODMode;`
- L106 _private member_ `TSharedPtr<SWidget> DefaultSkeletonWidget;`
- L107 _private member_ `TSharedPtr<SBorder> DynamicMeshSkeletonWidget;`
- L108 _private member_ `TSharedPtr<SReferenceSkeletonTree> DynamicMeshSkeletonTree;`
- L110 _private member_ `TSharedPtr<SBorder> ToolSkeletonTreeHost;`
- L113 _private member_ `TSharedPtr<SWidget> DefaultMorphTargetWidget;`
- L114 _private member_ `TSharedPtr<SBorder> MorphTargetManagerWidget;`
- L115 _private member_ `TSharedPtr<SMorphTargetManager> MorphTargetManager;`
- L117 _private member_ `TUniquePtr<FSkeletalMeshNotifierBindScope> DynamicMeshSkeletonTreeNotifierBindScope;`
- L119 _private member_ `TWeakObjectPtr<USkeletalMeshModelingToolsEditorMode> EditorMode;`
- L121 _private member_ `FUIAction DefaultResetBoneTransformsAction;`
- L122 _private member_ `FUIAction DefaultResetAllBoneTransformsAction;`
- L131 _private member_ `ESkeletonTabState SkeletonTreeTabState = ESkeletonTabState::DisplayDefaultSkeletalMeshSkeletonTree;`

#### enum `FSkeletalMeshModelingToolsEditorModeToolkit::ESkeletonTabState`  
`enum ESkeletonTabState`  
_L124-129_
- L126 _public enumerator_ `DisplayDefaultSkeletalMeshSkeletonTree`
- L127 _public enumerator_ `DisplayDynamicMeshSkeletonTree`
- L128 _public enumerator_ `DisplayToolSkeletonTree`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsMeshConverter.h` (Private)


#### enum `ERootBonePositionReference`  
`enum class ERootBonePositionReference`  
_L19-23_
- reflection: `UENUM()`
- L21 _public enumerator_ `Relative`
- L22 _public enumerator_ `Absolute`

#### class `USkeletonFromStaticMeshFactory`  
`class USkeletonFromStaticMeshFactory : public UFactory`  
_L27-54_
- reflection: `UCLASS(Hidden, MinimalAPI)`
- inherits: `UFactory`
- L32 _public prototype_ `USkeletonFromStaticMeshFactory(const FObjectInitializer& InObjectInitializer);`
- L35 _public prototype_ `virtual UObject* FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn ) override;` — UFactory overrides
- L44 _public function_ `virtual bool ShouldShowInNewMenu() const override`
- L47 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY()`
- L50 _public member_ `FVector RootPosition = {0.5, 0.5, 0.0};` — `UPROPERTY()`
- L53 _public member_ `ERootBonePositionReference PositionReference = ERootBonePositionReference::Relative;` — `UPROPERTY()`

#### class `USkeletalMeshFromStaticMeshFactory`  
`class USkeletalMeshFromStaticMeshFactory : public UFactory`  
_L58-87_
- reflection: `UCLASS(Hidden, MinimalAPI)`
- inherits: `UFactory`
- L63 _public prototype_ `USkeletalMeshFromStaticMeshFactory(const FObjectInitializer& InObjectInitializer);`
- L66 _public prototype_ `virtual UObject* FactoryCreateNew( UClass* InClass, UObject* InParent, FName InName, EObjectFlags InFlags, UObject* InContext, FFeedbackContext* InWarn ) override;` — UFactory overrides
- L75 _public function_ `virtual bool ShouldShowInNewMenu() const override`
- L77 _public member_ `FReferenceSkeleton ReferenceSkeleton;`
- L80 _public member_ `TObjectPtr<USkeleton> Skeleton;` — `UPROPERTY()`
- L83 _public member_ `TObjectPtr<UStaticMesh> StaticMesh;` — `UPROPERTY()`
- L86 _public member_ `FName BindBoneName;` — `UPROPERTY()`

#### enum `EReferenceSkeletonImportOption`  
`enum class EReferenceSkeletonImportOption`  
_L91-96_
- reflection: `UENUM()`
- L93 _public enumerator_ `CreateNew UMETA(ToolTip="Create a new skeleton with a single root bone")`
- L94 _public enumerator_ `UseExistingSkeleton UMETA(ToolTip="Use an already created skeleton asset")`
- L95 _public enumerator_ `UseExistingSkeletalMesh UMETA(ToolTip="Use a skeleton use by another skeletal mesh asset")`

#### enum `ERootBonePlacementOptions`  
`enum class ERootBonePlacementOptions`  
_L99-104_
- reflection: `UENUM()`
- L101 _public enumerator_ `BottomCenter UMETA(DisplayName="Bottom center", ToolTip="Bottom-center of the static mesh's bounding box")`
- L102 _public enumerator_ `Center UMETA(DisplayName="Center", ToolTip="Center of the static mesh's bounding box")`
- L103 _public enumerator_ `Origin UMETA(DisplayName="Origin", ToolTip="At the static mesh's origin (0,0,0)")`

#### class `UStaticMeshToSkeletalMeshConvertOptions`  
`class UStaticMeshToSkeletalMeshConvertOptions : public UObject, public IBoneReferenceSkeletonProvider`  
_L109-154_
- reflection: `UCLASS(config=EditorPerProjectUserSettings, HideCategories=Object, MinimalAPI)`
- inherits: `UObject,IBoneReferenceSkeletonProvider`
- L116 _public member_ `FDirectoryPath DestinationPath;` — `UPROPERTY(EditAnywhere, Config, Category="Location", meta=(ContentDir))`
- L120 _public member_ `EReferenceSkeletonImportOption SkeletonImportOption = EReferenceSkeletonImportOption::CreateNew;` — `UPROPERTY(EditAnywhere, Config, Category="Skeleton", meta=(DisplayName="Creation Type"))`
- L123 _public member_ `ERootBonePlacementOptions RootBonePlacement = ERootBonePlacementOptions::BottomCenter;` — `UPROPERTY(EditAnywhere, Config, Category="Skeleton", meta=(EditCondition="SkeletonImportOption==EReferenceSkeletonImportOption::CreateNew", EditConditionHides))`
- L126 _public member_ `FSoftObjectPath Skeleton;` — `UPROPERTY(EditAnywhere, Config, Category="Skeleton", meta=(AllowedClasses="/Script/Engine.Skeleton", EditCondition="SkeletonImportOption==EReferenceSkeletonImportOption::UseExistingSkeleton", EditConditionHides))`
- L129 _public member_ `FSoftObjectPath SkeletalMesh;` — `UPROPERTY(EditAnywhere, Config, Category="Skeleton", meta=(AllowedClasses="/Script/Engine.SkeletalMesh", EditCondition="SkeletonImportOption==EReferenceSkeletonImportOption::UseExistingSkeletalMesh", EditConditionHides))`
- L132 _public member_ `FBoneReference BindingBoneName;` — `UPROPERTY(EditAnywhere, Config, Category="Skeleton", meta=(EditCondition="SkeletonImportOption!=EReferenceSkeletonImportOption::CreateNew", EditConditionHides))`
- L135 _public member_ `FString PrefixToRemove = TEXT("SM_` — `UPROPERTY(EditAnywhere, Config, Category="Naming")`
- L138 _public member_ `FString SkeletalMeshPrefixToAdd = TEXT("SKM` — `UPROPERTY(EditAnywhere, Config, Category="Naming", meta=(DisplayName="Skeletal Mesh Prefix"))`
- L141 _public member_ `FString SkeletalMeshSuffixToAdd;` — `UPROPERTY(EditAnywhere, Config, Category="Naming", meta=(DisplayName="Skeletal Mesh Suffix"))`
- L144 _public member_ `FString SkeletonPrefixToAdd = TEXT("SK_` — `UPROPERTY(EditAnywhere, Config, Category="Naming", meta=(DisplayName="Skeleton Prefix", EditCondition="SkeletonImportOption==EReferenceSkeletonImportOption::CreateNew"))`
- L147 _public member_ `FString SkeletonSuffixToAdd;` — `UPROPERTY(EditAnywhere, Config, Category="Naming", meta=(DisplayName="Skeleton Suffix", EditCondition="SkeletonImportOption==EReferenceSkeletonImportOption::CreateNew"))`
- L150 _public prototype_ `virtual USkeleton* GetSkeleton(bool& bInvalidSkeletonIsError, const IPropertyHandle* PropertyHandle) override;` — IBoneReferenceSkeletonProvider implementation.
- L153 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — UObject overrides.

#### Free symbols / members of external scopes

- L158 _prototype_ `void ConvertStaticMeshAssetsToSkeletalMeshesInteractive(const TArray<FAssetData>& InStaticMeshAssets);` — Converts a static mesh to a skeletal mesh, creating both a skeletal mesh and a skeleton assets that link up.

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsModule.h` (Private)


#### class `FSkeletalMeshModelingToolsModule`  
`class FSkeletalMeshModelingToolsModule : public IModuleInterface`  
_L17-50_
- inherits: `IModuleInterface`
- L22 _public prototype_ `void StartupModule() override;` — IModuleInterface implementations
- L23 _public prototype_ `void ShutdownModule() override;`
- L27 _private prototype_ `void RegisterMenusAndToolbars();` — Extend toolbars and menus
- L29 _private prototype_ `TSharedRef<FExtender> ExtendSkelMeshEditorToolbar(const TSharedRef<FUICommandList> InCommandList, TSharedRef<ISkeletalMeshEditor> InSkeletalMeshEditor);`
- L32 _private prototype_ `bool IsEditingToolModeActive(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor) const;`
- L33 _private prototype_ `void OnToggleEditingToolsMode(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor);`
- L34 _private prototype_ `void CheckEnableEditingToolModeOnOpen(TWeakPtr<ISkeletalMeshEditor> InSkeletalMeshEditor);`
- L35 _private prototype_ `bool IsMeshEditable(TWeakPtr<ISkeletalMeshEditor> InSkeletonEditor);`
- L37 _private prototype_ `void OnPostEngineInit();`
- L39 _private prototype_ `void RegisterPropertyCustomizations();`
- L40 _private prototype_ `void UnregisterPropertyCustomizations();`
- L42 _private member_ `TArray<FName> CustomizedProperties;`
- L43 _private member_ `TArray<FName> CustomizedClasses;`
- L46 _private member_ `FDelegateHandle SkelMeshEditorExtenderHandle;` — The handle for the extender delegate we added. Needed for clean module shutdown.
- L47 _private member_ `FDelegateHandle SkelMeshEditorPostInitHandle;`
- L49 _private member_ `TArray<TWeakPtr<FApplicationMode>> RegisteredApplicationModes;`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshModelingTools, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogSkeletalMeshModelingTools, Log, All);`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsStyle.h` (Private)


#### class `FSkeletalMeshModelingToolsStyle`  
`class FSkeletalMeshModelingToolsStyle : public FSlateStyleSet`  
_L8-22_
- inherits: `FSlateStyleSet`
- L12 _public prototype_ `static FSkeletalMeshModelingToolsStyle& Get();`
- L17 _protected prototype_ `static void Register();`
- L18 _protected prototype_ `static void Unregister();`
- L21 _private prototype_ `FSkeletalMeshModelingToolsStyle();`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/SkeletalMeshModelingToolsViewportToolbarExtension.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace SkeletalMeshModelingTools` (scope `UE`)
- L12 _prototype_ `void ExtendSkeletalMeshEditorViewportToolbar( USkeletalMeshModelingToolsEditorMode& EdMode, const TSharedRef<FUICommandList>& CommandList);` (scope `UE::SkeletalMeshModelingTools`)
- L16 _prototype_ `void RemoveSkeletalMeshEditorViewportToolbarExtensions();` (scope `UE::SkeletalMeshModelingTools`)

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/ToolTargets/SKMBackedDynaMeshComponentToolTarget.h` (Private)


#### class `USkeletalMeshBackedDynamicMeshComponentToolTarget`  
`class USkeletalMeshBackedDynamicMeshComponentToolTarget : public UDynamicMeshComponentToolTarget, public ISkeletalMeshBackedTarget`  
_L18-38_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDynamicMeshComponentToolTarget,ISkeletalMeshBackedTarget`
- L24 _public prototype_ `virtual FReferenceSkeleton GetSkeleton() const override;`
- L25 _public prototype_ `virtual void CommitSkeletonModifier(USkeletonModifier* InModifier) override;`
- L27 _public prototype_ `virtual void CommitDynamicMeshChange(TUniquePtr<FToolCommandChange> Change, const FText& ChangeMessage) override;`
- L29 _public prototype_ `virtual USkeletalMesh* GetSkeletalMesh() const override;`
- L31 _public prototype_ `virtual void SetOwnerVisibility(bool bVisible) const override;`
- L33 _protected prototype_ `USkeletalMeshBackedDynamicMeshComponent* GetComponent() const;`
- L35 _protected member_ `TWeakObjectPtr<USkeletalMesh> WeakSkeletalMesh;`

#### class `USkeletalMeshBackedDynamicMeshComponentToolTargetFactory`  
`class USkeletalMeshBackedDynamicMeshComponentToolTargetFactory : public UDynamicMeshComponentToolTargetFactory`  
_L41-55_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDynamicMeshComponentToolTargetFactory`
- L46 _public prototype_ `void Init(ISkeletalMeshBackedDynamicMeshComponentProvider* InComponentProvider);`
- L48 _public prototype_ `virtual bool CanBuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) const override;`
- L50 _public prototype_ `virtual UToolTarget* BuildTarget(UObject* SourceObject, const FToolTargetTypeRequirements& TargetTypeInfo) override;`
- L52 _public prototype_ `static bool CanWriteToSource(const UObject* SourceObject);`
- L54 _public member_ `TWeakInterfacePtr<ISkeletalMeshBackedDynamicMeshComponentProvider> ComponentProvider;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API SKELETALMESHMODELINGTOOLS_API`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/Tools/SKMRunMeshProcessorBlueprintTool.h` (Private)


#### class `USkeletalMeshRunMeshProcessorBlueprintToolProperties`  
`class USkeletalMeshRunMeshProcessorBlueprintToolProperties : public UInteractiveToolPropertySet`  
_L27-47_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L32 _public member_ `bool bPreviewOnly = true;` — `UPROPERTY(EditAnywhere, Category = "Mode", meta = (TransientToolProperty))`
- L35 _public member_ `TSubclassOf<UEditorDynamicMeshProcessorBlueprint> ProcessorBlueprintClass;` — `UPROPERTY(EditAnywhere, DisplayName = "Dyanmic Mesh Processor Blueprint", Category = "Processor")`
- L40 _public member_ `TObjectPtr<UDynamicMeshProcessorBlueprint> ProcessorInstance;` — `UPROPERTY(EditAnywhere, Instanced, NoClear, Category = "Processor", meta = (ShowOnlyInnerProperties, EditConditionHides, HideEditConditionToggle, EditCondition = "ShouldShowProcessorInstance"))`
- L46 _public prototype_ `bool ShouldShowProcessorInstance() const;` — `UFUNCTION()` — Returns true only when the picked subclass exposes at least one BlueprintVisible editable property — otherwise the instance section would render as an empty header. Inherited C++ UPROPERTYs that aren't BlueprintVisible (e.g. the base class's bRequiresGameThread) don't count.

#### class `USkeletalMeshRunMeshProcessorBlueprintToolBuilder`  
`class USkeletalMeshRunMeshProcessorBlueprintToolBuilder : public UInteractiveToolBuilder`  
_L51-58_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolBuilder`
- L55 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L56 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L57 _public prototype_ `virtual const FToolTargetTypeRequirements& GetTargetRequirements() const;`

#### class `USkeletalMeshRunMeshProcessorBlueprintTool`  
`class USkeletalMeshRunMeshProcessorBlueprintTool : public USingleSelectionTool, public ISkeletalMeshGeometryIsolationAwareTool, public IInteractiveToolManageGeometrySelectionAPI`  
_L65-136_
- reflection: `UCLASS()`
- inherits: `USingleSelectionTool,ISkeletalMeshGeometryIsolationAwareTool,IInteractiveToolManageGeometrySelectionAPI`
- desc: Run Mesh Processor Blueprint tool.
- L72 _public prototype_ `virtual void Setup() override;`
- L73 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L74 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L75 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L77 _public function_ `virtual bool HasCancel() const override`
- L78 _public function_ `virtual bool HasAccept() const override`
- L79 _public prototype_ `virtual bool CanAccept() const override;`
- L81 _public prototype_ `void SetWorld(UWorld* InWorld);`
- L83 _public function_ `virtual bool IsInputIsolationValidOnOutput() const override`
- L84 _public function_ `virtual bool IsInputSelectionValidOnOutput() override`
- L88 _protected member_ `TObjectPtr<USkeletalMeshRunMeshProcessorBlueprintToolProperties> Settings;` — `UPROPERTY()`
- L91 _protected member_ `TObjectPtr<UDynamicMesh> ToolDynamicMesh;` — `UPROPERTY()`
- L94 _protected member_ `TObjectPtr<UPreviewMesh> PreviewMesh;` — `UPROPERTY()`
- L97 _protected member_ `TWeakObjectPtr<USkeletalMeshEditorContextObjectBase> EditorContext;` — `UPROPERTY()`
- L100 _protected member_ `TWeakObjectPtr<UWorld> TargetWorld;` — `UPROPERTY()`
- L106 _protected member_ `UE::Geometry::FDynamicMesh3 FullSourceMesh;` — Pristine full-mesh copy taken once at Setup. ProcessorInputMesh is rebuilt from this on Setup and whenever bPreviewOnly toggles: in preview-only mode we extract the isolated submesh (so the BP only operates on the visible region); when committing, we run the BP against the full mesh because the result will be written back to the whole asset.
- L107 _protected member_ `TArray<int32> IsolatedTriangles;`
- L108 _protected member_ `UE::Geometry::FDynamicMesh3 ProcessorInputMesh;`
- L109 _protected member_ `TArray<FTransform> ComponentSpaceTransformsRefPose;`
- L111 _protected member_ `SkeletalMeshToolsHelper::FPoseChangeDetector PoseChangeDetector;`
- L112 _protected member_ `bool bFastDeformPreviewMesh = false;`
- L114 _protected prototype_ `void RebuildProcessorInstance(TSubclassOf<UEditorDynamicMeshProcessorBlueprint> NewClass);`
- L115 _protected prototype_ `void RebuildProcessorInputMesh();`
- L116 _protected prototype_ `void RunProcessorAndUpdatePreview();`
- L117 _protected prototype_ `void PosePreviewMesh( const TArray<FTransform>& ComponentSpaceTransforms, const TMap<FName, float>& MorphTargetWeights);`
- L121 _protected prototype_ `void HandlePoseChangeDetectorEvent(SkeletalMeshToolsHelper::FPoseChangeDetector::FPayload Payload);`
- L124 _protected prototype_ `void SubscribeToBlueprintCompile(UClass* GeneratedClass);` — Refresh the instance and re-run the processor when the BP author recompiles their graph.
- L125 _protected prototype_ `void UnsubscribeFromBlueprintCompile();`
- L126 _protected prototype_ `void HandleBlueprintCompiled(UBlueprint* InBlueprint);`
- L128 _protected member_ `TWeakObjectPtr<UBlueprint> CurrentProcessorBlueprint;`
- L129 _protected member_ `FDelegateHandle BlueprintCompiledHandle;`
- L131 _protected prototype_ `const TArray<FTransform>& GetComponentSpaceBoneTransforms();`
- L132 _protected prototype_ `TMap<FName, float> GetMorphTargetWeights();`
- L135 _protected member_ `TArray<FTransform> DefaultComponentSpaceBoneTransforms;` — Fallback when EditorContext is unavailable.

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/ViewportInteractions/SKMModelingToolsGeometryClickSelection.h` (Private)


#### class `USkeletalMeshModelingToolsGeometryClickSelection`  
`class USkeletalMeshModelingToolsGeometryClickSelection : public UViewportClickInteraction`  
_L11-28_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportClickInteraction`
- L17 _public prototype_ `USkeletalMeshModelingToolsGeometryClickSelection();`
- L18 _public prototype_ `virtual void BuildBehaviors() override;`
- L19 _public prototype_ `virtual void OnClickUp(const FInputDeviceRay& InClickPos) override;`
- L21 _public prototype_ `void BindSelectionManager(UGeometrySelectionManager* InSelectionManager);`
- L23 _public function_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override`
- L27 _protected member_ `TWeakObjectPtr<UGeometrySelectionManager> SelectionManager;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/ViewportInteractions/SKMModelingToolsGeometryDoubleClickSelection.h` (Private)


#### class `USkeletalMeshModelingToolsGeometryDoubleClickBehavior`  
`class USkeletalMeshModelingToolsGeometryDoubleClickBehavior : public UViewportClickBehavior`  
_L13-21_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportClickBehavior`
- L18 _protected prototype_ `virtual TOptional<FInputCapturePriority> GetCapturePriority( UE::Editor::ViewportInteractions::EInputStage Stage, const FInputDeviceState& InputState) const override;`

#### class `USkeletalMeshModelingToolsGeometryDoubleClickSelection`  
`class USkeletalMeshModelingToolsGeometryDoubleClickSelection : public UViewportClickInteraction`  
_L24-43_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportClickInteraction`
- L30 _public prototype_ `USkeletalMeshModelingToolsGeometryDoubleClickSelection();`
- L31 _public prototype_ `virtual void BuildBehaviors() override;`
- L32 _public prototype_ `virtual void OnClickUp(const FInputDeviceRay& InClickPos) override;`
- L34 _public prototype_ `void BindSelection( UGeometrySelectionManager* InSelectionManager, TFunction<UPrimitiveComponent*()> InGetEditingComponent);`
- L38 _public function_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override`
- L41 _protected member_ `TWeakObjectPtr<UGeometrySelectionManager> SelectionManager;`
- L42 _protected member_ `TFunction<UPrimitiveComponent*()> GetEditingComponent;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/ViewportInteractions/SKMModelingToolsGeometryFrustumSelection.h` (Private)


#### class `USkeletalMeshModelingToolsGeometryFrustumSelection`  
`class USkeletalMeshModelingToolsGeometryFrustumSelection : public UFrustumSelectInteraction`  
_L11-27_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UFrustumSelectInteraction`
- L16 _public prototype_ `USkeletalMeshModelingToolsGeometryFrustumSelection();`
- L18 _public prototype_ `void BindSelectionManager(UGeometrySelectionManager* InSelectionManager);`
- L20 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;`
- L21 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InReleasePos) override;`
- L23 _public function_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override`
- L26 _protected member_ `TWeakObjectPtr<UGeometrySelectionManager> SelectionManager;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/ViewportInteractions/SKMModelingToolsGeometryHoverInteraction.h` (Private)


#### class `USkeletalMeshModelingToolsGeometryHoverInteraction`  
`class USkeletalMeshModelingToolsGeometryHoverInteraction : public UViewportInteraction , public IHoverBehaviorTarget`  
_L13-50_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportInteraction,IHoverBehaviorTarget`
- L20 _public prototype_ `USkeletalMeshModelingToolsGeometryHoverInteraction();`
- L22 _public prototype_ `void BindSelectionManager(UGeometrySelectionManager* InSelectionManager);`
- L27 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — Do hover hit-test
- L32 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;` — Initialize hover sequence at given position
- L37 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;` — Update active hover sequence with new input position
- L42 _public prototype_ `virtual void OnEndHover() override;` — Terminate active hover sequence
- L46 _protected member_ `TObjectPtr<UMouseHoverBehavior> HoverBehavior;` — `UPROPERTY()`
- L48 _protected member_ `TWeakObjectPtr<UGeometrySelectionManager> SelectionManager;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/ViewportInteractions/SKMModelingToolsGeometrySoftSelectRadiusDrag.h` (Private)


#### class `USkeletalMeshModelingToolsGeometrySoftSelectRadiusDragInteraction`  
`class USkeletalMeshModelingToolsGeometrySoftSelectRadiusDragInteraction : public UDragToolInteraction`  
_L12-38_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDragToolInteraction`
- L18 _public prototype_ `USkeletalMeshModelingToolsGeometrySoftSelectRadiusDragInteraction();`
- L20 _public prototype_ `void BindSelectionManager(UGeometrySelectionManager* InSelectionManager);`
- L22 _public prototype_ `virtual void Draw(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L25 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L26 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InPressPos) override;`
- L27 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) override;`
- L28 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InReleasePos) override;`
- L32 _protected function_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override`
- L35 _protected member_ `double StartingRadius = 0;`
- L37 _protected member_ `TWeakObjectPtr<UGeometrySelectionManager> SelectionManager;`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/Widgets/SSKMEnumPropertyComboBox.h` (Private)


#### class `UE::SkeletalMeshModelingTools::SSKMEnumPropertyComboBox`  
`template <typename TEnumType> class SSKMEnumPropertyComboBox : public SCompoundWidget`  
_L15-180_
- inherits: `SCompoundWidget`
- desc: A combo box for enum values. Useful to exclude elements
- L19 _public function_ `SLATE_BEGIN_ARGS(SSKMEnumPropertyComboBox<TEnumType>)`
- L23 _public prototype_ `SLATE_ATTRIBUTE(EVisibility, Visibility);` — The visibility attribute for this widget
- L26 _public prototype_ `SLATE_ATTRIBUTE(bool, IsEnabled);` — The enabled attribute for this widget. Only considered when the enum property handle is editable
- L29 _public prototype_ `SLATE_ARGUMENT(TSet<TEnumType>, ExcludedEnumerators);` — Enumerators that should be excluded from the combo box
- L31 _public function_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<IPropertyHandle>& InEnumPropertyHandle)`
- L100 _private function_ `bool IsEnabled() const` — Returns true if the widget is enabled
- L117 _private function_ `int32 GetValue() const` — Returns the currently selected axis
- L148 _private function_ `void SetValue(int32 EnumValue, ESelectInfo::Type SelectInfo)` — Called when an axis was selected
- L173 _private member_ `const FFieldClass* UnderlyingType = nullptr;` — The size type of the enum
- L176 _private member_ `TAttribute<bool> IsEnabledAttribute;` — The enabled attribute for this widget. Only considered when the enum property handle is editable.
- L179 _private member_ `TSharedPtr<IPropertyHandle> EnumPropertyHandle;` — The property handle to the enum

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace SkeletalMeshModelingTools` (scope `UE`)
- L43 _function_ `` (scope `UE::SkeletalMeshModelingTools::SSKMEnumPropertyComboBox::SLATE_END_ARGS`)

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Private/Widgets/SSKMQuickAccessMenu.h` (Private)


#### class `SSkeletalMeshModelingToolsQuickAccessMenu`  
`class SSkeletalMeshModelingToolsQuickAccessMenu : public SCompoundWidget`  
_L17-27_
- inherits: `SCompoundWidget`
- desc: Thin Slate host for the Skeletal Mesh Modeling Tools quick-access menu.
- L20 _public function_ `SLATE_BEGIN_ARGS(SSkeletalMeshModelingToolsQuickAccessMenu)`
- L22 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, CommandList) SLATE_EVENT(FOnPopulateSKMQuickAccessMenu, OnPopulateMenu) SLATE_END_ARGS() void Construct(const FArguments& InArgs);` — Should be the toolkit's command list so existing MapAction handlers fire when entries are clicked.

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DELEGATE_OneParam(FOnPopulateSKMQuickAccessMenu, FMenuBuilder& );`
- L12 _prototype_ `DECLARE_DELEGATE_OneParam(FOnPopulateSKMQuickAccessMenu, FMenuBuilder& );`

### `Plugins/Animation/SkeletalMeshModelingTools/Source/SkeletalMeshModelingTools/Public/SkeletalMeshModelingModeToolExtensions.h` (Public)


#### class `ISkeletalMeshModelingModeToolExtension`  
`class ISkeletalMeshModelingModeToolExtension : public IModelingModeToolExtension`  
_L15-25_
- inherits: `IModelingModeToolExtension`
- desc: ISkeletalMeshModelingModeToolExtension uses the IModularFeature API to allow a Plugin to provide a set of InteractiveTool's to be exposed in SkeletalMesh Modeling Mode. The Tools will be included in a section of the SkeletalMesh Modeling Mode tool list, based on GetToolSectionName().
- L18 _public prototype_ `virtual ~ISkeletalMeshModelingModeToolExtension() override = default;`
- L20 _public function_ `static FName GetModularFeatureName()`
