# Plugins / CommonConversationRuntime

- module root: `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime`
- headers: 19; symbols: 534
- symbol kinds: class=19, delegate=9, enum=7, enumerator=23, function=124, macro=16, member=124, prototype=188, struct=24
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: AIModule, CoreUObject, GameFeatures, NetCore, Projects, Slate, SlateCore
- PublicDependencyModuleNames: Core, DeveloperSettings, Engine, GameplayTags

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/CommonConversationRuntimeLogging.h` (Public)


#### Free symbols / members of external scopes

- L7 _prototype_ `DECLARE_LOG_CATEGORY_EXTERN(LogCommonConversationRuntime, Log, All);`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/CommonConversationRuntimeModule.h` (Public)


#### class `FCommonConversationRuntimeModule`  
`class FCommonConversationRuntimeModule : public IModuleInterface`  
_L7-14_
- inherits: `IModuleInterface`
- L12 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L13 _public prototype_ `virtual void ShutdownModule() override;`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationChoiceNode.h` (Public)


#### class `UConversationChoiceNode`  
`class UConversationChoiceNode : public UConversationSubNode`  
_L19-41_
- reflection: `UCLASS(MinimalAPI, Blueprintable)`
- inherits: `UConversationSubNode`
- desc: A choice on a task indicates that an option be presented to the user when the owning task is one of the available options of a preceding task.
- L25 _public member_ `FText DefaultChoiceDisplayText;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(ExposeOnSpawn), Category=Conversation)`
- L28 _public member_ `FGameplayTagContainer ChoiceTags;` — `UPROPERTY(BlueprintReadOnly, EditAnywhere, Category=Conversation)`
- L30 _public function_ `bool GetHideChoiceClassName() const`
- L32 _public prototype_ `virtual bool GenerateChoice(const FConversationContext& Context, FClientConversationOptionEntry& ChoiceEntry) const;`
- L34 _public prototype_ `virtual void NotifyChoicePickedByUser(const FConversationContext& InContext, const FClientConversationOptionEntry& InClientChoice) const;`
- L38 _protected prototype_ `void FillChoice(const FConversationContext& Context, FClientConversationOptionEntry& ChoiceEntry) const;` — `UFUNCTION(BlueprintNativeEvent)`
- L40 _protected member_ `bool bHideChoiceClassName = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationContext.h` (Public)


#### enum `EConversationTaskResultType`  
`enum class EConversationTaskResultType : uint8`  
_L27-62_
- reflection: `UENUM(BlueprintType)`
- desc: The conversation task result type gives the conversation system the instruction it needs after running a task.  Should we continue to the next task? or stop and give the player the choice of moving forward?
- L29 _public enumerator_ `Invalid`
- L31 _public enumerator_ `AbortConversation` — Aborts the conversation.
- L33 _public enumerator_ `AdvanceConversation` — Advances the conversation to the next task, or a random one if there are multiple.
- L39 _public enumerator_ `AdvanceConversationWithChoice` — Advances the conversation to a choice, this choice does not have to be one that would normally come next. Consider using this in advanced situations where you want to potentially dynamically jump to any node in existence.
- L44 _public enumerator_ `PauseConversationAndSendClientChoices` — Stops the conversation flow and notifies the client that there are choices, with a payload of anything the NPC needs to say along with whatever choices the user has.
- L49 _public enumerator_ `ReturnToLastClientChoice` — Dynamically allows jumping 'back' one step in the conversation.  This does not go back one Task, but to the last time in the conversation flow we paused conversation and sent the client choices.
- L56 _public enumerator_ `ReturnToCurrentClientChoice` — Does not advance the conversation, just refreshes the current choices again. This option is really useful if you need to have the user make a choice and then make the same choice again, ex. User clicks an option to buy an item, and you want them to be able to repeat that action.
- L61 _public enumerator_ `ReturnToConversationStart` — Allows jumping back to the beginning of the entire conversation tree, so that you can effectively, return to the 'main menu'.

#### struct `FConversationTaskResult`  
`struct FConversationTaskResult`  
_L70-148_
- reflection: `USTRUCT(BlueprintType)`
- desc: The FConversationTaskResult encompasses the type of result along with any extra data we need for that kind of result, for example if we're giving the player a message and giving them a choice, what what message do we need to send.
- L75 _public function_ `static FConversationTaskResult AbortConversation()`
- L80 _public function_ `static FConversationTaskResult AdvanceConversation()`
- L85 _public function_ `static FConversationTaskResult AdvanceConversationWithChoice(const FAdvanceConversationRequest& InAdvanceToChoice)`
- L90 _public function_ `static FConversationTaskResult PauseConversationAndSendClientChoices(const FClientConversationMessage& InMessage)`
- L95 _public function_ `static FConversationTaskResult ReturnToLastClientChoice()`
- L100 _public function_ `static FConversationTaskResult ReturnToCurrentClientChoice()`
- L105 _public function_ `static FConversationTaskResult ReturnToConversationStart()`
- L110 _public function_ `EConversationTaskResultType GetType() const`
- L111 _public function_ `const FAdvanceConversationRequest& GetChoice() const`
- L112 _public function_ `const FClientConversationMessage& GetMessage() const`
- L114 _public function_ `bool CanConversationContinue() const`
- L120 _public function_ `FConversationTaskResult() : Type(EConversationTaskResultType::Invalid)`
- L127 _public function_ `explicit inline FConversationTaskResult(EForceInit) : Type(EConversationTaskResultType::Invalid)` — Constructor @param EForceInit Force init enum
- L133 _private function_ `FConversationTaskResult(EConversationTaskResultType InType, const FAdvanceConversationRequest& InAdvanceToChoice, const FClientConversationMessage& InMessage) : Type(InType) , AdvanceToChoice(InAdvanceToChoice) , Message(InMessage)`
- L141 _private member_ `EConversationTaskResultType Type;` — `UPROPERTY()`
- L144 _private member_ `FAdvanceConversationRequest AdvanceToChoice;` — `UPROPERTY()`
- L147 _private member_ `FClientConversationMessage Message;` — `UPROPERTY()`

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FConversationTaskResult> : public TStructOpsTypeTraitsBase2<FConversationTaskResult>`  
_L152-158_
- inherits: `TStructOpsTypeTraitsBase2<FConversationTaskResult>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L155-157_

#### struct `FConversationContext`  
`struct FConversationContext`  
_L164-237_
- reflection: `USTRUCT(BlueprintType)`
- desc: Information about a currently active conversation
- L170 _public prototype_ `static FConversationContext CreateServerContext(UConversationInstance* InActiveConversation, const UConversationTaskNode* InTaskBeingConsidered);`
- L171 _public prototype_ `static FConversationContext CreateClientContext(UConversationParticipantComponent* InParticipantComponent, const UConversationTaskNode* InTaskBeingConsidered);`
- L173 _public prototype_ `FConversationContext CreateChildContext(const UConversationTaskNode* NewTaskBeingConsidered) const;`
- L174 _public prototype_ `FConversationContext CreateReturnScopeContext(const FConversationNodeHandle& NewReturnScope) const;`
- L176 _public prototype_ `UWorld* GetWorld() const;`
- L178 _public prototype_ `FConversationNodeHandle GetCurrentNodeHandle() const;`
- L180 _public function_ `UConversationRegistry& GetConversationRegistry() const`
- L182 _public function_ `UConversationInstance* GetActiveConversation() const`
- L183 _public function_ `UConversationInstance* TryGetActiveConversation() const`
- L185 _public function_ `const UConversationTaskNode* GetTaskBeingConsidered() const`
- L187 _public function_ `const TArray<FConversationNodeHandle>& GetReturnScopeStack() const`
- L189 _public prototype_ `const FConversationParticipantEntry* GetParticipant(const FGameplayTag& ParticipantTag) const;`
- L191 _public function_ `UConversationParticipantComponent* GetParticipantComponent(const FGameplayTag& ParticipantTag) const`
- L201 _public function_ `AActor* GetParticipantActor(const FGameplayTag& ParticipantTag) const`
- L211 _public prototype_ `FConversationParticipants GetParticipantsCopy() const;`
- L213 _public function_ `bool IsServerContext() const`
- L214 _public function_ `bool IsClientContext() const`
- L218 _private member_ `TObjectPtr<UConversationRegistry> ConversationRegistry = nullptr;` — `UPROPERTY()`
- L221 _private member_ `TObjectPtr<UConversationInstance> ActiveConversation = nullptr;` — `UPROPERTY()`
- L224 _private member_ `TObjectPtr<UConversationParticipantComponent> ClientParticipant = nullptr;` — `UPROPERTY()`
- L227 _private member_ `TObjectPtr<const UConversationTaskNode> TaskBeingConsidered = nullptr;` — `UPROPERTY()`
- L230 _private member_ `TArray<FConversationNodeHandle> ReturnScopeStack;` — `UPROPERTY()`
- L233 _private member_ `bool bServer_PRIVATE = false;` — `UPROPERTY()`
- L236 _private member_ `bool bClient_PRIVATE = false;` — `UPROPERTY()`

#### class `UConversationContextHelpers`  
`class UConversationContextHelpers : public UBlueprintFunctionLibrary`  
_L243-317_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- desc: Wrapper methods from FConversationContext
- L253 _public prototype_ `static UConversationInstance* GetConversationInstance(const FConversationContext& Context);` — `UFUNCTION(BlueprintPure, BlueprintAuthorityOnly, Category=Conversation)` — Returns the conversation instance object associated with the conversation context provided, or nullptr if not valid
- L257 _public prototype_ `static FConversationNodeHandle GetCurrentConversationNodeHandle(const FConversationContext& Context);` — `UFUNCTION(BlueprintPure, BlueprintAuthorityOnly, Category=Conversation)` — Returns the FConversationNodeHandle of the conversation instance associated with this context, or a handle with an invalid FGuid if not possible
- L264 _public prototype_ `static void MakeConversationParticipant(const FConversationContext& Context, AActor* ParticipantActor, FGameplayTag ParticipantTag);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Conversation)` — Registers an actor as part of the conversation, that actor doesn't need to have the UConversationParticipantComponent it won't be added though.
- L270 _public prototype_ `static FConversationTaskResult AdvanceConversation(const FConversationContext& Context);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Conversation)` — Constructs and returns a FConversationTaskResult configured with EConversationTaskResultType::AdvanceConversation
- L274 _public prototype_ `static FConversationTaskResult AdvanceConversationWithChoice(const FConversationContext& Context, const FAdvanceConversationRequest& Choice);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, meta=(AutoCreateRefTerm="Choice"), Category=Conversation)` — Constructs and returns a FConversationTaskResult configured with EConversationTaskResultType::AdvanceConversationWithChoice
- L278 _public prototype_ `static FConversationTaskResult PauseConversationAndSendClientChoices(const FConversationContext& Context, const FClientConversationMessage& Message);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Conversation)` — Constructs and returns a FConversationTaskResult configured with EConversationTaskResultType::PauseConversationAndSendClientChoices
- L282 _public prototype_ `static FConversationTaskResult ReturnToLastClientChoice(const FConversationContext& Context);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Conversation)` — Constructs and returns a FConversationTaskResult configured with EConversationTaskResultType::ReturnToLastClientChoice
- L286 _public prototype_ `static FConversationTaskResult ReturnToCurrentClientChoice(const FConversationContext& Context);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Conversation)` — Constructs and returns a FConversationTaskResult configured with EConversationTaskResultType::ReturnToCurrentClientChoice
- L290 _public prototype_ `static FConversationTaskResult ReturnToConversationStart(const FConversationContext& Context);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Conversation)` — Constructs and returns a FConversationTaskResult configured with EConversationTaskResultType::ReturnToConversationStart
- L294 _public prototype_ `static FConversationTaskResult AbortConversation(const FConversationContext& Context);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Conversation)` — Constructs and returns a FConversationTaskResult configured with EConversationTaskResultType::AbortConversation
- L301 _public prototype_ `static bool CanConversationContinue(const FConversationTaskResult& ConversationTasResult);` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = Conversation)` — Checks the provided task result against any which would end the conversation e.g. EConversationTaskResultType::Invalid or EConversationTaskResultType::AbortConversation
- L308 _public prototype_ `static UConversationParticipantComponent* GetConversationParticipant(const FConversationContext& Context, FGameplayTag ParticipantTag);` — `UFUNCTION(BlueprintPure=false, Category=Conversation)` — Returns the conversation participant component belonging to the participant indicated by 'ParticipantTag', or nullptr if not found
- L312 _public prototype_ `static AActor* GetConversationParticipantActor(const FConversationContext& Context, FGameplayTag ParticipantTag);` — `UFUNCTION(BlueprintPure=false, Category=Conversation)` — Returns the conversation participant actor indicated by 'ParticipantTag', or nullptr if not found
- L316 _public prototype_ `static UConversationParticipantComponent* FindConversationComponent(AActor* Actor);` — `UFUNCTION(BlueprintPure=false, Category=Conversation)` — Wrapper to find and return any UConversationParticipantComponent belonging to the provided parameter actor

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`
- L156 _enumerator_ `WithNoInitConstructor = true` (scope `TStructOpsTypeTraits::__anon735977920103`)

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationDatabase.h` (Public)


