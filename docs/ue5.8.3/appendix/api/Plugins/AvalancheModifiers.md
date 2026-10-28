# Plugins / AvalancheModifiers

- module root: `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers`
- headers: 37; symbols: 1031
- symbol kinds: class=32, delegate=2, enum=20, enumerator=69, function=146, macro=1, member=264, namespace=2, prototype=478, struct=17
- PrivateDependencyModuleNames: AssetRegistry, AssetTools, Avalanche, AvalancheOutliner, AvalancheSceneTree, AvalancheShapes, ClonerEffectorMeshBuilder, DynamicMaterial, GeometryAlgorithms, GeometryFramework, GeometryMask, GeometryScriptingCore, MeshModelingToolsExp, ModelingComponents, ModelingOperators, ProceduralMeshComponent, SlateCore, Text3D, UnrealEd
- PublicDependencyModuleNames: ActorModifier, ActorModifierCore, ActorModifierLayout, Avalanche, AvalancheSequence, Core, CoreUObject, DynamicMesh, Engine, GeometryCore

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Private/AvaModifiersActorUtils.h` (Private)


#### struct `FAvaModifiersActorUtils`  
`struct FAvaModifiersActorUtils`  
_L17-23_
- desc: All operations that can be reused or shared in modifiers should go here
- L20 _public prototype_ `static AActor* FindActorFromReferenceContainer(AActor* const InActor, const EActorModifierReferenceContainer InReferenceContainer, const bool bInIgnoreHiddenActors);` — Begin Outliner
- L21 _public prototype_ `static TArray<AActor*> GetReferenceActors(const FActorModifierSceneTreeActor* InTrackedActor);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Private/AvaModifiersModule.h` (Private)


#### class `FAvalancheModifiersModule`  
`class FAvalancheModifiersModule : public IModuleInterface`  
_L11-21_
- inherits: `IModuleInterface`
- L15 _public prototype_ `virtual void StartupModule() override;`
- L16 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _private prototype_ `TSharedPtr<IActorModifierSceneTreeCustomResolver> GetSceneTreeResolver(ULevel* InLevel);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Private/AvaModifiersSceneTreeResolver.h` (Private)


#### class `FAvaModifiersSceneTreeResolver`  
`class FAvaModifiersSceneTreeResolver : public IActorModifierSceneTreeCustomResolver`  
_L21-164_
- inherits: `IActorModifierSceneTreeCustomResolver`
- desc: This allows modifier to preserve hierarchy of the Motion Design outliner
- L24 _public function_ `explicit FAvaModifiersSceneTreeResolver(ULevel* InLevel) : LevelWeak(InLevel)`
- L28 _public function_ `virtual void Activate() override`
- L62 _public function_ `virtual void Deactivate() override`
- L91 _public function_ `virtual bool GetDirectChildrenActor(AActor* InActor, TArray<AActor*>& OutActors) const override`
- L102 _public function_ `virtual bool GetRootActors(ULevel* InLevel, TArray<AActor*>& OutActors) const override`
- L144 _public function_ `virtual FOnActorHierarchyChanged::RegistrationType& OnActorHierarchyChanged() override`
- L151 _private function_ `void OnOutlinerLoaded()`
- L156 _private function_ `void OnOutlinerHierarchyChanged(AActor* InActor, const AActor* InParent, EAvaOutlinerHierarchyChangeType InChange)`
- L162 _private member_ `FOnActorHierarchyChanged OnHierarchyChangedDelegate;`
- L163 _private member_ `TWeakObjectPtr<ULevel> LevelWeak;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Private/Tools/AvaPatternModifierTool.h` (Private)


#### class `UAvaPatternModifierTool`  
`class UAvaPatternModifierTool : public UObject`  
_L9-20_
- reflection: `UCLASS(Abstract)`
- inherits: `UObject`
- desc: Represent a tool supported by the pattern modifier
- L14 _public prototype_ `virtual TArray<FTransform> GetTransformInstances(const FBox& InOriginalBounds) const PURE_VIRTUAL(UAvaPatternModifierTool::GetTransformInstances, return {}; );`
- L15 _public prototype_ `virtual FVector GetCenterAlignmentAxis() const PURE_VIRTUAL(UAvaPatternModifierTool::GetCenterAlignmentAxis, return FVector::ZeroVector; );`
- L16 _public prototype_ `virtual FName GetToolName() const PURE_VIRTUAL(UAvaPatternModifierTool::GetToolName, return NAME_None; );`
- L19 _protected prototype_ `void OnToolPropertiesChanged() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Private/Tools/AvaTaperTool.h` (Private)


#### enum `EAvaTaperInterpolationType`  
`enum class EAvaTaperInterpolationType : uint8`  
_L16-23_
- reflection: `UENUM()`
- L18 _public enumerator_ `Linear`
- L19 _public enumerator_ `Quadratic`
- L20 _public enumerator_ `Cubic`
- L21 _public enumerator_ `QuadraticInverse`
- L22 _public enumerator_ `CubicInverse`

#### struct `FAvaTaperSettings`  
`struct FAvaTaperSettings`  
_L26-51_
- reflection: `USTRUCT()`
- L32 _public member_ `float Amount = 1.0;` — `UPROPERTY()` — the amount of taper to apply [0;1] as min-max range. Values out of this range will be clamped.
- L36 _public member_ `int ZAxisResolution = 2;` — `UPROPERTY()` — Number of lattice vertices along the Z axis
- L40 _public member_ `EAvaTaperInterpolationType InterpolationType = EAvaTaperInterpolationType::Linear;` — `UPROPERTY()` — Whether to use linear or cubic interpolation to get new mesh vertex positions from the lattice
- L44 _public member_ `bool bDeformNormals = false;` — `UPROPERTY()` — Whether to use approximate new vertex normals using the deformer
- L47 _public member_ `FVector2D Extent = FVector2D::UnitVector;` — `UPROPERTY()`
- L50 _public member_ `FVector2D Offset = FVector2D::ZeroVector;` — `UPROPERTY()`

#### class `UAvaTaperTool`  
`class UAvaTaperTool : public UObject`  
_L57-130_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: @brief A taper tool based on how ULatticeDeformerTool uses FFFDLattice
- L67 _public prototype_ `bool Setup(UE::Geometry::FDynamicMesh3* InMesh, const FAvaTaperSettings& InTaperSettings);` — Setup the Taper deformation tool @param InMesh the dynamic mesh to be tapered @param InTaperSettings
- L70 _public prototype_ `void SetTaperAmount(float InAmount);` — sets the amount of taper to apply [0;1] as min-max range. Values out of this range will be clamped.
- L73 _public prototype_ `void SetInterpolationType(EAvaTaperInterpolationType InInterpolationType);` — sets the type of interpolation used by the taper modifier
- L76 _public prototype_ `void SetVerticalResolution(int32 InResolution);` — sets vertical resolution that directly affects the number of control points used by the taper modifier. Should match the tessellation/resolution of the mesh
- L79 _public prototype_ `void SetDeformNormals(bool bInDeformNormals);` — if true, applies normal deformation
- L81 _public prototype_ `void SetTaperOffset(const FVector2D& InTaperOffset);`
- L88 _public prototype_ `bool ApplyTaper(TUniquePtr<UE::Geometry::FDynamicMesh3>& OutMesh);` — Applies the taper modifier to the mesh specified at Setup time, and stores the result in the specified dynamic mesh @param OutMesh the dynamic mesh where the taper result will be stored @return if taper was applied successfully
- L92 _private member_ `TSharedPtr<UE::Geometry::FDynamicMesh3, ESPMode::ThreadSafe> OriginalMesh = nullptr;` — Input mesh
- L93 _private member_ `TSharedPtr<UE::Geometry::FFFDLattice, ESPMode::ThreadSafe> Lattice = nullptr;`
- L96 _private member_ `TArray<FVector3d> ControlPoints;` — `UPROPERTY()`
- L99 _private member_ `FAvaTaperSettings Settings;` — `UPROPERTY()`
- L103 _private member_ `double MinValue = 0.0;` — `UPROPERTY()` — min and max Z values are used to map the taper along the z axis of the geometry
- L107 _private member_ `double MaxValue = 0.0;` — `UPROPERTY()` — min and max Z values are used to map the taper along the z axis of the geometry
- L110 _private prototype_ `void UpdateMinMaxZ();` — Refreshes min and max Z values based on current control points Z position
- L117 _private prototype_ `double GetInterpolatedModifier(double InModifier) const;` — Applies the current interpolation type to the specified Modifier value @param InModifier the value to be interpolated @return the interpolated value
- L120 _private prototype_ `void InitializeLattice(TArray<FVector3d>& OutLatticePoints);` — Create and store an FFFDLattice. Pass out the lattice's positions
- L123 _private prototype_ `UE::Geometry::FVector3i GetLatticeResolution() const;` — Returns this Lattice resolution as a vector. Used internally.
- L129 _private prototype_ `TUniquePtr<UE::Geometry::FDynamicMesh3> Compute();` — Internal function to compute the taper. Requires the TaperLatticeTool to be Setup. @return The tapered mesh (nullptr when failing)

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/AvaModifiersLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaModifier, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAvaModifier, Log, All);`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/AvaModifiersParametricMaterial.h` (Public)


#### struct `FAvaModifiersParametricMaterial`  
`struct FAvaModifiersParametricMaterial`  
_L15-41_
- reflection: `USTRUCT()`
- desc: Use this if you want a parametric material
- L19 _public prototype_ `FAvaModifiersParametricMaterial();`
- L21 _public prototype_ `UMaterial* GetDefaultMaterial() const;`
- L23 _public prototype_ `UMaterialInstanceDynamic* GetMaterial() const;`
- L25 _public prototype_ `void ApplyChanges(UObject* Outer = nullptr);`
- L28 _public member_ `FLinearColor MaskColor;` — `UPROPERTY()`
- L31 _private prototype_ `void ApplyParams() const;`
- L32 _private prototype_ `void CreateAndApply(UObject* Outer = nullptr);`
- L33 _private prototype_ `void EnsureCurrentMaterial(UObject* Outer = nullptr);`
- L34 _private prototype_ `UMaterial* LoadResource() const;`
- L37 _private member_ `TObjectPtr<UMaterial> DefaultMaterial;` — `UPROPERTY()`
- L40 _private member_ `TObjectPtr<UMaterialInstanceDynamic> InstanceMaterial;` — `UPROPERTY(Transient, Instanced)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/AvaModifiersPreviewPlane.h` (Public)


#### struct `FAvaModifierPreviewPlane`  
`struct FAvaModifierPreviewPlane`  
_L15-47_
- reflection: `USTRUCT()`
- desc: Use this if you want a preview plane on a specific actor
- L19 _public prototype_ `explicit FAvaModifierPreviewPlane();`
- L22 _public prototype_ `void Create(USceneComponent* InActorComponent);` — Create a preview plane attached to this component
- L25 _public prototype_ `void Destroy();` — Destroy the preview plane
- L28 _public prototype_ `void Show() const;` — Show the preview plane
- L31 _public prototype_ `void Hide() const;` — Hide the preview plane
- L34 _public prototype_ `void Update(const FTransform& InRelativeTransform) const;` — Update relative position of the plane
- L37 _public member_ `FAvaModifiersParametricMaterial PreviewDynMaterial;` — `UPROPERTY(Transient)`
- L40 _protected prototype_ `UStaticMesh* LoadPreviewResource() const;`
- L43 _protected member_ `TObjectPtr<UStaticMesh> PreviewStaticMesh = nullptr;` — `UPROPERTY(Transient)`
- L46 _protected member_ `TObjectPtr<UStaticMeshComponent> PreviewComponent = nullptr;` — `UPROPERTY(Transient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaAutoSizeModifier.h` (Public)


#### enum `EAvaAutoSizeFitMode`  
`enum class EAvaAutoSizeFitMode : uint8`  
_L16-21_
- reflection: `UENUM()`
- L18 _public enumerator_ `WidthAndHeight`
- L19 _public enumerator_ `WidthOnly`
- L20 _public enumerator_ `HeightOnly`

#### class `UAvaAutoSizeModifier`  
`class UAvaAutoSizeModifier : public UAvaGeometryBaseModifier , public IActorModifierTransformUpdateHandler , public IActorModifierRenderStateUpdateHandler , public IActorModifierSceneTreeUpdateHandler`  
_L27-168_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier,IActorModifierTransformUpdateHandler,IActorModifierRenderStateUpdateHandler,IActorModifierSceneTreeUpdateHandler`
- desc: Adapts the modified actor geometry size/scale to match reference actor bounds and act as a background
- L36 _public prototype_ `void SetReferenceActor(const FActorModifierSceneTreeActor& InReferenceActor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoSize")`
- L39 _public function_ `const FActorModifierSceneTreeActor& GetReferenceActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoSize")`
- L45 _public prototype_ `void SetPaddingHorizontal(double InPadding);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoSize")`
- L48 _public function_ `double GetPaddingHorizontal() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoSize")`
- L54 _public prototype_ `void SetPaddingVertical(double InPadding);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoSize")`
- L57 _public function_ `double GetPaddingVertical() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoSize")`
- L63 _public prototype_ `void SetFitMode(const EAvaAutoSizeFitMode InFitMode);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoSize")`
- L66 _public function_ `EAvaAutoSizeFitMode GetFitMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoSize")`
- L72 _public prototype_ `void SetIncludeChildren(bool bInIncludeChildren);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoSize")`
- L75 _public function_ `bool GetIncludeChildren() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoSize")`
- L82 _protected prototype_ `virtual void PostLoad() override;`
- L84 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L89 _protected prototype_ `virtual bool IsModifierDirtyable() const override;`
- L90 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L91 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L92 _protected prototype_ `virtual void SavePreState() override;`
- L93 _protected prototype_ `virtual void RestorePreState() override;`
- L94 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L95 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L96 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L97 _protected prototype_ `virtual void Apply() override;`
- L101 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L105 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L106 _protected prototype_ `virtual void OnActorVisibilityChanged(AActor* InActor) override;`
- L110 _protected prototype_ `virtual void OnSceneTreeTrackedActorChanged(int32 InIdx, AActor* InPreviousActor, AActor* InNewActor) override;`
- L111 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L112 _protected function_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) override`
- L113 _protected function_ `virtual void OnSceneTreeTrackedActorParentChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousParentActor, const TArray<TWeakObjectPtr<AActor>>& InNewParentActor) override`
- L114 _protected function_ `virtual void OnSceneTreeTrackedActorRearranged(int32 InIdx, AActor* InRearrangedActor) override`
- L117 _protected prototype_ `void OnReferenceActorChanged();`
- L120 _protected member_ `FActorModifierSceneTreeActor ReferenceActor;` — `UPROPERTY(EditInstanceOnly, Setter="SetReferenceActor", Getter="GetReferenceActor", Category="AutoSize", meta=(ShowOnlyInnerProperties, AllowPrivateAccess="true"))`
- L124 _protected member_ `EActorModifierReferenceContainer ReferenceContainer_DEPRECATED = EActorModifierReferenceContainer::Other;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ReferenceActor instead"))` — The method for finding a reference actor based on it's position in the parent's hierarchy.
- L128 _protected member_ `TWeakObjectPtr<AActor> ReferenceActorWeak_DEPRECATED = nullptr;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ReferenceActor instead"))` — The actor affecting the modifier. This is user selectable if the Reference Container is set to "Other".
- L132 _protected member_ `bool bIgnoreHiddenActors_DEPRECATED = false;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ReferenceActor instead"))` — If true, will search for the next visible actor based on the selected reference container.
- L136 _protected member_ `double PaddingVertical = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Interp, Category="AutoSize", meta=(AllowPrivateAccess="true"))` — Padding for top and bottom side
- L140 _protected member_ `double PaddingHorizontal = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Interp, Category="AutoSize", meta=(AllowPrivateAccess="true"))` — Padding for left and right side
- L143 _protected member_ `EAvaAutoSizeFitMode FitMode = EAvaAutoSizeFitMode::WidthAndHeight;` — `UPROPERTY(EditInstanceOnly, Setter="SetFitMode", Getter="GetFitMode", Category="AutoSize", meta=(AllowPrivateAccess="true"))`
- L147 _protected member_ `bool bIncludeChildren = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetIncludeChildren", Getter="GetIncludeChildren", Category="AutoSize", meta=(AllowPrivateAccess="true"))` — If true, will include children bounds too and compute the new size
- L152 _private member_ `FMargin Padding = FMargin(0.f);` — `UPROPERTY()` — Padding added around reference actor bounds for geometry
- L155 _private member_ `FVector2D PreModifierShapeDynMesh2DSize;` — `UPROPERTY()`
- L158 _private member_ `TWeakObjectPtr<UAvaShape2DDynMeshBase> ShapeDynMesh2DWeak;` — `UPROPERTY()`
- L161 _private member_ `FVector CachedFollowLocation = FVector::ZeroVector;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`
- L164 _private member_ `FBox CachedReferenceBounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`
- L167 _private member_ `bool bDeprecatedPropertiesMigrated = false;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaBendModifier.h` (Public)


