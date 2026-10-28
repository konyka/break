# Plugins / ActorModifier

- module root: `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier`
- headers: 10; symbols: 248
- symbol kinds: class=15, delegate=2, enum=8, enumerator=33, function=37, member=43, namespace=3, prototype=100, struct=6, typedef=1
- PrivateDependencyModuleNames: CoreUObject, Engine, Slate, SlateCore
- PublicDependencyModuleNames: ActorModifierCore, Core

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/ActorModifierTypes.h` (Public)


#### enum `EActorModifierAxis`  
`enum class EActorModifierAxis : uint8`  
_L9-15_
- reflection: `UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))`
- L11 _public enumerator_ `None = 0 UMETA(Hidden)`
- L12 _public enumerator_ `X = 1 << 0`
- L13 _public enumerator_ `Y = 1 << 1`
- L14 _public enumerator_ `Z = 1 << 2`

#### enum `EActorModifierVerticalAlignment`  
`enum class EActorModifierVerticalAlignment : uint8`  
_L19-24_
- reflection: `UENUM(BlueprintType)`
- L21 _public enumerator_ `Top`
- L22 _public enumerator_ `Center`
- L23 _public enumerator_ `Bottom`

#### enum `EActorModifierHorizontalAlignment`  
`enum class EActorModifierHorizontalAlignment : uint8`  
_L27-32_
- reflection: `UENUM(BlueprintType)`
- L29 _public enumerator_ `Left`
- L30 _public enumerator_ `Center`
- L31 _public enumerator_ `Right`

#### enum `EActorModifierDepthAlignment`  
`enum class EActorModifierDepthAlignment : uint8`  
_L35-40_
- reflection: `UENUM(BlueprintType)`
- L37 _public enumerator_ `Front`
- L38 _public enumerator_ `Center`
- L39 _public enumerator_ `Back`

#### enum `EActorModifierAlignment`  
`enum class EActorModifierAlignment : uint8`  
_L43-48_
- reflection: `UENUM(BlueprintType)`
- L45 _public enumerator_ `Horizontal`
- L46 _public enumerator_ `Vertical`
- L47 _public enumerator_ `Depth`

#### struct `FActorModifierAnchorAlignment`  
`struct FActorModifierAnchorAlignment`  
_L52-90_
- reflection: `USTRUCT(BlueprintType)`
- desc: Specifies a set of anchor alignments, one for each 3D axis.
- L57 _public member_ `bool bUseHorizontal = true;` — `UPROPERTY()`
- L60 _public member_ `bool bUseVertical = true;` — `UPROPERTY()`
- L63 _public member_ `bool bUseDepth = true;` — `UPROPERTY()`
- L66 _public member_ `EActorModifierHorizontalAlignment Horizontal = EActorModifierHorizontalAlignment::Center;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnchorAlignment", meta=(EditCondition="bUseHorizontal", EditConditionHides))`
- L69 _public member_ `EActorModifierVerticalAlignment Vertical = EActorModifierVerticalAlignment::Center;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnchorAlignment", meta=(EditCondition="bUseVertical", EditConditionHides))`
- L72 _public member_ `EActorModifierDepthAlignment Depth = EActorModifierDepthAlignment::Center;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AnchorAlignment", meta=(EditCondition="bUseDepth", EditConditionHides))`
- L74 _public function_ `FActorModifierAnchorAlignment()`
- L75 _public function_ `FActorModifierAnchorAlignment(const EActorModifierHorizontalAlignment InHorizontal, const EActorModifierVerticalAlignment InVertical, const EActorModifierDepthAlignment InDepth) : Horizontal(InHorizontal), Vertical(InVertical), Depth(InDepth)`
- L79 _public function_ `bool operator==(const FActorModifierAnchorAlignment& Other) const`
- L84 _public function_ `bool IsHorizontalMatch(const FActorModifierAnchorAlignment& Other) const`
- L85 _public function_ `bool IsVerticalMatch(const FActorModifierAnchorAlignment& Other) const`
- L86 _public function_ `bool IsDepthMatch(const FActorModifierAnchorAlignment& Other) const`
- L89 _public prototype_ `FVector LocalBoundsOffset(const FBox& InBounds, const bool bInInverted = false) const;` — Returns a point on the bounds extent determined by the alignment properties of the structure.

#### Free symbols / members of external scopes

