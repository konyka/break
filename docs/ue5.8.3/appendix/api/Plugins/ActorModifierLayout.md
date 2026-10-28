# Plugins / ActorModifierLayout

- module root: `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout`
- headers: 7; symbols: 280
- symbol kinds: class=7, enum=8, enumerator=27, function=52, member=60, prototype=125, struct=1
- PrivateDependencyModuleNames: CoreUObject, Engine
- PublicDependencyModuleNames: ActorModifier, ActorModifierCore, Core

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout/Public/Modifiers/ActorModifierAlignBetweenModifier.h` (Public)


#### struct `FActorModifierAlignBetweenWeightedActor`  
`struct FActorModifierAlignBetweenWeightedActor`  
_L13-57_
- reflection: `USTRUCT(BlueprintType)`
- desc: Represents an actor with a weight and an enabled state.
- L17 _public function_ `FActorModifierAlignBetweenWeightedActor()`
- L20 _public function_ `explicit FActorModifierAlignBetweenWeightedActor(AActor* InActor) : ActorWeak(InActor)`
- L24 _public function_ `explicit FActorModifierAlignBetweenWeightedActor(AActor* InActor, float InWeight, bool bInEnabled) : ActorWeak(InActor) , Weight(InWeight) , bEnabled(bInEnabled)`
- L31 _public function_ `bool IsValid() const` — Returns true if the actor is valid and the state is enabled.
- L41 _public function_ `bool operator==(const FActorModifierAlignBetweenWeightedActor& Other) const`
- L48 _public member_ `TWeakObjectPtr<AActor> ActorWeak;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Motion Design")` — An actor that will effect the placement location.
- L52 _public member_ `float Weight = 0.0f;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Motion Design", Meta = (ClampMin = "0.0", UIMin = "0.0"))` — How much effect this actor has on the placement location.
- L56 _public member_ `bool bEnabled = false;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="Motion Design")` — If true, will consider this weighted actor when calculating the placement location.

#### class `UActorModifierAlignBetweenModifier`  
`class UActorModifierAlignBetweenModifier : public UActorModifierCoreBase , public IActorModifierTransformUpdateHandler`  
_L63-125_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierCoreBase,IActorModifierTransformUpdateHandler`
- desc: Moves the modifying actor to the averaged location between an array of specified actors.
- L71 _public function_ `TSet<FActorModifierAlignBetweenWeightedActor> GetReferenceActors() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AlignBetween")` — Gets all reference actors and their weights.
- L78 _public prototype_ `void SetReferenceActors(const TSet<FActorModifierAlignBetweenWeightedActor>& InReferenceActors);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AlignBetween")` — Sets all reference actors and their weights.
- L82 _public prototype_ `bool AddReferenceActor(const FActorModifierAlignBetweenWeightedActor& InReferenceActor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AlignBetween")` — Adds an actor to the reference list.
- L86 _public prototype_ `bool RemoveReferenceActor(AActor* const InActor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AlignBetween")` — Removes an actor from the reference list.
- L90 _public prototype_ `bool FindReferenceActor(AActor* InActor, FActorModifierAlignBetweenWeightedActor& OutReferenceActor) const;` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AlignBetween")` — Finds an actor in the reference list.
- L95 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L96 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L101 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L102 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L103 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L104 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L105 _protected prototype_ `virtual void Apply() override;`
- L106 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L110 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L113 _protected prototype_ `void OnReferenceActorsChanged();`
- L114 _protected prototype_ `void SetTransformExtensionReferenceActors();`
- L117 _protected prototype_ `TSet<AActor*> GetActors(const bool bEnabledOnly = false) const;` — Gets all actors from their reference actor structs.
- L120 _protected prototype_ `TSet<FActorModifierAlignBetweenWeightedActor> GetEnabledReferenceActors() const;` — Returns all valid reference actors that enabled and have a weight greater than 0.
- L124 _protected member_ `TSet<FActorModifierAlignBetweenWeightedActor> ReferenceActors;` — `UPROPERTY(EditInstanceOnly, Setter="SetReferenceActors", Getter="GetReferenceActors", Category="AlignBetween", meta=(AllowPrivateAccess="true"))` — Editable set of reference actors and weights used to calculate the average location for this actor

#### Free symbols / members of external scopes