#### class `UAvaBendModifier`  
`class UAvaBendModifier : public UAvaGeometryBaseModifier`  
_L9-100_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- L15 _public prototype_ `void SetAngle(float InAngle);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bend")`
- L18 _public function_ `float GetAngle() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bend")`
- L24 _public prototype_ `void SetExtent(float InExtent);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bend")`
- L27 _public function_ `float GetExtent() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bend")`
- L33 _public prototype_ `void SetBendPosition(const FVector& InBendPosition);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bend")`
- L36 _public function_ `const FVector& GetBendPosition() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bend")`
- L42 _public prototype_ `void SetBendRotation(const FRotator& InBendRotation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bend")`
- L45 _public function_ `const FRotator& GetBendRotation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bend")`
- L51 _public prototype_ `void SetSymmetricExtents(bool bInSymmetricExtents);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bend")`
- L54 _public function_ `bool GetSymmetricExtents() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bend")`
- L60 _public prototype_ `void SetBidirectional(bool bInBidirectional);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bend")`
- L63 _public function_ `bool GetBidirectional() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bend")`
- L71 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L76 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L77 _protected prototype_ `virtual void Apply() override;`
- L80 _protected prototype_ `void OnBendTransformChanged();`
- L81 _protected prototype_ `void OnBendOptionChanged();`
- L84 _protected member_ `FVector BendPosition = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter="SetBendPosition", Getter="GetBendPosition", Category="Bend", meta=(AllowPrivateAccess="true"))`
- L87 _protected member_ `FRotator BendRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter="SetBendRotation", Getter="GetBendRotation", Category="Bend", meta=(AllowPrivateAccess="true"))`
- L90 _protected member_ `float Angle = 25;` — `UPROPERTY(EditInstanceOnly, Setter="SetAngle", Getter="GetAngle", Category="Bend", meta=(ClampMin="-360.0", ClampMax="360.0", AllowPrivateAccess="true"))`
- L93 _protected member_ `float Extent = 1.0;` — `UPROPERTY(EditInstanceOnly, Setter="SetExtent", Getter="GetExtent", Category="Bend", meta=(ClampMin="0", ClampMax="1.0", AllowPrivateAccess="true"))`
- L96 _protected member_ `bool bSymmetricExtents = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetSymmetricExtents", Getter="GetSymmetricExtents", Category="Bend", meta=(AllowPrivateAccess="true"))`
- L99 _protected member_ `bool bBidirectional = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetBidirectional", Getter="GetBidirectional", Category="Bend", meta=(AllowPrivateAccess="true"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaBevelModifier.h` (Public)


#### class `UAvaBevelModifier`  
`class UAvaBevelModifier : public UAvaGeometryBaseModifier`  
_L9-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- L14 _public member_ `static inline const FName BevelPolygroupLayerName = TEXT("Bev`
- L15 _public member_ `static constexpr float MinInset = 0;`
- L16 _public member_ `static constexpr int32 MinIterations = 0;`
- L17 _public member_ `static constexpr int32 MaxIterations = 10;`
- L18 _public member_ `static constexpr float MinRoundness = -2;`
- L19 _public member_ `static constexpr float MaxRoundness = 2;`
- L22 _public prototype_ `void SetInset(float InBevel);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bevel")`
- L25 _public function_ `float GetInset() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bevel")`
- L31 _public prototype_ `void SetIterations(int32 InIterations);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bevel")`
- L34 _public function_ `int32 GetIterations() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bevel")`
- L40 _public prototype_ `void SetRoundness(float InRoundness);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Bevel")`
- L43 _public function_ `float GetRoundness() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Bevel")`
- L51 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L56 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L57 _protected prototype_ `virtual void Apply() override;`
- L60 _protected prototype_ `void OnInsetChanged();`
- L61 _protected prototype_ `void OnIterationsChanged();`
- L62 _protected prototype_ `void OnRoundnessChanged();`
- L64 _protected prototype_ `float GetMaxInsetDistance() const;`
- L68 _protected member_ `float Inset = 1.0f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Bevel", meta=(ClampMin="0", AllowPrivateAccess="true"))` — Distance used on vertices for beveling, clamped between 0 and (min bound size / 2)
- L72 _protected member_ `int32 Iterations = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Bevel", meta=(ClampMin="0", ClampMax="10", AllowPrivateAccess="true"))` — Amount of subdivisions applied on the bevel, could affect performance the higher this value gets
- L76 _protected member_ `float Roundness = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Bevel", meta=(ClampMin="-2", ClampMax="2", EditCondition="Iterations > 0", AllowPrivateAccess="true"))` — Roundness of the beveling when multiple iterations are applied : -2 = inner rounded, 0 = flat, 2 = outer rounded

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaBooleanModifier.h` (Public)


#### enum `EAvaBooleanMode`  
`enum class EAvaBooleanMode : uint8`  
_L12-22_
- reflection: `UENUM(BlueprintType)`
- L15 _public enumerator_ `None UMETA(DisplayName="Target")` — Does not apply any mode, but get affected by other geometry modes
- L17 _public enumerator_ `Subtract` — Subtract this geometry from the one it is colliding with
- L19 _public enumerator_ `Intersect` — Only keep the intersecting geometry from the two colliding geometry
- L21 _public enumerator_ `Union` — Merges the two colliding geometry together

#### class `UAvaBooleanModifier`  
`class UAvaBooleanModifier : public UAvaGeometryBaseModifier , public IActorModifierTransformUpdateHandler`  
_L26-130_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier,IActorModifierTransformUpdateHandler`
- desc: This modifier allows you to apply a mask on a certain shape, this will affect every shape it collides with that matches options
- L35 _public member_ `static constexpr float MinDepth = UE_KINDA_SMALL_NUMBER * 2;` — This is the min depth threshold needed on the mask for it to work properly
- L38 _public prototype_ `void SetMode(EAvaBooleanMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Boolean")`
- L41 _public function_ `EAvaBooleanMode GetMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Boolean")`
- L47 _public prototype_ `void SetChannel(uint8 InChannel);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Boolean")`
- L50 _public function_ `uint8 GetChannel() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Boolean")`
- L55 _public function_ `const FAvaBooleanModifierSharedChannelInfo& GetChannelInfo() const`
- L63 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L68 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L69 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L70 _protected prototype_ `virtual void SavePreState() override;`
- L71 _protected prototype_ `virtual void RestorePreState() override;`
- L72 _protected prototype_ `virtual void Apply() override;`
- L73 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L74 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L75 _protected prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;`
- L79 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L82 _protected prototype_ `void ApplyInternal();`
- L84 _protected prototype_ `void OnModeChanged();`
- L85 _protected prototype_ `void OnChannelChanged();`
- L88 _protected prototype_ `void CreateMaskDepth() const;` — Creates depth for a mask shape that has none
- L91 _protected prototype_ `void OnMaskVisibilityChange(const UWorld* World, bool bMaskActorVisible) const;` — Called by the editor to change visibility of mask in a world
- L92 _protected prototype_ `void OnMaskingOptionsChanged();`
- L94 _protected prototype_ `void SaveOriginalMaterials();`
- L95 _protected prototype_ `void RestoreOriginalMaterials();`
- L97 _protected prototype_ `void UpdateMaskingMaterials();`
- L98 _protected prototype_ `void UpdateMaskDelegates();`
- L99 _protected prototype_ `void UpdateMaskVisibility();`
- L101 _protected prototype_ `static void ApplyTool(EAvaBooleanMode InMode, const UE::Geometry::FDynamicMesh3& InModeTool, const UAvaBooleanModifier* InTarget, UE::Geometry::FDynamicMesh3& OutMesh);`
- L105 _protected member_ `EAvaBooleanMode Mode = EAvaBooleanMode::None;` — `UPROPERTY(EditInstanceOnly, Setter="SetMode", Getter="GetMode", Category="Boolean", meta=(AllowPrivateAccess="true"))` — Mode to use when shapes are colliding, none means you will be masked otherwise you are masking
- L109 _protected member_ `uint8 Channel = 0;` — `UPROPERTY(EditInstanceOnly, Setter="SetChannel", Getter="GetChannel", Category="Boolean", meta=(AllowPrivateAccess="true"))` — Channel to only apply this tool on shapes with the same channel
- L112 _protected member_ `FAvaModifiersParametricMaterial ParametricMaskMaterial;` — `UPROPERTY(Transient)`
- L116 _protected member_ `TArray<TObjectPtr<UMaterialInterface>> OriginalMaterials;` — `UPROPERTY(DuplicateTransient, NonTransactional)` — Original materials before we apply the mask material
- L120 _protected member_ `TSet<TWeakObjectPtr<UAvaBooleanModifier>> CollidingModifiers;` — `UPROPERTY(DuplicateTransient, NonTransactional)` — Colliding actor modifiers to quickly update
- L124 _protected member_ `FAvaBooleanModifierSharedChannelInfo ChannelInfo;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — General infos on the channel used by this modifier profiler
- L129 _private member_ `FTransform LastTransform;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Track last transform during update to check against when moved

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaDynamicMeshConverterModifier.h` (Public)


#### enum `EAvaDynamicMeshConverterModifierType`  
`enum class EAvaDynamicMeshConverterModifierType : uint8`  
_L22-30_
- reflection: `UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))`
- desc: Components that can be converted to dynamic mesh
- L24 _public enumerator_ `None = 0 UMETA(Hidden)`
- L25 _public enumerator_ `StaticMeshComponent = 1 << 0`
- L26 _public enumerator_ `DynamicMeshComponent = 1 << 1`
- L27 _public enumerator_ `SkeletalMeshComponent = 1 << 2`
- L28 _public enumerator_ `BrushComponent = 1 << 3`
- L29 _public enumerator_ `ProceduralMeshComponent = 1 << 4`

#### enum `EAvaDynamicMeshConverterModifierFilter`  
`enum class EAvaDynamicMeshConverterModifierFilter : uint8`  
_L34-39_
- reflection: `UENUM(BlueprintType)`
- L36 _public enumerator_ `None`
- L37 _public enumerator_ `Include`
- L38 _public enumerator_ `Exclude`

#### struct `FAvaDynamicMeshConverterModifierComponentState`  
`struct FAvaDynamicMeshConverterModifierComponentState`  
_L42-80_
- reflection: `USTRUCT()`
- L46 _public function_ `explicit FAvaDynamicMeshConverterModifierComponentState()`
- L47 _public prototype_ `explicit FAvaDynamicMeshConverterModifierComponentState(UPrimitiveComponent* InPrimitiveComponent);`
- L49 _public prototype_ `void UpdateRelativeTransform(const FTransform& InParentTransform);`
- L56 _public function_ `bool operator==(const FAvaDynamicMeshConverterModifierComponentState& InOther) const`
- L63 _public member_ `TWeakObjectPtr<UPrimitiveComponent> Component;` — `UPROPERTY()` — The component we are converting to dynamic mesh
- L67 _public member_ `bool bComponentHiddenInGame = false;` — `UPROPERTY()` — The default visibility of the actor converted component in game
- L71 _public member_ `bool bComponentVisible = true;` — `UPROPERTY()` — The default visibility of the converted component in editor
- L75 _public member_ `FTransform ActorRelativeTransform = FTransform::Identity;` — `UPROPERTY()` — Transform saved before mesh is converted
- L79 _public member_ `TArray<TWeakObjectPtr<UMaterialInterface>> ComponentMaterialsWeak;` — `UPROPERTY(Transient)` — Used for diffs