- L16 _prototype_ `ENUM_CLASS_FLAGS(EActorModifierAxis);`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Extensions/ActorModifierRenderStateUpdateExtension.h` (Public)


#### class `UActorModifierRenderStateUpdateHandler`  
`class UActorModifierRenderStateUpdateHandler : public UInterface`  
_L14-17_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IActorModifierRenderStateUpdateHandler`  
`class IActorModifierRenderStateUpdateHandler`  
_L20-39_
- desc: Implement this interface to handle extension event
- L29 _public function_ `virtual UE::ActorModifierCore::ERenderStateDirtyReason GetRenderStateDirtyEventTypes() const` — Returns the relevant render state dirty event types relevant to this handler Defaults to all for legacy
- L35 _public prototype_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) = 0;` — Callback when a render state actor in this world changes
- L38 _public prototype_ `virtual void OnActorVisibilityChanged(AActor* InActor) = 0;` — Callback when a tracked actor visibility has changed

#### class `FActorModifierRenderStateUpdateExtension`  
`class FActorModifierRenderStateUpdateExtension : public FActorModifierCoreExtension`  
_L45-84_
- inherits: `FActorModifierCoreExtension`
- desc: This extension tracks specific actors for render state updates, when an update happens it will invoke IAvaRenderStateUpdateExtension function
- L49 _public prototype_ `explicit FActorModifierRenderStateUpdateExtension(TNotNull<IActorModifierRenderStateUpdateHandler*> InExtensionHandler);`
- L52 _public prototype_ `void TrackActorVisibility(AActor* InActor);` — Adds an actor to track for visibility
- L55 _public prototype_ `void UntrackActorVisibility(AActor* InActor);` — Removes a tracked actor for visibility
- L58 _public prototype_ `bool IsActorVisibilityTracked(AActor* InActor) const;` — Checks if actor is tracked for visibility
- L61 _public prototype_ `void SetTrackedActorsVisibility(const TSet<TWeakObjectPtr<AActor>>& InActors);` — Sets current tracked actors, removes any actors not included
- L64 _public prototype_ `void SetTrackedActorVisibility(AActor* InActor, bool bInIncludeChildren);` — Sets current tracked actors with actor and its children, removes any actors not included
- L68 _protected prototype_ `virtual void OnExtensionEnabled(EActorModifierCoreEnableReason InReason) override;`
- L69 _protected prototype_ `virtual void OnExtensionDisabled(EActorModifierCoreDisableReason InReason) override;`
- L73 _private prototype_ `void OnRenderStateDirty(UActorComponent& InComponent);`
- L75 _private prototype_ `void BindDelegate();`
- L76 _private prototype_ `void UnbindDelegate();`
- L78 _private member_ `TWeakInterfacePtr<IActorModifierRenderStateUpdateHandler> ExtensionHandlerWeak;`
- L80 _private member_ `TMap<TWeakObjectPtr<AActor>, bool> TrackedActorsVisibility;`
- L83 _private member_ `UE::ActorModifierCore::ERenderStateDirtyReason RelevantReasons;` — The render state dirty reasons that are relevant to this extension

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Extensions/ActorModifierSceneTreeUpdateExtension.h` (Public)


#### enum `EActorModifierReferenceContainer`  
`enum class EActorModifierReferenceContainer : uint8`  
_L14-26_
- reflection: `UENUM(BlueprintType)`
- desc: Specifies the method for finding a reference actor based on it's position in the parent's hierarchy.
- L17 _public enumerator_ `Previous` — Uses the previous actor in the parent's hierarchy.
- L19 _public enumerator_ `Next` — Uses the next actor in the parent's hierarchy.
- L21 _public enumerator_ `First` — Uses the first actor in the parent's hierarchy.
- L23 _public enumerator_ `Last` — Uses the last actor in the parent's hierarchy.
- L25 _public enumerator_ `Other` — Uses a specified reference actor set by the user.

