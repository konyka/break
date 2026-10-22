# Plugins / ChaosVDBuiltInExtensions

- module root: `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions`
- headers: 32; symbols: 543
- symbol kinds: class=34, enum=9, enumerator=33, function=23, member=181, namespace=8, prototype=232, struct=15, typedef=6, variable=2
- PrivateDependencyModuleNames: AppFramework, ChaosVDData, ChaosVDRuntime, Core, CoreUObject, EditorWidgets, Engine, InputCore, Slate, SlateCore, ToolMenus, TraceServices, TypedElementFramework, UnrealEd
- PublicDependencyModuleNames: ChaosVD

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/AccelerationStructures/ChaosVDAccelerationStructuresExtension.h` (Private)


#### class `FChaosVDAccelerationStructuresExtension`  
`class FChaosVDAccelerationStructuresExtension final : public FChaosVDExtension`  
_L14-27_
- inherits: `FChaosVDExtension`
- L18 _public prototype_ `FChaosVDAccelerationStructuresExtension();`
- L21 _public prototype_ `virtual void RegisterDataProcessorsInstancesForProvider(const TSharedRef<FChaosVDTraceProvider>& InTraceProvider) override;`
- L22 _public prototype_ `virtual TConstArrayView<TSubclassOf<UActorComponent>> GetSolverDataComponentsClasses() override;`
- L23 _public prototype_ `virtual void RegisterComponentVisualizers(const TSharedRef<SChaosVDMainTab>& InCVDToolKit) override;`
- L26 _private member_ `TArray<TSubclassOf<UActorComponent>> DataComponentsClasses;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/AccelerationStructures/Components/ChaosVDGTAccelerationStructuresDataComponent.h` (Private)


#### class `UChaosVDGTAccelerationStructuresDataComponent`  
`class UChaosVDGTAccelerationStructuresDataComponent : public UChaosVDSolverDataComponent`  
_L12-30_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- L18 _public prototype_ `UChaosVDGTAccelerationStructuresDataComponent();` — Sets default values for this component's properties
- L20 _public prototype_ `void UpdateAABBTreeData(TConstArrayView<TSharedPtr<FChaosVDAABBTreeDataWrapper>> AABBTreeDataView);`
- L22 _public function_ `TConstArrayView<TSharedPtr<FChaosVDAABBTreeDataWrapper>> GetAABBTreeData() const`
- L24 _public prototype_ `virtual void UpdateFromNewGameFrameData(const FChaosVDGameFrameData& InGameFrameData) override;`
- L26 _public prototype_ `virtual void ClearData() override;`
- L29 _protected member_ `TArray<TSharedPtr<FChaosVDAABBTreeDataWrapper>> RecordedABBTreeData;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/AccelerationStructures/Settings/ChaosVDAccelerationStructureVisualizationSettings.h` (Private)


#### enum `EChaosVDAccelerationStructureDataVisualizationFlags`  
`enum class EChaosVDAccelerationStructureDataVisualizationFlags : uint32`  
_L10-33_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Visualization flags used to control what is debug draw of the recorded acceleration structure data
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L14 _public enumerator_ `DrawNodesBounds = 1 << 0` — If Set, draws the bound of all nodes in the tree
- L16 _public enumerator_ `DrawBranches = 1 << 1` — If Set, draws lines to represent the branches of the tree
- L18 _public enumerator_ `DrawLeavesBounds = 1 << 2` — If Set, draws the bounds of the leaves of the tree
- L20 _public enumerator_ `DrawLeavesElementBounds = 1 << 3` — If Set, draws the bounds of each element in the leaves of the tree
- L22 _public enumerator_ `DrawLeavesElementConnections = 1 << 4` — If Set, inside each leaf bound, it draws lines from the elements to the center of the leaf bounds
- L24 _public enumerator_ `DrawDynamicTrees = 1 << 5` — If Set, all dynamic trees will be drawn
- L26 _public enumerator_ `DrawStaticTrees = 1 << 6` — If Set, all static trees will be drawn
- L29 _public enumerator_ `DrawLeavesRealElementBounds = 1 << 7 UMETA(Hidden)` — If Set, draws the real bounds of each element (not the bounds recorded in the leaf) in the leaves of the tree - This should match the bounds recorded in the leaf itself, otherwise it means the AABBtree might have out of sync data
- L32 _public enumerator_ `EnableDraw = DrawDynamicTrees | DrawStaticTrees` — If set, enabled debug drawing for any recorded acceleration structure available at the current visualized frame

#### class `UChaosVDAccelerationStructureVisualizationSettings`  
`class UChaosVDAccelerationStructureVisualizationSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L40-60_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- desc: Settings object that stores the values that control how acceleration structures are debug drawn
- L47 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — The depth priority used for while drawing contact data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L51 _public member_ `float BaseThickness = 3.0f;` — `UPROPERTY(EditAnywhere, config, Category=DebugDraw)` — The base thickness used to draw node bounds
- L53 _public prototype_ `static void SetDataVisualizationFlags(EChaosVDAccelerationStructureDataVisualizationFlags NewFlags);`
- L54 _public prototype_ `static EChaosVDAccelerationStructureDataVisualizationFlags GetDataVisualizationFlags();`
- L56 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L59 _private member_ `uint32 AccelerationStructureDataVisualizationFlags = static_cast<uint32>(EChaosVDAccelerationStructureDataVisualizationFlags::DrawNodesBounds | EChaosVDAccelerationStructureDataVisualizationFlags::DrawBranches);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVD.EChaosVDAccelerationStructureDataVisualizationFlags"))`

#### Free symbols / members of external scopes

- L34 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDAccelerationStructureDataVisualizationFlags);`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/AccelerationStructures/Trace/ChaosVDAABBTreeDataProcessor.h` (Private)


#### class `FChaosVDAABBTreeDataProcessor`  
`class FChaosVDAABBTreeDataProcessor final : public FChaosVDDataProcessorBase`  
_L9-15_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced AABB Tree Data
- L12 _public prototype_ `explicit FChaosVDAABBTreeDataProcessor();`
- L14 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/AccelerationStructures/Visualizers/ChaosVDGTAccelerationStructureDataComponentVisualizer.h` (Private)


#### enum `EChaosVDVisibleAABBTreeNodes`  
`enum class EChaosVDVisibleAABBTreeNodes`  
_L15-20_
- L17 _public enumerator_ `None = 0`
- L18 _public enumerator_ `Left = 1 << 0`
- L19 _public enumerator_ `Right = 1 << 1`

#### struct `FChaosVDAABBTreeSelectionContext`  
`struct FChaosVDAABBTreeSelectionContext`  
_L24-35_
- reflection: `USTRUCT()`
- L28 _public member_ `const FChaosVDAABBTreeNodeDataWrapper* NodeData = nullptr;`
- L29 _public member_ `const FChaosVDAABBTreeLeafDataWrapper* LeafData = nullptr;`
- L31 _public function_ `bool operator==(const FChaosVDAABBTreeSelectionContext& Other) const`

#### struct `FChaosVDGTAccelerationStructureSelectionHandle`  
`struct FChaosVDGTAccelerationStructureSelectionHandle : public FChaosVDSolverDataSelectionHandle`  
_L37-47_
- inherits: `FChaosVDSolverDataSelectionHandle`
- L39 _public prototype_ `virtual bool IsSelected() override;`
- L40 _public prototype_ `void CreateStructViewForDetailsPanelIfNeeded();`
- L42 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomDataReadOnlyStructViewForDetails() override;`
- L45 _private member_ `TSharedPtr<FChaosVDSelectionMultipleView> StructDataView;`
- L46 _private member_ `TSharedPtr<FStructOnScope> StructDataViewStructOnScope;`

