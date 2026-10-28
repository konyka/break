# Plugins / UVEditorTools

- module root: `Plugins/Editor/UVEditor/Source/UVEditorTools`
- headers: 36; symbols: 1287
- symbol kinds: class=83, delegate=11, enum=23, enumerator=94, function=143, macro=27, member=492, namespace=7, prototype=385, struct=9, typedef=13
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: DynamicMesh, Engine, GeometryAlgorithms, GeometryCore, InputCore, ModelingComponents, ModelingOperators, RHI, RenderCore, SlateCore, TextureUtilitiesCommon
- PublicDependencyModuleNames: Core, CoreUObject, InteractiveToolsFramework

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Actions/UVMakeIslandAction.h` (Public)


#### class `UUVMakeIslandAction`  
`class UUVMakeIslandAction : public UUVToolAction`  
_L21-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolAction`
- desc: Action that takes the currently selected triangles and makes a separate UV island out of them, i.e. any interior seams are removed, and seams are added around the boundary of the selection. If the selection is not connected in the mesh, islands will be created for each connected component of selected triangles. If some of the selected triangles have unset UVs, they will be initialized to 0 for the purposes to creating an island. The output is the triangles of the created islands. An unwrap operation on the island is typically a good thing to follow this action.
- L26 _public prototype_ `virtual bool CanExecuteAction() const override;`
- L27 _public prototype_ `virtual bool ExecuteAction() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Actions/UVSeamSewAction.h` (Public)


#### class `UUVSeamSewAction`  
`class UUVSeamSewAction : public UUVToolAction`  
_L23-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolAction`
- L27 _private typedef_ `using FDynamicMesh3 = UE::Geometry::FDynamicMesh3;`
- L30 _public prototype_ `virtual bool CanExecuteAction() const override;`
- L31 _public prototype_ `virtual bool ExecuteAction() override;`
- L33 _public prototype_ `static int32 FindSewEdgeOppositePairing(const FDynamicMesh3& UnwrapMesh, const FDynamicMesh3& AppliedMesh, int32 UVLayerIndex, int32 UnwrapEid, bool& bWouldPreferOppositeOrderOut);`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L17 _prototype_ `PREDECLARE_GEOMETRY(class FUVEditorDynamicMeshSelection);`
- L18 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Actions/UVSplitAction.h` (Public)


#### class `UUVSplitAction`  
`class UUVSplitAction : public UUVToolAction`  
_L13-20_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolAction`
- L18 _public prototype_ `virtual bool CanExecuteAction() const override;`
- L19 _public prototype_ `virtual bool ExecuteAction() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Actions/UVToolAction.h` (Public)


#### class `UUVToolAction`  
`class UUVToolAction : public UObject`  
_L16-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- L21 _public prototype_ `virtual void Setup(UInteractiveToolManager* ToolManager);`
- L22 _public prototype_ `virtual void Shutdown();`
- L23 _public function_ `virtual bool CanExecuteAction() const`
- L24 _public function_ `virtual bool ExecuteAction()`
- L28 _protected member_ `TObjectPtr<UUVToolSelectionAPI> SelectionAPI = nullptr;` — `UPROPERTY()`
- L31 _protected member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L33 _protected member_ `TWeakObjectPtr<UInteractiveToolManager> ToolManager;`
- L35 _protected function_ `virtual UInteractiveToolManager* GetToolManager() const`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/ContextObjects/UVToolAssetInputsContext.h` (Public)


#### class `UUVToolAssetInputsContext`  
`class UUVToolAssetInputsContext : public UUVToolContextObject`  
_L15-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: Simple context object used by UV asset editor to pass inputs down to the UV editor mode.
- L20 _public function_ `void Initialize(TArray<TObjectPtr<UObject>> AssetsIn, TArray<FTransform> TransformsIn)`
- L27 _public function_ `void GetAssetInputs(TArray<TObjectPtr<UObject>>& AssetsOut, TArray<FTransform>& TransformsOut) const`
- L34 _protected member_ `TArray<TObjectPtr<UObject>> Assets;`
- L35 _protected member_ `TArray<FTransform> Transforms;`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/ContextObjects/UVToolContextObjects.h` (Public)


#### class `UUVToolContextObject`  
`class UUVToolContextObject : public UObject`  
_L31-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Base class for context objects used in the UV editor.
- L39 _public function_ `virtual void Shutdown()` — Called by the mode when shutting context objects down, allowing them to do any cleanup. Initialization, on the other hand is usually done by some class-specific Initialize() method.
- L45 _public function_ `virtual void OnToolEnded(UInteractiveTool* DeadTool)` — Called whenever a tool is ended, for instance to let a context object remove listeners associated with that tool (it shouldn't have to do so, but may choose to for robustness).

#### class `UUVToolEmitChangeAPI`  
`class UUVToolEmitChangeAPI : public UUVToolContextObject`  
_L53-101_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: An API object meant to be stored in a context object store that allows UV editor tools to emit appropriate undo/redo transactions.
- L58 _public function_ `void Initialize(TObjectPtr<UInteractiveToolManager> ToolManagerIn)`
- L63 _public function_ `virtual void BeginUndoTransaction(const FText& Description)`
- L67 _public function_ `virtual void EndUndoTransaction()`
- L83 _public prototype_ `virtual void EmitToolIndependentChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description);` — Emit a change that can be undone even if we leave the tool from which it is emitted (as long as that UV editor instance is still open). Minor note: because we undo "out of" tools into a default tool and never out of a default tool, in practice, tool-independent changes will only ever be applied/reverted in the same tool invocation that they were emitted or in the default tool, not in other arbitrary tools. Since tool-independent changes usually operate on UV editor mesh input object, it is probably preferable to use EmitToolIndependentUnwrapCanonicalChange, which will set up a proper transaction for you.
- L90 _public prototype_ `virtual void EmitToolIndependentUnwrapCanonicalChange(UUVEditorToolMeshInput* InputObject, TUniquePtr<UE::Geometry::FDynamicMeshChange> UnwrapCanonicalMeshChange, const FText& Description);` — A convenience function that is like EmitToolIndependentChange, but uses a FDynamicMeshChange that operates on the UnwrapCanonical of an input to create a change object that updates the other views and issues an OnUndoRedo broadcast on the input object.
- L97 _public prototype_ `virtual void EmitToolDependentChange(UObject* TargetObject, TUniquePtr<FToolCommandChange> Change, const FText& Description);` — Emits a change that is considered expired when the active tool does not match the tool that was active when it was emitted.
- L100 _protected member_ `TWeakObjectPtr<UInteractiveToolManager> ToolManager = nullptr;`

#### class `UUVToolLivePreviewAPI`  
`class UUVToolLivePreviewAPI : public UUVToolContextObject`  
_L108-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: Allows tools to interact with the 3d preview viewport, which has a separate world and input router.
- L113 _public prototype_ `void Initialize(UWorld* WorldIn, UInputRouter* RouterIn, TUniqueFunction<void(FViewCameraState& CameraStateOut)> GetLivePreviewCameraStateFuncIn, TUniqueFunction<void(const UE::Geometry::FAxisAlignedBox3d& BoundingBox)> SetLivePreviewCameraToLookAtVolumeFuncIn, TUniqueFunction<void(const EMouseCursor::Type Cursor, bool bEnableOverride)> SetCursorOverrideFuncIn, UInteractiveGizmoManager* GizmoManager = nullptr);`
- L119 _public function_ `UWorld* GetLivePreviewWorld()`
- L120 _public function_ `UInputRouter* GetLivePreviewInputRouter()`
- L121 _public function_ `UInteractiveGizmoManager* GetGizmoManager()`
- L122 _public function_ `void GetLivePreviewCameraState(FViewCameraState& CameraStateOut)`
- L130 _public function_ `void SetLivePreviewCameraToLookAtVolume(const UE::Geometry::FAxisAlignedBox3d& BoundingBox)`
- L138 _public function_ `void SetCursorOverride(const EMouseCursor::Type Cursor)`
- L146 _public function_ `void ClearCursorOverride()`
- L154 _public prototype_ `virtual void OnToolEnded(UInteractiveTool* DeadTool) override;`
- L160 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRender, IToolsContextRenderAPI* RenderAPI);` — Broadcast by the 3D live preview viewport on Render() so that mechanics/tools can render there.
- L161 _public member_ `FOnRender OnRender;`
- L167 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDrawHUD, FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);` — Broadcast by the 3D live preview viewport on DrawHUD() so that mechanics/tools can draw there.
- L168 _public member_ `FOnDrawHUD OnDrawHUD;`
- L172 _protected member_ `TWeakObjectPtr<UWorld> World;` — `UPROPERTY()`
- L175 _protected member_ `TWeakObjectPtr<UInputRouter> InputRouter;` — `UPROPERTY()`
- L177 _protected member_ `TUniqueFunction<void(FViewCameraState& CameraStateOut)> GetLivePreviewCameraStateFunc;`
- L178 _protected member_ `TUniqueFunction<void(const UE::Geometry::FAxisAlignedBox3d& BoundingBox)> SetLivePreviewCameraToLookAtVolumeFunc;`
- L179 _protected member_ `TUniqueFunction<void(const EMouseCursor::Type Cursor, bool bEnableOverride)> SetCursorOverrideFunc;`
- L182 _private member_ `TWeakObjectPtr<UInteractiveGizmoManager> GizmoManager;`

#### struct `FUDIMBlock`  
`struct FUDIMBlock`  
_L186-199_
- reflection: `USTRUCT()`
- L191 _public member_ `int32 UDIM = 1001;` — `UPROPERTY()`
- L194 _public member_ `int32 TextureResolution = 512;` — `UPROPERTY()`
- L196 _public prototype_ `int32 BlockU() const;`
- L197 _public prototype_ `int32 BlockV() const;`
- L198 _public prototype_ `void SetFromBlocks(int32 BlockU, int32 BlockV);`

#### class `UUVTool2DViewportAPI`  
`class UUVTool2DViewportAPI : public UUVToolContextObject`  
_L205-272_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: Allows tools to interact with the 2d preview viewport
- L210 _public function_ `void SetUDIMBlocks(TArray<FUDIMBlock>& BlocksIn, bool bBroadcast = true)`
- L219 _public function_ `const TArray<FUDIMBlock>& GetUDIMBlocks() const`
- L224 _public function_ `void SetDrawGrid(bool bDrawGridIn, bool bBroadcast = true)`
- L233 _public function_ `const bool GetDrawGrid() const`
- L238 _public function_ `void SetDrawRulers(bool bDrawRulersIn, bool bBroadcast = true)`
- L247 _public function_ `const bool GetDrawRulers() const`
- L253 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUDIMBlockChange, const TArray<FUDIMBlock>& UDIMBlocks);`
- L254 _public member_ `FOnUDIMBlockChange OnUDIMBlockChange;`
- L256 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDrawGridChange, bool bDrawGrid);`
- L257 _public member_ `FOnDrawGridChange OnDrawGridChange;`
- L259 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDrawRulersChange, bool bDrawRulers);`
- L260 _public member_ `FOnDrawRulersChange OnDrawRulersChange;`
- L265 _protected member_ `TArray<FUDIMBlock> UDIMBlocks;` — `UPROPERTY(Transient)`
- L268 _protected member_ `bool bDrawGrid;` — `UPROPERTY(Transient)`
- L271 _protected member_ `bool bDrawRulers;` — `UPROPERTY(Transient)`

#### class `UUVToolAssetAndChannelAPI`  
`class UUVToolAssetAndChannelAPI : public UUVToolContextObject`  
_L279-314_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: Allows tools to interact with the assets and their UV layers
- L284 _public function_ `TArray<int32> GetCurrentChannelVisibility()`
- L293 _public function_ `void RequestChannelVisibilityChange(const TArray<int32>& ChannelPerAsset, bool bEmitUndoTransaction=true)`
- L301 _public function_ `void NotifyOfAssetChannelCountChange(int32 AssetID)`
- L310 _public member_ `TUniqueFunction<TArray<int32>()> GetCurrentChannelVisibilityFunc;`
- L311 _public member_ `TUniqueFunction<void(const TArray<int32>&, bool)> RequestChannelVisibilityChangeFunc;`
- L312 _public member_ `TUniqueFunction<void(int32 AssetID)> NotifyOfAssetChannelCountChangeFunc;`

#### class `UUVToolAABBTreeStorage`  
`class UUVToolAABBTreeStorage : public UUVToolContextObject`  
_L322-350_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: Stores AABB trees for UV input object unwrap canonical or applied canonical meshes. Binds to the input objects' OnCanonicalModified delegate to automatically update the tree when necessary.
- L326 _public typedef_ `using FDynamicMesh3 = UE::Geometry::FDynamicMesh3;`
- L327 _public typedef_ `using FDynamicMeshAABBTree3 = UE::Geometry::FDynamicMeshAABBTree3;`
- L330 _public prototype_ `void Set(FDynamicMesh3* MeshKey, TSharedPtr<FDynamicMeshAABBTree3> Tree, UUVEditorToolMeshInput* InputObject);`
- L333 _public prototype_ `TSharedPtr<FDynamicMeshAABBTree3> Get(FDynamicMesh3* MeshKey);`
- L335 _public prototype_ `void Remove(FDynamicMesh3* MeshKey);`
- L337 _public prototype_ `void RemoveByPredicate(TUniqueFunction< bool(const FDynamicMesh3* Mesh, TWeakObjectPtr<UUVEditorToolMeshInput> InputObject, TSharedPtr<FDynamicMeshAABBTree3> Tree)> Predicate);`
- L341 _public prototype_ `void Empty();`
- L343 _public prototype_ `virtual void Shutdown() override;`
- L347 _protected typedef_ `using TreeInputObjectPair = TPair<TSharedPtr<FDynamicMeshAABBTree3>, TWeakObjectPtr<UUVEditorToolMeshInput>>;`
- L349 _protected member_ `TMap<FDynamicMesh3*, TreeInputObjectPair> AABBTreeStorage;`

#### class `UUVEditorToolPropertiesAPI`  
`class UUVEditorToolPropertiesAPI : public UUVToolContextObject`  
_L359-387_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- L365 _public function_ `void SetToolDisplayProperties(UObject* ToolDisplayPropertesIn)` — Property sets passed here will be displayed in the Display menu at the top of the UV Editor.
- L370 _public function_ `UObject* GetToolDisplayProperties()`
- L378 _public function_ `virtual void OnToolEnded(UInteractiveTool* DeadTool)`
- L385 _protected member_ `TObjectPtr<UObject> ToolDisplayProperties = nullptr;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L18 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L160 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnRender, IToolsContextRenderAPI* RenderAPI);` — Broadcast by the 3D live preview viewport on Render() so that mechanics/tools can render there.
- L167 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDrawHUD, FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);` — Broadcast by the 3D live preview viewport on DrawHUD() so that mechanics/tools can draw there.
- L253 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUDIMBlockChange, const TArray<FUDIMBlock>& UDIMBlocks);`
- L256 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDrawGridChange, bool bDrawGrid);`
- L259 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnDrawRulersChange, bool bDrawRulers);`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/ContextObjects/UVToolViewportButtonsAPI.h` (Public)


#### class `UUVToolViewportButtonsAPI`  
`class UUVToolViewportButtonsAPI : public UUVToolContextObject`  
_L15-180_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: Allows tools to interact with buttons in the viewport
- L34 _public typedef_ `using ESelectionMode = UUVToolSelectionAPI::EUVEditorSelectionMode;`
- L36 _public function_ `void SetGizmoButtonsEnabled(bool bOn)`
- L41 _public function_ `bool AreGizmoButtonsEnabled() const`
- L46 _public function_ `void SetGizmoMode(EGizmoMode ModeIn, bool bBroadcast = true)`
- L55 _public function_ `EGizmoMode GetGizmoMode() const`
- L61 _public function_ `void SetSelectionButtonsEnabled(bool bOn)`
- L66 _public function_ `bool AreSelectionButtonsEnabled() const`
- L71 _public function_ `void SetSelectionMode(ESelectionMode ModeIn, bool bBroadcast = true)`
- L80 _public function_ `ESelectionMode GetSelectionMode() const`
- L85 _public function_ `void InitiateFocusCameraOnSelection() const`
- L90 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoModeChange, EGizmoMode NewGizmoMode);`
- L91 _public member_ `FOnGizmoModeChange OnGizmoModeChange;`
- L93 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionModeChange, ESelectionMode NewSelectionMode);`
- L94 _public member_ `FOnSelectionModeChange OnSelectionModeChange;`
- L96 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnInitiateFocusCameraOnSelection);`
- L97 _public member_ `FOnInitiateFocusCameraOnSelection OnInitiateFocusCameraOnSelection;`
- L99 _public function_ `virtual void OnToolEnded(UInteractiveTool* DeadTool) override`
- L106 _public function_ `void SetSnappingActive(bool bInEnabled)` — Sets snapping on/off, rather than the explicit type to enable/disable
- L111 _public function_ `bool IsSnappingActive() const`
- L116 _public function_ `void ToggleSnapEnabled(ESnapTypeFlag SnapMode)`
- L121 _public function_ `bool GetSnapEnabled(ESnapTypeFlag SnapMode) const`
- L127 _public function_ `bool IsSnapActive(ESnapTypeFlag SnapMode) const` — Whether to perform the snapping, not just get it's checkbox state
- L132 _public function_ `void SetSnapValue(ESnapTypeFlag SnapMode, float SnapValue)`
- L150 _public function_ `float GetSnapValue(ESnapTypeFlag SnapMode) const`
- L170 _protected member_ `bool bSnappingActive = true;` — Toggle for all snapping, can be toggled so that whatever options were stored aren't cleared on enable (vs. ESnapTypeFlag::NoSnap)
- L171 _protected member_ `int32 SnapEnabled = (uint8)ESnapTypeFlag::NoSnap;`
- L172 _protected member_ `float LocationSnap = 1.0;`
- L173 _protected member_ `float RotationSnap = 5.0;`
- L174 _protected member_ `float ScaleSnap = 1.0;`
- L176 _protected member_ `bool bGizmoButtonsEnabled = false;`
- L177 _protected member_ `EGizmoMode GizmoMode = EGizmoMode::Select;`
- L178 _protected member_ `bool bSelectionButtonsEnabled = false;`
- L179 _protected member_ `ESelectionMode SelectionMode = ESelectionMode::Island;`

#### enum `UUVToolViewportButtonsAPI::EGizmoMode`  
`enum class EGizmoMode`  
_L20-24_
- L22 _public enumerator_ `Select`
- L23 _public enumerator_ `Transform`

#### enum `UUVToolViewportButtonsAPI::ESnapTypeFlag`  
`enum class ESnapTypeFlag : uint8`  
_L26-32_
- L28 _public enumerator_ `NoSnap = 0`
- L29 _public enumerator_ `Location = 1 << 0`
- L30 _public enumerator_ `Rotation = 1 << 1`
- L31 _public enumerator_ `Scale = 1 << 2`

#### Free symbols / members of external scopes

- L90 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoModeChange, EGizmoMode NewGizmoMode);`
- L93 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelectionModeChange, ESelectionMode NewSelectionMode);`
- L96 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInitiateFocusCameraOnSelection);`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Drawing/BasicElementSet.h` (Public)