#### struct `FActorModifierSceneTreeActor`  
`struct FActorModifierSceneTreeActor`  
_L29-86_
- reflection: `USTRUCT(BlueprintType)`
- L35 _public prototype_ `FActorModifierSceneTreeActor() = default;`
- L37 _public function_ `explicit FActorModifierSceneTreeActor(AActor* InActor) : ReferenceContainer(EActorModifierReferenceContainer::Other) , ReferenceActorWeak(InActor)`
- L44 _public member_ `EActorModifierReferenceContainer ReferenceContainer = EActorModifierReferenceContainer::Other;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Outliner")` — The method for finding a reference actor based on it's position in the parent's hierarchy
- L48 _public member_ `TWeakObjectPtr<AActor> ReferenceActorWeak = nullptr;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Outliner", meta=(DisplayName="Reference Actor", EditCondition = "ReferenceContainer == EActorModifierReferenceContainer::Other"))` — The actor being followed by the modifier. This is user selectable if the Reference Container is set to "Other"
- L52 _public member_ `bool bSkipHiddenActors = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Outliner", meta=(EditCondition="ReferenceContainer != EActorModifierReferenceContainer::Other", EditConditionHides))` — If true, will search for the next visible actor based on the selected reference container
- L54 _public function_ `bool operator==(const FActorModifierSceneTreeActor& InOther) const`
- L61 _public function_ `AActor* GetLocalActor() const`
- L69 _protected member_ `TSet<TWeakObjectPtr<AActor>> ReferenceActorChildrenWeak;` — `UPROPERTY(Transient)` — All children of reference actor to compare with new set children for changes
- L73 _protected member_ `TArray<TWeakObjectPtr<AActor>> ReferenceActorDirectChildrenWeak;` — `UPROPERTY(Transient)` — Direct children of reference actor where order counts
- L77 _protected member_ `TArray<TWeakObjectPtr<AActor>> ReferenceActorsWeak;` — `UPROPERTY(Transient)` — Tracked references actors, if we skip hidden actors, we still need to track those for visibility changes, can be rebuilt
- L81 _protected member_ `TArray<TWeakObjectPtr<AActor>> ReferenceActorParentsWeak;` — `UPROPERTY(Transient)` — Parents of the reference actor
- L85 _protected member_ `TWeakObjectPtr<AActor> LocalActorWeak = nullptr;` — `UPROPERTY(Transient)` — Actor from which we start resolving this reference actor

#### class `UActorModifierSceneTreeUpdateHandler`  
`class UActorModifierSceneTreeUpdateHandler : public UInterface`  
_L89-92_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IActorModifierSceneTreeUpdateHandler`  
`class IActorModifierSceneTreeUpdateHandler`  
_L95-109_
- desc: Implement this interface to handle extension event
- L100 _public prototype_ `virtual void OnSceneTreeTrackedActorChanged(int32 InIdx, AActor* InPreviousActor, AActor* InNewActor) = 0;`
- L102 _public prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) = 0;`
- L104 _public prototype_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) = 0;`
- L106 _public prototype_ `virtual void OnSceneTreeTrackedActorParentChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousParentActor, const TArray<TWeakObjectPtr<AActor>>& InNewParentActor) = 0;`
- L108 _public prototype_ `virtual void OnSceneTreeTrackedActorRearranged(int32 InIdx, AActor* InRearrangedActor) = 0;`

#### class `IActorModifierSceneTreeCustomResolver`  
`class IActorModifierSceneTreeCustomResolver : public TSharedFromThis<IActorModifierSceneTreeCustomResolver>`  
_L112-124_
- inherits: `TSharedFromThis<IActorModifierSceneTreeCustomResolver>`
- desc: Helps resolve underlying actors in the scene
- L115 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorHierarchyChanged, AActor* ) virtual ~IActorModifierSceneTreeCustomResolver() = default;`
- L119 _public prototype_ `virtual void Activate() = 0;`
- L120 _public prototype_ `virtual void Deactivate() = 0;`
- L121 _public prototype_ `virtual bool GetDirectChildrenActor(AActor* InActor, TArray<AActor*>& OutActors) const = 0;`
- L122 _public prototype_ `virtual bool GetRootActors(ULevel* InLevel, TArray<AActor*>& OutActors) const = 0;`
- L123 _public prototype_ `virtual FOnActorHierarchyChanged::RegistrationType& OnActorHierarchyChanged() = 0;`