#### struct `FChaosGTAccelerationStructureVisualizationDataContext`  
`struct FChaosGTAccelerationStructureVisualizationDataContext : public FChaosVDVisualizationContext`  
_L50-63_
- inherits: `FChaosVDVisualizationContext`
- desc: Visualization context structure specific for acceleration structure visualizations
- L52 _public member_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> DataSelectionHandle = MakeShared<FChaosVDSolverDataSelectionHandle>();`
- L54 _public member_ `ESceneDepthPriorityGroup DepthPriority = SDPG_Foreground;`
- L56 _public member_ `const UChaosVDGTAccelerationStructuresDataComponent* DataComponent = nullptr;`
- L58 _public function_ `bool IsVisualizationFlagEnabled(EChaosVDAccelerationStructureDataVisualizationFlags Flag) const`

#### class `FChaosVDGTAccelerationStructureDataComponentVisualizer`  
`class FChaosVDGTAccelerationStructureDataComponentVisualizer final : public FChaosVDComponentVisualizerBase`  
_L65-81_
- inherits: `FChaosVDComponentVisualizerBase`
- L68 _public prototype_ `FChaosVDGTAccelerationStructureDataComponentVisualizer();`
- L70 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L72 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L74 _public prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override;`
- L78 _protected prototype_ `void DrawAABBTree(const FSceneView* View, FPrimitiveDrawInterface* PDI, const FChaosGTAccelerationStructureVisualizationDataContext& VisualizationContext, const TSharedRef<FChaosVDAABBTreeDataWrapper>& AABBTreeData);`
- L79 _protected prototype_ `void DrawAABBTreeNode(const FSceneView* View, FPrimitiveDrawInterface* PDI, const FChaosGTAccelerationStructureVisualizationDataContext& VisualizationContext, const TSharedRef<FChaosVDAABBTreeDataWrapper>& AABBTreeData, const FChaosVDAABBTreeNodeDataWrapper& AABBTreeNodeData, float Thickness, int32 CurrentTreeLevel = 1);`
- L80 _protected prototype_ `void DrawAABBTreeArrayLeaf(const FSceneView* View, FPrimitiveDrawInterface* PDI, const FChaosGTAccelerationStructureVisualizationDataContext& VisualizationContext, const FChaosVDAABBTreeLeafDataWrapper& AABBTreeArrayLeafData, const TSharedRef<FChaosVDAABBTreeDataWrapper>& AABBTreeData, float Thickness);`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/CameraTraces/ChaosVDCameraTracesExtension.h` (Private)


#### class `FChaosVDCameraTracesExtension`  
`class FChaosVDCameraTracesExtension final : public FChaosVDExtension, public TSharedFromThis<FChaosVDCameraTracesExtension>`  
_L20-60_
- inherits: `FChaosVDExtension,TSharedFromThis<FChaosVDCameraTracesExtension>`
- L24 _public prototype_ `FChaosVDCameraTracesExtension();`
- L27 _public prototype_ `virtual void RegisterDataProcessorsInstancesForProvider(const TSharedRef<FChaosVDTraceProvider>& InTraceProvider) override;`
- L28 _public prototype_ `virtual TConstArrayView<TSubclassOf<UActorComponent>> GetSolverDataComponentsClasses() override;`
- L29 _public prototype_ `virtual void RegisterComponentVisualizers(const TSharedRef<SChaosVDMainTab>& InCVDToolKit) override;`
- L30 _public prototype_ `virtual void PostMainTabInitialization(const TSharedRef<SChaosVDMainTab>& InParentTabWidget) override;`
- L31 _public prototype_ `virtual void HandleRecordingFirstFrameLoaded(TWeakPtr<FChaosVDPlaybackController> InController) override;`
- L40 _protected member_ `TWeakPtr<FChaosVDScene> WeakScenePtr;`
- L41 _protected member_ `TWeakPtr<FEditorModeTools> EditorModeToolsWeakPtr;`
- L43 _protected member_ `TOptional<FChaosVDCameraIdentifier> SelectedCamera;`
- L44 _protected member_ `bool bViewportStartAtCameraTrace = true;`
- L45 _protected member_ `static const FName ChaosViewportType;`
- L46 _protected member_ `static const FName CameraSeparatorName;`
- L48 _protected prototype_ `void SetTrackedCamera(FChaosVDCameraIdentifier InTargetCamera);`
- L49 _protected prototype_ `void ClearTrackedCamera();`
- L50 _protected prototype_ `bool FindCameraData(FVector& Position, FQuat& Rotation, float& FieldOfView, ECameraFindFlags CameraFindFlags) const;`
- L51 _protected prototype_ `void HandleCVDSceneUpdated();`
- L52 _protected prototype_ `void OnSolverVisibilityUpdated(int32 SolverID, bool bNewVisibility);`
- L53 _protected prototype_ `void CreateCameraTracesMenu();`
- L54 _protected prototype_ `void HandleSettingsChanged(UObject* SettingsObject);`
- L55 _protected prototype_ `void ToggleOffObjectTracking();`
- L56 _protected prototype_ `FChaosVDPlaybackViewportClient* GetPlaybackViewportClient();`
- L59 _private member_ `TArray<TSubclassOf<UActorComponent>> DataComponentsClasses;`

#### enum `FChaosVDCameraTracesExtension::ECameraFindFlags`  
`enum class ECameraFindFlags : uint8`  
_L34-38_
- L36 _public enumerator_ `Default`
- L37 _public enumerator_ `FindFirst`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/CameraTraces/Components/ChaosVDCameraDataComponent.h` (Private)


#### class `UChaosVDCameraDataComponent`  
`class UChaosVDCameraDataComponent : public UChaosVDSolverDataComponent`  
_L12-33_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- L18 _public prototype_ `UChaosVDCameraDataComponent();` — Sets default values for this component's properties
- L20 _public prototype_ `void UpdateCameraData(TConstArrayView<TSharedPtr<FChaosVDCameraDataWrapper>> CameraDataView);`
- L22 _public function_ `TConstArrayView<TSharedPtr<FChaosVDCameraDataWrapper>> GetCameraData() const`
- L27 _public prototype_ `virtual void UpdateFromNewGameFrameData(const FChaosVDGameFrameData& InGameFrameData) override;`
- L29 _public prototype_ `virtual void ClearData() override;`
- L32 _protected member_ `TArray<TSharedPtr<FChaosVDCameraDataWrapper>> RecordedCameraData;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/CameraTraces/Settings/ChaosVDCameraDataSettings.h` (Private)


#### enum `EChaosVDCameraDataVisualizationFlags`  
`enum class EChaosVDCameraDataVisualizationFlags : uint32`  
_L10-14_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Set of visualization flags options for camera data
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L13 _public enumerator_ `EnableDraw = 1 << 0`

#### class `UChaosVDCameraDataSettings`  
`class UChaosVDCameraDataSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L18-48_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L26 _public member_ `bool bViewportStartAtCameraTrace = true;` — `UPROPERTY(config, EditAnywhere, Category = DebugDraw)` — If true and if there is an existing camera trace, the initial viewport position will be at the rather than at the world origin
- L30 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — The depth priority used for while drawing data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L34 _public member_ `float DirectionVectorScale = 2.0f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Length of the camera direction vector when drawn.
- L36 _public prototype_ `static void SetDataVisualizationFlags(EChaosVDCameraDataVisualizationFlags NewFlags);`
- L37 _public prototype_ `static EChaosVDCameraDataVisualizationFlags GetDataVisualizationFlags();`
- L39 _public prototype_ `static void SetViewportStartAtCameraTrace(bool bInViewportStartAtCameraTrace);`
- L41 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L47 _private member_ `uint32 DebugDrawFlags = static_cast<uint32>(EChaosVDCameraDataVisualizationFlags::None);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVDBuiltInExtensions.EChaosVDCameraDataVisualizationFlags"))` — Set of flags to enable/disable visualization of debug draw data shapes

#### Free symbols / members of external scopes

- L15 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDCameraDataVisualizationFlags);`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/CameraTraces/Trace/ChaosVDCameraDataProcessor.h` (Private)