#### class `UAvaDynamicMeshConverterModifier`  
`class UAvaDynamicMeshConverterModifier : public UAvaGeometryBaseModifier , public IActorModifierSceneTreeUpdateHandler , public IActorModifierRenderStateUpdateHandler`  
_L83-259_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier,IActorModifierSceneTreeUpdateHandler,IActorModifierRenderStateUpdateHandler`
- L92 _public function_ `void SetSourceActor(AActor* InActor)` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L98 _public function_ `AActor* GetSourceActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L103 _public prototype_ `void SetSourceActorWeak(const TWeakObjectPtr<AActor>& InActor);`
- L104 _public function_ `TWeakObjectPtr<AActor> GetSourceActorWeak() const`
- L110 _public prototype_ `void SetComponentTypes(const TSet<EAvaDynamicMeshConverterModifierType>& InTypes);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L113 _public prototype_ `TSet<EAvaDynamicMeshConverterModifierType> GetComponentTypes() const;` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L115 _public prototype_ `void SetComponentType(int32 InComponentType);`
- L117 _public function_ `int32 GetComponentType() const`
- L123 _public prototype_ `void SetFilterActorMode(EAvaDynamicMeshConverterModifierFilter InFilter);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L126 _public function_ `EAvaDynamicMeshConverterModifierFilter GetFilterActorMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L132 _public prototype_ `void SetFilterActorClasses(const TSet<TSubclassOf<AActor>>& InClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L135 _public function_ `const TSet<TSubclassOf<AActor>>& GetFilterActorClasses() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L141 _public prototype_ `void SetIncludeAttachedActors(bool bInInclude);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L144 _public function_ `bool GetIncludeAttachedActors() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L150 _public prototype_ `void SetHideConvertedMesh(bool bInHide);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L153 _public function_ `bool GetHideConvertedMesh() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L159 _public prototype_ `void SetUpdateInterval(float InInterval);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L162 _public function_ `float GetUpdateInterval() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|DynamicMeshConverter")`
- L170 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L173 _protected prototype_ `virtual void ConvertToStaticMeshAsset();` — Export current dynamic mesh to static mesh asset
- L178 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L179 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L180 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L181 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L182 _protected prototype_ `virtual void RestorePreState() override;`
- L183 _protected prototype_ `virtual void Apply() override;`
- L184 _protected prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;`
- L185 _protected prototype_ `virtual bool IsModifierDirtyable() const override;`
- L189 _protected function_ `virtual void OnSceneTreeTrackedActorChanged(int32 InIdx, AActor* InPreviousActor, AActor* InNewActor)`
- L190 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors);`
- L191 _protected function_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors)`
- L192 _protected function_ `virtual void OnSceneTreeTrackedActorParentChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousParentActor, const TArray<TWeakObjectPtr<AActor>>& InNewParentActor)`
- L193 _protected function_ `virtual void OnSceneTreeTrackedActorRearranged(int32 InIdx, AActor* InRearrangedActor)`
- L197 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent);`
- L198 _protected function_ `virtual void OnActorVisibilityChanged(AActor* InActor)`
- L201 _protected prototype_ `void OnSourceActorChanged();`
- L203 _protected prototype_ `bool ConvertComponents(TArray<TWeakObjectPtr<UMaterialInterface>>& OutMaterialsWeak);`
- L204 _protected prototype_ `bool HasFlag(EAvaDynamicMeshConverterModifierType InFlag) const;`
- L206 _protected prototype_ `void AddDynamicMeshComponent();`
- L207 _protected prototype_ `void RemoveDynamicMeshComponent();`
- L209 _protected prototype_ `void GetFilteredActors(TArray<AActor*>& OutActors) const;`
- L213 _protected member_ `TWeakObjectPtr<AActor> SourceActorWeak = GetModifiedActor();` — `UPROPERTY(EditInstanceOnly, Setter="SetSourceActorWeak", Getter="GetSourceActorWeak", Category="DynamicMeshConverter", meta=(DisplayName="SourceActor", AllowPrivateAccess="true"))` — What actor should we copy from, by default is self
- L217 _protected member_ `int32 ComponentType = static_cast<int32>( EAvaDynamicMeshConverterModifierType::StaticMeshComponent | EAvaDynamicMeshConverterModifierType::DynamicMeshComponent | EAvaDynamicMeshConverterModifierType::SkeletalMeshComponent | EAvaDynamicMeshConverterModifierType::BrushComponent | EAvaDynamicMeshConverterModifierType::ProceduralMeshComponent);` — `UPROPERTY(EditInstanceOnly, Setter="SetComponentType", Getter="GetComponentType", Category="DynamicMeshConverter", meta=(Bitmask, BitmaskEnum="/Script/AvalancheModifiers.EAvaDynamicMeshConverterModifierType", AllowPrivateAccess="true"))` — Which components should we take into account for the conversion
- L226 _protected member_ `EAvaDynamicMeshConverterModifierFilter FilterActorMode = EAvaDynamicMeshConverterModifierFilter::None;` — `UPROPERTY(EditInstanceOnly, Setter="SetFilterActorMode", Getter="GetFilterActorMode", Category="DynamicMeshConverter", meta=(AllowPrivateAccess="true"))` — Actor filter mode : none, include or exclude specific actor class
- L230 _protected member_ `TSet<TSubclassOf<AActor>> FilterActorClasses;` — `UPROPERTY(EditInstanceOnly, Setter="SetFilterActorClasses", Getter="GetFilterActorClasses", Category="DynamicMeshConverter", meta=(EditCondition="FilterActorMode != EAvaDynamicMeshConverterModifierFilter::None", AllowPrivateAccess="true"))` — Actor class to use as filter when gathering actors to convert
- L234 _protected member_ `bool bIncludeAttachedActors = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetIncludeAttachedActors", Getter="GetIncludeAttachedActors", Category="DynamicMeshConverter", meta=(AllowPrivateAccess="true"))` — Checks and convert all attached actors below this actor
- L238 _protected member_ `bool bHideConvertedMesh = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetHideConvertedMesh", Getter="GetHideConvertedMesh", Category="DynamicMeshConverter", meta=(AllowPrivateAccess="true"))` — Change visibility of source mesh once they are converted to dynamic mesh, by default will convert itself so hide converted mesh is true
- L242 _protected member_ `float UpdateInterval = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="DynamicMeshConverter", meta=(ClampMin="0.0"))` — Update interval to compare if a transform/material has changed in converted components, when value <= 0 then skipped
- L246 _protected member_ `bool bComponentCreated = false;` — `UPROPERTY()` — Did we create the dynamic mesh component from this modifier or retrieved it
- L250 _protected member_ `TSet<FAvaDynamicMeshConverterModifierComponentState> ConvertedComponents;` — `UPROPERTY()` — Components converted to dynamic mesh
- L253 _protected member_ `FCEMeshBuilder MeshBuilder;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)`
- L255 _protected member_ `FActorModifierSceneTreeActor TrackedActor;`
- L258 _protected member_ `double LastTransformUpdateTime = 0;` — Time elasped since

#### Free symbols / members of external scopes

- L31 _prototype_ `ENUM_CLASS_FLAGS(EAvaDynamicMeshConverterModifierType);`
- L51 _function_ `friend uint32 GetTypeHash(const FAvaDynamicMeshConverterModifierComponentState& InItem)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaExtrudeModifier.h` (Public)


