# Plugins / LearningAgentsTraining

- module root: `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining`
- headers: 17; symbols: 567
- symbol kinds: class=21, delegate=5, enum=2, enumerator=5, function=1, macro=17, member=236, namespace=24, prototype=229, struct=27
- PrivateDependencyModuleNames: CoreUObject, Engine, Json, JsonUtilities, Learning, LearningAgents, LearningTraining, Projects, UnrealEd
- PublicDependencyModuleNames: AIModule, Core, GameplayTags, NavigationSystem

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsCommunicator.h` (Public)


#### struct `FLearningAgentsSharedMemoryCommunicatorSettings`  
`struct FLearningAgentsSharedMemoryCommunicatorSettings`  
_L28-49_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: Settings specific to shared memory communicators.
- L36 _public member_ `float Timeout = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Time in seconds to wait for the training process before timing out.
- L40 _public member_ `bool bUseExternalTrainingProcess = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, then we will attach to existing training process and skip spawning one.
- L44 _public member_ `FGuid ControlsGuid;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (EditCondition = "bUseExternalTrainingProcess"))` — The existing controls memory to attach to.
- L48 _public member_ `FDirectoryPath ConfigPath;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (EditCondition = "bUseExternalTrainingProcess"))` — The absolute path to the config directory.

#### struct `FLearningAgentsSocketCommunicatorSettings`  
`struct FLearningAgentsSocketCommunicatorSettings`  
_L53-74_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: Settings specific to socket communicators.
- L61 _public member_ `FString IpAddress = TEXT("127` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — IP Address for the socket.
- L65 _public member_ `uint32 Port = 48491;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0", ClampMax = "65535", UIMax = "65535"))` — Port for the socket.
- L69 _public member_ `float Timeout = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Time in seconds to wait for the training process before timing out.
- L73 _public member_ `bool bUseExternalTrainingProcess = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, then we will attach to existing training process and skip spawning one.

#### struct `FLearningAgentsSharedMemoryTrainerProcess`  
`struct FLearningAgentsSharedMemoryTrainerProcess`  
_L78-83_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint-compatible wrapper struct for Shared Memory Training Process.
- L82 _public member_ `TSharedPtr<UE::Learning::FSharedMemoryTrainerServerProcess> TrainerProcess;`

#### struct `FLearningAgentsSocketTrainerProcess`  
`struct FLearningAgentsSocketTrainerProcess`  
_L87-92_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint-compatible wrapper struct for Socket Training Process.
- L91 _public member_ `TSharedPtr<UE::Learning::FSocketTrainerServerProcess> TrainerProcess;`

#### struct `FLearningAgentsCommunicator`  
`struct FLearningAgentsCommunicator`  
_L96-101_
- reflection: `USTRUCT(BlueprintType)`
- desc: Blueprint-compatible wrapper struct for IExternalTrainer.
- L100 _public member_ `TSharedPtr<UE::Learning::IExternalTrainer> Trainer;`

#### class `ULearningAgentsCommunicatorLibrary`  
`class ULearningAgentsCommunicatorLibrary : public UBlueprintFunctionLibrary`  
_L105-208_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Contains functions for starting external trainers and communicating with them.
- L130 _public prototype_ `static FLearningAgentsCommunicator MakeSharedMemoryTrainingProcess( const FLearningAgentsTrainerProcessSettings& TrainerProcessSettings = FLearningAgentsTrainerProcessSettings(), const FLearningAgentsSharedMemoryCommunicatorSettings& SharedMemorySettings = FLearningAgentsSharedMemoryCommunicatorSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerProcessSettings,SharedMemorySettings"))` — Start and connect to a training sub-process which will communicate via shared memory. Shared memory has the least communication overhead so prefer this for local development. This must be called on game thread! You can use this in place of calling "SpawnSharedMemoryTrainingProcess" followed by "MakeSharedMemoryCommunicator" for most use-cases. If you wish to connect to an externally launched trainer (for debugging or scale-out reasons, etc.), you can use the following command-line options to override some settings: -LearningAgentsUseExternalTrainingProcess	If present, spawning a sub-process will be skipped. -LearningAgentsControlsGuid={guid}			This optional guid will override the SharedMemorySettings, so you can attach to shared memory control created by the trainer. @param TrainerProcessSettings							Settings universal to all trainer processes. @param FLearningAgentsSharedMemoryCommunicatorSettings	Settings specific to shared memory communicators.
- L144 _public prototype_ `static FLearningAgentsSharedMemoryTrainerProcess SpawnSharedMemoryTrainingProcess( const FLearningAgentsTrainerProcessSettings& TrainerProcessSettings = FLearningAgentsTrainerProcessSettings(), const FLearningAgentsSharedMemoryCommunicatorSettings& SharedMemorySettings = FLearningAgentsSharedMemoryCommunicatorSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerProcessSettings,SharedMemorySettings"))` — Start a local python training sub-process which will communicate via shared memory. Shared memory has the least communication overhead so prefer this for local development. This must be called on game thread! @param TrainerProcessSettings							Settings universal to all trainer processes. @param FLearningAgentsSharedMemoryCommunicatorSettings	Settings specific to shared memory communicators.
- L156 _public prototype_ `static FLearningAgentsCommunicator MakeSharedMemoryCommunicator( FLearningAgentsSharedMemoryTrainerProcess TrainerProcess, const FLearningAgentsTrainerProcessSettings& TrainerProcessSettings = FLearningAgentsTrainerProcessSettings(), const FLearningAgentsSharedMemoryCommunicatorSettings& SharedMemorySettings = FLearningAgentsSharedMemoryCommunicatorSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerProcessSettings,SharedMemorySettings"))` — Create a communicator which can be used to interact with a previously started shared memory trainer process. @param TrainerProcess									The shared memory trainer process to communicate with. @param TrainerProcessSettings							Settings universal to all trainer processes. @param FLearningAgentsSharedMemoryCommunicatorSettings	Settings specific to shared memory communicators.
- L178 _public prototype_ `static FLearningAgentsCommunicator MakeSocketTrainingProcess( const FLearningAgentsTrainerProcessSettings& TrainerProcessSettings = FLearningAgentsTrainerProcessSettings(), const FLearningAgentsSocketCommunicatorSettings& SocketSettings = FLearningAgentsSocketCommunicatorSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerProcessSettings,SocketSettings"))` — Start and connect to a training sub-process which will communicate via sockets. Sockets have some overhead compared to shared memory but can work over networked connects. This provides no encryption so do not use on public internet if privacy is a concern. This must be called on game thread! If you wish to connect to an externally launched trainer (for debugging or scale-out reasons, etc.), you can use the following command-line options to override some settings: -LearningAgentsUseExternalTrainingProcess	If present, spawning a sub-process will be skipped. -LearningAgentsIpAddress=					This optional IP address will override the SocketSettings -LearningAgentsPort=						This optional Port will override the SocketSettings @param TrainerProcessSettings					Settings universal to all trainer processes. @param FLearningAgentsSocketCommunicatorSettings	Settings specific to socket communicators.
- L193 _public prototype_ `static FLearningAgentsSocketTrainerProcess SpawnSocketTrainingProcess( const FLearningAgentsTrainerProcessSettings& TrainerProcessSettings = FLearningAgentsTrainerProcessSettings(), const FLearningAgentsSocketCommunicatorSettings& SocketSettings = FLearningAgentsSocketCommunicatorSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerProcessSettings,SocketSettings"))` — Start a local python training sub-process which will communicate via sockets. Sockets have some overhead compared to shared memory but can work over networked connects. This provides no encryption so do not use on public internet if privacy is a concern. This must be called on game thread! @param TrainerProcessSettings					Settings universal to all trainer processes. @param FLearningAgentsSocketCommunicatorSettings	Settings specific to socket communicators.
- L205 _public prototype_ `static FLearningAgentsCommunicator MakeSocketCommunicator( FLearningAgentsSocketTrainerProcess TrainerProcess, const FLearningAgentsSocketCommunicatorSettings& SocketSettings = FLearningAgentsSocketCommunicatorSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "SocketSettings"))` — Create a communicator which can be used to interact with a previously started socket trainer process. @param TrainerProcess							The socket trainer process to communicate with (optional). @param TrainerProcessSettings					Settings universal to all trainer processes. @param FLearningAgentsSocketCommunicatorSettings	Settings specific to socket communicators.

#### Free symbols / members of external scopes

- L15 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsCompletions.h` (Public)


#### enum `ELearningAgentsCompletion`  
`enum class ELearningAgentsCompletion : uint8`  
_L20-30_
- reflection: `UENUM(BlueprintType, Category = "LearningAgents", meta = (ScriptName = "LearningAgentsCompletionEnum"))`
- desc: Completion modes for episodes.
- L23 _public enumerator_ `Running UMETA(DisplayName = "Running")` — Episode is still running.
- L26 _public enumerator_ `Truncation UMETA(DisplayName = "Truncation")` — Episode ended while in progress. Critic will be used to estimate final return.
- L29 _public enumerator_ `Termination UMETA(DisplayName = "Termination")` — Episode ended and zero reward was expected for all future steps.

#### class `ULearningAgentsCompletions`  
`class ULearningAgentsCompletions : public UBlueprintFunctionLibrary`  
_L42-260_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- L50 _public prototype_ `static bool IsCompletionRunning(const ELearningAgentsCompletion Completion);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if a completion is running, otherwise false.
- L54 _public prototype_ `static bool IsCompletionCompleted(const ELearningAgentsCompletion Completion);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if a completion is either truncated or terminated, otherwise false.
- L58 _public prototype_ `static bool IsCompletionTruncation(const ELearningAgentsCompletion Completion);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if a completion is truncated, otherwise false.
- L62 _public prototype_ `static bool IsCompletionTermination(const ELearningAgentsCompletion Completion);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if a completion is terminated, otherwise false.
- L67 _public prototype_ `static ELearningAgentsCompletion CompletionOr(ELearningAgentsCompletion A, ELearningAgentsCompletion B);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (CommutativeAssociativeBinaryOperator, DisplayName="Completion OR", CompactNodeTitle = "OR"))` — Returns a termination if either input is a termination, otherwise a truncation if either input is a truncation, otherwise returns running.
- L71 _public prototype_ `static ELearningAgentsCompletion CompletionAnd(ELearningAgentsCompletion A, ELearningAgentsCompletion B);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (CommutativeAssociativeBinaryOperator, DisplayName = "Completion AND", CompactNodeTitle="AND"))` — Returns a termination if both inputs are a termination, otherwise a truncation if both inputs are either a truncation or termination, otherwise returns running.
- L75 _public prototype_ `static ELearningAgentsCompletion CompletionNot(ELearningAgentsCompletion A, ELearningAgentsCompletion NotRunningType = ELearningAgentsCompletion::Termination);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (DisplayName = "Completion NOT", CompactNodeTitle = "NOT"))` — Returns running if the input A is either a termination or truncation, otherwise returns the completion specified by NotRunningType
- L90 _public prototype_ `static ELearningAgentsCompletion MakeCompletion( const ELearningAgentsCompletion CompletionType = ELearningAgentsCompletion::Termination, const FName Tag = TEXT("Completion"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Yellow);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 1, DefaultToSelf = "VisualLoggerListener"))` — Make a completion. @param CompletionType The type of completion to make. @param Tag The tag for the completion. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this completion. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this completion. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting completion.
- L113 _public prototype_ `static ELearningAgentsCompletion MakeCompletionOnCondition( const bool bCondition, const ELearningAgentsCompletion CompletionType = ELearningAgentsCompletion::Termination, const FName Tag = TEXT("ConditionCompletion"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Yellow);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 2, DefaultToSelf = "VisualLoggerListener"))` — Make a completion based on some condition. @param bCondition When true, returns the given CompletionType, otherwise returns Running. @param CompletionType The type of completion to make. @param Tag The tag for the completion. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this completion. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this completion. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting completion.
- L138 _public prototype_ `static ELearningAgentsCompletion MakeCompletionOnTimeElapsed( const float Time, const float TimeThreshold = 10.0f, const ELearningAgentsCompletion CompletionType = ELearningAgentsCompletion::Truncation, const FName Tag = TEXT("TimeElapsedCompletion"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Yellow);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 3, DefaultToSelf = "VisualLoggerListener"))` — Make a completion when a time goes above a threshold. @param Time The current time. @param TimeThreshold The time threshold above which to complete with the given CompletionType. @param CompletionType The type of completion to make @param Tag The tag for the completion. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this completion. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this completion. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting completion.
- L164 _public prototype_ `static ELearningAgentsCompletion MakeCompletionOnEpisodeStepsRecorded( const int32 EpisodeSteps, const int32 MaxEpisodeSteps = 64, const ELearningAgentsCompletion CompletionType = ELearningAgentsCompletion::Truncation, const FName Tag = TEXT("EpisodeStepsRecordedCompletion"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Yellow);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 3, DefaultToSelf = "VisualLoggerListener"))` — Make a completion when the number of episode steps recorded exceeds some threshold. @param EpisodeSteps The number of steps recorded. @param MaxEpisodeSteps The step threshold above which to complete with the given CompletionType. @param CompletionType The type of completion to make @param Tag The tag for the completion. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this completion. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this completion. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting completion.
- L191 _public prototype_ `static ELearningAgentsCompletion MakeCompletionOnLocationDifferenceBelowThreshold( const FVector LocationA, const FVector LocationB, const float DistanceThreshold = 100.0f, const ELearningAgentsCompletion CompletionType = ELearningAgentsCompletion::Termination, const FName Tag = TEXT("LocationDifferenceBelowThresholdCompletion"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Yellow);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 4, DefaultToSelf = "VisualLoggerListener"))` — Make a completion when the distance between two locations is below some threshold. @param LocationA The first location. @param LocationB The second location. @param DistanceThreshold The distance threshold. @param CompletionType The type of completion to make @param Tag The tag for the completion. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this completion. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this completion. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting completion.
- L219 _public prototype_ `static ELearningAgentsCompletion MakeCompletionOnLocationDifferenceAboveThreshold( const FVector LocationA, const FVector LocationB, const float DistanceThreshold = 100.0f, const ELearningAgentsCompletion CompletionType = ELearningAgentsCompletion::Termination, const FName Tag = TEXT("LocationDifferenceAboveThresholdCompletion"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Yellow);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 4, DefaultToSelf = "VisualLoggerListener"))` — Make a completion when the distance between two locations is above some threshold. @param LocationA The first location. @param LocationB The second location. @param DistanceThreshold The distance threshold. @param CompletionType The type of completion to make @param Tag The tag for the completion. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this completion. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this completion. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting completion.
- L248 _public prototype_ `static ELearningAgentsCompletion MakeCompletionOnLocationOutsideBounds( const FVector Location, const FTransform BoundsTransform = FTransform(), const FVector BoundsMins = FVector(-100.0f, -100.0f, -100.0f), const FVector BoundsMaxs = FVector(+100.0f, +100.0f, +100.0f), const ELearningAgentsCompletion CompletionType = ELearningAgentsCompletion::Termination, const FName Tag = TEXT("LocationOutsideBoundsCompletion"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Yellow);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 5, DefaultToSelf = "VisualLoggerListener"))` — Make a completion when a location moves outside of sound bounds. @param Location The location. @param BoundsTransform The transform of the bounds object. @param BoundsMins The minimums of the bounds object. @param BoundsMaxs The maximums of the bounds object. @param CompletionType The type of completion to make @param Tag The tag for the completion. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this completion. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this completion. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting completion.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L13 _namespace_ `namespace UE`
- L13 _namespace_ `namespace Learning` (scope `UE`)
- L32 _namespace_ `namespace UE`
- L32 _namespace_ `namespace Learning` (scope `UE`)
- L32 _namespace_ `namespace Agents` (scope `UE::Learning`)
- L35 _prototype_ `ELearningAgentsCompletion GetLearningAgentsCompletion(const ECompletionMode CompletionMode);` (scope `UE::Learning::Agents`) — Get the learning agents completion from the UE::Learning completion.
- L38 _prototype_ `ECompletionMode GetCompletionMode(const ELearningAgentsCompletion Completion);` (scope `UE::Learning::Agents`) — Get the UE::Learning completion from the learning agents completion.

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsEntitiesManagerComponent.h` (Public)


