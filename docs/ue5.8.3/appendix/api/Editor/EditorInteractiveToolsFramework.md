# Editor / EditorInteractiveToolsFramework

- module root: `Source/Editor/Experimental/EditorInteractiveToolsFramework`
- headers: 112; symbols: 3179
- symbol kinds: class=123, delegate=16, enum=17, enumerator=79, function=156, macro=51, member=1063, namespace=98, prototype=1458, struct=79, typedef=8, variable=31
- PrivateDependencyModuleNames: AnimationCore, ApplicationCore, ContentBrowser, CoreUObject, DeveloperSettings, EditorFramework, EditorSubsystem, Engine, InputCore, Json, JsonUtilities, MeshDescription, PropertyEditor, RenderCore, Slate, SlateCore, StaticMeshDescription, ToolWidgets, TypedElementRuntime, ViewportSnapping, WorkspaceMenuStructure
- PublicDependencyModuleNames: Core, InteractiveToolsFramework, TypedElementFramework, UnrealEd

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Internal/EditorGizmos/EditorGizmoElementSharedInternal.h` (Internal)


#### class `UE::Editor::InteractiveToolsFramework::Internal::FTransformGizmoScaleAdjuster`  
`class FTransformGizmoScaleAdjuster : public GizmoRenderingUtil::IViewBasedTransformAdjuster`  
_L24-34_
- inherits: `GizmoRenderingUtil::IViewBasedTransformAdjuster`
- desc: Adjuster to apply various scale adjustments provided by external sources.
- L27 _public prototype_ `explicit FTransformGizmoScaleAdjuster(const IToolsContextQueriesAPI* InQueriesAPI, const TWeakInterfacePtr<ITransformGizmoSource>& InTransformGizmoSource);`
- L29 _public prototype_ `virtual FTransform GetAdjustedComponentToWorld(const GizmoRenderingUtil::ISceneViewInterface& InView, const FTransform& InCurrentComponentToWorld) override;`
- L32 _private member_ `const IToolsContextQueriesAPI* QueriesAPI;`
- L33 _private member_ `TWeakInterfacePtr<ITransformGizmoSource> TransformGizmoSource;`

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Editor` (scope `UE`)
- L16 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L21 _namespace_ `namespace Internal` (scope `UE::Editor::InteractiveToolsFramework`)
- L37 _function_ `template <EAxis::Type Axis> constexpr FVector GetAxisVector(const EAxisList::Type InAxisCoordinateSystem)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L43 _function_ `template <> constexpr FVector GetAxisVector<EAxis::X>(const EAxisList::Type InAxisCoordinateSystem)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L49 _function_ `template <> inline FVector GetAxisVector<EAxis::Y>(const EAxisList::Type InAxisCoordinateSystem)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L57 _function_ `template <> constexpr FVector GetAxisVector<EAxis::Z>(const EAxisList::Type InAxisCoordinateSystem)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L63 _function_ `template <EAxis::Type Axis> constexpr FVector GetAxisVector()` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L68 _function_ `inline FVector GetAxisVector(EAxis::Type InAxis)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L87 _function_ `inline bool IsAxisSingular(const EAxisList::Type InAxisList)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L107 _function_ `inline bool IsAxisPlanar(const EAxisList::Type InAxisList)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L128 _prototype_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> void GetSignedAxisBasis(EAxisList::Type InAxis, Math::TVector<RealType>& OutForward, Math::TVector<RealType>& OutUp, Math::TVector<RealType>& OutSide, const EAxisList::Type InAxisCoordinateSystem);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Compute Forward, Up, and Side vectors for the given axis. Vectors are returned so that they're aligned with the "positive" direction for that axis, depending on the provided AxisCoordinateSystem. @note: Not for use with an FFrame, which requires a specific orientation. The result may be invalid if used to construct one.
- L146 _prototype_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> void GetAxisBasis(EAxisList::Type InAxis, Math::TVector<RealType>& OutForward, Math::TVector<RealType>& OutUp, Math::TVector<RealType>& OutSide, const EAxisList::Type InAxisCoordinateSystem);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Compute Forward, Up, and Side vectors for the given axis. Vectors are returned so that when viewed along the axis (for example, top-down for Z), 'Side' points left and 'Up' points upward in that view. This can result in a negative Up vector in world space. The orientation is selected to provide a consistent basis for plane and other calculations that rely on a stable axis orientation relative to the input normal.
- L159 _prototype_ `int32 GetAxisIndex(const EAxisList::Type InAxisList);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Returns an index (0-2) from the given AxisList. The AxisList should specify a single value.
- L162 _prototype_ `Geometry::FFrame3d MakeScreenAlignedPlane(const FVector& InPlaneOrigin, const UGizmoViewContext* InViewContext);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Utility to create a screen-aligned plane from the given ViewContext and world origin.
- L165 _prototype_ `Geometry::FFrame3d MakeTransformedPlane( const FTransform& InTransform, const EToolContextCoordinateSystem InCoordinateSystem, const FVector& InForwardDirection, const FVector& InUpDirection, const FVector& InSideDirection);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Utility to create a plane for the given transform and coordinate space.
- L173 _prototype_ `Geometry::FFrame3d MakeTransformedPlaneForAxisList( const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const EAxisList::Type InAxisList, const TFunctionRef<const UGizmoElementBox*(const EAxisList::Type InAxisList)>& InGetPlanarElementFunc, const TFunctionRef<const IPlaneProvider*(const EAxisList::Type InAxisList)>& InGetAxisPlaneProvider);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Utility to create a plane for the given transform, coordinate space and axis list.
- L185 _prototype_ `Geometry::FFrame3d ModifyPlaneForView( const Geometry::FFrame3d& InPlane, const UGizmoViewContext* InViewContext, FVector& OutDirectionToRemove);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Modifies the given plane so that it, as much as possible, faces the camera while remaining aligned with the original. OutDirectionToRemove can be used to constrain derived movement to a single axis.
- L195 _prototype_ `int8 GetClockwiseAngleSignForAxis(const EAxis::Type InAxis);` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Returns a corrective sign for the given axis such that a positive angle results in a clockwise rotation, relative to that axis' plane. To visualize the need for this, add a positive angle to each axis while is ortho mode for that axis and not how X and Y are negated. Take care to only apply this once, and only to angles. A quat applied to a rotation corrects for this (so in effect, a positive angle in a quat is inverted when applied to X, Y).

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Internal/EditorGizmos/EditorGizmoElementSharedInternal.inl` (Internal)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Editor` (scope `UE`)
- L13 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Editor` (scope `UE`)
- L18 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L18 _namespace_ `namespace Internal` (scope `UE::Editor::InteractiveToolsFramework`)
- L20 _function_ `inline EAxisList::Type GetPlaneNormalAxis(EAxisList::Type InPlaneAxis)` (scope `UE::Editor::InteractiveToolsFramework::Internal`)
- L59 _function_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> void GetSignedAxisBasis(EAxisList::Type InAxis, Math::TVector<RealType>& OutForward, Math::TVector<RealType>& OutUp, Math::TVector<RealType>& OutSide, const EAxisList::Type InAxisCoordinateSystem)` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Get Forward, Up, Side vectors for the given axis.
- L108 _function_ `template <typename RealType UE_REQUIRES(std::is_floating_point_v<RealType>)> void GetAxisBasis(EAxisList::Type InAxis, Math::TVector<RealType>& OutForward, Math::TVector<RealType>& OutUp, Math::TVector<RealType>& OutSide, const EAxisList::Type InAxisCoordinateSystem)` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Get Forward, Up, Side vectors for the given axis.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Internal/EditorGizmos/EditorGizmoMath.h` (Internal)


#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace GizmoMath` (scope `UE::Editor`)
- L15 _prototype_ `FBox2d PlaceRectOutsideCircle(const Geometry::FCircle2d& InCircle, const FBox2d& InRect);` (scope `UE::Editor::GizmoMath`) — Pushes the given rectangle to touch the outside of the given circle.
- L22 _prototype_ `bool ClipLineToBox( const FVector2d& InLineStart, const FVector2d& InLineEnd, const FBox2d& InBox, FVector2d::FReal& OutClippedStart, FVector2d::FReal& OutClippedEnd);` (scope `UE::Editor::GizmoMath`) — Clips the given line within the give box (2D). Returns true if clipped, where the start and end clipped parameters (normalized distance along line) are output. To get positions, use: LineStart + LineDelta * ClippedStart (or End)
- L30 _prototype_ `bool ComputePlaneToScreenMatrix( const UGizmoViewContext* InView, const UE::Geometry::FFrame3d& InPlane, Geometry::FMatrix3d& OutPlaneToScreen);` (scope `UE::Editor::GizmoMath`) — Compute (World) Plane -> Screen matrix. Use inverse for Screen -> Plane.
- L39 _prototype_ `bool ComputeProjectedPointOnPlaneFromScreen( const UGizmoViewContext* InView, const FVector2d& InScreenPoint, const UE::Geometry::FFrame3d& InPlane, FVector& OutPoint);` (scope `UE::Editor::GizmoMath`) — Compute a point on the given plane (from screen). Note that the OutPoint will be in a correct location but is not a ray/plane intersection.
- L49 _prototype_ `bool ComputeAngleInPlaneFromScreen( const UGizmoViewContext* InView, const FVector2d& InScreenPoint, const UE::Geometry::FFrame3d& InPlane, FVector& OutPoint, double& OutAngle);` (scope `UE::Editor::GizmoMath`) — Compute a signed angle in the given plane (from screen). Note that the OutPoint will be in a correct location but is not a ray/plane intersection.
- L60 _prototype_ `bool ComputePointOnPlaneFromScreen( const UGizmoViewContext* InView, const FRay& InRay, const FVector2d& InScreenPoint, const UE::Geometry::FFrame3d& InPlane, FVector& OutPoint);` (scope `UE::Editor::GizmoMath`) — Compute a point on the given plane from screen. This will compute a correct ray/plane intersection when applicable.
- L67 _prototype_ `bool ComputePointOnCircleFromScreen( const UGizmoViewContext* InView, const FVector2d& InScreenPoint, const double& InCircleRadius, const UE::Geometry::FFrame3d& InPlane, FVector& OutPointOnCircle);` (scope `UE::Editor::GizmoMath`)
- L78 _prototype_ `float ComputePositivePlaneSignForView( const UGizmoViewContext* InView, const UE::Geometry::FFrame3d& InPlane, const float InDefaultSign = 1.0f);` (scope `UE::Editor::GizmoMath`) — Compute the positive sign of a plane axis for a given view (which may differ to the plane orientation). Used to determine the direction of manipulation relative to viewport drag. Optionally provide the default sign to fallback to if the sign cannot be determined.
- L84 _prototype_ `EAxisList::Type GetAxisListFromBools(const bool bInEnableX, const bool bInEnableY, const bool bInEnableZ);` (scope `UE::Editor::GizmoMath`) — Convert three bools to an EAxisList::Type
- L90 _prototype_ `[[maybe_unused]] bool GetBoolsFromAxisList(const EAxisList::Type InAxisList, bool bOutActiveAxis[3]);` (scope `UE::Editor::GizmoMath`) — Convert an EAxisList::Type to three bools indicating which axes are active. Returns true if all three axes are active, false otherwise. Based on FComponentElementLevelEditorViewportInteractionCustomization::ValidateScale::CheckActiveAxes
- L93 _prototype_ `FVector GetAxisMultiplier(const EAxisList::Type InAxisList, const FVector& InScreenSpaceMultiplier = FVector(0.0f, 1.0f, 1.0f));` (scope `UE::Editor::GizmoMath`) — Return a Vector to be used as a multiplier for per-axis values.
- L99 _prototype_ `FVector GetAxisCoordinateSystemMultiplier(const EAxisList::Type InAxisCoordinateSystem);` (scope `UE::Editor::GizmoMath`) — Return a Vector representing the positive sign for each axis, depending on the provided coordinate system. @example EAxisList::LeftUpForward will return FVector(1, -1, 1)
- L105 _prototype_ `FVector GetAxisCoordinateSystemMultiplier();` (scope `UE::Editor::GizmoMath`) — Return a Vector representing the positive sign for each axis, depending on the current coordinate system. @example EAxisList::LeftUpForward will return FVector(1, -1, 1)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Internal/EditorGizmos/TransformGizmoAccessor.h` (Internal)


#### struct `UE::Editor::InteractiveToolsFramework::FTransformGizmoAccessor`  
`struct FTransformGizmoAccessor`  
_L13-24_
- desc: Friended class to access UTransformGizmo internals, used externally.
- L15 _public prototype_ `ETransformGizmoPartIdentifier GetLastHitPart(const UTransformGizmo& InGizmo) const;`
- L17 _public prototype_ `bool IsPartSelected(const UTransformGizmo& InGizmo, const ETransformGizmoPartIdentifier InPartId) const;`
- L19 _public prototype_ `FTransform GetGizmoTransform(const UTransformGizmo& InGizmo) const;`
- L20 _public prototype_ `UGizmoElementHitMultiTarget* GetHitTarget(const UTransformGizmo& InGizmo) const;`
- L21 _public prototype_ `EGizmoTransformMode GetCurrentMode(const UTransformGizmo& InGizmo) const;`
- L23 _public prototype_ `FVector2D GetScreenProjectedDirection(const UTransformGizmo& InGizmo, const FVector& InLocalAxis) const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/CVarToggle.h` (Private)


#### class `TCVarToggle`  
`template <typename ValueType> class TCVarToggle`  
_L9-54_
- L12 _public function_ `explicit TCVarToggle(const FString& InName) : Name(InName)`
- L22 _public function_ `~TCVarToggle()`
- L30 _public function_ `ValueType GetValue() const`
- L32 _public function_ `void SetValue(const ValueType& InValue)`
- L42 _private function_ `void OnChanged(IConsoleVariable* InCVar)`
- L51 _private member_ `FDelegateHandle OnChangedHandle;`
- L52 _private member_ `const FString Name;`
- L53 _private member_ `ValueType Value;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Customizations/EditorTRSCustomizationUtils.h` (Private)


#### struct `UE::Editor::GizmoSettings::Private::FPropertyOuterVariant`  
`struct FPropertyOuterVariant`  
_L15-38_
- desc: UObject or StructOnScope
- L17 _public prototype_ `FPropertyOuterVariant() = default;`
- L19 _public function_ `explicit FPropertyOuterVariant(UObject* InObject) : Object(MakeWeakObjectPtr(InObject)) , bIsValid(InObject != nullptr)`
- L25 _public function_ `explicit FPropertyOuterVariant(const TSharedPtr<FStructOnScope>& InStruct) : Struct(InStruct) , bIsValid(InStruct.IsValid())`
- L31 _public member_ `TWeakObjectPtr<UObject> Object = nullptr;`
- L32 _public member_ `TSharedPtr<FStructOnScope> Struct = nullptr;`
- L34 _public function_ `bool IsValid() const`
- L37 _private member_ `bool bIsValid = false;`

#### Free symbols / members of external scopes

- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Editor` (scope `UE`)
- L12 _namespace_ `namespace GizmoSettings` (scope `UE::Editor`)
- L12 _namespace_ `namespace Private` (scope `UE::Editor::GizmoSettings`)
- L40 _prototype_ `const void* GetNestedPropertyValue(const void* InRootContainer, const TSharedPtr<FPropertyPath>& InPropertyPath);` (scope `UE::Editor::GizmoSettings::Private`)
- L43 _prototype_ `const void* GetDefaultPropertyValue(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` (scope `UE::Editor::GizmoSettings::Private`) — Get's the default value by constructing a default struct/object of the outer.
- L45 _prototype_ `TSharedPtr<FPropertyPath> GetPropertyPathRelativeToStructOfType(const TSharedPtr<IPropertyHandle>& InPropertyHandle, const UScriptStruct* InStructType);` (scope `UE::Editor::GizmoSettings::Private`)
- L47 _prototype_ `TSharedPtr<FPropertyPath> GetPropertyPathRelativeToOuter(const TSharedPtr<IPropertyHandle>& InPropertyHandle, const FPropertyOuterVariant& InOuter);` (scope `UE::Editor::GizmoSettings::Private`)
- L50 _prototype_ `FPropertyOuterVariant GetPropertyOuter(const TSharedPtr<IPropertyHandle>& InPropertyHandle);` (scope `UE::Editor::GizmoSettings::Private`) — Gets the first valid outer.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Customizations/GizmoCustomization.h` (Private)


#### class `FTransformGizmoEditorSettingsCustomizationBase`  
`class FTransformGizmoEditorSettingsCustomizationBase : public IDetailCustomization`  
_L17-53_
- inherits: `IDetailCustomization`
- desc: Base detail customization that isolates a single property section from UTransformGizmoEditorSettings::GizmosParameters. Derived classes specify which property, category, and struct type to target. The base class hides all other categories and re-adds the target property's children with custom reset-to-default behavior that compares against a CDO-like default value provided by the subclass.
- L21 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& InDetailBuilder) override;`
- L25 _protected prototype_ `void HideAllProperties(IDetailLayoutBuilder& InDetailBuilder);` — Hides every category and property in the detail layout.
- L31 _protected prototype_ `void IsolateCategory(IDetailLayoutBuilder& InDetailBuilder, const TSharedRef<IPropertyHandle>& InContainerProperty, const FName InCategoryName);` — Hides the original category for @p InContainerProperty and re-adds its children with per-property reset-to-default overrides and optional enabled-state gating via IsPropertyEnabledAttribute.
- L34 _protected prototype_ `bool IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> InPropertyHandle) const;` — Returns true when the property's current value differs from its default, indicating the reset arrow should be shown.
- L37 _protected prototype_ `void OnResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle);` — Copies the default value into the property and saves the config.
- L40 _protected prototype_ `virtual FName GetTargetPropertyName() const = 0;` — Returns the FName of the child property within FGizmosParameters that this customization displays (e.g. "Interaction", "Style", "Debug").
- L43 _protected prototype_ `virtual FName GetTargetCategoryName() const = 0;` — Returns the detail-panel category name under which the target property's children are shown.
- L46 _protected prototype_ `virtual const UScriptStruct* GetTargetStructType() const = 0;` — Returns the UScriptStruct describing the target property's type, used to build relative property paths for reset-to-default comparison.
- L49 _protected prototype_ `virtual const void* GetDefaultValue() const = 0;` — Returns a pointer to a default-constructed instance of the target struct, used as the reference for reset-to-default.
- L52 _protected member_ `TAttribute<bool> IsPropertyEnabledAttribute;` — Optional attribute controlling whether displayed properties are interactive. Set by derived classes that gate on a CVar or other condition.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Customizations/GizmoDebugCustomization.h` (Private)


#### class `FGizmoDebugSettingsCustomization`  
`class FGizmoDebugSettingsCustomization : public FTransformGizmoEditorSettingsCustomizationBase`  
_L11-44_
- inherits: `FTransformGizmoEditorSettingsCustomizationBase`
- desc: Details panel customization for FGizmoDebugSettings, shown in the transform gizmo editor settings. Gated behind a CVar toggle for debug drawing.
- L15 _public prototype_ `FGizmoDebugSettingsCustomization();`
- L21 _protected prototype_ `virtual FName GetTargetPropertyName() const override;` — Returns the property name for the debug settings struct within the gizmo settings.
- L24 _protected prototype_ `virtual FName GetTargetCategoryName() const override;` — Returns the category name under which the debug settings are displayed.
- L27 _protected prototype_ `virtual const UScriptStruct* GetTargetStructType() const override;` — Returns the UScriptStruct type descriptor for FGizmoDebugSettings.
- L30 _protected prototype_ `virtual const void* GetDefaultValue() const override;` — Returns the default FGizmoDebugSettings values used for reset-to-default.
- L36 _private prototype_ `bool IsPropertyEnabled() const;` — Returns true if the debug draw CVar is currently enabled.
- L40 _private member_ `FGizmoDebugSettings DefaultSettings;` — Default settings instance used as the reference value for the details panel.
- L43 _private member_ `TSharedPtr<TCVarToggle<bool>> CVarDebugDraw;` — CVar toggle controlling whether the debug draw settings section is visible and active.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Customizations/GizmoInteractionCustomization.h` (Private)


#### class `FTransformGizmoInteractionCustomization`  
`class FTransformGizmoInteractionCustomization : public FTransformGizmoEditorSettingsCustomizationBase`  
_L10-22_
- inherits: `FTransformGizmoEditorSettingsCustomizationBase`
- desc: Details panel customization for FTransformGizmoInteraction, shown in the transform gizmo editor settings under the Interaction category.
- L14 _protected prototype_ `virtual FName GetTargetPropertyName() const override;`
- L15 _protected prototype_ `virtual FName GetTargetCategoryName() const override;`
- L16 _protected prototype_ `virtual const UScriptStruct* GetTargetStructType() const override;`
- L17 _protected prototype_ `virtual const void* GetDefaultValue() const override;`
- L21 _private member_ `FTransformGizmoInteraction DefaultInteraction;` — Default interaction settings used as the reference for reset-to-default.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Customizations/GizmoPerStateValueCustomization.h` (Private)


#### class `TGizmoPerStateValueCustomization`  
`class TGizmoPerStateValueCustomization : public IPropertyTypeCustomization`  
_L19-190_
- inherits: `IPropertyTypeCustomization`
- L23 _public function_ `static TSharedRef<IPropertyTypeCustomization> MakeInstance()`
- L28 _public function_ `virtual void CustomizeHeader( TSharedRef<IPropertyHandle> InStructPropertyHandle, FDetailWidgetRow& InHeaderRow, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override`
- L132 _public function_ `virtual void CustomizeChildren(TSharedRef<IPropertyHandle> InPropertyHandle, IDetailChildrenBuilder& InChildBuilder, IPropertyTypeCustomizationUtils& InStructCustomizationUtils) override`
- L152 _protected function_ `FOptionalSize GetHeightOverride()`
- L157 _protected function_ `TSharedRef<SWidget> MakeStateValueWidget(const TSharedPtr<IPropertyHandle>& InStateValueHandle)`
- L175 _protected function_ `FSlateColor GetBorderColor(TSharedPtr<SWidget> InWidget) const`
- L183 _private member_ `TSharedPtr<IPropertyHandle> StructPropertyHandle;`
- L185 _private member_ `TSharedPtr<IPropertyHandle> DefaultPropertyHandle;`
- L186 _private member_ `TSharedPtr<IPropertyHandle> HoverPropertyHandle;`
- L187 _private member_ `TSharedPtr<IPropertyHandle> InteractPropertyHandle;`
- L188 _private member_ `TSharedPtr<IPropertyHandle> SelectPropertyHandle;`
- L189 _private member_ `TSharedPtr<IPropertyHandle> SubduePropertyHandle;`
- L193 _function_ `template <> inline FOptionalSize TGizmoPerStateValueCustomization<FGizmoPerStateValueLinearColor>::GetHeightOverride()`

#### Free symbols / members of external scopes

- L45 _function_ `` (scope `TGizmoPerStateValueCustomization::CustomizeHeader`)
- L198 _typedef_ `using FGizmoPerStateValueDoubleCustomization = TGizmoPerStateValueCustomization<FGizmoPerStateValueDouble>;`
- L199 _typedef_ `using FGizmoPerStateValueLinearColorCustomization = TGizmoPerStateValueCustomization<FGizmoPerStateValueLinearColor>;`
- L200 _typedef_ `using FGizmoPerStateValueMaterialVariantCustomization = TGizmoPerStateValueCustomization<FGizmoPerStateValueMaterialVariant>;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Customizations/GizmoStyleCustomization.h` (Private)


#### class `FTransformGizmoStyleCustomization`  
`class FTransformGizmoStyleCustomization : public FTransformGizmoEditorSettingsCustomizationBase`  
_L10-22_
- inherits: `FTransformGizmoEditorSettingsCustomizationBase`
- desc: Details panel customization for FTransformGizmoStyle, shown in the transform gizmo editor settings under the Style category.
- L14 _protected prototype_ `virtual FName GetTargetPropertyName() const override;`
- L15 _protected prototype_ `virtual FName GetTargetCategoryName() const override;`
- L16 _protected prototype_ `virtual const UScriptStruct* GetTargetStructType() const override;`
- L17 _protected prototype_ `virtual const void* GetDefaultValue() const override;`
- L21 _private member_ `FTransformGizmoStyle DefaultStyle;` — Default style settings used as the reference for reset-to-default.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Customizations/TransformGizmoEditorSettingsCustomization.h` (Private)


#### class `FTransformGizmoEditorSettingsCustomization`  
`class FTransformGizmoEditorSettingsCustomization : public IDetailCustomization`  
_L13-47_
- inherits: `IDetailCustomization`
- L17 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L19 _public prototype_ `FTransformGizmoEditorSettingsCustomization();`
- L21 _public prototype_ `virtual void CustomizeDetails(const TSharedPtr<IDetailLayoutBuilder>& InDetailBuilder) override;`
- L22 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L25 _private prototype_ `bool IsResetToDefaultVisible(TSharedPtr<IPropertyHandle> InPropertyHandle, const TFunction<const void*()>& InGetDefaultValueFunc);`
- L26 _private prototype_ `void OnResetToDefault(TSharedPtr<IPropertyHandle> InPropertyHandle, const TFunction<const void*()>& InGetDefaultValueFunc);`
- L29 _private prototype_ `TSharedRef<SWidget> GeneratePresetComboBoxContent();` — Generate the preset combobox widget.
- L32 _private prototype_ `FText GetActivePresetDisplayName() const;` — Returns the current display name for the active preset (or "Custom").
- L35 _private prototype_ `TSharedRef<IToolTip> GeneratePresetTooltip(const FTransformGizmoPreset& InPreset);` — Generates a rich tooltip widget showing a comparison table between current settings and a preset.
- L38 _private prototype_ `static void ApplyPreset(const FTransformGizmoPreset& InPreset);` — Apply the given preset values to the settings objects.
- L41 _private prototype_ `static void SaveConfigs();` — Calls SaveConfig on the common Settings objects.
- L44 _private member_ `TAttribute<bool> IsUsingNewGizmosAttribute;`
- L45 _private member_ `TAttribute<bool> IsUsingLegacyGizmosAttribute;`
- L46 _private member_ `TWeakPtr<IDetailLayoutBuilder> WeakDetailBuilder;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoDebugBase.h` (Private)


#### class `UGizmoDebugBase`  
`class UGizmoDebugBase : public UObject`  
_L78-105_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: This Debug object provides various Debug features for an FGizmoDebugObjectVariant, as specified by GetSupportedClass,
- L83 _public prototype_ `UGizmoDebugBase();`
- L86 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const PURE_VIRTUAL(UGizmoElementDebugBase::GetSupportedClass, return { };);` — The supported Class (specified in FGizmoDebugObjectVariant).
- L89 _public prototype_ `virtual void Draw(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const;` — General Draw functionality. Override specialized functions where present (ie. DrawHitGeometry).
- L92 _public prototype_ `virtual void DrawCanvas(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const;` — General Draw functionality. Override specialized functions where present (ie. DrawHitGeometry).
- L95 _public prototype_ `virtual void DrawHitGeometry(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const PURE_VIRTUAL(UGizmoElementDebugBase::DrawHitGeometry, { });` — Draws hit-testing geometry for the given gizmo object. Must be implemented by subclasses.
- L99 _protected prototype_ `TObjectPtr<const UMaterialInterface> GetMaterial() const;` — Returns the translucent material used for debug geometry rendering.
- L104 _private member_ `TObjectPtr<UMaterialInterface> Material;` — `UPROPERTY()` — Translucent material instance used for rendering debug overlays.

#### class `UGizmoElementDebugBase`  
`class UGizmoElementDebugBase : public UGizmoDebugBase`  
_L109-132_
- reflection: `UCLASS(Transient, Abstract, MinimalAPI)`
- inherits: `UGizmoDebugBase`
- desc: Extends UGizmoDebugBase with UGizmoElement specific functionality.
- L115 _public prototype_ `virtual void Draw(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const override;` — General Draw functionality. Iterates element-specific debug drawing for this gizmo element.
- L118 _public prototype_ `virtual void DrawHitGeometry(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;` — Draws hit-testing geometry for this gizmo element.
- L122 _protected prototype_ `virtual void DrawElement(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const;` — Draws debug visualization for a single gizmo element.
- L125 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InObject, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const PURE_VIRTUAL(UGizmoElementDebugBase, { });` — Draws hit-testing geometry for a single gizmo element. Must be implemented by subclasses.
- L128 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const;` — Updates the render traversal state for the given element, applying its local transform. Returns true if the element should be rendered.
- L131 _protected prototype_ `virtual FLinearColor GetElementColor(const UGizmoElementBase* InElement) const;` — Returns the color for the element, based on its current state.

#### class `UGizmoElementGroupDebug`  
`class UGizmoElementGroupDebug : public UGizmoElementDebugBase`  
_L136-154_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- desc: Debug visualizer for UGizmoElementGroupBase elements. Iterates child elements and delegates drawing to their respective debug objects.
- L143 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;` — Returns UGizmoElementGroupBase as the supported class for this debug visualizer.
- L147 _protected prototype_ `virtual void DrawElement(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const override;` — Draws debug visualization for a single gizmo element. Iterates child elements and delegates to their debug objects.
- L150 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;` — Draws hit-testing geometry for a single gizmo element. Iterates child elements and delegates to their debug objects.
- L153 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;` — Updates the render traversal state for the given group element. Applies group-level transform before child rendering.

#### Free symbols / members of external scopes

- L17 _typedef_ `using FGizmoDebugObjectVariant = TVariant<const UGizmoElementBase*, const UInteractiveGizmo*>;` — Variant type that can hold either a gizmo element or an interactive gizmo, used as input to debug draw routines.
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L21 _namespace_ `namespace Private` (scope `UE::Editor::InteractiveToolsFramework`)
- L33 _function_ `const DerivedType* GetVariantAs(const FGizmoDebugObjectVariant& InObject)` (scope `UE::Editor::InteractiveToolsFramework::Private`)
- L35 _typedef_ `using DecayedStoredType = std::decay_t<StoredType>;` (scope `UE::Editor::InteractiveToolsFramework::Private::GetVariantAs`)
- L36 _typedef_ `using DecayedDerivedType = std::decay_t<DerivedType>;` (scope `UE::Editor::InteractiveToolsFramework::Private::GetVariantAs`)
- L56 _namespace_ `namespace Internal` (scope `UE::Editor::InteractiveToolsFramework`)
- L60 _function_ `template <class GizmoElementType UE_REQUIRES(std::is_base_of_v<UGizmoElementBase, GizmoElementType>)> const GizmoElementType* GetVariantAsGizmoElement(const FGizmoDebugObjectVariant& InObject)` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Extracts a gizmo element of the specified type from the variant. Returns nullptr on type mismatch.
- L67 _function_ `template <class GizmoType UE_REQUIRES(std::is_base_of_v<UInteractiveGizmo, GizmoType>)> const GizmoType* GetVariantAsGizmo(const FGizmoDebugObjectVariant& InObject)` (scope `UE::Editor::InteractiveToolsFramework::Internal`) — Extracts an interactive gizmo of the specified type from the variant. Returns nullptr on type mismatch.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoDebugProvider.h` (Private)


#### class `UGizmoDebugProvider`  
`class UGizmoDebugProvider : public UObject`  
_L19-56_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- desc: Provides various Debug functionality for Gizmo Elements & Gizmos
- L28 _public prototype_ `void Setup();` — Discovers and registers all available UGizmoDebugBase subclasses. Must be called before any Draw methods.
- L31 _public prototype_ `void Draw(const FGizmoDebugObjectVariant& InObject, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const;` — Draws debug visualizations for the given gizmo object using the appropriate registered debug handler.
- L34 _public prototype_ `void DrawCanvas(const FGizmoDebugObjectVariant& InObject, FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const;` — Draws canvas-based (2D) debug visualizations for the given gizmo object.
- L37 _public prototype_ `void DrawHitGeometry(const FGizmoDebugObjectVariant& InObject, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const;` — Draws hit-testing geometry visualization for the given gizmo object.
- L41 _private prototype_ `TSubclassOf<UObject> GetDebugObjectSuperClass(const FGizmoDebugObjectVariant& InObject) const;` — Returns the base UObject class stored in the variant (UGizmoElementBase or UInteractiveGizmo).
- L44 _private prototype_ `TSubclassOf<UObject> GetDebugObjectClass(const FGizmoDebugObjectVariant& InObject) const;` — Returns the actual UObject class of the object stored in the variant.
- L47 _private prototype_ `bool GetDebugObjectFor(const FGizmoDebugObjectVariant& InObject, TObjectPtr<const UGizmoDebugBase>& OutDebugObject) const;` — Looks up or creates the appropriate debug handler for the given variant. Returns true if found.
- L52 _private member_ `mutable TMap<TSubclassOf<UObject>, TObjectPtr<const UGizmoDebugBase>> DebugObjects;` — `UPROPERTY()` — Cache mapping UObject classes to their corresponding debug handler instances. Populated lazily.
- L55 _private member_ `static constexpr float HitGeometryOpacity = 0.15f;` — Default opacity used when rendering hit-testing geometry overlays.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementArrowDebug.h` (Private)


#### class `UGizmoElementArrowDebug`  
`class UGizmoElementArrowDebug : public UGizmoElementGroupDebug`  
_L20-31_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupDebug`
- L26 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L29 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L30 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementArrowHeadDebug.h` (Private)


#### class `UGizmoElementArrowHeadDebug`  
`class UGizmoElementArrowHeadDebug : public UGizmoElementGroupDebug`  
_L20-29_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupDebug`
- L26 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L27 _public prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L28 _public prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementBoxDebug.h` (Private)


#### class `UGizmoElementBoxDebug`  
`class UGizmoElementBoxDebug : public UGizmoElementDebugBase`  
_L16-27_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- L22 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L26 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementCircleDebug.h` (Private)


#### class `UGizmoElementCircleDebug`  
`class UGizmoElementCircleDebug : public UGizmoElementDebugBase`  
_L16-27_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- L22 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L26 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementConeDebug.h` (Private)


#### class `UGizmoElementConeDebug`  
`class UGizmoElementConeDebug : public UGizmoElementDebugBase`  
_L16-27_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- L22 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L26 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementCylinderDebug.h` (Private)


#### class `UGizmoElementCylinderDebug`  
`class UGizmoElementCylinderDebug : public UGizmoElementDebugBase`  
_L16-27_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- L22 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L26 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementGimbalDebug.h` (Private)


#### class `UGizmoElementGimbalDebug`  
`class UGizmoElementGimbalDebug : public UGizmoElementGroupDebug`  
_L20-30_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupDebug`
- L26 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L29 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementRectangleDebug.h` (Private)


#### class `UGizmoElementRectangleDebug`  
`class UGizmoElementRectangleDebug : public UGizmoElementDebugBase`  
_L16-27_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- L22 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L26 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementSphereDebug.h` (Private)


#### class `UGizmoElementSphereDebug`  
`class UGizmoElementSphereDebug : public UGizmoElementDebugBase`  
_L16-27_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- L22 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L26 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/GizmoElementTorusDebug.h` (Private)


#### class `UGizmoElementTorusDebug`  
`class UGizmoElementTorusDebug : public UGizmoElementDebugBase`  
_L16-27_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementDebugBase`
- L22 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _protected prototype_ `virtual void DrawElementHitGeometry(const UGizmoElementBase* InElement, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5f)) const override;`
- L26 _protected prototype_ `virtual bool UpdateRenderState(const UGizmoElementBase* InElement, IToolsContextRenderAPI* InRenderAPI, const FVector& InLocalCenter, UGizmoElementBase::FRenderTraversalState& InOutRenderState) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Debug/TransformGizmoDebug.h` (Private)


#### class `UTransformGizmoDebug`  
`class UTransformGizmoDebug : public UGizmoDebugBase`  
_L19-28_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoDebugBase`
- desc: Provides Debug visualization for an owning TransformGizmo
- L24 _public prototype_ `virtual TSubclassOf<UObject> GetSupportedClass() const override;`
- L25 _public prototype_ `virtual void Draw(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const override;`
- L26 _public prototype_ `virtual void DrawCanvas(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FGizmoDebugSettings& InSettings) const override;`
- L27 _public prototype_ `virtual void DrawHitGeometry(const FGizmoDebugObjectVariant& InObject, const UGizmoDebugProvider* InDebugProvider, IToolsContextRenderAPI* InRenderAPI, const UGizmoElementBase::FRenderTraversalState& InRenderState, const FLinearColor& InColor = FLinearColor::Yellow.CopyWithNewOpacity(0.5)) const override;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/EditorGizmoElementHitMultiTarget.h` (Private)


#### class `UEditorGizmoElementHitMultiTarget`  
`class UEditorGizmoElementHitMultiTarget : public UGizmoElementHitMultiTarget`  
_L15-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGizmoElementHitMultiTarget`
- desc: An implementation of IGizmoClickMultiTarget with additional rules to determine valid interaction state transitions.
- L20 _public prototype_ `UEditorGizmoElementHitMultiTarget();`
- L23 _public prototype_ `virtual FInputRayHit IsHit(const FInputDeviceRay& ClickPos) const override;` — Performs a ray hit test against the gizmo element hierarchy, respecting priority hit testing when enabled.
- L26 _public prototype_ `virtual void UpdateHoverState(bool bHovering, uint32 InPartIdentifier) override;` — Updates the hover state for the given part, applying state transition rules.
- L29 _public prototype_ `virtual void UpdateInteractingState(bool bInteracting, uint32 InPartIdentifier) override;` — Updates the interacting (active drag) state for the given part, applying state transition rules.
- L32 _public prototype_ `virtual void UpdateSelectedState(bool bSelected, uint32 InPartIdentifier) override;` — Updates the selected state for the given part, applying state transition rules.
- L35 _public prototype_ `virtual void UpdateSubdueState(bool bSubdued, uint32 InPartIdentifier) override;` — Updates the subdued (dimmed) state for the given part, applying state transition rules.
- L38 _public prototype_ `void SetUsePriorityHitTesting(const bool bInUsePriorityHitTesting);` — Sets whether priority-based hit testing is used (closer/more specific elements take precedence).
- L41 _public prototype_ `bool GetUsePriorityHitTesting() const;` — Returns whether priority-based hit testing is enabled.
- L50 _public prototype_ `static UEditorGizmoElementHitMultiTarget* Construct( UGizmoElementBase* InGizmoElement, UGizmoViewContext* InGizmoViewContext, UObject* Outer = (UObject*)GetTransientPackage());` — Factory method to create and initialize a hit multi-target for the given gizmo element. @param InGizmoElement The root gizmo element to test hits against. @param InGizmoViewContext The view context providing camera/viewport information. @param Outer The outer object for the new instance.
- L57 _private prototype_ `bool IsPartSelected(uint32 InPartIdentifier) const;` — Returns whether the given part is currently in the selected state.
- L60 _private prototype_ `void SetPartSelected(uint32 InPartIdentifier, const bool bInSelected);` — Sets the selected state for the given part, updating the PartSelectionState bit array.
- L64 _private member_ `bool bUsePriorityHitTesting = true;` — `UPROPERTY(Getter = "GetUsePriorityHitTesting", Setter = "SetUsePriorityHitTesting")` — When true, uses priority-based hit testing where closer or more specific elements take precedence.
- L68 _private member_ `static constexpr bool bAllowMultiElementParts = true;` — Whether parts can be composed of multiple gizmo elements (always true for this implementation).
- L96 _private member_ `TArray<FStateRule, TFixedAllocator<static_cast<uint32>(EGizmoElementInteractionState::Max)>> StateRules;` — Rules governing valid state transitions for each interaction state.
- L99 _private member_ `TBitArray<> PartSelectionState;` — Per-part selection state, allowing interaction states to overlay (e.g. Hover can revert to Selected).

#### struct `UEditorGizmoElementHitMultiTarget::FStateRule`  
`struct FStateRule`  
_L71-93_
- desc: Defines a state transition rule for a single interaction state.
- L74 _public member_ `EGizmoElementInteractionState State;` — The interaction state this rule applies to.
- L77 _public member_ `bool bIsExclusive = false;` — If true, only the primary and secondary parts can hold this state simultaneously.
- L80 _public member_ `uint8 Priority = 0;` — Priority rank used to resolve conflicts when multiple states are available.
- L83 _public member_ `TArray<EGizmoElementInteractionState, TFixedAllocator<static_cast<uint32>(EGizmoElementInteractionState::Max)>> NextValidStates;` — Valid states that can follow this state in a transition.
- L86 _public member_ `TArray<EGizmoElementInteractionState, TFixedAllocator<static_cast<uint32>(EGizmoElementInteractionState::Max)>> RemoveStates;` — States removed from the same part when this state is applied (prevents priority-based state loss).
- L89 _public member_ `TArray<EGizmoElementInteractionState, TFixedAllocator<static_cast<uint32>(EGizmoElementInteractionState::Max)>> RemoveStatesOnOthers;` — States removed from all other parts when this state is applied.
- L92 _public member_ `TOptional<bool> bSelectFlagOverrideOnOthers;` — If set, overrides the selection flag of all other parts when this state is applied.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/EditorGizmoElementInterfaces.h` (Private)


#### class `UE::Editor::InteractiveToolsFramework::IPlaneProvider`  
`class IPlaneProvider`  
_L17-33_
- desc: Interface for gizmo elements that can construct an interaction plane. Used by axis and group elements to define the plane on which drag interactions are projected.
- L20 _public prototype_ `virtual ~IPlaneProvider() = default;`
- L26 _public prototype_ `virtual Geometry::FFrame3d MakePlane(const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const EAxisList::Type InAxisList = EAxisList::None) const = 0;` — Creates a plane from the given parameters, transformed into the provided coordinate space. The implementer *may* dictate and thus ignore the given AxisList. Implementers that require it should handle cases where an invalid value is passed to it.
- L32 _public prototype_ `virtual Geometry::FFrame3d MakePlane(const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const FRotationContext& InRotationContext, const EAxisList::Type InAxisList = EAxisList::None) const;` — Creates a plane from the given parameters, transformed into the provided coordinate space using the rotation context. The implementer *may* dictate and thus ignore the given AxisList. Implementers that require it should handle cases where an invalid value is passed to it.

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/EditorTRSGizmoBuilder.h` (Private)


#### class `UEditorTRSGizmoBuilder`  
`class UEditorTRSGizmoBuilder : public UEditorTransformGizmoBuilder`  
_L21-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorTransformGizmoBuilder`
- desc: Gizmo builder for the TRS (Translate/Rotate/Scale) transform gizmo. Creates and configures UEditorTRSGizmo instances based on the current scene selection.
- L29 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;` — Creates a new TRS gizmo instance configured for the current scene state.
- L32 _public prototype_ `virtual void UpdateGizmoForSelection(UInteractiveGizmo* Gizmo, const FToolBuilderState& SceneState) override;` — Updates the given TRS gizmo to reflect changes in the current scene selection.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementDashedLine.h` (Private)


#### class `UGizmoElementDashedLine`  
`class UGizmoElementDashedLine : public UGizmoElementLineBase`  
_L15-74_
- reflection: `UCLASS()`
- inherits: `UGizmoElementLineBase`
- desc: Simple object intended to be used as part of 3D Gizmos. Draws a dashed line based on parameters.
- L22 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L23 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L27 _public prototype_ `virtual void SetBase(FVector InBase);` — Set the world-space base (start) location of the line.
- L30 _public prototype_ `virtual FVector GetBase() const;` — Get the world-space base (start) location of the line.
- L33 _public prototype_ `virtual void SetLength(const float& InLength);` — Set the length of the line in world units.
- L36 _public prototype_ `virtual float GetLength() const;` — Get the length of the line in world units.
- L39 _public prototype_ `virtual void SetDirection(const FVector& InDirection);` — Set the direction of the line (unit vector).
- L42 _public prototype_ `virtual FVector GetDirection() const;` — Get the direction of the line.
- L49 _public prototype_ `virtual void SetDashParameters(const float InDashLength = 10.0f, const TOptional<float>& InGapLength = TOptional<float>());` — Set the dash pattern parameters. @param InDashLength Length of each dash segment in world units. @param InGapLength Length of each gap between dashes. Defaults to half of InDashLength if not specified.
- L52 _public prototype_ `virtual void GetDashParameters(float& OutDashLength, float& OutGapLength) const;` — Get the current dash and gap lengths.
- L57 _private member_ `FVector Base = FVector::ZeroVector;` — `UPROPERTY(Getter, Setter)` — World-space base (start) location of the line.
- L61 _private member_ `float Length = 100.0f;` — `UPROPERTY(Getter, Setter)` — Length of the line in world units.
- L65 _private member_ `FVector Direction = FVector(0.0f, 0.0f, 1.0f);` — `UPROPERTY(Getter, Setter)` — Direction of the line (unit vector).
- L69 _private member_ `float DashLength = 10.0f;` — `UPROPERTY()` — Length of each dash segment in world units.
- L73 _private member_ `float DashGapLength = 5.0f;` — `UPROPERTY()` — Length of each gap between dashes in world units.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementRotateAxis.h` (Private)


#### class `UGizmoElementRotateAxis`  
`class UGizmoElementRotateAxis : public UGizmoElementGroupBase , public UE::Editor::InteractiveToolsFramework::IPlaneProvider`  
_L35-257_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase,UE::Editor::InteractiveToolsFramework::IPlaneProvider`
- desc: Combines the visual elements of a single rotation axis: a torus ring handle, a delta arc showing the rotation angle, an origin indicator, a cursor-to-origin line, and a value label shown during interaction. Also implements IPlaneProvider to define the interaction plane for rotation projection.
- L80 _public prototype_ `UGizmoElementRotateAxis();`
- L82 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L83 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L85 _public prototype_ `virtual void SetViewAlignType(EGizmoElementViewAlignType InViewAlignType) override;`
- L86 _public prototype_ `virtual void SetViewAlignNormal(FVector InAxis) override;`
- L87 _public prototype_ `virtual void SetViewAlignAxis(FVector InAxis) override;`
- L90 _public prototype_ `const FGizmoElementRotateAxisStyle& GetStyle() const;` — Returns the current visual style for this rotation axis element.
- L93 _public prototype_ `void SetStyle(const FGizmoElementRotateAxisStyle& InStyle);` — Sets and applies the given Style.
- L97 _public prototype_ `virtual UE::Geometry::FFrame3d MakePlane( const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const EAxisList::Type InAxisList = EAxisList::None) const override;` — Creates the interaction plane for this rotation axis, transformed into the provided coordinate space.
- L104 _public prototype_ `virtual UE::Geometry::FFrame3d MakePlane( const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const FRotationContext& InRotationContext, const EAxisList::Type InAxisList = EAxisList::None) const override;` — Creates the interaction plane using the rotation context for gimbal-aware coordinate space transformation.
- L113 _public prototype_ `void DrawDebug(IToolsContextRenderAPI* RenderAPI, const FGizmoDebugSettings& InSettings);` — Renders various debug visualizations, if enabled.
- L116 _public prototype_ `void SetGizmoViewContext(UGizmoViewContext* InGizmoViewContext);` — Sets the Gizmo view context, needed for screen space interactions
- L120 _public prototype_ `void SetWidgetHost(IToolkitHost* const InWidgetHost);` — Sets the host to add/remove a widget to. Currently, this is a Toolkit host, but it could be abstracted to an ISlateWidgetHost (see IEditorViewportClientProxy).
- L129 _public prototype_ `void Setup( const uint32 InPartId, const EAxisList::Type InAxis, const FGizmoElementRotateAxisStyle& InStyle);` — Initialize the rotation axis element with a part identifier, axis, and visual style. Must be called before the element can render or receive interactions. @param InPartId Unique identifier for hit-testing this axis. @param InAxis The axis this element represents (e.g. EAxisList::X). @param InStyle Visual style parameters for the axis.
- L135 _public prototype_ `void UpdateElements();` — Rebuilds child elements to reflect the current style. Call after modifying style properties.
- L138 _public prototype_ `void BeginDelta(const FDeltaParameters& InParameters);` — Begin a delta interaction, recording the start state.
- L141 _public prototype_ `void UpdateDelta(const FDeltaParameters& InParameters);` — Update the delta arc and value label with the current angle and cursor location.
- L144 _public prototype_ `void EndDelta();` — End the current delta interaction and hide delta visuals.
- L149 _private member_ `FGizmoElementRotateAxisStyle Style;` — `UPROPERTY(Getter, Setter)` — Style contains various uniform and varying properties that affect the appearance of this gizmo element.
- L153 _private member_ `TObjectPtr<UGizmoElementTorus> AxisRingElement;` — `UPROPERTY()` — Rotate Axis.
- L157 _private member_ `TObjectPtr<UGizmoElementArc> DeltaArcElement;` — `UPROPERTY()` — Arc element that visualizes the rotation delta angle during interaction.
- L161 _private member_ `TObjectPtr<UGizmoElementValueWidget> DeltaWidgetElement;` — `UPROPERTY()` — Widget element that displays the numeric rotation angle value during interaction.
- L165 _private member_ `TObjectPtr<UGizmoElementCircle> OriginElement;` — `UPROPERTY()` — Circle element drawn at the gizmo origin during rotation interaction.
- L169 _private member_ `TObjectPtr<UGizmoElementDashedLine> OriginToCursorLineElement;` — `UPROPERTY()` — Dashed line element drawn from the origin to the cursor during rotation interaction.
- L173 _private prototype_ `void ApplyStyle();` — Applies the current Style properties to all child visual elements.
- L179 _private prototype_ `bool UpdateDeltaRenderState(IToolsContextRenderAPI* RenderAPI, const FVector& InLocalOrigin, FRenderTraversalState& InOutRenderState);` — Updates render state for delta elements during render traversal, using the start transform rather than the current. @return View-dependent visibility; true if this element is visible in the current view.
- L183 _private member_ `std::atomic_bool bIsValid = false;` — Flag indicating element validity - generally true after Setup is called.
- L187 _private member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext;` — `UPROPERTY(Setter)` — Gizmo view context, needed for screen space interactions
- L190 _private member_ `EAxisList::Type Axis;` — The represented axis (e.g. EAxisList::X).
- L192 _private member_ `int32 AxisIndex = 0;` — Index of the axis (0=X, 1=Y, 2=Z).
- L195 _private member_ `FVector NormalAxis;` — Normal direction of the rotation plane (axis of rotation).
- L198 _private member_ `FVector SideAxis;` — Side direction in the rotation plane, perpendicular to NormalAxis.
- L201 _private member_ `FVector UpAxis;` — Up direction in the rotation plane, perpendicular to both NormalAxis and SideAxis.
- L204 _private member_ `FNumberFormattingOptions TextNumberFormattingOptions;` — Formatting options for the delta angle label text.
- L231 _private member_ `FState StartState;` — State captured at the beginning of a rotation interaction.
- L233 _private member_ `FState CurrentState;` — State updated each frame during a rotation interaction.
- L236 _private member_ `bool bIsShowingDelta = false;` — Whether a delta interaction is currently active and delta visuals should be shown.
- L256 _private member_ `} DebugData;`

#### struct `UGizmoElementRotateAxis::FDeltaParameters`  
`struct FDeltaParameters`  
_L43-77_
- desc: Parameters shared between BeginDelta and UpdateDelta calls, describing the current rotation interaction state.
- L46 _public member_ `FTransform Transform = FTransform::Identity;` — The current world transform of the gizmo.
- L49 _public member_ `EToolContextCoordinateSystem CoordinateSystem = EToolContextCoordinateSystem::World;` — The active coordinate system (World, Local, etc.).
- L52 _public member_ `FRotationContext RotationContext = FRotationContext();` — Context for the rotation (e.g. gimbal state, accumulated rotation).
- L55 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L58 _public member_ `double Angle = 0.0;` — Accumulated rotation angle in radians from the start of the interaction.
- L61 _public member_ `int8 DisplaySign = 1;` — Display sign for the angle. Ensures clockwise visual matches clockwise input, even when the applied angle is negated (e.g. for X, Y axes).
- L64 _public member_ `bool bIsIndirectManipulation = false;` — Whether this is an indirect manipulation (e.g. input field rather than drag).
- L67 _public member_ `bool bIsCursorInViewport = true;` — Whether the cursor is currently within the viewport (affects delta label visibility).
- L70 _public member_ `FVector CursorLocation = FVector::ZeroVector;` — World-space cursor location, used for origin-to-cursor line.
- L73 _public member_ `FVector2D CursorLocation2D = FVector2D::ZeroVector;` — Screen-space cursor location.
- L76 _public member_ `EAxisRotateMode::Type RotateMode = EAxisRotateMode::Type::Pull;` — The rotation interaction mode (Pull or Dial).

#### struct `UGizmoElementRotateAxis::FState`  
`struct FState`  
_L207-228_
- desc: Snapshot of rotation interaction state, captured at the start and updated each frame.
- L210 _public member_ `FTransform Transform;` — World transform of the gizmo at this point in the interaction.
- L212 _public member_ `FTransform RotatedTransform;` — World transform with the accumulated rotation applied.
- L214 _public member_ `FRotationContext RotationContext;` — Rotation context (e.g. gimbal state) at this point in the interaction.
- L216 _public member_ `double Angle = 0.0;` — Accumulated rotation angle in radians.
- L218 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the rotation plane.
- L220 _public member_ `bool bShowCursor = false;` — Whether to show the cursor-to-origin line and origin indicator.
- L222 _public member_ `int8 DisplaySign = 1;` — Display sign multiplier for the angle (accounts for axis direction).
- L225 _public prototype_ `void Initialize(const FDeltaParameters& InParameters, const int32 InAxisIndex);` — Initializes this state from the given delta parameters and axis index.
- L227 _public prototype_ `void Update(const FDeltaParameters& InParameters);` — Updates this state with new delta parameters.

#### struct `UGizmoElementRotateAxis::FGizmoDebugData`  
`struct FGizmoDebugData`  
_L239-256_
- desc: Debug data collected during interactions for optional debug visualization.
- L242 _public member_ `FTransform TransformStart;` — Gizmo transform at the start of the interaction.
- L245 _public member_ `FTransform LastRenderTransform = FTransform::Identity;` — Most recent transform used during rendering.
- L247 _public member_ `FTransform LastDeltaTransform = FTransform::Identity;` — Most recent transform used for delta element rendering.
- L250 _public member_ `FVector HitPointStart = FVector::ZeroVector;` — World-space hit point at the start of the interaction.
- L252 _public member_ `FVector HitPointCurrent = FVector::ZeroVector;` — World-space hit point at the current frame.
- L255 _public member_ `FVector CursorDirection;` — Direction from the origin toward the cursor in world space.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementRotateAxisSet.h` (Private)


#### struct `FGizmoElementRotateAxisStyleOverride`  
`struct FGizmoElementRotateAxisStyleOverride`  
_L15-37_
- reflection: `USTRUCT(MinimalAPI)`
- desc: This style contains optional per-axis overrides. FGizmoElementRotateAxisStyle is used for the shared style.
- L21 _public member_ `TOptional<FGizmoPerStateValueLinearColor> Colors;` — `UPROPERTY()` — The Axis color, usually Red for X, etc.
- L25 _public member_ `TOptional<FGizmoPerStateValueMaterialVariant> Materials;` — `UPROPERTY()` — Optional per-state material overrides for the axis.
- L29 _public member_ `TOptional<TObjectPtr<UMaterialInterface>> DeltaMaterial;` — `UPROPERTY()` — Optional override for the material used to render the rotation delta arc.
- L33 _public member_ `TOptional<TObjectPtr<UMaterialInterface>> VertexColorMaterial;` — `UPROPERTY()` — Optional override for the vertex-color material used for the axis.
- L36 _public prototype_ `void ApplyTo(FGizmoElementRotateAxisStyle& InOutStyle) const;` — Applies the overrides, if set, to the given Style.

#### class `UGizmoElementRotateAxisSet`  
`class UGizmoElementRotateAxisSet : public UGizmoElementGroupBase`  
_L41-139_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase`
- desc: Represents a set of rotate-axis elements used in gizmo rendering. Provides functionality for managing and rendering multiple axis components as a single entity.
- L61 _public prototype_ `void DrawDebug(IToolsContextRenderAPI* RenderAPI, const FGizmoDebugSettings& InSettings, const uint32 InPartId = 0);` — Renders various debug visualizations, if enabled.
- L65 _public prototype_ `void SetWidgetHost(IToolkitHost* const InWidgetHost);` — Sets the host to add/remove a widget to. Currently, this is a Toolkit host, but it could be abstracted to an ISlateWidgetHost (see IEditorViewportClientProxy).
- L68 _public prototype_ `void SetAxisEnabled(const EAxisList::Type InAxisListToEnable);` — Enables the elements specified in the provided AxisList, and disables those that aren't.
- L71 _public prototype_ `const FGizmoElementRotateAxisStyle& GetStyle() const;` — Returns the current shared style used by this rotation axis set.
- L74 _public prototype_ `void SetStyle( const FGizmoElementRotateAxisStyle& InStyle, const FGizmoElementRotateAxisStyleOverride& InAxisStyleX, const FGizmoElementRotateAxisStyleOverride& InAxisStyleY, const FGizmoElementRotateAxisStyleOverride& InAxisStyleZ);` — Sets and applies the given Style + Overrides.
- L88 _public prototype_ `void Setup( const EAxisList::Type InAxisList, const FGizmoElementRotateAxisStyle& InStyle, const FAxisParameters& InAxisX, const FAxisParameters& InAxisY, const FAxisParameters& InAxisZ);` — Initialize the rotation axis set with all three axis elements. @param InAxisList Which axes to initially enable. @param InStyle Shared visual style for all rotation axis elements. @param InAxisX Parameters for the X axis element. @param InAxisY Parameters for the Y axis element. @param InAxisZ Parameters for the Z axis element.
- L96 _public prototype_ `void UpdateElements();` — Rebuilds child elements to reflect the current style. Call after modifying style properties.
- L99 _public prototype_ `UGizmoElementRotateAxis* GetAxisElement(const EAxis::Type InAxis) const;` — Get the rotation axis element for the given single axis (X, Y, or Z). Returns nullptr if not set up.
- L103 _private prototype_ `void ForEachAxisElement(const TFunctionRef<void(UGizmoElementRotateAxis* InElement)>& InFunc);` — Invokes the given function on each axis element (X, Y, Z).
- L106 _private prototype_ `void ApplyStyle();` — Applies the current style and per-axis overrides to all axis elements.
- L110 _private member_ `std::atomic_bool bIsValid = false;` — Flag indicating element validity - generally true after Setup is called.
- L114 _private member_ `FGizmoElementRotateAxisStyle Style;` — `UPROPERTY()` — Style contains various uniform and varying properties that affect the appearance of this gizmo element.
- L118 _private member_ `FGizmoElementRotateAxisStyleOverride StyleX;` — `UPROPERTY()` — Optional overrides for the X axis.
- L122 _private member_ `FGizmoElementRotateAxisStyleOverride StyleY;` — `UPROPERTY()` — Optional overrides for the Y axis.
- L126 _private member_ `FGizmoElementRotateAxisStyleOverride StyleZ;` — `UPROPERTY()` — Optional overrides for the Z axis.
- L130 _private member_ `TObjectPtr<UGizmoElementRotateAxis> AxisElementX;` — `UPROPERTY()` — X axis rotation element.
- L134 _private member_ `TObjectPtr<UGizmoElementRotateAxis> AxisElementY;` — `UPROPERTY()` — Y axis rotation element.
- L138 _private member_ `TObjectPtr<UGizmoElementRotateAxis> AxisElementZ;` — `UPROPERTY()` — Z axis rotation element.

#### struct `UGizmoElementRotateAxisSet::FAxisParameters`  
`struct FAxisParameters`  
_L47-57_
- desc: Per-Axis parameters.
- L50 _public member_ `uint32 PartId;` — Hit-test part identifier for this axis element.
- L53 _public member_ `EAxisList::Type Axis;` — Which axis (X, Y, or Z) this element represents.
- L56 _public member_ `FGizmoElementRotateAxisStyleOverride StyleOverride;` — Per-axis style overrides applied on top of the shared style.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementScaleAxis.h` (Private)


#### class `UGizmoElementScaleAxis`  
`class UGizmoElementScaleAxis : public UGizmoElementGroupBase , public UE::Editor::InteractiveToolsFramework::IPlaneProvider`  
_L37-269_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase,UE::Editor::InteractiveToolsFramework::IPlaneProvider`
- desc: Combines the visual elements of a single scale axis: a cylinder body, an arrow head handle, a delta line, and a value label shown during interaction. Also implements IPlaneProvider to define the interaction plane for drag projection.
- L88 _public prototype_ `UGizmoElementScaleAxis();`
- L91 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L92 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L96 _public prototype_ `void DrawDebug(IToolsContextRenderAPI* RenderAPI, const FGizmoDebugSettings& InSettings);` — Renders various debug visualizations, if enabled.
- L100 _public prototype_ `void SetWidgetHost(IToolkitHost* const InWidgetHost);` — Sets the host to add/remove a widget to. Currently, this is a Toolkit host, but it could be abstracted to an ISlateWidgetHost (see IEditorViewportClientProxy).
- L103 _public prototype_ `const FGizmoElementScaleAxisStyle& GetStyle() const;` — Returns the current visual style for this scale axis element.
- L106 _public prototype_ `void SetStyle(const FGizmoElementScaleAxisStyle& InStyle);` — Sets and applies the given Style.
- L109 _public prototype_ `const FGizmoElementScaleInteraction& GetInteraction() const;` — Returns the current interaction options for this scale axis element.
- L112 _public prototype_ `void SetInteraction(const FGizmoElementScaleInteraction& InInteraction);` — Sets and applies the given Interaction options.
- L116 _public prototype_ `virtual UE::Geometry::FFrame3d MakePlane(const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const EAxisList::Type InAxisList) const override;` — Creates the interaction plane for this scale axis, transformed into the provided coordinate space.
- L126 _public prototype_ `void Setup( const uint32 InPartId, const EAxisList::Type InAxis, const FGizmoElementScaleAxisStyle& InStyle);` — Initialize the scale axis element with a part identifier, axis, and visual style. Must be called before the element can render or receive interactions. @param InPartId Unique identifier for hit-testing this axis. @param InAxis The axis this element represents (e.g. EAxisList::X). @param InStyle Visual style parameters for the axis.
- L132 _public prototype_ `void UpdateElements();` — Rebuilds child elements to reflect the current style. Call after modifying style properties.
- L135 _public prototype_ `void BeginDelta(const FDeltaParameters& InParameters);` — Begin a delta interaction, recording the start state.
- L138 _public prototype_ `void UpdateDelta(const FDeltaParameters& InParameters);` — Update the delta visualization with the current scale factor.
- L141 _public prototype_ `void EndDelta();` — End the current delta interaction and hide delta visuals.
- L146 _private member_ `FGizmoElementScaleAxisStyle Style;` — `UPROPERTY()` — Style contains various uniform and varying properties that affect the appearance of this gizmo element.
- L150 _private member_ `FGizmoElementScaleInteraction Interaction;` — `UPROPERTY()` — Interaction options controlling how this scale axis responds to user input.
- L154 _private member_ `TObjectPtr<UGizmoElementCylinder> ArrowBodyElement;` — `UPROPERTY()` — Scale Axis Body.
- L158 _private member_ `TObjectPtr<UGizmoElementArrowHead> ArrowHeadElement;` — `UPROPERTY()` — Scale Axis Head.
- L162 _private member_ `TObjectPtr<UGizmoElementCylinder> DeltaLineElement;` — `UPROPERTY()` — Dashed Line.
- L166 _private member_ `TObjectPtr<UGizmoElementValueWidget> DeltaWidgetElement;` — `UPROPERTY()` — Widget that displays the numeric scale value label during interaction.
- L170 _private prototype_ `void ApplyStyle();` — Applies the current Style to all child visual elements.
- L172 _private prototype_ `void ApplyInteraction();` — Applies the current Interaction options to all child elements.
- L175 _private prototype_ `FVector GetHeadCenter(const float InPixelToWorldScale = 1.0f) const;` — Returns the world-space center of the arrow head, optionally scaled by a pixel-to-world factor.
- L178 _private prototype_ `float GetAxisLength() const;` — Returns the visual length of the axis body (excluding offset from center).
- L181 _private prototype_ `float GetTotalAxisLength() const;` — Get the axis length with offset-from-center.
- L184 _private prototype_ `float GetDeltaAxisLength(const FTransform& InTransform) const;` — Returns the length of the delta line for the given transform, accounting for pixel-to-world scaling.
- L187 _private prototype_ `FVector GetSignedDeltaDirection() const;` — Returns the axis direction vector, signed according to the current delta direction.
- L193 _private prototype_ `bool UpdateDeltaRenderState(IToolsContextRenderAPI* RenderAPI, const FVector& InLocalOrigin, FRenderTraversalState& InOutRenderState);` — Updates the render state for delta elements during render traversal, using the start transform rather than the current. @return View-dependent visibility; true if this element is visible in the current view.
- L197 _private member_ `std::atomic_bool bIsValid = false;` — Flag indicating element validity - generally true after Setup is called.
- L200 _private member_ `EAxisList::Type Axis = EAxisList::None;` — The axis this element represents (e.g. EAxisList::X).
- L203 _private member_ `FVector NormalDirection = FVector::ForwardVector;` — Normal (forward) direction along the axis in local space.
- L206 _private member_ `FVector UpDirection = FVector::UpVector;` — Up direction perpendicular to the axis, used for interaction plane construction.
- L209 _private member_ `FVector SideDirection = FVector::RightVector;` — Side direction perpendicular to the axis, used for interaction plane construction.
- L212 _private member_ `FNumberFormattingOptions TextNumberFormattingOptions;` — Formatting options for the delta value label text.
- L252 _private member_ `FState StartState;` — Captured state at the beginning of the current scale interaction.
- L255 _private member_ `FState CurrentState;` — State updated each frame during the current scale interaction.
- L258 _private member_ `bool bIsShowingDelta = false;` — Whether delta visuals (line and value label) are currently being displayed.
- L268 _private member_ `} DebugData;`

#### struct `UGizmoElementScaleAxis::FDeltaParameters`  
`struct FDeltaParameters`  
_L48-85_
- desc: Parameters shared between BeginDelta and UpdateDelta calls, describing the current scale interaction state.
- L51 _public member_ `FTransform Transform = FTransform::Identity;` — The current world transform of the gizmo.
- L54 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — Screen-space location of the gizmo origin, used for label placement.
- L57 _public member_ `EToolContextCoordinateSystem CoordinateSystem = EToolContextCoordinateSystem::World;` — The active coordinate system (World, Local, etc.).
- L60 _public member_ `EGizmoTransformScaleType ScaleType = EGizmoTransformScaleType::PercentageBased;` — The scale type being used for the interaction.
- L63 _public member_ `FVector AxisDirection = FVector::ZeroVector;` — Direction of the scale axis in the current coordinate system.
- L66 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L69 _public member_ `FVector PlaneIntersectionPoint = FVector::ZeroVector;` — World-space point where the interaction ray intersects the plane.
- L72 _public member_ `double Scale = 1.0;` — Current scale factor (1.0 = no change).
- L75 _public member_ `bool bIsCursorInViewport = true;` — Whether the cursor is currently within the viewport (affects delta label visibility).
- L78 _public member_ `bool bIsIndirectInteraction = false;` — Whether this is an indirect interaction (e.g. input field rather than drag).
- L81 _public member_ `bool bIsTrustworthy = true;` — Whether the scale value is reliable (false when the cursor is near the gizmo origin, causing instability).
- L84 _public member_ `EAxisList::Type AxisList = EAxisList::None;` — The axis or axes being scaled.

#### struct `UGizmoElementScaleAxis::FState`  
`struct FState`  
_L215-249_
- desc: Snapshot of the interaction state at a point in time, used to track start and current states during a scale drag.
- L218 _public member_ `FTransform Transform = FTransform::Identity;` — The world transform of the gizmo at this point in the interaction.
- L221 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — The gizmo origin projected into 2D screen-space.
- L224 _public member_ `double DeltaRadius = 0.0;` — Unsigned distance of the delta from the axis origin (always positive).
- L227 _public member_ `int8 DeltaSign = 1;` — Sign of the delta relative to the start of the operation/arrow head direction.
- L230 _public member_ `int8 AxisSign = 1;` — Sign of the axis relative to the actual object origin.
- L233 _public member_ `bool bIsSingleAxis = false;` — Whether the interaction is constrained to a single axis (as opposed to uniform/planar scale).
- L236 _public member_ `float DPIScale = 1.0f;` — The current DPI Scale
- L239 _public member_ `FVector PlaneIntersectionPoint = FVector::ZeroVector;` — World-space point where the interaction ray intersects the drag plane.
- L242 _public prototype_ `void Initialize(const FDeltaParameters& InParameters);` — Initializes the state from the given delta parameters at the start of an interaction.
- L245 _public prototype_ `void Update(const FDeltaParameters& InParameters);` — Updates the state from the given delta parameters during an ongoing interaction.
- L248 _public prototype_ `void Reset();` — Resets all members to their default values.

#### struct `UGizmoElementScaleAxis::FGizmoDebugData`  
`struct FGizmoDebugData`  
_L261-268_
- desc: Debug visualization data collected during interactions.
- L264 _public member_ `bool bIsEditing = false;` — Determines whether certain data is displayed, ie. drag operation deltas.
- L267 _public member_ `FTransform TransformStart;` — The gizmo transform captured at the start of the current drag operation, used for debug rendering.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementScaleGroup.h` (Private)


#### struct `FGizmoElementScaleAxisStyleOverride`  
`struct FGizmoElementScaleAxisStyleOverride`  
_L20-38_
- reflection: `USTRUCT(MinimalAPI)`
- desc: This style contains optional per-axis overrides. FGizmoElementScaleAxisStyle is used for the shared style.
- L26 _public member_ `TOptional<FGizmoPerStateValueLinearColor> Colors;` — `UPROPERTY()` — The Axis color, usually Red for X, etc.
- L30 _public member_ `TOptional<FGizmoPerStateValueMaterialVariant> Materials;` — `UPROPERTY()` — Optional override for the per-state materials.
- L34 _public member_ `TOptional<TObjectPtr<UMaterialInterface>> VertexColorMaterial;` — `UPROPERTY()` — Optional override for the vertex color material.
- L37 _public prototype_ `void ApplyTo(FGizmoElementScaleAxisStyle& InOutStyle) const;` — Applies the overrides, if set, to the given Style.

#### struct `FGizmoElementScalePlanarStyleOverride`  
`struct FGizmoElementScalePlanarStyleOverride`  
_L42-60_
- reflection: `USTRUCT(MinimalAPI)`
- desc: This style contains optional per-planar overrides. FGizmoElementScalePlanarStyle is used for the shared style.
- L48 _public member_ `TOptional<FGizmoPerStateValueLinearColor> Colors;` — `UPROPERTY()` — The Plane color, usually Red for YZ, etc.
- L52 _public member_ `TOptional<FGizmoPerStateValueMaterialVariant> Materials;` — `UPROPERTY()` — Optional override for the per-state materials.
- L56 _public member_ `TOptional<TObjectPtr<UMaterialInterface>> VertexColorMaterial;` — `UPROPERTY()` — Optional override for the vertex color material.
- L59 _public prototype_ `void ApplyTo(FGizmoElementScalePlanarStyle& InOutStyle) const;` — Applies the overrides, if set, to the given Style.

#### class `UGizmoElementScaleGroup`  
`class UGizmoElementScaleGroup : public UGizmoElementGroupBase , public UE::Editor::InteractiveToolsFramework::IPlaneProvider`  
_L68-350_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase,UE::Editor::InteractiveToolsFramework::IPlaneProvider`
- desc: Container for all scale gizmo elements: per-axis handles (X, Y, Z), planar handles (XY, YZ, XZ), and the uniform screen-space handle. Manages style propagation, interaction options, axis enable/disable, and delta visualization across all children.
- L137 _public prototype_ `void DrawDebug(IToolsContextRenderAPI* RenderAPI, const FGizmoDebugSettings& InSettings, const uint32 InPartId = 0);` — Renders various debug visualizations, if enabled.
- L141 _public prototype_ `void SetWidgetHost(IToolkitHost* const InWidgetHost);` — Sets the host to add/remove a widget to. Currently, this is a Toolkit host, but it could be abstracted to an ISlateWidgetHost (see IEditorViewportClientProxy).
- L144 _public prototype_ `void SetGetCurrentSnappingSettingsFunction(const TFunction<FToolContextSnappingConfiguration()>& InFunction);` — Sets a function that provides the current snapping settings to use during interaction.
- L147 _public prototype_ `void SetAxisEnabled(const EAxisList::Type InAxisListToEnable);` — Enables the elements specified in the provided AxisList and disables those that aren't.
- L150 _public prototype_ `void SetPlanarEnabled(const EAxisList::Type InAxisListToEnable);` — Enables the elements specified in the provided AxisList and disables those that aren't.
- L153 _public prototype_ `void SetUniformEnabled(const bool bInEnable);` — Enables or disables the uniform screen-space scale element.
- L156 _public prototype_ `const FGizmoElementScaleStyle& GetStyle() const;` — Returns the current shared scale style.
- L159 _public prototype_ `void SetStyle( const FGizmoElementScaleStyle& InStyle, const FGizmoElementScaleAxisStyleOverride& InAxisStyleX, const FGizmoElementScaleAxisStyleOverride& InAxisStyleY, const FGizmoElementScaleAxisStyleOverride& InAxisStyleZ, const FGizmoElementScalePlanarStyleOverride& InPlanarStyleXY, const FGizmoElementScalePlanarStyleOverride& InPlanarStyleYZ, const FGizmoElementScalePlanarStyleOverride& InPlanarStyleXZ);` — Sets and applies the given Style + Overrides.
- L169 _public prototype_ `const FGizmoElementScaleInteraction& GetInteraction() const;` — Returns the current interaction options.
- L172 _public prototype_ `void SetInteraction(const FGizmoElementScaleInteraction& InInteraction);` — Sets and applies the given Interaction options.
- L176 _public prototype_ `virtual UE::Geometry::FFrame3d MakePlane(const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const EAxisList::Type InAxisList) const override;` — Creates the interaction plane for the active scale axis or plane, transformed into the provided coordinate space.
- L192 _public prototype_ `void Setup( const uint32 InPartId, const FGizmoElementScaleStyle& InStyle, const FAxisParameters& InAxisX, const FAxisParameters& InAxisY, const FAxisParameters& InAxisZ, const FPlanarParameters& InPlanarXY, const FPlanarParameters& InPlanarYZ, const FPlanarParameters& InPlanarXZ, const uint32 InUniformPartId);` — Initialize the scale group with all axis, planar, and uniform elements. Must be called before the group can render or receive interactions. @param InPartId Base part identifier for the group. @param InStyle Shared visual style for all scale elements. @param InAxisX Parameters for the X axis element. @param InAxisY Parameters for the Y axis element. @param InAxisZ Parameters for the Z axis element. @param InPlanarXY Parameters for the XY planar element. @param InPlanarYZ Parameters for the YZ planar element. @param InPlanarXZ Parameters for the XZ planar element. @param InUniformPartId Part identifier for the uniform screen-space element.
- L204 _public prototype_ `void UpdateElements();` — Rebuilds child elements to reflect the current style. Call after modifying style properties.
- L207 _public prototype_ `UGizmoElementScaleAxis* GetAxisElement(const EAxis::Type InAxis) const;` — Get the scale axis element for the given single axis (X, Y, or Z). Returns nullptr if not set up.
- L210 _public prototype_ `UGizmoElementBox* GetPlanarElement(const EAxisList::Type InAxis) const;` — Get the planar element for the given axis pair (XY, YZ, or XZ). Returns nullptr if not set up.
- L213 _public prototype_ `void BeginDelta(const FDeltaParameters& InParameters);` — Begin a delta interaction, recording the start state. Propagates to the active axis element.
- L216 _public prototype_ `void UpdateDelta(const FDeltaParameters& InParameters);` — Update the delta visualization with the current scale factors.
- L219 _public prototype_ `void EndDelta();` — End the current delta interaction and hide delta visuals.
- L223 _private prototype_ `void ForEachAxisElement(const TFunctionRef<void(UGizmoElementScaleAxis* InElement)>& InFunc);` — Invokes the given function for each axis element (X, Y, Z).
- L226 _private prototype_ `void ForEachAxisElementByList(const TFunctionRef<void(UGizmoElementScaleAxis* InElement, const EAxis::Type InAxis)>& InFunc, const EAxisList::Type InAxisList) const;` — Invokes the given function for each axis element whose axis is included in InAxisList.
- L229 _private prototype_ `void ApplyStyle();` — Applies the current style and per-axis/planar overrides to all child elements.
- L231 _private prototype_ `void ApplyInteraction();` — Applies the current interaction options to all child elements.
- L234 _private prototype_ `void ApplyGetCurrentSnappingSettingsFunction();` — Applies and propagates the current GetCurrentSnappingSettingsFunction, if set.
- L238 _private member_ `std::atomic_bool bIsValid = false;` — Whether this group has been initialized via Setup().
- L242 _private member_ `FGizmoElementScaleStyle Style;` — `UPROPERTY()` — Style contains various uniform and varying properties that affect the appearance of this gizmo element.
- L246 _private member_ `FGizmoElementScaleInteraction Interaction;` — `UPROPERTY()` — Interaction options controlling how scale handles behave during user input.
- L250 _private member_ `FGizmoElementScaleAxisStyleOverride AxisXStyle;` — `UPROPERTY()` — Optional overrides for the X axis.
- L254 _private member_ `FGizmoElementScaleAxisStyleOverride AxisYStyle;` — `UPROPERTY()` — Optional overrides for the Y axis.
- L258 _private member_ `FGizmoElementScaleAxisStyleOverride AxisZStyle;` — `UPROPERTY()` — Optional overrides for the Z axis.
- L262 _private member_ `FGizmoElementScalePlanarStyleOverride PlanarXYStyle;` — `UPROPERTY()` — Optional overrides for the XY plane.
- L266 _private member_ `FGizmoElementScalePlanarStyleOverride PlanarYZStyle;` — `UPROPERTY()` — Optional overrides for the YZ plane.
- L270 _private member_ `FGizmoElementScalePlanarStyleOverride PlanarXZStyle;` — `UPROPERTY()` — Optional overrides for the XZ plane.
- L274 _private member_ `TObjectPtr<UGizmoElementScaleAxis> AxisXElement;` — `UPROPERTY()` — Axis X element.
- L278 _private member_ `TObjectPtr<UGizmoElementScaleAxis> AxisYElement;` — `UPROPERTY()` — Axis Y element.
- L282 _private member_ `TObjectPtr<UGizmoElementScaleAxis> AxisZElement;` — `UPROPERTY()` — Axis Z element.
- L286 _private member_ `TObjectPtr<UGizmoElementBox> PlanarXYElement;` — `UPROPERTY()` — Planar XY element.
- L290 _private member_ `TObjectPtr<UGizmoElementBox> PlanarYZElement;` — `UPROPERTY()` — Planar YZ element.
- L294 _private member_ `TObjectPtr<UGizmoElementBox> PlanarXZElement;` — `UPROPERTY()` — Planar XZ element.
- L298 _private member_ `TObjectPtr<UGizmoElementBox> UniformElement;` — `UPROPERTY()` — Uniform element.
- L302 _private member_ `TObjectPtr<UGizmoElementSphere> UniformElementAlternate;` — `UPROPERTY()` — Uniform element.
- L305 _private member_ `TFunction<FToolContextSnappingConfiguration()> GetCurrentSnappingSettingsFunction = nullptr;` — Callback that provides the current snapping configuration for scale interactions.
- L343 _private member_ `FState StartState;` — State captured at the beginning of the current delta interaction.
- L346 _private member_ `FState CurrentState;` — State representing the most recent update of the current delta interaction.
- L349 _private member_ `bool bIsShowingDelta = false;` — Whether a delta visualization is currently being displayed.

#### struct `UGizmoElementScaleGroup::FAxisParameters`  
`struct FAxisParameters`  
_L76-86_
- desc: Per-Axis parameters.
- L79 _public member_ `uint32 PartId = 0;` — Part identifier for this axis element.
- L82 _public member_ `EAxisList::Type Axis = EAxisList::None;` — Which axis this element represents.
- L85 _public member_ `FGizmoElementScaleAxisStyleOverride StyleOverride;` — Optional style overrides specific to this axis.

#### struct `UGizmoElementScaleGroup::FPlanarParameters`  
`struct FPlanarParameters`  
_L89-99_
- desc: Per-Plane parameters.
- L92 _public member_ `uint32 PartId = 0;` — Part identifier for this planar element.
- L95 _public member_ `EAxisList::Type Axis = EAxisList::None;` — Which axis pair this planar element represents (e.g. XY, YZ, XZ).
- L98 _public member_ `FGizmoElementScalePlanarStyleOverride StyleOverride;` — Optional style overrides specific to this plane.

#### struct `UGizmoElementScaleGroup::FDeltaParameters`  
`struct FDeltaParameters`  
_L102-133_
- desc: Parameters shared between BeginDelta and UpdateDelta calls, describing the current scale interaction state.
- L105 _public member_ `FTransform Transform = FTransform::Identity;` — The current world transform of the gizmo.
- L108 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — Screen-space location of the gizmo origin, used for label placement.
- L111 _public member_ `FVector DeltaScale = FVector::ZeroVector;` — Per-axis scale delta from the start of the interaction.
- L114 _public member_ `EToolContextCoordinateSystem CoordinateSystem = EToolContextCoordinateSystem::World;` — The active coordinate system (World, Local, etc.).
- L117 _public member_ `EGizmoTransformScaleType ScaleType = EGizmoTransformScaleType::PercentageBased;` — The scale type being used for the interaction.
- L120 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L123 _public member_ `FVector PlaneIntersectionPoint = FVector::ZeroVector;` — World-space point where the interaction ray intersects the plane.
- L126 _public member_ `EAxisList::Type AxisList = EAxisList::None;` — The axis or axes being scaled.
- L129 _public member_ `bool bIsIndirectInteraction = false;` — Whether this is an indirect interaction (e.g. input field rather than drag).
- L132 _public member_ `bool bIsTrustworthy = true;` — Whether the scale value is reliable (false when the cursor is near the gizmo origin, causing instability).

#### struct `UGizmoElementScaleGroup::FState`  
`struct FState`  
_L309-340_
- desc: Snapshot of interaction state used to track the start and current values during a delta operation.
- L312 _public member_ `FTransform Transform = FTransform::Identity;` — World transform of the gizmo at this point in the interaction.
- L315 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — Screen-space location of the gizmo origin.
- L318 _public member_ `FVector Scale = FVector::ZeroVector;` — Per-axis scale values at this point in the interaction.
- L321 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L324 _public member_ `FVector PlaneIntersectionPoint = FVector::ZeroVector;` — World-space point where the interaction ray intersects the plane.
- L327 _public member_ `EAxisList::Type AxisList = EAxisList::None;` — The axis or axes being scaled.
- L330 _public member_ `bool bIsSingleAxis = false;` — True when only a single axis is being scaled (not planar or uniform).
- L333 _public member_ `double DistanceFromStart = 0.0;` — Distance from the interaction start point along the interaction plane.
- L336 _public prototype_ `void Initialize(const FDeltaParameters& InParameters);` — Initializes this state from the given delta parameters at the start of an interaction.
- L339 _public prototype_ `void Update(const FDeltaParameters& InParameters);` — Updates this state from the given delta parameters during an ongoing interaction.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementTranslateAxis.h` (Private)


#### class `UGizmoElementTranslateAxis`  
`class UGizmoElementTranslateAxis : public UGizmoElementGroupBase , public UE::Editor::InteractiveToolsFramework::IPlaneProvider`  
_L36-203_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase,UE::Editor::InteractiveToolsFramework::IPlaneProvider`
- desc: Combines the visual elements of a single translation axis: an arrow handle, a dashed delta line, and a value label shown during interaction. Also implements IPlaneProvider to define the interaction plane for drag projection.
- L75 _public prototype_ `UGizmoElementTranslateAxis();`
- L78 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L79 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L83 _public prototype_ `const FGizmoElementTranslateAxisStyle& GetStyle() const;` — Returns the current visual style for this translate axis element.
- L86 _public prototype_ `void SetStyle(const FGizmoElementTranslateAxisStyle& InStyle);` — Sets and applies the given Style.
- L90 _public prototype_ `virtual UE::Geometry::FFrame3d MakePlane(const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const EAxisList::Type InAxisList) const override;` — Creates the interaction plane for this translate axis, transformed into the provided coordinate space.
- L94 _public prototype_ `void DrawDebug(IToolsContextRenderAPI* RenderAPI, const FGizmoDebugSettings& InSettings);` — Renders various debug visualizations, if enabled.
- L97 _public prototype_ `void SetGizmoViewContext(UGizmoViewContext* InGizmoViewContext);` — Sets the Gizmo view context, needed for screen space interactions
- L101 _public prototype_ `void SetWidgetHost(IToolkitHost* const InWidgetHost);` — Sets the host to add/remove a widget to. Currently, this is a Toolkit host, but it could be abstracted to an ISlateWidgetHost (see IEditorViewportClientProxy).
- L110 _public prototype_ `void Setup( const uint32 InPartId, const EAxisList::Type InAxis, const FGizmoElementTranslateAxisStyle& InStyle);` — Initialize the axis element with a part identifier, axis, and visual style. Must be called before the element can render or receive interactions. @param InPartId Unique identifier for hit-testing this axis. @param InAxis The axis this element represents (e.g. EAxisList::X). @param InStyle Visual style parameters for the axis.
- L116 _public prototype_ `void UpdateElements();` — Rebuilds child elements to reflect the current style. Call after modifying style properties.
- L119 _public prototype_ `void BeginDelta(const FDeltaParameters& InParameters);` — Begin a delta interaction, recording the start state.
- L122 _public prototype_ `void UpdateDelta(const FDeltaParameters& InParameters);` — Update the delta visualization with the current interaction state.
- L125 _public prototype_ `void EndDelta();` — End the current delta interaction and hide delta visuals.
- L130 _private member_ `FGizmoElementTranslateAxisStyle Style;` — `UPROPERTY(Getter, Setter)` — Style contains various uniform and varying properties that affect the appearance of this gizmo element.
- L134 _private member_ `TObjectPtr<UGizmoElementArrow> ArrowElement;` — `UPROPERTY()` — Translate Axis.
- L138 _private member_ `TObjectPtr<UGizmoElementValueWidget> DeltaWidgetElement;` — `UPROPERTY()` — Widget element that displays the delta value label during interaction.
- L142 _private prototype_ `void ApplyStyle();` — Propagates the current Style properties to all child visual elements.
- L146 _private member_ `std::atomic_bool bIsValid = false;` — Flag indicating element validity - generally true after Setup is called.
- L150 _private member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext;` — `UPROPERTY(Setter)` — Gizmo view context, needed for screen space interactions
- L153 _private member_ `EAxisList::Type Axis;` — The axis this element represents (e.g. EAxisList::X).
- L156 _private member_ `FVector ForwardDirection;` — Forward direction along the axis in local space.
- L159 _private member_ `FVector UpDirection;` — Up direction perpendicular to the axis, used for interaction plane construction.
- L162 _private member_ `FVector SideDirection;` — Side direction perpendicular to the axis, used for interaction plane construction.
- L165 _private member_ `FNumberFormattingOptions TextNumberFormattingOptions;` — Formatting options for the delta value label text.
- L196 _private member_ `FState StartState;` — Interaction state captured at BeginDelta, used as the reference for computing deltas.
- L199 _private member_ `FState CurrentState;` — Interaction state updated each frame during an active delta interaction.
- L202 _private member_ `bool bIsShowingDelta = false;` — Whether the delta visualization (dashed line and value label) is currently visible.

#### struct `UGizmoElementTranslateAxis::FDeltaParameters`  
`struct FDeltaParameters`  
_L44-72_
- desc: Parameters shared between BeginDelta and UpdateDelta calls, describing the current interaction state.
- L47 _public member_ `FTransform Transform = FTransform::Identity;` — The current world transform of the gizmo.
- L50 _public member_ `EToolContextCoordinateSystem CoordinateSystem = EToolContextCoordinateSystem::World;` — The active coordinate system (World, Local, etc.).
- L53 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — Screen-space location of the gizmo origin, used for label placement.
- L56 _public member_ `FVector AxisDirection = FVector::ZeroVector;` — Direction of the translation axis in the current coordinate system.
- L59 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L62 _public member_ `FVector Translation = FVector::ZeroVector;` — Accumulated translation delta from the start of the interaction.
- L65 _public member_ `bool bIsCursorInViewport = true;` — Whether the cursor is currently within the viewport (affects delta label visibility).
- L68 _public member_ `bool bIsIndirectInteraction = false;` — Whether this is an indirect interaction (e.g. input field rather than drag).
- L71 _public member_ `EAxisList::Type AxisList = EAxisList::None;` — The axis or axes being translated.

#### struct `UGizmoElementTranslateAxis::FState`  
`struct FState`  
_L168-193_
- desc: Snapshot of interaction state at a point in time, used to track start and current states during a delta.
- L171 _public member_ `FTransform Transform;` — The world transform of the gizmo at this point in the interaction.
- L174 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — The gizmo origin projected into 2D screen-space.
- L177 _public member_ `FVector Translation = FVector::ZeroVector;` — Accumulated translation offset from the interaction origin.
- L180 _public member_ `FVector AxisDirection = FVector::ZeroVector;` — Direction of the translation axis in the current coordinate system.
- L183 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L186 _public member_ `bool bIsSingleAxis = false;` — Whether the interaction is constrained to a single axis (as opposed to a plane).
- L189 _public prototype_ `void Initialize(const FDeltaParameters& InParameters);` — Populates all fields from the given delta parameters at the start of an interaction.
- L192 _public prototype_ `void Update(const FDeltaParameters& InParameters);` — Updates fields from the given delta parameters during an ongoing interaction.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementTranslateGroup.h` (Private)


#### struct `FGizmoElementTranslateAxisStyleOverride`  
`struct FGizmoElementTranslateAxisStyleOverride`  
_L22-44_
- reflection: `USTRUCT(MinimalAPI)`
- desc: This style contains optional per-axis overrides. FGizmoElementTranslateAxisStyle is used for the shared style.
- L28 _public member_ `TOptional<FGizmoPerStateValueLinearColor> Colors;` — `UPROPERTY()` — The Axis color, usually Red for X, etc.
- L32 _public member_ `TOptional<FGizmoPerStateValueMaterialVariant> Materials;` — `UPROPERTY()` — Optional override for axis materials per interaction state.
- L36 _public member_ `TOptional<TObjectPtr<UMaterialInterface>> DeltaMaterial;` — `UPROPERTY()` — Optional override for the delta visualization material.
- L40 _public member_ `TOptional<TObjectPtr<UMaterialInterface>> VertexColorMaterial;` — `UPROPERTY()` — Optional override for the vertex-color material.
- L43 _public prototype_ `void ApplyTo(FGizmoElementTranslateAxisStyle& InOutStyle) const;` — Applies the overrides, if set, to the given Style.

#### struct `FGizmoElementTranslatePlanarStyleOverride`  
`struct FGizmoElementTranslatePlanarStyleOverride`  
_L48-66_
- reflection: `USTRUCT(MinimalAPI)`
- desc: This style contains optional per-planar overrides. FGizmoElementTranslatePlanarStyle is used for the shared style.
- L54 _public member_ `TOptional<FGizmoPerStateValueLinearColor> Colors;` — `UPROPERTY()` — The Plane color, usually Red for YZ, etc.
- L58 _public member_ `TOptional<FGizmoPerStateValueMaterialVariant> Materials;` — `UPROPERTY()` — Optional override for planar materials per interaction state.
- L62 _public member_ `TOptional<TObjectPtr<UMaterialInterface>> VertexColorMaterial;` — `UPROPERTY()` — Optional override for the vertex-color material.
- L65 _public prototype_ `void ApplyTo(FGizmoElementTranslatePlanarStyle& InOutStyle) const;` — Applies the overrides, if set, to the given Style.

#### class `UGizmoElementTranslateGroup`  
`class UGizmoElementTranslateGroup : public UGizmoElementGroupBase , public UE::Editor::InteractiveToolsFramework::IPlaneProvider`  
_L74-348_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroupBase,UE::Editor::InteractiveToolsFramework::IPlaneProvider`
- desc: Container for all translation gizmo elements: per-axis arrows (X, Y, Z), planar handles (XY, YZ, XZ), and the uniform screen-space handle. Manages style propagation, axis enable/disable, and delta visualization across all children.
- L127 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L131 _public prototype_ `void DrawDebug(IToolsContextRenderAPI* RenderAPI, const FGizmoDebugSettings& InSettings, const uint32 InPartId = 0);` — Renders various debug visualizations, if enabled.
- L135 _public prototype_ `void SetWidgetHost(IToolkitHost* const InWidgetHost);` — Sets the host to add/remove a widget to. Currently, this is a Toolkit host, but it could be abstracted to an ISlateWidgetHost (see IEditorViewportClientProxy).
- L138 _public prototype_ `void SetGetCurrentSnappingSettingsFunction(const TFunction<FToolContextSnappingConfiguration()>& InFunction);` — Sets a function that provides the current snapping settings to use during interaction.
- L141 _public prototype_ `void SetAxisEnabled(const EAxisList::Type InAxisListToEnable);` — Enables the elements specified in the provided AxisList, and disables those that aren't.
- L144 _public prototype_ `void SetPlanarEnabled(const EAxisList::Type InAxisListToEnable);` — Enables the planar elements specified in the provided AxisList and disables those that aren't.
- L147 _public prototype_ `void SetUniformEnabled(const bool bInEnable);` — Enables the uniform screen-space element.
- L150 _public prototype_ `const FGizmoElementTranslateStyle& GetStyle() const;` — Returns the current shared translation style.
- L153 _public prototype_ `void SetStyle( const FGizmoElementTranslateStyle& InStyle, const FGizmoElementTranslateAxisStyleOverride& InAxisStyleX, const FGizmoElementTranslateAxisStyleOverride& InAxisStyleY, const FGizmoElementTranslateAxisStyleOverride& InAxisStyleZ, const FGizmoElementTranslatePlanarStyleOverride& InPlanarStyleXY, const FGizmoElementTranslatePlanarStyleOverride& InPlanarStyleYZ, const FGizmoElementTranslatePlanarStyleOverride& InPlanarStyleXZ);` — Sets and applies the given Style + Overrides.
- L164 _public prototype_ `virtual UE::Geometry::FFrame3d MakePlane(const FTransform& InTransform, const UGizmoViewContext* InViewContext, const EToolContextCoordinateSystem InCoordinateSystem, const EAxisList::Type InAxisList) const override;` — Creates the interaction plane for the active translate axis or plane, transformed into the provided coordinate space.
- L181 _public prototype_ `void Setup( const uint32 InPartId, const EAxisList::Type InAxisList, const FGizmoElementTranslateStyle& InStyle, const FAxisParameters& InAxisX, const FAxisParameters& InAxisY, const FAxisParameters& InAxisZ, const FPlanarParameters& InPlanarXY, const FPlanarParameters& InPlanarYZ, const FPlanarParameters& InPlanarXZ, const uint32 InUniformPartId);` — Initialize the translation group with all axis, planar, and uniform elements. Must be called before the group can render or receive interactions. @param InPartId Base part identifier for the group. @param InAxisList Which axes to initially enable. @param InStyle Shared visual style for all translation elements. @param InAxisX Parameters for the X axis element. @param InAxisY Parameters for the Y axis element. @param InAxisZ Parameters for the Z axis element. @param InPlanarXY Parameters for the XY planar element. @param InPlanarYZ Parameters for the YZ planar element. @param InPlanarXZ Parameters for the XZ planar element. @param InUniformPartId Part identifier for the uniform screen-space element.
- L194 _public prototype_ `void UpdateElements();` — Rebuilds child elements to reflect the current style. Call after modifying style properties.
- L197 _public prototype_ `void BeginDelta(const FDeltaParameters& InParameters);` — Begin a delta interaction, recording the start state. Propagates to the active axis element.
- L200 _public prototype_ `void UpdateDelta(const FDeltaParameters& InParameters);` — Update the delta visualization with the current interaction state.
- L203 _public prototype_ `void EndDelta();` — End the current delta interaction and hide delta visuals.
- L206 _public prototype_ `UGizmoElementTranslateAxis* GetAxisElement(const EAxis::Type InAxis) const;` — Get the axis element for the given single axis (X, Y, or Z). Returns nullptr if not set up.
- L209 _public prototype_ `UGizmoElementBox* GetPlanarElement(const EAxisList::Type InAxis) const;` — Get the planar element for the given axis pair (XY, YZ, or XZ). Returns nullptr if not set up.
- L213 _private prototype_ `void ApplyStyle();` — Applies the current style and per-axis/planar overrides to all child elements.
- L216 _private prototype_ `void ForEachAxisElement(const TFunctionRef<void(UGizmoElementTranslateAxis* InElement)>& InFunc) const;` — Invokes the given function on each axis element (X, Y, Z).
- L218 _private prototype_ `void ForEachAxisElementByList(const TFunctionRef<void(UGizmoElementTranslateAxis* InElement, const EAxis::Type InAxis)>& InFunc, const EAxisList::Type InAxisList) const;` — Invokes the given function on each axis element whose axis is included in InAxisList.
- L221 _private prototype_ `bool UpdateDeltaRenderState(IToolsContextRenderAPI* RenderAPI, const FVector& InLocalOrigin, FRenderTraversalState& InOutRenderState);` — Updates the render state for delta elements during render traversal, using the start transform rather than the current. Returns true if visible in the current view.
- L224 _private prototype_ `bool IsInteracting() const;` — Returns true if a delta interaction is currently active.
- L227 _private prototype_ `void ApplyGetCurrentSnappingSettingsFunction();` — Applies and propagates the current snapping-settings provider function, if set.
- L231 _private member_ `std::atomic_bool bIsValid = false;` — Flag indicating element validity - generally true after Setup is called.
- L235 _private member_ `FGizmoElementTranslateStyle Style;` — `UPROPERTY()` — Style contains various uniform and varying properties that affect the appearance of this gizmo element.
- L239 _private member_ `FGizmoElementTranslateAxisStyleOverride StyleX;` — `UPROPERTY()` — Optional overrides for the X axis.
- L243 _private member_ `FGizmoElementTranslateAxisStyleOverride StyleY;` — `UPROPERTY()` — Optional overrides for the Y axis.
- L247 _private member_ `FGizmoElementTranslateAxisStyleOverride StyleZ;` — `UPROPERTY()` — Optional overrides for the Z axis.
- L251 _private member_ `FGizmoElementTranslatePlanarStyleOverride PlanarXYStyle;` — `UPROPERTY()` — Optional overrides for the XY plane.
- L255 _private member_ `FGizmoElementTranslatePlanarStyleOverride PlanarYZStyle;` — `UPROPERTY()` — Optional overrides for the YZ plane.
- L259 _private member_ `FGizmoElementTranslatePlanarStyleOverride PlanarXZStyle;` — `UPROPERTY()` — Optional overrides for the XZ plane.
- L263 _private member_ `TObjectPtr<UGizmoElementTranslateAxis> AxisXElement;` — `UPROPERTY()` — Axis X element.
- L267 _private member_ `TObjectPtr<UGizmoElementTranslateAxis> AxisYElement;` — `UPROPERTY()` — Axis Y element.
- L271 _private member_ `TObjectPtr<UGizmoElementTranslateAxis> AxisZElement;` — `UPROPERTY()` — Axis Z element.
- L275 _private member_ `TObjectPtr<UGizmoElementBox> PlanarXYElement;` — `UPROPERTY()` — Planar XY element.
- L279 _private member_ `TObjectPtr<UGizmoElementBox> PlanarYZElement;` — `UPROPERTY()` — Planar YZ element.
- L283 _private member_ `TObjectPtr<UGizmoElementBox> PlanarXZElement;` — `UPROPERTY()` — Planar XZ element.
- L287 _private member_ `TObjectPtr<UGizmoElementRectangle> UniformElement;` — `UPROPERTY()` — Uniform element.
- L291 _private member_ `TObjectPtr<UGizmoElementCircle> UniformElementAlternate;` — `UPROPERTY()` — Uniform element (alternate). Switches between this and the other Uniform element depending on snap state.
- L295 _private member_ `TObjectPtr<UGizmoElementCircle> OriginElement;` — `UPROPERTY()` — Circle element drawn at the gizmo origin.
- L299 _private member_ `TObjectPtr<UGizmoElementCircle> DeltaOriginElement;` — `UPROPERTY()` — Circle element drawn at the delta origin during translation.
- L303 _private member_ `TObjectPtr<UGizmoElementCylinder> DeltaLineElement;` — `UPROPERTY()` — Line element visualizing the delta distance during translation.
- L306 _private member_ `TFunction<FToolContextSnappingConfiguration()> GetCurrentSnappingSettingsFunction = nullptr;` — Callback that provides the current snapping configuration for interaction.
- L341 _private member_ `FState StartState;` — Captured state at the beginning of the current delta interaction.
- L344 _private member_ `FState CurrentState;` — Most recently updated state during the current delta interaction.
- L347 _private member_ `bool bIsShowingDelta = false;` — True while delta visualization elements are being displayed.

#### struct `UGizmoElementTranslateGroup::FAxisParameters`  
`struct FAxisParameters`  
_L82-90_
- desc: Per-Axis parameters.
- L85 _public member_ `uint32 PartId = 0;` — Hit-test part identifier for this axis element.
- L87 _public member_ `EAxisList::Type Axis = EAxisList::None;` — Which axis this element represents.
- L89 _public member_ `FGizmoElementTranslateAxisStyleOverride StyleOverride;` — Optional style overrides for this axis.

#### struct `UGizmoElementTranslateGroup::FPlanarParameters`  
`struct FPlanarParameters`  
_L93-101_
- desc: Per-Plane parameters.
- L96 _public member_ `uint32 PartId = 0;` — Hit-test part identifier for this planar element.
- L98 _public member_ `EAxisList::Type Axis = EAxisList::None;` — Which plane (axis pair) this element represents.
- L100 _public member_ `FGizmoElementTranslatePlanarStyleOverride StyleOverride;` — Optional style overrides for this planar element.

#### struct `UGizmoElementTranslateGroup::FDeltaParameters`  
`struct FDeltaParameters`  
_L104-123_
- desc: Parameters shared between BeginDelta and UpdateDelta calls, describing the current interaction state.
- L107 _public member_ `FTransform Transform = FTransform::Identity;` — The current world transform of the gizmo.
- L110 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — Screen-space location of the gizmo origin, used for label placement.
- L113 _public member_ `EToolContextCoordinateSystem CoordinateSystem = EToolContextCoordinateSystem::World;` — The active coordinate system (World, Local, etc.).
- L116 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L119 _public member_ `EAxisList::Type AxisList = EAxisList::None;` — The axis or axes being translated.
- L122 _public member_ `bool bIsIndirectInteraction = false;` — Whether this is an indirect interaction (e.g. input field rather than drag).

#### struct `UGizmoElementTranslateGroup::FState`  
`struct FState`  
_L310-338_
- desc: Snapshot of the interaction state at a given point in time, used for delta visualization.
- L313 _public member_ `FTransform Transform;` — World transform of the gizmo.
- L316 _public member_ `FVector2D TransformLocation2D = FVector2D::ZeroVector;` — Screen-space location of the gizmo origin.
- L319 _public member_ `FVector Translation = FVector::ZeroVector;` — Accumulated translation offset from the start of the interaction.
- L322 _public member_ `FVector PlaneNormal = FVector::UpVector;` — Normal of the interaction plane.
- L325 _public member_ `EAxisList::Type AxisList = EAxisList::None;` — The axis or axes being translated.
- L328 _public member_ `bool bIsSingleAxis = false;` — True if the translation is constrained to a single axis.
- L331 _public member_ `double DistanceFromStart = 0.0;` — Signed distance moved from the start position along the translation direction.
- L334 _public prototype_ `void Initialize(const FDeltaParameters& InParameters);` — Initializes this state from the given delta parameters at interaction start.
- L337 _public prototype_ `void Update(const FDeltaParameters& InParameters);` — Updates this state from the given delta parameters during interaction.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementValueWidget.h` (Private)


#### class `UGizmoElementValueWidget`  
`class UGizmoElementValueWidget : public UGizmoElementWidget`  
_L20-52_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementWidget`
- desc: A widget-based gizmo element that displays a formatted numeric value label. Used to show delta values (e.g. translation distance, rotation angle, scale factor) next to the gizmo during interaction.
- L25 _public prototype_ `UGizmoElementValueWidget();`
- L28 _public prototype_ `void SetText(const FText& InText);` — Set the display text directly.
- L31 _public prototype_ `FText GetText() const;` — Get the current display text.
- L39 _public prototype_ `void SetUnitText(const double InValue, const EUnitType InUnitType, const FNumberFormattingOptions& InNumberFormattingOptions = FNumberFormattingOptions::DefaultNoGrouping());` — Format and set the display text from a numeric value with unit conversion. @param InValue The numeric value to display. @param InUnitType The unit type for display formatting (e.g. centimeters, degrees). @param InNumberFormattingOptions Formatting options controlling decimal places, grouping, etc.
- L43 _private prototype_ `FSlateColor GetBackgroundColorAndOpacity() const;` — Returns the background color and opacity for the value label, based on the current gizmo state.
- L48 _private member_ `FText Text;` — `UPROPERTY(Getter, Setter)` — The display text shown in the value widget.
- L51 _private member_ `TSharedPtr<SWidget> ValueWidget = nullptr;` — The Slate widget instance used to render the value label in the viewport.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/GizmoElementWidget.h` (Private)


#### class `UGizmoElementWidget`  
`class UGizmoElementWidget : public UGizmoElementBase`  
_L19-104_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementBase`
- desc: Represents a widget element in the Gizmo system. This is used to add functionality and visual representation associated with a widget in the context of a Gizmo.
- L24 _public prototype_ `UGizmoElementWidget();`
- L27 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L28 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI, const FRenderTraversalState& RenderState) override;`
- L30 _public prototype_ `virtual bool IsVisible(const FSceneView* View, EViewInteractionState InCurrentViewInteractionState, EGizmoElementInteractionState InCurrentInteractionState, const FTransform& InLocalToWorldTransform, const FVector& InLocalCenter) const override;`
- L33 _public prototype_ `const FVector GetLocation() const;`
- L34 _public prototype_ `void SetLocation(const FVector& InLocation);`
- L36 _public prototype_ `const FVector2D GetOffset2D() const;`
- L37 _public prototype_ `void SetOffset2D(const FVector2D& InOffset2D);`
- L39 _public prototype_ `bool GetClampToScreen() const;`
- L40 _public prototype_ `void SetClampToScreen(bool bInClampToScreen);`
- L42 _public typedef_ `using FClampToScreenFunction = TUniqueFunction<FVector2D(const FVector2D& WidgetLocation, const FVector2D& WidgetSize, const FIntRect& ViewRect)>;`
- L45 _public prototype_ `void SetClampToScreenFunction(FClampToScreenFunction&& InClampToScreenFunction);` — Set a custom function to use when ClampToScreen is true.
- L48 _public prototype_ `void ResetClampToScreenFunction();` — Resets the ClampToScreen function to default behavior.
- L50 _public prototype_ `const TSharedPtr<SWidget>& GetWidget() const;`
- L51 _public prototype_ `void SetWidget(const TSharedPtr<SWidget>& InWidget);`
- L55 _public prototype_ `void SetWidgetHost(IToolkitHost* const InWidgetHost);` — Sets the host to add/remove a widget to. Currently, this is a Toolkit host, but it could be abstracted to an ISlateWidgetHost (see IEditorViewportClientProxy).
- L60 _protected member_ `FVector Location = FVector::ZeroVector;` — `UPROPERTY(Getter, Setter)` — The location of the widget, in world space. Note that this is always projected into screen space.
- L64 _protected member_ `FVector2D Offset2D = FVector2D::ZeroVector;` — `UPROPERTY(Getter, Setter)` — Offset to apply in screen space, applied after converting from world to screen.
- L72 _protected member_ `bool bClampToScreen = false;` — `UPROPERTY(Getter = "GetClampToScreen", Setter = "SetClampToScreen")` — Whether to clamp the widget to screen bounds. Note that this has the effect of ignoring culling, so may require manual visibility handling. The clamping is based on the viewport size and widgets' desired size.
- L75 _protected member_ `FClampToScreenFunction ClampToScreenFunction;` — An overridable function to retrieve the clamped widget location. Useful for when the clamped location should be based on an intersection vs. simple clamp.
- L79 _private prototype_ `EVisibility GetVisibility() const;` — Get the widget visibility based on the element state.
- L82 _private prototype_ `void RemoveWidget();` — Remove the widget from the current viewport.
- L85 _private prototype_ `void UpdateWidgetTransform(const FVector2D& InLocation);` — Update the widget's transform based on the current location within the viewport.
- L88 _private prototype_ `void OnActiveViewportChanged(TSharedPtr<IAssetViewport> InOldViewport, TSharedPtr<IAssetViewport> InNewViewport);` — Callback for when the active viewport changes, to re-add the widget to the new viewport.
- L91 _private prototype_ `FVector2D ClampToScreenInternal(const FVector2D& InWidgetLocation, const FVector2D& InWidgetSize, const FIntRect& InViewRect) const;` — Internal implementation of the default ClampToScreen function.
- L94 _private member_ `const FVector2D Offset2DMultiplier = FVector2D(1.0, -1.0);` — Invert Y axis for screen space
- L97 _private member_ `TSharedPtr<SBox> HostWidget;` — The outer widget that's transformed from world to screen space, with the user-specified Widget as the child.
- L100 _private member_ `TSharedPtr<SWidget> Widget;` — The actual widget to display.
- L103 _private member_ `IToolkitHost* WidgetHost = nullptr;` — The current toolkit the widget is added to, containing a viewport.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Widgets/SGizmoCursor.h` (Private)


#### class `SGizmoCursor`  
`class SGizmoCursor : public SCompoundWidget , public FGCObject`  
_L16-74_
- inherits: `SCompoundWidget,FGCObject`
- desc: Slate widget that renders a rotatable, resizable cursor image for gizmo interactions. Uses a dynamic material instance to draw the cursor brush, and implements FGCObject to prevent GC of the material.
- L23 _public function_ `SLATE_BEGIN_ARGS(SGizmoCursor)`
- L26 _public prototype_ `SLATE_ATTRIBUTE(const FSlateBrush*, Image) SLATE_ATTRIBUTE(FSlateColor, ColorAndOpacity) SLATE_ATTRIBUTE(FVector2f, Size) SLATE_ATTRIBUTE(float, Rotation) SLATE_END_ARGS() SGizmoCursor();` — Image resource
- L41 _public prototype_ `void Construct(const FArguments& InArgs);` — Constructs the cursor widget from the provided Slate arguments.
- L44 _public prototype_ `virtual void AddReferencedObjects(FReferenceCollector& Collector) override;` — Reports various uobjects to the garbage collector so it is not collected while this widget is alive.
- L47 _public prototype_ `virtual FString GetReferencerName() const override;` — Returns the name of this referencer for GC debugging and logging.
- L50 _public prototype_ `void SetSize(const FVector2f& InSize);` — Sets the size of the cursor widget. This will overwrite any attribute binding present.
- L54 _private prototype_ `TOptional<FVector2D> GetSizeOverride() const;` — Returns the desired size override for the cursor widget, or empty to use default sizing.
- L57 _private prototype_ `TOptional<FSlateRenderTransform> GetImageTransform() const;` — Returns the render transform (rotation) to apply to the cursor image, or empty for no transform.
- L61 _private member_ `TSlateAttribute<FVector2f> Size;` — Current size of the cursor image in pixels.
- L64 _private member_ `TSlateAttribute<float> Rotation;` — Current rotation of the cursor image in radians.
- L67 _private member_ `TSharedPtr<FSlateBrush> Brush;` — Brush is used to draw the cursor on SImage
- L70 _private member_ `FSoftObjectPath BrushMaterialPath;` — Asset path to the material used for the cursor brush.
- L73 _private member_ `TObjectPtr<UMaterialInstanceDynamic> BrushMaterial = nullptr;` — Material used to draw the brush texture

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorGizmos/Widgets/SGizmoElementValue.h` (Private)


#### class `UE::Editor::InteractiveToolsFramework::SGizmoElementValue`  
`class SGizmoElementValue : public SCompoundWidget`  
_L14-28_
- inherits: `SCompoundWidget`
- desc: Slate widget that displays a formatted text value with a colored background, used for gizmo delta labels (distance, angle, scale).
- L17 _public function_ `SLATE_BEGIN_ARGS(SGizmoElementValue)`
- L19 _public prototype_ `SLATE_ATTRIBUTE(FText, Text) SLATE_ATTRIBUTE(FSlateColor, BackgroundColorAndOpacity) SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L27 _private member_ `TSharedPtr<FSlateRoundedBoxBrush> RoundedBoxBrush;`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Editor` (scope `UE`)
- L11 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorInteractiveToolsFrameworkStyle.h` (Private)


#### class `UE::Editor::InteractiveToolsFramework::Private::FEditorInteractiveToolsFrameworkStyle`  
`class FEditorInteractiveToolsFrameworkStyle : public FSlateStyleSet`  
_L12-29_
- inherits: `FSlateStyleSet`
- desc: Slate style set providing brushes, fonts, and colors for the Editor Interactive Tools Framework widgets (gizmo cursors, value labels, etc.).
- L17 _public prototype_ `static FEditorInteractiveToolsFrameworkStyle& Get();` — Returns the singleton instance, creating and registering it on first access.
- L20 _public prototype_ `virtual const FName& GetStyleSetName() const override;` — Returns the registered name used to identify this style set.
- L23 _private prototype_ `FEditorInteractiveToolsFrameworkStyle();`
- L28 _private member_ `static FName StyleName;` — The registered name of this style set.

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L9 _namespace_ `namespace Private` (scope `UE::Editor::InteractiveToolsFramework`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorTRSGizmoPresets.h` (Private)


#### struct `FTransformGizmoPreset`  
`struct FTransformGizmoPreset`  
_L13-85_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Represents a predefined gizmo configuration preset.
- L17 _public prototype_ `FTransformGizmoPreset() = default;`
- L19 _public function_ `FTransformGizmoPreset( const FName InName, const FText& InDisplayName, const FText& InToolTipText) : Name(InName) , DisplayName(InDisplayName) , ToolTipText(InToolTipText)`
- L30 _public member_ `FName Name;` — `UPROPERTY()` — The internal name of the preset.
- L34 _public member_ `FText DisplayName;` — `UPROPERTY()` — The display name of the preset.
- L38 _public member_ `FText ToolTipText;` — `UPROPERTY()` — Provides text for a tooltip display.
- L44 _public member_ `bool bDragDuplicateOnRotation = true;` — `UPROPERTY()` — Indicates whether a drag duplication action should be triggered when rotating an object.
- L50 _public member_ `bool bIncludeExplicitRotation = false;` — `UPROPERTY()` — Indicates whether explicit rotation operations should be included.
- L54 _public member_ `bool bUniformIndirectScale = false;` — `UPROPERTY()` — Indicates whether the indirect scale should be applied uniformly across all dimensions.
- L58 _public member_ `bool bPersistHandleSelection = false;` — `UPROPERTY()` — Indicates whether the selection of handles should be maintained across different operations.
- L62 _public member_ `bool bSequentialIndirectAxesButtons = false;` — `UPROPERTY()` — Indicates whether the indirect axes buttons are activated in a sequential manner.
- L66 _public member_ `bool bAdditiveIndirectAxes = false;` — `UPROPERTY()` — Determines whether indirect axes should be combined additively.
- L70 _public member_ `bool bScreenSpaceIndirectOrthographicManipulation = true;` — `UPROPERTY()` — Indicates whether screen-space indirect manipulation is enabled in orthographic views.
- L74 _public member_ `TEnumAsByte<EAxisRotateMode::Type> RotateMode = EAxisRotateMode::ScreenArc;` — `UPROPERTY()` — The mode to use for rotation (e.g. ScreenArc, Pull).
- L78 _public member_ `EGizmoTransformScaleType ScaleType = EGizmoTransformScaleType::PercentageBased;` — `UPROPERTY()` — The type of scaling to use (e.g. PercentageBased).
- L81 _public prototype_ `static const TArray<FTransformGizmoPreset>& GetBuiltInPresets();` — Returns the array of built-in presets.
- L84 _public prototype_ `static const FTransformGizmoPreset* FindPresetByName(FName InName);` — Finds a preset by name. Returns nullptr if not found.

#### struct `UE::Editor::InteractiveToolsFramework::FPresetSettingComparison`  
`struct FPresetSettingComparison`  
_L92-114_
- desc: A single row of comparison data between current settings and a preset.
- L95 _public member_ `FText SettingName;` — The display name of the setting (e.g. "Rotate Mode").
- L98 _public member_ `FText CurrentValue;` — The current value of this setting, formatted for display (used for non-bool settings).
- L101 _public member_ `FText PresetValue;` — The value this setting will be changed to if the preset is applied (used for non-bool settings).
- L104 _public member_ `bool bCurrentValueDiffersToPresetValue = false;` — True if the current value differs from the preset value.
- L107 _public member_ `bool bIsBool = false;` — True if this setting is a boolean and should be rendered as checkboxes.
- L110 _public member_ `bool bCurrentValue = false;` — The current boolean state (only valid when bIsBool is true).
- L113 _public member_ `bool bPresetValue = false;` — The preset boolean state (only valid when bIsBool is true).

#### struct `UE::Editor::InteractiveToolsFramework::FTransformGizmoPresetAccessor`  
`struct FTransformGizmoPresetAccessor`  
_L117-199_
- desc: Provides getters/setters to get current settings, and apply them.
- L120 _public prototype_ `bool CurrentSettingsMatchPreset(const FTransformGizmoPreset& InPreset) const;` — Returns true if the current settings match the given preset.
- L123 _public prototype_ `void ApplyPreset(const FTransformGizmoPreset& InPreset) const;` — Applies the given preset to the current settings.
- L126 _public prototype_ `TArray<FPresetSettingComparison> BuildComparisonWithPreset(const FTransformGizmoPreset& InPreset) const;` — Builds a per-setting comparison between the current settings and the given preset.
- L129 _public prototype_ `bool GetDragDuplicateOnRotation() const;` — Returns the current value of bDragDuplicateOnRotation.
- L132 _public prototype_ `void SetDragDuplicateOnRotation(bool bInValue) const;` — Sets the value of bDragDuplicateOnRotation.
- L135 _public prototype_ `bool GetIncludeExplicitRotation() const;` — Returns the current value of bIncludeExplicitRotation.
- L138 _public prototype_ `void SetIncludeExplicitRotation(bool bInValue) const;` — Sets the value of bIncludeExplicitRotation.
- L141 _public prototype_ `bool GetUniformIndirectScale() const;` — Returns the current value of bUniformIndirectScale.
- L144 _public prototype_ `void SetUniformIndirectScale(bool bInValue) const;` — Sets the value of bUniformIndirectScale.
- L147 _public prototype_ `bool GetPersistHandleSelection() const;` — Returns the current value of bPersistHandleSelection.
- L150 _public prototype_ `void SetPersistHandleSelection(bool bInValue) const;` — Sets the value of bPersistHandleSelection.
- L153 _public prototype_ `bool GetSequentialIndirectAxesButtons() const;` — Returns the current value of bSequentialIndirectAxesButtons.
- L156 _public prototype_ `void SetSequentialIndirectAxesButtons(bool bInValue) const;` — Sets the value of bSequentialIndirectAxesButtons.
- L159 _public prototype_ `bool GetAdditiveIndirectAxes() const;` — Returns the current value of bAdditiveIndirectAxes.
- L162 _public prototype_ `void SetAdditiveIndirectAxes(bool bInValue) const;` — Sets the value of bAdditiveIndirectAxes.
- L165 _public prototype_ `bool GetScreenSpaceIndirectOrthographicManipulation() const;` — Returns the current value of bScreenSpaceIndirectOrthographicManipulation.
- L168 _public prototype_ `void SetScreenSpaceIndirectOrthographicManipulation(bool bInValue) const;` — Sets the value of bScreenSpaceIndirectOrthographicManipulation.
- L171 _public prototype_ `EAxisRotateMode::Type GetRotateMode() const;` — Returns the current RotateMode.
- L174 _public prototype_ `void SetRotateMode(EAxisRotateMode::Type InRotateMode) const;` — Sets the RotateMode.
- L177 _public prototype_ `EGizmoTransformScaleType GetScaleType() const;` — Returns the current ScaleType.
- L180 _public prototype_ `void SetScaleType(EGizmoTransformScaleType InScaleType) const;` — Sets the ScaleType.
- L184 _private function_ `template <typename ObjectType> void BroadcastPropertyChanged(ObjectType* InObject, const FName InPropertyName) const`

#### Free symbols / members of external scopes

- L87 _namespace_ `namespace UE`
- L87 _namespace_ `namespace Editor` (scope `UE`)
- L87 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/EditorToolDataVisualizer.h` (Private)


#### class `UE::Editor::InteractiveToolsFramework::ToolDataVisualizer::FCanvasDashedLineItem`  
`class FCanvasDashedLineItem : public FCanvasLineItem`  
_L12-28_
- inherits: `FCanvasLineItem`
- desc: A canvas draw item that renders a dashed line between two points, with configurable dash and gap lengths.
- L15 _public prototype_ `FCanvasDashedLineItem() = default;`
- L18 _public prototype_ `template <typename VectorType> FCanvasDashedLineItem(const VectorType& InStartPos, const VectorType& InEndPos);`
- L21 _public prototype_ `virtual void Draw(FCanvas* InCanvas) override;` — Draws a dashed line on the canvas between the configured start and end positions.
- L24 _public member_ `float DashLength = 1.0f;` — The length of each dash segment, in pixels.
- L27 _public member_ `float DashGap = 1.0f;` — The length of the gap between dashes, in pixels.
- L31 _prototype_ `template <> FCanvasDashedLineItem::FCanvasDashedLineItem(const FVector2D& InStartPos, const FVector2D& InEndPos);`
- L34 _prototype_ `template <> FCanvasDashedLineItem::FCanvasDashedLineItem(const FVector& InStartPos, const FVector& InEndPos);`

#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace Editor` (scope `UE`)
- L7 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L9 _namespace_ `namespace ToolDataVisualizer` (scope `UE::Editor::InteractiveToolsFramework`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Snapping/EditorSnappingUtil.h` (Private)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace EditorSnappingUtil` (scope `UE`)
- L17 _function_ `template <typename ComponentType UE_REQUIRES(std::is_base_of_v<UActorComponent, std::decay_t<ComponentType>>)> bool GetActorComponents(const TConstArrayView<AActor*>& InActors, TArray<const ComponentType*>& OutComponents)` (scope `UE::EditorSnappingUtil`) — Utility function to get all components of the given type from one or more Actors. @return true if any components found.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Snapping/GridSnapping.h` (Private)


#### struct `UE::Editor::Gizmos::FGizmoGridSnapperRequest`  
`struct FGizmoGridSnapperRequest`  
_L21-26_
- L23 _public member_ `FVector PositionGridSize;`
- L24 _public member_ `FRotator RotationGridSize;`
- L25 _public member_ `FVector ScaleGridSize;`

#### class `UE::Editor::Gizmos::FGizmoGridSnapper`  
`class FGizmoGridSnapper final : public TSceneSnapQueryTargetHandler<FGizmoGridSnapperRequest>`  
_L28-55_
- inherits: `TSceneSnapQueryTargetHandler<FGizmoGridSnapperRequest>`
- L31 _public prototype_ `explicit FGizmoGridSnapper(const UInteractiveToolsContext* InToolsContext);`
- L32 _public prototype_ `virtual ~FGizmoGridSnapper() override = default;`
- L35 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L36 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const override;`
- L37 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapRotation(const FQuat& InRotation, FQuat& OutSnappedRotation, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L38 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapRotationAxisAngle(const double& InAngle, double& OutSnappedAngle, const EAxisList::Type InAxis) const override;`
- L39 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapScale(const FVector& InScale, FVector& OutSnappedScale, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L40 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapScaleAxis(const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const override;`
- L41 _public prototype_ `virtual bool IsQueryTypeSupported(const ESceneSnapQueryType InQueryType) const override;`
- L45 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FGizmoGridSnapperRequest& InTargetRequest, const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L46 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const FGizmoGridSnapperRequest& InTargetRequest, const double InAxisValue, double& OutSnappedPositionAxis, const EAxisList::Type InAxis) const override;`
- L47 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapRotation(const FGizmoGridSnapperRequest& InTargetRequest, const FQuat& InRotation, FQuat& OutSnappedRotation, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L48 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapRotationAxisAngle(const FGizmoGridSnapperRequest& InTargetRequest, const double& InAngle, double& OutSnappedAngle, const EAxisList::Type InAxis) const override;`
- L49 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapScale(const FGizmoGridSnapperRequest& InTargetRequest, const FVector& InScale, FVector& OutSnappedScale, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L50 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapScaleAxis(const FGizmoGridSnapperRequest& InTargetRequest, const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const override;`
- L54 _private member_ `const IToolsContextQueriesAPI* QueriesAPI = nullptr;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace Gizmos` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Snapping/PolicySnapping.h` (Private)


#### struct `UE::Editor::Gizmos::FGizmoPolicySnapper`  
`struct FGizmoPolicySnapper final : public FSceneSnapQueryTargetHandler`  
_L22-40_
- inherits: `FSceneSnapQueryTargetHandler`
- desc: Adapter for a given ISnappingPolicy.
- L25 _public prototype_ `explicit FGizmoPolicySnapper(const TSharedPtr<ISnappingPolicy>& InSnappingPolicy);`
- L26 _public prototype_ `virtual ~FGizmoPolicySnapper() override = default;`
- L29 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList) const override;`
- L30 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const double InAxisDelta, double& OutSnappedAxisDelta, const EAxisList::Type InAxis) const override;`
- L31 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapRotation(const FQuat& InRotation, FQuat& OutRotation, const EAxisList::Type InAxisList) const override;`
- L32 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapRotationAxisAngle(const double& InAngleDelta, double& OutSnappedAngleDelta, const EAxisList::Type InAxis) const override;`
- L33 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapScale(const FVector& InScale, FVector& OutSnappedScale, const EAxisList::Type InAxisList) const override;`
- L34 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapScaleAxis(const double InAxisDelta, double& OutSnappedAxisDelta, const EAxisList::Type InAxis) const override;`
- L35 _public prototype_ `virtual bool IsQueryTypeSupported(const ESceneSnapQueryType InQueryType) const override;`
- L39 _private member_ `TSharedPtr<ISnappingPolicy> SnappingPolicy;`

#### Free symbols / members of external scopes

- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace Gizmos` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Snapping/TransformSnapping.h` (Private)


#### struct `UE::Editor::Gizmos::FGizmoTransformSnapperRequest`  
`struct FGizmoTransformSnapperRequest`  
_L22-29_
- L24 _public member_ `EToolContextCoordinateSystem CoordinateSpace = EToolContextCoordinateSystem::World;`
- L25 _public member_ `FTransform Transform;`
- L26 _public member_ `FTransform CoordinateTransform;`
- L27 _public member_ `float SnapDistance = 0.0f;`
- L28 _public member_ `FRay WorldRay;`

#### class `UE::Editor::Gizmos::FGizmoTransformSnapper`  
`class FGizmoTransformSnapper final : public TSceneSnapQueryTargetHandler<FGizmoTransformSnapperRequest>`  
_L31-54_
- inherits: `TSceneSnapQueryTargetHandler<FGizmoTransformSnapperRequest>`
- L34 _public prototype_ `explicit FGizmoTransformSnapper(const UInteractiveToolsContext* InToolsContext);`
- L35 _public prototype_ `virtual ~FGizmoTransformSnapper() override = default;`
- L38 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const override;`
- L39 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L40 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const double InAxisValue, double& OutSnappedAxisValue, const EAxisList::Type InAxis) const override;`
- L41 _public prototype_ `virtual bool IsQueryTypeSupported(const ESceneSnapQueryType InQueryType) const override;`
- L45 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPosition(const FGizmoTransformSnapperRequest& InTargetRequest, const FVector& InPosition, FVector& OutSnappedPosition, const EAxisList::Type InAxisList = EAxisList::All) const override;`
- L46 _public prototype_ `virtual ESceneSnapQueryTargetResult SnapPositionAxis(const FGizmoTransformSnapperRequest& InTargetRequest, const double InAxisValue, double& OutSnappedPositionAxis, const EAxisList::Type InAxis) const override;`
- L49 _public function_ `virtual ESceneSnapQueryTargetType GetTargetTypes() const override`
- L52 _private member_ `TWeakObjectPtr<UInteractiveToolManager> ToolManager = nullptr;`
- L53 _private member_ `const IToolsContextQueriesAPI* QueriesAPI = nullptr;`

#### Free symbols / members of external scopes

- L20 _namespace_ `namespace UE`
- L20 _namespace_ `namespace Editor` (scope `UE`)
- L20 _namespace_ `namespace Gizmos` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Widgets/SCoordinateSystemMask.h` (Private)


#### struct `TWidgetTypeTraits`  
`template<> struct TWidgetTypeTraits<class SCoordinateSystemBitmask>`  
_L13-16_
- L15 _public function_ `static constexpr bool SupportsInvalidation()`

#### class `SCoordinateSystemBitmask`  
`class SCoordinateSystemBitmask : public SCompoundWidget`  
_L22-68_
- inherits: `SCompoundWidget`
- desc: A widget that displays ECoordSystem enum values as bitflags. @see: SPropertyEditorNumeric
- L44 _public function_ `SLATE_BEGIN_ARGS(SCoordinateSystemBitmask) : _Value(INDEX_NONE)`
- L47 _public prototype_ `SLATE_ARGUMENT(TSet<ECoordSystem>, ValuesToHide) SLATE_ATTRIBUTE(TOptional<int32>, Value) SLATE_EVENT(TDelegate<void(int32)>, OnSetValue) SLATE_END_ARGS() SCoordinateSystemBitmask();`
- L54 _public prototype_ `void Construct(const FArguments& InArgs);`
- L58 _private prototype_ `TOptional<int32> GetValue() const;` — Gets the current bitmask value from the property.
- L61 _private prototype_ `void SetValue(int32 NewValue);` — Commits a new bitmask value to the property.
- L64 _private member_ `TSlateAttribute<TOptional<int32>> ValueAttribute;`
- L65 _private member_ `TDelegate<void(int32)> OnSetValue;`
- L67 _private member_ `TSharedPtr<SComboButton> PrimaryWidget;`

#### struct `SCoordinateSystemBitmask::FCoordinateSystemFlagInfo`  
`struct FCoordinateSystemFlagInfo`  
_L28-41_
- desc: Flag information for coordinate system bitmask UI.
- L30 _public member_ `int32 Value = INDEX_NONE;`
- L31 _public member_ `FText DisplayName;`
- L32 _public member_ `FText ToolTipText;`
- L33 _public member_ `FSlateIcon Icon;`
- L34 _public member_ `bool bIsEditable = true;`
- L37 _public function_ `bool operator==(const ECoordSystem InCoordSystemValue) const` — Supports find by Key.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Widgets/SGizmoSettings.h` (Private)


#### class `SGizmoSettings`  
`class SGizmoSettings : public SCompoundWidget , public FNotifyHook`  
_L16-73_
- inherits: `SCompoundWidget,FNotifyHook`
- L21 _public function_ `SLATE_BEGIN_ARGS(SGizmoSettings)`
- L25 _public prototype_ `virtual ~SGizmoSettings() override;`
- L27 _public prototype_ `void Construct(const FArguments& InArgs);`
- L30 _private prototype_ `TSharedRef<SWidget> MakeStyleDetailsView();`
- L31 _private prototype_ `TSharedRef<SWidget> MakeInteractionDetailsView();`
- L32 _private prototype_ `TSharedRef<SWidget> MakeDebugDetailsView();`
- L34 _private prototype_ `TSharedPtr<IDetailsView> MakeDetailsView(TUniqueFunction<TSharedPtr<FStructOnScope>(UTransformGizmoEditorSettings*)>&& InStructProvider, FOnGetDetailCustomizationInstance InCustomizationGetter);`
- L37 _private function_ `template <typename CustomizationType> TSharedPtr<IDetailsView> MakeDetailsView(TUniqueFunction<TSharedPtr<FStructOnScope>(UTransformGizmoEditorSettings*)>&& InStructProvider)`
- L44 _private prototype_ `bool IsPropertyVisible(const FPropertyAndParent& InPropertyAndParent);`
- L47 _private prototype_ `virtual void NotifyPreChange(FEditPropertyChain* InPropertyAboutToChange) override;`
- L48 _private prototype_ `virtual void NotifyPostChange(const FPropertyChangedEvent& InPropertyChangedEvent, FEditPropertyChain* InPropertyThatChanged) override;`
- L51 _private prototype_ `void OnObjectTransacted(UObject* Object, const FTransactionObjectEvent& TransactionObjectEvent);`
- L53 _private prototype_ `void BroadcastGizmoParametersChanged() const;`
- L55 _private prototype_ `bool IsGizmoEnabled() const;`
- L56 _private prototype_ `FReply SetGizmoEnabled(const bool bInEnabled);`
- L58 _private prototype_ `FReply SaveSettings();`
- L59 _private prototype_ `FReply LoadSettings();`
- L62 _private prototype_ `FReply ResetSettings();` — Resets style and interaction.
- L66 _private member_ `TSharedPtr<SWidgetSwitcher> TabSwitcher;` — Switcher that controls which tab widget is currently visible
- L68 _private member_ `TSharedPtr<IDetailsView> StyleDetailsView;`
- L69 _private member_ `TSharedPtr<IDetailsView> InteractionDetailsView;`
- L71 _private member_ `TSharedPtr<TCVarToggle<bool>> CVarDebugDraw;`
- L72 _private member_ `TSharedPtr<TCVarToggle<bool>> CVarDebugHitDraw;`

#### Free symbols / members of external scopes

- L41 _function_ `MoveTemp(InStructProvider), FOnGetDetailCustomizationInstance::CreateLambda([]() -> TSharedRef<IDetailCustomization> { return MakeShared<CustomizationType>(); }));` (scope `SGizmoSettings::MakeDetailsView`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Private/Widgets/SGizmoTree.h` (Private)


#### class `FGizmoTreeElementViewModel`  
`class FGizmoTreeElementViewModel : public TSharedFromThis<FGizmoTreeElementViewModel>`  
_L20-82_
- inherits: `TSharedFromThis<FGizmoTreeElementViewModel>`
- L25 _public prototype_ `explicit FGizmoTreeElementViewModel() = default;`
- L27 _public prototype_ `static TSharedPtr<FGizmoTreeElementViewModel> Construct(const UGizmoElementBase* InGizmoElement, const TFunction<bool(const uint32)>& InGetSelectedFunc, const TSharedPtr<FGizmoTreeElementViewModel>& InParentViewModel = nullptr);`
- L29 _public prototype_ `const int32 GetLevel() const;`
- L31 _public prototype_ `const FLinearColor GetColor() const;`
- L33 _public prototype_ `const FName GetPartName() const;`
- L35 _public prototype_ `const bool IsPartInherited() const;`
- L37 _public prototype_ `const FString GetName() const;`
- L39 _public prototype_ `const FName GetStateName() const;`
- L41 _public prototype_ `const FLinearColor GetStateColor() const;`
- L43 _public prototype_ `const FName GetPreviousStateName() const;`
- L45 _public prototype_ `const FLinearColor GetPreviousStateColor() const;`
- L47 _public prototype_ `const bool IsStateInherited() const;`
- L49 _public prototype_ `const bool IsVisible() const;`
- L51 _public prototype_ `const bool IsSelected() const;`
- L53 _public prototype_ `const FLinearColor GetCurrentVertexColor() const;`
- L55 _public prototype_ `const FLinearColor GetCurrentLineColor() const;`
- L57 _public prototype_ `const FString GetCurrentMaterialName() const;`
- L59 _public prototype_ `TConstArrayView<TSharedPtr<FGizmoTreeElementViewModel>> GetChildren() const;`
- L61 _public member_ `TFunction<bool(const uint32)> GetSelectedFunc;`
- L64 _private prototype_ `void PopulateChildren();`
- L66 _private prototype_ `static FString ResolveOwningPropertyName(const UGizmoElementBase* InElement);`
- L68 _private prototype_ `const FLinearColor GetStateColorInternal(const EGizmoElementInteractionState InState) const;`
- L71 _private member_ `TWeakObjectPtr<const UGizmoElementBase> WeakGizmoElement;`
- L72 _private member_ `TWeakObjectPtr<const UGizmoElementLineBase> WeakLineElement;`
- L73 _private member_ `TWeakPtr<FGizmoTreeElementViewModel> WeakParent;`
- L74 _private member_ `TArray<TSharedPtr<FGizmoTreeElementViewModel>> Children;`
- L76 _private member_ `uint32 UniqueId = 0;`
- L77 _private member_ `int32 Level;`
- L78 _private member_ `FLinearColor Color;`
- L79 _private member_ `FString OwningPropertyName;`
- L80 _private member_ `mutable EGizmoElementInteractionState CurrentState = EGizmoElementInteractionState::None;`
- L81 _private member_ `mutable EGizmoElementInteractionState PreviousState = EGizmoElementInteractionState::None;`

#### class `FGizmoTreeViewModel`  
`class FGizmoTreeViewModel : public TSharedFromThis<FGizmoTreeViewModel>`  
_L84-122_
- inherits: `TSharedFromThis<FGizmoTreeViewModel>`
- L98 _public prototype_ `explicit FGizmoTreeViewModel() = default;`
- L100 _public prototype_ `~FGizmoTreeViewModel();`
- L102 _public prototype_ `static TSharedPtr<FGizmoTreeViewModel> Construct(const UTransformGizmo* InGizmo);`
- L104 _public prototype_ `const FName GetHitPartName() const;`
- L106 _public prototype_ `const FName GetLastSelectedPartName() const;`
- L107 _public prototype_ `const FName GetLastHoveredPartName() const;`
- L108 _public prototype_ `const FName GetLastInteractedPartName() const;`
- L109 _public prototype_ `const FName GetLastSubduedPartName() const;`
- L110 _public prototype_ `const FText GetInputRay() const;`
- L111 _public prototype_ `const FText GetInputPosition() const;`
- L112 _public prototype_ `const TArray<TSharedPtr<FGizmoTreeContextObjectViewModel>>& GetContextObjects() const;`
- L114 _public prototype_ `bool IsDebugDrawing() const;`
- L115 _public prototype_ `void SetDebugDraw(const bool bInValue);`
- L116 _public prototype_ `void OnDebugDrawChanged(IConsoleVariable* InCVar);`
- L119 _private member_ `TWeakObjectPtr<const UTransformGizmo> WeakGizmo;`
- L120 _private member_ `std::atomic_bool bIsDebugDrawing;`
- L121 _private member_ `TArray<TSharedPtr<FGizmoTreeContextObjectViewModel>> ContextObjects;`

#### class `FGizmoTreeViewModel::FGizmoTreeContextObjectViewModel`  
`class FGizmoTreeContextObjectViewModel : public TSharedFromThis<FGizmoTreeContextObjectViewModel>`  
_L87-95_
- inherits: `TSharedFromThis<FGizmoTreeContextObjectViewModel>`
- L90 _public prototype_ `static TSharedPtr<FGizmoTreeContextObjectViewModel> Construct(const UObject* InContextObject);`
- L92 _public member_ `FName Name;`
- L93 _public member_ `TArray<FName> PropertyNames;`
- L94 _public member_ `TArray<FName> FunctionNames;`

#### class `SGizmoTreeTableRow`  
`class SGizmoTreeTableRow : public SMultiColumnTableRow<TSharedPtr<FGizmoTreeElementViewModel>>`  
_L124-140_
- inherits: `SMultiColumnTableRow<TSharedPtr<FGizmoTreeElementViewModel>>`
- L127 _public function_ `SLATE_BEGIN_ARGS(SGizmoTreeTableRow)`
- L129 _public prototype_ `SLATE_ARGUMENT(TSharedPtr<FGizmoTreeElementViewModel>, Item) SLATE_END_ARGS() void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InTreeView);`
- L136 _public prototype_ `virtual TSharedRef<SWidget> GenerateWidgetForColumn(const FName& InColumnName) override;` — Overridden from SMultiColumnTableRow.  Generates a widget for this column of the tree row.
- L139 _private member_ `TSharedPtr<FGizmoTreeElementViewModel> Item;`

#### class `SGizmoTree`  
`class SGizmoTree : public SCompoundWidget`  
_L142-186_
- inherits: `SCompoundWidget`
- L146 _public function_ `SLATE_BEGIN_ARGS(SGizmoTree)`
- L148 _public prototype_ `SLATE_END_ARGS() void Construct(const FArguments& InArgs);`
- L153 _private prototype_ `virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;`
- L155 _private prototype_ `TSharedRef<ITableRow> GenerateContextObjectRow(TSharedPtr<FGizmoTreeViewModel::FGizmoTreeContextObjectViewModel> InContextObjectName, const TSharedRef<STableViewBase>& InOwnerTable);`
- L157 _private prototype_ `void UpdateGizmoChoices();`
- L158 _private prototype_ `FText GetGizmoChoiceLabel() const;`
- L159 _private prototype_ `TSharedRef<SWidget> GenerateGizmoChoiceWidget(TSharedPtr<FName> InName);`
- L160 _private prototype_ `void OnGizmoChoiceChanged(TSharedPtr<FName> InName, ESelectInfo::Type InSelectInfo);`
- L162 _private prototype_ `ECheckBoxState IsShowingHidden() const;`
- L163 _private prototype_ `void OnShowHiddenChanged(ECheckBoxState CheckBoxState);`
- L165 _private prototype_ `ECheckBoxState IsShowingLastState() const;`
- L166 _private prototype_ `void OnShowLastStateChanged(ECheckBoxState CheckBoxState);`
- L168 _private prototype_ `bool TryUpdateTreeItems();`
- L169 _private prototype_ `bool UpdateTreeItems();`
- L170 _private prototype_ `bool UpdateTreeItems(const UGizmoElementGroupBase* InGroupElement, const TSharedPtr<FGizmoTreeElementViewModel>& InParentItem, TArray<TSharedPtr<FGizmoTreeElementViewModel>>& OutChildren);`
- L171 _private prototype_ `void GetTreeChildren(TSharedPtr<FGizmoTreeElementViewModel> InViewModel, TArray<TSharedPtr<FGizmoTreeElementViewModel>>& OutChildren);`
- L172 _private prototype_ `TSharedRef<ITableRow> GenerateTreeRow(TSharedPtr<FGizmoTreeElementViewModel> InViewModel, const TSharedRef<STableViewBase>& InOwnerTable);`
- L174 _private prototype_ `UInteractiveToolManager* GetToolManager() const;`
- L175 _private prototype_ `UEditorInteractiveGizmoManager* GetGizmoManager() const;`
- L178 _private member_ `TSharedPtr<SHeaderRow> HeaderRowWidget;`
- L179 _private member_ `TSharedPtr<STreeView<TSharedPtr<FGizmoTreeElementViewModel>>> TreeViewWidget;`
- L180 _private member_ `TArray<TSharedPtr<FName>> GizmoChoiceNames;`
- L181 _private member_ `bool bShowHiddenItems = false;`
- L182 _private member_ `bool bShowLastState = false;`
- L183 _private member_ `TArray<TSharedPtr<FGizmoTreeElementViewModel>> TreeItems;`
- L184 _private member_ `TSharedPtr<FGizmoTreeViewModel> ViewModel;`
- L185 _private member_ `TWeakObjectPtr<UTransformGizmo> WeakTransformGizmo;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/Behaviors/2DViewportBehaviorTargets.h` (Public)


#### class `FEditor2DScrollBehaviorTarget`  
`class FEditor2DScrollBehaviorTarget : public IClickDragBehaviorTarget`  
_L18-37_
- inherits: `IClickDragBehaviorTarget`
- desc: Allows click-dragging to move the camera in the XY plane.
- L22 _public prototype_ `FEditor2DScrollBehaviorTarget(FEditorViewportClient* ViewportClientIn);`
- L25 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget
- L26 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L27 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L28 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L29 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L34 _protected member_ `FEditorViewportClient* ViewportClient = nullptr;` — TODO: Replace with a context object to avoid dependency on FEditorViewportClient (JIRA UE-163677)
- L35 _protected member_ `FVector3d OriginalCameraLocation;`
- L36 _protected member_ `FVector3d DragStart;`

#### class `FEditor2DMouseWheelZoomBehaviorTarget`  
`class FEditor2DMouseWheelZoomBehaviorTarget : public IMouseWheelBehaviorTarget`  
_L43-78_
- inherits: `IMouseWheelBehaviorTarget`
- desc: Allows the mouse wheel to move the camera forwards/backwards relative to the XY plane, in the direction pointed to by the mouse.
- L47 _public prototype_ `FEditor2DMouseWheelZoomBehaviorTarget(FEditorViewportClient* ViewportClientIn);`
- L50 _public prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& CurrentPos);` — IMouseWheelBehaviorTarget
- L51 _public prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& CurrentPos);`
- L52 _public prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& CurrentPos);`
- L61 _public prototype_ `virtual void SetZoomAmount(double PercentZoomIn);` — @param PercentZoomIn How much to move forward on each mouse wheel forward scroll. For instance, passing 20 here will decrease the distance to the XY plane by 20% each time. The zoom out amount will be set in such a way that it undoes the same effect. For instance if 20 was passed here, zoom out amount will be 25% since zooming in by 20% and then out by 25% of the result gets you back to where you were.
- L62 _public prototype_ `void SetZoomLimits(double ZoomInLimitIn, double ZoomOutLimitIn);`
- L64 _public prototype_ `void SetCameraFarPlaneWorldZ(double CameraFarPlaneWorldZIn);`
- L65 _public prototype_ `void SetCameraNearPlaneProportionZ(double CameraFarPlaneProportionZIn );`
- L67 _public member_ `inline static const double DEFAULT_ZOOM_AMOUNT = 20;`
- L71 _protected member_ `FEditorViewportClient* ViewportClient = nullptr;` — TODO: Replace with a context object to avoid dependency on (JIRA UE-163677)
- L72 _protected member_ `double ZoomInProportion;`
- L73 _protected member_ `double ZoomOutProportion;`
- L74 _protected member_ `double ZoomInLimit;`
- L75 _protected member_ `double ZoomOutLimit;`
- L76 _protected member_ `double CameraFarPlaneWorldZ;`
- L77 _protected member_ `double CameraNearPlaneProportionZ;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/Behaviors/MultiButtonClickDragBehavior.h` (Public)


#### class `UMultiButtonClickDragBehavior`  
`class UMultiButtonClickDragBehavior : public UClickDragInputBehavior, public IClickDragBehaviorTarget`  
_L21-87_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UClickDragInputBehavior,IClickDragBehaviorTarget`
- L30 _public prototype_ `void Initialize();` — UClickDragInputBehavior  implementation
- L32 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L33 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InPressPos) override;`
- L34 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) override;`
- L35 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos) override;`
- L36 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L40 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& Input) override;`
- L41 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& Input, EInputCaptureSide Side) override;`
- L42 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& Input, const FInputCaptureData& Data) override;`
- L45 _public function_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& PressPos)> CanBeginClickDragFunc = [](const FInputDeviceRay&)` — lambda implementation of CanBeginClickDragSequence
- L45 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& PressPos)> CanBeginClickDragFunc = [](const FInputDeviceRay&) { return FInputRayHit(); };` — lambda implementation of CanBeginClickDragSequence
- L48 _public function_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickPressFunc = [](const FInputDeviceRay&)` — lambda implementation of OnClickPress
- L48 _public member_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickPressFunc = [](const FInputDeviceRay&) {};` — lambda implementation of OnClickPress
- L51 _public function_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickDragFunc = [](const FInputDeviceRay&)` — lambda implementation of OnClickDrag
- L51 _public member_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnClickDragFunc = [](const FInputDeviceRay&) {};` — lambda implementation of OnClickDrag
- L54 _public function_ `TUniqueFunction<void(const FInputDeviceRay& ReleasePos)> OnClickReleaseFunc = [](const FInputDeviceRay&)` — lambda implementation of OnClickRelease
- L54 _public member_ `TUniqueFunction<void(const FInputDeviceRay& ReleasePos)> OnClickReleaseFunc = [](const FInputDeviceRay&) {};` — lambda implementation of OnClickRelease
- L57 _public function_ `TUniqueFunction<void()> OnTerminateFunc = []()` — lambda implementation of OnTerminateDragSequence
- L57 _public member_ `TUniqueFunction<void()> OnTerminateFunc = []() {};` — lambda implementation of OnTerminateDragSequence
- L60 _public function_ `TUniqueFunction<void(const FInputDeviceState& Input)> OnStateUpdated = [](const FInputDeviceState&)` — lambda implementation of OnStateUpdated
- L60 _public member_ `TUniqueFunction<void(const FInputDeviceState& Input)> OnStateUpdated = [](const FInputDeviceState&) {};` — lambda implementation of OnStateUpdated
- L63 _public prototype_ `void EnableButton(const FKey& InButton);` — enable InButton so that in can be captured
- L66 _public prototype_ `void DisableButton(const FKey& InButton);` — disable InButton so that it's not captured
- L71 _protected prototype_ `bool IsAnyButtonDown(const FInputDeviceState& InInput);` — @return true if any captured button is down.
- L74 _protected prototype_ `bool DidAnyButtonChangeState(const FInputDeviceState& InInput) const;` — @return true if any captured button changed its bPressed/bReleased state.
- L77 _protected prototype_ `bool HandlesLeftMouseButton() const;` — @return true if left mouse button is handled.
- L80 _protected prototype_ `bool HandlesMiddleMouseButton() const;` — @return true if middle mouse button is handled.
- L83 _protected prototype_ `bool HandlesRightMouseButton() const;` — @return true if right mouse button is handled.
- L86 _protected member_ `uint8 CapturedInputs[3] = {0 ,0, 0};` — mouse buttons that need to be captured. Left=0, Middle=1, Right=2

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/Behaviors/SingleClickAndDragBehavior.h` (Public)


#### class `ISingleClickAndDragBehaviorTarget`  
`class ISingleClickAndDragBehaviorTarget : public IModifierToggleBehaviorTarget`  
_L17-57_
- inherits: `IModifierToggleBehaviorTarget`
- desc: Functions required to apply standard "Click" and "Click-Drag" state machines to a target object. Differs to SingleClickOrDragBehavior in that it provides a separate call sequence for click press and click release.
- L20 _public prototype_ `virtual ~ISingleClickAndDragBehaviorTarget() override = default;`
- L27 _public prototype_ `virtual FInputRayHit CanBeginSingleClickAndDragSequence(const FInputDeviceRay& InPressPos) = 0;` — Test if target can begin click-drag interaction at this point @param InPressPos device position/ray at click point @return hit information at this point
- L33 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InPressPos) = 0;` — Notify Target that click press ocurred @param InPressPos device position/ray at click point
- L39 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragPos) = 0;` — Notify Target that the drag process has started @param InPressPos device position/ray at move point
- L45 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) = 0;` — Notify Target that input position has changed @param InPressPos device position/ray at click point
- L51 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos, bool bInIsDragOperation) = 0;` — Notify Target that click release occurred @param InPressPos device position/ray at click point
- L56 _public prototype_ `virtual void OnTerminateSingleClickAndDragSequence() = 0;` — Notify Target that click-drag sequence has been explicitly terminated (eg by escape key)

#### class `USingleClickAndDragBehavior`  
`class USingleClickAndDragBehavior : public UAnyButtonInputBehavior`  
_L85-183_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAnyButtonInputBehavior`
- desc: USingleClickAndDragInputBehavior implements a combination of "button-click" and "button-click-drag"-style input behavior. If the mouse is moved away from the original location, and update will occur and a drag operation will start. If the mouse is released without moving too far away, a click event will occur. Once the drag has started, returning to the original location will not produce a click event will not be produced, but the drag operation will continue. NOTE: This differs from USingleClickOrDragInputBehavior in that it provides a separate call sequence for click and drag: Single Clicks: OnClickPress OnClickRelease Drag: OnDragStarted OnClickDrag An ISingleClickAndDragBehaviorTarget instance must be provided which is manipulated by this behavior. The state machine works as follows: 1) on input-device-button-press, call Target::CanBeginSingleClickDragSequence to determine if capture should begin 2) on input-device-move, call Target::OnClickDrag if drag mode has been started or Target::OnDragStart if it crosses that threshold. 3) on input-device-button-release, call Target::OnClickRelease If a ForceEndCapture occurs we call Target::OnTerminateDragClickSequence
- L93 _public prototype_ `virtual void Initialize(ISingleClickAndDragBehaviorTarget* InTarget);` — Set the targets for Click and Drag interactions
- L98 _public member_ `TFunction<bool(const FInputDeviceState&)> ModifierCheckFunc = nullptr;` — WantsCapture() will only return capture request if this function returns true (or is null)
- L100 _public prototype_ `virtual FInputCapturePriority GetPriority() override;`
- L101 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InInputState) override;`
- L102 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& InInputState, EInputCaptureSide InCaptureSide) override;`
- L103 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& InInputState, const FInputCaptureData& InCaptureData) override;`
- L104 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& InCaptureData) override;`
- L106 _public prototype_ `virtual FInputDeviceRay GetDeviceRay(const FInputDeviceState& InInputDeviceState) override;`
- L108 _public prototype_ `bool UsesUnboundedCursor() const;`
- L109 _public prototype_ `void SetUsesUnboundedCursor(TAttribute<bool> InUsesUnboundedCursor);`
- L111 _public prototype_ `void SetPendingDragPriority(TOptional<FInputCapturePriority> InPriority);`
- L117 _public member_ `FInputBehaviorModifierStates Modifiers;` — The modifier set for this behavior
- L121 _public member_ `bool bBeginDragIfClickTargetNotHit = true;` — `UPROPERTY()` — If true (default), then if the click-mouse-down does not hit a valid click target (determined by IClickBehaviorTarget::IsHitByClick), then the Drag will be initiated
- L126 _public member_ `float DragDistanceThreshold = 2.0;` — `UPROPERTY()` — If the device moves more than this distance in 2D (pixel?) units, the interaction switches from click to drag
- L132 _protected prototype_ `virtual void OnClickPressInternal(const FInputDeviceState& InInput, EInputCaptureSide InSide);` — Internal function that forwards click evens to Target::OnClickPress, you can customize behavior here
- L137 _protected prototype_ `virtual void OnDragStartedInternal(const FInputDeviceState& InInput, const FInputCaptureData& InData);` — Internal function that forwards click evens to Target::OnDragStarted, you can customize behavior here
- L142 _protected prototype_ `virtual void OnClickDragInternal(const FInputDeviceState& InInput, const FInputCaptureData& InData);` — Internal function that forwards click evens to Target::OnClickDrag, you can customize behavior here
- L147 _protected prototype_ `virtual void OnClickReleaseInternal(const FInputDeviceState& InInput, const FInputCaptureData& InData);` — Internal function that forwards click evens to Target::OnClickRelease, you can customize behavior here
- L150 _private prototype_ `void UpdateDragDistance(const FInputDeviceState& InInputState);`
- L153 _private member_ `ISingleClickAndDragBehaviorTarget* Target = nullptr;` — Click and Drag Target object.
- L156 _private member_ `TOptional<FInputDeviceRay> InitialMouseDownRay;` — The initial mouse down position.
- L159 _private member_ `TOptional<FInputCapturePriority> PendingDragPriority;` — When set, the drag priority used when mouse motion has not yet moved byond the minimum drag distance.
- L162 _private member_ `EInputCaptureSide CaptureSide;` — Device capture
- L165 _private member_ `bool bIsBeyondDragDistance = false;` — Updated to mark whether mouse movement has moved beyond drag distance
- L168 _private member_ `bool bIsDragging = false;` — set to true if we are in an active drag capture, eg after rejecting possible click
- L174 _private member_ `bool bHasActiveCapture = false;` — set to true between BeginCapture and capture end (release/force-end). Guards WantsCapture from resetting InitialMouseDownRay when called by CollectWantsCapture during active capture.
- L177 _private member_ `bool bImmediatelyBeginDragInBeginCapture = false;` — flag used to communicate between WantsCapture and BeginCapture
- L180 _private member_ `bool bImmediatelyClickInBeginCapture = false;` — flag used to communicate between WantsCapture and BeginCapture
- L182 _private member_ `TAttribute<bool> UseUnboundedCursor;`

#### class `ULocalSingleClickAndDragBehavior`  
`class ULocalSingleClickAndDragBehavior : public USingleClickAndDragBehavior, public ISingleClickAndDragBehaviorTarget`  
_L189-217_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USingleClickAndDragBehavior,ISingleClickAndDragBehaviorTarget`
- desc: A version of USingleCLickAndDragBehavior that allows for arbitrary function pointers to handle the ISingleClickAndDragBehaviorTarget callbacks.
- L199 _public prototype_ `virtual void Initialize(ISingleClickAndDragBehaviorTarget* InTarget) override;` — Initializes the behavior with a fallback target. Any null function pointers will fall back to the provided target.
- L200 _public prototype_ `virtual FInputRayHit CanBeginSingleClickAndDragSequence(const FInputDeviceRay& InPressPos) override;`
- L201 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& InPressPos) override;`
- L202 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragPos) override;`
- L203 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& InDragPos) override;`
- L204 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos, bool bInIsDragOperation) override;`
- L205 _public prototype_ `virtual void OnTerminateSingleClickAndDragSequence() override;`
- L208 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& InPressPos)> CanBeginSingleClickAndDragSequenceFunc = nullptr;`
- L209 _public member_ `TUniqueFunction<void(const FInputDeviceRay& InDragPos)> OnClickPressFunc = nullptr;`
- L210 _public member_ `TUniqueFunction<void(const FInputDeviceRay& InDragPos)> OnDragStartFunc = nullptr;`
- L211 _public member_ `TUniqueFunction<void(const FInputDeviceRay& InDragPos)> OnClickDragFunc = nullptr;`
- L212 _public member_ `TUniqueFunction<void(const FInputDeviceRay& InDragPos, bool bInIsDragOperation)> OnClickReleaseFunc = nullptr;`
- L213 _public member_ `TUniqueFunction<void()> OnTerminateSingleClickAndDragSequenceFunc = nullptr;`
- L216 _private member_ `ISingleClickAndDragBehaviorTarget* FallbackTarget = nullptr;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/Behaviors/ViewportClickBehavior.h` (Public)


#### class `IViewportClickBehaviorTarget`  
`class IViewportClickBehaviorTarget`  
_L13-46_
- L16 _public prototype_ `virtual ~IViewportClickBehaviorTarget() = default;`
- L23 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& PressPos) = 0;` — Test if target can begin the click interaction at this point @param PressPos device position/ray at click point @return hit information at this point
- L28 _public prototype_ `virtual void OnClickDown(const FInputDeviceRay& InClickPos) = 0;` — Notify the target that the click has started
- L33 _public prototype_ `virtual void OnClickUp(const FInputDeviceRay& InClickPos) = 0;` — Notify the target that the click has completed
- L38 _public prototype_ `virtual void OnStateUpdated(const FInputDeviceState& InInputDeviceState) = 0;` — Notify Target button state has changed
- L43 _public function_ `virtual void OnForceEndCapture()` — Notify Target that capture is ending

#### class `UViewportClickBehavior`  
`class UViewportClickBehavior : public UInputBehavior`  
_L50-83_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: A Click behavior designed to compete alongside UViewportClickDragBehaviors
- L55 _public prototype_ `virtual void Initialize(IViewportClickBehaviorTarget* InTarget);`
- L57 _public prototype_ `virtual FInputCapturePriority GetPriority() override;`
- L58 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InputState) override;`
- L59 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& InputState, EInputCaptureSide eSide) override;`
- L60 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& InputState, const FInputCaptureData& CaptureData) override;`
- L62 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& CaptureData) override;`
- L64 _public prototype_ `void SetBindings(const TArray<UE::Editor::ViewportInteractions::FButtonBinding>& InBindings);`
- L67 _public prototype_ `virtual FInputDeviceRay GetDeviceRay(const FInputDeviceState& InInputDeviceState);` — @return current 3D world ray and optional 2D position for Target Device
- L69 _public prototype_ `virtual const FVector2D& GetMousePosition(const FInputDeviceState& InInputDeviceState) const;`
- L72 _protected prototype_ `void OnStateUpdatedInternal(const FInputDeviceState& InInputDeviceState);`
- L73 _protected prototype_ `void OnClickDownInternal(const FInputDeviceState& InputState);`
- L74 _protected prototype_ `void OnClickUpInternal(const FInputDeviceState& InputState);`
- L76 _protected prototype_ `virtual TOptional<FInputCapturePriority> GetCapturePriority(UE::Editor::ViewportInteractions::EInputStage Stage, const FInputDeviceState& InputState) const;`
- L78 _protected member_ `IViewportClickBehaviorTarget* Target = nullptr;`
- L79 _protected member_ `UE::Editor::ViewportInteractions::FButtonBindings Bindings;`
- L81 _protected member_ `TOptional<FInputCapturePriority> CachedCapturePriority;`
- L82 _protected member_ `bool bIsClicking = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/Behaviors/ViewportClickDragBehavior.h` (Public)


#### class `IViewportClickDragBehaviorTarget`  
`class IViewportClickDragBehaviorTarget`  
_L13-75_
- L32 _public prototype_ `virtual ~IViewportClickDragBehaviorTarget() = default;`
- L39 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) = 0;` — Test if target can begin click-drag interaction at this point @param PressPos device position/ray at click point @return hit information at this point
- L45 _public function_ `virtual void OnBeginCapture(const FInputDeviceRay& InClickPressPos)` — Notify Target that capture has started @param InClickPressPos device position/ray at click press point
- L51 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) = 0;` — Notify Target that drag has started @param InDragStartPos device position/ray at drag start point
- L57 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) = 0;` — Notify Target that input position has changed @param DragPos device position/ray at click point
- L63 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) = 0;` — Notify Target that drag has ended @param InDragEndPos device position/ray at drag end point
- L69 _public prototype_ `virtual void OnStateUpdated(const FInputDeviceState& InInputDeviceState) = 0;` — Notify Target button state has changed @param InInputDeviceState current device position/ray
- L74 _public function_ `virtual void OnEndCapture(EEndCaptureReason InReason)` — Notify Target that capture has ended.

#### enum `IViewportClickDragBehaviorTarget::EEndCaptureReason`  
`enum class EEndCaptureReason`  
_L16-24_
- L19 _public enumerator_ `End` — Ended as part of normal operation, e.g. releasing a mouse button.
- L21 _public enumerator_ `Canceled` — Canceled by explicit user action, e.g. pressing Escape.
- L23 _public enumerator_ `Forced` — Canceled by the system.

#### struct `IViewportClickDragBehaviorTarget::FDragArgs`  
`struct FDragArgs`  
_L26-30_
- L28 _public member_ `FInputDeviceRay Ray;`
- L29 _public member_ `FVector2D ScreenDelta;`

#### class `UViewportClickDragBehavior`  
`class UViewportClickDragBehavior : public UInputBehavior`  
_L84-184_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInputBehavior`
- desc: A behavior dedicated to Viewport Drag Interactions, directly supporting threshold-based capture. It can be used when capture stealing e.g. a single click behavior. The IViewportClickDragBehaviorTarget of this behavior will receive OnDragStart and OnDragEnd when drag starts/ends, and not on actual button press/release
- L89 _public prototype_ `DECLARE_DELEGATE_RetVal(const UE::Editor::ViewportInteractions::FButtonBindings&, FGetBindingsDelegate);`
- L91 _public prototype_ `void Initialize(IViewportClickDragBehaviorTarget* InTarget);`
- L97 _public prototype_ `void SetDragConfirmedPriority(FInputCapturePriority InDragConfirmedPriority);` — Set the priority this Drag Behavior will return from GetPriority once the current interaction is confirmed to be a drag. Should be higher than its DefaultPriority, and higher than the priority of any other behavior it wants to steal capture from
- L99 _public prototype_ `virtual FInputCapturePriority GetPriority() override;`
- L101 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InputState) override;`
- L102 _public prototype_ `virtual FInputCaptureUpdate BeginCapture(const FInputDeviceState& InputState, EInputCaptureSide eSide) override;`
- L103 _public prototype_ `virtual FInputCaptureUpdate UpdateCapture(const FInputDeviceState& InputState, const FInputCaptureData& CaptureData) override;`
- L104 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& CaptureData) override;`
- L106 _public prototype_ `void SetBindings(const TArray<UE::Editor::ViewportInteractions::FButtonBinding>& InBindings);`
- L107 _public prototype_ `void SetBindings(const FGetBindingsDelegate& InDelegate);`
- L110 _public prototype_ `virtual FInputDeviceRay GetDeviceRay(const FInputDeviceState& InInputDeviceState);` — @return current 3D world ray and optional 2D position for Target Device
- L113 _public prototype_ `virtual const FVector2D& GetMousePosition(const FInputDeviceState& InInputDeviceState) const;` — Extract the current mouse position from the Input Device State
- L115 _public prototype_ `virtual bool UsesUnboundedCursor() const;`
- L120 _public prototype_ `void SetUsesUnboundedCursor(TAttribute<bool> InUsesUnboundedCursor);` — Call to set the default unbounded cursor attribute.
- L126 _public prototype_ `void SetRequireDistanceThresholdOnCapture(TAttribute<bool> InRequireDistanceThresholdOnCapture);` — Call to set whether drag starts should be contingent on the distance threshold when this behavior has capture. Default false. When false, this behavior will immediately start the drag operation when it wins capture.
- L131 _public prototype_ `void ResetDrag(const FInputDeviceState& InputState);` — Reset drag state and tracked drag distance. Calls OnDragEnd() but does not exit the behavior.
- L133 _public function_ `bool IsDragging() const`
- L134 _public function_ `FVector2D GetMouseDownPosition() const`
- L138 _protected prototype_ `virtual void OnDragStartInternal(const FInputDeviceState& InputState);`
- L139 _protected prototype_ `virtual void OnClickDragInternal( const FInputDeviceState& InputState, const FInputCaptureData& Data );`
- L142 _protected prototype_ `virtual void OnDragEndInternal( const FInputDeviceState& InputState, const FInputCaptureData& Data );`
- L146 _protected prototype_ `virtual void OnStateUpdatedInternal(const FInputDeviceState& InInputDeviceState);`
- L148 _protected prototype_ `bool HasMovedEnoughForDrag() const;`
- L149 _protected prototype_ `const UE::Editor::ViewportInteractions::FButtonBindings& GetBindings() const;`
- L150 _protected prototype_ `virtual TOptional<FInputCapturePriority> GetCapturePriority(UE::Editor::ViewportInteractions::EInputStage Stage, const FInputDeviceState& InputState) const;`
- L153 _protected member_ `float DragDistanceThreshold = 2.0f;` — Distance after which a drag is considered such
- L156 _protected member_ `FVector2D MouseDownPosition;` — Cached cursor position
- L158 _protected member_ `TOptional<float> MouseTraveledDistance;`
- L164 _protected member_ `FInputCapturePriority NoCapturePriority = FInputCapturePriority(INT32_MAX);` — This is essentially a hack. When this behavior knows it doesn't want an input event, it falls back to this priority. This works around behavioral awkwardness with how capture stealing is currently implemented.
- L170 _protected member_ `FInputCapturePriority DragConfirmedPriority;` — The priority this Drag Behavior will return from GetPriority once the current interaction is confirmed to be a drag. Should be higher than its DefaultPriority, and higher than the priority of any other behavior it wants to steal capture from
- L172 _protected member_ `IViewportClickDragBehaviorTarget* Target = nullptr;`
- L174 _protected member_ `UE::Editor::ViewportInteractions::FButtonBindings Bindings;`
- L175 _protected member_ `FGetBindingsDelegate GetBindingsDelegate;`
- L177 _protected member_ `TOptional<FInputCapturePriority> CachedCapturePriority;`
- L180 _protected member_ `bool bDragging = false;` — True when capturing and dragging
- L182 _protected member_ `TAttribute<bool> UnboundedCursor;`
- L183 _protected member_ `TAttribute<bool> RequireDistanceThresholdOnCapture;`

#### class `ULocalViewportClickDragBehavior`  
`class ULocalViewportClickDragBehavior : public UViewportClickDragBehavior , public IViewportClickDragBehaviorTarget`  
_L191-266_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportClickDragBehavior,IViewportClickDragBehaviorTarget`
- desc: An implementation of UViewportClickDragBehavior that also implements IViewportClickDragBehaviorTarget directly, using a set of local lambda functions.
- L201 _public function_ `virtual void Initialize()` — Call this to initialize the class
- L207 _public member_ `TUniqueFunction<FInputRayHit(const FInputDeviceRay& PressPos)> CanBeginClickDragFunc = [](const FInputDeviceRay&) { return FInputRayHit(); };` — lambda implementation of CanBeginClickDragSequence
- L208 _public function_ ``
- L213 _public member_ `TUniqueFunction<void(const FInputDeviceRay& PressPos)> OnDragStartFunc = [](const FInputDeviceRay&) { };` — lambda implementation of OnDragStart
- L218 _public member_ `TUniqueFunction<void(const FDragArgs& PressPos)> OnDragFunc = [](const FDragArgs&) { };` — lambda implementation of OnClickDrag
- L223 _public member_ `TUniqueFunction<void(const FInputDeviceRay& ReleasePos)> OnDragEndFunc = [](const FInputDeviceRay&) { };` — lambda implementation of OnDragEnd
- L228 _public member_ `TUniqueFunction<void(EEndCaptureReason)> OnEndCaptureFunc = [](EEndCaptureReason Reason) { };` — lambda implementation of OnTerminateDragSequence
- L233 _public member_ `TUniqueFunction<void(const FInputDeviceState& Input)> OnStateUpdatedFunc = [](const FInputDeviceState&) { };` — lambda implementation of OnStateUpdated
- L237 _public function_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override`
- L242 _public function_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override`
- L247 _public function_ `virtual void OnDrag(const FDragArgs& DragPos) override`
- L252 _public function_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override`
- L257 _public function_ `virtual void OnStateUpdated(const FInputDeviceState& InInputDeviceState) override`
- L262 _public function_ `virtual void OnEndCapture(EEndCaptureReason InReason) override`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L89 _delegate_ `DECLARE_DELEGATE_RetVal(const UE::Editor::ViewportInteractions::FButtonBindings&, FGetBindingsDelegate);`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/Behaviors/ViewportQuickToggleInputBehavior.h` (Public)


#### class `IQuickToggleBehaviorTarget`  
`class IQuickToggleBehaviorTarget : public IKeyInputBehaviorTarget`  
_L10-16_
- inherits: `IKeyInputBehaviorTarget`
- L13 _public prototype_ `virtual ~IQuickToggleBehaviorTarget() override = default;`
- L15 _public function_ `virtual void OnQuickToggle(const FKey& InKey)`

#### class `UViewportQuickToggleInputBehavior`  
`class UViewportQuickToggleInputBehavior : public UKeyInputBehavior`  
_L19-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UKeyInputBehavior`
- L24 _public function_ `UViewportQuickToggleInputBehavior()`
- L26 _public function_ `virtual EInputDevices GetSupportedDevices() override`
- L31 _public prototype_ `void Initialize(IQuickToggleBehaviorTarget* InTarget, const FKey& InKey);`
- L32 _public prototype_ `void Initialize(IQuickToggleBehaviorTarget* InTarget, const TArray<FKey>& InKeys);`
- L34 _public prototype_ `virtual FInputCaptureRequest WantsCapture(const FInputDeviceState& InputState) override;`
- L35 _public prototype_ `virtual bool WantsForceEndCapture() override;`
- L36 _public prototype_ `virtual void ForceEndCapture(const FInputCaptureData& CaptureData) override;`
- L38 _public prototype_ `virtual void OnKeyPressedInternal(const FInputDeviceState& Input) override;`
- L39 _public prototype_ `virtual void OnKeyReleasedInternal(const FInputDeviceState& Input) override;`
- L42 _public member_ `TFunction<bool(const FInputDeviceState&)> CanQuickToggleFunc = nullptr;` — Can be used to specify if this behavior target should receive OnQuickToggle events or not
- L45 _private function_ `virtual void Initialize(IKeyInputBehaviorTarget* InTarget, const FKey& InKey) override`
- L46 _private function_ `virtual void Initialize(IKeyInputBehaviorTarget* InTarget, const TArray<FKey>& InKeys) override`
- L48 _private prototype_ `bool CanQuickToggle(const FInputDeviceState& Input) const;`
- L50 _private member_ `IQuickToggleBehaviorTarget* QuickToggleTarget;`
- L52 _private member_ `TArray<double> KeyPressedTime;`
- L53 _private member_ `double QuickToggleDelay = 0.2f;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EdModeInteractiveToolsContext.h` (Public)
_(no declarations extracted)_

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorDragTools/BoxSelectInteraction.h` (Public)


#### class `UBoxSelectInteraction`  
`class UBoxSelectInteraction : public UMarqueeSelectInteraction`  
_L14-63_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UMarqueeSelectInteraction`
- L19 _public prototype_ `UBoxSelectInteraction();`
- L22 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L23 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InPressPos) override;`
- L24 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) override;`
- L25 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InReleasePos) override;`
- L29 _protected prototype_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override;`
- L40 _private prototype_ `static bool IntersectsBox(const UModel& InModel, int32 InNodeIndex, const FBox& InBox, bool bInUseStrictSelection);` — Returns true if the provided BSP node intersects with the provided frustum @param InModel				The model containing BSP nodes to check @param InNodeIndex				The index to a BSP node in the model.  This node is used for the bounds check. @param InBox			The frustum to check against. @param bInUseStrictSelection	true if the node must be entirely within the frustum
- L43 _private prototype_ `static void AddHoverEffect(AActor& InActor);` — Adds a hover effect to the passed in actor
- L46 _private prototype_ `static void AddHoverEffect(UModel& InModel, int32 InSurfIndex);` — Adds a hover effect to the passed in bsp surface
- L49 _private prototype_ `static void RemoveHoverEffect(AActor& InActor);` — Removes a hover effect from the passed in actor
- L52 _private prototype_ `static void RemoveHoverEffect(UModel& InModel, int32 InSurfIndex);` — Removes a hover effect from the passed in bsp surface
- L59 _private prototype_ `void CalculateBox(FBox& OutBox) const;` — Calculates a box to check actors against @param OutBox	The created box.
- L62 _private member_ `TArray<UModel*> ModelsToCheck;` — List of BSP models to check for selection

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorDragTools/DragToolInteraction.h` (Public)


#### class `UDragToolInteraction`  
`class UDragToolInteraction : public UViewportInteraction, public IViewportClickDragBehaviorTarget`  
_L51-108_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportInteraction,IViewportClickDragBehaviorTarget`
- desc: The base class that all drag tools inherit from. The drag tools implement special behaviors for the user clicking and dragging in a viewport.
- L56 _public prototype_ `UDragToolInteraction();`
- L58 _public prototype_ `virtual void Initialize(UViewportInteractionsBehaviorSource* const InViewportInteractionsBehaviorSource) override;`
- L61 _public function_ `bool IsDragging() const` — @return true if we are dragging
- L67 _public member_ `bool bConvertDelta;` — Does this drag tool need to have the mouse movement converted to the viewport orientation?
- L70 _public function_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override`
- L75 _public function_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override`
- L76 _public function_ `virtual void OnDrag(const FDragArgs& InDrag) override`
- L77 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L78 _public prototype_ `virtual void OnEndCapture(EEndCaptureReason InReason) override;`
- L79 _public prototype_ `virtual void OnStateUpdated(const FInputDeviceState& InInputDeviceState) override;`
- L82 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnToolStateChange);`
- L83 _public function_ `FOnToolStateChange& OnActivateTool()`
- L87 _public function_ `FOnToolStateChange& OnDeactivateTool()`
- L93 _protected prototype_ `virtual bool ShouldDraw(const EViewInteractionState InInteractionState);`
- L96 _protected member_ `FVector Start, End;` — The start/end location of the current drag.
- L96 _protected member_ `FVector Start, End;` — The start/end location of the current drag.
- L99 _protected member_ `bool bUseSnapping;` — If true, the drag tool wants to be passed grid snapped values.
- L101 _protected member_ `FInputDeviceState InputState;`
- L102 _protected member_ `bool bIsDragging;`
- L104 _protected member_ `FOnToolStateChange OnToolActivatedDelegate;`
- L105 _protected member_ `FOnToolStateChange OnToolDeactivatedDelegate;`
- L107 _protected member_ `IEditorViewportClientProxy* EditorViewportClientProxy;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L25 _namespace_ `namespace UE`
- L25 _namespace_ `namespace Editor` (scope `UE`)
- L25 _namespace_ `namespace DragTools` (scope `UE::Editor`)
- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEditorDragToolsToggleDelegate) DECLARE_MULTICAST_DELEGATE(FOnOnViewportChangeToolToggleDelegate) bool UseEditorDragTools();`
- L29 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnOnViewportChangeToolToggleDelegate) bool UseEditorDragTools();`
- L29 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnOnViewportChangeToolToggleDelegate) bool UseEditorDragTools();` (scope `UE::Editor::DragTools`)
- L36 _prototype_ `bool IsViewportChangeToolEnabled();` (scope `UE::Editor::DragTools`)
- L38 _prototype_ `FOnEditorDragToolsToggleDelegate& OnEditorDragToolsActivated();` (scope `UE::Editor::DragTools`)
- L39 _prototype_ `FOnEditorDragToolsToggleDelegate& OnEditorDragToolsDeactivated();` (scope `UE::Editor::DragTools`)
- L41 _prototype_ `FOnOnViewportChangeToolToggleDelegate& OnViewportChangeToolActivated();` (scope `UE::Editor::DragTools`)
- L42 _prototype_ `FOnOnViewportChangeToolToggleDelegate& OnViewportChangeToolDeactivated();` (scope `UE::Editor::DragTools`)
- L82 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnToolStateChange);`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorDragTools/EditorViewportClientProxy.h` (Public)


#### class `IEditorViewportClientProxy`  
`class IEditorViewportClientProxy : public TSharedFromThis<IEditorViewportClientProxy>`  
_L16-30_
- inherits: `TSharedFromThis<IEditorViewportClientProxy>`
- L19 _public prototype_ `virtual ~IEditorViewportClientProxy() = default;`
- L22 _public prototype_ `static IEditorViewportClientProxy* CreateViewportClientProxy(FEditorViewportClient* InViewportClient);` — `UE_DEPRECATED(5.7, "Please use the version taking UModeManagerInteractiveToolsContext* as argument")`
- L23 _public prototype_ `static IEditorViewportClientProxy* CreateViewportClientProxy(UModeManagerInteractiveToolsContext* InInteractiveToolsContext);`
- L25 _public prototype_ `virtual bool IsActorVisible(const AActor* InActor) const = 0;`
- L27 _public prototype_ `virtual const TArray<FName> GetHiddenLayers() const = 0;`
- L29 _public prototype_ `virtual FEditorViewportClient* GetEditorViewportClient() const = 0;`

#### class `FEditorViewportClientProxy`  
`class FEditorViewportClientProxy : public IEditorViewportClientProxy`  
_L32-43_
- inherits: `IEditorViewportClientProxy`
- L35 _public prototype_ `FEditorViewportClientProxy(UModeManagerInteractiveToolsContext* InInteractiveToolsContext);`
- L37 _public prototype_ `virtual bool IsActorVisible(const AActor* InActor) const override;`
- L38 _public prototype_ `virtual const TArray<FName> GetHiddenLayers() const override;`
- L39 _public prototype_ `virtual FEditorViewportClient* GetEditorViewportClient() const override;`
- L42 _private member_ `TWeakObjectPtr<UModeManagerInteractiveToolsContext> InteractiveToolsContextWeak;`

#### class `FLevelEditorViewportClientProxy`  
`class FLevelEditorViewportClientProxy : public IEditorViewportClientProxy`  
_L45-57_
- inherits: `IEditorViewportClientProxy`
- L48 _public prototype_ `FLevelEditorViewportClientProxy(UModeManagerInteractiveToolsContext* InInteractiveToolsContext);`
- L50 _public prototype_ `virtual bool IsActorVisible(const AActor* InActor) const override;`
- L51 _public prototype_ `virtual const TArray<FName> GetHiddenLayers() const override;`
- L52 _public prototype_ `virtual FEditorViewportClient* GetEditorViewportClient() const override;`
- L53 _public prototype_ `virtual FLevelEditorViewportClient* GetLevelEditorViewportClient() const;`
- L56 _private member_ `TWeakObjectPtr<UModeManagerInteractiveToolsContext> InteractiveToolsContextWeak;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorDragTools/FrustumSelectInteraction.h` (Public)


#### class `UFrustumSelectInteraction`  
`class UFrustumSelectInteraction : public UMarqueeSelectInteraction`  
_L24-60_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UMarqueeSelectInteraction`
- desc: Draws a box in the current viewport and when the mouse button is released, it selects/unselects everything inside of it.
- L29 _public prototype_ `UFrustumSelectInteraction();`
- L32 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L33 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InPressPos) override;`
- L34 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) override;`
- L35 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InReleasePos) override;`
- L39 _protected prototype_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override;`
- L50 _private prototype_ `static bool IntersectsFrustum(const UModel& InModel, int32 NodeIndex, const FConvexVolume& InFrustum, bool bUseStrictSelection);` — Returns true if the provided BSP node intersects with the provided frustum @param InModel				The model containing BSP nodes to check @param NodeIndex				The index to a BSP node in the model.  This node is used for the bounds check. @param InFrustum				The frustum to check against. @param bUseStrictSelection	true if the node must be entirely within the frustum
- L59 _private prototype_ `void CalculateFrustum(const FSceneView* InView, FConvexVolume& OutFrustum, bool bUseBoxFrustum) const;` — Calculates a frustum to check actors against @param InView			Information about scene projection @param OutFrustum		The created frustum @param bUseBoxFrustum	If true a frustum out of the current dragged box will be created.  false will use the view frustum.

#### struct `UE::EditorDragTools::FViewportFrustum`  
`struct FViewportFrustum`  
_L69-94_
- L79 _public prototype_ `FViewportFrustum(const FEditorViewportClient& InViewportClient, const FSceneView& InView, const FVector& InStart, const FVector& InEnd, const bool InUseBoxFrustum);` — @param InViewportClient	Information about the viewport client (view location) @param InView			Information about scene projection @param InStart			The 2D screen space start position of the dragged box @param InEnd				The 2D screen space end position of the dragged box @param InUseBoxFrustum	If true a frustum out of the current dragged box will be created (false will use the view frustum)
- L85 _public prototype_ `void Calculate(FConvexVolume& OutFrustum) const;` — @param OutFrustum		The created frustum
- L89 _private member_ `const FEditorViewportClient& ViewportClient;`
- L90 _private member_ `const FSceneView& View;`
- L91 _private member_ `const FVector& Start;`
- L92 _private member_ `const FVector& End;`
- L93 _private member_ `bool bUseBoxFrustum = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L62 _namespace_ `namespace UE`
- L62 _namespace_ `namespace EditorDragTools` (scope `UE`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorDragTools/MarqueeSelectInteraction.h` (Public)


#### class `UMarqueeSelectInteraction`  
`class UMarqueeSelectInteraction : public UDragToolInteraction`  
_L19-36_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDragToolInteraction`
- desc: Base class for tools that use a marquee selection behavior
- L24 _public prototype_ `UMarqueeSelectInteraction();`
- L26 _public prototype_ `virtual void Draw(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L33 _protected prototype_ `bool IsWindowSelection() const;` — @return Whether selection should only include items completely contained by the box.
- L35 _protected member_ `TWeakObjectPtr<UViewportClickDragBehavior> ClickDragInputBehavior;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorDragTools/MeasureToolInteraction.h` (Public)


#### class `UMeasureToolInteraction`  
`class UMeasureToolInteraction : public UDragToolInteraction`  
_L12-35_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDragToolInteraction`
- L17 _public prototype_ `UMeasureToolInteraction();`
- L19 _public prototype_ `virtual void Draw(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L22 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L23 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InPressPos) override;`
- L24 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) override;`
- L31 _private prototype_ `FVector2D GetSnappedPixelPos(FVector2D InPixelPos) const;` — Gets the world-space snapped position of the specified pixel position
- L34 _private member_ `FVector2D PixelStart, PixelEnd;` — Pixel-space positions for start and end
- L34 _private member_ `FVector2D PixelStart, PixelEnd;` — Pixel-space positions for start and end

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorDragTools/ViewportChangeInteraction.h` (Public)


#### class `UViewportChangeInteraction`  
`class UViewportChangeInteraction : public UDragToolInteraction`  
_L16-38_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UDragToolInteraction`
- L21 _public prototype_ `UViewportChangeInteraction();`
- L23 _public prototype_ `virtual void Draw(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) override;`
- L26 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L27 _public prototype_ `virtual void OnBeginCapture(const FInputDeviceRay& InClickPressPos) override;`
- L28 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InPressPos) override;`
- L29 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) override;`
- L30 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InReleasePos) override;`
- L34 _private prototype_ `ELevelViewportType GetDesiredViewportType() const;`
- L35 _private prototype_ `FText GetDesiredViewportTypeText() const;`
- L37 _private member_ `FVector2D ViewOptionOffset;`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorGizmoElementShared.h` (Public)


#### struct `FGizmoDebugSettings`  
`struct FGizmoDebugSettings`  
_L36-95_
- reflection: `USTRUCT(MinimalAPI)`
- L43 _public member_ `bool bDrawDebug = false;` — `UPROPERTY(meta = (AllowPrivateAccess = "true"))` — Corresponds with the CVar. Not user-exposed, only used for persitence.
- L47 _public member_ `bool bDrawGizmos = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Set to false to disable rendering of gizmos while still drawing any selected debug options.
- L50 _public member_ `bool bDrawTiming = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L53 _public member_ `bool bDrawSnapping = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L56 _public member_ `bool bDrawHitTarget = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L59 _public member_ `bool bDrawInteractionPlane = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L62 _public member_ `bool bDrawAlignedInteractionPlane = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L65 _public member_ `bool bDrawScreenPlane = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L68 _public member_ `bool bDrawInputDelta = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L72 _public member_ `bool bDrawLocalTransform = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Transform Axes
- L76 _public member_ `bool bDrawElementTransform = true;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Element Axes
- L79 _public member_ `bool bDrawCursor = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L82 _public member_ `bool bDrawCursorRay = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")`
- L86 _public member_ `bool bDrawInputCorrespondence = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Shows visuals to assist QA in debugging the relationship between input, and the resulting transform applied.
- L90 _public member_ `bool bFreezeCamera = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Freezes view-dependent transforms, so that you can navigate around and see how elements are positioned in screen space.
- L94 _public member_ `bool bFreezeDelta = false;` — `UPROPERTY(EditAnywhere, Category = "Debug")` — Shows the last delta visuals.

#### struct `FGizmoMaterialVariant`  
`struct FGizmoMaterialVariant`  
_L98-113_
- reflection: `USTRUCT()`
- L103 _public member_ `TObjectPtr<UMaterialInterface> Solid;` — `UPROPERTY()`
- L106 _public member_ `TObjectPtr<UMaterialInterface> Translucent;` — `UPROPERTY()`
- L108 _public function_ `bool operator==(const FGizmoMaterialVariant& InOther) const`

#### struct `FGizmoPerStateValueMaterialVariant`  
`struct FGizmoPerStateValueMaterialVariant`  
_L120-180_
- reflection: `USTRUCT(MinimalAPI, meta = (DisplayName = "Per-State Value (GizmoMaterialVariant)"))`
- desc: Used to store per-state (GizmoMaterialVariant) values for gizmo elements. ie. vertex color.
- L124 _public typedef_ `using FValueType = FGizmoMaterialVariant;`
- L131 _public member_ `TOptional<FGizmoMaterialVariant> Default;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Default value, used when the Interaction State is "None". Optional to allow explicit un-setting, implying inheritance or some other value source.
- L135 _public member_ `TOptional<FGizmoMaterialVariant> Hover;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when hovering.
- L139 _public member_ `TOptional<FGizmoMaterialVariant> Interact;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when interacting.
- L143 _public member_ `TOptional<FGizmoMaterialVariant> Select;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when selected.
- L147 _public member_ `TOptional<FGizmoMaterialVariant> Subdue;` — `UPROPERTY(EditAnywhere, Category = "Value")` — Value used when subdued.
- L150 _public prototype_ `const FGizmoMaterialVariant& GetValueForState(const EGizmoElementInteractionState InState) const;` — Get the value for the given Interaction State, or Default if not set.
- L153 _public prototype_ `const FGizmoMaterialVariant& GetDefaultValue() const;` — Get the Default value if set, otherwise FLinearColor::Transparent.
- L156 _public function_ `const FGizmoMaterialVariant& GetHoverValue() const` — Get the Hover value, or Default if not set.
- L159 _public function_ `const FGizmoMaterialVariant& GetInteractValue() const` — Get the Interact value, or Default if not set.
- L162 _public function_ `const FGizmoMaterialVariant& GetSelectValue() const` — Get the Select value, or Default if not set.
- L165 _public function_ `const FGizmoMaterialVariant& GetSubdueValue() const` — Get the Subdue value, or Default if not set.

#### struct `FGizmoStyleBase`  
`struct FGizmoStyleBase`  
_L184-266_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Contains Style/Visual properties common to all gizmo elements, ie. PixelHitDistanceThreshold.
- L189 _public member_ `static const FGizmoPerStateValueMaterialVariant DefaultMaterials;` — Default values, required when applying one style to another - where they'll only override destination values that are Default.
- L190 _public member_ `static const FGizmoPerStateValueLinearColor DefaultColors;`
- L191 _public member_ `static constexpr float DefaultMinLineThickness = 1.0f;`
- L192 _public member_ `static constexpr float DefaultLineThicknessMultiplier = 1.0f;`
- L193 _public member_ `static constexpr float DefaultHoverLineThicknessMultiplier = 1.5f;`
- L194 _public member_ `static const FGizmoPerStateValueMaterialVariant DefaultLineMaterials;`
- L195 _public member_ `static const FGizmoPerStateValueLinearColor DefaultLineColors;`
- L196 _public member_ `static constexpr float DefaultPixelHitDistanceThreshold = 7.0f;`
- L197 _public member_ `static constexpr float DefaultMinimumPixelHitDistanceThreshold = 0.0f;`
- L200 _public member_ `FGizmoPerStateValueMaterialVariant Materials = DefaultMaterials;` — `UPROPERTY()`
- L203 _public member_ `FGizmoPerStateValueLinearColor Colors = DefaultColors;` — `UPROPERTY(EditAnywhere, Category = "Style", meta = (DisplayPriority = -100))`
- L206 _public member_ `FGizmoPerStateValueMaterialVariant LineMaterials = DefaultLineMaterials;` — `UPROPERTY()`
- L209 _public member_ `FGizmoPerStateValueLinearColor LineColors = DefaultLineColors;` — `UPROPERTY(EditAnywhere, Category = "Style", meta = (DisplayPriority = -100))`
- L213 _public member_ `float MinLineThickness = DefaultMinLineThickness;` — `UPROPERTY()` — Used to prevent sub-pixel line sizes.
- L216 _public member_ `float LineThicknessMultiplier = DefaultLineThicknessMultiplier;` — `UPROPERTY()`
- L219 _public member_ `float HoverLineThicknessMultiplier = DefaultHoverLineThicknessMultiplier;` — `UPROPERTY()`
- L223 _public member_ `float PixelHitDistanceThreshold = DefaultPixelHitDistanceThreshold;` — `UPROPERTY(EditAnywhere, Category = "Style", AdvancedDisplay, meta = (ClampMin = 0, UIMin = 0, UIMax = 50))` — Pixel hit distance threshold - where the default is generally 7px.
- L227 _public member_ `float MinimumPixelHitDistanceThreshold = DefaultMinimumPixelHitDistanceThreshold;` — `UPROPERTY(EditAnywhere, Category = "Style", AdvancedDisplay, meta = (ClampMin = 0, UIMin = 0, UIMax = 50))` — Minimum pixel hit distance threshold.
- L230 _public member_ `TOptional<float> SizeCoefficient;` — `UPROPERTY()`
- L236 _public function_ `static void ApplyTo(const FromType& InFrom, ToType& InTo)`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L19 _namespace_ `namespace UE`
- L19 _namespace_ `namespace Editor` (scope `UE`)
- L19 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L21 _prototype_ `void ApplyMaterialsToElement(UGizmoElementBase* InElement, const FGizmoPerStateValueMaterialVariant& InMaterials);` (scope `UE::Editor::InteractiveToolsFramework`)
- L23 _prototype_ `void ApplyMaterialOverrides(FGizmoMaterialVariant& InMaterialToOverride, const FGizmoMaterialVariant& InMaterialToOverrideFrom);` (scope `UE::Editor::InteractiveToolsFramework`)
- L26 _prototype_ `void ApplyMaterialOverrides(FGizmoPerStateValueMaterialVariant& InMaterialsToOverride, const FGizmoPerStateValueMaterialVariant& InMaterialsToOverrideFrom);` (scope `UE::Editor::InteractiveToolsFramework`) — Overrides materials in MaterialsToOverride with those in MaterialsToOverrideFrom, if set.
- L28 _prototype_ `void ApplyColorsToElement(UGizmoElementBase* InElement, const FGizmoPerStateValueLinearColor& InColors);` (scope `UE::Editor::InteractiveToolsFramework`)
- L30 _prototype_ `void ApplyColorsToElement(UGizmoElementLineBase* InElement, const FGizmoPerStateValueLinearColor& InColors);` (scope `UE::Editor::InteractiveToolsFramework`)
- L32 _prototype_ `void ApplyColorOverrides(FGizmoPerStateValueLinearColor& InColorsToOverride, const FGizmoPerStateValueLinearColor& InColorsToOverrideFrom);` (scope `UE::Editor::InteractiveToolsFramework`)
- L167 _function_ `friend bool operator==(const FGizmoPerStateValueMaterialVariant& InLeft, const FGizmoPerStateValueMaterialVariant& InRight)`
- L176 _function_ `friend bool operator!=(const FGizmoPerStateValueMaterialVariant& InLeft, const FGizmoPerStateValueMaterialVariant& InRight)`
- L249 _function_ `friend bool operator==(const FGizmoStyleBase& InLeft, const FGizmoStyleBase& InRight)`
- L262 _function_ `friend bool operator!=(const FGizmoStyleBase& InLeft, const FGizmoStyleBase& InRight)`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorGizmoStateTarget.h` (Public)


#### class `UEditorGizmoStateTarget`  
`class UEditorGizmoStateTarget : public UObject, public IGizmoStateTarget`  
_L26-88_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,IGizmoStateTarget`
- desc: UEditorGizmoStateTarget
- L34 _public prototype_ `virtual void BeginUpdate() override;` — BeginUpdate is called before the gizmo starts modifying the transform.
- L39 _public prototype_ `virtual void EndUpdate() override;` — EndUpdate is called after the gizmo finished modifying the transform.
- L44 _public prototype_ `virtual void CancelUpdate() override;` — CancelUpdate is called if a gizmo cancels a modification.
- L49 _public member_ `TWeakPtr<FEditorModeTools> WeakModeTools;` — TWeakPtr to mode manager to interface with
- L54 _public member_ `FText TransactionDescription;` — Localized text description of the transaction (used if TransactionManager is not null)
- L60 _public member_ `TScriptInterface<IToolContextTransactionProvider> TransactionManager;` — `UPROPERTY()` — Pointer to the GizmoManager or ToolManager that is used to open/close the transaction (if no Begin/End functions is provided by BeginUpdate)
- L68 _public prototype_ `static UEditorGizmoStateTarget* Construct( FEditorModeTools* InModeManager, const FText& InDescription, IToolContextTransactionProvider* TransactionManagerIn, UObject* Outer = (UObject*)GetTransientPackage());` — Create and initialize an standard instance of UGizmoEditorStateTarget @param InModeManager the context object this StateTarget will retrieve the mode manager from @param InDescription Localized text description of the transaction (if no Begin/End functions is provided by BeginUpdate) @param TransactionManagerIn pointer to the object to manage transactions (if no Begin/End functions is provided by BeginUpdate)
- L77 _public prototype_ `void SetTransformGizmo(UTransformGizmo* InGizmo);` — Sets the transform gizmo from which we can get data if required.
- L81 _protected prototype_ `EGizmoTransformMode GetTransformMode() const;` — Gets the current TransformMode, from the associated TransformGizmo (if available).
- L87 _protected member_ `TWeakObjectPtr<UTransformGizmo> TransformGizmo;` — The transform gizmo from which we can get data if required.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorTRSGizmo.h` (Public)


#### struct `UE::Editor::InteractiveToolsFramework::TNudgeDelta`  
`template<typename DeltaType> struct TNudgeDelta`  
_L80-84_
- L82 _public member_ `DeltaType Delta;`
- L83 _public member_ `EAxisList::Type Axis = EAxisList::None;`

#### class `UEditorTRSGizmo`  
`class UEditorTRSGizmo : public UEditorTransformGizmo , public ISingleClickAndDragBehaviorTarget , public IKeyInputBehaviorTarget`  
_L90-1027_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorTransformGizmo,ISingleClickAndDragBehaviorTarget,IKeyInputBehaviorTarget`
- L105 _public prototype_ `virtual void Setup() override;` — UInteractiveGizmo overrides
- L106 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L107 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L108 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L111 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;` — IHoverBehaviorTarget implementation
- L112 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L113 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L114 _public prototype_ `virtual void OnEndHover() override;`
- L117 _public prototype_ `virtual FInputRayHit CanBeginSingleClickAndDragSequence(const FInputDeviceRay& InPressPos) override;`
- L118 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L119 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragPos) override;`
- L120 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L121 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& InReleasePos, bool bInIsDragOperation) override;`
- L122 _public prototype_ `virtual void OnTerminateSingleClickAndDragSequence() override;`
- L126 _public prototype_ `virtual void OnKeyPressed(const FKey& KeyID) override;`
- L127 _public prototype_ `virtual void OnKeyReleased(const FKey& KeyID) override;`
- L128 _public prototype_ `virtual void OnForceEndCapture() override;`
- L132 _public prototype_ `virtual void OnUpdateModifierState(int ModifierID, bool bIsOn) override;`
- L137 _private prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;` — The IClickDragBehaviorTarget functions are not used
- L138 _private prototype_ `virtual void OnTerminateDragSequence() override;`
- L142 _public prototype_ `virtual void BeginTransformEditSequence() override;`
- L143 _public prototype_ `virtual void EndTransformEditSequence() override;`
- L145 _public prototype_ `const FTransformGizmoStyle& GetStyle() const;`
- L148 _public prototype_ `void SetStyle(const FTransformGizmoStyle& InStyle);` — Sets and applies the given Style.
- L151 _public prototype_ `void SetGizmoViewContext(UGizmoViewContext* InGizmoViewContext);` — Sets the Gizmo view context, needed for screen space interactions
- L156 _public prototype_ `virtual void HandleWidgetModeChanged(UE::Widget::EWidgetMode InWidgetMode) override;` — Handle widget mode changed.
- L161 _public prototype_ `virtual void OnParametersChanged(const FGizmosParameters& InParameters) override;` — Handle user parameters changes
- L167 _public member_ `FTransformGizmoStyle Style;` — `UPROPERTY()` — Style contains various uniform and varying properties that affect the appearance of this gizmo.
- L171 _public member_ `FTransformGizmoInteraction Interaction;` — `UPROPERTY()` — Interaction contains various user-defined options for gizmo interaction.
- L175 _public member_ `TObjectPtr<UGizmoDebugProvider> DebugProvider;` — `UPROPERTY()` — Debug Info provider
- L179 _public member_ `FVector2D InteractionPlanarStartPoint2D;` — `UPROPERTY()`
- L183 _public member_ `FVector2D InteractionPlanarCurrPoint2D;` — `UPROPERTY()`
- L187 _public member_ `FVector2D InteractionScreenObjectPos2D;` — `UPROPERTY()`
- L190 _public member_ `double InteractionPlanarStartDistance = 0.0;` — `UPROPERTY()`
- L193 _public member_ `double InteractionPlanarCurrDistance = 0.0;` — `UPROPERTY()`
- L197 _public member_ `double InteractionDeltaDivisor;` — `UPROPERTY()`
- L200 _public member_ `double InteractionReferencePointOffsetDistance = 0.0;` — `UPROPERTY()`
- L204 _public member_ `double AlignedInteractionAngleOffset = 0.0;` — `UPROPERTY()` — The difference between the angle in screen-space vs. world-space, if applicable.
- L208 _public member_ `FVector AlignedInteractionPlanarNormal = FVector::ZeroVector;` — `UPROPERTY()` — The normal direction of the current axis, which may or may not be the same as InteractionPlanarNormal.
- L212 _public member_ `FVector InteractionDelta = FVector::ZeroVector;` — `UPROPERTY()` — Store accumulatively applied delta.
- L215 _public member_ `FVector InteractionBidirection = FVector::ZeroVector;` — `UPROPERTY()`
- L218 _public member_ `UE::Math::TIntVector3<int8> ViewToAlignedSign = UE::Math::TIntVector3<int8>(1);` — Used to translate interaction direction to aligned (accounts for flipping, etc.)
- L221 _public member_ `FVector2D InteractionBidirection2D = FVector2D::ZeroVector;` — `UPROPERTY()`
- L225 _public member_ `double InteractionStartSign = 1.0;` — `UPROPERTY()` — Initial sign of the interaction, if applicable.
- L238 _protected member_ `TObjectPtr<ULocalViewportClickDragBehavior> IndirectClickDragBehavior;` — `UPROPERTY()`
- L246 _protected member_ `TObjectPtr<UGizmoElementTranslateGroup> TranslateGroupElement;` — `UPROPERTY()` — Translate Axis, Plane and ScreenSpace Group.
- L250 _protected member_ `TObjectPtr<UGizmoElementRotateAxisSet> RotateAxisSetElement;` — `UPROPERTY()` — Rotate Axis Group.
- L254 _protected member_ `TObjectPtr<UGizmoElementRotateAxis> RotateXGimbalElement2;` — `UPROPERTY()` — Gimbal Rotate X Axis
- L258 _protected member_ `TObjectPtr<UGizmoElementRotateAxis> RotateYGimbalElement2;` — `UPROPERTY()` — Gimbal Rotate Y Axis
- L262 _protected member_ `TObjectPtr<UGizmoElementRotateAxis> RotateZGimbalElement2;` — `UPROPERTY()` — Gimbal Rotate Z Axis
- L266 _protected member_ `TObjectPtr<UGizmoElementRotateAxis> RotateScreenSpaceElement2;` — `UPROPERTY()` — Rotate screen space circle
- L270 _protected member_ `TObjectPtr<UGizmoElementScaleGroup> ScaleGroupElement;` — `UPROPERTY()` — Scale Axis & Plane Group.
- L275 _protected prototype_ `TSharedPtr<SWidget> GetCursorWidget(const ETransformGizmoPartIdentifier InHitPartId) const;`
- L277 _protected prototype_ `float GetCursorRotation() const;`
- L279 _protected prototype_ `void UpdateCursorRotation(const FInputDeviceRay& InPressPos);`
- L280 _protected prototype_ `void UpdateCursor(const EGizmoElementInteractionState InState, const ETransformGizmoPartIdentifier InHitPartId, const bool bIsExitingState = false);`
- L283 _protected prototype_ `void DrawDebug(FCanvas* InCanvas, IToolsContextRenderAPI* RenderAPI, const double InPixelToWorldScale);` — Renders various debug visualizations, if enabled. Canvas is only valid when called from DrawHUD.
- L286 _protected prototype_ `virtual void SetupBehaviors() override;` — Setup behaviors
- L289 _protected prototype_ `virtual void SetupIndirectBehaviors() override;` — Setup indirect behaviors
- L292 _protected prototype_ `virtual void SetupMaterials() override;` — Setup materials
- L295 _protected prototype_ `virtual void SetupOnClickFunctions() override;` — Setup on click functions
- L298 _protected prototype_ `virtual void UpdateMode() override;` — Update current gizmo mode based on transform source
- L301 _protected prototype_ `virtual void UpdateRotationMode() override;` — Update current gizmo rotation mode (default or gimbal)
- L304 _protected prototype_ `virtual void EnableMode(EGizmoTransformMode InGizmoMode, EAxisList::Type InAxisListToDraw) override;` — Enable the given mode with the specified axes, EAxisList::Type::None will hide objects associated with mode
- L307 _protected prototype_ `virtual void EnableTranslate(EAxisList::Type InAxisListToDraw) override;` — Enable translate using specified axis list
- L310 _protected prototype_ `virtual void EnableRotate(EAxisList::Type InAxisListToDraw) override;` — Enable rotate using specified axis list
- L313 _protected prototype_ `virtual void EnableScale(EAxisList::Type InAxisListToDraw) override;` — Enable scale using specified axis list
- L316 _protected prototype_ `virtual UGizmoElementTranslateGroup* MakeTranslateGroup(const EAxisList::Type InAxisList);` — Construct translate group. AxisList should be XYZ or LUF, not the subset of axis' being currently edited.
- L319 _protected prototype_ `virtual void UpdateTranslateGroup(UGizmoElementTranslateGroup* InElement);` — Updates the given translate group with the current parameters (ie. size coefficient)
- L322 _protected prototype_ `virtual UGizmoElementScaleGroup* MakeScaleGroup(const EAxisList::Type InAxisList);` — Construct scale group. AxisList should be XYZ or LUF, not the subset of axis' being currently edited.
- L325 _protected prototype_ `virtual void UpdateScaleGroup(UGizmoElementScaleGroup* InElement);` — Updates the given scale group with the current parameters (ie. size coefficient)
- L328 _protected prototype_ `virtual UGizmoElementTorus* MakeRotateAxis(ETransformGizmoPartIdentifier InPartId, const FVector& TorusAxis0, const FVector& TorusAxis1, UMaterialInterface* InMaterial);` — Construct rotate axis handle
- L331 _protected prototype_ `virtual void UpdateRotateAxis(UGizmoElementTorus* InElement) override;` — Updates the given rotate axis handle with the current parameters (ie. size coefficient)
- L334 _protected prototype_ `virtual UGizmoElementRotateAxisSet* MakeRotateAxisSet(const EAxisList::Type InAxisList);` — Construct rotate axis set. AxisList should be XYZ or LUF, not the subset of axis' being currently edited.
- L337 _protected prototype_ `virtual void UpdateRotateAxisSet(UGizmoElementRotateAxisSet* InElement);` — Updates the given rotate axis set with the current parameters (ie. size coefficient)
- L340 _protected prototype_ `UGizmoElementRotateAxis* MakeRotateAxis(const ETransformGizmoPartIdentifier InPartId, const EAxis::Type InAxis);` — Construct rotate axis.
- L343 _protected prototype_ `virtual UGizmoElementTorus* MakeRotateAxis(ETransformGizmoPartIdentifier InPartId, const FVector& TorusAxis0, const FVector& TorusAxis1, UMaterialInterface* InMaterial, UMaterialInterface* InCurrentMaterial) override;` — Construct rotate axis.
- L347 _protected prototype_ `virtual void UpdateRotateAxis(UGizmoElementRotateAxis* InElement, const EAxis::Type InAxis);` — Updates the given rotate axis with the current parameters (ie. size coefficient).
- L350 _protected prototype_ `virtual UGizmoElementArc* MakeRotateAxisArc(ETransformGizmoPartIdentifier InPartId, const FVector& InAxis0, const FVector& InAxis1, UMaterialInterface* InMaterial);` — Construct rotate axis arc handle
- L353 _protected prototype_ `virtual void UpdateRotateAxisArc(UGizmoElementArc* InElement, UMaterialInterface* InMaterial);` — Updates the given rotate axis arc handle with the current parameters (ie. size coefficient)
- L356 _protected prototype_ `virtual UGizmoElementCircle* MakeArcballCircleHandle(ETransformGizmoPartIdentifier InPartId, float InRadius, const FLinearColor& InColor) override;` — Construct arcball screen space handle
- L359 _protected prototype_ `virtual void UpdateArcballCircleHandle(UGizmoElementCircle* InElement);` — Updates the given arcball handle with the current parameters (ie. size coefficient)
- L362 _protected prototype_ `virtual UGizmoElementRotateAxis* MakeRotateScreenSpaceHandle();` — Construct rotate screen space handle
- L365 _protected prototype_ `virtual void UpdateRotateScreenSpaceHandle(UGizmoElementRotateAxis* InElement);` — Updates the given rotate screen space handle with the current parameters (ie. size coefficient)
- L368 _protected prototype_ `void UpdateElement(UGizmoElementBase* InElement, const TOptional<FGizmoStyleBase>& InStyle = TOptional<FGizmoStyleBase>());` — Updates the given element with properties common to all.
- L371 _protected prototype_ `virtual void UpdateElements() override;` — Updates all gizmo elements based on current parameters
- L374 _protected prototype_ `virtual FTransform GetGizmoTransform() const override;` — Get gizmo transform based on cached current transform.
- L377 _protected prototype_ `virtual void UpdateMaterials();` — Updated referenced materials according to current parameters.
- L380 _protected prototype_ `virtual FInputRayHit UpdateHoveredPart(const FInputDeviceRay& DevicePos) override;` — Determine hit part and update hover state based on current input ray
- L383 _protected prototype_ `virtual bool GetRayParamIntersectionWithInteractionPlane(const FInputDeviceRay& InRay, FVector::FReal& OutHitParam) override;` — Return true if input ray intersects current interaction plane and return param along ray in OutHitParam
- L386 _protected prototype_ `virtual bool GetRayParamIntersectionWithPlane(const FRay& InRay, const FVector& InPlaneOrigin, const FVector& InPlaneNormal, FVector::FReal& OutHitParam);` — Return true if input ray intersects the given plane and return param along ray in OutHitParam
- L389 _protected prototype_ `virtual void UpdateHoverState(const bool bInHover, const ETransformGizmoPartIdentifier InPartId) override;` — Update hover state for given part id
- L392 _protected prototype_ `virtual void UpdateInteractingState(const bool bInInteracting, const ETransformGizmoPartIdentifier InPartId, const bool bIdOnly = false) override;` — Update interacting state for given part id
- L395 _protected prototype_ `virtual void ResetInteractingStates(const EGizmoTransformMode InMode) override;` — Reset all interacting states related to the transform mode to false
- L398 _protected prototype_ `virtual void UpdateSelectedState(const bool bInSelected, const ETransformGizmoPartIdentifier InPartId, const bool bIdOnly = false);` — Update selected state for given part id
- L401 _protected prototype_ `void ResetSelectedStates(const EGizmoTransformMode InMode);` — Reset all selected states related to the transform mode to false
- L404 _protected prototype_ `virtual void UpdateSubdueState(const bool bInSubdued, const ETransformGizmoPartIdentifier InPartId, const bool bIdOnly = false);` — Update subdued state for given part id
- L407 _protected prototype_ `void ResetSubdueStates(const EGizmoTransformMode InMode);` — Reset all subdued states related to the transform mode to false
- L410 _protected prototype_ `void EndDeltas();` — Ends all Delta states/visuals.
- L417 _protected prototype_ `virtual void OnClickPressAxis(const FInputDeviceRay& PressPos) override;` — Handle click press for translate axes
- L420 _protected prototype_ `void OnDragStartTranslateAxis(const FInputDeviceRay& PressPos);` — Handle drag start for translate axes
- L423 _protected prototype_ `virtual void OnClickDragTranslateAxis(const FInputDeviceRay& DragPos) override;` — Handle click drag for translate axes
- L426 _protected prototype_ `virtual void OnClickReleaseTranslateAxis(const FInputDeviceRay& ReleasePos) override;` — Handle click release for translate axes
- L432 _protected prototype_ `virtual void OnClickPressTranslatePlanar(const FInputDeviceRay& PressPos) override;`
- L435 _protected prototype_ `virtual void OnClickDragTranslatePlanar(const FInputDeviceRay& DragPos) override;` — Handle click drag for translate planar
- L438 _protected prototype_ `virtual void OnClickReleaseTranslatePlanar(const FInputDeviceRay& ReleasePos) override;` — Handle click release for translate planar
- L445 _protected prototype_ `virtual void OnClickPressScreenSpaceTranslate(const FInputDeviceRay& PressPos) override;` — Handle click press for screen-space translate
- L448 _protected prototype_ `virtual void OnClickDragScreenSpaceTranslate(const FInputDeviceRay& DragPos) override;` — Handle click drag for screen-space translate
- L451 _protected prototype_ `virtual void OnClickReleaseScreenSpaceTranslate(const FInputDeviceRay& ReleasePos) override;` — Handle click release for screen-space translate
- L458 _protected prototype_ `virtual void OnClickPressRotateAxis(const FInputDeviceRay& InPressPos) override;` — Handle click press for any rotate axis
- L461 _protected prototype_ `virtual void OnClickDragRotateAxis(const FInputDeviceRay& InDragPos) override;` — Handle click drag for rotate axis
- L464 _protected prototype_ `virtual void OnClickReleaseRotateAxis(const FInputDeviceRay& InReleasePos) override;` — Handle click release for rotate axes
- L467 _protected prototype_ `bool OnClickPressRotateArc( const FInputDeviceRay& InPressPos, const FVector& InPlaneNormal, const FVector& InPlaneAxis1, const FVector& InPlaneAxis2, const EAxis::Type InAxis = EAxis::None);` — Prepares data for arc rotation. This will return false if this is not possible (the rotate handle is perpendicular to the view)
- L471 _protected prototype_ `virtual double ComputeAxisRotateDeltaAngle(const FVector2D& InStartPos, const FInputDeviceRay& InDragPos) override;` — Compute angle (degrees) delta based on screen-space start/end positions. Intended to be used in combination with ComputeAxisRotateDelta
- L474 _protected prototype_ `virtual FQuat ComputeGimbalRotateDelta(const FVector2D& InStartPos, const FVector2D& InEndPos, const double InAngleSign = 1.0) override;` — Compute gimbal rotate delta based on screen-space start/end positions
- L476 _protected prototype_ `virtual FVector GetGimbalRotationAxis(const int32 InAxis) const override;`
- L480 _protected prototype_ `virtual FVector2D GetScreenGimbalRotateAxisDir(const FInputDeviceRay& InPressPos) override;` — Get screen-space axis for gimbal rotation drag
- L484 _protected prototype_ `virtual FVector2D GetScreenRotateAxisDir(const FInputDeviceRay& InPressPos) override;` — Get screen-space axis for rotation drag
- L492 _protected prototype_ `virtual void OnClickPressGimbalRotateAxis(const FInputDeviceRay& InPressPos) override;` — Handle click press for any gimbal rotate axis
- L495 _protected prototype_ `virtual void OnClickDragGimbalRotateAxis(const FInputDeviceRay& InDragPos) override;` — Handle click drag for gimbal rotate axis
- L502 _protected prototype_ `virtual void OnClickPressScreenSpaceRotate(const FInputDeviceRay& PressPos) override;` — Handle click press for screen-space rotate
- L505 _protected prototype_ `virtual void OnClickDragScreenSpaceRotate(const FInputDeviceRay& InDragPos) override;` — Handle click drag for screen-space rotate
- L508 _protected prototype_ `virtual void OnClickReleaseScreenSpaceRotate(const FInputDeviceRay& ReleasePos) override;` — Handle click release for screen-space rotate
- L515 _protected prototype_ `virtual void OnClickPressArcBallRotate(const FInputDeviceRay& PressPos) override;` — Handle click press for arc ball rotate
- L518 _protected prototype_ `virtual void OnClickDragArcBallRotate(const FInputDeviceRay& DragPos) override;` — Handle click drag for arc ball rotate
- L525 _protected prototype_ `virtual void OnClickPressScaleXAxis(const FInputDeviceRay& PressPos) override;` — Handle click press for scale X axis
- L528 _protected prototype_ `virtual void OnClickPressScaleYAxis(const FInputDeviceRay& PressPos) override;` — Handle click press for scale Y axis
- L531 _protected prototype_ `virtual void OnClickPressScaleZAxis(const FInputDeviceRay& PressPos) override;` — Handle click press for scale Z axis
- L534 _protected prototype_ `virtual void OnClickPressScaleXYPlanar(const FInputDeviceRay& PressPos) override;` — Handle click press for scale XY planar
- L537 _protected prototype_ `virtual void OnClickPressScaleYZPlanar(const FInputDeviceRay& PressPos) override;` — Handle click press for scale YZ planar
- L540 _protected prototype_ `virtual void OnClickPressScaleXZPlanar(const FInputDeviceRay& PressPos) override;` — Handle click press for scale XZ planar
- L543 _protected prototype_ `virtual void OnClickPressScalePlanar(const FInputDeviceRay& PressPos);` — Handle click press for scale planar
- L546 _protected prototype_ `virtual void OnClickPressScale(const FInputDeviceRay& PressPos) override;` — Handle click press for all scale methods
- L549 _protected prototype_ `virtual void OnClickDragScale(const FInputDeviceRay& DragPos) override;` — Handle click drag for all scale
- L552 _protected prototype_ `virtual void OnClickReleaseScaleAxis(const FInputDeviceRay& ReleasePos) override;` — Handle click release for scale axes
- L555 _protected prototype_ `virtual void OnClickReleaseScalePlanar(const FInputDeviceRay& ReleasePos) override;` — Handle click release for scale planar
- L558 _protected prototype_ `virtual void OnClickReleaseScaleXYZ(const FInputDeviceRay& ReleasePos) override;` — Handle click release for uniform scale
- L561 _protected prototype_ `virtual FVector ComputeScaleDelta(const FVector2D& InStartPos, const FVector2D& InEndPos, FVector2D& OutScreenDelta) override;` — Compute scale delta based on screen space start/end positions
- L563 _protected prototype_ `virtual void ApplyScaleDelta(const FVector& InScaleDelta) override;`
- L573 _protected prototype_ `virtual void ApplyTranslate(const FVector& InTranslate);`
- L579 _protected prototype_ `void SnapTranslate(FVector& InOutWorldDelta, const EAxisList::Type InAxisList, const FRay& InRay = FRay()) const;`
- L580 _protected prototype_ `void SnapRotateDelta(FQuat& InOutWorldDelta, const EAxisList::Type InAxisList) const;`
- L581 _protected prototype_ `void SnapRotateAngleDelta(double& InOutAngleDelta, const EAxisList::Type InAxisList) const;`
- L582 _protected prototype_ `void SnapScaleDelta(FVector& InOutLocalScaleDelta, const EAxisList::Type InAxisList, const FRay& InRay = FRay()) const;`
- L584 _protected prototype_ `void OnSelectionChanged(const UTypedElementSelectionSet* InElementSelectionSet);`
- L586 _protected prototype_ `FTransform GetActiveTransform() const;`
- L588 _protected prototype_ `void CacheCursorPosition();`
- L589 _protected prototype_ `void RestoreCursorPosition() const;`
- L592 _protected prototype_ `void ApplySnappingUpdateDeltas(const FInputDeviceRay& DragPos);` — Used when TRS Snapping flag has changed, and gizmo needs to adjust accordingly
- L595 _protected prototype_ `void ApplySurfaceSnappingUpdateDeltas(const FInputDeviceRay& DragPos);` — Used when Surface Snapping flag has changed, and gizmo needs to adjust accordingly
- L597 _protected prototype_ `void CacheSnappingStates();`
- L599 _protected prototype_ `bool HasCurrentTRSSnappingChanged() const;`
- L600 _protected prototype_ `bool HasSurfaceSnappingChanged() const;`
- L601 _protected prototype_ `void HandleSnappingChanges(const FInputDeviceRay& DragPos);`
- L604 _protected prototype_ `virtual bool CanRender(IToolsContextRenderAPI* InRenderAPI) const;` — Returns true if the gizmo should be rendered.
- L607 _protected prototype_ `virtual bool CanInteract(const EViewportContext InViewportContext = EViewportContext::Focused) const override;` — Returns true if the gizmo can be interacted with.
- L612 _private prototype_ `EToolContextCoordinateSystem GetCurrentPartCoordinateSystem() const;` — Get's the coordinate system for the current part, in case of override - ie. uniform translate is always in screen-space.
- L614 _private prototype_ `EToolContextCoordinateSystem GetCoordinateSystem() const;`
- L615 _private prototype_ `EGizmoTransformScaleType GetScaleType() const;`
- L617 _private prototype_ `FGizmoPerStateValueMaterialVariant GetAxisMaterials(const EAxis::Type InAxis);`
- L618 _private prototype_ `FGizmoPerStateValueLinearColor GetAxisColors(const EAxis::Type InAxis) const;`
- L619 _private prototype_ `FGizmoPerStateValueLinearColor GetAxisColors(const EAxisList::Type InAxis) const;`
- L620 _private prototype_ `UMaterialInterface* GetAxisMaterialSolid(const EAxis::Type InAxis);`
- L621 _private prototype_ `UMaterialInterface* GetAxisMaterialTranslucent(const EAxis::Type InAxis, const bool bInSubdued = false);`
- L624 _private prototype_ `void SetupOnHoverFunctions();` — Setup on hover functions
- L630 _private prototype_ `UMaterialInterface* GetMaterialPermutation(const bool bInUseShading, const bool bInTranslucent, const bool bInVertexColored) const;` — Get a material for the given static parameters (that require a separate material, not just different material parameters). Note that you should create an MID from this, rather than use it directly.
- L633 _private prototype_ `bool CanInteractWithPart(const ETransformGizmoPartIdentifier InPartId) const;` — Returns whether the given part can interact, which can differ depending on the context (ie. arcball rotation is not interactable in gimbal rotation mode).
- L635 _private prototype_ `[[maybe_unused]] ETransformGizmoPartIdentifier GetHitPartInternal(const FInputDeviceRay& InDeviceRay, FInputRayHit& OutRayHit) const;`
- L638 _private prototype_ `void InitializeInteractionPlane(const EAxisList::Type InAxisList);` — Initializes the interaction plane according to the current state.
- L641 _private prototype_ `void InitializeInteractionPlane(const UE::Geometry::FFrame3d& InFrame);` — Initializes the interaction plane according to the current state.
- L644 _private prototype_ `void InitializeInteractionPlanes(const UE::Geometry::FFrame3d& InFrame);` — Initializes both the interaction and aligned planes to the input value.
- L647 _private prototype_ `void InitializeScreenInteraction(const FInputDeviceRay& InDeviceRay);` — Initializes screen-space interaction according to the input ray and current state.
- L650 _private prototype_ `void InitializeInteractionSign();` — Initializes the interaction sign such that positive movements in the interaction plane appear to be applied in the correct direction on the object.
- L652 _private prototype_ `void ApplyStyle();`
- L656 _private prototype_ `EAxis::Type GetAxisForIndex(const int32 InIndex) const;`
- L657 _private prototype_ `EAxis::Type GetAxisForPart(const ETransformGizmoPartIdentifier InPartId) const;`
- L658 _private prototype_ `EAxisList::Type GetAxisListForPart(const ETransformGizmoPartIdentifier InPartId) const;`
- L660 _private prototype_ `ETransformGizmoPartIdentifier GetPartForAxisList(const EAxisList::Type InAxisList) const;`
- L662 _private prototype_ `void InitializeScreenSpaceTranslate(const FInputDeviceRay& InPressPos);`
- L663 _private prototype_ `void ResetDragTranslate(const FInputDeviceRay& DragPos);`
- L664 _private prototype_ `bool CameraFollowsMovement() const;`
- L666 _private prototype_ `void DuplicateSelection(bool bDroppingDuplicate = false) const;`
- L675 _private prototype_ `bool AllowsDragDuplicate(EDragDuplicateContext Context) const;`
- L677 _private prototype_ `bool IsRotationPrecisionMode() const;`
- L678 _private prototype_ `double GetRotationPrecisionModeMultiplier() const;`
- L680 _private prototype_ `FEditorViewportClient* GetEditorViewportClient() const;`
- L684 _private prototype_ `static int32 GetTranslateAxisIndexForPart(const ETransformGizmoPartIdentifier InPartId);`
- L686 _private prototype_ `void BeginTranslateDelta() const;`
- L687 _private prototype_ `void UpdateTranslateDelta() const;`
- L694 _private prototype_ `void SetRotateMode(const TEnumAsByte<EAxisRotateMode::Type> InRotateMode);` — Allows interception for debugging purposes, etc.
- L697 _private prototype_ `template <typename MakePullQuatFunc, typename MakeArcQuatFunc> void OnClickDragRotateAxisInternal( const FInputDeviceRay& InDragPos, UGizmoElementRotateAxis* InElement, MakePullQuatFunc&& InMakePullQuat, MakeArcQuatFunc&& InMakeArcQuat);`
- L704 _private prototype_ `bool GetRotateAxisVectorForPart(const ETransformGizmoPartIdentifier InPartId, FVector& OutAxisVector) const;` — Gets a corresponding axis vector in world space for the given PartId.
- L706 _private prototype_ `static int32 GetRotateAxisIndexForPart(const ETransformGizmoPartIdentifier InPartId);`
- L708 _private prototype_ `void BeginRotateAxisDelta(UGizmoElementRotateAxis* InElement) const;`
- L709 _private prototype_ `void UpdateRotateAxisDelta(UGizmoElementRotateAxis* InElement) const;`
- L715 _private prototype_ `static int32 GetScaleAxisIndexForPart(const ETransformGizmoPartIdentifier InPartId);`
- L717 _private prototype_ `double GetScreenSign(const FVector2D& InScreenPosition);`
- L718 _private prototype_ `double GetScreenSign(const FVector2D& InScreenPosition, const FVector2D& InSignAxisOrigin);`
- L720 _private prototype_ `void BeginScaleDelta() const;`
- L721 _private prototype_ `void UpdateScaleDelta() const;`
- L724 _private prototype_ `void UpdateScaleDelta(const FVector& InDeltaScale) const;` — Overload with a user-specified delta scale, which can differ to the actual one applied (ie. to match the cursor).
- L727 _private prototype_ `void ModifyScaleDeltaForScaleType(const EGizmoTransformScaleType InScaleType, const FVector& InPreviousDelta, FVector& InOutScaleDelta);` — Optionally modify the provided scale delta according to current settings, ie. percentage vs. offset.
- L731 _private prototype_ `void NudgeSelection(const FKey& InCurrentNudgeKey);`
- L733 _private prototype_ `UE::Editor::InteractiveToolsFramework::TNudgeDelta<FVector> GetTranslationNudge() const;`
- L734 _private prototype_ `UE::Editor::InteractiveToolsFramework::TNudgeDelta<FQuat> GetRotationNudge() const;`
- L735 _private prototype_ `UE::Editor::InteractiveToolsFramework::TNudgeDelta<FVector> GetScaleNudge() const;`
- L736 _private prototype_ `ENudgeDirection GetNudgeDirection(const FKey& InCurrentNudgeKey) const;`
- L746 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> HoverAxisMaterial;` — `UPROPERTY()`
- L749 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> SubdueAxisMaterial;` — `UPROPERTY()`
- L752 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> SelectAxisMaterial;` — `UPROPERTY()`
- L755 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> InteractAxisMaterial;` — `UPROPERTY()`
- L758 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialXTranslucent;` — `UPROPERTY()`
- L761 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialYTranslucent;` — `UPROPERTY()`
- L764 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialZTranslucent;` — `UPROPERTY()`
- L767 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialScreenSpaceTranslucent;` — `UPROPERTY()`
- L770 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialXSubdued;` — `UPROPERTY()`
- L773 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialYSubdued;` — `UPROPERTY()`
- L776 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialZSubdued;` — `UPROPERTY()`
- L779 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> UniformScaleMaterial;` — `UPROPERTY()`
- L781 _protected member_ `TSharedPtr<UE::GizmoRenderingUtil::IViewBasedTransformAdjuster> TransformAdjuster = nullptr;`
- L785 _protected member_ `FTransform StartTransform = FTransform::Identity;` — `UPROPERTY()` — Start transform
- L788 _protected member_ `UE::Geometry::FFrame3d InteractionPlane;` — Interaction, best fit for viewport interaction (could be in screen space rather than world)
- L791 _protected member_ `UE::Geometry::FFrame3d AlignedInteractionPlane;` — Aligns with the actual element being manipulated, may be the same or different to the interaction plane
- L794 _protected member_ `UE::Geometry::FFrame3d ScreenPlane;` — View-facing
- L797 _protected member_ `UE::Geometry::FFrame3d CursorPlane;` — Somewhere between the interaction and screen plane, used for cursor
- L799 _protected member_ `TArray<IHoverBehaviorTarget*> HoverElements;`
- L800 _protected member_ `TArray<IClickDragBehaviorTarget*> ClickDragElements;`
- L803 _protected member_ `TArray<TMemFunPtrType<false, UEditorTRSGizmo, void(const FInputDeviceRay& PressPos)>::Type> OnClickPressFunctions;` — Array of function pointers, indexed by gizmo part id, to handle click press behavior
- L807 _protected member_ `TArray<TMemFunPtrType<false, UEditorTRSGizmo, void(const FInputDeviceRay& DragPos)>::Type> OnDragStartFunctions;` — Array of function pointers, indexed by gizmo part id, to handle drag start behavior. This is often fired after some cursor movement test, so the input cursor position will be different than OnClickPress.
- L810 _protected member_ `TArray<TMemFunPtrType<false, UEditorTRSGizmo, void(const FInputDeviceRay& DragPos)>::Type> OnClickDragFunctions;` — Array of function pointers, indexed by gizmo part id, to handle click drag behavior
- L813 _protected member_ `TArray<TMemFunPtrType<false, UEditorTRSGizmo, void(const FInputDeviceRay& ReleasePos)>::Type> OnClickReleaseFunctions;` — Array of function pointers, indexed by gizmo part id, to handle click release behavior
- L816 _protected member_ `TFunction<const FGizmoCustomization()> CustomizationFunction;` — Customization function (to override default material or increment gizmo size for example)
- L818 _protected member_ `float CursorRotation = 0.0f;`
- L820 _protected member_ `TSharedPtr<class SGizmoCursor> DirectionalCursorWidget;`
- L828 _protected member_ `FQuat CurrentRotation = FQuat::Identity;` — Arc ball current rotation
- L831 _protected member_ `TEnumAsByte<EAxisRotateMode::Type> RotateMode = EAxisRotateMode::Arc;` — Actual rotate mode used (based on view dependant information).
- L834 _protected member_ `int8 ClockwiseCorrectionSignForAxis = 1;` — Corrective sign so that an intended positive angular change maps to a clockwise rotation. Only apply once when needed (some operations already account for it).
- L837 _protected member_ `bool bTrySwitchingToNormalPull = false;` — Switch from tangential to normal projection based on the first mouse drag.
- L840 _protected member_ `bool bGimbalRotationMode = false;` — Used to check if the gimbal mode is currently active (this is updated when ticking the gizmo)
- L842 _protected member_ `bool bAdditiveIndirectAxes = false;`
- L845 _protected member_ `bool bOnlyUpdatePivot = false;` — Set to true to only update the pivot point
- L848 _protected member_ `bool bDetectedNonStandardScaling = false;` — Set to true when an attempt to scale a target has no result
- L850 _protected member_ `bool bCameraFollowsMovement = false;`
- L851 _protected member_ `bool bResetDragTranslate = false;`
- L853 _protected member_ `bool bCtrlKeyDown = false;`
- L854 _protected member_ `bool bAltKeyDown = false;`
- L855 _protected member_ `bool bShiftKeyDown = false;`
- L857 _protected member_ `bool bRotationPrecisionModeDirty = false;`
- L860 _protected member_ `double ScreenSpacePrecisionVisualOffset = 0.0;` — Screen space precision rotation requires to keep track of rotation amount, to prevent UI inconsistencies
- L863 _protected member_ `FIntPoint CachedCursorPosition;` — Used when hiding the cursor
- L865 _protected member_ `FVector CachedViewLocation;`
- L867 _protected member_ `bool bTRSSnapDirty = false;`
- L868 _protected member_ `bool bSurfaceSnapDirty = false;`
- L870 _protected member_ `bool bCachedTranslationSnap = false;`
- L871 _protected member_ `bool bCachedRotationSnap = false;`
- L872 _protected member_ `bool bCachedScaleSnap = false;`
- L873 _protected member_ `bool bCachedSurfaceSnap = false;`
- L876 _protected member_ `FQuat CumulativeRotationDelta;` — Used when temporary rotation snapping is turned on, to reset rotation
- L877 _protected member_ `FVector CumulativeDragDelta;`
- L880 _private member_ `TWeakObjectPtr<USingleClickAndDragBehavior> ClickAndDragBehaviorWeak = nullptr;`
- L882 _private member_ `TSharedPtr<UE::Editor::InteractiveToolsFramework::FTransformGizmoProfiler> Profiler;`
- L932 _private member_ `} GizmoElementInteraction;`
- L989 _private member_ `} DebugData;`
- L1017 _private member_ `FGizmoNudgeData NudgeData;`
- L1024 _private member_ `TOptional<FModeAxisOverride> ModeAxisOverride;`
- L1026 _private member_ `TWeakObjectPtr<const UTypedElementSelectionSet> SelectionSetWeak;`

#### enum `UEditorTRSGizmo::ENudgeDirection`  
`enum ENudgeDirection`  
_L227-233_
- L229 _public enumerator_ `None`
- L230 _public enumerator_ `Horizontal`
- L231 _public enumerator_ `Vertical`
- L232 _public enumerator_ `Secondary` — A modifier can be used to enter a secondary nudging mode

#### enum `UEditorTRSGizmo::EDragDuplicateContext`  
`enum class EDragDuplicateContext`  
_L668-674_
- L671 _public enumerator_ `Capture` — Whether we can capture the duplication gesture
- L673 _public enumerator_ `Action` — Whether we can execute the duplication gesture

#### struct `UEditorTRSGizmo::FGizmoElementInteraction`  
`struct FGizmoElementInteraction`  
_L885-932_
- desc: Defines various interaction state behavior.
- L919 _public member_ `static TMap<ETransformGizmoPartIdentifier, FPartSet> HoverParts;` — Parts to also Hover (see HoverElements) when the given part is Hovered. This applies to behaviors/input, not InteractionState.
- L922 _public member_ `static TMap<ETransformGizmoPartIdentifier, FPartSet> ClickDragParts;` — Parts to also Click/Drag (see ClickDragElements) when the given part is Hovered. This applies to behaviors/input, not InteractionState.
- L925 _public member_ `static TMap<ETransformGizmoPartIdentifier, FPartSet> SubdueOnInteractParts;` — Parts to Subdue when the Part specified by Key is Interacted with.
- L928 _public member_ `static TMap<ETransformGizmoPartIdentifier, FPartSet> HideOnInteractParts;` — Parts to Hide when the Part specified by Key is Interacted with.
- L931 _public member_ `static TMap<ETransformGizmoPartIdentifier, FPartSet> InteractGroupParts;` — Parts to (also) Interact when the Part specified by Key is Interacted with.

#### struct `UEditorTRSGizmo::FGizmoElementInteraction::FPartSet`  
`struct FPartSet`  
_L889-915_
- desc: A set of parts.
- L898 _public function_ `FPartSet(const std::initializer_list<ETransformGizmoPartIdentifier> InParts) : Parts(InParts)`
- L902 _public function_ `explicit FPartSet(const FPartRange& InRange) : PartRange(InRange)`
- L906 _public member_ `TArray<ETransformGizmoPartIdentifier> Parts;`
- L912 _public member_ `TOptional<FPartRange> PartRange;` — If specified, the given part range is iterated, excluding the "Exclude" value (if not none). Parts are also iterated over.
- L914 _public prototype_ `void ForEachPart(const TFunctionRef<void(const ETransformGizmoPartIdentifier)>& InFunc);`

#### struct `UEditorTRSGizmo::FGizmoElementInteraction::FPartSet::FPartRange`  
`struct FPartRange`  
_L891-896_
- L893 _public member_ `ETransformGizmoPartIdentifier Start;`
- L894 _public member_ `ETransformGizmoPartIdentifier End;`
- L895 _public member_ `TOptional<ETransformGizmoPartIdentifier> Exclude;`

#### struct `UEditorTRSGizmo::FGizmoDebugData`  
`mutable struct FGizmoDebugData`  
_L934-989_
- L937 _public member_ `bool bIsEditing = false;` — Determines whether certain data is displayed, ie. drag operation deltas.
- L939 _public member_ `FRay InteractionRay;`
- L940 _public member_ `FVector2D InteractionScreenPos;`
- L942 _public member_ `FTransform TransformStart;`
- L943 _public member_ `FTransform TransformCurrent;`
- L945 _public member_ `FTransform InteractionStart;`
- L946 _public member_ `FTransform InteractionCurrent;`
- L947 _public member_ `FVector InteractionPlaneNormal;`
- L949 _public member_ `TSet<ETransformGizmoPartIdentifier> LastHitDeltaParts;`
- L952 _public member_ `FVector2D InteractionScreenDirection;` — Can indicate a 2D drag direction, etc.
- L954 _public member_ `FVector CursorDirectionWS;`
- L955 _public member_ `FVector2D CursorDirectionSS;`
- L957 _public member_ `FInputDeviceRay LastDeviceRay;`
- L958 _public member_ `FInputRayHit LastRayHit;`
- L961 _public member_ `bool bDebugRotate = false;` — Debug attributes to display the pull direction
- L962 _public member_ `FVector DebugDirection = FVector::ZeroVector;`
- L963 _public member_ `FVector DebugClosest = FVector::ZeroVector;`
- L964 _public member_ `FVector DebugNormalRemoved = FVector::ZeroVector;`
- L965 _public member_ `FVector DebugNormalSkip = FVector::ZeroVector;`
- L966 _public member_ `double InteractionAngleStart;`
- L967 _public member_ `double InteractionAngleCurrent;`
- L968 _public member_ `double InteractionRadius;`
- L969 _public member_ `double HitAngle;`
- L970 _public member_ `FVector PointOnCircleDirection = FVector::ZeroVector;`
- L972 _public member_ `FVector ReferencePoint = FVector::ZeroVector;`
- L974 _public member_ `FVector Test = FVector::ZeroVector;`
- L975 _public member_ `FVector2D Test2 = FVector2D::ZeroVector;`
- L976 _public member_ `FVector Test3 = FVector::ZeroVector;`
- L978 _public member_ `FVector2D Test2D1 = FVector2D::ZeroVector;`
- L979 _public member_ `FVector2D Test2D2 = FVector2D::ZeroVector;`
- L980 _public member_ `FVector2D Test2D3 = FVector2D::ZeroVector;`
- L982 _public member_ `FString DebugString;` — Can be current rotation mode, etc.
- L985 _public function_ `FVector GetHitPosition() const` — Utility to get hit position from LastDeviceRay, LastRayHit pair

#### struct `UEditorTRSGizmo::FGizmoNudgeData`  
`struct FGizmoNudgeData`  
_L992-1015_
- L995 _public member_ `TArray<FKey> PressedKeys;` — List of currently pressed nudge keys
- L998 _public member_ `float TimeSinceLastNudge = 0.0f;` — Elapsed time since last nudge
- L1000 _public function_ `FKey GetCurrentKey() const`
- L1010 _public function_ `void Reset()`

#### struct `UEditorTRSGizmo::FModeAxisOverride`  
`struct FModeAxisOverride`  
_L1019-1023_
- L1021 _public member_ `EGizmoTransformMode Mode;`
- L1022 _public member_ `EAxisList::Type AxisToDraw;`

#### Free symbols / members of external scopes

- L30 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L69 _namespace_ `namespace UE`
- L69 _namespace_ `namespace Editor` (scope `UE`)
- L69 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L73 _namespace_ `namespace Private` (scope `UE::Editor::InteractiveToolsFramework`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorTransformGizmo.h` (Public)


#### class `UEditorTransformGizmo`  
`class UEditorTransformGizmo : public UTransformGizmo`  
_L22-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UTransformGizmo`
- desc: UEditorTransformGizmo handles Editor-specific functionality for the TransformGizmo, applied to a UEditorTransformProxy target object.
- L27 _private prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;` — UTransformGizmo override
- L28 _private prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L33 _protected prototype_ `virtual void ApplyTranslateDelta(const FVector& InTranslateDelta) override;` — Apply translate delta to transform proxy
- L36 _protected prototype_ `virtual void ApplyRotateDelta(const FQuat& InRotateDelta) override;` — Apply rotate delta to transform proxy
- L39 _protected prototype_ `virtual void ApplyScaleDelta(const FVector& InScaleDelta) override;` — Apply scale delta to transform proxy
- L42 _protected prototype_ `virtual void SetActiveTarget( UTransformProxy* Target, IToolContextTransactionProvider* TransactionProvider = nullptr, IGizmoStateTarget* InStateTarget = nullptr) override;` — UTransformGizmo override
- L51 _protected prototype_ `void OnGizmoTransformBegin(UTransformProxy* TransformProxy) const;` — Functions to listen to gizmo transform begin/end. They are currently used to set data on the legacy widget as some viewport clients rely on current axis to be set.
- L52 _protected prototype_ `void OnGizmoTransformEnd(UTransformProxy* TransformProxy) const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorTransformGizmoBuilder.h` (Public)


#### class `UEditorTransformGizmoBuilder`  
`class UEditorTransformGizmoBuilder : public UInteractiveGizmoBuilder, public IEditorInteractiveGizmoSelectionBuilder`  
_L22-37_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmoBuilder,IEditorInteractiveGizmoSelectionBuilder`
- L29 _public prototype_ `virtual UInteractiveGizmo* BuildGizmo(const FToolBuilderState& SceneState) const override;` — UEditorInteractiveGizmoSelectionBuilder interface
- L30 _public prototype_ `virtual void UpdateGizmoForSelection(UInteractiveGizmo* Gizmo, const FToolBuilderState& SceneState) override;`
- L33 _public member_ `TFunction<const FGizmoCustomization()> CustomizationFunction;` — If set, this function will be passed to UTransformGizmo instances to override the default material and display size.
- L36 _protected prototype_ `static const UEditorTransformGizmoContextObject* GetTransformGizmoContext(const FToolBuilderState& InSceneState);`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorTransformGizmoDataBinder.h` (Public)


#### class `FEditorTransformGizmoDataBinder`  
`class FEditorTransformGizmoDataBinder : public TSharedFromThis<FEditorTransformGizmoDataBinder>`  
_L22-65_
- inherits: `TSharedFromThis<FEditorTransformGizmoDataBinder>`
- L26 _public prototype_ `virtual ~FEditorTransformGizmoDataBinder();`
- L33 _public prototype_ `void BindToGizmoContextObject(UEditorTransformGizmoContextObject* InContextObject);` — Makes it so that the gizmo binder attaches to any gizmos created by the context object in the future. The binding is automatically removed if FEditorTransformGizmoDataBinder is destroyed.
- L36 _public prototype_ `void BindToUninitializedGizmo(UTransformGizmo* Gizmo);` — Used for binding to context object, called from the OnGizmoCreated delegate.
- L39 _public prototype_ `void BindToInitializedGizmo(UTransformGizmo* InGizmo, UTransformProxy* InProxy);` — Binds to a specific gizmo for tracking. Requires ActiveTarget to be set.
- L42 _public prototype_ `void UnbindFromGizmo(UTransformGizmo* InGizmo, UTransformProxy* InProxy);` — Unbinds from a given gizmo. Done automatically for gizmos when their ActiveTarget is cleared.
- L49 _private member_ `TSet<TWeakObjectPtr<UTransformGizmo>> BoundGizmos;` — List of the gizmos currently bound to this so that we ensure that they are actually unbound on destruction. Note that this should not happen and bound gizmos should have called their Shutdown function before this being destroyed.
- L52 _private member_ `TWeakObjectPtr<UEditorTransformGizmoContextObject> WeakContext;` — Weak ptr to the context so we can interface with the current mode manager
- L54 _private prototype_ `FEditorViewportClient* GetViewportClient() const;`
- L56 _private prototype_ `void OnProxyBeginTransformEdit(UTransformProxy* InTransformProxy);`
- L57 _private prototype_ `void OnProxyTransformChanged(UTransformProxy* InTransformProxy, FTransform InTransform);`
- L58 _private prototype_ `void OnProxyEndTransformEdit(UTransformProxy* InTransformProxy);`
- L60 _private prototype_ `void OnProxyBeginPivotEdit(UTransformProxy* InTransformProxy);`
- L61 _private prototype_ `void OnProxyPivotChanged(UTransformProxy* InTransformProxy, FTransform InTransform);`
- L62 _private prototype_ `void OnProxyEndPivotEdit(UTransformProxy* InTransformProxy);`
- L64 _private member_ `bool bHasTransformChanged = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorTransformGizmoSource.h` (Public)


#### class `UEditorTransformGizmoSource`  
`class UEditorTransformGizmoSource : public UObject, public ITransformGizmoSource`  
_L39-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject,ITransformGizmoSource`
- desc: UEditorTransformGizmoSource is an ITransformGizmoSource implementation that provides current state information used to configure the Editor transform gizmo.
- L47 _public prototype_ `virtual EGizmoTransformMode GetGizmoMode() const override;` — @return The current display mode for the Editor transform gizmo
- L52 _public prototype_ `virtual EAxisList::Type GetGizmoAxisToDraw(EGizmoTransformMode InWidgetMode) const override;` — @return The current axes to draw for the specified mode
- L57 _public prototype_ `virtual EToolContextCoordinateSystem GetGizmoCoordSystemSpace() const override;` — @return The coordinate system space (world or local) to display the widget in
- L62 _public prototype_ `virtual float GetGizmoScale() const override;` — Returns a scale factor for the gizmo
- L67 _public prototype_ `virtual bool GetVisible(const EViewportContext InViewportContext = EViewportContext::Focused) const override;` — Whether the gizmo is visible
- L73 _public prototype_ `virtual bool CanInteract(const EViewportContext InViewportContext = EViewportContext::Focused) const override;` — Returns whether the gizmo can interact. Note that this can be true even if the gizmo is hidden to support indirect manipulation in game mode.
- L78 _public prototype_ `virtual EGizmoTransformScaleType GetScaleType() const override;` — Get current scale type
- L81 _public prototype_ `virtual const FRotationContext& GetRotationContext() const override;` — Get rotation context
- L83 _public prototype_ `static UEditorTransformGizmoSource* CreateNew( UObject* Outer = (UObject*)GetTransientPackage(), const UEditorTransformGizmoContextObject* InContext = nullptr);`
- L89 _protected prototype_ `const FEditorModeTools& GetModeTools() const;`
- L91 _protected prototype_ `const FEditorViewportClient* GetViewportClient(const EViewportContext InViewportContext = EViewportContext::Focused) const;`
- L93 _protected member_ `TWeakObjectPtr<const UEditorTransformGizmoContextObject> WeakContext = nullptr;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L25 _namespace_ `namespace FEditorTransformGizmoUtil`
- L28 _prototype_ `EGizmoTransformMode GetGizmoMode(UE::Widget::EWidgetMode InWidgetMode);` (scope `FEditorTransformGizmoUtil`) — Convert UE::Widget::EWidgetMode to ETransformGizmoMode
- L31 _prototype_ `UE::Widget::EWidgetMode GetWidgetMode(EGizmoTransformMode InGizmoMode);` (scope `FEditorTransformGizmoUtil`) — Convert EEditorGizmoMode to UE::Widget::EWidgetMode

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorTransformGizmoUtil.h` (Public)


#### class `UEditorTransformGizmoContextObject`  
`class UEditorTransformGizmoContextObject : public UObject`  
_L75-124_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject`
- L81 _public prototype_ `void RegisterGizmosWithManager(UInteractiveToolManager* InToolManager);`
- L82 _public prototype_ `void UnregisterGizmosWithManager(UInteractiveToolManager* InToolManager);`
- L84 _public prototype_ `void Initialize(FEditorModeTools* InModeTools);`
- L85 _public prototype_ `void Shutdown();`
- L87 _public prototype_ `void SetGizmosEnabled(bool bInEnabled);`
- L89 _public prototype_ `UTransformGizmo* CreateTransformGizmo( UEditorInteractiveGizmoManager* InGizmoManager, const FString& InInstanceIdentifier, void* InOwner) const;`
- L92 _public prototype_ `FEditorModeTools* GetModeTools() const;`
- L94 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoCreated, UTransformGizmo*);`
- L95 _public prototype_ `FOnGizmoCreated& OnGizmoCreatedDelegate();`
- L98 _public member_ `FRotationContext RotationContext;` — `UPROPERTY(Transient)`
- L102 _public member_ `bool bIsManipulatingPivot = false;` — `UPROPERTY(Transient)` — Temporary exposure for the purposes of flowing into legacy pivot-only manipulations
- L106 _private prototype_ `void UpdateGizmo(const TArray<FEditorViewportClient*>& InViewportClients) const;`
- L108 _private prototype_ `void InitializeGizmoManagerBinding();`
- L109 _private prototype_ `void InitializeViewportsBinding();`
- L111 _private prototype_ `void RemoveGizmoManagerBinding();`
- L112 _private prototype_ `void RemoveViewportsBinding();`
- L114 _private member_ `FOnGizmoCreated OnGizmoCreated;`
- L116 _private member_ `FEditorModeTools* ModeTools = nullptr;`
- L117 _private member_ `FDelegateHandle ViewportClientsChangedHandle;`
- L118 _private member_ `FDelegateHandle LevelViewportClientsChangedHandle;`
- L119 _private member_ `FDelegateHandle UseNewGizmosChangedHandled;`
- L120 _private member_ `FDelegateHandle GizmosParametersChangedHandle;`
- L121 _private member_ `bool bGizmosRegistered = false;`
- L123 _private member_ `TSharedPtr<FEditorTransformGizmoDataBinder> DataBinder;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L25 _namespace_ `namespace EditorTransformGizmoUtil` (scope `UE`)
- L37 _prototype_ `bool RegisterTransformGizmoContextObject(FEditorModeTools* InModeTools);` (scope `UE::EditorTransformGizmoUtil`) — If one does not already exist, create a new instance of UEditorTransformGizmoContextObject and add it to the ToolsContext's ContextObjectStore @return true if the ContextObjectStore now has a UEditorTransformGizmoContextObject (whether it already existed, or was created)
- L43 _prototype_ `bool UnregisterTransformGizmoContextObject(FEditorModeTools* InModeTools);` (scope `UE::EditorTransformGizmoUtil`) — Remove any existing UEditorTransformGizmoContextObject from the ToolsContext's ContextObjectStore @return true if the ContextObjectStore no longer has a UEditorTransformGizmoContextObject (whether it was removed, or did not exist)
- L48 _prototype_ `UTransformGizmo* CreateTransformGizmo( UInteractiveToolManager* InToolManager, const FString& InInstanceIdentifier = FString(), void* InOwner = nullptr);` (scope `UE::EditorTransformGizmoUtil`) — Spawn an editor like Transform Gizmo. ToolManager's ToolsContext must have a UEditorTransformGizmoContextObject registered
- L54 _prototype_ `UTransformGizmo* GetDefaultTransformGizmo(UInteractiveToolManager* InToolManager);` (scope `UE::EditorTransformGizmoUtil`) — Spawn an editor like Transform Gizmo. ToolManager's ToolsContext must have a UEditorTransformGizmoContextObject registered
- L59 _prototype_ `UTransformGizmo* FindDefaultTransformGizmo(UInteractiveToolManager* InToolManager);` (scope `UE::EditorTransformGizmoUtil`) — Returns the existing default Transform Gizmo if any.
- L64 _prototype_ `void RemoveDefaultTransformGizmo(UInteractiveToolManager* InToolManager);` (scope `UE::EditorTransformGizmoUtil`) — Removes the existing default Transform Gizmo if any.
- L94 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoCreated, UTransformGizmo*);`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/EditorTransformProxy.h` (Public)


#### class `UEditorTransformProxy`  
`class UEditorTransformProxy : public UTransformProxy`  
_L34-98_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UTransformProxy`
- desc: UEditorTransformProxy is a derivation of UTransformProxy that returns the transform that defines the current space of the default Editor transform gizmo for a given mode manager / viewport. This defaults internally to GLevelEditorModeManager() if none provided when constructing the proxy.
- L40 _public prototype_ `UEditorTransformProxy();`
- L45 _public prototype_ `virtual FTransform GetTransform() const override;` — @return the stored transform for currently selected objects.
- L50 _public function_ `virtual void SetTransform(const FTransform& Transform) override` — Unimplemented - all updates to the Editor transform proxy MUST be made by calling the Input delta methods.
- L55 _public prototype_ `virtual void BeginTransformEditSequence() override;`
- L58 _public prototype_ `virtual void InputTranslateDelta(const FVector& InDeltaTranslate, EAxisList::Type InAxisList);` — Input translate delta to be applied in world space of the current transform.
- L61 _public prototype_ `virtual void InputRotateDelta(const FRotator& InDeltaRotate, EAxisList::Type InAxisList);` — Input rotation delta to be applied in local space of the current transform.
- L64 _public prototype_ `virtual void InputScaleDelta(const FVector& InDeltaScale, EAxisList::Type InAxisList);` — Input scale delta to be applied in local space of the current transform.
- L67 _public prototype_ `void SetCurrentAxis(const EAxisList::Type InAxisList) const;` — Set legacy widget axis temporarily because FEditorViewportClient overrides may expect it
- L70 _public prototype_ `void SetUseLegacyWidgetScale(const bool bInUseLegacyWidgetScale);` — Set whether to use FEditorModeTools::GetWidgetScale as the Transform scale.
- L72 _public prototype_ `static UEditorTransformProxy* CreateNew(const UEditorTransformGizmoContextObject* InContext = nullptr, IAssetEditorContextInterface* InAssetEditorContext = nullptr);`
- L75 _public prototype_ `static UEditorTransformProxy* CreateNew(const UEditorTransformGizmoContextObject* InContext);` — `UE_DEPRECATED(5.7, "Use CreateNew that accepts an AssetEditorContext instead")`
- L80 _private prototype_ `virtual void UpdateSharedTransform() override;` — Recalculate main SharedTransform based on the current selection set.
- L82 _private prototype_ `FTypedElementListConstRef GetElementsToManipulate() const;`
- L84 _private prototype_ `FEditorViewportClient* GetViewportClient() const;`
- L90 _private member_ `bool bUseLegacyWidgetScale = true;` — `UPROPERTY()` — Whether to use FEditorModeTools::GetWidgetScale as the Transform scale. If false, scale is derived from the underlying objects.
- L94 _private member_ `TObjectPtr<UTypedElementViewportInteraction> ViewportInteraction;` — `UPROPERTY()` — The viewport interaction instance, providing handlers for selected Typed Elements.
- L96 _private member_ `TWeakObjectPtr<const UEditorTransformGizmoContextObject> WeakContext;`
- L97 _private member_ `TWeakInterfacePtr<IAssetEditorContextInterface> WeakAssetEditorContext;`

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/GizmoElementGimbal.h` (Public)


#### class `UGizmoElementGimbal`  
`class UGizmoElementGimbal : public UGizmoElementGroup`  
_L17-46_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UGizmoElementGroup`
- desc: Gimbal rotation group object intended to be used as part of 3D Rotation Gizmos This group expects three rotation sub-elements
- L24 _public prototype_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI, const FRenderTraversalState& InRenderState) override;`
- L25 _public prototype_ `virtual FInputRayHit LineTrace(const UGizmoViewContext* ViewContext, const FLineTraceTraversalState& LineTraceState, const FVector& RayOrigin, const FVector& RayDirection, FLineTraceOutput& OutLineTraceOutput) override;`
- L29 _public prototype_ `virtual void Add(UGizmoElementBase* InElement) override;` — Add object to group.
- L32 _public function_ `template <class ElementType UE_REQUIRES(std::is_base_of_v<UGizmoElementBase, ElementType>)> ElementType* GetAxisElement(const EAxis::Type InAxis) const`
- L45 _public member_ `FRotationContext RotationContext;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/GizmoElementRotate.h` (Public)


#### enum `EGizmoElementRotateShowFlags`  
`enum class EGizmoElementRotateShowFlags : uint32`  
_L14-25_
- reflection: `UENUM(meta = (Bitflags, ShowFlags))`
- desc: Bitflags controlling visibility of rotation delta visual elements during interaction.
- L17 _public enumerator_ `None = 0 UMETA(Hidden)` — No flags set.
- L19 _public enumerator_ `DeltaArc = 1 << 0` — Show the filled arc indicating the rotation delta.
- L21 _public enumerator_ `DeltaLabel = 1 << 1` — Show the numeric angle label.
- L24 _public enumerator_ `All = DeltaArc | DeltaLabel` — All delta visual elements enabled.

#### struct `FGizmoElementRotateAxisStyle`  
`struct FGizmoElementRotateAxisStyle : public FGizmoStyleBase`  
_L30-147_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for a single rotation axis element (ring + delta arc + origin marker + value label).
- L34 _public prototype_ `FGizmoElementRotateAxisStyle();`
- L38 _public member_ `EGizmoElementRotateShowFlags ShowFlags = EGizmoElementRotateShowFlags::All;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (Bitmask))` — Controls which delta visual elements are shown during interaction.
- L42 _public member_ `float Radius = 70.0f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 1.0f))` — Radius of the rotation ring in world units (before multiplier).
- L46 _public member_ `float RadiusMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier applied to Radius, typically driven by a user setting.
- L50 _public member_ `float LineThickness = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.1f))` — Thickness of the rotation ring line in world units.
- L54 _public member_ `float OriginRadius = 3.0f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.1f))` — Radius of the origin sphere drawn at the rotation center during interaction, in world units.
- L58 _public member_ `float OriginLineThickness = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.1f))` — Outline thickness of the origin sphere, in world units.
- L62 _public member_ `float OriginToCursorLineThickness = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.1f))` — Thickness of the line connecting the Origin to cursor location.
- L66 _public member_ `float OriginToCursorLineDashSpacing = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.1f))` — Dash length of the line connecting the Origin to cursor location.
- L70 _public member_ `float OriginToCursorLineDashGapSpacing = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.1f))` — Dash gap length of the line connecting the Origin to cursor location.
- L74 _public member_ `FLinearColor OriginToCursorLineColor = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = "Rotate")` — Color of the line connecting the Origin to cursor location.
- L78 _public member_ `float DeltaFillOpacity = 0.4f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.0f, ClampMax = 1.0f))` — Fill opacity of the delta arc.
- L82 _public member_ `float DeltaStrokeThickness = .625f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.1f))` — Thickness of the delta arc lines.
- L86 _public member_ `float DeltaStrokeOpacity = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.0f, ClampMax = 1.0f))` — Stroke/line opacity of the delta arc.
- L90 _public member_ `FLinearColor DeltaFillHSVModifier = FLinearColor(0.0f, 0.5f, 2.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (HideAlphaChannel))` — HSV modifier for the delta arc fill color. R = hue offset, G = saturation multiplier, B = value multiplier.
- L94 _public member_ `FLinearColor DeltaTextBackgroundColor = FLinearColor(0.141f, 0.141f, 0.141f, 0.65f);` — `UPROPERTY(EditAnywhere, Category = "Rotate")` — Background color/alpha of the text box.
- L98 _public member_ `FLinearColor CursorColor = FLinearColor::Black;` — `UPROPERTY(EditAnywhere, Category = "Rotate")` — Cursor color.
- L102 _public member_ `int32 NumSegments = 64;` — `UPROPERTY()` — Number of segments used when generating the rotation ring geometry.
- L106 _public member_ `int32 NumInnerSlices = 8;` — `UPROPERTY()` — Number of inner slices used for the delta arc fill geometry.
- L110 _public member_ `TObjectPtr<UMaterialInterface> DeltaMaterial;` — `UPROPERTY()` — Material used for rendering the delta arc fill.
- L114 _public member_ `TObjectPtr<UMaterialInterface> VertexColorMaterial;` — `UPROPERTY()` — Material used for vertex-color-based rendering of axis elements.

#### struct `FGizmoElementRotateArcballStyle`  
`struct FGizmoElementRotateArcballStyle : public FGizmoStyleBase`  
_L151-160_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for the arcball (trackball) rotation element.
- L155 _public prototype_ `FGizmoElementRotateArcballStyle();`
- L159 _public member_ `float Radius = 70.0f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 1.0f))` — Radius of the arcball sphere in world units.

#### struct `FGizmoElementRotateStyle`  
`struct FGizmoElementRotateStyle : public FGizmoStyleBase`  
_L164-191_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Composite style for the entire rotation gizmo, combining per-axis and arcball sub-styles with screen-space circle settings.
- L170 _public member_ `FGizmoElementRotateAxisStyle AxisStyle;` — `UPROPERTY(EditAnywhere, Category = "Rotate")` — Shared style for all single-axis rotation ring elements.
- L174 _public member_ `FGizmoElementRotateArcballStyle ArcballStyle;` — `UPROPERTY(EditAnywhere, Category = "Rotate")` — Style for the arcball (trackball) rotation element.
- L178 _public member_ `EGizmoElementRotateShowFlags ShowFlags = EGizmoElementRotateShowFlags::All;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (Bitmask))` — Controls which delta visual elements are shown during interaction at the group level.
- L182 _public member_ `float ScreenSpaceRadiusOffset = 12.6f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.01f))` — Distance offset from the rotation ring radius for the screen-space circle, in world units.
- L186 _public member_ `float ScreenSpaceLineThickness = 0.625f;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ClampMin = 0.01f))` — The thickness of the screen space rotation handle arc.
- L190 _public member_ `FLinearColor ScreenSpaceCircleColor = FLinearColor(0.9f, 0.9f, 0.9f);` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (HideAlphaChannel))` — Color of the screen-space rotation circle (outer ring).

#### struct `FGizmoElementRotateInteraction`  
`struct FGizmoElementRotateInteraction`  
_L195-248_
- reflection: `USTRUCT(MinimalAPI, Category = "Rotate")`
- desc: Interaction options for rotation gizmo elements, controlling how user input maps to rotation deltas.
- L200 _public function_ `static constexpr EAxisRotateMode::Type GetDefaultRotateMode()` — The default rotation mode to use with the Gizmo.
- L204 _public member_ `TOptional<TEnumAsByte<EAxisRotateMode::Type>> RotateMode;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Optionally override the project-level default rotation mode (Arc or Pull).
- L212 _public member_ `TOptional<FVector2D> Direction;` — `UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Drag Direction"))` — The explicit drag direction corresponding with view-relative rotation. (1.0, 0.0) means left-to-right movement rotates clockwise, right-to-left moves counter-clockwise. Vertical movement wouldn't do anything. Only applicable to Pull rotation. If not set, uses a "pull-string" approach where the direction is determined by the cursor position relative to the origin.
- L216 _public member_ `float PullMultiplier = 0.25f;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Sensitivity multiplier for Pull rotation mode.
- L220 _public member_ `float ArcMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Sensitivity multiplier for Arc rotation mode.
- L223 _public prototype_ `EAxisRotateMode::Type GetRotateMode() const;` — Returns the overridden RotateMode if set, otherwise use the Editor Setting.
- L227 _public member_ `float ArcballRotationPrecisionDamping = 0.05f;` — `UPROPERTY(EditAnywhere, Category = "Precision Mode", meta = (ClampMin = 0.01f))` — Arc rotation damping factor (precision mode)
- L231 _public member_ `float AxisRotationPrecisionDamping = 0.025f;` — `UPROPERTY(EditAnywhere, Category = "Precision Mode", meta = (ClampMin = 0.01f))` — Axis rotation damping factor (precision mode)
- L235 _public member_ `float ScreenSpaceRotationPrecisionDamping = 0.025f;` — `UPROPERTY(EditAnywhere, Category = "Precision Mode", meta = (ClampMin = 0.01f))` — Screen Space rotation damping factor (precision mode)
- L239 _public member_ `float ArcballRotationPrecisionBoost = 2.0f;` — `UPROPERTY(EditAnywhere, Category = "Precision Mode", meta = (ClampMin = 0.01f))` — Arc rotation boost factor (precision mode)
- L243 _public member_ `float AxisRotationPrecisionBoost = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Precision Mode", meta = (ClampMin = 0.01f))` — Axis rotation boost factor (precision mode)
- L247 _public member_ `float ScreenSpaceRotationPrecisionBoost = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Precision Mode", meta = (ClampMin = 0.01f))` — Screen Space rotation boost factor (precision mode)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L26 _prototype_ `ENUM_CLASS_FLAGS(EGizmoElementRotateShowFlags);`
- L117 _function_ `friend bool operator==(const FGizmoElementRotateAxisStyle& InLeft, const FGizmoElementRotateAxisStyle& InRight)` — Returns true if all style properties are equal.
- L143 _function_ `friend bool operator!=(const FGizmoElementRotateAxisStyle& InLeft, const FGizmoElementRotateAxisStyle& InRight)` — Returns true if any style property differs.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/GizmoElementScale.h` (Public)


#### enum `EGizmoElementScaleShowFlags`  
`enum class EGizmoElementScaleShowFlags : uint32`  
_L14-25_
- reflection: `UENUM(meta = (Bitflags, ShowFlags))`
- desc: Bitflags controlling visibility of scale delta visual elements during interaction.
- L17 _public enumerator_ `None = 0 UMETA(Hidden)` — No flags set.
- L19 _public enumerator_ `DeltaLine = 1 << 0` — Show the delta line from the axis handle to the scaled position.
- L21 _public enumerator_ `DeltaLabel = 1 << 1` — Show the numeric scale label.
- L24 _public enumerator_ `All = DeltaLine | DeltaLabel` — All delta visual elements enabled.

#### struct `FGizmoElementScaleAxisStyle`  
`struct FGizmoElementScaleAxisStyle : public FGizmoStyleBase`  
_L30-148_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for a single scale axis element (cylinder body + arrow head handle + delta visuals).
- L34 _public prototype_ `FGizmoElementScaleAxisStyle();`
- L38 _public member_ `float AxisLength = 62.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 1.0f))` — Length of the axis body in world units (before multiplier).
- L42 _public member_ `float AxisLengthMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier applied to AxisLength, typically driven by a user setting.
- L46 _public member_ `float AxisOffsetFromCenter = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 1.0f))` — Gap between the gizmo origin and the start of the axis body, in world units.
- L50 _public member_ `float HandleSizeMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier for the arrow head size, typically driven by a user setting.
- L54 _public member_ `float LineThickness = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Thickness of the axis line in world units.
- L58 _public member_ `float HeadSize = 8.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Size of the cube arrow head at the end of the axis, in world units.
- L62 _public member_ `float UniformSize = 12.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Size of the uniform (center) scale handle, in world units.
- L66 _public member_ `EGizmoElementScaleShowFlags ShowFlags = EGizmoElementScaleShowFlags::All;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (Bitmask))` — Controls which delta visual elements are shown during interaction.
- L70 _public member_ `TOptional<float> DeltaLineThickness;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Optional override for the delta line thickness. Falls back to LineThickness if not set.
- L74 _public member_ `float DeltaLineDashSpacing = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Length of each dash segment in the delta line, in world units.
- L78 _public member_ `float DeltaLineDashGapSpacing = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Length of each gap between dashes in the delta line, in world units.
- L82 _public member_ `FGizmoPerStateValueLinearColor UniformColors;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Per-state colors for the uniform (center) scale handle.
- L86 _public member_ `TOptional<FText> DeltaOffsetTextPrefix;` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Overrides the default prefix text for offset-based scale labels, if set.
- L90 _public member_ `TOptional<FText> DeltaPercentageTextPrefix;` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Overrides the default prefix text for percentage-based scale labels, if set.
- L94 _public member_ `TOptional<FText> DeltaOffsetTextSuffix;` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Overrides the default suffix text for offset-based scale labels, if set.
- L98 _public member_ `TOptional<FText> DeltaPercentageTextSuffix;` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Overrides the default suffix text for percentage-based scale labels, if set.
- L102 _public member_ `FLinearColor DeltaTextBackgroundColor = FLinearColor(0.141f, 0.141f, 0.141f, 0.65f);` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Background color/alpha of the text box.
- L106 _public member_ `TObjectPtr<UMaterialInterface> VertexColorMaterial;` — `UPROPERTY()` — Material used for vertex-color-based rendering of axis elements.
- L110 _public member_ `int32 NumSegments = 32;` — `UPROPERTY()` — Number of segments used when generating cylindrical geometry (axis body, etc.).
- L113 _public prototype_ `const FText& GetDeltaTextPrefixForScaleType(const EGizmoTransformScaleType InScaleType) const;` — Gets the overridden prefix, or the default if not overriden.
- L116 _public prototype_ `const FText& GetDeltaTextSuffixForScaleType(const EGizmoTransformScaleType InScaleType) const;` — Gets the overridden suffix, or the default if not overriden.

#### struct `FGizmoElementScalePlanarStyle`  
`struct FGizmoElementScalePlanarStyle : public FGizmoStyleBase`  
_L152-177_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for a planar scale handle (two-axis rectangle).
- L156 _public prototype_ `FGizmoElementScalePlanarStyle();`
- L160 _public member_ `float OffsetFromOrigin = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Distance from the gizmo origin to the center of the planar handle, in world units.
- L164 _public member_ `float Size = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Width and height of the planar handle square, in world units.
- L168 _public member_ `float SizeMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier applied to Size, typically driven by a user setting.
- L172 _public member_ `float Thickness = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Thickness (depth) of the planar handle geometry, in world units.
- L176 _public member_ `TObjectPtr<UMaterialInterface> VertexColorMaterial;` — `UPROPERTY()` — Material used for vertex-color-based rendering of the planar handle.

#### struct `FGizmoElementScaleUniformStyle`  
`struct FGizmoElementScaleUniformStyle : public FGizmoStyleBase`  
_L181-194_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for the uniform (screen-space) scale handle.
- L185 _public prototype_ `FGizmoElementScaleUniformStyle();`
- L189 _public member_ `float Size = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ClampMin = 0.1f))` — Size of the uniform scale handle element, in world units.
- L193 _public member_ `float SizeMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier applied to Size, typically driven by a user setting.

#### struct `FGizmoElementScaleStyle`  
`struct FGizmoElementScaleStyle : public FGizmoStyleBase`  
_L198-217_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Composite style for the entire scale gizmo, combining axis, planar, and uniform sub-styles.
- L204 _public member_ `FGizmoElementScaleAxisStyle AxisStyle;` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Shared style for all single-axis scale elements.
- L208 _public member_ `FGizmoElementScalePlanarStyle PlanarStyle;` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Shared style for all two-axis planar scale handles.
- L212 _public member_ `FGizmoElementScaleUniformStyle UniformStyle;` — `UPROPERTY(EditAnywhere, Category = "Scale")` — Style for the uniform (screen-space) scale handle.
- L216 _public member_ `EGizmoElementScaleShowFlags ShowFlags = EGizmoElementScaleShowFlags::All;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (Bitmask))` — Controls which delta visual elements are shown during interaction at the group level.

#### enum `EGizmoElementScaleDistanceSource`  
`enum class EGizmoElementScaleDistanceSource : uint8`  
_L221-227_
- reflection: `UENUM()`
- desc: Determines the reference point from which scale distance is measured.
- L224 _public enumerator_ `FromObject = 0` — Measure distance from the object being scaled.
- L226 _public enumerator_ `FromStart = 1` — Measure distance from the starting input/cursor position.

#### enum `EGizmoElementScaleDistanceType`  
`enum class EGizmoElementScaleDistanceType : uint8`  
_L231-237_
- reflection: `UENUM()`
- desc: Determines how the scale magnitude is computed from cursor movement.
- L234 _public enumerator_ `Linear = 0` — Based on the linear (Euclidean) distance from the distance source.
- L236 _public enumerator_ `Directional = 1` — Based on the projected distance along a specific screen-space direction.

#### struct `FGizmoElementScaleInteraction`  
`struct FGizmoElementScaleInteraction`  
_L241-267_
- reflection: `USTRUCT(MinimalAPI, Category = "Scale")`
- desc: Interaction options for scale gizmo elements, controlling how user input maps to scale deltas.
- L246 _public function_ `static constexpr EGizmoTransformScaleType GetDefaultScaleType()` — The default scale-type to use with the Gizmo.
- L250 _public member_ `EGizmoElementScaleDistanceSource DistanceSource = EGizmoElementScaleDistanceSource::FromStart;` — `UPROPERTY(EditAnywhere, Category = "Input")` — The amount is based on the distance to the reference point specified here.
- L254 _public member_ `EGizmoElementScaleDistanceType DistanceType = EGizmoElementScaleDistanceType::Directional;` — `UPROPERTY(EditAnywhere, Category = "Input")` — The direction of the scale (+/-) is based on the metric below.
- L258 _public member_ `FVector2D Direction = FVector2d(1.0f, 1.0f);` — `UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Drag Direction", EditCondition = "DistanceType == EGizmoElementScaleDistanceType::Directional"))` — The drag direction corresponding with a scale increase. (1.0, 0.0) means left-to-right movement scales up, right-to-left scales down. Vertical movement wouldn't do anything.
- L262 _public member_ `float Multiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Input")` — Overall multiplier applied to the computed scale delta.
- L266 _public member_ `TOptional<float> MinimumScale = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "Input", AdvancedDisplay)` — Minimum scale value clamp. Prevents the scale from reaching zero or extremely small values.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L26 _prototype_ `ENUM_CLASS_FLAGS(EGizmoElementScaleShowFlags);`
- L119 _function_ `friend bool operator==(const FGizmoElementScaleAxisStyle& InLeft, const FGizmoElementScaleAxisStyle& InRight)` — Returns true if all style properties are equal.
- L144 _function_ `friend bool operator!=(const FGizmoElementScaleAxisStyle& Lhs, const FGizmoElementScaleAxisStyle& RHS)` — Returns true if any style property differs.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/GizmoElementTranslate.h` (Public)


#### enum `EGizmoElementTranslateShowFlags`  
`enum class EGizmoElementTranslateShowFlags : uint32`  
_L14-27_
- reflection: `UENUM(meta = (Bitflags, ShowFlags))`
- desc: Bitflags controlling visibility of translation delta visual elements during interaction.
- L17 _public enumerator_ `None = 0 UMETA(Hidden)` — No flags set.
- L19 _public enumerator_ `DeltaLine = 1 << 0` — Show the dashed line from origin to current position.
- L21 _public enumerator_ `DeltaLabel = 1 << 1` — Show the numeric distance label.
- L23 _public enumerator_ `DeltaOrigin = 1 << 2` — Show the origin marker at the drag start point.
- L26 _public enumerator_ `All = DeltaLine | DeltaLabel | DeltaOrigin` — All delta visual elements enabled.

#### struct `FGizmoElementTranslateAxisStyle`  
`struct FGizmoElementTranslateAxisStyle : public FGizmoStyleBase`  
_L32-109_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for a single translation axis element (arrow handle + delta visuals).
- L36 _public prototype_ `FGizmoElementTranslateAxisStyle();`
- L40 _public member_ `float AxisLength = 49.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 1.0f))` — Length of the axis arrow body in world units (before multiplier).
- L44 _public member_ `float AxisLengthMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier applied to AxisLength, typically driven by a user setting.
- L48 _public member_ `float AxisOffsetFromCenter = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 1.0f))` — Gap between the gizmo origin and the start of the axis arrow, in world units.
- L52 _public member_ `float HandleSizeMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier for the arrow head size, typically driven by a user setting.
- L56 _public member_ `float LineThickness = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Thickness of the axis line in world units.
- L60 _public member_ `float ArrowSizeMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Overall scale multiplier for the arrow head geometry.
- L64 _public member_ `float ArrowHeight = 20.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Height of the arrow head cone in world units.
- L68 _public member_ `float ArrowRadius = 5.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Base radius of the arrow head cone in world units.
- L72 _public member_ `EGizmoElementTranslateShowFlags ShowFlags = EGizmoElementTranslateShowFlags::All;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (Bitmask))` — Controls which delta visual elements are shown during interaction.
- L76 _public member_ `FLinearColor DeltaTextBackgroundColor = FLinearColor(0.141f, 0.141f, 0.141f, 0.65f);` — `UPROPERTY(EditAnywhere, Category = "Translate")` — Background color/alpha of the text box.
- L80 _public member_ `TObjectPtr<UMaterialInterface> VertexColorMaterial;` — `UPROPERTY()` — Material used for vertex-color-based rendering of axis elements.
- L84 _public member_ `int32 NumSegments = 32;` — `UPROPERTY()` — Number of segments used when generating cylindrical geometry (arrow body, etc.).

#### struct `FGizmoElementTranslatePlanarStyle`  
`struct FGizmoElementTranslatePlanarStyle : public FGizmoStyleBase`  
_L113-138_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for a planar translation handle (two-axis rectangle).
- L117 _public prototype_ `FGizmoElementTranslatePlanarStyle();`
- L121 _public member_ `float OffsetFromOrigin = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Distance from the gizmo origin to the center of the planar handle, in world units.
- L125 _public member_ `float Size = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Width and height of the planar handle square, in world units.
- L129 _public member_ `float SizeMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier applied to Size, typically driven by a user setting.
- L133 _public member_ `float Thickness = 0.75f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Thickness (depth) of the planar handle geometry, in world units.
- L137 _public member_ `TObjectPtr<UMaterialInterface> VertexColorMaterial;` — `UPROPERTY()` — Material used for vertex-color-based rendering of the planar handle.

#### struct `FGizmoElementTranslateUniformStyle`  
`struct FGizmoElementTranslateUniformStyle : public FGizmoStyleBase`  
_L142-159_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Visual style parameters for the uniform (screen-space) translation handle.
- L146 _public prototype_ `FGizmoElementTranslateUniformStyle();`
- L150 _public member_ `float Size = 12.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Size of the uniform handle element, in world units.
- L154 _public member_ `float SizeMultiplier = 1.0f;` — `UPROPERTY()` — Multiplier applied to Size, typically driven by a user setting.
- L158 _public member_ `float LineThickness = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Line thickness for the uniform handle outline, in world units.

#### struct `FGizmoElementTranslateStyle`  
`struct FGizmoElementTranslateStyle : public FGizmoStyleBase`  
_L163-202_
- reflection: `USTRUCT(MinimalAPI)`
- inherits: `FGizmoStyleBase`
- desc: Composite style for the entire translation gizmo, combining axis, planar, and uniform sub-styles with shared delta visual settings.
- L169 _public member_ `FGizmoElementTranslateAxisStyle AxisStyle;` — `UPROPERTY(EditAnywhere, Category = "Translate")` — Shared style for all single-axis translation arrow elements.
- L173 _public member_ `FGizmoElementTranslatePlanarStyle PlanarStyle;` — `UPROPERTY(EditAnywhere, Category = "Translate")` — Shared style for all two-axis planar translation handles.
- L177 _public member_ `FGizmoElementTranslateUniformStyle UniformStyle;` — `UPROPERTY(EditAnywhere, Category = "Translate")` — Style for the uniform (screen-space) translation handle.
- L181 _public member_ `EGizmoElementTranslateShowFlags ShowFlags = EGizmoElementTranslateShowFlags::All;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (Bitmask))` — Controls which delta visual elements are shown during interaction at the group level.
- L185 _public member_ `float OriginRadius = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Radius of the origin sphere drawn at the drag start point, in world units.
- L189 _public member_ `float OriginLineThickness = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Outline thickness of the origin sphere, in world units.
- L193 _public member_ `TOptional<float> DeltaLineThickness;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Optional override for the delta dashed line thickness. Falls back to the axis LineThickness if not set.
- L197 _public member_ `float DeltaLineDashSpacing = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Length of each dash segment in the delta line, in world units.
- L201 _public member_ `float DeltaLineDashGapSpacing = 4.0f;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ClampMin = 0.1f))` — Length of each gap between dashes in the delta line, in world units.

#### struct `FGizmoElementTranslateInteraction`  
`struct FGizmoElementTranslateInteraction`  
_L206-218_
- reflection: `USTRUCT(MinimalAPI, Category = "Translate")`
- desc: Interaction options for translation gizmo elements, controlling how user input maps to translation deltas.
- L217 _public member_ `TOptional<FVector2D> Direction;` — `UPROPERTY(EditAnywhere, Category = "Input", meta = (DisplayName = "Drag Direction"))` — The explicit drag direction corresponding with view-relative translation. (1.0, 0.0) means left-to-right movement moves positively, right-to-left moves negatively. Vertical movement wouldn't do anything. Only applicable to indirect manipulation. If not set, the screen-space direction of the selected axis is used.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L28 _prototype_ `ENUM_CLASS_FLAGS(EGizmoElementTranslateShowFlags);`
- L87 _function_ `friend bool operator==(const FGizmoElementTranslateAxisStyle& InLeft, const FGizmoElementTranslateAxisStyle& InRight)` — Returns true if all style properties are equal.
- L105 _function_ `friend bool operator!=(const FGizmoElementTranslateAxisStyle& InLeft, const FGizmoElementTranslateAxisStyle& InRight)` — Returns true if any style property differs.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/GizmoRotationUtil.h` (Public)


#### struct `UE::GizmoRotationUtil::FRotationDecomposition`  
`struct FRotationDecomposition`  
_L18-25_
- desc: FRotationDecomposition is a data storage structure representing the rotations around the X, Y and Z axis
- L20 _public function_ `FRotationDecomposition()`
- L24 _public member_ `FQuat R[3];`

#### struct `UE::GizmoRotationUtil::IRelativeTransformInterface`  
`struct IRelativeTransformInterface`  
_L43-49_
- desc: IRelativeTransformInterface
- L45 _public prototype_ `virtual ~IRelativeTransformInterface() = default;`
- L47 _public prototype_ `virtual bool GetRelativeTransform(const FTypedElementHandle& InElementHandle, FEulerTransform& OutRelativeTransform) = 0;`
- L48 _public prototype_ `virtual bool SetRelativeTransform(const FTypedElementHandle& InElementHandle, const FEulerTransform& InRelativeTransform) = 0;`

#### class `UE::GizmoRotationUtil::FRelativeTransformInterfaceRegistry`  
`class FRelativeTransformInterfaceRegistry`  
_L54-84_
- desc: FRelativeTransformInterfaceRegistry
- L57 _public prototype_ `~FRelativeTransformInterfaceRegistry() = default;`
- L60 _public prototype_ `static FRelativeTransformInterfaceRegistry& Get();` — Get the singleton registry object
- L64 _public function_ `template<typename TWorldInterface> void RegisterRelativeTransformInterface(TUniquePtr<IRelativeTransformInterface>&& InInterface)` — Register an interface for the TWorldInterface static class
- L71 _public prototype_ `static void RegisterDefaultInterfaces();`
- L74 _public prototype_ `IRelativeTransformInterface* FindRelativeTransformInterface(const TTypedElement<ITypedElementWorldInterface>& InElement) const;` — Find the registered interface from the given class. Returns a nullptr if noting registered for that class.
- L75 _public prototype_ `IRelativeTransformInterface* FindRelativeTransformInterface(const UClass* InClass) const;`
- L78 _private prototype_ `FRelativeTransformInterfaceRegistry() = default;`
- L80 _private member_ `TMap<UClass*, TUniquePtr<IRelativeTransformInterface>> WorldInterfaceToRelativeTransformInterface;`
- L82 _private member_ `mutable TSet<const UClass*> QueriedUnregisteredClass;`
- L83 _private prototype_ `void LogOnce(const UClass* InClass) const;`

#### struct `UE::GizmoRotationUtil::FActorRelativeTransformInterface`  
`struct FActorRelativeTransformInterface : IRelativeTransformInterface`  
_L89-98_
- inherits: `IRelativeTransformInterface`
- desc: Handles get / set relative transform operations UActorElementWorldInterface & UActorElementEditorWorldInterface
- L91 _public prototype_ `virtual ~FActorRelativeTransformInterface() override = default;`
- L93 _public prototype_ `virtual bool GetRelativeTransform(const FTypedElementHandle& InElementHandle, FEulerTransform& OutRelativeTransform) override;`
- L94 _public prototype_ `virtual bool SetRelativeTransform(const FTypedElementHandle& InElementHandle, const FEulerTransform& InRelativeTransform) override;`
- L97 _private prototype_ `static USceneComponent* GetSceneComponent(const FTypedElementHandle& InElementHandle);`

#### struct `UE::GizmoRotationUtil::FComponentRelativeTransformInterface`  
`struct FComponentRelativeTransformInterface : IRelativeTransformInterface`  
_L103-112_
- inherits: `IRelativeTransformInterface`
- desc: Handles get / set relative transform operations UActorElementWorldInterface & UActorElementEditorWorldInterface
- L105 _public prototype_ `virtual ~FComponentRelativeTransformInterface() override = default;`
- L107 _public prototype_ `virtual bool GetRelativeTransform(const FTypedElementHandle& InElementHandle, FEulerTransform& OutRelativeTransform) override;`
- L108 _public prototype_ `virtual bool SetRelativeTransform(const FTypedElementHandle& InElementHandle, const FEulerTransform& InRelativeTransform) override;`
- L111 _private prototype_ `static USceneComponent* GetSceneComponent(const FTypedElementHandle& InElementHandle);`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace GizmoRotationUtil` (scope `UE`)
- L30 _prototype_ `void DecomposeRotations(const FTransform& InTransform, const FRotationContext& InRotationContext, FRotationDecomposition& OutDecomposition);` (scope `UE::GizmoRotationUtil`) — Decomposes InRotationContext.Rotation in respect to the rotation order to output the explicit per axis rotations.
- L35 _prototype_ `FVector GetRotationAxis(const FTransform& InTransform, const FRotationContext& InRotationContext, const int32 InAxis);` (scope `UE::GizmoRotationUtil`) — Returns the explicit rotation axis in respect to InRotationContext.Rotation & InRotationContext.RotationOrder
- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace GizmoRotationUtil` (scope `UE`)
- L117 _prototype_ `bool GetRelativeTransform(const TTypedElement<ITypedElementWorldInterface>& InElement, FTransform& OutTransform, FRotationContext& InOutRotationContext);` (scope `UE::GizmoRotationUtil`) — Returns the relative transform of an object by storing its explicit relative rotation in the provided FRotationContext

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/TransformGizmo.h` (Public)


#### enum `ETransformGizmoPartIdentifier`  
`enum class ETransformGizmoPartIdentifier`  
_L76-105_
- reflection: `UENUM()`
- desc: Part identifiers are used to associate transform gizmo parts with their corresponding representation in the render and hit target. The render and hit target should use the default identifier for any of their internal elements that do not correspond to transform gizmo parts, for example non-hittable visual guide elements.
- L78 _public enumerator_ `Default`
- L79 _public enumerator_ `TranslateAll`
- L80 _public enumerator_ `TranslateXAxis`
- L81 _public enumerator_ `TranslateYAxis`
- L82 _public enumerator_ `TranslateZAxis`
- L83 _public enumerator_ `TranslateXYPlanar`
- L84 _public enumerator_ `TranslateYZPlanar`
- L85 _public enumerator_ `TranslateXZPlanar`
- L86 _public enumerator_ `TranslateScreenSpace`
- L87 _public enumerator_ `RotateAll`
- L88 _public enumerator_ `RotateXAxis`
- L89 _public enumerator_ `RotateYAxis`
- L90 _public enumerator_ `RotateZAxis`
- L91 _public enumerator_ `RotateScreenSpace`
- L92 _public enumerator_ `RotateArcball`
- L93 _public enumerator_ `RotateXGimbal`
- L94 _public enumerator_ `RotateYGimbal`
- L95 _public enumerator_ `RotateZGimbal`
- L96 _public enumerator_ `ScaleAll`
- L97 _public enumerator_ `ScaleXAxis`
- L98 _public enumerator_ `ScaleYAxis`
- L99 _public enumerator_ `ScaleZAxis`
- L100 _public enumerator_ `ScaleXYPlanar`
- L101 _public enumerator_ `ScaleYZPlanar`
- L102 _public enumerator_ `ScaleXZPlanar`
- L103 _public enumerator_ `ScaleUniform`
- L104 _public enumerator_ `Max`

#### enum `ETransformGizmoShowFlags`  
`enum class ETransformGizmoShowFlags : uint32`  
_L117-126_
- reflection: `UENUM(meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Controls the (fixed) visibility of various visual elements in the TransformGizmo.
- L119 _public enumerator_ `None = 0 UMETA(Hidden)`
- L120 _public enumerator_ `DeltaLabel = 1 << 0`
- L121 _public enumerator_ `DeltaLine = 1 << 1`
- L122 _public enumerator_ `DeltaArc = 1 << 2`
- L123 _public enumerator_ `DeltaOrigin = 1 << 3`
- L125 _public enumerator_ `All = DeltaLabel | DeltaLine | DeltaArc | DeltaOrigin`

#### struct `FTransformGizmoStyle`  
`struct FTransformGizmoStyle`  
_L131-263_
- reflection: `USTRUCT(MinimalAPI)`
- desc: Contains all styling properties for TransformGizmo.
- L137 _public prototype_ `FTransformGizmoStyle();`
- L138 _public prototype_ `FTransformGizmoStyle(const FTransformGizmoStyle&) = default;`
- L139 _public prototype_ `FTransformGizmoStyle& operator=(const FTransformGizmoStyle&) = default;`
- L143 _public prototype_ `void MakeValid();` — Clamps and otherwise corrects values within the style.
- L149 _public member_ `static constexpr FLinearColor AxisColorX = FLinearColor(0.594f, 0.0197f, 0.0f);` — `UE_DEPRECATED(5.6, "Use AxisDisplayInfo::GetAxisColor(EAxisList::X) instead")`
- L151 _public member_ `static constexpr FLinearColor AxisColorY = FLinearColor(0.1349f, 0.3959f, 0.0f);` — `UE_DEPRECATED(5.6, "Use AxisDisplayInfo::GetAxisColor(EAxisList::Y) instead")`
- L153 _public member_ `static constexpr FLinearColor AxisColorZ = FLinearColor(0.0251f, 0.207f, 0.85f);` — `UE_DEPRECATED(5.6, "Use AxisDisplayInfo::GetAxisColor(EAxisList::Z) instead")`
- L161 _public member_ `float AxisSizeMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.1f, ClampMax = 100.0f, DisplayPriority = -1))` — Applies to axis lengths and radii. Use the GetModifiedAxisSizeMultiplier to account for various other project/editor settings.
- L165 _public member_ `float HandleSizeMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.01f, ClampMax = 4.0f, DisplayPriority = -1))` — Applies to arrow heads, planar and uniform handles.
- L169 _public member_ `float PlanarAxisOffsetFromOrigin = 50.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.01f, ClampMax = 300.0f, DisplayPriority = -1))` — Applies to both translate and scale planar handles.
- L173 _public member_ `float MinLineThickness = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.01f))` — Used to prevent sub-pixel line sizes.
- L176 _public member_ `float LineThicknessMultiplier = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.01f, ClampMax = 3.0f))`
- L179 _public member_ `float HoverLineThicknessMultiplier = 1.5f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.01f))`
- L184 _public member_ `FLinearColor CurrentColor = FLinearColor(1.0f, 1.0f, 0.0f);` — `UE_DEPRECATED(5.7, "Use HoverColor instead")` — `UPROPERTY(meta = (HideAlphaChannel, DeprecatedProperty, DeprecationMessage = "Use HoverColor instead."))` — The current color to use.
- L188 _public member_ `FLinearColor HoverColor = FLinearColor(1.0f, 0.552619f, 0.024453f);` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (HideAlphaChannel))` — The color to use on hover.
- L192 _public member_ `FLinearColor SelectColor = FLinearColor(0.8f, 0.8f, 0.0f);` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (HideAlphaChannel))` — The color to use on select.
- L196 _public member_ `FLinearColor InteractColor = FLinearColor(1.0f, 1.0f, 0.0f);` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (HideAlphaChannel))` — The color to use on interact.
- L200 _public member_ `FLinearColor SubdueColor = FLinearColor::Black.CopyWithNewOpacity(0.7f);` — `UPROPERTY(EditAnywhere, Category = "Shared")` — The color to use on subdue. Depending on the effect, we may only use the alpha value.
- L203 _public member_ `FLinearColor GreyColor = FLinearColor(0.6f, 0.6f, 0.6f);` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (HideAlphaChannel))`
- L206 _public member_ `FLinearColor WhiteColor = FLinearColor(0.9f, 0.9f, 0.9f);` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (HideAlphaChannel))`
- L210 _public member_ `bool bUseShading = true;` — `UPROPERTY(EditAnywhere, Category = "Shared")` — Whether to show shading on the gizmo, or unlit (if false).
- L213 _public member_ `float ShadingAmbient = 0.8f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (EditCondition = "bUseShading", ClampMin = 0.0f, ClampMax = 2.0f))`
- L216 _public member_ `float ShadingSpecularGlossiness = 0.1f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (EditCondition = "bUseShading", ClampMin = 0.0f, ClampMax = 1.0f))`
- L220 _public member_ `float PixelHitDistanceThreshold = 15.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.1f))` — Pixel hit distance threshold - where the default is generally 7px.
- L224 _public member_ `float MinimumPixelHitDistanceThreshold = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (ClampMin = 0.0f))` — Minimum pixel hit distance threshold.
- L228 _public member_ `FLinearColor DeltaTextBackgroundColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.65f);` — `UPROPERTY(EditAnywhere, Category = "Shared")` — Represents the background color for text labels.
- L232 _public member_ `bool bUsePlatformCursorSize = true;` — `UPROPERTY(EditAnywhere, Category = "Shared")` — Synchronizes the cursor size to that specified for the platform/OS. If false, CursorSize is used.
- L236 _public member_ `float CursorSize = 16.0f;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (EditCondition = "!bUsePlatformCursorSize"))` — Defines the size of the custom cursor.
- L240 _public member_ `uint32 ShowFlags = static_cast<uint32>(ETransformGizmoShowFlags::All);` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (Bitmask, BitmaskEnum = "/Script/EditorInteractiveToolsFramework.ETransformGizmoShowFlags"))` — Sets the fixed visibility of various elements.
- L245 _public member_ `FGizmoElementTranslateStyle TranslateStyle;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ShowOnlyInnerProperties, DisplayPriority = 10))`
- L250 _public member_ `FGizmoElementRotateStyle RotateStyle;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ShowOnlyInnerProperties, DisplayPriority = 11))`
- L255 _public member_ `FGizmoElementScaleStyle ScaleStyle;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ShowOnlyInnerProperties, DisplayPriority = 12))`
- L261 _public prototype_ `float GetModifiedAxisSizeMultiplier(const TOptional<TUniqueFunction<float(const float)>>& InModifierOverride = { }) const;` — Gets the AxisSizeMultiplier, modified by project/editor level settings, etc., or the given Modifier if specified.

#### struct `FTransformGizmoInteraction`  
`struct FTransformGizmoInteraction`  
_L266-292_
- reflection: `USTRUCT(MinimalAPI)`
- L272 _public member_ `bool bPersistHandleSelection = false;` — `UPROPERTY()` — Whether to allow handle selection to persist and reference for indirect operations.
- L276 _public member_ `int32 AdditionalCoordinateSystems = INDEX_NONE;` — `UPROPERTY(EditAnywhere, Category = "Shared", meta = (Bitmask, BitmaskEnum = "/Script/EditorFramework.ECoordSystem"))` — Stores additional coordinate systems enabled for this gizmo. By default, all are available.
- L279 _public member_ `FGizmoElementTranslateInteraction TranslateInteraction;` — `UPROPERTY(EditAnywhere, Category = "Translate", meta = (ShowOnlyInnerProperties, DisplayPriority = 10))`
- L282 _public member_ `FGizmoElementRotateInteraction RotateInteraction;` — `UPROPERTY(EditAnywhere, Category = "Rotate", meta = (ShowOnlyInnerProperties, DisplayPriority = 11))`
- L285 _public member_ `FGizmoElementScaleInteraction ScaleInteraction;` — `UPROPERTY(EditAnywhere, Category = "Scale", meta = (ShowOnlyInnerProperties, DisplayPriority = 12))`
- L288 _public prototype_ `bool IsCoordinateSystemEnabled(const ECoordSystem InCoordinateSystem) const;` — Returns true if the given coordinate system is enabled for this gizmo.
- L291 _public prototype_ `void SetCoordinateSystemEnabled(const ECoordSystem InCoordinateSystem, const bool bInIsEnabled);` — Sets whether the given coordinate system is enabled for this gizmo.

#### struct `FGizmosParameters`  
`struct FGizmosParameters`  
_L295-367_
- reflection: `USTRUCT()`
- L301 _public member_ `TEnumAsByte<EAxisRotateMode::Type> RotateMode = EAxisRotateMode::ScreenArc;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — Determines how dragging the rotate gizmo affects the selected objects
- L305 _public member_ `EGizmoTransformScaleType ScaleType = EGizmoTransformScaleType::PercentageBased;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — Determines how scale is calculated when applied.
- L311 _public member_ `bool bAdditiveIndirectAxes = false;` — `UPROPERTY(EditAnywhere, Category = "Experimental", DisplayName = "Additive Indirect Manipulation")` — When enabled, Ctrl+clicking multiple mouse buttons allows you to indirectly manipulate multiple axes at once.
- L317 _public member_ `bool bScreenSpaceIndirectOrthographicManipulation = true;` — `UPROPERTY(EditAnywhere, Category = "Experimental", DisplayName = "Screen Space Indirect Orthographic Manipulation")` — When enabled and in an orthographic view, Ctrl+LMB-Drag will move or scale in screen space, and Ctrl+RMB-Drag will rotate in screen space.
- L324 _public member_ `bool bSequentialIndirectAxesButtons = false;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — When disabled, Ctrl+LMB manipulates X, Ctrl+RMB manipulates Y, and Ctrl+LMB+RMB or Ctrl+MMB manipulates Z. When enabled LMB is mapped to X, MMB is mapped to Y, and RMB is mapped to Z.
- L330 _public member_ `bool bUniformIndirectScale = false;` — `UPROPERTY(EditAnywhere, Category = "Experimental", DisplayName = "Indirect Scale is always Uniform")` — When enabled, all indirect scale manipulations will trigger uniform scaling
- L337 _public member_ `bool bEnableExplicit = false;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — When enabled, the list of coordinate spaces in the viewport toolbar offers rig space: a coordinate system that is similar to parent space but uses gimbal rotations.
- L341 _public member_ `float AxisSizeMultiplier = 1.0f;` — `UPROPERTY()` — Multiplies the values of TranslateAxisLength, ScaleAxisLength, and RotateAxisRadius.
- L345 _public member_ `bool bPersistHandleSelection = false;` — `UPROPERTY(EditAnywhere, Category = "Experimental")` — Whether to allow persistent handle selection. If disabled, implicit indirect modification will also be disabled. Explicit (ctrl+mouse) will still work.
- L349 _public member_ `bool bDragDuplicateOnRotation = false;` — `UPROPERTY(EditAnywhere, Category=GizmoInteraction)` — When enabled, drag duplication will work on both translation and rotation (currently Level Editor only).
- L357 _public member_ `bool bScreenSpaceNudge = true;` — `UPROPERTY(EditAnywhere, Category=GizmoInteraction)` — When enabled, translate and scale nudging will be done based on camera view angle (nudge to the right will try to match what's "right" on the screen). When option is disabled, controls will be axis-based: Left/Right will control X, Up/Down will control Y, secondary Up/Down will control Z. Rotation nudging always does axis-based controls.
- L360 _public member_ `FTransformGizmoStyle Style;` — `UPROPERTY(Config, EditAnywhere, Category = "Appearance")`
- L363 _public member_ `FTransformGizmoInteraction Interaction;` — `UPROPERTY(Config, EditAnywhere, Category = "Interaction")`
- L366 _public member_ `FGizmoDebugSettings Debug;` — `UPROPERTY(Config, EditAnywhere, Category = "Debug", meta=(HideInDetailPanel))`

#### struct `FGizmoInteractionDescription`  
`struct FGizmoInteractionDescription`  
_L372-378_
- desc: FGizmoInteractionDescription provides a way to pass some interaction description in and out before/after starting/ending a gizmo manipulation
- L375 _public member_ `FInputDeviceRay Ray;` — ray based on the current input device
- L377 _public member_ `bool bIndirect = false;` — whether the interaction is direct or indirect

#### class `UTransformGizmo`  
`class UTransformGizmo : public UInteractiveGizmo, public IHoverBehaviorTarget, public IClickDragBehaviorTarget`  
_L388-1364_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UInteractiveGizmo,IHoverBehaviorTarget,IClickDragBehaviorTarget`
- desc: UTransformGizmo provides standard Transformation Gizmo interactions, applied to a UTransformProxy target object. By default the Gizmo will be a standard XYZ translate/rotate Gizmo (axis and plane translation).
- L457 _public member_ `} Style;`
- L468 _public prototype_ `virtual void SetDisallowNegativeScaling(bool bDisallow);` — By default, the nonuniform scale components can scale negatively. However, they can be made to clamp to zero instead by passing true here. This is useful for using the gizmo to flatten geometry. TODO: Should this affect uniform scaling too?
- L471 _public prototype_ `virtual void Setup() override;` — UInteractiveGizmo overrides
- L472 _public prototype_ `virtual void Shutdown() override;`
- L473 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L474 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L477 _public prototype_ `virtual bool CanRender(IToolsContextRenderAPI* InRenderAPI) const;` — Returns true if the gizmo should be rendered.
- L480 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& DevicePos) override;` — IHoverBehaviorTarget implementation
- L481 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L482 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L483 _public prototype_ `virtual void OnEndHover() override;`
- L486 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& PressPos) override;` — IClickDragBehaviorTarget implementation
- L487 _public prototype_ `virtual void OnClickPress(const FInputDeviceRay& PressPos) override;`
- L488 _public prototype_ `virtual void OnClickDrag(const FInputDeviceRay& DragPos) override;`
- L489 _public prototype_ `virtual void OnClickRelease(const FInputDeviceRay& ReleasePos) override;`
- L490 _public prototype_ `virtual void OnTerminateDragSequence() override;`
- L498 _public prototype_ `virtual void SetActiveTarget(UTransformProxy* Target, IToolContextTransactionProvider* TransactionProvider = nullptr, IGizmoStateTarget* InStateTarget = nullptr);` — Set the active target object for the Gizmo @param Target active target @param TransactionProvider optional IToolContextTransactionProvider implementation to use - by default uses GizmoManager @param InStateTarget optional IGizmoStateTarget implementation to use - will create a new UGizmoObjectModifyStateTarget none provided
- L503 _public prototype_ `virtual void ClearActiveTarget();` — Clear the active target object for the Gizmo
- L509 _public prototype_ `virtual void SetNewChildScale(const FVector& NewChildScale);` — Explicitly set the child scale. Mainly useful to "reset" the child scale to (1,1,1) when re-using Gizmo across multiple transform actions. @warning does not generate change/modify events!!
- L514 _public prototype_ `virtual void SetVisibility(bool bVisible);` — Set visibility for this Gizmo
- L519 _public prototype_ `void SetCustomizationFunction(const TFunction<const FGizmoCustomization()>& InFunction);` — Set customization function for this Gizmo
- L524 _public prototype_ `virtual void HandleWidgetModeChanged(UE::Widget::EWidgetMode InWidgetMode);` — Handle widget mode changed.
- L529 _public prototype_ `virtual void OnParametersChanged(const FGizmosParameters& InParameters);` — Handle user parameters changes
- L534 _public function_ `bool IsIndirectManipulation() const` — True if gizmo is being used for indirect manipulation
- L543 _public member_ `TObjectPtr<UTransformProxy> ActiveTarget;` — `UPROPERTY()` — The active target object for the Gizmo
- L547 _public member_ `TObjectPtr<UGizmoElementHitMultiTarget> HitTarget;` — `UPROPERTY()` — The hit target object
- L551 _public member_ `TObjectPtr<UMultiButtonClickDragBehavior> MultiIndirectClickDragBehavior;` — `UPROPERTY()` — The multi button mouse click behavior is accessible so that it can be modified to use different mouse keys.
- L555 _public member_ `TScriptInterface<ITransformGizmoSource> TransformGizmoSource;` — `UPROPERTY()` — Transform Gizmo Source
- L559 _public member_ `TObjectPtr<UGizmoElementGroup> GizmoElementRoot;` — `UPROPERTY()` — Root of renderable gizmo elements
- L563 _public member_ `TObjectPtr<UGizmoViewContext> GizmoViewContext;` — `UPROPERTY()` — Gizmo view context, needed for screen space interactions
- L567 _public member_ `bool bVisible = false;` — `UPROPERTY()` — Whether gizmo is visible.
- L571 _public member_ `bool bInInteraction = false;` — `UPROPERTY()` — Whether gizmo is interacting.
- L575 _public member_ `bool bSnapToWorldGrid = false;` — `UPROPERTY()` — If true, then when using world frame, Axis and Plane translation snap to the world grid via the ContextQueriesAPI (in PositionSnapFunction)
- L581 _public member_ `bool bGridSizeIsExplicit = false;` — `UPROPERTY()` — Optional grid size which overrides the Context Grid
- L583 _public member_ `FVector ExplicitGridSize;` — `UPROPERTY()`
- L589 _public member_ `bool bRotationGridSizeIsExplicit = false;` — `UPROPERTY()` — Optional grid size which overrides the Context Rotation Grid
- L591 _public member_ `FRotator ExplicitRotationGridSize;` — `UPROPERTY()`
- L597 _public member_ `bool bSnapToWorldRotGrid = false;` — `UPROPERTY()` — If true, then when using world frame, Axis and Plane translation snap to the world grid via the ContextQueriesAPI (in RotationSnapFunction)
- L600 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSetActiveTarget, UTransformGizmo*, UTransformProxy*);` — Broadcast at the end of a SetActiveTarget call.
- L601 _public member_ `FOnSetActiveTarget OnSetActiveTarget;`
- L604 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClearActiveTarget, UTransformGizmo*, UTransformProxy*);` — Broadcast at the beginning of a ClearActiveTarget call, when the ActiveTarget is not yet disconnected.
- L605 _public member_ `FOnClearActiveTarget OnAboutToClearActiveTarget;`
- L615 _protected member_ `TObjectPtr<UGizmoElementArrow> TranslateXAxisElement;` — `UPROPERTY()` — Translate X Axis
- L619 _protected member_ `TObjectPtr<UGizmoElementArrow> TranslateYAxisElement;` — `UPROPERTY()` — Translate Y Axis
- L623 _protected member_ `TObjectPtr<UGizmoElementArrow> TranslateZAxisElement;` — `UPROPERTY()` — Translate Z Axis
- L627 _protected member_ `TObjectPtr<UGizmoElementRectangle> TranslateScreenSpaceElement;` — `UPROPERTY()` — Translate screen-space
- L631 _protected member_ `TObjectPtr<UGizmoElementBox> TranslatePlanarXYElement;` — `UPROPERTY()` — Translate planar XY handle
- L635 _protected member_ `TObjectPtr<UGizmoElementBox> TranslatePlanarYZElement;` — `UPROPERTY()` — Translate planar YZ handle
- L639 _protected member_ `TObjectPtr<UGizmoElementBox> TranslatePlanarXZElement;` — `UPROPERTY()` — Translate planar XZ handle
- L643 _protected member_ `TObjectPtr<UGizmoElementTorus> RotateXAxisElement;` — `UPROPERTY()` — Rotate X Axis
- L647 _protected member_ `TObjectPtr<UGizmoElementTorus> RotateYAxisElement;` — `UPROPERTY()` — Rotate Y Axis
- L651 _protected member_ `TObjectPtr<UGizmoElementTorus> RotateZAxisElement;` — `UPROPERTY()` — Rotate Z Axis
- L655 _protected member_ `TObjectPtr<UGizmoElementTorus> RotateXGimbalElement;` — `UPROPERTY()` — Gimbal Rotate X Axis
- L659 _protected member_ `TObjectPtr<UGizmoElementTorus> RotateYGimbalElement;` — `UPROPERTY()` — Gimbal Rotate Y Axis
- L663 _protected member_ `TObjectPtr<UGizmoElementTorus> RotateZGimbalElement;` — `UPROPERTY()` — Gimbal Rotate Z Axis
- L667 _protected member_ `TObjectPtr<UGizmoElementGimbal> RotateGimbalElement;` — `UPROPERTY()` — Gimbal Rotate root element
- L671 _protected member_ `TObjectPtr<UGizmoElementCircle> RotateArcballElement;` — `UPROPERTY()` — Rotate arcball inner circle
- L675 _protected member_ `TObjectPtr<UGizmoElementCircle> RotateScreenSpaceElement;` — `UPROPERTY()` — Rotate screen space circle
- L679 _protected member_ `TObjectPtr<UGizmoElementArrow> ScaleXAxisElement;` — `UPROPERTY()` — Scale X Axis object
- L683 _protected member_ `TObjectPtr<UGizmoElementArrow> ScaleYAxisElement;` — `UPROPERTY()` — Scale Y Axis object
- L687 _protected member_ `TObjectPtr<UGizmoElementArrow> ScaleZAxisElement;` — `UPROPERTY()` — Scale Z Axis object
- L691 _protected member_ `TObjectPtr<UGizmoElementBox> ScalePlanarXYElement;` — `UPROPERTY()` — Scale planar XY handle
- L695 _protected member_ `TObjectPtr<UGizmoElementBox> ScalePlanarYZElement;` — `UPROPERTY()` — Scale planar YZ handle
- L699 _protected member_ `TObjectPtr<UGizmoElementBox> ScalePlanarXZElement;` — `UPROPERTY()` — Scale planar XZ handle
- L703 _protected member_ `TObjectPtr<UGizmoElementBox> ScaleUniformElement;` — `UPROPERTY()` — Uniform scale object
- L707 _protected member_ `TObjectPtr<UGizmoConstantFrameAxisSource> CameraAxisSource;` — `UPROPERTY()` — Axis that points towards camera, X/Y plane tangents aligned to right/up. Shared across Gizmos, and created internally during SetActiveTarget()
- L710 _protected prototype_ `void UpdateCameraAxisSource();` — internal function that updates CameraAxisSource by getting current view state from GizmoManager
- L714 _protected member_ `TScriptInterface<IGizmoStateTarget> StateTarget;` — `UPROPERTY()` — The state target is created internally during SetActiveTarget() if no one is provided.
- L720 _protected function_ `TUniqueFunction<bool()> ShouldAlignDestination = []()` — These are used to let the translation subgizmos use raycasts into the scene to align the gizmo with scene geometry. See comment for SetWorldAlignmentFunctions().
- L720 _protected member_ `TUniqueFunction<bool()> ShouldAlignDestination = []() { return false; };` — These are used to let the translation subgizmos use raycasts into the scene to align the gizmo with scene geometry. See comment for SetWorldAlignmentFunctions().
- L721 _protected function_ `TUniqueFunction<bool(const FRay&, FVector&)> DestinationAlignmentRayCaster = [](const FRay&, FVector&)`
- L721 _protected member_ `TUniqueFunction<bool(const FRay&, FVector&)> DestinationAlignmentRayCaster = [](const FRay&, FVector&) {return false; };`
- L723 _protected member_ `bool bDisallowNegativeScaling = false;`
- L728 _protected prototype_ `void RenderDebug(IToolsContextRenderAPI* RenderAPI);` — Renders various debug visualizations, if enabled.
- L731 _protected prototype_ `virtual void SetupBehaviors();` — Setup behaviors
- L734 _protected prototype_ `virtual void SetupIndirectBehaviors();` — Setup indirect behaviors
- L737 _protected prototype_ `virtual void SetupMaterials();` — Setup materials
- L740 _protected prototype_ `virtual void SetupOnClickFunctions();` — Setup on click functions
- L743 _protected prototype_ `virtual void UpdateMode();` — Update current gizmo mode based on transform source
- L746 _protected prototype_ `virtual void UpdateRotationMode();` — Update current gizmo rotation mode (default or gimbal)
- L749 _protected prototype_ `virtual void EnableMode(EGizmoTransformMode InGizmoMode, EAxisList::Type InAxisListToDraw);` — Enable the given mode with the specified axes, EAxisList::Type::None will hide objects associated with mode
- L752 _protected prototype_ `virtual void EnableTranslate(EAxisList::Type InAxisListToDraw);` — Enable translate using specified axis list
- L755 _protected prototype_ `virtual void EnableRotate(EAxisList::Type InAxisListToDraw);` — Enable rotate using specified axis list
- L758 _protected prototype_ `virtual void EnableScale(EAxisList::Type InAxisListToDraw);` — Enable scale using specified axis list
- L761 _protected prototype_ `virtual void EnablePlanarObjects(bool bTranslate, bool bEnableX, bool bEnableY, bool bEnableZ);` — Enable planar handles used by translate and scale
- L764 _protected prototype_ `virtual UGizmoElementArrow* MakeTranslateAxis(ETransformGizmoPartIdentifier InPartId, const FVector& InAxisDir, const FVector& InSideDir, UMaterialInterface* InMaterial);` — Construct translate axis handle
- L767 _protected prototype_ `virtual void UpdateTranslateAxis(UGizmoElementArrow* InElement);` — Updates the given translate axis handle with the current parameters (ie. size coefficient)
- L770 _protected prototype_ `virtual void UpdateTranslateAxis(UGizmoElementArrow* InElement, const EAxis::Type InAxis);` — Updates the given translate axis handle with the current parameters (ie. size coefficient)
- L773 _protected prototype_ `virtual void UpdateTranslateAxis(UGizmoElementArrow* InElement, const FVector& InAxisDir, const FVector& InSideDir);` — Updates the given translate axis handle with the current parameters (ie. size coefficient)
- L776 _protected prototype_ `virtual UGizmoElementArrow* MakeScaleAxis(ETransformGizmoPartIdentifier InPartId, const FVector& InAxisDir, const FVector& InSideDir, UMaterialInterface* InMaterial);` — Construct scale axis handle
- L779 _protected prototype_ `virtual void UpdateScaleAxis(UGizmoElementArrow* InElement);` — Updates the given scale axis handle with the current parameters (ie. size coefficient).
- L782 _protected prototype_ `virtual void UpdateScaleAxis(UGizmoElementArrow* InElement, const EAxis::Type InAxis);` — Updates the given scale axis handle with the current parameters (ie. size coefficient).
- L787 _protected prototype_ `virtual void UpdateScaleAxis(UGizmoElementArrow* InElement, const FVector& InAxisDir, const FVector& InSideDir);` — Updates the given scale axis handle with the current parameters (ie. size coefficient).
- L790 _protected prototype_ `virtual void UpdateAllScaleAxis();` — Updates all scale axis handles with the current parameters (ie. size coefficient)
- L793 _protected prototype_ `UGizmoElementTorus* MakeDefaultRotateAxis(const ETransformGizmoPartIdentifier InPartId);` — Construct the default rotate axis handle based on the ETransformGizmoPartIdentifier.
- L796 _protected prototype_ `virtual UGizmoElementTorus* MakeRotateAxis(ETransformGizmoPartIdentifier InPartId, const FVector& TorusAxis0, const FVector& TorusAxis1, UMaterialInterface* InMaterial, UMaterialInterface* InCurrentMaterial);` — Construct rotate axis handle
- L800 _protected prototype_ `virtual void UpdateRotateAxis(UGizmoElementTorus* InElement);` — Updates the given rotate axis handle with the current parameters (ie. size coefficient)
- L803 _protected prototype_ `virtual UGizmoElementBox* MakeUniformScaleHandle();` — Construct uniform scale handle
- L806 _protected prototype_ `virtual void UpdateUniformScaleHandle(UGizmoElementBox* InElement);` — Updates the given uniform scale handle with the current parameters (ie. size coefficient)
- L809 _protected prototype_ `virtual UGizmoElementBox* MakePlanarHandle(ETransformGizmoPartIdentifier InPartId, const FVector& InUpDirection, const FVector& InSideDirection, const FVector& InPlaneNormal, UMaterialInterface* InMaterial);` — Construct planar axis handle
- L813 _protected prototype_ `virtual void UpdatePlanarHandle(UGizmoElementBox* InElement, const FVector& InUpDirection, const FVector& InSideDirection);` — Updates the given uniform scale handle with the current parameters (ie. size coefficient)
- L816 _protected prototype_ `virtual UGizmoElementRectangle* MakeTranslateScreenSpaceHandle();` — Construct translate screen space handle
- L819 _protected prototype_ `virtual void UpdateTranslateScreenSpaceHandle(UGizmoElementRectangle* InElement);` — Updates the given translate screen space handle with the current parameters (ie. size coefficient)
- L822 _protected prototype_ `virtual UGizmoElementCircle* MakeArcballCircleHandle(ETransformGizmoPartIdentifier InPartId, float InRadius, const FLinearColor& InColor);` — Construct arcball screen space handle
- L825 _protected prototype_ `virtual UGizmoElementCircle* MakeRotateCircleHandle(ETransformGizmoPartIdentifier InPartId, float InRadius, const FLinearColor& InColor, const EGizmoElementDrawType InDrawType = EGizmoElementDrawType::Fill, const TOptional<FLinearColor>& InLineColorOverride = TOptional<FLinearColor>());` — Construct rotate screen space handle
- L829 _protected prototype_ `virtual void UpdateRotateCircleHandle(UGizmoElementCircle* InElement, float InRadius);` — Updates the given rotate screen space handle with the current parameters (ie. size coefficient)
- L832 _protected prototype_ `virtual void UpdateElements();` — Updates all gizmo elements based on current parameters
- L835 _protected prototype_ `virtual FTransform GetGizmoTransform() const;` — Get gizmo transform based on cached current transform.
- L838 _protected prototype_ `virtual FInputRayHit UpdateHoveredPart(const FInputDeviceRay& DevicePos);` — Determine hit part and update hover state based on current input ray
- L841 _protected prototype_ `virtual FVector GetWorldAxis(const FVector& InAxis) const;` — Get current interaction axis
- L844 _protected prototype_ `virtual FVector GetGimbalRotationAxis(const int32 InAxis) const;` — Get gimbal rotation axis (InAxis is expected to be in [0,2] range)
- L847 _protected prototype_ `virtual float GetNearestRayParamToInteractionAxis(const FInputDeviceRay& InRay);` — Get nearest param along input ray to the current interaction axis
- L850 _protected prototype_ `virtual bool GetRayParamIntersectionWithInteractionPlane(const FInputDeviceRay& InRay, FVector::FReal& OutHitParam);` — Return true if input ray intersects current interaction plane and return param along ray in OutHitParam
- L853 _protected prototype_ `virtual void UpdateHoverState(const bool bInHover, const ETransformGizmoPartIdentifier InPartId);` — Update hover state for given part id
- L856 _protected prototype_ `virtual void ResetHoverStates(const EGizmoTransformMode InMode);` — Reset all hover states related to the transform mode to false
- L859 _protected prototype_ `virtual void UpdateInteractingState(const bool bInInteracting, const ETransformGizmoPartIdentifier InPartId, const bool bIdOnly = false);` — Update interacting state for given part id
- L862 _protected prototype_ `virtual void ResetInteractingStates(const EGizmoTransformMode InMode);` — Reset all interacting states related to the transform mode to false
- L865 _protected prototype_ `virtual void BeginTransformEditSequence();` — Called at the start of a sequence of gizmo transform edits
- L868 _protected prototype_ `virtual void EndTransformEditSequence();` — Called at the end of a sequence of gizmo transform edits.
- L875 _protected prototype_ `virtual void OnClickPressTranslateXAxis(const FInputDeviceRay& PressPos);` — Handle click press for translate X axis
- L878 _protected prototype_ `virtual void OnClickPressTranslateYAxis(const FInputDeviceRay& PressPos);` — Handle click press for translate Y axis
- L881 _protected prototype_ `virtual void OnClickPressTranslateZAxis(const FInputDeviceRay& PressPos);` — Handle click press for translate Z axis
- L884 _protected prototype_ `virtual void OnClickPressAxis(const FInputDeviceRay& PressPos);` — Handle click press for translate axes
- L887 _protected prototype_ `virtual void OnClickDragTranslateAxis(const FInputDeviceRay& DragPos);` — Handle click drag for translate axes
- L890 _protected prototype_ `virtual void OnClickReleaseTranslateAxis(const FInputDeviceRay& ReleasePos);` — Handle click release for translate axes
- L897 _protected prototype_ `virtual void OnClickPressTranslateXYPlanar(const FInputDeviceRay& PressPos);` — Handle click press for translate XY planar
- L900 _protected prototype_ `virtual void OnClickPressTranslateYZPlanar(const FInputDeviceRay& PressPos);` — Handle click press for translate YZ planar
- L903 _protected prototype_ `virtual void OnClickPressTranslateXZPlanar(const FInputDeviceRay& PressPos);` — Handle click press for translate XZ planar
- L906 _protected prototype_ `virtual void OnClickPressPlanar(const FInputDeviceRay& PressPos);` — Handle click press for generic planar
- L909 _protected prototype_ `virtual void OnClickPressTranslatePlanar(const FInputDeviceRay& PressPos);` — Handle click press for translate planar
- L912 _protected prototype_ `virtual void OnClickDragTranslatePlanar(const FInputDeviceRay& DragPos);` — Handle click drag for translate planar
- L915 _protected prototype_ `virtual void OnClickReleaseTranslatePlanar(const FInputDeviceRay& ReleasePos);` — Handle click release for translate planar
- L918 _protected prototype_ `virtual FVector ComputeAxisTranslateDelta(double InStartParam, double InEndParam);` — Compute translate axis delta based on start/end params
- L921 _protected prototype_ `virtual FVector ComputePlanarTranslateDelta(const FVector& InStartPoint, const FVector& InEndPoint);` — Compute translate planar delta based on world space start/end points
- L928 _protected prototype_ `virtual void OnClickPressScreenSpaceTranslate(const FInputDeviceRay& PressPos);` — Handle click press for screen-space translate
- L931 _protected prototype_ `virtual void OnClickDragScreenSpaceTranslate(const FInputDeviceRay& DragPos);` — Handle click drag for screen-space translate
- L934 _protected prototype_ `virtual void OnClickReleaseScreenSpaceTranslate(const FInputDeviceRay& ReleasePos);` — Handle click release for screen-space translate
- L941 _protected prototype_ `virtual void OnClickPressRotateXAxis(const FInputDeviceRay& InPressPos);` — Handle click press for rotate X axis
- L944 _protected prototype_ `virtual void OnClickPressRotateYAxis(const FInputDeviceRay& InPressPos);` — Handle click press for rotate Y axis
- L947 _protected prototype_ `virtual void OnClickPressRotateZAxis(const FInputDeviceRay& InPressPos);` — Handle click press for rotate Z axis
- L950 _protected prototype_ `virtual void OnClickPressRotateAxis(const FInputDeviceRay& InPressPos);` — Handle click press for any rotate axis
- L953 _protected prototype_ `virtual void OnClickDragRotateAxis(const FInputDeviceRay& InDragPos);` — Handle click drag for rotate axis
- L956 _protected prototype_ `virtual void OnClickReleaseRotateAxis(const FInputDeviceRay& InReleasePos);` — Handle click release for rotate axes
- L959 _protected prototype_ `virtual FVector2D GetScreenRotateAxisDir(const FInputDeviceRay& InPressPos);` — Get screen-space axis for rotation drag
- L962 _protected prototype_ `virtual FVector2D GetScreenGimbalRotateAxisDir(const FInputDeviceRay& InPressPos);` — Get screen-space axis for gimbal rotation drag
- L965 _protected prototype_ `FVector2D GetWorldToScreenRotateAxisDir(const FInputDeviceRay& InPressPos, const FVector& InWorldAxis);` — Get screen-space axis based on a world space axis
- L968 _protected prototype_ `virtual double ComputeAxisRotateDeltaAngle(const FVector2D& InStartPos, const FInputDeviceRay& InDragPos);` — Compute angle (degrees) delta based on screen-space start/end positions. Intended to be used in combination with ComputeAxisRotateDelta
- L971 _protected prototype_ `virtual FQuat ComputeAxisRotateDelta(const double& InDeltaAngle);` — Compute rotate delta based on screen-space angle delta (in degrees)
- L974 _protected prototype_ `virtual FQuat ComputeGimbalRotateDelta(const FVector2D& InStartPos, const FVector2D& InEndPos, const double InAngleSign = 1.0);` — Compute gimbal rotate delta based on screen-space start/end positions
- L977 _protected prototype_ `virtual bool OnClickPressRotateArc( const FInputDeviceRay& InPressPos, const FVector& InPlaneNormal, const FVector& InPlaneAxis1, const FVector& InPlaneAxis2, const EAxis::Type InAxis = EAxis::None);` — Prepares data for arc rotation. This will return false if this is not possible (the rotate handle is perpendicular to the view)
- L986 _protected prototype_ `virtual void OnClickPressGimbalRotateAxis(const FInputDeviceRay& InPressPos);` — Handle click press for any gimbal rotate axis
- L989 _protected prototype_ `virtual void OnClickDragGimbalRotateAxis(const FInputDeviceRay& InDragPos);` — Handle click drag for gimbal rotate axis
- L996 _protected prototype_ `virtual void OnClickPressScreenSpaceRotate(const FInputDeviceRay& PressPos);` — Handle click press for screen-space rotate
- L999 _protected prototype_ `virtual void OnClickDragScreenSpaceRotate(const FInputDeviceRay& InDragPos);` — Handle click drag for screen-space rotate
- L1002 _protected prototype_ `virtual void OnClickReleaseScreenSpaceRotate(const FInputDeviceRay& ReleasePos);` — Handle click release for screen-space rotate
- L1005 _protected prototype_ `virtual FQuat ComputeAngularRotateDelta(FQuat::FReal InStartAngle, FQuat::FReal InEndAngle);` — Compute rotate delta based on start/end angles
- L1012 _protected prototype_ `virtual void OnClickPressArcBallRotate(const FInputDeviceRay& PressPos);` — Handle click press for arc ball rotate
- L1015 _protected prototype_ `virtual void OnClickDragArcBallRotate(const FInputDeviceRay& DragPos);` — Handle click drag for arc ball rotate
- L1018 _protected prototype_ `virtual void OnClickReleaseArcBallRotate(const FInputDeviceRay& ReleasePos);` — Handle click release for arc ball rotate
- L1021 _protected prototype_ `float GetWorldRadius(const float InRadius) const;` — Get the arc ball sphere world radius
- L1024 _protected prototype_ `float GetSizeCoefficient() const;`
- L1031 _protected prototype_ `virtual void OnClickPressScaleXAxis(const FInputDeviceRay& PressPos);` — Handle click press for scale X axis
- L1034 _protected prototype_ `virtual void OnClickPressScaleYAxis(const FInputDeviceRay& PressPos);` — Handle click press for scale Y axis
- L1037 _protected prototype_ `virtual void OnClickPressScaleZAxis(const FInputDeviceRay& PressPos);` — Handle click press for scale Z axis
- L1040 _protected prototype_ `virtual void OnClickPressScaleXYPlanar(const FInputDeviceRay& PressPos);` — Handle click press for scale XY planar
- L1043 _protected prototype_ `virtual void OnClickPressScaleYZPlanar(const FInputDeviceRay& PressPos);` — Handle click press for scale YZ planar
- L1046 _protected prototype_ `virtual void OnClickPressScaleXZPlanar(const FInputDeviceRay& PressPos);` — Handle click press for scale XZ planar
- L1049 _protected prototype_ `virtual void OnClickPressScaleXYZ(const FInputDeviceRay& PressPos);` — Handle click press for uniform scale
- L1052 _protected prototype_ `virtual void OnClickPressScale(const FInputDeviceRay& PressPos);` — Handle click press for all scale methods
- L1055 _protected prototype_ `virtual void OnClickDragScaleAxis(const FInputDeviceRay& DragPos);` — Handle click drag for scale axes
- L1058 _protected prototype_ `virtual void OnClickDragScalePlanar(const FInputDeviceRay& DragPos);` — Handle click drag for scale planar
- L1061 _protected prototype_ `virtual void OnClickDragScaleXYZ(const FInputDeviceRay& DragPos);` — Handle click drag for uniform scale
- L1064 _protected prototype_ `virtual void OnClickDragScale(const FInputDeviceRay& DragPos);` — Handle click drag for all scale
- L1067 _protected prototype_ `virtual void OnClickReleaseScaleAxis(const FInputDeviceRay& ReleasePos);` — Handle click release for scale axes
- L1070 _protected prototype_ `virtual void OnClickReleaseScalePlanar(const FInputDeviceRay& ReleasePos);` — Handle click release for scale planar
- L1073 _protected prototype_ `virtual void OnClickReleaseScaleXYZ(const FInputDeviceRay& ReleasePos);` — Handle click release for uniform scale
- L1076 _protected prototype_ `virtual FVector ComputeScaleDelta(const FVector2D& InStartPos, const FVector2D& InEndPos, FVector2D& OutScreenDelta);` — Compute scale delta based on screen space start/end positions
- L1083 _protected prototype_ `static FVector2D GetScreenProjectedAxis(const UGizmoViewContext* View, const FVector& InLocalAxis, const FTransform& InLocalToWorld = FTransform::Identity);` — Returns 2D vector projection of input axis onto input view plane
- L1090 _protected prototype_ `virtual void ApplyTranslateDelta(const FVector& InTranslateDelta);` — Apply translate delta to transform proxy
- L1093 _protected prototype_ `virtual void ApplyRotateDelta(const FQuat& InRotateDelta);` — Apply rotate delta to transform proxy
- L1096 _protected prototype_ `virtual void ApplyScaleDelta(const FVector& InScaleDelta);` — Apply scale delta to transform proxy
- L1099 _protected prototype_ `bool PositionSnapFunction(const FVector& WorldPosition, FVector& SnappedPositionOut) const;` — Axis and Plane TransformSources use this function to execute worldgrid snap queries
- L1100 _protected prototype_ `FQuat RotationSnapFunction(const FQuat& DeltaRotation) const;`
- L1102 _protected prototype_ `void SnapTranslateDelta(FVector& InOutWorldDelta) const;`
- L1103 _protected prototype_ `void SnapRotateDelta(FQuat& InOutWorldDelta) const;`
- L1104 _protected prototype_ `void SnapRotateAngleDelta(double& InOutAngleDelta) const;`
- L1105 _protected prototype_ `void SnapScaleDelta(FVector& InOutLocalScaleDelta) const;`
- L1108 _protected prototype_ `virtual uint32 GetMaxPartIdentifier() const;` — Get max part identifier.
- L1111 _protected prototype_ `virtual bool VerifyPartIdentifier(uint32 InPartIdentifier) const;` — Verify part identifier is within recognized range of transform gizmo part ids
- L1114 _protected prototype_ `bool IsVisible(const EViewportContext InViewportContext = EViewportContext::Focused) const;` — Returns whether the gizmo is visible in the viewport.
- L1117 _protected prototype_ `virtual bool CanInteract(const EViewportContext InViewportContext = EViewportContext::Focused) const;` — Returns whether the gizmo can interact. Note that this can be true even if the gizmo is not visible to support indirect manipulation.
- L1120 _protected prototype_ `const FRotationContext& GetRotationContext() const;` — Returns the current rotation context.
- L1126 _protected member_ `TObjectPtr<UMaterialInterface> TransparentVertexColorMaterial;` — `UPROPERTY()` — Materials and colors to be used when drawing the items for each axis
- L1128 _protected member_ `TObjectPtr<UMaterialInterface> GridMaterial;` — `UPROPERTY()`
- L1130 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialX;` — `UPROPERTY()`
- L1132 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialY;` — `UPROPERTY()`
- L1134 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> AxisMaterialZ;` — `UPROPERTY()`
- L1136 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> CurrentAxisMaterial;` — `UPROPERTY()`
- L1138 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> GreyMaterial;` — `UPROPERTY()`
- L1140 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> WhiteMaterial;` — `UPROPERTY()`
- L1142 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> OpaquePlaneMaterialXY;` — `UPROPERTY()`
- L1145 _protected member_ `TArray<TFunction<void(UTransformGizmo* TransformGizmo, const FInputDeviceRay& PressPos)> > OnClickPressFunctions;` — Array of function pointers, indexed by gizmo part id, to handle click press behavior
- L1148 _protected member_ `TArray<TFunction<void(UTransformGizmo* TransformGizmo, const FInputDeviceRay& DragPos)> > OnClickDragFunctions;` — Array of function pointers, indexed by gizmo part id, to handle click drag behavior
- L1151 _protected member_ `TArray<TFunction<void(UTransformGizmo* TransformGizmo, const FInputDeviceRay& ReleasePos)> > OnClickReleaseFunctions;` — Array of function pointers, indexed by gizmo part id, to handle click release behavior
- L1154 _protected member_ `TFunction<const FGizmoCustomization()> CustomizationFunction;` — Customization function (to override default material or increment gizmo size for example)
- L1158 _protected member_ `double ScaleMultiplier = 0.01;` — `UPROPERTY()` — Percentage-based scale multiplier
- L1162 _protected member_ `FTransform CurrentTransform = FTransform::Identity;` — `UPROPERTY()` — Current transform
- L1166 _protected member_ `EGizmoTransformMode CurrentMode = EGizmoTransformMode::None;` — `UPROPERTY()` — Currently rendered transform mode
- L1170 _protected member_ `TEnumAsByte<EAxisList::Type> CurrentAxisToDraw = EAxisList::None;` — `UPROPERTY()` — Currently rendered axis list
- L1174 _protected member_ `ETransformGizmoPartIdentifier LastHitPart = ETransformGizmoPartIdentifier::Default;` — `UPROPERTY()` — Last hit part
- L1177 _protected member_ `ETransformGizmoPartIdentifier LastHitPartPerMode[static_cast<uint8>(EGizmoTransformMode::Max)];` — Last hit part per mode
- L1179 _protected prototype_ `ETransformGizmoPartIdentifier GetCurrentModeLastHitPart() const;`
- L1180 _protected prototype_ `void SetModeLastHitPart(const EGizmoTransformMode InMode, const ETransformGizmoPartIdentifier InIdentifier);`
- L1182 _protected prototype_ `EAxisList::Type GetInteractionAxisList() const;`
- L1183 _protected prototype_ `virtual void SetInteractionAxisList(const EAxisList::Type InAxisList);`
- L1193 _protected member_ `TEnumAsByte<EAxisList::Type> InteractionAxisList;` — `UPROPERTY(Getter, Setter)` — Active axis type (only valid between state target BeginModify/EndModify)
- L1197 _protected member_ `FVector InteractionAxisOrigin;` — `UPROPERTY()` — Active world space axis origin (only valid between state target BeginModify/EndModify)
- L1201 _protected member_ `FVector InteractionAxisDirection;` — `UPROPERTY()` — Active world space axis (only valid between state target BeginModify/EndModify)
- L1205 _protected member_ `double InteractionAxisStartParam;` — `UPROPERTY()` — Active interaction start hit param (only valid between state target BeginModify/EndModify)
- L1209 _protected member_ `double InteractionAxisCurrParam;` — `UPROPERTY()` — Active interaction current hit param (only valid between state target BeginModify/EndModify)
- L1213 _protected member_ `FVector InteractionPlanarOrigin;` — `UPROPERTY()` — Active world space planar origin (only valid between state target BeginModify/EndModify)
- L1217 _protected member_ `FVector InteractionPlanarNormal;` — `UPROPERTY()` — Active world space normal used for planar (only valid between state target BeginModify/EndModify)
- L1221 _protected member_ `FVector NormalToRemove;` — `UPROPERTY()` — Active normal to remove from axis translation (only valid between state target BeginModify/EndModify)
- L1225 _protected member_ `FVector InteractionPlanarAxisX;` — `UPROPERTY()` — Active world space axis X used for planar (only valid between state target BeginModify/EndModify)
- L1229 _protected member_ `FVector InteractionPlanarAxisY;` — `UPROPERTY()` — Active world space axis Y used for planar (only valid between state target BeginModify/EndModify)
- L1233 _protected member_ `FVector InteractionPlanarStartPoint;` — `UPROPERTY()` — Active interaction start point planar (only valid between state target BeginModify/EndModify)
- L1237 _protected member_ `FVector InteractionPlanarCurrPoint;` — `UPROPERTY()` — Active interaction current point planar (only valid between state target BeginModify/EndModify)
- L1241 _protected member_ `double InteractionStartAngle;` — `UPROPERTY()` — Active interaction rotation start angle (only valid between state target BeginModify/EndModify)
- L1245 _protected member_ `double InteractionCurrAngle;` — `UPROPERTY()` — Active interaction rotation curr angle (only valid between state target BeginModify/EndModify)
- L1249 _protected member_ `FVector2D InteractionScreenAxisDirection;` — `UPROPERTY()` — Active interaction screen axis dir (only valid between state target BeginModify/EndModify)
- L1253 _protected member_ `FVector2D NormalProjectionToRemove;` — `UPROPERTY()` — Active normal projection to remove from drag when rotating
- L1257 _protected member_ `FVector2D InteractionScreenStartPos;` — `UPROPERTY()` — Active interaction screen start pos (only valid between state target BeginModify/EndModify)
- L1261 _protected member_ `FVector2D InteractionScreenEndPos;` — `UPROPERTY()` — Active interaction screen end pos (only valid between state target BeginModify/EndModify)
- L1265 _protected member_ `FVector2D InteractionScreenCurrPos;` — `UPROPERTY()` — Active interaction screen current pos (only valid between state target BeginModify/EndModify)
- L1269 _protected member_ `FVector InteractionArcBallStartPoint;` — `UPROPERTY()` — Active interaction arc ball start point
- L1273 _protected member_ `FVector InteractionArcBallCurrPoint;` — `UPROPERTY()` — Active interaction arc ball current point
- L1277 _protected member_ `FQuat StartRotation = FQuat::Identity;` — `UPROPERTY()` — Arc ball start rotation
- L1280 _protected member_ `FQuat CurrentRotation = FQuat::Identity;` — Arc ball current rotation
- L1284 _protected member_ `bool bIndirectManipulation;` — `UPROPERTY()` — Indirect manipulation
- L1288 _protected member_ `bool bDeferDrag = true;` — `UPROPERTY()` — Defer drag function on tick to avoid firing too many drag moves
- L1291 _protected member_ `TFunction<void()> PendingDragFunction;` — Pending drag function to be called if bDeferDrag is true
- L1298 _protected member_ `bool bSequentialIndirectAxesButtons = true;` — `UPROPERTY()` — When disabled, Ctrl+LMB manipulates X, Ctrl+RMB manipulates Y, and Ctrl+LMB+RMB manipulates Z. When enabled LMB is mapped to X, MMB is mapped to Y, and RMB is mapped to Z.
- L1302 _protected member_ `bool bUniformIndirectScale = false;` — `UPROPERTY()` — When enabled, all indirect scale manipulations will trigger uniform scaling
- L1308 _protected member_ `bool bScreenSpaceIndirectOrthographicManipulation = true;` — `UPROPERTY()` — When enabled and in an orthographic view, Ctrl+LMB-Drag will move or scale in screen space, and Ctrl+RMB-Drag will rotate in screen space.
- L1312 _protected member_ `TEnumAsByte<EAxisRotateMode::Type> DefaultRotateMode = EAxisRotateMode::ScreenArc;` — `UPROPERTY()` — Default rotate mode used when using axis rotation handles.
- L1315 _protected member_ `TEnumAsByte<EAxisRotateMode::Type> RotateMode = EAxisRotateMode::ScreenArc;` — Actual rotate mode used (based on view dependant information).
- L1318 _protected member_ `bool bTrySwitchingToNormalPull = false;` — Switch from tangential to normal projection based on the first mouse drag.
- L1321 _protected member_ `bool bGimbalRotationMode = false;` — Used to check if the gimbal mode is currently active (this is updated when ticking the gizmo)
- L1324 _protected member_ `UE_INTERNAL FOnGizmoInteraction OnPreCanInteractDelegate;` — pre-click delegate called before a click & drag interaction can start.
- L1327 _protected member_ `UE_INTERNAL FOnGizmoInteraction OnPostInteractionDelegate;` — conditional post-release delegate after a click & drag interaction ends.
- L1332 _public prototype_ `UE_INTERNAL FOnGizmoInteraction& OnPreCanInteract();` — Delegate to a pre-click called delegate before a click & drag interaction can start.
- L1335 _public prototype_ `UE_INTERNAL FOnGizmoInteraction& OnPostInteraction();` — Delegate to a conditional post-release delegate after a click & drag interaction ends.
- L1363 _private member_ `} DebugData;`

#### struct `UTransformGizmo::FGizmoStyle`  
`struct FGizmoStyle`  
_L398-457_
- desc: Contains all styling properties.
- L401 _public member_ `float AxisSizeMultiplier = 1.0f;` — Applies to axis lengths and radii
- L404 _public member_ `float LineThicknessMultiplier = 1.0f;` — Applies to lines
- L406 _public member_ `static constexpr float AxisRadius = 1.5f;`
- L407 _public member_ `static constexpr float AxisLengthOffset = 20.0f;`
- L410 _public member_ `float TranslateAxisLength = 70.0f;` — Transform
- L411 _public member_ `static constexpr float TranslateAxisConeAngle = 16.0f;`
- L412 _public member_ `static constexpr float TranslateAxisConeHeight = 22.0f;`
- L413 _public member_ `static constexpr float TranslateAxisConeRadius = 7.0f;`
- L414 _public member_ `static constexpr float TranslateScreenSpaceHandleSize = 14.0f;`
- L416 _public member_ `float RotateArcballSphereRadius = 70.0f;`
- L417 _public member_ `float RotateAxisRadius = 70.0f;`
- L418 _public member_ `float RotateCircleRadius = 70.0f;`
- L421 _public member_ `static constexpr float RotateAxisInnerRadius = 1.25f;` — Rotation
- L422 _public member_ `static constexpr int32 RotateAxisNumSegments = 64;`
- L423 _public member_ `static constexpr int32 RotateAxisInnerSlices = 8;`
- L425 _public member_ `static constexpr float RotateAxisOuterRadiusOffset = 3.0f;` — Offset from RotateAxisRadius
- L426 _public member_ `static constexpr float RotateOuterCircleRadiusOffset = 3.0f;` — Offset from RotateCircleRadius
- L427 _public member_ `static constexpr float RotateScreenSpaceRadiusOffset = 13.0f;` — Offset from RotateCircleRadius
- L430 _public member_ `float ScaleAxisLength = 70.0f;` — Scale
- L431 _public member_ `static constexpr float ScaleAxisCubeDim = 12.0f;`
- L433 _public member_ `static constexpr float PlanarHandleOffset = -15.0f;` — Offset from TranslateAxisLength
- L434 _public member_ `static constexpr float PlanarHandleSize = 15.0f;`
- L435 _public member_ `static constexpr float PlanarHandleThickness = 2.0f;`
- L437 _public member_ `static constexpr float AxisTransparency = 0.8f;`
- L439 _public member_ `static constexpr FLinearColor AxisColorX = FLinearColor(0.594f, 0.0197f, 0.0f);` — `UE_DEPRECATED(5.6, "Use AxisDisplayInfo::GetAxisColor(EAxisList::X) instead")`
- L441 _public member_ `static constexpr FLinearColor AxisColorY = FLinearColor(0.1349f, 0.3959f, 0.0f);` — `UE_DEPRECATED(5.6, "Use AxisDisplayInfo::GetAxisColor(EAxisList::Y) instead")`
- L443 _public member_ `static constexpr FLinearColor AxisColorZ = FLinearColor(0.0251f, 0.207f, 0.85f);` — `UE_DEPRECATED(5.6, "Use AxisDisplayInfo::GetAxisColor(EAxisList::Z) instead")`
- L444 _public member_ `static constexpr FLinearColor ScreenAxisColor = FLinearColor(0.76f, 0.72f, 0.14f);`
- L445 _public member_ `static constexpr FLinearColor PlaneColorXY = FLinearColor(1.0f, 1.0f, 0.0f);`
- L446 _public member_ `static constexpr FLinearColor ArcBallColor = FLinearColor(0.5f, 0.5f, 0.5f, 0.03f);`
- L447 _public member_ `static constexpr FLinearColor ScreenSpaceColor = FLinearColor(0.765f, 0.765f, 0.765f);`
- L448 _public member_ `static constexpr FLinearColor CurrentColor = FLinearColor(1.0f, 1.0f, 0.0f);`
- L449 _public member_ `static constexpr FLinearColor GreyColor = FLinearColor(0.50f, 0.50f, 0.50f);`
- L450 _public member_ `static constexpr FLinearColor WhiteColor = FLinearColor(1.0f, 1.0f, 1.0f);`
- L452 _public member_ `static constexpr FLinearColor RotateScreenSpaceCircleColor = WhiteColor;`
- L453 _public member_ `static constexpr FLinearColor RotateOuterCircleColor = GreyColor;`
- L454 _public member_ `static constexpr FLinearColor RotateArcballCircleColor = WhiteColor.CopyWithNewOpacity(0.1f);`
- L456 _public member_ `static constexpr float LargeOuterAlpha = 0.5f;`

#### struct `UTransformGizmo::FGizmoDebugData`  
`struct FGizmoDebugData`  
_L1339-1363_
- L1342 _public member_ `bool bIsEditing = false;` — Determines whether certain data is displayed, ie. drag operation deltas.
- L1344 _public member_ `FTransform TransformStart;`
- L1345 _public member_ `FTransform TransformCurrent;`
- L1347 _public member_ `FTransform InteractionStart;`
- L1348 _public member_ `FTransform InteractionCurrent;`
- L1349 _public member_ `FVector InteractionPlaneNormal;`
- L1352 _public member_ `FVector2D InteractionScreenDirection;` — Can indicate a 2D drag direction, etc.
- L1355 _public member_ `bool bDebugRotate = false;` — Debug attributes to display the pull direction
- L1356 _public member_ `FVector DebugDirection = FVector::ZeroVector;`
- L1357 _public member_ `FVector DebugClosest = FVector::ZeroVector;`
- L1358 _public member_ `FVector DebugNormalRemoved = FVector::ZeroVector;`
- L1359 _public member_ `FVector DebugNormalSkip = FVector::ZeroVector;`
- L1360 _public member_ `double InteractionAngleStart;`
- L1361 _public member_ `double InteractionAngleCurrent;`
- L1362 _public member_ `double InteractionRadius;`

#### Free symbols / members of external scopes

- L36 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L107 _prototype_ `ENUM_RANGE_BY_COUNT(ETransformGizmoPartIdentifier, ETransformGizmoPartIdentifier::Max);`
- L109 _namespace_ `namespace UE`
- L109 _namespace_ `namespace Editor` (scope `UE`)
- L109 _namespace_ `namespace InteractiveToolsFramework` (scope `UE::Editor`)
- L127 _prototype_ `ENUM_CLASS_FLAGS(ETransformGizmoShowFlags);`
- L380 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoInteraction, const FGizmoInteractionDescription&);`
- L380 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmoInteraction, const FGizmoInteractionDescription&);`
- L600 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSetActiveTarget, UTransformGizmo*, UTransformProxy*);` — Broadcast at the end of a SetActiveTarget call.
- L604 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClearActiveTarget, UTransformGizmo*, UTransformProxy*);` — Broadcast at the beginning of a ClearActiveTarget call, when the ActiveTarget is not yet disconnected.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorGizmos/TransformGizmoInterfaces.h` (Public)


#### enum `EGizmoTransformMode`  
`enum class EGizmoTransformMode : uint8`  
_L17-24_
- reflection: `UENUM()`
- desc: Interface for the Transform gizmo.
- L19 _public enumerator_ `None = 0`
- L20 _public enumerator_ `Translate`
- L21 _public enumerator_ `Rotate`
- L22 _public enumerator_ `Scale`
- L23 _public enumerator_ `Max`

#### enum `EAxisRotateMode::Type`  
`enum Type : uint8`  
_L29-34_
- L31 _public enumerator_ `Pull = 0`
- L32 _public enumerator_ `Arc = 1`
- L33 _public enumerator_ `ScreenArc = 2` — Like Arc, but in screen space, rather than aligned to the associated axis

#### enum `EGizmoTransformScaleType`  
`enum class EGizmoTransformScaleType : uint8`  
_L38-48_
- reflection: `UENUM()`
- L41 _public enumerator_ `Default = 0 UMETA(DisplayName="Offset")` — Apply scale as an additive change to the current scale value.
- L44 _public enumerator_ `PercentageBased = 1` — Apply scale proportionally, multiplying the starting scale value.
- L47 _public enumerator_ `Legacy = 2` — Use the legacy editor settings to determine how scale is applied.

#### enum `EViewportContext`  
`enum class EViewportContext : uint8`  
_L50-54_
- L52 _public enumerator_ `Hovered`
- L53 _public enumerator_ `Focused`

#### struct `FRotationContext`  
`struct FRotationContext`  
_L61-80_
- reflection: `USTRUCT()`
- L67 _public member_ `bool bUseExplicitRotator = false;` — `UPROPERTY()` — Enable explicit rotation axis
- L71 _public member_ `EEulerRotationOrder RotationOrder = EEulerRotationOrder::XYZ;` — `UPROPERTY()` — Order in which this rotation is expressed
- L75 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY()` — Rotation values
- L79 _public member_ `FTransform Offset = FTransform::Identity;` — `UPROPERTY()` — Parent offset transform

#### class `UTransformGizmoSource`  
`class UTransformGizmoSource : public UInterface`  
_L83-86_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `ITransformGizmoSource`  
`class ITransformGizmoSource`  
_L91-134_
- desc: ITransformGizmoSource is an interface for providing gizmo mode configuration information.
- L98 _public prototype_ `virtual EGizmoTransformMode GetGizmoMode() const PURE_VIRTUAL(ITransformGizmoSource::GetGizmoMode, return EGizmoTransformMode::None;);` — Returns the current Editor gizmo mode
- L103 _public prototype_ `virtual EAxisList::Type GetGizmoAxisToDraw(EGizmoTransformMode InGizmoMode) const PURE_VIRTUAL(ITransformGizmoSource::GetGizmoAxisToDraw, return EAxisList::None;);` — Returns the current gizmo axes to draw
- L108 _public prototype_ `virtual EToolContextCoordinateSystem GetGizmoCoordSystemSpace() const PURE_VIRTUAL(ITransformGizmoSource::GetGizmoCoordSystemSpace, return EToolContextCoordinateSystem::World;);` — Returns the coordinate system space (world or local) in which to display the gizmo
- L113 _public prototype_ `virtual float GetGizmoScale() const PURE_VIRTUAL(ITransformGizmoSource::GetGizmoScale, return 1.0f;);` — Returns a scale factor for the gizmo
- L118 _public prototype_ `virtual bool GetVisible(const EViewportContext InViewportContext = EViewportContext::Focused) const PURE_VIRTUAL(ITransformGizmoSource::GetVisible, return false;);` — Returns whether the gizmo should be visible.
- L123 _public prototype_ `virtual bool CanInteract(const EViewportContext InViewportContext = EViewportContext::Focused) const PURE_VIRTUAL(ITransformGizmoSource::CanInteract, return false;);` — Returns whether the gizmo can interact.
- L128 _public prototype_ `virtual EGizmoTransformScaleType GetScaleType() const PURE_VIRTUAL(ITransformGizmoSource::GetScaleType, return EGizmoTransformScaleType::Default;);` — Get current scale type
- L133 _public prototype_ `virtual const FRotationContext& GetRotationContext() const PURE_VIRTUAL(ITransformGizmoSource::GetRotationContext, static const FRotationContext Context; return Context;);` — Get rotation context

#### struct `FGizmoCustomization`  
`struct FGizmoCustomization`  
_L140-144_
- L142 _public member_ `TObjectPtr<UMaterial> Material = nullptr;`
- L143 _public member_ `float SizeCoefficient = 1.f;`

#### Free symbols / members of external scopes

- L27 _namespace_ `namespace EAxisRotateMode`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorInteractiveGizmoConditionalBuilder.h` (Public)


#### struct `FEditorGizmoTypePriority`  
`struct FEditorGizmoTypePriority`  
_L17-53_
- desc: FEditorGizmoTypePriority is used to establish relative priority between conditional gizmo builders. It is up to the gizmo manager to determine how the priority is used. In the EditorInteractiveGizmoManager, if more than one gizmo builder returns true from SatsifiesCondition(), the gizmo builder with highest priority will be used. If there are multiple builders the highest priority, multiple gizmos will be built.
- L19 _public member_ `static constexpr int DEFAULT_GIZMO_TYPE_PRIORITY = 50;`
- L22 _public member_ `int Priority;` — Constant priority value
- L24 _public function_ `FEditorGizmoTypePriority(int InPriority = DEFAULT_GIZMO_TYPE_PRIORITY)`
- L30 _public function_ `FEditorGizmoTypePriority MakeLower(int DeltaAmount = 1) const` — @return a priority lower than this priority
- L36 _public function_ `FEditorGizmoTypePriority MakeHigher(int DeltaAmount = 1) const` — @return a priority higher than this priority

#### class `UEditorInteractiveGizmoConditionalBuilder`  
`class UEditorInteractiveGizmoConditionalBuilder : public UInterface`  
_L63-66_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`
- desc: Gizmo builders which should be built once a condition is satisfied in the current scene state implement the IEditorInteractiveGizmoConditionalBuilder interface. The SatisfiesCondition method should return true whenever the builder is buildable based on scene state, most commonly based on selection. The builder's priority should be specified such that when more than one builder is discovered, the builder with highest priority will be built.

#### class `IEditorInteractiveGizmoConditionalBuilder`  
`class IEditorInteractiveGizmoConditionalBuilder`  
_L68-83_
- L75 _public prototype_ `virtual FEditorGizmoTypePriority GetPriority() const = 0;` — Returns the priority for this gizmo type.
- L78 _public prototype_ `virtual void SetPriority(const FEditorGizmoTypePriority& InPriority) = 0;` — Update the priority for this gizmo type.
- L81 _public prototype_ `virtual bool SatisfiesCondition(const FToolBuilderState& SceneState) const = 0;` — Returns true if this gizmo is valid for creation based on the current state.

#### Free symbols / members of external scopes

- L41 _function_ `friend bool operator<(const FEditorGizmoTypePriority& l, const FEditorGizmoTypePriority& r)`
- L45 _function_ `friend bool operator==(const FEditorGizmoTypePriority& l, const FEditorGizmoTypePriority& r)`
- L49 _function_ `friend bool operator>(const FEditorGizmoTypePriority& l, const FEditorGizmoTypePriority& r)`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorInteractiveGizmoManager.h` (Public)


#### struct `FActiveEditorGizmo`  
`struct FActiveEditorGizmo`  
_L34-41_
- reflection: `USTRUCT()`
- L39 _public member_ `TObjectPtr<UInteractiveGizmo> Gizmo = nullptr;` — `UPROPERTY()`
- L40 _public member_ `void* Owner = nullptr;`

#### class `UEditorInteractiveGizmoManager`  
`class UEditorInteractiveGizmoManager : public UInteractiveGizmoManager`  
_L50-253_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UInteractiveGizmoManager`
- desc: UEditorInteractiveGizmoManager allows users of the Tools framework to register and create selection-based Gizmo instances. For each selection-based Gizmo, a builder derived from UInteractiveGizmoSelectionBuilder is registered with the GizmoManager. When the section changes, the highest priority builders for which SatisfiesCondition() return true, will be used to build gizmos.
- L57 _protected prototype_ `UEditorInteractiveGizmoManager();`
- L60 _protected prototype_ `virtual void InitializeWithEditorModeManager(IToolsContextQueriesAPI* QueriesAPI, IToolsContextTransactionsAPI* TransactionsAPI, UInputRouter* InputRouter, FEditorModeTools* InEditorModeManager);` — Initialize the GizmoManager with the necessary Context-level state. UEdModeInteractiveToolsContext calls this, you should not.
- L63 _protected prototype_ `virtual void Shutdown() override;` — UInteractiveGizmoManager interface
- L68 _public prototype_ `virtual void Tick(float DeltaTime) override;` — UInteractiveGizmoManager interface
- L69 _public prototype_ `virtual void Render(IToolsContextRenderAPI* RenderAPI) override;`
- L70 _public prototype_ `virtual void DrawHUD(FCanvas* Canvas, IToolsContextRenderAPI* RenderAPI) override;`
- L79 _public prototype_ `void RegisterEditorGizmoType(EEditorGizmoCategory InGizmoCategory, UInteractiveGizmoBuilder* InGizmoBuilder);` — Register a new Editor gizmo type. @param InGizmoCategory category in which to register gizmo builder @param InGizmonBuilder new Editor gizmo builder - Accessory and Primary gizmo builders must derive from UInteractiveGizmoBuilder (of from a builder derived from it) and must implement the IEditorInteractiveConditionalGizmoBuilder and IEditorInteractiveSelectionGizmoBuilder interfaces.
- L86 _public prototype_ `void DeregisterEditorGizmoType(EEditorGizmoCategory InGizmoCategory, UInteractiveGizmoBuilder* InGizmoBuilder);` — Remove an Editor gizmo type from the set of known Editor gizmo types @param InGizmoBuilder same object pointer that was passed to RegisterEditorGizmoType() @return true if gizmo type was found and deregistered
- L96 _public prototype_ `void GetQualifiedEditorGizmoBuilders(EEditorGizmoCategory InGizmoCategory, const FToolBuilderState& InToolBuilderState, TArray<UInteractiveGizmoBuilder*>& InFoundBuilders);` — Get all qualified Editor gizmo builders for the specified category, based on the current state. Qualification is determined by the gizmo builder returning true from SatisfiesCondition() and relative priority. All qualified builders at the highest found priority will be returned. @param InGizmoCategory category in which to search for qualified builders @param InToolBuilderState current selection and other state @return array of qualified Gizmo selection builders based on current state
- L103 _public function_ `virtual void SetEditorGizmoBuilderResolution(bool bLocalOnly)` — Set how auto gizmo resolution should occur when CreateGizmosForCurrentState is invoked. If bSearchLocalOnly is true, only the current @param bLocalOnly - if true, only the current gizmo manager registry will be searched for candidate gizmos. If false, both the gizmo manager registry and any higher gizmo manager or gizmo subsystem (in the case of selection builders) will be searched
- L111 _public function_ `virtual bool GetEditorGizmoBuilderResolution() const` — Returns the current auto gizmo resolution setting
- L119 _public prototype_ `bool AreEditorGizmosAllowed() const;` — Gets whether editor gizmos are allowed
- L124 _public prototype_ `void SetAllowEditorGizmos(bool bInAllowed);` — Sets whether editor gizmos are allowed
- L131 _public prototype_ `virtual bool DestroyEditorGizmo(UInteractiveGizmo* Gizmo);` — Shutdown and remove a selection-based Gizmo @param Gizmo the Gizmo to shutdown and remove @return true if the Gizmo was found and removed
- L136 _public prototype_ `virtual void DestroyAllEditorGizmos();` — Shutdown and remove all active auto gizmos
- L139 _public prototype_ `virtual UInteractiveGizmo* CreateGizmo( const FString& BuilderIdentifier, const FString& InstanceIdentifier = FString(), void* Owner = nullptr) override;` — Try to activate a new Gizmo instance (UInteractiveGizmoManager override)
- L143 _public prototype_ `virtual bool DestroyGizmo(UInteractiveGizmo* InGizmo) override;` — Shutdown and remove a Gizmo (UInteractiveGizmoManager override)
- L146 _public prototype_ `static const FString& TransformInstanceIdentifier();` — instance/builder identifiers for transform gizmo
- L147 _public prototype_ `static const FString& TransformBuilderIdentifier();`
- L152 _public prototype_ `static bool AreEditorGizmosAllowed(const FEditorModeTools* ModeTools);` — Returns true if editor gizmos are enabled for the provided ModeTools instance.
- L157 _public prototype_ `static bool UsesNewTRSGizmos();` — Returns true if the new TRS gizmos are used.
- L162 _public prototype_ `static void SetUsesNewTRSGizmos(const bool bUseNewTRSGizmos);` — Updates the current New TRS Gizmo state and notifies that change using OnUsesNewTRSGizmosChangedDelegate
- L168 _public prototype_ `static int32 GetTransformGizmoVersion();` — Returns the current gizmo version. 0 = legacy, 1 = TransformGizmo, 2 = EditorTRSGizmo. Reads from existing settings (bUseExperimentalGizmo, bUseEditorTRSGizmo).
- L174 _public prototype_ `static void SetTransformGizmoVersion(const int32 InVersion);` — Sets the gizmo version by writing to the existing settings. Writes to existing settings (bUseExperimentalGizmo, bUseEditorTRSGizmo).
- L179 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUsesNewTRSGizmosChanged, const bool bUseNewTRSGizmos);` — Delegate to notify from bUseNewTRSGizmos changes
- L180 _public prototype_ `static FOnUsesNewTRSGizmosChanged& OnUsesNewTRSGizmosChangedDelegate();`
- L185 _public prototype_ `static void SetGizmosParameters(const FGizmosParameters& InParameters);` — Notifies FGizmosParameters changes across bound transform gizmos
- L190 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmosParametersChanged, const FGizmosParameters& InParameters);` — Delegate to notify from FGizmosParameters changes
- L191 _public prototype_ `static FOnGizmosParametersChanged& OnGizmosParametersChangedDelegate();`
- L196 _public prototype_ `static const TOptional<FGizmosParameters>& GetDefaultGizmosParameters();` — Returns the default gizmos parameters if set
- L201 _public prototype_ `static bool IsExplicitModeEnabled();` — Returns true if the Explicit mode is enabled;
- L209 _protected prototype_ `virtual bool GetShowEditorGizmos();` — Returns true if selection gizmos should be visible. @todo move this to a gizmo context object
- L215 _protected prototype_ `virtual bool GetShowEditorGizmosForView(IToolsContextRenderAPI* RenderAPI);` — Returns true if gizmos should be visible based on the current view's engine show flag. @todo move this to a gizmo context object
- L220 _protected prototype_ `void UpdateActiveEditorGizmos();` — Updates active selection gizmos when show selection state changes
- L224 _protected member_ `TObjectPtr<UEditorInteractiveGizmoRegistry> Registry;` — `UPROPERTY()` — Actual registry
- L228 _protected member_ `TArray<FActiveEditorGizmo> ActiveEditorGizmos;` — `UPROPERTY()` — set of Currently-active Gizmos
- L231 _protected member_ `TOptional<FGizmosParameters> DefaultGizmoParameters;` — `UPROPERTY()`
- L234 _protected member_ `bool bSearchLocalBuildersOnly = false;` — If false, only search gizmo builders in current gizmo manager. If true, also search gizmo subsystem
- L238 _protected member_ `TMap<TObjectPtr<UInteractiveGizmoBuilder>, TObjectPtr<UInteractiveGizmo>> CachedGizmoMap;` — `UPROPERTY()` — Cache for already built gizmos, currently this only caches the transform
- L241 _protected member_ `FEditorModeTools* EditorModeManager = nullptr;` — @todo: remove when GetShowEditorGizmos() is moved to gizmo context object
- L244 _protected member_ `bool bAllowEditorGizmos = true;` — Whether Editor gizmos are ever allowed in this context. Layered on top of UsesNewTRSGizmos()
- L247 _protected member_ `bool bShowEditorGizmos = false;` — Whether Editor gizmos are enabled. UpdateActiveEditorGizmos() determines this value each tick and updates if it has changed.
- L252 _private prototype_ `UTransformGizmo* FindDefaultTransformGizmo() const;` — Returns the existing default Gizmo instance if any.

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L179 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnUsesNewTRSGizmosChanged, const bool bUseNewTRSGizmos);` — Delegate to notify from bUseNewTRSGizmos changes
- L190 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGizmosParametersChanged, const FGizmosParameters& InParameters);` — Delegate to notify from FGizmosParameters changes

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorInteractiveGizmoRegistry.h` (Public)


#### enum `EEditorGizmoCategory`  
`enum class EEditorGizmoCategory :uint8`  
_L28-35_
- reflection: `UENUM()`
- desc: Gizmo category used for registering Editor gizmo selection-based builders
- L31 _public enumerator_ `Accessory` — Accessory gizmos, built simultaneously with the Level Editor TRS gizmo.
- L34 _public enumerator_ `Primary` — Primary gizmos, built in place of the Level Editor TRS gizmo.

#### class `UEditorGizmoRegistryCategoryEntry`  
`class UEditorGizmoRegistryCategoryEntry : public UObject`  
_L38-63_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- L48 _public prototype_ `virtual void GetQualifiedGizmoBuilders(const FToolBuilderState& InToolBuilderState, TArray<UInteractiveGizmoBuilder*>& InFoundBuilders) PURE_VIRTUAL(UEditorGizmoRegistryCategoryEntry::GetQualifiedGizmoBuilders, );` — Gets qualified gizmo builders, replacing those already found if necessary. @param FoundBuilders inputs qualified builders found so far, and outputs qualified builders for this category replacing
- L50 _public prototype_ `virtual void RegisterGizmoType(UInteractiveGizmoBuilder* InGizmoBuilder);`
- L52 _public prototype_ `virtual void DeregisterGizmoType(UInteractiveGizmoBuilder* InGizmoBuilder);`
- L54 _public prototype_ `virtual void ClearGizmoTypes();`
- L57 _public member_ `TArray<TObjectPtr<UInteractiveGizmoBuilder>> GizmoTypes;` — `UPROPERTY()`
- L62 _protected member_ `FString CategoryName;` — `UPROPERTY()`

#### class `UEditorGizmoRegistryCategoryEntry_ConditionalSelection`  
`class UEditorGizmoRegistryCategoryEntry_ConditionalSelection : public UEditorGizmoRegistryCategoryEntry`  
_L66-74_
- reflection: `UCLASS(Abstract)`
- inherits: `UEditorGizmoRegistryCategoryEntry`
- L71 _public prototype_ `virtual void GetQualifiedGizmoBuilders(const FToolBuilderState& InToolBuilderState, TArray<UInteractiveGizmoBuilder*>& InFoundBuilders) PURE_VIRTUAL(UEditorGizmoRegistryCategoryEntry::GetQualifiedGizmoBuilders, );`
- L73 _public prototype_ `virtual void RegisterGizmoType(UInteractiveGizmoBuilder* InGizmoBuilder);`

#### class `UEditorGizmoRegistryCategoryEntry_Primary`  
`class UEditorGizmoRegistryCategoryEntry_Primary : public UEditorGizmoRegistryCategoryEntry_ConditionalSelection`  
_L78-85_
- reflection: `UCLASS()`
- inherits: `UEditorGizmoRegistryCategoryEntry_ConditionalSelection`
- L82 _public prototype_ `UEditorGizmoRegistryCategoryEntry_Primary();`
- L84 _public prototype_ `virtual void GetQualifiedGizmoBuilders(const FToolBuilderState& InToolBuilderState, TArray<UInteractiveGizmoBuilder*>& FoundBuilders);`

#### class `UEditorGizmoRegistryCategoryEntry_Accessory`  
`class UEditorGizmoRegistryCategoryEntry_Accessory : public UEditorGizmoRegistryCategoryEntry_ConditionalSelection`  
_L88-95_
- reflection: `UCLASS()`
- inherits: `UEditorGizmoRegistryCategoryEntry_ConditionalSelection`
- L92 _public prototype_ `UEditorGizmoRegistryCategoryEntry_Accessory();`
- L94 _public prototype_ `virtual void GetQualifiedGizmoBuilders(const FToolBuilderState& InToolBuilderState, TArray<UInteractiveGizmoBuilder*>& FoundBuilders);`

#### class `UEditorInteractiveGizmoRegistry`  
`class UEditorInteractiveGizmoRegistry : public UObject`  
_L105-154_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: Gizmo types should be registered in either UEditorInteractiveGizmoSubsystem or UEditorInteractiveGizmoManager. This registry class is used internally by the subsystem and manager which each maintain its own registry at different scopes: the subystem is global to the Editor, the manager is local to the Interactive Tools Context.
- L111 _public prototype_ `UEditorInteractiveGizmoRegistry();`
- L114 _public prototype_ `virtual void Shutdown();` — Shutdown the registry, called by the gizmo subsystem and gizmo manager when they are shutdown/deinitialized.
- L123 _public prototype_ `void RegisterEditorGizmoType(EEditorGizmoCategory InGizmoCategory, UInteractiveGizmoBuilder* InGizmoBuilder);` — Register a new Editor gizmo type. @param InGizmoCategory category in which to register gizmo builder @param InGizmoBuilder new Editor gizmo builder - Accessory and Primary gizmo builders must derive from UInteractiveGizmoBuilder (of from a builder derived from it) and must implement the IEditorInteractiveConditionalGizmoBuilder and IEditorInteractiveSelectionGizmoBuilder interfaces.
- L130 _public prototype_ `void DeregisterEditorGizmoType(EEditorGizmoCategory InGizmoCategory, UInteractiveGizmoBuilder* InGizmoBuilder);` — Remove an Editor gizmo type from the set of known Editor gizmo types @param InGizmoBuilder same object pointer that was passed to RegisterEditorGizmoType() @return true if gizmo type was found and deregistered
- L135 _public prototype_ `void ClearEditorGizmoTypes();` — Clear all registered gizmo types
- L147 _public prototype_ `void GetQualifiedEditorGizmoBuilders(EEditorGizmoCategory InGizmoCategory, const FToolBuilderState& InToolBuilderState, TArray<UInteractiveGizmoBuilder*>& FoundBuilders);` — Get all qualified Editor gizmo builders for the specified category, based on the current state. Qualification is determined by the gizmo builder returning true from SatisfiesCondition() and relative priority. All qualified builders at the highest found priority will be returned. @param InGizmoCategory category in which to search for qualified builders @param InToolBuilderState current selection and other state @param FoundBuilders input and output parameter, inputs currently qualified builders, outputs resulting qualified builders which may add to or replace the input found builders. @return array of qualified Gizmo selection builders based on current state
- L153 _private member_ `TMap<EEditorGizmoCategory, TObjectPtr<UEditorGizmoRegistryCategoryEntry>> GizmoCategoryMap;` — `UPROPERTY()` — Current set of Gizmo Builders

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorInteractiveGizmoSelectionBuilder.h` (Public)


#### class `FEditorGizmoSelectionBuilderHelper`  
`class FEditorGizmoSelectionBuilderHelper`  
_L21-28_
- L27 _public prototype_ `static UTransformProxy* CreateTransformProxyForSelection(const FToolBuilderState& SceneState);` — Utility method that creates a transform proxy based on the current selection.

#### class `UEditorInteractiveGizmoSelectionBuilder`  
`class UEditorInteractiveGizmoSelectionBuilder : public UInterface`  
_L31-34_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IEditorInteractiveGizmoSelectionBuilder`  
`class IEditorInteractiveGizmoSelectionBuilder`  
_L36-50_
- L48 _public prototype_ `virtual void UpdateGizmoForSelection(UInteractiveGizmo* Gizmo, const FToolBuilderState& SceneState) = 0;` — Update gizmo's active target based on the current Editor selection and scene state.  This method creates a transform proxy for the current selection and sets the gizmo's active target to the new transform proxy. This method is called after a gizmo is automatically built based upon selection and also to update the existing gizmo when the selection changes.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorInteractiveGizmoSubsystem.h` (Public)


#### class `UEditorInteractiveGizmoSubsystem`  
`class UEditorInteractiveGizmoSubsystem : public UEditorSubsystem`  
_L44-135_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEditorSubsystem`
- desc: The InteractiveGizmoSubsystem provides methods for registering and unregistering selection-based gizmo builders. This subsystem will be queried for qualified builders based on the current selection. This subsystem should be used to register gizmo selection-based builders which are not specific to an ed mode or asset editor. For gizmo selection-based builders which are specific to an ed mode or asset editor, register with the UEditorinteractiveGizmoManager instead, when the ed mode or asset editor starts up (and deregister when the mode or asset editor shuts down). Plugins registering gizmo types should bind to the delegates returned by: - OnEditorGizmoSubsystemRegisterEditorGizmoTypes() - OnEditorGizmoSubsystemDeregisterEditorGizmoTypes() to register and dergister their gizmo builders.
- L50 _public prototype_ `UEditorInteractiveGizmoSubsystem();`
- L53 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L55 _public prototype_ `virtual void Deinitialize() override;`
- L61 _public prototype_ `DECLARE_EVENT(UEditorInteractiveSelectionGizmoSubsystem, FOnEditorGizmoSubsystemRegisterGlobalEditorGizmoTypes);` — Event which is broadcast just after default types are registered in the gizmo subsystem
- L62 _public function_ `FOnEditorGizmoSubsystemRegisterGlobalEditorGizmoTypes& OnEditorGizmoSubsystemRegisterGlobalEditorGizmoTypes()`
- L67 _public prototype_ `DECLARE_EVENT(UEditorInteractiveSelectionGizmoSubsystem, FOnEditorGizmoSubsystemDeregisterGlobalEditorGizmoTypes);` — Event which is broadcast just before default types are deregistered in the gizmo subsystem
- L68 _public function_ `FOnEditorGizmoSubsystemDeregisterGlobalEditorGizmoTypes& OnEditorGizmoSubsystemDeregisterGlobalEditorGizmoTypes()`
- L73 _public prototype_ `void RegisterBuiltinEditorGizmoTypes();` — Registers all built-in Editor gizmo types and broadcast registration event.
- L78 _public prototype_ `void DeregisterBuiltinEditorGizmoTypes();` — Removes all built-in Editor gizmo types and broadcast deregistration event.
- L87 _public prototype_ `void RegisterGlobalEditorGizmoType(EEditorGizmoCategory InGizmoCategory, UInteractiveGizmoBuilder* InGizmoBuilder);` — Register a new Editor gizmo type which will be global to the Editor. @param InGizmoCategory category in which to register gizmo builder @param InGizmonBuilder new Editor gizmo builder - Accessory and Primary gizmo builders must derive from UInteractiveGizmoBuilder (of from a builder derived from it) and must implement the IEditorInteractiveConditionalGizmoBuilder and IEditorInteractiveSelectionGizmoBuilder interfaces.
- L94 _public prototype_ `void DeregisterGlobalEditorGizmoType(EEditorGizmoCategory InGizmoCategory, UInteractiveGizmoBuilder* InGizmoBuilder);` — Remove an Editor gizmo type from the set of known Editor gizmo types @param InGizmoBuilder same object pointer that was passed to RegisterEditorGizmoType() @return true if gizmo type was found and deregistered
- L104 _public prototype_ `void GetQualifiedGlobalEditorGizmoBuilders(EEditorGizmoCategory InGizmoCategory, const FToolBuilderState& InToolBuilderState, TArray<UInteractiveGizmoBuilder*>& InFoundBuilders);` — Get all qualified Editor gizmo builders for the specified category, based on the current state. Qualification is determined by the gizmo builder returning true from SatisfiesCondition() and relative priority. All qualified builders at the highest found priority will be returned. @param InGizmoCategory category in which to search for qualified builders @param InToolBuilderState current selection and other state @return array of qualified Gizmo selection builders based on current state
- L109 _public prototype_ `void RegisterTransformGizmoBuilder(UInteractiveGizmoBuilder* InTransformGizmoBuilder);` — Register a transform gizmo builder used to build the Level Editor TRS gizmo, allowing the replacement of the default TRS gizmo builder.
- L114 _public function_ `UInteractiveGizmoBuilder* GetTransformGizmoBuilder()` — Get transform gizmo builder used to build the Level Editor TRS gizmo.
- L123 _private member_ `TObjectPtr<UInteractiveGizmoBuilder> TransformGizmoBuilder;` — `UPROPERTY()` — TRS gizmo builder
- L127 _private member_ `TObjectPtr<UEditorInteractiveGizmoRegistry> Registry;` — `UPROPERTY()` — Actual registry
- L130 _private member_ `FOnEditorGizmoSubsystemRegisterGlobalEditorGizmoTypes RegisterGlobalEditorGizmoTypesDelegate;` — Call to register gizmo types
- L133 _private member_ `FOnEditorGizmoSubsystemDeregisterGlobalEditorGizmoTypes DeregisterGlobalEditorGizmoTypesDelegate;` — Call to deregister gizmo types

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L61 _delegate_ `DECLARE_EVENT(UEditorInteractiveSelectionGizmoSubsystem, FOnEditorGizmoSubsystemRegisterGlobalEditorGizmoTypes);` — Event which is broadcast just after default types are registered in the gizmo subsystem
- L67 _delegate_ `DECLARE_EVENT(UEditorInteractiveSelectionGizmoSubsystem, FOnEditorGizmoSubsystemDeregisterGlobalEditorGizmoTypes);` — Event which is broadcast just before default types are deregistered in the gizmo subsystem

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorInteractiveToolsFrameworkModule.h` (Public)


#### class `FEditorInteractiveToolsFrameworkGlobals`  
`class FEditorInteractiveToolsFrameworkGlobals`  
_L14-20_
- L19 _public member_ `static int32 RegisteredStaticMeshTargetFactoryKey;` — This is the key returned by AddComponentTargetFactory() for the FStaticMeshComponentTargetFactory created/registered in StartupModule() below. Use this key to find/remove that module registration if you need to.

#### class `FEditorInteractiveToolsFrameworkModule`  
`class FEditorInteractiveToolsFrameworkModule : public IModuleInterface`  
_L22-57_
- inherits: `IModuleInterface`
- L27 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L28 _public prototype_ `virtual void ShutdownModule() override;`
- L34 _private prototype_ `static void OnUsesNewTRSGizmosChanged(bool bInUsesNewTRSGizmos);`
- L35 _private prototype_ `void OnPostEngineInit();`
- L37 _private member_ `FDelegateHandle TRSGizmoChangeDelegate;`
- L41 _private prototype_ `void RegisterConsoleCommands();`
- L42 _private prototype_ `void UnregisterConsoleCommands();`
- L43 _private prototype_ `void RegisterCustomizations();`
- L44 _private prototype_ `void UnregisterCustomizations();`
- L45 _private prototype_ `void RegisterTabs();`
- L46 _private prototype_ `void UnregisterTabs();`
- L48 _private prototype_ `void ExecuteShowSettings(const TArray<FString>& InArgs);`
- L49 _private prototype_ `void ExecuteShowGizmoTree(const TArray<FString>& InArgs);`
- L51 _private member_ `static const FLazyName GizmoSettingsTabId;`
- L52 _private member_ `static const FLazyName GizmoTreeTabId;`
- L54 _private member_ `TArray<IConsoleObject*> ConsoleCommands;`
- L55 _private member_ `TWeakPtr<SDockTab> WeakGizmoSettingsTab;`
- L56 _private member_ `TWeakPtr<SDockTab> WeakGizmoTreeTab;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/EditorTRSSettings.h` (Public)
_(no declarations extracted)_

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/GizmoEdModeInterface.h` (Public)


#### struct `FGizmoState`  
`struct FGizmoState`  
_L14-17_
- L16 _public member_ `EGizmoTransformMode TransformMode = EGizmoTransformMode::None;`

#### class `UGizmoEdModeInterface`  
`class UGizmoEdModeInterface : public UInterface`  
_L24-27_
- reflection: `UINTERFACE(NotBlueprintable, MinimalAPI)`
- inherits: `UInterface`

#### class `IGizmoEdModeInterface`  
`class IGizmoEdModeInterface`  
_L29-45_
- L36 _public prototype_ `virtual bool BeginTransform(const FGizmoState& InState) = 0;` — Called when a transform operation begins.
- L39 _public prototype_ `virtual bool EndTransform(const FGizmoState& InState) = 0;` — Called when a transform operation ends.
- L44 _public function_ `virtual bool OnTransformCanceled(const FGizmoState& InState)` — Called after a transform operation is canceled.

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/InteractiveToolStack.h` (Public)


#### struct `FInteractiveToolStack`  
`struct FInteractiveToolStack`  
_L42-103_
- reflection: `USTRUCT()`
- desc: FInteractiveToolStack represents a bundle of tools that may or may not share the same input chord Should some tools share a chord the most recently used tool will be activated by the chord. If no tools have been activated yet, the chord will go by order added to the stack. To use tool stacks, simply add a UToolStackContext to your relevant interactive tools context. This can be done by calling 'AddContextObject' to the context object store of your tool context. See: 'UWidgetEditorToolPaletteMode::Enter' as reference.
- L56 _public prototype_ `static void RegisterToolStack(UEdMode* EdMode, UEditorInteractiveToolsContext* UseToolsContext, TSharedPtr<FUICommandInfo> UICommand, FString ToolStackIdentifier);` — Helper method to generate tool stacks @param EdMode				EdMode registering this tool stack @param UseToolsContext		Tool context for this stack @param UICommand				Command to map tool start / stop actions to @param ToolStackIdentifier	Unique string identifier for the tool stack
- L68 _public prototype_ `static void AddToolToStack(UEdMode* EdMode, UEditorInteractiveToolsContext* UseToolsContext, TSharedPtr<FUICommandInfo> UICommand, FString ToolStackIdentifier, FString ToolIdentifier, UInteractiveToolBuilder* Builder);` — Helper method to add tools to stacks @param EdMode				EdMode registering tool to this tool stack @param UseToolsContext		Tool context for this stack @param UICommand				Command to map tool start / stop actions to @param ToolStackIdentifier	Unique string identifier for the tool stack @param ToolIdentifier		Unique string identifier for the tool, used to check if tool is active @param Builder				Builder for tool to be used by actions
- L73 _public prototype_ `int32 AddTool(const FString& InToolName, const TSharedPtr<FUICommandInfo>& InUICommand);` — Add the tool to our internal tool array
- L76 _public prototype_ `void NotifyToolActivated(const FString& InToolName);` — Signal that a tool was activated increasing its priority in the toolstack for future chord inputs
- L79 _public prototype_ `const FString GetLastActiveToolByChord(const FInputChord& InInputChord) const;` — Get Tool that should be activated for the given input chord
- L82 _public prototype_ `const FString GetLastActiveTool() const;` — Get most recently activated tool within this stack
- L85 _public prototype_ `const FSlateIcon& GetLastActiveToolIcon() const;` — Get most recently activated tool's icon within this stack
- L88 _public prototype_ `const FText& GetLastActiveToolLabel() const;` — Get most recently activated tool's label within this stack
- L91 _public prototype_ `const FText& GetLastActiveToolDescription() const;` — Get most recently activated tool's description within this stack
- L94 _public prototype_ `const TArray<TPair<FString, TSharedPtr<FUICommandInfo>>>& GetStack() const;` — Get the original tool stack
- L99 _protected member_ `TArray<TPair<FString, TSharedPtr<FUICommandInfo>>> SortedToolStack;` — Tools contained within this stack along with their input chord, sorted by most recently used
- L102 _protected member_ `TArray<TPair<FString, TSharedPtr<FUICommandInfo>>> OriginalStack;` — Original stack ordering

#### Free symbols / members of external scopes

- L23 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/Snapping/EditorSnappingManager.h` (Public)


#### class `UEditorSceneSnappingManager`  
`class UEditorSceneSnappingManager : public USceneSnappingManager`  
_L37-69_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `USceneSnappingManager`
- L42 _public prototype_ `UEditorSceneSnappingManager();`
- L44 _public prototype_ `void Initialize(const TObjectPtr<UInteractiveToolsContext>& InToolsContext);`
- L45 _public prototype_ `void Shutdown();`
- L47 _public prototype_ `virtual bool ExecuteSceneHitQuery(const FSceneHitQueryRequest& InRequest, FSceneHitQueryResult& OutResult) const override;`
- L48 _public prototype_ `virtual bool ExecuteSceneHitQuery(const FSceneHitQueryRequest& InRequest, TArray<FSceneHitQueryResult>& OutResults) const override;`
- L49 _public prototype_ `virtual bool ExecuteSceneSnapQuery(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const override;`
- L52 _public prototype_ `void RegisterSnapQueryTargetHandler(TUniquePtr<FSceneSnapQueryTargetHandler>&& InHandler);` — Register a snapping handler for a given snap target.
- L53 _public prototype_ `void DeregisterSnapQueryTargetHandler(const FName InHandlerName);`
- L56 _protected prototype_ `bool ExecuteSceneHitQueryPrimitiveTransform(const FSceneHitQueryRequest& InRequest, TArray<FSceneHitQueryResult>& OutResults) const;`
- L58 _protected prototype_ `bool ExecuteSceneSnapQueryPosition(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const;`
- L59 _protected prototype_ `bool ExecuteSceneSnapQueryRotation(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const;`
- L60 _protected prototype_ `bool ExecuteSceneSnapQueryRotationAngle(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const;`
- L61 _protected prototype_ `bool ExecuteSceneSnapQueryScale(const FSceneSnapQueryRequest& InRequest, TArray<FSceneSnapQueryResult>& OutResults) const;`
- L64 _protected member_ `TArray<TUniquePtr<FSceneSnapQueryTargetHandler>> QueryTargetHandlers;`
- L66 _protected member_ `const IToolsContextQueriesAPI* QueriesAPI = nullptr;`
- L68 _protected member_ `TUniquePtr<UE::Editor::Gizmos::Private::FEditorSceneSnappingManagerDebug> Debug;`

#### Free symbols / members of external scopes

- L22 _namespace_ `namespace UE`
- L22 _namespace_ `namespace Editor` (scope `UE`)
- L22 _namespace_ `namespace Gizmos` (scope `UE::Editor`)
- L24 _prototype_ `bool RegisterSceneSnappingManager(UInteractiveToolsContext* InToolsContext);` (scope `UE::Editor::Gizmos`)
- L26 _prototype_ `bool DeregisterSceneSnappingManager(const UInteractiveToolsContext* InToolsContext);` (scope `UE::Editor::Gizmos`)
- L28 _prototype_ `UEditorSceneSnappingManager* FindSceneSnappingManager(const UInteractiveToolManager* InToolManager);` (scope `UE::Editor::Gizmos`)
- L30 _namespace_ `namespace Private` (scope `UE::Editor::Gizmos`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ToolContexts/ToolStackContext.h` (Public)


#### class `UToolStackContext`  
`class UToolStackContext : public UObject`  
_L30-90_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UObject`
- desc: Context needed to support tool stacks, add this to your ContextObjectStore if you want to use tool stacks
- L34 _private prototype_ `virtual ~UToolStackContext();`
- L45 _public prototype_ `virtual void RegisterToolStack(TSharedPtr<FUICommandInfo> UICommand, const FString& ToolStackIdentifier, EToolsContextScope ToolScope = EToolsContextScope::Default);` — Registers and maps the provided UI command to actions that start / stop multiple tools within a tool stack Later on this UI command can be referenced to add the tool stack to a toolbar. @param	UICommand			Command to map tool stack to, should not have any chords due to child tools having hotkeys @param	ToolStackIdentifier	Unique string identifier for the tool stack @param	ToolScope			Scope to determine appropriate tool context for stack
- L56 _public prototype_ `virtual void AddToolToStack(TSharedPtr<FUICommandInfo> UICommand, const FString& ToolStackIdentifier, const FString& ToolIdentifier, UInteractiveToolBuilder* Builder, EToolsContextScope ToolScope = EToolsContextScope::Default);` — Registers and maps the provided UI command to actions that control a tool within a tool stack @param	UICommand			Command containing info such as icon, text, & chord for the tool @param	ToolStackIdentifier	Unique string identifier for the tool stack to add this tool to @param	ToolIdentifier		Unique string identifier for the tool, used to check if tool is active @param	Builder				Builder for tool to be used by actions @param	ToolScope			Scope to determine lifetime of tool (Editor, Mode, etc)
- L63 _public prototype_ `virtual void UnregisterToolStack(const FString& Identifier);` — Unregister a Tool stack, unregistration of individual tools is handled seperately Note: Currently this is never called since we properly free resources on destruction @param Identifier string used to identify this stack
- L70 _public prototype_ `virtual FInteractiveToolStack* AccessToolStack(const FString& Identifier);` — Access an existing tool stack @param	Identifier string used to identify this stack @return	Ptr to stack if it exists, nullptr otherwise
- L75 _public member_ `TWeakObjectPtr<UEdMode> EdMode;` — `UPROPERTY()` — EdMode owning the tools referenced by this stack
- L78 _public member_ `EToolsContextScope ToolContextScope;` — Scope for this context object
- L83 _protected member_ `TMap<FString, FInteractiveToolStack> ToolStacks;` — `UPROPERTY()` — Current set of named ToolStacks
- L86 _protected member_ `TArray<TPair<TSharedPtr<FUICommandInfo>, FString>> RegisteredEditorTools;` — List of Tools this Mode has registered in the EditorToolsContext, to be unregistered on Mode shutdown
- L89 _protected member_ `TArray<TPair<TSharedPtr<FUICommandInfo>, FString>> RegisteredEditorToolStacks;` — List of Tools stacks this Mode has registered in the EditorToolsContext, to be unregistered on Mode shutdown

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ToolContexts/WidgetToolsContext.h` (Public)


#### class `UWidgetToolsContext`  
`class UWidgetToolsContext : public UModeManagerInteractiveToolsContext`  
_L33-52_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UModeManagerInteractiveToolsContext`
- desc: UWidgetToolsContext extends UModeManagerInteractiveToolsContext with methods needed for tools operating on general widgets that do not have a viewport.
- L40 _public prototype_ `bool OnKeyChar(const FGeometry& MyGeometry, const FCharacterEvent& InCharacterEvent);`
- L41 _public prototype_ `bool OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L42 _public prototype_ `bool OnKeyUp(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent);`
- L43 _public prototype_ `bool OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L44 _public prototype_ `bool OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L45 _public prototype_ `bool OnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L46 _public prototype_ `bool OnMouseWheel(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L47 _public prototype_ `bool OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent);`
- L48 _public prototype_ `bool OnDragDetected(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent);`
- L49 _public prototype_ `void OnMouseCaptureLost(const FCaptureLostEvent& CaptureLostEvent);`
- L50 _public prototype_ `int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/TransformGizmoEditorSettings.h` (Public)


#### class `UTransformGizmoEditorSettings`  
`class UTransformGizmoEditorSettings : public UDeveloperSettings`  
_L14-100_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Config = EditorPerProjectUserSettings, meta = (DisplayName = "Gizmos"))`
- inherits: `UDeveloperSettings`
- L19 _public prototype_ `UTransformGizmoEditorSettings(const FObjectInitializer& ObjectInitializer);`
- L22 _public prototype_ `virtual void PostInitProperties() override;`
- L23 _public prototype_ `virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& InPropertyChangedEvent) override;`
- L24 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L25 _public prototype_ `virtual void PostReloadConfig(class FProperty* PropertyThatWasLoaded) override;`
- L29 _public member_ `float TransformGizmoSize = 0.0f;` — `UPROPERTY(Config, EditAnywhere, Category = "Transform Gizmo", DisplayName = "Transform Gizmo Size", meta = (ClampMin = "-10.0", ClampMax = "150.0"))`
- L36 _public member_ `bool bEnableArcballRotate;` — `UPROPERTY(EditAnywhere, Category = "Transform Gizmo", DisplayName = "Enable Arcball Rotate")` — Allow arcball rotation with rotate widget (updates the setting with the same name found in Level Editor Viewport Settings)
- L43 _public member_ `bool bEnableScreenRotate;` — `UPROPERTY(EditAnywhere, Category = "Transform Gizmo", DisplayName = "Enable Screen Rotate")` — Allow screen rotation with rotate widget (updates the setting with the same name found in Level Editor Viewport Settings)
- L50 _public member_ `bool bEnableAxisDrawing;` — `UPROPERTY(EditAnywhere, Category = "Transform Gizmo", DisplayName = "Enable Axis drawing for Transform Edit Widget")` — If true, the Edit widget of a transform will display the axis (updates the setting with the same name found in Level Editor Viewport Settings)
- L57 _public member_ `bool bEnableCombinedTranslateRotate;` — `UPROPERTY(EditAnywhere, Category = "Transform Gizmo", DisplayName = "Enable Combined Translate/Rotate Widget")` — Allow translate/rotate widget (updates the setting with the same name found in Level Editor Viewport Settings)
- L63 _public member_ `bool bUseExperimentalGizmo = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Experimental", Getter = "UsesExperimentalGizmo", Setter = "SetUseExperimentalGizmo")` — If true, the new TRS gizmos will be used. UI controls set both flags together; the intermediate state is CVar-only.
- L66 _public member_ `bool bUseEditorTRSGizmo = true;` — `UPROPERTY(Config, EditAnywhere, Category = "Experimental", Getter = "UsesNewTRSGizmo", Setter = "SetUseNewTRSGizmo")`
- L69 _public member_ `FGizmosParameters GizmosParameters;` — `UPROPERTY(Config, EditAnywhere, Category = "Experimental", meta = (ShowOnlyInnerProperties))`
- L72 _public prototype_ `void SetUseExperimentalGizmo(bool bInUseExperimentalGizmo);`
- L73 _public prototype_ `void SetUseNewTRSGizmo(bool bInUseNewTRSGizmo);`
- L75 _public prototype_ `bool UsesLegacyGizmo() const;`
- L76 _public prototype_ `bool UsesExperimentalGizmo() const;`
- L77 _public prototype_ `bool UsesNewTRSGizmo() const;`
- L79 _public prototype_ `void SetGizmosParameters(const FGizmosParameters& InGizmosParameters);`
- L86 _public prototype_ `void SetTransformGizmoAxisMultiplier(float InAxisMultiplier, bool bInteractive = false);` — Updates gizmo axis size multiplier. bInteractive set to true means the new value will not be saved to current configuration. Useful to get good performance while the value is being interactively changed, e.g. through a UI slider.
- L87 _public prototype_ `float GetTransformGizmoAxisMultiplier() const;`
- L90 _public prototype_ `void SetTransformGizmoSize(float InTransformGizmoSize);` — Use this for legacy gizmos
- L93 _private prototype_ `void BroadcastNewTRSGizmoChange() const;`
- L94 _private prototype_ `void BroadcastGizmosParametersChange() const;`
- L97 _private prototype_ `void SyncFromLevelEditorSettings();` — Writes to Gizmos settings from the current LevelEditorSettings.
- L99 _private prototype_ `void OnLegacySettingChanged(FName InPropertyName);`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportCameraRotateInteraction.h` (Public)


#### class `UViewportCameraRotateInteraction`  
`class UViewportCameraRotateInteraction final : public UViewportInteraction , public IKeyInputBehaviorTarget`  
_L19-51_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportInteraction,IKeyInputBehaviorTarget`
- desc: A viewport interaction to Rotate the camera using keyboard inputs. Only works while the camera is being controlled using the mouse
- L26 _public prototype_ `UViewportCameraRotateInteraction();`
- L29 _public prototype_ `virtual void OnKeyPressed(const FKey& InKeyID) override;`
- L30 _public prototype_ `virtual void OnKeyReleased(const FKey& InKeyID) override;`
- L34 _public prototype_ `virtual void Tick(float InDeltaTime) const override;`
- L39 _protected prototype_ `virtual void OnCommandChordChanged() override;`
- L40 _protected prototype_ `virtual TArray<TSharedPtr<FUICommandInfo>> GetCommands() const override;`
- L43 _protected prototype_ `void UpdateKeyState(const FKey& InKeyID, bool bInIsPressed);`
- L44 _protected prototype_ `TArray<FKey> GetKeys() const;`
- L47 _private member_ `TWeakObjectPtr<UKeyInputBehavior> KeyInputBehaviorWeak;`
- L49 _private member_ `float RotatePitchImpulse = 0.0f;`
- L50 _private member_ `float RotateYawImpulse = 0.0f;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportCameraSpeedMouseWheelInteraction.h` (Public)


#### class `UViewportCameraSpeedMouseWheelInteraction`  
`class UViewportCameraSpeedMouseWheelInteraction : public UViewportInteraction , public IMouseWheelBehaviorTarget`  
_L15-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportInteraction,IMouseWheelBehaviorTarget`
- L22 _public prototype_ `UViewportCameraSpeedMouseWheelInteraction();`
- L25 _public prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& CurrentPos) override;`
- L26 _public prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& CurrentPos) override;`
- L27 _public prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& CurrentPos) override;`
- L34 _public prototype_ `void UpdateCameraSpeed(float InUpdateFactor) const;` — Increments the current camera speed using the specified change factor, e.g. Speed += Speed * UpdateFactor @param InUpdateFactor positive or negative factor

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportCameraTranslateInteraction.h` (Public)


#### class `UViewportCameraTranslateInteraction`  
`class UViewportCameraTranslateInteraction final : public UViewportInteraction , public IKeyInputBehaviorTarget`  
_L20-51_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportInteraction,IKeyInputBehaviorTarget`
- desc: A viewport interaction used to Translate the camera using keyboard inputs while the camera is being moved using the mouse
- L27 _public prototype_ `UViewportCameraTranslateInteraction();`
- L30 _public function_ `virtual void OnKeyPressed(const FKey& InKeyID) override`
- L31 _public function_ `virtual void OnKeyReleased(const FKey& InKeyID) override`
- L32 _public prototype_ `virtual void OnForceEndCapture() override;`
- L36 _public prototype_ `virtual void Tick(float InDeltaTime) const override;`
- L41 _protected prototype_ `virtual void OnCommandChordChanged() override;`
- L42 _protected prototype_ `virtual TArray<TSharedPtr<FUICommandInfo>> GetCommands() const override;`
- L45 _protected prototype_ `TArray<FKey> GetKeys() const;`
- L48 _private member_ `TWeakObjectPtr<UKeyInputBehavior> KeyInputBehaviorWeak;`
- L50 _private member_ `bool bUseNumpadKey = true;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportClickInteraction.h` (Public)


#### enum `UE::InteractiveTools::EViewportClickButton`  
`enum class EViewportClickButton : uint8`  
_L14-19_
- L16 _public enumerator_ `Left`
- L17 _public enumerator_ `Middle`
- L18 _public enumerator_ `Right`

#### class `UViewportClickInteraction`  
`class UViewportClickInteraction : public UViewportInteraction , public IViewportClickBehaviorTarget`  
_L29-59_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UViewportInteraction,IViewportClickBehaviorTarget`
- desc: Provides click-on-up interactions with binding-complexity-based priority compatible with FViewportClick.
- L36 _public prototype_ `virtual void Initialize(UViewportInteractionsBehaviorSource* const InViewportInteractionsBehaviorSource) override;`
- L39 _public prototype_ `virtual FInputRayHit IsHitByClick(const FInputDeviceRay& InClickPos) override;`
- L40 _public prototype_ `virtual void OnClickDown(const FInputDeviceRay& InClickPos) override;`
- L41 _public prototype_ `virtual void OnClickUp(const FInputDeviceRay& InClickPos) override;`
- L42 _public prototype_ `virtual void OnForceEndCapture() override;`
- L44 _public prototype_ `virtual void OnStateUpdated(const FInputDeviceState& InInputDeviceState) override;`
- L48 _protected prototype_ `virtual void BuildBehaviors();`
- L50 _protected prototype_ `HHitProxy* GetHitProxy(const FInputDeviceRay& InClickPos) const;`
- L53 _protected function_ `virtual void ProcessClick_Internal(const FViewportClick& InViewportClick, HHitProxy* InHitProxy, FSceneView& View)` — Override this function to provide custom functionality
- L55 _protected member_ `TWeakObjectPtr<UViewportClickBehavior> ClickBehaviorWeak;`
- L57 _protected member_ `FKey LastChangedMouseButton = FKey();`
- L58 _protected member_ `EInputEvent LastInputEvent = EInputEvent::IE_MAX;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace InteractiveTools` (scope `UE`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportCommandsInteraction.h` (Public)


#### class `UViewportCommandsInteraction`  
`class UViewportCommandsInteraction : public UViewportInteraction, public IKeyInputBehaviorTarget`  
_L19-57_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportInteraction,IKeyInputBehaviorTarget`
- desc: A viewport interaction class used to add support for a list of FUICommandInfo Commands to the current viewport
- L24 _public prototype_ `UViewportCommandsInteraction();`
- L29 _public prototype_ `void SetCommands(const TSharedPtr<FUICommandList>& InEditorCommandList, const TArray<TSharedPtr<FUICommandInfo>>& InCommands);` — Sets which commands will be handled by this Command Interaction
- L32 _public prototype_ `virtual void OnKeyPressed(const FKey& InKeyID) override;`
- L33 _public prototype_ `virtual void OnKeyReleased(const FKey& InKeyID) override;`
- L37 _public member_ `bool bExecuteOnPress = false;` — Set to true to execute commands on Press instead of Release
- L41 _protected prototype_ `virtual void OnCommandChordChanged() override;`
- L42 _protected prototype_ `virtual TArray<TSharedPtr<FUICommandInfo>> GetCommands() const override;`
- L46 _private prototype_ `TArray<FKey> GetKeys();`
- L48 _private prototype_ `void ExecuteCommand(const FKey& InKeyID);`
- L49 _private prototype_ `bool MatchesCommandKey(const TSharedPtr<FUICommandInfo>& InCommandInfo, const FKey& InKeyID) const;`
- L51 _private prototype_ `bool CanBeActivated() const;`
- L53 _private member_ `TSharedPtr<FUICommandList> EditorCommandList;`
- L54 _private member_ `TArray<TSharedPtr<FUICommandInfo>> Commands;`
- L56 _private member_ `TWeakObjectPtr<UKeyInputBehavior> KeyInputBehaviorWeak;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportDollyInteraction.h` (Public)


#### class `UViewportDollyInteraction`  
`class UViewportDollyInteraction : public UViewportDragInteraction`  
_L12-28_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportDragInteraction`
- L17 _public prototype_ `UViewportDollyInteraction();`
- L19 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L20 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L21 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`
- L22 _public prototype_ `virtual bool CanBeActivated() const override;`
- L25 _private member_ `UE::Editor::ViewportInteractions::FButtonBindings NormalBindings;`
- L26 _private member_ `UE::Editor::ViewportInteractions::FButtonBindings CameraLockedBindings;`
- L27 _private prototype_ `const UE::Editor::ViewportInteractions::FButtonBindings& GetBindings() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportDragInteraction.h` (Public)


#### class `UViewportDragInteraction`  
`class UViewportDragInteraction : public UViewportInteraction , public IViewportClickDragBehaviorTarget`  
_L22-56_
- reflection: `UCLASS(MinimalAPI, Transient, Abstract)`
- inherits: `UViewportInteraction,IViewportClickDragBehaviorTarget`
- desc: A base class which can be used to implement interactions based on mouse drag actions
- L29 _public prototype_ `UViewportDragInteraction();`
- L31 _public function_ `virtual bool IsActive() const override`
- L34 _public prototype_ `virtual FInputRayHit CanBeginClickDragSequence(const FInputDeviceRay& InPressPos) override;`
- L35 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L36 _public prototype_ `virtual void OnDrag(const FDragArgs& InDrag) override;`
- L37 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L38 _public function_ `virtual void OnStateUpdated(const FInputDeviceState& InInputDeviceState) override`
- L39 _public prototype_ `virtual void OnEndCapture(EEndCaptureReason InReason) override;`
- L42 _public function_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY)`
- L46 _public function_ `virtual bool CanBeActivated() const`
- L53 _protected member_ `TWeakObjectPtr<UViewportClickDragBehavior> ViewportClickDragBehavior;`
- L55 _protected member_ `bool bIsDragging;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportFOVInteraction.h` (Public)


#### class `UViewportFOVInteraction`  
`class UViewportFOVInteraction : public UViewportInteraction , public IKeyInputBehaviorTarget`  
_L18-57_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportInteraction,IKeyInputBehaviorTarget`
- desc: A viewport interaction used to change the camera Field of View using either keyboard inputs or the mouse wheel
- L25 _public prototype_ `UViewportFOVInteraction();`
- L26 _public prototype_ `virtual void BeginDestroy() override;`
- L29 _public prototype_ `virtual void OnKeyPressed(const FKey& InKeyID) override;`
- L30 _public prototype_ `virtual void OnKeyReleased(const FKey& InKeyID) override;`
- L31 _public prototype_ `virtual void OnForceEndCapture() override;`
- L35 _public prototype_ `virtual void Tick(float InDeltaTime) const override;`
- L36 _public prototype_ `virtual void Initialize(UViewportInteractionsBehaviorSource* const InViewportInteractionsBehaviorSource) override;`
- L41 _protected prototype_ `virtual void OnCommandChordChanged() override;`
- L42 _protected prototype_ `virtual TArray<TSharedPtr<FUICommandInfo>> GetCommands() const override;`
- L45 _protected prototype_ `void UpdateKeyState(const FKey& InKeyID, bool bInIsPressed);`
- L46 _protected prototype_ `TArray<FKey> GetKeys() const;`
- L47 _protected prototype_ `TArray<FKey> GetNumpadKeys() const;`
- L50 _private prototype_ `void OnMouseLookingChanged(bool bInIsMouseLooking);`
- L51 _private prototype_ `void ResetImpulse();`
- L53 _private member_ `bool bUseNumpadKey = true;`
- L54 _private member_ `float ZoomOutInImpulse = 0;`
- L56 _private member_ `TWeakObjectPtr<UKeyInputBehavior> KeyInputBehaviorWeak;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportInteraction.h` (Public)


#### class `UViewportInteraction`  
`class UViewportInteraction : public UObject`  
_L102-219_
- reflection: `UCLASS(MinimalAPI, Transient, Abstract)`
- inherits: `UObject`
- desc: Base class used to implement viewport interactions. Has some helper functions to check if Shift, Alt, Ctrl modifier keys and Mouse Button keys are down. Tick can be used for code which needs to affect things like camera movements in Editor Viewport Client
- L107 _public prototype_ `UViewportInteraction();`
- L109 _public prototype_ `bool IsShiftDown() const;`
- L110 _public prototype_ `bool IsAltDown() const;`
- L111 _public prototype_ `bool IsCtrlDown() const;`
- L113 _public prototype_ `bool IsLeftMouseButtonDown() const;`
- L114 _public prototype_ `bool IsMiddleMouseButtonDown() const;`
- L115 _public prototype_ `bool IsRightMouseButtonDown() const;`
- L117 _public prototype_ `bool IsAnyMouseButtonDown() const;`
- L119 _public prototype_ `bool IsMouseLooking() const;`
- L121 _public prototype_ `void SetEnabled(bool bInEnabled);`
- L122 _public prototype_ `bool IsEnabled() const;`
- L124 _public function_ `virtual bool IsActive() const`
- L127 _public function_ `virtual void Shutdown()` — Called when the interaction is removed from its behavior source. Override to make sure the interaction is properly cleaned up
- L130 _public function_ `virtual void Tick(float InDeltaTime) const` — Called every frame.
- L133 _public function_ `virtual void Render(IToolsContextRenderAPI* InRenderAPI)` — Called every frame to render tools to world space
- L136 _public function_ `virtual void Draw(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI)` — Called every frame to render tools to a 2D canvas
- L138 _public function_ `TArray<TObjectPtr<UInputBehavior>> GetInputBehaviors()`
- L143 _public prototype_ `FName GetInteractionName() const;`
- L148 _public prototype_ `const TArray<FName>& GetInteractionGroups() const;` — The Groups this interaction belongs to, if any
- L153 _public prototype_ `virtual void Initialize(UViewportInteractionsBehaviorSource* const InViewportInteractionsBehaviorSource);` — Initialization code which can be expanded by derived classes
- L155 _public prototype_ `UViewportInteractionsBehaviorSource* GetViewportInteractionsBehaviorSource() const;`
- L158 _public prototype_ `virtual void BeginDestroy() override;`
- L166 _public prototype_ `bool IsCurrentModeSupported(const FEditorModeTools* InModeTools) const;` — Checks if the provided Mode is supported by this interaction. Used to know whether this interaction should be added or not to the current Mode. Should be called on the class CDO to avoid instantiating interactions which might not be used.
- L169 _protected prototype_ `FEditorModeTools* GetModeTools() const;`
- L170 _protected prototype_ `FEditorViewportClient* GetEditorViewportClient() const;`
- L172 _protected prototype_ `void SetMouseCursorOverride(EMouseCursor::Type InMouseCursor);`
- L173 _protected prototype_ `void ClearMouseCursorOverride();`
- L178 _protected function_ `virtual void OnCommandChordChanged()` — Define what should happen to UInputBehavior(s) when an "observed" command chord changes
- L186 _protected function_ `virtual TArray<TSharedPtr<FUICommandInfo>> GetCommands() const` — Return a list of commands used by a key-based UInputBehavior. Used for its initialization, or its refresh, whenever a command chord changes
- L191 _protected prototype_ `void RegisterInputBehavior(UInputBehavior* InBehavior);`
- L192 _protected prototype_ `void RegisterInputBehaviors(TArray<UInputBehavior*> InBehaviors);`
- L194 _protected function_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const`
- L197 _protected member_ `TWeakObjectPtr<UViewportInteractionsBehaviorSource> ViewportInteractionsBehaviorSource;` — `UPROPERTY()`
- L199 _protected member_ `bool bEnabled = true;`
- L205 _protected member_ `FName InteractionName = NAME_None;` — Name for this interaction, used by Viewport Interactions Behavior Source to identify it. If NAME_None, static class name will be used.
- L210 _protected member_ `TArray<FName> Groups;` — The groups this interaction belongs to. Interactions can belong to many groups.
- L213 _private prototype_ `void OnUserDefinedChordChanged(const FUICommandInfo& InCommandInfo);`
- L216 _private member_ `TArray<TObjectPtr<UInputBehavior>> InputBehaviors;` — `UPROPERTY()`
- L218 _private member_ `FDelegateHandle OnChordChangedDelegateHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Editor` (scope `UE`)
- L21 _namespace_ `namespace ViewportInteractions` (scope `UE::Editor`)
- L23 _variable_ `constexpr int ShiftKeyMod = 1;` (scope `UE::Editor::ViewportInteractions`)
- L24 _variable_ `constexpr int AltKeyMod = 2;` (scope `UE::Editor::ViewportInteractions`)
- L25 _variable_ `constexpr int CtrlKeyMod = 3;` (scope `UE::Editor::ViewportInteractions`)
- L27 _variable_ `constexpr int LeftMouseButtonMod = 4;` (scope `UE::Editor::ViewportInteractions`)
- L28 _variable_ `constexpr int RightMouseButtonMod = 5;` (scope `UE::Editor::ViewportInteractions`)
- L29 _variable_ `constexpr int MiddleMouseButtonMod = 6;` (scope `UE::Editor::ViewportInteractions`)
- L31 _variable_ `static constexpr int VIEWPORT_INTERACTIONS_DEFAULT_PRIORITY = FInputCapturePriority::DEFAULT_TOOL_PRIORITY - 5;` (scope `UE::Editor::ViewportInteractions`)
- L52 _variable_ `static constexpr int VIEWPORT_INTERACTION_PARTIAL_STEP = static_cast<int>(FInputCapturePriority::BINDING_COMPLEXITY_PRIORITY_STEP * (1.f/3.f));` (scope `UE::Editor::ViewportInteractions`) — Binding complexity is chosen so that "tool" behaviors win out over viewport interactions on the same complexity footing. Tool priority in this diagram is assumed to have a grandfathered single point of complexity. These statements should be true: - A tool beats an unmodified click. - A modified click can beat a tool. - An unmodified drag loses to a click until it is confirmed. - A modified, unconfirmed drag can beat an unmodified click. Offsetting clicks by 1/3rd and unconfirmed drags by another 1/3rd from that allows this: |--   Tool |--  Click |--|--  Modified Click |-- Drag (unconfirmed) |--|-- Drag confirmed (or modified unconfirmed drag) |--|--|-- Modified drag confirmed
- L55 _variable_ `static constexpr int CLICK_PRIORITY = FInputCapturePriority::DEFAULT_TOOL_PRIORITY + FInputCapturePriority::BINDING_COMPLEXITY_PRIORITY_STEP + VIEWPORT_INTERACTION_PARTIAL_STEP;` (scope `UE::Editor::ViewportInteractions`)
- L56 _variable_ `static constexpr int DRAG_PRIORITY = FInputCapturePriority::DEFAULT_TOOL_PRIORITY + FInputCapturePriority::BINDING_COMPLEXITY_PRIORITY_STEP + VIEWPORT_INTERACTION_PARTIAL_STEP * 2;` (scope `UE::Editor::ViewportInteractions`)
- L57 _variable_ `static constexpr int DRAG_CONFIRMED_PRIORITY = DRAG_PRIORITY - FInputCapturePriority::BINDING_COMPLEXITY_PRIORITY_STEP;` (scope `UE::Editor::ViewportInteractions`)
- L66 _variable_ `static FName Zoom = TEXT("Zoo` (scope `UE::Editor::ViewportInteractions`) — Camera Movement
- L67 _variable_ `static FName Orbit = TEXT("Orb` (scope `UE::Editor::ViewportInteractions`)
- L68 _variable_ `static FName PerspectiveViewAngle = TEXT("Per` (scope `UE::Editor::ViewportInteractions`)
- L69 _variable_ `static FName PerspectiveDolly = TEXT("Per` (scope `UE::Editor::ViewportInteractions`)
- L70 _variable_ `static FName PerspectivePan = TEXT("Per` (scope `UE::Editor::ViewportInteractions`)
- L71 _variable_ `static FName PerspectiveMoveYaw = TEXT("Per` (scope `UE::Editor::ViewportInteractions`)
- L72 _variable_ `static FName OrthographicPan = TEXT("Ort` (scope `UE::Editor::ViewportInteractions`)
- L73 _variable_ `static FName CameraTranslate = TEXT("Cam` (scope `UE::Editor::ViewportInteractions`)
- L74 _variable_ `static FName CameraRotate = TEXT("Cam` (scope `UE::Editor::ViewportInteractions`)
- L75 _variable_ `static FName FOV = TEXT("FOV` (scope `UE::Editor::ViewportInteractions`)
- L76 _variable_ `static FName Commands = TEXT("Com` (scope `UE::Editor::ViewportInteractions`)
- L79 _variable_ `static FName BoxSelect = TEXT("Box` (scope `UE::Editor::ViewportInteractions`) — Drag Tools
- L80 _variable_ `static FName FrustumSelect = TEXT("Fru` (scope `UE::Editor::ViewportInteractions`)
- L81 _variable_ `static FName Measure = TEXT("Mea` (scope `UE::Editor::ViewportInteractions`)
- L82 _variable_ `static FName ViewportChange = TEXT("Vie` (scope `UE::Editor::ViewportInteractions`)
- L83 _variable_ `static FName DuplicateDrag = TEXT("Dup` (scope `UE::Editor::ViewportInteractions`)
- L84 _variable_ `static FName DragMovesCamera = TEXT("Dra` (scope `UE::Editor::ViewportInteractions`)
- L88 _variable_ `static const FName ViewportClick = TEXT("Vie` (scope `UE::Editor::ViewportInteractions`) — Interactions that click on the viewport
- L90 _variable_ `static const FName CameraDrag = TEXT("Cam` (scope `UE::Editor::ViewportInteractions`) — Interactions that move the camera via mouse motion
- L92 _variable_ `static const FName CameraFly = TEXT("Cam` (scope `UE::Editor::ViewportInteractions`) — Interactions the enable FPS camera movement

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportInteractionBindings.h` (Public)


#### enum `UE::Editor::ViewportInteractions::EInputStage`  
`enum class EInputStage`  
_L12-18_
- L15 _public enumerator_ `Start` — Where the behavior has not yet started.
- L17 _public enumerator_ `Continue` — Where the behavior has started and needs to validate that it can continue.

#### struct `UE::Editor::ViewportInteractions::FButtonBinding`  
`struct FButtonBinding`  
_L20-69_
- L22 _public function_ `FButtonBinding(const FKey& InButton) : Chord(InButton) , Command(nullptr)`
- L27 _public function_ `FButtonBinding(const TSharedPtr<FUICommandInfo>& InCommand) : Chord() , Command(InCommand)`
- L32 _public prototype_ `FButtonBinding(const FButtonBinding& InBinding) = default;`
- L34 _public member_ `FInputChord Chord;`
- L35 _public member_ `TWeakPtr<FUICommandInfo> Command;`
- L39 _public member_ `bool bRequiredToStart = true;` — This button must be down for the behavior begin capture.
- L41 _public member_ `bool bTriggersStart = false;` — If any binding is set to true, the behavior can capture when this button is pressed and all required buttons are active.
- L43 _public member_ `bool bRequiredToContinue = true;` — This button must be down for the behavior to continue capture. Should be a subset of bRequiredToStart.
- L45 _public function_ `FButtonBinding& TriggersStart(bool bTriggers = true)`
- L51 _public function_ `FButtonBinding& Required(bool bRequired = true)`
- L58 _public function_ `FButtonBinding& RequiredToStart(bool bRequired = true)`
- L64 _public function_ `FButtonBinding& RequiredToContinue(bool bRequired = true)`

#### struct `UE::Editor::ViewportInteractions::FButtonBindings`  
`struct FButtonBindings`  
_L72-87_
- L74 _public prototype_ `FButtonBindings() = default;`
- L75 _public prototype_ `FButtonBindings(const FButtonBindings& OtherBindings) = default;`
- L76 _public prototype_ `FButtonBindings(const TArray<FButtonBinding>& InBindings);`
- L78 _public member_ `TArray<FButtonBinding> Bindings;`
- L79 _public member_ `bool bRequiresTrigger = false;`
- L81 _public prototype_ `int32 GetBindingComplexity(EInputStage Stage, const FInputDeviceState& InputDeviceState) const;`
- L82 _public prototype_ `bool DidAnyBindingStateChange(const FInputDeviceState& InputDeviceState) const;`
- L85 _protected prototype_ `static void ProcessBinding(EInputStage Stage, const FInputDeviceState& InputDeviceState, const FButtonBinding& Binding, int32& OutComplexity, bool& bOutTrigger);`
- L86 _protected prototype_ `static void ProcessBindingChord(EInputStage Stage, const FInputDeviceState& InputDeviceState, const FButtonBinding& Binding, const FInputChord& Chord, int32& OutComplexity, bool& bOutTrigger);`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Editor` (scope `UE`)
- L9 _namespace_ `namespace ViewportInteractions` (scope `UE::Editor`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportInteractionsBehaviorSource.h` (Public)


#### struct `FViewportInteractionGroup`  
`struct FViewportInteractionGroup`  
_L64-70_
- reflection: `USTRUCT()`
- L69 _public member_ `TArray<TObjectPtr<UViewportInteraction>> Interactions;` — `UPROPERTY()`

#### class `UViewportInteractionsBehaviorSource`  
`class UViewportInteractionsBehaviorSource final : public UObject , public IInputBehaviorSource , public IModifierToggleBehaviorTarget`  
_L81-393_
- reflection: `UCLASS(Transient, MinimalAPI)`
- inherits: `UObject,IInputBehaviorSource,IModifierToggleBehaviorTarget`
- desc: This class hosts a list of ITF Viewport Interactions and a UBehaviorSet containing the UInteractionBehavior instances required by those Viewport Interactions. It also acts as a behavior target, registering the status of Shift, Alt, Ctrl modifier keys. That and other pieces of information can be accessed externally, so that e.g. Viewport Interactions can know about modifier states without having to implement themselves what would be duplicate logic to handle those inputs. This class can also be used to know whether the Viewport camera is being moved using the mouse,or to mark it as such.
- L90 _public function_ `virtual const UInputBehaviorSet* GetInputBehaviors() const override`
- L97 _public prototype_ `virtual void OnUpdateModifierState(int InModifierID, bool bInIsOn) override;`
- L98 _public prototype_ `virtual void OnForceEndCapture() override;`
- L104 _public prototype_ `void Initialize(UEditorInteractiveToolsContext* InInteractiveToolsContext);` — Will initialize the required behaviors and the Behavior Set
- L109 _public prototype_ `void RegisterBehaviorSources();` — Register this Input Behavior Source to the InputRouter
- L114 _public prototype_ `void DeregisterBehaviorSources();` — Deregister this Input Behavior Source from the InputRouter
- L119 _public prototype_ `void Tick(float InDeltaTime);` — Call Tick on those Viewport Interactions which require it (e.g. Camera Mover)
- L124 _public prototype_ `void RenderTools(IToolsContextRenderAPI* InRenderAPI) const;` — Renders the active tool on the specified View/World
- L129 _public prototype_ `void DrawTools(FCanvas* InCanvas, IToolsContextRenderAPI* InRenderAPI) const;` — Draws the active tool on the specified View/Canvas
- L134 _public prototype_ `void AddInteractions(const TArray<const UClass*>& InInteractions, bool bInReregister = false);` — Add the specified interactions to this Behavior Source
- L139 _public prototype_ `UViewportInteraction* AddInteraction(const UClass* InInteractionClass, bool bInReregister = false);` — Add the specified interaction to this Behavior Source
- L144 _public prototype_ `UViewportInteraction* FindInteraction(const UClass* InInteractionClass) const;` — Finds an interaction with a given class if one exists
- L149 _public prototype_ `UViewportInteraction* FindInteraction(const FName& InName) const;` — Finds an interaction with a given name if one exists
- L154 _public prototype_ `bool IsAnyInteractionInGroupEnabled(const FName& InName) const;` — Returns true if any interaction in the given group is enabled. An enabled interaction can potentially take action.
- L159 _public prototype_ `bool IsAnyInteractionInGroupActive(const FName& InName) const;` — Returns true if any interaction in the given group is active. An active interaction is currently taking action.
- L164 _public prototype_ `void RemoveInteraction(const FName InInteractionName, bool bInReregister = false);` — Removes the specified interaction from the active ones.
- L170 _public prototype_ `void Reset();` — De-registers behaviors, removes viewport interactions. Behaviors added by Initialize will be kept around.
- L176 _public function_ `template<class T> T* GetTypedViewportInteraction() const` — Returns the first Viewport Interaction of type T
- L197 _public function_ `template<class T> TArray<T*> GetTypedViewportInteractions() const` — Returns all Viewport Interactions of type T
- L218 _public prototype_ `void SetMouseCursorOverride(EMouseCursor::Type InMouseCursor);` — Sets current mouse cursor override
- L220 _public prototype_ `void ClearMouseCursorOverride();`
- L227 _public function_ `template<class T> T* AddInteraction(bool bInReregister = false)` — Use the templated version in case there is some class specific initialization required by the newly created interaction, since this method will return the newly instantiated interaction
- L232 _public function_ `bool IsShiftDown() const`
- L237 _public function_ `bool IsAltDown() const`
- L242 _public function_ `bool IsCtrlDown() const`
- L247 _public function_ `bool IsLeftMouseButtonDown() const`
- L252 _public function_ `bool IsMiddleMouseButtonDown() const`
- L257 _public function_ `bool IsRightMouseButtonDown() const`
- L262 _public prototype_ `bool IsMouseLooking() const;`
- L264 _public prototype_ `void SetIsMouseLooking(bool bInIsLooking);`
- L266 _public function_ `bool HasCameraMoved() const`
- L271 _public prototype_ `void SetCameraHasMoved(bool bInHasMoved);`
- L274 _public function_ `bool IsGizmoDragging() const` — Whether the Editor Transform Gizmo is being interacted with
- L280 _public function_ `UEditorTransformGizmo* GetEditorTransformGizmo() const` — If available, return the current Editor Transform Gizmo
- L285 _public prototype_ `FEditorModeTools* GetModeTools() const;`
- L287 _public prototype_ `FEditorViewportClient* GetEditorViewportClient() const;`
- L289 _public prototype_ `FEditorViewportClient* GetHoveredEditorViewportClient() const;`
- L291 _public function_ `FOnMouseLookingChanged& OnMouseLookingStateChanged()`
- L296 _public function_ `FOnModifierKeyChanged& OnAltKeyStateChanged()`
- L301 _public function_ `FOnModifierKeyChanged& OnCtrlKeyStateChanged()`
- L306 _public function_ `FOnModifierKeyChanged& OnShiftKeyStateChanged()`
- L311 _public prototype_ `void SetUnsupportedViewportInteractions(const TArray<FName>& InUnsupportedInteractions);`
- L313 _public function_ `const TArray<FName>& GetUnsupportedViewportInteractions() const`
- L323 _private member_ `TObjectPtr<UInputBehaviorSet> BehaviorSet;` — `UPROPERTY(Transient)` — All Input Behaviors from registered Viewport Interactions should be added to this Behavior Set (done with ::AddInteraction() )
- L327 _private member_ `TArray<TObjectPtr<UInputBehavior>> CoreBehaviors;` — `UPROPERTY(Transient)` — Behaviors that are guaranteed to always be present
- L334 _private member_ `TMap<FName, TObjectPtr<UViewportInteraction>> ViewportInteractions;` — `UPROPERTY(Transient)` — A collection of ITF-based Viewport Interactions Key is the interaction name (class name when no Interaction name is specified)
- L340 _private member_ `TMap<FName, FViewportInteractionGroup> ViewportInteractionGroups;` — `UPROPERTY(Transient)` — Groups <-> Interactions is a many-to-many relationship. This provides easy access to a list of interactions by group.
- L342 _private prototype_ `void SetAltKeyState(bool bInDown);`
- L343 _private prototype_ `void SetCtrlKeyState(bool bInDown);`
- L344 _private prototype_ `void SetShiftKeyState(bool bInDown);`
- L346 _private prototype_ `void RegisterProxyDelegates();`
- L347 _private prototype_ `void DeregisterProxyDelegates();`
- L349 _private prototype_ `void OnGizmoCreatedDelegate(UTransformGizmo* InTransformGizmo);`
- L350 _private prototype_ `void OnGizmoMovementBegin(UTransformProxy* InTransformProxy);`
- L351 _private prototype_ `void OnGizmoMovementEnd(UTransformProxy* InTransformProxy);`
- L353 _private prototype_ `UToolsContextCursorAPI* GetCursorAPI();`
- L355 _private prototype_ `void CacheCursorPosition();`
- L356 _private prototype_ `void RestoreCursorPosition();`
- L358 _private member_ `bool bIsShiftDown;`
- L359 _private member_ `bool bIsCtrlDown;`
- L360 _private member_ `bool bIsAltDown;`
- L362 _private member_ `bool bIsLeftMouseButtonDown;`
- L363 _private member_ `bool bIsMiddleMouseButtonDown;`
- L364 _private member_ `bool bIsRightMouseButtonDown;`
- L366 _private member_ `TOptional<EMouseCursor::Type> CursorOverride;`
- L367 _private member_ `TOptional<EMouseCursor::Type> LastCursorOverride;`
- L372 _private member_ `TOptional<FIntPoint> HiddenCursorPosition;` — Caches cursor position whenever we hide it, so we can place it back where it was as soon as we show it again
- L375 _private member_ `TWeakObjectPtr<UEditorInteractiveToolsContext> EditorInteractiveToolsContextWeak;` — `UPROPERTY(Transient)`
- L378 _private member_ `TWeakObjectPtr<UToolsContextCursorAPI> WeakCursorAPI = nullptr;` — `UPROPERTY(Transient)`
- L380 _private member_ `FOnMouseLookingChanged OnMouseLookingChangedDelegate;`
- L382 _private member_ `FOnModifierKeyChanged OnAltKeyStateChangedDelegate;`
- L383 _private member_ `FOnModifierKeyChanged OnCtrlKeyStateChangedDelegate;`
- L384 _private member_ `FOnModifierKeyChanged OnShiftKeyStateChangedDelegate;`
- L387 _private member_ `TObjectPtr<UEditorTransformGizmo> TransformGizmo;` — `UPROPERTY(Transient)`
- L389 _private member_ `bool bGizmoDragging = false;`
- L390 _private member_ `bool bCameraHasMoved = false;`
- L392 _private member_ `TArray<FName> UnsupportedInteractions;`

#### Free symbols / members of external scopes

- L25 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
- L27 _namespace_ `namespace UE`
- L27 _namespace_ `namespace Editor` (scope `UE`)
- L27 _namespace_ `namespace ViewportInteractions` (scope `UE::Editor`)
- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnEditorViewportInteractionsToggleDelegate) bool UseEditorViewportInteractions();`
- L30 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnEditorViewportInteractionsToggleDelegate) bool UseEditorViewportInteractions();` (scope `UE::Editor::ViewportInteractions`)
- L40 _prototype_ `bool IsVerbose();` (scope `UE::Editor::ViewportInteractions`) — Helps hiding unwanted logs. For testing.
- L45 _prototype_ `void ToggleEditorViewportInteractions(bool bInEnable);` (scope `UE::Editor::ViewportInteractions`) — Toggles ITF Viewport Interactions On/Off
- L47 _prototype_ `FOnEditorViewportInteractionsToggleDelegate& OnEditorViewportInteractionsActivated();` (scope `UE::Editor::ViewportInteractions`)
- L48 _prototype_ `FOnEditorViewportInteractionsToggleDelegate& OnEditorViewportInteractionsDeactivated();` (scope `UE::Editor::ViewportInteractions`)
- L53 _prototype_ `bool CommandMatchesKey(const TSharedPtr<FUICommandInfo>& InCommandInfo, const FKey& InKeyID);` (scope `UE::Editor::ViewportInteractions`) — Checks whether the specified Command should be triggered by the specified Key
- L57 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogITFViewportInteractions, Log, All);`
- L57 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogITFViewportInteractions, Log, All);`
- L59 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnMouseLookingChanged, bool ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierKeyChanged, bool ) USTRUCT() struct FViewportInteractionGroup { GENERATED_BODY() UPROPERTY() TArray<TObjectPtr<UViewportInteraction>> Interactions; };`
- L61 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierKeyChanged, bool ) USTRUCT() struct FViewportInteractionGroup { GENERATED_BODY() UPROPERTY() TArray<TObjectPtr<UViewportInteraction>> Interactions; };`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportInteractionsUtilities.h` (Public)


#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Editor` (scope `UE`)
- L10 _namespace_ `namespace ViewportInteractions` (scope `UE::Editor`)
- L16 _prototype_ `void AddDefaultCameraMovementInteractions(UViewportInteractionsBehaviorSource* InInteractionsBehaviorSource);` (scope `UE::Editor::ViewportInteractions`) — Convenience function to add "standard" movement interactions to the specified Viewport Interactions Behavior Source e.g. Movement, Rotation, View Angle, Orbit, Panning, FOV, etc
- L18 _prototype_ `void AddDefaultDragToolsInteractions(UViewportInteractionsBehaviorSource* InInteractionsBehaviorSource);` (scope `UE::Editor::ViewportInteractions`)

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportLegacyClickInteraction.h` (Public)


#### class `UViewportLegacyClickInteraction`  
`class UViewportLegacyClickInteraction : public UViewportClickInteraction, public IHoverBehaviorTarget`  
_L16-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportClickInteraction,IHoverBehaviorTarget`
- desc: An interaction that passes through ITF clicks through to the legacy viewport click handlers.
- L21 _public prototype_ `UViewportLegacyClickInteraction();`
- L23 _public prototype_ `virtual void OnClickDown(const FInputDeviceRay& InClickPos) override;`
- L25 _public prototype_ `virtual FInputRayHit BeginHoverSequenceHitTest(const FInputDeviceRay& PressPos) override;`
- L26 _public prototype_ `virtual void OnBeginHover(const FInputDeviceRay& DevicePos) override;`
- L27 _public prototype_ `virtual bool OnUpdateHover(const FInputDeviceRay& DevicePos) override;`
- L28 _public prototype_ `virtual void OnEndHover() override;`
- L32 _protected prototype_ `virtual void BuildBehaviors() override;`
- L34 _protected prototype_ `virtual void ProcessClick_Internal(const FViewportClick& InViewportClick, HHitProxy* InHitProxy, FSceneView& View) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportMoveYawInteraction.h` (Public)


#### class `UViewportMoveYawInteraction`  
`class UViewportMoveYawInteraction : public UViewportDragInteraction`  
_L17-37_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportDragInteraction`
- desc: Implements the LMB + Drag Horizontal plane move + Yaw interaction
- L23 _public prototype_ `UViewportMoveYawInteraction();`
- L26 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L27 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L31 _public prototype_ `virtual bool CanBeActivated() const override;`
- L32 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`
- L36 _protected prototype_ `virtual TArray<FEditorModeID> GetUnsupportedModes() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportOrbitInteraction.h` (Public)


#### class `UViewportOrbitInteraction`  
`class UViewportOrbitInteraction : public UViewportDragInteraction`  
_L15-37_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportDragInteraction`
- desc: Triggers orbiting around current viewport focus
- L21 _public prototype_ `UViewportOrbitInteraction();`
- L24 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L25 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L29 _public prototype_ `virtual bool CanBeActivated() const override;`
- L30 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`
- L34 _private member_ `UE::Editor::ViewportInteractions::FButtonBindings NormalBindings;`
- L35 _private member_ `UE::Editor::ViewportInteractions::FButtonBindings CameraLockedBindings;`
- L36 _private prototype_ `const UE::Editor::ViewportInteractions::FButtonBindings& GetBindings() const;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportOrthoPanInteraction.h` (Public)


#### class `UViewportOrthoPanInteraction`  
`class UViewportOrthoPanInteraction : public UViewportDragInteraction`  
_L15-31_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UViewportDragInteraction`
- desc: Implements panning for orthographic views. Holding Alt or Shift inverts the panning direction.
- L20 _public prototype_ `UViewportOrthoPanInteraction();`
- L23 _public prototype_ `virtual bool CanBeActivated() const override;`
- L24 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L25 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L29 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportPanInteraction.h` (Public)


#### class `UViewportPanInteraction`  
`class UViewportPanInteraction : public UViewportDragInteraction`  
_L17-36_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportDragInteraction`
- desc: Implements the middle mouse pan interaction
- L22 _public prototype_ `UViewportPanInteraction();`
- L25 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L26 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L30 _public prototype_ `virtual bool CanBeActivated() const override;`
- L31 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`
- L35 _protected prototype_ `static void PanCamera(FEditorViewportClient& Client, float MouseDeltaX, float MouseDeltaY, bool bInvert, bool bUseWorldSpaceUp);`

#### class `UViewportMovePanInteraction`  
`class UViewportMovePanInteraction : public UViewportPanInteraction`  
_L42-51_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportPanInteraction`
- desc: Implements the LMB + RMB Drag world-space-up Pan interaction
- L47 _public prototype_ `UViewportMovePanInteraction();`
- L50 _protected prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`

#### class `UViewportTrackpadPanInteraction`  
`class UViewportTrackpadPanInteraction : public UViewportMovePanInteraction`  
_L57-65_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportMovePanInteraction`
- desc: Handles RMB + Trackpad movement for world-space-up Panning
- L62 _public prototype_ `UViewportTrackpadPanInteraction();`
- L64 _public prototype_ `virtual bool CanBeActivated() const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportSnapToggleInteraction.h` (Public)


#### class `UViewportSnapToggleInteraction`  
`class UViewportSnapToggleInteraction : public UViewportInteraction, public IQuickToggleBehaviorTarget`  
_L20-66_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportInteraction,IQuickToggleBehaviorTarget`
- desc: A viewport interaction that handles temporary and permanent snapping toggles Hold: toggles the relevant snap setting while the key is held, restoring on release. Quick-press: permanently toggles the snap setting
- L25 _public prototype_ `UViewportSnapToggleInteraction();`
- L28 _public prototype_ `virtual void Shutdown() override;`
- L32 _public prototype_ `virtual void OnQuickToggle(const FKey& InKey) override;`
- L36 _public prototype_ `virtual void OnKeyPressed(const FKey& InKeyID) override;`
- L37 _public prototype_ `virtual void OnKeyReleased(const FKey& InKeyID) override;`
- L38 _public prototype_ `virtual void OnForceEndCapture() override;`
- L43 _protected prototype_ `virtual void OnCommandChordChanged() override;`
- L44 _protected prototype_ `virtual TArray<TSharedPtr<FUICommandInfo>> GetCommands() const override;`
- L47 _protected prototype_ `TArray<FKey> GetKeys() const;`
- L50 _private prototype_ `static void SetSurfaceSnapping(bool bEnable);`
- L51 _private prototype_ `static bool CanTemporaryDisableSnapping();`
- L53 _private prototype_ `void SetTRSSnapping(bool bEnable) const;`
- L54 _private prototype_ `UE::Widget::EWidgetMode GetWidgetMode() const;`
- L55 _private prototype_ `void CacheTRSSnapping();`
- L56 _private prototype_ `void CacheSurfaceSnapping();`
- L59 _private member_ `TWeakObjectPtr<UViewportQuickToggleInputBehavior> QuickToggleBehaviorWeak;`
- L61 _private member_ `bool bCachedTRSSnapping = false;`
- L62 _private member_ `bool bCachedSurfaceSnapping = false;`
- L64 _private member_ `bool bTRSKeyHeld = false;`
- L65 _private member_ `bool bSurfaceKeyHeld = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportViewAngleInteraction.h` (Public)


#### class `UViewportViewAngleInteraction`  
`class UViewportViewAngleInteraction : public UViewportDragInteraction`  
_L15-33_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportDragInteraction`
- desc: Implements the RMB + Drag interaction used to change the current Camera View angle
- L21 _public prototype_ `UViewportViewAngleInteraction();`
- L24 _public prototype_ `virtual bool CanBeActivated() const override;`
- L25 _public prototype_ `virtual void OnDragStart(const FInputDeviceRay& InDragStartPos) override;`
- L26 _public prototype_ `virtual void OnDragEnd(const FInputDeviceRay& InDragEndPos) override;`
- L30 _public prototype_ `virtual void OnDragDelta(float InMouseDeltaX, float InMouseDeltaY) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`

### `Source/Editor/Experimental/EditorInteractiveToolsFramework/Public/ViewportInteractions/ViewportZoomInteraction.h` (Public)


#### class `UViewportZoomInteraction`  
`class UViewportZoomInteraction : public UViewportInteraction , public IMouseWheelBehaviorTarget , public IKeyInputBehaviorTarget`  
_L16-56_
- reflection: `UCLASS(MinimalAPI, Transient)`
- inherits: `UViewportInteraction,IMouseWheelBehaviorTarget,IKeyInputBehaviorTarget`
- desc: Implements a viewport interaction to change the current zoom level, using either keyboard inputs or the mouse wheel
- L24 _public prototype_ `UViewportZoomInteraction();`
- L27 _public prototype_ `virtual FInputRayHit ShouldRespondToMouseWheel(const FInputDeviceRay& InCurrentPos) override;`
- L28 _public prototype_ `virtual void OnMouseWheelScrollUp(const FInputDeviceRay& InCurrentPos) override;`
- L29 _public prototype_ `virtual void OnMouseWheelScrollDown(const FInputDeviceRay& InCurrentPos) override;`
- L33 _public prototype_ `virtual void OnKeyPressed(const FKey& InKeyID) override;`
- L34 _public prototype_ `virtual void OnKeyReleased(const FKey& InKeyID) override;`
- L35 _public prototype_ `virtual void OnForceEndCapture() override;`
- L39 _public prototype_ `virtual void Tick(float InDeltaTime) const override;`
- L43 _private prototype_ `void OrthographicZoom(bool bInZoomIn, float InZoomMultiplier = 1.0f, bool bInForceZoomToCenter = false) const;`
- L44 _private prototype_ `void PerspectiveZoom(bool bInZoomIn) const;`
- L45 _private prototype_ `void MouseWheelZoom(bool bInZoomIn) const;`
- L47 _private prototype_ `void OnDragStart();`
- L48 _private prototype_ `void OnDragEnd();`
- L49 _private prototype_ `void OnClickDrag(const FVector2D& InDelta);`
- L51 _private member_ `int16 ZoomDirection = 0;`
- L54 _private member_ `FKey ZoomIn = EKeys::Add;` — TODO: make them customizable
- L55 _private member_ `FKey ZoomOut = EKeys::Subtract;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API EDITORINTERACTIVETOOLSFRAMEWORK_API`
