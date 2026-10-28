# Plugins / InteractableInterface

- module root: `Plugins/Experimental/InteractionInterface/Source/InteractableInterface`
- headers: 9; symbols: 76
- symbol kinds: class=12, delegate=2, function=3, member=19, prototype=36, struct=4
- PublicDependencyModuleNames: Core, CoreUObject, Engine, GameplayAbilities, GameplayTags, GameplayTasks

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Private/InteractionInterfaceModule.h` (Private)


#### class `FInteractionInterfaceModule`  
`class FInteractionInterfaceModule : public IModuleInterface`  
_L7-25_
- inherits: `IModuleInterface`
- L17 _public prototype_ `static FInteractionInterfaceModule& Get();` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L24 _public prototype_ `static bool IsAvailable();` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractableInstigator.h` (Public)


#### class `UInteractableInstigator`  
`class UInteractableInstigator : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: This class does not need to be modified.

#### class `IInteractableInstigator`  
`class IInteractableInstigator`  
_L23-30_
- desc: Interface that represents a single "Instigator" of an interaction. Instigators are objects which are allowed to interact with targets. They can attempt to begin interacting with a given set of targets.
- L29 _protected prototype_ `virtual void OnAttemptToBeginInteractions(const TArray<TScriptInterface<IInteractionTarget>>& TargetsToInteractWith) = 0;`

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractableInterfaceLibrary.h` (Public)


#### class `UInteractableInterfaceLibrary`  
`class UInteractableInterfaceLibrary final : public UBlueprintFunctionLibrary`  
_L19-80_
- reflection: `UCLASS()`
- inherits: `UBlueprintFunctionLibrary`
- desc: BP function helpers to utilize the Interactable Interface.
- L32 _public prototype_ `static void GetInteractableTargetsFromActor(AActor* Actor, TArray<TScriptInterface<IInteractionTarget>>& OutInteractionTargets);` — `UFUNCTION(BlueprintCallable, Category="Interactions")` — Populates the given OutInteractionTargets array with all IInteractionTarget interface objects on the given actor. @param Actor						The actor to check for targets on @param OutInteractionTargets		Array of pointers to any interaction targets on the given actor
- L45 _public prototype_ `static void AppendTargetConfiguration(TScriptInterface<IInteractionTarget> Target, const FInteractionContext& Context, UPARAM(ref) FInteractionQueryResults& OutResults);` — `UFUNCTION(BlueprintCallable, Category="Interactions", meta=(AutoCreateRefTerm="Context"))` — Determines what the configuration of this target is. Gather information about this specific target so that it can be displayed to the player and provide access to what behavior should occur in response to this interaction. @param Target		The interaction target to get the configuration of @param Context		The context of this interaction. @param OutResults	Output results that this target will populate
- L55 _public prototype_ `static void BeginInteractionOnTarget(TScriptInterface<IInteractionTarget> Target, const FInteractionContext& Context);` — `UFUNCTION(BlueprintCallable, Category="Interactions", meta=(AutoCreateRefTerm="Context"))` — Called when this target is interacted with. Implement any state changes or gameplay affects you want this interaction to have here @param Target		The interaction target to begin interacting with @param Context		The context of this interaction.
- L61 _public prototype_ `static void ResetQueryResults(UPARAM(ref) FInteractionQueryResults& ToReset);` — `UFUNCTION(BlueprintCallable, Category="Interactions")` — Resets the values of the given interaction query results to be empty.
- L69 _public prototype_ `static void AppendInteractableTargetsFromOverlapResults(const TArray<FOverlapResult>& OverlapResults, TArray<TScriptInterface<IInteractionTarget>>& OutInteractableTargets);` — Given a set of overlap results, append any found IInteractionTargets to the OutInteractableTargets array. @param OverlapResults			The overlap results from a physics query to process. @param OutInteractableTargets	The array of targets to append any found targets to. This array will not be reset.
- L77 _public prototype_ `static void AppendInteractableTargetsFromHitResult(const FHitResult& HitResult, TArray<TScriptInterface<IInteractionTarget>>& OutInteractableTargets);` — Given a hit result, append any found IInteractionTargets to the OutInteractableTargets array. @param HitResult					The hit result to process for targets @param OutInteractableTargets	The array of targets to append any found targets to. This array will not be reset.
- L79 _public prototype_ `static AActor* GetActorFromInteractableTarget(const TScriptInterface<IInteractionTarget> InteractableTarget);`

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractableTargetInterface.h` (Public)


#### class `UInteractionTarget`  
`class UInteractionTarget : public UInterface`  
_L13-16_
- reflection: `UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`
- desc: This class does not need to be modified.

#### class `IInteractionTarget`  
`class IInteractionTarget`  
_L25-49_
- desc: Implement this interface on things that are able to be interacted with. A target should be something in the world that can be interacted with. For example, a treasure chest which can be opened, an item that can picked up, or some narrative design element for your game.
- L39 _public prototype_ `virtual void AppendTargetConfiguration(const FInteractionContext& Context, OUT FInteractionQueryResults& OutResults) const = 0;` — Determines what the configuration of this target is. Gather information about this specific target so that it can be displayed to the player and provide access to what behavior should occur in response to this interaction. @param Context		The context of this interaction. @param OutResults	Output results that this target will populate
- L48 _public prototype_ `virtual void BeginInteraction(const FInteractionContext& Context) = 0;` — Called when this target is interacted with. Implement any state changes or gameplay affects you want this interaction to have here @param Context		The context of this interaction. This is customizable for your game by adding additional context types.

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractionInstigatorComponent.h` (Public)


