# Plugins / LearningAgentsTrainingEditor

- module root: `Plugins/Experimental/LearningAgents/Source/LearningAgentsTrainingEditor`
- headers: 6; symbols: 65
- symbol kinds: class=7, macro=5, member=20, prototype=33
- DynamicallyLoadedModuleNames: 
- PrivateDependencyModuleNames: CoreUObject, EditorStyle, Engine, Learning, LearningAgents, LearningAgentsTraining, LearningTraining, PropertyEditor, Slate, SlateCore, UMG, UnrealEd
- PublicDependencyModuleNames: Core

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTrainingEditor/Public/LearningAgentsDepthMapVisualizer.h` (Public)


#### class `ULearningAgentsDepthMapWidget`  
`class ULearningAgentsDepthMapWidget : public UUserWidget`  
_L14-29_
- reflection: `UCLASS()`
- inherits: `UUserWidget`
- L19 _public prototype_ `void SetDepthValues(const TArray<float>& InDepthValues);`
- L20 _public prototype_ `void InitializeView(FVector2D RenderSize, FVector2D RenderPosition, int32 DMapHeight, int32 DMapWidth);`
- L23 _private member_ `TArray<float> DepthValues;`
- L25 _private member_ `TObjectPtr<UCanvasRenderTarget2D> DepthMapRenderer;`
- L28 _private prototype_ `void OnCanvasRenderTargetUpdate(UCanvas* Canvas, int32 Width, int32 Height);` — `UFUNCTION()`

#### class `ULearningAgentsDepthMapVisualizerComponent`  
`class ULearningAgentsDepthMapVisualizerComponent : public UActorComponent`  
_L32-53_
- reflection: `UCLASS(Blueprintable, ClassGroup = (LearningAgents), meta = (BlueprintSpawnableComponent))`
- inherits: `UActorComponent`
- L37 _public prototype_ `ULearningAgentsDepthMapVisualizerComponent();`
- L40 _public member_ `FVector2D RenderSize = FVector2D(512, 512);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LearningAgents")`
- L43 _public member_ `FVector2D RenderPosition = FVector2D(100, 100);` — `UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "LearningAgents")`
- L45 _public prototype_ `virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;`
- L48 _protected prototype_ `virtual void BeginPlay() override;`
- L51 _private member_ `TObjectPtr<ULearningAgentsDepthMapComponent> DepthMapComp;`
- L52 _private member_ `TObjectPtr<ULearningAgentsDepthMapWidget> Widget;`

#### Free symbols / members of external scopes

- L11 _macro_ `#define UE_API LEARNINGAGENTSTRAININGEDITOR_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTrainingEditor/Public/LearningAgentsFlowMatchingTrainerEditor.h` (Public)


#### class `ALearningAgentsFlowMatchingTrainerEditor`  
`class ALearningAgentsFlowMatchingTrainerEditor : public ALearningAgentsTrainerEditorBase`  
_L18-45_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `ALearningAgentsTrainerEditorBase`
- desc: Editor callable flow matching learning trainer.
- L23 _public prototype_ `ALearningAgentsFlowMatchingTrainerEditor();`
- L25 _public prototype_ `virtual void StartTraining() override;`
- L27 _public prototype_ `virtual void StopTraining() override;`
- L29 _public prototype_ `virtual bool IsTraining() const override;`
- L31 _public prototype_ `virtual void StartExport(UE::Learning::ETrainerExportFlags Flags) override;`
- L34 _public member_ `TObjectPtr<ULearningAgentsFlowMatchingTrainer> LearningAgentsFlowMatchingTrainer;` — `UPROPERTY(BlueprintReadWrite, Category = "LearningAgents")`
- L37 _public member_ `FLearningAgentsFlowMatchingTrainerSettings FlowMatchingTrainerSettings;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")`
- L40 _public member_ `FLearningAgentsFlowMatchingTrainerTrainingSettings FlowMatchingTrainerTrainingSettings;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")`
- L43 _public member_ `FLearningAgentsTrainerProcessSettings FlowMatchingTrainerPathSettings;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEARNINGAGENTSTRAININGEDITOR_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTrainingEditor/Public/LearningAgentsImitationTrainerEditor.h` (Public)


#### class `ALearningAgentsImitationTrainerEditor`  
`class ALearningAgentsImitationTrainerEditor : public ALearningAgentsTrainerEditorBase`  
_L17-45_
- reflection: `UCLASS(BlueprintType, Blueprintable)`
- inherits: `ALearningAgentsTrainerEditorBase`
- desc: Editor callable imitation learning trainer.
- L22 _public prototype_ `ALearningAgentsImitationTrainerEditor();`
- L25 _public prototype_ `virtual void StartTraining() override;` — Start training.
- L28 _public prototype_ `virtual void StopTraining() override;` — Stop training.
- L30 _public prototype_ `virtual bool IsTraining() const override;`
- L32 _public prototype_ `virtual void StartExport(UE::Learning::ETrainerExportFlags Flags) override;`
- L35 _public member_ `TObjectPtr<ULearningAgentsImitationTrainer> LearningAgentsImitationTrainer;` — `UPROPERTY(BlueprintReadWrite, Category = "LearningAgents")`
- L38 _public member_ `FLearningAgentsImitationTrainerSettings ImitationTrainerSettings;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")`
- L41 _public member_ `FLearningAgentsImitationTrainerTrainingSettings ImitationTrainerTrainingSettings;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")`
- L44 _public member_ `FLearningAgentsTrainerProcessSettings ImitationTrainerPathSettings;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")`