#### class `TBasicElementSet`  
`template <typename VectorType, int32 ElementDataSize> class TBasicElementSet`  
_L24-116_
- desc: Generic storage for sets of geometry.
- L28 _public typedef_ `using GeometryType = VectorType;`
- L29 _public member_ `static const int32 ElementSize = ElementDataSize;`
- L31 _public function_ `VectorType& operator[](int32 Index)`
- L36 _public function_ `const VectorType& operator[](int32 Index) const`
- L42 _public function_ `int32 NumElements() const` — Current number of points.
- L48 _public function_ `void ReserveElements(const int32 MaxNum)` — Reserve enough memory for up to the given maximum number of points. This function needs to be called before any calls to AddElement().
- L54 _public function_ `void ReserveAdditionalElements(const int32 AdditionalNum)` — Reserve enough memory for an additional number of points over the existing number already reserved. This function needs to be called before any calls to AddElement().
- L61 _public function_ `template<typename... Targs> void AddElement(Targs... ElementPoints)` — Add a point to be rendered using the component.
- L70 _public function_ `void ClearElements()`
- L80 _protected function_ `template<typename T, typename... Targs> void AddElementInternal(const T& ElementPoint, Targs... ElementPoints)`
- L88 _protected function_ `template<typename T> void AddElementInternal(const T& ElementPoint)`
- L93 _protected function_ `FBox CalcElementsBox() const`
- L107 _protected member_ `TArray<VectorType> Elements;`
- L108 _protected member_ `int32 Num = 0;`
- L110 _protected member_ `bool bElementsDirty = true;`
- L115 _private prototype_ `static void AddPointToBox(const VectorType& Point, FBox& Box);` — Helper function to generically add a point to an FBox.
- L119 _function_ `template <> inline void TBasicElementSet<FVector2f, 1>::AddPointToBox(const FVector2f& Point, FBox& Box)` — Helper function template instantiations for FVector2f and FVector3f
- L123 _function_ `template <> inline void TBasicElementSet<FVector3f, 1>::AddPointToBox(const FVector3f& Point, FBox& Box)`
- L124 _function_ `template <> inline void TBasicElementSet<FVector2f, 2>::AddPointToBox(const FVector2f& Point, FBox& Box)`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Drawing/BasicLineSetComponent.h` (Public)


#### class `UBasicLineSetComponentBase`  
`class UBasicLineSetComponentBase : public UMeshComponent`  
_L32-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshComponent`
- desc: Base class for component specific functionality independent of the type of line stored in the component.
- L38 _public prototype_ `UBasicLineSetComponentBase();`
- L41 _public prototype_ `void ClearComponent();` — Clears the component state and marks component as dirty.
- L44 _public prototype_ `void SetLineMaterial(UMaterialInterface* InLineMaterial);` — Specify material that handles lines.
- L47 _public prototype_ `void SetLineSetParameters(FColor InColor, float InSize, float InDepthBias);` — Set per line material parameters that are uniform for all lines.
- L50 _public prototype_ `void SetColor(FColor InColor);` — Set per line material Line Color parameter that is uniform for all lines
- L53 _public prototype_ `void SetLineThickness(float InSize);` — Set per line material Line Size/Thickness parameter that is uniform for all lines
- L58 _protected function_ `virtual int32 GetNumMaterials() const override`
- L63 _protected function_ `template <typename CalcLineBoxFn> FBoxSphereBounds UpdateComponentBounds(const FTransform& LocalToWorld, bool bLinesDirty, CalcLineBoxFn&& CalcLineBox) const` — Update component bounds using a provided function that determines the box around all line positions. This unifies how the bounds are calculated while keeping the calculation of the box around all line positions generic.
- L91 _protected member_ `TObjectPtr<const UMaterialInterface> LineMaterial;` — `UPROPERTY()`
- L94 _protected member_ `mutable FBoxSphereBounds Bounds;` — `UPROPERTY()`
- L97 _protected member_ `mutable bool bBoundsDirty = true;` — `UPROPERTY()`
- L100 _protected member_ `FColor Color;` — `UPROPERTY()`
- L103 _protected member_ `float Size = 1.0f;` — `UPROPERTY()`
- L106 _protected member_ `float DepthBias = 0.0f;` — `UPROPERTY()`

#### class `UBasic2DLineSetComponent`  
`class UBasic2DLineSetComponent final : public UBasicLineSetComponentBase, public TBasicElementSet<FVector2f, 2>`  
_L111-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasicLineSetComponentBase,TBasicElementSet<FVector2f,2>`
- desc: Instantiation of a basic line set component in 2D using FVector2f for line positions.
- L117 _public function_ `void Clear()` — Clear all lines and component state.
- L126 _private prototype_ `virtual FPrimitiveSceneProxy * CreateSceneProxy() override;`
- L129 _private function_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override`

#### class `UBasic3DLineSetComponent`  
`class UBasic3DLineSetComponent final : public UBasicLineSetComponentBase, public TBasicElementSet<FVector3f, 2>`  
_L140-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasicLineSetComponentBase,TBasicElementSet<FVector3f,2>`
- desc: Instantiation of a basic line set component in 3D using FVector3f for line positions.
- L146 _public function_ `void Clear()` — Clear all lines and component state.
- L155 _private prototype_ `virtual FPrimitiveSceneProxy * CreateSceneProxy() override;`
- L158 _private function_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L132 _function_ `return UpdateComponentBounds(LocalToWorld, bElementsDirty, [this]() { return CalcElementsBox(); });` (scope `UBasic2DLineSetComponent::CalcBounds`) — The call to CalcElementsBox() is specific to the element type but already available in the generic implementation in TBasicElementSet<>.
- L161 _function_ `return UpdateComponentBounds(LocalToWorld, bElementsDirty, [this]() { return CalcElementsBox(); });` (scope `UBasic3DLineSetComponent::CalcBounds`) — The call to CalcElementsBox() is specific to the element type but already available in the generic implementation in TBasicElementSet<>.

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Drawing/BasicPointSetComponent.h` (Public)


#### class `UBasicPointSetComponentBase`  
`class UBasicPointSetComponentBase : public UMeshComponent`  
_L32-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshComponent`
- desc: Base class for component specific functionality independent of the type of point stored in the component.
- L38 _public prototype_ `UBasicPointSetComponentBase();`
- L41 _public prototype_ `void ClearComponent();` — Clears the component state and marks component as dirty.
- L44 _public prototype_ `void SetPointMaterial(UMaterialInterface* InPointMaterial);` — Specify material that handles points.
- L47 _public prototype_ `void SetPointSetParameters(FColor InColor, float InSize, float InDepthBias);` — Set per point material parameters that are uniform for all points.
- L50 _public prototype_ `void SetColor(const FColor InColor);` — Set per point material Color parameter that is uniform for all points.
- L53 _public prototype_ `void SetPointSize(const float InSize);` — Set per point material Size parameter tat is uniform for all points.
- L58 _protected function_ `virtual int32 GetNumMaterials() const override`
- L63 _protected function_ `template <typename CalcPointBoxFn> FBoxSphereBounds UpdateComponentBounds(const FTransform& LocalToWorld, bool bPointsDirty, CalcPointBoxFn&& CalcPointBox) const` — Update component bounds using a provided function that determines the box around all point positions. This unifies how the bounds are calculated while keeping the calculation of the box around all point positions generic.
- L91 _protected member_ `TObjectPtr<const UMaterialInterface> PointMaterial;` — `UPROPERTY()`
- L94 _protected member_ `mutable FBoxSphereBounds Bounds;` — `UPROPERTY()`
- L97 _protected member_ `mutable bool bBoundsDirty = true;` — `UPROPERTY()`
- L100 _protected member_ `FColor Color;` — `UPROPERTY()`
- L103 _protected member_ `float Size = 1.0f;` — `UPROPERTY()`
- L106 _protected member_ `float DepthBias = 0.0f;` — `UPROPERTY()`

#### class `UBasic2DPointSetComponent`  
`class UBasic2DPointSetComponent final : public UBasicPointSetComponentBase, public TBasicElementSet<FVector2f, 1>`  
_L111-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasicPointSetComponentBase,TBasicElementSet<FVector2f,1>`
- desc: Instantiation of a basic point set component in 2D using FVector2f for point positions.
- L117 _public function_ `void Clear()` — Clear all points and component state.
- L126 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L129 _private function_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override`

#### class `UBasic3DPointSetComponent`  
`class UBasic3DPointSetComponent final : public UBasicPointSetComponentBase, public TBasicElementSet<FVector3f, 1>`  
_L140-165_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasicPointSetComponentBase,TBasicElementSet<FVector3f,1>`
- desc: Instantiation of a basic point set component in 3D using FVector3f for point positions.
- L146 _public function_ `void Clear()` — Clear all points and component state.
- L155 _private prototype_ `virtual FPrimitiveSceneProxy* CreateSceneProxy() override;`
- L158 _private function_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L132 _function_ `return UpdateComponentBounds(LocalToWorld, bElementsDirty, [this]() { return CalcElementsBox(); });` (scope `UBasic2DPointSetComponent::CalcBounds`) — The call to CalcElementsBox() is specific to the element type but already available in the generic implementation in TBasicElementSet<>.
- L161 _function_ `return UpdateComponentBounds(LocalToWorld, bElementsDirty, [this]() { return CalcElementsBox(); });` (scope `UBasic3DPointSetComponent::CalcBounds`) — The call to CalcElementsBox() is specific to the element type but already available in the generic implementation in TBasicElementSet<>.

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Drawing/BasicTriangleSetComponent.h` (Public)


#### class `UBasicTriangleSetComponentBase`  
`class UBasicTriangleSetComponentBase : public UMeshComponent`  
_L32-85_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMeshComponent`
- desc: Base class for component specific functionality independent of the type of line stored in the component.
- L38 _public prototype_ `UBasicTriangleSetComponentBase();`
- L41 _public prototype_ `void ClearComponent();` — Clears the component state and marks component as dirty.
- L44 _public prototype_ `void SetTriangleMaterial(UMaterialInterface* InTriangleMaterial);` — Specify material that handles lines.
- L47 _public prototype_ `void SetTriangleSetParameters(FColor InColor, const FVector3f& NormalIn);` — Set per line material parameters that are uniform for all lines.
- L52 _protected function_ `virtual int32 GetNumMaterials() const override`
- L57 _protected function_ `template <typename CalcTriangleBoxFn> FBoxSphereBounds UpdateComponentBounds(const FTransform& LocalToWorld, bool bTrianglesDirty, CalcTriangleBoxFn&& CalcTriangleBox) const` — Update component bounds using a provided function that determines the box around all line positions. This unifies how the bounds are calculated while keeping the calculation of the box around all line positions generic.
- L72 _protected member_ `TObjectPtr<const UMaterialInterface> TriangleMaterial;` — `UPROPERTY()`
- L75 _protected member_ `mutable FBoxSphereBounds Bounds;` — `UPROPERTY()`
- L78 _protected member_ `mutable bool bBoundsDirty = true;` — `UPROPERTY()`
- L81 _protected member_ `FColor Color;` — `UPROPERTY()`
- L84 _protected member_ `FVector3f Normal;` — `UPROPERTY()`

#### class `UBasic2DTriangleSetComponent`  
`class UBasic2DTriangleSetComponent final : public UBasicTriangleSetComponentBase, public TBasicElementSet<FVector2f, 3>`  
_L89-114_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasicTriangleSetComponentBase,TBasicElementSet<FVector2f,3>`
- desc: Instantiation of a basic line set component in 2D using FVector2f for line positions.
- L95 _public function_ `void Clear()` — Clear all lines and component state.
- L104 _private prototype_ `virtual FPrimitiveSceneProxy * CreateSceneProxy() override;`
- L107 _private function_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override`

#### class `UBasic3DTriangleSetComponent`  
`class UBasic3DTriangleSetComponent final : public UBasicTriangleSetComponentBase, public TBasicElementSet<FVector3f, 3>`  
_L118-143_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBasicTriangleSetComponentBase,TBasicElementSet<FVector3f,3>`
- desc: Instantiation of a basic line set component in 3D using FVector3f for line positions.
- L124 _public function_ `void Clear()` — Clear all lines and component state.
- L133 _private prototype_ `virtual FPrimitiveSceneProxy * CreateSceneProxy() override;`
- L136 _private function_ `virtual FBoxSphereBounds CalcBounds(const FTransform& LocalToWorld) const override`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L110 _function_ `return UpdateComponentBounds(LocalToWorld, bElementsDirty, [this]() { return CalcElementsBox(); });` (scope `UBasic2DTriangleSetComponent::CalcBounds`) — The call to CalcElementsBox() is specific to the element type but already available in the generic implementation in TBasicElementSet<>.
- L139 _function_ `return UpdateComponentBounds(LocalToWorld, bElementsDirty, [this]() { return CalcElementsBox(); });` (scope `UBasic3DTriangleSetComponent::CalcBounds`) — The call to CalcElementsBox() is specific to the element type but already available in the generic implementation in TBasicElementSet<>.

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Math/UVMetrics.h` (Public)
_(no declarations extracted)_

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Operators/UVEditorTexelDensityOp.h` (Public)
_(no declarations extracted)_

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Operators/UVEditorUVTransformOp.h` (Public)


#### enum `EUVEditorUVTransformType`  
`enum class EUVEditorUVTransformType`  
_L23-31_
- reflection: `UENUM()`
- desc: UV Transform Strategies for the UV Transform Tool
- L26 _public enumerator_ `Transform` — Apply Scale, Totation and Translation properties to all UV values
- L28 _public enumerator_ `Align` — Position all selected elements given alignment rules
- L30 _public enumerator_ `Distribute` — Position all selected elements given distribution rules

#### enum `EUVEditorPivotType`  
`enum class EUVEditorPivotType`  
_L37-47_
- reflection: `UENUM()`
- desc: Transform Pivot Mode
- L40 _public enumerator_ `BoundingBoxCenter` — Pivot around the collective center of all island bounding boxes
- L42 _public enumerator_ `Origin` — Pivot around the global origin point
- L44 _public enumerator_ `IndividualBoundingBoxCenter` — Pivot around each island's bounding box center
- L46 _public enumerator_ `Manual` — Pivot around a user specified point

#### enum `EUVEditorTranslationMode`  
`enum class EUVEditorTranslationMode`  
_L53-59_
- reflection: `UENUM()`
- desc: Translation Mode
- L56 _public enumerator_ `Relative` — Move elements relative to their current position by the amount specified
- L58 _public enumerator_ `Absolute` — Move elements such that the transform origin is placed at the value specified

#### enum `EUVEditorAlignDirection`  
`enum class EUVEditorAlignDirection`  
_L62-71_
- reflection: `UENUM()`
- L64 _public enumerator_ `None`
- L65 _public enumerator_ `Top`
- L66 _public enumerator_ `Bottom`
- L67 _public enumerator_ `Left`
- L68 _public enumerator_ `Right`
- L69 _public enumerator_ `CenterVertically`
- L70 _public enumerator_ `CenterHorizontally`

#### enum `EUVEditorAlignAnchor`  
`enum class EUVEditorAlignAnchor`  
_L74-84_
- reflection: `UENUM()`
- L79 _public enumerator_ `BoundingBox` — Align relative to the collective bounding box of all islands
- L81 _public enumerator_ `UDIMTile` — Align relative to the local UDIM tile containing the island
- L83 _public enumerator_ `Manual` — Align relative to a user specified point

#### enum `EUVEditorDistributeMode`  
`enum class EUVEditorDistributeMode : uint16`  
_L87-99_
- reflection: `UENUM()`
- L89 _public enumerator_ `None`
- L90 _public enumerator_ `VerticalSpace`
- L91 _public enumerator_ `HorizontalSpace`
- L92 _public enumerator_ `TopEdges`
- L93 _public enumerator_ `BottomEdges`
- L94 _public enumerator_ `LeftEdges`
- L95 _public enumerator_ `RightEdges`
- L96 _public enumerator_ `CentersVertically`
- L97 _public enumerator_ `CentersHorizontally`
- L98 _public enumerator_ `MinimallyRemoveOverlap`

#### enum `EUVEditorAlignDistributeGroupingMode`  
`enum class EUVEditorAlignDistributeGroupingMode : uint8`  
_L102-110_
- reflection: `UENUM()`
- L105 _public enumerator_ `IndividualBoundingBoxes` — Treat selection as individual connected components, moving each according to their bounding boxes.
- L107 _public enumerator_ `EnclosingBoundingBox` — Treat selection as a single unit, moving everything together and preserving relative positions.
- L109 _public enumerator_ `IndividualVertices` — Treat selection as isolated UV vertices, moving each UV independently of each other.

#### class `UUVEditorUVTransformPropertiesBase`  
`class UUVEditorUVTransformPropertiesBase : public UInteractiveToolPropertySet`  
_L116-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: UV Transform Settings
- L121 _public function_ `UUVEditorUVTransformPropertiesBase()`

#### class `UUVEditorUVTransformProperties`  
`class UUVEditorUVTransformProperties : public UUVEditorUVTransformPropertiesBase`  
_L138-181_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorUVTransformPropertiesBase`
- desc: UV Transform Settings
- L145 _public member_ `FVector2D Scale = FVector2D(1.0, 1.0);` — `UPROPERTY(EditAnywhere, Category = "AdvancedTransform|Scaling", DuplicateTransient, meta = (TransientToolProperty, DisplayName = "Scale"))` — Scale applied to UVs, potentially non-uniform
- L150 _public member_ `float Rotation = 0.0;` — `UPROPERTY(EditAnywhere, Category = "AdvancedTransform|Rotation", meta = (TransientToolProperty, DisplayName = "Rotation", UIMin = "-360", UIMax = "360", ClampMin = "-100000", ClampMax = "100000"))` — Rotation applied to UVs after scaling, specified in degrees
- L154 _public member_ `FVector2D Translation = FVector2D(0, 0);` — `UPROPERTY(EditAnywhere, Category = "AdvancedTransform|Translation", meta = (TransientToolProperty, DisplayName = "Translation"))` — Translation applied to UVs, and after scaling and rotation
- L158 _public member_ `EUVEditorTranslationMode TranslationMode = EUVEditorTranslationMode::Relative;` — `UPROPERTY(EditAnywhere, Category = "AdvancedTransform|Translation", meta = (TransientToolProperty, DisplayName = "Translation Mode"))` — Translation applied to UVs, and after scaling and rotation
- L162 _public member_ `EUVEditorPivotType PivotMode = EUVEditorPivotType::BoundingBoxCenter;` — `UPROPERTY(EditAnywhere, Category = "AdvancedTransform|TransformOrigin", meta = (TransientToolProperty, DisplayName = "Mode"))` — Transformation origin mode used for scaling and rotation
- L167 _public member_ `FVector2D ManualPivot = FVector2D(0, 0);` — `UPROPERTY(EditAnywhere, Category = "AdvancedTransform|TransformOrigin", meta = (TransientToolProperty, DisplayName = "Coords", EditCondition = "PivotMode == EUVEditorPivotType::Manual", EditConditionHides, HideEditConditionToggle = true))` — Manual Transformation origin point
- L170 _public member_ `float QuickTranslateOffset = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Quick Transform", meta = (TransientToolProperty, DisplayName = "Translation"))`
- L174 _public member_ `float QuickRotationOffset = 0.0;` — `UPROPERTY(EditAnywhere, Category = "Quick Transform", meta = (TransientToolProperty, DisplayName = "Rotation", UIMin = "-360", UIMax = "360", ClampMin = "-100000", ClampMax = "100000"))`
- L177 _public member_ `FVector2D QuickTranslation;` — `UPROPERTY(EditAnywhere, Category = "Quick Transform", meta = (TransientToolProperty))`
- L180 _public member_ `float QuickRotation;` — `UPROPERTY(EditAnywhere, Category = "Quick Transform", meta = (TransientToolProperty))`