#### class `FActorModifierSceneTreeUpdateExtension`  
`class FActorModifierSceneTreeUpdateExtension : public FActorModifierCoreExtension`  
_L130-179_
- inherits: `FActorModifierCoreExtension`
- desc: This extension tracks specific actors for render state updates, when an update happens it will dirty the modifier it is attached on if filter passes
- L133 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IActorModifierSceneTreeCustomResolver>, FOnGetSceneTreeResolver, ULevel* ) static FOnGetSceneTreeResolver::RegistrationType& OnGetSceneTreeResolver()`
- L139 _public prototype_ `explicit FActorModifierSceneTreeUpdateExtension(IActorModifierSceneTreeUpdateHandler* InExtensionHandler);`
- L141 _public prototype_ `void TrackSceneTree(int32 InTrackedActorIdx, FActorModifierSceneTreeActor* InTrackedActor);`
- L142 _public prototype_ `void UntrackSceneTree(int32 InTrackedActorIdx);`
- L143 _public prototype_ `FActorModifierSceneTreeActor* GetTrackedActor(int32 InTrackedActorIdx) const;`
- L145 _public prototype_ `void CheckTrackedActorsUpdate() const;`
- L146 _public prototype_ `void CheckTrackedActorUpdate(int32 InIdx) const;`
- L148 _public prototype_ `TArray<TWeakObjectPtr<AActor>> GetDirectChildrenActor(AActor* InActor) const;`
- L152 _protected prototype_ `virtual void OnExtensionInitialized() override;`
- L153 _protected prototype_ `virtual void OnExtensionEnabled(EActorModifierCoreEnableReason InReason) override;`
- L154 _protected prototype_ `virtual void OnExtensionDisabled(EActorModifierCoreDisableReason InReason) override;`
- L157 _protected prototype_ `TSet<TWeakObjectPtr<AActor>> GetChildrenActorsRecursive(const AActor* InActor) const;`
- L158 _protected prototype_ `TArray<TWeakObjectPtr<AActor>> GetParentActors(const AActor* InActor) const;`
- L159 _protected prototype_ `TArray<TWeakObjectPtr<AActor>> GetReferenceActors(const FActorModifierSceneTreeActor* InReferenceActor) const;`
- L160 _protected prototype_ `TArray<TWeakObjectPtr<AActor>> GetRootActors(ULevel* InLevel) const;`
- L163 _private member_ `static FOnGetSceneTreeResolver OnGetSceneTreeResolverDelegate;`
- L165 _private prototype_ `void OnRefreshTrackedActors(AActor* InActor);`
- L167 _private prototype_ `void OnRenderStateDirty(UActorComponent& InComponent);`
- L168 _private prototype_ `void OnWorldActorDestroyed(AActor* InActor);`
- L170 _private prototype_ `bool IsSameActorArray(const TArray<TWeakObjectPtr<AActor>>& InPreviousActorWeak, const TArray<TWeakObjectPtr<AActor>>& InNewActorWeak) const;`
- L172 _private member_ `TWeakInterfacePtr<IActorModifierSceneTreeUpdateHandler> ExtensionHandlerWeak;`
- L174 _private member_ `TMap<int32, FActorModifierSceneTreeActor*> TrackedActors;`
- L176 _private member_ `FDelegateHandle WorldActorDestroyedDelegate;`
- L178 _private member_ `TSharedPtr<IActorModifierSceneTreeCustomResolver> SceneTreeResolver;`

#### Free symbols / members of external scopes

- L115 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorHierarchyChanged, AActor* ) virtual ~IActorModifierSceneTreeCustomResolver() = default;`
- L133 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IActorModifierSceneTreeCustomResolver>, FOnGetSceneTreeResolver, ULevel* ) static FOnGetSceneTreeResolver::RegistrationType& OnGetSceneTreeResolver() { return OnGetSceneTreeResolverDelegate; } explicit FActorModifierSceneTreeUpdateExtension(IActorModifierSceneTreeUpdateHandler* InExtensionHandler);`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Extensions/ActorModifierTransformUpdateExtension.h` (Public)


#### class `UActorModifierTransformUpdateHandler`  
`class UActorModifierTransformUpdateHandler : public UInterface`  
_L10-13_
- reflection: `UINTERFACE(MinimalAPI, NotBlueprintType, meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IActorModifierTransformUpdateHandler`  
`class IActorModifierTransformUpdateHandler`  
_L16-23_
- desc: Implement this interface to handle extension event
- L22 _public prototype_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) = 0;` — Callback when a tracked actor transform changes

#### class `FActorModifierTransformUpdateExtension`  
`class FActorModifierTransformUpdateExtension : public FActorModifierCoreExtension`  
_L29-56_
- inherits: `FActorModifierCoreExtension`
- desc: This extension tracks specific actors for transform updates, when an update happens it will invoke the IAvaTransformUpdateExtension function
- L33 _public prototype_ `explicit FActorModifierTransformUpdateExtension(IActorModifierTransformUpdateHandler* InExtensionHandler);`
- L35 _public prototype_ `void TrackActor(AActor* InActor, bool bInReset);`
- L36 _public prototype_ `void UntrackActor(AActor* InActor);`
- L38 _public prototype_ `void TrackActors(const TSet<TWeakObjectPtr<AActor>>& InActors, bool bInReset);`
- L39 _public prototype_ `void UntrackActors(const TSet<TWeakObjectPtr<AActor>>& InActors);`
- L43 _protected prototype_ `virtual void OnExtensionEnabled(EActorModifierCoreEnableReason InReason) override;`
- L44 _protected prototype_ `virtual void OnExtensionDisabled(EActorModifierCoreDisableReason InReason) override;`
- L48 _private prototype_ `void OnTransformUpdated(USceneComponent* InComponent, EUpdateTransformFlags InFlags, ETeleportType InType);`
- L50 _private prototype_ `void BindDelegate(const AActor* InActor);`
- L51 _private prototype_ `void UnbindDelegate(const AActor* InActor);`
- L53 _private member_ `TWeakInterfacePtr<IActorModifierTransformUpdateHandler> ExtensionHandlerWeak;`
- L55 _private member_ `TSet<TWeakObjectPtr<AActor>> TrackedActors;`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Modifiers/ActorModifierArrangeBaseModifier.h` (Public)


