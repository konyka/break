# Plugins / ActorModifierCore

- module root: `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore`
- headers: 16; symbols: 562
- symbol kinds: class=11, delegate=8, enum=7, enumerator=27, function=71, macro=1, member=122, namespace=5, prototype=296, struct=14
- PrivateDependencyModuleNames: Engine, Slate, SlateCore, TraceLog, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Private/Modifiers/ActorModifierCoreSharedActor.h` (Private)


#### class `AActorModifierCoreSharedActor`  
`class AActorModifierCoreSharedActor : public AActor`  
_L15-57_
- reflection: `UCLASS(NotPlaceable, Hidden, NotBlueprintable, NotBlueprintType)`
- inherits: `AActor`
- desc: Singleton actor used to keep all shared data across modifiers instances, there can only be one per level, should not be visible to user Use the modifier subsystem to query objects, do not handle it directly
- L23 _protected prototype_ `virtual void PostLoad() override;`
- L26 _protected prototype_ `AActorModifierCoreSharedActor();`
- L30 _protected function_ `template<typename InSharedClass = UActorModifierCoreSharedObject, typename = typename TEnableIf<TIsDerivedFrom<InSharedClass, UActorModifierCoreSharedObject>::Value>::Type> InSharedClass* FindOrAddShared()` — Queries a shared object or create one of a specific class if none
- L38 _protected function_ `template<typename InSharedClass = UActorModifierCoreSharedObject, typename = typename TEnableIf<TIsDerivedFrom<InSharedClass, UActorModifierCoreSharedObject>::Value>::Type> InSharedClass* FindShared() const` — Queries a shared object of a specific class
- L45 _protected prototype_ `UActorModifierCoreSharedObject* FindOrAddShared(TSubclassOf<UActorModifierCoreSharedObject> InSharedClass);` — Queries a shared object or create one if none
- L48 _protected prototype_ `UActorModifierCoreSharedObject* FindShared(TSubclassOf<UActorModifierCoreSharedObject> InSharedClass) const;` — Queries a shared object
- L52 _protected prototype_ `void OnActorDestroyed(AActor* InActor);` — `UFUNCTION()` — Called when actor is destroyed
- L56 _protected member_ `TMap<TObjectPtr<UClass>, TObjectPtr<UActorModifierCoreSharedObject>> SharedObjects;` — `UPROPERTY()` — Map of Shared objects available

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/ActorModifierCoreLog.h` (Public)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogActorModifierCore, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogActorModifierCore, Log, All);`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/ActorModifierCoreBase.h` (Public)


#### class `UActorModifierCoreBase`  
`class UActorModifierCoreBase : public UObject`  
_L26-451_
- reflection: `UCLASS(MinimalAPI, NotBlueprintable, Abstract, EditInlineNew, HideCategories=(Tags, AssetUserData, Activation, Collision, Cooking))`
- inherits: `UObject`
- desc: Abstract base class for all modifier, a modifier must be located in a modifier stack to work properly
- L43 _public prototype_ `const FActorModifierCoreMetadata& GetModifierMetadata() const;` — Returns modifier metadata
- L46 _public prototype_ `FName GetModifierName() const;` — Returns this modifier unique name
- L49 _public prototype_ `FName GetModifierCategory() const;` — Returns this modifier category
- L52 _public function_ `TSharedPtr<FActorModifierCoreProfiler> GetProfiler() const` — Gets the modifier profiler
- L58 _public function_ `const FActorModifierCoreStatus& GetModifierLastStatus() const` — Gets the modifier last status
- L64 _public prototype_ `bool IsModifierStack() const;` — Whether this modifier is a stack to avoid casting
- L67 _public prototype_ `AActor* GetModifiedActor() const;` — Returns the modified actor for this modifier
- L70 _public prototype_ `UActorModifierCoreStack* GetModifierStack() const;` — Returns the stack this modifier is in
- L73 _public prototype_ `UActorModifierCoreStack* GetRootModifierStack() const;` — Returns the top root stack this modifier is in
- L76 _public prototype_ `UActorModifierCoreComponent* GetModifierComponent() const;` — Returns the modifier this stack is in
- L79 _public prototype_ `const UActorModifierCoreBase* GetPreviousModifier() const;` — Returns the previous modifier found before this one, will recurse upwards, could return a stack
- L82 _public prototype_ `const UActorModifierCoreBase* GetNextModifier() const;` — Returns the next modifier found after this one, will recurse upwards, could return a stack
- L85 _public prototype_ `const UActorModifierCoreBase* GetPreviousNameModifier(const FName& InModifierName) const;` — Returns the first modifier before this one that matches the name, will recurse upwards, could return a stack
- L88 _public prototype_ `const UActorModifierCoreBase* GetNextNameModifier(const FName& InModifierName) const;` — Returns the first modifier after this one that matches the name, will recurse upwards, could return a stack
- L91 _public prototype_ `bool CanMarkModifierDirty() const;` — Returns whether a modifier can be marked dirty
- L97 _public prototype_ `bool MarkModifierDirty(bool bExecute = true);` — Set this modifier as dirty to be able to execute only dirty modifiers returns true if the modifier could be marked dirty
- L100 _public function_ `bool IsModifierDirty() const` — Whether this modifier is set as dirty
- L106 _public function_ `bool IsModifierIdle() const` — Whether this modifier is idle and not running
- L112 _public function_ `bool IsModifierExecutionLocked() const` — Is the execution of this modifier locked
- L118 _public function_ `bool IsModifierApplied() const` — Whether this modifier is applied and can be restored
- L124 _public function_ `bool IsModifierInitialized() const` — Whether this modifier was initialized and is now ready to operate
- L130 _public function_ `virtual bool IsModifierEmpty() const` — Whether this modifier contains other modifiers
- L136 _public prototype_ `void SetModifierEnabled(bool bInEnabled);` — `UFUNCTION()`
- L138 _public prototype_ `bool IsModifierEnabled() const;`
- L141 _public prototype_ `void ProcessLockFunction(TFunctionRef<void()> InFunction);` — Locks this modifier execution and process a function before unlocking it
- L144 _public prototype_ `bool IsModifierProfiling() const;` — Is this modifier in profiling mode
- L148 _public function_ `template<typename InComponentClass = UActorComponent, typename = typename TEnableIf<TIsDerivedFrom<InComponentClass, UActorComponent>::Value>::Type> bool ForEachComponent(TFunctionRef<bool(InComponentClass*)> InFunction, EActorModifierCoreComponentType InComponentType = EActorModifierCoreComponentType::Owned, EActorModifierCoreLookup InActorLookup = EActorModifierCoreLookup::Self, TOptional<const AActor*> InOptionalActor = TOptional<const AActor*>()) const` — Helper to lookup components type, by default will loop through this actor components, stops when false is returned
- L194 _public function_ `template<typename InActorClass = AActor, typename = typename TEnableIf<TIsDerivedFrom<InActorClass, AActor>::Value>::Type> bool ForEachActor(TFunctionRef<bool(InActorClass*)> InFunction, EActorModifierCoreLookup InActorLookup = EActorModifierCoreLookup::DirectChildren, TOptional<const AActor*> InOptionalActor = TOptional<const AActor*>()) const` — Helper to lookup actors, by default will loop through this actor direct children, stops when false is returned
- L232 _protected prototype_ `UActorModifierCoreBase();`
- L235 _protected prototype_ `virtual void PostLoad() override;`
- L236 _protected prototype_ `virtual void PostEditImport() override;`
- L237 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;`
- L239 _protected prototype_ `virtual void PreEditUndo() override;`
- L240 _protected prototype_ `virtual void PostEditUndo() override;`
- L241 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L246 _protected function_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata)` — Override metadata for this modifier, called only once before modifier CDO is registered
- L249 _protected function_ `virtual bool IsModifierReady() const` — Checks whether this modifier is ready to run, called before this modifier is executed
- L252 _protected function_ `virtual bool IsModifierDirtyable() const` — You can do additional lightweights checks here in case you want to dirty the modifier instead of waiting for an event, tick must be enabled in the metadata
- L255 _protected function_ `virtual void SavePreState()` — Override in child classes, called before applying this modifier
- L258 _protected function_ `virtual void RestorePreState()` — Override in child classes, unapply this modified changes and restore the state before this modifier is applied
- L261 _protected prototype_ `virtual void Apply();` — Override in child classes, apply this modifier on the actual actor, call Next or Fail to complete the modifier execution
- L264 _protected function_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason)` — Called after the modifier was added to a stack and initialized after creation or serialization or duplication
- L267 _protected function_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason)` — Called after the modifier is removed from a stack and uninitialized after actor destruction
- L270 _protected function_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason)` — Called when a modifier is enabled
- L273 _protected function_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason)` — Called when a modifier is disabled
- L276 _protected function_ `virtual void OnModifiedActorTransformed()` — Called when modified actor transform is updated if this modifier is enabled
- L279 _protected prototype_ `void Next();` — The modifier was executed properly, skip to the next one
- L282 _protected prototype_ `void Fail(const FText& InFailReason);` — The modifier failed executing, do not continue and stop here
- L286 _protected function_ `template<typename InSharedClass = UActorModifierCoreSharedObject, typename = typename TEnableIf<TIsDerivedFrom<InSharedClass, UActorModifierCoreSharedObject>::Value>::Type> InSharedClass* GetShared(bool bInCreateIfNone = false) const` — Get shared object of that specific class or create one if none was found, casted version
- L293 _protected prototype_ `UActorModifierCoreSharedObject* GetShared(TSubclassOf<UActorModifierCoreSharedObject> InClass, bool bInCreateIfNone = false) const;` — Get shared object of that specific class or create one if none was found
- L297 _protected function_ `template<typename InExtensionClass, typename = typename TEnableIf<TIsDerivedFrom<InExtensionClass, FActorModifierCoreExtension>::IsDerived>::Type, typename... InArgTypes> InExtensionClass* AddExtension(InArgTypes&& ... InArgs)` — Adds an extension of a specific type to this modifier with its arguments or gets it if it already exists
- L319 _protected function_ `template<typename InExtensionClass, typename = typename TEnableIf<TIsDerivedFrom<InExtensionClass, FActorModifierCoreExtension>::IsDerived>::Type> bool ProcessExtension(TFunctionRef<void(InExtensionClass*)> InFunction)` — Executes the function for that extension if it exists, returns true if execution was successful
- L338 _protected function_ `template<typename InExtensionClass, typename = typename TEnableIf<TIsDerivedFrom<InExtensionClass, FActorModifierCoreExtension>::IsDerived>::Type> InExtensionClass* GetExtension() const` — Gets an extension with this type, casted version
- L355 _protected prototype_ `FActorModifierCoreExtension* GetExtension(const FName& InExtensionType) const;` — Gets an extension of this specific type
- L358 _protected prototype_ `bool RemoveExtension(const FName& InExtensionType);` — Removes an extension of this type from this modifier
- L361 _protected prototype_ `void LogModifier(const FString& InLog, bool bInForce = false, EActorModifierCoreStatus InType = EActorModifierCoreStatus::Success) const;` — `UE_DEPRECATED(5.8, "LogModifier deprecated. Prefer using UE_LOG instead.")`
- L363 _protected prototype_ `void DeferInitializeModifier();`
- L367 _private prototype_ `virtual void OnModifierDirty(UActorModifierCoreBase* DirtyModifier, bool bExecute);` — Called when modifier becomes dirty
- L370 _private prototype_ `virtual bool ProcessFunction(TFunctionRef<bool(const UActorModifierCoreBase*)> InFunction, const FActorModifierCoreStackSearchOp& InSearchOptions) const;` — Execute a const function on this modifier, only to read data
- L373 _private prototype_ `void Unapply();` — INTERNAL USE ONLY, called by the stack only to unapply this modifier if it was applied
- L376 _private prototype_ `void InitializeModifier(EActorModifierCoreEnableReason InReason);` — INTERNAL USE ONLY, called after load or creation or duplication
- L379 _private prototype_ `void UninitializeModifier(EActorModifierCoreDisableReason InReason);` — INTERNAL USE ONLY, called before being destroyed or removed
- L382 _private prototype_ `void PostModifierCreation(UActorModifierCoreStack* InStack);` — INTERNAL USE ONLY, called once after creating a modifier to set inner properties
- L385 _private prototype_ `void PostModifierCDOCreation();` — INTERNAL USE ONLY, called once after creating the CDO modifier
- L388 _private prototype_ `void PostModifierWorldLoad(UWorld* InWorld, ELevelTick InType, float InDelta);` — INTERNAL USE ONLY, Called when the world and all its actors have loaded to execute initialized modifiers
- L391 _private prototype_ `void EnableModifier(EActorModifierCoreEnableReason InReason);` — INTERNAL USE ONLY, handles enable virtual calls and other required tasks
- L394 _private prototype_ `void DisableModifier(EActorModifierCoreDisableReason InReason);` — INTERNAL USE ONLY, handles disable virtual calls and other required tasks
- L397 _private prototype_ `void LockModifierExecution();` — INTERNAL USE ONLY, locks the modifier execution to prevent the execution of the stack it is in
- L400 _private prototype_ `void UnlockModifierExecution();` — INTERNAL USE ONLY, unlocks the modifier and executes it if marked dirty
- L403 _private prototype_ `void AddExtensionInternal(const FName& InExtensionType, TSharedPtr<FActorModifierCoreExtension> InExtension);` — INTERNAL USE ONLY, add and setup a newly created extension for this modifier
- L406 _private prototype_ `void OnModifierEnabledChanged(bool bInExecute = true);` — Called after setting the modifier enabled state
- L409 _private prototype_ `void BeginModifierExecution();` — Called before the execution of this modifier
- L412 _private prototype_ `void EndModifierExecution();` — Called after the execution of this modifier
- L417 _private member_ `TMap<FName, TSharedPtr<FActorModifierCoreExtension, ESPMode::ThreadSafe>> ModifierExtensions;` — Map of typed extensions, will follow this modifier lifecycle
- L419 _private member_ `TWeakObjectPtr<AActor> ModifiedActor = nullptr;`
- L423 _private member_ `bool bModifierEnabled = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetModifierEnabled", Getter="IsModifierEnabled", Category="Modifier", meta=(DisplayName="Enable Modifier"))` — Is the modifier enabled or disabled
- L426 _private member_ `bool bModifierIdle = true;` — Is the modifier idle and not running
- L429 _private member_ `bool bModifierDirty = false;` — Is the modifier dirty and needs an update
- L432 _private member_ `bool bModifierApplied = false;` — Is the modifier applied and whether it can be un-applied
- L435 _private member_ `bool bModifierInitialized = false;` — Only initialize a modifier once, after creation or load
- L438 _private member_ `bool bModifierExecutionLocked = false;` — When marked dirty will not execute and prevent stack from executing
- L441 _private member_ `bool bModifierOptimized = false;` — This modifier is optimized in the stack
- L444 _private member_ `TSharedPtr<FActorModifierCoreMetadata> Metadata;` — This modifier metadata, same metadata for this modifier class
- L447 _private member_ `TSharedPtr<FActorModifierCoreProfiler> Profiler;` — This modifier profiler
- L450 _private member_ `FActorModifierCoreStatus Status;` — This modifier last status message

