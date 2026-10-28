# Plugins / LearningTraining

- module root: `Plugins/Experimental/LearningCore/Source/LearningTraining`
- headers: 8; symbols: 381
- symbol kinds: class=2, enum=6, enumerator=35, function=12, macro=4, member=122, namespace=22, prototype=162, struct=12, variable=4
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, JsonUtilities, Learning, Networking, Projects, Sockets
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Private/LearningSharedMemoryTraining.h` (Private)


#### enum `UE::Learning::SharedMemoryTraining::EControls`  
`enum class EControls : uint8`  
_L16-30_
- L18 _public enumerator_ `ExperienceEpisodeNum = 0`
- L19 _public enumerator_ `ExperienceStepNum = 1`
- L20 _public enumerator_ `ExperienceSignal = 2`
- L21 _public enumerator_ `ConfigSignal = 3`
- L22 _public enumerator_ `NetworkSignal = 4`
- L23 _public enumerator_ `CompleteSignal = 5`
- L24 _public enumerator_ `StopSignal = 6`
- L25 _public enumerator_ `PingSignal = 7`
- L26 _public enumerator_ `NetworkId = 8`
- L27 _public enumerator_ `ReplayBufferId = 9`
- L29 _public enumerator_ `ControlNum = 10`

#### Free symbols / members of external scopes

- L9 _namespace_ `namespace UE`
- L9 _namespace_ `namespace Learning` (scope `UE`)
- L14 _namespace_ `namespace SharedMemoryTraining` (scope `UE::Learning`)
- L32 _prototype_ `uint8 GetControlNum();` (scope `UE::Learning::SharedMemoryTraining`)
- L34 _prototype_ `ETrainerResponse SendConfigSignal( TLearningArrayView<1, volatile int32> Controls, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SharedMemoryTraining`)
- L38 _prototype_ `ETrainerResponse RecvNetwork( TLearningArrayView<1, volatile int32> Controls, const int32 NetworkId, ULearningNeuralNetworkData& OutNetwork, FSubprocess* Process, const TLearningArrayView<1, const uint8> NetworkData, const float Timeout = Trainer::DefaultTimeout, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SharedMemoryTraining`)
- L48 _prototype_ `ETrainerResponse SendStop( TLearningArrayView<1, volatile int32> Controls);` (scope `UE::Learning::SharedMemoryTraining`)
- L51 _prototype_ `bool HasNetworkOrCompleted(TLearningArrayView<1, volatile int32> Controls);` (scope `UE::Learning::SharedMemoryTraining`)
- L53 _prototype_ `ETrainerResponse SendNetwork( TLearningArrayView<1, volatile int32> Controls, const int32 NetworkId, TLearningArrayView<1, uint8> NetworkData, FSubprocess* Process, const ULearningNeuralNetworkData& Network, const float Timeout = Trainer::DefaultTimeout, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SharedMemoryTraining`)
- L63 _prototype_ `ETrainerResponse SendExperience( TLearningArrayView<1, int32> EpisodeStarts, TLearningArrayView<1, int32> EpisodeLengths, TLearningArrayView<1, ECompletionMode> EpisodeCompletionModes, TArrayView<TLearningArrayView<2, float>> EpisodeFinalObservations, TArrayView<TLearningArrayView<2, float>> EpisodeFinalMemoryStates, TArrayView<TLearningArrayView<2, float>> Observations, TArrayView<TLearningArrayView<2, float>> Actions, TArrayView<TLearningArrayView<2, float>> ActionModifiers, TArrayView<TLearningArrayView<2, float>> MemoryStates, TArrayView<TLearningArrayView<2, float>> Rewards, TLearningArrayView<1, volatile int32> Controls, FSubprocess* Process, const int32 ReplayBufferId, const FReplayBuffer& ReplayBuffer, const float Timeout = Trainer::DefaultTimeout, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SharedMemoryTraining`)

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Private/LearningSocketTraining.h` (Private)


#### enum `UE::Learning::SocketTraining::ESignal`  
`enum class ESignal : uint8`  
_L17-27_
- L19 _public enumerator_ `Invalid = 0`
- L20 _public enumerator_ `SendConfig = 1`
- L21 _public enumerator_ `SendExperience = 2`
- L22 _public enumerator_ `RecvNetwork = 3`
- L23 _public enumerator_ `SendNetwork = 4`
- L24 _public enumerator_ `RecvComplete = 5`
- L25 _public enumerator_ `SendStop = 6`
- L26 _public enumerator_ `RecvPing = 7`

#### Free symbols / members of external scopes

- L11 _namespace_ `namespace UE`
- L11 _namespace_ `namespace Learning` (scope `UE`)
- L15 _namespace_ `namespace SocketTraining` (scope `UE::Learning`)
- L29 _prototype_ `ETrainerResponse WaitForConnection( FSocket& Socket, FSubprocess* Process, const FInternetAddr& Addr, const float Timeout = Trainer::DefaultTimeout);` (scope `UE::Learning::SocketTraining`)
- L35 _prototype_ `ETrainerResponse RecvWithTimeout( FSocket& Socket, FSubprocess* Process, uint8* Bytes, const int32 ByteNum, const float Timeout = Trainer::DefaultTimeout);` (scope `UE::Learning::SocketTraining`)
- L42 _prototype_ `ETrainerResponse RecvNetwork( FSocket& Socket, const int32 NetworkId, int32& OutNetworkVersion, ULearningNeuralNetworkData& OutNetwork, FSubprocess* Process, TLearningArrayView<1, uint8> OutNetworkBuffer, const float Timeout = Trainer::DefaultTimeout, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings, const float SignalTimeout = Trainer::DefaultTimeout);` (scope `UE::Learning::SocketTraining`)
- L54 _prototype_ `ETrainerResponse SendWithTimeout( FSocket& Socket, FSubprocess* Process, const uint8* Bytes, const int32 ByteNum, const float Timeout = Trainer::DefaultTimeout);` (scope `UE::Learning::SocketTraining`)
- L61 _prototype_ `ETrainerResponse SendConfig( FSocket& Socket, const FString& ConfigString, FSubprocess* Process, const float Timeout = Trainer::DefaultTimeout, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SocketTraining`)
- L68 _prototype_ `ETrainerResponse SendStop( FSocket& Socket, FSubprocess* Process, const float Timeout = Trainer::DefaultTimeout);` (scope `UE::Learning::SocketTraining`)
- L73 _prototype_ `bool HasNetworkOrCompleted( FSocket& Socket, FSubprocess* Process);` (scope `UE::Learning::SocketTraining`)
- L77 _prototype_ `ETrainerResponse SendNetwork( FSocket& Socket, TLearningArrayView<1, uint8> NetworkBuffer, FSubprocess* Process, const int32 NetworkId, const ULearningNeuralNetworkData& Network, const float Timeout = Trainer::DefaultTimeout, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SocketTraining`)
- L87 _prototype_ `ETrainerResponse SendExperience( FSocket& Socket, const int32 NetworksVersion, const int32 ReplayBufferId, const FReplayBuffer& ReplayBuffer, FSubprocess* Process, const float Timeout = Trainer::DefaultTimeout, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SocketTraining`)
- L96 _prototype_ `ETrainerResponse SendExperience( FSocket& Socket, const TLearningArrayView<1, const int32> EpisodeStartsExperience, const TLearningArrayView<1, const int32> EpisodeLengthsExperience, const TLearningArrayView<2, const float> ObservationExperience, const TLearningArrayView<2, const float> ActionExperience, FSubprocess* Process, const float Timeout = Trainer::DefaultTimeout, const ELogSetting LogSettings = Trainer::DefaultLogSettings);` (scope `UE::Learning::SocketTraining`)

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Public/LearningExperience.h` (Public)


#### struct `UE::Learning::FEpisodeBuffer`  
`struct FEpisodeBuffer`  
_L25-136_
- desc: Buffer storing the observations, actions, and rewards of multiple instances over an episode
- L35 _public prototype_ `void Resize(const int32 InMaxInstanceNum, const int32 InMaxStepNum);` — Resize the experience buffer @param InMaxInstanceNum				Maximum number of instances @param InMaxStepNum					Maximum number of steps in an episode
- L40 _public prototype_ `void Reset(const FIndexSet Instances);` — Reset the buffer for the given set of instances
- L45 _public prototype_ `int32 AddObservations(const FName& Name, const int32 SchemaId, const int32 Size);`
- L47 _public prototype_ `void PushObservations(const int32 ObservationId, const TLearningArrayView<2, const float> InObservations, const FIndexSet Instances);`
- L49 _public prototype_ `const TLearningArrayView<2, const float> GetObservations(const int32 ObservationId, const int32 InstanceIdx) const;`
- L54 _public prototype_ `int32 AddActions(const FName& Name, const int32 SchemaId, const int32 Size);`
- L56 _public prototype_ `void PushActions(const int32 ActionId, const TLearningArrayView<2, const float> InActions, const FIndexSet Instances);`
- L58 _public prototype_ `const TLearningArrayView<2, const float> GetActions(const int32 ActionId, const int32 InstanceIdx) const;`
- L63 _public prototype_ `int32 AddActionModifiers(const FName& Name, const int32 SchemaId, const int32 Size);`
- L65 _public prototype_ `void PushActionModifiers(const int32 ActionModifierId, const TLearningArrayView<2, const float> InActionModifiers, const FIndexSet Instances);`
- L67 _public prototype_ `const TLearningArrayView<2, const float> GetActionModifiers(const int32 ActiActionModifierIdnId, const int32 InstanceIdx) const;`
- L72 _public prototype_ `int32 AddMemoryStates(const FName& Name, const int32 Size);`
- L74 _public prototype_ `void PushMemoryStates(const int32 MemoryStateId, const TLearningArrayView<2, const float> InMemoryStates, const FIndexSet Instances);`
- L76 _public prototype_ `const TLearningArrayView<2, const float> GetMemoryStates(const int32 MemoryStateId, const int32 InstanceIdx) const;`
- L81 _public prototype_ `int32 AddRewards(const FName& Name, const int32 Size);`
- L84 _public prototype_ `void PushRewards(const int32 RewardId, const TLearningArrayView<1, const float> InRewards, const FIndexSet Instances);` — Convenience overload for pushing rewards from a Training Environment
- L86 _public prototype_ `void PushRewards(const int32 RewardId, const TLearningArrayView<2, const float> InRewards, const FIndexSet Instances);`
- L88 _public prototype_ `const TLearningArrayView<2, const float> GetRewards(const int32 RewardId, const int32 InstanceIdx) const;`
- L93 _public prototype_ `void IncrementEpisodeStepNums(const FIndexSet Instances);`
- L95 _public prototype_ `const TLearningArrayView<1, const int32> GetEpisodeStepNums() const;`
- L97 _public prototype_ `int32 GetMaxInstanceNum() const;`
- L98 _public prototype_ `int32 GetMaxStepNum() const;`
- L102 _private member_ `bool bHasBeenSized = false;`
- L103 _private member_ `int32 MaxInstanceNum = 0;`
- L104 _private member_ `int32 MaxStepNum = 0;`
- L107 _private member_ `TArray<FName, TInlineAllocator<1>> ObservationNames;` — Observations
- L108 _private member_ `TArray<int32, TInlineAllocator<1>> ObservationSchemaIds;`
- L109 _private member_ `TArray<int32, TInlineAllocator<1>> ObservationSizes;`
- L110 _private member_ `TArray<TLearningArray<3, float>, TInlineAllocator<1>> ObservationArrays;`
- L113 _private member_ `TArray<FName, TInlineAllocator<1>> ActionNames;` — Actions
- L114 _private member_ `TArray<int32, TInlineAllocator<1>> ActionSchemaIds;`
- L115 _private member_ `TArray<int32, TInlineAllocator<1>> ActionSizes;`
- L116 _private member_ `TArray<TLearningArray<3, float>, TInlineAllocator<1>> ActionArrays;`
- L119 _private member_ `TArray<FName, TInlineAllocator<1>> ActionModifierNames;` — Action Modifiers
- L120 _private member_ `TArray<int32, TInlineAllocator<1>> ActionModifierSchemaIds;`
- L121 _private member_ `TArray<int32, TInlineAllocator<1>> ActionModifierSizes;`
- L122 _private member_ `TArray<TLearningArray<3, float>, TInlineAllocator<1>> ActionModifierArrays;`
- L125 _private member_ `TArray<FName, TInlineAllocator<1>> MemoryStateNames;` — Memory States
- L126 _private member_ `TArray<int32, TInlineAllocator<1>> MemoryStateSizes;`
- L127 _private member_ `TArray<TLearningArray<3, float>, TInlineAllocator<1>> MemoryStateArrays;`
- L130 _private member_ `TArray<FName, TInlineAllocator<1>> RewardNames;` — Rewards
- L131 _private member_ `TArray<int32, TInlineAllocator<1>> RewardSizes;`
- L132 _private member_ `TArray<TLearningArray<3, float>, TInlineAllocator<1>> RewardArrays;`
- L135 _private member_ `TLearningArray<1, int32> EpisodeStepNums;` — Episode Step Nums

#### struct `UE::Learning::FReplayBuffer`  
`struct FReplayBuffer`  
_L142-269_
- desc: Large buffer that sequentially concatenates a series of episodes in a large flat array. Used to collate episodic data together from multiple instances.
- L151 _public prototype_ `void Resize( const FEpisodeBuffer& EpisodeBuffer, const int32 InMaxEpisodeNum = 2048, const int32 InMaxStepNum = 16384);` — Resizes the replay buffer. @param EpisodeBuffer		Determines the dimensionality of the various arrays @param MaxEpisodeNum		Maximum number of episodes to be stored in the buffer @param MaxStepNum			Maximum number of steps to be stored in the buffer
- L159 _public prototype_ `void Reset();` — Reset the replay buffer. Does not free memory - just resets episode and sample num to zero.
- L173 _public prototype_ `bool AddEpisodes( const TLearningArrayView<1, const ECompletionMode> InEpisodeCompletionModes, const TArrayView<const TLearningArrayView<2, const float>> InEpisodeFinalObservations, const TArrayView<const TLearningArrayView<2, const float>> InEpisodeFinalMemoryStates, const FEpisodeBuffer& EpisodeBuffer, const FIndexSet Instances, const bool bAddTruncatedEpisodeWhenFull = true);` — Add a set of episodes to the replay buffer @param InEpisodeCompletionModes		Array of completion modes for each instance of shape (InstanceNum) @param InEpisodeFinalObservations		Array of final observations for each instance of shape (InstanceNum, ObservationVectorDimNum) @param InEpisodeFinalMemoryStates		Array of final memory states (post-evaluation) for each instance of shape (InstanceNum, MemoryStateVectorDimNum) @param EpisodeBuffer					Episode buffer to add experience from @param Instances						Instances to add @param bAddTruncatedEpisodeWhenFull	When enabled, this will add a truncated, partial episode to the buffer when full @returns								True when the replay buffer is full
- L188 _public prototype_ `void AddRecords( const int32 InEpisodeNum, const int32 InMaxStepNum, const int32 ObservationSchemaId, const int32 ObservationNum, const int32 ActionSchemaId, const int32 ActionNum, const TLearningArrayView<1, const int32> RecordedEpisodeStarts, const TLearningArrayView<1, const int32> RecordedEpisodeLengths, const TLearningArrayView<2, const float> RecordedObservations, const TLearningArrayView<2, const float> RecordedActions);` — Alternate way to add data from records generated via imitation learning. Does the resizing needed. Putting this in place until we have more time later to rewrite how imitation learning stores data. At this time, it seems logical to have the data records be implemented in terms of EpisodeBuffer(s), in which case this method may no longer be needed.
- L200 _public prototype_ `bool HasCompletions() const;`
- L202 _public prototype_ `bool HasFinalObservations() const;`
- L204 _public prototype_ `bool HasFinalMemoryStates() const;`
- L206 _public prototype_ `int32 GetMaxEpisodeNum() const;`
- L207 _public prototype_ `int32 GetMaxStepNum() const;`
- L208 _public prototype_ `int32 GetEpisodeNum() const;`
- L209 _public prototype_ `int32 GetStepNum() const;`
- L211 _public prototype_ `const TLearningArrayView<1, const int32> GetEpisodeStarts() const;`
- L212 _public prototype_ `const TLearningArrayView<1, const int32> GetEpisodeLengths() const;`
- L213 _public prototype_ `const TLearningArrayView<1, const ECompletionMode> GetEpisodeCompletionModes() const;`
- L215 _public prototype_ `int32 GetObservationsNum() const;`
- L216 _public prototype_ `const TLearningArrayView<2, const float> GetObservations(const int32 Index) const;`
- L217 _public prototype_ `const TLearningArrayView<2, const float> GetEpisodeFinalObservations(const int32 Index) const;`
- L219 _public prototype_ `int32 GetActionsNum() const;`
- L220 _public prototype_ `const TLearningArrayView<2, const float> GetActions(const int32 Index) const;`
- L222 _public prototype_ `int32 GetActionModifiersNum() const;`
- L223 _public prototype_ `const TLearningArrayView<2, const float> GetActionModifiers(const int32 Index) const;`
- L225 _public prototype_ `int32 GetMemoryStatesNum() const;`
- L226 _public prototype_ `const TLearningArrayView<2, const float> GetMemoryStates(const int32 Index) const;`
- L227 _public prototype_ `const TLearningArrayView<2, const float> GetEpisodeFinalMemoryStates(const int32 Index) const;`
- L229 _public prototype_ `int32 GetRewardsNum() const;`
- L230 _public prototype_ `const TLearningArrayView<2, const float> GetRewards(const int32 Index) const;`
- L232 _public prototype_ `TSharedRef<FJsonObject> AsJsonConfig(const int32 ReplayBufferId) const;`
- L236 _private member_ `bool bHasCompletions = false;`
- L237 _private member_ `bool bHasFinalObservations = false;`
- L238 _private member_ `bool bHasFinalMemoryStates = false;`
- L240 _private member_ `int32 MaxEpisodeNum = 0;`
- L241 _private member_ `int32 MaxStepNum = 0;`
- L243 _private member_ `int32 EpisodeNum = 0;`
- L244 _private member_ `int32 StepNum = 0;`
- L246 _private member_ `TLearningArray<1, int32> EpisodeStarts;`
- L247 _private member_ `TLearningArray<1, int32> EpisodeLengths;`
- L248 _private member_ `TLearningArray<1, ECompletionMode> EpisodeCompletionModes;`
- L250 _private member_ `TArray<FName, TInlineAllocator<1>> ObservationNames;`
- L251 _private member_ `TArray<int32, TInlineAllocator<1>> ObservationSchemaIds;`
- L252 _private member_ `TArray<TLearningArray<2, float>, TInlineAllocator<1>> Observations;`
- L253 _private member_ `TArray<TLearningArray<2, float>, TInlineAllocator<1>> EpisodeFinalObservations;`
- L255 _private member_ `TArray<FName, TInlineAllocator<1>> ActionNames;`
- L256 _private member_ `TArray<int32, TInlineAllocator<1>> ActionSchemaIds;`
- L257 _private member_ `TArray<TLearningArray<2, float>, TInlineAllocator<1>> Actions;`
- L259 _private member_ `TArray<FName, TInlineAllocator<1>> ActionModifierNames;`
- L260 _private member_ `TArray<int32, TInlineAllocator<1>> ActionModifierSchemaIds;`
- L261 _private member_ `TArray<TLearningArray<2, float>, TInlineAllocator<1>> ActionModifiers;`
- L263 _private member_ `TArray<FName, TInlineAllocator<1>> MemoryStateNames;`
- L264 _private member_ `TArray<TLearningArray<2, float>, TInlineAllocator<1>> MemoryStates;`
- L265 _private member_ `TArray<TLearningArray<2, float>, TInlineAllocator<1>> EpisodeFinalMemoryStates;`
- L267 _private member_ `TArray<FName, TInlineAllocator<1>> RewardNames;`
- L268 _private member_ `TArray<TLearningArray<2, float>, TInlineAllocator<1>> Rewards;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API LEARNINGTRAINING_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Learning` (scope `UE`)
- L271 _namespace_ `namespace Experience` (scope `UE::Learning`)
- L296 _prototype_ `void GatherExperienceUntilReplayBufferFull( FReplayBuffer& ReplayBuffer, FEpisodeBuffer& EpisodeBuffer, FResetInstanceBuffer& ResetBuffer, const TArrayView<const TLearningArrayView<2, const float>> ObservationVectorBuffers, const TArrayView<const TLearningArrayView<2, const float>> ActionVectorBuffers, const TArrayView<const TLearningArrayView<2, const float>> PreEvaluationMemoryStateVectorBuffers, const TArrayView<const TLearningArrayView<2, const float>> MemoryStateVectorBuffers, const TArrayView<const TLearningArrayView<1, const float>> RewardBuffers, TLearningArrayView<1, ECompletionMode> CompletionBuffer, TLearningArrayView<1, ECompletionMode> EpisodeCompletionBuffer, TLearningArrayView<1, ECompletionMode> AllCompletionBuffer, const TFunctionRef<void(const FIndexSet Instances)> ResetFunction, const TArrayView<const TFunctionRef<void(const FIndexSet Instances)>> ObservationFunctions, const TArrayView<const TFunctionRef<void(const FIndexSet Instances)>> PolicyFunctions, const TArrayView<const TFunctionRef<void(const FIndexSet Instances)>> ActionFunctions, const TArrayView<const TFunctionRef<void(const FIndexSet Instances)>> UpdateFunctions, const TArrayView<const TFunctionRef<void(const FIndexSet Instances)>> RewardFunctions, const TFunctionRef<void(const FIndexSet Instances)> CompletionFunction, const FIndexSet Instances);` (scope `UE::Learning::Experience`) — Resets, and then runs experience gathering until the provided replay buffer is full @param ReplayBuffer							Replay Buffer @param EpisodeBuffer							Episode Buffer @param ResetBuffer							Reset Buffer @param ObservationVectorBuffers				Buffers to read/write observation vectors into @param ActionVectorBuffers					Buffers to read/write action vectors into @param PreEvaluationMemoryStateVectorBuffers	Buffers to read/write pre-evaluation memory state vectors into @param MemoryStateVectorBuffers				Buffers to read/write (post-evaluation) memory state vectors into @param RewardBuffers							Buffers to read/write rewards into @param CompletionBuffer						Buffer to read/write completions into @param EpisodeCompletionBuffer				Additional buffer to record completions from full episode buffers @param AllCompletionBuffer					Additional buffer to record all completions from full episodes and normal completions @param ResetFunction							Function to run for resetting the environment @param ObservationFunctions					Functions to run for evaluating observations @param PolicyFunctions						Functions to run generating actions from observations @param ActionFunctions						Functions to run for evaluating actions @param UpdateFunctions						Functions to run for updating the environment @param RewardFunctions						Functions to run for evaluating rewards @param CompletionFunction						Function to run for evaluating completions @param Instances								Set of instances to gather experience for

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Public/LearningExternalTrainer.h` (Public)


#### struct `UE::Learning::IExternalTrainer`  
`struct IExternalTrainer`  
_L27-146_
- desc: Interface for communicating with an external trainer process.
- L29 _public prototype_ `virtual ~IExternalTrainer() = default;`
- L32 _public prototype_ `virtual bool IsValid() = 0;` — Returns true if this trainer is valid. Otherwise, false.
- L35 _public prototype_ `virtual void Terminate() = 0;` — Terminate the trainer immediately.
- L38 _public prototype_ `virtual ETrainerResponse SendStop() = 0;` — Signal for the trainer to stop.
- L46 _public prototype_ `virtual ETrainerResponse Wait() = 0;` — Wait for the trainer to finish. @param Timeout		Timeout to wait in seconds @returns				Trainer response
- L49 _public prototype_ `virtual bool HasNetworkOrCompleted() = 0;` — Returns true if we can receive a network or training completed. Otherwise, false.
- L60 _public prototype_ `virtual ETrainerResponse SendConfigs( const TSharedRef<FJsonObject>& DataConfigObject, const TSharedRef<FJsonObject>& ModelConfigObject, const TSharedRef<FJsonObject>& TrainerConfigObject, const ELogSetting LogSettings = Trainer::DefaultLogSettings) = 0;` — Sends the given json configs to the trainer process. @param DataConfigObject		The config to send with data-related settings (replay buffers, schemas) @param ModelConfigObject		The config to send with model-related settings (networks, architecture) @param TrainerConfigObject	The config to send with trainer-specific settings @param LogSettings			The log verbosity level @returns						Trainer response
- L73 _public prototype_ `virtual int32 AddNetwork(const ULearningNeuralNetworkData& Network) = 0;` — Adds the network to this external trainer. Allocates buffers, etc. Must be called for each network prior to calling Send/Receive. @params Network	The network to be added @returns			The network's unique id
- L85 _public prototype_ `virtual ETrainerResponse ReceiveNetwork( const int32 NetworkId, ULearningNeuralNetworkData& OutNetwork, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) = 0;` — Wait for the trainer to push an updated network. @param NetworkId		Unique network id @param OutNetwork		Network to update @param Timeout		Timeout to wait in seconds @param NetworkLock	Lock to use when updating network @param LogSettings	The log verbosity level @returns				Trainer response
- L101 _public prototype_ `virtual TArray<ETrainerResponse> ReceiveNetworks( const TArray<int32>& NetworkIds, TArray<TObjectPtr<ULearningNeuralNetworkData>> Networks, TArray<FRWLock*> NetworkLocks = TArray<FRWLock*>(), const ELogSetting LogSettings = Trainer::DefaultLogSettings) = 0;` — Wait for the trainer to push an array of updated networks. @param NetworkIds		Unique network ids @param OutNetworks		Networks to update @param Timeout		Timeout to wait in seconds @param NetworkLocks	Locks to use when updating networks @param LogSettings	The log verbosity level @returns				Trainer response
- L117 _public prototype_ `virtual ETrainerResponse SendNetwork( const int32 NetworkId, const ULearningNeuralNetworkData& Network, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) = 0;` — Wait for the trainer to be ready and push the current policy network. @param NetworkId		Unique network id @param Network		Network to push @param Timeout		Timeout to wait in seconds @param NetworkLock	Lock to use when pushing network @param LogSettings	The log verbosity level @returns				Trainer response
- L130 _public prototype_ `virtual int32 AddReplayBuffer(const FReplayBuffer& ReplayBuffer) = 0;` — Adds a named replay buffer to this external trainer. Must be called for each buffer prior to calling SendReplayBuffer. @params ReplayBuffer		The buffer to be added @returns					The replay buffer's unique id
- L142 _public prototype_ `virtual ETrainerResponse SendReplayBuffer( const int32 ReplayBufferId, const FReplayBuffer& ReplayBuffer, const ELogSetting LogSettings = Trainer::DefaultLogSettings) = 0;` — Wait for the trainer to be ready and send new experience. @params ReplayBufferId	Unique replay buffer id @params Name				The unique name of the buffer, used as a key @param ReplayBuffer		Replay buffer to send @param Timeout			Timeout to wait in seconds @param LogSettings		The log verbosity level @returns					Trainer response

#### struct `UE::Learning::FSharedMemoryTrainerServerProcess`  
`struct FSharedMemoryTrainerServerProcess`  
_L152-219_
- desc: This object allows you to launch the FSharedMemoryTrainer server as a subprocess, which is convenient when you want to train locally.
- L169 _public prototype_ `FSharedMemoryTrainerServerProcess( const FString& TaskName, const FString& CustomTrainerPath, const FString& TrainerFileName, const FString& PythonExecutablePath, const FString& PythonContentPath, const FString& InIntermediatePath, const FString& NneCpuContentPath, const float InTimeout = Trainer::DefaultTimeout, const ESubprocessFlags TrainingProcessFlags = ESubprocessFlags::None, const ELogSetting LogSettings = ELogSetting::Normal);` — Creates a training server as a subprocess using shared memory for communication. This will no-op if this UE process has a non-zero "LearningProcessIdx". @param TaskName					The name of this training task (used to disambiguate filenames, etc.) @param CustomTrainerPath			Path to check for custom trainer files @param TrainerFileName			The name of the training file to use @param PythonExecutablePath		Path to the python executable used for training. In general should be the python shipped with Unreal Editor. @param PythonContentPath			Path to the Python Content folder provided by the Learning plugin @param InIntermediatePath			Path to the intermediate folder to write temporary files, logs, and snapshots to @param TrainingProcessFlags		Training server subprocess flags @param LogSettings				Logging settings to use
- L182 _public prototype_ `bool IsRunning() const;` — Check if the server process is still running.
- L190 _public prototype_ `bool Wait();` — Wait for the server process to end @param Timeout		Timeout to wait in seconds @returns				true if successful, otherwise false if it times out
- L193 _public prototype_ `void Terminate();` — Terminate the server process.
- L196 _public prototype_ `TSharedMemoryArrayView<1, volatile int32> GetControlsSharedMemoryArrayView() const;` — Get the Controls shared memory array view.
- L199 _public prototype_ `const FString& GetIntermediatePath() const;` — Get the intermediate path.
- L202 _public prototype_ `const FString& GetConfigPath() const;` — Get the config path.
- L205 _public prototype_ `FSubprocess* GetTrainingSubprocess();` — Get the training subprocess.
- L210 _private prototype_ `void Deallocate();` — Free and deallocate all shared memory.
- L212 _private member_ `FString IntermediatePath;`
- L213 _private member_ `FString ConfigPath;`
- L215 _private member_ `TSharedMemoryArrayView<1, volatile int32> Controls;` — Mark as volatile to avoid compiler optimizing away reads without writes etc.
- L217 _private member_ `FSubprocess TrainingProcess;`
- L218 _private member_ `float Timeout = Trainer::DefaultTimeout;`

#### struct `UE::Learning::FSharedMemoryTrainer`  
`struct FSharedMemoryTrainer : public IExternalTrainer`  
_L227-330_
- inherits: `IExternalTrainer`
- desc: Trainer that connects to an external training server to perform training This trainer can be used to allow the python training process the run on a different machine to the experience gathering process.
- L258 _public prototype_ `FSharedMemoryTrainer( const FString& InTaskName, const TSharedPtr<FSharedMemoryTrainerServerProcess>& ExternalTrainerProcess, const bool bUseExternalTrainingProcess = false, const FGuid ControlsGuid = FGuid(), const FString& InConfigPath = FString(), const FString& InIntermediatePath = FString(), const float InTimeout = Trainer::DefaultTimeout);` — Creates a new SharedMemory trainer @param InTaskName						Unique name for this training task - used to avoid config filename conflicts @param ExternalTrainerProcess			Shared memory used for communicating status to the trainer server process @param bUseExternalTrainingProcess	If true, attach to existing external training process. @param ControlsGuid					If bUseExternalTrainingProcess is true, attach to this controls memory. @param InConfigPath					The path to write the config to. @param InIntermediatePath				The Intermediate Path - for writing temporary files. @param InTimeout						Timeout to wait in seconds for connection and initial data transfer
- L267 _public prototype_ `~FSharedMemoryTrainer();`
- L269 _public prototype_ `virtual bool IsValid() override final;`
- L271 _public prototype_ `virtual void Terminate() override final;`
- L273 _public prototype_ `virtual ETrainerResponse SendStop() override final;`
- L275 _public prototype_ `virtual ETrainerResponse Wait() override final;`
- L277 _public prototype_ `virtual bool HasNetworkOrCompleted() override final;`
- L279 _public prototype_ `virtual ETrainerResponse SendConfigs( const TSharedRef<FJsonObject>& DataConfigObject, const TSharedRef<FJsonObject>& ModelConfigObject, const TSharedRef<FJsonObject>& TrainerConfigObject, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L285 _public prototype_ `virtual int32 AddNetwork(const ULearningNeuralNetworkData& Network) override final;`
- L287 _public prototype_ `virtual ETrainerResponse ReceiveNetwork( const int32 NetworkId, ULearningNeuralNetworkData& OutNetwork, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L293 _public prototype_ `virtual TArray<ETrainerResponse> ReceiveNetworks( const TArray<int32>& NetworkIds, TArray<TObjectPtr<ULearningNeuralNetworkData>> Networks, TArray<FRWLock*> NetworkLocks = TArray<FRWLock*>(), const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L299 _public prototype_ `virtual ETrainerResponse SendNetwork( const int32 NetworkId, const ULearningNeuralNetworkData& Network, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L305 _public prototype_ `virtual int32 AddReplayBuffer(const FReplayBuffer& ReplayBuffer) override final;`
- L307 _public prototype_ `virtual ETrainerResponse SendReplayBuffer( const int32 ReplayBufferId, const FReplayBuffer& ReplayBuffer, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L315 _private prototype_ `void Deallocate();` — Free and deallocate all shared memory.
- L317 _private member_ `FString TaskName;`
- L318 _private member_ `FString IntermediatePath;`
- L319 _private member_ `FString ConfigPath;`
- L321 _private member_ `TSharedPtr<FSharedMemoryTrainerServerProcess> TrainingProcess = nullptr;`
- L323 _private member_ `float Timeout = Trainer::DefaultTimeout;`
- L325 _private member_ `bool bUseExternalTrainer = false;`
- L327 _private member_ `TSharedMemoryArrayView<1, volatile int32> Controls;`
- L328 _private member_ `TArray<TSharedMemoryArrayView<1, uint8>> NeuralNetworkSharedMemoryArrayViews;`
- L329 _private member_ `TArray<FSharedMemoryExperienceContainer> SharedMemoryExperienceContainers;`

#### struct `UE::Learning::FSharedMemoryTrainer::FSharedMemoryExperienceContainer`  
`struct FSharedMemoryExperienceContainer`  
_L229-245_
- L231 _public member_ `TSharedMemoryArrayView<1, int32> EpisodeStarts;`
- L232 _public member_ `TSharedMemoryArrayView<1, int32> EpisodeLengths;`
- L233 _public member_ `TSharedMemoryArrayView<1, ECompletionMode> EpisodeCompletionModes;`
- L235 _public member_ `TArray<TSharedMemoryArrayView<2, float>, TInlineAllocator<1>> EpisodeFinalObservations;`
- L236 _public member_ `TArray<TSharedMemoryArrayView<2, float>, TInlineAllocator<1>> EpisodeFinalMemoryStates;`
- L237 _public member_ `TArray<TSharedMemoryArrayView<2, float>, TInlineAllocator<1>> Observations;`
- L238 _public member_ `TArray<TSharedMemoryArrayView<2, float>, TInlineAllocator<1>> Actions;`
- L239 _public member_ `TArray<TSharedMemoryArrayView<2, float>, TInlineAllocator<1>> ActionModifiers;`
- L240 _public member_ `TArray<TSharedMemoryArrayView<2, float>, TInlineAllocator<1>> MemoryStates;`
- L241 _public member_ `TArray<TSharedMemoryArrayView<2, float>, TInlineAllocator<1>> Rewards;`
- L244 _public prototype_ `void Deallocate();` — Free and deallocate all shared memory.

#### struct `UE::Learning::FSocketTrainerServerProcess`  
`struct FSocketTrainerServerProcess`  
_L336-391_
- desc: This object allows you to launch the FSocketTrainer server as a subprocess, which is convenient when you want to train using it locally.
- L352 _public prototype_ `FSocketTrainerServerProcess( const FString& TaskName, const FString& CustomTrainerPath, const FString& TrainerFileName, const FString& PythonExecutablePath, const FString& PythonContentPath, const FString& IntermediatePath, const FString& NneCpuContentPath, const TCHAR* IpAddress = Trainer::DefaultIp, const uint32 Port = Trainer::DefaultPort, const float InTimeout = Trainer::DefaultTimeout, const ESubprocessFlags TrainingProcessFlags = ESubprocessFlags::None, const ELogSetting LogSettings = ELogSetting::Normal);` — Creates a training server as a subprocess @param TaskName					The name of this training task @param CustomTrainerPath			Path to check for custom trainer files @param TrainerFileName			The name of the training file to use @param PythonExecutablePath		Path to the python executable used for training. In general should be the python shipped with Unreal Editor. @param PythonContentPath			Path to the Python Content folder provided by the Learning plugin @param IntermediatePath			Path to the intermediate folder to write temporary files, logs, and snapshots to @param IpAddress					Ip address to bind the listening socket to. For a local server you will want to use 127.0.0.1 @param Port						Port to use for the listening socket. @param TrainingProcessFlags		Training server subprocess flags @param LogSettings				Logging settings to use
- L369 _public prototype_ `bool IsRunning() const;` — Check if the server process is still running
- L377 _public prototype_ `bool Wait();` — Wait for the server process to end @param Timeout		Timeout to wait in seconds @returns				true if successful, otherwise false if it times out
- L382 _public prototype_ `void Terminate();` — Terminate the server process
- L385 _public prototype_ `FSubprocess* GetTrainingSubprocess();` — Get the training subprocess.
- L389 _private member_ `FSubprocess TrainingProcess;`
- L390 _private member_ `float Timeout = Trainer::DefaultTimeout;`

#### struct `UE::Learning::FSocketTrainer`  
`struct FSocketTrainer : public IExternalTrainer`  
_L399-484_
- inherits: `IExternalTrainer`
- desc: Trainer that connects to an external training server to perform training This trainer can be used to allow the python training process the run on a different machine to the experience gathering process.
- L410 _public prototype_ `FSocketTrainer( ETrainerResponse& OutResponse, const TSharedPtr<FSocketTrainerServerProcess>& ExternalTrainerProcess, const bool bUseExternalTrainerProcess, const TCHAR* IpAddressOrHostname = Trainer::DefaultIp, const uint32 Port = Trainer::DefaultPort, const float InTimeout = Trainer::DefaultTimeout, const bool IsHostname = false);` — Creates a new Socket trainer @param OutResponse				Response to the initial connection @param ExternalTrainerProcess		The external trainer process @param IpAddress					Server Ip address @param Port						Server Port @param Timeout					Timeout to wait in seconds for connection and initial data transfer
- L419 _public prototype_ `~FSocketTrainer();`
- L421 _public prototype_ `virtual bool IsValid() override final;`
- L423 _public prototype_ `virtual void Terminate() override final;`
- L425 _public prototype_ `virtual ETrainerResponse SendStop() override final;`
- L427 _public prototype_ `virtual ETrainerResponse Wait() override final;`
- L429 _public prototype_ `virtual bool HasNetworkOrCompleted() override final;`
- L431 _public prototype_ `virtual ETrainerResponse SendConfigs( const TSharedRef<FJsonObject>& DataConfigObject, const TSharedRef<FJsonObject>& ModelConfigObject, const TSharedRef<FJsonObject>& TrainerConfigObject, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L437 _public prototype_ `virtual int32 AddNetwork(const ULearningNeuralNetworkData& Network) override final;`
- L439 _public prototype_ `virtual ETrainerResponse ReceiveNetwork( const int32 NetworkId, ULearningNeuralNetworkData& OutNetwork, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L445 _public prototype_ `virtual TArray<ETrainerResponse> ReceiveNetworks( const TArray<int32>& NetworkIds, TArray<TObjectPtr<ULearningNeuralNetworkData>> Networks, TArray<FRWLock*> NetworkLocks = TArray<FRWLock*>(), const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L451 _public prototype_ `virtual TArray<ETrainerResponse> ReceiveQueuedNetworks( const TArray<int32>& NetworkIds, TArray<TObjectPtr<ULearningNeuralNetworkData>> Networks, TArray<FRWLock*> NetworkLocks = TArray<FRWLock*>(), const ELogSetting LogSettings = Trainer::DefaultLogSettings);`
- L457 _public prototype_ `virtual ETrainerResponse SendNetwork( const int32 NetworkId, const ULearningNeuralNetworkData& Network, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L463 _public prototype_ `virtual int32 AddReplayBuffer(const FReplayBuffer& ReplayBuffer) override final;`
- L465 _public prototype_ `virtual ETrainerResponse SendReplayBuffer( const int32 ReplayBufferId, const FReplayBuffer& ReplayBuffer, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L472 _private member_ `TArray<TLearningArray<1, uint8>> NetworkBuffers;`
- L473 _private member_ `int32 LastReplayBufferId = -1;`
- L475 _private member_ `float Timeout = Trainer::DefaultTimeout;`
- L477 _private member_ `bool bUseExternalTrainer = false;`
- L479 _private member_ `TSharedPtr<FSocketTrainerServerProcess> TrainingProcess = nullptr;`
- L481 _private member_ `FSocket* Socket = nullptr;`
- L483 _private member_ `int32 NetworksVersion = -1;`

#### struct `UE::Learning::FFileTrainer`  
`struct FFileTrainer : public IExternalTrainer`  
_L486-549_
- inherits: `IExternalTrainer`
- L494 _public prototype_ `FFileTrainer(const FString& InIntermediatePath = FString(), ETrainerExportFlags InExportFlags = ETrainerExportFlags::All);` — Creates a new trainer that dumps training materials to file. @param InIntermediatePath				The Intermediate Path - for writing temporary files. @param InExportFlags					Which sections to export (defaults to All).
- L496 _public prototype_ `~FFileTrainer();`
- L498 _public function_ `virtual bool IsValid() override final`
- L500 _public function_ `virtual void Terminate() override final`
- L502 _public function_ `virtual ETrainerResponse SendStop() override final`
- L504 _public function_ `virtual ETrainerResponse Wait() override final`
- L506 _public function_ `virtual bool HasNetworkOrCompleted() override final`
- L508 _public prototype_ `virtual ETrainerResponse SendConfigs( const TSharedRef<FJsonObject>& DataConfigObject, const TSharedRef<FJsonObject>& ModelConfigObject, const TSharedRef<FJsonObject>& TrainerConfigObject, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L514 _public prototype_ `virtual int32 AddNetwork(const ULearningNeuralNetworkData& Network) override final;`
- L516 _public function_ `virtual ETrainerResponse ReceiveNetwork( const int32 NetworkId, ULearningNeuralNetworkData& OutNetwork, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final`
- L522 _public function_ `virtual TArray<ETrainerResponse> ReceiveNetworks( const TArray<int32>& NetworkIds, TArray<TObjectPtr<ULearningNeuralNetworkData>> Networks, TArray<FRWLock*> NetworkLocks = TArray<FRWLock*>(), const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final`
- L528 _public prototype_ `virtual ETrainerResponse SendNetwork( const int32 NetworkId, const ULearningNeuralNetworkData& Network, FRWLock* NetworkLock = nullptr, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L534 _public prototype_ `virtual int32 AddReplayBuffer(const FReplayBuffer& ReplayBuffer) override final;`
- L536 _public prototype_ `virtual ETrainerResponse SendReplayBuffer( const int32 ReplayBufferId, const FReplayBuffer& ReplayBuffer, const ELogSetting LogSettings = Trainer::DefaultLogSettings) override final;`
- L542 _private member_ `FString IntermediatePath;`
- L543 _private member_ `FString FileSaveDirectory;`
- L544 _private member_ `ETrainerExportFlags ExportFlags = ETrainerExportFlags::All;`
- L545 _private member_ `int32 ReplayBufferCount = 0;`
- L546 _private member_ `int32 NetworksCount = 0;`
- L548 _private member_ `TArray<TSharedMemoryArrayView<1, uint8>> NeuralNetworkSharedMemoryArrayViews;`

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LEARNINGTRAINING_API`
- L21 _namespace_ `namespace UE`
- L21 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Public/LearningPPOTrainer.h` (Public)


#### class `ULearningSocketPPOTrainerServerCommandlet`  
`class ULearningSocketPPOTrainerServerCommandlet : public UCommandlet`  
_L20-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UCommandlet`
- L24 _private prototype_ `ULearningSocketPPOTrainerServerCommandlet(const FObjectInitializer& ObjectInitializer);`
- L27 _private prototype_ `virtual int32 Main(const FString& Params) override;` — Runs the commandlet

#### struct `UE::Learning::FPPOTrainerTrainingSettings`  
`struct FPPOTrainerTrainingSettings`  
_L41-150_
- desc: Settings used for training with PPO
- L46 _public member_ `uint32 IterationNum = 1000000;` — Number of iterations to train the network for. Controls the overall training time. Training for about 100000 iterations should give you well trained network, but closer to 1000000 iterations or more is required for an exhaustively trained network.
- L49 _public member_ `float LearningRatePolicy = 0.0001f;` — Learning rate of the policy network. Typical values are between 0.001f and 0.0001f
- L53 _public member_ `float LearningRateCritic = 0.001f;` — Learning rate of the critic network. To avoid instability generally the critic should have a larger learning rate than the policy.
- L56 _public member_ `float LearningRateDecay = 1.0f;` — Amount by which to multiply the learning rate every 1000 iterations.
- L60 _public member_ `float WeightDecay = 0.0001f;` — Amount of weight decay to apply to the network. Larger values encourage network weights to be smaller but too large a value can cause the network weights to collapse to all zeros.
- L63 _public member_ `uint32 PolicyBatchSize = 1024;` — Batch size to use for training the policy. Large batch sizes are much more computationally efficient when training on the GPU.
- L66 _public member_ `uint32 CriticBatchSize = 4096;` — Batch size to use for training the critic. Large batch sizes are much more computationally efficient when training on the GPU.
- L70 _public member_ `uint32 PolicyWindow = 16;` — The number of consecutive steps of observations and actions over which to train the policy. Increasing this value will encourage the policy to use its memory effectively. Too large and training can become slow and unstable.
- L74 _public member_ `uint32 IterationsPerGather = 32;` — Number of training iterations to perform per buffer of experience gathered. This should be large enough for the critic and policy to be effectively updated, but too large and it will simply slow down training.
- L78 _public member_ `uint32 CriticWarmupIterations = 8;` — Number of iterations of training to perform to warm-up the Critic. This helps speed up and stabilize training at the beginning when the Critic may be producing predictions at the wrong order of magnitude.
- L83 _public member_ `float EpsilonClip = 0.2f;` — Clipping ratio to apply to policy updates. Keeps the training "on-policy". Larger values may speed up training at the cost of stability. Conversely, too small values will keep the policy from being able to learn an optimal policy.
- L86 _public member_ `float ReturnRegularizationWeight = 0.0001f;` — Weight used to regularize predicted returns. Encourages the critic not to over or under estimate returns.
- L89 _public member_ `float ActionSurrogateWeight = 1.0f;` — Weight for the loss used to train the policy via the PPO surrogate objective.
- L93 _public member_ `float ActionRegularizationWeight = 0.001f;` — Weight used to regularize actions.Larger values will encourage exploration and smaller actions, but too large will cause noisy actions centered around zero.
- L97 _public member_ `float ActionEntropyWeight = 0.0f;` — Weighting used for the entropy bonus. Larger values encourage larger action noise and therefore greater exploration but can make actions very noisy.
- L101 _public member_ `float GaeLambda = 0.95f;` — This is used in the Generalized Advantage Estimation, where larger values will tend to assign more credit to recent actions. Typical values should be between 0.9 and 1.0.
- L105 _public member_ `bool bAdvantageNormalization = true;` — When true, advantages are normalized. This tends to makes training more robust to adjustments of the scale of rewards.
- L109 _public member_ `float AdvantageMin = 0.0f;` — The minimum advantage to allow. Setting this below zero will encourage the policy to move away from bad actions, but can introduce instability.
- L113 _public member_ `float AdvantageMax = 10.0f;` — The maximum advantage to allow. Making this smaller may increase training stability at the cost of some training speed.
- L116 _public member_ `bool bUseGradNormMaxClipping = false;` — If true, uses gradient norm max clipping. Set this as True if training is unstable or leave as False if unused.
- L119 _public member_ `float GradNormMax = 0.5f;` — The maximum gradient norm to clip updates to.
- L124 _public member_ `int32 TrimEpisodeStartStepNum = 0;` — Number of steps to trim from the start of each episode during training. This can be useful if some reset process is taking several steps or you know your starting states are not entirely valid for example.
- L129 _public member_ `int32 TrimEpisodeEndStepNum = 0;` — Number of steps to trim from the end of each episode during training. This can be useful if you know the last few steps of an episode are not valid or contain incorrect information.
- L132 _public member_ `uint32 Seed = 1234;` — Random Seed to use for training
- L137 _public member_ `float DiscountFactor = 0.99f;` — The discount factor causes future rewards to be scaled down so that the policy will favor near-term rewards over potentially uncertain long-term rewards. Larger values encourage the system to "look-ahead" but make training more difficult.
- L140 _public member_ `ETrainerDevice Device = ETrainerDevice::GPU;` — Which device to use for training
- L146 _public member_ `bool bUseTensorboard = false;` — If to use TensorBoard for logging and tracking the training progress. TensorBoard will only work if it is installed in Unreal Engine's python environment. This can be done by enabling the "Tensorboard" plugin in your project.
- L149 _public member_ `bool bSaveSnapshots = false;` — If to save snapshots of the trained networks every 1000 iterations

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LEARNINGTRAINING_API`
- L30 _namespace_ `namespace UE`
- L30 _namespace_ `namespace Learning` (scope `UE`)
- L152 _namespace_ `namespace PPOTrainer` (scope `UE::Learning`)
- L193 _prototype_ `ETrainerResponse Train( IExternalTrainer* ExternalTrainer, FReplayBuffer& ReplayBuffer, FEpisodeBuffer& EpisodeBuffer, FResetInstanceBuffer& ResetBuffer, ULearningNeuralNetworkData& PolicyNetwork, ULearningNeuralNetworkData& CriticNetwork, ULearningNeuralNetworkData& EncoderNetwork, ULearningNeuralNetworkData& DecoderNetwork, TLearningArrayView<2, float> ObservationVectorBuffer, TLearningArrayView<2, float> ActionVectorBuffer, TLearningArrayView<2, float> PreEvaluationMemoryStateVectorBuffer, TLearningArrayView<2, float> MemoryStateVectorBuffer, TLearningArrayView<1, float> RewardBuffer, TLearningArrayView<1, ECompletionMode> CompletionBuffer, TLearningArrayView<1, ECompletionMode> EpisodeCompletionBuffer, TLearningArrayView<1, ECompletionMode> AllCompletionBuffer, const TFunctionRef<void(const FIndexSet Instances)> ResetFunction, const TFunctionRef<void(const FIndexSet Instances)> ObservationFunction, const TFunctionRef<void(const FIndexSet Instances)> PolicyFunction, const TFunctionRef<void(const FIndexSet Instances)> ActionFunction, const TFunctionRef<void(const FIndexSet Instances)> UpdateFunction, const TFunctionRef<void(const FIndexSet Instances)> RewardFunction, const TFunctionRef<void(const FIndexSet Instances)> CompletionFunction, const FIndexSet Instances, const Observation::FSchema& ObservationSchema, const Observation::FSchemaElement& ObservationSchemaElement, const Action::FSchema& ActionSchema, const Action::FSchemaElement& ActionSchemaElement, const FPPOTrainer ...` (scope `UE::Learning::PPOTrainer`) — Train a policy while gathering experience @param ExternalTrainer						External Trainer @param ReplayBuffer							Replay Buffer @param EpisodeBuffer							Episode Buffer @param ResetBuffer							Reset Buffer @param PolicyNetwork							Policy Network to use @param CriticNetwork							Critic Network to use @param EncoderNetwork							Encoder Network to use @param DecoderNetwork							Decoder Network to use @param ObservationVectorBuffer				Buffer to read/write observation vectors into @param ActionVectorBuffer						Buffer to read/write action vectors into @param PreEvaluationMemoryStateVectorBuffer	Buffer to read/write pre-evaluation memory state vectors into @param MemoryStateVectorBuffer				Buffer to read/write (post-evaluation) memory state vectors into @param RewardBuffer							Buffer to read/write rewards into @param CompletionBuffer						Buffer to read/write completions into @param EpisodeCompletionBuffer				Additional buffer to record completions from full episode buffers @param AllCompletionBuffer					Additional buffer to record all completions from full episodes and normal completions @param ResetFunction							Function to run for resetting the environment @param ObservationFunction					Function to run for evaluating observations @param PolicyFunction							Function to run for evaluating the policy @param ActionFunction							Function to run for evaluating actions @param UpdateFunction							Function to run for updating the environment @param RewardFunction							Functi

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Public/LearningSharedMemory.h` (Public)


#### struct `UE::Learning::TSharedMemoryArrayView`  
`template<uint8 DimNum, typename ElementType> struct TSharedMemoryArrayView`  
_L23-38_
- desc: Basic struct containing a view to a shared memory region, its guid, and a pointer to that region which is used for deallocation.
- L25 _public member_ `FGuid Guid;`
- L26 _public member_ `TLearningArrayView<DimNum, ElementType> View;`
- L27 _public member_ `FPlatformMemory::FSharedMemoryRegion* Region = nullptr;`
- L30 _public function_ `FString GetPlatformGuidString() const` — Gets a platform specific Guid string. This is required as guid strings on Mac must shorter to be used with shared memory

#### Free symbols / members of external scopes

- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Learning` (scope `UE`)
- L40 _namespace_ `namespace SharedMemory` (scope `UE::Learning`)
- L51 _function_ `template<uint8 DimNum, typename ElementType> TSharedMemoryArrayView<DimNum, ElementType> Map(const FGuid Guid, const TLearningArrayShape<DimNum>& Shape, const bool bCreate = false)` (scope `UE::Learning::SharedMemory`) — Map a view of a region of shared memory. @param Guid			Guid of the shared memory region @param Shape			Shape of the shared memory region @param bCreate		If this shared memory region should be created or if it already exists @returns				View of the shared memory region, guid, and pointer required for unmapping
- L79 _function_ `template<uint8 DimNum, typename ElementType> void Unmap(TSharedMemoryArrayView<DimNum, ElementType>& Memory)` (scope `UE::Learning::SharedMemory`) — Unmaps the view of the region of shared memory
- L96 _function_ `template<uint8 DimNum, typename ElementType> TSharedMemoryArrayView<DimNum, ElementType> Allocate(const TLearningArrayShape<DimNum>& Shape)` (scope `UE::Learning::SharedMemory`) — Allocate a region of shared memory. @param Shape			Shape of the shared memory region @returns				View of the shared memory region, guid, and pointer required for unmapping
- L105 _function_ `template<uint8 DimNum, typename ElementType> void Deallocate(TSharedMemoryArrayView<DimNum, ElementType>& Memory)` (scope `UE::Learning::SharedMemory`) — Deallocate the region of shared memory

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Public/LearningTrainer.h` (Public)


#### enum `UE::Learning::ETrainerDevice`  
`enum class ETrainerDevice : uint8`  
_L32-36_
- desc: Training Device
- L34 _public enumerator_ `CPU = 0`
- L35 _public enumerator_ `GPU = 1`

#### enum `UE::Learning::ETrainerResponse`  
`enum class ETrainerResponse : uint8`  
_L41-60_
- desc: Type of response from a Trainer
- L44 _public enumerator_ `Success = 0` — The communication was successful
- L47 _public enumerator_ `Unexpected = 1` — The communication send or received was unexpected
- L50 _public enumerator_ `Completed = 2` — Training is complete
- L53 _public enumerator_ `Stopped = 3` — Training is stopped
- L56 _public enumerator_ `Timeout = 4` — The communication timed-out
- L59 _public enumerator_ `NetworkSignalTimeout = 5` — The communication timed-out for a network signal

#### enum `UE::Learning::ESubprocessFlags`  
`enum class ESubprocessFlags : uint8`  
_L65-74_
- desc: Subprocess flags
- L67 _public enumerator_ `None = 0`
- L70 _public enumerator_ `ShowWindow = 1 << 0` — If to show the sub-process console window
- L73 _public enumerator_ `NoRedirectOutput = 1 << 1` — If to avoid redirecting the sub-process output to the output log

#### enum `UE::Learning::ETrainerExportFlags`  
`enum class ETrainerExportFlags : uint8`  
_L78-85_
- desc: Flags controlling which sections a trainer exports.
- L80 _public enumerator_ `None = 0`
- L81 _public enumerator_ `ReplayBuffers = 1 << 0` — ReplayBuffers/ dir: replay binaries + data-config.json
- L82 _public enumerator_ `Networks = 1 << 1` — Networks/ dir: network binaries + model-config.json
- L83 _public enumerator_ `TrainerConfig = 1 << 2` — trainer-config.json
- L84 _public enumerator_ `All = ReplayBuffers | Networks | TrainerConfig`

#### struct `UE::Learning::FSubprocess`  
`struct FSubprocess`  
_L91-137_
- desc: Simple managed subprocess similar to FMonitoredProcess
- L94 _public prototype_ `~FSubprocess();` — Will Terminate the subprocess if it is running.
- L104 _public prototype_ `bool Launch(const FString& Path, const FString& Params, const ESubprocessFlags Flags);` — Launches a new subprocess. @param Path The path of the executable to launch. @param Params The command line parameters. @param Flags Subprocess flags. @returns true if the launch was successful, otherwise false
- L109 _public prototype_ `bool IsRunning() const;` — Return true if the Subprocess is launched and running, otherwise false.
- L114 _public prototype_ `void Terminate();` — Terminates the subprocess
- L119 _public prototype_ `bool Update();` — Outputs anything the subprocess has written to stdout to the log line-by-line and returns true if the subprocess is still running.
- L124 _private member_ `FString OutputBuffer;` — Buffer for the subprocess' stdout
- L127 _private member_ `bool bIsLaunched = false;` — If a subprocess has been launched
- L130 _private member_ `FProcHandle ProcessHandle;` — Subprocess handle
- L133 _private member_ `void* ReadPipe = nullptr;` — Read pipe for subprocess stdout
- L136 _private member_ `void* WritePipe = nullptr;` — Write pipe for subprocess stdin

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LEARNINGTRAINING_API`
- L15 _namespace_ `namespace UE`
- L15 _namespace_ `namespace Learning` (scope `UE`)
- L17 _namespace_ `namespace Observation` (scope `UE::Learning`)
- L23 _namespace_ `namespace Action` (scope `UE::Learning`)
- L139 _namespace_ `namespace Trainer` (scope `UE::Learning`)
- L144 _variable_ `static constexpr float DefaultTimeout = 10.0f;` (scope `UE::Learning::Trainer`) — Default Timeout to use during communication.
- L149 _variable_ `static constexpr ELogSetting DefaultLogSettings = ELogSetting::Normal;` (scope `UE::Learning::Trainer`) — Default Log Settings to use during communication.
- L154 _variable_ `static constexpr const TCHAR* DefaultIp = TEXT("127` (scope `UE::Learning::Trainer`) — Default IP to use for networked training
- L159 _variable_ `static constexpr uint32 DefaultPort = 48491;` (scope `UE::Learning::Trainer`) — Default Port to use for networked training
- L164 _prototype_ `const TCHAR* GetDeviceString(const ETrainerDevice Device);` (scope `UE::Learning::Trainer`) — Converts a ETrainerDevice into a string.
- L169 _prototype_ `const TCHAR* GetResponseString(const ETrainerResponse Response);` (scope `UE::Learning::Trainer`) — Converts a ETrainerResponse into a string for use in logging and error messages.
- L178 _prototype_ `float DiscountFactorFromHalfLife(const float HalfLife, const float DeltaTime);` (scope `UE::Learning::Trainer`) — Compute the discount factor that corresponds to a particular HalfLife and DeltaTime. @param HalfLife		Time by which the reward should be discounted by half @param DeltaTime		DeltaTime taken upon each step of the environment @returns				Corresponding discount factor
- L186 _prototype_ `float DiscountFactorFromHalfLifeSteps(const int32 HalfLifeSteps);` (scope `UE::Learning::Trainer`) — Compute the discount factor that corresponds to a particular HalfLife provided in terms of number of steps @param HalfLifeSteps	Number of steps taken at which the reward should be discounted by half @returns				Corresponding discount factor
- L191 _prototype_ `FString GetPythonExecutablePath(const FString& EngineDir);` (scope `UE::Learning::Trainer`) — Gets the python executable path from the engine directory.
- L196 _prototype_ `FString GetSitePackagesPath(const FString& EngineDir);` (scope `UE::Learning::Trainer`) — Gets the PythonFoundationPackages site-packages path from the engine directory.
- L201 _prototype_ `FString GetPythonContentPath(const FString& EngineDir);` (scope `UE::Learning::Trainer`) — Gets the LearningAgents Content path from the engine directory.
- L206 _prototype_ `FString GetProjectPythonContentPath();` (scope `UE::Learning::Trainer`) — Gets the project's Python Content path.
- L211 _prototype_ `FString GetNneCpuContentPath();` (scope `UE::Learning::Trainer`) — Gets the NNE Runtime Basic CPU Python content path from the plugin.
- L216 _prototype_ `FString GetIntermediatePath(const FString& IntermediateDir);` (scope `UE::Learning::Trainer`) — Gets the LearningAgents Intermediate path from the intermediate directory.
- L221 _prototype_ `TSharedPtr<FJsonObject> ConvertObservationSchemaToJSON( const Observation::FSchema& ObservationSchema, const Observation::FSchemaElement& ObservationSchemaElement);` (scope `UE::Learning::Trainer`) — Converts an observation schema element into a JSON representation.
- L228 _prototype_ `TSharedPtr<FJsonObject> ConvertActionSchemaToJSON( const Action::FSchema& ActionSchema, const Action::FSchemaElement& ActionSchemaElement);` (scope `UE::Learning::Trainer`) — Converts an action schema element into a JSON representation.
- L233 _prototype_ `bool IsObservationSchemaSubsetCompatible( const FString& SourceJsonString, const Observation::FSchema& ObservationSchema, const Observation::FSchemaElement& ObservationSchemaElement);` (scope `UE::Learning::Trainer`) — Returns true if the schema and element are a subset of the provided JSON.
- L239 _prototype_ `bool IsObservationSchemaSubsetCompatible( const TSharedRef<FJsonObject> Object, const Observation::FSchema& ObservationSchema, const Observation::FSchemaElement& ObservationSchemaElement);` (scope `UE::Learning::Trainer`) — Returns true if the schema and element are a subset of the provided JSON.
- L245 _prototype_ `TArray<int32> ComputeObservationSchemaSubsetIndices( const FString& SourceJsonString, const Observation::FSchema& ObservationSchema, const Observation::FSchemaElement& ObservationSchemaElement);` (scope `UE::Learning::Trainer`) — Computes the indices to copy from a subset compatible JSON.
- L251 _prototype_ `void ComputeObservationSchemaSubsetIndices( int32& NextIndex, TArray<int32>& Indices, const TSharedRef<FJsonObject> Object, const Observation::FSchema& ObservationSchema, const Observation::FSchemaElement& ObservationSchemaElement);` (scope `UE::Learning::Trainer`) — Computes the indices to copy from a subset compatible JSON.
- L259 _prototype_ `bool IsActionSchemaSubsetCompatible( const FString& SourceJsonString, const Action::FSchema& ActionSchema, const Action::FSchemaElement& ActionSchemaElement);` (scope `UE::Learning::Trainer`) — Returns true if the schema and element are a subset of the provided JSON.
- L265 _prototype_ `bool IsActionSchemaSubsetCompatible( const TSharedRef<FJsonObject> Object, const Action::FSchema& ActionSchema, const Action::FSchemaElement& ActionSchemaElement);` (scope `UE::Learning::Trainer`) — Returns true if the schema and element are a subset of the provided JSON.
- L271 _prototype_ `TArray<int32> ComputeActionSchemaSubsetIndices( const FString& SourceJsonString, const Action::FSchema& ActionSchema, const Action::FSchemaElement& ActionSchemaElement);` (scope `UE::Learning::Trainer`) — Computes the indices to copy from a subset compatible JSON.
- L277 _prototype_ `void ComputeActionSchemaSubsetIndices( int32& NextIndex, TArray<int32>& Indices, const TSharedRef<FJsonObject> Object, const Action::FSchema& ActionSchema, const Action::FSchemaElement& ActionSchemaElement);` (scope `UE::Learning::Trainer`) — Computes the indices to copy from a subset compatible JSON.

### `Plugins/Experimental/LearningCore/Source/LearningTraining/Public/LearningTraining.h` (Public)


#### class `FLearningTrainingModule`  
`class FLearningTrainingModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`