#### class `UActorModifierArrangeBaseModifier`  
`class UActorModifierArrangeBaseModifier : public UActorModifierAttachmentBaseModifier , public IActorModifierRenderStateUpdateHandler , public IActorModifierTransformUpdateHandler`  
_L16-46_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UActorModifierAttachmentBaseModifier,IActorModifierRenderStateUpdateHandler,IActorModifierTransformUpdateHandler`
- desc: Abstract base class for modifiers dealing with arrangement and attachment actors on self
- L24 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L25 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L26 _protected prototype_ `virtual void OnModifiedActorTransformed() override;`
- L30 _protected prototype_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L31 _protected prototype_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) override;`
- L35 _protected function_ `virtual void OnRenderStateUpdated(AActor* InActor, UActorComponent* InComponent) override`
- L36 _protected function_ `virtual void OnActorVisibilityChanged(AActor* InActor) override`
- L40 _protected function_ `virtual void OnTransformUpdated(AActor* InActor, bool bInParentMoved) override`
- L45 _protected member_ `FActorModifierSceneTreeActor ReferenceActor;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Used to track self modified actor for changes

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Modifiers/ActorModifierAttachmentBaseModifier.h` (Public)


#### class `UActorModifierAttachmentBaseModifier`  
`class UActorModifierAttachmentBaseModifier : public UActorModifierCoreBase , public IActorModifierSceneTreeUpdateHandler`  
_L15-36_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UActorModifierCoreBase,IActorModifierSceneTreeUpdateHandler`
- desc: Abstract base class for all modifiers that deal with attachments
- L22 _protected prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L23 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L27 _protected function_ `virtual void OnSceneTreeTrackedActorChanged(int32 InIdx, AActor* InPreviousActor, AActor* InNewActor) override`
- L28 _protected function_ `virtual void OnSceneTreeTrackedActorChildrenChanged(int32 InIdx, const TSet<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TSet<TWeakObjectPtr<AActor>>& InNewChildrenActors) override`
- L29 _protected function_ `virtual void OnSceneTreeTrackedActorDirectChildrenChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousChildrenActors, const TArray<TWeakObjectPtr<AActor>>& InNewChildrenActors) override`
- L30 _protected function_ `virtual void OnSceneTreeTrackedActorParentChanged(int32 InIdx, const TArray<TWeakObjectPtr<AActor>>& InPreviousParentActor, const TArray<TWeakObjectPtr<AActor>>& InNewParentActor) override`
- L31 _protected function_ `virtual void OnSceneTreeTrackedActorRearranged(int32 InIdx, AActor* InRearrangedActor) override`
- L35 _protected member_ `TSet<TWeakObjectPtr<AActor>> ChildrenActorsWeak;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Shared/ActorModifierTransformShared.h` (Public)


#### enum `EActorModifierTransformSharedState`  
`enum class EActorModifierTransformSharedState : uint8`  
_L14-24_
- reflection: `UENUM()`
- desc: Enumerates all transform state that can be saved
- L16 _public enumerator_ `None`
- L17 _public enumerator_ `Location = 1 << 0`
- L18 _public enumerator_ `Rotation = 1 << 1`
- L19 _public enumerator_ `Scale = 1 << 2`
- L20 _public enumerator_ `LocationRotation = Location | Rotation`
- L21 _public enumerator_ `LocationScale = Location | Scale`
- L22 _public enumerator_ `RotationScale = Rotation | Scale`
- L23 _public enumerator_ `All = Location | Rotation | Scale`

#### struct `FActorModifierTransformSharedModifierState`  
`struct FActorModifierTransformSharedModifierState`  
_L27-63_
- reflection: `USTRUCT()`
- L31 _public function_ `FActorModifierTransformSharedModifierState()`
- L32 _public function_ `FActorModifierTransformSharedModifierState(UActorModifierCoreBase* InModifier) : ModifierWeak(InModifier)`
- L37 _public prototype_ `void Save(const AActor* InActor, EActorModifierTransformSharedState InSaveState);` — Save this modifier state if valid
- L40 _public prototype_ `void Restore(AActor* InActor, EActorModifierTransformSharedState InRestoreState);` — Restore this modifier state if valid
- L47 _public function_ `bool operator==(const FActorModifierTransformSharedModifierState& Other) const`
- L54 _public member_ `TWeakObjectPtr<UActorModifierCoreBase> ModifierWeak;` — `UPROPERTY()` — Modifier applying the transform change
- L58 _public member_ `FTransform ActorTransform;` — `UPROPERTY()` — Pre modifier transform saved
- L62 _public member_ `EActorModifierTransformSharedState SaveState = EActorModifierTransformSharedState::None;` — `UPROPERTY()` — Used to restore only what has changed

#### struct `FActorModifierTransformSharedActorState`  
`struct FActorModifierTransformSharedActorState`  
_L66-106_
- reflection: `USTRUCT()`
- L70 _public function_ `FActorModifierTransformSharedActorState()`
- L71 _public function_ `FActorModifierTransformSharedActorState(AActor* InActor) : ActorWeak(InActor)`
- L76 _public prototype_ `void Save(EActorModifierTransformSharedState InSaveState);` — Save this actor state if valid
- L79 _public prototype_ `void Restore(EActorModifierTransformSharedState InRestoreState);` — Restore this actor state if valid
- L86 _public function_ `bool operator==(const FActorModifierTransformSharedActorState& Other) const`
- L93 _public member_ `TSet<FActorModifierTransformSharedModifierState> ModifierStates;` — `UPROPERTY()` — Modifiers that are currently watching this state and locking it
- L97 _public member_ `TWeakObjectPtr<AActor> ActorWeak;` — `UPROPERTY()` — Actor that this state is describing
- L101 _public member_ `FTransform ActorTransform;` — `UPROPERTY()` — Pre state transform saved
- L105 _public member_ `EActorModifierTransformSharedState SaveState = EActorModifierTransformSharedState::None;` — `UPROPERTY()` — Used to restore only what has changed

#### class `UActorModifierTransformShared`  
`class UActorModifierTransformShared : public UActorModifierCoreSharedObject`  
_L115-152_
- reflection: `UCLASS(Hidden, MinimalAPI)`
- inherits: `UActorModifierCoreSharedObject`
- desc: Singleton class for transform modifiers to share data between each other Used because multiple modifier could be watching/updating an actor We want to save the state of that actor once before any modifier changes it and restore it when no other modifier is watching it
- L121 _public prototype_ `void SaveActorState(UActorModifierCoreBase* InModifierContext, AActor* InActor, EActorModifierTransformSharedState InSaveState = EActorModifierTransformSharedState::All);` — Save actor state, adds it if it is not tracked
- L124 _public prototype_ `void RestoreActorState(UActorModifierCoreBase* InModifierContext, AActor* InActor, EActorModifierTransformSharedState InRestoreState = EActorModifierTransformSharedState::All);` — Restore actor state, removes it if no other modifier track that actor state
- L127 _public prototype_ `FActorModifierTransformSharedActorState* FindActorState(AActor* InActor);` — Get the actor state for a specific actor
- L130 _public prototype_ `TSet<FActorModifierTransformSharedActorState*> FindActorsState(UActorModifierCoreBase* InModifierContext);` — Get all actor state related to a modifier
- L133 _public prototype_ `void RestoreActorsState(UActorModifierCoreBase* InModifierContext, const TSet<AActor*>* InActors = nullptr, EActorModifierTransformSharedState InRestoreState = EActorModifierTransformSharedState::All);` — Restore all actors states linked to this modifier
- L136 _public prototype_ `void RestoreActorsState(UActorModifierCoreBase* InModifierContext, const TSet<TWeakObjectPtr<AActor>>& InActors, EActorModifierTransformSharedState InRestoreState = EActorModifierTransformSharedState::All);` — Restore all specified actors linked to this modifier
- L139 _public prototype_ `bool IsActorStateSaved(UActorModifierCoreBase* InModifierContext, AActor* InActor);` — Returns true, if this modifier is tracking this actor
- L142 _public prototype_ `bool IsActorsStateSaved(UActorModifierCoreBase* InModifierContext);` — Returns true, if this modifier is tracking any actor
- L146 _protected prototype_ `virtual void PostLoad() override;`
- L151 _protected member_ `TSet<FActorModifierTransformSharedActorState> ActorStates;` — `UPROPERTY()` — Actor state before any modifier applied to it

#### Free symbols / members of external scopes

- L42 _function_ `friend uint32 GetTypeHash(const FActorModifierTransformSharedModifierState& InItem)`
- L81 _function_ `friend uint32 GetTypeHash(const FActorModifierTransformSharedActorState& InItem)`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Shared/ActorModifierVisibilityShared.h` (Public)