- L36 _function_ `friend uint32 GetTypeHash(const FActorModifierAlignBetweenWeightedActor& InItem)`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout/Public/Modifiers/ActorModifierAutoFollowModifier.h` (Public)


#### class `UActorModifierAutoFollowModifier`  
`class UActorModifierAutoFollowModifier : public UActorModifierAttachmentBaseModifier , public IActorModifierTransformUpdateHandler , public IActorModifierRenderStateUpdateHandler`  
_L19-205_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierAttachmentBaseModifier,IActorModifierTransformUpdateHandler,IActorModifierRenderStateUpdateHandler`
- desc: Moves the modifying actor along with a specified actor relative to the specified actor's bounds.
- L27 _public prototype_ `void SetReferenceActor(const FActorModifierSceneTreeActor& InReferenceActor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")`
- L30 _public function_ `const FActorModifierSceneTreeActor& GetReferenceActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")`
- L36 _public prototype_ `void SetFollowedAxis(int32 InFollowedAxis);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")`
- L39 _public function_ `int32 GetFollowedAxis() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")`
- L46 _public prototype_ `void SetDefaultDistance(const FVector& InDefaultDistance);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")` — Sets the distance from this actor to the followed actor.
- L50 _public function_ `FVector GetDefaultDistance() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")` — Gets the distance from this actor to the followed actor.
- L57 _public prototype_ `void SetMaxDistance(const FVector& InMaxDistance);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")` — Sets the maximum distance from this actor to the followed actor.
- L61 _public function_ `FVector GetMaxDistance() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")` — Gets the maximum distance from this actor to the followed actor.
- L68 _public prototype_ `void SetProgress(const FVector& InProgress);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")` — Sets the percent % progress from the maximum distance to the default distance.
- L72 _public function_ `FVector GetProgress() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")` — Gets the percent % progress from the maximum distance to the default distance.
- L79 _public prototype_ `void SetFollowedAlignment(const FActorModifierAnchorAlignment& InFollowedAlignment);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")` — Sets the alignment for the followed actor's center.
- L83 _public function_ `FActorModifierAnchorAlignment GetFollowedAlignment() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")` — Gets the alignment for the followed actor's center.
- L90 _public prototype_ `void SetLocalAlignment(const FActorModifierAnchorAlignment& InLocalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")` — Sets the alignment for this actor's center.
- L94 _public function_ `FActorModifierAnchorAlignment GetLocalAlignment() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")` — Gets the alignment for this actor's center.
- L101 _public prototype_ `void SetOffsetAxis(const FVector& InOffsetAxis);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|AutoFollow")` — Sets the axis direction to offset this actor from the followed actor's bounds.
- L105 _public function_ `FVector GetOffsetAxis() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|AutoFollow")` — Gets the axis direction to offset this actor from the followed actor's bounds.
- L112 _protected prototype_ `virtual void PostLoad() override;`
- L114 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L115 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L120 _protected prototype_ `virtual bool IsModifierDirtyable() const override;`
- L121 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L122 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L123 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L124 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L125 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L126 _protected prototype_ `virtual void Apply() override;`
- L130 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L134 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L135 _protected function_ `virtual void OnActorVisibilityChanged(AActor* InActor) override`
- L139 _protected prototype_ `virtual void OnSceneTreeTrackedActorChanged(int32 InIdx, AActor* InPreviousActor, AActor* InNewActor) override;`
- L140 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L143 _protected prototype_ `void OnReferenceActorChanged();`
- L145 _protected prototype_ `void OnFollowedAxisChanged();`
- L148 _protected member_ `FActorModifierSceneTreeActor ReferenceActor;` — `UPROPERTY(EditInstanceOnly, Setter="SetReferenceActor", Getter="GetReferenceActor", Category="AutoFollow", meta=(ShowOnlyInnerProperties, AllowPrivateAccess="true"))`
- L152 _protected member_ `EActorModifierReferenceContainer ReferenceContainer_DEPRECATED = EActorModifierReferenceContainer::Other;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ReferenceActor instead"))` — The method for finding a reference actor based on it's position in the parent's hierarchy.
- L156 _protected member_ `TWeakObjectPtr<AActor> ReferenceActorWeak_DEPRECATED = nullptr;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ReferenceActor instead"))` — The actor being followed by the modifier. This is user selectable if the Reference Container is set to "Other".
- L160 _protected member_ `bool bIgnoreHiddenActors_DEPRECATED = false;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ReferenceActor instead"))` — If true, will search for the next visible actor based on the selected reference container.
- L164 _protected member_ `int32 FollowedAxis = static_cast<int32>( EActorModifierAxis::Y | EActorModifierAxis::Z );` — `UPROPERTY(EditInstanceOnly, Setter="SetFollowedAxis", Getter="GetFollowedAxis", Category="AutoFollow", meta=(Bitmask, BitmaskEnum="/Script/ActorModifier.EActorModifierAxis", AllowPrivateAccess="true"))` — Which axis should we follow
- L171 _protected member_ `FVector OffsetAxis = FVector(0, 1, 0);` — `UPROPERTY(EditInstanceOnly, Setter="SetOffsetAxis", Getter="GetOffsetAxis", Interp, Category="AutoFollow", meta=(UIMin="-1.0", UIMax="1.0", AllowPrivateAccess="true"))` — Based on followed axis, the direction to offset this actor from the followed actor's bounds.
- L175 _protected member_ `FActorModifierAnchorAlignment FollowedAlignment;` — `UPROPERTY(EditInstanceOnly, Setter="SetFollowedAlignment", Getter="GetFollowedAlignment", Category="AutoFollow", meta=(AllowPrivateAccess="true"))` — The alignment for the followed actor's center.
- L179 _protected member_ `FActorModifierAnchorAlignment LocalAlignment;` — `UPROPERTY(EditInstanceOnly, Setter="SetLocalAlignment", Getter="GetLocalAlignment", Category="AutoFollow", meta=(AllowPrivateAccess="true"))` — The alignment for this actor's center.
- L183 _protected member_ `FVector DefaultDistance;` — `UPROPERTY(EditInstanceOnly, Setter="SetDefaultDistance", Getter="GetDefaultDistance", Interp, DisplayName="Start Padding", Category="AutoFollow", meta=(AllowPrivateAccess="true"))` — The distance from this actor to the followed actor.
- L187 _protected member_ `FVector MaxDistance;` — `UPROPERTY(EditInstanceOnly, Setter="SetMaxDistance", Getter="GetMaxDistance", Interp, DisplayName="End Padding", Category="AutoFollow", meta=(AllowPrivateAccess="true"))` — The maximum distance from this actor to the followed actor.
- L191 _protected member_ `FVector Progress;` — `UPROPERTY(EditInstanceOnly, Setter="SetProgress", Getter="GetProgress", Interp, DisplayName="Padding Progress", Category="AutoFollow", meta=(ClampMin="0.0", UIMin="0.0", ClampMax="100.0", UIMax="100.0", AllowPrivateAccess="true"))` — Percent % progress from the maximum distance to the default distance.
- L195 _private member_ `FVector CachedFollowLocation = FVector::ZeroVector;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`
- L198 _private member_ `FBox CachedReferenceBounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`
- L201 _private member_ `FBox CachedModifiedBounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`
- L204 _private member_ `bool bDeprecatedPropertiesMigrated = false;` — `UPROPERTY()`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout/Public/Modifiers/ActorModifierGridArrangeModifier.h` (Public)


#### enum `EActorModifierGridArrangeDirection`  
`enum class EActorModifierGridArrangeDirection : uint8`  
_L10-14_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies a starting direction when laying out a grid arrangement.
- L12 _public enumerator_ `Horizontal`
- L13 _public enumerator_ `Vertical`

#### enum `EActorModifierGridArrangeCorner2D`  
`enum class EActorModifierGridArrangeCorner2D : uint8`  
_L18-24_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies a corner for a 2D rectangle.
- L20 _public enumerator_ `TopLeft`
- L21 _public enumerator_ `TopRight`
- L22 _public enumerator_ `BottomLeft`
- L23 _public enumerator_ `BottomRight`

#### class `UActorModifierGridArrangeModifier`  
`class UActorModifierGridArrangeModifier : public UActorModifierArrangeBaseModifier`  
_L30-102_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierArrangeBaseModifier`
- desc: Arranges child actors in a 2D grid format.
- L37 _public prototype_ `void SetCount(const FIntPoint& InCount);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|GridArrange")` — Sets the width and height of the grid.
- L41 _public function_ `FIntPoint GetCount() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|GridArrange")` — Returns the width and height of the grid.
- L48 _public prototype_ `void SetSpread(const FVector2D& InSpread);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|GridArrange")` — Sets the distance between each horizontal and vertical child.
- L52 _public function_ `FVector2D GetSpread() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|GridArrange")` — Returns the distance between each horizontal and vertical child.
- L58 _public prototype_ `void SetStartCorner(EActorModifierGridArrangeCorner2D InCorner);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|GridArrange")`
- L61 _public function_ `EActorModifierGridArrangeCorner2D GetStartCorner() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|GridArrange")`
- L67 _public prototype_ `void SetStartDirection(EActorModifierGridArrangeDirection InDirection);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|GridArrange")`
- L70 _public function_ `EActorModifierGridArrangeDirection GetStartDirection() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|GridArrange")`
- L78 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L83 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L84 _protected prototype_ `virtual void Apply() override;`
- L89 _protected member_ `FIntPoint Count = FIntPoint(1, 1);` — `UPROPERTY(EditInstanceOnly, Setter="SetCount", Getter="GetCount", Category="GridArrange", Meta=(ClampMin="1", UIMin="1", AllowPrivateAccess="true"))` — The width and height of the grid.
- L93 _protected member_ `FVector2D Spread = FVector2D::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter="SetSpread", Getter="GetSpread", Interp, Category="GridArrange", meta=(AllowPrivateAccess="true"))` — The distance between each horizontal and vertical child.
- L97 _protected member_ `EActorModifierGridArrangeCorner2D StartCorner;` — `UPROPERTY(EditInstanceOnly, Setter="SetStartCorner", Getter="GetStartCorner", Category="GridArrange", meta=(AllowPrivateAccess="true"))` — The 2D corner from which to start the arrangement.
- L101 _protected member_ `EActorModifierGridArrangeDirection StartDirection;` — `UPROPERTY(EditInstanceOnly, Setter="SetStartDirection", Getter="GetStartDirection", Category="GridArrange", meta=(AllowPrivateAccess="true"))` — The direction from which to start the arrangement.

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout/Public/Modifiers/ActorModifierJustifyModifier.h` (Public)


#### enum `EActorModifierJustifyVertical`  
`enum class EActorModifierJustifyVertical : uint8`  
_L10-16_
- reflection: `UENUM(BlueprintType)`
- L12 _public enumerator_ `None`
- L13 _public enumerator_ `Top`
- L14 _public enumerator_ `Center`
- L15 _public enumerator_ `Bottom`

#### enum `EActorModifierJustifyHorizontal`  
`enum class EActorModifierJustifyHorizontal : uint8`  
_L19-25_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `None`
- L22 _public enumerator_ `Left`
- L23 _public enumerator_ `Center`
- L24 _public enumerator_ `Right`

#### enum `EActorModifierJustifyDepth`  
`enum class EActorModifierJustifyDepth : uint8`  
_L28-34_
- reflection: `UENUM(BlueprintType)`
- L30 _public enumerator_ `None`
- L31 _public enumerator_ `Front`
- L32 _public enumerator_ `Center`
- L33 _public enumerator_ `Back`

#### class `UActorModifierJustifyModifier`  
`class UActorModifierJustifyModifier : public UActorModifierArrangeBaseModifier`  
_L42-163_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierArrangeBaseModifier`
- desc: Justify Modifier Aligns child actors, based on their bounding box, according to the specified justification
- L48 _public prototype_ `void SetHorizontalAlignment(EActorModifierJustifyHorizontal InHorizontalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Justify")`
- L51 _public function_ `EActorModifierJustifyHorizontal GetHorizontalAlignment() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Justify")`
- L57 _public prototype_ `void SetVerticalAlignment(EActorModifierJustifyVertical InVerticalAlignment);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Justify")`
- L60 _public function_ `EActorModifierJustifyVertical GetVerticalAlignment() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Justify")`
- L66 _public prototype_ `void SetDepthAlignment(EActorModifierJustifyDepth InDepthAlignment);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Justify")`
- L69 _public function_ `EActorModifierJustifyDepth GetDepthAlignment() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Justify")`
- L75 _public prototype_ `void SetHorizontalAnchor(float InHorizontalAnchor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Justify")`
- L78 _public function_ `float GetHorizontalAnchor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Justify")`
- L84 _public prototype_ `void SetVerticalAnchor(float InVerticalAnchor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Justify")`
- L87 _public function_ `float GetVerticalAnchor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Justify")`
- L93 _public prototype_ `void SetDepthAnchor(float InDepthAnchor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Justify")`
- L96 _public function_ `float GetDepthAnchor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Justify")`
- L104 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L109 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L110 _protected prototype_ `virtual bool IsModifierDirtyable() const override;`
- L111 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L112 _protected prototype_ `virtual void Apply() override;`
- L116 _protected prototype_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L120 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L121 _protected prototype_ `virtual void OnActorVisibilityChanged(AActor* InActor) override;`
- L125 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L129 _protected prototype_ `void GetChildrenActors(TSet<TWeakObjectPtr<AActor>>& OutChildren) const;` — Get tracked actors from children actors
- L130 _protected prototype_ `void GetTrackedActors(const TSet<TWeakObjectPtr<AActor>>& InChildrenActors, TArray<TWeakObjectPtr<const AActor>>& OutTrackedActors) const;`
- L132 _protected prototype_ `bool HasDepthAlignment() const;`
- L133 _protected prototype_ `bool HasHorizontalAlignment() const;`
- L134 _protected prototype_ `bool HasVerticalAlignment() const;`
- L136 _protected prototype_ `FVector GetConstraintVector(const FVector& InBoundsCenter, const FVector& InModifiedActorPosition) const;`
- L137 _protected prototype_ `FVector MakeConstrainedAxisVector() const;`
- L138 _protected prototype_ `FVector GetAnchorOffset() const;`
- L139 _protected prototype_ `FVector GetAlignmentOffset(const FVector& InExtent) const;`
- L142 _protected member_ `EActorModifierJustifyHorizontal HorizontalAlignment;` — `UPROPERTY(EditInstanceOnly, Setter="SetHorizontalAlignment", Getter="GetHorizontalAlignment", Category="Justify", meta=(AllowPrivateAccess="true"))`
- L145 _protected member_ `EActorModifierJustifyVertical VerticalAlignment;` — `UPROPERTY(EditInstanceOnly, Setter="SetVerticalAlignment", Getter="GetVerticalAlignment", Category="Justify", meta=(AllowPrivateAccess="true"))`
- L148 _protected member_ `EActorModifierJustifyDepth DepthAlignment;` — `UPROPERTY(EditInstanceOnly, Setter="SetDepthAlignment", Getter="GetDepthAlignment", Category="Justify", meta=(AllowPrivateAccess="true"))`
- L151 _protected member_ `float HorizontalAnchor;` — `UPROPERTY(EditInstanceOnly, Setter="SetHorizontalAnchor", Getter="GetHorizontalAnchor", Interp, Category="Justify", meta=(EditCondition="HorizontalAlignment != EActorModifierJustifyHorizontal::None", EditConditionHides, AllowPrivateAccess="true"))`
- L154 _protected member_ `float VerticalAnchor;` — `UPROPERTY(EditInstanceOnly, Setter="SetVerticalAnchor", Getter="GetVerticalAnchor", Interp, Category="Justify", meta=(EditCondition="VerticalAlignment != EActorModifierJustifyVertical::None", EditConditionHides, AllowPrivateAccess="true"))`
- L157 _protected member_ `float DepthAnchor;` — `UPROPERTY(EditInstanceOnly, Setter="SetDepthAnchor", Getter="GetDepthAnchor", Interp, Category="Justify", meta=(EditCondition = "DepthAlignment != EActorModifierJustifyDepth::None", EditConditionHides, AllowPrivateAccess="true"))`
- L162 _private member_ `FBox CachedTrackedBounds = FBox(EForceInit::ForceInit);` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Cached actors bounds to detect a change in tick

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout/Public/Modifiers/ActorModifierLookAtModifier.h` (Public)


#### class `UActorModifierLookAtModifier`  
`class UActorModifierLookAtModifier : public UActorModifierAttachmentBaseModifier , public IActorModifierTransformUpdateHandler`  
_L16-103_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierAttachmentBaseModifier,IActorModifierTransformUpdateHandler`
- desc: Rotates the modifying actor to point it's specified axis at another actor.
- L23 _public prototype_ `void SetReferenceActor(const FActorModifierSceneTreeActor& InReferenceActor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|LookAt")`
- L26 _public function_ `const FActorModifierSceneTreeActor& GetReferenceActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|LookAt")`
- L33 _public prototype_ `void SetOrientationAxis(EActorModifierAxis InAxis);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|LookAt")` — Sets the axis that will point towards the reference actor.
- L37 _public function_ `EActorModifierAxis GetOrientationAxis() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|LookAt")` — Returns the axis that will point towards the reference actor.
- L44 _public prototype_ `void SetFlipAxis(const bool bInFlipAxis);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|LookAt")` — Sets the look-at direction to be flipped.
- L48 _public function_ `bool GetFlipAxis() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|LookAt")` — Returns true if flipping the look-at rotation axis.
- L55 _protected prototype_ `virtual void PostLoad() override;`
- L57 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L58 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& TransactionEvent) override;`
- L63 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L64 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L65 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L66 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L67 _protected prototype_ `virtual void Apply() override;`
- L68 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L72 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L76 _protected prototype_ `virtual void OnSceneTreeTrackedActorChanged(int32 InIdx, AActor* InPreviousActor, AActor* InNewActor) override;`
- L79 _protected prototype_ `void OnReferenceActorChanged();`
- L82 _protected member_ `FActorModifierSceneTreeActor ReferenceActor;` — `UPROPERTY(EditInstanceOnly, Setter="SetReferenceActor", Getter="GetReferenceActor", Category="LookAt", meta=(ShowOnlyInnerProperties, AllowPrivateAccess="true"))`
- L86 _protected member_ `EActorModifierAxis OrientationAxis = EActorModifierAxis::None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="LookAt", meta=(AllowPrivateAccess="true"))` — The axis to orient look at
- L90 _protected member_ `bool bFlipAxis = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetFlipAxis", Getter="GetFlipAxis", Category="LookAt", meta=(AllowPrivateAccess="true"))` — If true, will flip the look-at direction.
- L94 _protected member_ `TWeakObjectPtr<AActor> ReferenceActorWeak;` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use ReferenceActor instead"))` — The actor to look at.
- L99 _protected member_ `EActorModifierAlignment Axis;` — `UE_DEPRECATED(5.6, "Use OrientationAxis instead")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use OrientationAxis instead"))` — The axis that will point towards the reference actor.
- L102 _protected member_ `bool bDeprecatedPropertiesMigrated = false;` — `UPROPERTY()`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout/Public/Modifiers/ActorModifierRadialArrangeModifier.h` (Public)


#### enum `EActorModifierRadialArrangeMode`  
`enum class EActorModifierRadialArrangeMode : uint8`  
_L11-23_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies how child elements will be arranged radially.
- L17 _public enumerator_ `Monospace` — Each radial ring will contain the same number of elements. The space between elements in the outer rings will be greater than the inner rings.
- L22 _public enumerator_ `Equal` — All elements in all radial rings have the same spacing between them. The number of elements in the inner rings will be greater than the outer rings.

#### enum `EActorModifierRadialArrangePlane`  
`enum class EActorModifierRadialArrangePlane : uint8`  
_L27-32_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates how to layout the ring
- L29 _public enumerator_ `XY`
- L30 _public enumerator_ `YZ`
- L31 _public enumerator_ `XZ`

#### class `UActorModifierRadialArrangeModifier`  
`class UActorModifierRadialArrangeModifier : public UActorModifierArrangeBaseModifier`  
_L38-241_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierArrangeBaseModifier`
- desc: Arranges child actors in a circular rings around its center
- L45 _public prototype_ `void SetCount(const int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the number of child elements to use in the arrangement. Children whose index is greater than or equal to this value will be hidden.
- L49 _public function_ `int32 GetCount() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the number of child elements to use in the arrangement. Children whose index is greater than or equal to this value will be hidden.
- L56 _public prototype_ `void SetRings(const int32 InRings);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the number of rings.
- L60 _public function_ `int32 GetRings() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the number of rings.
- L67 _public prototype_ `void SetInnerRadius(const float InInnerRadius);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the radius from the center to the first inner ring.
- L71 _public function_ `float GetInnerRadius() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the radius from the center to the first inner ring.
- L78 _public prototype_ `void SetOuterRadius(const float InOuterRadius);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the radius from the center to the last outer ring.
- L82 _public function_ `float GetOuterRadius() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the radius from the center to the last outer ring.
- L89 _public prototype_ `void SetStartAngle(const float InStartAngle);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the start angle for the arrangement space and moving clockwise. 0 = Up, -90 = Left, 90 = Right
- L93 _public function_ `float GetStartAngle() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the start angle for the arrangement space and moving clockwise. 0 = Up, -90 = Left, 90 = Right
- L100 _public prototype_ `void SetEndAngle(const float InEndAngle);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the end angle for the arrangement space. 0 = Up, -90 = Left, 90 = Right
- L104 _public function_ `float GetEndAngle() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the end angle for the arrangement space. 0 = Up, -90 = Left, 90 = Right
- L111 _public prototype_ `void SetArrangement(const EActorModifierRadialArrangeMode InArrangement);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Defines how to arrange the child elements around the center.
- L115 _public function_ `EActorModifierRadialArrangeMode GetArrangement() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Defines how to arrange the child elements around the center.
- L122 _public prototype_ `void SetStartFromOuterRadius(const bool bInStartFromOuterRadius);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — If true, will arrange the child elements starting from the outer radius and moving to the inner radius. Has no effect if only using one ring.
- L126 _public function_ `bool GetStartFromOuterRadius() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — If true, will arrange the child elements starting from the outer radius and moving to the inner radius. Has no effect if only using one ring.
- L133 _public prototype_ `void SetOrient(const bool bInOrient);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — If true, will orient the selected axis torwards the center.
- L137 _public function_ `bool GetOrient() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — If true, will orient the selected axis torwards the center.
- L144 _public prototype_ `void SetOrientationAxis(EActorModifierAxis InAxis);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the axis to look at the center.
- L148 _public function_ `EActorModifierAxis GetOrientationAxis() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the axis to look at the center.
- L155 _public prototype_ `void SetBaseOrientation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — Sets the base rotation
- L159 _public function_ `const FRotator& GetBaseOrientation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — Gets the base rotation
- L166 _public prototype_ `void SetFlipOrient(const bool bInFlipOrient);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|RadialArrange")` — If true, will flip the center orientation to face outwards.
- L170 _public function_ `bool GetFlipOrient() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|RadialArrange")` — If true, will flip the center orientation to face outwards.
- L177 _protected prototype_ `virtual void PostLoad() override;`
- L179 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L184 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L185 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L186 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L187 _protected prototype_ `virtual void Apply() override;`
- L192 _protected member_ `int32 Count = -1;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="RadialArrange", meta=(ClampMin="-1", UIMin="-1", AllowPrivateAccess="true"))` — The number of child elements to limit in the arrangement, or -1 if unlimited. Children whose index is greater than or equal to this value will be hidden.
- L196 _protected member_ `int32 Rings = 1;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="RadialArrange", meta=(ClampMin="1", UIMin="1", AllowPrivateAccess="true"))` — The number of rings.
- L200 _protected member_ `float InnerRadius = 70.0f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Interp, Category="RadialArrange", meta=(ClampMin="0.0", UIMin="0.0", AllowPrivateAccess="true"))` — The radius from the center to the first inner ring.
- L204 _protected member_ `float OuterRadius = 200.0f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Interp, Category="RadialArrange", meta=(EditCondition="Rings > 1", EditConditionHides, ClampMin="0.0", UIMin="0.0", AllowPrivateAccess="true"))` — The radius from the center to the last outer ring.
- L208 _protected member_ `float StartAngle = -180.0f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Interp, Category="RadialArrange", meta=(ClampMin="-180.0", UIMin="-180.0", ClampMax="180.0", UIMax="180.0", AllowPrivateAccess="true"))` — The start angle for the arrangement space and moving clockwise. 0 = Up, -90 = Left, 90 = Right
- L212 _protected member_ `float EndAngle = 180.0f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Interp, Category="RadialArrange", meta=(ClampMin = "-180.0", UIMin = "-180.0", ClampMax = "180.0", UIMax = "180.0", AllowPrivateAccess="true"))` — The end angle for the arrangement space. 0 = Up, -90 = Left, 90 = Right
- L216 _protected member_ `EActorModifierRadialArrangeMode Arrangement = EActorModifierRadialArrangeMode::Equal;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="RadialArrange", meta=(AllowPrivateAccess="true"))` — Defines how to arrange the child elements around the center.
- L220 _protected member_ `bool bStartFromOuterRadius = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetStartFromOuterRadius", Getter="GetStartFromOuterRadius", Category="RadialArrange", meta=(AllowPrivateAccess="true"))` — If true, will arrange the child elements starting from the outer radius and moving to the inner radius. Has no effect if only using one ring.
- L224 _protected member_ `bool bOrient = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrient", Getter="GetOrient", Category="RadialArrange", meta=(AllowPrivateAccess="true"))` — If true, will orient the selected axis torwards the center.
- L228 _protected member_ `EActorModifierAxis OrientationAxis = EActorModifierAxis::None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="RadialArrange", meta=(EditCondition="bOrient", EditConditionHides, AllowPrivateAccess="true"))` — The axis to look at the center.
- L232 _protected member_ `FRotator BaseOrientation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="RadialArrange", meta=(EditCondition="bOrient", EditConditionHides, AllowPrivateAccess="true"))` — Base rotation added on top of the orientation rotation computed
- L236 _protected member_ `EActorModifierAlignment OrientAxis;` — `UE_DEPRECATED(5.5, "Use OrientationAxis instead")` — `UPROPERTY(meta=(DeprecatedProperty, DeprecationMessage="Use OrientationAxis instead"))`
- L240 _protected member_ `bool bFlipOrient = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetFlipOrient", Getter="GetFlipOrient", Category="RadialArrange", meta=(EditCondition="bOrient", EditConditionHides, AllowPrivateAccess="true"))` — If true, will flip the orientation axis to the opposite direction.

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierLayout/Public/Modifiers/ActorModifierSplinePathModifier.h` (Public)


#### enum `EActorModifierLayoutSplinePathSampleMode`  
`enum class EActorModifierLayoutSplinePathSampleMode : uint8`  
_L14-20_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Percentage`
- L17 _public enumerator_ `Distance`
- L18 _public enumerator_ `Time`
- L19 _public enumerator_ `Point`