#### class `FChaosVDCameraDataProcessor`  
`class FChaosVDCameraDataProcessor final : public FChaosVDDataProcessorBase`  
_L10-16_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced camera data
- L13 _public prototype_ `explicit FChaosVDCameraDataProcessor();`
- L15 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/CameraTraces/Visualizers/ChaosVDCameraDataComponentVisualizer.h` (Private)


#### struct `FChaosVDCameraSelectionContext`  
`struct FChaosVDCameraSelectionContext`  
_L14-24_
- reflection: `USTRUCT()`
- L18 _public member_ `const FChaosVDCameraDataWrapper* CameraData = nullptr;`
- L20 _public function_ `bool operator==(const FChaosVDCameraSelectionContext& Other) const`

#### struct `FChaosVDCameraSelectionHandle`  
`struct FChaosVDCameraSelectionHandle : public FChaosVDSolverDataSelectionHandle`  
_L26-36_
- inherits: `FChaosVDSolverDataSelectionHandle`
- L28 _public prototype_ `virtual bool IsSelected() override;`
- L29 _public prototype_ `void CreateStructViewForDetailsPanelIfNeeded();`
- L31 _public prototype_ `virtual TSharedPtr<FStructOnScope> GetCustomDataReadOnlyStructViewForDetails() override;`
- L34 _private member_ `TSharedPtr<FChaosVDSelectionMultipleView> StructDataView;`
- L35 _private member_ `TSharedPtr<FStructOnScope> StructDataViewStructOnScope;`

#### struct `FChaosVDCameraVisualizationDataContext`  
`struct FChaosVDCameraVisualizationDataContext : public FChaosVDVisualizationContext`  
_L39-52_
- inherits: `FChaosVDVisualizationContext`
- desc: Visualization context structure specific for camera data visualizations
- L41 _public member_ `TSharedPtr<FChaosVDSolverDataSelectionHandle> DataSelectionHandle = MakeShared<FChaosVDSolverDataSelectionHandle>();`
- L43 _public member_ `ESceneDepthPriorityGroup DepthPriority = SDPG_Foreground;`
- L45 _public member_ `const UChaosVDCameraDataComponent* DataComponent = nullptr;`
- L47 _public function_ `bool IsVisualizationFlagEnabled(EChaosVDCameraDataVisualizationFlags Flag) const`

#### class `FChaosVDCameraDataComponentVisualizer`  
`class FChaosVDCameraDataComponentVisualizer final : public FChaosVDComponentVisualizerBase`  
_L54-68_
- inherits: `FChaosVDComponentVisualizerBase`
- L57 _public prototype_ `FChaosVDCameraDataComponentVisualizer();`
- L59 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L61 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L63 _public prototype_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override;`
- L67 _protected prototype_ `void DrawCameraTrace(const FSceneView* View, FPrimitiveDrawInterface* PDI, const FChaosVDCameraVisualizationDataContext& VisualizationContext, const TSharedRef<FChaosVDCameraDataWrapper>& CameraData);`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/ChaosVDGenericDebugDrawExtension.h` (Private)


#### class `FChaosVDGenericDebugDrawExtension`  
`class FChaosVDGenericDebugDrawExtension final : public FChaosVDExtension`  
_L12-25_
- inherits: `FChaosVDExtension`
- L16 _public prototype_ `FChaosVDGenericDebugDrawExtension();`
- L19 _public prototype_ `virtual void RegisterDataProcessorsInstancesForProvider(const TSharedRef<FChaosVDTraceProvider>& InTraceProvider) override;`
- L20 _public prototype_ `virtual TConstArrayView<TSubclassOf<UActorComponent>> GetSolverDataComponentsClasses() override;`
- L21 _public prototype_ `virtual void RegisterComponentVisualizers(const TSharedRef<SChaosVDMainTab>& InCVDToolKit) override;`
- L24 _private member_ `TArray<TSubclassOf<UActorComponent>> DataComponentsClasses;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Components/ChaosVDGenericDebugDrawDataComponent.h` (Private)


#### enum `EChaosVDDrawDataContainerSource`  
`enum class EChaosVDDrawDataContainerSource : uint8`  
_L13-18_
- L15 _public enumerator_ `SolverFrame`
- L16 _public enumerator_ `SolverStage`
- L17 _public enumerator_ `GameFrame`

#### class `UChaosVDGenericDebugDrawDataComponent`  
`class UChaosVDGenericDebugDrawDataComponent : public UChaosVDSolverDataComponent`  
_L21-47_
- reflection: `UCLASS()`
- inherits: `UChaosVDSolverDataComponent`
- L25 _public prototype_ `UChaosVDGenericDebugDrawDataComponent();`
- L27 _public prototype_ `virtual void UpdateFromNewGameFrameData(const FChaosVDGameFrameData& InGameFrameData) override;`
- L29 _public prototype_ `virtual void UpdateFromSolverFrameData(const FChaosVDSolverFrameData& InSolverFrameData) override;`
- L31 _public prototype_ `virtual void UpdateFromNewSolverStageData(const FChaosVDSolverFrameData& InSolverFrameData, const FChaosVDFrameStageData& InSolverFrameStageData) override;`
- L33 _public prototype_ `virtual void ClearData() override;`
- L35 _public prototype_ `TConstArrayView<TSharedPtr<FChaosVDDebugDrawBoxDataWrapper>> GetDebugDrawBoxesDataView(EChaosVDDrawDataContainerSource Source) const;`
- L36 _public prototype_ `TConstArrayView<TSharedPtr<FChaosVDDebugDrawLineDataWrapper>> GetDebugDrawLinesDataView(EChaosVDDrawDataContainerSource Source) const;`
- L37 _public prototype_ `TConstArrayView<TSharedPtr<FChaosVDDebugDrawSphereDataWrapper>> GetDebugDrawSpheresDataView(EChaosVDDrawDataContainerSource Source) const;`
- L38 _public prototype_ `TConstArrayView<TSharedPtr<FChaosVDDebugDrawImplicitObjectDataWrapper>> GetDebugDrawImplicitObjectsDataView(EChaosVDDrawDataContainerSource Source) const;`
- L40 _public prototype_ `TSharedPtr<FChaosVDDebugShapeDataContainer> GetShapeDataContainer(EChaosVDDrawDataContainerSource Source) const;`
- L44 _private member_ `TSharedPtr<FChaosVDDebugShapeDataContainer> CurrentSolverStageDebugDrawData;`
- L45 _private member_ `TSharedPtr<FChaosVDDebugShapeDataContainer> CurrentSolverFrameDebugDrawData;`
- L46 _private member_ `TSharedPtr<FChaosVDDebugShapeDataContainer> CurrentGameFrameDebugDrawData;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Settings/ChaosVDGenericDebugDrawSettings.h` (Private)


#### enum `EChaosVDGenericDebugDrawVisualizationFlags`  
`enum class EChaosVDGenericDebugDrawVisualizationFlags : uint32`  
_L10-18_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Set of visualization flags options for Scene Queries
- L12 _public enumerator_ `None = 0 UMETA(Hidden)`
- L13 _public enumerator_ `EnableDraw = 1 << 0`
- L14 _public enumerator_ `DrawBoxes = 1 << 1`
- L15 _public enumerator_ `DrawLines = 1 << 2`
- L16 _public enumerator_ `DrawSpheres = 1 << 3`
- L17 _public enumerator_ `DrawImplicitObjects = 1 << 4`

#### class `UChaosVDGenericDebugDrawSettings`  
`class UChaosVDGenericDebugDrawSettings : public UChaosVDVisualizationSettingsObjectBase`  
_L22-50_
- reflection: `UCLASS(config=ChaosVD, PerObjectConfig)`
- inherits: `UChaosVDVisualizationSettingsObjectBase`
- L30 _public member_ `bool bShowDebugText = false;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — If true, any debug draw text available will be drawn
- L34 _public member_ `TEnumAsByte<ESceneDepthPriorityGroup> DepthPriority = ESceneDepthPriorityGroup::SDPG_Foreground;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — The depth priority used for while drawing data. Can be World or Foreground (with this one the shapes will be drawn on top of the geometry and be always visible)
- L38 _public member_ `float BaseThickness = 2.0f;` — `UPROPERTY(config, EditAnywhere, Category=DebugDraw)` — Thickness to apply to any debug draw shape controlled by this setting.
- L40 _public prototype_ `static void SetDataVisualizationFlags(EChaosVDGenericDebugDrawVisualizationFlags NewFlags);`
- L41 _public prototype_ `static EChaosVDGenericDebugDrawVisualizationFlags GetDataVisualizationFlags();`
- L43 _public prototype_ `virtual bool CanVisualizationFlagBeChangedByUI(uint32 Flag) override;`
- L49 _private member_ `uint32 DebugDrawFlags = static_cast<uint32>(EChaosVDGenericDebugDrawVisualizationFlags::DrawBoxes | EChaosVDGenericDebugDrawVisualizationFlags::DrawLines | EChaosVDGenericDebugDrawVisualizationFlags::DrawSpheres);` — `UPROPERTY(config, meta = (Bitmask, BitmaskEnum = "/Script/ChaosVD.EChaosVDGenericDebugDrawVisualizationFlags"))` — Set of flags to enable/disable visualization of debug draw data shapes

#### Free symbols / members of external scopes

- L19 _prototype_ `ENUM_CLASS_FLAGS(EChaosVDGenericDebugDrawVisualizationFlags);`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Trace/DataProcessors/ChaosVDDebugDrawBoxDataProcessor.h` (Private)


