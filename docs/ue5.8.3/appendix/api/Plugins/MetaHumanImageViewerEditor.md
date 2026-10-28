# Plugins / MetaHumanImageViewerEditor

- module root: `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor`
- headers: 9; symbols: 242
- symbol kinds: class=11, delegate=3, function=14, macro=6, member=87, prototype=118, struct=3
- PrivateDependencyModuleNames: CaptureDataCore, CoreUObject, EditorStyle, Engine, InputCore, MetaHumanCoreEditor, Slate, UnrealEd
- PublicDependencyModuleNames: Core, EditorStyle, MediaAssets, MetaHumanCore, MetaHumanCoreTech, MetaHumanImageViewer, ProceduralMeshComponent, SlateCore

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Private/MetaHumanImageViewerEditorModule.h` (Private)


#### class `FMetaHumanImageViewerEditorModule`  
`class FMetaHumanImageViewerEditorModule : public IModuleInterface`  
_L7-15_
- inherits: `IModuleInterface`
- L13 _public prototype_ `virtual void StartupModule() override;`
- L14 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/MetaHumanCurveDragOperations.h` (Public)


#### class `IMetaHumanEditorDragOperation`  
`class IMetaHumanEditorDragOperation`  
_L12-20_
- L15 _public prototype_ `virtual ~IMetaHumanEditorDragOperation() = default;`
- L16 _public prototype_ `virtual void OnBeginDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) = 0;`
- L17 _public prototype_ `virtual void OnDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) = 0;`
- L18 _public prototype_ `virtual void OnEndDrag() = 0;`
- L19 _public prototype_ `virtual void OnDragOperationPaint(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InPaintOnLayerId) = 0;`

#### class `FMetaHumanPointDragOperation`  
`class FMetaHumanPointDragOperation : public IMetaHumanEditorDragOperation`  
_L22-44_
- inherits: `IMetaHumanEditorDragOperation`
- L26 _public prototype_ `virtual void OnBeginDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L27 _public prototype_ `virtual void OnDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L28 _public prototype_ `virtual void OnEndDrag() override;`
- L29 _public prototype_ `virtual void OnDragOperationPaint(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InPaintOnLayerId) override;`
- L31 _public prototype_ `void Initialize(TSharedPtr<class FMetaHumanCurveDataController> InCurveDataController, const TSet<int32>& InSelectedIds);`
- L33 _public member_ `FOnGetPositionOnImage OnGetPostionOnImageDelegate;`
- L37 _private member_ `TSet<int32> SelectedPointIds;`
- L38 _private member_ `FVector2D PreviousFramePosition;`
- L39 _private member_ `double DragElapsed = 0.0;`
- L40 _private member_ `double DragLastTime = 0.0;`
- L42 _private member_ `TSharedPtr<class FMetaHumanCurveDataController> CurveDataController;`
- L43 _private member_ `TUniquePtr<class FScopedTransaction> Transaction;`

#### class `FMetaHumanMarqueSelectOperation`  
`class FMetaHumanMarqueSelectOperation : public IMetaHumanEditorDragOperation`  
_L46-68_
- inherits: `IMetaHumanEditorDragOperation`
- L50 _public prototype_ `virtual void OnBeginDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L51 _public prototype_ `virtual void OnDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L52 _public prototype_ `virtual void OnEndDrag() override;`
- L53 _public prototype_ `virtual void OnDragOperationPaint(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InPaintOnLayerId) override;`
- L55 _public prototype_ `void Initialize(TSharedPtr<class FMetaHumanCurveDataController> InCurveDataController);`
- L57 _public member_ `FOnResolveMarqueeSelection ResolveMarqueeSelectionDelegate;`
- L62 _private member_ `FSlateRect Marquee;` — The current marquee rectangle
- L65 _private member_ `FVector2D RealInitialPosition;` — Real Initial Position do to the delayed drag
- L67 _private member_ `TSharedPtr<class FMetaHumanCurveDataController> CurveDataController;`

#### struct `FMetaHumanCurveEditorDelayedDrag`  
`struct FMetaHumanCurveEditorDelayedDrag : FDelayedDrag`  
_L70-81_
- inherits: `FDelayedDrag`
- L73 _public member_ `TUniquePtr<IMetaHumanEditorDragOperation> DragImpl;` — The drag implementation to use once the drag has started
- L76 _public function_ `FMetaHumanCurveEditorDelayedDrag(FVector2D InInitialPosition, FKey InEffectiveKey) : FDelayedDrag(InInitialPosition, InEffectiveKey)` — Start a delayed drag operation at the specified position and effective key