#### struct `FLearningAgentsEntityInfo`  
`struct FLearningAgentsEntityInfo`  
_L19-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: FLearningAgentsEntityInfo holds spawn information of a single entity type.
- L25 _public member_ `TSubclassOf<AActor> EntityClass;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")` — Specify the entity class to spawn.
- L29 _public member_ `float EntitySpawnZOffset = 0.0f;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")` — Specify the Z offset to apply to spawn locations.
- L33 _public member_ `int32 EpisodeEntitySpawnCountMin = 0;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — The min number of entities to spawn at the start of an episode.
- L37 _public member_ `int32 EpisodeEntitySpawnCountMax = 0;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — The max number of entities to spawn at the start of an episode.

#### struct `FSpawnedEntitiesInfo`  
`struct FSpawnedEntitiesInfo`  
_L44-53_
- reflection: `USTRUCT(BlueprintType)`
- desc: FSpawnedEntitiesInfo holds references to spawned entities.
- L49 _public member_ `FLearningAgentsEntityInfo EntityInfo;` — `UPROPERTY(VisibleAnywhere, Category = "LearningAgents")`
- L52 _public member_ `TArray<TScriptInterface<ILearningAgentsEntityInterface>> SpawnedEntities;` — `UPROPERTY(VisibleAnywhere, Category = "LearningAgents")`

#### class `ULearningAgentsEntitiesManagerComponent`  
`class ULearningAgentsEntitiesManagerComponent : public UActorComponent, public ILearningAgentsLearningComponentInterface`  
_L59-98_
- reflection: `UCLASS(MinimalAPI, ClassGroup=(LearningAgents), meta=(BlueprintSpawnableComponent))`
- inherits: `UActorComponent,ILearningAgentsLearningComponentInterface`
- desc: ULearningAgentsEntitiesManagerComponent handles the spawn and reset of multiple entity types during training.
- L66 _public member_ `TArray<FLearningAgentsEntityInfo> Entities;` — `UPROPERTY(EditDefaultsOnly, Category = "LearningAgents")` — Specify the entity types to spawn.
- L69 _public prototype_ `virtual void InitializeLearningComponent();` — Initializes the entities that the component manages.
- L72 _public prototype_ `virtual void ResetLearningComponent();` — Resets entities that the component manages.
- L76 _public prototype_ `TScriptInterface<ILearningAgentsEntityInterface> SpawnEntitiesAtRandomLocations(TSubclassOf<AActor> EntityClass, float EntitySpawnZOffset, int32 SpawnCount);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Spawns pooled entities at random locations.
- L80 _public prototype_ `TScriptInterface<ILearningAgentsEntityInterface> SpawnEntityAtProjectedLocation(TSubclassOf<AActor> EntityClass, float EntitySpawnZOffset, const FTransform& Transform);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Spawns a single pooled entity with a specified transform projected in the gym.
- L84 _public prototype_ `TArray<TScriptInterface<ILearningAgentsEntityInterface>> SpawnEntities(TSubclassOf<AActor> EntityClass, float EntitySpawnZOffset, int32 SpawnCount, const FTransform& Transform);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Spawns multiple pooled entities.
- L87 _protected prototype_ `virtual void BeginPlay() override;`
- L91 _private member_ `TMap<FName, FSpawnedEntitiesInfo> EntitiesPool;` — `UPROPERTY(VisibleAnywhere, Category = "LearningAgents")`
- L93 _private prototype_ `void ProjectTransform(FTransform& Transform) const;`
- L95 _private prototype_ `void RandomizeTransform(FTransform& OutTransform, float LocationZOffset) const;`
- L97 _private prototype_ `bool CheckEntityClasses() const;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsEntityInterface.h` (Public)


#### class `ULearningAgentsEntityTrainingInterface`  
`class ULearningAgentsEntityTrainingInterface : public UInterface`  
_L17-20_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `UInterface`
- desc: Classes that implement the Entity Training Interface need to provide definitions for how to initialize an object for training and resetting the object after a training episode ends.

#### class `ILearningAgentsEntityTrainingInterface`  
`class ILearningAgentsEntityTrainingInterface`  
_L23-39_
- desc: Completion modes for episodes.
- L30 _public prototype_ `void InitializeEntity(ALearningAgentsGymBase* InGym);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LearningAgents")` — Initialize an entity at the start of training.
- L34 _public prototype_ `void ResetEntity(ALearningAgentsGymBase* InGym);` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LearningAgents")` — Resets an entity for a new training episode.
- L38 _public prototype_ `ALearningAgentsGymBase* GetGym() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LearningAgents")` — Resets an entity for a new training episode.

#### class `ULearningAgentsEntityInterface`  
`class ULearningAgentsEntityInterface : public ULearningAgentsEntityTrainingInterface`  
_L47-50_
- reflection: `UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)`
- inherits: `ULearningAgentsEntityTrainingInterface`
- desc: Classes that implement the Entity Interface need to provide definitions for enabling and disabling an entity during training. If using the LearningAgentsGym, this interface should be implemented by any actor that is spawned during training.

#### class `ILearningAgentsEntityInterface`  
`class ILearningAgentsEntityInterface: public ILearningAgentsEntityTrainingInterface`  
_L52-68_
- inherits: `ILearningAgentsEntityTrainingInterface`
- L59 _public prototype_ `void EnableEntity();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LearningAgents")` — Enables an entity to be used for training.
- L63 _public prototype_ `void DisableEntity();` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LearningAgents")` — Disables an entity used for training.
- L67 _public prototype_ `bool IsEntityEnabled() const;` — `UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LearningAgents")` — Checks whether an entity is eligible to be used for training.

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsFlowMatchingTrainer.h` (Public)


#### struct `FLearningAgentsFlowMatchingTrainerSettings`  
`struct FLearningAgentsFlowMatchingTrainerSettings`  
_L29-42_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The configurable settings for a ULearningAgentsFlowMatchingTrainer.
- L37 _public member_ `float TrainerCommunicationTimeout = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Time in seconds to wait for the training process before timing out.
- L41 _public member_ `FGameplayTag RecordingFilterTag;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")` — Tag used to filter records from the recording.

#### struct `FLearningAgentsFlowMatchingHyperparameters`  
`struct FLearningAgentsFlowMatchingHyperparameters`  
_L46-89_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The hyperparameters for the flow matching training process.
- L54 _public member_ `int32 NumberOfIterations = 1000000;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — The number of iterations to run before ending training.
- L58 _public member_ `float LearningRate = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Learning rate of the Denoiser network. Typical values are between 0.001 and 0.0001.
- L65 _public member_ `float WeightDecay = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Amount of weight decay to apply to the network. Larger values encourage network weights to be smaller but too large a value can cause the network weights to collapse to all zeros.
- L72 _public member_ `uint32 BatchSize = 256;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "4096"))` — Batch size to use for training. Smaller values tend to produce better results at the cost of slowing down training. Large batch sizes are much more computationally efficient when training on the GPU.
- L78 _public member_ `float ObservationNoiseScale = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — A multiplicative scaling factor that controls the observation noise that increases the perturbations added to observations.
- L84 _public member_ `bool bNormalizeLatents = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — Whether to perform latent normalization. If true, then we sample from a gaussian fitted to the latent distribution instead of N(0, 1).
- L88 _public member_ `int32 RandomSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0"))` — The seed used for any random sampling the trainer will perform, e.g. for weight initialization.

#### struct `FLearningAgentsFlowMatchingLoggingSettings`  
`struct FLearningAgentsFlowMatchingLoggingSettings`  
_L92-120_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- L103 _public member_ `bool bUseTensorboard = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, TensorBoard logs will be emitted to the intermediate directory. TensorBoard will only work if it is installed in Unreal Engine's python environment. This can be done by enabling the "Tensorboard" plugin in your project.
- L107 _public member_ `bool bSaveSnapshots = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, snapshots of the trained networks will be emitted to the intermediate directory.
- L111 _public member_ `int32 IterationsPerSnapshot = 1000;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — If bSaveSnapshots is true, the snapshots will be saved at an interval defined by the specified number of iterations.
- L115 _public member_ `bool bUseMLflow = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, MLflow will be used for experiment tracking.
- L119 _public member_ `FString MLflowTrackingUri = "";` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The URI of the MLflow Tracking Server to log to.

#### struct `FLearningAgentsFlowMatchingValidationSettings`  
`struct FLearningAgentsFlowMatchingValidationSettings`  
_L124-139_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: Validation settings for the flow matching training process.
- L132 _public member_ `bool bCheckObservationSchemaCompatibility = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")` — Whether to perform a blocking check to ensure that the interactor's observation schema is a valid subset of the recording asset's observation schema JSON description. For example, this option can be left off to allow different observation encoding options in the interactor than that specified at recording time. However, we recommend to keep this check unless you are confident of handling schema compatibility on your own.
- L138 _public member_ `bool bCheckActionSchemaCompatibility = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")` — Whether to perform a blocking check to ensure that the interactor's action schema is a valid subset of the recording asset's action schema JSON description. For example, this option can be left off to allow different action encoding options in the interactor than that specified at recording time. However, we recommend to keep this check unless you are confident of handling schema compatibility on your own.