#### struct `FConversationEntryList`  
`struct FConversationEntryList`  
_L26-38_
- reflection: `USTRUCT(BlueprintType)`
- desc: There may be multiple databases with the same entrypoint tag, this struct holds all of those nodes with the same matching tag name, so that the entry point is effectively randomized when there are multiple copies.
- L31 _public member_ `FGameplayTag EntryTag;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation)`
- L34 _public member_ `TArray<FGuid> DestinationList;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation)`
- L37 _public member_ `FString EntryIdentifier;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation)`

#### struct `FCommonDialogueBankParticipant`  
`struct FCommonDialogueBankParticipant`  
_L49-65_
- reflection: `USTRUCT(BlueprintType)`
- L54 _public member_ `FText FallbackName;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation)`
- L58 _public member_ `FGameplayTag ParticipantName;` — `UPROPERTY(EditAnywhere, Category=Identification, meta=(Categories="Conversation.Participant"))` — Identifier represented by the component
- L61 _public member_ `FLinearColor NodeTint = FLinearColor::White;` — `UPROPERTY(EditAnywhere, Category = Identification)`

#### class `UConversationDatabase`  
`class UConversationDatabase : public UPrimaryDataAsset`  
_L74-148_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UPrimaryDataAsset`
- L79 _public prototype_ `UConversationDatabase(const FObjectInitializer& ObjectInitializer);`
- L82 _public prototype_ `virtual void PostDuplicate(bool bDuplicateForPIE) override;`
- L83 _public prototype_ `virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;`
- L84 _public prototype_ `virtual EDataValidationResult ValidateOutBoundConnections(class FDataValidationContext& Context) const;`
- L85 _public prototype_ `virtual void PreSave(FObjectPreSaveContext ObjectSaveContext) override;`
- L87 _public function_ `const TMap<FGuid, TObjectPtr<UConversationNode>>& GetFullNodeMap() const`
- L90 _public function_ `bool IsNodeReachable(const FGuid& NodeGUID) const`
- L92 _public prototype_ `FLinearColor GetDebugParticipantColor(FGameplayTag ParticipantID) const;`
- L98 _private member_ `int32 CompilerVersion = INDEX_NONE;` — `UPROPERTY(AssetRegistrySearchable)` — Compiled: Entry points
- L102 _private member_ `TMap<FGuid, TObjectPtr<UConversationNode>> ReachableNodeMap;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation, meta = (AllowPrivateAccess = "true"))` — Compiled: Reachable nodes
- L106 _private member_ `TArray<FConversationEntryList> EntryTags;` — `UPROPERTY(AssetRegistrySearchable, BlueprintReadOnly, Category = Conversation, meta = (AllowPrivateAccess = "true"))` — Compiled: Entry points
- L110 _private member_ `FGameplayTagContainer ExitTags;` — `UPROPERTY(AssetRegistrySearchable, BlueprintReadOnly, Category = Conversation, meta = (AllowPrivateAccess = "true"))` — Compiled:
- L114 _private member_ `TArray<FGuid> InternalNodeIds;` — `UPROPERTY(AssetRegistrySearchable)` — Compiled:
- L118 _private member_ `TArray<FGuid> LinkedToNodeIds;` — `UPROPERTY(AssetRegistrySearchable)` — Compiled:
- L123 _private member_ `TArray<FCommonDialogueBankParticipant> Speakers;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Conversation, meta = (AllowPrivateAccess = "true"))` — List of participant slots
- L130 _private member_ `TMap<FGuid, TObjectPtr<UConversationNode>> FullNodeMap;` — `UPROPERTY()` — All nodes
- L134 _private member_ `TArray<TObjectPtr<UEdGraph>> SourceGraphs;` — `UPROPERTY()` — 'Source code' graphs (of type UConversationGraph)
- L137 _public prototype_ `FGuid GetGuidFromNode(const UConversationNode* NodeToFind) const;`
- L138 _public prototype_ `TObjectPtr<class UEdGraphNode> GetSourceGraphNodeFromGuid(FGuid NodeToFind) const;`
- L142 _public member_ `TArray<FEditedDocumentInfo> LastEditedDocuments;` — `UPROPERTY()` — Info about the graphs we last edited

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationEntryPointNode.h` (Public)


