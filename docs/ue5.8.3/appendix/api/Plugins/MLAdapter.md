# Plugins / MLAdapter

- module root: `Plugins/AI/MLAdapter/Source/MLAdapter`
- headers: 32; symbols: 619
- symbol kinds: class=21, delegate=5, enum=5, enumerator=19, function=94, macro=12, member=166, namespace=10, prototype=260, struct=19, typedef=4, union=1, variable=3
- PrivateDependencyModuleNames: DeveloperSettings, EditorFramework, RPCLib, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, CoreUObject, Engine, EnhancedInput, GameplayAbilities, GameplayTags, InputCore, Json, JsonUtilities, NNE

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Actuators/MLAdapterActuator.h` (Public)


#### class `UMLAdapterActuator`  
`class UMLAdapterActuator : public UMLAdapterAgentElement`  
_L18-40_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UMLAdapterAgentElement`
- desc: Allows an agent to take an action in the game world.
- L23 _public prototype_ `UMLAdapterActuator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _public prototype_ `virtual void PostInitProperties() override;`
- L28 _public function_ `virtual void Act(const float DeltaTime)` — Takes an action in the game based on earlier digested data.
- L31 _public function_ `virtual void DigestInputData(FMLAdapterMemoryReader& ValueStream)` — Stores data from the ValueStream to be later used by Act.
- L39 _protected member_ `mutable FCriticalSection ActionCS;` — This needs to be used in every implementation of Act and DigestInputData to ensure that shared state is not be accessed simultaneously by the game thread and the RPC server thread.

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Actuators/MLAdapterActuator_Camera.h` (Public)


