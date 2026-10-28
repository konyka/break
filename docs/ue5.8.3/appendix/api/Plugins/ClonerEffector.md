# Plugins / ClonerEffector

- module root: `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector`
- headers: 64; symbols: 1870
- symbol kinds: class=58, delegate=15, enum=23, enumerator=122, function=348, member=568, namespace=7, prototype=719, struct=8, typedef=1, variable=1
- PrivateDependencyModuleNames: DeveloperSettings, GeometryCore, GeometryFramework, GeometryScriptingCore, NiagaraCore, Slate, SlateCore, UnrealEd
- PublicDependencyModuleNames: ClonerEffectorMeshBuilder, Core, CoreUObject, Engine, Niagara

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Private/Cloner/Logs/CEClonerLogs.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCECloner, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCECloner, Log, All);`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Private/Effector/Logs/CEEffectorLogs.h` (Private)


#### Free symbols / members of external scopes

- L7 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogCEEffector, Log, All);`
- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCEEffector, Log, All);`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Private/Settings/CEClonerEffectorSettings.h` (Private)


#### class `UCEClonerEffectorSettings`  
`class UCEClonerEffectorSettings : public UDeveloperSettings`  
_L15-104_
- reflection: `UCLASS(Config=Engine, meta=(DisplayName="Cloner & Effector"))`
- inherits: `UDeveloperSettings`
- desc: Settings for motion design Cloner and Effector plugin
- L20 _public member_ `static constexpr int32 NoFlicker = 1;`
- L21 _public member_ `static constexpr TCHAR DefaultStaticMeshPath[] = TEXT("/Sc`
- L22 _public member_ `static constexpr TCHAR DefaultMaterialPath[] = TEXT("/Sc`
- L24 _public function_ `FLinearColor GetVisualizerInnerColor() const`
- L29 _public function_ `FLinearColor GetVisualizerOuterColor() const`
- L34 _public function_ `bool GetSpawnDefaultActorAttached() const`
- L39 _public prototype_ `UStaticMesh* GetDefaultStaticMesh() const;`
- L41 _public prototype_ `UMaterialInterface* GetDefaultMaterial() const;`
- L44 _public function_ `bool GetReduceMotionGhosting() const`
- L49 _public prototype_ `void OpenEditorSettingsWindow() const;`
- L53 _protected prototype_ `UCEClonerEffectorSettings();`
- L56 _protected prototype_ `virtual void PostInitProperties() override;`
- L58 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L64 _protected member_ `FLinearColor VisualizerInnerColor = FLinearColor(255, 0, 0, 0.1f);` — `UPROPERTY(Config, EditAnywhere, Category="Effector")` — Inner visualizer color for effectors
- L68 _protected member_ `FLinearColor VisualizerOuterColor = FLinearColor(0, 0, 255, 0.1f);` — `UPROPERTY(Config, EditAnywhere, Category="Effector")` — Outer visualizer color for effectors
- L72 _protected member_ `bool bSpawnDefaultActorAttached = true;` — `UPROPERTY(Config, EditAnywhere, Category="Cloner")` — Spawns a default actor attached to the cloner on spawn
- L76 _protected member_ `TSoftObjectPtr<UStaticMesh> DefaultStaticMesh;` — `UPROPERTY(Config, EditAnywhere, Category="Cloner")` — Default static mesh used when spawning default actor attached
- L80 _protected member_ `TSoftObjectPtr<UMaterialInterface> DefaultMaterial;` — `UPROPERTY(Config, EditAnywhere, Category="Cloner")` — Default material used when spawning default actor attached
- L85 _protected member_ `bool bReduceMotionGhosting = true;` — `UPROPERTY(Config, EditAnywhere, Category="Cloner")` — Reduces the r.TSR.ShadingRejection.Flickering.Period from 3 (default) to 1 if enabled to avoid ghosting artifacts when moving
- L90 _private prototype_ `void EnableNoFlicker();`
- L91 _private prototype_ `void DisableNoFlicker();`
- L92 _private prototype_ `bool IsNoFlickerEnabled() const;`
- L94 _private prototype_ `void OnReduceMotionGhostingChanged();`
- L95 _private prototype_ `void OnTSRShadingRejectionFlickeringPeriodChanged(IConsoleVariable* InCVar);`
- L98 _private member_ `IConsoleVariable* CVarTSRShadingRejectionFlickeringPeriod = nullptr;` — Allows to reduce ghosting artifacts when moving cloner instances
- L102 _private member_ `TOptional<int32> PreviousCVarValue;` — `UPROPERTY()` — Previous value to restore it when disabled

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Private/Utilities/CEClonerLayoutLatentAction.h` (Private)


#### class `FCEClonerLayoutLatentAction`  
`class FCEClonerLayoutLatentAction : public FPendingLatentAction`  
_L14-41_
- inherits: `FPendingLatentAction`
- desc: Latent action to set cloner layout and wait until layout is active and ready to use
- L17 _public prototype_ `FCEClonerLayoutLatentAction(const FLatentActionInfo& InLatentInfo, UCEClonerComponent* InCloner, TSubclassOf<UCEClonerLayoutBase> InLayoutClass, bool& bOutSuccess, UCEClonerLayoutBase*& OutLayout);`
- L19 _public prototype_ `virtual ~FCEClonerLayoutLatentAction();`
- L23 _protected prototype_ `virtual void UpdateOperation(FLatentResponse& OutResponse) override;`
- L25 _protected prototype_ `virtual FString GetDescription() const override;`
- L29 _protected prototype_ `void OnClonerLayoutLoaded(UCEClonerComponent* InClonerComponent, UCEClonerLayoutBase* InClonerLayoutBase) const;`
- L31 _protected member_ `FName ExecutionFunction;`
- L32 _protected member_ `int32 OutputLink;`
- L33 _protected member_ `FWeakObjectPtr CallbackTarget;`
- L35 _protected member_ `bool bLayoutSet;`
- L36 _protected member_ `TWeakObjectPtr<UCEClonerComponent> ClonerWeak;`
- L37 _protected member_ `TSubclassOf<UCEClonerLayoutBase> LayoutClass;`
- L39 _protected member_ `bool& bSuccess;`
- L40 _protected member_ `UCEClonerLayoutBase*& Layout;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/CEClonerEffectorShared.h` (Public)


#### enum `ECEClonerAxis`  
`enum class ECEClonerAxis : uint8`  
_L24-30_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerate the axis available to use
- L26 _public enumerator_ `X`
- L27 _public enumerator_ `Y`
- L28 _public enumerator_ `Z`
- L29 _public enumerator_ `Custom`

#### enum `ECEClonerPlane`  
`enum class ECEClonerPlane : uint8`  
_L34-40_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerate the planes available to use
- L36 _public enumerator_ `XY`
- L37 _public enumerator_ `YZ`
- L38 _public enumerator_ `XZ`
- L39 _public enumerator_ `Custom`

#### enum `ECEClonerMeshRenderMode`  
`enum class ECEClonerMeshRenderMode : uint8`  
_L44-52_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerate the mesh render modes available to render a cloner instance
- L47 _public enumerator_ `Iterate` — Iterate through each attachment mesh available
- L49 _public enumerator_ `Random` — Pick randomly through each attachment mesh available, update cloner seed for variations
- L51 _public enumerator_ `Blend` — Blend based on the total cloner instances and attachment mesh available

#### enum `ECEClonerGridConstraint`  
`enum class ECEClonerGridConstraint : uint8`  
_L56-62_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerate the grid constraints available when cloner layout selected is grid
- L58 _public enumerator_ `None`
- L59 _public enumerator_ `Sphere`
- L60 _public enumerator_ `Cylinder`
- L61 _public enumerator_ `Texture`

#### enum `ECEClonerEasing`  
`enum class ECEClonerEasing : uint8`  
_L68-113_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates all easing functions that are available to apply on weights See https://easings.net/ for curves visualizations and web open domain implementations Used as one enum to send the index to niagara as uint8 and apply easing directly in niagara
- L70 _public enumerator_ `Linear`
- L72 _public enumerator_ `InSine`
- L73 _public enumerator_ `OutSine`
- L74 _public enumerator_ `InOutSine`
- L76 _public enumerator_ `InQuad`
- L77 _public enumerator_ `OutQuad`
- L78 _public enumerator_ `InOutQuad`
- L80 _public enumerator_ `InCubic`
- L81 _public enumerator_ `OutCubic`
- L82 _public enumerator_ `InOutCubic`
- L84 _public enumerator_ `InQuart`
- L85 _public enumerator_ `OutQuart`
- L86 _public enumerator_ `InOutQuart`
- L88 _public enumerator_ `InQuint`
- L89 _public enumerator_ `OutQuint`
- L90 _public enumerator_ `InOutQuint`
- L92 _public enumerator_ `InExpo`
- L93 _public enumerator_ `OutExpo`
- L94 _public enumerator_ `InOutExpo`
- L96 _public enumerator_ `InCirc`
- L97 _public enumerator_ `OutCirc`
- L98 _public enumerator_ `InOutCirc`
- L100 _public enumerator_ `InBack`
- L101 _public enumerator_ `OutBack`
- L102 _public enumerator_ `InOutBack`
- L104 _public enumerator_ `InElastic`
- L105 _public enumerator_ `OutElastic`
- L106 _public enumerator_ `InOutElastic`
- L108 _public enumerator_ `InBounce`
- L109 _public enumerator_ `OutBounce`
- L110 _public enumerator_ `InOutBounce`
- L112 _public enumerator_ `Random`

#### enum `ECEClonerMeshAsset`  
`enum class ECEClonerMeshAsset : uint8`  
_L117-121_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerate the mesh asset to look for when mesh layout is selected
- L119 _public enumerator_ `StaticMesh`
- L120 _public enumerator_ `SkeletalMesh`

#### enum `ECEClonerMeshSampleData`  
`enum class ECEClonerMeshSampleData : uint8`  
_L125-132_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerate the mesh sample dataset to pick from when mesh layout is selected
- L127 _public enumerator_ `Vertices`
- L128 _public enumerator_ `Triangles`
- L129 _public enumerator_ `Sockets`
- L130 _public enumerator_ `Bones`
- L131 _public enumerator_ `Sections`

#### enum `ECEClonerEffectorType`  
`enum class ECEClonerEffectorType : uint8`  
_L136-150_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates the effector shapes available
- L139 _public enumerator_ `Sphere` — Clones inside the sphere radius will be affected by the effector
- L141 _public enumerator_ `Plane` — Clones between two planes will be affected by the effector
- L143 _public enumerator_ `Box` — Clones inside the box extent will be affected by the effector
- L145 _public enumerator_ `Unbound` — All clones will be affected by the effector with the same max weight
- L147 _public enumerator_ `Radial` — All clones within the angle range will be affected
- L149 _public enumerator_ `Torus` — All clones inside the torus radius will be affected by the effector

#### enum `ECEClonerEffectorMode`  
`enum class ECEClonerEffectorMode : uint8`  
_L154-170_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates the effector mode available
- L157 _public enumerator_ `Default` — Control clones offset, rotation, scale manually
- L159 _public enumerator_ `Target` — Rotates clones towards a target actor
- L161 _public enumerator_ `Procedural` — Procedural pattern applied across the field zone
- L163 _public enumerator_ `Push` — Pushes clones apart based on a strength and direction
- L165 _public enumerator_ `Step` — Accumulate transform on clones based on their index
- L167 _public enumerator_ `Cull` — Culls clones based on a zone
- L169 _public enumerator_ `Cancel` — Cancels/reverses all effects

#### enum `ECEClonerEffectorProceduralPattern`  
`enum class ECEClonerEffectorProceduralPattern : uint8`  
_L174-182_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates the effector procedural pattern available
- L177 _public enumerator_ `CurlNoise` — Jacobian Simplex Noise
- L179 _public enumerator_ `DirectionalWave` — Wave moving towards specific direction
- L181 _public enumerator_ `CircularWave` — Ripple wave movement

#### enum `ECEClonerEffectorPushDirection`  
`enum class ECEClonerEffectorPushDirection : uint8`  
_L186-198_
- reflection: `UENUM(BlueprintType)`
- desc: Enumerates the effector push direction available
- L189 _public enumerator_ `Forward` — Push based on the clone forward vector
- L191 _public enumerator_ `Right` — Push based on the clone right vector
- L193 _public enumerator_ `Up` — Push based on the cloner up vector
- L195 _public enumerator_ `Effector` — Push based on the clone position relative to the effector
- L197 _public enumerator_ `Random` — Push based on a random unit vector based on the cloner seed

#### enum `ECEClonerTextureSampleChannel`  
`enum class ECEClonerTextureSampleChannel : uint8`  
_L202-211_
- reflection: `UENUM()`
- desc: Enumerate all texture channels to sample for constraint
- L204 _public enumerator_ `RGBLuminance`
- L205 _public enumerator_ `RGBAverage`
- L206 _public enumerator_ `RGBMax`
- L207 _public enumerator_ `R`
- L208 _public enumerator_ `G`
- L209 _public enumerator_ `B`
- L210 _public enumerator_ `A`

#### enum `ECEClonerCompareMode`  
`enum class ECEClonerCompareMode : uint8`  
_L215-223_
- reflection: `UENUM()`
- desc: Enumerate all operation compare mode for constraint
- L217 _public enumerator_ `Greater`
- L218 _public enumerator_ `GreaterEqual`
- L219 _public enumerator_ `Equal`
- L220 _public enumerator_ `NotEqual`
- L221 _public enumerator_ `Less`
- L222 _public enumerator_ `LessEqual`

#### enum `ECEClonerSpawnLoopMode`  
`enum class ECEClonerSpawnLoopMode : uint8`  
_L227-235_
- reflection: `UENUM()`
- desc: Enumerates all modes to handle cloner spawn mode
- L230 _public enumerator_ `Once` — Cloner spawns once and then enters idle mode
- L232 _public enumerator_ `Multiple` — Cloner spawns multiple times and then enters idle mode
- L234 _public enumerator_ `Infinite` — Cloner spawns infinitely and never enters idle mode

#### enum `ECEClonerSpawnBehaviorMode`  
`enum class ECEClonerSpawnBehaviorMode : uint8`  
_L239-245_
- reflection: `UENUM()`
- desc: Enumerates all modes for how clones are spawned
- L242 _public enumerator_ `Instant` — Spawns instantly the number of clones needed for the layout at a specific interval
- L244 _public enumerator_ `Rate` — Spawns clones at a specific rate per second and fills the layout

#### enum `ECEClonerCollisionRadiusMode`  
`enum class ECEClonerCollisionRadiusMode : uint8`  
_L249-259_
- reflection: `UENUM()`
- desc: Enumerates all modes for how clones radius are calculed
- L252 _public enumerator_ `Manual` — Input collision radius manually
- L254 _public enumerator_ `MinExtent` — Collision radius will be calculated automatically based on the min extent value, mesh scale included
- L256 _public enumerator_ `MaxExtent` — Collision radius will be calculated automatically based on the max extent value, mesh scale included
- L258 _public enumerator_ `ExtentLength` — Collision radius will be calculated automatically based on the extent length, mesh scale included

#### enum `ECEClonerMeshConversion`  
`enum class ECEClonerMeshConversion : uint8`  
_L262-269_
- desc: Enumerates all conversion possible for cloner simulation
- L264 _public enumerator_ `StaticMesh`
- L265 _public enumerator_ `StaticMeshes`
- L266 _public enumerator_ `DynamicMesh`
- L267 _public enumerator_ `DynamicMeshes`
- L268 _public enumerator_ `InstancedStaticMesh`

#### enum `ECEClonerSystemStatus`  
`enum class ECEClonerSystemStatus : uint8`  
_L272-280_
- desc: Enumerates all states for extension/layout
- L275 _public enumerator_ `UpToDate = 0` — Nothing to do
- L277 _public enumerator_ `ParametersDirty = 1 << 0` — Parameters needs an update
- L279 _public enumerator_ `SimulationDirty = 1 << 1` — Simulation needs an update

#### enum `ECEClonerActorVisibility`  
`enum class ECEClonerActorVisibility : uint8`  
_L283-289_
- desc: Enumerates all visibility options for an actor
- L285 _public enumerator_ `None = 0`
- L286 _public enumerator_ `Game = 1 << 0`
- L287 _public enumerator_ `Editor = 1 << 1`
- L288 _public enumerator_ `All = Game | Editor`

#### struct `FCEClonerEffectorChannelData`  
`struct FCEClonerEffectorChannelData`  
_L292-396_
- reflection: `USTRUCT()`
- L299 _public member_ `static constexpr const TCHAR* MagnitudeName = TEXT("Mag` — General
- L300 _public member_ `static constexpr const TCHAR* LocationName = TEXT("Loc`
- L301 _public member_ `static constexpr const TCHAR* RotationName = TEXT("Rot`
- L302 _public member_ `static constexpr const TCHAR* ScaleName = TEXT("Sca`
- L303 _public member_ `static constexpr const TCHAR* ColorName = TEXT("Col`
- L306 _public member_ `static constexpr const TCHAR* TypeName = TEXT("Typ` — Type/Shape
- L307 _public member_ `static constexpr const TCHAR* EasingName = TEXT("Eas`
- L308 _public member_ `static constexpr const TCHAR* InnerExtentName = TEXT("Inn`
- L309 _public member_ `static constexpr const TCHAR* OuterExtentName = TEXT("Out`
- L312 _public member_ `static constexpr const TCHAR* ModeName = TEXT("Mod` — Mode
- L313 _public member_ `static constexpr const TCHAR* LocationDeltaName = TEXT("Loc`
- L314 _public member_ `static constexpr const TCHAR* RotationDeltaName = TEXT("Rot`
- L315 _public member_ `static constexpr const TCHAR* ScaleDeltaName = TEXT("Sca`
- L316 _public member_ `static constexpr const TCHAR* FrequencyName = TEXT("Fre`
- L317 _public member_ `static constexpr const TCHAR* PanName = TEXT("Pan`
- L318 _public member_ `static constexpr const TCHAR* PatternName = TEXT("Pat`
- L321 _public member_ `static constexpr const TCHAR* DelayInDurationName = TEXT("Del` — Delay
- L322 _public member_ `static constexpr const TCHAR* DelayOutDurationName = TEXT("Del`
- L323 _public member_ `static constexpr const TCHAR* DelaySpringFrequencyName = TEXT("Del`
- L324 _public member_ `static constexpr const TCHAR* DelaySpringFalloffName = TEXT("Del`
- L327 _public member_ `static constexpr const TCHAR* OrientationForceRateName = TEXT("Ori` — Forces
- L328 _public member_ `static constexpr const TCHAR* OrientationForceMinName = TEXT("Ori`
- L329 _public member_ `static constexpr const TCHAR* OrientationForceMaxName = TEXT("Ori`
- L330 _public member_ `static constexpr const TCHAR* VortexForceAmountName = TEXT("Vor`
- L331 _public member_ `static constexpr const TCHAR* VortexForceAxisName = TEXT("Vor`
- L332 _public member_ `static constexpr const TCHAR* CurlNoiseForceStrengthName = TEXT("Cur`
- L333 _public member_ `static constexpr const TCHAR* CurlNoiseForceFrequencyName = TEXT("Cur`
- L334 _public member_ `static constexpr const TCHAR* AttractionForceStrengthName = TEXT("Att`
- L335 _public member_ `static constexpr const TCHAR* AttractionForceFalloffName = TEXT("Att`
- L336 _public member_ `static constexpr const TCHAR* GravityForceAccelerationName = TEXT("Gra`
- L337 _public member_ `static constexpr const TCHAR* DragForceLinearName = TEXT("Dra`
- L338 _public member_ `static constexpr const TCHAR* DragForceRotationalName = TEXT("Dra`
- L339 _public member_ `static constexpr const TCHAR* VectorNoiseForceAmountName = TEXT("Vec`
- L341 _public function_ `int32 GetIdentifier() const`
- L347 _public member_ `float Magnitude = 0.f;` — General
- L348 _public member_ `FVector Location = FVector::ZeroVector;`
- L349 _public member_ `FQuat Rotation = FQuat::Identity;`
- L350 _public member_ `FVector Scale = FVector::OneVector;`
- L351 _public member_ `FLinearColor Color = FLinearColor::Transparent;`
- L354 _public member_ `ECEClonerEffectorType Type = ECEClonerEffectorType::Sphere;` — Type
- L355 _public member_ `ECEClonerEasing Easing = ECEClonerEasing::Linear;`
- L356 _public member_ `FVector InnerExtent = FVector::ZeroVector;`
- L357 _public member_ `FVector OuterExtent = FVector::ZeroVector;`
- L360 _public member_ `ECEClonerEffectorMode Mode = ECEClonerEffectorMode::Default;` — Mode
- L361 _public member_ `FVector LocationDelta = FVector::ZeroVector;`
- L362 _public member_ `FVector RotationDelta = FVector::ZeroVector;`
- L363 _public member_ `FVector ScaleDelta = FVector::OneVector;`
- L364 _public member_ `float Frequency = 1.f;`
- L365 _public member_ `FVector Pan = FVector::ZeroVector;`
- L366 _public member_ `ECEClonerEffectorProceduralPattern Pattern = ECEClonerEffectorProceduralPattern::CurlNoise;`
- L369 _public member_ `float DelayInDuration = 0.f;` — Delay
- L370 _public member_ `float DelayOutDuration = 0.f;`
- L371 _public member_ `float DelaySpringFrequency = 0.f;`
- L372 _public member_ `float DelaySpringFalloff = 0.f;`
- L375 _public member_ `float OrientationForceRate = 0.f;` — Forces
- L376 _public member_ `FVector OrientationForceMin = FVector::ZeroVector;`
- L377 _public member_ `FVector OrientationForceMax = FVector::ZeroVector;`
- L378 _public member_ `float VortexForceAmount = 0.f;`
- L379 _public member_ `FVector VortexForceAxis = FVector::ZeroVector;`
- L380 _public member_ `float CurlNoiseForceStrength = 0.f;`
- L381 _public member_ `float CurlNoiseForceFrequency = 0.f;`
- L382 _public member_ `float AttractionForceStrength = 0.f;`
- L383 _public member_ `float AttractionForceFalloff = 0.f;`
- L384 _public member_ `FVector GravityForceAcceleration = FVector::ZeroVector;`
- L385 _public member_ `float DragForceLinear = 0.f;`
- L386 _public member_ `float DragForceRotational = 0.f;`
- L387 _public member_ `float VectorNoiseForceAmount = 0.f;`
- L392 _protected member_ `int32 Identifier = INDEX_NONE;` — `UPROPERTY(VisibleInstanceOnly, Category="Effector", meta=(NoResetToDefault))` — Cached effector identifier to detect a change and update cloners DI
- L394 _protected prototype_ `void Write(UNiagaraDataChannelWriter* InWriter) const;`
- L395 _protected prototype_ `void Read(const UNiagaraDataChannelReader* InReader);`

#### struct `FCEClonerGridConstraintSphere`  
`struct FCEClonerGridConstraintSphere`  
_L399-408_
- reflection: `USTRUCT(BlueprintType)`
- L404 _public member_ `float Radius = 400.f;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`
- L407 _public member_ `FVector Center = FVector(0);` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`

#### struct `FCEClonerGridConstraintCylinder`  
`struct FCEClonerGridConstraintCylinder`  
_L411-423_
- reflection: `USTRUCT(BlueprintType)`
- L416 _public member_ `float Radius = 400.f;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`
- L419 _public member_ `float Height = 800.f;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`
- L422 _public member_ `FVector Center = FVector(0);` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`

#### struct `FCEClonerGridConstraintTexture`  
`struct FCEClonerGridConstraintTexture`  
_L426-444_
- reflection: `USTRUCT(BlueprintType)`
- L431 _public member_ `TWeakObjectPtr<UTexture> Texture;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`
- L434 _public member_ `ECEClonerTextureSampleChannel Channel = ECEClonerTextureSampleChannel::RGBLuminance;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`
- L437 _public member_ `ECEClonerPlane Plane = ECEClonerPlane::XY;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`
- L440 _public member_ `ECEClonerCompareMode CompareMode = ECEClonerCompareMode::Greater;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`
- L443 _public member_ `float Threshold = 0.f;` — `UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Cloner")`

#### struct `FCEExtensionSection`  
`struct FCEExtensionSection`  
_L447-462_
- L449 _public function_ `FCEExtensionSection()`
- L452 _public function_ `explicit FCEExtensionSection(FName InSectionName, int32 InSectionOrder) : SectionName(InSectionName) , SectionOrder(InSectionOrder)`
- L458 _public member_ `FName SectionName = NAME_None;` — Used for editor details UI
- L461 _public member_ `int32 SectionOrder = 0;` — Used to reorder categories in editor UI

#### Free symbols / members of external scopes

- L465 _namespace_ `namespace UE`
- L465 _namespace_ `namespace ClonerEffector` (scope `UE`)
- L468 _variable_ `static const FLazyName MeshArrayName = TEXT("Mes` (scope `UE::ClonerEffector`) — Name for the mesh array data interface to use
- L471 _prototype_ `UNiagaraDataInterfaceArrayMesh* FindMeshArrayDataInterface(UCEClonerComponent* InClonerComponent);` (scope `UE::ClonerEffector`) — Finds the 'MeshArray' data interface in the given cloner
- L474 _namespace_ `namespace EditorSection` (scope `UE::ClonerEffector`)
- L477 _prototype_ `FCEExtensionSection GetExtensionSectionFromClass(UClass* InClass);` (scope `UE::ClonerEffector::EditorSection`) — Retrieves section metadata from class
- L481 _namespace_ `namespace Conversion` (scope `UE::ClonerEffector`)
- L484 _prototype_ `AStaticMeshActor* ConvertClonerToStaticMesh(UCEClonerComponent* InCloner);` (scope `UE::ClonerEffector::Conversion`) — Convert a cloner to a single merged static mesh actor
- L487 _prototype_ `ADynamicMeshActor* ConvertClonerToDynamicMesh(UCEClonerComponent* InCloner);` (scope `UE::ClonerEffector::Conversion`) — Convert a cloner to a single merged dynamic mesh actor
- L490 _prototype_ `TArray<AStaticMeshActor*> ConvertClonerToStaticMeshes(UCEClonerComponent* InCloner);` (scope `UE::ClonerEffector::Conversion`) — Convert a cloner to multiple static mesh actors
- L493 _prototype_ `TArray<ADynamicMeshActor*> ConvertClonerToDynamicMeshes(UCEClonerComponent* InCloner);` (scope `UE::ClonerEffector::Conversion`) — Convert a cloner to multiple dynamic mesh actors
- L496 _prototype_ `TArray<AActor*> ConvertClonerToInstancedStaticMeshes(UCEClonerComponent* InCloner);` (scope `UE::ClonerEffector::Conversion`) — Convert a cloner to multiple instanced static mesh actors
- L499 _prototype_ `UActorComponent* CreateRootComponent(AActor* InActor, TSubclassOf<USceneComponent> InComponentClass, const FTransform& InWorldTransform);` (scope `UE::ClonerEffector::Conversion`) — Creates the root component for an actor
- L503 _prototype_ `bool PickAssetPath(const FString& InDefaultPath, FString& OutPickedPath);` (scope `UE::ClonerEffector::Conversion`) — Pick assets location
- L506 _prototype_ `UObject* CreateAssetPackage(TSubclassOf<UObject> InAssetClass, const FString& InAssetPath);` (scope `UE::ClonerEffector::Conversion`) — Create a specific asset in a package
- L510 _function_ `InClass* CreateAssetPackage(const FString& InAssetPath)` (scope `UE::ClonerEffector::Conversion`)

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/CEPropertyChangeDispatcher.h` (Public)


#### class `TCEPropertyChangeDispatcher`  
`template<typename InClassType> class TCEPropertyChangeDispatcher`  
_L12-33_
- L15 _public typedef_ `using FMemberFunctionType = typename TMemFunPtrType< false, InClassType, void()>::Type;`
- L17 _public function_ `TCEPropertyChangeDispatcher(std::initializer_list<TPairInitializer<const FName&, const FMemberFunctionType&>> InCallbacks) : PropertyChangedFunctions(InCallbacks)`
- L21 _public function_ `void OnPropertyChanged(InClassType* InObject, const FPropertyChangedEvent& InPropertyChangedEvent) const`
- L32 _private member_ `TMap<FName, FMemberFunctionType> PropertyChangedFunctions;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Attachments/CEClonerAttachmentItem.h` (Public)


#### struct `FCEClonerAttachmentItem`  
`struct FCEClonerAttachmentItem`  
_L15-93_
- reflection: `USTRUCT()`
- L21 _public member_ `TSet<TWeakObjectPtr<AActor>> ChildrenActors;` — `UPROPERTY()` — Children attached to this actor, order is not important here as they are combined into one
- L25 _public member_ `TWeakObjectPtr<AActor> ItemActor;` — `UPROPERTY()` — Current cloner attached actor represented by this item
- L29 _public member_ `TWeakObjectPtr<AActor> ParentActor;` — `UPROPERTY()` — Parent of this item actor or null if below cloner
- L34 _public member_ `TObjectPtr<UDynamicMesh> BakedMesh;` — `UPROPERTY(Transient)` — Actual baked mesh for the current actor item, dynamic because it's easier for merging them together and avoid conversions again
- L38 _public member_ `TArray<TWeakObjectPtr<UMaterialInterface>> BakedMaterials;` — `UPROPERTY()` — Actual baked materials for the current actor item
- L42 _public member_ `ECEClonerAttachmentStatus MeshStatus = ECEClonerAttachmentStatus::Outdated;` — `UPROPERTY()` — Status of the baked mesh, does it needs to be updated
- L46 _public member_ `FTransform ActorTransform = FTransform::Identity;` — `UPROPERTY()` — Last actor item transform, used to trigger an update if changed
- L50 _public member_ `bool bRootItem = false;` — `UPROPERTY()` — Item is root cloner actor
- L54 _public member_ `bool bSetupDone = false;` — `UPROPERTY(Transient)` — Item setup is done (visibility, delegates) once attached/loaded
- L58 _public member_ `ECEClonerAttachmentStatus Status = ECEClonerAttachmentStatus::Outdated;` — `UPROPERTY(Transient)` — Status of this attachment item
- L63 _public member_ `FVector Origin = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Cached pivot to detect changes in geometry
- L67 _public member_ `FVector Extent = FVector::ZeroVector;` — `UPROPERTY(Transient)` — Cached extent to detect changes in geometry
- L75 _public function_ `bool operator==(const FCEClonerAttachmentItem& InOther) const`
- L82 _public prototype_ `bool CheckBoundsChanged(bool bInUpdate);` — Check this item bounds without recursing
- L85 _public prototype_ `FBox GetBakedMeshBounds() const;` — Calculate baked mesh bounds
- L88 _public prototype_ `FBox GetAttachmentBounds() const;` — Get local attachment bounds
- L92 _public prototype_ `bool CheckMaterialsChanged(bool bInUpdate, TArray<TWeakObjectPtr<UMaterialInterface>>* OutInvalidMaterials = nullptr);` — Check this item materials to ensure they are supported

#### Free symbols / members of external scopes

- L70 _function_ `friend uint32 GetTypeHash(const FCEClonerAttachmentItem& InItem)`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Attachments/CEClonerAttachmentRootItem.h` (Public)


#### struct `FCEClonerAttachmentRootItem`  
`struct FCEClonerAttachmentRootItem`  
_L16-59_
- reflection: `USTRUCT()`
- L20 _public function_ `FCEClonerAttachmentRootItem()`
- L23 _public prototype_ `FCEClonerAttachmentRootItem(AActor* InActor);`
- L30 _public function_ `bool operator==(const FCEClonerAttachmentRootItem& InOther) const`
- L35 _public function_ `void Reset()`
- L45 _public member_ `TWeakObjectPtr<AActor> RootActor;` — `UPROPERTY()` — Actors directly attached to the cloner actor, order is important here
- L52 _public member_ `TObjectPtr<UStaticMesh> MergedBakedMesh;` — `UPROPERTY()` — Merged static meshes corresponding to the root actors for niagara, result of merging dynamic meshes together
- L57 _public member_ `TOptional<FVector> MeshSize;` — `UPROPERTY()` — Mesh size of the baked mesh / root actor tree, used to compare and detect a change

#### Free symbols / members of external scopes

- L25 _function_ `friend uint32 GetTypeHash(const FCEClonerAttachmentRootItem& InItem)`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Attachments/CEClonerAttachmentTree.h` (Public)


#### struct `FCEClonerAttachmentTree`  
`struct FCEClonerAttachmentTree`  
_L26-133_
- reflection: `USTRUCT()`
- desc: Represents a logical tree used by the cloner to render its attachments Could differ from the actual physical tree used in the scene
- L30 _public function_ `DECLARE_DELEGATE_TwoParams(FOnAttachmentChanged, AActor*, FCEClonerAttachmentItem&) FOnAttachmentChanged::RegistrationType& OnItemAttached()`
- L37 _public function_ `FOnAttachmentChanged::RegistrationType& OnItemDetached()`
- L43 _public prototype_ `void SetAttachmentRoot(AActor* InActor);` — Sets tree attachment root to scan from
- L46 _public prototype_ `AActor* GetAttachmentRoot() const;` — Gets tree attachment root
- L49 _public prototype_ `void SetBehaviorImplementation(const TSharedRef<ICEClonerAttachmentTreeBehavior>& InImplementation);` — Set the behavior implementation to use
- L52 _public prototype_ `void Cleanup();` — Performs cleanup before destruction
- L55 _public prototype_ `void MarkAttachmentOutdated();` — Marks the tree as outdated to perform an update
- L58 _public prototype_ `void MarkCacheOutdated(AActor* InActor);` — Marks the actor cache as outdated for an update
- L64 _public prototype_ `bool UpdateAttachments(bool bInReset = false);` — Triggers an update of the attachment tree to detect updated items If reset is true, clears the attachment tree and rebuilds it otherwise diff update
- L67 _public prototype_ `AActor* FindRootActor(AActor* InActor);` — Finds root actor of an actor based on this tree hierarchy by climbing up
- L70 _public prototype_ `FCEClonerAttachmentRootItem* FindRootItem(AActor* InActor);` — Finds root item of an actor based on this tree hierarchy by climbing up
- L73 _public prototype_ `TArray<AActor*> GetRootActors() const;` — Retrieves all root actors from this tree hierarchy
- L76 _public prototype_ `void ForEachAttachment(const TFunctionRef<bool(AActor*, FCEClonerAttachmentItem&)>& InFunctor);` — Traverses each attachment in tree, stops when false is returned
- L79 _public prototype_ `void DetachItem(AActor* InActor);` — Detach an item from the tree
- L82 _public prototype_ `bool IsCacheAvailable(bool bInAllowInvalid = true) const;` — True if all root meshes are valid and usable
- L85 _public prototype_ `void GetAttachments(AActor* InActor, TArray<const FCEClonerAttachmentItem*>& OutAttachmentItems, bool bInRecurse) const;` — Retrieves all attachments based on an actor
- L88 _public prototype_ `FBox GetAttachmentBounds(AActor* InActor, bool bInIncludeChildren) const;` — Get the attachment bounds based on tree hierarchy
- L92 _public prototype_ `TOptional<FVector> GetRootCachedMeshSize(AActor* InActor) const;` — Get cached size of root mesh, -1,-1,-1 when invalid
- L97 _public member_ `TMap<TWeakObjectPtr<AActor>, FCEClonerAttachmentItem> ItemAttachmentMap;` — `UPROPERTY()` — All cloner attached actor items
- L101 _public member_ `TArray<FCEClonerAttachmentRootItem> RootItemAttachments;` — `UPROPERTY()` — Root items directly attached to the cloner actor, order is important here
- L105 _public member_ `ECEClonerAttachmentStatus Status = ECEClonerAttachmentStatus::Outdated;` — `UPROPERTY(Transient)` — Status of the cloner tree
- L109 _public member_ `TSet<TWeakObjectPtr<AActor>> DirtyItemAttachments;` — `UPROPERTY(Transient)` — Attachment items that are dirty and need an update
- L113 _public member_ `bool bItemAttachmentsDirty = false;` — `UPROPERTY(Transient)` — Whether Added/Moved/Removed items requires an update
- L116 _private prototype_ `bool UpdateAttachmentsInternal();`
- L117 _private prototype_ `void UpdateAttachment(AActor* InActor, AActor* InParent, const FTransform& InActorTransform);`
- L118 _private prototype_ `void DetachItem(FCEClonerAttachmentItem& InItem);`
- L121 _private prototype_ `void Reset();` — Clears the whole tree
- L124 _private member_ `FOnAttachmentChanged OnItemAttachedDelegate;` — Called when tree item is attached
- L127 _private member_ `FOnAttachmentChanged OnItemDetachedDelegate;` — Called when tree item is detached
- L130 _private member_ `TObjectPtr<AActor> AttachmentRoot;` — `UPROPERTY(Transient)`
- L132 _private member_ `TSharedPtr<ICEClonerAttachmentTreeBehavior> BehaviorImplementation;`

#### Free symbols / members of external scopes

- L30 _delegate_ `DECLARE_DELEGATE_TwoParams(FOnAttachmentChanged, AActor*, FCEClonerAttachmentItem&) FOnAttachmentChanged::RegistrationType& OnItemAttached() { return OnItemAttachedDelegate; } FOnAttachmentChanged::RegistrationType& OnItemDetached() { return OnItemDetachedDelegate; } void SetAttachmentRoot(AActor* InActor);`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Attachments/CEClonerAttachmentTreeBehavior.h` (Public)


#### class `ICEClonerAttachmentTreeBehavior`  
`class ICEClonerAttachmentTreeBehavior : public TSharedFromThis<ICEClonerAttachmentTreeBehavior>`  
_L15-40_
- inherits: `TSharedFromThis<ICEClonerAttachmentTreeBehavior>`
- desc: Defines a custom implementation for the attachment tree
- L18 _public prototype_ `virtual ~ICEClonerAttachmentTreeBehavior() = default;`
- L21 _public prototype_ `virtual void OnActivation(FCEClonerAttachmentTree& InTree) = 0;` — Called when this implementation is activated
- L24 _public prototype_ `virtual void OnDeactivation(FCEClonerAttachmentTree& InTree) = 0;` — Called when this implementation is deactivated
- L27 _public prototype_ `virtual void GetOrderedChildrenActors(FCEClonerAttachmentTree& InTree, AActor* InActor, TArray<AActor*>& OutChildren) const = 0;` — Retrieve ordered list of children actors
- L30 _public prototype_ `virtual void InvalidateMesh(FCEClonerAttachmentTree& InTree, AActor* InActor) = 0;` — Attachment mesh status is out of date and needs an update
- L33 _public prototype_ `virtual void UpdateMesh(FCEClonerAttachmentTree& InTree, AActor* InActor) = 0;` — Update attachment mesh (materials)
- L36 _public prototype_ `virtual void OnItemAttached(FCEClonerAttachmentTree& InTree, FCEClonerAttachmentItem& InItem) = 0;` — Item is attached in the tree
- L39 _public prototype_ `virtual void OnItemDetached(FCEClonerAttachmentTree& InTree, FCEClonerAttachmentItem& InItem) = 0;` — Item is detached from the tree

#### class `FCEClonerAttachmentGroupBehavior`  
`class FCEClonerAttachmentGroupBehavior : public ICEClonerAttachmentTreeBehavior`  
_L43-83_
- inherits: `ICEClonerAttachmentTreeBehavior`
- desc: Base hierarchy where children are grouped under a root cloner actor
- L47 _protected prototype_ `virtual void OnActivation(FCEClonerAttachmentTree& InTree) override;`
- L48 _protected prototype_ `virtual void OnDeactivation(FCEClonerAttachmentTree& InTree) override;`
- L49 _protected prototype_ `virtual void GetOrderedChildrenActors(FCEClonerAttachmentTree& InTree, AActor* InActor, TArray<AActor*>& OutChildren) const override;`
- L50 _protected prototype_ `virtual void InvalidateMesh(FCEClonerAttachmentTree& InTree, AActor* InActor) override;`
- L51 _protected prototype_ `virtual void OnItemAttached(FCEClonerAttachmentTree& InTree, FCEClonerAttachmentItem& InItem) override;`
- L52 _protected prototype_ `virtual void OnItemDetached(FCEClonerAttachmentTree& InTree, FCEClonerAttachmentItem& InItem) override;`
- L53 _protected prototype_ `virtual void UpdateMesh(FCEClonerAttachmentTree& InTree, AActor* InActor) override;`
- L56 _protected prototype_ `void BindActorDelegates(FCEClonerAttachmentTree& InTree, AActor* InActor);`
- L57 _protected prototype_ `void UnbindActorDelegates(FCEClonerAttachmentTree& InTree, AActor* InActor);`
- L60 _protected prototype_ `void OnComponentTransformed(FCEClonerAttachmentTree& InTree, USceneComponent* InComponent, EUpdateTransformFlags InFlags, ETeleportType InTeleport);` — Called when the transform state of a cloned component changes
- L63 _protected prototype_ `void OnWorldActorDestroyed(FCEClonerAttachmentTree& InTree, AActor* InActor);` — Called when an actor in the world is destroyed
- L67 _protected prototype_ `void OnMeshChanged(FCEClonerAttachmentTree& InTree, AActor* InActor);` — Called when a mesh has changed in any cloned actors
- L70 _protected prototype_ `void OnRenderStateDirty(FCEClonerAttachmentTree& InTree, UActorComponent& InComponent);` — Called when the render state of a cloned component changes
- L73 _protected prototype_ `void OnLevelHierarchyChanged(FCEClonerAttachmentTree& InTree, AActor* InActor);` — Called when a level actor hierarchy changes
- L77 _protected prototype_ `void OnCheckMaterialChanged(FCEClonerAttachmentTree& InTree, UObject* InObject);` — Called when material is done compiling and when property is changed to test whether material have changed
- L80 _protected prototype_ `void RefreshBakedMeshRootMaterials(FCEClonerAttachmentTree& InTree, AActor* InActor);` — Called to update all materials of a root actor baked mesh
- L82 _protected member_ `FDelegateHandle WorldActorDestroyedDelegate;`

#### class `FCEClonerAttachmentFlatBehavior`  
`class FCEClonerAttachmentFlatBehavior : public FCEClonerAttachmentGroupBehavior`  
_L86-91_
- inherits: `FCEClonerAttachmentGroupBehavior`
- desc: Flat hierarchy where any grouped actor is unboxed as if it was under a root cloner actor
- L89 _private prototype_ `virtual void GetOrderedChildrenActors(FCEClonerAttachmentTree& InTree, AActor* InActor, TArray<AActor*>& OutChildren) const override;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Attachments/CEClonerAttachmentTypes.h` (Public)


#### enum `ECEClonerAttachmentStatus`  
`enum class ECEClonerAttachmentStatus : uint8`  
_L8-18_
- reflection: `UENUM()`
- L11 _public enumerator_ `Invalid` — Item should be removed, no longer valid
- L13 _public enumerator_ `Outdated` — Item should be updated, changes detected
- L15 _public enumerator_ `Updated` — Item is up to date, no changes needed
- L17 _public enumerator_ `Updating` — Item is being updated at the moment

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Attachments/CEClonerSceneTreeCustomResolver.h` (Public)


#### class `ICEClonerSceneTreeCustomResolver`  
`class ICEClonerSceneTreeCustomResolver : public TSharedFromThis<ICEClonerSceneTreeCustomResolver>`  
_L14-23_
- inherits: `TSharedFromThis<ICEClonerSceneTreeCustomResolver>`
- desc: Used to resolve underlying actors in the scene
- L17 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorHierarchyChanged, AActor* ) virtual ~ICEClonerSceneTreeCustomResolver() = default;`
- L19 _public prototype_ `virtual void Activate() = 0;`
- L20 _public prototype_ `virtual void Deactivate() = 0;`
- L21 _public prototype_ `virtual bool GetDirectChildrenActor(AActor* InActor, TArray<AActor*>& OutActors) const = 0;`
- L22 _public prototype_ `virtual FOnActorHierarchyChanged::RegistrationType& OnActorHierarchyChanged() = 0;`

#### Free symbols / members of external scopes

- L17 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnActorHierarchyChanged, AActor* ) virtual ~ICEClonerSceneTreeCustomResolver() = default;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/CEClonerActor.h` (Public)


#### class `ACEClonerActor`  
`class ACEClonerActor : public AActor`  
_L24-272_
- reflection: `UCLASS(MinimalAPI , BlueprintType , AutoExpandCategories=(ClonerComponent) , HideCategories=(Rendering,Replication,Collision,HLOD,Physics,Networking,Input,Actor,Cooking,LevelInstance,Streaming,DataLayers,WorldPartition) , DisplayName = "Motion Design Cloner Actor")`
- inherits: `AActor`
- L29 _public member_ `static inline const FString DefaultLabel = TEXT("Clo`
- L31 _public prototype_ `ACEClonerActor();`
- L34 _public function_ `UCEClonerComponent* GetClonerComponent() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L41 _public prototype_ `void SpawnDefaultActorAttached();` — Sets whether to spawn and attach a default actor on creation. Only available in editor engine
- L46 _protected prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L47 _protected prototype_ `virtual void PostLoad() override;`
- L52 _protected prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L57 _private prototype_ `void MigrateDeprecatedProperties();`
- L61 _private prototype_ `void OnEditorSelectionChanged(UObject* InSelection);` — Hide outline selection when this cloner only is selected in viewport
- L63 _private member_ `TOptional<bool> UseSelectionOutline;`
- L66 _private member_ `int32 MigrateToVersion = INDEX_NONE;`
- L69 _private member_ `TObjectPtr<UCEClonerComponent> ClonerComponent;` — `UPROPERTY(VisibleInstanceOnly, Category="Cloner")`
- L73 _private member_ `bool bEnabled = true;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L77 _private member_ `float TreeUpdateInterval = 0.2f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L81 _private member_ `int32 Seed = 0;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L85 _private member_ `FLinearColor Color = FLinearColor::White;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L89 _private member_ `bool bVisualizeEffectors;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L93 _private member_ `ECEClonerMeshRenderMode MeshRenderMode = ECEClonerMeshRenderMode::Iterate;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L97 _private member_ `ENiagaraMeshFacingMode MeshFacingMode = ENiagaraMeshFacingMode::Default;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L101 _private member_ `bool bMeshCastShadows = true;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L105 _private member_ `TArray<TObjectPtr<UStaticMesh>> DefaultMeshes;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L109 _private member_ `bool bUseOverrideMaterial = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L113 _private member_ `TObjectPtr<UMaterialInterface> OverrideMaterial;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L117 _private member_ `bool bSurfaceCollisionEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L121 _private member_ `bool bParticleCollisionEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L125 _private member_ `bool bCollisionVelocityEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L129 _private member_ `int32 CollisionIterations = 1;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L133 _private member_ `int32 CollisionGridResolution = 32;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L137 _private member_ `FVector CollisionGridSize = FVector(5000.f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L141 _private member_ `ECEClonerCollisionRadiusMode CollisionRadiusMode = ECEClonerCollisionRadiusMode::ExtentLength;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L145 _private member_ `TArray<float> CollisionRadii;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L149 _private member_ `float MassMin = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L153 _private member_ `float MassMax = 2.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L157 _private member_ `ECEClonerSpawnLoopMode SpawnLoopMode = ECEClonerSpawnLoopMode::Once;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L161 _private member_ `int32 SpawnLoopIterations = 1;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L165 _private member_ `float SpawnLoopInterval = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L169 _private member_ `ECEClonerSpawnBehaviorMode SpawnBehaviorMode = ECEClonerSpawnBehaviorMode::Instant;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L173 _private member_ `float SpawnRate = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L177 _private member_ `bool bLifetimeEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L181 _private member_ `float LifetimeMin = 0.25f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L185 _private member_ `float LifetimeMax = 1.5f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L189 _private member_ `bool bLifetimeScaleEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L193 _private member_ `FRichCurve LifetimeScaleCurve;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L197 _private member_ `FName LayoutName = NAME_None;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L201 _private member_ `bool bDeltaStepEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L205 _private member_ `FRotator DeltaStepRotation = FRotator(0.f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L209 _private member_ `FVector DeltaStepScale = FVector(0.f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L213 _private member_ `bool bRangeEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L217 _private member_ `FVector RangeOffsetMin = FVector::ZeroVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L221 _private member_ `FVector RangeOffsetMax = FVector::ZeroVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L225 _private member_ `FRotator RangeRotationMin = FRotator::ZeroRotator;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L229 _private member_ `FRotator RangeRotationMax = FRotator::ZeroRotator;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L233 _private member_ `bool bRangeScaleUniform = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L237 _private member_ `FVector RangeScaleMin = FVector::OneVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L241 _private member_ `FVector RangeScaleMax = FVector::OneVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L245 _private member_ `float RangeScaleUniformMin = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L249 _private member_ `float RangeScaleUniformMax = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L253 _private member_ `bool bInvertProgress = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L257 _private member_ `float Progress = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L261 _private member_ `TArray<TWeakObjectPtr<ACEEffectorActor>> EffectorsWeak;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L265 _private member_ `TMap<FName, TObjectPtr<UCEClonerLayoutBase>> LayoutInstances;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L270 _private member_ `bool bVisualizerSpriteVisible = true;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/CEClonerComponent.h` (Public)


#### class `UCEClonerComponent`  
`class UCEClonerComponent : public UNiagaraComponent`  
_L26-463_
- reflection: `UCLASS(MinimalAPI , BlueprintType , DisplayName = "Motion Design Cloner Component" , AutoExpandCategories=(Cloner, Layout) , HideCategories=(Transform, Niagara, Activation, Attachment, Randomness, Parameters) , meta = (BlueprintSpawnableComponent))`
- inherits: `UNiagaraComponent`
- L39 _public prototype_ `static FName GetActiveExtensionsPropertyName();`
- L41 _public prototype_ `static FName GetActiveLayoutPropertyName();`
- L43 _public prototype_ `static FName GetLayoutNamePropertyName();`
- L46 _public function_ `static FOnClonerMeshUpdated::RegistrationType& OnClonerMeshUpdated()`
- L51 _public function_ `static FOnClonerLayoutLoaded::RegistrationType& OnClonerLayoutLoaded()`
- L56 _public function_ `static FOnClonerInitialized::RegistrationType& OnClonerInitialized()`
- L61 _public function_ `static FOnClonerAttachmentChanged::RegistrationType& OnClonerActorAttached()`
- L66 _public function_ `static FOnClonerAttachmentChanged::RegistrationType& OnClonerActorDetached()`
- L71 _public prototype_ `UCEClonerComponent();`
- L74 _public prototype_ `void SetEnabled(bool bInEnable);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L77 _public function_ `bool GetEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L83 _public prototype_ `void SetSeed(int32 InSeed);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L86 _public function_ `int32 GetSeed() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L92 _public prototype_ `void SetColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L95 _public function_ `const FLinearColor& GetColor() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L101 _public prototype_ `void SetGlobalScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L104 _public function_ `const FVector& GetGlobalScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L110 _public prototype_ `void SetGlobalRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L113 _public function_ `const FRotator& GetGlobalRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L119 _public prototype_ `void SetLayoutName(FName InLayoutName);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L122 _public function_ `FName GetLayoutName() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L128 _public prototype_ `void SetLayoutClass(TSubclassOf<UCEClonerLayoutBase> InLayoutClass);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L131 _public prototype_ `TSubclassOf<UCEClonerLayoutBase> GetLayoutClass() const;` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L134 _public function_ `UCEClonerLayoutBase* GetActiveLayout() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L142 _public function_ `bool IsActiveLayout() const`
- L155 _public function_ `InLayoutClass* GetActiveLayout() const`
- L162 _public prototype_ `void SetTreeBehaviorName(FName InBehaviorName);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L165 _public function_ `FName GetTreeBehaviorName() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L171 _public prototype_ `void SetVisualizerSpriteVisible(bool bInVisible);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L174 _public function_ `bool GetVisualizerSpriteVisible() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L182 _public prototype_ `int32 GetMeshCount() const;` — `UFUNCTION(BlueprintPure, Category="Cloner")` — Returns the number of meshes this cloner currently handles
- L186 _public prototype_ `int32 GetAttachmentCount() const;` — `UFUNCTION(BlueprintPure, Category="Cloner")` — Returns the number of root attachment currently on this cloner
- L191 _public prototype_ `void ForceUpdateCloner();` — `UFUNCTION(CallInEditor, Category="Utilities")` — This will force an update of the cloner attachment tree
- L195 _public prototype_ `void OpenClonerSettings();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Open project settings for cloner
- L199 _public prototype_ `void CreateDefaultActorAttached();` — `UFUNCTION(CallInEditor, Category="Utilities")` — This will create a new default actor attached to this cloner if nothing is attached to this cloner
- L203 _public prototype_ `void ConvertToStaticMesh();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Converts the cloner simulation into a single static mesh, this is a heavy operation
- L207 _public prototype_ `void ConvertToDynamicMesh();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Converts the cloner simulation into a single dynamic mesh, this is a heavy operation
- L211 _public prototype_ `void ConvertToStaticMeshes();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Converts the cloner simulation into static meshes, this is a heavy operation
- L215 _public prototype_ `void ConvertToDynamicMeshes();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Converts the cloner simulation into dynamic meshes, this is a heavy operation
- L219 _public prototype_ `void ConvertToInstancedStaticMeshes();` — `UFUNCTION(CallInEditor, Category="Utilities")` — Converts the cloner simulation into instanced static meshes, this is a heavy operation
- L223 _public prototype_ `void RequestClonerUpdate(bool bInImmediate = false);` — Will force a system update to refresh user parameters
- L226 _public prototype_ `void RefreshClonerMeshes();` — Forces a refresh of the meshes used
- L229 _public function_ `template<typename InExtensionClass UE_REQUIRES(std::is_base_of_v<UCEClonerExtensionBase, InExtensionClass>)> InExtensionClass* GetExtension() const`
- L235 _public prototype_ `UCEClonerExtensionBase* GetExtension(TSubclassOf<UCEClonerExtensionBase> InExtensionClass) const;` — `UFUNCTION(BlueprintCallable, Category="Cloner", meta=(DeterminesOutputType="InExtensionClass"))`
- L237 _public prototype_ `UCEClonerExtensionBase* GetExtension(FName InExtensionName) const;`
- L239 _public function_ `TConstArrayView<TObjectPtr<UCEClonerExtensionBase>> GetActiveExtensions() const`
- L249 _public function_ `void GetActiveExtensions(TArray<UCEClonerExtensionBase*>& OutExtensions) const` — `UFUNCTION(BlueprintCallable, Category="Cloner")` — Retrieves all active extensions on this cloner @param OutExtensions [Out] Active extensions
- L255 _public prototype_ `TArray<AActor*> GetClonerRootActors() const;` — Retrieve root actors in their respective order
- L259 _protected member_ `static FOnClonerMeshUpdated OnClonerMeshUpdatedDelegate;` — Called when meshes have been updated
- L262 _protected member_ `static FOnClonerLayoutLoaded OnClonerLayoutLoadedDelegate;` — Called when new cloner layout is loaded
- L265 _protected member_ `static FOnClonerInitialized OnClonerInitializedDelegate;` — Called when cloner is initialized
- L268 _protected member_ `static FOnClonerAttachmentChanged OnClonerActorAttachedDelegate;` — Called when cloner actor is attached
- L271 _protected member_ `static FOnClonerAttachmentChanged OnClonerActorDetachedDelegate;` — Called when cloner actor is detached
- L274 _protected prototype_ `virtual void GetPreloadDependencies(TArray<UObject*>& OutDeps) override;`
- L275 _protected prototype_ `virtual void PostInitProperties() override;`
- L276 _protected prototype_ `virtual void PostLoad() override;`
- L278 _protected prototype_ `virtual void PreSave(FObjectPreSaveContext InSaveContext) override;`
- L279 _protected prototype_ `virtual void PreDuplicate(FObjectDuplicationParameters& InParams) override;`
- L280 _protected prototype_ `virtual void PostDuplicate(bool bInPIE) override;`
- L281 _protected prototype_ `virtual void PostEditImport() override;`
- L282 _protected prototype_ `virtual void PostEditUndo() override;`
- L283 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L288 _protected prototype_ `virtual void OnComponentCreated() override;`
- L289 _protected prototype_ `virtual void OnComponentDestroyed(bool bInDestroyingHierarchy) override;`
- L294 _protected prototype_ `void UpdateDirtyMeshesAsync();` — Runs async update to rebuild dirty meshes
- L297 _protected prototype_ `void UpdateActorDynamicMesh(AActor* InActor);` — Merges all primitive components from a single actor into a dynamic mesh
- L300 _protected prototype_ `void UpdateActorStaticMesh(AActor* InRootActor);` — Merges all actors dynamic meshes into a single static mesh
- L303 _protected prototype_ `void OnActorStaticMeshPostBuild(UStaticMesh* InMesh);` — Called once static mesh is done building
- L306 _protected prototype_ `void OnDirtyMeshesUpdated(bool bInSuccess);`
- L309 _protected prototype_ `void UpdateClonerMeshes();` — Update niagara asset static meshes
- L312 _protected prototype_ `void SetClonerActiveLayout(UCEClonerLayoutBase* InLayout);` — Sets the layout to use for this cloner simulation
- L314 _protected prototype_ `void OnActiveLayoutLoaded(UCEClonerLayoutBase* InLayout, bool bInSuccess);`
- L316 _protected prototype_ `void ActivateLayout(UCEClonerLayoutBase* InLayout);`
- L318 _protected prototype_ `void OnActiveLayoutChanged();`
- L322 _protected member_ `bool bEnabled = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetEnabled", Getter="GetEnabled", Category=General)` — Is this cloner enabled/disabled
- L326 _protected member_ `int32 Seed = 0;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category=General)` — Cloner instance seed for random deterministic patterns
- L330 _protected member_ `FLinearColor Color = FLinearColor::White;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category=General)` — Cloner color when unaffected by effectors, color will be passed down to the material (ParticleColor)
- L334 _protected member_ `FVector GlobalScale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category=General, meta=(ClampMin="0", Delta="0.01", MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))` — Global scale applied on all cloned items
- L338 _protected member_ `FRotator GlobalRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category=General)` — Global rotation applied on all cloned items
- L342 _protected member_ `FName TreeBehaviorName = NAME_None;` — `UPROPERTY(EditInstanceOnly, DisplayName="Tree Mode", Category=General, meta=(GetOptions="GetClonerTreeBehaviorNames"))` — Set the tree behavior with attachments
- L347 _protected member_ `bool bVisualizerSpriteVisible = true;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, Category=General, meta=(AllowPrivateAccess="true"))` — Toggle the sprite to visualize and click on this cloner
- L352 _protected member_ `FName LayoutName = NAME_None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Layout", Category="Layout", meta=(GetOptions="GetClonerLayoutNames"))` — Name of the layout to use
- L356 _protected member_ `TObjectPtr<UCEClonerLayoutBase> ActiveLayout;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Active layout used
- L360 _protected member_ `TArray<TObjectPtr<UCEClonerExtensionBase>> ActiveExtensions;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Active Extensions on this layout
- L364 _protected member_ `TArray<TObjectPtr<UCEClonerLayoutBase>> LayoutInstances;` — `UPROPERTY()` — Layout instances cached
- L368 _protected member_ `TArray<TObjectPtr<UCEClonerExtensionBase>> ExtensionInstances;` — `UPROPERTY()` — Layout extensions instances cached
- L371 _private member_ `static constexpr TCHAR SpriteTexturePath[] = TEXT("/Sc`
- L374 _private prototype_ `void InitializeCloner();` — Initiate and perform operation
- L375 _private prototype_ `void OnLevelLoaded(ULevel* InLevel, UWorld* InWorld);`
- L376 _private prototype_ `void PostInitializeCloner();`
- L377 _private prototype_ `void RegisterTicker();`
- L378 _private prototype_ `bool CheckResourcesReady();`
- L379 _private prototype_ `bool TickCloner(float InDelta);`
- L382 _private prototype_ `void UpdateClonerRenderState();` — Called to trigger an update of cloner rendering state tree
- L384 _private prototype_ `void OnEnabledChanged();`
- L385 _private prototype_ `void OnClonerEnabled();`
- L386 _private prototype_ `void OnClonerDisabled();`
- L387 _private prototype_ `void OnClonerSetEnabled(const UWorld* InWorld, bool bInEnabled, bool bInTransact);`
- L389 _private prototype_ `void OnSeedChanged();`
- L390 _private prototype_ `void OnColorChanged();`
- L391 _private prototype_ `void OnGlobalScaleChanged();`
- L392 _private prototype_ `void OnGlobalRotationChanged();`
- L393 _private prototype_ `void OnTreeBehaviorNameChanged();`
- L394 _private prototype_ `void OnLayoutNameChanged();`
- L397 _private prototype_ `void OnVisualizerSpriteVisibleChanged();`
- L400 _private prototype_ `void OnTreeItemAttached(AActor* InActor, FCEClonerAttachmentItem& InItem);`
- L401 _private prototype_ `void OnTreeItemDetached(AActor* InActor, FCEClonerAttachmentItem& InItem);`
- L406 _private function_ `InLayoutClass* FindOrAddLayout()`
- L412 _private prototype_ `UCEClonerLayoutBase* FindOrAddLayout(TSubclassOf<UCEClonerLayoutBase> InClass);` — Find or add a layout by its class
- L415 _private prototype_ `UCEClonerLayoutBase* FindOrAddLayout(FName InLayoutName);` — Find or add a layout by its name
- L420 _private function_ `InExtensionClass* FindOrAddExtension()`
- L426 _private prototype_ `UCEClonerExtensionBase* FindOrAddExtension(TSubclassOf<UCEClonerExtensionBase> InClass);` — Find or add an extension by its class
- L429 _private prototype_ `UCEClonerExtensionBase* FindOrAddExtension(FName InExtensionName);` — Find or add an extension by its name
- L433 _private prototype_ `TArray<FName> GetClonerLayoutNames() const;` — `UFUNCTION()` — Gets all layout names available
- L437 _private prototype_ `TArray<FName> GetClonerTreeBehaviorNames() const;` — `UFUNCTION()` — Gets all tree implementation names available
- L441 _private member_ `FCEClonerAttachmentTree ClonerTree;` — `UPROPERTY(NonTransactional)` — Attachment tree view
- L445 _private member_ `FCEMeshBuilder MeshBuilder;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Mesh builder to create final meshes that are sent to niagara
- L448 _private member_ `std::atomic<bool> bClonerMeshesUpdating = false;` — State of the baked dynamic and static mesh creation
- L450 _private member_ `bool bNeedsRefresh = false;`
- L452 _private member_ `bool bClonerInitialized = false;`
- L454 _private member_ `bool bClonerResourcesReady = false;`
- L456 _private member_ `FTSTicker::FDelegateHandle ClonerTickerHandle;`
- L457 _private member_ `FTSTicker::FDelegateHandle ConversionTickerHandle;`
- L461 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerComponent> PropertyChangeDispatcher;` — Used for PECP

#### Free symbols / members of external scopes

- L32 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClonerMeshUpdated, UCEClonerComponent* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerLayoutLoaded, UCEClonerComponent* , UCEClonerLayoutBase* ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnClonerInitialized, UCEClonerComponent* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerAttachmentChanged, UCEClonerComponent* , AActor* ) public: #if WITH_EDITOR static FName GetActiveExtensionsPropertyName();`
- L33 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerLayoutLoaded, UCEClonerComponent* , UCEClonerLayoutBase* ) DECLARE_MULTICAST_DELEGATE_OneParam(FOnClonerInitialized, UCEClonerComponent* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerAttachmentChanged, UCEClonerComponent* , AActor* ) public: #if WITH_EDITOR static FName GetActiveExtensionsPropertyName();`
- L34 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnClonerInitialized, UCEClonerComponent* ) DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerAttachmentChanged, UCEClonerComponent* , AActor* ) public: #if WITH_EDITOR static FName GetActiveExtensionsPropertyName();`
- L35 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerAttachmentChanged, UCEClonerComponent* , AActor* ) public: #if WITH_EDITOR static FName GetActiveExtensionsPropertyName();`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerCollisionExtension.h` (Public)


