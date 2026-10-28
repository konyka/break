# Plugins / GeometryMode

- module root: `Plugins/Editor/GeometryMode/Source/GeometryMode`
- headers: 20; symbols: 356
- symbol kinds: class=25, delegate=1, function=48, macro=1, member=64, prototype=203, struct=6, typedef=8
- DynamicallyLoadedModuleNames: PropertyEditor
- PrivateDependencyModuleNames: BSPUtils, Core, CoreUObject, EditorFramework, EditorSubsystem, Engine, InputCore, LevelEditor, NavigationSystem, Projects, RenderCore, Slate, SlateCore, UnrealEd

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier.h` (Public)


#### class `UGeomModifier`  
`class UGeomModifier : public UObject`  
_L24-175_
- reflection: `UCLASS(abstract, hidecategories=(Object, GeomModifier))`
- inherits: `UObject`
- L30 _private member_ `FText Description;` — `UPROPERTY(EditAnywhere, Category=GeomModifier)` — A human readable name for this modifier (appears on buttons, menus, etc)
- L34 _private member_ `FText Tooltip;` — `UPROPERTY(EditAnywhere, Category = GeomModifier)` — The tooltip to be displayed for this modifier
- L38 _private member_ `FName ToolbarIconName;` — `UPROPERTY()` — Icon name for showing this modifier in a toolbar
- L42 _private member_ `uint32 bPushButton:1;` — `UPROPERTY(EditAnywhere, Category=GeomModifier)` — If true, this modifier should be displayed as a push button instead of a radio button
- L49 _private member_ `uint32 bInitialized:1;` — `UPROPERTY(EditAnywhere, Category=GeomModifier)` — true if the modifier has been initialized. This is useful for interpreting user input and mouse drags correctly.
- L53 _private member_ `uint32 bPendingPivotOffsetUpdate:1;` — `UPROPERTY()` — If true, the pivot offset should be updated when the modification ends
- L56 _private member_ `uint32 bAppearsInToolbar : 1;` — `UPROPERTY()`
- L60 _private member_ `TObjectPtr<class UPolys> CachedPolys;` — `UPROPERTY()` — Stored state of polys in case the brush state needs to be restroed
- L65 _public prototype_ `const FText& GetModifierDescription() const;` — @return		The modifier's description string.
- L68 _public prototype_ `const FText& GetModifierTooltip() const;` — @return		The modifier's tooltip string.
- L71 _public prototype_ `virtual bool InputKey(class FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event);` — @return		true if the key was handled by this editor mode tool.
- L74 _public prototype_ `virtual bool InputDelta(class FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale);` — @return		true if the delta was handled by this editor mode tool.
- L79 _public prototype_ `virtual void Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI);` — Drawing functions to allow modifiers to have better control over the screen.
- L80 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient,FViewport* Viewport,const FSceneView* View,FCanvas* Canvas);`
- L87 _public prototype_ `bool Apply();` — Applies the modifier.  Does nothing if the editor is not in geometry mode. @return		true if something happened.
- L90 _public function_ `virtual bool Supports()` — `UE_DEPRECATED(4.25, "Supports has been deprected. Use SupportsCurrentSelection instead")`
- L95 _public function_ `virtual bool SupportsCurrentSelection()` — @return		true if this modifier will work on the currently selected sub objects.
- L98 _public prototype_ `virtual void Initialize();` — Gives the individual modifiers a chance to do something the first time they are activated.
- L103 _public prototype_ `bool StartModify();` — Starts the modification of geometry data.
- L108 _public prototype_ `bool EndModify();` — Ends the modification of geometry data.
- L113 _public prototype_ `void StartTrans();` — Handles the starting of transactions against the selected ABrushes.
- L118 _public prototype_ `void EndTrans();` — Handles the stopping of transactions against the selected ABrushes.
- L123 _public prototype_ `void StoreCurrentGeomSelections( TArray<struct FGeomSelection>& SelectionArray, FGeomObjectPtr go );` — Store the current geom selections (Edge, Vert and Poly)
- L128 _public prototype_ `void StoreAllCurrentGeomSelections();` — Store the current geom selections for all geom objects
- L130 _public function_ `virtual void Tick(FEditorViewportClient* ViewportClient,float DeltaTime)`
- L135 _public function_ `virtual void WasActivated()` — Gives the modifier a chance to initialize it's internal state when activated.
- L140 _public function_ `virtual void WasDeactivated()` — Gives the modifier a chance to clean up when the user is switching away from it.
- L146 _public prototype_ `void CacheBrushState();` — Stores the current state of the brush so that upon faulty operations, the brush may be restored to its previous state
- L151 _public prototype_ `void RestoreBrushState();` — Restores the brush to its cached state
- L156 _public prototype_ `bool DoEdgesOverlap();` — @return		true if two edges in the shape overlap not at a vertex
- L164 _protected prototype_ `void GeomError(const FString& InErrorMsg);` — Interface for displaying error messages. @param	InErrorMsg		The error message to display.
- L169 _protected prototype_ `virtual bool OnApply();` — Implements the modifier application.
- L174 _protected prototype_ `virtual void UpdatePivotOffset();` — Updates the pivot offset of the selected brushes based on the current vertex positions