#### class `UConversationEntryPointNode`  
`class UConversationEntryPointNode : public UConversationNodeWithLinks`  
_L12-22_
- reflection: `UCLASS(MinimalAPI, meta=(DisplayName="Entry Point"))`
- inherits: `UConversationNodeWithLinks`
- L18 _public member_ `FGameplayTag EntryTag;` — `UPROPERTY(EditAnywhere, Category=Conversation)`
- L21 _public prototype_ `virtual FString GetIdentifier();` — `UFUNCTION()`

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationInstance.h` (Public)


#### class `UConversationInstance`  
`class UConversationInstance : public UObject`  
_L29-186_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UObject`
- desc: An active conversation between one or more participants
- L36 _public prototype_ `DECLARE_EVENT_OneParam(UConversationInstance, FOnAllParticipantsNotifiedOfStartEvent, UConversationInstance* );` — Server notification sent after all participants have been individually notified of conversation start
- L37 _public member_ `FOnAllParticipantsNotifiedOfStartEvent OnAllParticipantsNotifiedOfStart;`
- L40 _public prototype_ `UConversationInstance();`
- L42 _public prototype_ `virtual UWorld* GetWorld() const override;`
- L47 _public prototype_ `void ServerRemoveParticipant(const FGameplayTag& ParticipantID, const FConversationParticipants& PreservedParticipants);` — Should be called with a copy of the conversation participants before any removals happen, that way clients can properly respond to the end of their respective conversations with an accurate account of who was in that conversation.
- L49 _public prototype_ `void ServerAssignParticipant(const FGameplayTag& ParticipantID, AActor* ParticipantActor);`
- L51 _public prototype_ `void ServerStartConversation(const FGameplayTag& EntryPoint, const UConversationDatabase* Graph = nullptr, const FString& EntryPointIdentifier = FString());`
- L53 _public prototype_ `void ServerAdvanceConversation(const FAdvanceConversationRequest& InChoicePicked);`
- L55 _public prototype_ `virtual void OnInvalidBranchChoice(const FAdvanceConversationRequest& InChoicePicked);`
- L57 _public prototype_ `void ServerAbortConversation();`
- L59 _public prototype_ `void ServerRefreshConversationChoices();`
- L61 _public prototype_ `void ServerRefreshTaskChoiceData(const FConversationNodeHandle& Handle);`
- L65 _public prototype_ `void ServerRefreshCurrentConversationNode();` — Attempts to process the current conversation node again - only useful in very specific circumstances where you'd want to re-run the current node without having to deal with conversation flow changes.
- L71 _public function_ `FConversationMemory& GetInstanceMemory()` — This is memory that will last for the duration of the conversation instance.  Don't store anything here you want to be long lived.
- L73 _public prototype_ `TArray<FGuid> DetermineBranches(const TArray<FGuid>& SourceList, EConversationRequirementResult MaximumRequirementResult = EConversationRequirementResult::Passed);`
- L77 _public function_ `TArray<FConversationParticipantEntry> GetParticipantListCopy() const` — @TODO: Conversation: Meh
- L82 _public function_ `const TArray<FConversationParticipantEntry>& GetParticipantList() const`
- L87 _public function_ `FConversationParticipants GetParticipantsCopy() const`
- L92 _public function_ `const FConversationParticipantEntry* GetParticipant(FGameplayTag ParticipantID) const`
- L97 _public function_ `UConversationParticipantComponent* GetParticipantComponent(FGameplayTag ParticipantID) const`
- L102 _public function_ `const UConversationDatabase* GetActiveConversationGraph() const`
- L107 _public function_ `const FConversationNodeHandle& GetCurrentNodeHandle() const`
- L108 _public function_ `const FConversationChoiceReference& GetCurrentChoiceReference() const`
- L109 _public function_ `const TArray<FClientConversationOptionEntry>& GetCurrentUserConversationChoices() const`
- L112 _protected function_ `virtual void OnStarted()`
- L113 _protected function_ `virtual void OnEnded()`
- L116 _protected prototype_ `void ModifyCurrentConversationNode(const FConversationChoiceReference& NewChoice);`
- L117 _protected prototype_ `void ModifyCurrentConversationNode(const FConversationBranchPoint& NewBranchPoint);`
- L118 _protected prototype_ `void ReturnToLastClientChoice(const FConversationContext& Context);`
- L119 _protected prototype_ `void ReturnToCurrentClientChoice(const FConversationContext& Context);`
- L120 _protected prototype_ `void ReturnToStart(const FConversationContext& Context);`
- L121 _protected prototype_ `virtual void PauseConversationAndSendClientChoices(const FConversationContext& Context, const FClientConversationMessage& ClientMessage);`
- L122 _protected function_ `virtual void OnChoiceNodePickedByUser(const FConversationContext& Context, const UConversationChoiceNode* ChoiceNode, const TArray<FConversationBranchPoint>& ValidDestinations)`
- L126 _private prototype_ `bool AreAllParticipantsReadyToConverse() const;`
- L127 _private prototype_ `void TryStartingConversation();`
- L129 _private function_ `const FConversationBranchPoint& GetCurrentBranchPoint() const`
- L131 _private prototype_ `void ResetConversationProgress();`
- L132 _private prototype_ `void UpdateNextChoices(const FConversationContext& Context);`
- L133 _private prototype_ `void SetNextChoices(const TArray<FConversationBranchPoint>& InAllChoices);`
- L134 _private prototype_ `const FConversationBranchPoint* FindBranchPointFromClientChoice(const FConversationChoiceReference& InChoice) const;`
- L137 _private prototype_ `void OnCurrentConversationNodeModified();`
- L139 _private prototype_ `void ProcessCurrentConversationNode();`
- L142 _private prototype_ `int32 ChooseBranchIndex(EConversationNodeBranchOrder BranchOrder, int32 NumBranchIndices);` — Chooses the next branch index. Called when the conversation advanced and the user did not select a choice
- L146 _protected function_ `const FGameplayTagContainer& GetCurrentChoiceTags() const`
- L148 _protected member_ `TArray<FClientConversationOptionEntry> CurrentUserChoices;`
- L152 _private member_ `FConversationParticipants Participants;` — `UPROPERTY()`
- L155 _private member_ `TObjectPtr<const UConversationDatabase> ActiveConversationGraph = nullptr;` — `UPROPERTY()`
- L157 _private member_ `FGameplayTag StartingEntryGameplayTag;`
- L158 _private member_ `FConversationBranchPoint StartingBranchPoint;`
- L160 _private member_ `FConversationBranchPoint CurrentBranchPoint;`
- L168 _private member_ `TArray<FCheckpoint> ClientBranchPoints;`
- L170 _private member_ `TArray<FConversationBranchPoint> CurrentBranchPoints;`
- L172 _private member_ `TArray<FConversationChoiceReference> ScopeStack;`
- L174 _private member_ `FRandomStream ConversationRNG;`
- L178 _private member_ `FConversationMemory InstanceMemory;`
- L182 _private member_ `bool bConversationStarted = false;`
- L185 _public function_ `const bool HasConversationStarted() const`

#### struct `UConversationInstance::FCheckpoint`  
`struct FCheckpoint`  
_L162-166_
- L164 _public member_ `FConversationBranchPoint ClientBranchPoint;`
- L165 _public member_ `TArray<FConversationChoiceReference> ScopeStack;`

#### Free symbols / members of external scopes

- L12 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`
- L21 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllParticipantsNotifiedOfStartEvent, UConversationInstance*, ConversationInstance);`
- L21 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAllParticipantsNotifiedOfStartEvent, UConversationInstance*, ConversationInstance);`
- L36 _delegate_ `DECLARE_EVENT_OneParam(UConversationInstance, FOnAllParticipantsNotifiedOfStartEvent, UConversationInstance* );` — Server notification sent after all participants have been individually notified of conversation start

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationLibrary.h` (Public)


