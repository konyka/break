# Plugins / DisplayClusterLightCardExtender

- module root: `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender`
- headers: 7; symbols: 104
- symbol kinds: class=6, delegate=1, function=26, member=16, prototype=51, struct=2, typedef=2
- PrivateDependencyModuleNames: Sequencer, UnrealEd
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Private/DisplayClusterLightCardExtenderModule.h` (Private)


#### class `FDisplayClusterLightCardExtenderModule`  
`class FDisplayClusterLightCardExtenderModule : public IDisplayClusterLightCardExtenderModule`  
_L9-38_
- inherits: `IDisplayClusterLightCardExtenderModule`
- L14 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation start
- L15 _public prototype_ `virtual void ShutdownModule() override;`
- L20 _public function_ `virtual FOnSequencerTimeChanged& GetOnSequencerTimeChanged() override` — Broadcast when any sequencer has its time changed
- L24 _private prototype_ `void OnSequencerCreated(TSharedRef<ISequencer> InSequencer);` — When a sequencer is opened
- L27 _private prototype_ `void OnSequencerTimeChanged(TWeakPtr<ISequencer> InSequencer);` — Called when the global time is changed in sequencer
- L30 _private prototype_ `void OnSequencerClosed(TSharedRef<ISequencer> InSequencer);` — When a sequencer is closed
- L33 _private member_ `TArray<TWeakPtr<ISequencer>> OpenSequencers;`
- L34 _private member_ `FDelegateHandle SequencerCreatedHandle;`
- L36 _private member_ `FOnSequencerTimeChanged OnSequencerTimeChangedDelegate;`

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Public/IDisplayClusterLightCardActorExtender.h` (Public)


#### class `IDisplayClusterLightCardActorExtender`  
`class IDisplayClusterLightCardActorExtender : public IModularFeature`  
_L14-35_
- inherits: `IModularFeature`
- desc: Light card Extender API
- L17 _public member_ `static const FName ModularFeatureName;`
- L19 _public prototype_ `virtual ~IDisplayClusterLightCardActorExtender() = default;`
- L22 _public prototype_ `virtual FName GetExtenderName() const = 0;` — Returns the name of the Extender
- L25 _public prototype_ `virtual TSubclassOf<UActorComponent> GetAdditionalSubobjectClass() = 0;` — Returns the class of the additional subobject that will be created in the actor.
- L29 _public prototype_ `virtual FName GetCategory() const = 0;` — Returns the name of the category in which details of the component are displayed
- L32 _public prototype_ `virtual bool ShouldShowSubcategories() const = 0;` — If true, displays properties in their respective categories

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Public/IDisplayClusterLightCardExtenderModule.h` (Public)


#### class `IDisplayClusterLightCardExtenderModule`  
`class IDisplayClusterLightCardExtenderModule : public IModuleInterface`  
_L8-42_
- inherits: `IModuleInterface`
- L11 _public member_ `static constexpr const TCHAR* ModuleName = TEXT("Dis`
- L14 _public prototype_ `virtual ~IDisplayClusterLightCardExtenderModule() = default;`
- L22 _public function_ `static inline IDisplayClusterLightCardExtenderModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L32 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use
- L38 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequencerTimeChanged, TWeakPtr<class ISequencer>);`
- L40 _public prototype_ `virtual FOnSequencerTimeChanged& GetOnSequencerTimeChanged() = 0;` — Broadcast when any sequencer has its time changed, including if one is closed

#### Free symbols / members of external scopes

- L38 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnSequencerTimeChanged, TWeakPtr<class ISequencer>);`

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Public/StageActor/DisplayClusterPositionalParams.h` (Public)


#### struct `FDisplayClusterPositionalParams`  
`struct FDisplayClusterPositionalParams`  
_L15-60_
- reflection: `USTRUCT(BlueprintType)`
- desc: Positional location and rotation parameters for use with nDisplay stage actors. Note that the origin point is purposely not included as these parameters are meant to be shared between actors with different origins.
- L20 _public member_ `double DistanceFromCenter = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation)`
- L23 _public member_ `double Longitude = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation, meta = (UIMin = 0, ClampMin = 0, UIMax = 360, ClampMax = 360))`
- L26 _public member_ `double Latitude = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation, meta = (UIMin = -90, ClampMin = -90, UIMax = 90, ClampMax = 90))`
- L29 _public member_ `double Spin = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation, meta = (UIMin = -360, ClampMin = -360, UIMax = 360, ClampMax = 360))`
- L32 _public member_ `double Pitch = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation, meta = (UIMin = -360, ClampMin = -360, UIMax = 360, ClampMax = 360))`
- L35 _public member_ `double Yaw = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation, meta = (UIMin = -360, ClampMin = -360, UIMax = 360, ClampMax = 360))`
- L38 _public member_ `double RadialOffset = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation)`
- L41 _public member_ `FVector2D Scale = FVector2D(1.0f);` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Orientation)`
- L43 _public function_ `bool operator==(const FDisplayClusterPositionalParams& Other) const`
- L56 _public function_ `bool operator!=(const FDisplayClusterPositionalParams& Other) const`

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Public/StageActor/DisplayClusterStageActorTemplate.h` (Public)