#### struct `FLearningAgentsFlowMatchingTrainerTrainingSettings`  
`struct FLearningAgentsFlowMatchingTrainerTrainingSettings`  
_L143-170_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The configurable settings for the flow matching training process.
- L149 _public member_ `FLearningAgentsFlowMatchingHyperparameters Hyperparameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")`
- L152 _public member_ `FLearningAgentsFlowMatchingLoggingSettings LoggingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")`
- L155 _public member_ `FLearningAgentsFlowMatchingValidationSettings ValidationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")`
- L159 _public member_ `ELearningAgentsTrainingDevice Device = ELearningAgentsTrainingDevice::GPU;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")` — The device to train on.
- L167 _public member_ `bool bEmbedNormalizationsInWeights = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — Whether to embed dataset normalizations into encoder and decoder networks. This is recommended to set to true to stabilize trainings. <Important> The normalization option in action/observation schemas must be set to one of the "auto" options.
- L169 _public prototype_ `TSharedRef<FJsonObject> AsJsonConfig() const;`

#### class `ULearningAgentsFlowMatchingTrainer`  
`class ULearningAgentsFlowMatchingTrainer : public ULearningAgentsManagerListener`  
_L180-338_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `ULearningAgentsManagerListener`
- desc: The ULearningAgentsFlowMatchingTrainer enables imitation learning with flow matching. Inference actions are generated by integrating the learned velocity field with ODE approximates. @see ULearningAgentsFlowMatching for the Denoiser class that performs ODE integration during inference. @see ULearningAgentsRecorder to understand how to make new recordings.
- L188 _public prototype_ `ULearningAgentsFlowMatchingTrainer();` — These constructors/destructors are needed to make forward declarations happy
- L189 _public prototype_ `ULearningAgentsFlowMatchingTrainer(FVTableHelper& Helper);`
- L190 _public prototype_ `virtual ~ULearningAgentsFlowMatchingTrainer();`
- L193 _public prototype_ `virtual void BeginDestroy() override;` — Will automatically call EndTraining if training is still in-progress when the object is destroyed.
- L206 _public prototype_ `static ULearningAgentsFlowMatchingTrainer* MakeFlowMatchingTrainer( UPARAM(ref) ULearningAgentsManager*& InManager, UPARAM(ref) ULearningAgentsInteractor*& InInteractor, UPARAM(ref) ULearningAgentsFlowMatching*& InFlowMatchingModel, const FLearningAgentsCommunicator& Communicator, TSubclassOf<ULearningAgentsFlowMatchingTrainer> Class, const FName Name = TEXT("Flow` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (Class = "/Script/LearningAgentsTraining.LearningAgentsFlowMatchingTrainer", DeterminesOutputType = "Class"))` — Constructs the flow matching trainer and runs the setup functions. @param InManager			The agent manager we are using. @param InInteractor		The agent interactor we are recording with. @param InFlowMatchingModel	The flow matching model we are using. @param Communicator		The communicator. @param Class				The trainer class. @param Name				The trainer name.
- L222 _public prototype_ `void SetupFlowMatchingTrainer( ULearningAgentsManager* InManager, ULearningAgentsInteractor* InInteractor, ULearningAgentsFlowMatching* InFlowMatchingModel, const FLearningAgentsCommunicator& Communicator);` — Initializes the flow matching trainer and runs the setup functions. @param InManager			The agent manager we are using. @param InInteractor		The agent interactor we are recording with. @param InFlowMatchingModel The flow matching model we are using. @param InCommunicator	The communicator.
- L230 _public prototype_ `bool IsTraining() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if the trainer is currently training; Otherwise, false.
- L239 _public prototype_ `bool HasTrainingFailed() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if the trainer has failed to communicate with the external training process. This can be used in combination with RunTraining to avoid filling the logs with errors. @returns				True if the training has failed. Otherwise, false.
- L250 _public prototype_ `void BeginTraining( const ULearningAgentsRecording* Recording, const FLearningAgentsFlowMatchingTrainerSettings& FlowMatchingTrainerSettings = FLearningAgentsFlowMatchingTrainerSettings(), const FLearningAgentsFlowMatchingTrainerTrainingSettings& FlowMatchingTrainerTrainingSettings = FLearningAgentsFlowMatchingTrainerTrainingSettings(), const FLearningAgentsTrainerProcessSettings& FlowMatchingTrainerPathSettings = FLearningAgentsTrainerProcessSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "FlowMatchingTrainerSettings,FlowMatchingTrainerTrainingSettings,FlowMatchingTrainerPathSettings"))` — Begins the training process with the provided settings. @param Recording								The data to train on. @param FlowMatchingTrainerSettings			The settings for this trainer. @param FlowMatchingTrainerTrainingSettings	The training settings for this network. @param FlowMatchingTrainerPathSettings		The path settings used by the flow matching trainer.
- L258 _public prototype_ `void EndTraining();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Stops the training process.
- L262 _public prototype_ `void IterateTraining();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Iterates the training process and gets the updated Denoiser network.
- L274 _public prototype_ `void RunTraining( const ULearningAgentsRecording* Recording, const FLearningAgentsFlowMatchingTrainerSettings& FlowMatchingTrainerSettings = FLearningAgentsFlowMatchingTrainerSettings(), const FLearningAgentsFlowMatchingTrainerTrainingSettings& FlowMatchingTrainerTrainingSettings = FLearningAgentsFlowMatchingTrainerTrainingSettings(), const FLearningAgentsTrainerProcessSettings& FlowMatchingTrainerPathSettings = FLearningAgentsTrainerProcessSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "FlowMatchingTrainerSettings,FlowMatchingTrainerTrainingSettings,FlowMatchingTrainerPathSettings"))` — Convenience function that runs a basic training loop. If training has not been started, it will start it. On each following call to this function, it will call IterateTraining. @param Recording								The data to train on. @param FlowMatchingTrainerSettings			The settings for this trainer. @param FlowMatchingTrainerTrainingSettings	The training settings for this network. @param FlowMatchingTrainerPathSettings		The path settings used by the flow matching trainer.
- L289 _public prototype_ `void ExportToFile( UE::Learning::FFileTrainer& FileTrainer, const ULearningAgentsRecording* Recording, const FLearningAgentsFlowMatchingTrainerSettings& FlowMatchingTrainerSettings, const FLearningAgentsFlowMatchingTrainerTrainingSettings& FlowMatchingTrainerTrainingSettings, UE::Learning::ETrainerExportFlags ExportFlags);` — Exports training materials to file, only performing work needed for the requested export flags. Skips expensive replay buffer construction when not exporting replay buffers. @param Recording							The data to export. @param FlowMatchingTrainerSettings		The settings for this trainer. @param FlowMatchingTrainerTrainingSettings	The training settings for this network. @param ExportFlags						Which sections to export.
- L301 _private member_ `TObjectPtr<ULearningAgentsInteractor> Interactor;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The interactor being trained.
- L305 _private member_ `TObjectPtr<ULearningAgentsFlowMatching> Model;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The flow matching model being trained.
- L309 _private member_ `bool bIsTraining = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — True if training is currently in-progress. Otherwise, false.
- L316 _private member_ `bool bHasTrainingFailed = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — True if trainer encountered an unrecoverable error during training (e.g. the trainer process timed out). Otherwise, false. This exists mainly to keep the editor from locking up if something goes wrong during training.
- L318 _private prototype_ `TSharedRef<FJsonObject> CreateSchemaConfig(const int32 ObservationSchemaId = 0, const int32 ActionSchemaId = 0) const;`
- L319 _private prototype_ `TSharedRef<FJsonObject> CreateDataConfig() const;`
- L320 _private prototype_ `TSharedRef<FJsonObject> CreateModelConfig() const;`
- L321 _private prototype_ `TSharedRef<FJsonObject> CreateTrainerConfig(const FLearningAgentsFlowMatchingTrainerTrainingSettings& TrainingSettings) const;`
- L322 _private prototype_ `void SendConfigs(const TSharedRef<FJsonObject>& DataConfigObject, const TSharedRef<FJsonObject>& ModelConfigObject, const TSharedRef<FJsonObject>& TrainerConfigObject);`
- L324 _private prototype_ `void DoneTraining();`
- L326 _private member_ `TUniquePtr<UE::Learning::FReplayBuffer> ReplayBuffer;`
- L327 _private member_ `TSharedPtr<UE::Learning::IExternalTrainer> Trainer;`
- L329 _private member_ `int32 DenoiserNetworkId = INDEX_NONE;`
- L330 _private member_ `int32 EncoderNetworkId = INDEX_NONE;`
- L331 _private member_ `int32 DecoderNetworkId = INDEX_NONE;`
- L333 _private member_ `int32 ReplayBufferId = INDEX_NONE;`
- L335 _private member_ `int32 ObservationId = INDEX_NONE;`
- L336 _private member_ `int32 ActionId = INDEX_NONE;`
- L337 _private member_ `int32 MemoryStateId = INDEX_NONE;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsGym.h` (Public)


#### class `ALearningAgentsGymBase`  
`class ALearningAgentsGymBase : public AActor`  
_L25-90_
- reflection: `UCLASS(MinimalAPI, Abstract, BlueprintType)`
- inherits: `AActor`
- desc: The Gym Base abstract class handles the start and reset of entities training in a single gym.
- L30 _public prototype_ `ALearningAgentsGymBase();`
- L34 _public prototype_ `void Initialize();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Initializes the gym at the start of training.
- L38 _public prototype_ `void Reset();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Resets the gym for a new training episode.
- L43 _public member_ `FOnGymInitializedSignature OnGymInitialized;` — `UPROPERTY(BlueprintAssignable, Category = "LearningAgents")` — Event called at a gym's initialization.
- L47 _public member_ `FOnBeginGymResetSignature OnBeginGymReset;` — `UPROPERTY(BlueprintAssignable, Category = "LearningAgents")` — Event called at the start of a gym's reset.
- L51 _public member_ `FOnPostGymResetSignature OnPostGymReset;` — `UPROPERTY(BlueprintAssignable, Category = "LearningAgents")` — Event called at the end of a gym's reset.
- L56 _public prototype_ `void GetRandomStream(FRandomStream& OutRandomStream) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Retrieves the current random stream used by the Gym.
- L59 _public prototype_ `TSharedPtr<FRandomStream> GetRandomStream() const;` — Retrieves the current random stream used by the Gym.
- L62 _public prototype_ `void SetRandomStream(const TSharedPtr<FRandomStream>& InRandomStream);` — Sets the random stream used by the Gym.
- L65 _public prototype_ `bool IsMemberOfGym(TObjectPtr<AActor> Actor) const;` — Checks if an actor is training in this gym.
- L68 _public prototype_ `virtual FRotator GenerateRandomRotationInGym() const PURE_VIRTUAL(ALearningAgentsGymBase::GenerateRandomRotationInGym, return INVALID_GYM_ROTATOR;);` — Generates a random rotator using the gym's random stream.
- L71 _public prototype_ `virtual FVector GenerateRandomLocationInGym() const PURE_VIRTUAL(ALearningAgentsGymBase::GenerateRandomLocationInGym, return INVALID_GYM_VECTOR;);` — Generates a valid random point in the gym using the gym's random stream. Must be overridden in a derived class.
- L74 _public prototype_ `virtual FVector ProjectPointToGym(const FVector& InPoint) const PURE_VIRTUAL(ALearningAgentsGymBase::ProjectPointToGym, return INVALID_GYM_VECTOR;);` — Projects a point onto a valid location in the gym. Must be overridden in a derived class.
- L77 _public prototype_ `virtual void GetGymExtents(FVector& OutMinExtents, FVector& OutMaxExtents) const PURE_VIRTUAL(ALearningAgentsGymBase::GetGymExtents, );` — Gets the gym max and min bounds. Must be overridden in a derived class.
- L82 _protected member_ `int32 RandomSeed = 1234;` — `UPROPERTY(EditDefaultsOnly, Category = "LearningAgents")` — The random seed used for spawn locations. Note: This is only used if a random stream is not setup by the GymsManager.
- L84 _protected member_ `TSharedPtr<FRandomStream> RandomStream;`
- L87 _protected member_ `TArray<TScriptInterface<ILearningAgentsLearningComponentInterface>> LearningComponents;` — `UPROPERTY()`
- L89 _protected prototype_ `void PopulateLearningComponents();`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L12 _macro_ `#define INVALID_GYM_VECTOR (FVector::ZeroVector)`
- L13 _macro_ `#define INVALID_GYM_ROTATOR (FRotator::ZeroRotator)`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGymInitializedSignature);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGymInitializedSignature);`
- L16 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginGymResetSignature);`
- L16 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginGymResetSignature);`
- L17 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostGymResetSignature);`
- L17 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPostGymResetSignature);`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsGymSimple.h` (Public)


#### class `ALearningAgentsGymSimple`  
`class ALearningAgentsGymSimple : public ALearningAgentsGymBase`  
_L17-34_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (LearningAgents), BlueprintType, Blueprintable)`
- inherits: `ALearningAgentsGymBase`
- desc: A simple gym template class that uses a static mesh as its training floor.
- L22 _public prototype_ `ALearningAgentsGymSimple();`
- L25 _public member_ `TObjectPtr<UStaticMeshComponent> SimpleGymFloor;` — `UPROPERTY(EditDefaultsOnly, Category = "LearningAgents")`
- L27 _public prototype_ `virtual void GetGymExtents(FVector& OutMinExtents, FVector& OutMaxExtents) const override;`
- L29 _public prototype_ `virtual FRotator GenerateRandomRotationInGym() const override;`
- L31 _public prototype_ `virtual FVector GenerateRandomLocationInGym() const override;`
- L33 _public prototype_ `virtual FVector ProjectPointToGym(const FVector& InPoint) const override;`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsGymsManager.h` (Public)


#### struct `FSpawnGymInfo`  
`struct FSpawnGymInfo`  
_L18-34_
- reflection: `USTRUCT(BlueprintType)`
- desc: This struct holds information (num to spawn etc) on one gym template to spawn.
- L24 _public member_ `TSubclassOf<ALearningAgentsGymBase> GymClass;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")` — The gym class used to construct gym instances.
- L28 _public member_ `int32 SpawnCount = 0;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0"))` — The number of gym instances to spawn.
- L30 _public function_ `int32 GetCount() const`

#### class `ALearningAgentsGymsManager`  
`class ALearningAgentsGymsManager : public AActor`  
_L41-75_
- reflection: `UCLASS(MinimalAPI, ClassGroup = (LearningAgents), Blueprintable)`
- inherits: `AActor`
- desc: The Learning Agents GymsManager centralizes the start and reset of training for multiple gym templates.
- L45 _private prototype_ `ALearningAgentsGymsManager();`
- L50 _public member_ `int32 RandomSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The random seed to initialize the random stream used by the GymsManager.
- L54 _public member_ `float GymsSpacing = 300.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The distance between each parallel gym when spawned.
- L58 _public prototype_ `void Start();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Spawns and initializes gym instances.
- L62 _public prototype_ `int32 GetGymsCount() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Get the number of gyms managed by the GymsManager.
- L66 _private member_ `TArray<FSpawnGymInfo> GymTemplates;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")`
- L68 _private member_ `TArray<TObjectPtr<ALearningAgentsGymBase>> SpawnedGyms;`
- L70 _private member_ `TSharedPtr<FRandomStream> RandomStream;`
- L72 _private prototype_ `void InitializeRandomStream();`
- L74 _private prototype_ `void SpawnGyms();`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsImitationTrainer.h` (Public)


#### struct `FLearningAgentsImitationTrainerSettings`  
`struct FLearningAgentsImitationTrainerSettings`  
_L29-42_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The configurable settings for a ULearningAgentsImitationTrainer.
- L37 _public member_ `float TrainerCommunicationTimeout = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Time in seconds to wait for the training process before timing out.
- L41 _public member_ `FGameplayTag RecordingFilterTag;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")` — Tag used to filter records from the recording.