#### Free symbols / members of external scopes

- L9 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(FVector2D, FOnGetPositionOnImage, const FVector2D&, bool bUseImageUV);`
- L9 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(FVector2D, FOnGetPositionOnImage, const FVector2D&, bool bUseImageUV);`
- L10 _delegate_ `DECLARE_DELEGATE_OneParam(FOnResolveMarqueeSelection, const FSlateRect& InSelection) class IMetaHumanEditorDragOperation { public: virtual ~IMetaHumanEditorDragOperation() = default; virtual void OnBeginDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) = 0; virtual void OnDrag(const FVector2D& InGeometry, const FPointerEvent& InMouseEvent) = 0; virtual void OnEndDrag() = 0; virtual void OnDragOperationPaint(const FGeometry& InAllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 InPaintOnLayerId) = 0; };`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/MetaHumanDepthMeshComponent.h` (Public)


#### class `UMetaHumanDepthMeshComponent`  
`class UMetaHumanDepthMeshComponent : public UProceduralMeshComponent`  
_L12-68_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UProceduralMeshComponent`
- L18 _public prototype_ `UMetaHumanDepthMeshComponent(const FObjectInitializer& InObjectInitializer);`
- L21 _public prototype_ `void OnRegister() override;`
- L22 _public prototype_ `void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L26 _public prototype_ `virtual FBoxSphereBounds CalcBounds(const FTransform& InLocalToWorld) const override;`
- L30 _public prototype_ `void SetDepthTexture(class UTexture* InDepthTexture);` — Sets the texture with depth data to display the mesh
- L33 _public prototype_ `void SetCameraCalibration(class UCameraCalibration* InCameraCalibration);` — Sets the camera calibration to calculate the placement of the depth mesh on the viewport
- L36 _public prototype_ `void SetDepthRange(float InDepthNear, float InDepthFar);` — Set the depth near and far planes to clamp the display of depth data
- L39 _public prototype_ `void SetSize(int32 InWidth, int32 InHeight);` — Set the resolution of the depth mesh
- L43 _private prototype_ `void SetDepthPlaneTransform(bool bInNotifyMaterial = false);` — Sets depth plane transform based on the depth far plane
- L45 _private prototype_ `void UpdateMaterialDepth();`
- L46 _private prototype_ `void UpdateMaterialTexture();`
- L47 _private prototype_ `void UpdateMaterialCameraIntrinsics();`
- L52 _private member_ `TObjectPtr<UCameraCalibration> CameraCalibration;` — `UPROPERTY()`
- L55 _private member_ `TObjectPtr<UTexture> DepthTexture;` — `UPROPERTY(EditAnywhere, Category = Texture)`
- L58 _private member_ `int32 Width = -1;` — `UPROPERTY()`
- L61 _private member_ `int32 Height = -1;` — `UPROPERTY()`
- L64 _private member_ `float DepthNear = 10.0f;` — `UPROPERTY(EditAnywhere, Category = DepthRange)`
- L67 _private member_ `float DepthFar = 55.5f;` — `UPROPERTY(EditAnywhere, Category = DepthRange)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANIMAGEVIEWEREDITOR_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/MetaHumanFootageComponent.h` (Public)


#### struct `FFootagePlaneData`  
`struct FFootagePlaneData`  
_L15-27_
- reflection: `USTRUCT()`
- L20 _public member_ `TObjectPtr<class UStaticMeshComponent> FootagePlane;` — `UPROPERTY(VisibleAnywhere, Category = "Footage Plane")`
- L23 _public member_ `TObjectPtr<class UTexture> ColorMediaTexture;` — `UPROPERTY(VisibleAnywhere, Category = "Footage Plane")`
- L26 _public member_ `TObjectPtr<class UTexture> DepthMediaTexture;` — `UPROPERTY(VisibleAnywhere, Category = "Footage Plane")`

#### class `UMetaHumanFootageComponent`  
`class UMetaHumanFootageComponent : public UPrimitiveComponent`  
_L36-117_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPrimitiveComponent`
- desc: A component that handles displaying of footage data in an AB viewport. Internally this component holds two plane static meshes with a material capable of displaying color or depth data. The meshes are transformed to account for the camera position and to be in the right aspect ratio.
- L42 _public prototype_ `UMetaHumanFootageComponent();`
- L45 _public prototype_ `virtual void PostLoad() override;`
- L49 _public prototype_ `void SetCameraCalibration(class UCameraCalibration* InCameraCalibration);` — Position the plane meshes to be in the right location and scale based given a camera calibration
- L52 _public prototype_ `void SetFootageResolution(const FVector2D& InResolution);` — When no calibration is known, specify the footage resolution instead in order to position the plane
- L55 _public prototype_ `void SetCamera(const FString& InCamera);` — Sets the active camera to use in the calibration
- L58 _public prototype_ `void SetMediaTextures(class UTexture* InColorMediaTexture, class UTexture* InDepthMediaTexture, bool bNotifyMaterial = false);` — Set the media textures that represent color and depth data. The visibility of each texture is controlled by ShowRGBChannel and ShowDepthChannel
- L61 _public prototype_ `void SetDepthRange(int32 InDepthNear, int32 InDepthFar);` — Sets the depth range used in the footage plane material
- L64 _public prototype_ `TArray<class UStaticMeshComponent*> GetFootagePlaneComponents() const;` — Returns both plane components
- L67 _public prototype_ `class UStaticMeshComponent* GetFootagePlaneComponent(EABImageViewMode InViewMode) const;` — Returns the plane component of the given AB view mode
- L70 _public prototype_ `void SetFootageVisible(EABImageViewMode InViewMode, bool bInIsVisible);` — Set the footage plane visibility on the given AB view mode
- L73 _public prototype_ `void ShowColorChannel(EABImageViewMode InViewMode);` — Display the color channel in the given AB view mode
- L76 _public prototype_ `void SetUndistortionEnabled(EABImageViewMode InViewMode, bool bUndistort);` — Set if we should display undistort the footage being displayed
- L84 _public prototype_ `void GetFootageScreenRect(const FVector2D& InViewportSize, float& OutFieldOfView, FBox2D& OutScreenRect, FTransform& OutCameraTransform) const;` — Calculates the field of view required to focus on this footage component also returns the screen rectangle this component occupies on screen a transform corresponding the extrinsic camera parameters that can be used to focus the viewport on the footage in 3D space
- L89 _private prototype_ `void CreateFootageMaterialInstances();` — Creates the material used to display color and depth data from footage in the viewport
- L92 _private prototype_ `class UMaterialInstanceDynamic* GetFootageMaterialInstance(EABImageViewMode InViewMode);` — Returns the material instance of a given AB view mode
- L95 _private prototype_ `void ConfigurePlane(EABImageViewMode InViewMode);` — Configure a given AB footage plane to display color
- L100 _private member_ `TMap<EABImageViewMode, FFootagePlaneData> FootagePlanes;` — `UPROPERTY(VisibleAnywhere, Category = "Footage Planes")`
- L103 _private member_ `TObjectPtr<UCameraCalibration> CameraCalibration;` — `UPROPERTY(VisibleAnywhere, Category = "Calibration")`
- L106 _private member_ `FString Camera;` — `UPROPERTY(VisibleAnywhere, Category = "Calibration")`
- L109 _private member_ `int32 DepthDataNear = 10;` — Depth range
- L110 _private member_ `int32 DepthDataFar = 50;`
- L116 _private member_ `FCameraCalibration EffectiveCalibration;` — An effective calibration to use when no actual calibration is known. This sets the image resolution from SetFootageResolution and an arbitrary field of view. Its sufficient to place the image plane in the scene.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANIMAGEVIEWEREDITOR_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/MetaHumanSceneCaptureComponent2D.h` (Public)


#### class `UMetaHumanSceneCaptureComponent2D`  
`class UMetaHumanSceneCaptureComponent2D : public USceneCaptureComponent2D`  
_L13-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneCaptureComponent2D`
- L18 _public prototype_ `UMetaHumanSceneCaptureComponent2D(const FObjectInitializer& InObjectInitializer);`
- L21 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L26 _public prototype_ `void SetViewportClient(TWeakPtr<class FEditorViewportClient> InPerformerViewportClient);` — Sets the viewport client that controls this component
- L29 _public prototype_ `void SetViewMode(EViewModeIndex InViewMode);` — Set the ShowFlags for this component based a view mode index
- L31 _public prototype_ `void InvalidateCache();`
- L36 _private member_ `TWeakPtr<FEditorViewportClient> ViewportClientRef;` — A reference to the viewport client that controls this component
- L38 _private member_ `static constexpr int32 NumTicksAfterCacheInvalidation = 2;`
- L39 _private member_ `int32 CurrentNumTicksAfterCacheInvalidation = 0;`
- L40 _private member_ `float CachedFOVAngle = -1;`
- L41 _private member_ `float CachedCustomNearClippingPlane = -1;`
- L42 _private member_ `FRotator CachedViewRotation = FRotator(0, 0, 0);`
- L43 _private member_ `FVector CachedViewLocation = FVector(0, 0, 0);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API METAHUMANIMAGEVIEWEREDITOR_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/SABImage.h` (Public)


