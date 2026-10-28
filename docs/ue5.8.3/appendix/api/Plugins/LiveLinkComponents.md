# Plugins / LiveLinkComponents

- module root: `Plugins/Animation/LiveLink/Source/LiveLinkComponents`
- headers: 9; symbols: 109
- symbol kinds: class=8, delegate=5, function=11, macro=5, member=30, prototype=49, struct=1
- PrivateDependencyModuleNames: Slate, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine, LiveLinkInterface

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Private/LiveLinkComponentModule.h` (Private)


#### class `FLiveLinkComponentsModule`  
`class FLiveLinkComponentsModule : public ILiveLinkComponentsModule`  
_L7-14_
- inherits: `ILiveLinkComponentsModule`
- L10 _public function_ `virtual FLiveLinkComponentRegistered& OnLiveLinkComponentRegistered() override`
- L13 _private member_ `FLiveLinkComponentRegistered OnLiveLinkComponentRegisteredDelegate;`

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Private/LiveLinkComponentPrivate.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkComponents, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogLiveLinkComponents, Log, All);`

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/Controllers/LiveLinkCharacterController.h` (Public)


#### class `ULiveLinkCharacterController`  
`class ULiveLinkCharacterController : public ULiveLinkTransformController`  
_L13-22_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `ULiveLinkTransformController`
- desc: Controller that allows driving an actor's transform through a subject with the Character role.
- L19 _public prototype_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectFrameData& SubjectData) override;`
- L20 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKCOMPONENTS_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/Controllers/LiveLinkLightController.h` (Public)


#### class `ULiveLinkLightController`  
`class ULiveLinkLightController : public ULiveLinkControllerBase`  
_L16-40_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `ULiveLinkControllerBase`
- desc: Controller that uses LiveLink light data to drive a light component. UPointLightComponent and USpotLightComponent are supported for specific properties
- L23 _public member_ `FComponentReference ComponentToControl_DEPRECATED;` — `UPROPERTY()`
- L26 _public member_ `FLiveLinkTransformControllerData TransformData_DEPRECATED;` — `UPROPERTY()`
- L32 _public prototype_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectFrameData& SubjectData) override;`
- L33 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) override;`
- L34 _public prototype_ `virtual TSubclassOf<UActorComponent> GetDesiredComponentClass() const override;`
- L38 _public prototype_ `virtual void PostLoad() override;`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LIVELINKCOMPONENTS_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/Controllers/LiveLinkTransformController.h` (Public)


#### struct `FLiveLinkTransformControllerData`  
`struct FLiveLinkTransformControllerData`  
_L17-55_
- reflection: `USTRUCT(Blueprintable)`
- L23 _public member_ `bool bWorldTransform = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Set the transform of the component in world space of in its local reference frame.
- L27 _public member_ `bool bUseLocation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", AdvancedDisplay)` — Whether we should set the owning actor's location with the value coming from live link.
- L31 _public member_ `bool bUseRotation = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", AdvancedDisplay)` — Whether we should set the owning actor's rotation with the value coming from live link.
- L35 _public member_ `bool bUseScale = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", AdvancedDisplay)` — Whether we should set the owning actor's scale with the value coming from live link.
- L42 _public member_ `bool bSweep = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", AdvancedDisplay)` — Whether we sweep to the destination location, triggering overlaps along the way and stopping short of the target if blocked by something. Only the root component is swept and checked for blocking collision, child components move without sweeping. If collision is off, this has no effect.
- L51 _public member_ `bool bTeleport = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink", AdvancedDisplay)` — Whether we teleport the physics state (if physics collision is enabled for this object). If true, physics velocity for this object is unchanged (so ragdoll parts are not affected by change in location). If false, physics velocity is updated based on the change in position (affecting ragdoll parts). If CCD is on and not teleporting, this will affect objects along the entire sweep volume.
- L53 _public prototype_ `void ApplyTransform(USceneComponent* SceneComponent, const FTransform& Transform, const FLiveLinkTransformStaticData& StaticData) const;`
- L54 _public prototype_ `void CheckForError(FName OwnerName, USceneComponent* SceneComponent) const;`