#### class `UConversationLibrary`  
`class UConversationLibrary : public UBlueprintFunctionLibrary`  
_L20-34_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UBlueprintFunctionLibrary`
- L25 _public prototype_ `UConversationLibrary();`
- L28 _public prototype_ `static UConversationInstance* StartConversation(const FGameplayTag& ConversationEntryTag, AActor* Instigator, const FGameplayTag& InstigatorTag, AActor* Target, const FGameplayTag& TargetTag, const TSubclassOf<UConversationInstance> ConversationInstanceClass = {});` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category="Conversation", meta = (DeterminesOutputType = "ConversationType"))`
- L32 _public prototype_ `static UConversationInstance* StartConversationFromGraph(const FGameplayTag& ConversationEntryTag, AActor* Instigator, const FGameplayTag& InstigatorTag, AActor* Target, const FGameplayTag& TargetTag, const UConversationDatabase* Graph, const FString& EntryPointIdentifier = TEXT(""));` — `UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Conversation", meta = (DeterminesOutputType = "ConversationType"))`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationLinkNode.h` (Public)


#### class `UConversationLinkNode`  
`class UConversationLinkNode : public UConversationTaskNode`  
_L13-28_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UConversationTaskNode`
- L18 _public prototype_ `UConversationLinkNode();`
- L20 _public function_ `FGameplayTag GetRemoteEntryTag() const`
- L23 _protected prototype_ `virtual FConversationTaskResult ExecuteTaskNode_Implementation(const FConversationContext& Context) const override;`
- L24 _protected prototype_ `virtual void GatherChoices(FConversationBranchPointBuilder& BranchBuilder, const FConversationContext& Context) const override;`
- L27 _protected member_ `FGameplayTag RemoteEntryTag;` — `UPROPERTY(EditAnywhere, Category = "Link")`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationMemory.h` (Public)


#### class `FConversationMemory`  
`class FConversationMemory : public FNoncopyable`  
_L16-93_
- inherits: `FNoncopyable`
- desc: Used to store arbitrary structs of data in different contexts for a conversation.  During a conversation an NPC may need to remember a choice or remember a randomly chosen thing.  This memory store allows that across different contexts, such as for the duration of the conversation instance, or as memory on the NPC.
- L19 _public function_ `FConversationMemory()`
- L20 _public prototype_ `~FConversationMemory();`
- L23 _public prototype_ `void* GetTaskMemoryOfType(const UConversationTaskNode& Task, const UScriptStruct* TaskMemoryStructType);` — NOTE: It is not valid for your memory struct to store a RAW UObject*, this data is not scanned for garbage collection.
- L27 _public function_ `template <typename TStructTaskMemory> TStructTaskMemory* GetTaskMemory(const UConversationTaskNode& Task)` — NOTE: It is not valid for your memory struct to store a RAW UObject*, this data is not scanned for garbage collection.
- L41 _private function_ `friend inline uint32 GetTypeHash(const FConversationTaskMemoryKey& Key)`
- L49 _private member_ `TMap<FConversationTaskMemoryKey, void*> TaskMemory;`
- L92 _private member_ `FTaskMemoryAllocator TaskMemoryAllocator;`

#### struct `FConversationMemory::FConversationTaskMemoryKey`  
`struct FConversationTaskMemoryKey`  
_L33-47_
- L36 _public prototype_ `FConversationTaskMemoryKey(const UConversationTaskNode& SourceTaskInstance, const UScriptStruct* TaskMemoryStructClass);`
- L38 _public prototype_ `const UScriptStruct* GetTaskMemoryStruct() const;`
- L40 _public function_ `bool operator==(const FConversationTaskMemoryKey& Rhs) const`
- L44 _private member_ `FObjectKey SourceTaskInstanceKey;`
- L45 _private member_ `FObjectKey TaskMemoryStructClassKey;`
- L46 _private member_ `uint32 KeyHash;`

#### class `FConversationMemory::FTaskMemoryAllocator`  
`class FTaskMemoryAllocator`  
_L52-90_
- desc: @TODO: Conversation: Copied from the SlabAllocator, we should have something like this in Core.
- L55 _public function_ `FTaskMemoryAllocator() : SlabSize(16384)`
- L60 _public function_ `~FTaskMemoryAllocator()`
- L68 _public function_ `void* Allocate(uint64 Size)`
- L85 _private member_ `TArray<void*> Slabs;`
- L86 _private member_ `uint8* CurrentSlab = nullptr;`
- L87 _private member_ `const uint64 SlabSize;`
- L88 _private member_ `uint64 CurrentSlabAllocatedSize = 0;`
- L89 _private member_ `uint64 TotalAllocatedSize = 0;`

#### Free symbols / members of external scopes

- L7 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationNode.h` (Public)


#### enum `EConversationNodeDescriptionVerbosity`  
`enum class EConversationNodeDescriptionVerbosity : uint8`  
_L22-26_
- L24 _public enumerator_ `Basic`
- L25 _public enumerator_ `Detailed`

#### struct `FConversationNodeHandle`  
`struct FConversationNodeHandle`  
_L34-64_
- reflection: `USTRUCT(BlueprintType)`
- L39 _public function_ `FConversationNodeHandle() : NodeGUID(0, 0, 0, 0)`
- L40 _public function_ `FConversationNodeHandle(const FGuid& InNodeGUID) : NodeGUID(InNodeGUID)`
- L43 _public member_ `FGuid NodeGUID;` — `UPROPERTY(EditAnywhere, Category=Conversation)`
- L45 _public function_ `bool IsValid() const`
- L46 _public function_ `FString ToString() const`
- L47 _public function_ `void Invalidate()`
- L49 _public function_ `FConversationNodeHandle& operator = (const FGuid& InNodeGUID)`
- L55 _public function_ `operator FGuid& ()`
- L56 _public function_ `operator FGuid() const`
- L62 _public prototype_ `const UConversationNode* TryToResolve(const FConversationContext& Context) const;` — Tries to resolve the node, this may fail, the guid might be bogus, or the node might not be in memory.
- L63 _public prototype_ `const UConversationNode* TryToResolve_Slow(UWorld* InWorld, const UConversationDatabase* Graph = nullptr) const;`

#### class `UConversationNode`  
`class UConversationNode : public UObject`  
_L73-167_
- reflection: `UCLASS(MinimalAPI, Abstract, Const)`
- inherits: `UObject`
- desc: Represents a single runtime node in the conversation database.
- L77 _private prototype_ `virtual UWorld* GetWorld() const override;`
- L80 _private prototype_ `void InitializeNode(UConversationNode* InParentNode);` — fill in data about tree structure
- L83 _private prototype_ `virtual void InitializeFromAsset(UConversationDatabase& Asset);` — initialize any asset related data
- L86 _private prototype_ `virtual void DescribeRuntimeValues(const UCommonDialogueConversation& OwnerComp, EConversationNodeDescriptionVerbosity Verbosity, TArray<FString>& Values) const;` — gathers description of all runtime parameters
- L89 _private function_ `UConversationNode* GetParentNode() const` — @return parent node
- L92 _private prototype_ `FText GetDisplayNameText() const;` — @return name of node
- L95 _private prototype_ `FText GetRuntimeDescription(const UCommonDialogueConversation& OwnerComp, EConversationNodeDescriptionVerbosity Verbosity) const;` — @return string containing description of this node instance with all relevant runtime values
- L98 _private prototype_ `virtual FText GetStaticDescription() const;` — @return string containing description of this node with all setup values
- L101 _private function_ `FGuid GetNodeGuid() const` — The node's unique ID.
- L105 _private prototype_ `virtual FName GetNodeIconName() const;` — Get the name of the icon used to display this node in the editor
- L108 _private function_ `virtual void OnNodeCreated()` — Called after creating new node in behavior tree editor, use for versioning
- L110 _private function_ `bool ShowPropertyEditors() const`
- L115 _private function_ `bool ShowPropertyDetails() const`
- L128 _protected prototype_ `FLinearColor GetDebugParticipantColor(FGameplayTag ParticipantID) const;` — `UFUNCTION(BlueprintCallable, Category=Conversation)`
- L132 _protected prototype_ `bool ShouldHideProperty(FProperty* InTestProperty) const;` — @return true if this property should be hidden in static description, false if should be shown
- L137 _public member_ `mutable TObjectPtr<UObject> EvalWorldContextObj;` — `UPROPERTY(Transient, DuplicateTransient)`
- L142 _protected member_ `FString NodeName;` — `UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Description, AdvancedDisplay, meta = (AllowPrivateAccess = "true"))` — node name
- L148 _protected member_ `FGuid Compiled_NodeGUID;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation, meta = (AllowPrivateAccess = "true"))` — The node's unique ID.  This value is set during compilation.
- L153 _protected member_ `uint32 bShowPropertyDetails : 1;` — `UPROPERTY(EditInstanceOnly, Category=Description, AdvancedDisplay)` — show detailed information about properties
- L157 _protected member_ `uint32 bShowPropertyEditors : 1;` — `UPROPERTY(EditInstanceOnly, Category=Description, AdvancedDisplay)` — show detailed information about properties
- L163 _private member_ `TObjectPtr<UConversationNode> ParentNode;` — `UPROPERTY()` — parent node