#### class `UUVEditorUVQuickTransformProperties`  
`class UUVEditorUVQuickTransformProperties : public UUVEditorUVTransformProperties`  
_L195-198_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorUVTransformProperties`
- desc: UV Quick Transform Only Settings We are using a subclass here to "trick" the details customization system, allowing us to reuse a lot of the logic without having to build new operators or new customizations. See FUVEditorUVTransformToolDetails and FUVEditorUVQuickTransformToolDetails, where we provide two customizations which present different views of the "same" properties - one with all settings and one with simply the quick transform settings. This is designed to be used in the future where we want to provide a quick translate "tool" when no other tools are running.

#### class `UUVEditorUVAlignProperties`  
`class UUVEditorUVAlignProperties : public UUVEditorUVTransformPropertiesBase`  
_L204-227_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorUVTransformPropertiesBase`
- desc: UV Align Settings
- L212 _public member_ `EUVEditorAlignAnchor AlignAnchor = EUVEditorAlignAnchor::BoundingBox;` — `UPROPERTY(EditAnywhere, Category = "Align", meta = (DisplayName = "Alignment Anchor"))` — Controls what geometry the alignment is to be relative to when performed.
- L217 _public member_ `FVector2D ManualAnchor = FVector2D(0, 0);` — `UPROPERTY(EditAnywhere, Category = "Align", meta = (DisplayName = "Anchor Coords", EditCondition = "AlignAnchor == EUVEditorAlignAnchor::Manual", EditConditionHides, HideEditConditionToggle = true))` — Manual anchor location for relative alignment
- L221 _public member_ `EUVEditorAlignDirection AlignDirection = EUVEditorAlignDirection::None;` — `UPROPERTY(EditAnywhere, Category = "Align", meta = (TransientToolProperty, DisplayName = "Alignment Direction"))` — Controls what side of the island bounding boxes are being aligned
- L225 _public member_ `EUVEditorAlignDistributeGroupingMode Grouping = EUVEditorAlignDistributeGroupingMode::IndividualBoundingBoxes;` — `UPROPERTY(EditAnywhere, Category = "Align", meta = (DisplayName = "Grouping Mode"))` — Controls how alignment considers grouping selected objects with respect to the alignment behavior.

#### class `UUVEditorUVDistributeProperties`  
`class UUVEditorUVDistributeProperties : public UUVEditorUVTransformPropertiesBase`  
_L233-259_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorUVTransformPropertiesBase`
- desc: UV Distribute Settings
- L239 _public member_ `EUVEditorDistributeMode DistributeMode = EUVEditorDistributeMode::None;` — `UPROPERTY(EditAnywhere, Category = "Distribute", meta = (TransientToolProperty, DisplayName = "Distribution Mode"))` — Controls the distribution behavior
- L243 _public member_ `EUVEditorAlignDistributeGroupingMode Grouping = EUVEditorAlignDistributeGroupingMode::IndividualBoundingBoxes;` — `UPROPERTY(EditAnywhere, Category = "Distribute", meta = (DisplayName = "Grouping Mode"))` — Controls how distribution considers grouping selected objects with respect to the distribution behavior.
- L247 _public member_ `bool bEnableManualDistances;` — `UPROPERTY(EditAnywhere, Category = "Distribute", meta = (DisplayName = "Manual Distances"))` — If true, enable overriding distances used in the distribution behavior with manually entered values.
- L252 _public member_ `float ManualExtent;` — `UPROPERTY(EditAnywhere, Category = "Distribute", meta = (DisplayName = "Manual Extent", EditCondition = "bEnableManualDistances", EditConditionHides, HideEditConditionToggle = true))` — For Edge and Center distribution modes, specify the desired overall distance within which to evenly place the edges or centers.
- L257 _public member_ `float ManualSpacing;` — `UPROPERTY(EditAnywhere, Category = "Distribute", meta = (DisplayName = "Manual Spacing", EditCondition = "bEnableManualDistances", EditConditionHides, HideEditConditionToggle = true))` — For Spacing and Remove Overlap distribution modes, specify the desired distance between objects.

#### enum `UE::Geometry::EUVEditorUVTransformTypeBackend`  
`enum class EUVEditorUVTransformTypeBackend`  
_L270-275_
- L272 _public enumerator_ `Transform`
- L273 _public enumerator_ `Align`
- L274 _public enumerator_ `Distribute`

#### enum `UE::Geometry::EUVEditorPivotTypeBackend`  
`enum class EUVEditorPivotTypeBackend`  
_L277-283_
- L279 _public enumerator_ `Origin`
- L280 _public enumerator_ `IndividualBoundingBoxCenter`
- L281 _public enumerator_ `BoundingBoxCenter`
- L282 _public enumerator_ `Manual`

#### enum `UE::Geometry::EUVEditorTranslationModeBackend`  
`enum class EUVEditorTranslationModeBackend`  
_L285-289_
- L287 _public enumerator_ `Relative`
- L288 _public enumerator_ `Absolute`

#### enum `UE::Geometry::EUVEditorAlignDirectionBackend`  
`enum class EUVEditorAlignDirectionBackend`  
_L291-300_
- L293 _public enumerator_ `None`
- L294 _public enumerator_ `Top`
- L295 _public enumerator_ `Bottom`
- L296 _public enumerator_ `Left`
- L297 _public enumerator_ `Right`
- L298 _public enumerator_ `CenterVertically`
- L299 _public enumerator_ `CenterHorizontally`

#### enum `UE::Geometry::EUVEditorAlignAnchorBackend`  
`enum class EUVEditorAlignAnchorBackend`  
_L302-308_
- L305 _public enumerator_ `UDIMTile` — FirstItem, // TODO:  Support this later once we have support in the Selection API
- L306 _public enumerator_ `BoundingBox`
- L307 _public enumerator_ `Manual`

#### enum `UE::Geometry::EUVEditorDistributeModeBackend`  
`enum class EUVEditorDistributeModeBackend`  
_L310-322_
- L312 _public enumerator_ `None`
- L313 _public enumerator_ `LeftEdges`
- L314 _public enumerator_ `RightEdges`
- L315 _public enumerator_ `TopEdges`
- L316 _public enumerator_ `BottomEdges`
- L317 _public enumerator_ `CentersVertically`
- L318 _public enumerator_ `CentersHorizontally`
- L319 _public enumerator_ `VerticalSpace`
- L320 _public enumerator_ `HorizontalSpace`
- L321 _public enumerator_ `MinimallyRemoveOverlap`

#### enum `UE::Geometry::EUVEditorAlignDistributeGroupingModeBackend`  
`enum class EUVEditorAlignDistributeGroupingModeBackend`  
_L324-329_
- L326 _public enumerator_ `IndividualBoundingBoxes`
- L327 _public enumerator_ `EnclosingBoundingBox`
- L328 _public enumerator_ `IndividualVertices`

#### class `UE::Geometry::FUVEditorUVTransformBaseOp`  
`class FUVEditorUVTransformBaseOp : public FDynamicMeshOperator`  
_L331-367_
- inherits: `FDynamicMeshOperator`
- L334 _public prototype_ `virtual ~FUVEditorUVTransformBaseOp() = default;`
- L337 _public member_ `TSharedPtr<FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;` — inputs
- L338 _public member_ `int UVLayerIndex = 0;`
- L339 _public member_ `EUVEditorAlignDistributeGroupingModeBackend GroupingMode;`
- L341 _public prototype_ `void SetTransform(const FTransformSRT3d& Transform);`
- L342 _public prototype_ `void SetSelection(const TSet<int32>& EdgeSelection, const TSet<int32>& VertexSelection);`
- L344 _public prototype_ `virtual void CalculateResult(FProgressCancel* Progress) override;`
- L345 _public function_ `const TArray<FVector2D>& GetPivotLocations() const`
- L348 _protected prototype_ `virtual void HandleTransformationOp(FProgressCancel* Progress) = 0;`
- L350 _protected prototype_ `FVector2f GetAlignmentPointFromBoundingBoxAndDirection(EUVEditorAlignDirectionBackend Direction, const FAxisAlignedBox2d& BoundingBox);`
- L351 _protected prototype_ `FVector2f GetAlignmentPointFromUDIMAndDirection(EUVEditorAlignDirectionBackend Direction, FVector2i UDIMTile);`
- L352 _protected prototype_ `void RebuildBoundingBoxes();`
- L353 _protected prototype_ `void CollectTransformElements();`
- L354 _protected prototype_ `void SortComponentsByBoundingBox(bool bSortXThenY = true);`
- L356 _protected member_ `TMap<int32, int32> ElementToComponent;`
- L357 _protected member_ `FDynamicMeshUVOverlay* ActiveUVLayer;`
- L358 _protected member_ `FAxisAlignedBox2d OverallBoundingBox;`
- L359 _protected member_ `TArray<FAxisAlignedBox2d> PerComponentBoundingBoxes;`
- L360 _protected member_ `TOptional< TSet<int32> > TransformingElements;`
- L361 _protected member_ `TSharedPtr<FMeshConnectedComponents> UVComponents;`
- L362 _protected member_ `TArray<int32> SpatiallyOrderedComponentIndex;`
- L363 _protected member_ `TArray<FVector2D> VisualizationPivots;`
- L365 _protected member_ `TOptional<TSet<int32>> VertexSelection;`
- L366 _protected member_ `TOptional<TSet<int32>> EdgeSelection;`

#### class `UE::Geometry::FUVEditorUVTransformOp`  
`class FUVEditorUVTransformOp : public FUVEditorUVTransformBaseOp`  
_L372-392_
- inherits: `FUVEditorUVTransformBaseOp`
- L375 _public prototype_ `virtual ~FUVEditorUVTransformOp() = default;`
- L378 _public member_ `FVector2D QuickTranslation = FVector2D(0.0, 0.0);` — inputs
- L379 _public member_ `float QuickRotation = 0.0;`
- L381 _public member_ `FVector2D Scale = FVector2D(1.0, 1.0);`
- L382 _public member_ `float Rotation = 0.0;`
- L383 _public member_ `FVector2D Translation = FVector2D(0, 0);`
- L384 _public member_ `EUVEditorTranslationModeBackend TranslationMode = EUVEditorTranslationModeBackend::Relative;`
- L386 _public member_ `EUVEditorPivotTypeBackend PivotMode = EUVEditorPivotTypeBackend::Origin;`
- L387 _public member_ `FVector2D ManualPivot = FVector2D(0, 0);`
- L390 _protected prototype_ `virtual void HandleTransformationOp(FProgressCancel* Progress) override;`
- L391 _protected prototype_ `FVector2f GetPivotFromMode(int32 ElementID, EUVEditorPivotTypeBackend Mode);`

#### class `UE::Geometry::FUVEditorUVAlignOp`  
`class FUVEditorUVAlignOp : public FUVEditorUVTransformBaseOp`  
_L394-408_
- inherits: `FUVEditorUVTransformBaseOp`
- L397 _public prototype_ `virtual ~FUVEditorUVAlignOp() = default;`
- L399 _public member_ `EUVEditorAlignAnchorBackend AlignAnchor = EUVEditorAlignAnchorBackend::BoundingBox;`
- L400 _public member_ `EUVEditorAlignDirectionBackend AlignDirection = EUVEditorAlignDirectionBackend::None;`
- L401 _public member_ `FVector2D ManualAnchor = FVector2D(0, 0);`
- L404 _protected prototype_ `virtual void HandleTransformationOp(FProgressCancel* Progress) override;`

#### class `UE::Geometry::FUVEditorUVDistributeOp`  
`class FUVEditorUVDistributeOp : public FUVEditorUVTransformBaseOp`  
_L410-423_
- inherits: `FUVEditorUVTransformBaseOp`
- L413 _public prototype_ `virtual ~FUVEditorUVDistributeOp() = default;`
- L415 _public member_ `EUVEditorDistributeModeBackend DistributeMode = EUVEditorDistributeModeBackend::None;`
- L416 _public member_ `bool bEnableManualDistances;`
- L417 _public member_ `float ManualExtent;`
- L418 _public member_ `float ManualSpacing;`
- L421 _protected prototype_ `virtual void HandleTransformationOp(FProgressCancel* Progress) override;`

#### class `UUVEditorUVTransformOperatorFactory`  
`class UUVEditorUVTransformOperatorFactory : public UObject, public UE::Geometry::IDynamicMeshOperatorFactory`  
_L436-455_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,UE::Geometry::IDynamicMeshOperatorFactory`
- desc: Can be hooked up to a UMeshOpPreviewWithBackgroundCompute to perform UV Transform operations. Inherits from UObject so that it can hold a strong pointer to the settings UObject, which needs to be a UObject to be displayed in the details panel.
- L442 _public prototype_ `virtual TUniquePtr<UE::Geometry::FDynamicMeshOperator> MakeNewOperator() override;` — IDynamicMeshOperatorFactory API
- L444 _public member_ `EUVEditorUVTransformType TransformType;`
- L447 _public member_ `TObjectPtr<UUVEditorUVTransformPropertiesBase> Settings;` — `UPROPERTY()`
- L449 _public member_ `TOptional<TSet<int32>> EdgeSelection;`
- L450 _public member_ `TOptional<TSet<int32>> VertexSelection;`
- L452 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh;`
- L453 _public function_ `TUniqueFunction<int32()> GetSelectedUVChannel = []()`
- L453 _public member_ `TUniqueFunction<int32()> GetSelectedUVChannel = []() { return 0; };`
- L454 _public member_ `FTransform TargetTransform;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L262 _namespace_ `namespace UE`
- L264 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Selection/UVEditorMeshSelectionMechanic.h` (Public)


#### class `UUVEditorMeshSelectionMechanic`  
`class UUVEditorMeshSelectionMechanic : public UInteractionMechanic`  
_L36-204_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractionMechanic`
- desc: Mechanic for selecting elements of a dynamic mesh in the UV editor. Interacts heavily with UUVToolSelectionAPI, which actually stores selections.
- L41 _public typedef_ `using FDynamicMeshAABBTree3 = UE::Geometry::FDynamicMeshAABBTree3;`
- L42 _public typedef_ `using FUVToolSelection = UE::Geometry::FUVToolSelection;`
- L44 _public prototype_ `virtual ~UUVEditorMeshSelectionMechanic() = default;`
- L46 _public prototype_ `virtual void Setup(UInteractiveTool* ParentTool) override;`
- L47 _public prototype_ `virtual void Shutdown() override;`
- L53 _public prototype_ `void Initialize(UWorld* World, UWorld* LivePreviewWorld, UUVToolSelectionAPI* SelectionAPI);` — Initialization functions. The selection API is provided as a parameter rather than being grabbed out of the context store mainly because UVToolSelectionAPI itself sets up a selection mechanic, and is not yet in the context store when it does this.
- L54 _public prototype_ `void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn);`
- L56 _public prototype_ `void SetIsEnabled(bool bIsEnabled);`
- L57 _public function_ `bool IsEnabled()`
- L71 _public prototype_ `bool RaycastCanonicals(const FRay& WorldRay, bool bRaycastIsForUnwrap, bool bPreferSelected, FRaycastResult& HitOut) const;` — This is a helper method that doesn't get used in normal selection mechanic operation, but can be used by clients if they need to raycast canonical meshes, since the mechanic already keeps aabb trees for them. The mechanic does not need to be enabled to use this (and typically will not be, if a tool is doing its own raycasting).
- L74 _public prototype_ `TArray<FUVToolSelection> GetAllCanonicalTrianglesInUnwrapRadius(const FVector2d& UnwrapWorldHitPoint, double Radius) const;`
- L76 _public prototype_ `void SetShowHoveredElements(bool bShow);`
- L78 _public typedef_ `using ESelectionMode = UUVToolSelectionAPI::EUVEditorSelectionMode;`
- L79 _public typedef_ `using FModeChangeOptions = UUVToolSelectionAPI::FSelectionMechanicModeChangeOptions;`
- L83 _public prototype_ `void SetSelectionMode(ESelectionMode TargetMode, const FModeChangeOptions& Options = FModeChangeOptions());` — Sets selection mode for the mechanic.
- L86 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L87 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L88 _public prototype_ `virtual void LivePreviewRender(IToolsContextRenderAPI* RenderAPI);`
- L89 _public prototype_ `virtual void LivePreviewDrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L91 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& ClickPos, bool bSourceIsLivePreview);` — IClickBehaviorTarget implementation
- L92 _public prototype_ `virtual void OnClicked(const FInputDeviceRay& ClickPos, bool bSourceIsLivePreview);`
- L95 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn);` — IModifierToggleBehaviorTarget implementation
- L98 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos, bool bSourceIsLivePreview);` — IHoverBehaviorTarget implementation
- L99 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos);`
- L100 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos, bool bSourceIsLivePreview);`
- L101 _public prototype_ `virtual void OnEndHover();`
- L107 _public member_ `FSimpleMulticastDelegate OnDragSelectionChanged;` — Broadcasted whenever the marquee mechanic rectangle is changed, since these changes don't trigger normal selection broadcasts.
- L112 _protected member_ `TObjectPtr<UUVToolSelectionAPI> SelectionAPI = nullptr;` — `UPROPERTY()`
- L115 _protected member_ `TObjectPtr<UUVToolViewportButtonsAPI> ViewportButtonsAPI = nullptr;` — `UPROPERTY()`
- L118 _protected member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L121 _protected member_ `TObjectPtr<UUVToolLivePreviewAPI> LivePreviewAPI = nullptr;` — `UPROPERTY()`
- L124 _protected member_ `TObjectPtr<ULocalSingleClickInputBehavior> UnwrapClickTargetRouter = nullptr;` — `UPROPERTY()`
- L127 _protected member_ `TObjectPtr<ULocalSingleClickInputBehavior> LivePreviewClickTargetRouter = nullptr;` — `UPROPERTY()`
- L130 _protected member_ `TObjectPtr<ULocalMouseHoverBehavior> UnwrapHoverBehaviorTargetRouter = nullptr;` — `UPROPERTY()`
- L133 _protected member_ `TObjectPtr<ULocalMouseHoverBehavior> LivePreviewHoverBehaviorTargetRouter = nullptr;` — `UPROPERTY()`
- L136 _protected member_ `TObjectPtr<URectangleMarqueeMechanic> MarqueeMechanic = nullptr;` — `UPROPERTY()`
- L139 _protected member_ `TObjectPtr<URectangleMarqueeMechanic> LivePreviewMarqueeMechanic = nullptr;` — `UPROPERTY()`
- L142 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> HoverTriangleSetMaterial = nullptr;` — `UPROPERTY()`
- L145 _protected member_ `TObjectPtr<APreviewGeometryActor> HoverGeometryActor = nullptr;` — `UPROPERTY()`
- L147 _protected member_ `TWeakObjectPtr<UTriangleSetComponent> HoverTriangleSet = nullptr;` — Weak pointers so that they go away when geometry actor is destroyed
- L148 _protected member_ `TWeakObjectPtr<ULineSetComponent> HoverLineSet = nullptr;`
- L149 _protected member_ `TWeakObjectPtr<UPointSetComponent> HoverPointSet = nullptr;`
- L152 _protected member_ `TObjectPtr<UInputBehaviorSet> LivePreviewBehaviorSet = nullptr;` — `UPROPERTY()`
- L155 _protected member_ `TObjectPtr<ULocalInputBehaviorSource> LivePreviewBehaviorSource = nullptr;` — `UPROPERTY()`
- L157 _protected member_ `TWeakObjectPtr<UInputRouter> LivePreviewInputRouter = nullptr;`
- L160 _protected member_ `TObjectPtr<APreviewGeometryActor> LivePreviewHoverGeometryActor = nullptr;` — `UPROPERTY()`
- L162 _protected member_ `TWeakObjectPtr<UTriangleSetComponent> LivePreviewHoverTriangleSet = nullptr;` — Weak pointers so that they go away when geometry actor is destroyed
- L163 _protected member_ `TWeakObjectPtr<ULineSetComponent> LivePreviewHoverLineSet = nullptr;`
- L164 _protected member_ `TWeakObjectPtr<UPointSetComponent> LivePreviewHoverPointSet = nullptr;`
- L167 _protected prototype_ `TSharedPtr<FDynamicMeshAABBTree3> GetMeshSpatial(int32 TargetId, bool bUseUnwrap) const;` — Should be the same as the mode-level targets array, indexed by AssetID
- L168 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;`
- L169 _protected member_ `TArray<TSharedPtr<FDynamicMeshAABBTree3>> UnwrapMeshSpatials;` — 1:1 with Targets
- L170 _protected member_ `TArray<TSharedPtr<FDynamicMeshAABBTree3>> AppliedMeshSpatials;` — 1:1 with Targets
- L172 _protected member_ `ESelectionMode SelectionMode;`
- L173 _protected member_ `bool bIsEnabled = false;`
- L174 _protected member_ `bool bShowHoveredElements = true;`
- L176 _protected prototype_ `bool GetHitTid(const FInputDeviceRay& ClickPos, int32& TidOut, int32& AssetIDOut, bool bUseUnwrap, int32* ExistingSelectionObjectIndexOut = nullptr);`
- L178 _protected prototype_ `void ModifyExistingSelection(TSet<int32>& SelectionSetToModify, const TArray<int32>& SelectedIDs);`
- L180 _protected member_ `FViewCameraState CameraState;`
- L182 _protected member_ `bool bShiftToggle = false;`
- L183 _protected member_ `bool bCtrlToggle = false;`
- L184 _protected member_ `static const int32 ShiftModifierID = 1;`
- L185 _protected member_ `static const int32 CtrlModifierID = 2;`
- L188 _protected function_ `bool ShouldAddToSelection() const` — All four combinations of shift/ctrl down are assigned a behaviour
- L189 _protected function_ `bool ShouldRemoveFromSelection() const`
- L190 _protected function_ `bool ShouldToggleFromSelection() const`
- L191 _protected function_ `bool ShouldRestartSelection() const`
- L194 _protected prototype_ `void OnDragRectangleStarted();` — For marquee mechanic
- L195 _protected prototype_ `void OnDragRectangleChanged(const FCameraRectangle& CurrentRectangle, bool bSourceIsLivePreview);`
- L196 _protected prototype_ `void OnDragRectangleFinished(const FCameraRectangle& Rectangle, bool bCancelled, bool bSourceIsLivePreview);`
- L198 _protected member_ `TArray<FUVToolSelection> PreDragSelections;`
- L199 _protected member_ `TArray<FUVToolSelection> PreDragUnsetSelections;`
- L202 _protected member_ `TArray<const FUVToolSelection*> AssetIDToPreDragSelection;` — Maps asset id to a pre drag selection so that it is easy to tell which assets started with a selection. 1:1 with Targets.
- L203 _protected member_ `TArray<const FUVToolSelection*> AssetIDToPreDragUnsetSelection;`