#### class `FChaosVDDebugDrawBoxDataProcessor`  
`class FChaosVDDebugDrawBoxDataProcessor final : public FChaosVDDataProcessorBase`  
_L9-15_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Debug Draw Box shapes
- L12 _public prototype_ `explicit FChaosVDDebugDrawBoxDataProcessor();`
- L14 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Trace/DataProcessors/ChaosVDDebugDrawDataProcessorUtils.h` (Private)


#### enum `Chaos::VisualDebugger::Utils::EShapeDataContainerAccessorFlags`  
`enum class EShapeDataContainerAccessorFlags : uint8`  
_L10-15_
- L12 _public enumerator_ `None = 0`
- L14 _public enumerator_ `MarkFrameDirty = 1 << 0` — If the container lives in a game thread frame, it will mark it as dirty

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace Chaos`
- L8 _namespace_ `namespace VisualDebugger` (scope `Chaos`)
- L8 _namespace_ `namespace Utils` (scope `Chaos::VisualDebugger`)
- L16 _function_ `ENUM_CLASS_FLAGS(EShapeDataContainerAccessorFlags) template<typename DataType> TSharedPtr<FChaosVDDebugShapeDataContainer> GetShapeDataContainer(const TSharedRef<DataType>& InData, const TSharedRef<FChaosVDTraceProvider>& TraceProvider, EShapeDataContainerAccessorFlags Flags)` (scope `Chaos::VisualDebugger::Utils`)
- L77 _function_ `template<typename DataType> void RemapDebugDrawShapeDataSolverID(const TSharedRef<DataType>& InData, const TSharedRef<FChaosVDTraceProvider>& TraceProvider)` (scope `Chaos::VisualDebugger::Utils`)

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Trace/DataProcessors/ChaosVDDebugDrawImplicitObjectDataProcessor.h` (Private)


#### class `FChaosVDDebugDrawImplicitObjectDataProcessor`  
`class FChaosVDDebugDrawImplicitObjectDataProcessor final : public FChaosVDDataProcessorBase`  
_L9-15_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Debug Draw Implicit Objects
- L12 _public prototype_ `explicit FChaosVDDebugDrawImplicitObjectDataProcessor();`
- L14 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Trace/DataProcessors/ChaosVDDebugDrawLineDataProcessor.h` (Private)


#### class `FChaosVDDebugDrawLineDataProcessor`  
`class FChaosVDDebugDrawLineDataProcessor final : public FChaosVDDataProcessorBase`  
_L9-15_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Debug Draw lines
- L12 _public prototype_ `explicit FChaosVDDebugDrawLineDataProcessor();`
- L14 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Trace/DataProcessors/ChaosVDDebugDrawSphereDataProcessor.h` (Private)


#### class `FChaosVDDebugDrawSphereDataProcessor`  
`class FChaosVDDebugDrawSphereDataProcessor final : public FChaosVDDataProcessorBase`  
_L9-15_
- inherits: `FChaosVDDataProcessorBase`
- desc: Data processor implementation that is able to deserialize traced Debug Draw sphere shapes
- L12 _public prototype_ `explicit FChaosVDDebugDrawSphereDataProcessor();`
- L14 _public prototype_ `virtual bool ProcessRawData(const TArray<uint8>& InData) override;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/GenericDebugDraw/Visualizers/ChaosVDGenericDebugDrawDataComponentVisualizer.h` (Private)


#### struct `FChaosVDGenericDebugDrawDataVisualizationSettings`  
`struct FChaosVDGenericDebugDrawDataVisualizationSettings : public FChaosVDVisualizationContext`  
_L14-31_
- inherits: `FChaosVDVisualizationContext`
- desc: Visualization context structure specific for acceleration structure visualizations
- L16 _public member_ `ESceneDepthPriorityGroup DepthPriority = SDPG_Foreground;`
- L18 _public member_ `float Thickness = 0.0f;`
- L20 _public member_ `bool bShowDebugText = false;`
- L22 _public member_ `EChaosVDDrawDataContainerSource DataSource = EChaosVDDrawDataContainerSource::GameFrame;`
- L24 _public member_ `const UChaosVDGenericDebugDrawDataComponent* DataComponent = nullptr;`
- L26 _public function_ `bool IsVisualizationFlagEnabled(EChaosVDGenericDebugDrawVisualizationFlags Flag) const`

#### class `FChaosVDGenericDebugDrawDataComponentVisualizer`  
`class FChaosVDGenericDebugDrawDataComponentVisualizer final : public FChaosVDComponentVisualizerBase`  
_L33-51_
- inherits: `FChaosVDComponentVisualizerBase`
- L37 _public prototype_ `FChaosVDGenericDebugDrawDataComponentVisualizer();`
- L39 _public prototype_ `virtual void RegisterVisualizerMenus() override;`
- L41 _public function_ `virtual bool CanHandleClick(const HChaosVDComponentVisProxy& VisProxy) override`
- L43 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L45 _public prototype_ `void DrawData(const FSceneView* View, FPrimitiveDrawInterface* PDI, const FChaosVDGenericDebugDrawDataVisualizationSettings& InVisualizationContext);`
- L47 _public prototype_ `void DrawBoxes(FPrimitiveDrawInterface* PDI, const FSceneView* View, const FChaosVDGenericDebugDrawDataVisualizationSettings& InVisualizationContext);`
- L48 _public prototype_ `void DrawLines(FPrimitiveDrawInterface* PDI, const FSceneView* View, const FChaosVDGenericDebugDrawDataVisualizationSettings& InVisualizationContext);`
- L49 _public prototype_ `void DrawSpheres(FPrimitiveDrawInterface* PDI, const FSceneView* View, const FChaosVDGenericDebugDrawDataVisualizationSettings& InVisualizationContext);`
- L50 _public prototype_ `void DrawImplicitObjects(FPrimitiveDrawInterface* PDI, const FSceneView* View, const FChaosVDGenericDebugDrawDataVisualizationSettings& InVisualizationContext);`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/ParticleExtraData/ChaosVDParticleExtraDataExtension.h` (Private)


#### class `FChaosVDParticleExtraDataExtension`  
`class FChaosVDParticleExtraDataExtension final : public FChaosVDExtension`  
_L13-20_
- inherits: `FChaosVDExtension`
- desc: Built-in CVD extension that registers the FChaosVDParticleExtraDataProcessor. UChaosVDParticleExtraDataComponent is registered directly as a default subobject on AChaosVDSolverInfoActor, so this extension only handles processor registration.
- L16 _public prototype_ `FChaosVDParticleExtraDataExtension();`
- L17 _public prototype_ `virtual ~FChaosVDParticleExtraDataExtension() override = default;`
- L19 _public prototype_ `virtual void RegisterDataProcessorsInstancesForProvider(const TSharedRef<FChaosVDTraceProvider>& InTraceProvider) override;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/ChaosVDMetrics.h` (Private)


#### enum `ChaosVDCollisionComplexityFilteringOptions`  
`enum class ChaosVDCollisionComplexityFilteringOptions : uint8`  
_L13-18_
- reflection: `UENUM()`
- L15 _public enumerator_ `Simple`
- L16 _public enumerator_ `Complex`
- L17 _public enumerator_ `All`

#### enum `ChaosVDParticleMetricsType`  
`enum class ChaosVDParticleMetricsType : uint8`  
_L21-25_
- reflection: `UENUM()`
- L23 _public enumerator_ `PrimitiveDensity`
- L24 _public enumerator_ `MemoryUsage`

#### struct `FChaosVDMetricsSettings`  
`struct FChaosVDMetricsSettings`  
_L28-55_
- reflection: `USTRUCT()`
- L33 _public member_ `float SimpleMinThreshold = 0.0f;` — `UPROPERTY()`
- L36 _public member_ `float SimpleMaxThreshold = 0.0f;` — `UPROPERTY()`
- L39 _public member_ `float ComplexMinThreshold = 0.0f;` — `UPROPERTY()`
- L42 _public member_ `float ComplexMaxThreshold = 0.0f;` — `UPROPERTY()`
- L45 _public member_ `float AllMinThreshold = 0.0f;` — `UPROPERTY()`
- L48 _public member_ `float AllMaxThreshold = 0.0f;` — `UPROPERTY()`
- L50 _public prototype_ `double GetMinThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity) const;`
- L51 _public prototype_ `void SetMinThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity, double InMin);`
- L53 _public prototype_ `double GetMaxThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity) const;`
- L54 _public prototype_ `void SetMaxThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity, double InMax);`