#### class `UConversationNodeWithLinks`  
`class UConversationNodeWithLinks : public UConversationNode`  
_L172-183_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UConversationNode`
- L178 _public member_ `TArray<FGuid> OutputConnections;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation)`
- L180 _public function_ `virtual bool IsOutBoundConnectionAllowed(const UConversationNodeWithLinks* OtherNode, FText& OutErrorMessage) const`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`
- L66 _function_ `inline bool operator==(const FConversationNodeHandle& Lhs, const FConversationNodeHandle& Rhs)`
- L67 _function_ `inline bool operator!=(const FConversationNodeHandle& Lhs, const FConversationNodeHandle& Rhs)`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationParticipantComponent.h` (Public)


#### class `UConversationParticipantComponent`  
`class UConversationParticipantComponent : public UActorComponent`  
_L22-173_
- reflection: `UCLASS(MinimalAPI, BlueprintType)`
- inherits: `UActorComponent`
- desc: Active conversation participants should have this component on them. It keeps track of what conversations they are participating in (typically no more than one)
- L27 _public prototype_ `UConversationParticipantComponent();`
- L30 _public prototype_ `DECLARE_EVENT_OneParam(UConversationParticipantComponent, FConversationStatusChangedEvent, bool );` — Client and server notification of the conversation starting or ending
- L31 _public member_ `FConversationStatusChangedEvent ConversationStatusChanged;`
- L33 _public prototype_ `DECLARE_EVENT(UConversationParticipantComponent, FConversationStartedEvent);`
- L34 _public member_ `FConversationStartedEvent ConversationStarted;`
- L36 _public prototype_ `DECLARE_EVENT_OneParam(UConversationParticipantComponent, FConversationUpdatedEvent, const FClientConversationMessagePayload& );`
- L37 _public member_ `FConversationUpdatedEvent ConversationUpdated;`
- L39 _public prototype_ `DECLARE_EVENT_TwoParams(UConversationParticipantComponent, FConversationTaskChoiceDataUpdatedEvent, const FConversationNodeHandle& , const FClientConversationOptionEntry& );`
- L40 _public member_ `FConversationTaskChoiceDataUpdatedEvent ConversationTaskChoiceDataUpdated;`
- L43 _public prototype_ `void SendClientConversationMessage(const FConversationContext& Context, const FClientConversationMessagePayload& Payload);`
- L44 _public prototype_ `virtual void SendClientUpdatedChoices(const FConversationContext& Context, const bool bForcedRefresh = false);`
- L45 _public prototype_ `void SendClientRefreshedTaskChoiceData(const FConversationNodeHandle& Handle, const FConversationContext& Context);`
- L48 _public prototype_ `void RequestServerAdvanceConversation(const FAdvanceConversationRequest& InChoicePicked);` — `UFUNCTION(BlueprintCallable, Category=Conversation)`
- L51 _public prototype_ `void ServerNotifyConversationStarted(UConversationInstance* Conversation, FGameplayTag AsParticipant);`
- L52 _public prototype_ `void ServerNotifyConversationEnded(UConversationInstance* Conversation, const FConversationParticipants& PreservedParticipants);`
- L53 _public prototype_ `void ServerNotifyExecuteTaskAndSideEffects(const FConversationNodeHandle& Handle, const UConversationDatabase* Graph = nullptr);`
- L54 _public prototype_ `void ServerForAllConversationsRefreshChoices(UConversationInstance* IgnoreConversation = nullptr);`
- L55 _public prototype_ `void ServerForAllConversationsRefreshTaskChoiceData(const FConversationNodeHandle& Handle, UConversationInstance* IgnoreConversation );`
- L58 _public function_ `virtual bool ServerIsReadyToConverse() const` — Check if this actor is in a good state to start a conversation
- L61 _public prototype_ `virtual void ServerGetReadyToConverse();` — Ask to this actor to change is state to be able to start a conversation
- L64 _public prototype_ `void ServerAbortAllConversations();` — Ask this actor to abort all active conversations
- L66 _public function_ `FConversationMemory& GetParticipantMemory()`
- L68 _public prototype_ `DECLARE_MULTICAST_DELEGATE_OneParam(FParticipantReadyToConverse, UConversationParticipantComponent*);`
- L70 _public member_ `FParticipantReadyToConverse OnParticipantReadyToConverseEvent;` — Delegate send when this actor enter in the good state to start a conversation
- L74 _public prototype_ `virtual FText GetParticipantDisplayName();` — `UFUNCTION(BlueprintCallable, Category=Conversation)`
- L77 _public prototype_ `bool IsInActiveConversation() const;` — `UFUNCTION(BlueprintCallable, Category = Conversation)`
- L81 _public prototype_ `FConversationNodeHandle GetCurrentNodeHandle() const;`
- L83 _public prototype_ `const FConversationParticipantEntry* GetParticipant(const FGameplayTag& ParticipantTag) const;`
- L86 _public prototype_ `AActor* GetParticipantActor(const FGameplayTag& ParticipantTag) const;` — `UFUNCTION(BlueprintPure, Category = Conversation)`
- L89 _public prototype_ `void GetOtherParticipantActors(TArray<AActor*>& OutParticipantActors) const;` — `UFUNCTION(BlueprintCallable, Category = Conversation)`
- L93 _protected prototype_ `void ServerAdvanceConversation(const FAdvanceConversationRequest& InChoicePicked);` — `UFUNCTION(Server, Reliable)`
- L96 _protected prototype_ `void ClientUpdateParticipants(const FConversationParticipants& InParticipants);` — `UFUNCTION(Client, Reliable)`
- L99 _protected prototype_ `void ClientExecuteTaskAndSideEffects(FConversationNodeHandle Handle, const UConversationDatabase* Graph = nullptr);` — `UFUNCTION(Client, Reliable)`
- L102 _protected prototype_ `void ClientUpdateConversation(const FClientConversationMessagePayload& Message);` — `UFUNCTION(Client, Reliable)`
- L105 _protected prototype_ `void ClientUpdateConversationTaskChoiceData(FConversationNodeHandle Handle, const FClientConversationOptionEntry& OptionEntry);` — `UFUNCTION(Client, Reliable)`
- L108 _protected prototype_ `void ClientUpdateConversations(int32 InConversationsActive);` — `UFUNCTION(Client, Reliable)`
- L111 _protected prototype_ `void ClientStartConversation(const FConversationParticipants& InParticipants);` — `UFUNCTION(Client, Reliable)`
- L114 _protected prototype_ `void ClientExitConversation(const FConversationParticipants& InParticipants);` — `UFUNCTION(Client, Reliable)`
- L118 _protected prototype_ `void OnRep_ConversationsActive(int32 OldConversationsActive);` — `UFUNCTION()`
- L120 _protected prototype_ `virtual void OnEnterConversationState();`
- L121 _protected prototype_ `virtual void OnLeaveConversationState();`
- L122 _protected prototype_ `virtual void OnConversationUpdated(const FClientConversationMessagePayload& Message);`
- L124 _protected prototype_ `virtual void OnClientStartConversation(const FConversationParticipants& InParticipants);`
- L125 _protected prototype_ `virtual void OnClientExitConversation(const FConversationParticipants& InParticipants);`
- L128 _protected prototype_ `virtual void OnServerConversationStarted(UConversationInstance* Conversation, FGameplayTag AsParticipant);`
- L129 _protected prototype_ `virtual void OnServerConversationEnded(UConversationInstance* Conversation);`
- L133 _protected function_ `UConversationInstance* GetCurrentConversationForAuthority() const`
- L134 _protected function_ `const TArray<UConversationInstance*>& GetConversationsForAuthority() const`
- L140 _public function_ `int32 GetConversationsActive() const` — The number of conversations active.  A given conversationalist might be in multiple conversations at once. e.g. Multiple players "talking" to the same NPC in a multiplayer game.
- L143 _public function_ `const FClientConversationMessagePayload& GetLastMessage() const` — A cached version of the last conversation message payload data recieved.
- L146 _public function_ `const int32 GetLastMessageIndex() const` — Gets the last message index recieved, this is just a monotomically increasing number each time we get a new message.
- L148 _public function_ `bool GetIsFirstConversationUpdateBroadcasted() const`
- L153 _private member_ `int32 ConversationsActive = 0;` — `UPROPERTY(Replicated, ReplicatedUsing=OnRep_ConversationsActive)`
- L157 _private member_ `FConversationMemory ParticipantMemory;`
- L162 _private member_ `TObjectPtr<UConversationInstance> Auth_CurrentConversation;` — `UPROPERTY()`
- L165 _private member_ `TArray<TObjectPtr<UConversationInstance>> Auth_Conversations;` — `UPROPERTY()`
- L168 _private member_ `FClientConversationMessagePayload LastMessage;` — `UPROPERTY()`
- L170 _private member_ `int32 MessageIndex = 0;`
- L172 _private member_ `bool bIsFirstConversationUpdateBroadcasted = false;`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`
- L15 _delegate_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversationStatusChanged, bool, bIsInConversation);`
- L15 _prototype_ `DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversationStatusChanged, bool, bIsInConversation);`
- L30 _delegate_ `DECLARE_EVENT_OneParam(UConversationParticipantComponent, FConversationStatusChangedEvent, bool );` — Client and server notification of the conversation starting or ending
- L33 _delegate_ `DECLARE_EVENT(UConversationParticipantComponent, FConversationStartedEvent);`
- L36 _delegate_ `DECLARE_EVENT_OneParam(UConversationParticipantComponent, FConversationUpdatedEvent, const FClientConversationMessagePayload& );`
- L39 _delegate_ `DECLARE_EVENT_TwoParams(UConversationParticipantComponent, FConversationTaskChoiceDataUpdatedEvent, const FConversationNodeHandle& , const FClientConversationOptionEntry& );`
- L68 _delegate_ `DECLARE_MULTICAST_DELEGATE_OneParam(FParticipantReadyToConverse, UConversationParticipantComponent*);`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationRegistry.h` (Public)


#### struct `FNetSerializeScriptStructCache_ConvVersion`  
`struct FNetSerializeScriptStructCache_ConvVersion`  
_L23-37_
- reflection: `USTRUCT()`
- desc: Container for safely replicating  script struct references (constrained to a specified parent struct)
- L27 _public prototype_ `void InitForType(UScriptStruct* InScriptStruct);`
- L30 _public prototype_ `bool NetSerialize(FArchive& Ar, UScriptStruct*& Struct);` — Serializes reference to given script struct (must be in the cache)
- L33 _public member_ `TMap<TObjectPtr<UScriptStruct>, int32> ScriptStructsToIndex;` — `UPROPERTY()`
- L36 _public member_ `TArray<TObjectPtr<UScriptStruct>> IndexToScriptStructs;` — `UPROPERTY()`