#### class `SABImage`  
`class SABImage : public SMetaHumanImageViewer, public FGCObject`  
_L16-113_
- inherits: `SMetaHumanImageViewer,FGCObject`
- L21 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnInvalidate);`
- L23 _public function_ `FOnInvalidate& OnInvalidate()`
- L26 _public prototype_ `void Setup(bool bInManageTextures);`
- L28 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector&) override;`
- L29 _public prototype_ `virtual FString GetReferencerName() const override;`
- L31 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L32 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L33 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L34 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L35 _public prototype_ `virtual FReply OnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L37 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InWidgetClippingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool InParentEnabled) const override;`
- L41 _public prototype_ `void SetTextures(UTexture* InTextureA, UTexture* InTextureB);`
- L42 _public prototype_ `UTextureRenderTarget2D* GetRenderTarget(EABImageViewMode InMode) const;`
- L44 _public prototype_ `void SetViewMode(EABImageViewMode InViewMode);`
- L45 _public prototype_ `EABImageViewMode GetViewMode() const;`
- L47 _public function_ `TArray<EABImageViewMode> SingleViewModes() const`
- L48 _public function_ `TArray<EABImageViewMode> AllViewModes() const`
- L52 _public function_ `bool IsSingleView() const`
- L53 _public function_ `bool IsMultiView() const`
- L54 _public function_ `bool IsTextureView() const`
- L56 _public prototype_ `void SetNavigationMode(EABImageNavigationMode InNavigationMode);`
- L57 _public prototype_ `EABImageNavigationMode GetNavigationMode() const;`
- L59 _public prototype_ `void AdjustZoomForFootageInDualView(double InFootageAspect) const;`
- L62 _public prototype_ `void ResetABWipePostion();` — Reset the position of wipe mode to default
- L67 _private member_ `FOnInvalidate OnInvalidateDelegate;`
- L70 _private member_ `TMap<EABImageViewMode, TObjectPtr<UTextureRenderTarget2D>> RenderTarget;`
- L72 _private member_ `EABImageViewMode ViewMode = EABImageViewMode::A;`
- L73 _private member_ `EABImageNavigationMode NavigationMode = EABImageNavigationMode::TwoD;`
- L75 _private member_ `FVector2f Origin = FVector2f::ZeroVector;`
- L76 _private member_ `float Angle = 0;`
- L77 _private member_ `float Alpha = 0;`
- L79 _private member_ `const float OriginSize = 20;`
- L80 _private member_ `const float LineThickness = 1;`
- L81 _private member_ `const float PickSensitivity = 5;`
- L82 _private member_ `const float LabelOffset = 30;`
- L83 _private member_ `const float AlphaLineLength = 200;`
- L85 _private member_ `const FLinearColor NormalColour = FLinearColor(1, 0, 0);`
- L86 _private member_ `const FLinearColor HighlightedColour = FLinearColor(1, 1, 0);`
- L88 _private member_ `bool bOriginHighlighted = false;`
- L89 _private member_ `bool bOriginMove = false;`
- L90 _private member_ `bool bAngleHighlighted = false;`
- L91 _private member_ `bool bAngleMove = false;`
- L92 _private member_ `bool bAlphaHighlighted = false;`
- L93 _private member_ `bool bAlphaMove = false;`
- L95 _private member_ `FVector2f OriginOffset = FVector2f::ZeroVector;`
- L96 _private member_ `float AngleOffset = 0;`
- L98 _private prototype_ `void GetLines(const FGeometry& InGeometry, TArray<FVector2f>& OutOrigin, TArray<FVector2f>& OutAngle, TArray<FVector2f>& OutAlpha) const;`
- L99 _private prototype_ `bool HitLines(const FVector2f& InPoint, const TArray<FVector2f>& InLines) const;`
- L103 _protected prototype_ `virtual void GeometryChanged() override;`
- L107 _private member_ `TObjectPtr<UMaterialInstanceDynamic> MaterialInstance = nullptr;`
- L109 _private member_ `FSlateBrush Brush;`
- L111 _private prototype_ `FVector2f Get2DLocalMouse(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, EABImageMouseSide &OutMouseSide);`
- L112 _private member_ `EABImageMouseSide MouseSideOrig = EABImageMouseSide::NotApplicable;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API METAHUMANIMAGEVIEWEREDITOR_API`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnInvalidate);`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/SMetaHumanOverlayWidget.h` (Public)