#### enum `EAvaExtrudeMode`  
`enum class EAvaExtrudeMode : uint8`  
_L9-14_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Opposite`
- L12 _public enumerator_ `Front`
- L13 _public enumerator_ `Symmetrical`

#### class `UAvaExtrudeModifier`  
`class UAvaExtrudeModifier : public UAvaGeometryBaseModifier`  
_L18-86_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- desc: This modifier extrude triangles from a 2D shape with a specific depth and optionally closes the back
- L23 _public member_ `static inline const FName ExtrudePolygroupLayerName = TEXT("Ext`
- L24 _public member_ `static inline const FName BackPolygroupLayerName = TEXT("Ext`
- L27 _public prototype_ `void SetDepth(float InDepth);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Extrude")`
- L30 _public function_ `float GetDepth() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Extrude")`
- L36 _public prototype_ `void SetCloseBack(bool bInCloseBack);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Extrude")`
- L39 _public function_ `bool GetCloseBack() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Extrude")`
- L45 _public prototype_ `void SetExtrudeMode(EAvaExtrudeMode InExtrudeMode);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Extrude")`
- L48 _public function_ `EAvaExtrudeMode GetExtrudeMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Extrude")`
- L55 _protected prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L57 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L62 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L63 _protected prototype_ `virtual void Apply() override;`
- L66 _protected prototype_ `void OnDepthChanged();`
- L67 _protected prototype_ `void OnCloseBackChanged();`
- L68 _protected prototype_ `void OnExtrudeModeChanged();`
- L69 _protected prototype_ `FVector GetExtrudeDirection() const;`
- L73 _protected member_ `float Depth = 30.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetDepth", Getter="GetDepth", Category="Extrude", meta=(ClampMin="0", DisplayName="Extrude Depth", Units="Centimeters", AllowPrivateAccess="true"))` — Handles mesh depth to extrude primary section
- L77 _protected member_ `bool bCloseBack = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetCloseBack", Getter="GetCloseBack", Category="Extrude", meta=(AllowPrivateAccess="true"))` — Closes the back of the extrude for a 2D shape for example
- L81 _protected member_ `bool bMoveMeshOppositeDirection_DEPRECATED = true;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ExtrudeMode instead"))` — Moves the mesh in the opposite extrude direction by the depth distance
- L85 _protected member_ `EAvaExtrudeMode ExtrudeMode = EAvaExtrudeMode::Opposite;` — `UPROPERTY(EditInstanceOnly, Setter="SetExtrudeMode", Getter="GetExtrudeMode", Category="Extrude", meta=(AllowPrivateAccess="true"))` — Specifies the Extrude direction

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaGeometryBaseModifier.h` (Public)


#### class `UAvaGeometryBaseModifier`  
`class UAvaGeometryBaseModifier : public UActorModifierCoreBase`  
_L17-59_
- reflection: `UCLASS(Abstract)`
- inherits: `UActorModifierCoreBase`
- desc: Base class used for geometry modifier that uses dynamic mesh components
- L25 _public prototype_ `static UE::Geometry::FDynamicMeshPolygroupAttribute* FindOrCreatePolygroupLayer(UE::Geometry::FDynamicMesh3& EditMesh, const FName& InLayerName, TArray<int32>* GroupTriangles = nullptr);` — Get polygroup layer by name
- L29 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L30 _protected prototype_ `virtual bool IsModifierReady() const override;`
- L31 _protected prototype_ `virtual void SavePreState() override;`
- L32 _protected prototype_ `virtual void RestorePreState() override;`
- L33 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L34 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L37 _protected prototype_ `void OnMeshChanged();`
- L40 _protected prototype_ `UDynamicMeshComponent* GetMeshComponent() const;` — Gets the cached dynamic mesh component. If null, find the first attached and caches it
- L43 _protected prototype_ `UDynamicMesh* GetMeshObject() const;` — Gets the dynamic mesh object from the cached mesh component
- L46 _protected prototype_ `bool IsMeshValid() const;` — Checks if the dynamic mesh component is valid
- L49 _protected prototype_ `FBox GetMeshBounds() const;` — Get dynamic mesh bounds
- L52 _protected member_ `TOptional<UE::Geometry::FDynamicMesh3> PreModifierCachedMesh;` — Cached Mesh to restore to the Pre-Modifier State
- L53 _protected member_ `TOptional<FBox> PreModifierCachedBounds;`
- L58 _private member_ `TWeakObjectPtr<UDynamicMeshComponent> MeshComponent = nullptr;` — `UPROPERTY(DuplicateTransient)` — The actor dynamic mesh component

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaGlobalOpacityModifier.h` (Public)


#### class `UAvaGlobalOpacityModifier`  
`class UAvaGlobalOpacityModifier : public UAvaMaterialParameterModifier`  
_L13-53_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaMaterialParameterModifier`
- desc: This modifier sets global opacity parameters on an actor with Material Designer Instances generated with the Material Designer
- L18 _public prototype_ `UAvaGlobalOpacityModifier();`
- L21 _public prototype_ `void SetGlobalOpacity(float InOpacity);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|GlobalOpacity")`
- L24 _public function_ `float GetGlobalOpacity() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|GlobalOpacity")`
- L32 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L37 _protected prototype_ `virtual void Apply() override;`
- L38 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L41 _protected prototype_ `void OnGlobalOpacityChanged();`
- L43 _protected prototype_ `virtual void OnActorMaterialAdded(UMaterialInstanceDynamic* InAdded) override;`
- L44 _protected prototype_ `virtual void OnActorMaterialRemoved(UMaterialInstanceDynamic* InRemoved) override;`
- L45 _protected prototype_ `void OnDynamicMaterialValueChanged(UDMMaterialComponent* InComponent, UDMMaterialComponent* InSource, EDMUpdateType InUpdateType);`
- L49 _protected member_ `float GlobalOpacity = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetGlobalOpacity", Getter="GetGlobalOpacity", Category="Material Parameter", meta=(ClampMin="0", ClampMax="1", AllowPrivateAccess="true"))` — Global opacity to set on all Material Designer Instances
- L52 _protected member_ `int32 SupportedOpacityMaterialCount = 0;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaHideEmptyModifier.h` (Public)


#### class `UAvaHideEmptyModifier`  
`class UAvaHideEmptyModifier : public UActorModifierArrangeBaseModifier`  
_L11-80_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierArrangeBaseModifier`
- L17 _public function_ `void SetContainerActor(AActor* InActor)` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|HideEmpty")`
- L23 _public function_ `AActor* GetContainerActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|HideEmpty")`
- L28 _public prototype_ `void SetContainerActorWeak(TWeakObjectPtr<AActor> InContainer);`
- L29 _public function_ `TWeakObjectPtr<AActor> GetContainerActorWeak() const`
- L35 _public prototype_ `void SetInvertVisibility(bool bInInvert);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|HideEmpty")`
- L38 _public function_ `bool GetInvertVisibility() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|HideEmpty")`
- L46 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L51 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L52 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L53 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L54 _protected prototype_ `virtual void Apply() override;`
- L55 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L56 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L59 _protected prototype_ `void OnTextChanged();`
- L60 _protected prototype_ `void OnContainerActorChanged();`
- L61 _protected prototype_ `void OnInvertVisibilityChanged();`
- L64 _protected prototype_ `virtual void OnSceneTreeTrackedActorChanged(int32 InIdx, AActor* InPreviousActor, AActor* InNewActor) override;`
- L65 _protected prototype_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L70 _protected member_ `TWeakObjectPtr<AActor> ContainerActorWeak;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="HideEmpty", meta=(DisplayName="ContainerActor", AllowPrivateAccess="true"))` — The container to hide when text is empty, by default self
- L74 _protected member_ `bool bInvertVisibility = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetInvertVisibility", Getter="GetInvertVisibility", Category="HideEmpty", meta=(AllowPrivateAccess="true"))` — Invert the behaviour and visibility of the container if text is empty
- L79 _private member_ `TWeakObjectPtr<UText3DComponent> TextComponent;` — `UPROPERTY()` — Cached text component

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaMaterialParameterModifier.h` (Public)


#### struct `FAvaMaterialParameterMapScalar`  
`struct FAvaMaterialParameterMapScalar`  
_L14-23_
- reflection: `USTRUCT(BlueprintType)`
- L19 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter")`
- L22 _public member_ `float Value = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter")`

#### struct `FAvaMaterialParameterMapVector`  
`struct FAvaMaterialParameterMapVector`  
_L26-35_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter")`
- L34 _public member_ `FLinearColor Value = FLinearColor::Black;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter")`

#### struct `FAvaMaterialParameterMapTexture`  
`struct FAvaMaterialParameterMapTexture`  
_L38-47_
- reflection: `USTRUCT(BlueprintType)`
- L43 _public member_ `FName Name = NAME_None;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter")`
- L46 _public member_ `TObjectPtr<UTexture> Value = nullptr;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter")`

#### struct `FAvaMaterialParameterMap`  
`struct FAvaMaterialParameterMap`  
_L50-121_
- reflection: `USTRUCT(BlueprintType)`
- L57 _public prototype_ `FAvaMaterialParameterMap() = default;`
- L58 _public prototype_ `FAvaMaterialParameterMap(const FAvaMaterialParameterMap&) = default;`
- L59 _public prototype_ `FAvaMaterialParameterMap(FAvaMaterialParameterMap&&) = default;`
- L60 _public prototype_ `FAvaMaterialParameterMap& operator=(const FAvaMaterialParameterMap&) = default;`
- L61 _public prototype_ `FAvaMaterialParameterMap& operator=(FAvaMaterialParameterMap&&) = default;`
- L65 _public prototype_ `void MatchKeys(const FAvaMaterialParameterMap& InParameterMap);` — Matches the input parameter key map and removes all unused keys, does not touch current values
- L68 _public prototype_ `void PushParametersTo(UMaterialInstanceDynamic* InMaterial);` — Apply our parameters to this Material Designer Instance
- L71 _public prototype_ `void PullParametersFrom(UMaterialInstanceDynamic* InMaterial);` — Read parameters from this Material Designer Instance and save them here.
- L74 _public prototype_ `const FAvaMaterialParameterMapScalar* FindScalarParameter(FName InParameterName) const;` — Returns the scalar parameter struct with the given name.
- L77 _public prototype_ `FAvaMaterialParameterMapScalar* FindScalarParameter(FName InParameterName, bool bInCreateIfMissing = false);` — Returns the scalar parameter struct with the given name, potentially creating it if it doesn't exist.
- L80 _public prototype_ `const FAvaMaterialParameterMapVector* FindVectorParameter(FName InParameterName) const;` — Returns the vector parameter struct with the given name.
- L83 _public prototype_ `FAvaMaterialParameterMapVector* FindVectorParameter(FName InParameterName, bool bInCreateIfMissing = false);` — Returns the vector parameter struct with the given name, potentially creating it if it doesn't exist.
- L86 _public prototype_ `const FAvaMaterialParameterMapTexture* FindTextureParameter(FName InParameterName) const;` — Returns the texture parameter struct with the given name.
- L89 _public prototype_ `FAvaMaterialParameterMapTexture* FindTextureParameter(FName InParameterName, bool bInCreateIfMissing = false);` — Returns the texture parameter struct with the given name, potentially creating it if it doesn't exist.
- L93 _private prototype_ `void UpdateDeprecatedParameterProperties();`
- L98 _private member_ `TArray<FAvaMaterialParameterMapScalar> ScalarParameterStructs;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter", meta = (DisplayName = "Scalar Parameters", AllowPrivateAccess, TitleProperty = "Name", ShowOnlyInnerProperties))`
- L102 _private member_ `TArray<FAvaMaterialParameterMapVector> VectorParameterStructs;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter", meta = (DisplayName = "Vector Parameters", AllowPrivateAccess, TitleProperty = "Name", ShowOnlyInnerProperties))`
- L106 _private member_ `TArray<FAvaMaterialParameterMapTexture> TextureParameterStructs;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "MaterialParameter", meta = (DisplayName = "Texture Parameters", AllowPrivateAccess, TitleProperty = "Name", ShowOnlyInnerProperties))`
- L111 _private member_ `TMap<FName, float> ScalarParameters_DEPRECATED;` — `UE_DEPRECATED(5.7, "ScalarParameters has been deprecated. Please use ScalarParameterStructs")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been refactored to use an array and struct, instead of a map."))`
- L115 _private member_ `TMap<FName, FLinearColor> VectorParameters_DEPRECATED;` — `UE_DEPRECATED(5.7, "VectorParameters has been deprecated. Please use VectorParameterStructs")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been refactored to use an array and struct, instead of a map."))`
- L119 _private member_ `TMap<FName, TObjectPtr<UTexture>> TextureParameters_DEPRECATED;` — `UE_DEPRECATED(5.7, "TextureParameters has been deprecated. Please use TextureParameterStructs")` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "This property has been refactored to use an array and struct, instead of a map."))`

#### class `UAvaMaterialParameterModifier`  
`class UAvaMaterialParameterModifier : public UActorModifierArrangeBaseModifier`  
_L125-223_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierArrangeBaseModifier`
- desc: This modifier sets specified dynamic materials parameters on an actor and its children
- L130 _public prototype_ `UAvaMaterialParameterModifier();`
- L133 _public prototype_ `void SetMaterialParameters(const FAvaMaterialParameterMap& InParameterMap);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|MaterialParameter")`
- L136 _public function_ `const FAvaMaterialParameterMap& GetMaterialParameters() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|MaterialParameter")`
- L142 _public prototype_ `void SetUpdateChildren(bool bInUpdateChildren);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|MaterialParameter")`
- L145 _public function_ `bool GetUpdateChildren() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|MaterialParameter")`
- L153 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L154 _protected prototype_ `virtual void PostLoad() override;`
- L159 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L160 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L161 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L162 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L163 _protected prototype_ `virtual void RestorePreState() override;`
- L164 _protected prototype_ `virtual void SavePreState() override;`
- L165 _protected prototype_ `virtual void Apply() override;`
- L169 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L170 _protected prototype_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L174 _protected prototype_ `void SaveMaterialParameters();` — Read and save original values
- L176 _protected prototype_ `void RestoreMaterialParameters();` — Write and restore original values
- L180 _protected prototype_ `virtual void OnActorPropertyChanged(UObject* InObject, FPropertyChangedEvent& InChangeEvent);` — Called when a property changes, used to detect material changes
- L183 _protected prototype_ `void ScanActorMaterials();`
- L185 _protected prototype_ `void OnMaterialParametersChanged();`
- L186 _protected prototype_ `void OnUpdateChildrenChanged();`
- L188 _protected function_ `virtual void OnActorMaterialAdded(UMaterialInstanceDynamic* InAdded)`
- L189 _protected function_ `virtual void OnActorMaterialRemoved(UMaterialInstanceDynamic* InRemoved)`
- L192 _protected prototype_ `bool IsActorSupported(const AActor* InActor) const;` — Checks if this actor has a Material Designer Instance or that we already track one
- L195 _protected prototype_ `TSet<UMaterialInstanceDynamic*> GetComponentDynamicMaterials(const UPrimitiveComponent* InComponent) const;` — Retrieves all Material Designer Instance from a primitive component
- L199 _protected member_ `FAvaMaterialParameterMap MaterialParameters;` — `UPROPERTY(EditInstanceOnly, Setter="SetMaterialParameters", Getter="GetMaterialParameters", Category="MaterialParameter", meta=(HideEditConditionToggle, EditCondition="bShowMaterialParameters", EditConditionHides, AllowPrivateAccess="true"))` — Which parameters should we set on the Material Designer Instance
- L203 _protected member_ `TMap<TWeakObjectPtr<UMaterialInstanceDynamic>, FAvaMaterialParameterMap> SavedMaterialParameters;` — `UPROPERTY()` — Used to restore Material Designer Instance parameters to their original state
- L207 _protected member_ `TSubclassOf<UMaterialInstanceDynamic> MaterialClass;` — `UPROPERTY(Transient)` — Filter material type for child modifiers
- L211 _protected member_ `bool bUpdateChildren = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetUpdateChildren", Getter="GetUpdateChildren", Category="MaterialParameter", meta=(AllowPrivateAccess="true"))` — Will also look into attached children actors
- L216 _protected member_ `bool bShowMaterialParameters = true;` — `UPROPERTY(Transient)` — Used by child classes to override MaterialParameters
- L221 _private prototype_ `void UpdateDeprecatedParameterProperties();`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaMirrorModifier.h` (Public)


#### class `UAvaMirrorModifier`  
`class UAvaMirrorModifier : public UAvaGeometryBaseModifier`  
_L12-111_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- L18 _public prototype_ `void SetMirrorFramePosition(const FVector& InMirrorFramePosition);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Mirror")`
- L21 _public function_ `const FVector& GetMirrorFramePosition() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Mirror")`
- L27 _public prototype_ `void SetMirrorFrameRotation(const FRotator& InMirrorFrameRotation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Mirror")`
- L30 _public function_ `const FRotator& GetMirrorFrameRotation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Mirror")`
- L36 _public prototype_ `void SetApplyPlaneCut(bool bInApplyPlaneCut);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Mirror")`
- L39 _public function_ `bool GetApplyPlaneCut() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Mirror")`
- L45 _public prototype_ `void SetFlipCutSide(bool bInFlipCutSide);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Mirror")`
- L48 _public function_ `bool GetFlipCutSide() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Mirror")`
- L54 _public prototype_ `void SetWeldAlongPlane(bool bInWeldAlongPlane);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Mirror")`
- L57 _public function_ `bool GetWeldAlongPlane() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Mirror")`
- L65 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L70 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L71 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L72 _protected prototype_ `virtual void Apply() override;`
- L73 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L74 _protected prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;`
- L77 _protected prototype_ `void OnMirrorFrameChanged();`
- L78 _protected prototype_ `void OnMirrorOptionChanged();`
- L81 _protected prototype_ `void CreatePreviewComponent();`
- L82 _protected prototype_ `void DestroyPreviewComponent();`
- L83 _protected prototype_ `void UpdatePreviewComponent();`
- L85 _protected prototype_ `void OnShowMirrorFrameChanged();`
- L89 _protected member_ `FVector MirrorFramePosition = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter="SetMirrorFramePosition", Getter="GetMirrorFramePosition", Category="Mirror", meta=(AllowPrivateAccess="true"))`
- L92 _protected member_ `FRotator MirrorFrameRotation = FRotator(0, 0, 90);` — `UPROPERTY(EditInstanceOnly, Setter="SetMirrorFrameRotation", Getter="GetMirrorFrameRotation", Category="Mirror", meta=(AllowPrivateAccess="true"))`
- L95 _protected member_ `bool bApplyPlaneCut = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetApplyPlaneCut", Getter="GetApplyPlaneCut", Category="Mirror", meta=(AllowPrivateAccess="true"))`
- L98 _protected member_ `bool bFlipCutSide = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetFlipCutSide", Getter="GetFlipCutSide", Category="Mirror", meta=(AllowPrivateAccess="true"))`
- L101 _protected member_ `bool bWeldAlongPlane = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetWeldAlongPlane", Getter="GetWeldAlongPlane", Category="Mirror", meta=(AllowPrivateAccess="true"))`
- L105 _protected member_ `bool bShowMirrorFrame = false;` — `UPROPERTY(EditInstanceOnly, Category="Mirror", meta=(AllowPrivateAccess="true"))`
- L109 _private member_ `FAvaModifierPreviewPlane PreviewPlane;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaNormalModifier.h` (Public)


#### enum `EAvaNormalModifierSplitMethod`  
`enum class EAvaNormalModifierSplitMethod : uint8`  
_L9-21_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `None` — Do not split, leave as it is
- L14 _public enumerator_ `Vertex` — Each vertex will have a split normal between tris
- L16 _public enumerator_ `Triangle` — Shared vertex between triangles will have a split normal
- L18 _public enumerator_ `PolyGroup` — Vertices of a same face grouped together will have a split normal
- L20 _public enumerator_ `Threshold` — Vertices above a certain angle threshold will have a split normal

#### class `UAvaNormalModifier`  
`class UAvaNormalModifier : public UAvaGeometryBaseModifier`  
_L24-133_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- L30 _public prototype_ `void SetAngleWeighted(bool bInAngleWeighted);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Normal")`
- L33 _public function_ `bool GetAngleWeighted() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Normal")`
- L39 _public prototype_ `void SetAreaWeighted(bool bInAreaWeighted);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Normal")`
- L42 _public function_ `bool GetAreaWeighted() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Normal")`
- L48 _public prototype_ `void SetInvert(bool bInInvert);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Normal")`
- L51 _public function_ `bool GetInvert() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Normal")`
- L57 _public prototype_ `void SetSplitMethod(EAvaNormalModifierSplitMethod InSplitMethod);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Normal")`
- L60 _public function_ `EAvaNormalModifierSplitMethod GetSplitMethod() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Normal")`
- L66 _public prototype_ `void SetAngleThreshold(float InAngleThreshold);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Normal")`
- L69 _public function_ `float GetAngleThreshold() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Normal")`
- L75 _public prototype_ `void SetPolyGroupLayerIdx(int32 InPolyGroupLayer);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Normal")`
- L78 _public prototype_ `int32 GetPolyGroupLayerIdx() const;` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Normal")`
- L80 _public prototype_ `void SetPolyGroupLayer(const FString& InPolyGroupLayer);`
- L82 _public function_ `FString GetPolyGroupLayer() const`
- L90 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L95 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L96 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L97 _protected prototype_ `virtual void Apply() override;`
- L100 _protected prototype_ `void OnAngleWeightedChanged();`
- L101 _protected prototype_ `void OnAreaWeightedChanged();`
- L102 _protected prototype_ `void OnInvertChanged();`
- L103 _protected prototype_ `void OnSplitMethodChanged();`
- L104 _protected prototype_ `void OnAngleThresholdChanged();`
- L105 _protected prototype_ `void OnPolyGroupLayerChanged();`
- L108 _protected prototype_ `TArray<FString> GetPolyGroupLayers() const;` — `UFUNCTION()`
- L112 _protected member_ `bool bAngleWeighted = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetAngleWeighted", Getter="GetAngleWeighted", Category="Normal", meta=(AllowPrivateAccess="true"))` — Recompute normals and weight them by angle
- L116 _protected member_ `bool bAreaWeighted = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetAreaWeighted", Getter="GetAreaWeighted", Category="Normal", meta=(AllowPrivateAccess="true"))` — Recompute normals and weight them by area
- L120 _protected member_ `bool bInvert = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetInvert", Getter="GetInvert", Category="Normal", meta=(AllowPrivateAccess="true"))` — Recompute normals and invert normals and triangles
- L124 _protected member_ `EAvaNormalModifierSplitMethod SplitMethod = EAvaNormalModifierSplitMethod::Threshold;` — `UPROPERTY(EditInstanceOnly, Setter="SetSplitMethod", Getter="GetSplitMethod", Category="Normal", meta=(AllowPrivateAccess="true"))` — Recompute normals and use a split method
- L128 _protected member_ `float AngleThreshold = 60.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetAngleThreshold", Getter="GetAngleThreshold", Category="Normal", meta=(ClampMin="0.0", ClampMax="180.0", EditCondition="SplitMethod == EAvaNormalModifierSplitMethod::Threshold", AllowPrivateAccess="true"))` — Angle to compare and split normal when threshold method is chosen
- L132 _protected member_ `FString PolyGroupLayer = TEXT("Non` — `UPROPERTY(EditInstanceOnly, Setter="SetPolyGroupLayer", Getter="GetPolyGroupLayer", Category="Normal", meta=(GetOptions="GetPolyGroupLayers", EditCondition="SplitMethod == EAvaNormalModifierSplitMethod::PolyGroup", AllowPrivateAccess="true"))` — PolyGroup to use to split normal from when PolyGroup method is chosen

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaOutlineModifier.h` (Public)


#### enum `EAvaOutlineMode`  
`enum class EAvaOutlineMode : uint8`  
_L9-13_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Outset`
- L12 _public enumerator_ `Inset`

