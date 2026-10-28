# Plugins / ActorModifierRendering

- module root: `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierRendering`
- headers: 1; symbols: 14
- symbol kinds: class=1, function=1, member=3, prototype=9
- PrivateDependencyModuleNames: CompositeCore, CoreUObject, Engine
- PublicDependencyModuleNames: ActorModifier, ActorModifierCore, Core

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifierRendering/Public/Modifiers/ActorModifierHoldoutCompositeModifier.h` (Public)


#### class `UActorModifierHoldoutCompositeModifier`  
`class UActorModifierHoldoutCompositeModifier : public UActorModifierAttachmentBaseModifier`  
_L16-62_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorModifierAttachmentBaseModifier`
- desc: Track primitive components to render them in a separate pass and composites it back using an alpha holdout mask
- L22 _public prototype_ `void SetIncludeChildren(bool bInInclude);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Holdout")`
- L25 _public function_ `bool GetIncludeChildren() const` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Holdout")`
- L33 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L38 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L39 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L40 _protected prototype_ `virtual void RestorePreState() override;`
- L41 _protected prototype_ `virtual void Apply() override;`
- L45 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L48 _protected prototype_ `void OnIncludeChildrenChanged();`
- L49 _protected prototype_ `void UnregisterPrimitiveComponents();`
- L53 _protected member_ `bool bIncludeChildren = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetIncludeChildren", Getter="GetIncludeChildren", Category="HoldoutComposite", meta=(AllowPrivateAccess="true"))` — If true, will apply itself onto children actors as well
- L57 _protected member_ `TSet<TWeakObjectPtr<UPrimitiveComponent>> PrimitiveComponentsWeak;` — `UPROPERTY()` — Primitive components tracked by the composite subsystem
- L61 _protected member_ `FActorModifierSceneTreeActor ReferenceActor;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Used to track self modified actor for changes