#### enum `EActorModifierVisibilityActor`  
`enum class EActorModifierVisibilityActor : uint8`  
_L13-19_
- reflection: `UENUM(meta=(Bitflags))`
- L15 _public enumerator_ `None = 0`
- L16 _public enumerator_ `Game = 1 << 0`
- L17 _public enumerator_ `Editor = 1 << 1`
- L18 _public enumerator_ `GameAndEditor = Game | Editor`

#### struct `FActorModifierVisibilitySharedModifierState`  
`struct FActorModifierVisibilitySharedModifierState`  
_L23-60_
- reflection: `USTRUCT()`
- L27 _public function_ `FActorModifierVisibilitySharedModifierState()`
- L28 _public function_ `FActorModifierVisibilitySharedModifierState(UActorModifierCoreBase* InModifier) : ModifierWeak(InModifier)`
- L33 _public prototype_ `void Save(const AActor* InActor);` — Save this modifier state if valid
- L36 _public prototype_ `void Restore(AActor* InActor) const;` — Restore this modifier state if valid
- L43 _public function_ `bool operator==(const FActorModifierVisibilitySharedModifierState& Other) const`
- L49 _public member_ `TWeakObjectPtr<UActorModifierCoreBase> ModifierWeak;` — `UPROPERTY()`
- L54 _public member_ `bool bActorHiddenInEditor = false;` — `UPROPERTY()` — Pre state editor visibility saved
- L59 _public member_ `bool bActorHiddenInGame = false;` — `UPROPERTY()` — Pre state game visibility saved