#### class `UAvaOutlineModifier`  
`class UAvaOutlineModifier : public UAvaGeometryBaseModifier`  
_L17-78_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- desc: This modifier adds an outline around a 2D shape with a specific distance
- L23 _public prototype_ `void SetMode(EAvaOutlineMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Outline")`
- L26 _public function_ `EAvaOutlineMode GetMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Outline")`
- L32 _public prototype_ `void SetDistance(float InDistance);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Outline")`
- L35 _public function_ `float GetDistance() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Outline")`
- L41 _public prototype_ `void SetRemoveInside(bool bInRemoveInside);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Outline")`
- L44 _public function_ `bool GetRemoveInside() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Outline")`
- L52 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L57 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L58 _protected prototype_ `virtual void Apply() override;`
- L61 _protected prototype_ `void OnModeChanged();`
- L62 _protected prototype_ `void OnDistanceChanged();`
- L63 _protected prototype_ `void OnRemoveInsideChanged();`
- L65 _protected prototype_ `float GetMaxInsetDistance() const;`
- L69 _protected member_ `EAvaOutlineMode Mode = EAvaOutlineMode::Outset;` — `UPROPERTY(EditInstanceOnly, Setter="SetMode", Getter="GetMode", Category="Outline", meta=(AllowPrivateAccess="true"))` — Set the mode like inset or outset
- L73 _protected member_ `float Distance = 10.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetDistance", Getter="GetDistance", Category="Outline", meta=(ClampMin="0", AllowPrivateAccess="true"))` — Set the distance for the outline
- L77 _protected member_ `bool bRemoveInside = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetRemoveInside", Getter="GetRemoveInside", Category="Outline", meta=(AllowPrivateAccess="true"))` — Remove the inside part and create a hole in the shape

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaPatternModifier.h` (Public)


#### enum `EAvaPatternModifierLayout`  
`enum class EAvaPatternModifierLayout : uint8`  
_L11-16_
- reflection: `UENUM(BlueprintType)`
- L13 _public enumerator_ `Line = 0`
- L14 _public enumerator_ `Grid = 1`
- L15 _public enumerator_ `Circle = 2`

#### enum `EAvaPatternModifierAxis`  
`enum class EAvaPatternModifierAxis : uint8`  
_L19-24_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `X = 0`
- L22 _public enumerator_ `Y = 1`
- L23 _public enumerator_ `Z = 2`

#### enum `EAvaPatternModifierPlane`  
`enum class EAvaPatternModifierPlane : uint8`  
_L27-32_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `XY = 0`
- L30 _public enumerator_ `ZX = 1`
- L31 _public enumerator_ `YZ = 2`

#### enum `EAvaPatternModifierLineAlignment`  
`enum class EAvaPatternModifierLineAlignment : uint8`  
_L35-40_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `Start`
- L38 _public enumerator_ `Center`
- L39 _public enumerator_ `End`

#### enum `EAvaPatternModifierGridAlignment`  
`enum class EAvaPatternModifierGridAlignment : uint8`  
_L43-50_
- reflection: `UENUM(BlueprintType)`
- L45 _public enumerator_ `TopLeft`
- L46 _public enumerator_ `TopRight`
- L47 _public enumerator_ `Center`
- L48 _public enumerator_ `BottomLeft`
- L49 _public enumerator_ `BottomRight`

#### struct `FVector2b`  
`struct FVector2b`  
_L53-62_
- reflection: `USTRUCT(BlueprintType)`
- L58 _public member_ `bool bX = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Values")`
- L61 _public member_ `bool bY = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Values")`

#### struct `FAvaPatternModifierLineLayoutOptions`  
`struct FAvaPatternModifierLineLayoutOptions`  
_L65-93_
- reflection: `USTRUCT(BlueprintType)`
- L70 _public member_ `EAvaPatternModifierAxis Axis = EAvaPatternModifierAxis::Y;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L73 _public member_ `bool bAxisInverted = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L76 _public member_ `int32 RepeatCount = 4;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern", meta=(ClampMin="1"))`
- L79 _public member_ `float Spacing = 0.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L83 _public member_ `bool bCentered = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")` — Center the layout based on the axis
- L86 _public member_ `bool bAccumulateTransform = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L89 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L92 _public member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`

#### struct `FAvaPatternModifierGridLayoutOptions`  
`struct FAvaPatternModifierGridLayoutOptions`  
_L96-124_
- reflection: `USTRUCT(BlueprintType)`
- L101 _public member_ `EAvaPatternModifierPlane Plane = EAvaPatternModifierPlane::YZ;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L104 _public member_ `FVector2b AxisInverted;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L107 _public member_ `FIntPoint RepeatCount = FIntPoint(2, 2);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern", meta=(ClampMin="1"))` — Row, Column
- L110 _public member_ `FVector2D Spacing = FVector2D(0.f);` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L114 _public member_ `bool bCentered = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")` — Center the layout based on the plane
- L117 _public member_ `bool bAccumulateTransform = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L120 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L123 _public member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`

#### struct `FAvaPatternModifierCircleLayoutOptions`  
`struct FAvaPatternModifierCircleLayoutOptions`  
_L127-158_
- reflection: `USTRUCT(BlueprintType)`
- L132 _public member_ `EAvaPatternModifierPlane Plane = EAvaPatternModifierPlane::YZ;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L135 _public member_ `float Radius = 100.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L138 _public member_ `float StartAngle = 180.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L141 _public member_ `float FullAngle = 360.f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L144 _public member_ `int32 RepeatCount = 4;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern", meta=(ClampMin="1"))`
- L148 _public member_ `bool bCentered = true;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")` — Center the layout based on the plane
- L151 _public member_ `bool bAccumulateTransform = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L154 _public member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`
- L157 _public member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Pattern")`

#### class `UAvaPatternModifier`  
`class UAvaPatternModifier : public UAvaGeometryBaseModifier`  
_L162-233_
- reflection: `UCLASS(MinimalAPI, BlueprintType, AutoExpandCategories=(Pattern))`
- inherits: `UAvaGeometryBaseModifier`
- desc: This modifier clones a shape following various layouts and options
- L167 _public prototype_ `UAvaPatternModifier();`
- L170 _public prototype_ `void SetActiveToolClass(const TSubclassOf<UAvaPatternModifierTool>& InClass);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L173 _public function_ `TSubclassOf<UAvaPatternModifierTool> GetActiveToolClass() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L180 _protected prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L182 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L187 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L188 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L189 _protected prototype_ `virtual void Apply() override;`
- L193 _protected prototype_ `UAvaPatternModifierTool* FindOrAddTool(TSubclassOf<UAvaPatternModifierTool> InToolClass);` — Finds saved tool or create and saves it
- L196 _protected function_ `template<typename InToolClass> InToolClass* FindOrAddTool()`
- L201 _protected prototype_ `void OnActiveToolClassChanged();`
- L204 _protected member_ `TSubclassOf<UAvaPatternModifierTool> ActiveToolClass;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", NoClear, meta=(ShowDisplayNames, AllowPrivateAccess="true"))`
- L207 _protected member_ `TObjectPtr<UAvaPatternModifierTool> ActiveTool;` — `UPROPERTY(VisibleInstanceOnly, Instanced, Category="Pattern", Transient, TextExportTransient, DuplicateTransient)`
- L210 _protected member_ `TArray<TObjectPtr<UAvaPatternModifierTool>> Tools;` — `UPROPERTY()`
- L213 _private prototype_ `void MigrateVersion(int32 InCurrentVersion);`
- L217 _private member_ `EAvaPatternModifierLayout Layout = EAvaPatternModifierLayout::Line;` — `UE_DEPRECATED(5.6, "Moved to ToolName")` — `UPROPERTY()`
- L221 _private member_ `FAvaPatternModifierLineLayoutOptions LineLayoutOptions;` — `UE_DEPRECATED(5.6, "Moved to Line Tool")` — `UPROPERTY()`
- L225 _private member_ `FAvaPatternModifierGridLayoutOptions GridLayoutOptions;` — `UE_DEPRECATED(5.6, "Moved to Grid Tool")` — `UPROPERTY()`
- L229 _private member_ `FAvaPatternModifierCircleLayoutOptions CircleLayoutOptions;` — `UE_DEPRECATED(5.6, "Moved to Circle Tool")` — `UPROPERTY()`
- L232 _private member_ `FBox OriginalMeshBounds;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaPlaneCutModifier.h` (Public)


#### class `UAvaPlaneCutModifier`  
`class UAvaPlaneCutModifier : public UAvaGeometryBaseModifier`  
_L11-102_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- desc: This modifier cuts a shape based on a 2D plane
- L17 _public prototype_ `void SetPlaneOrigin(float InOrigin);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|PlaneCut")`
- L20 _public function_ `float GetPlaneOrigin() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|PlaneCut")`
- L26 _public prototype_ `void SetPlaneRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|PlaneCut")`
- L29 _public function_ `const FRotator& GetPlaneRotation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|PlaneCut")`
- L35 _public prototype_ `void SetInvertCut(bool bInInvertCut);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|PlaneCut")`
- L38 _public function_ `bool GetInvertCut() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|PlaneCut")`
- L44 _public prototype_ `void SetFillHoles(bool bInFillHoles);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|PlaneCut")`
- L47 _public function_ `bool GetFillHoles() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|PlaneCut")`
- L55 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L60 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L61 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L62 _protected prototype_ `virtual void Apply() override;`
- L63 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L64 _protected prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;`
- L68 _protected prototype_ `FVector GetPlaneLocation() const;` — Returns actual location of plane bounds restricted
- L70 _protected prototype_ `void OnPlaneRotationChanged();`
- L71 _protected prototype_ `void OnFillHolesChanged();`
- L72 _protected prototype_ `void OnInvertCutChanged();`
- L73 _protected prototype_ `void OnPlaneOriginChanged();`
- L76 _protected prototype_ `void OnUsePreviewChanged();`
- L77 _protected prototype_ `void CreatePreviewComponent();`
- L78 _protected prototype_ `void DestroyPreviewComponent();`
- L79 _protected prototype_ `void UpdatePreviewComponent();`
- L83 _protected member_ `float PlaneOrigin = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetPlaneOrigin", Getter="GetPlaneOrigin", Category="PlaneCut", meta=(Delta="0.5", LinearDeltaSensitivity="1", AllowPrivateAccess="true"))`
- L86 _protected member_ `FRotator PlaneRotation = FRotator(0, 0, 90);` — `UPROPERTY(EditInstanceOnly, Setter="SetPlaneRotation", Getter="GetPlaneRotation", Category="PlaneCut", meta=(AllowPrivateAccess="true"))`
- L89 _protected member_ `bool bInvertCut = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetInvertCut", Getter="GetInvertCut", Category="PlaneCut", meta=(AllowPrivateAccess="true"))`
- L92 _protected member_ `bool bFillHoles = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetFillHoles", Getter="GetFillHoles", Category="PlaneCut", meta=(AllowPrivateAccess="true"))`
- L96 _protected member_ `bool bUsePreview = false;` — `UPROPERTY(EditInstanceOnly, Category="PlaneCut", meta=(AllowPrivateAccess="true"))`
- L100 _private member_ `FAvaModifierPreviewPlane PreviewPlane;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaSizeToTextureModifier.h` (Public)


#### enum `EAvaSizeToTextureRule`  
`enum class EAvaSizeToTextureRule : uint8`  
_L15-29_
- reflection: `UENUM()`
- L20 _public enumerator_ `AdaptiveWidth` — Automatically adapts the width based on the height, to maintain texture ratio
- L24 _public enumerator_ `AdaptiveHeight` — Automatically adapts the height based on the width, to maintain texture ratio
- L26 _public enumerator_ `FixedHeight UMETA(Hidden)` — Lock height and adapt width
- L28 _public enumerator_ `FixedWidth UMETA(Hidden)` — Lock width and adapt height

#### class `UAvaSizeToTextureModifier`  
`class UAvaSizeToTextureModifier : public UAvaGeometryBaseModifier , public IActorModifierRenderStateUpdateHandler`  
_L35-134_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier,IActorModifierRenderStateUpdateHandler`
- desc: Adapts the modified actor geometry size/scale to match the texture size/ratio
- L42 _public prototype_ `void SetTexture(UTexture* InTexture);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TextureSize")`
- L45 _public function_ `UTexture* GetTexture() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TextureSize")`
- L51 _public prototype_ `void SetRule(EAvaSizeToTextureRule InRule);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TextureSize")`
- L54 _public function_ `EAvaSizeToTextureRule GetRule() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TextureSize")`
- L60 _public prototype_ `void SetFixedHeight(float InFixedHeight);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TextureSize")`
- L63 _public function_ `float GetFixedHeight() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TextureSize")`
- L69 _public prototype_ `void SetFixedWidth(float InFixedWidth);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TextureSize")`
- L72 _public function_ `float GetFixedWidth() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TextureSize")`
- L80 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L85 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L86 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L87 _protected prototype_ `virtual void SavePreState() override;`
- L88 _protected prototype_ `virtual void RestorePreState() override;`
- L89 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L90 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L91 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L92 _protected prototype_ `virtual void Apply() override;`
- L96 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L97 _protected prototype_ `virtual void OnActorVisibilityChanged(AActor* InActor) override;`
- L100 _protected prototype_ `void OnTextureOptionsChanged();`
- L102 _protected prototype_ `void GetShapeSizeAndScale(FVector2D& OutShapeSize, FVector2D& OutShapeScale) const;`
- L103 _protected prototype_ `void CheckSizeOrScaleChanged();`
- L107 _protected member_ `TObjectPtr<UTexture> Texture;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="TextureSize", meta=(AllowPrivateAccess="true"))` — Texture to resize to
- L111 _protected member_ `EAvaSizeToTextureRule Rule = EAvaSizeToTextureRule::AdaptiveWidth;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="TextureSize", meta=(AllowPrivateAccess="true"))` — Rule for texture resize
- L115 _protected member_ `float FixedHeight = 512.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="TextureSize", meta=(ClampMin="0", EditCondition="Rule == EAvaSizeToTextureRule::FixedHeight", EditConditionHides, AllowPrivateAccess="true"))` — The fixed height size
- L119 _protected member_ `float FixedWidth = 512.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="TextureSize", meta=(ClampMin="0", EditCondition="Rule == EAvaSizeToTextureRule::FixedWidth", EditConditionHides, AllowPrivateAccess="true"))` — The fixed width size
- L123 _private member_ `FVector2D PreModifierShape2DSize = FVector2D::ZeroVector;` — `UPROPERTY()`
- L125 _private member_ `FVector2D CachedScale = FVector2D::ZeroVector;`
- L126 _private member_ `FVector2D CachedSize = FVector2D::ZeroVector;`
- L129 _private member_ `TWeakObjectPtr<UAvaShape2DDynMeshBase> Shape2DWeak;` — `UPROPERTY()`
- L132 _private member_ `static const TAvaPropertyChangeDispatcher<UAvaSizeToTextureModifier> PropertyChangeDispatcher;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaSplineSweepModifier.h` (Public)