#### struct `FLearningAgentsImitationTrainerHyperparameters`  
`struct FLearningAgentsImitationTrainerHyperparameters`  
_L46-111_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The hyperparameters for the imitation learning training process.
- L53 _public member_ `int32 NumberOfIterations = 1000000;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — The number of iterations to run before ending training.
- L57 _public member_ `float LearningRate = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Learning rate of the policy network. Typical values are between 0.001 and 0.0001.
- L61 _public member_ `float LearningRateDecay = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Amount by which to multiply the learning rate every time it decays.
- L65 _public member_ `int32 LearningRateDecayStepSize = 1000;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — The number of iterations to train before updating the learning rate.
- L72 _public member_ `float WeightDecay = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Amount of weight decay to apply to the network. Larger values encourage network weights to be smaller but too large a value can cause the network weights to collapse to all zeros.
- L79 _public member_ `uint32 BatchSize = 128;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "4096"))` — Batch size to use for training. Smaller values tend to produce better results at the cost of slowing down training. Large batch sizes are much more computationally efficient when training on the GPU.
- L87 _public member_ `uint32 Window = 64;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "512"))` — The number of consecutive steps of observations and actions over which to train the policy. Increasing this value will encourage the policy to use its memory effectively. Too large and training can become unstable. Given we don't know the memory state during imitation learning it is better this is slightly larger than when we are doing reinforcement learning.
- L93 _public member_ `float ActionRegularizationWeight = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Weight used to regularize actions. Larger values will encourage smaller actions but too large will cause actions to become always zero.
- L100 _public member_ `float ActionEntropyWeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — Weighting used for the entropy bonus. Larger values encourage larger action noise and therefore greater exploration but can make actions very noisy.
- L106 _public member_ `float ObservationNoiseScale = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0"))` — A multiplicative scaling factor that controls the observation noise that increases the perturbations added to observations.
- L110 _public member_ `int32 RandomSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0"))` — The seed used for any random sampling the trainer will perform, e.g. for weight initialization.

#### struct `FLearningAgentsImitationLearningLoggingSettings`  
`struct FLearningAgentsImitationLearningLoggingSettings`  
_L114-142_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- L125 _public member_ `bool bUseTensorboard = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, TensorBoard logs will be emitted to the intermediate directory. TensorBoard will only work if it is installed in Unreal Engine's python environment. This can be done by enabling the "Tensorboard" plugin in your project.
- L129 _public member_ `bool bSaveSnapshots = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, snapshots of the trained networks will be emitted to the intermediate directory.
- L133 _public member_ `int32 IterationsPerSnapshot = 1000;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — If bSaveSnapshots is true, the snapshots will be saved at an interval defined by the specified number of iterations.
- L137 _public member_ `bool bUseMLflow = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, MLflow will be used for experiment tracking.
- L141 _public member_ `FString MLflowTrackingUri = "";` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The URI of the MLflow Tracking Server to log to.

#### struct `FLearningAgentsImitationLearningValidationSettings`  
`struct FLearningAgentsImitationLearningValidationSettings`  
_L146-165_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: Validation settings for the imitation learning training process.
- L156 _public member_ `bool bCheckObservationSchemaCompatibility = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")` — Whether to perform a blocking check to ensure that the interactor's observation schema is a valid subset of the recording asset's observation schema JSON description. For example, this option can be left off to allow different observation encoding options in the interactor than that specified at recording time. However, we recommend to keep this check unless you are confident of handling schema compatibility on your own.
- L164 _public member_ `bool bCheckActionSchemaCompatibility = true;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")` — Whether to perform a blocking check to ensure that the interactor's action schema is a valid subset of the recording asset's action schema JSON description. For example, this option can be left off to allow different action encoding options in the interactor than that specified at recording time. However, we recommend to keep this check unless you are confident of handling schema compatibility on your own.

#### struct `FLearningAgentsImitationTrainerTrainingSettings`  
`struct FLearningAgentsImitationTrainerTrainingSettings`  
_L169-213_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The configurable settings for the imitation learning training process.
- L175 _public member_ `FLearningAgentsImitationTrainerHyperparameters Hyperparameters;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")`
- L178 _public member_ `FLearningAgentsImitationLearningLoggingSettings LoggingSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")`
- L181 _public member_ `FLearningAgentsImitationLearningValidationSettings ValidationSettings;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")`
- L185 _public member_ `ELearningAgentsTrainingDevice Device = ELearningAgentsTrainingDevice::GPU;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents")` — The device to train on.
- L193 _public member_ `bool bEmbedNormalizationsInWeights = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — Whether to embed dataset normalizations into encoder and decoder networks. This is recommended to set to true to stabilize trainings. <Important> The normalization option in action/observation schemas must be set to one of the "auto" options.
- L197 _public member_ `bool bRunEvaluation = false;` — `UPROPERTY(VisibleDefaultsOnly, Category = "LearningAgents")` — Should evaluation run during the training process. Currently not used in Python
- L201 _public member_ `float TrainEvalDatasetSplit = 0.1f;` — `UPROPERTY(VisibleDefaultsOnly, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0", EditCondition = "bRunEvaluation"))` — How much data should be used for evaluation. Currently not used in Python
- L205 _public member_ `int32 EvaluationFrequency = 50;` — `UPROPERTY(VisibleDefaultsOnly, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bRunEvaluation"))` — How many training iteration loops between an evaluation run. Currently not used in Python
- L209 _public member_ `int32 BatchCountPerEvaluation = 10;` — `UPROPERTY(VisibleDefaultsOnly, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0", EditCondition = "bRunEvaluation"))` — How many batches to perform evaluation on? Randomly chosen each evaluation. Currently not used in Python
- L212 _public prototype_ `TSharedRef<FJsonObject> AsJsonConfig() const;`

#### class `ULearningAgentsImitationTrainer`  
`class ULearningAgentsImitationTrainer : public ULearningAgentsManagerListener`  
_L225-382_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `ULearningAgentsManagerListener`
- desc: The ULearningAgentsImitationTrainer enable imitation learning, i.e. learning from human/AI demonstrations. Imitation training is typically much faster than reinforcement learning, but requires gathering large amounts of data in order to generalize. This can be used to initialize a reinforcement learning policy to speed up initial exploration. @see ULearningAgentsInteractor to understand how observations and actions work. @see ULearningAgentsController to understand how we can manually perform actions via a human or AI. @see ULearningAgentsRecorder to understand how to make new recordings.
- L233 _public prototype_ `ULearningAgentsImitationTrainer();` — These constructors/destructors are needed to make forward declarations happy
- L234 _public prototype_ `ULearningAgentsImitationTrainer(FVTableHelper& Helper);`
- L235 _public prototype_ `virtual ~ULearningAgentsImitationTrainer();`
- L238 _public prototype_ `virtual void BeginDestroy() override;` — Will automatically call EndTraining if training is still in-progress when the object is destroyed.
- L251 _public prototype_ `static ULearningAgentsImitationTrainer* MakeImitationTrainer( UPARAM(ref) ULearningAgentsManager*& InManager, UPARAM(ref) ULearningAgentsInteractor*& InInteractor, UPARAM(ref) ULearningAgentsPolicy*& InPolicy, const FLearningAgentsCommunicator& Communicator, TSubclassOf<ULearningAgentsImitationTrainer> Class, const FName Name = TEXT("Imit` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (Class = "/Script/LearningAgentsTraining.LearningAgentsImitationTrainer", DeterminesOutputType = "Class"))` — Constructs the imitation trainer and runs the setup functions. @param InManager			The agent manager we are using. @param InInteractor		The agent interactor we are recording with. @param InPolicy			The policy we are using. @param Communicator		The communicator. @param Class				The trainer class. @param Name				The trainer name.
- L267 _public prototype_ `void SetupImitationTrainer( ULearningAgentsManager* InManager, ULearningAgentsInteractor* InInteractor, ULearningAgentsPolicy* InPolicy, const FLearningAgentsCommunicator& Communicator);` — Initializes the imitation trainer and runs the setup functions. @param InManager			The agent manager we are using. @param InInteractor		The agent interactor we are recording with. @param InPolicy			The policy we are using. @param InCommunicator	The communicator.
- L275 _public prototype_ `bool IsTraining() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if the trainer is currently training; Otherwise, false.
- L284 _public prototype_ `bool HasTrainingFailed() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if the trainer has failed to communicate with the external training process. This can be used in combination with RunTraining to avoid filling the logs with errors. @returns				True if the training has failed. Otherwise, false.
- L295 _public prototype_ `void BeginTraining( const ULearningAgentsRecording* Recording, const FLearningAgentsImitationTrainerSettings& ImitationTrainerSettings = FLearningAgentsImitationTrainerSettings(), const FLearningAgentsImitationTrainerTrainingSettings& ImitationTrainerTrainingSettings = FLearningAgentsImitationTrainerTrainingSettings(), const FLearningAgentsTrainerProcessSettings& ImitationTrainerPathSettings = FLearningAgentsTrainerProcessSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "ImitationTrainerSettings,ImitationTrainerTrainingSettings,ImitationTrainerPathSettings"))` — Begins the training process with the provided settings. @param Recording							The data to train on. @param ImitationTrainerSettings			The settings for this trainer. @param ImitationTrainerTrainingSettings	The training settings for this network. @param ImitationTrainerPathSettings		The path settings used by the imitation trainer.
- L303 _public prototype_ `void EndTraining();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Stops the training process.
- L307 _public prototype_ `void IterateTraining();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Iterates the training process and gets the updated policy network.
- L319 _public prototype_ `void RunTraining( const ULearningAgentsRecording* Recording, const FLearningAgentsImitationTrainerSettings& ImitationTrainerSettings = FLearningAgentsImitationTrainerSettings(), const FLearningAgentsImitationTrainerTrainingSettings& ImitationTrainerTrainingSettings = FLearningAgentsImitationTrainerTrainingSettings(), const FLearningAgentsTrainerProcessSettings& ImitationTrainerPathSettings = FLearningAgentsTrainerProcessSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "ImitationTrainerSettings,ImitationTrainerTrainingSettings,ImitationTrainerPathSettings"))` — Convenience function that runs a basic training loop. If training has not been started, it will start it. On each following call to this function, it will call IterateTraining. @param Recording							The data to train on. @param ImitationTrainerSettings			The settings for this trainer. @param ImitationTrainerTrainingSettings	The training settings for this network. @param ImitationTrainerPathSettings		The path settings used by the imitation trainer.
- L334 _public prototype_ `void ExportToFile( UE::Learning::FFileTrainer& FileTrainer, const ULearningAgentsRecording* Recording, const FLearningAgentsImitationTrainerSettings& ImitationTrainerSettings, const FLearningAgentsImitationTrainerTrainingSettings& ImitationTrainerTrainingSettings, UE::Learning::ETrainerExportFlags ExportFlags);` — Exports training materials to file, only performing work needed for the requested export flags. Skips expensive replay buffer construction when not exporting replay buffers. @param Recording							The data to export. @param ImitationTrainerSettings			The settings for this trainer. @param ImitationTrainerTrainingSettings	The training settings for this network. @param ExportFlags						Which sections to export.
- L346 _private member_ `TObjectPtr<ULearningAgentsInteractor> Interactor;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The interactor being trained.
- L350 _private member_ `TObjectPtr<ULearningAgentsPolicy> Policy;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The policy being trained.
- L354 _private member_ `bool bIsTraining = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — True if training is currently in-progress. Otherwise, false.
- L361 _private member_ `bool bHasTrainingFailed = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — True if trainer encountered an unrecoverable error during training (e.g. the trainer process timed out). Otherwise, false. This exists mainly to keep the editor from locking up if something goes wrong during training.
- L363 _private prototype_ `TSharedRef<FJsonObject> CreateDataConfig() const;`
- L364 _private prototype_ `TSharedRef<FJsonObject> CreateModelConfig() const;`
- L365 _private prototype_ `TSharedRef<FJsonObject> CreateTrainerConfig(const FLearningAgentsImitationTrainerTrainingSettings& TrainingSettings) const;`
- L366 _private prototype_ `void SendConfigs(const TSharedRef<FJsonObject>& DataConfigObject, const TSharedRef<FJsonObject>& ModelConfigObject, const TSharedRef<FJsonObject>& TrainerConfigObject);`
- L368 _private prototype_ `void DoneTraining();`
- L370 _private member_ `TUniquePtr<UE::Learning::FReplayBuffer> ReplayBuffer;`
- L371 _private member_ `TSharedPtr<UE::Learning::IExternalTrainer> Trainer;`
- L373 _private member_ `int32 PolicyNetworkId = INDEX_NONE;`
- L374 _private member_ `int32 EncoderNetworkId = INDEX_NONE;`
- L375 _private member_ `int32 DecoderNetworkId = INDEX_NONE;`
- L377 _private member_ `int32 ReplayBufferId = INDEX_NONE;`
- L379 _private member_ `int32 ObservationId = INDEX_NONE;`
- L380 _private member_ `int32 ActionId = INDEX_NONE;`
- L381 _private member_ `int32 MemoryStateId = INDEX_NONE;`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsLearningComponentInterface.h` (Public)


#### class `ULearningAgentsLearningComponentInterface`  
`class ULearningAgentsLearningComponentInterface : public UInterface`  
_L12-15_
- reflection: `UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint), BlueprintType)`
- inherits: `UInterface`

#### class `ILearningAgentsLearningComponentInterface`  
`class ILearningAgentsLearningComponentInterface`  
_L17-29_
- L24 _public prototype_ `virtual void InitializeLearningComponent() = 0;` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Initializes the component at the start of training.
- L28 _public prototype_ `virtual void ResetLearningComponent() = 0;` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Resets the component for a new training episode.

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsPPOTrainer.h` (Public)


#### struct `FLearningAgentsPPOTrainerSettings`  
`struct FLearningAgentsPPOTrainerSettings`  
_L33-61_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The configurable settings for a ULearningAgentsPPOTrainer.
- L44 _public member_ `int32 MaxEpisodeStepNum = 512;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — Maximum number of steps recorded in an episode before it is added to the replay buffer. This can generally be left at the default value and does not have a large impact on training.
- L52 _public member_ `int32 MaximumRecordedEpisodesPerIteration = 1000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — Maximum number of episodes to record before running a training iteration. An iteration of training will be run when either this or MaximumRecordedEpisodesPerIteration is reached. Typical values for this should be around 1000. Setting this too small means there is not enough data each iteration for the system to train. Setting it too large means training will be very slow.
- L60 _public member_ `int32 MaximumRecordedStepsPerIteration = 10000;` — `UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — Maximum number of steps to record before running a training iteration. An iteration of training will be run when either this or MaximumRecordedEpisodesPerIteration is reached. Typical values for this should be around 10000. Setting this too small means there is not enough data each iteration for the system to train. Setting it too large means training will be very slow.