#### Free symbols / members of external scopes

- L21 _typedef_ `typedef TSharedPtr<class FGeomObject> FGeomObjectPtr;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Clip.h` (Public)


#### class `UGeomModifier_Clip`  
`class UGeomModifier_Clip : public UGeomModifier_Edit`  
_L20-53_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L25 _private member_ `uint32 bFlipNormal:1;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L28 _private member_ `uint32 bSplit:1;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L32 _private member_ `TArray<FVector> ClipMarkers;` — `UPROPERTY()` — The clip markers that the user has dropped down in the world so far.
- L36 _private member_ `FVector SnappedMouseWorldSpacePos;` — `UPROPERTY()` — The mouse position, in world space, where the user currently is hovering.
- L40 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L41 _private prototype_ `virtual bool InputKey(class FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L42 _private prototype_ `virtual void Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI) override;`
- L43 _private prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient,FViewport* Viewport,const FSceneView* View,FCanvas* Canvas) override;`
- L44 _private prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient,float DeltaTime) override;`
- L45 _private prototype_ `virtual void WasActivated() override;`
- L47 _protected prototype_ `virtual bool OnApply() override;`
- L52 _private prototype_ `void ApplyClip( bool InSplit, bool InFlipNormal );` — @todo document

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Create.h` (Public)


#### class `UGeomModifier_Create`  
`class UGeomModifier_Create : public UGeomModifier_Edit`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L20 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L22 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Delete.h` (Public)


#### class `UGeomModifier_Delete`  
`class UGeomModifier_Delete : public UGeomModifier_Edit`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L20 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L22 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Edit.h` (Public)


#### class `UGeomModifier_Edit`  
`class UGeomModifier_Edit : public UGeomModifier`  
_L21-30_
- reflection: `UCLASS(autoexpandcategories=Settings)`
- inherits: `UGeomModifier`
- L25 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L28 _private prototype_ `virtual bool InputDelta(class FEditorViewportClient* InViewportClient,FViewport* InViewport,FVector& InDrag,FRotator& InRot,FVector& InScale) override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Extrude.h` (Public)


#### class `UGeomModifier_Extrude`  
`class UGeomModifier_Extrude : public UGeomModifier_Edit`  
_L16-45_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L21 _private member_ `int32 Length;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L24 _private member_ `int32 Segments;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L27 _private member_ `int32 SaveCoordSystem;` — `UPROPERTY()`
- L31 _private prototype_ `virtual bool InputDelta(class FEditorViewportClient* InViewportClient, FViewport* InViewport, FVector& InDrag, FRotator& InRot, FVector& InScale) override;`
- L32 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L33 _private prototype_ `virtual void Initialize() override;`
- L34 _private prototype_ `virtual void WasActivated() override;`
- L35 _private prototype_ `virtual void WasDeactivated() override;`
- L38 _private prototype_ `void CheckCoordinatesMode();` — Check the coordinates mode is local and warn the user with a suppressible dialog if it is not
- L41 _protected prototype_ `virtual bool OnApply() override;`
- L44 _private prototype_ `void Apply(int32 InLength, int32 InSegments);`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Flip.h` (Public)


#### class `UGeomModifier_Flip`  
`class UGeomModifier_Flip : public UGeomModifier_Edit`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L20 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L22 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Lathe.h` (Public)


#### class `UGeomModifier_Lathe`  
`class UGeomModifier_Lathe : public UGeomModifier_Edit`  
_L14-40_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L19 _private member_ `int32 TotalSegments;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L22 _private member_ `int32 Segments;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L25 _private member_ `uint32 AlignToSide:1;` — `UPROPERTY(EditAnywhere, Category=Settings)`
- L29 _private member_ `TEnumAsByte<EAxis::Type> Axis;` — `UPROPERTY()` — The axis of rotation to use when creating the brush.  This is automatically determined from the current ortho viewport.
- L33 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L34 _private prototype_ `virtual void Initialize() override;`
- L36 _protected prototype_ `virtual bool OnApply() override;`
- L39 _private prototype_ `void Apply( int32 InTotalSegments, int32 InSegments, EAxis::Type InAxis );`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Optimize.h` (Public)


#### class `UGeomModifier_Optimize`  
`class UGeomModifier_Optimize : public UGeomModifier_Triangulate`  
_L14-23_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Triangulate`
- L21 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Pen.h` (Public)


#### class `UGeomModifier_Pen`  
`class UGeomModifier_Pen : public UGeomModifier_Edit`  
_L20-63_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L26 _private member_ `uint32 bAutoExtrude:1;` — `UPROPERTY(EditAnywhere, Category=Settings)` — If true, the shape will be automatically extruded into a brush upon completion.
- L30 _private member_ `uint32 bCreateConvexPolygons:1;` — `UPROPERTY(EditAnywhere, Category=Settings)` — If true, the tool will try and optimize the resulting triangles into convex polygons before creating the brush.
- L34 _private member_ `uint32 bCreateBrushShape:1;` — `UPROPERTY(EditAnywhere, Category=Settings)` — If true, the resulting shape will be turned into an ABrushShape actor.
- L38 _private member_ `int32 ExtrudeDepth;` — `UPROPERTY(EditAnywhere, Category=Settings)` — How far to extrude the newly created brush if bAutoExtrude is set to true.
- L42 _private member_ `TArray<FVector> ShapeVertices;` — `UPROPERTY()` — The vertices that the user has dropped down in the world so far.
- L46 _private member_ `FVector MouseWorldSpacePos;` — `UPROPERTY(transient)` — The mouse position, in world space, where the user currently is hovering (snapped to grid if that setting is enabled).
- L49 _private member_ `FEditorViewportClient* UsingViewportClient;`
- L52 _private prototype_ `virtual bool InputKey(class FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L53 _private prototype_ `virtual void Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI) override;`
- L54 _private prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient,FViewport* Viewport,const FSceneView* View,FCanvas* Canvas) override;`
- L55 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L56 _private prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient,float DeltaTime) override;`
- L57 _private prototype_ `virtual void WasActivated() override;`
- L59 _protected prototype_ `virtual bool OnApply() override;`
- L62 _private prototype_ `void Apply();`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Split.h` (Public)


#### class `UGeomModifier_Split`  
`class UGeomModifier_Split : public UGeomModifier_Edit`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L20 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L22 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Triangulate.h` (Public)