#### Free symbols / members of external scopes

- L13 _macro_ `#define UE_API LEARNINGAGENTSTRAININGEDITOR_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTrainingEditor/Public/LearningAgentsTrainerEditorBase.h` (Public)


#### class `ALearningAgentsTrainerEditorBase`  
`class ALearningAgentsTrainerEditorBase : public AActor`  
_L18-58_
- reflection: `UCLASS(Abstract)`
- inherits: `AActor`
- desc: Editor callable imitation learning trainer.
- L23 _public prototype_ `ALearningAgentsTrainerEditorBase();`
- L27 _public prototype_ `ULearningAgentsManagerListener* SetupTraining();` — `UFUNCTION(BlueprintImplementableEvent, Category = "LearningAgents", meta = (ReturnDisplayName = "Trainer"))` — Setup the imitation trainer with necessary components in blueprints.
- L30 _public prototype_ `virtual void StartTraining() PURE_VIRTUAL(ALearningAgentsTrainerEditorBase::StartTraining);` — Start training.
- L33 _public prototype_ `virtual void StopTraining() PURE_VIRTUAL(ALearningAgentsTrainerEditorBase::StopTraining);` — Stop training.
- L36 _public prototype_ `virtual bool IsTraining() const PURE_VIRTUAL(ALearningAgentsTrainerEditorBase::IsTraining, return false;);` — Is training.
- L40 _public prototype_ `FLearningAgentsCommunicator MakeFileCommunicator(FDirectoryPath EditorIntermediateRelativePath);` — `UFUNCTION(BlueprintCallable, Category = "LearningAgents")` — Make File communicator to file training materials for external training.
- L43 _public prototype_ `virtual void StartExport(UE::Learning::ETrainerExportFlags Flags) PURE_VIRTUAL(ALearningAgentsTrainerEditorBase::StartExport);` — Export training materials to file with the given export flags. No training loop is started.
- L46 _public member_ `UE::Learning::ETrainerExportFlags ExportFlags = UE::Learning::ETrainerExportFlags::All;` — The export flags used by MakeFileCommunicator.
- L49 _public member_ `TSharedPtr<UE::Learning::FFileTrainer> FileTrainer;` — The file trainer created by MakeFileCommunicator, used by StartExport.
- L51 _public member_ `float TrainingTickInterval = 0.0f;`
- L54 _public member_ `TObjectPtr<ULearningAgentsManager> LearningAgentsManager;` — `UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "LearningAgents")`
- L57 _public member_ `TObjectPtr<ULearningAgentsRecording> Recording;` — `UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "LearningAgents")`

#### Free symbols / members of external scopes

- L14 _macro_ `#define UE_API LEARNINGAGENTSTRAININGEDITOR_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTrainingEditor/Public/LearningAgentsTrainerEditorDetails.h` (Public)


#### class `FLearningAgentsTrainerEditorDetails`  
`class FLearningAgentsTrainerEditorDetails : public IDetailCustomization`  
_L11-25_
- inherits: `IDetailCustomization`
- desc: Details customization for the flow matching learning trainer
- L14 _public prototype_ `static TSharedRef<IDetailCustomization> MakeInstance();`
- L15 _public prototype_ `virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;`
- L18 _private member_ `TArray<TWeakObjectPtr<UObject>> EditedObjects;`
- L19 _private prototype_ `FReply OnRunClicked();`
- L20 _private prototype_ `FReply OnStopClicked();`
- L21 _private prototype_ `FReply OnExportAllClicked();`
- L22 _private prototype_ `FReply OnExportNetworksClicked();`
- L23 _private prototype_ `FReply OnExportReplayBuffersClicked();`
- L24 _private prototype_ `FReply OnExportTrainerConfigClicked();`

#### Free symbols / members of external scopes

- L8 _macro_ `#define UE_API LEARNINGAGENTSTRAININGEDITOR_API`

### `Plugins/Experimental/LearningAgents/Source/LearningAgentsTrainingEditor/Public/LearningAgentsTrainingEditor.h` (Public)


#### class `FLearningAgentsTrainingEditorModule`  
`class FLearningAgentsTrainingEditorModule : public IModuleInterface`  
_L7-13_
- inherits: `IModuleInterface`
- L11 _public prototype_ `virtual void StartupModule() override;` — IModuleInterface implementation
- L12 _public prototype_ `virtual void ShutdownModule() override;`