#### struct `FConversationsHandle`  
`struct FConversationsHandle : public TSharedFromThis<FConversationsHandle>`  
_L45-64_
- inherits: `TSharedFromThis<FConversationsHandle>`
- desc: These handles are issued when someone requests a conversation entry point be streamed in. As long as this handle remains active, we were continue to keep it keep those elements streamed in, as well as if new game feature plugins activate, we will stream in additional assets or let previous ones expire.
- L47 _public prototype_ `static TSharedPtr<FConversationsHandle> Create(const UConversationRegistry* InOwningRegistry, const TSharedPtr<FStreamableHandle>& InStreamableHandle, const TArray<FGameplayTag>& InEntryTags);`
- L54 _public prototype_ `FConversationsHandle(FPrivateToken, UConversationRegistry* InOwningRegistry, const TSharedPtr<FStreamableHandle>& InStreamableHandle, const TArray<FGameplayTag>& InEntryTags);`
- L57 _private prototype_ `void Initialize();`
- L58 _private prototype_ `void HandleAvailableConversationsChanged();`
- L61 _private member_ `TSharedPtr<FStreamableHandle> StreamableHandle;`
- L62 _private member_ `TArray<FGameplayTag> ConversationEntryTags;`
- L63 _private member_ `TWeakObjectPtr<UConversationRegistry> OwningRegistryPtr;`

#### struct `FConversationsHandle::FPrivateToken`  
`struct FPrivateToken`  
_L51-51_
- desc: Private token only allows members or friends to call MakeShared
- L51 _public prototype_ `struct FPrivateToken` — Private token only allows members or friends to call MakeShared

#### class `UConversationRegistry`  
`class UConversationRegistry : public UWorldSubsystem, public IGameFeatureStateChangeObserver`  
_L73-134_
- reflection: `UCLASS(MinimalAPI)`
- inherits: `UWorldSubsystem,IGameFeatureStateChangeObserver`
- desc: A registry that can answer questions about all available dialogue assets
- L78 _public prototype_ `UConversationRegistry();`
- L80 _public prototype_ `static UConversationRegistry* GetFromWorld(const UWorld* World);`
- L83 _public prototype_ `virtual void Initialize(FSubsystemCollectionBase& Collection) override;` — UWorldSubsystem Begin
- L84 _public prototype_ `virtual void Deinitialize() override;`
- L87 _public prototype_ `UConversationNode* GetRuntimeNodeFromGUID(const FGuid& NodeGUID, const UConversationDatabase* Graph = nullptr) const;`
- L88 _public prototype_ `UConversationNode* TryGetRuntimeNodeFromGUID(const FGuid& NodeGUID, const UConversationDatabase* Graph = nullptr) const;`
- L89 _public prototype_ `TArray<FGuid> GetEntryPointGUIDs(const FGameplayTag& EntryPoint) const;`
- L91 _public prototype_ `TArray<FGuid> GetOutputLinkGUIDs(const FGameplayTag& EntryPoint) const;`
- L92 _public prototype_ `TArray<FGuid> GetOutputLinkGUIDs(const FGuid& SourceGUID) const;`
- L93 _public prototype_ `TArray<FGuid> GetOutputLinkGUIDs(const TArray<FGuid>& SourceGUIDs) const;`
- L94 _public prototype_ `TArray<FGuid> GetOutputLinkGUIDs(const UConversationDatabase* Graph, const FGameplayTag& EntryPoint, const FString& EntryIdentifier) const;`
- L95 _public prototype_ `TArray<FGuid> GetOutputLinkGUIDs(const UConversationDatabase* Graph, const FGuid& SourceGUID) const;`
- L97 _public prototype_ `TSharedPtr<FConversationsHandle> LoadConversationsFor(const FGameplayTag& ConversationEntryTag) const;`
- L98 _public prototype_ `TSharedPtr<FConversationsHandle> LoadConversationsFor(const TArray<FGameplayTag>& ConversationEntryTags) const;`
- L100 _public prototype_ `TArray<FPrimaryAssetId> GetPrimaryAssetIdsForEntryPoint(FGameplayTag EntryPoint) const;`
- L103 _public prototype_ `TArray<FGameplayTag> GetLinkedExitConversationEntryTags(const UConversationDatabase* ConversationDatabase) const;` — If a conversation database links to other conversaton assets, the tags of those conversations can be obtained here
- L106 _public member_ `FNetSerializeScriptStructCache_ConvVersion ConversationChoiceDataStructCache;` — `UPROPERTY(Transient)`
- L108 _public member_ `FAvailableConversationsChangedEvent AvailableConversationsChanged;`
- L110 _public prototype_ `void FlushBuildDependenciesGraph();`
- L111 _public prototype_ `void SetWaitDependenciesGraphToFlush(bool bWaitToFlush);`
- L114 _private prototype_ `UConversationDatabase* GetConversationFromNodeGUID(const FGuid& NodeGUID) const;`
- L116 _private prototype_ `void BuildDependenciesGraph();`
- L117 _private prototype_ `void GetAllDependenciesForConversation(const FSoftObjectPath& Parent, TSet<FSoftObjectPath>& OutConversationsToLoad) const;`
- L119 _private prototype_ `void GameFeatureStateModified();`
- L121 _private prototype_ `virtual void OnGameFeatureActivated(const UGameFeatureData* GameFeatureData, const FString& PluginURL) override;`
- L123 _private prototype_ `virtual void OnGameFeatureDeactivating(const UGameFeatureData* GameFeatureData, FGameFeatureDeactivatingContext& Context, const FString& PluginURL) override;`
- L126 _private member_ `TMap<FSoftObjectPath, TArray<FSoftObjectPath>> RuntimeDependencyGraph;`
- L127 _private member_ `TMap<FGameplayTag, TArray<FSoftObjectPath>> EntryTagToConversations;`
- L128 _private member_ `TMap<FGameplayTag, TArray<FGuid>> EntryTagToEntryList;`
- L129 _private member_ `TMap<FGuid, FSoftObjectPath> NodeGuidToConversation;`
- L132 _private member_ `bool bDependenciesBuilt = false;`
- L133 _private member_ `bool bWaitForDependenciesGraphFlush = false;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`
- L67 _delegate_ `DECLARE_MULTICAST_DELEGATE(FAvailableConversationsChangedEvent);`
- L67 _prototype_ `DECLARE_MULTICAST_DELEGATE(FAvailableConversationsChangedEvent);`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationRequirementNode.h` (Public)


#### enum `EConversationRequirementResult`  
`enum class EConversationRequirementResult : uint8`  
_L14-22_
- reflection: `UENUM(BlueprintType)`
- desc: The requirement result.
- L17 _public enumerator_ `Passed` — This option is available
- L19 _public enumerator_ `FailedButVisible` — This option is not available, but we should tell the player about it still.
- L21 _public enumerator_ `FailedAndHidden` — This option is not available, and we should keep it hidden.

#### class `UConversationRequirementNode`  
`class UConversationRequirementNode : public UConversationSubNode`  
_L31-38_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UConversationSubNode`
- desc: A requirement is placed on a parent node to control whether or not it can be activated (when a link to the parent node is being evaluated, the requirement will be asked if it is satisfied or not)
- L37 _public prototype_ `EConversationRequirementResult IsRequirementSatisfied(const FConversationContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`
- L24 _prototype_ `EConversationRequirementResult MergeRequirements(EConversationRequirementResult CurrentResult, EConversationRequirementResult MergeResult);`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationSettings.h` (Public)


#### class `UConversationSettings`  
`class UConversationSettings : public UDeveloperSettings`  
_L16-30_
- reflection: `UCLASS(MinimalAPI, Config = Game, DefaultConfig, meta = (DisplayName = "Conversation"))`
- inherits: `UDeveloperSettings`
- desc: Conversation settings.
- L22 _public prototype_ `UConversationSettings();`
- L24 _public function_ `UClass* GetConversationInstanceClass() const`
- L29 _protected member_ `TSoftClassPtr<UConversationInstance> ConversationInstanceClass;` — `UPROPERTY(config, EditAnywhere, Category=Conversation)`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationSideEffectNode.h` (Public)


#### class `UConversationSideEffectNode`  
`class UConversationSideEffectNode : public UConversationSubNode`  
_L20-34_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UConversationSubNode`
- desc: Side effects are actions that are performed just after a task is executed (this allows state-altering or cosmetic actions to be mixed in to other nodes) When a task executes on the server, it replicates to the client that it executed and to then execute any client side effects that may be necessary for that task.
- L26 _public prototype_ `void CauseSideEffect(const FConversationContext& Context) const;` — Called by the client and server code executes the side effect.
- L30 _protected prototype_ `void ServerCauseSideEffect(const FConversationContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly)`
- L33 _protected prototype_ `void ClientCauseSideEffect(const FConversationContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic)`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationSubNode.h` (Public)