#### struct `FLearningAgentsPPOTrainingSettings`  
`struct FLearningAgentsPPOTrainingSettings`  
_L65-260_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The configurable settings for the PPO training process.
- L73 _public member_ `int32 NumberOfIterations = 1000000;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1"))` — The number of iterations to run before ending training.
- L77 _public member_ `float LearningRatePolicy = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Learning rate of the policy network. Typical values are between 0.001 and 0.0001.
- L84 _public member_ `float LearningRateCritic = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Learning rate of the critic network. To avoid instability generally the critic should have a larger learning rate than the policy. Typically this can be set to 10x the rate of the policy.
- L88 _public member_ `float LearningRateDecay = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Amount by which to multiply the learning rate every 1000 iterations.
- L95 _public member_ `float WeightDecay = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Amount of weight decay to apply to the network. Larger values encourage network weights to be smaller but too large a value can cause the network weights to collapse to all zeros.
- L101 _public member_ `int32 PolicyBatchSize = 1024;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "4096"))` — Batch size to use for training the policy. Large batch sizes are much more computationally efficient when training on the GPU.
- L107 _public member_ `int32 CriticBatchSize = 4096;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "4096"))` — Batch size to use for training the critic. Large batch sizes are much more computationally efficient when training on the GPU.
- L114 _public member_ `int32 PolicyWindowSize = 16;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "128"))` — The number of consecutive steps of observations and actions over which to train the policy. Increasing this value will encourage the policy to use its memory effectively. Too large and training can become slow and unstable.
- L121 _public member_ `int32 IterationsPerGather = 32;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "1024"))` — Number of training iterations to perform per buffer of experience gathered. This should be large enough for the critic and policy to be effectively updated, but too large and it will simply slow down training.
- L128 _public member_ `int32 CriticWarmupIterations = 8;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "1", UIMin = "1", UIMax = "128"))` — Number of iterations of training to perform to warm - up the Critic. This helps speed up and stabilize training at the beginning when the Critic may be producing predictions at the wrong order of magnitude.
- L136 _public member_ `float EpsilonClip = 0.2f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — Clipping ratio to apply to policy updates. Keeps the training "on-policy". Larger values may speed up training at the cost of stability. Conversely, too small values will keep the policy from being able to learn an optimal policy.
- L142 _public member_ `float ReturnRegularizationWeight = 0.0001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Weight used to regularize returns. Encourages the critic not to over or under estimate returns.
- L148 _public member_ `float ActionSurrogateWeight = 1.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Weight for the loss used to train the policy via the PPO surrogate objective.
- L155 _public member_ `float ActionRegularizationWeight = 0.001f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Weight used to regularize actions. Larger values will encourage exploration and smaller actions, but too large will cause noisy actions centered around zero.
- L162 _public member_ `float ActionEntropyWeight = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", UIMin = "0.0", UIMax = "1.0"))` — Weighting used for the entropy bonus. Larger values encourage larger action noise and therefore greater exploration but can make actions very noisy.
- L169 _public member_ `float GaeLambda = 0.95f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — This is used in the Generalized Advantage Estimation, where larger values will tend to assign more credit to recent actions. Typical values should be between 0.9 and 1.0.
- L173 _public member_ `bool bAdvantageNormalization = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — When true, advantages are normalized. This tends to makes training more robust to adjustments of the scale of rewards.
- L180 _public member_ `float MinimumAdvantage = 0.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (UIMin = "-10.0", UIMax = "0.0"))` — The minimum advantage to allow. Setting this below zero will encourage the policy to move away from bad actions, but can introduce instability.
- L187 _public member_ `float MaximumAdvantage = 10.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (UIMin = "0.0", UIMax = "10.0"))` — The maximum advantage to allow. Making this smaller may increase training stability at the cost of some training speed.
- L194 _public member_ `bool bUseGradNormMaxClipping = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — When true, gradient norm max clipping will be used on the policy, critic, encoder, and decoder. Set this as True if training is unstable (and adjust GradNormMax) or leave as False if unused.
- L203 _public member_ `float GradNormMax = 0.5f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (UIMin = "0.0", UIMax = "10.0"))` — The maximum gradient norm to clip updates to. Only used when bUseGradNormMaxClipping is set to true. This needs to be carefully chosen based on the size of your gradients during training. Setting too low can make it difficult to learn an optimal policy, and too high will have no impact.
- L210 _public member_ `int32 NumberOfStepsToTrimAtStartOfEpisode = 0;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0"))` — The number of steps to trim from the start of the episode, e.g. can be useful if some things are still getting setup at the start of the episode and you don't want them used for training.
- L217 _public member_ `int32 NumberOfStepsToTrimAtEndOfEpisode = 0;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0"))` — The number of steps to trim from the end of the episode. Can be useful if the end of the episode contains irrelevant data.
- L221 _public member_ `int32 RandomSeed = 1234;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0"))` — The seed used for any random sampling the trainer will perform, e.g. for weight initialization.
- L228 _public member_ `float DiscountFactor = 0.99f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))` — The discount factor to use during training. This affects how much the agent cares about future rewards vs near-term rewards. Should typically be a value less than but near 1.0.
- L232 _public member_ `ELearningAgentsTrainingDevice Device = ELearningAgentsTrainingDevice::GPU;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The device to train on.
- L241 _public member_ `bool bUseTensorboard = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, TensorBoard logs will be emitted to the intermediate directory. TensorBoard will only work if it is installed in Unreal Engine's python environment. This can be done by enabling the "Tensorboard" plugin in your project.
- L245 _public member_ `bool bSaveSnapshots = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, snapshots of the trained networks will be emitted to the intermediate directory.
- L249 _public member_ `int32 IterationsPerSnapshot = 1000;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (ClampMin = "0", UIMin = "0"))` — The iterations interval to save new networks snapshot.
- L253 _public member_ `bool bUseMLflow = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, MLflow will be used for experiment tracking.
- L257 _public member_ `FString MLflowTrackingUri = "";` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The URI of the MLflow Tracking Server to log to.
- L259 _public prototype_ `TSharedRef<FJsonObject> AsJsonConfig() const;`

#### class `ULearningAgentsPPOTrainer`  
`class ULearningAgentsPPOTrainer : public ULearningAgentsManagerListener`  
_L263-466_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `ULearningAgentsManagerListener`
- L271 _public prototype_ `ULearningAgentsPPOTrainer();` — These constructors/destructors are needed to make forward declarations happy
- L272 _public prototype_ `ULearningAgentsPPOTrainer(FVTableHelper& Helper);`
- L273 _public prototype_ `virtual ~ULearningAgentsPPOTrainer();`
- L276 _public prototype_ `virtual void BeginDestroy() override;` — Will automatically call EndTraining if training is still in-progress when the object is destroyed.
- L292 _public prototype_ `static ULearningAgentsPPOTrainer* MakePPOTrainer( UPARAM(ref) ULearningAgentsManager*& InManager, UPARAM(ref) ULearningAgentsInteractor*& InInteractor, UPARAM(ref) ULearningAgentsTrainingEnvironment*& InTrainingEnvironment, UPARAM(ref) ULearningAgentsPolicy*& InPolicy, UPARAM(ref) ULearningAgentsCritic*& InCritic, const FLearningAgentsCommunicator& Communicator, TSubclassOf<ULearningAgentsPPOTrainer> Class, const FName Name = TEXT("PPOTrainer"), const FLearningAgentsPPOTrainerSettings& TrainerSettings = FLearningAgentsPPOTrainerSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (Class = "/Script/LearningAgents.LearningAgentsPPOTrainer", DeterminesOutputType = "Class", AutoCreateRefTerm = "TrainerSettings"))` — Constructs the trainer. @param InManager				The agent manager we are using. @param InInteractor			The agent interactor we are training with. @param InTrainingEnvironment	The training environment. @param InPolicy				The policy to be trained. @param InCritic				The critic to be trained. @param Communicator			The communicator. @param Class					The trainer class. @param Name					The trainer name. @param TrainerSettings		The trainer settings to use.
- L315 _public prototype_ `void SetupPPOTrainer( UPARAM(ref) ULearningAgentsManager*& InManager, UPARAM(ref) ULearningAgentsInteractor*& InInteractor, UPARAM(ref) ULearningAgentsTrainingEnvironment*& InTrainingEnvironment, UPARAM(ref) ULearningAgentsPolicy*& InPolicy, UPARAM(ref) ULearningAgentsCritic*& InCritic, const FLearningAgentsCommunicator& Communicator, const FLearningAgentsPPOTrainerSettings& TrainerSettings = FLearningAgentsPPOTrainerSettings());` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerSettings"))` — Initializes the trainer. @param InManager				The agent manager we are using. @param InInteractor			The agent interactor we are training with. @param InTrainingEnvironment	The training environment. @param InPolicy				The policy to be trained. @param InCritic				The critic to be trained. @param InCommunicator		The communicator. @param TrainerSettings		The trainer settings to use.
- L327 _public prototype_ `virtual void OnAgentsAdded_Implementation(const TArray<int32>& AgentIds) override;`
- L328 _public prototype_ `virtual void OnAgentsRemoved_Implementation(const TArray<int32>& AgentIds) override;`
- L329 _public prototype_ `virtual void OnAgentsReset_Implementation(const TArray<int32>& AgentIds) override;`
- L337 _public prototype_ `const bool IsTraining() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if the trainer is currently training; Otherwise, false.
- L347 _public prototype_ `void BeginTraining( const FLearningAgentsPPOTrainingSettings& TrainerTrainingSettings = FLearningAgentsPPOTrainingSettings(), const FLearningAgentsTrainingGameSettings& TrainingGameSettings = FLearningAgentsTrainingGameSettings(), const bool bResetAgentsOnBegin = true);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerTrainingSettings,TrainingGameSettings"))` — Begins the training process with the provided settings. @param TrainerTrainingSettings	The settings for this training run. @param TrainingGameSettings		The settings that will affect the game's simulation. @param bResetAgentsOnBegin		If true, reset all agents at the beginning of training.
- L354 _public prototype_ `void EndTraining();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Stops the training process.
- L365 _public prototype_ `void ProcessExperience(const bool bResetAgentsOnUpdate = true);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Call this function at the end of each step of your training loop. This takes the current observations/actions/ rewards and moves them into the episode experience buffer. All agents with full episode buffers or those which have been signaled complete will be reset. If enough experience is gathered, it will be sent to the training process and an iteration of training will be run and the updated policy will be synced back. @param bResetAgentsOnUpdate				If true, reset all agents whenever an updated policy is received.
- L378 _public prototype_ `void RunTraining( const FLearningAgentsPPOTrainingSettings& TrainerTrainingSettings = FLearningAgentsPPOTrainingSettings(), const FLearningAgentsTrainingGameSettings& TrainingGameSettings = FLearningAgentsTrainingGameSettings(), const bool bResetAgentsOnBegin = true, const bool bResetAgentsOnUpdate = true);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerTrainingSettings,TrainingGameSettings"))` — Convenience function that runs a basic training loop. If training has not been started, it will start it, and then call RunInference. On each following call to this function, it will call GatherRewards, GatherCompletions, and ProcessExperience, followed by RunInference. @param TrainerTrainingSettings			The settings for this training run. @param TrainingGameSettings				The settings that will affect the game's simulation. @param bResetAgentsOnBegin				If true, reset all agents at the beginning of training. @param bResetAgentsOnUpdate				If true, reset all agents whenever an updated policy is received.
- L391 _public prototype_ `int32 GetEpisodeStepNum(const int32 AgentId) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AgentId = "-1"))` — Gets the number of step recorded in an episode for the given agent. @param AgentId	The AgentId to look-up the number of recorded episode steps for @returns			The number of recorded episode steps
- L400 _public prototype_ `bool HasTrainingFailed() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if the trainer has failed to communicate with the external training process. This can be used in combination with RunTraining to avoid filling the logs with errors. @returns				True if the training has failed. Otherwise, false.
- L407 _private member_ `TObjectPtr<ULearningAgentsInteractor> Interactor;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The agent interactor associated with this component.
- L411 _private member_ `TObjectPtr<ULearningAgentsTrainingEnvironment> TrainingEnvironment;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The training environment associated with this component.
- L415 _private member_ `TObjectPtr<ULearningAgentsPolicy> Policy;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The current policy for experience gathering.
- L419 _private member_ `TObjectPtr<ULearningAgentsCritic> Critic;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The current critic.
- L423 _private member_ `bool bIsTraining = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — True if training is currently in-progress. Otherwise, false.
- L430 _private member_ `bool bHasTrainingFailed = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — True if trainer encountered an unrecoverable error during training (e.g. the trainer process timed out). Otherwise, false. This exists mainly to keep the editor from locking up if something goes wrong during training.
- L432 _private member_ `TUniquePtr<UE::Learning::FEpisodeBuffer> EpisodeBuffer;`
- L433 _private member_ `TUniquePtr<UE::Learning::FReplayBuffer> ReplayBuffer;`
- L434 _private member_ `TSharedPtr<UE::Learning::IExternalTrainer> Trainer;`
- L440 _private prototype_ `TSharedRef<FJsonObject> CreateDataConfig() const;` — The data config contains the info needed to create the neural network models and the supporting data buffers. These need to stay synchronized between UE and the trainer process, otherwise we will run into memory errors.
- L446 _private prototype_ `TSharedRef<FJsonObject> CreateTrainerConfig(const FLearningAgentsPPOTrainingSettings& TrainingSettings) const;` — The trainer config contains the info needed run our specific training algorithm. In theory, most of these values can be easily overridden on the trainer process side without causing any errors.
- L448 _private prototype_ `void SendConfigs(const TSharedRef<FJsonObject>& DataConfigObject, const TSharedRef<FJsonObject>& TrainerConfigObject);`
- L450 _private prototype_ `void DoneTraining();`
- L452 _private member_ `UE::Learning::Agents::FGameSettingsState PreviousGameSettingsState;`
- L454 _private member_ `int32 PolicyNetworkId = INDEX_NONE;`
- L455 _private member_ `int32 CriticNetworkId = INDEX_NONE;`
- L456 _private member_ `int32 EncoderNetworkId = INDEX_NONE;`
- L457 _private member_ `int32 DecoderNetworkId = INDEX_NONE;`
- L459 _private member_ `int32 ReplayBufferId = INDEX_NONE;`
- L461 _private member_ `int32 ObservationId = INDEX_NONE;`
- L462 _private member_ `int32 ActionId = INDEX_NONE;`
- L463 _private member_ `int32 ActionModifierId = INDEX_NONE;`
- L464 _private member_ `int32 MemoryStateId = INDEX_NONE;`
- L465 _private member_ `int32 RewardId = INDEX_NONE;`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L17 _namespace_ `namespace UE`
- L17 _namespace_ `namespace Learning` (scope `UE`)

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsRecorder.h` (Public)