#### class `UGeomModifier_Triangulate`  
`class UGeomModifier_Triangulate : public UGeomModifier_Edit`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L20 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L22 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Turn.h` (Public)


#### class `UGeomModifier_Turn`  
`class UGeomModifier_Turn : public UGeomModifier_Edit`  
_L14-24_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L20 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L22 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Classes/GeomModifier_Weld.h` (Public)


#### class `UGeomModifier_Weld`  
`class UGeomModifier_Weld : public UGeomModifier_Edit`  
_L13-23_
- reflection: `UCLASS()`
- inherits: `UGeomModifier_Edit`
- L19 _private prototype_ `virtual bool SupportsCurrentSelection() override;`
- L21 _protected prototype_ `virtual bool OnApply() override;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Private/BrushEditingSubsystemImpl.h` (Private)


#### class `UBrushEditingSubsystemImpl`  
`class UBrushEditingSubsystemImpl : public UBrushEditingSubsystem`  
_L16-41_
- reflection: `UCLASS()`
- inherits: `UBrushEditingSubsystem`
- L21 _public prototype_ `UBrushEditingSubsystemImpl();`
- L23 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L25 _public prototype_ `virtual bool ProcessClickOnBrushGeometry(FEditorViewportClient* ViewportClient, HHitProxy* InHitProxy, const FViewportClick& Click) override;`
- L27 _public prototype_ `virtual void UpdateGeometryFromSelectedBrushes() override;`
- L28 _public prototype_ `virtual void UpdateGeometryFromBrush(ABrush* Brush) override;`
- L30 _public prototype_ `virtual bool IsGeometryEditorModeActive() const override;`
- L32 _public prototype_ `virtual void DeselectAllEditingGeometry() override;`
- L34 _public prototype_ `virtual bool HandleActorDelete() override;`
- L37 _private prototype_ `bool ProcessClickOnGeomPoly(FEditorViewportClient* ViewportClient, HGeomPolyProxy* GeomHitProxy, const FViewportClick& Click);`
- L38 _private prototype_ `bool ProcessClickOnGeomEdge(FEditorViewportClient* ViewportClient, HGeomEdgeProxy* GeomHitProxy, const FViewportClick& Click);`
- L39 _private prototype_ `bool ProcessClickOnGeomVertex(FEditorViewportClient* ViewportClient, HGeomVertexProxy* GeomHitProxy, const FViewportClick& Click);`

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogBrushEditing, Log, All);`
- L9 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogBrushEditing, Log, All);`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Private/GeometryMode.h` (Private)


#### class `FGeometryModeToolkit`  
`class FGeometryModeToolkit : public FModeToolkit`  
_L22-70_
- inherits: `FModeToolkit`
- desc: Mode Toolkit for the Geometry Tools
- L29 _public prototype_ `virtual void Init(const TSharedPtr< class IToolkitHost >& InitToolkitHost) override;` — Initializes the geometry mode toolkit
- L32 _public prototype_ `virtual FName GetToolkitFName() const override;` — IToolkit interface
- L33 _public prototype_ `virtual FText GetBaseToolkitName() const override;`
- L34 _public prototype_ `virtual class FEdMode* GetEditorMode() const override;`
- L35 _public prototype_ `virtual TSharedPtr<class SWidget> GetInlineContent() const override;`
- L37 _public prototype_ `virtual void GetToolPaletteNames(TArray<FName>& PaletteNames) const override;`
- L38 _public prototype_ `virtual FText GetToolPaletteDisplayName(FName Palette) const override;`
- L39 _public prototype_ `virtual void BuildToolPalette(FName Palette, class FToolBarBuilder& ToolbarBuilder) override;`
- L42 _public prototype_ `virtual FText GetActiveToolDisplayName() const;` — Modes Panel Header Information
- L43 _public prototype_ `virtual FText GetActiveToolMessage() const;`
- L46 _public prototype_ `void OnGeometrySelectionChanged();` — Method called when the selection
- L49 _public prototype_ `class FModeTool_GeometryModify* GetGeometryModeTool() const;` — Returns a reference to the geometry mode tool
- L53 _private prototype_ `void OnModifierStateChanged(ECheckBoxState NewCheckedState, UGeomModifier* Modifier);` — Called when a new modifier mode is selected
- L55 _private prototype_ `void OnModifierToolBarButtonClicked(UGeomModifier* Modifier);`
- L58 _private prototype_ `ECheckBoxState IsModifierChecked(UGeomModifier* Modifier) const;` — Returns the state of a modifier radio button
- L61 _private prototype_ `bool IsModifierEnabled(UGeomModifier* Modifier) const;` — Returns the enabled state of a modifier button
- L63 _private prototype_ `FReply OnApplyClicked();`
- L65 _private prototype_ `void OnModifierClicked(UGeomModifier* Modifier);`
- L69 _private member_ `TSharedPtr<class SGeometryModeControls> GeomWidget;` — Geometry tools widget

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Private/GeometryModeStyle.h` (Private)