#### class `UMLAdapterActuator_Camera`  
`class UMLAdapterActuator_Camera : public UMLAdapterActuator`  
_L13-51_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMLAdapterActuator`
- desc: Allows an agent to rotate the camera.
- L18 _public prototype_ `UMLAdapterActuator_Camera(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L20 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L22 _public prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L25 _public prototype_ `virtual void Act(const float DeltaTime) override;` — Rotates the camera.
- L28 _public prototype_ `virtual void DigestInputData(FMLAdapterMemoryReader& ValueStream) override;` — Stores data in HeadingVector or HeadingRotator depending on bVectorMode.
- L33 _protected prototype_ `virtual void DescribeSelfToGameplayDebugger(class FGameplayDebuggerCategory& DebuggerCategory) const override;`
- L38 _protected member_ `FRotator HeadingRotator;` — `UPROPERTY()` — Stores the direction to point the camera as a rotator.
- L42 _protected member_ `FVector HeadingVector;` — `UPROPERTY()` — Stores the direction to point the camera as a vector.
- L46 _protected member_ `uint32 bConsumeData : 1;` — `UPROPERTY()` — If true, acting will reinitialize the HeadingRotator/Vector after reading them.
- L50 _protected member_ `uint32 bVectorMode : 1;` — `UPROPERTY()` — If true, use the HeadingVector. Otherwise, use the HeadingRotator.

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Actuators/MLAdapterActuator_EnhancedInput.h` (Public)


#### class `UMLAdapterActuator_EnhancedInput`  
`class UMLAdapterActuator_EnhancedInput : public UMLAdapterActuator`  
_L14-42_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMLAdapterActuator`
- desc: Allows an agent to simulate player input via the UEnhancedPlayerInput subsystem.
- L19 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L21 _public prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L24 _public prototype_ `virtual void Act(const float DeltaTime) override;` — Performs one or more actions on the input component.
- L27 _public prototype_ `virtual void DigestInputData(FMLAdapterMemoryReader& ValueStream) override;` — Stores data in InputData to be later injected into actions.
- L30 _protected member_ `TArray<float> InputData;`
- L38 _protected member_ `TArray<TObjectPtr<UInputAction>> TrackedActions;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MLAdapter)` — The actions that this actuator is allowed to inject data into. Modifying this list after using the actuator is unsupported because the InputData is injected into the actions based on the ordering in this array. Changing this could cause data to be injected incorrectly.
- L41 _protected member_ `bool bClearActionOnUse = true;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MLAdapter)`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Actuators/MLAdapterActuator_InputKey.h` (Public)


#### class `UMLAdapterActuator_InputKey`  
`class UMLAdapterActuator_InputKey : public UMLAdapterActuator`  
_L12-40_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMLAdapterActuator`
- desc: Allows an agent to directly inject key presses into its avatar's input component.
- L17 _public prototype_ `UMLAdapterActuator_InputKey(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L19 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L21 _public prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L24 _public prototype_ `virtual void Act(const float DeltaTime) override;` — Presses the keys stored in "KeysToPress"
- L26 _public prototype_ `virtual void DigestInputData(FMLAdapterMemoryReader& ValueStream) override;`
- L29 _protected member_ `TArray<TTuple<FKey, FName>> RegisteredKeys;`
- L31 _protected member_ `TArray<int32> KeysToPress;`
- L33 _protected member_ `TBitArray<> PressedKeys;`
- L35 _protected member_ `TArray<float> InputData;`
- L39 _protected member_ `bool bIsMultiBinary;` — temporary solution. If true then the incoming actions are expected to be MultiBinary, if false (default) the actions will be treated as Discrete

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Agents/MLAdapterAgent.h` (Public)


#### struct `FMLAdapterParameterMap`  
`struct FMLAdapterParameterMap`  
_L23-29_
- reflection: `USTRUCT()`
- desc: Provides a serializable mapping from parameter name to value that is used to configure sensors & actuators.
- L28 _public member_ `TMap<FName, FString> Params;` — `UPROPERTY(EditAnywhere, Category = MLAdapter)`

#### struct `FMLAdapterAgentConfig`  
`struct FMLAdapterAgentConfig`  
_L33-58_
- reflection: `USTRUCT()`
- desc: A serializable config for an agent. Used in the external API to define agents.
- L38 _public member_ `TMap<FName, FMLAdapterParameterMap> Sensors;` — `UPROPERTY()`
- L41 _public member_ `TMap<FName, FMLAdapterParameterMap> Actuators;` — `UPROPERTY()`
- L44 _public member_ `FName AvatarClassName;` — `UPROPERTY()`
- L47 _public member_ `FName AgentClassName;` — `UPROPERTY()`
- L51 _public member_ `bool bAvatarClassExact = false;` — `UPROPERTY()` — If set to true, won't accept child classes of the AvatarClass.
- L54 _public member_ `bool bAutoRequestNewAvatarUponClearingPrev = true;` — `UPROPERTY()`
- L56 _public prototype_ `FMLAdapterParameterMap& AddSensor(const FName SensorName, FMLAdapterParameterMap&& Parameters = FMLAdapterParameterMap());`
- L57 _public prototype_ `FMLAdapterParameterMap& AddActuator(const FName ActuatorName, FMLAdapterParameterMap&& Parameters = FMLAdapterParameterMap());`

#### class `UMLAdapterAgent`  
`class UMLAdapterAgent : public UObject`  
_L74-245_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UObject`
- desc: An agent capable of controlling a single avatar (e.g. a Pawn or Controller). Contains sensors for perceiving information about the environment and actuators for taking actions in the game.
- L79 _public prototype_ `UMLAdapterAgent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L82 _public prototype_ `virtual void PostInitProperties() override;` — Perform initial setup for blueprint spawned agents.
- L85 _public prototype_ `virtual void BeginDestroy() override;` — Shutdown all the sensors and actuators and cleanup references to the avatar.
- L88 _public prototype_ `virtual bool RegisterSensor(UMLAdapterSensor& Sensor);` — Add a sensor to this agent. Returns true if the sensor was successfully added.
- L91 _public prototype_ `virtual void Sense(const float DeltaTime);` — Updates all the sensors that are configured as 'IsPolling'.
- L97 _public prototype_ `virtual void Think(const float DeltaTime);` — Decide what action to take based on the current observations. @see UMLAdapterAgent_Inference for an agent that implements this.
- L100 _public prototype_ `virtual void Act(const float DeltaTime);` — Tick all of the agent's actuators.
- L103 _public prototype_ `virtual void DigestActions(FMLAdapterMemoryReader& ValueStream);` — Move data into the actuators for the next time Act is called.
- L106 _public function_ `FMLAdapter::FAgentID GetAgentID() const` — Get this agent's ID.
- L109 _public function_ `APawn* GetPawn()` — Get the Pawn this agent is controlling.
- L112 _public function_ `const APawn* GetPawn() const` — Get the Pawn this agent is controlling.
- L115 _public function_ `AController* GetController()` — Get the Controller this agent is controlling.
- L118 _public function_ `const AController* GetController() const` — Get the Controller this agent is controlling.
- L120 _public function_ `TArray<TObjectPtr<UMLAdapterSensor>>::TConstIterator GetSensorsConstIterator() const`
- L121 _public function_ `TArray<TObjectPtr<UMLAdapterActuator>>::TConstIterator GetActuatorsConstIterator() const`
- L124 _public prototype_ `virtual float GetReward() const;` — If the avatar is a controller, then get the current score from the controller's player state.
- L127 _public prototype_ `virtual bool IsDone() const;` — The agent is done if its avatar has been destroyed and it can't request a new one.
- L130 _public function_ `UMLAdapterActuator* GetActuator(const uint32 ActuatorID)` — Get the actuator with the given ID if this agent has it.
- L137 _public prototype_ `void DescribeSelfToGameplayDebugger(class FGameplayDebuggerCategory& DebuggerCategory) const;`
- L144 _protected prototype_ `virtual void OnAvatarDestroyed(AActor* DestroyedActor);` — `UFUNCTION()` — When the agent's avatar is destroyed, we need to cleanup callbacks and references to the avatar. Will request a new avatar if AgentConfig.bAutoRequestNewAvatarUponClearingPrev is true.
- L148 _protected prototype_ `void OnPawnControllerChanged(APawn* InPawn, AController* InController);` — `UFUNCTION()` — Will be bound to UGameInstance.OnPawnControllerChanged if current avatar is a pawn or a controller.
- L151 _protected prototype_ `virtual void OnPawnChanged(APawn* NewPawn, AController* InController);` — If the Pawn changed, we need to let all the sensors know.
- L156 _protected function_ `void SetAgentID(FMLAdapter::FAgentID NewAgentID)` — Set this agent's ID to its new ID.
- L161 _public prototype_ `void GetObservations(FMLAdapterMemoryWriter& Ar);` — Retrieve all the sensor data from the last time Sense was called.
- L164 _public function_ `const FMLAdapterAgentConfig& GetConfig() const` — Get this agent's current config. This will not be accurate if the agent was spawned from a blueprint.
- L167 _public prototype_ `virtual void Configure(const FMLAdapterAgentConfig& NewConfig);` — Setup this agent's avatar, sensors, and actuators. Typically used for agents spawned via RPC.
- L170 _public prototype_ `virtual void GetActionSpaceDescription(FMLAdapterSpaceDescription& OutSpaceDesc) const;` — Get the overall action space of this agent based on all its actuators. Used to determine the necessary output shape of the ML model.
- L173 _public prototype_ `virtual void GetObservationSpaceDescription(FMLAdapterSpaceDescription& OutSpaceDesc) const;` — Get the overall observation space of this agent based on all its sensors. Used to determine the necessary input shape of the ML model.
- L176 _public prototype_ `UMLAdapterSession& GetSession();` — Get the session that this agent belongs to.
- L179 _public prototype_ `virtual bool IsSuitableAvatar(AActor& InAvatar) const;` — Returns true is the given avatar can be controlled by this agent.
- L182 _public prototype_ `virtual void SetAvatar(AActor* InAvatar);` — Sets the avatar for this agent and all of its sensors and actuators. Registers callbacks.
- L185 _public function_ `AActor* GetAvatar() const` — Get the avatar this agent is controlling.
- L188 _public function_ `bool IsReady() const` — Returns true if this agent has an avatar set.
- L191 _public prototype_ `void EnableActionDuration(bool bEnable, float DurationSeconds);` — Enable/disable the action durations with the specified time duration in seconds.
- L194 _public prototype_ `bool TryResetActionDuration();` — Resets the action duration flag if it has elapsed. Returns false if not reset yet. Used with HasActionDurationElapsed by Manager.
- L197 _protected prototype_ `virtual void ShutDownSensorsAndActuators();`
- L201 _protected member_ `TArray<TObjectPtr<UMLAdapterSensor>> Sensors;` — `UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = MLAdapter)`
- L204 _protected member_ `TArray<TObjectPtr<UMLAdapterActuator>> Actuators;` — `UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = MLAdapter)`
- L207 _protected member_ `TSubclassOf<AActor> AvatarClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MLAdapter)`
- L211 _protected member_ `bool bEnableActionDuration = false;` — `UPROPERTY(EditAnywhere, Category = MLAdapter)` — If true, then agents won't be able to make a new decision until each action duration has elapsed.
- L215 _protected member_ `float ActionDurationSeconds = 0.1f;` — `UPROPERTY(EditAnywhere, Category = MLAdapter)` — How long should agents wait before they can change their action
- L219 _protected member_ `float CurrentActionDuration = 0.f;` — `UPROPERTY(VisibleInstanceOnly, Category = MLAdapter)` — How much time has the current action been executing
- L222 _protected member_ `bool bActionDurationElapsed = false;` — `UPROPERTY(VisibleInstanceOnly, Category = MLAdapter)`
- L224 _protected member_ `mutable FCriticalSection ActionDurationCS;`
- L228 _private member_ `TObjectPtr<AActor> Avatar;` — `UPROPERTY()`
- L231 _private member_ `TObjectPtr<AController> Controller;` — `UPROPERTY()`
- L234 _private member_ `TObjectPtr<APawn> Pawn;` — `UPROPERTY()`
- L236 _private member_ `FMLAdapter::FAgentID AgentID;`
- L238 _private member_ `FMLAdapterAgentConfig AgentConfig;`
- L241 _private member_ `uint32 bEverHadAvatar : 1;` — True if the agent ever had a Pawn. Otherwise, false.
- L244 _private member_ `uint32 bRegisteredForPawnControllerChange : 1;` — True if we have callbacks registered.

#### Free symbols / members of external scopes

- L60 _namespace_ `namespace FMLAdapterAgentHelpers`
- L63 _prototype_ `bool GetAsPawnAndController(AActor* Avatar, AController*& OutController, APawn*& OutPawn);` (scope `FMLAdapterAgentHelpers`) — Get the Pawn and Controller from the given Avatar if possible.
- L66 _prototype_ `bool GetAsPawnAndController(AActor* Avatar, TObjectPtr<AController>& OutController, TObjectPtr<APawn>& OutPawn);` (scope `FMLAdapterAgentHelpers`) — Get the Pawn and Controller from the given Avatar if possible.
- L132 _function_ `TObjectPtr<UMLAdapterActuator>* FoundActuator = Actuators.FindByPredicate([ActuatorID](const UMLAdapterActuator* Actuator) { return (Actuator->GetElementID() == ActuatorID); });` (scope `UMLAdapterAgent::GetActuator`)

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Agents/MLAdapterAgentElement.h` (Public)


#### class `UMLAdapterAgentElement`  
`class UMLAdapterAgentElement : public UObject`  
_L20-101_
- reflection: `UCLASS(abstract)`
- inherits: `UObject`
- desc: An agent element is any object that can be attached to an agent. Base class for UMLAdapterSensor and UMLAdapterActuator.
- L24 _public prototype_ `UMLAdapterAgentElement(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L25 _public prototype_ `virtual void PostInitProperties() override;`
- L28 _public prototype_ `const UMLAdapterAgent& GetAgent() const;` — Get the agent this element is attached to.
- L31 _public function_ `uint32 GetElementID() const` — Get the ID of this element.
- L34 _public function_ `const FString& GetNickname() const` — Get nickname of this element.
- L37 _public prototype_ `AActor* GetAvatar() const;` — @return The owning agent's avatar.
- L43 _public prototype_ `APawn* GetPawnAvatar() const;` — @return The pawn associated with the owning agent. If owning agent's avatar is a pawn then that gets retrieved, if not the function will check if it's a controller and if so retrieve its pawn.
- L49 _public prototype_ `AController* GetControllerAvatar() const;` — @return The controller associated with the owning agent. If owning agent's avatar is a controller then that gets retrieved, if not the function will check if it's a pawn and if so retrieve its controller.
- L56 _public prototype_ `bool GetPawnAndControllerAvatar(APawn*& OutPawn, AController*& OutController) const;` — Fetches both the pawn and the controller associated with the current agent. It's like both calling @see GetPawnAvatar and @see GetControllerAvatar. @return true if at least one of the fetched pair is non-null.
- L58 _public function_ `virtual FString GetDescription() const`
- L64 _public function_ `virtual void Shutdown()` — Called before object's destruction. Can be called as part of new agent config application when old actuator get destroyed.
- L66 _public function_ `void SetNickname(const FString& NewNickname)`
- L67 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params);`
- L68 _public function_ `virtual void OnAvatarSet(AActor* Avatar)`
- L70 _public prototype_ `virtual void UpdateSpaceDef();`
- L71 _public function_ `const FMLAdapter::FSpace& GetSpaceDef() const`
- L74 _public prototype_ `virtual void DescribeSelfToGameplayDebugger(class FGameplayDebuggerCategory& DebuggerCategory) const;`
- L78 _protected prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const PURE_VIRTUAL(UMLAdapterAgentElement::ConstructSpaceDef, return MakeShareable(new FMLAdapter::FSpace_Dummy()); );`
- L82 _protected member_ `FString Description;` — Can be queried by remote clients.
- L84 _protected member_ `TSharedRef<FMLAdapter::FSpace> SpaceDef;`
- L88 _protected member_ `uint32 ElementID;` — `UPROPERTY()` — @note This is not a common counter, meaning Sensors and Actuators (for example) track the ID separately.
- L95 _protected member_ `FString Nickname;` — `UPROPERTY()` — User-configured name for this element, mostly for debugging purposes but comes in handy when fetching observation/action spaces descriptions. Defaults to UnrealEngine instance name.
- L99 _protected member_ `mutable FString DebugRuntimeString;` — Displayed in debugging tools and logging.

#### struct `FAgentElementSort`  
`struct FAgentElementSort`  
_L103-113_
- L105 _public function_ `bool operator()(const UMLAdapterAgentElement* A, const UMLAdapterAgentElement* B) const`
- L109 _public function_ `bool operator()(const UMLAdapterAgentElement& A, const UMLAdapterAgentElement& B) const`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Agents/MLAdapterAgent_Inference.h` (Public)


#### class `UMLAdapterAgent_Inference`  
`class UMLAdapterAgent_Inference : public UMLAdapterAgent`  
_L18-38_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMLAdapterAgent`
- desc: Inference agents have a neural network that can process senses and output actuations via their Think method. You can create a blueprint of this class to easily wire-up an agent that functions entirely inside the Unreal Engine. @see UMLAdapterNoRPCManager - we do not usually need to open the RPC interface if we are exclusively using inference agents.
- L23 _public prototype_ `virtual void PostInitProperties() override;` — Tries to load the neural network from the ModelDataPath.
- L26 _public prototype_ `virtual void Think(const float DeltaTime) override;` — Process observations from the sensors with the neural network and populate the actuators with data.
- L30 _public member_ `TObjectPtr<UNNEModelData> ModelData;` — `UPROPERTY(EditAnywhere, Category = MLAdapter)` — Reference to neural network asset data.
- L33 _public member_ `TSharedPtr<UE::NNE::IModelInstanceCPU> Brain;` — The neural network controlling this agent.
- L36 _private member_ `uint32 InputTensorSizeInBytes = 0;`
- L37 _private member_ `uint32 OutputTensorSizeInBytes = 0;`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Debug/DebugHelpers.h` (Public)


#### Free symbols / members of external scopes

- L7 _macro_ `#define NOT_IMPLEMENTED() ensureMsgf(false && "NotImplemented", TEXT("NotImplemented"))`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Debug/GameplayDebuggerCategory_MLAdapter.h` (Public)


#### class `FGameplayDebuggerCategory_MLAdapter`  
`class FGameplayDebuggerCategory_MLAdapter : public FGameplayDebuggerCategory`  
_L14-40_
- inherits: `FGameplayDebuggerCategory`
- L17 _public prototype_ `FGameplayDebuggerCategory_MLAdapter();`
- L19 _public prototype_ `virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;`
- L20 _public prototype_ `virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;`
- L22 _public prototype_ `static TSharedRef<FGameplayDebuggerCategory> MakeInstance();`
- L25 _protected prototype_ `void ResetProps();`
- L27 _protected prototype_ `void OnShowNextAgent();`
- L28 _protected prototype_ `void OnRequestAvatarUpdate();`
- L29 _protected prototype_ `void OnSetAvatarAsDebugAgent();`
- L31 _protected prototype_ `void OnCurrentSessionChanged();`
- L32 _protected prototype_ `void OnAgentAvatarChanged(UMLAdapterAgent& Agent, AActor* OldAvatar);`
- L33 _protected prototype_ `void OnBeginAgentRemove(UMLAdapterAgent& Agent);`
- L35 _protected prototype_ `void Init();`
- L38 _protected member_ `AActor* CachedDebugActor;`
- L39 _protected member_ `FMLAdapter::FAgentID CachedAgentID;`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterAsync.h` (Public)


#### Free symbols / members of external scopes

- L10 _function_ `template<typename RetType> RetType CallOnGameThread(TFunction<RetType()> InFunction)` — sends InFunction to be called on the GameThread and waits for the result
- L15 _function_ `` (scope `CallOnGameThread`)
- L25 _function_ `template<> inline void CallOnGameThread(TFunction<void()> InFunction)` — fire (InFunction to be called on the GameThread) and forget

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterInputHelper.h` (Public)


#### Free symbols / members of external scopes

- L9 _namespace_ `namespace FMLAdapterInputHelper`
- L11 _prototype_ `void CreateInputMap(TArray<TTuple<FKey, FName>>& InterfaceKeys, TMap<FKey, int32>& FKeyToInterfaceKeyMap);` (scope `FMLAdapterInputHelper`)
- L13 _prototype_ `TSharedPtr<FMLAdapter::FSpace> ConstructEnhancedInputSpaceDef(const TArray<UInputAction*>& TrackedActions);` (scope `FMLAdapterInputHelper`)

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterJson.h` (Public)


#### struct `FMLAdapter::IJsonable`  
`struct IJsonable`  
_L46-49_

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace FMLAdapter`
- L12 _function_ `template<typename StructType> FString StructArrayToJsonString(const TArray<StructType>& InStructArray)` (scope `FMLAdapter`)
- L32 _function_ `template<typename StructType> FString StructToJsonString(const StructType& InStruct)` (scope `FMLAdapter`)
- L41 _function_ `template<typename StructType> bool JsonStringToStruct(const FString& JsonString, StructType& OutStruct)` (scope `FMLAdapter`)

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterLibrarian.h` (Public)


#### struct `FMLAdapterLibrarian`  
`struct FMLAdapterLibrarian`  
_L19-117_
- reflection: `USTRUCT()`
- desc: The FMLAdapterLibrarian discovers all classes that derived from UMLAdapterAgent, UMLAdapterSensor, or UMLAdapterActuator. It provides functionality for finding those classes by name, so that remote clients can spawn them via their name.
- L27 _public prototype_ `void GatherClasses();` — Register all the base classes and derived classes that inherit from UMLAdapterAgent, UMLAdapterSensor, or UMLAdapterActuator.
- L30 _public prototype_ `void RegisterSensorClass(const TSubclassOf<UMLAdapterSensor>& Class);` — Add the sensor class to the list of known sensors.
- L33 _public prototype_ `void RegisterActuatorClass(const TSubclassOf<UMLAdapterActuator>& Class);` — Add the actuator class to the list of known actuators.
- L36 _public prototype_ `void RegisterAgentClass(const TSubclassOf<UMLAdapterAgent>& Class);` — Add the agent class to the list of known agents.
- L39 _public prototype_ `void AddRPCFunctionDescription(const FName FunctionName, FString&& Description);` — Add the given description to the mapped entry for the given function name.
- L42 _public function_ `TMap<uint32, TSubclassOf<UMLAdapterSensor> >::TConstIterator GetSensorsClassIterator() const` — Get a const iterator over the list of known sensors.
- L45 _public function_ `TMap<uint32, TSubclassOf<UMLAdapterActuator> >::TConstIterator GetActuatorsClassIterator() const` — Get a const iterator over the list of known actuators.
- L48 _public function_ `TArray<TSubclassOf<UMLAdapterAgent> >::TConstIterator GetAgentsClassIterator() const` — Get a const iterator over the list of known agents.
- L56 _public prototype_ `bool GetFunctionDescription(const FName FunctionName, FString& OutDescription) const;` — Gets the function description for the given function name. @param FunctionName The name of the function whose description we would like to get. @param OutDescription The description will be returned here if found. @return True if the description was found. Otherwise false.
- L64 _public prototype_ `inline bool GetFunctionDescription(const FString& FunctionName, FString& OutDescription) const;` — Gets the function description for the given function name. @param FunctionName The name of the function whose description we would like to get. @param OutDescription The description will be returned here if found. @return True if the description was found. Otherwise false.
- L67 _public function_ `TMap<FName, FString>::TConstIterator GetFunctionDescriptionsIterator() const` — Get a const iterator over the list of function descriptions.
- L75 _public prototype_ `bool GetSensorDescription(const FName SensorName, FString& OutDescription) const;` — Gets the description for the given sensor name. @param SensorName The name of the sensor whose description we would like to get. @param OutDescription The description will be returned here if found. @return True if the description was found. Otherwise false.
- L83 _public prototype_ `bool GetActuatorDescription(const FName ActuatorName, FString& OutDescription) const;` — Gets the description for the given actuator name. @param ActuatorName The name of the actuator whose description we would like to get. @param OutDescription The description will be returned here if found. @return True if the description was found. Otherwise false.
- L89 _public prototype_ `TSubclassOf<UMLAdapterAgent> FindAgentClass(const FName ClassName) const;` — Find the agent class with the given class name. Can be the full name or the substring after "UMLAdapterAgent_". Will return UMLAdapterAgent::StaticClass() if not found.
- L95 _public prototype_ `TSubclassOf<UMLAdapterSensor> FindSensorClass(const FName ClassName) const;` — Find the sensor class with the given class name. Can be the full name or the substring after "UMLAdapterSensor_". Will return UMLAdapterSensor::StaticClass() if not found.
- L101 _public prototype_ `TSubclassOf<UMLAdapterActuator> FindActuatorClass(const FName ClassName) const;` — Find the actuator class with the given class name. Can be the full name or the substring after "UMLAdapterActuator_". Will return UMLAdapterActuator::StaticClass() if not found.
- L104 _public prototype_ `static const FMLAdapterLibrarian& Get();` — Gets the librarian owned by the singleton UMLAdapterManager instance.
- L108 _protected member_ `TMap<uint32, TSubclassOf<UMLAdapterSensor> > KnownSensorClasses;` — `UPROPERTY()`
- L111 _protected member_ `TMap<uint32, TSubclassOf<UMLAdapterActuator> > KnownActuatorClasses;` — `UPROPERTY()`
- L114 _protected member_ `TArray<TSubclassOf<UMLAdapterAgent> > KnownAgentClasses;` — `UPROPERTY()`
- L116 _protected member_ `TMap<FName, FString> RPCFunctionDescriptions;`
- L122 _function_ `bool FMLAdapterLibrarian::GetFunctionDescription(const FString& FunctionName, FString& OutDescription) const`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterModule.h` (Public)


#### class `IMLAdapterModule`  
`class IMLAdapterModule : public IModuleInterface`  
_L14-39_
- inherits: `IModuleInterface`
- desc: The public interface to this module.  In most cases, this interface is only public to sibling modules within this plugin.
- L25 _public function_ `static inline IMLAdapterModule& Get()` — Singleton-like access to this module's interface.  This is just for convenience! Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already. @return Returns singleton instance, loading the module on demand if needed
- L35 _public function_ `static inline bool IsAvailable()` — Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true. @return True if the module is loaded and ready to use

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterScribe.h` (Public)


#### Free symbols / members of external scopes

- L14 _namespace_ `namespace FMLAdapterScribe`
- L16 _prototype_ `std::vector<std::string> ToStringVector(const TArray<FString>& Array);` (scope `FMLAdapterScribe`)
- L17 _prototype_ `std::vector<std::string> ToStringVector(const TArray<FName>& Array);` (scope `FMLAdapterScribe`)
- L18 _prototype_ `std::vector<std::string> ListFunctions();` (scope `FMLAdapterScribe`)
- L19 _prototype_ `std::map<std::string, uint32> ListSensorTypes();` (scope `FMLAdapterScribe`)
- L20 _prototype_ `std::map<std::string, uint32> ListActuatorTypes();` (scope `FMLAdapterScribe`)
- L29 _prototype_ `std::string GetDescription(std::string const& ElementName);` (scope `FMLAdapterScribe`) — Gets the description for the given name. Searches the Librarian for registered names in the following order: 1. Functions 2. Sensors 3. Actuators @return The description if found. Otherwise, returns string literal "Not Found".

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterSettings.h` (Public)


#### class `UMLAdapterSettings`  
`class UMLAdapterSettings : public UDeveloperSettings`  
_L22-49_
- reflection: `UCLASS(config = Plugins, defaultconfig, DisplayName="MLAdapter")`
- inherits: `UDeveloperSettings`
- desc: Implements the settings for the MLAdapter plugin.
- L27 _public prototype_ `UMLAdapterSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L29 _public prototype_ `virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;`
- L32 _public prototype_ `static TSubclassOf<UMLAdapterManager> GetManagerClass();`
- L33 _public prototype_ `static TSubclassOf<UMLAdapterSession> GetSessionClass();`
- L34 _public prototype_ `static TSubclassOf<UMLAdapterAgent> GetAgentClass();`
- L35 _public function_ `static uint16 GetDefaultRPCServerPort()`
- L39 _protected member_ `FSoftClassPath ManagerClass;` — `UPROPERTY(EditAnywhere, config, Category = MLAdapter, meta = (MetaClass = "/Script/MLAdapter.MLAdapterManager"))`
- L42 _protected member_ `FSoftClassPath SessionClass;` — `UPROPERTY(EditAnywhere, config, Category = MLAdapter, meta = (MetaClass = "/Script/MLAdapter.MLAdapterSession"))`
- L45 _protected member_ `FSoftClassPath DefaultAgentClass;` — `UPROPERTY(EditAnywhere, config, Category = MLAdapter, meta = (MetaClass = "/Script/MLAdapter.MLAdapterAgent"))`
- L48 _protected member_ `uint16 DefaultRPCServerPort = 15151;` — `UPROPERTY(EditAnywhere, config, Category = MLAdapter)`

#### Free symbols / members of external scopes

- L16 _macro_ `#define GET_CONFIG_VALUE(a) (GetDefault<UMLAdapterSettings>()->a)`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterSpace.h` (Public)


#### enum `EMLAdapterSpaceType`  
`enum class EMLAdapterSpaceType : uint8`  
_L11-18_
- reflection: `UENUM()`
- L13 _public enumerator_ `Discrete`
- L14 _public enumerator_ `MultiDiscrete`
- L15 _public enumerator_ `Box`
- L16 _public enumerator_ `Tuple`
- L17 _public enumerator_ `MAX`

#### struct `FMLAdapter::FSpace`  
`struct FSpace : public IJsonable, public TSharedFromThis<FSpace>`  
_L25-32_
- inherits: `IJsonable,TSharedFromThis<FSpace>`
- desc: Defines the numerical space of a sensor, actuator, or agent. Similar to OpenAI Gym's spaces.
- L27 _public function_ `virtual ~FSpace()`
- L28 _public member_ `EMLAdapterSpaceType Type = EMLAdapterSpaceType::MAX;`
- L30 _public function_ `virtual FString ToJson() const`
- L31 _public function_ `virtual int32 Num() const`

#### struct `FMLAdapter::FSpace_Discrete`  
`struct FSpace_Discrete : public FSpace`  
_L35-41_
- inherits: `FSpace`
- desc: A discrete space contains a countable number of values.
- L37 _public member_ `uint32 Count;`
- L38 _public prototype_ `explicit FSpace_Discrete(uint32 InCount = 2);`
- L39 _public prototype_ `virtual FString ToJson() const override;`
- L40 _public function_ `virtual int32 Num() const override`

#### struct `FMLAdapter::FSpace_MultiDiscrete`  
`struct FSpace_MultiDiscrete : public FSpace`  
_L44-54_
- inherits: `FSpace`
- desc: Multiple options, each with separate discrete range
- L46 _public member_ `TArray<uint32> Options;`
- L48 _public prototype_ `explicit FSpace_MultiDiscrete(uint32 InCount, uint32 InValues = 2);` — simplified constructor creating InCount number of InValues-count options
- L50 _public prototype_ `explicit FSpace_MultiDiscrete(std::initializer_list<uint32> InOptions);` — each element in InOptions defines number of possible values for each n-th option
- L51 _public prototype_ `explicit FSpace_MultiDiscrete(const TArray<uint32>& InOptions);`
- L52 _public prototype_ `virtual FString ToJson() const override;`
- L53 _public function_ `virtual int32 Num() const override`

#### struct `FMLAdapter::FSpace_Box`  
`struct FSpace_Box : public FSpace`  
_L57-69_
- inherits: `FSpace`
- desc: A continuous space that contains a number of ranges defined by the shape, whose values will fall inside the Low to High range.
- L59 _public member_ `TArray<uint32> Shape;`
- L60 _public member_ `float Low = -1.f;`
- L61 _public member_ `float High = 1.f;`
- L62 _public prototype_ `FSpace_Box();`
- L63 _public prototype_ `FSpace_Box(std::initializer_list<uint32> InShape, float InLow = -1.f, float InHigh = 1.f);`
- L64 _public prototype_ `virtual FString ToJson() const override;`
- L65 _public prototype_ `virtual int32 Num() const override;`
- L67 _public function_ `static TSharedPtr<FSpace> Vector3D(float Low = -1.f, float High = 1.f)`
- L68 _public function_ `static TSharedPtr<FSpace> Vector2D(float Low = -1.f, float High = 1.f)`

#### struct `FMLAdapter::FSpace_Dummy`  
`struct FSpace_Dummy : public FSpace_Box`  
_L72-76_
- inherits: `FSpace_Box`
- desc: A placeholder shape - typically returned in invalid scenarios.
- L74 _public function_ `FSpace_Dummy() : FSpace_Box({ 0 })`
- L75 _public function_ `virtual int32 Num() const override`

#### struct `FMLAdapter::FSpace_Tuple`  
`struct FSpace_Tuple : public FSpace`  
_L79-87_
- inherits: `FSpace`
- desc: Container for multiple subspaces.
- L81 _public member_ `TArray<TSharedPtr<FSpace> > SubSpaces;`
- L82 _public prototype_ `FSpace_Tuple();`
- L83 _public prototype_ `FSpace_Tuple(std::initializer_list<TSharedPtr<FSpace> > InitList);`
- L84 _public prototype_ `FSpace_Tuple(TArray<TSharedPtr<FSpace> >& InSubSpaces);`
- L85 _public prototype_ `virtual FString ToJson() const override;`
- L86 _public prototype_ `virtual int32 Num() const override;`

#### struct `FMLAdapter::FSpaceSerializeGuard`  
`struct FSpaceSerializeGuard`  
_L89-102_
- L91 _public member_ `const TSharedRef<FMLAdapter::FSpace>& Space;`
- L92 _public member_ `FMLAdapterMemoryWriter& Ar;`
- L93 _public member_ `const int64 Tell;`
- L94 _public member_ `const int ElementSize;`
- L95 _public function_ `FSpaceSerializeGuard(const TSharedRef<FMLAdapter::FSpace>& InSpace, FMLAdapterMemoryWriter& InAr, const int InElementSize = sizeof(float)) : Space(InSpace), Ar(InAr), Tell(InAr.Tell()), ElementSize(InElementSize)`
- L98 _public function_ `~FSpaceSerializeGuard()`

#### struct `FMLAdapterDescription`  
`struct FMLAdapterDescription`  
_L107-126_
- L109 _public prototype_ `static bool FromJson(const FString& JsonString, FMLAdapterDescription& OutInstance);`
- L110 _public prototype_ `FString ToJson() const;`
- L112 _public function_ `FMLAdapterDescription& Add(FString Key, FString Element)`
- L113 _public function_ `FMLAdapterDescription& Add(FString Key, const FMLAdapterDescription& Element)`
- L114 _public function_ `FMLAdapterDescription& Add(FString Key, const int Element)`
- L115 _public function_ `FMLAdapterDescription& Add(FString Key, const float Element)`
- L116 _public function_ `FMLAdapterDescription& Add(const FMLAdapter::FSpace& Space)`
- L119 _public function_ `void Reset()` — Used in loops to optimize memory use
- L121 _public function_ `bool IsEmpty() const`
- L124 _protected member_ `TArray<TPair<FString, FString>> Data;`
- L125 _protected member_ `TArray<FString> PrepData;`

#### struct `FMLAdapterSpaceDescription`  
`struct FMLAdapterSpaceDescription`  
_L129-139_
- L131 _public typedef_ `typedef TPair<FString, FMLAdapterDescription> ValuePair;`
- L132 _public prototype_ `FString ToJson() const;`
- L134 _public function_ `FMLAdapterSpaceDescription& Add(FString Key, FMLAdapterDescription&& Element)`
- L135 _public function_ `FMLAdapterSpaceDescription& Add(FString Key, FMLAdapterDescription Element)`
- L138 _protected member_ `TArray<ValuePair> Data;`

#### Free symbols / members of external scopes

- L19 _prototype_ `DECLARE_ENUM_TO_STRING(EMLAdapterSpaceType);`
- L22 _namespace_ `namespace FMLAdapter`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/MLAdapterTypes.h` (Public)


#### struct `FMLAdapterMemoryWriter`  
`struct FMLAdapterMemoryWriter : FMemoryWriter`  
_L77-91_
- inherits: `FMemoryWriter`
- L79 _public function_ `FMLAdapterMemoryWriter(TArray<uint8>& InBytes, bool bIsPersistent = false, bool bSetOffset = false, const FName InArchiveName = NAME_None) : FMemoryWriter(InBytes, bIsPersistent, bSetOffset, InArchiveName)`
- L85 _public function_ `template <typename MSGPACK_OBJECT> void msgpack_object(MSGPACK_OBJECT *o, clmdep_msgpack::zone &z) const`

#### struct `FMLAdapterMemoryReader`  
`struct FMLAdapterMemoryReader : FMemoryReader`  
_L94-99_
- inherits: `FMemoryReader`
- L96 _public function_ `FMLAdapterMemoryReader(const TArray<uint8>& InBytes, bool bIsPersistent = false) : FMemoryReader(InBytes, bIsPersistent)`

#### Free symbols / members of external scopes

- L14 _delegate_ `DECLARE_LOG_CATEGORY_EXTERN(LogMLAdapter, Log, All);`
- L14 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogMLAdapter, Log, All);`
- L17 _macro_ `#define DEFINE_ENUM_TO_STRING(EnumType, EnumPackage) FString EnumToString(const EnumType Value) \`
- L24 _macro_ `#define DECLARE_ENUM_TO_STRING(EnumType) FString EnumToString(const EnumType Value)`
- L27 _namespace_ `namespace FMLAdapter`
- L29 _typedef_ `typedef uint32 FAgentID;` (scope `FMLAdapter`)
- L30 _variable_ `static const FAgentID InvalidAgentID = FAgentID(-1);` (scope `FMLAdapter`)
- L31 _variable_ `static const uint32 InvalidSensorID = 0;` (scope `FMLAdapter`)
- L32 _variable_ `static const uint32 InvalidActuatorID = 0;` (scope `FMLAdapter`)
- L43 _function_ `template<class T> T* NewObject(UObject* Outer)` (scope `FMLAdapter`) — MLAdapter-flavored new object creation. We're using this with all the objects we intend to access from outside the game-thread (most notably from the rpc calls). This gives us more control over objects' life cycle. Note: objects created this way won't go away even if there's nothing referencing them until we clear the EInternalObjectFlags::Async flag
- L51 _function_ `template<class T> T* NewObject(UObject* Outer, UClass* Class, FName Name = NAME_None, EObjectFlags Flags = RF_NoFlags, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, FObjectInstancingGraph* InInstanceGraph = nullptr)` (scope `FMLAdapter`)
- L58 _prototype_ `AController* ActorToController(AActor& Actor);` (scope `FMLAdapter`)
- L61 _namespace_ `namespace rpc`
- L75 _typedef_ `typedef rpc::server FRPCServer;`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Managers/MLAdapterManager.h` (Public)


#### enum `EMLAdapterServerMode`  
`enum class EMLAdapterServerMode : uint8`  
_L26-33_
- reflection: `UENUM()`
- L28 _public enumerator_ `Invalid`
- L29 _public enumerator_ `Server`
- L30 _public enumerator_ `Client`
- L31 _public enumerator_ `Standalone` — this applies both to Standalone games as well as PIE
- L32 _public enumerator_ `AutoDetect`

#### class `UMLAdapterManager`  
`class UMLAdapterManager : public UObject, public FTickableGameObject, public FSelfRegisteringExec`  
_L41-209_
- reflection: `UCLASS(Transient)`
- inherits: `UObject,FTickableGameObject,FSelfRegisteringExec`
- desc: The manager of the MLAdapter system. Sets up the RPC server for communication with remote client. Based on settings, creates and ticks the UMLAdapterSession. Tells the UMLAdapterLibrarian to gather its classes. A singleton instance is setup automatically during OnPostEngineInit if this plugin is included.
- L45 _public typedef_ `using FRPCFunctionBind = TFunction<void(FRPCServer& )>;`
- L46 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenericRPCServerDelegate, FRPCServer& );`
- L47 _public prototype_ `DECLARE_MULTICAST_DELEGATE(FOnGenericEvent);`
- L49 _public prototype_ `UMLAdapterManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L50 _public prototype_ `virtual void BeginDestroy() override;`
- L51 _public prototype_ `virtual void PostInitProperties() override;`
- L54 _public prototype_ `virtual void Tick(float DeltaTime) override;` — FTickableGameObject begin
- L55 _public prototype_ `virtual TStatId GetStatId() const override;`
- L56 _public function_ `virtual bool IsTickableWhenPaused() const override`
- L57 _public function_ `virtual bool IsTickableInEditor() const override`
- L58 _public prototype_ `virtual ETickableTickType GetTickableTickType() const override;`
- L59 _public prototype_ `virtual bool IsTickable() const override;`
- L63 _public prototype_ `virtual bool Exec(class UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar) override;` — FExec begin
- L67 _public prototype_ `virtual void BindToDelegates();` — Binds the manager's world, game mode, and editor delegates - called during PostInitProperties.
- L70 _public prototype_ `virtual void CleanUpDelegates();` — Cleans up all the manager's delegates - called during BeginDestroy.
- L73 _public prototype_ `virtual void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues);` — Starts the RPC server if the world is a game world
- L76 _public prototype_ `virtual void OnWorldCleanup(UWorld* World, bool bSessionEnded, bool bCleanupResources);` — Closes the current session.
- L78 _public prototype_ `virtual void OnBeginPIE(const bool bIsSimulating);`
- L79 _public prototype_ `virtual void OnEndPIE(const bool bIsSimulating);`
- L82 _public prototype_ `virtual void OnGameModeInitialized(AGameModeBase* GameMode);` — Notifies the session that the game mode has initialized.
- L85 _public prototype_ `virtual void OnGameModePostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer);` — Notifies the session a player has connected.
- L88 _public prototype_ `virtual void OnGameModeMatchStateSet(FName MatchState);` — @note This might not get called at all if the project's game mode doesn't extend AGameMode.
- L94 _public prototype_ `virtual void StartServer(uint16 Port, EMLAdapterServerMode InMode = EMLAdapterServerMode::AutoDetect, uint16 ServerThreads = 1);` — Starts a new RPC server. If a server is already running, it will be shut down before the new instance gets created. @param ServerThreads best set at the number of external clients that are going to be connecting
- L97 _public prototype_ `virtual void StopServer();` — Stop the RPC server.
- L100 _public prototype_ `virtual bool IsRunning() const;` — True if there is an RPC server currently running.
- L103 _public prototype_ `virtual void ConfigureAsServer(FRPCServer& Server);` — "Server" in this context means UnrealEngine game server, not RPC server.
- L106 _public prototype_ `virtual void ConfigureAsClient(FRPCServer& Server);` — "Client" in this context means UnrealEngine game client, not RPC client.
- L109 _public prototype_ `virtual void ConfigureAsStandalone(FRPCServer& Server);` — Essentially calls both the server and client versions.
- L112 _public prototype_ `virtual void EnsureAISystemPresence(UWorld& World);` — If given World doesn't have an AI system, this call results in creating one.
- L115 _public prototype_ `virtual void EnsureNavigationSystemPresence(UWorld& World);` — If given World doesn't have a Navigation system instance, this call results in creating one.
- L117 _public prototype_ `virtual UMLAdapterSession* CreateNewSession();`
- L118 _public prototype_ `virtual void SetSession(UMLAdapterSession* NewSession);`
- L119 _public prototype_ `virtual void CloseSession(UMLAdapterSession& InSession);`
- L122 _public prototype_ `virtual UMLAdapterSession& GetSession();` — Returns the current session. If one doesn't exist, it gets created.
- L123 _public function_ `bool HasSession() const`
- L126 _public function_ `void RegisterSensorClass(const TSubclassOf<UMLAdapterSensor>& Class)` — Register a sensor class with this manager's librarian.
- L129 _public function_ `void RegisterActuatorClass(const TSubclassOf<UMLAdapterActuator>& Class)` — Register an actuator class with this manager's librarian.
- L132 _public function_ `void RegisterAgentClass(const TSubclassOf<UMLAdapterAgent>& Class)` — Register an agent class with this manager's librarian.
- L134 _public prototype_ `virtual void ResetWorld();`
- L135 _public prototype_ `void SetManualWorldTickEnabled(bool bEnable);`
- L137 _public function_ `FOnGenericRPCServerDelegate& GetOnAddClientFunctions()`
- L138 _public function_ `FOnGenericRPCServerDelegate& GetOnAddServerFunctions()`
- L141 _public prototype_ `inline static UMLAdapterManager& Get();` — Get the current manager instance.
- L144 _public prototype_ `inline static bool IsReady();` — Returns true if the manager instance exists.
- L147 _public function_ `const FMLAdapterLibrarian& GetLibrarian() const` — Get this manager's librarian.
- L150 _public function_ `bool IsWorldRealTime() const` — Returns true if this manager is not being ticked manually by the remote client.
- L152 _public function_ `FOnGenericEvent& GetOnCurrentSessionChanged()`
- L156 _protected prototype_ `void AddCommonFunctions(FRPCServer& Server);`
- L158 _protected prototype_ `virtual bool ShouldInitForWorld(const UWorld& World) const;`
- L164 _protected member_ `TObjectPtr<UMLAdapterSession> Session;` — `UPROPERTY()`
- L167 _protected member_ `TObjectPtr<UWorld> LastActiveWorld;` — `UPROPERTY()`
- L170 _protected member_ `FMLAdapterLibrarian Librarian;` — `UPROPERTY()`
- L172 _protected member_ `FOnGenericRPCServerDelegate OnAddClientFunctions;`
- L173 _protected member_ `FOnGenericRPCServerDelegate OnAddServerFunctions;`
- L175 _protected member_ `FOnGenericEvent OnCurrentSessionChanged;`
- L177 _protected member_ `EMLAdapterServerMode RequestedFunctionMode = EMLAdapterServerMode::Invalid;`
- L178 _protected member_ `EMLAdapterServerMode CurrentFunctionMode = EMLAdapterServerMode::Invalid;`
- L179 _protected member_ `uint16 CurrentPort = 0;`
- L180 _protected member_ `uint16 CurrentServerThreads = 1;`
- L182 _protected member_ `TArray<uint8> Data;`
- L184 _protected member_ `float WorldFPS = 20.f;`
- L186 _protected member_ `uint32 bCommonFunctionsAdded : 1;`
- L187 _protected member_ `uint32 bTickWorldManually : 1;`
- L192 _protected member_ `int32 StepsRequested = 0;` — is the manager is in 'manual ticking mode' (where external client is responsible for progressing the world sim by calling 'request_world_tick' function) the simulation will progress by StepsRequested ticks before pausing
- L194 _protected member_ `FDelegateHandle OnPostWorldInitializationHandle;`
- L195 _protected member_ `FDelegateHandle OnWorldCleanupHandle;`
- L196 _protected member_ `FDelegateHandle OnGameModeInitializedHandle;`
- L197 _protected member_ `FDelegateHandle OnGameModePostLoginHandle;`
- L198 _protected member_ `FDelegateHandle OnGameModeMatchStateSetHandle;`
- L200 _protected member_ `FDelegateHandle BeginPIEHandle;`
- L201 _protected member_ `FDelegateHandle EndPIEHandle;`
- L204 _protected member_ `static UMLAdapterManager* ManagerInstance;`
- L206 _public prototype_ `static void RecreateManagerInstance();`
- L208 _public member_ `static FOnGenericEvent OnPostInit;`
- L214 _function_ `UMLAdapterManager& UMLAdapterManager::Get()`
- L221 _function_ `bool UMLAdapterManager::IsReady()`

#### Free symbols / members of external scopes

- L15 _namespace_ `namespace rpc`
- L16 _namespace_ `namespace FMLAdapterConsoleCommands`
- L46 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnGenericRPCServerDelegate, FRPCServer& );`
- L47 _delegate_ `DECLARE_MULTICAST_DELEGATE(FOnGenericEvent);`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Managers/MLAdapterNoRPCManager.h` (Public)


#### class `UMLAdapterNoRPCManager`  
`class UMLAdapterNoRPCManager : public UMLAdapterManager`  
_L14-19_
- reflection: `UCLASS()`
- inherits: `UMLAdapterManager`
- desc: UMLAdapterNoRPCManager won't start the RPC server and will immediately start a session and spawn the default agent. This is intended to be used when there will only be a single inference agent that exists for the life of the game.
- L18 _public prototype_ `virtual void OnPostWorldInit(UWorld* World, const UWorld::InitializationValues) override;`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/RPCWrapper/MsgPack.h` (Public)