#### class `ULiveLinkTransformController`  
`class ULiveLinkTransformController : public ULiveLinkControllerBase`  
_L60-96_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `ULiveLinkControllerBase`
- L67 _public member_ `FComponentReference ComponentToControl_DEPRECATED;` — `UPROPERTY()`
- L71 _public member_ `FLiveLinkTransformControllerData TransformData;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LiveLink", meta=(ShowOnlyInnerProperties))`
- L77 _public member_ `FTransform OffsetTransform = FTransform::Identity;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — Offset transform applied in local space to the controlled scene component
- L82 _private member_ `FTransform CombinedTransform;` — Combined transform resulting from composing the incoming LiveLink transform & the offset transform
- L86 _public prototype_ `virtual void OnEvaluateRegistered() override;`
- L87 _public prototype_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectFrameData& SubjectData) override;`
- L88 _public prototype_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport) override;`
- L89 _public prototype_ `virtual TSubclassOf<UActorComponent> GetDesiredComponentClass() const override;`
- L90 _public prototype_ `virtual void SetAttachedComponent(UActorComponent* ActorComponent) override;`
- L94 _public prototype_ `virtual void PostLoad() override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKCOMPONENTS_API`

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/ILiveLinkComponentModule.h` (Public)


#### class `ILiveLinkComponentsModule`  
`class ILiveLinkComponentsModule : public IModuleInterface`  
_L16-24_
- inherits: `IModuleInterface`
- desc: Interface for LiveLinkComponent module
- L19 _public prototype_ `virtual FLiveLinkComponentRegistered& OnLiveLinkComponentRegistered() = 0;`
- L23 _public prototype_ `virtual ~ILiveLinkComponentsModule() = default;` — Virtual destructor.

#### Free symbols / members of external scopes