#### struct `UUVEditorMeshSelectionMechanic::FRaycastResult`  
`struct FRaycastResult`  
_L59-64_
- L61 _public member_ `int32 AssetID = IndexConstants::InvalidID;`
- L62 _public member_ `int32 Tid = IndexConstants::InvalidID;`
- L63 _public member_ `FVector3d HitPosition;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Selection/UVToolSelection.h` (Public)


#### class `UE::Geometry::FUVToolSelection`  
`class FUVToolSelection`  
_L20-124_
- desc: Class that represents a selection in the canonical unwrap of a UV editor input object.
- L30 _public member_ `TWeakObjectPtr<UUVEditorToolMeshInput> Target = nullptr;`
- L31 _public member_ `EType Type = EType::Vertex;`
- L32 _public member_ `TSet<int32> SelectedIDs;`
- L34 _public function_ `void Clear()`
- L41 _public prototype_ `void SelectAll(const FDynamicMesh3& Mesh, EType TypeIn);`
- L43 _public prototype_ `bool IsAllSelected(const FDynamicMesh3& Mesh) const;`
- L45 _public function_ `bool IsEmpty() const`
- L50 _public function_ `bool HasStableEdgeIdentifiers() const`
- L55 _public function_ `bool operator==(const FUVToolSelection& Other) const`
- L64 _public function_ `bool operator!=(const FUVToolSelection& Other) const`
- L69 _public prototype_ `void SaveStableEdgeIdentifiers(const FDynamicMesh3& Mesh);`
- L71 _public prototype_ `void RestoreFromStableEdgeIdentifiers(const FDynamicMesh3& Mesh);`
- L73 _public prototype_ `bool AreElementsPresentInMesh(const FDynamicMesh3& Mesh) const;`
- L75 _public prototype_ `FAxisAlignedBox3d ToBoundingBox(const FDynamicMesh3& Mesh, const FTransform Transform = FTransform3d::Identity) const;`
- L80 _public prototype_ `FUVToolSelection GetConvertedSelection(const FDynamicMesh3& Mesh, FUVToolSelection::EType ExpectedSelectionType) const;` — Utility method to construct a new selection from an existing reference selection, only with a new geometry type.
- L87 _public prototype_ `FUVToolSelection GetConvertedSelectionForUnwrappedMesh() const;` — Utility method to construct a new selection from an existing reference Applied mesh selection, only for the equivalent Unwrap mesh geometry. If the target for this selection is currently invalid or unset, this will return an empty selection.
- L94 _public prototype_ `FUVToolSelection GetConvertedSelectionForAppliedMesh() const;` — Utility method to construct a new selection from an existing reference Unwrap mesh selection, only for the equivalent Applied mesh geometry. If the target for this selection is currently invalid or unset, this will return an empty selection.
- L105 _public prototype_ `static TArray<int32> ConvertUnwrappedElementIdsToAppliedElementIds(EType SelectionMode, const FDynamicMesh3& UnwrapMesh, const FDynamicMesh3& AppliedMesh, const FDynamicMeshUVOverlay& UVOverlay, const TArray<int32>& IDsIn);` — Utility method to convert element ids from those belonging to the unwrapped mesh to those belonging to equivalent ids on the applied mesh @param SelectionMode The type of element the input ids represent @param UnwrapMesh A dynamic mesh instance representing the unwrapped mesh which the input ids belong to @param AppliedMesh A dynamic mesh instance representing the applied mesh for which the resulting ids will belong to @param UVOverlay An overlay representing the current UV mapping linking the unwrapped and applied mesh @param IDsIn The ids of the elements from the unwrapped mesh to convert to applied element ids
- L118 _public prototype_ `static TArray<int32> ConvertAppliedElementIdsToUnwrappedElementIds(EType SelectionMode, const FDynamicMesh3& AppliedMesh, const FDynamicMesh3& UnwrapMesh, const FDynamicMeshUVOverlay& UVOverlay, const TArray<int32>& IDsIn, TArray<int32>& AppliedOnlyElementIds);` — Utility method to convert element ids from those belonging to the applied mesh to those belonging to equivalent ids on the unwrapped mesh @param SelectionMode The type of element the input ids represent @param AppliedMesh A dynamic mesh instance representing the applied mesh which the input ids belong to @param UnwrapMesh A dynamic mesh instance representing the unwrapped mesh for which the resulting ids will belong to @param UVOverlay An overlay representing the current UV mapping linking the unwrapped and applied mesh @param IDsIn The ids of the elements from the unwrapped mesh to convert to applied element ids @param AppliedOnlyElementIds The ids of any remaining elements that have no direct mappings, due to unset UVs, in the unwrapped mesh
- L123 _protected member_ `FMeshEdgesFromTriangleSubIndices StableEdgeIDs;`

#### enum `UE::Geometry::FUVToolSelection::EType`  
`enum class EType`  
_L23-28_
- L25 _public enumerator_ `Vertex`
- L26 _public enumerator_ `Edge`
- L27 _public enumerator_ `Triangle`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L14 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Geometry` (scope `UE`)

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Selection/UVToolSelectionAPI.h` (Public)


#### enum `ESelectionChangeTypeFlag`  
`enum class ESelectionChangeTypeFlag : uint8`  
_L22-27_
- desc: Enum to describe the nature of the selection change during either a OnPreSelectionChange callback or OnSelectionChange callback.
- L24 _public enumerator_ `None = 0`
- L25 _public enumerator_ `SelectionChanged = 1 << 0` — Set for normal selection change events
- L26 _public enumerator_ `UnsetSelectionChanged = 1 << 1` — Set for unset selection change events

#### class `UUVToolSelectionAPI`  
`class UUVToolSelectionAPI : public UUVToolContextObject`  
_L42-394_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVToolContextObject`
- desc: API for dealing with mode-level selection in the UV editor. Selections are stored in a list of objects, one object per asset that contains a selection, all of the same type (vert/edge/tri), none empty. Selections are considered to be referring to the UnwrapCanonical mesh of the corresponding target. There are also functions to enable automatic highlighting of the current selection, and to enable a selection mechanic in the viewport (to which tools can respond via OnSelectionChanged broadcasts).
- L46 _public typedef_ `using FUVToolSelection = UE::Geometry::FUVToolSelection;`
- L51 _public function_ `bool HaveSelections() const` — Returns true when current selection is not empty.
- L61 _public function_ `const TArray<FUVToolSelection>& GetSelections() const` — Returns the current selection. When there are multiple selection objects, it means that there are selections in multiple assets, with a separate selection object per asset containing a selection. In such a case, all objects will have the same type (vertex/edge/triangle). Each selection object is considered to be referring to the CanonicalUnwrap mesh of the associated target.
- L66 _public function_ `FUVToolSelection::EType GetSelectionsType()` — Returns type (vertex/edge/triangle) of current selection. Undefined if selection is empty.
- L91 _public prototype_ `void SetSelections(const TArray<FUVToolSelection>& SelectionsIn, bool bBroadcast, bool bEmitChange);` — Sets the current selection. Selections should be same type, with no more than one selection object per asset, and no empty selection objects. Selections should be referring to the UnwrapCanonical of the associated target. @param bBroadcast If true, broadcast OnPreSelectionChange and OnSelectionChanged @param bEmitChange If true, emit an undo/redo transaction. @param bAllowInconsistentSelectionTypes If true, allow setting selections with different selection types than any currently set UnsetElement selections. Primarily useful during undo/redo
- L96 _public prototype_ `void ClearSelections(bool bBroadcast, bool bEmitChange);` — Equivalent to calling SetSelections with an empty array.
- L107 _public prototype_ `FVector3d GetUnwrapSelectionBoundingBoxCenter(bool bForceRecalculate = false);` — Gets the bounding box center of the current selection. The center point is cached and invalidated on the next SetSelection call, but can be forced to be recalculated. Note: you should call with bForceRecalculate = true whenever calling this from OnCanonicalModified, because it is not guaranteed that the selection api will detect the mesh change (and therefore invalidate the cached value) before your call site, due to the order of OnCanonicalModified broadcasts
- L115 _public prototype_ `bool HaveUnsetElementAppliedMeshSelections() const;` — These are functions that are used if a selection made in the applied mesh cannot be converted to an unwrap mesh selection due to unset UV elements (meaning that the selected portion does not exist in the unwrap mesh). Such selections are stored separately from all those that are able to be converted (which get stored with the usual unwrap selections). These "unset element" selections are ignored by many tools/actions but operated on by some others.
- L116 _public function_ `const TArray<FUVToolSelection>& GetUnsetElementAppliedMeshSelections()`
- L117 _public prototype_ `void SetUnsetElementAppliedMeshSelections(const TArray<FUVToolSelection>& SelectionsIn, bool bBroadcast, bool bEmitChange);`
- L118 _public prototype_ `void ClearUnsetElementAppliedMeshSelections(bool bBroadcast, bool bEmitChange);`
- L141 _public function_ `const UUVEditorMeshSelectionMechanic* GetSelectionMechanic() const` — Most clients shouldn't need to touch the selection mechanic directly, but it can be useful for certain utility functions that exist on the mechanic.
- L143 _public prototype_ `void SetSelectionMechanicEnabled(bool bEnabled);`
- L149 _public prototype_ `void SetSelectionMechanicOptions(const FSelectionMechanicOptions& Options);`
- L177 _public prototype_ `void SetSelectionMechanicMode(EUVEditorSelectionMode Mode, const FSelectionMechanicModeChangeOptions& Options = FSelectionMechanicModeChangeOptions());` — Sets the mechanic mode of operation.
- L185 _public prototype_ `void SetHighlightVisible(bool bUnwrapHighlightVisible, bool bAppliedHighlightVisible, bool bRebuild = true);` — Changes the visibility of the highlight.
- L209 _public prototype_ `void SetHighlightOptions(const FHighlightOptions& Options);`
- L211 _public prototype_ `void ClearHighlight(bool bClearForUnwrap = true, bool bClearForAppliedPreview = true);`
- L217 _public prototype_ `void RebuildUnwrapHighlight(const FTransform& StartTransform);` — Build up a highlight of the current selection in the Unwrap, with a given transform considered as its start transform.
- L225 _public prototype_ `void SetUnwrapHighlightTransform(const FTransform& NewTransform);` — Change the transform of the unwrap highlight without rebuilding it (for cheap movement of the highlight when translating the elements). Note that unmoved paired edges (if paired edge highlighting is enabled) will still be rebuilt since their shape may be changed by the movement of adjacent edges.
- L227 _public prototype_ `FTransform GetUnwrapHighlightTransform();`
- L229 _public prototype_ `void RebuildAppliedPreviewHighlight();`
- L240 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreSelectionChange, bool bEmitChangeAllowed, uint32 SelectionChangeType );` — Broadcasted right before a selection change is applied (and therefore before a selection change transaction is emitted). Useful if a user wants to emit their own bookend transaction first. @param bEmitChangeAllowed If false, the callback must not emit any undo/redo transactions, likely because this is being called from an apply/revert of an existing transaction. @param SelectionChangeType Set as some combination of ESelectionChangeCondition to describe the nature of the selection change.
- L241 _public member_ `FOnPreSelectionChange OnPreSelectionChange;`
- L252 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChanged, bool bEmitChangeAllowed, uint32 SelectionChangeType);` — Broadcasted after a selection change is applied (after the selection change transaction is emitted, if relevant). @param bEmitChangeAllowed If false, the callback must not emit any undo/redo transactions, likely because this is being called from an apply/revert of an existing transaction. @param SelectionChangeType Set as some combination of ESelectionChangeCondition to describe the nature of the selection change.
- L253 _public member_ `FOnSelectionChanged OnSelectionChanged;`
- L259 _public member_ `FSimpleMulticastDelegate OnDragSelectionChanged;` — Broadcasted whenever the marquee rectangle is changed, since these changes don't trigger normal selection broadcasts.
- L320 _public function_ `bool IsActive() const` — Returns true in between Initialize() and Shutdown(). Used by undo/redo to expire transactions when editor is closed.
- L326 _public prototype_ `void BeginChange();` — Preps a selection change transaction, if the user wants more control on what the previous and current selection is.
- L331 _public prototype_ `bool EndChangeAndEmitIfModified(bool bBroadcast);` — Ends the active change and emits it via the EmitChangeAPI
- L334 _public prototype_ `void Initialize(UInteractiveToolManager* ToolManagerIn, UWorld* UnwrapWorld, UInputRouter* UnwrapInputRouterIn, UUVToolLivePreviewAPI* LivePreviewAPI, UUVToolEmitChangeAPI* EmitChangeAPIIn);` — Initialization functions:
- L338 _public prototype_ `void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn);` — Should be called after Initialize()
- L341 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI);` — Called by the owner of the API
- L342 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L345 _public prototype_ `virtual void LivePreviewRender(IToolsContextRenderAPI* RenderAPI);` — Could have had the api place these into the LivePreviewAPI delegates, but decided against it to align with Render() and DrawHUD() above. The owner will just call these directly.
- L346 _public prototype_ `virtual void LivePreviewDrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI);`
- L349 _public prototype_ `virtual void Shutdown() override;` — UUVToolContextObject
- L350 _public prototype_ `virtual void OnToolEnded(UInteractiveTool* DeadTool) override;`
- L361 _public prototype_ `void SetLivePreviewSelectionUXSettings(const FLivePreviewSelectionUXSettings& Settings) const;` — Sets the UV Live Preview Selection settings
- L364 _protected member_ `TArray<FUVToolSelection> CurrentSelections;`
- L365 _protected member_ `TArray<FUVToolSelection> CurrentUnsetSelections;`
- L368 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L370 _protected member_ `TWeakObjectPtr<UInputRouter> UnwrapInputRouter = nullptr;`
- L373 _protected member_ `TObjectPtr<UUVEditorMechanicAdapterTool> MechanicAdapter = nullptr;` — `UPROPERTY()`
- L376 _protected member_ `TObjectPtr<UUVToolSelectionHighlightMechanic> HighlightMechanic = nullptr;` — `UPROPERTY()`
- L379 _protected member_ `TObjectPtr<UUVEditorMeshSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L382 _protected member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L384 _protected member_ `TUniquePtr<FSelectionChange> PendingSelectionChange = nullptr;`
- L385 _protected member_ `TUniquePtr<FUnsetSelectionChange> PendingUnsetSelectionChange = nullptr;`
- L388 _protected member_ `FHighlightOptions HighlightOptions;`
- L390 _protected member_ `FVector3d CachedUnwrapSelectionBoundingBoxCenter;`
- L391 _protected member_ `bool bCachedUnwrapSelectionBoundingBoxCenterValid = false;`
- L393 _protected member_ `bool bIsActive = false;`

#### enum `UUVToolSelectionAPI::EUVEditorSelectionMode`  
`enum class EUVEditorSelectionMode`  
_L123-133_
- desc: Mode of operation for the selection mechanic.
- L126 _public enumerator_ `None` — When None, means that mechanic will not select anything
- L128 _public enumerator_ `Vertex`
- L129 _public enumerator_ `Edge`
- L130 _public enumerator_ `Triangle`
- L131 _public enumerator_ `Island`
- L132 _public enumerator_ `Mesh`

#### struct `UUVToolSelectionAPI::FSelectionMechanicOptions`  
`struct FSelectionMechanicOptions`  
_L145-148_
- L147 _public member_ `bool bShowHoveredElements = true;`

#### struct `UUVToolSelectionAPI::FSelectionMechanicModeChangeOptions`  
`struct FSelectionMechanicModeChangeOptions`  
_L152-173_
- desc: Options for how a SetSelectionMechanicMode() call is performed
- L159 _public member_ `bool bConvertExisting = true;` — If true, any existing selection will be converted to be compatible with the new mode. For instance if an existing selection is vertices and we switch to Island selection mode, the vertex selection will be converted to a triangle selection.
- L165 _public member_ `bool bBroadcastIfConverted = true;` — If true and a conversion is performed (requires bConvertExisting to be true), the OnPreSelectionChanged and OnSelectionChanged delegates will be broadcast.
- L168 _public member_ `bool bEmitChanges = true;` — If true, emit appropriate undo / redo transactions.
- L172 _public function_ `FSelectionMechanicModeChangeOptions()` — Shouldn't really need this constructor but there seems to be a clang bug that requires it if we want to use a default-constructed instance as a default arg as we do below.

#### struct `UUVToolSelectionAPI::FHighlightOptions`  
`struct FHighlightOptions`  
_L187-208_
- L191 _public member_ `bool bBaseHighlightOnPreviews = false;` — When true, highlighting is based off of the preview meshes rather than the canonical meshes.
- L194 _public member_ `bool bAutoUpdateApplied = false;` — When true, SetSelection calls will trigger a rebuild of the applied highlight
- L197 _public member_ `bool bAutoUpdateUnwrap = false;` — When true, SetSelection calls will trigger a rebuild of the unwrap highlight
- L203 _public member_ `bool bUseCentroidForUnwrapAutoUpdate = true;` — If unwrap highlights are automatically updated, the start transform of these will be set to the centroid of the selection when the below is true. This requires centroid calculation but allows the highlight to be easily translated in response to gizmo movement.
- L207 _public member_ `bool bShowPairedEdgeHighlights = false;` — When building the unwrap highlight, show each edge and the paired edge to which it can be welded (in different colors).

#### class `UUVToolSelectionAPI::FSelectionChange`  
`class FSelectionChange : public FToolCommandChange`  
_L268-294_
- inherits: `FToolCommandChange`
- desc: An object representing a selection that can be as an undo/redo item, usually emitted by the selection API itself. Expects UUVToolSelectionAPI to be the associated UObject.
- L277 _public member_ `bool bUseStableUnwrapCanonicalIDsForEdges = true;` — When true, edge-type selections are not stored as eids, but rather as stable identifiers relative to the UnwrapCanonical mesh in the Target of the selection. This keeps them from being invalidated when other transactions edit the mesh in a way that changes Eids without actually changing topology.
- L279 _public prototype_ `virtual void SetBefore(TArray<FUVToolSelection> Selections);`
- L280 _public prototype_ `virtual void SetAfter(TArray<FUVToolSelection> Selections);`
- L284 _public prototype_ `virtual TArray<FUVToolSelection> GetBefore() const;` — Useful for storing a pending change and figuring out whether it needs to be emitted. Respects bUseStableUnwrapCanonicalIDsForEdges.
- L286 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L287 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L288 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L289 _public prototype_ `virtual FString ToString() const override;`
- L292 _protected member_ `TArray<FUVToolSelection> Before;`
- L293 _protected member_ `TArray<FUVToolSelection> After;`

#### class `UUVToolSelectionAPI::FUnsetSelectionChange`  
`class FUnsetSelectionChange : public FToolCommandChange`  
_L300-316_
- inherits: `FToolCommandChange`
- desc: An object representing an unset UV selection that can be as an undo/redo item, usually emitted by the selection API itself. Expects UUVToolSelectionAPI to be the associated UObject.
- L303 _public prototype_ `virtual void SetBefore(TArray<FUVToolSelection> Selections);`
- L304 _public prototype_ `virtual void SetAfter(TArray<FUVToolSelection> Selections);`
- L306 _public prototype_ `virtual const TArray<FUVToolSelection>& GetBefore() const;`
- L308 _public prototype_ `virtual bool HasExpired(UObject* Object) const override;`
- L309 _public prototype_ `virtual void Apply(UObject* Object) override;`
- L310 _public prototype_ `virtual void Revert(UObject* Object) override;`
- L311 _public prototype_ `virtual FString ToString() const override;`
- L314 _protected member_ `TArray<FUVToolSelection> Before;`
- L315 _protected member_ `TArray<FUVToolSelection> After;`

#### struct `UUVToolSelectionAPI::FLivePreviewSelectionUXSettings`  
`struct FLivePreviewSelectionUXSettings`  
_L353-358_
- desc: Holds the properties of the UV Live Preview Selection (in 3d viewport) for customization
- L355 _public member_ `TOptional<FColor> SelectionColor;`
- L356 _public member_ `TOptional<float> LineThickness;`
- L357 _public member_ `TOptional<float> PointSize;`

#### class `UUVToolSupportsSelection`  
`class UUVToolSupportsSelection : public UInterface`  
_L398-401_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UInterface for IUVToolSupportsSelection

#### class `IUVToolSupportsSelection`  
`class IUVToolSupportsSelection`  
_L413-427_
- desc: If a tool does not inherit from IUVToolSupportsSelection, then selection will automatically be cleared before the tool invocation via an undoable transaction, to avoid a state where the selection refers to invalid items after tool completion. If a tool does inherit from IUVToolSupportsSelection, then the UV editor will not clear the selection before invocation, allowing the tool to use it. However, the tool is expected to properly deal with selection itself and avoid an invalid state (including avoiding incorrect undo/redo selection event ordering.
- L425 _public function_ `virtual bool SupportsUnsetElementAppliedMeshSelections() const` — A tool that returns false here will have the unset element selections (ie selections of triangles that don't have associated UV's) cleared before its invocation. Returning true will keep these unset element selections, but the tool will be responsible for dealing with them and avoiding any invalid states.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L28 _prototype_ `ENUM_CLASS_FLAGS(ESelectionChangeTypeFlag);`
- L240 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPreSelectionChange, bool bEmitChangeAllowed, uint32 SelectionChangeType );` — Broadcasted right before a selection change is applied (and therefore before a selection change transaction is emitted). Useful if a user wants to emit their own bookend transaction first. @param bEmitChangeAllowed If false, the callback must not emit any undo/redo transactions, likely because this is being called from an apply/revert of an existing transaction. @param SelectionChangeType Set as some combination of ESelectionChangeCondition to describe the nature of the selection change.
- L252 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSelectionChanged, bool bEmitChangeAllowed, uint32 SelectionChangeType);` — Broadcasted after a selection change is applied (after the selection change transaction is emitted, if relevant). @param bEmitChangeAllowed If false, the callback must not emit any undo/redo transactions, likely because this is being called from an apply/revert of an existing transaction. @param SelectionChangeType Set as some combination of ESelectionChangeCondition to describe the nature of the selection change.

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/Selection/UVToolSelectionHighlightMechanic.h` (Public)