#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_VIRTUAL_MSGPACK_DEFINE(...) \`
- L17 _macro_ `#define UE_MSGPACK_DEFINE(...) \`
- L26 _macro_ `#define UE_MSGPACK_DEFINE(...)`
- L27 _macro_ `#define UE_VIRTUAL_MSGPACK_DEFINE(...)`
- L28 _macro_ `#define MSGPACK_DEFINE_ARRAY(...)`
- L35 _macro_ `#define UE_RPC_BIND(FuncName, FuncBody) TEXT(FuncName), [this](FRPCServer& Serv) { Serv.bind(FuncName, FuncBody); }` — helper macro for just binding a simple function. Not recommended for elaborate lambdas since using this macro interferes with debugging (unable to break in the lambdas body).
- L36 _macro_ `#define FSTRING_TO_STD(a) (std::string(TCHAR_TO_UTF8(*a)))`
- L40 _namespace_ `namespace FMLAdapter`
- L43 _function_ `template<typename T> TArray<T> VectorToArray(const std::vector<T> InVector)` (scope `FMLAdapter`)

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/RPCWrapper/Server.h` (Public)
_(no declarations extracted)_

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/RPCWrapper/rpclib_includes.h` (Public)


#### Free symbols / members of external scopes

- L23 _macro_ `#define RPCLIB_MSGPACK clmdep_msgpack`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sensors/MLAdapterSensor.h` (Public)


#### enum `EMLAdapterTickPolicy`  
`enum class EMLAdapterTickPolicy : uint8`  
_L15-21_
- reflection: `UENUM()`
- desc: Controls the frequency that a sensor should tick at.
- L17 _public enumerator_ `EveryTick`
- L18 _public enumerator_ `EveryXSeconds`
- L19 _public enumerator_ `EveryNTicks`
- L20 _public enumerator_ `Never`

#### class `UMLAdapterSensor`  
`class UMLAdapterSensor : public UMLAdapterAgentElement`  
_L25-100_
- reflection: `UCLASS(Abstract, Blueprintable, EditInlineNew)`
- inherits: `UMLAdapterAgentElement`
- desc: Allows an agent to sense information about the game world or itself.
- L30 _public prototype_ `UMLAdapterSensor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L31 _public prototype_ `virtual void PostInitProperties() override;`
- L37 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;` — Called before actuator's destruction. Can be called as part of new agent config application when old actuator get destroyed.
- L39 _public prototype_ `virtual void OnAvatarSet(AActor* Avatar) override;`
- L42 _public function_ `FMLAdapter::FAgentID GetAgentID() const` — AIGym leftovers. Potentially to be removed
- L43 _public prototype_ `const UMLAdapterAgent& GetAgent() const;`
- L44 _public prototype_ `bool IsConfiguredForAgent(const UMLAdapterAgent& Agent) const;`
- L45 _public function_ `bool IsPolling() const`
- L48 _public prototype_ `virtual bool ConfigureForAgent(UMLAdapterAgent& Agent);` — True if config was successful. Only then will the sensor instance be added to agent's active sensors.
- L50 _public prototype_ `void OnPawnChanged(APawn* OldPawn, APawn* NewPawn);`
- L53 _public prototype_ `void Sense(const float DeltaTime);` — Called for every sense, regardless of whether it's a polling-type or not.
- L59 _public prototype_ `virtual void GetObservations(FMLAdapterMemoryWriter& Ar) PURE_VIRTUAL(UMLAdapterSensor::GetObservations, );` — @param bTransfer if set to true the Sensor is expected to clear all stored observations after copying/moving them to OutObservations
- L64 _protected prototype_ `virtual void ClearPawn(APawn& InPawn);` — Clean up any references to the Pawn or its components.
- L67 _protected function_ `virtual void SenseImpl(const float DeltaTime)` — Called from Sense based on TickPolicy.
- L70 _protected member_ `FMLAdapter::FAgentID AgentID;`
- L74 _protected member_ `uint32 bRequiresPawn : 1;` — `UPROPERTY(EditDefaultsOnly, Category=MLAdapter)` — @todo this is not currently referenced anywhere
- L78 _protected member_ `uint32 bIsPolling : 1;` — `UPROPERTY(EditDefaultsOnly, Category = MLAdapter)` — @todo this is not currently referenced anywhere
- L82 _protected member_ `EMLAdapterTickPolicy TickPolicy;` — `UPROPERTY(EditDefaultsOnly, Category = MLAdapter)` — Determines what frequency this sensor ticks at.
- L93 _protected member_ `FTicksOrSeconds TickEvery;`
- L96 _protected member_ `mutable FCriticalSection ObservationCS;` — This needs to be locked anytime the sensor is accessing shared state internally.
- L98 _private member_ `int32 AccumulatedTicks;`
- L99 _private member_ `float AccumulatedSeconds;`

#### struct `UMLAdapterSensor::FTicksOrSeconds`  
`struct FTicksOrSeconds`  
_L84-92_
- L91 _public function_ `FTicksOrSeconds() : Ticks(0)`

#### union `UMLAdapterSensor::FTicksOrSeconds::(anonymous)`  
``  
_L87-90_

#### Free symbols / members of external scopes

- L88 _member_ `int32 Ticks;` (scope `UMLAdapterSensor::FTicksOrSeconds::__anonfacc1cc6010a`)
- L89 _member_ `float Seconds;` (scope `UMLAdapterSensor::FTicksOrSeconds::__anonfacc1cc6010a`)

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sensors/MLAdapterSensor_AIPerception.h` (Public)