#### struct `FParticleMetricEntry`  
`struct FParticleMetricEntry`  
_L57-74_
- L59 _public member_ `FName ParticleName;`
- L60 _public member_ `int32 SolverID = INDEX_NONE;`
- L61 _public member_ `int32 ParticleID = INDEX_NONE;`
- L62 _public member_ `uint32 SimplePrimitives = 0;`
- L63 _public member_ `uint32 SimpleMemoryUsage = 0;`
- L64 _public member_ `uint32 ComplexPrimitives = 0;`
- L65 _public member_ `uint32 ComplexMemoryUsage = 0;`
- L66 _public member_ `uint32 AllPrimitives = 0;`
- L67 _public member_ `FBox ParticleBounds = FBox(EForceInit::ForceInitToZero);`
- L69 _public prototype_ `double GetVolumeSafe();`
- L71 _public prototype_ `double GetMetric(ChaosVDCollisionComplexityFilteringOptions Complexity, ChaosVDParticleMetricsType Metric);`
- L73 _public prototype_ `void Aggregate(FParticleMetricEntry& Metric);`

#### Free symbols / members of external scopes

- L76 _namespace_ `namespace ChaosVDMetrics`
- L78 _prototype_ `uint32 GetPrimitiveCount(const Chaos::FImplicitObject* ImplicitPtr, const Chaos::EImplicitObjectType ImplicitType);` (scope `ChaosVDMetrics`)
- L79 _prototype_ `uint32 GetMemoryUsage(const Chaos::FImplicitObject* ImplicitPtr, const Chaos::EImplicitObjectType ImplicitType);` (scope `ChaosVDMetrics`)
- L80 _prototype_ `void CalculateMetrics(const TSharedRef<FChaosVDSceneParticle>& InParticleInstance, TWeakPtr<FChaosVDScene> WeakCVDScene, FParticleMetricEntry& OutMetrics);` (scope `ChaosVDMetrics`)
- L81 _prototype_ `void CalculateImplicitMetrics(Chaos::FConstImplicitObjectPtr InImplicitObject, TWeakPtr<FChaosVDScene> WeakCVDScene, const TSharedRef<FChaosVDSceneParticle>& InParticleInstance, FParticleMetricEntry& OutMetrics, int ShapeIndex);` (scope `ChaosVDMetrics`)

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Commands/ChaosVDMetricsHeatmapCommands.h` (Private)


#### class `FChaosVDMetricsHeatmapCommands`  
`class FChaosVDMetricsHeatmapCommands : public TCommands<FChaosVDMetricsHeatmapCommands>`  
_L7-21_
- inherits: `TCommands<FChaosVDMetricsHeatmapCommands>`
- L9 _private typedef_ `using ThisClass = FChaosVDMetricsHeatmapCommands;`
- L10 _private typedef_ `using Super = TCommands<FChaosVDMetricsHeatmapCommands>;`
- L13 _public prototype_ `FChaosVDMetricsHeatmapCommands();`
- L15 _public prototype_ `virtual ~FChaosVDMetricsHeatmapCommands() override = default;`
- L17 _public prototype_ `virtual void RegisterCommands() override;`
- L19 _public member_ `TSharedPtr<FUICommandInfo> FocusBounds;`
- L20 _public member_ `TSharedPtr<FUICommandInfo> TrackEditorView;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/PerformanceMetricsExtension.h` (Private)


#### class `FPerformanceMetricsExtension`  
`class FPerformanceMetricsExtension : public FChaosVDExtension`  
_L9-22_
- inherits: `FChaosVDExtension`
- L12 _public prototype_ `FPerformanceMetricsExtension();`
- L14 _public prototype_ `virtual void RegisterCustomTabSpawners(const TSharedRef<SChaosVDMainTab>& InParentTabWidget) override;`
- L15 _public prototype_ `virtual void RegisterComponentVisualizers(const TSharedRef<SChaosVDMainTab>& InCVDToolKit) override;`
- L16 _public prototype_ `virtual void HandleRecordingFirstFrameLoaded(TWeakPtr<FChaosVDPlaybackController> InController) override;`
- L18 _public member_ `TWeakPtr<SChaosVDMainTab> WeakCVDToolKit;`
- L19 _public member_ `TWeakPtr<FEditorModeTools> EditorModeToolsWeakPtr;`
- L21 _public member_ `static FName TabID;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Settings/ChaosVDMetricsViewSettings.h` (Private)


#### struct `FChaosVDHeatmapColorSettings`  
`struct FChaosVDHeatmapColorSettings`  
_L17-60_
- reflection: `USTRUCT()`
- L23 _public member_ `FColor LowValueColor = FColor(10, 10, 10);` — `UPROPERTY()` — The color for the low values in the metric's expected range.
- L27 _public member_ `FColor MidpointValueColor = FColor(0x85, 0x0C, 0x00);` — `UPROPERTY()` — The color for the values in the middle of the metric's expected range.
- L31 _public member_ `FColor HighValueColor = FColor(0xFF, 0, 0);` — `UPROPERTY()` — The color for the high values in the metric's expected range.
- L35 _public member_ `FColor MaxValueColor = FColor(0xFF, 0xE6, 0xE6);` — `UPROPERTY()` — The color for values exceeding the metric's expected range.
- L40 _public member_ `float MinAlpha = 0.4f;` — `UPROPERTY()` — The minimum alpha value used for all spatial values.
- L47 _public member_ `float MaxAlpha = 0.8f;` — `UPROPERTY()` — The maximum alpha value used for spatial values. The alpha value increases linearly according to the spatial value range.
- L51 _public member_ `float AlphaFactor = 2.0f;` — `UPROPERTY()` — How fast the heat value's alpha increases from MinValue to MaxValue according to the spatial value range.
- L55 _public member_ `float LowpointRatio = 0.2f;` — `UPROPERTY()` — The ratio position of the low point. All values up to this ratio should use LowValueColor.
- L59 _public member_ `float MidpointRatio = 0.5f;` — `UPROPERTY()` — The ratio position of the mid blend point. The value at this ratio should use MidpointValueColor.

#### class `UChaosVDMetricsViewSettings`  
`class UChaosVDMetricsViewSettings : public UChaosVDSettingsObjectBase`  
_L63-95_
- reflection: `UCLASS(config = ChaosVD)`
- inherits: `UChaosVDSettingsObjectBase`
- L67 _public prototype_ `UChaosVDMetricsViewSettings();`
- L70 _public member_ `uint32 HeatmapCellSize;` — `UPROPERTY(Config)`
- L73 _public member_ `FChaosVDHeatmapColorSettings HeatmapColorSettings;` — `UPROPERTY(Config)`
- L75 _public prototype_ `virtual void PostInitProperties() override;`
- L77 _public prototype_ `uint32 GetHeatmapCellSize() const;`
- L78 _public prototype_ `static void SetHeatmapCellSize(uint32 InValue);`
- L80 _public prototype_ `static void SetHeatmapCellMinThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity, ChaosVDParticleMetricsType Metrics, double InMin);`
- L81 _public prototype_ `double GetHeatmapCellMinThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity, ChaosVDParticleMetricsType Metrics) const;`
- L83 _public prototype_ `static void SetHeatmapCellMaxThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity, ChaosVDParticleMetricsType Metrics, double InMax);`
- L84 _public prototype_ `double GetHeatmapCellMaxThreshold(ChaosVDCollisionComplexityFilteringOptions Complexity, ChaosVDParticleMetricsType Metrics) const;`
- L86 _public prototype_ `static void SetHeatmapColorSettings(FChaosVDHeatmapColorSettings& InSettings);`
- L88 _public prototype_ `static const UChaosVDMetricsViewSettings* GetDefaultSettings();`
- L89 _public prototype_ `void SetDefaults();`
- L91 _public member_ `static TStrongObjectPtr<UChaosVDMetricsViewSettings> DefaultSettings;`
- L94 _private member_ `TMap<ChaosVDParticleMetricsType, FChaosVDMetricsSettings> MetricSettings;` — `UPROPERTY(Config)`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace Chaos`
- L10 _namespace_ `namespace VD` (scope `Chaos`)
- L10 _namespace_ `namespace PerformanceMetrics` (scope `Chaos::VD`)
- L10 _namespace_ `namespace SettingsBounds` (scope `Chaos::VD::PerformanceMetrics`)
- L12 _variable_ `constexpr uint32 MinCellSize = 1000;` (scope `Chaos::VD::PerformanceMetrics::SettingsBounds`)
- L13 _variable_ `constexpr uint32 MaxCellSize = 12800;` (scope `Chaos::VD::PerformanceMetrics::SettingsBounds`)

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Tabs/PerformanceMetricsTabSpawner.h` (Private)


#### class `FPerformanceMetricsTabSpawner`  
`class FPerformanceMetricsTabSpawner : public FChaosVDTabSpawnerBase`  
_L8-21_
- inherits: `FChaosVDTabSpawnerBase`
- L11 _public function_ `FPerformanceMetricsTabSpawner(const FName& InTabID, const TSharedPtr<FTabManager>& InTabManager, const TWeakPtr<SChaosVDMainTab>& InOwningTabWidget) : FChaosVDTabSpawnerBase(InTabID, InTabManager, InOwningTabWidget)`
- L14 _public prototype_ `virtual TSharedRef<SDockTab> HandleTabSpawnRequest(const FSpawnTabArgs& Args) override;`
- L16 _public prototype_ `virtual void HandleTabClosed(TSharedRef<SDockTab> InTabClosed) override;`
- L17 _public prototype_ `virtual void HandleTabSpawned(TSharedRef<SDockTab> InTabSpawned) override;`
- L18 _public prototype_ `void HandleRecordingFirstFrameLoaded(TWeakPtr<FChaosVDPlaybackController> InController);`
- L20 _private member_ `TSharedPtr<SPerfMetricsViewer> PerfViewerTabContent;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Widgets/SCVDMetricsHeatmapToolbar.h` (Private)


#### class `SCVDMetricsHeatmapToolbar`  
`class SCVDMetricsHeatmapToolbar final : public SViewportToolBar`  
_L11-35_
- inherits: `SViewportToolBar`
- L13 _private prototype_ `SLATE_DECLARE_WIDGET(SCVDMetricsHeatmapToolbar, SViewportToolBar);`
- L16 _public function_ `SLATE_BEGIN_ARGS(SCVDMetricsHeatmapToolbar)`
- L17 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FUICommandList>, EditorCommands) SLATE_END_ARGS() void Construct(const FArguments& InArgs, TSharedPtr<FChaosVDMetricsViewerState> InViewerState);`
- L23 _private prototype_ `TSharedRef<SWidget> GenerateOptionsMenu();`
- L24 _private prototype_ `TSharedRef<SWidget> GenerateFocusMenu() const;`
- L26 _private prototype_ `static void RegisterOptionsMenu();`
- L27 _private prototype_ `static void RegisterFocusMenu();`
- L29 _private prototype_ `void PopulateMenuHeatmapColorSettings(FToolMenuSection& Section);`
- L30 _private prototype_ `void PopulateMenuMetricSettings(FToolMenuSection& Section);`
- L32 _private member_ `TSharedPtr<FChaosVDMetricsViewerState> ViewerState;`
- L33 _private member_ `TSharedPtr<FUICommandList> CommandList;`
- L34 _private member_ `TArray<TSharedRef<FName>> ProfileNames;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Widgets/SCVDMetricsHistogram.h` (Private)