#### class `UUVToolSelectionHighlightMechanic`  
`class UUVToolSelectionHighlightMechanic : public UInteractionMechanic`  
_L31-140_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractionMechanic`
- desc: Mechanic for highlighting mesh elements (usually selection) in the UV editor.
- L35 _private typedef_ `using FUVToolSelection = UE::Geometry::FUVToolSelection;`
- L39 _public prototype_ `void Initialize(UWorld* UnwrapWorld, UWorld* LivePreviewWorld);`
- L40 _public prototype_ `void Shutdown() override;`
- L42 _public prototype_ `void SetIsVisible(bool bUnwrapHighlightVisible, bool bLivePreviewHighlightVisible);`
- L52 _public prototype_ `void RebuildUnwrapHighlight(const TArray<FUVToolSelection>& Selections, const FTransform& StartTransform, bool bUsePreviews = false);` — Rebuilds the unwrap mesh highlights. @param StartTransform The transform to consider as the start transform, so that the highlights can be repositioned easily later via SetUnwrapHighlightTransform(). @param bUsePreviews If true, the selected element positions will be gotten from the UnwrapPreview of each selection target rather than UnwrapCanonical.
- L65 _public prototype_ `void SetUnwrapHighlightTransform(const FTransform& Transform, bool bRebuildStaticPairedEdges = true, bool bUsePreviews = false);` — Set the transform of the unwrap mesh highlights without rebuilding them, likely to follow the translation of the underlying elements via gizmo. @param bRebuildStaticPairedEdges If true, and paired edge highlighting is enabled, unselected paired edges are rebuilt in the highlight. This is usually necessary because such edges may be attached to moving selected edges. @param bUsePreviews If bRebuildStaticPairedEdges is true, this will prefer to use the previews rather than the unwrap canonical.
- L71 _public prototype_ `FTransform GetUnwrapHighlightTransform();` — Get the current transform of the unwrap highlight.
- L79 _public prototype_ `void RebuildAppliedHighlightFromUnwrapSelection(const TArray<FUVToolSelection>& UnwrapSelections, bool bUsePreviews = false);` — Convert the unwrap selections to elements in the applied mesh, then highlight those there. @param bUsePreviews If true, the previews are used rather than the canonicals both for converting over to applied mesh elements and to finding the highlight positions.
- L87 _public prototype_ `void AppendAppliedHighlight(const TArray<FUVToolSelection>& AppliedSelections, bool bUsePreviews = false);` — Adds additional highlighting elements based on selection information. This is used to extend selection line sets for the unset selections if they are needed. @param bUsePreviews If true, the previews are used rather than the canonicals for finding the highlight positions.
- L94 _public prototype_ `void SetEnablePairedEdgeHighlights(bool bEnable);` — When true, edge selections also highlight the edge pairings (i.e. edges that could weld with the selected edges). Note that the call itself controls visibility and the next rebuild call, but won't cause an immediate rebuild on its own.
- L99 _public prototype_ `void SetColor(const FColor Color) const;` — Directly set the Color property of the selection line and point set.
- L104 _public prototype_ `void SetLineThickness(const float LineSize) const;` — Directly set the Size/Thickness property of the selection line set.
- L109 _public prototype_ `void SetPointSize(const float PointSize) const;` — directly set the Size property of the selection point set.
- L114 _protected member_ `TObjectPtr<APreviewGeometryActor> UnwrapGeometryActor = nullptr;` — `UPROPERTY()`
- L116 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> TriangleSetMaterial = nullptr;` — `UPROPERTY()`
- L118 _protected member_ `TWeakObjectPtr<UBasic2DTriangleSetComponent> UnwrapTriangleSet = nullptr;`
- L119 _protected member_ `TWeakObjectPtr<UBasic2DLineSetComponent> UnwrapLineSet = nullptr;`
- L120 _protected member_ `TWeakObjectPtr<UBasic2DLineSetComponent> SewEdgePairingLeftLineSet = nullptr;`
- L121 _protected member_ `TWeakObjectPtr<UBasic2DLineSetComponent> SewEdgePairingRightLineSet = nullptr;`
- L122 _protected member_ `TWeakObjectPtr<UBasic2DPointSetComponent> UnwrapPointSet = nullptr;`
- L123 _protected member_ `TWeakObjectPtr<UBasic2DLineSetComponent> UnwrapPairedEdgeLineSet = nullptr;`
- L126 _protected member_ `TObjectPtr<APreviewGeometryActor> UnwrapStationaryGeometryActor = nullptr;` — `UPROPERTY()`
- L127 _protected member_ `TWeakObjectPtr<UBasic2DLineSetComponent> SewEdgeUnselectedPairingLineSet = nullptr;`
- L132 _protected member_ `TArray<TPair<TWeakObjectPtr<UUVEditorToolMeshInput>, TArray<TPair<int32, int32>>>> StaticPairedEdgeVidsPerMesh;` — Per mesh, gives a list of endpoint vid pairs for the unselected edges that are part of edge pairs, for rebuilding when necessary.
- L135 _protected member_ `TObjectPtr<APreviewGeometryActor> LivePreviewGeometryActor = nullptr;` — `UPROPERTY()`
- L136 _protected member_ `TWeakObjectPtr<UBasic3DLineSetComponent> LivePreviewLineSet = nullptr;`
- L137 _protected member_ `TWeakObjectPtr<UBasic3DPointSetComponent> LivePreviewPointSet = nullptr;`
- L139 _protected member_ `bool bPairedEdgeHighlightsEnabled = true;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L14 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L15 _prototype_ `PREDECLARE_GEOMETRY(class FUVToolSelection);`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/TargetInterfaces/UVUnwrapDynamicMesh.h` (Public)


#### class `UUVUnwrapDynamicMesh`  
`class UUVUnwrapDynamicMesh : public UInterface`  
_L15-18_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IUVUnwrapDynamicMesh`  
`class IUVUnwrapDynamicMesh`  
_L25-33_
- desc: Interface that is able to use the UV's of a target to generate a flat FDynamicMesh representing a given layer, and to bake a modified such mesh back to the UV's of the target provided that the triangle id's have all stayed the same.
- L30 _public prototype_ `virtual int32 GetNumUVLayers() = 0;`
- L31 _public prototype_ `virtual TSharedPtr<FDynamicMesh3> GetMesh(int32 LayerIndex) = 0;`
- L32 _public prototype_ `virtual void SaveBackToUVs(const FDynamicMesh3* MeshToSave, int32 LayerIndex) = 0;`

#### Free symbols / members of external scopes

- L12 _prototype_ `PREDECLARE_USE_GEOMETRY_CLASS(FDynamicMesh3);`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/ToolTargets/UVEditorToolMeshInput.h` (Public)


#### class `UUVEditorToolMeshInput`  
`class UUVEditorToolMeshInput : public UToolTarget`  
_L39-285_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UToolTarget`
- desc: A package of the needed information for an asset being operated on by a UV editor tool. It includes a UV unwrap mesh, a mesh with the UV layer applied, and background-op-compatible previews for each. It also has convenience methods for updating all of the represenations from just one of them, using a "fast update" code path when possible. This tool target is a bit different from usual in that it is not created by a tool target manager, and therefore doesn't have an accompanying factory. Instead, it is created by the mode, because the mode has access to the worlds in which the previews need to be created. It's arguable whether this should even inherit from UToolTarget.
- L51 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> UnwrapCanonical;` — Mesh representing the unwrapped UV layer. If the UnwrapPreview is changed via background ops, then this mesh can be used to restart an operation as parameters change. Once a change is completed, this mesh should be updated (i.e., it is the "canonical" unwrap mesh, though the final UV layer truth is in the UV's of AppliedCanonical).
- L57 _public member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> UnwrapPreview = nullptr;` — `UPROPERTY()` — Preview of the unwrapped UV layer, suitable for being manipulated by background ops.
- L70 _public member_ `TSharedPtr<UE::Geometry::FDynamicMesh3> AppliedCanonical;` — A 3d mesh with the UV layer applied. This is the canonical result that will be baked back on the application of changes. It can also be used to reset background ops that may operate on AppliedPreview.
- L76 _public member_ `TObjectPtr<UMeshOpPreviewWithBackgroundCompute> AppliedPreview;` — `UPROPERTY()` — 3d preview of the asset with the UV layer updated, suitable for use with background ops.
- L84 _public member_ `TObjectPtr<UMeshElementsVisualizer> WireframeDisplay = nullptr;` — `UPROPERTY()` — Optional: a wireframe to track the mesh in unwrap preview. If set, it gets updated whenever the class updates the unwrap preview, and it is destroyed on Shutdown(). TODO: We should have a fast path for updating the wireframe...
- L90 _public member_ `bool bEnableTriangleVertexColors = false;` — `UPROPERTY()` — When enabled, this causes the unwrap preview to recieve updates to the vertex color buffers when mesh updates occur.
- L118 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectModified, UUVEditorToolMeshInput* InputObject, const FCanonicalModifiedInfo&);` — Broadcast when the canonical unwrap or applied meshes change. This gets broadcast by utility functions in this class that update those meshes (except for UpdateUnwrapCanonicalOverlayFromPositions, which is usually followed by a more complete update). If those utility functions are not used and the client updates one of those meshes, the client should broadcast the change themselves so that important related info can be updated (for instance, so that the mode can mark those objects as modified).
- L119 _public member_ `FOnObjectModified OnCanonicalModified;`
- L122 _public member_ `TObjectPtr<UToolTarget> SourceTarget = nullptr;` — Additional needed information
- L123 _public member_ `int32 AssetID = -1;` — Index into targets array
- L124 _public member_ `int32 UVLayerIndex = 0;`
- L127 _public member_ `TFunction<FVector3d(const FVector2f&)> UVToVertPosition;` — Mappings used for generating and baking back the unwrap.
- L128 _public member_ `TFunction<FVector2f(const FVector3d&)> VertPositionToUV;`
- L130 _public prototype_ `bool InitializeMeshes(UToolTarget* Target, TSharedPtr<UE::Geometry::FDynamicMesh3> AppliedCanonicalIn, UMeshOpPreviewWithBackgroundCompute* AppliedPreviewIn, int32 AssetID, int32 UVLayerIndex, UWorld* UnwrapWorld, UWorld* LivePreviewWorld, UMaterialInterface* WorkingMaterialIn, TFunction<FVector3d(const FVector2f&)> UVToVertPositionFuncIn, TFunction<FVector2f(const FVector3d&)> VertPositionToUVFuncIn);`
- L139 _public prototype_ `void Shutdown();`
- L163 _public member_ `static const TArray<int32>* const NONE_CHANGED_ARG;` — Can be passed in as a ChangedVids/ChangedElements/ChangedConnectivityTids arguments as an equivalent of passing a pointer to an empty array.
- L169 _public prototype_ `void UpdateUnwrapPreviewOverlayFromPositions(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr);` — Updates UnwrapPreview UV Overlay from UnwrapPreview vert positions. Issues a NotifyDeferredEditCompleted for both positions and UVs.
- L179 _public prototype_ `void UpdateUnwrapCanonicalOverlayFromPositions(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr);` — Updates UnwrapCanonical UV Overlay from UnwrapCanonical vert positions. Issues a NotifyDeferredEditCompleted for both positions and UVs. Doesn't broadcast because it is expected that this call is followed by another call that updates the rest of the input object.
- L187 _public prototype_ `void UpdateAppliedPreviewFromUnwrapPreview(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr);` — Updates the AppliedPreview from UnwrapPreview, without updating the non-preview meshes. Useful for updates during a drag, etc, when we only care about updating the visible items. Assumes that the overlay in UnwrapPreview is already updated.
- L194 _public prototype_ `void UpdateUnwrapPreviewFromAppliedPreview( const TArray<int32>* ChangedElementIDs = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr);` — Updates only the UnwrapPreview from AppliedPreview, without updating the non-preview meshes. Useful for transient updates when we only care about updating the visible items.
- L202 _public prototype_ `void UpdateCanonicalFromPreviews(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, bool bBroadcast = true);` — Updates the non-preview meshes from their preview counterparts. Useful, for instance, after the completion of a drag to update the canonical objects.
- L208 _public prototype_ `void UpdatePreviewsFromCanonical(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr);` — Updates the preview meshes from their canonical counterparts. Useful mainly as a way to reset the previews.
- L216 _public prototype_ `void UpdateAllFromUnwrapPreview(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr, bool bBroadcast = true);` — Updates the other meshes using the mesh in UnwrapPreview. Assumes that the overlay in UnwrapPreview is updated. Used to update everything when the applied preview was not being updated in tandem with the unwrap preview (otherwise one would use UpdateCanonicalFromPreviews).
- L223 _public prototype_ `void UpdateAllFromUnwrapCanonical(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr, bool bBroadcast = true);` — Updates the other meshes using the mesh in UnwrapCanonical. Useful when immediately applying an operation that operates directly on the unwrap mesh.
- L230 _public prototype_ `void UpdateAllFromAppliedCanonical(const TArray<int32>* ChangedVids = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr, bool bBroadcast = true);` — Updates the other meshes using the mesh in AppliedCanonical. Useful when switching UV layer indices or otherwise resetting the collection from the "original" data.
- L236 _public prototype_ `void UpdateAllFromAppliedPreview(const TArray<int32>* ChangedElementIDs = nullptr, const TArray<int32>* ChangedConnectivityTids = nullptr, const TArray<int32>* FastRenderUpdateTids = nullptr, bool bBroadcast = true);` — Updates the other meshes using the UV overlay in the live preview.
- L243 _public prototype_ `void UpdateFromCanonicalUnwrapUsingMeshChange(const UE::Geometry::FDynamicMeshChange& UnwrapCanonicalMeshChange, bool bBroadcast = true);` — Uses the stored triangles/vertices in the mesh change to update everything from the canonical unwrap. Assumes the change has already been applied to the canonical unwrap.
- L249 _public prototype_ `int32 UnwrapVidToAppliedVid(int32 UnwrapVid);` — Convert a vid in the unwrap mesh to the corresponding vid in the applied mesh (i.e., parent vertex of the element corresponding to the unwrap vertex).
- L255 _public prototype_ `void AppliedVidToUnwrapVids(int32 AppliedVid, TArray<int32>& UnwrapVidsOut);` — Get the unwrap vids corresponding to a given applied vid. These will be multiple if the vertex is a seam vertex and therefore has multiple UV elements associated with it.
- L262 _public prototype_ `virtual bool IsToolTargetValid() const;` — Returns whether or not the underlying source ToolTarget is still valid. This is separated from IsValid, which also checks the ToolTarget, in case we are interested in the status of just the ToolTarget.
- L269 _public prototype_ `virtual bool AreMeshesValid() const;` — Returns whether or not the canonical and preview meshes are still valid. This is separated from IsValid, in case we are interested in the status of just the canonical and preview meshes.
- L272 _public prototype_ `virtual bool IsValid() const override;` — UToolTarget
- L279 _protected prototype_ `virtual EMeshRenderAttributeFlags GetUnwrapUpdateAttributeFlags() const;` — Returns the currently configured mesh attribute buffer flags enabled on this target for updating the unwrap previews
- L284 _protected prototype_ `virtual EMeshRenderAttributeFlags GetAppliedUpdateAttributeFlags() const;` — Returns the currently configured mesh attribute buffer flags enabled on this target for updating the applied previews

#### struct `UUVEditorToolMeshInput::FCanonicalModifiedInfo`  
`struct FCanonicalModifiedInfo`  
_L94-108_
- desc: Information about an OnCanonicalModified broadcast. This is a struct so that we can add more information if we someday need to.
- L107 _public member_ `bool bAppliedMeshShapeChanged = false;` — This would only be true if we udpated the mesh after editing it externally, since the UV editor doesn't change mesh shape.

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L21 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh3);`
- L22 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMeshChange);`
- L118 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectModified, UUVEditorToolMeshInput* InputObject, const FCanonicalModifiedInfo&);` — Broadcast when the canonical unwrap or applied meshes change. This gets broadcast by utility functions in this class that update those meshes (except for UpdateUnwrapCanonicalOverlayFromPositions, which is usually followed by a more complete update). If those utility functions are not used and the client updates one of those meshes, the client should broadcast the change themselves so that important related info can be updated (for instance, so that the mode can mark those objects as modified).

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorBrushSelectTool.h` (Public)


