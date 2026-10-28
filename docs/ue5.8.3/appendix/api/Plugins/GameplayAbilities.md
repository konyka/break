# Plugins / GameplayAbilities

- module root: `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities`
- headers: 144; symbols: 5121
- symbol kinds: class=127, delegate=126, enum=74, enumerator=235, function=488, macro=138, member=1477, namespace=50, prototype=2201, struct=197, typedef=6, variable=2
- PrivateDependencyModuleNames: EditorFramework, Niagara, SequenceRecorder, Slate, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, DataRegistry, DeveloperSettings, Engine, GameplayTags, GameplayTasks, MovieScene, NetCore, PhysicsCore

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/AbilitySystemCheatManagerExtension.h` (Private)


#### class `UAbilitySystemCheatManagerExtension`  
`class UAbilitySystemCheatManagerExtension final : public UCheatManagerExtension`  
_L11-49_
- reflection: `UCLASS(NotBlueprintable)`
- inherits: `UCheatManagerExtension`
- desc: Cheats related to GAS
- L16 _public prototype_ `UAbilitySystemCheatManagerExtension();`
- L22 _public prototype_ `void AbilityListGranted() const;` — `UFUNCTION(Exec)` — List all of the Abilities Granted to the owning Player
- L26 _public prototype_ `void AbilityGrant(const FString& AssetSearchString) const;` — `UFUNCTION(Exec)` — Grant a specified GameplayAbility to the owning Player
- L30 _public prototype_ `void AbilityActivate(const FString& PartialName) const;` — `UFUNCTION(Exec)` — Activate a previously granted GameplayAbility on the owning Player
- L34 _public prototype_ `void AbilityCancel(const FString& PartialName) const;` — `UFUNCTION(Exec)` — Cancel a previously activated GameplayAbility on the owning Player
- L40 _public prototype_ `void EffectListActive() const;` — `UFUNCTION(Exec)` — List the Active Gameplay Effects on the owning Player
- L44 _public prototype_ `void EffectApply(const FString& PartialName, float EffectLevel = -1.0f) const;` — `UFUNCTION(Exec)` — Apply a Gameplay Effect on the owning Player
- L48 _public prototype_ `void EffectRemove(const FString& NameOrHandle) const;` — `UFUNCTION(Exec)` — Remove an Active Gameplay Effect on the owning Player

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/AbilitySystemPrivate.h` (Private)


#### enum `UE::AbilitySystem::Private::EAllowPredictiveGEFlags`  
`enum class EAllowPredictiveGEFlags`  
_L11-17_
- desc: These are flags to rollback fixes in live production
- L13 _public enumerator_ `None = 0` — No intentional loopholes, try our best to enforce this rule (preferred, default).
- L14 _public enumerator_ `AllowNativeRemoveByHandle = 1 << 0` — Some games may be relying on RemoveActiveGameplayEffect having only the UFUNCTION BlueprintAuthority check; it was previously not checked in native.
- L15 _public enumerator_ `AllowRemovalByTagRequirements = 1 << 1` — A bug introduced in UE5.3 allowed target tag requirements to remove GE's client-side due to the above.
- L16 _public enumerator_ `AllowGameplayEventToApplyGE = 1 << 2` — Legacy bug allowed Gameplay Events to create a prediction window with which one could apply GE's locally. That causes issues since it's not guaranteed to be communicated to the server.

#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace AbilitySystem` (scope `UE`)
- L8 _namespace_ `namespace Private` (scope `UE::AbilitySystem`)
- L18 _prototype_ `ENUM_CLASS_FLAGS(EAllowPredictiveGEFlags);` (scope `UE::AbilitySystem::Private`)
- L21 _variable_ `inline int32 CVarAllowPredictiveGEFlagsValue = 0;` (scope `UE::AbilitySystem::Private`) — CVar that controls which fixes to the predictive GE code we want to disable (for legacy reasons)
- L22 _variable_ `inline FAutoConsoleVariableRef CVarAllowPredictiveGEFlags(TEXT("AbilitySystem.Fix.AllowPredictiveGEFlags"), CVarAllowPredictiveGEFlagsValue, TEXT("Default: 0 (all fixes, no exceptions).\n \ Use flag 0x1 to allow when removing by Handle in native (legacy). Use flag 0x2 to allow RequirementsTags to remove (bug introduced in UE5.3). Use flag 0x4 to allow Gameplay Events to predictively execute GE's (legacy bug)."));` (scope `UE::AbilitySystem::Private`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/Serialization/InternalGameplayEffectContextNetSerializer.h` (Private)


#### struct `FGameplayEffectContextAccessorForNetSerializer`  
`struct FGameplayEffectContextAccessorForNetSerializer : public FGameplayEffectContext`  
_L10-47_
- inherits: `FGameplayEffectContext`
- desc: Implementation is located in GameplayEffectContextNetSerializer.cpp
- L14 _public prototype_ `void CopyReplicatedFieldsFrom(const FGameplayEffectContextAccessorForNetSerializer& GE);`
- L15 _public prototype_ `void AssignReplicatedFieldsTo(FGameplayEffectContextAccessorForNetSerializer& GE) const;`
- L17 _public function_ `void SetShouldReplicateInstigator(bool bShouldReplicateInstigator)`
- L18 _public function_ `bool ShouldReplicateInstigator() const`
- L20 _public function_ `void SetShouldReplicateEffectCauser(bool bShouldReplicateEffectCauser)`
- L21 _public function_ `bool ShouldReplicateEffectCauser() const`
- L23 _public function_ `void SetShouldReplicateWorldOrigin(bool bShouldReplicateWorldOrigin)`
- L24 _public function_ `bool ShouldReplicateWorldOrigin() const`
- L26 _public function_ `void SetShouldReplicateSourceObject(bool bShouldReplicateSourceObject)`
- L27 _public function_ `bool ShouldReplicateSourceObject() const`
- L29 _public prototype_ `const FHitResult* GetHitResult() const;`
- L30 _public prototype_ `void SetHitResult(TSharedRef<FHitResult> HitResult);`
- L46 _public member_ `static uint16 PropertyToMemberIndex[EPropertyName::PropertyName_ReplicatedPropertyCount];`

#### enum `FGameplayEffectContextAccessorForNetSerializer::EPropertyName`  
`enum EPropertyName : uint32`  
_L33-44_
- L35 _public enumerator_ `PropertyName_Instigator`
- L36 _public enumerator_ `PropertyName_EffectCauser`
- L37 _public enumerator_ `PropertyName_AbilityCDO`
- L38 _public enumerator_ `PropertyName_AbilityLevel`
- L39 _public enumerator_ `PropertyName_SourceObject`
- L40 _public enumerator_ `PropertyName_Actors`
- L41 _public enumerator_ `PropertyName_WorldOrigin`
- L43 _public enumerator_ `PropertyName_ReplicatedPropertyCount`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/Serialization/InternalMinimalGameplayCueReplicationProxyNetSerializer.h` (Private)


#### struct `FMinimalGameplayCueReplicationProxyForNetSerializer`  
`struct FMinimalGameplayCueReplicationProxyForNetSerializer`  
_L15-28_
- reflection: `USTRUCT()`
- L20 _public prototype_ `void CopyReplicatedFieldsFrom(const FMinimalGameplayCueReplicationProxy& ReplicationProxy);`
- L21 _public prototype_ `void AssignReplicatedFieldsTo(FMinimalGameplayCueReplicationProxy& ReplicationProxy) const;`
- L25 _private member_ `TArray<FGameplayTag> Tags;` — `UPROPERTY()`
- L27 _private member_ `TArray<FVector_NetQuantize> Locations;` — `UPROPERTY()`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/Serialization/InternalMinimalReplicationTagCountMapNetSerializer.h` (Private)


#### struct `FMinimalReplicationTagCountMapForNetSerializer`  
`struct FMinimalReplicationTagCountMapForNetSerializer`  
_L13-27_
- reflection: `USTRUCT()`
- L18 _public prototype_ `void CopyReplicatedFieldsFrom(const FMinimalReplicationTagCountMap& TagCountMap);`
- L19 _public prototype_ `void AssignReplicatedFieldsTo(FMinimalReplicationTagCountMap& TagCountMap) const;`
- L21 _public prototype_ `SIZE_T GetTagCount() const;`
- L22 _public prototype_ `void ClampTagCount(SIZE_T MaxTagCount);`
- L26 _private member_ `TArray<FGameplayTag> Tags;` — `UPROPERTY()`
- L29 _function_ `inline SIZE_T FMinimalReplicationTagCountMapForNetSerializer::GetTagCount() const`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/Serialization/MinimalReplicationTagCountMapReplicationFragment.h` (Private)


#### class `UE::Net::FMinimalReplicationTagCountMapReplicationFragment`  
`class FMinimalReplicationTagCountMapReplicationFragment : public FReplicationFragment`  
_L21-42_
- inherits: `FReplicationFragment`
- desc: ReplicationFragment implementation used for Iris backwards compatibility until there's a simple way to markup arbitrary members or declare replicated states in a different manner. That coupled with generic Iris ApplyState functionality and not serializing data into gameplay objects directly would make the need for the fragment and the custom serializer go away. Instead the custom logic would be handled in the ApplyState implementation. @note This is NOT what good looks like. Markup your data and avoid custom gameplay logic in serialization code.
- L24 _public prototype_ `FMinimalReplicationTagCountMapReplicationFragment(EReplicationFragmentTraits InTraits, UObject* InOwner, const FReplicationStateDescriptor* InDescriptor);`
- L26 _public prototype_ `void Register(FFragmentRegistrationContext& Context);`
- L29 _protected prototype_ `virtual void ApplyReplicatedState(FReplicationStateApplyContext& Context) const override;`
- L30 _protected prototype_ `virtual bool PollReplicatedState(EReplicationFragmentPollFlags PollOption) override;`
- L31 _protected prototype_ `virtual void CallRepNotifies(FReplicationStateApplyContext& Context) override;`
- L32 _protected prototype_ `virtual void CollectOwner(FReplicationStateOwnerCollector* Owners) const override;`
- L35 _private prototype_ `void MimicMinimalReplicationTagCountMapReceiveLogic(FReplicationStateApplyContext& Context) const;`
- L36 _private prototype_ `void CallRepNotify(FReplicationStateApplyContext& Context);`
- L39 _private member_ `TRefCountPtr<const FReplicationStateDescriptor> ReplicationStateDescriptor;`
- L40 _private member_ `TUniquePtr<FPropertyReplicationState> SrcReplicationState;`
- L41 _private member_ `UObject* Owner = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)
- L13 _prototype_ `FReplicationFragment* CreateAndRegisterMinimalReplicationTagCountMapReplicationFragment(UObject* Owner, const FReplicationStateDescriptor* Descriptor, FFragmentRegistrationContext& Context);` (scope `UE::Net`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Private/Serialization/PredictionKeyNetSerializer.h` (Private)


#### struct `FPredictionKeyNetSerializerConfig`  
`struct FPredictionKeyNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Async/AbilityAsync.h` (Public)


#### class `UAbilityAsync`  
`class UAbilityAsync : public UCancellableAsyncAction`  
_L22-48_
- reflection: `UCLASS(Abstract, meta = (ExposedAsyncProxy = AsyncAction), MinimalAPI)`
- inherits: `UCancellableAsyncAction`
- desc: AbilityAsync is a base class for ability-specific BlueprintAsyncActions. These are similar to ability tasks, but they can be executed from any blueprint like an actor and are not tied to a specific ability lifespan. By default these actions are only kept alive by the blueprint graph that spawns them and will eventually be destroyed if the graph instance is deleted or spawns a replacement. EndAction should be called when a one-time action has succeeded or failed, but for longer-lived actions with multiple triggers it can be called from blueprints.
- L27 _public prototype_ `virtual void Cancel() override;`
- L31 _public prototype_ `virtual void EndAction();` — `UFUNCTION(BlueprintCallable, Category = "Ability|Async")` — Explicitly end the action, will disable any callbacks and allow action to be destroyed
- L34 _public prototype_ `virtual bool ShouldBroadcastDelegates() const;` — This should be called prior to broadcasting delegates back into the event graph, this ensures the action and ability system component are still valid
- L37 _public prototype_ `virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;` — Returns the ability system component this action is bound to
- L40 _public prototype_ `virtual void SetAbilitySystemComponent(UAbilitySystemComponent* InAbilitySystemComponent);` — Sets the bound component
- L43 _public prototype_ `virtual void SetAbilityActor(AActor* InActor);` — Sets the bound component by searching actor for one
- L46 _private member_ `TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Async/AbilityAsync_WaitAttributeChanged.h` (Public)


#### class `UAbilityAsync_WaitAttributeChanged`  
`class UAbilityAsync_WaitAttributeChanged : public UAbilityAsync`  
_L15-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityAsync`
- L27 _public prototype_ `static UAbilityAsync_WaitAttributeChanged* WaitForAttributeChanged(AActor* TargetActor, FGameplayAttribute Attribute, bool OnlyTriggerOnce = false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay attribute is changed on a target ability system component It will keep listening as long as OnlyTriggerOnce = false If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitForAttributeChange instead.
- L29 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAsyncWaitAttributeChangedDelegate, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);`
- L31 _public member_ `FAsyncWaitAttributeChangedDelegate Changed;` — `UPROPERTY(BlueprintAssignable)`
- L35 _protected prototype_ `virtual void Activate() override;`
- L36 _protected prototype_ `virtual void EndAction() override;`
- L38 _protected prototype_ `void OnAttributeChanged(const FOnAttributeChangeData& ChangeData);`
- L40 _protected member_ `FGameplayAttribute Attribute;`
- L41 _protected member_ `bool OnlyTriggerOnce = false;`
- L43 _protected member_ `FDelegateHandle MyHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAsyncWaitAttributeChangedDelegate, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Async/AbilityAsync_WaitGameplayEffectApplied.h` (Public)


#### class `UAbilityAsync_WaitGameplayEffectApplied`  
`class UAbilityAsync_WaitGameplayEffectApplied : public UAbilityAsync`  
_L22-74_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityAsync`
- desc: This action listens for specific gameplay effect applications based off specified tags. Effects themselves are not replicated; rather the tags they grant, the attributes they change, and the gameplay cues they emit are replicated. This will only listen for local server or predicted client effects.
- L41 _public prototype_ `static UAbilityAsync_WaitGameplayEffectApplied* WaitGameplayEffectAppliedToActor(AActor* TargetActor, const FGameplayTargetDataFilterHandle SourceFilter, FGameplayTagRequirements SourceTagRequirements, FGameplayTagRequirements TargetTagRequirements, FGameplayTagRequirements AssetTagRequirements, FGameplayTagRequirements GrantedTagRequirements, bool TriggerOnce = false, bool ListenForPeriodicEffect = false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Async", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))` — Wait until a GameplayEffect is applied to a target actor. @param TargetActor The actor on which to listen for a GameplayEffect being applied to it @param SourceFilter Actor filter for the source actor applying this effect that must be passed to trigger this task @param SourceTagRequirements Gameplay tag requirements for the source actor applying this effect @param TargetTagRequirements Gameplay tag requirements for the target actor receiving this effect (self in this case) @param AssetTagRequirements Requirements for the asset tags of the applied effect: 'Tags this Effect Has' on the GameplayEffect class @param GrantedTagRequirements Requirements for the tags granted by the applied effect: 'Grant Tags to Target Actor' on the GameplayEffect class @param TriggerOnce If TriggerOnce is true, this task will only return one time. Otherwise it will return everytime a GE is applied that meets the requirements over the life of the ability. @param OptionalExternalOwner Can be used to run this task on someone else (not the owner of the ability). By default you can leave this empty. @param ListenForPeriodicEffects Whether to also fire on periodic ticks of the applied effect
- L43 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAppliedDelegate, AActor*, Source, FGameplayEffectSpecHandle, SpecHandle, FActiveGameplayEffectHandle, ActiveHandle);`
- L45 _public member_ `FOnAppliedDelegate OnApplied;` — `UPROPERTY(BlueprintAssignable)`
- L48 _protected prototype_ `virtual void Activate() override;`
- L49 _protected prototype_ `virtual void EndAction() override;`
- L51 _protected prototype_ `FString GetBroadcastingEffectStackString() const;`
- L53 _protected prototype_ `void OnApplyGameplayEffectCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);`
- L56 _protected member_ `FGameplayTargetDataFilterHandle Filter;` — Actor filter for the source actor applying this effect that must be passed to trigger this task
- L58 _protected member_ `FGameplayTagRequirements SourceTagRequirements;` — Tag requirements for source actor that applies the GameplayEffect
- L60 _protected member_ `FGameplayTagRequirements TargetTagRequirements;` — Tag requirements for target actor to which the GameplayEffect is applied
- L62 _protected member_ `FGameplayTagRequirements AssetTagRequirements;` — Tag requirements for asset tags ('Tags this Effect Has') on the GameplayEffect being applied
- L64 _protected member_ `FGameplayTagRequirements GrantedTagRequirements;` — Tag requirements for granted tags ('Grant Tags to Target Actor') that the GameplayEffect applies to the target actor
- L66 _protected member_ `bool TriggerOnce = false;`
- L67 _protected member_ `bool ListenForPeriodicEffects = false;`
- L69 _protected member_ `FDelegateHandle OnApplyGameplayEffectCallbackDelegateHandle;`
- L70 _protected member_ `FDelegateHandle OnPeriodicGameplayEffectExecuteCallbackDelegateHandle;`
- L73 _protected member_ `TArray<TSubclassOf<class UGameplayEffect>> BroadcastingEffectStack;` — If we are in the process of broadcasting, we do not allow a GameplayEffect class to trigger application of another instance of the same class.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L43 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAppliedDelegate, AActor*, Source, FGameplayEffectSpecHandle, SpecHandle, FActiveGameplayEffectHandle, ActiveHandle);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Async/AbilityAsync_WaitGameplayEvent.h` (Public)


#### class `UAbilityAsync_WaitGameplayEvent`  
`class UAbilityAsync_WaitGameplayEvent : public UAbilityAsync`  
_L15-46_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityAsync`
- L27 _public prototype_ `static UAbilityAsync_WaitGameplayEvent* WaitGameplayEventToActor(AActor* TargetActor, UPARAM(meta=(GameplayTagFilter="GameplayEventTagsCategory")) FGameplayTag EventTag, bool OnlyTriggerOnce = false, boo` — `UFUNCTION(BlueprintCallable, Category = "Ability|Async", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag event is triggered on a target ability system component It will keep listening as long as OnlyTriggerOnce = false If OnlyMatchExact = false it will trigger for nested tags If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitGameplayEvent instead.
- L29 _public prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventReceivedDelegate, FGameplayEventData, Payload);`
- L32 _public member_ `FEventReceivedDelegate EventReceived;` — `UPROPERTY(BlueprintAssignable)`
- L35 _protected prototype_ `virtual void Activate() override;`
- L36 _protected prototype_ `virtual void EndAction() override;`
- L38 _protected prototype_ `virtual void GameplayEventCallback(const FGameplayEventData* Payload);`
- L39 _protected prototype_ `virtual void GameplayEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload);`
- L41 _protected member_ `FGameplayTag Tag;`
- L42 _protected member_ `bool OnlyTriggerOnce = false;`
- L43 _protected member_ `bool OnlyMatchExact = false;`
- L45 _protected member_ `FDelegateHandle MyHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L29 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventReceivedDelegate, FGameplayEventData, Payload);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Async/AbilityAsync_WaitGameplayTag.h` (Public)


#### class `UAbilityAsync_WaitGameplayTag`  
`class UAbilityAsync_WaitGameplayTag : public UAbilityAsync`  
_L15-33_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UAbilityAsync`
- L20 _protected prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncWaitGameplayTagDelegate);`
- L22 _protected prototype_ `virtual void Activate() override;`
- L23 _protected prototype_ `virtual void EndAction() override;`
- L25 _protected prototype_ `virtual void GameplayTagCallback(const FGameplayTag Tag, int32 NewCount);`
- L26 _protected prototype_ `virtual void BroadcastDelegate();`
- L28 _protected member_ `int32 TargetCount = -1;`
- L29 _protected member_ `FGameplayTag Tag;`
- L30 _protected member_ `bool OnlyTriggerOnce = false;`
- L32 _protected member_ `FDelegateHandle MyHandle;`

#### class `UAbilityAsync_WaitGameplayTagAdded`  
`class UAbilityAsync_WaitGameplayTagAdded : public UAbilityAsync_WaitGameplayTag`  
_L36-53_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityAsync_WaitGameplayTag`
- L42 _public member_ `FAsyncWaitGameplayTagDelegate Added;` — `UPROPERTY(BlueprintAssignable)`
- L50 _public prototype_ `static UAbilityAsync_WaitGameplayTagAdded* WaitGameplayTagAddToActor(AActor* TargetActor, FGameplayTag Tag, bool OnlyTriggerOnce=false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag is Added to Target Actor's ability component If the tag is already present when this task is started, it will immediately broadcast the Added event. It will keep listening as long as OnlyTriggerOnce = false. If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitGameplayTagAdd instead.
- L52 _public prototype_ `virtual void BroadcastDelegate() override;`

#### class `UAbilityAsync_WaitGameplayTagRemoved`  
`class UAbilityAsync_WaitGameplayTagRemoved : public UAbilityAsync_WaitGameplayTag`  
_L56-73_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityAsync_WaitGameplayTag`
- L62 _public member_ `FAsyncWaitGameplayTagDelegate Removed;` — `UPROPERTY(BlueprintAssignable)`
- L70 _public prototype_ `static UAbilityAsync_WaitGameplayTagRemoved* WaitGameplayTagRemoveFromActor(AActor* TargetActor, FGameplayTag Tag, bool OnlyTriggerOnce=false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag is Removed from Target Actor's ability component If the tag is not present when this task is started, it will immediately broadcast the Removed event. It will keep listening as long as OnlyTriggerOnce = false. If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitGameplayTagRemove instead.
- L72 _public prototype_ `virtual void BroadcastDelegate() override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncWaitGameplayTagDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Async/AbilityAsync_WaitGameplayTagCountChanged.h` (Public)


#### class `UAbilityAsync_WaitGameplayTagCountChanged`  
`class UAbilityAsync_WaitGameplayTagCountChanged : public UAbilityAsync`  
_L10-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityAsync`
- L15 _protected prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncWaitGameplayTagCountDelegate, int32, TagCount);`
- L17 _protected prototype_ `virtual void Activate() override;`
- L18 _protected prototype_ `virtual void EndAction() override;`
- L20 _protected prototype_ `virtual void GameplayTagCallback(const FGameplayTag Tag, int32 NewCount);`
- L22 _protected member_ `FGameplayTag Tag;`
- L23 _protected member_ `FDelegateHandle GameplayTagCountChangedHandle;`
- L27 _public member_ `FAsyncWaitGameplayTagCountDelegate TagCountChanged;` — `UPROPERTY(BlueprintAssignable)`
- L34 _public prototype_ `static UAbilityAsync_WaitGameplayTagCountChanged* WaitGameplayTagCountChangedOnActor(AActor* TargetActor, FGameplayTag Tag);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag count changes on Target Actor's ability component If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitGameplayTagCountChange instead.

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAsyncWaitGameplayTagCountDelegate, int32, TagCount);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Async/AbilityAsync_WaitGameplayTagQuery.h` (Public)


#### class `UAbilityAsync_WaitGameplayTagQuery`  
`class UAbilityAsync_WaitGameplayTagQuery : public UAbilityAsync`  
_L17-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityAsync`
- desc: This class defines an async node to wait on a gameplay tag query.
- L24 _public member_ `FAsyncWaitGameplayTagQueryDelegate Triggered;` — `UPROPERTY(BlueprintAssignable)` — This delegate will be triggered when the trigger condition has been met.
- L33 _public prototype_ `static UAbilityAsync_WaitGameplayTagQuery* WaitGameplayTagQueryOnActor(AActor* TargetActor, const FGameplayTagQuery TagQuery, const EWaitGameplayTagQueryTriggerCondition TriggerCondition = EWaitGameplayTagQueryTriggerCondition::WhenTrue, const bool bOnlyTriggerOnce=false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DefaultToSelf = "TargetActor", BlueprintInternalUseOnly = "TRUE"))` — Wait until the given gameplay tag query has become true or false, based on TriggerCondition, looking at the target actors ASC. If the the tag query already satisfies the TriggerCondition when this task is started, it will immediately broadcast the Triggered event. It will keep listening as long as bOnlyTriggerOnce = false. If used in an ability graph, this async action will wait even after activation ends. It's recommended to use WaitGameplayTagQuery instead.
- L39 _public prototype_ `virtual void Activate() override;` — Activates this AbilityAsync node.
- L43 _protected prototype_ `virtual void EndAction() override;` — Ends this AbilityAsync node, unregistering all tag changed delagates.
- L46 _protected prototype_ `virtual bool ShouldBroadcastDelegates() const;` — Returns if this AbilityAsync node should currently broadcast it's delegates.
- L49 _protected prototype_ `void UpdateTargetTags(const FGameplayTag Tag, int32 NewCount);` — This will update the tags in the TargetTags container to reflect that tags that are on the target ASC.
- L52 _protected prototype_ `void EvaluateTagQuery();` — This will evaluate the TargetTags using the given TagQuery, executing the Trigger delegate if needed.
- L55 _protected member_ `FGameplayTagQuery TagQuery;` — This is the tag query to evaluate for triggering this node.
- L58 _protected member_ `EWaitGameplayTagQueryTriggerCondition TriggerCondition = EWaitGameplayTagQueryTriggerCondition::WhenTrue;` — This indicates when to Trigger the Triggered output for this node.
- L61 _protected member_ `bool bOnlyTriggerOnce = false;` — This indicates if this node should only trigger once, or any number of times.
- L64 _protected member_ `bool bRegisteredCallbacks = false;` — Indicates if the callbacks for tag changes have been registered.
- L67 _protected member_ `bool bQueryState = false;` — This was the last result of evaluating the TagQuery.
- L71 _protected member_ `FGameplayTagContainer TargetTags;` — This is the tag container of the targets the target ASC currently has. NOTE: This will only contain the tags referenced in the TagQuery.
- L74 _protected member_ `TMap<FGameplayTag, FDelegateHandle> TagHandleMap;` — This is the handles to the tag changed delegate for each gameplay tag in the TagQuery.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncWaitGameplayTagQueryDelegate);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAsyncWaitGameplayTagQueryDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility.h` (Public)


#### struct `FScopedCanActivateAbilityLogEnabler`  
`struct FScopedCanActivateAbilityLogEnabler`  
_L27-38_
- L29 _public function_ `FScopedCanActivateAbilityLogEnabler()`
- L31 _public function_ `~FScopedCanActivateAbilityLogEnabler()`
- L33 _public function_ `static bool IsLoggingEnabled()`
- L37 _private member_ `static int32 LogEnablerCounter;`

#### class `UGameplayAbility`  
`class UGameplayAbility : public UObject, public IGameplayTaskOwnerInterface`  
_L91-906_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `UObject,IGameplayTaskOwnerInterface`
- desc: Abilities define custom gameplay logic that can be activated by players or external game logic
- L128 _public prototype_ `EGameplayAbilityInstancingPolicy::Type GetInstancingPolicy() const;` — Returns how the ability is instanced when executed. This limits what an ability can do in its implementation.
- L131 _public function_ `EGameplayAbilityReplicationPolicy::Type GetReplicationPolicy() const` — How an ability replicates state/events to everyone on the network
- L137 _public function_ `EGameplayAbilityNetExecutionPolicy::Type GetNetExecutionPolicy() const` — Where does an ability execute on the network? Does a client "ask and predict", "ask and wait", "don't ask (just do it)"
- L143 _public function_ `EGameplayAbilityNetSecurityPolicy::Type GetNetSecurityPolicy() const` — Where should an ability execute on the network? Provides protection from clients attempting to execute restricted abilities.
- L150 _public prototype_ `FGameplayAbilityActorInfo GetActorInfo() const;` — `UFUNCTION(BlueprintCallable, Category=Ability)` — Returns the actor info associated with this ability, has cached pointers to useful objects
- L154 _public prototype_ `AActor* GetOwningActorFromActorInfo() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Returns the actor that owns this ability, which may not have a physical location
- L158 _public prototype_ `AActor* GetAvatarActorFromActorInfo() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Returns the physical actor that is executing this ability. May be null
- L162 _public prototype_ `USkeletalMeshComponent* GetOwningComponentFromActorInfo() const;` — `UFUNCTION(BlueprintCallable, DisplayName = "GetSkeletalMeshComponentFromActorInfo", Category = Ability)` — Convenience method for abilities to get skeletal mesh component - useful for aiming abilities
- L166 _public prototype_ `UAbilitySystemComponent* GetAbilitySystemComponentFromActorInfo() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Returns the AbilitySystemComponent that is activating this ability
- L169 _public prototype_ `UAbilitySystemComponent* GetAbilitySystemComponentFromActorInfo_Checked() const;` — `UE_DEPRECATED(5.5, "Use GetAbilitySystemComponentFromActorInfo_Ensured")`
- L170 _public prototype_ `UAbilitySystemComponent* GetAbilitySystemComponentFromActorInfo_Ensured() const;`
- L173 _public prototype_ `const FGameplayTagContainer& GetAssetTags() const;` — The ability is considered to have these tags.
- L176 _public prototype_ `const FGameplayAbilityActorInfo* GetCurrentActorInfo() const;` — Gets the current actor info bound to this ability - can only be called on instanced abilities.
- L179 _public prototype_ `FGameplayAbilityActivationInfo GetCurrentActivationInfo() const;` — Gets the current activation info bound to this ability - can only be called on instanced abilities.
- L182 _public function_ `FGameplayAbilityActivationInfo& GetCurrentActivationInfoRef()` — Gets the current activation info bound to this ability - can only be called on instanced abilities.
- L189 _public prototype_ `FGameplayAbilitySpecHandle GetCurrentAbilitySpecHandle() const;` — Gets the current AbilitySpecHandle- can only be called on instanced abilities.
- L192 _public prototype_ `FGameplayAbilitySpec* GetCurrentAbilitySpec() const;` — Retrieves the actual AbilitySpec for this ability. Can only be called on instanced abilities.
- L196 _public prototype_ `FGameplayEffectContextHandle GetGrantedByEffectContext() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Retrieves the EffectContext of the GameplayEffect that granted this ability. Can only be called on instanced abilities.
- L200 _public prototype_ `virtual FGameplayEffectContextHandle GetContextFromOwner(FGameplayAbilityTargetDataHandle OptionalTargetData) const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Generates a GameplayEffectContextHandle from our owner and an optional TargetData.
- L203 _public prototype_ `virtual FGameplayEffectContextHandle MakeEffectContext(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo *ActorInfo) const;` — Returns an effect context, given a specified actor info
- L207 _public prototype_ `FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpec(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level=1.f) const;` — `UFUNCTION(BlueprintCallable, Category=Ability)` — Convenience method for abilities to get outgoing gameplay effect specs (for example, to pass on to projectiles to apply to whoever they hit)
- L210 _public prototype_ `virtual FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpec(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level = 1.f) const;` — Native version of above function
- L213 _public prototype_ `virtual void ApplyAbilityTagsToGameplayEffectSpec(FGameplayEffectSpec& Spec, FGameplayAbilitySpec* AbilitySpec) const;` — Add the Ability's tags to the given GameplayEffectSpec. This is likely to be overridden per project.
- L216 _public prototype_ `bool IsActive() const;` — Returns true if the ability is currently active
- L219 _public prototype_ `bool IsTriggered() const;` — Is this ability triggered from TriggerData (or is it triggered explicitly through input/game code)
- L222 _public prototype_ `bool IsPredictingClient() const;` — Is this ability running on a a predicting client, this is false in single player
- L225 _public prototype_ `bool IsForRemoteClient() const;` — True if this is on the server and is being executed for a non-local player, false in single player
- L229 _public prototype_ `bool IsLocallyControlled() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = Ability, Meta = (ExpandBoolAsExecs = "ReturnValue"))` — True if the owning actor is locally controlled, true in single player
- L232 _public prototype_ `bool HasAuthority(const FGameplayAbilityActivationInfo* ActivationInfo) const;` — True if this is the server or single player
- L235 _public prototype_ `bool K2_HasAuthority() const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = Ability, DisplayName = "HasAuthority", Meta = (ExpandBoolAsExecs = "ReturnValue"))`
- L238 _public prototype_ `bool HasAuthorityOrPredictionKey(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo* ActivationInfo) const;` — True if we are authority or we have a valid prediciton key that is expected to work
- L241 _public prototype_ `bool IsInstantiated() const;` — True if this has been instanced, always true for blueprints
- L244 _public member_ `FOnGameplayAbilityEnded OnGameplayAbilityEnded;` — Notification that the ability has ended.  Set using TryActivateAbility.
- L247 _public member_ `FGameplayAbilityEndedDelegate OnGameplayAbilityEndedWithData;` — Notification that the ability has ended with data on how it was ended
- L250 _public member_ `FOnGameplayAbilityCancelled OnGameplayAbilityCancelled;` — Notification that the ability is being cancelled.  Called before OnGameplayAbilityEnded.
- L253 _public member_ `FOnGameplayAbilityStateEnded OnGameplayAbilityStateEnded;` — Used by the ability state task to handle when a state is ended
- L256 _public member_ `FGenericAbilityDelegate OnConfirmDelegate;` — Callback for when this ability has been confirmed by the server
- L263 _public prototype_ `virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;` — Returns true if this ability can be activated right now. Has no side effects
- L266 _public prototype_ `virtual bool ShouldAbilityRespondToEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayEventData* Payload) const;` — Returns true if this ability can be triggered right now. Has no side effects
- L269 _public prototype_ `virtual bool ShouldActivateAbility(ENetRole Role) const;` — Returns true if an an ability should be activated
- L273 _public prototype_ `float GetCooldownTimeRemaining() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Returns the time in seconds remaining on the currently active cooldown.
- L276 _public prototype_ `virtual float GetCooldownTimeRemaining(const FGameplayAbilityActorInfo* ActorInfo) const;` — Returns the time in seconds remaining on the currently active cooldown.
- L279 _public prototype_ `virtual void GetCooldownTimeRemainingAndDuration(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, float& TimeRemaining, float& CooldownDuration) const;` — Returns the time in seconds remaining on the currently active cooldown and the original duration for this cooldown.
- L282 _public prototype_ `virtual const FGameplayTagContainer* GetCooldownTags() const;` — Returns all tags that can put this ability into cooldown
- L285 _public prototype_ `virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;` — Returns true if none of the ability's tags are blocked and if it doesn't have a "Blocking" tag and has all "Required" tags.
- L288 _public prototype_ `virtual bool IsBlockingOtherAbilities() const;` — Returns true if this ability is blocking other abilities
- L292 _public prototype_ `virtual void SetShouldBlockOtherAbilities(bool bShouldBlockAbilities);` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Sets rather ability block flags are enabled or disabled. Only valid on instanced abilities
- L299 _public prototype_ `virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility);` — Destroys instanced-per-execution abilities. Instance-per-actor abilities should 'reset'. Any active ability state tasks receive the 'OnAbilityStateInterrupted' event. Non instance abilities - what can we do?
- L303 _public prototype_ `void K2_CancelAbility();` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "CancelAbility", meta=(ScriptName = "CancelAbility"))` — Call from Blueprint to cancel the ability naturally
- L306 _public prototype_ `virtual bool CanBeCanceled() const;` — Returns true if this ability can be canceled
- L310 _public prototype_ `virtual void SetCanBeCanceled(bool bCanBeCanceled);` — `UFUNCTION(BlueprintCallable, Category=Ability)` — Sets whether the ability should ignore cancel requests. Only valid on instanced abilities
- L318 _public prototype_ `virtual bool K2_CommitAbility();` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "CommitAbility", meta=(ScriptName = "CommitAbility"))` — Attempts to commit the ability (spend resources, etc). This our last chance to fail. Child classes that override ActivateAbility must call this themselves!
- L322 _public prototype_ `virtual bool K2_CommitAbilityCooldown(bool BroadcastCommitEvent=false, bool ForceCooldown=false);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "CommitAbilityCooldown", meta=(ScriptName = "CommitAbilityCooldown"))` — Attempts to commit the ability's cooldown only. If BroadcastCommitEvent is true, it will broadcast the commit event that tasks like WaitAbilityCommit are listening for.
- L326 _public prototype_ `virtual bool K2_CommitAbilityCost(bool BroadcastCommitEvent=false);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "CommitAbilityCost", meta=(ScriptName = "CommitAbilityCost"))` — Attempts to commit the ability's cost only. If BroadcastCommitEvent is true, it will broadcast the commit event that tasks like WaitAbilityCommit are listening for.
- L330 _public prototype_ `virtual bool K2_CheckAbilityCooldown();` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "CheckAbilityCooldown", meta=(ScriptName = "CheckAbilityCooldown"))` — Checks the ability's cooldown, but does not apply it.
- L334 _public prototype_ `virtual bool K2_CheckAbilityCost();` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "CheckAbilityCost", meta=(ScriptName = "CheckAbilityCost"))` — Checks the ability's cost, but does not apply it.
- L336 _public prototype_ `virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);`
- L337 _public prototype_ `virtual bool CommitAbilityCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const bool ForceCooldown, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);`
- L338 _public prototype_ `virtual bool CommitAbilityCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);`
- L341 _public prototype_ `virtual bool CommitCheck(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);` — The last chance to fail before committing, this will usually be the same as CanActivateAbility. Some abilities may need to do extra checks here if they are consuming extra stuff in CommitExecute
- L345 _public prototype_ `void K2_CommitExecute();` — `UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "CommitExecute", meta = (ScriptName = "CommitExecute"))` — BP event called from CommitAbility
- L348 _public prototype_ `virtual void CommitExecute(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);` — Does the commit atomically (consume resources, do cooldowns, etc)
- L351 _public prototype_ `virtual UGameplayEffect* GetCooldownGameplayEffect() const;` — Returns the gameplay effect used to determine cooldown
- L354 _public prototype_ `virtual UGameplayEffect* GetCostGameplayEffect() const;` — Returns the gameplay effect used to apply cost
- L357 _public prototype_ `virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;` — Checks cooldown. returns true if we can be used again. False if not
- L360 _public prototype_ `virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;` — Applies CooldownGameplayEffect to the target
- L363 _public prototype_ `virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;` — Checks cost. returns true if we can pay for the ability. False if not
- L366 _public prototype_ `virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;` — Applies the ability's cost to the target
- L373 _public function_ `virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)` — Input binding stub.
- L376 _public function_ `virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)` — Input binding stub.
- L379 _public function_ `virtual void OnWaitingForConfirmInputBegin()` — Called from AbilityTask_WaitConfirmCancel to handle input confirming
- L380 _public function_ `virtual void OnWaitingForConfirmInputEnd()`
- L388 _public prototype_ `UAnimMontage* GetCurrentMontage() const;` — `UFUNCTION(BlueprintCallable, Category = Animation)` — Returns the currently playing montage for this ability, if any
- L391 _public prototype_ `virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage);` — Call to set/get the current montage from a montage task. Set to allow hooking up montage events to ability events
- L399 _public prototype_ `int32 GetAbilityLevel() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Returns current level of the Ability
- L402 _public prototype_ `int32 GetAbilityLevel(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;` — Returns current ability level for non instanced abilities. You must call this version in these contexts!
- L406 _public prototype_ `int32 GetAbilityLevel_BP(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo) const;` — `UFUNCTION(BlueprintCallable, Category = Ability, meta = (DisplayName = "GetAbilityLevelNonInstanced", ReturnDisplayName = "AbilityLevel"))` — Returns current ability level for non instanced abilities. You must call this version in these contexts!
- L410 _public prototype_ `UObject* GetCurrentSourceObject() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Retrieves the SourceObject associated with this ability. Can only be called on instanced abilities.
- L413 _public prototype_ `UObject* GetSourceObject(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;` — Retrieves the SourceObject associated with this ability. Callable on non instanced
- L417 _public prototype_ `UObject* GetSourceObject_BP(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo& ActorInfo) const;` — `UFUNCTION(BlueprintCallable, Category = Ability, meta = (DisplayName = "GetSourceObjectNonInstanced", ReturnDisplayName = "SourceObject"))` — Retrieves the SourceObject associated with this ability. Callable on non instanced
- L424 _public prototype_ `virtual void SetRemoteInstanceHasEnded();` — Called by ability system component to inform this ability instance the remote instance was ended
- L427 _public prototype_ `virtual void NotifyAvatarDestroyed();` — Called to inform the ability that the AvatarActor has been replaced. If the ability is dependent on avatar state, it may want to end itself.
- L430 _public prototype_ `virtual void NotifyAbilityTaskWaitingOnPlayerData(class UAbilityTask* AbilityTask);` — Called to inform the ability that a task is waiting for the player to do something
- L433 _public prototype_ `virtual void NotifyAbilityTaskWaitingOnAvatar(class UAbilityTask* AbilityTask);` — Called to inform the ability that a task is waiting for the player's avatar to do something in world
- L436 _public prototype_ `virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);` — Called when the ability is given to an AbilitySystemComponent
- L439 _public function_ `virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)` — Called when the ability is removed from an AbilitySystemComponent
- L442 _public prototype_ `virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);` — Called when the avatar actor is set/changes
- L445 _public function_ `virtual bool ShouldReplicateAbilitySpec(const FGameplayAbilitySpec& AbilitySpec) const` — Takes in the ability spec and checks if we should allow replication on the ability spec, this will NOT stop replication of the ability UObject just the spec inside the UAbilitySystemComponenet ActivatableAbilities for this ability
- L455 _public prototype_ `void InvalidateClientPredictionKey() const;` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Invalidates the current prediction key. This should be used in cases where there is a valid prediction window, but the server is doing logic that only it can do, and afterwards performs an action that the client could predict (had the client been able to run the server-only code prior). This returns instantly and has no other side effects other than clearing the current prediction key.
- L459 _public prototype_ `virtual void RemoveGrantedByEffect();` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Removes the GameplayEffect that granted this ability. Can only be called on instanced abilities.
- L462 _public prototype_ `void AddAbilityTaskDebugMessage(UGameplayTask* AbilityTask, FString DebugMessage);` — Adds a debug message to display to the user
- L466 _public prototype_ `FGameplayTagContainer& EditorGetAssetTags();` — Allow modification of the AssetTags (AbilityTags) while in editor
- L476 _public member_ `FGameplayTagContainer AbilityTags;` — `UE_DEPRECATED_FORGAME(5.5, "Use GetAssetTags(). This is being made non-mutable, private and renamed to AssetTags in the future. Use SetAssetTags to set defaults (in constructor only).")` — `UPROPERTY(EditDefaultsOnly, Category = Tags, DisplayName="AssetTags (Default AbilityTags)", meta=(Categories="AbilityTagCategory"))` — This ability has these tags
- L480 _public member_ `bool bReplicateInputDirectly;` — `UPROPERTY(EditDefaultsOnly, Category = Input)` — If true, this ability will always replicate input press/release events to the server.
- L484 _public member_ `bool RemoteInstanceEnded;` — `UPROPERTY()` — Set when the remote instance of this ability has ended (but the local instance may still be running or finishing up
- L489 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L490 _public prototype_ `virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;`
- L491 _public prototype_ `virtual bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;`
- L492 _public prototype_ `virtual bool IsSupportedForNetworking() const override;`
- L493 _public prototype_ `virtual void PreDestroyFromReplication() override;`
- L496 _public prototype_ `virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;`
- L500 _public prototype_ `virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const;` — Overridden to allow Blueprint replicated properties to work
- L503 _public prototype_ `virtual void RegisterReplicationFragments(UE::Net::FFragmentRegistrationContext& Context, UE::Net::EFragmentRegistrationFlags RegistrationFlags) override;` — Register all replication fragments
- L508 _public prototype_ `virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;`
- L509 _public prototype_ `virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;`
- L510 _public prototype_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;`
- L511 _public prototype_ `virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;`
- L512 _public prototype_ `virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;`
- L513 _public prototype_ `virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;`
- L523 _protected prototype_ `void SetAssetTags(const FGameplayTagContainer& InAbilityTags);` — Allows a derived class to set the default GameplayTags that this Ability is considered to have (formerly AbilityTags). This can only be called during construction. At runtime, the AbilitySpec is queried through a Gameplay Ability's CDO for its AbilityTags which can be a combination of these Asset Tags and specifically granted DynamicAbilityTags (all instances generated from an AbilitySpec are expected to share the same AbilityTags).
- L531 _protected prototype_ `bool K2_ShouldAbilityRespondToEvent(FGameplayAbilityActorInfo ActorInfo, FGameplayEventData Payload) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "ShouldAbilityRespondToEvent", meta=(ScriptName = "ShouldAbilityRespondToEvent"))` — Returns true if this ability can be activated right now. Has no side effects
- L533 _protected member_ `bool bHasBlueprintShouldAbilityRespondToEvent;`
- L537 _protected prototype_ `virtual void SendGameplayEvent(UPARAM(meta=(GameplayTagFilter="GameplayEventTagsCategory")) FGameplayTag EventTag, FGa` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Sends a gameplay event, also creates a prediction window
- L545 _protected prototype_ `bool K2_CanActivateAbility(FGameplayAbilityActorInfo ActorInfo, const FGameplayAbilitySpecHandle Handle, FGameplayTagContainer& RelevantTags) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName="CanActivateAbility", meta=(ScriptName="CanActivateAbility"))` — Returns true if this ability can be activated right now. Has no side effects
- L547 _protected member_ `bool bHasBlueprintCanUse;`
- L565 _protected prototype_ `void K2_ActivateAbility();` — `UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "ActivateAbility", meta=(ScriptName = "ActivateAbility"))` — The main function that defines what an ability does. -Child classes will want to override this -This function graph should call CommitAbility -This function graph should call EndAbility Latent/async actions are ok in this graph. Note that Commit and EndAbility calling requirements speak to the K2_ActivateAbility graph. In C++, the call to K2_ActivateAbility() may return without CommitAbility or EndAbility having been called. But it is expected that this will only occur when latent/async actions are pending. When K2_ActivateAbility logically finishes, then we will expect Commit/End to have been called.
- L568 _protected prototype_ `void K2_ActivateAbilityFromEvent(const FGameplayEventData& EventData);` — `UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "ActivateAbilityFromEvent", meta=(ScriptName = "ActivateAbilityFromEvent"))`
- L570 _protected member_ `bool bHasBlueprintActivate;`
- L571 _protected member_ `bool bHasBlueprintActivateFromEvent;`
- L574 _protected prototype_ `virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);` — Actually activate ability, do not call this directly
- L577 _protected prototype_ `virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr);` — Do boilerplate init stuff and then call ActivateAbility
- L580 _protected prototype_ `void CallActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate = nullptr, const FGameplayEventData* TriggerEventData = nullptr);` — Executes PreActivate and ActivateAbility
- L583 _protected prototype_ `virtual void ConfirmActivateSucceed();` — Called on a predictive ability when the server confirms its execution
- L590 _protected prototype_ `virtual void K2_EndAbility();` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName="End Ability", meta=(ScriptName = "EndAbility"))` — Call from blueprints to forcibly end the ability without canceling it. This will replicate the end ability to the client or server which can interrupt tasks
- L594 _protected prototype_ `virtual void K2_EndAbilityLocally();` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "End Ability Locally", meta = (ScriptName = "EndAbilityLocally"))` — Call from blueprints to end the ability naturally. This will only end predicted abilities locally, allowing it end naturally on the client or server
- L598 _protected prototype_ `void K2_OnEndAbility(bool bWasCancelled);` — `UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnEndAbility", meta=(ScriptName = "OnEndAbility"))` — Blueprint event, will be called if an ability ends normally or abnormally
- L601 _protected prototype_ `bool IsEndAbilityValid(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;` — Check if the ability can be ended
- L604 _protected prototype_ `virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);` — Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server
- L612 _protected prototype_ `FActiveGameplayEffectHandle BP_ApplyGameplayEffectToOwner(TSubclassOf<UGameplayEffect> GameplayEffectClass, int32 GameplayEffectLevel = 1, int32 Stacks = 1);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName="ApplyGameplayEffectToOwner", meta=(ScriptName="ApplyGameplayEffectToOwner"))` — Apply a gameplay effect to the owner of this ability
- L615 _protected prototype_ `FActiveGameplayEffectHandle ApplyGameplayEffectToOwner(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const UGameplayEffect* GameplayEffect, float GameplayEffectLevel, int32 Stacks = 1) const;` — Non blueprintcallable, safe to call on CDO/NonInstance abilities
- L619 _protected prototype_ `FActiveGameplayEffectHandle K2_ApplyGameplayEffectSpecToOwner(const FGameplayEffectSpecHandle EffectSpecHandle);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "ApplyGameplayEffectSpecToOwner", meta=(ScriptName = "ApplyGameplayEffectSpecToOwner"))` — Apply a previously created gameplay effect spec to the owner of this ability
- L621 _protected prototype_ `FActiveGameplayEffectHandle ApplyGameplayEffectSpecToOwner(const FGameplayAbilitySpecHandle AbilityHandle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEffectSpecHandle SpecHandle) const;`
- L625 _protected prototype_ `void BP_EditSpecValues(FGameplayEffectSpecHandle SpecHandle) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "EditSpecValues", meta = (ScriptName = "EditSpecValues"))` — Change Gameplay effect values before they get applied
- L633 _protected prototype_ `TArray<FActiveGameplayEffectHandle> BP_ApplyGameplayEffectToTarget(FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<UGameplayEffect> GameplayEffectClass, int32 GameplayEffectLevel = 1, int32 Stacks = 1);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "ApplyGameplayEffectToTarget", meta=(ScriptName = "ApplyGameplayEffectToTarget"))` — Apply a gameplay effect to a Target
- L636 _protected prototype_ `TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectToTarget(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayAbilityTargetDataHandle& Target, TSubclassOf<UGameplayEffect> GameplayEffectClass, float GameplayEffectLevel, int32 Stacks = 1) const;` — Non blueprintcallable, safe to call on CDO/NonInstance abilities
- L640 _protected prototype_ `TArray<FActiveGameplayEffectHandle> K2_ApplyGameplayEffectSpecToTarget(const FGameplayEffectSpecHandle EffectSpecHandle, FGameplayAbilityTargetDataHandle TargetData);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "ApplyGameplayEffectSpecToTarget", meta=(ScriptName = "ApplyGameplayEffectSpecToTarget"))` — Apply a previously created gameplay effect spec to a target
- L642 _protected prototype_ `TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpecToTarget(const FGameplayAbilitySpecHandle AbilityHandle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEffectSpecHandle SpecHandle, const FGameplayAbilityTargetDataHandle& TargetData) const;`
- L650 _protected prototype_ `void BP_RemoveGameplayEffectFromOwnerWithAssetTags(FGameplayTagContainer WithAssetTags, int32 StacksToRemove = -1);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName="RemoveGameplayEffectFromOwnerWithAssetTags", meta=(ScriptName="RemoveGameplayEffectFromOwnerWithAssetTags"))` — Removes GameplayEffects from owner which match the given asset level tags
- L654 _protected prototype_ `void BP_RemoveGameplayEffectFromOwnerWithGrantedTags(FGameplayTagContainer WithGrantedTags, int32 StacksToRemove = -1);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName="RemoveGameplayEffectFromOwnerWithGrantedTags", meta=(ScriptName="RemoveGameplayEffectFromOwnerWithGrantedTags"))` — Removes GameplayEffects from owner which grant the given tags
- L658 _protected prototype_ `void BP_RemoveGameplayEffectFromOwnerWithHandle(FActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);` — `UFUNCTION(BlueprintCallable, Category = Ability, DisplayName = "RemoveGameplayEffectFromOwnerWithHandle", meta=(ScriptName = "RemoveGameplayEffectFromOwnerWithHandle"))` — Removes GameplayEffect from owner that match the given handle
- L667 _protected prototype_ `virtual void K2_ExecuteGameplayCue(FGameplayTag GameplayCueTag, FGameplayEffectContextHandle Context);` — `UFUNCTION(BlueprintCallable, Category = Ability, meta=(GameplayTagFilter="GameplayCue"), DisplayName="Execute GameplayCue On Owner", meta=(ScriptName="ExecuteGameplayCue"))` — Invoke a gameplay cue on the ability owner
- L671 _protected prototype_ `virtual void K2_ExecuteGameplayCueWithParams(FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);` — `UFUNCTION(BlueprintCallable, Category = Ability, meta = (GameplayTagFilter = "GameplayCue"), DisplayName = "Execute GameplayCueWithParams On Owner", meta=(ScriptName = "ExecuteGameplayCueWithParams"))` — Invoke a gameplay cue on the ability owner, with extra parameters
- L675 _protected prototype_ `virtual void K2_AddGameplayCue(FGameplayTag GameplayCueTag, FGameplayEffectContextHandle Context, bool bRemoveOnAbilityEnd = true);` — `UFUNCTION(BlueprintCallable, Category = Ability, meta=(GameplayTagFilter="GameplayCue"), DisplayName="Add GameplayCue To Owner", meta=(ScriptName="AddGameplayCue"))` — Adds a persistent gameplay cue to the ability owner. Optionally will remove if ability ends
- L679 _protected prototype_ `virtual void K2_AddGameplayCueWithParams(FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameter, bool bRemoveOnAbilityEnd = true);` — `UFUNCTION(BlueprintCallable, Category = Ability, meta = (GameplayTagFilter = "GameplayCue"), DisplayName = "Add GameplayCueWithParams To Owner", meta=(ScriptName = "AddGameplayCueWithParams"))` — Adds a persistent gameplay cue to the ability owner. Optionally will remove if ability ends
- L683 _protected prototype_ `virtual void K2_RemoveGameplayCue(FGameplayTag GameplayCueTag);` — `UFUNCTION(BlueprintCallable, Category = Ability, meta=(GameplayTagFilter="GameplayCue"), DisplayName="Remove GameplayCue From Owner", meta=(ScriptName="RemoveGameplayCue"))` — Removes a persistent gameplay cue from the ability owner
- L691 _protected member_ `TEnumAsByte<EGameplayAbilityReplicationPolicy::Type> ReplicationPolicy;` — `UPROPERTY(EditDefaultsOnly, Category = Advanced)` — How an ability replicates state/events to everyone on the network. Replication is not required for NetExecutionPolicy.
- L695 _protected member_ `TEnumAsByte<EGameplayAbilityInstancingPolicy::Type> InstancingPolicy;` — `UPROPERTY(EditDefaultsOnly, Category = Advanced)` — How the ability is instanced when executed. This limits what an ability can do in its implementation.
- L699 _protected member_ `bool bServerRespectsRemoteAbilityCancellation;` — `UPROPERTY(EditDefaultsOnly, Category = Advanced)` — If this is set, the server-side version of the ability can be canceled by the client-side version. The client-side version can always be canceled by the server.
- L703 _protected member_ `bool bRetriggerInstancedAbility;` — `UPROPERTY(EditDefaultsOnly, Category = Advanced)` — if true, and trying to activate an already active instanced ability, end it and re-trigger it.
- L707 _protected member_ `FGameplayAbilityActivationInfo CurrentActivationInfo;` — `UPROPERTY(BlueprintReadOnly, Category = Ability)` — This is information specific to this instance of the ability. E.g, whether it is predicting, authoring, confirmed, etc.
- L711 _protected member_ `FGameplayEventData CurrentEventData;` — `UPROPERTY(BlueprintReadOnly, Category = Ability)` — Information specific to this instance of the ability, if it was activated by an event
- L715 _protected member_ `TEnumAsByte<EGameplayAbilityNetExecutionPolicy::Type> NetExecutionPolicy;` — `UPROPERTY(EditDefaultsOnly, Category=Advanced)` — How does an ability execute on the network. Does a client "ask and predict", "ask and wait", "don't ask (just do it)".
- L719 _protected member_ `TEnumAsByte<EGameplayAbilityNetSecurityPolicy::Type> NetSecurityPolicy;` — `UPROPERTY(EditDefaultsOnly, Category = Advanced)` — What protections does this ability have? Should the client be allowed to request changes to the execution of the ability?
- L723 _protected member_ `TSubclassOf<class UGameplayEffect> CostGameplayEffectClass;` — `UPROPERTY(EditDefaultsOnly, Category = Costs)` — This GameplayEffect represents the cost (mana, stamina, etc) of the ability. It will be applied when the ability is committed.
- L727 _protected member_ `TArray<FAbilityTriggerData> AbilityTriggers;` — `UPROPERTY(EditDefaultsOnly, Category = Triggers)` — Triggers to determine if this ability should execute in response to an event
- L731 _protected member_ `TSubclassOf<class UGameplayEffect> CooldownGameplayEffectClass;` — `UPROPERTY(EditDefaultsOnly, Category = Cooldowns)` — This GameplayEffect represents the cooldown. It will be applied when the ability is committed and the ability cannot be used again until it is expired.
- L739 _protected member_ `FGameplayTagContainer CancelAbilitiesWithTag;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="AbilityTagCategory"))` — Abilities with these tags are cancelled when this ability is executed
- L743 _protected member_ `FGameplayTagContainer BlockAbilitiesWithTag;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="AbilityTagCategory"))` — Abilities with these tags are blocked while this ability is active
- L747 _protected member_ `FGameplayTagContainer ActivationOwnedTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="OwnedTagsCategory"))` — Tags to apply to activating owner while this ability is active. These are replicated if ReplicateActivationOwnedTags is enabled in AbilitySystemGlobals.
- L751 _protected member_ `FGameplayTagContainer ActivationRequiredTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="OwnedTagsCategory"))` — This ability can only be activated if the activating actor/component has all of these tags
- L755 _protected member_ `FGameplayTagContainer ActivationBlockedTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="OwnedTagsCategory"))` — This ability is blocked if the activating actor/component has any of these tags
- L759 _protected member_ `FGameplayTagContainer SourceRequiredTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="SourceTagsCategory"))` — This ability can only be activated if the source actor/component has all of these tags
- L763 _protected member_ `FGameplayTagContainer SourceBlockedTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="SourceTagsCategory"))` — This ability is blocked if the source actor/component has any of these tags
- L767 _protected member_ `FGameplayTagContainer TargetRequiredTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="TargetTagsCategory"))` — This ability can only be activated if the target actor/component has all of these tags
- L771 _protected member_ `FGameplayTagContainer TargetBlockedTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta=(Categories="TargetTagsCategory"))` — This ability is blocked if the target actor/component has any of these tags
- L779 _protected prototype_ `void ConfirmTaskByInstanceName(FName InstanceName, bool bEndTask);` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Finds all currently active tasks named InstanceName and confirms them. What this means depends on the individual task. By default, this does nothing other than ending if bEndTask is true.
- L782 _protected prototype_ `void EndOrCancelTasksByInstanceName();` — Internal function, cancels all the tasks we asked to cancel last frame (by instance name).
- L783 _protected member_ `TArray<FName> CancelTaskInstanceNames;`
- L787 _protected prototype_ `void EndTaskByInstanceName(FName InstanceName);` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Add any task with this instance name to a list to be ended (not canceled) next frame.  See also CancelTaskByInstanceName.
- L788 _protected member_ `TArray<FName> EndTaskInstanceNames;`
- L792 _protected prototype_ `void CancelTaskByInstanceName(FName InstanceName);` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Add any task with this instance name to a list to be canceled (not ended) next frame.  See also EndTaskByInstanceName.
- L796 _protected prototype_ `void EndAbilityState(FName OptionalStateNameToEnd);` — `UFUNCTION(BlueprintCallable, Category = Ability)` — Ends any active ability state task with the given name. If name is 'None' all active states will be ended (in an arbitrary order).
- L800 _protected member_ `TArray<TObjectPtr<UGameplayTask>> ActiveTasks;` — `UPROPERTY()` — List of currently active tasks, do not modify directly
- L803 _protected member_ `TArray<FAbilityTaskDebugMessage> TaskDebugMessages;` — Tasks can emit debug messages throughout their life for debugging purposes. Saved on the ability so that they persist after task is finished
- L811 _protected prototype_ `void MontageJumpToSection(FName SectionName);` — `UFUNCTION(BlueprintCallable, Category="Ability|Animation")` — Immediately jumps the active montage to a section
- L815 _protected prototype_ `void MontageSetNextSectionName(FName FromSectionName, FName ToSectionName);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Animation")` — Sets pending section on active montage
- L823 _protected prototype_ `void MontageStop(float OverrideBlendOutTime = -1.0f);` — `UFUNCTION(BlueprintCallable, Category="Ability|Animation", Meta = (AdvancedDisplay = "OverrideBlendOutTime"))` — Stops the current animation montage. @param OverrideBlendTime If >= 0, will override the BlendOutTime parameter on the AnimMontage instance
- L827 _protected member_ `TObjectPtr<class UAnimMontage> CurrentMontage;` — `UPROPERTY()` — Active montage being played by this ability
- L835 _protected prototype_ `FGameplayAbilityTargetingLocationInfo MakeTargetLocationInfoFromOwnerActor();` — `UFUNCTION(BlueprintPure, Category = Ability)` — Creates a target location from where the owner avatar is
- L839 _protected prototype_ `FGameplayAbilityTargetingLocationInfo MakeTargetLocationInfoFromOwnerSkeletalMeshComponent(FName SocketName);` — `UFUNCTION(BlueprintPure, Category = Ability)` — Creates a target location from a socket on the owner avatar's skeletal mesh
- L846 _protected prototype_ `virtual void PostNetInit();` — Called to initialize after being created due to replication
- L849 _protected prototype_ `virtual void SetCurrentActorInfo(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;` — Modifies actor info, only safe on instanced abilities
- L852 _protected prototype_ `virtual void SetCurrentActivationInfo(const FGameplayAbilityActivationInfo ActivationInfo);` — Modifies activation info, only safe on instanced abilities
- L855 _protected prototype_ `void SetCurrentInfo(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);` — Sets both actor and activation info
- L864 _protected member_ `mutable const FGameplayAbilityActorInfo* CurrentActorInfo;` — This is shared, cached information about the thing using us E.g, Actor*, MovementComponent*, AnimInstance, etc. This is hopefully allocated once per actor and shared by many abilities. The actual struct may be overridden per game to include game specific data. (E.g, child classes may want to cast to FMyGameAbilityActorInfo)
- L867 _protected member_ `mutable FGameplayAbilitySpecHandle CurrentSpecHandle;` — For instanced abilities
- L870 _protected member_ `TSet<FGameplayTag> TrackedGameplayCues;` — GameplayCues that were added during this ability that will get automatically removed when it ends
- L874 _protected member_ `bool bIsActive;` — `UPROPERTY()` — True if the ability is currently active. For instance per owner abilities
- L878 _protected member_ `bool bIsAbilityEnding = false;` — `UPROPERTY()` — True if the end ability has been called, but has not yet completed.
- L882 _protected member_ `bool bIsCancelable;` — `UPROPERTY()` — True if the ability is currently cancelable, if not will only be canceled by hard EndAbility calls
- L886 _protected member_ `bool bIsBlockingOtherAbilities;` — `UPROPERTY()` — True if the ability block flags are currently enabled
- L889 _protected member_ `mutable int8 ScopeLockCount;` — A count of all the current scope locks.
- L892 _protected member_ `mutable TArray<FPostLockDelegate> WaitingToExecute;` — A list of all the functions waiting for the scope lock to end so they can run.
- L895 _protected prototype_ `void IncrementListLock() const;` — Increases the scope lock count.
- L898 _protected prototype_ `void DecrementListLock() const;` — Decreases the scope lock count. Runs the waiting to execute delegates if the count drops to zero.
- L901 _protected prototype_ `virtual void Serialize(FArchive& Ar) override;` — We need to serialize non-property fields in certain circumstances
- L904 _protected prototype_ `virtual void PostMigrate(const struct FUObjectMigrationContext& MigrationContext) override;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L78 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayAbilityEnded, UGameplayAbility*);` — Notification delegate definition for when the gameplay ability ends
- L78 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayAbilityEnded, UGameplayAbility*);` — Notification delegate definition for when the gameplay ability ends
- L81 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGameplayAbilityCancelled);` — Notification delegate definition for when the gameplay ability is cancelled
- L81 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGameplayAbilityCancelled);` — Notification delegate definition for when the gameplay ability is cancelled
- L84 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayAbilityStateEnded, FName);` — Used to notify ability state tasks that a state is being ended
- L84 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayAbilityStateEnded, FName);` — Used to notify ability state tasks that a state is being ended
- L87 _delegate_ `DECLARE_DELEGATE(FPostLockDelegate);` — Used to delay execution until we leave a critical section
- L87 _prototype_ `DECLARE_DELEGATE(FPostLockDelegate);` — Used to delay execution until we leave a critical section

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityRepAnimMontage.h` (Public)


#### enum `ERepAnimPositionMethod`  
`enum class ERepAnimPositionMethod`  
_L15-19_
- reflection: `UENUM()`
- desc: Enum used by the Ability Rep Anim Montage struct to rep the quantized position or the current section id
- L17 _public enumerator_ `Position = 0` — reps the position in the montage to keep the client in sync (heavier, quantized, more precise)
- L18 _public enumerator_ `CurrentSectionId = 1` — reps the current section id we want to play on the client (compact, less precise)

#### struct `FGameplayAbilityRepAnimMontage`  
`struct FGameplayAbilityRepAnimMontage`  
_L23-109_
- reflection: `USTRUCT()`
- desc: Data about montages that is replicated to simulated clients
- L29 _public member_ `TObjectPtr<UAnimSequenceBase> Animation;` — `UPROPERTY()` — Animation ref. When playing a dynamic montage this points to the AnimSequence the montage was created from
- L33 _public member_ `FName SlotName;` — `UPROPERTY()` — Optional slot name used by dynamic montages.
- L37 _public member_ `float PlayRate;` — `UPROPERTY()` — Play Rate
- L41 _public member_ `float Position;` — `UPROPERTY(NotReplicated)` — Montage position
- L45 _public member_ `float BlendTime;` — `UPROPERTY()` — Montage current blend time
- L49 _public member_ `float BlendOutTime;` — `UPROPERTY(NotReplicated)` — Optional blend out used by dynamic montages.
- L53 _public member_ `float PlayCount;` — `UPROPERTY()` — Fractional loop count for non-montages
- L57 _public member_ `uint8 NextSectionID;` — `UPROPERTY()` — NextSectionID
- L61 _public member_ `uint8 PlayInstanceId;` — `UPROPERTY()` — ID incremented every time a montage is played, used to trigger replication when the same montage is played multiple times. This ID wraps around when it reaches its max value.
- L65 _public member_ `uint8 bRepPosition : 1;` — `UPROPERTY()` — flag indicating we should serialize the position or the current section id
- L69 _public member_ `uint8 IsStopped : 1;` — `UPROPERTY()` — Bit set when montage has been stopped.
- L73 _public member_ `uint8 SkipPositionCorrection : 1;` — `UPROPERTY()` — Stops montage position from replicating at all to save bandwidth
- L77 _public member_ `uint8 bSkipPlayRate : 1;` — `UPROPERTY()` — Stops PlayRate from replicating to save bandwidth. PlayRate will be assumed to be 1.f.
- L80 _public member_ `FPredictionKey PredictionKey;` — `UPROPERTY()`
- L84 _public member_ `uint8 SectionIdToPlay;` — `UPROPERTY()` — The current section Id used by the montage. Will only be valid if bRepPosition is false
- L86 _public function_ `FGameplayAbilityRepAnimMontage() : Animation(nullptr), SlotName(NAME_None), PlayRate(0.f), Position(0.f), BlendTime(0.f), BlendOutTime(0.f), PlayCount(0.f), NextSectionID(0), PlayInstanceId(0), bRepPosition(true), IsStopped(true), SkipPositionCorrection(false), bSkipPlayRate(false), SectionIdToPlay(0)`
- L104 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L106 _public prototype_ `void SetRepAnimPositionMethod(ERepAnimPositionMethod InMethod);`
- L108 _public prototype_ `UAnimMontage* GetAnimMontage() const;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayAbilityRepAnimMontage> : public TStructOpsTypeTraitsBase2<FGameplayAbilityRepAnimMontage>`  
_L112-118_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAbilityRepAnimMontage>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L115-117_

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L116 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon70ded4020103`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetActor.h` (Public)


#### class `AGameplayAbilityTargetActor`  
`class AGameplayAbilityTargetActor : public AActor`  
_L27-106_
- reflection: `UCLASS(Blueprintable, abstract, notplaceable, MinimalAPI)`
- inherits: `AActor`
- desc: TargetActors are spawned to assist with ability targeting. They are spawned by ability tasks and create/determine the outgoing targeting data passed from one task to another WARNING: These actors are spawned once per ability activation and in their default form are not very efficient For most games you will need to subclass and heavily modify this actor, or you will want to implement similar functions in a game-specific actor or blueprint to avoid actor spawn costs This class is not well tested by internal games, but it is a useful class to look at to learn how target replication occurs
- L33 _public prototype_ `void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L37 _public member_ `bool ShouldProduceTargetDataOnServer;` — `UPROPERTY(EditAnywhere, Category=Advanced)` — The TargetData this class produces can be entirely generated on the server. We don't require the client to send us full or partial TargetData (possibly just a 'confirm')
- L42 _public member_ `FGameplayAbilityTargetingLocationInfo StartLocation;` — `UPROPERTY(BlueprintReadOnly, meta=(ExposeOnSpawn=true), Category=Targeting)` — `UPROPERTY(BlueprintReadOnly, meta = (ExposeOnSpawn = true), Replicated, Category = Targeting)` — Describes where the targeting action starts, usually the player character or a socket on the player character.
- L45 _public prototype_ `virtual void StartTargeting(UGameplayAbility* Ability);` — Initialize and begin targeting logic
- L47 _public prototype_ `virtual bool IsConfirmTargetingAllowed();`
- L50 _public prototype_ `virtual void ConfirmTargetingAndContinue();` — Requesting targeting data, but not necessarily stopping/destroying the task. Useful for external target data requests.
- L54 _public prototype_ `virtual void ConfirmTargeting();` — `UFUNCTION()` — Outside code is saying 'stop and just give me what you have.' Returns true if the ability accepts this and can be forgotten.
- L58 _public prototype_ `virtual void CancelTargeting();` — `UFUNCTION()` — Outside code is saying 'stop everything and just forget about it'
- L60 _public prototype_ `virtual void BindToConfirmCancelInputs();`
- L62 _public prototype_ `virtual bool ShouldProduceTargetData() const;`
- L65 _public prototype_ `virtual bool OnReplicatedTargetDataReceived(FGameplayAbilityTargetDataHandle& Data) const;` — Replicated target data was received from a client. Possibly sanitize/verify. return true if data is good and we should broadcast it as valid data.
- L69 _public member_ `FAbilityTargetData TargetDataReadyDelegate;`
- L70 _public member_ `FAbilityTargetData CanceledDelegate;`
- L72 _public prototype_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;`
- L75 _public member_ `TObjectPtr<APlayerController> PrimaryPC;` — `UPROPERTY(BlueprintReadOnly, Category = "Targeting")`
- L78 _public member_ `TObjectPtr<UGameplayAbility> OwningAbility;` — `UPROPERTY()`
- L81 _public member_ `bool bDestroyOnConfirmation;` — `UPROPERTY(BlueprintReadOnly, Replicated, Category = Targeting)`
- L84 _public member_ `TObjectPtr<AActor> SourceActor;` — `UPROPERTY(BlueprintReadOnly, Replicated, Category = Targeting)`
- L88 _public member_ `FWorldReticleParameters ReticleParams;` — `UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Targeting)` — Parameters for world reticle. Usage of these parameters is dependent on the reticle.
- L92 _public member_ `TSubclassOf<AGameplayAbilityWorldReticle> ReticleClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Targeting)` — Reticle that will appear on top of acquired targets. Reticles will be spawned/despawned as targets are acquired/lost.
- L95 _public member_ `FGameplayTargetDataFilterHandle Filter;` — `UPROPERTY(BlueprintReadWrite, Replicated, meta = (ExposeOnSpawn = true), Category = Targeting)`
- L99 _public member_ `bool bDebug;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, meta = (ExposeOnSpawn = true), Category = Targeting)` — Draw the debug information (if applicable) for this targeting actor.
- L101 _public member_ `FDelegateHandle GenericConfirmHandle;`
- L102 _public member_ `FDelegateHandle GenericCancelHandle;`
- L105 _public member_ `TObjectPtr<UAbilitySystemComponent> GenericDelegateBoundASC;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetActor_ActorPlacement.h` (Public)


#### class `AGameplayAbilityTargetActor_ActorPlacement`  
`class AGameplayAbilityTargetActor_ActorPlacement : public AGameplayAbilityTargetActor_GroundTrace`  
_L15-33_
- reflection: `UCLASS(Blueprintable)`
- inherits: `AGameplayAbilityTargetActor_GroundTrace`
- L19 _private prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L21 _private prototype_ `virtual void StartTargeting(UGameplayAbility* InAbility) override;`
- L25 _private member_ `TObjectPtr<UClass> PlacedActorClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Targeting)` — Actor we intend to place.
- L29 _private member_ `TObjectPtr<UMaterialInterface> PlacedActorMaterial;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Projectile)` — Override Material 0 on our placed actor's meshes with this material for visualization.
- L32 _private member_ `TWeakObjectPtr<AGameplayAbilityWorldReticle_ActorVisualization> ActorVisualizationReticle;` — Visualization for the intended location of the placed actor.

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetActor_GroundTrace.h` (Public)


#### class `AGameplayAbilityTargetActor_GroundTrace`  
`class AGameplayAbilityTargetActor_GroundTrace : public AGameplayAbilityTargetActor_Trace`  
_L18-44_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `AGameplayAbilityTargetActor_Trace`
- L22 _private prototype_ `virtual void StartTargeting(UGameplayAbility* InAbility) override;`
- L26 _private member_ `float CollisionRadius;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Targeting)` — Radius for a sphere or capsule.
- L30 _private member_ `float CollisionHeight;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Targeting)` — Height for a capsule. Implicitly indicates a capsule is desired if this is greater than zero.
- L35 _protected prototype_ `virtual FHitResult PerformTrace(AActor* InSourceActor) override;`
- L37 _protected prototype_ `virtual bool IsConfirmTargetingAllowed() override;`
- L39 _protected prototype_ `bool AdjustCollisionResultForShape(const FVector OriginalStartPoint, const FVector OriginalEndPoint, const FCollisionQueryParams Params, FHitResult& OutHitResult) const;`
- L41 _protected member_ `FCollisionShape CollisionShape;`
- L42 _protected member_ `float CollisionHeightOffset;` — When tracing, give this much extra height to avoid start-in-ground problems. Dealing with thick placement actors while standing near walls may be trickier.
- L43 _protected member_ `bool bLastTraceWasGood;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetActor_Radius.h` (Public)


#### class `AGameplayAbilityTargetActor_Radius`  
`class AGameplayAbilityTargetActor_Radius : public AGameplayAbilityTargetActor`  
_L17-37_
- reflection: `UCLASS(Blueprintable, notplaceable, MinimalAPI)`
- inherits: `AGameplayAbilityTargetActor`
- desc: Selects everything within a given radius of the source actor.
- L23 _public prototype_ `virtual void StartTargeting(UGameplayAbility* Ability) override;`
- L25 _public prototype_ `virtual void ConfirmTargetingAndContinue() override;`
- L29 _public member_ `float Radius;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Radius)` — Radius of target acquisition around the ability's start location.
- L33 _protected prototype_ `TArray<TWeakObjectPtr<AActor> > PerformOverlap(const FVector& Origin);`
- L35 _protected prototype_ `FGameplayAbilityTargetDataHandle MakeTargetData(const TArray<TWeakObjectPtr<AActor>>& Actors, const FVector& Origin) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetActor_SingleLineTrace.h` (Public)


#### class `AGameplayAbilityTargetActor_SingleLineTrace`  
`class AGameplayAbilityTargetActor_SingleLineTrace : public AGameplayAbilityTargetActor_Trace`  
_L14-20_
- reflection: `UCLASS(Blueprintable, MinimalAPI)`
- inherits: `AGameplayAbilityTargetActor_Trace`
- L19 _protected prototype_ `virtual FHitResult PerformTrace(AActor* InSourceActor) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetActor_Trace.h` (Public)


#### class `AGameplayAbilityTargetActor_Trace`  
`class AGameplayAbilityTargetActor_Trace : public AGameplayAbilityTargetActor`  
_L22-61_
- reflection: `UCLASS(Abstract, Blueprintable, notplaceable, config=Game, MinimalAPI)`
- inherits: `AGameplayAbilityTargetActor`
- desc: Intermediate base class for all line-trace type targeting actors.
- L27 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L30 _public prototype_ `static void LineTraceWithFilter(FHitResult& OutHitResult, const UWorld* World, const FGameplayTargetDataFilterHandle FilterHandle, const FVector& Start, const FVector& End, FName ProfileName, const FCollisionQueryParams Params);` — Traces as normal, but will manually filter all hit actors
- L33 _public prototype_ `static void SweepWithFilter(FHitResult& OutHitResult, const UWorld* World, const FGameplayTargetDataFilterHandle FilterHandle, const FVector& Start, const FVector& End, const FQuat& Rotation, const FCollisionShape CollisionShape, FName ProfileName, const FCollisionQueryParams Params);` — Sweeps as normal, but will manually filter all hit actors
- L35 _public prototype_ `void AimWithPlayerController(const AActor* InSourceActor, FCollisionQueryParams Params, const FVector& TraceStart, FVector& OutTraceEnd, bool bIgnorePitch = false) const;`
- L37 _public prototype_ `static bool ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition);`
- L39 _public prototype_ `virtual void StartTargeting(UGameplayAbility* Ability) override;`
- L41 _public prototype_ `virtual void ConfirmTargetingAndContinue() override;`
- L43 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L46 _public member_ `float MaxRange;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Trace)`
- L49 _public member_ `FCollisionProfileName TraceProfile;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, config, meta = (ExposeOnSpawn = true), Category = Trace)`
- L53 _public member_ `bool bTraceAffectsAimPitch;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Trace)` — Does the trace affect the aiming pitch
- L56 _protected prototype_ `virtual FHitResult PerformTrace(AActor* InSourceActor) PURE_VIRTUAL(AGameplayAbilityTargetActor_Trace, return FHitResult(););`
- L58 _protected prototype_ `FGameplayAbilityTargetDataHandle MakeTargetData(const FHitResult& HitResult) const;`
- L60 _protected member_ `TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;`

#### Free symbols / members of external scopes

- L16 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetDataFilter.h` (Public)


#### enum `ETargetDataFilterSelf::Type`  
`enum Type : int`  
_L17-22_
- L19 _public enumerator_ `TDFS_Any UMETA(DisplayName = "Allow self or others")`
- L20 _public enumerator_ `TDFS_NoSelf UMETA(DisplayName = "Filter self out")`
- L21 _public enumerator_ `TDFS_NoOthers UMETA(DisplayName = "Filter others out")`

#### struct `FGameplayTargetDataFilter`  
`struct FGameplayTargetDataFilter`  
_L27-81_
- reflection: `USTRUCT(BlueprintType)`
- desc: Simple actor target filter, games can subclass this
- L31 _public prototype_ `virtual ~FGameplayTargetDataFilter() = default;`
- L34 _public function_ `virtual bool FilterPassesForActor(const AActor* ActorToBeFiltered) const` — Returns true if the actor passes the filter and will be targeted
- L64 _public prototype_ `void InitializeFilterContext(AActor* FilterActor);` — Initializes SelfActor
- L68 _public member_ `TObjectPtr<AActor> SelfActor = nullptr;` — `UPROPERTY()` — Actor we're comparing against.
- L72 _public member_ `TSubclassOf<AActor> RequiredActorClass;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Filter)` — Subclass actors must be to pass the filter.
- L76 _public member_ `TEnumAsByte<ETargetDataFilterSelf::Type> SelfFilter = ETargetDataFilterSelf::TDFS_Any;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Filter)` — Filter based on whether or not this actor is "self."
- L80 _public member_ `bool bReverseFilter = false;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Filter)` — Reverses the meaning of the filter, so it will exclude all actors that pass.

#### struct `FGameplayTargetDataFilterHandle`  
`struct FGameplayTargetDataFilterHandle`  
_L85-125_
- reflection: `USTRUCT(BlueprintType)`
- desc: Polymorphic handle to filter structure that handles checking if actors should be targeted
- L89 _public member_ `TSharedPtr<FGameplayTargetDataFilter> Filter;`
- L92 _public function_ `bool FilterPassesForActor(const AActor* ActorToBeFiltered) const` — Returns true if the actor passes the filter and will be targeted
- L111 _public function_ `bool FilterPassesForActor(const TWeakObjectPtr<AActor> ActorToBeFiltered) const`
- L116 _public function_ `bool operator()(const TWeakObjectPtr<AActor> ActorToBeFiltered) const`
- L121 _public function_ `bool operator()(const AActor* ActorToBeFiltered) const`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L15 _namespace_ `namespace ETargetDataFilterSelf`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTargetTypes.h` (Public)


#### enum `EGameplayTargetingConfirmation::Type`  
`enum Type : int`  
_L29-42_
- desc: Describes how the targeting information is confirmed
- L32 _public enumerator_ `Instant` — The targeting happens instantly without special logic or user input deciding when to 'fire'
- L35 _public enumerator_ `UserConfirmed` — The targeting happens when the user confirms the targeting
- L38 _public enumerator_ `Custom` — The GameplayTargeting Ability is responsible for deciding when the targeting data is ready. Not supported by all TargetingActors
- L41 _public enumerator_ `CustomMulti` — The GameplayTargeting Ability is responsible for deciding when the targeting data is ready. Not supported by all TargetingActors. Should not destroy upon data production

#### struct `FGameplayAbilityTargetDataDeleter`  
`struct FGameplayAbilityTargetDataDeleter`  
_L49-52_
- desc: This type should be provided as the Deleter when creating a TSharedPtr<FGameplayAbilityTargetData> so that the Object's ScriptStruct data will be destructed correctly.
- L51 _public prototype_ `void operator()(FGameplayAbilityTargetData* Object) const;`

#### struct `FGameplayAbilityTargetData`  
`struct FGameplayAbilityTargetData`  
_L80-169_
- reflection: `USTRUCT()`
- desc: A generic structure for targeting data. We want generic functions to produce this data and other generic functions to consume this data. We expect this to be able to hold specific actors/object reference and also generic location/direction/origin information. Some example producers: -Overlap/Hit collision event generates TargetData about who was hit in a melee attack -A mouse input causes a hit trace and the actor infront of the crosshair is turned into TargetData -A mouse input causes TargetData to be generated from the owner's crosshair view origin/direction -An AOE/aura pulses and all actors in a radius around the instigator are added to TargetData -Panzer Dragoon style 'painting' targeting mode -MMORPG style ground AOE targeting style (potentially both a location on the ground and actors that were targeted) Some example consumers: -Apply a GameplayEffect to all actors in TargetData -Find closest actor from all in TargetData -Call some function on all actors in TargetData -Filter or merge TargetDatas -Spawn a new actor at a TargetData location Maybe it is better to distinguish between actor list targeting vs positional targeting data? -AOE/aura type of targeting data blurs the line
- L84 _public prototype_ `virtual ~FGameplayAbilityTargetData() = default;`
- L87 _public prototype_ `TArray<FActiveGameplayEffectHandle> ApplyGameplayEffect(const UGameplayEffect* GameplayEffect, const FGameplayEffectContextHandle& InEffectContext, float Level, FPredictionKey PredictionKey = FPredictionKey());` — Applies a gameplay effect to each target represented
- L90 _public prototype_ `virtual TArray<FActiveGameplayEffectHandle> ApplyGameplayEffectSpec(FGameplayEffectSpec& Spec, FPredictionKey PredictionKey = FPredictionKey());` — Applies a previously created gameplay effect spec to each target represented
- L93 _public prototype_ `virtual void AddTargetDataToContext(FGameplayEffectContextHandle& Context, bool bIncludeActorArray) const;` — Modifies the context and adds this target data to the target data handle stored within
- L96 _public function_ `virtual TArray<TWeakObjectPtr<AActor>> GetActors() const` — Returns all actors targeted, almost always overridden
- L102 _public function_ `virtual bool SetActors(TArray<TWeakObjectPtr<AActor>> NewActorArray)` — Modify the actor list
- L109 _public function_ `virtual bool HasHitResult() const` — Return true in subclasses if GetHitResult will work
- L115 _public function_ `virtual const FHitResult* GetHitResult() const` — Override to return a hit result
- L121 _public function_ `virtual bool HasOrigin() const` — Override to true if GetOrigin will work
- L127 _public function_ `virtual FTransform GetOrigin() const` — Override to return an origin point, which may be derived from other data
- L133 _public function_ `virtual bool HasEndPoint() const` — Override to true if GetEndPoint/Transform will work
- L139 _public function_ `virtual FVector GetEndPoint() const` — Override to return a target/end point
- L145 _public function_ `virtual FTransform GetEndPointTransform() const` — Override to return a transform, default will create one from just the location
- L151 _public function_ `virtual UScriptStruct* GetScriptStruct() const` — Returns the serialization data, must always be overridden
- L157 _public prototype_ `virtual FString ToString() const;` — Returns a debug string representation
- L160 _public function_ `virtual bool ShouldCheckForTargetActorSwap() const` — See notes on delegate definition FOnTargetActorSwapped
- L165 _public function_ `virtual void ReplaceHitWith(AActor* NewHitActor, const FHitResult* NewHitResult)`

#### enum `EGameplayAbilityTargetingLocationType::Type`  
`enum Type : int`  
_L175-185_
- desc: What type of location calculation to use when an ability asks for our transform
- L178 _public enumerator_ `LiteralTransform UMETA(DisplayName = "Literal Transform")` — We report an actual raw transform. This is also the final fallback if other methods fail
- L181 _public enumerator_ `ActorTransform UMETA(DisplayName = "Actor Transform")` — We pull the transform from an associated actor directly
- L184 _public enumerator_ `SocketTransform UMETA(DisplayName = "Socket Transform")` — We aim from a named socket on the player's skeletal mesh component

#### struct `FGameplayAbilityTargetDataHandle`  
`struct FGameplayAbilityTargetDataHandle`  
_L202-295_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle for Targeting Data. This servers two main purposes: -Avoid us having to copy around the full targeting data structure in Blueprints -Allows us to leverage polymorphism in the target data structure -Allows us to implement NetSerialize and replicate by value between clients/server -Avoid using UObjects could be used to give us polymorphism and by reference passing in blueprints. -However we would still be screwed when it came to replication -Replication by value -Pass by reference in blueprints -Polymophism in TargetData structure
- L206 _public function_ `FGameplayAbilityTargetDataHandle()`
- L207 _public function_ `FGameplayAbilityTargetDataHandle(FGameplayAbilityTargetData* DataPtr)`
- L212 _public function_ `FGameplayAbilityTargetDataHandle(FGameplayAbilityTargetDataHandle&& Other) : UniqueId(Other.UniqueId), Data(MoveTemp(Other.Data))`
- L213 _public function_ `FGameplayAbilityTargetDataHandle(const FGameplayAbilityTargetDataHandle& Other) : UniqueId(Other.UniqueId), Data(Other.Data)`
- L215 _public function_ `FGameplayAbilityTargetDataHandle& operator=(FGameplayAbilityTargetDataHandle&& Other)`
- L216 _public function_ `FGameplayAbilityTargetDataHandle& operator=(const FGameplayAbilityTargetDataHandle& Other)`
- L218 _public member_ `uint8 UniqueId = 0;`
- L221 _public member_ `TArray<TSharedPtr<FGameplayAbilityTargetData>, TInlineAllocator<1> > Data;` — Raw storage of target data, do not modify this directly
- L224 _public function_ `void Clear()` — Resets handle to have no targets
- L230 _public function_ `int32 Num() const` — Returns number of target data, not number of actors/targets as target data may contain multiple actors
- L236 _public function_ `bool IsValid(int32 Index) const` — Returns true if there are any valid targets
- L242 _public function_ `const FGameplayAbilityTargetData* Get(int32 Index) const` — Returns data at index, or nullptr if invalid
- L248 _public function_ `FGameplayAbilityTargetData* Get(int32 Index)` — Returns data at index, or nullptr if invalid
- L254 _public function_ `void Add(FGameplayAbilityTargetData* DataPtr)` — Adds a new target data to handle, it must have been created with new
- L260 _public function_ `void Append(const FGameplayAbilityTargetDataHandle& OtherHandle)` — Does a shallow copy of target data from one handle to another
- L266 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Serialize for networking, handles polymorphism
- L269 _public function_ `bool operator==(const FGameplayAbilityTargetDataHandle& Other) const` — Comparison operator
- L291 _public function_ `bool operator!=(const FGameplayAbilityTargetDataHandle& Other) const` — Comparison operator

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayAbilityTargetDataHandle> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetDataHandle>`  
_L298-306_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAbilityTargetDataHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L301-305_

#### struct `FGameplayAbilityTargetingLocationInfoFixLayout`  
`struct FGameplayAbilityTargetingLocationInfoFixLayout`  
_L309-312_
- desc: Hacky base class to avoid 8 bytes of padding after the vtable
- L311 _public prototype_ `virtual ~FGameplayAbilityTargetingLocationInfoFixLayout() = default;`

#### struct `FGameplayAbilityTargetingLocationInfo`  
`struct FGameplayAbilityTargetingLocationInfo #if CPP : public FGameplayAbilityTargetingLocationInfoFixLayout #endif`  
_L316-377_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FGameplayAbilityTargetingLocationInfoFixLayout`
- desc: Structure that stores a location in one of several different formats
- L323 _public function_ `FGameplayAbilityTargetingLocationInfo() : SourceActor(nullptr) , SourceComponent(nullptr) , SourceAbility(nullptr) , LocationType(EGameplayAbilityTargetingLocationType::LiteralTransform)`
- L330 _public prototype_ `virtual ~FGameplayAbilityTargetingLocationInfo() = default;`
- L332 _public function_ `void operator=(const FGameplayAbilityTargetingLocationInfo& Other)`
- L343 _public prototype_ `FTransform GetTargetingTransform() const;` — Converts internal format into a literal world space transform
- L345 _public prototype_ `FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromHitResult(TWeakObjectPtr<UGameplayAbility> Ability, const FHitResult& HitResult) const;` — Initializes new target data and fills in with hit results
- L346 _public prototype_ `FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromHitResults(TWeakObjectPtr<UGameplayAbility> Ability, const TArray<FHitResult>& HitResults) const;`
- L349 _public prototype_ `FGameplayAbilityTargetDataHandle MakeTargetDataHandleFromActors(const TArray<TWeakObjectPtr<AActor>>& TargetActors, bool OneActorPerHandle = false) const;` — Initializes new actor list target data, and sets this as the origin
- L353 _public member_ `TObjectPtr<AActor> SourceActor;` — `UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Targeting)` — A source actor is needed for Actor-based targeting, but not for Socket-based targeting.
- L357 _public member_ `TObjectPtr<UMeshComponent> SourceComponent;` — `UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Targeting)` — Socket-based targeting requires a skeletal mesh component to check for the named socket.
- L361 _public member_ `TObjectPtr<UGameplayAbility> SourceAbility;` — `UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Targeting)` — Ability that will be using the targeting data
- L365 _public member_ `FTransform LiteralTransform;` — `UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Targeting)` — A literal world transform can be used, if one has been calculated outside of the actor using the ability.
- L369 _public member_ `FName SourceSocketName;` — `UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Targeting)` — If SourceComponent is valid, this is the name of the socket transform that will be used. If no Socket is provided, SourceComponent's transform will be used.
- L373 _public member_ `TEnumAsByte<EGameplayAbilityTargetingLocationType::Type> LocationType;` — `UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = Targeting)` — Type of location used - will determine what data is transmitted over the network and what fields are used when calculating position.
- L376 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Optimized serialize function

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayAbilityTargetingLocationInfo> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetingLocationInfo>`  
_L380-386_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAbilityTargetingLocationInfo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L383-385_

#### struct `FGameplayAbilityTargetData_LocationInfo`  
`struct FGameplayAbilityTargetData_LocationInfo : public FGameplayAbilityTargetData`  
_L390-444_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FGameplayAbilityTargetData`
- desc: Target data with just a source and target location in space
- L396 _public member_ `FGameplayAbilityTargetingLocationInfo SourceLocation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targeting)` — Generic location data for source
- L400 _public member_ `FGameplayAbilityTargetingLocationInfo TargetLocation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targeting)` — Generic location data for target
- L404 _public function_ `virtual bool HasOrigin() const override`
- L409 _public function_ `virtual FTransform GetOrigin() const override`
- L416 _public function_ `virtual bool HasEndPoint() const override`
- L421 _public function_ `virtual FVector GetEndPoint() const override`
- L426 _public function_ `virtual FTransform GetEndPointTransform() const override`
- L433 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L438 _public function_ `virtual FString ToString() const override`
- L443 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayAbilityTargetData_LocationInfo> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_LocationInfo>`  
_L447-453_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_LocationInfo>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L450-452_

#### struct `FGameplayAbilityTargetData_ActorArray`  
`struct FGameplayAbilityTargetData_ActorArray : public FGameplayAbilityTargetData`  
_L457-547_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FGameplayAbilityTargetData`
- desc: Target data with a source location and a list of targeted actors, makes sense for AOE attacks
- L463 _public member_ `FGameplayAbilityTargetingLocationInfo SourceLocation;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Targeting)` — We could be selecting this group of actors from any type of location, so use a generic location type
- L467 _public member_ `TArray<TWeakObjectPtr<AActor> > TargetActorArray;` — `UPROPERTY(EditAnywhere, Category = Targeting)` — Rather than targeting a single point, this type of targeting selects multiple actors.
- L469 _public function_ `virtual TArray<TWeakObjectPtr<AActor> > GetActors() const override`
- L474 _public function_ `virtual bool SetActors(TArray<TWeakObjectPtr<AActor>> NewActorArray) override`
- L482 _public function_ `virtual bool HasOrigin() const override`
- L487 _public function_ `virtual FTransform GetOrigin() const override`
- L509 _public function_ `virtual bool HasEndPoint() const override`
- L522 _public function_ `virtual FVector GetEndPoint() const override`
- L536 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`
- L541 _public function_ `virtual FString ToString() const override`
- L546 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayAbilityTargetData_ActorArray> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_ActorArray>`  
_L550-556_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_ActorArray>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L553-555_

#### struct `FGameplayAbilityTargetData_SingleTargetHit`  
`struct FGameplayAbilityTargetData_SingleTargetHit : public FGameplayAbilityTargetData`  
_L560-643_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FGameplayAbilityTargetData`
- desc: Target data with a single hit result, data is packed into the hit result
- L564 _public function_ `FGameplayAbilityTargetData_SingleTargetHit()`
- L567 _public function_ `FGameplayAbilityTargetData_SingleTargetHit(FHitResult InHitResult) : HitResult(MoveTemp(InHitResult))`
- L573 _public function_ `virtual TArray<TWeakObjectPtr<AActor> > GetActors() const override`
- L587 _public function_ `virtual bool HasHitResult() const override`
- L592 _public function_ `virtual const FHitResult* GetHitResult() const override`
- L597 _public function_ `virtual bool HasOrigin() const override`
- L602 _public function_ `virtual FTransform GetOrigin() const override`
- L607 _public function_ `virtual bool HasEndPoint() const override`
- L612 _public function_ `virtual FVector GetEndPoint() const override`
- L617 _public function_ `virtual void ReplaceHitWith(AActor* NewHitActor, const FHitResult* NewHitResult)`
- L632 _public member_ `FHitResult HitResult;` — `UPROPERTY()` — Hit result that stores data
- L635 _public member_ `bool bHitReplaced = false;` — `UPROPERTY(NotReplicated)`
- L637 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L639 _public function_ `virtual UScriptStruct* GetScriptStruct() const override`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayAbilityTargetData_SingleTargetHit> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_SingleTargetHit>`  
_L646-652_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_SingleTargetHit>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L649-651_

#### enum `EAbilityGenericReplicatedEvent::Type`  
`enum Type : int`  
_L664-686_
- L667 _public enumerator_ `GenericConfirm = 0` — A generic confirmation to commit the ability
- L669 _public enumerator_ `GenericCancel` — A generic cancellation event. Not necessarily a canellation of the ability or targeting. Could be used to cancel out of a channelling portion of ability.
- L671 _public enumerator_ `InputPressed` — Additional input presses of the ability (Press X to activate ability, press X again while it is active to do other things within the GameplayAbility's logic)
- L673 _public enumerator_ `InputReleased` — Input release event of the ability
- L675 _public enumerator_ `GenericSignalFromClient` — A generic event from the client
- L677 _public enumerator_ `GenericSignalFromServer` — A generic event from the server
- L679 _public enumerator_ `GameCustom1` — Custom events for game use
- L680 _public enumerator_ `GameCustom2`
- L681 _public enumerator_ `GameCustom3`
- L682 _public enumerator_ `GameCustom4`
- L683 _public enumerator_ `GameCustom5`
- L684 _public enumerator_ `GameCustom6`
- L685 _public enumerator_ `MAX`

#### struct `FAbilityReplicatedData`  
`struct FAbilityReplicatedData`  
_L690-702_
- desc: Payload for generic replicated events
- L692 _public function_ `FAbilityReplicatedData() : bTriggered(false), VectorPayload(ForceInitToZero)`
- L695 _public member_ `bool bTriggered;` — Event has triggered
- L698 _public member_ `FVector_NetQuantize100 VectorPayload;` — Optional Vector payload for event
- L701 _public member_ `FSimpleMulticastDelegate Delegate;` — Delegate that will be called on replication

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L26 _namespace_ `namespace EGameplayTargetingConfirmation`
- L172 _namespace_ `namespace EGameplayAbilityTargetingLocationType`
- L302 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon894eb0070103`) — Necessary so that TSharedPtr<FGameplayAbilityTargetData> Data is copied around
- L303 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon894eb0070103`)
- L304 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon894eb0070103`)
- L384 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon894eb0070203`) — For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
- L451 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon894eb0070303`) — For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
- L554 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon894eb0070403`) — For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
- L650 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon894eb0070503`) — For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
- L655 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityTargetData, const FGameplayAbilityTargetDataHandle&);` — Generic callback for returning when target data is available
- L655 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityTargetData, const FGameplayAbilityTargetDataHandle&);` — Generic callback for returning when target data is available
- L658 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityTargetDataSetDelegate, const FGameplayAbilityTargetDataHandle&, FGameplayTag);` — Generic callback for returning when target data is available
- L658 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityTargetDataSetDelegate, const FGameplayAbilityTargetDataHandle&, FGameplayTag);` — Generic callback for returning when target data is available
- L662 _namespace_ `namespace EAbilityGenericReplicatedEvent`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTriggerType.h` (Public)


#### enum `EGameplayAbilityTriggerSource::Type`  
`enum Type : int`  
_L12-22_
- desc: Defines what type of trigger will activate the ability, paired to a tag
- L15 _public enumerator_ `GameplayEvent UMETA(DisplayName = "On Gameplay Event")` — Triggered by an external gameplay event. The ability will receive a GameplayEvent payload.
- L18 _public enumerator_ `OwnedTagAdded UMETA(DisplayName = "When Tag Is Added")` — Triggered when the owner gains the specified tag. Will not cancel when the tag is removed.
- L21 _public enumerator_ `OwnedTagPresent UMETA(DisplayName = "When Tag Is Present")` — Triggered when the owner has the specified tag. The ability will be canceled if the tag is later removed.

#### struct `FAbilityTriggerData`  
`struct FAbilityTriggerData`  
_L27-42_
- reflection: `USTRUCT()`
- desc: Structure that defines how an ability will be triggered by external events
- L31 _public function_ `FAbilityTriggerData() : TriggerSource(EGameplayAbilityTriggerSource::GameplayEvent)`
- L37 _public member_ `FGameplayTag TriggerTag;` — `UPROPERTY(EditAnywhere, Category=TriggerData, meta=(Categories="TriggerTagCategory"))` — The tag to respond to
- L41 _public member_ `TEnumAsByte<EGameplayAbilityTriggerSource::Type> TriggerSource;` — `UPROPERTY(EditAnywhere, Category=TriggerData)` — The type of trigger to respond to

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace EGameplayAbilityTriggerSource`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityTypes.h` (Public)


#### enum `EGameplayAbilityInstancingPolicy::Type`  
`enum Type : int`  
_L43-55_
- desc: How the ability is instanced when executed. This limits what an ability can do in its implementation. For example, a NonInstanced Ability cannot have state. It is probably unsafe for an InstancedPerActor ability to have latent actions, etc.
- L46 _public enumerator_ `NonInstanced UE_DEPRECATED_FORGAME(5.5, "Use InstancedPerActor as the default to avoid confusing corner cases")` — This ability is never instanced. Anything that executes the ability is operating on the CDO.
- L50 _public enumerator_ `InstancedPerActor UMETA(DisplayName = "Instanced Per Actor")` — Each actor gets it's own single instance of this ability, which supports replication to its owning actor to allow RPC's within the ability. As it is a single instance, only one ability maybe active at any time. State is saved between activations.
- L54 _public enumerator_ `InstancedPerExecution UMETA(DisplayName = "Instanced Per Execution")` — We instance this ability each time it is executed. Replication currently unsupported. These can have multiple running at the same time, and no state is saved between execution.

#### enum `EGameplayAbilityNetExecutionPolicy::Type`  
`enum Type : int`  
_L62-75_
- desc: Where does an ability execute on the network. Does a client "ask and predict", "ask and wait", "don't ask (just do it)"
- L65 _public enumerator_ `LocalPredicted UMETA(DisplayName = "Local Predicted")` — Part of this ability runs predictively on the local client if there is one
- L68 _public enumerator_ `LocalOnly UMETA(DisplayName = "Local Only")` — This ability will only run on the client or server that has local control
- L71 _public enumerator_ `ServerInitiated UMETA(DisplayName = "Server Initiated")` — This ability is initiated by the server, but will also run on the local client if one exists
- L74 _public enumerator_ `ServerOnly UMETA(DisplayName = "Server Only")` — This ability will only run on the server

#### enum `EGameplayAbilityNetSecurityPolicy::Type`  
`enum Type : int`  
_L82-95_
- desc: What protections does this ability have? Should the client be allowed to request changes to the execution of the ability?
- L85 _public enumerator_ `ClientOrServer UMETA(DisplayName = "Client Or Server")` — No security requirements. Client or server can trigger execution and termination of this ability freely.
- L88 _public enumerator_ `ServerOnlyExecution UMETA(DisplayName = "Server Only Execution")` — A client requesting execution of this ability will be ignored by the server. Clients can still request that the server cancel or end this ability.
- L91 _public enumerator_ `ServerOnlyTermination UMETA(DisplayName = "Server Only Termination")` — A client requesting cancellation or ending of this ability will be ignored by the server. Clients can still request execution of the ability.
- L94 _public enumerator_ `ServerOnly UMETA(DisplayName = "Server Only")` — Server controls both execution and termination of this ability. A client making any requests will be ignored.

#### enum `EGameplayAbilityReplicationPolicy::Type`  
`enum Type : int`  
_L102-109_
- desc: How an ability replicates state/events to everyone on the network
- L105 _public enumerator_ `ReplicateNo UMETA(DisplayName = "Do Not Replicate")` — We don't replicate the instance of the ability to anyone.
- L108 _public enumerator_ `ReplicateYes UMETA(DisplayName = "Replicate")` — We replicate the instance of the ability to the owner.

#### struct `FGameplayAbilityActorInfo`  
`struct FGameplayAbilityActorInfo`  
_L123-181_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayAbilityActorInfo Cached data associated with an Actor using an Ability. -Initialized from an AActor* in InitFromActor -Abilities use this to know what to actor upon. E.g., instead of being coupled to a specific actor class. -These are generally passed around as pointers to support polymorphism. -Projects can override UAbilitySystemGlobals::AllocAbilityActorInfo to override the default struct type that is created.
- L127 _public prototype_ `virtual ~FGameplayAbilityActorInfo() = default;`
- L131 _public member_ `TWeakObjectPtr<AActor> OwnerActor;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — The actor that owns the abilities, shouldn't be null
- L135 _public member_ `TWeakObjectPtr<AActor> AvatarActor;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — The physical representation of the owner, used for targeting and animation. This will often be null!
- L139 _public member_ `TWeakObjectPtr<APlayerController> PlayerController;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — PlayerController associated with the owning actor. This will often be null!
- L143 _public member_ `TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — Ability System component associated with the owner actor, shouldn't be null
- L147 _public member_ `TWeakObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — Skeletal mesh of the avatar actor. Often null
- L151 _public member_ `TWeakObjectPtr<UAnimInstance> AnimInstance;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — Anim instance of the avatar actor. Often null
- L155 _public member_ `TWeakObjectPtr<UMovementComponent> MovementComponent;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — Movement component of the avatar actor. Often null
- L159 _public member_ `FName AffectedAnimInstanceTag;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — The linked Anim Instance that this component will play montages in. Use NAME_None for the main anim instance.
- L162 _public prototype_ `UAnimInstance* GetAnimInstance() const;` — Accessor to get the affected anim instance from the SkeletalMeshComponent
- L165 _public prototype_ `bool IsLocallyControlled() const;` — Returns true if this actor is locally controlled. Only true for players on the client that owns them (differs from APawn::IsLocallyControlled which requires a Controller)
- L168 _public prototype_ `bool IsLocallyControlledPlayer() const;` — Returns true if this actor has a PlayerController that is locally controlled.
- L171 _public prototype_ `bool IsNetAuthority() const;` — Returns true if the owning actor has net authority
- L174 _public prototype_ `virtual void InitFromActor(AActor *OwnerActor, AActor *AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent);` — Initializes the info from an owning actor. Will set both owner and avatar
- L177 _public prototype_ `virtual void SetAvatarActor(AActor *AvatarActor);` — Sets a new avatar actor, keeps same owner and ability system component
- L180 _public prototype_ `virtual void ClearActorInfo();` — Clears out any actor info, both owner and avatar

#### struct `FGameplayAbilityLocalAnimMontage`  
`struct FGameplayAbilityLocalAnimMontage`  
_L187-211_
- reflection: `USTRUCT()`
- desc: Data about montages that were played locally (all montages in case of server. predictive montages in case of client). Never replicated directly.
- L191 _public function_ `FGameplayAbilityLocalAnimMontage() : AnimMontage(nullptr), PlayInstanceId(0), AnimatingAbility(nullptr)`
- L198 _public member_ `TObjectPtr<UAnimMontage> AnimMontage;` — `UPROPERTY()` — What montage is being played
- L202 _public member_ `uint8 PlayInstanceId;` — `UPROPERTY()` — ID tied to a particular play of a montage, used to trigger replication when the same montage is played multiple times. This ID wraps around when it reaches its max value.
- L206 _public member_ `FPredictionKey PredictionKey;` — `UPROPERTY()` — Prediction key that started the montage play
- L210 _public member_ `TWeakObjectPtr<UGameplayAbility> AnimatingAbility;` — `UPROPERTY()` — The ability, if any, that instigated this montage

#### struct `FGameplayEventData`  
`struct FGameplayEventData`  
_L216-268_
- reflection: `USTRUCT(BlueprintType)`
- desc: Metadata for a tag-based Gameplay Event, that can activate other abilities or run ability-specific logic
- L220 _public function_ `FGameplayEventData() : Instigator(nullptr) , Target(nullptr) , OptionalObject(nullptr) , OptionalObject2(nullptr) , EventMagnitude(0.f)`
- L231 _public member_ `FGameplayTag EventTag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload, meta=(GameplayTagFilter="GameplayEventTagsCategory"))` — Tag of the event that triggered this
- L235 _public member_ `TObjectPtr<const AActor> Instigator;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — The instigator of the event
- L239 _public member_ `TObjectPtr<const AActor> Target;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — The target of the event
- L243 _public member_ `TObjectPtr<const UObject> OptionalObject;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — An optional ability-specific object to be passed though the event
- L247 _public member_ `TObjectPtr<const UObject> OptionalObject2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — A second optional ability-specific object to be passed though the event
- L251 _public member_ `FGameplayEffectContextHandle ContextHandle;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — Polymorphic context information
- L255 _public member_ `FGameplayTagContainer InstigatorTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — Tags that the instigator has
- L259 _public member_ `FGameplayTagContainer TargetTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — Tags that the target has
- L263 _public member_ `float EventMagnitude;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — The magnitude of the triggering event
- L267 _public member_ `FGameplayAbilityTargetDataHandle TargetData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayAbilityTriggerPayload)` — The polymorphic target information for the event

#### struct `FAbilityEndedData`  
`struct FAbilityEndedData`  
_L279-313_
- reflection: `USTRUCT(BlueprintType)`
- desc: Ability Ended Data
- L283 _public function_ `FAbilityEndedData() : AbilityThatEnded(nullptr) , bReplicateEndAbility(false) , bWasCancelled(false)`
- L290 _public function_ `FAbilityEndedData(UGameplayAbility* InAbility, FGameplayAbilitySpecHandle InHandle, bool bInReplicateEndAbility, bool bInWasCancelled) : AbilityThatEnded(InAbility) , AbilitySpecHandle(InHandle) , bReplicateEndAbility(bInReplicateEndAbility) , bWasCancelled(bInWasCancelled)`
- L300 _public member_ `TObjectPtr<UGameplayAbility> AbilityThatEnded;` — `UPROPERTY()` — Ability that ended, normally instance but could be CDO
- L304 _public member_ `FGameplayAbilitySpecHandle AbilitySpecHandle;` — `UPROPERTY()` — Specific ability spec that ended
- L308 _public member_ `bool bReplicateEndAbility;` — `UPROPERTY()` — Rather to replicate the ability to ending
- L312 _public member_ `bool bWasCancelled;` — `UPROPERTY()` — True if this was cancelled deliberately, false if it ended normally

#### struct `FGameplayAbilityInputBinds`  
`struct FGameplayAbilityInputBinds`  
_L320-355_
- desc: Structure that tells AbilitySystemComponent what to bind to an InputComponent (see BindAbilityActivationToInputComponent)
- L322 _public function_ `FGameplayAbilityInputBinds(FString InConfirmTargetCommand, FString InCancelTargetCommand, FTopLevelAssetPath InEnumPathName, int32 InConfirmTargetInputID = INDEX_NONE, int32 InCancelTargetInputID = INDEX_NONE) : ConfirmTargetCommand(InConfirmTargetCommand) , CancelTargetCommand(InCancelTargetCommand) , EnumPathName(InEnumPathName) , ConfirmTargetInputID(InConfirmTargetInputID) , CancelTargetInputID(InCancelTargetInputID)`
- L331 _public prototype_ `FGameplayAbilityInputBinds(FGameplayAbilityInputBinds&&) = default;`
- L332 _public prototype_ `FGameplayAbilityInputBinds(const FGameplayAbilityInputBinds&) = default;`
- L333 _public prototype_ `FGameplayAbilityInputBinds& operator=(FGameplayAbilityInputBinds&&) = default;`
- L334 _public prototype_ `FGameplayAbilityInputBinds& operator=(const FGameplayAbilityInputBinds&) = default;`
- L337 _public member_ `FString ConfirmTargetCommand;` — Defines command string that will be bound to Confirm Targeting
- L340 _public member_ `FString CancelTargetCommand;` — Defines command string that will be bound to Cancel Targeting
- L343 _public member_ `FTopLevelAssetPath EnumPathName;` — Returns enum to use for ability binds. E.g., "Ability1"-"Ability9" input commands will be bound to ability activations inside the AbiltiySystemComponent
- L346 _public member_ `int32 ConfirmTargetInputID;` — If >=0, Confirm is bound to an entry in the enum
- L349 _public member_ `int32 CancelTargetInputID;` — If >=0, Cancel is bound to an entry in the enum
- L351 _public function_ `UEnum* GetBindEnum()`

#### struct `FAttributeDefaults`  
`struct FAttributeDefaults`  
_L360-373_
- reflection: `USTRUCT()`
- desc: Used to initialize default values for attributes
- L364 _public function_ `FAttributeDefaults() : DefaultStartingTable(nullptr)`
- L369 _public member_ `TSubclassOf<UAttributeSet> Attributes;` — `UPROPERTY(EditAnywhere, Category = "AttributeTest")`
- L372 _public member_ `TObjectPtr<UDataTable> DefaultStartingTable;` — `UPROPERTY(EditAnywhere, Category = "AttributeTest")`

#### struct `FAbilityTaskDebugMessage`  
`struct FAbilityTaskDebugMessage`  
_L378-391_
- reflection: `USTRUCT()`
- desc: Debug message emitted by ability tasks
- L382 _public function_ `FAbilityTaskDebugMessage() : FromTask(nullptr)`
- L387 _public member_ `TObjectPtr<UGameplayTask> FromTask;` — `UPROPERTY()`
- L390 _public member_ `FString Message;` — `UPROPERTY()`

#### struct `FServerAbilityRPCBatch`  
`struct FServerAbilityRPCBatch`  
_L402-435_
- reflection: `USTRUCT()`
- desc: This struct holds state to batch server RPC calls: ServerTryActivateAbility, ServerSetReplicatedTargetData, ServerEndAbility.
- L406 _public function_ `FServerAbilityRPCBatch() : InputPressed(false), Ended(false), Started(false)`
- L412 _public member_ `FGameplayAbilitySpecHandle AbilitySpecHandle;` — `UPROPERTY()`
- L415 _public member_ `FPredictionKey PredictionKey;` — `UPROPERTY()`
- L418 _public member_ `FGameplayAbilityTargetDataHandle TargetData;` — `UPROPERTY()`
- L421 _public member_ `bool InputPressed;` — `UPROPERTY()`
- L424 _public member_ `bool Ended;` — `UPROPERTY()`
- L428 _public member_ `bool Started;` — `UPROPERTY(NotReplicated)` — Safety bool to make sure ServerTryActivate was called exactly one time in a batch
- L431 _public function_ `bool operator==(const FGameplayAbilitySpecHandle& InHandle) const` — To allow FindByKey etc

#### struct `FScopedServerAbilityRPCBatcher`  
`struct FScopedServerAbilityRPCBatcher`  
_L439-449_
- desc: Helper struct for defining ServerRPC batch windows. If null ASC is passed in, this becomes a noop.
- L441 _public prototype_ `FScopedServerAbilityRPCBatcher(UAbilitySystemComponent* InASC, FGameplayAbilitySpecHandle InAbilityHandle);`
- L442 _public prototype_ `~FScopedServerAbilityRPCBatcher();`
- L446 _private member_ `UAbilitySystemComponent* ASC;`
- L447 _private member_ `FGameplayAbilitySpecHandle AbilityHandle;`
- L448 _private member_ `FScopedPredictionWindow ScopedPredictionWindow;`

#### struct `FGameplayAbilitySpecHandleAndPredictionKey`  
`struct FGameplayAbilitySpecHandleAndPredictionKey`  
_L454-486_
- reflection: `USTRUCT()`
- desc: Used as a key for storing internal ability data
- L458 _public function_ `FGameplayAbilitySpecHandleAndPredictionKey() : PredictionKeyAtCreation(0)`
- L462 _public function_ `FGameplayAbilitySpecHandleAndPredictionKey(const FGameplayAbilitySpecHandle& HandleRef, const FPredictionKey& PredictionKeyAtCreationRef) : AbilityHandle(HandleRef), PredictionKeyAtCreation(PredictionKeyAtCreationRef.Current)`
- L466 _public function_ `bool operator==(const FGameplayAbilitySpecHandleAndPredictionKey& Other) const`
- L471 _public function_ `bool operator!=(const FGameplayAbilitySpecHandleAndPredictionKey& Other) const`
- L482 _public member_ `FGameplayAbilitySpecHandle AbilityHandle;` — `UPROPERTY()`
- L485 _public member_ `int32 PredictionKeyAtCreation;` — `UPROPERTY()`

#### struct `FAbilityReplicatedDataCache`  
`struct FAbilityReplicatedDataCache`  
_L489-543_
- desc: Struct defining the cached data for a specific gameplay ability. This data is generally synchronized client->server in a network game.
- L492 _public member_ `FGameplayAbilityTargetDataHandle TargetData;` — What elements this activation is targeting
- L495 _public member_ `FGameplayTag ApplicationTag;` — What tag to pass through when doing an application
- L498 _public member_ `bool bTargetConfirmed;` — True if we've been positively confirmed our targeting, false if we don't know
- L501 _public member_ `bool bTargetCancelled;` — True if we've been positively cancelled our targeting, false if we don't know
- L504 _public member_ `FAbilityTargetDataSetDelegate TargetSetDelegate;` — Delegate to call whenever this is modified
- L507 _public member_ `FSimpleMulticastDelegate TargetCancelledDelegate;` — Delegate to call whenever this is confirmed (without target data)
- L510 _public member_ `FAbilityReplicatedData GenericEvents[EAbilityGenericReplicatedEvent::MAX];` — Generic events that contain no payload data
- L513 _public member_ `FPredictionKey PredictionKey;` — Prediction Key when this data was set
- L515 _public function_ `FAbilityReplicatedDataCache() : bTargetConfirmed(false), bTargetCancelled(false)`
- L516 _public prototype_ `virtual ~FAbilityReplicatedDataCache() = default;`
- L519 _public function_ `void Reset()` — Resets any cached data, leaves delegates up
- L533 _public function_ `void ResetAll()` — Resets cached data and clears delegates.

#### struct `FGameplayAbilityReplicatedDataContainer`  
`struct FGameplayAbilityReplicatedDataContainer`  
_L554-568_
- desc: Associative container of GameplayAbilitySpecs + PredictionKeys --> FAbilityReplicatedDataCache. Basically, it holds replicated data on the ability system component that abilities access in their scripting. This was refactored from a normal TMap. This mainly serves to: 1. Return shared ptrs to the cached data so that callsites are not vulnerable to the underlying map shifting around (E.g invoking a replicated event ends the ability or activates a new one and causes memory to move, invalidating the pointer). 2. Data is cleared on ability end via ::Remove. 3. The FAbilityReplicatedDataCache instances are recycled rather than allocated each time via ::FreeData.
- L556 _public prototype_ `TSharedPtr<FAbilityReplicatedDataCache> Find(const FGameplayAbilitySpecHandleAndPredictionKey& Key) const;`
- L557 _public prototype_ `TSharedRef<FAbilityReplicatedDataCache> FindOrAdd(const FGameplayAbilitySpecHandleAndPredictionKey& Key);`
- L559 _public prototype_ `void Remove(const FGameplayAbilitySpecHandleAndPredictionKey& Key);`
- L560 _public prototype_ `void PrintDebug();`
- L564 _private typedef_ `typedef TPair<FGameplayAbilitySpecHandleAndPredictionKey, TSharedRef<FAbilityReplicatedDataCache>> FKeyDataPair;`
- L566 _private member_ `TArray<FKeyDataPair> InUseData;`
- L567 _private member_ `TArray<TSharedRef<FAbilityReplicatedDataCache>> FreeData;`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L31 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAbilitySystemComponent, Log, All);`
- L33 _macro_ `#define ENABLE_ABILITYTASK_DEBUGMSG !(UE_BUILD_SHIPPING | UE_BUILD_TEST)`
- L37 _namespace_ `namespace EGameplayAbilityInstancingPolicy`
- L59 _namespace_ `namespace EGameplayAbilityNetExecutionPolicy`
- L79 _namespace_ `namespace EGameplayAbilityNetSecurityPolicy`
- L99 _namespace_ `namespace EGameplayAbilityReplicationPolicy`
- L271 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayEventMulticastDelegate, const FGameplayEventData*);` — Delegate for handling gameplay event data
- L271 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayEventMulticastDelegate, const FGameplayEventData*);` — Delegate for handling gameplay event data
- L274 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FGameplayEventTagMulticastDelegate, FGameplayTag, const FGameplayEventData*);` — Delegate for handling gameplay event data, includes tag as the Event Data does not always have it filled out
- L274 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FGameplayEventTagMulticastDelegate, FGameplayTag, const FGameplayEventData*);` — Delegate for handling gameplay event data, includes tag as the Event Data does not always have it filled out
- L316 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayAbilityEndedDelegate, const FAbilityEndedData&);` — Notification delegate definition for when the gameplay ability ends
- L316 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGameplayAbilityEndedDelegate, const FAbilityEndedData&);` — Notification delegate definition for when the gameplay ability ends
- L394 _delegate_ `DECLARE_MULTICAST_DELEGATE(FAbilitySystemComponentPredictionKeyClear);` — Used for cleaning up predicted data on network clients
- L394 _prototype_ `DECLARE_MULTICAST_DELEGATE(FAbilitySystemComponentPredictionKeyClear);` — Used for cleaning up predicted data on network clients
- L397 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGenericAbilityDelegate, UGameplayAbility*);` — Generic delegate for ability 'events'/notifies
- L397 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FGenericAbilityDelegate, UGameplayAbility*);` — Generic delegate for ability 'events'/notifies
- L476 _function_ `friend uint32 GetTypeHash(const FGameplayAbilitySpecHandleAndPredictionKey& Handle)`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityWorldReticle.h` (Public)


#### struct `FWorldReticleParameters`  
`struct FWorldReticleParameters`  
_L15-27_
- reflection: `USTRUCT(BlueprintType)`
- L20 _public function_ `void Initialize(FVector InAOEScale)` — Use this so that we can't slip in new parameters without some actor knowing about it.
- L26 _public member_ `FVector AOEScale = FVector(0.f);` — `UPROPERTY(BlueprintReadWrite, Category = Reticle)`

#### class `AGameplayAbilityWorldReticle`  
`class AGameplayAbilityWorldReticle : public AActor`  
_L31-95_
- reflection: `UCLASS(Blueprintable, notplaceable, MinimalAPI)`
- inherits: `AActor`
- desc: Reticles allow targeting to be visualized. Tasks can spawn these. Artists/designers can create BPs for these.
- L37 _public prototype_ `virtual void Tick(float DeltaSeconds) override;`
- L41 _public prototype_ `virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;`
- L43 _public prototype_ `void InitializeReticle(AGameplayAbilityTargetActor* InTargetingActor, APlayerController* PlayerController, FWorldReticleParameters InParameters);`
- L45 _public prototype_ `void SetIsTargetValid(bool bNewValue);`
- L46 _public prototype_ `void SetIsTargetAnActor(bool bNewValue);`
- L50 _public prototype_ `void OnValidTargetChanged(bool bNewValue);` — `UFUNCTION(BlueprintImplementableEvent, Category = Reticle)` — Called whenever bIsTargetValid changes value.
- L54 _public prototype_ `void OnTargetingAnActor(bool bNewValue);` — `UFUNCTION(BlueprintImplementableEvent, Category = Reticle)` — Called whenever bIsTargetAnActor changes value.
- L57 _public prototype_ `void OnParametersInitialized();` — `UFUNCTION(BlueprintImplementableEvent, Category = Reticle)`
- L60 _public prototype_ `void SetReticleMaterialParamFloat(FName ParamName, float value);` — `UFUNCTION(BlueprintImplementableEvent, Category = Reticle)`
- L63 _public prototype_ `void SetReticleMaterialParamVector(FName ParamName, FVector value);` — `UFUNCTION(BlueprintImplementableEvent, Category = Reticle)`
- L66 _public prototype_ `void FaceTowardSource(bool bFaceIn2D);` — `UFUNCTION(BlueprintCallable, Category = Reticle)`
- L69 _public member_ `FWorldReticleParameters Parameters;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Reticle")`
- L73 _public member_ `bool bFaceOwnerFlat;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Reticle")` — Makes the reticle's default owner-facing behavior operate in 2D (flat) instead of 3D (pitched). Defaults to true.
- L77 _public member_ `bool bSnapToTargetedActor;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"), Category = "Reticle")` — If the target is an actor snap to it's location
- L82 _protected member_ `bool bIsTargetValid;` — `UPROPERTY(BlueprintReadOnly, Category = "Network")` — This indicates whether or not the targeting actor considers the current target to be valid. Defaults to true.
- L86 _protected member_ `bool bIsTargetAnActor;` — `UPROPERTY(BlueprintReadOnly, Category = "Network")` — This indicates whether or not the targeting reticle is pointed at an actor. Defaults to false.
- L90 _protected member_ `TObjectPtr<APlayerController> PrimaryPC;` — `UPROPERTY(BlueprintReadOnly, Category = "Network")` — This is used in the process of determining whether we should replicate to a specific client.
- L94 _protected member_ `TObjectPtr<AGameplayAbilityTargetActor> TargetingActor;` — `UPROPERTY(BlueprintReadOnly, Category = "Network")` — In the future, we may want to grab things like sockets off of this.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbilityWorldReticle_ActorVisualization.h` (Public)


#### class `AGameplayAbilityWorldReticle_ActorVisualization`  
`class AGameplayAbilityWorldReticle_ActorVisualization : public AGameplayAbilityWorldReticle`  
_L17-38_
- reflection: `UCLASS(notplaceable)`
- inherits: `AGameplayAbilityWorldReticle`
- desc: This is a dummy reticle for internal use by visualization placement tasks. It builds a custom visual model of the visualization being placed.
- L22 _public prototype_ `void InitializeReticleVisualizationInformation(AGameplayAbilityTargetActor* InTargetingActor, AActor* VisualizationActor, UMaterialInterface *VisualizationMaterial);`
- L27 _private member_ `TObjectPtr<class UCapsuleComponent> CollisionComponent;` — `UPROPERTY()` — Hardcoded collision component, so other objects don't think they can collide with the visualization actor
- L31 _public member_ `TArray<TObjectPtr<UActorComponent>> VisualizationComponents;` — `UPROPERTY()`
- L34 _public prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;` — Overridable function called whenever this actor is being removed from a level
- L37 _public function_ `class UCapsuleComponent* GetCollisionComponent()` — Returns CollisionComponent subobject

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility_CharacterJump.h` (Public)


#### class `UGameplayAbility_CharacterJump`  
`class UGameplayAbility_CharacterJump : public UGameplayAbility`  
_L17-30_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayAbility`
- desc: Ability that jumps with a character.
- L23 _public prototype_ `virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;`
- L25 _public prototype_ `virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;`
- L27 _public prototype_ `virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;`
- L29 _public prototype_ `virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/GameplayAbility_Montage.h` (Public)


#### class `UGameplayAbility_Montage`  
`class UGameplayAbility_Montage : public UGameplayAbility`  
_L22-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UGameplayAbility`
- desc: A gameplay ability that plays a single montage and applies a GameplayEffect
- L28 _public prototype_ `virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* OwnerInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;`
- L31 _public member_ `TObjectPtr<UAnimMontage> MontageToPlay;` — `UPROPERTY(EditDefaultsOnly, Category = MontageAbility)`
- L34 _public member_ `float PlayRate;` — `UPROPERTY(EditDefaultsOnly, Category = MontageAbility)`
- L37 _public member_ `FName SectionName;` — `UPROPERTY(EditDefaultsOnly, Category = MontageAbility)`
- L41 _public member_ `TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClassesWhileAnimating;` — `UPROPERTY(EditDefaultsOnly, Category = MontageAbility)` — GameplayEffects to apply and then remove while the animation is playing
- L45 _public member_ `TArray<TObjectPtr<const UGameplayEffect>> GameplayEffectsWhileAnimating;` — `UPROPERTY(VisibleDefaultsOnly, Category = Deprecated)` — Deprecated. Use GameplayEffectClassesWhileAnimating instead.
- L47 _public prototype_ `void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent, TArray<struct FActiveGameplayEffectHandle> AppliedEffects);`
- L49 _public prototype_ `void GetGameplayEffectsWhileAnimating(TArray<const UGameplayEffect*>& OutEffects) const;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask.h` (Public)


#### enum `EAbilityTaskWaitState`  
`enum class EAbilityTaskWaitState : uint8`  
_L77-87_
- reflection: `UENUM()`
- desc: Latent tasks are waiting on something. This is to differeniate waiting on the user to do something vs waiting on the game to do something. Tasks start WaitingOnGame, and are set to WaitingOnUser when appropriate (see WaitTargetData, WaitIiputPress, etc)
- L80 _public enumerator_ `WaitingOnGame = 0x01` — Task is waiting for the game to do something
- L83 _public enumerator_ `WaitingOnUser = 0x02` — Waiting for the user to do something
- L86 _public enumerator_ `WaitingOnAvatar = 0x04` — Waiting on Avatar (Character/Pawn/Actor) to do something (usually something physical in the world, like land, move, etc)

#### class `UAbilityTask`  
`class UAbilityTask : public UGameplayTask`  
_L90-180_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UGameplayTask`
- L94 _private prototype_ `virtual void OnDestroy(bool bInOwnerFinished) override;`
- L95 _private prototype_ `virtual void BeginDestroy() override;`
- L101 _private prototype_ `virtual void PreDestroyFromReplication() override;` — Clears potential dangling pointers. Added to prevent dangling pointer to GameplayAbility that issued the task. When overriding use EndTask() instead.
- L104 _private prototype_ `FGameplayAbilitySpecHandle GetAbilitySpecHandle() const;` — Returns spec handle for owning ability
- L106 _private prototype_ `void SetAbilitySystemComponent(UAbilitySystemComponent* InAbilitySystemComponent);`
- L110 _private member_ `TObjectPtr<UGameplayAbility> Ability;` — `UPROPERTY()` — GameplayAbility that created us
- L113 _private member_ `TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;` — `UPROPERTY()`
- L116 _private prototype_ `bool IsPredictingClient() const;` — Returns true if the ability is a locally predicted ability running on a client. Usually this means we need to tell the server something.
- L119 _private prototype_ `bool IsForRemoteClient() const;` — Returns true if we are executing the ability on the server for a non locally controlled client
- L122 _private prototype_ `bool IsLocallyControlled() const;` — Returns true if we are executing the ability on the locally controlled client
- L125 _private prototype_ `FPredictionKey GetActivationPredictionKey() const;` — Returns ActivationPredictionKey of owning ability
- L128 _private prototype_ `bool ShouldBroadcastAbilityTaskDelegates() const;` — This should be called prior to broadcasting delegates back into the ability graph. This makes sure the ability is still active.
- L130 _private prototype_ `virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;`
- L132 _private prototype_ `static void DebugRecordAbilityTaskCreatedByAbility(const UObject* Ability);`
- L136 _private function_ `template <class T> static T* NewAbilityTask(UGameplayAbility* ThisAbility, FName InstanceName = FName())` — Helper function for instantiating and initializing a new task
- L150 _private function_ `template<typename T> static bool DelayedFalse()`
- L157 _private function_ `template <class T> inline static T* NewTask(UObject* WorldContextObject, FName InstanceName = FName())` — this function has been added to make sure AbilityTasks don't use this method
- L164 _private prototype_ `void SetWaitingOnRemotePlayerData();` — Called when the ability task is waiting on remote player data. IF the remote player ends the ability prematurely, and a task with this set is still running, the ability is killed.
- L165 _private prototype_ `void ClearWaitingOnRemotePlayerData();`
- L166 _private prototype_ `virtual bool IsWaitingOnRemotePlayerdata() const override;`
- L169 _private prototype_ `void SetWaitingOnAvatar();` — same as RemotePlayerData but for ACharacter type of state (movement state, etc)
- L170 _private prototype_ `void ClearWaitingOnAvatar();`
- L171 _private prototype_ `virtual bool IsWaitingOnAvatar() const override;`
- L174 _private member_ `uint8 WaitStateBitMask;` — What we are waiting on
- L175 _private member_ `uint8 bWasSuccessfullyDestroyed : 1;`
- L179 _protected prototype_ `bool CallOrAddReplicatedDelegate(EAbilityGenericReplicatedEvent::Type Event, FSimpleMulticastDelegate::FDelegate Delegate);` — Helper method for registering client replicated callbacks

#### struct `FAbilityInstanceNamePredicate`  
`struct FAbilityInstanceNamePredicate`  
_L183-196_
- desc: For searching through lists of ability instances
- L185 _public function_ `FAbilityInstanceNamePredicate(FName DesiredInstanceName)`
- L190 _public function_ `bool operator()(const TWeakObjectPtr<UAbilityTask> A) const`
- L195 _public member_ `FName InstanceName;`

#### struct `FAbilityInstanceClassPredicate`  
`struct FAbilityInstanceClassPredicate`  
_L198-211_
- L200 _public function_ `FAbilityInstanceClassPredicate(TSubclassOf<UAbilityTask> Class)`
- L205 _public function_ `bool operator()(const TWeakObjectPtr<UAbilityTask> A) const`
- L210 _public member_ `TSubclassOf<UAbilityTask> TaskClass;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L213 _macro_ `#define ABILITYTASK_MSG(Format, ...) \`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h` (Public)


#### class `UAbilityTask_ApplyRootMotionConstantForce`  
`class UAbilityTask_ApplyRootMotionConstantForce : public UAbilityTask_ApplyRootMotion_Base`  
_L24-84_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_ApplyRootMotion_Base`
- desc: Applies force to character's movement
- L29 _private member_ `FApplyRootMotionConstantForceDelegate OnFinish;` — `UPROPERTY(BlueprintAssignable)`
- L33 _private prototype_ `static UAbilityTask_ApplyRootMotionConstantForce* ApplyRootMotionConstantForce ( UGameplayAbility* OwningAbility, FName TaskInstanceName, FVector WorldDirection, float Strength, float Duration, bool bIsAdditive, UCurveFloat* StrengthOverTime, ERootMotionFinishVelocityMode VelocityOnFinishMode, FVector SetVelocityOnFinish, float ClampVelocityOnFinish, bool bEnableGravity );` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Apply force to character's movement
- L49 _private prototype_ `virtual void TickTask(float DeltaTime) override;` — Tick function for this task, if bTickingTask == true
- L51 _private prototype_ `virtual void PreDestroyFromReplication() override;`
- L52 _private prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L56 _protected prototype_ `virtual void SharedInitAndApply() override;`
- L61 _protected member_ `FVector WorldDirection;` — `UPROPERTY(Replicated)`
- L64 _protected member_ `float Strength;` — `UPROPERTY(Replicated)`
- L67 _protected member_ `float Duration;` — `UPROPERTY(Replicated)`
- L70 _protected member_ `bool bIsAdditive;` — `UPROPERTY(Replicated)`
- L79 _protected member_ `TObjectPtr<UCurveFloat> StrengthOverTime;` — `UPROPERTY(Replicated)` — Strength of the force over time Curve Y is 0 to 1 which is percent of full Strength parameter to apply Curve X is 0 to 1 normalized time if this force has a limited duration (Duration > 0), or is in units of seconds if this force has unlimited duration (Duration < 0)
- L82 _protected member_ `bool bEnableGravity;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionConstantForceDelegate);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionConstantForceDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_ApplyRootMotionJumpForce.h` (Public)


#### class `UAbilityTask_ApplyRootMotionJumpForce`  
`class UAbilityTask_ApplyRootMotionJumpForce : public UAbilityTask_ApplyRootMotion_Base`  
_L25-100_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_ApplyRootMotion_Base`
- desc: Applies force to character's movement
- L30 _private member_ `FApplyRootMotionJumpForceDelegate OnFinish;` — `UPROPERTY(BlueprintAssignable)`
- L33 _private member_ `FApplyRootMotionJumpForceDelegate OnLanded;` — `UPROPERTY(BlueprintAssignable)`
- L36 _private prototype_ `void Finish();` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks")`
- L39 _private prototype_ `void OnLandedCallback(const FHitResult& Hit);` — `UFUNCTION()`
- L43 _private prototype_ `static UAbilityTask_ApplyRootMotionJumpForce* ApplyRootMotionJumpForce(UGameplayAbility* OwningAbility, FName TaskInstanceName, FRotator Rotation, float Distance, float Height, float Duration, float MinimumLandedTriggerTime, bool bFinishOnLanded, ERootMotionFinishVelocityMode VelocityOnFinishMode, FVector SetVelocityOnFinish, float ClampVelocityOnFinish, UCurveVector* PathOffsetCurve, UCurveFloat* TimeMappingCurve);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Apply force to character's movement
- L46 _private prototype_ `virtual void Activate() override;`
- L49 _private prototype_ `virtual void TickTask(float DeltaTime) override;` — Tick function for this task, if bTickingTask == true
- L51 _private prototype_ `virtual void PreDestroyFromReplication() override;`
- L52 _private prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L56 _protected prototype_ `virtual void SharedInitAndApply() override;`
- L64 _protected prototype_ `void TriggerLanded();` — Work-around for OnLanded being called during bClientUpdating in movement replay code Don't want to trigger our Landed logic during a replay, so we wait until next frame If we don't, we end up removing root motion from a replay root motion set instead of the real one
- L69 _protected member_ `FRotator Rotation;` — `UPROPERTY(Replicated)`
- L72 _protected member_ `float Distance;` — `UPROPERTY(Replicated)`
- L75 _protected member_ `float Height;` — `UPROPERTY(Replicated)`
- L78 _protected member_ `float Duration;` — `UPROPERTY(Replicated)`
- L81 _protected member_ `float MinimumLandedTriggerTime;` — `UPROPERTY(Replicated)`
- L84 _protected member_ `bool bFinishOnLanded;` — `UPROPERTY(Replicated)`
- L87 _protected member_ `TObjectPtr<UCurveVector> PathOffsetCurve;` — `UPROPERTY(Replicated)`
- L97 _protected member_ `TObjectPtr<UCurveFloat> TimeMappingCurve;` — `UPROPERTY(Replicated)` — Maps real time to movement fraction curve to affect the speed of the movement through the path Curve X is 0 to 1 normalized real time (a fraction of the duration) Curve Y is 0 to 1 is what percent of the move should be at a given X Default if unset is a 1:1 correspondence
- L99 _protected member_ `bool bHasLanded;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionJumpForceDelegate);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionJumpForceDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_ApplyRootMotionMoveToActorForce.h` (Public)


#### enum `ERootMotionMoveToActorTargetOffsetType`  
`enum class ERootMotionMoveToActorTargetOffsetType : uint8`  
_L25-33_
- reflection: `UENUM()`
- L28 _public enumerator_ `AlignFromTargetToSource = 0` — Align target offset vector from target to source, ignoring height difference
- L30 _public enumerator_ `AlignToTargetForward` — Align from target actor location to target actor forward
- L32 _public enumerator_ `AlignToWorldSpace` — Align in world space

#### class `UAbilityTask_ApplyRootMotionMoveToActorForce`  
`class UAbilityTask_ApplyRootMotionMoveToActorForce : public UAbilityTask_ApplyRootMotion_Base`  
_L39-150_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_ApplyRootMotion_Base`
- desc: Applies force to character's movement
- L44 _private member_ `FApplyRootMotionMoveToActorForceDelegate OnFinished;` — `UPROPERTY(BlueprintAssignable)`
- L48 _private prototype_ `static UAbilityTask_ApplyRootMotionMoveToActorForce* ApplyRootMotionMoveToActorForce(UGameplayAbility* OwningAbility, FName TaskInstanceName, AActor* TargetActor, FVector TargetLocationOffset, ERootMotionMoveToActorTargetOffsetType OffsetAlignment, float Duration, UCurveFloat* TargetLerpSpeedHorizontal, UCurveFloat* TargetLerpSpeedVertical, bool bSetNewMovementMode, EMovementMode MovementMode, bool bRestrictSpeedToExpected, UCurveVector* PathOffsetCurve, UCurveFloat* TimeMappingCurve, ERootMotionFinishVelocityMode VelocityOnFinishMode, FVector SetVelocityOnFinish, float ClampVelocityOnFinish, bool bDisableDestinationReachedInterrupt, float ReachedDestinationDistance = 50.0f);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Apply force to character's movement to move to a target actor
- L52 _private prototype_ `static UAbilityTask_ApplyRootMotionMoveToActorForce* ApplyRootMotionMoveToComponentForce(UGameplayAbility* OwningAbility, FName TaskInstanceName, USceneComponent* TargetComponent, FVector TargetComponentRelativeLocation, FVector TargetLocationOffset, ERootMotionMoveToActorTargetOffsetType OffsetAlignment, float Duration, UCurveFloat* TargetLerpSpeedHorizontal, UCurveFloat* TargetLerpSpeedVertical, bool bSetNewMovementMode, EMovementMode MovementMode, bool bRestrictSpeedToExpected, UCurveVector* PathOffsetCurve, UCurveFloat* TimeMappingCurve, ERootMotionFinishVelocityMode VelocityOnFinishMode, FVector SetVelocityOnFinish, float ClampVelocityOnFinish, bool bDisableDestinationReachedInterrupt, float ReachedDestinationDistance = 50.0f);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Apply force to character's movement to move to a target component with relative location
- L56 _private prototype_ `static UAbilityTask_ApplyRootMotionMoveToActorForce* ApplyRootMotionMoveToTargetDataActorForce(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayAbilityTargetDataHandle TargetDataHandle, int32 TargetDataIndex, int32 TargetActorIndex, FVector TargetLocationOffset, ERootMotionMoveToActorTargetOffsetType OffsetAlignment, float Duration, UCurveFloat* TargetLerpSpeedHorizontal, UCurveFloat* TargetLerpSpeedVertical, bool bSetNewMovementMode, EMovementMode MovementMode, bool bRestrictSpeedToExpected, UCurveVector* PathOffsetCurve, UCurveFloat* TimeMappingCurve, ERootMotionFinishVelocityMode VelocityOnFinishMode, FVector SetVelocityOnFinish, float ClampVelocityOnFinish, bool bDisableDestinationReachedInterrupt, float ReachedDestinationDistance = 50.0f);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Apply force to character's movement using an index into targetData instead of using an actor directly.
- L59 _private prototype_ `virtual void TickTask(float DeltaTime) override;` — Tick function for this task, if bTickingTask == true
- L61 _private prototype_ `virtual void PreDestroyFromReplication() override;`
- L62 _private prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L65 _private prototype_ `void OnTargetActorSwapped(class AActor* OriginalTarget, class AActor* NewTarget);` — `UFUNCTION()`
- L69 _protected prototype_ `virtual void SharedInitAndApply() override;`
- L71 _protected prototype_ `bool UpdateTargetLocation(float DeltaTime);`
- L73 _protected prototype_ `void SetRootMotionTargetLocation(FVector NewTargetLocation);`
- L75 _protected prototype_ `FVector CalculateTargetOffset() const;`
- L78 _protected prototype_ `void OnRep_TargetLocation();` — `UFUNCTION()`
- L82 _protected member_ `FDelegateHandle TargetActorSwapHandle;`
- L85 _protected member_ `FVector StartLocation;` — `UPROPERTY(Replicated)`
- L88 _protected member_ `FVector TargetLocation;` — `UPROPERTY(ReplicatedUsing=OnRep_TargetLocation)`
- L91 _protected member_ `TObjectPtr<AActor> TargetActor;` — `UPROPERTY(Replicated)`
- L94 _protected member_ `TObjectPtr<USceneComponent> TargetComponent = nullptr;` — `UPROPERTY(Replicated)`
- L97 _protected member_ `FVector TargetComponentRelativeLocation = FVector::ZeroVector;` — `UPROPERTY(Replicated)`
- L100 _protected member_ `FVector TargetLocationOffset;` — `UPROPERTY(Replicated)`
- L103 _protected member_ `ERootMotionMoveToActorTargetOffsetType OffsetAlignment;` — `UPROPERTY(Replicated)`
- L106 _protected member_ `float Duration;` — `UPROPERTY(Replicated)`
- L111 _protected member_ `bool bDisableDestinationReachedInterrupt;` — `UPROPERTY(Replicated)` — By default, this force ends when the destination is reached. Using this parameter you can disable it so it will not "early out" and get interrupted by reaching the destination and instead go to its full duration.
- L115 _protected member_ `float ReachedDestinationDistance;` — `UPROPERTY(Replicated)` — This is the distance where, at or less that this distance to the destination, the user is considered to be at the destination.
- L118 _protected member_ `bool bSetNewMovementMode;` — `UPROPERTY(Replicated)`
- L121 _protected member_ `TEnumAsByte<EMovementMode> NewMovementMode;` — `UPROPERTY(Replicated)`
- L127 _protected member_ `bool bRestrictSpeedToExpected;` — `UPROPERTY(Replicated)` — If enabled, we limit velocity to the initial expected velocity to go distance to the target over Duration. This prevents cases of getting really high velocity the last few frames of the root motion if you were being blocked by collision. Disabled means we do everything we can to velocity during the move to get to the TargetLocation.
- L130 _protected member_ `TObjectPtr<UCurveVector> PathOffsetCurve;` — `UPROPERTY(Replicated)`
- L140 _protected member_ `TObjectPtr<UCurveFloat> TimeMappingCurve;` — `UPROPERTY(Replicated)` — Maps real time to movement fraction curve to affect the speed of the movement through the path Curve X is 0 to 1 normalized real time (a fraction of the duration) Curve Y is 0 to 1 is what percent of the move should be at a given X Default if unset is a 1:1 correspondence
- L143 _protected member_ `TObjectPtr<UCurveFloat> TargetLerpSpeedHorizontalCurve;` — `UPROPERTY(Replicated)`
- L146 _protected member_ `TObjectPtr<UCurveFloat> TargetLerpSpeedVerticalCurve;` — `UPROPERTY(Replicated)`
- L148 _protected member_ `EMovementMode PreviousMovementMode;`
- L149 _protected member_ `uint8 PreviousCustomMode;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FApplyRootMotionMoveToActorForceDelegate, bool, DestinationReached, bool, TimedOut, FVector, FinalTargetLocation);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FApplyRootMotionMoveToActorForceDelegate, bool, DestinationReached, bool, TimedOut, FVector, FinalTargetLocation);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_ApplyRootMotionMoveToForce.h` (Public)


#### class `UAbilityTask_ApplyRootMotionMoveToForce`  
`class UAbilityTask_ApplyRootMotionMoveToForce : public UAbilityTask_ApplyRootMotion_Base`  
_L25-75_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_ApplyRootMotion_Base`
- desc: Applies force to character's movement
- L31 _public member_ `FApplyRootMotionMoveToForceDelegate OnTimedOut;` — `UPROPERTY(BlueprintAssignable)`
- L34 _public member_ `FApplyRootMotionMoveToForceDelegate OnTimedOutAndDestinationReached;` — `UPROPERTY(BlueprintAssignable)`
- L38 _public prototype_ `static UAbilityTask_ApplyRootMotionMoveToForce* ApplyRootMotionMoveToForce(UGameplayAbility* OwningAbility, FName TaskInstanceName, FVector TargetLocation, float Duration, bool bSetNewMovementMode, EMovementMode MovementMode, bool bRestrictSpeedToExpected, UCurveVector* PathOffsetCurve, ERootMotionFinishVelocityMode VelocityOnFinishMode, FVector SetVelocityOnFinish, float ClampVelocityOnFinish);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Apply force to character's movement
- L41 _public prototype_ `virtual void TickTask(float DeltaTime) override;` — Tick function for this task, if bTickingTask == true
- L43 _public prototype_ `virtual void PreDestroyFromReplication() override;`
- L44 _public prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L47 _protected prototype_ `virtual void SharedInitAndApply() override;`
- L50 _protected member_ `FVector StartLocation;` — `UPROPERTY(Replicated)`
- L53 _protected member_ `FVector TargetLocation;` — `UPROPERTY(Replicated)`
- L56 _protected member_ `float Duration;` — `UPROPERTY(Replicated)`
- L59 _protected member_ `bool bSetNewMovementMode = false;` — `UPROPERTY(Replicated)`
- L62 _protected member_ `TEnumAsByte<EMovementMode> NewMovementMode = EMovementMode::MOVE_Walking;` — `UPROPERTY(Replicated)`
- L68 _protected member_ `bool bRestrictSpeedToExpected = false;` — `UPROPERTY(Replicated)` — If enabled, we limit velocity to the initial expected velocity to go distance to the target over Duration. This prevents cases of getting really high velocity the last few frames of the root motion if you were being blocked by collision. Disabled means we do everything we can to velocity during the move to get to the TargetLocation.
- L71 _protected member_ `TObjectPtr<UCurveVector> PathOffsetCurve = nullptr;` — `UPROPERTY(Replicated)`
- L73 _protected member_ `EMovementMode PreviousMovementMode = EMovementMode::MOVE_None;`
- L74 _protected member_ `uint8 PreviousCustomMovementMode = 0;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionMoveToForceDelegate);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionMoveToForceDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_ApplyRootMotionRadialForce.h` (Public)


#### class `UAbilityTask_ApplyRootMotionRadialForce`  
`class UAbilityTask_ApplyRootMotionRadialForce : public UAbilityTask_ApplyRootMotion_Base`  
_L25-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_ApplyRootMotion_Base`
- desc: Applies force to character's movement
- L30 _private member_ `FApplyRootMotionRadialForceDelegate OnFinish;` — `UPROPERTY(BlueprintAssignable)`
- L34 _private prototype_ `static UAbilityTask_ApplyRootMotionRadialForce* ApplyRootMotionRadialForce(UGameplayAbility* OwningAbility, FName TaskInstanceName, FVector Location, AActor* LocationActor, float Strength, float Duration, float Radius, bool bIsPush, bool bIsAdditive, bool bNoZForce, UCurveFloat* StrengthDistanceFalloff, UCurveFloat* StrengthOverTime, bool bUseFixedWorldDirection, FRotator FixedWorldDirection, ERootMotionFinishVelocityMode VelocityOnFinishMode, FVector SetVelocityOnFinish, float ClampVelocityOnFinish);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Apply force to character's movement
- L37 _private prototype_ `virtual void TickTask(float DeltaTime) override;` — Tick function for this task, if bTickingTask == true
- L39 _private prototype_ `virtual void PreDestroyFromReplication() override;`
- L40 _private prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L44 _protected prototype_ `virtual void SharedInitAndApply() override;`
- L49 _protected member_ `FVector Location;` — `UPROPERTY(Replicated)`
- L52 _protected member_ `TObjectPtr<AActor> LocationActor;` — `UPROPERTY(Replicated)`
- L55 _protected member_ `float Strength;` — `UPROPERTY(Replicated)`
- L58 _protected member_ `float Duration;` — `UPROPERTY(Replicated)`
- L61 _protected member_ `float Radius;` — `UPROPERTY(Replicated)`
- L64 _protected member_ `bool bIsPush;` — `UPROPERTY(Replicated)`
- L67 _protected member_ `bool bIsAdditive;` — `UPROPERTY(Replicated)`
- L70 _protected member_ `bool bNoZForce;` — `UPROPERTY(Replicated)`
- L78 _protected member_ `TObjectPtr<UCurveFloat> StrengthDistanceFalloff;` — `UPROPERTY(Replicated)` — Strength of the force over distance to Location Curve Y is 0 to 1 which is percent of full Strength parameter to apply Curve X is 0 to 1 normalized distance (0 = 0cm, 1 = what Strength % at Radius units out)
- L87 _protected member_ `TObjectPtr<UCurveFloat> StrengthOverTime;` — `UPROPERTY(Replicated)` — Strength of the force over time Curve Y is 0 to 1 which is percent of full Strength parameter to apply Curve X is 0 to 1 normalized time if this force has a limited duration (Duration > 0), or is in units of seconds if this force has unlimited duration (Duration < 0)
- L90 _protected member_ `bool bUseFixedWorldDirection;` — `UPROPERTY(Replicated)`
- L93 _protected member_ `FRotator FixedWorldDirection;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionRadialForceDelegate);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApplyRootMotionRadialForceDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_ApplyRootMotion_Base.h` (Public)


#### class `UAbilityTask_ApplyRootMotion_Base`  
`class UAbilityTask_ApplyRootMotion_Base : public UAbilityTask`  
_L18-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Base class for ability tasks that apply root motion
- L22 _private prototype_ `virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;`
- L25 _private member_ `static FOnTargetActorSwapped OnTargetActorSwapped;` — ..See notes on delegate definition FOnTargetActorSwapped.
- L29 _protected function_ `virtual void SharedInitAndApply()`
- L30 _protected prototype_ `virtual bool HasTimedOut() const;`
- L33 _protected member_ `FName ForceName;` — `UPROPERTY(Replicated)`
- L37 _protected member_ `ERootMotionFinishVelocityMode FinishVelocityMode;` — `UPROPERTY(Replicated)` — What to do with character's Velocity when root motion finishes
- L41 _protected member_ `FVector FinishSetVelocity;` — `UPROPERTY(Replicated)` — If FinishVelocityMode mode is "SetVelocity", character velocity is set to this value when root motion finishes
- L45 _protected member_ `float FinishClampVelocity;` — `UPROPERTY(Replicated)` — If FinishVelocityMode mode is "ClampVelocity", character velocity is clamped to this value when root motion finishes
- L48 _protected member_ `TWeakObjectPtr<UCharacterMovementComponent> MovementComponent;` — `UPROPERTY()`
- L50 _protected member_ `uint16 RootMotionSourceID;`
- L52 _protected member_ `bool bIsFinished;`
- L54 _protected member_ `float StartTime;`
- L55 _protected member_ `float EndTime;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L14 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTargetActorSwapped, AActor*, AActor*);` — This delegate can be used to support target swapping on abilities.  e.g. If a decoy is created and you want root motion to switch the destination to the decoy
- L14 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTargetActorSwapped, AActor*, AActor*);` — This delegate can be used to support target swapping on abilities.  e.g. If a decoy is created and you want root motion to switch the destination to the decoy

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_MoveToLocation.h` (Public)


#### class `UAbilityTask_MoveToLocation`  
`class UAbilityTask_MoveToLocation : public UAbilityTask`  
_L33-80_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Move to a location, ignoring clipping, over a given length of time. Ends when the TargetLocation is reached. This will RESET your character's current movement mode! If you wish to maintain PHYS_Flying or PHYS_Custom, you must reset it on completion.!
- L38 _private member_ `FMoveToLocationDelegate OnTargetLocationReached;` — `UPROPERTY(BlueprintAssignable)`
- L40 _private prototype_ `virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;`
- L44 _private prototype_ `static UAbilityTask_MoveToLocation* MoveToLocation(UGameplayAbility* OwningAbility, FName TaskInstanceName, FVector Location, float Duration, UCurveFloat* OptionalInterpolationCurve, UCurveVector* OptionalVectorInterpolationCurve);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Move to the specified location, using the vector curve (range 0 - 1) if specified, otherwise the float curve (range 0 - 1) or fallback to linear interpolation
- L46 _private prototype_ `virtual void Activate() override;`
- L49 _private prototype_ `virtual void TickTask(float DeltaTime) override;` — Tick function for this task, if bTickingTask == true
- L51 _private prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L55 _protected member_ `bool bIsFinished;`
- L58 _protected member_ `FVector StartLocation;` — `UPROPERTY(Replicated)`
- L63 _protected member_ `FVector TargetLocation;` — `UPROPERTY(Replicated)`
- L66 _protected member_ `float DurationOfMovement;` — `UPROPERTY(Replicated)`
- L69 _protected member_ `float TimeMoveStarted;`
- L71 _protected member_ `float TimeMoveWillEnd;`
- L74 _protected member_ `TObjectPtr<UCurveFloat> LerpCurve;` — `UPROPERTY(Replicated)`
- L77 _protected member_ `TObjectPtr<UCurveVector> LerpCurveVector;` — `UPROPERTY(Replicated)`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveToLocationDelegate);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMoveToLocationDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_NetworkSyncPoint.h` (Public)


#### enum `EAbilityTaskNetSyncType`  
`enum class EAbilityTaskNetSyncType : uint8`  
_L14-24_
- reflection: `UENUM()`
- L17 _public enumerator_ `BothWait` — Both client and server wait until the other signals
- L20 _public enumerator_ `OnlyServerWait` — Only server will wait for the client signal. Client will signal and immediately continue without waiting to hear from Server.
- L23 _public enumerator_ `OnlyClientWait` — Only client will wait for the server signal. Server will signal and immediately continue without waiting to hear from Client.

#### class `UAbilityTask_NetworkSyncPoint`  
`class UAbilityTask_NetworkSyncPoint : public UAbilityTask`  
_L28-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Task for providing a generic sync point for client server (one can wait for a signal from the other)
- L33 _private member_ `FNetworkSyncDelegate OnSync;` — `UPROPERTY(BlueprintAssignable)`
- L36 _private prototype_ `void OnSignalCallback();` — `UFUNCTION()`
- L38 _private prototype_ `virtual void Activate() override;`
- L55 _private prototype_ `static UAbilityTask_NetworkSyncPoint* WaitNetSync(UGameplayAbility* OwningAbility, EAbilityTaskNetSyncType SyncType);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Synchronize execution flow between Client and Server. Depending on SyncType, the Client and Server will wait for the other to reach this node or another WaitNetSync node in the ability before continuing execution. BothWait - Both Client and Server will wait until the other reaches the node. (Whoever gets their first, waits for the other before continueing). OnlyServerWait - Only server will wait for the client signal. Client will signal and immediately continue without waiting to hear from Server. OnlyClientWait - Only client will wait for the server signal. Server will signal and immediately continue without waiting to hear from Client. Note that this is "ability instance wide". These sync points never affect sync points in other abilities. In most cases you will have both client and server execution paths connected to the same WaitNetSync node. However it is possible to use separate nodes for cleanliness of the graph. The "signal" is "ability instance wide".
- L59 _protected prototype_ `void SyncFinished();`
- L62 _protected member_ `EAbilityGenericReplicatedEvent::Type ReplicatedEventToListenFor;` — The event we replicate
- L64 _protected member_ `EAbilityTaskNetSyncType SyncType;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNetworkSyncDelegate);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNetworkSyncDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_PlayAnimAndWait.h` (Public)


#### class `UAbilityTask_PlayAnimAndWait`  
`class UAbilityTask_PlayAnimAndWait : public UAbilityTask`  
_L17-98_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L23 _public member_ `FPlayAnimWaitSimpleDelegate OnCompleted;` — `UPROPERTY(BlueprintAssignable)`
- L26 _public member_ `FPlayAnimWaitSimpleDelegate OnBlendOut;` — `UPROPERTY(BlueprintAssignable)`
- L29 _public member_ `FPlayAnimWaitSimpleDelegate OnBlendIn;` — `UPROPERTY(BlueprintAssignable)`
- L32 _public member_ `FPlayAnimWaitSimpleDelegate OnInterrupted;` — `UPROPERTY(BlueprintAssignable)`
- L35 _public member_ `FPlayAnimWaitSimpleDelegate OnCancelled;` — `UPROPERTY(BlueprintAssignable)`
- L38 _public prototype_ `void OnMontageBlendedIn(UAnimMontage* Montage);` — `UFUNCTION()`
- L41 _public prototype_ `void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);` — `UFUNCTION()`
- L44 _public prototype_ `void OnMontageInterrupted();` — `UFUNCTION()`
- L47 _public prototype_ `void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);` — `UFUNCTION()`
- L65 _public prototype_ `static UAbilityTask_PlayAnimAndWait* CreatePlayAnimAndWaitProxy(UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimSequence* AnimSequence, FName SlotName = NAME_None, float BlendInTime = 0.25f, float BlendOutTime = 0.25f, float InPlayRate = 1.0f, float StartTimeSeconds = 0.0f, bool bStopWhenAbilityEnds = true, float AnimRootMotionTranslationScale = 1.0f, float InPlayCount = 1.0f);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="Play Anim And Wait", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Start playing an animation montage on the avatar actor and wait for it to finish If StopWhenAbilityEnds is true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled. On normal execution, OnBlendOut is called when the montage is blending out, and OnCompleted when it is completely done playing OnInterrupted is called if another montage overwrites this, and OnCancelled is called if the ability or task is cancelled @param TaskInstanceName Set to override the name of this task, for later querying @param MontageToPlay The montage to play on the character @param Rate Change to play the montage faster or slower @param StartSection If not empty, named montage section to start from @param bStopWhenAbilityEnds If true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled @param AnimRootMotionTranslationScale Change to modify size of root motion or set to 0 to block it entirely @param StartTimeSeconds Starting time offset in montage, this will be overridden by StartSection if that is also set
- L68 _public prototype_ `virtual void Activate() override;`
- L71 _public prototype_ `virtual void ExternalCancel() override;` — Called when the ability is asked to cancel from an outside node. What this means depends on the individual task. By default, this does nothing other than ending the task.
- L73 _public prototype_ `virtual FString GetDebugString() const override;`
- L77 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L80 _protected prototype_ `bool StopPlayingMontage();` — Checks if the ability is playing a montage and stops that montage, returns true if a montage was stopped, false if not.
- L82 _protected member_ `FOnMontageBlendingOutStarted BlendingOutDelegate;`
- L83 _protected member_ `FOnMontageBlendedInEnded BlendedInDelegate;`
- L84 _protected member_ `FOnMontageEnded MontageEndedDelegate;`
- L85 _protected member_ `FDelegateHandle InterruptedHandle;`
- L88 _protected member_ `TObjectPtr<UAnimSequence> AnimSequenceToPlay;` — `UPROPERTY()`
- L90 _protected member_ `FName SlotName = NAME_None;`
- L91 _protected member_ `float BlendInTime = 0.25f;`
- L92 _protected member_ `float BlendOutTime = 0.25f;`
- L93 _protected member_ `float PlayRate = 1.0f;`
- L94 _protected member_ `float PlayCount = 1.0f;`
- L95 _protected member_ `float AnimRootMotionTranslationScale = 1.0f;`
- L96 _protected member_ `float StartTimeSeconds = 0.0f;`
- L97 _protected member_ `bool bStopWhenAbilityEnds = true;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayAnimWaitSimpleDelegate);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayAnimWaitSimpleDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_PlayMontageAndWait.h` (Public)


#### class `UAbilityTask_PlayMontageAndWait`  
`class UAbilityTask_PlayMontageAndWait : public UAbilityTask`  
_L16-108_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Ability task to simply play a montage. Many games will want to make a modified version of this task that looks for game-specific events
- L22 _public member_ `FMontageWaitSimpleDelegate OnCompleted;` — `UPROPERTY(BlueprintAssignable)`
- L25 _public member_ `FMontageWaitSimpleDelegate OnBlendedIn;` — `UPROPERTY(BlueprintAssignable)`
- L28 _public member_ `FMontageWaitSimpleDelegate OnBlendOut;` — `UPROPERTY(BlueprintAssignable)`
- L31 _public member_ `FMontageWaitSimpleDelegate OnInterrupted;` — `UPROPERTY(BlueprintAssignable)`
- L34 _public member_ `FMontageWaitSimpleDelegate OnCancelled;` — `UPROPERTY(BlueprintAssignable)`
- L37 _public prototype_ `void OnMontageBlendedIn(UAnimMontage* Montage);` — `UFUNCTION()`
- L40 _public prototype_ `void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);` — `UFUNCTION()`
- L44 _public prototype_ `void OnGameplayAbilityCancelled();` — `UFUNCTION()` — Callback function for when the owning Gameplay Ability is cancelled
- L47 _public prototype_ `void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);` — `UFUNCTION()`
- L66 _public prototype_ `static UAbilityTask_PlayMontageAndWait* CreatePlayMontageAndWaitProxy(UGameplayAbility* OwningAbility, FName TaskInstanceName, UAnimMontage* MontageToPlay, float Rate = 1.f, FName StartSection = NAME_None, bool bStopWhenAbilityEnds = true, float AnimRootMotionTranslationScale = 1.f, float StartTimeSeconds = 0.f, bool bAllowInterruptAfterBlendOut = false);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName="PlayMontageAndWait", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Start playing an animation montage on the avatar actor and wait for it to finish If StopWhenAbilityEnds is true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled. On normal execution, OnBlendOut is called when the montage is blending out, and OnCompleted when it is completely done playing OnInterrupted is called if another montage overwrites this, and OnCancelled is called if the ability or task is cancelled @param TaskInstanceName Set to override the name of this task, for later querying @param MontageToPlay The montage to play on the character @param Rate Change to play the montage faster or slower @param StartSection If not empty, named montage section to start from @param bStopWhenAbilityEnds If true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled @param AnimRootMotionTranslationScale Change to modify size of root motion or set to 0 to block it entirely @param StartTimeSeconds Starting time offset in montage, this will be overridden by StartSection if that is also set @param bAllowInterruptAfterBlendOut If true, you can receive OnInterrupted after an OnBlendOut started (otherwise OnInterrupted will not fire when interrupted, but you will not get OnComplete).
- L69 _public prototype_ `virtual void Activate() override;`
- L72 _public prototype_ `virtual void ExternalCancel() override;` — Called when the ability is asked to cancel from an outside node. What this means depends on the individual task. By default, this does nothing other than ending the task.
- L74 _public prototype_ `virtual FString GetDebugString() const override;`
- L78 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L81 _protected prototype_ `bool StopPlayingMontage();` — Checks if the ability is playing a montage and stops that montage, returns true if a montage was stopped, false if not.
- L83 _protected member_ `FOnMontageBlendedInEnded BlendedInDelegate;`
- L84 _protected member_ `FOnMontageBlendingOutStarted BlendingOutDelegate;`
- L85 _protected member_ `FOnMontageEnded MontageEndedDelegate;`
- L86 _protected member_ `FDelegateHandle InterruptedHandle;`
- L89 _protected member_ `TObjectPtr<UAnimMontage> MontageToPlay;` — `UPROPERTY()`
- L92 _protected member_ `float Rate;` — `UPROPERTY()`
- L95 _protected member_ `FName StartSection;` — `UPROPERTY()`
- L98 _protected member_ `float AnimRootMotionTranslationScale;` — `UPROPERTY()`
- L101 _protected member_ `float StartTimeSeconds;` — `UPROPERTY()`
- L104 _protected member_ `bool bStopWhenAbilityEnds;` — `UPROPERTY()`
- L107 _protected member_ `bool bAllowInterruptAfterBlendOut;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMontageWaitSimpleDelegate);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMontageWaitSimpleDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_Repeat.h` (Public)


#### class `UAbilityTask_Repeat`  
`class UAbilityTask_Repeat : public UAbilityTask`  
_L18-47_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Repeat a task a certain number of times at a given interval.
- L23 _private member_ `FRepeatedActionDelegate OnPerformAction;` — `UPROPERTY(BlueprintAssignable)`
- L26 _private member_ `FRepeatedActionDelegate OnFinished;` — `UPROPERTY(BlueprintAssignable)`
- L28 _private prototype_ `virtual FString GetDebugString() const override;`
- L30 _private prototype_ `void PerformAction();`
- L34 _private prototype_ `static UAbilityTask_Repeat* RepeatAction(UGameplayAbility* OwningAbility, float TimeBetweenActions, int32 TotalActionCount);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Start a task that repeats an action or set of actions.
- L36 _private prototype_ `virtual void Activate() override;`
- L39 _protected member_ `int32 ActionPerformancesDesired;`
- L40 _protected member_ `int32 ActionCounter;`
- L41 _protected member_ `float TimeBetweenActions;`
- L44 _protected member_ `FTimerHandle TimerHandle_PerformAction;` — Handle for efficient management of PerformAction timer
- L46 _protected prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRepeatedActionDelegate, int32, ActionNumber);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRepeatedActionDelegate, int32, ActionNumber);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_SpawnActor.h` (Public)


#### class `UAbilityTask_SpawnActor`  
`class UAbilityTask_SpawnActor: public UAbilityTask`  
_L29-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L34 _private member_ `FSpawnActorDelegate Success;` — `UPROPERTY(BlueprintAssignable)`
- L38 _private member_ `FSpawnActorDelegate DidNotSpawn;` — `UPROPERTY(BlueprintAssignable)` — Called when we can't spawn: on clients or potentially on server if they fail to spawn (rare)
- L42 _private prototype_ `static UAbilityTask_SpawnActor* SpawnActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> Class);` — `UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category="Ability|Tasks")` — Spawn new Actor on the network authority (server)
- L45 _private prototype_ `bool BeginSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, TSubclassOf<AActor> Class, AActor*& SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")`
- L48 _private prototype_ `void FinishSpawningActor(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, AActor* SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")`
- L51 _protected member_ `FGameplayAbilityTargetDataHandle CachedTargetDataHandle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnActorDelegate, AActor*, SpawnedActor);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnActorDelegate, AActor*, SpawnedActor);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_StartAbilityState.h` (Public)


#### class `UAbilityTask_StartAbilityState`  
`class UAbilityTask_StartAbilityState : public UAbilityTask`  
_L29-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: An ability state is simply an ability task that provides a way to handle the ability being interrupted. You can use ability states to do state-specific cleanup if the ability ends or was interrupted at a certain point during it's execution. An ability state will always result in either 'OnStateEnded' or 'OnStateInterrupted' being called. 'OnStateEnded' will be called if: - The ability itself ends via AGameplayAbility::EndAbility - The ability state is manually ended via AGameplayAbility::EndAbilityState - Another ability state is started will 'bEndCurrentState' set to true 'OnStateInterrupted' will be called if: - The ability itself is cancelled via AGameplayAbility::CancelAbility
- L35 _private member_ `FAbilityStateDelegate OnStateEnded;` — `UPROPERTY(BlueprintAssignable)` — Invoked if 'EndAbilityState' is called or if 'EndAbility' is called and this state is active.
- L39 _private member_ `FAbilityStateDelegate OnStateInterrupted;` — `UPROPERTY(BlueprintAssignable)` — Invoked if the ability was interrupted and this state is active.
- L41 _private prototype_ `virtual void Activate() override;`
- L43 _private prototype_ `virtual void ExternalCancel() override;`
- L45 _private prototype_ `virtual FString GetDebugString() const override;`
- L54 _private prototype_ `static UAbilityTask_StartAbilityState* StartAbilityState(UGameplayAbility* OwningAbility, FName StateName, bool bEndCurrentState = true);` — `UFUNCTION(BlueprintCallable, Meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")` — Starts a new ability state. @param StateName The name of the state. @param bEndCurrentState If true, all other active ability states will be ended.
- L58 _private member_ `FDelegateHandle EndStateHandle;`
- L59 _private member_ `FDelegateHandle InterruptStateHandle;`
- L61 _private member_ `bool bWasEnded;`
- L62 _private member_ `bool bWasInterrupted;`
- L64 _private member_ `bool bEndCurrentState;`
- L66 _private prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L68 _private prototype_ `void OnEndState(FName StateNameToEnd);`
- L69 _private prototype_ `void OnInterruptState();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityStateDelegate);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityStateDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_VisualizeTargeting.h` (Public)


#### class `UAbilityTask_VisualizeTargeting`  
`class UAbilityTask_VisualizeTargeting: public UAbilityTask`  
_L17-61_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L22 _private member_ `FVisualizeTargetingDelegate TimeElapsed;` — `UPROPERTY(BlueprintAssignable)`
- L24 _private prototype_ `void OnTimeElapsed();`
- L28 _private prototype_ `static UAbilityTask_VisualizeTargeting* VisualizeTargeting(UGameplayAbility* OwningAbility, TSubclassOf<AGameplayAbilityTargetActor> Class, FName TaskInstanceName, float Duration = -1.0f);` — `UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms="Instigator"), Category="Ability|Tasks")` — Spawns target actor and uses it for visualization.
- L32 _private prototype_ `static UAbilityTask_VisualizeTargeting* VisualizeTargetingUsingActor(UGameplayAbility* OwningAbility, AGameplayAbilityTargetActor* TargetActor, FName TaskInstanceName, float Duration = -1.0f);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Ability|Tasks")` — Visualize target using a specified target actor.
- L34 _private prototype_ `virtual void Activate() override;`
- L37 _private prototype_ `bool BeginSpawningActor(UGameplayAbility* OwningAbility, TSubclassOf<AGameplayAbilityTargetActor> Class, AGameplayAbilityTargetActor*& SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")`
- L40 _private prototype_ `void FinishSpawningActor(UGameplayAbility* OwningAbility, AGameplayAbilityTargetActor* SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")`
- L44 _protected prototype_ `void SetDuration(const float Duration);`
- L46 _protected prototype_ `bool ShouldSpawnTargetActor() const;`
- L47 _protected prototype_ `void InitializeTargetActor(AGameplayAbilityTargetActor* SpawnedActor) const;`
- L48 _protected prototype_ `void FinalizeTargetActor(AGameplayAbilityTargetActor* SpawnedActor) const;`
- L50 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L54 _protected member_ `TSubclassOf<AGameplayAbilityTargetActor> TargetClass;`
- L57 _protected member_ `TWeakObjectPtr<AGameplayAbilityTargetActor> TargetActor;` — The TargetActor that we spawned
- L60 _protected member_ `FTimerHandle TimerHandle_OnTimeElapsed;` — Handle for efficient management of OnTimeElapsed timer

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVisualizeTargetingDelegate);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FVisualizeTargetingDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitAbilityActivate.h` (Public)


#### class `UAbilityTask_WaitAbilityActivate`  
`class UAbilityTask_WaitAbilityActivate : public UAbilityTask`  
_L21-58_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits for the actor to activate another ability
- L26 _private member_ `FWaitAbilityActivateDelegate OnActivate;` — `UPROPERTY(BlueprintAssignable)`
- L28 _private prototype_ `virtual void Activate() override;`
- L31 _private prototype_ `void OnAbilityActivate(UGameplayAbility *ActivatedAbility);` — `UFUNCTION()`
- L35 _private prototype_ `static UAbilityTask_WaitAbilityActivate* WaitForAbilityActivate(UGameplayAbility* OwningAbility, FGameplayTag WithTag, FGameplayTag WithoutTag, bool IncludeTriggeredAbilities=false, bool TriggerOnce=true);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until a new ability (of the same or different type) is activated. Only input based abilities will be counted unless IncludeTriggeredAbilities is true.
- L39 _private prototype_ `static UAbilityTask_WaitAbilityActivate* WaitForAbilityActivateWithTagRequirements(UGameplayAbility* OwningAbility, FGameplayTagRequirements TagRequirements, bool IncludeTriggeredAbilities = false, bool TriggerOnce = true);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until a new ability (of the same or different type) is activated. Only input based abilities will be counted unless IncludeTriggeredAbilities is true. Uses a tag requirements structure to filter abilities.
- L43 _private prototype_ `static UAbilityTask_WaitAbilityActivate* WaitForAbilityActivate_Query(UGameplayAbility* OwningAbility, FGameplayTagQuery Query, bool IncludeTriggeredAbilities=false, bool TriggerOnce=true);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until a new ability (of the same or different type) is activated. Only input based abilities will be counted unless IncludeTriggeredAbilities is true.
- L45 _private member_ `FGameplayTag WithTag;`
- L46 _private member_ `FGameplayTag WithoutTag;`
- L47 _private member_ `bool IncludeTriggeredAbilities;`
- L48 _private member_ `bool TriggerOnce;`
- L49 _private member_ `FGameplayTagRequirements TagRequirements;`
- L51 _private member_ `FGameplayTagQuery Query;`
- L55 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L57 _protected member_ `FDelegateHandle OnAbilityActivateDelegateHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitAbilityActivateDelegate, UGameplayAbility*, ActivatedAbility);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitAbilityActivateDelegate, UGameplayAbility*, ActivatedAbility);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitAbilityCommit.h` (Public)


#### class `UAbilityTask_WaitAbilityCommit`  
`class UAbilityTask_WaitAbilityCommit : public UAbilityTask`  
_L18-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits for the actor to activate another ability
- L23 _private member_ `FWaitAbilityCommitDelegate OnCommit;` — `UPROPERTY(BlueprintAssignable)`
- L25 _private prototype_ `virtual void Activate() override;`
- L28 _private prototype_ `void OnAbilityCommit(UGameplayAbility *ActivatedAbility);` — `UFUNCTION()`
- L32 _private prototype_ `static UAbilityTask_WaitAbilityCommit* WaitForAbilityCommit(UGameplayAbility* OwningAbility, FGameplayTag WithTag, FGameplayTag WithoutTage, bool TriggerOnce=true);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE", DisplayName = "Wait For New Ability Commit"))` — Wait until a new ability (of the same or different type) is commited.
- L35 _private prototype_ `static UAbilityTask_WaitAbilityCommit* WaitForAbilityCommit_Query(UGameplayAbility* OwningAbility, FGameplayTagQuery Query, bool TriggerOnce=true);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE", DisplayName = "Wait For New Ability Commit Query"))`
- L37 _private member_ `FGameplayTag WithTag;`
- L38 _private member_ `FGameplayTag WithoutTag;`
- L39 _private member_ `bool TriggerOnce;`
- L42 _private member_ `FGameplayTagQuery Query;`
- L46 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L48 _protected member_ `FDelegateHandle OnAbilityCommitDelegateHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitAbilityCommitDelegate, UGameplayAbility*, ActivatedAbility);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitAbilityCommitDelegate, UGameplayAbility*, ActivatedAbility);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitAttributeChange.h` (Public)


#### enum `EWaitAttributeChangeComparison::Type`  
`enum Type : int`  
_L18-28_
- L20 _public enumerator_ `None`
- L21 _public enumerator_ `GreaterThan`
- L22 _public enumerator_ `LessThan`
- L23 _public enumerator_ `GreaterThanOrEqualTo`
- L24 _public enumerator_ `LessThanOrEqualTo`
- L25 _public enumerator_ `NotEqualTo`
- L26 _public enumerator_ `ExactlyEqualTo`
- L27 _public enumerator_ `MAX UMETA(Hidden)`

#### class `UAbilityTask_WaitAttributeChange`  
`class UAbilityTask_WaitAttributeChange : public UAbilityTask`  
_L37-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits for the actor to activate another ability
- L42 _private member_ `FWaitAttributeChangeDelegate OnChange;` — `UPROPERTY(BlueprintAssignable)`
- L44 _private prototype_ `virtual void Activate() override;`
- L46 _private prototype_ `void OnAttributeChange(const FOnAttributeChangeData& CallbackData);`
- L50 _private prototype_ `static UAbilityTask_WaitAttributeChange* WaitForAttributeChange(UGameplayAbility* OwningAbility, FGameplayAttribute Attribute, FGameplayTag WithSrcTag, FGameplayTag WithoutSrcTag, bool TriggerOnce=true, AActor* OptionalExternalOwner = nullptr);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until an attribute changes.
- L54 _private prototype_ `static UAbilityTask_WaitAttributeChange* WaitForAttributeChangeWithComparison(UGameplayAbility* OwningAbility, FGameplayAttribute InAttribute, FGameplayTag InWithTag, FGameplayTag InWithoutTag, TEnumAsByte<EWaitAttributeChangeComparison::Type> InComparisonType, float InComparisonValue, bool TriggerOnce=true, AActor* OptionalExternalOwner = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until an attribute changes to pass a given test.
- L56 _private member_ `FGameplayTag WithTag;`
- L57 _private member_ `FGameplayTag WithoutTag;`
- L58 _private member_ `FGameplayAttribute Attribute;`
- L59 _private member_ `TEnumAsByte<EWaitAttributeChangeComparison::Type> ComparisonType;`
- L60 _private member_ `float ComparisonValue;`
- L61 _private member_ `bool bTriggerOnce;`
- L62 _private member_ `FDelegateHandle OnAttributeChangeDelegateHandle;`
- L67 _protected member_ `TObjectPtr<UAbilitySystemComponent> ExternalOwner;` — `UPROPERTY()`
- L69 _protected prototype_ `UAbilitySystemComponent* GetFocusedASC();`
- L71 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L16 _namespace_ `namespace EWaitAttributeChangeComparison`
- L31 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitAttributeChangeDelegate);`
- L31 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitAttributeChangeDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitAttributeChangeRatioThreshold.h` (Public)


#### class `UAbilityTask_WaitAttributeChangeRatioThreshold`  
`class UAbilityTask_WaitAttributeChangeRatioThreshold : public UAbilityTask`  
_L22-66_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits for the ratio between two attributes to match a threshold
- L27 _private member_ `FWaitAttributeChangeRatioThresholdDelegate OnChange;` — `UPROPERTY(BlueprintAssignable)`
- L29 _private prototype_ `virtual void Activate() override;`
- L31 _private prototype_ `void OnNumeratorAttributeChange(const FOnAttributeChangeData& CallbackData);`
- L32 _private prototype_ `void OnDenominatorAttributeChange(const FOnAttributeChangeData& CallbackData);`
- L36 _private prototype_ `static UAbilityTask_WaitAttributeChangeRatioThreshold* WaitForAttributeChangeRatioThreshold(UGameplayAbility* OwningAbility, FGameplayAttribute AttributeNumerator, FGameplayAttribute AttributeDenominator, TEnumAsByte<EWaitAttributeChangeComparison::Type> ComparisonType, float ComparisonValue, bool bTriggerOnce, AActor* OptionalExternalOwner = nullptr);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait on attribute ratio change meeting a comparison threshold.
- L38 _private member_ `FGameplayAttribute AttributeNumerator;`
- L39 _private member_ `FGameplayAttribute AttributeDenominator;`
- L40 _private member_ `TEnumAsByte<EWaitAttributeChangeComparison::Type> ComparisonType;`
- L41 _private member_ `float ComparisonValue;`
- L42 _private member_ `bool bTriggerOnce;`
- L43 _private member_ `FDelegateHandle OnNumeratorAttributeChangeDelegateHandle;`
- L44 _private member_ `FDelegateHandle OnDenominatorAttributeChangeDelegateHandle;`
- L48 _protected member_ `float LastAttributeNumeratorValue;`
- L49 _protected member_ `float LastAttributeDenominatorValue;`
- L50 _protected member_ `bool bMatchedComparisonLastAttributeChange;`
- L53 _protected member_ `FTimerHandle CheckAttributeTimer;` — Timer used when either numerator or denominator attribute is changed to delay checking of ratio to avoid false positives (MaxHealth changed before Health updates accordingly)
- L56 _protected member_ `TObjectPtr<UAbilitySystemComponent> ExternalOwner;` — `UPROPERTY()`
- L58 _protected prototype_ `UAbilitySystemComponent* GetFocusedASC();`
- L60 _protected prototype_ `void OnAttributeChange();`
- L61 _protected prototype_ `void OnRatioChange();`
- L63 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L65 _protected prototype_ `bool DoesValuePassComparison(float ValueNumerator, float ValueDenominator) const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaitAttributeChangeRatioThresholdDelegate, bool, bMatchesComparison, float, CurrentRatio);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaitAttributeChangeRatioThresholdDelegate, bool, bMatchesComparison, float, CurrentRatio);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitAttributeChangeThreshold.h` (Public)


#### class `UAbilityTask_WaitAttributeChangeThreshold`  
`class UAbilityTask_WaitAttributeChangeThreshold : public UAbilityTask`  
_L21-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits for an attribute to match a threshold
- L26 _private member_ `FWaitAttributeChangeThresholdDelegate OnChange;` — `UPROPERTY(BlueprintAssignable)`
- L28 _private prototype_ `virtual void Activate() override;`
- L30 _private prototype_ `void OnAttributeChange(const FOnAttributeChangeData& CallbackData);`
- L34 _private prototype_ `static UAbilityTask_WaitAttributeChangeThreshold* WaitForAttributeChangeThreshold(UGameplayAbility* OwningAbility, FGameplayAttribute Attribute, TEnumAsByte<EWaitAttributeChangeComparison::Type> ComparisonType, float ComparisonValue, bool bTriggerOnce, AActor* OptionalExternalOwner = nullptr);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait on attribute change meeting a comparison threshold.
- L36 _private member_ `FGameplayAttribute Attribute;`
- L37 _private member_ `TEnumAsByte<EWaitAttributeChangeComparison::Type> ComparisonType;`
- L38 _private member_ `float ComparisonValue;`
- L39 _private member_ `bool bTriggerOnce;`
- L40 _private member_ `FDelegateHandle OnAttributeChangeDelegateHandle;`
- L44 _protected member_ `bool bMatchedComparisonLastAttributeChange;`
- L47 _protected member_ `TObjectPtr<UAbilitySystemComponent> ExternalOwner;` — `UPROPERTY()`
- L49 _protected prototype_ `UAbilitySystemComponent* GetFocusedASC();`
- L51 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L53 _protected prototype_ `bool DoesValuePassComparison(float Value) const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaitAttributeChangeThresholdDelegate, bool, bMatchesComparison, float, CurrentValue);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaitAttributeChangeThresholdDelegate, bool, bMatchesComparison, float, CurrentValue);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitCancel.h` (Public)


#### class `UAbilityTask_WaitCancel`  
`class UAbilityTask_WaitCancel : public UAbilityTask`  
_L14-38_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L19 _private member_ `FWaitCancelDelegate OnCancel;` — `UPROPERTY(BlueprintAssignable)`
- L22 _private prototype_ `void OnCancelCallback();` — `UFUNCTION()`
- L25 _private prototype_ `void OnLocalCancelCallback();` — `UFUNCTION()`
- L28 _private prototype_ `static UAbilityTask_WaitCancel* WaitCancel(UGameplayAbility* OwningAbility);` — `UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", DisplayName="Wait for Cancel Input"), Category="Ability|Tasks")`
- L30 _private prototype_ `virtual void Activate() override;`
- L34 _protected prototype_ `virtual void OnDestroy(bool AbilityEnding) override;`
- L36 _protected member_ `bool RegisteredCallbacks;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitCancelDelegate);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitCancelDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitConfirm.h` (Public)


#### class `UAbilityTask_WaitConfirm`  
`class UAbilityTask_WaitConfirm : public UAbilityTask`  
_L12-35_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L17 _private member_ `FGenericGameplayTaskDelegate OnConfirm;` — `UPROPERTY(BlueprintAssignable)`
- L20 _private prototype_ `void OnConfirmCallback(UGameplayAbility* InAbility);` — `UFUNCTION()`
- L22 _private prototype_ `virtual void Activate() override;`
- L26 _private prototype_ `static UAbilityTask_WaitConfirm* WaitConfirm(UGameplayAbility* OwningAbility);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the server confirms the use of this ability. This is used to gate predictive portions of the ability
- L30 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L32 _protected member_ `bool RegisteredCallback;`
- L34 _protected member_ `FDelegateHandle OnConfirmCallbackDelegateHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitConfirmCancel.h` (Public)


#### class `UAbilityTask_WaitConfirmCancel`  
`class UAbilityTask_WaitConfirmCancel : public UAbilityTask`  
_L18-51_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L23 _private member_ `FWaitConfirmCancelDelegate OnConfirm;` — `UPROPERTY(BlueprintAssignable)`
- L26 _private member_ `FWaitConfirmCancelDelegate OnCancel;` — `UPROPERTY(BlueprintAssignable)`
- L29 _private prototype_ `void OnConfirmCallback();` — `UFUNCTION()`
- L32 _private prototype_ `void OnCancelCallback();` — `UFUNCTION()`
- L35 _private prototype_ `void OnLocalConfirmCallback();` — `UFUNCTION()`
- L38 _private prototype_ `void OnLocalCancelCallback();` — `UFUNCTION()`
- L41 _private prototype_ `static UAbilityTask_WaitConfirmCancel* WaitConfirmCancel(UGameplayAbility* OwningAbility);` — `UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", DisplayName="Wait for Confirm Input"), Category="Ability|Tasks")`
- L43 _private prototype_ `virtual void Activate() override;`
- L47 _protected prototype_ `virtual void OnDestroy(bool AbilityEnding) override;`
- L49 _protected member_ `bool RegisteredCallbacks;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitConfirmCancelDelegate);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitConfirmCancelDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitDelay.h` (Public)


#### class `UAbilityTask_WaitDelay`  
`class UAbilityTask_WaitDelay : public UAbilityTask`  
_L14-36_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L19 _private member_ `FWaitDelayDelegate OnFinish;` — `UPROPERTY(BlueprintAssignable)`
- L21 _private prototype_ `virtual void Activate() override;`
- L24 _private prototype_ `virtual FString GetDebugString() const override;` — Return debug string describing task
- L28 _private prototype_ `static UAbilityTask_WaitDelay* WaitDelay(UGameplayAbility* OwningAbility, float Time);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait specified time. This is functionally the same as a standard Delay node.
- L32 _private prototype_ `void OnTimeFinish();`
- L34 _private member_ `float Time;`
- L35 _private member_ `float TimeStarted;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitDelayDelegate);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitDelayDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayEffectApplied.h` (Public)


#### class `UAbilityTask_WaitGameplayEffectApplied`  
`class UAbilityTask_WaitGameplayEffectApplied : public UAbilityTask`  
_L16-70_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L21 _private prototype_ `void OnApplyGameplayEffectCallback(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION()`
- L23 _private prototype_ `virtual void Activate() override;`
- L26 _private member_ `FGameplayTargetDataFilterHandle Filter;` — Actor filter for the source actor applying this effect that must be passed to trigger this task
- L28 _private member_ `FGameplayTagRequirements SourceTagRequirements;` — Tag requirements for source actor that applies the GameplayEffect
- L30 _private member_ `FGameplayTagRequirements TargetTagRequirements;` — Tag requirements for target actor to which the GameplayEffect is applied
- L32 _private member_ `FGameplayTagRequirements AssetTagRequirements;` — Tag requirements for asset tags ('Tags this Effect Has') on the GameplayEffect being applied
- L34 _private member_ `FGameplayTagRequirements GrantedTagRequirements;` — Tag requirements for granted tags ('Grant Tags to Target Actor') that the GameplayEffect applies to the target actor
- L37 _private member_ `FGameplayTagQuery SourceTagQuery;` — Tag query that must be passed for source actor that applies the GameplayEffect
- L39 _private member_ `FGameplayTagQuery TargetTagQuery;` — Tag query that must be passed for target actor to which the GameplayEffect is applied
- L41 _private member_ `FGameplayTagQuery AssetTagQuery;` — Tag query that must be passed for asset tags ('Tags this Effect Has') on the GameplayEffect being applied
- L43 _private member_ `FGameplayTagQuery GrantedTagQuery;` — Tag query that must be passed for granted tags ('Grant Tags to Target Actor') that the GameplayEffect applies to the target actor
- L45 _private member_ `bool TriggerOnce;`
- L46 _private member_ `bool ListenForPeriodicEffects;`
- L48 _private prototype_ `void SetExternalActor(AActor* InActor);`
- L52 _protected prototype_ `UAbilitySystemComponent* GetASC();`
- L54 _protected function_ `virtual void BroadcastDelegate(AActor* Avatar, FGameplayEffectSpecHandle SpecHandle, FActiveGameplayEffectHandle ActiveHandle)`
- L55 _protected function_ `virtual void RegisterDelegate()`
- L56 _protected function_ `virtual void RemoveDelegate()`
- L58 _protected prototype_ `FString GetBroadcastingEffectStackString() const;`
- L60 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L62 _protected member_ `bool RegisteredCallback;`
- L63 _protected member_ `bool UseExternalOwner;`
- L66 _protected member_ `TObjectPtr<UAbilitySystemComponent> ExternalOwner;` — `UPROPERTY()`
- L69 _protected member_ `TArray<TSubclassOf<class UGameplayEffect>> BroadcastingEffectStack;` — If we are in the process of broadcasting, we do not allow a GameplayEffect class to trigger application of another instance of the same class.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayEffectApplied_Self.h` (Public)


#### class `UAbilityTask_WaitGameplayEffectApplied_Self`  
`class UAbilityTask_WaitGameplayEffectApplied_Self : public UAbilityTask_WaitGameplayEffectApplied`  
_L16-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_WaitGameplayEffectApplied`
- L21 _private member_ `FGameplayEffectAppliedSelfDelegate OnApplied;` — `UPROPERTY(BlueprintAssignable)`
- L37 _private prototype_ `static UAbilityTask_WaitGameplayEffectApplied_Self* WaitGameplayEffectAppliedToSelf(UGameplayAbility* OwningAbility, const FGameplayTargetDataFilterHandle SourceFilter, FGameplayTagRequirements SourceTagRequirements, FGameplayTagRequirements TargetTagRequirements, FGameplayTagRequirements AssetTagRequirements, FGameplayTagRequirements GrantedTagRequirements, bool TriggerOnce=false, AActor* OptionalExternalOwner=nullptr, bool ListenForPeriodicEffect=false );` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the owner *receives* a GameplayEffect from a given source (the source may be the owner too!). @param OwningAbility The ability that executes this task @param SourceFilter Actor filter for the source actor applying this effect that must be passed to trigger this task @param SourceTagRequirements Gameplay tag requirements for the source actor applying this effect @param TargetTagRequirements Gameplay tag requirements for the target actor receiving this effect (self in this case) @param AssetTagRequirements Requirements for the asset tags of the applied effect: 'Tags this Effect Has' on the GameplayEffect class @param GrantedTagRequirements Requirements for the tags granted by the applied effect: 'Grant Tags to Target Actor' on the GameplayEffect class @param TriggerOnce If TriggerOnce is true, this task will only return one time. Otherwise it will return everytime a GE is applied that meets the requirements over the life of the ability. @param OptionalExternalOwner Can be used to run this task on someone else (not the owner of the ability). By default you can leave this empty. @param ListenForPeriodicEffects Whether to also fire on periodic ticks of the applied effect
- L54 _private prototype_ `static UAbilityTask_WaitGameplayEffectApplied_Self* WaitGameplayEffectAppliedToSelf_Query(UGameplayAbility* OwningAbility, const FGameplayTargetDataFilterHandle SourceFilter, FGameplayTagQuery SourceTagQuery, FGameplayTagQuery TargetTagQuery, FGameplayTagQuery AssetTagQuery, FGameplayTagQuery GrantedTagQuery, bool TriggerOnce=false, AActor* OptionalExternalOwner=nullptr, bool ListenForPeriodicEffect=false );` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the owner *receives* a GameplayEffect from a given source (the source may be the owner too!). This version uses FGameplayTagQuery (more power) instead of FGameplayTagRequirements (faster). @param OwningAbility The ability that executes this task @param SourceFilter Actor filter for the source actor applying this effect that must be passed to trigger this task @param SourceTagQuery Gameplay tag requirements for the source actor applying this effect @param TargetTagQuery Gameplay tag requirements for the target actor receiving this effect (self in this case) @param AssetTagQuery Requirements for the asset tags of the applied effect: 'Tags this Effect Has' on the GameplayEffect class @param GrantedTagQuery Requirements for the tags granted by the applied effect: 'Grant Tags to Target Actor' on the GameplayEffect class @param TriggerOnce If TriggerOnce is true, this task will only return one time. Otherwise it will return everytime a GE is applied that meets the requirements over the life of the ability. @param OptionalExternalOwner Can be used to run this task on someone else (not the owner of the ability). By default you can leave this empty. @param ListenForPeriodicEffects Whether to also fire on periodic ticks of the applied effect
- L58 _protected prototype_ `virtual void BroadcastDelegate(AActor* Avatar, FGameplayEffectSpecHandle SpecHandle, FActiveGameplayEffectHandle ActiveHandle) override;`
- L59 _protected prototype_ `virtual void RegisterDelegate() override;`
- L60 _protected prototype_ `virtual void RemoveDelegate() override;`
- L63 _private member_ `FDelegateHandle OnApplyGameplayEffectCallbackDelegateHandle;`
- L64 _private member_ `FDelegateHandle OnPeriodicGameplayEffectExecuteCallbackDelegateHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameplayEffectAppliedSelfDelegate, AActor*, Source, FGameplayEffectSpecHandle, SpecHandle, FActiveGameplayEffectHandle, ActiveHandle );`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameplayEffectAppliedSelfDelegate, AActor*, Source, FGameplayEffectSpecHandle, SpecHandle, FActiveGameplayEffectHandle, ActiveHandle );`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayEffectApplied_Target.h` (Public)


#### class `UAbilityTask_WaitGameplayEffectApplied_Target`  
`class UAbilityTask_WaitGameplayEffectApplied_Target : public UAbilityTask_WaitGameplayEffectApplied`  
_L16-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_WaitGameplayEffectApplied`
- L21 _private member_ `FGameplayEffectAppliedTargetDelegate OnApplied;` — `UPROPERTY(BlueprintAssignable)`
- L37 _private prototype_ `static UAbilityTask_WaitGameplayEffectApplied_Target* WaitGameplayEffectAppliedToTarget(UGameplayAbility* OwningAbility, const FGameplayTargetDataFilterHandle TargetFilter, FGameplayTagRequirements SourceTagRequirements, FGameplayTagRequirements TargetTagRequirements, FGameplayTagRequirements AssetTagRequirements, FGameplayTagRequirements GrantedTagRequirements, bool TriggerOnce=false, AActor* OptionalExternalOwner=nullptr, bool ListenForPeriodicEffects=false);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the owner (or External Owner) applies a GameplayEffect to a Target (the target may be the owner too!). @param OwningAbility The ability that executes this task @param SourceFilter Actor filter for the source actor applying this effect that must be passed to trigger this task @param SourceTagRequirements Gameplay tag requirements for the source actor applying this effect @param TargetTagRequirements Gameplay tag requirements for the target actor receiving this effect @param AssetTagRequirements Requirements for the asset tags of the applied effect: 'Tags this Effect Has' on the GameplayEffect class. @param GrantedTagRequirements Requirements for the tags granted by the applied effect: 'Grant Tags to Target Actor' on the GameplayEffect class. @param TriggerOnce If TriggerOnce is true, this task will only return one time. Otherwise it will return everytime a GE is applied that meets the requirements over the life of the ability. @param OptionalExternalOwner Can be used to run this task on someone else (not the owner of the ability). By default you can leave this empty. @param ListenForPeriodicEffects Whether to also fire on periodic ticks of the applied effect
- L54 _private prototype_ `static UAbilityTask_WaitGameplayEffectApplied_Target* WaitGameplayEffectAppliedToTarget_Query(UGameplayAbility* OwningAbility, const FGameplayTargetDataFilterHandle SourceFilter, FGameplayTagQuery SourceTagQuery, FGameplayTagQuery TargetTagQuery, FGameplayTagQuery AssetTagQuery, FGameplayTagQuery GrantedTagQuery, bool TriggerOnce=false, AActor* OptionalExternalOwner=nullptr, bool ListenForPeriodicEffect=false );` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the owner (or External Owner) applies a GameplayEffect to a Target (the target may be the owner too!). This version uses FGameplayTagQuery (more power) instead of FGameplayTagRequirements (faster). @param OwningAbility The ability that executes this task @param SourceFilter Actor filter for the source actor applying this effect that must be passed to trigger this task @param SourceTagQuery Gameplay tag requirements for the source actor applying this effect @param TargetTagQuery Gameplay tag requirements for the target actor receiving this effect @param AssetTagQuery Requirements for the asset tags of the applied effect: 'Tags this Effect Has' on the GameplayEffect class @param GrantedTagQuery Requirements for the tags granted by the applied effect: 'Grant Tags to Target Actor' on the GameplayEffect class @param TriggerOnce If TriggerOnce is true, this task will only return one time. Otherwise it will return everytime a GE is applied that meets the requirements over the life of the ability. @param OptionalExternalOwner Can be used to run this task on someone else (not the owner of the ability). By default you can leave this empty. @param ListenForPeriodicEffects Whether to also fire on periodic ticks of the applied effect
- L58 _protected prototype_ `virtual void BroadcastDelegate(AActor* Avatar, FGameplayEffectSpecHandle SpecHandle, FActiveGameplayEffectHandle ActiveHandle) override;`
- L59 _protected prototype_ `virtual void RegisterDelegate() override;`
- L60 _protected prototype_ `virtual void RemoveDelegate() override;`
- L63 _private member_ `FDelegateHandle OnApplyGameplayEffectCallbackDelegateHandle;`
- L64 _private member_ `FDelegateHandle OnPeriodicGameplayEffectExecuteCallbackDelegateHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameplayEffectAppliedTargetDelegate, AActor*, Target, FGameplayEffectSpecHandle, SpecHandle, FActiveGameplayEffectHandle, ActiveHandle );`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGameplayEffectAppliedTargetDelegate, AActor*, Target, FGameplayEffectSpecHandle, SpecHandle, FActiveGameplayEffectHandle, ActiveHandle );`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayEffectBlockedImmunity.h` (Public)


#### class `UAbilityTask_WaitGameplayEffectBlockedImmunity`  
`class UAbilityTask_WaitGameplayEffectBlockedImmunity : public UAbilityTask`  
_L17-56_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L22 _private member_ `FGameplayEffectBlockedDelegate Blocked;` — `UPROPERTY(BlueprintAssignable)`
- L26 _private prototype_ `static UAbilityTask_WaitGameplayEffectBlockedImmunity* WaitGameplayEffectBlockedByImmunity(UGameplayAbility* OwningAbility, FGameplayTagRequirements SourceTagRequirements, FGameplayTagRequirements TargetTagRequirements, AActor* OptionalExternalTarget=nullptr, bool OnlyTriggerOnce=false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Listens for GE immunity. By default this means "this hero blocked a GE due to immunity". Setting OptionalExternalTarget will listen for a GE being blocked on an external target. Note this only works on the server.
- L28 _private prototype_ `virtual void Activate() override;`
- L30 _private prototype_ `virtual void ImmunityCallback(const FGameplayEffectSpec& BlockedSpec, const FActiveGameplayEffect* ImmunityGE);`
- L32 _private member_ `FGameplayTagRequirements SourceTagRequirements;`
- L33 _private member_ `FGameplayTagRequirements TargetTagRequirements;`
- L35 _private member_ `bool TriggerOnce;`
- L36 _private member_ `bool ListenForPeriodicEffects;`
- L38 _private prototype_ `void SetExternalActor(AActor* InActor);`
- L42 _protected prototype_ `UAbilitySystemComponent* GetASC();`
- L44 _protected prototype_ `void RegisterDelegate();`
- L45 _protected prototype_ `void RemoveDelegate();`
- L47 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L49 _protected member_ `bool RegisteredCallback;`
- L50 _protected member_ `bool UseExternalOwner;`
- L53 _protected member_ `TObjectPtr<UAbilitySystemComponent> ExternalOwner;` — `UPROPERTY()`
- L55 _protected member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayEffectBlockedDelegate, FGameplayEffectSpecHandle, BlockedSpec, FActiveGameplayEffectHandle, ImmunityGameplayEffectHandle);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameplayEffectBlockedDelegate, FGameplayEffectSpecHandle, BlockedSpec, FActiveGameplayEffectHandle, ImmunityGameplayEffectHandle);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayEffectRemoved.h` (Public)


#### class `UAbilityTask_WaitGameplayEffectRemoved`  
`class UAbilityTask_WaitGameplayEffectRemoved : public UAbilityTask`  
_L21-49_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits for the actor to activate another ability
- L26 _private member_ `FWaitGameplayEffectRemovedDelegate OnRemoved;` — `UPROPERTY(BlueprintAssignable)`
- L29 _private member_ `FWaitGameplayEffectRemovedDelegate InvalidHandle;` — `UPROPERTY(BlueprintAssignable)`
- L31 _private prototype_ `virtual void Activate() override;`
- L34 _private prototype_ `void OnGameplayEffectRemoved(const FGameplayEffectRemovalInfo& InGameplayEffectRemovalInfo);` — `UFUNCTION()`
- L38 _private prototype_ `static UAbilityTask_WaitGameplayEffectRemoved* WaitForGameplayEffectRemoved(UGameplayAbility* OwningAbility, FActiveGameplayEffectHandle Handle);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay effect is removed.
- L40 _private member_ `FActiveGameplayEffectHandle Handle;`
- L44 _protected prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L45 _protected member_ `bool Registered;`
- L47 _protected member_ `FDelegateHandle OnGameplayEffectRemovedDelegateHandle;`
- L48 _protected member_ `FDelegateHandle OnGameplayEffectRemovedDelegateHandle_Deprecated;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitGameplayEffectRemovedDelegate, const FGameplayEffectRemovalInfo &, GameplayEffectRemovalInfo);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitGameplayEffectRemovedDelegate, const FGameplayEffectRemovalInfo &, GameplayEffectRemovalInfo);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayEffectStackChange.h` (Public)


#### class `UAbilityTask_WaitGameplayEffectStackChange`  
`class UAbilityTask_WaitGameplayEffectStackChange : public UAbilityTask`  
_L21-48_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits for the actor to activate another ability
- L26 _private member_ `FWaitGameplayEffectStackChangeDelegate OnChange;` — `UPROPERTY(BlueprintAssignable)`
- L29 _private member_ `FWaitGameplayEffectStackChangeDelegate InvalidHandle;` — `UPROPERTY(BlueprintAssignable)`
- L31 _private prototype_ `virtual void Activate() override;`
- L34 _private prototype_ `void OnGameplayEffectStackChange(FActiveGameplayEffectHandle Handle, int32 NewCount, int32 OldCount);` — `UFUNCTION()`
- L38 _private prototype_ `static UAbilityTask_WaitGameplayEffectStackChange* WaitForGameplayEffectStackChange(UGameplayAbility* OwningAbility, FActiveGameplayEffectHandle Handle);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay effect is removed.
- L40 _private member_ `FActiveGameplayEffectHandle Handle;`
- L44 _protected prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L45 _protected member_ `bool Registered;`
- L47 _protected member_ `FDelegateHandle OnGameplayEffectStackChangeDelegateHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWaitGameplayEffectStackChangeDelegate, FActiveGameplayEffectHandle, Handle, int32, NewCount, int32, OldCount);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWaitGameplayEffectStackChangeDelegate, FActiveGameplayEffectHandle, Handle, int32, NewCount, int32, OldCount);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayEvent.h` (Public)


#### class `UAbilityTask_WaitGameplayEvent`  
`class UAbilityTask_WaitGameplayEvent : public UAbilityTask`  
_L18-54_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L23 _private member_ `FWaitGameplayEventDelegate EventReceived;` — `UPROPERTY(BlueprintAssignable)`
- L31 _private prototype_ `static UAbilityTask_WaitGameplayEvent* WaitGameplayEvent(UGameplayAbility* OwningAbility, UPARAM(meta=(GameplayTagFilter="GameplayEventTagsCategory"))FGameplayTag EventTag, AActor* OptionalExternalTarget=nullptr, bool OnlyTriggerOnce=false, boo` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag event is triggered. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes It will keep listening as long as OnlyTriggerOnce = false If OnlyMatchExact = false it will trigger for nested tags
- L33 _private prototype_ `void SetExternalTarget(AActor* Actor);`
- L35 _private prototype_ `UAbilitySystemComponent* GetTargetASC();`
- L37 _private prototype_ `virtual void Activate() override;`
- L39 _private prototype_ `virtual void GameplayEventCallback(const FGameplayEventData* Payload);`
- L40 _private prototype_ `virtual void GameplayEventContainerCallback(FGameplayTag MatchingTag, const FGameplayEventData* Payload);`
- L42 _private prototype_ `void OnDestroy(bool AbilityEnding) override;`
- L44 _private member_ `FGameplayTag Tag;`
- L47 _private member_ `TObjectPtr<UAbilitySystemComponent> OptionalExternalTarget;` — `UPROPERTY()`
- L49 _private member_ `bool UseExternalTarget;`
- L50 _private member_ `bool OnlyTriggerOnce;`
- L51 _private member_ `bool OnlyMatchExact;`
- L53 _private member_ `FDelegateHandle MyHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitGameplayEventDelegate, FGameplayEventData, Payload);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitGameplayEventDelegate, FGameplayEventData, Payload);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayTag.h` (Public)


#### class `UAbilityTask_WaitGameplayTagAdded`  
`class UAbilityTask_WaitGameplayTagAdded : public UAbilityTask_WaitGameplayTag`  
_L15-32_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_WaitGameplayTag`
- L20 _private member_ `FWaitGameplayTagDelegate Added;` — `UPROPERTY(BlueprintAssignable)`
- L27 _private prototype_ `static UAbilityTask_WaitGameplayTagAdded* WaitGameplayTagAdd(UGameplayAbility* OwningAbility, FGameplayTag Tag, AActor* InOptionalExternalTarget=nullptr, bool OnlyTriggerOnce=false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag is Added. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes. If the tag is already present when this task is started, it will immediately broadcast the Added event. It will keep listening as long as OnlyTriggerOnce = false.
- L29 _private prototype_ `virtual void Activate() override;`
- L31 _private prototype_ `virtual void GameplayTagCallback(const FGameplayTag Tag, int32 NewCount) override;`

#### class `UAbilityTask_WaitGameplayTagRemoved`  
`class UAbilityTask_WaitGameplayTagRemoved : public UAbilityTask_WaitGameplayTag`  
_L35-52_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask_WaitGameplayTag`
- L40 _private member_ `FWaitGameplayTagDelegate Removed;` — `UPROPERTY(BlueprintAssignable)`
- L47 _private prototype_ `static UAbilityTask_WaitGameplayTagRemoved* WaitGameplayTagRemove(UGameplayAbility* OwningAbility, FGameplayTag Tag, AActor* InOptionalExternalTarget=nullptr, bool OnlyTriggerOnce=false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag is Removed. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes. If the tag is not present when this task is started, it will immediately broadcast the Removed event. It will keep listening as long as OnlyTriggerOnce = false.
- L49 _private prototype_ `virtual void Activate() override;`
- L51 _private prototype_ `virtual void GameplayTagCallback(const FGameplayTag Tag, int32 NewCount) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitGameplayTagDelegate);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitGameplayTagDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayTagBase.h` (Public)


#### class `UAbilityTask_WaitGameplayTag`  
`class UAbilityTask_WaitGameplayTag : public UAbilityTask`  
_L15-43_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L19 _private prototype_ `virtual void Activate() override;`
- L22 _private prototype_ `virtual void GameplayTagCallback(const FGameplayTag Tag, int32 NewCount);` — `UFUNCTION()`
- L24 _private prototype_ `void SetExternalTarget(AActor* Actor);`
- L26 _private member_ `FGameplayTag Tag;`
- L30 _protected prototype_ `UAbilitySystemComponent* GetTargetASC();`
- L32 _protected prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;`
- L34 _protected member_ `bool RegisteredCallback;`
- L37 _protected member_ `TObjectPtr<UAbilitySystemComponent> OptionalExternalTarget;` — `UPROPERTY()`
- L39 _protected member_ `bool UseExternalTarget;`
- L40 _protected member_ `bool OnlyTriggerOnce;`
- L42 _protected member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayTagCountChanged.h` (Public)


#### class `UAbilityTask_WaitGameplayTagCountChanged`  
`class UAbilityTask_WaitGameplayTagCountChanged : public UAbilityTask`  
_L13-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L19 _protected member_ `FWaitGameplayTagCountDelegate TagCountChanged;` — `UPROPERTY(BlueprintAssignable)`
- L25 _protected prototype_ `static UAbilityTask_WaitGameplayTagCountChanged* WaitGameplayTagCountChange(UGameplayAbility* OwningAbility, FGameplayTag Tag, AActor* InOptionalExternalTarget = nullptr);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the specified gameplay tag count has changed. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes.
- L27 _protected prototype_ `virtual void Activate() override;`
- L28 _protected prototype_ `virtual void GameplayTagCallback(const FGameplayTag Tag, int32 NewCount);`
- L30 _protected member_ `FGameplayTag Tag;`
- L32 _protected prototype_ `UAbilitySystemComponent* GetTargetASC();`
- L33 _protected prototype_ `virtual void OnDestroy(bool bAbilityIsEnding) override;`
- L36 _protected member_ `TObjectPtr<UAbilitySystemComponent> OptionalExternalTarget;` — `UPROPERTY()`
- L38 _protected member_ `FDelegateHandle GameplayTagCountChangedHandle;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitGameplayTagCountDelegate, int32, TagCount);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitGameplayTagCountDelegate, int32, TagCount);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayTagQuery.h` (Public)


#### enum `EWaitGameplayTagQueryTriggerCondition`  
`enum class EWaitGameplayTagQueryTriggerCondition : uint8`  
_L14-18_
- reflection: `UENUM()`
- desc: This enum defines the condition in which the wait gameplay tag query node will trigger.
- L16 _public enumerator_ `WhenTrue = 0`
- L17 _public enumerator_ `WhenFalse`

#### class `UAbilityTask_WaitGameplayTagQuery`  
`class UAbilityTask_WaitGameplayTagQuery : public UAbilityTask`  
_L22-94_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: This class defines a node to wait on a gameplay tag query.
- L28 _public prototype_ `virtual void Activate() override;` — Activates this AbilityTask.
- L31 _public prototype_ `void SetExternalTarget(const AActor* Actor);` — Sets the external target that this node whould use for checking tags.
- L41 _public prototype_ `static UAbilityTask_WaitGameplayTagQuery* WaitGameplayTagQuery(UGameplayAbility* OwningAbility, const FGameplayTagQuery TagQuery, const AActor* InOptionalExternalTarget = nullptr, const EWaitGameplayTagQueryTriggerCondition TriggerCondition = EWaitGameplayTagQueryTriggerCondition::WhenTrue, const bool bOnlyTriggerOnce = false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the given gameplay tag query has become true or false, based on TriggerCondition. By default this will look at the owner of this ability. OptionalExternalTarget can be set to make this look at another actor's tags for changes.  If the the tag query already satisfies the TriggerCondition when this task is started, it will immediately broadcast the Triggered event. It will keep listening as long as bOnlyTriggerOnce = false.
- L51 _protected prototype_ `void UpdateTargetTags(const FGameplayTag Tag, int32 NewCount);` — `UFUNCTION()` — This will update the tags in the TargetTags container to reflect that tags that are on the target ASC.
- L54 _protected prototype_ `void EvaluateTagQuery();` — This will evaluate the TargetTags using the given TagQuery, executing the Trigger delegate if needed.
- L57 _protected prototype_ `UAbilitySystemComponent* GetTargetASC();` — This gets the ASC to use to listen to tag changed events.
- L60 _protected prototype_ `virtual void OnDestroy(bool AbilityIsEnding) override;` — This will handle cleaning up any registered delegates.
- L63 _protected member_ `FGameplayTagQuery TagQuery;` — This is the tag query to evaluate for triggering this node.
- L66 _protected member_ `bool bRegisteredCallbacks = false;` — Indicates if the callbacks for tag changes have been registered.
- L69 _protected member_ `bool bQueryState = false;` — This was the last result of evaluating the TagQuery.
- L73 _protected member_ `FGameplayTagContainer TargetTags;` — This is the tag container of the targets the target ASC currently has. NOTE: This will only contain the tags referenced in the TagQuery.
- L76 _protected member_ `TMap<FGameplayTag, FDelegateHandle> TagHandleMap;` — This is the handles to the tag changed delegate for each gameplay tag in the TagQuery.
- L80 _protected member_ `FWaitGameplayTagQueryDelegate Triggered;` — `UPROPERTY(BlueprintAssignable)` — This delegate will be triggered when the trigger condition has been met.
- L84 _protected member_ `TObjectPtr<UAbilitySystemComponent> OptionalExternalTarget = nullptr;` — `UPROPERTY()` — This is the optional external target to use when getting the ASC to get tags from.
- L87 _protected member_ `EWaitGameplayTagQueryTriggerCondition TriggerCondition = EWaitGameplayTagQueryTriggerCondition::WhenTrue;` — This indicates when to Trigger the Triggered output for this node.
- L90 _protected member_ `bool bUseExternalTarget = false;` — This indicates if we should use the external target.
- L93 _protected member_ `bool bOnlyTriggerOnce = false;` — This indicates if this node should only trigger once, or any number of times.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L10 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitGameplayTagQueryDelegate);`
- L10 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitGameplayTagQueryDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitInputPress.h` (Public)


#### class `UAbilityTask_WaitInputPress`  
`class UAbilityTask_WaitInputPress : public UAbilityTask`  
_L18-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits until the input is pressed from activating an ability. This should be true immediately upon starting the ability, since the key was pressed to activate it. We expect server to execute this task in parallel and keep its own time. We do not keep track of
- L23 _private member_ `FInputPressDelegate OnPress;` — `UPROPERTY(BlueprintAssignable)`
- L26 _private prototype_ `void OnPressCallback();` — `UFUNCTION()`
- L28 _private prototype_ `virtual void Activate() override;`
- L32 _private prototype_ `static UAbilityTask_WaitInputPress* WaitInputPress(UGameplayAbility* OwningAbility, bool bTestAlreadyPressed=false);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the user presses the input button for this ability's activation. Returns time this node spent waiting for the press. Will return 0 if input was already down.
- L36 _protected member_ `float StartTime;`
- L37 _protected member_ `bool bTestInitialState;`
- L38 _protected member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputPressDelegate, float, TimeWaited);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputPressDelegate, float, TimeWaited);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitInputRelease.h` (Public)


#### class `UAbilityTask_WaitInputRelease`  
`class UAbilityTask_WaitInputRelease : public UAbilityTask`  
_L18-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Waits until the input is released from activating an ability. Clients will replicate a 'release input' event to the server, but not the exact time it was held locally. We expect server to execute this task in parallel and keep its own time.
- L23 _private member_ `FInputReleaseDelegate OnRelease;` — `UPROPERTY(BlueprintAssignable)`
- L26 _private prototype_ `void OnReleaseCallback();` — `UFUNCTION()`
- L28 _private prototype_ `virtual void Activate() override;`
- L32 _private prototype_ `static UAbilityTask_WaitInputRelease* WaitInputRelease(UGameplayAbility* OwningAbility, bool bTestAlreadyReleased=false);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until the user releases the input button for this ability's activation. Returns time from hitting this node, till release. Will return 0 if input was already released.
- L36 _protected member_ `float StartTime;`
- L37 _protected member_ `bool bTestInitialState;`
- L38 _protected member_ `FDelegateHandle DelegateHandle;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputReleaseDelegate, float, TimeHeld);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInputReleaseDelegate, float, TimeHeld);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitMovementModeChange.h` (Public)


#### class `UAbilityTask_WaitMovementModeChange`  
`class UAbilityTask_WaitMovementModeChange : public UAbilityTask`  
_L18-42_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L25 _public member_ `FMovementModeChangedDelegate OnChange;` — `UPROPERTY(BlueprintAssignable)`
- L28 _public prototype_ `void OnMovementModeChange(ACharacter * Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);` — `UFUNCTION()`
- L30 _public member_ `EMovementMode RequiredMode;`
- L34 _public prototype_ `static UAbilityTask_WaitMovementModeChange* CreateWaitMovementModeChange(UGameplayAbility* OwningAbility, EMovementMode NewMode);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE", DisplayName="WaitMovementModeChange"))` — Wait until movement mode changes (E.g., landing)
- L36 _public prototype_ `virtual void Activate() override;`
- L39 _private prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L41 _private member_ `TWeakObjectPtr<ACharacter> MyCharacter;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovementModeChangedDelegate, EMovementMode, NewMovementMode);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMovementModeChangedDelegate, EMovementMode, NewMovementMode);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitOverlap.h` (Public)


#### class `UAbilityTask_WaitOverlap`  
`class UAbilityTask_WaitOverlap : public UAbilityTask`  
_L22-44_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Fixme: this is still incomplete and probablyh not what most games want for melee systems. -Only actually activates on Blocking hits -Uses first PrimitiveComponent instead of being able to specify arbitrary component.
- L27 _private member_ `FWaitOverlapDelegate OnOverlap;` — `UPROPERTY(BlueprintAssignable)`
- L30 _private prototype_ `void OnHitCallback(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);` — `UFUNCTION()`
- L32 _private prototype_ `virtual void Activate() override;`
- L36 _private prototype_ `static UAbilityTask_WaitOverlap* WaitForOverlap(UGameplayAbility* OwningAbility);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until an overlap occurs. This will need to be better fleshed out so we can specify game specific collision requirements
- L40 _private prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L42 _private prototype_ `UPrimitiveComponent* GetComponent();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L11 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitOverlapDelegate, const FGameplayAbilityTargetDataHandle&, TargetData);`
- L11 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitOverlapDelegate, const FGameplayAbilityTargetDataHandle&, TargetData);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitTargetData.h` (Public)


#### class `UAbilityTask_WaitTargetData`  
`class UAbilityTask_WaitTargetData: public UAbilityTask`  
_L24-92_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- desc: Wait for targeting actor (spawned from parameter) to provide data. Can be set not to end upon outputting data. Can be ended by task name. WARNING: These actors are spawned once per ability activation and in their default form are not very efficient For most games you will need to subclass and heavily modify this actor, or you will want to implement similar functions in a game-specific actor or blueprint to avoid actor spawn costs This task is not well tested by internal games, but it is a useful class to look at to learn how target replication occurs
- L29 _private member_ `FWaitTargetDataDelegate ValidData;` — `UPROPERTY(BlueprintAssignable)`
- L32 _private member_ `FWaitTargetDataDelegate Cancelled;` — `UPROPERTY(BlueprintAssignable)`
- L35 _private prototype_ `virtual void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& Data, FGameplayTag ActivationTag);` — `UFUNCTION()`
- L38 _private prototype_ `virtual void OnTargetDataReplicatedCancelledCallback();` — `UFUNCTION()`
- L41 _private prototype_ `virtual void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& Data);` — `UFUNCTION()`
- L44 _private prototype_ `virtual void OnTargetDataCancelledCallback(const FGameplayAbilityTargetDataHandle& Data);` — `UFUNCTION()`
- L48 _private prototype_ `static UAbilityTask_WaitTargetData* WaitTargetData(UGameplayAbility* OwningAbility, FName TaskInstanceName, TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType, TSubclassOf<AGameplayAbilityTargetActor> Class);` — `UFUNCTION(BlueprintCallable, meta=(HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms="Instigator"), Category="Ability|Tasks")` — Spawns target actor and waits for it to return valid data or to be canceled.
- L52 _private prototype_ `static UAbilityTask_WaitTargetData* WaitTargetDataUsingActor(UGameplayAbility* OwningAbility, FName TaskInstanceName, TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType, AGameplayAbilityTargetActor* TargetActor);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true", HideSpawnParms = "Instigator"), Category = "Ability|Tasks")` — Uses specified target actor and waits for it to return valid data or to be canceled.
- L54 _private prototype_ `virtual void Activate() override;`
- L57 _private prototype_ `virtual bool BeginSpawningActor(UGameplayAbility* OwningAbility, TSubclassOf<AGameplayAbilityTargetActor> Class, AGameplayAbilityTargetActor*& SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")`
- L60 _private prototype_ `virtual void FinishSpawningActor(UGameplayAbility* OwningAbility, AGameplayAbilityTargetActor* SpawnedActor);` — `UFUNCTION(BlueprintCallable, meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"), Category = "Abilities")`
- L63 _private prototype_ `virtual void ExternalConfirm(bool bEndTask) override;` — Called when the ability is asked to confirm from an outside node. What this means depends on the individual task. By default, this does nothing other than ending if bEndTask is true.
- L66 _private prototype_ `virtual void ExternalCancel() override;` — Called when the ability is asked to cancel from an outside node. What this means depends on the individual task. By default, this does nothing other than ending the task.
- L70 _protected prototype_ `virtual bool ShouldSpawnTargetActor() const;`
- L71 _protected prototype_ `virtual void InitializeTargetActor(AGameplayAbilityTargetActor* SpawnedActor) const;`
- L72 _protected prototype_ `virtual void FinalizeTargetActor(AGameplayAbilityTargetActor* SpawnedActor) const;`
- L74 _protected prototype_ `virtual void RegisterTargetDataCallbacks();`
- L76 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L78 _protected prototype_ `virtual bool ShouldReplicateDataToServer() const;`
- L83 _protected member_ `TSubclassOf<AGameplayAbilityTargetActor> TargetClass;` — `UPROPERTY()`
- L87 _protected member_ `TObjectPtr<AGameplayAbilityTargetActor> TargetActor;` — `UPROPERTY()` — The TargetActor that we spawned
- L89 _protected member_ `TEnumAsByte<EGameplayTargetingConfirmation::Type> ConfirmationType;`
- L91 _protected member_ `FDelegateHandle OnTargetDataReplicatedCallbackDelegateHandle;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitTargetDataDelegate, const FGameplayAbilityTargetDataHandle&, Data);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitTargetDataDelegate, const FGameplayAbilityTargetDataHandle&, Data);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitVelocityChange.h` (Public)


#### class `UAbilityTask_WaitVelocityChange`  
`class UAbilityTask_WaitVelocityChange: public UAbilityTask`  
_L16-39_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UAbilityTask`
- L22 _private member_ `FWaitVelocityChangeDelegate OnVelocityChage;` — `UPROPERTY(BlueprintAssignable)` — Delegate called when velocity requirements are met
- L24 _private prototype_ `virtual void TickTask(float DeltaTime) override;`
- L28 _private prototype_ `static UAbilityTask_WaitVelocityChange* CreateWaitVelocityChange(UGameplayAbility* OwningAbility, FVector Direction, float MinimumMagnitude);` — `UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName="WaitVelocityChange",HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait for the actor's movement component velocity to be of minimum magnitude when projected along given direction
- L30 _private prototype_ `virtual void Activate() override;`
- L35 _protected member_ `TWeakObjectPtr<UMovementComponent> CachedMovementComponent;` — `UPROPERTY()`
- L37 _protected member_ `float MinimumMagnitude;`
- L38 _protected member_ `FVector Direction;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L13 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitVelocityChangeDelegate);`
- L13 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitVelocityChangeDelegate);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemBlueprintLibrary.h` (Public)


#### struct `FGameplayTagChangedEventWrapperSpec`  
`struct FGameplayTagChangedEventWrapperSpec`  
_L30-49_
- desc: Holds tracking data for gameplay tag change event wrappers that have been bound.
- L32 _public prototype_ `FGameplayTagChangedEventWrapperSpec( UAbilitySystemComponent* AbilitySystemComponent, FOnGameplayTagChangedEventWrapperSignature InGameplayTagChangedEventWrapperDelegate, EGameplayTagEventType::Type InTagListeningPolicy);`
- L36 _public prototype_ `~FGameplayTagChangedEventWrapperSpec();`
- L39 _public member_ `TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponentWk;` — The AbilitySystemComponent this spec is bound to.
- L42 _public member_ `FOnGameplayTagChangedEventWrapperSignature GameplayTagChangedEventWrapperDelegate;` — The event wrapper delegate cached off, to be executed when the gameplaytag(s) we care about are changed.
- L45 _public member_ `EGameplayTagEventType::Type TagListeningPolicy;` — Specifies what kinds of gameplay tag changes we will execute for.
- L48 _public member_ `TMap<FGameplayTag, FDelegateHandle> DelegateBindings;` — Map of the respective gameplay tags to the delegate handle the ASC gave us to use for unbinding later.

#### struct `FGameplayTagChangedEventWrapperSpecHandle`  
`struct FGameplayTagChangedEventWrapperSpecHandle`  
_L53-65_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle to a event wrapper listening for gameplay tag change(s) via one of the BindEventWrapper<to gameplay tag(s)> methods on the AbilitySystemLibrary
- L57 _public prototype_ `FGameplayTagChangedEventWrapperSpecHandle();`
- L58 _public prototype_ `FGameplayTagChangedEventWrapperSpecHandle(FGameplayTagChangedEventWrapperSpec* DataPtr);`
- L61 _public member_ `TSharedPtr<FGameplayTagChangedEventWrapperSpec> Data;` — Internal pointer to binding spec
- L63 _public prototype_ `bool operator==(FGameplayTagChangedEventWrapperSpecHandle const& Other) const;`
- L64 _public prototype_ `bool operator!=(FGameplayTagChangedEventWrapperSpecHandle const& Other) const;`

#### class `UAbilitySystemBlueprintLibrary`  
`class UAbilitySystemBlueprintLibrary : public UBlueprintFunctionLibrary`  
_L69-661_
- reflection: `UCLASS(meta=(ScriptName="AbilitySystemLibrary"), MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint library for ability system. Many of these functions are useful to call from native as well
- L75 _private prototype_ `static UAbilitySystemComponent* GetAbilitySystemComponent(AActor* Actor);` — `UFUNCTION(BlueprintPure, Category = Ability, Meta=(DefaultToSelf = "Actor"))` — Tries to find an ability system component on the actor, will use AbilitySystemInterface or fall back to a component search
- L83 _private prototype_ `static void SendGameplayEventToActor(AActor* Actor, UPARAM(meta=(GameplayTagFilter="GameplayEventTagsCategory")) FGameplayTag EventTag, FGa` — `UFUNCTION(BlueprintCallable, Category = Ability, Meta = (Tooltip = "This function can be used to trigger an ability on the actor in question with useful payload data."))` — This function can be used to trigger an ability on the actor in question with useful payload data. NOTE: GetAbilitySystemComponent is called on the actor to find a good component, and if the component isn't found, the event will not be sent.
- L100 _private prototype_ `static FGameplayTagChangedEventWrapperSpecHandle BindEventWrapperToGameplayTagChanged( UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag Tag, FOnGameplayTagChangedEventWrapperSignature GameplayTagChangedEventWrapperDelegate, bool bExecuteImmediatelyIfTagApplied = true, EGameplayTagEventType::Type TagListeningPolicy = EGameplayTagEventType::NewOrRemoved);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Tags", meta = (AdvancedDisplay = "bExecuteImmediatelyIfTagApplied, TagListeningPolicy"))` — Binds to changes in the given Tag on the given ASC's owned tags. Cache off the returned handle and call one of the 'Unbind'...'EventWrapper' fns and pass in the handle when you are finished with the binding. @param Tag                               FGameplayTag to listen for changes on @param BindingObject                     UObject owning the Event (usually self) @param GameplayTagChangedEventWrapperDelegate Tag Changed Event to trigger @param bExecuteImmediatelyIfTagApplied   If true, the bound event will immediately execute if we already have the tag. @param TagListeningPolicy                Whether we are listening for any tag change or just applied/removed. @return                                  FGameplayTagChangedEventWrapperSpecHandle Handle by which this binding request can be unbound.
- L118 _private prototype_ `static FGameplayTagChangedEventWrapperSpecHandle BindEventWrapperToAnyOfGameplayTagsChanged( UAbilitySystemComponent* AbilitySystemComponent, const TArray<FGameplayTag>& Tags, FOnGameplayTagChangedEventWrapperSignature GameplayTagChangedEventWrapperDelegate, bool bExecuteImmediatelyIfTagApplied = true, EGameplayTagEventType::Type TagListeningPolicy = EGameplayTagEventType::NewOrRemoved);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Tags", meta = (AdvancedDisplay = "bExecuteImmediatelyIfTagApplied, TagListeningPolicy"))` — Binds to changes in the given Tags on the given ASC's owned tags. Cache off the returned handle and call one of the 'Unbind'...'EventWrapper' fns and pass in the handle when you are finished with the binding. @param Tags                              TArray of FGameplayTag to listen for changes on @param BindingObject                     UObject owning the Event (usually self) @param GameplayTagChangedEventWrapperDelegate Tag Changed Event to trigger @param bExecuteImmediatelyIfTagApplied   If true, the bound event will immediately execute if we already have the tag. @param TagListeningPolicy                Whether we are listening for any tag change or just applied/removed. @return                                  FGameplayTagChangedEventWrapperSpecHandle Handle by which this binding request can be unbound.
- L136 _private prototype_ `static FGameplayTagChangedEventWrapperSpecHandle BindEventWrapperToAnyOfGameplayTagContainerChanged( UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTagContainer TagContainer, FOnGameplayTagChangedEventWrapperSignature GameplayTagChangedEventWrapperDelegate, bool bExecuteImmediatelyIfTagApplied = true, EGameplayTagEventType::Type TagListeningPolicy = EGameplayTagEventType::NewOrRemoved);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Tags", meta = (AdvancedDisplay = "bExecuteImmediatelyIfTagApplied, TagListeningPolicy"))` — Binds to changes in the given TagContainer on the given ASC's owned tags. Cache off the returned handle and call one of the 'Unbind'...'EventWrapper' fns and pass in the handle when you are finished with the binding. @param TagContainer                      FGameplayTagContainer of tags to listen for changes on @param BindingObject                     UObject owning the Event (usually self) @param GameplayTagChangedEventWrapperDelegate Tag Changed Event to trigger @param bExecuteImmediatelyIfTagApplied   If true, the bound event will immediately execute if we already have the tag. @param TagListeningPolicy                Whether we are listening for any tag change or just applied/removed. @return                                  FGameplayTagChangedEventWrapperSpecHandle Handle by which this binding request can be unbound.
- L149 _private prototype_ `static void UnbindAllGameplayTagChangedEventWrappersForHandle(FGameplayTagChangedEventWrapperSpecHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Tags")` — Unbinds the event wrapper tag change event bound via a BindEventWrapper<to gameplay tag(s)> method that is tied to the given Handle. (expected to unbind 1 or none) @param Handle     FGameplayTagChangedEventWrapperSpecHandle Handle provided when binding to a delegate
- L159 _private prototype_ `static void UnbindGameplayTagChangedEventWrapperForHandle(FGameplayTag Tag, FGameplayTagChangedEventWrapperSpecHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Tags")` — Unbinds the event wrapper tag change event bound via a BindEventWrapper<to gameplay tag(s)> method that is tied to the given Handle, for the specific tag. and were bound to the given Tag. (expected to unbind 1 or none, only makes sense to call if the original binding was for listening to multiple tags.) @param Tag        FGameplayTag to unbind from @param Handle     int Handle provided when binding to a delegate
- L164 _protected prototype_ `static void ProcessGameplayTagChangedEventWrapper(const FGameplayTag GameplayTag, int32 GameplayTagCount, FOnGameplayTagChangedEventWrapperSignature GameplayTagChangedEventWrapperDelegate);` — Helper fn to process gameplay tag changed event wrappers.
- L174 _public prototype_ `static bool IsValid(FGameplayAttribute Attribute);` — `UFUNCTION(BlueprintPure, Category = "Ability|Attribute")` — Returns true if the attribute actually exists
- L178 _public prototype_ `static float GetFloatAttribute(const AActor* Actor, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute);` — `UFUNCTION(BlueprintPure, Category = "Ability|Attribute")` — Returns the value of Attribute from the ability system component belonging to Actor.
- L182 _public prototype_ `static float GetFloatAttributeFromAbilitySystemComponent(const UAbilitySystemComponent* AbilitySystem, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute);` — `UFUNCTION(BlueprintPure, Category = "Ability|Attribute")` — Returns the value of Attribute from the ability system component AbilitySystem.
- L186 _public prototype_ `static float GetFloatAttributeBase(const AActor* Actor, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute);` — `UFUNCTION(BlueprintPure, Category = "Ability|Attribute")` — Returns the base value of Attribute from the ability system component belonging to Actor.
- L190 _public prototype_ `static float GetFloatAttributeBaseFromAbilitySystemComponent(const UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute, bool& bSuccessfullyFoundAttribute);` — `UFUNCTION(BlueprintPure, Category = "Ability|Attribute")` — Returns the base value of Attribute from the ability system component AbilitySystemComponent.
- L194 _public prototype_ `static float EvaluateAttributeValueWithTags(UAbilitySystemComponent* AbilitySystem, FGameplayAttribute Attribute, const FGameplayTagContainer& SourceTags, const FGameplayTagContainer& TargetTags, bool& bSuccess);` — `UFUNCTION(BlueprintPure, Category = "Ability|Attribute")` — Returns the value of Attribute from the ability system component AbilitySystem after evaluating it with source and target tags. bSuccess indicates the success or failure of this operation.
- L198 _public prototype_ `static float EvaluateAttributeValueWithTagsAndBase(UAbilitySystemComponent* AbilitySystem, FGameplayAttribute Attribute, const FGameplayTagContainer& SourceTags, const FGameplayTagContainer& TargetTags, float BaseValue, bool& bSuccess);` — `UFUNCTION(BlueprintPure, Category = "Ability|Attribute")` — Returns the value of Attribute from the ability system component AbilitySystem after evaluating it with source and target tags using the passed in base value instead of the real base value. bSuccess indicates the success or failure of this operation.
- L202 _public prototype_ `static bool EqualEqual_GameplayAttributeGameplayAttribute(FGameplayAttribute AttributeA, FGameplayAttribute AttributeB);` — `UFUNCTION(BlueprintPure, meta=(DisplayName = "Equal (Gameplay Attribute)", CompactNodeTitle = "==", Keywords = "== equal"), Category="Ability|Attribute")` — Simple equality operator for gameplay attributes
- L206 _public prototype_ `static bool NotEqual_GameplayAttributeGameplayAttribute(FGameplayAttribute AttributeA, FGameplayAttribute AttributeB);` — `UFUNCTION(BlueprintPure, meta=(DisplayName = "Not Equal (Gameplay Attribute)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category="Ability|Attribute")` — Simple inequality operator for gameplay attributes
- L210 _public prototype_ `static FString GetDebugStringFromGameplayAttribute(const FGameplayAttribute& Attribute);` — `UFUNCTION(BlueprintPure, Category="Ability|Attribute")` — Returns FString representation of a gameplay attribute's set class and name, in the form of AttrSetName.AttrName (or just AttrName if not part of a set).
- L218 _public prototype_ `static FGameplayAbilityTargetDataHandle AppendTargetDataHandle(FGameplayAbilityTargetDataHandle TargetHandle, const FGameplayAbilityTargetDataHandle& HandleToAdd);` — `UFUNCTION(BlueprintCallable, Category = "Ability|TargetData")` — Copies targets from HandleToAdd to TargetHandle
- L222 _public prototype_ `static FGameplayAbilityTargetDataHandle AbilityTargetDataFromLocations(const FGameplayAbilityTargetingLocationInfo& SourceLocation, const FGameplayAbilityTargetingLocationInfo& TargetLocation);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Creates a target data with a source and destination location
- L226 _public prototype_ `static FGameplayAbilityTargetDataHandle AbilityTargetDataFromHitResult(const FHitResult& HitResult);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Creates a target data with a single hit result
- L230 _public prototype_ `static int32 GetDataCountFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns number of target data objects, not necessarily number of distinct targets
- L234 _public prototype_ `static FGameplayAbilityTargetDataHandle AbilityTargetDataFromActor(AActor* Actor);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Creates single actor target data
- L238 _public prototype_ `static FGameplayAbilityTargetDataHandle AbilityTargetDataFromActorArray(const TArray<AActor*>& ActorArray, bool OneTargetPerHandle);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Creates actor array target data
- L242 _public prototype_ `static FGameplayAbilityTargetDataHandle FilterTargetData(const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTargetDataFilterHandle ActorFilterClass);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Create a new target data handle with filtration performed on the data
- L246 _public prototype_ `static FGameplayTargetDataFilterHandle MakeFilterHandle(FGameplayTargetDataFilter Filter, AActor* FilterActor);` — `UFUNCTION(BlueprintPure, Category = "Filter")` — Create a handle for filtering target data, filling out all fields
- L251 _public prototype_ `static FGameplayEffectSpecHandle MakeSpecHandle(UGameplayEffect* InGameplayEffect, AActor* InInstigator, AActor* InEffectCauser, float InLevel = 1.0f);` — `UE_DEPRECATED(5.5, "Use MakeSpecHandleByClass. It's safer as InGameplayEffect needs to be a CDO")` — `UFUNCTION(BlueprintPure, Category = "Spec", meta=(DeprecatedFunction, DeprecatedMessage="Use Make Spec Handle (By Class)"))` — Create a spec handle, filling out all fields
- L255 _public prototype_ `static FGameplayEffectSpecHandle MakeSpecHandleByClass(TSubclassOf<UGameplayEffect> GameplayEffect, AActor* Instigator, AActor* EffectCauser, float Level = 1.0f);` — `UFUNCTION(BlueprintCallable, Category = "Spec", meta=(DisplayName="Make Spec Handle (By Class)"))` — Create a spec handle, filling out all fields
- L259 _public prototype_ `static FGameplayEffectSpecHandle CloneSpecHandle(AActor* InNewInstigator, AActor* InEffectCauser, FGameplayEffectSpecHandle GameplayEffectSpecHandle_Clone);` — `UFUNCTION(BlueprintPure, Category = "Spec")` — Create a spec handle, cloning another
- L263 _public prototype_ `static TArray<AActor*> GetActorsFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns all actors targeted, for a given index
- L267 _public prototype_ `static TArray<AActor*> GetAllActorsFromTargetData(const FGameplayAbilityTargetDataHandle& TargetData);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns all actors targeted
- L271 _public prototype_ `static bool DoesTargetDataContainActor(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index, AActor* Actor);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns true if the given TargetData has the actor passed in targeted
- L275 _public prototype_ `static bool TargetDataHasActor(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns true if the given TargetData has at least 1 actor targeted
- L279 _public prototype_ `static bool TargetDataHasHitResult(const FGameplayAbilityTargetDataHandle& HitResult, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns true if the target data has a hit result
- L283 _public prototype_ `static FHitResult GetHitResultFromTargetData(const FGameplayAbilityTargetDataHandle& HitResult, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns the hit result for a given index if it exists
- L287 _public prototype_ `static bool TargetDataHasOrigin(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns true if the target data has an origin
- L291 _public prototype_ `static FTransform GetTargetDataOrigin(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns the origin for a given index if it exists
- L295 _public prototype_ `static bool TargetDataHasEndPoint(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns true if the target data has an end point
- L299 _public prototype_ `static FVector GetTargetDataEndPoint(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns the end point for a given index if it exists
- L303 _public prototype_ `static FTransform GetTargetDataEndPointTransform(const FGameplayAbilityTargetDataHandle& TargetData, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|TargetData")` — Returns the end point transform for a given index if it exists
- L311 _public prototype_ `static bool EffectContextIsValid(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "IsValid"))` — Returns true if this context has ever been initialized
- L315 _public prototype_ `static bool EffectContextIsInstigatorLocallyControlled(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "IsInstigatorLocallyControlled"))` — Returns true if the ability system component that instigated this is locally controlled
- L319 _public prototype_ `static FHitResult EffectContextGetHitResult(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetHitResult"))` — Extracts a hit result from the effect context if it is set
- L323 _public prototype_ `static bool EffectContextHasHitResult(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "HasHitResult"))` — Returns true if there is a valid hit result inside the effect context
- L327 _public prototype_ `static void EffectContextAddHitResult(FGameplayEffectContextHandle EffectContext, FHitResult HitResult, bool bReset);` — `UFUNCTION(BlueprintCallable, Category = "Ability|EffectContext", Meta = (DisplayName = "AddHitResult"))` — Adds a hit result to the effect context
- L331 _public prototype_ `static FVector EffectContextGetOrigin(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetOrigin"))` — Gets the location the effect originated from
- L335 _public prototype_ `static void EffectContextSetOrigin(FGameplayEffectContextHandle EffectContext, FVector Origin);` — `UFUNCTION(BlueprintCallable, Category = "Ability|EffectContext", Meta = (DisplayName = "SetOrigin"))` — Sets the location the effect originated from
- L339 _public prototype_ `static AActor* EffectContextGetInstigatorActor(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetInstigatorActor"))` — Gets the instigating actor (that holds the ability system component) of the EffectContext
- L343 _public prototype_ `static AActor* EffectContextGetOriginalInstigatorActor(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetOriginalInstigatorActor"))` — Gets the original instigator actor that started the chain of events to cause this effect
- L347 _public prototype_ `static AActor* EffectContextGetEffectCauser(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetEffectCauser"))` — Gets the physical actor that caused the effect, possibly a projectile or weapon
- L351 _public prototype_ `static UObject* EffectContextGetSourceObject(FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintPure, Category = "Ability|EffectContext", Meta = (DisplayName = "GetSourceObject"))` — Gets the source object of the effect.
- L359 _public prototype_ `static bool IsInstigatorLocallyControlled(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category="Ability|GameplayCue")` — Returns true if the ability system component that spawned this cue is locally controlled
- L363 _public prototype_ `static bool IsInstigatorLocallyControlledPlayer(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category="Ability|GameplayCue")` — Returns true if the ability system component that spawned this cue is locally controlled and a player
- L367 _public prototype_ `static int32 GetActorCount(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Returns number of actors stored in the Effect Context used by this cue
- L371 _public prototype_ `static AActor* GetActorByIndex(FGameplayCueParameters Parameters, int32 Index);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Returns actor stored in the Effect Context used by this cue
- L375 _public prototype_ `static FHitResult GetHitResult(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Returns a hit result stored in the effect context if valid
- L379 _public prototype_ `static bool HasHitResult(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Checks if the effect context has a hit reslt stored inside
- L383 _public prototype_ `static void ForwardGameplayCueToTarget(TScriptInterface<IGameplayCueInterface> TargetCueInterface, EGameplayCueEvent::Type EventType, FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayCue")` — Forwards the gameplay cue to another gameplay cue interface object
- L387 _public prototype_ `static AActor* GetInstigatorActor(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Gets the instigating actor (that holds the ability system component) of the GameplayCue
- L391 _public prototype_ `static FTransform GetInstigatorTransform(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Gets instigating world location
- L395 _public prototype_ `static FVector GetOrigin(FGameplayCueParameters Parameters);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Gets instigating world location
- L399 _public prototype_ `static bool GetGameplayCueEndLocationAndNormal(AActor* TargetActor, FGameplayCueParameters Parameters, FVector& Location, FVector& Normal);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Gets the best end location and normal for this gameplay cue. If there is hit result data, it will return this. Otherwise it will return the target actor's location/rotation. If none of this is available, it will return false.
- L403 _public prototype_ `static bool GetGameplayCueDirection(AActor* TargetActor, FGameplayCueParameters Parameters, FVector& Direction);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Gets the best normalized effect direction for this gameplay cue. This is useful for effects that require the direction of an enemy attack. Returns true if a valid direction could be calculated.
- L407 _public prototype_ `static bool DoesGameplayCueMeetTagRequirements(FGameplayCueParameters Parameters, const FGameplayTagRequirements& SourceTagReqs, const FGameplayTagRequirements& TargetTagReqs);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue")` — Returns true if the aggregated source and target tags from the effect spec meets the tag requirements
- L411 _public prototype_ `static FGameplayCueParameters MakeGameplayCueParameters(float NormalizedMagnitude, float RawMagnitude, FGameplayEffectContextHandle EffectContext, FGameplayTag MatchedTagName, FGameplayTag OriginalTag, FGameplayTagContainer AggregatedSourceTags, FGameplayTagContainer AggregatedTargetTags, FVector Location, FVector Normal, AActor* Instigator, AActor* EffectCauser, UObject* SourceObject, UPhysicalMaterial* PhysicalMaterial, int32 GameplayEffectLevel, int32 AbilityLevel, USceneComponent* TargetAttachComponent, bool bReplicateLocationWhenUsingMinimalRepProxy);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue", meta = (NativeMakeFunc, AdvancedDisplay=5, Location="0,0,0", Normal= "0,0,0", GameplayEffectLevel = "1", AbilityLevel = "1"))` — Native make, to avoid having to deal with quantized vector types
- L415 _public prototype_ `static void BreakGameplayCueParameters(const struct FGameplayCueParameters& Parameters, float& NormalizedMagnitude, float& RawMagnitude, FGameplayEffectContextHandle& EffectContext, FGameplayTag& MatchedTagName, FGameplayTag& OriginalTag, FGameplayTagContainer& AggregatedSourceTags, FGameplayTagContainer& AggregatedTargetTags, FVector& Location, FVector& Normal, AActor*& Instigator, AActor*& EffectCauser, UObject*& SourceObject, UPhysicalMaterial*& PhysicalMaterial, int32& GameplayEffectLevel, int32& AbilityLevel, USceneComponent*& TargetAttachComponent, bool& bReplicateLocationWhenUsingMinimalRepProxy);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayCue", meta = (NativeBreakFunc, AdvancedDisplay=6))` — Native break, to avoid having to deal with quantized vector types
- L423 _public prototype_ `static FGameplayEffectSpecHandle AssignSetByCallerMagnitude(FGameplayEffectSpecHandle SpecHandle, FName DataName, float Magnitude);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Sets a raw name Set By Caller magnitude value, the tag version should normally be used
- L427 _public prototype_ `static FGameplayEffectSpecHandle AssignTagSetByCallerMagnitude(FGameplayEffectSpecHandle SpecHandle, FGameplayTag DataTag, float Magnitude);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect", meta = (GameplayTagFilter = "SetByCaller"))` — Sets a gameplay tag Set By Caller magnitude value
- L431 _public prototype_ `static FGameplayEffectSpecHandle SetDuration(FGameplayEffectSpecHandle SpecHandle, float Duration);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Manually sets the duration on a specific effect
- L435 _public prototype_ `static FGameplayEffectSpecHandle AddGrantedTag(FGameplayEffectSpecHandle SpecHandle, FGameplayTag NewGameplayTag);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — This instance of the effect will now grant NewGameplayTag to the object that this effect is applied to
- L439 _public prototype_ `static FGameplayEffectSpecHandle AddGrantedTags(FGameplayEffectSpecHandle SpecHandle, FGameplayTagContainer NewGameplayTags);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — This instance of the effect will now grant NewGameplayTags to the object that this effect is applied to
- L443 _public prototype_ `static FGameplayTagContainer GetGrantedTags(FGameplayEffectSpecHandle SpecHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Return all tags granted by this GameplayEffectSpec: both from the GE asset and dynamic granted tags.
- L447 _public prototype_ `static FGameplayEffectSpecHandle AddAssetTag(FGameplayEffectSpecHandle SpecHandle, FGameplayTag NewGameplayTag);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Adds NewGameplayTag to this instance of the effect
- L451 _public prototype_ `static FGameplayEffectSpecHandle AddAssetTags(FGameplayEffectSpecHandle SpecHandle, FGameplayTagContainer NewGameplayTags);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Adds NewGameplayTags to this instance of the effect
- L455 _public prototype_ `static FGameplayTagContainer GetAssetTags(FGameplayEffectSpecHandle SpecHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Return all asset tags of this GameplayEffectSpec: both from the GE asset and dynamic asset tags.
- L460 _public prototype_ `static FGameplayEffectSpecHandle AddLinkedGameplayEffectSpec(FGameplayEffectSpecHandle SpecHandle, FGameplayEffectSpecHandle LinkedGameplayEffectSpec);` — `UE_DEPRECATED(5.3, "Linked GameplayEffects aren't replicated. The new UAdditionalGameplayEffectsComponent renders this functionality obsolete (and since it's configured in the Asset, it is properly synced).")` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect", meta = (DeprecatedFunction, DeprecatedMessage="Linked GameplayEffects aren't replicated. Configure the GameplayEffect asset with a suitable GameplayEffectComponent."))` — Adds LinkedGameplayEffectSpec to SpecHandles. LinkedGameplayEffectSpec will be applied when/if SpecHandle is applied successfully. LinkedGameplayEffectSpec will not be modified here. Returns the ORIGINAL SpecHandle (legacy decision)
- L465 _public prototype_ `static FGameplayEffectSpecHandle AddLinkedGameplayEffect(FGameplayEffectSpecHandle SpecHandle, TSubclassOf<UGameplayEffect> LinkedGameplayEffect);` — `UE_DEPRECATED(5.3, "Linked GameplayEffects aren't replicated. The new UAdditionalGameplayEffectsComponent renders this functionality obsolete (and since it's configured in the Asset, it is properly synced).")` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect", meta = (DeprecatedFunction, DeprecatedMessage = "Linked GameplayEffects aren't replicated. Configure the GameplayEffect asset with a suitable GameplayEffectComponent."))` — Adds LinkedGameplayEffect to SpecHandles. LinkedGameplayEffectSpec will be applied when/if SpecHandle is applied successfully. This will initialize the LinkedGameplayEffect's Spec for you. Returns to NEW linked spec in case you want to add more to it.
- L469 _public prototype_ `static FGameplayEffectSpecHandle SetStackCount(FGameplayEffectSpecHandle SpecHandle, int32 StackCount);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Sets the GameplayEffectSpec's StackCount to the specified amount (prior to applying)
- L473 _public prototype_ `static FGameplayEffectSpecHandle SetStackCountToMax(FGameplayEffectSpecHandle SpecHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Sets the GameplayEffectSpec's StackCount to the max stack count defined in the GameplayEffect definition
- L477 _public prototype_ `static FGameplayEffectContextHandle GetEffectContext(FGameplayEffectSpecHandle SpecHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Gets the GameplayEffectSpec's effect context handle
- L482 _public prototype_ `static TArray<FGameplayEffectSpecHandle> GetAllLinkedGameplayEffectSpecHandles(FGameplayEffectSpecHandle SpecHandle);` — `UE_DEPRECATED(5.3, "Linked GameplayEffects aren't replicated. The new UAdditionalGameplayEffectsComponent renders this functionality obsolete (and since it's configured in the Asset, it is properly synced).")` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect", meta = (DeprecatedFunction, DeprecatedMessage = "Linked GameplayEffects aren't replicated. Configure the GameplayEffect asset with a suitable GameplayEffectComponent."))` — Returns handles for all Linked GE Specs that SpecHandle may apply. Useful if you want to append additional information to them.
- L486 _public prototype_ `static bool AddLooseGameplayTags(AActor* Actor, const FGameplayTagContainer& GameplayTags, bool bShouldReplicate=false);` — `UFUNCTION(BlueprintCallable, Category="Ability|GameplayEffect")` — Manually adds a set of tags to a given actor, and optionally replicates them.
- L490 _public prototype_ `static bool RemoveLooseGameplayTags(AActor* Actor, const FGameplayTagContainer& GameplayTags, bool bShouldReplicate=false);` — `UFUNCTION(BlueprintCallable, Category="Ability|GameplayEffect")` — Manually removes a set of tags from a given actor, with optional replication.
- L494 _public prototype_ `static bool AddGameplayTags(AActor* Actor, const FGameplayTagContainer& GameplayTags, EGameplayTagReplicationState ReplicationRule = EGameplayTagReplicationState::None);` — `UFUNCTION(BlueprintCallable, Category="Ability|GameplayEffect")` — Manually adds a set of tags to a given actor
- L498 _public prototype_ `static bool RemoveGameplayTags(AActor* Actor, const FGameplayTagContainer& GameplayTags, EGameplayTagReplicationState ReplicationRule = EGameplayTagReplicationState::None);` — `UFUNCTION(BlueprintCallable, Category="Ability|GameplayEffect")` — Manually removes a set of tags from a given actor
- L502 _public prototype_ `static const UGameplayEffect* GetGameplayEffectFromSpecHandle(FGameplayEffectSpecHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Get the GameplayEffect definition from a GameplayEffectSpecHandle.
- L506 _public prototype_ `static bool IsDurationGameplayEffectSpecHandle(FGameplayEffectSpecHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns whether the GameplayEffectSpecHandle represents a non-instant GameplayEffect.
- L510 _public prototype_ `static EGameplayEffectDurationType GetDurationPolicyFromGameplayEffectSpecHandle(FGameplayEffectSpecHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the Duration Policy of a GameplayEffectSpec.
- L518 _public prototype_ `static float GetModifiedAttributeMagnitude(FGameplayEffectSpecHandle SpecHandle, FGameplayAttribute Attribute);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Gets the magnitude of change for an attribute on an APPLIED GameplayEffectSpec.
- L521 _public prototype_ `static float GetModifiedAttributeMagnitude(const FGameplayEffectSpec& SpecHandle, FGameplayAttribute Attribute);` — Helper function that may be useful to call from native as well
- L529 _public prototype_ `static bool IsActiveGameplayEffectHandleValid(FActiveGameplayEffectHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns whether the active gameplay effect handle has a valid handle value, regardless of whether the effect expired.
- L533 _public prototype_ `static bool IsActiveGameplayEffectHandleActive(FActiveGameplayEffectHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns whether the active gameplay effect handle represents a gameplay effect that is valid and still active.
- L537 _public prototype_ `static class UAbilitySystemComponent* GetAbilitySystemComponentFromActiveGameplayEffectHandle(FActiveGameplayEffectHandle Handle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns AbilitySystemComponent from an ActiveGameplayEffectHandle.
- L541 _public prototype_ `static int32 GetActiveGameplayEffectStackCount(FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns current stack count of an active Gameplay Effect. Will return 0 if the GameplayEffect is no longer valid.
- L545 _public prototype_ `static int32 GetActiveGameplayEffectStackLimitCount(FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns stack limit count of an active Gameplay Effect. Will return 0 if the GameplayEffect is no longer valid.
- L549 _public prototype_ `static float GetActiveGameplayEffectStartTime(FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the start time (time which the GE was added) for a given GameplayEffect
- L553 _public prototype_ `static float GetActiveGameplayEffectExpectedEndTime(FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the expected end time (when we think the GE will expire) for a given GameplayEffect (note someone could remove or change it before that happens!)
- L557 _public prototype_ `static float GetActiveGameplayEffectTotalDuration(FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the total duration for a given GameplayEffect
- L561 _public prototype_ `static float GetActiveGameplayEffectRemainingDuration(UObject* WorldContextObject, FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect", meta = (WorldContext = "WorldContextObject"))` — Returns the total duration for a given GameplayEffect, basically ExpectedEndTime - Current Time
- L565 _public prototype_ `static FString GetActiveGameplayEffectDebugString(FActiveGameplayEffectHandle ActiveHandle);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect", Meta = (DisplayName = "Get Active GameplayEffect Debug String "))` — Returns a debug string for display
- L569 _public prototype_ `static const UGameplayEffectUIData* GetGameplayEffectUIData(TSubclassOf<UGameplayEffect> EffectClass, TSubclassOf<UGameplayEffectUIData> DataType);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect", Meta = (DisplayName = "Get GameplayEffect UI Data", DeterminesOutputType="DataType"))` — Returns the UI data for a gameplay effect class (if any)
- L573 _public prototype_ `static bool EqualEqual_ActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& A, const FActiveGameplayEffectHandle& B);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect", meta = (DisplayName = "Equal (Active Gameplay Effect Handle)", CompactNodeTitle = "==", ScriptOperator = "=="))` — Equality operator for two Active Gameplay Effect Handles
- L577 _public prototype_ `static bool NotEqual_ActiveGameplayEffectHandle(const FActiveGameplayEffectHandle& A, const FActiveGameplayEffectHandle& B);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect", meta = (DisplayName = "Not Equal (Active Gameplay Effect Handle)", CompactNodeTitle = "!=", ScriptOperator = "!="))` — Inequality operator for two Active Gameplay Effect Handles
- L585 _public prototype_ `static const UGameplayEffect* GetGameplayEffectFromActiveEffectHandle(const FActiveGameplayEffectHandle& ActiveHandle);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect")` — Returns the Gameplay Effect CDO from an active handle. This reference should be considered read only, but you can use it to read additional Gameplay Effect info, such as icon, description, etc.
- L593 _public prototype_ `static const FGameplayTagContainer& GetGameplayEffectAssetTags(TSubclassOf<UGameplayEffect> EffectClass);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect", meta = (DisplayName = "Get Asset Tags"))` — Returns all tags that the Gameplay Effect *has* (that denote the GE Asset itself) and *does not* grant to any Actor.
- L597 _public prototype_ `static const FGameplayTagContainer& GetGameplayEffectGrantedTags(TSubclassOf<UGameplayEffect> EffectClass);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayEffect", meta = (DisplayName = "Get Granted Tags"))` — Returns all tags that the Gameplay Effect grants to the target Actor
- L613 _public prototype_ `static const UGameplayAbility* GetGameplayAbilityFromSpecHandle(UAbilitySystemComponent* AbilitySystem, const FGameplayAbilitySpecHandle& AbilitySpecHandle, bool& bIsInstance);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayAbility")` — Provides the Gameplay Ability object associated with an Ability Spec Handle This can be either an instanced ability, or in the case of shared abilities, the Class Default Object @param AbilitySpec The Gameplay Ability Spec you want to get the object from @param bIsInstance Set to true if this is an instanced ability instead of a shared CDO @return Pointer to the Gameplay Ability object
- L617 _public prototype_ `static bool IsGameplayAbilityActive(const UGameplayAbility* GameplayAbility);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayAbility", meta=(DisplayName="Is Active",DefaultToSelf=GameplayAbility))` — Returns true if the passed-in Gameplay Ability instance is active (activated and not yet ended).
- L625 _public prototype_ `static bool HasAnyAbilitiesByPredicate( const UAbilitySystemComponent* AbilitySystemComponent, const TFunctionRef<bool(const UGameplayAbility& AbilityRef)> Predicate, bool bOnlyRunPredicateOnAbilityCDOs = false);` — Returns true if the ASC has any abilities that meet a given predicate. @param AbilitySystemComponent         The ability system component we are checking abilities on. @param Predicate                      The predicate to run on each ability @param bOnlyRunPredicateOnAbilityCDOs If true, we will only run the predicate on the ability specs' Ability CDO instead of on its instance(s). @return                               Returns true if any abilities passed the predicate.
- L632 _public prototype_ `static bool HasAnyAbilitiesWithAssetTag(const UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag AssetTag);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayAbility")` — Returns true if the ASC has any abilities that have a specific asset tag.
- L636 _public prototype_ `static bool EqualEqual_GameplayAbilitySpecHandle(const FGameplayAbilitySpecHandle& A, const FGameplayAbilitySpecHandle& B);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayAbility", meta = (DisplayName = "Equal (Gameplay Ability Spec Handle)", CompactNodeTitle = "==", ScriptOperator = "=="))` — Equality operator for two Gameplay Ability Spec Handles
- L640 _public prototype_ `static bool NotEqual_GameplayAbilitySpecHandle(const FGameplayAbilitySpecHandle& A, const FGameplayAbilitySpecHandle& B);` — `UFUNCTION(BlueprintPure, Category = "Ability|GameplayAbility", meta = (DisplayName = "Not Equal (Gameplay Ability Spec Handle)", CompactNodeTitle = "!=", ScriptOperator = "!="))` — Inequality operator for two Gameplay Ability Spec Handles
- L650 _public prototype_ `static float Conv_ScalableFloatToFloat(const FScalableFloat& Input, float Level = 0.0f);` — `UFUNCTION(BlueprintPure, Category="ScalableFloat", meta=(DisplayName="Get Value At Level (single-precision)", BlueprintAutocast, IgnoreTypePromotion))` — Converts the given Scalable float to the value at the given level. @param Input	The scalable float to get the value from @param Level The Level of which to get the value at @return The single-precision float value at the given level from the scalable float
- L660 _public prototype_ `static double Conv_ScalableFloatToDouble(const FScalableFloat& Input, float Level = 0.0f);` — `UFUNCTION(BlueprintPure, Category="ScalableFloat", meta=(DisplayName="Get Value At Level (double-precision)", BlueprintAutocast, IgnoreTypePromotion))` — Converts the given Scalable float to the value at the given level. @param Input	The scalable float to get the value from @param Level The Level of which to get the value at @return The double-precision float value at the given level from the scalable float

#### Free symbols / members of external scopes

- L20 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L27 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGameplayTagChangedEventWrapperSignature, const FGameplayTag&, Tag, int32, TagCount);` — Called when a gameplay tag bound to a event wrapper via one of the BindEventWrapper<to gameplay tag(s)> methods on the AbilitySystemLibrary changes.
- L27 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGameplayTagChangedEventWrapperSignature, const FGameplayTag&, Tag, int32, TagCount);` — Called when a gameplay tag bound to a event wrapper via one of the BindEventWrapper<to gameplay tag(s)> methods on the AbilitySystemLibrary changes.

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h` (Public)


#### enum `EGameplayEffectReplicationMode`  
`enum class EGameplayEffectReplicationMode : uint8`  
_L81-89_
- reflection: `UENUM()`
- desc: How gameplay effects will be replicated to clients
- L84 _public enumerator_ `Minimal` — Only replicate minimal gameplay effect info. Note: this does not work for Owned AbilitySystemComponents (Use Mixed instead).
- L86 _public enumerator_ `Mixed` — Only replicate minimal gameplay effect info to simulated proxies but full info to owners and autonomous proxies
- L88 _public enumerator_ `Full` — Replicate full gameplay info to all

#### enum `EConsiderPending`  
`enum class EConsiderPending : uint8`  
_L92-104_
- desc: When performing actions (such as gathering activatable abilities), how do we deal with Pending items (e.g. abilities not yet added or removed)
- L95 _public enumerator_ `None = 0` — Don't consider any Pending actions (such as Pending Abilities Added or Removed)
- L98 _public enumerator_ `PendingAdd = (1 << 0)` — Consider Pending Adds when performing the action
- L101 _public enumerator_ `PendingRemove = (1 << 1)` — Consider Pending Removes when performing the action
- L103 _public enumerator_ `All = PendingAdd | PendingRemove`

#### class `UAbilitySystemComponent`  
`class UAbilitySystemComponent : public UGameplayTasksComponent, public IGameplayTagAssetInterface, public IAbilitySystemReplicationProxyInterface`  
_L109-1989_
- reflection: `UCLASS(ClassGroup=AbilitySystem, hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent), MinimalAPI)`
- inherits: `UGameplayTasksComponent,IGameplayTagAssetInterface,IAbilitySystemReplicationProxyInterface`
- desc: The core ActorComponent for interfacing with the GameplayAbilities System
- L114 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityAbilityKey, int32, InputID);` — Used to register callbacks to ability-key input
- L117 _private prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityConfirmOrCancel);` — Used to register callbacks to confirm/cancel input
- L120 _private prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGameplayEffectAppliedDelegate, UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle);` — Delegate for when an effect is applied
- L128 _private function_ `template <class T > const T* GetSet() const` — Finds existing AttributeSet
- L135 _private function_ `template <class T > const T* GetSetChecked() const` — Finds existing AttributeSet. Asserts if it isn't there.
- L142 _private function_ `template <class T > static const T* GetSetOnActor(AActor* InActor)` — Finds existing AttributeSet for the given actor
- L154 _private function_ `template <class T > const T* AddSet()` — Adds a new AttributeSet (initialized to default values)
- L164 _private function_ `template <class T> const T* AddAttributeSetSubobject(T* Subobject)` — Manually add a new attribute set that is a subobject of this ability system component. All subobjects of this component are automatically added during initialization.
- L177 _private prototype_ `bool HasAttributeSetForAttribute(FGameplayAttribute Attribute) const;` — Does this ability system component have this attribute? @param Attribute	Handle of the gameplay effect to retrieve target tags from @return true if Attribute is valid and this ability system component contains an attribute set that contains Attribute. Returns false otherwise.
- L180 _private prototype_ `const UAttributeSet* InitStats(TSubclassOf<class UAttributeSet> Attributes, const UDataTable* DataTable);` — Initializes starting attributes from a data table. Not well supported, a gameplay effect with curve table references may be a better solution
- L183 _private prototype_ `void K2_InitStats(TSubclassOf<class UAttributeSet> Attributes, const UDataTable* DataTable);` — `UFUNCTION(BlueprintCallable, Category="Skills", meta=(DisplayName="InitStats", ScriptName="InitStats"))`
- L187 _private prototype_ `void GetAllAttributes(TArray<FGameplayAttribute>& OutAttributes);` — `UFUNCTION(BlueprintPure, Category="Gameplay Attributes")` — Returns a list of all attributes for this abilty system component
- L196 _private prototype_ `const UAttributeSet* GetAttributeSet(TSubclassOf<UAttributeSet> AttributeSetClass) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Gameplay Attributes", meta=(DeterminesOutputType = AttributeSetClass))` — Returns a reference to the Attribute Set instance, if one exists in this component @param AttributeSetClass The type of attribute set to look for @param bFound Set to true if an instance of the Attribute Set exists
- L206 _private prototype_ `float GetGameplayAttributeValue(FGameplayAttribute Attribute, bool& bFound) const;` — `UFUNCTION(BlueprintPure, Category = "Gameplay Attributes")` — Returns the current value of the given gameplay attribute, or zero if the attribute is not found. NOTE: This doesn't take predicted gameplay effect modifiers into consideration, so the value may not be accurate on clients at all times. @param Attribute The gameplay attribute to query @param bFound Set to true if the attribute exists in this component
- L209 _private member_ `TArray<FAttributeDefaults> DefaultStartingData;` — `UPROPERTY(EditAnywhere, Category="AttributeTest")`
- L212 _private prototype_ `void SetSpawnedAttributes(const TArray<UAttributeSet*>& NewAttributeSet);` — Remove all current AttributeSets and register the ones in the passed array. Note that it's better to call Add/Remove directly when possible.
- L215 _private prototype_ `const TArray<UAttributeSet*>& GetSpawnedAttributes() const;` — Access the spawned attributes list when you don't intend to modify the list.
- L218 _private prototype_ `void AddSpawnedAttribute(UAttributeSet* Attribute);` — Add a new attribute set
- L221 _private prototype_ `void RemoveSpawnedAttribute(UAttributeSet* Attribute);` — Remove an existing attribute set
- L224 _private prototype_ `void RemoveAllSpawnedAttributes();` — Remove all attribute sets
- L229 _private member_ `FName AffectedAnimInstanceTag;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Skills")` — The linked Anim Instance that this component will play montages in. Use NAME_None for the main anim instance.
- L233 _private prototype_ `void SetNumericAttributeBase(const FGameplayAttribute &Attribute, float NewBaseValue);` — Sets the base value of an attribute. Existing active modifiers are NOT cleared and will act upon the new base value.
- L236 _private prototype_ `float GetNumericAttributeBase(const FGameplayAttribute &Attribute) const;` — Gets the base value of an attribute. That is, the value of the attribute with no stateful modifiers
- L245 _private prototype_ `void ApplyModToAttribute(const FGameplayAttribute &Attribute, TEnumAsByte<EGameplayModOp::Type> ModifierOp, float ModifierMagnitude);` — Applies an in-place mod to the given attribute. This correctly update the attribute's aggregator, updates the attribute set property, and invokes the OnDirty callbacks. This does not invoke Pre/PostGameplayEffectExecute calls on the attribute set. This does no tag checking, application requirements, immunity, etc. No GameplayEffectSpec is created or is applied! This should only be used in cases where applying a real GameplayEffectSpec is too slow or not possible.
- L251 _private prototype_ `void ApplyModToAttributeUnsafe(const FGameplayAttribute &Attribute, TEnumAsByte<EGameplayModOp::Type> ModifierOp, float ModifierMagnitude);` — Applies an inplace mod to the given attribute. Unlike ApplyModToAttribute this function will run on the client or server. This may result in problems related to prediction and will not roll back properly.
- L254 _private prototype_ `float GetNumericAttribute(const FGameplayAttribute &Attribute) const;` — Returns current (final) value of an attribute
- L255 _private prototype_ `float GetNumericAttributeChecked(const FGameplayAttribute &Attribute) const;`
- L258 _private prototype_ `float GetFilteredAttributeValue(const FGameplayAttribute& Attribute, const FGameplayTagRequirements& SourceTags, const FGameplayTagContainer& TargetTags, const TArray<FActiveGameplayEffectHandle>& HandlesToIgnore = TArray<FActiveGameplayEffectHandle>());` — Returns an attribute value, after applying tag filters
- L265 _private prototype_ `virtual void ForceAvatarReplication();` — Forces avatar actor to update it's replication. Useful for things like needing to replication for movement / locations reasons.
- L268 _private prototype_ `virtual void SetReplicationMode(EGameplayEffectReplicationMode NewReplicationMode);` — When true, we will not replicate active gameplay effects for this ability system component, so attributes and tags
- L271 _private member_ `EGameplayEffectReplicationMode ReplicationMode;` — How gameplay effects are replicated
- L274 _private prototype_ `virtual IAbilitySystemReplicationProxyInterface* GetReplicationInterface();` — Who to route replication through if ReplicationProxyEnabled (if this returns null, when ReplicationProxyEnabled, we wont replicate)
- L277 _private member_ `FPredictionKey ScopedPredictionKey;` — Current prediction key, set with FScopedPredictionWindow
- L280 _private function_ `FPredictionKey GetPredictionKeyForNewAction() const` — Returns the prediction key that should be used for any actions
- L286 _private function_ `bool CanPredict() const` — Do we have a valid prediction key to do more predictive actions with
- L292 _private prototype_ `bool HasAuthorityOrPredictionKey(const FGameplayAbilityActivationInfo* ActivationInfo) const;` — Returns true if this is running on the server or has a valid prediction key
- L295 _private prototype_ `virtual bool IsOwnerActorAuthoritative() const;` — Returns true if this component's actor has authority
- L298 _private prototype_ `virtual bool ShouldRecordMontageReplication() const;` — Returns true if this component should record montage replication info.
- L301 _private prototype_ `virtual void ReplicateEndOrCancelAbility(FGameplayAbilitySpecHandle Handle, FGameplayAbilityActivationInfo ActivationInfo, UGameplayAbility* Ability, bool bWasCanceled);` — Replicate that an ability has ended/canceled, to the client or server as appropriate
- L304 _private prototype_ `virtual void ForceCancelAbilityDueToReplication(UGameplayAbility* Instance);` — Force cancels the ability and does not replicate this to the other side. This should be called when the ability is cancelled by the other side
- L329 _private member_ `TArray<FPendingAbilityInfo> PendingServerActivatedAbilities;` — This is a list of GameplayAbilities that were activated on the server and can't yet execute on the client. It will try to execute these at a later point
- L337 _private prototype_ `FActiveGameplayEffectHandle BP_ApplyGameplayEffectSpecToTarget(const FGameplayEffectSpecHandle& SpecHandle, UAbilitySystemComponent* Target);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects, meta = (DisplayName = "ApplyGameplayEffectSpecToTarget", ScriptName = "ApplyGameplayEffectSpecToTarget"))` — Applies a previously created gameplay effect spec to a target
- L339 _private prototype_ `virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToTarget(const FGameplayEffectSpec& GameplayEffect, UAbilitySystemComponent *Target, FPredictionKey PredictionKey=FPredictionKey());`
- L343 _private prototype_ `FActiveGameplayEffectHandle BP_ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpecHandle& SpecHandle);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects, meta = (DisplayName = "ApplyGameplayEffectSpecToSelf", ScriptName = "ApplyGameplayEffectSpecToSelf"))` — Applies a previously created gameplay effect spec to this component
- L345 _private prototype_ `virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey = FPredictionKey());`
- L348 _private prototype_ `const UGameplayEffect* GetGameplayEffectDefForHandle(FActiveGameplayEffectHandle Handle);` — Gets the FActiveGameplayEffect based on the passed in Handle
- L358 _private prototype_ `virtual bool RemoveActiveGameplayEffect(FActiveGameplayEffectHandle Handle, int32 StacksToRemove=-1);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = GameplayEffects)` — Removes the specified GameplayEffect by Handle. @param Handle								The handle of the gameplay effect to remove @param StacksToRemove						Number of stacks to remove, -1 means remove all @return Whether the effect was successfully removed.
- L368 _private prototype_ `virtual void RemoveActiveGameplayEffectBySourceEffect(TSubclassOf<UGameplayEffect> GameplayEffect, UAbilitySystemComponent* InstigatorAbilitySystemComponent, int32 StacksToRemove = -1);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = GameplayEffects)` — Remove active gameplay effects whose backing definition are the specified gameplay effect class @param GameplayEffect					Class of gameplay effect to remove; Does nothing if left null @param InstigatorAbilitySystemComponent	If specified, will only remove gameplay effects applied from this instigator ability system component @param StacksToRemove					Number of stacks to remove, -1 means remove all
- L372 _private prototype_ `virtual FGameplayEffectSpecHandle MakeOutgoingSpec(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle Context) const;` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects)` — Get an outgoing GameplayEffectSpec that is ready to be applied to other things.
- L376 _private prototype_ `virtual FGameplayEffectContextHandle MakeEffectContext() const;` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects)` — Create an EffectContext for the owner of this AbilitySystemComponent
- L388 _private prototype_ `int32 GetGameplayEffectCount(TSubclassOf<UGameplayEffect> SourceGameplayEffect, UAbilitySystemComponent* OptionalInstigatorFilterComponent, bool bEnforceOnGoingCheck = true) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category=GameplayEffects)` — Get the count of the specified source effect on the ability system component. For non-stacking effects, this is the sum of all active instances. For stacking effects, this is the sum of all valid stack counts. If an instigator is specified, only effects from that instigator are counted. @param SourceGameplayEffect					Effect to get the count of @param OptionalInstigatorFilterComponent		If specified, only count effects applied by this ability system component @return Count of the specified source effect
- L400 _private prototype_ `int32 GetGameplayEffectCount_IfLoaded(TSoftClassPtr<UGameplayEffect> SoftSourceGameplayEffect, UAbilitySystemComponent* OptionalInstigatorFilterComponent, bool bEnforceOnGoingCheck = true) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure, Category = GameplayEffects)` — Get the count of the specified source effect on the ability system component. For non-stacking effects, this is the sum of all active instances. For stacking effects, this is the sum of all valid stack counts. If an instigator is specified, only effects from that instigator are counted. @param SoftSourceGameplayEffect				Effect to get the count of. If this is not currently loaded, the count is 0 @param OptionalInstigatorFilterComponent		If specified, only count effects applied by this ability system component @return Count of the specified source effect
- L403 _private prototype_ `int32 GetAggregatedStackCount(const FGameplayEffectQuery& Query) const;` — Returns the sum of StackCount of all gameplay effects that pass query
- L407 _private prototype_ `void RemoveActiveGameplayEffect_NoReturn(FActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);` — `UE_DEPRECATED_FORGAME(5.5, "This shouldn't be public. Use RemoveActiveGameplayEffect (which won't allow non-authority to remove) or expose RemoveActiveGameplayEffect_AllowClientRemoval if your intent is to break that contract.")` — This only exists so it can be hooked up to a multicast delegate
- L410 _private prototype_ `virtual void OnPredictiveGameplayCueCatchup(FGameplayTag Tag);` — Called for predictively added gameplay cue. Needs to remove tag count and possible invoke OnRemove event if misprediction
- L413 _private prototype_ `float GetGameplayEffectDuration(FActiveGameplayEffectHandle Handle) const;` — Returns the total duration of a gameplay effect
- L416 _private prototype_ `virtual void RecomputeGameplayEffectStartTimes(const float WorldTime, const float ServerWorldTime);` — Called whenever the server time replicates via the game state to keep our cooldown timers in sync with the server
- L419 _private prototype_ `void GetGameplayEffectStartTimeAndDuration(FActiveGameplayEffectHandle Handle, float& StartEffectTime, float& Duration) const;` — Return start time and total duration of a gameplay effect
- L423 _private prototype_ `virtual void UpdateActiveGameplayEffectSetByCallerMagnitude(FActiveGameplayEffectHandle ActiveHandle, UPARAM(meta=(Categories = "SetByCaller"))FGameplayTag SetByCallerTag, float` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = GameplayEffects)` — Dynamically update the set-by-caller magnitude for an active gameplay effect
- L427 _private prototype_ `virtual void UpdateActiveGameplayEffectSetByCallerMagnitudes(FActiveGameplayEffectHandle ActiveHandle, const TMap<FGameplayTag, float>& NewSetByCallerValues);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = GameplayEffects)` — Dynamically update multiple set-by-caller magnitudes for an active gameplay effect
- L431 _private prototype_ `virtual void SetActiveGameplayEffectLevel(FActiveGameplayEffectHandle ActiveHandle, int32 NewLevel);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = GameplayEffects)` — Updates the level of an already applied gameplay effect. The intention is that this is 'seemless' and doesnt behave like removing/reapplying
- L435 _private prototype_ `virtual void SetActiveGameplayEffectLevelUsingQuery(FGameplayEffectQuery Query, int32 NewLevel);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = GameplayEffects)` — Updates the level of an already applied gameplay effect. The intention is that this is 'seemless' and doesnt behave like removing/reapplying
- L442 _private prototype_ `virtual FActiveGameplayEffectHandle SetActiveGameplayEffectInhibit(FActiveGameplayEffectHandle&& ActiveGEHandle, bool bInhibit, bool bInvokePredictedEffects);` — (Un-)Inhibit an Active Gameplay Effect so it may be disabled (and perform some disabling actions, such as removing tags). An inhibited Active Gameplay Effect will lay dormant for re-enabling on some condition (usually tags).  When it's uninhibited, it will reapply some of its functionality. NOTE:  The passed-in ActiveGEHandle is no longer valid.  Use the returned FActiveGameplayEffectHandle to determine if the Active GE Handle is still active.
- L449 _private prototype_ `float GetGameplayEffectMagnitude(FActiveGameplayEffectHandle Handle, FGameplayAttribute Attribute) const;` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects)` — Raw accessor to ask the magnitude of a gameplay effect, not necessarily always correct. How should outside code (UI, etc) ask things like 'how much is this gameplay effect modifying my damage by' (most likely we want to catch this on the backend - when damage is applied we can get a full dump/history of how the number got to where it is. But still we may need polling methods like below (how much would my damage be)
- L452 _private prototype_ `int32 GetCurrentStackCount(FActiveGameplayEffectHandle Handle) const;` — Returns current stack count of an already applied GE
- L455 _private prototype_ `int32 GetCurrentStackCount(FGameplayAbilitySpecHandle Handle) const;` — Returns current stack count of an already applied GE, but given the ability spec handle that was granted by the GE
- L458 _private prototype_ `FString GetActiveGEDebugString(FActiveGameplayEffectHandle Handle) const;` — Returns debug string describing active gameplay effect
- L461 _private prototype_ `FActiveGameplayEffectHandle FindActiveGameplayEffectHandle(FGameplayAbilitySpecHandle Handle) const;` — Gets the GE Handle of the GE that granted the passed in Ability
- L464 _private prototype_ `const FActiveGameplayEffect* GetActiveGameplayEffect(const FActiveGameplayEffectHandle Handle) const;` — Returns const pointer to the actual active gameplay effect structure
- L467 _private prototype_ `const FActiveGameplayEffectsContainer& GetActiveGameplayEffects() const;` — Returns all active gameplay effects on this ASC
- L470 _private prototype_ `const UGameplayEffect* GetGameplayEffectCDO(const FActiveGameplayEffectHandle Handle) const;` — Returns a const pointer to the gameplay effect CDO associated with an active handle.
- L479 _private prototype_ `const FGameplayTagContainer* GetGameplayEffectSourceTagsFromHandle(FActiveGameplayEffectHandle Handle) const;` — Get the source tags from the gameplay spec represented by the specified handle, if possible @param Handle	Handle of the gameplay effect to retrieve source tags from @return Source tags from the gameplay spec represented by the handle, if possible
- L488 _private prototype_ `const FGameplayTagContainer* GetGameplayEffectTargetTagsFromHandle(FActiveGameplayEffectHandle Handle) const;` — Get the target tags from the gameplay spec represented by the specified handle, if possible @param Handle	Handle of the gameplay effect to retrieve target tags from @return Target tags from the gameplay spec represented by the handle, if possible
- L495 _private prototype_ `void CaptureAttributeForGameplayEffect(OUT FGameplayEffectAttributeCaptureSpec& OutCaptureSpec);` — Populate the specified capture spec with the data necessary to capture an attribute from the component @param OutCaptureSpec	[OUT] Capture spec to populate with captured data
- L503 _private prototype_ `void OnAttributeAggregatorDirty(FAggregator* Aggregator, FGameplayAttribute Attribute, bool FromRecursiveCall=false);` — Called when a specific attribute aggregator value changes, gameplay effects refresh their values when this happens
- L506 _private prototype_ `void OnMagnitudeDependencyChange(FActiveGameplayEffectHandle Handle, const FAggregator* ChangedAggregator);` — Called when attribute magnitudes change, to forward information to dependent gameplay effects
- L509 _private prototype_ `void OnGameplayEffectAppliedToTarget(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);` — This ASC has successfully applied a GE to something (potentially itself)
- L510 _private prototype_ `void OnGameplayEffectAppliedToSelf(UAbilitySystemComponent* Source, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveHandle);`
- L511 _private prototype_ `void OnPeriodicGameplayEffectExecuteOnTarget(UAbilitySystemComponent* Target, const FGameplayEffectSpec& SpecExecuted, FActiveGameplayEffectHandle ActiveHandle);`
- L512 _private prototype_ `void OnPeriodicGameplayEffectExecuteOnSelf(UAbilitySystemComponent* Source, const FGameplayEffectSpec& SpecExecuted, FActiveGameplayEffectHandle ActiveHandle);`
- L515 _private prototype_ `virtual void OnGameplayEffectDurationChange(struct FActiveGameplayEffect& ActiveEffect);` — Called when the duration of a gameplay effect has changed
- L518 _private member_ `FOnGameplayEffectAppliedDelegate OnGameplayEffectAppliedDelegateToSelf;` — Called on server whenever a GE is applied to self. This includes instant and duration based GEs.
- L521 _private member_ `FOnGameplayEffectAppliedDelegate OnGameplayEffectAppliedDelegateToTarget;` — Called on server whenever a GE is applied to someone else. This includes instant and duration based GEs.
- L524 _private member_ `FOnGameplayEffectAppliedDelegate OnActiveGameplayEffectAddedDelegateToSelf;` — Called on both client and server whenever a duration based GE is added (E.g., instant GEs do not trigger this).
- L527 _private member_ `FOnGameplayEffectAppliedDelegate OnPeriodicGameplayEffectExecuteDelegateOnSelf;` — Called on server whenever a periodic GE executes on self
- L530 _private member_ `FOnGameplayEffectAppliedDelegate OnPeriodicGameplayEffectExecuteDelegateOnTarget;` — Called on server whenever a periodic GE executes on target
- L533 _private member_ `FImmunityBlockGE OnImmunityBlockGameplayEffectDelegate;` — Immunity notification support
- L536 _private prototype_ `FOnGameplayAttributeChange& RegisterGameplayAttributeEvent(FGameplayAttribute Attribute);` — Register for when an attribute value changes, should be replaced by GetGameplayAttributeValueChangeDelegate
- L539 _private prototype_ `FOnGameplayAttributeValueChange& GetGameplayAttributeValueChangeDelegate(FGameplayAttribute Attribute);` — Register for when an attribute value changes
- L542 _private member_ `FGenericAbilityDelegate AbilityActivatedCallbacks;` — A generic callback anytime an ability is activated (started)
- L545 _private member_ `FAbilityEnded AbilityEndedCallbacks;` — Callback anytime an ability is ended
- L548 _private member_ `FGameplayAbilityEndedDelegate OnAbilityEnded;` — Callback anytime an ability is ended, with extra information
- L551 _private member_ `FGenericAbilityDelegate AbilityCommittedCallbacks;` — A generic callback anytime an ability is committed (cost/cooldown applied)
- L554 _private member_ `FAbilityFailedDelegate AbilityFailedCallbacks;` — Called with a failure reason when an ability fails to activate
- L557 _private member_ `FAbilitySpecDirtied AbilitySpecDirtiedCallbacks;` — Called when an ability spec's internals have changed
- L560 _private member_ `TArray<FGameplayEffectApplicationQuery> GameplayEffectApplicationQueries;` — We allow users to setup a series of functions that must be true in order to allow a GameplayEffect to be applied
- L563 _private prototype_ `virtual void NotifyAbilityCommit(UGameplayAbility* Ability);` — Call notify callbacks above
- L564 _private prototype_ `virtual void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability);`
- L565 _private prototype_ `virtual void NotifyAbilityFailed(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason);`
- L568 _private prototype_ `FOnGivenActiveGameplayEffectRemoved& OnAnyGameplayEffectRemovedDelegate();` — Called when any gameplay effects are removed
- L571 _private prototype_ `FActiveGameplayEffectEvents* GetActiveEffectEventSet(FActiveGameplayEffectHandle Handle);` — Returns delegate structure that allows binding to several gameplay effect changes
- L572 _private prototype_ `FOnActiveGameplayEffectRemoved_Info* OnGameplayEffectRemoved_InfoDelegate(FActiveGameplayEffectHandle Handle);`
- L573 _private prototype_ `FOnActiveGameplayEffectStackChange* OnGameplayEffectStackChangeDelegate(FActiveGameplayEffectHandle Handle);`
- L574 _private prototype_ `FOnActiveGameplayEffectTimeChange* OnGameplayEffectTimeChangeDelegate(FActiveGameplayEffectHandle Handle);`
- L575 _private prototype_ `FOnActiveGameplayEffectInhibitionChanged* OnGameplayEffectInhibitionChangedDelegate(FActiveGameplayEffectHandle Handle);`
- L581 _private function_ `inline bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override`
- L586 _private function_ `inline bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override`
- L591 _private function_ `inline bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override`
- L596 _private function_ `inline void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override`
- L602 _private function_ `[[nodiscard]] inline const FGameplayTagContainer& GetOwnedGameplayTags() const`
- L608 _private function_ `inline bool MatchesGameplayTagQuery(const FGameplayTagQuery& TagQuery) const` — Checks whether the query matches the owned GameplayTags
- L614 _private function_ `inline int32 GetTagCount(FGameplayTag TagToCheck) const` — Returns the number of instances of a given tag
- L620 _private function_ `inline void SetTagMapCount(const FGameplayTag& Tag, int32 NewCount, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None)` — Forcibly sets the number of instances of a given tag
- L627 _private function_ `inline void UpdateTagMap(const FGameplayTag& BaseTag, int32 CountDelta, EGameplayTagReplicationState TagRepState)` — Update the number of instances of a given tag and calls callback
- L633 _private function_ `inline void UpdateTagMap(const FGameplayTagContainer& Container, int32 CountDelta, EGameplayTagReplicationState TagRepState)` — Update the number of instances of a given tag and calls callback
- L642 _private function_ `inline void GetBlockedAbilityTags(FGameplayTagContainer& TagContainer) const` — Fills TagContainer with BlockedAbilityTags
- L647 _private function_ `[[nodiscard]] inline const FGameplayTagContainer GetBlockedAbilityTags() const`
- L656 _private function_ `inline void AddLooseGameplayTag(const FGameplayTag& GameplayTag, int32 Count=1, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None)` — Allows GameCode to add loose gameplaytags which are not backed by a GameplayEffect. It is up to the calling GameCode to make sure these tags are added on clients/server where necessary
- L661 _private function_ `inline void AddLooseGameplayTags(const FGameplayTagContainer& GameplayTags, int32 Count = 1, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None)`
- L666 _private function_ `inline void RemoveLooseGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None)`
- L671 _private function_ `inline void RemoveLooseGameplayTags(const FGameplayTagContainer& GameplayTags, int32 Count = 1, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None)`
- L676 _private function_ `inline void SetLooseGameplayTagCount(const FGameplayTag& GameplayTag, int32 NewCount, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None)`
- L689 _private prototype_ `int32 GetGameplayTagCount(FGameplayTag GameplayTag) const;` — `UFUNCTION(BlueprintPure, Category = "Gameplay Tags")` — Returns the current count of the given gameplay tag. This includes both loose tags, and tags granted by gameplay effects and abilities. This function can be called on the client, but it may not display the most current count on the server. @param GameplayTag The gameplay tag to query
- L695 _private function_ `inline void AddMinimalReplicationGameplayTag(const FGameplayTag& GameplayTag)` — Minimally replicated tags are replicated tags that come from GEs when in bMinimalReplication mode. (The GEs do not replicate, but the tags they grant do replicate via these functions)
- L701 _private function_ `inline void AddMinimalReplicationGameplayTags(const FGameplayTagContainer& GameplayTags)`
- L707 _private function_ `inline void RemoveMinimalReplicationGameplayTag(const FGameplayTag& GameplayTag)`
- L713 _private function_ `inline void RemoveMinimalReplicationGameplayTags(const FGameplayTagContainer& GameplayTags)`
- L720 _private prototype_ `FOnGameplayEffectTagCountChanged& RegisterGameplayTagEvent(FGameplayTag Tag, EGameplayTagEventType::Type EventType=EGameplayTagEventType::NewOrRemoved);` — Allow events to be registered for specific gameplay tags being added or removed
- L723 _private prototype_ `bool UnregisterGameplayTagEvent(FDelegateHandle DelegateHandle, FGameplayTag Tag, EGameplayTagEventType::Type EventType=EGameplayTagEventType::NewOrRemoved);` — Unregister previously added events
- L726 _private prototype_ `FDelegateHandle RegisterAndCallGameplayTagEvent(FGameplayTag Tag, FOnGameplayEffectTagCountChanged::FDelegate Delegate, EGameplayTagEventType::Type EventType=EGameplayTagEventType::NewOrRemoved);` — Register a tag event and immediately call it
- L729 _private prototype_ `FOnGameplayEffectTagCountChanged& RegisterGenericGameplayTagEvent();` — Returns multicast delegate that is invoked whenever a tag is added or removed (but not if just count is increased. Only for 'new' and 'removed' events)
- L732 _private prototype_ `virtual int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);` — Executes a gameplay event. Returns the number of successful ability activations triggered by the event
- L735 _private prototype_ `FDelegateHandle AddGameplayEventTagContainerDelegate(const FGameplayTagContainer& TagFilter, const FGameplayEventTagMulticastDelegate::FDelegate& Delegate);` — Adds a new delegate to call when gameplay events happen. It will only be called if it matches any tags in passed filter container
- L738 _private prototype_ `void RemoveGameplayEventTagContainerDelegate(const FGameplayTagContainer& TagFilter, FDelegateHandle DelegateHandle);` — Remotes previously registered delegate
- L741 _private member_ `TMap<FGameplayTag, FGameplayEventMulticastDelegate> GenericGameplayEventCallbacks;` — Callbacks bound to Gameplay tags, these only activate if the exact tag is used. To handle tag hierarchies use AddGameplayEventContainerDelegate
- L749 _private member_ `float OutgoingDuration;` — `UPROPERTY(meta=(SystemGameplayAttribute="true"))` — Internal Attribute that modifies the duration of gameplay effects created by this component
- L753 _private member_ `float IncomingDuration;` — `UPROPERTY(meta = (SystemGameplayAttribute = "true"))` — Internal Attribute that modifies the duration of gameplay effects applied to this component
- L755 _private prototype_ `static FProperty* GetOutgoingDurationProperty();`
- L756 _private prototype_ `static FProperty* GetIncomingDurationProperty();`
- L758 _private prototype_ `static const FGameplayEffectAttributeCaptureDefinition& GetOutgoingDurationCapture();`
- L759 _private prototype_ `static const FGameplayEffectAttributeCaptureDefinition& GetIncomingDurationCapture();`
- L767 _private prototype_ `FActiveGameplayEffectHandle BP_ApplyGameplayEffectToTarget(TSubclassOf<UGameplayEffect> GameplayEffectClass, UAbilitySystemComponent *Target, float Level, FGameplayEffectContextHandle Context);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects, meta=(DisplayName = "ApplyGameplayEffectToTarget", ScriptName = "ApplyGameplayEffectToTarget"))` — Apply a gameplay effect to passed in target
- L768 _private prototype_ `FActiveGameplayEffectHandle ApplyGameplayEffectToTarget(UGameplayEffect *GameplayEffect, UAbilitySystemComponent *Target, float Level = UGameplayEffect::INVALID_LEVEL, FGameplayEffectContextHandle Context = FGameplayEffectContextHandle(), FPredictionKey PredictionKey = FPredictionKey());`
- L772 _private prototype_ `FActiveGameplayEffectHandle BP_ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle EffectContext);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects, meta=(DisplayName = "ApplyGameplayEffectToSelf", ScriptName = "ApplyGameplayEffectToSelf"))` — Apply a gameplay effect to self
- L773 _private prototype_ `FActiveGameplayEffectHandle ApplyGameplayEffectToSelf(const UGameplayEffect *GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext, FPredictionKey PredictionKey = FPredictionKey());`
- L776 _private function_ `int32 GetNumActiveGameplayEffects() const` — Returns the number of gameplay effects that are currently active on this ability system component
- L782 _private function_ `void GetAllActiveGameplayEffectSpecs(TArray<FGameplayEffectSpec>& OutSpecCopies) const` — Makes a copy of all the active effects on this ability component
- L788 _private function_ `void SetBaseAttributeValueFromReplication(const FGameplayAttribute& Attribute, float NewValue, float OldValue)` — Call from OnRep functions to set the attribute base value on the client
- L794 _private function_ `void SetBaseAttributeValueFromReplication(const FGameplayAttribute& Attribute, const FGameplayAttributeData& NewValue, const FGameplayAttributeData& OldValue)` — Call from OnRep functions to set the attribute base value on the client
- L800 _private function_ `bool CanApplyAttributeModifiers(const UGameplayEffect *GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext)` — Tests if all modifiers in this GameplayEffect will leave the attribute > 0.f
- L806 _private prototype_ `TArray<float> GetActiveEffectsTimeRemaining(const FGameplayEffectQuery& Query) const;` — Gets time remaining for all effects that match query
- L809 _private prototype_ `TArray<float> GetActiveEffectsDuration(const FGameplayEffectQuery& Query) const;` — Gets total duration for all effects that match query
- L812 _private prototype_ `TArray<TPair<float,float>> GetActiveEffectsTimeRemainingAndDuration(const FGameplayEffectQuery& Query) const;` — Gets both time remaining and total duration  for all effects that match query
- L816 _private prototype_ `TArray<FActiveGameplayEffectHandle> GetActiveEffects(const FGameplayEffectQuery& Query) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category = "GameplayEffects", meta=(DisplayName = "Get Active Gameplay Effects for Query"))` — Returns list of active effects, for a query
- L820 _private prototype_ `TArray<FActiveGameplayEffectHandle> GetActiveEffectsWithAllTags(FGameplayTagContainer Tags) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "GameplayEffects")` — Returns list of active effects that have all of the passed in tags
- L823 _private prototype_ `float GetActiveEffectsEndTime(const FGameplayEffectQuery& Query) const;` — This will give the world time that all effects matching this query will be finished. If multiple effects match, it returns the one that returns last
- L824 _private prototype_ `float GetActiveEffectsEndTimeWithInstigators(const FGameplayEffectQuery& Query, TArray<AActor*>& Instigators) const;`
- L827 _private prototype_ `bool GetActiveEffectsEndTimeAndDuration(const FGameplayEffectQuery& Query, float& EndTime, float& Duration) const;` — Returns end time and total duration
- L830 _private prototype_ `virtual void ModifyActiveEffectStartTime(FActiveGameplayEffectHandle Handle, float StartTimeDiff);` — Modify the start time of a gameplay effect, to deal with timers being out of sync originally
- L834 _private prototype_ `int32 RemoveActiveEffectsWithTags(FGameplayTagContainer Tags);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects)` — Removes all active effects that contain any of the tags in Tags
- L838 _private prototype_ `int32 RemoveActiveEffectsWithSourceTags(FGameplayTagContainer Tags);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects)` — Removes all active effects with captured source tags that contain any of the tags in Tags
- L842 _private prototype_ `int32 RemoveActiveEffectsWithAppliedTags(FGameplayTagContainer Tags);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects)` — Removes all active effects that apply any of the tags in Tags
- L846 _private prototype_ `int32 RemoveActiveEffectsWithGrantedTags(FGameplayTagContainer Tags);` — `UFUNCTION(BlueprintCallable, Category = GameplayEffects)` — Removes all active effects that grant any of the tags in Tags
- L849 _private prototype_ `virtual int32 RemoveActiveEffects(const FGameplayEffectQuery& Query, int32 StacksToRemove = -1);` — Removes all active effects that match given query. StacksToRemove=-1 will remove all stacks.
- L857 _private prototype_ `void NetMulticast_InvokeGameplayCueExecuted_FromSpec(const FGameplayEffectSpecForRPC Spec, FPredictionKey PredictionKey) override;` — `UFUNCTION(NetMulticast, unreliable)` — Do not call these functions directly, call the wrappers on GameplayCueManager instead
- L860 _private prototype_ `void NetMulticast_InvokeGameplayCueExecuted(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L863 _private prototype_ `void NetMulticast_InvokeGameplayCuesExecuted(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L866 _private prototype_ `void NetMulticast_InvokeGameplayCueExecuted_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L869 _private prototype_ `void NetMulticast_InvokeGameplayCuesExecuted_WithParams(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L872 _private prototype_ `void NetMulticast_InvokeGameplayCueAdded(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L875 _private prototype_ `void NetMulticast_InvokeGameplayCueAdded_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters Parameters) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L878 _private prototype_ `void NetMulticast_InvokeGameplayCueAddedAndWhileActive_FromSpec(const FGameplayEffectSpecForRPC& Spec, FPredictionKey PredictionKey) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L881 _private prototype_ `void NetMulticast_InvokeGameplayCueAddedAndWhileActive_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L884 _private prototype_ `void NetMulticast_InvokeGameplayCuesAddedAndWhileActive_WithParams(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) override;` — `UFUNCTION(NetMulticast, unreliable)`
- L887 _private prototype_ `void ExecuteGameplayCue(const FGameplayTag GameplayCueTag, FGameplayEffectContextHandle EffectContext = FGameplayEffectContextHandle());` — GameplayCues can also come on their own. These take an optional effect context to pass through hit result, etc
- L888 _private prototype_ `void ExecuteGameplayCue(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);`
- L891 _private prototype_ `void AddGameplayCue(const FGameplayTag GameplayCueTag, FGameplayEffectContextHandle EffectContext = FGameplayEffectContextHandle());` — Add a persistent gameplay cue
- L892 _private prototype_ `void AddGameplayCue(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);`
- L895 _private prototype_ `void AddGameplayCue_MinimalReplication(const FGameplayTag GameplayCueTag, FGameplayEffectContextHandle EffectContext = FGameplayEffectContextHandle());` — Add gameplaycue for minimal replication mode. Should only be called in paths that would replicate gameplaycues in other ways (through GE for example) if not in minimal replication mode
- L898 _private prototype_ `void RemoveGameplayCue(const FGameplayTag GameplayCueTag);` — Remove a persistent gameplay cue
- L901 _private prototype_ `void RemoveGameplayCue_MinimalReplication(const FGameplayTag GameplayCueTag);` — Remove gameplaycue for minimal replication mode. Should only be called in paths that would replicate gameplaycues in other ways (through GE for example) if not in minimal replication mode
- L904 _private prototype_ `void RemoveAllGameplayCues();` — Removes any GameplayCue added on its own, i.e. not as part of a GameplayEffect.
- L907 _private prototype_ `void InvokeGameplayCueEvent(const FGameplayEffectSpecForRPC& Spec, EGameplayCueEvent::Type EventType);` — Handles gameplay cue events from external sources
- L908 _private prototype_ `void InvokeGameplayCueEvent(const FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, FGameplayEffectContextHandle EffectContext = FGameplayEffectContextHandle());`
- L909 _private prototype_ `void InvokeGameplayCueEvent(const FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& GameplayCueParameters);`
- L913 _private function_ `bool IsGameplayCueActive(const FGameplayTag GameplayCueTag) const` — `UFUNCTION(BlueprintCallable, Category="GameplayCue", meta=(GameplayTagFilter="GameplayCue"))` — Allows polling to see if a GameplayCue is active. We expect most GameplayCue handling to be event based, but some cases we may need to check if a GameplayCue is active (Animation Blueprint for example)
- L919 _private prototype_ `virtual void InitDefaultGameplayCueParameters(FGameplayCueParameters& Parameters);` — Will initialize gameplay cue parameters with this ASC's Owner (Instigator) and AvatarActor (EffectCauser)
- L922 _private prototype_ `virtual bool IsReadyForGameplayCues();` — Are we ready to invoke gameplaycues yet?
- L925 _private prototype_ `virtual void HandleDeferredGameplayCues(const FActiveGameplayEffectsContainer* GameplayEffectsContainer);` — Handle GameplayCues that may have been deferred while doing the NetDeltaSerialize and waiting for the avatar actor to get loaded
- L949 _private prototype_ `FGameplayAbilitySpecHandle GiveAbility(const FGameplayAbilitySpec& AbilitySpec);` — Grants an Ability. This will be ignored if the actor is not authoritative. Returns handle that can be used in TryActivateAbility, etc. @param AbilitySpec FGameplayAbilitySpec containing information about the ability class, level and input ID to bind it to.
- L958 _private prototype_ `FGameplayAbilitySpecHandle GiveAbilityAndActivateOnce(FGameplayAbilitySpec& AbilitySpec, const FGameplayEventData* GameplayEventData = nullptr);` — Grants an ability and attempts to activate it exactly one time, which will cause it to be removed. Only valid on the server, and the ability's Net Execution Policy cannot be set to Local or Local Predicted @param AbilitySpec FGameplayAbilitySpec containing information about the ability class, level and input ID to bind it to. @param GameplayEventData Optional activation event data. If provided, Activate Ability From Event will be called instead of ActivateAbility, passing the Event Data
- L969 _private prototype_ `FGameplayAbilitySpecHandle K2_GiveAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 0, int32 InputID = -1);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Gameplay Abilities", meta = (DisplayName = "Give Ability", ScriptName = "GiveAbility"))` — Grants a Gameplay Ability and returns its handle. This will be ignored if the actor is not authoritative. @param AbilityClass Type of ability to grant @param Level Level to grant the ability at @param InputID Input ID value to bind ability activation to.
- L980 _private prototype_ `FGameplayAbilitySpecHandle K2_GiveAbilityAndActivateOnce(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 0, int32 InputID = -1);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Gameplay Abilities", meta = (DisplayName = "Give Ability And Activate Once", ScriptName = "GiveAbilityAndActivateOnce"))` — Grants a Gameplay Ability, activates it once, and removes it. This will be ignored if the actor is not authoritative. @param AbilityClass Type of ability to grant @param Level Level to grant the ability at @param InputID Input ID value to bind ability activation to.
- L984 _private prototype_ `void ClearAllAbilities();` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Gameplay Abilities")` — Wipes all 'given' abilities. This will be ignored if the actor is not authoritative.
- L993 _private prototype_ `void ClearAllAbilitiesWithInputID(int32 InputID = 0);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Gameplay Abilities")` — Clears all abilities bound to a given Input ID This will be ignored if the actor is not authoritative @param InputID The numeric Input ID of the abilities to remove
- L1002 _private prototype_ `void ClearAbility(const FGameplayAbilitySpecHandle& Handle);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Gameplay Abilities")` — Removes the specified ability. This will be ignored if the actor is not authoritative. @param Handle Ability Spec Handle of the ability we want to remove
- L1005 _private prototype_ `void SetRemoveAbilityOnEnd(FGameplayAbilitySpecHandle AbilitySpecHandle);` — Sets an ability spec to remove when its finished. If the spec is not currently active, it terminates it immediately. Also clears InputID of the Spec.
- L1016 _private prototype_ `void GetActivatableGameplayAbilitySpecsByAllMatchingTags(const FGameplayTagContainer& GameplayTagContainer, TArray < struct FGameplayAbilitySpec* >& MatchingGameplayAbilities, bool bOnlyAbilitiesThatSatisfyTagRequirements = true) const;` — Gets all Activatable Gameplay Abilities that match all tags in GameplayTagContainer AND for which DoesAbilitySatisfyTagRequirements() is true.  The latter requirement allows this function to find the correct ability without requiring advanced knowledge.  For example, if there are two "Melee" abilities, one of which requires a weapon and one of which requires being unarmed, then those abilities can use Blocking and Required tags to determine when they can fire.  Using the Satisfying Tags requirements simplifies a lot of usage cases. For example, Behavior Trees can use various decorators to test an ability fetched using this mechanism as well as the Task to execute the ability without needing to know that there even is more than one such ability.
- L1024 _private prototype_ `bool TryActivateAbilitiesByTag(const FGameplayTagContainer& GameplayTagContainer, bool bAllowRemoteActivation = true);` — `UFUNCTION(BlueprintCallable, Category = "Abilities")` — Attempts to activate every gameplay ability that matches the given tag and DoesAbilitySatisfyTagRequirements(). Returns true if anything attempts to activate. Can activate more than one ability and the ability may fail later. If bAllowRemoteActivation is true, it will remotely activate local/server abilities, if false it will only try to locally activate abilities.
- L1032 _private prototype_ `bool TryActivateAbilityByClass(TSubclassOf<UGameplayAbility> InAbilityToActivate, bool bAllowRemoteActivation = true);` — `UFUNCTION(BlueprintCallable, Category = "Abilities")` — Attempts to activate the ability that is passed in. This will check costs and requirements before doing so. Returns true if it thinks it activated, but it may return false positives due to failure later in activation. If bAllowRemoteActivation is true, it will remotely activate local/server abilities, if false it will only try to locally activate the ability
- L1040 _private prototype_ `bool TryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation = true);` — `UFUNCTION(BlueprintCallable, Category = "Abilities")` — Attempts to activate the given ability, will check costs and requirements before doing so. Returns true if it thinks it activated, but it may return false positives due to failure later in activation. If bAllowRemoteActivation is true, it will remotely activate local/server abilities, if false it will only try to locally activate the ability
- L1042 _private prototype_ `bool HasActivatableTriggeredAbility(FGameplayTag Tag);`
- L1045 _private prototype_ `bool TriggerAbilityFromGameplayEvent(FGameplayAbilitySpecHandle AbilityToTrigger, FGameplayAbilityActorInfo* ActorInfo, FGameplayTag Tag, const FGameplayEventData* Payload, UAbilitySystemComponent& Component);` — Triggers an ability from a gameplay event, will only trigger on local/server depending on execution flags
- L1052 _private prototype_ `void CancelAbility(UGameplayAbility* Ability);` — Cancels the specified ability CDO.
- L1055 _private prototype_ `void CancelAbilityHandle(const FGameplayAbilitySpecHandle& AbilityHandle);` — Cancels the ability indicated by passed in spec handle. If handle is not found among reactivated abilities nothing happens.
- L1058 _private prototype_ `void CancelAbilities(const FGameplayTagContainer* WithTags=nullptr, const FGameplayTagContainer* WithoutTags=nullptr, UGameplayAbility* Ignore=nullptr);` — Cancel all abilities with the specified tags. Will not cancel the Ignore instance
- L1061 _private prototype_ `void CancelAllAbilities(UGameplayAbility* Ignore=nullptr);` — Cancels all abilities regardless of tags. Will not cancel the ignore instance
- L1064 _private prototype_ `virtual void DestroyActiveState();` — Cancels all abilities and kills any remaining instanced abilities
- L1076 _private prototype_ `virtual void ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecuteCancelTags, const FGameplayTagContainer& CancelTags);` — Called from ability activation or native code, will apply the correct ability blocking tags and cancel existing abilities. Subclasses can override the behavior @param AbilityTags The tags of the ability that has block and cancel flags @param RequestingAbility The gameplay ability requesting the change, can be NULL for native events @param bEnableBlockTags If true will enable the block tags, if false will disable the block tags @param BlockTags What tags to block @param bExecuteCancelTags If true will cancel abilities matching tags @param CancelTags what tags to cancel
- L1079 _private function_ `virtual void HandleChangeAbilityCanBeCanceled(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bCanBeCanceled)` — Called when an ability is cancellable or not. Doesn't do anything by default, can be overridden to tie into gameplay events
- L1083 _private prototype_ `virtual bool AreAbilityTagsBlocked(const FGameplayTagContainer& Tags) const;` — `UFUNCTION(BlueprintCallable, Category="Abilities")` — Returns true if any passed in tags are blocked
- L1086 _private prototype_ `void BlockAbilitiesWithTags(const FGameplayTagContainer& Tags);` — Block or cancel blocking for specific ability tags
- L1087 _private prototype_ `void UnBlockAbilitiesWithTags(const FGameplayTagContainer& Tags);`
- L1090 _private prototype_ `bool IsAbilityInputBlocked(int32 InputID) const;` — Checks if the ability system is currently blocking InputID. Returns true if InputID is blocked, false otherwise.
- L1093 _private prototype_ `void BlockAbilityByInputID(int32 InputID);` — Block or cancel blocking for specific input IDs
- L1094 _private prototype_ `void UnBlockAbilityByInputID(int32 InputID);`
- L1101 _private function_ `const TArray<FGameplayAbilitySpec>& GetActivatableAbilities() const` — Returns the list of all activatable abilities. Read-only.
- L1107 _private function_ `TArray<FGameplayAbilitySpec>& GetActivatableAbilities()` — Returns the list of all activatable abilities.
- L1113 _private function_ `float GetAbilityLastActivatedTime() const` — Returns local world time that an ability was activated. Valid on authority (server) and autonomous proxy (controlling client).
- L1116 _private prototype_ `FGameplayAbilitySpec* FindAbilitySpecFromHandle(FGameplayAbilitySpecHandle Handle, EConsiderPending ConsiderPending = EConsiderPending::PendingRemove) const;` — Returns an ability spec from a handle. If modifying call MarkAbilitySpecDirty. Treat the return value as ephemeral as the pointer will potentially be invalidated on any subsequent call into AbilitySystemComponent.
- L1124 _private prototype_ `TArray<const FGameplayAbilitySpec*> FindAbilitySpecsFromGEHandle(const FScopedAbilityListLock& ScopeLock, FActiveGameplayEffectHandle Handle, EConsiderPending ConsiderPending = EConsiderPending::PendingRemove) const;` — Returns all ability spec handles granted from a GE handle. Only the server may call this function. @param ScopeLock - The lock to communicate to the caller that the return value is only valid for as long as this lock is in scope @param Handle - The handle of the Active Gameplay Effect which granted the abilities we are looking for @param ConsiderPending - Are we returning AbilitySpecs that are pending for addition/removal?
- L1127 _private prototype_ `FGameplayAbilitySpec* FindAbilitySpecFromClass(TSubclassOf<UGameplayAbility> InAbilityClass) const;` — Returns an ability spec corresponding to given ability class. If modifying call MarkAbilitySpecDirty
- L1130 _private prototype_ `FGameplayAbilitySpec* FindAbilitySpecFromInputID(int32 InputID) const;` — Returns an ability spec from a handle. If modifying call MarkAbilitySpecDirty
- L1138 _private prototype_ `virtual void FindAllAbilitySpecsFromInputID(int32 InputID, TArray<const FGameplayAbilitySpec*>& OutAbilitySpecs) const;` — Returns all abilities with the given InputID @param InputID The Input ID to match @param OutAbilitySpecs Array of pointers to matching specs
- L1143 _private prototype_ `virtual FGameplayAbilitySpec BuildAbilitySpecFromClass(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 0, int32 InputID = -1);` — Build a simple FGameplayAbilitySpec from class, level and optional Input ID
- L1152 _private prototype_ `void GetAllAbilities(TArray<FGameplayAbilitySpecHandle>& OutAbilityHandles) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Gameplay Abilities")` — Returns an array with all granted ability handles NOTE: currently this doesn't include abilities that are mid-activation @param OutAbilityHandles This array will be filled with the granted Ability Spec Handles
- L1162 _private prototype_ `void FindAllAbilitiesWithTags(TArray<FGameplayAbilitySpecHandle>& OutAbilityHandles, FGameplayTagContainer Tags, bool bExactMatch = true) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Gameplay Abilities")` — Returns an array with all abilities that match the provided tags @param OutAbilityHandles This array will be filled with matching Ability Spec Handles @param Tags Gameplay Tags to match @param bExactMatch If true, tags must be matched exactly. Otherwise, abilities matching any of the tags will be returned
- L1171 _private prototype_ `void FindAllAbilitiesMatchingQuery(TArray<FGameplayAbilitySpecHandle>& OutAbilityHandles, FGameplayTagQuery Query) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Gameplay Abilities")` — Returns an array with all abilities that match the provided Gameplay Tag Query @param OutAbilityHandles This array will be filled with matching Ability Spec Handles @param Query Gameplay Tag Query to match
- L1180 _private prototype_ `void FindAllAbilitiesWithInputID(TArray<FGameplayAbilitySpecHandle>& OutAbilityHandles, int32 InputID = 0) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Gameplay Abilities")` — Returns an array with all abilities bound to an Input ID value @param OutAbilityHandles This array will be filled with matching Ability Spec Handles @param InputID The Input ID to match
- L1183 _private prototype_ `FGameplayEffectContextHandle GetEffectContextFromActiveGEHandle(FActiveGameplayEffectHandle Handle);` — Retrieves the EffectContext of the GameplayEffect of the active GameplayEffect.
- L1186 _private prototype_ `void MarkAbilitySpecDirty(FGameplayAbilitySpec& Spec, bool WasAddOrRemove=false);` — Call to mark that an ability spec has been modified
- L1189 _private prototype_ `bool InternalTryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, FPredictionKey InPredictionKey = FPredictionKey(), UGameplayAbility ** OutInstancedAbility = nullptr, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate = nullptr, const FGameplayEventData* TriggerEventData = nullptr);` — Attempts to activate the given ability, will only work if called from the correct client/server context
- L1192 _private member_ `FGameplayTagContainer InternalTryActivateAbilityFailureTags;` — Failure tags used by InternalTryActivateAbility (E.g., this stores the  FailureTags of the last call to InternalTryActivateAbility
- L1195 _private prototype_ `virtual void NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled);` — Called from the ability to let the component know it is ended
- L1197 _private prototype_ `void ClearAbilityReplicatedDataCache(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActivationInfo& ActivationInfo);`
- L1200 _private prototype_ `void IncrementAbilityListLock();` — Called from FScopedAbilityListLock
- L1201 _private prototype_ `void DecrementAbilityListLock();`
- L1236 _private prototype_ `static void OnShowDebugInfo(AHUD* HUD, UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& YL, float& YPos);`
- L1238 _private prototype_ `virtual void DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos);`
- L1239 _private prototype_ `virtual void PrintDebug();`
- L1241 _private prototype_ `void AccumulateScreenPos(FAbilitySystemComponentDebugInfo& Info);`
- L1242 _private prototype_ `virtual void Debug_Internal(struct FAbilitySystemComponentDebugInfo& Info);`
- L1243 _private prototype_ `void DebugLine(struct FAbilitySystemComponentDebugInfo& Info, FString Str, float XOffset, float YOffset, int32 MinTextRowsToAdvance = 0);`
- L1244 _private prototype_ `FString CleanupName(FString Str);`
- L1247 _private prototype_ `void PrintAllGameplayEffects() const;` — Print a debug list of all gameplay effects
- L1251 _private prototype_ `void ServerPrintDebug_Request();` — `UFUNCTION(Server, reliable, WithValidation)` — Ask the server to send ability system debug information back to the client, via ClientPrintDebug_Response
- L1255 _private prototype_ `void ServerPrintDebug_RequestWithStrings(const TArray<FString>& Strings);` — `UFUNCTION(Server, reliable, WithValidation)` — Same as ServerPrintDebug_Request but this includes the client debug strings so that the server can embed them in replays
- L1258 _private prototype_ `virtual void OnServerPrintDebug_Request();` — Virtual function games can override to do their own stuff when either ServerPrintDebug function runs on the server
- L1261 _private prototype_ `virtual bool ShouldSendClientDebugStringsToServer() const;` — Determines whether to call ServerPrintDebug_Request or ServerPrintDebug_RequestWithStrings.
- L1264 _private prototype_ `void ClientPrintDebug_Response(const TArray<FString>& Strings, int32 GameFlags);` — `UFUNCTION(Client, reliable)`
- L1265 _private prototype_ `virtual void OnClientPrintDebug_Response(const TArray<FString>& Strings, int32 GameFlags);`
- L1268 _private prototype_ `void ClearDebugInstantEffects();`
- L1270 _private prototype_ `virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const override;`
- L1275 _private member_ `TArray<FString> ClientDebugStrings;` — `UPROPERTY(ReplicatedUsing=OnRep_ClientDebugString)`
- L1278 _private member_ `TArray<FString> ServerDebugStrings;` — `UPROPERTY(ReplicatedUsing = OnRep_ServerDebugString)`
- L1281 _public prototype_ `void SetClientDebugStrings(TArray<FString>&& NewClientDebugStrings);`
- L1282 _public prototype_ `TArray<FString>& GetClientDebugStrings_Mutable();`
- L1283 _public prototype_ `const TArray<FString>& GetClientDebugStrings() const;`
- L1285 _public prototype_ `void SetServerDebugStrings(TArray<FString>&& NewServerDebugStrings);`
- L1286 _public prototype_ `TArray<FString>& GetServerDebugStrings_Mutable();`
- L1287 _public prototype_ `const TArray<FString>& GetServerDebugStrings() const;`
- L1290 _public prototype_ `virtual void OnRep_ClientDebugString();` — `UFUNCTION()`
- L1293 _public prototype_ `virtual void OnRep_ServerDebugString();` — `UFUNCTION()`
- L1300 _public prototype_ `void CallServerTryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool InputPressed, FPredictionKey PredictionKey);`
- L1301 _public prototype_ `void CallServerSetReplicatedTargetData(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, const FGameplayAbilityTargetDataHandle& ReplicatedTargetDataHandle, FGameplayTag ApplicationTag, FPredictionKey CurrentPredictionKey);`
- L1302 _public prototype_ `void CallServerEndAbility(FGameplayAbilitySpecHandle AbilityToEnd, FGameplayAbilityActivationInfo ActivationInfo, FPredictionKey PredictionKey);`
- L1304 _public function_ `virtual bool ShouldDoServerAbilityRPCBatch() const`
- L1305 _public prototype_ `virtual void BeginServerAbilityRPCBatch(FGameplayAbilitySpecHandle AbilityHandle);`
- L1306 _public prototype_ `virtual void EndServerAbilityRPCBatch(FGameplayAbilitySpecHandle AbilityHandle);`
- L1309 _public member_ `TArray<FServerAbilityRPCBatch, TInlineAllocator<1> > LocalServerAbilityRPCBatchData;` — Accumulated client side data that is batched out to server on EndServerAbilityRPCBatch
- L1312 _public prototype_ `void ServerAbilityRPCBatch(FServerAbilityRPCBatch BatchInfo);` — `UFUNCTION(Server, reliable, WithValidation)`
- L1315 _public prototype_ `virtual void ServerAbilityRPCBatch_Internal(FServerAbilityRPCBatch& BatchInfo);` — Overridable function for sub classes
- L1327 _public prototype_ `bool GetUserAbilityActivationInhibited() const;` — `UFUNCTION(BlueprintCallable, Category="Abilities")` — This is meant to be used to inhibit activating an ability from an input perspective. (E.g., the menu is pulled up, another game mechanism is consuming all input, etc) This should only be called on locally owned players. This should not be used to game mechanics like silences or disables. Those should be done through gameplay effects.
- L1331 _public prototype_ `virtual void SetUserAbilityActivationInhibited(bool NewInhibit);` — `UFUNCTION(BlueprintCallable, Category="Abilities")` — Disable or Enable a local user from being able to activate abilities. This should only be used for input/UI etc related inhibition. Do not use for game mechanics.
- L1335 _public member_ `bool UserAbilityActivationInhibited;` — `UPROPERTY()` — Rather activation is currently inhibited
- L1339 _public member_ `bool ReplicationProxyEnabled;` — `UPROPERTY()` — When enabled GameplayCue RPCs will be routed through the AvatarActor's IAbilitySystemReplicationProxyInterface rather than this component
- L1343 _public member_ `bool bSuppressGrantAbility;` — `UPROPERTY()` — Suppress all ability granting through GEs on this component
- L1347 _public member_ `bool bSuppressGameplayCues;` — `UPROPERTY()` — Suppress all GameplayCues on this component
- L1351 _public member_ `TArray<TObjectPtr<AGameplayAbilityTargetActor>> SpawnedTargetActors;` — `UPROPERTY()` — List of currently active targeting actors
- L1354 _public prototype_ `virtual void BindToInputComponent(UInputComponent* InputComponent);` — Bind to an input component with some default action names
- L1357 _public prototype_ `virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo);` — Bind to an input component with customized bindings
- L1360 _public prototype_ `virtual void SetBlockAbilityBindingsArray(FGameplayAbilityInputBinds BindInfo);` — Initializes BlockedAbilityBindings variable
- L1363 _public prototype_ `virtual void AbilityLocalInputPressed(int32 InputID);` — Called to handle ability bind input
- L1364 _public prototype_ `virtual void AbilityLocalInputReleased(int32 InputID);`
- L1372 _public prototype_ `void PressInputID(int32 InputID);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Abilities")` — Sends a local player Input Pressed event with the provided Input ID, notifying any bound abilities @param InputID The Input ID to match
- L1379 _public prototype_ `void ReleaseInputID(int32 InputID);` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Abilities")` — Sends a local player Input Released event with the provided Input ID, notifying any bound abilities @param InputID The Input ID to match
- L1382 _public prototype_ `virtual void LocalInputConfirm();` — Handle confirm/cancel for target actors
- L1383 _public prototype_ `virtual void LocalInputCancel();`
- L1389 _public prototype_ `void InputConfirm();` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Abilities")` — Sends a local player Input Confirm event, notifying abilities
- L1395 _public prototype_ `void InputCancel();` — `UFUNCTION(BlueprintCallable, Category = "Gameplay Abilities")` — Sends a local player Input Cancel event, notifying abilities
- L1398 _public member_ `int32 GenericConfirmInputID;` — InputID for binding GenericConfirm/Cancel events
- L1399 _public member_ `int32 GenericCancelInputID;`
- L1401 _public function_ `bool IsGenericConfirmInputBound(int32 InputID) const`
- L1402 _public function_ `bool IsGenericCancelInputBound(int32 InputID) const`
- L1405 _public member_ `FAbilityConfirmOrCancel GenericLocalConfirmCallbacks;` — Generic local callback for generic ConfirmEvent that any ability can listen to
- L1408 _public member_ `FAbilityConfirmOrCancel GenericLocalCancelCallbacks;` — Generic local callback for generic CancelEvent that any ability can listen to
- L1412 _public prototype_ `virtual void TargetConfirm();` — `UFUNCTION(BlueprintCallable, Category = "Abilities")` — Any active targeting actors will be told to stop and return current targeting data
- L1416 _public prototype_ `virtual void TargetCancel();` — `UFUNCTION(BlueprintCallable, Category = "Abilities")` — Any active targeting actors will be stopped and canceled, not returning any targeting data
- L1423 _public prototype_ `virtual float PlayMontage(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimMontage* Montage, float InPlayRate, FName StartSectionName = NAME_None, float StartTimeSeconds = 0.0f);` — Plays a montage and handles replication and prediction based on passed in ability/activation info
- L1425 _public prototype_ `virtual UAnimMontage* PlaySlotAnimationAsDynamicMontage(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate = 1.f, float StartTimeSeconds = 0.0f);`
- L1427 _public prototype_ `virtual UAnimMontage* PlaySlotAnimationAsDynamicMontage_WithFractionalLoops(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate = 1.f, float StartTimeSeconds = 0.0f, float PlayCount = 1.0f);`
- L1430 _public prototype_ `virtual float PlayMontageSimulated(UAnimMontage* Montage, float InPlayRate, FName StartSectionName = NAME_None);` — Plays a montage without updating replication/prediction structures. Used by simulated proxies when replication tells them to play a montage.
- L1432 _public prototype_ `virtual UAnimMontage* PlaySlotAnimationAsDynamicMontageSimulated(UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate = 1.f);`
- L1434 _public prototype_ `virtual UAnimMontage* PlaySlotAnimationAsDynamicMontage_WithFractionalLoopsSimulated(UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate = 1.f, float PlayCount = 1.0f);`
- L1437 _public prototype_ `virtual void CurrentMontageStop(float OverrideBlendOutTime = -1.0f);` — Stops whatever montage is currently playing. Expectation is caller should only be stopping it if they are the current animating ability (or have good reason not to check)
- L1440 _public prototype_ `virtual void StopMontageIfCurrent(const UAnimMontage& Montage, float OverrideBlendOutTime = -1.0f);` — Stops current montage if it's the one given as the Montage param
- L1443 _public prototype_ `virtual void ClearAnimatingAbility(UGameplayAbility* Ability);` — Clear the animating ability that is passed in, if it's still currently animating
- L1446 _public prototype_ `virtual void CurrentMontageJumpToSection(FName SectionName);` — Jumps current montage to given section. Expectation is caller should only be stopping it if they are the current animating ability (or have good reason not to check)
- L1449 _public prototype_ `virtual void CurrentMontageSetNextSectionName(FName FromSectionName, FName ToSectionName);` — Sets current montages next section name. Expectation is caller should only be stopping it if they are the current animating ability (or have good reason not to check)
- L1452 _public prototype_ `FName CurrentMontageGetNextSectionName() const;` — Returns the next section name for the current montage.
- L1455 _public prototype_ `virtual void CurrentMontageSetPlayRate(float InPlayRate);` — Sets current montage's play rate
- L1458 _public prototype_ `bool IsAnimatingAbility(UGameplayAbility* Ability) const;` — Returns true if the passed in ability is the current animating ability
- L1461 _public prototype_ `UGameplayAbility* GetAnimatingAbility() const;` — Returns the current animating ability
- L1464 _public prototype_ `UAnimMontage* GetCurrentMontage() const;` — Returns montage that is currently playing
- L1467 _public prototype_ `int32 GetCurrentMontageSectionID() const;` — Get SectionID of currently playing AnimMontage
- L1470 _public prototype_ `FName GetCurrentMontageSectionName() const;` — Get SectionName of currently playing AnimMontage
- L1473 _public prototype_ `float GetCurrentMontageSectionLength() const;` — Get length in time of current section
- L1476 _public prototype_ `float GetCurrentMontageSectionTimeLeft() const;` — Returns amount of time left in current section
- L1479 _public prototype_ `void SetMontageRepAnimPositionMethod(ERepAnimPositionMethod InMethod);` — Method to set the replication method for the position in the montage
- L1489 _private member_ `TObjectPtr<AActor> OwnerActor;` — `UPROPERTY(ReplicatedUsing = OnRep_OwningActor)` — The actor that owns this component logically
- L1493 _private member_ `TObjectPtr<AActor> AvatarActor;` — `UPROPERTY(ReplicatedUsing = OnRep_OwningActor)` — The actor that is the physical representation used for abilities. Can be NULL
- L1497 _public prototype_ `void SetOwnerActor(AActor* NewOwnerActor);`
- L1498 _public function_ `AActor* GetOwnerActor() const`
- L1500 _public prototype_ `void SetAvatarActor_Direct(AActor* NewAvatarActor);`
- L1501 _public function_ `AActor* GetAvatarActor_Direct() const`
- L1504 _public prototype_ `void OnRep_OwningActor();` — `UFUNCTION()`
- L1507 _public prototype_ `void OnAvatarActorDestroyed(AActor* InActor);` — `UFUNCTION()`
- L1510 _public prototype_ `void OnOwnerActorDestroyed(AActor* InActor);` — `UFUNCTION()`
- L1513 _public prototype_ `void OnSpawnedAttributesEndPlayed(AActor* InActor, EEndPlayReason::Type EndPlayReason);` — `UFUNCTION()`
- L1516 _public member_ `TSharedPtr<FGameplayAbilityActorInfo> AbilityActorInfo;` — Cached off data about the owning actor that abilities will need to frequently access (movement component, mesh component, anim instance, etc)
- L1523 _public prototype_ `virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor);` — Initialized the Abilities' ActorInfo - the structure that holds information about who we are acting on and who controls us. OwnerActor is the actor that logically owns this component. AvatarActor is what physical actor in the world we are acting on. Usually a Pawn but it could be a Tower, Building, Turret, etc, may be the same as Owner
- L1526 _public prototype_ `virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;` — Returns avatar actor to be used for a specific task, normally GetAvatarActor
- L1529 _public prototype_ `AActor* GetAvatarActor() const;` — Returns the avatar actor for this component
- L1532 _public prototype_ `void SetAvatarActor(AActor* InAvatarActor);` — Changes the avatar actor, leaves the owner actor the same
- L1535 _public function_ `virtual void OnPlayerControllerSet()` — called when the ASC's AbilityActorInfo has a PlayerController set.
- L1540 _public prototype_ `virtual void ClearActorInfo();` — This is called when the actor that is initialized to this system dies, this will clear that actor from this system and FGameplayAbilityActorInfo
- L1546 _public prototype_ `void RefreshAbilityActorInfo();` — This will refresh the Ability's ActorInfo structure based on the current ActorInfo. That is, AvatarActor will be the same but we will look for new AnimInstance, MovementComponent, PlayerController, etc.
- L1555 _public prototype_ `void ServerSetReplicatedEvent(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, FPredictionKey CurrentPredictionKey);` — `UFUNCTION(Server, reliable, WithValidation)` — Replicates the Generic Replicated Event to the server.
- L1559 _public prototype_ `void ServerSetReplicatedEventWithPayload(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, FPredictionKey CurrentPredictionKey, FVector_NetQuantize100 VectorPayload);` — `UFUNCTION(Server, reliable, WithValidation)` — Replicates the Generic Replicated Event to the server with payload.
- L1563 _public prototype_ `void ClientSetReplicatedEvent(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — `UFUNCTION(Client, reliable)` — Replicates the Generic Replicated Event to the client.
- L1566 _public prototype_ `bool InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, FPredictionKey CurrentPredictionKey = FPredictionKey());` — Calls local callbacks that are registered with the given Generic Replicated Event
- L1569 _public prototype_ `bool InvokeReplicatedEventWithPayload(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, FPredictionKey CurrentPredictionKey, FVector_NetQuantize100 VectorPayload);` — Calls local callbacks that are registered with the given Generic Replicated Event
- L1573 _public prototype_ `void ServerSetReplicatedTargetData(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, const FGameplayAbilityTargetDataHandle& ReplicatedTargetDataHandle, FGameplayTag ApplicationTag, FPredictionKey CurrentPredictionKey);` — `UFUNCTION(Server, reliable, WithValidation)` — Replicates targeting data to the server
- L1577 _public prototype_ `void ServerSetReplicatedTargetDataCancelled(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, FPredictionKey CurrentPredictionKey);` — `UFUNCTION(Server, reliable, WithValidation)` — Replicates to the server that targeting has been cancelled
- L1580 _public prototype_ `virtual void ConfirmAbilityTargetData(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, const FGameplayAbilityTargetDataHandle& TargetData, const FGameplayTag& ApplicationTag);` — Sets the current target data and calls applicable callbacks
- L1583 _public prototype_ `virtual void CancelAbilityTargetData(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Cancels the ability target data and calls callbacks
- L1586 _public prototype_ `void ConsumeAllReplicatedData(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Deletes all cached ability client data (Was: ConsumeAbilityTargetData)
- L1588 _public prototype_ `void ConsumeClientReplicatedTargetData(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Consumes cached TargetData from client (only TargetData)
- L1591 _public prototype_ `void ConsumeGenericReplicatedEvent(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Consumes the given Generic Replicated Event (unsets it).
- L1594 _public prototype_ `FAbilityReplicatedData GetReplicatedDataOfGenericReplicatedEvent(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Gets replicated data of the given Generic Replicated Event.
- L1597 _public prototype_ `void CallAllReplicatedDelegatesIfSet(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Calls any Replicated delegates that have been sent (TargetData or Generic Replicated Events). Note this can be dangerous if multiple places in an ability register events and then call this function.
- L1600 _public prototype_ `bool CallReplicatedTargetDataDelegatesIfSet(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Calls the TargetData Confirm/Cancel events if they have been sent.
- L1603 _public prototype_ `bool CallReplicatedEventDelegateIfSet(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Calls a given Generic Replicated Event delegate if the event has already been sent
- L1606 _public prototype_ `bool CallOrAddReplicatedDelegate(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey, FSimpleMulticastDelegate::FDelegate Delegate);` — Calls passed in delegate if the Client Event has already been sent. If not, it adds the delegate to our multicast callback that will fire when it does.
- L1609 _public prototype_ `FAbilityTargetDataSetDelegate& AbilityTargetDataSetDelegate(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Returns TargetDataSet delegate for a given Ability/PredictionKey pair
- L1612 _public prototype_ `FSimpleMulticastDelegate& AbilityTargetDataCancelledDelegate(FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Returns TargetData Cancelled delegate for a given Ability/PredictionKey pair
- L1615 _public prototype_ `FSimpleMulticastDelegate& AbilityReplicatedEventDelegate(EAbilityGenericReplicatedEvent::Type EventType, FGameplayAbilitySpecHandle AbilityHandle, FPredictionKey AbilityOriginalPredictionKey);` — Returns Generic Replicated Event for a given Ability/PredictionKey pair
- L1619 _public prototype_ `void ServerSetInputPressed(FGameplayAbilitySpecHandle AbilityHandle);` — `UFUNCTION(Server, reliable, WithValidation)` — Direct Input state replication. These will be called if bReplicateInputDirectly is true on the ability and is generally not a good thing to use. (Instead, prefer to use Generic Replicated Events).
- L1622 _public prototype_ `void ServerSetInputReleased(FGameplayAbilitySpecHandle AbilityHandle);` — `UFUNCTION(Server, reliable, WithValidation)`
- L1625 _public prototype_ `virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec);` — Called on local player always. Called on server only if bReplicateInputDirectly is set on the GameplayAbility.
- L1628 _public prototype_ `virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec);` — Called on local player always. Called on server only if bReplicateInputDirectly is set on the GameplayAbility.
- L1634 _public prototype_ `virtual void InitializeComponent() override;`
- L1635 _public prototype_ `virtual void UninitializeComponent() override;`
- L1636 _public prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L1637 _public prototype_ `virtual bool GetShouldTick() const override;`
- L1638 _public prototype_ `virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;`
- L1639 _public prototype_ `virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags) override;`
- L1641 _public prototype_ `virtual void ForceReplication() override;` — Force owning actor to update it's replication, to make sure that gameplay cues get sent down quickly. Override to change how aggressive this is
- L1642 _public prototype_ `virtual void PreNetReceive() override;`
- L1643 _public prototype_ `virtual void PostNetReceive() override;`
- L1644 _public prototype_ `virtual void OnRegister() override;`
- L1645 _public prototype_ `virtual void OnUnregister() override;`
- L1646 _public prototype_ `virtual void ReadyForReplication() override;`
- L1647 _public prototype_ `virtual void BeginPlay() override;`
- L1648 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L1651 _protected prototype_ `virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;`
- L1652 _protected prototype_ `virtual void GetReplicatedCustomConditionState(FCustomPropertyConditionState& OutActiveState) const override;`
- L1654 _protected prototype_ `void UpdateActiveGameplayEffectsReplicationCondition();`
- L1655 _protected prototype_ `void UpdateMinimalReplicationGameplayCuesCondition();`
- L1668 _protected member_ `FGameplayAbilitySpecContainer ActivatableAbilities;` — `UPROPERTY(ReplicatedUsing = OnRep_ActivateAbilities, BlueprintReadOnly, Transient, Category = "Abilities")`
- L1671 _protected member_ `FGameplayAbilityReplicatedDataContainer AbilityTargetDataMap;` — Maps from an ability spec to the target data. Used to track replicated data and callbacks
- L1674 _protected member_ `TArray<TPair<FGameplayTagContainer, FGameplayEventTagMulticastDelegate>> GameplayEventTagContainerDelegates;` — List of gameplay tag container filters, and the delegates they call
- L1679 _private member_ `TArray<TObjectPtr<UGameplayAbility>> AllReplicatedInstancedAbilities;` — `UPROPERTY()` — Full list of all instance-per-execution gameplay abilities associated with this component
- L1683 _protected function_ `const TArray<UGameplayAbility*>& GetReplicatedInstancedAbilities() const` — Full list of all instance-per-execution gameplay abilities associated with this component
- L1686 _protected prototype_ `void AddReplicatedInstancedAbility(UGameplayAbility* GameplayAbility);` — Add a gameplay ability associated to this component
- L1689 _protected prototype_ `void RemoveReplicatedInstancedAbility(UGameplayAbility* GameplayAbility);` — Remove a gameplay ability associated to this component
- L1692 _protected prototype_ `void RemoveAllReplicatedInstancedAbilities();` — Unregister all the gameplay abilities of this component
- L1695 _protected prototype_ `virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec);` — Will be called from GiveAbility or from OnRep. Initializes events (triggers and inputs) with the given ability
- L1698 _protected prototype_ `virtual void OnRemoveAbility(FGameplayAbilitySpec& AbilitySpec);` — Will be called from RemoveAbility or from OnRep. Unbinds inputs with the given ability
- L1701 _protected prototype_ `void CheckForClearedAbilities();` — Called from ClearAbility, ClearAllAbilities or OnRep. Clears any triggers that should no longer exist.
- L1704 _protected prototype_ `virtual void CancelAbilitySpec(FGameplayAbilitySpec& Spec, UGameplayAbility* Ignore);` — Cancel a specific ability spec
- L1707 _protected prototype_ `virtual UGameplayAbility* CreateNewInstanceOfAbility(FGameplayAbilitySpec& Spec, const UGameplayAbility* Ability);` — Creates a new instance of an ability, storing it in the spec
- L1710 _protected member_ `int32 AbilityScopeLockCount;` — Indicates how many levels of ABILITY_SCOPE_LOCK() we are in. The ability list may not be modified while AbilityScopeLockCount > 0.
- L1712 _protected member_ `TArray<FGameplayAbilitySpecHandle, TInlineAllocator<2> > AbilityPendingRemoves;` — Abilities that will be removed when exiting the current ability scope lock.
- L1714 _protected member_ `TArray<FGameplayAbilitySpec, TInlineAllocator<2> > AbilityPendingAdds;` — Abilities that will be added when exiting the current ability scope lock.
- L1716 _protected member_ `bool bAbilityPendingClearAll;` — Whether all abilities should be removed when exiting the current ability scope lock. Will be prioritized over pending adds.
- L1719 _protected member_ `float AbilityLastActivatedTime;` — Local World time of the last ability activation. This is used for AFK/idle detection
- L1722 _protected prototype_ `virtual void OnRep_ActivateAbilities();` — `UFUNCTION()`
- L1725 _protected prototype_ `void ServerTryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool InputPressed, FPredictionKey PredictionKey);` — `UFUNCTION(Server, reliable, WithValidation)`
- L1728 _protected prototype_ `void ServerTryActivateAbilityWithEventData(FGameplayAbilitySpecHandle AbilityToActivate, bool InputPressed, FPredictionKey PredictionKey, FGameplayEventData TriggerEventData);` — `UFUNCTION(Server, reliable, WithValidation)`
- L1731 _protected prototype_ `void ClientTryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate);` — `UFUNCTION(Client, reliable)`
- L1734 _protected prototype_ `void RemoteEndOrCancelAbility(FGameplayAbilitySpecHandle AbilityToEnd, FGameplayAbilityActivationInfo ActivationInfo, bool bWasCanceled);` — Called by ServerEndAbility and ClientEndAbility; avoids code duplication.
- L1737 _protected prototype_ `void ServerEndAbility(FGameplayAbilitySpecHandle AbilityToEnd, FGameplayAbilityActivationInfo ActivationInfo, FPredictionKey PredictionKey);` — `UFUNCTION(Server, reliable, WithValidation)`
- L1740 _protected prototype_ `void ClientEndAbility(FGameplayAbilitySpecHandle AbilityToEnd, FGameplayAbilityActivationInfo ActivationInfo);` — `UFUNCTION(Client, reliable)`
- L1743 _protected prototype_ `void ServerCancelAbility(FGameplayAbilitySpecHandle AbilityToCancel, FGameplayAbilityActivationInfo ActivationInfo);` — `UFUNCTION(Server, reliable, WithValidation)`
- L1746 _protected prototype_ `void ClientCancelAbility(FGameplayAbilitySpecHandle AbilityToCancel, FGameplayAbilityActivationInfo ActivationInfo);` — `UFUNCTION(Client, reliable)`
- L1749 _protected prototype_ `void ClientActivateAbilityFailed(FGameplayAbilitySpecHandle AbilityToActivate, int16 PredictionKey);` — `UFUNCTION(Client, Reliable)`
- L1750 _protected member_ `int32 ClientActivateAbilityFailedCountRecent;`
- L1751 _protected member_ `float ClientActivateAbilityFailedStartTime;`
- L1754 _protected prototype_ `void OnClientActivateAbilityCaughtUp(FGameplayAbilitySpecHandle AbilityToActivate, FPredictionKey::KeyType PredictionKey);`
- L1757 _protected prototype_ `void ClientActivateAbilitySucceed(FGameplayAbilitySpecHandle AbilityToActivate, FPredictionKey PredictionKey);` — `UFUNCTION(Client, Reliable)`
- L1760 _protected prototype_ `void ClientActivateAbilitySucceedWithEventData(FGameplayAbilitySpecHandle AbilityToActivate, FPredictionKey PredictionKey, FGameplayEventData TriggerEventData);` — `UFUNCTION(Client, Reliable)`
- L1763 _protected prototype_ `virtual void InternalServerTryActivateAbility(FGameplayAbilitySpecHandle AbilityToActivate, bool InputPressed, const FPredictionKey& PredictionKey, const FGameplayEventData* TriggerEventData);` — Implementation of ServerTryActivateAbility
- L1766 _protected prototype_ `void OnPredictiveMontageRejected(UAnimMontage* PredictiveMontage);` — Called when a prediction key that played a montage is rejected
- L1769 _protected prototype_ `void AnimMontage_UpdateReplicatedData();` — Copy LocalAnimMontageInfo into RepAnimMontageInfo
- L1770 _protected prototype_ `void AnimMontage_UpdateReplicatedData(FGameplayAbilityRepAnimMontage& OutRepAnimMontageInfo);`
- L1773 _protected prototype_ `void AnimMontage_UpdateForcedPlayFlags(FGameplayAbilityRepAnimMontage& OutRepAnimMontageInfo);` — Copy over playing flags for duplicate animation data
- L1778 _protected member_ `FGameplayAbilityRepAnimMontage RepAnimMontageInfo;` — `UPROPERTY(ReplicatedUsing=OnRep_ReplicatedAnimMontage)` — Data structure for replicating montage info to simulated clients
- L1780 _protected prototype_ `void SetRepAnimMontageInfo(const FGameplayAbilityRepAnimMontage& NewRepAnimMontageInfo);`
- L1781 _protected prototype_ `FGameplayAbilityRepAnimMontage& GetRepAnimMontageInfo_Mutable();`
- L1782 _protected prototype_ `const FGameplayAbilityRepAnimMontage& GetRepAnimMontageInfo() const;`
- L1786 _protected member_ `bool bCachedIsNetSimulated;` — `UPROPERTY()` — Cached value of rather this is a simulated actor
- L1790 _protected member_ `bool bPendingMontageRep;` — `UPROPERTY()` — Set if montage rep happens while we don't have the animinstance associated with us yet
- L1794 _protected member_ `FGameplayAbilityLocalAnimMontage LocalAnimMontageInfo;` — `UPROPERTY()` — Data structure for montages that were instigated locally (everything if server, predictive if client. replicated if simulated proxy)
- L1797 _protected prototype_ `virtual void OnRep_ReplicatedAnimMontage();` — `UFUNCTION()`
- L1800 _protected prototype_ `virtual bool IsReadyForReplicatedMontage();` — Returns true if we are ready to handle replicated montage information
- L1804 _protected prototype_ `void ServerCurrentMontageSetNextSectionName(UAnimSequenceBase* ClientAnimation, float ClientPosition, FName SectionName, FName NextSectionName);` — `UFUNCTION(reliable, server, WithValidation)` — RPC function called from CurrentMontageSetNextSectionName, replicates to other clients
- L1808 _protected prototype_ `void ServerCurrentMontageJumpToSectionName(UAnimSequenceBase* ClientAnimation, FName SectionName);` — `UFUNCTION(reliable, server, WithValidation)` — RPC function called from CurrentMontageJumpToSection, replicates to other clients
- L1812 _protected prototype_ `void ServerCurrentMontageSetPlayRate(UAnimSequenceBase* ClientAnimation, float InPlayRate);` — `UFUNCTION(reliable, server, WithValidation)` — RPC function called from CurrentMontageSetPlayRate, replicates to other clients
- L1815 _protected member_ `TMap<FGameplayTag, TArray<FGameplayAbilitySpecHandle > > GameplayEventTriggeredAbilities;` — Abilities that are triggered from a gameplay event
- L1818 _protected member_ `TMap<FGameplayTag, TArray<FGameplayAbilitySpecHandle > > OwnedTagTriggeredAbilities;` — Abilities that are triggered from a tag being added to the owner
- L1821 _protected prototype_ `virtual void MonitoredTagChanged(const FGameplayTag Tag, int32 NewCount);` — Callback that is called when an owned tag bound to an ability changes
- L1824 _protected prototype_ `bool HasNetworkAuthorityToActivateTriggeredAbility(const FGameplayAbilitySpec &Spec) const;` — Returns true if the specified ability should be activated from an event in this network mode
- L1827 _protected prototype_ `virtual void AddGameplayCue_Internal(const FGameplayTag GameplayCueTag, FGameplayEffectContextHandle& EffectContext, FActiveGameplayCueContainer& GameplayCueContainer);` — Internal gameplay cue functions
- L1828 _protected prototype_ `virtual void AddGameplayCue_Internal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters, FActiveGameplayCueContainer& GameplayCueContainer);`
- L1829 _protected prototype_ `virtual void RemoveGameplayCue_Internal(const FGameplayTag GameplayCueTag, FActiveGameplayCueContainer& GameplayCueContainer);`
- L1832 _protected prototype_ `void SetNumericAttribute_Internal(const FGameplayAttribute &Attribute, float& NewFloatValue);` — Actually pushes the final attribute value to the attribute set's property. Should not be called by outside code since this does not go through the attribute aggregator system.
- L1834 _protected prototype_ `bool HasNetworkAuthorityToApplyGameplayEffect(FPredictionKey PredictionKey) const;`
- L1836 _protected prototype_ `void ExecutePeriodicEffect(FActiveGameplayEffectHandle Handle);`
- L1838 _protected prototype_ `void ExecuteGameplayEffect(FGameplayEffectSpec &Spec, FPredictionKey PredictionKey);`
- L1840 _protected prototype_ `void CheckDurationExpired(FActiveGameplayEffectHandle Handle);`
- L1842 _protected prototype_ `TArray<TObjectPtr<UGameplayTask>>& GetAbilityActiveTasks(UGameplayAbility* Ability);`
- L1845 _protected prototype_ `void RemoveActiveGameplayEffect_AllowClientRemoval(FActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);` — A version of RemoveActiveGameplayEffect that allows us to remove it even when we don't have authority
- L1847 _protected prototype_ `void OnCaughtUpActiveGameplayEffect(FActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);`
- L1849 _protected prototype_ `void OnRejectedActiveGameplayEffect(FActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);`
- L1851 _protected prototype_ `void OnPredictiveGameplayEffectStackCaughtUp(FActiveGameplayEffectHandle Handle);`
- L1855 _protected member_ `FActiveGameplayEffectsContainer ActiveGameplayEffects;` — `UPROPERTY(Replicated)` — Contains all of the gameplay effects that are currently active on this component
- L1859 _protected member_ `FActiveGameplayCueContainer ActiveGameplayCues;` — `UPROPERTY(Replicated)` — List of all active gameplay cues (executed outside of Gameplay Effects)
- L1863 _protected member_ `FActiveGameplayCueContainer MinimalReplicationGameplayCues;` — `UPROPERTY(Replicated)` — Replicated gameplaycues when in minimal replication mode. These are cues that would come normally come from ActiveGameplayEffects (but since we do not replicate AGE in minimal mode, they must be replicated through here)
- L1866 _protected member_ `FGameplayTagCountContainer BlockedAbilityTags;` — Abilities with these tags are not able to be activated
- L1868 _protected prototype_ `void SetBlockedAbilityBindings(const TArray<uint8>& NewBlockedAbilityBindings);`
- L1869 _protected prototype_ `TArray<uint8>& GetBlockedAbilityBindings_Mutable();`
- L1870 _protected prototype_ `const TArray<uint8>& GetBlockedAbilityBindings() const;`
- L1872 _protected prototype_ `void DebugCyclicAggregatorBroadcasts(struct FAggregator* Aggregator);`
- L1876 _protected member_ `FGameplayTagCountContainer GameplayTagCountContainer;` — `UPROPERTY(Replicated)` — Acceleration map for all gameplay tags (OwnedGameplayTags from GEs and explicit GameplayCueTags)
- L1878 _protected prototype_ `void SetMinimalReplicationTags(const FMinimalReplicationTagCountMap& NewMinimalReplicationTags);`
- L1879 _protected prototype_ `FMinimalReplicationTagCountMap& GetMinimalReplicationTags_Mutable();`
- L1880 _protected prototype_ `const FMinimalReplicationTagCountMap& GetMinimalReplicationTags() const;`
- L1882 _protected prototype_ `FMinimalReplicationTagCountMap& GetReplicatedLooseTags_Mutable();`
- L1883 _protected prototype_ `const FMinimalReplicationTagCountMap& GetReplicatedLooseTags() const;`
- L1885 _protected prototype_ `void ResetTagMap();`
- L1887 _protected prototype_ `void NotifyTagMap_StackCountChange(const FGameplayTagContainer& Container);`
- L1889 _protected function_ `virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists)`
- L1891 _protected prototype_ `const UAttributeSet* GetAttributeSubobject(const TSubclassOf<UAttributeSet> AttributeClass) const;`
- L1892 _protected prototype_ `const UAttributeSet* GetAttributeSubobjectChecked(const TSubclassOf<UAttributeSet> AttributeClass) const;`
- L1893 _protected prototype_ `const UAttributeSet* GetOrCreateAttributeSubobject(TSubclassOf<UAttributeSet> AttributeClass);`
- L1895 _protected prototype_ `void UpdateTagMapSingle_Internal(const FGameplayTag& Tag, int32 CountDelta, EGameplayTagReplicationState TagRepState);`
- L1896 _protected prototype_ `void UpdateTagMap_Internal(const FGameplayTagContainer& Container, int32 CountDelta, EGameplayTagReplicationState TagRepState);`
- L1912 _private prototype_ `TArray<TObjectPtr<UAttributeSet>>& GetSpawnedAttributes_Mutable();`
- L1915 _private prototype_ `void SetSpawnedAttributesListDirty();` — Needs to be called when modifying the SpawnedAttributes array for changes to be replicated
- L1919 _private member_ `TArray<uint8> BlockedAbilityBindings;` — `UPROPERTY(Transient, Replicated)` — Tracks abilities that are blocked based on input binding. An ability is blocked if BlockedAbilityBindings[InputID] > 0
- L1923 _private member_ `FMinimalReplicationTagCountMap MinimalReplicationTags;` — `UE_DEPRECATED(5.7, "This will be removed in favor of using TagOnly replication state for on the replicated Tag Count Container")` — `UPROPERTY(Replicated)`
- L1925 _private prototype_ `void RegisterAbilityTriggers(const FGameplayAbilitySpec& Spec, TConstArrayView<FAbilityTriggerData> AbilityTriggers);`
- L1926 _private prototype_ `void UnregisterAbilityTriggers(const FGameplayAbilitySpec& Spec, TConstArrayView<FAbilityTriggerData> AbilityTriggers);`
- L1932 _private member_ `TArray<TObjectPtr<UAttributeSet>> SpawnedAttributes;` — `UPROPERTY(Replicated, ReplicatedUsing = OnRep_SpawnedAttributes, Transient)` — List of attribute sets
- L1935 _private prototype_ `void OnRep_SpawnedAttributes(const TArray<UAttributeSet*>& PreviousSpawnedAttributes);` — `UFUNCTION()`
- L1937 _private member_ `FDelegateHandle MonitoredTagChangedDelegateHandle;`
- L1938 _private member_ `FTimerHandle OnRep_ActivateAbilitiesTimerHandle;`
- L1943 _private member_ `FMinimalReplicationTagCountMap ReplicatedLooseTags;` — `UE_DEPRECATED(5.7, "This will be removed in favor of using CountToOwner replication state for on the replicated Tag Count Container")` — `UPROPERTY(Replicated)` — Container used for replicating loose gameplay tags
- L1945 _private member_ `uint8 bDestroyActiveStateInitiated : 1;`
- L1949 _public prototype_ `void CacheIsNetSimulated();` — Caches the flags that indicate whether this component has network authority.
- L1953 _public member_ `FReplicatedPredictionKeyMap ReplicatedPredictionKeyMap;` — `UPROPERTY(Replicated, Transient)` — PredictionKeys, see more info in GameplayPrediction.h. This has to come *last* in all replicated properties on the AbilitySystemComponent to ensure OnRep/callback order.
- L1979 _protected member_ `TArray<FAbilityListLockActiveChange*> AbilityListLockActiveChanges;`
- L1982 _private prototype_ `float PlayMontageInternal(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimMontage* Montage, float InPlayRate, FName StartSectionName, float StartTimeSeconds, TFunctionRef<void(FGameplayAbilityRepAnimMontage&)> MutateRepAnimMontageFunction);`
- L1987 _protected prototype_ `virtual void PrePredictionActivation(const UGameplayAbility* Ability);` — Called before activation for LocalPredicted Ability to execute CharacterMovementComponent->FlushServerMoves When overriding make sure to include Super::PrePredictionActivation(Ability)

#### struct `UAbilitySystemComponent::FPendingAbilityInfo`  
`struct FPendingAbilityInfo`  
_L307-326_
- desc: A pending activation that cannot be activated yet, will be rechecked at a later point
- L309 _public function_ `bool operator==(const FPendingAbilityInfo& Other) const`
- L316 _public member_ `FGameplayAbilitySpecHandle Handle;` — Properties of the ability that needs to be activated
- L317 _public member_ `FPredictionKey PredictionKey;`
- L318 _public member_ `FGameplayEventData TriggerEventData;`
- L321 _public member_ `bool bPartiallyActivated;` — True if this ability was activated remotely and needs to follow up, false if the ability hasn't been activated at all yet
- L323 _public function_ `FPendingAbilityInfo() : bPartiallyActivated(false)`

#### struct `UAbilitySystemComponent::FAbilitySystemComponentDebugInfo`  
`struct FAbilitySystemComponentDebugInfo`  
_L1207-1234_
- L1209 _public function_ `FAbilitySystemComponentDebugInfo()`
- L1214 _public member_ `class UCanvas* Canvas;`
- L1216 _public member_ `bool bPrintToLog;`
- L1218 _public member_ `bool bShowAttributes;`
- L1219 _public member_ `bool bShowGameplayEffects;`
- L1220 _public member_ `bool bShowAbilities;`
- L1222 _public member_ `float XPos;`
- L1223 _public member_ `float YPos;`
- L1224 _public member_ `float OriginalX;`
- L1225 _public member_ `float OriginalY;`
- L1226 _public member_ `float MaxY;`
- L1227 _public member_ `float NewColumnYPadding;`
- L1228 _public member_ `float YL;`
- L1230 _public member_ `bool Accumulate;`
- L1231 _public member_ `TArray<FString> Strings;`
- L1233 _public member_ `int32 GameFlags;` — arbitrary flags for games to set/read in Debug_Internal

#### struct `UAbilitySystemComponent::FAbilityListLockActiveChange`  
`struct FAbilityListLockActiveChange`  
_L1957-1977_
- L1959 _public function_ `FAbilityListLockActiveChange(UAbilitySystemComponent& InAbilitySystemComp, TArray<FGameplayAbilitySpec, TInlineAllocator<2> >& PendingAdds, TArray<FGameplayAbilitySpecHandle, TInlineAllocator<2> >& PendingRemoves) : AbilitySystemComp(InAbilitySystemComp), Adds(MoveTemp(PendingAdds)), Removes(MoveTemp(PendingRemoves))`
- L1969 _public function_ `~FAbilityListLockActiveChange()`
- L1974 _public member_ `UAbilitySystemComponent& AbilitySystemComp;`
- L1975 _public member_ `TArray<FGameplayAbilitySpec, TInlineAllocator<2> > Adds;`
- L1976 _public member_ `TArray<FGameplayAbilitySpecHandle, TInlineAllocator<2> > Removes;`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L62 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FTargetingRejectedConfirmation, int32);` — Called when a targeting actor rejects target confirmation
- L62 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FTargetingRejectedConfirmation, int32);` — Called when a targeting actor rejects target confirmation
- L65 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityFailedDelegate, const UGameplayAbility*, const FGameplayTagContainer&);` — Called when ability fails to activate, passes along the failed ability and a tag explaining why
- L65 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityFailedDelegate, const UGameplayAbility*, const FGameplayTagContainer&);` — Called when ability fails to activate, passes along the failed ability and a tag explaining why
- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityEnded, UGameplayAbility*);` — Called when ability ends
- L68 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAbilityEnded, UGameplayAbility*);` — Called when ability ends
- L71 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitySpecDirtied, const FGameplayAbilitySpec&);` — Notify interested parties that ability spec has been modified
- L71 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitySpecDirtied, const FGameplayAbilitySpec&);` — Notify interested parties that ability spec has been modified
- L74 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FImmunityBlockGE, const FGameplayEffectSpec& , const FActiveGameplayEffect* );` — Notifies when GameplayEffectSpec is blocked by an ActiveGameplayEffect due to immunity
- L74 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FImmunityBlockGE, const FGameplayEffectSpec& , const FActiveGameplayEffect* );` — Notifies when GameplayEffectSpec is blocked by an ActiveGameplayEffect due to immunity
- L77 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGameplayEffectApplicationQuery, const FActiveGameplayEffectsContainer& , const FGameplayEffectSpec& );` — We allow a list of delegates to decide if the application of a Gameplay Effect can be blocked. If it's blocked, it will call the ImmunityBlockGE above
- L77 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FGameplayEffectApplicationQuery, const FActiveGameplayEffectsContainer& , const FGameplayEffectSpec& );` — We allow a list of delegates to decide if the application of a Gameplay Effect can be blocked. If it's blocked, it will call the ImmunityBlockGE above
- L114 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityAbilityKey, int32, InputID);` — Used to register callbacks to ability-key input
- L117 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityConfirmOrCancel);` — Used to register callbacks to confirm/cancel input
- L120 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnGameplayEffectAppliedDelegate, UAbilitySystemComponent*, const FGameplayEffectSpec&, FActiveGameplayEffectHandle);` — Delegate for when an effect is applied

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemDebugHUD.h` (Public)


#### enum `EAlignHorizontal::Type`  
`enum Type`  
_L20-25_
- L22 _public enumerator_ `Left`
- L23 _public enumerator_ `Center`
- L24 _public enumerator_ `Right`

#### enum `EAlignVertical::Type`  
`enum Type`  
_L30-35_
- L32 _public enumerator_ `Top`
- L33 _public enumerator_ `Center`
- L34 _public enumerator_ `Bottom`

#### class `UAbilitySystemDebugHUDExtension`  
`class UAbilitySystemDebugHUDExtension : public UObject`  
_L43-60_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: An extension for the Ability System debug HUD Extensions should be used for displaying information on screen for each Ability System Actor
- L50 _public function_ `virtual bool IsEnabled() const` — Returns whether this extension should be rendered for each actor
- L59 _public function_ `virtual void GetDebugStrings(const AActor* Actor, const UAbilitySystemComponent* Comp, OUT TArray<FString>& OutDebugStrings) const` — Builds an array of strings to render for Ability System actor @param Actor	The avatar actor for the ability system component @param Comp	The Ability System Component being debugged @param OutDebugStrings	Array to fill with debug strings

#### class `UAbilitySystemDebugHUDExtension_Tags`  
`class UAbilitySystemDebugHUDExtension_Tags final : public UAbilitySystemDebugHUDExtension`  
_L66-83_
- reflection: `UCLASS()`
- inherits: `UAbilitySystemDebugHUDExtension`
- desc: Ability System Debug HUD extension for drawing all owned tags by an actor
- L70 _private member_ `TSet<FString> TagsToDisplay;`
- L72 _private member_ `bool bEnabled;`
- L76 _public prototype_ `static void ToggleExtension(const TArray<FString>& Args, UWorld* World);`
- L79 _public prototype_ `bool IsEnabled() const override;`
- L80 _public prototype_ `void GetDebugStrings(const AActor* Actor, const UAbilitySystemComponent* Comp, OUT TArray<FString>& OutDebugStrings) const override;`

#### class `UAbilitySystemDebugHUDExtension_Attributes`  
`class UAbilitySystemDebugHUDExtension_Attributes final : public UAbilitySystemDebugHUDExtension`  
_L89-108_
- reflection: `UCLASS()`
- inherits: `UAbilitySystemDebugHUDExtension`
- desc: Ability System Debug HUD extension for drawing attributes of an actor
- L93 _private member_ `TSet<FString> AttributesToDisplay;`
- L95 _private member_ `bool bIncludeModifiers;`
- L97 _public prototype_ `static void ToggleExtension(const TArray<FString>& Args, UWorld* World);`
- L99 _public prototype_ `static void ToggleIncludeModifiers();`
- L101 _public prototype_ `static void ClearDisplayedAttributes(const TArray<FString>& Args, UWorld* World);`
- L104 _public prototype_ `bool IsEnabled() const override;`
- L105 _public prototype_ `void GetDebugStrings(const AActor* Actor, const UAbilitySystemComponent* Comp, OUT TArray<FString>& OutDebugStrings) const override;`

#### class `UAbilitySystemDebugHUDExtension_BlockedAbilityTags`  
`class UAbilitySystemDebugHUDExtension_BlockedAbilityTags final : public UAbilitySystemDebugHUDExtension`  
_L114-131_
- reflection: `UCLASS()`
- inherits: `UAbilitySystemDebugHUDExtension`
- desc: Ability System Debug HUD extension for drawing all blocked ability tags on an actor
- L118 _private member_ `TSet<FString> TagsToDisplay;`
- L120 _private member_ `bool bEnabled;`
- L124 _public prototype_ `static void ToggleExtension(const TArray<FString>& Args, UWorld* World);`
- L127 _public prototype_ `bool IsEnabled() const override;`
- L128 _public prototype_ `void GetDebugStrings(const AActor* Actor, const UAbilitySystemComponent* Comp, OUT TArray<FString>& OutDebugStrings) const override;`

#### class `AAbilitySystemDebugHUD`  
`class AAbilitySystemDebugHUD : public AHUD`  
_L134-182_
- reflection: `UCLASS()`
- inherits: `AHUD`
- L140 _public prototype_ `static void ToggleBasicHUD(const TArray<FString>& Args, UWorld* World);`
- L148 _public prototype_ `static void NotifyExtensionEnableChanged(UWorld* InWorld);` — Notifies the AbilitySystemDebugHUD that an extension has been enabled/disabled This will create the HUD if it did not exist and there are any extensions enabled or destroy the HUD if it did exist and there are no extensions enabled
- L154 _public prototype_ `static void RegisterHUDClass(TSubclassOf<AAbilitySystemDebugHUD> InHUDClass);` — Replaces the AbilitySystemDebugHUD with a user class NOTE: Only one AbilitySystemDebugHUD class can be active at a time.
- L156 _public prototype_ `void DrawDebugHUD(UCanvas* Canvas, APlayerController* PC);` — main HUD update loop
- L161 _protected prototype_ `virtual bool ShouldDisplayDebugForActor(UCanvas* InCanvas, const AActor* Actor, const FVector& CameraPosition, const FVector& CameraDir) const;` — Returns whether debug information should be drawn for a given actor
- L164 _private prototype_ `static void CreateHUD(UWorld* World);`
- L166 _private prototype_ `void DrawWithBackground(UFont* InFont, const FString& Text, const FColor& TextColor, EAlignHorizontal::Type HAlign, float& OffsetX, EAlignVertical::Type VAlign, float& OffsetY, float Alpha = 1.f);`
- L168 _private prototype_ `void DisplayDebugStrings(UCanvas* InCanvas, const AActor* Actor, const TArray<FString>& DebugStrings, const FVector& CameraPosition, const FVector& CameraDir, float& VerticalOffset) const;`
- L170 _private prototype_ `void DrawDebugAbilitySystemComponent(UAbilitySystemComponent* Component);`
- L172 _private prototype_ `void DrawAbilityDebugInfo(UCanvas* Canvas, APlayerController* PC) const;`
- L176 _private member_ `static bool bEnableBasicHUD;`
- L178 _private member_ `static TSubclassOf<AAbilitySystemDebugHUD> HUDClass;`
- L180 _private member_ `static FDelegateHandle DrawDebugDelegateHandle;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L18 _namespace_ `namespace EAlignHorizontal`
- L28 _namespace_ `namespace EAlignVertical`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemGlobals.h` (Public)


#### struct `FNetSerializeScriptStructCache`  
`struct FNetSerializeScriptStructCache`  
_L29-52_
- reflection: `USTRUCT()`
- desc: Container for safely replicating  script struct references (constrained to a specified parent struct)
- L33 _public prototype_ `void InitForType(UScriptStruct* InScriptStruct);`
- L35 _public function_ `void SetInitDirty()`
- L40 _public prototype_ `void RemoveInPackages(TConstArrayView<UPackage*>);`
- L43 _public prototype_ `bool NetSerialize(FArchive& Ar, UScriptStruct*& Struct);` — Serializes reference to given script struct (must be in the cache)
- L46 _public member_ `TArray<TObjectPtr<UScriptStruct>> ScriptStructs;` — `UPROPERTY()`
- L49 _public member_ `TObjectPtr<UScriptStruct> BaseStructType;` — `UPROPERTY()`
- L51 _public member_ `bool bIsInitDirty = false;`

#### class `UAbilitySystemGlobals`  
`class UAbilitySystemGlobals : public UObject`  
_L57-430_
- reflection: `UCLASS(config = Game, MinimalAPI)`
- inherits: `UObject`
- desc: Holds global data for the ability system. Configuration is done via the Developer Settings, Project -> Gameplay Abilities Settings
- L64 _private function_ `static UAbilitySystemGlobals& Get()` — Gets the single instance of the globals object, will create it as necessary
- L69 _private prototype_ `virtual void InitGlobalData();` — Will be called once on first use to load global data tables and tags (see FGameplayAbilitiesModule::GetAbilitySystemGlobals)
- L72 _private prototype_ `bool IsAbilitySystemGlobalsInitialized() const;` — Returns true if InitGlobalData has been called
- L75 _private prototype_ `bool ShouldUseDebugTargetFromHud();` — Returns true if we should use debug target from the HUD
- L78 _private prototype_ `UCurveTable* GetGlobalCurveTable();` — Returns the globally registered curve table
- L81 _private prototype_ `UDataTable* GetGlobalAttributeMetaDataTable();` — Returns the data table defining attribute metadata (NOTE: Currently not in use)
- L84 _private prototype_ `FAttributeSetInitter* GetAttributeSetInitter() const;` — Returns data used to initialize attributes to their default values
- L87 _private prototype_ `static UAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent=true);` — Searches the passed in actor for an ability system component, will use IAbilitySystemInterface or fall back to a component search
- L90 _private prototype_ `virtual FGameplayAbilityActorInfo* AllocAbilityActorInfo() const;` — Should allocate a project specific AbilityActorInfo struct. Caller is responsible for deallocation
- L93 _private prototype_ `virtual FGameplayEffectContext* AllocGameplayEffectContext() const;` — Should allocate a project specific GameplayEffectContext struct. Caller is responsible for deallocation
- L96 _private prototype_ `virtual void GlobalPreGameplayEffectSpecApply(FGameplayEffectSpec& Spec, UAbilitySystemComponent* AbilitySystemComponent);` — Global callback that can handle game-specific code that needs to run before applying a gameplay effect spec
- L99 _private function_ `virtual void PushCurrentAppliedGE(const FGameplayEffectSpec* Spec, UAbilitySystemComponent* AbilitySystemComponent)` — Override to handle global state when gameplay effects are being applied
- L100 _private function_ `virtual void SetCurrentAppliedGE(const FGameplayEffectSpec* Spec)`
- L101 _private function_ `virtual void PopCurrentAppliedGE()`
- L104 _private prototype_ `bool ShouldPredictTargetGameplayEffects() const;` — Returns true if the ability system should try to predict gameplay effects applied to non local targets
- L107 _private prototype_ `bool ShouldReplicateActivationOwnedTags() const;` — Returns true if tags granted to owners from ability activations should be replicated
- L110 _private prototype_ `UFunction* GetGameplayCueFunction(const FGameplayTag &Tag, UClass* Class, FName &MatchedTag);` — Searches the passed in class to look for a UFunction implementing the gameplay cue tag, sets MatchedTag to the exact tag found
- L113 _private prototype_ `virtual UGameplayCueManager* GetGameplayCueManager();` — Returns the gameplay cue manager singleton object, creating if necessary
- L116 _private prototype_ `UGameplayTagReponseTable* GetGameplayTagResponseTable();` — Returns the gameplay tag response object, creating if necessary
- L119 _private prototype_ `static bool DeriveGameplayCueTagFromAssetName(FString AssetName, FGameplayTag& GameplayCueTag, FName& GameplayCueName);` — Sets a default gameplay cue tag using the asset's name. Returns true if it changed the tag.
- L123 _private function_ `template<class T> static void DeriveGameplayCueTagFromClass(T* CDO)` — Sets a default gameplay cue tag using the asset's class
- L149 _private function_ `virtual void GameplayEffectPostEditChangeProperty(class UGameplayEffect* GE, FPropertyChangedEvent& PropertyChangedEvent)` — Allows projects to override PostEditChangeProeprty on GEs without having to subclass Gameplayeffect. Intended for validation/auto populating based on changed data.
- L155 _private member_ `FSoftClassPath AbilitySystemGlobalsClassName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->AbilitySystemGlobalsClassName to access this variable in code")` — `UPROPERTY(config)` — The class to instantiate as the globals object. Defaults to this class but can be overridden
- L157 _private function_ `void AutomationTestOnly_SetGlobalAttributeDataTable(UDataTable *InTable)`
- L165 _private prototype_ `bool ShouldIgnoreCooldowns() const;` — Returns true if ability cooldowns are ignored, returns false otherwise. Always returns false in shipping builds.
- L168 _private prototype_ `bool ShouldIgnoreCosts() const;` — Returns true if ability costs are ignored, returns false otherwise. Always returns false in shipping builds.
- L171 _private prototype_ `DECLARE_MULTICAST_DELEGATE(FOnClientServerDebugAvailable);` — Called when debug strings are available, to write them to the display
- L172 _private member_ `FOnClientServerDebugAvailable OnClientServerDebugAvailable;`
- L175 _private member_ `TArray<FString> AbilitySystemDebugStrings;` — Global place to accumulate debug strings for ability system component. Used when we fill up client side debug string immediately, and then wait for server to send server strings
- L179 _private member_ `bool bUseDebugTargetFromHud;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->bUseDebugTargetFromHud to access this variable in code")` — Set to true if you want the "ShowDebug AbilitySystem" cheat to use the hud's debug target instead of the ability system's debug target.
- L182 _private prototype_ `static void NonShipping_ApplyGlobalAbilityScaler_Rate(float& Rate);` — Helper functions for applying global scaling to various ability system tasks. This isn't meant to be a shipping feature, but to help with debugging and interation via cvar AbilitySystem.GlobalAbilityScale
- L183 _private prototype_ `static void NonShipping_ApplyGlobalAbilityScaler_Duration(float& Duration);`
- L190 _private member_ `FGameplayTag ActivateFailIsDeadTag;` — `UE_DEPRECATED(5.5, "This variable is not used in the codebase")` — `UPROPERTY()` — TryActivate failed due to being dead
- L194 _private member_ `FName ActivateFailIsDeadName;` — `UE_DEPRECATED(5.5, "This variable is not used in the codebase")` — `UPROPERTY(config)`
- L198 _private member_ `FGameplayTag ActivateFailCooldownTag;` — `UPROPERTY()` — TryActivate failed due to being on cooldown
- L202 _private member_ `FName ActivateFailCooldownName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings (it will map to ActivateFailCooldownTag)")` — `UPROPERTY(config)`
- L206 _private member_ `FGameplayTag ActivateFailCostTag;` — `UPROPERTY()` — TryActivate failed due to not being able to spend costs
- L210 _private member_ `FName ActivateFailCostName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings (it will map to ActivateFailCostTag)")` — `UPROPERTY(config)`
- L214 _private member_ `FGameplayTag ActivateFailTagsBlockedTag;` — `UPROPERTY()` — TryActivate failed due to being blocked by other abilities
- L218 _private member_ `FName ActivateFailTagsBlockedName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings (it will map to ActivateFailTagsBlockedTag)")` — `UPROPERTY(config)`
- L222 _private member_ `FGameplayTag ActivateFailTagsMissingTag;` — `UPROPERTY()` — TryActivate failed due to missing required tags
- L226 _private member_ `FName ActivateFailTagsMissingName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings (it will map to ActivateFailTagsMissingTag)")` — `UPROPERTY(config)`
- L230 _private member_ `FGameplayTag ActivateFailNetworkingTag;` — `UPROPERTY()` — Failed to activate due to invalid networking settings, this is designer error
- L234 _private member_ `FName ActivateFailNetworkingName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings (it will map to ActivateFailNetworkingTag)")` — `UPROPERTY(config)`
- L239 _private member_ `int32 MinimalReplicationTagCountBits;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->MinimalReplicationTagCountBits to access this variable in code")` — `UPROPERTY(config)` — How many bits to use for "number of tags" in FMinimalReplicationTagCountMap::NetSerialize.
- L242 _private prototype_ `virtual void InitGlobalTags();` — Initialize global tags by reading from config using the names and creating tags for use at runtime
- L244 _private prototype_ `void InitTargetDataScriptStructCache();`
- L247 _private prototype_ `virtual void InitGameplayCueParameters(FGameplayCueParameters& CueParameters, const FGameplayEffectSpecForRPC &Spec);` — Initialize GameplayCue Parameters
- L248 _private prototype_ `virtual void InitGameplayCueParameters_GESpec(FGameplayCueParameters& CueParameters, const FGameplayEffectSpec &Spec);`
- L249 _private prototype_ `virtual void InitGameplayCueParameters(FGameplayCueParameters& CueParameters, const FGameplayEffectContextHandle& EffectContext);`
- L256 _private prototype_ `virtual void StartAsyncLoadingObjectLibraries();` — Trigger async loading of the gameplay cue object libraries. By default, the manager will do this on creation, but that behavior can be changed by a derived class overriding ShouldAsyncLoadObjectLibrariesAtStart and returning false. In that case, this function must be called to begin the load
- L259 _private prototype_ `bool ShouldAllowGameplayModEvaluationChannels() const;` — Simple accessor to whether gameplay modifier evaluation channels should be allowed or not
- L265 _private prototype_ `bool IsGameplayModEvaluationChannelValid(EGameplayModEvaluationChannel Channel) const;` — Returns whether the specified gameplay mod evaluation channel is valid for use or not. Considers whether channel usage is allowed at all, as well as if the specified channel has a valid alias for the game.
- L268 _private prototype_ `const FName& GetGameplayModEvaluationChannelAlias(EGameplayModEvaluationChannel Channel) const;` — Simple channel-based accessor to the alias name for the specified gameplay mod evaluation channel, if any
- L271 _private prototype_ `const FName& GetGameplayModEvaluationChannelAlias(int32 Index) const;` — Simple index-based accessor to the alias name for the specified gameplay mod evaluation channel, if any
- L274 _private prototype_ `virtual TArray<FString> GetGameplayCueNotifyPaths();` — Path where the engine will load gameplay cue notifies from
- L277 _private prototype_ `virtual void AddGameplayCueNotifyPath(const FString& InPath);` — Add a path to the GameplayCueNotifyPaths array.
- L284 _private prototype_ `virtual int32 RemoveGameplayCueNotifyPath(const FString& InPath);` — Remove the given gameplay cue notify path from the GameplayCueNotifyPaths array. @return Number of paths removed.
- L287 _private member_ `FNetSerializeScriptStructCache TargetDataStructCache;` — `UPROPERTY()`
- L290 _private member_ `FNetSerializeScriptStructCache EffectContextStructCache;` — `UPROPERTY()`
- L292 _private prototype_ `void AddAttributeDefaultTables(const FName OwnerName, const TArray<FSoftObjectPath>& AttribDefaultTableNames);`
- L293 _private prototype_ `void RemoveAttributeDefaultTables(const FName OwnerName, const TArray<FSoftObjectPath>& AttribDefaultTableNames);`
- L297 _protected prototype_ `virtual TArray<FSoftObjectPath> GetGlobalAttributeSetDefaultsTablePaths() const;` — Get the SoftObjectPaths for all tables that should be loaded for default Attribute values
- L299 _protected prototype_ `virtual void InitAttributeDefaults();`
- L300 _protected prototype_ `virtual void ReloadAttributeDefaults();`
- L301 _protected prototype_ `virtual void AllocAttributeSetInitter();`
- L306 _protected member_ `bool bAllowGameplayModEvaluationChannels;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->bAllowGameplayModEvaluationChannels to access this variable in code")` — `UPROPERTY(config)` — Whether the game should allow the usage of gameplay mod evaluation channels or not
- L311 _protected member_ `EGameplayModEvaluationChannel DefaultGameplayModEvaluationChannel;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->DefaultGameplayModEvaluationChannel to access this variable in code")` — `UPROPERTY(config)` — The default mod evaluation channel for the game
- L316 _protected member_ `FName GameplayModEvaluationChannelAliases[static_cast<int32>(EGameplayModEvaluationChannel::Channel_MAX)];` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->GameplayModEvaluationChannelAliases to access this variable in code")` — `UPROPERTY(config)` — Game-specified named aliases for gameplay mod evaluation channels; Only those with valid aliases are eligible to be used in a game (except Channel0, which is always valid)
- L321 _protected member_ `FSoftObjectPath GlobalCurveTableName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->GlobalCurveTableName to access this variable in code")` — `UPROPERTY(config)` — Name of global curve table to use as the default for scalable floats, etc.
- L324 _protected member_ `TObjectPtr<UCurveTable> GlobalCurveTable;` — `UPROPERTY()`
- L329 _protected member_ `FSoftObjectPath GlobalAttributeMetaDataTableName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->GlobalAttributeMetaDataTableName to access this variable in code")` — `UPROPERTY(config)` — Holds information about the valid attributes' min and max values and stacking rules
- L332 _protected member_ `TObjectPtr<UDataTable> GlobalAttributeMetaDataTable;` — `UPROPERTY()`
- L337 _protected member_ `FSoftObjectPath GlobalAttributeSetDefaultsTableName;` — `UE_DEPRECATED(5.5, "See GetGlobalAttributeSetDefaultsTablePaths() which is an array rather than this version (singular)")` — `UPROPERTY(config)` — Holds default values for attribute sets, keyed off of Name/Levels. NOTE: Preserved for backwards compatibility, should use the array version below now
- L342 _protected member_ `TArray<FSoftObjectPath> GlobalAttributeSetDefaultsTableNames;` — `UE_DEPRECATED(5.5, "Set this variable through the Project Settings and use GetGlobalAttributeSetDefaultsTablePaths() to access this variable in code")` — `UPROPERTY()` — Array of curve table names to use for default values for attribute sets, keyed off of Name/Levels
- L346 _protected member_ `TArray<TObjectPtr<UCurveTable>> GlobalAttributeDefaultsTables;` — `UPROPERTY()` — Curve tables containing default values for attribute sets, keyed off of Name/Levels
- L351 _protected member_ `FSoftObjectPath GlobalGameplayCueManagerClass;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->GlobalGameplayCueManagerClass to access this variable in code")` — `UPROPERTY(config)` — Class reference to gameplay cue manager. Use this if you want to just instantiate a class for your gameplay cue manager without having to create an asset.
- L356 _protected member_ `FSoftObjectPath GlobalGameplayCueManagerName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->GlobalGameplayCueManagerName to access this variable in code")` — `UPROPERTY(config)` — Object reference to gameplay cue manager (E.g., reference to a specific blueprint of your GameplayCueManager class. This is not necessary unless you want to have data or blueprints in your gameplay cue manager.
- L361 _protected member_ `TArray<FString> GameplayCueNotifyPaths;` — `UE_DEPRECATED(5.5, "This will be moved to private. Use GetGameplayCueNotifyPaths, AddGameplayCueNotifyPath, or RemoveGameplayCueNotifyPath")` — `UPROPERTY(config)` — Look in these paths for GameplayCueNotifies. These are your "always loaded" set.
- L366 _protected member_ `FSoftObjectPath GameplayTagResponseTableName;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->GameplayTagResponseTableName to access this variable in code")` — `UPROPERTY(config)` — The class to instantiate as the GameplayTagResponseTable.
- L369 _protected member_ `TObjectPtr<UGameplayTagReponseTable> GameplayTagResponseTable;` — `UPROPERTY()`
- L371 _protected member_ `bool bInitialized = false;`
- L376 _protected member_ `bool PredictTargetGameplayEffects;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->PredictTargetGameplayEffects to access this variable in code")` — `UPROPERTY(config)` — Set to true if you want clients to try to predict gameplay effects done to targets. If false it will only predict self effects
- L384 _protected member_ `bool ReplicateActivationOwnedTags;` — `UE_DEPRECATED(5.5, "Configure this variable through the Project Settings and use GetDefault<UGameplayAbilitiesDeveloperSettings>()->ReplicateActivationOwnedTags to access this variable in code")` — `UPROPERTY(config)` — Set to true if you want tags granted to owners from ability activations to be replicated. If false, ActivationOwnedTags are only applied locally. This should only be disabled for legacy game code that depends on non-replication of ActivationOwnedTags.
- L388 _protected member_ `TObjectPtr<UGameplayCueManager> GlobalGameplayCueManager;` — `UPROPERTY()` — Manager for all gameplay cues
- L391 _protected member_ `TSharedPtr<FAttributeSetInitter> GlobalAttributeSetInitter;` — Used to initialize attribute sets
- L397 _protected member_ `TMap<FSoftObjectPath, TArray<FName>> GlobalAttributeSetDefaultsTableNamesWithOwners;` — Curve table names to use for default values for attribute sets, keyed off of Name/Levels (with owners to allow removal of hard reference by GlobalAttributeDefaultsTables) Required to allow unloading of plugins
- L400 _protected prototype_ `template <class T> T* InternalGetLoadTable(T*& Table, FString TableName);`
- L402 _protected prototype_ `void OnAttributeDefaultTableChanged();`
- L405 _protected prototype_ `void OnTableReimported(UObject* InObject);`
- L406 _protected prototype_ `void OnPreBeginPIE(const bool bIsSimulatingInEditor);`
- L409 _protected prototype_ `static void ResetCachedData();`
- L410 _protected prototype_ `void HandlePreLoadMap(const FWorldContext& WorldContext, const FString& MapName);`
- L413 _protected member_ `bool RegisteredReimportCallback;`
- L417 _private prototype_ `void PerformDeveloperSettingsUpgrade();`
- L419 _private member_ `FDelegateHandle ModulesChangedHandle;`
- L420 _private member_ `FDelegateHandle ModulesUnloadedHandle;`
- L424 _public prototype_ `void Notify_OpenAssetInEditor(FString AssetName, int AssetType);` — To add functionality for opening assets directly from the game.
- L425 _public member_ `FOnAbilitySystemAssetOpenedDelegate AbilityOpenAssetInEditorCallbacks;`
- L428 _public prototype_ `void Notify_FindAssetInEditor(FString AssetName, int AssetType);` — ...for finding assets directly from the game.
- L429 _public member_ `FOnAbilitySystemAssetFoundDelegate AbilityFindAssetInEditorCallbacks;`

#### struct `FScopeCurrentGameplayEffectBeingApplied`  
`struct FScopeCurrentGameplayEffectBeingApplied`  
_L433-443_
- desc: Scope object that indicates when a gameplay effect is being applied
- L435 _public function_ `FScopeCurrentGameplayEffectBeingApplied(const FGameplayEffectSpec* Spec, UAbilitySystemComponent* AbilitySystemComponent)`
- L439 _public function_ `~FScopeCurrentGameplayEffectBeingApplied()`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L24 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilitySystemAssetOpenedDelegate, FString , int );` — Called when ability fails to activate, passes along the failed ability and a tag explaining why
- L24 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilitySystemAssetOpenedDelegate, FString , int );` — Called when ability fails to activate, passes along the failed ability and a tag explaining why
- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilitySystemAssetFoundDelegate, FString, int);`
- L25 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAbilitySystemAssetFoundDelegate, FString, int);`
- L171 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnClientServerDebugAvailable);` — Called when debug strings are available, to write them to the display

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemInterface.h` (Public)


#### class `UAbilitySystemInterface`  
`class UAbilitySystemInterface : public UInterface`  
_L20-23_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for native actors to expose access to an ability system component. This is used by native actors to efficiently return a component and handle more complicated cases. This interface should never be called directly, instead call GetAbilitySystemComponentFromActor or GetAbilitySystemComponent on the AbilitySystemBlueprintLibrary as that also handles looking up by component type.

#### class `IAbilitySystemInterface`  
`class IAbilitySystemInterface`  
_L25-31_
- L30 _private prototype_ `virtual UAbilitySystemComponent* GetAbilitySystemComponent() const = 0;` — Returns the ability system component to use for this actor. It may live on another actor, such as a Pawn using the PlayerState's component

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemLog.h` (Public)


#### Free symbols / members of external scopes

- L16 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAbilitySystem, Display, All);`
- L17 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(VLogAbilitySystem, Display, All);`
- L18 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayEffects, Display, All);`
- L23 _macro_ `#define ABILITY_LOG(Verbosity, Format, ...) \` — Without logging enabled we pass ability system through to UE_LOG which only handles Fatal verbosity in NO_LOGGING
- L28 _macro_ `#define ABILITY_VLOG(Actor, Verbosity, Format, ...) \`
- L53 _macro_ `#define ABILITY_VLOG_ATTRIBUTE_GRAPH(Actor, Verbosity, AttributeName, OldValue, NewValue) \`
- L69 _macro_ `#define ABILITY_VLOG_ATTRIBUTE_GRAPH(Actor, Verbosity, AttributeName, OldValue, NewValue)`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemReplicationProxyInterface.h` (Public)


#### class `UAbilitySystemReplicationProxyInterface`  
`class UAbilitySystemReplicationProxyInterface : public UInterface`  
_L23-26_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for actors that act like an ability system component for replication. This can be used to group together different components for replication

#### class `IAbilitySystemReplicationProxyInterface`  
`class IAbilitySystemReplicationProxyInterface`  
_L28-73_
- L32 _private prototype_ `virtual void ForceReplication() = 0;`
- L39 _private prototype_ `virtual void Call_InvokeGameplayCueExecuted_FromSpec(const FGameplayEffectSpecForRPC Spec, FPredictionKey PredictionKey);`
- L40 _private prototype_ `virtual void Call_InvokeGameplayCueExecuted(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext);`
- L41 _private prototype_ `virtual void Call_InvokeGameplayCuesExecuted(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext);`
- L42 _private prototype_ `virtual void Call_InvokeGameplayCueExecuted_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters);`
- L43 _private prototype_ `virtual void Call_InvokeGameplayCuesExecuted_WithParams(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters);`
- L44 _private prototype_ `virtual void Call_InvokeGameplayCueAdded(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext);`
- L45 _private prototype_ `virtual void Call_InvokeGameplayCueAdded_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters Parameters);`
- L46 _private prototype_ `virtual void Call_InvokeGameplayCueAddedAndWhileActive_FromSpec(const FGameplayEffectSpecForRPC& Spec, FPredictionKey PredictionKey);`
- L47 _private prototype_ `virtual void Call_InvokeGameplayCueAddedAndWhileActive_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters);`
- L48 _private prototype_ `virtual void Call_InvokeGameplayCuesAddedAndWhileActive_WithParams(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters);`
- L54 _private prototype_ `virtual void NetMulticast_InvokeGameplayCueExecuted_FromSpec(const FGameplayEffectSpecForRPC Spec, FPredictionKey PredictionKey) = 0;`
- L56 _private prototype_ `virtual void NetMulticast_InvokeGameplayCueExecuted(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext) = 0;`
- L58 _private prototype_ `virtual void NetMulticast_InvokeGameplayCuesExecuted(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext) = 0;`
- L60 _private prototype_ `virtual void NetMulticast_InvokeGameplayCueExecuted_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) = 0;`
- L62 _private prototype_ `virtual void NetMulticast_InvokeGameplayCuesExecuted_WithParams(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) = 0;`
- L64 _private prototype_ `virtual void NetMulticast_InvokeGameplayCueAdded(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext) = 0;`
- L66 _private prototype_ `virtual void NetMulticast_InvokeGameplayCueAdded_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters Parameters) = 0;`
- L68 _private prototype_ `virtual void NetMulticast_InvokeGameplayCueAddedAndWhileActive_FromSpec(const FGameplayEffectSpecForRPC& Spec, FPredictionKey PredictionKey) = 0;`
- L70 _private prototype_ `virtual void NetMulticast_InvokeGameplayCueAddedAndWhileActive_WithParams(const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) = 0;`
- L72 _private prototype_ `virtual void NetMulticast_InvokeGameplayCuesAddedAndWhileActive_WithParams(const FGameplayTagContainer GameplayCueTags, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters) = 0;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemStats.h` (Public)


#### Free symbols / members of external scopes

- L8 _delegate_ `DECLARE_STATS_GROUP(TEXT("AbilitySystem"), STATGROUP_AbilitySystem, STATC`
- L10 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GameplayEffectsHasAllTagsTime"), STAT_GameplayEffectsHasAllTags`
- L11 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GameplayEffectsHasAnyTagTime"), STAT_GameplayEffectsHasAnyTag,`
- L12 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GameplayEffectsGetOwnedTags"), STAT_GameplayEffectsGetOwnedTags,`
- L13 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GameplayEffectsTick"), STAT_GameplayEffectsTick, STATGROU`
- L14 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("CanApplyAttributeModifiers"), STAT_GameplayEffectsCanApplyAttributeModifiers, S`
- L15 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetActiveEffectsData"), STAT_GameplayEffectsGetActiveEffectsTimeRemaining, STATGRO`
- L16 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetActiveEffectsData"), STAT_GameplayEffectsGetActiveEffectsDuration, STATGRO`
- L17 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetActiveEffectsData"), STAT_GameplayEffectsGetActiveEffectsTimeRemainingAndDuration, STATGRO`
- L18 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetActiveEffectsData"), STAT_GameplayEffectsGetActiveEffects, STATGRO`
- L19 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetActiveEffectsData"), STAT_GameplayEffectsGetAllActiveEffectHandles, STATGRO`
- L20 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("SetActiveEffectsData"), STAT_GameplayEffectsModifyActiveEffectStartTime, STATGRO`
- L21 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetCooldownTimeRemaining"), STAT_GameplayAbilityGetCooldownTimeRemaining, STA`
- L22 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetCooldownTimeRemaining"), STAT_GameplayAbilityGetCooldownTimeRemainingAndDuration, STA`
- L23 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("RemoveActiveGameplayEffect"), STAT_RemoveActiveGameplayEffect, S`
- L24 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ApplyGameplayEffectSpec"), STAT_ApplyGameplayEffectSpec, STAT`
- L25 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetGameplayCueFunction"), STAT_GetGameplayCueFunction, STATG`
- L26 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GetOutgoingSpec"), STAT_GetOutgoingSpec, STATGROUP_Ab`
- L27 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("InitAttributeSetDefaults"), STAT_InitAttributeSetDefaults, STA`
- L28 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("TickAbilityTasks"), STAT_TickAbilityTasks, STATGROUP_A`
- L29 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("FindAbilitySpecFromHandle"), STAT_FindAbilitySpecFromHandle, ST`
- L30 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Aggregator Evaluate"), STAT_AggregatorEvaluate, STATGROU`
- L31 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Aggregator BroadcastOnDirty"), STAT_AggregatorBroadcastOnDirty,`
- L32 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Has Application Immunity To Spec"), STAT_HasApplicationImmunityToS`
- L33 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("Has Matching GameplayTag"), STAT_HasMatchingGameplayTag, STA`
- L34 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GameplayCueNotify Static"), STAT_HandleGameplayCueNotifyStatic, STA`
- L35 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GameplayCueNotify Actor"), STAT_HandleGameplayCueNotifyActor, STAT`
- L36 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ApplyGameplayEffectToTarget"), STAT_ApplyGameplayEffectToTarget,`
- L37 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ExecuteActiveEffectsFrom"), STAT_ExecuteActiveEffectsFrom, STA`
- L38 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("InternalExecuteMod"), STAT_InternalExecuteMod, STATGROUP`
- L39 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("PostGameplayEffectExecute"), STAT_PostGameplayEffectExecute, ST`
- L40 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ActiveGameplayEffect Added"), STAT_OnActiveGameplayEffectAdded, S`
- L41 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("ActiveGameplayEffect Removed"), STAT_OnActiveGameplayEffectRemoved,`
- L42 _delegate_ `DECLARE_CYCLE_STAT_EXTERN(TEXT("GameplayCueInterface HandleGameplayCue"), STAT_GameplayCueInterface_HandleGa`
- L44 _delegate_ `DECLARE_DWORD_ACCUMULATOR_STAT_EXTERN(TEXT("AbilityTask Count"), STAT_AbilitySystem_TaskCount, STATGROUP_`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemTestAttributeSet.h` (Public)


#### class `UAbilitySystemTestAttributeSet`  
`class UAbilitySystemTestAttributeSet : public UAttributeSet`  
_L13-77_
- reflection: `UCLASS(Blueprintable, BlueprintType, meta=(HideInDetailsView), MinimalAPI)`
- inherits: `UAttributeSet`
- L25 _private member_ `mutable float MaxHealth;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest", meta = (HideFromModifiers))`
- L28 _private member_ `mutable float Health;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest", meta = (HideFromModifiers))`
- L31 _private member_ `mutable FGameplayAttributeData Mana;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L34 _private member_ `mutable float MaxMana;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L38 _private member_ `mutable float Damage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest")` — This Damage is just used for applying negative health mods. Its not a 'persistent' attribute.
- L42 _private member_ `mutable float SpellDamage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")` — This Attribute is the actual spell damage for this actor. It will power spell based GameplayEffects
- L46 _private member_ `mutable float PhysicalDamage;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")` — This Attribute is the actual physical damage for this actor. It will power physical based GameplayEffects
- L49 _private member_ `mutable float CritChance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L52 _private member_ `mutable float CritMultiplier;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L55 _private member_ `mutable float ArmorDamageReduction;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L58 _private member_ `mutable float DodgeChance;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L61 _private member_ `mutable float LifeSteal;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L64 _private member_ `mutable float Strength;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "AttributeTest")`
- L67 _private member_ `mutable float StackingAttribute1;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest")`
- L70 _private member_ `mutable float StackingAttribute2;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest")`
- L73 _private member_ `mutable float NoStackAttribute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest")`
- L75 _private prototype_ `virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data) override;`
- L76 _private prototype_ `virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemTestPawn.h` (Public)


#### class `AAbilitySystemTestPawn`  
`class AAbilitySystemTestPawn : public ADefaultPawn, public IGameplayCueInterface, public IAbilitySystemInterface`  
_L17-38_
- reflection: `UCLASS(Blueprintable, BlueprintType, notplaceable, MinimalAPI)`
- inherits: `ADefaultPawn,IGameplayCueInterface,IAbilitySystemInterface`
- L21 _private prototype_ `virtual void PostInitializeComponents() override;`
- L23 _private prototype_ `virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;`
- L28 _private member_ `TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;` — `UPROPERTY(Category = AbilitySystem, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))` — DefaultPawn collision component
- L34 _public member_ `static FName AbilitySystemComponentName;`
- L37 _public function_ `class UAbilitySystemComponent* GetAbilitySystemComponent()` — Returns AbilitySystemComponent subobject

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/ActiveGameplayEffectHandle.h` (Public)


#### struct `FActiveGameplayEffectHandle`  
`struct FActiveGameplayEffectHandle`  
_L17-109_
- reflection: `USTRUCT(BlueprintType)`
- desc: This handle is required for things outside of FActiveGameplayEffectsContainer to refer to a specific active GameplayEffect For example if a skill needs to create an active effect and then destroy that specific effect that it created, it has to do so through a handle. a pointer or index into the active list is not sufficient. These are not synchronized between clients and server.
- L22 _public prototype_ `FActiveGameplayEffectHandle() = default;` — Construct an invalid handle typically used to indicate failure of a Gameplay Effect to execute
- L31 _public function_ `FActiveGameplayEffectHandle(int32 InHandle) : Handle(InHandle), bPassedFiltersAndWasExecuted(true)` — `UE_DEPRECATED(5.8, "Use GenerateNewHandle (for properly constructed, valid handle) or GetInstantExecutedHandle (see comments)")` — This constructor has been deprecated since it leaks internal implementation, leaves the Owning ASC undefined, and it's not always clear what the intent of the caller is.  It's been replaced by two factory functions: 1. GenerateNewHandle which will give you a valid, properly constructed Handle 2. GetInstantExecutedHandle which will give you a special handle, deemed to be invalid since it already executed instantly.
- L38 _public prototype_ `static FActiveGameplayEffectHandle GenerateNewHandle(UAbilitySystemComponent* OwningComponent);` — Generates a new handle, it will be set to successfully applied. It is up to the caller to associate it with an FActiveGameplayEffect.
- L48 _public prototype_ `static FActiveGameplayEffectHandle GetInstantExecutedHandle();` — Get a handle that represents an Instant (non-duration) Gameplay Effect. We use this as a sentinel value for FActiveGameplayEffectHandle returned from functions where the underlying GE has already completed execution (instantly) and thus cannot be queried further. Such a handle has the following rules: IsValid() unintuitively returns false, as it does not represent an Active Gameplay Effect. WasSuccessfullyApplied() returns true, as it is assumed this represents the execution of the Instant GE. GetOwningAbilitySystemComponent() returns an undefined value and should not be relied upon.
- L51 _public function_ `bool IsValid() const` — True if this is/was tracking an active (non-instant) gameplay effect. Will continue to return true if the GE was removed.
- L57 _public function_ `bool WasSuccessfullyApplied() const` — True if this applied a gameplay effect. This can be true when it is not valid if it applied an instant effect
- L64 _public prototype_ `UAbilitySystemComponent* GetOwningAbilitySystemComponent() const;` — Returns the ability system component that currently has the ActiveGameplayEffect this handle represents. Note: If the GameplayEffect has been removed, this will return nullptr regardless of where the ActiveGE was applied.
- L67 _public function_ `static void ResetGlobalHandleMap()` — `UE_DEPRECATED(5.8, "We no longer use a global TMap to get the Owning ASC. You can remove this function.")`
- L70 _public function_ `void RemoveFromGlobalMap()` — `UE_DEPRECATED(5.8, "We no longer use a global TMap to get the Owning ASC. You can remove this function.")`
- L72 _public function_ `bool operator==(const FActiveGameplayEffectHandle& Other) const`
- L77 _public function_ `bool operator!=(const FActiveGameplayEffectHandle& Other) const`
- L87 _public function_ `FString ToString() const`
- L93 _public function_ `void Invalidate()` — Reset the handle to a default (invalid) state
- L99 _private prototype_ `FActiveGameplayEffectHandle(UAbilitySystemComponent* InOwningASC);`
- L102 _private member_ `TWeakObjectPtr<UAbilitySystemComponent> WeakOwningASC = {};` — `UPROPERTY()`
- L105 _private member_ `int32 Handle = INDEX_NONE;` — `UPROPERTY()`
- L108 _private member_ `bool bPassedFiltersAndWasExecuted = false;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L82 _function_ `friend uint32 GetTypeHash(const FActiveGameplayEffectHandle& InHandle)`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/ActiveGameplayEffectIterator.h` (Public)


#### class `FActiveGameplayEffectIterator`  
`template< typename ElementType, typename ContainerType > class FActiveGameplayEffectIterator`  
_L22-136_
- L26 _public function_ `FActiveGameplayEffectIterator(const ContainerType& InContainer, int32 StartIdx=0) : index(StartIdx) , Current(nullptr) , Pending(nullptr) , Container(const_cast<ContainerType&>(InContainer))`
- L40 _public function_ `~FActiveGameplayEffectIterator()`
- L46 _public function_ `void operator++()`
- L51 _public function_ `ElementType& operator*() const`
- L57 _public function_ `ElementType* operator->() const`
- L63 _public function_ `explicit operator bool() const`
- L80 _private function_ `inline ElementType* AdvancePending(ElementType** Next)`
- L86 _private function_ `void Next()`
- L103 _private function_ `void UpdateCurrent()`
- L132 _private member_ `int32 index;`
- L133 _private member_ `ElementType* Current;`
- L134 _private member_ `ElementType* Pending;`
- L135 _private member_ `ContainerType& Container;`

#### Free symbols / members of external scopes

- L68 _function_ `friend bool operator==(const FActiveGameplayEffectIterator& Lhs, const FActiveGameplayEffectIterator& Rhs)`
- L73 _function_ `friend bool operator!=(const FActiveGameplayEffectIterator& Lhs, const FActiveGameplayEffectIterator& Rhs)`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AnimNotify_GameplayCue.h` (Public)


#### class `UAnimNotify_GameplayCue`  
`class UAnimNotify_GameplayCue : public UAnimNotify`  
_L19-40_
- reflection: `UCLASS(editinlinenew, Const, hideCategories = Object, collapseCategories, MinimalAPI, Meta = (DisplayName = "GameplayCue (Burst)"))`
- inherits: `UAnimNotify`
- desc: UAnimNotify_GameplayCue An animation notify used for instantaneous gameplay cues (Burst/Latent).
- L25 _public prototype_ `UAnimNotify_GameplayCue();`
- L27 _public prototype_ `virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;`
- L29 _public prototype_ `FString GetNotifyName_Implementation() const override;`
- L32 _public prototype_ `virtual bool CanBePlaced(UAnimSequenceBase* Animation) const override;`
- L39 _protected member_ `FGameplayCueTag GameplayCue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayCue, meta = (Categories = "GameplayCue"))` — GameplayCue tag to invoke.

#### class `UAnimNotify_GameplayCueState`  
`class UAnimNotify_GameplayCueState : public UAnimNotifyState`  
_L49-76_
- reflection: `UCLASS(editinlinenew, Const, hideCategories = Object, collapseCategories, MinimalAPI, Meta = (DisplayName = "GameplayCue (Looping)"))`
- inherits: `UAnimNotifyState`
- desc: UAnimNotify_GameplayCueState An animation notify state used for duration based gameplay cues (Looping).
- L55 _public prototype_ `UAnimNotify_GameplayCueState();`
- L57 _public prototype_ `virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;`
- L58 _public prototype_ `virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;`
- L59 _public prototype_ `virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;`
- L61 _public prototype_ `FString GetNotifyName_Implementation() const override;`
- L64 _public prototype_ `virtual bool CanBePlaced(UAnimSequenceBase* Animation) const override;`
- L71 _protected member_ `FGameplayCueTag GameplayCue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayCue, meta = (Categories = "GameplayCue"))` — GameplayCue tag to invoke
- L74 _protected member_ `FGameplayCueProxyTick PreviewProxyTick;`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AttributeSet.h` (Public)


#### struct `FGameplayAttributeData`  
`struct FGameplayAttributeData`  
_L21-54_
- reflection: `USTRUCT(BlueprintType)`
- desc: Place in an AttributeSet to create an attribute that can be accessed using FGameplayAttribute. It is strongly encouraged to use this instead of raw float attributes
- L24 _public function_ `FGameplayAttributeData() : BaseValue(0.f) , CurrentValue(0.f)`
- L29 _public function_ `FGameplayAttributeData(float DefaultValue) : BaseValue(DefaultValue) , CurrentValue(DefaultValue)`
- L34 _public prototype_ `virtual ~FGameplayAttributeData() = default;`
- L37 _public prototype_ `float GetCurrentValue() const;` — Returns the current value, which includes temporary buffs
- L40 _public prototype_ `virtual void SetCurrentValue(float NewValue);` — Modifies current value, normally only called by ability system or during initialization
- L43 _public prototype_ `float GetBaseValue() const;` — Returns the base value which only includes permanent changes
- L46 _public prototype_ `virtual void SetBaseValue(float NewValue);` — Modifies the permanent base value, normally only called by ability system or during initialization
- L50 _protected member_ `float BaseValue;` — `UPROPERTY(BlueprintReadOnly, Category = "Attribute")`
- L53 _protected member_ `float CurrentValue;` — `UPROPERTY(BlueprintReadOnly, Category = "Attribute")`

#### struct `FGameplayAttribute`  
`struct FGameplayAttribute`  
_L58-164_
- reflection: `USTRUCT(BlueprintType)`
- desc: Describes a FGameplayAttributeData or float property inside an attribute set. Using this provides editor UI and helper functions
- L62 _public function_ `FGameplayAttribute() : Attribute(nullptr) , AttributeOwner(nullptr)`
- L68 _public prototype_ `FGameplayAttribute(FProperty *NewProperty);`
- L71 _public function_ `bool IsValid() const` — Returns true if our Attribute has a valid resolved Field
- L77 _public function_ `void SetUProperty(FProperty *NewProperty)` — Set up from a FProperty inside a set
- L93 _public function_ `FProperty* GetUProperty() const` — Returns raw property
- L99 _public function_ `UClass* GetAttributeSetClass() const` — Returns the AttributeSet subclass holding this attribute
- L106 _public prototype_ `bool IsSystemAttribute() const;` — Returns true if this is one of the special attributes defined on the AbilitySystemComponent itself
- L109 _public prototype_ `static bool IsSupportedProperty(const FProperty* Prop);` — Returns whether a property is able to represent a Gameplay Attribute. Does not check whether the property is owned by an attribute set.
- L112 _public prototype_ `static bool IsGameplayAttributeDataProperty(const FProperty* Property);` — Returns true if the variable associated with Property is of type FGameplayAttributeData or one of its subclasses
- L115 _public prototype_ `void SetNumericValueChecked(float& NewValue, class UAttributeSet* Dest) const;` — Modifies the current value of an attribute, will not modify base value if that is supported
- L118 _public prototype_ `float GetNumericValue(const UAttributeSet* Src) const;` — Returns the current value of an attribute
- L119 _public prototype_ `float GetNumericValueChecked(const UAttributeSet* Src) const;`
- L122 _public prototype_ `const FGameplayAttributeData* GetGameplayAttributeData(const UAttributeSet* Src) const;` — Returns the AttributeData, will fail if this is a float attribute
- L123 _public prototype_ `const FGameplayAttributeData* GetGameplayAttributeDataChecked(const UAttributeSet* Src) const;`
- L124 _public prototype_ `FGameplayAttributeData* GetGameplayAttributeData(UAttributeSet* Src) const;`
- L125 _public prototype_ `FGameplayAttributeData* GetGameplayAttributeDataChecked(UAttributeSet* Src) const;`
- L128 _public prototype_ `bool operator==(const FGameplayAttribute& Other) const;` — Equality/Inequality operators
- L129 _public prototype_ `bool operator!=(const FGameplayAttribute& Other) const;`
- L138 _public function_ `FString GetName() const` — Returns name of attribute, usually the same as the property
- L145 _public prototype_ `void PostSerialize(const FArchive& Ar);` — Custom serialization
- L150 _public member_ `FString AttributeName;` — `UPROPERTY(Category = GameplayAttribute, VisibleAnywhere, BlueprintReadOnly)` — Name of the attribute, usually the same as property name
- L153 _public prototype_ `static void GetAllAttributeProperties(TArray<FProperty*>& OutProperties, FString FilterMetaStr=FString(), bool UseEditorOnlyData=true);` — In editor, this will filter out properties with meta tag "HideInDetailsView" or equal to FilterMetaStr. In non editor, it returns all properties
- L159 _private member_ `TFieldPath<FProperty> Attribute;` — `UPROPERTY(Category = GameplayAttribute, EditAnywhere)`
- L163 _private member_ `TObjectPtr<UStruct> AttributeOwner;` — `UPROPERTY(Category = GameplayAttribute, VisibleAnywhere)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FGameplayAttribute > : public TStructOpsTypeTraitsBase2< FGameplayAttribute >`  
_L168-174_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAttribute>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L171-173_

#### class `UAttributeSet`  
`class UAttributeSet : public UObject`  
_L185-265_
- reflection: `UCLASS(DefaultToInstanced, Blueprintable, MinimalAPI)`
- inherits: `UObject`
- desc: Defines the set of all GameplayAttributes for your game Games should subclass this and add FGameplayAttributeData properties to represent attributes like health, damage, etc AttributeSets are added to the actors as subobjects, and then registered with the AbilitySystemComponent It often desired to have several sets per project that inherit from each other You could make a base health set, then have a player set that inherits from it and adds more attributes
- L191 _public prototype_ `static void GetAttributesFromSetClass(const TSubclassOf<UAttributeSet>& AttributeSetClass, TArray<FGameplayAttribute>& Attributes);` — Populates (without emptying) a TArray with all FGameplayAttributes from an attribute set class.
- L194 _public function_ `virtual bool ShouldInitProperty(bool FirstInit, FProperty* PropertyToInit) const` — Override to disable initialization for specific properties
- L200 _public function_ `virtual bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData &Data)` — Called just before modifying the value of an attribute. AttributeSet can make additional modifications here. Return true to continue, or false to throw out the modification. Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.
- L206 _public function_ `virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)` — Called just after a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made. Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 second +10 movement speed buff.
- L220 _public function_ `virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)` — Called just before any modification happens to an attribute. There is no additional context provided here since anything can trigger this. Executed effects, duration based effects, effects being removed, immunity being applied, stacking rules changing, etc. This function is meant to enforce things like "Health = Clamp(Health, 0, MaxHealth)" and NOT things like "trigger this extra thing if damage is applied, etc". NewValue is a mutable reference so you are able to clamp the newly applied value as well.
- L223 _public function_ `virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)` — Called just after any modification happens to an attribute.
- L231 _public function_ `virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const` — This is called just before any modification happens to an attribute's base value when an attribute aggregator exists. This function should enforce clamping (presuming you wish to clamp the base value along with the final value in PreAttributeChange) This function should NOT invoke gameplay related events or callbacks. Do those in PreAttributeChange() which will be called prior to the final value of the attribute actually changing.
- L234 _public function_ `virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const` — Called just after any modification happens to an attribute's base value when an attribute aggregator exists.
- L237 _public function_ `virtual void OnAttributeAggregatorCreated(const FGameplayAttribute& Attribute, FAggregator* NewAggregator) const` — Callback for when an FAggregator is created for an attribute in this set. Allows custom setup of FAggregator::EvaluationMetaData
- L240 _public prototype_ `void SetNetAddressable();` — This signifies the attribute set can be ID'd by name over the network.
- L243 _public prototype_ `virtual void InitFromMetaDataTable(const UDataTable* DataTable);` — Initializes attribute data from a meta DataTable
- L246 _public prototype_ `AActor* GetOwningActor() const;` — Gets information about owning actor
- L247 _public prototype_ `UAbilitySystemComponent* GetOwningAbilitySystemComponent() const;`
- L248 _public prototype_ `UAbilitySystemComponent* GetOwningAbilitySystemComponentChecked() const;`
- L249 _public prototype_ `FGameplayAbilityActorInfo* GetActorInfo() const;`
- L252 _public prototype_ `virtual void PrintDebug();` — Print debug information to the log
- L255 _public prototype_ `virtual bool IsNameStableForNetworking() const override;` — Overrides
- L256 _public prototype_ `virtual bool IsSupportedForNetworking() const override;`
- L257 _public prototype_ `virtual void PreNetReceive() override;`
- L258 _public prototype_ `virtual void PostNetReceive() override;`
- L261 _public prototype_ `virtual void RegisterReplicationFragments(UE::Net::FFragmentRegistrationContext& Context, UE::Net::EFragmentRegistrationFlags RegistrationFlags) override;` — Register all replication fragments
- L264 _protected member_ `uint32 bNetAddressable : 1;` — Is this attribute set safe to ID over the network by name?

#### struct `FAttributeMetaData`  
`struct FAttributeMetaData : public FTableRowBase`  
_L271-293_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FTableRowBase`
- desc: DataTable that allows us to define meta data about attributes. Still a work in progress.
- L277 _public prototype_ `FAttributeMetaData();`
- L280 _public member_ `float BaseValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")`
- L283 _public member_ `float MinValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")`
- L286 _public member_ `float MaxValue;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")`
- L289 _public member_ `FString DerivedAttributeInfo;` — `UPROPERTY()`
- L292 _public member_ `bool bCanStack;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Attribute")`

#### struct `FAttributeSetInitter`  
`struct FAttributeSetInitter`  
_L340-348_
- desc: Helper struct that facilitates initializing attribute set default values from spread sheets (UCurveTable). Projects are free to initialize their attribute sets however they want. This is just want example that is useful in some cases. Basic idea is to have a spreadsheet in this form: 1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20 Default.Health.MaxHealth		100	200	300	400	500	600	700	800	900	999	999	999	999	999	999	999	999	999	999	999 Default.Health.HealthRegenRate	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1 Default.Health.AttackRating		10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10 Default.Move.MaxMoveSpeed		500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500 Hero1.Health.MaxHealth			100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100	100 Hero1.Health.HealthRegenRate	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1	1 	1	1	1	1 Hero1.Health.AttackRating		10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10	10 Hero1.Move.MaxMoveSpeed			500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500	500 Where rows are in the form: [GroupName].[AttributeSetName].[Attribute] GroupName			- arbitrary name to identify the "group" AttributeSetName	- what UAttributeSet the attributes belong to. (Note that this is a simple partial match on the UClass name. "Health" matches "UMyGameHealthSet"). Attribute			- the name of the actual attribute property (matches full name). Columns represent "Level". FAttributeSetInitter::PreloadAt
- L342 _public prototype_ `virtual ~FAttributeSetInitter() = default;`
- L344 _public prototype_ `virtual void PreloadAttributeSetData(const TArray<UCurveTable*>& CurveData) = 0;`
- L345 _public prototype_ `virtual void InitAttributeSetDefaults(UAbilitySystemComponent* AbilitySystemComponent, FName GroupName, int32 Level, bool bInitialInit) const = 0;`
- L346 _public prototype_ `virtual void ApplyAttributeDefault(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute& InAttribute, FName GroupName, int32 Level) const = 0;`
- L347 _public function_ `virtual TArray<float> GetAttributeSetValues(UClass* AttributeSetClass, FProperty* AttributeProperty, FName GroupName) const`

#### struct `FAttributeSetInitterDiscreteLevels`  
`struct FAttributeSetInitterDiscreteLevels : public FAttributeSetInitter`  
_L351-391_
- inherits: `FAttributeSetInitter`
- desc: Explicit implementation of attribute set initter, relying on the existence and usage of discrete levels for data look-up (that is, CurveTable->Eval is not possible)
- L353 _public prototype_ `virtual void PreloadAttributeSetData(const TArray<UCurveTable*>& CurveData) override;`
- L355 _public prototype_ `virtual void InitAttributeSetDefaults(UAbilitySystemComponent* AbilitySystemComponent, FName GroupName, int32 Level, bool bInitialInit) const override;`
- L356 _public prototype_ `virtual void ApplyAttributeDefault(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute& InAttribute, FName GroupName, int32 Level) const override;`
- L358 _public prototype_ `virtual TArray<float> GetAttributeSetValues(UClass* AttributeSetClass, FProperty* AttributeProperty, FName GroupName) const override;`
- L390 _private member_ `TMap<FName, FAttributeSetDefaultsCollection> Defaults;`

#### struct `FAttributeSetInitterDiscreteLevels::FAttributeDefaultValueList`  
`struct FAttributeDefaultValueList`  
_L361-378_
- L363 _public function_ `void AddPair(FProperty* InProperty, float InValue)`
- L377 _public member_ `TArray<FOffsetValuePair> List;`

#### struct `FAttributeSetInitterDiscreteLevels::FAttributeDefaultValueList::FOffsetValuePair`  
`struct FOffsetValuePair`  
_L368-375_
- L370 _public function_ `FOffsetValuePair(FProperty* InProperty, float InValue) : Property(InProperty), Value(InValue)`
- L373 _public member_ `FProperty* Property;`
- L374 _public member_ `float Value;`

#### struct `FAttributeSetInitterDiscreteLevels::FAttributeSetDefaults`  
`struct FAttributeSetDefaults`  
_L380-383_
- L382 _public member_ `TMap<TSubclassOf<UAttributeSet>, FAttributeDefaultValueList> DataMap;`

#### struct `FAttributeSetInitterDiscreteLevels::FAttributeSetDefaultsCollection`  
`struct FAttributeSetDefaultsCollection`  
_L385-388_
- L387 _public member_ `TArray<FAttributeSetDefaults> LevelData;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L131 _function_ `friend uint32 GetTypeHash( const FGameplayAttribute& InAttribute )`
- L172 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anona623e4880103`)
- L402 _macro_ `#define GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue) \`
- L428 _macro_ `#define GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \`
- L435 _macro_ `#define GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \`
- L441 _macro_ `#define GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \`
- L451 _macro_ `#define GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \`
- L465 _macro_ `#define ATTRIBUTE_ACCESSORS_BASIC(ClassName, PropertyName) \` — Instead of copying the ATTRIBUTE_ACCESSORS macro from the comment above, you can also immediately use this one if it fulfills your needs. Named differently to not cause name collision in existing projects that have copied ATTRIBUTE_ACCESSORS already: ATTRIBUTE_ACCESSORS_BASIC(UMyHealthSet, Health)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitiesDeveloperSettings.h` (Public)


#### class `UGameplayAbilitiesDeveloperSettings`  
`class UGameplayAbilitiesDeveloperSettings : public UDeveloperSettings`  
_L30-133_
- reflection: `UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Gameplay Abilities Settings"), MinimalAPI)`
- inherits: `UDeveloperSettings`
- desc: Expose Global Gameplay Ability Settings in an easy to understand Developer Settings interface (usable through the Editor's Project Settings). This the preferred way to configure the config variables previously found in AbilitySystemGlobals.  Projects may still opt to override the AbilitySystemGlobals class with their own customized class to modify Gameplay Ability functionality across their project.
- L37 _public member_ `FSoftClassPath AbilitySystemGlobalsClassName = UAbilitySystemGlobals::StaticClass();` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta=(DisplayName = "Ability System Globals Class", MetaClass="/Script/GameplayAbilities.AbilitySystemGlobals", ConfigRestartRequired=true))` — The global ability system class to use
- L41 _public member_ `bool bUseDebugTargetFromHud = false;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay)` — Set to true if you want the "ShowDebug AbilitySystem" cheat to use the hud's debug target instead of the ability system's debug target.
- L45 _public member_ `TArray<FSoftObjectPath> GlobalAttributeSetDefaultsTableNames;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Attribute, meta=(DisplayName = "Global Attribute Set Defaults Tables", AllowedClasses="/Script/Engine.CurveTable", ConfigRestartRequired=true))` — Array of curve table names to use for default values for attribute sets, keyed off of Name/Levels
- L49 _public member_ `FSoftObjectPath GlobalAttributeMetaDataTableName;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Attribute, meta=(DisplayName = "Global Attribute Meta Data Table", AllowedClasses="/Script/Engine.DataTable", ConfigRestartRequired=true))` — Holds information about the valid attributes' min and max values and stacking rules
- L53 _public member_ `FSoftClassPath GlobalGameplayCueManagerClass = UGameplayCueManager::StaticClass();` — `UPROPERTY(Config, EditDefaultsOnly, Category=GameplayCue, meta=(DisplayName = "Global GameplayCue Manager Class", MetaClass="/Script/GameplayAbilities.GameplayCueManager", ConfigRestartRequired=true))` — Class reference to gameplay cue manager. Use this if you want to just instantiate a class for your gameplay cue manager without having to create an asset.
- L57 _public member_ `FSoftObjectPath GlobalGameplayCueManagerName;` — `UPROPERTY(Config, EditDefaultsOnly, Category=GameplayCue, meta=(AllowedClasses="/Script/GameplayAbilities.GameplayCueManager", ConfigRestartRequired=true))` — Class reference to gameplay cue manager. Use this if you want to just instantiate a class for your gameplay cue manager without having to create an asset.
- L61 _public member_ `TArray<FString> GameplayCueNotifyPaths;` — `UPROPERTY(Config, EditDefaultsOnly, Category=GameplayCue, meta = (ConfigRestartRequired=true))` — Look in these paths for GameplayCueNotifies. These are your "always loaded" set.
- L65 _public member_ `FSoftObjectPath GlobalCurveTableName;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta=(DisplayName = "Global Curve Table", AllowedClasses="/Script/Engine.CurveTable", ConfigRestartRequired=true))` — Name of global curve table to use as the default for scalable floats, etc.
- L69 _public member_ `bool PredictTargetGameplayEffects = true;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay)` — Set to true if you want clients to try to predict gameplay effects done to targets. If false it will only predict self effects
- L76 _public member_ `bool ReplicateActivationOwnedTags = true;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay)` — Set to true if you want tags granted to owners from ability activations to be replicated. If false, ActivationOwnedTags are only applied locally. This should only be disabled for legacy game code that depends on non-replication of ActivationOwnedTags.
- L80 _public member_ `FGameplayTag ActivateFailCanActivateAbilityTag;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta = (ConfigRestartRequired=true))` — TryActive failed due to GameplayAbility's CanActivateAbility function (Blueprint or Native)
- L84 _public member_ `FGameplayTag ActivateFailCooldownTag;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta = (ConfigRestartRequired=true))` — TryActivate failed due to being on cooldown
- L88 _public member_ `FGameplayTag ActivateFailCostTag;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta = (ConfigRestartRequired=true))` — TryActivate failed due to not being able to spend costs
- L92 _public member_ `FGameplayTag ActivateFailNetworkingTag;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta = (ConfigRestartRequired=true))` — Failed to activate due to invalid networking settings, this is designer error
- L96 _public member_ `FGameplayTag ActivateFailTagsBlockedTag;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta = (ConfigRestartRequired=true))` — TryActivate failed due to being blocked by other abilities
- L100 _public member_ `FGameplayTag ActivateFailTagsMissingTag;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta = (ConfigRestartRequired=true))` — TryActivate failed due to missing required tags
- L104 _public member_ `FSoftObjectPath GameplayTagResponseTableName;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Gameplay, meta=(DisplayName = "Gameplay Tag Response Table", AllowedClasses="/Script/GameplayAbilities.GameplayTagReponseTable", ConfigRestartRequired=true))` — The class to instantiate as the GameplayTagResponseTable.
- L108 _public member_ `bool bAllowGameplayModEvaluationChannels = false;` — `UPROPERTY(config, EditDefaultsOnly, Category=GameplayEffects, meta = (ConfigRestartRequired=true))` — Whether the game should allow the usage of gameplay mod evaluation channels or not
- L112 _public member_ `EGameplayModEvaluationChannel DefaultGameplayModEvaluationChannel = EGameplayModEvaluationChannel::Channel0;` — `UPROPERTY(config, EditDefaultsOnly, Category=GameplayEffects, meta = (ConfigRestartRequired=true))` — The default mod evaluation channel for the game
- L116 _public member_ `FName GameplayModEvaluationChannelAliases[10];` — `UPROPERTY(config, EditDefaultsOnly, Category=GameplayEffects, meta = (ConfigRestartRequired=true))` — Game-specified named aliases for gameplay mod evaluation channels; Only those with valid aliases are eligible to be used in a game (except Channel0, which is always valid)
- L120 _public member_ `int32 MinimalReplicationTagCountBits = 5;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Advanced)` — How many bits to use for "number of tags" in FMinimalReplicationTagCountMap::NetSerialize.
- L123 _public prototype_ `virtual bool CanEditChange(const FProperty* InProperty) const override;`
- L125 _public function_ `virtual void OverrideConfigSection(FString& InOutSectionName) override`

#### class `UGameplayAbilitiesEditorDeveloperSettings`  
`class UGameplayAbilitiesEditorDeveloperSettings : public UDeveloperSettingsBackedByCVars`  
_L136-152_
- reflection: `UCLASS(config = EditorPerProjectUserSettings, meta = (DisplayName = "Gameplay Abilities Editor Settings"), MinimalAPI)`
- inherits: `UDeveloperSettingsBackedByCVars`
- L142 _protected member_ `bool bIgnoreCooldowns = false;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Debug, meta = (ConsoleVariable = "AbilitySystem.IgnoreCooldowns"))`
- L145 _protected member_ `bool bIgnoreCosts = false;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Debug, meta = (ConsoleVariable = "AbilitySystem.IgnoreCosts"))`
- L148 _protected member_ `float AbilitySystemGlobalScaler = 1.f;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Debug, meta = (ConsoleVariable = "AbilitySystem.GlobalAbilityScale"))`
- L151 _protected member_ `float DebugDrawMaxDistance = 2048.f;` — `UPROPERTY(Config, EditDefaultsOnly, Category=Debug, meta = (ConsoleVariable = "AbilitySystem.DebugDrawMaxDistance"))`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitiesModule.h` (Public)


#### class `IGameplayAbilitiesModule`  
`class IGameplayAbilitiesModule : public IModuleInterface`  
_L13-45_
- inherits: `IModuleInterface`
- desc: The public interface to this module
- L24 _public function_ `static inline IGameplayAbilitiesModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L40 _public prototype_ `virtual class UAbilitySystemGlobals* GetAbilitySystemGlobals() = 0;`
- L42 _public prototype_ `virtual bool IsAbilitySystemGlobalsAvailable() = 0;`
- L44 _public prototype_ `virtual void CallOrRegister_OnAbilitySystemGlobalsReady(FSimpleMulticastDelegate::FDelegate Delegate) = 0;`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilityBlueprint.h` (Public)


#### class `UGameplayAbilityBlueprint`  
`class UGameplayAbilityBlueprint : public UBlueprint`  
_L18-35_
- reflection: `UCLASS(BlueprintType, MinimalAPI)`
- inherits: `UBlueprint`
- L25 _private function_ `virtual bool SupportedByDefaultBlueprintFactory() const override` — UBlueprint interface
- L32 _private prototype_ `static UGameplayAbilityBlueprint* FindRootGameplayAbilityBlueprint(UGameplayAbilityBlueprint* DerivedBlueprint);` — Returns the most base gameplay ability blueprint for a given blueprint (if it is inherited from another ability blueprint, returning null if only native / non-ability BP classes are it's parent)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitySet.h` (Public)


#### enum `EGameplayAbilityInputBinds::Type`  
`enum Type : int`  
_L27-38_
- L29 _public enumerator_ `Ability1 UMETA(DisplayName = "Ability1 (LMB)")`
- L30 _public enumerator_ `Ability2 UMETA(DisplayName = "Ability2 (RMB)")`
- L31 _public enumerator_ `Ability3 UMETA(DisplayName = "Ability3 (Q)")`
- L32 _public enumerator_ `Ability4 UMETA(DisplayName = "Ability4 (E)")`
- L33 _public enumerator_ `Ability5 UMETA(DisplayName = "Ability5 (R)")`
- L34 _public enumerator_ `Ability6 UMETA(DisplayName = "Ability6 (Shift)")`
- L35 _public enumerator_ `Ability7 UMETA(DisplayName = "Ability7 (Space)")`
- L36 _public enumerator_ `Ability8 UMETA(DisplayName = "Ability8 (B)")`
- L37 _public enumerator_ `Ability9 UMETA(DisplayName = "Ability9 (T)")`

#### struct `FGameplayAbilityBindInfo`  
`struct FGameplayAbilityBindInfo`  
_L45-54_
- reflection: `USTRUCT()`
- desc: Example struct that pairs a enum input command to a GameplayAbilityClass.6
- L50 _public member_ `TEnumAsByte<EGameplayAbilityInputBinds::Type> Command = EGameplayAbilityInputBinds::Ability1;` — `UPROPERTY(EditAnywhere, Category = BindInfo)`
- L53 _public member_ `TSubclassOf<UGameplayAbility> GameplayAbilityClass;` — `UPROPERTY(EditAnywhere, Category = BindInfo)`

#### class `UGameplayAbilitySet`  
`class UGameplayAbilitySet : public UDataAsset`  
_L63-72_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: This is an example DataAsset that could be used for defining a set of abilities to give to an AbilitySystemComponent and bind to an input command. Your project is free to implement this however it wants!
- L69 _private member_ `TArray<FGameplayAbilityBindInfo> Abilities;` — `UPROPERTY(EditAnywhere, Category = AbilitySet)`
- L71 _private prototype_ `void GiveAbilities(UAbilitySystemComponent* AbilitySystemComponent) const;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L25 _namespace_ `namespace EGameplayAbilityInputBinds`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitySpec.h` (Public)


#### enum `EGameplayAbilityActivationMode::Type`  
`enum Type : int`  
_L28-44_
- L31 _public enumerator_ `Authority` — We are the authority activating this ability
- L34 _public enumerator_ `NonAuthority` — We are not the authority but aren't predicting yet. This is a mostly invalid state to be in
- L37 _public enumerator_ `Predicting` — We are predicting the activation of this ability
- L40 _public enumerator_ `Confirmed` — We are not the authority, but the authority has confirmed this activation
- L43 _public enumerator_ `Rejected` — We tried to activate it, and server told us we couldn't (even though we thought we could)

#### enum `EGameplayEffectGrantedAbilityRemovePolicy`  
`enum class EGameplayEffectGrantedAbilityRemovePolicy : uint8`  
_L49-57_
- reflection: `UENUM()`
- desc: Describes what happens when a GameplayEffect, that is granting an active ability, is removed from its owner.
- L52 _public enumerator_ `CancelAbilityImmediately` — Active abilities are immediately canceled and the ability is removed.
- L54 _public enumerator_ `RemoveAbilityOnEnd` — Active abilities are allowed to finish, and then removed.
- L56 _public enumerator_ `DoNothing` — Granted abilities are left lone when the granting GameplayEffect is removed.

#### struct `FGameplayAbilitySpecDef`  
`struct FGameplayAbilitySpecDef`  
_L61-102_
- reflection: `USTRUCT(BlueprintType)`
- desc: This is data that can be used to create an FGameplayAbilitySpec. Has some data that is only relevant when granted by a GameplayEffect
- L63 _public function_ `FGameplayAbilitySpecDef() : InputID(INDEX_NONE) , RemovalPolicy(EGameplayEffectGrantedAbilityRemovePolicy::CancelAbilityImmediately) , SourceObject(nullptr)`
- L75 _public member_ `TSubclassOf<UGameplayAbility> Ability;` — `UPROPERTY(EditDefaultsOnly, Category="Ability Definition", NotReplicated)` — What ability to grant
- L79 _public member_ `FScalableFloat LevelScalableFloat;` — `UPROPERTY(EditDefaultsOnly, Category="Ability Definition", NotReplicated, DisplayName="Level")` — What level to grant this ability at
- L83 _public member_ `int32 InputID;` — `UPROPERTY(EditDefaultsOnly, Category="Ability Definition", NotReplicated)` — Input ID to bind this ability to
- L87 _public member_ `EGameplayEffectGrantedAbilityRemovePolicy RemovalPolicy;` — `UPROPERTY(EditDefaultsOnly, Category="Ability Definition", NotReplicated)` — What will remove this ability later
- L91 _public member_ `TWeakObjectPtr<UObject> SourceObject;` — `UPROPERTY(NotReplicated)` — What granted this spec, not replicated or settable in editor
- L94 _public member_ `TMap<FGameplayTag, float> SetByCallerTagMagnitudes;` — SetbyCaller Magnitudes that were passed in to this ability by a GE (GE's that grant abilities)
- L98 _public member_ `FGameplayAbilitySpecHandle AssignedHandle;` — `UPROPERTY()` — This handle can be set if the SpecDef is used to create a real FGameplaybilitySpec
- L100 _public prototype_ `bool operator==(const FGameplayAbilitySpecDef& Other) const;`
- L101 _public prototype_ `bool operator!=(const FGameplayAbilitySpecDef& Other) const;`

#### struct `FGameplayAbilityActivationInfo`  
`struct FGameplayAbilityActivationInfo`  
_L114-161_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayAbilityActivationInfo Data tied to a specific activation of an ability. -Tell us whether we are the authority, if we are predicting, confirmed, etc. -Holds current and previous PredictionKey -Generally not meant to be subclassed in projects. -Passed around by value since the struct is small.
- L118 _public function_ `FGameplayAbilityActivationInfo() : ActivationMode(EGameplayAbilityActivationMode::Authority) , bCanBeEndedByOtherInstance(false)`
- L124 _public prototype_ `FGameplayAbilityActivationInfo(AActor* InActor);`
- L126 _public function_ `FGameplayAbilityActivationInfo(EGameplayAbilityActivationMode::Type InType) : ActivationMode(InType) , bCanBeEndedByOtherInstance(false)`
- L134 _public member_ `mutable TEnumAsByte<EGameplayAbilityActivationMode::Type> ActivationMode;` — `UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")` — Activation status of this ability
- L138 _public member_ `uint8 bCanBeEndedByOtherInstance:1;` — `UPROPERTY()` — An ability that runs on multiple game instances can be canceled by a remote instance, but only if that remote instance has already confirmed starting it.
- L141 _public prototype_ `void SetActivationConfirmed();` — Called on client when activation is confirmed on server
- L144 _public prototype_ `void SetActivationRejected();` — Called when activation was rejected by the server
- L147 _public prototype_ `void SetPredicting(FPredictionKey PredictionKey);` — Called on client to set this as a predicted ability
- L150 _public prototype_ `void ServerSetActivationPredictionKey(FPredictionKey PredictionKey);` — Called on the server to set the key used by the client to predict this ability
- L153 _public function_ `const FPredictionKey& GetActivationPredictionKey() const` — Returns prediction key, const to avoid being able to modify it after creation
- L159 _private member_ `FPredictionKey PredictionKeyWhenActivated;` — `UPROPERTY()` — This was the prediction key used to activate this ability. It does not get updated if new prediction keys are generated over the course of the ability

#### struct `FGameplayAbilitySpec`  
`struct FGameplayAbilitySpec : public FFastArraySerializerItem`  
_L168-297_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FFastArraySerializerItem`
- desc: An activatable ability spec, hosted on the ability system component. This defines both what the ability is (what class, what level, input binding etc) and also holds runtime state that must be kept outside of the ability being instanced/activated.
- L173 _public prototype_ `FGameplayAbilitySpec(const FGameplayAbilitySpec&) = default;`
- L174 _public prototype_ `FGameplayAbilitySpec(FGameplayAbilitySpec&&) = default;`
- L175 _public prototype_ `FGameplayAbilitySpec& operator=(const FGameplayAbilitySpec&) = default;`
- L176 _public prototype_ `FGameplayAbilitySpec& operator=(FGameplayAbilitySpec&&) = default;`
- L177 _public prototype_ `~FGameplayAbilitySpec() = default;`
- L180 _public function_ `FGameplayAbilitySpec() : Ability(nullptr), Level(1), InputID(INDEX_NONE), SourceObject(nullptr), ActiveCount(0), InputPressed(false), RemoveAfterActivation(false), PendingRemove(false), bActivateOnce(false)`
- L185 _public prototype_ `FGameplayAbilitySpec(TSubclassOf<UGameplayAbility> InAbilityClass, int32 InLevel = 1, int32 InInputID = INDEX_NONE, UObject* InSourceObject = nullptr);` — Version that takes an ability class
- L188 _public prototype_ `FGameplayAbilitySpec(UGameplayAbility* InAbility, int32 InLevel = 1, int32 InInputID = INDEX_NONE, UObject* InSourceObject = nullptr);` — Version that takes an ability CDO, this exists for backward compatibility
- L191 _public prototype_ `FGameplayAbilitySpec(FGameplayAbilitySpecDef& InDef, int32 InGameplayEffectLevel, FActiveGameplayEffectHandle InGameplayEffectHandle = FActiveGameplayEffectHandle());` — Version that takes an existing spec def
- L195 _public member_ `FGameplayAbilitySpecHandle Handle;` — `UPROPERTY()` — Handle for outside sources to refer to this spec by
- L199 _public member_ `TObjectPtr<UGameplayAbility> Ability;` — `UPROPERTY()` — Ability of the spec (Always the CDO. This should be const but too many things modify it currently)
- L203 _public member_ `int32 Level;` — `UPROPERTY()` — Level of Ability
- L207 _public member_ `int32 InputID;` — `UPROPERTY()` — InputID, if bound
- L211 _public member_ `TWeakObjectPtr<UObject> SourceObject;` — `UPROPERTY()` — Object this ability was created from, can be an actor or static object. Useful to bind an ability to a gameplay object
- L215 _public member_ `uint8 ActiveCount;` — `UPROPERTY(NotReplicated)` — A count of the number of times this ability has been activated minus the number of times it has been ended. For instanced abilities this will be the number of currently active instances. Can't replicate until prediction accurately handles this.
- L219 _public member_ `uint8 InputPressed:1;` — `UPROPERTY(NotReplicated)` — Is input currently pressed. Set to false when input is released
- L223 _public member_ `uint8 RemoveAfterActivation:1;` — `UPROPERTY(NotReplicated)` — If true, this ability should be removed as soon as it finishes executing
- L227 _public member_ `uint8 PendingRemove:1;` — `UPROPERTY(NotReplicated)` — Pending removal due to scope lock
- L231 _public member_ `uint8 bActivateOnce : 1;` — `UPROPERTY(NotReplicated)` — This ability should be activated once when it is granted.
- L234 _public member_ `TSharedPtr<FGameplayEventData> GameplayEventData = nullptr;` — Cached GameplayEventData if this ability was pending for add and activate due to scope lock
- L239 _public member_ `FGameplayAbilityActivationInfo ActivationInfo;` — `UE_DEPRECATED(5.5, "ActivationInfo on the Spec only applies to NonInstanced abilities (which are now deprecated; instanced abilities have their own per-instance CurrentActivationInfo)")` — `UPROPERTY(NotReplicated)` — Activation state of this ability. This is not replicated since it needs to be overwritten locally on clients during prediction.
- L244 _public member_ `FGameplayTagContainer DynamicAbilityTags;` — `UE_DEPRECATED(5.5, "Use GetDynamicSpecSourceTags() which better represents what this variable does")` — `UPROPERTY()` — Optional ability tags that are replicated.  These tags are also captured as source tags by applied gameplay effects.
- L248 _public function_ `FGameplayTagContainer& GetDynamicSpecSourceTags()` — Optional tags that are replicated with this AbilitySpec.  The specified tags are captured as a GESpec's Source tags by GE's created with this ability spec (@see UGameplayAbility::MakeOutgoingGameplayEffectSpec).
- L249 _public function_ `const FGameplayTagContainer& GetDynamicSpecSourceTags() const`
- L254 _public member_ `TArray<FAbilityTriggerData> DynamicAbilityTriggers;` — `UPROPERTY()` — Additional Ability Triggers that can be used in order to trigger the ability associated with this spec.
- L258 _public member_ `TArray<TObjectPtr<UGameplayAbility>> NonReplicatedInstances;` — `UPROPERTY(NotReplicated)` — Non replicating instances of this ability.
- L262 _public member_ `TArray<TObjectPtr<UGameplayAbility>> ReplicatedInstances;` — `UPROPERTY()` — Replicated instances of this ability..
- L269 _public member_ `FActiveGameplayEffectHandle GameplayEffectHandle;` — `UPROPERTY(NotReplicated)` — Handle to GE that granted us (usually invalid). FActiveGameplayEffectHandles are not synced across the network and this is valid only on Authority. If you need FGameplayAbilitySpec -> FActiveGameplayEffectHandle, then use AbilitySystemComponent::FindActiveGameplayEffectHandle.
- L272 _public member_ `TMap<FGameplayTag, float> SetByCallerTagMagnitudes;` — Passed on SetByCaller magnitudes if this ability was granted by a GE
- L275 _public prototype_ `UGameplayAbility* GetPrimaryInstance() const;` — Returns the primary instance, only valid on InstancedPerActor abilities (returns nullptr otherwise)
- L278 _public prototype_ `bool ShouldReplicateAbilitySpec() const;` — interface function to see if the ability should replicated the ability spec or not
- L281 _public function_ `TArray<UGameplayAbility*> GetAbilityInstances() const` — Returns all instances, which can include InstancedPerExecution abilities
- L290 _public prototype_ `bool IsActive() const;` — Returns true if this ability is active in any way
- L292 _public prototype_ `void PreReplicatedRemove(const struct FGameplayAbilitySpecContainer& InArraySerializer);`
- L293 _public prototype_ `void PostReplicatedChange(const struct FGameplayAbilitySpecContainer& InArraySerializer);`
- L294 _public prototype_ `void PostReplicatedAdd(const struct FGameplayAbilitySpecContainer& InArraySerializer);`
- L296 _public prototype_ `FString GetDebugString();`

#### struct `FGameplayAbilitySpecContainer`  
`struct FGameplayAbilitySpecContainer : public FFastArraySerializer`  
_L301-339_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FFastArraySerializer`
- desc: Fast serializer wrapper for above struct
- L305 _public function_ `FGameplayAbilitySpecContainer() : Owner(nullptr)`
- L312 _public member_ `TArray<FGameplayAbilitySpec> Items;` — `UPROPERTY()` — List of activatable abilities
- L316 _public member_ `TObjectPtr<UAbilitySystemComponent> Owner;` — `UPROPERTY(NotReplicated)` — Component that owns this list
- L319 _public prototype_ `void RegisterWithOwner(UAbilitySystemComponent* Owner);` — Initializes Owner variable
- L321 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms);`
- L324 _public function_ `template< typename Type, typename SerializerType > bool ShouldWriteFastArrayItem(const Type& Item, const bool bIsWritingOnClient)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FGameplayAbilitySpecContainer > : public TStructOpsTypeTraitsBase2< FGameplayAbilitySpecContainer >`  
_L342-348_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayAbilitySpecContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L345-347_

#### struct `FScopedAbilityListLock`  
`struct FScopedAbilityListLock`  
_L351-358_
- desc: Used to stop us from removing abilities from an ability system component while we're iterating through the abilities
- L353 _public prototype_ `FScopedAbilityListLock(UAbilitySystemComponent& InContainer);`
- L354 _public prototype_ `~FScopedAbilityListLock();`
- L357 _private member_ `UAbilitySystemComponent& AbilitySystemComponent;`

#### struct `FScopedTargetListLock`  
`struct FScopedTargetListLock`  
_L363-373_
- desc: Used to stop us from canceling or ending an ability while we're iterating through its gameplay targets
- L365 _public prototype_ `FScopedTargetListLock(UAbilitySystemComponent& InAbilitySystemComponent, const UGameplayAbility& InAbility);`
- L366 _public prototype_ `~FScopedTargetListLock();`
- L369 _private member_ `const UGameplayAbility& GameplayAbility;`
- L372 _private member_ `FScopedAbilityListLock AbilityLock;` — we also need to make sure the ability isn't removed while we're in this lock

#### Free symbols / members of external scopes

- L18 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L26 _namespace_ `namespace EGameplayAbilityActivationMode`
- L346 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anon9e24b5b10103`)
- L360 _macro_ `#define ABILITYLIST_SCOPE_LOCK() FScopedAbilityListLock ActiveScopeLock(*this);`
- L375 _macro_ `#define TARGETLIST_SCOPE_LOCK(ASC) FScopedTargetListLock ActiveScopeLock(ASC, *this);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayAbilitySpecHandle.h` (Public)


#### struct `FGameplayAbilitySpecHandle`  
`struct FGameplayAbilitySpecHandle`  
_L15-65_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle that points to a specific granted ability. These are globally unique
- L19 _public function_ `FGameplayAbilitySpecHandle() : Handle(INDEX_NONE)`
- L25 _public function_ `bool IsValid() const` — True if GenerateNewHandle was called on this handle
- L31 _public prototype_ `void GenerateNewHandle();` — Sets this to a valid handle
- L33 _public function_ `bool operator==(const FGameplayAbilitySpecHandle& Other) const`
- L38 _public function_ `bool operator!=(const FGameplayAbilitySpecHandle& Other) const`
- L56 _public function_ `FString ToString() const`
- L64 _private member_ `int32 Handle;` — `UPROPERTY()`

#### Free symbols / members of external scopes

- L44 _function_ `friend FArchive& operator<<(FArchive& Ar, FGameplayAbilitySpecHandle& Value)` — Operator to expose FGameplayAbilitySpecHandle serialization to custom serialization functions like NetSerialize overrides.
- L51 _function_ `friend uint32 GetTypeHash(const FGameplayAbilitySpecHandle& SpecHandle)`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueFunctionLibrary.h` (Public)


#### class `UGameplayCueFunctionLibrary`  
`class UGameplayCueFunctionLibrary : public UBlueprintFunctionLibrary`  
_L23-50_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: UGameplayCueFunctionLibrary Helpful utility function for working with gameplay cues.
- L31 _public prototype_ `static FGameplayCueParameters MakeGameplayCueParametersFromHitResult(const FHitResult& HitResult);` — `UFUNCTION(BlueprintPure, Category = "GameplayCue")` — Builds gameplay cue parameters using data from a hit result.
- L37 _public prototype_ `static void ExecuteGameplayCueOnActor(AActor* Target, const FGameplayTag GameplayCueTag, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (GameplayTagFilter = "GameplayCue"), DisplayName = "Execute GameplayCue On Actor (Burst)")` — Invoke a one time "instant" execute event for a gameplay cue on the target actor. * If the actor has an ability system, the event will fire on authority only and will be replicated. * If the actor does not have an ability system, the event will only be fired locally.
- L43 _public prototype_ `static void AddGameplayCueOnActor(AActor* Target, const FGameplayTag GameplayCueTag, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (GameplayTagFilter = "GameplayCue"), DisplayName = "Add GameplayCue On Actor (Looping)")` — Invoke the added event for a gameplay cue on the target actor. This should be paired with a RemoveGameplayCueOnActor call. * If the actor has an ability system, the event will fire on authority only and will be replicated. * If the actor does not have an ability system, the event will only be fired locally.
- L49 _public prototype_ `static void RemoveGameplayCueOnActor(AActor* Target, const FGameplayTag GameplayCueTag, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (GameplayTagFilter = "GameplayCue"), DisplayName = "Remove GameplayCue On Actor (Looping)")` — Invoke the removed event for a gameplay cue on the target actor. This should be paired with an AddGameplayCueOnActor call. * If the actor has an ability system, the event will fire on authority only and will be replicated. * If the actor does not have an ability system, the event will only be fired locally.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueInterface.h` (Public)


#### class `UGameplayCueInterface`  
`class UGameplayCueInterface: public UInterface`  
_L25-28_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for actors that wish to handle GameplayCue events from GameplayEffects. Native only because blueprints can't implement interfaces with native functions

#### class `IGameplayCueInterface`  
`class IGameplayCueInterface`  
_L30-88_
- L37 _public prototype_ `virtual void HandleGameplayCue(UObject* Self, FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Handle a single gameplay cue
- L40 _public prototype_ `virtual void HandleGameplayCues(UObject* Self, const FGameplayTagContainer& GameplayCueTags, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Wrapper that handles multiple cues
- L46 _public prototype_ `virtual bool ShouldAcceptGameplayCue(UObject* Self, FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Returns true if the object can currently accept gameplay cues associated with the given tag. Returns true by default. Allows objects to opt out of cues in cases such as pending death
- L52 _public prototype_ `virtual void HandleGameplayCue(AActor *Self, FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Handle a single gameplay cue
- L55 _public prototype_ `virtual void HandleGameplayCues(AActor *Self, const FGameplayTagContainer& GameplayCueTags, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Wrapper that handles multiple cues
- L58 _public prototype_ `virtual bool ShouldAcceptGameplayCue(AActor *Self, FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Returns true if the actor can currently accept gameplay cues associated with the given tag. Returns true by default. Allows actors to opt out of cues in cases such as pending death
- L64 _public function_ `virtual void GetGameplayCueSets(TArray<class UGameplayCueSet*>& OutSets) const` — Return the cue sets used by this object. This is optional and it is possible to leave this list empty.
- L67 _public prototype_ `virtual void GameplayCueDefaultHandler(EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Default native handler, called if no tag matches found
- L71 _public prototype_ `void BlueprintCustomHandler(EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, Category = GameplayCue, meta = (BlueprintInternalUseOnly = "true"))` — Internal function to map ufunctions directly to gameplaycue tags
- L75 _public prototype_ `virtual void ForwardGameplayCueToParent();` — `UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Ability|GameplayCue")` — Call from a Cue handler event to continue checking for additional, more generic handlers. Called from the ability system blueprint library
- L78 _public prototype_ `static void DispatchBlueprintCustomHandler(UObject* Object, UFunction* Func, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Calls the UFunction override for a specific gameplay cue
- L81 _public prototype_ `static void ClearTagToFunctionMap();` — Clears internal cache of what classes implement which functions
- L83 _public function_ `IGameplayCueInterface() : bForwardToParent(false)`
- L87 _private member_ `bool bForwardToParent;` — If true, keep checking for additional handlers

#### struct `FActiveGameplayCue`  
`struct FActiveGameplayCue : public FFastArraySerializerItem`  
_L101-128_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FFastArraySerializerItem`
- L105 _public function_ `FActiveGameplayCue()`
- L111 _public member_ `FGameplayTag GameplayCueTag;` — `UPROPERTY()`
- L114 _public member_ `FPredictionKey PredictionKey;` — `UPROPERTY()`
- L117 _public member_ `FGameplayCueParameters Parameters;` — `UPROPERTY()`
- L121 _public member_ `bool bPredictivelyRemoved;` — `UPROPERTY(NotReplicated)` — Has this been predictively removed on the client?
- L123 _public prototype_ `void PreReplicatedRemove(const struct FActiveGameplayCueContainer &InArray);`
- L124 _public prototype_ `void PostReplicatedAdd(const struct FActiveGameplayCueContainer &InArray);`
- L125 _public function_ `void PostReplicatedChange(const struct FActiveGameplayCueContainer &InArray)`
- L127 _public prototype_ `FString GetDebugString();`

#### struct `FActiveGameplayCueContainer`  
`struct FActiveGameplayCueContainer : public FFastArraySerializer`  
_L131-171_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FFastArraySerializer`
- L136 _public member_ `TArray< FActiveGameplayCue > GameplayCues;` — `UPROPERTY()`
- L138 _public prototype_ `void SetOwner(UAbilitySystemComponent* InOwner);`
- L139 _public prototype_ `UAbilitySystemComponent* GetOwner() const;`
- L142 _public member_ `bool bMinimalReplication;` — Should this container only replicate in minimal replication mode
- L144 _public prototype_ `void AddCue(const FGameplayTag& Tag, const FPredictionKey& PredictionKey, const FGameplayCueParameters& Parameters);`
- L145 _public prototype_ `void RemoveCue(const FGameplayTag& Tag);`
- L148 _public prototype_ `void PredictiveRemove(const FGameplayTag& Tag);` — Marks as predictively removed so that we dont invoke remove event twice due to onrep
- L150 _public prototype_ `void PredictiveAdd(const FGameplayTag& Tag, FPredictionKey& PredictionKey);`
- L153 _public prototype_ `bool HasCue(const FGameplayTag& Tag) const;` — Does explicit check for gameplay cue tag
- L156 _public prototype_ `bool ShouldReplicate() const;` — Returns true if the instance should be replicated. If false the property is allowed to be disabled for replication.
- L158 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms);`
- L161 _public prototype_ `void RemoveAllCues();` — Will broadcast the OnRemove event for all currently active cues
- L165 _private prototype_ `int32 GetGameStateTime(const UWorld* World) const;`
- L168 _private member_ `TObjectPtr<class UAbilitySystemComponent> Owner = nullptr;` — `UPROPERTY(NotReplicated)`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FActiveGameplayCueContainer > : public TStructOpsTypeTraitsBase2< FActiveGameplayCueContainer >`  
_L174-180_
- inherits: `TStructOpsTypeTraitsBase2<FActiveGameplayCueContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L177-179_

#### struct `FGameplayCueTag`  
`struct FGameplayCueTag`  
_L187-198_
- reflection: `USTRUCT(BlueprintType)`
- desc: Wrapper struct around a gameplaytag with the GameplayCue category. This also allows for a details customization
- L192 _public member_ `FGameplayTag GameplayCueTag;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories="GameplayCue"), Category="GameplayCue")`
- L194 _public function_ `bool IsValid() const`

#### struct `FMinimalGameplayCueReplicationProxy`  
`struct FMinimalGameplayCueReplicationProxy`  
_L207-255_
- reflection: `USTRUCT()`
- desc: An alternative way to replicating gameplay cues. This does not use fast TArray serialization and does not serialize gameplaycue parameters. The parameters are created on the receiving side with default information. This will be more efficient with server cpu but will take more bandwidth when the array changes. To use, put this on your replication proxy actor (such a the pawn). Call SetOwner, PreReplication and RemoveallCues in the appropriate places.
- L211 _public prototype_ `FMinimalGameplayCueReplicationProxy();`
- L214 _public prototype_ `void SetOwner(UAbilitySystemComponent* ASC);` — Set Owning ASC. This is what the GC callbacks are called on.
- L217 _public prototype_ `void PreReplication(const FActiveGameplayCueContainer& SourceContainer);` — Copies data in from an FActiveGameplayCueContainer (such as the one of the ASC). You must call this manually from PreReplication.
- L220 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Custom NetSerialization to pack the entire array
- L223 _public prototype_ `void RemoveAllCues();` — Will broadcast the OnRemove event for all currently active cues
- L226 _public function_ `void SetRequireNonOwningNetConnection(bool b)` — If true, we will skip updating the Owner ASC if we replicate on a connection owned by the ASC
- L229 _public member_ `TFunction<void(FGameplayCueParameters&, UAbilitySystemComponent*)> InitGameplayCueParametersFunc;` — Called to init parameters
- L231 _public function_ `bool operator==(const FMinimalGameplayCueReplicationProxy& Other) const`
- L232 _public function_ `bool operator!=(const FMinimalGameplayCueReplicationProxy& Other) const`
- L234 _public function_ `bool operator==(const FActiveGameplayCueContainer& Other) const`
- L235 _public function_ `bool operator!=(const FActiveGameplayCueContainer& Other) const`
- L243 _private member_ `TArray< FGameplayTag, TInlineAllocator<NumInlineTags> > ReplicatedTags;`
- L244 _private member_ `TArray< FVector_NetQuantize, TInlineAllocator<NumInlineTags> > ReplicatedLocations;`
- L245 _private member_ `TArray< FGameplayTag, TInlineAllocator<NumInlineTags> > LocalTags;`
- L246 _private member_ `TBitArray< TInlineAllocator<NumInlineTags> > LocalBitMask;`
- L249 _private member_ `TObjectPtr<UAbilitySystemComponent> Owner = nullptr;` — `UPROPERTY()`
- L251 _private member_ `int32 LastSourceArrayReplicationKey = -1;`
- L253 _private member_ `bool bRequireNonOwningNetConnection = false;`
- L254 _private member_ `bool bCachedModifiedOwnerTags = false;`

#### enum `FMinimalGameplayCueReplicationProxy::(anonymous)`  
`enum`  
_L241-241_

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FMinimalGameplayCueReplicationProxy > : public TStructOpsTypeTraitsBase2< FMinimalGameplayCueReplicationProxy >`  
_L258-266_
- inherits: `TStructOpsTypeTraitsBase2<FMinimalGameplayCueReplicationProxy>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L261-265_

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L18 _namespace_ `namespace UE`
- L18 _namespace_ `namespace Net` (scope `UE`)
- L178 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anon9791d0460103`)
- L241 _enumerator_ `enum { NumInlineTags = 16 }; TArray< FGameplayTag` (scope `FMinimalGameplayCueReplicationProxy::__anon9791d0460203`)
- L262 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon9791d0460303`)
- L263 _enumerator_ `WithNetSharedSerialization = true` (scope `TStructOpsTypeTraits::__anon9791d0460303`)
- L264 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon9791d0460303`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueManager.h` (Public)


#### enum `EGameplayCueExecutionOptions`  
`enum class EGameplayCueExecutionOptions : int32`  
_L32-46_
- desc: Options to specify what parts of gameplay cue execution should be skipped
- L35 _public enumerator_ `Default = 0` — Default options, check everything
- L37 _public enumerator_ `IgnoreInterfaces = 0x00000001` — Skip gameplay cue interface check
- L39 _public enumerator_ `IgnoreNotifies = 0x00000002` — Skip spawning notifies
- L41 _public enumerator_ `IgnoreTranslation = 0x00000004` — Skip tag translation step
- L43 _public enumerator_ `IgnoreSuppression = 0x00000008` — Ignores suppression check, always spawns
- L45 _public enumerator_ `IgnoreDebug = 0x00000010` — Don't show debug visualizations

#### struct `FGameplayCueObjectLibrary`  
`struct FGameplayCueObjectLibrary`  
_L51-106_
- reflection: `USTRUCT()`
- desc: An ObjectLibrary for the GameplayCue Notifies. Wraps 2 underlying UObjectLibraries plus options/delegates for how they are loaded
- L54 _public function_ `FGameplayCueObjectLibrary() : ActorObjectLibrary(nullptr) , StaticObjectLibrary(nullptr) , CueSet(nullptr) , AsyncPriority(0) , bShouldSyncScan(false) , bShouldAsyncLoad(false) , bShouldSyncLoad(false) , bHasBeenInitialized(false)`
- L68 _public member_ `TArray<FString> Paths;` — `UPROPERTY()` — Paths to search for
- L71 _public member_ `FOnGameplayCueNotifySetLoaded OnLoaded;` — Callback for when load finishes
- L74 _public member_ `FShouldLoadGCNotifyDelegate ShouldLoad;` — Callback for "should I add this FAssetData to the set"
- L78 _public member_ `TObjectPtr<UObjectLibrary> ActorObjectLibrary;` — `UPROPERTY()` — Object library for actor based notifies
- L82 _public member_ `TObjectPtr<UObjectLibrary> StaticObjectLibrary;` — `UPROPERTY()` — Object library for object based notifies
- L86 _public member_ `TObjectPtr<UGameplayCueSet> CueSet;` — `UPROPERTY()` — Set to put the loaded asset data into. If null we will use the global set (RuntimeGameplayCueObjectLibrary.CueSet)
- L89 _public member_ `TAsyncLoadPriority AsyncPriority;` — Priority to use if async loading
- L93 _public member_ `bool bShouldSyncScan;` — `UPROPERTY()` — Should we force a sync scan on the asset registry in order to discover asset data, or just use what is there
- L97 _public member_ `bool bShouldAsyncLoad;` — `UPROPERTY()` — Should we start async loading everything that we find (that passes ShouldLoad delegate check)
- L101 _public member_ `bool bShouldSyncLoad;` — `UPROPERTY()` — Should we sync load everything that we find (that passes ShouldLoad delegate check)
- L105 _public member_ `bool bHasBeenInitialized;` — `UPROPERTY()` — True if this has been initialized with correct data

#### struct `FAsyncLoadPendingGameplayCue`  
`struct FAsyncLoadPendingGameplayCue`  
_L109-126_
- desc: While a GameplayCueNotify class is being loaded async, GameplayCue events will be deferred until load completion.
- L111 _public function_ `FAsyncLoadPendingGameplayCue() : OwningSet(nullptr), GameplayCueTag(), TargetActor(nullptr), EventType(EGameplayCueEvent::Type::OnActive), Parameters()`
- L116 _public function_ `FAsyncLoadPendingGameplayCue(TWeakObjectPtr<UGameplayCueSet> OwningSet, FGameplayTag GameplayCueTag, TWeakObjectPtr<AActor> TargetActor, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) : OwningSet(OwningSet), GameplayCueTag(GameplayCueTag), TargetActor(TargetActor), EventType(EventType), Parameters(Parameters)`
- L121 _public member_ `TWeakObjectPtr<UGameplayCueSet> OwningSet;`
- L122 _public member_ `FGameplayTag GameplayCueTag;`
- L123 _public member_ `TWeakObjectPtr<AActor> TargetActor;`
- L124 _public member_ `TEnumAsByte<EGameplayCueEvent::Type> EventType;`
- L125 _public member_ `FGameplayCueParameters Parameters;`

#### class `UGameplayCueManager`  
`class UGameplayCueManager : public UDataAsset`  
_L130-443_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: Singleton manager object that handles dispatching gameplay cues and spawning GameplayCueNotify actors as needed
- L137 _private prototype_ `virtual void InvokeGameplayCueExecuted_FromSpec(UAbilitySystemComponent* OwningComponent, const FGameplayEffectSpec& Spec, FPredictionKey PredictionKey);`
- L138 _private prototype_ `virtual void InvokeGameplayCueExecuted(UAbilitySystemComponent* OwningComponent, const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayEffectContextHandle EffectContext);`
- L139 _private prototype_ `virtual void InvokeGameplayCueExecuted_WithParams(UAbilitySystemComponent* OwningComponent, const FGameplayTag GameplayCueTag, FPredictionKey PredictionKey, FGameplayCueParameters GameplayCueParameters);`
- L141 _private prototype_ `virtual void InvokeGameplayCueAddedAndWhileActive_FromSpec(UAbilitySystemComponent* OwningComponent, const FGameplayEffectSpec& Spec, FPredictionKey PredictionKey);`
- L144 _private prototype_ `void StartGameplayCueSendContext();` — Start or stop a gameplay cue send context. Used by FScopedGameplayCueSendContext above, when all contexts are removed the cues are flushed
- L145 _private prototype_ `void EndGameplayCueSendContext();`
- L148 _private prototype_ `virtual void FlushPendingCues();` — Send out any pending cues
- L151 _private member_ `FSimpleMulticastDelegate OnFlushPendingCues;` — Broadcasted when ::FlushPendingCues runs: useful for custom batching/gameplay cue handling
- L154 _private prototype_ `virtual void OnCreated();` — Called when manager is first created
- L157 _private prototype_ `virtual void OnEngineInitComplete();` — Called when engine has completely loaded, this is a good time to finalize things
- L160 _private prototype_ `virtual bool ProcessPendingCueExecute(FGameplayCuePendingExecute& PendingCue);` — Process a pending cue, return false if the cue should be rejected.
- L163 _private prototype_ `virtual bool DoesPendingCueExecuteMatch(FGameplayCuePendingExecute& PendingCue, FGameplayCuePendingExecute& ExistingCue);` — Returns true if two pending cues match, can be overridden in game
- L170 _private prototype_ `virtual void HandleGameplayCues(AActor* TargetActor, const FGameplayTagContainer& GameplayCueTags, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters, EGameplayCueExecutionOptions Options = EGameplayCueExecutionOptions::Default);` — Main entry point for handling a gameplaycue event. These functions will call the 3 functions below to handle gameplay cues
- L171 _private prototype_ `virtual void HandleGameplayCue(AActor* TargetActor, FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters, EGameplayCueExecutionOptions Options = EGameplayCueExecutionOptions::Default);`
- L174 _private prototype_ `virtual bool ShouldSuppressGameplayCues(AActor* TargetActor);` — 1. returns true to ignore gameplay cues
- L177 _private prototype_ `void TranslateGameplayCue(FGameplayTag& Tag, AActor* TargetActor, const FGameplayCueParameters& Parameters);` — 2. Allows Tag to be translated in place to a different Tag. See FGameplayCueTranslorManager
- L180 _private prototype_ `virtual void RouteGameplayCue(AActor* TargetActor, FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters, EGameplayCueExecutionOptions Options = EGameplayCueExecutionOptions::Default);` — 3. Actually routes the gameplaycue event to the right place.
- L194 _private prototype_ `static void AddGameplayCue_NonReplicated(AActor* Target, const FGameplayTag GameplayCueTag, const FGameplayCueParameters& Parameters);` — Convenience methods for invoking non-replicated gameplay cue events. We want to avoid exposing designers the choice of "is this gameplay cue replicated or non-replicated?". We want to make the decision for them in most cases: - Abilities will always use replicated GameplayCue events because they are not executed on simulated proxies. - Animations always use non-replicated GameplayCue events because they are always executed on simulated proxies. Sometimes it will be useful to give designers both options: in actor classes where there are many possible use cases. Still, we should keep the choice confined to the actor class, and not globally.  E.g., Don't add both choices to the function library since they would appear everywhere. Add the choices to the actor class so they only appear there.
- L195 _private prototype_ `static void RemoveGameplayCue_NonReplicated(AActor* Target, const FGameplayTag GameplayCueTag, const FGameplayCueParameters& Parameters);`
- L196 _private prototype_ `static void ExecuteGameplayCue_NonReplicated(AActor* Target, const FGameplayTag GameplayCueTag, const FGameplayCueParameters& Parameters);`
- L201 _private prototype_ `virtual void EndGameplayCuesFor(AActor* TargetActor);` — Force any instanced GameplayCueNotifies to stop
- L204 _private prototype_ `virtual AGameplayCueNotify_Actor* GetInstancedCueActor(AActor* TargetActor, UClass* GameplayCueNotifyActorClass, const FGameplayCueParameters& Parameters);` — Returns the cached instance cue. Creates it if it doesn't exist.
- L207 _private prototype_ `virtual void NotifyGameplayCueActorFinished(AGameplayCueNotify_Actor* Actor);` — Notify that this actor is finished and should be destroyed or recycled
- L210 _private prototype_ `virtual void NotifyGameplayCueActorEndPlay(AGameplayCueNotify_Actor* Actor);` — Notify to say the actor is about to be destroyed and the GC manager needs to remove references to it. This should not happen in normal play with recycling enabled, but could happen in replays.
- L213 _private prototype_ `void ResetPreallocation(UWorld* World);` — Resets preallocation for a given world
- L216 _private prototype_ `void UpdatePreallocation(UWorld* World);` — Prespawns a single actor for gameplaycue notify actor classes that need prespawning (should be called by outside gamecode, such as gamestate)
- L218 _private prototype_ `void OnPostWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);`
- L220 _private prototype_ `void OnPreReplayScrub(UWorld* World);`
- L223 _private prototype_ `void DumpPreallocationStats(const FPreallocationInfo& PreallocationInfo, bool bWarnOnActiveActors = false);` — Prints what classes exceeded their preallocation sizes during runtime
- L241 _private prototype_ `UGameplayCueSet* GetRuntimeCueSet();` — Returns the Ryntime cueset, which is the global cueset used in runtime, as opposed to the editor cue set which is used only when running the editor
- L244 _private prototype_ `void InitializeRuntimeObjectLibrary();` — Called to setup and initialize the runtime library. The passed in paths will be scanned and added to the global gameplay cue set where appropriate
- L247 _private prototype_ `TArray<UGameplayCueSet*> GetGlobalCueSets();` — Will return the Runtime cue set and the EditorCueSet, if the EditorCueSet is available. This is used mainly for handling asset created/deleted in the editor
- L251 _private prototype_ `void InitializeEditorObjectLibrary();` — Called from editor to soft load all gameplay cue notifies for the GameplayCueEditor
- L254 _private prototype_ `void RequestPeriodicUpdateOfEditorObjectLibraryWhileWaitingOnAssetRegistry();` — Calling this will make the GC manager periodically refresh the EditorObjectLibrary until the asset registry is finished scanning
- L257 _private prototype_ `void GetEditorObjectLibraryGameplayCueNotifyFilenames(TArray<FString>& Filenames) const;` — Get filenames of all GC notifies we know about (loaded or not). Useful for cooking
- L260 _private prototype_ `void LoadNotifyForEditorPreview(FGameplayTag GameplayCueTag);` — Looks in the EditorObjectLibrary for a notify for this tag, if it finds it, it loads it and puts it in the RuntimeObjectLibrary so that it can be previewed in the editor
- L262 _private prototype_ `UGameplayCueSet* GetEditorCueSet();`
- L264 _private member_ `FSimpleMulticastDelegate OnEditorObjectLibraryUpdated;`
- L265 _private member_ `bool EditorObjectLibraryFullyInitialized;`
- L267 _private member_ `FTimerHandle EditorPeriodicUpdateHandle;`
- L272 _protected prototype_ `virtual bool ShouldSyncScanRuntimeObjectLibraries() const;`
- L273 _protected prototype_ `virtual bool ShouldSyncLoadRuntimeObjectLibraries() const;`
- L274 _protected prototype_ `virtual bool ShouldAsyncLoadRuntimeObjectLibraries() const;`
- L275 _protected prototype_ `virtual bool ShouldDeferScanningRuntimeLibraries() const;`
- L278 _protected prototype_ `void RefreshObjectLibraries();` — Refreshes the existing, already initialized, object libraries.
- L281 _protected prototype_ `virtual TSharedPtr<FStreamableHandle> InitObjectLibrary(FGameplayCueObjectLibrary& Library);` — Internal function to actually init the FGameplayCueObjectLibrary.  Returns StreamableHandle when asset async loading is requested.
- L283 _protected prototype_ `virtual TArray<FString> GetAlwaysLoadedGameplayCuePaths();`
- L286 _protected function_ `virtual TArray<FString> GetValidGameplayCuePaths()` — returns list of valid gameplay cue paths. Subclasses may override this to specify locations that aren't part of the "always loaded" LoadedPaths array
- L289 _protected prototype_ `AGameplayCueNotify_Actor* FindExistingCueOnActor(const AActor& TargetActor, const TSubclassOf<AGameplayCueNotify_Actor>& CueClass, const FGameplayCueParameters& Parameters) const;` — Given a TargetActor and a CueClass, find an existing instance of the CueNotify Actor that we can reuse
- L292 _protected prototype_ `AGameplayCueNotify_Actor* FindRecycledCue(const TSubclassOf<AGameplayCueNotify_Actor>& CueClass, const UWorld& FindInWorld);` — Given a CueClass, find an already spawned (but currently unused) recycled instance that exists in FindInWorld so that we may reuse it. Note: This function also compacts the recycled instances, removing stale ones.
- L295 _protected member_ `FGameplayCueObjectLibrary RuntimeGameplayCueObjectLibrary;` — `UPROPERTY(transient)`
- L298 _protected member_ `FGameplayCueObjectLibrary EditorGameplayCueObjectLibrary;` — `UPROPERTY(transient)`
- L303 _protected member_ `TSharedPtr<FStreamableHandle> GameplayCueAssetHandle;` — Handle to maintain ownership of gameplay cue assets. Note:	Only the latest handle to async load request is cached. If projects require multiple concurrent asynchronous loads, handles returned from InitObjectLibrary should be cached as needed.
- L307 _public function_ `virtual bool ShouldLoadGameplayCueAssetData(const FAssetData& Data) const` — Called before loading any gameplay cue notifies from object libraries. Allows subclasses to skip notifies.
- L316 _public prototype_ `virtual void AddGameplayCueNotifyPath(const FString& InPath, const bool bShouldRescanCueAssets = true);` — Add a path to the GameplayCueNotifyPaths array. Re-initalizes RuntimeObjectLibrary based on the new paths @param InPath					The path to the directory that should be added to the scan @param bShouldRescanCueAssets		If true then the runtime object library will be rebuilt.
- L326 _public prototype_ `virtual int32 RemoveGameplayCueNotifyPath(const FString& InPath, const bool bShouldRescanCueAssets = true);` — Remove the given gameplay cue notify path from the GameplayCueNotifyPaths array. Re-initalizes RuntimeObjectLibrary based on the new paths @param InPath					The path to the directory that should be removed from the scan @param bShouldRescanCueAssets		If true then the runtime object library will be rebuilt. @return Number of paths removed.
- L328 _public prototype_ `int32 FinishLoadingGameplayCueNotifies();`
- L330 _public member_ `FStreamableManager StreamableManager;`
- L332 _public prototype_ `void PrintGameplayCueNotifyMap();`
- L334 _public prototype_ `virtual void PrintLoadedGameplayCueNotifyClasses();`
- L336 _public prototype_ `virtual class UWorld* GetWorld() const override;`
- L338 _public prototype_ `static UWorld* GetCachedWorldForGameplayCueNotifies();`
- L340 _public prototype_ `DECLARE_EVENT_FiveParams(UGameplayCueManager, FOnRouteGameplayCue, AActor*, FGameplayTag, EGameplayCueEvent::Type, const FGameplayCueParameters&, EGameplayCueExecutionOptions);`
- L341 _public function_ `FOnRouteGameplayCue& OnGameplayCueRouted()`
- L346 _public prototype_ `void HandleAssetAdded(UObject *Object);` — Handles updating an object library when a new asset is created
- L349 _public prototype_ `void HandleAssetDeleted(UObject *Object);` — Handles cleaning up an object library if it matches the passed in object
- L352 _public prototype_ `void HandleAssetRenamed(const FAssetData& Data, const FString& String);` — Warns if we move a GameplayCue notify out of the valid search paths
- L354 _public prototype_ `bool VerifyNotifyAssetIsInValidPath(FString Path);`
- L356 _public member_ `bool bAccelerationMapOutdated;`
- L358 _public member_ `FOnGameplayCueNotifyChange OnGameplayCueNotifyAddOrRemove;`
- L361 _public member_ `static class USceneComponent* PreviewComponent;` — Animation Preview Hacks
- L362 _public member_ `static UWorld* PreviewWorld;`
- L363 _public member_ `static FGameplayCueProxyTick PreviewProxyTick;`
- L366 _public prototype_ `static bool IsGameplayCueRecylingEnabled();`
- L368 _public function_ `virtual bool ShouldAsyncLoadObjectLibrariesAtStart() const`
- L370 _public member_ `FGameplayCueTranslationManager TranslationManager;`
- L377 _public prototype_ `virtual FGameplayCueDebugInfo* GetDebugInfo(int32 Handle, bool Reset=false);`
- L381 _public prototype_ `virtual bool ShouldSyncLoadMissingGameplayCues() const;` — If true, this will synchronously load missing gameplay cues
- L384 _public prototype_ `virtual bool ShouldAsyncLoadMissingGameplayCues() const;` — If true, this will asynchronously load missing gameplay cues, and execute cue when the load finishes
- L387 _public prototype_ `bool IsAsyncLoadingGameplayCueNotifyClass(const FSoftObjectPath& CueNotifyClass) const;` — Whether a GameplayCueNotify class is currently loading (async load requested by this and streaming callback not received yet).
- L390 _public prototype_ `virtual bool HandleMissingGameplayCue(UGameplayCueSet* OwningSet, struct FGameplayCueNotifyData& CueData, AActor* TargetActor, EGameplayCueEvent::Type EventType, FGameplayCueParameters& Parameters);` — Handles what to do if a missing cue is requested. If return true, this was loaded and execution should continue
- L396 _protected prototype_ `virtual void ReloadObjectLibrary(UWorld* World, const UWorld::InitializationValues IVS);` — This handles the case where GameplayCueNotifications have changed between sessions, which is possible in editor.
- L399 _protected prototype_ `void BuildCuesToAddToGlobalSet(TConstArrayView<FAssetData> AssetDataList, FName TagPropertyName, TArray<struct FGameplayCueReferencePair>& OutCuesToAdd, TArray<FSoftObjectPath>& OutAssetsToLoad, FShouldLoadGCNotifyDelegate = FShouldLoadGCNotifyDelegate());`
- L402 _protected prototype_ `void CheckForTooManyRPCs(FName FuncName, const FGameplayCuePendingExecute& PendingCue, const FString& CueID, const FGameplayEffectContext* EffectContext);` — The cue manager has a tendency to produce a lot of RPCs. This logs out when we are attempting to fire more RPCs than will actually go off
- L404 _protected prototype_ `void OnGameplayCueNotifyAsyncLoadComplete(TArray<FSoftObjectPath> StringRef);`
- L406 _protected prototype_ `void OnMissingCueAsyncLoadComplete(FSoftObjectPath LoadedNotifyClass);`
- L408 _protected prototype_ `void CheckForPreallocation(UClass* GCClass);`
- L412 _protected member_ `TArray<TObjectPtr<UClass>> LoadedGameplayCueNotifyClasses;` — `UPROPERTY(transient)` — Hardref to the gameplaycue notify classes we have async loaded
- L416 _protected member_ `TArray<TSubclassOf<AGameplayCueNotify_Actor>> GameplayCueClassesForPreallocation;` — `UPROPERTY(transient)` — Classes that we need to preallocate instances for
- L420 _protected member_ `TArray<FGameplayCuePendingExecute> PendingExecuteCues;` — `UPROPERTY(transient)` — List of gameplay cue executes that haven't been processed yet
- L424 _protected member_ `int32 GameplayCueSendContextCount;` — `UPROPERTY(transient)` — Number of active gameplay cue send contexts, when it goes to 0 cues are flushed
- L427 _protected member_ `static UWorld* CurrentWorld;` — Cached world we are currently handling cues for. Used for non instanced GC Notifies that need world.
- L429 _protected prototype_ `FPreallocationInfo& GetPreallocationInfo(const UWorld* World);`
- L432 _protected member_ `TArray<FPreallocationInfo> PreallocationInfoList_Internal;` — `UPROPERTY(transient)`
- L435 _protected member_ `TMap<FSoftObjectPath, TArray<FAsyncLoadPendingGameplayCue>> AsyncLoadPendingGameplayCues;` — While a GCN class was not loaded yet, events are requested and async loading is enabled, cache them until the class finishes async loading.
- L437 _protected member_ `FOnRouteGameplayCue OnRouteGameplayCue;`
- L441 _private prototype_ `void AddPendingCueExecuteInternal(FGameplayCuePendingExecute& PendingCue);`

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L21 _macro_ `#define GAMEPLAYCUE_DEBUG 0`
- L27 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGameplayCueNotifySetLoaded, TArray<FSoftObjectPath>);`
- L27 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGameplayCueNotifySetLoaded, TArray<FSoftObjectPath>);`
- L28 _delegate_ `DECLARE_DELEGATE_OneParam(FGameplayCueProxyTick, float);`
- L28 _prototype_ `DECLARE_DELEGATE_OneParam(FGameplayCueProxyTick, float);`
- L29 _delegate_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FShouldLoadGCNotifyDelegate, const FAssetData&, FName);`
- L29 _prototype_ `DECLARE_DELEGATE_RetVal_TwoParams(bool, FShouldLoadGCNotifyDelegate, const FAssetData&, FName);`
- L47 _prototype_ `ENUM_CLASS_FLAGS(EGameplayCueExecutionOptions);`
- L340 _delegate_ `DECLARE_EVENT_FiveParams(UGameplayCueManager, FOnRouteGameplayCue, AActor*, FGameplayTag, EGameplayCueEvent::Type, const FGameplayCueParameters&, EGameplayCueExecutionOptions);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueNotifyTypes.h` (Public)


#### enum `EGameplayCueNotify_EffectPlaySpace`  
`enum class EGameplayCueNotify_EffectPlaySpace : uint8`  
_L68-75_
- reflection: `UENUM(BlueprintType)`
- desc: EGameplayCueNotify_EffectPlaySpace Used by some effects (like camera shakes) to specify what coordinate space the they should be applied in.
- L71 _public enumerator_ `WorldSpace` — Play the effect in world space.
- L74 _public enumerator_ `CameraSpace` — Play the effect in camera space.

#### enum `EGameplayCueNotify_LocallyControlledSource`  
`enum class EGameplayCueNotify_LocallyControlledSource : uint8`  
_L84-91_
- reflection: `UENUM(BlueprintType)`
- desc: EGameplayCueNotify_LocallyControlledSource Specifies what actor to use when determining if the gameplay cue notify is locally controlled.
- L87 _public enumerator_ `InstigatorActor` — Use the instigator actor as the source when deciding the locally controlled policy.
- L90 _public enumerator_ `TargetActor` — Use the target actor as the source when deciding the locally controlled policy.

#### enum `EGameplayCueNotify_LocallyControlledPolicy`  
`enum class EGameplayCueNotify_LocallyControlledPolicy : uint8`  
_L100-110_
- reflection: `UENUM(BlueprintType)`
- desc: EGameplayCueNotify_LocallyControlledPolicy Specifies if the gameplay cue notify should spawn based on it being locally controlled.
- L103 _public enumerator_ `Always` — Always spawns regardless of locally controlled.
- L106 _public enumerator_ `LocalOnly` — Only spawn if the source actor is locally controlled.
- L109 _public enumerator_ `NotLocal` — Only spawn if the source actor is NOT locally controlled.

#### struct `FGameplayCueNotify_SpawnCondition`  
`struct FGameplayCueNotify_SpawnCondition final`  
_L119-150_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_SpawnCondition Conditions used to determine if the gameplay cue notify should spawn.
- L123 _public prototype_ `FGameplayCueNotify_SpawnCondition();`
- L125 _public prototype_ `bool ShouldSpawn(const FGameplayCueNotify_SpawnContext& SpawnContext) const;`
- L129 _public member_ `EGameplayCueNotify_LocallyControlledSource LocallyControlledSource;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Source actor to use when determining if it is locally controlled.
- L133 _public member_ `EGameplayCueNotify_LocallyControlledPolicy LocallyControlledPolicy;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Locally controlled policy used to determine if the gameplay cue effects should spawn.
- L137 _public member_ `float ChanceToPlay;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "1.0", ClampMax = "1.0"))` — Random chance to play the effects.  (1.0 = always play,  0.0 = never play)
- L142 _public member_ `TArray<TEnumAsByte<EPhysicalSurface>> AllowedSurfaceTypes;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — The gameplay cue effects will only spawn if the surface type is in this list. An empty list means everything is allowed.
- L143 _public member_ `mutable FGameplayCueNotify_SurfaceMask AllowedSurfaceMask;`
- L148 _public member_ `TArray<TEnumAsByte<EPhysicalSurface>> RejectedSurfaceTypes;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — The gameplay cue effects will only spawn if the surface type is NOT in this list. An empty list means nothing will be rejected.
- L149 _public member_ `mutable FGameplayCueNotify_SurfaceMask RejectedSurfaceMask;`

#### enum `EGameplayCueNotify_AttachPolicy`  
`enum class EGameplayCueNotify_AttachPolicy : uint8`  
_L159-166_
- reflection: `UENUM(BlueprintType)`
- desc: EGameplayCueNotify_AttachPolicy Specifies if the gameplay cue notify should attach to the target actor.
- L162 _public enumerator_ `DoNotAttach` — Do not attach to the target actor.  The target may still be used to get location and other information.
- L165 _public enumerator_ `AttachToTarget` — Attach to the target actor if possible.

#### struct `FGameplayCueNotify_PlacementInfo`  
`struct FGameplayCueNotify_PlacementInfo final`  
_L175-215_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_PlacementInfo Specifies how the gameplay cue notify will be positioned in the world.
- L179 _public prototype_ `FGameplayCueNotify_PlacementInfo();`
- L181 _public prototype_ `bool FindSpawnTransform(const FGameplayCueNotify_SpawnContext& SpawnContext, FTransform& OutTransform) const;`
- L183 _public prototype_ `void SetComponentTransform(USceneComponent* Component, const FTransform& Transform) const;`
- L184 _public prototype_ `void TryComponentAttachment(USceneComponent* Component, USceneComponent* AttachComponent) const;`
- L188 _public member_ `FName SocketName;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Target's socket (or bone) used for location and rotation.  If "None", it uses the target's root.
- L192 _public member_ `EGameplayCueNotify_AttachPolicy AttachPolicy;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Whether to attach to the target actor or not attach.
- L196 _public member_ `EAttachmentRule AttachmentRule;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — How the transform is handled when attached.
- L200 _public member_ `uint32 bOverrideRotation : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, will always spawn using rotation override.
- L204 _public member_ `uint32 bOverrideScale : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, will always spawn using the scale override.
- L209 _public member_ `FRotator RotationOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideRotation"))` — If enabled, will always spawn using rotation override. This will also set the rotation to be absolute, so any changes to the parent's rotation will be ignored after attachment.
- L214 _public member_ `FVector ScaleOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideScale"))` — If enabled, will always spawn using scale override. This will also set the scale to be absolute, so any changes to the parent's scale will be ignored after attachment.

#### struct `FGameplayCueNotify_SpawnContext`  
`struct FGameplayCueNotify_SpawnContext final`  
_L223-261_
- desc: FGameplayCueNotify_SpawnContext Temporary spawn information collected from input parameters.
- L227 _public prototype_ `FGameplayCueNotify_SpawnContext(UWorld* InWorld, AActor* InTargetActor, const FGameplayCueParameters& InCueParameters);`
- L229 _public function_ `void SetDefaultSpawnCondition(const FGameplayCueNotify_SpawnCondition* InSpawnCondition)`
- L230 _public function_ `void SetDefaultPlacementInfo(const FGameplayCueNotify_PlacementInfo* InPlacementInfo)`
- L232 _public function_ `const FGameplayCueNotify_PlacementInfo& GetPlacementInfo(bool bUseOverride, const FGameplayCueNotify_PlacementInfo& PlacementInfoOverride) const`
- L237 _public function_ `const FGameplayCueNotify_SpawnCondition& GetSpawnCondition(bool bUseOverride, const FGameplayCueNotify_SpawnCondition& SpawnConditionOverride) const`
- L242 _public prototype_ `APlayerController* FindLocalPlayerController(EGameplayCueNotify_LocallyControlledSource Source) const;`
- L246 _protected prototype_ `void InitializeContext();`
- L250 _public member_ `UWorld* World;`
- L251 _public member_ `AActor* TargetActor;`
- L252 _public member_ `const FGameplayCueParameters& CueParameters;`
- L253 _public member_ `const FHitResult* HitResult;`
- L254 _public member_ `USceneComponent* TargetComponent;`
- L255 _public member_ `EPhysicalSurface SurfaceType;`
- L259 _private member_ `const FGameplayCueNotify_SpawnCondition* DefaultSpawnCondition;`
- L260 _private member_ `const FGameplayCueNotify_PlacementInfo* DefaultPlacementInfo;`

#### struct `FGameplayCueNotify_SpawnResult`  
`struct FGameplayCueNotify_SpawnResult final`  
_L270-305_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_SpawnResult Temporary structure used to track results of spawning components.
- L274 _public prototype_ `FGameplayCueNotify_SpawnResult();`
- L276 _public prototype_ `void Reset();`
- L280 _public member_ `TArray<TObjectPtr<UFXSystemComponent>> FxSystemComponents;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = GameplayCueNotify)` — List of FX components spawned.  There may be null pointers here as it matches the defined order.
- L284 _public member_ `TArray<TObjectPtr<UAudioComponent>> AudioComponents;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = GameplayCueNotify)` — List of audio components spawned.  There may be null pointers here as it matches the defined order.
- L288 _public member_ `TArray<TObjectPtr<UCameraShakeBase>> CameraShakes;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = GameplayCueNotify)` — List of camera shakes played.  There will be one camera shake per local player controller if shake is played in world.
- L292 _public member_ `TArray<TScriptInterface<ICameraLensEffectInterface>> CameraLensEffects;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = GameplayCueNotify)` — List of camera len effects spawned.  There will be one camera lens effect per local player controller if the effect is played in world.
- L296 _public member_ `TObjectPtr<UForceFeedbackComponent> ForceFeedbackComponent;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = GameplayCueNotify)` — Force feedback component that was spawned.  This is only valid when force feedback is set to play in world.
- L300 _public member_ `TObjectPtr<APlayerController> ForceFeedbackTargetPC;` — `UPROPERTY(Transient)` — Player controller used to play the force feedback effect.  Used to stop the effect later.
- L304 _public member_ `TObjectPtr<UDecalComponent> DecalComponent;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = GameplayCueNotify)` — Spawned decal component.  This may be null.

#### struct `FGameplayCueNotify_ParticleInfo`  
`struct FGameplayCueNotify_ParticleInfo final`  
_L314-348_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_ParticleInfo Properties that specify how to play a particle effect.
- L318 _public prototype_ `FGameplayCueNotify_ParticleInfo();`
- L320 _public prototype_ `bool PlayParticleEffect(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L323 _public prototype_ `void ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;`
- L327 _public member_ `FGameplayCueNotify_SpawnCondition SpawnConditionOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideSpawnCondition"))` — Condition to check before spawning the particle system.
- L331 _public member_ `FGameplayCueNotify_PlacementInfo PlacementInfoOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverridePlacementInfo"))` — Defines how the particle system will be placed.
- L335 _public member_ `TObjectPtr<UNiagaraSystem> NiagaraSystem;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Niagara FX system to spawn.
- L339 _public member_ `uint32 bOverrideSpawnCondition : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the spawn condition override and not the default one.
- L343 _public member_ `uint32 bOverridePlacementInfo : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the placement info override and not the default one.
- L347 _public member_ `uint32 bCastShadow : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — If enabled, this particle system will cast a shadow.

#### struct `FGameplayCueNotify_SoundParameterInterfaceInfo`  
`struct FGameplayCueNotify_SoundParameterInterfaceInfo final`  
_L356-367_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_SoundParameterInterfaceInfo Properties that specify how to interface with the ISoundParameterControllerInterface
- L362 _public prototype_ `FGameplayCueNotify_SoundParameterInterfaceInfo();`
- L366 _public member_ `FName StopTriggerName = TEXT("OnS` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — The name of the stop trigger set via the parameter interface

#### struct `FGameplayCueNotify_SoundInfo`  
`struct FGameplayCueNotify_SoundInfo final`  
_L375-427_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_SoundInfo Properties that specify how to play a sound effect.
- L379 _public prototype_ `FGameplayCueNotify_SoundInfo();`
- L381 _public prototype_ `bool PlaySound(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L384 _public prototype_ `void ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;`
- L388 _public member_ `FGameplayCueNotify_SpawnCondition SpawnConditionOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideSpawnCondition"))` — Condition to check before playing the sound.
- L392 _public member_ `FGameplayCueNotify_PlacementInfo PlacementInfoOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverridePlacementInfo"))` — Defines how the sound will be placed.
- L396 _public member_ `TObjectPtr<USoundBase> Sound;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Sound to play.
- L399 _public member_ `TObjectPtr<USoundBase> SoundCue;` — `UPROPERTY(meta = (DeprecatedProperty, DeprecationMessage = "5.0 - SoundCue is deprecated. Instead use the Sound property. The type is USoundBase not USoundCue."))`
- L403 _public member_ `float LoopingFadeOutDuration;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — How long it should take to fade out.  Only used on looping gameplay cues.
- L409 _public member_ `float LoopingFadeVolumeLevel;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — The volume level you want the sound to fade out to over the 'Looping Fade Out Duration' before stopping. This value is irrelevant if the 'Looping Fade Out Duration' is zero. NOTE: If the fade out duration is positive and this value is not lower than the volume the sound is playing at, the sound will never stop!
- L413 _public member_ `FGameplayCueNotify_SoundParameterInterfaceInfo SoundParameterInterfaceInfo;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bUseSoundParameterInterface"))` — Defines how to interface with the sound.
- L417 _public member_ `uint32 bOverrideSpawnCondition : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the spawn condition override and not the default one.
- L421 _public member_ `uint32 bOverridePlacementInfo : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the placement info override and not the default one.
- L425 _public member_ `uint32 bUseSoundParameterInterface : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the placement info override and not the default one.

#### struct `FGameplayCueNotify_CameraShakeInfo`  
`struct FGameplayCueNotify_CameraShakeInfo final`  
_L436-490_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_CameraShakeInfo Properties that specify how to play a camera shake.
- L440 _public prototype_ `FGameplayCueNotify_CameraShakeInfo();`
- L442 _public prototype_ `bool PlayCameraShake(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L445 _public prototype_ `void ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;`
- L449 _public member_ `FGameplayCueNotify_SpawnCondition SpawnConditionOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideSpawnCondition"))` — Condition to check before playing the camera shake.
- L453 _public member_ `FGameplayCueNotify_PlacementInfo PlacementInfoOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverridePlacementInfo"))` — Defines how the camera shake will be placed.
- L457 _public member_ `TSubclassOf<UCameraShakeBase> CameraShake;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Camera shake to play.
- L461 _public member_ `float ShakeScale;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Scale applied to the camera shake.
- L465 _public member_ `EGameplayCueNotify_EffectPlaySpace PlaySpace;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — What coordinate space to play the camera shake relative to.
- L469 _public member_ `uint32 bOverrideSpawnCondition : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the spawn condition override and not the default one.
- L473 _public member_ `uint32 bOverridePlacementInfo : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the placement info override and not the default one.
- L477 _public member_ `uint32 bPlayInWorld : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — If enabled, the camera shake will be played in the world and affect all players.
- L481 _public member_ `float WorldInnerRadius;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bPlayInWorld", UIMin = "0.0", ClampMin = "0.0"))` — Players inside this radius get the full intensity camera shake.
- L485 _public member_ `float WorldOuterRadius;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bPlayInWorld", UIMin = "0.0", ClampMin = "0.0"))` — Players outside this radius do not get the camera shake applied.
- L489 _public member_ `float WorldFalloffExponent;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bPlayInWorld", UIMin = "0.0", ClampMin = "0.0"))` — Exponent that describes the shake intensity falloff curve between the inner and outer radii.  (1.0 is linear)

#### struct `FGameplayCueNotify_CameraLensEffectInfo`  
`struct FGameplayCueNotify_CameraLensEffectInfo final`  
_L499-541_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_CameraLensEffectInfo Properties that specify how to play a camera lens effect.
- L503 _public prototype_ `FGameplayCueNotify_CameraLensEffectInfo();`
- L505 _public prototype_ `bool PlayCameraLensEffect(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L508 _public prototype_ `void ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;`
- L512 _public member_ `FGameplayCueNotify_SpawnCondition SpawnConditionOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideSpawnCondition"))` — Condition to check before playing the camera lens effect.
- L516 _public member_ `FGameplayCueNotify_PlacementInfo PlacementInfoOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverridePlacementInfo"))` — Defines how the camera lens effect will be placed.
- L520 _public member_ `TSubclassOf<AActor> CameraLensEffect;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (MustImplement = "/Script/Engine.CameraLensEffectInterface"))` — Camera lens effect to play.
- L524 _public member_ `uint32 bOverrideSpawnCondition : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the spawn condition override and not the default one.
- L528 _public member_ `uint32 bOverridePlacementInfo : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the placement info override and not the default one.
- L532 _public member_ `uint32 bPlayInWorld : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — If enabled, the camera lens effect will be played in the world and affect all players.
- L536 _public member_ `float WorldInnerRadius;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bPlayInWorld", UIMin = "0.0", ClampMin = "0.0"))` — Players inside this radius get the full intensity camera lens effect.
- L540 _public member_ `float WorldOuterRadius;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bPlayInWorld", UIMin = "0.0", ClampMin = "0.0"))` — Players outside this radius do not get the camera lens effect applied.

#### struct `FGameplayCueNotify_ForceFeedbackInfo`  
`struct FGameplayCueNotify_ForceFeedbackInfo final`  
_L550-601_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_ForceFeedbackInfo Properties that specify how to play a force feedback effect.
- L554 _public prototype_ `FGameplayCueNotify_ForceFeedbackInfo();`
- L556 _public prototype_ `bool PlayForceFeedback(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L559 _public prototype_ `void ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;`
- L563 _public member_ `FGameplayCueNotify_SpawnCondition SpawnConditionOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideSpawnCondition"))` — Condition to check before playing the force feedback.
- L567 _public member_ `FGameplayCueNotify_PlacementInfo PlacementInfoOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverridePlacementInfo"))` — Defines how the force feedback will be placed.
- L571 _public member_ `TObjectPtr<UForceFeedbackEffect> ForceFeedbackEffect;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Force feedback effect to play.
- L576 _public member_ `FName ForceFeedbackTag;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Tag used to identify the force feedback effect so it can later be canceled. Warning: If this is "None" it will stop ALL force feedback effects if it is canceled.
- L580 _public member_ `uint32 bIsLooping : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — If enabled, the force feedback will be set to loop.
- L584 _public member_ `uint32 bOverrideSpawnCondition : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the spawn condition override and not the default one.
- L588 _public member_ `uint32 bOverridePlacementInfo : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the placement info override and not the default one.
- L592 _public member_ `uint32 bPlayInWorld : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — If enabled, the force feedback will be played in the world and affect all players.
- L596 _public member_ `float WorldIntensity;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bPlayInWorld"))` — Multiplier applied to the force feedback when played in world.
- L600 _public member_ `TObjectPtr<UForceFeedbackAttenuation> WorldAttenuation;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bPlayInWorld"))` — How the force feedback is attenuated over distance when played in world.

#### struct `FGameplayCueNotify_InputDevicePropertyInfo`  
`struct FGameplayCueNotify_InputDevicePropertyInfo final`  
_L610-626_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_InputDevicePropertyInfo Properties that specify how to set input device properties during a gameplay cue notify
- L614 _public prototype_ `FGameplayCueNotify_InputDevicePropertyInfo() = default;`
- L617 _public prototype_ `bool SetDeviceProperties(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;` — Set the device properties on specified on this struct on the Input Device Subsystem.
- L621 _public prototype_ `void ValidateBurstAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;` — Validate that the device properties in this effect are usable
- L625 _public member_ `TArray<TSubclassOf<UInputDeviceProperty>> DeviceProperties;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayCueNotify)` — Input Device properties to apply

#### struct `FGameplayCueNotify_DecalInfo`  
`struct FGameplayCueNotify_DecalInfo final`  
_L634-678_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_DecalInfo Properties that specify how to spawn a decal.
- L638 _public prototype_ `FGameplayCueNotify_DecalInfo();`
- L640 _public prototype_ `bool SpawnDecal(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L645 _public member_ `FGameplayCueNotify_SpawnCondition SpawnConditionOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverrideSpawnCondition"))` — Condition to check before spawning the decal.
- L649 _public member_ `FGameplayCueNotify_PlacementInfo PlacementInfoOverride;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (EditCondition = "bOverridePlacementInfo"))` — Defines how the decal will be placed.
- L653 _public member_ `TObjectPtr<UMaterialInterface> DecalMaterial;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Decal material to spawn.
- L657 _public member_ `FVector DecalSize;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, meta = (AllowPreserveRatio = "true"))` — Decal size in local space (does not include the component scale).
- L661 _public member_ `uint32 bOverrideSpawnCondition : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the spawn condition override and not the default one.
- L665 _public member_ `uint32 bOverridePlacementInfo : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, Meta = (InlineEditConditionToggle))` — If enabled, use the placement info override and not the default one.
- L669 _public member_ `uint32 bOverrideFadeOut : 1;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — If enabled, override default decal actor fade out values.
- L673 _public member_ `float FadeOutStartDelay;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, meta = (EditCondition = "bOverrideFadeOut"))` — Sets when the decal actor will start fading out.  Will override setting in class.
- L677 _public member_ `float FadeOutDuration;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify, meta = (EditCondition = "bOverrideFadeOut"))` — Sets how long it takes for decal actor to fade out.  Will override setting in class.

#### struct `FGameplayCueNotify_BurstEffects`  
`struct FGameplayCueNotify_BurstEffects final`  
_L687-726_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_BurstEffects Set of effects to spawn for a single event, used by all gameplay cue notify types.
- L691 _public prototype_ `FGameplayCueNotify_BurstEffects();`
- L693 _public prototype_ `void ExecuteEffects(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L695 _public prototype_ `void ValidateAssociatedAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;`
- L701 _protected member_ `TArray<FGameplayCueNotify_ParticleInfo> BurstParticles;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Particle systems to be spawned on gameplay cue execution.  These should never use looping effects!
- L705 _protected member_ `TArray<FGameplayCueNotify_SoundInfo> BurstSounds;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Sound to be played on gameplay cue execution.  These should never use looping effects!
- L709 _protected member_ `FGameplayCueNotify_CameraShakeInfo BurstCameraShake;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Camera shake to be played on gameplay cue execution.  This should never use a looping effect!
- L713 _protected member_ `FGameplayCueNotify_CameraLensEffectInfo BurstCameraLensEffect;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Camera lens effect to be played on gameplay cue execution.  This should never use a looping effect!
- L717 _protected member_ `FGameplayCueNotify_ForceFeedbackInfo BurstForceFeedback;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Force feedback to be played on gameplay cue execution.  This should never use a looping effect!
- L721 _protected member_ `FGameplayCueNotify_InputDevicePropertyInfo BurstDevicePropertyEffect;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayCueNotify)` — Input device properties to be applied on gameplay cue execution
- L725 _protected member_ `FGameplayCueNotify_DecalInfo BurstDecal;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Decal to be spawned on gameplay cue execution.  Actor should have fade out time or override should be set so it will clean up properly.

#### struct `FGameplayCueNotify_LoopingEffects`  
`struct FGameplayCueNotify_LoopingEffects final`  
_L735-772_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayCueNotify_LoopingEffects Set of looping effects to spawn for looping gameplay cues.
- L739 _public prototype_ `FGameplayCueNotify_LoopingEffects();`
- L741 _public prototype_ `void StartEffects(const FGameplayCueNotify_SpawnContext& SpawnContext, FGameplayCueNotify_SpawnResult& OutSpawnResult) const;`
- L743 _public prototype_ `void StopEffects(FGameplayCueNotify_SpawnResult& SpawnResult) const;`
- L745 _public prototype_ `void ValidateAssociatedAssets(const UObject* ContainingAsset, const FString& Context, class FDataValidationContext& ValidationContext) const;`
- L751 _protected member_ `TArray<FGameplayCueNotify_ParticleInfo> LoopingParticles;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Particle systems to be spawned on gameplay cue loop start.
- L755 _protected member_ `TArray<FGameplayCueNotify_SoundInfo> LoopingSounds;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Sound to be played on gameplay cue loop start.
- L759 _protected member_ `FGameplayCueNotify_CameraShakeInfo LoopingCameraShake;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Camera shake to be played on gameplay cue loop start.
- L763 _protected member_ `FGameplayCueNotify_CameraLensEffectInfo LoopingCameraLensEffect;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Camera lens effect to be played on gameplay cue loop start.
- L767 _protected member_ `FGameplayCueNotify_ForceFeedbackInfo LoopingForceFeedback;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayCueNotify)` — Force feedback to be played on gameplay cue loop start.
- L771 _protected member_ `FGameplayCueNotify_InputDevicePropertyInfo LoopingInputDevicePropertyEffect;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayCueNotify)` — Input device properties to be applied on gameplay cue loop start.

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L32 _typedef_ `typedef uint64 FGameplayCueNotify_SurfaceMask;`
- L36 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayCueNotify, Log, All);`
- L36 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogGameplayCueNotify, Log, All);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueNotify_Actor.h` (Public)


#### class `AGameplayCueNotify_Actor`  
`class AGameplayCueNotify_Actor : public AActor`  
_L20-177_
- reflection: `UCLASS(Blueprintable, meta = (ShowWorldContextPin), hidecategories = (Replication), MinimalAPI)`
- inherits: `AActor`
- L25 _private prototype_ `virtual bool HandlesEvent(EGameplayCueEvent::Type EventType) const;` — Does this GameplayCueNotify handle this type of GameplayCueEvent?
- L28 _private prototype_ `virtual void OnOwnerDestroyed(AActor* DestroyedActor);` — `UFUNCTION()`
- L30 _private prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L33 _protected prototype_ `virtual void BeginPlay() override;`
- L35 _protected prototype_ `virtual void K2_DestroyActor() override;`
- L36 _protected prototype_ `virtual void Destroyed() override;`
- L39 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L43 _public prototype_ `virtual void SetOwner( AActor* NewOwner ) override;`
- L45 _public prototype_ `virtual void PostInitProperties() override;`
- L47 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L49 _public prototype_ `virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);`
- L52 _public prototype_ `virtual void GameplayCueFinishedCallback();` — Called when the GC is finished. It may be about to go back to the recyle pool, or it may be about to be destroyed.
- L54 _public prototype_ `virtual bool GameplayCuePendingRemove();`
- L57 _public prototype_ `virtual bool Recycle();` — Called when returning to the recycled pool. Reset all state so that it can be reused. Return false if this class cannot be recycled.
- L60 _public prototype_ `virtual void ReuseAfterRecycle();` — Called when we are about to reuse the GC. Should undo anything done in Recycle like hiding the actor
- L64 _public prototype_ `virtual void K2_EndGameplayCue();` — `UFUNCTION(BlueprintCallable, Category="GameplayCueNotify", DisplayName="End (Recycle) GameplayCue", meta=(ScriptName="EndGameplayCue"))` — Ends the gameplay cue: either destroying it or recycling it. You must call this manually only if you do not use bAutoDestroyOnRemove/AutoDestroyDelay
- L67 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L72 _public member_ `bool bAutoDestroyOnRemove;` — `UPROPERTY(EditDefaultsOnly, Category = Cleanup)` — We will auto destroy (recycle) this GameplayCueActor when the OnRemove event fires (after OnRemove is called).
- L76 _public member_ `float AutoDestroyDelay;` — `UPROPERTY(EditAnywhere, Category = Cleanup)` — If bAutoDestroyOnRemove is true, the actor will stay alive for this many seconds before being auto destroyed.
- L80 _public member_ `bool WarnIfTimelineIsStillRunning;` — `UPROPERTY(EditAnywhere, Category = Cleanup)` — Warn if we have a timeline running when we cleanup this gameplay cue (we will kill the timeline either way)
- L84 _public member_ `bool WarnIfLatentActionIsStillRunning;` — `UPROPERTY(EditAnywhere, Category = Cleanup)` — Warn if we have a latent action (delay, etc) running when we cleanup this gameplay cue (we will kill the latent action either way)
- L88 _public prototype_ `void K2_HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintImplementableEvent, Category = "GameplayCueNotify", DisplayName = "HandleGameplayCue", meta=(ScriptName = "HandleGameplayCue"))` — Generic Event Graph event that will get called for every event type
- L92 _public prototype_ `bool OnExecute(AActor* MyTarget, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintNativeEvent, Category = "GameplayCueNotify")` — Called when a GameplayCue is executed, this is used for instant effects or periodic ticks
- L96 _public prototype_ `bool OnActive(AActor* MyTarget, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintNativeEvent, Category = "GameplayCueNotify", DisplayName="On Burst", meta=(ScriptName="OnBurst;OnActive"))` — Called when a GameplayCue with duration is first activated, this will only be called if the client witnessed the activation
- L100 _public prototype_ `bool WhileActive(AActor* MyTarget, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintNativeEvent, Category = "GameplayCueNotify", DisplayName="On Become Relevant", meta=(ScriptName="OnBecomeRelevant;WhileActive"))` — Called when a GameplayCue with duration is first seen as active, even if it wasn't actually just applied (Join in progress, etc)
- L104 _public prototype_ `bool OnRemove(AActor* MyTarget, const FGameplayCueParameters& Parameters);` — `UFUNCTION(BlueprintNativeEvent, Category = "GameplayCueNotify", DisplayName="On Cease Relevant", meta=(ScriptName="OnCeaseRelevant;OnRemove"))` — Called when a GameplayCue with duration is removed
- L108 _public member_ `FGameplayTag GameplayCueTag;` — `UPROPERTY(EditDefaultsOnly, Category=GameplayCue, meta=(Categories="GameplayCue"))` — Tag this notify is activated by
- L112 _public member_ `FName GameplayCueName;` — `UPROPERTY(AssetRegistrySearchable)` — Mirrors GameplayCueTag in order to be asset registry searchable
- L116 _public member_ `bool bAutoAttachToOwner;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — If true, attach this GameplayCue Actor to the target actor while it is active. Attaching is slightly more expensive than not attaching, so only enable when you need to.
- L120 _public member_ `bool IsOverride;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — Does this Cue override other cues, or is it called in addition to them? E.g., If this is Damage.Physical.Slash, we wont call Damage.Physical afer we run this cue.
- L127 _public member_ `bool bUniqueInstancePerInstigator;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — Does this cue get a new instance for each instigator? For example if two instigators apply a GC to the same source, do we create two of these GameplayCue Notify actors or just one? If the notify is simply playing FX or sounds on the source, it should not need unique instances. If this Notify is attaching a beam from the instigator to the target, it does need a unique instance per instigator.
- L134 _public member_ `bool bUniqueInstancePerSourceObject;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — Does this cue get a new instance for each source object? For example if two source objects apply a GC to the same source, do we create two of these GameplayCue Notify actors or just one? If the notify is simply playing FX or sounds on the source, it should not need unique instances. If this Notify is attaching a beam from the source object to the target, it does need a unique instance per instigator.
- L141 _public member_ `bool bAllowMultipleOnActiveEvents;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue, DisplayName="Allow Multiple On Burst Events")` — Does this cue trigger its On Burst event if it's already been triggered? This can occur when the associated tag is triggered by multiple sources and there is no unique instancing.
- L148 _public member_ `bool bAllowMultipleWhileActiveEvents;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue, DisplayName="Allow Multiple On Become Relevant Events")` — Does this cue trigger its On Become Relevant event if it's already been triggered? This can occur when the associated tag is triggered by multiple sources and there is no unique instancing.
- L152 _public member_ `int32 NumPreallocatedInstances;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — How many instances of the gameplay cue to preallocate
- L155 _public member_ `bool bInRecycleQueue;` — Set when the GC actor is in the recycle queue (E.g., not active in world. This is to prevent rentrancy in the recyle code since multiple paths can lead the GC actor there)
- L158 _public member_ `TWeakObjectPtr<AActor> CueInstigator;` — Keep track of the Instigator so we can decide if this GameplayCueNotify is one we're searching for.
- L161 _public member_ `TWeakObjectPtr<const UObject> CueSourceObject;` — Keep track of the SourceObject so we can decide if this GameplayCueNotify is one we're searching for.
- L164 _protected member_ `FTimerHandle FinishTimerHandle;`
- L166 _protected prototype_ `void ClearOwnerDestroyedDelegate();`
- L168 _protected member_ `bool bHasHandledOnActiveEvent;`
- L169 _protected member_ `bool bHasHandledWhileActiveEvent;`
- L170 _protected member_ `bool bHasHandledOnRemoveEvent;`
- L173 _private prototype_ `virtual void DeriveGameplayCueTagFromAssetName();`
- L175 _private prototype_ `void AttachToOwnerIfNecessary();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueNotify_Burst.h` (Public)


#### class `UGameplayCueNotify_Burst`  
`class UGameplayCueNotify_Burst : public UGameplayCueNotify_Static`  
_L20-52_
- reflection: `UCLASS(Blueprintable, Category = "GameplayCueNotify", Meta = (ShowWorldContextPin, DisplayName = "GCN Burst", ShortTooltip = "A one-off GameplayCueNotify that is never spawned into the world."), MinimalAPI)`
- inherits: `UGameplayCueNotify_Static`
- desc: UGameplayCueNotify_Burst This is a non-instanced gameplay cue notify for effects that are one-offs. Since it is not instanced, it cannot do latent actions such as delays and time lines.
- L26 _public prototype_ `UGameplayCueNotify_Burst();`
- L30 _protected prototype_ `virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const override;`
- L33 _protected prototype_ `void OnBurst(AActor* Target, const FGameplayCueParameters& Parameters, const FGameplayCueNotify_SpawnResult& SpawnResults) const;` — `UFUNCTION(BlueprintImplementableEvent)`
- L36 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L43 _protected member_ `FGameplayCueNotify_SpawnCondition DefaultSpawnCondition;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Defaults")` — Default condition to check before spawning anything.  Applies for all spawns unless overridden.
- L47 _protected member_ `FGameplayCueNotify_PlacementInfo DefaultPlacementInfo;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Defaults")` — Default placement rules.  Applies for all spawns unless overridden.
- L51 _protected member_ `FGameplayCueNotify_BurstEffects BurstEffects;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Effects")` — List of effects to spawn on burst.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueNotify_BurstLatent.h` (Public)


#### class `AGameplayCueNotify_BurstLatent`  
`class AGameplayCueNotify_BurstLatent : public AGameplayCueNotify_Actor`  
_L20-58_
- reflection: `UCLASS(Blueprintable, notplaceable, Category = "GameplayCueNotify", Meta = (ShowWorldContextPin, DisplayName = "GCN Burst Latent", ShortTooltip = "A one-off GameplayCueNotify that can use latent actions such as timelines."), MinimalAPI)`
- inherits: `AGameplayCueNotify_Actor`
- desc: AGameplayCueNotify_BurstLatent This is an instanced gameplay cue notify for effects that are one-offs. Since it is instanced, it can do latent things like time lines or delays.
- L26 _public prototype_ `AGameplayCueNotify_BurstLatent();`
- L30 _protected prototype_ `virtual bool Recycle() override;`
- L32 _protected prototype_ `virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) override;`
- L35 _protected prototype_ `void OnBurst(AActor* Target, const FGameplayCueParameters& Parameters, const FGameplayCueNotify_SpawnResult& SpawnResults);` — `UFUNCTION(BlueprintImplementableEvent)`
- L38 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L45 _protected member_ `FGameplayCueNotify_SpawnCondition DefaultSpawnCondition;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Defaults")` — Default condition to check before spawning anything.  Applies for all spawns unless overridden.
- L49 _protected member_ `FGameplayCueNotify_PlacementInfo DefaultPlacementInfo;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Defaults")` — Default placement rules.  Applies for all spawns unless overridden.
- L53 _protected member_ `FGameplayCueNotify_BurstEffects BurstEffects;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Effects")` — List of effects to spawn on burst.
- L57 _protected member_ `FGameplayCueNotify_SpawnResult BurstSpawnResults;` — `UPROPERTY(BlueprintReadOnly, Category = "GCN Effects")` — Results of spawned burst effects.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueNotify_HitImpact.h` (Public)


#### class `UGameplayCueNotify_HitImpact`  
`class UGameplayCueNotify_HitImpact : public UGameplayCueNotify_Static`  
_L21-36_
- reflection: `UCLASS(Blueprintable, meta = (DisplayName = "GCN Hit Impact (Deprecated)", Category = "GameplayCue", ShortTooltip = "This class is deprecated. Use UFortGameplayCueNotify_Burst (GCN Burst) instead."), MinimalAPI)`
- inherits: `UGameplayCueNotify_Static`
- L26 _private prototype_ `virtual bool HandlesEvent(EGameplayCueEvent::Type EventType) const override;` — Does this GameplayCueNotify handle this type of GameplayCueEvent?
- L28 _private prototype_ `virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;`
- L31 _private member_ `TObjectPtr<USoundBase> Sound;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayCue)`
- L35 _private member_ `TObjectPtr<UParticleSystem> ParticleSystem;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayCue)` — Effects to play for weapon attacks against specific surfaces

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueNotify_Looping.h` (Public)


#### class `AGameplayCueNotify_Looping`  
`class AGameplayCueNotify_Looping : public AGameplayCueNotify_Actor`  
_L20-99_
- reflection: `UCLASS(Blueprintable, notplaceable, Category = "GameplayCueNotify", Meta = (ShowWorldContextPin, DisplayName = "GCN Looping", ShortTooltip = "A GameplayCueNotify that has a duration that is driven by the game."), MinimalAPI)`
- inherits: `AGameplayCueNotify_Actor`
- desc: AGameplayCueNotify_Looping This is an instanced gameplay cue notify for continuous looping effects. The game is responsible for defining the start/stop by adding/removing the gameplay cue.
- L26 _public prototype_ `AGameplayCueNotify_Looping();`
- L30 _protected prototype_ `virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;`
- L31 _protected prototype_ `virtual bool Recycle() override;`
- L33 _protected prototype_ `virtual bool OnActive_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) override;`
- L34 _protected prototype_ `virtual bool WhileActive_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) override;`
- L35 _protected prototype_ `virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) override;`
- L36 _protected prototype_ `virtual bool OnRemove_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) override;`
- L39 _protected prototype_ `void OnApplication(AActor* Target, const FGameplayCueParameters& Parameters, const FGameplayCueNotify_SpawnResult& SpawnResults);` — `UFUNCTION(BlueprintImplementableEvent)`
- L42 _protected prototype_ `void OnLoopingStart(AActor* Target, const FGameplayCueParameters& Parameters, const FGameplayCueNotify_SpawnResult& SpawnResults);` — `UFUNCTION(BlueprintImplementableEvent)`
- L45 _protected prototype_ `void OnRecurring(AActor* Target, const FGameplayCueParameters& Parameters, const FGameplayCueNotify_SpawnResult& SpawnResults);` — `UFUNCTION(BlueprintImplementableEvent)`
- L48 _protected prototype_ `void OnRemoval(AActor* Target, const FGameplayCueParameters& Parameters, const FGameplayCueNotify_SpawnResult& SpawnResults);` — `UFUNCTION(BlueprintImplementableEvent)`
- L50 _protected prototype_ `void RemoveLoopingEffects();`
- L53 _protected prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L60 _protected member_ `FGameplayCueNotify_SpawnCondition DefaultSpawnCondition;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Defaults")` — Default condition to check before spawning anything.  Applies for all spawns unless overridden.
- L64 _protected member_ `FGameplayCueNotify_PlacementInfo DefaultPlacementInfo;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Defaults")` — Default placement rules.  Applies for all spawns unless overridden.
- L68 _protected member_ `FGameplayCueNotify_BurstEffects ApplicationEffects;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Application Effects (On Active)")` — List of effects to spawn on application.  These should not be looping effects!
- L72 _protected member_ `FGameplayCueNotify_SpawnResult ApplicationSpawnResults;` — `UPROPERTY(BlueprintReadOnly, Category = "GCN Application Effects (On Active)")` — Results of spawned application effects.
- L76 _protected member_ `FGameplayCueNotify_LoopingEffects LoopingEffects;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Looping Effects (While Active)")` — List of effects to spawn on loop start.
- L80 _protected member_ `FGameplayCueNotify_SpawnResult LoopingSpawnResults;` — `UPROPERTY(BlueprintReadOnly, Category = "GCN Looping Effects (While Active)")` — Results of spawned looping effects.
- L84 _protected member_ `FGameplayCueNotify_BurstEffects RecurringEffects;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Recurring Effects (On Execute)")` — List of effects to spawn for a recurring gameplay effect (e.g. each time a DOT ticks).  These should not be looping effects!
- L88 _protected member_ `FGameplayCueNotify_SpawnResult RecurringSpawnResults;` — `UPROPERTY(BlueprintReadOnly, Category = "GCN Recurring Effects (On Execute)")` — Results of spawned recurring effects.
- L92 _protected member_ `FGameplayCueNotify_BurstEffects RemovalEffects;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GCN Removal Effects (On Remove)")` — List of effects to spawn on removal.  These should not be looping effects!
- L96 _protected member_ `FGameplayCueNotify_SpawnResult RemovalSpawnResults;` — `UPROPERTY(BlueprintReadOnly, Category = "GCN Removal Effects (On Remove)")` — Results of spawned removal effects.
- L98 _protected member_ `bool bLoopingEffectsRemoved;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueNotify_Static.h` (Public)


#### class `UGameplayCueNotify_Static`  
`class UGameplayCueNotify_Static : public UObject`  
_L19-74_
- reflection: `UCLASS(Blueprintable, meta = (ShowWorldContextPin), hidecategories = (Replication), MinimalAPI)`
- inherits: `UObject`
- L24 _private prototype_ `virtual bool HandlesEvent(EGameplayCueEvent::Type EventType) const;` — Does this GameplayCueNotify handle this type of GameplayCueEvent?
- L26 _private prototype_ `virtual void OnOwnerDestroyed();`
- L28 _private prototype_ `virtual void PostInitProperties() override;`
- L30 _private prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L32 _private prototype_ `virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);`
- L34 _private prototype_ `UWorld* GetWorld() const override;`
- L37 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L42 _private prototype_ `void K2_HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) const;` — `UFUNCTION(BlueprintImplementableEvent, Category = "GameplayCueNotify", DisplayName = "HandleGameplayCue", meta=(ScriptName = "HandleGameplayCue"))` — Generic Event Graph event that will get called for every event type
- L46 _private prototype_ `bool OnExecute(AActor* MyTarget, const FGameplayCueParameters& Parameters) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "GameplayCueNotify")` — Called when a GameplayCue is executed, this is used for instant effects or periodic ticks
- L50 _private prototype_ `bool OnActive(AActor* MyTarget, const FGameplayCueParameters& Parameters) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "GameplayCueNotify")` — Called when a GameplayCue with duration is first activated, this will only be called if the client witnessed the activation
- L54 _private prototype_ `bool WhileActive(AActor* MyTarget, const FGameplayCueParameters& Parameters) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "GameplayCueNotify")` — Called when a GameplayCue with duration is first seen as active, even if it wasn't actually just applied (Join in progress, etc)
- L58 _private prototype_ `bool OnRemove(AActor* MyTarget, const FGameplayCueParameters& Parameters) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "GameplayCueNotify")` — Called when a GameplayCue with duration is removed
- L62 _private member_ `FGameplayTag GameplayCueTag;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue, meta=(Categories="GameplayCue"))` — Tag this notify is activated by
- L66 _private member_ `FName GameplayCueName;` — `UPROPERTY(AssetRegistrySearchable)` — Mirrors GameplayCueTag in order to be asset registry searchable
- L70 _private member_ `bool IsOverride;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — Does this Cue override other cues, or is it called in addition to them? E.g., If this is Damage.Physical.Slash, we wont call Damage.Physical afer we run this cue.
- L73 _private prototype_ `virtual void DeriveGameplayCueTagFromAssetName();`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueSet.h` (Public)


#### struct `FGameplayCueNotifyData`  
`struct FGameplayCueNotifyData`  
_L16-36_
- reflection: `USTRUCT()`
- L20 _public function_ `FGameplayCueNotifyData() : LoadedGameplayCueClass(nullptr) , ParentDataIdx( INDEX_NONE )`
- L27 _public member_ `FGameplayTag GameplayCueTag;` — `UPROPERTY(EditAnywhere, Category=GameplayCue)`
- L30 _public member_ `FSoftObjectPath GameplayCueNotifyObj;` — `UPROPERTY(EditAnywhere, Category=GameplayCue, meta=(AllowedClasses="/Script/GameplayAbilities.GameplayCueNotify_Static, /Script/GameplayAbilities.GameplayCueNotify_Actor"))`
- L33 _public member_ `TObjectPtr<UClass> LoadedGameplayCueClass;` — `UPROPERTY(transient)`
- L35 _public member_ `int32 ParentDataIdx;`

#### struct `FGameplayCueReferencePair`  
`struct FGameplayCueReferencePair`  
_L38-47_
- L40 _public member_ `FGameplayTag GameplayCueTag;`
- L41 _public member_ `FSoftObjectPath StringRef;`
- L43 _public function_ `FGameplayCueReferencePair(const FGameplayTag& InGameplayCueTag, const FSoftObjectPath& InStringRef) : GameplayCueTag(InGameplayCueTag) , StringRef(InStringRef)`

#### class `UGameplayCueSet`  
`class UGameplayCueSet : public UDataAsset`  
_L53-103_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: A set of gameplay cue actors to handle gameplay cue events
- L58 _private prototype_ `virtual bool HandleGameplayCue(AActor* TargetActor, FGameplayTag GameplayCueTag, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters);` — Handles the cue event by spawning the cue actor. Returns true if the event was handled.
- L61 _private prototype_ `virtual void AddCues(const TArray<FGameplayCueReferencePair>& CuesToAdd);` — Adds a list of cues to the set
- L64 _private prototype_ `virtual void RemoveCuesByTags(const FGameplayTagContainer& TagsToRemove);` — Removes all cues from the set matching any of the supplied tags
- L67 _private prototype_ `virtual void RemoveCuesByStringRefs(const TArray<FSoftObjectPath>& CuesToRemove);` — Removes all cues from the set matching the supplied string refs
- L70 _private prototype_ `virtual void RemoveLoadedClass(UClass* Class);` — Nulls reference to the loaded class. Note this doesn't remove the entire cue from the internal data structure, just the hard ref to the loaded class
- L73 _private prototype_ `virtual void GetFilenames(TArray<FString>& Filenames) const;` — Returns filenames of everything we know about (loaded or not)
- L76 _private prototype_ `virtual void GetSoftObjectPaths(TArray<FSoftObjectPath>& List) const;` — Extracts all soft object paths pointing to Cues
- L80 _private prototype_ `void CopyCueDataToSetForEditorPreview(FGameplayTag Tag, UGameplayCueSet* DestinationSet);`
- L83 _private prototype_ `virtual void UpdateCueByStringRefs(const FSoftObjectPath& CueToRemove, FString NewPath);` — Updates an existing cue
- L88 _private prototype_ `virtual void Empty();` — Removes all cues from the set
- L90 _private prototype_ `virtual void PrintCues() const;`
- L93 _private member_ `TArray<FGameplayCueNotifyData> GameplayCueData;` — `UPROPERTY(EditAnywhere, Category=CueSet)`
- L96 _private member_ `TMap<FGameplayTag, int32> GameplayCueDataMap;` — Maps GameplayCue Tag to index into above GameplayCues array.
- L98 _private prototype_ `static FGameplayTag BaseGameplayCueTag();`
- L101 _protected prototype_ `virtual bool HandleGameplayCueNotify_Internal(AActor* TargetActor, int32 DataIdx, EGameplayCueEvent::Type EventType, FGameplayCueParameters& Parameters);`
- L102 _protected prototype_ `virtual void BuildAccelerationMap_Internal();`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCueTranslator.h` (Public)


#### struct `FGameplayCueTranslationEditorOnlyData`  
`struct FGameplayCueTranslationEditorOnlyData`  
_L60-71_
- L62 _public function_ `FGameplayCueTranslationEditorOnlyData() :UniqueID(0), Enabled(true)`
- L67 _public member_ `FName EditorDescription;` — For pretty/custom printing
- L68 _public member_ `FString ToolTip;` — additional info for tooltip text (exactly where did this rule come from?)
- L69 _public member_ `int32 UniqueID;` — For filtering overrides by translation rule. Set by the GameplaycueTranslator.
- L70 _public member_ `bool Enabled;` — Is this actually enabled, or not (and if not, we may still want to draw it in the editor but greyed out). In non editor builds, the translator rule class should "just not return the rule" if its disanled.

#### struct `FGameplayCueTranslationEditorInfo`  
`struct FGameplayCueTranslationEditorInfo`  
_L73-79_
- L75 _public member_ `FGameplayTag GameplayTag;` — Will only exist if there is an existing FGameplayTag
- L76 _public member_ `FName GameplayTagName;` — Will always exist, even if tag hasn't been created
- L78 _public member_ `FGameplayCueTranslationEditorOnlyData EditorData;`

#### struct `FGameplayCueTranslationNameSwap`  
`struct FGameplayCueTranslationNameSwap`  
_L89-97_
- desc: Basis for name swaps. This swaps FromName to ToName
- L91 _public member_ `FName FromName;`
- L92 _public member_ `TArray<FName, TInlineAllocator<4> > ToNames;`
- L95 _public member_ `FGameplayCueTranslationEditorOnlyData EditorData;`

#### struct `FGameplayCueTranslatorNodeIndex`  
`struct FGameplayCueTranslatorNodeIndex`  
_L101-123_
- reflection: `USTRUCT()`
- desc: Simple index/handle for referencing items in FGameplayCueTranslationManager::TranslationLUT
- L105 _public function_ `FGameplayCueTranslatorNodeIndex() : Index(INDEX_NONE)`
- L107 _public function_ `FGameplayCueTranslatorNodeIndex(FGameplayTagNetIndex InIndex) : Index(InIndex)`
- L110 _public member_ `int32 Index;` — `UPROPERTY()`
- L112 _public function_ `bool IsValid() const`
- L114 _public function_ `inline operator int32() const`
- L119 _public function_ `inline bool operator==(const FGameplayCueTranslatorNodeIndex& Other) const`

#### struct `FGameplayCueTranslationLink`  
`struct FGameplayCueTranslationLink`  
_L127-137_
- reflection: `USTRUCT()`
- desc: Represents a translation from one FGameplayCueTranslatorNode to many others. You will have one of these links per UGameplayCueTranslator that can translate a node.
- L133 _public member_ `TObjectPtr<const UGameplayCueTranslator> RulesCDO = nullptr;` — `UPROPERTY()` — The rule that provides this translation
- L136 _public member_ `TArray< FGameplayCueTranslatorNodeIndex > NodeLookup;` — Fixed size lookup. The RulesCDO return the index into this which will translate to the new node.

#### struct `FGameplayCueTranslatorNode`  
`struct FGameplayCueTranslatorNode`  
_L141-166_
- reflection: `USTRUCT()`
- desc: A node in our translation table/graph. The node represents an actual gameplaytag or a possible gameplay tag, with links to what it can be translated into.
- L147 _public member_ `TArray<FGameplayCueTranslationLink> Links;` — `UPROPERTY()` — Ways we can be translated into another FGameplayCueTranslatorNode
- L151 _public member_ `FGameplayCueTranslatorNodeIndex CachedIndex;` — `UPROPERTY()` — Our index into FGameplayCueTranslationManager::TranslationLUT
- L155 _public member_ `FGameplayTag CachedGameplayTag;` — `UPROPERTY()` — The FGameplayTag if this tag actually exists. This will always exist at runtime. In editor builds, it may not (GameplayCueEditor)
- L159 _public member_ `FName CachedGameplayTagName;` — `UPROPERTY()` — FName of the tag. This will always be valid, whether the tag is in the GameplayTag dictionary or not.
- L162 _public member_ `TSet<const UGameplayCueTranslator*> UsedTranslators;` — Translation that have been used to "get us here" and should not be used further down the chain. To avoid recursion
- L165 _public prototype_ `FGameplayCueTranslationLink& FindOrCreateLink(const UGameplayCueTranslator* RuleClass, int32 LookupSize);` — Helper to create a new link for a given UGameplayCueTranslator

#### struct `FNameSwapData`  
`struct FNameSwapData`  
_L168-175_
- L171 _public member_ `const UGameplayCueTranslator* ClassCDO;` — Class that provided the rules
- L174 _public member_ `TArray<FGameplayCueTranslationNameSwap> NameSwaps;` — What it gave us

#### struct `FGameplayCueTranslationManager`  
`struct FGameplayCueTranslationManager`  
_L182-247_
- reflection: `USTRUCT()`
- desc: This is the struct that does the actual translation. It lives on the GameplayCueManager and encapsulates all translation logic.
- L187 _public prototype_ `void TranslateTag(FGameplayTag& Tag, AActor* TargetActor, const FGameplayCueParameters& Parameters);` — This is *the* runtime function that translates the tag (if necessary)
- L190 _public prototype_ `void BuildTagTranslationTable();` — Builds all our translation tables. This works backwards by looking at the tags in the dictionary and determining which could be derived from translation rules. This is pretty fast.
- L191 _public prototype_ `bool BuildTagTranslationTable_r(const FName& TagName, const TArray<FName>& SplitNames);`
- L197 _public prototype_ `void BuildTagTranslationTable_Forward();` — Builds all *possible* translation tables. This works forwards by looking at existing tags and determining what translated tags could be dervied from them. This WILL populate the TranslationLUT with all possible tags, not just ones that exist in the dictionar. This is not as fast and is onyl called in the editor.
- L198 _public prototype_ `void BuildTagTranslationTable_Forward_r(const FName& TagName, const TArray<FName>& SplitNames);`
- L201 _public prototype_ `void RefreshNameSwaps();` — refresh our name swap rules. Called internally by the manager and externally by GC tool
- L203 _public prototype_ `void PrintTranslationTable();`
- L204 _public prototype_ `void PrintTranslationTable_r(FGameplayCueTranslatorNode& Node, FString IdentStr=FString());`
- L209 _public prototype_ `bool GetTranslatedTags(const FName& ParentTag, TArray<FGameplayCueTranslationEditorInfo>& Children);` — Used by the GC editor to enumerate possible translation tags. Never called at runtime.
- L210 _public function_ `const TArray<FNameSwapData>& GetNameSwapData() const`
- L213 _public prototype_ `FGameplayTag SearchSlowForTranslationParent(FGameplayTag Tag);` — Searches, slowly, to see if the passed in tag can be translated from something else. Don't call this at runtime.
- L220 _private member_ `TArray< FGameplayCueTranslatorNode > TranslationLUT;` — `UPROPERTY()` — The Look Up Table
- L224 _private member_ `TMap<FName, FGameplayCueTranslatorNodeIndex> TranslationNameToIndexMap;` — `UPROPERTY()` — Acceleration map from gameplay tag name to index into TranslationLUT
- L228 _private member_ `TObjectPtr<UGameplayTagsManager> TagManager = nullptr;` — `UPROPERTY()` — Cached reference to tag manager
- L231 _private member_ `TArray<FNameSwapData> AllNameSwaps;` — All name swpa rules we have gathered
- L233 _private prototype_ `bool TranslateTag_Internal(FGameplayCueTranslatorNode& Node, FGameplayTag& OutTag, const FName& TagName, AActor* TargetActor, const FGameplayCueParameters& Parameters);`
- L235 _private prototype_ `FGameplayCueTranslatorNodeIndex GetTranslationIndexForTag(const FGameplayTag& Tag, bool CreateIfInvalid=false);`
- L237 _private prototype_ `FGameplayCueTranslatorNode* GetTranslationNodeForTag(const FGameplayTag& Tag, bool CreateIfInvalid=false);`
- L238 _private prototype_ `FGameplayCueTranslatorNode* GetTranslationNodeForName(FName Name, bool CreateIfInvalid=false);`
- L240 _private prototype_ `FGameplayCueTranslatorNodeIndex GetTranslationIndexForName(FName Name, bool CreateIfInvalid=false);`
- L242 _private prototype_ `void ResetTranslationLUT();`
- L245 _private member_ `int32 TotalNumTranslations;` — Only used in debug printing/stats
- L246 _private member_ `int32 TotalNumTheoreticalTranslations;`

#### class `UGameplayCueTranslator`  
`class UGameplayCueTranslator: public UObject`  
_L261-281_
- reflection: `UCLASS(Abstract, MinimalAPI)`
- inherits: `UObject`
- L268 _public function_ `virtual void GetTranslationNameSpawns(TArray<FGameplayCueTranslationNameSwap>& SwapList) const` — return (via out param) list of tag swaps you will do. This should be deterministic/order matters for later!
- L271 _public function_ `virtual int32 GameplayCueToTranslationIndex(const FName& TagName, AActor* TargetActor, const FGameplayCueParameters& Parameters) const` — runtime function to mapping Tag/Actor/Parameters to a translation index. The returned index here maps to the array was modified in ::GetTranslationNameSpawns
- L274 _public function_ `virtual int32 GetPriority() const` — Sorting priority. Higher number = first chance to translate a tag
- L277 _public function_ `virtual bool IsEnabled() const` — Whether this translator class should be enabled. Useful for disabling WIP translators
- L280 _public function_ `virtual bool ShouldShowInTopLevelFilterList() const` — Whether this translator should be shown in the top level view of the filter tree in the gameplaycue editor. If false, we will only add this as children of top level translators

#### class `UGameplayCueTranslator_Test`  
`class UGameplayCueTranslator_Test : public UGameplayCueTranslator`  
_L287-372_
- reflection: `UCLASS()`
- inherits: `UGameplayCueTranslator`
- desc: This is an example translator class.
- L297 _public function_ `virtual void GetTranslationNameSpawns(TArray<FGameplayCueTranslationNameSwap>& SwapList) const override` — This adds the name swaps. We create 3 rules, Hero->Steel, Hero->Rampage, Hero->Kurohane. All this says is, "this <UGameplayCueTranslator_Test> can translate tags like this".
- L326 _public function_ `virtual int32 GameplayCueToTranslationIndex(const FName& TagName, AActor* TargetActor, const FGameplayCueParameters& Parameters) const` — This is called at runtime to actually do the swapping. This is a trivial example, we will use hardcoded memory addressess to switch on the 3 possible translations. A more realistic approach would be to look at something on the AActor (maybe, cast it to your base actor or interface type) or the GameplayCue parameters. Using an acceleration map may be a good idea here: your translator class could have access to a global map that maps actor* -> swap index. Important thing to understand: the int32 returned is the index into the SwapList that we created in ::GetTranslationNameSpawns()!
- L347 _public function_ `virtual bool IsEnabled() const override` — We never actually want to use this in production, so return false

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayCue_Types.h` (Public)


#### enum `EGameplayCuePayloadType`  
`enum class EGameplayCuePayloadType : uint8`  
_L23-29_
- reflection: `UENUM()`
- desc: Describes what type of payload is attached to a cue execution, we only replicate what is needed
- L26 _public enumerator_ `CueParameters` — Uses FGameplayCueParameters
- L28 _public enumerator_ `FromSpec` — Uses FGameplayEffectSpecForRPC

#### struct `FGameplayCuePendingExecute`  
`struct FGameplayCuePendingExecute`  
_L34-62_
- reflection: `USTRUCT()`
- desc: Structure to keep track of pending gameplay cues that haven't been applied yet.
- L38 _public function_ `FGameplayCuePendingExecute()`
- L41 _public member_ `TArray<FGameplayTag, TInlineAllocator<1> > GameplayCueTags;` — List of tags, we allocate one as there is almost always exactly one tag
- L45 _public member_ `FPredictionKey PredictionKey;` — `UPROPERTY()` — Prediction key that spawned this cue
- L49 _public member_ `EGameplayCuePayloadType PayloadType = EGameplayCuePayloadType::CueParameters;` — `UPROPERTY()` — What type of payload is attached to this cue
- L53 _public member_ `TObjectPtr<UAbilitySystemComponent> OwningComponent = nullptr;` — `UPROPERTY()` — What component to send the cue on
- L57 _public member_ `FGameplayEffectSpecForRPC FromSpec;` — `UPROPERTY()` — If this cue is from a spec, here's the copy of that spec
- L61 _public member_ `FGameplayCueParameters CueParameters;` — `UPROPERTY()` — Store the full cue parameters or just the effect context depending on type

#### struct `FGameplayCueNotifyActorArray`  
`struct FGameplayCueNotifyActorArray`  
_L65-71_
- reflection: `USTRUCT()`
- L70 _public member_ `TArray<TObjectPtr<AGameplayCueNotify_Actor>> Actors;` — `UPROPERTY(transient)`

#### struct `FPreallocationInfo`  
`struct FPreallocationInfo`  
_L75-89_
- reflection: `USTRUCT()`
- desc: Struct for pooling and preallocating gameplaycuenotify_actor classes. This data is per world and used to track what actors are available to recycle and which classes need to preallocate instances of those actors
- L81 _public member_ `TMap<TObjectPtr<UClass>, FGameplayCueNotifyActorArray> PreallocatedInstances;` — `UPROPERTY(transient)` — Raw list of pooled instances. This relies on NotifyGameplayCueActorEndPlay always being called when actor is destroyed
- L85 _public member_ `TArray<TSubclassOf<AGameplayCueNotify_Actor>> ClassesNeedingPreallocation;` — `UPROPERTY(transient)` — List of classes that will be pooled
- L88 _public member_ `FObjectKey OwningWorldKey;` — World that owns this list

#### struct `FScopedGameplayCueSendContext`  
`struct FScopedGameplayCueSendContext`  
_L95-99_
- desc: FScopedGameplayCueSendContext Add this around code that sends multiple gameplay cues to allow grouping them into a smalkler number of cues for more efficient networking
- L97 _public prototype_ `FScopedGameplayCueSendContext();`
- L98 _public prototype_ `~FScopedGameplayCueSendContext();`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L102 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGameplayCueNotifyChange);` — Delegate for when GC notifies are added or removed from manager
- L102 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGameplayCueNotifyChange);` — Delegate for when GC notifies are added or removed from manager

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayDebuggerCategory_Abilities.h` (Public)


#### class `FGameplayDebuggerCategory_Abilities`  
`class FGameplayDebuggerCategory_Abilities : public FGameplayDebuggerCategory`  
_L17-105_
- inherits: `FGameplayDebuggerCategory`
- L20 _public prototype_ `FGameplayDebuggerCategory_Abilities();`
- L22 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L23 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L25 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L27 _public prototype_ `void OnShowGameplayTagsToggle();`
- L28 _public prototype_ `void OnShowGameplayAbilitiesToggle();`
- L29 _public prototype_ `void OnShowGameplayEffectsToggle();`
- L30 _public prototype_ `void OnShowGameplayAttributesToggle();`
- L45 _protected prototype_ `void DrawGameplayTags(FGameplayDebuggerCanvasContext& CanvasContext, const APlayerController* OwnerPC) const;`
- L46 _protected prototype_ `void DrawGameplayAbilities(FGameplayDebuggerCanvasContext& CanvasContext, const APlayerController* OwnerPC) const;`
- L47 _protected prototype_ `void DrawGameplayEffects(FGameplayDebuggerCanvasContext& CanvasContext, const APlayerController* OwnerPC) const;`
- L48 _protected prototype_ `void DrawGameplayAttributes(FGameplayDebuggerCanvasContext& CanvasContext, const APlayerController* OwnerPC) const;`
- L90 _protected member_ `FRepData DataPack;`
- L92 _protected prototype_ `bool WrapStringAccordingToViewport(const FString& iStr, FString& oStr, FGameplayDebuggerCanvasContext& CanvasContext, float ViewportWitdh) const;`
- L95 _private prototype_ `TArray<FRepData::FGameplayAttributeDebug> CollectAttributeData(const APlayerController* OwnerPC, const UAbilitySystemComponent* AbilityComp) const;`
- L96 _private prototype_ `TArray<FRepData::FGameplayEffectDebug> CollectEffectsData(const APlayerController* OwnerPC, const UAbilitySystemComponent* AbilityComp) const;`
- L99 _private member_ `float LastDrawDataEndSize = 0.0f;` — Save off the last expected draw size so that we can draw a border around it next frame (and hope we're the same size)
- L101 _private member_ `bool bShowGameplayTags = true;`
- L102 _private member_ `bool bShowGameplayAbilities = true;`
- L103 _private member_ `bool bShowGameplayEffects = true;`
- L104 _private member_ `bool bShowGameplayAttributes = true;`

#### enum `FGameplayDebuggerCategory_Abilities::ENetworkStatus`  
`enum class ENetworkStatus : uint8`  
_L35-38_
- desc: Some GAS features such as Attributes can exist on the server, client, or both.  We can also get 'detached' if both sides have the same values (such as Attributes) that aren't networked. We are reusing this same concept to try and reconcile Gameplay Effects predicted locally, or triggered server-side.
- L37 _public enumerator_ `ServerOnly`
- L37 _public enumerator_ `ServerOnly`
- L37 _public enumerator_ `ServerOnly`
- L37 _public enumerator_ `ServerOnly`
- L37 _public enumerator_ `ServerOnly`

#### struct `FGameplayDebuggerCategory_Abilities::FRepData`  
`struct FRepData`  
_L50-89_
- L52 _public member_ `FGameplayTagContainer OwnedTags;`
- L53 _public member_ `TArray<int32> TagCounts;`
- L62 _public member_ `TArray<FGameplayAbilityDebug> Abilities;`
- L77 _public member_ `TArray<FGameplayEffectDebug> GameplayEffects;`
- L86 _public member_ `TArray<FGameplayAttributeDebug> Attributes;`
- L88 _public prototype_ `void Serialize(FArchive& Ar);`

#### struct `FGameplayDebuggerCategory_Abilities::FRepData::FGameplayAbilityDebug`  
`struct FGameplayAbilityDebug`  
_L55-61_
- L57 _public member_ `FString Ability;`
- L58 _public member_ `FString Source;`
- L59 _public member_ `int32 Level = 0;`
- L60 _public member_ `bool bIsActive = false;`

#### struct `FGameplayDebuggerCategory_Abilities::FRepData::FGameplayEffectDebug`  
`struct FGameplayEffectDebug`  
_L64-76_
- L66 _public member_ `int32 ReplicationID = INDEX_NONE;` — unique & shared between server/client (or INDEX_NONE if local)
- L67 _public member_ `FString Effect;`
- L68 _public member_ `FString Context;`
- L69 _public member_ `float Duration = 0.0f;`
- L70 _public member_ `float Period = 0.0f;`
- L71 _public member_ `int32 Stacks = 0;`
- L72 _public member_ `float Level = 0.0f;`
- L74 _public member_ `ENetworkStatus NetworkStatus = ENetworkStatus::ServerOnly;`
- L75 _public member_ `bool bInhibited = false;`

#### struct `FGameplayDebuggerCategory_Abilities::FRepData::FGameplayAttributeDebug`  
`struct FGameplayAttributeDebug`  
_L79-85_
- L81 _public member_ `FString AttributeName;`
- L82 _public member_ `float BaseValue = 0.0f;`
- L83 _public member_ `float CurrentValue = 0.0f;`
- L84 _public member_ `ENetworkStatus NetworkStatus = ENetworkStatus::ServerOnly;`

#### Free symbols / members of external scopes

- L41 _function_ `friend constexpr int32 operator+(const ENetworkStatus& value)` — Unary operator + for quick conversion from enum class to int32

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffect.h` (Public)


#### enum `EGameplayEffectMagnitudeCalculation`  
`enum class EGameplayEffectMagnitudeCalculation : uint8`  
_L67-77_
- reflection: `UENUM()`
- desc: Enumeration outlining the possible gameplay effect magnitude calculation policies.
- L70 _public enumerator_ `ScalableFloat` — Use a simple, scalable float for the calculation.
- L72 _public enumerator_ `AttributeBased` — Perform a calculation based upon an attribute.
- L74 _public enumerator_ `CustomCalculationClass` — Perform a custom calculation, capable of capturing and acting on multiple attributes, in either BP or native.
- L76 _public enumerator_ `SetByCaller` — This magnitude will be set explicitly by the code/blueprint that creates the spec.

#### enum `EAttributeBasedFloatCalculationType`  
`enum class EAttributeBasedFloatCalculationType : uint8`  
_L81-91_
- reflection: `UENUM()`
- desc: Enumeration outlining the possible attribute based float calculation policies.
- L84 _public enumerator_ `AttributeMagnitude` — Use the final evaluated magnitude of the attribute.
- L86 _public enumerator_ `AttributeBaseValue` — Use the base value of the attribute.
- L88 _public enumerator_ `AttributeBonusMagnitude` — Use the "bonus" evaluated magnitude of the attribute: Equivalent to (FinalMag - BaseValue).
- L90 _public enumerator_ `AttributeMagnitudeEvaluatedUpToChannel` — Use a calculated magnitude stopping with the evaluation of the specified "Final Channel"

#### enum `EGameplayEffectVersion`  
`enum class EGameplayEffectVersion : uint8`  
_L95-102_
- reflection: `UENUM()`
- desc: The version of the UGameplayEffect. Used for upgrade paths.
- L97 _public enumerator_ `Monolithic` — Legacy version from Pre-UE5.3 (before we were versioning)
- L98 _public enumerator_ `Modular53` — New modular version available in UE5.3
- L99 _public enumerator_ `AbilitiesComponent53` — Granted Abilities are moved into the Abilities Component
- L101 _public enumerator_ `Current = AbilitiesComponent53`

#### struct `FGameplayEffectConstants`  
`struct FGameplayEffectConstants`  
_L104-117_
- L107 _public member_ `static const float INFINITE_DURATION;` — Infinite duration
- L110 _public member_ `static const float INSTANT_APPLICATION;` — No duration; Time specifying instant application of an effect
- L113 _public member_ `static const float NO_PERIOD;` — Constant specifying that the combat effect has no period and doesn't check for over time application
- L116 _public member_ `static const float INVALID_LEVEL;` — No Level/Level not set

#### struct `FAttributeBasedFloat`  
`struct FAttributeBasedFloat`  
_L124-195_
- reflection: `USTRUCT()`
- desc: Struct representing a float whose magnitude is dictated by a backing attribute and a calculation policy, follows basic form of: (Coefficient * (PreMultiplyAdditiveValue + [Eval'd Attribute Value According to Policy])) + PostMultiplyAdditiveValue
- L131 _public function_ `FAttributeBasedFloat() : Coefficient(1.f) , PreMultiplyAdditiveValue(0.f) , PostMultiplyAdditiveValue(0.f) , BackingAttribute() , AttributeCalculationType(EAttributeBasedFloatCalculationType::AttributeMagnitude) , FinalChannel(EGameplayModEvaluationChannel::Channel0)` — Constructor
- L150 _public prototype_ `float CalculateMagnitude(const FGameplayEffectSpec& InRelevantSpec) const;` — Calculate and return the magnitude of the float given the specified gameplay effect spec. @note:	This function assumes (and asserts on) the existence of the required captured attribute within the spec. It is the responsibility of the caller to verify that the spec is properly setup before calling this function. @param InRelevantSpec	Gameplay effect spec providing the backing attribute capture @return Evaluated magnitude based upon the spec & calculation policy
- L154 _public member_ `FScalableFloat Coefficient;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Coefficient to the attribute calculation
- L158 _public member_ `FScalableFloat PreMultiplyAdditiveValue;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Additive value to the attribute calculation, added in before the coefficient applies
- L162 _public member_ `FScalableFloat PostMultiplyAdditiveValue;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Additive value to the attribute calculation, added in after the coefficient applies
- L166 _public member_ `FGameplayEffectAttributeCaptureDefinition BackingAttribute;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Attribute backing the calculation
- L170 _public member_ `FCurveTableRowHandle AttributeCurve;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — If a curve table entry is specified, the attribute will be used as a lookup into the curve instead of using the attribute directly.
- L174 _public member_ `EAttributeBasedFloatCalculationType AttributeCalculationType;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Calculation policy in regards to the attribute
- L178 _public member_ `EGameplayModEvaluationChannel FinalChannel;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Channel to terminate evaluation on when using AttributeEvaluatedUpToChannel calculation type
- L182 _public member_ `FGameplayTagContainer SourceTagFilter;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Filter to use on source tags; If specified, only modifiers applied with all of these tags will factor into the calculation
- L186 _public member_ `FGameplayTagContainer TargetTagFilter;` — `UPROPERTY(EditDefaultsOnly, Category=AttributeFloat)` — Filter to use on target tags; If specified, only modifiers applied with all of these tags will factor into the calculation
- L189 _public prototype_ `bool operator==(const FAttributeBasedFloat& Other) const;` — Equality/Inequality operators
- L190 _public prototype_ `bool operator!=(const FAttributeBasedFloat& Other) const;`
- L193 _public prototype_ `EDataValidationResult IsDataValid(class FDataValidationContext& Context, const FString& PathName) const;`

#### struct `FCustomCalculationBasedFloat`  
`struct FCustomCalculationBasedFloat`  
_L199-250_
- reflection: `USTRUCT()`
- desc: Structure to encapsulate magnitudes that are calculated via custom calculation
- L203 _public function_ `FCustomCalculationBasedFloat() : CalculationClassMagnitude(nullptr) , Coefficient(1.f) , PreMultiplyAdditiveValue(0.f) , PostMultiplyAdditiveValue(0.f)`
- L222 _public prototype_ `float CalculateMagnitude(const FGameplayEffectSpec& InRelevantSpec) const;` — Calculate and return the magnitude of the float given the specified gameplay effect spec. @note:	This function assumes (and asserts on) the existence of the required captured attribute within the spec. It is the responsibility of the caller to verify that the spec is properly setup before calling this function. @param InRelevantSpec	Gameplay effect spec providing the backing attribute capture @return Evaluated magnitude based upon the spec & calculation policy
- L225 _public member_ `TSubclassOf<UGameplayModMagnitudeCalculation> CalculationClassMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=CustomCalculation, DisplayName="Calculation Class")`
- L229 _public member_ `FScalableFloat Coefficient;` — `UPROPERTY(EditDefaultsOnly, Category=CustomCalculation)` — Coefficient to the custom calculation
- L233 _public member_ `FScalableFloat PreMultiplyAdditiveValue;` — `UPROPERTY(EditDefaultsOnly, Category=CustomCalculation)` — Additive value to the attribute calculation, added in before the coefficient applies
- L237 _public member_ `FScalableFloat PostMultiplyAdditiveValue;` — `UPROPERTY(EditDefaultsOnly, Category=CustomCalculation)` — Additive value to the attribute calculation, added in after the coefficient applies
- L241 _public member_ `FCurveTableRowHandle FinalLookupCurve;` — `UPROPERTY(EditDefaultsOnly, Category=CustomCalculation)` — If a curve table entry is specified, the OUTPUT of this custom class magnitude (including the pre and post additive values) lookup into the curve instead of using the attribute directly.
- L244 _public prototype_ `bool operator==(const FCustomCalculationBasedFloat& Other) const;` — Equality/Inequality operators
- L245 _public prototype_ `bool operator!=(const FCustomCalculationBasedFloat& Other) const;`
- L248 _public prototype_ `EDataValidationResult IsDataValid(class FDataValidationContext& Context, const FString& PathName) const;`

#### struct `FSetByCallerFloat`  
`struct FSetByCallerFloat`  
_L254-272_
- reflection: `USTRUCT()`
- desc: Struct for holding SetBytCaller data
- L258 _public function_ `FSetByCallerFloat() : DataName(NAME_None)`
- L264 _public member_ `FName DataName;` — `UPROPERTY(VisibleDefaultsOnly, Category=SetByCaller)` — The Name the caller (code or blueprint) will use to set this magnitude by.
- L267 _public member_ `FGameplayTag DataTag;` — `UPROPERTY(EditDefaultsOnly, Category = SetByCaller, meta = (Categories = "SetByCaller"))`
- L270 _public prototype_ `bool operator==(const FSetByCallerFloat& Other) const;` — Equality/Inequality operators
- L271 _public prototype_ `bool operator!=(const FSetByCallerFloat& Other) const;`

#### struct `FGameplayEffectModifierMagnitude`  
`struct FGameplayEffectModifierMagnitude`  
_L276-393_
- reflection: `USTRUCT()`
- desc: Struct representing the magnitude of a gameplay effect modifier, potentially calculated in numerous different ways
- L283 _public function_ `FGameplayEffectModifierMagnitude() : MagnitudeCalculationType(EGameplayEffectMagnitudeCalculation::ScalableFloat)` — Default Constructor
- L289 _public function_ `FGameplayEffectModifierMagnitude(const FScalableFloat& Value) : MagnitudeCalculationType(EGameplayEffectMagnitudeCalculation::ScalableFloat) , ScalableFloatMagnitude(Value)` — Constructors for setting value in code (for automation tests)
- L294 _public function_ `FGameplayEffectModifierMagnitude(const FAttributeBasedFloat& Value) : MagnitudeCalculationType(EGameplayEffectMagnitudeCalculation::AttributeBased) , AttributeBasedMagnitude(Value)`
- L299 _public function_ `FGameplayEffectModifierMagnitude(const FCustomCalculationBasedFloat& Value) : MagnitudeCalculationType(EGameplayEffectMagnitudeCalculation::CustomCalculationClass) , CustomMagnitude(Value)`
- L304 _public function_ `FGameplayEffectModifierMagnitude(const FSetByCallerFloat& Value) : MagnitudeCalculationType(EGameplayEffectMagnitudeCalculation::SetByCaller) , SetByCallerMagnitude(Value)`
- L317 _public prototype_ `bool CanCalculateMagnitude(const FGameplayEffectSpec& InRelevantSpec) const;` — Determines if the magnitude can be properly calculated with the specified gameplay effect spec (could fail if relying on an attribute not present, etc.) @param InRelevantSpec	Gameplay effect spec to check for magnitude calculation @return Whether or not the magnitude can be properly calculated
- L328 _public prototype_ `bool AttemptCalculateMagnitude(const FGameplayEffectSpec& InRelevantSpec, OUT float& OutCalculatedMagnitude, bool WarnIfSetByCallerFail=true, float DefaultSetbyCaller=0.f) const;` — Attempts to calculate the magnitude given the provided spec. May fail if necessary information (such as captured attributes) is missing from the spec. @param InRelevantSpec			Gameplay effect spec to use to calculate the magnitude with @param OutCalculatedMagnitude	[OUT] Calculated value of the magnitude, will be set to 0.f in the event of failure @return True if the calculation was successful, false if it was not
- L331 _public prototype_ `bool AttemptRecalculateMagnitudeFromDependentAggregatorChange(const FGameplayEffectSpec& InRelevantSpec, OUT float& OutCalculatedMagnitude, const FAggregator* ChangedAggregator) const;` — Attempts to recalculate the magnitude given a changed aggregator. This will only recalculate if we are a modifier that is linked (non snapshot) to the given aggregator.
- L338 _public prototype_ `void GetAttributeCaptureDefinitions(OUT TArray<FGameplayEffectAttributeCaptureDefinition>& OutCaptureDefs) const;` — Gather all of the attribute capture definitions necessary to compute the magnitude and place them into the provided array @param OutCaptureDefs	[OUT] Array populated with necessary attribute capture definitions
- L340 _public function_ `EGameplayEffectMagnitudeCalculation GetMagnitudeCalculationType() const`
- L343 _public prototype_ `bool GetStaticMagnitudeIfPossible(float InLevel, float& OutMagnitude, const FString* ContextString = nullptr) const;` — Returns the magnitude as it was entered in data. Only applies to ScalableFloat or any other type that can return data without context
- L346 _public prototype_ `bool GetSetByCallerDataNameIfPossible(FName& OutDataName) const;` — Returns the DataName associated with this magnitude if it is set by caller
- L349 _public function_ `const FSetByCallerFloat& GetSetByCallerFloat() const` — Returns SetByCaller data structure, for inspection purposes
- L352 _public prototype_ `TSubclassOf<UGameplayModMagnitudeCalculation> GetCustomMagnitudeCalculationClass() const;` — Returns the custom magnitude calculation class, if any, for this magnitude. Only applies to CustomMagnitudes
- L355 _public prototype_ `bool Serialize(FArchive& Ar);` — Implementing Serialize to clear references to assets that are not needed
- L357 _public prototype_ `bool operator==(const FGameplayEffectModifierMagnitude& Other) const;`
- L358 _public prototype_ `bool operator!=(const FGameplayEffectModifierMagnitude& Other) const;`
- L361 _public prototype_ `FText GetValueForEditorDisplay() const;`
- L362 _public prototype_ `EDataValidationResult IsDataValid(class FDataValidationContext& Context, const FString& PathName) const;`
- L365 _public prototype_ `void ReportErrors(const FString& PathName) const;` — `UE_DEPRECATED(5.6, "Use IsDataValid")`
- L372 _protected member_ `EGameplayEffectMagnitudeCalculation MagnitudeCalculationType;` — `UPROPERTY(EditDefaultsOnly, Category=Magnitude)` — Type of calculation to perform to derive the magnitude
- L376 _protected member_ `FScalableFloat ScalableFloatMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=Magnitude)` — Magnitude value represented by a scalable float
- L381 _protected member_ `FAttributeBasedFloat AttributeBasedMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=Magnitude)` — Magnitude value represented by an attribute-based float (Coefficient * (PreMultiplyAdditiveValue + [Eval'd Attribute Value According to Policy])) + PostMultiplyAdditiveValue
- L385 _protected member_ `FCustomCalculationBasedFloat CustomMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=Magnitude)` — Magnitude value represented by a custom calculation class
- L389 _protected member_ `FSetByCallerFloat SetByCallerMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=Magnitude)` — Magnitude value represented by a SetByCaller magnitude

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayEffectModifierMagnitude> : public TStructOpsTypeTraitsBase2<FGameplayEffectModifierMagnitude>`  
_L396-402_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayEffectModifierMagnitude>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L399-401_

#### enum `EGameplayEffectScopedModifierAggregatorType`  
`enum class EGameplayEffectScopedModifierAggregatorType : uint8`  
_L406-413_
- reflection: `UENUM()`
- desc: Enumeration representing the types of scoped modifier aggregator usages available
- L409 _public enumerator_ `CapturedAttributeBacked` — Aggregator is backed by an attribute capture
- L412 _public enumerator_ `Transient` — Aggregator is entirely transient (acting as a "temporary variable") and must be identified via gameplay tag

#### struct `FGameplayEffectExecutionScopedModifierInfo`  
`struct FGameplayEffectExecutionScopedModifierInfo`  
_L420-475_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct representing modifier info used exclusively for "scoped" executions that happen instantaneously. These are folded into a calculation only for the extent of the calculation and never permanently added to an aggregator.
- L425 _public function_ `FGameplayEffectExecutionScopedModifierInfo() : AggregatorType(EGameplayEffectScopedModifierAggregatorType::CapturedAttributeBacked) , ModifierOp(EGameplayModOp::Additive)` — Constructors
- L430 _public function_ `FGameplayEffectExecutionScopedModifierInfo(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef) : CapturedAttribute(InCaptureDef) , AggregatorType(EGameplayEffectScopedModifierAggregatorType::CapturedAttributeBacked) , ModifierOp(EGameplayModOp::Additive)`
- L437 _public function_ `FGameplayEffectExecutionScopedModifierInfo(const FGameplayTag& InTransientAggregatorIdentifier) : TransientAggregatorIdentifier(InTransientAggregatorIdentifier) , AggregatorType(EGameplayEffectScopedModifierAggregatorType::Transient) , ModifierOp(EGameplayModOp::Additive)`
- L446 _public member_ `FGameplayEffectAttributeCaptureDefinition CapturedAttribute;` — `UPROPERTY(VisibleDefaultsOnly, Category=Execution)` — Backing attribute that the scoped modifier is for
- L450 _public member_ `FGameplayTag TransientAggregatorIdentifier;` — `UPROPERTY(VisibleDefaultsOnly, Category=Execution)` — Identifier for aggregator if acting as a transient "temporary variable" aggregator
- L454 _public member_ `EGameplayEffectScopedModifierAggregatorType AggregatorType;` — `UPROPERTY(VisibleDefaultsOnly, Category=Execution)` — Type of aggregator backing the scoped mod
- L458 _public member_ `TEnumAsByte<EGameplayModOp::Type> ModifierOp;` — `UPROPERTY(EditDefaultsOnly, Category=Execution)` — Modifier operation to perform
- L462 _public member_ `FGameplayEffectModifierMagnitude ModifierMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=Execution)` — Magnitude of the scoped modifier
- L466 _public member_ `FGameplayModEvaluationChannelSettings EvaluationChannelSettings;` — `UPROPERTY(EditDefaultsOnly, Category=Execution)` — Evaluation channel settings of the scoped modifier
- L470 _public member_ `FGameplayTagRequirements SourceTags;` — `UPROPERTY(EditDefaultsOnly, Category=Execution)` — Source tag requirements for the modifier to apply
- L474 _public member_ `FGameplayTagRequirements TargetTags;` — `UPROPERTY(EditDefaultsOnly, Category=Execution)` — Target tag requirements for the modifier to apply

#### enum `EGameplayEffectGrantedEffectRemovalPolicy`  
`enum class EGameplayEffectGrantedEffectRemovalPolicy : uint8`  
_L480-488_
- reflection: `UENUM()`
- desc: Describes what happens to a Gameplay Effect that was applied on-application by another Gameplay Effect (via UAdditionalEffectsGameplayEffectComponent) when the applying effect is removed.
- L483 _public enumerator_ `GrantedEffectControlsOwnLifetime` — The applied Gameplay Effect manages its own lifetime independently. This is the default behavior.
- L487 _public enumerator_ `RemoveGrantedEffectOnEnd` — The applied Gameplay Effect will be removed when the Gameplay Effect that applied it is removed. Cannot be used when the granted effect has an Instant duration (instant GEs are never persisted).

#### struct `FConditionalGameplayEffect`  
`struct FConditionalGameplayEffect`  
_L494-522_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct for gameplay effects that apply only if another gameplay effect (or execution) was successfully applied.
- L498 _public prototype_ `bool CanApply(const FGameplayTagContainer& SourceTags, float SourceLevel) const;`
- L500 _public prototype_ `FGameplayEffectSpecHandle CreateSpec(FGameplayEffectContextHandle EffectContext, float SourceLevel) const;`
- L504 _public member_ `TSubclassOf<UGameplayEffect> EffectClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffect)` — gameplay effect that will be applied to the target
- L508 _public member_ `FGameplayTagContainer RequiredSourceTags;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffect)` — Tags that the source must have for this GE to apply.  If this is blank, then there are no requirements to apply the EffectClass.
- L513 _public member_ `EGameplayEffectGrantedEffectRemovalPolicy RemovalPolicy = EGameplayEffectGrantedEffectRemovalPolicy::GrantedEffectControlsOwnLifetime;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffect)` — What happens to this applied effect when the Gameplay Effect that applied it is removed. Only relevant when this entry is used in UAdditionalEffectsGameplayEffectComponent::OnApplicationGameplayEffects.
- L518 _public member_ `int32 StackCountToRemove = INDEX_NONE;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffect, meta = (EditCondition = "RemovalPolicy == EGameplayEffectGrantedEffectRemovalPolicy::RemoveGrantedEffectOnEnd", EditConditionHides))` — Number of stacks to remove when RemovalPolicy is RemoveGrantedEffectOnEnd. INDEX_NONE (default) removes all stacks.
- L520 _public prototype_ `bool operator==(const FConditionalGameplayEffect& Other) const;`
- L521 _public prototype_ `bool operator!=(const FConditionalGameplayEffect& Other) const;`

#### struct `FGameplayEffectExecutionDefinition`  
`struct FGameplayEffectExecutionDefinition`  
_L529-557_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct representing the definition of a custom execution for a gameplay effect. Custom executions run special logic from an outside class each time the gameplay effect executes.
- L540 _public prototype_ `void GetAttributeCaptureDefinitions(OUT TArray<FGameplayEffectAttributeCaptureDefinition>& OutCaptureDefs) const;` — Gathers and populates the specified array with the capture definitions that the execution would like in order to perform its custom calculation. Up to the individual execution calculation to handle if some of them are missing or not. @param OutCaptureDefs	[OUT] Capture definitions requested by the execution
- L544 _public member_ `TSubclassOf<UGameplayEffectExecutionCalculation> CalculationClass;` — `UPROPERTY(EditDefaultsOnly, Category=Execution)` — Custom execution calculation class to run when the gameplay effect executes
- L548 _public member_ `FGameplayTagContainer PassedInTags;` — `UPROPERTY(EditDefaultsOnly, Category = Execution)` — These tags are passed into the execution as is, and may be used to do conditional logic
- L552 _public member_ `TArray<FGameplayEffectExecutionScopedModifierInfo> CalculationModifiers;` — `UPROPERTY(EditDefaultsOnly, Category = Execution)` — Modifiers that are applied "in place" during the execution calculation
- L556 _public member_ `TArray<FConditionalGameplayEffect> ConditionalGameplayEffects;` — `UPROPERTY(EditDefaultsOnly, Category = Execution)` — Other Gameplay Effects that will be applied to the target of this execution if the execution is successful. Note if no execution class is selected, these will always apply.

#### struct `FGameplayModifierInfo`  
`struct FGameplayModifierInfo`  
_L565-598_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayModifierInfo Tells us "Who/What we" modify Does not tell us how exactly
- L571 _public member_ `FGameplayAttribute Attribute;` — `UPROPERTY(EditDefaultsOnly, Category=GameplayModifier, meta=(FilterMetaTag="HideFromModifiers"))` — The Attribute we modify or the GE we modify modifies.
- L579 _public member_ `TEnumAsByte<EGameplayModOp::Type> ModifierOp = EGameplayModOp::Additive;` — `UPROPERTY(EditDefaultsOnly, Category=GameplayModifier)` — The numeric operation of this modifier: Override, Add, Multiply, etc When multiple modifiers aggregate together, the equation is: ((BaseValue + AddBase) * MultiplyAdditive / DivideAdditive * MultiplyCompound) + AddFinal
- L583 _public member_ `FGameplayEffectModifierMagnitude ModifierMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=GameplayModifier)` — Magnitude of the modifier
- L587 _public member_ `FGameplayModEvaluationChannelSettings EvaluationChannelSettings;` — `UPROPERTY(EditDefaultsOnly, Category=GameplayModifier)` — Evaluation channel settings of the modifier
- L590 _public member_ `FGameplayTagRequirements SourceTags;` — `UPROPERTY(EditDefaultsOnly, Category=GameplayModifier)`
- L593 _public member_ `FGameplayTagRequirements TargetTags;` — `UPROPERTY(EditDefaultsOnly, Category=GameplayModifier)`
- L596 _public prototype_ `bool operator==(const FGameplayModifierInfo& Other) const;` — Equality/Inequality operators
- L597 _public prototype_ `bool operator!=(const FGameplayModifierInfo& Other) const;`

#### struct `FGameplayEffectCue`  
`struct FGameplayEffectCue`  
_L606-649_
- reflection: `USTRUCT(BlueprintType)`
- desc: FGameplayEffectCue This is a cosmetic cue that can be tied to a UGameplayEffect. This is essentially a GameplayTag + a Min/Max level range that is used to map the level of a GameplayEffect to a normalized value used by the GameplayCue system.
- L610 _public function_ `FGameplayEffectCue() : MinLevel(0.f) , MaxLevel(0.f)`
- L616 _public function_ `FGameplayEffectCue(const FGameplayTag& InTag, float InMinLevel, float InMaxLevel) : MinLevel(InMinLevel) , MaxLevel(InMaxLevel)`
- L625 _public member_ `FGameplayAttribute MagnitudeAttribute;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — The attribute to use as the source for cue magnitude. If none use level
- L629 _public member_ `float MinLevel;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — The minimum level that this Cue supports
- L633 _public member_ `float MaxLevel;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue)` — The maximum level that this Cue supports
- L637 _public member_ `FGameplayTagContainer GameplayCueTags;` — `UPROPERTY(EditDefaultsOnly, Category = GameplayCue, meta = (Categories="GameplayCue"))` — Tags passed to the gameplay cue handler when this cue is activated
- L639 _public function_ `float NormalizeLevel(float InLevel)`

#### struct `FInheritedTagContainer`  
`struct FInheritedTagContainer`  
_L653-682_
- reflection: `USTRUCT(BlueprintType)`
- desc: Structure that is used to combine tags from parent and child blueprints in a safe way
- L659 _public member_ `FGameplayTagContainer CombinedTags;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Application, meta=(Tooltip="CombinedTags = Inherited - Removed + Added"))` — Tags that I inherited and tags that I added minus tags that I removed
- L663 _public member_ `FGameplayTagContainer Added;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Application, meta=(DisplayName="Add to Inherited"))` — Tags that I have (in addition to my parent's tags)
- L667 _public member_ `FGameplayTagContainer Removed;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Application, meta=(DisplayName="Remove from Inherited"))` — Tags that should be removed (only if my parent had them).  Note: we cannot use this to remove a tag that exists on a target. It only modifies the result of CombinedTags.
- L669 _public prototype_ `void UpdateInheritedTagProperties(const FInheritedTagContainer* Parent);`
- L672 _public prototype_ `void ApplyTo(FGameplayTagContainer& ApplyToContainer) const;` — Apply the Added and Removed tags to the passed-in container (does not have to be the previously configured Parent!)
- L675 _public prototype_ `void AddTag(const FGameplayTag& TagToAdd);` — Add a tag that will appear in addition to any inherited tags
- L678 _public prototype_ `void RemoveTag(const FGameplayTag& TagToRemove);` — Remove a tag that will be omitted from any inherited tags
- L680 _public prototype_ `bool operator==(const FInheritedTagContainer& Other) const;`
- L681 _public prototype_ `bool operator!=(const FInheritedTagContainer& Other) const;`

#### enum `EGameplayEffectDurationType`  
`enum class EGameplayEffectDurationType : uint8`  
_L686-694_
- reflection: `UENUM()`
- desc: Gameplay effect duration policies
- L689 _public enumerator_ `Instant` — This effect applies instantly
- L691 _public enumerator_ `Infinite` — This effect lasts forever
- L693 _public enumerator_ `HasDuration` — The duration of this effect will be specified by a magnitude

#### enum `EGameplayEffectStackingDurationPolicy`  
`enum class EGameplayEffectStackingDurationPolicy : uint8`  
_L698-708_
- reflection: `UENUM()`
- desc: Enumeration of policies for dealing with duration of a gameplay effect while stacking
- L701 _public enumerator_ `RefreshOnSuccessfulApplication` — The duration of the effect will be refreshed from any successful stack application
- L704 _public enumerator_ `NeverRefresh` — The duration of the effect will never be refreshed
- L707 _public enumerator_ `ExtendDuration` — New stacks will add their GE spec's duration onto current remaining time

#### enum `EGameplayEffectStackingPeriodPolicy`  
`enum class EGameplayEffectStackingPeriodPolicy : uint8`  
_L712-719_
- reflection: `UENUM()`
- desc: Enumeration of policies for dealing with the period of a gameplay effect while stacking
- L715 _public enumerator_ `ResetOnSuccessfulApplication` — Any progress toward the next tick of a periodic effect is discarded upon any successful stack application
- L718 _public enumerator_ `NeverReset` — The progress toward the next tick of a periodic effect will never be reset, regardless of stack applications

#### enum `EGameplayEffectStackingExpirationPolicy`  
`enum class EGameplayEffectStackingExpirationPolicy : uint8`  
_L723-733_
- reflection: `UENUM()`
- desc: Enumeration of policies for dealing gameplay effect stacks that expire (in duration based effects).
- L726 _public enumerator_ `ClearEntireStack` — The entire stack is cleared when the active gameplay effect expires
- L729 _public enumerator_ `RemoveSingleStackAndRefreshDuration` — The current stack count will be decremented by 1 and the duration refreshed. The GE is not "reapplied", just continues to exist with one less stacks.
- L732 _public enumerator_ `RefreshDuration` — The duration of the gameplay effect is refreshed. This essentially makes the effect infinite in duration. This can be used to manually handle stack decrements via OnStackCountChange callback

#### enum `EGameplayEffectPeriodInhibitionRemovedPolicy`  
`enum class EGameplayEffectPeriodInhibitionRemovedPolicy : uint8`  
_L737-747_
- reflection: `UENUM()`
- desc: Enumeration of policies for dealing with the period of a gameplay effect when inhibition is removed
- L740 _public enumerator_ `NeverReset` — Does not reset. The period timing will continue as if the inhibition hadn't occurred.
- L743 _public enumerator_ `ResetPeriod` — Resets the period. The next execution will occur one full period from when inhibition is removed.
- L746 _public enumerator_ `ExecuteAndResetPeriod` — Executes immediately and resets the period.

#### struct `FModifierSpec`  
`struct FModifierSpec`  
_L751-768_
- reflection: `USTRUCT()`
- desc: Holds evaluated magnitude from a GameplayEffect modifier
- L755 _public function_ `FModifierSpec() : EvaluatedMagnitude(0.f)`
- L757 _public function_ `float GetEvaluatedMagnitude() const`
- L763 _private member_ `float EvaluatedMagnitude;` — `UPROPERTY()` — In the event that the modifier spec requires custom magnitude calculations, this is the authoritative, last evaluated value of the magnitude

#### struct `FGameplayEffectModifiedAttribute`  
`struct FGameplayEffectModifiedAttribute`  
_L772-785_
- reflection: `USTRUCT()`
- desc: Saves list of modified attributes, to use for gameplay cues or later processing
- L778 _public member_ `FGameplayAttribute Attribute;` — `UPROPERTY()` — The attribute that has been modified
- L782 _public member_ `float TotalMagnitude;` — `UPROPERTY()` — Total magnitude applied to that attribute
- L784 _public function_ `FGameplayEffectModifiedAttribute() : TotalMagnitude(0.0f)`

#### struct `FGameplayEffectAttributeCaptureSpec`  
`struct FGameplayEffectAttributeCaptureSpec`  
_L789-922_
- reflection: `USTRUCT()`
- desc: Struct used to hold the result of a gameplay attribute capture; Initially seeded by definition data, but then populated by ability system component when appropriate
- L798 _public prototype_ `FGameplayEffectAttributeCaptureSpec();` — Constructors
- L799 _public prototype_ `FGameplayEffectAttributeCaptureSpec(const FGameplayEffectAttributeCaptureDefinition& InDefinition);`
- L806 _public prototype_ `bool HasValidCapture() const;` — Returns whether the spec actually has a valid capture yet or not @return True if the spec has a valid attribute capture, false if it does not
- L817 _public prototype_ `bool AttemptCalculateAttributeMagnitude(const FAggregatorEvaluateParameters& InEvalParams, OUT float& OutMagnitude) const;` — Attempts to calculate the magnitude of the captured attribute given the specified parameters. Can fail if the spec doesn't have a valid capture yet. @param InEvalParams	Parameters to evaluate the attribute under @param OutMagnitude	[OUT] Computed magnitude @return True if the magnitude was successfully calculated, false if it was not
- L829 _public prototype_ `bool AttemptCalculateAttributeMagnitudeUpToChannel(const FAggregatorEvaluateParameters& InEvalParams, EGameplayModEvaluationChannel FinalChannel, OUT float& OutMagnitude) const;` — Attempts to calculate the magnitude of the captured attribute given the specified parameters, up to the specified evaluation channel (inclusive). Can fail if the spec doesn't have a valid capture yet. @param InEvalParams	Parameters to evaluate the attribute under @param FinalChannel	Evaluation channel to terminate the calculation at @param OutMagnitude	[OUT] Computed magnitude @return True if the magnitude was successfully calculated, false if it was not
- L841 _public prototype_ `bool AttemptCalculateAttributeMagnitudeWithBase(const FAggregatorEvaluateParameters& InEvalParams, float InBaseValue, OUT float& OutMagnitude) const;` — Attempts to calculate the magnitude of the captured attribute given the specified parameters, including a starting base value. Can fail if the spec doesn't have a valid capture yet. @param InEvalParams	Parameters to evaluate the attribute under @param InBaseValue	Base value to evaluate the attribute under @param OutMagnitude	[OUT] Computed magnitude @return True if the magnitude was successfully calculated, false if it was not
- L851 _public prototype_ `bool AttemptCalculateAttributeBaseValue(OUT float& OutBaseValue) const;` — Attempts to calculate the base value of the captured attribute given the specified parameters. Can fail if the spec doesn't have a valid capture yet. @param OutBaseValue	[OUT] Computed base value @return True if the base value was successfully calculated, false if it was not
- L862 _public prototype_ `bool AttemptCalculateAttributeBonusMagnitude(const FAggregatorEvaluateParameters& InEvalParams, OUT float& OutBonusMagnitude) const;` — Attempts to calculate the "bonus" magnitude (final - base value) of the captured attribute given the specified parameters. Can fail if the spec doesn't have a valid capture yet. @param InEvalParams		Parameters to evaluate the attribute under @param OutBonusMagnitude	[OUT] Computed bonus magnitude @return True if the bonus magnitude was successfully calculated, false if it was not
- L874 _public prototype_ `bool AttemptCalculateAttributeContributionMagnitude(const FAggregatorEvaluateParameters& InEvalParams, FActiveGameplayEffectHandle ActiveHandle, OUT float& OutBonusMagnitude) const;` — Attempts to calculate the contribution of the specified GE to the captured attribute given the specified parameters. Can fail if the spec doesn't have a valid capture yet. @param InEvalParams		Parameters to evaluate the attribute under @param ActiveHandle		Handle of the gameplay effect to query about @param OutBonusMagnitude	[OUT] Computed bonus magnitude @return True if the bonus magnitude was successfully calculated, false if it was not
- L884 _public prototype_ `bool AttemptGetAttributeAggregatorSnapshot(OUT FAggregator& OutAggregatorSnapshot) const;` — Attempts to populate the specified aggregator with a snapshot of the backing captured aggregator. Can fail if the spec doesn't have a valid capture yet. @param OutAggregatorSnapshot	[OUT] Snapshotted aggregator, if possible @return True if the aggregator was successfully snapshotted, false if it was not
- L894 _public prototype_ `bool AttemptAddAggregatorModsToAggregator(OUT FAggregator& OutAggregatorToAddTo) const;` — Attempts to populate the specified aggregator with all of the mods of the backing captured aggregator. Can fail if the spec doesn't have a valid capture yet. @param OutAggregatorToAddTo	[OUT] Aggregator with mods appended, if possible @return True if the aggregator had mods successfully added to it, false if it did not
- L897 _public prototype_ `bool AttemptGatherAttributeMods(const FAggregatorEvaluateParameters& InEvalParams, OUT TMap<EGameplayModEvaluationChannel, const TArray<FAggregatorMod>*>& OutModMap) const;` — Gathers made for a given capture. Note all mods are returned but only some will be qualified (use Qualified() func to determine)
- L900 _public prototype_ `const FGameplayEffectAttributeCaptureDefinition& GetBackingDefinition() const;` — Simple accessor to backing capture definition
- L903 _public prototype_ `void RegisterLinkedAggregatorCallback(FActiveGameplayEffectHandle Handle) const;` — Register this handle with linked aggregators
- L906 _public prototype_ `void UnregisterLinkedAggregatorCallback(FActiveGameplayEffectHandle Handle) const;` — Unregister this handle with linked aggregators
- L909 _public prototype_ `bool ShouldRefreshLinkedAggregator(const FAggregator* ChangedAggregator) const;` — Return true if this capture should be recalculated if the given aggregator has changed
- L912 _public prototype_ `void SwapAggregator(FAggregatorRef From, FAggregatorRef To);` — Swaps any internal references From aggregator To aggregator. Used when cloning
- L918 _private member_ `FGameplayEffectAttributeCaptureDefinition BackingDefinition;` — `UPROPERTY()` — Copy of the definition the spec should adhere to for capturing
- L921 _private member_ `FAggregatorRef AttributeAggregator;` — Ref to the aggregator for the captured attribute

#### struct `FGameplayEffectAttributeCaptureSpecContainer`  
`struct FGameplayEffectAttributeCaptureSpecContainer`  
_L926-1002_
- reflection: `USTRUCT()`
- desc: Struct used to handle a collection of captured source and target attributes
- L932 _public prototype_ `FGameplayEffectAttributeCaptureSpecContainer();`
- L934 _public prototype_ `FGameplayEffectAttributeCaptureSpecContainer(FGameplayEffectAttributeCaptureSpecContainer&& Other);`
- L936 _public prototype_ `FGameplayEffectAttributeCaptureSpecContainer(const FGameplayEffectAttributeCaptureSpecContainer& Other);`
- L938 _public prototype_ `FGameplayEffectAttributeCaptureSpecContainer& operator=(FGameplayEffectAttributeCaptureSpecContainer&& Other);`
- L940 _public prototype_ `FGameplayEffectAttributeCaptureSpecContainer& operator=(const FGameplayEffectAttributeCaptureSpecContainer& Other);`
- L948 _public prototype_ `void AddCaptureDefinition(const FGameplayEffectAttributeCaptureDefinition& InCaptureDefinition);` — Add a definition to be captured by the owner of the container. Will not add the definition if its exact match already exists within the container. @param InCaptureDefinition	Definition to capture with
- L956 _public prototype_ `void CaptureAttributes(class UAbilitySystemComponent* InAbilitySystemComponent, EGameplayEffectAttributeCaptureSource InCaptureSource);` — Capture source or target attributes from the specified component. Should be called by the container's owner. @param InAbilitySystemComponent	Component to capture attributes from @param InCaptureSource			Whether to capture attributes as source or target
- L966 _public prototype_ `const FGameplayEffectAttributeCaptureSpec* FindCaptureSpecByDefinition(const FGameplayEffectAttributeCaptureDefinition& InDefinition, bool bOnlyIncludeValidCapture) const;` — Find a capture spec within the container matching the specified capture definition, if possible. @param InDefinition				Capture definition to use as the search basis @param bOnlyIncludeValidCapture	If true, even if a spec is found, it won't be returned if it doesn't also have a valid capture already @return The found attribute spec matching the specified search params, if any
- L975 _public prototype_ `bool HasValidCapturedAttributes(const TArray<FGameplayEffectAttributeCaptureDefinition>& InCaptureDefsToCheck) const;` — Determines if the container has specs with valid captures for all of the specified definitions. @param InCaptureDefsToCheck	Capture definitions to check for @return True if the container has valid capture attributes for all of the specified definitions, false if it does not
- L978 _public prototype_ `bool HasNonSnapshottedAttributes() const;` — Returns whether the container has at least one spec w/o snapshotted attributes
- L981 _public prototype_ `void RegisterLinkedAggregatorCallbacks(FActiveGameplayEffectHandle Handle) const;` — Registers any linked aggregators to notify this active handle if they are dirtied
- L984 _public prototype_ `void UnregisterLinkedAggregatorCallbacks(FActiveGameplayEffectHandle Handle) const;` — Unregisters any linked aggregators from notifying this active handle if they are dirtied
- L987 _public prototype_ `void SwapAggregator(FAggregatorRef From, FAggregatorRef To);` — Swaps any internal references From aggregator To aggregator. Used when cloning
- L993 _private member_ `TArray<FGameplayEffectAttributeCaptureSpec> SourceAttributes;` — `UPROPERTY()` — Captured attributes from the source of a gameplay effect
- L997 _private member_ `TArray<FGameplayEffectAttributeCaptureSpec> TargetAttributes;` — `UPROPERTY()` — Captured attributes from the target of a gameplay effect
- L1001 _private member_ `bool bHasNonSnapshottedAttributes;` — `UPROPERTY()` — If true, has at least one capture spec that did not request a snapshot

#### struct `FGameplayEffectSpec`  
`struct FGameplayEffectSpec`  
_L1014-1291_
- reflection: `USTRUCT(BlueprintType)`
- desc: GameplayEffect Specification. Tells us: -What UGameplayEffect (const data) -What Level -Who instigated FGameplayEffectSpec is modifiable. We start with initial conditions and modifications be applied to it. In this sense, it is stateful/mutable but it is still distinct from an FActiveGameplayEffect which in an applied instance of an FGameplayEffectSpec.
- L1022 _public prototype_ `FGameplayEffectSpec();`
- L1024 _public prototype_ `FGameplayEffectSpec(const UGameplayEffect* InDef, const FGameplayEffectContextHandle& InEffectContext, float Level = FGameplayEffectConstants::INVALID_LEVEL);`
- L1026 _public prototype_ `FGameplayEffectSpec(const FGameplayEffectSpec& Other);`
- L1028 _public prototype_ `FGameplayEffectSpec(const FGameplayEffectSpec& Other, const FGameplayEffectContextHandle& InEffectContext);` — For cloning, copy all attributes, but set a new effectContext.
- L1030 _public prototype_ `FGameplayEffectSpec(FGameplayEffectSpec&& Other);`
- L1032 _public prototype_ `FGameplayEffectSpec& operator=(FGameplayEffectSpec&& Other);`
- L1034 _public prototype_ `FGameplayEffectSpec& operator=(const FGameplayEffectSpec& Other);`
- L1037 _public prototype_ `void Initialize(const UGameplayEffect* InDef, const FGameplayEffectContextHandle& InEffectContext, float Level = FGameplayEffectConstants::INVALID_LEVEL);` — Can be called manually but it is preferred to use the 3 parameter constructor
- L1040 _public prototype_ `void InitializeFromLinkedSpec(const UGameplayEffect* InDef, const FGameplayEffectSpec& OriginalSpec);` — Initialize the spec as a linked spec. The original spec's context is preserved except for the original GE asset tags, which are stripped out
- L1043 _public prototype_ `void CopySetByCallerMagnitudes(const FGameplayEffectSpec& OriginalSpec);` — Copies SetbyCallerMagnitudes from OriginalSpec into this
- L1046 _public prototype_ `void MergeSetByCallerMagnitudes(const TMap<FGameplayTag, float>& Magnitudes);` — Copies SetbuCallerMagnitudes, but only if magnitudes don't exist in our map (slower but preserves data)
- L1055 _public prototype_ `bool HasValidCapturedAttributes(const TArray<FGameplayEffectAttributeCaptureDefinition>& InCaptureDefsToCheck) const;` — Determines if the spec has capture specs with valid captures for all of the specified definitions. @param InCaptureDefsToCheck	Capture definitions to check for @return True if the container has valid capture attributes for all of the specified definitions, false if it does not
- L1058 _public prototype_ `const FGameplayEffectModifiedAttribute* GetModifiedAttribute(const FGameplayAttribute& Attribute) const;` — Looks for an existing modified attribute struct, may return NULL
- L1059 _public prototype_ `FGameplayEffectModifiedAttribute* GetModifiedAttribute(const FGameplayAttribute& Attribute);`
- L1062 _public prototype_ `FGameplayEffectModifiedAttribute* AddModifiedAttribute(const FGameplayAttribute& Attribute);` — Adds a new modified attribute struct, will always add so check to see if it exists first
- L1071 _public prototype_ `bool AttemptCalculateDurationFromDef(OUT float& OutDefDuration) const;` — Helper function to attempt to calculate the duration of the spec from its GE definition @param OutDefDuration	Computed duration of the spec from its GE definition; Not the actual duration of the spec @return True if the calculation was successful, false if it was not
- L1080 _public prototype_ `bool AttemptCalculateMaxDurationFromDef(OUT float& OutDefMaxDuration) const;` — Helper function to attempt to calculate the maximum duration of the spec from its GE definition @param OutDefMaxDuration	Computed max duration of the spec from its GE definition @return True if the calculation was successful, false if it was not
- L1083 _public prototype_ `void SetDuration(float NewDuration, bool bLockDuration);` — Sets duration. This should only be called as the GameplayEffect is being created and applied; Ignores calls after attribute capture
- L1085 _public prototype_ `float GetDuration() const;`
- L1088 _public prototype_ `float GetPeriod() const;` — Returns the Period for the effect. If DurationPolicy is Instant this will forcibly return NO_PERIOD
- L1091 _public prototype_ `void SetStackCount(int32 NewStackCount);` — Sets the stack count for this GE to NewStackCount if stacking is supported.
- L1094 _public prototype_ `int32 GetStackCount() const;` — Returns the stack count for this GE spec.
- L1097 _public prototype_ `void SetContext(FGameplayEffectContextHandle NewEffectContext, bool bSkipRecaptureSourceActorTags = false);` — Set the context info: who and where this spec came from.
- L1099 _public function_ `FGameplayEffectContextHandle GetContext() const`
- L1105 _public prototype_ `void GetAllGrantedTags(OUT FGameplayTagContainer& OutContainer) const;` — Appends all tags granted by this gameplay effect spec
- L1108 _public prototype_ `void GetAllBlockedAbilityTags(OUT FGameplayTagContainer& OutContainer) const;` — Appends all blocked ability tags granted by this gameplay effect spec
- L1111 _public prototype_ `void GetAllAssetTags(OUT FGameplayTagContainer& OutContainer) const;` — Appends all tags that apply to this gameplay effect spec
- L1114 _public prototype_ `void SetSetByCallerMagnitude(FName DataName, float Magnitude);` — Sets the magnitude of a SetByCaller modifier
- L1117 _public prototype_ `void SetSetByCallerMagnitude(FGameplayTag DataTag, float Magnitude);` — Sets the magnitude of a SetByCaller modifier
- L1120 _public prototype_ `float GetSetByCallerMagnitude(FName DataName, bool WarnIfNotFound = true, float DefaultIfNotFound = 0.f) const;` — Returns the magnitude of a SetByCaller modifier. Will return 0.f and Warn if the magnitude has not been set.
- L1123 _public prototype_ `float GetSetByCallerMagnitude(FGameplayTag DataTag, bool WarnIfNotFound = true, float DefaultIfNotFound = 0.f) const;` — Returns the magnitude of a SetByCaller modifier. Will return 0.f and Warn if the magnitude has not been set.
- L1125 _public prototype_ `void SetLevel(float InLevel);`
- L1127 _public prototype_ `float GetLevel() const;`
- L1129 _public prototype_ `void PrintAll() const;`
- L1131 _public prototype_ `FString ToSimpleString() const;`
- L1133 _public function_ `const FGameplayEffectContextHandle& GetEffectContext() const`
- L1138 _public function_ `void DuplicateEffectContext()`
- L1143 _public prototype_ `void CaptureAttributeDataFromTarget(UAbilitySystemComponent* TargetAbilitySystemComponent);`
- L1154 _public prototype_ `float GetModifierMagnitude(int32 ModifierIdx, bool bFactorInStackCount) const;` — `UE_DEPRECATED(5.6, "Versions using bFactorInStackCount are deprecated, please use GetModifierMagnitude(int32 ModifierIdx) instead.")` — Get the computed magnitude of the modifier on the spec with the specified index @param ModifierIdx			Modifier to get @param bFactorInStackCount	If true, the calculation will include the stack count @return Computed magnitude
- L1163 _public prototype_ `float GetModifierMagnitude(int32 ModifierIdx) const;` — Get the computed magnitude of the modifier on the spec with the specified index @param ModifierIdx			Modifier to get @return Computed magnitude
- L1166 _public prototype_ `void CalculateModifierMagnitudes();` — Fills out the modifier magnitudes inside the Modifier Specs
- L1169 _public prototype_ `void RecaptureAttributeDataForClone(UAbilitySystemComponent* OriginalASC, UAbilitySystemComponent* NewASC);` — Recapture attributes from source and target for cloning
- L1172 _public prototype_ `void RecaptureSourceActorTags();` — Recaptures source actor tags of this spec without modifying anything else
- L1175 _public prototype_ `void SetupAttributeCaptureDefinitions();` — Helper function to initialize all of the capture definitions required by the spec
- L1178 _public prototype_ `float CalculateModifiedDuration() const;` — Helper function that returns the duration after applying relevant modifiers from the source and target ability system components
- L1181 _public prototype_ `void AddDynamicAssetTag(const FGameplayTag& TagToAdd);` — Dynamically add an asset tag not originally from the source GE definition; Added to DynamicAssetTags as well as injected into the captured source spec tags
- L1184 _public prototype_ `void AppendDynamicAssetTags(const FGameplayTagContainer& TagsToAppend);` — Dynamically append asset tags not originally from the source GE definition; Added to DynamicAssetTags as well as injected into the captured source spec tags
- L1187 _public prototype_ `const FGameplayTagContainer& GetDynamicAssetTags() const;` — Simple const accessor to the dynamic asset tags
- L1190 _public prototype_ `FVisualLogStatusCategory GrabVisLogStatus() const;`
- L1195 _private prototype_ `void CaptureDataFromSource(bool bSkipRecaptureSourceActorTags = false);`
- L1198 _private prototype_ `bool AttemptCalculateDurationRelatedMagnitude(const FGameplayEffectModifierMagnitude& MagnitudeDef, OUT float& OutDurationValue) const;` — Attempts to calculate a duration-related magnitude. Helper function to allow reuse between Duration and MaxDuration.
- L1204 _public member_ `TObjectPtr<const UGameplayEffect> Def;` — `UPROPERTY()` — GameplayEfect definition. The static data that this spec points to.
- L1208 _public member_ `TArray<FGameplayEffectModifiedAttribute> ModifiedAttributes;` — `UPROPERTY()` — A list of attributes that were modified during the application of this spec
- L1212 _public member_ `FGameplayEffectAttributeCaptureSpecContainer CapturedRelevantAttributes;` — `UPROPERTY(NotReplicated)` — Attributes captured by the spec that are relevant to custom calculations, potentially in owned modifiers, etc.; NOT replicated to clients
- L1216 _public member_ `TArray< FGameplayEffectSpecHandle > TargetEffectSpecs;` — `UE_DEPRECATED(5.3, "These TargetEffectSpecs are not replicated, thus can only apply to the server. Use UAdditionalGameplayEffectComponent instead (or roll your own solution)")` — other effects that need to be applied to the target if this effect is successful
- L1224 _public member_ `float Duration;` — `UPROPERTY()` — The duration in seconds of this effect instantaneous effects should have a duration of FGameplayEffectConstants::INSTANT_APPLICATION effects that last forever should have a duration of FGameplayEffectConstants::INFINITE_DURATION
- L1228 _public member_ `float Period;` — `UPROPERTY()` — The period in seconds of this effect, nonperiodic effects should have a period of FGameplayEffectConstants::NO_PERIOD
- L1232 _public member_ `FTagContainerAggregator CapturedSourceTags;` — `UPROPERTY(NotReplicated)` — Captured Source Tags on GameplayEffectSpec creation
- L1236 _public member_ `FTagContainerAggregator CapturedTargetTags;` — `UPROPERTY(NotReplicated)` — Tags from the target, captured during execute
- L1240 _public member_ `FGameplayTagContainer DynamicGrantedTags;` — `UPROPERTY()` — Tags that are granted and that did not come from the UGameplayEffect def. These are replicated.
- L1248 _private member_ `FGameplayTagContainer DynamicAssetTags;` — `UPROPERTY()` — Tags that are on this effect spec and that did not come from the UGameplayEffect def. These are replicated. To access use AddDynamicAssetTag, AppendDynamicAssetTags, or GetDynamicAssetTags as appropriate, removal is no longer supported
- L1253 _public member_ `TArray<FModifierSpec> Modifiers;` — `UPROPERTY()` — The calculated modifiers for this effect
- L1258 _private member_ `int32 StackCount;` — `UPROPERTY()` — Total number of stacks of this effect. Use GetStackCount and SetStackCount to access.
- L1263 _public member_ `uint32 bCompletedSourceAttributeCapture : 1;` — `UPROPERTY(NotReplicated)` — Whether the spec has had its source attribute capture completed or not yet
- L1267 _public member_ `uint32 bCompletedTargetAttributeCapture : 1;` — `UPROPERTY(NotReplicated)` — Whether the spec has had its target attribute capture completed or not yet
- L1271 _public member_ `uint32 bDurationLocked : 1;` — `UPROPERTY(NotReplicated)` — Whether the duration of the spec is locked or not; If it is, attempts to set it will fail
- L1276 _public member_ `TArray<FGameplayAbilitySpecDef> GrantedAbilitySpecs;` — `UE_DEPRECATED(5.3, "This variable will be removed in favor of (immutable) GASpecs that live on GameplayEffectComponents (e.g. AbilitiesGameplayEffectComponent)")` — `UPROPERTY()` — List of abilities granted by this effect
- L1279 _public member_ `TMap<FName, float> SetByCallerNameMagnitudes;` — Map of set by caller magnitudes
- L1280 _public member_ `TMap<FGameplayTag, float> SetByCallerTagMagnitudes;`
- L1286 _private member_ `FGameplayEffectContextHandle EffectContext;` — `UPROPERTY()` — This tells us how we got here (who / what applied us)
- L1290 _private member_ `float Level;` — `UPROPERTY()` — The level this effect was applied at

#### struct `FGameplayEffectSpecForRPC`  
`struct FGameplayEffectSpecForRPC`  
_L1296-1344_
- reflection: `USTRUCT()`
- desc: This is a cut down version of the gameplay effect spec used for RPCs.
- L1300 _public prototype_ `FGameplayEffectSpecForRPC();`
- L1302 _public prototype_ `FGameplayEffectSpecForRPC(const FGameplayEffectSpec& InSpec);`
- L1306 _public member_ `TObjectPtr<const UGameplayEffect> Def;` — `UPROPERTY()` — GameplayEfect definition. The static data that this spec points to.
- L1309 _public member_ `TArray<FGameplayEffectModifiedAttribute> ModifiedAttributes;` — `UPROPERTY()`
- L1312 _public member_ `FGameplayEffectContextHandle EffectContext;` — `UPROPERTY()`
- L1315 _public member_ `FGameplayTagContainer AggregatedSourceTags;` — `UPROPERTY()`
- L1318 _public member_ `FGameplayTagContainer AggregatedTargetTags;` — `UPROPERTY()`
- L1321 _public member_ `float Level;` — `UPROPERTY()`
- L1324 _public member_ `float AbilityLevel;` — `UPROPERTY()`
- L1326 _public function_ `FGameplayEffectContextHandle GetContext() const`
- L1331 _public function_ `float GetLevel() const`
- L1336 _public function_ `float GetAbilityLevel() const`
- L1341 _public prototype_ `FString ToSimpleString() const;`
- L1343 _public prototype_ `const FGameplayEffectModifiedAttribute* GetModifiedAttribute(const FGameplayAttribute& Attribute) const;`

#### struct `FActiveGameplayEffect`  
`struct FActiveGameplayEffect : public FFastArraySerializerItem`  
_L1355-1464_
- reflection: `USTRUCT(BlueprintType)`
- inherits: `FFastArraySerializerItem`
- desc: Active GameplayEffect instance -What GameplayEffect Spec -Start time -When to execute next -Replication callbacks
- L1363 _public prototype_ `FActiveGameplayEffect() = default;`
- L1364 _public prototype_ `FActiveGameplayEffect(FActiveGameplayEffectHandle InHandle, const FGameplayEffectSpec& InSpec, float CurrentWorldTime, float InStartServerWorldTime, FPredictionKey InPredictionKey);`
- L1367 _public prototype_ `FActiveGameplayEffect(const FActiveGameplayEffect& Other);` — These need to be defined because we need to omit PendingNext from move operations and the base class isn't trivially copyable
- L1368 _public prototype_ `FActiveGameplayEffect(FActiveGameplayEffect&& Other);`
- L1369 _public prototype_ `FActiveGameplayEffect& operator=(FActiveGameplayEffect&& other);`
- L1370 _public prototype_ `FActiveGameplayEffect& operator=(const FActiveGameplayEffect& other);`
- L1372 _public function_ `float GetTimeRemaining(float WorldTime) const`
- L1378 _public function_ `float GetDuration() const`
- L1383 _public function_ `float GetPeriod() const`
- L1388 _public function_ `float GetEndTime() const`
- L1394 _public prototype_ `void PrintAll() const;`
- L1396 _public prototype_ `void PreReplicatedRemove(const struct FActiveGameplayEffectsContainer &InArray);`
- L1397 _public prototype_ `void PostReplicatedAdd(const struct FActiveGameplayEffectsContainer &InArray);`
- L1398 _public prototype_ `void PostReplicatedChange(const struct FActiveGameplayEffectsContainer &InArray);`
- L1401 _public prototype_ `FString GetDebugString();` — Debug string used by Fast Array serialization
- L1404 _public prototype_ `void RecomputeStartWorldTime(const FActiveGameplayEffectsContainer& InArray);` — Refreshes the cached StartWorldTime for this effect. To be used when the server/client world time delta changes significantly to keep the start time in sync.
- L1407 _public prototype_ `void RecomputeStartWorldTime(const float WorldTime, const float ServerWorldTime);` — Refreshes the cached StartWorldTime for this effect. To be used when the server/client world time delta changes significantly to keep the start time in sync.
- L1409 _public function_ `bool operator==(const FActiveGameplayEffect& Other)`
- L1417 _public member_ `FActiveGameplayEffectHandle Handle;` — Globally unique ID for identify this active gameplay effect. Can be used to look up owner. Not networked.
- L1420 _public member_ `FGameplayEffectSpec Spec;` — `UPROPERTY()`
- L1423 _public member_ `FPredictionKey PredictionKey;` — `UPROPERTY()`
- L1427 _public member_ `TArray<FGameplayAbilitySpecHandle> GrantedAbilityHandles;` — `UPROPERTY()` — Handles of Gameplay Abilities that were granted to the target by this Active Gameplay Effect
- L1431 _public member_ `float StartServerWorldTime = 0.0f;` — `UPROPERTY()` — Server time this started
- L1435 _public member_ `float CachedStartServerWorldTime = 0.0f;` — `UPROPERTY(NotReplicated)` — Used for handling duration modifications being replicated
- L1438 _public member_ `float StartWorldTime = 0.0f;` — `UPROPERTY(NotReplicated)`
- L1442 _public member_ `bool bIsInhibited = true;` — `UPROPERTY(NotReplicated)` — Not sure if this should replicate or not. If replicated, we may have trouble where IsInhibited doesn't appear to change when we do tag checks (because it was previously inhibited, but replication made it inhibited).
- L1445 _public member_ `mutable bool bPendingRepOnActiveGC = false;` — When replicated down, we cue the GC events until the entire list of active gameplay effects has been received
- L1446 _public member_ `mutable bool bPendingRepWhileActiveGC = false;`
- L1448 _public member_ `bool IsPendingRemove = false;`
- L1451 _public member_ `int32 ClientCachedStackCount = 0;` — Last StackCount that the client had. Used to tell if the stackcount has changed in PostReplicatedChange
- L1453 _public member_ `FTimerHandle PeriodHandle;`
- L1454 _public member_ `FTimerHandle DurationHandle;`
- L1457 _public member_ `FActiveGameplayEffect* PendingNext = nullptr;` — Cached pointer.  Since these ActiveGE's can be reused in-place, this should *not* be copied during copy/move operations
- L1460 _public member_ `FActiveGameplayEffectEvents EventSet;` — All the bindable events for this active effect (bundled to allow easier non-const access to these events via the ASC)
- L1463 _public member_ `bool bPostPredictObject = false;` — Signifies an active effect that was predicted and has now been replicated back to the client

#### struct `FGameplayEffectQuery`  
`struct FGameplayEffectQuery`  
_L1471-1558_
- reflection: `USTRUCT(BlueprintType)`
- desc: Every set condition within this query must match in order for the query to match. i.e. individual query elements are ANDed together.
- L1477 _public prototype_ `FGameplayEffectQuery();` — ctors and operators
- L1478 _public prototype_ `FGameplayEffectQuery(const FGameplayEffectQuery& Other);`
- L1479 _public prototype_ `FGameplayEffectQuery(FActiveGameplayEffectQueryCustomMatch InCustomMatchDelegate);`
- L1480 _public prototype_ `FGameplayEffectQuery(FGameplayEffectQuery&& Other);`
- L1481 _public prototype_ `FGameplayEffectQuery& operator=(FGameplayEffectQuery&& Other);`
- L1482 _public prototype_ `FGameplayEffectQuery& operator=(const FGameplayEffectQuery& Other);`
- L1485 _public member_ `FActiveGameplayEffectQueryCustomMatch CustomMatchDelegate;` — Native delegate for providing custom matching conditions.
- L1489 _public member_ `FActiveGameplayEffectQueryCustomMatch_Dynamic CustomMatchDelegate_BP;` — `UPROPERTY(BlueprintReadWrite, Category = Query)` — BP-exposed delegate for providing custom matching conditions.
- L1493 _public member_ `FGameplayTagQuery OwningTagQuery;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Query)` — Query that is matched against tags this GE gives
- L1497 _public member_ `FGameplayTagQuery EffectTagQuery;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Query)` — Query that is matched against tags this GE has
- L1501 _public member_ `FGameplayTagQuery SourceTagQuery;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Query, DisplayName = SourceSpecTagQuery)` — Query that is matched against spec tags the source of this GE has
- L1505 _public member_ `FGameplayTagQuery SourceAggregateTagQuery;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Query)` — Query that is matched against all tags the source of this GE has
- L1509 _public member_ `FGameplayAttribute ModifyingAttribute;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Query)` — Matches on GameplayEffects which modify given attribute.
- L1513 _public member_ `TObjectPtr<const UObject> EffectSource;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Query)` — Matches on GameplayEffects which come from this source
- L1517 _public member_ `TSubclassOf<UGameplayEffect> EffectDefinition;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Query)` — Matches on GameplayEffects with this definition
- L1520 _public member_ `TArray<FActiveGameplayEffectHandle> IgnoreHandles;` — Handles to ignore as matches, even if other criteria is met
- L1523 _public prototype_ `bool Matches(const FActiveGameplayEffect& Effect) const;` — Returns true if Effect matches all specified criteria of this query, including CustomMatch delegates if bound. Returns false otherwise.
- L1528 _public prototype_ `bool Matches(const FGameplayEffectSpec& Effect) const;` — Returns true if Effect matches all specified criteria of this query. This does NOT check FActiveGameplayEffectQueryCustomMatch since this is performed on the spec (possibly prior to applying). Note: it would be reasonable to support a custom delegate that operated on the FGameplayEffectSpec itself.
- L1531 _public prototype_ `bool IsEmpty() const;` — Returns true if the query is empty/default. E.g., it has no data set.
- L1536 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchAnyOwningTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if there are any common tags between the given tags and an ActiveGameplayEffect's owning tags
- L1538 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchAllOwningTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if all of the given tags are in the ActiveGameplayEffect's owning tags
- L1540 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchNoOwningTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if there are no common tags between the given tags and an ActiveGameplayEffect's owning tags
- L1543 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchAnyEffectTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if there are any common tags between the given tags and an ActiveGameplayEffect's tags
- L1545 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchAllEffectTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if all of the given tags are in the ActiveGameplayEffect's tags
- L1547 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchNoEffectTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if there are no common tags between the given tags and an ActiveGameplayEffect's tags
- L1550 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchAnySourceSpecTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if there are any common tags between the given tags and an ActiveGameplayEffect's source spec tags
- L1552 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchAllSourceSpecTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if all of the given tags are in the ActiveGameplayEffect's source spec tags
- L1554 _public prototype_ `static FGameplayEffectQuery MakeQuery_MatchNoSourceSpecTags(const FGameplayTagContainer& InTags);` — Creates an effect query that will match if there are no common tags between the given tags and an ActiveGameplayEffect's source spec tags
- L1556 _public prototype_ `bool operator==(const FGameplayEffectQuery& Other) const;`
- L1557 _public prototype_ `bool operator!=(const FGameplayEffectQuery& Other) const;`

#### struct `FActiveGameplayEffectQuery`  
`struct FActiveGameplayEffectQuery`  
_L1568-1621_
- reflection: `USTRUCT()`
- desc: Generic querying data structure for active GameplayEffects. Lets us ask things like: Give me duration/magnitude of active gameplay effects with these tags Give me handles to all activate gameplay effects modifying this attribute. Any requirements specified in the query are required: must meet "all" not "one".
- L1572 _public function_ `FActiveGameplayEffectQuery() : OwningTagContainer(nullptr) , EffectTagContainer(nullptr) , OwningTagContainer_Rejection(nullptr) , EffectTagContainer_Rejection(nullptr) , EffectSource(nullptr) , EffectDef(nullptr)`
- L1582 _public function_ `FActiveGameplayEffectQuery(const FGameplayTagContainer* InOwningTagContainer) : OwningTagContainer(InOwningTagContainer) , EffectTagContainer(nullptr) , OwningTagContainer_Rejection(nullptr) , EffectTagContainer_Rejection(nullptr) , EffectSource(nullptr) , EffectDef(nullptr)`
- L1593 _public member_ `FActiveGameplayEffectQueryCustomMatch CustomMatch;` — Bind this to override the default query-matching code.
- L1596 _public prototype_ `bool Matches(const FActiveGameplayEffect& Effect) const;` — Returns true if Effect matches the criteria of this query, which will be overridden by CustomMatch if it is bound. Returns false otherwise.
- L1599 _public member_ `const FGameplayTagContainer* OwningTagContainer;` — used to match with InheritableOwnedTagsContainer
- L1602 _public member_ `const FGameplayTagContainer* EffectTagContainer;` — used to match with InheritableGameplayEffectTags
- L1605 _public member_ `const FGameplayTagContainer* OwningTagContainer_Rejection;` — used to reject matches with InheritableOwnedTagsContainer
- L1608 _public member_ `const FGameplayTagContainer* EffectTagContainer_Rejection;` — used to reject matches with InheritableGameplayEffectTags
- L1611 _public member_ `FGameplayAttribute ModifyingAttribute;` — Matches on GameplayEffects which modify given attribute
- L1614 _public member_ `const UObject* EffectSource;` — Matches on GameplayEffects which come from this source
- L1617 _public member_ `const UGameplayEffect* EffectDef;` — Matches on GameplayEffects with this definition
- L1620 _public member_ `TArray<FActiveGameplayEffectHandle> IgnoreHandles;` — Handles to ignore as matches, even if other criteria is met

#### struct `FCustomModifierDependencyHandle`  
`struct FCustomModifierDependencyHandle`  
_L1624-1636_
- desc: Helper struct to hold data about external dependencies for custom modifiers
- L1626 _public function_ `FCustomModifierDependencyHandle() : ActiveEffectHandles() , ActiveDelegateHandle()`
- L1632 _public member_ `TSet<FActiveGameplayEffectHandle> ActiveEffectHandles;` — Set of handles of active gameplay effects dependent upon a particular external dependency
- L1635 _public member_ `FDelegateHandle ActiveDelegateHandle;` — Delegate handle populated as a result of binding to an external dependency delegate

#### struct `FActiveGameplayEffectsContainer`  
`struct FActiveGameplayEffectsContainer : public FFastArraySerializer`  
_L1652-2026_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- desc: Active GameplayEffects Container -Bucket of ActiveGameplayEffects -Needed for FFastArraySerialization This should only be used by UAbilitySystemComponent. All of this could just live in UAbilitySystemComponent except that we need a distinct USTRUCT to implement FFastArraySerializer. The preferred way to iterate through the ActiveGameplayEffectContainer is with CreateConstIterator/CreateIterator or stl style range iteration: for (const FActiveGameplayEffect& Effect : this) {} for (auto It = CreateConstIterator(); It; ++It) {}
- L1663 _public typedef_ `typedef FActiveGameplayEffectIterator<const FActiveGameplayEffect, FActiveGameplayEffectsContainer> ConstIterator;`
- L1664 _public typedef_ `typedef FActiveGameplayEffectIterator<FActiveGameplayEffect, FActiveGameplayEffectsContainer> Iterator;`
- L1666 _public prototype_ `FActiveGameplayEffectsContainer();`
- L1667 _public prototype_ `~FActiveGameplayEffectsContainer();`
- L1669 _public member_ `UAbilitySystemComponent* Owner;`
- L1670 _public member_ `bool OwnerIsNetAuthority;`
- L1672 _public member_ `FOnGivenActiveGameplayEffectRemoved OnActiveGameplayEffectRemovedDelegate;`
- L1686 _public member_ `TArray<DebugExecutedGameplayEffectData> DebugExecutedGameplayEffects;` — Stores a record of gameplay effects that have executed and their results. Useful for debugging
- L1689 _public prototype_ `void DescribeSelfToVisLog(FVisualLogEntry* Snapshot) const;` — Report our current state to the VisLog
- L1692 _public prototype_ `void GetActiveGameplayEffectDataByAttribute(TMultiMap<FGameplayAttribute, FActiveGameplayEffectsContainer::DebugExecutedGameplayEffectData>& EffectMap) const;`
- L1694 _public prototype_ `void RegisterWithOwner(UAbilitySystemComponent* Owner);`
- L1696 _public prototype_ `FActiveGameplayEffect* ApplyGameplayEffectSpec(const FGameplayEffectSpec& Spec, FPredictionKey& InPredictionKey, bool& bFoundExistingStackableGE);`
- L1698 _public prototype_ `FActiveGameplayEffect* GetActiveGameplayEffect(const FActiveGameplayEffectHandle Handle);`
- L1700 _public prototype_ `const FActiveGameplayEffect* GetActiveGameplayEffect(const FActiveGameplayEffectHandle Handle) const;`
- L1707 _public prototype_ `void PredictivelyExecuteEffectSpec(FGameplayEffectSpec& Spec, FPredictionKey PredictionKey, const bool bPredictGameplayCues = false);` — Predictively execute a given effect spec. Any attribute modifications and effect execution calculations in the effect will run and then if desired predict gameplay cues @note: This method will not predictively run any conditional effects that may be set up in the effect that apply post execution and will only happen if/when this spec is applied on the server. @note: WARNING: This will locally perform attribute changes on your client so beware.
- L1709 _public prototype_ `void ExecuteActiveEffectsFrom(FGameplayEffectSpec &Spec, FPredictionKey PredictionKey = FPredictionKey() );`
- L1711 _public prototype_ `void ExecutePeriodicGameplayEffect(FActiveGameplayEffectHandle Handle);` — This should not be outward facing to the skill system API, should only be called by the owning AbilitySystemComponent
- L1713 _public prototype_ `bool RemoveActiveGameplayEffect(FActiveGameplayEffectHandle Handle, int32 StacksToRemove, bool bPredictionRejected = false);`
- L1715 _public prototype_ `void GetGameplayEffectStartTimeAndDuration(FActiveGameplayEffectHandle Handle, float& EffectStartTime, float& EffectDuration) const;`
- L1717 _public prototype_ `float GetGameplayEffectMagnitude(FActiveGameplayEffectHandle Handle, FGameplayAttribute Attribute) const;`
- L1719 _public prototype_ `void SetActiveGameplayEffectLevel(FActiveGameplayEffectHandle ActiveHandle, int32 NewLevel);`
- L1728 _public prototype_ `void UpdateActiveGameplayEffectSetByCallerMagnitude(FActiveGameplayEffectHandle ActiveHandle, const FGameplayTag& SetByCallerTag, float NewValue);` — Update a set-by-caller magnitude for the active effect to match the new value, if possible @param ActiveHandle		Handle of the active effect to update @param SetByCallerTag	Set-by-caller tag to update @param NewValue			New value of the set-by-caller magnitude
- L1736 _public prototype_ `void UpdateActiveGameplayEffectSetByCallerMagnitudes(FActiveGameplayEffectHandle ActiveHandle, const TMap<FGameplayTag, float>& NewSetByCallerValues);` — Update set-by-caller magnitudes for the active effect to match the new values, if possible; Replaces existing values @param ActiveHandle			Handle of the active effect to update @param NewSetByCallerValues	Map of set-by-caller tag to new magnitude
- L1738 _public prototype_ `void SetAttributeBaseValue(FGameplayAttribute Attribute, float NewBaseValue);`
- L1740 _public prototype_ `float GetAttributeBaseValue(FGameplayAttribute Attribute) const;`
- L1742 _public prototype_ `float GetEffectContribution(const FAggregatorEvaluateParameters& Parameters, FActiveGameplayEffectHandle ActiveHandle, FGameplayAttribute Attribute);`
- L1745 _public prototype_ `void ApplyModToAttribute(const FGameplayAttribute &Attribute, TEnumAsByte<EGameplayModOp::Type> ModifierOp, float ModifierMagnitude, const FGameplayEffectModCallbackData* ModData=nullptr);` — Actually applies given mod to the attribute
- L1754 _public prototype_ `const FGameplayTagContainer* GetGameplayEffectSourceTagsFromHandle(FActiveGameplayEffectHandle Handle) const;` — Get the source tags from the gameplay spec represented by the specified handle, if possible @param Handle	Handle of the gameplay effect to retrieve source tags from @return Source tags from the gameplay spec represented by the handle, if possible
- L1763 _public prototype_ `const FGameplayTagContainer* GetGameplayEffectTargetTagsFromHandle(FActiveGameplayEffectHandle Handle) const;` — Get the target tags from the gameplay spec represented by the specified handle, if possible @param Handle	Handle of the gameplay effect to retrieve target tags from @return Target tags from the gameplay spec represented by the handle, if possible
- L1770 _public prototype_ `void CaptureAttributeForGameplayEffect(OUT FGameplayEffectAttributeCaptureSpec& OutCaptureSpec);` — Populate the specified capture spec with the data necessary to capture an attribute from the container @param OutCaptureSpec	[OUT] Capture spec to populate with captured data
- L1772 _public prototype_ `void PrintAllGameplayEffects() const;`
- L1779 _public function_ `inline int32 GetNumGameplayEffects() const` — Returns the total number of gameplay effects. NOTE this does include GameplayEffects that pending removal. Any pending remove gameplay effects are deleted at the end of their scope lock
- L1793 _public prototype_ `void CheckDuration(FActiveGameplayEffectHandle Handle);`
- L1796 _public prototype_ `ELifetimeCondition GetReplicationCondition() const;` — Returns which ELifetimeCondition can be used for this instance to replicate to relevant connections. This can be used to change the condition if the property is set to use COND_Dynamic in an object's GetLifetimeReplicatedProps implementation.
- L1799 _public function_ `void SetIsUsingReplicationCondition(bool bInIsUsingReplicationCondition)` — Set whether the container is using COND_Dynamic and setting the proper condition at runtime.
- L1802 _public function_ `bool IsUsingReplicationCondition() const` — Return whether the container is using COND_Dynamic and setting the proper condition at runtime.
- L1804 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParms);`
- L1806 _public prototype_ `void Uninitialize();`
- L1808 _public prototype_ `bool CanApplyAttributeModifiers(const UGameplayEffect *GameplayEffect, float Level, const FGameplayEffectContextHandle& EffectContext);`
- L1810 _public prototype_ `TArray<float> GetActiveEffectsTimeRemaining(const FGameplayEffectQuery& Query) const;`
- L1812 _public prototype_ `TArray<float> GetActiveEffectsDuration(const FGameplayEffectQuery& Query) const;`
- L1814 _public prototype_ `TArray<TPair<float,float>> GetActiveEffectsTimeRemainingAndDuration(const FGameplayEffectQuery& Query) const;`
- L1816 _public prototype_ `TArray<FActiveGameplayEffectHandle> GetActiveEffects(const FGameplayEffectQuery& Query) const;`
- L1818 _public prototype_ `float GetActiveEffectsEndTime(const FGameplayEffectQuery& Query, TArray<AActor*>& Instigators) const;`
- L1819 _public prototype_ `bool GetActiveEffectsEndTimeAndDuration(const FGameplayEffectQuery& Query, float& EndTime, float& Duration, TArray<AActor*>& Instigators) const;`
- L1822 _public prototype_ `TArray<FActiveGameplayEffectHandle> GetAllActiveEffectHandles() const;` — Returns an array of all of the active gameplay effect handles
- L1824 _public prototype_ `void ModifyActiveEffectStartTime(FActiveGameplayEffectHandle Handle, float StartTimeDiff);`
- L1826 _public prototype_ `int32 RemoveActiveEffects(const FGameplayEffectQuery& Query, int32 StacksToRemove);`
- L1833 _public prototype_ `int32 GetActiveEffectCount(const FGameplayEffectQuery& Query, bool bEnforceOnGoingCheck = true) const;` — Get the count of the effects matching the specified query (including stack count) @return Count of the effects matching the specified query
- L1835 _public prototype_ `bool IsServerWorldTimeAvailable() const;`
- L1837 _public prototype_ `float GetServerWorldTime() const;`
- L1839 _public prototype_ `float GetWorldTime() const;`
- L1841 _public prototype_ `bool HasReceivedEffectWithPredictedKey(FPredictionKey PredictionKey) const;`
- L1843 _public prototype_ `bool HasPredictedEffectWithPredictedKey(FPredictionKey PredictionKey) const;`
- L1846 _public prototype_ `void SetBaseAttributeValueFromReplication(const FGameplayAttribute& Attribute, float NewBaseValue, float OldBaseValue);` — `UE_DEPRECATED(5.5, "Replaced by private SetBaseAttributeValueFromReplication that uses FGameplayAttributeData")`
- L1848 _public prototype_ `void GetAllActiveGameplayEffectSpecs(TArray<FGameplayEffectSpec>& OutSpecCopies) const;`
- L1850 _public prototype_ `void DebugCyclicAggregatorBroadcasts(struct FAggregator* Aggregator);`
- L1853 _public prototype_ `void CloneFrom(const FActiveGameplayEffectsContainer& Source);` — Performs a deep copy on the source container, duplicating all gameplay effects and reconstructing the attribute aggregator map to match the passed in source.
- L1858 _public prototype_ `FOnGameplayAttributeChange& RegisterGameplayAttributeEvent(FGameplayAttribute Attribute);` — `UE_DEPRECATED(4.17, "Use GetGameplayAttributeValueChangeDelegate (the delegate signature has changed)")`
- L1860 _public prototype_ `FOnGameplayAttributeValueChange& GetGameplayAttributeValueChangeDelegate(FGameplayAttribute Attribute);`
- L1862 _public prototype_ `void IncrementLock();`
- L1863 _public prototype_ `void DecrementLock();`
- L1865 _public function_ `inline ConstIterator CreateConstIterator() const`
- L1866 _public function_ `inline Iterator CreateIterator()`
- L1869 _public prototype_ `void RecomputeStartWorldTimes(const float WorldTime, const float ServerWorldTime);` — Recomputes the start time for all active abilities
- L1872 _public prototype_ `void PostReplicatedReceive(const FFastArraySerializer::FPostReplicatedReceiveParameters& Parameters);` — Called every time data has been modified by the FastArraySerializer
- L1875 _private prototype_ `void SetBaseAttributeValueFromReplication(const FGameplayAttribute& Attribute, const FGameplayAttributeData& NewValue, const FGameplayAttributeData& OldValue);`
- L1883 _private function_ `inline const FActiveGameplayEffect* GetActiveGameplayEffect(int32 idx) const` — Accessors for internal functions to get GameplayEffects directly by index. Note this will return GameplayEffects that are pending removal! To iterate over all 'valid' gameplay effects, use the CreateConstIterator/CreateIterator or the stl style range iterator
- L1888 _private function_ `inline FActiveGameplayEffect* GetActiveGameplayEffect(int32 idx)`
- L1911 _private member_ `TArray<FActiveGameplayEffect> GameplayEffects_Internal;` — `UPROPERTY()` — Our active list of Effects. Do not access this directly (Even from internal functions!) Use GetNumGameplayEffect() / GetGameplayEffect() !
- L1913 _private prototype_ `void InternalUpdateNumericalAttribute(FGameplayAttribute Attribute, float NewValue, const FGameplayEffectModCallbackData* ModData, bool bFromRecursiveCall=false);`
- L1916 _private member_ `const struct FGameplayEffectModCallbackData* CurrentModcallbackData;` — Cached pointer to current mod data needed for callbacks. We cache it in the AGE struct to avoid passing it through all the delegate/aggregator plumbing
- L1926 _private prototype_ `bool InternalExecuteMod(FGameplayEffectSpec& Spec, FGameplayModifierEvaluatedData& ModEvalData);` — Helper function to execute a mod on owned attributes @param Spec			Gameplay effect spec executing the mod @param ModEvalData	Evaluated data for the mod @return True if the mod successfully executed, false if it did not
- L1928 _public function_ `bool IsNetAuthority() const`
- L1933 _private prototype_ `void InternalExecutePeriodicGameplayEffect(FActiveGameplayEffect& ActiveEffect);`
- L1936 _private prototype_ `bool InternalRemoveActiveGameplayEffect(int32 Idx, int32 StacksToRemove, bool bPrematureRemoval, bool bPredictionRejected = false);` — Called internally to actually remove a GameplayEffect or to reduce its StackCount. Returns true if we resized our internal GameplayEffect array.
- L1939 _private prototype_ `void InternalOnActiveGameplayEffectAdded(FActiveGameplayEffect& Effect, bool bInvokePredictedEffects);` — Called both in server side creation and replication creation/deletion
- L1940 _private prototype_ `void InternalOnActiveGameplayEffectRemoved(FActiveGameplayEffect& Effect, bool bInvokePredictedEffects, const FGameplayEffectRemovalInfo& GameplayEffectRemovalInfo);`
- L1942 _private prototype_ `void RemoveActiveGameplayEffectGrantedTagsAndModifiers(const FActiveGameplayEffect& Effect, bool bInvokePredictedEffects, bool bPredictionRejected = false);`
- L1943 _private prototype_ `void AddActiveGameplayEffectGrantedTagsAndModifiers(FActiveGameplayEffect& Effect, bool bInvokePredictedEffects);`
- L1946 _private prototype_ `void RemoveActiveEffectTagDependency(const FGameplayTagContainer& Tags, FActiveGameplayEffectHandle Handle);` — Updates tag dependency map when a GameplayEffect is removed
- L1949 _private prototype_ `void AddCustomMagnitudeExternalDependencies(FActiveGameplayEffect& Effect);` — Internal helper function to bind the active effect to all of the custom modifier magnitude external dependency delegates it contains, if any
- L1952 _private prototype_ `void RemoveCustomMagnitudeExternalDependencies(FActiveGameplayEffect& Effect);` — Internal helper function to unbind the active effect from all of the custom modifier magnitude external dependency delegates it may have bound to, if any
- L1955 _private prototype_ `void OnCustomMagnitudeExternalDependencyFired(TSubclassOf<UGameplayModMagnitudeCalculation> MagnitudeCalculationClass);` — Internal callback fired as a result of a custom modifier magnitude external dependency delegate firing; Updates affected active gameplay effects as necessary
- L1962 _private prototype_ `void RestartActiveGameplayEffectDuration(FActiveGameplayEffect& ActiveGameplayEffect);` — Updates the active GE's start time to current world time. Despite what the function name suggests, duration is not refreshed or re-calculated here. Only queries to the active effect's remaining time are affected. Call-sites should update duration on the GE spec if relevant, and should ensure that a new expiration timer is set in the world timer manager that fires at T = (new) start time + (new) duration.
- L1966 _private member_ `TMap<FGameplayAttribute, FAggregatorRef> AttributeAggregatorMap;`
- L1969 _private member_ `TMap<FGameplayAttribute, FOnGameplayAttributeChange> AttributeChangeDelegates;` — DEPRECATED: use AttributeValueChangeDelegates
- L1971 _private member_ `TMap<FGameplayAttribute, FOnGameplayAttributeValueChange> AttributeValueChangeDelegates;`
- L1974 _private member_ `TMap<FObjectKey, FCustomModifierDependencyHandle> CustomMagnitudeClassDependencies;` — Mapping of custom gameplay modifier magnitude calculation class to dependency handles for triggering updates on external delegates firing
- L1977 _private member_ `TMap<TWeakObjectPtr<UGameplayEffect>, TArray<FActiveGameplayEffectHandle> > SourceStackingMap;` — A map to manage stacking while we are the source
- L1979 _private prototype_ `FAggregatorRef& FindOrCreateAttributeAggregator(const FGameplayAttribute& Attribute);`
- L1981 _private prototype_ `void CleanupAttributeAggregator(const FGameplayAttribute& Attribute);`
- L1983 _private prototype_ `void OnAttributeAggregatorDirty(FAggregator* Aggregator, FGameplayAttribute Attribute, bool FromRecursiveCall=false);`
- L1985 _private prototype_ `void OnMagnitudeDependencyChange(FActiveGameplayEffectHandle Handle, const FAggregator* ChangedAgg);`
- L1987 _private prototype_ `void OnStackCountChange(FActiveGameplayEffect& ActiveEffect, int32 OldStackCount, int32 NewStackCount);`
- L1989 _private prototype_ `void OnPredictiveGameplayEffectStackCaughtUp(FActiveGameplayEffectHandle Handle);`
- L1991 _private prototype_ `void OnDurationChange(FActiveGameplayEffect& ActiveEffect);`
- L1993 _private prototype_ `void UpdateAllAggregatorModMagnitudes(FActiveGameplayEffect& ActiveEffect);`
- L1995 _private prototype_ `void UpdateAggregatorModMagnitudes(const TSet<FGameplayAttribute>& AttributesToUpdate, FActiveGameplayEffect& ActiveEffect);`
- L1998 _private prototype_ `FActiveGameplayEffect* FindStackableActiveGameplayEffect(const FGameplayEffectSpec& Spec);` — Helper function to find the active GE that the specified spec can stack with, if any
- L2001 _private prototype_ `bool HandleActiveGameplayEffectStackOverflow(const FActiveGameplayEffect& ActiveStackableGE, const FGameplayEffectSpec& OldSpec, const FGameplayEffectSpec& OverflowingSpec, FPredictionKey PredictionKey = {});` — Helper function to handle the case of same-effect stacking overflow; Returns true if the overflow application should apply, false if it should not
- L2003 _private prototype_ `bool ShouldUseMinimalReplication();`
- L2005 _private prototype_ `void DeletePendingActiveGameplayEffect();`
- L2007 _private member_ `mutable int32 ScopedLockCount;`
- L2008 _private member_ `int32 PendingRemoves;`
- L2009 _private member_ `uint32 NumConsecutiveUnmappedReferencesDebug = 0;`
- L2011 _private member_ `FActiveGameplayEffect* PendingGameplayEffectHead;` — Head of pending GE linked list
- L2012 _private member_ `FActiveGameplayEffect** PendingGameplayEffectNext;` — Points to the where to store the next pending GE (starts pointing at head, as more are added, points further down the list).
- L2014 _private member_ `uint8 bIsUsingReplicationCondition : 1;`

#### struct `FActiveGameplayEffectsContainer::DebugExecutedGameplayEffectData`  
`struct DebugExecutedGameplayEffectData`  
_L1674-1682_
- L1676 _public member_ `FString GameplayEffectName;`
- L1677 _public member_ `FString ActivationState;`
- L1678 _public member_ `FGameplayAttribute Attribute;`
- L1679 _public member_ `TEnumAsByte<EGameplayModOp::Type> ModifierOp;`
- L1680 _public member_ `float Magnitude;`
- L1681 _public member_ `int32 StackCount;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FActiveGameplayEffectsContainer > : public TStructOpsTypeTraitsBase2< FActiveGameplayEffectsContainer >`  
_L2029-2036_
- inherits: `TStructOpsTypeTraitsBase2<FActiveGameplayEffectsContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L2032-2035_

#### struct `FScopedActiveGameplayEffectLock`  
`struct FScopedActiveGameplayEffectLock`  
_L2047-2054_
- desc: FScopedActiveGameplayEffectLock Provides a mechanism for locking the active gameplay effect list while possibly invoking callbacks into gamecode. For example, if some internal code in FActiveGameplayEffectsContainer is iterating through the active GE list or holding onto a pointer to something in that list, any changes to that list could cause memory the move out from underneath. This scope lock will queue deletions and additions until after the scope is over. The additions and deletions will actually go through, but we will defer the memory operations to the active gameplay effect list.
- L2049 _public prototype_ `FScopedActiveGameplayEffectLock(FActiveGameplayEffectsContainer& InContainer);`
- L2050 _public prototype_ `~FScopedActiveGameplayEffectLock();`
- L2053 _private member_ `FActiveGameplayEffectsContainer& Container;`

#### struct `FGameplayEffectVersion`  
`struct FGameplayEffectVersion`  
_L2074-2086_
- reflection: `USTRUCT()`
- desc: Gameplay Effects Data needs to be versioned (e.g. going from Monolithic to Modular) Unfortunately, the Custom Package Versioning doesn't work for this case, because we're upgrading outside of the Serialize function.  For that reason we want to store a UProperty that says what version we're on.  Unfortunately that propagates from Parent to Child (inheritance rules) so to overcome that, we have a special UStruct that always serializes its data (so it will always be loaded, not inherited). Here is how to do that: 1. Return false in Identical (which effectively disables delta serialization). 2. Reset the value in PostInitProperties, thereby not using the inherited value on the initial preload. 3. Ensure the CurrentVersion field isn't marked up as a UPROPERTY to avoid automatic copying between parent/child. 4. Implement Serialize to ensure the CurrentVersion is still serialized.
- L2079 _public member_ `EGameplayEffectVersion CurrentVersion;` — The version the owning GameplayEffect is currently set to
- L2082 _public function_ `bool Identical(const FGameplayEffectVersion* Other, uint32 PortFlags) const` — By always returning false here, we can disable delta serialization
- L2085 _public prototype_ `bool Serialize(FStructuredArchive::FSlot Slot);` — We must use a custom serializer to make sure CurrentVersion serializes properly (without markup to avoid unwanted copying)

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayEffectVersion> : public TStructOpsTypeTraitsBase2<FGameplayEffectVersion>`  
_L2089-2096_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayEffectVersion>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L2092-2095_

#### class `UGameplayEffect`  
`class UGameplayEffect : public UObject, public IGameplayTagAssetInterface`  
_L2104-2478_
- reflection: `UCLASS(Blueprintable, PrioritizeCategories="Status Duration GameplayEffect GameplayCues Stacking", meta = (ShortTooltip = "A GameplayEffect modifies attributes and tags."), MinimalAPI)`
- inherits: `UObject,IGameplayTagAssetInterface`
- desc: UGameplayEffect The GameplayEffect definition. This is the data asset defined in the editor that drives everything. This is only blueprintable to allow for templating gameplay effects. Gameplay effects should NOT contain blueprint graphs.
- L2111 _public member_ `static const float INFINITE_DURATION;` — These are deprecated but remain for backwards compat, please use FGameplayEffectConstants:: instead.
- L2112 _public member_ `static const float INSTANT_APPLICATION;`
- L2113 _public member_ `static const float NO_PERIOD;`
- L2114 _public member_ `static const float INVALID_LEVEL;`
- L2117 _public prototype_ `virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;` — `UE_DEPRECATED(5.3, "The implementation and method name did not match. Use GetGrantedTags() to get the tags Granted to the Actor this GameplayEffect is applied to.")`
- L2120 _public prototype_ `virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;` — `UE_DEPRECATED(5.3, "The implementation and method name did not match. Use GetGrantedTags().HasTag() to check against the tags this GameplayEffect will Grant to the Actor.")`
- L2123 _public prototype_ `virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;` — `UE_DEPRECATED(5.3, "The implementation and method name did not match. Use GetGrantedTags().HasAll() to check against the tags this GameplayEffect will Grant to the Actor.")`
- L2126 _public prototype_ `virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;` — `UE_DEPRECATED(5.3, "The implementation and method name did not match. Use GetGrantedTags().HasAny() to check against the tags this GameplayEffect will Grant to the Actor.")`
- L2128 _public prototype_ `virtual void GetBlockedAbilityTags(FGameplayTagContainer& OutTagContainer) const;`
- L2131 _public prototype_ `virtual void PostInitProperties() override;` — Needed to properly disable inheriting the version value from its parent.
- L2134 _public prototype_ `virtual void PostLoad() override;` — PostLoad gets called once after the asset has been loaded.  It does not get called again on Blueprint recompile (@see PostCDOCompiled)
- L2137 _public prototype_ `virtual void OnGameplayEffectChanged();` — Called when the Gameplay Effect has finished loading.  This is used to catch both PostLoad (the initial load) and PostCDOCompiled (any subsequent changes)
- L2141 _public prototype_ `virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;` — Do our upgrades in PostCDOCompiled
- L2144 _public prototype_ `void PostCDOCompiledFixupSubobjects();` — We need to fix-up all of the SubObjects manually since the Engine doesn't fully support this
- L2146 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;`
- L2152 _public prototype_ `bool CanApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const;` — Can we Apply this Gameplay Effect?  Note: Apply is the generic term for adding to the active container or executing it.
- L2158 _public prototype_ `bool OnAddedToActiveContainer(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const;` — Receive a notify that this GameplayEffect has been added to an Active Container.  ActiveGE will be the Active version of this GameplayEffect. Returns true if this GameplayEffect should be active (or false to inhibit).
- L2164 _public prototype_ `void OnExecuted(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const;` — Receive a notify that this GameplayEffect has been executed (it must be instant, as it is not added to the Container). Since it is not added to the container, it will not have an associated FActiveGameplayEffect, just the FGameplayEffectSpec.
- L2170 _public prototype_ `void OnApplied(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const;` — Receive a notify that this GameplayEffect has been applied (this GE is either previously added to the container or executed in such cases). However, this also encompasses cases where a GE was added to a container previously and then applied again to 'stack'.  It does not happen for periodic executions of a duration GE.
- L2173 _public function_ `const FGameplayTagContainer& GetAssetTags() const` — Returns all tags that this GE *has* and *does not* grant to any Actor.
- L2176 _public function_ `const FGameplayTagContainer& GetGrantedTags() const` — Returns all tags granted to the Target Actor of this gameplay effect. That is to say: If this GE is applied to an Actor, they get these tags.
- L2179 _public function_ `const FGameplayTagContainer& GetBlockedAbilityTags() const` — Returns all blocking ability tags granted by this gameplay effect definition. Blocking tags means the target will not be able to execute an ability with this asset tag.
- L2182 _public prototype_ `int32 GetStackLimitCount() const;` — Returns the maximum stack size for this gameplay effect
- L2185 _public prototype_ `EGameplayEffectStackingExpirationPolicy GetStackExpirationPolicy() const;` — Returns the stack expiration policy for this gameplay effect
- L2196 _public prototype_ `template<typename GEComponentClass> const GEComponentClass* FindComponent() const;` — Find and return the component of class GEComponentClass on this GE, if one exists. Note: The const is a hint that these are assets that should not be modified at runtime. If you're building your own dynamic GameplayEffect: @see AddComponent, FindOrAddComponent. @return	The component matching the query (if it exists).
- L2199 _public prototype_ `const UGameplayEffectComponent* FindComponent(TSubclassOf<UGameplayEffectComponent> ClassToFind) const;` — @return the first component that derives from the passed-in ClassToFind, if one exists.
- L2207 _public prototype_ `template<typename GEComponentClass> GEComponentClass& AddComponent();` — Add a GameplayEffectComponent to the GameplayEffect.  This does not check for duplicates and is guaranteed to return a new instance. @return	The newly added instanced GameplayEffectComponent.
- L2215 _public prototype_ `template<typename GEComponentClass> GEComponentClass& FindOrAddComponent();` — Find an existing GameplayEffectComponent of the requested class, or add one if none are found. @return	The existing instance of GEComponentClass, or a newly added one.
- L2219 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Allow each Gameplay Effect Component to validate its own data.  Call this version (Super::IsDataValid) _after_ your overridden version to update EditorStatusText.
- L2227 _protected prototype_ `EGameplayEffectVersion GetVersion() const;` — Let's keep track of the version so that we can upgrade the Components properly.  This will be set properly in PostLoad after upgrades.
- L2230 _protected prototype_ `void SetVersion(EGameplayEffectVersion Version);` — Sets the Version of the class to denote it's been upgraded
- L2233 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext SaveContext) override;` — We should intercept the Save call and revalidate all of our deprecated values to avoid hanging onto stale data
- L2237 _private prototype_ `void ConvertAbilitiesComponent();` — Helper functions for converting data to use components
- L2238 _private prototype_ `void ConvertAdditionalEffectsComponent();`
- L2239 _private prototype_ `void ConvertAssetTagsComponent();`
- L2240 _private prototype_ `void ConvertBlockByTagsComponent();`
- L2241 _private prototype_ `void ConvertChanceToApplyComponent();`
- L2242 _private prototype_ `void ConvertCustomCanApplyComponent();`
- L2243 _private prototype_ `void ConvertImmunityComponent();`
- L2244 _private prototype_ `void ConvertRemoveOtherComponent();`
- L2245 _private prototype_ `void ConvertTagRequirementsComponent();`
- L2246 _private prototype_ `void ConvertTargetTagsComponent();`
- L2247 _private prototype_ `void ConvertUIComponent();`
- L2256 _public member_ `EGameplayEffectDurationType DurationPolicy;` — `UPROPERTY(EditDefaultsOnly, Category=Duration)` — Policy for the duration of this effect
- L2260 _public member_ `FGameplayEffectModifierMagnitude DurationMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category=Duration, meta=(EditCondition="DurationPolicy == EGameplayEffectDurationType::HasDuration", EditConditionHides))` — Duration in seconds. 0.0 for instantaneous effects; -1.0 for infinite duration. When applying stacks onto an existing active effect, the new spec's Duration is considered.
- L2264 _public member_ `FGameplayEffectModifierMagnitude MaxDurationMagnitude;` — `UPROPERTY(EditDefaultsOnly, Category = Duration, meta = (EditCondition = "DurationPolicy == EGameplayEffectDurationType::HasDuration", EditConditionHides))` — MaxDuration in seconds. <= 0.0 for unlimited. When applying stacks onto an existing active effect, the new spec's MaxDuration is considered.
- L2268 _public member_ `FScalableFloat Period;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Duration|Period", meta=(EditCondition="DurationPolicy != EGameplayEffectDurationType::Instant", EditConditionHides))` — Period in seconds. 0.0 for non-periodic effects
- L2272 _public member_ `bool bExecutePeriodicEffectOnApplication;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Duration|Period", meta=(EditCondition="true", EditConditionHides))` — If true, the effect executes on application and then at every period interval. If false, no execution occurs until the first period elapses.
- L2276 _public member_ `EGameplayEffectPeriodInhibitionRemovedPolicy PeriodicInhibitionPolicy;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Duration|Period", meta=(EditCondition="true", EditConditionHides))` — How we should respond when a periodic gameplay effect is no longer inhibited
- L2280 _public member_ `TArray<FGameplayModifierInfo> Modifiers;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=GameplayEffect, meta=(TitleProperty=Attribute))` — Array of modifiers that will affect the target of this effect
- L2284 _public member_ `TArray<FGameplayEffectExecutionDefinition> Executions;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffect)` — Array of executions that will affect the target of this effect
- L2289 _public member_ `FScalableFloat ChanceToApplyToTarget_DEPRECATED;` — `UE_DEPRECATED(5.3, "Chance To Apply To Target is deprecated. Use the UChanceToApplyGameplayEffectComponent instead.")` — `UPROPERTY(meta = (GameplayAttribute = "True", DeprecatedProperty))` — Probability that this gameplay effect will be applied to the target actor (0.0 for never, 1.0 for always)
- L2293 _public member_ `TArray<TSubclassOf<UGameplayEffectCustomApplicationRequirement> > ApplicationRequirements_DEPRECATED;` — `UE_DEPRECATED(5.3, "Application Requirements is deprecated. Use the UCustomCanApplyGameplayEffectComponent instead.")` — `UPROPERTY(meta = (DisplayName = "Application Requirement", DeprecatedProperty))`
- L2298 _public member_ `TArray<FConditionalGameplayEffect> ConditionalGameplayEffects;` — `UE_DEPRECATED(5.3, "Conditional Gameplay Effects is deprecated. Use the UAdditionalEffectsGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = "Deprecated|GameplayEffect", meta = (DeprecatedProperty))` — other gameplay effects that will be applied to the target of this effect if this effect applies
- L2302 _public member_ `TArray<TSubclassOf<UGameplayEffect>> OverflowEffects;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stacking|Overflow", meta = (EditConditionHides, EditCondition = "StackingType != EGameplayEffectStackingType::None"))` — Effects to apply when a stacking effect "overflows" its stack count through another attempted application. Added whether the overflow application succeeds or not. Overflow occurs for each added stack if stack count limit is infinite (0 or -1)
- L2306 _public member_ `bool bDenyOverflowApplication;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stacking|Overflow", meta = (EditConditionHides, EditCondition = "StackingType != EGameplayEffectStackingType::None"))` — If true, stacking attempts made while at the stack count will fail, resulting in the duration and context not being refreshed
- L2310 _public member_ `bool bClearStackOnOverflow;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stacking|Overflow", meta=(EditConditionHides, EditCondition="(StackingType != EGameplayEffectStackingType::None) && bDenyOverflowApplication"))` — If true, the entire stack of the effect will be cleared once it overflows
- L2315 _public member_ `TArray<TSubclassOf<UGameplayEffect>> PrematureExpirationEffectClasses;` — `UE_DEPRECATED(5.3, "Premature Expiration Effect Classes is deprecated. Use the UAdditionalEffectsGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category="Deprecated|Expiration", meta = (DeprecatedProperty))` — Effects to apply when this effect is made to expire prematurely (like via a forced removal, clear tags, etc.); Only works for effects with a duration
- L2320 _public member_ `TArray<TSubclassOf<UGameplayEffect>> RoutineExpirationEffectClasses;` — `UE_DEPRECATED(5.3, "Routine Expiration Effect Classes is deprecated. Use the UAdditionalEffectsGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category="Deprecated|Expiration", meta = (DeprecatedProperty))` — Effects to apply when this effect expires naturally via its duration; Only works for effects with a duration
- L2324 _public member_ `bool bRequireModifierSuccessToTriggerCues;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayCues")` — If true, cues will only trigger when GE modifiers succeed being applied (whether through modifiers or executions)
- L2328 _public member_ `bool bSuppressStackingCues;` — `UPROPERTY(EditDefaultsOnly, Category = "GameplayCues")` — If true, GameplayCues will only be triggered for the first instance in a stacking GameplayEffect.
- L2332 _public member_ `TArray<FGameplayEffectCue> GameplayCues;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameplayCues")` — Cues to trigger non-simulated reactions in response to this GameplayEffect such as sounds, particle effects, etc
- L2337 _public member_ `TObjectPtr<class UGameplayEffectUIData> UIData;` — `UE_DEPRECATED(5.3, "UI Data is deprecated. UGameplayEffectUIData now dervies from UGameplayEffectComponent, add it as a GameplayEffectComponent. You can then access it with FindComponent<UGameplayEffectUIData>().")` — `UPROPERTY(BlueprintReadOnly, Transient, Instanced, Category = "Deprecated|Display", meta = (DeprecatedProperty))` — Data for the UI representation of this effect. This should include things like text, icons, etc. Not available in server-only builds.
- L2346 _public member_ `FInheritedTagContainer InheritableGameplayEffectTags;` — `UE_DEPRECATED(5.3, "Inheritable Gameplay Effect Tags is deprecated. To configure, add a UAssetTagsGameplayEffectComponent. To access, use GetAssetTags.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (DisplayName = "GameplayEffectAssetTag", Categories="GameplayEffectTagsCategory", DeprecatedProperty))` — The GameplayEffect's Tags: tags the the GE *has* and DOES NOT give to the actor.
- L2351 _public member_ `FInheritedTagContainer InheritableOwnedTagsContainer;` — `UE_DEPRECATED(5.3, "Inheritable Owned Tags Container is deprecated. To configure, add a UTargetTagsGameplayEffectComponent. To access, use GetGrantedTags.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (DisplayName="GrantedTags", Categories="OwnedTagsCategory", DeprecatedProperty))` — These tags are applied to the actor I am applied to
- L2356 _public member_ `FInheritedTagContainer InheritableBlockedAbilityTagsContainer;` — `UE_DEPRECATED(5.3, "Inheritable Blocked Ability Tags Container is deprecated. Use the UTargetTagsGameplayEffectComponent instead. To access, use GetBlockedAbilityTags.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (DisplayName="GrantedBlockedAbilityTags", Categories="BlockedAbilityTagsCategory", DeprecatedProperty))` — These blocked ability tags are applied to the actor I am applied to
- L2361 _public member_ `FGameplayTagRequirements OngoingTagRequirements;` — `UE_DEPRECATED(5.3, "Ongoing Tag Requirements is deprecated. Use the UTargetTagRequirementsGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (Categories="OngoingTagRequirementsCategory", DeprecatedProperty))` — Once Applied, these tags requirements are used to determined if the GameplayEffect is "on" or "off". A GameplayEffect can be off and do nothing, but still applied.
- L2366 _public member_ `FGameplayTagRequirements ApplicationTagRequirements;` — `UE_DEPRECATED(5.3, "Application Tag Requirements is deprecated. Use the UTargetTagRequirementsGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (Categories="ApplicationTagRequirementsCategory", DeprecatedProperty))` — Tag requirements for this GameplayEffect to be applied to a target. This is pass/fail at the time of application. If fail, this GE fails to apply.
- L2371 _public member_ `FGameplayTagRequirements RemovalTagRequirements;` — `UE_DEPRECATED(5.3, "Removal Tag Requirements is deprecated. Use the URemoveOtherGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (Categories="ApplicationTagRequirementsCategory", DeprecatedProperty))` — Tag requirements that if met will remove this effect. Also prevents effect application.
- L2376 _public member_ `FInheritedTagContainer RemoveGameplayEffectsWithTags;` — `UE_DEPRECATED(5.3, "Remove Gameplay Effects With Tags is deprecated. Use the UTargetTagRequirementsGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (Categories="RemoveTagRequirementsCategory", DeprecatedProperty))` — GameplayEffects that *have* tags in this container will be cleared upon effect application.
- L2381 _public member_ `FGameplayTagRequirements GrantedApplicationImmunityTags;` — `UE_DEPRECATED(5.3, "Granted Application Immunity Tags is deprecated. Use the UImmunityGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (DisplayName = "GrantedApplicationImmunityTags", Categories="GrantedApplicationImmunityTagsCategory", DeprecatedProperty))` — Grants the owner immunity from these source tags.
- L2386 _public member_ `FGameplayEffectQuery GrantedApplicationImmunityQuery;` — `UE_DEPRECATED(5.3, "Granted Application Immunity Query is deprecated. Use the UImmunityGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = Deprecated, meta = (DeprecatedProperty))` — Grants immunity to GameplayEffects that match this query. Queries are more powerful but slightly slower than GrantedApplicationImmunityTags.
- L2390 _public member_ `bool HasGrantedApplicationImmunityQuery = false;` — `UE_DEPRECATED(5.3, "HasGrantedApplicationImmunityQuery is deprecated. Use the UImmunityGameplayEffectComponent instead.")` — Cached !GrantedApplicationImmunityQuery.IsEmpty(). Set on PostLoad.
- L2395 _public member_ `FGameplayEffectQuery RemoveGameplayEffectQuery;` — `UE_DEPRECATED(5.3, "Remove Gameplay Effect Query is deprecated. Use the URemoveOtherGameplayEffectComponent instead.")` — `UPROPERTY(BlueprintReadOnly, Category = Tags, meta = (DisplayAfter = "RemovalTagRequirements", DeprecatedProperty))` — On Application of an effect, any active effects with this this query that matches against the added effect will be removed. Queries are more powerful but slightly slower than RemoveGameplayEffectsWithTags.
- L2399 _public member_ `bool HasRemoveGameplayEffectsQuery = false;` — `UE_DEPRECATED(5.3, "HasRemoveGameplayEffectsQuery is deprecated. Use the URemoveOtherGameplayEffectComponent instead.")` — Cached !RemoveGameplayEffectsQuery.IsEmpty(). Set on PostLoad.
- L2409 _public member_ `EGameplayEffectStackingType StackingType;` — `UE_DEPRECATED(5.7, "Stacking Type will be made private, Please use GetStackingType.")` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stacking)` — How this GameplayEffect stacks with other instances of this same GameplayEffect
- L2413 _public member_ `int32 StackLimitCount;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stacking, meta = (EditConditionHides, EditCondition = "StackingType != EGameplayEffectStackingType::None"))` — Stack limit for StackingType. A value of -1 or 0 means no limit.
- L2417 _public member_ `EGameplayEffectStackingDurationPolicy StackDurationRefreshPolicy;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stacking, meta = (EditConditionHides, EditCondition = "StackingType != EGameplayEffectStackingType::None"))` — Policy for how the effect duration should be refreshed while stacking
- L2421 _public member_ `EGameplayEffectStackingPeriodPolicy StackPeriodResetPolicy;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stacking, meta = (EditConditionHides, EditCondition = "StackingType != EGameplayEffectStackingType::None"))` — Policy for how the effect period should be reset (or not) while stacking
- L2425 _public member_ `EGameplayEffectStackingExpirationPolicy StackExpirationPolicy;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stacking, meta = (EditConditionHides, EditCondition = "StackingType != EGameplayEffectStackingType::None"))` — Policy for how to handle duration expiring on this gameplay effect
- L2429 _public member_ `bool bFactorInStackCount;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stacking, meta = (EditConditionHides, EditCondition = "StackingType != EGameplayEffectStackingType::None"))` — If true, the calculation will include the stack count for Modifier Magnitudes
- L2432 _public prototype_ `EGameplayEffectStackingType GetStackingType() const;` — return the stacking type defined from the data asset
- L2436 _public prototype_ `void SetStackingType(EGameplayEffectStackingType InType);` — Set stacking type
- L2446 _public member_ `TArray<FGameplayAbilitySpecDef> GrantedAbilities;` — `UE_DEPRECATED(5.3, "GrantedAbilities are deprecated in favor of AbilitiesGameplayEffectComponent")` — `UPROPERTY(BlueprintReadOnly, Category = "Granted Abilities")` — Policy for what abilities this GE will grant.
- L2455 _public member_ `FGameplayTagContainer CachedAssetTags;` — Cached copy of all the tags this GE has. Data populated during PostLoad.
- L2458 _public member_ `FGameplayTagContainer CachedGrantedTags;` — Cached copy of all the tags this GE grants to its target. Data populated during PostLoad.
- L2461 _public member_ `FGameplayTagContainer CachedBlockedAbilityTags;` — Cached copy of all the tags this GE applies to its target to block Gameplay Abilities. Data populated during PostLoad.
- L2466 _protected member_ `TArray<TObjectPtr<UGameplayEffectComponent>> GEComponents;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = "GameplayEffect", meta = (DisplayName = "Components", TitleProperty = EditorFriendlyName, ShowOnlyInnerProperties, DisplayPriority = 0))` — These Gameplay Effect Components define how this Gameplay Effect behaves when applied
- L2471 _protected member_ `mutable FText EditorStatusText;` — `UPROPERTY(VisibleAnywhere, Transient, Category = Status)` — Allow us to show the Status of the class (valid configurations or invalid configurations) while configuring in the Editor
- L2476 _private member_ `FGameplayEffectVersion DataVersion;` — `UPROPERTY()` — The saved version of this package (the value is not inherited from its parents). @see SetVersion and GetVersion.
- L2481 _function_ `template<typename GEComponentClass> const GEComponentClass* UGameplayEffect::FindComponent() const`
- L2497 _function_ `template<typename GEComponentClass> GEComponentClass& UGameplayEffect::AddComponent()`
- L2509 _function_ `template<typename GEComponentClass> GEComponentClass& UGameplayEffect::FindOrAddComponent()`

#### Free symbols / members of external scopes

- L27 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L400 _enumerator_ `WithSerializer = true` (scope `TStructOpsTypeTraits::__anonf4a83ee50103`)
- L1466 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FActiveGameplayEffectQueryCustomMatch, const FActiveGameplayEffect&);`
- L1466 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(bool, FActiveGameplayEffectQueryCustomMatch, const FActiveGameplayEffect&);`
- L1467 _delegate_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FActiveGameplayEffectQueryCustomMatch_Dynamic, FActiveGameplayEffect, Effect, bool&, bMatches);`
- L1467 _prototype_ `DECLARE_DYNAMIC_DELEGATE_TwoParams(FActiveGameplayEffectQueryCustomMatch_Dynamic, FActiveGameplayEffect, Effect, bool&, bMatches);`
- L2021 _function_ `inline friend Iterator begin(FActiveGameplayEffectsContainer* Container)`
- L2022 _function_ `inline friend Iterator end(FActiveGameplayEffectsContainer* Container)`
- L2024 _function_ `inline friend ConstIterator begin(const FActiveGameplayEffectsContainer* Container)`
- L2025 _function_ `inline friend ConstIterator end(const FActiveGameplayEffectsContainer* Container)`
- L2033 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anonf4a83ee50203`)
- L2034 _enumerator_ `WithCopy = false` (scope `TStructOpsTypeTraits::__anonf4a83ee50203`)
- L2056 _macro_ `#define GAMEPLAYEFFECT_SCOPE_LOCK() FScopedActiveGameplayEffectLock ActiveScopeLock(*this);`
- L2093 _enumerator_ `WithIdentical = true` (scope `TStructOpsTypeTraits::__anonf4a83ee50303`)
- L2094 _enumerator_ `WithStructuredSerializer = true` (scope `TStructOpsTypeTraits::__anonf4a83ee50303`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectAggregator.h` (Public)


#### struct `FAggregatorEvaluateParameters`  
`struct FAggregatorEvaluateParameters`  
_L15-38_
- desc: Data that is used in aggregator evaluation that is passed from the caller/game code
- L17 _public function_ `FAggregatorEvaluateParameters() : SourceTags(nullptr) , TargetTags(nullptr) , IncludePredictiveMods(false)`
- L24 _public member_ `const FGameplayTagContainer* SourceTags;` — This tag container is expected to hold all aggregrated tags of the gameplay effect's source: from ability system component, effect spec, ability, calculation specific tags, etc.
- L26 _public member_ `const FGameplayTagContainer* TargetTags;` — This tag container is expected to hold all aggregrated tags of the gameplay effect's target: from ability system component, effect spec, ability, calculation specific tags, etc.
- L29 _public member_ `TArray<FActiveGameplayEffectHandle> IgnoreHandles;` — Any mods with one of these handles will be ignored during evaluation
- L32 _public member_ `FGameplayTagContainer AppliedSourceTagFilter;` — If any tags are specified in the filter, a mod's owning active gameplay effect's source tags must match ALL of them in order for the mod to count during evaluation
- L35 _public member_ `FGameplayTagContainer AppliedTargetTagFilter;` — If any tags are specified in the filter, a mod's owning active gameplay effect's target tags must match ALL of them in order for the mod to count during evaluation
- L37 _public member_ `bool IncludePredictiveMods;`

#### struct `FAggregatorEvaluateMetaData`  
`struct FAggregatorEvaluateMetaData`  
_L41-53_
- desc: Data that is used in aggregator evaluation that is intrinsic to the aggregator itself. Not passed in from the game code (though maybe originally setup once by the game code)
- L43 _public typedef_ `typedef TFunction< void(const FAggregatorEvaluateParameters&, const FAggregator*) > FCustomQualifiesFunc;`
- L45 _public function_ `FAggregatorEvaluateMetaData(FCustomQualifiesFunc InQualifierFunc) : CustomQualifiesFunc(InQualifierFunc)`
- L52 _public member_ `FCustomQualifiesFunc CustomQualifiesFunc;`

#### struct `FAggregatorMod`  
`struct FAggregatorMod`  
_L55-78_
- L57 _public member_ `const FGameplayTagRequirements* SourceTagReqs;`
- L58 _public member_ `const FGameplayTagRequirements* TargetTagReqs;`
- L60 _public member_ `float EvaluatedMagnitude;` — Magnitude this mod was last evaluated at
- L61 _public member_ `float StackCount;`
- L63 _public member_ `FActiveGameplayEffectHandle ActiveHandle;` — Handle of the active GameplayEffect we are tied to (if any)
- L64 _public member_ `bool IsPredicted;`
- L66 _public function_ `bool Qualifies() const`
- L69 _public prototype_ `void UpdateQualifies(const FAggregatorEvaluateParameters& Parameters) const;` — Called to update the Qualifies bool
- L72 _public function_ `void SetExplicitQualifies(bool NewQualifies) const` — Intended to be used by FAggregatorEvaluateMetaData::CustomQualifiesFunc to toggle qualifications of mods
- L77 _private member_ `mutable bool IsQualified;` — This bool is updated by UpdateQualifiees. Think of it as a transient bool, we make a full pass on all qualifiers first (::UpdateQualifies) then while evaluating we check what the bool was set to (::Qualifies)

#### struct `FAggregatorModInfo`  
`struct FAggregatorModInfo`  
_L80-85_
- L82 _public member_ `EGameplayModEvaluationChannel Channel;`
- L83 _public member_ `EGameplayModOp::Type Op;`
- L84 _public member_ `const FAggregatorMod* Mod;`

#### struct `FAggregatorModChannel`  
`struct FAggregatorModChannel`  
_L88-178_
- desc: Struct representing an individual aggregation channel/depth. Contains mods of all mod op types.
- L98 _public prototype_ `float EvaluateWithBase(float InlineBaseValue, const FAggregatorEvaluateParameters& Parameters) const;` — Evaluates the channel's mods with the specified base value and evaluation parameters @param InlineBaseValue	Base value to use for the evaluation @param Parameters		Additional evaluation parameters to use @return Evaluated value based upon the channel's mods
- L113 _public prototype_ `bool ReverseEvaluate(float FinalValue, const FAggregatorEvaluateParameters& Parameters, OUT float& ComputedValue) const;` — Evaluates a final value in reverse, attempting to determine a base value from the modifiers within the channel. Certain conditions (such as the use of override mods) can prevent this from computing correctly, at which point false will be returned. This is predominantly used for filling in base values on clients from replication for float-based attributes. @note This will be deprecated/removed soon with the transition to struct-based attributes. @param FinalValue	Final value to reverse evaluate @param Parameters	Evaluation parameters to use for the reverse evaluation @param ComputedValue	[OUT] Reverse evaluated base value @return True if the reverse evaluation was successful, false if it was not
- L125 _public prototype_ `void AddMod(float EvaluatedMagnitude, TEnumAsByte<EGameplayModOp::Type> ModOp, const FGameplayTagRequirements* SourceTagReqs, const FGameplayTagRequirements* TargetTagReqs, bool bIsPredicted, const FActiveGameplayEffectHandle& ActiveHandle);` — Add a modifier to the channel @param EvaluatedMagnitude	Magnitude of the modifier @param ModOp					Operation of the modifier @param SourceTagReqs			Source tag requirements of the modifier @param TargetTagReqs			Target tag requirements of the modifier @param bIsPredicted			Whether the mod is predicted or not @param ActiveHandle			Handle of the active gameplay effect that's applying the mod
- L132 _public prototype_ `void RemoveModsWithActiveHandle(const FActiveGameplayEffectHandle& Handle);` — Remove all mods from the channel that match the specified gameplay effect handle @param Handle	Handle to use for removal
- L139 _public prototype_ `void AddModsFrom(const FAggregatorModChannel& Other);` — Add the specified channel's mods into this channel @param Other	Other channel to add mods from
- L142 _public prototype_ `void UpdateQualifiesOnAllMods(const FAggregatorEvaluateParameters& Parameters) const;` — runs UpdateQualifies on all mods
- L145 _public prototype_ `void ForEachMod(FAggregatorModInfo& Info, TFunction<void (const FAggregatorModInfo&) > Func) const;` — Helper function for iterating through all mods within a channel
- L153 _public prototype_ `void GetAllAggregatorMods(EGameplayModEvaluationChannel Channel, OUT TMap<EGameplayModEvaluationChannel, const TArray<FAggregatorMod>*>& OutMods) const;` — Populate a mapping of channel to corresponding mods @param Channel	Enum channel associated with this channel @param OutMods	Mapping of channel enum to mods
- L161 _public prototype_ `void OnActiveEffectDependenciesSwapped(const TMap<FActiveGameplayEffectHandle, FActiveGameplayEffectHandle>& SwappedDependencies);` — Called when the mod channel's gameplay effect dependencies have potentially been swapped out for new ones, like when GE arrays are cloned. Updates mod handles appropriately. @param SwappedDependencies	Mapping of old gameplay effect handles to new replacements
- L172 _public prototype_ `static float SumMods(const TArray<FAggregatorMod>& InMods, float Bias, const FAggregatorEvaluateParameters& Parameters);` — Helper function to sum all of the mods in the specified array, using the specified modifier bias and evaluation parameters @param InMods		Mods to sum @param Bias			Bias to apply to modifier magnitudes @param Parameters	Evaluation parameters @return Summed value of mods
- L177 _private member_ `TArray<FAggregatorMod> Mods[EGameplayModOp::Max];` — Collection of modifers within the channel, organized by modifier operation

#### struct `FAggregatorModChannelContainer`  
`struct FAggregatorModChannelContainer`  
_L181-276_
- desc: Struct representing a container of modifier channels
- L190 _public prototype_ `FAggregatorModChannel& FindOrAddModChannel(EGameplayModEvaluationChannel Channel);` — Find or add a modifier channel for the specified enum value @param Channel	Channel to find or add a modifier channel for @return Modifier channel for the specified enum value
- L193 _public prototype_ `int32 GetNumChannels() const;` — Simple accessor to the current number of modifier channels active
- L207 _public prototype_ `float EvaluateWithBase(float InlineBaseValue, const FAggregatorEvaluateParameters& Parameters) const;` — Evaluates the result of the specified base value run through each existing evaluation channel's modifiers in numeric order with the specified evaluation parameters. The result of the evaluation of an individual channel acts as the new base value to the channel that follows it until all channels have been evaluated. EXAMPLE: Base Value: 2, Channel 0 has a +2 Additive Mod, Channel 1 is provided a base value of 4 to run through its modifiers @param InlineBaseValue	Initial base value to use in the first evaluation channel @param Parameters		Additional evaluation parameters @return Result of the specified base value run through each modifier in each evaluation channel in numeric order
- L219 _public prototype_ `float EvaluateWithBaseToChannel(float InlineBaseValue, const FAggregatorEvaluateParameters& Parameters, EGameplayModEvaluationChannel FinalChannel) const;` — Similar to EvaluateWithBase (see comment there for details), but terminates early after evaluating the specified final channel instead of continuing through every possible channel @param InlineBaseValue	Initial base value to use in the first evaluation channel @param Parameters		Additional evaluation parameters @param FinalChannel		Channel to terminate evaluation with (inclusive) @return Result of the specified base value run through each modifier in each evaluation channel in numeric order
- L235 _public prototype_ `float ReverseEvaluate(float FinalValue, const FAggregatorEvaluateParameters& Parameters) const;` — Evaluates a final value in reverse, attempting to determine a base value from the modifiers within all of the channels. The operation proceeds through all channels in reverse order, with the result of the evaluation of an individual channel used as the new final value to the channel that precedes it numerically. If any channel has a condition that prevents it from computing correctly (such as an override mod), this function just returns the original final value. This is predominantly used for filling in base values on clients from replication for float-based attributes. @note This will be deprecated/removed soon with the transition to struct-based attributes. @param FinalValue	Final value to reverse evaluate @param Parameters	Evaluation parameters to use for the reverse evaluation @return If possible, the base value from the reverse evaluation. If not possible, the original final value is returned.
- L238 _public prototype_ `void EvaluateQualificationForAllMods(const FAggregatorEvaluateParameters& Parameters) const;` — Calls ::UpdateQualifies on each mod
- L245 _public prototype_ `void RemoveAggregatorMod(const FActiveGameplayEffectHandle& ActiveHandle);` — Removes any mods from every channel matching the specified handle @param ActiveHandle	Handle to use for removal
- L252 _public prototype_ `void AddModsFrom(const FAggregatorModChannelContainer& Other);` — Adds the mods from specified container to this one @param Other	Container to add mods from
- L255 _public prototype_ `void ForEachMod( TFunction<void (const FAggregatorModInfo&) > ) const;` — Helper function for iterating through all mods within the channel container
- L262 _public prototype_ `void GetAllAggregatorMods(OUT TMap<EGameplayModEvaluationChannel, const TArray<FAggregatorMod>*>& OutMods) const;` — Populate a mapping of channel to corresponding mods for debugging purposes @param OutMods	Mapping of channel enum to mods
- L270 _public prototype_ `void OnActiveEffectDependenciesSwapped(const TMap<FActiveGameplayEffectHandle, FActiveGameplayEffectHandle>& SwappedDependencies);` — Called when the container's gameplay effect dependencies have potentially been swapped out for new ones, like when GE arrays are cloned. Updates each channel appropriately. @param SwappedDependencies	Mapping of old gameplay effect handles to new replacements
- L275 _private member_ `TMap<EGameplayModEvaluationChannel, FAggregatorModChannel> ModChannelsMap;` — Mapping of evaluation channel enumeration to actual struct representation

#### struct `FAggregator`  
`struct FAggregator : public TSharedFromThis<FAggregator>`  
_L278-376_
- inherits: `TSharedFromThis<FAggregator>`
- L280 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAggregatorDirty, FAggregator*);`
- L282 _public function_ `FAggregator(float InBaseValue=0.f) : EvaluationMetaData(nullptr) , NetUpdateID(0) , BaseValue(InBaseValue) , BroadcastingDirtyCount(0)`
- L289 _public prototype_ `~FAggregator();`
- L292 _public prototype_ `float GetBaseValue() const;` — Simple accessor to base value
- L293 _public prototype_ `void SetBaseValue(float NewBaseValue, bool BroadcastDirtyEvent = true);`
- L295 _public prototype_ `void ExecModOnBaseValue(TEnumAsByte<EGameplayModOp::Type> ModifierOp, float EvaluatedMagnitude);`
- L296 _public prototype_ `static float StaticExecModOnBaseValue(float BaseValue, TEnumAsByte<EGameplayModOp::Type> ModifierOp, float EvaluatedMagnitude);`
- L298 _public prototype_ `void AddAggregatorMod(float EvaluatedData, TEnumAsByte<EGameplayModOp::Type> ModifierOp, EGameplayModEvaluationChannel ModifierChannel, const FGameplayTagRequirements* SourceTagReqs, const FGameplayTagRequirements* TargetTagReqs, bool IsPredicted, FActiveGameplayEffectHandle ActiveHandle = FActiveGameplayEffectHandle() );`
- L301 _public prototype_ `void RemoveAggregatorMod(FActiveGameplayEffectHandle ActiveHandle);` — Removes all mods for the passed in handle and marks this as dirty to recalculate the aggregator
- L304 _public prototype_ `void UpdateAggregatorMod(FActiveGameplayEffectHandle ActiveHandle, const FGameplayAttribute& Attribute, const FGameplayEffectSpec& Spec, bool bWasLocallyGenerated, FActiveGameplayEffectHandle InHandle);` — Updates the aggregators for the past in handle, this will handle it so the UAttributeSets stats only get one update for the delta change
- L307 _public prototype_ `float Evaluate(const FAggregatorEvaluateParameters& Parameters) const;` — Evaluates the Aggregator with the internal base value and given parameters
- L310 _public prototype_ `float EvaluateToChannel(const FAggregatorEvaluateParameters& Parameters, EGameplayModEvaluationChannel FinalChannel) const;` — Evaluates the aggregator with the internal base value and given parameters, up to the specified evaluation channel (inclusive)
- L313 _public prototype_ `float ReverseEvaluate(float FinalValue, const FAggregatorEvaluateParameters& Parameters) const;` — Works backwards to calculate the base value. Used on clients for doing predictive modifiers
- L316 _public prototype_ `float EvaluateWithBase(float InlineBaseValue, const FAggregatorEvaluateParameters& Parameters) const;` — Evaluates the Aggregator with an arbitrary base value
- L319 _public prototype_ `float EvaluateBonus(const FAggregatorEvaluateParameters& Parameters) const;` — Evaluates the Aggregator to compute its "bonus" (final - base) value
- L322 _public prototype_ `float EvaluateContribution(const FAggregatorEvaluateParameters& Parameters, FActiveGameplayEffectHandle ActiveHandle) const;` — Evaluates the contribution from the GE associated with ActiveHandle
- L325 _public prototype_ `void EvaluateQualificationForAllMods(const FAggregatorEvaluateParameters& Parameters) const;` — Calls ::UpdateQualifies on each mod. Useful for when you need to manually inspect aggregators
- L327 _public prototype_ `void TakeSnapshotOf(const FAggregator& AggToSnapshot);`
- L329 _public member_ `FOnAggregatorDirty OnDirty;`
- L330 _public member_ `FOnAggregatorDirty OnDirtyRecursive;` — Called in case where we are in a recursive dirtying chain. This will force the backing uproperty to update but not call the game code delegates
- L332 _public prototype_ `void AddModsFrom(const FAggregator& SourceAggregator);`
- L334 _public prototype_ `void AddDependent(FActiveGameplayEffectHandle Handle);`
- L335 _public prototype_ `void RemoveDependent(FActiveGameplayEffectHandle Handle);`
- L342 _public prototype_ `void GetAllAggregatorMods(OUT TMap<EGameplayModEvaluationChannel, const TArray<FAggregatorMod>*>& OutMods) const;` — Populate a mapping of channel to corresponding mods @param OutMods	Mapping of channel enum to mods
- L350 _public prototype_ `void OnActiveEffectDependenciesSwapped(const TMap<FActiveGameplayEffectHandle, FActiveGameplayEffectHandle>& SwappedDependencies);` — Called when the aggregator's gameplay effect dependencies have potentially been swapped out for new ones, like when GE arrays are cloned. Updates the modifier channel container appropriately, as well as directly-specified dependents. @param SwappedDependencies	Mapping of old gameplay effect handles to new replacements
- L353 _public prototype_ `void ForEachMod( TFunction<void (const FAggregatorModInfo&) > ) const;` — Helper function for iterating through all mods within the aggregator
- L356 _public member_ `FAggregatorEvaluateMetaData* EvaluationMetaData;` — Custom meta data for the aggregator
- L359 _public member_ `int32 NetUpdateID;` — NetworkID that we had our last update from. Will only be set on clients and is only used to ensure we don't recompute server base value twice.
- L363 _private prototype_ `void BroadcastOnDirty();`
- L365 _private member_ `float BaseValue;`
- L366 _private member_ `FAggregatorModChannelContainer ModChannels;`
- L369 _private member_ `TArray<FActiveGameplayEffectHandle> Dependents;` — ActiveGE handles that we need to notify if we change. NOT copied over during snapshots.
- L370 _private member_ `int32 BroadcastingDirtyCount;`

#### struct `FAggregatorRef`  
`struct FAggregatorRef`  
_L378-388_
- L380 _public function_ `FAggregatorRef()`
- L381 _public function_ `FAggregatorRef(FAggregator* InData) : Data(InData)`
- L383 _public function_ `FAggregator* Get() const`
- L385 _public member_ `TSharedPtr<FAggregator> Data;`
- L387 _public prototype_ `void TakeSnapshotOf(const FAggregatorRef& RefToSnapshot);`

#### struct `FScopedAggregatorOnDirtyBatch`  
`struct FScopedAggregatorOnDirtyBatch`  
_L397-413_
- desc: Allows us to batch all aggregator OnDirty calls within a scope. That is, ALL OnDirty() callbacks are delayed until FScopedAggregatorOnDirtyBatch goes out of scope. The only catch is that we store raw FAggregator*. This should only be used in scopes where aggreagtors are not deleted. There is currently no place that does. If we find to, we could add additional safety checks.
- L399 _public prototype_ `FScopedAggregatorOnDirtyBatch();`
- L400 _public prototype_ `~FScopedAggregatorOnDirtyBatch();`
- L402 _public prototype_ `static void BeginLock();`
- L403 _public prototype_ `static void EndLock();`
- L405 _public prototype_ `static void BeginNetReceiveLock();`
- L406 _public prototype_ `static void EndNetReceiveLock();`
- L408 _public member_ `static int32 GlobalBatchCount;`
- L409 _public member_ `static TSet<FAggregator*> DirtyAggregators;`
- L411 _public member_ `static bool GlobalFromNetworkUpdate;`
- L412 _public member_ `static int32 NetUpdateID;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L280 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnAggregatorDirty, FAggregator*);`
- L415 _macro_ `#define AGGREGATOR_BATCH_SCOPE() FScopedAggregatorOnDirtyBatch AggregatorOnDirtyBatcher;`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectAggregatorLibrary.h` (Public)


#### struct `FAggregatorEvaluateMetaDataLibrary`  
`struct FAggregatorEvaluateMetaDataLibrary`  
_L9-12_
- L11 _public member_ `static FAggregatorEvaluateMetaData MostNegativeMod_AllPositiveMods;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectAttributeCaptureDefinition.h` (Public)


#### enum `EGameplayEffectAttributeCaptureSource`  
`enum class EGameplayEffectAttributeCaptureSource : uint8`  
_L12-18_
- reflection: `UENUM()`
- desc: Enumeration for options of where to capture gameplay attributes from for gameplay effects.
- L15 _public enumerator_ `Source` — Source (caster) of the gameplay effect.
- L17 _public enumerator_ `Target` — Target (recipient) of the gameplay effect.

#### struct `FGameplayEffectAttributeCaptureDefinition`  
`struct FGameplayEffectAttributeCaptureDefinition`  
_L23-70_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct defining gameplay attribute capture options for gameplay effects
- L27 _public function_ `FGameplayEffectAttributeCaptureDefinition()`
- L33 _public function_ `FGameplayEffectAttributeCaptureDefinition(FGameplayAttribute InAttribute, EGameplayEffectAttributeCaptureSource InSource, bool InSnapshot) : AttributeToCapture(MoveTemp(InAttribute)), AttributeSource(InSource), bSnapshot(InSnapshot)`
- L41 _public member_ `FGameplayAttribute AttributeToCapture;` — `UPROPERTY(EditDefaultsOnly, Category=Capture)` — Gameplay attribute to capture
- L45 _public member_ `EGameplayEffectAttributeCaptureSource AttributeSource;` — `UPROPERTY(EditDefaultsOnly, Category=Capture)` — Source of the gameplay attribute
- L49 _public member_ `bool bSnapshot;` — `UPROPERTY(EditDefaultsOnly, Category=Capture)` — Whether the attribute should be snapshotted or not
- L52 _public prototype_ `bool operator==(const FGameplayEffectAttributeCaptureDefinition& Other) const;` — Equality/Inequality operators
- L53 _public prototype_ `bool operator!=(const FGameplayEffectAttributeCaptureDefinition& Other) const;`
- L69 _public prototype_ `FString ToSimpleString() const;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L60 _function_ `friend uint32 GetTypeHash(const FGameplayEffectAttributeCaptureDefinition& CaptureDef)` — Get type hash for the capture definition; Implemented to allow usage in TMap @param CaptureDef Capture definition to get the type hash of

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectCalculation.h` (Public)


#### class `UGameplayEffectCalculation`  
`class UGameplayEffectCalculation : public UObject`  
_L15-29_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Abstract base for specialized gameplay effect calculations; Capable of specifing attribute captures
- L22 _public prototype_ `virtual const TArray<FGameplayEffectAttributeCaptureDefinition>& GetAttributeCaptureDefinitions() const;` — Simple accessor to capture definitions for attributes
- L28 _protected member_ `TArray<FGameplayEffectAttributeCaptureDefinition> RelevantAttributesToCapture;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Attributes)` — Attributes to capture that are relevant to the calculation

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponent.h` (Public)


#### class `UGameplayEffectComponent`  
`class UGameplayEffectComponent : public UObject`  
_L32-87_
- reflection: `UCLASS(Abstract, Const, DefaultToInstanced, EditInlineNew, CollapseCategories, Within=GameplayEffect, MinimalAPI)`
- inherits: `UObject`
- desc: Gameplay Effect Component (aka GEComponent) GEComponents are what define how a GameplayEffect behaves.  Introduced in UE 5.3, there are very few calls from UGameplayEffect to UGameplayEffectComponent by design. Instead of providing a larger API for all desired functionality, the implementer of a GEComponent must read the GE flow carefully and register desired callbacks to achieve the desired results.  This effectively limits the implementation of GEComponents to native code for the time being. GEComponents live Within a GameplayEffect (which is typically a data-only blueprint asset).  Thus, like GEs, only one GEComponent exists for all applied instances. One of the unintuitive caveats of this is that GEComponent should not contain any runtime manipulated/instanced data (e.g. stored state per execution). One must take careful consideration about where to store any data (and thus when it can be evaluated).  The early implementations typically work around this by storing small amounts of runtime data on the desired callbacks (e.g. by binding extra parameters on the delegate).  This may explain why some functionality is still in UGameplayEffect rather than a UGameplayEffectComponent.  Future implementations may need extra data stored on the FGameplayEffectSpec (i.e. Gameplay Effect Spec Components). @see GameplayEffect.h for further notes, especially on the terminology used (Added vs. Executed vs. Apply).
- L38 _public prototype_ `UGameplayEffectComponent();` — Constructor
- L41 _public prototype_ `UGameplayEffect* GetOwner() const;` — Returns the GameplayEffect that owns this Component (the Outer)
- L47 _public function_ `virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const` — Can the GameplayEffectSpec apply to the passed-in ASC?  All Components of the GE must return true, or a single one can return false to prohibit the application. Note: Application and Inhibition are two separate things.  If a GE can apply, we then either Add it (if it has duration/prediction) or Execute it (if it's instant).
- L54 _public function_ `virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const` — Called when a Gameplay Effect is Added to the ActiveGameplayEffectsContainer.  GE's are added to that container when they have duration (or are predicting locally). Note: This also occurs as a result of replication (e.g. when the server replicates a GE to the owning client -- including the 'duplicate' GE after a prediction). Return if the effect should remain active, or false to inhibit.  Note: Inhibit does not remove the effect (it remains added but dormant, waiting to uninhibit).
- L60 _public function_ `virtual void OnGameplayEffectExecuted(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const` — Called when a Gameplay Effect is executed.  GE's can only Execute on ROLE_Authority.  GE's only Execute when they're applying an instant effect (otherwise they're added to the ActiveGameplayEffectsContainer). Note: Periodic effects Execute every period (and are also added to ActiveGameplayEffectsContainer).  One may think of this as periodically executing an instant effect (and thus can only happen on the server).
- L66 _public function_ `virtual void OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const` — Called when a Gameplay Effect is initially applied, or stacked.  GE's are 'applied' in both cases of duration or instant execution.  This call does not happen periodically, nor through replication. One should favor this function over OnActiveGameplayEffectAdded & OnGameplayEffectExecuted (but all multiple may be used depending on the case).
- L71 _public function_ `virtual void OnGameplayEffectChanged()` — Let us know that the owning GameplayEffect has been modified, thus apply an asset-related changes to the owning GameplayEffect (e.g. any of its fields)
- L78 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Allow each Gameplay Effect Component to validate its own data.  Any warnings/errors will immediately show up in the Gameplay Effect when in Editor. The default implementation ensures we only have a single type of any given class.  Override this function to change that functionality and use Super::Super::IsDataValid if needed.
- L85 _protected member_ `FString EditorFriendlyName;` — `UPROPERTY(VisibleDefaultsOnly, Transient, Category=AlwaysHidden, Meta=(EditCondition=False, EditConditionHides))` — Friendly name for displaying in the Editor's Gameplay Effect Component Index (@see UGameplayEffect::GEComponents). We set EditCondition False here so it doesn't show up otherwise.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L91 _function_ `template<typename GEComponentClass, typename LateBindGameplayEffect = UGameplayEffect>` — Find the same component in the parent of the passed-in GameplayEffect.  Useful for having a child component inherit properties from the parent (e.g. inherited tags).

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/AbilitiesGameplayEffectComponent.h` (Public)


#### struct `FGameplayAbilitySpecConfig`  
`struct FGameplayAbilitySpecConfig`  
_L13-32_
- reflection: `USTRUCT()`
- desc: Options on how to configure a GameplayAbilitySpec to grant an Actor
- L19 _public member_ `TSubclassOf<UGameplayAbility> Ability;` — `UPROPERTY(EditDefaultsOnly, Category = "Ability Definition")` — What ability to grant
- L27 _public member_ `int32 InputID = INDEX_NONE;` — `UPROPERTY(EditDefaultsOnly, Category = "Ability Definition")` — Input ID to bind this ability to
- L31 _public member_ `EGameplayEffectGrantedAbilityRemovePolicy RemovalPolicy = EGameplayEffectGrantedAbilityRemovePolicy::CancelAbilityImmediately;` — `UPROPERTY(EditDefaultsOnly, Category = "Ability Definition")` — What will remove this ability later

#### class `UAbilitiesGameplayEffectComponent`  
`class UAbilitiesGameplayEffectComponent : public UGameplayEffectComponent`  
_L38-83_
- reflection: `UCLASS(DisplayName="Grant Gameplay Abilities", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Grants additional Gameplay Abilities to the Target of a Gameplay Effect while active
- L46 _public prototype_ `UAbilitiesGameplayEffectComponent();` — Constructor
- L49 _public prototype_ `virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const override;` — Register for the appropriate events when we're applied
- L52 _public prototype_ `void AddGrantedAbilityConfig(const FGameplayAbilitySpecConfig& Config);` — Adds an entry for granting Gameplay Abilities
- L56 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Warn on misconfigured Gameplay Effect
- L61 _protected prototype_ `virtual void OnInhibitionChanged(FActiveGameplayEffectHandle ActiveGEHandle, bool bIsInhibited) const;` — This allows us to be notified when the owning GameplayEffect has had its inhibition changed (which can happen on the initial application).
- L64 _protected function_ `virtual void GrantAbilities(FActiveGameplayEffectHandle ActiveGEHandle) const` — `UE_DEPRECATED(5.8, "Use the version that takes an FActiveGameplayEffect (because they may be PendingRemove by now, so the Handle won't resolve)")`
- L67 _protected function_ `virtual void RemoveAbilities(FActiveGameplayEffectHandle ActiveGEHandle) const` — `UE_DEPRECATED(5.8, "Use the version that takes an FActiveGameplayEffect (because they may be PendingRemove by now, so the Handle won't resolve)")`
- L70 _protected prototype_ `virtual void GrantAbilities(UAbilitySystemComponent& OwningASC, const FActiveGameplayEffect& ActiveGE) const;` — We should grant the configured Gameplay Abilities
- L73 _protected prototype_ `virtual void RemoveAbilities(UAbilitySystemComponent& OwningASC, const FActiveGameplayEffect& ActiveGE) const;` — We should remove the configured Gameplay Abilities
- L77 _private prototype_ `void OnActiveGameplayEffectRemoved(const FGameplayEffectRemovalInfo& RemovalInfo) const;` — We must undo all effects when removed
- L82 _protected member_ `TArray<FGameplayAbilitySpecConfig> GrantAbilityConfigs;` — `UPROPERTY(EditDefaultsOnly, Category = GrantAbilities)` — Abilities to Grant to the Target while this Gameplay Effect is active

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/AdditionalEffectsGameplayEffectComponent.h` (Public)


#### class `UAdditionalEffectsGameplayEffectComponent`  
`class UAdditionalEffectsGameplayEffectComponent : public UGameplayEffectComponent`  
_L13-65_
- reflection: `UCLASS(CollapseCategories, DisplayName="Apply Additional Effects", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Add additional Gameplay Effects that attempt to activate under certain conditions (or no conditions)
- L21 _public prototype_ `virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& GEContainer, FActiveGameplayEffect& ActiveGE) const override;` — Called when a Gameplay Effect is Added to the ActiveGameplayEffectsContainer.  We register a callback to execute the OnComplete Gameplay Effects.
- L26 _public prototype_ `virtual void OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const override;` — Called when a Gameplay Effect is applied.  This executes the OnApplication Gameplay Effects.
- L32 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — There are some fields that are incompatible with one another, so let's catch them during configuration phase.
- L40 _protected prototype_ `void OnActiveGameplayEffectRemoved(const FGameplayEffectRemovalInfo& RemovalInfo, FActiveGameplayEffectsContainer* ActiveGEContainer) const;` — Whenever the ActiveGE gets removed, we want to apply the configured OnComplete GameplayEffects
- L48 _public member_ `bool bOnApplicationCopyDataFromOriginalSpec = false;` — `UPROPERTY(EditDefaultsOnly, Category = OnApplication)` — This will copy all of the data (e.g. SetByCallerMagnitudes) from the GESpec that Applied this GameplayEffect to the new OnApplicationGameplayEffect Specs. One would think this is normally desirable (and how OnComplete works by default), but we default to false here for backwards compatability.
- L52 _public member_ `TArray<FConditionalGameplayEffect> OnApplicationGameplayEffects;` — `UPROPERTY(EditDefaultsOnly, Category = OnApplication)` — Other gameplay effects that will be applied to the target of this effect if the owning effect applies
- L56 _public member_ `TArray<TSubclassOf<UGameplayEffect>> OnCompleteAlways;` — `UPROPERTY(EditDefaultsOnly, Category = OnComplete)` — Effects to apply when this effect completes, regardless of how it ends
- L60 _public member_ `TArray<TSubclassOf<UGameplayEffect>> OnCompleteNormal;` — `UPROPERTY(EditDefaultsOnly, Category = OnComplete)` — Effects to apply when this effect expires naturally via its duration
- L64 _public member_ `TArray<TSubclassOf<UGameplayEffect>> OnCompletePrematurely;` — `UPROPERTY(EditDefaultsOnly, Category = OnComplete)` — Effects to apply when this effect is made to expire prematurely (e.g. via a forced removal, clear tags, etc.)

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/AssetTagsGameplayEffectComponent.h` (Public)


#### class `UAssetTagsGameplayEffectComponent`  
`class UAssetTagsGameplayEffectComponent : public UGameplayEffectComponent`  
_L13-51_
- reflection: `UCLASS(DisplayName="Tags This Effect Has (Asset Tags)", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: These are tags that the Gameplay Effect Asset itself 'has' (owns). These do _not_ transfer to any Actors
- L19 _public prototype_ `virtual void PostInitProperties() override;` — Setup a better EditorFriendlyName and do some initialization
- L22 _public prototype_ `virtual void OnGameplayEffectChanged() override;` — Needed to properly apply FInheritedTagContainer properties
- L25 _public function_ `const FInheritedTagContainer& GetConfiguredAssetTagChanges() const` — Gets the Asset Tags inherited tag structure (as configured)
- L28 _public prototype_ `void SetAndApplyAssetTagChanges(const FInheritedTagContainer& TagContainerMods);` — Applies the Asset Tags to the GameplayEffect (and saves those changes)
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Needed to properly update FInheritedTagContainer properties
- L36 _private function_ `static const FName& GetInheritableAssetTagsName()` — Get a cached version of the FProperty Name for PostEditChangeProperty
- L45 _private prototype_ `void ApplyAssetTagChanges() const;` — Applies the Asset Tags to the GameplayEffect
- L50 _private member_ `FInheritedTagContainer InheritableAssetTags;` — `UPROPERTY(EditDefaultsOnly, Category = Tags, meta = (DisplayName = "AssetTags", Categories = "OwnedTagsCategory"))` — The GameplayEffect's Tags: tags the the GE *has* and DOES NOT give to the actor.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/BlockAbilityTagsGameplayEffectComponent.h` (Public)


#### class `UBlockAbilityTagsGameplayEffectComponent`  
`class UBlockAbilityTagsGameplayEffectComponent : public UGameplayEffectComponent`  
_L13-54_
- reflection: `UCLASS(DisplayName="Block Abilities with Tags", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Handles blocking the activation of Gameplay Abilities based on Gameplay Tags for the Target actor of the owner Gameplay Effect
- L19 _public prototype_ `virtual void PostInitProperties() override;` — Setup an EditorFriendlyName and do some initialization
- L22 _public prototype_ `virtual void OnGameplayEffectChanged() override;` — Needed to properly apply FInheritedTagContainer properties
- L25 _public function_ `const FInheritedTagContainer& GetConfiguredBlockedAbilityTagChanges() const` — Gets the Blocked Ability Tags inherited tag structure (as configured)
- L28 _public prototype_ `void SetAndApplyBlockedAbilityTagChanges(const FInheritedTagContainer& TagContainerMods);` — Applies the Blocked Ability Tags to the GameplayEffect (and saves those changes) so that when the Gameplay Effect is applied, these Blocking Tags are then applied to the Target Actor
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Needed to properly update FInheritedTagContainer properties
- L35 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Validate incompatible configurations
- L39 _private function_ `static const FName& GetInheritableBlockedAbilityTagsContainerPropertyName()` — Get a cached version of the FProperty Name for PostEditChangeProperty
- L48 _private prototype_ `void ApplyBlockedAbilityTagChanges() const;` — Applies the Blocked Ability Tags to the owning GameplayEffect
- L53 _private member_ `FInheritedTagContainer InheritableBlockedAbilityTagsContainer;` — `UPROPERTY(EditDefaultsOnly, Category = None, meta = (DisplayName = "Block Abilities w/ Tags"))` — These tags are applied to the target actor of the Gameplay Effect.  Blocked Ability Tags prevent Gameplay Abilities with these tags from executing.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/CancelAbilityTagsGameplayEffectComponent.h` (Public)


#### enum `ECancelAbilityTagsGameplayEffectComponentMode`  
`enum class ECancelAbilityTagsGameplayEffectComponentMode : uint8`  
_L14-21_
- reflection: `UENUM()`
- desc: Enumeration representing when the ability cancellation logic for the 'CancelAbilityTagsGameplayEffectComponent' happens
- L17 _public enumerator_ `OnApplication` — Component applies cancellation logic when the owning gameplay effect is Applied. Use this if we want to cancel abilities a single time on GE application, regardless of GE duration type.
- L20 _public enumerator_ `OnExecution` — Component applies cancellation logic when the owning gameplay effect is Executed. Use this if we want to cancel abilities on each periodic GE execution.

#### class `UCancelAbilityTagsGameplayEffectComponent`  
`class UCancelAbilityTagsGameplayEffectComponent : public UGameplayEffectComponent`  
_L25-80_
- reflection: `UCLASS(DisplayName="Cancel Abilities with Tags", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Handles canceling active Gameplay Abilities based on Gameplay Tags for the Target actor of the owner Gameplay Effect
- L31 _public prototype_ `virtual void PostInitProperties() override;` — Set up an EditorFriendlyName and do some initialization
- L34 _public prototype_ `virtual void OnGameplayEffectChanged() override;` — Needed to properly apply FInheritedTagContainer properties
- L37 _public prototype_ `virtual void OnGameplayEffectExecuted(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const override;` — Needed to cancel abilities if we're canceling abilities on execution
- L40 _public prototype_ `virtual void OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const override;` — Needed to cancel abilities if we're canceling abilities on effect application
- L43 _public prototype_ `void SetAndApplyCanceledAbilityTagChanges(const FInheritedTagContainer& CanceledAbilityWithTagsMods, const FInheritedTagContainer& CanceledAbilityWithoutTagsMods);` — Applies the Canceled Ability Tags to the GameplayEffect (and saves those changes) so that when the Gameplay Effect is applied, abilities with these tags are cancelled
- L46 _private prototype_ `void CancelOwnerAbilities(const FActiveGameplayEffectsContainer& ActiveGEContainer) const;`
- L50 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Needed to properly update FInheritedTagContainer properties
- L53 _private prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Validate incompatible configurations
- L56 _private function_ `static const FName& GetInheritableCancelAbilitiesWithTagsContainerPropertyName()` — Get a cached version of the FProperty Name for PostEditChangeProperty
- L62 _private function_ `static const FName& GetInheritableCancelAbilitiesWithoutTagsContainerPropertyName()`
- L71 _private member_ `ECancelAbilityTagsGameplayEffectComponentMode ComponentMode = ECancelAbilityTagsGameplayEffectComponentMode::OnApplication;` — `UPROPERTY(EditDefaultsOnly, Category = None, meta = (DisplayName = "Mode"))` — When do we want the ability cancellation logic for this component to happen?
- L75 _private member_ `FInheritedTagContainer InheritableCancelAbilitiesWithTagsContainer;` — `UPROPERTY(EditDefaultsOnly, Category = None, meta = (DisplayName = "Cancel Abilities With Tags"))` — These tags cancel active Gameplay Abilities with these tags.
- L79 _private member_ `FInheritedTagContainer InheritableCancelAbilitiesWithoutTagsContainer;` — `UPROPERTY(EditDefaultsOnly, Category = None, meta = (DisplayName = "Cancel Abilities Without Tags"))` — These tags cancel active Gameplay Abilities without these tags.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/ChanceToApplyGameplayEffectComponent.h` (Public)


#### class `UChanceToApplyGameplayEffectComponent`  
`class UChanceToApplyGameplayEffectComponent : public UGameplayEffectComponent`  
_L14-35_
- reflection: `UCLASS(DisplayName="Chance To Apply This Effect", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Applies a probablity to the application conditions of the Gameplay Effect.
- L20 _public prototype_ `virtual void PostLoad() override;` — Warn of errors in the Editor
- L23 _public prototype_ `virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const override;` — Determine if we can apply this GameplayEffect or not
- L26 _public function_ `const FScalableFloat& GetChanceToApplyToTarget() const` — Get the configured chance to apply to target
- L29 _public prototype_ `void SetChanceToApplyToTarget(const FScalableFloat& ChanceToApplyToTarget);` — Set the chance to apply to target
- L34 _private member_ `FScalableFloat ChanceToApplyToTarget;` — `UPROPERTY(EditDefaultsOnly, Category = Application, meta = (GameplayAttribute = "True"))` — Probability that this gameplay effect will be applied to the target actor (0.0 for never, 1.0 for always)

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/CustomCanApplyGameplayEffectComponent.h` (Public)


#### class `UCustomCanApplyGameplayEffectComponent`  
`class UCustomCanApplyGameplayEffectComponent : public UGameplayEffectComponent`  
_L14-28_
- reflection: `UCLASS(DisplayName="Custom Can Apply This Effect", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Handles configuration of a CustomApplicationRequirement function to see if this GameplayEffect should apply
- L19 _public prototype_ `UCustomCanApplyGameplayEffectComponent();`
- L22 _public prototype_ `virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const override;` — Determine if we can apply this GameplayEffect or not
- L27 _public member_ `TArray<TSubclassOf<UGameplayEffectCustomApplicationRequirement>> ApplicationRequirements;` — `UPROPERTY(EditDefaultsOnly, Category = Application, meta = (DisplayName = "Custom Application Requirement"))` — Custom application requirements

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/ImmunityGameplayEffectComponent.h` (Public)


#### class `UImmunityGameplayEffectComponent`  
`class UImmunityGameplayEffectComponent : public UGameplayEffectComponent`  
_L16-43_
- reflection: `UCLASS(DisplayName="Immunity to Other Effects", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Immunity is blocking the application of _other_ GameplayEffectSpecs. This registers a global handler on the ASC to block the application of other GameplayEffectSpecs.
- L23 _public prototype_ `UImmunityGameplayEffectComponent();` — Constructor to set EditorFriendlyName
- L26 _public prototype_ `virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const override;` — We need to register our callback to check for Immunity
- L32 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Warn about instant Gameplay Effects as they do not persist over time (and therefore cannot grant immunity)
- L37 _protected prototype_ `bool AllowGameplayEffectApplication(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpecToConsider, FActiveGameplayEffectHandle ImmunityActiveGE) const;` — We register with the AbilitySystemComponent to try and block any GESpecs we think we should be immune to
- L42 _public member_ `TArray<FGameplayEffectQuery> ImmunityQueries;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = None)` — Grants immunity to GameplayEffects that match this query.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/RemoveOtherGameplayEffectComponent.h` (Public)


#### class `URemoveOtherGameplayEffectComponent`  
`class URemoveOtherGameplayEffectComponent : public UGameplayEffectComponent`  
_L15-39_
- reflection: `UCLASS(DisplayName="Remove Other Effects", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Remove other Gameplay Effects based on certain conditions
- L21 _public prototype_ `URemoveOtherGameplayEffectComponent();` — Constructor to set EditorFriendlyName
- L26 _public prototype_ `virtual void OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const override;` — We will re-run RemoveGameplayEffectQueries every time the owning Gameplay Effect is applied.
- L32 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Warn about periodic Gameplay Effects, that you probably instead want the OngoingTagRequirements in TagRequirementsGameplayEffectComponent
- L38 _public member_ `TArray<FGameplayEffectQuery> RemoveGameplayEffectQueries;` — `UPROPERTY(EditDefaultsOnly, Category = None)` — On Application of the owning Gameplay Effect, any Active GameplayEffects that *match* these queries will be removed.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/TargetTagRequirementsGameplayEffectComponent.h` (Public)


#### class `UTargetTagRequirementsGameplayEffectComponent`  
`class UTargetTagRequirementsGameplayEffectComponent : public UGameplayEffectComponent`  
_L15-58_
- reflection: `UCLASS(DisplayName="Require Tags to Apply/Continue This Effect", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Specifies tag requirements that the Target (owner of the Gameplay Effect) must have if this GE should apply or continue to execute
- L21 _public prototype_ `UTargetTagRequirementsGameplayEffectComponent();` — Constructor to set EditorFriendlyName
- L24 _public prototype_ `virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const override;` — Can we apply to the ActiveGEContainer?
- L27 _public prototype_ `virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& GEContainer, FActiveGameplayEffect& ActiveGE) const override;` — Once we've applied, we need to register for ongoing requirements
- L33 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Validate incompatible configurations
- L38 _private prototype_ `void OnGameplayEffectRemoved(const FGameplayEffectRemovalInfo& GERemovalInfo, UAbilitySystemComponent* ASC, TArray<TTuple<FGameplayTag, FDelegateHandle>> AllBoundEvents) const;` — We need to be notified when we're removed to unregister some callbacks
- L41 _private prototype_ `void OnTagChanged(const FGameplayTag GameplayTag, int32 NewCount, FActiveGameplayEffectHandle ActiveGEHandle) const;` — We need to register a callback for when the owner changes its tags.  When that happens, we need to figure out if our GE should continue to execute
- L44 _private prototype_ `bool HaveRemovalRequirementsBeenMet(const FGameplayTagContainer& TargetOwnedTags, bool bNetAuthority) const;` — Have requirements to remove this Gameplay Effect been met?
- L49 _public member_ `FGameplayTagRequirements ApplicationTagRequirements;` — `UPROPERTY(EditDefaultsOnly, Category = Tags)` — Tag requirements the target must have for this GameplayEffect to be applied. This is pass/fail at the time of application. If fail, this GE fails to apply.
- L53 _public member_ `FGameplayTagRequirements OngoingTagRequirements;` — `UPROPERTY(EditDefaultsOnly, Category = Tags)` — Once Applied, these tags requirements are used to determined if the GameplayEffect is "on" or "off". A GameplayEffect can be off and do nothing, but still applied.
- L57 _public member_ `FGameplayTagRequirements RemovalTagRequirements;` — `UPROPERTY(EditDefaultsOnly, Category = Tags)` — Tag requirements that if met will remove this effect. Also prevents effect application.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectComponents/TargetTagsGameplayEffectComponent.h` (Public)


#### class `UTargetTagsGameplayEffectComponent`  
`class UTargetTagsGameplayEffectComponent : public UGameplayEffectComponent`  
_L13-54_
- reflection: `UCLASS(DisplayName="Grant Tags to Target Actor", MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: Handles granting Tags to the Target (sometimes referred to as the Owner) of the Gameplay Effect
- L19 _public prototype_ `virtual void PostInitProperties() override;` — Setup an EditorFriendlyName and do some initialization
- L22 _public prototype_ `virtual void OnGameplayEffectChanged() override;` — Needed to properly load FInheritedTagContainer properties
- L25 _public function_ `const FInheritedTagContainer& GetConfiguredTargetTagChanges() const` — Gets the (Granted) Target Tags inherited tag structure (as configured)
- L28 _public prototype_ `void SetAndApplyTargetTagChanges(const FInheritedTagContainer& TagContainerMods);` — Applies the (Granted) Target Tags to the GameplayEffect (and saves those changes) so that it may grant these Tags the Target Actor when Applied
- L32 _public prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;` — Needed to properly update FInheritedTagContainer properties
- L35 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;` — Validate incompatible configurations
- L39 _private function_ `static const FName& GetInheritableGrantedTagsContainerName()` — Get a cached version of the FProperty Name for PostEditChangeProperty
- L48 _private prototype_ `void ApplyTargetTagChanges() const;` — Applies the configured (Granted) Target Tags to the owning GameplayEffect.
- L53 _private member_ `FInheritedTagContainer InheritableGrantedTagsContainer;` — `UPROPERTY(EditDefaultsOnly, Category = None, meta = (DisplayName = "Add Tags", Categories = "OwnedTagsCategory"))` — These tags are applied (granted) to the target actor of the Gameplay Effect.  The Target would then "own" these Tags.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectCustomApplicationRequirement.h` (Public)


#### class `UGameplayEffectCustomApplicationRequirement`  
`class UGameplayEffectCustomApplicationRequirement : public UObject`  
_L16-24_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, MinimalAPI)`
- inherits: `UObject`
- desc: Class used to perform custom gameplay effect modifier calculations, either via blueprint or native code
- L23 _public prototype_ `bool CanApplyGameplayEffect(const UGameplayEffect* GameplayEffect, const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const;` — `UFUNCTION(BlueprintNativeEvent, Category="Calculation")` — Return whether the gameplay effect should be applied or not

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectExecutionCalculation.h` (Public)


#### struct `FGameplayEffectCustomExecutionParameters`  
`struct FGameplayEffectCustomExecutionParameters`  
_L21-197_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct representing parameters for a custom gameplay effect execution. Should not be held onto via reference, used just for the scope of the execution
- L28 _public prototype_ `FGameplayEffectCustomExecutionParameters();` — Constructors
- L29 _public prototype_ `FGameplayEffectCustomExecutionParameters(FGameplayEffectSpec& InOwningSpec, const TArray<FGameplayEffectExecutionScopedModifierInfo>& InScopedMods, UAbilitySystemComponent* InTargetAbilityComponent, const FGameplayTagContainer& InPassedIntags, const FPredictionKey& InPredictionKey);`
- L33 _public prototype_ `const FGameplayEffectSpec& GetOwningSpec() const;` — Simple accessor to owning gameplay spec
- L36 _public prototype_ `FGameplayEffectSpec* GetOwningSpecForPreExecuteMod() const;` — Non const access. Be careful with this, especially when modifying a spec after attribute capture.
- L39 _public prototype_ `UAbilitySystemComponent* GetTargetAbilitySystemComponent() const;` — Simple accessor to target ability system component
- L42 _public prototype_ `UAbilitySystemComponent* GetSourceAbilitySystemComponent() const;` — Simple accessor to source ability system component (could be null!)
- L45 _public prototype_ `const FGameplayTagContainer& GetPassedInTags() const;` — Simple accessor to the Passed In Tags to this execution
- L47 _public prototype_ `TArray<FActiveGameplayEffectHandle> GetIgnoreHandles() const;`
- L49 _public prototype_ `FPredictionKey GetPredictionKey() const;`
- L61 _public prototype_ `bool AttemptCalculateCapturedAttributeMagnitude(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef, const FAggregatorEvaluateParameters& InEvalParams, OUT float& OutMagnitude) const;` — Attempts to calculate the magnitude of a captured attribute given the specified parameters. Can fail if the gameplay spec doesn't have a valid capture for the attribute. @param InCaptureDef	Attribute definition to attempt to calculate the magnitude of @param InEvalParams	Parameters to evaluate the attribute under @param OutMagnitude	[OUT] Computed magnitude @return True if the magnitude was successfully calculated, false if it was not
- L74 _public prototype_ `bool AttemptCalculateCapturedAttributeMagnitudeWithBase(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef, const FAggregatorEvaluateParameters& InEvalParams, float InBaseValue, OUT float& OutMagnitude) const;` — Attempts to calculate the magnitude of a captured attribute given the specified parameters, including a starting base value. Can fail if the gameplay spec doesn't have a valid capture for the attribute. @param InCaptureDef	Attribute definition to attempt to calculate the magnitude of @param InEvalParams	Parameters to evaluate the attribute under @param InBaseValue	Base value to evaluate the attribute under @param OutMagnitude	[OUT] Computed magnitude @return True if the magnitude was successfully calculated, false if it was not
- L85 _public prototype_ `bool AttemptCalculateCapturedAttributeBaseValue(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef, OUT float& OutBaseValue) const;` — Attempts to calculate the base value of a captured attribute given the specified parameters. Can fail if the gameplay spec doesn't have a valid capture for the attribute. @param InCaptureDef	Attribute definition to attempt to calculate the base value of @param OutBaseValue	[OUT] Computed base value @return True if the base value was successfully calculated, false if it was not
- L97 _public prototype_ `bool AttemptCalculateCapturedAttributeBonusMagnitude(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef, const FAggregatorEvaluateParameters& InEvalParams, OUT float& OutBonusMagnitude) const;` — Attempts to calculate the bonus magnitude of a captured attribute given the specified parameters. Can fail if the gameplay spec doesn't have a valid capture for the attribute. @param InCaptureDef		Attribute definition to attempt to calculate the bonus magnitude of @param InEvalParams		Parameters to evaluate the attribute under @param OutBonusMagnitude	[OUT] Computed bonus magnitude @return True if the bonus magnitude was successfully calculated, false if it was not
- L108 _public prototype_ `bool AttemptGetCapturedAttributeAggregatorSnapshot(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef, OUT FAggregator& OutSnapshottedAggregator) const;` — Attempts to populate the specified aggregator with a snapshot of a backing captured aggregator. Can fail if the gameplay spec doesn't have a valid capture for the attribute. @param InCaptureDef				Attribute definition to attempt to snapshot @param OutSnapshottedAggregator	[OUT] Snapshotted aggregator, if possible @return True if the aggregator was successfully snapshotted, false if it was not
- L117 _public prototype_ `bool AttemptGatherAttributeMods(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef, const FAggregatorEvaluateParameters& InEvalParams, OUT TMap<EGameplayModEvaluationChannel, const TArray<FAggregatorMod>*>& OutModMap) const;` — Returns all modifiers for a given captured def. Note the returned list is a direct reference to the internal list stored in the attribute aggregators (possibly a snapshot copy or possibly the "real" ones). Also note that all modifiers are returned, even ones that do not qualify for the given InEvalParams. You will still need to check ::Qualifies() on the mods themselves to see if they "count". (we are returning a direct reference to the internal mod list, so we do not want to remove them or force a copy). Consider using ForEachQualifiedAttributeMod when you want to "do something for every qualifier mod".
- L120 _public prototype_ `bool ForEachQualifiedAttributeMod(const FGameplayEffectAttributeCaptureDefinition& InCaptureDef, const FAggregatorEvaluateParameters& InEvalParams, TFunction< void(EGameplayModEvaluationChannel, EGameplayModOp::Type, const FAggregatorMod&) >) const;` — Runs given TFunction on every qualifier mod for a given AttributeCaptureDefinition
- L131 _public prototype_ `bool AttemptCalculateTransientAggregatorMagnitude(const FGameplayTag& InAggregatorIdentifier, const FAggregatorEvaluateParameters& InEvalParams, OUT float& OutMagnitude) const;` — Attempts to calculate the magnitude of a transient aggregator given the specified parameters. @param InAggregatorIdentifier	Tag identifying the transient aggregator to attempt to calculate the magnitude of @param InEvalParams				Parameters to evaluate the aggregator under @param OutMagnitude				[OUT] Computed magnitude @return True if the magnitude was successfully calculated, false if it was not
- L143 _public prototype_ `bool AttemptCalculateTransientAggregatorMagnitudeWithBase(const FGameplayTag& InAggregatorIdentifier, const FAggregatorEvaluateParameters& InEvalParams, float InBaseValue, OUT float& OutMagnitude) const;` — Attempts to calculate the magnitude of a transient aggregator given the specified parameters, including a starting base value. @param InAggregatorIdentifier	Tag identifying the transient aggregator to attempt to calculate the magnitude of @param InEvalParams				Parameters to evaluate the attribute under @param InBaseValue				Base value to evaluate the attribute under @param OutMagnitude				[OUT] Computed magnitude @return True if the magnitude was successfully calculated, false if it was not
- L153 _public prototype_ `bool AttemptCalculateTransientAggregatorBaseValue(const FGameplayTag& InAggregatorIdentifier, OUT float& OutBaseValue) const;` — Attempts to calculate the base value of a transient aggregator given the specified parameters. @param InAggregatorIdentifier	Tag identifying the transient aggregator to attempt to calculate the base value of @param OutBaseValue				[OUT] Computed base value @return True if the base value was successfully calculated, false if it was not
- L164 _public prototype_ `bool AttemptCalculateTransientAggregatorBonusMagnitude(const FGameplayTag& InAggregatorIdentifier, const FAggregatorEvaluateParameters& InEvalParams, OUT float& OutBonusMagnitude) const;` — Attempts to calculate the bonus magnitude of a transient aggregator given the specified parameters. @param InAggregatorIdentifier		Tag identifying the transient aggregator to attempt to calculate the bonus magnitude of @param InEvalParams					Parameters to evaluate the attribute under @param OutBonusMagnitude				[OUT] Computed bonus magnitude @return True if the bonus magnitude was successfully calculated, false if it was not
- L175 _public prototype_ `bool AttemptGetCapturedAttributeAggregatorSnapshot(const FGameplayTag& InAggregatorIdentifier, OUT FAggregator& OutSnapshottedAggregator) const;` — Attempts to populate the specified aggregator with a snapshot of a backing transient aggregator. Can fail if the transient aggregator doesn't exist as a result of no scoped mods targeting it. @param InAggregatorIdentifier	Tag identifying the transient aggregator to attempt to snapshot @param OutSnapshottedAggregator	[OUT] Snapshotted aggregator, if possible @return True if the aggregator was successfully snapshotted, false if it was not
- L180 _private member_ `TMap<FGameplayEffectAttributeCaptureDefinition, FAggregator> ScopedModifierAggregators;` — Mapping of capture definition to aggregator with scoped modifiers added in; Used to process scoped modifiers w/o modifying underlying aggregators in the capture
- L183 _private member_ `TMap<FGameplayTag, FAggregator> ScopedTransientAggregators;` — Mapping of tag identifier to aggregators with scoped modifiers added in; Used to process "temporary variable" support w/o requiring backed attribute capture definitions in scoped modifiers
- L186 _private member_ `FGameplayEffectSpec* OwningSpec;` — Owning gameplay effect spec
- L189 _private member_ `TWeakObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent;` — Target ability system component of the execution
- L192 _private member_ `FGameplayTagContainer PassedInTags;` — The extra tags that were passed in to this execution
- L194 _private member_ `TArray<FActiveGameplayEffectHandle> IgnoreHandles;`
- L196 _private member_ `FPredictionKey PredictionKey;`

#### struct `FGameplayEffectCustomExecutionOutput`  
`struct FGameplayEffectCustomExecutionOutput`  
_L201-257_
- reflection: `USTRUCT(BlueprintType)`
- desc: Struct representing the output of a custom gameplay effect execution.
- L208 _public prototype_ `FGameplayEffectCustomExecutionOutput();` — Constructor
- L211 _public prototype_ `void MarkStackCountHandledManually();` — Mark that the execution has manually handled the stack count and the GE system should not attempt to automatically act upon it for emitted modifiers
- L214 _public prototype_ `bool IsStackCountHandledManually() const;` — Simple accessor for determining whether the execution has manually handled the stack count or not
- L217 _public prototype_ `bool AreGameplayCuesHandledManually() const;` — Accessor for determining if GameplayCue events have already been handled
- L220 _public prototype_ `void MarkConditionalGameplayEffectsToTrigger();` — Mark that the execution wants conditional gameplay effects to trigger
- L223 _public prototype_ `void MarkGameplayCuesHandledManually();` — Mark that the execution wants conditional gameplay effects to trigger
- L226 _public prototype_ `bool ShouldTriggerConditionalGameplayEffects() const;` — Simple accessor for determining whether the execution wants conditional gameplay effects to trigger or not
- L229 _public prototype_ `void AddOutputModifier(const FGameplayModifierEvaluatedData& InOutputMod);` — Add the specified evaluated data to the execution's output modifiers
- L232 _public prototype_ `const TArray<FGameplayModifierEvaluatedData>& GetOutputModifiers() const;` — Simple accessor to output modifiers of the execution
- L235 _public prototype_ `void GetOutputModifiers(OUT TArray<FGameplayModifierEvaluatedData>& OutOutputModifiers) const;` — Simple accessor to output modifiers of the execution
- L238 _public function_ `TArray<FGameplayModifierEvaluatedData>& GetOutputModifiersRef()` — Returns direct access to output modifiers of the execution (avoid copy)
- L244 _private member_ `TArray<FGameplayModifierEvaluatedData> OutputModifiers;` — `UPROPERTY()` — Modifiers emitted by the execution
- L248 _private member_ `uint32 bTriggerConditionalGameplayEffects : 1;` — `UPROPERTY()` — If true, the execution wants to trigger conditional gameplay effects when it completes
- L252 _private member_ `uint32 bHandledStackCountManually : 1;` — `UPROPERTY()` — If true, the execution itself has manually handled the stack count of the effect and the GE system doesn't have to automatically handle it
- L256 _private member_ `uint32 bHandledGameplayCuesManually : 1;` — `UPROPERTY()` — If true, the execution itself has manually invoked all gameplay cues and the GE system doesn't have to automatically handle them.

#### class `UGameplayEffectExecutionCalculation`  
`class UGameplayEffectExecutionCalculation : public UGameplayEffectCalculation`  
_L260-315_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, MinimalAPI)`
- inherits: `UGameplayEffectCalculation`
- L268 _protected member_ `bool bRequiresPassedInTags;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Attributes)` — Used to indicate if this execution uses Passed In Tags
- L276 _protected member_ `TArray<FGameplayEffectAttributeCaptureDefinition> InvalidScopedModifierAttributes;` — `UPROPERTY(EditDefaultsOnly, Category=Attributes)` — Any attribute in this list will not show up as a valid option for scoped modifiers; Used to allow attribute capture for internal calculation while preventing modification
- L280 _protected member_ `FGameplayTagContainer ValidTransientAggregatorIdentifiers;` — `UPROPERTY(EditDefaultsOnly, Category=NonAttributeCalculation)` — Any tag in this container will show up as a valid "temporary variable" for scoped modifiers; Used to allow for data-driven variable support that doesn't rely on scoped modifiers
- L288 _public prototype_ `virtual void GetValidScopedModifierAttributeCaptureDefinitions(OUT TArray<FGameplayEffectAttributeCaptureDefinition>& OutScopableModifiers) const;` — Gets the collection of capture attribute definitions that the calculation class will accept as valid scoped modifiers @param OutScopableModifiers	[OUT] Array to populate with definitions valid as scoped modifiers
- L295 _public prototype_ `virtual const FGameplayTagContainer& GetValidTransientAggregatorIdentifiers() const;` — Gets the collection of identifiers of valid transient aggregators ("temporary variable aggregators") @return Array of valid transient aggregator identifiers
- L298 _public prototype_ `virtual bool DoesRequirePassedInTags() const;` — Returns if this execution requires passed in tags
- L314 _public prototype_ `void Execute(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;` — `UFUNCTION(BlueprintNativeEvent, Category="Calculation")` — Called whenever the owning gameplay effect is executed. Allowed to do essentially whatever is desired, including generating new modifiers to instantly execute as well. @note: Native subclasses should override the auto-generated Execute_Implementation function and NOT this one. @param ExecutionParams		Parameters for the custom execution calculation @param OutExecutionOutput	[OUT] Output data populated by the execution detailing further behavior or results of the execution

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L323 _macro_ `#define DECLARE_ATTRIBUTE_CAPTUREDEF(P) \`
- L327 _macro_ `#define DEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectExtension.h` (Public)


#### struct `FGameplayEffectModCallbackData`  
`struct FGameplayEffectModCallbackData`  
_L17-30_
- L19 _public function_ `FGameplayEffectModCallbackData(const FGameplayEffectSpec& InEffectSpec, FGameplayModifierEvaluatedData& InEvaluatedData, UAbilitySystemComponent& InTarget) : EffectSpec(InEffectSpec) , EvaluatedData(InEvaluatedData) , Target(InTarget)`
- L26 _public member_ `const struct FGameplayEffectSpec& EffectSpec;` — The spec that the mod came from
- L27 _public member_ `struct FGameplayModifierEvaluatedData& EvaluatedData;` — The 'flat'/computed data to be applied to the target
- L29 _public member_ `class UAbilitySystemComponent &Target;` — Target we intend to apply to

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectTypes.h` (Public)


#### enum `EGameplayModEvaluationChannel`  
`enum class EGameplayModEvaluationChannel : uint8`  
_L54-69_
- reflection: `UENUM()`
- desc: Valid gameplay modifier evaluation channels; Displayed and renamed via game-specific aliases and options
- L56 _public enumerator_ `Channel0 UMETA(Hidden)`
- L57 _public enumerator_ `Channel1 UMETA(Hidden)`
- L58 _public enumerator_ `Channel2 UMETA(Hidden)`
- L59 _public enumerator_ `Channel3 UMETA(Hidden)`
- L60 _public enumerator_ `Channel4 UMETA(Hidden)`
- L61 _public enumerator_ `Channel5 UMETA(Hidden)`
- L62 _public enumerator_ `Channel6 UMETA(Hidden)`
- L63 _public enumerator_ `Channel7 UMETA(Hidden)`
- L64 _public enumerator_ `Channel8 UMETA(Hidden)`
- L65 _public enumerator_ `Channel9 UMETA(Hidden)`
- L68 _public enumerator_ `Channel_MAX UMETA(Hidden)` — Always keep last

#### struct `FGameplayModEvaluationChannelSettings`  
`struct FGameplayModEvaluationChannelSettings`  
_L74-108_
- reflection: `USTRUCT()`
- desc: Struct representing evaluation channel settings for a gameplay modifier
- L79 _public prototype_ `FGameplayModEvaluationChannelSettings();` — Constructor
- L87 _public prototype_ `EGameplayModEvaluationChannel GetEvaluationChannel() const;` — Get the modifier evaluation channel to use @return	Either the channel directly specified within the settings, if valid, or Channel0 in the event of a game not using modifier channels or in the case of an invalid channel being specified within the settings
- L91 _public member_ `static const FName ForceHideMetadataKey;`
- L92 _public member_ `static const FString ForceHideMetadataEnabledValue;`
- L95 _public prototype_ `void SetEvaluationChannel(EGameplayModEvaluationChannel NewChannel);`
- L97 _public prototype_ `bool operator==(const FGameplayModEvaluationChannelSettings& Other) const;`
- L98 _public prototype_ `bool operator!=(const FGameplayModEvaluationChannelSettings& Other) const;`
- L104 _protected member_ `EGameplayModEvaluationChannel Channel;` — `UPROPERTY(EditDefaultsOnly, Category=EvaluationChannel)` — Channel the settings would prefer to use, if possible/valid

#### enum `EGameplayModOp::Type`  
`enum Type : int`  
_L118-149_
- desc: Defines the ways that mods will modify attributes. Values of the same type are aggregated, and then applied in the following equation: ((BaseValue + AddBase) * MultiplyAdditive / DivideAdditive * MultiplyCompound) + AddFinal
- L121 _public enumerator_ `AddBase UMETA(DisplayName="Add (Base)")` — Adds to the Base value. This happens first, before all other mods are considered.
- L124 _public enumerator_ `MultiplyAdditive UMETA(DisplayName = "Multiply (Additive)")` — Multipliers are added together first, then multiplied against prev result. E.g. 50% + 50% = 100% in values is 1.5 + 1.5 = 2.0.
- L127 _public enumerator_ `DivideAdditive UMETA(DisplayName = "Divide (Additive)")` — Divisors are added together, then divided against the prev result. E.g. 1/2 + 1/2 = 1/3 in values is 2 + 2 = 3.
- L132 _public enumerator_ `MultiplyCompound = 4 UMETA(DisplayName = "Multiply (Compound)")` — Multiply the prev result by this value. E.g. two values of 1.5 compounded: 1.5 * 1.5 = 2.25.
- L135 _public enumerator_ `AddFinal UMETA(DisplayName = "Add (Final)")` — Add this value to the final computed result.
- L138 _public enumerator_ `Max UMETA(Hidden, DisplayName="Invalid")` — This must always be the last value (used in iteration code).
- L141 _public enumerator_ `Additive = 0 UMETA(Hidden)` — Backwards compatible names
- L142 _public enumerator_ `Multiplicitive = 1 UMETA(Hidden)` — Backwards compat name
- L143 _public enumerator_ `Division = 2 UMETA(Hidden)` — Backwards compat name
- L148 _public enumerator_ `Override = 3 UMETA(DisplayName="Override")` — Override the value, regardless of what the computation provides.

#### enum `EGameplayEffectStackingType`  
`enum class EGameplayEffectStackingType : uint8`  
_L177-187_
- reflection: `UENUM()`
- desc: Defines how multiple instances of the same GameplayEffect definition stack when applied (non-instant GE's).
- L180 _public enumerator_ `None UMETA(DisplayName = "No Stacking")` — No stacking. Each application is a separate instance.
- L183 _public enumerator_ `AggregateBySource UMETA(DisplayName = "Stack Per Source")` — Stacks only when the same source reapplies the effect.
- L186 _public enumerator_ `AggregateByTarget UMETA(DisplayName = "Stack Per Target")` — Stacks only when the effect is reapplied to the same target.

#### struct `FGameplayModifierEvaluatedData`  
`struct FGameplayModifierEvaluatedData`  
_L194-239_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data that describes what happened in an attribute modification. This is passed to ability set callbacks
- L198 _public function_ `FGameplayModifierEvaluatedData() : Attribute() , ModifierOp(EGameplayModOp::Additive) , Magnitude(0.f) , IsValid(false)`
- L206 _public function_ `FGameplayModifierEvaluatedData(const FGameplayAttribute& InAttribute, TEnumAsByte<EGameplayModOp::Type> InModOp, float InMagnitude, FActiveGameplayEffectHandle InHandle = FActiveGameplayEffectHandle()) : Attribute(InAttribute) , ModifierOp(InModOp) , Magnitude(InMagnitude) , Handle(InHandle) , IsValid(true)`
- L217 _public member_ `FGameplayAttribute Attribute;` — `UPROPERTY()` — What attribute was modified
- L221 _public member_ `TEnumAsByte<EGameplayModOp::Type> ModifierOp;` — `UPROPERTY()` — The numeric operation of this modifier: Override, Add, Multiply, etc
- L225 _public member_ `float Magnitude;` — `UPROPERTY()` — The raw magnitude of the applied attribute, this is generally before being clamped
- L229 _public member_ `FActiveGameplayEffectHandle Handle;` — `UPROPERTY()` — Handle of the active gameplay effect that originated us. Will be invalid in many cases
- L233 _public member_ `bool IsValid;` — `UPROPERTY()` — True if something was evaluated
- L235 _public function_ `FString ToSimpleString() const`

#### struct `FGameplayEffectContext`  
`struct FGameplayEffectContext`  
_L248-474_
- reflection: `USTRUCT()`
- desc: Data structure that stores an instigator and related data, such as positions and targets Games can subclass this structure and add game-specific information It is passed throughout effect execution so it is a great place to track transient information about an execution
- L252 _public function_ `FGameplayEffectContext() : AbilityLevel(1) , WorldOrigin(ForceInitToZero) , bHasWorldOrigin(false) , bReplicateSourceObject(false) , bReplicateInstigator(false) , bReplicateEffectCauser(false)`
- L262 _public function_ `FGameplayEffectContext(AActor* InInstigator, AActor* InEffectCauser) : AbilityLevel(1) , WorldOrigin(ForceInitToZero) , bHasWorldOrigin(false) , bReplicateSourceObject(false) , bReplicateInstigator(false) , bReplicateEffectCauser(false)`
- L273 _public prototype_ `virtual ~FGameplayEffectContext() = default;`
- L276 _public prototype_ `virtual void GetOwnedGameplayTags(OUT FGameplayTagContainer& ActorTagContainer, OUT FGameplayTagContainer& SpecTagContainer) const;` — Returns the list of gameplay tags applicable to this effect, defaults to the owner's tags. SpecTagContainer remains untouched by default.
- L279 _public prototype_ `virtual void AddInstigator(class AActor *InInstigator, class AActor *InEffectCauser);` — Sets the instigator and effect causer. Instigator is who owns the ability that spawned this, EffectCauser is the actor that is the physical source of the effect, such as a weapon. They can be the same.
- L282 _public prototype_ `virtual void SetAbility(const UGameplayAbility* InGameplayAbility);` — Sets the ability that was used to spawn this
- L285 _public function_ `virtual AActor* GetInstigator() const` — Returns the immediate instigator that applied this effect
- L291 _public prototype_ `const UGameplayAbility* GetAbility() const;` — Returns the CDO of the ability used to instigate this context
- L294 _public prototype_ `const UGameplayAbility* GetAbilityInstance_NotReplicated() const;` — Returns the specific instance that instigated this, may not always be set
- L297 _public function_ `int32 GetAbilityLevel() const` — Gets the ability level this was evaluated at
- L303 _public function_ `virtual UAbilitySystemComponent* GetInstigatorAbilitySystemComponent() const` — Returns the ability system component of the instigator of this effect
- L309 _public function_ `virtual AActor* GetEffectCauser() const` — Returns the physical actor tied to the application of this effect
- L315 _public function_ `void SetEffectCauser(AActor* InEffectCauser)` — Modify the effect causer actor, useful when that information is added after creation
- L322 _public function_ `virtual AActor* GetOriginalInstigator() const` — Should always return the original instigator that started the whole chain. Subclasses can override what this does
- L328 _public function_ `virtual UAbilitySystemComponent* GetOriginalInstigatorAbilitySystemComponent() const` — Returns the ability system component of the instigator that started the whole chain
- L334 _public function_ `virtual void AddSourceObject(const UObject* NewSourceObject)` — Sets the object this effect was created from.
- L341 _public function_ `virtual UObject* GetSourceObject() const` — Returns the object this effect was created from.
- L347 _public prototype_ `virtual void AddActors(const TArray<TWeakObjectPtr<AActor>>& IActor, bool bReset = false);` — Add actors to the stored actor list
- L350 _public prototype_ `virtual void AddHitResult(const FHitResult& InHitResult, bool bReset = false);` — Add a hit result for targeting
- L353 _public function_ `virtual const TArray<TWeakObjectPtr<AActor>>& GetActors() const` — Returns actor list, may be empty
- L359 _public function_ `virtual const FHitResult* GetHitResult() const` — Returns hit result, this can be null
- L365 _public function_ `virtual FHitResult* GetHitResult()` — Returns hit result, this can be null
- L371 _public prototype_ `virtual void AddOrigin(FVector InOrigin);` — Adds an origin point
- L374 _public function_ `virtual const FVector& GetOrigin() const` — Returns origin point, may be invalid if HasOrigin is false
- L380 _public function_ `virtual bool HasOrigin() const` — Returns true if GetOrigin will give valid information
- L386 _public prototype_ `virtual FString ToString() const;` — Returns debug string
- L389 _public function_ `virtual UScriptStruct* GetScriptStruct() const` — Returns the actual struct used for serialization, subclasses must override this!
- L395 _public function_ `virtual FGameplayEffectContext* Duplicate() const` — Creates a copy of this context, used to duplicate for later modifications
- L408 _public prototype_ `virtual bool IsLocallyControlled() const;` — True if this was instigated by a locally controlled actor
- L411 _public prototype_ `virtual bool IsLocallyControlledPlayer() const;` — True if this was instigated by a locally controlled player
- L414 _public prototype_ `virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Custom serialization, subclasses must override this
- L417 _protected prototype_ `static bool CanActorReferenceBeReplicated(const AActor* Actor);`
- L423 _protected member_ `TWeakObjectPtr<AActor> Instigator;` — `UPROPERTY()` — Instigator actor, the actor that owns the ability system component
- L427 _protected member_ `TWeakObjectPtr<AActor> EffectCauser;` — `UPROPERTY()` — The physical actor that actually did the damage, can be a weapon or projectile
- L431 _protected member_ `TWeakObjectPtr<UGameplayAbility> AbilityCDO;` — `UPROPERTY()` — The ability CDO that is responsible for this effect context (replicated)
- L435 _protected member_ `TWeakObjectPtr<UGameplayAbility> AbilityInstanceNotReplicated;` — `UPROPERTY(NotReplicated)` — The ability instance that is responsible for this effect context (NOT replicated)
- L439 _protected member_ `int32 AbilityLevel;` — `UPROPERTY()` — The level this was executed at
- L443 _protected member_ `TWeakObjectPtr<UObject> SourceObject;` — `UPROPERTY()` — Object this effect was created from, can be an actor or static object. Useful to bind an effect to a gameplay object
- L447 _protected member_ `TWeakObjectPtr<UAbilitySystemComponent> InstigatorAbilitySystemComponent;` — `UPROPERTY(NotReplicated)` — The ability system component that's bound to instigator
- L451 _protected member_ `TArray<TWeakObjectPtr<AActor>> Actors;` — `UPROPERTY()` — Actors referenced by this context
- L454 _protected member_ `TSharedPtr<FHitResult> HitResult;` — Trace information - may be nullptr in many cases
- L458 _protected member_ `FVector WorldOrigin;` — `UPROPERTY()` — Stored origin, may be invalid if bHasWorldOrigin is false
- L461 _protected member_ `uint8 bHasWorldOrigin:1;` — `UPROPERTY()`
- L465 _protected member_ `uint8 bReplicateSourceObject:1;` — `UPROPERTY(NotReplicated)` — True if the SourceObject can be replicated. This bool is not replicated itself.
- L469 _protected member_ `uint8 bReplicateInstigator:1;` — `UPROPERTY(NotReplicated)` — True if the Instigator can be replicated. This bool is not replicated itself.
- L473 _protected member_ `uint8 bReplicateEffectCauser:1;` — `UPROPERTY(NotReplicated)` — True if the Instigator can be replicated. This bool is not replicated itself.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FGameplayEffectContext >`  
_L477-484_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayEffectContext>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L480-483_

#### struct `FGameplayEffectContextHandle`  
`struct FGameplayEffectContextHandle`  
_L491-794_
- reflection: `USTRUCT(BlueprintType)`
- desc: Handle that wraps a FGameplayEffectContext or subclass, to allow it to be polymorphic and replicate properly
- L495 _public function_ `FGameplayEffectContextHandle()`
- L499 _public prototype_ `virtual ~FGameplayEffectContextHandle() = default;`
- L502 _public function_ `explicit FGameplayEffectContextHandle(FGameplayEffectContext* DataPtr)` — Constructs from an existing context, should be allocated by new
- L508 _public function_ `void operator=(FGameplayEffectContext* DataPtr)` — Sets from an existing context, should be allocated by new
- L513 _public function_ `void Clear()`
- L518 _public function_ `bool IsValid() const`
- L524 _public function_ `FGameplayEffectContext* Get()` — Returns Raw effet context, may be null
- L528 _public function_ `const FGameplayEffectContext* Get() const`
- L534 _public function_ `void GetOwnedGameplayTags(OUT FGameplayTagContainer& ActorTagContainer, OUT FGameplayTagContainer& SpecTagContainer) const` — Returns the list of gameplay tags applicable to this effect, defaults to the owner's tags
- L543 _public function_ `void AddInstigator(class AActor *InInstigator, class AActor *InEffectCauser)` — Sets the instigator and effect causer. Instigator is who owns the ability that spawned this, EffectCauser is the actor that is the physical source of the effect, such as a weapon. They can be the same.
- L552 _public function_ `void SetAbility(const UGameplayAbility* InGameplayAbility)` — Sets Ability instance and CDO parameters on context
- L561 _public function_ `virtual AActor* GetInstigator() const` — Returns the immediate instigator that applied this effect
- L571 _public function_ `const UGameplayAbility* GetAbility() const` — Returns the Ability CDO
- L581 _public function_ `const UGameplayAbility* GetAbilityInstance_NotReplicated() const` — Returns the Ability Instance (never replicated)
- L591 _public function_ `int32 GetAbilityLevel() const` — Returns level this was executed at
- L601 _public function_ `virtual UAbilitySystemComponent* GetInstigatorAbilitySystemComponent() const` — Returns the ability system component of the instigator of this effect
- L611 _public function_ `virtual AActor* GetEffectCauser() const` — Returns the physical actor tied to the application of this effect
- L621 _public function_ `AActor* GetOriginalInstigator() const` — Should always return the original instigator that started the whole chain. Subclasses can override what this does
- L631 _public function_ `UAbilitySystemComponent* GetOriginalInstigatorAbilitySystemComponent() const` — Returns the ability system component of the instigator that started the whole chain
- L641 _public function_ `void AddSourceObject(const UObject* NewSourceObject)` — Sets the object this effect was created from.
- L650 _public function_ `UObject* GetSourceObject() const` — Returns the object this effect was created from.
- L660 _public function_ `bool IsLocallyControlled() const` — Returns if the instigator is locally controlled
- L670 _public function_ `bool IsLocallyControlledPlayer() const` — Returns if the instigator is locally controlled and a player
- L680 _public function_ `void AddActors(const TArray<TWeakObjectPtr<AActor>>& InActors, bool bReset = false)` — Add actors to the stored actor list
- L689 _public function_ `void AddHitResult(const FHitResult& InHitResult, bool bReset = false)` — Add a hit result for targeting
- L698 _public function_ `const TArray<TWeakObjectPtr<AActor>> GetActors()` — Returns actor list, may be empty
- L709 _public function_ `const FHitResult* GetHitResult() const` — Returns hit result, this can be null
- L719 _public function_ `void AddOrigin(FVector InOrigin)` — Adds an origin point
- L728 _public function_ `virtual const FVector& GetOrigin() const` — Returns origin point, may be invalid if HasOrigin is false
- L738 _public function_ `virtual bool HasOrigin() const` — Returns true if GetOrigin will give valid information
- L748 _public function_ `FString ToString() const` — Returns debug string
- L754 _public function_ `FGameplayEffectContextHandle Duplicate() const` — Creates a deep copy of this handle, used before modifying
- L768 _public function_ `bool operator==(FGameplayEffectContextHandle const& Other) const` — Comparison operator
- L782 _public function_ `bool operator!=(FGameplayEffectContextHandle const& Other) const` — Comparison operator
- L788 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Custom serializer, handles polymorphism of context
- L793 _private member_ `TSharedPtr<FGameplayEffectContext> Data;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayEffectContextHandle> : public TStructOpsTypeTraitsBase2<FGameplayEffectContextHandle>`  
_L797-805_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayEffectContextHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L800-804_

#### struct `FGameplayEffectRemovalInfo`  
`struct FGameplayEffectRemovalInfo`  
_L810-836_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data struct for containing information pertinent to GameplayEffects as they are removed
- L816 _public member_ `bool bPrematureRemoval = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Removal")` — True when the gameplay effect's duration has not expired, meaning the gameplay effect is being forcefully removed.
- L820 _public member_ `bool bPredictionRejected = false;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Removal")` — True when the effect is being removed due to prediction rejection
- L824 _public member_ `int32 StackCount = 0;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Removal")` — Number of Stacks this gameplay effect had before it was removed.
- L828 _public member_ `FGameplayEffectContextHandle EffectContext;` — `UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Removal")` — Actor this gameplay effect was targeting.
- L832 _public member_ `TObjectPtr<UAbilitySystemComponent> OwningASC = {};` — `UPROPERTY(Transient)` — Which AbilitySystemComponent this Gameplay Effect was applied to
- L835 _public member_ `const FActiveGameplayEffect* ActiveEffect = nullptr;` — The Effect being Removed

#### struct `FGameplayCueParameters`  
`struct FGameplayCueParameters`  
_L841-952_
- reflection: `USTRUCT(BlueprintType, meta = (HasNativeBreak = "/Script/GameplayAbilities.AbilitySystemBlueprintLibrary.BreakGameplayCueParameters", HasNativeMake = "/Script/GameplayAbilities.AbilitySystemBlueprintLibrary.MakeGameplayCueParameters"))`
- desc: Metadata about a gameplay cue execution
- L845 _public function_ `FGameplayCueParameters() : NormalizedMagnitude(0.0f) , RawMagnitude(0.0f) , Location(ForceInitToZero) , Normal(ForceInitToZero) , GameplayEffectLevel(1) , AbilityLevel(1)`
- L855 _public prototype_ `FGameplayCueParameters(const struct FGameplayEffectSpecForRPC &Spec);` — Projects can override this via UAbilitySystemGlobals
- L856 _public prototype_ `FGameplayCueParameters(const struct FGameplayEffectContextHandle& EffectContext);`
- L858 _public prototype_ `bool operator==(const FGameplayCueParameters& Other) const;`
- L859 _public function_ `bool operator!=(const FGameplayCueParameters& Other) const`
- L866 _public member_ `float NormalizedMagnitude;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — Magnitude of source gameplay effect, normalzed from 0-1. Use this for "how strong is the gameplay effect" (0=min, 1=,max)
- L870 _public member_ `float RawMagnitude;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — Raw final magnitude of source gameplay effect. Use this is you need to display numbers or for other informational purposes.
- L874 _public member_ `FGameplayEffectContextHandle EffectContext;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — Effect context, contains information about hit result, etc
- L878 _public member_ `mutable FGameplayTag MatchedTagName;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue, NotReplicated)` — The tag name that matched this specific gameplay cue handler
- L882 _public member_ `mutable FGameplayTag OriginalTag;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue, NotReplicated)` — The original tag of the gameplay cue
- L886 _public member_ `FGameplayTagContainer AggregatedSourceTags;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — The aggregated source tags taken from the effect spec
- L890 _public member_ `FGameplayTagContainer AggregatedTargetTags;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — The aggregated target tags taken from the effect spec
- L894 _public member_ `FVector_NetQuantize10 Location;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — Location cue took place at
- L898 _public member_ `FVector_NetQuantizeNormal Normal;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — Normal of impact that caused cue
- L902 _public member_ `TWeakObjectPtr<AActor> Instigator;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — Instigator actor, the actor that owns the ability system component
- L906 _public member_ `TWeakObjectPtr<AActor> EffectCauser;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — The physical actor that actually did the damage, can be a weapon or projectile
- L910 _public member_ `TWeakObjectPtr<const UObject> SourceObject;` — `UPROPERTY(BlueprintReadWrite, Category=GameplayCue)` — Object this effect was created from, can be an actor or static object. Useful to bind an effect to a gameplay object
- L914 _public member_ `TWeakObjectPtr<const UPhysicalMaterial> PhysicalMaterial;` — `UPROPERTY(BlueprintReadWrite, Category = GameplayCue)` — PhysMat of the hit, if there was a hit.
- L918 _public member_ `int32 GameplayEffectLevel;` — `UPROPERTY(BlueprintReadWrite, Category = GameplayCue)` — If originating from a GameplayEffect, the level of that GameplayEffect
- L922 _public member_ `int32 AbilityLevel;` — `UPROPERTY(BlueprintReadWrite, Category = GameplayCue)` — If originating from an ability, this will be the level of that ability
- L926 _public member_ `TWeakObjectPtr<USceneComponent> TargetAttachComponent;` — `UPROPERTY(BlueprintReadWrite, Category = GameplayCue)` — Could be used to say "attach FX to this component always"
- L930 _public member_ `bool bReplicateLocationWhenUsingMinimalRepProxy = false;` — `UPROPERTY(BlueprintReadWrite, Category = GameplayCue)` — If we're using a minimal replication proxy, should we replicate location for this cue
- L933 _public member_ `bool bGameplayEffectActive = true;` — If originating from a GameplayEffect, whether that GameplayEffect is still Active
- L936 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Optimized serializer
- L939 _public prototype_ `bool IsInstigatorLocallyControlled(AActor* FallbackActor = nullptr) const;` — Returns true if this is locally controlled, using fallback actor if nothing else available
- L942 _public prototype_ `bool IsInstigatorLocallyControlledPlayer(AActor* FallbackActor=nullptr) const;` — Fallback actor is used if the parameters have nullptr for instigator and effect causer
- L945 _public prototype_ `AActor* GetInstigator() const;` — Returns the actor that instigated this originally, generally attached to an ability system component
- L948 _public prototype_ `AActor* GetEffectCauser() const;` — Returns the actor that physically caused the damage, could be a projectile or weapon
- L951 _public prototype_ `const UObject* GetSourceObject() const;` — Returns the object that originally caused this, game-specific but usually not an actor

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayCueParameters> : public TStructOpsTypeTraitsBase2<FGameplayCueParameters>`  
_L955-961_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayCueParameters>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L958-960_

#### enum `EGameplayCueEvent::Type`  
`enum Type : int`  
_L968-981_
- desc: Indicates what type of action happened to a specific gameplay cue tag. Sometimes you will get multiple events at once
- L971 _public enumerator_ `OnActive` — Called when a GameplayCue with duration is first activated, this will only be called if the client witnessed the activation
- L974 _public enumerator_ `WhileActive` — Called when a GameplayCue with duration is first seen as active, even if it wasn't actually just applied (Join in progress, etc)
- L977 _public enumerator_ `Executed` — Called when a GameplayCue is executed, this is used for instant effects or periodic ticks
- L980 _public enumerator_ `Removed` — Called when a GameplayCue with duration is removed

#### struct `FActiveGameplayEffectEvents`  
`struct FActiveGameplayEffectEvents`  
_L996-1002_
- desc: Callback struct for different types of gameplay effect changes
- L998 _public member_ `FOnActiveGameplayEffectRemoved_Info OnEffectRemoved;`
- L999 _public member_ `FOnActiveGameplayEffectStackChange OnStackChanged;`
- L1000 _public member_ `FOnActiveGameplayEffectTimeChange OnTimeChanged;`
- L1001 _public member_ `FOnActiveGameplayEffectInhibitionChanged OnInhibitionChanged;`

#### struct `FOnAttributeChangeData`  
`struct FOnAttributeChangeData`  
_L1009-1022_
- desc: Temporary parameter struct used when an attribute has changed
- L1011 _public function_ `FOnAttributeChangeData() : NewValue(0.0f) , OldValue(0.0f) , GEModData(nullptr)`
- L1017 _public member_ `FGameplayAttribute Attribute;`
- L1019 _public member_ `float NewValue;`
- L1020 _public member_ `float OldValue;`
- L1021 _public member_ `const FGameplayEffectModCallbackData* GEModData;`

#### enum `EGameplayTagEventType::Type`  
`enum Type : int`  
_L1035-1042_
- desc: Rather a tag was added or removed, used in callbacks
- L1038 _public enumerator_ `NewOrRemoved` — Event only happens when tag is new or completely removed
- L1041 _public enumerator_ `AnyCountChange` — Event happens any time tag "count" changes

#### enum `EGameplayTagReplicationState`  
`enum class EGameplayTagReplicationState : uint8`  
_L1050-1057_
- reflection: `UENUM()`
- desc: Enum to describe replication rules for each tag Any state besides "None" must be added on the server and can be predicted on clients.
- L1052 _public enumerator_ `None` — Tag will not replicate
- L1053 _public enumerator_ `SimulatedTagOnly` — tag will be replicated to simulated proxies, but not the owner. Used for GameplayEffect tags
- L1054 _public enumerator_ `TagOnly` — Tag will replicate to all without count
- L1055 _public enumerator_ `CountToOwner` — Tag will replicate to all and Count will replicate to owner, Functions same as TagAndCountToAll with Iris
- L1056 _public enumerator_ `TagAndCountToAll` — Tag and Count will replicate to all

#### struct `FGameplayTagCountItem`  
`struct FGameplayTagCountItem`  
_L1060-1094_
- reflection: `USTRUCT()`
- L1064 _public function_ `FGameplayTagCountItem() : Tag(FGameplayTag()) , Count(0) , ReplicationState(EGameplayTagReplicationState::None)`
- L1070 _public function_ `FGameplayTagCountItem(const FGameplayTag& InTag, const int32 InCount = 1, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None) : Tag(InTag) , Count(InCount) , ReplicationState(TagRepState)`
- L1077 _public member_ `FGameplayTag Tag;` — `UPROPERTY()`
- L1080 _public member_ `int32 Count;` — `UPROPERTY()`
- L1083 _public member_ `EGameplayTagReplicationState ReplicationState;` — `UPROPERTY()`
- L1085 _public function_ `bool operator == (const FGameplayTagCountItem& Other) const`
- L1090 _public function_ `bool operator == (const FGameplayTag& OtherTag) const`

#### struct `FGameplayTagCountContainer`  
`struct FGameplayTagCountContainer`  
_L1102-1416_
- reflection: `USTRUCT()`
- desc: Struct that tracks the number/count of tag applications within it. Explicitly tracks the tags added or removed, while simultaneously tracking the count of parent tags as well. Events/delegates are fired whenever the tag counts of any tag (explicit or parent) are modified.
- L1113 _public function_ `inline bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const` — Check if the count container has a gameplay tag that matches against the specified tag (expands to include parents of asset tags) @param TagToCheck	Tag to check for a match @return True if the count container has a gameplay tag that matches, false if not
- L1125 _public function_ `inline bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const` — Check if the count container has gameplay tags that matches against all of the specified tags (expands to include parents of asset tags) @param TagContainer			Tag container to check for a match. If empty will return true @return True if the count container matches all of the gameplay tags
- L1152 _public function_ `inline bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const` — Check if the count container has gameplay tags that matches against any of the specified tags (expands to include parents of asset tags) @param TagContainer			Tag container to check for a match. If empty will return false @return True if the count container matches any of the gameplay tags
- L1177 _public function_ `inline void UpdateTagCount(const FGameplayTagContainer& Container, int32 CountDelta)` — Update the specified container of tags by the specified delta, potentially causing an additional or removal from the explicit tag list @param Container		Container of tags to update @param CountDelta	Delta of the tag count to apply
- L1208 _public function_ `inline bool UpdateTagCount(const FGameplayTag& Tag, int32 CountDelta, EGameplayTagReplicationState TagRepState)` — Update the specified tag by the specified delta, potentially causing an additional or removal from the explicit tag list @param Tag						Tag to update @param CountDelta				Delta of the tag count to apply @return True if tag was *either* added or removed. (E.g., we had the tag and now dont. or didnt have the tag and now we do. We didn't just change the count (1 count -> 2 count would return false).
- L1228 _public function_ `inline bool UpdateTagCount_DeferredParentRemoval(const FGameplayTag& Tag, int32 CountDelta, TArray<FDeferredTagChangeDelegate>& DeferredTagChangeDelegates)` — Update the specified tag by the specified delta, potentially causing an additional or removal from the explicit tag list. Calling code MUST call FillParentTags followed by executing the returned delegates. @param Tag						Tag to update @param CountDelta				Delta of the tag count to apply @param DeferredTagChangeDelegates		Delegates to be called after this code runs @return True if tag was *either* added or removed. (E.g., we had the tag and now dont. or didnt have the tag and now we do. We didn't just change the count (1 count -> 2 count would return false).
- L1247 _public function_ `inline bool SetTagCount(const FGameplayTag& Tag, int32 NewCount, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None)` — Set the specified tag count to a specific value @param Tag			Tag to update @param Count			New count of the tag @param TagRepState	The replication state for the tag, if it is being added it will be added with this state @return True if tag was *either* added or removed. (E.g., we had the tag and now dont. or didnt have the tag and now we do. We didn't just change the count (1 count -> 2 count would return false).
- L1278 _public function_ `inline int32 GetTagCount(const FGameplayTag& Tag) const` — return the hierarchical count for a specified tag e.g. if A.B & A.C were added, GetTagCount("A") would return 2. @param Tag			Tag to update @return the count of the passed in tag
- L1296 _public function_ `inline int32 GetExplicitTagCount(const FGameplayTag& Tag) const` — return how many times the exact specified tag has been added to the container (ignores the tag hierarchy) e.g. if A.B & A.C were added, GetExplicitTagCount("A") would return 0, and GetExplicitTagCount("A.B") would return 1. @param Tag			Tag to update @return the count of the passed in tag
- L1308 _public function_ `void FillParentTags()` — Fills in ParentTags from GameplayTags
- L1317 _public prototype_ `void Notify_StackCountChange(const FGameplayTag& Tag);` — Broadcasts the AnyChange event for this tag. This is called when the stack count of the backing gameplay effect change. It is up to the receiver of the broadcasted delegate to decide what to do with this.
- L1326 _public prototype_ `FOnGameplayEffectTagCountChanged& RegisterGameplayTagEvent(const FGameplayTag& Tag, EGameplayTagEventType::Type EventType=EGameplayTagEventType::NewOrRemoved);` — Return delegate that can be bound to for when the specific tag's count changes to or off of zero @param Tag	Tag to get a delegate for @return Delegate for when the specified tag's count changes to or off of zero
- L1333 _public function_ `FOnGameplayEffectTagCountChanged& RegisterGenericGameplayEvent()` — Return delegate that can be bound to for when the any tag's count changes to or off of zero @return Delegate for when any tag's count changes to or off of zero
- L1339 _public function_ `const FGameplayTagContainer& GetExplicitGameplayTags() const` — Simple accessor to the explicit gameplay tag list
- L1349 _public prototype_ `void Reset(bool bResetCallbacks = true);` — Removes all of the tags. Does not notify any delegates. @param bResetCallbacks	If true, also remove all of the registered tag count change delegates
- L1351 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams);`
- L1353 _public prototype_ `void SetOwner(UAbilitySystemComponent* ASC);`
- L1355 _public function_ `bool operator==(const FGameplayTagCountContainer& Other) const`
- L1387 _private member_ `TArray<FGameplayTagCountItem> Items;` — Array of explicit tags and their count
- L1390 _private member_ `TMap<FGameplayTag, FDelegateInfo> GameplayTagEventMap;` — Map of tag to delegate that will be fired when the count for the key tag changes to or away from zero
- L1393 _private member_ `TMap<FGameplayTag, int32> GameplayTagCountMap;` — Map of tag to active count of that tag
- L1396 _private member_ `FOnGameplayEffectTagCountChanged OnAnyTagChangeDelegate;` — Delegate fired whenever any tag's count changes to or away from zero
- L1399 _private member_ `FGameplayTagContainer ExplicitTags;` — Container of tags that were explicitly added
- L1403 _private member_ `TObjectPtr<class UAbilitySystemComponent> Owner;` — `UPROPERTY()` — We want to track the owner for the container so that we can give valuable logging about tag replication mismatches.
- L1406 _private prototype_ `bool UpdateTagMap_Internal(const FGameplayTag& Tag, int32 CountDelta, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None);` — Internal helper function to adjust the explicit tag list & corresponding maps/delegates/etc. as necessary
- L1409 _private prototype_ `bool UpdateTagMapDeferredParentRemoval_Internal(const FGameplayTag& Tag, int32 CountDelta, TArray<FDeferredTagChangeDelegate>& DeferredTagChangeDelegates, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None);` — Internal helper function to adjust the explicit tag list & corresponding maps/delegates/etc. as necessary. This does not call FillParentTags or any of the tag change delegates. These delegates are returned and must be executed by the caller.
- L1412 _private prototype_ `bool UpdateExplicitTags(const FGameplayTag& Tag, int32 CountDelta, bool bDeferParentTagsOnRemove, EGameplayTagReplicationState TagRepState = EGameplayTagReplicationState::None);` — Internal helper function to adjust the explicit tag list & corresponding map.
- L1415 _private prototype_ `bool GatherTagChangeDelegates(const FGameplayTag& Tag, int32 CountDelta, TArray<FDeferredTagChangeDelegate>& TagChangeDelegates, EGameplayTagReplicationState TagRepState);` — Internal helper function to collect the delegates that need to be called when Tag has its count changed by CountDelta.

#### struct `FGameplayTagCountContainer::FDelegateInfo`  
`struct FDelegateInfo`  
_L1380-1384_
- L1382 _public member_ `FOnGameplayEffectTagCountChanged OnNewOrRemove;`
- L1383 _public member_ `FOnGameplayEffectTagCountChanged OnAnyChange;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FGameplayTagCountContainer > : public TStructOpsTypeTraitsBase2< FGameplayTagCountContainer >`  
_L1419-1425_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayTagCountContainer>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L1422-1424_

#### struct `FGameplayTagBlueprintPropertyMapping`  
`struct FGameplayTagBlueprintPropertyMapping`  
_L1433-1470_
- reflection: `USTRUCT()`
- desc: Struct used to update a blueprint property with a gameplay tag count. The property is automatically updated as the gameplay tag count changes. It only supports boolean, integer, and float properties.
- L1439 _public function_ `FGameplayTagBlueprintPropertyMapping()`
- L1440 _public function_ `FGameplayTagBlueprintPropertyMapping(const FGameplayTagBlueprintPropertyMapping& Other)`
- L1450 _public prototype_ `FGameplayTagBlueprintPropertyMapping& operator=(const FGameplayTagBlueprintPropertyMapping& Other) = default;` — Pretty weird that the assignment operator copies the handle when the copy constructor doesn't - bug?
- L1454 _public member_ `FGameplayTag TagToMap;` — `UPROPERTY(EditAnywhere, Category = GameplayTagBlueprintProperty)` — Gameplay tag being counted.
- L1458 _public member_ `TFieldPath<FProperty> PropertyToEdit;` — `UPROPERTY(VisibleAnywhere, Category = GameplayTagBlueprintProperty)` — Property to update with the gameplay tag count.
- L1462 _public member_ `FName PropertyName;` — `UPROPERTY(VisibleAnywhere, Category = GameplayTagBlueprintProperty)` — Name of property being edited.
- L1466 _public member_ `FGuid PropertyGuid;` — `UPROPERTY(VisibleAnywhere, Category = GameplayTagBlueprintProperty)` — Guid of property being edited.
- L1469 _public member_ `FDelegateHandle DelegateHandle;` — Handle to delegate bound on the ability system component.

#### struct `FGameplayTagBlueprintPropertyMap`  
`struct FGameplayTagBlueprintPropertyMap`  
_L1480-1518_
- reflection: `USTRUCT()`
- desc: Struct used to manage gameplay tag blueprint property mappings. It registers the properties with delegates on an ability system component. This struct can not be used in containers (such as TArray) since it uses a raw pointer to bind the delegate and it's address could change causing an invalid binding.
- L1486 _public prototype_ `FGameplayTagBlueprintPropertyMap();`
- L1487 _public prototype_ `FGameplayTagBlueprintPropertyMap(const FGameplayTagBlueprintPropertyMap& Other);`
- L1488 _public prototype_ `~FGameplayTagBlueprintPropertyMap();`
- L1491 _public prototype_ `void Initialize(UObject* Owner, class UAbilitySystemComponent* ASC);` — Call this to initialize and bind the properties with the ability system component.
- L1494 _public prototype_ `void ApplyCurrentTags();` — Call to manually apply the current tag state, can handle cases where callbacks were skipped
- L1498 _public prototype_ `EDataValidationResult IsDataValid(const UObject* ContainingAsset, class FDataValidationContext& Context) const;` — This can optionally be called in the owner's IsDataValid() for data validation.
- L1503 _protected prototype_ `void Unregister();`
- L1505 _protected prototype_ `void GameplayTagEventCallback(const FGameplayTag Tag, int32 NewCount, TWeakObjectPtr<UObject> RegisteredOwner);`
- L1507 _protected prototype_ `bool IsPropertyTypeValid(const FProperty* Property) const;`
- L1509 _protected prototype_ `EGameplayTagEventType::Type GetGameplayTagEventType(const FProperty* Property) const;`
- L1513 _protected member_ `TWeakObjectPtr<UObject> CachedOwner;`
- L1514 _protected member_ `TWeakObjectPtr<UAbilitySystemComponent> CachedASC;`
- L1517 _protected member_ `TArray<FGameplayTagBlueprintPropertyMapping> PropertyMappings;` — `UPROPERTY(EditAnywhere, Category = GameplayTagBlueprintProperty)`

#### struct `FGameplayTagRequirements`  
`struct FGameplayTagRequirements`  
_L1523-1553_
- reflection: `USTRUCT(BlueprintType)`
- desc: Encapsulate require and ignore tags
- L1529 _public member_ `FGameplayTagContainer RequireTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayModifier, meta=(DisplayName="Must Have Tags"))` — All of these tags must be present
- L1533 _public member_ `FGameplayTagContainer IgnoreTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayModifier, meta=(DisplayName="Must Not Have Tags"))` — None of these tags may be present
- L1537 _public member_ `FGameplayTagQuery TagQuery;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameplayModifier, meta = (DisplayName = "Query Must Match"))` — Build up a more complex query that can't be expressed with RequireTags/IgnoreTags alone
- L1540 _public prototype_ `bool RequirementsMet(const FGameplayTagContainer& Container) const;` — True if all required tags and no ignore tags found
- L1543 _public prototype_ `bool IsEmpty() const;` — True if neither RequireTags or IgnoreTags has any tags
- L1546 _public prototype_ `FString ToString() const;` — Return debug string
- L1548 _public prototype_ `bool operator==(const FGameplayTagRequirements& Other) const;`
- L1549 _public prototype_ `bool operator!=(const FGameplayTagRequirements& Other) const;`
- L1552 _public prototype_ `[[nodiscard]] FGameplayTagQuery ConvertTagFieldsToTagQuery() const;` — Converts the RequireTags and IgnoreTags fields into an equivalent FGameplayTagQuery

#### struct `FTagContainerAggregator`  
`struct FTagContainerAggregator`  
_L1558-1619_
- reflection: `USTRUCT()`
- desc: Structure used to combine tags from different sources during effect execution
- L1562 _public function_ `FTagContainerAggregator() : CacheIsValid(false)`
- L1564 _public function_ `FTagContainerAggregator(FTagContainerAggregator&& Other) : CapturedActorTags(MoveTemp(Other.CapturedActorTags)) , CapturedSpecTags(MoveTemp(Other.CapturedSpecTags)) , CachedAggregator(MoveTemp(Other.CachedAggregator)) , CacheIsValid(Other.CacheIsValid)`
- L1572 _public function_ `FTagContainerAggregator(const FTagContainerAggregator& Other) : CapturedActorTags(Other.CapturedActorTags) , CapturedSpecTags(Other.CapturedSpecTags) , CachedAggregator(Other.CachedAggregator) , CacheIsValid(Other.CacheIsValid)`
- L1580 _public function_ `FTagContainerAggregator& operator=(FTagContainerAggregator&& Other)`
- L1589 _public function_ `FTagContainerAggregator& operator=(const FTagContainerAggregator& Other)`
- L1599 _public prototype_ `FGameplayTagContainer& GetActorTags();` — Returns tags from the source or target actor
- L1600 _public prototype_ `const FGameplayTagContainer& GetActorTags() const;`
- L1603 _public prototype_ `FGameplayTagContainer& GetSpecTags();` — Get tags that came from the effect spec
- L1604 _public prototype_ `const FGameplayTagContainer& GetSpecTags() const;`
- L1607 _public prototype_ `const FGameplayTagContainer* GetAggregatedTags() const;` — Returns combination of spec and actor tags
- L1612 _private member_ `FGameplayTagContainer CapturedActorTags;` — `UPROPERTY()`
- L1615 _private member_ `FGameplayTagContainer CapturedSpecTags;` — `UPROPERTY()`
- L1617 _private member_ `mutable FGameplayTagContainer CachedAggregator;`
- L1618 _private member_ `mutable bool CacheIsValid;`

#### struct `FGameplayEffectSpecHandle`  
`struct FGameplayEffectSpecHandle`  
_L1624-1660_
- reflection: `USTRUCT(BlueprintType)`
- desc: Allows blueprints to generate a GameplayEffectSpec once and then reference it by handle, to apply it multiple times/multiple targets.
- L1628 _public prototype_ `FGameplayEffectSpecHandle();`
- L1629 _public prototype_ `FGameplayEffectSpecHandle(FGameplayEffectSpec* DataPtr);`
- L1632 _public member_ `TSharedPtr<FGameplayEffectSpec> Data;` — Internal pointer to effect spec
- L1634 _public function_ `void Clear()`
- L1639 _public function_ `bool IsValid() const`
- L1644 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L1647 _public function_ `bool operator==(FGameplayEffectSpecHandle const& Other) const` — Comparison operator
- L1656 _public function_ `bool operator!=(FGameplayEffectSpecHandle const& Other) const` — Comparison operator

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FGameplayEffectSpecHandle> : public TStructOpsTypeTraitsBase2<FGameplayEffectSpecHandle>`  
_L1663-1671_
- inherits: `TStructOpsTypeTraitsBase2<FGameplayEffectSpecHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L1666-1670_

#### struct `FMinimalReplicationTagCountMap`  
`struct FMinimalReplicationTagCountMap`  
_L1676-1770_
- reflection: `USTRUCT()`
- desc: Map that stores count of tags, in a form that is optimized for replication
- L1680 _public function_ `FMinimalReplicationTagCountMap() : Owner(nullptr)`
- L1686 _public function_ `void AddTag(const FGameplayTag& Tag)`
- L1697 _public prototype_ `void RemoveTag(const FGameplayTag& Tag);`
- L1699 _public function_ `void AddTags(const FGameplayTagContainer& Container)`
- L1707 _public function_ `void RemoveTags(const FGameplayTagContainer& Container)`
- L1715 _public function_ `void SetTagCount(const FGameplayTag& Tag, int32 NewCount)`
- L1733 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L1735 _public member_ `TMap<FGameplayTag, int32> TagMap;`
- L1738 _public member_ `TObjectPtr<class UAbilitySystemComponent> Owner;` — `UPROPERTY()`
- L1741 _public function_ `bool operator==(FMinimalReplicationTagCountMap const& Other) const` — Comparison operator
- L1747 _public function_ `bool operator!=(FMinimalReplicationTagCountMap const& Other) const` — Comparison operator
- L1752 _public member_ `int32 MapID;`
- L1755 _public function_ `void SetRequireNonOwningNetConnection(bool b)` — If true, we will skip updating the Owner ASC if we replicate on a connection owned by the ASC
- L1757 _public prototype_ `void SetOwner(UAbilitySystemComponent* ASC);`
- L1760 _public prototype_ `void RemoveAllTags();` — Removes all tags that this container is granting
- L1766 _private member_ `bool bRequireNonOwningNetConnection = false;`
- L1767 _private member_ `TWeakObjectPtr<UNetConnection> LastConnection;`
- L1769 _private prototype_ `void UpdateOwnerTagMap();`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FMinimalReplicationTagCountMap> : public TStructOpsTypeTraitsBase2<FMinimalReplicationTagCountMap>`  
_L1773-1781_
- inherits: `TStructOpsTypeTraitsBase2<FMinimalReplicationTagCountMap>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L1776-1780_

#### Free symbols / members of external scopes

- L19 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L21 _macro_ `#define SKILL_SYSTEM_AGGREGATOR_DEBUG 1`
- L24 _macro_ `#define SKILL_AGG_DEBUG( Format, ... ) *FString::Printf(Format, ##__VA_ARGS__)`
- L26 _macro_ `#define SKILL_AGG_DEBUG( Format, ... ) nullptr`
- L39 _namespace_ `namespace UE`
- L39 _namespace_ `namespace Net` (scope `UE`)
- L47 _prototype_ `FString EGameplayModOpToString(int32 Type);` — Wrappers to convert enum to string. These are fairly slow
- L48 _prototype_ `FString EGameplayModToString(int32 Type);`
- L49 _prototype_ `FString EGameplayModEffectToString(int32 Type);`
- L50 _prototype_ `FString EGameplayCueEventToString(int32 Type);`
- L112 _namespace_ `namespace EGameplayModOp`
- L152 _namespace_ `namespace GameplayEffectUtilities`
- L161 _prototype_ `float GetModifierBiasByModifierOp(EGameplayModOp::Type ModOp);` (scope `GameplayEffectUtilities`) — Helper function to retrieve the modifier bias based upon modifier operation @param ModOp	Modifier operation to retrieve the modifier bias for @return Modifier bias for the specified operation
- L172 _prototype_ `float ComputeStackedModifierMagnitude(float BaseComputedMagnitude, int32 StackCount, EGameplayModOp::Type ModOp);` (scope `GameplayEffectUtilities`) — Helper function to compute the stacked modifier magnitude from a base magnitude, given a stack count and modifier operation @param BaseComputedMagnitude	Base magnitude to compute from @param StackCount			Stack count to use for the calculation @param ModOp					Modifier operation to use @return Computed modifier magnitude with stack count factored in
- L481 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon709d179a0103`)
- L482 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon709d179a0103`) — Necessary so that TSharedPtr<FHitResult> Data is copied around
- L801 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon709d179a0203`) — Necessary so that TSharedPtr<FGameplayEffectContext> Data is copied around
- L802 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon709d179a0203`)
- L803 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon709d179a0203`)
- L959 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon709d179a0303`)
- L965 _namespace_ `namespace EGameplayCueEvent`
- L984 _delegate_ `DECLARE_DELEGATE_OneParam(FOnGameplayAttributeEffectExecuted, struct FGameplayModifierEvaluatedData&);`
- L984 _prototype_ `DECLARE_DELEGATE_OneParam(FOnGameplayAttributeEffectExecuted, struct FGameplayModifierEvaluatedData&);`
- L985 _delegate_ `DECLARE_DELEGATE(FDeferredTagChangeDelegate);`
- L985 _prototype_ `DECLARE_DELEGATE(FDeferredTagChangeDelegate);`
- L987 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameplayEffectTagCountChanged, const FGameplayTag, int32);`
- L987 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameplayEffectTagCountChanged, const FGameplayTag, int32);`
- L988 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGivenActiveGameplayEffectRemoved, const FActiveGameplayEffect&);`
- L988 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGivenActiveGameplayEffectRemoved, const FActiveGameplayEffect&);`
- L990 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveGameplayEffectRemoved_Info, const FGameplayEffectRemovalInfo&);`
- L990 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActiveGameplayEffectRemoved_Info, const FGameplayEffectRemovalInfo&);`
- L991 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnActiveGameplayEffectStackChange, FActiveGameplayEffectHandle, int32 , int32 );`
- L991 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnActiveGameplayEffectStackChange, FActiveGameplayEffectHandle, int32 , int32 );`
- L992 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnActiveGameplayEffectTimeChange, FActiveGameplayEffectHandle, float , float );`
- L992 _prototype_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnActiveGameplayEffectTimeChange, FActiveGameplayEffectHandle, float , float );`
- L993 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActiveGameplayEffectInhibitionChanged, FActiveGameplayEffectHandle, bool );`
- L993 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActiveGameplayEffectInhibitionChanged, FActiveGameplayEffectHandle, bool );`
- L1005 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameplayAttributeChange, float, const FGameplayEffectModCallbackData*);` — This is deprecated, use FOnGameplayAttributeValueChange
- L1005 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnGameplayAttributeChange, float, const FGameplayEffectModCallbackData*);` — This is deprecated, use FOnGameplayAttributeValueChange
- L1024 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayAttributeValueChange, const FOnAttributeChangeData&);`
- L1024 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayAttributeValueChange, const FOnAttributeChangeData&);`
- L1026 _delegate_ `DECLARE_DELEGATE_RetVal(FGameplayTagContainer, FGetGameplayTags);`
- L1026 _prototype_ `DECLARE_DELEGATE_RetVal(FGameplayTagContainer, FGetGameplayTags);`
- L1028 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(FOnGameplayEffectTagCountChanged&, FRegisterGameplayTagChangeDelegate, FGameplayTag);`
- L1028 _prototype_ `DECLARE_DELEGATE_RetVal_OneParam(FOnGameplayEffectTagCountChanged&, FRegisterGameplayTagChangeDelegate, FGameplayTag);`
- L1032 _namespace_ `namespace EGameplayTagEventType`
- L1423 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anon709d179a0403`)
- L1667 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon709d179a0503`)
- L1668 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon709d179a0503`)
- L1669 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon709d179a0503`)
- L1777 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anon709d179a0603`)
- L1778 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon709d179a0603`)
- L1779 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon709d179a0603`)
- L1783 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnExternalGameplayModifierDependencyChange);`
- L1783 _prototype_ `DECLARE_MULTICAST_DELEGATE(FOnExternalGameplayModifierDependencyChange);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectUIData.h` (Public)


#### class `UGameplayEffectUIData`  
`class UGameplayEffectUIData : public UGameplayEffectComponent`  
_L16-19_
- reflection: `UCLASS(Blueprintable, Abstract, EditInlineNew, CollapseCategories, MinimalAPI)`
- inherits: `UGameplayEffectComponent`
- desc: UGameplayEffectUIData Base class to provide game-specific data about how to describe a Gameplay Effect in the UI. Subclass with data to use in your game. In Unreal Engine 5.3, this now derives from UGameplayEffectComponent so you can use it directly as a GameplayEffectComponent.

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayEffectUIData_TextOnly.h` (Public)


#### class `UGameplayEffectUIData_TextOnly`  
`class UGameplayEffectUIData_TextOnly : public UGameplayEffectUIData`  
_L15-22_
- reflection: `UCLASS(DisplayName="UI Data (Text Only)", MinimalAPI)`
- inherits: `UGameplayEffectUIData`
- desc: UI data that contains only text. This is mostly used as an example of a subclass of UGameplayEffectUIData. If your game needs only text, this is a reasonable class to use. To include more data, make a custom subclass of UGameplayEffectUIData.
- L21 _public member_ `FText Description;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Data, meta = (MultiLine = "true"))`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayModMagnitudeCalculation.h` (Public)


#### class `UGameplayModMagnitudeCalculation`  
`class UGameplayModMagnitudeCalculation : public UGameplayEffectCalculation`  
_L15-164_
- reflection: `UCLASS(BlueprintType, Blueprintable, Abstract, MinimalAPI)`
- inherits: `UGameplayEffectCalculation`
- desc: Class used to perform custom gameplay effect modifier calculations, either via blueprint or native code
- L30 _public prototype_ `float CalculateBaseMagnitude(const FGameplayEffectSpec& Spec) const;` — `UFUNCTION(BlueprintNativeEvent, Category="Calculation")` — Calculate the base magnitude of the gameplay effect modifier, given the specified spec. Note that the owning spec def can still modify this base value with a coeffecient and pre/post multiply adds. see FCustomCalculationBasedFloat::CalculateMagnitude for details. @param Spec	Gameplay effect spec to use to calculate the magnitude with @return Computed magnitude of the modifier
- L42 _public prototype_ `virtual FOnExternalGameplayModifierDependencyChange* GetExternalModifierDependencyMulticast(const FGameplayEffectSpec& Spec, UWorld* World) const;` — If the magnitude resultant from the custom calculation depends on game code-specific conditions that are not under the purview of the ability system, this method should be overridden to provide a multicast delegate that will fire when the reliant conditions change, so that the magnitude can be recalculated and updated. @param Spec	Gameplay effect spec that is requesting the delegate @param World	UWorld that is requesting the delegate @return Multicast delegate that will fire when this calculation's external dependencies change, if any
- L45 _public prototype_ `bool ShouldAllowNonNetAuthorityDependencyRegistration() const;` — Simple accessor to bAllowNonNetAuthorityDependencyRegistration with some validation: Read the comment on that variable for usage!!!
- L50 _protected prototype_ `bool GetCapturedAttributeMagnitude(const FGameplayEffectAttributeCaptureDefinition& Def, const FGameplayEffectSpec& Spec, const FAggregatorEvaluateParameters& EvaluationParameters, OUT float& Magnitude) const;` — Convenience method to get attribute magnitude during a CalculateMagnitude call
- L67 _protected member_ `bool bAllowNonNetAuthorityDependencyRegistration;` — `UPROPERTY(EditDefaultsOnly, Category=ExternalDependencies, AdvancedDisplay)` — Whether the calculation allows non-net authorities to register the external dependency multi-cast delegate or not; Effectively whether clients are allowed to perform the custom calculation themselves or not @Note:	This is an advanced use case that should only be enabled under very specific circumstances. This is designed for games that are utilizing network dormancy and may want to trust the client to update non-gameplay critical attributes client-side without causing a network dormancy flush. Usage of this flag is *NOT* compatible with attribute capture within the calculation and will trigger an ensure if used in tandem. Clients are incapable of performing custom calculations that require attribute captures. In general, if your game is not using network dormancy, this should always remain disabled. @Note:	If enabling this for a custom calculation, be sure that the external delegate is sourced from something guaranteed to be on the client to avoid timing issues. As an example, binding to a delegate on a GameState is potentially unreliable, as the client reference to that actor may not be available during registration.
- L79 _protected prototype_ `float K2_GetCapturedAttributeMagnitude(const FGameplayEffectSpec& EffectSpec, FGameplayAttribute Attribute, const FGameplayTagContainer& SourceTags, const FGameplayTagContainer& TargetTags) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Ability|GameplayEffect", meta=(DisplayName="Get Captured Attribute Magnitude", ScriptName="GetCapturedAttributeMagnitude"))` — Gets the captured magnitude value for the given Attribute For this to work correctly, the Attribute needs to be added to the Relevant Attributes to Capture array @param EffectSpec The Gameplay Effect Spec to get the info from @param Attribute The attribute to query @return The magnitude value if found, zero otherwise
- L90 _protected prototype_ `float GetSetByCallerMagnitudeByTag(const FGameplayEffectSpec& EffectSpec, const FGameplayTag& Tag) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Ability|GameplayEffect")` — Extracts the Set by Caller Magnitude from a Gameplay Effect Spec @param EffectSpec The Gameplay Effect Spec to get the info from @param Tag The effect tag to query @return The magnitude value if found, zero otherwise
- L101 _protected prototype_ `float GetSetByCallerMagnitudeByName(const FGameplayEffectSpec& EffectSpec, const FName& MagnitudeName) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Ability|GameplayEffect")` — Extracts the Set by Caller Magnitude from a Gameplay Effect Spec @param EffectSpec The Gameplay Effect Spec to get the info from @param MagnitudeName The effect name to query @return The magnitude value if found, zero otherwise
- L111 _protected prototype_ `FGameplayTagContainer GetSourceAggregatedTags(const FGameplayEffectSpec& EffectSpec) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Ability|GameplayEffect")` — Copies and returns the source aggregated tags from a Gameplay Effect Spec @param EffectSpec The Gameplay Effect Spec to get the info from @return Gameplay Tag Container with the copied tags. The container will be empty if no captured source tags exist.
- L121 _protected prototype_ `const FGameplayTagContainer& GetSourceActorTags(const FGameplayEffectSpec& EffectSpec) const;` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the source actor tags from a Gameplay Effect Spec @param EffectSpec The Gameplay Effect Spec to get the info from @return Gameplay Tag Container with the copied tags. The container will be empty if no captured source tags exist.
- L131 _protected prototype_ `const FGameplayTagContainer& GetSourceSpecTags(const FGameplayEffectSpec& EffectSpec) const;` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the source spec tags from a Gameplay Effect Spec @param EffectSpec The Gameplay Effect Spec to get the info from @return Gameplay Tag Container with the copied tags. The container will be empty if no captured source tags exist.
- L141 _protected prototype_ `FGameplayTagContainer GetTargetAggregatedTags(const FGameplayEffectSpec& EffectSpec) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "Ability|GameplayEffect")` — Copies and returns the target aggregated tags from a Gameplay Effect Spec @param EffectSpec The Gameplay Effect Spec to get the info from @return Gameplay Tag Container with the copied tags. The container will be empty if no captured source tags exist.
- L152 _protected prototype_ `const FGameplayTagContainer& GetTargetActorTags(const FGameplayEffectSpec& EffectSpec) const;` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the target actor tags from a Gameplay Effect Spec Useful for Modifier Magnitude Calculations @param EffectSpec The Gameplay Effect Spec to get the info from @return Gameplay Tag Container with the copied tags. The container will be empty if no captured source tags exist.
- L163 _protected prototype_ `const FGameplayTagContainer& GetTargetSpecTags(const FGameplayEffectSpec& EffectSpec) const;` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayEffect")` — Returns the target spec tags from a Gameplay Effect Spec Useful for Modifier Magnitude Calculations @param EffectSpec The Gameplay Effect Spec to get the info from @return Gameplay Tag Container with the copied tags. The container will be empty if no captured source tags exist.

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayPrediction.h` (Public)


#### struct `FPredictionKey`  
`struct FPredictionKey`  
_L296-414_
- reflection: `USTRUCT()`
- L300 _public typedef_ `typedef int16 KeyType;`
- L301 _public prototype_ `FPredictionKey() = default;`
- L305 _public member_ `int16 Current = 0;` — `UPROPERTY()` — The unique ID of this prediction key
- L309 _public member_ `int16 Base = 0;` — `UPROPERTY(NotReplicated)` — If non 0, the original prediction key this was created from (in a dependency chain)
- L313 _public member_ `bool bIsServerInitiated = false;` — `UPROPERTY()` — True if this was created as a server initiated activation key, used to identify server activations but cannot be used for prediction
- L316 _public prototype_ `static FPredictionKey CreateNewPredictionKey(const UAbilitySystemComponent*);` — Construct a new prediction key with no dependencies
- L319 _public prototype_ `static FPredictionKey CreateNewServerInitiatedKey(const UAbilitySystemComponent*);` — Construct a new server initiation key, for abilities activated on the server
- L322 _public prototype_ `void GenerateDependentPredictionKey();` — Create a new dependent prediction key: keep our existing base or use the current key as the base.
- L325 _public prototype_ `FPredictionKeyEvent& NewRejectedDelegate();` — Creates new delegate called only when this key is rejected.
- L328 _public prototype_ `FPredictionKeyEvent& NewCaughtUpDelegate();` — Creates new delegate called only when replicated state catches up to this key.
- L331 _public prototype_ `void NewRejectOrCaughtUpDelegate(FPredictionKeyEvent Event);` — Add a new delegate that is called if the key is rejected or caught up to.
- L333 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);`
- L336 _public function_ `bool IsValidKey() const` — A key is valid if it's non-zero, prediction keys for other clients will serialize down as 0 and be invalid
- L342 _public function_ `bool IsLocalClientKey() const` — A key was generated by the local client if it's valid and not a server key, prediction keys for other clients will serialize down as 0 and be invalid
- L348 _public function_ `bool IsServerInitiatedKey() const` — True if this was created as a server initiated activation key, used to identify server activations but cannot be used for prediction
- L354 _public function_ `bool IsValidForMorePrediction() const` — Can this key be used for more predictive actions, or has it already been sent off to the server?
- L360 _public function_ `bool WasReceived() const` — Was this PredictionKey received from a NetSerialize or created locally?
- L365 _public function_ `bool WasLocallyGenerated() const`
- L370 _public function_ `bool operator==(const FPredictionKey& Other) const`
- L376 _public function_ `bool operator!=(const FPredictionKey& Other) const`
- L381 _public function_ `FString ToString() const`
- L392 _public function_ `uint64 GetPredictiveConnectionKey() const`
- L404 _private prototype_ `void GenerateNewPredictionKey();`
- L406 _private function_ `explicit FPredictionKey(int32 Key) : Current(static_cast<KeyType>(Key))`
- L413 _private member_ `FObjectKey PredictiveConnectionObjectKey;` — On the server, uniquely identifies network connection this was serialized on/from.  See NetSerialize for additional information.

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FPredictionKey> : public TStructOpsTypeTraitsBase2<FPredictionKey>`  
_L418-425_
- inherits: `TStructOpsTypeTraitsBase2<FPredictionKey>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L421-424_

#### struct `FPredictionKeyDelegates`  
`struct FPredictionKeyDelegates`  
_L435-467_
- L451 _public member_ `TMap<FPredictionKey::KeyType, FDelegates> DelegateMap;`
- L453 _public prototype_ `static FPredictionKeyDelegates& Get();`
- L455 _public prototype_ `static FPredictionKeyEvent& NewRejectedDelegate(FPredictionKey::KeyType Key);`
- L456 _public prototype_ `static FPredictionKeyEvent& NewCaughtUpDelegate(FPredictionKey::KeyType Key);`
- L457 _public prototype_ `static void NewRejectOrCaughtUpDelegate(FPredictionKey::KeyType Key, FPredictionKeyEvent NewEvent);`
- L459 _public prototype_ `static void BroadcastRejectedDelegate(FPredictionKey::KeyType Key);`
- L460 _public prototype_ `static void BroadcastCaughtUpDelegate(FPredictionKey::KeyType Key);`
- L462 _public prototype_ `static void Reject(FPredictionKey::KeyType Key);`
- L463 _public prototype_ `static void CatchUpTo(FPredictionKey::KeyType Key);`
- L465 _public prototype_ `static void AddDependency(FPredictionKey::KeyType ThisKey, FPredictionKey::KeyType DependsOn);`

#### struct `FPredictionKeyDelegates::FDelegates`  
`struct FDelegates`  
_L440-449_
- L445 _public member_ `TArray<FPredictionKeyEvent> RejectedDelegates;` — This delegate is called if the prediction key is associated with an action that is explicitly rejected by the server.
- L448 _public member_ `TArray<FPredictionKeyEvent> CaughtUpDelegates;` — This delegate is called when replicated state has caught up with the prediction key. Doesnt imply rejection or acceptance.

#### struct `FScopedPredictionWindow`  
`struct FScopedPredictionWindow`  
_L479-504_
- L485 _public prototype_ `FScopedPredictionWindow(UAbilitySystemComponent* AbilitySystemComponent, FPredictionKey InPredictionKey, bool InSetReplicatedPredictionKey = true);` — To be called on server when a new prediction key is received from the client (In an RPC). InSetReplicatedPredictionKey should be set to false in cases where we want a scoped prediction key but have already repped the prediction key. (For example, cached target data will restore the prediction key that the TD was sent with, but this key was already repped down as confirmed when received)
- L488 _public prototype_ `FScopedPredictionWindow(UAbilitySystemComponent* AbilitySystemComponent, bool CanGenerateNewKey=true);` — To be called in the callsite where the predictive code will take place. This generates a new PredictionKey and acts as a synchonization point between client and server for that key.
- L490 _public prototype_ `~FScopedPredictionWindow();`
- L494 _private member_ `TWeakObjectPtr<UAbilitySystemComponent> Owner;`
- L495 _private member_ `bool ClearScopedPredictionKey;`
- L496 _private member_ `bool SetReplicatedPredictionKey;`
- L497 _private member_ `FPredictionKey RestoreKey;`
- L500 _private member_ `FOnSendRPC DebugSavedOnSendRPC;`
- L501 _private member_ `TWeakObjectPtr<UNetDriver> DebugSavedNetDriver;`
- L502 _private member_ `TOptional<FPredictionKey::KeyType> DebugBaseKeyOfChain;`

#### enum `EGasPredictionKeyResult`  
`enum class EGasPredictionKeyResult : uint8`  
_L509-519_
- desc: Possible results when evaluating how to deal with an FPredictionKey
- L512 _public enumerator_ `SilentlyDrop` — Silently drop the key (don't acknowledge it at all)
- L515 _public enumerator_ `Accept` — Accept the key (e.g. server acknowledges the event happened)
- L518 _public enumerator_ `Reject` — Reject the key (e.g. server says the event never happened)

#### struct `FScopedDiscardPredictions`  
`struct FScopedDiscardPredictions`  
_L527-547_
- desc: Discard the predictions that occur within this window. This is useful in a case where you don't intend to send a chain of generated events (FPredictionKeys) to the server. For example, we use this in a case where we want to play a Montage locally, and we notify the server unreliably (i.e. it is an optional event). Note: Nothing stops something within this scope from creating a valid key, then sending that valid key to the server.  This is meant for generated keys that aren't already going to be sent.
- L530 _public prototype_ `explicit FScopedDiscardPredictions(UAbilitySystemComponent* AbilitySystemComponent, EGasPredictionKeyResult HowToHandlePredictions = EGasPredictionKeyResult::SilentlyDrop);` — Pass in the AbilitySystemComponent to discard predictions on.  Optionally, if we want to do something other than just Drop the prediction events you can override that.
- L533 _public prototype_ `~FScopedDiscardPredictions();` — When the scope ends, we will perform the final drop/ack/nack of the prediction chain
- L537 _private member_ `TWeakObjectPtr<UAbilitySystemComponent> Owner;` — Weak pointer to the 'Owning' ASC.  If this ends up being invalid/null we don't do anything.
- L540 _private member_ `FPredictionKey KeyToRestoreOnOwner;` — The key that we're going to restore on the Owner
- L543 _private member_ `EGasPredictionKeyResult PredictionKeyChainResult;` — How we're going to handle the resulting chain of predictions
- L546 _private member_ `FPredictionKey BaseKeyToAck;` — This is the key that we're going to eventually acknowledge according to PredictionKeyChainResult

#### struct `FReplicatedPredictionKeyItem`  
`struct FReplicatedPredictionKeyItem : public FFastArraySerializerItem`  
_L570-592_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializerItem`
- L575 _public prototype_ `FReplicatedPredictionKeyItem();` — As we know that FReplicatedPredictionKeyItem is well behaved and does not leak outside of FReplicatedPredictionKeyMap we allow ReplicationID and ReplicationKey to be copied around to avoid issues when instantiating from archetype or CDO
- L576 _public prototype_ `FReplicatedPredictionKeyItem(const FReplicatedPredictionKeyItem& Other);`
- L577 _public prototype_ `FReplicatedPredictionKeyItem(FReplicatedPredictionKeyItem&& Other);`
- L578 _public prototype_ `FReplicatedPredictionKeyItem& operator=(FReplicatedPredictionKeyItem&& other);`
- L579 _public prototype_ `FReplicatedPredictionKeyItem& operator=(const FReplicatedPredictionKeyItem& other);`
- L582 _public member_ `FPredictionKey PredictionKey;` — `UPROPERTY()`
- L584 _public function_ `void PostReplicatedAdd(const struct FReplicatedPredictionKeyMap &InArray)`
- L585 _public function_ `void PostReplicatedChange(const struct FReplicatedPredictionKeyMap &InArray)`
- L587 _public function_ `FString GetDebugString()`
- L591 _private prototype_ `void OnRep(const struct FReplicatedPredictionKeyMap& InArray);`

#### struct `FReplicatedPredictionKeyMap`  
`struct FReplicatedPredictionKeyMap : public FFastArraySerializer`  
_L595-613_
- reflection: `USTRUCT()`
- inherits: `FFastArraySerializer`
- L599 _public prototype_ `FReplicatedPredictionKeyMap();`
- L602 _public member_ `TArray<FReplicatedPredictionKeyItem> PredictionKeys;` — `UPROPERTY()`
- L604 _public prototype_ `void ReplicatePredictionKey(FPredictionKey Key);`
- L606 _public prototype_ `bool NetDeltaSerialize(FNetDeltaSerializeInfo & DeltaParms);`
- L608 _public prototype_ `FString GetDebugString() const;`
- L610 _public member_ `static const int32 KeyRingBufferSize;`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits< FReplicatedPredictionKeyMap > : public TStructOpsTypeTraitsBase2< FReplicatedPredictionKeyMap >`  
_L616-622_
- inherits: `TStructOpsTypeTraitsBase2<FReplicatedPredictionKeyMap>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L619-621_

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Net` (scope `UE`)
- L20 _delegate_ `DECLARE_DELEGATE(FPredictionKeyEvent);`
- L20 _prototype_ `DECLARE_DELEGATE(FPredictionKeyEvent);`
- L386 _function_ `friend uint32 GetTypeHash(const FPredictionKey& InKey)`
- L422 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anon6d948ac90103`)
- L423 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anon6d948ac90103`)
- L620 _enumerator_ `WithNetDeltaSerializer = true` (scope `TStructOpsTypeTraits::__anon6d948ac90203`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/GameplayTagResponseTable.h` (Public)


#### struct `FGameplayTagReponsePair`  
`struct FGameplayTagReponsePair`  
_L19-38_
- reflection: `USTRUCT()`
- L25 _public member_ `FGameplayTag Tag;` — `UPROPERTY(EditAnywhere, Category="Response")` — Tag that triggers this response
- L29 _public member_ `TSubclassOf<UGameplayEffect> ResponseGameplayEffect;` — `UPROPERTY()` — Deprecated. Replaced with ResponseGameplayEffects
- L33 _public member_ `TArray<TSubclassOf<UGameplayEffect> > ResponseGameplayEffects;` — `UPROPERTY(EditAnywhere, Category="Response")` — The GameplayEffects to apply in reponse to the tag
- L37 _public member_ `int32 SoftCountCap = 0;` — `UPROPERTY(EditAnywhere, Category="Response", meta=(ClampMin = "0"))` — The max "count" this response can achieve. This will not prevent counts from being applied, but will be used when calculating the net count of a tag. 0=no cap.

#### struct `FGameplayTagResponseTableEntry`  
`struct FGameplayTagResponseTableEntry`  
_L41-52_
- reflection: `USTRUCT()`
- L47 _public member_ `FGameplayTagReponsePair Positive;` — `UPROPERTY(EditAnywhere, Category="Response")` — Tags that count as "positive" toward to final response count. If the overall count is positive, this ResponseGameplayEffect is applied.
- L51 _public member_ `FGameplayTagReponsePair Negative;` — `UPROPERTY(EditAnywhere, Category="Response")` — Tags that count as "negative" toward to final response count. If the overall count is negative, this ResponseGameplayEffect is applied.

#### class `UGameplayTagReponseTable`  
`class UGameplayTagReponseTable : public UDataAsset`  
_L62-107_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UDataAsset`
- desc: A data driven table for applying gameplay effects based on tag count. This allows designers to map a "tag count" -> "response Gameplay Effect" relationship. For example, "for every count of "Status.Haste" I get 1 level of GE_Response_Haste. This class facilitates building this table and automatically registering and responding to tag events on the ability system component.
- L67 _private member_ `TArray<FGameplayTagResponseTableEntry> Entries;` — `UPROPERTY(EditAnywhere, Category="Response")`
- L72 _private prototype_ `void RegisterResponseForEvents(UAbilitySystemComponent* ASC);` — Registers for tag events for the given ability system component. Note this will happen to every spawned ASC, we may want to allow games to limit what classe this is called on, or potentially build into the table class restrictions for each response entry.
- L74 _private prototype_ `virtual void PostLoad() override;`
- L79 _protected prototype_ `void TagResponseEvent(const FGameplayTag Tag, int32 NewCount, UAbilitySystemComponent* ASC, int32 idx);` — `UFUNCTION()`
- L82 _protected member_ `mutable FGameplayEffectQuery Query;` — Temporary structs to avoid extra heap allocations every time we recalculate tag count
- L84 _protected function_ `FGameplayEffectQuery& MakeQuery(const FGameplayTag& Tag) const`
- L98 _protected member_ `TMap< TWeakObjectPtr<UAbilitySystemComponent>, TArray< FGameplayTagResponseAppliedInfo> > RegisteredASCs;`
- L100 _protected member_ `float LastASCPurgeTime;`
- L102 _protected prototype_ `void Remove(UAbilitySystemComponent* ASC, TArray<FActiveGameplayEffectHandle>& Handles);`
- L104 _protected prototype_ `void AddOrUpdate(UAbilitySystemComponent* ASC, const TArray<TSubclassOf<UGameplayEffect> >& ResponseGameplayEffects, int32 TotalCount, TArray<FActiveGameplayEffectHandle>& Handles);`
- L106 _protected prototype_ `int32 GetCount(const FGameplayTagReponsePair& Pair, UAbilitySystemComponent* ASC) const;`

#### struct `UGameplayTagReponseTable::FGameplayTagResponseAppliedInfo`  
`struct FGameplayTagResponseAppliedInfo`  
_L92-96_
- L94 _public member_ `TArray<FActiveGameplayEffectHandle> PositiveHandles;`
- L95 _public member_ `TArray<FActiveGameplayEffectHandle> NegativeHandles;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API GAMEPLAYABILITIES_API`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/ScalableFloat.h` (Public)


#### struct `FScalableFloat`  
`struct FScalableFloat`  
_L14-124_
- reflection: `USTRUCT(BlueprintType)`
- desc: Generic numerical value in the form Value * Curve[Level]
- L18 _public function_ `FScalableFloat() : Value(0.f) , LocalCachedCurveID(INDEX_NONE) , CachedCurve(nullptr)`
- L25 _public function_ `FScalableFloat(float InInitialValue) : Value(InInitialValue) , LocalCachedCurveID(INDEX_NONE) , CachedCurve(nullptr)`
- L32 _public prototype_ `~FScalableFloat() = default;`
- L38 _public member_ `float Value;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ScalableFloat)` — Raw value, is multiplied by curve
- L42 _private member_ `mutable int32 LocalCachedCurveID;` — Value of GetGlobalCachedCurveID when CachedCurve was set
- L47 _public member_ `FCurveTableRowHandle Curve;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ScalableFloat)` — Curve that is evaluated at a specific level. If found, it is multipled by Value
- L51 _public member_ `FDataRegistryType RegistryType;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ScalableFloat)` — Name of Data Registry containing curve to use. If set the RowName inside Curve is used as the item name
- L54 _public prototype_ `float GetValueAtLevel(float Level, const FString* ContextString = nullptr) const;` — Returns the scaled value at a given level
- L57 _public prototype_ `float GetValue(const FString* ContextString = nullptr) const;` — Returns the scaled value at level 0
- L60 _public prototype_ `bool AsBool(float Level = 0, const FString* ContextString = nullptr) const;` — Used when using a scalable float as a bool
- L63 _public prototype_ `int32 AsInteger(float Level = 0, const FString* ContextString = nullptr) const;` — Returns the value as an int32
- L66 _public prototype_ `bool EvaluateCurveAtLevel(float& OutValue, const FRealCurve*& OutCurve, float Level, const FString& ContextString, bool bWarnIfInvalid = true) const;` — Gets the value and possible curve at a given level, returning false if it failed to find a good value
- L69 _public function_ `bool IsStatic() const` — True if there is no curve lookup
- L75 _public prototype_ `void SetValue(float NewValue);` — Sets raw value
- L78 _public prototype_ `void SetScalingValue(float InCoeffecient, FName InRowName, UCurveTable * InTable);` — Overrides raw value and curve reference
- L81 _public function_ `float GetValueChecked() const` — Returns static value, only safe if this has no curve reference
- L88 _public prototype_ `FString ToSimpleString() const;` — Outputs human readable string
- L91 _public prototype_ `bool IsValid() const;` — Error checking: Returns false if this has an invalid curve reference but will not print warnings
- L95 _public prototype_ `bool IsValidWithWarnings(const FString& ContextString) const;` — `UE_DEPRECATED(5.6, "Use IsDataValid and manually output the errors")` — Error checking: Checks if float is valid and prints detailed warnings if not valid
- L99 _public prototype_ `EDataValidationResult IsDataValid(class FDataValidationContext& Context, const FString& PathName) const;` — Error checking must be performed by the owning class, then call this to get specific errors
- L103 _public prototype_ `bool operator==(const FScalableFloat& Other) const;` — Equality/Inequality operators
- L104 _public prototype_ `bool operator!=(const FScalableFloat& Other) const;`
- L107 _public prototype_ `FScalableFloat& operator=(const FScalableFloat& Src);` — copy operator to prevent duplicate handles
- L110 _public prototype_ `bool SerializeFromMismatchedTag(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot);` — Used to upgrade a float or int8/int16/int32 property into an FScalableFloat
- L111 _public prototype_ `void PostSerialize(const FArchive& Ar);`
- L115 _private member_ `mutable const FRealCurve* CachedCurve;` — Cached direct pointer to the RealCurve we should evaluate
- L118 _private function_ `void ClearCachedCurve() const` — Clear cached data

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FScalableFloat> : public TStructOpsTypeTraitsBase2<FScalableFloat>`  
_L127-135_
- inherits: `TStructOpsTypeTraitsBase2<FScalableFloat>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L131-134_

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API GAMEPLAYABILITIES_API`
- L132 _enumerator_ `WithStructuredSerializeFromMismatchedTag = true` (scope `TStructOpsTypeTraits::__anonba2ea1350103`)
- L133 _enumerator_ `WithPostSerialize = true` (scope `TStructOpsTypeTraits::__anonba2ea1350103`)
- L138 _macro_ `#define SCALABLEFLOAT_REPORTERROR(Scalable)\` — Macro to call IsValidWithWarnings with a correct error info. Assumed to be called within a UObject
- L142 _macro_ `#define SCALABLEFLOAT_REPORTERROR_WITHPATHNAME(Scalable, PathNameString)\` — Macro to call IsValidWithWarnings with a correct error info

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Sequencer/MovieSceneGameplayCueSections.h` (Public)


#### struct `FMovieSceneGameplayCueKey`  
`struct FMovieSceneGameplayCueKey`  
_L19-75_
- reflection: `USTRUCT()`
- L23 _public function_ `FMovieSceneGameplayCueKey() : Location(ForceInitToZero) , Normal(ForceInitToZero) , NormalizedMagnitude(0.0f) , PhysicalMaterial(nullptr) , GameplayEffectLevel(1) , AbilityLevel(1) , bAttachToBinding(true)`
- L34 _public member_ `FGameplayCueTag Cue;` — `UPROPERTY(EditAnywhere, Category="Gameplay Cue")`
- L38 _public member_ `FVector Location;` — `UPROPERTY(EditAnywhere, Category="Position")` — Location cue took place at - relative to the attached component if applicable
- L42 _public member_ `FVector Normal;` — `UPROPERTY(EditAnywhere, Category="Position")` — Normal of impact that caused cue
- L46 _public member_ `FName AttachSocketName;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Position")` — When attached to a skeletal mesh component, specifies a socket to trigger the cue at
- L50 _public member_ `float NormalizedMagnitude;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Gameplay Cue", meta=(ClampMin=0.0, ClampMax=1.0))` — Magnitude of source gameplay effect, normalzed from 0-1. Use this for "how strong is the gameplay effect" (0=min, 1=,max)
- L54 _public member_ `FMovieSceneObjectBindingID Instigator;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Gameplay Cue")` — Instigator actor, the actor that owns the ability system component.
- L58 _public member_ `FMovieSceneObjectBindingID EffectCauser;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Gameplay Cue")` — The physical actor that actually did the damage, can be a weapon or projectile
- L62 _public member_ `TObjectPtr<const UPhysicalMaterial> PhysicalMaterial;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Gameplay Cue")` — PhysMat of the hit, if there was a hit.
- L66 _public member_ `int32 GameplayEffectLevel;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Gameplay Cue")` — The level of that GameplayEffect
- L70 _public member_ `int32 AbilityLevel;` — `UPROPERTY(EditAnywhere, AdvancedDisplay, Category="Gameplay Cue")` — If originating from an ability, this will be the level of that ability
- L74 _public member_ `bool bAttachToBinding;` — `UPROPERTY(EditAnywhere, Category="Position")` — Attach the gameplay cue to the track's bound object in sequencer

#### struct `FMovieSceneGameplayCueChannel`  
`struct FMovieSceneGameplayCueChannel : public FMovieSceneChannel`  
_L79-129_
- reflection: `USTRUCT()`
- inherits: `FMovieSceneChannel`
- L88 _public function_ `inline TMovieSceneChannelData<FMovieSceneGameplayCueKey> GetData()` — Access a mutable interface for this channel's data @return An object that is able to manipulate this channel's data
- L98 _public function_ `inline TMovieSceneChannelData<const FMovieSceneGameplayCueKey> GetData() const` — Access a constant interface for this channel's data @return An object that is able to interrogate this channel's data
- L106 _public prototype_ `virtual void GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles) override;`
- L107 _public prototype_ `virtual void GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes) override;`
- L108 _public prototype_ `virtual void SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes) override;`
- L109 _public prototype_ `virtual void DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles) override;`
- L110 _public prototype_ `virtual void DeleteKeys(TArrayView<const FKeyHandle> InHandles) override;`
- L111 _public prototype_ `virtual void DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore) override;`
- L112 _public prototype_ `virtual void RemapTimes(const UE::MovieScene::IRetimingInterface& Retimer) override;`
- L113 _public prototype_ `virtual TRange<FFrameNumber> ComputeEffectiveRange() const override;`
- L114 _public prototype_ `virtual int32 GetNumKeys() const override;`
- L115 _public prototype_ `virtual void Reset() override;`
- L116 _public prototype_ `virtual void Offset(FFrameNumber DeltaPosition) override;`
- L122 _private member_ `TArray<FFrameNumber> KeyTimes;` — `UPROPERTY(meta=(KeyTimes))` — Array of times for each key
- L126 _private member_ `TArray<FMovieSceneGameplayCueKey> KeyValues;` — `UPROPERTY(meta=(KeyValues), AssetRegistrySearchable)` — Array of values that correspond to each key time
- L128 _private member_ `FMovieSceneKeyHandleMap KeyHandles;`

#### struct `TMovieSceneChannelTraits`  
`template<> struct TMovieSceneChannelTraits<FMovieSceneGameplayCueChannel> : TMovieSceneChannelTraitsBase<FMovieSceneGameplayCueChannel>`  
_L132-135_
- inherits: `TMovieSceneChannelTraitsBase<FMovieSceneGameplayCueChannel>`

#### enum `TMovieSceneChannelTraits::(anonymous)`  
`enum`  
_L134-134_

#### class `UMovieSceneGameplayCueTriggerSection`  
`class UMovieSceneGameplayCueTriggerSection : public UMovieSceneHookSection`  
_L156-173_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneHookSection`
- desc: Implements a movie scene section that triggers gameplay cues
- L163 _public prototype_ `UMovieSceneGameplayCueTriggerSection(const FObjectInitializer&);`
- L167 _private prototype_ `virtual EMovieSceneChannelProxyType CacheChannelProxy() override;`
- L168 _private prototype_ `virtual void Trigger(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L169 _private function_ `virtual TArrayView<const FFrameNumber> GetTriggerTimes() const`
- L172 _private member_ `FMovieSceneGameplayCueChannel Channel;` — `UPROPERTY(AssetRegistrySearchable)`

#### class `UMovieSceneGameplayCueSection`  
`class UMovieSceneGameplayCueSection : public UMovieSceneHookSection`  
_L180-197_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneHookSection`
- desc: Implements a movie scene section that triggers gameplay cues
- L187 _public prototype_ `UMovieSceneGameplayCueSection(const FObjectInitializer&);`
- L191 _private prototype_ `virtual void Begin(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L192 _private prototype_ `virtual void Update(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L193 _private prototype_ `virtual void End(TSharedRef<FSharedPlaybackState> SharedPlaybackState, const UE::MovieScene::FEvaluationHookParams& Params) const override;`
- L196 _private member_ `FMovieSceneGameplayCueKey Cue;` — `UPROPERTY(EditAnywhere, AssetRegistrySearchable, Category="Cue", meta=(ShowOnlyInnerProperties))`

#### Free symbols / members of external scopes

- L134 _enumerator_ `enum { SupportsDefaults = false };` (scope `TMovieSceneChannelTraits::__anon135002250103`)
- L137 _function_ `inline bool EvaluateChannel(const FMovieSceneGameplayCueChannel* InChannel, FFrameTime InTime, FMovieSceneGameplayCueKey& OutValue)`
- L143 _namespace_ `namespace MovieSceneClipboard`
- L145 _function_ `template<> inline FName GetKeyTypeName<FMovieSceneGameplayCueKey>()` (scope `MovieSceneClipboard`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Sequencer/MovieSceneGameplayCueTrack.h` (Public)


#### class `UMovieSceneGameplayCueTrack`  
`class UMovieSceneGameplayCueTrack : public UMovieSceneNameableTrack`  
_L20-65_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UMovieSceneNameableTrack`
- desc: Implements a movie scene track that triggers gameplay cues
- L28 _public function_ `UMovieSceneGameplayCueTrack()` — Default constructor.
- L35 _public member_ `static FMovieSceneGameplayCueEvent OnHandleCueEvent;`
- L39 _public prototype_ `static void SetSequencerTrackHandler(FMovieSceneGameplayCueEvent InGameplayCueTrackHandler);` — `UFUNCTION(BlueprintCallable, Category = "Ability|GameplayCue")` — Override the default function for invoking Gameplay Cues from sequencer tracks
- L45 _public prototype_ `virtual void AddSection(UMovieSceneSection& Section) override;`
- L46 _public prototype_ `virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;`
- L47 _public prototype_ `virtual UMovieSceneSection* CreateNewSection() override;`
- L48 _public prototype_ `virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;`
- L49 _public prototype_ `virtual bool HasSection(const UMovieSceneSection& Section) const override;`
- L50 _public prototype_ `virtual bool IsEmpty() const override;`
- L51 _public prototype_ `virtual void RemoveAllAnimationData() override;`
- L52 _public prototype_ `virtual void RemoveSection(UMovieSceneSection& Section) override;`
- L53 _public prototype_ `virtual void RemoveSectionAt(int32 SectionIndex) override;`
- L54 _public function_ `virtual bool SupportsMultipleRows() const override`
- L57 _public prototype_ `virtual FText GetDefaultDisplayName() const override;`
- L64 _private member_ `TArray<TObjectPtr<UMovieSceneSection>> Sections;` — `UPROPERTY()` — The track's sections.

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FMovieSceneGameplayCueEvent, AActor*, Target, FGameplayTag, GameplayTag, const FGameplayCueParameters&, Parameters, EGameplayCueEvent::Type, Event);`
- L14 _prototype_ `DECLARE_DYNAMIC_DELEGATE_FourParams(FMovieSceneGameplayCueEvent, AActor*, Target, FGameplayTag, GameplayTag, const FGameplayCueParameters&, Parameters, EGameplayCueEvent::Type, Event);`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/GameplayAbilityRepAnimMontageNetSerializer.h` (Public)


#### struct `FGameplayAbilityRepAnimMontageNetSerializerConfig`  
`struct FGameplayAbilityRepAnimMontageNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/GameplayAbilityTargetDataHandleNetSerializer.h` (Public)


#### Free symbols / members of external scopes

- L8 _namespace_ `namespace UE`
- L8 _namespace_ `namespace Net` (scope `UE`)
- L15 _prototype_ `void InitGameplayAbilityTargetDataHandleNetSerializerTypeCache();`

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/GameplayAbilityTargetingLocationInfoNetSerializer.h` (Public)


#### struct `FGameplayAbilityTargetingLocationInfoNetSerializerConfig`  
`struct FGameplayAbilityTargetingLocationInfoNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/GameplayEffectContextHandleNetSerializer.h` (Public)


#### struct `FGameplayEffectContextHandleNetSerializerConfig`  
`struct FGameplayEffectContextHandleNetSerializerConfig : public FPolymorphicStructNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FPolymorphicStructNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _prototype_ `void InitGameplayEffectContextHandleNetSerializerTypeCache();`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/GameplayEffectContextNetSerializer.h` (Public)


#### struct `FGameplayEffectContextNetSerializerConfig`  
`struct FGameplayEffectContextNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)
- L18 _function_ `constexpr SIZE_T GetGameplayEffectContextNetSerializerSafeQuantizedSize()` (scope `UE::Net`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/GameplayTagCountContainerNetSerializer.h` (Public)


#### struct `FGameplayTagCountContainerNetSerializerConfig`  
`struct FGameplayTagCountContainerNetSerializerConfig : public FNetSerializerConfig`  
_L17-20_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### struct `FNetGameplayTagCountContainerStateForNetSerialize`  
`struct FNetGameplayTagCountContainerStateForNetSerialize`  
_L23-36_
- reflection: `USTRUCT()`
- L28 _public member_ `TArray<FGameplayTagCountItem> TagStates;` — `UPROPERTY()`
- L30 _public prototype_ `void CopyFromTagCountContainer(const FGameplayTagCountContainer& Container);`
- L32 _public function_ `bool operator== (const FNetGameplayTagCountContainerStateForNetSerialize& Other) const`

#### Free symbols / members of external scopes

- L38 _namespace_ `namespace UE`
- L38 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/MinimalGameplayCueReplicationProxyNetSerializer.h` (Public)


#### struct `FMinimalGameplayCueReplicationProxyNetSerializerConfig`  
`struct FMinimalGameplayCueReplicationProxyNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/MinimalGameplayCueReplicationProxyReplicationFragment.h` (Public)


#### class `UE::Net::FMinimalGameplayCueReplicationProxyReplicationFragment`  
`class FMinimalGameplayCueReplicationProxyReplicationFragment : public FReplicationFragment`  
_L21-42_
- inherits: `FReplicationFragment`
- desc: ReplicationFragment implementation used for Iris backwards compatibility until there's a simple way to markup arbitrary members or declare replicated states in a different manner. That coupled with generic Iris ApplyState funcitonality and not serializing data into gameplay objects directly would make the need for the fragment and the custom serializer go away. Instead the custom logic would be handled in the ApplyState implementation. @note This is NOT what good looks like. Markup your data and avoid custom gameplay logic in serialization code.
- L24 _public prototype_ `FMinimalGameplayCueReplicationProxyReplicationFragment(EReplicationFragmentTraits InTraits, UObject* InOwner, const FReplicationStateDescriptor* InDescriptor);`
- L26 _public prototype_ `void Register(FFragmentRegistrationContext& Context);`
- L29 _protected prototype_ `virtual void ApplyReplicatedState(FReplicationStateApplyContext& Context) const override;`
- L30 _protected prototype_ `virtual bool PollReplicatedState(EReplicationFragmentPollFlags PollOption) override;`
- L31 _protected prototype_ `virtual void CallRepNotifies(FReplicationStateApplyContext& Context) override;`
- L32 _protected prototype_ `virtual void CollectOwner(FReplicationStateOwnerCollector* Owners) const override;`
- L35 _private prototype_ `void MimicMinimalGameplayCueReplicationProxyReceiveLogic(FReplicationStateApplyContext& Context) const;`
- L36 _private prototype_ `void CallRepNotify(FReplicationStateApplyContext& Context);`
- L39 _private member_ `TRefCountPtr<const FReplicationStateDescriptor> ReplicationStateDescriptor;`
- L40 _private member_ `TUniquePtr<FPropertyReplicationState> SrcReplicationState;`
- L41 _private member_ `UObject* Owner = nullptr;`

#### Free symbols / members of external scopes

- L10 _namespace_ `namespace UE`
- L10 _namespace_ `namespace Net` (scope `UE`)
- L13 _prototype_ `FReplicationFragment* CreateAndRegisterMinimalGameplayCueReplicationProxyReplicationFragment(UObject* Owner, const FReplicationStateDescriptor* Descriptor, FFragmentRegistrationContext& Context);` (scope `UE::Net`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/Serialization/MinimalReplicationTagCountNetSerializer.h` (Public)


#### struct `FMinimalReplicationTagCountMapNetSerializerConfig`  
`struct FMinimalReplicationTagCountMapNetSerializerConfig : public FNetSerializerConfig`  
_L9-12_
- reflection: `USTRUCT()`
- inherits: `FNetSerializerConfig`

#### Free symbols / members of external scopes

- L14 _namespace_ `namespace UE`
- L14 _namespace_ `namespace Net` (scope `UE`)

### `Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/TickableAttributeSetInterface.h` (Public)


#### class `UTickableAttributeSetInterface`  
`class UTickableAttributeSetInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: Interface for attribute sets that need to tick to update state. These can be expensive

#### class `ITickableAttributeSetInterface`  
`class ITickableAttributeSetInterface`  
_L17-35_
- L27 _public prototype_ `virtual void Tick(float DeltaTime) = 0;` — Ticks the attribute set by DeltaTime seconds @param DeltaTime Size of the time step in seconds.
- L34 _public prototype_ `virtual bool ShouldTick() const = 0;` — Does this attribute set need to tick? @return true if this attribute set should currently be ticking, false otherwise.