#### enum `EAvaSplineSweepSampleMode`  
`enum class EAvaSplineSweepSampleMode : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `FullDistance` — Samples the full spline distance : steps on the full distance
- L18 _public enumerator_ `CustomDistance` — Samples a custom distance : steps per custom distance

#### class `UAvaSplineSweepModifier`  
`class UAvaSplineSweepModifier : public UAvaGeometryBaseModifier , public IActorModifierRenderStateUpdateHandler`  
_L22-218_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier,IActorModifierRenderStateUpdateHandler`
- L28 _public member_ `static constexpr int32 MaxSampleCount = 200;`
- L31 _public function_ `void SetSplineActor(AActor* InActor)` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L37 _public function_ `AActor* GetSplineActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L42 _public prototype_ `void SetSplineActorWeak(TWeakObjectPtr<AActor> InSplineActorWeak);`
- L43 _public function_ `TWeakObjectPtr<AActor> GetSplineActorWeak() const`
- L49 _public prototype_ `void SetSampleMode(EAvaSplineSweepSampleMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L52 _public function_ `EAvaSplineSweepSampleMode GetSampleMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L58 _public prototype_ `void SetSampleDistance(float InDistance);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L61 _public function_ `float GetSampleDistance() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L67 _public prototype_ `void SetSteps(int32 InSteps);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L70 _public function_ `int32 GetSteps() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L76 _public prototype_ `void SetProgressOffset(float InOffset);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L79 _public function_ `float GetProgressOffset() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L85 _public prototype_ `void SetProgressStart(float InStart);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L88 _public function_ `float GetProgressStart() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L94 _public prototype_ `void SetProgressEnd(float InEnd);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L97 _public function_ `float GetProgressEnd() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L103 _public prototype_ `void SetScaleStart(float InScaleStart);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L106 _public function_ `float GetScaleStart() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L112 _public prototype_ `void SetScaleEnd(float InScaleEnd);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L115 _public function_ `float GetScaleEnd() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L121 _public prototype_ `void SetCapped(bool bInCapped);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L124 _public function_ `bool GetCapped() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L130 _public prototype_ `void SetLooped(bool bInLooped);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplineSweep")`
- L133 _public function_ `bool GetLooped() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplineSweep")`
- L141 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L146 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L147 _protected function_ `virtual void OnActorVisibilityChanged(AActor* InActor) override`
- L151 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L152 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L153 _protected prototype_ `virtual void Apply() override;`
- L156 _protected prototype_ `void OnModifierOptionsChanged();`
- L157 _protected prototype_ `void OnSplineActorWeakChanged();`
- L158 _protected prototype_ `void OnSplineOptionsChanged();`
- L159 _protected prototype_ `bool SampleSpline();`
- L163 _protected member_ `TWeakObjectPtr<AActor> SplineActorWeak;` — `UPROPERTY(EditInstanceOnly, Setter="SetSplineActorWeak", Getter="GetSplineActorWeak", Category="SplineSweep", meta=(FilterActorByComponentClass="/Script/Engine.SplineComponent", AllowPrivateAccess="true"))` — Spline actor to retrieve the USplineComponent from
- L167 _protected member_ `EAvaSplineSweepSampleMode SampleMode = EAvaSplineSweepSampleMode::FullDistance;` — `UPROPERTY(EditInstanceOnly, Setter="SetSampleMode", Getter="GetSampleMode", Category="SplineSweep", meta=(AllowPrivateAccess="true"))` — How do we sample the spline
- L171 _protected member_ `float SampleDistance = 1000.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetSampleDistance", Getter="GetSampleDistance", Category="SplineSweep", meta=(ClampMin="1", EditCondition="SampleMode == EAvaSplineSweepSampleMode::CustomDistance", EditConditionHides, AllowPrivateAccess="true"))` — Custom sample distance for steps per distance mode
- L175 _protected member_ `int32 Steps = 64;` — `UPROPERTY(EditInstanceOnly, Setter="SetSteps", Getter="GetSteps", Category="SplineSweep", meta=(ClampMin="3", ClampMax="200", AllowPrivateAccess="true"))` — The sample count defines the precision of the sweep
- L179 _protected member_ `float ProgressOffset = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetProgressOffset", Getter="GetProgressOffset", Category="SplineSweep", meta=(AllowPrivateAccess="true"))` — Sample range offset of the spline, for closed loop spline range can wrap around
- L183 _protected member_ `float ProgressStart = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetProgressStart", Getter="GetProgressStart", Category="SplineSweep", meta=(ClampMin="0", ClampMax="1", AllowPrivateAccess="true"))` — Sample start range of the spline
- L187 _protected member_ `float ProgressEnd = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetProgressEnd", Getter="GetProgressEnd", Category="SplineSweep", meta=(ClampMin="0", ClampMax="1", AllowPrivateAccess="true"))` — Sample end range of the spline
- L191 _protected member_ `float ScaleStart = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetScaleStart", Getter="GetScaleStart", Category="SplineSweep", meta=(ClampMin="0", AllowPrivateAccess="true"))` — Start scale of the spline mesh
- L195 _protected member_ `float ScaleEnd = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter="SetScaleEnd", Getter="GetScaleEnd", Category="SplineSweep", meta=(ClampMin="0", AllowPrivateAccess="true"))` — End scale of the spline mesh
- L199 _protected member_ `bool bCapped = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetCapped", Getter="GetCapped", Category="SplineSweep", meta=(EditCondition="!bLooped", AllowPrivateAccess="true"))` — Whether start and end are closed, loop must be false
- L203 _protected member_ `bool bLooped = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetLooped", Getter="GetLooped", Category="SplineSweep", meta=(AllowPrivateAccess="true"))` — Whether we close the whole spline path, if spline loops this will be true
- L207 _protected member_ `TWeakObjectPtr<USplineComponent> SplineComponentWeak;` — `UPROPERTY()` — Spline component to sample from
- L211 _protected member_ `TArray<FTransform> SplineSamples;` — `UPROPERTY(Transient)` — Sample points taken from the spline
- L216 _private member_ `static const TAvaPropertyChangeDispatcher<UAvaSplineSweepModifier> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaSubdivideModifier.h` (Public)


#### enum `EAvaSubdivisionType`  
`enum class EAvaSubdivisionType : uint8`  
_L9-14_
- reflection: `UENUM(BlueprintType)`
- L11 _public enumerator_ `Selective`
- L12 _public enumerator_ `Uniform`
- L13 _public enumerator_ `PN`

#### class `UAvaSubdivideModifier`  
`class UAvaSubdivideModifier : public UAvaGeometryBaseModifier`  
_L17-74_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- L22 _public member_ `static constexpr int MinSubdivideCuts = 1;`
- L23 _public member_ `static constexpr int MaxSubdivideCuts = 15;`
- L26 _public prototype_ `void SetCuts(int32 InCuts);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Subdivide")`
- L29 _public function_ `int32 GetCuts() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Subdivide")`
- L35 _public prototype_ `void SetRecomputeNormals(bool bInRecomputeNormals);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Subdivide")`
- L38 _public function_ `bool GetRecomputeNormals() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Subdivide")`
- L44 _public prototype_ `void SetType(EAvaSubdivisionType InType);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Subdivide")`
- L47 _public function_ `EAvaSubdivisionType GetType() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Subdivide")`
- L55 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L60 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L61 _protected prototype_ `virtual void Apply() override;`
- L64 _protected prototype_ `void OnOptionsChanged();`
- L67 _protected member_ `int32 Cuts = 2;` — `UPROPERTY(EditInstanceOnly, Setter="SetCuts", Getter="GetCuts", Category="Subdivide", meta=(ClampMin="1", ClampMax="15", AllowPrivateAccess="true"))`
- L70 _protected member_ `bool bRecomputeNormals = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetRecomputeNormals", Getter="GetRecomputeNormals", Category="Subdivide", meta=(EditCondition="Type == EAvaSubdivisionType::PN", EditConditionHides, AllowPrivateAccess="true"))`
- L73 _protected member_ `EAvaSubdivisionType Type = EAvaSubdivisionType::Uniform;` — `UPROPERTY(EditInstanceOnly, Setter="SetType", Getter="GetType", Category="Subdivide", meta=(AllowPrivateAccess="true"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaTaperModifier.h` (Public)


#### enum `EAvaTaperReferenceFrame`  
`enum class EAvaTaperReferenceFrame : uint8`  
_L10-14_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `MeshCenter`
- L13 _public enumerator_ `Custom`

#### enum `EAvaTaperExtent`  
`enum class EAvaTaperExtent : uint8`  
_L17-21_
- reflection: `UENUM(BlueprintType)`
- L19 _public enumerator_ `WholeShape`
- L20 _public enumerator_ `Custom`

#### class `UAvaTaperModifier`  
`class UAvaTaperModifier : public UAvaGeometryBaseModifier`  
_L24-156_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UAvaGeometryBaseModifier`
- L29 _public member_ `static constexpr int MinTaperLatticeResolution = 1;`
- L30 _public member_ `static constexpr int MaxTaperLatticeResolution = 20;`
- L33 _public prototype_ `void SetAmount(float InAmount);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper")`
- L36 _public function_ `float GetAmount() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper")`
- L42 _public prototype_ `void SetUpperExtent(float InUpperExtent);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper")`
- L45 _public function_ `float GetUpperExtent() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper")`
- L51 _public prototype_ `void SetLowerExtent(float InLowerExtent);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper")`
- L54 _public function_ `float GetLowerExtent() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper")`
- L60 _public prototype_ `void SetExtent(EAvaTaperExtent InExtent);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper")`
- L63 _public function_ `EAvaTaperExtent GetExtent() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper")`
- L69 _public prototype_ `void SetInterpolationType(EAvaTaperInterpolationType InInterpolationType);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper")`
- L72 _public function_ `EAvaTaperInterpolationType GetInterpolationType() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper")`
- L78 _public prototype_ `void SetReferenceFrame(EAvaTaperReferenceFrame InReferenceFrame);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper")`
- L81 _public function_ `EAvaTaperReferenceFrame GetReferenceFrame() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper")`
- L88 _public prototype_ `void SetResolution(int32 InResolution);` — `UE_DEPRECATED(5.7, "Use subdivide modifier before this modifier instead")` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper", meta=(DeprecatedFunction, DeprecatedMessage="Use subdivide modifier before this modifier instead"))`
- L92 _public function_ `int32 GetResolution() const` — `UE_DEPRECATED(5.7, "Use subdivide modifier before this modifier instead")` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper", meta=(DeprecatedFunction, DeprecatedMessage="Use subdivide modifier before this modifier instead"))`
- L100 _public prototype_ `void SetOffset(FVector2D InOffset);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Taper")`
- L103 _public function_ `FVector2D GetOffset() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Taper")`
- L111 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L116 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L117 _protected prototype_ `virtual void Apply() override;`
- L120 _protected prototype_ `void CreateTaperTool();`
- L122 _protected prototype_ `void OnParameterChanged();`
- L124 _protected prototype_ `FVector2D GetRequiredOffset() const;`
- L125 _protected prototype_ `FVector2D GetRequiredExtent() const;`
- L127 _protected prototype_ `int32 GetSubdividersCuts() const;`
- L130 _protected member_ `float Amount = 0.0;` — `UPROPERTY(EditInstanceOnly, Setter="SetAmount", Getter="GetAmount", Category="Taper", meta=(ClampMin="0.0", ClampMax="1.0", AllowPrivateAccess="true"))`
- L133 _protected member_ `EAvaTaperExtent Extent = EAvaTaperExtent::WholeShape;` — `UPROPERTY(EditInstanceOnly, Setter="SetExtent", Getter="GetExtent", Category="Taper", meta=(AllowPrivateAccess="true"))`
- L136 _protected member_ `float UpperExtent = 100;` — `UPROPERTY(EditInstanceOnly, Setter="SetUpperExtent", Getter="GetUpperExtent", Category="Taper", meta=(EditCondition="Extent == EAvaTaperExtent::Custom", EditConditionHides, ClampMin="0", ClampMax="100", Units="Percent", ToolTip="100%: shape top.\n0%: shape bottom.", AllowPrivateAccess="true"))`
- L139 _protected member_ `float LowerExtent = 100;` — `UPROPERTY(EditInstanceOnly, Setter="SetLowerExtent", Getter="GetLowerExtent", Category="Taper", meta=(EditCondition="Extent == EAvaTaperExtent::Custom", EditConditionHides, ClampMin="0", ClampMax="100", Units="Percent", ToolTip="100%: shape bottom.\n0%: shape top.", AllowPrivateAccess="true"))`
- L142 _protected member_ `EAvaTaperInterpolationType InterpolationType = EAvaTaperInterpolationType::Linear;` — `UPROPERTY(EditInstanceOnly, Setter="SetInterpolationType", Getter="GetInterpolationType", Category="Taper", meta=(AllowPrivateAccess="true"))`
- L146 _protected member_ `int32 Resolution = 5;` — `UE_DEPRECATED(5.7, "Use subdivide modifier before this modifier instead")` — `UPROPERTY(Transient, meta=(DeprecatedProperty, DeprecatedMessage="Use subdivide modifier before this modifier instead"))`
- L149 _protected member_ `EAvaTaperReferenceFrame ReferenceFrame = EAvaTaperReferenceFrame::MeshCenter;` — `UPROPERTY(EditInstanceOnly, Setter="SetReferenceFrame", Getter="GetReferenceFrame", Category="Taper", meta=(AllowPrivateAccess="true"))`
- L152 _protected member_ `FVector2D Offset = FVector2D::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter="SetOffset", Getter="GetOffset", Category="Taper", meta=(EditCondition="ReferenceFrame == EAvaTaperReferenceFrame::Custom", EditConditionHides, AllowPrivateAccess="true"))`
- L155 _protected member_ `TObjectPtr<UAvaTaperTool> TaperTool = nullptr;` — `UPROPERTY()`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaTranslucentPriorityModifier.h` (Public)


#### enum `EAvaTranslucentPriorityModifierMode`  
`enum class EAvaTranslucentPriorityModifierMode : uint8`  
_L14-24_
- reflection: `UENUM(BlueprintType)`
- L17 _public enumerator_ `AutoCameraDistance UMETA(DisplayName = "Camera Distance")` — The closer you are from the camera based on camera forward axis, the higher your sort priority will be
- L19 _public enumerator_ `AutoOutlinerTree UMETA(DisplayName = "Outliner Top First")` — The higher you are in the outline tree, the higher your sort priority will be
- L21 _public enumerator_ `AutoOutlinerTreeInverted UMETA(DisplayName = "Outliner Bottom First")` — The lower you are in the outline tree, the higher your sort priority will be
- L23 _public enumerator_ `Manual` — Set it yourself

#### class `UAvaTranslucentPriorityModifier`  
`class UAvaTranslucentPriorityModifier : public UActorModifierArrangeBaseModifier`  
_L27-177_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierArrangeBaseModifier`
- L35 _public prototype_ `void SetMode(EAvaTranslucentPriorityModifierMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L38 _public function_ `EAvaTranslucentPriorityModifierMode GetMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L44 _public prototype_ `void SetCameraActor(ACameraActor* InCameraActor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L47 _public function_ `ACameraActor* GetCameraActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L52 _public prototype_ `void SetCameraActorWeak(const TWeakObjectPtr<ACameraActor>& InCameraActor);`
- L54 _public function_ `TWeakObjectPtr<ACameraActor> GetCameraActorWeak() const`
- L60 _public prototype_ `void SetSortPriority(int32 InSortPriority);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L63 _public function_ `int32 GetSortPriority() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L69 _public prototype_ `void SetSortPriorityOffset(int32 InOffset);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L72 _public function_ `int32 GetSortPriorityOffset() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L78 _public prototype_ `void SetSortPriorityStep(int32 InStep);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L81 _public function_ `int32 GetSortPriorityStep() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L87 _public prototype_ `void SetIncludeChildren(bool bInIncludeChildren);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L90 _public function_ `bool GetIncludeChildren() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|TranslucentSortPriority")`
- L97 _protected prototype_ `virtual void PostLoad() override;`
- L99 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L104 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L105 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L106 _protected prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;`
- L107 _protected prototype_ `virtual void SavePreState() override;`
- L108 _protected prototype_ `virtual void RestorePreState() override;`
- L109 _protected prototype_ `virtual void Apply() override;`
- L110 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L111 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L115 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L116 _protected prototype_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L117 _protected prototype_ `virtual void OnSceneTreeTrackedActorRearranged(int32 InIdx, AActor* InRearrangedActor) override;`
- L121 _protected prototype_ `virtual UE::ActorModifierCore::ERenderStateDirtyReason GetRenderStateDirtyEventTypes() const override;`
- L122 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L126 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L129 _protected prototype_ `void OnModeChanged();`
- L130 _protected prototype_ `void OnCameraActorChanged();`
- L131 _protected prototype_ `void OnSortPriorityChanged();`
- L132 _protected prototype_ `void OnSortPriorityLevelGlobalsChanged() const;`
- L133 _protected prototype_ `void OnIncludeChildrenChanged();`
- L135 _protected prototype_ `void OnGlobalSortPriorityOffsetChanged();`
- L137 _protected prototype_ `ACameraActor* GetDefaultCameraActor() const;`
- L141 _protected member_ `EAvaTranslucentPriorityModifierMode Mode = EAvaTranslucentPriorityModifierMode::Manual;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="TranslucentSortPriority", meta=(DisplayName="Sort Mode", AllowPrivateAccess="true"))` — The sort mode we are currently in
- L145 _protected member_ `TWeakObjectPtr<ACameraActor> CameraActorWeak = nullptr;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="TranslucentSortPriority", meta=(DisplayName="Camera Actor", EditCondition="Mode == EAvaTranslucentPriorityModifierMode::AutoCameraDistance", AllowPrivateAccess="true"))` — The camera actor to compute the distance from
- L149 _protected member_ `int32 SortPriority = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="TranslucentSortPriority", meta=(EditCondition="Mode == EAvaTranslucentPriorityModifierMode::Manual", EditConditionHides, AllowPrivateAccess="true"))` — The sort priority that will be set on the primitive component for manual mode
- L153 _protected member_ `int32 SortPriorityOffset = 0;` — `UPROPERTY(Transient, EditInstanceOnly, Setter, Getter, Category="TranslucentSortPriority", meta=(AllowPrivateAccess="true"))` — Sort priority offset shared across all modifiers in this same level
- L157 _protected member_ `int32 SortPriorityStep = 1;` — `UPROPERTY(Transient, EditInstanceOnly, Setter, Getter, Category="TranslucentSortPriority", meta=(AllowPrivateAccess="true"))` — Sort priority incremental step shared across all modifiers in this same level
- L161 _protected member_ `bool bIncludeChildren = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetIncludeChildren", Getter="GetIncludeChildren", Category="TranslucentSortPriority", meta=(AllowPrivateAccess="true"))` — If true, will include children too and update their sort priority
- L165 _protected member_ `TSet<TWeakObjectPtr<UPrimitiveComponent>> PrimitiveComponentsWeak;` — `UPROPERTY()` — The components this modifier is managing
- L170 _private member_ `TMap<TWeakObjectPtr<UPrimitiveComponent>, int32> PreviousSortPriorities;` — `UPROPERTY()` — The previous sort priority to restore when disabling this modifier
- L173 _private member_ `TMap<FObjectKey, int32> LastSortPriorities;` — Last primitive components assigned sort priority, used for comparison on change
- L176 _private member_ `TArray<FAvaTranslucentPriorityModifierComponentState> CachedSortedComponentStates;` — Used to avoid querying again the full list of component states

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Modifiers/AvaVisibilityModifier.h` (Public)


#### class `UAvaVisibilityModifier`  
`class UAvaVisibilityModifier : public UActorModifierArrangeBaseModifier`  
_L14-104_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierArrangeBaseModifier`
- desc: Controls the visibility of a range of child actors by index.
- L21 _public prototype_ `void SetInvertVisibility(bool bInInvertVisibility);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Visibility")` — Sets the child index range to hide instead of showing.
- L25 _public function_ `bool GetInvertVisibility() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Visibility")` — Returns true if hiding the child index range instead of showing.
- L31 _public prototype_ `void SetIndex(int32 InIndex);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Visibility")`
- L34 _public function_ `int32 GetIndex() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Visibility")`
- L40 _public prototype_ `void SetTreatAsRange(bool bInTreatAsRange);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Visibility")`
- L43 _public function_ `bool GetTreatAsRange() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Visibility")`
- L49 _public prototype_ `void SetSkipWhenHidden(bool bInSkip);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Visibility")`
- L52 _public function_ `bool GetSkipWhenHidden() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Visibility")`
- L60 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L65 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L66 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L67 _protected prototype_ `virtual void Apply() override;`
- L71 _protected prototype_ `virtual void OnActorVisibilityChanged(AActor* InActor) override;`
- L75 _protected prototype_ `bool IsChildActorHidden(AActor* InActor) const;` — Used by other modifiers of this class to check if we are hiding an actor
- L78 _protected prototype_ `UAvaVisibilityModifier* GetFirstModifierAbove(AActor* InActor);` — Get first visibility modifier found above this actor
- L79 _protected prototype_ `TArray<UAvaVisibilityModifier*> GetModifiersAbove(AActor* InActor);`
- L82 _protected prototype_ `AActor* GetDirectChildren(AActor* InParentActor, AActor* InChildActor);` — Will find the direct children of InParentActor that contains this child actor
- L86 _protected member_ `int32 Index = 0;` — `UPROPERTY(EditInstanceOnly, Setter="SetIndex", Getter="GetIndex", Category="Visibility", meta=(ClampMin="0", UIMin="0", AllowPrivateAccess="true"))` — Child index to set visibility, visible if bInvertVisibility is false else hidden
- L90 _protected member_ `bool bTreatAsRange = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetTreatAsRange", Getter="GetTreatAsRange", Category="Visibility", meta=(DisplayName="Keep Visible", AllowPrivateAccess="true"))` — Treat index as a range from 0 to index
- L94 _protected member_ `bool bInvertVisibility = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetInvertVisibility", Getter="GetInvertVisibility", Category="Visibility", meta=(AllowPrivateAccess="true"))` — If true, will hide the child index range instead of showing.
- L98 _protected member_ `bool bSkipWhenHidden = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetSkipWhenHidden", Getter="GetSkipWhenHidden", Category="Visibility", meta=(AllowPrivateAccess="true"))` — If true, when the top actor having this modifier is hidden, children actor visibility state will not be handled
- L103 _private member_ `TMap<TWeakObjectPtr<AActor>, bool> DirectChildrenActorsWeak;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Visibility defined for direct children of this actor, used by other modifiers of this type to check

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Profilers/AvaBooleanModifierProfiler.h` (Public)