#### class `UUVEditorBrushSelectToolProperties`  
`class UUVEditorBrushSelectToolProperties : public UInteractiveToolPropertySet`  
_L21-50_
- reflection: `UCLASS()`
- inherits: `UInteractiveToolPropertySet`
- L32 _public member_ `bool bClearSelectionOnEachDrag = true;` — `UPROPERTY(EditAnywhere, Category = Options)` — When true, each drag will clear the existing selection if neither Shift (add to selection) nor Ctrl (remove from selection) nor both (toggle selection) are pressed. When false, selection will not clear, requiring manual removal from selection using Ctrl.
- L36 _public member_ `bool bExpandToIslands = false;` — `UPROPERTY(EditAnywhere, Category = Options)` — When true, brush selects whole UV islands instead of individual triangles.
- L44 _public member_ `float UnwrapBrushRadius = 1.0f / (1 << 5);` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Unwrap Radius", ClampMin = "0", ClampMax = "1000000", UIMax = "1"))` — Radius of the brush in the 2D UV unwrap view.
- L49 _public member_ `float LivePreviewBrushRadius = 100.0f / (1 << 4);` — `UPROPERTY(EditAnywhere, Category = Options, meta = (DisplayName = "Preview Radius", ClampMin = "0", ClampMax = "1000000", UIMax = "100"))` — Radius of the brush in the 3D live preview view.

#### class `UUVEditorBrushSelectTool`  
`class UUVEditorBrushSelectTool : public UInteractiveTool , public IInteractiveToolNestedAcceptCancelAPI , public IUVToolSupportsSelection , public IUVEditorGenericBuildableTool`  
_L59-163_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolNestedAcceptCancelAPI,IUVToolSupportsSelection,IUVEditorGenericBuildableTool`
- desc: The brush select tool allows for brush selection of triangles on the unwrap or the live preview.
- L69 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L70 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L71 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L72 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L73 _public function_ `virtual bool HasCancel() const override`
- L74 _public function_ `virtual bool HasAccept() const override`
- L75 _public prototype_ `virtual void RegisterActions(FInteractiveToolActionSet& ActionSet) override;`
- L78 _public function_ `virtual bool SupportsNestedCancelCommand() override` — IInteractiveToolNestedAcceptCancelAPI
- L79 _public prototype_ `virtual bool CanCurrentlyNestedCancel() override;`
- L80 _public prototype_ `virtual bool ExecuteNestedCancelCommand() override;`
- L83 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — IUVEditorGenericBuildableTool
- L88 _public function_ `virtual bool SupportsUnsetElementAppliedMeshSelections() const`
- L92 _private member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L95 _private member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L98 _private member_ `TObjectPtr<UUVToolSelectionAPI> SelectionAPI = nullptr;` — `UPROPERTY()`
- L100 _private member_ `TWeakObjectPtr<const UUVEditorMeshSelectionMechanic> SelectionMechanic = nullptr;`
- L103 _private member_ `TObjectPtr<UUVToolLivePreviewAPI> LivePreviewAPI = nullptr;` — `UPROPERTY()`
- L105 _private member_ `TWeakObjectPtr<UInputRouter> LivePreviewInputRouter = nullptr;`
- L107 _private member_ `TObjectPtr<UInputBehaviorSet> LivePreviewBehaviorSet = nullptr;` — `UPROPERTY()`
- L109 _private member_ `TObjectPtr<ULocalInputBehaviorSource> LivePreviewBehaviorSource = nullptr;` — `UPROPERTY()`
- L112 _private member_ `TObjectPtr<UUVEditorBrushSelectToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L115 _private member_ `TObjectPtr<UBrushStampIndicator> UnwrapBrushIndicator = nullptr;` — `UPROPERTY()`
- L118 _private member_ `TObjectPtr<UBrushStampIndicator> LivePreviewBrushIndicator = nullptr;` — `UPROPERTY()`
- L120 _private member_ `TArray<UUVEditorMeshSelectionMechanic::FRaycastResult> PendingLivePreviewHits;`
- L123 _private member_ `TArray<FVector2d> PendingUnwrapHits;` — For unwrap, we don't necessarily need to hit the mesh to be able to select things with the brush- we just need the locations of all the hits.
- L126 _private prototype_ `void ClearSelections(bool bBroadcastAndEmit = false);` — Updates internal structures in addition to the actual selection api
- L128 _private prototype_ `void ProcessPendingUnwrapHits();`
- L129 _private prototype_ `void ProcessPendingLivePreviewHits();`
- L131 _private member_ `bool bHavePendingUnwrapHit = false;`
- L132 _private member_ `bool bHavePendingLivePreviewHit = false;`
- L134 _private member_ `int32 ShiftModifierID = 1;`
- L135 _private member_ `int32 CtrlModifierID = 2;`
- L136 _private member_ `bool bShiftToggle = false;`
- L137 _private member_ `bool bCtrlToggle = false;`
- L138 _private member_ `bool bCurrentStrokeIsSubtracting = false;`
- L149 _private member_ `TArray<int32> TempROIBuffer;`
- L153 _private member_ `bool bHaveInteracted = false;` — Currently used just so that the Esc key exits out of the tool instead of clearing the selection if we haven't yet done anything.
- L155 _private member_ `bool bHoveringUnwrap = false;`
- L156 _private member_ `bool bHoveringLivePreview = false;`
- L157 _private member_ `bool bDraggingUnwrap = false;`
- L158 _private member_ `bool bDraggingLivePreview = false;`
- L159 _private prototype_ `void UpdateViewportStateFromHoverOrDragEvent(bool bFromUnwrap, bool bIsEndEvent, bool bDragging);`
- L161 _private prototype_ `void IncreaseBrushRadiusAction();`
- L162 _private prototype_ `void DecreaseBrushRadiusAction();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorLayerEditTool.h` (Public)


#### class `UUVEditorChannelEditToolBuilder`  
`class UUVEditorChannelEditToolBuilder : public UInteractiveToolBuilder`  
_L20-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L25 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L26 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L30 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.

#### enum `EChannelEditToolAction`  
`enum class EChannelEditToolAction`  
_L34-41_
- reflection: `UENUM()`
- L36 _public enumerator_ `NoAction`
- L38 _public enumerator_ `Add`
- L39 _public enumerator_ `Copy`
- L40 _public enumerator_ `Delete`

#### class `UUVEditorChannelEditSettings`  
`class UUVEditorChannelEditSettings : public UInteractiveToolPropertySet`  
_L45-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L51 _public member_ `EChannelEditToolAction Action = EChannelEditToolAction::Add;` — `UPROPERTY(EditAnywhere, Category = Options, meta = (InvalidEnumValues = "NoAction"))` — UV Layer Edit action to preform

#### class `UUVEditorChannelEditTargetProperties`  
`class UUVEditorChannelEditTargetProperties : public UInteractiveToolPropertySet`  
_L55-123_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L61 _public member_ `FString Asset;` — `UPROPERTY(EditAnywhere, Category = "UVChannels", meta = (DisplayName = "Asset", GetOptions = GetAssetNames, EditCondition = "bActionNeedsAsset", EditConditionHides = true, HideEditConditionToggle = true))`
- L64 _public prototype_ `const TArray<FString>& GetAssetNames();` — `UFUNCTION()`
- L67 _public member_ `FString TargetChannel;` — `UPROPERTY(EditAnywhere, Category = "UVChannels", meta = (DisplayName = "Target UV Channel", GetOptions = GetUVChannelNames, EditCondition = "bActionNeedsTarget", EditConditionHides = true, HideEditConditionToggle = true))`
- L70 _public member_ `FString ReferenceChannel;` — `UPROPERTY(EditAnywhere, Category = "UVChannels", meta = (DisplayName = "Source UV Channel", GetOptions = GetUVChannelNames, EditCondition = "bActionNeedsReference", EditConditionHides = true, HideEditConditionToggle = true))`
- L73 _public prototype_ `const TArray<FString>& GetUVChannelNames();` — `UFUNCTION()`
- L75 _public member_ `TArray<FString> UVChannelNames;`
- L76 _public member_ `TArray<FString> UVAssetNames;`
- L79 _public member_ `TArray<int32> NumUVChannelsPerAsset;` — 1:1 with UVAssetNames
- L82 _public member_ `bool bActionNeedsAsset = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L85 _public member_ `bool bActionNeedsReference = false;` — `UPROPERTY(meta = (TransientToolProperty))`
- L88 _public member_ `bool bActionNeedsTarget = true;` — `UPROPERTY(meta = (TransientToolProperty))`
- L91 _public prototype_ `void Initialize( const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn, bool bInitializeSelection);`
- L95 _public prototype_ `void SetUsageFlags(EChannelEditToolAction Action);`
- L102 _public prototype_ `bool ValidateUVAssetSelection(bool bUpdateIfInvalid);` — Verify that the UV asset selection is valid @param bUpdateIfInvalid if selection is not valid, reset UVAsset to Asset0 or empty if no assets exist @return true if selection in UVAsset is an entry in UVAssetNames.
- L109 _public prototype_ `bool ValidateUVChannelSelection(bool bUpdateIfInvalid);` — Verify that the UV channel selection is valid @param bUpdateIfInvalid if selection is not valid, UVChannel to UV0 or empty if no UV channels exist @return true if selection in UVChannel is an entry in UVChannelNamesList.
- L115 _public prototype_ `int32 GetSelectedAssetID();` — @return selected UV asset ID, or -1 if invalid selection
- L122 _public prototype_ `int32 GetSelectedChannelIndex(bool bForceToZeroOnFailure = false, bool bUseReference = false);` — @param bForceToZeroOnFailure if true, then instead of returning -1 we return 0 so calling code can fallback to default UV paths @param bUseReference if true, get the selected reference channel index, otherwise return the target channel's index. @return selected UV channel index, or -1 if invalid selection, or 0 if invalid selection and bool bForceToZeroOnFailure = true

#### class `UUVEditorChannelEditAddProperties`  
`class UUVEditorChannelEditAddProperties : public UInteractiveToolPropertySet`  
_L126-131_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`

#### class `UUVEditorChannelEditCopyProperties`  
`class UUVEditorChannelEditCopyProperties : public UInteractiveToolPropertySet`  
_L134-139_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`

#### class `UUVEditorChannelEditDeleteProperties`  
`class UUVEditorChannelEditDeleteProperties : public UInteractiveToolPropertySet`  
_L142-147_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`

#### class `UUVEditorChannelEditToolActionPropertySet`  
`class UUVEditorChannelEditToolActionPropertySet : public UInteractiveToolPropertySet`  
_L150-162_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L155 _public member_ `TWeakObjectPtr<UUVEditorChannelEditTool> ParentTool;`
- L157 _public function_ `void Initialize(UUVEditorChannelEditTool* ParentToolIn)`
- L158 _public prototype_ `void PostAction(EChannelEditToolAction Action);`
- L161 _public prototype_ `void Apply();` — `UFUNCTION(CallInEditor, Category = Actions)`

#### class `UUVEditorChannelEditTool`  
`class UUVEditorChannelEditTool : public UInteractiveTool`  
_L168-260_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool`
- L177 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — The tool will operate on the meshes given here.
- L182 _public prototype_ `virtual void Setup() override;`
- L183 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L185 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L187 _public function_ `virtual bool HasCancel() const override`
- L188 _public function_ `virtual bool HasAccept() const override`
- L189 _public function_ `virtual bool CanAccept() const override`
- L191 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L193 _public prototype_ `void RequestAction(EChannelEditToolAction ActionType);`
- L194 _public prototype_ `EChannelEditToolAction ActiveAction() const;`
- L198 _protected prototype_ `void ApplyVisbleChannelChange();`
- L199 _protected prototype_ `void UpdateChannelSelectionProperties(int32 ChangingAsset);`
- L201 _protected prototype_ `void AddChannel();`
- L202 _protected prototype_ `void CopyChannel();`
- L203 _protected prototype_ `void DeleteChannel();`
- L204 _protected member_ `int32 ActiveAsset;`
- L205 _protected member_ `int32 ActiveChannel;`
- L206 _protected member_ `int32 ReferenceChannel;`
- L208 _protected member_ `EChannelEditToolAction PendingAction = EChannelEditToolAction::NoAction;`
- L211 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L214 _protected member_ `TObjectPtr<UUVEditorChannelEditToolActionPropertySet> ToolActions = nullptr;` — `UPROPERTY()`
- L217 _protected member_ `TObjectPtr<UUVEditorChannelEditSettings> ActionSelectionProperties = nullptr;` — `UPROPERTY()`
- L220 _protected member_ `TObjectPtr<UUVEditorChannelEditTargetProperties> SourceChannelProperties = nullptr;` — `UPROPERTY()`
- L223 _protected member_ `TObjectPtr<UUVEditorChannelEditAddProperties> AddActionProperties = nullptr;` — `UPROPERTY()`
- L226 _protected member_ `TObjectPtr<UUVEditorChannelEditCopyProperties> CopyActionProperties = nullptr;` — `UPROPERTY()`
- L229 _protected member_ `TObjectPtr<UUVEditorChannelEditDeleteProperties> DeleteActionProperties = nullptr;` — `UPROPERTY()`
- L232 _protected member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L256 _protected member_ `TArray<FActionHistoryItem> AnalyticsActionHistory;`
- L257 _protected member_ `UE::Geometry::UVEditorAnalytics::FTargetAnalytics InputTargetAnalytics;`
- L258 _protected member_ `FDateTime ToolStartTimeAnalytics;`
- L259 _protected prototype_ `void RecordAnalytics();`

#### struct `UUVEditorChannelEditTool::FActionHistoryItem`  
`struct FActionHistoryItem`  
_L238-254_
- L240 _public member_ `FDateTime Timestamp;`
- L241 _public member_ `EChannelEditToolAction ActionType = EChannelEditToolAction::NoAction;`
- L246 _public member_ `int32 FirstOperandIndex = -1;` — if ActionType == Add    then FirstOperandIndex is the index of the added UV layer if ActionType == Delete then FirstOperandIndex is the index of the deleted UV layer if ActionType == Copy   then FirstOperandIndex is the index of the source UV layer
- L251 _public member_ `int32 SecondOperandIndex = -1;` — if ActionType == Add    then SecondOperandIndex is unused if ActionType == Delete then SecondOperandIndex is unused if ActionType == Copy   then SecondOperandIndex is the index of the target UV layer
- L253 _public member_ `bool bDeleteActionWasActuallyClear = false;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorLayoutTool.h` (Public)


#### class `UUVEditorLayoutToolBuilder`  
`class UUVEditorLayoutToolBuilder : public UInteractiveToolBuilder`  
_L22-33_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L27 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L28 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L32 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.

#### class `UUVEditorLayoutTool`  
`class UUVEditorLayoutTool : public UInteractiveTool, public IUVToolSupportsSelection`  
_L39-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IUVToolSupportsSelection`
- L48 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — The tool will operate on the meshes given here.
- L53 _public prototype_ `virtual void Setup() override;`
- L54 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L56 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L58 _public function_ `virtual bool HasCancel() const override`
- L59 _public function_ `virtual bool HasAccept() const override`
- L60 _public prototype_ `virtual bool CanAccept() const override;`
- L62 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L66 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L69 _protected member_ `TObjectPtr<UUVLayoutProperties> Settings = nullptr;` — `UPROPERTY()`
- L72 _protected member_ `TArray<TObjectPtr<UUVLayoutOperatorFactory>> Factories;` — `UPROPERTY()`
- L75 _protected member_ `TObjectPtr<UUVToolSelectionAPI> UVToolSelectionAPI = nullptr;` — `UPROPERTY()`
- L79 _protected member_ `TObjectPtr< UUVTool2DViewportAPI> UVTool2DViewportAPI = nullptr;` — `UPROPERTY()`
- L85 _protected member_ `UE::Geometry::UVEditorAnalytics::FTargetAnalytics InputTargetAnalytics;`
- L86 _protected member_ `FDateTime ToolStartTimeAnalytics;`
- L87 _protected prototype_ `void RecordAnalytics();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorLogging.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogUVEditor, Log, All);`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorMechanicAdapterTool.h` (Public)


#### class `UUVEditorMechanicAdapterTool`  
`class UUVEditorMechanicAdapterTool : public UInteractiveTool`  
_L20-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool`
- desc: This is a dummy tool that only exists to make it possible for mechanics to be used in outside of an actual tool. The tool can be passed in to the mechanics' Setup() calls. If necessary, the behaviors can be extracted via GetInputBehaviors() to be placed into an input router.
- L25 _public member_ `UInteractiveToolManager* ToolManager = nullptr;`
- L27 _public function_ `virtual UInteractiveToolManager* GetToolManager() const override`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorRecomputeUVsTool.h` (Public)


#### class `UUVEditorRecomputeUVsToolBuilder`  
`class UUVEditorRecomputeUVsToolBuilder : public UInteractiveToolBuilder`  
_L31-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L36 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L37 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L41 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.

#### class `UUVEditorRecomputeUVsTool`  
`class UUVEditorRecomputeUVsTool : public UInteractiveTool, public IUVToolSupportsSelection`  
_L49-104_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IUVToolSupportsSelection`
- desc: UUVEditorRecomputeUVsTool Recomputes UVs based on existing segmentations of the mesh
- L54 _public prototype_ `virtual void Setup() override;`
- L55 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L57 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L59 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L61 _public function_ `virtual bool HasCancel() const override`
- L62 _public function_ `virtual bool HasAccept() const override`
- L63 _public prototype_ `virtual bool CanAccept() const override;`
- L65 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L71 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — The tool will operate on the meshes given here.
- L78 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L81 _protected member_ `TObjectPtr<URecomputeUVsToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L84 _protected member_ `TObjectPtr<UPolygroupLayersProperties> PolygroupLayerProperties = nullptr;` — `UPROPERTY()`
- L87 _protected member_ `TArray<TObjectPtr<URecomputeUVsOpFactory>> Factories;` — `UPROPERTY()`
- L90 _protected member_ `TObjectPtr<UUVToolSelectionAPI> UVToolSelectionAPI = nullptr;` — `UPROPERTY()`
- L93 _protected member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> ActiveGroupSet;`
- L94 _protected prototype_ `void OnSelectedGroupLayerChanged();`
- L95 _protected prototype_ `void UpdateActiveGroupLayer(bool bUpdateFactories = true);`
- L101 _protected member_ `UE::Geometry::UVEditorAnalytics::FTargetAnalytics InputTargetAnalytics;`
- L102 _protected member_ `FDateTime ToolStartTimeAnalytics;`
- L103 _protected prototype_ `void RecordAnalytics();`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorSeamTool.h` (Public)


#### enum `EUVEditorSeamMode`  
`enum class EUVEditorSeamMode : uint8`  
_L30-36_
- reflection: `UENUM()`
- L33 _public enumerator_ `Cut = 0` — Marked path will cut the UV island, creating new seams.
- L35 _public enumerator_ `Join = 1` — Marked path will join the UV island, removing seams.

#### class `UUVEditorSeamToolProperties`  
`class UUVEditorSeamToolProperties : public UInteractiveToolPropertySet`  
_L39-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L46 _public member_ `EUVEditorSeamMode Mode = EUVEditorSeamMode::Cut;` — `UPROPERTY(EditAnywhere, Category = Options)`
- L56 _public member_ `double PathSimilarityWeight = 200;` — `UPROPERTY(EditAnywhere, Category = Options, AdvancedDisplay, meta = ( ClampMin = 0, UIMax = 1000))` — Setting this above 0 will include a measure of path similarity to seam transfer, so that among similarly short paths, we pick one that lies closer to the edge. Useful in cases where the path is on the wrong diagonal to the triangulation, because it prefers a closely zigzagging path over a wider "up and over" path that has similar length. If set to 0, only path length is used.

#### class `UUVEditorSeamToolBuilder`  
`class UUVEditorSeamToolBuilder : public UInteractiveToolBuilder`  
_L60-71_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L65 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L66 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L70 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — These are pointers so that they can be updated under the builder without having to reset them after things are reinitialized.

#### class `UUVEditorSeamTool`  
`class UUVEditorSeamTool : public UInteractiveTool, public IInteractiveToolNestedAcceptCancelAPI`  
_L74-207_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolNestedAcceptCancelAPI`
- L80 _public typedef_ `using FDynamicMeshAABBTree3 = UE::Geometry::FDynamicMeshAABBTree3;`
- L82 _public prototype_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn);`
- L85 _public prototype_ `void EditLockedPath( TUniqueFunction<void(TArray<int32>& LockedPathInOut)> EditFunction, int32 MeshIndex);` — For use by undo/redo
- L89 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L90 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L91 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L92 _public function_ `virtual bool HasCancel() const override`
- L93 _public function_ `virtual bool HasAccept() const override`
- L96 _public function_ `virtual bool SupportsNestedCancelCommand() override` — IInteractiveToolNestedAcceptCancelAPI
- L97 _public prototype_ `virtual bool CanCurrentlyNestedCancel() override;`
- L98 _public prototype_ `virtual bool ExecuteNestedCancelCommand() override;`
- L99 _public function_ `virtual bool SupportsNestedAcceptCommand() override`
- L100 _public prototype_ `virtual bool CanCurrentlyNestedAccept() override;`
- L101 _public prototype_ `virtual bool ExecuteNestedAcceptCommand() override;`
- L103 _protected prototype_ `void ReconstructExistingSeamsVisualization();`
- L104 _protected prototype_ `void ReconstructLockedPathVisualization();`
- L106 _protected prototype_ `int32 Get2DHitVertex(const FRay& WorldRayIn, int32* IndexOf2DSpatialOut = nullptr);`
- L107 _protected prototype_ `int32 Get3DHitVertex(const FRay& WorldRayIn, int32* IndexOf3DSpatialOut = nullptr);`
- L109 _protected prototype_ `void OnMeshVertexClicked(int32 Vid, int32 IndexOfMesh, bool bVidIsFromUnwrap);`
- L110 _protected prototype_ `void OnMeshVertexHovered(int32 Vid, int32 IndexOfMesh, bool bVidIsFromUnwrap);`
- L111 _protected prototype_ `void UpdateHover();`
- L113 _protected prototype_ `void ClearHover(bool bClearHoverInfo = true);` — @param bClearHoverInfo If true, also clears HoverVid, etc in addition to just clearing display.
- L114 _protected prototype_ `void ResetPreviewColors();`
- L115 _protected prototype_ `void ApplyClick();`
- L117 _protected prototype_ `void ApplySeam(const TArray<int32>& AppliedVidsIn);` — Clears LockedAppliedVids, but builds seam off of AppliedVidsIn
- L118 _protected prototype_ `void ClearLockedPath(bool bEmitChange = true);`
- L120 _protected prototype_ `void UpdateToolMessage();`
- L122 _protected member_ `int32 TemporaryModeToggleModifierID = 1;`
- L123 _protected member_ `bool bModeIsTemporarilyToggled;`
- L124 _protected prototype_ `bool IsInJoinMode() const;`
- L125 _protected prototype_ `void OnSeamModeChanged();`
- L133 _protected member_ `EState State = EState::WaitingToStart;`
- L136 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L139 _protected member_ `TObjectPtr< UUVEditorSeamToolProperties> Settings = nullptr;` — `UPROPERTY()`
- L142 _protected member_ `TObjectPtr<UUVToolLivePreviewAPI> LivePreviewAPI = nullptr;` — `UPROPERTY()`
- L145 _protected member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L148 _protected member_ `TObjectPtr<UInputBehaviorSet> LivePreviewBehaviorSet = nullptr;` — `UPROPERTY()`
- L151 _protected member_ `TObjectPtr<ULocalInputBehaviorSource> LivePreviewBehaviorSource = nullptr;` — `UPROPERTY()`
- L154 _protected member_ `TObjectPtr<UPreviewGeometry> UnwrapGeometry = nullptr;` — `UPROPERTY()`
- L157 _protected member_ `TObjectPtr<UPreviewGeometry> LivePreviewGeometry = nullptr;` — `UPROPERTY()`
- L159 _protected member_ `TWeakObjectPtr<UInputRouter> LivePreviewInputRouter = nullptr;`
- L161 _protected member_ `TArray<TSharedPtr<FDynamicMeshAABBTree3>> Spatials2D;` — 1:1 with targets
- L162 _protected member_ `TArray<TSharedPtr<FDynamicMeshAABBTree3>> Spatials3D;` — 1:1 with targets
- L164 _protected member_ `FViewCameraState LivePreviewCameraState;`
- L167 _protected member_ `int32 ClickedVid = IndexConstants::InvalidID;` — Used to remember click info to apply on tick
- L168 _protected member_ `int32 ClickedMeshIndex = -1;`
- L169 _protected member_ `bool bClickWasInUnwrap = false;`
- L172 _protected member_ `int32 HoverVid = IndexConstants::InvalidID;` — Used to remember hover info to apply on tick
- L173 _protected member_ `int32 HoverMeshIndex = IndexConstants::InvalidID;`
- L174 _protected member_ `bool bHoverVidIsFromUnwrap = false;`
- L175 _protected member_ `int32 LastHoverVid = IndexConstants::InvalidID;`
- L176 _protected member_ `int32 LastHoverMeshIndex = IndexConstants::InvalidID;`
- L177 _protected member_ `bool bLastHoverVidWasFromUnwrap = false;`
- L180 _protected member_ `int32 SeamStartAppliedVid = IndexConstants::InvalidID;` — Used to know when to end the seam.
- L181 _protected member_ `int32 LastLockedAppliedVid = IndexConstants::InvalidID;`
- L183 _protected member_ `TArray<int32> LockedPath;`
- L184 _protected member_ `TArray<int32> PreviewPath;`
- L186 _protected prototype_ `FColor GetLockedPathColor() const;`
- L187 _protected prototype_ `FColor GetExtendPathColor() const;`
- L191 _protected member_ `bool bCompletionColorOverride = false;` — When true, the entire path is changed to the "completion" color to show that the next click will complete the path.
- L197 _protected member_ `UE::Geometry::UVEditorAnalytics::FTargetAnalytics InputTargetAnalytics;`
- L198 _protected member_ `FDateTime ToolStartTimeAnalytics;`
- L199 _protected prototype_ `void RecordAnalytics();`
- L202 _private prototype_ `void GetVidPath(const UUVEditorToolMeshInput& Target, bool bUnwrapMeshSource, const TArray<int32>& StartVids, int32 EndVid, TArray<int32>& VidPathOut);`
- L205 _private member_ `TArray<double> UnwrapMaxDims;`
- L206 _private member_ `TArray<double> AppliedMeshMaxDims;`

#### enum `UUVEditorSeamTool::EState`  
`enum class EState`  
_L127-131_
- L129 _public enumerator_ `WaitingToStart`
- L130 _public enumerator_ `SeamInProgress`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L27 _prototype_ `PREDECLARE_GEOMETRY(class FDynamicMesh);`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorStyle.h` (Public)