#### class `FExponentialTypeInterface`  
`class FExponentialTypeInterface : public INumericTypeInterface<double>`  
_L13-30_
- inherits: `INumericTypeInterface<double>`
- L16 _public prototype_ `virtual FString ToString(const double& Value) const override;`
- L18 _public prototype_ `virtual TOptional<double> FromString(const FString& InString, const double& ExistingValue) override;`
- L20 _public prototype_ `virtual bool IsCharacterValid(TCHAR InChar) const override;`
- L22 _public function_ `virtual int32 GetMinFractionalDigits() const override`
- L25 _public function_ `virtual int32 GetMaxFractionalDigits() const override`
- L28 _public function_ `virtual void SetMinFractionalDigits(const TAttribute<TOptional<int32>>& InMinFractionalDigits) override`
- L29 _public function_ `virtual void SetMaxFractionalDigits(const TAttribute<TOptional<int32>>& InMaxFractionalDigits) override`

#### struct `SCVDMetricsHistogramData`  
`struct SCVDMetricsHistogramData`  
_L32-48_
- L34 _public member_ `double MinStat = 10000000000;`
- L35 _public member_ `double MaxStat = 0;`
- L36 _public member_ `double AvgStat = 0;`
- L37 _public member_ `double MedianStat = 0;`
- L38 _public member_ `uint32 NumValues = 0;`
- L40 _public member_ `uint32 MaxBinCount = 0;`
- L41 _public member_ `uint32 MinBinCount = 1000000000;`
- L43 _public member_ `uint32 NumBins = 10;`
- L44 _public member_ `double LowerThreshold = 0;`
- L45 _public member_ `double UpperThreshold = std::numeric_limits<double>::max();`
- L47 _public member_ `TArray<uint32> Bins;`

#### class `SCVDMetricsHistogramPanelView`  
`class SCVDMetricsHistogramPanelView final : public SCompoundWidget`  
_L50-74_
- inherits: `SCompoundWidget`
- L52 _private prototype_ `SLATE_DECLARE_WIDGET(SCVDMetricsHistogramPanelView, SCompoundWidget);`
- L55 _public function_ `SLATE_BEGIN_ARGS(SCVDMetricsHistogramPanelView)`
- L58 _public prototype_ `SCVDMetricsHistogramPanelView();`
- L60 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<FChaosVDMetricsViewerState> InViewerState);`
- L62 _public prototype_ `void UpdateHistogram();`
- L64 _public prototype_ `TSharedRef<SWidget> GetHistogramSettingsMenuContent();`
- L67 _private member_ `TSharedPtr<FChaosVDMetricsViewerState> ViewerState;`
- L68 _private member_ `TSharedPtr<SCVDMetricsHistogramData> HistogramData;`
- L70 _private member_ `TSharedPtr<FExponentialTypeInterface> ExponentialFormat;`
- L72 _private member_ `float SideBarWidth = 300;`

#### class `SCVDMetricsHistogramCanvas`  
`class SCVDMetricsHistogramCanvas final : public SCompoundWidget`  
_L76-115_
- inherits: `SCompoundWidget`
- L78 _private prototype_ `SLATE_DECLARE_WIDGET(SCVDMetricsHistogramCanvas, SCompoundWidget);`
- L81 _public function_ `SLATE_BEGIN_ARGS(SCVDMetricsHistogramCanvas)`
- L84 _public prototype_ `SCVDMetricsHistogramCanvas();`
- L86 _public prototype_ `void Construct(const FArguments& InArgs, TSharedPtr<SCVDMetricsHistogramData>& InHistogramData, TSharedPtr<FChaosVDMetricsViewerState>& InViewerState);`
- L89 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L90 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L91 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L92 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L94 _private prototype_ `int32 PaintBackground(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle) const;`
- L95 _private prototype_ `int32 PaintValues(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L97 _private prototype_ `FGeometry GetScrollBarAreaGeometry() const;`
- L98 _private prototype_ `FGeometry GetHistogramBarsGeometry(const FGeometry& AllottedGeometry) const;`
- L100 _private prototype_ `FGeometry GetClippingGeometry(const FGeometry& AllottedGeometry) const;`
- L101 _private prototype_ `int32 GetIndexFromScreenSpacePosition(const FVector2D& ScreenSpacePosition) const;`
- L102 _private prototype_ `FText GetTooltipText() const;`
- L104 _private member_ `TSharedPtr<SScrollBar> ScrollBar;`
- L105 _private member_ `TSharedPtr<SWidget> ScrollBarAreaWidget;`
- L106 _private member_ `TSharedPtr<SCVDMetricsHistogramData> HistogramData;`
- L107 _private member_ `TSharedPtr<FChaosVDMetricsViewerState> ViewerState;`
- L109 _private member_ `FGeometry HistogramBarsGeometry;`
- L111 _private member_ `FVector2D CursorScreenSpacePosition = FVector2D::ZeroVector;`
- L113 _private member_ `mutable float LastBarWidth = 1;`
- L114 _private member_ `int32 SelectedBarIndex = INDEX_NONE;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Widgets/SChaosVDMetricsView.h` (Private)


#### class `SParticleMetricRowWidget`  
`class SParticleMetricRowWidget : public SMultiColumnTableRow< TSharedPtr<FParticleMetricEntry>>`  
_L26-40_
- inherits: `SMultiColumnTableRow<TSharedPtr<FParticleMetricEntry>>`
- L29 _public function_ `SLATE_BEGIN_ARGS(SParticleMetricRowWidget)`
- L30 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTable, TSharedPtr<FParticleMetricEntry> InItem, ChaosVDCollisionComplexityFilteringOptions Complexity, ChaosVDParticleMetricsType Metric, TSharedPtr<FParticleMetricEntry> InSumMetric);`
- L34 _public prototype_ `TSharedRef<SWidget> GenerateWidgetForColumn(const FName& ColumnName);`
- L36 _public member_ `TSharedPtr<FParticleMetricEntry> Item;`
- L37 _public member_ `ChaosVDCollisionComplexityFilteringOptions SelectedComplexity = ChaosVDCollisionComplexityFilteringOptions::Simple;`
- L38 _public member_ `ChaosVDParticleMetricsType SelectedMetric = ChaosVDParticleMetricsType::PrimitiveDensity;`
- L39 _public member_ `TSharedPtr<FParticleMetricEntry> SumMetric;`

#### class `SChaosVDMetricsView`  
`class SChaosVDMetricsView : public SCompoundWidget`  
_L42-82_
- inherits: `SCompoundWidget`
- L45 _public function_ `SLATE_BEGIN_ARGS(SChaosVDMetricsView)`
- L46 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene> InCVDScene, TSharedPtr<FChaosVDMetricsViewerState> InViewerState);`
- L50 _public prototype_ `void Reset();`
- L52 _public prototype_ `void ApplyFiltering();`
- L54 _private member_ `TSharedPtr<SListView<TSharedPtr<FParticleMetricEntry>>> ComplexityListView;`
- L56 _private member_ `TSharedPtr<SSearchBox> SearchBox;`
- L58 _private member_ `TSharedPtr<STextBlock> MetricHeaderText;`
- L60 _private member_ `TArray<TSharedPtr<FParticleMetricEntry>> FilteredParticleEntries;`
- L62 _private member_ `TWeakPtr<FChaosVDScene> CVDScene;`
- L64 _private member_ `TSharedPtr<FChaosVDMetricsViewerState> ViewerState;`
- L66 _private member_ `TSharedPtr<FParticleMetricEntry> SumStatistics;`
- L68 _private prototype_ `TSharedRef<ITableRow> GenerateComplexityEntryRow(TSharedPtr<FParticleMetricEntry> ParticleComplexityEntry, const TSharedRef<STableViewBase>& TableViewBase) const;`
- L69 _private prototype_ `void HandleListDoubleClick(TSharedPtr<FParticleMetricEntry> ParticleComplexityEntry);`
- L70 _private prototype_ `void HandleListSelectionChanged(TSharedPtr<FParticleMetricEntry> ParticleComplexityEntry, ESelectInfo::Type SelectionType);`
- L81 _public member_ `static FColumnNames ColumnNames;`