#### Free symbols / members of external scopes

- L161 _function_ `` (scope `UActorModifierCoreBase::ForEachComponent`)

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/ActorModifierCoreComponent.h` (Public)


#### class `UActorModifierCoreComponent`  
`class UActorModifierCoreComponent : public UActorComponent`  
_L12-48_
- reflection: `UCLASS(MinimalAPI, ClassGroup="Modifiers", BlueprintType, EditInlineNew, DefaultToInstanced, meta=(BlueprintSpawnableComponent), HideCategories=(Tags, Activation, Cooking, AssetUserData, Collision))`
- inherits: `UActorComponent`
- desc: Component that contains a modifier stack and can be added on any actor
- L20 _public prototype_ `static UActorModifierCoreComponent* CreateAndExposeComponent(AActor* InParentActor);` — Create this component for a specific actor and exposes it to the editor and for serialization
- L22 _public prototype_ `UActorModifierCoreComponent();`
- L25 _public function_ `UActorModifierCoreStack* GetModifierStack() const` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers")`
- L32 _protected prototype_ `virtual void OnComponentCreated() override;`
- L33 _protected prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L37 _protected prototype_ `virtual void PostLoad() override;`
- L39 _protected prototype_ `virtual void PostEditUndo() override;`
- L43 _protected prototype_ `virtual void TickComponent(float InDeltaTime, ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction) override;`
- L47 _protected member_ `TObjectPtr<UActorModifierCoreStack> ModifierStack = nullptr;` — `UPROPERTY(VisibleInstanceOnly, NoClear, Export, Instanced, Category="Modifiers")` — This is the root stack that will contain all modifiers for this actor

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/ActorModifierCoreDefs.h` (Public)


#### enum `EActorModifierCoreEnableReason`  
`enum class EActorModifierCoreEnableReason : uint8`  
_L31-41_
- reflection: `UENUM(BlueprintType)`
- L34 _public enumerator_ `User` — Modifier added by user
- L36 _public enumerator_ `Load` — Modifier added by load
- L38 _public enumerator_ `Undo` — Modifier added by undo
- L40 _public enumerator_ `Duplicate` — Modifier added by duplicate

#### enum `EActorModifierCoreDisableReason`  
`enum class EActorModifierCoreDisableReason : uint8`  
_L44-52_
- reflection: `UENUM(BlueprintType)`
- L47 _public enumerator_ `User` — Modifier disabled by user
- L49 _public enumerator_ `Undo` — Modifier disabled by undo
- L51 _public enumerator_ `Destroyed` — Modifier disabled by actor destroyed

#### enum `EActorModifierCoreStackPosition`  
`enum class EActorModifierCoreStackPosition : uint8`  
_L56-60_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates valid positions for modifier operations
- L58 _public enumerator_ `Before`
- L59 _public enumerator_ `After`

#### enum `EActorModifierCoreComponentType`  
`enum class EActorModifierCoreComponentType : uint8`  
_L63-68_
- desc: Enumerates component type on actor
- L65 _public enumerator_ `Owned = 1 << 0`
- L66 _public enumerator_ `Instanced = 1 << 1`
- L67 _public enumerator_ `All = Owned | Instanced`

#### enum `EActorModifierCoreLookup`  
`enum class EActorModifierCoreLookup : uint8`  
_L71-78_
- desc: Enumerates actor lookup possibilities
- L73 _public enumerator_ `Self = 1 << 0`
- L74 _public enumerator_ `DirectChildren = 1 << 1`
- L75 _public enumerator_ `SelfAndDirectChild = Self | DirectChildren`
- L76 _public enumerator_ `AllChildren = DirectChildren | 1 << 2`
- L77 _public enumerator_ `SelfAndAllChildren = Self | AllChildren`

#### enum `EActorModifierCoreStatus`  
`enum class EActorModifierCoreStatus : uint8`  
_L81-89_
- desc: Enumerates modifier status message
- L84 _public enumerator_ `Success` — Everything went well
- L86 _public enumerator_ `Warning` — Everything went well but requires user attention
- L88 _public enumerator_ `Error` — Something went wrong

#### struct `FActorModifierCoreMetadata`  
`struct FActorModifierCoreMetadata`  
_L95-324_
- reflection: `USTRUCT(BlueprintType)`
- desc: Metadata for each modifier CDO, modifier instance will share same metadata as CDO
- L99 _public member_ `static inline const FName DefaultCategory = TEXT("Def`
- L101 _public member_ `static inline const FText DefaultDescription = FText::FromString(TEXT("Desc`
- L102 _public member_ `static inline const FLinearColor DefaultColor = FLinearColor::White;`
- L105 _public prototype_ `FActorModifierCoreMetadata();`
- L106 _public prototype_ `explicit FActorModifierCoreMetadata(const UActorModifierCoreBase* InModifier);`
- L110 _public function_ `template<typename InProfilerClass, typename = typename TEnableIf<TIsDerivedFrom<InProfilerClass, FActorModifierCoreProfiler>::IsDerived>::Type> FActorModifierCoreMetadata& SetProfilerClass()` — Set the profiler class used for this modifier instances
- L123 _public prototype_ `FActorModifierCoreMetadata& SetName(FName InName);` — Set name of this modifier, should only be set once
- L126 _public prototype_ `FActorModifierCoreMetadata& SetCategory(FName InCategory);` — Set Category group of this modifier, should only be set once
- L129 _public prototype_ `FActorModifierCoreMetadata& AllowTick(bool bInAllowed);` — Allow modifier to tick to update when IsModifierDirtyable returns true
- L132 _public prototype_ `FActorModifierCoreMetadata& AllowMultiple(bool bInAllowed);` — Allows multiple modifiers of the same type in the same stack
- L135 _public prototype_ `FActorModifierCoreMetadata& AddDependency(const FName& InModifierName);` — Add a modifier dependency for this modifier, will be added when this modifier is added
- L138 _public prototype_ `FActorModifierCoreMetadata& DisallowBefore(const FName& InModifierName);` — Disallows this modifier before another modifier
- L141 _public prototype_ `FActorModifierCoreMetadata& DisallowAfter(const FName& InModifierName);` — Disallows this modifier after another modifier
- L144 _public prototype_ `FActorModifierCoreMetadata& AvoidBeforeCategory(const FName& InCategory);` — Avoid usage of this modifier before another modifier category
- L147 _public prototype_ `FActorModifierCoreMetadata& AvoidAfterCategory(const FName& InCategory);` — Avoid usage of this modifier after another modifier category
- L150 _public prototype_ `FActorModifierCoreMetadata& SetCompatibilityRule(const TFunction<bool(const AActor*)>& InModifierRule);` — Sets the usage rule for this modifier, if it passes it will be available for this actor
- L153 _public prototype_ `FActorModifierCoreMetadata& SetCompatibilityRule(const FModifierCompatibilityRule& InModifierRule);` — Sets the usage rule for this modifier, if it passes it will be available for this actor
- L156 _public prototype_ `UActorModifierCoreBase* CreateModifierInstance(UActorModifierCoreStack* InStack) const;` — Create the modifier instance
- L159 _public prototype_ `TSharedPtr<FActorModifierCoreProfiler> CreateProfilerInstance(UActorModifierCoreBase* InModifier) const;` — Create the profiler instance
- L161 _public prototype_ `bool ResetDefault();`
- L163 _public function_ `FName GetName() const`
- L168 _public function_ `FName GetCategory() const`
- L173 _public function_ `bool IsTickAllowed() const`
- L178 _public function_ `bool IsMultipleAllowed() const`
- L183 _public function_ `bool IsStack() const`
- L188 _public function_ `TConstArrayView<FName> GetDependencies() const`
- L193 _public function_ `const TSet<FName>& GetDisallowedBefore() const`
- L198 _public function_ `const TSet<FName>& GetDisallowedAfter() const`
- L203 _public function_ `TSubclassOf<UActorModifierCoreBase> GetClass() const`
- L208 _public prototype_ `bool IsDisallowedAfter(const FName& InModifierName) const;`
- L210 _public prototype_ `bool IsDisallowedBefore(const FName& InModifierName) const;`
- L212 _public prototype_ `bool IsAllowedAfter(const FName& InModifierName) const;`
- L214 _public prototype_ `bool IsAllowedBefore(const FName& InModifierName) const;`
- L216 _public prototype_ `bool IsCompatibleWith(const AActor* InActor) const;`
- L219 _public prototype_ `bool DependsOn(const FName& InModifierName) const;` — Checks if this modifier depends on another modifier
- L222 _public prototype_ `bool IsRequiredBy(const FName& InModifierName) const;` — Check if this modifier is required by the other modifier
- L224 _public prototype_ `bool ShouldAvoidBefore(FName InCategory) const;`
- L226 _public prototype_ `bool ShouldAvoidAfter(FName InCategory) const;`
- L229 _public prototype_ `FActorModifierCoreMetadata& SetDisplayName(const FText& InName);`
- L231 _public prototype_ `FActorModifierCoreMetadata& SetDescription(const FText& InDescription);`
- L233 _public prototype_ `FActorModifierCoreMetadata& SetColor(const FLinearColor& InColor);`
- L235 _public prototype_ `FActorModifierCoreMetadata& SetIcon(const FSlateIcon& InIcon);`
- L237 _public prototype_ `FActorModifierCoreMetadata& SetHidden(bool bInHidden);`
- L239 _public function_ `bool IsHidden() const`
- L244 _public function_ `const FText& GetDisplayName() const`
- L249 _public function_ `const FText& GetDescription() const`
- L254 _public function_ `const FLinearColor& GetColor() const`
- L259 _public function_ `const FSlateIcon& GetIcon() const`
- L266 _private prototype_ `void SetupProfilerInstanceInternal(TSharedPtr<FActorModifierCoreProfiler> InProfiler, UActorModifierCoreBase* InModifier, const FName& InProfilerType) const;`
- L269 _private member_ `FName Name;` — Unique name to use for this modifier
- L272 _private member_ `FName Category;` — Category group of this modifier to sort them
- L275 _private member_ `bool bTickAllowed = false;` — Tick allowed for this modifier to run additional checks to detect changes
- L278 _private member_ `bool bMultipleAllowed = false;` — Is this modifier allowed multiple times in the same stack
- L281 _private member_ `bool bIsStack;` — Is this modifier a stack
- L284 _private member_ `TArray<FName> Dependencies;` — What modifiers does this modifier need to work properly, in the correct order
- L287 _private member_ `TSet<FName> DisallowedBefore;` — Is this modifier disallowed before these modifiers
- L290 _private member_ `TSet<FName> DisallowedAfter;` — Is this modifier disallowed after these modifiers
- L293 _private member_ `TSet<FName> AvoidedBeforeCategories;` — Modifier avoided before these categories
- L296 _private member_ `TSet<FName> AvoidedAfterCategories;` — Modifier avoided after these categories
- L299 _private member_ `TFunction<bool(const AActor*)> CompatibilityRuleFunction;` — Rule to pass before this modifier can be used on an actor
- L300 _private member_ `FModifierCompatibilityRule CompatibilityRuleDelegate;`
- L303 _private member_ `TSubclassOf<UActorModifierCoreBase> Class;` — In order to create new instances of this modifier
- L306 _private member_ `TFunction<TSharedPtr<FActorModifierCoreProfiler>(UActorModifierCoreBase*)> ProfilerFunction;` — Function to create a new profiler instance for a modifier
- L310 _private member_ `bool bHidden;` — Is this modifier visible or hidden in menu
- L313 _private member_ `FText DisplayName;` — Display name of this modifier for menus
- L316 _private member_ `FText Description;` — Description of the modifier as tooltip in menus
- L319 _private member_ `FLinearColor Color;` — Color visible in modifier tab
- L322 _private member_ `FSlateIcon Icon;` — Icon visible in menus, details panel and modifier tab

#### struct `FActorModifierCoreStackCloneOp`  
`struct FActorModifierCoreStackCloneOp`  
_L327-344_
- desc: Modifier stack clone operation
- L330 _public member_ `UActorModifierCoreBase* CloneModifier;` — Modifier in another stack that we want to clone
- L332 _public member_ `EActorModifierCoreStackPosition ClonePosition = EActorModifierCoreStackPosition::Before;`
- L335 _public member_ `UActorModifierCoreBase* ClonePositionContext = nullptr;` — Context modifier in the stack we want to clone to
- L337 _public member_ `FText* FailReason = nullptr;`
- L339 _public member_ `TArray<UActorModifierCoreBase*>* AddedDependencies = nullptr;`
- L342 _public member_ `bool bShouldTransact = false;`

#### struct `FActorModifierCoreStackInsertOp`  
`struct FActorModifierCoreStackInsertOp`  
_L347-362_
- desc: Modifier stack insert/add operation
- L349 _public member_ `FName NewModifierName = NAME_None;`
- L351 _public member_ `EActorModifierCoreStackPosition InsertPosition = EActorModifierCoreStackPosition::Before;`
- L353 _public member_ `UActorModifierCoreBase* InsertPositionContext = nullptr;`
- L355 _public member_ `FText* FailReason = nullptr;`
- L357 _public member_ `TArray<UActorModifierCoreBase*>* AddedDependencies = nullptr;`
- L360 _public member_ `bool bShouldTransact = false;`

#### struct `FActorModifierCoreStackMoveOp`  
`struct FActorModifierCoreStackMoveOp`  
_L365-378_
- desc: Modifier stack move operation
- L367 _public member_ `UActorModifierCoreBase* MoveModifier;`
- L369 _public member_ `EActorModifierCoreStackPosition MovePosition = EActorModifierCoreStackPosition::Before;`
- L371 _public member_ `UActorModifierCoreBase* MovePositionContext = nullptr;`
- L373 _public member_ `FText* FailReason = nullptr;`
- L376 _public member_ `bool bShouldTransact = false;`

#### struct `FActorModifierCoreStackRemoveOp`  
`struct FActorModifierCoreStackRemoveOp`  
_L381-394_
- desc: Modifier stack remove operation
- L383 _public member_ `UActorModifierCoreBase* RemoveModifier;`
- L385 _public member_ `bool bRemoveDependencies = false;`
- L387 _public member_ `TArray<UActorModifierCoreBase*>* RemovedDependencies = nullptr;`
- L389 _public member_ `FText* FailReason = nullptr;`
- L392 _public member_ `bool bShouldTransact = false;`

#### struct `FActorModifierCoreStackSearchOp`  
`struct FActorModifierCoreStackSearchOp`  
_L397-412_
- desc: Modifier stack search operation
- L399 _public prototype_ `static const FActorModifierCoreStackSearchOp& GetDefault();`
- L402 _public member_ `EActorModifierCoreStackPosition Position = EActorModifierCoreStackPosition::After;` — Position to look relative to a context
- L405 _public member_ `UActorModifierCoreBase* PositionContext = nullptr;` — Position context to operate search
- L408 _public member_ `bool bSkipStack = true;` — Skip stacks during search to only focus on modifiers
- L411 _public member_ `bool bRecurse = true;` — Also looks in nested stacks

#### struct `FActorModifierCoreScopedLock`  
`struct FActorModifierCoreScopedLock final`  
_L415-424_
- desc: Will lock modifiers execution during lifetime of this struct
- L417 _public prototype_ `explicit FActorModifierCoreScopedLock(UActorModifierCoreBase* InModifier);`
- L418 _public prototype_ `explicit FActorModifierCoreScopedLock(const TSet<UActorModifierCoreBase*>& InModifiers);`
- L420 _public prototype_ `~FActorModifierCoreScopedLock();`
- L423 _protected member_ `TSet<TWeakObjectPtr<UActorModifierCoreBase>> ModifiersWeak;`

#### struct `FActorModifierCoreStatus`  
`struct FActorModifierCoreStatus`  
_L426-450_
- L428 _public function_ `FActorModifierCoreStatus()`
- L429 _public function_ `explicit FActorModifierCoreStatus(EActorModifierCoreStatus InStatus, const FText& InStatusMessage) : Status(InStatus) , StatusMessage(InStatusMessage)`
- L434 _public function_ `EActorModifierCoreStatus GetStatus() const`
- L439 _public function_ `const FText& GetStatusMessage() const`
- L446 _protected member_ `EActorModifierCoreStatus Status = EActorModifierCoreStatus::Success;` — Modifier last status
- L449 _protected member_ `FText StatusMessage = FText::GetEmpty();` — Modifier last status message

#### struct `FActorModifierCoreExecutionTask`  
`struct FActorModifierCoreExecutionTask`  
_L453-483_
- reflection: `USTRUCT()`
- L458 _public prototype_ `void Restore();` — Restore original state until first dirty modifier, last -> first
- L461 _public prototype_ `void Apply(TConstArrayView<UActorModifierCoreBase*> InModifiers, UActorModifierCoreStack* InStack);` — Build the execution chain of dirty modifiers and execute, first -> last
- L463 _public prototype_ `void Next();`
- L464 _public prototype_ `void Fail();`
- L465 _public prototype_ `void Skip();`
- L467 _public prototype_ `UActorModifierCoreBase* GetCurrentModifier() const;`
- L469 _public prototype_ `void ReplaceModifier(UActorModifierCoreBase& InOldModifier, UActorModifierCoreBase& InNewModifier);`
- L470 _public prototype_ `void RemoveModifier(UActorModifierCoreBase& InModifier);`
- L473 _private prototype_ `void BuildExecutionChain(TConstArrayView<UActorModifierCoreBase*> InModifiers, UActorModifierCoreStack* InStack);`
- L474 _private prototype_ `void ExecuteCurrentModifier();`
- L477 _private member_ `TObjectPtr<UActorModifierCoreStack> ModifierStack;` — `UPROPERTY()`
- L480 _private member_ `TArray<TObjectPtr<UActorModifierCoreBase>> Modifiers;` — `UPROPERTY()`
- L482 _private member_ `int32 CurrentIndex = INDEX_NONE;`

#### Free symbols / members of external scopes

- L91 _delegate_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FModifierCompatibilityRule, const AActor*, InTargetActor);`
- L91 _prototype_ `DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FModifierCompatibilityRule, const AActor*, InTargetActor);`
- L113 _function_ `` (scope `FActorModifierCoreMetadata::SetProfilerClass`)

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/ActorModifierCoreExtension.h` (Public)