#### class `UConversationSubNode`  
`class UConversationSubNode : public UConversationNode`  
_L12-15_
- reflection: `UCLASS(MinimalAPI, Abstract)`
- inherits: `UConversationNode`
- desc: @TODO: CONVERSATION: Comment me

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationTaskNode.h` (Public)


#### enum `EConversationNodeBranchOrder`  
`enum class EConversationNodeBranchOrder : uint8`  
_L19-24_
- reflection: `UENUM()`
- L21 _public enumerator_ `Random`
- L22 _public enumerator_ `LeftToRight`
- L23 _public enumerator_ `RightToLeft`

#### class `UConversationTaskNode`  
`class UConversationTaskNode : public UConversationNodeWithLinks`  
_L51-129_
- reflection: `UCLASS(MinimalAPI, Abstract, Blueprintable)`
- inherits: `UConversationNodeWithLinks`
- desc: The ConversationTaskNode is the basis of any task in the conversation graph, that task may be as simple as saying some text to the user, and providing some choices. However more complex tasks can fire off quests, can spawn actors, pretty much any arbitrary thing you want. The conversation system is less about just a dialogue tree, and more about a graph of actions the NPC can take, and choices they can provide to the player.
- L58 _public member_ `TArray<TObjectPtr<UConversationSubNode>> SubNodes;` — `UPROPERTY(BlueprintReadOnly, Category = Conversation)` — Requirements and side effects
- L63 _public member_ `uint32 bHasRequirements : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Conversation)` — EDITOR ONLY VISUALS: Does this task internally have requirements?
- L67 _public member_ `uint32 bHasDynamicChoices : 1;` — `UPROPERTY(EditDefaultsOnly, Category=Conversation)` — EDITOR ONLY VISUALS: Does this task generate dynamic choices?
- L72 _public member_ `bool bIgnoreRequirementsWhileAdvancingConversations = false;` — `UPROPERTY(EditDefaultsOnly, Category = "UI")` — This setting is designed for requirements that only matter when option is generated
- L78 _public member_ `EConversationNodeBranchOrder BranchOrder = EConversationNodeBranchOrder::Random;` — `UPROPERTY(EditInstanceOnly, Category=Conversation, AdvancedDisplay)` — Defines the order in which branches are selected when the conversation advanced automatically and the user did not choose a specific branch
- L82 _public prototype_ `bool GetNodeBodyColor(FLinearColor& BodyColor) const;` — `UFUNCTION(BlueprintNativeEvent)`
- L86 _public prototype_ `FConversationTaskResult ExecuteTaskNodeWithSideEffects(const FConversationContext& Context) const;` — @TODO: CONVERSATION: Comment me
- L90 _public prototype_ `virtual FName GetNodeIconName() const override;`
- L97 _public prototype_ `EConversationRequirementResult CheckRequirements(const FConversationContext& InContext) const;` — Returns the highest priority EConversationRequirementResult, so Passed, having the least priority and FailedHidden having the highest priority.
- L99 _public prototype_ `static void GenerateChoicesForDestinations(FConversationBranchPointBuilder& BranchBuilder, const FConversationContext& InContext, const TArray<FGuid>& CandidateDestinations);`
- L103 _public prototype_ `virtual void GenerateNextChoices(FConversationBranchPointBuilder& BranchBuilder, const FConversationContext& Context) const;` — Generates this task nodes' next possible conversation chioces. Default behavior handles finding static destination node choices and dynamic choices generated by the node, but this can be overriden if more custom behavior is desired for a specific task node.
- L107 _protected prototype_ `EConversationRequirementResult IsRequirementSatisfied(const FConversationContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly)`
- L110 _protected prototype_ `FConversationTaskResult ExecuteTaskNode(const FConversationContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly)`
- L113 _protected prototype_ `void ExecuteClientEffects(const FConversationContext& Context) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic)`
- L116 _protected prototype_ `void GatherStaticExtraData(const FConversationContext& Context, TArray<FConversationNodeParameterPair>& InOutExtraData) const;` — `UFUNCTION(BlueprintNativeEvent, BlueprintAuthorityOnly)`
- L118 _protected prototype_ `virtual void GatherChoices(FConversationBranchPointBuilder& BranchBuilder, const FConversationContext& Context) const;`
- L120 _protected prototype_ `virtual void GatherStaticChoices(FConversationBranchPointBuilder& BranchBuilder, const FConversationContext& Context) const;`
- L121 _protected prototype_ `virtual void GatherDynamicChoices(FConversationBranchPointBuilder& BranchBuilder, const FConversationContext& Context) const;`
- L127 _protected member_ `FLinearColor DefaultNodeBodyColor = FLinearColor::White;` — `UPROPERTY(EditDefaultsOnly, Category=Description)` — Default color of the node.

#### Free symbols / members of external scopes

- L9 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`

### `Plugins/Experimental/CommonConversation/Source/CommonConversationRuntime/Public/ConversationTypes.h` (Public)


#### struct `FConversationChoiceData`  
`struct FConversationChoiceData`  
_L19-31_
- reflection: `USTRUCT()`
- L24 _public function_ `FConversationChoiceData()`
- L25 _public prototype_ `virtual ~FConversationChoiceData() = default;`
- L27 _public function_ `virtual UScriptStruct* GetScriptStruct() const`

#### struct `FConversationChoiceDataHandle`  
`struct FConversationChoiceDataHandle`  
_L43-136_
- reflection: `USTRUCT()`
- L49 _public member_ `TArray<TSharedPtr<FConversationChoiceData>, TInlineAllocator<1> > Data;` — Raw storage of target data, do not modify this directly
- L52 _public function_ `FConversationChoiceDataHandle()`
- L53 _public function_ `FConversationChoiceDataHandle(FConversationChoiceData* DataPtr)`
- L58 _public function_ `FConversationChoiceDataHandle(FConversationChoiceDataHandle&& Other) : Data(MoveTemp(Other.Data))`
- L59 _public function_ `FConversationChoiceDataHandle(const FConversationChoiceDataHandle& Other) : Data(Other.Data)`
- L61 _public function_ `FConversationChoiceDataHandle& operator=(FConversationChoiceDataHandle&& Other)`
- L62 _public function_ `FConversationChoiceDataHandle& operator=(const FConversationChoiceDataHandle& Other)`
- L65 _public function_ `void Clear()` — Resets handle to have no targets
- L71 _public function_ `int32 Num() const` — Returns number of target data, not number of actors/targets as target data may contain multiple actors
- L77 _public function_ `bool IsValid(int32 Index) const` — Returns true if there are any valid targets
- L83 _public function_ `const FConversationChoiceData* Get(int32 Index) const` — Returns data at index, or nullptr if invalid
- L89 _public function_ `FConversationChoiceData* Get(int32 Index)` — Returns data at index, or nullptr if invalid
- L95 _public function_ `void Add(FConversationChoiceData* DataPtr)` — Adds a new target data to handle, it must have been created with new
- L101 _public function_ `void Append(const FConversationChoiceDataHandle& OtherHandle)` — Does a shallow copy of target data from one handle to another
- L107 _public prototype_ `bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);` — Serialize for networking, handles polymorphism
- L110 _public function_ `bool operator==(const FConversationChoiceDataHandle& Other) const` — Comparison operator
- L132 _public function_ `bool operator!=(const FConversationChoiceDataHandle& Other) const` — Comparison operator

#### struct `TStructOpsTypeTraits`  
`template<> struct TStructOpsTypeTraits<FConversationChoiceDataHandle> : public TStructOpsTypeTraitsBase2<FConversationChoiceDataHandle>`  
_L139-147_
- inherits: `TStructOpsTypeTraitsBase2<FConversationChoiceDataHandle>`

#### enum `TStructOpsTypeTraits::(anonymous)`  
``  
_L142-146_

#### struct `FConversationParticipantEntry`  
`struct FConversationParticipantEntry`  
_L153-170_
- reflection: `USTRUCT(BlueprintType)`
- L160 _public member_ `TObjectPtr<AActor> Actor = nullptr;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L163 _public member_ `FGameplayTag ParticipantID;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L166 _public function_ `template<class TParticipantComponentClass = UConversationParticipantComponent> TParticipantComponentClass* GetParticipantComponent() const`

#### struct `FConversationParticipants`  
`struct FConversationParticipants`  
_L176-191_
- reflection: `USTRUCT(BlueprintType)`
- L182 _public prototype_ `const FConversationParticipantEntry* GetParticipant(FGameplayTag ParticipantID) const;`
- L184 _public prototype_ `UConversationParticipantComponent* GetParticipantComponent(FGameplayTag ParticipantID) const;`
- L186 _public prototype_ `bool Contains(AActor* PotentialParticipant) const;`
- L190 _public member_ `TArray<FConversationParticipantEntry> List;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`