#### class `FUVEditorStyle`  
`class FUVEditorStyle : public FSlateStyleSet`  
_L13-26_
- inherits: `FSlateStyleSet`
- desc: Slate style set for UV Editor
- L17 _public member_ `static FName StyleName;`
- L20 _public prototype_ `static FUVEditorStyle& Get();` — Access the singleton instance for this style set
- L24 _private prototype_ `FUVEditorStyle();`
- L25 _private prototype_ `~FUVEditorStyle();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorTexelDensityTool.h` (Public)


#### class `UUVEditorTexelDensityToolBuilder`  
`class UUVEditorTexelDensityToolBuilder : public UInteractiveToolBuilder`  
_L37-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L42 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L43 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L47 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.

#### enum `ETexelDensityToolAction`  
`enum class ETexelDensityToolAction`  
_L51-58_
- reflection: `UENUM()`
- L53 _public enumerator_ `NoAction`
- L54 _public enumerator_ `Processing`
- L56 _public enumerator_ `BeginSamping`
- L57 _public enumerator_ `Sampling`

#### class `UUVEditorTexelDensityActionSettings`  
`class UUVEditorTexelDensityActionSettings : public UInteractiveToolPropertySet`  
_L62-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L67 _public member_ `TWeakObjectPtr<UUVEditorTexelDensityTool> ParentTool;`
- L69 _public function_ `void Initialize(UUVEditorTexelDensityTool* ParentToolIn)`
- L70 _public prototype_ `void PostAction(ETexelDensityToolAction Action);`
- L73 _public prototype_ `void SampleTexelDensity();` — `UFUNCTION(CallInEditor, Category = Actions)`

#### class `UUVEditorTexelDensityToolSettings`  
`class UUVEditorTexelDensityToolSettings : public UUVEditorTexelDensitySettings`  
_L77-86_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorTexelDensitySettings`
- L82 _public member_ `TWeakObjectPtr<UUVEditorTexelDensityTool> ParentTool;`
- L83 _public function_ `void Initialize(UUVEditorTexelDensityTool* ParentToolIn)`
- L85 _public prototype_ `virtual bool InSamplingMode() const override;`

#### class `UUVEditorTexelDensityTool`  
`class UUVEditorTexelDensityTool : public UInteractiveTool, public IUVToolSupportsSelection`  
_L92-214_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IUVToolSupportsSelection`
- desc: UUVEditorRecomputeUVsTool Recomputes UVs based on existing segmentations of the mesh
- L97 _public prototype_ `virtual void Setup() override;`
- L98 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L100 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L102 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L104 _public function_ `virtual bool HasCancel() const override`
- L105 _public function_ `virtual bool HasAccept() const override`
- L106 _public prototype_ `virtual bool CanAccept() const override;`
- L108 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L114 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — The tool will operate on the meshes given here.
- L120 _public prototype_ `void RequestAction(ETexelDensityToolAction ActionType);`
- L121 _public prototype_ `ETexelDensityToolAction ActiveAction() const;`
- L125 _private member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L128 _private member_ `TObjectPtr<UUVEditorTexelDensitySettings> Settings = nullptr;` — `UPROPERTY()`
- L131 _private member_ `TObjectPtr<UUVEditorTexelDensityActionSettings> ActionSettings = nullptr;` — `UPROPERTY()`
- L133 _private member_ `ETexelDensityToolAction PendingAction = ETexelDensityToolAction::NoAction;`
- L136 _private member_ `TObjectPtr<UUVToolSelectionAPI> UVToolSelectionAPI = nullptr;` — `UPROPERTY()`
- L139 _private member_ `TObjectPtr<UUVToolLivePreviewAPI> LivePreviewAPI = nullptr;` — `UPROPERTY()`
- L143 _private member_ `TObjectPtr< UUVTool2DViewportAPI> UVTool2DViewportAPI = nullptr;` — `UPROPERTY()`
- L146 _private member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L149 _private member_ `TArray<TObjectPtr<UUVTexelDensityOperatorFactory>> Factories;` — `UPROPERTY()`
- L151 _private member_ `int32 RemainingTargetsToProcess;`
- L152 _private prototype_ `void PerformBackgroundScalingTask();`
- L155 _private member_ `TObjectPtr<UInputBehaviorSet> LivePreviewBehaviorSet = nullptr;` — `UPROPERTY()`
- L158 _private member_ `TObjectPtr<ULocalInputBehaviorSource> LivePreviewBehaviorSource = nullptr;` — `UPROPERTY()`
- L161 _private member_ `TObjectPtr<UPreviewGeometry> UnwrapGeometry = nullptr;` — `UPROPERTY()`
- L164 _private member_ `TObjectPtr<UPreviewGeometry> LivePreviewGeometry = nullptr;` — `UPROPERTY()`
- L166 _private member_ `TWeakObjectPtr<UInputRouter> LivePreviewInputRouter = nullptr;`
- L168 _private member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3>> Spatials2D;` — 1:1 with targets
- L169 _private member_ `TArray<TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3>> Spatials3D;` — 1:1 with targets
- L171 _private member_ `FViewCameraState LivePreviewCameraState;`
- L174 _private member_ `TObjectPtr<UMaterialInstanceDynamic> TriangleSetMaterial = nullptr;` — `UPROPERTY()`
- L176 _private member_ `TSharedPtr<UE::Geometry::FPolygroupSet, ESPMode::ThreadSafe> ActiveGroupSet;`
- L177 _private prototype_ `void OnSelectedGroupLayerChanged();`
- L178 _private prototype_ `void UpdateActiveGroupLayer(bool bUpdateFactories = true);`
- L180 _private prototype_ `int32 Get2DHitTriangle(const FRay& WorldRayIn, int32* IndexOf2DSpatialOut = nullptr);`
- L181 _private prototype_ `int32 Get3DHitTriangle(const FRay& WorldRayIn, int32* IndexOf2DSpatialOut = nullptr);`
- L183 _private prototype_ `void OnMeshTriangleClicked(int32 Tid, int32 IndexOfMesh, bool bTidIsFromUnwrap);`
- L184 _private prototype_ `void OnMeshTriangleHovered(int32 Tid, int32 IndexOfMesh, bool bTidIsFromUnwrap);`
- L185 _private prototype_ `void UpdateHover();`
- L187 _private prototype_ `void ClearHover(bool bClearHoverInfo = true);` — @param bClearHoverInfo If true, also clears HoverVid, etc in addition to just clearing display.
- L189 _private prototype_ `void ApplyClick();`
- L190 _private prototype_ `void UpdateToolMessage();`
- L193 _private member_ `int32 ClickedTid = IndexConstants::InvalidID;` — Used to remember click info to apply on tick
- L194 _private member_ `int32 ClickedMeshIndex = -1;`
- L195 _private member_ `bool bClickWasInUnwrap = false;`
- L198 _private member_ `int32 HoverTid = IndexConstants::InvalidID;` — Used to remember hover info to apply on tick
- L199 _private member_ `int32 HoverMeshIndex = IndexConstants::InvalidID;`
- L200 _private member_ `bool bHoverTidIsFromUnwrap = false;`
- L201 _private member_ `int32 LastHoverTid = IndexConstants::InvalidID;`
- L202 _private member_ `int32 LastHoverMeshIndex = IndexConstants::InvalidID;`
- L203 _private member_ `bool bLastHoverTidWasFromUnwrap = false;`
- L209 _private member_ `UE::Geometry::UVEditorAnalytics::FTargetAnalytics InputTargetAnalytics;`
- L210 _private member_ `FDateTime ToolStartTimeAnalytics;`
- L211 _private prototype_ `void RecordAnalytics();`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorToolAnalyticsUtils.h` (Public)


#### struct `UE::Geometry::UVEditorAnalytics::FTargetAnalytics`  
`struct FTargetAnalytics`  
_L29-43_
- L31 _public member_ `int64 AllAssetsNumVertices = 0;`
- L32 _public member_ `int64 AllAssetsNumTriangles = 0;`
- L33 _public member_ `int64 AllAssetsNumUVLayers = 0;`
- L35 _public member_ `TArray<int32> PerAssetNumVertices;`
- L36 _public member_ `TArray<int32> PerAssetNumTriangles;`
- L37 _public member_ `TArray<int32> PerAssetNumUVLayers;`
- L38 _public member_ `TArray<int32> PerAssetActiveUVChannelIndex;`
- L39 _public member_ `TArray<int32> PerAssetActiveUVChannelNumVertices;`
- L40 _public member_ `TArray<int32> PerAssetActiveUVChannelNumTriangles;`
- L42 _public prototype_ `void AppendToAttributes(TArray<FAnalyticsEventAttribute>& Attributes, FString Prefix = "") const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITORTOOLS_API`
- L11 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Geometry` (scope `UE`)
- L16 _namespace_ `namespace UVEditorAnalytics` (scope `UE::Geometry`)
- L20 _function_ `template <typename EnumType> FAnalyticsEventAttribute AnalyticsEventAttributeEnum(const FString& AttributeName, EnumType EnumValue)` (scope `UE::Geometry::UVEditorAnalytics`)
- L27 _prototype_ `FString UVEditorAnalyticsEventName(const FString& ToolEventName);` (scope `UE::Geometry::UVEditorAnalytics`)
- L45 _prototype_ `FTargetAnalytics CollectTargetAnalytics(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& Targets);` (scope `UE::Geometry::UVEditorAnalytics`)

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorToolBase.h` (Public)


#### class `UUVEditorGenericBuildableTool`  
`class UUVEditorGenericBuildableTool : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: UObject for IUVEditorGenericBuildableTool

#### class `IUVEditorGenericBuildableTool`  
`class IUVEditorGenericBuildableTool`  
_L26-31_
- desc: Interface that allows a component to receive various gizmo-specific callbacks while still inheriting from some class other than UGizmoBaseComponent.
- L30 _public prototype_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn) = 0;`

#### class `UGenericUVEditorToolBuilder`  
`class UGenericUVEditorToolBuilder : public UInteractiveToolBuilder`  
_L39-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: Simple builder that just instantiates the given class and passes in the targets. Can be used for any UV tools that don't need special handling, as long as they implement IUVEditorGenericBuildableTool.
- L47 _public prototype_ `virtual void Initialize(TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn, TSubclassOf<UInteractiveTool> ToolClassIn);` — @param ToolClassIn Must implement IUVEditorGenericBuildableTool.
- L49 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L50 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L55 _private member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.
- L57 _private member_ `TSubclassOf<UInteractiveTool> ToolClass;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorToolsModule.h` (Public)


#### class `FUVEditorToolsModule`  
`class FUVEditorToolsModule : public IModuleInterface`  
_L8-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorTransformTool.h` (Public)


#### class `UUVEditorTransformToolDisplayProperties`  
`class UUVEditorTransformToolDisplayProperties : public UInteractiveToolPropertySet`  
_L28-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- desc: Visualization settings for the TransformTool
- L34 _public member_ `bool bDrawPivots = true;` — `UPROPERTY(EditAnywhere, Category = "Tool Display Settings", meta = (DisplayName = "Display Tool Pivots"))` — Draw the tool's active pivot location if needed.

#### class `UUVEditorBaseTransformToolBuilder`  
`class UUVEditorBaseTransformToolBuilder : public UInteractiveToolBuilder`  
_L38-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L43 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L44 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L48 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.
- L51 _protected prototype_ `virtual void ConfigureTool(UUVEditorTransformTool* NewTool) const;`

#### class `UUVEditorTransformToolBuilder`  
`class UUVEditorTransformToolBuilder : public UUVEditorBaseTransformToolBuilder`  
_L55-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorBaseTransformToolBuilder`
- L60 _protected prototype_ `virtual void ConfigureTool(UUVEditorTransformTool* NewTool) const override;`

#### class `UUVEditorAlignToolBuilder`  
`class UUVEditorAlignToolBuilder : public UUVEditorBaseTransformToolBuilder`  
_L64-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorBaseTransformToolBuilder`
- L69 _protected prototype_ `virtual void ConfigureTool(UUVEditorTransformTool* NewTool) const override;`

#### class `UUVEditorDistributeToolBuilder`  
`class UUVEditorDistributeToolBuilder : public UUVEditorBaseTransformToolBuilder`  
_L73-79_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UUVEditorBaseTransformToolBuilder`
- L78 _protected prototype_ `virtual void ConfigureTool(UUVEditorTransformTool* NewTool) const override;`