#### struct `SChaosVDMetricsView::FColumnNames`  
`struct FColumnNames`  
_L74-79_
- L76 _public member_ `const FName Name = FName("Nam`
- L77 _public member_ `const FName Metric = FName("Met`
- L78 _public member_ `const FName Percentage = FName("Per`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Widgets/SChaosVDMetricsViewerState.h` (Private)


#### class `FChaosVDMetricsViewerState`  
`class FChaosVDMetricsViewerState : public TSharedFromThis<FChaosVDMetricsViewerState>`  
_L14-87_
- inherits: `TSharedFromThis<FChaosVDMetricsViewerState>`
- L18 _public typedef_ `using FSelectedMetricChangedSignature = void(const ChaosVDParticleMetricsType&, const ChaosVDCollisionComplexityFilteringOptions&);`
- L19 _public typedef_ `using FSelectionBoxChangedSignature = void(const FBox2D&);`
- L20 _public typedef_ `using FHeatmapCellSizeChangedSignature = void(uint32 InCellSize);`
- L21 _public typedef_ `using FHistogramFilterSignature = void(double HistogramMin, double HistogramMax);`
- L23 _public prototype_ `TMulticastDelegateRegistration<FSelectedMetricChangedSignature>& OnSelectedMetricChanged();`
- L24 _public prototype_ `TMulticastDelegateRegistration<FSelectionBoxChangedSignature>& OnSelectionBoxChanged();`
- L25 _public prototype_ `TMulticastDelegateRegistration<FHeatmapCellSizeChangedSignature>& OnHeatmapCellSizeChanged();`
- L26 _public prototype_ `TMulticastDelegateRegistration<FHistogramFilterSignature>& OnHistogramFilterChanged();`
- L28 _public prototype_ `void SetSelectedComplexity(ChaosVDCollisionComplexityFilteringOptions Complexity);`
- L30 _public prototype_ `ChaosVDCollisionComplexityFilteringOptions GetSelectedComplexity();`
- L32 _public prototype_ `void SetSelectedMetric(ChaosVDParticleMetricsType Metric);`
- L33 _public prototype_ `ChaosVDParticleMetricsType GetSelectedMetric();`
- L35 _public prototype_ `void SetSelectionBox(const FBox2D& InFilterBox);`
- L36 _public prototype_ `const FBox2D& GetSelectionBox() const;`
- L38 _public prototype_ `uint32 GetHeatmapCellSize() const;`
- L39 _public prototype_ `void SetHeatmapCellSize(uint32 InValue, bool bSendUpdateEvent = true);`
- L40 _public prototype_ `void ResetHeatmapCellSize();`
- L42 _public prototype_ `void SetEditorModeTools(const TWeakPtr<FEditorModeTools> InWeakEditorModeTools);`
- L43 _public prototype_ `FChaosVDPlaybackViewportClient* GetPlaybackViewportClient();`
- L44 _public prototype_ `FChaosVDHeatmapColorSettings& GetHeatmapColorSettings();`
- L45 _public prototype_ `void SetHeatmapColorSettings(FChaosVDHeatmapColorSettings& ColorSettings);`
- L47 _public prototype_ `void SetHeatmapCellMinThreshold(double InMin, bool bSendUpdateEvent = true);`
- L48 _public prototype_ `double GetHeatmapCellMinThreshold();`
- L50 _public prototype_ `void SetHeatmapCellMaxThreshold(double InMax, bool bSendUpdateEvent = true);`
- L51 _public prototype_ `double GetHeatmapCellMaxThreshold();`
- L53 _public prototype_ `void SetHistogramFilter(double InMin, double InMax);`
- L54 _public prototype_ `void GetHistogramFilter(double& OutMin, double& OutMax);`
- L56 _public prototype_ `void SetParticleMetrics(const TSharedPtr<TArray<TSharedPtr<FParticleMetricEntry>>>& InParticleEntries);`
- L57 _public prototype_ `TSharedPtr<TArray<TSharedPtr<FParticleMetricEntry>>> GetParticleEntries();`
- L58 _public prototype_ `bool IsParticleDataValid();`
- L60 _public prototype_ `void UpdateDataFromSettings();`
- L64 _private member_ `FBox2D SelectionBox = FBox2D(ForceInit);`
- L65 _private member_ `ChaosVDCollisionComplexityFilteringOptions SelectedComplexity = ChaosVDCollisionComplexityFilteringOptions::Simple;`
- L66 _private member_ `ChaosVDParticleMetricsType SelectedMetric = ChaosVDParticleMetricsType::PrimitiveDensity;`
- L68 _private member_ `FChaosVDHeatmapColorSettings HeatmapColorSettings;`
- L70 _private member_ `TWeakPtr<FEditorModeTools> EditorModeToolsWeakPtr;`
- L71 _private member_ `static const FName ChaosViewportType;`
- L73 _private member_ `uint32 HeatmapCellSize = 2000;`
- L75 _private member_ `double HeatmapCellMin;`
- L76 _private member_ `double HeatmapCellMax;`
- L78 _private member_ `double HistogramMin = -1;`
- L79 _private member_ `double HistogramMax = -1;`
- L81 _private member_ `TSharedPtr<TArray<TSharedPtr<FParticleMetricEntry>>> ParticleEntries;`
- L83 _private member_ `TMulticastDelegate<FSelectedMetricChangedSignature> SelectedMetricChangedDelegate;`
- L84 _private member_ `TMulticastDelegate<FSelectionBoxChangedSignature> SelectionBoxChangedDelegate;`
- L85 _private member_ `TMulticastDelegate<FHeatmapCellSizeChangedSignature> HeatmapCellSizeChangedDelegate;`
- L86 _private member_ `TMulticastDelegate<FHistogramFilterSignature> HistogramFilterChangedDelegate;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Widgets/SMetricsHeatmap.h` (Private)


#### struct `SCVDMetricsHeatmapState`  
`struct SCVDMetricsHeatmapState`  
_L15-33_
- L17 _public member_ `FBox2f ScreenRect = FBox2f(ForceInit);`
- L20 _public member_ `FVector2D FocusCenter = FVector2D::ZeroVector;` — Center focus point in world space
- L23 _public member_ `FTransform2d WorldToScreen;` — Transform from world to screen space
- L26 _public member_ `FTransform2d ScreenToWorld;` — Transform from screen to world space
- L28 _public member_ `static constexpr float HeatmapMinScale = 0.0016f;`
- L29 _public member_ `static constexpr float HeatmapMaxScale = 0.05f;`
- L32 _public member_ `float Scale = HeatmapMaxScale;` — Current zoom scale

#### struct `SCVDMetricsHeatmapCellData`  
`struct SCVDMetricsHeatmapCellData`  
_L35-40_
- L36 _public member_ `int64 XCoord;`
- L37 _public member_ `int64 YCoord;`
- L38 _public member_ `bool bIsCalculated = false;`
- L39 _public member_ `double CalculatedMetric = 0;`

#### class `SCVDMetricsHeatmapView`  
`class SCVDMetricsHeatmapView : public SCompoundWidget`  
_L43-116_
- inherits: `SCompoundWidget`
- desc: Heatmap view based on the FN Spatial Profiler
- L45 _private prototype_ `SLATE_DECLARE_WIDGET(SCVDMetricsHeatmapView, SCompoundWidget);`
- L48 _public function_ `SLATE_BEGIN_ARGS(SCVDMetricsHeatmapView)`
- L51 _public prototype_ `SCVDMetricsHeatmapView();`
- L53 _public prototype_ `void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene> InCVDScene, TSharedPtr<FChaosVDMetricsViewerState> InViewerState);`
- L55 _public prototype_ `void RefreshHeatmapView(bool bInvalidateBounds = true);`
- L57 _public prototype_ `void FocusEditorView() const;`
- L58 _public prototype_ `void FocusSampleBounds();`
- L60 _public prototype_ `void Teleport();`
- L63 _private prototype_ `void BindCommands();`
- L64 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L66 _private prototype_ `void UpdateMouseByEvent(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L67 _private prototype_ `void UpdateTransform() const;`
- L68 _private prototype_ `virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;`
- L69 _private prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L70 _private prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L71 _private prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L72 _private prototype_ `virtual FReply OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L73 _private prototype_ `virtual FReply OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;`
- L75 _private prototype_ `int32 PaintGrid(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L76 _private prototype_ `int32 PaintSpatialCell(const SCVDMetricsHeatmapCellData& Cell, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L77 _private prototype_ `int32 PaintEditorView(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L78 _private prototype_ `int32 PaintSpatialData(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L79 _private prototype_ `int32 PaintSelectionBounds(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L80 _private prototype_ `int32 PaintAxes(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L81 _private prototype_ `int32 PaintLegend(const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;`
- L83 _private prototype_ `void UpdateSelectionBox();`
- L85 _private prototype_ `bool IsScreenRectValid() const;`
- L86 _private prototype_ `bool IsMouseDragging() const;`
- L88 _private member_ `mutable SCVDMetricsHeatmapState State;`
- L90 _private member_ `FVector2f CursorScreenSpacePosition = FVector2f(ForceInitToZero);`
- L91 _private member_ `FVector2D CursorWorldPosition = FVector2D(ForceInitToZero);`
- L92 _private member_ `FVector2D LastCursorWorldDragPosition = FVector2D(ForceInitToZero);`
- L94 _private member_ `FVector2D SelectionStart = FVector2D(ForceInitToZero);`
- L95 _private member_ `FVector2D SelectionEnd = FVector2D(ForceInitToZero);`
- L97 _private member_ `int32 HeatmapCellSize = 200;`
- L99 _private member_ `float TotalMouseDelta = 0.0f;`
- L101 _private member_ `bool bIsTrackingCamera = false;`
- L103 _private member_ `bool bIsPanning = false;`
- L104 _private member_ `bool bIsFiltering = false;`
- L106 _private member_ `TSharedPtr<FChaosVDMetricsViewerState> ViewerState;`
- L107 _private member_ `TWeakPtr<FChaosVDScene> CVDScene;`
- L109 _private member_ `mutable TArray<SCVDMetricsHeatmapCellData> CellData;`
- L110 _private member_ `mutable TSet<FVector2d> CalculatedCells;`
- L112 _private member_ `TSharedPtr<SCVDMetricsHeatmapToolbar> Toolbar;`
- L113 _private member_ `const TSharedRef<FUICommandList> CommandList;`
- L114 _private member_ `TSharedPtr<TQuadTree<int32, 16>> QueuedQuadTree;`
- L115 _private member_ `TUniquePtr<TQuadTree<int32, 16>> QuadTree;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Private/PerformanceMetrics/Widgets/SPerfMetricsViewer.h` (Private)


#### class `SPerfMetricsViewer`  
`class SPerfMetricsViewer : public SCompoundWidget`  
_L19-60_
- inherits: `SCompoundWidget`
- L22 _public function_ `SLATE_BEGIN_ARGS(SPerfMetricsViewer)`
- L24 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TWeakPtr<FChaosVDScene>& InCVDScene, const TWeakPtr<SChaosVDMainTab>& InWeakMainTab);`
- L27 _public prototype_ `static void AnalyzeCurrentFrame(TSharedPtr<TArray<TSharedPtr<FParticleMetricEntry>>>& OutMetrics, TWeakPtr<FChaosVDScene> WeakCVDScenePtr, int32 SolverID);`
- L34 _public prototype_ `void SetTargetSolverID(FTargetSolverEntry NewTarget);`
- L35 _public prototype_ `void HandleRecordingFirstFrameLoaded(TWeakPtr<FChaosVDPlaybackController> InController);`
- L38 _private member_ `bool bProcessingTask = false;`
- L39 _private member_ `bool bAbortPendingAnalysis = false;`
- L41 _private member_ `TWeakPtr<FChaosVDScene> WeakCVDScene;`
- L42 _private member_ `TWeakPtr<SChaosVDMainTab> WeakMainTab;`
- L43 _private member_ `TSharedPtr<SButton> RefreshButton;`
- L44 _private member_ `TSharedPtr<SChaosVDMetricsView> Metrics;`
- L45 _private member_ `TSharedPtr<SCVDMetricsHeatmapView> Heatmap;`
- L46 _private member_ `TSharedPtr<SCVDMetricsHistogramPanelView> Histogram;`
- L47 _private member_ `static FName ToolBarName;`
- L48 _private member_ `FTargetSolverEntry CurrentTargetSolver;`
- L50 _private member_ `TSharedPtr<FChaosVDMetricsViewerState> ViewerState;`
- L52 _private member_ `ChaosVDCollisionComplexityFilteringOptions SelectedComplexity = ChaosVDCollisionComplexityFilteringOptions::Simple;`
- L53 _private member_ `ChaosVDParticleMetricsType SelectedMetric = ChaosVDParticleMetricsType::PrimitiveDensity;`
- L55 _private prototype_ `void RegisterMainToolbarMenu();`
- L56 _private prototype_ `TSharedRef<SWidget> GenerateMainToolbarWidget();`
- L57 _private prototype_ `TSharedRef<SWidget> GenerateSolverSelectorMenu();`
- L58 _private prototype_ `FText GetSolverSelectorButtonLabel() const;`

#### struct `SPerfMetricsViewer::FTargetSolverEntry`  
`struct FTargetSolverEntry`  
_L29-33_
- L31 _public member_ `int32 ID = INDEX_NONE;`
- L32 _public member_ `FText Name;`

#### class `UChaosVDPerfMetricsViewerToolbarMenuContext`  
`class UChaosVDPerfMetricsViewerToolbarMenuContext : public UObject`  
_L63-68_
- reflection: `UCLASS()`
- inherits: `UObject`
- L67 _public member_ `TWeakPtr<SPerfMetricsViewer> ViewerInstance;`

### `Plugins/ChaosVD/Source/ChaosVDBuiltInExtensions/Public/ChaosVDBuiltInExtensions.h` (Public)


#### class `FChaosVDBuiltInExtensionsModule`  
`class FChaosVDBuiltInExtensionsModule : public IModuleInterface`  
_L11-24_
- inherits: `IModuleInterface`
- L14 _public prototype_ `virtual void StartupModule() override;`
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L19 _private prototype_ `template <typename ExtensionType> void CreateAndRegisterExtensionInstance();`
- L21 _private prototype_ `void UnregisterCreatedExtensions();`
- L23 _private member_ `TArray<TWeakPtr<FChaosVDExtension>> AvailableExtensions;`
- L27 _function_ `template <typename ExtensionType> void FChaosVDBuiltInExtensionsModule::CreateAndRegisterExtensionInstance()`
