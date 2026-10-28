# Editor / ViewportSnapping

- module root: `Source/Editor/ViewportSnapping`
- headers: 2; symbols: 15
- symbol kinds: class=2, function=1, prototype=12
- PrivateDependencyModuleNames: Core, RHI, RenderCore
- PrivateIncludePathModuleNames: UnrealEd

### `Source/Editor/ViewportSnapping/Public/ISnappingPolicy.h` (Public)


#### class `ISnappingPolicy`  
`class ISnappingPolicy`  
_L10-67_
- L13 _public prototype_ `virtual ~ISnappingPolicy() = default;`
- L21 _public prototype_ `virtual void SnapScale(FVector& Point, const FVector& GridBase)=0;` — Snaps a scale value to the scale grid @param Point	The point to snap.  This value will be modified to account for snapping @param GridBase	Base grid offset
- L29 _public prototype_ `virtual void SnapPointToGrid(FVector& Point, const FVector& GridBase)=0;` — Snaps a point value to the positional grid @param Point	The point to snap.  This value will be modified to account for snapping @param GridBase	Base grid offset
- L36 _public prototype_ `virtual void SnapRotatorToGrid(FRotator& Rotation)=0;` — Snaps a rotator to the rotational grid @param Rotation	The rotator to snap.  This value will be modified to account for snapping
- L43 _public prototype_ `virtual void ClearSnappingHelpers(bool bClearImmediately = false)=0;` — Clears all vertices being drawn to help a user snap @param bClearImmediatley	true to clear helpers without fading them out
- L51 _public prototype_ `virtual void DrawSnappingHelpers(const FSceneView* View, FPrimitiveDrawInterface* PDI)=0;` — Draws snapping helpers @param View	The current view of the scene @param PDI	Drawing interface
- L56 _public prototype_ `virtual bool IsRotationSnappingEnabled() const = 0;` — @return true if rotation snapping is enabled
- L61 _public prototype_ `virtual bool IsTranslationSnappingEnabled() const = 0;` — @return true if translation snapping is enabled
- L66 _public prototype_ `virtual bool IsScaleSnappingEnabled() const = 0;` — @return true if scale snapping is enabled

### `Source/Editor/ViewportSnapping/Public/ViewportSnappingModule.h` (Public)


#### class `IViewportSnappingModule`  
`class IViewportSnappingModule : public IModuleInterface`  
_L15-28_
- inherits: `IModuleInterface`
- desc: Snapping policy manager module
- L18 _public prototype_ `virtual void RegisterSnappingPolicy(TSharedPtr<ISnappingPolicy> NewPolicy)=0;`
- L19 _public prototype_ `virtual void UnregisterSnappingPolicy(TSharedPtr<ISnappingPolicy> PolicyToRemove)=0;`
- L21 _public prototype_ `virtual TSharedPtr<ISnappingPolicy> GetMergedPolicy()=0;`
- L23 _public function_ `static TSharedPtr<ISnappingPolicy> GetSnapManager()`