#### struct `FConversationNodeParameterPair`  
`struct FConversationNodeParameterPair`  
_L196-208_
- reflection: `USTRUCT(BlueprintType)`
- L200 _public function_ `FConversationNodeParameterPair()`
- L201 _public function_ `FConversationNodeParameterPair(const FString& InName, const FString& InValue) : Name(InName), Value(InValue)`
- L204 _public member_ `FString Name;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Conversation)`
- L207 _public member_ `FString Value;` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Conversation)`

#### struct `FConversationChoiceReference`  
`struct FConversationChoiceReference`  
_L227-252_
- reflection: `USTRUCT(BlueprintType)`
- desc: The conversation choice reference is the closest thing there is to a link at runtime for a choice. Choices always map to a Task node, which is the NodeReference.  However some tasks could potentially dynamically generate several possible choices.  In that case they would do so with a unique set of NodeParameters.  These would allow one task, say, "Sell N Items", where it's one task offering 3 different items for sale, and so it needs to match-up those choices with what the user chooses later. the NodeParameters would contain the dynamic data generated at runtime signifying for the server what to choose. Luckily the user does not need to guard against cheating clients.  Any dynamically generated choice is remembered by the server - so any choice selected dynamically can be verified by the server as one it offered to the user.
- L232 _public member_ `static const FConversationChoiceReference Empty;`
- L234 _public function_ `FConversationChoiceReference()`
- L235 _public function_ `FConversationChoiceReference(const FGuid& InNodeGUID) : NodeReference(InNodeGUID)`
- L239 _public member_ `FConversationNodeHandle NodeReference;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)` — This is the node that we're targeting with our choice.
- L247 _public member_ `TArray<FConversationNodeParameterPair> NodeParameters;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)` — These are the parameters required by that node to be activated.  The same node could potentially handle several dynamic choices it provides, so these parameters are used to uniquely identify the choice when the client responds to the server.
- L249 _public function_ `bool IsValid() const`
- L251 _public prototype_ `FString ToString() const;`

#### struct `FAdvanceConversationRequest`  
`struct FAdvanceConversationRequest`  
_L260-280_
- reflection: `USTRUCT(BlueprintType)`
- L265 _public member_ `static const FAdvanceConversationRequest Any;`
- L267 _public function_ `FAdvanceConversationRequest()`
- L268 _public function_ `FAdvanceConversationRequest(const FConversationChoiceReference& InChoice) : Choice(InChoice)`
- L271 _public prototype_ `FString ToString() const;`
- L275 _public member_ `FConversationChoiceReference Choice;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L279 _public member_ `TArray<FConversationNodeParameterPair> UserParameters;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)` — @TODO: CONVERSATION: Not currently supported, TODO.

#### enum `EConversationChoiceType`  
`enum class EConversationChoiceType : uint8`  
_L288-296_
- reflection: `UENUM()`
- L293 _public enumerator_ `ServerOnly` — ServerOnly choices are the choices the user shouldn't see and are filtered from the client.
- L294 _public enumerator_ `UserChoiceAvailable`
- L295 _public enumerator_ `UserChoiceUnavailable`

#### struct `FClientConversationOptionEntry`  
`struct FClientConversationOptionEntry`  
_L302-366_
- reflection: `USTRUCT(BlueprintType)`
- desc: The conversation option entry is what we send to the client, one entry per choice.
- L309 _public member_ `FText ChoiceText;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L312 _public member_ `FGameplayTagContainer ChoiceTags;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L315 _public member_ `EConversationChoiceType ChoiceType = EConversationChoiceType::ServerOnly;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L318 _public member_ `FConversationChoiceReference ChoiceReference;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L326 _public member_ `TArray<FConversationNodeParameterPair> ExtraData;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)` — Occasionally a choice might need to send down metadata that's entirely extra. It's just bonus information for the client to do things like show more information in the UI.  This information is not used on the return to the server to make the choice.
- L333 _public function_ `template<class TConversationNodeClass = UConversationNode> const TConversationNodeClass* TryToResolveChoiceNode(const FConversationContext& Context) const` — Tries to resolve the node, this may fail, the guid might be bogus, or the node might not be in memory.
- L339 _public function_ `template<class TConversationNodeClass = UConversationNode> const TConversationNodeClass* TryToResolveChoiceNode_Slow(UWorld* InWorld, const UConversationDatabase* Graph = nullptr) const`
- L344 _public function_ `void SetChoiceAvailable(bool bIsAvailable)`
- L345 _public function_ `bool IsChoiceAvailable() const`
- L347 _public function_ `const FConversationChoiceReference& ToChoiceReference() const`
- L348 _public prototype_ `FAdvanceConversationRequest ToAdvanceConversationRequest(const TArray<FConversationNodeParameterPair>& InUserParameters = TArray<FConversationNodeParameterPair>()) const;`
- L350 _public function_ `FString GetChoiceDataForKey(const FString& ParamKey) const`

#### struct `FConversationBranchPoint`  
`struct FConversationBranchPoint`  
_L385-401_
- reflection: `USTRUCT()`
- desc: You can think of the FConversationBranchPoint as the owner of FClientConversationOptionEntry. We don't send this one to the client though, we store temporary state here so that when a user picks a choice there may be other things we need to know or store for actions we need to take due to the user picking this choice.  For example, some choices may introduce needing to 'push' a new scope so that when that subtree terminates we return to the previous point, like a stack.  There's no reason the client needs to understand this, so we just store it here.
- L390 _public function_ `FConversationBranchPoint()`
- L391 _public function_ `FConversationBranchPoint(const FClientConversationOptionEntry& InClientChoice) : ClientChoice(InClientChoice)`
- L392 _public function_ `FConversationBranchPoint(FClientConversationOptionEntry&& InClientChoice) : ClientChoice(MoveTemp(InClientChoice))`
- L394 _public function_ `const FConversationNodeHandle& GetNodeHandle() const`
- L397 _public member_ `TArray<FConversationNodeHandle> ReturnScopeStack;` — `UPROPERTY()`
- L400 _public member_ `FClientConversationOptionEntry ClientChoice;` — `UPROPERTY()`

#### struct `FConversationBranchPointBuilder`  
`struct FConversationBranchPointBuilder : public FNoncopyable`  
_L405-414_
- inherits: `FNoncopyable`
- L407 _public prototype_ `void AddChoice(const FConversationContext& InContext, FClientConversationOptionEntry&& InChoice);`
- L409 _public function_ `int32 Num() const`
- L410 _public function_ `const TArray<FConversationBranchPoint>& GetBranches() const`
- L413 _private member_ `TArray<FConversationBranchPoint> BranchPoints;`

#### struct `FClientConversationMessage`  
`struct FClientConversationMessage`  
_L422-441_
- reflection: `USTRUCT(BlueprintType)`
- L428 _public member_ `FGameplayTag SpeakerID;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L431 _public member_ `FText ParticipantDisplayName;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L434 _public member_ `FText Text;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L438 _public member_ `TArray<FConversationNodeParameterPair> MetadataParameters;` — `UPROPERTY(BlueprintReadWrite, Category = Conversation)` — Additional metadata for this message (e.g. Emotion: "Angry"/"Happy")
- L440 _public function_ `FString ToString() const`

#### struct `FClientConversationMessagePayload`  
`struct FClientConversationMessagePayload`  
_L449-468_
- reflection: `USTRUCT(BlueprintType)`
- L456 _public member_ `FClientConversationMessage Message;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L459 _public member_ `FConversationParticipants Participants;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L462 _public member_ `FConversationNodeHandle CurrentNode;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L465 _public member_ `TArray<FClientConversationOptionEntry> Options;` — `UPROPERTY(BlueprintReadWrite, Category=Conversation)`
- L467 _public function_ `FString ToString() const`

#### Free symbols / members of external scopes

- L10 _macro_ `#define UE_API COMMONCONVERSATIONRUNTIME_API`
- L143 _enumerator_ `WithCopy = true` (scope `TStructOpsTypeTraits::__anonb2a1baa20103`) — Necessary so that TSharedPtr<FConversationChoiceData> Data is copied around
- L144 _enumerator_ `WithNetSerializer = true` (scope `TStructOpsTypeTraits::__anonb2a1baa20103`)
- L145 _enumerator_ `WithIdenticalViaEquality = true` (scope `TStructOpsTypeTraits::__anonb2a1baa20103`)
- L210 _function_ `inline bool operator==(const FConversationNodeParameterPair& Lhs, const FConversationNodeParameterPair& Rhs)`
- L211 _function_ `inline bool operator!=(const FConversationNodeParameterPair& Lhs, const FConversationNodeParameterPair& Rhs)`
- L254 _function_ `inline bool operator==(const FConversationChoiceReference& Lhs, const FConversationChoiceReference& Rhs)`
- L255 _function_ `inline bool operator!=(const FConversationChoiceReference& Lhs, const FConversationChoiceReference& Rhs)`
- L352 _function_ `const FConversationNodeParameterPair* NodeParameter = ChoiceReference.NodeParameters.FindByPredicate([=](const FConversationNodeParameterPair& Pair) { return Pair.Name.Equals(ParamKey, ESearchCase::IgnoreCase); });` (scope `FClientConversationOptionEntry::GetChoiceDataForKey`)
- L358 _function_ `const FConversationNodeParameterPair* ExtraDataParameter = ExtraData.FindByPredicate([=](const FConversationNodeParameterPair& Pair) { return Pair.Name.Equals(ParamKey, ESearchCase::IgnoreCase); });` (scope `FClientConversationOptionEntry::GetChoiceDataForKey`)
- L368 _function_ `inline bool operator==(const FClientConversationOptionEntry& Lhs, const FClientConversationOptionEntry& Rhs)`
- L369 _function_ `inline bool operator!=(const FClientConversationOptionEntry& Lhs, const FClientConversationOptionEntry& Rhs)`
- L371 _function_ `inline bool operator==(const FClientConversationOptionEntry& Lhs, const FConversationChoiceReference& Rhs)`
- L372 _function_ `inline bool operator!=(const FClientConversationOptionEntry& Lhs, const FConversationChoiceReference& Rhs)`