#### class `UCEClonerCollisionExtension`  
`class UCEClonerCollisionExtension : public UCEClonerExtensionBase`  
_L15-189_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, AutoExpandCategories=("Collisions"), meta=(Section="Physics", Priority=90))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with collisions and physics related options
- L20 _public prototype_ `UCEClonerCollisionExtension();`
- L23 _public prototype_ `void SetSurfaceCollisionEnabled(bool bInSurfaceCollisionEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L26 _public function_ `bool GetSurfaceCollisionEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L32 _public prototype_ `void SetParticleCollisionEnabled(bool bInParticleCollisionEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L35 _public function_ `bool GetParticleCollisionEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L41 _public prototype_ `void SetCollisionVelocityEnabled(bool bInCollisionVelocityEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L44 _public function_ `bool GetCollisionVelocityEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L50 _public prototype_ `void SetCollisionIterations(int32 InCollisionIterations);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L53 _public function_ `int32 GetCollisionIterations() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L59 _public prototype_ `void SetCollisionGridResolution(int32 InCollisionGridResolution);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L62 _public function_ `int32 GetCollisionGridResolution() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L68 _public prototype_ `void SetCollisionGridSize(const FVector& InCollisionGridSize);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L71 _public function_ `FVector GetCollisionGridSize() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L77 _public prototype_ `void SetCollisionRadiusMode(ECEClonerCollisionRadiusMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L80 _public function_ `ECEClonerCollisionRadiusMode GetCollisionRadiusMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L86 _public function_ `const TArray<float>& GetCollisionRadii() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L92 _public prototype_ `void SetMassMin(float InMassMin);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L95 _public function_ `float GetMassMin() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L101 _public prototype_ `void SetMassMax(float InMassMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L104 _public function_ `float GetMassMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L112 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L117 _protected prototype_ `virtual void OnExtensionDeactivated() override;`
- L118 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L119 _protected prototype_ `virtual void OnClonerMeshesUpdated() override;`
- L123 _protected prototype_ `bool ShouldInitVisualizerComponent(TNotNull<const UCEClonerComponent*> InComponent) const;`
- L124 _protected prototype_ `bool InitVisualizerComponent();`
- L125 _protected prototype_ `void DestroyVisualizerComponent();`
- L133 _protected member_ `bool bSurfaceCollisionEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetSurfaceCollisionEnabled", Getter="GetSurfaceCollisionEnabled", Category="Collisions", meta=(RefreshPropertyView))` — Allow particles to react to surface by using the distance field, ensure the mesh you want particle to collide with is tick enough or increase its distance field resolution scale in static mesh editor
- L137 _protected member_ `bool bParticleCollisionEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetParticleCollisionEnabled", Getter="GetParticleCollisionEnabled", Category="Collisions", meta=(RefreshPropertyView))` — Allow particles to react to other emitter particles, uses a neighbor grid to detect collision
- L141 _protected member_ `bool bCollisionVelocityEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetCollisionVelocityEnabled", Getter="GetCollisionVelocityEnabled", Category="Collisions", meta=(EditCondition="bParticleCollisionEnabled", EditConditionHides))` — Recalculate accurate velocity after collision is updated
- L145 _protected member_ `int32 CollisionIterations = 1;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Collisions", meta=(ClampMin="1", EditCondition="bParticleCollisionEnabled", EditConditionHides))` — Amount of iterations to improve particle collision results but affects performance
- L149 _protected member_ `int32 CollisionGridResolution = 32;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Collisions", meta=(ClampMin="1", EditCondition="bParticleCollisionEnabled", EditConditionHides))` — Resolution of the neighbor grid to detect collision between particles
- L153 _protected member_ `FVector CollisionGridSize = FVector(5000.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Collisions", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", EditCondition="bParticleCollisionEnabled", EditConditionHides))` — Size of the neighbor grid to detect collision between particles, particles outside this grid will not have collisions
- L157 _protected member_ `ECEClonerCollisionRadiusMode CollisionRadiusMode = ECEClonerCollisionRadiusMode::ExtentLength;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Collisions", meta=(EditCondition="bSurfaceCollisionEnabled || bParticleCollisionEnabled", EditConditionHides, RefreshPropertyView))` — Collision radius calculation mode
- L161 _protected member_ `TArray<float> CollisionRadii;` — `UPROPERTY(EditInstanceOnly, Getter, Category="Collisions", EditFixedSize, meta=(ClampMin="0", EditFixedOrder, EditCondition="(bSurfaceCollisionEnabled || bParticleCollisionEnabled) && CollisionRadiusMode == ECEClonerCollisionRadiusMode::Manual", EditConditionHides))` — Radius expected around each particle for collision, order matches attachment index
- L165 _protected member_ `float MassMin = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Collisions", meta=(ClampMin="1"))` — Minimum particle mass, used for collisions to push apart
- L169 _protected member_ `float MassMax = 2.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Collisions", meta=(ClampMin="1"))` — Maximum particle mass, used for collisions to push apart
- L174 _protected member_ `bool bPreviewCollisionGrid = false;` — `UPROPERTY(EditInstanceOnly, Category="Collisions", meta=(EditCondition="bParticleCollisionEnabled", EditConditionHides))` — Preview 3D neighbor grid used for collision
- L178 _protected member_ `TObjectPtr<UStaticMeshComponent> CollisionVisualizerComponent;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Used to preview collision grid in editor
- L181 _protected member_ `TObjectPtr<UMaterialInstanceDynamic> CollisionVisualizerMaterial;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)`
- L187 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerCollisionExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerConstraintExtension.h` (Public)