#### class `SMetaHumanOverlayWidget`  
`template<class T> class SMetaHumanOverlayWidget : public T`  
_L19-71_
- inherits: `T`
- L24 _public function_ `SMetaHumanOverlayWidget()`
- L29 _public function_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InWidgetClippingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool InParentEnabled) const override`
- L62 _public function_ `void SetOverlay(const FText& InOverlay)`
- L69 _private member_ `FText Overlay;`
- L70 _private member_ `FSlateBrush NoEntryBrush;`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/STrackerImageViewer.h` (Public)


#### struct `FViewerStatesForFrame`  
`struct FViewerStatesForFrame`  
_L11-36_
- L14 _public member_ `TMap<FString, TArray<FVector2D>> SplineDensePoints;` — Dense points used to draw the curves as lines between the points
- L17 _public member_ `TMap<FString, TArray<FVector2D>> SplineDensePointsImageSpace;` — Local copy of dense points in Image Space as is original contour data
- L20 _public member_ `TMap<FString, TArray<FVector2D>> AllDensePointsForSplines;` — This member is only used as advanced comparison tool, when Cvar to show full curve is enabled
- L23 _public member_ `TArray<FControlVertex> ControlVerticesForDraw;` — Local copy of control vertices in widget space for drawing
- L26 _public member_ `TSet<int32> SelectedPointIds;` — A list of selected points on visible curves
- L29 _public member_ `TSet<FString> SelectedCurveNames;` — A list of selected curves. Should match the outliner
- L32 _public member_ `FString HighlightedCurveName;` — A curve the mouse is hovering over
- L35 _public member_ `int32 HighlightedPointID = 0;` — A point the mouse is hovering over