#### class `FAvaBooleanModifierProfiler`  
`class FAvaBooleanModifierProfiler : public FAvaGeometryModifierProfiler`  
_L10-23_
- inherits: `FAvaGeometryModifierProfiler`
- desc: Modifier profiler used by boolean modifiers
- L13 _public member_ `static inline const FName ChannelInfo = TEXT("Cha`
- L16 _public prototype_ `virtual void SetupProfilingStats() override;`
- L17 _public prototype_ `virtual void BeginProfiling() override;`
- L18 _public prototype_ `virtual void EndProfiling() override;`
- L19 _public prototype_ `virtual TSet<FName> GetMainProfilingStats() const override;`
- L22 _public prototype_ `FAvaBooleanModifierSharedChannelInfo GetChannelInfo() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Profilers/AvaGeometryModifierProfiler.h` (Public)


#### class `FAvaGeometryModifierProfiler`  
`class FAvaGeometryModifierProfiler : public FActorModifierCoreProfiler`  
_L8-31_
- inherits: `FActorModifierCoreProfiler`
- desc: Modifier profiler used by geometry modifiers
- L11 _public member_ `static inline const FName VertexInName = TEXT("Ver`
- L12 _public member_ `static inline const FName VertexOutName = TEXT("Ver`
- L13 _public member_ `static inline const FName TriangleInName = TEXT("Tri`
- L14 _public member_ `static inline const FName TriangleOutName = TEXT("Tri`
- L15 _public member_ `static inline const FName EdgeInName = TEXT("Edg`
- L16 _public member_ `static inline const FName EdgeOutName = TEXT("Edg`
- L19 _public prototype_ `virtual void SetupProfilingStats() override;`
- L20 _public prototype_ `virtual void BeginProfiling() override;`
- L21 _public prototype_ `virtual void EndProfiling() override;`
- L22 _public prototype_ `virtual TSet<FName> GetMainProfilingStats() const override;`
- L25 _public prototype_ `int32 GetVertexIn() const;`
- L26 _public prototype_ `int32 GetVertexOut() const;`
- L27 _public prototype_ `int32 GetTriangleIn() const;`
- L28 _public prototype_ `int32 GetTriangleOut() const;`
- L29 _public prototype_ `int32 GetEdgeIn() const;`
- L30 _public prototype_ `int32 GetEdgeOut() const;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Shared/AvaBooleanModifierShared.h` (Public)


#### struct `FAvaBooleanModifierSharedChannel`  
`struct FAvaBooleanModifierSharedChannel`  
_L13-19_
- reflection: `USTRUCT()`
- L18 _public member_ `TSet<TWeakObjectPtr<UAvaBooleanModifier>> ModifiersWeak;` — `UPROPERTY()`

#### struct `FAvaBooleanModifierSharedChannelInfo`  
`struct FAvaBooleanModifierSharedChannelInfo`  
_L22-45_
- reflection: `USTRUCT(BlueprintType)`
- L28 _public member_ `int32 ChannelCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Channel")` — The number of channel currently active
- L32 _public member_ `int32 ChannelModifierCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Channel")` — The number of modifier on that channel, the more there are, the more impact on performance
- L36 _public member_ `int32 ChannelToolCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Channel")` — The number of modifier on that channel that are used to mask other non mask modifier
- L40 _public member_ `int32 ChannelTargetCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Channel")` — The number of modifier on that channel that are masked by other mask modifier
- L44 _public member_ `int32 ChannelIntersectCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Channel")` — The number of modifier intersecting with this modifier