#### class `UCEClonerConstraintExtension`  
`class UCEClonerConstraintExtension : public UCEClonerExtensionBase`  
_L11-233_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Cloner", Priority=40))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with clone grid constraints
- L16 _public prototype_ `UCEClonerConstraintExtension();`
- L19 _public prototype_ `void SetConstraint(ECEClonerGridConstraint InConstraint);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L22 _public function_ `ECEClonerGridConstraint GetConstraint() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L28 _public prototype_ `void SetInvertConstraint(bool bInInvertConstraint);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L31 _public function_ `bool GetInvertConstraint() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L37 _public prototype_ `void SetSphereRadius(float InSphereRadius);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L40 _public function_ `float GetSphereRadius() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L46 _public prototype_ `void SetSphereCenter(const FVector& InSphereCenter);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L49 _public function_ `FVector GetSphereCenter() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L55 _public prototype_ `void SetCylinderRadius(float InCylinderRadius);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L58 _public function_ `float GetCylinderRadius() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L64 _public prototype_ `void SetCylinderHeight(float InCylinderHeight);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L67 _public function_ `float GetCylinderHeight() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L73 _public prototype_ `void SetCylinderCenter(const FVector& InCylinderCenter);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L76 _public function_ `FVector GetCylinderCenter() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L82 _public prototype_ `void SetTextureAsset(UTexture* InTexture);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L85 _public function_ `UTexture* GetTextureAsset() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L91 _public prototype_ `void SetTextureSampleMode(ECEClonerTextureSampleChannel InSampleMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L94 _public function_ `ECEClonerTextureSampleChannel GetTextureSampleMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L100 _public prototype_ `void SetTexturePlane(ECEClonerPlane InPlane);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L103 _public function_ `ECEClonerPlane GetTexturePlane() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L109 _public prototype_ `void SetTextureCompareMode(ECEClonerCompareMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L112 _public function_ `ECEClonerCompareMode GetTextureCompareMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L118 _public prototype_ `void SetTextureThreshold(float InThreshold);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L121 _public function_ `float GetTextureThreshold() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L127 _public prototype_ `void SetTextureOffset(const FVector2D& InOffset);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L130 _public function_ `FVector2D GetTextureOffset() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L136 _public prototype_ `void SetTextureRotation(float InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L139 _public function_ `float GetTextureRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L145 _public prototype_ `void SetTextureScale(const FVector2D& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L148 _public function_ `FVector2D GetTextureScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L154 _public prototype_ `void SetTextureClamp(bool bInClamp);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L157 _public function_ `bool GetTextureClamp() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L165 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L170 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L171 _protected prototype_ `virtual bool IsLayoutSupported(const UCEClonerLayoutBase* InLayout) const override;`
- L175 _protected member_ `ECEClonerGridConstraint Constraint = ECEClonerGridConstraint::None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(RefreshPropertyView))`
- L178 _protected member_ `bool bInvertConstraint = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetInvertConstraint", Getter="GetInvertConstraint", Category="Constraint", meta=(EditCondition="Constraint != ECEClonerGridConstraint::None", EditConditionHides))`
- L183 _protected member_ `float SphereRadius = 400.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Sphere", EditConditionHides))`
- L186 _protected member_ `FVector SphereCenter = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Sphere", EditConditionHides))`
- L191 _protected member_ `float CylinderRadius = 400.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Cylinder", EditConditionHides))`
- L194 _protected member_ `float CylinderHeight = 800.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Cylinder", EditConditionHides))`
- L197 _protected member_ `FVector CylinderCenter = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Cylinder", EditConditionHides))`
- L202 _protected member_ `TObjectPtr<UTexture> TextureAsset;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L205 _protected member_ `ECEClonerPlane TexturePlane = ECEClonerPlane::XY;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(InvalidEnumValues="Custom", EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L208 _protected member_ `ECEClonerTextureSampleChannel TextureSampleMode = ECEClonerTextureSampleChannel::RGBLuminance;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L211 _protected member_ `ECEClonerCompareMode TextureCompareMode = ECEClonerCompareMode::Greater;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L214 _protected member_ `float TextureThreshold = 0.1f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(ClampMin="0", EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L217 _protected member_ `FVector2D TextureOffset = FVector2D::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L220 _protected member_ `float TextureRotation = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L223 _protected member_ `FVector2D TextureScale = FVector2D(1.0);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Constraint", meta=(Delta="0.01", MotionDesignVectorWidget, AllowPreserveRatio="XY", EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L226 _protected member_ `bool bTextureClamp = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetTextureClamp", Getter="GetTextureClamp", Category="Constraint", meta=(EditCondition="Constraint == ECEClonerGridConstraint::Texture", EditConditionHides))`
- L231 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerConstraintExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerDisplacementExtension.h` (Public)