#### class `STrackerImageViewer`  
`class STrackerImageViewer : public SABImage`  
_L38-191_
- inherits: `SABImage`
- L43 _public function_ `SLATE_BEGIN_ARGS(STrackerImageViewer) : _ShouldDrawPoints(true) , _ShouldDrawCurves(true) , _DefaultCurvesColor(FLinearColor::Green) , _DefaultPointsColor(FLinearColor::Green) , _HighlightedColor(FLinearColor::White) , _SelectedColor(FLinearColor::Yellow) , _DeactivatedColor(FLinearColor::Gray)`
- L52 _public prototype_ `SLATE_ATTRIBUTE(const FSlateBrush*, Image) SLATE_ATTRIBUTE(bool, ShouldDrawPoints) SLATE_ATTRIBUTE(bool, ShouldDrawCurves) SLATE_ARGUMENT(FLinearColor, DefaultCurvesColor) SLATE_ARGUMENT(FLinearColor, DefaultPointsColor) SLATE_ARGUMENT(FLinearColor, HighlightedColor) SLATE_ARGUMENT(FLinearColor, SelectedColor) SLATE_ARGUMENT(FLinearColor, DeactivatedColor) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L79 _public prototype_ `virtual FReply OnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L80 _public prototype_ `virtual FReply OnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L81 _public prototype_ `virtual FReply OnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L82 _public prototype_ `virtual FReply OnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;`
- L83 _public prototype_ `virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;`
- L85 _public function_ `virtual bool SupportsKeyboardFocus() const override`
- L87 _public prototype_ `virtual int32 OnPaint(const FPaintArgs& InArgs, const FGeometry& InAllottedGeometry, const FSlateRect& InWidgetClippingRect, FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FWidgetStyle& InWidgetStyle, bool InParentEnabled) const override;`
- L92 _public function_ `FVector2D GetTrackerImageSize() const` — Returns the size of the underlying tracker image. Used to calculate the correct placement of curves and points in the image being displayed
- L95 _public prototype_ `bool ContainsData() const;` — True if the viewer Data Controller contains data
- L98 _public prototype_ `void SetTrackerImageSize(const FIntPoint& InTrackerImageSize);` — Sets the size of the underlying tracker image. Used to calculate the correct placement of curves and points in the image being displayed
- L101 _public prototype_ `void ResetTrackerImageScreenRect(const FBox2D& InTrackerScreenRect = FBox2D{ ForceInit });` — Set the tracker image screen rect used to place the tracking contours in the correct location on screen. By default this will be the entire widget area
- L104 _public prototype_ `void UpdateCurveSelection(bool bClearPointSelection);` — A function connected to a callback in controller when curve selection is changed
- L107 _public prototype_ `void SetDataControllerForCurrentFrame(TSharedPtr<class FMetaHumanCurveDataController> InShapeAnnotation);` — Sets the data controller for the current frame
- L110 _public prototype_ `void SetEditCurvesAndPointsEnabled(bool bInCanEdit);` — Sets whether or not the points and curves can be edited user interaction
- L113 _public prototype_ `void SetCurvesColor(FLinearColor InColor);` — Set the color for curves. This will update the default color
- L116 _public prototype_ `void SetPointsColor(FLinearColor InColor);` — Set the color for points. This will update the default color
- L119 _public prototype_ `void SetPointsSize(float InSize);` — Set the size for points. This will update the default size
- L122 _public prototype_ `virtual void ResetView() override;` — Resets the view to default
- L125 _public prototype_ `void UpdateDisplayedDataForWidget();` — Update visual data for points and curves on this widget from underlying contour data
- L128 _public prototype_ `void UpdatePointPositionFullCurve(IConsoleVariable* InVar);` — A wrapper around Update point position for CVar
- L131 _public prototype_ `FVector2D GetPointPositionOnImage(const FVector2D& InScreenPosition, bool bUseImageUV = true) const;` — Returns image coordinates for specified screen position
- L134 _public prototype_ `TSet<int32>& GetViewportSelectedPointIds();` — Returns a reference to selected points ids stored in the viewport
- L139 _protected prototype_ `bool CanEditCurvesAndPoints() const;`
- L141 _protected prototype_ `FVector2D GetPointPositionOnScreen(const FVector2D& InOriginalPosition, const FBox2D& InUV, const FVector2D& InWidgetSize) const;`
- L142 _protected prototype_ `FLinearColor GetPointColor(const int32 InPointID) const;`
- L143 _protected prototype_ `FLinearColor GetCurveColor(const FString& InCurveName) const;`
- L146 _protected prototype_ `TPair<FString, FVector2D> GetClosestInsertionPosition(const FVector2D& InMousePosition, const float InDistanceToCheck) const;` — Returns a curve name and closest position on that curve to mouse pos. OutParam is the closest index on dense spline
- L149 _protected prototype_ `TMap<FString, int32> GetClosestSplinePointOnCurves(const FVector2D& InMousePosition, const float InDistanceToCheck) const;` — Returns the map of curves with corresponding dense spline point ID within a check distance from mouse
- L151 _protected prototype_ `void DrawControlVertices(FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FGeometry& AllottedGeometry) const;`
- L152 _protected prototype_ `void DrawTrackingCurves(FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FGeometry& AllottedGeometry) const;`
- L153 _protected prototype_ `void DrawTrackingCurvesFromAllPoints(FSlateWindowElementList& OutDrawElements, int32 InLayerId, const FGeometry& AllottedGeometry) const;`
- L155 _protected prototype_ `void ResolveHighlightingForMouseMove(const FVector2D& InMousePosition);`
- L156 _protected prototype_ `void ResolveSelectionFromMarquee(const FSlateRect& InSelectionMarquee);`
- L157 _protected prototype_ `void PopulateSelectionListForMouseClick();`
- L158 _protected prototype_ `void AddRemoveKey(const FVector2D& InMousePos, bool bAdd);`
- L160 _protected prototype_ `TArray<FVector2D> GetPointAtPosition(const FVector2D& InScreenPosition) const;`
- L161 _protected prototype_ `bool SetHighlightingFromPoint(const FVector2D& InMousePos);`
- L162 _protected prototype_ `bool SetHighlightingFromCurve(const FVector2D& InMousePos);`
- L163 _protected prototype_ `bool ResolveSelectionForMouseClick(const FPointerEvent& InMouseEvent, const FVector2D& InMousePos);`
- L164 _protected prototype_ `bool SetManipulationStateForMouseClick(const FPointerEvent& InMouseEvent, const FVector2D& InMousePos);`
- L166 _protected member_ `bool bCanEditPointsAndCurves = true;`
- L167 _protected member_ `TAttribute<bool> bShouldDrawPoints;`
- L168 _protected member_ `TAttribute<bool> bShouldDrawCurves;`
- L170 _protected member_ `FBox2D TrackerImageRect;`
- L171 _protected member_ `FVector2D TrackerImageSize;`
- L173 _protected member_ `TOptional<FMetaHumanCurveEditorDelayedDrag> DragOperation;`
- L174 _protected member_ `TSharedPtr<class FMetaHumanCurveDataController> CurveDataController;`
- L175 _protected member_ `FViewerStatesForFrame ViewState;`
- L179 _protected member_ `FLinearColor DefaultCurvesColor;`
- L180 _protected member_ `FLinearColor DefaultPointsColor;`
- L181 _protected member_ `FLinearColor HighlightedColor;`
- L182 _protected member_ `FLinearColor SelectedColor;`
- L183 _protected member_ `FLinearColor DeactivatedColor;`
- L185 _protected member_ `const int32 LinesPerCircle = 33;`
- L186 _protected member_ `float PointSize = 5.f;`
- L188 _protected member_ `double MouseMoveLastTime = 0;`
- L189 _protected member_ `double MouseMoveElapsed = 0;`
- L190 _protected member_ `static constexpr float DistanceToCurveForHighlighting = 5.0;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API METAHUMANIMAGEVIEWEREDITOR_API`

