# Plugins / AudioMotorSim

- module root: `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim`
- headers: 8; symbols: 96
- symbol kinds: class=7, externvar=1, function=11, macro=2, member=34, namespace=2, prototype=34, struct=5
- PublicDependencyModuleNames: Core, CoreUObject, Engine

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/AudioMotorModelComponent.h` (Public)


#### struct `FMotorSimEntry`  
`struct FMotorSimEntry`  
_L17-26_
- reflection: `USTRUCT(BlueprintType)`
- L22 _public member_ `TScriptInterface<IAudioMotorSim> Sim;` — `UPROPERTY(BlueprintReadOnly, Category = "MotorSim")`
- L25 _public member_ `int32 SortOrder = 0;` — `UPROPERTY(BlueprintReadOnly, Category = "MotorSim")`

#### class `UAudioMotorModelComponent`  
`class UAudioMotorModelComponent : public UActorComponent`  
_L29-112_
- reflection: `UCLASS(MinimalAPI, ClassGroup = AudioMotorSim, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L33 _public prototype_ `virtual void BeginPlay() override;`
- L36 _public member_ `TArray<FMotorSimEntry> SimComponents;` — `UPROPERTY(BlueprintReadOnly, Transient, Category = "Model")`
- L39 _public member_ `TArray<TScriptInterface<IAudioMotorSimOutput>> AudioComponents;` — `UPROPERTY(Transient)`
- L42 _public prototype_ `virtual void Update(const FAudioMotorSimInputContext& Input);` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L45 _public prototype_ `virtual void Reset();` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L48 _public prototype_ `virtual void StartOutput();` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L51 _public prototype_ `virtual void StopOutput();` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L54 _public prototype_ `void AddMotorAudioComponent(TScriptInterface<IAudioMotorSimOutput> InComponent);` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L57 _public prototype_ `void RemoveMotorAudioComponent(TScriptInterface<IAudioMotorSimOutput> InComponent);` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L60 _public prototype_ `void AddMotorSimComponent(TScriptInterface<IAudioMotorSim> InComponent, const int32 SortOrder = 0);` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L63 _public prototype_ `void RemoveMotorSimComponent(TScriptInterface<IAudioMotorSim> InComponent);` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L66 _public prototype_ `void RemoveAllMotorSimComponents();` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L69 _public prototype_ `void ConfigureMotorSimComponents(const TArray<FInstancedStruct>& InConfigData);` — `UFUNCTION(BlueprintCallable, Category = MotorModel)`
- L72 _public function_ `float GetRpm() const` — `UFUNCTION(BlueprintPure, Category = State)`
- L75 _public function_ `int32 GetGear() const` — `UFUNCTION(BlueprintPure, Category = State)`
- L78 _public function_ `FAudioMotorSimRuntimeContext GetRuntimeInfo() const` — `UFUNCTION(BlueprintPure, Category = State)`
- L81 _public function_ `const FAudioMotorSimInputContext& GetCachedInputData() const` — `UFUNCTION(BlueprintPure, Category = State)`
- L84 _public function_ `template<typename T> TObjectPtr<T> GetMotorSimOfType()`
- L103 _public prototype_ `void DebugPrintRuntimeInfo() const;`
- L104 _public prototype_ `void DebugPrintInputContext() const;`
- L108 _private member_ `FAudioMotorSimRuntimeContext CachedRuntimeContext;`
- L110 _private member_ `FAudioMotorSimInputContext CachedInputContext;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOMOTORSIM_API`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/AudioMotorSimConfigData.h` (Public)


#### struct `FAudioMotorSimConfigData`  
`struct FAudioMotorSimConfigData`  
_L11-14_
- reflection: `USTRUCT(BlueprintType)`
- desc: Base struct containing configuration data for motor sim components

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/AudioMotorSimLogs.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogAudioMotorSim, Log, All);`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/AudioMotorSimModule.h` (Public)
_(no declarations extracted)_

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/AudioMotorSimTypes.h` (Public)


#### struct `FAudioMotorSimInputContext`  
`struct FAudioMotorSimInputContext`  
_L8-67_
- reflection: `USTRUCT(BlueprintType)`
- desc: collection of properties to be filled out by the vehicle in order to update the motor sim
- L14 _public member_ `float DeltaTime = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpdateContext")` — Time in Seonds
- L18 _public member_ `float Speed = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")` — Current speed of the vehicle in any direction
- L22 _public member_ `float ForwardSpeed = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")` — Current speed of the vehicle relative to its forward direction
- L26 _public member_ `float SideSpeed = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")` — absolute value of the speed of the vehicle relative to its right direction
- L30 _public member_ `float UpSpeed = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")` — Current speed of the vehicle along the z-axis
- L34 _public member_ `float Throttle = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — normalized input representing the player wanting to accelerate [-1, 1]
- L38 _public member_ `float Brake = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")` — normalized input representing the player wanting to slow down [0, 1]
- L42 _public member_ `float SurfaceFrictionModifier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — scaling to apply to any behaviors that model surface friction
- L46 _public member_ `float MotorFrictionModifier = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — scaling to apply to any behaviors that model internal motor friction
- L50 _public member_ `float Boost = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — normalized input representing additional thrust beyond normal driving behaviors
- L54 _public member_ `bool bDriving = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — whether a player can drive the vehicle right now
- L58 _public member_ `bool bGrounded = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — whether the vehicle is firmly on the ground
- L62 _public member_ `bool bCanShift = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — whether the motor can freely shift gears
- L66 _public member_ `bool bClutchEngaged = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — when true, signals that the gears are temporarily disconnected from the motor

#### struct `FAudioMotorSimRuntimeContext`  
`struct FAudioMotorSimRuntimeContext`  
_L71-98_
- reflection: `USTRUCT(BlueprintType)`
- desc: properties that represent the current state of the motor sim, and persist between updates
- L77 _public member_ `bool bShifting = false;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — true while the motor is performing a gear shift
- L81 _public member_ `int32 Gear = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — which gear the motor is in, if it uses gears
- L85 _public member_ `float VirtualSpeedKmh = 0.f;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State", meta = (ForceUnits = "km/h"))` — the virtual speed calculated by the Motor Physics Simulation
- L89 _public member_ `float Rpm = 0.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — normalized RPM [0-1] of the motor
- L93 _public member_ `float Volume = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — volume to set on the output component
- L97 _public member_ `float Pitch = 1.f;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")` — pitch to set on the output component

#### Free symbols / members of external scopes

- L100 _namespace_ `namespace AudioMotorSim`
- L102 _function_ `inline float CmsToKmh(const float InSpeed)` (scope `AudioMotorSim`)
- L103 _function_ `inline float KmhToCms(const float InSpeed)` (scope `AudioMotorSim`)

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/IAudioMotorModelDebugger.h` (Public)


#### class `IAudioMotorModelDebugger`  
`class IAudioMotorModelDebugger : public IModularFeature`  
_L14-21_
- inherits: `IModularFeature`
- L17 _public prototype_ `virtual ~IAudioMotorModelDebugger() = default;`
- L19 _public prototype_ `virtual void RegisterComponentWithDebugger(class UAudioMotorModelComponent* MotorModelComponent) = 0;`
- L20 _public prototype_ `virtual void SendAdditionalDebugData(UObject* Object, const FInstancedStruct& InData) = 0;`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace AudioMotorModelDebugger`
- L11 _externvar_ `extern const FLazyName DebuggerModularFeatureName;` (scope `AudioMotorModelDebugger`)

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/IAudioMotorSim.h` (Public)


#### struct `FAudioMotorSimDebugDataBase`  
`struct FAudioMotorSimDebugDataBase`  
_L19-24_
- reflection: `USTRUCT()`
- L23 _public member_ `TMap<FName, double> ParameterValues;`

#### class `UAudioMotorSim`  
`class UAudioMotorSim : public UInterface`  
_L27-30_
- reflection: `UINTERFACE(MinimalAPI, BlueprintType, NotBlueprintable)`
- inherits: `UInterface`

#### class `IAudioMotorSim`  
`class IAudioMotorSim`  
_L32-50_
- L37 _public prototype_ `virtual void Init() = 0;`
- L39 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) = 0;`
- L43 _public function_ `virtual void Reset()` — `UFUNCTION(BlueprintCallable, Category = "AudioMotorSim")` — Use to reset any state that might be desired. Will be called automatically if the entire MotorSim is Reset, or call it manually
- L46 _public function_ `virtual bool GetEnabled()` — `UFUNCTION(BlueprintCallable, Category = "AudioMotorSim")`
- L49 _public function_ `virtual void ConfigMotorSim(const FInstancedStruct& InConfigData)` — `UFUNCTION(BlueprintCallable, Category = "AudioMotorSim")`

#### class `UAudioMotorSimComponent`  
`class UAudioMotorSimComponent : public UActorComponent, public IAudioMotorSim`  
_L53-120_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable, EditInlineNew, Category = "AudioMotorSim", hideCategories = (Activation, AssetUserData, ComponentReplication, Cooking, Navigation, Replication, Tags, Variable), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent,IAudioMotorSim`
- L58 _public prototype_ `UAudioMotorSimComponent(const FObjectInitializer& ObjectInitializer);`
- L60 _public prototype_ `virtual void BeginPlay() override;`
- L62 _public prototype_ `virtual void Init() override;`
- L64 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) override;`
- L66 _public prototype_ `virtual void Reset() override;`
- L68 _public function_ `virtual bool GetEnabled() override`
- L76 _public prototype_ `bool BP_Update(UPARAM(ref) FAudioMotorSimInputContext& Input, UPARAM(ref) FAudioMotorSimRuntimeContext& RuntimeInfo);` — `UFUNCTION(BlueprintImplementableEvent, Category = "AudioMotorSim", DisplayName = "OnUpdate")` — Called every tick that this component is being updated. Use "Set Members in Struct" to update values for future components in the chain. The return value does nothing. @param Input			Holds values which are not saved between update frames which represent input to the simulation @param RuntimeInfo	Holds values which are saved between update frames to represent the output or state of the simulation @return				Vestigial, does nothing.
- L80 _public prototype_ `void BP_Reset();` — `UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="AudioMotorSim", DisplayName = "OnReset")` — Called when something Resets this component
- L84 _public prototype_ `void SetEnabled(bool bNewEnabled);` — `UFUNCTION(BlueprintCallable, Category="AudioMotorSim")` — controls whether this will run its update function
- L86 _public prototype_ `virtual void ConfigMotorSim(const FInstancedStruct& InConfigData) override;`
- L91 _public member_ `FAudioMotorSimInputContext CachedInput;` — `UPROPERTY(BlueprintReadOnly, Category = "DebugInfo")` — Input data after running this component
- L95 _public member_ `FAudioMotorSimRuntimeContext CachedRuntimeInfo;` — `UPROPERTY(BlueprintReadOnly, Category = "DebugInfo")` — runtime info after running this component
- L97 _public prototype_ `virtual void GetCachedData(FAudioMotorSimInputContext& OutInput, FAudioMotorSimRuntimeContext& OutRuntimeInfo);`
- L102 _public member_ `bool bEnabled = true;` — `UPROPERTY(BlueprintReadOnly, Category="AudioMotorSim")` — will only update if enabled
- L107 _protected prototype_ `bool ShouldCollectDebugData() const;`
- L108 _protected member_ `FInstancedStruct CachedDebugData;`
- L114 _private prototype_ `void SendCachedDebugData();`
- L115 _private member_ `TArray<IAudioMotorModelDebugger*> MotorModelDebuggers;`
- L116 _private member_ `bool bCollectDebugData = false;`
- L119 _private member_ `bool bUpdateImplemented = true;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API AUDIOMOTORSIM_API`

### `Plugins/Runtime/AudioMotorSim/Source/AudioMotorSim/Public/IAudioMotorSimOutput.h` (Public)


#### class `UAudioMotorSimOutput`  
`class UAudioMotorSimOutput : public UInterface`  
_L11-14_
- reflection: `UINTERFACE(MinimalAPI)`
- inherits: `UInterface`

#### class `IAudioMotorSimOutput`  
`class IAudioMotorSimOutput`  
_L16-25_
- L21 _public prototype_ `virtual void Update(FAudioMotorSimInputContext& Input, FAudioMotorSimRuntimeContext& RuntimeInfo) = 0;`
- L23 _public prototype_ `virtual void StartOutput() = 0;`
- L24 _public prototype_ `virtual void StopOutput() = 0;`
