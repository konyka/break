# Plugins / SmartSnapping

- module root: `Plugins/2D/Paper2D/Source/SmartSnapping`
- headers: 1; symbols: 14
- symbol kinds: class=1, member=2, prototype=11
- PrivateDependencyModuleNames: Core, CoreUObject, LevelEditor, Slate, SlateCore, ViewportSnapping

### `Plugins/2D/Paper2D/Source/SmartSnapping/Private/PlanarConstraintSnapPolicy.h` (Private)


#### class `FPlanarConstraintSnapPolicy`  
`class FPlanarConstraintSnapPolicy : public ISnappingPolicy`  
_L14-37_
- inherits: `ISnappingPolicy`
- L17 _public member_ `FPlane SnapPlane;`
- L19 _public prototype_ `virtual bool IsEnabled() const;`
- L20 _public prototype_ `void ToggleEnabled();`
- L23 _private member_ `bool bIsEnabled;`
- L25 _public prototype_ `FPlanarConstraintSnapPolicy();`
- L28 _public prototype_ `virtual void SnapScale(FVector& Point, const FVector& GridBase) override;` — ISnappingPolicy interface
- L29 _public prototype_ `virtual void SnapPointToGrid(FVector& Point, const FVector& GridBase) override;`
- L30 _public prototype_ `virtual void SnapRotatorToGrid(FRotator& Rotation) override;`
- L31 _public prototype_ `virtual void ClearSnappingHelpers(bool bClearImmediately) override;`
- L32 _public prototype_ `virtual void DrawSnappingHelpers(const FSceneView* View, FPrimitiveDrawInterface* PDI) override;`
- L33 _public prototype_ `virtual bool IsTranslationSnappingEnabled() const override;`
- L34 _public prototype_ `virtual bool IsRotationSnappingEnabled() const override;`
- L35 _public prototype_ `virtual bool IsScaleSnappingEnabled() const override;`