### `Plugins/MetaHuman/MetaHumanAnimator/Source/MetaHumanImageViewerEditor/Public/Utils/CustomMaterialUtils.h` (Public)


#### class `CustomMaterialUtils`  
`class CustomMaterialUtils`  
_L15-60_
- L19 _public prototype_ `static void SetupExpression(class UMaterialExpressionTextureObjectParameter* InExpression, const FName& InName, bool bInUseExternalSampler);`
- L20 _public prototype_ `static void SetupExpression(class UMaterialExpressionScalarParameter* InExpression, const FName& InName, bool bInUseExternalSampler);`
- L21 _public prototype_ `static void SetupExpression(class UMaterialExpressionVectorParameter* InExpression, const FName& InName, bool bInUseExternalSampler);`
- L22 _public prototype_ `static void SetupExpression(class UMaterialExpression* InExpression, const FName& InName, bool bInUseExternalSampler);`
- L25 _public function_ `template<typename T> static void AddInput(const FName& InName, UMaterial* InMaterial, UMaterialExpressionCustom* InCustomNode, bool bInUseExternalSampler = false)`
- L46 _public prototype_ `static UMaterialInstanceDynamic* CreateMovieContourDepthMaterial(const FName& InName, bool bInUseExternalSampler, int32 InDepthComponent);` — A material that can show the raw footage, a contour overlay, and depth data. Material parameters are: "Movie"			Texture		RGBA or depth texture "Contours"		Texture		RGBA texture which is overlaid on above "ShowDarken"	Scalar		If >0.5 image is dimmed down "ShowContours"	Scalar		If >0.5 overlay is applied "DepthNear"		Scalar		Minium visible depth value "DepthFar"		Scalar		Maximum visible depth value
- L59 _public prototype_ `static UMaterialInstanceDynamic* CreateDepthMeshMaterial(const FName& InName);` — A material that can show depth data as a 3D mesh. Material parameters are: "Movie"				Texture		Depth texture "InvFocal"			Scalar		The focal length component of the inverse of the camera intrinsic matrix "InvX"				Scalar		The X principle point component of the inverse of the camera intrinsic matrix "InvY"				Scalar		the Y principle point component of the inverse of the camera intrinsic matrix "DepthNear"			Scalar		Minimum visible depth value "DepthFar"			Scalar		Maximum visible depth value "InvExtrinsicRow0	Vector		The first row of the depth camera extrinsic matrix "InvExtrinsicRow1	Vector		The second row of the depth camera extrinsic matrix "InvExtrinsicRow2	Vector		The third row of the depth camera extrinsic matrix "InvExtrinsicRow3	Vector		The fourth row of the depth camera extrinsic matrix

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API METAHUMANIMAGEVIEWEREDITOR_API`