#### class `UActorModifierSplinePathModifier`  
`class UActorModifierSplinePathModifier : public UActorModifierCoreBase , public IActorModifierRenderStateUpdateHandler , public IActorModifierTransformUpdateHandler`  
_L26-194_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierCoreBase,IActorModifierRenderStateUpdateHandler,IActorModifierTransformUpdateHandler`
- desc: This modifier allows to sample a spline and update the actor transform based on the spline path
- L34 _public prototype_ `static FName GetSplineActorWeakPropertyName();`
- L37 _public prototype_ `void SetSplineActorWeak(TWeakObjectPtr<AActor> InActor);`
- L38 _public function_ `TWeakObjectPtr<AActor> GetSplineActorWeak() const`
- L44 _public prototype_ `void SetSplineActor(AActor* InActor);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L47 _public function_ `AActor* GetSplineActor() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L53 _public prototype_ `void SetSampleMode(EActorModifierLayoutSplinePathSampleMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L56 _public function_ `EActorModifierLayoutSplinePathSampleMode GetSampleMode() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L62 _public prototype_ `void SetProgress(float InProgress);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L65 _public function_ `float GetProgress() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L71 _public prototype_ `void SetDistance(float InDistance);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L74 _public function_ `float GetDistance() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L80 _public prototype_ `void SetTime(float InTime);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L83 _public function_ `float GetTime() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L89 _public prototype_ `void SetPointIndex(int32 InIndex);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L92 _public function_ `int32 GetPointIndex() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L98 _public prototype_ `void SetOrient(bool bInOrient);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L101 _public function_ `bool GetOrient() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L107 _public prototype_ `void SetBaseOrientation(const FRotator& InOrientation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L110 _public function_ `const FRotator& GetBaseOrientation() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L116 _public prototype_ `void SetScale(bool bInScale);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|SplinePath")`
- L119 _public function_ `bool GetScale() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|SplinePath")`
- L127 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L132 _protected prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override;`
- L133 _protected function_ `virtual void OnActorVisibilityChanged(AActor* InActor) override`
- L137 _protected prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override;`
- L141 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L142 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L143 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L144 _protected prototype_ `virtual void Apply() override;`
- L147 _protected prototype_ `void OnSplineActorWeakChanged();`
- L148 _protected prototype_ `void OnSplineOptionsChanged();`
- L152 _protected member_ `TWeakObjectPtr<AActor> SplineActorWeak;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="SplinePath", meta=(FilterActorByComponentClass="/Script/Engine.SplineComponent", AllowPrivateAccess="true"))` — Spline actor to retrieve the USplineComponent from
- L156 _protected member_ `EActorModifierLayoutSplinePathSampleMode SampleMode = EActorModifierLayoutSplinePathSampleMode::Percentage;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="SplinePath", meta=(AllowPrivateAccess="true"))` — How to sample the spline
- L160 _protected member_ `float Progress = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="SplinePath", meta=(EditCondition="SampleMode == EActorModifierLayoutSplinePathSampleMode::Percentage", EditConditionHides, Units=Percent, AllowPrivateAccess="true"))` — Percentage progress to sample the spline at
- L164 _protected member_ `float Distance = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="SplinePath", meta=(EditCondition="SampleMode == EActorModifierLayoutSplinePathSampleMode::Distance", EditConditionHides, Units=Centimeters, AllowPrivateAccess="true"))` — Distance to sample the spline at
- L168 _protected member_ `float Time = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="SplinePath", meta=(EditCondition="SampleMode == EActorModifierLayoutSplinePathSampleMode::Time", EditConditionHides, AllowPrivateAccess="true"))` — Time to sample the spline at
- L172 _protected member_ `int32 PointIndex = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="SplinePath", meta=(EditCondition="SampleMode == EActorModifierLayoutSplinePathSampleMode::Point", EditConditionHides, AllowPrivateAccess="true"))` — Point index to sample the spline at
- L176 _protected member_ `bool bOrient = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrient", Getter="GetOrient", Category="SplinePath", meta=(AllowPrivateAccess="true"))` — Orient actor based on spline tangent
- L180 _protected member_ `FRotator BaseOrientation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="SplinePath", meta=(EditCondition="bOrient", EditConditionHides, AllowPrivateAccess="true"))` — Base rotation added on top of the orientation rotation computed
- L184 _protected member_ `bool bScale = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetScale", Getter="GetScale", Category="SplinePath", meta=(AllowPrivateAccess="true"))` — Apply scale based on spline point scale
- L188 _protected member_ `TWeakObjectPtr<USplineComponent> SplineComponentWeak;` — `UPROPERTY()` — Spline component found on the spline actor
- L192 _private member_ `static const TActorModifierPropertyChangeDispatcher<UActorModifierSplinePathModifier> PropertyChangeDispatcher;`