#### class `UInteractionInstigatorComponent`  
`class UInteractionInstigatorComponent : public UActorComponent, public IInteractableInstigator`  
_L14-41_
- reflection: `UCLASS(Blueprintable, ClassGroup = Gameplay, meta = (BlueprintSpawnableComponent), HideCategories = (Activation, AssetUserData, Collision))`
- inherits: `UActorComponent,IInteractableInstigator`
- L22 _public prototype_ `UInteractionInstigatorComponent(const FObjectInitializer& ObjectInitializer);`
- L28 _public prototype_ `void AttemptToBeginInteractions(const TArray<TScriptInterface<IInteractionTarget>>& TargetsToInteractWith);` — `UFUNCTION(BlueprintCallable, Category="Interactions")` — Attempts to begin interacting with the given array of targets
- L36 _protected member_ `FInstancedStruct InteractionContextData;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactions", meta = (BaseStruct = "/Script/InteractableInterface.InteractionContextData"))` — Data about this specific interaction
- L39 _protected prototype_ `virtual void OnAttemptToBeginInteractions(const TArray<TScriptInterface<IInteractionTarget>>& TargetsToInteractWith) override;`

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractionInterfaceLogs.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogInteractions, Log, All);`

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractionTargetComponent.h` (Public)


#### class `UInteractionTargetComponent`  
`class UInteractionTargetComponent : public UBoxComponent, public IInteractionTarget`  
_L20-70_
- reflection: `UCLASS(Blueprintable, ClassGroup = Gameplay, meta = (BlueprintSpawnableComponent), HideCategories = (Activation, AssetUserData))`
- inherits: `UBoxComponent,IInteractionTarget`
- desc: A target that can be interacted with by an interaction instigator. Add this component to actors that you would like to be intractable.
- L27 _public prototype_ `UInteractionTargetComponent(const FObjectInitializer& ObjectInitializer);`
- L31 _public member_ `FBeginInteractionCallback OnBeginInteractionCallback;` — `UPROPERTY(BlueprintAssignable, Category="Interactions")` — A callback for when this target begins interaction.
- L43 _public prototype_ `void BP_AppendTargetConfiguration(const FInteractionContext& Context, FInteractionQueryResults& OutResults) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure=false, Category="Interactions", meta=(DisplayName="Get Target Configuration", AutoCreateRefTerm="Context,OutResults"))` — Determines what the configuration of this target is. Gather information about this specific target so that it can be displayed to the player and provide access to what behavior should occur in response to this interaction. @param Context		The context of this interaction. @param OutResults	Output results that this target will populate
- L53 _public prototype_ `void BP_BeginInteraction(const FInteractionContext& Context);` — `UFUNCTION(BlueprintCallable, Category="Interactions", meta=(DisplayName="Begin Interaction",AutoCreateRefTerm="Context"))` — Called when this target is interacted with. Implement any state changes or gameplay affects you want this interaction to have here @param Context		The context of this interaction. This is customizable for your game by adding additional context types.
- L58 _protected prototype_ `virtual void AppendTargetConfiguration(const FInteractionContext& QueryContext, FInteractionQueryResults& OutResults) const override;`
- L59 _protected prototype_ `virtual void BeginInteraction(const FInteractionContext& Context) override;`
- L69 _protected member_ `TArray<FInstancedStruct> TargetConfigs;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interaction", meta = (BaseStruct = "/Script/InteractableInterface.InteractionTargetConfiguration"))` — The configuration for this target component. Stores metadata about this interaction can be used to build UI or make decisions about which target is currently desired the most by the instigator.

#### Free symbols / members of external scopes

