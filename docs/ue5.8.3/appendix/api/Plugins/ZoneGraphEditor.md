# Plugins / ZoneGraphEditor

- module root: `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor`
- headers: 14; symbols: 295
- symbol kinds: class=14, enum=1, enumerator=3, function=31, macro=2, member=87, namespace=3, prototype=147, struct=7
- PrivateDependencyModuleNames: AIGraph, AppFramework, GraphEditor, KismetWidgets, Projects, PropertyEditor, RenderCore, ToolMenus
- PublicDependencyModuleNames: AssetTools, ComponentVisualizers, Core, CoreUObject, DetailCustomizations, EditorFramework, Engine, InputCore, LevelEditor, PropertyEditor, Slate, SlateCore, UnrealEd, ZoneGraph

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneGraphEditorStyle.h` (Private)


#### class `FZoneGraphEditorStyle`  
`class FZoneGraphEditorStyle`  
_L7-25_
- L11 _public prototype_ `static void Initialize();`
- L12 _public prototype_ `static void Shutdown();`
- L13 _public function_ `static TSharedPtr<ISlateStyle> Get()`
- L14 _public prototype_ `static FName GetStyleSetName();`
- L16 _public function_ `static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL)`
- L21 _public prototype_ `static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);`
- L24 _private member_ `static TSharedPtr<FSlateStyleSet> StyleSet;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneGraphPropertyUtils.h` (Private)


#### Free symbols / members of external scopes

- L12 _macro_ `#define LOCTEXT_NAMESPACE "ZoneGraphEditor"`
- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ZoneGraph` (scope `UE`)
- L14 _namespace_ `namespace PropertyUtils` (scope `UE::ZoneGraph`)
- L19 _function_ `template<typename T> TOptional<T> GetValue(const TSharedPtr<IPropertyHandle>& ValueProperty)` (scope `UE::ZoneGraph::PropertyUtils`) — Expects T is struct.
- L64 _function_ `template<typename T> void SetValue(TSharedPtr<IPropertyHandle>& ValueProperty, T NewValue, EPropertyValueSetFlags::Type Flags = 0)` (scope `UE::ZoneGraph::PropertyUtils`) — Expects T is struct.
- L116 _prototype_ `FLinearColor GetMaskColor(TSharedPtr<IPropertyHandle> MaskProperty);` (scope `UE::ZoneGraph::PropertyUtils`)
- L117 _prototype_ `FText GetMaskDescription(TSharedPtr<IPropertyHandle> MaskProperty);` (scope `UE::ZoneGraph::PropertyUtils`)

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneGraphTagDetails.h` (Private)


#### class `FZoneGraphTagDetails`  
`class FZoneGraphTagDetails : public IPropertyTypeCustomization`  
_L14-41_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneGraphTag.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _private prototype_ `FLinearColor GetColor() const;`
- L27 _private prototype_ `FText GetDescription() const;`
- L28 _private prototype_ `TSharedRef<SWidget> OnGetComboContent() const;`
- L30 _private prototype_ `void OnEditTags();`
- L31 _private prototype_ `void OnSetBit(uint8 Bit);`
- L33 _private prototype_ `void CacheTagInfos();`
- L35 _private member_ `TArray<FZoneGraphTagInfo> TagInfos;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> BitProperty;`
- L39 _private member_ `class IPropertyUtilities* PropUtils;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneGraphTagFilterDetails.h` (Private)