#### class `UCEClonerDisplacementExtension`  
`class UCEClonerDisplacementExtension : public UCEClonerExtensionBase`  
_L11-178_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Cloner", Priority=50))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with clone grid displacements
- L16 _public prototype_ `UCEClonerDisplacementExtension();`
- L19 _public prototype_ `void SetDisplacementEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L22 _public function_ `bool GetDisplacementEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L28 _public prototype_ `void SetDisplacementInvert(bool bInInvert);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L31 _public function_ `bool GetDisplacementInvert() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L37 _public prototype_ `void SetDisplacementOffsetMax(const FVector& InMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L40 _public function_ `const FVector& GetDisplacementOffsetMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L46 _public prototype_ `void SetDisplacementRotationMax(const FRotator& InMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L49 _public function_ `const FRotator& GetDisplacementRotationMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L55 _public prototype_ `void SetDisplacementScaleMax(const FVector& InMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L58 _public function_ `const FVector& GetDisplacementScaleMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L64 _public prototype_ `void SetDisplacementTextureAsset(UTexture* InTexture);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L67 _public function_ `UTexture* GetDisplacementTextureAsset() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L73 _public prototype_ `void SetDisplacementTextureSampleMode(ECEClonerTextureSampleChannel InSampleMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L76 _public function_ `ECEClonerTextureSampleChannel GetDisplacementTextureSampleMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L82 _public prototype_ `void SetDisplacementTexturePlane(ECEClonerPlane InPlane);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L85 _public function_ `ECEClonerPlane GetDisplacementTexturePlane() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L91 _public prototype_ `void SetDisplacementTextureOffset(const FVector2D& InOffset);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L94 _public function_ `FVector2D GetDisplacementTextureOffset() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L100 _public prototype_ `void SetDisplacementTextureRotation(float InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L103 _public function_ `float GetDisplacementTextureRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L109 _public prototype_ `void SetDisplacementTextureScale(const FVector2D& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L112 _public function_ `FVector2D GetDisplacementTextureScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L118 _public prototype_ `void SetDisplacementTextureClamp(bool bInClamp);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L121 _public function_ `bool GetDisplacementTextureClamp() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L129 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L134 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L135 _protected prototype_ `virtual bool IsLayoutSupported(const UCEClonerLayoutBase* InLayout) const override;`
- L139 _protected member_ `bool bDisplacementEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetDisplacementEnabled", Getter="GetDisplacementEnabled", DisplayName="Enabled", Category="Displacement", meta=(RefreshPropertyView))`
- L142 _protected member_ `bool bDisplacementInvert = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetDisplacementInvert", Getter="GetDisplacementInvert", DisplayName="Invert", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L145 _protected member_ `FVector DisplacementOffsetMax = FVector(0, 0, 100.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Offset", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L148 _protected member_ `FRotator DisplacementRotationMax = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Rotation", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L151 _protected member_ `FVector DisplacementScaleMax = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Scale", Category="Displacement", meta=(ClampMin="0", Delta="0.01", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", EditCondition="bDisplacementEnabled", EditConditionHides))`
- L154 _protected member_ `TObjectPtr<UTexture> DisplacementTextureAsset;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="TextureAsset", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L157 _protected member_ `ECEClonerPlane DisplacementTexturePlane = ECEClonerPlane::XY;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="TexturePlane", Category="Displacement", meta=(InvalidEnumValues="Custom", EditCondition="bDisplacementEnabled", EditConditionHides))`
- L160 _protected member_ `ECEClonerTextureSampleChannel DisplacementTextureSampleMode = ECEClonerTextureSampleChannel::RGBLuminance;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="TextureSampleMode", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L163 _protected member_ `FVector2D DisplacementTextureOffset = FVector2D::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="TextureOffset", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L166 _protected member_ `float DisplacementTextureRotation = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="TextureRotation", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L169 _protected member_ `FVector2D DisplacementTextureScale = FVector2D(1.0);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="TextureScale", Category="Displacement", meta=(Delta="0.01", MotionDesignVectorWidget, AllowPreserveRatio="XY", EditCondition="bDisplacementEnabled", EditConditionHides))`
- L172 _protected member_ `bool bDisplacementTextureClamp = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetDisplacementTextureClamp", Getter="GetDisplacementTextureClamp", DisplayName="TextureClamp", Category="Displacement", meta=(EditCondition="bDisplacementEnabled", EditConditionHides))`
- L176 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerDisplacementExtension> PropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerEffectorExtension.h` (Public)


#### class `UCEClonerEffectorExtension`  
`class UCEClonerEffectorExtension : public UCEClonerExtensionBase`  
_L16-80_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Effector", Priority=30))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with effectors options
- L22 _public prototype_ `static FName GetEffectorActorsWeakName();`
- L25 _public prototype_ `UCEClonerEffectorExtension();`
- L29 _public prototype_ `int32 GetEffectorCount() const;` — `UFUNCTION(BlueprintPure, Category="Cloner")` — Gets the number of effectors applied on this cloner
- L33 _public prototype_ `bool LinkEffector(AActor* InEffectorActor);` — `UFUNCTION(BlueprintCallable, Category="Cloner")` — Links new actor effectors to apply transformation on clones
- L37 _public prototype_ `bool UnlinkEffector(AActor* InEffectorActor);` — `UFUNCTION(BlueprintCallable, Category="Cloner")` — Unlinks the effector actor and reset the cloner simulation
- L41 _public prototype_ `bool IsEffectorLinked(const AActor* InEffectorActor) const;` — `UFUNCTION(BlueprintPure, Category="Cloner")` — Checks if an effector is linked with this cloner
- L46 _public prototype_ `void CreateLinkedEffector();` — `UFUNCTION(CallInEditor, Category="Effector")` — This will create a new effector actor, link it to this cloner and select it
- L52 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L53 _protected prototype_ `virtual void PostEditUndo() override;`
- L58 _protected prototype_ `virtual void OnExtensionActivated() override;`
- L59 _protected prototype_ `virtual void OnExtensionDeactivated() override;`
- L60 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L63 _protected prototype_ `void OnEffectorIdentifierChanged(UCEEffectorComponent* InEffector, int32 InOldIdentifier, int32 InNewIdentifier);`
- L64 _protected prototype_ `void OnEffectorsChanged();`
- L65 _protected prototype_ `void OnEffectorActorsChanged();`
- L69 _protected member_ `TArray<TWeakObjectPtr<AActor>> EffectorActorsWeak;` — `UPROPERTY(EditInstanceOnly, Category="Effector", meta=(DisplayName="Effectors"))` — Effectors actors linked to this cloner
- L74 _private member_ `TSet<TWeakObjectPtr<UCEEffectorComponent>> EffectorsInternalWeak;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient, NonTransactional)` — Copy of effectors linked to this cloner to compare diffs
- L78 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerEffectorExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerEmitterSpawnExtension.h` (Public)


#### class `UCEClonerEmitterSpawnExtension`  
`class UCEClonerEmitterSpawnExtension : public UCEClonerExtensionBase`  
_L14-145_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Emission", Priority=70))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with clones spawning options
- L19 _public prototype_ `UCEClonerEmitterSpawnExtension();`
- L22 _public prototype_ `void SetSpawnLoopMode(ECEClonerSpawnLoopMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L25 _public function_ `ECEClonerSpawnLoopMode GetSpawnLoopMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L31 _public prototype_ `void SetSpawnLoopIterations(int32 InIterations);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L34 _public function_ `int32 GetSpawnLoopIterations() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L40 _public prototype_ `void SetSpawnLoopInterval(float InInterval);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L43 _public function_ `float GetSpawnLoopInterval() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L49 _public prototype_ `void SetSpawnBehaviorMode(ECEClonerSpawnBehaviorMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L52 _public function_ `ECEClonerSpawnBehaviorMode GetSpawnBehaviorMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L58 _public prototype_ `void SetSpawnRate(float InRate);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L61 _public function_ `float GetSpawnRate() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L67 _public prototype_ `void SetSpawnMaxFrameCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L70 _public function_ `int32 GetSpawnMaxFrameCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L76 _public prototype_ `void SetSpawnMaxTotalCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L79 _public function_ `int32 GetSpawnMaxTotalCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L86 _public prototype_ `void SetUseLocalSpace(bool bInLocalSpace);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L89 _public function_ `bool GetUseLocalSpace() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L98 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L103 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L108 _protected member_ `ECEClonerSpawnLoopMode SpawnLoopMode = ECEClonerSpawnLoopMode::Once;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Emission Mode", Category="Spawn", meta=(RefreshPropertyView))` — How many times do we spawn clones
- L112 _protected member_ `int32 SpawnLoopIterations = 1;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Emission Count", Category="Spawn", meta=(ClampMin="1", EditCondition="SpawnLoopMode == ECEClonerSpawnLoopMode::Multiple", EditConditionHides))` — Amount of spawn iterations for clones
- L116 _protected member_ `ECEClonerSpawnBehaviorMode SpawnBehaviorMode = ECEClonerSpawnBehaviorMode::Instant;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Emission Style", Category="Spawn", meta=(EditCondition="SpawnLoopMode != ECEClonerSpawnLoopMode::Once", EditConditionHides, RefreshPropertyView))` — How does spawn occurs
- L120 _protected member_ `float SpawnLoopInterval = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Emission Interval", Category="Spawn", meta=(ClampMin="0", EditCondition="SpawnLoopMode != ECEClonerSpawnLoopMode::Once && SpawnBehaviorMode == ECEClonerSpawnBehaviorMode::Instant", EditConditionHides))` — Interval/Duration of spawn for clones
- L124 _protected member_ `float SpawnRate = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Emission Rate", Category="Spawn", meta=(ClampMin="0", EditCondition="SpawnLoopMode != ECEClonerSpawnLoopMode::Once && SpawnBehaviorMode == ECEClonerSpawnBehaviorMode::Rate", EditConditionHides))` — How many clones to spawn each seconds
- L128 _protected member_ `bool bUseLocalSpace = true;` — `UPROPERTY(EditInstanceOnly, Category="Spawn", meta=(EditCondition="SpawnLoopMode != ECEClonerSpawnLoopMode::Once", EditConditionHides))` — Simulation takes place in local space or world space
- L132 _protected member_ `int32 SpawnMaxFrameCount = 1000000;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Max Frame Spawn Count", Category="Spawn", meta=(ClampMin="0"))` — Amount of particle allowed to spawn in a single frame
- L136 _protected member_ `int32 SpawnMaxTotalCount = 1000000;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Max Total Spawn Count", Category="Spawn", meta=(ClampMin="0"))` — Amount of particle allowed to spawn by the emitter
- L141 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerEmitterSpawnExtension> PropertyChangeDispatcher;` — Used for PECP
- L143 _private prototype_ `void OnLocalSpaceChanged();`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerExtensionBase.h` (Public)


#### class `UCEClonerExtensionBase`  
`class UCEClonerExtensionBase : public UObject`  
_L15-122_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Within=CEClonerComponent)`
- inherits: `UObject`
- desc: Reusable extension on cloner layout to group similar options
- L20 _public prototype_ `UCEClonerExtensionBase();`
- L22 _public prototype_ `UCEClonerExtensionBase(FName InExtensionName, int32 InExtensionPriority);`
- L25 _public function_ `FName GetExtensionName() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L30 _public function_ `int32 GetExtensionPriority() const`
- L36 _public prototype_ `FCEExtensionSection GetExtensionSection() const;`
- L40 _public prototype_ `UCEClonerComponent* GetClonerComponent() const;` — Get the cloner component using this extension
- L43 _public prototype_ `UCEClonerComponent* GetClonerComponentChecked() const;` — Get the cloner component using this extension checked version
- L46 _public prototype_ `UCEClonerLayoutBase* GetClonerLayout() const;` — Get the cloner active layout that uses this extension
- L49 _public prototype_ `void ActivateExtension();` — Enable this extension
- L52 _public prototype_ `void DeactivateExtension();` — Disable this extension
- L55 _public function_ `bool IsExtensionActive() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L64 _public function_ `virtual bool OnUpdateClonerMeshes(TArray<FNiagaraMeshRendererMeshPropertiesBase>& InOutMeshes)` — Called when the meshes are being updated. With opportunity for extension to change the mesh data. @return true if the meshes were changed.
- L70 _public function_ `virtual void OnClonerMeshesUpdated()` — Called when the meshes are updated
- L73 _public prototype_ `void UpdateExtensionParameters();` — Updates all extensions parameters
- L76 _public prototype_ `void MarkExtensionDirty(bool bInUpdateCloner = true);` — Request refresh extension next tick
- L79 _public prototype_ `bool IsExtensionDirty() const;` — Is this extension dirty
- L82 _public function_ `virtual bool IsLayoutSupported(const UCEClonerLayoutBase* InLayout) const` — Filter supported layout for this extension
- L88 _public function_ `virtual void OnExtensionDirtied(const UCEClonerExtensionBase* InExtension)` — Called when an active extension is dirtied to allow other extensions to react accordingly
- L92 _protected prototype_ `virtual void PostEditImport() override;`
- L94 _protected prototype_ `virtual void PostEditUndo() override;`
- L99 _protected function_ `virtual void OnExtensionActivated()` — Called when the extension becomes active
- L102 _protected function_ `virtual void OnExtensionDeactivated()` — Called when the extension becomes inactive
- L105 _protected function_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent)` — Called to reapply extension parameters
- L108 _protected prototype_ `void OnExtensionPropertyChanged();` — Used by PECP to update parameters
- L113 _private member_ `FName ExtensionName = NAME_None;` — `UPROPERTY(Transient)` — Unique extension name for the cloner
- L117 _private member_ `int32 ExtensionPriority = 0;` — `UPROPERTY(Transient)` — Some extensions need to be called before or after others
- L119 _private member_ `bool bExtensionActive = false;`
- L121 _private member_ `ECEClonerSystemStatus ExtensionStatus = ECEClonerSystemStatus::UpToDate;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerLifetimeExtension.h` (Public)


#### class `UCEClonerLifetimeExtension`  
`class UCEClonerLifetimeExtension : public UCEClonerExtensionBase`  
_L15-115_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Emission", Priority=80))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with clones lifetime options
- L20 _public prototype_ `UCEClonerLifetimeExtension();`
- L23 _public prototype_ `void SetLifetimeEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L26 _public function_ `bool GetLifetimeEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L32 _public prototype_ `void SetLifetimeMin(float InMin);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L35 _public function_ `float GetLifetimeMin() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L41 _public prototype_ `void SetLifetimeMax(float InMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L44 _public function_ `float GetLifetimeMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L50 _public prototype_ `void SetLifetimeScaleEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L53 _public function_ `bool GetLifetimeScaleEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L59 _public prototype_ `void SetLifetimeScaleCurve(UCurveFloat* InCurve);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L61 _public prototype_ `void SetLifetimeScaleCurve(const FRichCurve& InCurve);`
- L63 _public function_ `const FRichCurve& GetLifetimeScaleCurve() const`
- L68 _public function_ `UNiagaraDataInterfaceCurve* GetLifetimeScaleCurveDI() const`
- L76 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L81 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L84 _protected prototype_ `void OnLifetimeScaleCurveChanged();`
- L88 _protected member_ `bool bLifetimeEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetLifetimeEnabled", Getter="GetLifetimeEnabled", DisplayName="Enabled", Category="Lifetime", meta=(RefreshPropertyView))` — Do we destroy the clones after a specific duration
- L92 _protected member_ `float LifetimeMin = 0.25f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Min", Category="Lifetime", meta=(ClampMin="0", EditCondition="bLifetimeEnabled", EditConditionHides))` — Minimum lifetime for a clone
- L96 _protected member_ `float LifetimeMax = 1.5f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Max", Category="Lifetime", meta=(ClampMin="0", EditCondition="bLifetimeEnabled", EditConditionHides))` — Maximum lifetime for a clone
- L100 _protected member_ `bool bLifetimeScaleEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetLifetimeScaleEnabled", Getter="GetLifetimeScaleEnabled", DisplayName="ScaleEnabled", Category="Lifetime", meta=(EditCondition="bLifetimeEnabled", EditConditionHides, RefreshPropertyView))` — Enable scale by lifetime
- L104 _protected member_ `TWeakObjectPtr<UNiagaraDataInterfaceCurve> LifetimeScaleCurveDIWeak;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Used to expose the scale curve editor in details panel
- L108 _protected member_ `FRichCurve LifetimeScaleCurve;` — `UPROPERTY(Setter, Getter)` — Rich curve used in the data interface for the lifetime
- L113 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerLifetimeExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerMeshRendererExtension.h` (Public)