- L12 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeginInteractionCallback, const FInteractionContext&, Context);`
- L12 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBeginInteractionCallback, const FInteractionContext&, Context);`

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractionTask_WaitForTargets.h` (Public)


#### class `UAbilityTask_GrantNearbyInteractionData`  
`class UAbilityTask_GrantNearbyInteractionData : public UAbilityTask`  
_L36-98_
- reflection: `UCLASS()`
- inherits: `UAbilityTask`
- desc: Gameplay Ability Task that will query all available interaction targets at a given interval around it's owning ability actor. This task will gather nearby interactive targets and make them available to you via blueprint/C++ with the OnAvailableInteractionTargetsChanged delegate
- L45 _public prototype_ `static UAbilityTask_GrantNearbyInteractionData* GrantAbilitiesForNearbyInteractionData( UGameplayAbility* OwningAbility, ECollisionChannel TraceChannel, float InteractionScanRange = 500.0f, float InteractionScanRate = 0.1f);` — `UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))` — Wait until an overlap occurs. This will need to be better fleshed out so we can specify game specific collision requirements
- L55 _public member_ `FAvailableInteractionTargetsChanged OnAvailableInteractionTargetsChanged;` — `UPROPERTY(BlueprintAssignable)` — Delegate fired when the available interaction targets near the owner of this ability task have changed
- L60 _protected prototype_ `virtual void Activate() override;`
- L61 _protected prototype_ `virtual void OnDestroy(bool AbilityEnded) override;`
- L68 _protected prototype_ `virtual void QueryNearbyInteractables();` — Runs a query to gather the nearby interactable objects to this ability's owner.
- L74 _protected member_ `float InteractionScanRange = 500.0f;` — How often to scan for targets. A world OverlapMultiByChannel call will happen at this rate to check for available interactions around us.
- L80 _protected member_ `float InteractionScanRate = 0.1f;` — How often to scan for targets. A world OverlapMultiByChannel call will happen at this rate to check for available interactions around us.
- L85 _protected member_ `ECollisionChannel InteractionTraceChannel = ECC_GameTraceChannel1;` — The collision channel to check for interactable targets on
- L91 _protected member_ `FTimerHandle QueryTimerHandle;` — Timer handle that is populated on this task's Activate function and cleared OnDestroy for how often to Query for targets.
- L97 _protected member_ `TArray<TScriptInterface<IInteractionTarget>> CurrentAvailableTargets;` — `UPROPERTY()` — Array of interaction targets which are in range from the most recent query

#### class `UInteractionAbilityInterface`  
`class UInteractionAbilityInterface : public UInterface`  
_L103-106_
- reflection: `UINTERFACE()`
- inherits: `UInterface`

#### class `IInteractionAbilityInterface`  
`class IInteractionAbilityInterface`  
_L109-132_
- L121 _protected prototype_ `void OnAvailableInteractionsUpdated();` — `UFUNCTION(BlueprintNativeEvent, Category="Interactions")` — Called when this ability's available interaction targets have been updated. This is a good place to update some UI or display some message to the user that they can now interact with the current targets.
- L122 _protected function_ `virtual void OnAvailableInteractionsUpdated_Implementation()`
- L130 _protected prototype_ `void OnTriggerInteraction();` — `UFUNCTION(BlueprintNativeEvent, Category="Interactions")` — Triggers the interaction with one or more of the currently available targets. Override this in blueprints or native C++ to decide which of the currently available targets you would like to interact with and how.
- L131 _protected function_ `virtual void OnTriggerInteraction_Implementation()`

#### class `UGameplayAbility_Interact`  
`class UGameplayAbility_Interact : public UGameplayAbility, public IInteractionAbilityInterface`  
_L146-216_
- reflection: `UCLASS(Abstract)`
- inherits: `UGameplayAbility,IInteractionAbilityInterface`
- desc: Gameplay ability for interacting with a target(s). This ability will trigger interactions on its current list of available targets which are populated via the UpdateInteractions functions. When UpdateInteractions is called, it provides a nice place to update some UI or other things you may want to do to display to your player that interactions are now available.
- L154 _public prototype_ `UGameplayAbility_Interact(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L162 _public prototype_ `void UpdateInteractions(const TArray<TScriptInterface<IInteractionTarget>>& AvailableTargets);` — `UFUNCTION(BlueprintCallable, Category="Interactions")` — Update the available interactions that this ability can trigger. This is normally populated via an async task running in the ability blueprint to gather nearby targets.
- L168 _public prototype_ `void TriggerInteraction();` — `UFUNCTION(BlueprintCallable, Category = "Interactions")` — Attempts to begin the interaction with the current targets.
- L173 _protected prototype_ `virtual void ActivateAbility( const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;`
- L181 _protected prototype_ `void HandleTargetsUpdatedFromTask(const TArray<TScriptInterface<IInteractionTarget>>& AvailableTargets);`
- L187 _protected prototype_ `virtual void OnAvailableInteractionsUpdated_Implementation() override;` — Native C++ implementation of OnAvailableInteractionsUpdated. Override this to do any work you may need to when new interactions become available
- L188 _protected prototype_ `virtual void OnTriggerInteraction_Implementation() override;`
- L195 _protected member_ `float InteractionScanRate = 0.1f;` — `UPROPERTY(EditDefaultsOnly, Category = "Interactions")` — How often to scan for targets. A world OverlapMultiByChannel call will happen at this rate to check for available interactions around us.
- L202 _protected member_ `float InteractionScanRange = 500.0f;` — `UPROPERTY(EditDefaultsOnly, Category = "Interactions")` — The range to scan for available targets. A sphere of this radius will be cast around this ability's owning actor to check for nearby interactions.
- L208 _protected member_ `TEnumAsByte<ECollisionChannel> InteractionTraceChannel = ECC_GameTraceChannel1;` — `UPROPERTY(EditDefaultsOnly, Category = "Interactions")` — The collision channel to use when checking for interaction targets within the given area
- L215 _protected member_ `TArray<TScriptInterface<IInteractionTarget>> CurrentAvailableTargets;` — `UPROPERTY(BlueprintReadOnly, Category = "Interactions")` — Array of available interaction targets to interact with. This is populated by "UpdateInteractions" and normally after an ability task to gather the available targets has completed.

#### Free symbols / members of external scopes

- L26 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAvailableInteractionTargetsChanged, const TArray<TScriptInterface<IInteractionTarget>>&, InteractableOptions);` — Delegate fired for when the nearby available interactable targets have changed.
- L26 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAvailableInteractionTargetsChanged, const TArray<TScriptInterface<IInteractionTarget>>&, InteractableOptions);` — Delegate fired for when the nearby available interactable targets have changed.