- L11 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLiveLinkComponentRegistered, ULiveLinkComponentController*);`
- L11 _prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FLiveLinkComponentRegistered, ULiveLinkComponentController*);`

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/LiveLinkComponentController.h` (Public)


#### class `ULiveLinkComponentController`  
`class ULiveLinkComponentController : public UActorComponent`  
_L22-147_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(LiveLink), meta=(DisplayName="LiveLink Controller", BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L27 _public prototype_ `ULiveLinkComponentController();`
- L28 _public prototype_ `~ULiveLinkComponentController();`
- L32 _public member_ `FLiveLinkSubjectRepresentation SubjectRepresentation;` — `UPROPERTY(EditAnywhere, BlueprintSetter = SetSubjectRepresentation, BlueprintGetter = GetSubjectRepresentation, Category="LiveLink")`
- L36 _public member_ `TObjectPtr<ULiveLinkControllerBase> Controller_DEPRECATED;` — `UPROPERTY(Instanced, NoClear)`
- L41 _public member_ `TMap<TSubclassOf<ULiveLinkRole>, TObjectPtr<ULiveLinkControllerBase>> ControllerMap;` — `UPROPERTY(Interp, BlueprintReadOnly, EditAnywhere, Category = "LiveLink", Instanced, NoClear, meta = (ShowOnlyInnerProperties))` — Instanced controllers used to control the desired role
- L44 _public member_ `bool bUpdateInEditor;` — `UPROPERTY(EditAnywhere, Category="LiveLink", AdvancedDisplay)`
- L48 _public member_ `FLiveLinkTickDelegate OnLiveLinkUpdated;` — `UPROPERTY(BlueprintAssignable, Category = "LiveLink")` — This Event is triggered any time new LiveLink data is available, including in the editor
- L52 _public member_ `FOnControllerMapUpdatedDelegate OnControllerMapUpdatedDelegate;` — `UPROPERTY(BlueprintAssignable, Category = "LiveLink")` — This Event is triggered any time the controller map is updated
- L57 _public member_ `FComponentReference ComponentToControl_DEPRECATED;` — `UE_DEPRECATED(5.1, "This property has been deprecated. Please use the ComponentPicker property of each controller in this LiveLink component's controller map.")` — `UPROPERTY()`
- L62 _public member_ `bool bDisableEvaluateLiveLinkWhenSpawnable = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — If true, will not evaluate LiveLink if the attached actor is a spawnable in Sequencer
- L66 _public member_ `bool bEvaluateLiveLink = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiveLink")` — If false, will not evaluate live link, effectively pausing.
- L70 _public member_ `bool bUpdateInPreviewEditor = false;` — `UPROPERTY(EditAnywhere, Category = "LiveLink", AdvancedDisplay, meta = (EditCondition = "bUpdateInEditor"))` — If true, will tick when the world is a preview (i.e Blueprint editors)
- L74 _protected member_ `bool bIsDirty;` — Keep track when component gets registered or controller map gets changed
- L77 _protected member_ `TOptional<bool> bIsSpawnableCache;` — Cache if the owner is a spawnable.
- L82 _public prototype_ `void SetControllerClassForRole(TSubclassOf<ULiveLinkRole> RoleClass, TSubclassOf<ULiveLinkControllerBase> DesiredControllerClass);` — Creates an instance of the desired controller class for a specified Role class
- L86 _public function_ `FLiveLinkSubjectRepresentation GetSubjectRepresentation() const` — `UFUNCTION(BlueprintGetter)` — Return Representation of Subject that is used in the controller
- L90 _public prototype_ `void SetSubjectRepresentation(FLiveLinkSubjectRepresentation InSubjectRepresentation);` — `UFUNCTION(BlueprintSetter)` — Set Representation of Subject that is used in the controller and update the controller map
- L93 _public prototype_ `bool IsControllerMapOutdated() const;` — Returns true if ControllerMap needs to be updated for the current Role. Useful for customization or C++ modification to the Role
- L96 _public prototype_ `void OnSubjectRoleChanged();` — Used to notify that the subject role has changed. Mainly from Customization or C++ modification to the subject's Role
- L100 _public prototype_ `UActorComponent* GetControlledComponent(TSubclassOf<ULiveLinkRole> InRoleClass) const;` — `UFUNCTION(BlueprintPure, Category="LiveLink")` — Returns the component controlled by the LiveLink controller of the input Role. Returns null if there is no controller for that Role
- L104 _public prototype_ `void SetControlledComponent(TSubclassOf<ULiveLinkRole> InRoleClass, UActorComponent* InComponent);` — `UFUNCTION(BlueprintCallable, Category = "LiveLink")` — Set the component to control for the LiveLink controller of the input Role
- L107 _public function_ `FLiveLinkControllersTicked& OnLiveLinkControllersTicked()` — Multicast delegate that broadcasts after LiveLink controllers have ticked with the latest frame of subject data
- L111 _public prototype_ `void OnEndPIE(bool bIsSimulating);` — Used to cleanup controllers when exiting PIE
- L115 _public prototype_ `virtual void OnRegister() override;`
- L116 _public prototype_ `virtual void DestroyComponent(bool bPromoteChildren = false) override;`
- L117 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L121 _public prototype_ `virtual void PostLoad() override;`
- L122 _public prototype_ `virtual void Serialize(FArchive& Ar) override;`
- L124 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L131 _protected prototype_ `TArray<TSubclassOf<ULiveLinkRole>> GetSelectedRoleHierarchyClasses(const TSubclassOf<ULiveLinkRole> InCurrentRoleClass) const;` — Returns an array representing the class hierarchy of the given class
- L132 _protected prototype_ `TSubclassOf<ULiveLinkControllerBase> GetControllerClassForRoleClass(const TSubclassOf<ULiveLinkRole> RoleClass) const;`
- L135 _protected prototype_ `void CleanupControllersInMap();` — Loops through the controller map and calls Cleanup() on each entry
- L138 _protected prototype_ `void InitializeController(ULiveLinkControllerBase* InController);` — Initializes the component that the newly created input controller should control based on its specified desired component class
- L142 _protected prototype_ `void ConvertOldControllerSystem();` — Called during loading to convert old data to new scheme.
- L146 _private member_ `FLiveLinkControllersTicked LiveLinkControllersTickedDelegate;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LIVELINKCOMPONENTS_API`
- L14 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLiveLinkTickDelegate, float, DeltaTime);`
- L14 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLiveLinkTickDelegate, float, DeltaTime);`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerMapUpdatedDelegate);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnControllerMapUpdatedDelegate);`
- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FLiveLinkControllersTicked, const ULiveLinkComponentController* const, const FLiveLinkSubjectFrameData&);`
- L17 _prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FLiveLinkControllersTicked, const ULiveLinkComponentController* const, const FLiveLinkSubjectFrameData&);`

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/LiveLinkComponentSettings.h` (Public)