#### class `UCEClonerMeshRendererExtension`  
`class UCEClonerMeshRendererExtension : public UCEClonerExtensionBase`  
_L13-154_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Rendering", Priority=110))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with mesh rendering options
- L18 _public prototype_ `UCEClonerMeshRendererExtension();`
- L21 _public prototype_ `void SetMeshRenderMode(ECEClonerMeshRenderMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L24 _public function_ `ECEClonerMeshRenderMode GetMeshRenderMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L30 _public prototype_ `void SetMeshFacingMode(ENiagaraMeshFacingMode InMode);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L33 _public function_ `ENiagaraMeshFacingMode GetMeshFacingMode() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L39 _public prototype_ `void SetMeshCastShadows(bool InbCastShadows);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L42 _public function_ `bool GetMeshCastShadows() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L47 _public prototype_ `void SetDefaultMeshes(const TArray<TObjectPtr<UStaticMesh>>& InMeshes);`
- L49 _public function_ `const TArray<TObjectPtr<UStaticMesh>>& GetDefaultMeshes() const`
- L55 _public prototype_ `void SetDefaultMeshes(const TArray<UStaticMesh*>& InMeshes);` — `UFUNCTION(BlueprintCallable, Category="Cloner", meta=(DisplayName="SetDefaultMeshes"))`
- L58 _public prototype_ `void GetDefaultMeshes(TArray<UStaticMesh*>& OutMeshes) const;` — `UFUNCTION(BlueprintPure, Category="Cloner", meta=(DisplayName="GetDefaultMeshes"))`
- L61 _public prototype_ `void SetVisualizeEffectors(bool bInVisualize);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L64 _public function_ `bool GetVisualizeEffectors() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L70 _public prototype_ `void SetUseOverrideMaterial(bool bInOverride);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L73 _public function_ `bool GetUseOverrideMaterial() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L79 _public prototype_ `void SetOverrideMaterial(UMaterialInterface* InMaterial);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L82 _public function_ `UMaterialInterface* GetOverrideMaterial() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L88 _public prototype_ `void SetSortTranslucentParticles(bool bInSort);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L91 _public function_ `bool GetSortTranslucentParticles() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L99 _protected prototype_ `virtual void PostTransacted(const FTransactionObjectEvent& InTransactionEvent) override;`
- L100 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L105 _protected prototype_ `virtual bool OnUpdateClonerMeshes(TArray<FNiagaraMeshRendererMeshPropertiesBase>& InOutMeshes) override;`
- L106 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L110 _protected prototype_ `int32 GetClonerMeshesMaterialCount() const;` — Get the number of material slots available
- L113 _protected prototype_ `TArray<FNiagaraMeshMaterialOverride> GetOverrideMeshesMaterials() const;` — Get the niagara materials override if enabled
- L115 _protected prototype_ `void OnOverrideMaterialOptionsChanged();`
- L119 _protected member_ `ECEClonerMeshRenderMode MeshRenderMode = ECEClonerMeshRenderMode::Iterate;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Renderer")` — Indicates how we select the mesh to render on each clones
- L123 _protected member_ `ENiagaraMeshFacingMode MeshFacingMode = ENiagaraMeshFacingMode::Default;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Renderer")` — Mode to indicate how clones facing is determined
- L127 _protected member_ `bool bMeshCastShadows = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetMeshCastShadows", Getter="GetMeshCastShadows", Category="Renderer")` — Whether clones cast shadow, disabling will result in better performance
- L131 _protected member_ `TArray<TObjectPtr<UStaticMesh>> DefaultMeshes;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Renderer")` — When nothing is attached to the cloner, these meshes are used as default
- L135 _protected member_ `bool bVisualizeEffectors = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetVisualizeEffectors", Getter="GetVisualizeEffectors", Category="Renderer")` — Override materials to show effectors applied on this cloner based on their color property
- L139 _protected member_ `bool bUseOverrideMaterial = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetUseOverrideMaterial", Getter="GetUseOverrideMaterial", Category="Renderer", meta=(RefreshPropertyView))` — Whether to override meshes materials with another material
- L143 _protected member_ `TObjectPtr<UMaterialInterface> OverrideMaterial;` — `UPROPERTY(EditAnywhere, Setter, Getter, Category="Renderer", meta=(EditCondition="bUseOverrideMaterial", EditConditionHides))` — The override materials that will be set instead of meshes materials, bVisualizeEffectors must be disabled
- L147 _protected member_ `bool bSortTranslucentParticles = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetSortTranslucentParticles", Getter="GetSortTranslucentParticles", Category="Renderer")` — Sort particles by depth when it has a translucent material, this will avoid flickering artifacts from appearing
- L152 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerMeshRendererExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerProgressExtension.h` (Public)


#### class `UCEClonerProgressExtension`  
`class UCEClonerProgressExtension : public UCEClonerExtensionBase`  
_L11-60_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Emission", Priority=100))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with clone progress options
- L16 _public prototype_ `UCEClonerProgressExtension();`
- L19 _public prototype_ `void SetInvertProgress(bool bInInvertProgress);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L22 _public function_ `bool GetInvertProgress() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L28 _public prototype_ `void SetProgress(float InProgress);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L31 _public function_ `float GetProgress() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L39 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L44 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L49 _protected member_ `bool bInvertProgress = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetInvertProgress", Getter="GetInvertProgress", Category="Progress")` — Invert progress behaviour
- L53 _protected member_ `float Progress = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Progress", meta=(ClampMin="0", ClampMax="1"))` — Changes visibility of instances based on the total count, 1.f = 100% = all instances visible
- L58 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerProgressExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerRangeExtension.h` (Public)


#### class `UCEClonerRangeExtension`  
`class UCEClonerRangeExtension : public UCEClonerExtensionBase`  
_L11-168_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Cloner", Priority=10))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with range options
- L16 _public prototype_ `UCEClonerRangeExtension();`
- L19 _public prototype_ `void SetRangeEnabled(bool bInRangeEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L22 _public function_ `bool GetRangeEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L28 _public prototype_ `void SetRangeMirrored(bool bInMirrored);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L31 _public function_ `bool GetRangeMirrored() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L37 _public prototype_ `void SetRangeOffsetMin(const FVector& InRangeOffsetMin);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L40 _public function_ `const FVector& GetRangeOffsetMin() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L46 _public prototype_ `void SetRangeOffsetMax(const FVector& InRangeOffsetMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L49 _public function_ `const FVector& GetRangeOffsetMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L55 _public prototype_ `void SetRangeRotationMin(const FRotator& InRangeRotationMin);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L58 _public function_ `const FRotator& GetRangeRotationMin() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L64 _public prototype_ `void SetRangeRotationMax(const FRotator& InRangeRotationMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L67 _public function_ `const FRotator& GetRangeRotationMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L73 _public prototype_ `void SetRangeScaleUniform(bool bInRangeScaleUniform);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L76 _public function_ `bool GetRangeScaleUniform() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L82 _public prototype_ `void SetRangeScaleMin(const FVector& InRangeScaleMin);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L85 _public function_ `const FVector& GetRangeScaleMin() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L91 _public prototype_ `void SetRangeScaleMax(const FVector& InRangeScaleMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L94 _public function_ `const FVector& GetRangeScaleMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L100 _public prototype_ `void SetRangeScaleUniformMin(float InRangeScaleUniformMin);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L103 _public function_ `float GetRangeScaleUniformMin() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L109 _public prototype_ `void SetRangeScaleUniformMax(float InRangeScaleUniformMax);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L112 _public function_ `float GetRangeScaleUniformMax() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L120 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L125 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L130 _protected member_ `bool bRangeEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetRangeEnabled", Getter="GetRangeEnabled", DisplayName="Enabled", Category="Range", meta=(RefreshPropertyView))` — Use random range transforms for each clones
- L134 _protected member_ `bool bRangeMirrored = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetRangeMirrored", Getter="GetRangeMirrored", DisplayName="Mirror Min & Max", Category="Range", meta=(EditCondition="bRangeEnabled", EditConditionHides, RefreshPropertyView))` — Mirrors max offset and rotation values in min offset and rotation
- L137 _protected member_ `FVector RangeOffsetMin = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="OffsetMin", Category="Range", meta=(EditCondition="bRangeEnabled && !bRangeMirrored", EditConditionHides))`
- L140 _protected member_ `FVector RangeOffsetMax = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="OffsetMax", Category="Range", meta=(EditCondition="bRangeEnabled", EditConditionHides))`
- L143 _protected member_ `FRotator RangeRotationMin = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="RotationMin", Category="Range", meta=(EditCondition="bRangeEnabled && !bRangeMirrored", EditConditionHides))`
- L146 _protected member_ `FRotator RangeRotationMax = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="RotationMax", Category="Range", meta=(EditCondition="bRangeEnabled", EditConditionHides))`
- L149 _protected member_ `bool bRangeScaleUniform = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetRangeScaleUniform", Getter="GetRangeScaleUniform", DisplayName="ScaleUniformEnabled", Category="Range", meta=(EditCondition="bRangeEnabled", EditConditionHides, RefreshPropertyView))`
- L152 _protected member_ `FVector RangeScaleMin = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="ScaleMin", Category="Range", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.0001", ClampMin="0", EditCondition="bRangeEnabled && !bRangeScaleUniform", EditConditionHides))`
- L155 _protected member_ `FVector RangeScaleMax = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="ScaleMax", Category="Range", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.0001", ClampMin="0", EditCondition="bRangeEnabled && !bRangeScaleUniform", EditConditionHides))`
- L158 _protected member_ `float RangeScaleUniformMin = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="ScaleMin", Category="Range", meta=(Delta="0.0001", ClampMin="0", EditCondition="bRangeEnabled && bRangeScaleUniform", EditConditionHides))`
- L161 _protected member_ `float RangeScaleUniformMax = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="ScaleMax", Category="Range", meta=(Delta="0.0001", ClampMin="0", EditCondition="bRangeEnabled && bRangeScaleUniform", EditConditionHides))`
- L166 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerRangeExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerStepExtension.h` (Public)


#### class `UCEClonerStepExtension`  
`class UCEClonerStepExtension : public UCEClonerExtensionBase`  
_L11-86_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Cloner", Priority=20))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with delta step accumulated options
- L16 _public prototype_ `UCEClonerStepExtension();`
- L19 _public prototype_ `void SetDeltaStepEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L22 _public function_ `bool GetDeltaStepEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L28 _public prototype_ `void SetDeltaStepPosition(const FVector& InPosition);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L31 _public function_ `FVector GetDeltaStepPosition() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L37 _public prototype_ `void SetDeltaStepRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L40 _public function_ `FRotator GetDeltaStepRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L46 _public prototype_ `void SetDeltaStepScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L49 _public function_ `FVector GetDeltaStepScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L57 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L62 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L67 _protected member_ `bool bDeltaStepEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetDeltaStepEnabled", Getter="GetDeltaStepEnabled", DisplayName="Enabled", Category="Step", meta=(RefreshPropertyView))` — Enable steps to add delta variation on each clone instance
- L71 _protected member_ `FVector DeltaStepPosition = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Position", Category="Step", meta=(EditCondition="bDeltaStepEnabled", EditConditionHides))` — Amount of position difference between one step and the next one
- L75 _protected member_ `FRotator DeltaStepRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Rotation", Category="Step", meta=(EditCondition="bDeltaStepEnabled", EditConditionHides))` — Amount of rotation difference between one step and the next one
- L79 _protected member_ `FVector DeltaStepScale = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Scale", Category="Step", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.0001", EditCondition="bDeltaStepEnabled", EditConditionHides))` — Amount of scale difference between one step and the next one
- L84 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerStepExtension> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Extensions/CEClonerTextureExtension.h` (Public)


#### enum `ECEClonerTextureProvider`  
`enum class ECEClonerTextureProvider : uint8`  
_L10-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `Constraint` — Use texture from constraint extension
- L15 _public enumerator_ `Displacement` — Use texture from displacement extension
- L17 _public enumerator_ `Custom` — Use custom texture

#### class `UCEClonerTextureExtension`  
`class UCEClonerTextureExtension : public UCEClonerExtensionBase`  
_L22-154_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEClonerComponent, meta=(Section="Cloner", Priority=60))`
- inherits: `UCEClonerExtensionBase`
- desc: Extension dealing with clone grid texture and UV for material
- L27 _public prototype_ `UCEClonerTextureExtension();`
- L30 _public prototype_ `void SetTextureEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L33 _public function_ `bool GetTextureEnabled() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L39 _public prototype_ `void SetTextureProvider(ECEClonerTextureProvider InProvider);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L42 _public function_ `ECEClonerTextureProvider GetTextureProvider() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L48 _public prototype_ `void SetCustomTextureAsset(UTexture* InTexture);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L51 _public function_ `UTexture* GetCustomTextureAsset() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L57 _public prototype_ `void SetTextureUVProvider(ECEClonerTextureProvider InProvider);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L60 _public function_ `ECEClonerTextureProvider GetTextureUVProvider() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L66 _public prototype_ `void SetCustomTextureUVPlane(ECEClonerPlane InPlane);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L69 _public function_ `ECEClonerPlane GetCustomTextureUVPlane() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L75 _public prototype_ `void SetCustomTextureUVOffset(const FVector2D& InOffset);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L78 _public function_ `FVector2D GetCustomTextureUVOffset() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L84 _public prototype_ `void SetCustomTextureUVRotation(float InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L87 _public function_ `float GetCustomTextureUVRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L93 _public prototype_ `void SetCustomTextureUVScale(const FVector2D& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L96 _public function_ `FVector2D GetCustomTextureUVScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L102 _public prototype_ `void SetCustomTextureUVClamp(bool bInClamp);` — `UFUNCTION(BlueprintCallable, Category="Cloner")`
- L105 _public function_ `bool GetCustomTextureUVClamp() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L113 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L118 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEClonerComponent* InComponent) override;`
- L119 _protected prototype_ `virtual bool IsLayoutSupported(const UCEClonerLayoutBase* InLayout) const override;`
- L120 _protected prototype_ `virtual void OnExtensionDirtied(const UCEClonerExtensionBase* InExtension) override;`
- L124 _protected member_ `bool bTextureEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetTextureEnabled", Getter="GetTextureEnabled", DisplayName="Enabled", Category="Texture", meta=(RefreshPropertyView))`
- L127 _protected member_ `ECEClonerTextureProvider TextureProvider = ECEClonerTextureProvider::Constraint;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Texture Provider", Category="Texture", meta=(EditCondition="bTextureEnabled", EditConditionHides, RefreshPropertyView))`
- L130 _protected member_ `TObjectPtr<UTexture> CustomTextureAsset;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Texture Asset", Category="Texture", meta=(EditCondition="bTextureEnabled && TextureProvider == ECEClonerTextureProvider::Custom", EditConditionHides))`
- L133 _protected member_ `ECEClonerTextureProvider TextureUVProvider = ECEClonerTextureProvider::Constraint;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Texture UV Provider", Category="Texture", meta=(EditCondition="bTextureEnabled", EditConditionHides))`
- L136 _protected member_ `ECEClonerPlane CustomTextureUVPlane = ECEClonerPlane::XY;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Texture UV Plane", Category="Texture", meta=(InvalidEnumValues="Custom", EditCondition="bTextureEnabled && TextureUVProvider == ECEClonerTextureProvider::Custom", EditConditionHides))`
- L139 _protected member_ `FVector2D CustomTextureUVOffset = FVector2D::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Texture UV Offset", Category="Texture", meta=(EditCondition="bTextureEnabled && TextureUVProvider == ECEClonerTextureProvider::Custom", EditConditionHides))`
- L142 _protected member_ `float CustomTextureUVRotation = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Texture UV Rotation", Category="Texture", meta=(EditCondition="bTextureEnabled && TextureUVProvider == ECEClonerTextureProvider::Custom", EditConditionHides))`
- L145 _protected member_ `FVector2D CustomTextureUVScale = FVector2D(1.0);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Texture UV Scale", Category="Texture", meta=(Delta="0.01", MotionDesignVectorWidget, AllowPreserveRatio="XY", EditCondition="bTextureEnabled && TextureUVProvider == ECEClonerTextureProvider::Custom", EditConditionHides))`
- L148 _protected member_ `bool bCustomTextureUVClamp = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetCustomTextureUVClamp", Getter="GetCustomTextureUVClamp", DisplayName="Texture UV Clamp", Category="Texture", meta=(EditCondition="bTextureEnabled && TextureUVProvider == ECEClonerTextureProvider::Custom", EditConditionHides))`
- L152 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerTextureExtension> PropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerCircleLayout.h` (Public)


#### class `UCEClonerCircleLayout`  
`class UCEClonerCircleLayout : public UCEClonerLayoutBase`  
_L11-149_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L18 _public function_ `UCEClonerCircleLayout() : UCEClonerLayoutBase( TEXT("Circle") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerCircle.NS_ClonerCircle'") )`
- L26 _public prototype_ `void SetCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L29 _public function_ `int32 GetCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L35 _public prototype_ `void SetRingCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L38 _public function_ `int32 GetRingCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L44 _public prototype_ `void SetRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L47 _public function_ `float GetRadius() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L53 _public prototype_ `void SetAngleStart(float InAngleStart);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L56 _public function_ `float GetAngleStart() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L62 _public prototype_ `void SetAngleRatio(float InAngleRatio);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L65 _public function_ `float GetAngleRatio() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L71 _public prototype_ `void SetOrientMesh(bool bInOrientMesh);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L74 _public function_ `bool GetOrientMesh() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L80 _public prototype_ `void SetPlane(ECEClonerPlane InPlane);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L83 _public function_ `ECEClonerPlane GetPlane() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L89 _public prototype_ `void SetRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L92 _public function_ `const FRotator& GetRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L98 _public prototype_ `void SetScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Circle")`
- L101 _public function_ `const FVector& GetScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Circle")`
- L109 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L114 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L118 _protected member_ `int32 Count = 3 * 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L121 _protected member_ `int32 RingCount = 1;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="1"))`
- L124 _protected member_ `float Radius = 200.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L127 _protected member_ `float AngleStart = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L130 _protected member_ `float AngleRatio = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L133 _protected member_ `bool bOrientMesh = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrientMesh", Getter="GetOrientMesh", Category="Layout")`
- L136 _protected member_ `ECEClonerPlane Plane = ECEClonerPlane::XY;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(RefreshPropertyView))`
- L139 _protected member_ `FRotator Rotation = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(EditCondition="Plane == ECEClonerPlane::Custom", EditConditionHides))`
- L142 _protected member_ `FVector Scale = FVector(1.f, 1.f, 1.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.01"))`
- L147 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerCircleLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerCylinderLayout.h` (Public)


#### class `UCEClonerCylinderLayout`  
`class UCEClonerCylinderLayout : public UCEClonerLayoutBase`  
_L11-161_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L18 _public function_ `UCEClonerCylinderLayout() : UCEClonerLayoutBase( TEXT("Cylinder") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerCylinder.NS_ClonerCylinder'") )`
- L26 _public prototype_ `void SetBaseCount(int32 InBaseCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L29 _public function_ `int32 GetBaseCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L35 _public prototype_ `void SetHeightCount(int32 InHeightCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L38 _public function_ `int32 GetHeightCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L44 _public prototype_ `void SetHeight(float InHeight);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L47 _public function_ `float GetHeight() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L53 _public prototype_ `void SetRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L56 _public function_ `float GetRadius() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L62 _public prototype_ `void SetAngleStart(float InAngleStart);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L65 _public function_ `float GetAngleStart() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L71 _public prototype_ `void SetAngleRatio(float InAngleRatio);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L74 _public function_ `float GetAngleRatio() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L80 _public prototype_ `void SetOrientMesh(bool bInOrientMesh);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L83 _public function_ `bool GetOrientMesh() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L89 _public prototype_ `void SetPlane(ECEClonerPlane InPlane);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L92 _public function_ `ECEClonerPlane GetPlane() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L98 _public prototype_ `void SetRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L101 _public function_ `const FRotator& GetRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L107 _public prototype_ `void SetScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Cylinder")`
- L110 _public function_ `const FVector& GetScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Cylinder")`
- L118 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L123 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L127 _protected member_ `int32 BaseCount = 3 * 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L130 _protected member_ `int32 HeightCount = 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L133 _protected member_ `float Height = 400.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L136 _protected member_ `float Radius = 200.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L139 _protected member_ `float AngleStart = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L142 _protected member_ `float AngleRatio = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L145 _protected member_ `bool bOrientMesh = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrientMesh", Getter="GetOrientMesh", Category="Layout")`
- L148 _protected member_ `ECEClonerPlane Plane = ECEClonerPlane::XY;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(RefreshPropertyView))`
- L151 _protected member_ `FRotator Rotation = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(EditCondition="Plane == ECEClonerPlane::Custom", EditConditionHides))`
- L154 _protected member_ `FVector Scale = FVector(1.f, 1.f, 1.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.01"))`
- L159 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerCylinderLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerFreePlacementLayout.h` (Public)


#### class `UCEClonerFreePlacementLayout`  
`class UCEClonerFreePlacementLayout : public UCEClonerLayoutBase`  
_L11-52_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L16 _public function_ `UCEClonerFreePlacementLayout() : UCEClonerLayoutBase( TEXT("FreePlacement") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerFreePlacement.NS_ClonerFreePlacement'") )`
- L26 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L31 _protected prototype_ `virtual void OnLayoutActive() override;`
- L32 _protected prototype_ `virtual void OnLayoutInactive() override;`
- L33 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L36 _protected prototype_ `void OnClonerMeshUpdated(UCEClonerComponent* InClonerComponent);`
- L39 _protected prototype_ `void OnClonerActorAttached(UCEClonerComponent* InClonerComponent, AActor* InActor);`
- L40 _protected prototype_ `void OnClonerActorDetached(UCEClonerComponent* InClonerComponent, AActor* InActor);`
- L41 _protected prototype_ `void ApplyComponentsSettings();`
- L42 _protected prototype_ `void RestoreComponentsSettings();`
- L43 _protected prototype_ `void ApplyComponentsSettings(AActor* InActor);`
- L44 _protected prototype_ `void RestoreComponentsSettings(AActor* InActor);`
- L50 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerFreePlacementLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerGridLayout.h` (Public)


#### class `UCEClonerGridLayout`  
`class UCEClonerGridLayout : public UCEClonerLayoutBase`  
_L11-186_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L18 _public function_ `UCEClonerGridLayout() : UCEClonerLayoutBase( TEXT("Grid") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerGrid.NS_ClonerGrid'") )`
- L26 _public prototype_ `void SetCountX(int32 InCountX);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L29 _public function_ `int32 GetCountX() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L35 _public prototype_ `void SetCountY(int32 InCountY);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L38 _public function_ `int32 GetCountY() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L44 _public prototype_ `void SetCountZ(int32 InCountZ);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L47 _public function_ `int32 GetCountZ() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L53 _public prototype_ `void SetSpacingX(float InSpacingX);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L56 _public function_ `float GetSpacingX() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L62 _public prototype_ `void SetSpacingY(float InSpacingY);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L65 _public function_ `float GetSpacingY() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L71 _public prototype_ `void SetSpacingZ(float InSpacingZ);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L74 _public function_ `float GetSpacingZ() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L80 _public prototype_ `void SetTwistFactor(float InFactor);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L83 _public function_ `float GetTwistFactor() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L89 _public prototype_ `void SetTwistAxis(ECEClonerAxis InAxis);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Grid")`
- L92 _public function_ `ECEClonerAxis GetTwistAxis() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Grid")`
- L99 _public function_ `ECEClonerGridConstraint GetConstraint() const`
- L104 _public function_ `bool GetInvertConstraint() const`
- L109 _public function_ `const FCEClonerGridConstraintSphere& GetSphereConstraint() const`
- L114 _public function_ `const FCEClonerGridConstraintCylinder& GetCylinderConstraint() const`
- L119 _public function_ `const FCEClonerGridConstraintTexture& GetTextureConstraint() const`
- L129 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L134 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L138 _protected member_ `int32 CountX = 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L141 _protected member_ `int32 CountY = 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L144 _protected member_ `int32 CountZ = 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L147 _protected member_ `float SpacingX = 105.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L150 _protected member_ `float SpacingY = 105.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L153 _protected member_ `float SpacingZ = 105.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L156 _protected member_ `float TwistFactor = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(UIMin="0", UIMax="100"))`
- L159 _protected member_ `ECEClonerAxis TwistAxis = ECEClonerAxis::Y;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(InvalidEnumValues="Custom"))`
- L164 _private member_ `ECEClonerGridConstraint Constraint = ECEClonerGridConstraint::None;` — `UE_DEPRECATED(5.5, "Moved to constraint extension")` — `UPROPERTY()`
- L168 _private member_ `bool bInvertConstraint = false;` — `UE_DEPRECATED(5.5, "Moved to constraint extension")` — `UPROPERTY()`
- L172 _private member_ `FCEClonerGridConstraintSphere SphereConstraint;` — `UE_DEPRECATED(5.5, "Moved to constraint extension")` — `UPROPERTY()`
- L176 _private member_ `FCEClonerGridConstraintCylinder CylinderConstraint;` — `UE_DEPRECATED(5.5, "Moved to constraint extension")` — `UPROPERTY()`
- L180 _private member_ `FCEClonerGridConstraintTexture TextureConstraint;` — `UE_DEPRECATED(5.5, "Moved to constraint extension")` — `UPROPERTY()`
- L184 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerGridLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerHoneycombLayout.h` (Public)


#### class `UCEClonerHoneycombLayout`  
`class UCEClonerHoneycombLayout : public UCEClonerLayoutBase`  
_L11-151_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L18 _public function_ `UCEClonerHoneycombLayout() : UCEClonerLayoutBase( TEXT("Honeycomb") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerHoneycomb.NS_ClonerHoneycomb'") )`
- L26 _public prototype_ `void SetPlane(ECEClonerPlane InPlane);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L29 _public function_ `ECEClonerPlane GetPlane() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L35 _public prototype_ `void SetWidthCount(int32 InWidthCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L38 _public function_ `int32 GetWidthCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L44 _public prototype_ `void SetHeightCount(int32 InHeightCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L47 _public function_ `int32 GetHeightCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L53 _public prototype_ `void SetWidthOffset(float InWidthOffset);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L56 _public function_ `float GetWidthOffset() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L62 _public prototype_ `void SetHeightOffset(float InHeightOffset);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L65 _public function_ `float GetHeightOffset() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L71 _public prototype_ `void SetHeightSpacing(float InHeightSpacing);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L74 _public function_ `float GetHeightSpacing() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L80 _public prototype_ `void SetWidthSpacing(float InWidthSpacing);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L83 _public function_ `float GetWidthSpacing() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L89 _public prototype_ `void SetTwistFactor(float InFactor);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L92 _public function_ `float GetTwistFactor() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L98 _public prototype_ `void SetTwistAxis(ECEClonerAxis InAxis);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Honeycomb")`
- L101 _public function_ `ECEClonerAxis GetTwistAxis() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Honeycomb")`
- L109 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L113 _protected prototype_ `void OnTwistAxisChanged();`
- L116 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L120 _protected member_ `ECEClonerPlane Plane = ECEClonerPlane::XY;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(InvalidEnumValues="Custom"))`
- L123 _protected member_ `int32 WidthCount = 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L126 _protected member_ `int32 HeightCount = 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L129 _protected member_ `float WidthOffset = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L132 _protected member_ `float HeightOffset = 0.5f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L135 _protected member_ `float WidthSpacing = 105.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L138 _protected member_ `float HeightSpacing = 105.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L141 _protected member_ `float TwistFactor = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(UIMin="0", UIMax="100"))`
- L144 _protected member_ `ECEClonerAxis TwistAxis = ECEClonerAxis::Y;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(InvalidEnumValues="Custom"))`
- L149 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerHoneycombLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerLayoutBase.h` (Public)


#### class `UCEClonerLayoutBase`  
`class UCEClonerLayoutBase : public UObject`  
_L24-194_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, AutoExpandCategories=("Layout"))`
- inherits: `UObject`
- desc: Base class for layouts available in the cloner actor Steps to add a new layout : 1. Create a new system that extends from NS_ClonerBase and expose all the parent parameters (examples can be found in Content) 2. Extend this layout class and give it a unique name with the newly created system path 3. Expose all new system specific parameters in the layout extended class and update them when required Your new layout is ready and will be available in the cloner in the layout dropdown
- L31 _public member_ `static constexpr TCHAR LayoutBaseAssetPath[] = TEXT("/Sc`
- L33 _public function_ `UCEClonerLayoutBase() : UCEClonerLayoutBase(NAME_None, FString())`
- L37 _public function_ `UCEClonerLayoutBase(const FName& InLayoutName, const FString& InLayoutAssetPath) : LayoutName(InLayoutName) , LayoutAssetPath(InLayoutAssetPath)`
- L43 _public function_ `FName GetLayoutName() const` — `UFUNCTION(BlueprintPure, Category="Cloner")`
- L48 _public function_ `const FString& GetLayoutAssetPath() const`
- L53 _public function_ `UNiagaraSystem* GetSystem() const`
- L58 _public function_ `UNiagaraMeshRendererProperties* GetMeshRenderer() const`
- L63 _public function_ `FOnClonerLayoutLoaded::RegistrationType& OnLayoutLoadedDelegate()`
- L69 _public prototype_ `UCEClonerComponent* GetClonerComponent() const;` — Get the cloner component using this layout
- L72 _public prototype_ `AActor* GetClonerActor() const;` — Get the actor using this layout
- L75 _public prototype_ `void UpdateLayoutParameters();` — Updates all parameters handled by this layout
- L78 _public prototype_ `bool IsLayoutValid() const;` — Checks if the niagara system asset is valid and usable with the cloner
- L81 _public prototype_ `bool IsLayoutLoaded() const;` — Is this layout system cached and ready to be used
- L84 _public prototype_ `void LoadLayout();` — Load this layout system if not already loaded
- L87 _public prototype_ `bool UnloadLayout();` — Free the loaded system and return to idle state
- L91 _public prototype_ `bool IsLayoutActive() const;` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout")` — Is this layout system in use within the cloner
- L94 _public prototype_ `bool ActivateLayout();` — Activate this layout system on the cloner, must be loaded first
- L97 _public prototype_ `bool DeactivateLayout();` — Deactivate this layout system if active
- L100 _public prototype_ `TSet<TSubclassOf<UCEClonerExtensionBase>> GetSupportedExtensions() const;` — Gets the cloner extensions supported by this layout
- L103 _public function_ `virtual bool IsExtensionSupported(const UCEClonerExtensionBase* InExtension) const` — Filter supported extension for this layout
- L109 _public prototype_ `void MarkLayoutDirty(bool bInUpdateCloner = true);` — Request refresh layout next tick
- L112 _public prototype_ `bool IsLayoutDirty() const;` — Is the cloner not up to date with layout parameters
- L116 _protected prototype_ `virtual void PostEditImport() override;`
- L117 _protected prototype_ `virtual void PostLoad() override;`
- L119 _protected prototype_ `virtual void PostEditUndo() override;`
- L124 _protected function_ `virtual void OnLayoutLoaded()` — Called once after layout is loaded
- L127 _protected function_ `virtual void OnLayoutUnloaded()` — Called once after layout is unloaded
- L130 _protected function_ `virtual void OnLayoutActive()` — Called after layout becomes active
- L133 _protected function_ `virtual void OnLayoutInactive()` — Called after layout becomes inactive
- L136 _protected function_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent)` — Called to reapply layout parameters
- L138 _protected prototype_ `void OnLayoutPropertyChanged();`
- L141 _private member_ `FOnClonerLayoutLoaded OnClonerLayoutLoadedDelegate;`
- L144 _private prototype_ `void OnSystemPackageLoaded(const FName& InName, UPackage* InPackage, EAsyncLoadingResult::Type InResult);` — Called when the system package was async loaded
- L145 _private prototype_ `void OnSystemLoaded();`
- L148 _private prototype_ `void CacheMeshRenderer();` — Finds and cache first mesh renderer in emitter
- L151 _private prototype_ `void BindCleanupDelegates();` — Bind delegates to clear resources during level or world cleanup
- L152 _private prototype_ `void UnbindCleanupDelegates() const;`
- L155 _private prototype_ `void OnWorldCleanup(UWorld* InWorld, bool bInSessionEnded, bool bInCleanupResources);` — When level is unloaded or world cleaned up, deactivate and unload layout
- L156 _private prototype_ `void OnLevelCleanup();`
- L159 _private prototype_ `void CleanOwnedSystem() const;` — Marks niagara system owned by this layout garbage to avoid GC leak
- L163 _private prototype_ `FString GetLayoutHash() const;` — Get the niagara system package hash
- L167 _private prototype_ `bool IsSystemHashMatching() const;` — Checks if cached hash matches package hash
- L171 _private member_ `FName LayoutName;` — `UPROPERTY(Transient)` — Layout name to display in layout options
- L175 _private member_ `FString LayoutAssetPath;` — `UPROPERTY(Transient)` — Niagara System asset path for this layout
- L179 _private member_ `TObjectPtr<UNiagaraSystem> NiagaraSystem;` — `UPROPERTY(DuplicateTransient, TextExportTransient)` — Niagara system used for this layout, cached to save some time
- L183 _private member_ `TObjectPtr<UNiagaraMeshRendererProperties> MeshRenderer;` — `UPROPERTY(Transient, DuplicateTransient, TextExportTransient)` — Mesh renderer in this niagara system
- L187 _private member_ `FString CachedSystemHash;` — `UPROPERTY(DuplicateTransient, TextExportTransient)` — Hash of the cached system for diffs
- L190 _private member_ `int32 LoadRequestIdentifier = INDEX_NONE;` — Id for the load request initiated
- L193 _private member_ `ECEClonerSystemStatus LayoutStatus = ECEClonerSystemStatus::UpToDate;` — Status for this layout

#### Free symbols / members of external scopes

- L28 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnClonerLayoutLoaded, UCEClonerLayoutBase* , bool ) public: static constexpr TCHAR LayoutBaseAssetPath[] = TEXT("/Sc`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerLineLayout.h` (Public)


#### class `UCEClonerLineLayout`  
`class UCEClonerLineLayout : public UCEClonerLayoutBase`  
_L11-101_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L18 _public function_ `UCEClonerLineLayout() : UCEClonerLayoutBase( TEXT("Line") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerLine.NS_ClonerLine'") )`
- L26 _public prototype_ `void SetCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Line")`
- L29 _public function_ `int32 GetCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Line")`
- L35 _public prototype_ `void SetSpacing(float InSpacing);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Line")`
- L38 _public function_ `float GetSpacing() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Line")`
- L44 _public prototype_ `void SetAxis(ECEClonerAxis InAxis);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Line")`
- L47 _public function_ `ECEClonerAxis GetAxis() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Line")`
- L53 _public prototype_ `void SetDirection(const FVector& InDirection);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Line")`
- L56 _public function_ `const FVector& GetDirection() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Line")`
- L62 _public prototype_ `void SetRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Line")`
- L65 _public function_ `const FRotator& GetRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Line")`
- L73 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L78 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L82 _protected member_ `int32 Count = 10;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L85 _protected member_ `float Spacing = 105.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L88 _protected member_ `ECEClonerAxis Axis = ECEClonerAxis::Y;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(RefreshPropertyView))`
- L91 _protected member_ `FVector Direction = FVector::YAxisVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", ClampMax="1", EditCondition="Axis == ECEClonerAxis::Custom", EditConditionHides))`
- L94 _protected member_ `FRotator Rotation = FRotator(0.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L99 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerLineLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerMeshLayout.h` (Public)


#### class `UCEClonerMeshLayout`  
`class UCEClonerMeshLayout : public UCEClonerLayoutBase`  
_L15-112_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L23 _public prototype_ `static FName GetSampleActorWeakName();`
- L24 _public prototype_ `static FName GetAssetName();`
- L27 _public function_ `UCEClonerMeshLayout() : UCEClonerLayoutBase( TEXT("Mesh") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerSampleMesh.NS_ClonerSampleMesh'") )`
- L35 _public prototype_ `void SetCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Mesh")`
- L38 _public function_ `int32 GetCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Mesh")`
- L44 _public prototype_ `void SetAsset(ECEClonerMeshAsset InAsset);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Mesh")`
- L47 _public function_ `ECEClonerMeshAsset GetAsset() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Mesh")`
- L53 _public prototype_ `void SetSampleData(ECEClonerMeshSampleData InSampleData);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Mesh")`
- L56 _public function_ `ECEClonerMeshSampleData GetSampleData() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Mesh")`
- L62 _public prototype_ `void SetSampleActorWeak(const TWeakObjectPtr<AActor>& InSampleActor);` — `UFUNCTION()`
- L64 _public function_ `TWeakObjectPtr<AActor> GetSampleActorWeak() const`
- L70 _public prototype_ `void SetSampleActor(AActor* InActor);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Mesh")`
- L73 _public function_ `AActor* GetSampleActor() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Mesh")`
- L81 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L86 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L90 _protected prototype_ `void OnSampleActorDestroyed(AActor* InDestroyedActor);` — `UFUNCTION()`
- L93 _protected member_ `ECEClonerMeshAsset Asset = ECEClonerMeshAsset::StaticMesh;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L96 _protected member_ `TWeakObjectPtr<AActor> SampleActorWeak;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Sample Actor", Category="Layout", meta=(DisplayAfter="Asset"))`
- L99 _protected member_ `int32 Count = 3 * 3 * 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L102 _protected member_ `ECEClonerMeshSampleData SampleData = ECEClonerMeshSampleData::Vertices;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L106 _private member_ `TWeakObjectPtr<USceneComponent> SceneComponentWeak;` — `UPROPERTY(Transient)`
- L110 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerMeshLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerSphereRandomLayout.h` (Public)


#### class `UCEClonerSphereRandomLayout`  
`class UCEClonerSphereRandomLayout : public UCEClonerLayoutBase`  
_L10-136_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L17 _public function_ `UCEClonerSphereRandomLayout() : UCEClonerLayoutBase( TEXT("SphereRandom") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerSphereRandom.NS_ClonerSphereRandom'") )`
- L25 _public prototype_ `void SetCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L28 _public function_ `int32 GetCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L34 _public prototype_ `void SetRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L37 _public function_ `float GetRadius() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L43 _public prototype_ `void SetDistribution(float InDistribution);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L46 _public function_ `float GetDistribution() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L52 _public prototype_ `void SetLongitude(float InLongitude);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L55 _public function_ `float GetLongitude() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L61 _public prototype_ `void SetLatitude(float InLatitude);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L64 _public function_ `float GetLatitude() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L70 _public prototype_ `void SetOrientMesh(bool InbOrientMesh);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L73 _public function_ `bool GetOrientMesh() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L79 _public prototype_ `void SetRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L82 _public function_ `FRotator GetRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L88 _public prototype_ `void SetScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereRandom")`
- L91 _public function_ `FVector GetScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereRandom")`
- L99 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L104 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L108 _protected member_ `int32 Count = 30;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L111 _protected member_ `float Radius = 200.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L114 _protected member_ `float Distribution = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", ClampMax="1"))`
- L117 _protected member_ `float Longitude = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", ClampMax="1"))`
- L120 _protected member_ `float Latitude = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", ClampMax="1"))`
- L123 _protected member_ `bool bOrientMesh = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrientMesh", Getter="GetOrientMesh", Category="Layout")`
- L126 _protected member_ `FRotator Rotation = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L129 _protected member_ `FVector Scale = FVector(1.f, 1.f, 1.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.01"))`
- L134 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerSphereRandomLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerSphereUniformLayout.h` (Public)


#### class `UCEClonerSphereUniformLayout`  
`class UCEClonerSphereUniformLayout : public UCEClonerLayoutBase`  
_L10-112_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L17 _public function_ `UCEClonerSphereUniformLayout() : UCEClonerLayoutBase( TEXT("SphereUniform") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerSphere.NS_ClonerSphere'") )`
- L25 _public prototype_ `void SetCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereUniform")`
- L28 _public function_ `int32 GetCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereUniform")`
- L34 _public prototype_ `void SetRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereUniform")`
- L37 _public function_ `float GetRadius() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereUniform")`
- L43 _public prototype_ `void SetRatio(float InRatio);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereUniform")`
- L46 _public function_ `float GetRatio() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereUniform")`
- L52 _public prototype_ `void SetOrientMesh(bool InbOrientMesh);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereUniform")`
- L55 _public function_ `bool GetOrientMesh() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereUniform")`
- L61 _public prototype_ `void SetRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereUniform")`
- L64 _public function_ `FRotator GetRotation() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereUniform")`
- L70 _public prototype_ `void SetScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|SphereUniform")`
- L73 _public function_ `FVector GetScale() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|SphereUniform")`
- L81 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L86 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L90 _protected member_ `int32 Count = 30;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L93 _protected member_ `float Radius = 200.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L96 _protected member_ `float Ratio = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", ClampMax="1"))`
- L99 _protected member_ `bool bOrientMesh = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrientMesh", Getter="GetOrientMesh", Category="Layout")`
- L102 _protected member_ `FRotator Rotation = FRotator(0.f, 0.f, 0.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L105 _protected member_ `FVector Scale = FVector(1.f, 1.f, 1.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.01"))`
- L110 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerSphereUniformLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Cloner/Layouts/CEClonerSplineLayout.h` (Public)


#### class `UCEClonerSplineLayout`  
`class UCEClonerSplineLayout : public UCEClonerLayoutBase`  
_L14-105_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UCEClonerLayoutBase`
- L22 _public prototype_ `static FName GetSplineActorWeakName();`
- L25 _public function_ `UCEClonerSplineLayout() : UCEClonerLayoutBase( TEXT("Spline") , TEXT("/Script/Niagara.NiagaraSystem'/ClonerEffector/Systems/NS_ClonerSampleSpline.NS_ClonerSampleSpline'") )`
- L33 _public prototype_ `void SetCount(int32 InCount);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Spline")`
- L36 _public function_ `int32 GetCount() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Spline")`
- L42 _public prototype_ `void SetSplineActorWeak(const TWeakObjectPtr<AActor>& InSplineActor);` — `UFUNCTION()`
- L44 _public function_ `TWeakObjectPtr<AActor> GetSplineActorWeak() const`
- L50 _public prototype_ `void SetSplineActor(AActor* InSplineActor);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Spline")`
- L53 _public function_ `AActor* GetSplineActor() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Spline")`
- L59 _public prototype_ `void SetOrientMesh(bool bInOrientMesh);` — `UFUNCTION(BlueprintCallable, Category="Cloner|Layout|Spline")`
- L62 _public function_ `bool GetOrientMesh() const` — `UFUNCTION(BlueprintPure, Category="Cloner|Layout|Spline")`
- L70 _public prototype_ `void SpawnLinkedSplineActor();` — `UFUNCTION(CallInEditor, Category="Layout")` — Spawns an actor with a spline component and linked it to this cloner layout
- L76 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L81 _protected prototype_ `virtual void OnLayoutActive() override;`
- L82 _protected prototype_ `virtual void OnLayoutInactive() override;`
- L83 _protected prototype_ `virtual void OnLayoutParametersChanged(UCEClonerComponent* InComponent) override;`
- L86 _protected prototype_ `void OnSampleSplineRenderStateUpdated(UActorComponent& InComponent);`
- L89 _protected member_ `int32 Count = 3 * 3;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Layout")`
- L92 _protected member_ `TWeakObjectPtr<AActor> SplineActorWeak;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="SampleActor", Category="Layout")`
- L95 _protected member_ `bool bOrientMesh = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrientMesh", Getter="GetOrientMesh", Category="Layout")`
- L99 _private prototype_ `void OnSampleSplineDestroyed(AActor* InDestroyedActor);` — `UFUNCTION()`
- L103 _private member_ `static const TCEPropertyChangeDispatcher<UCEClonerSplineLayout> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/CEEffectorActor.h` (Public)


#### class `ACEEffectorActor`  
`class ACEEffectorActor : public AActor`  
_L18-248_
- reflection: `UCLASS(MinimalAPI , BlueprintType , HideCategories=(Rendering,Replication,Collision,HLOD,Physics,Networking,Input,Actor,Cooking,LevelInstance,DataLayers,WorldPartition) , DisplayName = "Motion Design Effector Actor")`
- inherits: `AActor`
- L28 _public member_ `static inline const FString DefaultLabel = TEXT("Eff`
- L30 _public prototype_ `ACEEffectorActor();`
- L33 _public function_ `UCEEffectorComponent* GetEffectorComponent() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L40 _public prototype_ `virtual FString GetDefaultActorLabel() const override;`
- L46 _protected prototype_ `virtual void Serialize(FArchive& InArchive) override;`
- L47 _protected prototype_ `virtual void PostLoad() override;`
- L51 _private prototype_ `void MigrateDeprecatedProperties();`
- L52 _private prototype_ `void RegisterToChannel() const;`
- L55 _private member_ `TObjectPtr<UCEEffectorComponent> EffectorComponent;` — `UPROPERTY(VisibleInstanceOnly, Category="Effector")`
- L57 _private member_ `int32 MigrateToVersion = INDEX_NONE;`
- L61 _private member_ `bool bEnabled = true;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L65 _private member_ `float Magnitude = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L69 _private member_ `FLinearColor Color = FLinearColor::Red;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L73 _private member_ `ECEClonerEffectorType Type = ECEClonerEffectorType::Sphere;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L77 _private member_ `bool bInvertType = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L81 _private member_ `ECEClonerEasing Easing = ECEClonerEasing::Linear;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L85 _private member_ `float InnerRadius = 50.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L89 _private member_ `float OuterRadius = 200.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L93 _private member_ `FVector InnerExtent = FVector(50.f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L97 _private member_ `FVector OuterExtent = FVector(200.f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L101 _private member_ `float PlaneSpacing = 200.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L105 _private member_ `float RadialAngle = 180.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L109 _private member_ `float RadialMinRadius = 0.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L113 _private member_ `float RadialMaxRadius = 1000.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L117 _private member_ `float TorusRadius = 250.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L121 _private member_ `float TorusInnerRadius = 50.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L125 _private member_ `float TorusOuterRadius = 200.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L129 _private member_ `ECEClonerEffectorMode Mode = ECEClonerEffectorMode::Default;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L133 _private member_ `FVector Offset = FVector::ZeroVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L137 _private member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L141 _private member_ `FVector Scale = FVector::OneVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L145 _private member_ `TWeakObjectPtr<AActor> TargetActorWeak = nullptr;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L149 _private member_ `TWeakObjectPtr<AActor> InternalTargetActorWeak = nullptr;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L153 _private member_ `FVector LocationStrength = FVector::ZeroVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L157 _private member_ `FRotator RotationStrength = FRotator::ZeroRotator;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L161 _private member_ `FVector ScaleStrength = FVector::OneVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L165 _private member_ `FVector Pan = FVector::ZeroVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L169 _private member_ `float Frequency = 0.5f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L173 _private member_ `FVector PushStrength = FVector(100.f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L177 _private member_ `ECEClonerEffectorPushDirection PushDirection = ECEClonerEffectorPushDirection::Forward;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L181 _private member_ `bool bOrientationForceEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L185 _private member_ `float OrientationForceRate = 1.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L189 _private member_ `FVector OrientationForceMin = FVector(-0.1f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L193 _private member_ `FVector OrientationForceMax = FVector(0.1f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L197 _private member_ `bool bVortexForceEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L201 _private member_ `float VortexForceAmount = 10000.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L205 _private member_ `FVector VortexForceAxis = FVector::ZAxisVector;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L209 _private member_ `bool bCurlNoiseForceEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L213 _private member_ `float CurlNoiseForceStrength = 1000.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L217 _private member_ `float CurlNoiseForceFrequency = 10.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L221 _private member_ `bool bAttractionForceEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L225 _private member_ `float AttractionForceStrength = 1000.f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L229 _private member_ `float AttractionForceFalloff = 0.1f;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L233 _private member_ `bool bGravityForceEnabled = false;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L237 _private member_ `FVector GravityForceAcceleration = FVector(0, 0, -980.f);` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L242 _private member_ `bool bVisualizerComponentVisible = true;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`
- L246 _private member_ `bool bVisualizerSpriteVisible = true;` — `UE_DEPRECATED(5.5, "Moved to component and extensions")` — `UPROPERTY()`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/CEEffectorComponent.h` (Public)


#### class `UCEEffectorComponent`  
`class UCEEffectorComponent : public USceneComponent`  
_L26-316_
- reflection: `UCLASS(MinimalAPI , BlueprintType , HideCategories=(Tags,Activation,LOD,AssetUserData,Navigation,Rendering,Cooking,Physics,WorldPartition) , DisplayName = "Motion Design Effector Component" , meta=(BlueprintSpawnableComponent))`
- inherits: `USceneComponent`
- desc: Class used to define an effector
- L36 _public prototype_ `static FName GetModeNamePropertyName();`
- L38 _public prototype_ `static FName GetTypeNamePropertyName();`
- L41 _public prototype_ `UCEEffectorComponent();`
- L44 _public prototype_ `void SetEnabled(bool bInEnable);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L47 _public function_ `bool GetEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L53 _public prototype_ `void SetColor(const FLinearColor& InColor);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L56 _public function_ `const FLinearColor& GetColor() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L62 _public prototype_ `void SetMagnitude(float InMagnitude);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L65 _public function_ `float GetMagnitude() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L71 _public prototype_ `void SetTypeName(FName InTypeName);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L74 _public function_ `FName GetTypeName() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L80 _public prototype_ `void SetTypeClass(TSubclassOf<UCEEffectorTypeBase> InTypeClass);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L83 _public prototype_ `TSubclassOf<UCEEffectorTypeBase> GetTypeClass() const;` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L86 _public prototype_ `void SetModeName(FName InModeName);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L89 _public function_ `FName GetModeName() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L95 _public prototype_ `void SetModeClass(TSubclassOf<UCEEffectorModeBase> InModeClass);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L98 _public prototype_ `TSubclassOf<UCEEffectorModeBase> GetModeClass() const;` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L102 _public prototype_ `void SetVisualizerComponentVisible(bool bInVisible);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L105 _public function_ `bool GetVisualizerComponentVisible() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L111 _public prototype_ `void SetVisualizerSpriteVisible(bool bInVisible);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L114 _public function_ `bool GetVisualizerSpriteVisible() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L119 _public prototype_ `int32 AddVisualizerComponent(UDynamicMeshComponent* InComponent);`
- L122 _public prototype_ `void UpdateVisualizer(int32 InVisualizerIndex, TFunctionRef<void(UDynamicMesh*)> InMeshFunction) const;` — Updates a specific mesh visualizers based on its index
- L124 _public prototype_ `void SetVisualizerColor(int32 InVisualizerIndex, const FLinearColor& InColor);`
- L128 _public prototype_ `TConstArrayView<TWeakObjectPtr<UCEClonerEffectorExtension>> GetClonerExtensionsWeak() const;` — Get linked cloners
- L131 _public prototype_ `FCEClonerEffectorChannelData& GetChannelData();` — Get the effector channel data
- L135 _public prototype_ `int32 GetChannelIdentifier() const;` — `UFUNCTION(BlueprintPure, Category="Effector")` — Get the effector channel identifier
- L137 _public prototype_ `void OnClonerLinked(UCEClonerEffectorExtension* InClonerExtension);`
- L138 _public prototype_ `void OnClonerUnlinked(UCEClonerEffectorExtension* InClonerExtension);`
- L143 _public function_ `InTypeClass* GetActiveType() const`
- L149 _public function_ `UCEEffectorTypeBase* GetActiveType() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L157 _public function_ `InModeClass* GetActiveType() const`
- L163 _public function_ `UCEEffectorModeBase* GetActiveMode() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L168 _public function_ `TConstArrayView<TObjectPtr<UCEEffectorEffectBase>> GetActiveEffects() const`
- L174 _public prototype_ `void GetActiveEffects(TArray<UCEEffectorEffectBase*>& OutEffects) const;` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L177 _public prototype_ `UCEEffectorExtensionBase* GetExtension(TSubclassOf<UCEEffectorExtensionBase> InExtensionClass) const;` — `UFUNCTION(BlueprintCallable, Category="Effector", meta=(DeterminesOutputType="InExtensionClass"))`
- L180 _public function_ `template<typename InExtensionClass UE_REQUIRES(std::is_base_of_v<UCEEffectorExtensionBase, InExtensionClass>)> InExtensionClass* GetExtension() const`
- L185 _public prototype_ `UCEEffectorExtensionBase* GetExtension(FName InExtensionName) const;`
- L187 _public prototype_ `void RequestClonerUpdate(bool bInImmediate);`
- L191 _protected prototype_ `virtual void OnComponentCreated() override;`
- L192 _protected prototype_ `virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;`
- L197 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L198 _protected prototype_ `virtual void PostEditUndo() override;`
- L200 _protected prototype_ `virtual void PostEditImport() override;`
- L201 _protected prototype_ `virtual void PostLoad() override;`
- L202 _protected prototype_ `virtual void PostDuplicate(EDuplicateMode::Type InDuplicateMode) override;`
- L207 _protected prototype_ `void ForceRefreshLinkedCloners();` — `UFUNCTION(CallInEditor, Category="Effector")`
- L212 _protected member_ `bool bEnabled = true;` — `UPROPERTY(EditInstanceOnly, Setter="SetEnabled", Getter="GetEnabled", Category="Effector")` — Is this effector enabled/disabled on linked cloners
- L216 _protected member_ `float Magnitude = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Effector", meta=(ClampMin="0", ClampMax="1"))` — The ratio effect of the effector on clones
- L220 _protected member_ `FLinearColor Color = FLinearColor::Red;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Effector")` — Affected clones color passed over to material
- L224 _protected member_ `FName TypeName = NAME_None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Shape", Category="Shape", meta=(GetOptions="GetEffectorTypeNames"))` — Name of the shape type to use
- L228 _protected member_ `TObjectPtr<UCEEffectorTypeBase> ActiveType;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Cached active type used for faster access
- L232 _protected member_ `FName ModeName = NAME_None;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Mode", Category="Mode", meta=(GetOptions="GetEffectorModeNames"))` — Name of the shape type to use
- L236 _protected member_ `TObjectPtr<UCEEffectorModeBase> ActiveMode;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Cached active mode used for faster access
- L240 _protected member_ `TArray<TObjectPtr<UCEEffectorEffectBase>> ActiveEffects;` — `UPROPERTY(Transient, DuplicateTransient, NonTransactional)` — Active Effects on this effector
- L245 _protected member_ `bool bVisualizerComponentVisible = true;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, Category="Effector")` — Visibility of the components visualizer
- L249 _protected member_ `bool bVisualizerSpriteVisible = true;` — `UPROPERTY(EditInstanceOnly, AdvancedDisplay, Category="Effector")` — Toggle the sprite to visualize and click on this effector
- L253 _private member_ `static constexpr TCHAR VisualizerMaterialPath[] = TEXT("/Sc`
- L254 _private member_ `static constexpr TCHAR VisualizerColorName[] = TEXT("Vis`
- L255 _private member_ `static constexpr TCHAR SpriteTexturePath[] = TEXT("/Sc`
- L257 _private prototype_ `void RegisterToChannel();`
- L258 _private prototype_ `void UnregisterFromChannel();`
- L259 _private prototype_ `void OnTransformUpdated(USceneComponent* InComponent, EUpdateTransformFlags InFlags, ETeleportType InTeleportType);`
- L261 _private prototype_ `void OnEnabledChanged();`
- L262 _private prototype_ `void OnEffectorEnabled();`
- L263 _private prototype_ `void OnEffectorDisabled();`
- L264 _private prototype_ `void OnEffectorSetEnabled(const UWorld* InWorld, bool bInEnabled, bool bInTransact);`
- L266 _private prototype_ `void OnEffectorOptionsChanged();`
- L267 _private prototype_ `void OnTypeNameChanged();`
- L268 _private prototype_ `void OnModeNameChanged();`
- L269 _private prototype_ `void OnEffectsChanged();`
- L272 _private prototype_ `void OnVisualizerOptionsChanged();`
- L277 _private function_ `InExtensionClass* FindOrAddExtension()`
- L282 _private prototype_ `UCEEffectorExtensionBase* FindOrAddExtension(FName InExtensionName);`
- L283 _private prototype_ `UCEEffectorExtensionBase* FindOrAddExtension(TSubclassOf<UCEEffectorExtensionBase> InExtensionClass);`
- L287 _private prototype_ `TArray<FName> GetEffectorTypeNames() const;` — `UFUNCTION()` — Gets all type names available
- L291 _private prototype_ `TArray<FName> GetEffectorModeNames() const;` — `UFUNCTION()` — Gets all mode names available
- L295 _private member_ `FCEClonerEffectorChannelData ChannelData;` — `UPROPERTY(VisibleInstanceOnly, Transient, DuplicateTransient, TextExportTransient, NonTransactional, AdvancedDisplay, Category="Effector", meta=(NoResetToDefault))` — Transient effector channel data
- L299 _private member_ `TArray<TWeakObjectPtr<UCEClonerEffectorExtension>> ClonerExtensionsWeak;` — `UPROPERTY(SkipSerialization, NonTransactional)` — Cloners linked to this effector, used to refresh or relink on duplicate
- L303 _private member_ `TArray<TObjectPtr<UCEEffectorExtensionBase>> ExtensionInstances;` — `UPROPERTY()` — Cached extensions instances
- L307 _private member_ `TArray<TWeakObjectPtr<UDynamicMeshComponent>> VisualizerComponentsWeak;` — `UPROPERTY(Transient, DuplicateTransient)`
- L310 _private member_ `TArray<TObjectPtr<UMaterialInstanceDynamic>> VisualizerMaterialsWeak;` — `UPROPERTY(Transient, DuplicateTransient)`
- L314 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorComponent> PropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/CEEffectorExtensionBase.h` (Public)


#### class `UCEEffectorExtensionBase`  
`class UCEEffectorExtensionBase : public UObject`  
_L13-85_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UObject`
- desc: Represents an extension for an effector to apply a custom behavior on cloner
- L18 _public function_ `UCEEffectorExtensionBase() : UCEEffectorExtensionBase( NAME_None )`
- L24 _public function_ `UCEEffectorExtensionBase(FName InExtensionName) : ExtensionName(InExtensionName)`
- L29 _public function_ `FName GetExtensionName() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L35 _public prototype_ `FCEExtensionSection GetExtensionSection() const;`
- L39 _public prototype_ `UCEEffectorComponent* GetEffectorComponent() const;` — Get the effector component using this extension
- L42 _public prototype_ `void UpdateExtensionParameters(bool bInUpdateLinkedCloners = false);` — Request refresh extension next tick
- L45 _public prototype_ `void ActivateExtension();` — Enable this extension
- L48 _public prototype_ `void DeactivateExtension();` — Disable this extension
- L51 _public function_ `bool IsExtensionActive() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L57 _public function_ `virtual bool RedirectExtensionName(FName InOldExtensionName) const` — Called after load when extension name is obsolete to handle redirection to this extension
- L64 _protected prototype_ `virtual void PostEditImport() override;`
- L68 _protected function_ `virtual void OnExtensionActivated()` — Called when extension becomes active
- L71 _protected function_ `virtual void OnExtensionDeactivated()` — Called when extension becomes inactive
- L74 _protected function_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent)` — Called to reapply type parameters
- L77 _protected prototype_ `void OnExtensionPropertyChanged();` — Used by PECP to update parameters
- L82 _private member_ `FName ExtensionName = NAME_None;` — `UPROPERTY(Transient)` — Unique extension name used for dropdown and selection
- L84 _private member_ `bool bExtensionActive = false;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Effects/CEEffectorDelayEffect.h` (Public)


#### class `UCEEffectorDelayEffect`  
`class UCEEffectorDelayEffect : public UCEEffectorEffectBase`  
_L13-105_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent, meta=(Section="Delay", Priority=3))`
- inherits: `UCEEffectorEffectBase`
- desc: Effector delay extension to affect clones after a period of time with a spring effect
- L18 _public function_ `UCEEffectorDelayEffect() : UCEEffectorEffectBase( TEXT("Delay") )`
- L25 _public prototype_ `void SetDelayEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L28 _public function_ `bool GetDelayEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L34 _public prototype_ `void SetDelayInDuration(float InDuration);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L37 _public function_ `float GetDelayInDuration() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L43 _public prototype_ `void SetDelayOutDuration(float InDuration);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L46 _public function_ `float GetDelayOutDuration() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L52 _public prototype_ `void SetDelaySpringFrequency(float InFrequency);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L55 _public function_ `float GetDelaySpringFrequency() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L61 _public prototype_ `void SetDelaySpringFalloff(float InFalloff);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L64 _public function_ `float GetDelaySpringFalloff() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L72 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L77 _protected prototype_ `virtual void UpdateEffectChannelData(FCEClonerEffectorChannelData& InChannelData, bool bInEnabled) override;`
- L82 _protected member_ `bool bDelayEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetDelayEnabled", Getter="GetDelayEnabled", DisplayName="Enabled", Category="Delay", meta=(RefreshPropertyView))` — Enable time delay for the mode effect
- L86 _protected member_ `float DelayInDuration = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Offset Duration", Category="Delay", meta=(Units=Seconds, ClampMin="0", EditCondition="bDelayEnabled", EditConditionHides))` — Time delay for the effect to reach its peak
- L90 _protected member_ `float DelayOutDuration = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Trail Duration", Category="Delay", meta=(Units=Seconds, ClampMin="0", EditCondition="bDelayEnabled", EditConditionHides))` — Time delay for the effect to go back to its rest state
- L94 _protected member_ `float DelaySpringFrequency = 3.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Spring Frequency", Category="Delay", meta=(ClampMin="1", EditCondition="bDelayEnabled", EditConditionHides))` — Frequency of the delayed spring effect
- L98 _protected member_ `float DelaySpringFalloff = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Spring Falloff", Category="Delay", meta=(ClampMin="1", EditCondition="bDelayEnabled", EditConditionHides))` — Damping or decay of the delayed spring effect
- L103 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorDelayEffect> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Effects/CEEffectorEffectBase.h` (Public)


#### class `UCEEffectorEffectBase`  
`class UCEEffectorEffectBase : public UCEEffectorExtensionBase`  
_L12-40_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Within=CEEffectorComponent, meta=(Section="Effect", Priority=3))`
- inherits: `UCEEffectorExtensionBase`
- desc: Represents an effect for an effector to affect clones in a specific way, works with modes and types
- L17 _public function_ `UCEEffectorEffectBase() : UCEEffectorExtensionBase(NAME_None)`
- L21 _public function_ `UCEEffectorEffectBase(FName InModeName) : UCEEffectorExtensionBase( InModeName )`
- L28 _public function_ `virtual bool IsModeSupported(TSubclassOf<UCEEffectorModeBase> InModeClass) const` — Filter supported mode
- L35 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L36 _protected prototype_ `virtual void OnExtensionDeactivated() override;`
- L39 _protected function_ `virtual void UpdateEffectChannelData(FCEClonerEffectorChannelData& InChannelData, bool bInEnabled)`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Effects/CEEffectorForceEffect.h` (Public)


#### class `UCEEffectorForceEffect`  
`class UCEEffectorForceEffect : public UCEEffectorEffectBase`  
_L13-306_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent, meta=(Section="Forces", Priority=3))`
- inherits: `UCEEffectorEffectBase`
- desc: Effector supported forces to affect clones
- L18 _public function_ `UCEEffectorForceEffect() : UCEEffectorEffectBase( TEXT("Forces") )`
- L25 _public prototype_ `void SetForcesEnabled(bool bInForcesEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L28 _public function_ `bool GetForcesEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L34 _public prototype_ `void SetOrientationForceEnabled(bool bInForceEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L37 _public function_ `bool GetOrientationForceEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L43 _public prototype_ `void SetOrientationForceRate(float InForceOrientationRate);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L46 _public function_ `float GetOrientationForceRate() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L52 _public prototype_ `void SetOrientationForceMin(const FVector& InForceOrientationMin);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L55 _public function_ `const FVector& GetOrientationForceMin() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L61 _public prototype_ `void SetOrientationForceMax(const FVector& InForceOrientationMax);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L64 _public function_ `const FVector& GetOrientationForceMax() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L70 _public prototype_ `void SetVortexForceEnabled(bool bInForceEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L73 _public function_ `bool GetVortexForceEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L79 _public prototype_ `void SetVortexForceAmount(float InForceVortexAmount);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L82 _public function_ `float GetVortexForceAmount() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L88 _public prototype_ `void SetVortexForceAxis(const FVector& InForceVortexAxis);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L91 _public function_ `const FVector& GetVortexForceAxis() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L97 _public prototype_ `void SetCurlNoiseForceEnabled(bool bInForceEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L100 _public function_ `bool GetCurlNoiseForceEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L106 _public prototype_ `void SetCurlNoiseForceStrength(float InForceCurlNoiseStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L109 _public function_ `float GetCurlNoiseForceStrength() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L115 _public prototype_ `void SetCurlNoiseForceFrequency(float InForceCurlNoiseFrequency);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L118 _public function_ `float GetCurlNoiseForceFrequency() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L124 _public prototype_ `void SetAttractionForceEnabled(bool bInForceEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L127 _public function_ `bool GetAttractionForceEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L133 _public prototype_ `void SetAttractionForceStrength(float InForceStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L136 _public function_ `float GetAttractionForceStrength() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L142 _public prototype_ `void SetAttractionForceFalloff(float InForceFalloff);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L145 _public function_ `float GetAttractionForceFalloff() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L151 _public prototype_ `void SetGravityForceEnabled(bool bInForceEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L154 _public function_ `bool GetGravityForceEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L160 _public prototype_ `void SetGravityForceAcceleration(const FVector& InAcceleration);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L163 _public function_ `FVector GetGravityForceAcceleration() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L169 _public prototype_ `void SetDragForceEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L172 _public function_ `bool GetDragForceEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L178 _public prototype_ `void SetDragForceLinear(float InStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L181 _public function_ `float GetDragForceLinear() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L187 _public prototype_ `void SetDragForceRotational(float InStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L190 _public function_ `float GetDragForceRotational() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L196 _public prototype_ `void SetVectorNoiseForceEnabled(bool bInEnabled);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L199 _public function_ `bool GetVectorNoiseForceEnabled() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L205 _public prototype_ `void SetVectorNoiseForceAmount(float InAmount);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L208 _public function_ `float GetVectorNoiseForceAmount() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L216 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L221 _protected prototype_ `virtual void OnExtensionDeactivated() override;`
- L225 _protected prototype_ `virtual void UpdateEffectChannelData(FCEClonerEffectorChannelData& InChannelData, bool bInEnabled) override;`
- L228 _protected prototype_ `void OnForceOptionsChanged();`
- L232 _protected member_ `bool bForcesEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetForcesEnabled", Getter="GetForcesEnabled", DisplayName="Enabled", Category="Force", meta=(RefreshPropertyView))` — Forces global state
- L236 _protected member_ `bool bOrientationForceEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetOrientationForceEnabled", Getter="GetOrientationForceEnabled", Category="Force", meta=(EditCondition="bForcesEnabled", EditConditionHides, RefreshPropertyView))` — Enable orientation force to allow each clone instance to rotate around its pivot
- L239 _protected member_ `float OrientationForceRate = 1.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(Delta="0.0001", ClampMin="0", EditCondition="bForcesEnabled && bOrientationForceEnabled", EditConditionHides))`
- L242 _protected member_ `FVector OrientationForceMin = FVector(-0.1f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(AllowPreserveRatio, EditCondition="bForcesEnabled && bOrientationForceEnabled", EditConditionHides))`
- L245 _protected member_ `FVector OrientationForceMax = FVector(0.1f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(AllowPreserveRatio, EditCondition="bForcesEnabled && bOrientationForceEnabled", EditConditionHides))`
- L249 _protected member_ `bool bVortexForceEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetVortexForceEnabled", Getter="GetVortexForceEnabled", Category="Force", meta=(EditCondition="bForcesEnabled", EditConditionHides, RefreshPropertyView))` — Enable vortex force to allow each clone instance to rotate around a specific axis on the cloner pivot
- L252 _protected member_ `float VortexForceAmount = 100.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bVortexForceEnabled", EditConditionHides))`
- L255 _protected member_ `FVector VortexForceAxis = FVector::ZAxisVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bVortexForceEnabled", EditConditionHides))`
- L259 _protected member_ `bool bCurlNoiseForceEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetCurlNoiseForceEnabled", Getter="GetCurlNoiseForceEnabled", Category="Force", meta=(EditCondition="bForcesEnabled", EditConditionHides, RefreshPropertyView))` — Enable curl noise force to allow each clone instance to add random location variation
- L262 _protected member_ `float CurlNoiseForceStrength = 100.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bCurlNoiseForceEnabled", EditConditionHides))`
- L265 _protected member_ `float CurlNoiseForceFrequency = 10.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bCurlNoiseForceEnabled", EditConditionHides))`
- L269 _protected member_ `bool bAttractionForceEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetAttractionForceEnabled", Getter="GetAttractionForceEnabled", Category="Force", meta=(EditCondition="bForcesEnabled", EditConditionHides, RefreshPropertyView))` — Enable attraction force to allow each clone instances to gravitate toward a location
- L272 _protected member_ `float AttractionForceStrength = 100.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bAttractionForceEnabled", EditConditionHides))`
- L275 _protected member_ `float AttractionForceFalloff = 0.1f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bAttractionForceEnabled", EditConditionHides))`
- L279 _protected member_ `bool bGravityForceEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetGravityForceEnabled", Getter="GetGravityForceEnabled", Category="Force", meta=(EditCondition="bForcesEnabled", EditConditionHides, RefreshPropertyView))` — Enable gravity force to pull particles based on an acceleration vector
- L282 _protected member_ `FVector GravityForceAcceleration = FVector(0, 0, -980.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bGravityForceEnabled", EditConditionHides))`
- L286 _protected member_ `bool bDragForceEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetDragForceEnabled", Getter="GetDragForceEnabled", Category="Force", meta=(EditCondition="bForcesEnabled", EditConditionHides, RefreshPropertyView))` — Enable drag force to decrease particles velocity
- L289 _protected member_ `float DragForceLinear = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bDragForceEnabled", EditConditionHides))`
- L292 _protected member_ `float DragForceRotational = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bDragForceEnabled", EditConditionHides))`
- L296 _protected member_ `bool bVectorNoiseForceEnabled = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetVectorNoiseForceEnabled", Getter="GetVectorNoiseForceEnabled", Category="Force", meta=(EditCondition="bForcesEnabled", EditConditionHides, RefreshPropertyView))` — Enable vector random noise force to add variation to clones behavior
- L299 _protected member_ `float VectorNoiseForceAmount = 100.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Force", meta=(EditCondition="bForcesEnabled && bVectorNoiseForceEnabled", EditConditionHides))`
- L304 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorForceEffect> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorCancelMode.h` (Public)


#### class `UCEEffectorCancelMode`  
`class UCEEffectorCancelMode : public UCEEffectorModeBase`  
_L13-26_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorModeBase`
- desc: Negates all effects applied on clones
- L18 _public function_ `UCEEffectorCancelMode() : UCEEffectorModeBase(TEXT("Cancel"), static_cast<int32>(ECEClonerEffectorMode::Cancel))`
- L24 _protected prototype_ `virtual bool IsEffectSupported(TSubclassOf<UCEEffectorEffectBase> InEffectClass) const override;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorCullMode.h` (Public)


#### enum `ECEEffectorCullModeBehavior`  
`enum class ECEEffectorCullModeBehavior : uint8`  
_L13-19_
- reflection: `UENUM(BlueprintType)`
- L16 _public enumerator_ `Kill` — Kill clones based on effector shape, lower priority than other hide effector
- L18 _public enumerator_ `Hide` — Hide clones based on effector shape, higher priority than other kill effector

#### class `UCEEffectorCullMode`  
`class UCEEffectorCullMode : public UCEEffectorModeBase`  
_L22-76_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorModeBase`
- L27 _public function_ `UCEEffectorCullMode() : UCEEffectorModeBase(TEXT("Cull"), static_cast<int32>(ECEClonerEffectorMode::Cull))`
- L32 _public prototype_ `void SetBehavior(ECEEffectorCullModeBehavior InBehavior);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `ECEEffectorCullModeBehavior GetBehavior() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L41 _public prototype_ `void SetScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L44 _public function_ `const FVector& GetScale() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L51 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L55 _protected prototype_ `virtual void PostInitProperties() override;`
- L57 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L61 _protected prototype_ `void OnBehaviorChanged();`
- L65 _protected member_ `ECEEffectorCullModeBehavior Behavior = ECEEffectorCullModeBehavior::Hide;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode")` — Expected behavior when culling clones
- L69 _protected member_ `FVector Scale = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.01"))` — Scale applied on affected clones before they are culled to slowly disappear
- L74 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorCullMode> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorModeBase.h` (Public)


#### class `UCEEffectorModeBase`  
`class UCEEffectorModeBase : public UCEEffectorExtensionBase`  
_L13-51_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Within=CEEffectorComponent, meta=(Section="Mode", Priority=2))`
- inherits: `UCEEffectorExtensionBase`
- desc: Represents a behavior for an effector to affect clones in a specific way
- L18 _public function_ `UCEEffectorModeBase() : UCEEffectorModeBase(NAME_None, INDEX_NONE)`
- L22 _public function_ `UCEEffectorModeBase(FName InModeName, int32 InModeIdentifier) : UCEEffectorExtensionBase( InModeName ) , ModeIdentifier(InModeIdentifier)`
- L29 _public function_ `int32 GetModeIdentifier() const`
- L34 _public prototype_ `TSet<TSubclassOf<UCEEffectorEffectBase>> GetSupportedEffects() const;`
- L38 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L42 _protected function_ `virtual bool IsEffectSupported(TSubclassOf<UCEEffectorEffectBase> InEffectClass) const` — Override if a specific effect is not supported by this mode
- L50 _private member_ `int32 ModeIdentifier = 0;` — `UPROPERTY(Transient)` — Unique identifier to pass it to niagara

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorOffsetMode.h` (Public)


#### class `UCEEffectorOffsetMode`  
`class UCEEffectorOffsetMode : public UCEEffectorModeBase`  
_L13-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorModeBase`
- L18 _public function_ `UCEEffectorOffsetMode() : UCEEffectorModeBase(TEXT("Offset"), static_cast<int32>(ECEClonerEffectorMode::Default))`
- L23 _public prototype_ `void SetOffset(const FVector& InOffset);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `FVector GetOffset() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `FRotator GetRotation() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L41 _public prototype_ `void SetScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L44 _public function_ `FVector GetScale() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L51 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L56 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L62 _protected member_ `FVector Offset = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode")` — Offset applied on affected clones
- L66 _protected member_ `FRotator Rotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode")` — Rotation applied on affected clones
- L70 _protected member_ `FVector Scale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.01"))` — Scale applied on affected clones
- L75 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorOffsetMode> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorProceduralMode.h` (Public)


#### class `UCEEffectorProceduralMode`  
`class UCEEffectorProceduralMode : public UCEEffectorModeBase`  
_L13-118_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorModeBase`
- L18 _public function_ `UCEEffectorProceduralMode() : UCEEffectorModeBase(TEXT("Procedural"), static_cast<int32>(ECEClonerEffectorMode::Procedural))`
- L23 _public prototype_ `void SetPattern(ECEClonerEffectorProceduralPattern InPattern);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `ECEClonerEffectorProceduralPattern GetPattern() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetLocationStrength(const FVector& InStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `FVector GetLocationStrength() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L41 _public prototype_ `void SetRotationStrength(const FRotator& InStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L44 _public function_ `FRotator GetRotationStrength() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L50 _public prototype_ `void SetScaleStrength(const FVector& InStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L53 _public function_ `FVector GetScaleStrength() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L59 _public prototype_ `void SetPan(const FVector& InPan);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L62 _public function_ `FVector GetPan() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L68 _public prototype_ `void SetFrequency(float InFrequency);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L71 _public function_ `float GetFrequency() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L78 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L79 _protected prototype_ `virtual bool RedirectExtensionName(FName InOldExtensionName) const override;`
- L83 _protected prototype_ `virtual void PostInitProperties() override;`
- L85 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L91 _protected member_ `ECEClonerEffectorProceduralPattern Pattern = ECEClonerEffectorProceduralPattern::CurlNoise;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode")` — Procedural pattern behavior
- L95 _protected member_ `FVector LocationStrength = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode")` — Amplitude of the noise field for location
- L99 _protected member_ `FRotator RotationStrength = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode")` — Amplitude of the noise field for rotation
- L103 _protected member_ `FVector ScaleStrength = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ", Delta="0.01"))` — Amplitude of the noise field for scale
- L107 _protected member_ `FVector Pan = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))` — Panning to offset the noise field sampling
- L111 _protected member_ `float Frequency = 0.5f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode", meta=(ClampMin="0"))` — Intensity of the noise field
- L116 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorProceduralMode> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorPushMode.h` (Public)


#### class `UCEEffectorPushMode`  
`class UCEEffectorPushMode : public UCEEffectorModeBase`  
_L13-64_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorModeBase`
- L18 _public function_ `UCEEffectorPushMode() : UCEEffectorModeBase(TEXT("Push"), static_cast<int32>(ECEClonerEffectorMode::Push))`
- L23 _public prototype_ `void SetPushDirection(ECEClonerEffectorPushDirection InDirection);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `ECEClonerEffectorPushDirection GetPushDirection() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetPushStrength(const FVector& InStrength);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `const FVector& GetPushStrength() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L42 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L47 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L53 _protected member_ `FVector PushStrength = FVector(100.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode", meta=(MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))` — Strength of the push effect
- L57 _protected member_ `ECEClonerEffectorPushDirection PushDirection = ECEClonerEffectorPushDirection::Effector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode")` — Relative direction computed for the push effect on each clone
- L62 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorPushMode> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorStepMode.h` (Public)


#### class `UCEEffectorStepMode`  
`class UCEEffectorStepMode : public UCEEffectorModeBase`  
_L13-77_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorModeBase`
- L18 _public function_ `UCEEffectorStepMode() : UCEEffectorModeBase(TEXT("Step"), static_cast<int32>(ECEClonerEffectorMode::Step))`
- L23 _public prototype_ `void SetStepPosition(const FVector& InPosition);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `FVector GetStepPosition() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetStepRotation(const FRotator& InRotation);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `FRotator GetStepRotation() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L41 _public prototype_ `void SetStepScale(const FVector& InScale);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L44 _public function_ `FVector GetStepScale() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L52 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L57 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L62 _protected member_ `FVector StepPosition = FVector::ZeroVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Position", Category="Mode")` — Interpolates from 0 to this position offset based on the particle index and particle count
- L66 _protected member_ `FRotator StepRotation = FRotator::ZeroRotator;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Rotation", Category="Mode")` — Interpolates from 0 to this rotation based on the particle index and particle count
- L70 _protected member_ `FVector StepScale = FVector::OneVector;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, DisplayName="Scale", Category="Mode", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))` — Interpolates from 1 to this scale based on the particle index and particle count
- L75 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorStepMode> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Modes/CEEffectorTargetMode.h` (Public)


#### class `UCEEffectorTargetMode`  
`class UCEEffectorTargetMode : public UCEEffectorModeBase`  
_L14-71_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorModeBase`
- L19 _public function_ `UCEEffectorTargetMode() : UCEEffectorModeBase(TEXT("Target"), static_cast<int32>(ECEClonerEffectorMode::Target))`
- L24 _public prototype_ `void SetTargetActor(AActor* InTargetActor);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L27 _public function_ `AActor* GetTargetActor() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetTargetActorWeak(const TWeakObjectPtr<AActor>& InTargetActor);`
- L34 _public function_ `TWeakObjectPtr<AActor> GetTargetActorWeak() const`
- L41 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L42 _protected prototype_ `virtual void OnExtensionDeactivated() override;`
- L43 _protected prototype_ `virtual void OnExtensionActivated() override;`
- L48 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L54 _protected member_ `TWeakObjectPtr<AActor> TargetActorWeak = nullptr;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Mode", meta=(DisplayName="TargetActor"))` — The actor to track when mode is set to target
- L57 _protected member_ `TWeakObjectPtr<AActor> InternalTargetActorWeak = nullptr;` — `UPROPERTY()`
- L60 _private prototype_ `void OnTargetActorChanged();`
- L62 _private prototype_ `void OnTargetActorTransformChanged(USceneComponent* InUpdatedComponent, EUpdateTransformFlags InFlags, ETeleportType InTeleport);`
- L65 _private prototype_ `void OnTargetActorDestroyed(AActor* InActor);` — `UFUNCTION()`
- L69 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorTargetMode> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorBoundType.h` (Public)


#### class `UCEEffectorBoundType`  
`class UCEEffectorBoundType : public UCEEffectorTypeBase`  
_L11-74_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorTypeBase`
- L18 _public function_ `UCEEffectorBoundType() : UCEEffectorTypeBase(NAME_None, INDEX_NONE)`
- L22 _public function_ `UCEEffectorBoundType(FName InTypeName, int32 InTypeIdentifier) : UCEEffectorTypeBase(InTypeName, InTypeIdentifier)`
- L27 _public prototype_ `void SetInvertType(bool bInInvert);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L30 _public function_ `bool GetInvertType() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L36 _public prototype_ `void SetEasing(ECEClonerEasing InEasing);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L39 _public function_ `ECEClonerEasing GetEasing() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L46 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L47 _protected prototype_ `virtual void OnExtensionActivated() override;`
- L48 _protected prototype_ `virtual void OnExtensionDeactivated() override;`
- L53 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L58 _protected prototype_ `void OnEffectorDeveloperSettingsChanged(UObject* InSettings, FPropertyChangedEvent& InEvent);`
- L63 _protected member_ `bool bInvertType = false;` — `UPROPERTY(EditInstanceOnly, Setter="SetInvertType", Getter="GetInvertType", Category="Shape")` — Invert the type effect, instead of affecting the inside of a zone, will affect the outside
- L67 _protected member_ `ECEClonerEasing Easing = ECEClonerEasing::Linear;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape")` — Weight easing function applied to lerp transforms
- L72 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorBoundType> PropertyChangeDispatcher;` — Used for PECP

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorBoxType.h` (Public)


#### class `UCEEffectorBoxType`  
`class UCEEffectorBoxType : public UCEEffectorBoundType`  
_L11-70_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorBoundType`
- L18 _public function_ `UCEEffectorBoxType() : UCEEffectorBoundType(TEXT("Box"), static_cast<int32>(ECEClonerEffectorType::Box))`
- L23 _public prototype_ `void SetInnerExtent(const FVector& InExtent);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `FVector GetInnerExtent() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetOuterExtent(const FVector& InExtent);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `FVector GetOuterExtent() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L42 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L46 _protected prototype_ `virtual void OnExtensionVisualizerDirty(int32 InDirtyFlags) override;`
- L51 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L52 _protected prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyChain) override;`
- L58 _protected member_ `FVector InnerExtent = FVector(50.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))` — Inner extent of box, all clones inside will be affected with a maximum weight
- L62 _protected member_ `FVector OuterExtent = FVector(200.f);` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0", MotionDesignVectorWidget, AllowPreserveRatio="XYZ"))` — Outer extent of box, all clones outside will not be affected
- L67 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorBoxType> PropertyChangeDispatcher;` — Used for PECP
- L68 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorBoxType> PrePropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorPlaneType.h` (Public)


#### class `UCEEffectorPlaneType`  
`class UCEEffectorPlaneType : public UCEEffectorBoundType`  
_L11-57_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorBoundType`
- L18 _public function_ `UCEEffectorPlaneType() : UCEEffectorBoundType(TEXT("Plane"), static_cast<int32>(ECEClonerEffectorType::Plane))`
- L23 _public prototype_ `void SetPlaneSpacing(float InSpacing);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `float GetPlaneSpacing() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L33 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L37 _protected prototype_ `virtual void OnExtensionVisualizerDirty(int32 InDirtyFlags) override;`
- L42 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L43 _protected prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyChain) override;`
- L49 _protected member_ `float PlaneSpacing = 200.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Plane spacing, everything inside this zone will be affected
- L54 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorPlaneType> PropertyChangeDispatcher;` — Used for PECP
- L55 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorPlaneType> PrePropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorRadialType.h` (Public)


#### class `UCEEffectorRadialType`  
`class UCEEffectorRadialType : public UCEEffectorBoundType`  
_L11-83_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorBoundType`
- L18 _public function_ `UCEEffectorRadialType() : UCEEffectorBoundType(TEXT("Radial"), static_cast<int32>(ECEClonerEffectorType::Radial))`
- L23 _public prototype_ `void SetRadialAngle(float InAngle);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `float GetRadialAngle() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetRadialMinRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `float GetRadialMinRadius() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L41 _public prototype_ `void SetRadialMaxRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L44 _public function_ `float GetRadialMaxRadius() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L51 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L55 _protected prototype_ `virtual void OnExtensionVisualizerDirty(int32 InDirtyFlags) override;`
- L60 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L61 _protected prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyChain) override;`
- L67 _protected member_ `float RadialAngle = 180.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0", ClampMax="360"))` — Radial angle in degree, everything within the angle will be affected
- L71 _protected member_ `float RadialMinRadius = 0.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Minimum radius for the radial effect to be applied on clones, below clones will not be affected
- L75 _protected member_ `float RadialMaxRadius = 1000.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Maximum radius for the radial effect to be applied on clones, above clones will not be affected
- L80 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorRadialType> PropertyChangeDispatcher;` — Used for PECP
- L81 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorRadialType> PrePropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorSphereType.h` (Public)


#### class `UCEEffectorSphereType`  
`class UCEEffectorSphereType : public UCEEffectorBoundType`  
_L11-70_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorBoundType`
- L18 _public function_ `UCEEffectorSphereType() : UCEEffectorBoundType(TEXT("Sphere"), static_cast<int32>(ECEClonerEffectorType::Sphere))`
- L23 _public prototype_ `void SetOuterRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `float GetOuterRadius() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetInnerRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `float GetInnerRadius() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L42 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L46 _protected prototype_ `virtual void OnExtensionVisualizerDirty(int32 InDirtyFlags) override;`
- L51 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L52 _protected prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyChain) override;`
- L58 _protected member_ `float InnerRadius = 50.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Inner radius of sphere, all clones inside will be affected with a maximum weight
- L62 _protected member_ `float OuterRadius = 200.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Outer radius of sphere, all clones outside will not be affected
- L67 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorSphereType> PropertyChangeDispatcher;` — Used for PECP
- L68 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorSphereType> PrePropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorTorusType.h` (Public)


#### class `UCEEffectorTorusType`  
`class UCEEffectorTorusType : public UCEEffectorBoundType`  
_L11-83_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorBoundType`
- L18 _public function_ `UCEEffectorTorusType() : UCEEffectorBoundType(TEXT("Torus"), static_cast<int32>(ECEClonerEffectorType::Torus))`
- L23 _public prototype_ `void SetTorusRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L26 _public function_ `float GetTorusRadius() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L32 _public prototype_ `void SetTorusInnerRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L35 _public function_ `float GetTorusInnerRadius() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L41 _public prototype_ `void SetTorusOuterRadius(float InRadius);` — `UFUNCTION(BlueprintCallable, Category="Effector")`
- L44 _public function_ `float GetTorusOuterRadius() const` — `UFUNCTION(BlueprintPure, Category="Effector")`
- L51 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L55 _protected prototype_ `virtual void OnExtensionVisualizerDirty(int32 InDirtyFlags) override;`
- L60 _protected prototype_ `virtual void PostEditChangeProperty(FPropertyChangedEvent& InPropertyChangedEvent) override;`
- L61 _protected prototype_ `virtual void PreEditChange(FEditPropertyChain& InPropertyChain) override;`
- L67 _protected member_ `float TorusRadius = 250.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Main torus radius from center to the edge where inner and outer tube will be revolved
- L71 _protected member_ `float TorusInnerRadius = 50.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Minimum revolved radius for the torus effect, clones contained inside will be affected with a maximum weight
- L75 _protected member_ `float TorusOuterRadius = 200.f;` — `UPROPERTY(EditInstanceOnly, Setter, Getter, Category="Shape", meta=(ClampMin="0"))` — Maximum revolved radius for the torus effect, clones outside of it will not be affected
- L80 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorTorusType> PropertyChangeDispatcher;` — Used for PECP
- L81 _private member_ `static const TCEPropertyChangeDispatcher<UCEEffectorTorusType> PrePropertyChangeDispatcher;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorTypeBase.h` (Public)


#### class `UCEEffectorTypeBase`  
`class UCEEffectorTypeBase : public UCEEffectorExtensionBase`  
_L19-82_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType, Within=CEEffectorComponent, meta=(Section="Shape", Priority=1))`
- inherits: `UCEEffectorExtensionBase`
- desc: Represents a shape for an effector to affect clones on specific zones
- L24 _public member_ `static constexpr int32 InnerVisualizerFlag = 1 << 0;`
- L25 _public member_ `static constexpr int32 OuterVisualizerFlag = 1 << 1;`
- L27 _public function_ `UCEEffectorTypeBase() : UCEEffectorTypeBase(NAME_None, INDEX_NONE)`
- L31 _public function_ `UCEEffectorTypeBase(FName InTypeName, int32 InTypeIdentifier) : UCEEffectorExtensionBase( InTypeName ) , TypeIdentifier(InTypeIdentifier)`
- L38 _public function_ `int32 GetTypeIdentifier() const`
- L44 _protected prototype_ `static int32 VisualizerFlagToIdentifier(int32 InVisualizerFlag);`
- L48 _protected prototype_ `virtual void PostEditUndo() override;`
- L53 _protected prototype_ `virtual void OnExtensionParametersChanged(UCEEffectorComponent* InComponent) override;`
- L57 _protected prototype_ `virtual void OnExtensionActivated() override;`
- L60 _protected prototype_ `void MarkVisualizerDirty(int32 InDirtyFlags);`
- L61 _protected prototype_ `void UpdateVisualizer(int32 InVisualizerFlag, TFunctionRef<void(UDynamicMesh*)> InMeshFunction) const;`
- L64 _protected function_ `virtual void OnExtensionVisualizerDirty(int32 InDirtyFlags)` — Called when a visualizer is dirtied to update it
- L67 _protected prototype_ `void OnVisualizerPropertyChanged();`
- L68 _protected prototype_ `bool OnVisualizerTick(float InDeltaTime);`
- L74 _private member_ `int32 TypeIdentifier = 0;` — `UPROPERTY(Transient)` — Unique identifier to pass it to niagara
- L78 _private member_ `int32 DirtyVisualizerFlags = 0;` — Dirty visualizer ids
- L80 _private member_ `FTSTicker::FDelegateHandle VisualizerTickHandle;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Effector/Types/CEEffectorUnboundType.h` (Public)


#### class `UCEEffectorUnboundType`  
`class UCEEffectorUnboundType : public UCEEffectorTypeBase`  
_L10-23_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Within=CEEffectorComponent)`
- inherits: `UCEEffectorTypeBase`
- L15 _public function_ `UCEEffectorUnboundType() : UCEEffectorTypeBase(TEXT("Unbound"), static_cast<int32>(ECEClonerEffectorType::Unbound))`
- L21 _protected prototype_ `virtual void OnExtensionVisualizerDirty(int32 InDirtyFlags) override;`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Subsystems/CEClonerSubsystem.h` (Public)


#### class `UCEClonerSubsystem`  
`class UCEClonerSubsystem : public UEngineSubsystem`  
_L21-179_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UEngineSubsystem`
- L37 _public function_ `static FOnSubsystemInitialized::RegistrationType& OnSubsystemInitialized()`
- L42 _public function_ `static FOnClonerSetEnabled::RegistrationType& OnClonerSetEnabled()`
- L47 _public function_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<ICEClonerSceneTreeCustomResolver>, FOnGetSceneTreeResolver, ULevel* ) static FOnGetSceneTreeResolver::RegistrationType& OnGetSceneTreeResolver()`
- L54 _public prototype_ `static UCEClonerSubsystem* Get();` — Get this subsystem instance
- L56 _public prototype_ `bool RegisterLayoutClass(UClass* InClonerLayoutClass);`
- L58 _public prototype_ `bool UnregisterLayoutClass(UClass* InClonerLayoutClass);`
- L60 _public prototype_ `bool IsLayoutClassRegistered(UClass* InClonerLayoutClass);`
- L63 _public prototype_ `TSet<FName> GetLayoutNames() const;` — Get available cloner layout names to use in dropdown
- L66 _public prototype_ `TSet<TSubclassOf<UCEClonerLayoutBase>> GetLayoutClasses() const;` — Get available cloner layout classes
- L69 _public prototype_ `FName FindLayoutName(TSubclassOf<UCEClonerLayoutBase> InLayoutClass) const;` — Based on a layout class, find layout name
- L72 _public prototype_ `TSubclassOf<UCEClonerLayoutBase> FindLayoutClass(FName InLayoutName) const;` — Based on a layout name, find layout class
- L75 _public prototype_ `UCEClonerLayoutBase* CreateNewLayout(FName InLayoutName, UCEClonerComponent* InCloner);` — Creates a new layout instance for a cloner
- L77 _public prototype_ `bool RegisterExtensionClass(UClass* InClass);`
- L79 _public prototype_ `bool UnregisterExtensionClass(UClass* InClass);`
- L81 _public prototype_ `bool IsExtensionClassRegistered(UClass* InClass) const;`
- L84 _public prototype_ `TSet<FName> GetExtensionNames() const;` — Get available cloner extension names to use
- L87 _public prototype_ `TSet<TSubclassOf<UCEClonerExtensionBase>> GetExtensionClasses() const;` — Get available cloner extension classes to use
- L90 _public prototype_ `FName FindExtensionName(TSubclassOf<UCEClonerExtensionBase> InClass) const;` — Based on a extension class, find extension name
- L93 _public prototype_ `UCEClonerExtensionBase* CreateNewExtension(FName InExtensionName, UCEClonerComponent* InCloner);` — Creates a new extension instance for a cloner
- L96 _public prototype_ `void SetClonersEnabled(const TSet<UCEClonerComponent*>& InCloners, bool bInEnable, bool bInShouldTransact);` — Set cloners state and optionally transact
- L99 _public prototype_ `void SetLevelClonersEnabled(const UWorld* InWorld, bool bInEnable, bool bInShouldTransact);` — Set cloners state in world and optionally transact
- L103 _public prototype_ `void ConvertCloners(const TSet<UCEClonerComponent*>& InCloners, ECEClonerMeshConversion InMeshConversion);` — Converts cloners simulation to a mesh
- L107 _public function_ `TArray<UCEEffectorComponent*> CreateLinkedEffectors(const TArray<UCEClonerComponent*>& InCloners, ECEClonerActionFlags InFlags, TFunctionRef<void(UCEEffectorComponent*)> InGenerator = [](UCEEffectorComponent*){});` — Spawn linked effectors with a generator and optionally transact
- L107 _public prototype_ `TArray<UCEEffectorComponent*> CreateLinkedEffectors(const TArray<UCEClonerComponent*>& InCloners, ECEClonerActionFlags InFlags, TFunctionRef<void(UCEEffectorComponent*)> InGenerator = [](UCEEffectorComponent*){});` — Spawn linked effectors with a generator and optionally transact
- L110 _public prototype_ `UCEClonerComponent* CreateClonerWithActors(UWorld* InWorld, const TSet<AActor*>& InActors, ECEClonerActionFlags InFlags);` — Creates a new cloner with actors attached
- L113 _public prototype_ `void FireMaterialWarning(const AActor* InClonerActor, const AActor* InContextActor, const TArray<TWeakObjectPtr<UMaterialInterface>>& InUnsetMaterials);` — Fires a warning about unset materials used within a cloner
- L116 _public prototype_ `bool RegisterAttachmentTreeBehavior(FName InName, TFunction<TSharedRef<ICEClonerAttachmentTreeBehavior>()>& InCreator);` — Register an attachment tree behavior
- L119 _public prototype_ `bool UnregisterAttachmentTreeBehavior(FName InName);` — Unregister an attachment tree behavior
- L122 _public prototype_ `TArray<FName> GetAttachmentTreeBehaviorNames() const;` — Gets all attachment behavior registered
- L125 _public prototype_ `TSharedPtr<ICEClonerAttachmentTreeBehavior> CreateAttachmentTreeBehavior(FName InName) const;` — Creates the specific attachment tree behavior
- L128 _public prototype_ `TSharedPtr<ICEClonerSceneTreeCustomResolver> FindCustomLevelSceneTreeResolver(ULevel* InLevel);` — Finds a custom scene tree resolver for a specific level if available
- L131 _public prototype_ `const UNiagaraSystem* FindOrLoadTemplateNiagaraSystem(const UCEClonerLayoutBase* InLayout);` — Finds or loads the template niagara system to be used by the layout
- L134 _public prototype_ `const UNiagaraSystem* FindOrLoadBaseNiagaraSystem();` — Finds or loads the base niagara system all layouts use
- L137 _protected member_ `static FOnSubsystemInitialized OnSubsystemInitializedDelegate;`
- L140 _protected member_ `static FOnClonerSetEnabled OnClonerSetEnabledDelegate;` — Delegate to change state of cloners in a world
- L142 _protected member_ `static FOnGetSceneTreeResolver OnGetSceneTreeResolverDelegate;`
- L145 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L146 _protected prototype_ `virtual void Deinitialize() override;`
- L149 _protected prototype_ `void ScanForRegistrableClasses();`
- L151 _protected prototype_ `void OnLevelCleanup(ULevel* InLevel);`
- L152 _protected prototype_ `void OnWorldCleanup(UWorld* InWorld, bool, bool bInCleanupResources);`
- L156 _protected member_ `TMap<FName, TSubclassOf<UCEClonerLayoutBase>> LayoutClasses;` — `UPROPERTY()` — Linking name to the layout class
- L160 _protected member_ `TMap<FName, TObjectPtr<UNiagaraSystem>> TemplateNiagaraSystems;` — `UPROPERTY()` — Layout name to their template niagara systems
- L164 _protected member_ `TObjectPtr<UNiagaraSystem> BaseNiagaraSystem;` — `UPROPERTY()` — Parent niagara system that all layouts are based from to validate user parameters
- L168 _protected member_ `TMap<FName, TSubclassOf<UCEClonerExtensionBase>> ExtensionClasses;` — `UPROPERTY()` — Linking name to the extension class
- L171 _protected member_ `TMap<FName, TFunction<TSharedRef<ICEClonerAttachmentTreeBehavior>()>> TreeBehaviorCreators;` — Used to create a cloner tree attachment behavior
- L174 _protected member_ `TMap<TObjectKey<ULevel>, TSharedRef<ICEClonerSceneTreeCustomResolver>> LevelCustomResolvers;` — Used to gather ordered actors based on parent
- L177 _protected member_ `double LastNotificationTime = 0.0;`

#### enum `UCEClonerSubsystem::ECEClonerActionFlags`  
`enum class ECEClonerActionFlags : uint8`  
_L29-35_
- L31 _public enumerator_ `None`
- L32 _public enumerator_ `ShouldTransact = 1 << 0`
- L33 _public enumerator_ `ShouldSelect = 1 << 1`
- L34 _public enumerator_ `All = ShouldTransact | ShouldSelect`

#### Free symbols / members of external scopes

- L25 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSubsystemInitialized) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnClonerSetEnabled, const UWorld* , bool , bool ) public: enum class ECEClonerActionFlags : uint8 { None, ShouldTransact = 1 << 0, ShouldSelect = 1 << 1, All = ShouldTransact | ShouldSelect, };`
- L26 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnClonerSetEnabled, const UWorld* , bool , bool ) public: enum class ECEClonerActionFlags : uint8 { None, ShouldTransact = 1 << 0, ShouldSelect = 1 << 1, All = ShouldTransact | ShouldSelect, };`
- L47 _delegate_ `DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<ICEClonerSceneTreeCustomResolver>, FOnGetSceneTreeResolver, ULevel* ) static FOnGetSceneTreeResolver::RegistrationType& OnGetSceneTreeResolver() { return OnGetSceneTreeResolverDelegate; } static UCEClonerSubsystem* Get();`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Subsystems/CEEffectorSubsystem.h` (Public)


#### class `UCEEffectorSubsystem`  
`class UCEEffectorSubsystem : public UEngineSubsystem, public FTickableGameObject`  
_L15-127_
- reflection: `UCLASS()`
- inherits: `UEngineSubsystem,FTickableGameObject`
- L24 _public function_ `static FOnSubsystemInitialized::RegistrationType& OnSubsystemInitialized()`
- L29 _public function_ `static FOnEffectorIdentifierChanged::RegistrationType& OnEffectorIdentifierChanged()`
- L34 _public function_ `static FOnEffectorSetEnabled::RegistrationType& OnEffectorSetEnabled()`
- L40 _public prototype_ `static UCEEffectorSubsystem* Get();` — Get this subsystem instance
- L43 _public prototype_ `bool RegisterChannelEffector(UCEEffectorComponent* InEffector);` — Registers an effector actor to use it within a effector channel
- L46 _public prototype_ `bool UnregisterChannelEffector(UCEEffectorComponent* InEffector);` — Unregister an effector actor used within a effector channel
- L49 _public prototype_ `UCEEffectorComponent* GetEffectorByChannelIdentifier(int32 InIdentifier) const;` — Get the effector using this channel identifier
- L51 _public prototype_ `bool RegisterExtensionClass(UClass* InClass);`
- L53 _public prototype_ `bool UnregisterExtensionClass(UClass* InClass);`
- L55 _public prototype_ `bool IsExtensionClassRegistered(UClass* InClass) const;`
- L58 _public function_ `template<typename InExtensionClass> TSet<FName> GetExtensionNames() const`
- L63 _public prototype_ `TSet<FName> GetExtensionNames(TSubclassOf<UCEEffectorExtensionBase> InExtensionClass) const;`
- L66 _public function_ `template<typename InExtensionClass> TSet<TSubclassOf<UCEEffectorExtensionBase>> GetExtensionClasses() const`
- L71 _public prototype_ `TSet<TSubclassOf<UCEEffectorExtensionBase>> GetExtensionClasses(TSubclassOf<UCEEffectorExtensionBase> InExtensionClass) const;`
- L74 _public prototype_ `FName FindExtensionName(TSubclassOf<UCEEffectorExtensionBase> InClass) const;` — Based on a extension class, find extension name
- L77 _public prototype_ `UCEEffectorExtensionBase* CreateNewExtension(FName InExtensionName, UCEEffectorComponent* InEffector);` — Creates a new extension instance for an effector
- L80 _public prototype_ `void SetEffectorsEnabled(const TSet<UCEEffectorComponent*>& InEffectors, bool bInEnable, bool bInShouldTransact);` — Set effectors state and optionally transact
- L83 _public prototype_ `void SetLevelEffectorsEnabled(const UWorld* InWorld, bool bInEnable, bool bInShouldTransact);` — Set effectors state in world and optionally transact
- L86 _protected member_ `static constexpr TCHAR DataChannelAssetPath[] = TEXT("/Sc`
- L89 _protected member_ `static FOnSubsystemInitialized OnSubsystemInitializedDelegate;` — Broadcasted when this subsystem is initialized
- L92 _protected member_ `static FOnEffectorIdentifierChanged OnEffectorIdentifierChangedDelegate;` — Broadcasted when this effector identifier changed to update linked cloners
- L95 _protected member_ `static FOnEffectorSetEnabled OnEffectorSetEnabledDelegate;` — Delegate to change state of effectors in a world
- L98 _protected prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;`
- L99 _protected prototype_ `virtual void Deinitialize() override;`
- L103 _protected prototype_ `virtual TStatId GetStatId() const override;`
- L104 _protected prototype_ `virtual void Tick(float InDeltaSeconds) override;`
- L105 _protected prototype_ `virtual bool IsTickable() const override;`
- L106 _protected function_ `virtual bool IsTickableInEditor() const override`
- L107 _protected function_ `virtual ETickableTickType GetTickableTickType() const override`
- L111 _protected prototype_ `void UpdateEffectorChannel(const UWorld* InWorld);` — Updates all registered effectors
- L114 _protected prototype_ `void ScanForRegistrableClasses();` — Scan classes and registers them
- L118 _protected member_ `TMap<FName, TSubclassOf<UCEEffectorExtensionBase>> ExtensionClasses;` — `UPROPERTY()` — Linking name to the extension class
- L122 _protected member_ `TArray<TWeakObjectPtr<UCEEffectorComponent>> EffectorsWeak;` — `UPROPERTY()` — Ordered effectors included in this channel
- L126 _protected member_ `TObjectPtr<UNiagaraDataChannelAsset> EffectorDataChannelAsset;` — `UPROPERTY()` — This represents the data channel structure for effector

#### Free symbols / members of external scopes

- L19 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnSubsystemInitialized) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEffectorIdentifierChanged, UCEEffectorComponent* , int32 , int32 ) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEffectorSetEnabled, const UWorld* , bool , bool ) public: static FOnSubsystemInitialized::RegistrationType& OnSubsystemInitialized() { return OnSubsystemInitializedDelegate; } static FOnEffectorIdentifierChanged::RegistrationType& OnEffectorIdentifierChanged() { return OnEffectorIdentifierChangedDelegate; } static FOnEffectorSetEnabled::RegistrationType& OnEffectorSetEnabled() { return OnEffectorSetEnabledDelegate; } static UCEEffectorSubsystem* Get();`
- L20 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEffectorIdentifierChanged, UCEEffectorComponent* , int32 , int32 ) DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEffectorSetEnabled, const UWorld* , bool , bool ) public: static FOnSubsystemInitialized::RegistrationType& OnSubsystemInitialized() { return OnSubsystemInitializedDelegate; } static FOnEffectorIdentifierChanged::RegistrationType& OnEffectorIdentifierChanged() { return OnEffectorIdentifierChangedDelegate; } static FOnEffectorSetEnabled::RegistrationType& OnEffectorSetEnabled() { return OnEffectorSetEnabledDelegate; } static UCEEffectorSubsystem* Get();`
- L21 _delegate_ `DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnEffectorSetEnabled, const UWorld* , bool , bool ) public: static FOnSubsystemInitialized::RegistrationType& OnSubsystemInitialized() { return OnSubsystemInitializedDelegate; } static FOnEffectorIdentifierChanged::RegistrationType& OnEffectorIdentifierChanged() { return OnEffectorIdentifierChangedDelegate; } static FOnEffectorSetEnabled::RegistrationType& OnEffectorSetEnabled() { return OnEffectorSetEnabledDelegate; } static UCEEffectorSubsystem* Get();`

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Utilities/CEClonerEffectorUtilities.h` (Public)


#### Free symbols / members of external scopes

- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace ClonerEffector` (scope `UE`)
- L13 _namespace_ `namespace Utilities` (scope `UE::ClonerEffector`)
- L16 _prototype_ `const FText& GetMaterialWarningText();` (scope `UE::ClonerEffector::Utilities`)
- L19 _prototype_ `void ShowWarning(const FText& InWarning);` (scope `UE::ClonerEffector::Utilities`) — Show material warning notification when missing niagara usage flag
- L23 _prototype_ `bool IsMaterialDirtyable(const UMaterialInterface* InMaterial);` (scope `UE::ClonerEffector::Utilities`) — Only materials transient or part of the content folder can be dirtied, engine or plugins cannot
- L26 _prototype_ `bool IsMaterialUsageFlagSet(const UMaterialInterface* InMaterial);` (scope `UE::ClonerEffector::Utilities`) — Check if material has niagara usage flag set
- L29 _prototype_ `bool FilterSupportedMaterials(TArray<TWeakObjectPtr<UMaterialInterface>>& InMaterials, TArray<TWeakObjectPtr<UMaterialInterface>>& OutUnsetMaterials, UMaterialInterface* InDefaultMaterial);` (scope `UE::ClonerEffector::Utilities`) — Replaces all unsupported material by default material, gathers unset materials that needs recompiling with proper flags
- L32 _prototype_ `bool FilterSupportedMaterial(UMaterialInterface*& InMaterial, UMaterialInterface* InDefaultMaterial);` (scope `UE::ClonerEffector::Utilities`) — Check if a material is supported otherwise replaces it with default material
- L35 _prototype_ `void SetActorVisibility(AActor* InActor, bool bInVisibility, ECEClonerActorVisibility InTarget = ECEClonerActorVisibility::All);` (scope `UE::ClonerEffector::Utilities`) — Set specific actor visibility
- L38 _prototype_ `AActor* FindClonerActor(AActor* InActor);` (scope `UE::ClonerEffector::Utilities`) — Look parent attach actor until first cloner component is found

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Utilities/CEClonerLibrary.h` (Public)


#### class `UCEClonerLibrary`  
`class UCEClonerLibrary : public UBlueprintFunctionLibrary`  
_L17-86_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Cloner Library")`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint operations for cloner
- L27 _public prototype_ `static void GetClonerLayoutClasses(TSet<TSubclassOf<UCEClonerLayoutBase>>& OutLayoutClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Cloner|Utility")` — Retrieves all layout classes available for a cloner @param OutLayoutClasses [Out] Layout classes available
- L34 _public prototype_ `static void GetClonerExtensionClasses(TSet<TSubclassOf<UCEClonerExtensionBase>>& OutExtensionClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Cloner|Utility")` — Retrieves all extension classes available for a cloner @param OutExtensionClasses [Out] Extension classes available
- L43 _public prototype_ `static bool GetClonerLayoutName(TSubclassOf<UCEClonerLayoutBase> InLayoutClass, FName& OutLayoutName);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Cloner|Utility")` — Retrieves the layout name from a layout class @param InLayoutClass Layout class to get the name from @param OutLayoutName [Out] Layout name @return true when the layout name was retrieved
- L51 _public prototype_ `static bool GetClonerLayoutNames(TSet<FName>& OutLayoutNames);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Cloner|Utility")` — Retrieves all the layout names @param OutLayoutNames [Out] Layout names @return true when the layout names were retrieved
- L60 _public prototype_ `static bool GetClonerLayoutClass(FName InLayoutName, TSubclassOf<UCEClonerLayoutBase>& OutLayoutClass);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Cloner|Utility")` — Retrieves the layout class from a layout name @param InLayoutName Layout name to get the class from @param OutLayoutClass [Out] Layout class @return true when the layout class was retrieved
- L73 _public prototype_ `static void SetClonerLayoutByClass(const UObject* InWorldContext, FLatentActionInfo InLatentInfo, UCEClonerComponent* InCloner, TSubclassOf<UCEClonerLayoutBase> InLayoutClass, bool& bOutSuccess, UCEClonerLayoutBase*& OutLayout);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Cloner|Utility", meta=(Latent, LatentInfo="InLatentInfo", WorldContext="InWorldContext"))` — Sets the active layout of a cloner and wait until the layout is loaded and active @param InWorldContext World context object @param InLatentInfo Latent action info @param InCloner Target cloner component @param InLayoutClass Cloner layout class @param bOutSuccess [Out] True when the layout class is set @param OutLayout [Out] Layout object corresponding to the layout class
- L85 _public prototype_ `static void SetClonerLayoutByName(const UObject* InWorldContext, FLatentActionInfo InLatentInfo, UCEClonerComponent* InCloner, FName InLayoutName, bool& bOutSuccess, UCEClonerLayoutBase*& OutLayout);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Cloner|Utility", meta=(Latent, LatentInfo="InLatentInfo", WorldContext="InWorldContext"))` — Sets the active layout of a cloner and wait until the layout is loaded and active @param InWorldContext World context object @param InLatentInfo Latent action info @param InCloner Target cloner component @param InLayoutName Cloner layout name @param bOutSuccess [Out] True when the layout class is set @param OutLayout [Out] Layout object corresponding to the layout class

### `Plugins/VirtualProduction/ClonerEffector/Source/ClonerEffector/Public/Utilities/CEEffectorLibrary.h` (Public)


#### class `UCEEffectorLibrary`  
`class UCEEffectorLibrary : public UBlueprintFunctionLibrary`  
_L17-49_
- reflection: `UCLASS(MinimalAPI, DisplayName="Motion Design Effector Library")`
- inherits: `UBlueprintFunctionLibrary`
- desc: Blueprint operations for effector
- L27 _public prototype_ `static void GetEffectorModeClasses(TSet<TSubclassOf<UCEEffectorModeBase>>& OutModeClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Effector|Utility")` — Retrieves all mode classes available for an effector @param OutModeClasses [Out] Available mode classes
- L34 _public prototype_ `static void GetEffectorTypeClasses(TSet<TSubclassOf<UCEEffectorTypeBase>>& OutTypeClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Effector|Utility")` — Retrieves all type classes available for an effector @param OutTypeClasses [Out] Available type classes
- L41 _public prototype_ `static void GetEffectorTypeNames(TSet<FName>& OutTypeNames);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Effector|Utility")` — Retrieves all type classes available for an effector @param OutTypeNames [Out] Available type names
- L48 _public prototype_ `static void GetEffectorEffectClasses(TSet<TSubclassOf<UCEEffectorEffectBase>>& OutEffectClasses);` — `UFUNCTION(BlueprintCallable, Category="Motion Design|Effector|Utility")` — Retrieves all effect classes available for an effector @param OutEffectClasses [Out] Available effect classes