### `Plugins/Experimental/InteractionInterface/Source/InteractableInterface/Public/InteractionTypes.h` (Public)


#### struct `FInteractionTargetConfiguration`  
`struct FInteractionTargetConfiguration`  
_L20-35_
- reflection: `USTRUCT(BlueprintType)`
- desc: Contains data about a single interactable target. This is information that you may want to use to build some UI or decide on what the state of certain interactable objects is.
- L30 _public member_ `FText DisplayName;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interactions")` — The display name that can be used for this interaction

#### struct `FInteractionContextData`  
`struct FInteractionContextData`  
_L46-61_
- reflection: `USTRUCT(BlueprintType)`
- desc: Data about a specific interaction that is happening. It is encouraged that you make structs that inherit from this one to add custom game logic and conditions you may need for any given interaction. For example, you may have a target which is only able to be used if the player has a specific item equipped, or some other conditional state like that.
- L54 _public member_ `TScriptInterface<IInteractableInstigator> Instigator;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="General")` — The interaction instigator who is doing the querying!
- L60 _public member_ `FGameplayTagContainer InteractionTags;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="General")` — Some tags that are unique to this interaction and can be used to provide some context

#### struct `FInteractionContext`  
`struct FInteractionContext`  
_L71-87_
- reflection: `USTRUCT(BlueprintType)`
- desc: The context of a given interaction query. This holds some state about what is currently querying for intractable objects and will allow you to specify some specific game state around each interaction. @see IInteractionTarget::BeginInteraction
- L80 _public member_ `TScriptInterface<IInteractionTarget> Target;` — `UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category=General)` — The interactable target that should be used
- L86 _public member_ `FInstancedStruct ContextData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (BaseStruct = "/Script/InteractableInterface.InteractionContextData"))` — Data about this specific interaction query

#### struct `FInteractionQueryResults`  
`struct FInteractionQueryResults`  
_L98-118_
- reflection: `USTRUCT(BlueprintType)`
- desc: A struct that will be populated with all the available interaction options for a given target. These query results are populated by Interaction Targets. Each target may have multiple configurations on it (i.e. a bench with two seats, or a car with 4 doors to open) @see IInteractionTarget::GetTargetConfiguration
- L106 _public function_ `void Reset()` — Resets the values of this query results to be empty.
- L117 _public member_ `TArray<FInstancedStruct> AvailableInteractions;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = General, meta = (BaseStruct = "/Script/InteractableInterface.InteractionTargetConfiguration"))` — Array of available interactions that can be started. Add to this array for any interaction which you would like to be presented as an available option in response to this query.