#### struct `FLearningAgentsRecorderPathSettings`  
`struct FLearningAgentsRecorderPathSettings`  
_L27-42_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The path settings for the recorder.
- L33 _public prototype_ `FLearningAgentsRecorderPathSettings();`
- L37 _public member_ `FDirectoryPath IntermediateRelativePath;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LearningAgents", meta = (RelativePath))` — The relative path to the Intermediate directory. Defaults to FPaths::ProjectIntermediateDir.
- L41 _public member_ `FString RecordingsSubdirectory = TEXT("Rec` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LearningAgents", meta = (RelativePath))` — The name of the sub-directory to use in the intermediate directory

#### class `ULearningAgentsRecorder`  
`class ULearningAgentsRecorder : public ULearningAgentsManagerListener`  
_L46-220_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))`
- inherits: `ULearningAgentsManagerListener`
- desc: A component that can be used to create recordings of training data for imitation learning.
- L54 _public prototype_ `ULearningAgentsRecorder();` — These constructors/destructors are needed to make forward declarations happy
- L55 _public prototype_ `ULearningAgentsRecorder(FVTableHelper& Helper);`
- L56 _public prototype_ `virtual ~ULearningAgentsRecorder();`
- L59 _public prototype_ `virtual void BeginDestroy() override;` — Will automatically call EndRecording if recording is still in-progress when the object is destroyed.
- L74 _public prototype_ `static ULearningAgentsRecorder* MakeRecorder( UPARAM(ref) ULearningAgentsManager*& InManager, UPARAM(ref) ULearningAgentsInteractor*& InInteractor, TSubclassOf<ULearningAgentsRecorder> Class, const FName Name = TEXT("Recorder"), const FLearningAgentsRecorderPathSettings& RecorderPathSettings = FLearningAgentsRecorderPathSettings(), ULearningAgentsRecording* RecordingAsset = nullptr, bool bReinitializeRecording = true);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (Class = "/Script/LearningAgentsTraining.LearningAgentsRecorder", DeterminesOutputType = "Class", AutoCreateRefTerm = "RecorderPathSettings"))` — Constructs this object and runs the setup functions for the underlying data storage. @param InManager					The agent manager we are using. @param InInteractor				The agent interactor we are recording with. @param Class						The recorder class @param Name						The recorder class @param RecorderPathSettings		The path settings used by the recorder. @param RecordingAsset			Optional recording asset to use. If not provided or bReinitializeRecording is set then a new recording object will be created. @pram bReinitializeRecording		If to reinitialize the recording asset
- L94 _public prototype_ `void SetupRecorder( UPARAM(ref) ULearningAgentsManager*& InManager, UPARAM(ref) ULearningAgentsInteractor*& InInteractor, const FLearningAgentsRecorderPathSettings& RecorderPathSettings = FLearningAgentsRecorderPathSettings(), ULearningAgentsRecording* RecordingAsset = nullptr, bool bReinitializeRecording = true);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "RecorderPathSettings"))` — Initializes this object and runs the setup functions for the underlying data storage. @param InManager					The agent manager we are using. @param InInteractor				The agent interactor we are recording with. @param RecorderPathSettings		The path settings used by the recorder. @param RecordingAsset			Optional recording asset to use. If not provided or bReinitializeRecording is set then a new recording object will be created. @pram bReinitializeRecording		If to reinitialize the recording asset
- L104 _public prototype_ `virtual void OnAgentsRemoved_Implementation(const TArray<int32>& AgentIds) override;`
- L105 _public prototype_ `virtual void OnAgentsReset_Implementation(const TArray<int32>& AgentIds) override;`
- L113 _public prototype_ `void BeginRecording();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Begins the recording of the observations and actions of each added agent.
- L117 _public prototype_ `void EndRecording();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Ends the recording of the observations and actions of each agent and stores them in the current recording object.
- L121 _public prototype_ `void EndRecordingAndDiscard();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Ends the recording of the observations and actions of each agent and discards them.
- L125 _public prototype_ `bool IsRecording() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Returns true if recording is active; Otherwise, false.
- L129 _public member_ `FOnRecordingBeginSignature OnRecordingBegin;` — `UPROPERTY(BlueprintAssignable, Category = "LearningAgents")` — Called after the recording has started
- L133 _public member_ `FOnRecordingEndSignature OnRecordingEnd;` — `UPROPERTY(BlueprintAssignable, Category = "LearningAgents")` — Called after the recording has stopped
- L141 _public prototype_ `void AddExperience();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — While recording, adds the current buffered observations and actions of the added agents to the internal buffer. Call this after GatherObservations and either EvaluateAgentController (if recording a human/AI demonstration) or DecodeAndSampleActions (if recording from another policy).
- L145 _public prototype_ `const ULearningAgentsRecording* GetRecordingAsset() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Gets the current recording object. Note: this may be empty until EndRecording has been called.
- L149 _protected prototype_ `ULearningAgentsInteractor* GetInteractor() const;` — `UFUNCTION(BlueprintPure, Category="LearningAgents")`
- L156 _protected prototype_ `FLearningAgentsSchema SaveSchemaConfig(const FString& FileName = TEXT("sche` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Saves the schema config JSON to the recording directory with the given filename. Defaults to "schema-config.json".
- L163 _private member_ `TObjectPtr<ULearningAgentsInteractor> Interactor;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The agent interactor this recorder is associated with.
- L167 _private member_ `TObjectPtr<ULearningAgentsRecording> Recording;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — The current recording object.
- L171 _private member_ `bool bIsRecording = false;` — `UPROPERTY(VisibleAnywhere, Transient, Category = "LearningAgents")` — True if recording is currently in-progress. Otherwise, false.
- L177 _private member_ `FString RecordingDirectory;` — Directory to store recordings in
- L219 _private member_ `TArray<FAgentRecordBuffer, TInlineAllocator<32>> RecordBuffers;` — Array of recording buffers for each agent

#### struct `ULearningAgentsRecorder::FAgentRecordBuffer`  
`struct FAgentRecordBuffer`  
_L180-216_
- desc: Basic structure used to buffer the observations and actions of each agent.
- L182 _public prototype_ `FAgentRecordBuffer();`
- L183 _public prototype_ `FAgentRecordBuffer( const int32 InObservationCompatibilityHash, const int32 InActionCompatibilityHash, const UE::Learning::Observation::FSchema InObservationSchema, const UE::Learning::Observation::FSchemaElement InObservationSchemaElement, const UE::Learning::Action::FSchema InActionSchema, const UE::Learning::Action::FSchemaElement InActionSchemaElement);`
- L191 _public member_ `const int32 ChunkSize = 1024;`
- L192 _public member_ `int32 StepNum = 0;`
- L193 _public member_ `int32 ObservationCompatibilityHash = 0;`
- L194 _public member_ `int32 ActionCompatibilityHash = 0;`
- L195 _public member_ `UE::Learning::Observation::FSchema ObservationSchema;`
- L196 _public member_ `UE::Learning::Observation::FSchemaElement ObservationSchemaElement;`
- L197 _public member_ `UE::Learning::Action::FSchema ActionSchema;`
- L198 _public member_ `UE::Learning::Action::FSchemaElement ActionSchemaElement;`
- L199 _public member_ `TArray<TLearningArray<2, float>, TInlineAllocator<16>> Observations;`
- L200 _public member_ `TArray<TLearningArray<2, float>, TInlineAllocator<16>> Actions;`
- L202 _public prototype_ `TLearningArrayView<1, float> GetObservation(const int32 SampleIdx);`
- L203 _public prototype_ `TLearningArrayView<1, float> GetAction(const int32 SampleIdx);`
- L204 _public prototype_ `TLearningArrayView<1, const float> GetObservation(const int32 SampleIdx) const;`
- L205 _public prototype_ `TLearningArrayView<1, const float> GetAction(const int32 SampleIdx) const;`
- L207 _public prototype_ `bool IsEmpty() const;`
- L209 _public prototype_ `void Empty();`
- L211 _public prototype_ `void Push( const TLearningArrayView<1, const float> Observation, const TLearningArrayView<1, const float> Action);`
- L215 _public prototype_ `void CopyToRecord(FLearningAgentsRecord& Record) const;`

#### Free symbols / members of external scopes

- L17 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L19 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecordingBeginSignature);`
- L19 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecordingBeginSignature);`
- L20 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecordingEndSignature);`
- L20 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRecordingEndSignature);`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsRecording.h` (Public)


#### struct `FLearningAgentsSchema`  
`struct FLearningAgentsSchema`  
_L31-44_
- reflection: `USTRUCT(BlueprintType)`
- desc: A schema entry.
- L39 _public member_ `FString ObservationSchemaJson;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LearningAgents")` — Observation schema in JSON format.
- L43 _public member_ `FString ActionSchemaJson;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LearningAgents")` — Action schema in JSON format.

#### class `ULearningAgentsRecordBlob`  
`class ULearningAgentsRecordBlob : public UObject`  
_L48-59_
- reflection: `UCLASS()`
- inherits: `UObject`
- desc: Container for the record's binary data. Kept separate to keep Slate from loading it.
- L55 _public member_ `TArray<float> ObservationData;` — `UPROPERTY()`
- L58 _public member_ `TArray<float> ActionData;` — `UPROPERTY()`

#### struct `FLearningAgentsRecord`  
`struct FLearningAgentsRecord`  
_L63-104_
- reflection: `USTRUCT(BlueprintType)`
- desc: A single recording of a series of observations and actions.
- L71 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LearningAgents")` — Record's name.
- L75 _public member_ `FName SchemaName;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LearningAgents")` — Schema's name. Must correspond with a schema in the recording.
- L79 _public member_ `int32 StepNum = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LearningAgents")` — The number of observations and actions recorded.
- L83 _public member_ `int32 ObservationDimNum = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LearningAgents")` — The number of dimensions in the observation vector for this record
- L87 _public member_ `int32 ActionDimNum = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LearningAgents")` — The number of dimensions in the action vector for this record
- L91 _public member_ `int32 ObservationCompatibilityHash = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LearningAgents")` — The compatibility hash for the recorded observation vectors
- L95 _public member_ `int32 ActionCompatibilityHash = 0;` — `UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "LearningAgents")` — The compatibility hash for the recorded action vectors
- L99 _public member_ `FGameplayTagContainer Tags;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LearningAgents")` — The tags to be referenced in the imitation trainer.
- L103 _public member_ `TObjectPtr<ULearningAgentsRecordBlob> Blob;` — `UPROPERTY()` — The binary data.