#### class `FGeometryModeStyle`  
`class FGeometryModeStyle`  
_L7-22_
- L10 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L14 _public prototype_ `static TSharedPtr< class ISlateStyle > Get();`
- L16 _public prototype_ `static FName GetStyleSetName();`
- L18 _private prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L21 _private member_ `static TSharedPtr< class FSlateStyleSet > StyleSet;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Public/EditorGeometry.h` (Public)


#### class `FGeomBase`  
`class FGeomBase`  
_L20-82_
- desc: Base class for all classes that support storing and editing of geometry.
- L23 _public prototype_ `FGeomBase();`
- L24 _public prototype_ `virtual ~FGeomBase() = default;`
- L27 _public prototype_ `virtual void Select( bool InSelect = 1 );` — Does nothing if not in geometry mode.
- L29 _public function_ `bool IsSelected() const`
- L30 _public function_ `int32 GetSelectionIndex() const`
- L36 _public function_ `void ForceSelectionIndex( int32 InSelectionIndex )` — Allows manual setting of the selection index.  This is dangerous and should only be called by the FEdModeGeometry::PostUndo() function.
- L39 _public prototype_ `virtual FVector GetMidPoint() const = 0;` — Returns a location that represents the middle of the object
- L42 _public function_ `virtual FVector GetWidgetLocation()` — Returns a valid position for the widget to be drawn at for this object
- L45 _public function_ `virtual FRotator GetWidgetRotation() const` — Gets the local rotation to use when transforming this object
- L48 _public prototype_ `FGeomObjectPtr GetParentObject();` — @{
- L49 _public prototype_ `const FGeomObjectPtr GetParentObject() const;`
- L53 _public function_ `virtual bool IsVertex() const` — Returns true if this geometry objects is a vertex.
- L56 _public function_ `const FVector& GetNormal() const` — @{
- L57 _public function_ `const FVector& GetMid() const`
- L59 _public function_ `int32 GetParentObjectIndex() const`
- L63 _public function_ `void SetNormal(const FVector& InNormal)` — @{
- L64 _public function_ `void SetMid(const FVector& InMid)`
- L66 _public function_ `void SetParentObjectIndex(int32 InParentObjectIndex)`
- L71 _protected member_ `int32 ParentObjectIndex;` — Allows polys, edges and vertices to point to the FGeomObject that owns them.
- L74 _protected member_ `FVector Normal;` — The normal vector for this object.
- L77 _protected member_ `FVector Mid;` — The mid point for this object.
- L81 _private member_ `int32 SelectionIndex;` — If > INDEX_NONE, this object is selected

#### struct `FPolyVertexIndex`  
`struct FPolyVertexIndex`  
_L89-113_
- desc: An index pair denoting a polygon and vertex within the parent objects ABrush.
- L91 _public function_ `FPolyVertexIndex()`
- L95 _public function_ `FPolyVertexIndex( int32 InPolyIndex, int32 InVertexIndex )`
- L101 _public member_ `int32 PolyIndex, VertexIndex;`
- L101 _public member_ `int32 PolyIndex, VertexIndex;`
- L103 _public function_ `bool operator==( const FPolyVertexIndex& In ) const`

#### class `FGeomVertex`  
`class FGeomVertex : public FGeomBase, public FVector3f`  
_L120-151_
- inherits: `FGeomBase,FVector3f`
- desc: A 3D position.
- L123 _public prototype_ `FGeomVertex();`
- L125 _public prototype_ `virtual FVector GetWidgetLocation();`
- L127 _public prototype_ `virtual FRotator GetWidgetRotation() const;`
- L129 _public prototype_ `virtual FVector GetMidPoint() const;`
- L131 _public function_ `virtual bool IsVertex() const`
- L134 _public member_ `TArray<FPolyVertexIndex> ActualVertexIndices;` — The list of vertices that this vertex represents.
- L135 _public prototype_ `FVector3f* GetActualVertex( FPolyVertexIndex& InPVI );`
- L141 _public member_ `TArray<int32> ParentPolyIndices;` — Indices into the parent poly pool. A vertex can belong to more than one poly and this keeps track of that relationship.
- L144 _public function_ `FGeomVertex& operator=( const FVector3f& In )` — Assignment simply copies off the vertex position.

#### class `FGeomEdge`  
`class FGeomEdge : public FGeomBase`  
_L158-178_
- inherits: `FGeomBase`
- desc: The space between 2 adjacent vertices.
- L161 _public prototype_ `FGeomEdge();`
- L163 _public prototype_ `virtual FVector GetWidgetLocation();`
- L165 _public prototype_ `virtual FVector GetMidPoint() const;`
- L168 _public prototype_ `bool IsSameEdge( const FGeomEdge& InEdge ) const;` — Returns true if InEdge matches this edge, independant of winding.
- L174 _public member_ `TArray<int32> ParentPolyIndices;` — Indices into the parent poly pool. An edge can belong to more than one poly and this keeps track of that relationship.
- L177 _public member_ `int32 VertexIndices[2];` — Indices into the parent vertex pool.

#### class `FGeomPoly`  
`class FGeomPoly : public FGeomBase`  
_L185-223_
- inherits: `FGeomBase`
- desc: An individual polygon.
- L188 _public prototype_ `FGeomPoly();`
- L190 _public prototype_ `virtual FVector GetWidgetLocation();`
- L192 _public prototype_ `virtual FVector GetMidPoint() const;`
- L198 _public member_ `int32 ActualPolyIndex;` — The polygon this poly represents.  This is an index into the polygon array inside the ABrush that is selected in this objects parent FGeomObject.
- L199 _public prototype_ `FPoly* GetActualPoly();`
- L202 _public member_ `TArray<int> EdgeIndices;` — Array of indices into the parent objects edge pool.
- L204 _public function_ `bool operator==( const FGeomPoly& In ) const`

#### class `FGeomObject`  
`class FGeomObject : public FGeomBase, public FGCObject`  
_L230-325_
- inherits: `FGeomBase,FGCObject`
- desc: A group of polygons forming an individual object.
- L233 _public prototype_ `FGeomObject();`
- L235 _public prototype_ `virtual FVector GetMidPoint() const override;`
- L238 _public member_ `TObjectPtr<ABrush> ActualBrush;` — Index to the ABrush actor this object represents.
- L239 _public function_ `ABrush* GetActualBrush()`
- L240 _public function_ `const ABrush* GetActualBrush() const`
- L251 _public member_ `TArray<FGeomBase*> SelectionOrder;` — Used for tracking the order of selections within this object.  This is required for certain modifiers to work correctly. This list is generated on the fly whenever the array is accessed but is marked as dirty (see bSelectionOrderDirty). NOTE: do not serialize
- L259 _public function_ `void DirtySelectionOrder()` — Dirties the selection order.
- L265 _public member_ `bool bSelectionOrderDirty;` — If 1, the selection order array needs to be compiled before being accessed. NOTE: do not serialize
- L268 _public prototype_ `void CompileSelectionOrder();`
- L271 _public member_ `TArray<FGeomVertex> VertexPool;` — Main lists.  All lower data types refer to the contents of these pools through indices.
- L272 _public member_ `TArray<FGeomEdge> EdgePool;`
- L273 _public member_ `TArray<FGeomPoly> PolyPool;`
- L283 _public prototype_ `void CompileUniqueEdgeArray( TArray<FGeomEdge>* InEdges );` — Compiles a list of unique edges.  This runs through the edge pool and only adds edges into the pool that aren't already there (the difference being that this routine counts edges that share the same vertices, but are wound backwards to each other, as being equal). @param	InEdges		The edge array to fill up.
- L286 _public prototype_ `void ComputeData();` — Tells the object to recompute all of it's internal data.
- L289 _public prototype_ `void ClearData();` — Erases all current data for this object.
- L291 _public prototype_ `virtual FVector GetWidgetLocation() override;`
- L292 _public prototype_ `int32 AddVertexToPool( int32 InObjectIndex, int32 InParentPolyIndex, int32 InPolyIndex, int32 InVertexIndex );`
- L293 _public prototype_ `int32 AddEdgeToPool( FGeomPoly* InPoly, int32 InParentPolyIndex, int32 InVectorIdxA, int32 InVectorIdxB );`
- L294 _public prototype_ `virtual void GetFromSource();`
- L295 _public prototype_ `virtual void SendToSource();`
- L296 _public prototype_ `bool FinalizeSourceData();`
- L297 _public prototype_ `int32 GetObjectIndex();`
- L299 _public prototype_ `void SelectNone();`
- L300 _public prototype_ `int32 GetNewSelectionIndex();`
- L306 _public function_ `void ForceLastSelectionIndex( int32 InLastSelectionIndex )` — Allows manual setting of the last selection index.  This is dangerous and should only be called by the FEdModeGeometry::PostUndo() function.
- L308 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;`
- L309 _public prototype_ `virtual FString GetReferencerName() const override;`
- L316 _public prototype_ `int32 SetPivotFromSelectionArray( TArray<struct FGeomSelection>& SelectionArray );` — Set the pivot position based on the 'highest' selected object (vertex/edge/poly) in the given selection array @param SelectionArray - The array of selections @return The index of the array entry used for setting the pivot. Returns INDEX_NONE if pivot not set
- L321 _public prototype_ `void UpdateFromSelectionArray( TArray<struct FGeomSelection>& SelectionArray );` — Update the selection state based on the passed in array
- L324 _private member_ `int32 LastSelectionIndex;`

#### struct `HGeomPolyProxy`  
`struct HGeomPolyProxy : public HHitProxy`  
_L337-369_
- inherits: `HHitProxy`
- desc: Hit proxy for polygons.
- L339 _public prototype_ `DECLARE_HIT_PROXY();`
- L341 _public member_ `TWeakPtr<FGeomObject> GeomObjectWeakPtr;`
- L342 _public member_ `int32 PolyIndex;`
- L344 _public function_ `HGeomPolyProxy(FGeomObjectPtr InGeomObject, int32 InPolyIndex): HHitProxy(HPP_UI), GeomObjectWeakPtr(InGeomObject), PolyIndex(InPolyIndex)`
- L350 _public function_ `FGeomObject* GetGeomObject()`
- L352 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L365 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override` — Method that specifies whether the hit proxy *always* allows translucent primitives to be associated with it or not, regardless of any other engine/editor setting. For example, if translucent selection was disabled, any hit proxies returning true would still allow translucent selection. In this specific case, true is always returned because geometry mode hit proxies always need to be selectable or geometry mode will not function correctly. @return	true if translucent primitives are always allowed with this hit proxy; false otherwise

#### struct `HGeomEdgeProxy`  
`struct HGeomEdgeProxy : public HHitProxy`  
_L374-407_
- inherits: `HHitProxy`
- desc: Hit proxy for edges.
- L376 _public prototype_ `DECLARE_HIT_PROXY();`
- L379 _public member_ `TWeakPtr<FGeomObject> GeomObjectWeakPtr;` — Kept around for backwards compat
- L380 _public member_ `int32 EdgeIndex;`
- L382 _public function_ `HGeomEdgeProxy(FGeomObjectPtr InGeomObject, int32 InEdgeIndex): HHitProxy(HPP_UI), GeomObjectWeakPtr(InGeomObject), EdgeIndex(InEdgeIndex)`
- L388 _public function_ `FGeomObject* GetGeomObject()`
- L390 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L403 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override` — Method that specifies whether the hit proxy *always* allows translucent primitives to be associated with it or not, regardless of any other engine/editor setting. For example, if translucent selection was disabled, any hit proxies returning true would still allow translucent selection. In this specific case, true is always returned because geometry mode hit proxies always need to be selectable or geometry mode will not function correctly. @return	true if translucent primitives are always allowed with this hit proxy; false otherwise

#### struct `HGeomVertexProxy`  
`struct HGeomVertexProxy : public HHitProxy`  
_L414-446_
- inherits: `HHitProxy`
- desc: Hit proxy for vertices.
- L416 _public prototype_ `DECLARE_HIT_PROXY();`
- L418 _public member_ `TWeakPtr<FGeomObject> GeomObjectWeakPtr;`
- L419 _public member_ `int32 VertexIndex;`
- L421 _public function_ `HGeomVertexProxy(FGeomObjectPtr InGeomObject, int32 InVertexIndex): HHitProxy(HPP_UI), GeomObjectWeakPtr(InGeomObject), VertexIndex(InVertexIndex)`
- L427 _public function_ `FGeomObject* GetGeomObject()`
- L429 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L442 _public function_ `virtual bool AlwaysAllowsTranslucentPrimitives() const override` — Method that specifies whether the hit proxy *always* allows translucent primitives to be associated with it or not, regardless of any other engine/editor setting. For example, if translucent selection was disabled, any hit proxies returning true would still allow translucent selection. In this specific case, true is always returned because geometry mode hit proxies always need to be selectable or geometry mode will not function correctly. @return	true if translucent primitives are always allowed with this hit proxy; false otherwise

#### Free symbols / members of external scopes

- L14 _typedef_ `typedef TSharedPtr<class FGeomObject> FGeomObjectPtr;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Public/GeometryEdMode.h` (Public)


#### class `FEdModeGeometry`  
`class FEdModeGeometry : public FEdMode`  
_L33-202_
- inherits: `FEdMode`
- desc: Allows for BSP geometry to be edited directly
- L37 _public prototype_ `FEdModeGeometry();`
- L53 _public prototype_ `static TSharedRef< FEdModeGeometry > Create();`
- L54 _public prototype_ `virtual ~FEdModeGeometry();`
- L57 _public prototype_ `virtual void Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI) override;` — FEdMode interface
- L58 _public prototype_ `virtual bool ShowModeWidgets() const override;`
- L59 _public prototype_ `virtual bool UsesToolkits() const override;`
- L60 _public prototype_ `virtual bool ShouldDrawBrushWireframe( AActor* InActor ) const override;`
- L61 _public prototype_ `virtual bool GetCustomDrawingCoordinateSystem( FMatrix& InMatrix, void* InData ) override;`
- L62 _public prototype_ `virtual bool GetCustomInputCoordinateSystem( FMatrix& InMatrix, void* InData ) override;`
- L63 _public prototype_ `virtual void Enter() override;`
- L64 _public prototype_ `virtual void Exit() override;`
- L65 _public prototype_ `virtual void ActorSelectionChangeNotify() override;`
- L66 _public prototype_ `virtual void MapChangeNotify() override;`
- L67 _public prototype_ `virtual void SelectionChanged() override;`
- L68 _public prototype_ `virtual FVector GetWidgetLocation() const override;`
- L69 _public prototype_ `virtual bool IsCompatibleWith(FEditorModeID OtherModeID) const override;`
- L70 _public prototype_ `virtual bool ComputeBoundingBoxForViewportFocus(AActor* Actor, UPrimitiveComponent* PrimitiveComponent, FBox& InOutBox) const override;`
- L74 _public prototype_ `virtual void AddReferencedObjects( FReferenceCollector& Collector ) override;` — FGCObject interface
- L77 _public prototype_ `virtual void GeometrySelectNone(bool bStoreSelection, bool bResetPivot);`
- L82 _public prototype_ `virtual int32 CountObjectsSelected();` — Returns the number of objects that are selected.
- L87 _public prototype_ `virtual int32 CountSelectedPolygons();` — Returns the number of polygons that are selected.
- L94 _public prototype_ `virtual void GetSelectedPolygons( TArray<FGeomPoly*>& InPolygons ) const;` — Returns the polygons that are selected. @param	InPolygons	An array to fill with the selected polygons.
- L99 _public prototype_ `virtual bool HavePolygonsSelected();` — Returns true if the user has polygons selected.
- L104 _public prototype_ `virtual int32 CountSelectedEdges();` — Returns the number of edges that are selected.
- L111 _public prototype_ `virtual void GetSelectedEdges( TArray<FGeomEdge*>& InEdges ) const;` — Returns the edges that are selected. @param	InEdges	An array to fill with the selected edges.
- L116 _public prototype_ `virtual bool HaveEdgesSelected();` — Returns true if the user has edges selected.
- L121 _public prototype_ `virtual int32 CountSelectedVertices();` — Returns the number of vertices that are selected.
- L126 _public prototype_ `virtual bool HaveVerticesSelected();` — Returns true if the user has vertices selected.
- L131 _public prototype_ `virtual void GetSelectedVertices( TArray<FGeomVertex*>& InVerts ) const;` — Fills an array with all selected vertices.
- L138 _public prototype_ `virtual int32 GetSelectionState();` — Utility function that allow you to poll and see if certain sub elements are currently selected. Returns a combination of the flags in EGeomSelectionStatus.
- L145 _public prototype_ `bool CacheSelectedData( TArray<HGeomMidPoints>& raGeomData, const FGeomObject& rGeomObject ) const;` — Cache all the selected geometry on the object, and add to the array if any is found Return true if new object has been added to the array.
- L152 _public prototype_ `bool FindFromCache( TArray<HGeomMidPoints>& raGeomData, FGeomObject& rGeomObject, TArray<FGeomBase*>& raSelectedGeom ) const;` — Attempt to find all the new geometry using the cached data, and cache those new ones out Return true everything was found (or there was nothing to find)
- L159 _public prototype_ `bool SelectCachedData( TArray<FGeomBase*>& raSelectedGeom ) const;` — Select all the verts/edges/polys that were found Return true if successful
- L164 _public prototype_ `virtual void GetFromSource();` — Compiles geometry mode information from the selected brushes.
- L169 _public prototype_ `virtual void SendToSource();` — Changes the source brushes to match the current geometry data.
- L170 _public prototype_ `virtual bool FinalizeSourceData();`
- L171 _public prototype_ `virtual void PostUndo() override;`
- L172 _public prototype_ `virtual bool ExecDelete();`
- L173 _public prototype_ `virtual void UpdateInternalData() override;`
- L175 _public prototype_ `void RenderPoly( const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI );`
- L176 _public prototype_ `void RenderEdge( const FSceneView* View, FPrimitiveDrawInterface* PDI );`
- L177 _public prototype_ `void RenderVertex( const FSceneView* View, FPrimitiveDrawInterface* PDI );`
- L179 _public prototype_ `void ShowModifierWindow(bool bShouldShow);`
- L183 _public typedef_ `typedef TArray<FGeomObjectPtr>::TIterator TGeomObjectIterator;` — @{
- L184 _public typedef_ `typedef TArray<FGeomObjectPtr>::TConstIterator TGeomObjectConstIterator;`
- L186 _public function_ `TGeomObjectIterator GeomObjectItor()`
- L187 _public function_ `TGeomObjectConstIterator GeomObjectConstItor() const`
- L190 _public function_ `FGeomObjectPtr GetGeomObject(int32 Index)` — @todo DB: Get rid of these; requires changes to FGeomBase::ParentObjectIndex
- L191 _public function_ `const FGeomObjectPtr GetGeomObject(int32 Index) const`
- L201 _protected member_ `TArray<FGeomObjectPtr> GeomObjects;` — Custom data compiled when this mode is entered, based on currently selected brushes.  This data is what is drawn and what the LD interacts with while in this mode.  Changes done here are reflected back to the real data in the level at specific times.

#### struct `FEdModeGeometry::HGeomMidPoints`  
`struct HGeomMidPoints`  
_L42-51_
- desc: Struct for cacheing of selected objects components midpoints for reselection when rebuilding the BSP
- L45 _public member_ `ABrush* ActualBrush;` — The actor that the verts/edges/polys belong to
- L48 _public member_ `TArray<FVector> VertexPool;` — Arrays of the midpoints of all the selected verts/edges/polys
- L49 _public member_ `TArray<FVector> EdgePool;`
- L50 _public member_ `TArray<FVector> PolyPool;`

#### class `FModeTool_GeometryModify`  
`class FModeTool_GeometryModify : public FModeTool`  
_L211-273_
- inherits: `FModeTool`
- desc: Widget manipulation of geometry.
- L214 _public prototype_ `FModeTool_GeometryModify();`
- L216 _public function_ `virtual FString GetName() const override`
- L218 _public prototype_ `void SetCurrentModifier( UGeomModifier* InModifier );`
- L219 _public prototype_ `UGeomModifier* GetCurrentModifier() const;`
- L221 _public prototype_ `int32 GetNumModifiers() const;`
- L226 _public prototype_ `virtual bool InputDelta(FEditorViewportClient* InViewportClient,FViewport* InViewport,FVector& InDrag,FRotator& InRot,FVector& InScale) override;` — @return		true if the delta was handled by this editor mode tool.
- L228 _public prototype_ `virtual bool StartModify() override;`
- L229 _public prototype_ `virtual bool EndModify() override;`
- L231 _public prototype_ `virtual void StartTrans() override;`
- L232 _public prototype_ `virtual void EndTrans() override;`
- L234 _public prototype_ `virtual void SelectNone() override;`
- L235 _public prototype_ `virtual bool BoxSelect( FBox& InBox, bool InSelect = true ) override;`
- L236 _public prototype_ `virtual bool FrustumSelect( const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, bool InSelect = true ) override;`
- L240 _public typedef_ `typedef TArray<TObjectPtr<UGeomModifier>>::TIterator TModifierIterator;` — @{
- L241 _public typedef_ `typedef TArray<TObjectPtr<UGeomModifier>>::TConstIterator TModifierConstIterator;`
- L243 _public function_ `TModifierIterator ModifierIterator()`
- L244 _public function_ `TModifierConstIterator ModifierConstIterator() const`
- L247 _public function_ `UGeomModifier* GetModifier(int32 Index)` — @todo DB: Get rid of these; requires changes to EditorGeometry.cpp
- L248 _public function_ `const UGeomModifier* GetModifier(int32 Index) const`
- L251 _public prototype_ `virtual void Tick(FEditorViewportClient* ViewportClient,float DeltaTime) override;`
- L254 _public prototype_ `virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;` — @return		true if the key was handled by this editor mode tool.
- L256 _public prototype_ `virtual void Render(const FSceneView* View,FViewport* Viewport,FPrimitiveDrawInterface* PDI) override;`
- L257 _public prototype_ `virtual void DrawHUD(FEditorViewportClient* ViewportClient,FViewport* Viewport,const FSceneView* View,FCanvas* Canvas) override;`
- L262 _public prototype_ `void StoreAllCurrentGeomSelections();` — Store the current geom selections for all geom objects
- L265 _public member_ `bool bGeomModified;` — Used to track when actualy modification takes place
- L269 _protected member_ `TArray<TObjectPtr<UGeomModifier>> Modifiers;` — All available modifiers.
- L272 _protected member_ `UGeomModifier* CurrentModifier;` — The current modifier.

#### Free symbols / members of external scopes

- L27 _typedef_ `typedef TSharedPtr<class FGeomObject> FGeomObjectPtr;`

### `Plugins/Editor/GeometryMode/Source/GeometryMode/Public/GeometryModeModule.h` (Public)


#### struct `FGeometryEditingModes`  
`struct FGeometryEditingModes`  
_L13-18_
- L15 _public member_ `static FEditorModeID EM_Geometry;`
- L16 _public member_ `static FEditorModeID EM_Bsp;`
- L17 _public member_ `static FEditorModeID EM_TextureAlign;`

#### class `FGeometryModeModule`  
`class FGeometryModeModule : public IModuleInterface`  
_L22-29_
- inherits: `IModuleInterface`
- desc: Geometry mode module
- L26 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface
- L27 _public prototype_ `virtual void ShutdownModule() override;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GEOMETRYMODE_API`
- L11 _typedef_ `typedef FName FEditorModeID;`