#### class `UUVEditorTransformTool`  
`class UUVEditorTransformTool : public UInteractiveTool, public IUVToolSupportsSelection`  
_L85-142_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IUVToolSupportsSelection`
- L94 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — The tool will operate on the meshes given here.
- L99 _public prototype_ `void SetToolMode(const EUVEditorUVTransformType& Mode);`
- L101 _public prototype_ `virtual void Setup() override;`
- L102 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L104 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L106 _public function_ `virtual bool HasCancel() const override`
- L107 _public function_ `virtual bool HasAccept() const override`
- L108 _public prototype_ `virtual bool CanAccept() const override;`
- L110 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L112 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L116 _protected member_ `TOptional<EUVEditorUVTransformType> ToolMode;`
- L119 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L122 _protected member_ `TObjectPtr<UUVEditorUVTransformPropertiesBase> Settings = nullptr;` — `UPROPERTY()`
- L125 _protected member_ `TObjectPtr<UUVEditorTransformToolDisplayProperties> DisplaySettings = nullptr;` — `UPROPERTY()`
- L128 _protected member_ `TArray<TObjectPtr<UUVEditorUVTransformOperatorFactory>> Factories;` — `UPROPERTY()`
- L131 _protected member_ `TObjectPtr<UUVToolSelectionAPI> UVToolSelectionAPI = nullptr;` — `UPROPERTY()`
- L133 _protected member_ `TArray<TArray<FVector2D>> PerTargetPivotLocations;`
- L139 _protected member_ `UE::Geometry::UVEditorAnalytics::FTargetAnalytics InputTargetAnalytics;`
- L140 _protected member_ `FDateTime ToolStartTimeAnalytics;`
- L141 _protected prototype_ `void RecordAnalytics();`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorUVSnapshotTool.h` (Public)


#### class `UUVEditorUVSnapshotToolBuilder`  
`class UUVEditorUVSnapshotToolBuilder : public UInteractiveToolBuilder`  
_L24-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- desc: ToolBuilder
- L28 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L29 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L33 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets. Supports only one target

#### class `UUVEditorUVSnapshotTool`  
`class UUVEditorUVSnapshotTool : public UInteractiveTool, public IUVToolSupportsSelection, public UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshMapBaker>`  
_L42-136_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IUVToolSupportsSelection,UE::Geometry::IGenericDataOperatorFactory<UE::Geometry::FMeshMapBaker>`
- desc: UV Snapshot Tool Exports a texture asset of a UV Layout
- L47 _public prototype_ `virtual void Setup() override;`
- L48 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L50 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L51 _public function_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override`
- L52 _public function_ `virtual bool HasCancel() const override`
- L53 _public function_ `virtual bool HasAccept() const override`
- L54 _public prototype_ `virtual bool CanAccept() const override;`
- L58 _public prototype_ `virtual TUniquePtr<UE::Geometry::TGenericDataOperator<UE::Geometry::FMeshMapBaker>> MakeNewOperator() override;`
- L64 _public function_ `virtual void SetTarget(const TObjectPtr<UUVEditorToolMeshInput>& TargetIn)` — The tool will operate on the mesh given here. Supports only one mesh.
- L73 _private member_ `TObjectPtr<UUVEditorToolMeshInput> Target;` — `UPROPERTY()` — Mesh input to UV Editor
- L79 _private member_ `TObjectPtr<UUVEditorBakeUVShellProperties> UVShellSettings;` — `UPROPERTY()` — Property set for bake and result
- L85 _private member_ `TObjectPtr<UPreviewGeometry> PreviewGeoBackgroundQuad;` — `UPROPERTY()` — Preview Geometry for display in Unwrapped viewport
- L90 _private member_ `TUniquePtr<TGenericDataBackgroundCompute<UE::Geometry::FMeshMapBaker>> Compute = nullptr;` — Background compute
- L93 _private member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> DetailMesh;` — used in the bake
- L94 _private member_ `TSharedPtr<UE::Geometry::FDynamicMeshAABBTree3, ESPMode::ThreadSafe> DetailSpatial;`
- L101 _private prototype_ `void OnMapUpdated(const TUniquePtr<UE::Geometry::FMeshMapBaker>& NewResult);` — Retrieves the result of the FMeshMapBaker and generated UTexture2D into the CachedUVMap @param NewResult the resulting FMeshMapBaker from the background compute
- L108 _private prototype_ `void UpdateVisualization();` — Updates the preview material on the preview quad with the computed results. Invoked by OnMapsUpdated. Also sets the result to what is currently in CachedUVMap
- L114 _private member_ `TObjectPtr<UTexture2D> CachedUVMap = nullptr;` — `UPROPERTY()` — Internal cache of bake uv texture result
- L119 _private prototype_ `void SetUpPreviewQuad();` — Uses Preview Geometry to draw a preview of the bake in the unwrap viewport
- L124 _private prototype_ `UMaterialInstanceDynamic* GetMaterialForQuad();` — Retrieves the Material for the preview quad, or the preview result
- L130 _private prototype_ `void CreateTextureAsset(const TObjectPtr<UTexture2D>& Texture) const;` — Create texture asset from our result Texture2D @param Texture the result texture to create
- L135 _private prototype_ `static void InitializeUVLayerNames(TArray<FString>& UVLayerNamesList, const int16 NumUVLayers);` — Initialize the list of all UV Layer names

#### class `UUVEditorBakeUVShellProperties`  
`class UUVEditorBakeUVShellProperties : public UInteractiveToolPropertySet`  
_L139-187_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolPropertySet`
- L145 _public member_ `FString UVLayer;` — `UPROPERTY(meta = (DisplayName = "UV Layer", GetOptions = GetTargetUVLayerNamesFunc, NoResetToDefault))` — The source mesh UV Layer to sample.
- L149 _public member_ `float WireframeThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "UV Snapshot Output", meta = (UIMin = "0.0", UIMax = "10.0", ClampMin = "0.0"))` — The thickness of the wireframe in pixels.
- L153 _public member_ `FLinearColor WireframeColor = FLinearColor::Blue;` — `UPROPERTY(EditAnywhere, Category = "UV Snapshot Output")` — The color of wireframe pixels.
- L157 _public member_ `FLinearColor ShellColor = FLinearColor::Gray;` — `UPROPERTY(EditAnywhere, Category = "UV Snapshot Output")` — The color of the UV shell interior pixels.
- L161 _public member_ `FLinearColor BackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);` — `UPROPERTY(EditAnywhere, Category = "UV Snapshot Output")` — The color of pixels external to UV shells.
- L165 _public member_ `EBakeTextureResolution Resolution = EBakeTextureResolution::Resolution256;` — `UPROPERTY(EditAnywhere, Category = Textures)` — The pixel resolution of the generated textures
- L169 _public member_ `EBakeTextureSamplesPerPixel SamplesPerPixel = EBakeTextureSamplesPerPixel::Sample4;` — `UPROPERTY(EditAnywhere, Category = Textures)` — Number of samples per pixel
- L173 _public member_ `FString SavedPath = FString();` — `UPROPERTY()` — Saved path where last UVSnapshot was saved to. Empty if this is first save out
- L177 _public member_ `TObjectPtr<UTexture2D> Result;` — `UPROPERTY(VisibleAnywhere, Category = Results, meta = (DisplayName = "Result Texture", TransientToolProperty))` — Bake
- L180 _public function_ `const TArray<FString>& GetTargetUVLayerNamesFunc() const` — `UFUNCTION()`
- L186 _public member_ `TArray<FString> TargetUVLayerNamesList;` — `UPROPERTY(meta = (TransientToolProperty))`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVEditorUXSettings.h` (Public)


#### class `FUVEditorUXSettings`  
`class FUVEditorUXSettings`  
_L10-195_
- L20 _public member_ `static const float UVMeshScalingFactor;` — The ScaleFactor just scales the mesh up. Scaling the mesh up makes it easier to zoom in further into the display before getting issues with the camera near plane distance.
- L23 _public member_ `static const float CameraFarPlaneWorldZ;` — Position to place the 2D camera far plane relative to world z
- L28 _public member_ `static const float CameraNearPlaneProportionZ;` — The near plane gets positioned some proportion to z = 0. We don't use a constant value because our depth offset values are percentage-based Lower proportion move the plane nearer to world z Note: This serves as an upper bound for all other depth offsets - higher than this value risks being clipped
- L32 _public member_ `static const float UnwrapTriangleOpacity;` — 2D Unwrap Display Properties
- L33 _public member_ `static const float UnwrapTriangleDepthOffset;`
- L34 _public member_ `static const float UnwrapTriangleOpacityWithBackground;`
- L36 _public member_ `static const float WireframeDepthOffset;`
- L37 _public member_ `static const float UnwrapBoundaryHueShift;`
- L38 _public member_ `static const float UnwrapBoundarySaturation;`
- L39 _public member_ `static const float UnwrapBoundaryValue;`
- L40 _public member_ `static const FColor UnwrapTriangleFillColor;`
- L41 _public member_ `static const FColor UnwrapTriangleWireframeColor;`
- L43 _public prototype_ `static FLinearColor GetTriangleColorByTargetIndex(int32 TargetIndex);`
- L44 _public prototype_ `static FLinearColor GetWireframeColorByTargetIndex(int32 TargetIndex);`
- L45 _public prototype_ `static FLinearColor GetBoundaryColorByTargetIndex(int32 TargetIndex);`
- L49 _public prototype_ `static FColor MakeCividisColorFromScalar(float Scalar);` — Provides a color blindness friendly ramp for visualizing metrics and other data Domain is [0 , 1]
- L53 _public prototype_ `static FColor MakeTurboColorFromScalar(float Scalar);` — Provides a color blindness friendly ramp for visualizing diverging metrics and other data Domain is [-0.5, 0.5]
- L56 _public member_ `static const float WireframeThickness;` — Wireframe Properties
- L57 _public member_ `static const float BoundaryEdgeThickness;`
- L60 _public member_ `static const float SelectionTriangleOpacity;` — Selection Highlighting Properties
- L61 _public member_ `static const FColor SelectionTriangleFillColor;`
- L62 _public member_ `static const FColor SelectionTriangleWireframeColor;`
- L64 _public member_ `static const float SelectionHoverTriangleOpacity;`
- L65 _public member_ `static const FColor SelectionHoverTriangleFillColor;`
- L66 _public member_ `static const FColor SelectionHoverTriangleWireframeColor;`
- L68 _public member_ `static const float LivePreviewHighlightThickness;`
- L69 _public member_ `static const float LivePreviewHighlightPointSize;`
- L70 _public member_ `static const float LivePreviewHighlightDepthOffset;`
- L72 _public member_ `static const float SelectionLineThickness;`
- L73 _public member_ `static const float SelectionPointThickness;`
- L74 _public member_ `static const float SelectionWireframeDepthBias;`
- L75 _public member_ `static const float SelectionTriangleDepthBias;`
- L76 _public member_ `static const float SelectionHoverWireframeDepthBias;`
- L77 _public member_ `static const float SelectionHoverTriangleDepthBias;`
- L79 _public member_ `static const FColor LivePreviewExistingSeamColor;`
- L80 _public member_ `static const float LivePreviewExistingSeamThickness;`
- L81 _public member_ `static const float LivePreviewExistingSeamDepthBias;`
- L85 _public member_ `static const FColor ToolLockedCutPathColor;` — These are currently used by the seam tool but can be generally used by tools for displaying paths.
- L86 _public member_ `static const FColor ToolLockedJoinPathColor;`
- L87 _public member_ `static const float ToolLockedPathThickness;`
- L88 _public member_ `static const float ToolLockedPathDepthBias;`
- L89 _public member_ `static const FColor ToolExtendCutPathColor;`
- L90 _public member_ `static const FColor ToolExtendJoinPathColor;`
- L91 _public member_ `static const float ToolExtendPathThickness;`
- L92 _public member_ `static const float ToolExtendPathDepthBias;`
- L93 _public member_ `static const FColor ToolCompletionPathColor;`
- L95 _public member_ `static const float ToolPointSize;`
- L98 _public member_ `static const float SewLineHighlightThickness;` — Sew Action styling
- L99 _public member_ `static const float SewLineDepthOffset;`
- L100 _public member_ `static const FColor SewSideLeftColor;`
- L101 _public member_ `static const FColor SewSideRightColor;`
- L104 _public member_ `static const float AxisThickness;` — Grid
- L105 _public member_ `static const float GridMajorThickness;`
- L106 _public member_ `static const FColor XAxisColor;`
- L107 _public member_ `static const FColor YAxisColor;`
- L108 _public member_ `static const FColor RulerXColor;`
- L109 _public member_ `static const FColor RulerYColor;`
- L110 _public member_ `static const FColor GridMajorColor;`
- L111 _public member_ `static const FColor GridMinorColor;`
- L112 _public member_ `static const int32 GridSubdivisionsPerLevel;`
- L113 _public member_ `static const int32 GridLevels;`
- L114 _public member_ `static const int32 RulerSubdivisionLevel;`
- L117 _public member_ `static const int32 PivotCircleNumSides;` — Pivots
- L118 _public member_ `static const float PivotCircleRadius;`
- L119 _public member_ `static const float PivotLineThickness;`
- L120 _public member_ `static const FColor PivotLineColor;`
- L123 _public member_ `static const float BackgroundQuadDepthOffset;` — Background
- L141 _public prototype_ `static FVector3d ExternalUVToUnwrapWorldPosition(const FVector2f& UV);` — Converts from UV value as displayed to user or seen before import, to point in unwrap world space. This is useful for mapping visualizations to world unwrap space. Like other world-UV conversion functions, clients should not know about the details of this conversion.
- L150 _public prototype_ `static FVector2f UnwrapWorldPositionToExternalUV(const FVector3d& VertPosition);` — Converts from point in unwrap world space, to UV value as displayed to user or seen before import. This is useful for labeling UV values in the unwrap world, even though the UV values are stored slightly differently inside the mesh itself. Like other world-UV conversion functions, clients should not know about the details of this conversion.
- L155 _public prototype_ `static FVector2f ExternalUVToInternalUV(const FVector2f& UV);` — Converts from UV value as displayed to user or seen before import, to UV as stored on a mesh in Unreal.
- L160 _public prototype_ `static FVector2f InternalUVToExternalUV(const FVector2f& UV);` — Converts from UV as stored on a mesh in Unreal to UV as displayed to user or seen in an external program.
- L168 _public prototype_ `static FVector3d UVToVertPosition(const FVector2f& UV);` — Convert from UV as stored on a mesh in Unreal to world position in the UV editor unwrap world. This allows changes in UVs of a mesh to be mapped to its unwrap representation. Like other world-UV conversion functions, clients should not know about the details of this conversion.
- L176 _public prototype_ `static FVector2f VertPositionToUV(const FVector3d& VertPosition);` — Converts from position in UV editor unwrap world to UV value as stored on a mesh in Unreal. This allows changes in the unwrap world to be mapped to actual mesh UVs. Like other world-UV conversion functions, clients should not know about the details of this conversion.
- L183 _public member_ `static TAutoConsoleVariable<int32> CVarEnablePrototypeUDIMSupport;`
- L188 _public prototype_ `static float LocationSnapValue(int32 LocationSnapMenuIndex);`
- L189 _public prototype_ `static int32 MaxLocationSnapValue();`
- L193 _private prototype_ `FUVEditorUXSettings();`
- L194 _private prototype_ `~FUVEditorUXSettings();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API UVEDITORTOOLS_API`

### `Plugins/Editor/UVEditor/Source/UVEditorTools/Public/UVSelectTool.h` (Public)


#### class `UUVSelectToolBuilder`  
`class UUVSelectToolBuilder : public UInteractiveToolBuilder`  
_L26-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveToolBuilder`
- L31 _public prototype_ `virtual bool CanBuildTool(const FToolBuilderState& SceneState) const override;`
- L32 _public prototype_ `virtual UInteractiveTool* BuildTool(const FToolBuilderState& SceneState) const override;`
- L36 _public member_ `const TArray<TObjectPtr<UUVEditorToolMeshInput>>* Targets = nullptr;` — This is a pointer so that it can be updated under the builder without having to set it in the mode after initializing targets.

#### class `UUVSelectTool`  
`class UUVSelectTool : public UInteractiveTool, public IInteractiveToolNestedAcceptCancelAPI, public IUVToolSupportsSelection`  
_L45-124_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveTool,IInteractiveToolNestedAcceptCancelAPI,IUVToolSupportsSelection`
- desc: The tool in the UV editor that secretly runs when other tools are not running. It uses the selection api to allow the user to select elements, and has a gizmo that can be used to transform these elements.
- L54 _public function_ `virtual void SetTargets(const TArray<TObjectPtr<UUVEditorToolMeshInput>>& TargetsIn)` — The tool will operate on the meshes given here.
- L59 _public prototype_ `void SelectAll();`
- L62 _public prototype_ `FTransform GetGizmoTransform() const;` — Used by undo/redo.
- L63 _public prototype_ `void SetGizmoTransform(const FTransform& NewTransform);`
- L66 _public prototype_ `virtual void Setup() override;` — UInteractiveTool
- L67 _public prototype_ `virtual void Shutdown(EToolShutdownType ShutdownType) override;`
- L68 _public prototype_ `virtual void OnPropertyModified(UObject* PropertySet, FProperty* Property) override;`
- L69 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L70 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L71 _public prototype_ `virtual void OnTick(float DeltaTime) override;`
- L72 _public function_ `virtual bool HasCancel() const override`
- L73 _public function_ `virtual bool HasAccept() const override`
- L76 _public function_ `virtual bool SupportsNestedCancelCommand() override` — IInteractiveToolNestedAcceptCancelAPI
- L77 _public prototype_ `virtual bool CanCurrentlyNestedCancel() override;`
- L78 _public prototype_ `virtual bool ExecuteNestedCancelCommand() override;`
- L81 _protected prototype_ `virtual void OnSelectionChanged(bool bEmitChangeAllowed, uint32 SelectionChangeType);`
- L84 _protected prototype_ `virtual void GizmoTransformChanged(UTransformProxy* Proxy, FTransform Transform);` — Callbacks we'll receive from the gizmo proxy
- L85 _protected prototype_ `virtual void GizmoTransformStarted(UTransformProxy* Proxy);`
- L86 _protected prototype_ `virtual void GizmoTransformEnded(UTransformProxy* Proxy);`
- L88 _protected prototype_ `virtual void ApplyGizmoTransform();`
- L89 _protected prototype_ `virtual void UpdateGizmo(bool bForceRecomputeSelectionCenters = false);`
- L92 _protected member_ `TArray<TObjectPtr<UUVEditorToolMeshInput>> Targets;` — `UPROPERTY()`
- L95 _protected member_ `TObjectPtr<UUVToolViewportButtonsAPI> ViewportButtonsAPI = nullptr;` — `UPROPERTY()`
- L98 _protected member_ `TObjectPtr<UUVToolEmitChangeAPI> EmitChangeAPI = nullptr;` — `UPROPERTY()`
- L101 _protected member_ `TObjectPtr<UUVToolSelectionAPI> SelectionAPI = nullptr;` — `UPROPERTY()`
- L104 _protected member_ `TObjectPtr<UUVEditorMeshSelectionMechanic> SelectionMechanic = nullptr;` — `UPROPERTY()`
- L107 _protected member_ `TObjectPtr<UCombinedTransformGizmo> TransformGizmo = nullptr;` — `UPROPERTY()`
- L109 _protected member_ `UE::Geometry::FFrame3d InitialGizmoFrame;`
- L110 _protected member_ `FTransform UnappliedGizmoTransform;`
- L111 _protected member_ `bool bInDrag = false;`
- L112 _protected member_ `bool bUpdateGizmoOnCanonicalChange = true;`
- L113 _protected member_ `bool bGizmoTransformNeedsApplication = false;`
- L115 _protected member_ `TArray<UE::Geometry::FUVToolSelection> CurrentSelections;`
- L117 _protected member_ `TArray<TArray<int32>> RenderUpdateTidsPerSelection;` — The outer arrays are 1:1 with the Selections array obtained from the Selection API
- L119 _protected member_ `TArray<TArray<int32>> MovingVidsPerSelection;` — Inner arrays for these two are 1:1 with each other
- L120 _protected member_ `TArray<TArray<FVector3d>> MovingVertOriginalPositionsPerSelection;`
- L123 _private prototype_ `void ReinitializeFromSelection(bool bForceRecomputeSelectionCenters);`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API UVEDITORTOOLS_API`