#### class `ULiveLinkComponentSettings`  
`class ULiveLinkComponentSettings : public UObject`  
_L18-31_
- reflection: `UCLASS(MinimalAPI, config=Game, defaultconfig)`
- inherits: `UObject`
- desc: Settings for LiveLink.
- L26 _public member_ `TMap<TSubclassOf<ULiveLinkRole>, TSubclassOf<ULiveLinkControllerBase>> DefaultControllerForRole;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink", meta = (AllowAbstract = "false"))` — Default Controller class to use for the specified role
- L30 _public member_ `bool bUpdateSubjectsImmediatelyInPIE = true;` — `UPROPERTY(config, EditAnywhere, Category = "LiveLink")` — If true, all LiveLink subjects with pending frame data will be updated immediately before the LiveLink components execute (only applies to PIE)

### `Plugins/Animation/LiveLink/Source/LiveLinkComponents/Public/LiveLinkControllerBase.h` (Public)


#### class `ULiveLinkControllerBase`  
`class ULiveLinkControllerBase : public UObject`  
_L20-105_
- reflection: `UCLASS(MinimalAPI, Abstract, ClassGroup = (LiveLink), editinlinenew)`
- inherits: `UObject`
- L26 _public prototype_ `virtual void PostLoad() override;`
- L30 _public function_ `virtual void OnEvaluateRegistered()` — Initialize the controller at the first tick of its owner component.
- L33 _public function_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectRepresentation& SubjectRepresentation)` — `UE_DEPRECATED(4.25, "This function is deprecated. Use Tick function that received evaluated data instead.")`
- L38 _public function_ `virtual void Tick(float DeltaTime, const FLiveLinkSubjectFrameData& SubjectData)` — Function called every frame with the data evaluated by the component.
- L44 _public function_ `virtual bool IsRoleSupported(const TSubclassOf<ULiveLinkRole>& RoleToSupport)` — Can it support a specific role. This is called on the default object before creating an instance.
- L49 _public function_ `virtual TSubclassOf<UActorComponent> GetDesiredComponentClass() const` — Returns the component class that this controller wants to control
- L54 _public prototype_ `virtual void SetAttachedComponent(UActorComponent* ActorComponent);` — Sets the component this controller is driving
- L59 _public prototype_ `virtual void SetSelectedSubject(FLiveLinkSubjectRepresentation LiveLinkSubject);` — Sets the live link subject from which this controller is receiving data
- L64 _public function_ `virtual void Cleanup()` — Cleanup controller state before getting removed
- L67 _public function_ `virtual void InitializeInEditor()`
- L71 _public function_ `virtual FLiveLinkSubjectRepresentation GetSelectedSubject()` — Get the selected LiveLink subject for this controller
- L76 _public prototype_ `UActorComponent* GetAttachedComponent() const;` — Returns the component controlled by this controller
- L81 _public prototype_ `void OnComponentToControlChanged();` — Callback to reset the AttachedComponent when the value of the ComponentPicker is changed
- L84 _protected prototype_ `AActor* GetOuterActor() const;`
- L89 _public prototype_ `static TSubclassOf<ULiveLinkControllerBase> GetControllerForRole(const TSubclassOf<ULiveLinkRole>& RoleToSupport);` — `UE_DEPRECATED(4.25, "This function is deprecated. Use GetControllersForRole instead and use first element to have the same result.")`
- L94 _public prototype_ `static TArray<TSubclassOf<ULiveLinkControllerBase>> GetControllersForRole(const TSubclassOf<ULiveLinkRole>& RoleToSupport);` — Returns the list of ULiveLinkControllerBase classes that support the given role
- L101 _protected member_ `FComponentReference ComponentPicker;` — `UPROPERTY(EditInstanceOnly, Category = "ComponentToControl", meta = (UseComponentPicker, AllowedClasses = "/Script/Engine.ActorComponent", DisallowedClasses = "/Script/LiveLinkComponents.LiveLinkComponentController"))` — A component reference (customized) that allows the user to specify a component that this controller should control
- L104 _protected member_ `FLiveLinkSubjectRepresentation SelectedSubject;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LIVELINKCOMPONENTS_API`