#### class `UAvaBooleanModifierShared`  
`class UAvaBooleanModifierShared : public UActorModifierCoreSharedObject`  
_L52-84_
- reflection: `UCLASS(Transient, Hidden)`
- inherits: `UActorModifierCoreSharedObject`
- desc: Singleton class for boolean modifiers to share data Transient because we can rebuild it, no need to save the asset
- L58 _public prototype_ `void TrackModifierChannel(UAvaBooleanModifier* InModifier);` — Track a modifier on a channel
- L61 _public prototype_ `void UntrackModifierChannel(UAvaBooleanModifier* InModifier);` — Untrack a modifier from a channel
- L64 _public prototype_ `void UpdateModifierChannel(UAvaBooleanModifier* InModifier);` — Updates and refresh modifier channel
- L67 _public prototype_ `uint8 GetChannelCount() const;` — Get number of active channel
- L70 _public prototype_ `int32 GetChannelModifierCount(uint8 InChannel) const;` — Get number of modifier active on that channel
- L73 _public prototype_ `int32 GetChannelModifierModeCount(uint8 InChannel, EAvaBooleanMode InMode) const;` — Get number of modifier active on that channel with that mode set
- L76 _public prototype_ `TSet<TWeakObjectPtr<UAvaBooleanModifier>> GetIntersectingModifiers(const UAvaBooleanModifier* InTargetModifier, FAvaBooleanModifierSharedChannelInfo* OutDesc = nullptr);` — Get all intersecting modifiers with the input target modifier
- L80 _private prototype_ `bool TestIntersection(const UE::Geometry::FDynamicMesh3& InToolMesh, const FTransform& InToolTransform, const UE::Geometry::FDynamicMesh3& InTargetMesh, const FTransform& InTargetTransform) const;` — Tests if two meshes are intersecting, always pass the tool/mask mesh first
- L83 _private member_ `TMap<uint8, FAvaBooleanModifierSharedChannel> Channels;` — `UPROPERTY(Transient)`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Shared/AvaTranslucentPriorityModifierShared.h` (Public)


#### struct `FAvaTranslucentPriorityModifierComponentState`  
`struct FAvaTranslucentPriorityModifierComponentState`  
_L17-74_
- reflection: `USTRUCT()`
- L22 _public prototype_ `FAvaTranslucentPriorityModifierComponentState() = default;`
- L23 _public function_ `explicit FAvaTranslucentPriorityModifierComponentState(UPrimitiveComponent* InComponent) : PrimitiveComponent(InComponent)`
- L27 _public prototype_ `FAvaTranslucentPriorityModifierComponentState(const FAvaTranslucentPriorityModifierComponentState&) = default;`
- L28 _public prototype_ `FAvaTranslucentPriorityModifierComponentState(FAvaTranslucentPriorityModifierComponentState&&) = default;`
- L29 _public prototype_ `FAvaTranslucentPriorityModifierComponentState& operator=(const FAvaTranslucentPriorityModifierComponentState&) = default;`
- L30 _public prototype_ `FAvaTranslucentPriorityModifierComponentState& operator=(FAvaTranslucentPriorityModifierComponentState&&) = default;`
- L34 _public prototype_ `void Save();` — Save this component state if valid
- L37 _public prototype_ `void Restore() const;` — Restore this component state if valid
- L40 _public prototype_ `AActor* GetOwningActor() const;` — Get component owning actor
- L43 _public prototype_ `FVector GetComponentLocation() const;` — Get component world location
- L50 _public function_ `bool operator==(const FAvaTranslucentPriorityModifierComponentState& InOther) const`
- L57 _public member_ `TWeakObjectPtr<UAvaTranslucentPriorityModifier> ModifierWeak;` — `UE_DEPRECATED(5.8,"Use Modifier instead")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use Modifier instead"))`
- L61 _public member_ `TWeakObjectPtr<UPrimitiveComponent> PrimitiveComponentWeak;` — `UE_DEPRECATED(5.8,"Use PrimitiveComponent instead")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use PrimitiveComponent instead"))`
- L65 _public member_ `TObjectPtr<UAvaTranslucentPriorityModifier> Modifier;` — `UPROPERTY()` — Modifier managing this component state
- L69 _public member_ `TObjectPtr<UPrimitiveComponent> PrimitiveComponent;` — `UPROPERTY()` — Primitive component that this state is describing
- L73 _public member_ `int32 SortPriority = 0;` — `UPROPERTY()` — Previous sort priority to restore

#### class `UAvaTranslucentPriorityModifierShared`  
`class UAvaTranslucentPriorityModifierShared : public UActorModifierCoreSharedObject`  
_L80-139_
- reflection: `UCLASS(Hidden)`
- inherits: `UActorModifierCoreSharedObject`
- desc: Singleton class for translucent priority modifiers to share data about component state
- L85 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnLevelGlobalsChanged) FOnLevelGlobalsChanged OnLevelGlobalsChangedDelegate;`
- L89 _public prototype_ `void SetComponentsState(UAvaTranslucentPriorityModifier* InModifierContext, const TSet<TWeakObjectPtr<UPrimitiveComponent>>& InComponents);` — Replaces the component linked to this context by new components set
- L92 _public prototype_ `void SaveComponentState(UAvaTranslucentPriorityModifier* InModifierContext, UPrimitiveComponent* InComponent, bool bInOverrideContext);` — Save component state, adds it if it is not tracked, optionally override the context
- L95 _public prototype_ `void RestoreComponentState(const UAvaTranslucentPriorityModifier* InModifierContext, UPrimitiveComponent* InComponent, bool bInClearState);` — Restore component state, removes it if no other modifier track that state
- L98 _public prototype_ `void RestoreComponentsState(const UAvaTranslucentPriorityModifier* InModifierContext, bool bInClearState);` — Restore components state linked to this modifier
- L101 _public prototype_ `void RestoreComponentsState(const UAvaTranslucentPriorityModifier* InModifierContext, const TSet<TWeakObjectPtr<UPrimitiveComponent>>& InComponents, bool bInClearState);` — Restore components state linked to this modifier
- L104 _public prototype_ `UAvaTranslucentPriorityModifier* FindModifierContext(UPrimitiveComponent* InComponent) const;` — Find the modifier linked to a component
- L107 _public prototype_ `TArray<FAvaTranslucentPriorityModifierComponentState> GetSortedComponentStates(UAvaTranslucentPriorityModifier* InModifierContext) const;` — Get sorted components state based on modifier context
- L109 _public prototype_ `void SetSortPriorityOffset(int32 InOffset);`
- L111 _public function_ `int32 GetSortPriorityOffset() const`
- L116 _public prototype_ `void SetSortPriorityStep(int32 InStep);`
- L118 _public function_ `int32 GetSortPriorityStep() const`
- L125 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L126 _private prototype_ `virtual void PostLoad() override;`
- L130 _private member_ `TSet<FAvaTranslucentPriorityModifierComponentState> ComponentStates;` — `UPROPERTY()`
- L134 _private member_ `int32 SortPriorityOffset = 0;` — `UPROPERTY()` — Offset for the whole level
- L138 _private member_ `int32 SortPriorityStep = 1;` — `UPROPERTY()` — Incremental step for the whole level

#### Free symbols / members of external scopes

- L45 _function_ `friend uint32 GetTypeHash(const FAvaTranslucentPriorityModifierComponentState& InItem)`
- L85 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnLevelGlobalsChanged) FOnLevelGlobalsChanged OnLevelGlobalsChangedDelegate;`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Tools/AvaPatternModifierCircleTool.h` (Public)


#### class `UAvaPatternModifierCircleTool`  
`class UAvaPatternModifierCircleTool : public UAvaPatternModifierTool`  
_L11-126_
- reflection: `UCLASS(DisplayName="Circle", ClassGroup="Modifiers")`
- inherits: `UAvaPatternModifierTool`
- desc: Circle tool for the pattern modifier
- L19 _public function_ `EAvaPatternModifierPlane GetCirclePlane() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L25 _public prototype_ `void SetCirclePlane(EAvaPatternModifierPlane InCirclePlane);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L28 _public function_ `float GetCircleRadius() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L34 _public prototype_ `void SetCircleRadius(float InCircleRadius);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L37 _public function_ `float GetCircleStartAngle() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L43 _public prototype_ `void SetCircleStartAngle(float InCircleStartAngle);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L46 _public function_ `float GetCircleFullAngle() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L52 _public prototype_ `void SetCircleFullAngle(float InCircleFullAngle);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L55 _public function_ `int32 GetCircleCount() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L61 _public prototype_ `void SetCircleCount(int32 InCircleCount);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L64 _public function_ `bool GetCircleAccumulateTransform() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L70 _public prototype_ `void SetCircleAccumulateTransform(bool bInCircleAccumulateTransform);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L73 _public function_ `FRotator GetCircleRotation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L79 _public prototype_ `void SetCircleRotation(const FRotator& InCircleRotation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L82 _public function_ `FVector GetCircleScale() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L88 _public prototype_ `void SetCircleScale(const FVector& InCircleScale);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L93 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L98 _protected prototype_ `virtual TArray<FTransform> GetTransformInstances(const FBox& InOriginalBounds) const;`
- L99 _protected prototype_ `virtual FVector GetCenterAlignmentAxis() const override;`
- L100 _protected prototype_ `virtual FName GetToolName() const override;`
- L104 _protected member_ `EAvaPatternModifierPlane CirclePlane = EAvaPatternModifierPlane::YZ;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L107 _protected member_ `float CircleRadius = 100.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L110 _protected member_ `float CircleStartAngle = 180.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L113 _protected member_ `float CircleFullAngle = 360.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L116 _protected member_ `int32 CircleCount = 4;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", meta=(ClampMin="1", ClampMax="10000"))`
- L119 _protected member_ `bool bCircleAccumulateTransform = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetCircleAccumulateTransform", Getter="GetCircleAccumulateTransform", Category="Pattern")`
- L122 _protected member_ `FRotator CircleRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L125 _protected member_ `FVector CircleScale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Tools/AvaPatternModifierGridTool.h` (Public)


#### class `UAvaPatternModifierGridTool`  
`class UAvaPatternModifierGridTool : public UAvaPatternModifierTool`  
_L11-138_
- reflection: `UCLASS(DisplayName="Grid", ClassGroup="Modifiers")`
- inherits: `UAvaPatternModifierTool`
- desc: Grid tool for the pattern modifier
- L19 _public function_ `EAvaPatternModifierPlane GetGridPlane() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L25 _public prototype_ `void SetGridPlane(EAvaPatternModifierPlane InGridPlane);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L28 _public function_ `EAvaPatternModifierGridAlignment GetGridAlignment() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L34 _public prototype_ `void SetGridAlignment(EAvaPatternModifierGridAlignment InGridAlignment);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L37 _public function_ `int32 GetGridCountX() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L43 _public prototype_ `void SetGridCountX(int32 InGridCountX);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L46 _public function_ `int32 GetGridCountY() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L52 _public prototype_ `void SetGridCountY(int32 InGridCountY);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L55 _public function_ `float GetGridSpacingX() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L61 _public prototype_ `void SetGridSpacingX(float InGridSpacingX);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L64 _public function_ `float GetGridSpacingY() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L70 _public prototype_ `void SetGridSpacingY(float InGridSpacingY);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L73 _public function_ `bool GetGridAccumulateTransform() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L79 _public prototype_ `void SetGridAccumulateTransform(bool bInGridAccumulateTransform);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L82 _public function_ `FRotator GetGridRotation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L88 _public prototype_ `void SetGridRotation(const FRotator& InGridRotation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L91 _public function_ `FVector GetGridScale() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L97 _public prototype_ `void SetGridScale(const FVector& InGridScale);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L102 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L107 _protected prototype_ `virtual TArray<FTransform> GetTransformInstances(const FBox& InOriginalBounds) const;`
- L108 _protected prototype_ `virtual FVector GetCenterAlignmentAxis() const override;`
- L109 _protected prototype_ `virtual FName GetToolName() const override;`
- L113 _protected member_ `EAvaPatternModifierPlane GridPlane = EAvaPatternModifierPlane::YZ;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L116 _protected member_ `EAvaPatternModifierGridAlignment GridAlignment = EAvaPatternModifierGridAlignment::Center;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L119 _protected member_ `int32 GridCountX = 2;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", meta=(ClampMin="1", ClampMax="10000"))`
- L122 _protected member_ `int32 GridCountY = 2;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", meta=(ClampMin="1", ClampMax="10000"))`
- L125 _protected member_ `float GridSpacingX = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L128 _protected member_ `float GridSpacingY = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L131 _protected member_ `bool bGridAccumulateTransform = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetGridAccumulateTransform", Getter="GetGridAccumulateTransform", Category="Pattern")`
- L134 _protected member_ `FRotator GridRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L137 _protected member_ `FVector GridScale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Tools/AvaPatternModifierLineTool.h` (Public)


#### class `UAvaPatternModifierLineTool`  
`class UAvaPatternModifierLineTool : public UAvaPatternModifierTool`  
_L11-114_
- reflection: `UCLASS(DisplayName="Line", ClassGroup="Modifiers")`
- inherits: `UAvaPatternModifierTool`
- desc: Line tool for the pattern modifier
- L19 _public function_ `EAvaPatternModifierAxis GetLineAxis() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L25 _public prototype_ `void SetLineAxis(EAvaPatternModifierAxis InLineAxis);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L28 _public function_ `EAvaPatternModifierLineAlignment GetLineAlignment() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L34 _public prototype_ `void SetLineAlignment(EAvaPatternModifierLineAlignment InLineAlignment);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L37 _public function_ `int32 GetLineCount() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L43 _public prototype_ `void SetLineCount(int32 InLineCount);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L46 _public function_ `float GetLineSpacing() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L52 _public prototype_ `void SetLineSpacing(float InLineSpacing);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L55 _public function_ `bool GetLineAccumulateTransform() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L61 _public prototype_ `void SetLineAccumulateTransform(bool bInLineAccumulateTransform);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L64 _public function_ `FRotator GetLineRotation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L70 _public prototype_ `void SetLineRotation(const FRotator& InLineRotation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L73 _public function_ `FVector GetLineScale() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Pattern")`
- L79 _public prototype_ `void SetLineScale(const FVector& InLineScale);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Pattern")`
- L84 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InEvent) override;`
- L89 _protected prototype_ `virtual TArray<FTransform> GetTransformInstances(const FBox& InOriginalBounds) const;`
- L90 _protected prototype_ `virtual FVector GetCenterAlignmentAxis() const override;`
- L91 _protected prototype_ `virtual FName GetToolName() const override;`
- L95 _protected member_ `EAvaPatternModifierAxis LineAxis = EAvaPatternModifierAxis::Y;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L98 _protected member_ `EAvaPatternModifierLineAlignment LineAlignment = EAvaPatternModifierLineAlignment::Center;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L101 _protected member_ `int32 LineCount = 4;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", meta=(ClampMin="1", ClampMax="10000"))`
- L104 _protected member_ `float LineSpacing = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L107 _protected member_ `bool bLineAccumulateTransform = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetLineAccumulateTransform", Getter="GetLineAccumulateTransform", Category="Pattern")`
- L110 _protected member_ `FRotator LineRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern")`
- L113 _protected member_ `FVector LineScale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Pattern", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))`

### `Plugins/VirtualProduction/Avalanche/Source/AvalancheModifiers/Public/Version/AvaTranslucentPriorityModifierVersion.h` (Public)


#### struct `UE::AvaModifiers::FTranslucentPriorityModifierVersion`  
`struct FTranslucentPriorityModifierVersion`  
_L14-33_
- desc: Describes the versions of the translucent priority modifier
- L17 _private prototype_ `FTranslucentPriorityModifierVersion() = delete;`
- L32 _public member_ `const static FGuid Guid;`

#### enum `UE::AvaModifiers::FTranslucentPriorityModifierVersion::Type`  
`enum Type : uint8`  
_L20-30_
- L22 _public enumerator_ `PreVersioning = 0`
- L25 _public enumerator_ `UpgradeFromWeak` — Upgraded TWeakObjectPtr to TObjectPtr in UAvaTranslucentPriorityModifierShared
- L28 _public enumerator_ `VersionPlusOne`
- L29 _public enumerator_ `LatestVersion = VersionPlusOne - 1`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API AVALANCHEMODIFIERS_API`
- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace AvaModifiers` (scope `UE`)