#### class `FZoneGraphTagFilterDetails`  
`class FZoneGraphTagFilterDetails : public IPropertyTypeCustomization`  
_L14-47_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneGraphTagFilter.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _private prototype_ `FLinearColor GetAnyTagsColor() const;`
- L27 _private prototype_ `FText GetAnyTagsDescription() const;`
- L28 _private prototype_ `EVisibility IsAnyTagsVisible() const;`
- L30 _private prototype_ `FLinearColor GetAllTagsColor() const;`
- L31 _private prototype_ `FText GetAllTagsDescription() const;`
- L32 _private prototype_ `EVisibility IsAllTagsVisible() const;`
- L34 _private prototype_ `FLinearColor GetNotTagsColor() const;`
- L35 _private prototype_ `FText GetNotTagsDescription() const;`
- L36 _private prototype_ `EVisibility IsNotTagsVisible() const;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> AnyTagsProperty;`
- L39 _private member_ `TSharedPtr<IPropertyHandle> AllTagsProperty;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> NotTagsProperty;`
- L41 _private member_ `TSharedPtr<IPropertyHandle> AnyTagsMaskProperty;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> AllTagsMaskProperty;`
- L43 _private member_ `TSharedPtr<IPropertyHandle> NotTagsMaskProperty;`
- L45 _private member_ `class IPropertyUtilities* PropUtils;`
- L46 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneGraphTagInfoDetails.h` (Private)


#### class `FZoneGraphTagInfoDetails`  
`class FZoneGraphTagInfoDetails : public IPropertyTypeCustomization`  
_L17-45_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneGraphTagInfo.
- L21 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L24 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L25 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L29 _private prototype_ `FLinearColor GetColor() const;`
- L30 _private prototype_ `FText GetTagDescription() const;`
- L32 _private prototype_ `FReply OnColorPressed(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L33 _private prototype_ `void SetColor(FLinearColor NewColor);`
- L34 _private prototype_ `void OnColorPickerCancelled(FLinearColor OriginalColor);`
- L36 _private member_ `TSharedPtr<IPropertyHandle> TagProperty;`
- L37 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> ColorProperty;`
- L39 _private member_ `TSharedPtr<SColorBlock> ColorWidget;`
- L41 _private member_ `class IPropertyUtilities* PropUtils;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`
- L44 _private member_ `TArray<FZoneGraphTagInfo> Infos;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneGraphTagMaskDetails.h` (Private)


#### class `FZoneGraphTagMaskDetails`  
`class FZoneGraphTagMaskDetails : public IPropertyTypeCustomization`  
_L14-39_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneGraphTagMask.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _private prototype_ `FLinearColor GetColor() const;`
- L27 _private prototype_ `FText GetDescription() const;`
- L28 _private prototype_ `TSharedRef<SWidget> OnGetComboContent() const;`
- L30 _private prototype_ `void OnEditTags();`
- L31 _private prototype_ `void OnToggleBit(uint32 BitMask);`
- L32 _private prototype_ `void OnSetMask(FZoneGraphTagMask Mask);`
- L33 _private prototype_ `bool OnIsBitSet(uint32 BitMask) const;`
- L35 _private member_ `TSharedPtr<IPropertyHandle> MaskProperty;`
- L37 _private member_ `class IPropertyUtilities* PropUtils;`
- L38 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneGraphTessellationSettingsDetails.h` (Private)


#### class `FZoneGraphTessellationSettingsDetails`  
`class FZoneGraphTessellationSettingsDetails : public IPropertyTypeCustomization`  
_L14-51_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneGraphTessellationSettings.
- L18 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L21 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L22 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L26 _private prototype_ `FLinearColor GetAnyTagsColor() const;`
- L27 _private prototype_ `FText GetAnyTagsDescription() const;`
- L28 _private prototype_ `EVisibility IsAnyTagsVisible() const;`
- L30 _private prototype_ `FLinearColor GetAllTagsColor() const;`
- L31 _private prototype_ `FText GetAllTagsDescription() const;`
- L32 _private prototype_ `EVisibility IsAllTagsVisible() const;`
- L34 _private prototype_ `FLinearColor GetNotTagsColor() const;`
- L35 _private prototype_ `FText GetNotTagsDescription() const;`
- L36 _private prototype_ `EVisibility IsNotTagsVisible() const;`
- L38 _private prototype_ `FText GetToleranceDescription() const;`
- L40 _private member_ `TSharedPtr<IPropertyHandle> AnyTagsProperty;`
- L41 _private member_ `TSharedPtr<IPropertyHandle> AllTagsProperty;`
- L42 _private member_ `TSharedPtr<IPropertyHandle> NotTagsProperty;`
- L43 _private member_ `TSharedPtr<IPropertyHandle> AnyTagsMaskProperty;`
- L44 _private member_ `TSharedPtr<IPropertyHandle> AllTagsMaskProperty;`
- L45 _private member_ `TSharedPtr<IPropertyHandle> NotTagsMaskProperty;`
- L47 _private member_ `TSharedPtr<IPropertyHandle> ToleranceProperty;`
- L49 _private member_ `class IPropertyUtilities* PropUtils;`
- L50 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneLaneDescDetails.h` (Private)


#### class `FZoneLaneDescDetails`  
`class FZoneLaneDescDetails : public IPropertyTypeCustomization`  
_L12-34_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneLaneDesc.
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _private prototype_ `FLinearColor GetTagColor() const;`
- L25 _private prototype_ `FText GetTagDescription() const;`
- L26 _private prototype_ `FText GetDescription() const;`
- L28 _private member_ `TSharedPtr<IPropertyHandle> WidthProperty;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> DirectionProperty;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> TagsProperty;`
- L32 _private member_ `class IPropertyUtilities* PropUtils;`
- L33 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneLaneProfileDetails.h` (Private)


#### class `FZoneLaneProfileDetails`  
`class FZoneLaneProfileDetails : public IPropertyTypeCustomization`  
_L12-31_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneLaneProfile.
- L16 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L19 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L20 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L24 _private prototype_ `FText GetDescription() const;`
- L26 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;`
- L27 _private member_ `TSharedPtr<IPropertyHandle> LanesProperty;`
- L29 _private member_ `class IPropertyUtilities* PropUtils;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneLaneProfileRefDetails.h` (Private)


#### class `FZoneLaneProfileRefDetails`  
`class FZoneLaneProfileRefDetails : public IPropertyTypeCustomization`  
_L13-35_
- inherits: `IPropertyTypeCustomization`
- desc: Type customization for FZoneLaneProfileRef.
- L17 _public prototype_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L20 _public prototype_ `virtual void CustomizeHeader(TSharedRef<IPropertyHandle> StructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;` — IPropertyTypeCustomization interface
- L21 _public prototype_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> StructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils& StructCustomizationUtils) override;`
- L25 _private prototype_ `void OnProfileComboChange(int32 Idx);`
- L26 _private prototype_ `TSharedRef<SWidget> OnGetProfileContent() const;`
- L27 _private prototype_ `FText GetCurrentProfileDesc() const;`
- L29 _private member_ `TSharedPtr<IPropertyHandle> NameProperty;`
- L30 _private member_ `TSharedPtr<IPropertyHandle> IDProperty;`
- L31 _private member_ `TSharedPtr<IPropertyHandle> LanesProperty;`
- L33 _private member_ `class IPropertyUtilities* PropUtils;`
- L34 _private member_ `TSharedPtr<IPropertyHandle> StructProperty;`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneShapeComponentDetails.h` (Private)


#### class `FZoneShapeComponentDetails`  
`class FZoneShapeComponentDetails : public IDetailCustomization`  
_L10-18_
- inherits: `IDetailCustomization`
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();` — Makes a new instance of this detail layout class for a specific detail view requesting it
- L17 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;` — IDetailCustomization interface

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Private/ZoneShapeComponentVisualizer.h` (Private)


#### enum `FZoneShapeControlPointType`  
`enum class FZoneShapeControlPointType : uint8`  
_L28-33_
- reflection: `UENUM()`
- L30 _public enumerator_ `None`
- L31 _public enumerator_ `In`
- L32 _public enumerator_ `Out`

#### class `UZoneShapeComponentVisualizerSelectionState`  
`class UZoneShapeComponentVisualizerSelectionState : public UObject`  
_L37-83_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: Selection state data that will be captured by scoped transactions.
- L41 _public function_ `FComponentPropertyPath GetShapePropertyPath() const`
- L42 _public function_ `void SetShapePropertyPath(const FComponentPropertyPath& InShapePropertyPath)`
- L43 _public function_ `const TSet<int32>& GetSelectedPoints() const`
- L44 _public function_ `TSet<int32>& ModifySelectedPoints()`
- L45 _public function_ `int32 GetLastPointIndexSelected() const`
- L46 _public function_ `void SetLastPointIndexSelected(const int32 InLastPointIndexSelected)`
- L47 _public function_ `int32 GetSelectedSegmentIndex() const`
- L48 _public function_ `void SetSelectedSegmentIndex(const int32 InSelectedSegmentIndex)`
- L49 _public function_ `FVector GetSelectedSegmentPoint() const`
- L50 _public function_ `void SetSelectedSegmentPoint(const FVector& InSelectedSegmentPoint)`
- L51 _public function_ `float GetSelectedSegmentT() const`
- L52 _public function_ `void SetSelectedSegmentT(const float InSelectedSegmentT)`
- L53 _public function_ `int32 GetSelectedControlPoint() const`
- L54 _public function_ `void SetSelectedControlPoint(const int32 InSelectedControlPoint)`
- L55 _public function_ `FZoneShapeControlPointType GetSelectedControlPointType() const`
- L56 _public function_ `void SetSelectedControlPointType(const FZoneShapeControlPointType InSelectedControlPointType)`
- L61 _protected member_ `FComponentPropertyPath ShapePropertyPath;` — `UPROPERTY()` — Property path from the parent actor to the component
- L64 _protected member_ `TSet<int32> SelectedPoints;` — `UPROPERTY()` — Index of keys we have selected
- L67 _protected member_ `int32 LastPointIndexSelected = 0;` — `UPROPERTY()` — Index of the last key we selected
- L70 _protected member_ `int32 SelectedSegmentIndex = 0;` — `UPROPERTY()` — Index of segment we have selected
- L73 _protected member_ `FVector SelectedSegmentPoint = FVector::ZeroVector;` — `UPROPERTY()` — Position on selected segment
- L76 _protected member_ `float SelectedSegmentT = 0.0f;` — `UPROPERTY()` — Interpolation value along the selected segment
- L79 _protected member_ `int32 SelectedControlPoint = 0;` — `UPROPERTY()` — Index of tangent handle we have selected
- L82 _protected member_ `FZoneShapeControlPointType SelectedControlPointType = FZoneShapeControlPointType::None;` — `UPROPERTY()` — The type of the selected tangent handle

#### struct `HZoneShapeVisProxy`  
`struct HZoneShapeVisProxy : public HComponentVisProxy`  
_L86-98_
- inherits: `HComponentVisProxy`
- desc: Base class for clickable shape editing proxies
- L88 _public prototype_ `DECLARE_HIT_PROXY( );`
- L90 _public function_ `HZoneShapeVisProxy(const UActorComponent* InComponent, EHitProxyPriority InPriority = HPP_Wireframe) : HComponentVisProxy(InComponent, InPriority)`
- L94 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`

#### struct `HZoneShapePointProxy`  
`struct HZoneShapePointProxy : public HZoneShapeVisProxy`  
_L101-116_
- inherits: `HZoneShapeVisProxy`
- desc: Proxy for a shape point
- L103 _public prototype_ `DECLARE_HIT_PROXY( );`
- L105 _public function_ `HZoneShapePointProxy(const UActorComponent* InComponent, int32 InPointIndex) : HZoneShapeVisProxy(InComponent, HPP_Foreground) , PointIndex(InPointIndex)`
- L110 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L115 _public member_ `int32 PointIndex;`

#### struct `HZoneShapeSegmentProxy`  
`struct HZoneShapeSegmentProxy : public HZoneShapeVisProxy`  
_L119-134_
- inherits: `HZoneShapeVisProxy`
- desc: Proxy for a shape segment
- L121 _public prototype_ `DECLARE_HIT_PROXY( );`
- L123 _public function_ `HZoneShapeSegmentProxy(const UActorComponent* InComponent, int32 InSegmentIndex) : HZoneShapeVisProxy(InComponent) , SegmentIndex(InSegmentIndex)`
- L128 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L133 _public member_ `int32 SegmentIndex;`

#### struct `HZoneShapeControlPointProxy`  
`struct HZoneShapeControlPointProxy : public HZoneShapeVisProxy`  
_L137-154_
- inherits: `HZoneShapeVisProxy`
- desc: Proxy for a control point handle
- L139 _public prototype_ `DECLARE_HIT_PROXY( );`
- L141 _public function_ `HZoneShapeControlPointProxy(const UActorComponent* InComponent, int32 InPointIndex, bool bInInControlPoint) : HZoneShapeVisProxy(InComponent, HPP_Foreground) , PointIndex(InPointIndex) , bInControlPoint(bInInControlPoint)`
- L147 _public function_ `virtual EMouseCursor::Type GetMouseCursor() override`
- L152 _public member_ `int32 PointIndex;`
- L153 _public member_ `bool bInControlPoint;`

#### class `FZoneShapeComponentVisualizer`  
`class FZoneShapeComponentVisualizer : public FComponentVisualizer, public FGCObject`  
_L157-359_
- inherits: `FComponentVisualizer,FGCObject`
- desc: ZoneShapeComponent visualizer/edit functionality
- L160 _public prototype_ `FZoneShapeComponentVisualizer();`
- L161 _public prototype_ `virtual ~FZoneShapeComponentVisualizer();`
- L164 _public prototype_ `virtual void OnRegister() override;`
- L165 _public prototype_ `virtual void DrawVisualization(const UActorComponent* Component, const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L166 _public prototype_ `virtual bool VisProxyHandleClick(FEditorViewportClient* InViewportClient, HComponentVisProxy* VisProxy, const FViewportClick& Click) override;`
- L167 _public prototype_ `virtual void DrawVisualizationHUD(const UActorComponent* Component, const FViewport* Viewport, const FSceneView* View, FCanvas* Canvas) override;`
- L168 _public prototype_ `virtual void EndEditing() override;`
- L169 _public prototype_ `virtual bool GetWidgetLocation(const FEditorViewportClient* ViewportClient, FVector& OutLocation) const override;`
- L170 _public prototype_ `virtual bool GetCustomInputCoordinateSystem(const FEditorViewportClient* ViewportClient, FMatrix& OutMatrix) const override;`
- L171 _public prototype_ `virtual bool HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport, FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale) override;`
- L172 _public prototype_ `virtual bool HandleInputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event) override;`
- L174 _public prototype_ `virtual bool HandleBoxSelect(const FBox& InBox, FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — Handle box select input
- L176 _public prototype_ `virtual bool HandleFrustumSelect(const FConvexVolume& InFrustum, FEditorViewportClient* InViewportClient, FViewport* InViewport) override;` — Handle frustum select input
- L178 _public prototype_ `virtual bool HasFocusOnSelectionBoundingBox(FBox& OutBoundingBox) override;` — Return whether focus on selection should focus on bounding box defined by active visualizer
- L180 _public prototype_ `virtual bool HandleSnapTo(const bool bInAlign, const bool bInUseLineTrace, const bool bInUseBounds, const bool bInUsePivot, AActor* InDestination) override;` — Pass snap input to active visualizer
- L182 _public prototype_ `virtual UActorComponent* GetEditedComponent() const override;` — Get currently edited component, this is needed to reset the active visualizer after undo/redo
- L183 _public prototype_ `virtual TSharedPtr<SWidget> GenerateContextMenu() const override;`
- L184 _public prototype_ `virtual bool IsVisualizingArchetype() const override;`
- L188 _public prototype_ `UZoneShapeComponent* GetEditedShapeComponent() const;` — Get the shape component we are currently editing
- L190 _public function_ `const TSet<int32>& GetSelectedPoints() const`
- L219 _protected prototype_ `bool IsAnySelectedPointIndexOutOfRange(const UZoneShapeComponent& Comp) const;` — Determine if any selected key index is out of range (perhaps because something external has modified the shape)
- L222 _protected prototype_ `bool IsSinglePointSelected() const;` — Whether a single point is currently selected
- L225 _protected prototype_ `bool TransformSelectedControlPoint(const FVector& DeltaTranslate);` — Transforms selected control point by given translation
- L228 _protected prototype_ `bool TransformSelectedPoints(const FEditorViewportClient* ViewportClient, const FVector& DeltaTranslate, const FRotator& DeltaRotate, const FVector& DeltaScale) const;` — Transforms selected points by given delta translation, rotation and scale.
- L231 _protected prototype_ `void ChangeSelectionState(int32 Index, bool bIsCtrlHeld) const;` — Update the key selection state of the visualizer
- L234 _protected prototype_ `bool DuplicatePointForAltDrag(const FVector& InDrag) const;` — Alt-drag: duplicates the selected point
- L237 _protected prototype_ `void SplitSegment(const int32 InSegmentIndex, const float SegmentSplitT, UZoneShapeComponent* ShapeComp = nullptr) const;` — Split segment using given interpolation value, selects the new point
- L240 _protected prototype_ `void AddSegment(const FVector& InWorldPos, const int32 InSelectedIndex, UZoneShapeComponent* InShapeComp = nullptr) const;` — Add segment using given position and index, selects the new point
- L243 _protected prototype_ `void DuplicateSelectedPoints(const FVector& WorldOffset = FVector::ZeroVector, bool bInsertAfter = true) const;` — Duplicates selected points and selects them.
- L246 _protected prototype_ `const UZoneShapeComponent* UpdateSelectedShapeComponent(const HComponentVisProxy* VisProxy);` — Updates the component and selected properties if the component has changed
- L249 _protected prototype_ `bool GetLastSelectedPointRotation(FQuat& OutRotation) const;` — Returns the rotation of last selected point, or false if last selection is not valid.
- L251 _protected prototype_ `void OnDeletePoint() const;`
- L252 _protected prototype_ `bool CanDeletePoint() const;`
- L255 _protected prototype_ `void OnDuplicatePoint() const;` — Duplicates selected points in place
- L256 _protected prototype_ `bool IsPointSelectionValid() const;`
- L258 _protected prototype_ `void OnAddPointToSegment() const;`
- L259 _protected prototype_ `bool CanAddPointToSegment() const;`
- L261 _protected prototype_ `void OnSetPointType(FZoneShapePointType Type) const;`
- L262 _protected prototype_ `bool IsPointTypeSet(FZoneShapePointType Type) const;`
- L264 _protected prototype_ `void OnSelectAllPoints() const;`
- L265 _protected prototype_ `bool CanSelectAllPoints() const;`
- L267 _protected prototype_ `void OnBreakAtPointNewActors() const;`
- L268 _protected prototype_ `void OnBreakAtPointNewComponents() const;`
- L269 _protected prototype_ `bool CanBreakAtPoint() const;`
- L271 _protected prototype_ `void OnBreakAtSegmentNewActors() const;`
- L272 _protected prototype_ `void OnBreakAtSegmentNewComponents() const;`
- L273 _protected prototype_ `bool CanBreakAtSegment() const;`
- L275 _protected prototype_ `void GenerateShapePointTypeSubMenu(FMenuBuilder& MenuBuilder) const;`
- L277 _protected prototype_ `void GenerateSnapAlignSubMenu(FMenuBuilder& MenuBuilder) const;`
- L278 _protected prototype_ `void GenerateBreakAtPointSubMenu(FMenuBuilder& MenuBuilder) const;`
- L279 _protected prototype_ `void GenerateBreakAtSegmentSubMenu(FMenuBuilder& MenuBuilder) const;`
- L282 _protected prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — FGCObject interface
- L283 _protected function_ `virtual FString GetReferencerName() const override`
- L290 _protected member_ `TSharedPtr<FUICommandList> ShapeComponentVisualizerActions;` — Output log commands
- L293 _protected member_ `FProperty* ShapePointsProperty;` — Property to be notified when points change
- L296 _protected member_ `TObjectPtr<UZoneShapeComponentVisualizerSelectionState> SelectionState;` — Current selection state
- L299 _protected member_ `bool bAllowDuplication;` — Whether we currently allow duplication when dragging
- L302 _protected member_ `FVector DuplicateAccumulatedDrag;` — Alt-drag: Accumulates delayed drag offset.
- L305 _protected member_ `bool bControlPointPositionCaptured;` — True if the ControlPointPosition has been initialized
- L308 _protected member_ `FVector ControlPointPosition;` — Selected control pints adjusted position, allows the gizmo to move freely, while we constrain the control point.
- L311 _protected member_ `bool bHasCachedRotation = false;` — True if cached rotation is set.
- L314 _protected member_ `FQuat CachedRotation = FQuat::Identity;` — Rotation cached when mouse button is pressed.
- L316 _protected member_ `bool bIsSelectingComponent = false;`
- L319 _protected member_ `int32 SelectedPointForConnecting = -1;` — The point used to calculate the auto connect and intersection states.
- L321 _protected member_ `bool bIsAutoConnecting = false;`
- L329 _protected member_ `FAutoConnectState AutoConnectState;`
- L331 _protected member_ `bool bIsCreatingIntersection = false;`
- L340 _protected member_ `FCreateIntersectionState CreateIntersectionState;`
- L344 _private prototype_ `TArray<UZoneShapeComponent*> BreakAtPoint(bool bCreateNewActor, UZoneShapeComponent* ShapeComp = nullptr) const;`
- L345 _private prototype_ `void BreakAtSegment(bool bCreateNewActor) const;`
- L347 _private prototype_ `void DetectCloseByShapeForAutoConnection(const UZoneShapeComponent* ShapeComp, const FZoneShapePoint& DraggedPoint);`
- L348 _private prototype_ `void DetectCloseByShapeForAutoIntersectionCreation(const UZoneShapeComponent* ShapeComp, const FZoneShapePoint& DraggedPoint);`
- L350 _private prototype_ `void CreateIntersection(UZoneShapeComponent* ShapeComp);`
- L351 _private prototype_ `void CreateIntersectionForSplineShape(UZoneShapeComponent* ShapeComp, FZoneShapePoint& DraggedPoint, bool DestroyCoveredShape = true);`
- L352 _private prototype_ `void CreateIntersectionForPolygonShape(UZoneShapeComponent* ShapeComp, FZoneShapePoint& DraggedPoint);`
- L354 _private prototype_ `void ClearAutoConnectingStatus();`
- L355 _private prototype_ `void ClearAutoIntersectionStatus();`
- L357 _private prototype_ `bool CanAutoConnect(const UZoneShapeComponent* ShapeComp) const;`
- L358 _private prototype_ `bool CanAutoCreateIntersection(const UZoneShapeComponent* ShapeComp) const;`

#### struct `FZoneShapeComponentVisualizer::ZoneShapeConnectorRenderInfo`  
`struct ZoneShapeConnectorRenderInfo`  
_L198-216_
- L200 _public function_ `ZoneShapeConnectorRenderInfo(FVector InPosition, FVector InFoward, FVector InUp) : Position(InPosition) , Foward(InFoward) , Up(InUp)`
- L209 _public member_ `FVector Position = FVector::ZeroVector;` — Position of the connector.
- L212 _public member_ `FVector Foward = FVector::ForwardVector;` — Foward direction of the connector.
- L215 _public member_ `FVector Up = FVector::UpVector;` — Up direction of the connector.

#### struct `FZoneShapeComponentVisualizer::FAutoConnectState`  
`struct FAutoConnectState`  
_L322-328_
- L324 _public member_ `TArray<ZoneShapeConnectorRenderInfo> DestShapeConnectorInfos;`
- L325 _public member_ `int32 ClosestShapeConnectorInfoIndex = INDEX_NONE;`
- L326 _public member_ `FVector NearestPointWorldPosition = FVector::ZeroVector;`
- L327 _public member_ `FVector NearestPointWorldNormal = FVector::ZeroVector;`

#### struct `FZoneShapeComponentVisualizer::FCreateIntersectionState`  
`struct FCreateIntersectionState`  
_L332-339_
- L334 _public member_ `TWeakObjectPtr<UZoneShapeComponent> WeakTargetShapeComponent;`
- L335 _public member_ `int32 OverlappingSegmentIndex = INDEX_NONE;`
- L336 _public member_ `float OverlappingSegmentT = -1.0f;`
- L337 _public member_ `int32 ClosePointIndex = INDEX_NONE;`
- L338 _public member_ `FVector PreviewLocation = FVector::ZeroVector;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API ZONEGRAPHEDITOR_API`

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Public/IZoneGraphEditor.h` (Public)


#### class `IZoneGraphEditor`  
`class IZoneGraphEditor : public FAssetEditorToolkit`  
_L10-14_
- inherits: `FAssetEditorToolkit`
- desc: ZoneGraph Editor public interface

### `Plugins/Runtime/ZoneGraph/Source/ZoneGraphEditor/Public/ZoneGraphEditorModule.h` (Public)


#### class `FZoneGraphEditorModule`  
`class FZoneGraphEditorModule : public IModuleInterface`  
_L15-30_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L19 _public prototype_ `virtual void StartupModule() override;`
- L20 _public prototype_ `virtual void ShutdownModule() override;`
- L23 _private prototype_ `void RegisterComponentVisualizer(FName ComponentClassName, TSharedPtr<FComponentVisualizer> Visualizer);`
- L24 _private prototype_ `void RegisterMenus();`
- L26 _private prototype_ `void OnBuildZoneGraph();`
- L28 _private member_ `TArray<FName> RegisteredComponentClassNames;`
- L29 _private member_ `TSharedPtr<FUICommandList> PluginCommands;`