#### class `FActorModifierCoreExtension`  
`class FActorModifierCoreExtension : public TSharedFromThis<FActorModifierCoreExtension>`  
_L19-91_
- inherits: `TSharedFromThis<FActorModifierCoreExtension>`
- desc: A modifier extension is a piece of logic that multiple modifiers can reuse Can be customized for a specific scenario, only extends one modifier Differs from singleton shared object that can handle or be used by multiple modifiers Will follow the lifecycle of the modifier it is attached to
- L24 _public prototype_ `virtual ~FActorModifierCoreExtension();`
- L28 _protected function_ `virtual void OnExtensionInitialized()` — Overwrite this, called when the extension is created
- L31 _protected function_ `virtual void OnExtensionEnabled(EActorModifierCoreEnableReason InReason)` — Overwrite this, called when the modifier is enabled
- L34 _protected function_ `virtual void OnExtensionDisabled(EActorModifierCoreDisableReason InReason)` — Overwrite this, called when the modifier is disabled
- L37 _protected prototype_ `AActor* GetModifierActor() const;` — Get the modifier actor
- L40 _protected prototype_ `UWorld* GetModifierWorld() const;` — Get the modifier actor world
- L43 _protected prototype_ `ULevel* GetModifierLevel() const;` — Get the modifier actor level
- L47 _protected function_ `template <typename InModifierClass, typename = typename TEnableIf<TIsDerivedFrom<InModifierClass, UActorModifierCoreBase>::IsDerived>::Type> InModifierClass* GetModifier() const` — Get the casted modifier to which this extension is linked
- L53 _protected function_ `UActorModifierCoreBase* GetModifier() const` — Get the modifier to which this extension is linked
- L59 _protected function_ `FName GetExtensionType() const` — Get this extension type without needing a cast
- L65 _protected function_ `bool IsExtensionEnabled() const` — Is this extension enabled
- L72 _private prototype_ `void ConstructInternal(UActorModifierCoreBase* InModifier, const FName& InExtensionType);` — INTERNAL USE ONLY, will be called right after the constructor to setup this extension
- L75 _private prototype_ `void EnableExtension(EActorModifierCoreEnableReason InReason);` — INTERNAL USE ONLY, will enable the extension and call virtual functions
- L78 _private prototype_ `void DisableExtension(EActorModifierCoreDisableReason InReason);` — INTERNAL USE ONLY, will disable the extension and call virtual functions
- L81 _private member_ `TWeakObjectPtr<UActorModifierCoreBase> ModifierWeak = nullptr;` — Modifier to which this extension is linked
- L84 _private member_ `FName ExtensionType;` — Extension type to retrieve it on instance without cast needed
- L87 _private member_ `bool bExtensionInitialized = false;` — Extension was initialized properly and ready to use
- L90 _private member_ `bool bExtensionEnabled = false;` — Extension is enabled

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/ActorModifierCoreSharedObject.h` (Public)


#### class `UActorModifierCoreSharedObject`  
`class UActorModifierCoreSharedObject : public UObject`  
_L14-17_
- reflection: `UCLASS(NotPlaceable, Hidden, NotBlueprintable, NotBlueprintType, Abstract)`
- inherits: `UObject`
- desc: Abstract base class for all modifier shared data, these will be saved into one single shared actor per world, can be queried by modifiers to read and write data, create children of this class to share same data across modifiers

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/ActorModifierCoreStack.h` (Public)