#### class `UDisplayClusterStageActorTemplate`  
`class UDisplayClusterStageActorTemplate : public UObject`  
_L10-21_
- reflection: `UCLASS(Abstract, PerObjectConfig, config=EditorPerProjectUserSettings)`
- inherits: `UObject`
- L15 _public function_ `virtual AActor* GetTemplateActor() const`
- L20 _public member_ `bool bIsFavorite;` — `UPROPERTY(Config)` — If the user has marked this a favorite template.

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Public/StageActor/DisplayClusterWeakStageActorPtr.h` (Public)


#### struct `FDisplayClusterWeakStageActorPtr`  
`struct FDisplayClusterWeakStageActorPtr`  
_L13-110_
- desc: Wrapper around a WeakObjectPtr to manage actors implementing IDisplayClusterStageActor.
- L16 _private member_ `FWeakObjectPtr ObjectPtr;`
- L19 _public prototype_ `virtual ~FDisplayClusterWeakStageActorPtr() = default;`
- L20 _public prototype_ `FDisplayClusterWeakStageActorPtr() = default;`
- L21 _public prototype_ `FDisplayClusterWeakStageActorPtr(const AActor* InActorPtr);`
- L24 _public prototype_ `IDisplayClusterStageActor* Get() const;` — Dereference the weak pointer
- L26 _public prototype_ `AActor* AsActor() const;`
- L27 _public prototype_ `AActor* AsActorChecked() const;`
- L30 _protected function_ `FWeakObjectPtr& GetWeakObjectPtr()`
- L31 _protected function_ `const FWeakObjectPtr& GetWeakObjectPtrConst() const`
- L35 _public function_ `FORCEINLINE bool IsValid() const` — Is the weak pointer valid
- L41 _public function_ `FORCEINLINE void Reset()` — Reset the weak pointer
- L47 _public function_ `FORCEINLINE IDisplayClusterStageActor* operator*() const` — Dereference the weak pointer
- L53 _public function_ `FORCEINLINE IDisplayClusterStageActor* operator->() const` — Dereference the weak pointer

#### Free symbols / members of external scopes

- L58 _function_ `friend bool operator==(const FDisplayClusterWeakStageActorPtr& Lhs, const FDisplayClusterWeakStageActorPtr& Rhs)`
- L64 _function_ `template <typename LhsT, typename RhsT, typename = decltype((LhsT*)nullptr == (RhsT*)nullptr)> friend bool operator==(const FDisplayClusterWeakStageActorPtr& Lhs, const RhsT* Rhs)`
- L70 _function_ `template <typename LhsT, typename RhsT, typename = decltype((LhsT*)nullptr == (RhsT*)nullptr)> friend bool operator==(const LhsT* Lhs, const FDisplayClusterWeakStageActorPtr& Rhs)`
- L76 _function_ `template <typename LhsT> friend bool operator==(const FDisplayClusterWeakStageActorPtr& Lhs, TYPE_OF_NULLPTR)`
- L82 _function_ `template <typename RhsT> friend bool operator==(TYPE_OF_NULLPTR, const FDisplayClusterWeakStageActorPtr& Rhs)`
- L88 _function_ `template <typename LhsT, typename RhsT, typename = decltype((LhsT*)nullptr != (RhsT*)nullptr)> friend bool operator!=(const FDisplayClusterWeakStageActorPtr& Lhs, const RhsT* Rhs)`
- L94 _function_ `template <typename LhsT, typename RhsT, typename = decltype((LhsT*)nullptr != (RhsT*)nullptr)> friend bool operator!=(const LhsT* Lhs, const FDisplayClusterWeakStageActorPtr& Rhs)`
- L100 _function_ `template <typename LhsT> friend bool operator!=(const FDisplayClusterWeakStageActorPtr& Lhs, TYPE_OF_NULLPTR)`
- L106 _function_ `template <typename RhsT> friend bool operator!=(TYPE_OF_NULLPTR, const FDisplayClusterWeakStageActorPtr& Rhs)`

### `Plugins/Runtime/nDisplayModularFeatures/Source/DisplayClusterLightCardExtender/Public/StageActor/IDisplayClusterStageActor.h` (Public)


#### class `UDisplayClusterStageActor`  
`class UDisplayClusterStageActor : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))`
- inherits: `UInterface`

#### class `IDisplayClusterStageActor`  
`class IDisplayClusterStageActor`  
_L17-111_
- L23 _public typedef_ `typedef TPair<void*, FProperty*> FPropertyPair;` — A pair made up of a container pointer and a property within that container
- L26 _public typedef_ `typedef TArray<FPropertyPair, TInlineAllocator<16>> FPositionalPropertyArray;` — Array type used to return positional properties for a stage actor
- L30 _public member_ `static const FRotator PlaneMeshRotation;` — The rotation used to orient the plane mesh used for the light card so that its normal points radially inwards
- L32 _public prototype_ `virtual void SetLongitude(double InValue) = 0;`
- L33 _public prototype_ `virtual double GetLongitude() const = 0;`
- L35 _public prototype_ `virtual void SetLatitude(double InValue) = 0;`
- L36 _public prototype_ `virtual double GetLatitude() const = 0;`
- L38 _public prototype_ `virtual void SetDistanceFromCenter(double InValue) = 0;`
- L39 _public prototype_ `virtual double GetDistanceFromCenter() const = 0;`
- L41 _public prototype_ `virtual void SetSpin(double InValue) = 0;`
- L42 _public prototype_ `virtual double GetSpin() const = 0;`
- L44 _public prototype_ `virtual void SetPitch(double InValue) = 0;`
- L45 _public prototype_ `virtual double GetPitch() const = 0;`
- L47 _public prototype_ `virtual void SetYaw(double InValue) = 0;`
- L48 _public prototype_ `virtual double GetYaw() const = 0;`
- L50 _public prototype_ `virtual void SetRadialOffset(double InValue) = 0;`
- L51 _public prototype_ `virtual double GetRadialOffset() const = 0;`
- L53 _public prototype_ `virtual void SetOrigin(const FTransform& InOrigin) = 0;`
- L54 _public prototype_ `virtual FTransform GetOrigin() const = 0;`
- L56 _public prototype_ `virtual void SetScale(const FVector2D& InScale) = 0;`
- L57 _public prototype_ `virtual FVector2D GetScale() const = 0;`
- L59 _public function_ `virtual void SetAlwaysFlushToWall(bool bInAlwaysFlushToWall)`
- L60 _public function_ `virtual bool IsAlwaysFlushToWall() const`
- L64 _public prototype_ `virtual const TSet<FName>& GetPositionalPropertyNames() const;` — Return property names defined for this stage actor for use in property notifies
- L67 _public prototype_ `virtual FName GetPositionalPropertiesMemberName() const;` — Return the property name for an owning struct containing the positional params properties, may be NAME_None if a struct isn't used
- L70 _public prototype_ `virtual void GetPositionalProperties(FPositionalPropertyArray& OutPropertyPairs) const = 0;` — Get an array of positional properties defined for this stage actor for use in property notifies.
- L73 _public prototype_ `virtual FBox GetBoxBounds(bool bLocalSpace = false) const;` — Return the bounding box for the stage actor. The default implementation returns the components bounding box
- L76 _public function_ `virtual bool IsUVActor() const` — Whether this actor supports movement in UV space
- L77 _public function_ `virtual void SetUVCoordinates(const FVector2D& InUVCoordinates)`
- L78 _public function_ `virtual FVector2D GetUVCoordinates() const`
- L81 _public prototype_ `virtual bool IsProxy() const;` — If this stage actor is a copy of a level instance actor
- L84 _public prototype_ `virtual void UpdateStageActorTransform();` — Update positional properties of the stage actor. The default implementation updates the actor's transform
- L87 _public prototype_ `virtual FTransform GetStageActorTransform(bool bRemoveOrigin = false) const;` — Return the adjusted transform of the stage actor. The default implementation uses the actor's location as a base
- L90 _public prototype_ `virtual void SetPositionalParams(const FDisplayClusterPositionalParams& InParams);` — Sets positional parameters
- L93 _public prototype_ `virtual FDisplayClusterPositionalParams GetPositionalParams() const;` — Retrieves positional parameters
- L96 _public prototype_ `virtual void UpdatePositionalParamsFromTransform();` — Update positional params from current actor transform
- L99 _public prototype_ `static void ClampLatitudeAndLongitude(double& InOutLatitude, double& InOutLongitude);` — Clamp the given latitude and longitude
- L102 _public prototype_ `static FTransform PositionalParamsToActorTransform(const FDisplayClusterPositionalParams& InParams, const FTransform& InOrigin);` — Convert latitude/longitude/yaw/pitch/roll to a transform that could be applied to an actor
- L105 _public prototype_ `static FDisplayClusterPositionalParams TransformToPositionalParams(const FTransform& InTransform, const FTransform& InOrigin, double InRadialOffset);` — Convert an actor transform to positional params
- L109 _public prototype_ `void UpdateEditorGizmos();` — Update global selection gizmos