#### class `ULearningAgentsRecording`  
`class ULearningAgentsRecording : public UDataAsset`  
_L108-246_
- reflection: `UCLASS(MinimalAPI, BlueprintType, Blueprintable)`
- inherits: `UDataAsset`
- desc: Data asset representing an array of records.
- L114 _public prototype_ `ULearningAgentsRecording();` — These constructors/destructors are needed to make forward declarations happy
- L115 _public prototype_ `ULearningAgentsRecording(FVTableHelper& Helper);`
- L116 _public prototype_ `virtual ~ULearningAgentsRecording();`
- L122 _public prototype_ `virtual void ResetRecording();` — `UFUNCTION(CallInEditor, Category = "LearningAgents")` — Resets this recording asset to be empty.
- L126 _public prototype_ `void AppendRecording();` — `UFUNCTION(CallInEditor, Category = "LearningAgents")` — Appends the recording from "RecordingFile" to this recording.
- L130 _public prototype_ `void AppendAllRecordingsFromFolder();` — `UFUNCTION(CallInEditor, Category = "LearningAgents", meta = (DisplayName = "Append All Recordings from Folder"))` — Appends all .record files from the specified folder to this recording asset
- L134 _public prototype_ `void AppendSchema();` — `UFUNCTION(CallInEditor, Category = "LearningAgents")` — Appends the schema from "SchemaFile" to this recording.
- L138 _public prototype_ `void AppendSchemaFromFile(const FName& SchemaName, const FFilePath& Schema);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (RelativePath))` — Append schema to this recording from a file.
- L142 _public prototype_ `virtual void LoadRecordingFromFile(const FFilePath& File, const FName& SchemaName, const FGameplayTag& Tag, TArray<FLearningAgentsRecord>& OutRecords);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (RelativePath))` — Load this recording from a file.
- L146 _public prototype_ `void SaveRecordingToFile(const FFilePath& File) const;` — `UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "LearningAgents", meta = (RelativePath))` — Save this recording to a file.
- L150 _public prototype_ `void AppendRecordingFromFile(const FFilePath& File, const FName& SchemaName, const FGameplayTag& Tag);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (RelativePath))` — Append to this recording from a file.
- L154 _public prototype_ `void LoadRecordingFromAsset(ULearningAgentsRecording* RecordingAsset);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Loads this recording from the given recording asset
- L158 _public prototype_ `void SaveRecordingToAsset(ULearningAgentsRecording* RecordingAsset);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Saves this recording to the given recording asset
- L162 _public prototype_ `void AppendRecordingToAsset(ULearningAgentsRecording* RecordingAsset);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Appends this recording to the given recording asset
- L166 _public prototype_ `int32 GetRecordNum() const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Get the number of records
- L170 _public prototype_ `int32 GetRecordStepNum(const int32 Record) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents")` — Get the number of steps in a given record
- L181 _public prototype_ `void GetObservationVector(TArray<float>& OutObservationVector, int32& OutObservationCompatibilityHash, const int32 Record, const int32 Step);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Get the Observation Vector associated with a particular step of a given recording @param OutObservationVector				Output Observation Vector @param OutObservationCompatibilityHash	Output Compatibility Hash for the given Observation Vector @param Record							Index of the record in the array of records. @param Step								Step of the recording
- L192 _public prototype_ `void GetActionVector(TArray<float>& OutActionVector, int32& OutActionCompatibilityHash, const int32 Record, const int32 Step);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Get the Action Vector associated with a particular step of a given recording @param OutActionVector					Output Action Vector @param OutActionCompatibilityHash		Output Compatibility Hash for the given Action Vector @param Record							Index of the record in the array of records. @param Step								Step of the recording
- L206 _public prototype_ `TUniquePtr<UE::Learning::FReplayBuffer> BuildReplayBuffer( const ULearningAgentsInteractor* Interactor, const FGameplayTag& RecordingFilterTag, bool bCheckObservationSchemaCompatibility, bool bCheckActionSchemaCompatibility) const;` — Builds a replay buffer from this recording, filtering by tag and validating schema compatibility. Returns nullptr if no valid data is found. @param Interactor							The interactor whose observation/action schemas define the target layout. @param RecordingFilterTag					Tag used to filter records. If invalid, no filtering is applied. @param bCheckObservationSchemaCompatibility	Whether to validate observation schema subset compatibility. @param bCheckActionSchemaCompatibility		Whether to validate action schema subset compatibility. @return A replay buffer containing the copied data, or nullptr if no valid records were found.
- L213 _public prototype_ `void ForceMarkDirty();` — Marks this asset as modified even during PIE
- L215 _public prototype_ `void AddSchema(const FName& SchemaName, FLearningAgentsSchema NewSchema);`
- L221 _public member_ `FFilePath RecordingFile;` — `UPROPERTY(EditInstanceOnly, Category = "LearningAgents")` — A recording file. Used in combination with the "AppendRecording" button in the editor.
- L225 _public member_ `FDirectoryPath RecordingFolder;` — `UPROPERTY(EditInstanceOnly, Category = "LearningAgents")` — A folder containing .record files to load. Used in combination with the "Append All Recordings From Folder" button in the editor.
- L229 _public member_ `FGameplayTag NewTag;` — `UPROPERTY(EditInstanceOnly, Category = "LearningAgents")` — The tag to apply to new records. Used in combination with the "AppendRecording" and "Append All Recordings from Folder" buttons in the editor.
- L233 _public member_ `FName NewSchemaName;` — `UPROPERTY(EditInstanceOnly, Category = "LearningAgents")` — The schema name. Used in combination with the "AppendSchema" and "AppendRecording" buttons in the editor.
- L237 _public member_ `FFilePath SchemaFile;` — `UPROPERTY(EditInstanceOnly, Category = "LearningAgents")` — A schema file. Used in combination with the "AppendSchema" button in the editor.
- L241 _public member_ `TMap<FName, FLearningAgentsSchema> Schemas;` — `UPROPERTY(EditInstanceOnly, Category = "LearningAgents")` — Map of schemas.
- L245 _public member_ `TArray<FLearningAgentsRecord> Records;` — `UPROPERTY(EditInstanceOnly, Category = "LearningAgents")` — Set of records.

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L16 _namespace_ `namespace UE`
- L16 _namespace_ `namespace Learning` (scope `UE`)
- L23 _namespace_ `namespace UE`
- L23 _namespace_ `namespace Learning` (scope `UE`)
- L23 _namespace_ `namespace Agents` (scope `UE::Learning`)
- L23 _namespace_ `namespace Recording` (scope `UE::Learning::Agents`)
- L25 _prototype_ `int32 GetMagicNumber();` (scope `UE::Learning::Agents::Recording`)
- L26 _prototype_ `int32 GetVersionNumber();` (scope `UE::Learning::Agents::Recording`)

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsRewards.h` (Public)


#### class `ULearningAgentsRewards`  
`class ULearningAgentsRewards : public UBlueprintFunctionLibrary`  
_L15-334_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UBlueprintFunctionLibrary`
- L35 _public prototype_ `static float MakeReward( const float RewardValue, const float RewardScale = 1.0f, const FName Tag = TEXT("Reward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 2, DefaultToSelf = "VisualLoggerListener"))` — Make a reward from a float value. @param RewardValue The float value used to create the reward. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L59 _public prototype_ `static float MakeRewardOnCondition( const bool bCondition, const float RewardScale = 1.0f, const FName Tag = TEXT("ConditionReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 2, DefaultToSelf = "VisualLoggerListener"))` — Make a reward which is equal to RewardScale when bCondition is true, otherwise returns zero. @param bCondition The condition under which to create a reward. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L85 _public prototype_ `static float MakeRewardFromLocationDifference( const FVector LocationA, const FVector LocationB, const float LocationScale = 100.0f, const float RewardScale = 1.0f, const FName Tag = TEXT("LocationDifferenceReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 4, DefaultToSelf = "VisualLoggerListener"))` — Make a reward based on the distance between two locations. Gives a larger reward the further the distance between the locations. @param LocationA The first location. @param LocationB The second location. @param LocationScale The expected scale for the distance between locations. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L113 _public prototype_ `static float MakeRewardOnLocationDifferenceBelowThreshold( const FVector LocationA, const FVector LocationB, const float DistanceThreshold = 100.0f, const float RewardScale = 1.0f, const FName Tag = TEXT("LocationDifferenceBelowThresholdReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 4, DefaultToSelf = "VisualLoggerListener"))` — Make a reward when the distance between two locations is below a threshold, otherwise returns zero. @param LocationA The first location. @param LocationB The second location. @param DistanceThreshold The distance threshold. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L141 _public prototype_ `static float MakeRewardOnLocationDifferenceAboveThreshold( const FVector LocationA, const FVector LocationB, const float DistanceThreshold = 100.0f, const float RewardScale = 1.0f, const FName Tag = TEXT("LocationDifferenceAboveThresholdReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 4, DefaultToSelf = "VisualLoggerListener"))` — Make a reward when the distance between two locations is above a threshold, otherwise returns zero. @param LocationA The first location. @param LocationB The second location. @param DistanceThreshold The distance threshold. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L169 _public prototype_ `static float MakeRewardFromLocationSimilarity( const FVector LocationA, const FVector LocationB, const float LocationScale = 100.0f, const float RewardScale = 1.0f, const FName Tag = TEXT("LocationSimilarityReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 4, DefaultToSelf = "VisualLoggerListener"))` — Make a reward based on how similar two locations are. @param LocationA The first location. @param LocationB The second location. @param LocationScale The expected scale for the distance between locations. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L198 _public prototype_ `static float MakeRewardFromRotationSimilarity( const FRotator RotationA, const FRotator RotationB, const float RewardScale = 1.0f, const FName Tag = TEXT("RotationSimilarityReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerRotationLocationA = FVector::ZeroVector, const FVector VisualLoggerRotationLocationB = FVector::ZeroVector, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 3, DefaultToSelf = "VisualLoggerListener"))` — Make a reward based on how similar two rotations are. @param RotationA The first rotation. @param RotationB The second rotation. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerRotationLocationA A location for the visual logger to display the first rotation in the world. @param VisualLoggerRotationLocationB A location for the visual logger to display the second rotation in the world. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L228 _public prototype_ `static float MakeRewardFromRotationSimilarityAsQuats( const FQuat RotationA, const FQuat RotationB, const float RewardScale = 1.0f, const FName Tag = TEXT("RotationSimilarityReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerRotationLocationA = FVector::ZeroVector, const FVector VisualLoggerRotationLocationB = FVector::ZeroVector, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 3, DefaultToSelf = "VisualLoggerListener"))` — Make a reward based on how similar two rotations are represented as quaternions. @param RotationA The first rotation. @param RotationB The second rotation. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerRotationLocationA A location for the visual logger to display the first rotation in the world. @param VisualLoggerRotationLocationB A location for the visual logger to display the second rotation in the world. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L258 _public prototype_ `static float MakeRewardFromAngleSimilarity( const float AngleA, const float AngleB, const float RewardScale = 1.0f, const FName Tag = TEXT("AngleSimilarityReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerAngleLocationA = FVector::ZeroVector, const FVector VisualLoggerAngleLocationB = FVector::ZeroVector, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 3, DefaultToSelf = "VisualLoggerListener"))` — Make a reward based on how similar two angles are. Angles should be given in degrees. @param AngleA The first angle. @param AngleB The second angle. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerAngleLocationA A location for the visual logger to display the first angle in the world. @param VisualLoggerAngleLocationB A location for the visual logger to display the second angle in the world. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L289 _public prototype_ `static float MakeRewardFromDirectionSimilarity( const FVector DirectionA, const FVector DirectionB, const float RewardScale = 1.0f, const FName Tag = TEXT("DirectionSimilarityReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerDirectionLocationA = FVector::ZeroVector, const FVector VisualLoggerDirectionLocationB = FVector::ZeroVector, const FVector VisualLoggerLocation = FVector::ZeroVector, const float VisualLoggerArrowLength = 100.0f, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 3, DefaultToSelf = "VisualLoggerListener", DirectionA="1.0,0.0,0.0", DirectionB = "1.0,0.0,0.0"))` — Make a reward based on how similar two directions are. @param DirectionA The first direction. @param DirectionB The second direction. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerDirectionLocationA A location for the visual logger to display the first direction in the world. @param VisualLoggerDirectionLocationB A location for the visual logger to display the second direction in the world. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerArrowLength The length of the arrow to display for the directions. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.
- L321 _public prototype_ `static float MakeRewardFromVelocityAlongSpline( const USplineComponent* SplineComponent, const FVector Location, const FVector Velocity, const float VelocityScale = 200.0f, const float RewardScale = 1.0f, const float FiniteDifferenceDelta = 10.0f, const FName Tag = TEXT("VelocityAlongSplineReward"), const bool bVisualLoggerEnabled = false, ULearningAgentsManagerListener* VisualLoggerListener = nullptr, const int32 VisualLoggerAgentId = -1, const FVector VisualLoggerLocation = FVector::ZeroVector, const FLinearColor VisualLoggerColor = FLinearColor::Green);` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AdvancedDisplay = 6, DefaultToSelf = "VisualLoggerListener"))` — Make a reward based on the velocity an object is moving along a spline. @param SplineComponent The spline. @param Location The location of the object. @param Velocity The velocity of the object. @param VelocityScale The expected scale for the velocity. @param RewardScale The scale of the reward. Use a negative scale to create a penalty. @param FiniteDifferenceDelta The finite difference to use when computing the velocity along the spline. @param Tag The tag for the reward. Used for debugging. @param bVisualLoggerEnabled When true, debug data will be sent to the visual logger. @param VisualLoggerListener The listener object which is making this reward. This must be set to use logging. @param VisualLoggerAgentId The agent id associated with this reward. @param VisualLoggerLocation A location for the visual logger information in the world. @param VisualLoggerColor The color for the visual logger display. @return The resulting reward value.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsTrainer.h` (Public)


#### enum `ELearningAgentsTrainingDevice`  
`enum class ELearningAgentsTrainingDevice : uint8`  
_L13-17_
- reflection: `UENUM(BlueprintType, Category = "LearningAgents")`
- desc: Enumeration of the training devices.
- L15 _public enumerator_ `CPU`
- L16 _public enumerator_ `GPU`