#### class `UActorModifierCoreStack`  
`class UActorModifierCoreStack : public UActorModifierCoreBase`  
_L16-280_
- reflection: `UCLASS(MinimalAPI, BlueprintType, DefaultToInstanced, EditInlineNew)`
- inherits: `UActorModifierCoreBase`
- desc: A modifier stack contains modifiers and is also a modifier by itself
- L30 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierUpdated, UActorModifierCoreBase* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierAdded, UActorModifierCoreBase* , EActorModifierCoreEnableReason ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierRemoved, UActorModifierCoreBase* , EActorModifierCoreDisableReason ) static FOnModifierAdded::RegistrationType& OnModifierAdded()`
- L39 _public function_ `static FOnModifierRemoved::RegistrationType& OnModifierRemoved()`
- L44 _public function_ `static FOnModifierUpdated::RegistrationType& OnModifierMoved()`
- L49 _public function_ `static FOnModifierUpdated::RegistrationType& OnModifierReplaced()`
- L55 _public prototype_ `static UActorModifierCoreStack* Create(UActorModifierCoreComponent* InComponent, UActorModifierCoreStack* InParentStack = nullptr);` — Create a new stack by passing the actor and the parent stack if there is one
- L58 _public prototype_ `bool IsModifierStackFrozen() const;` — Returns true if this stack is frozen
- L64 _public prototype_ `void SetModifierStackFrozen(bool bInFrozen);` — Set whether the modifier stack is frozen @see bModifierStackFrozen
- L67 _public function_ `TConstArrayView<UActorModifierCoreBase*> GetModifiers() const` — Gets all modifiers in this stack, does not recurse
- L75 _public function_ `void GetClassModifiers(TArray<InModifierType*>& OutModifiers) const`
- L89 _public function_ `InModifierType* GetClassModifier() const`
- L102 _public prototype_ `UActorModifierCoreBase* GetFirstModifier() const;` — Gets the first modifier in this stack, does not recurse
- L105 _public prototype_ `UActorModifierCoreBase* GetLastModifier() const;` — Gets the last modifier in this stack, does not recurse
- L108 _public prototype_ `bool GetDependentModifiers(UActorModifierCoreBase* InModifier, TSet<UActorModifierCoreBase*>& OutDependentModifiers) const;` — Gets all modifiers found after this one in the stack that depends on this modifier
- L111 _public prototype_ `bool GetRequiredModifiers(UActorModifierCoreBase* InModifier, TSet<UActorModifierCoreBase*>& OutDependentModifiers) const;` — Gets all modifiers found before this one in the stack that are required by this modifier
- L114 _public prototype_ `bool ContainsModifier(const FName& InSearchName, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const;` — Check that we have a modifier inside this stack, checks also nested stacks
- L115 _public prototype_ `bool ContainsModifier(const UClass* InSearchClass, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const;`
- L116 _public prototype_ `bool ContainsModifier(const UActorModifierCoreBase* InSearchModifier, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const;`
- L119 _public prototype_ `UActorModifierCoreBase* FindModifier(FName InSearchName, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const;` — Finds a modifier inside this stack, returns first found, checks also nested stacks
- L120 _public prototype_ `UActorModifierCoreBase* FindModifier(const UClass* InSearchClass, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const;`
- L123 _public prototype_ `TArray<UActorModifierCoreBase*> FindModifiers(FName InSearchName, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const;` — Finds modifiers inside this stack, checks also nested stacks
- L124 _public prototype_ `TArray<UActorModifierCoreBase*> FindModifiers(const UClass* InSearchClass, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const;`
- L127 _public prototype_ `bool IsRootStack() const;` — This is the root actor stack if we do not have any parent stack
- L130 _public prototype_ `void ProcessFunctionOnRestore(const TFunction<void()>& InFunction);` — Execute those function when the stack is restored, before executing it again
- L133 _public prototype_ `void ProcessFunctionOnIdle(const TFunction<void()>& InFunction);` — Execute those function when the stack is on idle, done with updates
- L136 _public prototype_ `bool ProcessSearchFunction(TFunctionRef<bool(const UActorModifierCoreBase*)> InFunction, const FActorModifierCoreStackSearchOp& InSearchOptions) const;` — Process a search function to use before/after position context, stops when false is returned
- L139 _public function_ `virtual bool IsModifierEmpty() const override` — Does this stack contains any modifiers
- L145 _public prototype_ `void SetModifierProfiling(bool bInProfiling);` — Set profiling mode for stack and modifiers inside
- L149 _protected prototype_ `virtual void PostLoad() override;`
- L151 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L156 _protected prototype_ `virtual bool ProcessFunction(TFunctionRef<bool(const UActorModifierCoreBase*)> InFunction, const FActorModifierCoreStackSearchOp& InSearchOptions = FActorModifierCoreStackSearchOp::GetDefault()) const override;` — Process a function through each modifier in the stack and also the stacks below, stop when we return false
- L159 _protected prototype_ `bool ContainsModifierBefore(const FName& InSearchName, const UActorModifierCoreBase* InBeforeModifier) const;` — Checks that we have a modifier with this name inside this stack before another modifier, checks also nested stacks
- L160 _protected prototype_ `bool ContainsModifierBefore(const UActorModifierCoreBase* InSearchModifier, const UActorModifierCoreBase* InBeforeModifier) const;`
- L163 _protected prototype_ `bool ContainsModifierAfter(const FName& InSearchName, const UActorModifierCoreBase* InAfterModifier) const;` — Checks that we have a modifier with this name inside this stack after another modifier, checks also nested stacks
- L164 _protected prototype_ `bool ContainsModifierAfter(const UActorModifierCoreBase* InSearchModifier, const UActorModifierCoreBase* InAfterModifier) const;`
- L167 _protected prototype_ `bool IsModifierStackInitialized() const;` — Checks whether all modifier in this stack are initialized
- L170 _protected prototype_ `UActorModifierCoreBase* CloneModifier(FActorModifierCoreStackCloneOp& InCloneOp);` — Clone a modifier with options from another stack/actor, returns the newly inserted modifier, supports BATCH operation
- L173 _protected prototype_ `UActorModifierCoreBase* InsertModifier(FActorModifierCoreStackInsertOp& InInsertOp);` — Insert/Add a modifier with options in the stack, returns the newly inserted modifier, supports BATCH operation
- L176 _protected prototype_ `bool MoveModifier(FActorModifierCoreStackMoveOp& InMoveOp);` — Moves a modifier with options in the stack, if fail will return a failing reason, supports BATCH operation
- L179 _protected prototype_ `bool RemoveModifier(FActorModifierCoreStackRemoveOp& InRemoveOp);` — Removes a modifier from this stack, supports BATCH operation
- L182 _protected prototype_ `bool RemoveAllModifiers();` — Removes all modifiers from this stack in one batch to reduce updates
- L185 _protected prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;` — Register this stack to the subsystem to query it later only if root stack
- L188 _protected prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;` — Unregister this stack to the subsystem and propagates to the children modifiers
- L191 _protected prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;` — Called when the whole stack is disabled, propagates to the children modifiers
- L194 _protected prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;` — Called when the whole stack is enabled again, propagates to the children modifiers
- L197 _protected prototype_ `virtual bool IsModifierReady() const override;` — A stack will run if all its modifiers are ready to run
- L200 _protected prototype_ `virtual void RestorePreState() override;` — Restore the state before this stack was apply by reversing executed modifiers
- L203 _protected prototype_ `virtual void Apply() override;` — Execute this stack and the modifiers it contains
- L206 _protected prototype_ `virtual void OnModifiedActorTransformed() override;` — Calls OnModifyingActorTransformed of each modifier in the stack if enabled
- L209 _protected prototype_ `virtual void OnModifierDirty(UActorModifierCoreBase* DirtyModifier, bool bExecute) override;` — Called when a modifier in the stack is dirty
- L213 _private member_ `static FOnModifierAdded OnModifierAddedDelegate;` — Called when a modifier is added to the stack
- L216 _private member_ `static FOnModifierRemoved OnModifierRemovedDelegate;` — Called when a modifier is removed from the stack
- L219 _private member_ `static FOnModifierUpdated OnModifierMovedDelegate;` — Called when a modifier is moved in the stack
- L222 _private member_ `static FOnModifierUpdated OnModifierReplacedDelegate;` — Called when a modifier is replaced in the stack (blueprint)
- L225 _private prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;` — Sets the stack to receive tick events
- L228 _private prototype_ `void TickModifier(float InDelta) const;` — INTERNAL USE ONLY, allows tickable modifier to mark themselves dirty when checking IsModifierDirtyable
- L231 _private prototype_ `void OnModifierStackFrozenChanged();` — Called when the modifier stack frozen has changed
- L234 _private prototype_ `void OnActorTransformUpdated(USceneComponent*, EUpdateTransformFlags, ETeleportType);` — Called when the actor transform is updated
- L237 _private prototype_ `void OnModifierExecutionFinished(bool bInResult);` — Called when the execution task is done
- L240 _private prototype_ `void ScheduleModifierOptimization(bool bInInvalidateAll = false);` — Schedules a modifier optimization on idle
- L243 _private prototype_ `void CheckModifierOptimization(bool bInInvalidateAll);` — Checks for any possible modifier optimization within the stack
- L246 _private prototype_ `void OnBlueprintModifierReplaced(UActorModifierCoreBlueprintBase* InOldModifier, UActorModifierCoreBlueprintBase* InNewModifier);` — Replaces blueprint modifier by their new object
- L250 _private member_ `TArray<TObjectPtr<UActorModifierCoreBase>> Modifiers;` — `UPROPERTY(VisibleInstanceOnly, NoClear, Export, Instanced, Category = "Modifiers")` — Contains actual modifiers in the stack
- L253 _private member_ `FActorModifierCoreExecutionTask ExecutionTask;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)`
- L257 _private member_ `TOptional<FActorModifierCoreExecutionTask> RootExecutionTask;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Used by root stack to trigger itself
- L267 _private member_ `bool bModifierStackFrozen = false;` — `UPROPERTY(EditInstanceOnly, Category="Modifier", meta=(DisplayName="Freeze Stack"))` — EXPERIMENTAL: Freeze the stack to disable modifiers from being added/removed/moved, while also preventing restore states from occurring. The only operation allowed in a frozen state is to remove the stack as a whole. This can be used to temporarily apply a set of modifiers once, and persist the changes after removing the modifiers.
- L271 _private member_ `bool bModifierProfiling = false;` — `UPROPERTY(EditInstanceOnly, Category="Modifier", meta=(DisplayName="Enable Profiling"))` — Enable profiling for the modifiers in this stack
- L273 _private member_ `bool bAllModifiersDirty = true;`
- L276 _private member_ `TArray<TFunction<void()>> OnIdleFunctions;` — Functions to execute once when the stack is on idle
- L279 _private member_ `TArray<TFunction<void()>> OnRestoreFunctions;` — Functions to execute once when the stack is restored

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierUpdated, UActorModifierCoreBase* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierAdded, UActorModifierCoreBase* , EActorModifierCoreEnableReason ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierRemoved, UActorModifierCoreBase* , EActorModifierCoreDisableReason ) static FOnModifierAdded::RegistrationType& OnModifierAdded() { return OnModifierAddedDelegate; } static FOnModifierRemoved::RegistrationType& OnModifierRemoved() { return OnModifierRemovedDelegate; } static FOnModifierUpdated::RegistrationType& OnModifierMoved() { return OnModifierMovedDelegate; } static FOnModifierUpdated::RegistrationType& OnModifierReplaced() { return OnModifierReplacedDelegate; } static UActorModifierCoreStack* Create(UActorModifierCoreComponent* InComponent, UActorModifierCoreStack* InParentStack = nullptr);`
- L31 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierAdded, UActorModifierCoreBase* , EActorModifierCoreEnableReason ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierRemoved, UActorModifierCoreBase* , EActorModifierCoreDisableReason ) static FOnModifierAdded::RegistrationType& OnModifierAdded() { return OnModifierAddedDelegate; } static FOnModifierRemoved::RegistrationType& OnModifierRemoved() { return OnModifierRemovedDelegate; } static FOnModifierUpdated::RegistrationType& OnModifierMoved() { return OnModifierMovedDelegate; } static FOnModifierUpdated::RegistrationType& OnModifierReplaced() { return OnModifierReplacedDelegate; } static UActorModifierCoreStack* Create(UActorModifierCoreComponent* InComponent, UActorModifierCoreStack* InParentStack = nullptr);`
- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierRemoved, UActorModifierCoreBase* , EActorModifierCoreDisableReason ) static FOnModifierAdded::RegistrationType& OnModifierAdded() { return OnModifierAddedDelegate; } static FOnModifierRemoved::RegistrationType& OnModifierRemoved() { return OnModifierRemovedDelegate; } static FOnModifierUpdated::RegistrationType& OnModifierMoved() { return OnModifierMovedDelegate; } static FOnModifierUpdated::RegistrationType& OnModifierReplaced() { return OnModifierReplacedDelegate; } static UActorModifierCoreStack* Create(UActorModifierCoreComponent* InComponent, UActorModifierCoreStack* InParentStack = nullptr);`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/ActorModifierRenderStateDirtyEvent.h` (Public)


#### enum `UE::ActorModifierCore::ERenderStateDirtyReason`  
`enum class ERenderStateDirtyReason : uint8`  
_L14-30_
- L17 _public enumerator_ `Unknown = 0` — Render state change reason is not known
- L19 _public enumerator_ `Visibility = 1 << 0` — Render state was changed because a primitive became visible/hidden
- L21 _public enumerator_ `Material = 1 << 1` — Render state was changed because a material was changed
- L23 _public enumerator_ `TranslucencyPriority = 1 << 2` — Render state was dirtied because of translucency priority
- L25 _public enumerator_ `Geometry = 1 << 3` — Render state was dirtied because of geometry change
- L27 _public enumerator_ `SceneTree = 1 << 4` — Render state dirtied because of a scene tree change
- L29 _public enumerator_ `All = 0xFF`

#### struct `UE::ActorModifierCore::FRenderStateDirtyReasonScope`  
`struct FRenderStateDirtyReasonScope : public FNoncopyable`  
_L46-53_
- inherits: `FNoncopyable`
- desc: Tracks the reason a render state dirty happened. Used to avoid unnecessary computations from modifiers.
- L48 _public prototype_ `explicit FRenderStateDirtyReasonScope(ERenderStateDirtyReason InReason);`
- L49 _public prototype_ `~FRenderStateDirtyReasonScope();`
- L52 _private member_ `ERenderStateDirtyReason PreviousReason;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API ACTORMODIFIERCORE_API`
- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace ActorModifierCore` (scope `UE`)
- L31 _prototype_ `ENUM_CLASS_FLAGS(ERenderStateDirtyReason);` (scope `UE::ActorModifierCore`)
- L34 _prototype_ `ERenderStateDirtyReason GetRenderStateDirtyReason();` (scope `UE::ActorModifierCore`) — Get the current render state reason
- L40 _prototype_ `bool IsRenderStateDirtyRelevant(ERenderStateDirtyReason InReason);` (scope `UE::ActorModifierCore`) — Determines whether the given reason is part of the current render state dirty reason When the current reason is 'unknown' this returns true.

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/Blueprints/ActorModifierCoreBlueprintBase.h` (Public)


#### class `UActorModifierCoreBlueprintBase`  
`class UActorModifierCoreBlueprintBase : public UActorModifierCoreBase`  
_L11-75_
- reflection: `UCLASS(MinimalAPI, Blueprintable, Abstract, EditInlineNew, HideCategories=(Tags, AssetUserData, Activation, Collision, Cooking))`
- inherits: `UActorModifierCoreBase`
- desc: Abstract base class for all blueprint modifier
- L20 _protected prototype_ `void OnModifierSetupEvent(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, FActorModifierCoreMetadata& OutMetadata);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called once to setup modifier metadata
- L24 _protected prototype_ `void OnModifierReplacedEvent(AActor* InTargetActor);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called when the modifier gets recompiled and replaced in the stack
- L28 _protected prototype_ `void OnModifierAddedEvent(AActor* InTargetActor, EActorModifierCoreEnableReason InReason);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called when this modifier is added in a stack on an actor
- L32 _protected prototype_ `void OnModifierEnabledEvent(AActor* InTargetActor, EActorModifierCoreEnableReason InReason);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called when this modifier is enabled
- L36 _protected prototype_ `void OnModifierDisabledEvent(AActor* InTargetActor, EActorModifierCoreDisableReason InReason);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called when this modifier is disabled
- L40 _protected prototype_ `void OnModifierRemovedEvent(AActor* InTargetActor, EActorModifierCoreDisableReason InReason);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called when this modifier is removed from a stack on an actor
- L44 _protected prototype_ `void OnModifierSaveStateEvent(AActor* InTargetActor);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called before this modifier is applied on an actor to save all relevant state
- L48 _protected prototype_ `void OnModifierRestoreStateEvent(AActor* InTargetActor);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers", meta=(ForceAsFunction))` — Called to restore this modifier actions on an actor
- L52 _protected prototype_ `bool OnModifierApplyEvent(AActor* InTargetActor, FText& OutFailReason);` — `UFUNCTION(BlueprintImplementableEvent, Category="Modifiers")` — Called to apply a custom action on an actor
- L56 _protected prototype_ `void FlagModifierDirty();` — `UFUNCTION(BlueprintCallable, Category="Modifiers")` — Flag this modifier as needing an update after a property value has changed
- L61 _private prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L66 _private prototype_ `virtual void OnModifierCDOSetup(FActorModifierCoreMetadata& InMetadata) override;`
- L67 _private prototype_ `virtual void OnModifierAdded(EActorModifierCoreEnableReason InReason) override;`
- L68 _private prototype_ `virtual void OnModifierEnabled(EActorModifierCoreEnableReason InReason) override;`
- L69 _private prototype_ `virtual void OnModifierDisabled(EActorModifierCoreDisableReason InReason) override;`
- L70 _private prototype_ `virtual void OnModifierRemoved(EActorModifierCoreDisableReason InReason) override;`
- L71 _private prototype_ `virtual void SavePreState() override;`
- L72 _private prototype_ `virtual void RestorePreState() override;`
- L73 _private prototype_ `virtual void Apply() override;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/Blueprints/ActorModifierCoreGeneratedClass.h` (Public)


#### class `UActorModifierCoreGeneratedClass`  
`class UActorModifierCoreGeneratedClass : public UBlueprintGeneratedClass`  
_L11-14_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintGeneratedClass`
- desc: Blueprint modifier class generated by UActorModifierCoreBlueprint

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/Profiler/ActorModifierCoreProfiler.h` (Public)


#### class `FActorModifierCoreProfiler`  
`class FActorModifierCoreProfiler : public TSharedFromThis<FActorModifierCoreProfiler>`  
_L11-96_
- inherits: `TSharedFromThis<FActorModifierCoreProfiler>`
- desc: Profiler class to track modifier usage and performance
- L17 _public member_ `static inline const FName ExecutionTimeName = TEXT("Exe`
- L18 _public member_ `static inline const FName AverageExecutionTimeName = TEXT("Ave`
- L19 _public member_ `static inline const FName TotalExecutionTimeName = TEXT("Tot`
- L20 _public member_ `static inline const FName FrameCountDeltaName = TEXT("Fra`
- L21 _public member_ `static inline const FName FrameRateDeltaName = TEXT("Fra`
- L23 _public prototype_ `virtual ~FActorModifierCoreProfiler();`
- L26 _public prototype_ `virtual void SetupProfilingStats();` — Override this in child classes to setup stats being measured by the profiler
- L29 _public prototype_ `virtual void BeginProfiling();` — Override this in child classes to measure initial stats, called before modifier is applied
- L32 _public prototype_ `virtual void EndProfiling();` — Override this in child classes to measure final stats, called after modifier is applied
- L35 _public prototype_ `virtual TSet<FName> GetMainProfilingStats() const;` — Gets the main stats to display and hide the others
- L37 _public function_ `FName GetProfilerType() const`
- L42 _public function_ `FString GetProfilerTag() const`
- L47 _public function_ `TSharedPtr<FStructOnScope> GetStructProfilerStats() const`
- L52 _public function_ `UActorModifierCoreBase* GetModifier() const`
- L58 _public function_ `template <typename InModifierClass, typename = typename TEnableIf<TIsDerivedFrom<InModifierClass, UActorModifierCoreBase>::IsDerived>::Type> InModifierClass* GetModifier() const`
- L63 _public prototype_ `AActor* GetModifierActor() const;`
- L65 _public prototype_ `double GetExecutionTime() const;`
- L66 _public prototype_ `double GetAverageExecutionTime() const;`
- L67 _public prototype_ `double GetTotalExecutionTime() const;`
- L68 _public prototype_ `int64 GetFrameCountDelta() const;`
- L69 _public prototype_ `float GetFrameRateDelta() const;`
- L73 _protected prototype_ `void ConstructInternal(UActorModifierCoreBase* InModifier, const FName& InProfilerType);` — INTERNAL USE ONLY, called after this class instance is created
- L76 _protected member_ `FInstancedPropertyBag ProfilerStats;` — Used to store and update profiling stats
- L80 _private member_ `TWeakObjectPtr<UActorModifierCoreBase> ModifierWeak = nullptr;` — Profiled modifier
- L83 _private member_ `FName ProfilerType;` — Type of this profiler object
- L86 _private member_ `TSharedPtr<FStructOnScope> StructProfilerStats = nullptr;` — Used to only read profiling stats
- L89 _private member_ `FString ProfilerTag;` — Profiler tag for log
- L91 _private member_ `float FrameRateStart = 0.f;`
- L92 _private member_ `uint64 FrameCountStart = 0;`
- L93 _private member_ `uint64 ExecutionTimeStart = 0;`
- L94 _private member_ `double TotalExecutionTime = 0;`
- L95 _private member_ `uint64 ExecutionCount = 0;`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/Utilities/ActorModifierCoreLibrary.h` (Public)


#### class `UActorModifierCoreLibrary`  
`class UActorModifierCoreLibrary : public UBlueprintFunctionLibrary`  
_L14-324_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Modifier Library")`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint Create/Read/Update/Delete operations for modifiers
- L24 _public prototype_ `static void MarkModifierDirty(UActorModifierCoreBase* InModifier);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Marks the modifier dirty @param InModifier The modifier to dirty
- L34 _public prototype_ `static bool FindModifierStack(AActor* InActor, UActorModifierCoreStack*& OutModifierStack, bool bInCreateIfNone = false);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier stack or create one if none is found @param InActor The actor to get the modifier stack from @param OutModifierStack [Out] The modifier stack for this actor @param bInCreateIfNone Whether to create the modifier stack if none is found @return true when a valid modifier stack is returned
- L44 _public prototype_ `static bool InsertModifier(UActorModifierCoreStack* InModifierStack, const FActorModifierCoreInsertOperation& InOperation, UActorModifierCoreBase*& OutNewModifier);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Creates and insert a new modifier into a modifier stack @param InModifierStack The modifier stack to use for the operation @param InOperation The data for this operation @param OutNewModifier [Out] The newly created modifier @return true when a valid modifier is returned
- L54 _public prototype_ `static bool CloneModifier(UActorModifierCoreStack* InModifierStack, const FActorModifierCoreCloneOperation& InOperation, UActorModifierCoreBase*& OutNewModifier);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Clones an existing modifier into a modifier stack @param InModifierStack The modifier stack to use for the operation @param InOperation The data for this operation @param OutNewModifier [Out] The newly created modifier @return true when a valid modifier is returned
- L63 _public prototype_ `static bool MoveModifier(UActorModifierCoreStack* InModifierStack, const FActorModifierCoreMoveOperation& InOperation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Moves an existing modifier into a modifier stack @param InModifierStack The modifier stack to use for the operation @param InOperation The data for this operation @return true when the operation was successful
- L72 _public prototype_ `static bool RemoveModifier(UActorModifierCoreStack* InModifierStack, const FActorModifierCoreRemoveOperation& InOperation);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Removes an existing modifier from a modifier stack @param InModifierStack The modifier stack to use for the operation @param InOperation The data for this operation @return true when the operation was successful
- L81 _public prototype_ `static bool EnableModifier(UActorModifierCoreBase* InModifier, bool bInState);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Sets the state of an existing modifier @param InModifier The modifier to use for the operation @param bInState The new state for the modifier @return true when the operation was successful
- L90 _public prototype_ `static bool IsModifierEnabled(const UActorModifierCoreBase* InModifier, bool& bOutEnabled);` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Utility")` — Checks the state of an existing modifier @param InModifier The modifier to read from @param bOutEnabled The modifier enabled state @return true when the operation was successful
- L99 _public prototype_ `static bool GetModifierStack(const UActorModifierCoreBase* InModifier, UActorModifierCoreStack*& OutModifierStack);` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier stack this modifier is in @param InModifier The modifier to read from @param OutModifierStack [Out] The modifier stack this modifier belongs to @return true when a valid stack is returned
- L108 _public prototype_ `static bool GetModifierActor(const UActorModifierCoreBase* InModifier, AActor*& OutModifiedActor);` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Utility")` — Retrieves the actor modified by a modifier @param InModifier The modifier to read from @param OutModifiedActor [Out] The actor modified by this modifier @return true when a valid actor is returned
- L117 _public prototype_ `static bool GetModifierName(const UActorModifierCoreBase* InModifier, FName& OutModifierName);` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier name of an existing modifier @param InModifier The modifier to read from @param OutModifierName [Out] The modifier name @return true when a valid name is returned
- L126 _public prototype_ `static bool GetModifierNameByClass(TSubclassOf<UActorModifierCoreBase> InModifierClass, FName& OutModifierName);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier name from a modifier class @param InModifierClass The modifier class to resolve the name from @param OutModifierName [Out] The modifier name @return true when a valid name is returned
- L135 _public prototype_ `static bool GetModifierCategory(const UActorModifierCoreBase* InModifier, FName& OutModifierCategory);` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier category of an existing modifier @param InModifier The modifier to read from @param OutModifierCategory [Out] The modifier category @return true when a valid category is returned
- L144 _public prototype_ `static bool GetModifierCategoryByClass(TSubclassOf<UActorModifierCoreBase> InModifierClass, FName& OutModifierCategory);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier category from a modifier class @param InModifierClass The modifier class to resolve the category from @param OutModifierCategory [Out] The modifier category @return true when a valid category is returned
- L152 _public prototype_ `static bool GetModifierCategories(TSet<FName>& OutModifierCategories);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier categories available @param OutModifierCategories [Out] The modifier categories registered @return true when the operation was successful
- L161 _public prototype_ `static bool GetModifiersByCategory(FName InCategory, TSet<TSubclassOf<UActorModifierCoreBase>>& OutSupportedModifierClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifiers classes by a category @param InCategory The modifier category to match @param OutSupportedModifierClasses [Out] The modifier classes that match the category @return true when the operation was successful
- L170 _public prototype_ `static bool GetModifierClass(FName InModifierName, TSubclassOf<UActorModifierCoreBase>& OutModifierClass);` — `UFUNCTION(BlueprintPure, Category="Motion Design|Modifiers|Utility")` — Retrieves the modifier class from a modifier name @param InModifierName The modifier name to resolve @param OutModifierClass [Out] The modifier class that matches the name @return true when the operation was successful
- L179 _public prototype_ `static bool GetStackModifiers(const UActorModifierCoreStack* InModifierStack, TArray<UActorModifierCoreBase*>& OutModifiers);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves all modifiers from a modifier stack @param InModifierStack The modifier stack to read from @param OutModifiers [Out] The modifiers contained within the stack @return true when the operation was successful
- L188 _public prototype_ `static bool GetDependentModifiers(UActorModifierCoreBase* InModifier, TSet<UActorModifierCoreBase*>& OutModifiers);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves all modifiers found after this one that depends on this modifier @param InModifier The modifier that is required by others @param OutModifiers [Out] The dependent modifiers that required the modifier @return true when the operation was successful
- L197 _public prototype_ `static bool GetRequiredModifiers(UActorModifierCoreBase* InModifier, TSet<UActorModifierCoreBase*>& OutModifiers);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Retrieves all modifiers found before this one that are required for this modifier @param InModifier The modifier that requires other modifiers @param OutModifiers [Out] The required modifiers to use the modifier @return true when the operation was successful
- L206 _public prototype_ `static UActorModifierCoreBase* FindModifierByClass(UActorModifierCoreStack* InModifierStack, TSubclassOf<UActorModifierCoreBase> InModifierClass);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility", meta=(DeterminesOutputType="InModifierClass"))` — Returns the first modifier of a specified class in the stack @param InModifierStack The modifier stack to search @param InModifierClass The class of the modifier to look for @return the modifier of the specified class, if any.
- L215 _public prototype_ `static UActorModifierCoreBase* FindModifierByName(const UActorModifierCoreStack* InModifierStack, FName InModifierName);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Returns the first modifier with specified name in the stack @param InModifierStack The modifier stack to search @param InModifierName The name of the modifier to look for @return the modifier with specified name, if any.
- L224 _public prototype_ `static TArray<UActorModifierCoreBase*> FindModifiersByClass(UActorModifierCoreStack* InModifierStack, TSubclassOf<UActorModifierCoreBase> InModifierClass);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility", meta=(DeterminesOutputType="InModifierClass"))` — Finds all modifiers with specified class in the stack @param InModifierStack The modifier stack to search @param InModifierClass The class of the modifier to look for @return the modifiers with specified class, if any.
- L233 _public prototype_ `static TArray<UActorModifierCoreBase*> FindModifiersByName(UActorModifierCoreStack* InModifierStack, FName InModifierName);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Finds all modifiers with specified class in the stack @param InModifierStack The modifier stack to search @param InModifierName The name of the modifier to look for @return the modifiers with specified name, if any.
- L242 _public prototype_ `static bool ContainsModifier(UActorModifierCoreStack* InModifierStack, UActorModifierCoreBase* InModifier);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Checks if a modifier is contained in the stack @param InModifierStack The modifier stack to search @param InModifier The modifier to look for @return true if the modifier is contained within that stack
- L253 _public prototype_ `static bool GetSupportedModifiers(AActor* InActor, TSet<TSubclassOf<UActorModifierCoreBase>>& OutSupportedModifierClasses, EActorModifierCoreStackPosition InContextPosition = EActorModifierCoreStackPosition::Before, UActorModifierCoreBase* InContextModifier = nullptr);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Gets all modifier classes supported by this actor at a specific position @param InActor The actor to check for compatibility @param OutSupportedModifierClasses [Out] The modifier classes available @param InContextPosition The context position to insert the modifier @param InContextModifier The context modifier for insertion @return true when the operation was successful
- L261 _public prototype_ `static bool GetAvailableModifiers(TSet<TSubclassOf<UActorModifierCoreBase>>& OutAvailableModifierClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Gets all available modifier classes registered @param OutAvailableModifierClasses [Out] The modifier classes registered and available to use @return true when the operation was successful
- L270 _public prototype_ `static FActorModifierCoreMetadata& SetModifierMetadataName(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, FName InName);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Sets the modifier metadata name @param InMetadata The modifier metadata to use @param InName The modifier name to set @return The modifier metadata to chain operations
- L279 _public prototype_ `static FActorModifierCoreMetadata& SetModifierMetadataCategory(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, FName InCategory);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Sets the modifier metadata category @param InMetadata The modifier metadata to use @param InCategory The modifier category to set @return The modifier metadata to chain operations
- L288 _public prototype_ `static FActorModifierCoreMetadata& SetModifierMetadataDisplayName(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, const FText& InName);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Sets the modifier metadata display name (EDITOR-ONLY) @param InMetadata The modifier metadata to use @param InName The modifier name to set @return The modifier metadata to chain operations
- L296 _public prototype_ `static FActorModifierCoreMetadata& SetModifierMetadataColor(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, const FLinearColor& InColor);` — Sets the modifier metadata color (EDITOR-ONLY) @param InMetadata The modifier metadata to use @param InColor The modifier color to set @return The modifier metadata to chain operations
- L305 _public prototype_ `static FActorModifierCoreMetadata& SetModifierMetadataDescription(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, const FText& InDescription);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Sets the modifier metadata description (EDITOR-ONLY) @param InMetadata The modifier metadata to use @param InDescription The modifier description to set @return The modifier metadata to chain operations
- L314 _public prototype_ `static FActorModifierCoreMetadata& AddModifierMetadataDependency(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, TSubclassOf<UActorModifierCoreBase> InModifierClass);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Adds a modifier metadata dependency for this modifier @param InMetadata The modifier metadata to use @param InModifierClass The modifier dependency to add @return The modifier metadata to chain operations
- L323 _public prototype_ `static FActorModifierCoreMetadata& SetModifierMetadataCompatibilityRule(UPARAM(Ref) FActorModifierCoreMetadata& InMetadata, const FModifierCompatibilityRule& InDelegate);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Modifiers|Utility")` — Sets the modifier metadata compatibility rule @param InMetadata The modifier metadata to use @param InDelegate The modifier rule to set @return The modifier metadata to chain operations

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/Utilities/ActorModifierCoreLibraryDefs.h` (Public)


#### struct `FActorModifierCoreInsertOperation`  
`struct FActorModifierCoreInsertOperation`  
_L11-23_
- reflection: `USTRUCT(BlueprintType)`
- L16 _public member_ `TSubclassOf<UActorModifierCoreBase> ModifierClass;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`
- L19 _public member_ `EActorModifierCoreStackPosition InsertPosition = EActorModifierCoreStackPosition::Before;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`
- L22 _public member_ `TObjectPtr<UActorModifierCoreBase> InsertPositionContext = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`

#### struct `FActorModifierCoreCloneOperation`  
`struct FActorModifierCoreCloneOperation`  
_L26-38_
- reflection: `USTRUCT(BlueprintType)`
- L31 _public member_ `TObjectPtr<UActorModifierCoreBase> CloneModifier = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`
- L34 _public member_ `EActorModifierCoreStackPosition ClonePosition = EActorModifierCoreStackPosition::Before;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`
- L37 _public member_ `TObjectPtr<UActorModifierCoreBase> ClonePositionContext = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`

#### struct `FActorModifierCoreMoveOperation`  
`struct FActorModifierCoreMoveOperation`  
_L41-53_
- reflection: `USTRUCT(BlueprintType)`
- L46 _public member_ `TObjectPtr<UActorModifierCoreBase> MoveModifier = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`
- L49 _public member_ `EActorModifierCoreStackPosition MovePosition = EActorModifierCoreStackPosition::Before;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`
- L52 _public member_ `TObjectPtr<UActorModifierCoreBase> MovePositionContext = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`

#### struct `FActorModifierCoreRemoveOperation`  
`struct FActorModifierCoreRemoveOperation`  
_L56-65_
- reflection: `USTRUCT(BlueprintType)`
- L61 _public member_ `TObjectPtr<UActorModifierCoreBase> RemoveModifier = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`
- L64 _public member_ `bool bRemoveDependencies = false;` — `UPROPERTY(BlueprintReadWrite, Category="Motion Design|Modifiers|Utility")`

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Modifiers/Utilities/ActorModifierCoreUtilities.h` (Public)


#### Free symbols / members of external scopes

- L7 _namespace_ `namespace UE`
- L7 _namespace_ `namespace ActorModifierCore` (scope `UE`)
- L7 _namespace_ `namespace Utilities` (scope `UE::ActorModifierCore`)
- L10 _prototype_ `UActorModifierCoreBase* FindFirstActorModifierByClass(const AActor* InStartActor, const TSubclassOf<UActorModifierCoreBase>& InModifierClass);` (scope `UE::ActorModifierCore::Utilities`) — Climbs up the attachment tree to find a modifier with a specific class
- L13 _prototype_ `FString GetActorNameSafe(const AActor* InActor);` (scope `UE::ActorModifierCore::Utilities`) — Safely gets the actor label or name (if label is empty), returning an empty string if actor is null

### `Plugins/VirtualProduction/ActorModifierCore/Source/ActorModifierCore/Public/Subsystems/ActorModifierCoreSubsystem.h` (Public)


#### class `UActorModifierCoreSubsystem`  
`class UActorModifierCoreSubsystem : public UEngineSubsystem, public FTickableGameObject`  
_L22-237_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem,FTickableGameObject`
- desc: This subsystem handle all modifiers stack active in the engine and allows to create modifiers with registered metadata
- L32 _public member_ `static constexpr const TCHAR* BlueprintClass = TEXT("/Sc`
- L34 _public function_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierClassRegistered, const FActorModifierCoreMetadata& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierStackRegistered, const UActorModifierCoreStack* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierReplaced, UActorModifierCoreBlueprintBase* , UActorModifierCoreBlueprintBase* ) static FOnModifierClassRegistered::RegistrationType& OnModifierClassRegistered()`
- L43 _public function_ `static FOnModifierClassRegistered::RegistrationType& OnModifierClassUnregistered()`
- L48 _public function_ `static FOnModifierReplaced::RegistrationType& OnModifierReplaced()`
- L53 _public prototype_ `static UActorModifierCoreSubsystem* Get();`
- L56 _public prototype_ `static FTSTicker& GetModifierTicker();` — Gets the ticker for modifiers to use instead of CoreTicker
- L58 _public prototype_ `UActorModifierCoreSubsystem();`
- L61 _public prototype_ `bool RegisterModifierClass(const UClass* InModifierClass, bool bInOverrideIfExists = false);` — Register a modifier class or override an already existing one
- L62 _public prototype_ `bool UnregisterModifierClass(const FName& InName);`
- L63 _public prototype_ `bool UnregisterModifierClass(const UClass* InModifierClass);`
- L64 _public prototype_ `bool IsRegisteredModifierClass(const FName& InName) const;`
- L65 _public prototype_ `bool IsRegisteredModifierClass(const UClass* InClass) const;`
- L68 _public prototype_ `FName GetRegisteredModifierName(const UClass* InModifierClass) const;` — Return the modifier name or none from the modifier class provided
- L71 _public prototype_ `TSubclassOf<UActorModifierCoreBase> GetRegisteredModifierClass(FName InModifierName) const;` — Return the modifier class from the modifier name provided
- L74 _public prototype_ `TSet<TSubclassOf<UActorModifierCoreBase>> GetRegisteredModifierClasses() const;` — Return a set of class for all modifiers registered
- L77 _public prototype_ `TSet<FName> GetRegisteredModifiers() const;` — Returns the name of modifiers that are currently registered
- L80 _public prototype_ `TSet<FName> GetAllowedModifiers(AActor* InActor, UActorModifierCoreBase* InContextModifier = nullptr, EActorModifierCoreStackPosition InContextPosition = EActorModifierCoreStackPosition::Before) const;` — Returns the modifiers names that are allowed for specific actor/stack and before another modifier
- L83 _public prototype_ `TSet<FName> GetCategoryModifiers(const FName& InCategory) const;` — Returns the modifiers name that match a specific category
- L86 _public prototype_ `TSet<FName> GetModifierCategories() const;` — Returns the categories for all registered modifiers
- L89 _public prototype_ `FName GetModifierCategory(const FName& InModifier) const;` — Returns the category this modifier is in
- L93 _public prototype_ `TSet<FName> GetHiddenModifiers() const;` — Returns the modifiers hidden to the user
- L97 _public prototype_ `TArray<UActorModifierCoreBase*> GetAllowedMoveModifiers(UActorModifierCoreBase* InMoveModifier) const;` — Returns modifiers from the stack where we can move the provided modifier, required and dependent modifiers from this MoveModifier will not appear in the list
- L100 _public prototype_ `UActorModifierCoreStack* GetActorModifierStack(const AActor* InActor) const;` — This is the correct way to retrieve a modifier stack for a specific actor if it has one
- L103 _public prototype_ `UActorModifierCoreStack* AddActorModifierStack(AActor* InActor) const;` — This is the correct way to add modifier component to a specific actor if it has none
- L106 _public prototype_ `const AActor* GetModifierStackActor(const UActorModifierCoreStack* InStack) const;` — Return the actor this stack is linked to
- L109 _public prototype_ `bool ForEachModifierMetadata(TFunctionRef<bool(const FActorModifierCoreMetadata&)> InProcessFunction) const;` — Loops through each registered modifier metadata, only used to read
- L112 _public prototype_ `bool ProcessModifierMetadata(const FName& InName, TFunctionRef<bool(const FActorModifierCoreMetadata&)> InProcessFunction) const;` — Process this on matching registered metadata, only used to read
- L115 _public prototype_ `UActorModifierCoreSharedObject* GetModifierSharedObject(ULevel* InLevel, TSubclassOf<UActorModifierCoreSharedObject> InClass, bool bInCreateIfNone = false) const;` — Get modifier shared object from a specific level and class, only one or none can exists per level
- L118 _public prototype_ `bool EnableModifiers(const TSet<UActorModifierCoreBase*>& InModifiers, bool bInEnabled, bool bInShouldTransact = false) const;` — Enable or disable modifiers, will update the original array and perform a transaction if wanted
- L121 _public prototype_ `TArray<UActorModifierCoreBase*> AddActorsModifiers(const TSet<AActor*>& InActors, FActorModifierCoreStackInsertOp& InAddOp) const;` — Add a modifier to actors, adds a stack automatically if none is found, will update the original array and perform a transaction if wanted
- L124 _public prototype_ `bool RemoveActorsModifiers(const TSet<AActor*>& InActors, bool bInShouldTransact = false) const;` — Remove all modifiers from actors, will update the original array and perform a transaction if wanted
- L127 _public prototype_ `bool RemoveModifiers(const TSet<UActorModifierCoreBase*>& InModifiers, FActorModifierCoreStackRemoveOp& InRemoveOp) const;` — Remove modifiers from different actors or stacks, will update the original array and perform a transaction if wanted
- L130 _public prototype_ `bool RemoveModifierStacks(const TSet<UActorModifierCoreStack*>& InStacks, bool bInShouldTransact = false) const;` — Removes modifier components and modifier stacks
- L133 _public prototype_ `UActorModifierCoreBase* InsertModifier(UActorModifierCoreStack* InStack, FActorModifierCoreStackInsertOp& InInsertOp) const;` — Insert a modifier in a stack before or after another modifier, will perform a transaction if wanted
- L136 _public prototype_ `bool MoveModifier(UActorModifierCoreStack* InStack, FActorModifierCoreStackMoveOp& InMoveOp) const;` — Moves a modifier in a stack before or after another modifier, will perform a transaction if wanted
- L139 _public prototype_ `bool MoveModifiers(const TArray<UActorModifierCoreBase*>& InModifiers, UActorModifierCoreStack* InStack, FActorModifierCoreStackMoveOp& InMoveOp) const;` — Move modifiers to a specific target modifier position, will perform menu action transaction if wanted
- L142 _public prototype_ `TArray<UActorModifierCoreBase*> CloneModifiers(const TArray<UActorModifierCoreBase*>& InModifiers, UActorModifierCoreStack* InStack, FActorModifierCoreStackCloneOp& InCloneOp) const;` — Clone modifiers to a specific target modifier position, will perform menu action transaction if wanted
- L145 _public prototype_ `void GetSortedModifiers(const TSet<UActorModifierCoreBase*>& InModifiers, AActor* InTargetActor, UActorModifierCoreBase* InTargetModifier, EActorModifierCoreStackPosition InPosition, TArray<UActorModifierCoreBase*>& OutMoveModifiers, TArray<UActorModifierCoreBase*>& OutCloneModifiers) const;` — Get order dependent modifiers in the correct order for stack operations
- L149 _protected member_ `static FOnModifierClassRegistered OnModifierClassRegisteredDelegate;` — Called when a modifier class is registered
- L152 _protected member_ `static FOnModifierClassRegistered OnModifierClassUnregisteredDelegate;` — Called when a modifier class is unregistered
- L155 _protected member_ `static FOnModifierStackRegistered OnModifierStackRegisteredDelegate;` — Called when an actor modifier stack is registered
- L158 _protected member_ `static FOnModifierStackRegistered OnModifierStackUnregisteredDelegate;` — Called when an actor modifier stack is unregistered
- L161 _protected member_ `static FOnModifierReplaced OnModifierReplacedDelegate;` — Called when a blueprint modifier gets replaced
- L164 _protected member_ `static FTSTicker ModifierTicker;` — Ticker for modifiers to use instead of CoreTicker
- L167 _protected prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L168 _protected prototype_ `virtual bool IsTickableInEditor() const override;`
- L169 _protected prototype_ `virtual void Tick(float InDeltaTime) override;`
- L170 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L174 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L175 _protected prototype_ `virtual void Deinitialize() override;`
- L178 _protected prototype_ `void OnInsertModifier(const FActorModifierCoreStackInsertOp& InInsertOp) const;`
- L181 _protected prototype_ `bool RegisterActorModifierStack(UActorModifierCoreStack* InStack);` — Register a root actor stack to query this actor stack from everywhere, is called automatically at creation or deserialization by stack
- L184 _protected prototype_ `bool UnregisterActorModifierStack(const AActor* InActor);` — Unregister a root stack by providing the actor it is attached to
- L187 _protected prototype_ `bool UnregisterActorModifierStack(const UActorModifierCoreStack* InStack);` — Unregister a root stack from an actor by providing the stack itself
- L190 _protected prototype_ `bool IsRegisteredActorModifierStack(const AActor* InActor) const;` — Do we have a root modifier stack for this actor
- L193 _protected prototype_ `bool IsRegisteredActorModifierStack(const UActorModifierCoreStack* InStack) const;` — Do we have a registered root stack
- L196 _protected prototype_ `bool ValidateModifierCreation(const FName& InName, const UActorModifierCoreStack* InStack, FText& OutFailReason, UActorModifierCoreBase* InBeforeModifier = nullptr) const;` — Checks whether we can add a modifier to the stack
- L199 _protected prototype_ `UActorModifierCoreBase* CreateModifierInstance(const FName& InName, UActorModifierCoreStack* InStack, FText& OutFailReason, UActorModifierCoreBase* InBeforeModifier = nullptr) const;` — Creates a modifier based on a name and a stack, should be called by the stack itself
- L202 _protected prototype_ `bool BuildModifierDependencies(const FName& InName, TArray<FName>& OutBeforeModifiers) const;` — Builds a modifier dependency list, does not make additional checks
- L205 _protected prototype_ `void ScanForModifiers();` — Done only once at subsystem initialization
- L207 _protected prototype_ `void OnAssetRegistryFilesLoaded();`
- L208 _protected prototype_ `void OnAssetRegistryAssetAdded(const FAssetData& InAssetData);`
- L209 _protected prototype_ `void OnAssetRegistryAssetUpdated(const FAssetData& InAssetData);`
- L210 _protected prototype_ `void OnAssetRegistryAssetRemoved(const FAssetData& InAssetData);`
- L212 _protected prototype_ `void OnBlueprintObjectsReplaced(const TMap<UObject*, UObject*>& InReplacements);`
- L214 _protected prototype_ `void RegisterModifierAsset(const FAssetData& InAssetData);`
- L215 _protected prototype_ `void UnregisterModifierAsset(const FAssetData& InAssetData);`
- L218 _protected prototype_ `bool RegisterModifierSharedProvider(AActorModifierCoreSharedActor* InSharedActor) const;` — Registers a modifier shared provider actor for a world
- L221 _protected prototype_ `bool UnregisterModifierSharedProvider(const AActor* InSharedActor) const;` — Unregisters a modifier shared provider actor for a world
- L224 _protected prototype_ `AActorModifierCoreSharedActor* GetModifierSharedProvider(ULevel* InLevel, bool bInSpawnIfNotFound = true) const;` — Gets a modifier shared provider for a world, creates one if none is found
- L227 _protected member_ `TMap<FName, TSharedRef<FActorModifierCoreMetadata>> ModifiersMetadata;` — stores modifiers metadata, you can override these if you want a different behaviour
- L230 _protected member_ `TMap<TWeakObjectPtr<const AActor>, TWeakObjectPtr<UActorModifierCoreStack>> ModifierStacks;` — stores modifiers stacks per actor, there should be only one root stack per actor
- L233 _protected member_ `TMap<TWeakObjectPtr<const ULevel>, TWeakObjectPtr<AActorModifierCoreSharedActor>> ModifierSharedProviders;` — Stores modifiers providers per world/level, there should be only one provider per level
- L236 _protected member_ `bool bFilesLoaded = false;` — Asset Registry files loaded

#### Free symbols / members of external scopes

- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierClassRegistered, const FActorModifierCoreMetadata& ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierStackRegistered, const UActorModifierCoreStack* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierReplaced, UActorModifierCoreBlueprintBase* , UActorModifierCoreBlueprintBase* ) static FOnModifierClassRegistered::RegistrationType& OnModifierClassRegistered() { return OnModifierClassRegisteredDelegate; } static FOnModifierClassRegistered::RegistrationType& OnModifierClassUnregistered() { return OnModifierClassUnregisteredDelegate; } static FOnModifierReplaced::RegistrationType& OnModifierReplaced() { return OnModifierReplacedDelegate; } static UActorModifierCoreSubsystem* Get();`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnModifierStackRegistered, const UActorModifierCoreStack* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierReplaced, UActorModifierCoreBlueprintBase* , UActorModifierCoreBlueprintBase* ) static FOnModifierClassRegistered::RegistrationType& OnModifierClassRegistered() { return OnModifierClassRegisteredDelegate; } static FOnModifierClassRegistered::RegistrationType& OnModifierClassUnregistered() { return OnModifierClassUnregisteredDelegate; } static FOnModifierReplaced::RegistrationType& OnModifierReplaced() { return OnModifierReplacedDelegate; } static UActorModifierCoreSubsystem* Get();`
- L36 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModifierReplaced, UActorModifierCoreBlueprintBase* , UActorModifierCoreBlueprintBase* ) static FOnModifierClassRegistered::RegistrationType& OnModifierClassRegistered() { return OnModifierClassRegisteredDelegate; } static FOnModifierClassRegistered::RegistrationType& OnModifierClassUnregistered() { return OnModifierClassUnregisteredDelegate; } static FOnModifierReplaced::RegistrationType& OnModifierReplaced() { return OnModifierReplacedDelegate; } static UActorModifierCoreSubsystem* Get();`