#### class `UMLAdapterSensor_AIPerception`  
`class UMLAdapterSensor_AIPerception : public UMLAdapterSensor`  
_L22-94_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMLAdapterSensor`
- desc: When applied to a player controller will create an AIPerception component for that player and plug it into the AIPerceptionSystem. The sensor will report information gathered by the perception system on the behalf of this agent. @see UAIPerceptionComponent::ProcessStimuli Note that the world needs to be configured to allow AI Systems to be created @see Server.Configure mz@todo replace with the proper reference
- L44 _public prototype_ `UMLAdapterSensor_AIPerception(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L46 _public prototype_ `virtual void GetViewPoint(AActor& Avatar, FVector& POVLocation, FRotator& POVRotation) const;`
- L49 _protected prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L50 _protected prototype_ `virtual void GetObservations(FMLAdapterMemoryWriter& Ar) override;`
- L51 _protected prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L52 _protected prototype_ `virtual void UpdateSpaceDef() override;`
- L53 _protected prototype_ `virtual void OnAvatarSet(AActor* Avatar) override;`
- L55 _protected prototype_ `virtual void SenseImpl(const float DeltaTime) override;`
- L58 _protected prototype_ `virtual void DescribeSelfToGameplayDebugger(FGameplayDebuggerCategory& DebuggerCategory) const override;`
- L61 _protected function_ `inline float Sanify(const float DegreeAngles) const`
- L69 _protected function_ `inline FRotator Sanify(const FRotator Rotator) const`
- L77 _protected member_ `TObjectPtr<UAIPerceptionComponent> PerceptionComponent;` — `UPROPERTY()`
- L86 _protected member_ `bool bSenseOnlyChanges = false;` — `UPROPERTY()` — When set to true will only gather perception "delta" meaning consecutive updates will consist of new perception information. Defaults to "false" which means that every update all of data contained by the PerceptionComponent will be "sensed"
- L88 _protected member_ `float PeripheralVisionAngleDegrees;`
- L89 _protected member_ `float MaxStimulusAge;`
- L90 _protected member_ `uint16 TargetsToSenseCount;`
- L91 _protected member_ `ESortType TargetsSortType;`
- L92 _protected member_ `TArray<FTargetRecord> CachedTargets;`
- L93 _protected member_ `uint32 bVectorMode : 1;`

#### enum `UMLAdapterSensor_AIPerception::ESortType`  
`enum class ESortType : uint8`  
_L26-30_
- L28 _public enumerator_ `Distance`
- L29 _public enumerator_ `InFrontness`

#### struct `UMLAdapterSensor_AIPerception::FTargetRecord`  
`struct FTargetRecord`  
_L31-42_
- L33 _public member_ `FRotator HeadingRotator;`
- L34 _public member_ `FVector HeadingVector;`
- L35 _public member_ `float Distance;`
- L36 _public member_ `int32 ID;`
- L38 _public member_ `float HeadingDot;` — non essential, helper/debug
- L39 _public member_ `TWeakObjectPtr<AActor> Target;`
- L41 _public function_ `FTargetRecord() : HeadingRotator(EForceInit::ForceInitToZero), HeadingVector(EForceInit::ForceInitToZero), Distance(0.f), ID(0), HeadingDot(-1.f)`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sensors/MLAdapterSensor_Attribute.h` (Public)


#### class `UMLAdapterSensor_Attribute`  
`class UMLAdapterSensor_Attribute : public UMLAdapterSensor`  
_L15-42_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMLAdapterSensor`
- L19 _public prototype_ `UMLAdapterSensor_Attribute(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L21 _public prototype_ `virtual bool ConfigureForAgent(UMLAdapterAgent& Agent) override;`
- L22 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L25 _protected prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L26 _protected prototype_ `virtual void UpdateSpaceDef() override;`
- L27 _protected prototype_ `virtual void OnAvatarSet(AActor* Avatar) override;`
- L28 _protected prototype_ `virtual void SenseImpl(const float DeltaTime) override;`
- L29 _protected prototype_ `virtual void GetObservations(FMLAdapterMemoryWriter& Ar) override;`
- L31 _protected prototype_ `void SetAttributes(TArray<FString>& InAttributeNames);`
- L32 _protected prototype_ `void BindAttributes(AActor& Actor);`
- L35 _protected member_ `TObjectPtr<UAttributeSet> AttributeSet;` — `UPROPERTY()`
- L37 _protected member_ `TArray<FName> AttributeNames;`
- L39 _protected member_ `TArray<FGameplayAttributeData*> Attributes;` — valid only as long as AttributeSet != nullptr
- L41 _protected member_ `TArray<float> Values;`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sensors/MLAdapterSensor_Camera.h` (Public)


#### class `UMLAdapterSensor_Camera`  
`class UMLAdapterSensor_Camera : public UMLAdapterSensor`  
_L18-64_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMLAdapterSensor`
- desc: Observing player's camera
- L22 _public prototype_ `UMLAdapterSensor_Camera(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L24 _public prototype_ `virtual bool ConfigureForAgent(UMLAdapterAgent& Agent) override;`
- L25 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L26 _public prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L27 _public prototype_ `virtual void GetObservations(FMLAdapterMemoryWriter& Ar) override;`
- L30 _protected prototype_ `virtual void SenseImpl(const float DeltaTime) override;`
- L32 _protected prototype_ `virtual void OnAvatarSet(AActor* Avatar) override;`
- L33 _protected prototype_ `virtual void ClearPawn(APawn& InPawn) override;`
- L35 _protected prototype_ `void HandleScreenshotData(int32 InSizeX, int32 InSizeY, const TArray<FColor>& InImageData);`
- L39 _protected member_ `uint32 Width;` — `UPROPERTY(EditAnywhere, Category = MLAdapter, meta=(UIMin=1, ClampMin=1))`
- L42 _protected member_ `uint32 Height;` — `UPROPERTY(EditAnywhere, Category = MLAdapter, meta=(UIMin=1, ClampMin=1))`
- L45 _protected member_ `uint32 bShowUI : 1;` — `UPROPERTY(EditAnywhere, Category = MLAdapter)`
- L48 _protected member_ `TObjectPtr<USceneCaptureComponent2D> CaptureComp;` — `UPROPERTY(Transient)`
- L51 _protected member_ `TObjectPtr<UTextureRenderTarget2D> RenderTarget2D;` — `UPROPERTY(Transient)`
- L54 _protected member_ `TObjectPtr<UGameViewportClient> CachedViewportClient;` — `UPROPERTY()`
- L56 _protected member_ `ETextureRenderTargetFormat RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA16f;`
- L57 _protected member_ `ESceneCaptureSource CaptureSource = SCS_FinalColorLDR;`
- L58 _protected member_ `uint8 CameraIndex = 0;`
- L60 _protected member_ `FDelegateHandle ScreenshotDataCallbackHandle;`
- L63 _public member_ `TArray<FLinearColor> LastTickData;`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sensors/MLAdapterSensor_EnhancedInput.h` (Public)


#### class `UMLAdapterSensor_EnhancedInput`  
`class UMLAdapterSensor_EnhancedInput : public UMLAdapterSensor`  
_L12-37_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMLAdapterSensor`
- L17 _protected prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L18 _protected prototype_ `virtual void GetObservations(FMLAdapterMemoryWriter& Ar) override;`
- L19 _protected prototype_ `virtual void UpdateSpaceDef() override;`
- L20 _protected prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L23 _protected prototype_ `virtual void OnAvatarSet(AActor* Avatar) override;` — The Avatar here is expected to be a player-controlled APawn or an APlayerController
- L25 _protected member_ `TArray<float> InputState;`
- L27 _protected member_ `TMap<FString, int32> InputStateIndices;`
- L30 _protected member_ `TArray<TObjectPtr<UInputAction>> TrackedActions;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MLAdapter)`
- L33 _protected member_ `TObjectPtr<UEnhancedInputComponent> InputComponent;` — `UPROPERTY(BlueprintReadOnly, Category = MLAdapter)`
- L36 _protected prototype_ `void OnInputAction(const FInputActionInstance& ActionInstance);` — `UFUNCTION()`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sensors/MLAdapterSensor_Input.h` (Public)


#### class `UMLAdapterSensor_Input`  
`class UMLAdapterSensor_Input : public UMLAdapterSensor`  
_L22-50_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMLAdapterSensor`
- desc: Note that this sensor doesn't buffer input state between GetObservations call @todo a child class could easily do that by overriding OnInputKey/OnInputAxis and GetObservations
- L26 _public prototype_ `UMLAdapterSensor_Input(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L29 _protected prototype_ `virtual void OnInputAxis(FViewport* InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad);`
- L30 _protected prototype_ `virtual void OnInputKey(const FInputKeyEventArgs& EventArgs);`
- L32 _protected prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L33 _protected prototype_ `virtual void GetObservations(FMLAdapterMemoryWriter& Ar) override;`
- L34 _protected prototype_ `virtual void UpdateSpaceDef() override;`
- L35 _protected prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L36 _protected prototype_ `virtual void OnAvatarSet(AActor* Avatar);`
- L39 _protected member_ `TObjectPtr<UGameViewportClient> GameViewport;` — `UPROPERTY(EditDefaultsOnly, Category = MLAdapter)`
- L42 _protected member_ `uint32 bRecordKeyRelease : 1;` — `UPROPERTY(EditDefaultsOnly, Category = MLAdapter)`
- L44 _protected member_ `TArray<float> InputState;`
- L47 _protected member_ `TArray<TTuple<FKey, FName>> InterfaceKeys;` — stores (FKey, ActionName pairs). The order is important since FKeyToInterfaceKeyMap refers to it.
- L49 _protected member_ `TMap<FKey, int32> FKeyToInterfaceKeyMap;`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sensors/MLAdapterSensor_Movement.h` (Public)


#### class `UMLAdapterSensor_Movement`  
`class UMLAdapterSensor_Movement : public UMLAdapterSensor`  
_L11-44_
- reflection: `UCLASS(Blueprintable)`
- inherits: `UMLAdapterSensor`
- desc: Allows an agent to sense its avatar's location and velocity.
- L15 _public prototype_ `UMLAdapterSensor_Movement(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());`
- L17 _public prototype_ `virtual bool ConfigureForAgent(UMLAdapterAgent& Agent) override;`
- L18 _public prototype_ `virtual void Configure(const TMap<FName, FString>& Params) override;`
- L19 _public prototype_ `virtual TSharedPtr<FMLAdapter::FSpace> ConstructSpaceDef() const override;`
- L22 _protected prototype_ `virtual void OnAvatarSet(AActor* Avatar) override;`
- L23 _protected prototype_ `virtual void SenseImpl(const float DeltaTime) override;`
- L24 _protected prototype_ `virtual void GetObservations(FMLAdapterMemoryWriter& Ar) override;`
- L28 _protected member_ `uint32 bAbsoluteLocation : 1;` — `UPROPERTY()`
- L31 _protected member_ `uint32 bAbsoluteVelocity : 1;` — `UPROPERTY()`
- L34 _protected member_ `FVector RefLocation;` — `UPROPERTY()`
- L37 _protected member_ `FVector RefVelocity;` — `UPROPERTY()`
- L40 _protected member_ `FVector CurrentLocation;` — `UPROPERTY()`
- L43 _protected member_ `FVector CurrentVelocity;` — `UPROPERTY()`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sessions/MLAdapterLocalDataCollectionSession.h` (Public)


#### class `UMLAdapterLocalDataCollectionSession`  
`class UMLAdapterLocalDataCollectionSession : public UMLAdapterSession`  
_L17-46_
- reflection: `UCLASS(Blueprintable, EditInlineNew)`
- inherits: `UMLAdapterSession`
- desc: Collects data from agents' sensors and writes them to a file for offline processing. Only works with a locally controlled, single-player game.
- L21 _public prototype_ `virtual void PostInitProperties() override;`
- L23 _public prototype_ `virtual void OnPostWorldInit(UWorld& World) override;`
- L26 _public prototype_ `virtual void OnPawnControllerChanged(APawn* InPawn, AController* InController);` — `UFUNCTION()`
- L28 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L30 _public prototype_ `virtual void Close() override;`
- L33 _public member_ `FDirectoryPath FilePath;` — `UPROPERTY(EditDefaultsOnly, Category = MLAdapter)`
- L36 _public member_ `FString FileName;` — `UPROPERTY(EditDefaultsOnly, Category = MLAdapter)`
- L39 _public member_ `bool bPrefixOutputFilenameWithTimestamp;` — `UPROPERTY(EditDefaultsOnly, Category = MLAdapter)`
- L42 _private member_ `FString OutputFilePath;`
- L45 _private member_ `TWeakObjectPtr<UMLAdapterAgent> PlayerControlledAgent;` — `UPROPERTY()`

### `Plugins/AI/MLAdapter/Source/MLAdapter/Public/Sessions/MLAdapterSession.h` (Public)


#### enum `EMLAdapterSimState`  
`enum class EMLAdapterSimState : uint8`  
_L25-30_
- L27 _public enumerator_ `BootingUp`
- L28 _public enumerator_ `InProgress`
- L29 _public enumerator_ `Finished`

#### class `UMLAdapterSession`  
`class UMLAdapterSession : public UObject`  
_L37-230_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Container for agents that exist in the world. Ticks the agents. Finds avatars for the agents.
- L42 _public prototype_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAgentAvatarChangedDelegate, UMLAdapterAgent& , AActor* );`
- L43 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginAgentRemove, UMLAdapterAgent& );`
- L46 _public function_ `virtual UWorld* GetWorld() const override` — Get this session's cached world.
- L48 _public prototype_ `virtual void PostInitProperties() override;`
- L50 _public prototype_ `virtual void BeginDestroy() override;`
- L54 _public function_ `UGameInstance* GetGameInstance() const`
- L57 _public prototype_ `virtual void SetWorld(UWorld* NewWorld);` — Sets the world that this session will use to find avatars for agents
- L60 _public prototype_ `virtual void OnActorSpawned(AActor* InActor);` — If there are agents waiting for an avatar, then check if a newly spawned actor fits the agent.
- L62 _public prototype_ `virtual void OnPostWorldInit(UWorld& World);`
- L63 _public prototype_ `virtual void OnWorldCleanup(UWorld& World, bool bSessionEnded, bool bCleanupResources);`
- L64 _public prototype_ `virtual void OnGameModeInitialized(AGameModeBase& GameModeBase);`
- L65 _public prototype_ `virtual void OnGameModeMatchStateSet(FName InMatchState);`
- L66 _public prototype_ `virtual void OnGameModePostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer);`
- L69 _public prototype_ `virtual void Open();` — Mark the session as active.
- L72 _public prototype_ `virtual void Close();` — Mark the session as inactive and cleanup all agents.
- L75 _public prototype_ `virtual void Tick(float DeltaTime);` — Call all agents' Sense(), Think(), and Act() methods.
- L81 _public prototype_ `virtual void ConfigureAsServer();` — This is where Session can add Authority-side-specific functions by calling UMLAdapterManager::Get().AddServerFunctionBind
- L88 _public prototype_ `virtual void ConfigureAsClient();` — This is where Session can add Client-side-specific functions by calling UMLAdapterManager::Get().AddClientFunctionBind. "Client" in this context means UnrealEngine game client, not RPC client.
- L91 _public prototype_ `virtual void ResetWorld(FMLAdapter::FAgentID AgentID = FMLAdapter::InvalidAgentID);` — Using FMLAdapter::InvalidAgentID for AgentID will reset all agents.
- L94 _public prototype_ `bool IsDone() const;` — A session is done if the SimulationState == Finished or the game mode's match has ended.
- L97 _public prototype_ `bool IsReady() const;` — A session is ready if the SimulationState == InProgress or the game mode's match has started but not ended.
- L100 _public function_ `float GetTimestamp() const` — Get the world time in seconds at the most recent time this session ticked.
- L103 _public prototype_ `void SetManualWorldTickEnabled(bool bEnable);` — If true, the world's ticking will be controlled by the remote client.
- L106 _public prototype_ `void EnableActionDuration(FMLAdapter::FAgentID AgentID, bool bEnable, float DurationSeconds);` — Enable/disable the action durations with the specified time duration in seconds.
- L109 _public prototype_ `bool TryResetActionDuration(FMLAdapter::FAgentID AgentID);` — Resets the action duration flag if it has elapsed. Returns false if not reset yet or the agent is not found. Used with HasActionDurationElapsed by Manager.
- L111 _public function_ `FOnAgentAvatarChangedDelegate GetOnAgentAvatarChanged()`
- L112 _public function_ `FOnBeginAgentRemove GetOnBeginAgentRemove()`
- L119 _public prototype_ `FMLAdapter::FAgentID AddAgent();` — Add a default agent as specified in the UMLAdapterSettings.
- L122 _public prototype_ `FMLAdapter::FAgentID AddAgent(const FMLAdapterAgentConfig& InConfig);` — Add an agent using the specified config.
- L128 _public prototype_ `FMLAdapter::FAgentID GetNextAgentID(FMLAdapter::FAgentID ReferenceAgentID) const;` — @return Next valid agent ID. Note that the return value might be equal to ReferenceAgentID if there's only one agent. Will be FMLAdapter::InvalidAgentId if no agents registered.
- L131 _public prototype_ `UMLAdapterAgent* GetAgent(FMLAdapter::FAgentID AgentID);` — Returns the agent corresponding to the given ID. Returns nullptr if the ID is invalid.
- L134 _public prototype_ `void RemoveAgent(FMLAdapter::FAgentID AgentID);` — Remove the agent with the given ID from this session.
- L137 _public prototype_ `bool IsAgentReady(FMLAdapter::FAgentID AgentID) const;` — Returns true if the agent with the given ID has a valid avatar assigned.
- L140 _public prototype_ `void FindAvatars(UWorld& World);` — Finds avatar in given World for every avatar-less agent in AwaitingAvatar
- L146 _public prototype_ `void RemoveAvatars(UWorld* World);` — Processes Agents and removes all agent avatars belonging to World. If World is null the function will remove all avatars.
- L157 _public prototype_ `virtual bool RequestAvatarForAgent(UMLAdapterAgent& Agent, UWorld* InWorld = nullptr, const bool bForceSearch = false);` — Finds a suitable avatar in InWorld (or CachedWorld, if InWorld is null) for given agent, as specified by FMLAdapterAgentConfig.AvatarClass and confirmed by Agent->IsSuitableAvatar call. If no suitable avatar is found this agent will be added to "waiting list" (AwaitingAvatar) @param bForceSearch if true will ignore whether the Agent is already waiting in AwaitingAvatar and will perform the search right away. Note that the Agent might still end up in AwaitingAvatar if there's no suitable avatars available @return True if an avatar has been assigned. False otherwise.
- L160 _public prototype_ `bool RequestAvatarForAgent(FMLAdapter::FAgentID& AgentID, UWorld* InWorld = nullptr);` — Calls RequestAvatarForAgent(UMLAdapterAgent& Agent, ...) after looking up the agent by its ID.
- L163 _public prototype_ `void BindAvatar(UMLAdapterAgent& Agent, AActor& Avatar);` — Sets a new avatar on the agent after clearing any existing avatar.
- L166 _public prototype_ `void ClearAvatar(UMLAdapterAgent& Agent);` — Remove the existing avatar from the given agent.
- L169 _public function_ `int32 GetAgentsCount() const` — @todo this technically returns the count of all agents that ever existed given that we are not removing them yet.
- L172 _public prototype_ `const UMLAdapterAgent* FindAgentByAvatar(AActor& Avatar) const;` — Find an agent that is controlling the given avatar if one exists. Returns nullptr if not.
- L178 _public prototype_ `void DescribeSelfToGameplayDebugger(class FGameplayDebuggerCategory& DebuggerCategory) const;`
- L182 _protected prototype_ `virtual void SetGameMode(AGameModeBase* GameModeBase);`
- L184 _protected function_ `inline static uint32 HashAvatar(const AActor& Avatar)`
- L190 _protected member_ `TObjectPtr<AGameModeBase> CachedGameMode;` — `UPROPERTY()`
- L193 _protected member_ `TObjectPtr<UWorld> CachedWorld;` — `UPROPERTY()`
- L197 _protected member_ `TMap<uint32, TObjectPtr<UMLAdapterAgent>> AvatarToAgent;` — `UPROPERTY()` — @see HashAvatar
- L200 _protected member_ `TArray<TObjectPtr<UMLAdapterAgent>> Agents;` — `UPROPERTY()`
- L203 _protected member_ `TArray<TObjectPtr<UMLAdapterAgent>> AwaitingAvatar;` — `UPROPERTY()`
- L205 _protected member_ `FOnAgentAvatarChangedDelegate OnAgentAvatarChanged;`
- L206 _protected member_ `FOnBeginAgentRemove OnBeginAgentRemove;`
- L208 _protected member_ `FDelegateHandle ActorSpawnedDelegateHandle;`
- L210 _protected member_ `EMLAdapterSimState SimulationState;`
- L212 _protected member_ `float LastTimestamp = -1.f;`
- L214 _protected member_ `bool bActive = false;`
- L215 _protected member_ `bool bTickWorldManually = false;`
- L217 _protected member_ `mutable FCriticalSection AgentOpCS;`
- L229 _protected member_ `TSharedPtr<FWorldTicker> WorldTicker;`

#### struct `UMLAdapterSession::FWorldTicker`  
`struct FWorldTicker : public FTickableGameObject`  
_L219-227_
- inherits: `FTickableGameObject`
- L221 _public member_ `TWeakObjectPtr<UWorld> CachedWorld;`
- L222 _public function_ `FWorldTicker(UWorld* InWorld) : CachedWorld(InWorld)`
- L223 _public prototype_ `virtual ~FWorldTicker();`
- L224 _public prototype_ `virtual void Tick(float DeltaTime) override;`
- L225 _public function_ `virtual UWorld* GetTickableGameObjectWorld() const override`
- L226 _public function_ `virtual TStatId GetStatId() const`

#### Free symbols / members of external scopes

- L42 _delegate_ `DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAgentAvatarChangedDelegate, UMLAdapterAgent& , AActor* );`
- L43 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FOnBeginAgentRemove, UMLAdapterAgent& );`