#### struct `FActorModifierVisibilitySharedActorState`  
`struct FActorModifierVisibilitySharedActorState`  
_L63-105_
- reflection: `USTRUCT()`
- L67 _public function_ `FActorModifierVisibilitySharedActorState()`
- L68 _public function_ `FActorModifierVisibilitySharedActorState(AActor* InActor) : ActorWeak(InActor)`
- L73 _public prototype_ `void Save();` — Save this actor state if valid
- L76 _public prototype_ `void Restore() const;` — Restore this actor state if valid
- L83 _public function_ `bool operator==(const FActorModifierVisibilitySharedActorState& Other) const`
- L90 _public member_ `TSet<FActorModifierVisibilitySharedModifierState> ModifierStates;` — `UPROPERTY()` — Modifiers that are currently watching this state and locking it
- L94 _public member_ `TWeakObjectPtr<AActor> ActorWeak;` — `UPROPERTY()` — Actor that this state is describing
- L99 _public member_ `bool bActorHiddenInEditor = false;` — `UPROPERTY()` — Pre state editor visibility saved
- L104 _public member_ `bool bActorHiddenInGame = false;` — `UPROPERTY()` — Pre state game visibility saved

#### class `UActorModifierVisibilityShared`  
`class UActorModifierVisibilityShared : public UActorModifierCoreSharedObject`  
_L114-153_
- reflection: `UCLASS(Hidden, MinimalAPI)`
- inherits: `UActorModifierCoreSharedObject`
- desc: Singleton class for visibility modifiers to share data between each other Used because multiple modifier could be watching/updating an actor We want to save the state of that actor once before any modifier changes it and restore it when no other modifier is watching it
- L120 _public prototype_ `void SaveActorState(UActorModifierCoreBase* InModifierContext, AActor* InActor);` — Watch actor state, adds it if it is not tracked
- L123 _public prototype_ `void RestoreActorState(UActorModifierCoreBase* InModifierContext, AActor* InActor);` — Unwatch actor state, removes it if no other modifier track that actor state
- L126 _public prototype_ `FActorModifierVisibilitySharedActorState* FindActorState(AActor* InActor);` — Gather original state before any modifier is applied if there is one
- L129 _public prototype_ `void SetActorVisibility(UActorModifierCoreBase* InModifierContext, AActor* InActor, bool bInHidden, bool bInRecurse = false, EActorModifierVisibilityActor InActorVisibility = EActorModifierVisibilityActor::GameAndEditor);` — Set actor visibility in game or editor and recurse, tracks original state if not tracked
- L132 _public prototype_ `void SetActorsVisibility(UActorModifierCoreBase* InModifierContext, TArray<AActor*> InActors, bool bInHidden, EActorModifierVisibilityActor InActorVisibility = EActorModifierVisibilityActor::GameAndEditor);` — Set actors visibility in game or editor, tracks original state if not tracked
- L135 _public prototype_ `void RestoreActorsState(UActorModifierCoreBase* InModifierContext, const TSet<AActor*>* InActors = nullptr);` — Unwatch all actors states linked to this modifier
- L137 _public prototype_ `void RestoreActorsState(UActorModifierCoreBase* InModifierContext, const TSet<TWeakObjectPtr<AActor>>& InActors);`
- L140 _public prototype_ `bool IsActorStateSaved(UActorModifierCoreBase* InModifierContext, AActor* InActor);` — Returns true, if this modifier is tracking this actor
- L143 _public prototype_ `bool IsActorsStateSaved(UActorModifierCoreBase* InModifierContext);` — Returns true, if this modifier is tracking any actor
- L147 _protected prototype_ `virtual void PostLoad() override;`
- L152 _protected member_ `TSet<FActorModifierVisibilitySharedActorState> ActorStates;` — `UPROPERTY()` — Actor state before any modifier applied to it