#### struct `FLearningAgentsTrainingGameSettings`  
`struct FLearningAgentsTrainingGameSettings`  
_L24-73_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The configurable game settings for a ULearningAgentsTrainer. These allow the timestep and physics tick to be fixed during training, which can enable ticking faster than real-time.
- L36 _public member_ `bool bUseFixedTimeStep = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, the game will run in fixed time step mode (i.e the frame's delta times will always be the same regardless of how much wall time has passed). This can enable faster than real-time training if your game runs quickly. If false, the time steps will match real wall time.
- L44 _public member_ `float FixedTimeStepFrequency = 60.0f;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (DisplayName = "Fixed Time Step Frequency (Hz)"), meta = (ClampMin = "0.0", UIMin = "0.0"))` — Determines the amount of time for each frame when bUseFixedTimeStep is true; Ignored if false. You want this time step to match as closely as possible to the expected inference time steps, otherwise your training results may not generalize to your game.
- L48 _public member_ `bool bSetMaxPhysicsStepToFixedTimeStep = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, set the physics delta time to match the fixed time step.
- L52 _public member_ `bool bDisableMaxFPS = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, the MaxFPS console variable will be set to a negative number during training; Otherwise, it will not.
- L56 _public member_ `bool bDisableVSync = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, VSync will be disabled; Otherwise, it will not. Disabling VSync can speed up the game simulation.
- L60 _public member_ `bool bUseUnlitViewportRendering = false;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, the viewport rendering will be unlit; Otherwise, it will not. Disabling lighting can speed up the game simulation.
- L66 _public member_ `bool bDisableUseLessCPUInTheBackground = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, the Use Less CPU In The Background editor setting will be disabled. This prevents the editor from running slowly when minimized.
- L70 _public member_ `bool bDisableEditorVSync = true;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — If true, Editor VSync will be disabled; Otherwise, it will not. Disabling Editor VSync can speed up the game simulation.

#### struct `UE::Learning::Agents::FGameSettingsState`  
`struct FGameSettingsState`  
_L78-89_
- desc: ----- Private Recording of GameSettings -----
- L80 _public member_ `bool bFixedTimestepUsed = false;`
- L81 _public member_ `float FixedTimeStepDeltaTime = -1.0f;`
- L82 _public member_ `float MaxPhysicsStep = -1.0f;`
- L83 _public member_ `int32 MaxFPS = 120;`
- L84 _public member_ `bool bVSyncEnabled = true;`
- L85 _public member_ `int32 ViewModeIndex = -1;`
- L87 _public member_ `bool bUseLessCPUInTheBackground = true;`
- L88 _public member_ `bool bEditorVSyncEnabled = true;`

#### struct `FLearningAgentsTrainerProcessSettings`  
`struct FLearningAgentsTrainerProcessSettings`  
_L104-174_
- reflection: `USTRUCT(BlueprintType, Category = "LearningAgents")`
- desc: The path settings for the trainer.
- L110 _public prototype_ `FLearningAgentsTrainerProcessSettings();`
- L114 _public member_ `FString TaskName = TEXT("Tra` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — Training task name. Used to avoid filename collisions with other training processes running on the same machine.
- L118 _public member_ `FDirectoryPath EditorEngineRelativePath;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (RelativePath))` — The relative path to the engine for editor builds. Defaults to FPaths::EngineDir.
- L139 _public member_ `FString NonEditorEngineRelativePath;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The relative path to the editor engine folder for non-editor builds. If we want to run training in cooked, non-editor builds, then by default we wont have access to python and the LearningAgents training scripts - these are editor-only things and are stripped during the cooking process. However, running training in non-editor builds can be very important - we probably want to disable rendering and sound while we are training to make experience gathering as fast as possible - and for any non-trivial game is simply may not be realistic to run it for a long time in play-in-editor. For this reason even in non-editor builds we let you provide the path where all of these editor-only things can be found. This allows you to run training when these things actually exist somewhere accessible to the executable, which will usually be the case on a normal development machine or cloud machine if it is set up that way. Since non-editor builds can be produced in a number of different ways, this is not set by default and cannot use a directory picker since it is relative to the final location of where your cooked, non-editor executable will exist rather than the current with-editor executable.
- L143 _public member_ `FDirectoryPath EditorIntermediateRelativePath;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents", meta = (RelativePath))` — The relative path to the Intermediate directory. Defaults to FPaths::ProjectIntermediateDir.
- L147 _public member_ `FString NonEditorIntermediateRelativePath;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The relative path to the intermediate folder for non-editor builds.
- L151 _public member_ `FDirectoryPath CustomTrainerModulePath;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The complete path to a custom trainer module when training with a custom trainer.
- L155 _public member_ `FString NonEditorCustomTrainerModulePath;` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — The complete path to a custom trainer module when training with a custom trainer for non-editor builds.
- L159 _public member_ `FString TrainerFileName = TEXT("lea` — `UPROPERTY(EditAnywhere, Category = "LearningAgents")` — Trainer file name. The name of the python file to use for training. Do NOT include the '.py' file extension.
- L164 _public prototype_ `FString GetEditorEnginePath() const;` — Gets the Relative Editor Engine Path accounting for if this is an editor build or not
- L167 _public prototype_ `FString GetIntermediatePath() const;` — Gets the Relative Intermediate Path
- L170 _public prototype_ `FString GetCustomTrainerModulePath() const;` — Gets the Custom Trainer Module Path
- L173 _public prototype_ `FString GetNneCpuContentPath() const;` — Gets the NNE Runtime Basic CPU Python content path. Auto-discovers from the plugin if not overridden.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L75 _namespace_ `namespace UE`
- L75 _namespace_ `namespace Learning` (scope `UE`)
- L75 _namespace_ `namespace Agents` (scope `UE::Learning`)
- L92 _prototype_ `ELearningAgentsTrainingDevice GetLearningAgentsTrainingDevice(const ETrainerDevice Device);` (scope `UE::Learning::Agents`) — Get the learning agents trainer device from the UE::Learning trainer device.
- L95 _prototype_ `ETrainerDevice GetTrainingDevice(const ELearningAgentsTrainingDevice Device);` (scope `UE::Learning::Agents`) — Get the UE::Learning trainer device from the learning agents trainer device.
- L97 _prototype_ `void ApplyGameSettings(const FLearningAgentsTrainingGameSettings& Settings, const UWorld* World, FGameSettingsState& OutGameSettingsState);` (scope `UE::Learning::Agents`)
- L99 _prototype_ `void RevertGameSettings(const FGameSettingsState& Settings, const UWorld* World);` (scope `UE::Learning::Agents`)

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsTraining.h` (Public)


#### class `FLearningAgentsTrainingModule`  
`class FLearningAgentsTrainingModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTraining/Public/LearningAgentsTrainingEnvironment.h` (Public)


#### class `ULearningAgentsTrainingEnvironment`  
`class ULearningAgentsTrainingEnvironment : public ULearningAgentsManagerListener`  
_L18-237_
- reflection: `UCLASS(MinimalAPI, Abstract, HideDropdown, BlueprintType, Blueprintable)`
- inherits: `ULearningAgentsManagerListener`
- L26 _public prototype_ `ULearningAgentsTrainingEnvironment();` — These constructors/destructors are needed to make forward declarations happy
- L27 _public prototype_ `ULearningAgentsTrainingEnvironment(FVTableHelper& Helper);`
- L28 _public prototype_ `virtual ~ULearningAgentsTrainingEnvironment();`
- L34 _public prototype_ `static ULearningAgentsTrainingEnvironment* MakeTrainingEnvironment( UPARAM(ref) ULearningAgentsManager*& InManager, TSubclassOf<ULearningAgentsTrainingEnvironment> Class, const FName Name = TEXT("Trai` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (DeterminesOutputType = "Class", AutoCreateRefTerm = "TrainerSettings"))` — Constructs the training environment and runs the setup functions for rewards and completions.
- L43 _public prototype_ `void SetupTrainingEnvironment(UPARAM(ref) ULearningAgentsManager*& InManager);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents", meta = (AutoCreateRefTerm = "TrainerSettings"))` — Initializes the training environment and runs the setup functions for rewards and completions.
- L48 _public prototype_ `virtual void OnAgentsAdded_Implementation(const TArray<int32>& AgentIds) override;`
- L49 _public prototype_ `virtual void OnAgentsRemoved_Implementation(const TArray<int32>& AgentIds) override;`
- L50 _public prototype_ `virtual void OnAgentsReset_Implementation(const TArray<int32>& AgentIds) override;`
- L51 _public prototype_ `virtual void OnAgentsManagerTick_Implementation(const TArray<int32>& AgentIds, const float DeltaTime) override;`
- L64 _public prototype_ `void GatherAgentReward(float& OutReward, const int32 AgentId);` — `UFUNCTION(BlueprintNativeEvent, Category = "LearningAgents", Meta = (ForceAsFunction))` — This callback should be overridden by the Trainer and gathers the reward value for the given agent. @param OutReward			Output reward for the given agent. @param AgentId			Agent id to gather reward for.
- L75 _public prototype_ `void GatherAgentRewards(TArray<float>& OutRewards, const TArray<int32>& AgentIds);` — `UFUNCTION(BlueprintNativeEvent, Category = "LearningAgents", Meta = (ForceAsFunction))` — This callback can be overridden by the Trainer and gathers all the reward values for the given set of agents. By default this will call GatherAgentReward on each agent. @param OutRewards		Output rewards for each agent in AgentIds @param AgentIds			Agents to gather rewards for.
- L87 _public prototype_ `void GatherAgentCompletion(ELearningAgentsCompletion& OutCompletion, const int32 AgentId);` — `UFUNCTION(BlueprintNativeEvent, Category = "LearningAgents", Meta = (ForceAsFunction))` — This callback should be overridden by the Trainer and gathers the completion for a given agent. @param OutCompletion		Output completion for the given agent. @param AgentId			Agent id to gather completion for.
- L97 _public prototype_ `void GatherAgentCompletions(TArray<ELearningAgentsCompletion>& OutCompletions, const TArray<int32>& AgentIds);` — `UFUNCTION(BlueprintNativeEvent, Category = "LearningAgents", Meta = (ForceAsFunction))` — This callback can be overridden by the Trainer and gathers all the completions for the given set of agents. By default this will call GatherAgentCompletion on each agent. @param OutCompletions	Output completions for each agent in AgentIds @param AgentIds			Agents to gather completions for.
- L108 _public prototype_ `void ResetAgentEpisode(const int32 AgentId);` — `UFUNCTION(BlueprintNativeEvent, Category = "LearningAgents", Meta = (ForceAsFunction))` — This callback should be overridden by the Trainer and resets the episode for the given agent. @param AgentId			The id of the agent that need resetting.
- L117 _public prototype_ `void ResetAgentEpisodes(const TArray<int32>& AgentIds);` — `UFUNCTION(BlueprintNativeEvent, Category = "LearningAgents", Meta = (ForceAsFunction))` — This callback can be overridden by the Trainer and resets all episodes for each agent in the given set. By default this will call ResetAgentEpisode on each agent. @param AgentIds			The ids of the agents that need resetting.
- L128 _public prototype_ `void GatherRewards();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Call this function when it is time to evaluate the rewards for your agents. This should be done at the beginning of each iteration of your training loop after the initial step, i.e. after taking an action, you want to get into the next state before evaluating the rewards.
- L136 _public prototype_ `void GatherCompletions();` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Call this function when it is time to evaluate the completions for your agents. This should be done at the beginning of each iteration of your training loop after the initial step, i.e. after taking an action, you want to get into the next state before evaluating the completions.
- L142 _public prototype_ `bool HasReward(const int32 AgentId) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AgentId = "-1"))` — Returns true if GatherRewards has been called and the reward already set for the given agent.
- L148 _public prototype_ `bool HasCompletion(const int32 AgentId) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AgentId = "-1"))` — Returns true if GatherCompletions has been called and the completion already set for the given agent.
- L157 _public prototype_ `float GetReward(const int32 AgentId) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AgentId = "-1"))` — Gets the current reward for an agent. Should be called only after GatherRewards. @param AgentId	The AgentId to look-up the reward for @returns			The reward
- L166 _public prototype_ `ELearningAgentsCompletion GetCompletion(const int32 AgentId) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AgentId = "-1"))` — Gets the current completion for an agent. Should be called only after GatherCompletions. @param AgentId	The AgentId to look-up the completion for @returns			The completion type
- L175 _public prototype_ `float GetEpisodeTime(const int32 AgentId) const;` — `UFUNCTION(BlueprintPure, Category = "LearningAgents", meta = (AgentId = "-1"))` — Gets the current elapsed episode time for the given agent. @param AgentId	The AgentId to look-up the episode time for @returns			The elapsed episode time
- L181 _public prototype_ `const TLearningArrayView<1, const float> GetRewardArrayView() const;` — Gets the rewards as a const array view.
- L184 _public prototype_ `uint64 GetRewardIteration(const int32 AgentId) const;` — Gets the reward iteration value for the given agent id.
- L187 _public prototype_ `UE::Learning::ECompletionMode GetAgentCompletion(const int32 AgentId) const;` — Gets the agent completion mode for the given agent id.
- L190 _public prototype_ `const TLearningArrayView<1, const UE::Learning::ECompletionMode> GetAgentCompletions() const;` — Gets the agent completions as a const array view.
- L193 _public prototype_ `const TLearningArrayView<1, const UE::Learning::ECompletionMode> GetAllCompletions() const;` — Gets the all completions as a const array view.
- L196 _public prototype_ `void SetAllCompletions(UE::Learning::FIndexSet AgentSet);` — Computes a combined completion buffer for agents that have been completed manually and those which have reached the maximum episode length.
- L199 _public prototype_ `TLearningArrayView<1, UE::Learning::ECompletionMode> GetEpisodeCompletions();` — Gets the episode completions as a mutable array view.
- L202 _public prototype_ `uint64 GetCompletionIteration(const int32 AgentId) const;` — Gets the completion iteration value for the given agent id.
- L204 _public prototype_ `UE::Learning::FResetInstanceBuffer& GetResetBuffer() const;`
- L210 _private member_ `TArray<float> RewardBuffer;` — Callback Reward Output
- L213 _private member_ `TArray<ELearningAgentsCompletion> CompletionBuffer;` — Callback Completion Output
- L216 _private member_ `TLearningArray<1, float> Rewards;` — Reward Buffer
- L219 _private member_ `TLearningArray<1, UE::Learning::ECompletionMode> AgentCompletions;` — Agent Completions Buffer
- L222 _private member_ `TLearningArray<1, UE::Learning::ECompletionMode> EpisodeCompletions;` — Episode Completions Buffer
- L225 _private member_ `TLearningArray<1, UE::Learning::ECompletionMode> AllCompletions;` — All Completions Buffer
- L228 _private member_ `TLearningArray<1, float> EpisodeTimes;` — Agent episode times
- L230 _private member_ `TUniquePtr<UE::Learning::FResetInstanceBuffer> ResetBuffer;`
- L233 _private member_ `TLearningArray<1, uint64, TInlineAllocator<32>> RewardIteration;` — Number of times rewards have been evaluated for all agents
- L236 _private member_ `TLearningArray<1, uint64, TInlineAllocator<32>> CompletionIteration;` — Number of times completions have been evaluated for all agents

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API LEARNINGAGENTSTRAINING_API`
- L12 _namespace_ `namespace UE`
- L12 _namespace_ `namespace Learning` (scope `UE`)