#### Free symbols / members of external scopes

- L20 _prototype_ `ENUM_CLASS_FLAGS(EActorModifierVisibilityActor);`
- L38 _function_ `friend uint32 GetTypeHash(const FActorModifierVisibilitySharedModifierState& InItem)`
- L78 _function_ `friend uint32 GetTypeHash(const FActorModifierVisibilitySharedActorState& InItem)`

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Utilities/ActorModifierActorUtils.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace ActorModifier` (scope `UE`)
- L14 _namespace_ `namespace ActorUtils` (scope `UE::ActorModifier`)
- L17 _prototype_ `bool IsActorVisible(const AActor* InActor);` (scope `UE::ActorModifier::ActorUtils`) — Rendering
- L20 _prototype_ `FBox GetActorsBounds(const TSet<TWeakObjectPtr<AActor>>& InActors, const FTransform& InReferenceTransform, bool bInSkipHidden, bool bInTransformBox);` (scope `UE::ActorModifier::ActorUtils`) — Layout
- L21 _prototype_ `FBox GetActorsBounds(const TSet<TWeakObjectPtr<AActor>>& InActors, const FTransform& InReferenceTransform, bool bInSkipHidden = false);` (scope `UE::ActorModifier::ActorUtils`)
- L22 _prototype_ `FBox GetActorsBounds(AActor* InActor, bool bInIncludeChildren, bool bInSkipHidden = false);` (scope `UE::ActorModifier::ActorUtils`)
- L23 _prototype_ `FBox GetActorBounds(const AActor* InActor);` (scope `UE::ActorModifier::ActorUtils`)
- L24 _prototype_ `FVector GetVectorAxis(int32 InAxis);` (scope `UE::ActorModifier::ActorUtils`)
- L25 _prototype_ `bool IsAxisVectorEquals(const FVector& InVectorA, const FVector& InVectorB, int32 InCompareAxis);` (scope `UE::ActorModifier::ActorUtils`)
- L26 _prototype_ `FOrientedBox GetOrientedBox(const FBox& InLocalBox, const FTransform& InWorldTransform);` (scope `UE::ActorModifier::ActorUtils`)
- L27 _prototype_ `FRotator FindLookAtRotation(const FVector& InEyePosition, const FVector& InTargetPosition, EActorModifierAxis InAxis, bool bInFlipAxis);` (scope `UE::ActorModifier::ActorUtils`)

### `Plugins/VirtualProduction/ActorModifier/Source/ActorModifier/Public/Utilities/ActorModifierPropertyChangeDispatcher.h` (Public)


#### class `TActorModifierPropertyChangeDispatcher`  
`template<typename InClassType> class TActorModifierPropertyChangeDispatcher`  
_L13-34_
- desc: Used to map properties to member functions that will get executed once a property changes
- L16 _public typedef_ `using FMemberFunctionType = typename TMemFunPtrType< false, InClassType, void()>::Type;`
- L18 _public function_ `TActorModifierPropertyChangeDispatcher(std::initializer_list<TPairInitializer<const FName&, const FMemberFunctionType&>> InCallbacks) : PropertyChangedFunctions(InCallbacks)`
- L22 _public function_ `void OnPropertyChanged(InClassType* InObject, const FPropertyChangedEvent& InPropertyChangedEvent) const`
- L33 _private member_ `TMap<FName, FMemberFunctionType> PropertyChangedFunctions;`
